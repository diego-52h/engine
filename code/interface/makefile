STD = -std=c++20

#Directories
interfaceOutput = ../../output/interface/
interfaceHeader = header/
interfaceSource = source/

#Interface files
Keyboard.o = $(interfaceOutput)Keyboard.o
Keyboard.h = $(interfaceHeader)Keyboard.h
Keyboard.c = $(interfaceSource)Keyboard.cpp

Mouse.o = $(interfaceOutput)Mouse.o
Mouse.h = $(interfaceHeader)Mouse.h
Mouse.c = $(interfaceSource)Mouse.cpp

Timer.o = $(interfaceOutput)Timer.o
Timer.h = $(interfaceHeader)Timer.h
Timer.c = $(interfaceSource)Timer.cpp

Window.o = $(interfaceOutput)Window.o
Window.h = $(interfaceHeader)Window.h
Window.c = $(interfaceSource)Window.cpp

#Compile commands
compileLibs = -I$(interfaceHeader) -I$(interfaceSource)
compileFile = g++ $(STD) $(compileLibs) -c -o

all: $(Window.o)

#Interface
$(Keyboard.o): $(Keyboard.h) $(Keyboard.c)
	$(compileFile) $(Keyboard.o) $(Keyboard.c)

$(Mouse.o): $(Mouse.h) $(Mouse.c)
	$(compileFile) $(Mouse.o) $(Mouse.c)

$(Timer.o): $(Timer.h) $(Timer.c)
	$(compileFile) $(Timer.o) $(Timer.c)

$(Window.o): $(Window.h) $(Window.c) $(Keyboard.o) $(Mouse.o) $(Timer.o)
	$(compileFile) $(Window.o) $(Window.c)