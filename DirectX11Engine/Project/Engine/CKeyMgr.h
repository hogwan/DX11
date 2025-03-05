#pragma once
#include "singleton.h"

enum class KEY
{
	Q,W,E,R,
	A,S,D,F,
	Z,X,C,V,
	T,Y,G,H,

	_0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,

	LEFT,
	RIGHT,
	UP,
	DOWN,

	LBTN,
	RBTN,

	ENTER,
	ESC,
	SPACE,
	LSHIFT,
	ALT,
	CTRL,

	KEY_END,
};

enum class KEY_STATE
{
	TAP,
	PRESSED,
	RELEASED,
	NONE,
};

struct tKeyInfo
{
	KEY_STATE	State;
	bool		PrevPressed;
};


class CKeyMgr
	:public CSingleton<CKeyMgr>
{
	SINGLE(CKeyMgr)

private:
	vector<tKeyInfo>	m_vecKey;
	Vec2				m_CurMousePos;
	Vec2				m_PrevMousePos;
	Vec2				m_DragDir;

public:
	void init();
	void tick();

public:
	KEY_STATE GetKeyState(KEY _Key) { return m_vecKey[(UINT)_Key].State; }

	Vec2 GetMousePos() { return m_CurMousePos; };
	Vec2 GetPrevMousePos() { return m_PrevMousePos; };
	Vec2 GetMouseDrag() { return m_DragDir; }
};

