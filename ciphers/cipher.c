#include "cipher.h"


/*
Utilizing the cipher funtion effectively:
    Shift Cipher: 
        the fucntion can be used to encrypt and decrypt text.
        For encryption, the function will be used normally, but
        for decryption, the "shift_val" parameter will passed as
        "26 - shift_val".

    Vegenere Cipher:
        
                 
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



void* caller(void* arg){
    // unwrapping
    wrapper* item = (wrapper*)arg;
    enum Cipher cipher_id = item->cipher_call;
    ThreadData* threads = item->threads;
    char text = item->data_packet.text;

    // calling the cipher function
    switch (cipher_id)
    {
        case Shift:
            shift(
                text,
                item->data_packet.key, 
                threads[item->counter].srt_ind, 
                threads[item->counter].end_ind
            );
            break;
            
        default:
            break;
    }

    pthread_exit(NULL);
}
