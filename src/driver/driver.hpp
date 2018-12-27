#pragma once

#include <string>
#include <list>
#include <exception>
#include <type_traits>
#include <parser/parser.hpp>
#include <parser/sql.hpp>
#include <storage/StorageEngine.hpp>
#include <json.hpp>
#include "datatypes/Table.hpp"
#include "DriverBase.hpp"

namespace sql {

class Driver : public DriverBase {
public:
    static Driver& Instance()
    {
        static Driver instance;
        return instance;
    }

    std::string RunQuery(const std::string);

    Table* Execute(const cmd::Instruction&) override;
    Table* Execute(const cmd::Literal&) override;
    Table* Execute(const cmd::Expression&) override;
    Table* Execute(const cmd::Operation&) override;
    Table* Execute(const cmd::CreateTable&) override;
    Table* Execute(const cmd::DropTable&) override;
    Table* Execute(const cmd::Select&) override;
    Table* Execute(const cmd::Insert&) override;
    Table* Execute(const cmd::ShowCreateTable&) override;
    Table* Execute(const cmd::TableDefinition&) override;
    Table* Execute(const cmd::Update&) override;
    Table* Execute(const cmd::Delete&) override;
    Table* Execute(const cmd::Column&) override;
    Table* Execute(const cmd::ColumnDefintion&) override;

private:
    Driver() = default;
    ~Driver() = default;
    Driver(Driver const &) = delete;
    void operator=(Driver const &) = delete;
};

} // namespace sql