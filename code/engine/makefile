STD = -std=c++20

#Directories
gameOutput = ../../output/engine/game/
gameHeader = game/header/
gameSource = game/source/

graphicsOutput = ../../output/engine/graphics/
graphicsHeader = graphics/header/
graphicsSource = graphics/source/

mathOutput = ../../output/engine/math/
mathHeader = math/header/
mathSource = math/source/

physicsOutput = ../../output/engine/physics/
physicsHeader = physics/header/
physicsSource = physics/source/

interfaceOutput = ../../output/interface/
interfaceHeader = ../interface/header/
interfaceSource = ../interface/source/

#Engine game files
GameEngine.o = $(gameOutput)GameEngine.o
GameEngine.h = $(gameHeader)GameEngine.h
GameEngine.c = $(gameSource)GameEngine.cpp

GameObject.o = $(gameOutput)GameObject.o
GameObject.h = $(gameHeader)GameObject.h
GameObject.c = $(gameSource)GameObject.cpp

World.o = $(gameOutput)World.o
World.h = $(gameHeader)World.h
World.c = $(gameSource)World.cpp

#Engine graphics files
Camera.o = $(graphicsOutput)Camera.o
Camera.h = $(graphicsHeader)Camera.h
Camera.c = $(graphicsSource)Camera.cpp

GraphicsEngine.o = $(graphicsOutput)GraphicsEngine.o
GraphicsEngine.h = $(graphicsHeader)GraphicsEngine.h
GraphicsEngine.c = $(graphicsSource)GraphicsEngine.cpp

GraphicsObject.o = $(graphicsOutput)GraphicsObject.o
GraphicsObject.h = $(graphicsHeader)GraphicsObject.h
GraphicsObject.c = $(graphicsSource)GraphicsObject.cpp

#Engine math files
Math.h = $(mathHeader)Math.h

Matrix2.o = $(mathOutput)Matrix2.o
Matrix2.h = $(mathHeader)Matrix2.h
Matrix2.c = $(mathSource)Matrix2.cpp

Matrix3.o = $(mathOutput)Matrix3.o
Matrix3.h = $(mathHeader)Matrix3.h
Matrix3.c = $(mathSource)Matrix3.cpp

Vector2.o = $(mathOutput)Vector2.o
Vector2.h = $(mathHeader)Vector2.h
Vector2.c = $(mathSource)Vector2.cpp

#Engine physics files
BoxVolume.o = $(physicsOutput)BoxVolume.o
BoxVolume.h = $(physicsHeader)BoxVolume.h
BoxVolume.c = $(physicsSource)BoxVolume.cpp

CircleVolume.o = $(physicsOutput)CircleVolume.o
CircleVolume.h = $(physicsHeader)CircleVolume.h
CircleVolume.c = $(physicsSource)CircleVolume.cpp

CollisionDetection.o = $(physicsOutput)CollisionDetection.o
CollisionDetection.h = $(physicsHeader)CollisionDetection.h
CollisionDetection.c = $(physicsSource)CollisionDetection.cpp

CollisionVolume.o = $(physicsOutput)CollisionVolume.o
CollisionVolume.h = $(physicsHeader)CollisionVolume.h
CollisionVolume.c = $(physicsSource)CollisionVolume.cpp

GeometryUtil.o = $(physicsOutput)GeometryUtil.o
GeometryUtil.h = $(physicsHeader)GeometryUtil.h
GeometryUtil.c = $(physicsSource)GeometryUtil.cpp

Hull.o = $(physicsOutput)Hull.o
Hull.h = $(physicsHeader)Hull.h
Hull.c = $(physicsSource)Hull.cpp

Manifold.o = $(physicsOutput)Manifold.o
Manifold.h = $(physicsHeader)Manifold.h
Manifold.c = $(physicsSource)Manifold.cpp

PhysicsObject.o = $(physicsOutput)PhysicsObject.o
PhysicsObject.h = $(physicsHeader)PhysicsObject.h
PhysicsObject.c = $(physicsSource)PhysicsObject.cpp

PhysicsEngine.o = $(physicsOutput)PhysicsEngine.o
PhysicsEngine.h = $(physicsHeader)PhysicsEngine.h
PhysicsEngine.c = $(physicsSource)PhysicsEngine.cpp

Transform.o = $(physicsOutput)Transform.o
Transform.h = $(physicsHeader)Transform.h
Transform.c = $(physicsSource)Transform.cpp

#Interface files
Keyboard.o = $(interfaceOutput)Keyboard.o
Mouse.o = $(interfaceOutput)Mouse.o
Timer.o = $(interfaceOutput)Timer.o
Window.o = $(interfaceOutput)Window.o

