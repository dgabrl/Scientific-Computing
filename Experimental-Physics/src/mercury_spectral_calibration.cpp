/**
 * @file mercury_spectral_calibration.cpp
 * @author David Gabriel Guimarães (USP)
 * @brief Mercury (Hg) emission spectrum analysis for spectrometer calibration.
 * * This script utilizes the CERN ROOT framework to perform Gaussian fitting 
 * on various intensity peaks (pixels). The goal is to identify the centroids 
 * of emission lines to establish a pixel-to-wavelength mapping.
 */

#include <iostream>
#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"

void mercury_spectral_calibration() {
    // Canvas Setup: Dividing into a 2x3 matrix to visualize 6 simultaneous fits
    TCanvas* ct = new TCanvas("ct", "Time on axis", 0, 0, 600, 600);
    ct->Divide(2, 3);

    // --- REGION I.1 ---
    // Experimental Data: Pixel position vs. Captured Intensity
    double x1[5] = { 2569, 2570, 2571, 2572, 2573 };
    double y1[5] = { 620922, 747061, 769054, 769857, 579922 };
    double e_x1[5] = { 1, 1, 1, 1, 1 }; // Pixel error

    TGraphErrors* gr1 = new TGraphErrors(5, x1, y1, e_x1, NULL);

    ct->cd(1); // Access first quadrant
    gr1->SetMarkerStyle(20);
    gr1->SetMarkerColor(1);
    gr1->SetLineColor(1);
    gr1->GetXaxis()->SetTitle("Pixel");
    gr1->GetYaxis()->SetTitle("Intensidade");
    gr1->SetTitle("Regi#tilde{a}o I"); 
    
    gr1->Draw("APE");
    gr1->Fit("gaus"); // Gaussian Fit for peak identification

    TLegend* l1 = new TLegend(0.1, 0.7, 0.28, 0.9);
    l1->SetHeader("Legenda", "C");
    l1->AddEntry("NULL", "M#acute{e}dia = 2571");
    l1->AddEntry("NULL", "#sigma = 3");
    l1->Draw();

    // --- REGION I.2 ---
    double x2[8] = { 2575, 2576, 2577, 2578, 2579, 2580, 2581, 2582 };
    double y2[8] = { 527690, 712012, 766102, 770270, 768814, 769218, 768786, 665211 };
    double e_y2[8] = { 1, 1, 1, 1, 1, 1, 1, 1 };

    TGraphErrors* gr2 = new TGraphErrors(8, x2, y2, e_y2, NULL);

    ct->cd(2);
    gr2->SetMarkerStyle(20);
    gr2->SetMarkerColor(1);
    gr2->SetLineColor(1);
    gr2->GetXaxis()->SetTitle("Pixel");
    gr2->GetYaxis()->SetTitle("Intensidade");
    gr2->SetTitle("Regi#tilde{a}o I");

    gr2->Draw("APE");
    gr2->Fit("gaus");

    TLegend* l2 = new TLegend(0.1, 0.7, 0.28, 0.9);
    l2->SetHeader("Legenda", "C");
    l2->AddEntry("NULL", "M#acute{e}dia = 2579");
    l2->AddEntry("NULL", "#sigma = 5");
    l2->Draw();

    // --- REGION I.3 ---
    double x3[13] = { 2618, 2619, 2620, 2621, 2622, 2623, 2624, 2625, 2626, 2627, 2628, 2629, 2630 };
    double y3[13] = { 21098, 56078, 239902, 484110, 529176, 435543, 405634, 360014, 257055, 179220, 107862, 57059, 32137 };
    double e_y3[13] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    TGraphErrors* gr3 = new TGraphErrors(13, x3, y3, e_y3, NULL);

    ct->cd(3);
    gr3->SetMarkerStyle(20);
    gr3->SetMarkerColor(1);
    gr3->SetLineColor(1);
    gr3->GetXaxis()->SetTitle("Pixel");
    gr3->GetYaxis()->SetTitle("Intensidade");
    gr3->SetTitle("Regi#tilde{a}o I");
    gr3->Draw("APE");
    gr3->Fit("gaus");

    TLegend* l3 = new TLegend(0.1, 0.7, 0.28, 0.9);
    l3->SetHeader("Legenda", "C");
    l3->AddEntry("NULL", "M#acute{e}dia = 2623");
    l3->AddEntry("NULL", "#sigma = 3");
    l3->Draw();

    // --- REGION II.1 ---
    double x4[10] = { 3040, 3041, 3042, 3043, 3044, 3045, 3046, 3047, 3048, 3049 };
    double y4[10] = { 27576, 36020, 52733, 75973, 100457, 117570, 125214, 123430, 116372, 105147 };
    double e_y4[10] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    TGraphErrors* gr4 = new TGraphErrors(10, x4, y4, e_y4, NULL);

    ct->cd(4);
    gr4->SetMarkerStyle(20);
    gr4->SetMarkerColor(1);
    gr4->SetLineColor(1);
    gr4->GetXaxis()->SetTitle("Pixel");
    gr4->GetYaxis()->SetTitle("Intensidade");
    gr4->SetTitle("Regi#tilde{a}o II");

    gr4->Draw("APE");
    gr4->Fit("gaus");

    TLegend* l4 = new TLegend(0.1, 0.7, 0.28, 0.9);
    l4->SetHeader("Legenda", "C");
    l4->AddEntry("NULL", "M#acute{e}dia = 3046");
    l4->AddEntry("NULL", "#sigma = 4");
    l4->Draw();

    // --- REGION II.2 ---
    double x5[17] = { 3050, 3051, 3052, 3053, 3054, 3055, 3056, 3057, 3058, 3059, 3060, 3061, 3062, 3063, 3064, 3065, 3066 };
    double y5[17] = { 95030, 89099, 90306, 100445, 124238, 164667, 215282, 277543, 318256, 330912, 323440, 300656, 271883, 232777, 197149, 170979, 160128 };
    double e_y5[17] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

    TGraphErrors* gr5 = new TGraphErrors(17, x5, y5, e_y5, NULL);

    ct->cd(5);
    gr5->SetMarkerStyle(20);
    gr5->SetMarkerColor(1);
    gr5->SetLineColor(1);
    gr5->GetXaxis()->SetTitle("Pixel");
    gr5->GetYaxis()->SetTitle("Intensidade");
    gr5->SetTitle("Regi#tilde{a}o II");

    gr5->Draw("APE");
    gr5->Fit("gaus");

    TLegend* l5 = new TLegend(0.1, 0.7, 0.28, 0.9);
    l5->SetHeader("Legenda", "C");
    l5->AddEntry("NULL", "M#acute{e}dia = 3059");
    l5->AddEntry("NULL", "#sigma = 5");
    l5->Draw();

    // --- REGION II.3 (Broad Peak / Saturation study) ---
    double x6[45] = { 3067, 3068, 3069, 3070, 3071, 3072, 3073, 3074, 3075, 3076, 3077, 3078, 3079, 3080, 3081, 3082, 3083, 3084, 3085, 3086, 3087, 3088, 3089, 3090, 3091, 3092, 3093, 3094, 3095, 3096, 3097, 3098, 3099, 3100, 3101, 3102, 3103, 3104, 3105, 3106, 3107, 3108, 3109, 3110, 3111 };
    double y6[45] = { 161589, 180767, 226273, 316394, 459282, 642882, 747801, 768991, 352211, 60921, 4295, 14267, 52319, 119247, 226883, 472731, 702582, 763756, 769978, 770179, 769573, 769383, 768846, 768409, 576093, 408819, 370169, 360214, 333763, 302255, 280688, 265548, 251555, 240363, 234500, 227673, 217641, 207094, 194736, 181313, 167948, 152790, 136335, 120400, 104783 };
    double e_y6[45];
    for(int i=0; i<45; i++) e_y6[i] = 1.0;

    TGraphErrors* gr6 = new TGraphErrors(45, x6, y6, e_y6, NULL);

    ct->cd(6);
    gr6->SetMarkerStyle(20);
    gr6->SetMarkerColor(1);
    gr6->SetLineColor(1);
    gr6->GetXaxis()->SetTitle("Pixel");
    gr6->GetYaxis()->SetTitle("Intensidade");
    gr6->SetTitle("Regi#tilde{a}o II");

    gr6->Draw("APE");
    gr6->Fit("gaus");

    TLegend* l6 = new TLegend(0.1, 0.7, 0.28, 0.9);
    l6->SetHeader("Legenda", "C");
    l6->AddEntry("NULL", "M#acute{e}dia = 3087");
    l6->AddEntry("NULL", "#sigma = 10");
    l6->Draw();
}
