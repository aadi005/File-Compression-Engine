#include "../include/utils.hpp"
#include <chrono>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <random>
#include <filesystem>

namespace Utils
{
    std::string generateUUID()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 15);
        std::stringstream ss;

        for (int i = 0; i < 32; ++i)
        {
            ss << std::hex << dis(gen);
            if (i == 7 || i == 11 || i == 15 || i == 19)
                ss << "-";
        }

        return ss.str();
    }

    std::string currentTimestamp()
    {
        auto now = std::chrono::system_clock::now();
        auto in_time = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    void logResult(const std::string &uuid, long compressMs, long decompressMs, double ratio, bool isValid)
    {
        std::filesystem::create_directory("logs");

        std::ifstream original("data/apple_stock.csv", std::ifstream::ate | std::ifstream::binary);
        std::ifstream compressed("data/compressed.bin", std::ifstream::ate | std::ifstream::binary);
        auto originalSize = original.tellg();
        auto compressedSize = compressed.tellg();

        std::ofstream log("logs/compression_log.txt", std::ios::app);

        log << "Run ID: " << uuid << "\n"
            << "Timestamp: " << currentTimestamp() << "\n"
            << "Original Size (bytes): " << originalSize << "\n"
            << "Compressed Size (bytes): " << compressedSize << "\n"
            << "Compression Ratio: " << ratio << "\n"
            << "Compression Time (ms): " << compressMs << "\n"
            << "Decompression Time (ms): " << decompressMs << "\n"
            << "Validation: " << (isValid ? "PASS" : "FAIL") << "\n"
            << "\n";

        log.close();
    }

}
