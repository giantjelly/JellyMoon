using namespace std;
#include <iostream>
#include <string>

#include <glew.h>
#include <SDL.h>
#include <SDL_image.h>
#include <ctime>
#include <lua.hpp>



// GLOBAL VARIABLES

int VIEWPORTWIDTH = 1280;
int VIEWPORTHEIGHT = 720;
string TITLE = "";
int PROJECTIONWIDTH = VIEWPORTWIDTH;
int PROJECTIONHEIGHT = VIEWPORTHEIGHT;
bool FULLSCREEN = false;
int MOUSEX = 0;
int MOUSEY = 0;



// VIDEO CLASS

void videoEnableTextures(bool enable);
void videoClear();
void videoPush();
void videoPop();
void videoTranslate(double x, double y, double z);
void videoRotate(double angle);
void videoColor(double r, double g, double b, double a);
void videoRenderQuad(double left, double top, double right, double bottom);
void videoRenderSprite(GLuint texture, double offsetX, double offsetY, double offsetWidth, double offsetHeight, double x, double y, double scale);
void videoRenderCircle(double x, double y, double radius, double detailScale);
GLuint videoLoadTexture(string file);

void videoLoadIdentity();
void videoRotate(double x, double y, double angle);

void videoEnableTextures(bool enable) {

	if (enable) glEnable(GL_TEXTURE_2D);
	else glDisable(GL_TEXTURE_2D);
}

void videoClear() {

	glClear(GL_COLOR_BUFFER_BIT);
}

void videoPush() {

	glPushMatrix();
}

void videoPop() {

	glPopMatrix();
}

void videoTranslate(double x, double y, double z) {

	glTranslated(x, y, z);
}

void videoRotate(double angle) {

	glRotated(angle, 0.0, 0.0, 1.0);
}

void videoColor(double r, double g, double b, double a) {

	glColor4f(r, g, b, a);
}

void videoRenderQuad(double x, double y, double width, double height) {

	glBegin(GL_QUADS);

	glVertex3d(x, y, 0);
	glVertex3d(x + width, y, 0);
	glVertex3d(x + width, y + height, 0);
	glVertex3d(x, y + height, 0);

	glEnd();
}

void videoRenderSprite(GLuint texture, double offsetX, double offsetY, double offsetWidth, double offsetHeight, double x, double y, double scale) {

	glBindTexture(GL_TEXTURE_2D, texture);
	glEnable(GL_TEXTURE_2D);

	int tw;
	int th;
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &tw);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &th);

	double xStart = offsetX / tw;
	double xEnd = (offsetX+offsetWidth) / tw;
	double yStart = offsetY / th;
	double yEnd = (offsetY + offsetHeight) / th;
	double width = offsetWidth*scale;
	double height = offsetHeight*scale;

	glBegin(GL_QUADS);

	glTexCoord2d(xStart, yStart);
	glVertex3f(x, y, 0);

	glTexCoord2d(xEnd, yStart);
	glVertex3f(x + width, y, 0);

	glTexCoord2d(xEnd, yEnd);
	glVertex3f(x + width, y + height, 0);

	glTexCoord2d(xStart, yEnd);
	glVertex3f(x, y + height, 0);

	glEnd();
}

void videoRenderCircle(double x, double y, double radius, double detailScale) {

	int detail = 50*detailScale;

	glBegin(GL_TRIANGLE_FAN);

	for (int i = 0; i < detail; i++) {

		double rad = (((double)i/(double)detail)*360)*(3.14159 / 180.0);
		glVertex3d( x+(cos(rad)*radius), y+(sin(rad)*radius), 0 );
	}

	glEnd();
}

