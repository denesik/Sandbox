#pragma once

#include <memory>
#include "..\Graphic\Render\Cube.h"


struct IBlock
{
  IBlock() {};
  virtual ~IBlock() {};

  /// Создать копию блока.
  virtual IBlock* Clone() const = 0;

  /// Является ли блок статическим?
  virtual bool IsStatic() const = 0;
};

template<class T>
class Block : public IBlock
{
public:

  /// Молучить графическую модель блока.
  const Cube &GetModel()
  {
    return mModel;
  }

  /// Клонировать блок.
  IBlock *Clone() const override
  {
    return new T(*static_cast<const T*>(this));
  }

protected:
  std::shared_ptr<Cube> mModel;
};



