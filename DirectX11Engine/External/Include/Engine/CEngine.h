#pragma once
class CEngine
{
private:
	HWND	m_hMainWnd;
	POINT	m_hResolution;

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

