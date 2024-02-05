#pragma once

#include <string>

namespace Vanim
{
	class AssetManager
	{
	public:
		static std::string GetFileContent(const char* filePath);
	};
}
