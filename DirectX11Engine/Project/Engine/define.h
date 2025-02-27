#pragma once

#define SINGLE(type)	private:\
							type();\
							type(const type& _origin) = delete;\
						public:\
							~type();\
							friend class CSingleton<type>;

#define DEVICE CDevice::GetInst()->GetDevice()
#define CONTEXT CDevice::GetInst()->GetContext()

#define KEY_CHECK(Key, State)				CKeyMgr::GetInst()->GetKeyState(Key) == State
#define KEY_PRESSED(Key)					KEY_CHECK(Key, KEY_STATE::PRESSED)
#define KEY_TAP(Key)						KEY_CHECK(Key, KEY_STATE::TAP)
#define KEY_RELEASED(Key)					KEY_CHECK(Key, KEY_STATE::RELEASED)

#define DT CTimeMgr::GetInst()->GetDeltaTime()

#define MAX_LAYER 32

typedef Vector2 Vec2;
typedef Vector3 Vec3;
typedef Vector4 Vec4;
