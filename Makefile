FILES=build/emulator.o build/common.o build/memory.o
INCLUDE=-Iinclude/
LIBS_LINK=-Llibraries/ -lmingw32 -lSDL2 -lSDL2main

all: $(FILES)
	gcc $(FILES) $(INCLUDE) $(LIBS_LINK) -o bin/emulator

build/emulator.o: src/emulator.c
	gcc $(INCLUDE) -g -c $< -o $@

build/common.o: src/common.c
	gcc $(INCLUDE) -g -c $< -o $@

build/memory.o: src/memory.c
	gcc $(INCLUDE) -g -c $< -o $@

clean:
	rm $(FILES)
	rm bin/emulator.exe
