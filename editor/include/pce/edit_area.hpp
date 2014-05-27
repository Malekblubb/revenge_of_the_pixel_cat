//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_EDIT_AREA_HPP
#define PCE_EDIT_AREA_HPP


#include "brush.hpp"

#include <QRect>
#include <QVector>
#include <QWidget>


namespace Ui
{class main_window;}

namespace pce
{
	enum class select_mode : char
	{
		none,
		selecting,	// currently selecting
		preview,	// selection in the preview-area
		edit		// selection in the edit-area
	};
	
	class edit_area : public QWidget
	{
		Q_OBJECT

		// selection
		brush m_brush;
		QRect m_target_rect;
		select_mode m_select_mode;
		
		// grid
		QVector<QLineF> m_grid_lines;
		
		qreal m_scale;
		
		bool m_graphic_preview_active;
		bool m_mouse_pressed;
		bool m_grid_active;
		
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
		
		// settings slots
		void grid_state_changed(bool b);
		void grid_update_requested(QString);
		void scale_change_requested(int i);
		
	private:
		void init();
		
		// other utils
		void reset_select_mode() noexcept;
		bool is_select_mode(select_mode mode) const noexcept;
		bool is_select_mode_any() const noexcept;
		
		void recalc_grid();
		
		// events
		void paintEvent(QPaintEvent*) override;
		
		// input
		void keyPressEvent(QKeyEvent* ev) override;
		void keyReleaseEvent(QKeyEvent* ev) override;
		void mousePressEvent(QMouseEvent* ev) override;
		void mouseMoveEvent(QMouseEvent* ev) override;
		void mouseReleaseEvent(QMouseEvent*) override;
		void wheelEvent(QWheelEvent*) override;
	};
}


#endif // PCE_EDIT_AREA_HPP
