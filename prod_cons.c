#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0; // Index for producer and consumer
sem_t empty, full, mutex; // Semaphores

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100; // Produce an item
        sem_wait(&empty);    // Wait for empty slot
        sem_wait(&mutex);    // Lock the buffer
        
        buffer[in] = item;   // Add item to buffer
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;
        
        sem_post(&mutex);    // Unlock buffer
        sem_post(&full);     // Increment full slot count
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);     // Wait for full slot
        sem_wait(&mutex);    // Lock the buffer
        
        item = buffer[out];  // Remove item from buffer
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
        
        sem_post(&mutex);    // Unlock buffer
        sem_post(&empty);    // Increment empty slot count
    }
}

int main() {
    pthread_t prod, cons;
    
    sem_init(&empty, 0, BUFFER_SIZE); // Initialize empty slots
    sem_init(&full, 0, 0);            // Initialize full slots
    sem_init(&mutex, 0, 1);           // Initialize mutex
    
    pthread_create(&prod, NULL, producer, NULL); // Create producer thread
    pthread_create(&cons, NULL, consumer, NULL); // Create consumer thread
    
    pthread_join(prod, NULL); // Wait for producer to finish
    pthread_join(cons, NULL); // Wait for consumer to finish
    
    sem_destroy(&empty);  // Destroy semaphores
    sem_destroy(&full);
    sem_destroy(&mutex);
    
    return 0;
}
