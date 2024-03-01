#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <map>
#include <set>

#include <SDL2/SDL.h>

enum class Key
{
	KEY_0, KEY_1, KEY_2, KEY_3, KEY_4,
	KEY_5, KEY_6, KEY_7, KEY_8, KEY_9,
	
	KEY_A, KEY_B, KEY_C, KEY_D, KEY_E,
	KEY_F, KEY_G, KEY_H, KEY_I, KEY_J,
	KEY_K, KEY_L, KEY_M, KEY_N, KEY_O,
	KEY_P, KEY_Q, KEY_R, KEY_S, KEY_T,
	KEY_U, KEY_V, KEY_W, KEY_X, KEY_Y,
	KEY_Z,
	
	KEY_TAB, KEY_SPACE,
	
	KEY_ARROW_U, KEY_ARROW_D,
	KEY_ARROW_L, KEY_ARROW_R,
	
	KEY_ALT_L, KEY_CTRL_L, KEY_SHIFT_L,
	KEY_ALT_R, KEY_CTRL_R, KEY_SHIFT_R,
};

class Keyboard
{
	public:
		Keyboard();
		~Keyboard();
		
		void update(SDL_Event& event);
		
		const std::set<Key>& getPressedKeys() const;
		const std::set<Key>& getDroppedKeys() const;
	
	protected:
		std::set<Key> pressedKeys;
		std::set<Key> droppedKeys;
		
		static const std::map<SDL_Scancode, Key> scancodeToKey;
};

#endif