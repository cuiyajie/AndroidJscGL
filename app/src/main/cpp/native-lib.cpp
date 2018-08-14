#include "native-lib.h"
#include <string>
#include <thread>
#include <vector>
#include "include/jsc.h"
#include <unistd.h>

/*
 * Most of this is modified from https://github.com/sixo/node-example
 */

extern "C"
JNIEXPORT void JNICALL
Java_fex_momo_com_androidjscgl_drawGL(JNIEnv *env, jobject instance, jstring jscode) {

}