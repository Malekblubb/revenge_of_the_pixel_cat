//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_EDIT_AREA_HPP
#define PCE_EDIT_AREA_HPP


#include <QRect>
#include <QWidget>


namespace Ui
{class main_window;}

namespace pce
{
	class edit_area : public QWidget
	{
		Q_OBJECT

		QRect m_selected_rect;
		QRect m_source_selected_rect;
		bool m_graphic_preview_active;
		bool m_mouse_pressed;
		bool m_selected;
		
		class graphics_manager* m_graphicsmgr;
		Ui::main_window* m_ui;
		
	public:
		edit_area(QWidget* parent = nullptr);
		
		void set_graphicsmgr(class graphics_manager* gmgr);
		void set_ui(Ui::main_window* ui);
		
	public slots:
		// provide an interface for other widgets
		// to send their key events
		void key_pressed(QKeyEvent* ev);
		void key_released(QKeyEvent* ev);
		
	private:
		void init();
		
		// events
		void paintEvent(QPaintEvent*) override;
		
		// input
		void keyPressEvent(QKeyEvent* ev) override;
		void keyReleaseEvent(QKeyEvent* ev) override;
		void mousePressEvent(QMouseEvent* ev) override;
		void mouseMoveEvent(QMouseEvent* ev) override;
		void mouseReleaseEvent(QMouseEvent* ev) override;
	};
}


#endif // PCE_EDIT_AREA_HPP
