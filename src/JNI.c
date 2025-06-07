#include <jni.h>
#include "JNI.h"

#include "attackTables.h"
#include "bit.h"
#include "inputProcessor.h"
#include "randomizingRoutines.h"

JNIEXPORT jint JNICALL Java_JNI_square(JNIEnv *env, jobject obj, jint x) {
    return x * x;
}

JNIEXPORT jint JNICALL Java_JNI_bitScanForward(JNIEnv *env, jobject obj, jlong bb) {
    return bitScanForward((U64)bb);
}

JNIEXPORT jlong JNICALL Java_JNI_getPawnAttacks(JNIEnv *env, jobject obj, jboolean isWhite, jint square) {
    return getPawnAttacks(isWhite, square);
}
JNIEXPORT void JNICALL Java_JNI_initAttackTables(JNIEnv *env, jobject obj) {
    initAll();
}
JNIEXPORT jlong JNICALL Java_JNI_getKnightAttacks(JNIEnv *env, jobject obj, jint square) {
    return getKnightAttacks(square);
}
JNIEXPORT jint JNICALL Java_JNI_squareToPos(JNIEnv *env, jobject obj, jstring square) {
    const char *squareStr = (*env)->GetStringUTFChars(env, square, 0);
    int pos = squareToPos((char *)squareStr);
    (*env)->ReleaseStringUTFChars(env, square, squareStr);
    return pos;
}

JNIEXPORT jlong JNICALL Java_JNI_getBishopAttacks(JNIEnv *env, jobject obj, jint square, jlong blockers) {
    return getBishopAttacks(square, (U64)blockers);
}

JNIEXPORT jlong JNICALL Java_JNI_getRookAttacks(JNIEnv *env, jobject obj, jint square, jlong blockers) {
    return getRookAttacks(square, (U64)blockers);
}

JNIEXPORT jlong JNICALL Java_JNI_getQueenAttacks(JNIEnv *env, jobject obj, jint square, jlong blockers) {
    return getQueenAttacks(square, (U64)blockers);
}
