//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include "ui_main_window.h"
#include <pce/edit_area.hpp>
#include <pce/graphics_manager.hpp>

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
		m_graphic_preview_active{false},
		m_mouse_pressed{false},
		m_select_mode{select_mode::none}
	{this->init();}
	
	
	void edit_area::set_graphicsmgr(graphics_manager* gmgr)
	{m_graphicsmgr = gmgr;}
	
	void edit_area::set_ui(Ui::main_window* ui)
	{m_ui = ui;}
	
	
	void edit_area::key_pressed(QKeyEvent* ev)
	{this->keyPressEvent(ev);}
	
	void edit_area::key_released(QKeyEvent* ev)
	{this->keyReleaseEvent(ev);}
	
	
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
	
	
	void edit_area::paintEvent(QPaintEvent*)
	{
		// draw the stylsheet
		QStyleOption opt;
		opt.init(this);
		QPainter p{this};
		this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
		
		// get current selected image
		const QImage* current_img{nullptr};
		if(m_ui->lw_tilesets->currentIndex().row() != -1)
			current_img = &m_graphicsmgr->images().at(m_ui->lw_tilesets->currentItem()->text().toStdString());
		
		// draw image preview on space key press		
		if(m_graphic_preview_active && m_ui->lw_tilesets->currentIndex().row() != -1)
			p.drawImage(QPoint{0, 0}, *current_img);
		
		if(this->is_select_mode_any())
		{
			// draw selected shape
			p.setBrush({{255, 255, 255, 100}});
			p.setPen(Qt::white);
			p.drawRect(m_selected_rect);
			
			// draw info text
			p.setPen({0, 0, 0});
			auto w(m_selected_rect.width()), h(m_selected_rect.height());
			p.drawText(QPoint{m_selected_rect.x() + 5, m_selected_rect.y() + 13}, QString{"w: %1(%2), h: %3(%4)"}.arg(w / 64).arg(w).arg(h / 64).arg(h));
		}
		
		if((current_img != nullptr) && this->is_select_mode(select_mode::preview))
			p.drawImage(m_selected_rect, *current_img, m_source_selected_rect);
		
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
		m_mouse_pressed = true;
		this->reset_select_mode();
		
		m_selected_rect.setX(mlk::math::round_to(ev->x(), 64));
		m_selected_rect.setY(mlk::math::round_to(ev->y(), 64));
		m_selected_rect.setWidth(0);
		m_selected_rect.setHeight(0);
		
		m_source_selected_rect.setX(m_selected_rect.x());
		m_source_selected_rect.setY(m_selected_rect.y());
		m_source_selected_rect.setWidth(0);
		m_source_selected_rect.setHeight(0);
		this->repaint();
		ev->accept();
	}
	
	void edit_area::mouseMoveEvent(QMouseEvent* ev)
	{
		if(m_mouse_pressed)
		{
			m_select_mode = select_mode::selecting;
			m_selected_rect.setWidth(mlk::math::round_to(ev->x() - m_selected_rect.x(), 64));
			m_selected_rect.setHeight(mlk::math::round_to(ev->y() - m_selected_rect.y(), 64));
		}
		else
		{
			if(this->is_select_mode_any()) // why need i "-1" here ??
				m_selected_rect.setCoords(ev->x(), ev->y(), ev->x() + m_selected_rect.width() - 1, ev->y() + m_selected_rect.height() - 1);
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
		
		m_source_selected_rect.setWidth(m_selected_rect.width());
		m_source_selected_rect.setHeight(m_selected_rect.height());
		
		// reset invalid size
		if(m_selected_rect.width() == 0 || m_selected_rect.height() == 0)
			m_select_mode = select_mode::none;
		
		this->repaint();
	}
}
