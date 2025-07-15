#include "../include/compressor.hpp"
#include "../include/utils.hpp"
#include <iostream>
#include <chrono>
#include <filesystem>

int main()
{
    std::string inputCSV = "data/apple_stock.csv";
    std::string compressedFile = "data/compressed.bin";
    std::string restoredCSV = "restored/restored.csv";

    std::cout << "Reading CSV...\n";
    auto stockData = Compressor::readCSV(inputCSV);

    std::cout << "Compressing...\n";
    auto start = std::chrono::high_resolution_clock::now();
    Compressor::compressToFile(stockData, compressedFile);
    auto end = std::chrono::high_resolution_clock::now();
    auto compressionTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    double ratio = Compressor::calculateCompressionRatio(inputCSV, compressedFile);

    std::cout << "Compression done in " << compressionTime << " ms\n";
    std::cout << "Compression Ratio: " << ratio << "\n";

    std::cout << "Decompressing...\n";
    start = std::chrono::high_resolution_clock::now();
    auto decompressed = Compressor::decompressFromFile(compressedFile);
    end = std::chrono::high_resolution_clock::now();
    auto decompressionTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Decompression done in " << decompressionTime << " ms\n";

    std::cout << "Writing restored CSV...\n";
    Compressor::writeCSV(decompressed, restoredCSV);

    bool match = (stockData.size() == decompressed.size());
    for (size_t i = 0; i < stockData.size() && match; ++i)
    {
        if (std::abs(stockData[i].close - decompressed[i].close) > 1e-6 ||
            std::abs(stockData[i].open - decompressed[i].open) > 1e-6 ||
            std::abs(stockData[i].high - decompressed[i].high) > 1e-6 ||
            std::abs(stockData[i].low - decompressed[i].low) > 1e-6 ||
            stockData[i].volume != decompressed[i].volume)
        {
            match = false;
        }
    }

    std::cout << (match ? "Data verified successfully.\n" : "Data mismatch detected!\n");

    std::string runID = Utils::generateUUID();
    Utils::logResult(runID, compressionTime, decompressionTime, ratio, match);

    return 0;
}
