#ifndef PCG8100_H_INCLUDED
#define PCG8100_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

void	pcg8100_reset(void);

void	pcg8100_out(unsigned char port, unsigned char data);

void	pcg8100_out_at(unsigned char port, unsigned char data, int cpu_state);

void	pcg8100_mix(short *stereo, int frames, int sample_rate);

int	statesave_pcg8100(void);
int	stateload_pcg8100(void);

#ifdef __cplusplus
}
#endif

#endif	/* PCG8100_H_INCLUDED */
