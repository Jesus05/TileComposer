#include <iostream>

using namespace std;

#include "tilecomposerlib.h"

#include <QImage>
#include <QPainter>
#include <QDebug>

struct Rects
{
  QPoint start;
  int imageSize;
  QRect inner() const { return QRect(start + QPoint(2 + imageSize, 2 + imageSize), QSize(imageSize, imageSize)); }

  QRect leftUp() const { return QRect(start + QPoint(1, 1), QSize(imageSize, imageSize)); }
  QRect leftDown() const { return QRect(start + QPoint(1, 3 + imageSize * 2), QSize(imageSize, imageSize)); }
  QRect left() const { return QRect(start + QPoint(1, 2 + imageSize), QSize(imageSize, imageSize)); }

  QRect up() const { return QRect(start + QPoint(2 + imageSize, 1), QSize(imageSize, imageSize)); }
  QRect down() const { return QRect(start + QPoint(2 + imageSize, 3 + imageSize * 2), QSize(imageSize, imageSize)); }

  QRect right() const { return QRect(start + QPoint(3 + imageSize * 2, 2 + imageSize), QSize(imageSize, imageSize)); }
  QRect rightUp() const { return QRect(start + QPoint(3 + imageSize * 2, 1), QSize(imageSize, imageSize)); }
  QRect rightDown() const { return QRect(start + QPoint(3 + imageSize * 2, 3 + imageSize * 2), QSize(imageSize, imageSize)); }

  QRect leftInner() const { return QRect(start + QPoint(6 + imageSize * 5, 2 + imageSize), QSize(imageSize, imageSize)); }
  QRect leftUpInner() const { return QRect(start + QPoint(6 + imageSize * 5, 1), QSize(imageSize, imageSize)); }
  QRect leftDownInner() const { return QRect(start + QPoint(6 + imageSize * 5, 3 + imageSize * 2), QSize(imageSize, imageSize)); }

  QRect upInner() const { return QRect(start + QPoint(5 + imageSize * 4, 3 + imageSize * 2), QSize(imageSize, imageSize)); }
  QRect downInner() const { return QRect(start + QPoint(5 + imageSize * 4, 1), QSize(imageSize, imageSize)); }

  QRect rightInner() const { return QRect(start + QPoint(4 + imageSize * 3, 2 + imageSize), QSize(imageSize, imageSize)); }
  QRect rightUpInner() const { return QRect(start + QPoint(4 + imageSize * 3, 3 + imageSize * 2), QSize(imageSize, imageSize)); }
  QRect rightDownInner() const { return QRect(start + QPoint(4 + imageSize * 3, 1), QSize(imageSize, imageSize)); }

};

struct Points
{
  QPoint start;
  int imageSize;
  QPoint point(const int &x, const int &y) { return start + QPoint(imageSize * x, imageSize * y); }
};

std::vector<QPainter::PixmapFragment> fragments(const Rects &rects)
{
  std::vector<QPainter::PixmapFragment> f;
  f.push_back(QPainter::PixmapFragment::create(QPointF(0, 0), rects.inner()));
  return f;
}

