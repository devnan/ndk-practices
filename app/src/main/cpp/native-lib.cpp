#include <jni.h>
#include <string>
#include <assert.h>
#include "native-lib.h"

#define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0]))) //数组x大小

extern "C"

JNIEXPORT jstring JNICALL Java_com_devnan_ndk_MainActivity_stringFromJNI2(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello World!";
    return env->NewStringUTF(hello.c_str());
}

JNIEXPORT jstring JNICALL stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello JNI!";
    return env->NewStringUTF(hello.c_str());
}

/**
 * 调用JNIEnv函数RegisterNatives进行注册
 *
 * jint RegisterNatives(jclass clazz, const JNINativeMethod* methods, jint nMethods)
 * clazz: java类名，通过FindClass得到
 * methods: JNINativeMethod结构体指针
 * nMethods: 方法个数
 */
static int registerNatives(JNIEnv *env) {
    jclass clazz;
    clazz = env->FindClass(className);
    if (clazz == NULL) {
        return JNI_FALSE;
    }
    if (env->RegisterNatives(clazz, gMethods, NELEM(gMethods)) < 0) {
        return JNI_FALSE;
    }

    return JNI_TRUE;
}

/**
 * System.loadLibrary()最后会调用到此函数
 */
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        return JNI_ERR;
    }
    assert(env != NULL);
    if (!registerNatives(env)) {
        return JNI_ERR;
    }
    return JNI_VERSION_1_6;
}

