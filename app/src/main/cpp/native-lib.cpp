#include "native-lib.h"
#include <string>
#include <thread>
#include <vector>
#include <unistd.h>

#include <EGL/egl.h>
// at least some defs from gl1 are needed
#include <GLES/gl.h>
#include <GLES2/gl2.h>
#include <android/sensor.h>
#include "include/jsc/JavaScript.h"

/*
 * Most of this is modified from https://github.com/sixo/node-example
 */

JSValueRef _glClear(JSContextRef ctx, JSObjectRef func, JSObjectRef thisObj, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
    double mask = JSValueToNumber(ctx, argv[0], nullptr);
    glClear(mask);
    return JSValueMakeUndefined(ctx);
}

JSValueRef _glClearColor(JSContextRef ctx, JSObjectRef func, JSObjectRef thisObj, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
    double red = JSValueToNumber(ctx, argv[0], nullptr);
    double green = JSValueToNumber(ctx, argv[1], nullptr);
    double blue = JSValueToNumber(ctx, argv[2], nullptr);
    double alpha = JSValueToNumber(ctx, argv[3], nullptr);
    glClearColor(red, green, blue, alpha);
    return JSValueMakeUndefined(ctx);
}

extern "C" JNIEXPORT void
JNICALL
Java_fex_momo_com_androidjscgl_MainActivity_drawGL(JNIEnv *env, jobject instance, jstring jscode) {
    LOGD("%s", env -> GetStringUTFChars(jscode, nullptr));
    JSContextGroupRef group = JSContextGroupCreate();
    JSGlobalContextRef globalContext = JSGlobalContextCreateInGroup(group, nullptr);
    JSObjectRef globalObject = JSContextGetGlobalObject(globalContext);

    JSStringRef func_clear_str = JSStringCreateWithUTF8CString("clear");
    JSObjectRef func_clear_obj = JSObjectMakeFunctionWithCallback(globalContext, func_clear_str, (JSObjectCallAsFunctionCallback)_glClear);
    JSObjectSetProperty(globalContext, globalObject, func_clear_str, func_clear_obj, kJSPropertyAttributeNone, nullptr );

    JSStringRef func_clearColor_str = JSStringCreateWithUTF8CString("clearColor");
    JSObjectRef func_clearColor_obj = JSObjectMakeFunctionWithCallback(globalContext, func_clearColor_str, (JSObjectCallAsFunctionCallback)_glClearColor);
    JSObjectSetProperty(globalContext, globalObject, func_clearColor_str, func_clearColor_obj, kJSPropertyAttributeNone, nullptr );

    // make javascript
    JSStringRef script = JSStringCreateWithCharacters(env -> GetStringChars(jscode, nullptr), env -> GetStringLength(jscode));
    // evaluate it
    JSEvaluateScript(globalContext, script, nullptr, nullptr, 1, nullptr );
    // manual raw pointer management ... hopefully did not forget any
    JSGlobalContextRelease(globalContext);
    JSContextGroupRelease(group);
    JSStringRelease(func_clear_str);
    JSStringRelease(func_clearColor_str);
    JSStringRelease(script);
}