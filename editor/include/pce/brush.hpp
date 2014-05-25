//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_BRUSH_HPP
#define PCE_BRUSH_HPP


#include <QPoint>
#include <QRect>


namespace pce
{
	class brush
	{
		QRect m_selection_rect;
		
	public:
		void selection_begin(const QPoint& p);
		void selecting(const QPoint& p);
		bool selection_end();
		void reset();
		
		const auto& rect() const noexcept
		{return m_selection_rect;}
	};
}


#endif // PCE_BRUSH_HPP
