//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pce/layer.hpp>

#include <mlk/log/log.h>

#include <QPainter>
#include <iostream>

namespace pce
{
	layer::layer(int width, int height) :
		m_num_tiles_x{width},
		m_num_tiles_y{height},
		m_drawarea{width * 64, height * 64, QImage::Format_ARGB32},
		m_position{0.f, 0.f},
		m_tiles(width * height)
	{ }
	
	void layer::use_brush(const QRect& source_rect, const QImage& source_img, const QPoint& target_point)
	{
		for(auto sy(source_rect.y()), ty(target_point.y()); sy < source_rect.height() + source_rect.y(); sy += 64, ty += 64)
		{
			for(auto sx(source_rect.x()), tx(target_point.x()); sx < source_rect.width() + source_rect.x(); sx += 64, tx += 64)
			{				
				auto index(((sy / 64) * 16) + (sx / 64)), target_tile(((ty / 64) * m_num_tiles_x) + (tx / 64));
				if(static_cast<mlk::st>(target_tile) >= m_tiles.size())
				{
					mlk::lerr()["pce::layer"] << "wrong target_tile index. requested: " << target_tile << ", max: " << m_tiles.size() - 1;
					continue;
				}
				
				m_tiles[target_tile] = {index, 0};
			}
		}
		
		this->clear({target_point.x(), target_point.y()}, {target_point.x() + source_rect.width(), target_point.y() + source_rect.height()});
		
		QPainter p{&m_drawarea};
		p.drawImage(target_point, source_img, source_rect);
	}
	
	void layer::move(qreal offx, qreal offy) noexcept
	{
		m_position.setX(m_position.x() + offx);
		m_position.setY(m_position.y() + offy);
	}
	
	void layer::set_position(const QPointF& pos) noexcept
	{
		m_position = pos;
	}
	
	
	void layer::clear(const QPoint& from, const QPoint& to)
	{
		for(auto y(from.y()); y < to.y(); ++y)
			for(auto x(from.x()); x < to.x(); ++x)
				m_drawarea.setPixel(x, y, 0);
	}
}

