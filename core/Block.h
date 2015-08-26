#pragma once

#include <memory>
#include "..\Graphic\Render\Model.h"


struct IBlock
{
  IBlock() {};
  virtual ~IBlock() {};

  /// ������� ����� �����.
  virtual IBlock* Clone() const = 0;

  /// �������� �� ���� �����������?
  virtual bool IsStatic() const = 0;

  /// �������� ����������� ������ �����.
  virtual const Model &GetModel() const = 0;
};

template<class T>
class Block : public IBlock
{
public:

  /// �������� ����������� ������ �����.
  const Model &GetModel() const override
  {
    return *mModel.get();
  }

  /// ����������� ����.
  IBlock *Clone() const override
  {
    return new T(*static_cast<const T*>(this));
  }

protected:
  std::shared_ptr<Model> mModel;
};



