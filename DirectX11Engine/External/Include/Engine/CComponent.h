#pragma once
#include "CEntity.h"

#include "CGameObject.h"

class CMeshRender;
class CCamera;

class CComponent :
    public CEntity
{
private:
    CGameObject*            m_Owner;   // �ش� ������Ʈ�� �����ϰ� �ִ� ������Ʈ �ּ�
    const COMPONENT_TYPE    m_Type;    // ������ ���� ������Ʈ������ ���� enum

public:
    virtual void begin() {};
    virtual void tick() {};
    virtual void finaltick() = 0;

public:
    COMPONENT_TYPE GetComponentType() { return m_Type; }
    CGameObject* GetOwner() { return m_Owner; }

    CTransform* Transform() { return m_Owner->Transform(); }
    CMeshRender* MeshRender() { return m_Owner->MeshRender(); }
    CCamera* Camera() { return m_Owner->Camera(); }

public:
    CComponent(COMPONENT_TYPE _Type);
    ~CComponent();
    friend CGameObject;
};