#Compile commands
compileLibs = -I$(gameHeader) -I$(gameSource) -I$(graphicsHeader) -I$(graphicsSource) -I$(mathHeader) -I$(mathSource) -I$(physicsHeader) -I$(physicsSource) -I$(interfaceHeader) -I$(interfaceSource)
compileFile = g++ $(STD) $(compileLibs) -c -o

all: Interface $(GameEngine.o) $(BoxVolume.o) $(CircleVolume.o)

#Engine game
$(GameEngine.o): $(GameEngine.h) $(GameEngine.c) $(GraphicsEngine.o) $(PhysicsEngine.o) $(Window.o)
	$(compileFile) $(GameEngine.o) $(GameEngine.c)

$(GameObject.o): $(GameObject.h) $(GameObject.c) $(GraphicsObject.o) $(PhysicsObject.o) $(Transform.o)
	$(compileFile) $(GameObject.o) $(GameObject.c)

$(World.o): $(World.h) $(World.c) $(GameObject.o)
	$(compileFile) $(World.o) $(World.c)

#Engine graphics
$(Camera.o): $(Camera.h) $(Camera.c)
	$(compileFile) $(Camera.o) $(Camera.c)

$(GraphicsEngine.o): $(GraphicsEngine.h) $(GraphicsEngine.c) $(GameObject.o) $(World.o) $(Camera.o) $(GraphicsObject.o) $(Math.h) $(Transform.o)
	$(compileFile) $(GraphicsEngine.o) $(GraphicsEngine.c)

$(GraphicsObject.o): $(GraphicsObject.h) $(GraphicsObject.c) $(Vector2.o) $(Transform.o)
	$(compileFile) $(GraphicsObject.o) $(GraphicsObject.c)

#Engine math
$(Matrix2.o): $(Matrix2.h) $(Matrix2.c) $(Vector2.o)
	$(compileFile) $(Matrix2.o) $(Matrix2.c)

$(Matrix3.o): $(Matrix3.h) $(Matrix3.c) $(Matrix2.h) $(Vector2.o)
	$(compileFile) $(Matrix3.o) $(Matrix3.c)

$(Vector2.o): $(Vector2.h) $(Vector2.c)
	$(compileFile) $(Vector2.o) $(Vector2.c)

#Engine physics
$(BoxVolume.o): $(BoxVolume.h) $(BoxVolume.c) $(Matrix2.o) $(Matrix3.o) $(Vector2.o) $(CollisionVolume.o) $(GeometryUtil.o) $(Hull.o) $(Transform.o)
	$(compileFile) $(BoxVolume.o) $(BoxVolume.c)

$(CircleVolume.o): $(CircleVolume.h) $(CircleVolume.c) $(Vector2.o) $(CollisionVolume.o) $(GeometryUtil.o) $(Transform.o)
	$(compileFile) $(CircleVolume.o) $(CircleVolume.c)

$(CollisionDetection.o): $(CollisionDetection.h) $(CollisionDetection.c) $(Vector2.o) $(CollisionVolume.o) $(PhysicsObject.o)
	$(compileFile) $(CollisionDetection.o) $(CollisionDetection.c)

$(CollisionVolume.o): $(CollisionVolume.h) $(CollisionVolume.c) $(Vector2.o) $(GeometryUtil.o) $(Transform.o)
	$(compileFile) $(CollisionVolume.o) $(CollisionVolume.c)

$(GeometryUtil.o): $(GeometryUtil.h) $(GeometryUtil.c) $(Vector2.o)
	$(compileFile) $(GeometryUtil.o) $(GeometryUtil.c)

$(Hull.o): $(Hull.h) $(Hull.c) $(Vector2.o)
	$(compileFile) $(Hull.o) $(Hull.c)

$(Manifold.o): $(Manifold.h) $(Manifold.c) $(Vector2.o) $(CollisionDetection.o) $(CollisionVolume.o) $(GeometryUtil.o) $(PhysicsObject.o) $(Transform.o)
	$(compileFile) $(Manifold.o) $(Manifold.c)

$(PhysicsEngine.o): $(PhysicsEngine.h) $(PhysicsEngine.c) $(GameObject.o) $(GameWorld.o) $(Vector2.o) $(CollisionDetection.o) $(Manifold.o) $(PhysicsObject.o)
	$(compileFile) $(PhysicsEngine.o) $(PhysicsEngine.c)

$(PhysicsObject.o): $(PhysicsObject.h) $(PhysicsObject.c) $(Vector2.o) $(CollisionVolume.o) $(Transform.o)
	$(compileFile) $(PhysicsObject.o) $(PhysicsObject.c)

$(Transform.o): $(Transform.h) $(Transform.c) $(Matrix2.o) $(Matrix3.o) $(Vector2.o)
	$(compileFile) $(Transform.o) $(Transform.c)

#Interface
Interface:
	mingw32-make -C ../interface/