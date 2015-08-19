#pragma once

#include <memory>
#include "..\Graphic\Render\Cube.h"


struct IBlock
{
  IBlock() {};
  virtual ~IBlock() {};

  /// ������� ����� �����.
  virtual IBlock* Clone() const = 0;

  /// �������� �� ���� �����������?
  virtual bool IsStatic() const = 0;
};

template<class T>
class Block : public IBlock
{
public:

  /// �������� ����������� ������ �����.
  const Cube &GetModel()
  {
    return mModel;
  }

  /// ����������� ����.
  IBlock *Clone() const override
  {
    return new T(*static_cast<const T*>(this));
  }

protected:
  std::shared_ptr<Cube> mModel;
};



