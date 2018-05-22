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
#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)

void fileSearch(char *searchTerm)
{
    //Declarations
    const char *path = "."; //set pointer to the scanned directory

    //opendir() function opens the directory named by
    //filename(here is path), associates a directory
    //stream with it and returns a pointer to be used
    //to identify the directory stream
    DIR *directory = opendir(path); 
    
    //The dirent structure defines the format of 
    //direcotry entries
    struct dirent *entry;
    char *dirName = NULL;
    char cwd[1024];

    //The stat structure is used to determine
    //file type/direcotry
    struct stat dirSt;
    
    //getcwd() function copies the absolute pathname 
    //of the current working directory into the memory
    if(getcwd(cwd, sizeof(cwd)) != NULL)
    {

        if(directory)
        {
            //readdir function() returns a pointer to the next 
            //directory entry
            while((entry = readdir(directory)))
            {

                dirName = entry->d_name; //structure dirent member, Name of entry(d_name) 

                //stat function check if the entry is a directory,
                //if not, print an error message
                if(stat(dirName, &dirSt) == -1)
                {
                    perror("error");
                    continue;
                }

                //The strcmp() function compares the entry
                //string and if it equals, skip and do not 
                //recurse the . or .. directories
                if(strcmp(dirName, ".") == 0 || strcmp(dirName, "..") == 0)
                {
                    continue;
                }
                
                //function strstr() locates the string searchTerm
                //check if there's searchTerm matches 
                //file in the path user provided
                //prints absolute path and the match results
                if(dirName && strstr(dirName, searchTerm))
                {
                    printf("%s/%s\n", cwd, dirName);
                }
                
                //Test whether a file is of the specified type
                //S_ISDIR is test for a directory
                if(S_ISDIR(dirSt.st_mode))
                {
                    //chidr() function cause the directory named 
                    //by the pathname pointed to by the path 
                    //argument to become the current working directory(dirName)
                    chdir(dirName);
                    //check the directory
                    fileSearch(searchTerm);
                    //change back to the parent directory
                    chdir("..");
                }
            }
        }
    }
}



int main(int argc, char *argv[])
{
    //Declare
    char *dirPath;
    char *searchTerm;
    struct stat dirSt;
    
    //Argument error(Usage)
    if(argc < 3)
    {
        fprintf(stderr, "Usage: %s <searchTerm> <starting directory> \n", argv[0]);
        exit(1);
    }
    
    //Set searchTerm and starting directory to the
    //correct argument
    searchTerm = argv[1];
    dirPath = argv[2];

    //stat function check if the entry is a directory,
    //if not, print an error message
    if(stat(dirPath, &dirSt) != 0)
    {
        perror("error");
        exit(1);
    }
    
    //chidr() function cause the directory named 
    //by the pathname pointed to by the path 
    //argument to become the current working directory(dirPath)
    chdir(dirPath);
    //check the directory
    fileSearch(searchTerm);

    //clock_t returns the number of clock 
    //ticks elapsed since the program was launched
    clock_t startTime, endTime;
    float totalTime = 0;
    startTime = clock();
    endTime = clock();
    //count the time in millisecond
    totalTime = (float)(endTime - startTime) / CLOCKS_PER_MS; 
    printf("\nTime: %fms \n", totalTime);
    
    return 0;
}

