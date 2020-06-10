{
gROOT->SetStyle("Plain");
gStyle->SetMarkerStyle(20);
TH1F *spec = new TH1F("spec","electron spectrum",3000,1,6000);
spec->GetXaxis()->SetTitle("Energy [keV]");
spec->GetYaxis()->SetTitle("Counts");
TTree *t= new TTree();
t->ReadFile("output.dat","event:energy:x:y:z");
t->Draw("energy >> spec");
}