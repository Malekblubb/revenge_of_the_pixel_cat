//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pce/brush.hpp>
#include <pce/constants.hpp>
#include <pce/layer.hpp>

#include <mlk/log/log.h>

#include <QPainter>
#include <iomanip>


namespace pce
{
	layer::layer(int width, int height) :
		m_num_tiles_x{width},
		m_num_tiles_y{height},
		m_drawarea{width * 64, height * 64, QImage::Format_ARGB32},
		m_position{0.f, 0.f},
		m_tiles(width * height, {0, 0}),
		m_name{"Layer#"}
	{this->clear_all();}
	
	void layer::use_brush(const brush* b, const QRect& source_rect, const QPoint& target_point, bool self)
	{
		if(self && source_rect.contains(target_point))
			return;
		
		auto bx(0), by(0);
		for(auto sy(source_rect.y()), ty(target_point.y()); sy < source_rect.height() + source_rect.y(); sy += 64, ty += 64, ++by)
		{bx = 0;
			for(auto sx(source_rect.x()), tx(target_point.x()); sx < source_rect.width() + source_rect.x(); sx += 64, tx += 64, ++bx)
			{		
				auto index(((sy / 64) * 16) + (sx / 64)), target_tile(((ty / 64) * m_num_tiles_x) + (tx / 64));
				if(static_cast<mlk::st>(target_tile) >= m_tiles.size())
				{
					mlk::lerr()["pce::layer"] << "wrong target_tile index. requested: " << target_tile << ", max: " << m_tiles.size() - 1;
					continue;
				}
				

				m_tiles[target_tile] = b->tiles().at(by * source_rect.width() / 64 + bx);
			}
		}
		
		this->clear({target_point.x(), target_point.y()}, {target_point.x() + source_rect.width(), target_point.y() + source_rect.height()});
		
		// redraw full layer
		this->redraw();
	}
	
	void layer::move(qreal offx, qreal offy) noexcept
	{
		m_position.setX(m_position.x() + offx);
		m_position.setY(m_position.y() + offy);
	}
	
	
	void layer::set_size(int num_tiles_x, int num_tiles_y)
	{
		std::vector<tile> new_vec(num_tiles_x * num_tiles_y);
		
		// copy to new vec
		for(auto y(0); y < num_tiles_y; ++y)
		{
			for(auto x(0); x < num_tiles_x; ++x)	
			{
				if(x >= m_num_tiles_x || y >= m_num_tiles_y)
					new_vec[y * num_tiles_x + x] = {0, 0};
				else
					new_vec[y * num_tiles_x + x] = m_tiles[y * m_num_tiles_x + x];
			}
		}
		
		std::cout << "OLD-----------" << std::endl;
		for(auto y(0); y < m_num_tiles_y; ++y)
		{
			for(auto x(0); x < m_num_tiles_x; ++x)	
			{
				std::cout << std::setw(2) << std::setfill('0') << m_tiles[y * m_num_tiles_x + x].index << " ";
			}
			std::cout << std::endl;
		}
		
		std::cout << "\n\nNEW-----------" << std::endl;
		for(auto y(0); y < num_tiles_y; ++y)
		{
			for(auto x(0); x < num_tiles_x; ++x)	
			{
				std::cout << std::setw(2) << std::setfill('0') << new_vec[y * num_tiles_x + x].index << " ";
			}
			std::cout << std::endl;
		}
		
		// create new drawarea
		auto copy_img(m_drawarea.copy(0, 0, m_num_tiles_x * 64, m_num_tiles_y * 64));
		m_drawarea = {num_tiles_x * 64, num_tiles_y * 64, QImage::Format_ARGB32};
		
		// copy all new stuff
		m_num_tiles_x = num_tiles_x;
		m_num_tiles_y = num_tiles_y;
		m_tiles = new_vec;
		
		// redraw old stuff
		this->clear_all();
		QPainter p{&m_drawarea};
		p.drawImage(QPoint{0, 0}, copy_img);
	}
	
	void layer::set_position(const QPointF& pos) noexcept
	{m_position = pos;}
	
	void layer::set_position_x(qreal x) noexcept
	{m_position.setX(x);}

	void layer::set_position_y(qreal y) noexcept
	{m_position.setY(y);}
	
	void layer::set_name(const std::string& name) noexcept
	{m_name = name;}
	
	void layer::set_image(const QImage* img, const std::string& name) noexcept
	{
		m_image = img;
		m_image_name = name;
		this->on_image_change();
	}
	
	
	std::vector<tile> layer::tiles_from_to(const QRect& rect, bool self) const
	{
		auto num_tiles_x(rect.width() / 64), num_tiles_y(rect.height() / 64);
		auto start(constants::index_from_coords(rect.topLeft())), end(constants::index_from_coords(rect.bottomRight()));
		std::vector<tile> result(num_tiles_x * num_tiles_y);
		
		for(auto y(0); y < rect.height() / 64; ++y)
			for(auto x(start); x < rect.width() / 64 + start; ++x)				
				result[y* num_tiles_x+ (x-start)] = self ? m_tiles[y * m_num_tiles_x +x] : tile{y * m_num_tiles_x +x, 0};		
		
		return result;
	}
	
	
	void layer::clear(const QPoint& from, const QPoint& to)
	{
		for(auto y(from.y()); y < to.y(); ++y)
			for(auto x(from.x()); x < to.x(); ++x)
				if(y < m_drawarea.height() &&  x < m_drawarea.width())
					m_drawarea.setPixel(x, y, 0);
	}
	
	void layer::clear_all()
	{this->clear({0, 0}, {m_num_tiles_x * 64, m_num_tiles_y * 64});}
	
	void layer::redraw()
	{
		if(m_image == nullptr)
			return;
		
		QPainter p{&m_drawarea};

		for(auto y(0); y < m_num_tiles_y; ++y)
			for(auto x(0); x < m_num_tiles_x; ++x)
			{
				auto index(m_tiles[y*m_num_tiles_x+x].index);
				if(index == 0)
					continue;
				
				auto coords(constants::coords_from_tileindex(index));
				p.drawImage(x*64, y*64, *m_image, coords.x(), coords.y(), 64, 64);
			}
	}
	
	void layer::on_image_change()
	{
		if(m_image == nullptr)
			return;
		
		QPainter p{&m_drawarea};
		for(auto y(0); y < m_num_tiles_y; ++y)
			for(auto x(0); x < m_num_tiles_x; ++x)
			{
				auto& tile(m_tiles[y * m_num_tiles_x + x]);
				if(tile.index == 0)
					continue;
				
				auto coords(constants::coords_from_tileindex(tile.index));
				this->clear({x * 64, y * 64}, {x * 2 * 64, x * 2 * 64});
				p.drawImage(x * 64, y * 64, *m_image, coords.x(), coords.y(), 64, 64);
			}
	}
}

