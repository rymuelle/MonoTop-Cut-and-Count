#include "B2GTTree_cut_and_count_autorun.C"

void plot_wjets_with_cuts(){

    B2GTTree_cut_and_count m;
    //initilze cutflow for precut
    m.Precut_cutflow.push_back(cut_flow_count("all events wjet"));
    m.Precut_cutflow.push_back(cut_flow_count("eactly one muon"));
    m.Precut_cutflow.push_back(cut_flow_count("jet cut"));
    m.Precut_cutflow.push_back(cut_flow_count("transverse mass of W cut"));

    m.Signal_cutflow.push_back(cut_flow_count("all events signal region wjet"));
    m.Signal_cutflow.push_back(cut_flow_count("exactly_one_bjet_signal"));
    m.Signal_cutflow.push_back(cut_flow_count("other_jets_signal"));
    m.Signal_cutflow.push_back(cut_flow_count("mTW_above_50_signal"));
    m.Signal_cutflow.push_back(cut_flow_count("delta_phi_muon_bjet_signal"));
    m.Signal_cutflow.push_back(cut_flow_count("met_signal"));

    m.WJet_cutflow.push_back(cut_flow_count("all events WJet region wjet"));
    m.WJet_cutflow.push_back(cut_flow_count("high_pt_not_bjet_wjet"));
    m.WJet_cutflow.push_back(cut_flow_count("other_jet_WJet"));

    m.TTBar_cutflow.push_back(cut_flow_count("all events TTbar region wjet"));
    m.TTBar_cutflow.push_back(cut_flow_count("two_bjets wjet"));
    m.TTBar_cutflow.push_back(cut_flow_count("leading jet pt wjet"));


    //initilize plots
    m.PreCut_analysis_plots = new analysis_plots("WJET_precut");
    m.Signal_analysis_plots = new analysis_plots("WJET_Signal");
    m.WJet_analysis_plots = new analysis_plots("WJET_WJet");
    m.TTBar_analysis_plots = new analysis_plots("WJET_TTBar");
    m.extra_analysis_plots = new analysis_plots("WJET_extra");

    m.Loop();
    
    m.print_cutflow(m.Precut_cutflow);
    m.print_cutflow(m.Signal_cutflow);
    m.print_cutflow(m.WJet_cutflow);
    m.print_cutflow(m.TTBar_cutflow);

    m.Draw_plots(m.PreCut_analysis_plots);
    m.Draw_plots(m.Signal_analysis_plots);
    m.Draw_plots(m.WJet_analysis_plots);
    m.Draw_plots(m.TTBar_analysis_plots);
}

