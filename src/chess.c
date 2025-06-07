#include <jni.h>
#include <stdio.h>
#include "JNI.h"       
#include "attackTables.h" 

JNIEXPORT jlong JNICALL Java_JNI_getBishopAttacks(JNIEnv *env, jobject obj, jlong occupancy, jint square) {
    return (jlong) getBishopAttacks((U64) occupancy, (int) square);
}

JNIEXPORT jlong JNICALL Java_JNI_getRookAttacks(JNIEnv *env, jobject obj, jlong occupancy, jint square) {
    return (jlong) getRookAttacks((U64) occupancy, (int) square);
}
