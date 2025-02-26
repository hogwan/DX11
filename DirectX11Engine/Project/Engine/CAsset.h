#pragma once
#include "CEntity.h"
class CAsset :
    public CEntity
{
private:
    wstring             m_Key;              // �ε��� Ű��
    wstring             m_RelativePath;     // �����
    const ASSET_TYPE    m_Type;             // Asset�� Ÿ��

public:
    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }

    ASSET_TYPE GetAssetType() { return m_Type; }

public:
    CAsset(ASSET_TYPE _Type);
    ~CAsset();
};

