#include "corepch.h"
#include "Lua.h"

namespace Vanim
{
	Lua::Lua()
	:	_luaState(nullptr)
	{
		_luaState = luaL_newstate();

		luaL_openlibs(_luaState);

		lua_setglobal(_luaState, "os");
		lua_pushnil(_luaState);
		lua_setglobal(_luaState, "io");
		lua_pushnil(_luaState);
	}

	Lua::~Lua()
	{
		lua_close(_luaState);
		_luaState = nullptr;
	}

	bool Lua::RunFile(const char* filePath) const
	{
		return CheckResult(luaL_dofile(_luaState, filePath));
	}

	bool Lua::RunCommand(const char* command) const
	{
		return CheckResult(luaL_dostring(_luaState, command));
	}

	float Lua::GetFloat(const char* variable) const
	{
		lua_getglobal(_luaState, variable);

		if (!lua_isnumber(_luaState, TOP_STACK))
		{
			VANIM_ERROR(variable << " is not a float");
			return 0.0f;
		}

		return (float)lua_tonumber(_luaState, TOP_STACK);
	}

	int32_t Lua::GetInt(const char* variable) const
	{
		lua_getglobal(_luaState, variable);

		if (!lua_isinteger(_luaState, TOP_STACK))
		{
			VANIM_ERROR(variable << " is not an integer");
			return 0;
		}

		return (int)lua_tointeger(_luaState, TOP_STACK);
	}

	const char* Lua::GetString(const char* variable) const
	{
		lua_getglobal(_luaState, variable);

		if (!lua_isstring(_luaState, TOP_STACK))
		{
			VANIM_ERROR(variable << " is not a string");
			return "";
		}

		return (const char*)lua_tostring(_luaState, TOP_STACK);
	}

	bool Lua::GetBool(const char* variable) const
	{
		lua_getglobal(_luaState, variable);

		if (!lua_isboolean(_luaState, TOP_STACK))
		{
			VANIM_ERROR(variable << " is not a bool");
			return false;
		}

		return (bool)lua_toboolean(_luaState, TOP_STACK);
	}

	float Lua::GetFloat(int32_t index) const
	{
		if (!lua_isnumber(_luaState, index))
		{
			VANIM_ERROR("variable at the top of the stack is not a float");
			return 0.0f;
		}

		return (float)lua_tonumber(_luaState, index);
	}

	int32_t Lua::GetInt(int32_t index) const
	{
		if (!lua_isinteger(_luaState, index))
		{
			VANIM_ERROR("variable at the top of the stack is not an integer");
			return 0;
		}

		return (int32_t)lua_tointeger(_luaState, index);
	}

	const char* Lua::GetString(int32_t index) const
	{
		if (!lua_isstring(_luaState, index))
		{
			VANIM_ERROR("variable at the top of the stack is not a string");
			return "";
		}

		return (const char*)lua_tostring(_luaState, index);
	}

	bool Lua::GetBool(int32_t index) const
	{
		if (!lua_isboolean(_luaState, index))
		{
			VANIM_ERROR("variable at the top of the stack is not a bool");
			return false;
		}

		return (bool)lua_toboolean(_luaState, index);
	}

	float Lua::GetFloatInTable(const char* key) const
	{
		lua_pushstring(_luaState, key);
		lua_gettable(_luaState, TOP_STACK - 1);

		if (!lua_isnumber(_luaState, TOP_STACK))
		{
			VANIM_ERROR("value at" << key << " is not a float");
			return 0.0f;
		}

		float value = (float)lua_tonumber(_luaState, TOP_STACK);

		lua_pop(_luaState, 1);

		return value;
	}

	int32_t Lua::GetIntInTable(const char* key) const
	{
		lua_pushstring(_luaState, key);
		lua_gettable(_luaState, TOP_STACK - 1);

		if (!lua_isinteger(_luaState, TOP_STACK))
		{
			VANIM_ERROR("value at" << key << " is not an integer");
			return 0;
		}

		int32_t value = (int32_t)lua_tointeger(_luaState, TOP_STACK);

		lua_pop(_luaState, 1);

		return value;
	}

	const char* Lua::GetStringInTable(const char* key) const
	{
		lua_pushstring(_luaState, key);
		lua_gettable(_luaState, TOP_STACK - 1);

		if (!lua_isstring(_luaState, TOP_STACK))
		{
			VANIM_ERROR("value at" << key << " is not a string");
			return "";
		}
		
		const char* value = (const char*)lua_tostring(_luaState, TOP_STACK);

		lua_pop(_luaState, 1);

		return value;
	}

	bool Lua::GetBoolInTable(const char* key) const
	{
		lua_pushstring(_luaState, key);
		lua_gettable(_luaState, TOP_STACK - 1);

		if (!lua_isboolean(_luaState, TOP_STACK))
		{
			VANIM_ERROR("value at" << key << " is not a bool");
			return false;
		}

		bool value = (bool)lua_toboolean(_luaState, TOP_STACK);

		lua_pop(_luaState, 1);

		return value;
	}

	void Lua::PushFloat(float value) const
	{
		lua_pushnumber(_luaState, value);
	}

	void Lua::PushInt(int32_t value) const
	{
		lua_pushinteger(_luaState, value);
	}

	void Lua::PushString(const char* value) const
	{
		lua_pushstring(_luaState, value);
	}

	void Lua::PushBool(bool value) const
	{
		lua_pushboolean(_luaState, value);
	}

	void Lua::Pop() const
	{
		lua_pop(_luaState, 1);
	}

	bool Lua::PutTableOnTop(const char* table) const
	{
		lua_getglobal(_luaState, table);

		return lua_istable(_luaState, TOP_STACK);
	}

	bool Lua::PutFunctionOnTop(const char* function) const
	{
		lua_getglobal(_luaState, function);

		return lua_isfunction(_luaState, TOP_STACK);
	}

	bool Lua::CallFunction(
		size_t numArguments, 
		size_t numReturns
	) const
	{
		return CheckResult(lua_pcall(_luaState, numArguments, numReturns, NULL));
	}

	void Lua::RegisterFunction(
		const char* name,
		int (*function)(lua_State*)
	) const
	{
		lua_register(_luaState, name, function);
	}

	bool Lua::CheckResult(int32_t result) const
	{
		switch (result)
		{
			case LUA_OK:
				return true;
			default:
				const char* errMsg = lua_tostring(_luaState, TOP_STACK);
				VANIM_ERROR("[LUA]: " << errMsg);
				return false;
		}
	}
}
