//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_LAYER_HPP
#define PCE_LAYER_HPP


#include "tile.hpp"

#include <string>
#include <vector>

#include <QImage>
#include <QRect>


namespace pce
{
	class layer
	{
		int m_num_tiles_x;
		int m_num_tiles_y;
		QImage m_drawarea;
		QPointF m_position;
		std::vector<tile> m_tiles;		
		std::string m_name;
		
		const QImage* m_image{nullptr};
		std::string m_image_name;
		
	public:
		layer() = default;
		layer(int width, int height);
		
		void use_brush(const class brush* b, const QPoint& target_point, bool self);
		void move(qreal offx, qreal offy) noexcept;
		
		void set_size(int num_tiles_x, int num_tiles_y);
		void set_position(const QPointF& pos) noexcept;
		void set_position_x(qreal x) noexcept;
		void set_position_y(qreal y) noexcept;
		void set_name(const std::string& name) noexcept;
		void set_image(const QImage* img, const std::string& name) noexcept;
	
		
		int num_tiles_x() const noexcept
		{return m_num_tiles_x;}
		
		int num_tiles_y() const noexcept
		{return m_num_tiles_y;}
		
		const auto& drawarea() const noexcept
		{return m_drawarea;}
		
		const auto& position() const noexcept
		{return m_position;}
		
		auto name() const noexcept
		{return m_name + " (" + m_image_name + ")";}
		
		const auto& image_name() const noexcept
		{return m_image_name;}
		
		const auto* image() const noexcept
		{return m_image;}
		
		const auto& tiles() const noexcept
		{return m_tiles;}
		
		std::vector<tile> tiles_from_to(const QRect& rect, bool self) const;
		
	private:
		void clear(const QPoint& from, const QPoint& to);
		void clear_all();
		void redraw();
		void on_image_change();
	};
}


#endif // PCE_LAYER_HPP
