#pragma once
class CTimeMgr
	:public CSingleton<CTimeMgr>
{
	SINGLE(CTimeMgr)
private:
	LARGE_INTEGER	m_llFrequency;	//�ʴ� ī��Ʈ ��
	LARGE_INTEGER	m_llCurCount;	//���� ī��Ʈ ��
	LARGE_INTEGER	m_llPrevCount;	//���� ������ ī��Ʈ ��

	float			m_fDT;			// DeltaTime : 1������ �����ϴµ� �ɸ� �ð�
	float			m_fTime;			//���μ��� ���� ������ ���� �ð�
	float			m_fAccTime;		//1�ʸ� üũ�ϱ� ���� �ð� ��������

	UINT			m_iFrmCount;
public:
	void init();
	void tick();

public:
	float GetDeltaTime()
	{
		return m_fDT;
	}

};

