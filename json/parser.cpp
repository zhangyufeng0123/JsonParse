#include"parser.h"

using namespace gotomove::json;

Parser::Parser() : m_str(""), m_idx(0){

}

void Parser::load(const std::string &str){
    this->m_str = str;
    this->m_idx = 0;
}

void Parser::skip_white_space(){
    while(this->m_str[this->m_idx] == ' ' || this->m_str[this->m_idx] == '\n' || m_str[this->m_idx] == '\r' || m_str[this->m_idx] == '\t') {
        this->m_idx++;
    }
}

char Parser::get_next_token(){
    this->skip_white_space();
    return this->m_str[this->m_idx++];
}

Json Parser::parse(){
    char ch = this->get_next_token();
    switch (ch)
    {
    case 'n':
        this->m_idx--;
        return parse_null();
    case 't':
    case 'f':
        this->m_idx--;
        return parse_bool();
    case '-':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        this->m_idx--;
        return parse_number();
    case '"':
        return Json(parse_string());
    // case '[':
    //     return parse_array();
    // case '{':
    //     return parse_object();
    
    default:
        break;
    }
    throw std::logic_error("unexpected char");
}

Json Parser::parse_null(){
    if(this->m_str.compare(m_idx, 4, "null") == 0) {
        this->m_idx += 4;
        return Json();
    }
    throw std::logic_error("parser null error");
}


Json Parser::parse_bool(){
    if(this->m_str.compare(m_idx, 4, "true") == 0){
        this->m_idx += 4;
        return Json(true);
    }else if(this->m_str.compare(m_idx, 5, "false") == 0){
        this->m_idx += 5;
        return Json(false);
    }
    throw std::logic_error("parser bool error");
}

Json Parser::parse_number(){
    int pos = this->m_idx;

    if(this->m_str[this->m_idx] == '-'){
        ++this->m_idx;
    }

    if(this->m_str[this->m_idx] == '0'){
        ++this->m_idx;
        if(this->m_str[this->m_idx] >= '0' && this->m_str[this->m_idx] <= '9'){
            throw std::logic_error("leading 0s not permitted in numbers");
        }
    }else if(this->m_str[this->m_idx] >= '1' && this->m_str[this->m_idx] <= '9'){
        ++this->m_idx;
        while(this->m_str[this->m_idx] >= '0' && this->m_str[this->m_idx] <= '9'){
            ++this->m_idx;
        }
    }else{
        throw std::logic_error("invalid character in number");
    }

    if(this->m_str[this->m_idx] != '.'){
        return std::atoi(this->m_str.c_str() + pos);
    }

    if(this->m_str[this->m_idx] == '.'){
        ++this->m_idx;
        if(this->m_str[this->m_idx] < '0' || this->m_str[this->m_idx] > '9'){
            throw std::logic_error("at least one digit required in fractional part");
        }
        while(this->m_str[this->m_idx] >= '0' && this->m_str[this->m_idx] <= '9'){
            ++this->m_idx;
        }
    }
    return std::atoi(this->m_str.c_str() + pos);
}

std::string Parser::parse_string(){
    std::string out;
    while(true){
        if(this->m_idx == this->m_str.size()){
            throw std::logic_error("unexpected end of input in string");
        }
        char ch = this->m_str[this->m_idx++];
        if(ch == '"'){
            return out;
        }else if(ch != '\\'){
            out += ch;
            continue;
        }
        throw std::logic_error("not support escaped characters in string");
    }
}