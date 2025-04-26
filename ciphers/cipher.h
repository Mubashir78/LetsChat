#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>

#define MSG_LEN 1024
#define NUM_THREADS 8
#define CHUNK_SIZE (MSG_LEN/NUM_THREADS)
typedef struct{
    
    pthread_t thread_id;
    int 
        srt_ind,
        end_ind,
        thread_num;

} thread_data;
typedef struct{
    char* text;
    int* key;
} packet;
typedef struct{
    thread_data info;
    packet pkt;
    void* cipher_function;
} wrapper; 

// managing functions
void* thread_manager(packet, int, void*);
void* wrapper_function(void* arg);
void cipher_caller(packet, thread_data, void*);
//cipher functions
void shift(char* text, int shift_val, int start_ind, int end_ind);
void vegenere(char* text, int* key);
// void permutation(char* text, int* key, int keylen);

