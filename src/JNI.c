#include <jni.h>
#include "JNI.h"      // The generated header
#include "inputProcessor.h"
#include "driver.h"

// JNI naming: Java_<Package>_<Class>_<MethodName>
// If no package: Java_<ClassName>_<MethodName>

JNIEXPORT jint JNICALL Java_JNI_makePlayerMove(JNIEnv *env, jobject obj, jstring move, jint promotion) {
    
    const char *c_move = (*env)->GetStringUTFChars(env, move, NULL);
    
    if (c_move == NULL) {
        return -1;  
    }

    int result = makePlayerMove((char *)c_move, (int)promotion);

    // Release the string
    (*env)->ReleaseStringUTFChars(env, move, c_move);

    return result;
}

JNIEXPORT jint JNICALL Java_JNI_getBestMove(JNIEnv *env, jobject obj, jint depth) {
    return getBestMove(depth); 
}

JNIEXPORT jint JNICALL Java_JNI_playBestMove(JNIEnv* env, jobject obj) {
    return playBestMove();
}

JNIEXPORT jint JNICALL Java_JNI_playBestFromFen(JNIEnv* env, jobject obj, jstring jfen) {
    const char* fen = (*env)->GetStringUTFChars(env, jfen, NULL);
    int result = playBestFromFen((char*)fen);
    (*env)->ReleaseStringUTFChars(env, jfen, fen);
    return result;
}
JNIEXPORT jint JNICALL Java_JNI_makeMove(JNIEnv *env, jobject thisObj, jint move, jint flag) {
    return makeMove(move, flag);
}


