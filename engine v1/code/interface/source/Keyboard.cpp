#include "Keyboard.h"

const std::map<SDL_Scancode, Key> Keyboard::scancodeToKey = {
	{SDL_SCANCODE_0, Key::KEY_0}, {SDL_SCANCODE_1, Key::KEY_1}, {SDL_SCANCODE_2, Key::KEY_2}, {SDL_SCANCODE_3, Key::KEY_3}, {SDL_SCANCODE_4, Key::KEY_4},
	{SDL_SCANCODE_5, Key::KEY_5}, {SDL_SCANCODE_6, Key::KEY_6}, {SDL_SCANCODE_7, Key::KEY_7}, {SDL_SCANCODE_8, Key::KEY_8}, {SDL_SCANCODE_9, Key::KEY_9},
	
	{SDL_SCANCODE_A, Key::KEY_A}, {SDL_SCANCODE_B, Key::KEY_B}, {SDL_SCANCODE_C, Key::KEY_C}, {SDL_SCANCODE_D, Key::KEY_D}, {SDL_SCANCODE_E, Key::KEY_E},
	{SDL_SCANCODE_F, Key::KEY_F}, {SDL_SCANCODE_G, Key::KEY_G}, {SDL_SCANCODE_H, Key::KEY_H}, {SDL_SCANCODE_I, Key::KEY_I}, {SDL_SCANCODE_J, Key::KEY_J},
	{SDL_SCANCODE_K, Key::KEY_K}, {SDL_SCANCODE_L, Key::KEY_L}, {SDL_SCANCODE_M, Key::KEY_M}, {SDL_SCANCODE_N, Key::KEY_N}, {SDL_SCANCODE_O, Key::KEY_O},
	{SDL_SCANCODE_P, Key::KEY_P}, {SDL_SCANCODE_Q, Key::KEY_Q}, {SDL_SCANCODE_R, Key::KEY_R}, {SDL_SCANCODE_S, Key::KEY_S}, {SDL_SCANCODE_T, Key::KEY_T},
	{SDL_SCANCODE_U, Key::KEY_U}, {SDL_SCANCODE_V, Key::KEY_V}, {SDL_SCANCODE_W, Key::KEY_W}, {SDL_SCANCODE_X, Key::KEY_X}, {SDL_SCANCODE_Y, Key::KEY_Y},
	{SDL_SCANCODE_Z, Key::KEY_Z},
	
	{SDL_SCANCODE_TAB, Key::KEY_TAB}, {SDL_SCANCODE_SPACE, Key::KEY_SPACE},
	
	{SDL_SCANCODE_UP, Key::KEY_ARROW_U}, {SDL_SCANCODE_DOWN, Key::KEY_ARROW_D},
	{SDL_SCANCODE_LEFT, Key::KEY_ARROW_L}, {SDL_SCANCODE_RIGHT, Key::KEY_ARROW_R},
	
	{SDL_SCANCODE_LALT, Key::KEY_ALT_L}, {SDL_SCANCODE_LCTRL, Key::KEY_CTRL_L}, {SDL_SCANCODE_LSHIFT, Key::KEY_SHIFT_L},
	{SDL_SCANCODE_RALT, Key::KEY_ALT_R}, {SDL_SCANCODE_RCTRL, Key::KEY_CTRL_R}, {SDL_SCANCODE_RSHIFT, Key::KEY_SHIFT_R},
};

Keyboard::Keyboard()
{
}

Keyboard::~Keyboard()
{
}

void Keyboard::update(SDL_Event& event)
{
	this -> droppedKeys.clear();
	
	switch(event.type)
	{
		case SDL_KEYUP:
		{
			auto it = Keyboard::scancodeToKey.find(event.key.keysym.scancode);
			
			if(it != Keyboard::scancodeToKey.end())
			{
				this -> pressedKeys.erase((*it).second);
				this -> droppedKeys.insert((*it).second);
			}
		} break;
		
		case SDL_KEYDOWN:
		{
			auto it = Keyboard::scancodeToKey.find(event.key.keysym.scancode);
			
			if(it != Keyboard::scancodeToKey.end())
				this -> pressedKeys.insert((*it).second);
		} break;
	}
}

const std::set<Key>& Keyboard::getPressedKeys() const
{
	return this -> pressedKeys;
}

const std::set<Key>& Keyboard::getDroppedKeys() const
{
	return this -> droppedKeys;
}