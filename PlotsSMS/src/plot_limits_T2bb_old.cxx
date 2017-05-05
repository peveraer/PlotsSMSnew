// plot_limits_summary: Plots various limit curves on same canvas

// System includes
#include <fstream>
#include <iostream>

// ROOT includes
#include "TStyle.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TH1D.h"
#include "TROOT.h"
#include "TPad.h"
#include "TError.h" // Controls error level reporting

// User includes
#include "plot_limits_summary.hpp"

using namespace std;
namespace{
  double cmsH = 0.075;
  float legLineH = 0.039;
  float legTextSize = 0.035;
  float fillTransparency = 0.06;

  TString lsp = "#lower[-0.12]{#tilde{#chi}}#lower[0.2]{#scale[0.85]{^{0}}}#kern[-1.3]{#scale[0.85]{_{1}}}";
  //  int c8TeV(kGray+2);
  //  int cSus15002(kBlue), cSus15003(kOrange), cSus15004(kGreen+3);//, cSus15005(kMagenta+1);
  //int cSus15004_1l(kBlack), cSus15006(kGreen+1), cSus15007(kRed), cSus15008(kCyan+1), cSus16003(kOrange+2);
   int cSus15002(kBlue);
     int cSus15003(kOrange);
    int cSus15004(kGreen+1);
    //    int cSus16002(kGreen+1), cSus16007A(kMagenta+1);
    //    int cSus16007alpha(kRed), cComb(kBlack);//, cSus15007(kRed), cSus15008(kCyan+2);
}

