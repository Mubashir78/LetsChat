#include "cipher.h"


/*
Way to use the cipher function:
    thread_manager() will take care of:
        - segmenting of the input packet
        - initialzing assigning threads
        - calling the right cipher function
        
                 
*/

void shift(char* text, int shift_val, int start_ind, int end_ind){
    for (int i = start_ind; text[i] != '\0' && i < end_ind; i++) 
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + shift_val) % 26 + base;
        }
}

void vegenere(char text[], int key[]){}

void permutation(char text[], int key[], int keylen){}

void RSA(){}
 


void* thread_manager(packet pkt, int num_threads, void* cipher){

    pthread_t tid[num_threads]; 
    thread_data data[num_threads];
    wrapper pakages[num_threads];

    for (int i=0; i<num_threads; i++){

        data[i].thread_id = tid[i]; data[i].thread_num = i;
        
        data[i].srt_ind = i*CHUNK_SIZE; 
        data[i].end_ind = (i == num_threads-1)? MSG_LEN : ((i+1)*CHUNK_SIZE);

        pakages[i].info = data[i]; pakages[i].pkt = pkt; pakages[i].cipher_function = cipher;

        pthread_create(&tid[i], NULL, wrapper_function, &pakages[i]);
    }

    for (int i=0; i<num_threads; i++) {
        pthread_join(tid[i], NULL);
    }

    pthread_exit(NULL);
}
