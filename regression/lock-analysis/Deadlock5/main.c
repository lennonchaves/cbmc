// no deadlock

#include <pthread.h>

pthread_mutex_t m1,m2;

int x;

void *thr1(void *arg)
{
  pthread_mutex_lock(&m1);
  pthread_mutex_lock(&m2);
  ++x;
  pthread_mutex_unlock(&m2);
  pthread_mutex_unlock(&m1);

  int k=0;
}

void *thr2(void *arg)
{
  pthread_mutex_lock(&m1);
  pthread_mutex_lock(&m2);
  ++x;
  pthread_mutex_unlock(&m2);
  pthread_mutex_unlock(&m1);
}


void *thr3(void *arg)
{
  pthread_mutex_lock(&m2);
  pthread_mutex_lock(&m1);
  ++x;
  pthread_mutex_unlock(&m1);
  pthread_mutex_unlock(&m2);
}


int main()
{
  pthread_t tid1, tid2, tid3;
  pthread_create(&tid1, NULL, thr1, NULL);
  pthread_create(&tid2, NULL, thr2, NULL);

  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  pthread_create(&tid3, NULL, thr3, NULL);
  pthread_join(tid3, NULL);

  return 0;
}