//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pce/constants.hpp>
#include <pce/brush.hpp>
#include <pce/layer.hpp>

#include <mlk/tools/math.h>

#include <QPainter>
#include <iostream>


namespace pce
{
	void brush::selection_begin(const QPoint& p)
	{
		m_selection_rect.setX(mlk::math::round_to(p.x(), 64));
		m_selection_rect.setY(mlk::math::round_to(p.y(), 64));
		m_selection_rect.setWidth(64);
		m_selection_rect.setHeight(64);
		
		m_current_rotation = 0.;
	}
	
	void brush::selecting(const QPoint& p)
	{
		auto w(mlk::math::round_to(p.x() - m_selection_rect.x(), 64)), h(mlk::math::round_to(p.y() - m_selection_rect.y(), 64));
		w = w < 0 ? -w : w;
		h = h < 0 ? -h : h;		
		m_selection_rect.setWidth(w);
		m_selection_rect.setHeight(h);
	}
	
	bool brush::selection_end(const layer* tiles_from_layer, bool from_layer_image)
	{
		if(m_selection_rect.width() == 0 || m_selection_rect.height() == 0)
		{
			this->reset();
			return false;
		}
		
		// get tiles inside of selection_rect
		m_tiles = tiles_from_layer->tiles_from_to(m_selection_rect, from_layer_image);
		 
		// recreate preview image
		m_preview = {m_selection_rect.width(), m_selection_rect.height(), QImage::Format_ARGB32};
		
		// redraw image
		QPainter p{&m_preview};
		constants::clear_image_pixels(m_preview);
		
		for(auto y(0); y < m_selection_rect.height() / 64; ++y)
			for(auto x(0); x < m_selection_rect.width() / 64; ++x)
			{
				auto coords(constants::coords_from_tileindex(m_tiles.at(y*(m_selection_rect.width()/64)+x).index));
				p.drawImage(x*64, y*64, *tiles_from_layer->image(), coords.x(), coords.y(), 64, 64);
			}
		
		return true;
	}
	
	void brush::reset()
	{
		m_selection_rect.setX(0);
		m_selection_rect.setY(0);
		m_selection_rect.setWidth(0);
		m_selection_rect.setHeight(0);
	}


	void brush::rotate(qreal angle)
	{
		auto cpy(m_preview);
		if(angle == 90. && cpy.width() != cpy.height())
		{
			m_preview = {m_preview.height(), m_preview.width(), QImage::Format_ARGB32};
			m_selection_rect.setWidth(m_preview.width());
			m_selection_rect.setHeight(m_preview.height());
		}
		
		QTransform t;
		t.rotate(angle);
		m_preview = cpy.transformed(t);
		
		this->add_rotation(angle);
	}
	
	
	void brush::add_rotation(qreal angle) noexcept
	{
//		std::cout << m_current_rotation << std::endl;
		
		if(m_current_rotation + angle >= 360.)
			m_current_rotation += angle - 360.;
		else
			m_current_rotation += angle;
		
		std::cout << m_current_rotation << std::endl;
	}
}
