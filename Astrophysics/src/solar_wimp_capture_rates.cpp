// solar_wimp_capture_rates.cpp
// Calculation of WIMP capture rates by the Sun for different chemical elements.
// Research supported by FAPESP.
// Ref: Jungman et al. (1996)

#include <iostream>
#include "TCanvas.h"
#include "TROOT.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TLegend.h"
#include "TArrow.h"
#include "TLatex.h"

// General constants used in the model
double vesc = 1156;    // Escape velocity [km/s]
double vtil = 270;     // Dispersion velocity [km/s]
double v_x = 270;      // WIMP velocity [km/s] (Ref.: Jungman)
double p_x = 0.4;      // Local DM density [GeV]
double sigma = 10e-44; // Cross-section [cm²]
double mn = 0.939;     // Nucleon mass [GeV] (Ref.: Nist Codata)

// --- HYDROGEN (H) ---
double mH = mn;
Double_t yH(double x) { return x / mH; }
Double_t mrNH(double x) { return (x * mH) / (x + mH); }
Double_t mrnH(double x) { return (x * mn) / (x + mn); }
Double_t AH(double x) { return (3 * yH(x) * pow(vesc, 2)) / (2 * TMath::Power(yH(x) - 1, 2) * pow(vtil, 2)); }
Double_t SH(double x) { return TMath::Power((TMath::Power(AH(x), 1.5)) / (1 + (TMath::Power(AH(x), 1.5))), 1 / 1.5); }
Double_t FH(double x) { return 1; }
Double_t sigH(double x) { return pow(1, 2) * TMath::Power(mrNH(x), 2) * sigma / TMath::Power(mrnH(x), 2); }
Double_t sumH(double x) { return (FH(x) * sigH(x) * 0.7352 * 3.16 * SH(x)) / (mH * (10e-40)); }

// --- HELIUM-4 (He) ---
double mHe = 4*mn;
Double_t yHe(double x){return x / mHe;}
Double_t mrNHe(double x) {return (x * mHe) / (x + mHe);}
Double_t mrnHe(double x) {return (x * mn) / (x + mn);}
Double_t AHe(double x) {return (3 * yHe(x) * pow(vesc, 2)) / (2 * TMath::Power(yHe(x) - 1, 2) * pow(vtil, 2));}
Double_t SHe(double x) {return TMath::Power((TMath::Power(AHe(x), 1.5)) / (1 + (TMath::Power(AHe(x), 1.5))), 1 / 1.5);}
Double_t FHe(double x) {return 0.986 + (1 - 0.986) * TMath::Exp(-(TMath::Power((TMath::Log(x)) / (TMath::Log(18.2)), 1.58)));}
Double_t sigHe(double x) {return pow(4, 2) * TMath::Power(mrNHe(x), 2) * sigma / TMath::Power(mrnHe(x), 2);}
Double_t sumHe(double x) {return (FHe(x) * sigHe(x) * 0.2485 * 3.4 * SHe(x) * pow(10,40)) / mHe;}
Double_t CHe(double x) {return 4.8 * (10e24) * (p_x / 0.3) * (270 / v_x) * (sumHe(x) / x);}

// --- CARBON (C) ---
double mC = 12*mn;
Double_t yC(double x) { return x / mC; }
Double_t mrNC(double x) { return (x * mC) / (x + mC); }
Double_t mrnC(double x) { return (x * mn) / (x + mn); }
Double_t AC(double x) { return (3 * yC(x) * pow(vesc, 2)) / (2 * TMath::Power((yC(x) - 1), 2) * pow(vtil, 2)); }
Double_t SC(double x) { return TMath::Power((TMath::Power(AC(x), 1.5)) / (1 + (TMath::Power(AC(x), 1.5))), (1 / 1.5)); }
Double_t FC(double x) { return 0.788 + (1 - 0.788) * TMath::Exp(-(TMath::Power((TMath::Log(x)) / (TMath::Log(61.6)), 2.69))); }
Double_t sigC(double x) { return pow(12, 2) * TMath::Power(mrNC(x), 2) * sigma / TMath::Power(mrnC(x), 2); }
Double_t sumC(double x) { return (FC(x) * sigC(x) * (3.87 * 10e-3) * 3.23 * SC(x)) / (mC * (10e-40)); }
Double_t CC(double x) { return 4.8 * (10e24) * (p_x / 0.3) * (270 / v_x) * (sumC(x) / x); }

