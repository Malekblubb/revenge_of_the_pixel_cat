//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_CORE_GAME_UPDATER_HPP
#define PC_CORE_GAME_UPDATER_HPP

#include "engine_component.hpp"
#include <pc/common.hpp>

#include <mlk/time/time_utl.h>

namespace pc {
	
	class GameUpdater : public EngineComponent {
		static constexpr float mStep{1.f};
		float mCurrentCut{0.f}, mNextCut{1.f}, mFrameduration{0.f};
		mlk::hrs_time_pnt mLastUpdate{mlk::tm::time_pnt()};
		
		Game* mGame{nullptr};
		
	public:		
		virtual void engineInitFinished() override;
		
		void start() noexcept;
		void end() noexcept;
		
		void runUpdate();
		void runRender();
		
		float fps() const noexcept { return 1.f / (mFrameduration / 1000.f); }
		float frameduration() const noexcept { return mFrameduration; }
		
	private:
		
	};
	
}


#endif // PC_CORE_GAME_UPDATER_HPP 
