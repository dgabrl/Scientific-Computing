// milky_way_nfw_profile.cpp
// Analysis of the Milky Way rotation curve using NFW (Dark Matter) and Stellar Disk components.
// This project was supported by a FAPESP research grant.
// Data Source: MIT Haystack Observatory (https://www.haystack.mit.edu/wp-content/uploads/2020/07/memo_SRT_011.pdf)

#include <iostream>
#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TMath.h"

// Observational data from MIT Haystack (Radius in kpc, Velocity in km/s)
double x_data[9] = { 0, 1.5, 2.9, 4.2, 5.5, 6.5, 7.4, 8, 8.5 };
double y_data[9] = { 150, 219, 205, 229, 237, 238, 252, 237, 230 };
double y_err[9] = { 10, 10, 10, 10, 10, 10, 10, 10, 10 };

void milky_way_nfw_profile() {
    // Physical Constants
    double G = 6.67e-11;      // Gravitational constant [Nm²/kg²]
    double Md = 1e41;         // Disk Mass approximation [kg]
    double b = 4;             // Scale length [kpc]
    double rho_cr = 9.3e-27;  // Critical density of the Universe [kg/m³]
    double r_vir = 267 / 3.24078e-20; // Virial radius converted to meters
    double c = 12;            // Concentration parameter

    // Calculating rho_s for the Dark Matter Halo (NFW Profile)
    double rho_s = 34 * (pow(c, 3)) * rho_cr / (log(1 + c) - (c / (1 + c)));

    // Total Fit Curve (Empirical adjustment for visualization)
    TF1* f_fit = new TF1("f_fit", "[0]*(((x/[1])+[2])/((x/[1])+1))", 0, 12);
    f_fit->SetParameters(220, 1, 0.6);
    f_fit->SetLineColor(kBlack);
    f_fit->SetLineWidth(2);

    // Creating the graph with experimental points
    TGraphErrors* gr = new TGraphErrors(9, x_data, y_data, NULL, y_err);
    gr->SetMarkerStyle(21);
    gr->SetMarkerSize(1.2);
    gr->GetXaxis()->SetTitle("R (kpc)");
    gr->GetYaxis()->SetTitle("V (km/s)");
    gr->SetTitle("Rotation Curve of the Milky Way");
    gr->GetYaxis()->SetRangeUser(0, 350);

    gr->Draw("APE");
    gr->Fit("f_fit", "Q");

    // Stellar Disk Component (Keplerian-like fall-off)
    TF1* f_disk = new TF1("f_disk", "sqrt(((-[0]*[1]*3.24078e-20)/x)*(-1 + exp(-x/[2])*(1+(x/[2]))))/1000", 0, 12);
    f_disk->SetParameters(G, Md, b);
    f_disk->SetLineColor(kRed);
    f_disk->SetLineStyle(7);
    f_disk->Draw("same");

    // Dark Matter Halo Component (NFW Profile)
    double a_const = 4 * TMath::Pi() * G * rho_s * pow(r_vir, 3) / pow(c, 3);
    TF1* g_nfw = new TF1("g_nfw", "130.8 + sqrt([0]*((3.24078e-20/x)*log(1+([3]*x)/([2]*3.24078e-20))-([3]/([2]+[3]*(x/3.24078e-20)))))/1000", 0, 12);
    g_nfw->SetParameters(a_const, rho_s, r_vir, c);
    g_nfw->SetLineColor(kBlue);
    g_nfw->SetLineStyle(7);
    g_nfw->Draw("same");

    // Legend configuration
    TLegend* legend = new TLegend(0.15, 0.65, 0.35, 0.85);
    legend->SetBorderSize(1);
    legend->AddEntry(f_disk, "Stellar Disk", "l");
    legend->AddEntry(gr, "Exp. Points (MIT)", "lep");
    legend->AddEntry(g_nfw, "NFW Halo", "l");
    legend->AddEntry(f_fit, "Total Fit", "l");
    legend->Draw();
}
