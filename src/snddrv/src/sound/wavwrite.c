#include "mamecore.h"
#include "wavwrite.h"

struct _wav_file
{
	OSD_FILE *file;
	UINT32 total_offs;
	UINT32 data_offs;
};

#ifdef LSB_FIRST
#define intel_long(x) (x)
#define intel_short(x) (x)
#else
#define intel_long(x) (((x << 24) | (((unsigned long) x) >> 24) | (( x & 0x0000ff00) << 8) | (( x & 0x00ff0000) >> 8)))
#define intel_short(x) (((x) << 8) | ((x) >> 8))
#endif

wav_file *wav_open(const char *filename, int sample_rate, int channels)
{
	UINT32 bps, temp32;
	UINT16 align, temp16;
	/* allocate memory for the wav struct */
	wav_file *wav = (wav_file *) malloc(sizeof(struct _wav_file));
	if (!wav)
		return NULL;

	/* create the file */
	wav->file = osd_fopen(FTYPE_WRITE, filename, "wb");
	if (!wav->file)
	{
		free(wav);
		return NULL;
	}

	/* write the 'RIFF' header */
	osd_fwrite("RIFF", 1, 4, wav->file);

	/* write the total size */
	temp32 = 0;
	wav->total_offs = osd_ftell(wav->file);
	osd_fwrite(&temp32, 1, 4, wav->file);

	/* write the 'WAVE' type */
	osd_fwrite("WAVE", 1, 4, wav->file);

	/* write the 'fmt ' tag */
	osd_fwrite("fmt ", 1, 4, wav->file);

	/* write the format length */
	temp32 = intel_long(16);
	osd_fwrite(&temp32, 1, 4, wav->file);

	/* write the format (PCM) */
	temp16 = intel_short(1);
	osd_fwrite(&temp16, 1, 2, wav->file);

	/* write the channels */
	temp16 = intel_short(channels);
	osd_fwrite(&temp16, 1, 2, wav->file);

	/* write the sample rate */
	temp32 = intel_long(sample_rate);
	osd_fwrite(&temp32, 1, 4, wav->file);

	/* write the bytes/second */
	bps = sample_rate * 2 * channels;
	temp32 = intel_long(bps);
	osd_fwrite(&temp32, 1, 4, wav->file);

	/* write the block align */
	align = 2 * channels;
	temp16 = intel_short(align);
	osd_fwrite(&temp16, 1, 2, wav->file);

	/* write the bits/sample */
	temp16 = intel_short(16);
	osd_fwrite(&temp16, 1, 2, wav->file);

	/* write the 'data' tag */
	osd_fwrite("data", 1, 4, wav->file);

	/* write the data length */
	temp32 = 0;
	wav->data_offs = osd_ftell(wav->file);
	osd_fwrite(&temp32, 1, 4, wav->file);

	return wav;
}


void wav_close(wav_file *wav)
{
	UINT32 total = osd_ftell(wav->file);
	UINT32 temp32;

	/* update the total file size */
	osd_fseek(wav->file, wav->total_offs, SEEK_SET);
	temp32 = total - (wav->total_offs + 4);
	temp32 = intel_long(temp32);
	osd_fwrite(&temp32, 1, 4, wav->file);

	/* update the data size */
	osd_fseek(wav->file, wav->data_offs, SEEK_SET);
	temp32 = total - (wav->data_offs + 4);
	temp32 = intel_long(temp32);
	osd_fwrite(&temp32, 1, 4, wav->file);

	osd_fclose(wav->file);
	free(wav);
}


void wav_add_data_16(wav_file *wav, INT16 *data, int samples)
{
#ifdef LSB_FIRST
	/* just write and flush the data */
	osd_fwrite(data, 2, samples, wav->file);
	osd_fflush(wav->file);
#else
	INT16 *temp;
	int i;

	/* allocate temp memory */
	temp = malloc(samples * sizeof(temp[0]));
	if (!temp)
		return;

	/* swap */
	for (i = 0; i < samples; i++)
		temp[i] = intel_short((UINT16) data[i]);

	/* write and flush */
	osd_fwrite(temp, 2, samples, wav->file);
	osd_fflush(wav->file);

	/* free memory */
	free(temp);
#endif
}
