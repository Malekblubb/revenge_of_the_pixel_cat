//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_CONSTANTS_HPP
#define PCE_CONSTANTS_HPP


#include <string>

#include <QImage>
#include <QPoint>


namespace pce
{
	namespace constants
	{
		inline const auto& graphics_path()
		{
			static std::string s{"graphics"};
			return s;
		}
		
		inline const auto& level_version_string()
		{
			static std::string s{"1"};
			return s;
		}
		
		inline int default_layersize()
		{return 16;}
		
		inline QPoint coords_from_tileindex(int index, int tile_size = 64)
		{return {(index % 16) * tile_size, (index /16) * tile_size};}
		
		inline int index_from_coords(const QPoint& coords, int num_tiles_x = 16, int tile_size = 64)
		{return ((coords.y() / tile_size) * num_tiles_x) + (coords.x() / tile_size);}
		
		inline void clear_image_pixels(QImage& img, const QPoint& from = {0, 0}, const QPoint& to = {0, 0})
		{
			auto toc(to);
			if(toc == QPoint{0, 0})
				toc = {img.width(), img.height()};
			
			for(auto y(from.y()); y < toc.y(); ++y)
				for(auto x(from.x()); x < toc.x(); ++x)
					if(y < img.height() && y > 0 &&  x < img.width() && x > 0)
						img.setPixel(x, y, 0);
		}
	}
}


#endif // PCE_CONSTANTS_HPP 
