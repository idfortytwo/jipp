#include <pthread.h>
#include <unistd.h>
#include <cstdio>
#include <ctime>

using namespace std;


pthread_t philosophers[5];
pthread_mutex_t forks[5];

void* eat(void* _pos) {
    int pos = (int) _pos;
    pthread_mutex_t* left_fork = &forks[pos];
    pthread_mutex_t* right_fork = &forks[(pos + 1) % 5];

    printf("Philosopher %d is thinking...\n", pos);

    struct timespec timeout{};
    clock_gettime(CLOCK_REALTIME, &timeout);
    timeout.tv_sec += 3;

    int left_wait = pthread_mutex_timedlock(left_fork, &timeout);
    int right_wait = pthread_mutex_timedlock(right_fork, &timeout);

    if (left_wait == ETIMEDOUT || right_wait == ETIMEDOUT) {
        printf("Philosopher %d starved to death\n", pos);
        return nullptr;
    }

    printf("Philosopher %d is eating\n", pos);
    sleep(2);

    pthread_mutex_unlock(left_fork);
    pthread_mutex_unlock(right_fork);
    printf("Philosopher %d is finished eating\n", pos);

    return nullptr;
}

int main() {
    for (auto &fork : forks)
        pthread_mutex_init(&fork, nullptr);

    for (int pos = 0; pos < 5; pos++)
        pthread_create(&philosophers[pos], nullptr, eat, (void*) pos);

    for (auto &philosopher : philosophers)
        pthread_join(philosopher, nullptr);

    return 0;
}