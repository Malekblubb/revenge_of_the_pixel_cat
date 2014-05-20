//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_GRAPHICS_MANAGER_HPP
#define PCE_GRAPHICS_MANAGER_HPP


#include <mlk/filesystem/filesystem.h>

#include <QImage>

#include <map>


namespace pce
{
	class graphics_manager
	{
		mlk::fs::dir_handle m_dir;
		std::map<std::string, QImage> m_images;
		
	public:
		graphics_manager(const std::string& load_path);
		
		const auto& images() const noexcept
		{return m_images;}
		
	private:
		void init();
	};
}


#endif // PCE_GRAPHICS_MANAGER_HPP
