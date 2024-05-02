// init implementation
// Creating .git directory here
#include "repo.h"

int init(int argc, char* argv[]){
    Repo repo = Repo::createRepo(argv);
    // string da_git_name = ".git";

    // if(mkdir(".git", 0777) == -1){
    //     cout<<"Reinitialised existing git directory\n";
    //     return 1;
    // }
    // string path_obj = da_git_name + "/objects";
    // const char *path_o = path_obj.c_str();
    // mkdir(path_o, 0777);

    // string path_log = da_git_name+"/"+"logs";
    // const char *path_l = path_log.c_str();
    // mkdir(path_l, 0777);

    // ofstream log_head;
    // string path_log_head = path_log + "/" +"HEAD";
    // log_head.open(path_log_head, ofstream::app);

    // string path_log_refs = path_log + "/" +"refs";
    // const char *path_lr = path_log_refs.c_str();
    // mkdir(path_lr, 0777);

    // string path_log_refs_heads = path_log_refs + "/" +"heads";
    // const char *path_lrh = path_log_refs_heads.c_str();
    // mkdir(path_lrh, 0777);

    // ofstream log_rh_master;
    // string path_log_rh_master = path_log_refs_heads + "/" +"master";
    // log_rh_master.open(path_log_rh_master, ofstream::app);

    // fstream desc;
    // string desc_file = da_git_name+ "/" + "description";
    // const char *path_desc_file = desc_file.c_str();
    // desc.open(path_desc_file,ios::out);
    
    // // fstream idx;
    // // string idx_file = da_git_name+ "/" + "index";
    // // const char *path_idx_file = idx_file.c_str();
    // // idx.open(path_idx_file, ios::out);
    
    // fstream head;
    // string path_head = da_git_name + "/" +"HEAD";
    // const char *path_h = path_head.c_str();
    // head.open(path_h, ios::out);
    // head << "ref: refs/heads/master";

    // string path_refs = da_git_name + "/" +"refs";
    // const char *path_r = path_refs.c_str();
    // mkdir(path_r, 0777);

    // string path_ref_heads = path_refs + "/" +"heads";
    // const char *path_rh = path_ref_heads.c_str();
    // mkdir(path_rh, 0777);
    
    // return 0;

}