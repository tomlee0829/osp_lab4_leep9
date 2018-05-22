//Description: Lab program of recursive file search in C,
//prints all files and deirectories whose names contain
//the search term and also print the time it took
//to do the search.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

void fileSearch(char *searchTerm)
{
    //Declarations
    const char *path = ".";
    DIR *directory = opendir(path);
    struct dirent *entry;
    char *dirName = NULL;
    char cwd[1024];
    struct stat dirSt;
    
    if(getcwd(cwd, sizeof(cwd)) != NULL)
    {
        if(directory)
        {
            while(entry = readdir(directory))
            {
                dirName = entry->d_name;
                if(stat(dirName, &dirSt) == -1)
                {
                    perror("error");
                    continue;
                }
                
                if(strcmp(dirName, ".") == 0 || strcmp(dirName, "..") == 0)
                {
                    continue;
                }
                
                if(dirName && strstr(dirName, searchTerm))
                {
                    printf("%s/%s\n", cwd, dirName);
                }
                
                if(S_ISDIR(dirSt.st_mode))
                {
                    chdir(dirName);
                    fileSearch(searchTerm);
                    chdir("..");
                }
            }
        }
    }
}



int main(int argc, char *argv[])
{
    //Argument error
    if(argc < 3)
    {
        fprintf(stderr, "Usage: %s <searchTerm> <starting directory> \n", argv[0]);
        exit(1);
    }
    
    return 0;
}

