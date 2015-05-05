#pragma once

#include <moai-core/MOAILua.h>
#include <zl-util/ZLLeanArray.h>
#include <zl-util/ZLVec2D.h>

class TGEPolygon2D :
	public virtual MOAILuaObject {
private:

	ZLLeanArray < USVec2D >	mVertices;
	ZLLeanArray < USVec2D >	mEdges;
	bool					mEdgesDirty;

	//----------------------------------------------------------------//
	static int		_clamp						( lua_State* L );
	static int		_contains					( lua_State* L );
	static int		_getVertex					( lua_State* L );
	static int		_getVertexCount				( lua_State* L );
	static int		_intersectsLine				( lua_State* L );
	static int		_reserveVertices			( lua_State* L );
	static int		_setVertex					( lua_State* L );
	static int		_transform					( lua_State* L );

	//----------------------------------------------------------------//
	void			BlessEdges					();
	USVec2D			Clamp						( const USVec2D& point );
	bool			Contains					( const USVec2D& point );
	USVec2D			GetVertex					( u32 id );
	u32				GetVertexCount				();
	bool			IntersectsLine				( const USVec2D& start, const USVec2D& end );
	void			ReserveVertices				( u32 total );
	void			SetVertex					( u32 id, const USVec2D& vertex );
	void			Transform					( const ZLAffine3D& mtx );

public:
	
	DECL_LUA_FACTORY ( TGEPolygon2D )
	
	//----------------------------------------------------------------//
					TGEPolygon2D				();
					~TGEPolygon2D				();
	void			RegisterLuaClass			( MOAILuaState& state );
	void			RegisterLuaFuncs			( MOAILuaState& state );
};