int main(){
  gErrorIgnoreLevel=kWarning; // Turns off ROOT INFO messages

  // Label definitions

  TString lsp("#tilde{#chi}#lower[0.2]{#scale[0.85]{^{0}}}#kern[-1.3]{#scale[0.85]{_{1}}}");
  TString pp_gluglu("pp #rightarrow #tilde{b}#kern[0.3]{#tilde{b}}");
  TString basetitle(pp_gluglu+",  #tilde{b} #rightarrow ");
  TString mj("M#lower[-.1]{_{J}}");
  TString mt2("M#lower[-.1]{_{T2}}"), mht("H_{#lower[-.4]{T}}^{miss}"), aT("#alpha#lower[-.1]{_{T}}");

  // Folder with root files containing the TGraphs
  TString folder("root/limits_2016/");
  vector<model_limits> models;

  ///////////////////////////////    Defining T2tt plot    /////////////////////////////////
 
  models.push_back(model_limits("T2bbold", basetitle+"b#kern[0.4]{"+lsp+"}"));
  models.back().add("SUS-16-014, 0-lep ("+mht+"), 12.9 fb^{-1}", folder+"T2bb_RA2.root", 
  		    cSus15002, "ObsLim", "ExpLim");
 models.back().add("SUS-16-015, 0-lep ("+mt2+"), 12.9 fb^{-1}", folder+"T2bb_MT2.root", 
		    cSus15003, "gr_obs_smoothed", "gr_exp_smoothed");
 models.back().add("SUS-16-016, 0-lep ("+aT+"), 12.9 fb^{-1}", folder+"T2bb_alphaT_v2.root", 
   		    cSus15004, "observed_total", "expected_total");
 //  models.back().add("SUS-15-004, 1-lep (Razor), 2.1 fb^{-1}", folder+"t1tbqq_sus15_004.root", 
 //		    cSus15004_1l, "Obs_T1tttt_MuMultiJet_EleMultiJet", "Exp_T1tttt_MuMultiJet_EleMultiJet");
 //  models.back().add("SUS-16-029, 0-lep stop, 12.9 fb^{-1}", folder+"T2tt_A.root", 
 //		    cSus16007A, "graph_smoothed_Obs", "graph_smoothed_Exp");
 //  models.back().add("SUS-16-030, 0-lep (top tag), 12.9 fb^{-1}", folder+"T2tt_alpha.root", 
 //    		    cSus16007alpha, "combined_obsExclOneTimesProspino_base_BR100pct", "combined_expExclOneTimesProspino_base_BR100pct");
 //  models.back().add("SUS-16-028, 1-lep stop, 12.9 fb^{-1}", folder+"T2tt_1l.root", 
 //    		    cSus16002, "gObsLimit_T2tt", "gExpLimit_T2tt");
 //   models.back().add("", folder+"T2tt_RA2.root", 
 // 		    cSus15002, "ObsLim2", "ExpLim2");
// models.back().add("", folder+"T2tt_1l.root", 
		       //		    cSus16002, "gObsLimit_2_T2tt", "gExpLimit_2_T2tt");
 //  models.back().add("", folder+"T2tt_A.root", 
 //		    cSus16007A, "graph_smoothed_Obs_1", "graph_smoothed_Exp_1");
 //models.back().add("", folder+"T2tt_alpha.root", 
 //		    cSus16007alpha, "combined_obsExclOneTimesProspino_base_BR100pct", "combined_expExclOneTimesProspino_extra_BR100pct");
 // models.back().add("Combination 0-lep and 1-lep stop, 12.9 fb^{-1}", folder+"comb.root", 
 //		    cComb, "gObs", "gExp");

 vector<TString> oldfiles;
 oldfiles.push_back(folder+"T2bb_MT2_old.root");
 oldfiles.push_back(folder+"T2bb_Batool.root");

  vector<TString> graphnames;
  graphnames.push_back("gr_exp_smoothed");
  graphnames.push_back("combined_expExclOneTimesProspino_BR100pct");

  

  //////////////////////////////////////////////////////////////////////////////////////// 
  //////////////////////////////////    Making plots    //////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////// 
  
  // Creating canvas
  gStyle->SetOptStat(0);  
  float lMargin(0.14), tMargin(0.08), rMargin(0.04), bMargin(0.14);
  TCanvas can("canvas","", 600, 600);
  setCanvas(can, lMargin, tMargin, rMargin, bMargin);

  // Creating base legend for observed/expected
  int wobs(4), wexp(4);
  TH1D hobs("hobs","",1,0,1), hexp("hexp","",1,0,1);
  hobs.SetLineColor(1); hobs.SetLineWidth(wobs);
  hexp.SetLineColor(1); hexp.SetLineStyle(2); hexp.SetLineWidth(wexp);
  
  double legX(1-rMargin-0.02), legY(1-tMargin-0.07);
  double legW = 0.2, legH = 0.07;
  TLegend baseleg(legX-legW, legY-legH, legX, legY);
  baseleg.SetTextSize(0.034); baseleg.SetFillColor(0); 
  baseleg.SetFillStyle(0); baseleg.SetBorderSize(0);
  //baseleg.AddEntry(&hobs, "Observed");
  baseleg.AddEntry(&hexp, "Expected");
  //  legX = 0.73;
  TLegend obsleg(legX-legW, legY-legH-0.03, legX, legY-0.04);
  obsleg.SetTextSize(0.034); obsleg.SetFillColor(0); 
  obsleg.SetFillStyle(0); obsleg.SetBorderSize(0);
  obsleg.AddEntry(&hobs, "Observed");

 

  // Looping over each model
  cout<<endl;
  for(size_t imodel(0); imodel < models.size(); imodel++){
    model_limits mod(models[imodel]);

    // Creating base histogram and drawing lumi labels
    float Xmin(300), Xmax(1100), Ymin(0), Ymax(800), glu_lsp;
    getModelParams(mod.model, Xmin, Xmax, Ymin, Ymax, glu_lsp);

    TH2D hbase = baseHistogram(Xmin, Xmax, Ymin, Ymax);
    hbase.Draw();
    addLabelsTitle(lMargin, tMargin, rMargin, mod.title);

    int n_old=oldfiles.size();
    vector<TGraph*> exp_old(n_old);
    for(int it=0;it<n_old;it++){
      TFile flimit(oldfiles[it]);
      exp_old[it] = getGraph(flimit, graphnames[it]);
      exp_old[it]->SetFillColor(kGray);
      exp_old[it]->Draw("f same");
    }


    // Plotting limits
    size_t ncurves(mod.files.size());
    vector<TGraph*> obs(ncurves, 0), exp(ncurves, 0);
    // Getting all graphs first because the ones that come from TCanvas mess up the colors
    for(size_t file(0); file < ncurves; file++){
      TFile flimit(mod.files[file]);
      exp[file] = getGraph(flimit, mod.expnames[file]);
      obs[file] = getGraph(flimit, mod.obsnames[file]);
    }
    for(size_t file(0); file < ncurves; file++){
      setGraphStyle(exp[file], mod.colors[file], 2, wexp, glu_lsp);
      setGraphStyle(obs[file], mod.colors[file], 1, wobs, glu_lsp);
      //      obs[file]->Draw("f same");  //Removed for now

      TString obsname("obs"); obsname += imodel; obsname += file;
      obs[file]->SetName(obsname);
    } // Loop over curves in each model
    // Plotting the lines on top of the fills
    for(size_t file(0); file < ncurves; file++){
      if(exp[file]) exp[file]->Draw("same");
      obs[file]->Draw("same");
    }// Loop over curves in each model

    Float_t diagX2[4] = {95,995,980,80};
    Float_t diagY2[4] = {0,900,900,0};
    TGraph *gdiagonal2 = new TGraph(4, diagX2, diagY2);
    gdiagonal2->SetName("MtopDiagonal");
    gdiagonal2->SetFillColor(kWhite);
    gdiagonal2->SetLineColor(kBlack);
    //    gdiagonal2->Draw("LFSAME");

    // Drawing legends
    baseleg.Draw();
    obsleg.Draw();
    legX = lMargin+0.03; legY = 1-tMargin-cmsH-0.035; //legY = 1-tMargin-cmsH-0.035;
    legW = 0.13; 
    legH = legLineH * ncurves * mod.legScale;
    //legH = legLineH * 6 * mod.legScale;

    TLegend limleg(legX, legY-legH, legX+legW, legY);
    limleg.SetTextSize(legTextSize * mod.legScale); limleg.SetFillColor(0); 
    limleg.SetFillStyle(0); limleg.SetBorderSize(0);
    for(size_t file(0); file < ncurves; file++){
      if(mod.labels[file].Length()<2)  continue;
      limleg.AddEntry(obs[file]->GetName(), mod.labels[file], "l");
    }
    limleg.Draw();
    //    legX=1-rMargin-0.02; legY=1-tMargin-0.07;
    //    legW = 0.4; legH = 0.07;
    TLegend limleg2(legX, legY-legH-legLineH* mod.legScale, legX+legW, legY-legH);
    //    TLegend limleg2(legX, legY-legH, legX+legW, legY);
    limleg2.SetTextSize(legTextSize * mod.legScale); limleg.SetFillColor(0); 
    limleg2.SetFillStyle(0); limleg2.SetBorderSize(0);
    exp_old[0]->SetLineColor(kGray);
    limleg2.AddEntry(exp_old[0], " 2015 exclusion results", "f");
    limleg2.Draw();


    Float_t diagX[4] = {175.+25.,287.5,262.5,175.-25.};
    Float_t diagY[4] = {0,87.5,112.5,0};
    TGraph *gdiagonal = new TGraph(4, diagX, diagY);
    gdiagonal->SetName("MtopDiagonal");
    gdiagonal->SetFillColor(kWhite);
    gdiagonal->SetLineColor(kBlack);
    //    gdiagonal->Draw("LFSAME");



    hbase.Draw("axis same");
    TString plotname(mod.model+"_limits_summary_cms.pdf");
    can.SaveAs(plotname);
    cout<<" open "<<plotname<<endl;
  } // Loop over models
  cout<<endl<<endl;
}


