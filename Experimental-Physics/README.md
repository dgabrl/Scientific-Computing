# Experimental Physics: Atomic Spectroscopy 🧪

This repository documents the computational analysis of experimental data from the **Modern Physics Laboratory** at the **University of São Paulo (USP)**. The focus is on using the **CERN ROOT** framework to process spectral data, perform statistical fitting, and validate phenomena.

## 🔬 Project Overview: Mercury (Hg) Calibration

The first stage of this project involves the spectral calibration using a Mercury lamp. By identifying the exact pixel positions of known emission lines, we can establish a precise pixel-to-wavelength mapping for the spectrometer.

### Methodology
The analysis was performed using **Non-linear Least Squares Fitting**. Since spectral lines follow a distribution influenced by instrumental broadening, we applied **Gaussian Models** to extract:
* **Centroids ($\mu$):** The exact sub-pixel location of the peak.
* **Dispersion ($\sigma$):** The width of the emission line.
* **Amplitude:** The peak intensity.

## 🛠️ Technical Implementation

The implementation in `mercury_spectral_calibration.cpp` features:
* **`TGraphErrors`**: Used to handle raw intensity data and account for experimental uncertainties.
* **`TF1` (Gaussian Fit)**: Automated fitting using the `gaus` function to minimize $\chi^2$.
* **Multi-panel Visualization**: A $2 \times 3$ grid layout to compare different regions of the spectrum ($I$ and $II$) simultaneously.



## 📊 Results

The following result shows the automated fitting process. Each subplot represents a specific region of the Mercury spectrum where the red curve indicates the optimized Gaussian model.

### Spectral Peak Analysis
![Mercury Spectral Analysis](./results/mercury_spectral_analysis.png)

*Figure: Gaussian fits for Regions 1 and 2 of the Hg spectrum. These results are used to determine the peak means (Média) and standard deviations ($\sigma$) required for calibration.*

---

## 📂 Directory Structure

```text
.
├── README.md
├── results/
│   └── mercury_spectral_analysis.png
└── src/
    └── mercury_spectral_calibration.cpp
