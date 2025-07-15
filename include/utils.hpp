#pragma once

#include <string>

namespace Utils
{
    std::string generateUUID();
    std::string currentTimestamp();
    void logResult(const std::string &uuid, long compressMs, long decompressMs, double ratio, bool isValid);
}
