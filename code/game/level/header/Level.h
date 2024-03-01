#ifndef LEVEL_H
#define LEVEL_H

#include <functional>
#include <map>
#include <string>

#include "World.h"

#include "Vector2.h"

#include "Mouse.h"
#include "Keyboard.h"

#include "Character.h"

typedef std::function<void(void)> Handler;

class Level : public World
{
	public:
		Level(const std::string& path);
		~Level();
		
		void loadInput(const std::string& path);
		
		void handleInput(const Mouse& mouse) override;
		void handleInput(const Keyboard& keyboard) override;
		
		virtual void update(float dt) override;
	
	protected:
		std::string name;
		
		Character* player;
		
		std::map<std::string, Handler> handlers {
			{"moveU", [this](){this -> player -> moveU();}},
			{"moveD", [this](){this -> player -> moveD();}},
			{"moveL", [this](){this -> player -> moveL();}},
			{"moveR", [this](){this -> player -> moveR();}},
			
			{"punch", [this](){this -> player -> punch();}},
			{"shoot", [this](){this -> player -> shoot();}},
		};
		
		static std::map<std::string, Key> keys;
		
		static std::map<Key, Handler> handlePressedKey;
		static std::map<Key, Handler> handleDroppedKey;
};

#endif