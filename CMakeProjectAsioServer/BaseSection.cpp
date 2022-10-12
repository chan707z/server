#include "BaseSection.h"

BaseSection::BaseSection()
{
}

BaseSection::~BaseSection()
{
}

void BaseSection::SetUserBase(shared_ptr<UserBase> pUserBase)
{
    m_pUserBase = pUserBase;
}

shared_ptr<UserBase> BaseSection::GetUserBase()
{
    return m_pUserBase;
}