TGraph* getGraph(TFile &flimit, TString gname){
  if(gname == "noplot") return 0;
  TGraph *graph = static_cast<TGraph*>(flimit.Get(gname));
  // If the TGraph is not directly provided in the root file, try to extract it from a TCanvas
  if(graph==0) {
    TPad *current_pad = static_cast<TPad*>(gPad);
    TCanvas *c1 = static_cast<TCanvas*>(flimit.Get("c1"));
    current_pad->cd();
    if(c1==0) {
      cout<<"Could not find graph "<<gname<<" in file "<<flimit.GetName()<<". Exiting!"<<endl<<endl;
      exit(0);
    }
    graph = static_cast<TGraph*>(c1->GetListOfPrimitives()->FindObject(gname));
    if(graph==0) {
      cout<<"Could not find graph "<<gname<<" in file "<<flimit.GetName()<<". Exiting!"<<endl<<endl;
      exit(0);
    }
  }
  return graph;
}

void setGraphStyle(TGraph* graph, int color, int style, int width, double glu_lsp){
  if(graph==0) return;


  // Setting graph style
  graph->SetLineColor(color);
  graph->SetLineStyle(style);
  int fillcolor(color);
  graph->SetFillColor(fillcolor);
  graph->SetFillColorAlpha(fillcolor, fillTransparency);
  graph->SetFillStyle(1001);
  graph->SetLineWidth(width); 
  if(glu_lsp<-100) std::cout<<"Test"<<std::endl;
  
  int np(graph->GetN());
  double mglu,iniglu, endglu, mlsp,mlsp2;
  graph->GetPoint(0, iniglu, mlsp);
  graph->GetPoint(np-1, endglu, mlsp2);
  // Reversing graph if printed towards decreasing mgluino
  if(iniglu-mlsp > endglu-mlsp2) reverseGraph(graph);
  // Adding a point so that it goes down to mLSP = 0
   graph->GetPoint(0, mglu, mlsp);
   //   if(mlsp > mglu-99) graph->SetPoint(0, 100, 0);
  graph->SetPoint(graph->GetN(), max(iniglu,endglu), 0);
  reverseGraph(graph);
  graph->SetPoint(graph->GetN(), 0, 0);
   /*
  reverseGraph(graph);

  //Adding a point at LSP = 0, and removing points beyond the diagonal
  //  int point=0;
  //  while(point<=graph->GetN()){
    for(int point(0); point < np; point++){
    graph->GetPoint(point, mglu, mlsp);
    //      std::cout<<"Found: "<<mlsp<<" "<<mglu<<std::endl;
    if(mlsp > mglu-99.5){
      std::cout<<"Found: "<<mlsp<<" "<<mglu<<std::endl;
      while(point <= graph->GetN()){  //std::cout<<"Found: "<<mlsp<<" "<<mglu<<std::endl;
	//	graph->RemovePoint(point);
	//	 np--;
            graph->RemovePoint(graph->GetN()-1);
	np--;}
	     break;
      
    }
    //point++;
  } 

  //  np++;
  
    glu_lsp=100;

  // Finding intersection of line between last 2 points and mlsp = mglu - glu_lsp
  double x1, y1, x2, y2;
  graph->GetPoint(np-1, x1, y1);
  graph->GetPoint(np-2, x2, y2);
  double slope((y1-y2)/(x1-x2)), offset(y1-slope*x1);
  double intersection((offset+glu_lsp)/(1-slope));

  // Adding extrapolation into the diagonal, and point for mglu = 0
  if(slope!=1) graph->SetPoint(graph->GetN(), intersection, intersection-glu_lsp);
  graph->SetPoint(graph->GetN(), 0, -glu_lsp);
  //cout<<intersection<<endl;
  if(x1 == x2 || y1 == y2 || slope == 1){
    for(int point(0); point < graph->GetN(); point++){
      graph->GetPoint(point, mglu, mlsp);
      //cout<<point<<": "<<mglu<<", "<<mlsp<<endl;
    }
    } 
    graph->SetPoint(graph->GetN(), 100, 0);
   */

}

