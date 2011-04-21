void ffmpegInit();
void * ffmpegOpenInputFile(char * url, char *format);
int ffmpegFindStreamInfo(void *pFormatCtx);
int ffmpegFindVideoStream(void *pFormatCtx);
void * ffmpegGetCodecContext(void *pFormatCtx, int videoStream);
void * ffmpegFindDecoder(void *pCodecCtx);
int ffmpegCodecOpen(void *pCodecCtx, void *pCodec);
void * ffmpegAllocFrame();
int ffmpegPictureSize(void *pCodecCtx);
void ffmpegPictureFill(void * pFrameRGB, void * buffer, void * pCodecCtx);
void * ffmpegScalerContext(void * pCodecCtx);
void ffmpegScale(void *img_convert_ctx_RGB, void * pCodecCtx, void *pFrame, void *pFrameRGB);
void * ffmpegBuffer(void *pFrameRGB);
int ffmpegLineSize(void *pFrameRGB);
int ffmpegWidth(void *pCodecCtx);
int ffmpegHeight(void *pCodecCtx);
void * ffmpegNewPacket();
void * ffmpegNewPacket();
void ffmpegDeletePacket(void * packet);
int ffmpegReadFrame(void *pFormatCtx, void *packet);
int ffmpegPacketIndex(void *packet);
void ffmpegDecodeVideo(void *pCodecCtx, void *pFrame, void *packet, int *frameFinished);
unsigned char * ffmpegPacketData(void * packet);
unsigned ffmpegPacketSize(void * packet);
void ffmpegPacketFree(void * packet);
void ffmpegStreamFree(void *img_convert_ctx_RGB, void *pFrameRGB, void *pFrame, void *pCodecCtx, void *pFormatCtx);

















