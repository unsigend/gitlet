/**
 * Part of the Implementation of gitlet project
 * Under the MIT License
 * Copyright (c) 2025, 2026 QIU YIXIANG
 */

#include <general/external.hpp>
#include <argparse/argparse.hpp>
#include <cmd/cmd.hpp>

using namespace gitlet;

int main(int argc, char *argv[]) {
    
    // only one argument (program name)
    if (argc < 2){
        
    }else{
        // with more than one argument
        std::string sub_cmd = argv[1];

    }
    
    return 0;
}