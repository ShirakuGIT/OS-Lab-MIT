#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t rw_mutex, mutex; // Semaphores
int read_count = 0;    // Number of readers

void* reader(void* arg) {
    while (1) {
        sem_wait(&mutex); // Lock to update read_count
        read_count++;
        if (read_count == 1) sem_wait(&rw_mutex); // First reader locks writers
        sem_post(&mutex); // Unlock after updating read_count
        
        // Critical section: Reading
        printf("Reader %ld is reading\n", (long)arg);
        
        sem_wait(&mutex); // Lock to update read_count
        read_count--;
        if (read_count == 0) sem_post(&rw_mutex); // Last reader unlocks writers
        sem_post(&mutex); // Unlock after updating read_count
    }
}

void* writer(void* arg) {
    while (1) {
        sem_wait(&rw_mutex); // Writer locks readers and writers
        // Critical section: Writing
        printf("Writer %ld is writing\n", (long)arg);
        sem_post(&rw_mutex); // Unlock after writing
    }
}

int main() {
    pthread_t r[5], w[2];
    
    sem_init(&mutex, 0, 1);     // Semaphore for reader count access
    sem_init(&rw_mutex, 0, 1);  // Semaphore for writer access
    
    for (long i = 0; i < 5; i++) pthread_create(&r[i], NULL, reader, (void*)i); // Create readers
    for (long i = 0; i < 2; i++) pthread_create(&w[i], NULL, writer, (void*)i); // Create writers
    
    for (int i = 0; i < 5; i++) pthread_join(r[i], NULL); // Join readers
    for (int i = 0; i < 2; i++) pthread_join(w[i], NULL); // Join writers
    
    sem_destroy(&mutex);      // Destroy semaphores
    sem_destroy(&rw_mutex);
    
    return 0;
}
