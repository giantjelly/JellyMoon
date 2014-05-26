/*#include <lua.hpp>
#include "video.h"
#include "lib.h"
#include "videoLua.h"

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

	int texture = lua_tonumber(l, 1);
	int x = lua_tonumber(l, 2);
	int y = lua_tonumber(l, 3);
	int width = lua_tonumber(l, 4);
	int height = lua_tonumber(l, 5);

	videoRenderSprite(texture, x, y, width, height);

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
}*/