#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace  std ;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int iLogLev = 0;
        iLogLev = av_log_get_level();
        qDebug()<<iLogLev;
        av_log_set_level(AV_LOG_DEBUG);
         iLogLev = av_log_get_level();
          qDebug()<<iLogLev;

          av_register_all(); //初始化FFMPEG  调用了这个才能正常适用编码器和解码器
          //=========================== 创建AVFormatContext结构体 ===============================//
              //分配一个AVFormatContext，FFMPEG所有的操作都要通过这个AVFormatContext来进行
              AVFormatContext *pFormatCtx = avformat_alloc_context();
           //==================================== 打开文件 ======================================//
              char *file_path = "/Users/wander/Downloads/test.mp4";//这里必须使用左斜杠
              int ret = avformat_open_input(&pFormatCtx, file_path, NULL, NULL);
              if(ret != 0)
              {
                  cout << "open error!" << endl;
                // return -1;
              }
              //循环查找视频中包含的流信息，直到找到视频类型的流
                  //便将其记录下来 保存到videoStream变量中
                  int i;
                  int videoStream;

                  //=================================== 获取视频流信息 ===================================//
                  if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
                  {
                      cout << "Could't find stream infomation." << endl;
                  //    return -1;
                  }
                  videoStream = -1;

                      for (i = 0; i < pFormatCtx->nb_streams; i++)
                      {
                          if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
                          {
                              videoStream = i;
                          }
                      }
                      //如果videoStream为-1 说明没有找到视频流
                        if (videoStream == -1)
                        {
                            cout << "Didn't find a video stream." << endl;
                            //return -1;
                        }
                        //=================================  查找解码器 ===================================//
                            AVCodecContext* pCodecCtx = pFormatCtx->streams[videoStream]->codec;
                            AVCodec* pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
                            if (pCodec == NULL)
                            {
                                cout << "Codec not found." << endl;
                              //  return -1;
                            }
                            //================================  打开解码器 ===================================//
                                if (avcodec_open2(pCodecCtx, pCodec, NULL) < 0)// 具体采用什么解码器ffmpeg经过封装  我们无须知道
                                {
                                    cout << "Could not open codec." << endl;
                                //    return -1;
                                }




                             //================================ 设置数据转换参数 ================================//
                                SwsContext * img_convert_ctx;
                                img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, //源地址长宽以及数据格式
                                                                 pCodecCtx->width, pCodecCtx->height,AV_PIX_FMT_YUVJ420P,    //目的地址长宽以及数据格式
                                                                 SWS_BICUBIC, NULL, NULL, NULL);//算法类型  AV_PIX_FMT_YUVJ420P   AV_PIX_FMT_BGR24





                            //==================================== 分配空间 ==================================//
                                //一帧图像数据大小
                                int numBytes = avpicture_get_size(AV_PIX_FMT_YUVJ420P, pCodecCtx->width,pCodecCtx->height);

                                unsigned char *out_buffer;
                                out_buffer = (unsigned char *) av_malloc(numBytes * sizeof(unsigned char));

                                AVFrame * pFrame;
                                pFrame = av_frame_alloc();
                                AVFrame * pFrameRGB;
                                pFrameRGB = av_frame_alloc();
                                avpicture_fill((AVPicture *) pFrameRGB, out_buffer, AV_PIX_FMT_YUVJ420P,pCodecCtx->width, pCodecCtx->height);
                                //会将pFrameRGB的数据按RGB格式自动"关联"到buffer  即pFrameRGB中的数据改变了 out_buffer中的数据也会相应的改变





                            //=========================== 分配AVPacket结构体 ===============================//
                                int y_size = pCodecCtx->width * pCodecCtx->height;
                                AVPacket *packet = (AVPacket *) malloc(sizeof(AVPacket)); //分配一个packet
                                av_new_packet(packet, y_size); //分配packet的数据

}

MainWindow::~MainWindow()
{
    delete ui;
}
