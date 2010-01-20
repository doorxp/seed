/*! \file TextArea.cpp
	\author Danny Angelo Carminati Grein
	\brief GUI TextArea Widget
*/


#include "Defines.h"
#include "Input.h"
#include "Log.h"
#include "Rect.h"
#include "gui/TextArea.h"
#include "Renderer2D.h"
#include "Screen.h"
#include "Number.h"


#define TAG		"[GUI::TextArea] "


#if DEBUG_ENABLE_RECT_TEXTAREA == 1
#define DEBUG_TEXTAREA_RECT DEBUG_RECT(this->GetX(), this->GetY(), this->GetWidth(), this->GetHeight(), DEBUG_RECT_COLOR_TEXTAREA);
#else
#define DEBUG_TEXTAREA_RECT
#endif


namespace Seed {


TextArea::TextArea()
	: IWidget()
	, iLines(0)
	, fDiffX(0.0f)
	, fScaleX(0.0f)
	, fScaleY(0.0f)
	, iColor(0)
	, eHAlign(HorizontalAlignLeft)
	, eVAlign(VerticalAlignTop)
	, pFont(NULL)
	, pLines(NULL)
	, cText()
	, bAutoAdjust(FALSE)
{
	this->Reset();
}

TextArea::~TextArea()
{
	this->Reset();

	if(Private::bInitialized)
		pGuiManager->Remove(this);
}

void TextArea::Reset()
{
	if (this->pLines)
		pMemoryManager->Free(this->pLines, pDefaultPool);

	this->iId				= 0;
	this->bDisabled			= TRUE;
	this->iColor			= 0;
	this->iLines			= 0;
	this->eHAlign 			= HorizontalAlignLeft;
	this->eVAlign 			= VerticalAlignTop;
	this->eBlendOperation	= IRenderable::NONE;

	this->pLines			= NULL;

	IWidget::Reset();
}

void TextArea::Update(f32 dt)
{
	IWidget::Update(dt);

	if (this->bChanged)
	{
		this->Rebuild();
	}

	this->bChanged = FALSE;
	this->bTransformationChanged = FALSE;
}

void TextArea::Render(f32 delta)
{
	UNUSED(delta);

	DEBUG_TEXTAREA_RECT;

	this->cText.SetBlending(this->eBlendOperation);
	this->cText.SetColor(this->iColor);
	this->cText.SetScale(this->GetScaleX(), this->GetScaleY());

	for (u32 i = 0; i < this->iLines; i++)
	{
		if (!pLines[i].iIndex && !pLines[i].iSize)
			break;

		this->cText.SetPosition(pLines[i].fPosX + this->GetX(), pLines[i].fPosY + this->GetY());
		this->cText.Draw(pLines[i].iIndex, pLines[i].iSize);
	}
}


u32 TextArea::GetLineCount() const
{
	return iLines;
}

u32 TextArea::CaculateLineCount()
{
	u32 lines = 0;
	if (bAutoAdjust)
	{
		u32 index = 0;
		f32 lineWidth = 0;
		u32 size = 0;
		while (1)
		{
			size = cText.GetLengthNonBreakMaxWidth(&index, this->GetWidth(), &lineWidth);

			if (!size)
				break;

			lines++;
			index += size;
		}
		this->SetHeight(lines * (cText.GetHeight() + cText.GetFontTracking()));
	}
	else
	{
		lines = static_cast<u32>(this->GetHeight() / (cText.GetHeight() + cText.GetFontTracking()));
	}

	return lines;
}

void TextArea::Rebuild()
{
	u32 lines = this->CaculateLineCount();
	if (!lines)
		return;

	u32 sizeBuff = lines * sizeof(struct sLineInfo);
	if (lines != iLines)
	{
		iLines = lines;
		if (pLines)
			pMemoryManager->Free(pLines, pDefaultPool);

		pLines = static_cast<struct sLineInfo *>(pMemoryManager->Alloc(sizeBuff, pDefaultPool));
	}
	MEMSET(pLines, '\0', sizeBuff);

	u32 index = 0;
	u32 size = 0;
	f32 lineWidth = 0.0f;
	u32 usedLines = 0;
	for (u32 i = 0; i < this->iLines; i++)
	{
		size = cText.GetLengthNonBreakMaxWidth(&index, this->GetWidth(), &lineWidth);

		if (!size)
			break;

		this->pLines[i].iSize = size;
		this->pLines[i].iIndex = index;
		//this->pLines[i].fPosY = y + ((cText.GetHeight() + cText.GetFontTracking()) * i * this->GetScaleY());

		f32 diffX = this->GetWidth() - lineWidth;
		switch (eHAlign)
		{
			case HorizontalAlignLeft:
				this->pLines[i].fPosX = 0.0f;
			break;

			case HorizontalAlignRight:
				this->pLines[i].fPosX = diffX;
			break;

			case HorizontalAlignCenter:
				this->pLines[i].fPosX = (diffX / 2.0f);
			break;

			case HorizontalAlignNone:
			default:
			break;
		}

		index += size;
		usedLines++;
	}

	f32 y = 0.0f;
	f32 textHeight = ((cText.GetHeight() + cText.GetFontTracking()) * usedLines) * this->GetScaleY();
	switch (eVAlign)
	{
		case VerticalAlignCenter:
			y += ((this->GetHeight() - textHeight) / 2.0f);
		break;

		case VerticalAlignBottom:
			y += this->GetHeight() - textHeight;
		break;

		case VerticalAlignTop:
		default:
		break;
	}

	for (u32 i = 0; i < usedLines; i++)
		this->pLines[i].fPosY = y + ((cText.GetHeight() + cText.GetFontTracking()) * i * this->GetScaleY());
}

INLINE void TextArea::SetText(u32 dictId)
{
	this->cText.SetText(dictId);

	if (!this->GetHeight())
		this->SetHeight(cText.GetHeight());

	if (!this->GetWidth())
		this->SetWidth(cText.GetWidth());

	this->Rebuild();
	this->bChanged = FALSE;


//	this->bChanged = TRUE;
}

INLINE void TextArea::SetText(WideString str)
{
	this->cText.SetText(str);

	if (!this->GetHeight())
		this->SetHeight(cText.GetHeight());

	if (!this->GetWidth())
		this->SetWidth(cText.GetWidth());

	this->Rebuild();
	this->bChanged = FALSE;
//	this->bChanged = TRUE;
}

INLINE void TextArea::SetText(const String &str)
{
	this->cText.SetText(str);

	if (!this->GetHeight())
		this->SetHeight(cText.GetHeight());

	if (!this->GetWidth())
		this->SetWidth(cText.GetWidth());

	this->Rebuild();
	this->bChanged = FALSE;
//	this->bChanged = TRUE;
}


/*
INLINE void TextArea::Print(WideString str, ...)
{
	va_list ap;
	va_start(ap, str);
	this->cText.Print(str, &ap);
	va_end(ap);

	if (!this->GetHeight())
		this->SetHeight(cText.GetHeight());

	if (!this->GetWidth())
		this->SetWidth(cText.GetWidth());

	this->bChanged = TRUE;
}
*/

INLINE void TextArea::SetAutoAdjust(BOOL b)
{
	this->bAutoAdjust = b;
}

INLINE void TextArea::SetFont(const Font *font)
{
	this->pFont = font;
	this->cText.SetFont(const_cast<Font*>(pFont));
	this->bChanged = TRUE;
}

INLINE void TextArea::SetPriority(u32 p)
{
	IRenderable::iPriority = p;
	IWidget::iPriority = p;
}

INLINE void TextArea::SetAlignment(eHorizontalAlignment align)
{
	this->eHAlign = align;
	this->bChanged = TRUE;
}

INLINE void TextArea::SetAlignment(eVerticalAlignment align)
{
	this->eVAlign = align;
	this->bChanged = TRUE;
}

INLINE void TextArea::SetColor(u8 r, u8 g, u8 b, u8 a)
{
	this->iColor = PIXEL_COLOR(r, g, b, a);
}

INLINE void TextArea::SetColor(PIXEL px)
{
	this->iColor = px;
}

INLINE PIXEL TextArea::GetColor() const
{
	return this->iColor;
}

INLINE const char *TextArea::GetObjectName() const
{
	return "TextArea";
}

INLINE int TextArea::GetObjectType() const
{
	return Seed::ObjectGuiTextArea;
}


} // namespace
