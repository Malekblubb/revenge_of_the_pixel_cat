//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pce/layer.hpp>

#include <QPainter>


namespace pce
{
	layer::layer(int width, int height) :
		m_drawarea{width, height, QImage::Format_ARGB32},
		m_position{0.f, 0.f}
	{ }
	
	void layer::use_brush(const QRect& source_rect, const QImage& source_img, const QPoint& target_point)
	{
		QPainter p{&m_drawarea};
		p.drawImage(target_point, source_img, source_rect);
	}
	
	void layer::move(qreal offx, qreal offy) noexcept
	{
		m_position.setX(m_position.x() + offx);
		m_position.setY(m_position.y() + offy);
	}
}

