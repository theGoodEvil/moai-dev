
#include <tge-extensions/DWTracking.h>
#if ANDROID
#include <jni.h>

#include <moai-android/moaiext-jni.h>
#include <moai-android/JniUtils.h>

extern JavaVM* jvm;

#else

extern void dwTrackingLogProgress( cc8* msg );

#endif

int DWTracking::_trackProgress ( lua_State* L ) {

    MOAILuaState state( L );
    if (! state.CheckParams( 2, "S" ) ) return 0;

    cc8* page = state.GetValue< cc8* >( 2, "" );
    #if ANDROID
    JNI_GET_ENV( jvm, env );
    JNI_GET_JSTRING( page, jpage );
    jclass moaiApp = env->FindClass("com/dw/bienenretter/MoaiActivity");
    if (moaiApp == NULL) {
        ZLLog::Print( "DWTracking: Unable to find java class %s", "com/dw/bienenretter/MoaiActivity" );
    } else {
        jmethodID trackProgress = env->GetStaticMethodID( moaiApp, "trackProgress", "(Ljava/lang/String;)V" );
        if ( trackProgress == NULL ) {
            ZLLog::Print( "Unable to find static java method %s", "trackProgress" );
        } else  {
            env->CallStaticVoidMethod( moaiApp, trackProgress, jpage );
            return 1;
        }
    }
    return 0;
    #else
    dwTrackingLogProgress( page ); 
    return 1;
    #endif

}

DWTracking::DWTracking(  ) {
    RTTI_BEGIN
        RTTI_EXTEND( MOAILuaObject )
    RTTI_END
}

DWTracking::~DWTracking( ) {}

void DWTracking::RegisterLuaClass( MOAILuaState& state ) {
    luaL_Reg regTable [] =  {
         { "trackProgress", _trackProgress },
         { NULL, NULL }
    };
    luaL_register( state, 0, regTable );
}


