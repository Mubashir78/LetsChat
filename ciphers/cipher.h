#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <pthread.h>

#define MSG_LEN 1024
#define NUM_THREADS 8
#define CHUNK_SIZE (MSG_LEN/NUM_THREADS)

enum Cipher{
    Shift, 
    Vegenere,
    Permutation
};

typedef struct{
    pthread_t thread;
    int 
        srt_ind,
        end_ind,
        thread_id;
} ThreadData;

typedef struct{
    char* text;
    int* key;
} default_arg_packet;

typedef struct{
    ThreadData* threads;
    default_arg_packet data_packet;
    enum cipher_call;
    int counter;
} wrapper;

// wrapper function
void* caller(void* arg);


//cipher functions
void shift(char* text, int shift_val, int start_ind, int end_ind);
void vegenere(char text[], int key[]);
void permutation(char text[], int key[], int keylen);

