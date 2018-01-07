#pragma once

#include <cstdio>
#include <string>
#include <utility>
#include <vector>
#include "IRuntimeModule.hpp"
#include "Buffer.hpp"

namespace My {
	class AssetLoader : public IRuntimeModule {
    public:
        virtual ~AssetLoader() {};

        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick();

        typedef void* AssetFilePtr;

        enum AssetOpenMode {
            MY_OPEN_TEXT   = 0, /// Open In Text Mode
            MY_OPEN_BINARY = 1, /// Open In Binary Mode 
        };

        enum AssetSeekBase {
            MY_SEEK_SET = 0, /// SEEK_SET
            MY_SEEK_CUR = 1, /// SEEK_CUR
            MY_SEEK_END = 2  /// SEEK_END
        };

        bool AddSearchPath(const char *path);

        bool RemoveSearchPath(const char *path);

        virtual bool FileExists(const char *filePath);

        virtual AssetFilePtr OpenFile(const char* name, AssetOpenMode mode);

        virtual Buffer SyncOpenAndReadText(const char *filePath);

        virtual Buffer SyncOpenAndReadBinary(const char *filePath);

        virtual size_t SyncRead(const AssetFilePtr& fp, Buffer& buf);

        virtual void CloseFile(AssetFilePtr& fp);

        virtual size_t GetSize(const AssetFilePtr& fp);

        virtual int32_t Seek(AssetFilePtr fp, long offset, AssetSeekBase where);

        inline std::string SyncOpenAndReadTextFileToString(const char* fileName)
        {
            std::string result;
            Buffer buffer = SyncOpenAndReadText(fileName);
            char* content = reinterpret_cast<char*>(buffer.GetData());

            if (content)
            {
                result = std::string(std::move(content));
            }

            return result;
        }
    private:
        std::vector<std::string> m_strSearchPath;
	};

    extern AssetLoader*     g_pAssetLoader;
}
