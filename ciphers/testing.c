#include "cipher.h"


char* getText(){
    printf("Enter text: ");

    char* buffer = (char*)malloc(MSG_LEN);

    if(!fgets(buffer, sizeof(buffer), stdin))
        return NULL;

    return buffer;
}


int main(){ 
    default_arg_packet shift_cipher;

    shift_cipher.text = getText();
    int shift_val = 1; shift_cipher.key = &shift_val;
    

    ThreadData threads[NUM_THREADS]; 
    

    // wrapping or zipping all of the data required for encoding, along with data paralellism.
    wrapper item; 

    item.data_packet = shift_cipher;
    item.threads = threads;
    item.cipher_call = Shift;

    // implementing data paralellism
    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].srt_ind = i * CHUNK_SIZE; threads[i].thread_id = i;
        threads[i].end_ind = (i == NUM_THREADS - 1) ? MSG_LEN : (i + 1) * CHUNK_SIZE;
        item.counter = i;

        if (pthread_create(&threads[i].thread, NULL, caller, (void*)&item)) 
            {printf("Error creating thread %d\n", i); return 1;}        
    }

    for (int i = 0; i < NUM_THREADS; i++) pthread_join(threads[i].thread, NULL);

    printf("\n\nCipher Messege: %s",shift_cipher.text);

    free(shift_cipher.text);
    return 0;
}