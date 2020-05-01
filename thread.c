//VIDEO LINK - https://www.youtube.com/watch?v=y2iBBEexGC4&feature=youtu.be

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //Header file for the pthreads works only in linux
#include <unistd.h>
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //initialising the mutex variables with prefined values in pthread header
pthread_cond_t var = PTHREAD_COND_INITIALIZER;     //initialising the condition variables with prefined values in pthread header
void *counteven();                                 //pointer to even counter function
void *countodd();                                  //pointer to odd counter function
int count = 0;
#define COUNT_DONE 10 //maximum iterations can be changed using this value

void main()
{
    pthread_t eventhread, oddthread;                   //declaration of the pthreads
    pthread_create(&oddthread, NULL, &countodd, NULL); //creation of the pthreads
    pthread_create(&eventhread, NULL, &counteven, NULL);
    pthread_join(oddthread, NULL); //waiting for the completion of the method by the threads using this method
    pthread_join(eventhread, NULL);
    exit(0); //successful exit with code 0
}

void *counteven()
{
    for (;;) //infinite loop as the termination is controlled by COUNT_DONE
    {
        pthread_mutex_lock(&mutex); //aquireing the mutex lock
        if (count % 2 == 0)         //checking the condtion on the variable
        {
            pthread_cond_wait(&var, &mutex); //condtional waiting for the job to complete
            sleep(1);
        }
        count++;                    //return to this after conditon
        printf("Even %d\n", count); //printing of the count
        pthread_cond_signal(&var);  //releasing the condtional hold
        if (count >= COUNT_DONE)    //checking for the release
        {
            pthread_mutex_unlock(&mutex); //release of the mutex lock
            return (NULL);
        }
        pthread_mutex_unlock(&mutex); //release of the mutex lock
    }
}

void *countodd()
{
    for (;;) //infinite loop as the termination is controlled by COUNT_DONE
    {
        pthread_mutex_lock(&mutex); //aquireing the mutex lock
        if (count % 2 != 0)         //checking the condtion on the variable
        {
            pthread_cond_wait(&var, &mutex); //condtional waiting for the job to complete
            sleep(1);
        }
        count++;                   //return to this after conditon
        printf("Odd %d\n", count); //printing of the count
        pthread_cond_signal(&var); //releasing the condtional hold
        if (count >= COUNT_DONE)   //checking for the release
        {
            pthread_mutex_unlock(&mutex); //release of the mutex lock
            return (NULL);
        }
        pthread_mutex_unlock(&mutex); //release of the mutex lock
    }
}

//-------------------------THANK YOU---------------------------------
// Abhinandan Purkait
// Roll - 1705876
// 1705876@kiit.ac.in
// purkaitabhinandan@gmail.com
