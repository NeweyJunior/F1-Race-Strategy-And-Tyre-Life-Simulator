# F1 Race Strategy and Tyre Life Simulator 🏎️🏁

A C-based physics engine and strategy simulator for Formula 1 tyre degradation and pit-stop optimization. Inspired by real-world telemetry logic and track-specific variables.

## 🚀 What's New in V1.5 (Latest Update)

With this release, the simulator evolves from a basic mathematical model into a system closely resembling real-world telemetry and edge-case scenarios.

* **Pit Window Integration:** Added dynamic pit windows to strategy calculations (`SOFT_WINDOW_COEFFICIENT`, `MEDIUM_WINDOW_COEFFICIENT`, `HARD_WINDOW_COEFFICIENT`). The simulator now calculates not only which tyre compound to fit but exactly between which laps the pit stops should occur.
* **Graining Model Calibration:** The "Cold Weather Graining" penalty for tracks with low temperatures (<25°C) has been calibrated to 18%. This aligns the simulator's strategic decisions perfectly with real-world F1 outcomes on cold/low-grip tracks (e.g., Piastri's 2024 Baku victory).
* **Increased Simulation Precision:** The algorithmic calculation pool (`PROBABILITY_CALCULATION_NUMBER`) was expanded from 1,000 to 10,000 possibilities, yielding much sharper and highly reliable race time estimations.
* **Input Validation:** Implemented comprehensive `scanf` validations for terminal inputs to prevent system crashes caused by incorrect or invalid data entries.
* **Repository Cleanup:** Updated the `.gitignore` file to untrack compiled `.exe` files and local `.vscode` configurations, keeping the repository strictly focused on source code.

## ⚙️ Core Mechanics

The simulator analyzes track characteristics using the following parameters:
1. **Track Stress Level (1-5):** Lateral and longitudinal loads exerted on the tyres based on the circuit's cornering profile.
2. **Track Temperature:** Real-time thermal degradation and cold-weather graining calculations.
3. **Fuel Weight Penalty:** The linear impact of a full fuel load (110kg) on lap times and overall tyre lifespan.
4. **Pit Lane Time:** The net time lost in the pit lane, used to calculate the Track Position balance vs. tyre advantage.

## 🗺️ Roadmap
* [ ] **Weather System (V1.6):** Integrating wet track dynamics, including Intermediate and Full Wet tyre compounds.
* [ ] **Safety Car (SC) & VSC Impact:** Calculating the strategic impact of Safety Car periods (e.g., ~50% reduction in pit lane time loss) on Undercut/Overcut strategies.
* [ ] **Dirty Air Coefficient:** Modeling the negative impact of running in traffic on tyre degradation and temperatures.