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
		abort,
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
		QPointF m_global_translate;
		const QImage* m_current_img;
		
		QPointF m_mousewheel_offset;
		
		bool m_graphic_preview_active;
		bool m_mouse_pressed;
		bool m_mousewheel_pressed;
		bool m_control_pressed;
		bool m_grid_active;
		
		class graphics_manager* m_graphicsmgr;
		class layer_manager* m_layermgr;
		class status_manager* m_statusmgr;
		Ui::main_window* m_ui;
		
	public:
		edit_area(QWidget* parent = nullptr);
		
		void set_graphicsmgr(class graphics_manager* gmgr) noexcept
		{m_graphicsmgr = gmgr;}
		
		void set_layermgr(class layer_manager* lmgr) noexcept
		{m_layermgr = lmgr;}
		
		void set_statusmgr(class status_manager* smgr) noexcept
		{m_statusmgr = smgr;}
		
		void set_ui(Ui::main_window* ui) noexcept
		{m_ui = ui;}
		
		auto* layermgr() noexcept
		{return m_layermgr;}
		
		const auto& global_translate() const noexcept
		{return m_global_translate;}
		
	signals:
		void layer_moved();
		void global_translate_changed();
		
	public slots:
		// provide an interface for other widgets
		// to send their key events
		void key_pressed(QKeyEvent* ev);
		void key_released(QKeyEvent* ev);
		
		// settings slots
		void grid_state_changed(bool b);
		void grid_update_requested(QString);
		void scale_change_requested(int i);
		
		// global transform slots
		void translate_x_request(qreal value) noexcept;
		void translate_y_request(qreal value) noexcept;
		void set_translate_x(qreal value) noexcept;
		void set_translate_y(qreal value) noexcept;
		
		// brush slots
		void brush_rotate_180_request();
		void brush_rotate_90_request();
		void brush_flip_horizontal_request();
		void brush_flip_vertical_request();
		
		// repaint request
		void repaint_request();
		
	private:
		void init();
		
		// other utils
		void reset_select_mode() noexcept;
		bool is_select_mode(select_mode mode) const noexcept;
		bool is_select_mode_any() const noexcept;
		
		QPoint validate_mousepos(int x, int y) const noexcept;
		
		void recalc_grid();
		
		void move_target_rect_invalid(const QPoint& p);
		void use_brush_invalid(const QPoint& p);
		
		// events
		void paintEvent(QPaintEvent*) override;
		
		// input
		void keyPressEvent(QKeyEvent* ev) override;
		void keyReleaseEvent(QKeyEvent* ev) override;
		void mousePressEvent(QMouseEvent* ev) override;
		void mouseMoveEvent(QMouseEvent* ev) override;
		void mouseReleaseEvent(QMouseEvent* ev) override;
		void wheelEvent(QWheelEvent*) override;
		
		void handle_mousepress(QMouseEvent* ev);
		void handle_mouse_move(QMouseEvent* ev);
		void handle_mouse_release(QMouseEvent*);
	};
}


#endif // PCE_EDIT_AREA_HPP