// --- NITROGEN (N) ---
double mN = 14*mn;
Double_t yN(double x) { return x / mN; }
Double_t mrNN(double x) { return (x * mN) / (x + mN); }
Double_t mrnN(double x) { return (x * mn) / (x + mn); }
Double_t AN(double x) { return (3 * yN(x) * pow(vesc, 2)) / (2 * TMath::Power(yN(x) - 1, 2) * pow(vtil, 2)); }
Double_t SN(double x) { return TMath::Power((TMath::Power(AN(x), 1.5)) / (1 + (TMath::Power(AN(x), 1.5))), 1 / 1.5); }
Double_t FN(double x) { return 0.613 + (1 - 0.613) * TMath::Exp(-(TMath::Power((TMath::Log(x)) / (TMath::Log(75.2)), 2.69))); }
Double_t sigN(double x) { return pow(14, 2) * TMath::Power(mrNN(x), 2) * sigma / TMath::Power(mrnN(x), 2); }
Double_t sumN(double x) { return (FN(x) * sigN(x) * 6.91 * (10e-4) * 3.23 * SN(x)) / (mN * (10e-40)); }
Double_t CN(double x) { return 4.8 * (10e24) * (p_x / 0.3) * (270 / v_x) * (sumN(x) / x); }

// --- OXYGEN (O) ---
double mO =  16*mn;
Double_t yO(double x) { return x / mO; }
Double_t mrNO(double x) { return (x * mO) / (x + mO); }
Double_t mrnO(double x) { return (x * mn) / (x + mn); }
Double_t AO(double x) { return (3 * yO(x) * pow(vesc, 2)) / (2 * TMath::Power(yO(x) - 1, 2) * pow(vtil, 2)); }
Double_t SO(double x) { return TMath::Power((TMath::Power(AO(x), 1.5)) / (1 + (TMath::Power(AO(x), 1.5))), 1 / 1.5); }
Double_t FO(double x) { return 0.613 + (1 - 0.613) * TMath::Exp(-(TMath::Power((TMath::Log(x)) / (TMath::Log(75.2)), 2.69))); }
Double_t sigO(double x) { return pow(16, 2) * TMath::Power(mrNO(x), 2) * sigma / TMath::Power(mrnO(x), 2); }
Double_t sumO(double x) { return (FO(x) * sigO(x) * 5.72 * (10e-3) * 3.23 * SO(x)) / (mO * (10e-40)); }
Double_t CO(double x) { return 4.8 * (10e24) * (p_x / 0.3) * (270 / v_x) * (sumO(x) / x); }

// --- NEON (Ne) ---
double mNe = 20*mn;
Double_t yNe(double x) { return x / mNe; }
Double_t mrNNe(double x) { return (x * mNe) / (x + mNe); }
Double_t mrnNe(double x) { return (x * mn) / (x + mn); }
Double_t ANe(double x) { return (3 * yNe(x) * pow(vesc, 2)) / (2 * TMath::Power(yNe(x) - 1, 2) * pow(vtil, 2)); }
Double_t SNe(double x) { return TMath::Power((TMath::Power(ANe(x), 1.5)) / (1 + (TMath::Power(ANe(x), 1.5))), 1 / 1.5); }
Double_t FNe(double x) { return 0.613 + (1 - 0.613) * TMath::Exp(-(TMath::Power((TMath::Log(x)) / (TMath::Log(75.2)), 2.69))); }
Double_t sigNe(double x) { return pow(20, 2) * TMath::Power(mrNNe(x), 2) * sigma / TMath::Power(mrnNe(x), 2); }
Double_t sumNe(double x) { return (FNe(x) * sigNe(x) * 1.25 * (10e-3) * 3.23 * SNe(x)) / (mNe * (10e-40)); }
Double_t CNe(double x) { return 4.8 * (10e24) * (p_x / 0.3) * (270 / v_x) * (sumNe(x) / x); }

