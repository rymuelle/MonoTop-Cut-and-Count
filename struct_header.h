#include <TH2.h>
//cut flow struct
struct cut_flow_count{
    std::string cut_name;
    int         cut_count;
    cut_flow_count(std::string);
    void        iterate();
};

cut_flow_count::cut_flow_count(std::string name){
    cut_name = name;
    cut_count = 0;
}

void cut_flow_count::iterate(){
    cut_count = cut_count + 1;
}

//plot struct
struct analysis_plots{
    int nBins;
    double muon_pt_max;
    std::string cut_name;
    TH1F * muon_pt;
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
    std::cout << name << std::endl;

}
