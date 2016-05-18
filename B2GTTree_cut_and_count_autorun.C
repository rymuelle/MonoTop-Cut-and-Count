#define B2GTTree_cut_and_count_cxx
#include "B2GTTree_cut_and_count.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void B2GTTree_cut_and_count::Loop()
{
//   In a ROOT session, you can do:
//      Root > .L B2GTTree_cut_and_count.C
//      Root > B2GTTree_cut_and_count t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;


   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
    //std::cout << mu_Pt[0] << std::endl;
    //
    if(Precut(jentry)){
      //  std::cout << "passed Precut" << std::endl;
        fill_plots(PreCut_analysis_plots);
        if(Signal(jentry)){
            //Signal
        }
        if(WJet(jentry)){
          //w Jet
        } 
        if(TTBar(jentry)){
            //ttbar
        } 
        if(extra(jentry)){
            //ttbar
        } 
    }




   }
    
}
//  148     m.Precut_cutflow.push_back(cut_flow_count("all events wjet"));
//  149     m.Precut_cutflow.push_back(cut_flow_count("eactly one muon"));
//  150     m.Precut_cutflow.push_back(cut_flow_count("leading jet pt > 10 GeV"));
bool B2GTTree_cut_and_count::Precut(Long64_t jentry){
    bool keep_event = false;
    bool no_other_muon_electron = true;

    //no other leptons  NOT COMPLETED!!!!!!!!! work and shit
    for(int i = 1; i < sizeof(mu_Pt)/sizeof(mu_Pt[0]); i++){
        if(mu_Pt[i] > 33 and abs(mu_Eta[i]) < 2.1 and mu_Iso04[i] < .12 and no_other_muon_electron){
            no_other_muon_electron = false;
            std::cout << mu_Pt[i] << std::endl;
        }
    }

    //no other leptons  NOT COMPLETED!!!!!!!!! work and shit
    for(int i = 0; i < sizeof(el_Pt)/sizeof(el_Pt[0]); i++){
        if(el_Pt[i] > 20 and abs(el_Eta[i]) < 2.5 and el_Iso03[i] < .20 and no_other_muon_electron){
            no_other_muon_electron = false;
            std::cout << el_Pt[i] << std::endl;
        }
    }
    
    
    Precut_cutflow[0].iterate();
    if( mu_Pt[0] > 33 and abs(mu_Eta[0]) < 2.1 and mu_Iso04[0] < .12 and no_other_muon_electron){ 
        Precut_cutflow[1].iterate();
        if(jetAK4_Pt[0] > 50){
            Precut_cutflow[2].iterate();
            keep_event = true;
        }
    }

    if(jentry ==998){
        for(int i = 0; i < Precut_cutflow.size(); i++){
            std::cout << "name: " << Precut_cutflow[i].cut_name << " cut count: " << Precut_cutflow[i].cut_count << std::endl;
        }
    }

    return keep_event;
}

bool B2GTTree_cut_and_count::Signal(Long64_t jentry){
    bool keep_event = false;
    if( mu_Pt[0] > 10){
        keep_event = true;
    }
    return keep_event;
}

bool B2GTTree_cut_and_count::WJet(Long64_t jentry){
    bool keep_event = false;
    if( mu_Pt[0] > 10){
        keep_event = true;
    }
    return keep_event;
}

bool B2GTTree_cut_and_count::TTBar(Long64_t jentry){
    bool keep_event = false;
    if( mu_Pt[0] > 10){
        keep_event = true;
    }
    return keep_event;
}

bool B2GTTree_cut_and_count::extra(Long64_t jentry){
    bool keep_event = false;
    if( mu_Pt[0] > 10){
        keep_event = true;
    }
    return keep_event;
}


void B2GTTree_cut_and_count_autorun(){

    B2GTTree_cut_and_count m;
    //initilze cutflow for precut
    m.Precut_cutflow.push_back(cut_flow_count("all events wjet"));
    m.Precut_cutflow.push_back(cut_flow_count("eactly one muon"));
    m.Precut_cutflow.push_back(cut_flow_count("jet cut"));

    //initilize plots
    m.PreCut_analysis_plots = new analysis_plots("WJET_precut");

    m.Loop();
    
    m.Draw_plots(m.PreCut_analysis_plots);
}

