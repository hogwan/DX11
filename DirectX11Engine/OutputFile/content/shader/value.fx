#ifndef _VALUE
#define _VALUE

cbuffer TRANSFORM : register(b0)
{
    row_major matrix g_matWorld;
    row_major matrix g_matView;
    row_major matrix g_matProj;
}

cbuffer MATERIAL_CONST : register(b1)
{
    int         g_int_0;
    int         g_int_1;
    int         g_int_2;
    int         g_int_3;
    
    float       g_float_0;
    float       g_float_1;
    float       g_float_2;
    float       g_float_3;
    
    float2      g_v2_0;
    float2      g_v2_1;
    float2      g_v2_2;
    float2      g_v2_3;
    
    float4      g_v4_0;
    float4      g_v4_1;
    float4      g_v4_2;
    float4      g_v4_3;
    
    Matrix      g_mat_0;
    Matrix      g_mat_1;
    Matrix      g_mat_2;
    Matrix      g_mat_3;
}

SamplerState    g_Sam_0 : register(s0);
SamplerState    g_Sam_1 : register(s0);

Texture2D       g_tex_0 : register(t0);
Texture2D       g_tex_1 : register(t1);
Texture2D       g_tex_2 : register(t2);
Texture2D       g_tex_3 : register(t3);
Texture2D       g_tex_4 : register(t4);
Texture2D       g_tex_5 : register(t5);

TextureCube     g_texcube_0 : register(t6);
TextureCube     g_texcube_1 : register(t7);
TextureCube     g_texcube_2 : register(t8);
TextureCube     g_texcube_3 : register(t9);

Texture2DArray  g_texarr_0 : register(t10);
Texture2DArray  g_texarr_1 : register(t11);
Texture2DArray  g_texarr_2 : register(t12);
Texture2DArray  g_texarr_3 : register(t13);

#endif