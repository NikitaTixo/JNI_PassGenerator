#include "nativeLib_NativeLib.h"
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <omp.h>

using namespace std;

void generatePasswords(const string& symbols, int length, const string& password) {

    omp_set_num_threads(2);

    if (length == 0) {
        #pragma omp critical
        {
            const string path = "myfile.txt";
            fstream fs;
            fs.open(path, fstream::in | fstream::out | fstream::app);
            fs << password << "\n";
            fs.close();
        }
        return;
    }

    #pragma omp parallel for
    for (int i = 0; i < symbols.length(); i++) {
        string newPassword = password + symbols[i];
        generatePasswords(symbols, length - 1, newPassword);
    }
}

extern "C" {
    JNIEXPORT void JNICALL Java_nativeLib_NativeLib_generatePass(
    JNIEnv *env,
    jclass cls,
    jobjectArray symbols,
    jint length,
    jstring password) {
        const char* passwordStr = env->GetStringUTFChars(password, nullptr);
        jint arrLength = env->GetArrayLength(symbols);

        string symbolsStr;
        for (jint i = 0; i < arrLength; i++) {
            jstring symbol = (jstring)env->GetObjectArrayElement(symbols, i);
            const char* symbolStr = env->GetStringUTFChars(symbol, nullptr);
            symbolsStr += symbolStr;
            env->ReleaseStringUTFChars(symbol, symbolStr);
        }

        generatePasswords(symbolsStr, length, passwordStr);
        env->ReleaseStringUTFChars(password, passwordStr);
    }
}

