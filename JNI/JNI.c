#include <jni.h>
#include "JNI.h"      // The generated header
#include "inputProcessor.h"
#include "driver.h"

// JNI naming: Java_<Package>_<Class>_<MethodName>
// If no package: Java_<ClassName>_<MethodName>

JNIEXPORT jint JNICALL Java_JNI_makePlayerMove(JNIEnv *env, jobject obj, jstring move) {
    // Convert Java string to C string
    const char *c_move = (*env)->GetStringUTFChars(env, move, NULL);
    
    if (c_move == NULL) {
        return -1;  // OutOfMemoryError is thrown by JVM automatically
    }

    int result = makePlayerMove((char *)c_move);

    // Release the string
    (*env)->ReleaseStringUTFChars(env, move, c_move);

    return result;
}

JNIEXPORT jint JNICALL Java_JNI_getBestMove(JNIEnv *env, jobject obj) {
    return getBestMove();
}
