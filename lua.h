#ifndef LUA_H
#define LUA_H

#include <lua.hpp>
#include "lib.h"

class Lua {

public:

	lua_State* l;
	bool error;

	Lua();
	void loadSettings(int &width, int &height, double &viewportScale, bool &fullscreen, string &title, bool &limitFrames);

	bool appVar(string var);
	void appSetVar(string var, int value);
	void appFunc(string func);
	void appFunc(string func, int value);

	void registerTable(string tableName, const luaL_reg* functions);
	void registerTables();

};

#endif