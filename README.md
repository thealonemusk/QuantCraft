# QuantCraft

QuantCraft is a lightweight, modular backtesting skeleton written in modern C++ (C++17).
It demonstrates a simple data-loader -> strategy -> execution -> portfolio pipeline and is intended as a starting point for building a scalable backtester.

## What you'll find here

- `core/` - core engine components: `Backtester`, `ExecutionEngine`, `Portfolio`, `Order`, `Trade`.
- `data/` - CSV parsing and `MarketDataLoader` (simple CSV-backed loader).
- `strategies/` - example strategies (`MeanReversion` and `Momentum`).
- `utils/` - small helpers like `Logger` and `MathUtils`.
- `main.cpp` - small demo runner that exercises the strategy and portfolio.

## Quick start (Windows PowerShell)

1. Configure and generate the build files with CMake:

```powershell
cmake -S . -B build
```

2. Build the project (Release recommended):

```powershell
cmake --build build --config Release
```

3. Run the produced executable:

```powershell
.\build\Release\quantcraft.exe
```

You should see console output showing the demo backtest and final portfolio state.

## CSV loader format

The simple CSV loader expects rows in this order:

timestamp,open,high,low,close,volume[,symbol]

If the `symbol` column is missing the loader assigns the symbol `TEST`.

## Assumptions & Limitations

This project is a lightweight starting point. Below are the important assumptions and current limitations you should be aware of when using or extending the code.

- Data input

  - The CSV loader expects a simple OHLCV row per line: timestamp,open,high,low,close,volume[,symbol]. Rows with fewer than 6 columns are skipped.
  - Timestamp handling is string-based and not parsed into a time type. Trades and analysis use timestamps as opaque strings.
  - There is no calendar alignment or handling of missing bars. Strategies receive only the rows present in the CSV in file order.
- Execution model

  - Orders are executed as market fills at the bar close price with a small fixed slippage factor. There is no order book, limit order queuing, partial fills simulation, or latency model.
  - Execution assumes full fills for the requested quantity when the portfolio accepts the trade.
- Portfolio & risk

  - The portfolio uses a simple cash/position model. Shorting is allowed (positions can go negative).
  - A basic `applyTrade` method returns true/false for acceptance; it uses a placeholder leverage check and conservatively rejects trades that would push cash far below a naive bound. This is not a replacement for a proper margin model.
  - There is no per-symbol position limits, multi-currency handling, transaction costs other than slippage, or fees modeling.
- Strategy contract

  - Strategies implement `onData(timestamp, price)` and `generateSignals()` and are called sequentially per bar by the backtester.
  - Strategies are not required to be thread-safe. If you parallelize signal generation later, ensure strategies use local state or provide synchronization.
- Concurrency & scalability

  - The current backtester runs in a single thread: strategies are called one-by-one and orders are executed synchronously.
  - The architecture is modular and ready for concurrency improvements (per-bar parallel signal generation, per-symbol sharding). These need careful synchronization when updating shared state (Portfolio, TradeLogger).
- Results & analytics

  - A simple `ResultsAnalyzer` computes realized PnL and an approximate maximum drawdown from the ordered trade list. It does not compute time-series metrics (daily returns, Sharpe) because we do not maintain an equity curve at per-bar granularity yet.
  - Trade logging writes a `trades.csv` with the executed trades. The CSV is created even if zero trades were logged (header only).
- Testing & configuration

  - No unit tests or CI integration included yet. Adding Catch2 / GoogleTest and wiring a test target in CMake is recommended.
  - Configuration is code-driven (constants or `main.cpp`). No CLI flag parsing or config file (JSON/TOML) is present yet.

todo:
add a synthetic `data/sample.csv` to exercise the full pipeline, wire unit tests, add a proper margin/risk model, simulate partial fills, or introduce concurrency for signal generation.



## Testing

add a synthetic `data/sample.csv` to exercise the full pipeline, wire unit tests, add a proper margin/risk model, simulate partial fills, or introduce concurrency for signal generation.

  This project doesn't include unit tests yet. Two common ways to add tests are shown below; pick one and I can wire it into CMake for you.

  Option A — Catch2 via FetchContent (no external package manager)

1. Edit `CMakeLists.txt` and add a test target that uses FetchContent to download Catch2 and compile tests. Example CMake snippet:

```cmake
  include(FetchContent)
  FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
  )
  FetchContent_MakeAvailable(catch2)

  add_executable(tests tests/test_main.cpp tests/test_portfolio.cpp)
  target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
  include(CTest)
  include(Catch)
  catch_discover_tests(tests)
```

2. Create `tests/test_main.cpp` and `tests/test_portfolio.cpp` with some basic assertions.
3. Build and run tests from PowerShell:

```powershell
  # Configure
  cmake -S . -B build
  # Build tests
  cmake --build build --config Release --target tests
  # Run tests
  ctest --test-dir build --output-on-failure
```

  Option B — Install Catch2 with vcpkg (system-wide package flow)

1. Install vcpkg and install Catch2:

```powershell
  # (one-time)
  git clone https://github.com/microsoft/vcpkg.git
  cd vcpkg
  .\bootstrap-vcpkg.bat
  # install Catch2
  vcpkg install catch2
```

2. Tell CMake to use vcpkg toolchain when configuring:

```powershell
  cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake
  cmake --build build --config Release
  ctest --test-dir build --output-on-failure
```

  If you'd like I can:

- Add a small set of unit tests (portfolio and CSV parser) and wire the FetchContent CMake snippet above.
- Add a `tests/` folder with example tests and update `CMakeLists.txt` to expose a `tests` target.

  Pick which testing approach you prefer and I will implement the CMake changes and add a couple of starter tests.
