// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef	MOAIPOLYGONPATHGRAPH_H
#define	MOAIPOLYGONPATHGRAPH_H

#include <moai-sim/MOAIPathGraph.h>
#include <zl-util/ZLPolygon2D.h>

class MOAIPathFinder;

//================================================================//
// MOAIPolygonPathGraph
//================================================================//
/**	@name	MOAIPolygonPathGraph
	@text	Graph for pathfinding inside a concave polygon.
*/
class MOAIPolygonPathGraph :
	public MOAIPathGraph {
private:

	friend class MOAIPathFinder;
	
	USPolygon2D		mPolygon;

	//----------------------------------------------------------------//
	static int		_setPolygon					( lua_State* L );

	//----------------------------------------------------------------//
	void			PushNeighbors				( MOAIPathFinder& pathFinder, int nodeID );

public:
	
	DECL_LUA_FACTORY ( MOAIPolygonPathGraph )
	
	//----------------------------------------------------------------//
					MOAIPolygonPathGraph		();
					~MOAIPolygonPathGraph		();
	void			RegisterLuaClass			( MOAILuaState& state );
	void			RegisterLuaFuncs			( MOAILuaState& state );
};

#endif
