#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char *argv[])
{
    
    DIR *d;
    
    struct dirent *dir;
    d = opendir(argv[1]);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if (argc<=2){
                printf("%s\n", dir->d_name);
            }
            else {
                int result = strncmp(argv[2], dir->d_name, 1);
                
                if (result != 0)
                {printf("%s\n", dir->d_name);}
            }
        }
        closedir(d);
    }
    return 0;
}

