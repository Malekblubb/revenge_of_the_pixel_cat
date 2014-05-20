//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_EDIT_AREA_HPP
#define PCE_EDIT_AREA_HPP


#include <QWidget>


namespace pce
{
	class edit_area : public QWidget
	{
		Q_OBJECT

		bool m_graphic_preview_active;
		
	public:
		edit_area(QWidget* parent = nullptr);
		
	public slots:
		// provide an interface for other widgets
		// to send their key events
		void key_pressed(QKeyEvent* ev);
		void key_released(QKeyEvent* ev);
		
	private:
		void init();
		
		// events
		void paintEvent(QPaintEvent*) override;
		void keyPressEvent(QKeyEvent* ev) override;
		void keyReleaseEvent(QKeyEvent* ev) override;
	};
}


#endif // PCE_EDIT_AREA_HPP
