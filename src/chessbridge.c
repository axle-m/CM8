#include <jni.h>
#include "testFile.h"
#include <stdio.h>

JNIEXPORT jlong JNICALL Java_testFile_maskBishopAttacks
  (JNIEnv *env, jobject obj, jint pos) {
    
    return (1LL << pos);
}
