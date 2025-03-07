#pragma once
#include "CEntity.h"

#include "CGameObject.h"

#define GET_OTHER_COMPONENT(Type)  C##Type* Type() { return m_Owner->Type(); }

class CComponent :
    public CEntity
{
private:
    CGameObject* m_Owner;    // �ش� ������Ʈ�� �����ϰ� �ִ� ������Ʈ �ּ�
    const COMPONENT_TYPE    m_Type;     // ������ ���� ������Ʈ������ ���� enum

public:
    virtual void begin() {}
    virtual void tick() {}
    virtual void finaltick() = 0;

public:
    COMPONENT_TYPE GetComponentType() { return m_Type; }
    CGameObject* GetOwner() { return m_Owner; }

    GET_OTHER_COMPONENT(Transform)
    GET_OTHER_COMPONENT(MeshRender)
    GET_OTHER_COMPONENT(Camera)

public:
    CComponent(COMPONENT_TYPE _Type);
    ~CComponent();

    friend class CGameObject;
};