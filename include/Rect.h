/*! \file Rect.h
	\author Rafael Eduardo Gonchor
	\brief Rectangle utils
*/


#ifndef __RECT_H__
#define __RECT_H__


#include "Log.h"


namespace Seed {


template <class TYPE> class Rect
{
	public:
		TYPE x;
		TYPE y;
		TYPE width;
		TYPE height;

	public:
		Rect(TYPE x = 0, TYPE y = 0, TYPE width = 0, TYPE height = 0)
			: x(x)
			, y(y)
			, width(width)
			, height(height)
		{
		}


		Rect(const Rect<TYPE> &rect)
			: x(0)
			, y(0)
			, width(0)
			, height(0)
		{
			LoadRect(rect);
		}


		Rect<TYPE> &operator=(const Rect<TYPE> &rect)
		{
			x      = rect.x;
			y      = rect.y;
			width  = rect.width;
			height = rect.height;

			return *this;
		}


		BOOL operator==(const Rect<TYPE> &rect) const
		{
			return((x == rect.x) && (y == rect.y) && (width == rect.width) && (height == rect.height));
		}


		BOOL operator!=(const Rect<TYPE> &rect) const
		{
			return(!(x == rect.x) || !(y == rect.y) || !(width == rect.width) || !(height == rect.height));
		}


		Rect<TYPE> & LoadRect(const Rect<TYPE> &rect)
		{
			*this = rect;
			return *this;
		}


		BOOL IsCollidedWith(const Rect<TYPE> &rect)
		{
			TYPE left1, left2;
			TYPE right1, right2;
			TYPE top1, top2;
			TYPE bottom1, bottom2;

			left1   = this->x;
			left2   = rect.x;
			right1  = this->x + (TYPE)this->width;
			right2  = rect.x + (TYPE)rect.width;
			top1    = this->y;
			top2    = rect.y;
			bottom1 = this->y + (TYPE)this->height;
			bottom2 = rect.y + (TYPE)rect.height;

			if (bottom1 < top2) return(FALSE);
			if (top1 > bottom2) return(FALSE);

			if (right1 < left2) return(FALSE);
			if (left1 > right2) return(FALSE);

			return TRUE;
		}


		void GetOverlappedRect(const Rect<TYPE> &rect, Rect<TYPE> &rectDst)
		{
			TYPE left1, left2;
			TYPE right1, right2;
			TYPE top1, top2;
			TYPE bottom1, bottom2;
			TYPE over_bottom;
			TYPE over_top;
			TYPE over_left;
			TYPE over_right;

			left1   = this->x;
			left2   = rect.x;
			right1  = this->x + (TYPE)this->width;
			right2  = rect.x + (TYPE)rect.width;
			top1    = this->y;
			top2    = rect.y;
			bottom1 = this->y + (TYPE)this->height;
			bottom2 = rect.y + (TYPE)rect.height;

			// Ok, compute the rectangle of overlap:
			if (bottom1 > bottom2) over_bottom = bottom2;
			else over_bottom = bottom1;

			if (top1 < top2) over_top = top2;
			else over_top = top1;

			if (right1 > right2) over_right = right2;
			else over_right = right1;

			if (left1 < left2) over_left = left2;
			else over_left = left1;

			rectDst.x      = over_left;
			rectDst.y      = over_top;
			rectDst.width  = (TYPE)(over_right - over_left);
			rectDst.height = (TYPE)(over_bottom - over_top);
		}


		BOOL Contains(TYPE pX, TYPE pY)
		{
			if (pX > (TYPE)(x + width))
			{
				return FALSE;
			}
			else if	(pX < x)
			{
				return FALSE;
			}
			if (pY > (TYPE)(y + height))
			{
				return FALSE;
			}
			else if	(pY < y)
			{
				return FALSE;
			}

			return TRUE;
		}

		BOOL ContainsArea(const Rect<TYPE> &rect)
		{
			if (this->Contains(rect.x, rect.y) && 
				this->Contains(rect.x+rect.width, rect.y+rect.height))
				return TRUE;

			return FALSE;
		}

		void ScaleSize(f32 fScale)
		{
			this->width		*= fScale;
			this->height	*= fScale;
		}

		void ScaleBounds(f32 fScale)
		{
			TYPE newWidth	= width * fScale;
			TYPE newHeight	= height * fScale;

			x -= (newWidth - width)   / 2;
			y -= (newHeight - height) / 2;

			width	= newWidth;
			height	= newHeight;
		}

		void Print()
		{
			Log("Rect info: x -> %d, y -> %d, width -> %d, height -> %d", x, y, width, height);
		}
};


} // namespace


#endif // __RECT_H__

