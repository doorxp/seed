/******************************************************************************
 ** Copyright (c) 2010 Seed Developers
 ** All rights reserved
 ** Contact: licensing@seedframework.org
 ** Website: http://www.seedframework.org

 ** This file is part of the Seed Framework.

 ** Commercial Usage
 ** Seed Framework is available under proprietary license for those who cannot,
 ** or choose not to, use LGPL and GPL code in their projects (eg. iPhone,
 ** Nintendo Wii and others).

 ** GNU Lesser General Public License Usage
 ** Alternatively, this file may be used under the terms of the GNU Lesser
 ** General Public License version 2.1 as published by the Free Software
 ** Foundation and appearing in the file LICENSE.LGPL included in the
 ** packaging of this file.  Please review the following information to
 ** ensure the GNU Lesser General Public License version 2.1 requirements
 ** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
 **
 ** In addition, as a special exception, Seed developers gives you certain
 ** additional rights. These rights are described in the Seed Framework LGPL
 ** Exception version 1.1, included in the file LGPL_EXCEPTION.txt in this
 ** package.
 **
 ** If you have questions regarding the use of this file, please contact
 ** Seed developers at licensing@seedframework.org.
 **
 *****************************************************************************/

/*! \file Text.cpp
	\author	Danny Angelo Carminati Grein
	\brief Text implementation
*/

#include "Defines.h"
#include "Log.h"
#include "Text.h"
#include "Font.h"
#include "Dictionary.h"
#include "Screen.h"
#include "TString.h"

#include <stdarg.h>
#include <stdio.h>


#define TAG "[Text] "

#define TEXT_BUFFER_MAX	2048


