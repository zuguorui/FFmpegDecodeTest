#include <jni.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <android/log.h>
#include "OfficalDecodeAudio.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavutil/frame.h"
#include "libavutil/mem.h"
#include "libavformat/avformat.h"
#include "libswresample/swresample.h"
}

using namespace std;

#define MODULE_NAME  "native-lib"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, MODULE_NAME, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, MODULE_NAME, __VA_ARGS__)

extern "C" JNIEXPORT void JNICALL
Java_com_example_ffmpegdecodetest_MainActivity_nPrintFormatInfo(
        JNIEnv *env,
        jobject /* this */) {

    av_register_all();
    int count = 0;

    AVInputFormat *inFormat = av_iformat_next(NULL);
    LOGD("input formats:");
    while(inFormat != NULL)
    {
        LOGD("[In]%10s", inFormat->name);
        inFormat = inFormat->next;
        count++;
    }
    LOGD("FFmpeg in format count: %d", count);

    count = 0;
    AVOutputFormat *outFormat = av_oformat_next(NULL);
    LOGD("output formats:");
    while(outFormat != NULL)
    {
        LOGD("[Out]%10s", outFormat->name);
        outFormat = outFormat->next;
        count++;
    }
    LOGD("FFmpeg out format count: %d", count);
}

extern "C" JNIEXPORT void JNICALL
        Java_com_example_ffmpegdecodetest_MainActivity_nDecode(
                JNIEnv *env,
                jobject *instance, jstring input_file, jstring output_file)
{
    const char *inPath = env->GetStringUTFChars(input_file, NULL);
    const char *outputPath = env->GetStringUTFChars(output_file, NULL);
    OfficalDecodeAudio::decodeAudio(inPath, outputPath);

    env->ReleaseStringUTFChars(input_file, inPath);
    env->ReleaseStringUTFChars(output_file, outputPath);

}




