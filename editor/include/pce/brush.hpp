//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_BRUSH_HPP
#define PCE_BRUSH_HPP


#include <pce/tile.hpp>

#include <QImage>
#include <QPoint>
#include <QRect>

#include <vector>


namespace pce
{
	class brush
	{
		QImage m_preview;
		QRect m_selection_rect;
		std::vector<tile> m_tiles;
		qreal m_current_rotation{0.};
		
	public:
		void selection_begin(const QPoint& p);
		void selecting(const QPoint& p);
		bool selection_end(const class layer* tiles_from_layer, bool from_layer_image);
		void reset();
		
		void rotate(qreal angle);
		
		const auto& preview() const noexcept
		{return m_preview;}
		
		const auto& rect() const noexcept
		{return m_selection_rect;}
		
		const auto& tiles() const noexcept
		{return m_tiles;}
		
		auto rotation() const noexcept
		{return m_current_rotation;}
		
	private:
		void add_rotation(qreal angle) noexcept;
	};
}


#endif // PCE_BRUSH_HPP
