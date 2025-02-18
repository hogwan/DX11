#pragma once
#include <wincrypt.h>
class CEngine
{
private:
	HWND	m_hMainHwnd;
	POINT	m_Resolution;

public:
	int init(HWND _hWnd, POINT _Resolution);

public:
	static CEngine* GetInst()
	{
		static CEngine Core;
		return &Core;
	}
private:
	CEngine();
	CEngine(const CEngine& _origin) = delete;
	~CEngine();
};

