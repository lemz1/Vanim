#include "corepch.h"
#include "AssetManager.h"

#include "VanimCore/Base.h"

namespace Vanim
{
    std::string AssetManager::GetFileContent(const char* filePath)
    {
        std::ifstream file(filePath, std::ios::binary);

        if (!file.is_open())
        {
            VANIM_WARN("Couldn't find file: " << filePath);
            #ifdef VANIM_DEBUG
            assert(file.is_open());
            #endif
            return "";
        }

        std::string content;
        file.seekg(0, std::ios::end);
        content.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&content[0], content.size());
        file.close();

        return content;
    }
}
