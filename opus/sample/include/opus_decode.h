#ifndef OPUS_DECODEC_H
#define OPUS_DECODEC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <opus/opus.h>
#include <opus/opus_types.h>

#define OPUS_DECODE_MAX_PCM_SIZE	(16*1024)

class OpusDecode
{
public:
	OpusDecode();
	~OpusDecode() ;

	int init_param(int sample_rate, int channel);
	bool write_packet(const uint8_t* data_in, int len_in, uint8_t *data_out, int& len_out);

private:
	bool open_decoder();
	void closeDecoder();

private:
	OpusDecoder *mp_decoder;
	unsigned char mp_pcmData[OPUS_DECODE_MAX_PCM_SIZE];

	int m_sampleRate;
	int m_channel;
};

#endif

