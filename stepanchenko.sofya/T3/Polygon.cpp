#include "Polygon.hpp"

#include <vector>
#include <algorithm>
#include <istream>
#include <Delimeter.hpp>

std::istream& stepanchenko::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = DelimiterI;
  Point t_point{ 0, 0 };
  in >> del{ '(' } >> t_point.x >> del{ ';' } >> t_point.y >> del{ ')' };
  if (in)
  {
  point = t_point;
  }
  return in;
}

std::istream& stepanchenko::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  size_t amount = 0;
  in >> amount;
  if (amount < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > t_points;
  t_points.reserve(amount);
  std::copy_n(std::istream_iterator< Point >{ in }, amount, std::back_inserter(t_points));
  t_points.shrink_to_fit();
  if (in && t_points.size() == amount)
  {
    polygon.points = t_points;
  }
  return in;
}
