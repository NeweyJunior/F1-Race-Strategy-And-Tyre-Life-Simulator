# F1 Race Strategy and Tyre Life Simulator 🏎️🏁

A C-based physics engine and strategy simulator for Formula 1 tyre degradation and pit-stop optimization. Inspired by real-world telemetry logic and track-specific variables.

## 🚀 What's New in V1.7 (Safety Car & Precision Update)

V1.7 introduces a major leap in tactical realism and temporal precision. We have bridged the gap between basic lap-timing and high-fidelity race engineering.

* **Safety Car (SC) Integration:** The engine can now simulate race interruptions. It features a "stitching" logic that seamlessly merges pre-SC race data with the dynamic post-SC strategy, allowing for accurate "free pit stop" analysis.
* **Temporal Precision (HH:MM:SS.ms):** Race duration output has been upgraded from simple MM:SS to a precise **Hours:Minutes:Seconds.Milliseconds** format, providing granular data for qualifying and race pace comparisons.
* **Optimized Timing Engine:** The underlying time-keeping algorithm has been overhauled for better performance, ensuring millisecond-perfect estimation across all 71+ laps.
* **Code Clarity & Maintainability:** `calculateStopNumber` and `printResult` have undergone extensive refactoring. The logic is now heavily commented and optimized for readability, making it easier for contributors to follow the race-strategy flow.
* **Strategy Struct Evolution:** The core `strategy` struct has been expanded to support multi-stint telemetry data, allowing for deeper historical analysis of race-winning strategies.

*(Includes all V1.6 features: Separation of Concerns, Data Encapsulation, and Full Modular C Structure via Makefile).*

## ⚙️ Core Mechanics

The simulator analyzes track characteristics using the following parameters:

1. **Track Stress Level (1-5):** Lateral and longitudinal loads exerted on the tyres.
2. **Track Temperature:** Thermal degradation and cold-weather graining calculations.
3. **Fuel Weight Penalty:** Dynamic impact of fuel load (up to 110kg) on lap times.
4. **Pit Lane Time:** Balance of track position vs. tyre advantage.

## 🛠️ How to Build & Run (User Manual)

### 1. Compile the Simulator (Box, Box!)
```bash
make
```
*Note: The Makefile will automatically locate all necessary source files inside the `src/` directory, compile them, and link them into a single executable.*

### 2. Ignite the Engine
Once the compilation is complete and the `main.exe` file is generated, launch the simulation by running:

**For Windows:**
```bash
.\main.exe
```

**For Linux / macOS:**
```bash
./main.exe
```

## 🗺️ Roadmap
* [ ] **Weather System:** Integrating wet track dynamics, including Intermediate and Full Wet tyre compounds.
* [ ] **🚀 Future Migration:** The long-term architectural goal for this simulator is a full migration to C++. This will allow us to leverage Object-Oriented Programming (OOP) for complex vehicle dynamics, multi-car simulation, and template-based tyre models.
* [ ] **Dirty Air Coefficient:** Modeling the negative impact of running in traffic on tyre degradation and temperatures.