#pragma once
#include "CEntity.h"

class CComponent;
class CScript;
class CRenderComponent;

class CGameObject :
    public CEntity
{
private:
    CComponent*         m_arrCom[(UINT)COMPONENT_TYPE::END];
    CRenderComponent*   m_RenderCom;

    vector<CScript*>    m_vecScripts;

public:
    void begin();           // ������ ���۵� ��, ������ �շ��� ��
    void tick();            // �� �����Ӹ��� ȣ��, DT ���� �� ���� ����
    void finaltick();       // tick ���� �߻��� �ϵ��� ������ �۾� or ���ҽ� ���ε� �� ���� ������ ����
    void render();          // ȭ�鿡 �׷����� �Լ�

public:
    void AddComponent(CComponent* _Component);
    CComponent* GetComponent(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }

    class CTransform* Transform() { return (CTransform*)m_arrCom[(UINT)COMPONENT_TYPE::TRANSFORM]; }
    class CMeshRender* MeshRender() { return (CMeshRender*)m_arrCom[(UINT)COMPONENT_TYPE::MESHRENDER]; }
    class CCamera* Camera() { return (CCamera*)m_arrCom[(UINT)COMPONENT_TYPE::CAMERA]; }

public:
    CGameObject();
    ~CGameObject();
};