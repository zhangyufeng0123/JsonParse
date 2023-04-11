#include "json.h"
#include<sstream>
#include "parser.h"

using namespace gotomove::json;

Json::Json(){
    this->m_type = json_null;
}

Json::Json(bool value) : m_type(json_bool){
    this->m_bool = value;
}

Json::Json(int value) : m_type(json_int){
    this->m_int = value;
}

Json::Json(double value) : m_type(json_double){
    this->m_double = value;
}

Json::Json(const std::string &value) : m_type(json_string){
    this->m_string = value;
}

//委托构造函数
Json::Json(const char *value) : m_type(json_string){
    this->m_string = value;
}

Json::Json(Type type) : m_type(type){
    switch (type)
    {
    case json_null:
        /* code */
        break;
    case json_bool:
        this->m_bool = false;
        break;
    case json_int:
        this->m_int = 0;
        break;
    case json_double:
        this->m_double = 0.0;
        break;
    
    default:
        break;
    }
}

Json::Json(const Json &other){
    this->copy(other);
}

Json::~Json(){

}

Json::Type Json::type() const{
    return this->m_type;
}

bool Json::isNull() const{
    return this->type() == json_null;
}

bool Json::isBool() const{
    return this->type() == json_bool;
}

bool Json::isInt() const{
    return this->type() == json_int;
}

bool Json::isDouble() const{
    return this->type() == json_double;
}

bool Json::isString() const{
    return this->type() == json_string;
}

bool Json::isArray() const{
    return this->type() == json_array;
}

bool Json::isObject() const{
    return this->type() == json_object;
}

bool Json::asBool() const{
    if(!this->isBool()){
        throw std::logic_error("function Json::asBool value type error");
    }
    return this->m_bool;
}

int Json::asInt() const{
    if(!this->isInt()) {
        throw std::logic_error("function Json::asInt value type error");
    }
    return this->m_int;
}

double Json::asDouble() const{
    if(!this->isDouble()){
        throw std::logic_error("function Json::asDouble value type error");
    }
    return this->m_double;
}

std::string Json::asString() const{
    if(!this->isString()){
        throw std::logic_error("function Json::asString value type error");
    }
    return this->m_string;
}

void Json::copy(const Json &other){
    this->clear();
    this->m_type = other.type();
    switch (this->type())
    {
    case json_null:
        /* code */
        break;
    case json_bool:
        this->m_bool = other.m_bool;
        break;
    case json_int:
        this->m_int = other.m_int;
        break;
    case json_double:
        this->m_double = other.m_double;
        break;
    case json_string:
        this->m_string = other.m_string;
        break;
    case json_array:
        this->m_array = other.m_array;
        break;
    case json_object:
        this->m_object = other.m_object;
        break;
    default:
        break;
    }
}

int Json::size() const{
    switch (this->type())
    {
    case json_array:
        return int(this->m_array.size());
    case json_object:
        return int(this->m_object.size());
    default:
        throw std::logic_error("function Json::size value type error");
    }
}

bool Json::empty() const{
    switch (this->type())
    {
    case json_null:
        return true;
    case json_array:
        return this->m_array.empty();
    case json_object:
        return this->m_object.empty();
    
    default:
        return false;
    }
}

void Json::clear(){
    switch (this->type())
    {
    case json_null:
        /* code */
        break;
    case json_bool:
        this->m_bool = false;
        break;
    case json_int:
        this->m_int = 0;
        break;
    case json_double:
        this->m_double = 0.0;
        break;
    case json_string:
        this->m_string = "";
        break;
    case json_array:
        this->m_array.clear();
        break;
    case json_object:
        this->m_object.clear();
        break;
    default:
        break;
    }
}

void Json::remove(int index){
    if(!this->isArray()){
        throw std::logic_error("function Json::remove(int) type value error");
    }
    if(index < 0 || index >= this->size()){
        throw std::logic_error("function Json::remove(int) Subscript out-of-bounds");
    }
    this->m_array.erase(this->m_array.begin() + index);
}

void Json::remove(const char *key){
    std::string name(key);
    this->remove(name);
}

void Json::remove(const std::string &key){
    if(!this->isObject()){
        throw std::logic_error("function Json::remove(string) type value error");
    }
    std::map<std::string, Json>::iterator it = this->m_object.find(key);
    if(it == this->m_object.end()){
        throw std::logic_error("function Json::remove(string) Subscript out-of-bounds");
    }
    this->m_object.erase(it);
}

bool Json::has(int index) const{
    if(!this->isArray()){
        throw std::logic_error("function Json::has(int) type value error");
    }
    if(index < 0 || index >= this->size()){
        return false;
    }
    return true;
}

bool Json::has(const char *key) const{
    std::string name(key);
    return this->has(name);
}

bool Json::has(const std::string &key) const{
    if(!this->isObject()) {
        throw std::logic_error("function Json::has(string) type value error");
    }
    std::map<std::string, Json>::const_iterator it = this->m_object.find(key);
    if(it == this->m_object.end()){
        return false;
    }
    return true;
}

const Json &Json::get(int index) const{
    if(this->has(index)){
        return this->m_array.at(index);
    }
    throw std::logic_error("function Json::get(int) Subscript out-of-bounds");
}

const Json &Json::get(const char *key) const{
    std::string name(key);
    return this->get(name);
}

