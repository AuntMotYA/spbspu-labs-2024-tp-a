#include "dataStruct.hpp"
#include <iostream>
#include <complex>
#include <cmath>
#include "delimeter.hpp"

double getComplexNumModule(double rl, double im)
{
  return std::sqrt(std::pow(rl, 2) + std::pow(im, 2));
}

bool isaychev::DataStruct::operator<(const DataStruct & other) const
{
  if (key1 == other.key1)
  {
    double module1 = getComplexNumModule(key2.real(), key2.imag());
    double module2 = getComplexNumModule(other.key2.real(), other.key2.imag());
    if (module1 == module2)
    {
      return (key3.size() < other.key3.size());
    }
    return (module1 < module2);
  }
  return (key1 < other.key1);
}

std::istream & isaychev::operator>>(std::istream & in, DataStruct & obj)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }

  in >> std::noskipws;

  using dc = DelimChI;
  using ds = DelimStrI;

  DataStruct input;
  char c = 0;

  in >> ds{"(:"};
  for (int i = 0; i < 3; ++i)
  {
    in >> ds{"key"} >> c;

    if (c == '1')
    {
      in >> dc{' '} >> LongLongI{input.key1} >> dc{':'};
    }
    else if (c == '2')
    {
      in >> ds{" #c("} >> ComplexI{input.key2} >> ds{"):"};
    }
    else if (c == '3')
    {
      in >> ds{" \""} >> StringI{input.key3} >> ds{"\":"};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> dc{')'};

  if (in)
  {
    obj = input;
  }

  in >> std::skipws;
  return in;
}

std::ostream & isaychev::operator<<(std::ostream & out, const DataStruct & obj)
{
  out << "(:key1 " << obj.key1 << "ll";
  out << ":key2 #c(" << obj.key2.real() << " " << obj.key2.imag() << ")";
  out << ":key3 \"" << obj.key3 << "\":)";
  return out;
}
