//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_LIST_WIDGET_LAYER_ITEM_HPP
#define PCE_LIST_WIDGET_LAYER_ITEM_HPP

#include <QListWidgetItem>


namespace pce
{
	class list_widget_layer_item : public QListWidgetItem
	{
		int m_index;
		
	public:
		list_widget_layer_item(int index) :
			QListWidgetItem{QString{"Layer%1"}.arg(index)},
			m_index{index}
		{ }
		
		void set_index(int index) noexcept
		{m_index = index;}
		
		int index() const noexcept
		{return m_index;}
	};
}


#endif // PCE_LIST_WIDGET_LAYER_ITEM_HPP
