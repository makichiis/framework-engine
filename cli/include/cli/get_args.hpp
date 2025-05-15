#ifndef GET_ARGS_HPP
#define GET_ARGS_HPP

#include <string>

struct FCLIArguments {
    std::string sample_name;
    std::string location;
    std::string project_name;
    bool list_samples = false;
    bool empty = false;

};  
    
FCLIArguments get_args(int argc, char** argv);    

#endif 