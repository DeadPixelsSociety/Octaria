//--------------------------------------------------------------------------------------------------
// Package     : Octaria
// File        : CMultiResolutionApplication.h
// Author      : PRADAL & co
// Description : -
// Platform    : All
//--------------------------------------------------------------------------------------------------

#ifndef __CMULTIRESOLUTIONAPPLICATION_H
#define __CMULTIRESOLUTIONAPPLICATION_H

//
/// @todo comment
class CMultiResolutionApplication
{
public:

	//
	// Construction / Destruction
	explicit				CMultiResolutionApplication		(void);
	virtual					~CMultiResolutionApplication	(void);

	void					OnPreInitialize					(void);
	void					OnPostInitialize				(void);
	void					OnPreUpdate						(float deltaTimeInMs);
	void					OnPostUpdate					(float deltaTimeInMs);
	void					OnPreRelease					(void);
	void					OnPostRelease					(void);

	void					OnActivate						(void);
	void					OnDeactivate					(void);

    void					OnTouchDown						(int iTouch, float positionX, float positionY);
    void					OnTouchUp						(int iTouch, float positionX, float positionY);
    void					OnTouchMove						(int iTouch, float positionX, float positionY);

	ShCamera *				GetCamera						(void);
	void					SetCamera						(ShCamera * pCamera);

protected:

private:

	ShCamera *				m_pCamera;						///< @todo comment

};

#endif // __CMULTIRESOLUTIONAPPLICATION_H

