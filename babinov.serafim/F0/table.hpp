#ifndef TABLE_HPP
#define TABLE_HPP
#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <utility>

namespace babinov
{
  enum DataType
  {
    PK,
    INTEGER,
    REAL,
    TEXT
  };
  bool isLess(const std::string& el1, const std::string& el2, babinov::DataType dataType);

  const std::unordered_map< DataType, std::string > DEFAULT_VALUES = {
    {PK, "0"},
    {INTEGER, "0"},
    {REAL, "0.0"},
    {TEXT, ""}
  };

  const std::unordered_map< DataType, std::string > DATA_TYPES_AS_STR = {
    {PK, "PK"},
    {INTEGER, "INTEGER"},
    {REAL, "REAL"},
    {TEXT, "TEXT"}
  };

  const std::unordered_map< std::string, DataType > DATA_TYPES_FROM_STR = {
    {"PK", PK},
    {"INTEGER", INTEGER},
    {"REAL", REAL},
    {"TEXT", TEXT}
  };

  class Table
  {
   public:
    using column_t = std::pair< std::string, DataType >;
    using row_t = std::vector< std::string >;

    Table();
    explicit Table(const std::vector< column_t >& columns);
    Table(const Table& other);
    Table(Table&& other) noexcept;
    ~Table() = default;
    Table& operator=(const Table& other);
    Table& operator=(Table&& other) noexcept;

    const std::vector< column_t >& getColumns() const;
    const std::list< row_t >& getRows() const;
    bool isCorrectRow(const row_t& row) const;
    DataType getColumnType(const std::string& columnName) const;

    void readRow(std::istream& in);
    void printRow(std::ostream& out, std::list< row_t >::const_iterator iter) const;
    void printRow(std::ostream& out, const Table::row_t& row) const;

    void insert(const row_t& row);
    std::vector< std::list< row_t >::const_iterator > select(const std::string& columnName, const std::string& value) const;
    bool update(size_t rowId, const std::string& columnName, const std::string& value);
    void alter(const std::string& columnName, const column_t& newColumn);
    bool del(const std::string& columnName, const std::string& value);
    void swap(Table& other) noexcept;
    void clear() noexcept;

    template< class Comparator >
    void sort(const std::string& columnName, Comparator comp);
    void sort(const std::string& columnName);
    Table link(const Table& other, const std::string& columnName) const;

   private:
    std::vector< column_t > columns_;
    std::unordered_map< std::string, size_t > columnIndexes_;
    std::list< row_t > rows_;
    std::unordered_map< size_t, std::list< row_t >::iterator > rowIters_;
    size_t lastId_;
  };

  template< class Comparator >
  void Table::sort(const std::string& columnName, Comparator comp)
  {
    size_t index = columnIndexes_.at(columnName);
    auto pred = [&](const row_t& r1, const row_t& r2) -> bool
    {
      return comp(r1[index], r2[index]);
    };
    rows_.sort(pred);
  }

  bool isCorrectName(const std::string& name);
  bool isLess(const std::string& el1, const std::string& el2, DataType dataType);
  std::istream& operator>>(std::istream& in, Table::column_t& column);
  std::istream& operator>>(std::istream& in, Table& table);
  std::ostream& operator<<(std::ostream& out, const Table::column_t& column);
  std::ostream& operator<<(std::ostream& out, const Table& table);
}

#endif
