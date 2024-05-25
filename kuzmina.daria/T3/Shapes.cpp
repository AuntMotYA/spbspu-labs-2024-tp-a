#include "Shapes.hpp"
#include <iostream>
#include <functional>
#include <algorithm>
#include <numeric>
#include "DelimiterI.hpp"

bool kuzmina::Point::operator==(const Point& other) const
{
  return (x == other.x) && (y == other.y);
}

double kuzmina::Polygon::getArea() const
{
  using namespace std::placeholders;
  auto countArea = std::bind(CountArea{ points[1] }, _1, _2, points[0]);

  return std::accumulate(points.begin(), points.end(), 0.0, countArea);
}

double kuzmina::CountArea::operator()(double area, const Point& point2, const Point& point3)
{
  area += 0.5 * std::abs((point3.x - point1.x) * (point2.y - point1.y) - (point2.x - point1.x) * (point3.y - point1.y));
  point1 = point2;

  return area;
}

bool kuzmina::Polygon::hasRightAngle() const
{
  auto countAngle = CountAngle{ points[points.size() - 1], points[points.size() - 2] };

  return std::find_if(points.cbegin(), points.cend(), countAngle) != points.cend();
}

bool kuzmina::CountAngle::operator()(const Point& point3)
{
  Point side1 = { point2.x - point1.x, point2.y - point1.y };
  Point side2 = { point2.x - point3.x, point2.y - point3.y };

  point2 = point1;
  point1 = point3;

  return side1.x * side2.x + side1.y * side2.y == 0;
}

std::istream& kuzmina::operator>>(std::istream& in, Point& point)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  int tempX = 0, tempY = 0;

  in >> DelimiterI{ '(' } >> tempX >> DelimiterI{ ';' } >> tempY >> DelimiterI{ ')' };

  if (in)
  {
    point.x = tempX;
    point.y = tempY;
  }

  return in;
}

std::istream& kuzmina::operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  size_t numberOfPoints = 0;
  in >> numberOfPoints;

  if (numberOfPoints < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  std::vector< Point > tempPoints;

  for (size_t i = 0; i < numberOfPoints; ++i)
  {
    Point p;

    if (in.peek() == '\n')
    {
      in.setstate(std::ios::failbit);
    }

    in >> p;
    if (in)
    {
      tempPoints.push_back(p);
    }
  }

  if (!in || in.peek() != '\n' || tempPoints.size() != numberOfPoints)
  {
    in.setstate(std::ios::failbit);
  }
  else
  {
    polygon.points = tempPoints;
  }

  return in;
}
