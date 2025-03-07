#pragma once
#include "CEntity.h"

class CComponent;
class CRenderComponent;
class CTransform;
class CMeshRender;
class CCamera;

class CScript;


#define GET_COMPONENT(Type, TYPE) C##Type* Type() { return ( C##Type*)m_arrCom[(UINT)COMPONENT_TYPE::TYPE]; }

class CGameObject :
    public CEntity
{
private:
    CComponent* m_arrCom[(UINT)COMPONENT_TYPE::END];
    CRenderComponent* m_RenderCom;

    vector<CScript*>    m_vecScripts;


public:
    void begin();       // ������ ���۵� ��, ������ �շ��� ��
    void tick();        // �� �����Ӹ��� ȣ��, DT ���� �� ���� ����
    void finaltick();   // tick ���� �߻��� �ϵ��� ������ �۾� or ���ҽ� ���ε� �� ���� ������ ����
    void render();      // ȭ�鿡 �׷����� �Լ�

public:
    void AddComponent(CComponent* _Component);
    CComponent* GetComponent(COMPONENT_TYPE _Type) { return m_arrCom[(UINT)_Type]; }

    GET_COMPONENT(Transform, TRANSFORM)
    GET_COMPONENT(MeshRender, MESHRENDER)
    GET_COMPONENT(Camera, CAMERA)

public:
    CGameObject();
    ~CGameObject();
};