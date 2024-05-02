#include "common.h"
#include "include/index.h"

int main(int argc, char *argv[]){
    if(argc == 1){
        std::cout<<"No arguments given\n";
        exit(1);
    }else if(strcmp(argv[1], "init") == 0){
        std::cout<<"git init\n";
        init(argc, argv);
    }else if(strcmp(argv[1], "status") == 0){
        std::cout<<"git status\n";
        // status(argc, argv);
    }else{
        std::cout<<"Wrong arguments given\n";
    }
}