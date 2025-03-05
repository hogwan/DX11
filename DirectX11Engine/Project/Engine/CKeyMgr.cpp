#include "pch.h"
#include "CKeyMgr.h"
#include "CEngine.h"

UINT g_KeyValue[(UINT)KEY::KEY_END] =
{
	'Q',
	'W',
	'E',
	'R',
	'A',
	'S',
	'D',
	'F',
	'Z',
	'X',
	'C',
	'V',
	'T',
	'Y',
	'G',
	'H',

	'0',
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',

	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	VK_LBUTTON,
	VK_RBUTTON,

	VK_RETURN,
	VK_ESCAPE,
	VK_SPACE,
	VK_LSHIFT,
	VK_MENU,
	VK_CONTROL,
};

CKeyMgr::CKeyMgr()
{

}

CKeyMgr::~CKeyMgr()
{

}

void CKeyMgr::init()
{
	for (UINT i = 0; i < (UINT)KEY::KEY_END; i++)
	{
		tKeyInfo info = {};
		info.State = KEY_STATE::NONE;
		info.PrevPressed = false;

		m_vecKey.push_back(info);
	}
}

void CKeyMgr::tick()
{
	for (size_t i = 0; i < m_vecKey.size(); ++i)
	{
		// KEY �� ���ȴ�
		if (GetAsyncKeyState(g_KeyValue[i]) & 0x8001)
		{
			// �������� �ȴ����־���.
			if (!m_vecKey[i].PrevPressed)
			{
				m_vecKey[i].State = KEY_STATE::TAP;
			}
			// �ش� KEY �� �����־���.
			else
			{
				m_vecKey[i].State = KEY_STATE::PRESSED;
			}

			m_vecKey[i].PrevPressed = true;
		}

		// KEY �� �ȴ����ִ�.
		else
		{
			// �ش� KEY �� �����־���.
			if (m_vecKey[i].PrevPressed)
			{
				m_vecKey[i].State = KEY_STATE::RELEASED;
			}
			// �������� �ȴ����־���.
			else
			{
				m_vecKey[i].State = KEY_STATE::NONE;
			}
			m_vecKey[i].PrevPressed = false;
		}
	}

	// ���콺 ��ǥ ����
	m_PrevMousePos = m_CurMousePos;
	
	POINT ptMouse = {};
	GetCursorPos(&ptMouse);
	ScreenToClient(CEngine::GetInst()->GetMainWnd(), &ptMouse);
	m_CurMousePos = Vec2((float)ptMouse.x, (float)ptMouse.y);
	m_DragDir = m_CurMousePos - m_PrevMousePos;
	m_DragDir.y *= -1.f;
	m_DragDir.Normalize();
}
