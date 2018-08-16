/*
 * Copyright (C) 2015 Dominic Szablewski (dominic@phoboslab.org)
 * Copyright (C) 2015-2016 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef JSTypedArray_h
#define JSTypedArray_h

#include "JSBase.h"
#include "JSValueRef.h"

#ifdef __cplusplus
extern "C" {
#endif

// ------------- Typed Array functions --------------

/*!
 @function
 @abstract           Returns a temporary pointer to the backing store of a JavaScript Typed Array object.
 @param ctx          The execution context to use.
 @param object       The Typed Array object whose backing store pointer to return.
 @param exception    A pointer to a JSValueRef in which to store an exception, if any. Pass NULL if you do not care to store an exception.
 @result             A pointer to the raw data buffer that serves as object's backing store or NULL if object is not a Typed Array object.
 @discussion         The pointer returned by this function is temporary and is not guaranteed to remain valid across JavaScriptCore API calls.
 */
JS_EXPORT void* JSObjectGetTypedArrayBytesPtr(JSContextRef ctx, JSObjectRef object, JSValueRef* exception);

/*!
 @function
 @abstract           Returns the length of a JavaScript Typed Array object.
 @param ctx          The execution context to use.
 @param object       The Typed Array object whose length to return.
 @param exception    A pointer to a JSValueRef in which to store an exception, if any. Pass NULL if you do not care to store an exception.
 @result             The length of the Typed Array object or 0 if the object is not a Typed Array object.
 */
JS_EXPORT size_t JSObjectGetTypedArrayLength(JSContextRef ctx, JSObjectRef object, JSValueRef* exception);

/*!
 @function
 @abstract           Returns the byte length of a JavaScript Typed Array object.
 @param ctx          The execution context to use.
 @param object       The Typed Array object whose byte length to return.
 @param exception    A pointer to a JSValueRef in which to store an exception, if any. Pass NULL if you do not care to store an exception.
 @result             The byte length of the Typed Array object or 0 if the object is not a Typed Array object.
 */
JS_EXPORT size_t JSObjectGetTypedArrayByteLength(JSContextRef ctx, JSObjectRef object, JSValueRef* exception);

/*!
 @function
 @abstract           Returns the byte offset of a JavaScript Typed Array object.
 @param ctx          The execution context to use.
 @param object       The Typed Array object whose byte offset to return.
 @param exception    A pointer to a JSValueRef in which to store an exception, if any. Pass NULL if you do not care to store an exception.
 @result             The byte offset of the Typed Array object or 0 if the object is not a Typed Array object.
 */
JS_EXPORT size_t JSObjectGetTypedArrayByteOffset(JSContextRef ctx, JSObjectRef object, JSValueRef* exception);

/*!
 @function
 @abstract           Returns the JavaScript Array Buffer object that is used as the backing of a JavaScript Typed Array object.
 @param ctx          The execution context to use.
 @param object       The JSObjectRef whose Typed Array type data pointer to obtain.
 @param exception    A pointer to a JSValueRef in which to store an exception, if any. Pass NULL if you do not care to store an exception.
 @result             A JSObjectRef with a JSTypedArrayType of kJSTypedArrayTypeArrayBuffer or NULL if object is not a Typed Array.
 */
JS_EXPORT JSObjectRef JSObjectGetTypedArrayBuffer(JSContextRef ctx, JSObjectRef object, JSValueRef* exception);

// ------------- Array Buffer functions -------------
/*!
 @function
 @abstract         Returns a pointer to the data buffer that serves as the backing store for a JavaScript Typed Array object.
 @param object     The Array Buffer object whose internal backing store pointer to return.
 @param exception  A pointer to a JSValueRef in which to store an exception, if any. Pass NULL if you do not care to store an exception.
 @result           A pointer to the raw data buffer that serves as object's backing store or NULL if object is not an Array Buffer object.
 @discussion       The pointer returned by this function is temporary and is not guaranteed to remain valid across JavaScriptCore API calls.
 */
JS_EXPORT void* JSObjectGetArrayBufferBytesPtr(JSContextRef ctx, JSObjectRef object, JSValueRef* exception);

/*!
 @function
 @abstract         Returns the number of bytes in a JavaScript data object.
 @param ctx        The execution context to use.
 @param object     The JS Arary Buffer object whose length in bytes to return.
 @param exception  A pointer to a JSValueRef in which to store an exception, if any. Pass NULL if you do not care to store an exception.
 @result           The number of bytes stored in the data object.
 */
JS_EXPORT size_t JSObjectGetArrayBufferByteLength(JSContextRef ctx, JSObjectRef object, JSValueRef* exception);

#ifdef __cplusplus
}
#endif

#endif /* JSTypedArray_h */