#pragma once
#include "JSON_VALUE.h"
#include <memory>
namespace json {
    using Key = std::string;
    using Value = std::shared_ptr<JSON_VALUE>;
}