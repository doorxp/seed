/*! \file Timeline.cpp
	\author	Rafael Eduardo Gonchor
	\brief Timeline implementation to be used with ITransformable2D objects
*/

#include "Timeline.h"
#include "EventMovie.h"
#include "Movie.h"


namespace Seed {


Timeline::Timeline()
	: pParent(NULL)
	, pObject(NULL)
	, pListener(NULL)
	, fElapsedTime(0.0f)
	, fElapsedKeyframeTime(0.0f)
	, iCurrentFrame(0)
	, iKeyframeFrom(0)
	, iKeyframeTo(0)
/*
	, ptParentPosition(0.0f, 0.0f)
	, ptParentLocalPosition(0.0f, 0.0f)
	, ptParentScale(1.0f, 1.0f)
	, fParentRotation(0.0f)
*/
	, arKeyframes()
{
	MEMSET(arKeyframes, '\0', sizeof(Keyframe *) * MAX_KEYFRAMES);
}

Timeline::~Timeline()
{
	this->Reset();
}

INLINE void Timeline::Reset()
{
	MEMSET(arKeyframes, '\0', sizeof(Keyframe *) * MAX_KEYFRAMES);

	fElapsedTime 			= 0.0f;
	fElapsedKeyframeTime 	= 0.0f;
	iCurrentFrame 			= 0;
	iKeyframeFrom 			= 0;
	iKeyframeTo 			= 0;

/*
	ptParentPosition		= Point(0.0f, 0.0f);
	ptParentScale			= Point(1.0f, 1.0f);
	fParentRotation			= 0.0f;
*/
}

INLINE void Timeline::Rewind()
{
	iCurrentFrame			= 0;
	iKeyframeFrom 			= 0;
	iKeyframeTo 			= 0;
	fElapsedTime 			= 0.0f;
	fElapsedKeyframeTime 	= 0.0f;
}

INLINE void Timeline::AddKeyframe(u32 frame, Keyframe *keyframe)
{
	ASSERT_MSG(frame < MAX_KEYFRAMES, "Keyframe out of range.");
	arKeyframes[frame] = keyframe;
}

void Timeline::GotoAndPlay(u32 frame)
{
	iCurrentFrame	= frame;
	iKeyframeFrom	= FindPreviousKeyframe();
	iKeyframeTo		= FindNextKeyframe();
}

void Timeline::GotoAndPlay(const char *strKeyframeName)
{
	iKeyframeFrom	= FindKeyframeByName(strKeyframeName);
	iKeyframeTo		= FindNextKeyframe();
	iCurrentFrame	= iKeyframeFrom;
}

void Timeline::Render(f32 dt)
{
	if (!pObject)
		return;

	//attempt to get the next keyframe
	if (iKeyframeTo <= 0)
	{
		iKeyframeTo = FindNextKeyframe();
		//end of animation, restart
		if (iKeyframeTo < 0)
		{
			if (pListener)
			{
				EventMovie ev(this, arKeyframes[iCurrentFrame], static_cast<u32>(iCurrentFrame));
				pListener->OnTimelineFrame(&ev);
				pListener->OnTimelineRestart(&ev);
			}

			iKeyframeFrom = 0;
			iCurrentFrame = 0;
			this->Render(dt);
			return;
		}
	}

	//start interpolating keyframes
	Keyframe *kfFrom	= arKeyframes[iKeyframeFrom];
	Keyframe *kfTo 		= arKeyframes[iKeyframeTo];

	ASSERT_MSG(kfFrom, 	"A keyframe is required at frame 0.");
	ASSERT_MSG(kfTo, 	"At least two keyframes must be set.");

	if (pListener)
	{
		EventMovie ev(this, kfFrom, static_cast<u32>(iCurrentFrame));
		pListener->OnTimelineFrame(&ev);
	}

	f32 fBegin 		= static_cast<f32>(iCurrentFrame - iKeyframeFrom);
	f32 fDuration 	= static_cast<f32>(iKeyframeTo - iKeyframeFrom);

	//Raptor note: Timeline should only change the position and orientation of the object NEVER
	//its visibility or rendering state
	//pObject->SetVisible(!kfFrom->bBlank);
	if (!kfFrom->bBlank)
	{
		//calculate the interpolated values
		f32 fCurrRot,
			fCurrPosX,
			fCurrPosY,
			fCurrLocalPosX,
			fCurrLocalPosY,
			fCurrScaleX,
			fCurrScaleY,
			fCurrR,
			fCurrG,
			fCurrB,
			fCurrA;

		if (kfFrom->bTween && !kfTo->bBlank)
		{
			fCurrRot		= EaseQuadPercent(	fBegin,
												kfFrom->fRotation,
												(kfTo->fRotation - kfFrom->fRotation),
												fDuration,
												kfFrom->fEasing);

			fCurrPosX		= EaseQuadPercent(	fBegin,
												kfFrom->ptPos.x,
												(kfTo->ptPos.x - kfFrom->ptPos.x),
												fDuration,
												kfFrom->fEasing);


			fCurrPosY		= EaseQuadPercent(	fBegin,
												kfFrom->ptPos.y,
												(kfTo->ptPos.y - kfFrom->ptPos.y),
												fDuration,
												kfFrom->fEasing);

			fCurrLocalPosX	= EaseQuadPercent(	fBegin,
												kfFrom->ptLocalPos.x,
												(kfTo->ptLocalPos.x - kfFrom->ptLocalPos.x),
												fDuration,
												kfFrom->fEasing);


			fCurrLocalPosY	= EaseQuadPercent(	fBegin,
												kfFrom->ptLocalPos.y,
												(kfTo->ptLocalPos.y - kfFrom->ptLocalPos.y),
												fDuration,
												kfFrom->fEasing);

			fCurrScaleX		= EaseQuadPercent(	fBegin,
												kfFrom->ptScale.x,
												(kfTo->ptScale.x - kfFrom->ptScale.x),
												fDuration,
												kfFrom->fEasing);

			fCurrScaleY		= EaseQuadPercent(	fBegin,
												kfFrom->ptScale.y,
												(kfTo->ptScale.y - kfFrom->ptScale.y),
												fDuration,
												kfFrom->fEasing);

			fCurrR			= EaseQuadPercent(	fBegin,
												(f32)kfFrom->iColorR,
												((f32)kfTo->iColorR - (f32)kfFrom->iColorR),
												fDuration,
												kfFrom->fEasing);

			fCurrG			= EaseQuadPercent(	fBegin,
												(f32)kfFrom->iColorG,
												((f32)kfTo->iColorG - (f32)kfFrom->iColorG),
												fDuration,
												kfFrom->fEasing);

			fCurrB			= EaseQuadPercent(	fBegin,
												(f32)kfFrom->iColorB,
												((f32)kfTo->iColorB - (f32)kfFrom->iColorB),
												fDuration,
												kfFrom->fEasing);

			fCurrA			= EaseQuadPercent(	fBegin,
												(f32)kfFrom->iColorA,
												((f32)kfTo->iColorA - (f32)kfFrom->iColorA),
												fDuration,
												kfFrom->fEasing);
		}
		else
		{
			fCurrRot 		= kfFrom->fRotation;
			fCurrPosX		= kfFrom->ptPos.x;
			fCurrPosY		= kfFrom->ptPos.y;
			fCurrLocalPosX	= kfFrom->ptLocalPos.x;
			fCurrLocalPosY	= kfFrom->ptLocalPos.y;
			fCurrScaleX		= kfFrom->ptScale.x;
			fCurrScaleY		= kfFrom->ptScale.y;
			fCurrR			= kfFrom->iColorR;
			fCurrG			= kfFrom->iColorG;
			fCurrB			= kfFrom->iColorB;
			fCurrA			= kfFrom->iColorA;
		}
/*
		fCurrPosX 			+= ptParentPosition.x;
		fCurrPosY 			+= ptParentPosition.y;
		fCurrLocalPosX		+= ptParentLocalPosition.x;
		fCurrLocalPosY		+= ptParentLocalPosition.y;
		fCurrScaleX 		*= ptParentScale.x;
		fCurrScaleY			*= ptParentScale.y;
		fCurrRot			+= fParentRotation;
*/
		pObject->SetPosition(fCurrPosX, fCurrPosY);
		pObject->SetLocalPosition(fCurrLocalPosX, fCurrLocalPosY);
		pObject->SetRotation(fCurrRot);
		pObject->SetScale(fCurrScaleX, fCurrScaleY);
		pObject->SetColor((u8)fCurrR, (u8)fCurrG, (u8)fCurrB, (u8)fCurrA);
	}

	if ((fBegin / fDuration) >= 1.0f)
	{
		switch (kfTo->iEvent)
		{
			case Keyframe::KEYFRAME_EVENT_NONE:
			{
				iKeyframeFrom 	= iKeyframeTo;
				iKeyframeTo 	= FindNextKeyframe();
			}
			break;

			case Keyframe::KEYFRAME_EVENT_STOP:
			{
				iKeyframeFrom = iKeyframeTo;
			}
			break;

			case Keyframe::KEYFRAME_EVENT_RESTART:
			{
				iKeyframeFrom = 0;
				iKeyframeTo   = -1;
				iCurrentFrame = 0;
				return;
			}
			break;

			case Keyframe::KEYFRAME_EVENT_JUMPTOFRAME:
			{
				iCurrentFrame = kfTo->iFrameToJump;
				iKeyframeFrom = FindPreviousKeyframe();
				iKeyframeTo   = FindNextKeyframe();
				return;
			}
			break;
		}
	}
	else
	{
		switch (kfFrom->iEvent)
		{
			case Keyframe::KEYFRAME_EVENT_STOP:
			{
				iKeyframeTo		= iKeyframeFrom;
				iCurrentFrame	= iKeyframeFrom;
				return;
			}
			break;
		}
	}

	//FIXME when changing to timebased instead of framebased the iCurrentFrame increment must
	//be based on the elapsedtime
	fElapsedKeyframeTime++;
	fElapsedTime++;
	iCurrentFrame++;
}

INLINE void Timeline::SetObject(ITransformable2D *object)
{
	if (pObject)
		pObject->SetParent(NULL);

	pObject = object;
	
	if (pObject)
		pObject->SetParent(reinterpret_cast<ITransformable2D *>(pParent));
}

INLINE ITransformable2D *Timeline::GetObject() const
{
	return this->pObject;
}

INLINE f32 Timeline::GetWidth() const
{
	f32 r = 0.0f;
	if (pObject)
		r = pObject->GetWidth();

	return r;
}

INLINE f32 Timeline::GetHeight() const
{
	f32 r = 0.0f;
	if (pObject)
		r = pObject->GetHeight();

	return r;
}

INLINE u32 Timeline::GetCurrentFrame() const
{
	return static_cast<u32>(this->iCurrentFrame);
}

INLINE void Timeline::SetLocalPosition(f32 posX, f32 posY)
{
	ptParentLocalPosition.x 	= posX;
	ptParentLocalPosition.y 	= posY;
}

INLINE void Timeline::SetPosition(f32 posX, f32 posY)
{
	ptParentPosition.x 	= posX;
	ptParentPosition.y 	= posY;
}

INLINE void Timeline::SetScale(f32 scaleX, f32 scaleY)
{
	ptParentScale.x		= scaleX;
	ptParentScale.y		= scaleY;
}

INLINE void Timeline::SetRotation(f32 rotation)
{
	fParentRotation = rotation;
}

INLINE s32 Timeline::FindKeyframeByName(const char *pstrName)
{
	for (s32 i = 0; i < MAX_KEYFRAMES; i++)
	{
		if (!arKeyframes[i])
			continue;
		else if (!STRCMP(arKeyframes[i]->pstrName, pstrName))
			return i;
	}

	return 0;
}

INLINE s32 Timeline::FindNextKeyframe()
{
	for (s32 i = iKeyframeFrom+1; i < MAX_KEYFRAMES; i++)
	{
		if (!arKeyframes[i])
			continue;
		else
			return i;
	}

	return -1;
}

INLINE s32 Timeline::FindPreviousKeyframe()
{
	for (s32 i = iCurrentFrame; i >= 0; i--)
	{
		if (!arKeyframes[i])
			continue;
		else
			return i;
	}

	return -1;
}

INLINE void Timeline::SetListener(IEventMovieListener *listener)
{
	this->pListener = listener;
}

INLINE const Keyframe *Timeline::GetCurrentKeyframe() const
{
	return arKeyframes[iKeyframeFrom];
}

INLINE f32 Timeline::EaseQuadPercent(f32 time, f32 begin, f32 change, f32 duration, f32 easing)
{
	if (duration <= 0.0f)
		return begin;

	if (time <= 0.0)
		return begin;

	if ((time /= duration) >= 1.0f)
		return begin + change;

	// linear tween if percent is 0
	if (!easing)
		return change * time + begin;

	if (easing > 1.0f)
		easing = 1.0f;
	else if (easing < -1.0f)
		easing = -1.0f;

	// ease in if percent is negative
	if (easing < 0.0f)
		return change * time * (time * (-easing) + (1.0f + easing)) + begin;

	// ease out if percent is positive
	return change * time * ((2.0f - time) * easing + (1.0f - easing)) + begin;
}

INLINE void Timeline::SetParent(Movie *parent)
{
	pParent = parent;
	if (pObject)
		pObject->SetParent(reinterpret_cast<ITransformable2D *>(parent));
}

INLINE Movie *Timeline::GetParent() const
{
	return pParent;
}

} // namespace
