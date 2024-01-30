#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
void print_comnd(int JJ, char *khalse[]);
int run_init(int argc, char * const argv[]);

// struct global
// {
//     char mmd[100][100];
//     int tedad_global;
// };
void copy_file(char *src_f , char * des_f){
    FILE * src = fopen(src_f, "r");
    FILE * des = fopen(des_f, "w");
    char * line = (char *)malloc(1000);
    while (fgets(line, 1000, src) != NULL){
        fprintf(des, "%s", line);
    }
    fclose(des);
    fclose(src);
    free(line);
}

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

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
        char cwd[1000];
        char commtis[]={"/.giutin/commits1.txt"};
        getcwd(cwd , 1000);
        FILE* file = fopen("/home/aria/Desktop/address.txt" , "a");
        fprintf(file , "%s\n" , cwd);
        // printf("%s\n" , cwd);
        fclose(file);
        strcat(cwd , commtis);
        FILE* aria =  fopen(cwd , "w");
        fclose(aria);
        return create_configs("aria" , "ariarashidiqw@gmail.com");
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
    // poshe commits be stage eshare darad
    if(mkdir(".giutin/commitsasl" , 0755) != 0) return 1;
    // create files folder
    if (mkdir(".giutin/files", 0755) != 0) return 1;

    file = fopen(".giutin/tracks", "w");
    fclose(file);

    return 0;
}
int reset (char * link){
    int v;
    v =is_regular_file(link);
    if(v==1){
        char namefile[100];
        char *token = "/";
        char *str = strtok(link , token);
        while(str!=NULL){
            strcpy(namefile , str);
            str = strtok(NULL , token);
        }
        printf("%s\n" , namefile);
        char cwd[1000];
        getcwd(cwd , 1000);
        printf("%s\n" , cwd);
        char commit[]={"/.giutin/commits"};
        char a[]="/";
        strcat(cwd , commit);
        struct dirent *entry;
        DIR *dir = opendir(cwd);
        while ((entry = readdir(dir)) != NULL) {
            if (strcmp(entry->d_name, namefile) == 0){
                strcat(cwd , a);
                strcat(cwd , namefile);
                printf("%s\n" , cwd);
                remove(cwd);
                break;
            }
                
        }
        closedir(dir);

    }
    else{
        char cwd[1000];
        char cwd3[1000];
        getcwd(cwd , 1000);
        printf("%s\n" , cwd);
        char commit[]={"/.giutin/commits"};
        char a[]={"/"};
        strcat(cwd , commit);
        printf("%s\n" , cwd);
        struct dirent *entry;
        // struct dirent *entry2;
        DIR *dir = opendir(cwd);
        // DIR *dir1 = opendir(link);
        if(dir == NULL){
            printf("there is no directory\n");
        }
        else{
            while((entry = readdir(dir)) != NULL){
                struct dirent *entry2;
                DIR *dir1 = opendir(link);
                if(dir1 ==NULL){
                    printf("there is no directory\n");
                    return 0; 
                }
                while((entry2 = readdir(dir1)) != NULL){
                    if(strcmp(entry -> d_name , entry2 -> d_name)==0){
                        char filename[100];
                        strcpy(filename , entry2 -> d_name);
                        strcpy(cwd3 , cwd);
                        strcat(cwd3 , a);
                        strcat(cwd3 , filename);
                        remove(cwd3);

                    }
                }
            }
        }
    }
}
int stts(char * commit , char * aknon , char *giutin){
    // akhari jaye commitasli
    // printf("%s\n%s\n%s\n" , commit , aknon , giutin);
    int test=0;
    int test1=0;
    char cwd1[1000];
    char cwd2[1000];
    char bb[]={"/"};
    strcat(commit , bb);
    strcpy(cwd1 , commit);
    struct dirent *entry;
    // printf("%s\n" , commit);
    DIR *dir = opendir(commit);
    if(dir == NULL){
        printf("new\n");
    }
    while((entry = readdir(dir))!=NULL && entry->d_name[0]!='.'){
        // printf("%s\n" , entry->d_name);
        strcpy(cwd1 , commit);
        test1=0;
        test=0;
        struct dirent *entry2;
        DIR *dir2 = opendir(aknon);
        while((entry2 = readdir(dir2))!= NULL){
            strcpy(cwd2 , aknon);
            if(strcmp(entry ->d_name , entry2 ->d_name)==0){
                // printf("%s\n" , entry2->d_name);
                struct dirent *entry3;
                DIR *dir3 = opendir(giutin);
                while((entry3 = readdir(dir3))!= NULL){
                    if(strcmp(entry ->d_name , entry3->d_name)==0){
                        printf("+A\n");
                        test1++;
                        break;
                    }
                }
                if(test1==0){
                    char filename[100];
                    strcpy(filename , entry->d_name);
                    strcat(cwd1 , bb);
                    strcat(cwd1 , filename);
                    strcat(cwd2 , bb);
                    strcat(cwd2 , filename);
                    FILE *file = fopen(cwd1 , "r");
                    FILE *file1 = fopen(cwd2 , "r");
                    if(file1 == NULL){
                        printf("+D/n");
                    }
                    else{
                        int jaj=0;
                        int aja =0;
                        char a[1000];
                        char aaa[1000];
                        while(fgets(a , 1000 , file)!=NULL){
                            fgets(aaa , 1000 , file1);
                            if(strcmp(a , aaa)==0){
                                jaj++;
                            }
                            aja++;
                        }
                        if(aja != jaj){
                            printf("+M\n");
                        }
                    }
                }
                test ++;
                break;
            }
        }
        if(test == 0){
            printf("+D\n");
        }
    }
}
int main(int JJ , char *khalse[]){
    if(JJ<2){
        printf("eshtebahhhhhh\n");
        return 1;
    }
    print_comnd(JJ , khalse);

    if(strcmp(khalse[1] , "init")==0){
        
        return run_init(JJ , khalse);
    }
    if(strcmp(khalse[1] , "config")==0){
        if(JJ <4 ){
            printf("wrong\n");
        }
        else{
            if(strcmp(khalse[2] , "-global")==0){
                if(JJ < 5 ){
                    printf("wrong\n");
                }
                else{
                    if(strcmp(khalse[3] , "user.name")==0){
                        FILE * adress = fopen("/home/aria/Desktop/address.txt" , "r");
                        char cwd[1000];
                        char cwd1[] = {"/.giutin/config"};
                        char cwd2[] = {"1"};
                        // printf("%d\n" , 123);
                        while(fgets(cwd , 1000 , adress)!=NULL){
                            cwd[strlen(cwd)-1] = '\0';
                            char cww[1000];
                            strcat(cwd , cwd1);
                            strcpy(cww , cwd);
                            printf("%s\n" , cww);
                            FILE *file1 = fopen(cwd, "r");
                            strcat(cwd , cwd2);
                            FILE *file = fopen(cwd , "w");
                            char name[40] , name2[40] , email[40] , email2[40] , branch[40] , branch2[40] , last[40] , current[50];
                            int last_commit , current_commit_ID ;
                            fscanf(file1 , "%s %s" ,name2 , name);
                            fscanf(file1 , "%s %s" ,email2 ,  email);
                            fscanf(file1 , "%s %d"  ,last ,  &last_commit);
                            fscanf(file1 , "%s %d" , current , &current_commit_ID);
                            fscanf(file1 , "%s %s" ,branch2 ,  branch);
                            fprintf(file, "username: %s\n", khalse[4]);
                            fprintf(file, "email: %s\n", email);
                            fprintf(file, "last_commit_ID: %d\n", last_commit);
                            fprintf(file, "current_commit_ID: %d\n", current_commit_ID);
                            fprintf(file, "branch: %s", branch);
                            fclose(file);
                            fclose(file1);
                            remove(cww);
                            rename(cwd , cww);
                        }
                        fclose(adress);
                    }
                    else if(strcmp(khalse[3] , "user.email")==0){
                        FILE * adress = fopen("/home/aria/Desktop/address.txt" , "r");
                        char cwd[1000];
                        char cwd1[] = {"/.giutin/config"};
                        char cwd2[] = {"1"};
                        char cww[1000];
                        while(fgets(cwd , 1000 , adress)!=NULL){
                            cwd[strlen(cwd)-1]= '\0';
                            strcat(cwd , cwd1);
                            strcpy(cww , cwd);
                            FILE *file1 = fopen(cwd, "r");
                            strcat(cwd , cwd2);
                            FILE *file = fopen(cwd , "w");
                            char name[40] , name2[40] , email[40] , email2[40] , branch[40] , branch2[40] , last[40] , current[50];
                            int last_commit , current_commit_ID ;
                            fscanf(file1 , "%s %s" ,name2 , name);
                            fscanf(file1 , "%s %s" ,email2 ,  email);
                            fscanf(file1 , "%s %d"  ,last ,  &last_commit);
                            fscanf(file1 , "%s %d" , current , &current_commit_ID);
                            fscanf(file1 , "%s %s" ,branch2 ,  branch);
                            fprintf(file, "username: %s\n", name);
                            fprintf(file, "email: %s\n", khalse[4]);
                            fprintf(file, "last_commit_ID: %d\n", last_commit);
                            fprintf(file, "current_commit_ID: %d\n", current_commit_ID);
                            fprintf(file, "branch: %s", branch);
                            fclose(file);
                            fclose(file1);
                            remove(cww);
                            rename(cwd , cww);
                        }
                        fclose(adress);
                    }
                    else if(strcmp(khalse[3] , "alias")==0){
                        char new[1000];
                        char past[1000];
                        strcpy(new , khalse[4]);
                        strcpy(past , khalse[5]);
                        char cwd[1000];
                        FILE * adress = fopen("/home/aria/Desktop/address.txt" , "r");
                        while(fgets(cwd , 1000 , adress)!=NULL){
                            cwd[strlen(cwd)-1]='\0';
                            char cwd1[]={"/.giutin/commits1.txt"};
                            strcat(cwd , cwd1);
                            printf("%s\n" , cwd);
                            FILE * file = fopen(cwd , "r");
                            if(file == NULL){
                                printf("wrong\n");
                                fclose(file);
                            }
                            else{
                                fclose(file);
                                FILE *aria = fopen(cwd , "a");
                                fprintf(aria , "%s %s\n" , past , new); 
                                fclose(aria);  
                            }
                        }
                    }
                    
                }
            }
            else if(strcmp(khalse[2] , "user.name")==0){
                char cwd[1000];
                getcwd(cwd , 1000);
                char cwd1[] = {"/.giutin/config"};
                char cwd2[]={"1"};
                char cww[1000];
                strcat(cwd , cwd1);
                strcpy(cww  , cwd);
                FILE *file1 = fopen(cwd , "r");
                strcat(cwd , cwd2);
                if(file1==NULL){
                    printf("the file doesn't exist\n");
                }
                else{
                    char name[40] , name2[40] , email[40] , email2[40] , branch[40] , branch2[40] , last[40] , current[50];
                    int last_commit , current_commit_ID ;
                    fscanf(file1 , "%s %s" ,name2 , name);
                    fscanf(file1 , "%s %s" ,email2 ,  email);
                    fscanf(file1 , "%s %d"  ,last ,  &last_commit);
                    fscanf(file1 , "%s %d" , current , &current_commit_ID);
                    fscanf(file1 , "%s %s" ,branch2 ,  branch);
                    FILE *file = fopen(cwd, "w");
                    fprintf(file, "username: %s\n", khalse[3]);
                    fprintf(file, "email: %s\n", email);
                    fprintf(file, "last_commit_ID: %d\n", last_commit);
                    fprintf(file, "current_commit_ID: %d\n", current_commit_ID);
                    fprintf(file, "branch: %s", branch);
                    fclose(file);
                    fclose(file1);
                    remove(cww);
                    rename(cwd , cww);
                }
            }
            else if(strcmp(khalse[2] , "user.email")==0){
                char cwd[1000];
                getcwd(cwd , 1000);
                // printf("%s\n" , cwd);
                char cwd1[] = {"/.giutin/config"};
                char cwd2[]={"1"};
                char cww[1000];
                strcat(cwd , cwd1);
                strcpy(cww  , cwd);
                // printf("%s\n" , cww);
                FILE *file1 = fopen(cwd , "r");
                strcat(cwd , cwd2);
                if(file1==NULL){
                    printf("the file doesn't exist\n");
                }
                else{
                    char name[40] , name2[40] , email[40] , email2[40] , branch[40] , branch2[40] , last[40] , current[50];
                    int last_commit , current_commit_ID ;
                    fscanf(file1 , "%s %s" ,name2 , name);
                    fscanf(file1 , "%s %s" ,email2 ,  email);
                    fscanf(file1 , "%s %d"  ,last ,  &last_commit);
                    fscanf(file1 , "%s %d" , current , &current_commit_ID);
                    fscanf(file1 , "%s %s" ,branch2 ,  branch);
                    FILE *file = fopen(cwd, "w");
                    fprintf(file, "username: %s\n", name);
                    fprintf(file, "email: %s\n", khalse[3]);
                    fprintf(file, "last_commit_ID: %d\n", last_commit);
                    fprintf(file, "current_commit_ID: %d\n", current_commit_ID);
                    fprintf(file, "branch: %s", branch);
                    fclose(file);
                    fclose(file1);
                    remove(cww);
                    rename(cwd , cww);
                    // printf("%s %s\n" , cww , cwd);
                }
            }
            else if(strcmp(khalse[2] , "alias")==0){
                char new[1000];
                char past[1000];
                strcpy(new , khalse[3]);
                strcpy(past , khalse[4]);
                char cwd[1000];
                getcwd(cwd , 1000);
                char cwd1[]={"/.giutin/commits1.txt"};
                strcat(cwd , cwd1);
                FILE * file = fopen(cwd , "r");
                if(file == NULL){
                    printf("wrong\n");
                    fclose(file);
                }
                else{
                    fclose(file);
                    FILE *aria = fopen(cwd , "a");
                    fprintf(aria , "%s %s\n" , past , new); 
                    fclose(aria);  
                }
            }
        }
    }
    else if(strcmp(khalse[1] , "add")==0){
        if(JJ == 3){
            if(strcmp(khalse[2] , "s*c")==0){

            }
            else{
                char cwd[1000];
                char cwd2[1000];
                char konon[1000];
                // char ff='/';
                getcwd(konon , 1000);
                strcat(konon , "/");
                // printf("%s\n" , konon);
                strcpy(cwd , khalse[2]);
                strcpy(cwd2 , konon);
                strcat(cwd2 , cwd);
                strcpy(cwd , cwd2);
                // printf("%s\n" , cwd);
                int v;
                v = is_regular_file(cwd);
                if(v==1){
                    // printf("%s\n" , konon);
                    int h=0;
                    char tok[]={"/"};
                    char *str ;
                    // printf("%s\n" , cwd2);
                    str = strtok(cwd2 , tok);
                    // printf("%s\n" , str);
                    char fg[100];
                    while(str != NULL){
                        strcpy(fg , str);
                        str = strtok(NULL , tok);
                    }
                    // printf("%s\n" , fg);
                    char cwd1[]={"/.giutin/commits/"};
                    strcat(konon , cwd1);
                    strcat(konon , fg);
                    // printf("%s\n" , konon);
                    FILE * ali = fopen(konon , "w");
                    fclose(ali);
                    copy_file(cwd , konon);
                }
                else{
                    DIR * dir = opendir(cwd);
                    char *tok={"/"};
                    char *token = strtok(cwd , tok);
                    char namedir[100];
                    while(token!=NULL){
                        strcpy(namedir , token);
                        token = strtok(NULL , tok);
                    }
                    if (dir == NULL) {
                        printf("Error opening current directory\n");
                    }
                    else{
                        struct dirent *entry;
                        while ((entry = readdir(dir)) != NULL) {
                            char konon[1000];
                            getcwd(konon , 1000);
                            strcat(konon , "/");
                            strcpy(cwd , khalse[2]);
                            strcpy(cwd2 , konon);
                            strcat(cwd2 , cwd);
                            if (entry->d_type == DT_REG){
                                char desn[1000];
                                strcpy(desn , entry->d_name);
                                strcat(cwd2 , "/");
                                strcat(cwd2 , entry->d_name);
                                char cwd1[]={"/.giutin/commits/"};
                                strcat(konon , cwd1);
                                strcat(konon , desn);
                                FILE* aria = fopen(konon , "w");
                                fclose(aria);
                                copy_file(cwd2 , konon);
                            }
                        }
                        closedir(dir);
                    }
                }
            }
        }
        else{
            if(strcmp(khalse[2] , "-f")==0){
                for(int i=3 ; i<JJ ; i++){
                    if(strcmp(khalse[i] , "s*c")==0){

                    }
                    else{
                        char cwd[1000];
                        char cwd2[1000];
                        char konon[1000];
                        // char ff='/';
                        getcwd(konon , 1000);
                        strcat(konon , "/");
                        // printf("%s\n" , konon);
                        strcpy(cwd , khalse[i]);
                        strcpy(cwd2 , konon);
                        strcat(cwd2 , cwd);
                        strcpy(cwd , cwd2);
                        // printf("%s\n" , cwd);
                        int v;
                        v = is_regular_file(cwd);
                        if(v==1){
                            // printf("%s\n" , konon);
                            int h=0;
                            char tok[]={"/"};
                            char *str ;
                            // printf("%s\n" , cwd2);
                            str = strtok(cwd2 , tok);
                            // printf("%s\n" , str);
                            char fg[100];
                            while(str != NULL){
                                strcpy(fg , str);
                                str = strtok(NULL , tok);
                            }
                            // printf("%s\n" , fg);
                            char cwd1[]={"/.giutin/commits/"};
                            strcat(konon , cwd1);
                            strcat(konon , fg);
                            // printf("%s\n" , konon);
                            FILE * ali = fopen(konon , "w");
                            fclose(ali);
                            copy_file(cwd , konon);
                        }
                        else{
                            DIR * dir = opendir(cwd);
                            char *tok={"/"};
                            char *token = strtok(cwd , tok);
                            char namedir[100];
                            while(token!=NULL){
                                strcpy(namedir , token);
                                token = strtok(NULL , tok);
                            }
                            if (dir == NULL) {
                                printf("Error opening current directory\n");
                            }
                            else{
                                struct dirent *entry;
                                while ((entry = readdir(dir)) != NULL) {
                                    char konon[1000];
                                    getcwd(konon , 1000);
                                    strcat(konon , "/");
                                    strcpy(cwd , khalse[i]);
                                    strcpy(cwd2 , konon);
                                    strcat(cwd2 , cwd);
                                    if (entry->d_type == DT_REG){
                                        char desn[1000];
                                        strcpy(desn , entry->d_name);
                                        strcat(cwd2 , "/");
                                        strcat(cwd2 , entry->d_name);
                                        char cwd1[]={"/.giutin/commits/"};
                                        strcat(konon , cwd1);
                                        strcat(konon , desn);
                                        FILE* aria = fopen(konon , "w");
                                        fclose(aria);
                                        copy_file(cwd2 , konon);
                                    }
                                }
                                closedir(dir);
                            }
                        }
                    }
                }
            }
            else if(strcmp(khalse[2] , "-n")==0){
                char cwd[1000];
                getcwd(cwd , 1000);
                char cwd1[]={"/.giutin/commits"};
                strcat(cwd , cwd1);
                // printf("%s\n" , cwd);
                DIR* dir= opendir(cwd);
                struct dirent *entry;
                while((entry = readdir(dir))!=NULL){
                    char r[100];
                    strcpy(r , entry -> d_name);
                    if(r[0] == '.'){
                        continue;
                    }
                    printf("%s\n" , entry -> d_name);
                }
            }
        }
    }
    else if(strcmp(khalse[1] , "rest")==0){
        char cwd1[1000];
        char aa[]="/";
        getcwd(cwd1 , 1000);
        strcat(cwd1 , aa);
        strcat(cwd1 , khalse[2]);
        printf("%s cwd1\n" , cwd1);
        reset(cwd1);
    }
    else if(strcmp(khalse[1] , "status")==0){
        char cwd[1000];
        getcwd(cwd , 1000);
        char cwd12[1000];
        strcpy(cwd12 , cwd);
        char *token;
        char *tok={"/"};
        printf("%s\n" , cwd);
        token = strtok(cwd , tok);
        int test=0;
        int test1=0;
        char ali[1000];
        char l[]={"/"};
        while(token != NULL){
            if(test1 == 0){
                strcpy(ali , l);
                strcat(ali , token);
            }
            else{
                strcat(ali , token);
            }
            strcat(ali , l);
            test1++;
            if(strcmp(token , ".giutin")== 0){
                test++;
                break;
            }
            token = strtok (NULL , tok);
        }
        printf("%d\n" , test1);
        if(test == 0){
            printf("wrong golom\n");
        }
        else{
            printf("%s\n" , ali);
            char cc[]={"commits"};
            char cd[]={"commitsasl"};
            char v[1000];
            strcpy(v , ali);
            strcat(v , cd);
            strcat(ali, cc);
            printf("%s\n%s\n" , ali , v);
            stts(ali , cwd12 , v);
        }
    }
}