#include "pch.h"
#include "CEngine.h"
#include "CDevice.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CAssetMgr.h"
#include "CLevelMgr.h"

#include "temp.h"

CEngine::CEngine()
	: m_hMainHwnd(nullptr)
	, m_Resolution{}
{

}

CEngine::~CEngine()
{

}

int CEngine::init(HWND _hWnd, POINT _Resolution)
{
	m_hMainHwnd = _hWnd;
	m_Resolution = _Resolution;

	// 윈도우 크기 설정
	RECT rt = { 0,0,m_Resolution.x,m_Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hMainHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// DirectX11
	if (FAILED(CDevice::GetInst()->init(m_hMainHwnd, m_Resolution)))
	{
		MessageBox(m_hMainHwnd, L"Device 초기화 실패", L"엔진 초기화 실패", MB_OK);
		return E_FAIL;
	}

	//Manager
	CTimeMgr::GetInst()->init();
	CPathMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CAssetMgr::GetInst()->init();
	CLevelMgr::GetInst()->begin();

	return S_OK;
}

void CEngine::progress()
{
	// ============
	// Manager Tick
	// ============
	CTimeMgr::GetInst()->tick();
	CKeyMgr::GetInst()->tick();

	// Object Tick
	CLevelMgr::GetInst()->tick();

	// ===========
	// Rendering
	// ===========
	// Target Clear
	float ClearColor[4] = { 0.3f,0.3f,0.3f,1.f };
	CDevice::GetInst()->ClearTarget(ClearColor);

	// Object Render
	CLevelMgr::GetInst()->render();

	// Present
	CDevice::GetInst()->Present();
}
