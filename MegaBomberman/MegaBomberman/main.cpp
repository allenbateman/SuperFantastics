#include <sdl.h>
#include <iostream>

int main(int argc, char* args[]) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Error" << std::endl;
	}

	return 0;
}