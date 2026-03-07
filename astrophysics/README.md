# Milky Way Rotation Curve Analysis 🌌

This project implements a numerical model to analyze the rotation velocity of the Milky Way as a function of its radial distance, addressing one of the most significant evidences for the existence of **Dark Matter**.

## 🔬 Scientific Context
In Newtonian (Keplerian) dynamics, the rotation velocity of a galaxy is expected to decrease as distance from the center increases ($V \propto r^{-1/2}$). However, observational data shows a "flat" rotation curve at large radii. This implementation decomposes the galactic mass into two primary components to explain this phenomenon:

1.  **Stellar Disk (Baryonic Matter):** Modeled with an exponential disk profile.
2.  **Dark Matter Halo (Non-Baryonic):** Modeled using the **Navarro-Frenk-White (NFW)** density profile, which is the standard in modern cosmology.

## 📊 Resulting Visualization

![Milky Way Rotation Curve Result](rotation_curve_result.png)

*The plot illustrates how the **Stellar Disk** (red dashed line) fails to account for high velocities at the outskirts, while the addition of the **NFW Halo** (blue dashed line) aligns the **Total Fit** (black solid line) with the experimental data.*

## 🛠️ Technical Features
* **Language:** C++
* **Framework:** [CERN ROOT](https://root.cern/) (Data Analysis Framework).
* **Algorithm:** * Multi-component function fitting using `TF1`.
    * Statistical error handling with `TGraphErrors`.
    * Integration of physical constants (Gravitational constant $G$, Critical Density $\rho_{cr}$, etc.).

## 📜 Credits & Data Sources
* **Research Grant:** Developed during an Undergraduate Research Fellowship supported by **FAPESP** (São Paulo Research Foundation).
* **Data Source:** Observational rotation data provided by the **MIT Haystack Observatory** ([Memo SRT 011](https://www.haystack.mit.edu/wp-content/uploads/2020/07/memo_SRT_011.pdf)).

## 🚀 How to Run
Ensure you have the CERN ROOT framework installed. Run the script directly in the ROOT interpreter:
```bash
root -l milky_way_nfw_profile.cpp
