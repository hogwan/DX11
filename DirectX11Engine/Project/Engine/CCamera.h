#pragma once
#include "CComponent.h"
class CCamera :
    public CComponent
{
private:
    int m_CamPriority; // 랜더 매니저에 등록될 때 카메라의 우선순위( 0 : 메인카메라, -1 : 미등록카메라, 이외 : 서브카메라)
    float m_Far;

    Matrix m_matView;
    Matrix m_matProj;

public:
    void SetCameraPriority(int _Priority);

public:
    virtual void finaltick() override;
    void render();

public:
    CCamera();
    ~CCamera();
};