const Json &Json::get(const std::string &key) const{
    if(!this->has(key)){
        return this->m_object.at(key);
    }
    throw std::logic_error("function Json::get(string) Subscript out-of-bounds");
}

void Json::set(const Json &other){
    this->copy(other);
}

void Json::set(bool value){
    this->clear();
    this->m_type = json_bool;
    this->m_bool = value;
}

void Json::set(int value){
    this->clear();
    this->m_type = json_int;
    this->m_int = value;
}

void Json::set(double value){
    this->clear();
    this->m_type = json_double;
    this->m_double = value;
}

void Json::set(const std::string &value){
    this->clear();
    this->m_type = json_string;
    this->m_string = value;
}

void Json::set(const char *value){
    std::string name(value);
    this->set(name);
}

Json &Json::push_back(const Json &value){
    if(this->isNull()){
        this->m_type = json_array;
    }
    if(!this->isArray()){
        throw std::logic_error("function Json::push_back requires array value");
    }
    this->m_array.push_back(value);
    return *this;
}

Json &Json::operator=(const Json &other){
    this->copy(other);
    return *this;
}

Json &Json::operator=(bool value){
    this->set(value);
    return *this;
}

Json &Json::operator=(int value){
    this->set(value);
    return *this;
}

Json &Json::operator=(double value){
    this->set(value);
    return *this;
}

Json &Json::operator=(const std::string &value){
    this->set(value);
    return *this;
}

Json &Json::operator = (const char *value){
    this->set(value);
    return *this;
}


bool Json::operator==(const Json &other){
    if(this->type() != other.type()) return false;
    switch (this->type())
    {
    case json_null:
        return true;
    case json_bool:
        return this->m_bool == other.m_bool;
    case json_int:
        return this->m_int == other.m_int;
    case json_double:
        return this->m_double == other.m_double;
    case json_string:
        return this->m_string == other.m_string;
    default:
        return false;
    }
}

bool Json::operator==(bool value){
    if(!this->isBool()) return false;
    return this->m_bool == value;
}

bool Json::operator==(int value){
    if(!this->isInt()) return false;
    return this->m_int == value;
}

bool Json::operator==(double value){
    if(!this->isDouble()) return false;
    return this->m_double == value;
}

bool Json::operator==(const std::string &value){
    if(!this->isString()) return false;
    return this->m_string == value;
}

bool Json::operator==(const char *value){
    std::string name(value);
    return *this == name;
}

bool Json::operator!=(const Json &other){
    return !(*this == other);
}

bool Json::operator!=(bool value){
    return !(*this == value);
}

bool Json::operator!=(int value){
    return !(*this == value);
}

bool Json::operator!=(double value){
    return !(*this == value);
}

bool Json::operator!=(const std::string &value){
    return !(*this == value);
}

bool Json::operator!=(const char *value){
    return !(*this == value);
}

Json::operator bool(){
    if(!this->isBool()){
        throw std::logic_error("function Json::operator(bool) requires bool value");
    }
    return this->m_bool;
}

Json::operator int(){
    if(!this->isInt()){
        throw std::logic_error("function Json::operator(int) requires int value");
    }
    return this->m_int;
}

Json::operator double(){
    if(!this->isDouble()){
        throw std::logic_error("function Json::operator(double) requires double value");
    }
    return this->m_double;
}

Json::operator std::string(){
    if(!this->isString()){
        throw std::logic_error("function Json::operator(string) requires string value");
    }
    return this->m_string;
}

Json::operator std::string() const{
    if(!this->isString()){
        throw std::logic_error("function Json::operator(string) requires string value");
    }
    return this->m_string;
}

const Json & Json::operator[] (int index) const{
    return this->get(index);
}

Json &Json::operator[] (const char *key){
    std::string name(key);
    return this->m_object[name];
}

Json &Json::operator[] (const std::string &key){
    if(this->isNull()){
        this->m_type = json_object;
    }
    if(type() != json_object){
        throw std::logic_error("function Json::operator [const string &] requires object value");
    }
    return this->m_object[key];
}

const Json &Json::operator[] (const char *key) const{
    return this->get(key);
}

const Json &Json::operator [] (const std::string &key) const{
    return this->get(key);
}

std::string Json::to_String() const{
    std::ostringstream os;
    switch (this->type())
    {
    case json_null:
        /* code */
        os << "null";
        break;
    case json_bool:
        if(this->m_bool) {
            os << "true";
        }else {
            os << "false";
        }
        break;
    case json_int:
        os << this->m_int;
        break;
    case json_double:
        os << this->m_double;
        break;
    case json_string:
        os << '\"' << this->m_string << '\"';
        break;
    case json_array:
        os << "[";
        for(std::vector<Json>::const_iterator it = this->m_array.begin(); it != this->m_array.end(); ++it){
            if(it != this->m_array.begin()) {
                os << ",";
            }
            os << it->to_String();
        }
        os << ']';
        break;
    case json_object:
        os << '{';
        for(std::map<std::string, Json>::const_iterator it = this->m_object.begin(); it != this->m_object.end(); ++it){
            if(it != this->m_object.begin()){
                os << ',';
            }
            os << '\"' << it->first << "\":" << it->second.to_String();
        }
        os << '}';
        break;
    default:
        break;
    }
    return os.str();
}

void Json::parse(const std::string &str){
    Parser p;
    p.load(str);
    *this = p.parse();
}

