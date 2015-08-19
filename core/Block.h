#pragma once

#include <memory>
#include "..\Graphic\Render\Cube.h"


struct BlockBase
{
  BlockBase() {};
  virtual ~BlockBase() {};
  virtual BlockBase* Clone() const = 0;
};

template<typename T = Block>
class Block : BlockBase
{
public:
  /// ���������� ����������� ������ �����.
  void SetModel(const std::shared_ptr<Cube> &model)
  {
    mModel = model;
  }

  /// �������� ����������� ������ �����.
  const Cube &GetModel()
  {
    return mModel;
  }

  /// ����������� ����.
  BlockBase *Clone() const override
  {
    return new T(*static_cast<T*>(this));
  }

protected:
  std::shared_ptr<Cube> mModel;
};



