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

JSValueRef _clear(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
    double mask = JSValueToNumber(ctx, argv[0], nullptr);
    glClear(mask);
    return JSValueMakeUndefined(ctx);
}

JSValueRef _clearColor(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
    double red = JSValueToNumber(ctx, argv[0], nullptr);
    double green = JSValueToNumber(ctx, argv[1], nullptr);
    double blue = JSValueToNumber(ctx, argv[2], nullptr);
    double alpha = JSValueToNumber(ctx, argv[3], nullptr);
    glClearColor(red, green, blue, alpha);
    return JSValueMakeUndefined(ctx);
}

JSValueRef _createShader(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
	int type = JSValueToNumber(ctx, argv[0], nullptr);
	GLuint shader = glCreateShader(type);
	return JSValueMakeNumber(ctx, shader);
}

JSValueRef _shaderSource(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
	int shader = JSValueToNumber(ctx, argv[0], nullptr);
	JSStringRef source = JSValueToStringCopy(ctx, argv[1], nullptr);
	size_t buf_size = JSStringGetLength(source);
	char* buf = new char[buf_size];
	JSStringGetUTF8CString(source, buf, buf_size + 1);
	LOGD("Script %s", buf);
	GLsizei count = 1;
	GLint length[] = { -1 };
	const GLchar* string[] = { buf };
	glShaderSource(shader, count, string, length);
	return JSValueMakeUndefined(ctx);
}

JSValueRef _compileShader(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
	glCompileShader(JSValueToNumber(ctx, argv[0], nullptr));
	return JSValueMakeUndefined(ctx);
}

JSValueRef _getShaderParameter(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
	GLint shader = JSValueToNumber(ctx, argv[0], nullptr);
	GLenum pname = JSValueToNumber(ctx, argv[1], nullptr);
	int param[1];
	glGetShaderiv(shader, pname, param);
	return JSValueMakeUndefined(ctx);
}

JSValueRef _createProgram(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
	GLint program = glCreateProgram();
	return JSValueMakeNumber(ctx, program);
}

JSValueRef _attachShader(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
	GLint program = JSValueToNumber(ctx, argv[0], nullptr);
	GLenum shader = JSValueToNumber(ctx, argv[1], nullptr);
	glAttachShader(program, shader);
	return JSValueMakeUndefined(ctx);
}

JSValueRef _linkProgram(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
	GLint program = JSValueToNumber(ctx, argv[0], nullptr);
	glLinkProgram(program);
	return JSValueMakeUndefined(ctx);
}

JSValueRef _getProgramParameter(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
	GLint shader = JSValueToNumber(ctx, argv[0], nullptr);
	GLenum pname = JSValueToNumber(ctx, argv[1], nullptr);
	int param[1];
	glGetProgramiv(shader, pname, param);
	return JSValueMakeUndefined(ctx);
}

JSValueRef _createBuffer(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
	GLuint buf[1];
	glGenBuffers(1, buf);
	return JSValueMakeNumber(ctx, buf[0]);
}

JSValueRef _bindBuffer(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
	GLenum target = JSValueToNumber(ctx, argv[0], nullptr);
	GLint buf = JSValueToNumber(ctx, argv[1], nullptr);
	glBindBuffer(target, buf);
	return JSValueMakeUndefined(ctx);
}

// 需要完善
JSValueRef _bufferData(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
	GLenum target = JSValueToNumber(ctx, argv[0], nullptr);
	GLenum usage = JSValueToNumber(ctx, argv[2], nullptr);
	JSObjectRef obj = JSValueToObject(ctx, argv[1], nullptr);
	GLsizeiptr size = JSObjectGetTypedArrayByteLength(ctx, obj, nullptr);
	LOGD("Len: %d", size);
	void *ptr = JSObjectGetTypedArrayBytesPtr(ctx, obj, nullptr);
	LOGD("Content: %d", ptr);
	glBufferData(target, size, ptr, usage);
	return JSValueMakeUndefined(ctx);
}

JSValueRef _getAttribLocation(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
	GLuint program = JSValueToNumber(ctx, argv[0], nullptr);
	JSStringRef jname = JSValueToStringCopy(ctx, argv[1], nullptr);
	size_t size = JSStringGetLength(jname);
	char* name = new char[size + 1];
	JSStringGetUTF8CString(jname, name, size);
	return JSValueMakeNumber(ctx, glGetAttribLocation(program, name));
}

