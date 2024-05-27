#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

namespace lebedev
{
  struct Point
  {
    int x, y;
  };
  std::istream & operator>>(std::istream & input, Point & point);
  double getX(const Point & point);
  double getY(const Point & point);
}

#endif
