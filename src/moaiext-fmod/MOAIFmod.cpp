// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include <moaiext-fmod/MOAIFmod.h>
#include <fmod.hpp>

#ifdef MOAI_OS_NACL
#include <fmodnacl.h>
#include "moai_nacl.h"
#include "ppapi/c/ppb.h"
#include "ppapi/cpp/instance.h"
#endif

//================================================================//
// local
//================================================================//

//----------------------------------------------------------------//
/**	@name	getMemoryStats
	@text	Get memory usage.

	@opt	boolean blocking - Default value is 'false.'
	@out	number currentAlloc
	@out	number maxAlloc
*/
int	MOAIFmod::_getMemoryStats( lua_State* L ) {
	USLuaState state ( L );
	
	bool blocking = state.GetValue < bool >( 1, false );
	
	int currentAlloc;
	int maxAlloc;
	
	FMOD_Memory_GetStats ( &currentAlloc, &maxAlloc, blocking );
	
	lua_pushnumber ( state, currentAlloc );
	lua_pushnumber ( state, maxAlloc );
	
	return 2;
}

//----------------------------------------------------------------//
/**	@name	init
	@text	Initializes the sound system.

	@out	nil
*/
int MOAIFmod::_init ( lua_State* L ) {

	USLuaState state ( L );
	
#ifdef MOAI_OS_NACL
	printf ( "Cannot initialize fmod on background thread\n" );
	return -1;
#endif

	MOAIFmod::Get ().OpenSoundSystem ();

	return 0;
}

//================================================================//
// MOAIFmod
//================================================================//

//----------------------------------------------------------------//
void MOAIFmod::CloseSoundSystem () {

	if ( !this->mSoundSys ) return;
	
	this->mSoundSys->close ();
	this->mSoundSys->release ();
	this->mSoundSys = 0;
}

//----------------------------------------------------------------//
MOAIFmod::MOAIFmod () :
	mSoundSys ( 0 ) {
}

//----------------------------------------------------------------//
MOAIFmod::~MOAIFmod () {

	this->CloseSoundSystem ();
}

//----------------------------------------------------------------//
void MOAIFmod::MuteChannels ( bool mute ) {

	this->mMainChannelGroup->setMute ( mute );
}

//----------------------------------------------------------------//
void MOAIFmod::OpenSoundSystem () {

	FMOD_RESULT result;

	FMOD::Debug_SetLevel(FMOD_DEBUG_ALL);

	result = FMOD::System_Create ( &this->mSoundSys ); // Create the main system object.
	if ( result != FMOD_OK ) return;

#ifdef MOAI_OS_NACL

	printf ( "init moai fmod system\n" );
	FMOD_NACL_EXTRADRIVERDATA extraDriverData;
	memset(&extraDriverData, 0, sizeof(FMOD_NACL_EXTRADRIVERDATA));
	extraDriverData.instance = g_instance->pp_instance();

	result = this->mSoundSys->init ( 32, FMOD_INIT_NORMAL, &extraDriverData );
#else
	result = this->mSoundSys->init ( 100, FMOD_INIT_NORMAL, 0 );
#endif

	if ( result != FMOD_OK ) return;
	
	result = this->mSoundSys->getMasterChannelGroup ( &this->mMainChannelGroup );
	if ( result != FMOD_OK ) return;

	printf ( "init moai fmod all done\n" );
}

//----------------------------------------------------------------//
void MOAIFmod::RegisterLuaClass ( USLuaState& state ) {
	
	luaL_Reg regTable [] = {
		{ "getMemoryStats",		_getMemoryStats },
		{ "init",				_init },
		{ NULL, NULL }
	};
	
	luaL_register ( state, 0, regTable );
}

//----------------------------------------------------------------//
void MOAIFmod::RegisterLuaFuncs ( USLuaState& state ) {
	UNUSED ( state );
}

//----------------------------------------------------------------//
void MOAIFmod::Update () {

	if ( this->mSoundSys ) {
		this->mSoundSys->update ();
	}
}

//----------------------------------------------------------------//
STLString MOAIFmod::ToString () {

	STLString repr;

	PRETTY_PRINT ( repr, mSoundSys )

	return repr;
}
