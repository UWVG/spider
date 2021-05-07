#ifndef __SPIDER_H_
#define __SPIDER_H_
#ifdef __cplusplus
extern  "C"
{
#endif
	struct Signal {
		int status;
		int Noise;
		int SNR;
		int RSSI;
	};
	extern int _spider(char *,struct Signal *);
#ifdef __cplusplus
}
#endif
#endif