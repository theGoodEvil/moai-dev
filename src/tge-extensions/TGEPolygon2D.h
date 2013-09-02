#pragma once

#include <moai-core/MOAILua.h>
#include <zl-util/ZLLeanArray.h>
#include <zl-util/ZLVec2D.h>

class TGEPolygon2D :
	public virtual MOAILuaObject {
private:

	ZLLeanArray < USVec2D >	mVertices;

	//----------------------------------------------------------------//
	static int		_getVertex					( lua_State* L );
	static int		_reserveVertices			( lua_State* L );
	static int		_setVertex					( lua_State* L );

	//----------------------------------------------------------------//
	USVec2D			GetVertex					( u32 id );
	void			ReserveVertices				( u32 total );
	void			SetVertex					( u32 id, float x, float y );

public:
	
	DECL_LUA_FACTORY ( TGEPolygon2D )
	
	//----------------------------------------------------------------//
					TGEPolygon2D				();
					~TGEPolygon2D				();
	void			RegisterLuaClass			( MOAILuaState& state );
	void			RegisterLuaFuncs			( MOAILuaState& state );
};
