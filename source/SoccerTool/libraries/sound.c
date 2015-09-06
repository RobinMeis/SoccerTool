#include <portaudio.h> //Audio part's originalsSource: http://stackoverflow.com/questions/379353/what-is-a-lightweight-cross-platform-wav-playing-library
#include <sndfile.h>
#include <pthread.h>
#include <time.h>

int repeat;

static int output_cb(const void * input, void * output, unsigned long frames_per_buffer, const PaStreamCallbackTimeInfo *time_info, PaStreamCallbackFlags flags, void * data) {
  SNDFILE * file = data;
  sf_read_short(file, output, frames_per_buffer);
  return paContinue;
}

#define error_check(err) \
    do {\
        if (err) { \
            fprintf(stderr, "line %d ", __LINE__); \
            fprintf(stderr, "error number: %d\n", err); \
            fprintf(stderr, "\n\t%s\n\n", Pa_GetErrorText(err)); \
        } \
    } while (0)

void *play(void *repeat_ptr) {
  int n;
  int *repeat = (int *)repeat_ptr;
  PaStreamParameters out_param;
  PaStream * stream;
  PaError err;
  SNDFILE * file;
  SF_INFO sfinfo;

  struct timespec tim, tim2;
  tim.tv_sec  = 0;
  tim.tv_nsec = 500000000L;

  for (n=0; n<(*repeat); ++n) {
    file = sf_open("whistle.wav", SFM_READ, &sfinfo);
    printf("%d frames %d samplerate %d channels\n", (int)sfinfo.frames, sfinfo.samplerate, sfinfo.channels);

    /* init portaudio */
    err = Pa_Initialize();
    error_check(err);

    /* we are using the default device */
    out_param.device = Pa_GetDefaultOutputDevice();
    if (out_param.device == paNoDevice)
        fprintf(stderr, "Haven't found an audio device!\n");

    /* stero or mono */
    out_param.channelCount = sfinfo.channels;
    out_param.sampleFormat = paInt16;
    out_param.suggestedLatency = Pa_GetDeviceInfo(out_param.device)->defaultLowOutputLatency;
    out_param.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(&stream, NULL, &out_param, sfinfo.samplerate, paFramesPerBufferUnspecified, paClipOff, output_cb, file);
    error_check(err);

    err = Pa_StartStream(stream);
    error_check(err);

    Pa_Sleep(1000);

    err = Pa_StopStream(stream);
    error_check(err);
    err = Pa_CloseStream(stream);
    error_check(err);
    sf_close(file);
    Pa_Terminate();
     nanosleep(&tim, &tim2);
  }
}

int play_whistle(int rep) {
  repeat=rep;
  pthread_t inc_play;
  if(pthread_create(&inc_play, NULL, play, &repeat)) {
    fprintf(stderr, "Error creating thread\n");
    return 1;
  }
  return 0;
}
