#include "FfmpegWrapper.h"

#define UINT64_C uint64_t 

extern "C" {
#include "libavformat/avformat.h"
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
}
/*
typedef struct {
	uint8_t* buffer;
	int bufferlength;
	AVCodecContext *pCodecCtx;
	AVFrame *pFrameRGB;

	AVFrame *pFrame;
	unsigned int videoStream;
	AVFormatContext *pFormatCtx;
	void (*IlcAfterFrame)(void *, void *, char *, unsigned char*, unsigned, unsigned, unsigned);
	
	void *parent;
	void *field;
	char closeFlag;
	AVCodec *pCodec;
	SwsContext* img_convert_ctx_RGB;
} IlcFfmpegStreamData;
*/
void ffmpegInit() {

	//register all the codecs, parsers and bitstream filters which were enabled at configuration time
	avcodec_register_all();
	//initializes libavformat and registers all the muxers, demuxers and protocols
	av_register_all();

	avcodec_init();


}

void * ffmpegOpenInputFile(char * url, char *format) {

	AVInputFormat* m_file_iformat;
	AVFormatContext* pFormatCtx;
	
	m_file_iformat = av_find_input_format( format );

	if(m_file_iformat == 0) {
		return NULL;
	}

	if(av_open_input_file(&pFormatCtx, url, m_file_iformat, 0, NULL) != 0) {
		return NULL;
	}
	printf("av_open_input_file OK\n");
	return (void *)pFormatCtx;

}

int ffmpegFindVideoStream(void *pFormatCtx) {

	int i;
	for(i=0; i<((int)((AVFormatContext*)pFormatCtx)->nb_streams); i++) {
		if(((AVFormatContext*)pFormatCtx)->streams[i]->codec->codec_type==CODEC_TYPE_VIDEO)	{
			return i;
		}
	}
	return -1;
}

void * ffmpegGetCodecContext(void *pFormatCtx, int videoStream) {

	return (void *) ((AVFormatContext*)pFormatCtx)->streams[videoStream]->codec;
	
}

void * ffmpegFindDecoder(void *pCodecCtx) {

	return (void *) avcodec_find_decoder(((AVCodecContext *)pCodecCtx)->codec_id);
	
}

int ffmpegCodecOpen(void *pCodecCtx, void *pCodec) {

	return avcodec_open(((AVCodecContext *)pCodecCtx), ((AVCodec *)pCodec));
	
}

void * ffmpegAllocFrame() {

	return (void *)avcodec_alloc_frame();
	
}

int ffmpegFindStreamInfo(void *pFormatCtx) {
	return av_find_stream_info((AVFormatContext*)pFormatCtx);
}


int ffmpegPictureSize(void *pCodecCtx) {
	return avpicture_get_size(PIX_FMT_RGB24, ((AVCodecContext *)pCodecCtx)->width, ((AVCodecContext *)pCodecCtx)->height);
}

void ffmpegPictureFill(void * pFrameRGB, void * buffer, void * pCodecCtx) {

	avpicture_fill( 
		(AVPicture *)pFrameRGB, 
		(uint8_t*)buffer, 
		PIX_FMT_RGB24,	
		((AVCodecContext *)pCodecCtx)->width, 
		((AVCodecContext *)pCodecCtx)->height);

}

void * ffmpegScalerContext(void * pCodecCtx) {

	int sws_flags = SWS_BICUBIC;
	return (void *)	sws_getContext(((AVCodecContext *)pCodecCtx)->width, ((AVCodecContext *)pCodecCtx)->height,
											((AVCodecContext *)pCodecCtx)->pix_fmt,
											((AVCodecContext *)pCodecCtx)->width, ((AVCodecContext *)pCodecCtx)->height,
											PIX_FMT_RGB24,
											sws_flags, NULL, NULL, NULL);
}

void ffmpegScale(void *img_convert_ctx_RGB, void * pCodecCtx, void *pFrame, void *pFrameRGB) {

	sws_scale((SwsContext *)img_convert_ctx_RGB, ((AVFrame *)pFrame)->data, ((AVFrame *)pFrame)->linesize,
			0, ((AVCodecContext *)pCodecCtx)->height, ((AVFrame *)pFrameRGB)->data, ((AVFrame *)pFrameRGB)->linesize);

}

void * ffmpegBuffer(void *pFrameRGB) {
	return (void *) ((AVFrame *)pFrameRGB)->data[0];
}

int ffmpegLineSize(void *pFrameRGB) {
	return ((AVFrame *)pFrameRGB)->linesize[0];
}

int ffmpegWidth(void *pCodecCtx) {
	return ((AVCodecContext *)pCodecCtx)->width;
}

int ffmpegHeight(void *pCodecCtx) {
	return ((AVCodecContext *)pCodecCtx)->height;
}

void * ffmpegNewPacket() {
	void *packet;
	packet = malloc(sizeof(AVPacket));
	memset(packet, 0, sizeof(AVPacket));
	return packet;
}

void ffmpegDeletePacket(void * packet) {
	free(packet);
}

unsigned char * ffmpegPacketData(void * packet) {
	return ((AVPacket *)packet)->data;
}

unsigned ffmpegPacketSize(void * packet) {
	return ((AVPacket *)packet)->size;
}

void ffmpegPacketFree(void * packet) {

	av_free_packet((AVPacket *)packet);

}

int ffmpegReadFrame(void *pFormatCtx, void *packet) {

	return av_read_frame((AVFormatContext *)pFormatCtx, (AVPacket *)packet);

}
void ffmpegDecodeVideo(void *pCodecCtx, void *pFrame, void *packet, int *frameFinished) {

	avcodec_decode_video2((AVCodecContext *)pCodecCtx, (AVFrame *)pFrame, frameFinished, (AVPacket*)packet);

}

int ffmpegPacketIndex(void *packet) {

	return ((AVPacket *)packet)->stream_index;

}


void ffmpegStreamFree(void *img_convert_ctx_RGB, void *pFrameRGB, void *pFrame, void *pCodecCtx, void *pFormatCtx) {


	if(img_convert_ctx_RGB != NULL)
		sws_freeContext((SwsContext *)img_convert_ctx_RGB);	
	
	if(pFrameRGB != NULL)
		av_free((AVFrame *)pFrameRGB);


	if(pFrame != NULL)
		av_free((AVFrame *)pFrame);
	
    if (pCodecCtx != NULL) 
		avcodec_close((AVCodecContext *)pCodecCtx);

	
	if(pFormatCtx != NULL)
		av_close_input_file((AVFormatContext *)pFormatCtx);

}
