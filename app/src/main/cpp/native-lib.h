#ifndef ANDROIDJSCGL_NATIVE_LIB_H
#define ANDROIDJSCGL_NATIVE_LIB_H

#include <jni.h>
#include <android/log.h>
#include <vector>

#define LOGD(...) (__android_log_print(ANDROID_LOG_DEBUG, "JSC", __VA_ARGS__))

extern "C" JNIEXPORT void
JNICALL
Java_fex_momo_com_androidjscgl_MainActivity_bootstrap(JNIEnv *env, jobject instance);


extern "C" JNIEXPORT void
JNICALL
Java_fex_momo_com_androidjscgl_MainActivity_runScript(JNIEnv *env, jobject instance, jstring jscode);

extern "C" JNIEXPORT void
JNICALL
Java_fex_momo_com_androidjscgl_MainActivity_nativeSurfaceChanged(JNIEnv *env, jobject instance, jint w, jint h);

extern "C" JNIEXPORT void
JNICALL
Java_fex_momo_com_androidjscgl_MainActivity_destory(JNIEnv *env, jobject instance);

#endif