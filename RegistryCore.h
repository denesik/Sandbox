#pragma once

#ifndef RegistryCore_h__
#define RegistryCore_h__


#define REGISTRY_CORE RegistryCore::Instatce()

class RegistryCore
{
public:
  static RegistryCore &Instatce();

private:
  RegistryCore();
  ~RegistryCore();
  RegistryCore(const RegistryCore &);
  RegistryCore& operator=(const RegistryCore &);

private:

};

#endif // RegistryCore_h__
