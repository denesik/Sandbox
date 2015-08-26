#pragma once

#include <memory>
#include "..\Graphic\Render\Model.h"


struct IBlock
{
  IBlock() {};
  virtual ~IBlock() {};

  /// Создать копию блока.
  virtual IBlock* Clone() const = 0;

  /// Является ли блок статическим?
  virtual bool IsStatic() const = 0;

  /// Получить графическую модель блока.
  virtual const Model &GetModel() const = 0;
};

template<class T>
class Block : public IBlock
{
public:

  /// Получить графическую модель блока.
  const Model &GetModel() const override
  {
    return *mModel.get();
  }

  /// Клонировать блок.
  IBlock *Clone() const override
  {
    return new T(*static_cast<const T*>(this));
  }

protected:
  std::shared_ptr<Model> mModel;
};



