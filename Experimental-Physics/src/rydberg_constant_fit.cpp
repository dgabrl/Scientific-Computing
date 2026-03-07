/**
 * @file rydberg_constant_fit.cpp
 * @author David Gabriel Guimarães (USP)
 * @brief Linear regression analysis to determine the Rydberg Constant.
 * * This script processes experimental data from the Hydrogen Balmer series.
 * It performs a linear fit based on the Rydberg formula: 1/lambda = R_H * (1/n1^2 - 1/n2^2),
 * rearranged here to extract R_H from the slope.
 */

#include <iostream>
#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"

void rydberg_constant_fit() {
    // Experimental data: wavelength (y) vs 1/n^2 (x)
    // Values represent observed spectral lines for the Balmer series
    double y[3] = { 0.0002298, 0.0002055, 0.0001519 };
    double x[3] = { 0.040, 0.063, 0.111 };
    double ey[3] = { 0.0000005, 0.0000005, 0.0000005 }; // Uncertainty in wavelength

    // Create a TGraphErrors object to handle uncertainties during the fit
    TGraphErrors* gr1 = new TGraphErrors(3, x, y, NULL, ey);
    
    // Graphical styling
    gr1->SetMarkerStyle(20);
    gr1->SetMarkerColor(1);
    gr1->SetLineColor(1);
    
    // Labels kept in Portuguese as requested
    gr1->GetXaxis()->SetTitle("1/n^{2}");
    gr1->GetYaxis()->SetTitle("Comprimento de onda #lambda (angstrom)");
    gr1->SetTitle("Ajuste para a Constante de Rydberg");

    gr1->Draw("APE");

    // Define the fit function based on the theoretical model
    // [0] represents the slope related to Rydberg Constant, [1] represents the intercept
    TF1* g = new TF1("g", "[0]*(0.25 - x) + [1]", 0.03, 0.12);

    // Initial parameter estimation for the numerical solver
    g->SetParameter(0, 1);
    g->SetParameter(1, 1);
    g->SetLineColor(2); // Red line for the fit result
    g->SetLineStyle(2); // Dashed line style

    // Perform the Chi-Square minimization fit
    gr1->Fit("g");

    // Visualization of the results in a legend
    TLegend* legend = new TLegend(0.1, 0.4, 0.20, 0.9);
    legend->SetHeader("y = (0,00110(1))x -1(2)*10^{-6}", "C");
    legend->Draw();
}