int main(int argc, char *argv[])
{
  QImage image1;
  image1.load("./image1.png");
  QImage image2;
  image2.load("./image2.png");

  image1 = image1.convertToFormat(QImage::Format_ARGB32);
  image2 = image2.convertToFormat(QImage::Format_ARGB32);

  qDebug() << image1 << image2;

  uchar *one = image1.bits();

  QImage image3(GetTileSetWidth(image1.width()), GetTileSetHeight(image1.width()), QImage::Format_ARGB32);

  unsigned char* tilesetMem = static_cast<unsigned char*>(CreateTileSetFromJSONFile(one, image1.width(), "./generator.txt"));

  uchar *three = image3.bits();
  for (int i = 0; i < image3.byteCount(); i++)
  {
    three[i] = tilesetMem[i];
  }

  QImage image4(image1.width() * 8, image1.width() * 8, QImage::Format_ARGB32);
  QPainter painter(&image4);
  Rects oneRects;
  oneRects.start = QPoint(0, 0);
  oneRects.imageSize = image1.width();
  Rects twoRects = oneRects;
  twoRects.start = QPoint(0, image1.height() * 3 );
  Points point;
  point.start = QPoint(0, 0);
  point.imageSize = image1.width();

  for (int x = 0; x < 8; x++)
  for (int y = 0; y < 8; y++)
  {
    painter.drawImage(point.point(x, y), image2);
  }
  for (int x = 0; x < 2; x++)
  for (int y = 0; y < 2; y++)
  {
    painter.drawImage(point.point(x, y), image3.copy(oneRects.inner()));
  }
  for (int x = 6; x < 8; x++)
  for (int y = 0; y < 2; y++)
  {
    painter.drawImage(point.point(x, y), image3.copy(oneRects.inner()));
  }
  for (int x = 6; x < 8; x++)
  for (int y = 6; y < 8; y++)
  {
    painter.drawImage(point.point(x, y), image3.copy(oneRects.inner()));
  }
  for (int x = 0; x < 2; x++)
  for (int y = 6; y < 8; y++)
  {
    painter.drawImage(point.point(x, y), image3.copy(oneRects.inner()));
  }

  painter.drawImage(point.point(0, 2), image3.copy(oneRects.leftUp()));
  painter.drawImage(point.point(0, 5), image3.copy(oneRects.leftDown()));
  painter.drawImage(point.point(0, 3), image3.copy(oneRects.left()));
  painter.drawImage(point.point(0, 4), image3.copy(oneRects.leftInner()));
  painter.drawImage(point.point(1, 2), image3.copy(oneRects.up()));
  painter.drawImage(point.point(1, 5), image3.copy(oneRects.down()));
  painter.drawImage(point.point(2, 0), image3.copy(oneRects.leftUp()));
  painter.drawImage(point.point(2, 7), image3.copy(oneRects.leftDown()));
  painter.drawImage(point.point(2, 1), image3.copy(oneRects.left()));
  painter.drawImage(point.point(2, 2), image3.copy(oneRects.leftDownInner()));
  painter.drawImage(point.point(2, 6), image3.copy(oneRects.left()));
  painter.drawImage(point.point(2, 5), image3.copy(oneRects.leftUpInner()));
  painter.drawImage(point.point(3, 0), image3.copy(oneRects.up()));
  painter.drawImage(point.point(3, 7), image3.copy(oneRects.down()));
  painter.drawImage(point.point(4, 0), image3.copy(oneRects.upInner()));
  painter.drawImage(point.point(4, 7), image3.copy(oneRects.downInner()));
  painter.drawImage(point.point(5, 0), image3.copy(oneRects.rightUp()));
  painter.drawImage(point.point(5, 7), image3.copy(oneRects.rightDown()));
  painter.drawImage(point.point(5, 1), image3.copy(oneRects.right()));
  painter.drawImage(point.point(5, 6), image3.copy(oneRects.right()));
  painter.drawImage(point.point(5, 2), image3.copy(oneRects.rightUpInner()));
  painter.drawImage(point.point(5, 5), image3.copy(oneRects.rightDownInner()));
  painter.drawImage(point.point(6, 2), image3.copy(oneRects.up()));
  painter.drawImage(point.point(6, 5), image3.copy(oneRects.down()));
  painter.drawImage(point.point(7, 2), image3.copy(oneRects.rightUp()));
  painter.drawImage(point.point(7, 5), image3.copy(oneRects.rightDown()));
  painter.drawImage(point.point(7, 3), image3.copy(oneRects.right()));
  painter.drawImage(point.point(7, 4), image3.copy(oneRects.rightInner()));

  FreeTileSet(tilesetMem);

  image3.save("./image3.png");
  image4.save("./image4.png");

  return 0;
}
