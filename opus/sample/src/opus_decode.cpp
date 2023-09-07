#include "opus_decode.h"
#include "ros/ros.h"
#include <stdio.h>

#define  PER_SAMPLE_BYTE 2

OpusDecode::OpusDecode()
	:mp_decoder(NULL),
	 m_sampleRate(0),
	 m_channel(1) 
{ 
}

OpusDecode::~OpusDecode()
{
	closeDecoder();
}

int OpusDecode::init_param(int sample_rate, int channel)
{
	m_sampleRate = sample_rate;
	m_channel = channel;
	return 0;
}

bool OpusDecode::open_decoder()
{
	if (mp_decoder != NULL)
	{
		return true;
	}

	int res = 0;
	mp_decoder = opus_decoder_create(m_sampleRate, m_channel, &res);
	if (res != OPUS_OK || mp_decoder == NULL)
	{
		ROS_ERROR("Cannot create decoder: %s", opus_strerror(res));
		return false;
	}

	return mp_decoder != NULL;
}

void OpusDecode::closeDecoder()
{
	if (mp_decoder != NULL)
	{
		opus_decoder_destroy(mp_decoder);
		mp_decoder = NULL;
	}
}

bool OpusDecode::write_packet(const uint8_t* data_in, int len_in, uint8_t *data_out, int& len_out)
{
	if (mp_decoder == NULL) {
		if (!open_decoder()) {
			return false;
		}
	}

	if (!data_in || !len_in) {
		return false;
	}

	int res = opus_decode(mp_decoder, data_in, len_in, (opus_int16 *)mp_pcmData, 
		sizeof(mp_pcmData)/PER_SAMPLE_BYTE/PER_SAMPLE_BYTE, 0);	
	if (res <= 0) {
		return false;
	}

	len_out = res * PER_SAMPLE_BYTE;
	memcpy(data_out, mp_pcmData, len_out);

	return true;
}

