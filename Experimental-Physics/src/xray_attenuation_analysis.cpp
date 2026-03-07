/**
 * @file xray_attenuation_analysis.cpp
 * @author David Gabriel Guimarães (USP)
 * @brief Analysis of X-ray attenuation coefficients for Zirconium (Zr) and Molybdenum (Mo).
 * * This script applies the Beer-Lambert law in its logarithmic form: ln(I0/I) = mu * x.
 * By plotting the logarithm of absorbance against the linear attenuation coefficient (mu),
 * we can verify the material's properties and the experimental setup's consistency.
 */

#include <iostream>
#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"

void xray_attenuation_analysis() {
    // Canvas setup: 1 column, 2 rows to compare Zr and Mo separately
    TCanvas* ct = new TCanvas("ct", "X-Ray Attenuation Analysis", 0, 0, 600, 800);
    ct->Divide(1, 2);

    // --- SECTION 1: Zirconium (Zr) Data ---
    // x: Linear attenuation coefficient mu (1/cm)
    // y: Logarithm of absorbance ln(N0/N)
    double x[2] = { 481.36, 159.78 }; 
    double y[2] = { 1.1, 0.77 }; 
    double ey[2] = { 0.1, 0.04 }; // Vertical error bars (uncertainty)

    TGraphErrors* gr1 = new TGraphErrors(2, x, y, NULL, ey);

    ct->cd(1);
    gr1->SetMarkerStyle(20);
    gr1->SetMarkerColor(1);
    gr1->SetLineColor(1);
    
    // Labels kept in Portuguese for result consistency
    gr1->GetXaxis()->SetTitle("#mu(1/cm)");
    gr1->GetYaxis()->SetTitle("Logaritmo da Absort#hat{a}ncia");
    gr1->SetTitle("Logaritmo da Absort#hat{a}ncia por #mu para o Zr");

    gr1->Draw("APE");
    
    // Theoretical model: Linear fit y = ax + b
    TF1* f1 = new TF1("f1", "[0]*x+[1]", 80, 500);
    f1->SetParameter(0, 0.03);
    f1->SetParameter(1, 0);
    f1->SetLineColor(2);
    f1->SetLineStyle(10); // Dashed line for the fit

    gr1->Fit("f1");

    TLegend* l1 = new TLegend(0.1, 0.7, 0.35, 0.9);
    l1->SetHeader("Legenda", "C");
    l1->AddEntry(gr1, "Dados Exp.", "lep");
    l1->AddEntry(f1, "Ajuste Te#acute{o}rico", "l");
    l1->Draw();

    // --- SECTION 2: Molybdenum (Mo) Data ---
    double x2[2] = { 291.4, 133.5 }; 
    double y2[2] = { 1.10, 2.51 }; 
    double ey2[2] = { 0.07, 0.07 };

    TGraphErrors* gr2 = new TGraphErrors(2, x2, y2, NULL, ey2);

    ct->cd(2);
    gr2->SetMarkerStyle(20);
    gr2->SetMarkerColor(1);
    gr2->SetLineColor(1);
    gr2->GetXaxis()->SetTitle("#mu(1/cm)");
    gr2->GetYaxis()->SetTitle("Logaritmo da Absort#hat{a}ncia");
    gr2->SetTitle("Logaritmo da Absort#hat{a}ncia por #mu para o Mo");

    gr2->Draw("APE");

    TF1* f2 = new TF1("f2", "[0]*x + [1]", 100, 810);
    f2->SetParameter(0, 1);
    f2->SetParameter(1, 0);
    f2->SetLineColor(2);
    f2->SetLineStyle(10);

    gr2->Fit("f2");

    TLegend* l2 = new TLegend(0.1, 0.7, 0.35, 0.9);
    l2->SetHeader("Legenda", "C");
    l2->AddEntry(gr2, "Dados Exp.", "lep");
    l2->AddEntry(f2, "Ajuste Te#acute{o}rico", "l");
    l2->Draw();
    
    // Optional: Save the plot automatically
    // ct->SaveAs("results/xray_attenuation_zr_mo.png");
}
