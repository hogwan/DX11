#pragma once
#include "CComponent.h"
class CCamera :
    public CComponent
{
private:
    PROJ_TYPE m_ProjType;

    int m_CamPriority; // ���� �Ŵ����� ��ϵ� �� ī�޶��� �켱����( 0 : ����ī�޶�, -1 : �̵��ī�޶�, �̿� : ����ī�޶�)

    float m_FOV; // �þ߰�(Field Of View)
    float m_Far; // �þ� �ִ�Ÿ�

    float m_AspectRatio; // ��Ⱦ ��
    float m_Width;       // ���� ����
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

