// Copyright (c) 2010-2011 Zipline Games, Inc. All Rights Reserved.
// http://getmoai.com

#ifndef MOAIPKMHEADER_H
#define MOAIPKMHEADER_H

#include <moai-sim/MOAITextureHeader.h>

//================================================================//
// MOAIPkmHeader
//================================================================//
class MOAIPkmHeader :
	public MOAITextureHeader {
private:
	
	static const u32 HEADER_SIZE		= 16;
	static const u32 PKM_FILE_MAGIC		= 0x204d4b50;
	static const u16 PKM_VERSION_1		= 0x3031;
	
	u32 mPKM;				// should be 'P' 'K' 'M' ' '
	u16 mVersion;			// should be '1' '0'
	u16 mType;				// should be 0 (ETC1_RGB_NO_MIPMAPS)
	u16 mDataWidth;			// pixel width of image data (multiple of 4)
	u16 mDataHeight;		// pixel height of image data (multiple of 4)
	u16 mWidth;				// image pixel width (can be less due to padding)
	u16 mHeight;			// image pixel height (can be less due to padding)

public:

	//----------------------------------------------------------------//
	virtual u32				GetHeaderSize			();
	virtual void*			GetHeaderStart			();
	virtual u32				GetHeight				();
	virtual u32				GetTotalSize			();
	virtual u32				GetWidth				();
	virtual bool			IsValid					();
	virtual void			Invalidate				();
							MOAIPkmHeader			();
	virtual					~MOAIPkmHeader			();
};

#endif
