//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCSHARED_LEVEL_HEADER_HPP
#define PCSHARED_LEVEL_HEADER_HPP


namespace pce
{
	struct level_header
	{
		char ident[4];
		int version;
		int levelfile_begin;
		int images_begin;
	};
}


#endif // PCSHARED_LEVEL_HEADER_HPP
