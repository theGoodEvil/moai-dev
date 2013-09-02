// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIPolygonPathGraph.h>

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	setPolygon
	@text	Set polygon data to use for pathfinding.

	@in		MOAIPolygonPathGraph self
	@in		table verts					Array containg polygon vertex coordinate components. ( t[1] = x0, t[2] = y0, t[3] = x1, t[4] = y1... )
	@out	nil
*/
int MOAIPolygonPathGraph::_setPolygon ( lua_State* L ) {
	MOAI_LUA_SETUP ( MOAIPolygonPathGraph, "UT" )

	u32 totalVerts = lua_objlen ( state, 2 ) / 2;

	self->mPolygon.Init( totalVerts );

	USVec2D vert;

	int itr = state.PushTableItr ( 2 );
	for (u32 idx = 0 ; state.TableItrNext ( itr ); ++idx ) {
		
		float val = state.GetValue < float >( -1, 0 );
		
		if ( idx & 0x01 ) {
			vert.mY = val;
			self->mPolygon.SetVert(idx / 2, vert);
		}
		else {
			vert.mX = val;
		}
	}
	
	self->mPolygon.Bless();

	return 0;
}

//================================================================//
// MOAIPolygonPathGraph
//================================================================//

//----------------------------------------------------------------//
MOAIPolygonPathGraph::MOAIPolygonPathGraph () {
	
	RTTI_SINGLE ( MOAIPolygonPathGraph )
}

//----------------------------------------------------------------//
MOAIPolygonPathGraph::~MOAIPolygonPathGraph () {

}

//----------------------------------------------------------------//
void MOAIPolygonPathGraph::PushNeighbors ( MOAIPathFinder& pathFinder, int nodeID ) {
	
	// TODO
}

//----------------------------------------------------------------//
void MOAIPolygonPathGraph::RegisterLuaClass ( MOAILuaState& state ) {

}

//----------------------------------------------------------------//
void MOAIPolygonPathGraph::RegisterLuaFuncs ( MOAILuaState& state ) {
	MOAIPathGraph::RegisterLuaFuncs ( state );
	
	luaL_Reg regTable [] = {
		{ "setPolygon",			_setPolygon },
		{ NULL, NULL }
	};

	luaL_register ( state, 0, regTable );
}
