#include "cipher.h"
#include <pthread.h>

char* getText(){
    printf("Enter text: ");
    char* buffer = (char*)malloc(256);
    if(!fgets(buffer, sizeof(buffer), stdin))
        return NULL;
    return buffer;
}



