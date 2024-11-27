#include "TCanvas.h"
#include "TStyle.h"
#include "TAxis.h"
#include "TH1F.h"
#include "TF1.h"

void maxwell()
{
  
  //
  // Canvas dove il grafico verra' disegnato
  // (dimensione : 500 x 500) ed opzioni di stile (griglie, colore di sfondo, ...)
  //
  
  TCanvas *canvas = new TCanvas ("canvas", "tempi di caduta", 700, 500);
  gStyle->SetCanvasColor(0);
  gStyle->SetStatBorderSize(1);
  canvas->SetGrid(true);

  //
  // Istogramma nBins = numero di bins , xMin(Max) = minimo (massimo) per l'asse x
  // riempito col numero di occorrenze per bin normalizzate a numero_di_misure * largezza_del_bin
  //

  Int_t nBins = 8;
  Int_t nMeas = 40;
  
  Float_t binWidth = 0.1;
  Float_t xMin = 6.85;
  Float_t xMax = 7.65;

  Float_t scale = nMeas * binWidth;

  TH1F * histo = new TH1F("histo","Tempi di caduta",nBins,xMin,xMax);

  histo->Fill(6.9, 0.0/scale);	   
  histo->Fill(7.0, 7.0/scale);
  histo->Fill(7.1, 9.0/scale);
  histo->Fill(7.2, 15.0/scale);
  histo->Fill(7.3, 5.0/scale);
  histo->Fill(7.4, 3.0/scale);
  histo->Fill(7.5, 1.0/scale);
  histo->Fill(7.6, 0.0/scale);


  histo->GetXaxis()->SetTitle("tempo [s]");
  histo->GetYaxis()->SetTitle("#Phi [s^{-1}]"); 
  histo->SetFillColor(kAzure + 2); 

  histo->Draw("HIST");

  //
  // Funzione gaussiana nell'intervallo [xMin,xMax] : 
  // [0]/(sqrt(2*pi_greco)*[2]) * exp(-0.5*((x-[1])/[2])^2) )
  //

  TF1 *func = new TF1("func", "gausn", xMin, xMax);

  //
  // Parametri [0] = area , [1] = media, [2] = sigma
  // calcolati con le informazioni dei tempi di caduta
  //

  func->SetParameter(0, 1.);
  func->SetParameter(1, 7.1775);
  func->SetParameter(2, 0.125038);

  func->SetLineColor(kGreen + 2); 
  func->Draw("same");

}
