#include "jni_refs.hpp"
#include "helpers/general.hpp"
#include "models/jni_renderer.hpp"

// From rive-cpp
#include "artboard.hpp"
#include "animation/linear_animation_instance.hpp"
//

#include <jni.h>

std::string jstring2string(JNIEnv *env, jstring jStr)
{
    const char *cstr = env->GetStringUTFChars(jStr, NULL);
    std::string str = std::string(cstr);
    return str;
}

#ifdef __cplusplus
extern "C"
{
#endif

    using namespace rive_android;

    // ARTBOARD

    JNIEXPORT jstring JNICALL Java_app_rive_runtime_kotlin_Artboard_nativeName(
        JNIEnv *env,
        jobject thisObj,
        jlong ref)
    {
        ::globalJNIEnv = env;

        rive::Artboard *artboard = (rive::Artboard *)ref;

        return env->NewStringUTF(artboard->name().c_str());
    }

    JNIEXPORT jlong JNICALL Java_app_rive_runtime_kotlin_Artboard_nativeFirstAnimation(
        JNIEnv *env,
        jobject thisObj,
        jlong ref)
    {
        ::globalJNIEnv = env;

        rive::Artboard *artboard = (rive::Artboard *)ref;

        return (jlong)artboard->firstAnimation<rive::LinearAnimation>();
    }

    JNIEXPORT jlong JNICALL Java_app_rive_runtime_kotlin_Artboard_nativeAnimationByIndex(
        JNIEnv *env,
        jobject thisObj,
        jlong ref,
        jint index)
    {
        ::globalJNIEnv = env;

        rive::Artboard *artboard = (rive::Artboard *)ref;

        return (jlong)artboard->animation<rive::LinearAnimation>(index);
    }

    JNIEXPORT jlong JNICALL Java_app_rive_runtime_kotlin_Artboard_nativeAnimationByName(
        JNIEnv *env,
        jobject thisObj,
        jlong ref,
        jstring name)
    {
        ::globalJNIEnv = env;

        rive::Artboard *artboard = (rive::Artboard *)ref;

        return (jlong)artboard->animation<rive::LinearAnimation>(
            jstring2string(env, name));
    }

    JNIEXPORT jlong JNICALL Java_app_rive_runtime_kotlin_Artboard_nativeAnimationCount(
        JNIEnv *env,
        jobject thisObj,
        jlong ref)
    {
        ::globalJNIEnv = env;

        rive::Artboard *artboard = (rive::Artboard *)ref;

        return (jint)artboard->animationCount();
    }

    JNIEXPORT void JNICALL Java_app_rive_runtime_kotlin_Artboard_nativeAdvance(
        JNIEnv *env,
        jobject thisObj,
        jlong ref,
        jfloat elapsedTime)
    {
        ::globalJNIEnv = env;

        rive::Artboard *artboard = (rive::Artboard *)ref;
        artboard->advance(elapsedTime);
    }

    JNIEXPORT jlong JNICALL Java_app_rive_runtime_kotlin_Artboard_nativeBounds(
        JNIEnv *env,
        jobject thisObj,
        jlong ref)
    {
        ::globalJNIEnv = env;

        rive::Artboard *artboard = (rive::Artboard *)ref;
        auto bounds = new rive::AABB(artboard->bounds());
        return (jlong)bounds;
    }

    JNIEXPORT void JNICALL Java_app_rive_runtime_kotlin_Artboard_nativeDraw(
        JNIEnv *env,
        jobject thisObj,
        jlong ref,
        jlong rendererRef,
        jobject rendererObj)
    {
        ::globalJNIEnv = env;
        ::globalJNIObj = rendererObj;

        rive::Artboard *artboard = (rive::Artboard *)ref;
        ::JNIRenderer *renderer = (::JNIRenderer *)rendererRef;
        artboard->draw(renderer);
    }

#ifdef __cplusplus
}
#endif
