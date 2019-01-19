#pragma once

#include <string>
#include <vector>
#include <cstdint>
#include <json.hpp>
#include <fifo_map.hpp>
#include <parser/sql.hpp>
#include <storage/StorageEngine.hpp>
#include "Record.hpp"

namespace sql {

using TabDef = cmd::TableDefinition;
using Cols = std::vector<cmd::ColumnDefinition>;
using Rows = std::vector<Record>;

using json = nlohmann::json;

std::string to_string(cmd::LiteralType t);

class Table
{
public:
  Table() {}

  explicit Table(
      cmd::TableDefinition name
    ) : name_(name),
        meta_(std::make_shared<se::MetaData>(name.ToString())) { }

  explicit Table(
      cmd::TableDefinition name,
      std::list<cmd::ColumnDefinition> columns
    ) : name_(name),
        columns_(columns),
        meta_(std::make_shared<se::MetaData>(name.ToString())) { }

  explicit Table(
      cmd::TableDefinition name,
      std::list<cmd::ColumnDefinition> columns,
      std::list<Record> records
    ) : name_(name),
        columns_(columns),
        records_(records),
        meta_(std::make_shared<se::MetaData>(name.ToString())) { }

  explicit Table(
      std::list<cmd::ColumnDefinition> columns,
      std::list<Record> records
    ) : columns_(columns),
        records_(records) { }

  void AddColumn(cmd::ColumnDefinition column);
  void InsertRecord(Record record);
  void DeleteRecord(int index);

  const std::list<cmd::ColumnDefinition>& GetColumns() const { return columns_; }
  const std::list<Record>& GetRecords() const { return records_; }

// TODO: Make its implementation working normal:
  std::string ToString() const;

  cmd::TableDefinition name_;

public:
  std::list<cmd::ColumnDefinition> columns_;
  std::list<Record> records_;

// TODO: Create it in constructor
  std::shared_ptr<se::MetaData> meta_;
};


void to_json(json& j, const Table& t);
void from_json(const json& j, Table& t);

} //namespace sql