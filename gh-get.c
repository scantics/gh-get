/*******************************************************************************
*   
*   gh-get
*   
*   Command-line wrapper for GitHub clones and pulls.
*   
*   This is intended to simplify the cloning and pulling of repos on GitHub by
*   reducing the information needed down to the user and repo name. Imitates
*   apt-get by cloning the repo if one does not exist, and updating the repo
*   with a pull if it already exists.
*   
*   Usage: gh-get <GitHub user>/<repository> -t [path_name]
*   
*******************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>


#define USAGE "gh-get <GitHub user>/<repository> [-t <path_name>]"

int main(int argc, char **argv)
{
    int i;
    char target[255];
    target[0] = ' ';
    bool target_set = false;
    /* Only taking one arg for now, yell if we get more or less. */
    for(i = 1; i < argc; ++i) {
        if(strcmp(argv[i],"-t") == 0) {
            if(i < argc-1) {
                strcat(target,argv[i+1]);
                target_set = true;
            } else {
                printf("No target path specified.\nUsage: %s",USAGE);
                return -1;
            }
        }
    }

    
    /* Store input and isolate repo name. */
    char * input = argv[1];
    char * reponame = strchr(input, '/');
    reponame++;
    
    /* Find if repo exists */
    bool repoexists = false;
    struct stat s;
    stat(reponame, &s);
    if(S_ISDIR(s.st_mode))
        repoexists = true;
    
    /* Build our git request. */
    char cmdstr[255] = "git ";
    if(repoexists) 
    {
        /* If repo exists, perform a pull. */
        strcat(cmdstr, "-C ");
        strcat(cmdstr, reponame);
        strcat(cmdstr, " pull");
    }
    else
    {
        /* If repo does not exist, clone the repo.
           What is being cloned?*/
        strcat(cmdstr, "clone https://github.com/");
        strcat(cmdstr, input);
        strcat(cmdstr, ".git");
    }
    if(target_set) {
        strcat(cmdstr,target);
    }
    /* Run our git clone/pull. */
    i=system(cmdstr);
    
    /* Return whatever value we got. */
    return i;
}
