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
		
	public:
		layer() = default;
		layer(int width, int height);
		
		void use_brush(const QRect& source_rect, const QImage& source_img, const QPoint& target_point);
		void move(qreal offx, qreal offy) noexcept;
		
		void set_position(const QPointF& pos) noexcept;
		void set_name(const std::string& name) noexcept;
	
		
		const auto& drawarea() const noexcept
		{return m_drawarea;}
		
		const auto& position() const noexcept
		{return m_position;}
		
		const auto& name() const noexcept
		{return m_name;}
		
	private:
		void clear(const QPoint& from, const QPoint& to);
	};
}


#endif // PCE_LAYER_HPP
