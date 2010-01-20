/*! \file ITransformable2D.h
	\author	Danny Angelo Carminati Grein
	\brief Defines a primitive Transformable2D class interface
*/

#ifndef __ITRANSFORMABLE2D_H__
#define __ITRANSFORMABLE2D_H__

#include "Defines.h"
#include "Point.h"
#include "interface/IRenderable.h"

/*
FIXME: 2009-06-25 | WISH | CORE | Utilizar Point para storage dos dados | Danny Angelo Carminati Grein
*/

namespace Seed {


class ITransformable2D : public IRenderable
{
	public:
		ITransformable2D();
		virtual ~ITransformable2D();

		virtual void SetWidth(f32 w);
		virtual void SetHeight(f32 h);

		virtual void SetX(f32 x);
		virtual void SetY(f32 y);
		virtual void AddX(f32 value);
		virtual void AddY(f32 value);

		virtual void SetPosition(f32 x, f32 y);
		virtual void AddPosition(f32 x, f32 y);
		virtual void SetPosition(const Point<f32> &pos);
		virtual void AddPosition(const Point<f32> &pos);

		virtual void SetLocalX(f32 x);
		virtual void SetLocalY(f32 y);
		virtual void AddLocalX(f32 value);
		virtual void AddLocalY(f32 value);

		virtual void SetLocalPosition(f32 x, f32 y);
		virtual void AddLocalPosition(f32 x, f32 y);
		virtual void SetLocalPosition(const Point<f32> &pos);
		virtual void AddLocalPosition(const Point<f32> &pos);

		virtual void SetRotation(f32 rot);
		virtual void AddRotation(f32 rot);

		virtual void SetScaleX(f32 scaleX);
		virtual void SetScaleY(f32 scaleY);
		virtual void SetScale(f32 scale);
		virtual void SetScale(f32 scaleX, f32 scaleY);
		virtual void SetScale(const Point<f32> &scale);

		virtual void AddScaleX(f32 scaleX);
		virtual void AddScaleY(f32 scaleY);
		virtual void AddScale(f32 scale);
		virtual void AddScale(f32 scaleX, f32 scaleY);
		virtual void AddScale(const Point<f32> &scale);

		// Normalized Width and Height
		virtual f32 GetWidth() const;
		virtual f32 GetHeight() const;

		virtual f32 GetX() const;
		virtual f32 GetY() const;
		virtual Point<f32> GetPosition() const;

		virtual f32 GetLocalX() const;
		virtual f32 GetLocalY() const;
		virtual Point<f32> GetLocal() const;

		virtual f32 GetRotation() const;

		virtual f32 GetScaleX() const;
		virtual f32 GetScaleY() const;

		virtual u32 GetPriority() const;

		virtual BOOL ContainsPoint(f32 x, f32 y);
		virtual BOOL ContainsPoint(const Point<f32> &pos);

		/// Set a parent for this transformable
		/**
		When a Transformable2D has a parent it will inherit all it's properies.
		If you use a instanced Transformable2D and delete it, you're responsable 
		to set the parent of this object to NULL or we can crash badly.
		\param Set a Transformable2D as parent for this object
		 */
		virtual void SetParent(ITransformable2D *pParent);
		virtual ITransformable2D *GetParent() const;

		virtual void Reset();
		
		virtual BOOL IsChanged() const;

		// IObject
		virtual const char *GetObjectName() const = 0;
		virtual int GetObjectType() const = 0;

	protected:
		BOOL bTransformationChanged;
		ITransformable2D *pParent;
		Point<f32> ptPos;
		//f32 fPosX;
		//f32 fPosY;
		Point<f32> ptLocalPos;
		//f32 fLocalPosX;
		//f32 fLocalPosY;
		f32 fWidth;
		f32 fHeight;
		f32 fScaleX;
		f32 fScaleY;
		f32 fRotation;

	private:
		SEED_DISABLE_COPY(ITransformable2D);
};


} // namespace


#endif // __ITRANSFORMABLE2D_H__