#ifndef LUA_H
#define LUA_H

#include <string>
#include <lua.hpp>

class Lua {

public:

	lua_State* l;
	bool error;

	Lua();
	void loadSettings(int &width, int &height, double &viewportScale, bool &fullscreen, std::string &title, bool &limitFrames);

	bool appVar(std::string var);
	void appSetVar(std::string var, int value);
	void appFunc(std::string func);
	void appFunc(std::string func, int value);

	void registerTable(std::string tableName, const luaL_reg* functions);
	void registerTables();

};

#endif