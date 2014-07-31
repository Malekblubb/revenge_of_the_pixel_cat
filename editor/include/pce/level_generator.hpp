//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PCE_LEVEL_GENERATOR_HPP
#define PCE_LEVEL_GENERATOR_HPP


#include <mlk/types/types.h>

#include <vector>


namespace Ui
{class main_window;}

namespace pce
{
	class level_generator
	{
		bool m_error;
		mlk::data_packet m_result;
		mlk::data_packet m_images;
		
		Ui::main_window* m_ui;
		class graphics_manager* m_gmgr;
		
	public:
		level_generator();
		
		bool generate();
		
		void set_ui(Ui::main_window* ui) noexcept
		{m_ui = ui;}
		
		void set_gmgr(class graphics_manager* gmgr) noexcept
		{m_gmgr = gmgr;}
		
		const auto& get() const noexcept
		{return m_result;}
		
	private:
		void generate_json();
		void create_package();
	};
}


#endif // PCE_LEVEL_GENERATOR_HPP
