#include <string>
#include <SDL.h>
#include "lua.h"

class Engine {

public:

	SDL_Window *window;
	SDL_GLContext glContext;
	Lua *lua;

	int width = 1280;
	int height = 720;
	double viewportScale = 1;
	bool fullscreen = false;
	std::string title;
	bool limitFrames = true;
	static int mousex;
	static int mousey;
	static int fps;
	static int tps;

	std::string luaRender = "render";
	std::string luaTick = "tick";
	std::string luaKeyDown = "keyDown";
	std::string luaKeyUp = "keyUp";
	std::string luaMouseDown = "mouseDown";

	Engine();
	void run();

	static int getMousex(lua_State* l);
	static int getMousey(lua_State* l);
	static int getFrames(lua_State* l);
	static int getTicks(lua_State* l);

};