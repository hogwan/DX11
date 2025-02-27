#pragma once
#include "CEntity.h"

class CLayer;
class CGameObject;

class CLevel :
    public CEntity
{
private:
    CLayer* m_arrLayer[MAX_LAYER];

public:
    void AddObject(UINT _LayerIdx, CGameObject* _Object);

    void begin();
    void tick();
    void finaltick();
    void render();

public:
    CLevel();
    ~CLevel();
};

