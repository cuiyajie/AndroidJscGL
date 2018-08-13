#include <jni.h>
#include <string>
#include <stdlib.h>

extern "C" JNIEXPORT jstring

JNICALL
Java_fex_momo_com_androidjscgl_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
