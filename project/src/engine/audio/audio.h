#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

#define PLAY_AUDIO true

#define AUDIO_RATE 44100
#define AUDIO_CHANNELS 2
#define AUDIO_BUFFERS 4096

void init_audio(void);
void load_audio_sound(Mix_Chunk **chunk, const char *path);
void load_audio_music(Mix_Music **music, const char *path);
void play_audio_sound(Mix_Chunk *sound);
void play_audio_music(Mix_Music *music);