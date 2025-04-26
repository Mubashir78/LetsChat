#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

#define file_path "./shared_mem.txt"


int main(){
    char * buffer;
    pid_t pid = fork();

    

    if (pid == 0) {
        
        printf("the child must write smth to the shared file: \n"); 
        
        int fd = open(file_path,O_WRONLY , 0644);
        
        printf("=======\nentering the loop now\n");
        char string[1024] = {0}; 
        while(1){
            fgets(string,sizeof(string),stdin);
            // string[(int)strcspn(string,"\n")] = '\0';
            (write(fd,string,(int)strlen(string)) > 0) ? printf("success : ") : printf("fail\n");
            if (strcmp(string,"exit\n") == 0) break;
        }printf("\n==============\nexiting the loop\n");

        // while(1);

        close(fd);

    }
    else {
        
        wait(NULL); printf("Now parent will resume its execution\n");
        
        int fd = open(file_path, O_RDONLY, 0644);
        
        char string[1024]; lseek(fd, 0, SEEK_SET);
        if (read(fd,string,sizeof(string)) > 0) printf("%s\n",string);
        
        close(fd);
    }

    return 0;
}