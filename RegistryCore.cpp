#include "RegistryCore.h"

RegistryCore &RegistryCore::Instatce()
{
  static RegistryCore registry;
  return registry;
}

RegistryCore::RegistryCore()
{

}

RegistryCore::~RegistryCore()
{
}


