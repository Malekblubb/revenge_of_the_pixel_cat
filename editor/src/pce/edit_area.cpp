//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include "ui_main_window.h"
#include <pce/edit_area.hpp>
#include <pce/graphics_manager.hpp>

#include <mlk/containers/container_utl.h>
#include <mlk/tools/math.h>

#include <QBrush>
#include <QKeyEvent>
#include <QPainter>
#include <QPaintEngine>
#include <QStyleOption>
#include <iostream>


namespace pce
{	
	edit_area::edit_area(QWidget* parent) :
		QWidget{parent},
		m_select_mode{select_mode::none},
		m_scale{1.},
		m_graphic_preview_active{false},
		m_mouse_pressed{false},
		m_grid_active{false}
	{this->init();}
	
	
	void edit_area::set_graphicsmgr(graphics_manager* gmgr)
	{m_graphicsmgr = gmgr;}
	
	void edit_area::set_ui(Ui::main_window* ui)
	{m_ui = ui;}
	
	
	void edit_area::key_pressed(QKeyEvent* ev)
	{this->keyPressEvent(ev);}
	
	void edit_area::key_released(QKeyEvent* ev)
	{this->keyReleaseEvent(ev);}
	
	void edit_area::grid_state_changed(bool b)
	{
		m_grid_active = b;
		if(b)
			this->recalc_grid();
		this->repaint();
	}
	
	void edit_area::grid_update_requested(QString)
	{
		this->recalc_grid();
		this->repaint();
	}
	
	void edit_area::scale_change_requested(int i)
	{
		m_scale = i % 10 == 0 ? static_cast<qreal>(i) / 100 : 1.f;
		m_ui->sb_scale->setValue(m_scale * 100);
		this->recalc_grid();
		this->repaint();
	}
	
	
	void edit_area::init()
	{		
		// set focus policy
		this->setFocusPolicy(Qt::StrongFocus);
		
		// set mousetracking
		this->setMouseTracking(true);
		
		// set stylesheet
		this->setStyleSheet("background-image:url(://assets/checker.png);");
	}
	
	
	void edit_area::reset_select_mode() noexcept
	{m_select_mode = select_mode::none;}
	
	bool edit_area::is_select_mode(select_mode mode) const noexcept
	{return m_select_mode == mode;}
	
	bool edit_area::is_select_mode_any() const noexcept
	{return m_select_mode != select_mode::none;}
	
	
	void edit_area::recalc_grid()
	{
		m_grid_lines.clear();
		qreal sizex(m_ui->sb_grid_x->value()), sizey(m_ui->sb_grid_y->value());
		
		for(auto i(sizex); i < m_ui->w_edit_area->width() / m_scale; i += sizex)
			m_grid_lines.push_back({i, 0, i, m_ui->w_edit_area->height() / m_scale});
		
		for(auto i(sizey); i < m_ui->w_edit_area->height() / m_scale; i += sizey)
			m_grid_lines.push_back({0, i, m_ui->w_edit_area->width() / m_scale, i});
	}
	
	
	void edit_area::paintEvent(QPaintEvent*)
	{
		QPainter p{this};
		
		// draw the stylsheet
		QStyleOption opt;
		opt.init(this);
		this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
		
		// transform
		QTransform t;
		t.scale(m_scale, m_scale);
		p.setTransform(t);
		
		// get current selected image
		const QImage* current_img{nullptr};
		if(m_ui->lw_tilesets->currentIndex().row() != -1)
			current_img = &m_graphicsmgr->images().at(m_ui->lw_tilesets->currentItem()->text().toStdString());
		
		// draw image preview on space key press		
		if(m_graphic_preview_active && m_ui->lw_tilesets->currentIndex().row() != -1)
			p.drawImage(QPoint{0, 0}, *current_img);
		
		
		// draw selected shape
		p.setBrush({{255, 255, 255, 100}});
		p.setPen(Qt::white);
		
		if(this->is_select_mode(select_mode::selecting))
			p.drawRect(m_brush.rect());
		else if(this->is_select_mode_any())
			p.drawRect(m_target_rect);
		
		if(this->is_select_mode_any())
		{
			// draw info text
			p.setPen({0, 0, 0});
			auto w(m_brush.rect().width()), h(m_brush.rect().height());
			p.drawText(QPoint{m_target_rect.x(), m_target_rect.y()}, QString{"w: %1(%2), h: %3(%4)"}.arg(w / 64).arg(w).arg(h / 64).arg(h));
		}
		
		if((current_img != nullptr) && this->is_select_mode(select_mode::preview))
			p.drawImage(m_target_rect, *current_img, m_brush.rect());
		
		// draw the grid
		if(m_grid_active)
		{
			p.setPen(QColor{"#" + m_ui->le_gridcolor->text()});
			p.drawLines(m_grid_lines);
		}
		
		std::cout << "repaint" << std::endl;
		
	}
	
