// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAITextureHeader.h>

//================================================================//
// MOAITextureHeader
//================================================================//

//----------------------------------------------------------------//
void MOAITextureHeader::Load ( ZLStream& stream ) {

	this->Invalidate ();
	stream.PeekBytes ( this->GetHeaderStart (), this->GetHeaderSize ());
}

//----------------------------------------------------------------//
MOAITextureHeader::MOAITextureHeader () {
}

//----------------------------------------------------------------//
MOAITextureHeader::~MOAITextureHeader () {
}
