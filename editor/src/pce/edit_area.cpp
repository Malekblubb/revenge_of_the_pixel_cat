//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pce/edit_area.hpp>

#include <QKeyEvent>
#include <QPainter>
#include <QStyleOption>
#include <iostream>


namespace pce
{	
	edit_area::edit_area(QWidget* parent) :
		QWidget{parent},
		m_graphic_preview_active{false}
	{this->init();}
	
	void edit_area::key_pressed(QKeyEvent* ev)
	{this->keyPressEvent(ev);}

	void edit_area::key_released(QKeyEvent* ev)
	{this->keyReleaseEvent(ev);}
	
	void edit_area::init()
	{
		// set focus policy
		this->setFocusPolicy(Qt::StrongFocus);
		
		// set stylesheet
		this->setStyleSheet("background-image:url(://assets/checker.png);");
	}
	
	void edit_area::paintEvent(QPaintEvent*)
	{
		// draw the stylsheet
		QStyleOption opt;
	    opt.init(this);
		QPainter p{this};
	    this->style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
		
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
}
