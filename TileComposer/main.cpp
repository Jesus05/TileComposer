#include <iostream>

using namespace std;

#include "tilecomposerlib.h"

#include <QImage>
#include <QDebug>

int main(int argc, char *argv[])
{
  QImage image1;
  image1.load("../../images/sand.png");
  QImage image2;
  image2.load("../../images/pavement_seamless.png");

  image1 = image1.convertToFormat(QImage::Format_ARGB32);
  image2 = image2.convertToFormat(QImage::Format_ARGB32);

  qDebug() << image1 << image2;

  uchar *one = image1.bits();
  uchar *two = image2.bits();

  QImage image3(GetTileSetWidth(image1.width()), GetTileSetHeight(image1.width()), QImage::Format_ARGB32);

  unsigned char* tilesetMem = static_cast<unsigned char*>(CreateTileSet(one, two, image1.width()));

  uchar *three = image3.bits();
  for (int i = 0; i < image3.byteCount(); i++)
  {
    three[i] = tilesetMem[i];
  }

  FreeTileSet(tilesetMem);

  image1.save("./image1.png");
  image2.save("./image2.png");
  image3.save("./image3.png");

  return 0;
}
