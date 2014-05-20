//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_GRAPHICSLIST_WIDGET_HPP
#define PCE_GRAPHICSLIST_WIDGET_HPP


#include <QListWidget>


namespace pce
{
	class graphicslist_widget : public QListWidget
	{
		Q_OBJECT
		
	public:
		graphicslist_widget(QWidget* parent = nullptr) :
			QListWidget{parent}
		{ }
		
	signals:
		void key_pressed(QKeyEvent* ev);
		void key_released(QKeyEvent* ev);
		
	private:
		void keyPressEvent(QKeyEvent* ev) override
		{emit this->key_pressed(ev);}
		
		void keyReleaseEvent(QKeyEvent* ev) override
		{emit this->key_released(ev);}
	};
}


#endif // PCE_GRAPHICSLIST_WIDGET_HPP
