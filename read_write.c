# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>

sem_t rw_mutex, mutex;
int read_count = 0;

void * read()
{
    while(1) {
        sem_wait(&mutex);
        read_count = read_count + 1;

        if (read_count == 1)
        {
            wait(&rw_mutex);
        }
        sem_post(&mutex);

        printf("Reader is reading.\n");

        sem_wait(&mutex);
        read_count = read_count - 1;
        if (read_count == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&rw_mutex);
    }
}

void *write()
{
    while(1)
    {
        sem_wait(&rw_mutex);
        printf("Writer is writing.\n");
    }
    sem_post(&rw_mutex);
}