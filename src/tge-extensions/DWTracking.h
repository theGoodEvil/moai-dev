#pragma once
#include <moai-core/headers.h>

class DWTracking:
    public MOAIGlobalClass< DWTracking, MOAILuaObject >  {
   
private:

    static int _trackProgress   ( lua_State* L );

public:
    DECL_LUA_SINGLETON( DWTracking )
    
    DWTracking  ( );
    ~DWTracking ( );
     
    void RegisterLuaClass( MOAILuaState& state );
};



