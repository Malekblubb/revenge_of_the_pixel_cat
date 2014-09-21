//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCSHARED_CONSTANTS_HPP 
#define PCSHARED_CONSTANTS_HPP


#include <string>


namespace pcshared
{
	inline auto level_version_int()
	{return 1;}
	
	inline const auto& level_version_string()
	{
		static std::string s{std::to_string(level_version_int())};
		return s;
	}
	
	inline const auto& level_ident()
	{
		static std::string ident{"PCEL"};
		return ident;
	}
	
	inline const auto& levelfile_json_start()
	{
		static std::string s{"pixelcat_level"};
		return s;
	}
	
	inline const auto& infofile_json_start()
	{
		static std::string s{"pixelcat_levelinfo"};
		return s;
	}
}

#endif // PCSHARED_CONSTANTS_HPP
