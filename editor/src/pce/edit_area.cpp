//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include "ui_main_window.h"
#include <pce/edit_area.hpp>
#include <pce/graphics_manager.hpp>
#include <pce/layer_manager.hpp>
#include <pce/list_widget_layer_item.hpp>

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
		m_global_translate{0., 0.},
		m_current_img{nullptr},
		m_mousewheel_offset{0., 0.},
		m_graphic_preview_active{false},
		m_mouse_pressed{false},
		m_mousewheel_pressed{false},
		m_grid_active{false}
	{this->init();}
	
	
	void edit_area::set_graphicsmgr(graphics_manager* gmgr) noexcept
	{m_graphicsmgr = gmgr;}
	
	void edit_area::set_layermgr(layer_manager* lmgr) noexcept
	{m_layermgr = lmgr;}
	
	void edit_area::set_ui(Ui::main_window* ui) noexcept
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
		m_scale = i % 10 == 0 ? static_cast<qreal>(i) / 100 : 1.;
		m_ui->sb_scale->setValue(m_scale * 100);
		this->recalc_grid();
		this->repaint();
	}
	
	void edit_area::translate_x_request(qreal value) noexcept
	{
		m_global_translate.setX(m_global_translate.x() + value);
		emit this->global_translate_changed();
	}
	
	void edit_area::translate_y_request(qreal value) noexcept
	{
		m_global_translate.setY(m_global_translate.y() + value);
		emit this->global_translate_changed();
	}
	
	void edit_area::set_translate_x(qreal value) noexcept
	{
		m_global_translate.setX(value);
		emit this->global_translate_changed();
	}
	
	void edit_area::set_translate_y(qreal value) noexcept
	{
		m_global_translate.setY(value);
		emit this->global_translate_changed();
	}

	
	void edit_area::repaint_request()
	{this->repaint();}
	
	
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
	
	
	QPoint edit_area::validate_mousepos(int x, int y) const noexcept
	{		
		return 
		{
			static_cast<int>(mlk::math::round_to(static_cast<qreal>(x), 64 * m_scale) / m_scale),
			static_cast<int>(mlk::math::round_to(static_cast<qreal>(y), 64 * m_scale) / m_scale)
		};
	}
	
	
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
		
		
		// ---------------------------------------------------------------
		
		
		// transform
		QTransform t;
		t.scale(m_scale, m_scale);
		p.setTransform(t);
		
		
		// -------- draw WITHOUT translation --------
		// get current selected image
		if(m_ui->lw_tilesets->currentIndex().row() != -1)
			m_current_img = &m_graphicsmgr->images().at(m_ui->lw_tilesets->currentItem()->text().toStdString());
			
		
		// draw image preview on space key press		
		if(m_graphic_preview_active && m_ui->lw_tilesets->currentIndex().row() != -1)
			p.drawImage(QPoint{0, 0}, *m_current_img);
		
		
		// ---------------------------------------------------------------
		
		
		// draw selected shape
		p.setBrush({{255, 255, 255, 100}});
		p.setPen(Qt::white);
		
		if(!m_graphic_preview_active)
		{
			t.translate(m_global_translate.x(), m_global_translate.y());
			p.setTransform(t);
		}
		
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
		
		if((m_current_img != nullptr) && this->is_select_mode(select_mode::preview))
			p.drawImage(m_target_rect, *m_current_img, m_brush.rect());
			
		
		t.translate(-m_global_translate.x(), -m_global_translate.y());
		p.setTransform(t);
		
		
		// draw the grid
		if(m_grid_active)
		{
			p.setPen(QColor{"#" + m_ui->le_gridcolor->text()});
			p.drawLines(m_grid_lines);
		}
		
		// draw "world zero point"
		p.setPen(Qt::green);
		p.drawText(QPointF{0., 320.}, "World zero point");
		p.drawLine(QPointF{0., 320.}, QPointF{this->width() / m_scale, 320.});
		
		
		t.translate(m_global_translate.x(), m_global_translate.y());
		p.setTransform(t);
		
		
		// -------- draw ON translation --------		
		// draw layers (sorted)		
		auto* layerlist(m_ui->lw_layers);
		for(auto i(layerlist->count() - 1); i != -1; --i)
		{
			auto* layer(m_layermgr->from_rowindex(i));
			if(layer == nullptr)
				continue;
			
			// copy the transform for each layer
			auto tc(t);
			tc.translate(layer->position().x(), layer->position().y());
			p.setTransform(tc);
			
			// draw layer content
			p.drawImage(QPoint{0, 0}, layer->drawarea());
			
			// draw layer outrect
			if(i == layerlist->currentRow())
				p.setPen(Qt::blue);
			else
				p.setPen(Qt::red);
			auto rect(layer->drawarea().rect());
			p.drawText(QPoint{rect.x(), layer->position().y() <= 10 ? 10 : rect.y()}, layer->name().c_str());
			p.setBrush(QColor{0, 0, 0, 0});
			p.drawRect(rect);
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
		ev->accept();
		
		if(ev->button() == Qt::LeftButton)
		{
			if(this->is_select_mode(select_mode::none))
			{
				m_mouse_pressed = true;
				m_select_mode = select_mode::selecting;
				
				// start the selection
				if(m_graphic_preview_active)
					m_brush.selection_begin(ev->pos() / m_scale);
				else
					m_brush.selection_begin(ev->pos() / m_scale - QPoint{static_cast<int>(m_global_translate.x()), static_cast<int>(m_global_translate.y())});
				
				// target begin == brush
				m_target_rect = m_brush.rect();
			}
			else
				if(m_current_img != nullptr && m_layermgr->selected_layer() != nullptr &&
						m_layermgr->selected_layer()->image() == m_current_img && this->is_select_mode(select_mode::preview))
				{
					auto validated(this->validate_mousepos(ev->x(), ev->y()));
					validated -= QPoint{static_cast<int>(m_layermgr->selected_layer()->position().x() + m_global_translate.x()),
										static_cast<int>(m_layermgr->selected_layer()->position().y() + m_global_translate.y())};
					m_layermgr->selected_layer()->use_brush(m_brush.rect(), *m_current_img, {validated.x(), validated.y()});
				}
		}
		else if(ev->button() == Qt::RightButton)
		{
			m_mouse_pressed = false;
			m_select_mode = select_mode::abort;
			
			m_brush.reset();
			m_target_rect.setWidth(0);
			m_target_rect.setHeight(0);
		}
		
		m_mousewheel_pressed = ev->button() == Qt::MiddleButton;
		if(m_mousewheel_pressed && m_layermgr->selected_layer() != nullptr) // calc the offset between layer and mouse for better moving
			m_mousewheel_offset = ev->posF() - m_layermgr->selected_layer()->position();
		
		this->repaint();
	}
	
	void edit_area::mouseMoveEvent(QMouseEvent* ev)
	{
		ev->accept();
		
		if(m_mouse_pressed)
			m_brush.selecting(ev->pos() / m_scale);
		else
		{
			if(this->is_select_mode_any()) // why need i "-1" here ??
			{
				auto validated(this->validate_mousepos(ev->x(), ev->y()));
				validated -= {(int)m_global_translate.x(), (int)m_global_translate.y()};
				m_target_rect.setCoords(validated.x(), validated.y(), validated.x() + m_brush.rect().width() - 1, validated.y() + m_brush.rect().height() - 1);
			}
		}
		
		if(m_mousewheel_pressed && m_layermgr->selected_layer() != nullptr)
		{
			// mousepos - start offset = moving the layer from the start-mouse-point, not from topleft corner
			auto newpos(ev->posF() - m_mousewheel_offset);
			m_layermgr->selected_layer()->set_position({mlk::math::round_to(newpos.x(), 64.), mlk::math::round_to(newpos.y(), 64.)});
			
			// emit layer_moved signal
			emit this->layer_moved();
		}
		
		this->repaint();
	}
	
	void edit_area::mouseReleaseEvent(QMouseEvent*)
	{		
		m_mouse_pressed = false;
		
		if(this->is_select_mode(select_mode::selecting) || this->is_select_mode(select_mode::abort))
		{
			
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
		}
	
		
		m_mousewheel_pressed = false;
		
		this->repaint();
	}
	
	void edit_area::wheelEvent(QWheelEvent* ev)
	{
		ev->accept();
		
		auto d(ev->delta() / 8 / 15);
		m_scale += d < 0 ? -0.1 : 0.1;
		if(m_scale >= 1.9) m_scale = 1.9;
		else if(m_scale <= 0.1) m_scale = 0.1;
		
		this->scale_change_requested(std::round(m_scale * 100));
	}
}
