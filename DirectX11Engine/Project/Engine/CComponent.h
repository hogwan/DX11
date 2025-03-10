#pragma once
#include "CEntity.h"

#include "CGameObject.h"

#define GET_OTHER_COMPONENT(Type)  C##Type* Type() { return m_Owner->Type(); }

class CComponent :
    public CEntity
{
private:
    CGameObject* m_Owner;    // 해당 컴포넌트를 소유하고 있는 오브젝트 주소
    const COMPONENT_TYPE    m_Type;     // 본인이 무슨 컴포넌트인지에 대한 enum

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