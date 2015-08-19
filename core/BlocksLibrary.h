#pragma once
#ifndef BlocksLibrary_h__
#define BlocksLibrary_h__

#include <unordered_map>
#include <string>
#include "Block.h"

class BlocksLibrary
{
public:
  BlocksLibrary();
  ~BlocksLibrary();

  /// ���������������� ����.
  void Registry(const std::string &id, IBlock *block);

  /// ������� ����.
  /// ���� ���� �����������, ������������ ��������� �� ��������� �����, ���������� � ����������.
  /// ���� ���� ������������, ��������� ����� �����.
  /// @param blockId ������������� �����.
  IBlock *Create(const std::string &id);

private:

  std::unordered_map<std::string, IBlock *> mBlocks;
};


#endif // BlocksLibrary_h__


