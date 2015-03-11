#include <jni.h>
#include <stdlib.h>
#include <string.h>



#include "com_u17webplib_webplib.h"
#include "webp/decode.h"





JNIEXPORT jint JNICALL Java_com_u17webplib_webplib_getVersion
  (JNIEnv * env, jclass jc){
  int nVersion = WebPGetDecoderVersion();
  return nVersion;
  }

/*

*/
JNIEXPORT jbyteArray JNICALL Java_com_u17webplib_webplib_getAdvancedDecode
  (JNIEnv *env, jclass jcls, jbyteArray data, jint swidth, jint sheigth, jintArray jwidth, jintArray jheight){

  jbyteArray jResult = 0;
  uint8_t* tData = NULL;
  int data_size = 0;

  if(data != NULL){
    data_size = env->GetArrayLength(data);
    tData = (uint8_t*)env->GetByteArrayElements(data, NULL);
  }


  if(tData != NULL){
    WebPDecoderConfig config;
    if(WebPInitDecoderConfig(&config) == 0){
    return 0;
    }

    if(WebPGetFeatures(tData, data_size,&config.input)!=VP8_STATUS_OK) return 0;
    if(config.input.width == 0 || config.input.height == 0) return 0;

    float iwidth = config.input.width;
    float iheigth = config.input.height;

    float tempW = (float)swidth * 1.5f;
    float tempH = (float)sheigth * 1.5f;

    if(iwidth >= tempW || iheigth >= tempH){
        if((tempW/tempH) < 0){
        iwidth = tempW;
        iheigth = iwidth / (iheigth / iwidth);
        }
        else{
        iheigth = tempH;
        iwidth = iheigth / (iheigth / iwidth);
        }
    }


    //config.options.no_fancy_upsampling = 1;
    config.output.colorspace = MODE_ARGB;
    config.options.use_scaling = 1;
    config.options.scaled_width = iwidth;
    config.options.scaled_height = iheigth;

    if ((WebPDecode(tData, data_size, &config) != VP8_STATUS_OK)){
    return 0;
    }

    //free(tData);

    //output width
    {
        jint  jvalue = (jint)config.options.scaled_width;
        env->SetIntArrayRegion(jwidth,0,1,&jvalue);
    }
    //output height
    {
        jint  jvalue = (jint)config.options.scaled_height;
        env->SetIntArrayRegion(jheight,0,1,&jvalue);
    }

    uint8_t* result = config.output.u.RGBA.rgba;
    size_t size = config.output.u.RGBA.size;
    jbyteArray outData = env->NewByteArray(size);
    jbyte *arr = env->GetByteArrayElements(outData, NULL);
    for (int i=0; i<size; i++){
      arr[i] = (jbyte)result[i];
     }
    env->ReleaseByteArrayElements(outData, arr, 0);

    WebPFreeDecBuffer(&config.output);
    return outData;
  }
  return 0;
 }

