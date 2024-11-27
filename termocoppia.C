#include "TGraphErrors.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TAxis.h"
#include "TF1.h"

void termocoppia()
{

  //
  // Canvas dove il grafico verra' disegnato
  // (dimensione : 500 x 500) ed opzioni di stile (griglie, colore di sfondo, ...)
  //
  
  TCanvas *canvas = new TCanvas ("canvas", "Calibrazione termocoppia", 700, 500);
  gStyle->SetCanvasColor(0);
  gStyle->SetStatBorderSize(1);
  canvas->SetGrid(true);

  //
  // Grafico y(x), con barre di errore con punti ed errori
  // (indice del punto, coordinata x, coordinata y) aggiunti uno ad uno
  // NOTA: l'indice dei punti comincia da 0 
  //
  
  TGraphErrors *graph = new TGraphErrors();

  graph->SetPoint(0,99.73, 2.84);
  graph->SetPointError(0, 0., 0.03);

  graph->SetPoint(1,89.84, 2.39);
  graph->SetPointError(1, 0., 0.03);

  graph->SetPoint(2,80.40, 2.00);
  graph->SetPointError(2,  0., 0.03);

  graph->SetPoint(3,70.08, 1.54);
  graph->SetPointError(3, 0., 0.03);

  graph->SetPoint(4,60.57, 1.16);
  graph->SetPointError(4, 0., 0.03);

  graph->SetPoint(5,50.62,0.76 );
  graph->SetPointError(5, 0., 0.03);



  //
  // Disegno del grafico, definizione del marker per i punti e titoli degli assi
  //

  graph->SetMarkerStyle(1);
  graph->GetXaxis()->SetTitle("temperatura [#circC]"); 
  graph->GetYaxis()->SetTitle("ddp [mV]"); 

  graph->Draw("AP");
  
  //
  // Funzione polinomiale di ordine 1 con parametri [0] = intercetta , [1] = pendenza 
  // e fit lineare della funzione usando i punti del grafico
  //

  TF1 *func = new TF1("func","pol1");
  gStyle->SetOptFit(0111);
  graph->Fit("func");
  
}
