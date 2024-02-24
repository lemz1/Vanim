#pragma once

extern "C"
{
	#include <lua542/include/lua.h>
	#include <lua542/include/lauxlib.h>
	#include <lua542/include/lualib.h>
}

#include "VanimCore/Base.h"

#include "VanimCore/Util/AssetManager.h"

namespace Vanim
{
	class Lua
	{
	public:
		Lua();
		~Lua();

		bool RunFile(const char* filePath) const;

		bool RunCommand(const char* command) const;

		float GetFloat(const char* variable) const;
		int32_t GetInt(const char* variable) const;
		const char* GetString(const char* variable) const;
		bool GetBool(const char* variable) const;

		float GetFloat(int32_t index) const;
		int32_t GetInt(int32_t index) const;
		const char* GetString(int32_t index) const;
		bool GetBool(int32_t index) const;

		float GetFloatInTable(const char* key) const;
		int32_t GetIntInTable(const char* key) const;
		const char* GetStringInTable(const char* key) const;
		bool GetBoolInTable(const char* key) const;

		void PushFloat(float value) const;
		void PushInt(int32_t value) const;
		void PushString(const char* value) const;
		void PushBool(bool value) const;

		void Pop() const;

		bool PutTableOnTop(const char* table) const;
		bool PutFunctionOnTop(const char* function) const;

		bool CallFunction(
			size_t numArguments, 
			size_t numReturns
		) const;

		void RegisterFunction(
			const char* name, 
			int (*function)(lua_State*)
		) const;
	public:
		static constexpr int32_t TOP_STACK = -1;
		static constexpr int32_t BOTTOM_STACK = 1;
	private:
		bool CheckResult(int32_t result) const;
	private:
		lua_State* _luaState;
	};
}
