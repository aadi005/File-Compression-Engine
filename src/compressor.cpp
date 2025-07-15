#include "compressor.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

namespace Compressor
{
    std::vector<StockEntry> readCSV(const std::string &filename)
    {
        std::vector<StockEntry> data;
        std::ifstream file(filename);
        std::string line;

        getline(file, line);
        while (getline(file, line))
        {
            std::istringstream ss(line);
            std::string token;
            StockEntry entry;

            getline(ss, entry.date, ',');

            getline(ss, token, ',');
            entry.close = std::stod(token.substr(1));

            getline(ss, token, ',');
            entry.volume = std::stol(token);

            getline(ss, token, ',');
            entry.open = std::stod(token.substr(1));

            getline(ss, token, ',');
            entry.high = std::stod(token.substr(1));

            getline(ss, token, ',');
            entry.low = std::stod(token.substr(1));

            data.push_back(entry);
        }
        return data;
    }

    void compressToFile(const std::vector<StockEntry> &data, const std::string &outputFile)
    {
        std::ofstream out(outputFile, std::ios::binary);

        if (data.empty())
            return;

        out.write(reinterpret_cast<const char *>(&data[0]), sizeof(StockEntry));

        for (size_t i = 1; i < data.size(); ++i)
        {
            double dc = data[i].close - data[i - 1].close;
            long dv = data[i].volume - data[i - 1].volume;
            double do_ = data[i].open - data[i - 1].open;
            double dh = data[i].high - data[i - 1].high;
            double dl = data[i].low - data[i - 1].low;

            out.write(reinterpret_cast<const char *>(&dc), sizeof(double));
            out.write(reinterpret_cast<const char *>(&dv), sizeof(long));
            out.write(reinterpret_cast<const char *>(&do_), sizeof(double));
            out.write(reinterpret_cast<const char *>(&dh), sizeof(double));
            out.write(reinterpret_cast<const char *>(&dl), sizeof(double));
        }

        out.close();
    }

    std::vector<StockEntry> decompressFromFile(const std::string &inputFile)
    {
        std::ifstream in(inputFile, std::ios::binary);
        std::vector<StockEntry> data;

        if (!in)
            return data;

        StockEntry base;
        in.read(reinterpret_cast<char *>(&base), sizeof(StockEntry));
        data.push_back(base);

        while (in.peek() != EOF)
        {
            double dc, do_, dh, dl;
            long dv;
            in.read(reinterpret_cast<char *>(&dc), sizeof(double));
            in.read(reinterpret_cast<char *>(&dv), sizeof(long));
            in.read(reinterpret_cast<char *>(&do_), sizeof(double));
            in.read(reinterpret_cast<char *>(&dh), sizeof(double));
            in.read(reinterpret_cast<char *>(&dl), sizeof(double));

            StockEntry prev = data.back();
            StockEntry entry = {
                prev.date,
                prev.close + dc,
                prev.volume + dv,
                prev.open + do_,
                prev.high + dh,
                prev.low + dl};

            data.push_back(entry);
        }

        return data;
    }

    void writeCSV(const std::vector<StockEntry> &data, const std::string &filename)
    {
        std::ofstream file(filename);
        file << "Date,Close/Last,Volume,Open,High,Low\n";

        for (const auto &row : data)
        {
            file << row.date << ",$"
                 << std::fixed << std::setprecision(2) << row.close << ","
                 << row.volume << ",$"
                 << row.open << ",$"
                 << row.high << ",$"
                 << row.low << "\n";
        }
    }

    double calculateCompressionRatio(const std::string &originalFile, const std::string &compressedFile)
    {
        std::ifstream in1(originalFile, std::ifstream::ate | std::ifstream::binary);
        std::ifstream in2(compressedFile, std::ifstream::ate | std::ifstream::binary);
        return static_cast<double>(in1.tellg()) / static_cast<double>(in2.tellg());
    }
}
