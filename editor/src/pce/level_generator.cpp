//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
// 

#include "ui_main_window.h"
#include <pce/constants.hpp>
#include <pce/graphics_manager.hpp>
#include <pce/layer_manager.hpp>
#include <pce/level_generator.hpp>

#include <mlk/jsoncpp_utils/json_array.h>

#include <jsoncpp/json/json.h>


namespace pce
{
	level_generator::level_generator() :
		m_error{false}
	{ }
	
	
	bool level_generator::generate()
	{
		this->generate_json();
		if(m_error)
			return false;
		
		this->create_package();
		if(m_error)
			return false;
		
		return true;
	}
	
	
	void level_generator::generate_json()
	{		
		Json::Value root, inforoot;
		auto& lvroot(root["pixelcat_level"]);
		auto& infroot(inforoot["pixelcat_levelinfo"]);
		
		
		// level infos
		lvroot["_name"] = m_ui->le_levelname->text().toStdString();
		lvroot["_author"] = m_ui->le_levelauthor->text().toStdString();
		lvroot["_version"] = constants::level_version_string();
		
		// layers
		mlk::json::array j_layers;
		
		auto image_index(0);
		auto* layerlist(m_ui->lw_layers);
		for(auto i(layerlist->count() - 1); i != -1; --i, ++image_index)
		{
			auto* layer(m_ui->w_edit_area->layermgr()->from_rowindex(i));
			if(layer == nullptr)
				continue;
			
			// do data stuff
			auto data(m_gmgr->image_data(layer->image_name()));
			mlk::cnt::append(layer->image_name(), m_images);
			m_images += data;
			
			// do json stuff
			infroot[layer->image_name()] = static_cast<int>(data.size());
			
			// create new layer
			Json::Value j_layer;
			j_layer["_name"] = layer->name();
			j_layer["_width"] = layer->num_tiles_x();
			j_layer["_height"] = layer->num_tiles_y();
			j_layer["_pos_x"] = layer->position().x();
			j_layer["_pos_y"] = layer->position().y();
			j_layer["_img_name"] = layer->image_name();
			
			// create new tiles array
			mlk::json::array j_tiles;
			
			
			for(const auto& tile : layer->tiles())
			{
				// fill the tiles array
				mlk::json::array j_tile;
				j_tile.append(tile.index);
				j_tile.append(tile.flags);
				j_tile.append(tile.rotation);
				    
				// append generated tile to layer array
				j_tiles.append(j_tile);
			}
			
			// append generated layer to layers array
			j_layer["tiles"] = j_tiles;
			j_layers.append(j_layer);
		}
		
		// add all layers to file
		lvroot["layers"] = j_layers;
		
		Json::StyledWriter infowriter, levelwriter;
		auto infofile(infowriter.write(inforoot));
		auto levelfile(levelwriter.write(root));
		
		MD(infofile);
	}
	
	void level_generator::create_package()
	{
		
	}
}
