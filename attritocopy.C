// Builds a graph with errors, displays it and saves it as an image
void setStylecopy(){
  gROOT->SetStyle("Plain");
  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(111);
  gStyle->SetPalette(57);
  gStyle->SetOptTitle(0);
}

void attritocopy(){
    setStyle();
    // The values and the errors on the X and Y axis
    const int n_points=4;
    double x_vals[n_points]=
            {0.300728,0.337023,0.355101,0.440271};
    double y_vals[n_points]=
            {2.5062,4.9597,7.216,13.8764};
    
   double x_errs[n_points]=
            {0.022838,0.015549,0.0111792,0.010418};
    double y_errs[n_points]=
            {0.2246,0.2344,0.2391,0.2718};

    // Instance of the graph
    TGraphErrors * graph =new TGraphErrors(n_points,x_vals,y_vals,x_errs,y_errs);
    graph->SetTitle("Coefficiente di attrito legno;tan#Phi; #Deltax/cos#Phi (cm)");
    graph->GetYaxis()->SetRangeUser(1,16);//range asse y
    // Cosmetics
    graph->SetMarkerStyle(kOpenCircle);
    graph->SetMarkerColor(kBlue);
    graph->SetLineColor(kBlue);

    // The canvas on which we'll draw the graph
    TCanvas *mycanvas = new TCanvas();


    // Define a linear function
    TF1 *f = new TF1("Linear law","([1]*x)+[0]",0.2,1.2);
    // Let's make the function line nicer
    f->SetLineColor(kRed); f->SetLineStyle(2);
    // Fit it to the graph and draw it
    f->SetParName(0,"A"); //attrito
    f->SetParName(1,"B"); 
    graph->Fit(f);

    // Draw the graph !
    graph->Draw("APE");

    cout << "x and y measurements correlation =" <<graph->GetCorrelationFactor()<<endl;
    cout << "The Chisquare of the fit = "<< graph->Chisquare(f)<<endl;
    cout << "Chisquare from function  "<<f->GetChisquare()<<endl;
    cout << "NDF from function  "<<f->GetNDF()<<endl;
 
   // Build and Draw a legend
    TLegend *leg=new TLegend(.1,.7,.3,.9);
    leg->SetFillColor(0);
    graph->SetFillColor(0);
    leg->AddEntry(graph,"Punti Sperimentali");
    leg->AddEntry(f,"Fit Lineare");
    leg->Draw("Same");

    mycanvas->Print("Attrito.gif");
}