// --- MAGNESIUM (Mg) ---
double mMg = 24*mn;
Double_t yMg(double x) { return x / mMg; }
Double_t mrNMg(double x) { return (x * mMg) / (x + mMg); }
Double_t mrnMg(double x) { return (x * mn) / (x + mn); }
Double_t AMg(double x) { return (3 * yMg(x) * pow(vesc, 2)) / (2 * TMath::Power(yMg(x) - 1, 2) * pow(vtil, 2)); }
Double_t SMg(double x) { return TMath::Power((TMath::Power(AMg(x), 1.5)) / (1 + (TMath::Power(AMg(x), 1.5))), 1 / 1.5); }
Double_t FMg(double x) { return 0.281 + (1 - 0.281) * TMath::Exp(-(TMath::Power((TMath::Log(x)) / (TMath::Log(71.7)), 2.97))); }
Double_t sigMg(double x) { return pow(24, 2) * TMath::Power(mrNMg(x), 2) * sigma / TMath::Power(mrnMg(x), 2); }
Double_t sumMg(double x) { return (FMg(x) * sigMg(x) * 7.06 * (10e-4) * 3.23 * SMg(x)) / (mMg * (10e-40)); }
Double_t CMg(double x) { return 4.8 * (10e24) * (p_x / 0.3) * (270 / v_x) * (sumMg(x) / x); }

// --- SILICON (Si) ---
double mSi = 28*mn;
Double_t ySi(double x) { return x / mSi; }
Double_t mrNSi(double x) { return (x * mSi) / (x + mSi); }
Double_t mrnSi(double x) { return (x * mn) / (x + mn); }
Double_t ASi(double x) { return (3 * ySi(x) * pow(vesc, 2)) / (2 * TMath::Power(ySi(x) - 1, 2) * pow(vtil, 2)); }
Double_t SSi(double x) { return TMath::Power((TMath::Power(ASi(x), 1.5)) / (1 + (TMath::Power(ASi(x), 1.5))), 1 / 1.5); }
Double_t FSi(double x) { return 0.281 + (1 - 0.281) * TMath::Exp(-(TMath::Power((TMath::Log(x)) / (TMath::Log(71.7)), 2.97))); }
Double_t sigSi(double x) { return pow(28, 2) * TMath::Power(mrNSi(x), 2) * sigma / TMath::Power(mrnSi(x), 2); }
Double_t sumSi(double x) { return (FSi(x) * sigSi(x) * 6.63 * (10e-4) * 3.23 * SSi(x)) / (mSi * (10e-40)); }
Double_t CSi(double x) { return 4.8 * (10e24) * (p_x / 0.3) * (270 / v_x) * (sumSi(x) / x); }

// --- SULFUR (S) ---
double mS = 32*mn;
Double_t yS(double x) { return x / mS; }
Double_t mrNS(double x) { return (x * mS) / (x + mS); }
Double_t mrnS(double x) { return (x * mn) / (x + mn); }
Double_t AS(double x) { return (3 * yS(x) * pow(vesc, 2)) / (2 * TMath::Power(yS(x) - 1, 2) * pow(vtil, 2)); }
Double_t SS(double x) { return TMath::Power((TMath::Power(AS(x), 1.5)) / (1 + (TMath::Power(AS(x), 1.5))), 1 / 1.5); }
Double_t FS(double x) { return 0.101 + (1 - 0.101) * TMath::Exp(-(TMath::Power((TMath::Log(x)) / (TMath::Log(57)), 3.1))); }
Double_t sigS(double x) { return pow(32, 2) * TMath::Power(mrNS(x), 2) * sigma / TMath::Power(mrnS(x), 2); }
Double_t sumS(double x) { return (FS(x) * sigS(x) * 3.08 * (10e-4) * 3.23 * SS(x)) / (mS * (10e-40)); }
Double_t CS(double x) { return 4.8 * (10e24) * (p_x / 0.3) * (270 / v_x) * (sumS(x) / x); }

