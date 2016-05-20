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
        if( Signal(jentry)){
            fill_plots(Signal_analysis_plots);
        }
        if(WJet(jentry)){
          //w Jet
            fill_plots(WJet_analysis_plots);
            std::cout << "test" << std::endl;
        } 
        if(TTBar(jentry)){
            //ttbar
            fill_plots(TTBar_analysis_plots);
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
//  150     m.Precut_cutflow.push_back(cut_flow_count("leading jet pt > 10 GeV"));
bool B2GTTree_cut_and_count::Precut(Long64_t jentry){
    bool keep_event = false;
    bool no_other_muon_electron = true;
    bool muon_cut = false;
    bool jet_cut = false;
    bool transvers_mass_cut = false;

    //no other leptons  NOT COMPLETED!!!!!!!!! work and shit
    for(int i = 1; i < mu_size; i++){
        if(mu_Pt[i] > 33 and abs(mu_Eta[i]) < 2.1 and mu_Iso04[i] < .12 and no_other_muon_electron){
            no_other_muon_electron = false;
           // std::cout << mu_Pt[i] << std::endl;
        }
    }

    //no other leptons  NOT COMPLETED!!!!!!!!! work and shit
    for(int i = 0; i < el_size; i++){
        if(el_Pt[i] > 20 and abs(el_Eta[i]) < 2.5 and el_Iso03[i] < .20 and no_other_muon_electron){
            no_other_muon_electron = false;
            //std::cout << el_Pt[i] << std::endl;
        }
    }
    
    
    Precut_cutflow[0].iterate();
    if( mu_Pt[0] > 33 and abs(mu_Eta[0]) < 2.1 and mu_Iso04[0] < .12 and no_other_muon_electron){ 

        Precut_cutflow[1].iterate();
        muon_cut = true;

    }
    //jet cuts
    if( jetAK4_Pt[0] > 70 and muon_cut){ 

        int jet_count = 0;
        int bjet_count = 0;
        btag_index = -10;
        for(int i = 0; i < jetAK4_size; i++){
    //        if( jetAK4_CSVv2[i] > .5 and jetAK4_Pt[i] > 30 and abs(jetAK4_Eta[i]) < 2.5){
            if( jetAK4_Pt[i] > 70 and abs(jetAK4_Eta[i]) < 2.4){ 
                jet_count = jet_count + 1;
            }
            if( jetAK4_CSVv2[i] > CSVv2M_working_point_76X  and jetAK4_Pt[i] > 30 and abs(jetAK4_Eta[i]) < 2.5){
                bjet_count = bjet_count + 1;
                btag_index = i;
            }
        }

        //std::cout << return_mTW() << std::endl;
        if(bjet_count != 1){
            btag_index = -10;
        }
        
        if(jet_count >= 1){
            Precut_cutflow[2].iterate();
            jet_cut = true;
        }
    }


    //transverse mass cut
    if( return_mTW() > 40 and jet_cut){
        transvers_mass_cut = true;
        Precut_cutflow[3].iterate();
    }


    if(muon_cut == true and jet_cut == true and transvers_mass_cut){
        keep_event = true;
    }
    return keep_event;
}

bool B2GTTree_cut_and_count::Signal(Long64_t jentry){
    bool keep_event = false;
    bool exactly_one_bjet = false;
    bool other_jets = false;
    bool mTW_above_50 = false;
    bool delta_phi_muon_bjet = false;
    bool met = false;

    Signal_cutflow[0].iterate();

    int local_btag_index = -10;
    //jet cuts
    int number_bjets = 0;
    for(int i = 0; i < jetAK4_size; i++){
        if(jetAK4_CSVv2[i] > CSVv2M_working_point_76X and jetAK4_Pt[i] > 70 and abs(jetAK4_Eta[i]) < 2.5){
            number_bjets = number_bjets + 1;
            local_btag_index = i;
        } else if( jetAK4_Pt[i] > 30 and jetAK4_CSVv2[i] < CSVv2M_working_point_76X){
            other_jets = true;
        }
    }
    
    if(number_bjets == 1){
        exactly_one_bjet = true;
        Signal_cutflow[1].iterate();
    } else {
        local_btag_index = -10;
    }
    if( exactly_one_bjet == true and other_jets == false){
        Signal_cutflow[2].iterate();
    }

    //transverse mass
    if(return_mTW() > 50 and exactly_one_bjet == true and other_jets == false){
        mTW_above_50 = true;
        Signal_cutflow[3].iterate();
    }

    //delta phi
   if(abs(mu_Phi[0] - jetAK4_Phi[local_btag_index]) < 1.7 and mTW_above_50){
        delta_phi_muon_bjet = true;
        Signal_cutflow[4].iterate();
   }

    if(met_Pt[0] > 100 and delta_phi_muon_bjet){
        met = true;
        Signal_cutflow[5].iterate();
    }


    if( exactly_one_bjet and other_jets == false and mTW_above_50 and delta_phi_muon_bjet){
        keep_event = true;
    }


    return keep_event;
}

bool B2GTTree_cut_and_count::WJet(Long64_t jentry){
    bool keep_event = false;
    bool high_pt_not_bjet = false;
    bool other_jet = false;


    WJet_cutflow[0].iterate();
    int number_selected_jets = 0;
    for(int i = 0; i < jetAK4_size; i++){
        if(jetAK4_Pt[i] > 70 and jetAK4_CSVv2[i] < CSVv2M_working_point_76X and abs(jetAK4_Eta[i]) < 2.5){
            number_selected_jets = number_selected_jets + 1;
        }else if( jetAK4_Pt[i] > 30 and abs(jetAK4_Eta[i]) < 2.5){
            other_jet = true;
        }

    }

    if( number_selected_jets == 1){
        high_pt_not_bjet = true;
        WJet_cutflow[1].iterate();
    }
    if(high_pt_not_bjet and other_jet == false){
        WJet_cutflow[2].iterate();
        keep_event = true;
    }


    return keep_event;
}

bool B2GTTree_cut_and_count::TTBar(Long64_t jentry){
    bool keep_event = false;
    bool two_bjets = false;
    bool leading_jet_pt = false;

    int local_num_bjets = 0;
    TTBar_cutflow[0].iterate();
     for(int i = 0; i < jetAK4_size; i++){
         if(jetAK4_Pt[i] > 30 and jetAK4_CSVv2[i] > CSVv2M_working_point_76X and abs(jetAK4_Eta[i]) < 2.5){
            local_num_bjets = local_num_bjets + 1;
            if( jetAK4_Pt[i] > 70){
                leading_jet_pt = true;
            }
         }
     }

    if( local_num_bjets == 2){
        two_bjets = true;
        TTBar_cutflow[1].iterate();
    }
    if( two_bjets and leading_jet_pt){
        TTBar_cutflow[2].iterate();
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


//void B2GTTree_cut_and_count_autorun(){
//
//    B2GTTree_cut_and_count m;
//    //initilze cutflow for precut
//    m.Precut_cutflow.push_back(cut_flow_count("all events wjet"));
//    m.Precut_cutflow.push_back(cut_flow_count("eactly one muon"));
//    m.Precut_cutflow.push_back(cut_flow_count("jet cut"));
//
//    //initilize plots
//    m.PreCut_analysis_plots = new analysis_plots("WJET_precut");
//
//    m.Loop();
//    
//    m.Draw_plots(m.PreCut_analysis_plots);
//}
//
