all:
	g++ -I./include -I./include/SDL2 -I./include/headers  ./glad/src/glad.c -I./glad/include -o Zi.exe  *.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -mwindows
