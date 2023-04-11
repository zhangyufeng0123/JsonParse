#pragma once

#include"json.h"

namespace gotomove{
namespace json{

class Parser{
public:
    Parser();
    void load(const std::string &str);

    Json parse();
private:
    void skip_white_space();
    char get_next_token();
    Json parse_null();
    Json parse_bool();
    Json parse_number();
    std::string parse_string();

private:
    std::string m_str;
    int m_idx;
};

}}