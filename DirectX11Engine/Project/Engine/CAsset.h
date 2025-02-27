#pragma once
#include "CEntity.h"
class CAsset :
    public CEntity
{
private:
    wstring             m_Key;              // �ε��� Ű��
    wstring             m_RelativePath;     // �����
    const ASSET_TYPE    m_Type;             // Asset�� Ÿ��
    int m_RefCount;

public:
    const wstring& GetKey() { return m_Key; }
    const wstring& GetRelativePath() { return m_RelativePath; }
    ASSET_TYPE GetAssetType() { return m_Type; }

private:
    void AddRef() { m_RefCount++; }
    void Release() { m_RefCount--; }

public:
    CAsset(ASSET_TYPE _Type);
    CAsset(const CAsset& _Origin) = delete;
    ~CAsset();

    template<typename T>
    friend class Ptr;
};

