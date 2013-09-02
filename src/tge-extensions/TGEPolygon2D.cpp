#include "pch.h"
#include <tge-extensions/TGEPolygon2D.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
int TGEPolygon2D::_clamp ( lua_State* L ) {
	MOAI_LUA_SETUP ( TGEPolygon2D, "UNN" )

	float x = state.GetValue < float >( 2, 0.0f );
	float y = state.GetValue < float >( 3, 0.0f );

	USVec2D result = self->Clamp ( USVec2D ( x, y ));
	state.Push ( result.mX );
	state.Push ( result.mY );

	return 2;
}

//----------------------------------------------------------------//
int TGEPolygon2D::_contains ( lua_State* L ) {
	MOAI_LUA_SETUP ( TGEPolygon2D, "UNN" )

	float x = state.GetValue < float >( 2, 0.0f );
	float y = state.GetValue < float >( 3, 0.0f );

	bool result = self->Contains ( USVec2D ( x, y ));
	state.Push ( result );

	return 1;
}

//----------------------------------------------------------------//
int TGEPolygon2D::_getVertex ( lua_State* L ) {
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
int TGEPolygon2D::_intersectsLine ( lua_State* L ) {
	MOAI_LUA_SETUP ( TGEPolygon2D, "UNNNN" )

	float x1 = state.GetValue < float >( 2, 0.0f );
	float y1 = state.GetValue < float >( 3, 0.0f );
	float x2 = state.GetValue < float >( 4, 0.0f );
	float y2 = state.GetValue < float >( 5, 0.0f );
	
	bool result = self->IntersectsLine ( USVec2D ( x1, y1 ), USVec2D ( x2, y2 ));
	state.Push ( result );

	return 1;
}

//----------------------------------------------------------------//
int TGEPolygon2D::_reserveVertices ( lua_State* L ) {
	MOAI_LUA_SETUP ( TGEPolygon2D, "UN" )

	u32 total = state.GetValue < u32 >( 2, 0 );
	self->ReserveVertices ( total );

	return 0;
}

//----------------------------------------------------------------//
int TGEPolygon2D::_setVertex ( lua_State* L ) {
	MOAI_LUA_SETUP ( TGEPolygon2D, "UNNN" )

	u32 id = state.GetValue < u32 >( 2, 1 ) - 1;
	float x = state.GetValue < float >( 3, 0.0f );
	float y = state.GetValue < float >( 4, 0.0f );

	if ( MOAILogMessages::CheckIndexPlusOne ( id, self->mVertices.Size (), L )) {
		self->SetVertex ( id, USVec2D ( x, y ));
	}

	return 0;
}

//================================================================//
// TGEPolygon2D
//================================================================//

//----------------------------------------------------------------//
void TGEPolygon2D::BlessEdges () {

	if ( this->mEdgesDirty ) {
		u32 total = this->mVertices.Size ();

		for ( u32 i = 0; i < total; ++i ) {
			USVec2D nextVertex = this->mVertices [ ( i + 1 ) % total ];
			USVec2D thisVertex = this->mVertices [ i ];

			this->mEdges [ i ] = nextVertex - thisVertex;
		}

		this->mEdgesDirty = false;
	}
}

//----------------------------------------------------------------//
USVec2D TGEPolygon2D::Clamp ( const USVec2D& point ) {

	if ( this->Contains ( point )) {
		return point;
	}

	this->BlessEdges ();

	u32 total = this->mVertices.Size ();
	USVec2D closestPoint;
	float minDistance = MAXFLOAT;
	
	for ( u32 i = 0; i < total; ++i ) {
		USVec2D v = this->mVertices [ i ];
		USVec2D edge = this->mEdges [ i ];
		
		float s = ( point - v ).Dot ( edge ) / edge.LengthSquared();
		v.Add ( edge, ZLFloat::Clamp( s, 0.0f, 1.0f ));
		
		float distance = v.DistSqrd ( point );
		if ( distance < minDistance ) {
			minDistance = distance;
			closestPoint = v;
		}
	}
	
	return closestPoint;
}

//----------------------------------------------------------------//
bool TGEPolygon2D::Contains ( const USVec2D& point ) {

	u32 count = this->mVertices.Size();
	bool result = false;

	float pX = point.mX;
	float pY = point.mY;

	for ( u32 i = 0, j = count - 1; i < count; j = i++ ) {
		float iX = this->mVertices [ i ].mX;
		float iY = this->mVertices [ i ].mY;
		float jX = this->mVertices [ j ].mX;
		float jY = this->mVertices [ j ].mY;

		if ((( iY > pY ) != ( jY > pY )) && ( pX < ( jX - iX ) * ( pY - iY ) / ( jY - iY ) + iX )) {
			result = !result;
		}
	}

	return result;
}

//----------------------------------------------------------------//
USVec2D TGEPolygon2D::GetVertex ( u32 id ) {

	if ( id < this->mVertices.Size ()) {
		return this->mVertices [ id ];
	}
	
	return USVec2D ( 0.0f, 0.0f );
}

//----------------------------------------------------------------//
bool TGEPolygon2D::IntersectsLine ( const USVec2D& start, const USVec2D& end ) {

	this->BlessEdges ();

	for ( u32 i = 0; i < this->mVertices.Size (); ++i ) {
		USVec2D vertex = this->mVertices [ i ];
		USVec2D edge = this->mEdges [ i ];
		USVec2D otherEdge = end - start;

		float denom = edge.mX * otherEdge.mY - edge.mY * otherEdge.mX;
		
		if ( denom == 0.0f ) {
			return false;
		}
		
		USVec2D w = vertex - start;
		float s = ( otherEdge.mX * w.mY - otherEdge.mY * w.mX ) / denom;
		float t = ( edge.mX * w.mY - edge.mY * w.mX ) / denom;
		
		if ( s > 0.0f && s < 1.0f && t > 0.0f && t < 1.0f ) {
			return true;
		}
	}
	
	return false;
}

//----------------------------------------------------------------//
void TGEPolygon2D::RegisterLuaClass ( MOAILuaState& state ) {

	UNUSED ( state );
}

//----------------------------------------------------------------//
void TGEPolygon2D::RegisterLuaFuncs ( MOAILuaState& state ) {
	
	luaL_Reg regTable [] = {
		{ "clamp",				_clamp },
		{ "contains",			_contains },
		{ "getVertex",			_getVertex },
		{ "intersectsLine",		_intersectsLine },
		{ "reserveVertices",	_reserveVertices },
		{ "setVertex",			_setVertex },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void TGEPolygon2D::ReserveVertices ( u32 total ) {

	this->mVertices.Init ( total );
	this->mEdges.Init ( total );
}

//----------------------------------------------------------------//
void TGEPolygon2D::SetVertex ( u32 id, const USVec2D& vertex ) {

	u32 total = this->mVertices.Size ();

	if ( id < total ) {
		this->mVertices [ id ] = vertex;
	}

	this->mEdgesDirty = true;
}

//----------------------------------------------------------------//
TGEPolygon2D::TGEPolygon2D () :
	mEdgesDirty ( true ) {
	
	RTTI_SINGLE ( TGEPolygon2D )
}

//----------------------------------------------------------------//
TGEPolygon2D::~TGEPolygon2D () {

}
