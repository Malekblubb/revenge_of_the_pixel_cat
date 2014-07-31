//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pce/graphics_manager.hpp>

#include <mlk/containers/container_utl.h>

#include <QBuffer>
#include <QByteArray>


namespace pce
{
	graphics_manager::graphics_manager(const std::string& load_path) :
		m_dir{load_path}
	{this->init();}
	
	void graphics_manager::init()
	{
		for(const auto& a : m_dir.get_content<true>())
		{
			m_images.emplace(a.name, QImage{a.path.c_str()});
		}
	}
	
	mlk::data_packet graphics_manager::image_data(const std::string& name) const
	{
		if(!mlk::cnt::exists_map_first(name, m_images))
			return {};
		
		QByteArray ba;
		QBuffer buf{&ba};
		buf.open(QIODevice::WriteOnly);
		m_images.at(name).save(&buf, "PNG");
		buf.close();
		return {ba.begin(), ba.end()};
	}
}
