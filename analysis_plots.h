#include <TH2.h>
//plot struct
struct analysis_plots{
    int nBins;
    double muon_pt_max;
    std::string cut_name;
    TH1F * muon_pt;
    TH1F * MET_pt;
    analysis_plots(std::string);
};

analysis_plots::analysis_plots(std::string name){
    nBins = 100;
    muon_pt_max = 250;
    cut_name = name;
    std::string temp_name;
    //muon_pt = new TH1F("TH1F_muon_pt" + name; "TH1F muon pT " + name + "; pT (GeV/c); counts", nBins, 0, muon_pt_max);
   temp_name = "leading_muon_Pt" + cut_name; 
    muon_pt = new TH1F(temp_name.c_str(), "test", 100, 0, 250);
    temp_name = "leading_MET_Pt" + cut_name; 
    MET_pt = new TH1F(temp_name.c_str(), "test", 100, 0, 1000);
   // std::cout << name << std::endl;

}
