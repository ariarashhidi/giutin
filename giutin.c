#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
void print_comnd(int JJ, char *khalse[]);
int run_init(int argc, char * const argv[]);

struct global
{
    char mmd[100][100];
    int tedad_global;
};


void print_comnd(int JJ , char *khalse[]){
    for(int i=0 ; i<JJ ; i++){
        fprintf(stdout ,"%s " , khalse[i]);
    }
    fprintf(stdout , "\n");
}
int run_init(int argc, char * const argv[]) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL) return 1;

    char tmp_cwd[1024];
    bool exists = false;
    struct dirent *entry;
    do {
        // find .giutin
        DIR *dir = opendir(".");
        if (dir == NULL) {
            perror("Error opening current directory");
            return 1;
        }
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".giutin") == 0)
                exists = true;
        }
        closedir(dir);

        // update current working directory
        if (getcwd(tmp_cwd, sizeof(tmp_cwd)) == NULL) return 1;

        // change cwd to parent
        if (strcmp(tmp_cwd, "/") != 0) {
            if (chdir("..") != 0) return 1;
        }

    } while (strcmp(tmp_cwd, "/") != 0);

    // return to the initial cwd
    if (chdir(cwd) != 0) return 1;
        
    if (!exists) {
        if (mkdir(".giutin", 0755) != 0) return 1;
        return create_configs("aria", "ariarashidiqw@gmail.com");
    } else {
        perror("giutin repository has already initialized");
    }
    return 0;
}
int create_configs(char *username, char *email) {
    FILE *file = fopen(".giutin/config", "w");
    if (file == NULL) return 1;

    fprintf(file, "username: %s\n", username);
    fprintf(file, "email: %s\n", email);
    fprintf(file, "last_commit_ID: %d\n", 0);
    fprintf(file, "current_commit_ID: %d\n", 0);
    fprintf(file, "branch: %s", "master");

    fclose(file);
    
    // create commits folder
    if (mkdir(".giutin/commits", 0755) != 0) return 1;

    // create files folder
    if (mkdir(".giutin/files", 0755) != 0) return 1;

    file = fopen(".giutin/staging", "w");
    fclose(file);

    file = fopen(".giutin/tracks", "w");
    fclose(file);

    return 0;
}

int main(int JJ , char *khalse[]){
    if(JJ<2){
        printf("eshtebahhhhhh\n");
        return 1;
    }
    print_comnd(JJ , khalse);

    if(strcmp(khalse[1] , "init")==0){
        printf("11\n");
        return run_init(JJ , khalse);
    }
    if(strcmp(khalse[1] , "config")==0){
        if(JJ <4 || JJ>=6){
            printf("wrong\n");
        }
        else{
            if(strcmp(khalse[2] , "-global")==0){
                if(JJ < 5){
                    printf("wrong\n");
                }
                else{
                    FILE *file1 = fopen(".giutin/config" , "r");
                    char name[40] , name2[40] , email[40] , email2[40] , branch[40] , branch2[40] , last[40] , current[50];
                    int last_commit , current_commit_ID ;
                    fscanf(file1 , "%s %s" ,name2 , name);
                    fscanf(file1 , "%s %s" ,email2 ,  email);
                    fscanf(file1 , "%s %d"  ,last ,  &last_commit);
                    fscanf(file1 , "%s %d" , current , &current_commit_ID);
                    fscanf(file1 , "%s %s" ,branch2 ,  branch);

                    if(strcmp(khalse[3] , "user.name")==0){
                        FILE *file = fopen(".giutin/config1", "w");
                        fprintf(file, "username: %s\n", khalse[4]);
                        fprintf(file, "email: %s\n", email);
                        fprintf(file, "last_commit_ID: %d\n", last_commit);
                        fprintf(file, "current_commit_ID: %d\n", current_commit_ID);
                        fprintf(file, "branch: %s", branch);
                        fclose(file);
                        fclose(file1);
                        remove(".giutin/config");
                        rename(".giutin/config1" , ".giutin/config");
                    }
                    else if(strcmp(khalse[3] , "user.email")==0){
                        FILE *file = fopen(".giutin/config1", "w");
                        fprintf(file, "username: %s\n", name);
                        fprintf(file, "email: %s\n", khalse[4]);
                        fprintf(file, "last_commit_ID: %d\n", last_commit);
                        fprintf(file, "current_commit_ID: %d\n", current_commit_ID);
                        fprintf(file, "branch: %s", branch);
                        fclose(file);
                        fclose(file1);
                        remove(".giutin/config");
                        rename(".giutin/config1" , ".giutin/config");
                    }
                }
            }
            else if(strcmp(khalse[2] , "user.name")==0){
                
            }
            else if(strcmp(khalse[2] , "user.email")==0){

            }
        }
    }
}