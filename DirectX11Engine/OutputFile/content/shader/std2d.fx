#ifndef _STD2D
#define _STD2D

#include "value.fx"

struct VS_IN
{
    float3 vPos : POSITION;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};

struct VS_OUT
{
    float4 vPosition : SV_Position;
    float4 vColor : COLOR;
    float2 vUV : TEXCOORD;
};



VS_OUT VS_Std2D(VS_IN _in)
{
    VS_OUT output = (VS_OUT) 0.f;
    
    float4 vWorldPos = mul(float4(_in.vPos, 1.f), g_matWorld);
    float4 vViewPos = mul(vWorldPos, g_matView);
    float4 vProjPos = mul(vViewPos, g_matProj);
    
    //행렬을 곱할 때 3차원 좌표를 4차원으로 확장
    output.vPosition = vProjPos;
    output.vColor = _in.vColor;
    output.vUV = _in.vUV;
    return output;
}

float4 PS_Std2D(VS_OUT _in) : SV_Target
{
    float4 vColor = (float4) 0.f;
    if(g_int_0 == 0)
    {
        vColor = g_tex_0.Sample(g_Sam_0, _in.vUV);
    }
    else if(g_int_0 == 1)
    {
        vColor = float4(1.f, 1.f, 0.f, 1.f);
    }
    
    else if(g_int_0 == 2)
    {
        vColor = float4(0.f, 1.f, 1.f, 1.f);
        
    }
    return vColor;
}

#endif