// --- IRON (Fe) ---
double mFe = 56*mn;
Double_t yFe(double x) {return x / mFe;}
Double_t mrNFe(double x) {return (x * mFe) / (x + mFe);}
Double_t mrnFe(double x) {return (x * mn) / (x + mn);}
Double_t AFe(double x) {return (3 * yFe(x) * pow(vesc, 2)) / (2 * TMath::Power(yFe(x) - 1, 2) * pow(vtil, 2));}
Double_t SFe(double x) {return TMath::Power((TMath::Power(AFe(x), 1.5)) / (1 + (TMath::Power(AFe(x), 1.5))), 1 / 1.5);}
Double_t FFe(double x) { return 0.00677 + (1 - 0.00677) * TMath::Exp(-(TMath::Power((TMath::Log(x)) / (TMath::Log(29.3)), 3.36))); }
Double_t sigFe(double x) {return pow(56, 2) * TMath::Power(mrNFe(x), 2) * sigma / TMath::Power(mrnFe(x), 2);}
Double_t sumFe(double x) {return (FFe(x) * sigFe(x) * 1.29 * (10e-3) * 3.23 * SFe(x)) / (mFe * (10e-40));}
Double_t CFe(double x) {return 4.8 * (10e24) * (p_x / 0.3) * (270 / v_x) * (sumFe(x) / x);}

// --- TOTAL CAPTURE RATE ---
Double_t Ct(double x) {
	return 4.8 * (10e24) * (p_x / 0.3) * (270 / (vtil * x)) * (sumH(x) + sumHe(x) + sumC(x) + sumN(x) + sumO(x) + sumNe(x) + sumMg(x) + sumSi(x) + sumS(x) + sumFe(x));
}

void solar_wimp_capture_rates() {
	TCanvas* c1 = new TCanvas();
	gPad->SetLogx();
	gPad->SetLogy();
	
	// Plot for Helium-4
	TF1* C_He = new TF1("C_He", "CHe(x)", 10, 1000);
	C_He->SetTitle("WIMP Solar Capture Rate;WIMP Mass (GeV);Capture Rate (s^{-1})");
	C_He->Draw();
	C_He->SetLineStyle(5);
	C_He->SetLineColor(kBlue);

	// Plot for Iron
	TF1* C_Fe = new TF1("C_Fe", "CFe(x)", 10, 1000);
	//C_Fe->Draw("same");
	C_Fe->SetLineStyle(5);
	C_Fe->SetLineColor(kYellow+2);

	// Plot for Carbon
	TF1* C_C = new TF1("C_C", "CC(x)", 10, 1000);
	C_C->Draw("same");
	C_C->SetLineStyle(5);
	C_C->SetLineColor(kRed);

	// Plot for Nitrogen
	TF1* C_N = new TF1("C_N", "CN(x)", 10, 1000);
	C_N->Draw("same");
	C_N->SetLineStyle(5);
	C_N->SetLineColor(kGreen);

	// Plot for Oxygen
	TF1* C_O = new TF1("C_O", "CO(x)", 10, 1000);
	C_O->Draw("same");
	C_O->SetLineStyle(5);
	C_O->SetLineColor(kGreen+2);

	// Plot for Neon
	TF1* C_Ne = new TF1("C_Ne", "CNe(x)", 10, 1000);
	C_Ne->Draw("same");
	C_Ne->SetLineStyle(5);
	C_Ne->SetLineColor(kCyan);

	// Plot for Total Capture Rate
	TF1* C_Ct = new TF1("C_Ct", "Ct(x)", 10, 1000);
	C_Ct->Draw("same");
	C_Ct->SetLineStyle(1);
	C_Ct->SetLineColor(kBlack);
}

#ifndef __CINT__
int main() {
	solar_wimp_capture_rates();
}
#endif
