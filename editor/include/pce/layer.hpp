//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_LAYER_HPP
#define PCE_LAYER_HPP


#include <QImage>


namespace pce
{
	class layer
	{
		QImage m_drawarea;
		
	public:
		layer(int width, int height);
	};
}


#endif // PCE_LAYER_HPP
