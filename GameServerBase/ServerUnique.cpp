#include "pch.h"
#include "ServerUnique.h"

std::atomic<__int64> ServerUnique::UniqueID = 0;

__int64 ServerUnique::GetNextUniqueId()
{
    ++UniqueID;
    return UniqueID;
}

ServerUnique::ServerUnique()
{
}

ServerUnique::~ServerUnique()
{
}

ServerUnique::ServerUnique(ServerUnique&& _other) noexcept
{
}