void reverseGraph(TGraph *graph){
  int np(graph->GetN());
  double mglu, mlsp;
  vector<double> mglus, mlsps;
  for(int point(np-1); point >= 0; point--){
    graph->GetPoint(point, mglu, mlsp);
    mglus.push_back(mglu);
    mlsps.push_back(mlsp);
  }
  for(int point(0); point < np; point++)
    graph->SetPoint(point, mglus[point], mlsps[point]);
}

void getModelParams(TString model, float &Xmin, float &Xmax, float &Ymin, float &Ymax, float &glu_lsp){
  if(model == "T1tttt"){
    Xmin = 600; Xmax = 1950;
    Ymin = 0;   Ymax = 2085;
    glu_lsp = 225;
  }
  if(model == "T1tttt_leptonic"){
    Xmin = 600; Xmax = 1950;
    Ymin = 0;   Ymax = 1785;
    glu_lsp = 225;
  }
  if(model == "T1tttt_hadronic"){
    Xmin = 600; Xmax = 1950;
    Ymin = 0;   Ymax = 1785;
    glu_lsp = 225;
  }
  if(model == "T1bbbb"){
    Xmin = 600; Xmax = 1950;
    Ymin = 0;   Ymax = 1885;
    glu_lsp = 25;
  }    
  if(model == "T1qqqq"){
    Xmin = 600; Xmax = 1950;
    Ymin = 0;   Ymax = 1750;
    glu_lsp = 25;
  }    
}


