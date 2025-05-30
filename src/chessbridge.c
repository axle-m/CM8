#include <jni.h>
#include "testFile.h"  // this was generated
#include "bit.h"
#include "attackTables.h"

// This is the C implementation of the native Java method
JNIEXPORT jlong JNICALL Java_testFile_getBishopAttackMask(JNIEnv *env, jobject obj, jint pos) {
    return (jlong)maskBishopAttacks((int)pos);
}
JNIEXPORT jlong JNICALL Java_testFile_getKnightAttacks(JNIEnv *env, jobject obj, jint square) {
    return (jlong)maskKnightAttacks(square); 
}