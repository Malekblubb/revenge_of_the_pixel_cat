//
// Copyright (c) 2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef PC_CORE_INPUT_HPP
#define PC_CORE_INPUT_HPP

#include "engine_component.hpp"
#include <pc/common.hpp>

#include <mlk/tools/bitset.h>

namespace pc {
	
	// TODO: Implement onKeys in a nice way
	class Input : public EngineComponent {
		mlk::bitset<Key, Key::KeyCount> mKeys;
		mlk::bitset<Button, Button::ButtonCount> mButtons;
		Vec2f mMousePosition{0.f, 0.f};
		
	public:
		mlk::event_delegates<Key> onKey;
		mlk::event_delegates<Button, Vec2f> onButton;
		mlk::event_delegates<MouseWheel, Vec2f> onWheel;
		
		void update(const Vec2f& mousePosition) {
			mMousePosition = mousePosition;
		}
		
		void keyPressed(Key key) { mKeys |= key; onKey[key](); }
		void keyReleased(Key key) { mKeys.remove(key); }
		
		void mousePressed(Button button) { mButtons |= button; onButton[button](mMousePosition); }
		void mouseReleased(Button button) { mButtons.remove(button); }
		
		void mouseScrolled(int delta) {
			delta < 0 ? onWheel[MouseWheel::down](mMousePosition) : onWheel[MouseWheel::up](mMousePosition);
		}
	};
	
}


#endif // PC_CORE_INPUT_HPP 
