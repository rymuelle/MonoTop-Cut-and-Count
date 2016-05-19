#include "B2GTTree_cut_and_count_autorun.C"

void plot_wjets_with_cuts(){

    B2GTTree_cut_and_count m;
    //initilze cutflow for precut
    m.Precut_cutflow.push_back(cut_flow_count("all events wjet"));
    m.Precut_cutflow.push_back(cut_flow_count("eactly one muon"));
    m.Precut_cutflow.push_back(cut_flow_count("jet cut"));

    //initilize plots
    m.PreCut_analysis_plots = new analysis_plots("WJET_precut");

    m.Loop();
    
    m.print_cutflow(m.Precut_cutflow);

    m.Draw_plots(m.PreCut_analysis_plots);
}

