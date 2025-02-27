#pragma once
#include "singleton.h"

class CLevel;

class CLevelMgr :
    public CSingleton<CLevelMgr>
{
   SINGLE(CLevelMgr)

private:
    CLevel* m_CurLevel;

public:
    void begin();
    void tick();
    void render();


};
