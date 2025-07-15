#pragma once

#include <string>
#include <vector>
#include <tuple>

struct StockEntry
{
    std::string date;
    double close;
    long volume;
    double open;
    double high;
    double low;
};

namespace Compressor
{
    std::vector<StockEntry> readCSV(const std::string &filename);

    void compressToFile(const std::vector<StockEntry> &data, const std::string &outputFile);

    std::vector<StockEntry> decompressFromFile(const std::string &inputFile);

    void writeCSV(const std::vector<StockEntry> &data, const std::string &filename);

    double calculateCompressionRatio(const std::string &originalFile, const std::string &compressedFile);
}