namespace Seed {


Text::Text()
	: bChanged(FALSE)
	, pFont(NULL)
	, pStrData(NULL)
	, fPosX(0)
	, fPosY(0)
	, fLocalX(0)
	, fLocalY(0)
	, fWidth(0)
	, fHeight(0)
	, fScaleX(1.0f)
	, fScaleY(1.0f)
	, iColor(PIXEL_COLOR(255, 255, 255, 255))
	, iOperation(Seed::BlendNone)
{
}

Text::~Text()
{
}

INLINE void Text::Reset()
{
	//sRelease(pFont);
	pStrData = NULL;
	fPosX = 0;
	fPosY = 0;
	fLocalX = 0;
	fLocalY = 0;
	bChanged = FALSE;
}

INLINE void Text::SetText(u32 dictText)
{

	pStrData = const_cast<WideString>(pDictionary->GetString(dictText));
	fWidth = this->GetWidth(0, String::Length(pStrData));
	bChanged = TRUE;
}

INLINE void Text::SetText(const WideString str)
{
	pStrData = str;
	fWidth = this->GetWidth(0, String::Length(pStrData));
	bChanged = TRUE;
}

INLINE void Text::SetText(const String &str)
{
	this->SetText(const_cast<WideString>(str.GetData()));
}

INLINE f32 Text::GetWidth(u32 index, u32 size)
{
	f32 w = 0.0f;
	if (pStrData && pFont)
	{
		for (u32 i = 0; i < size; i++)
		{
			u32 letter = pStrData[index + i];

			if (letter == '\0' || letter == '\n')
				break;

			pFont->SetLetter(letter);
			w += pFont->GetWidth() + pFont->GetSpacing();
		}

		//w -= pFont->GetSpacing();
	}

	return w;
}

u32 Text::GetLengthNonBreakMaxWidth(u32 *index, f32 maxWidth, f32 *lineWidth)
{
	// Pode ter somente texto ou somente fonte, por isso nao usar ASSERT
	if (!pStrData || !pFont)
		return 0;

	u32 size = String::Length(pStrData);
	if (*index >= size)
		return 0;

	size++; // \0
	f32 w = 0;
	u32 len = 0;
	u32 separator = 0;

	//Log("B index: %d  char: '%c'", *index, pStrData[*index]);
	if (pStrData[*index] == ' ' || pStrData[*index] == '\t' || pStrData[*index] == '\n' || pStrData[*index] == '\r')
		(*index)++;
	if (pStrData[*index] == '\r')
		(*index)++;

	//Log("A index: %d  char: '%c'", *index, pStrData[*index]);
	f32 nw = 0;
	for (u32 i = *index; i < size; i++)
	{
		u32 letter = pStrData[i];

		if (letter == '\0' || letter == '\n')
			break;

		if (letter == ' ' || letter == '\t')
			separator = i - *index;

		pFont->SetLetter(letter);
		nw = pFont->GetWidth();

		//Log("'%c' %f - %f", letter, nw, w+nw);
		if (w + nw > maxWidth)
			break;
		//Log(".");
		w += nw;
		len++;

		nw = pFont->GetSpacing();
		//Log("spacing %f - %f", nw, w+nw);
		if (w + nw > maxWidth)
			break;
		//Log(".");
		w += nw;
	}

	u32 ch = pStrData[*index + len];
	if (ch != '\0' && ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r' && len != 0 && separator != 0)
	{
		len = separator + 1;
		if (len > 0)
			w = this->GetWidth(*index, len);
	}

	*lineWidth = w;
	return len;
}

void Text::Draw(u32 index, u32 size)
{
	if (!pFont || !pStrData || !fWidth)
		return;

	u32 total = size;
	if (!total)
	{
		total = String::Length(pStrData);
	}
	else
	{
		ASSERT_MSG(index + total <= String::Length(pStrData), "Text index + size out of string bounds.");
	}

	//if (pScreen->HasModeChanged())
	//	fWidth = this->GetWidth(index, total);

	f32 fX = fPosX;
	f32 fY = fPosY;

	pFont->SetBlending(iOperation);
	pFont->SetColor(iColor);
	pFont->SetScale(fScaleX, fScaleY);
	for (u32 i = 0; i < total; i++)
	{
		u32 letter = pStrData[index + i];

		pFont->SetLetter(letter);
		pFont->SetPosition(fX, fY);
		pFont->Draw();

		fX += pFont->GetWidth() + pFont->GetSpacing();
	}
}

/*
INLINE BOOL Text::IsChanged()
{
	return bChanged;
}

INLINE void Text::SetChanged(BOOL b)
{
	bChanged = b;
}
*/

INLINE f32 Text::GetFontTracking() const
{
	f32 ret = 0.0f;
	if (pFont)
		ret = pFont->GetTracking();

	return ret;
}

INLINE f32 Text::GetWidth() const
{
	return fWidth;
}

INLINE f32 Text::GetHeight() const
{
	return fHeight;
}

INLINE f32 Text::GetX() const
{
	return fPosX;
}

INLINE f32 Text::GetY() const
{
	return fPosY;
}

INLINE void Text::SetPosition(f32 x, f32 y)
{
	fPosX = x;
	fPosY = y;
}

INLINE void Text::SetLocalPosition(f32 x, f32 y)
{
	fLocalX = x;
	fLocalY = y;
}

INLINE void Text::SetFont(Font *f)
{
	//sRelease(pFont);
	pFont = f;
	//sAcquire(pFont);

	pFont->SetScale(this->GetScaleX(), this->GetScaleY());
	if (pStrData)
		fWidth = this->GetWidth(0, String::Length(pStrData));

	fHeight = pFont->GetHeight();
}

INLINE void Text::SetBlending(eBlendMode op)
{
	iOperation = op;
}

INLINE void Text::SetColor(u8 r, u8 g, u8 b, u8 a)
{
	iColor = PIXEL_COLOR(r, g, b, a);
}

INLINE void Text::SetColor(PIXEL px)
{
	iColor = px;
}

INLINE void Text::SetScale(f32 scaleX, f32 scaleY)
{
	fScaleX = scaleX;
	fScaleY = scaleY;

	if (pFont)
	{
		pFont->SetScale(fScaleX, fScaleY);
		fHeight = pFont->GetHeight();
	}

	if (pStrData)
		fWidth = this->GetWidth(0, String::Length(pStrData));

	bChanged = TRUE;
}

INLINE const WideString Text::GetText() const
{
	return pStrData;
}

INLINE f32 Text::GetScaleX() const
{
	return fScaleX;
}

INLINE f32 Text::GetScaleY() const
{
	return fScaleY;
}

} // namespace
