# F1 Race Strategy and Tyre Life Simulator 🏎️🏁

A C-based physics engine and strategy simulator for Formula 1 tyre degradation and pit-stop optimization. Inspired by real-world telemetry logic and track-specific variables.

## 🚀 What's New in V1.6 (Core Architecture Update)

With this latest major refactoring, the simulator's backend has been completely overhauled. It now utilizes advanced C data structures and decoupled logic for maximum efficiency and readability.

* **Separation of Concerns (Rendering vs. Calculation):** Completely isolated the mathematical simulation engine (`calculateStopNumber`) from the UI/rendering layer (`resultScreen`). The engine now strictly calculates physics and returns data, while the rendering layer purely handles console output. 
* **Data Encapsulation (Struct Returns):** Eliminated global variable dependencies. The simulation now packages all 10,000 algorithmic possibilities and returns the winning telemetry inside a highly optimized `strategy` struct (StrategyResult).
* **High-Fidelity Fuel Tracking & Bug Fix:** Resolved a critical logic flaw where the final stint bypassed fuel consumption. The simulator now accurately tracks the exact physical fuel weight (in kg) crossing the finish line, rather than relying on boolean states, providing extremely accurate "Fuel amount is not enough" alerts.
* **Safety Car Groundwork:** The structural and architectural preparations for handling Safety Car (SC) and Virtual Safety Car (VSC) logic are now fully embedded in the main simulation loop.
* **Expanded Probability Pool:** The algorithmic calculation pool (`PROBABILITY_CALCULATION_NUMBER`) operates seamlessly with 10,000 possibilities, yielding sharper and highly reliable race time estimations.

*(Includes all V1.5 features: Dynamic Pit Windows, Cold Weather Graining Calibration, and Full Modular C Structure via Makefile).*

## ⚙️ Core Mechanics

The simulator analyzes track characteristics using the following parameters:
1. **Track Stress Level (1-5):** Lateral and longitudinal loads exerted on the tyres based on the circuit's cornering profile.
2. **Track Temperature:** Real-time thermal degradation and cold-weather graining calculations.
3. **Fuel Weight Penalty:** The dynamic and linear impact of fuel load (up to 110kg) on lap times, braking zones, and overall tyre lifespan.
4. **Pit Lane Time:** The net time lost in the pit lane, used to calculate the Track Position balance vs. tyre advantage.

## 🛠️ How to Build & Run (User Manual)

With the transition to a modular C architecture, the simulator is now compiled using a standard `Makefile`. This ensures a clean, automated, and lightning-fast build process.

### Prerequisites
* A C compiler (e.g., **GCC** via MinGW/MSYS2 for Windows, or native GCC on Linux/macOS).
* The **`make`** utility installed and properly added to your system's environment variables (`PATH`).

### 1. Compile the Simulator (Box, Box!)
Open your terminal in the root directory of the project and run the following command to let the pit crew assemble the car:

```bash
make

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
* [ ] **Weather System (V1.7):** Integrating wet track dynamics, including Intermediate and Full Wet tyre compounds.
* [ ] **Safety Car (SC) & VSC Impact:** Calculating the strategic impact of Safety Car periods (e.g., ~50% reduction in pit lane time loss) on Undercut/Overcut strategies.
* [ ] **Dirty Air Coefficient:** Modeling the negative impact of running in traffic on tyre degradation and temperatures.
