#include "TableControllerImpl.hpp"
#include <iostream>
#include <cstdlib>
#include <pthread.h>
#include <thread>

using namespace std;

void *RowController_1(void *threadid) {
    long id;
    id = (long)threadid;
    cout << "Thread_1: " << id << endl;
}

void *RowController_2(void *threadid) {
    long id;
    id = (long)threadid;
    cout << "Thread2: " << id << endl;
}

void *RowController_3(void *threadid) {
    long id;
    id = (long)threadid;
    cout << "Thread_3: " << id << endl;
}

void *RowController_4(void *threadid) {
    long id;
    id = (long)threadid;
    cout << "Thread_4: " << id << endl;
}

void RC_pthread() {
    pthread_t RC_1;
    pthread_t RC_2;
    pthread_t RC_3;
    pthread_t RC_4;

    pthread_create(&RC_1, NULL, RowController_1, (void *)1);
    pthread_create(&RC_2, NULL, RowController_2, (void *)2);
    pthread_create(&RC_3, NULL, RowController_3, (void *)3);
    pthread_create(&RC_4, NULL, RowController_4, (void *)4);
    
    pthread_join(RC_1, NULL);
    pthread_join(RC_2, NULL);
    pthread_join(RC_3, NULL);
    pthread_join(RC_4, NULL);

    
}
