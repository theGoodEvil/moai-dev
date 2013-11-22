// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#include "pch.h"
#include <moai-sim/MOAIPkmHeader.h>

//================================================================//
// MOAIPkmHeader
//================================================================//

//----------------------------------------------------------------//
u32 MOAIPkmHeader::GetHeaderSize () {

	return 16;
}

//----------------------------------------------------------------//
void* MOAIPkmHeader::GetHeaderStart () {

	return &this->mPKM;
}

//----------------------------------------------------------------//
u32 MOAIPkmHeader::GetHeight () {

	return this->mHeight;
}

//----------------------------------------------------------------//
u32 MOAIPkmHeader::GetTotalSize () {

	return this->mDataWidth * this->mDataHeight / 2;
}

//----------------------------------------------------------------//
u32 MOAIPkmHeader::GetWidth () {

	return this->mWidth;
}

//----------------------------------------------------------------//
void MOAIPkmHeader::Invalidate () {
	this->mPKM = 0;
}

//----------------------------------------------------------------//
bool MOAIPkmHeader::IsValid () {

	return this->mPKM == PKM_FILE_MAGIC && this->mVersion == PKM_VERSION_1;
}

//----------------------------------------------------------------//
MOAIPkmHeader::MOAIPkmHeader () {

	this->Invalidate ();
}

//----------------------------------------------------------------//
MOAIPkmHeader::~MOAIPkmHeader () {
}
