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
		m_tiles(width * height, {0, 0, 0.}),
		m_name{"Layer#"}
	{constants::clear_image_pixels(m_drawarea);}
	
	void layer::use_brush(const brush* b, const QPoint& target_point, bool self)
	{
		auto source_rect(b->rect());
		if(self && source_rect.contains(target_point))
			return;
		
		auto bx(0), by(0);
		for(auto sy(source_rect.y()), ty(target_point.y()); sy < source_rect.height() + source_rect.y(); sy += 64, ty += 64, ++by)
		{
			bx = 0;
			
			for(auto sx(source_rect.x()), tx(target_point.x()); sx < source_rect.width() + source_rect.x(); sx += 64, tx += 64, ++bx)
			{		
				auto target_tile(((ty / 64) * m_num_tiles_x) + (tx / 64));
				if(static_cast<mlk::st>(target_tile) >= m_tiles.size() || target_tile < 0)
				{
					mlk::lerr()["pce::layer"] << "wrong target_tile index. requested: " << target_tile << ", max: " << m_tiles.size() - 1;
					continue;
				}
				
				// copy tiles from brush
				m_tiles[target_tile] = b->tiles().at(by * source_rect.width() / 64 + bx);
			}
		}
		
		// clear old content
		constants::clear_image_pixels(m_drawarea, {target_point.x(), target_point.y()}, {target_point.x() + source_rect.width(), target_point.y() + source_rect.height()});
		
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
		if((num_tiles_x == m_num_tiles_x) && (num_tiles_y == m_num_tiles_y))
		{
			mlk::lout("pce::layer") << "set_size ignored. same size requested";
			return;
		}
		
		std::vector<tile> new_vec(num_tiles_x * num_tiles_y);
		
		// copy to new vec
		for(auto y(0); y < num_tiles_y; ++y)
		{
			for(auto x(0); x < num_tiles_x; ++x)	
			{
				if(x >= m_num_tiles_x || y >= m_num_tiles_y)
					new_vec[y * num_tiles_x + x] = {0, 0, 0};
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
	
	
	std::vector<tile> layer::tiles_in_rect(const QRect& rect, bool self) const
	{
		auto num_tiles_x(rect.width() / 64), num_tiles_y(rect.height() / 64);
		std::vector<tile> result(num_tiles_x * num_tiles_y);
		
		auto target(0);
		for(auto y(rect.y()); y < rect.bottomLeft().y(); y += 64)	
			for(auto x(rect.x()); x < rect.topRight().x(); x += 64, ++target)
				result[target] = self ? m_tiles[constants::index_from_coords({x,y}, m_num_tiles_x)] : tile{constants::index_from_coords({x,y}), 0, 0.};

		return result;
	}
	
	
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
	{this->redraw();}
}