void setCanvas(TCanvas &can, float lMargin, float tMargin, float rMargin, float bMargin){
  can.SetLogz();
  can.SetTickx(1);
  can.SetTicky(1);
  can.SetLeftMargin(lMargin);
  can.SetTopMargin(tMargin);
  can.SetRightMargin(rMargin);
  can.SetBottomMargin(bMargin);
}

void addLabelsTitle(float lMargin, float tMargin, float rMargin, TString title){
  TLatex label; label.SetNDC();  
  // Printing CMS Preliminary
  double offsetx(0.025), ycms(1-tMargin-cmsH);
  label.SetTextAlign(11); label.SetTextFont(61); label.SetTextSize(0.75*tMargin);
  label.DrawLatex(lMargin+offsetx, ycms, "CMS");
  label.SetTextAlign(11); label.SetTextFont(52); label.SetTextSize(0.038);
  label.DrawLatex(0.27+offsetx, ycms, "Preliminary");
  // Printing top title
  label.SetTextAlign(22); label.SetTextFont(42); label.SetTextSize(0.6*tMargin);
  label.DrawLatex((1-rMargin-lMargin)/2.+lMargin-0.05, 1-tMargin/2., title);
  //  label.DrawLatex(lMargin+offsetx, 1-tMargin/2., title);

  // Printing date
  label.SetTextAlign(31); label.SetTextFont(52); label.SetTextSize(0.45*tMargin);
  label.DrawLatex(1-rMargin-0.02, 1-tMargin+0.018, "ICHEP 2016");
  label.SetTextFont(41); label.SetTextSize(0.6*tMargin);
  label.DrawLatex(1-rMargin-0.04,1-tMargin-0.07,"13 TeV");
}

TH2D baseHistogram(float Xmin, float Xmax, float Ymin, float Ymax){
  TH2D hbase("hbase", "", 1, Xmin, Xmax, 1, Ymin, Ymax);
  hbase.GetXaxis()->SetLabelFont(42);
  hbase.GetXaxis()->SetLabelSize(0.035);
  hbase.GetXaxis()->SetTitleFont(42);
  hbase.GetXaxis()->SetTitleSize(0.05);
  hbase.GetXaxis()->SetTitleOffset(1.2);
  hbase.GetXaxis()->SetTitle("m#kern[0.12]{_{#lower[-0.12]{#tilde{b}}}} [GeV]");
  hbase.GetYaxis()->SetLabelFont(42);
  hbase.GetYaxis()->SetLabelSize(0.035);
  hbase.GetYaxis()->SetTitleFont(42);
  hbase.GetYaxis()->SetTitleSize(0.05);
  hbase.GetYaxis()->SetTitleOffset(1.3);
  hbase.GetYaxis()->SetTitle("m#kern[0.12]{_{"+lsp+"}} [GeV]");
  return hbase;
}

void model_limits::add(TString label, TString file, int color, TString obsname, TString expname){
  labels.push_back(label);
  files.push_back(file);
  obsnames.push_back(obsname);
  expnames.push_back(expname);
  colors.push_back(color);
}

model_limits::model_limits(TString imodel, TString ititle, float ilegScale):
  model(imodel),
  title(ititle),
  legScale(ilegScale){
  }
