#pragma once
#include "CComponent.h"
class CCamera :
    public CComponent
{
private:
    PROJ_TYPE m_ProjType;

    int m_CamPriority; // 랜더 매니저에 등록될 때 카메라의 우선순위( 0 : 메인카메라, -1 : 미등록카메라, 이외 : 서브카메라)

    float m_FOV; // 시야각(Field Of View)
    float m_Far; // 시야 최대거리

    float m_AspectRatio; // 종횡 비
    float m_Width;       // 가로 길이
    float m_Scale;

    Matrix m_matView;
    Matrix m_matProj;

public:
    void SetCameraPriority(int _Priority);

    void SetProjType(PROJ_TYPE _Type) { m_ProjType = _Type; }
    void SetFar(float _Far) { m_Far = _Far; }
    void SetFOV(float _FOV) { m_FOV = _FOV; }
    void SetWidth(float _Width) { m_Width = _Width; }
    void SetAspectRatio(float _AspectRatio) { m_AspectRatio = _AspectRatio; }
    void SetScale(float _Scale) { m_Scale = _Scale; }

    int GetCameraPriority() { return m_CamPriority; }

    PROJ_TYPE GetProjType() { return m_ProjType; }
    float GetFar() { return m_Far; }
    float GetFOV() { return m_FOV; }
    float GetWidth() { return m_Width; }
    float GetAspectRatio() { return m_AspectRatio; }
    float GetScale() { return m_Scale; }
public:
    virtual void finaltick() override;
    void render();

public:
    CCamera();
    ~CCamera();
};

