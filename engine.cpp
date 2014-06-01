#include "engine.h"
#include <ctime>

int Engine::mousex = 0;
int Engine::mousey = 0;
int Engine::fps = 0;
int Engine::tps = 0;

Engine::Engine() {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << SDL_GetError() << endl;
		return;
	}

	window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		cout << SDL_GetError() << endl;
		return;
	}

	glContext = SDL_GL_CreateContext(window);
	lua = new Lua();
	lua->loadSettings(width, height, viewportScale, fullscreen, title, limitFrames);
}

void Engine::run() {

	

	SDL_SetWindowTitle(window, title.c_str());
	SDL_SetWindowSize(window, width*viewportScale, height*viewportScale);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	if (fullscreen) SDL_SetWindowFullscreen(window, SDL_TRUE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	bool quit = false;
	SDL_Event e;

	glViewport(0, 0, width*viewportScale, height*viewportScale);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, height, 0, 10, -10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 1);
	if (!limitFrames) SDL_GL_SetSwapInterval(0);

	double time = clock();
	double tickTime = clock();
	int frames = 0;
	int ticks = 0;
	double msPerTick = 1000.0 / 60.0;
	double unprocessed = 0.0;

	while (!quit) {

		while (SDL_PollEvent(&e)) {

			if (e.type == SDL_QUIT) quit = true;

			if (e.type == SDL_KEYDOWN) lua->appFunc(luaKeyDown, e.key.keysym.scancode);

			if (e.type == SDL_KEYUP) lua->appFunc(luaKeyUp, e.key.keysym.scancode);

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (e.button.button == SDL_BUTTON_LEFT) lua->appFunc(luaMouseDown, 0);
				if (e.button.button == SDL_BUTTON_RIGHT) lua->appFunc(luaMouseDown, 1);
			}

			if (e.type == SDL_MOUSEMOTION) {
				mousex = e.motion.x;
				mousey = e.motion.y;
			}
		}

		if (!lua->error) {

			if (clock() - time > 1000) {
				fps = frames;
				tps = ticks;
				frames = 0;
				ticks = 0;
				time = clock();
				lua->appFunc("secondstep");
			}

			unprocessed += (clock() - tickTime) / msPerTick;
			tickTime = clock();

			while (unprocessed >= 1.0) {
				unprocessed--;
				lua->appFunc(luaTick);
				ticks++;
			}

			lua->appFunc(luaRender);
			frames++;
			SDL_GL_SwapWindow(window);
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
}

int Engine::getMousex(lua_State* l) {

	lua_pushnumber(l, mousex);
	return 1;
}

int Engine::getMousey(lua_State* l) {

	lua_pushnumber(l, mousey);
	return 1;
}

int Engine::getFrames(lua_State* l) {

	lua_pushnumber(l, fps);
	return 1;
}

int Engine::getTicks(lua_State* l) {

	lua_pushnumber(l, tps);
	return 1;
}