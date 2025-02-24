#include "pch.h"
#include "CTimeMgr.h"
#include "CEngine.h"

CTimeMgr::CTimeMgr()
	: m_llFrequency{}
	, m_llCurCount{}
	, m_llPrevCount{}
	, m_fDT(0.f)
	, m_fAccTime(0.f)
	, m_fTime(0.f)
	, m_iFrmCount(0)
{

}

CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// 초당 카운트 수
	QueryPerformanceFrequency(&m_llFrequency);
	QueryPerformanceCounter(&m_llCurCount);
	m_llPrevCount = m_llCurCount;
}

void CTimeMgr::tick()
{
	QueryPerformanceCounter(&m_llCurCount);

	m_fDT = static_cast<float>(m_llCurCount.QuadPart - m_llPrevCount.QuadPart)
		/ static_cast<float>(m_llFrequency.QuadPart);

	m_fTime += m_fDT;
	m_fAccTime += m_fDT;
	++m_iFrmCount;
	if (m_fAccTime >= 1.f)
	{
		wchar_t szText[255] = {};
		swprintf_s(szText, L"FPS : %d, DeltaTime : %f", m_iFrmCount, m_fDT);

		HWND hMainWnd = CEngine::GetInst()->GetMainWnd();
		SetWindowText(hMainWnd, szText);

		m_fAccTime -= 1.f;
		m_iFrmCount = 0;
	}

	m_llPrevCount = m_llCurCount;
}
