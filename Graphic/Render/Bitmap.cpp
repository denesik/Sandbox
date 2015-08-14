#include "Bitmap.h"

#include "lodepng/lodepng.h"


Bitmap::Bitmap()
{
}

Bitmap::Bitmap(const std::string &fileName)
{
  unsigned error = lodepng::decode(mData, mSize.x, mSize.y, fileName);

  if(error)
  {
    throw new BitmapException(BitmapException::FILE_NOT_FOUND);
  }
}

Bitmap::Bitmap(const glm::uvec2 &size, const Color &color)
  : mSize(size)
{
  mData.resize(mSize.x * mSize.y * sizeof(color));
  for(unsigned int i = 0; i < mData.size(); i += sizeof(color))
  {
    memcpy(&mData[i], &color, sizeof(color));
  }
}

Bitmap::~Bitmap()
{
}

const glm::uvec2 &Bitmap::GetSize() const
{
  return mSize;
}

const std::vector<unsigned char> &Bitmap::GetRaw() const
{
  return mData;
}

void Bitmap::Save(const std::string &fileName) const
{
  unsigned error = lodepng::encode(fileName, mData, mSize.x, mSize.y);

  if(error)
  {
    throw new BitmapException(BitmapException::FILE_NOT_SAVE);
  }
}

void Bitmap::Insert(const glm::uvec2 &pos, const Bitmap &bitmap)
{
  // Вставляемая битмапа должна полностью влазить в текущую.
  //assert(); 

  const auto &bSize = bitmap.GetSize();

  glm::uvec2 iPos;
  for (; iPos.y < bSize.y; ++iPos.y)
  {
    for (; iPos.x < bSize.x; ++iPos.x)
    {
      Set(pos + iPos, bitmap.Get(iPos));
    }
    iPos.x = 0;
  }

}

void Bitmap::Set(const glm::uvec2 &pos, Color color)
{
  memcpy(&mData[pos.y * mSize.x * 4 + pos.x * 4], &color.raw.abgr, sizeof(color));
}

Color Bitmap::Get(const glm::uvec2 &pos) const
{
  Color color;
  memcpy(&color.raw.abgr, &mData[pos.y * mSize.x * 4 + pos.x * 4], sizeof(color));
  return color;
}
