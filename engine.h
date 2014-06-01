#include <SDL.h>
#include "lib.h"
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
	string title = "";
	bool limitFrames = true;
	static int mousex;
	static int mousey;
	static int fps;
	static int tps;

	string luaRender = "render";
	string luaTick = "tick";
	string luaKeyDown = "keyDown";
	string luaKeyUp = "keyUp";
	string luaMouseDown = "mouseDown";

	Engine();
	void run();

	static int getMousex(lua_State* l);
	static int getMousey(lua_State* l);
	static int getFrames(lua_State* l);
	static int getTicks(lua_State* l);

};