GLuint videoLoadTexture(string file) {

	SDL_Surface *surface = IMG_Load(file.c_str());
	if (surface == nullptr) {
		cout << "Bitmap load error: " << SDL_GetError() << endl;
		return NULL;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	int mode = GL_RGB;
	if (surface->format->BytesPerPixel == 4) mode = GL_RGBA;

	glTexImage2D(
		GL_TEXTURE_2D, 0, mode,
		surface->w, surface->h,
		0,
		mode, GL_UNSIGNED_BYTE, surface->pixels
		);

	SDL_FreeSurface(surface);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	return texture;
}

void videoLoadIdentity() {

	glLoadIdentity();
}

void videoRotate(double x, double y, double angle) {

	videoTranslate(x, y, 0);
	videoRotate(angle);
	videoTranslate(-x, -y, 0);
}



// VIDEO LUA CLASS

int luaEnableTextures(lua_State* l);
int luaClear(lua_State* l);
int luaPush(lua_State* l);
int luaPop(lua_State* l);
int luaTranslate(lua_State* l);
int luaRotate(lua_State* l);
int luaColor(lua_State* l);
int luaRenderQuad(lua_State* l);
int luaRenderSprite(lua_State* l);
int luaRenderCircle(lua_State* l);
int luaLoadTexture(lua_State* l);
int luaLoadIdentity(lua_State* l);

int luaEnableTextures(lua_State* l) {

	bool enable = lua_toboolean(l, 1);

	videoEnableTextures(enable);

	return 0;
}

int luaClear(lua_State* l) {

	videoClear();

	return 0;
}

int luaPush(lua_State* l) {

	videoPush();

	return 0;
}

int luaPop(lua_State* l) {

	videoPop();

	return 0;
}

int luaTranslate(lua_State* l) {

	double x = lua_tonumber(l, 1);
	double y = lua_tonumber(l, 2);
	double z = lua_tonumber(l, 3);

	videoTranslate(x, y, z);

	return 0;
}

int luaRotate(lua_State* l) {

	double x = lua_tonumber(l, 1);
	double y = lua_tonumber(l, 2);
	double r = lua_tonumber(l, 3);

	videoRotate(x, y, r);

	return 0;
}

int luaColor(lua_State* l) {

	double r = lua_tonumber(l, 1);
	double g = lua_tonumber(l, 2);
	double b = lua_tonumber(l, 3);
	double a = lua_tonumber(l, 4);

	videoColor(r, g, b, a);

	return 0;
}

int luaRenderQuad(lua_State* l) {

	double x = lua_tonumber(l, 1);
	double y = lua_tonumber(l, 2);
	double width = lua_tonumber(l, 3);
	double height = lua_tonumber(l, 4);

	videoRenderQuad(x, y, width, height);

	return 0;
}

int luaRenderSprite(lua_State* l) {

	// void videoRenderSprite(GLuint texture, int offsetX, int offsetY, int offsetWidth, int offsetHeight, double x, double y, double scale);

	int texture = lua_tonumber(l, 1);
	int offsetX = lua_tonumber(l, 2);
	int offsetY = lua_tonumber(l, 3);
	int offsetWidth = lua_tonumber(l, 4);
	int offsetHeight = lua_tonumber(l, 5);
	double x = lua_tonumber(l, 6);
	double y = lua_tonumber(l, 7);
	double scale = lua_tonumber(l, 8);

	videoRenderSprite(texture, offsetX, offsetY, offsetWidth, offsetHeight, x, y, scale);

	return 0;
}

int luaRenderCircle(lua_State* l) {

	double x = lua_tonumber(l, 1);
	double y = lua_tonumber(l, 2);
	double radius = lua_tonumber(l, 3);
	double detailScale = lua_tonumber(l, 4);

	videoRenderCircle(x, y, radius, detailScale);

	return 0;
}

int luaLoadTexture(lua_State* l) {

	string file = lua_tostring(l, 1);
	unsigned int number = videoLoadTexture(file);
	lua_pushnumber(l, number);

	return 1;
}

int luaLoadIdentity(lua_State* l) {

	videoLoadIdentity();

	return 0;
}



// LUA CLASS

class Lua {

public:

	lua_State* l;
	bool error;

	Lua();
	void loadSettings();

	bool appVar(string var);
	void appSetVar(string var, int value);
	void appFunc(string func);
	void appFunc(string func, int value);

	void registerTable(string tableName, const luaL_reg* functions);
	void registerTables();

};

Lua::Lua() {

	error = false;

	l = lua_open();
	luaL_openlibs(l);

	registerTables();

	if (luaL_dofile(l, "main.lua") != 0) error = true;
	if (lua_type(l, -1) == LUA_TSTRING) cout << lua_tostring(l, -1) << endl;

	loadSettings();

	appSetVar("app.mouseX", 0);
	appSetVar("app.mouseY", 0);
}

bool Lua::appVar(string var) {

	lua_getfield(l, LUA_GLOBALSINDEX, "app");
	if (lua_istable(l, -1)) {
		lua_getfield(l, -1, var.c_str());
		if (!lua_isnil(l, -1)) {
			return true;
		}
	}

	return false;
}

void Lua::appSetVar(string var, int value) {

	string str = var + " = " + to_string(value);

	if (!error)
	if (luaL_dostring(l, str.c_str()) != 0) {
		if (lua_type(l, -1) == LUA_TSTRING) cout << lua_tostring(l, -1) << endl;
		error = true;
	}
}

void Lua::appFunc(string func) {

	string f = func + "()";

	//if (!error)
	if (luaL_dostring(l, f.c_str()) != 0) {
		cout << func << " : ";
		if (lua_type(l, -1) == LUA_TSTRING) cout << lua_tostring(l, -1) << endl;
		error = true;
	}
}

void Lua::appFunc(string func, int value) {

	string f = func + "(" + to_string(value) + ")";

	//if (!error)
	if (luaL_dostring(l, f.c_str()) != 0) {
		cout << func << " : ";
		if (lua_type(l, -1) == LUA_TSTRING) cout << lua_tostring(l, -1) << endl;
		error = true;
	}
}

void Lua::loadSettings() {

	if (appVar("viewportWidth")) VIEWPORTWIDTH = lua_tonumber(l, -1);
	if (appVar("viewportHeight")) VIEWPORTHEIGHT = lua_tonumber(l, -1);
	if (appVar("projectionWidth")) PROJECTIONWIDTH = lua_tonumber(l, -1);
	if (appVar("projectionHeight")) PROJECTIONHEIGHT = lua_tonumber(l, -1);
	if (appVar("fullscreen")) FULLSCREEN = lua_toboolean(l, -1);
	if (appVar("title")) TITLE = lua_tostring(l, -1);
}

void Lua::registerTable(string tableName, const luaL_reg* functions) {

	luaL_register(l, tableName.c_str(), functions);
}

int mousex(lua_State* l) {

	lua_pushnumber(l, MOUSEX);
	return 1;
}

int mousey(lua_State* l) {

	lua_pushnumber(l, MOUSEY);
	return 1;
}

void Lua::registerTables() {

	static const luaL_reg luaVideo[] = {
		{
			"enableTextures",
			luaEnableTextures
		},
		{
			"clear",
			luaClear
		},
		{
			"push",
			luaPush
		},
		{
			"pop",
			luaPop
		},
		{
			"translate",
			luaTranslate
		},
		{
			"rotate",
			luaRotate
		},
		{
			"color",
			luaColor
		},
		{
			"renderQuad",
			luaRenderQuad
		},
		{
			"renderSprite",
			luaRenderSprite
		},
		{
			"renderCircle",
			luaRenderCircle
		},
		{
			"loadTexture",
			luaLoadTexture
		},
		{
			"loadIdentity",
			luaLoadIdentity
		},
		{ NULL, NULL }
	};

	static const luaL_reg luaInput[] = {
		{
			"mousex",
			mousex
		},
		{
			"mousey",
			mousey
		},
		{ NULL, NULL }
	};

	registerTable("video", luaVideo);
	registerTable("input", luaInput);
}



// MAIN FUNC

int main(int argc, char **argv) {

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		cout << "Init error[" << SDL_GetError() << "]" << endl;
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 720, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		cout << "Window error[" << SDL_GetError() << "]" << endl;
		return 1;
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(window);

	Lua lua = Lua();

	SDL_SetWindowTitle(window, TITLE.c_str());
	SDL_SetWindowSize(window, VIEWPORTWIDTH, VIEWPORTHEIGHT);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	if (FULLSCREEN) SDL_SetWindowFullscreen(window, SDL_TRUE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	bool quit = false;
	SDL_Event e;

	//TEST
	/*glewInit();

	double verticies[] = {
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0
	};

	GLuint buffer = 0;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);*/
	//END TEST

	glViewport(0, 0, VIEWPORTWIDTH, VIEWPORTHEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, PROJECTIONWIDTH, PROJECTIONHEIGHT, 0, 10, -10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 1);
	//SDL_GL_SetSwapInterval(0);

	double time = clock();
	int frames = 0;

	while (!quit) {

		//bool resetLua = false;

		while (SDL_PollEvent(&e) /*&& !resetLua*/) {

			if (e.type == SDL_QUIT) quit = true;

			if (e.type == SDL_KEYDOWN) lua.appFunc("keyDown", e.key.keysym.scancode);

			if (e.type == SDL_KEYUP) lua.appFunc("keyUp", e.key.keysym.scancode);

			if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (e.button.button == SDL_BUTTON_LEFT) lua.appFunc("mouseDown", 0);
				if (e.button.button == SDL_BUTTON_RIGHT) lua.appFunc("mouseDown", 1);
			}

			if (e.type == SDL_MOUSEMOTION) {
				MOUSEX = e.motion.x;
				MOUSEY = e.motion.y;
			}

			/*if (e.type == SDL_KEYDOWN) if (e.key.keysym.sym == SDLK_F5) {
				lua = Lua();
				resetLua = true;
			}*/
		}

		//if (resetLua) continue;

		if (!lua.error) {
			lua.appFunc("render");
			lua.appFunc("tick");

			SDL_GL_SwapWindow(window);
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 1;
}