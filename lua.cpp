#include "lua.h"

#include <iostream>
#include <lua.hpp>
#include "videoLua.h"
#include "engine.h"

Lua::Lua() {

	error = false;

	l = lua_open();
	luaL_openlibs(l);

	registerTables();

	if (luaL_dofile(l, "main.lua") != 0) error = true;
	if (lua_type(l, -1) == LUA_TSTRING) std::cout << lua_tostring(l, -1) << std::endl;

	//appSetVar("app.mouseX", 0);
	//appSetVar("app.mouseY", 0);
	std::cout << "Lua constructor called" << std::endl;
}

bool Lua::appVar(std::string var) {

	lua_getfield(l, LUA_GLOBALSINDEX, "app");
	if (lua_istable(l, -1)) {
		lua_getfield(l, -1, var.c_str());
		if (!lua_isnil(l, -1)) {
			return true;
		}
	}

	return false;
}

void Lua::appSetVar(std::string var, int value) {

	std::string str = var + " = " + std::to_string(value);

	if (!error)
	if (luaL_dostring(l, str.c_str()) != 0) {
		if (lua_type(l, -1) == LUA_TSTRING) std::cout << lua_tostring(l, -1) << std::endl;
		error = true;
	}
}

void Lua::appFunc(std::string func) {

	std::string f = func + "()";

	//if (!error)
	if (luaL_dostring(l, f.c_str()) != 0) {
		std::cout << func << " : ";
		if (lua_type(l, -1) == LUA_TSTRING) std::cout << lua_tostring(l, -1) << std::endl;
		error = true;
	}
}

void Lua::appFunc(std::string func, int value) {

	std::string f = func + "(" + std::to_string(value) + ")";

	//if (!error)
	if (luaL_dostring(l, f.c_str()) != 0) {
		std::cout << func << " : ";
		if (lua_type(l, -1) == LUA_TSTRING) std::cout << lua_tostring(l, -1) << std::endl;
		error = true;
	}
}

void Lua::loadSettings(int &width, int &height, double &viewportScale, bool &fullscreen, std::string &title, bool &limitFrames) {

	if (appVar("width")) width = lua_tonumber(l, -1);
	if (appVar("height")) height = lua_tonumber(l, -1);
	if (appVar("scale")) viewportScale = lua_tonumber(l, -1);
	if (appVar("fullscreen")) fullscreen = lua_toboolean(l, -1);

	if (appVar("title")) title = lua_tostring(l, -1);
	if (appVar("limitframes")) limitFrames = lua_toboolean(l, -1);
}

void Lua::registerTable(std::string tableName, const luaL_reg* functions) {

luaL_register(l, tableName.c_str(), functions);
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
			"renderSpriteRotated",
			luaRenderSpriteRotated
		},
		{
			"renderCircle",
			luaRenderCircle
		},
		{
			"renderElipse",
			luaRenderElipse
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
		Engine::getMousex
	},
	{
		"mousey",
		Engine::getMousey
	},
	{ NULL, NULL }
	};

	static const luaL_reg luaJellyMoon[] = {
	{
		"frames",
		Engine::getFrames
	},
	{
		"ticks",
		Engine::getTicks
	},
	{ NULL, NULL }
	};

	registerTable("video", luaVideo);
	registerTable("input", luaInput);
	registerTable("jellymoon", luaJellyMoon);
}