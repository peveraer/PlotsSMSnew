#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TClonesArray.h>
#include <TString.h>
#include <TBenchmark.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <TFile.h>
#include <TH1F.h>
#include <TTree.h>
#include <TLorentzVector.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TList.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#endif

void convert_TMultiGraph(){

  TFile * inputFile=new TFile("T2QQ_alphaT.root");
  TMultiGraph *mg= (TMultiGraph*) inputFile->FindObjectAny("expected_total");
  TList* grlist;
  grlist = mg->GetListOfGraphs();
  TIter next(grlist);
  TObject *obj;
  obj= next();
  TGraph *expected_total=(TGraph*)obj;

 TMultiGraph *mg2= (TMultiGraph*) inputFile->FindObjectAny("observed_total");
  TList* grlist2;
  grlist2 = mg2->GetListOfGraphs();
  TIter next2(grlist2);
  TObject *obj2;
  obj2= next2();
  TGraph *observed_total=(TGraph*)obj2;

  TFile * outputFile=new TFile("T2QQ_alphaT_v2.root","RECREATE");
  outputFile->cd();
  expected_total->Write("expected_total");
  observed_total->Write("observed_total");

}
