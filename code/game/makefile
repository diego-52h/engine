STD = -std=c++20

#Directories
engineGameOutput = ../../output/engine/game/
engineGameHeader = ../engine/game/header/
engineGameSource = ../engine/game/source/

engineGraphicsOutput = ../../output/engine/graphics/
engineGraphicsHeader = ../engine/graphics/header/
engineGraphicsSource = ../engine/graphics/source/

engineMathOutput = ../../output/engine/math/
engineMathHeader = ../engine/math/header/
engineMathSource = ../engine/math/source/

enginePhysicsOutput = ../../output/engine/physics/
enginePhysicsHeader = ../engine/physics/header/
enginePhysicsSource = ../engine/physics/source/

gameLevelOutput = ../../output/game/level/
gameLevelHeader = level/header/
gameLevelSource = level/source/

gameObjectOutput = ../../output/game/object/
gameObjectHeader = object/header/
gameObjectSource = object/source/

gameUtilOutput = ../../output/game/util/
gameUtilHeader = util/header/
gameUtilSource = util/source/

interfaceOutput = ../../output/interface/
interfaceHeader = ../interface/header/
interfaceSource = ../interface/source/

#Main file
Game.c = Game.cpp

#Game level files
Level.o = $(gameLevelOutput)Level.o
Level.h = $(gameLevelHeader)Level.h
Level.c = $(gameLevelSource)Level.cpp

#Game object files
Breakable.o = $(gameObjectOutput)Breakable.o
Breakable.h = $(gameObjectHeader)Breakable.h
Breakable.c = $(gameObjectSource)Breakable.cpp

Character.o = $(gameObjectOutput)Character.o
Character.h = $(gameObjectHeader)Character.h
Character.c = $(gameObjectSource)Character.cpp

Object.o = $(gameObjectOutput)Object.o
Object.h = $(gameObjectHeader)Object.h
Object.c = $(gameObjectSource)Object.cpp

Player.o = $(gameObjectOutput)Player.o
Player.h = $(gameObjectHeader)Player.h
Player.c = $(gameObjectHeader)Player.cpp

Weapon.o = $(gameObjectOutput)Weapon.o
Weapon.h = $(gameObjectHeader)Weapon.h
Weapon.c = $(gameObjectSource)Weapon.cpp

#Game util files
TinyXML2.o = $(gameUtilOutput)tinyxml2.o
TinyXML2.h = $(gameUtilHeader)tinyxml2.h
TinyXML2.c = $(gameUtilSource)tinyxml2.cpp

#Engine game files
GameEngine.o = $(engineGameOutput)GameEngine.o
GameObject.o = $(engineGameOutput)GameObject.o
World.o = $(engineGameOutput)World.o

#Engine graphics files
Camera.o = $(engineGraphicsOutput)Camera.o
GraphicsEngine.o = $(engineGraphicsOutput)GraphicsEngine.o
GraphicsObject.o = $(engineGraphicsOutput)GraphicsObject.o

#Engine math files
Math.h = $(engineMathHeader)Math.h

Matrix2.o = $(engineMathOutput)Matrix2.o
Matrix3.o = $(engineMathOutput)Matrix3.o
Vector2.o = $(engineMathOutput)Vector2.o

#Engine physics files
BoxVolume.o = $(enginePhysicsOutput)BoxVolume.o
CircleVolume.o = $(enginePhysicsOutput)CircleVolume.o
CollisionDetection.o = $(enginePhysicsOutput)CollisionDetection.o
CollisionVolume.o = $(enginePhysicsOutput)CollisionVolume.o
GeometryUtil.o = $(enginePhysicsOutput)GeometryUtil.o
Hull.o = $(enginePhysicsOutput)Hull.o
Manifold.o = $(enginePhysicsOutput)Manifold.o
PhysicsObject.o = $(enginePhysicsOutput)PhysicsObject.o
PhysicsEngine.o = $(enginePhysicsOutput)PhysicsEngine.o
Transform.o = $(enginePhysicsOutput)Transform.o

#Interface files
Keyboard.o = $(interfaceOutput)Keyboard.o
Mouse.o = $(interfaceOutput)Mouse.o
Timer.o = $(interfaceOutput)Timer.o
Window.o = $(interfaceOutput)Window.o

#Compile commands
compileLibs = -Icode/ -I$(engineGameHeader) -I$(engineGameSource) -I$(engineGraphicsHeader) -I$(engineGraphicsSource) -I$(engineMathHeader) -I$(engineMathSource) -I$(enginePhysicsHeader) -I$(enginePhysicsSource) -I$(gameLevelHeader) -I$(gameLevelSource) -I$(gameObjectHeader) -I$(gameObjectSource) -I$(gameUtilHeader) -I$(gameUtilSource) -I$(interfaceHeader) -I$(interfaceSource)
compileFile = g++ $(STD) $(compileLibs) -c -o
compileGame = g++ $(STD) $(compileLibs) -o ../../output/Game $(engineGameOutput)*.o $(engineGraphicsOutput)*.o $(engineMathOutput)*.o $(enginePhysicsOutput)*.o $(gameLevelOutput)*.o $(gameObjectOutput)*.o $(gameUtilOutput)*.o $(interfaceOutput)*.o

all: Interface Engine Game

#Main file
Game: $(Game.c) $(Level.o)
	$(compileGame) $(Game.c) -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

#Game
$(Level.o): $(Level.h) $(Level.c) $(Breakable.o) $(Character.o) $(Object.o) $(TinyXML2.o) $(GameObject.o) $(World.o) $(Camera.o) $(Vector2.o) $(PhysicsObject.o) $(Keyboard.o) $(Mouse.o)
	$(compileFile) $(Level.o) $(Level.c)

$(Breakable.o): $(Breakable.h) $(Breakable.c) $(Object.o) $(TinyXML2.o) $(World.o) $(GraphicsObject.o)
	$(compileFile) $(Breakable.o) $(Breakable.c)

$(Character.o): $(Character.h) $(Character.c) $(Breakable.o) $(Weapon.o) $(TinyXML2.o) $(World.o) $(GraphicsObject.o) $(PhysicsObject.o)
	$(compileFile) $(Character.o) $(Character.c)

$(Object.o): $(Object.h) $(Object.c) $(TinyXML2.o) $(GameObject.o) $(GraphicsObject.o) $(BoxVolume.o) $(CircleVolume.o) $(CollisionVolume.o) $(PhysicsObject.o) $(Vector2.o)
	$(compileFile) $(Object.o) $(Object.c)

$(Player.o): $(Player.h) $(Player.c)
	$(compileFile) $(Player.o) $(Player.c)

$(Weapon.o): $(Weapon.h) $(Weapon.c) $(TinyXML2.o) $(World.o) $(GraphicsObject.o)
	$(compileFile) $(Weapon.o) $(Weapon.c)

#Game util
$(TinyXML2.o): $(TinyXML2.h) $(TinyXML2.c)
	$(compileFile) $(TinyXML2.o) $(TinyXML2.c)

#Interface
Interface:
	mingw32-make -C ../interface

#Engine
Engine:
	mingw32-make -C ../engine