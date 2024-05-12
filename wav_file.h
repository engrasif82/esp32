#ifndef WAV_FILE_H
#define WAV_FILE_H

#include <stdio.h>
#include <stdint.h>

// Function to write a simple WAV file header
void write_wav_header(FILE *file, uint32_t audio_data_size);

#endif
