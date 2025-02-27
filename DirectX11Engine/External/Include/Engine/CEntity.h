#pragma once
class CEntity
{
private:
	static UINT g_NextID;

private:
	wstring		m_Name;
	UINT		m_ID;

public:
	const wstring& GetName() { return m_Name; }
	void SetName(const wstring& _Name) { m_Name = _Name; }
	const UINT GetID() { return m_ID; }

	// �ڱ� �ڽ��� ������ ��ü�� ��ȯ
	//virtual CEntity* Clone() = 0;

public:
	CEntity();
	CEntity(const CEntity& _Origin);
	virtual ~CEntity();
};

