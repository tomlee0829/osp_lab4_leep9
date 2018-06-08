//Description: Lab program of multi-threded recursive
//file search in C, prints all files and deirectories
//whose names contain the search term
//and also print the time it took to do the search.
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>
#include <time.h>
#include <sys/stat.h>
#define CLOCKS_PER_MS (CLOCKS_PER_SEC / 1000)

#define T 4 //define 4 threads for using

//Declartions Below

//Declare function prototypes
void recursiveDirectorySearch(char *directoryName);
void *fileSearch(void *file);

//Declare global variables
const char *fileTerm;
const char *startingDir;

//struct for arugments to pass in functions
struct argument
{
    //The dirent structure defines the format of
    //direcotry entries
    struct dirent *entry;
};


//Implement functions
void *fileSearch(void *file)
{
    struct argument *arg = file;
	struct dirent *dirEntry = arg->entry;
    char *dirName = NULL;
    dirName = dirEntry->d_name; //structure dirent member, Name of entry(d_name)
	char *path = malloc(sizeof(char) + strlen(startingDir) + strlen(dirEntry->d_name) + 2);
    
    //DT_DIR check for directory
    if (dirEntry->d_type == DT_DIR)
    {
        ///The strcmp() function compares the entry
        //string and if it equals, skip and do not
        //recurse the . or .. directories
        if(strcmp(dirName, ".") == 0 || strcmp(dirName, "..") == 0)
        {
           return NULL;
        }
        
        strcpy(path, startingDir);
        strcat(path, "/");
        strcat(path, dirName);
        recursiveDirectorySearch(path);
        
        //function strstr() locates the string fileTerm
        //check if there's fileTerm matches
        //file in the path user provided
        //prints absolute path and the match results
        if(strstr(dirName, fileTerm) != NULL)
        {
            strcat(path, ":"); //append : to indicate dir
            printf("%s\n", path);
        }

    }
    //DT_REG checks for regular file
    else if (dirEntry->d_type == DT_REG)
    {
        //function strstr() locates the string fileTerm
        //check if there's fileTerm matches
        //file in the path user provided
        //prints absolute path and the match results
        if(strstr(dirName, fileTerm) != NULL)
        {
            printf("%s\n", dirName);
        }
    }
        free(path); //free the allocated space
}


int main(int argc, char *argv[])
{
    //clock_t returns the number of clock
    //ticks elapsed since the program was launched
    clock_t startTime, endTime;
    float totalTime = 0;
    
    struct stat dirSt;
    
    //Argument error(Usage)
    if (argc != 3)
    {
        printf("Usage: fileSearchThreaded <search term> <starting directory>\n");
        exit(1);
    }
    else
    {
        //Set searchTerm and starting directory to the
        //correct argument
        fileTerm = argv[1];
        startingDir = argv[2];
        
        //stat function check if the entry is a directory,
        //if not, print an error message
        if(stat(startingDir, &dirSt) != 0)
        {
            perror("error");
            exit(1);
        }
        
        //Set up threads
        pthread_t threads[T];
        
        //Allocate space for each thread
        struct argument *arg = malloc(sizeof(struct argument));;
        struct argument *arg1 = malloc(sizeof(struct argument));;
        struct argument *arg2 = malloc(sizeof(struct argument));;
        struct argument *arg3 = malloc(sizeof(struct argument));;
        
        
        endTime = clock();
        closedir(directory); //close the directory
        
        //count the time in millisecond
        totalTime = (float)(endTime - startTime) / CLOCKS_PER_MS;
        printf("\nTime: %fms \n", totalTime);
    }
    
    return 0;
}
