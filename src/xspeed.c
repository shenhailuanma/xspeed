#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <inttypes.h>
#include <getopt.h>
#include <sys/time.h>


#include "libavformat/avformat.h"


static int xspeed_debug = 1;
#ifdef MODULE_NAME
#undef MODULE_NAME
#endif

#define MODULE_NAME     "xspeed"

#ifdef DEB1
#undef DEB1
#endif

#ifdef DEB2
#undef DEB2
#endif

#ifdef DEB3
#undef DEB3
#endif


#ifdef ERR
#undef ERR
#endif

#define SPLICE_VERSION "1.0.0"

#define DEB1(format, arg...)    \
    if (speed_debug >=1) {    \
        printf(MODULE_NAME "\t F: %s"" L: %u " format, __FUNCTION__ ,__LINE__,  ## arg );\
    }
#define DEB2(format, arg...)    \
    if (speed_debug >=2) {    \
        printf(MODULE_NAME "\t F: %s"" L: %u " format, __FUNCTION__ ,__LINE__,  ## arg );\
    }
#define DEB3(format, arg...)    \
    if (speed_debug >=3) {    \
        printf(MODULE_NAME "\t F: %s"" L: %u " format, __FUNCTION__ ,__LINE__,  ## arg );\
    }


#define ERR(format, arg...)    printf("ERROR: "MODULE_NAME " F: %s"" L: %u " format, __FUNCTION__ ,__LINE__,  ## arg )

#define LOG(format, arg...)    printf("LOG: "MODULE_NAME ": " format, ## arg )



struct xspeed_params{
    char input[512]; // input url
    char output[512];
    char format[32];
    int  speed;

};

#define ARG_PARSE_ERROR     -1
#define ARG_PARSE_OK        0  
#define ARG_PARSE_QUIT      1


static void print_help(void)
{
    printf("Usage: ./xspeed  -i <input_file> -s <speed_number> -o <output_file>\n");
    printf("\tinput_file: the input file.\n");
    printf("\tspeed_number: the number of speed change.\n");
    printf("\toutput_file: the output file.\n");
    printf("For example:\n");
    printf("\t./xspeed -i /data/video/source.mp4 -s 2 -o /tmp/out.mp4\n");
}



static struct option    long_option[] = 
{
    {"help",    no_argument,        0, 'h'},
    {"input",   required_argument,  0, 'i'},
    {"speed",   required_argument,  0, 's'},
    {"output",   required_argument,  0, 'o'},
    {0, 0, 0, 0},
};


static int parse_and_update_params(struct xspeed_params * params, int argc, char ** argv)
{
    int ch;
    int option_index = 0;
    int argcnt = 0;

    while(1){
        ch = getopt_long(argc, argv, "hi:o:x:", long_option, &option_index);
        if(ch == EOF){
            break;
        }

        argcnt += 1;

        switch(ch){
            case 'h':
                print_help();
                return ARG_PARSE_QUIT;
                break;

            case 'i':
                printf("-i(--input):%s\n",optarg);
                
                if(strlen(optarg) >= sizeof(params->input)){
                    printf("input url too long!\n");
                    return ARG_PARSE_ERROR;
                }
                strcpy(params->input, optarg);

                break;
            case 'o':
                printf("-o(--output):%s\n",optarg);
                if(strlen(optarg) >= sizeof(params->output)){
                    printf("output url too long!\n");
                    return ARG_PARSE_ERROR;
                }
                strcpy(params->output, optarg);
            
                break;
            case 'f':
                printf("-f(--format):%s\n",optarg);
                if(strlen(optarg) >= sizeof(params->format)){
                    printf("format too long!\n");
                    return ARG_PARSE_ERROR;
                }
                strcpy(params->format, optarg);
                break;

            case 's':
                printf("-s(--speed):%s\n",optarg);
                if(strlen(optarg) >= sizeof(params->format)){
                    printf("format too long!\n");
                    return ARG_PARSE_ERROR;
                }
                strcpy(params->format, optarg);
                break;
            default:
                print_help();
                break;
                
        }
    }

    if(optind < argc)
    {
        printf("args parse error!\n");
        return ARG_PARSE_ERROR;
    }

    if(argcnt <= 0){
        print_help();
        return ARG_PARSE_ERROR;
    }

    return ARG_PARSE_OK;

}

int main(int argc, char ** argv)
{


    int ret;
    int val;
    
    struct xspeed_params params;

    AVFormatContext *ctx = NULL;




    memset(&params, 0, sizeof(params));

    // parse and update the params
    if(parse_and_update_params(&params, argc, argv) != 0){
        return -1;
    }

    printf("input:%s\n", params.input);
    printf("output:%s\n", params.output);
    printf("speed:%d\n", params.speed);


    av_register_all();

    // open the media file
    ret = avformat_open_input(&ctx, params.input, NULL, NULL);
    if (ret < 0) {
        ERR("error open stream: '%s', error code: %d \n", params.input, ret);
        return -1;
    }

    ret = avformat_find_stream_info(ctx, NULL);
    if (ret < 0) {
        ERR("could not find stream info.\n");
        return -1;
    }

    av_dump_format(ctx, 0, ctx->filename, 0);


    int videoStreamIndex=-1;
    int audioStreamIndex=-1;
    double time_base = 0;
    int audio_time_base = 0;
    int video_time_base = 0;
    int i;


    for(i = 0; i < ctx->nb_streams; i++){
        AVStream* stream = ctx->streams[i];
        if(stream->codec->codec_type == AVMEDIA_TYPE_VIDEO){
            printf("find a video stream[%d]: %dkbps\n", i, stream->codec->bit_rate / 1000);
            videoStreamIndex = i;
  
            video_time_base = stream->time_base.den / stream->time_base.num;
            printf("video_time_base=%d\n", video_time_base);
        }
        if(stream->codec->codec_type == AVMEDIA_TYPE_AUDIO){
            printf("find a audio stream[%d]: %dkbps\n", i, stream->codec->bit_rate / 1000);
            audioStreamIndex = i;
           
            audio_time_base = stream->time_base.den / stream->time_base.num;
            printf("audio_time_base=%d\n", audio_time_base);
        }
    }


    AVPacket packet;
    int frameIndex = 0;

    int64_t pre_video_dts = 0;
    int64_t pre_audio_dts = 0;

    int fps = ctx->streams[videoStreamIndex]->r_frame_rate.num/ctx->streams[videoStreamIndex]->r_frame_rate.den;
    printf("fps = %d\n", fps);


    int video_should_dt = video_time_base/fps;
    printf("video_should_dt = %d\n", video_should_dt);

    int video_dt = 0;
    int frame_error = 0;

    // do 
    while(1){
 
        ret = av_read_frame(ctx, &packet);
        if(ret == AVERROR(EAGAIN)){
            // EAGAIN means try again

            continue;
        }
        if(ret < 0){
            break;
        }

        if(packet.stream_index == videoStreamIndex){
            frameIndex++;
            frame_error = 0;

            if(pre_video_dts != 0){
                pre_video_dts = packet.dts;
            }else{
                video_dt = packet.dts - pre_video_dts;
                if(video_dt - 2*video_should_dt > 0 || pre_video_dts >  packet.dts){
                    frame_error = 1;
                }
            }
            pre_video_dts = packet.dts;
            printf("#%d : [video], index=%d, pts=%"PRId64", dts=%"PRId64", ifKey=%d, size=%d, error=%d\n", frameIndex, packet.stream_index, packet.pts, packet.dts, packet.flags & AV_PKT_FLAG_KEY, packet.size, frame_error);
        }
        if(packet.stream_index == audioStreamIndex){
            frameIndex++;

            printf("#%d : [audio], index=%d, pts=%"PRId64", dts=%"PRId64", ifKey=%d, size=%d\n", frameIndex, packet.stream_index, packet.pts, packet.dts, packet.flags & AV_PKT_FLAG_KEY, packet.size);
        }
        av_free_packet(&packet);
    }


    return 0;
}