#include <pthread.h>
#include <stdio.h>

#include "sound.h"

unsigned int status[2],  //0=Stop, 1=Läuft, Index für Spiel
    verbleibende_zeit[2], //Zeit für Index Spiel
    whistle_done[2]; //Index (0,1)

void *thread(void *none) {
  for(;;) {
    if (status[0]==1 && verbleibende_zeit[0] > 0)
      --verbleibende_zeit[0];
    else if (whistle_done[0]==0 && status[0]==1) {
      play_whistle(1);
      whistle_done[0]=1;
    }

    if (status[1]==1 && verbleibende_zeit[1] > 0)
      --verbleibende_zeit[1];
    else if (whistle_done[1]==0 && status[1]==1) {
      play_whistle(1);
      whistle_done[1]=1;
    }
    sleep(1);
  }
}

void stoppuhr_init(void) {
  status[0]=0;
  status[1]=0;
  verbleibende_zeit[0]=0;
  verbleibende_zeit[1]=0;

  pthread_t inc_thread;
  if(pthread_create(&inc_thread, NULL, thread, &status[0])) {
    exit (1);
  }
}

void stoppuhr_start(int uhr) {
  if (uhr==0 || uhr==1)
    status[uhr]=1;
}

void stoppuhr_stop(int uhr) {
  if (uhr==0 || uhr==1)
    status[uhr]=0;
}

void stoppuhr_set(int uhr, int startzeit) {
  if (uhr==0 || uhr==1) {
    status[uhr]=0;
    whistle_done[uhr]=0;
    verbleibende_zeit[uhr]=startzeit;
  }
}

unsigned int stoppuhr_get(int uhr) {
  if (uhr==0 || uhr==1)
    return verbleibende_zeit[uhr];
}
