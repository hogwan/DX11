#pragma once
#include "enum.h"

// ����
// 3D ������ ��ǥ�� ��Ÿ���� ����
struct Vtx
{
	Vec3 vPos;
	Vec4 vColor;
	Vec2 vUV;
};

// ����� ���� ��û ����
struct tDebugShapeInfo
{
	DEBUG_SHAPE		Shape;
	Vec3			Position;
	Vec3			Scale;
	Vec3			Rotation;
	Matrix			matWorld;
	Vec4			Color;
	float			Duration;
	float			Age;
};


//������� ���� ����ü
struct tTransform
{
	Matrix matWorld;
	Matrix matView;
	Matrix matProj;
};
extern tTransform g_Trans;

struct tMtrlConst
{
	int		iArr[4];
	float	fArr[4];
	Vec2	v2Arr[4];
	Vec4	v4Arr[4];
	Matrix	matArr[4];
};