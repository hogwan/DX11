#include "pch.h"
#include "CEngine.h"
#include "CDevice.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CAssetMgr.h"
#include "CLevelMgr.h"
#include "CRenderMgr.h"

CEngine::CEngine()
	: m_hMainHwnd(nullptr)
	, m_Resolution{}
{

}

CEngine::~CEngine()
{

}

int CEngine::init(HWND _hWnd, Vec2 _Resolution)
{
	m_hMainHwnd = _hWnd;
	m_Resolution = _Resolution;

	// ������ ũ�� ����
	RECT rt = { 0,0,m_Resolution.x,m_Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hMainHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// DirectX11
	if (FAILED(CDevice::GetInst()->init(m_hMainHwnd, m_Resolution)))
	{
		MessageBox(m_hMainHwnd, L"Device �ʱ�ȭ ����", L"���� �ʱ�ȭ ����", MB_OK);
		return E_FAIL;
	}

	//Manager
	CTimeMgr::GetInst()->init();
	CPathMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CAssetMgr::GetInst()->init();
	CRenderMgr::GetInst()->init();
	CLevelMgr::GetInst()->init();

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
	CRenderMgr::GetInst()->render();
}
