#pragma once

#include <memory>
#include "..\Graphic\Render\Cube.h"


class Block
{
public:

  void SetModel(const std::shared_ptr<Cube> &model);

  const Cube &GetModel();

private:
  std::shared_ptr<Cube> mModel;
};