JSValueRef _vertexAttribPointer(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
	GLuint index = JSValueToNumber(ctx, argv[0], nullptr);
	GLint size = JSValueToNumber(ctx, argv[1], nullptr);
	GLenum type = JSValueToNumber(ctx, argv[2], nullptr);
	GLboolean normalized = (unsigned char)JSValueToNumber(ctx, argv[3], nullptr);
	GLsizei stride = JSValueToNumber(ctx, argv[4], nullptr);
	void *ptr = (void *)JSValueToObject(ctx, argv[5], nullptr);
	glVertexAttribPointer(index, size, type, normalized, stride, ptr);
	return JSValueMakeUndefined(ctx);
}

JSValueRef _enableVertexAttribArray(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
	GLuint index = JSValueToNumber(ctx, argv[0], nullptr);
	glEnableVertexAttribArray(index);
	return JSValueMakeUndefined(ctx);
}

JSValueRef _useProgram(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
	GLuint program = JSValueToNumber(ctx, argv[0], nullptr);
	glUseProgram(program);
	return JSValueMakeUndefined(ctx);
}

JSValueRef _lineWidth(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
	glLineWidth(JSValueToNumber(ctx, argv[0], nullptr));
	return JSValueMakeUndefined(ctx);
}

JSValueRef _drawArrays(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
	GLenum mode = JSValueToNumber(ctx, argv[0], nullptr);
	GLint first = JSValueToNumber(ctx, argv[1], nullptr);
	GLsizei count = JSValueToNumber(ctx, argv[2], nullptr);
	glDrawArrays(mode, first, count);
	return JSValueMakeUndefined(ctx);
}

JSValueRef _log(JSContextRef ctx, JSObjectRef thisObj, JSObjectRef func, size_t argsCount, const JSValueRef argv[], JSValueRef& exception) {
	JSStringRef msg = JSValueToStringCopy(ctx, argv[0], nullptr);
	size_t buf_size = JSStringGetLength(msg);
	char* buf = new char[buf_size];
	JSStringGetUTF8CString(msg, buf, buf_size + 1);
	LOGD("%s", buf);
	return JSValueMakeUndefined(ctx);
}


void bindVariable(JSContextRef ctx, JSObjectRef thisObj, const char* string, JSValueRef val) {
	JSStringRef str = JSStringCreateWithUTF8CString(string);
	JSObjectSetProperty(ctx, thisObj, str, val, kJSPropertyAttributeNone, nullptr);
	JSStringRelease(str);
}

void bindFunction(JSContextRef ctx, JSObjectRef thisObj, const char* string, JSObjectCallAsFunctionCallback function) {
	JSStringRef str = JSStringCreateWithUTF8CString(string);
	JSObjectRef func = JSObjectMakeFunctionWithCallback(ctx, str, function);
	JSObjectSetProperty(ctx, thisObj, str, func, kJSPropertyAttributeNone, nullptr);
	JSStringRelease(str);
}

JSContextGroupRef group;
JSGlobalContextRef globalContext;
JSObjectRef globalObject;
bool bootstrapped = false;

