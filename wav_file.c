#include "wav_file.h"
#include <string.h>

void write_wav_header(FILE *file, uint32_t audio_data_size)
{
    uint32_t total_size = audio_data_size + 36; // Total file size minus 8 bytes for RIFF and WAVE headers
    uint32_t data_size = audio_data_size;

    // WAV header structure
    struct
    {
        // RIFF Header
        char riff_header[4];
        uint32_t wav_size;
        char wave_header[4];

        // FMT Header
        char fmt_header[4];
        uint32_t fmt_chunk_size;
        uint16_t audio_format;
        uint16_t num_channels;
        uint32_t sample_rate;
        uint32_t byte_rate;
        uint16_t sample_alignment;
        uint16_t bit_depth;

        // Data Header
        char data_header[4];
        uint32_t data_size;
    } wav_header;

    // Fill in the WAV header
    memcpy(wav_header.riff_header, "RIFF", 4);
    wav_header.wav_size = total_size;
    memcpy(wav_header.wave_header, "WAVE", 4);
    memcpy(wav_header.fmt_header, "fmt ", 4);
    wav_header.fmt_chunk_size = 16;
    wav_header.audio_format = 1;                                                 // PCM format
    wav_header.num_channels = 1;                                                 // Mono audio
    wav_header.sample_rate = 44100;                                              // Sample rate (adjust as needed)
    wav_header.byte_rate = wav_header.sample_rate * wav_header.num_channels * 2; // Sample rate * channels * bytes per sample
    wav_header.sample_alignment = wav_header.num_channels * 2;                   // Channels * bytes per sample
    wav_header.bit_depth = 16;                                                   // 16-bit audio
    memcpy(wav_header.data_header, "data", 4);
    wav_header.data_size = data_size;

    // Write the header to the file
    fwrite(&wav_header, sizeof(wav_header), 1, file);
}
