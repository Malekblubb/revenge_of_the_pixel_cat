//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#include <pce/layer.hpp>


namespace pce
{
	layer::layer(int width, int height) :
		m_drawarea{width, height, QImage::Format_ARGB32}
	{ } 
}

