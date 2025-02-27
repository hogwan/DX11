#pragma once
#include "CComponent.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CAssetMgr.h"

#include "CTransform.h"

class CScript :
    public CComponent
{
private:

public:
    virtual void finaltick() final {}
    virtual void tick() = 0;

public:
    CScript();
    ~CScript();
};

