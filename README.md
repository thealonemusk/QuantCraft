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

## Development notes & next steps

- Add unit tests (Catch2 or GoogleTest) and wire them into the CMake build.
- Add trade logging and a results analyzer (PnL time series, Sharpe ratio, drawdown).
- Implement concurrency for signal generation and/or per-symbol sharding for large universes.
- Improve portfolio risk checks (reject orders that would breach cash/limits) and simulate partial fills.
- Add configuration via CLI or a simple TOML/JSON file for strategy params and paths.

If you'd like, I can implement any of the above (unit tests, concurrency, or result export). Tell me which and I'll proceed.

# QuantCraft-

Portfolio portfolio(100000);