extern "C" JNIEXPORT void
JNICALL
Java_fex_momo_com_androidjscgl_MainActivity_bootstrap(JNIEnv *env, jobject instance) {
	if (bootstrapped) {
		return;
	}

	group = JSContextGroupCreate();
	globalContext = JSGlobalContextCreateInGroup(group, nullptr);
	globalObject = JSContextGetGlobalObject(globalContext);

	JSStringRef gl_obj_str = JSStringCreateWithUTF8CString("gl");
	JSObjectRef gl_obj = JSObjectMake(globalContext, nullptr, nullptr);
	JSObjectSetProperty(globalContext, globalObject, gl_obj_str, gl_obj, kJSPropertyAttributeNone, nullptr);

	JSStringRef console_obj_str = JSStringCreateWithUTF8CString("console");
	JSObjectRef console_obj = JSObjectMake(globalContext, nullptr, nullptr);
	JSObjectSetProperty(globalContext, globalObject, console_obj_str, console_obj, kJSPropertyAttributeNone, nullptr);

	bindFunction(globalContext, console_obj, "log", (JSObjectCallAsFunctionCallback)_log);
	bindVariable(globalContext, gl_obj, "COLOR_BUFFER_BIT", JSValueMakeNumber(globalContext, GL_COLOR_BUFFER_BIT));
	bindVariable(globalContext, gl_obj, "ARRAY_BUFFER", JSValueMakeNumber(globalContext, GL_ARRAY_BUFFER));
	bindVariable(globalContext, gl_obj, "VERTEX_SHADER", JSValueMakeNumber(globalContext, GL_VERTEX_SHADER));
	bindVariable(globalContext, gl_obj, "COMPILE_STATUS", JSValueMakeNumber(globalContext, GL_COMPILE_STATUS));
	bindVariable(globalContext, gl_obj, "FRAGMENT_SHADER", JSValueMakeNumber(globalContext, GL_FRAGMENT_SHADER));
	bindVariable(globalContext, gl_obj, "LINK_STATUS", JSValueMakeNumber(globalContext, GL_LINK_STATUS));
	bindVariable(globalContext, gl_obj, "STATIC_DRAW", JSValueMakeNumber(globalContext, GL_STATIC_DRAW));
	bindVariable(globalContext, gl_obj, "FLOAT", JSValueMakeNumber(globalContext, GL_FLOAT));
	bindVariable(globalContext, gl_obj, "LINE_LOOP", JSValueMakeNumber(globalContext, GL_LINE_LOOP));

	bindFunction(globalContext, gl_obj, "createShader", (JSObjectCallAsFunctionCallback)_createShader);
	bindFunction(globalContext, gl_obj, "shaderSource", (JSObjectCallAsFunctionCallback)_shaderSource);
	bindFunction(globalContext, gl_obj, "compileShader", (JSObjectCallAsFunctionCallback)_compileShader);
	bindFunction(globalContext, gl_obj, "getShaderParameter", (JSObjectCallAsFunctionCallback)_getShaderParameter);
	bindFunction(globalContext, gl_obj, "clear", (JSObjectCallAsFunctionCallback)_clear);
	bindFunction(globalContext, gl_obj, "clearColor", (JSObjectCallAsFunctionCallback)_clearColor);
	bindFunction(globalContext, gl_obj, "createProgram", (JSObjectCallAsFunctionCallback)_createProgram);
	bindFunction(globalContext, gl_obj, "getProgramParameter", (JSObjectCallAsFunctionCallback)_getProgramParameter);
	bindFunction(globalContext, gl_obj, "attachShader", (JSObjectCallAsFunctionCallback)_attachShader);
	bindFunction(globalContext, gl_obj, "linkProgram", (JSObjectCallAsFunctionCallback)_linkProgram);
	bindFunction(globalContext, gl_obj, "createBuffer", (JSObjectCallAsFunctionCallback)_createBuffer);
	bindFunction(globalContext, gl_obj, "bindBuffer", (JSObjectCallAsFunctionCallback)_bindBuffer);
	bindFunction(globalContext, gl_obj, "bufferData", (JSObjectCallAsFunctionCallback)_bufferData);
	bindFunction(globalContext, gl_obj, "getAttribLocation", (JSObjectCallAsFunctionCallback)_getAttribLocation);
	bindFunction(globalContext, gl_obj, "vertexAttribPointer", (JSObjectCallAsFunctionCallback)_vertexAttribPointer);
	bindFunction(globalContext, gl_obj, "enableVertexAttribArray", (JSObjectCallAsFunctionCallback)_enableVertexAttribArray);
	bindFunction(globalContext, gl_obj, "useProgram", (JSObjectCallAsFunctionCallback)_useProgram);
	bindFunction(globalContext, gl_obj, "lineWidth", (JSObjectCallAsFunctionCallback)_lineWidth);
	bindFunction(globalContext, gl_obj, "drawArrays", (JSObjectCallAsFunctionCallback)_drawArrays);

	// manual raw pointer management ... hopefully did not forget any
	JSStringRelease(gl_obj_str);
	bootstrapped = true;
}

extern "C" JNIEXPORT void
JNICALL
Java_fex_momo_com_androidjscgl_MainActivity_runScript(JNIEnv *env, jobject instance, jstring jscode) {
	// make javascript
	JSStringRef script = JSStringCreateWithCharacters(env -> GetStringChars(jscode, nullptr), env -> GetStringLength(jscode));
	// evaluate it
	JSEvaluateScript(globalContext, script, nullptr, nullptr, 1, nullptr );
	JSStringRelease(script);
}

extern "C" JNIEXPORT void
JNICALL
Java_fex_momo_com_androidjscgl_MainActivity_nativeSurfaceChanged(JNIEnv *env, jobject instance, jint w, jint h) {
	glViewport(0, 0, w, h);
}

extern "C" JNIEXPORT void
JNICALL
Java_fex_momo_com_androidjscgl_MainActivity_destroy(JNIEnv *env, jobject instance) {
	JSGlobalContextRelease(globalContext);
	JSContextGroupRelease(group);
};