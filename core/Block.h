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
  /// Установить графическую модель блоку.
  void SetModel(const std::shared_ptr<Cube> &model)
  {
    mModel = model;
  }

  /// Молучить графическую модель блока.
  const Cube &GetModel()
  {
    return mModel;
  }

  /// Клонировать блок.
  BlockBase *Clone() const override
  {
    return new T(*static_cast<T*>(this));
  }

protected:
  std::shared_ptr<Cube> mModel;
};



