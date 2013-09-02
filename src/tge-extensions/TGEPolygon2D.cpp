#include "pch.h"
#include <tge-extensions/TGEPolygon2D.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
int TGEPolygon2D::_getVertex( lua_State* L ) {
	MOAI_LUA_SETUP ( TGEPolygon2D, "UN" )

	u32 id = state.GetValue < u32 >( 2, 1 ) - 1;

	if ( MOAILogMessages::CheckIndexPlusOne ( id, self->mVertices.Size (), L )) {
		USVec2D vertex = self->GetVertex( id );

		state.Push ( vertex.mX );
		state.Push ( vertex.mY );

		return 2;
	}

	return 0;
}

//----------------------------------------------------------------//
int TGEPolygon2D::_reserveVertices( lua_State* L ) {
	MOAI_LUA_SETUP ( TGEPolygon2D, "UN" )

	u32 total = state.GetValue < u32 >( 2, 0 );
	self->ReserveVertices ( total );

	return 0;
}

//----------------------------------------------------------------//
int TGEPolygon2D::_setVertex( lua_State* L ) {
	MOAI_LUA_SETUP ( TGEPolygon2D, "UNNN" )

	u32 id = state.GetValue < u32 >( 2, 1 ) - 1;
	float x = state.GetValue < float >( 3, 0.0f );
	float y = state.GetValue < float >( 4, 0.0f );

	if ( MOAILogMessages::CheckIndexPlusOne ( id, self->mVertices.Size (), L )) {
		self->SetVertex ( id, x, y );
	}

	return 0;
}

//================================================================//
// TGEPolygon2D
//================================================================//

//----------------------------------------------------------------//
USVec2D TGEPolygon2D::GetVertex( u32 id ) {

	if ( id < this->mVertices.Size ()) {
		return this->mVertices [ id ];
	}
	
	return USVec2D ( 0.0f, 0.0f );
}

//----------------------------------------------------------------//
void TGEPolygon2D::RegisterLuaClass ( MOAILuaState& state ) {

	UNUSED ( state );
}

//----------------------------------------------------------------//
void TGEPolygon2D::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	luaL_Reg regTable [] = {
		{ "getVertex",			_getVertex },
		{ "reserveVertices",	_reserveVertices },
		{ "setVertex",			_setVertex },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void TGEPolygon2D::ReserveVertices ( u32 total ) {

	this->mVertices.Init ( total );
}

//----------------------------------------------------------------//
void TGEPolygon2D::SetVertex( u32 id, float x, float y ) {

	if ( id < this->mVertices.Size ()) {
		this->mVertices [ id ].mX = x;
		this->mVertices [ id ].mY = y;
	}
}

//----------------------------------------------------------------//
TGEPolygon2D::TGEPolygon2D () {
	
	RTTI_SINGLE ( TGEPolygon2D )
}

//----------------------------------------------------------------//
TGEPolygon2D::~TGEPolygon2D () {

}
