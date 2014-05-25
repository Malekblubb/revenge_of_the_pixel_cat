//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pce/brush.hpp>

#include <mlk/tools/math.h>


namespace pce
{
	void brush::selection_begin(const QPoint& p)
	{
		m_selection_rect.setX(mlk::math::round_to(p.x(), 64));
		m_selection_rect.setY(mlk::math::round_to(p.y(), 64));
		m_selection_rect.setWidth(64);
		m_selection_rect.setHeight(64);
	}
	
	void brush::selecting(const QPoint& p)
	{
		auto w(mlk::math::round_to(p.x() - m_selection_rect.x(), 64)), h(mlk::math::round_to(p.y() - m_selection_rect.y(), 64));
		w = w < 0 ? -w : w;
		h = h < 0 ? -h : h;		
		m_selection_rect.setWidth(w);
		m_selection_rect.setHeight(h);
	}
	
	bool brush::selection_end()
	{
		if(m_selection_rect.width() == 0 || m_selection_rect.height() == 0)
		{
			this->reset();
			return false;
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
}
