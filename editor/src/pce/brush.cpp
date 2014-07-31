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
	
	bool brush::selection_end(const layer* l, bool from_layer_image)
	{
		if(m_selection_rect.width() == 0 || m_selection_rect.height() == 0)
		{
			this->reset();
			return false;
		}
		
		// get tiles inside of selection_rect
		m_tiles = l->tiles_in_rect(m_selection_rect, from_layer_image);
		 
		// recreate preview image
		m_preview = {m_selection_rect.width(), m_selection_rect.height(), QImage::Format_ARGB32_Premultiplied};
		
		// copy image
		constants::clear_image_pixels(m_preview);
		QPainter p{&m_preview};
		if(l->image() != nullptr)
			p.drawImage({0, 0}, from_layer_image ? l->drawarea() : *l->image(), m_selection_rect);
		
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
		// save current rect
		m_last_rect = m_selection_rect;
					  
		auto cpy(m_preview);
		if(angle == 90. && cpy.width() != cpy.height())
		{
			// recreate preview image
			m_preview = {m_preview.height(), m_preview.width(), QImage::Format_ARGB32_Premultiplied};
			
			// change size
			m_selection_rect.setWidth(m_preview.width());
			m_selection_rect.setHeight(m_preview.height());
		}
		
		m_preview = cpy.transformed(QTransform{}.rotate(angle));
		
		// calculate current rotation
		this->add_rotation(angle);
		
		// add the rotation to the tiles
		for(auto& a : m_tiles)
			a.rotation = a.rotation + angle >= 360. ? a.rotation + angle - 360. : a.rotation + angle;
		
		// reorder tiles to fit rotation
		this->reorder_tiles(angle == 90 ? reorder_action::rotate90 : reorder_action::rotate180);
	}
	
	void brush::flip(tile_flag f)
	{		
		for(auto& a : m_tiles)
			a.flags |= f;

		
		if(f == tile_flag::flip_horizontal)
		{
			auto cpy(m_preview);
			m_preview = cpy.transformed(QTransform{}.scale(-1., 1.));
		}
		else if(f == tile_flag::flip_vertical)
		{
			auto cpy(m_preview);
			m_preview = cpy.transformed(QTransform{}.scale(1., -1.));
		}
		
		this->reorder_tiles(f == tile_flag::flip_horizontal ? reorder_action::flip_h : reorder_action::flip_v);
	}
	
	
	void brush::add_rotation(qreal angle) noexcept
	{
		if(m_current_rotation + angle >= 360.)
			m_current_rotation += angle - 360.;
		else
			m_current_rotation += angle;
	}
	
	void brush::reorder_tiles(reorder_action a)
	{
		auto w(m_last_rect.width() / 64), h(m_last_rect.height() / 64);
		
		if(a == reorder_action::rotate90 || a == reorder_action::rotate180)
		{
			auto old_tiles(m_tiles);
			auto tile_index(0);
			m_tiles.clear();
			m_tiles.resize(w*h);
			
			if(a == reorder_action::rotate90)
			{
				for(auto x(0); x < w; ++x)
					for(auto y(h - 1); y >= 0; --y, ++tile_index)  
						m_tiles[tile_index] = old_tiles[y * w + x];
			}
			else if(a == reorder_action::rotate180)
			{			
				for(auto y(h - 1); y >= 0; --y)
					for(auto x(w - 1); x >= 0; --x, ++tile_index)
						m_tiles[tile_index] = old_tiles[y * w + x];
			}
		}
		else if(a == reorder_action::flip_h)
		{
			auto old_tiles(m_tiles);
			auto tile_index(0);
			
			for(auto y(0); y < h; ++y)
				for(auto x(w - 1); x >= 0; --x, ++tile_index)
					m_tiles[tile_index] = old_tiles[y*w+x];
		}
		else if(a == reorder_action::flip_v)
		{
			
		}
	}
}
