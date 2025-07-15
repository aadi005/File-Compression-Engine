# Data Compression Engine

A C++ project that compresses and decompresses Apple stock price data using delta encoding.  
Logs performance metrics including compression ratio, time taken, and validation status.

## Input Format

CSV file with the following header and data format:

```
Date,Close/Last,Volume,Open,High,Low
07/14/2025,$208.62,38840110,$209.93,$210.91,$207.54
```

## Features

- Delta-encodes numeric fields (Open, High, Low, Close, Volume)
- Binary compression with custom format
- Decompression and exact restoration
- Validation of data integrity
- Unique run ID logging with timestamps
- Benchmarking: compression ratio, time (ms)

## Folder Structure

```
stockDataCompressionEngine/
├── include/         # Header files
├── src/             # C++ source code
├── data/            # Input stock data + compressed output
├── restored/        # Decompressed CSV
├── logs/            # Run logs
├── Makefile         # Build and run
└── README.md
```

## Usage

To compile and run the project:

```
make run
```

To clean outputs:

```
make clean
```

## Logs

Each run creates an entry in `logs/compression_log.txt`:

## Author

**Aaditya Goel**
