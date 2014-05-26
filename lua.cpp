/*#include "lib.h"
#include <lua.hpp>
#include "videoLua.h"
#include "lua.h"
#include "globals.h"

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
		}
	};

	registerTable("video", luaVideo);
	registerTable("input", luaInput);
}*/