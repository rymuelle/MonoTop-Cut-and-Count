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

