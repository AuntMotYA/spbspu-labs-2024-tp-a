#include "polygon.hpp"
#include <dilimiter.hpp>

std::istream & lebedev::operator>>(std::istream & input, Point & point)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  Point temp_point = { 0, 0 };
  input >> Delimiter{ '(' } >> temp_point.x >> Delimiter{ ';' } >> temp_point.y >> Delimiter{ ')' };
  if (input)
  {
    point = temp_point;
  }
  else
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}