	void edit_area::keyPressEvent(QKeyEvent* ev)
	{
		if(ev->isAutoRepeat())
		{
			ev->ignore();
			return;
		}
		
		if((ev->key() == Qt::Key::Key_Space))
		{
			m_graphic_preview_active = true;
			this->repaint();
			ev->accept();
		}
	}
	
	void edit_area::keyReleaseEvent(QKeyEvent* ev)
	{
		if(ev->isAutoRepeat())
		{
			ev->ignore();
			return;
		}
		
		if((ev->key() == Qt::Key::Key_Space))
		{
			m_graphic_preview_active = false;
			this->repaint();
			ev->accept();
		}
	}
	
	void edit_area::mousePressEvent(QMouseEvent* ev)
	{
		this->reset_select_mode();
		
		if(ev->button() == Qt::LeftButton)
		{
			m_mouse_pressed = true;
			
			// start the selection
			m_brush.selection_begin(ev->pos() / m_scale);
			
			// target begin == brush
			m_target_rect = m_brush.rect();
		}
		else
		{
			m_mouse_pressed = false;
			
			m_brush.reset();
			m_target_rect.setWidth(0);
			m_target_rect.setHeight(0);
		}
		
		this->repaint();
		ev->accept();
	}
	
	void edit_area::mouseMoveEvent(QMouseEvent* ev)
	{
		if(m_mouse_pressed)
		{
			m_select_mode = select_mode::selecting;
			m_brush.selecting(ev->pos() / m_scale);
		}
		else
		{
			if(this->is_select_mode_any()) // why need i "-1" here ??
			{
				auto x(mlk::math::round_to(static_cast<qreal>(ev->x()), 64 * m_scale) / m_scale);
				auto y(mlk::math::round_to(static_cast<qreal>(ev->y()), 64 * m_scale) / m_scale);
				m_target_rect.setCoords(x, y, x + m_brush.rect().width() - 1, y + m_brush.rect().height() - 1);
			}
		}
		this->repaint();
		ev->accept();
	}
	
	void edit_area::mouseReleaseEvent(QMouseEvent*)
	{
		m_mouse_pressed = false;
		
		// change select mode
		if(m_graphic_preview_active)
			m_select_mode = select_mode::preview;
		else
			m_select_mode = select_mode::edit;
		
		m_target_rect.setWidth(m_brush.rect().width());
		m_target_rect.setHeight(m_brush.rect().height());
		
		// reset invalid size
		if(!m_brush.selection_end())
			m_select_mode = select_mode::none;
		
		this->repaint();
	}
	
	void edit_area::wheelEvent(QWheelEvent* ev)
	{
		auto d(ev->delta() / 8 / 15);
		m_scale += d < 0 ? -0.1 : 0.1;
		if(m_scale >= 1.9) m_scale = 1.9;
		else if(m_scale <= 0.1) m_scale = 0.1;
		
		this->scale_change_requested(m_scale * 100);
	}
}
