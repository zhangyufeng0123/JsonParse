#include"jsonP.h"

using namespace gotomove::jsonP;

Json::Json() : m_type(json_null){}

Json::Json(bool value) : m_type(json_bool){
    this->m_value.m_bool = value;
}

Json::Json(int value) : m_type(json_int){
    this->m_value.m_int = value;
}

Json::Json(double value) : m_type(json_double){
    this->m_value.m_double = value;
}

Json::Json(const char *value) : m_type(json_string){
    this->m_value.m_string = new std::string(value);
}

Json::Json(const std::string &value) : m_type(json_string){
    this->m_value.m_string = new std::string(value);
}

Json::Json(Type type) : m_type(type){
    switch (this->getType())
    {
    case json_null:
        /* code */
        break;
    case json_int:
        this->m_value.m_int = 0;
        break;
    case json_double:
        this->m_value.m_double = 0.0;
        break;
    case json_bool:
        this->m_value.m_bool = false;
        break;
    case json_string:
        this->m_value.m_string = new std::string("");
        break;
    case json_array:
        this->m_value.m_array = new std::vector<Json>();
        break;
    case json_object:
        this->m_value.m_object = new std::unordered_map<std::string, Json> ();
        break;
    
    default:
        break;
    }
}

Json::Json(const Json &other){
    this->copy(other);
}

//TODO:
Json::~Json(){
    
}


Json::Type Json::getType() const{
    return this->m_type;
}

bool Json::isNull() const{
    if(this->getType() == json_null) return true;
    return false;
}

bool Json::isBool() const{
    if(this->getType() == json_bool) return true;
    return false;
}

bool Json::isInt() const{
    if(this->getType() == json_int) return true;
    return false;
}

bool Json::isDouble() const{
    if(this->getType() == json_double) return true;
    return false;
}

bool Json::isString() const{
    if(this->getType() == json_string) return true;
    return false;
}

bool Json::isArray() const{
    if(this->getType() == json_array) return true;
    return false;
}

bool Json::isObject() const {
    if(this->getType() == json_object) return true;
    return false;
}

bool Json::asBool() const{
    if(!this->isBool()){
        throw std::logic_error("function Json::asBool() error, the type of Json is not bool");
    }
    return this->m_value.m_bool;
}

int Json::asInt() const{
    if(!this->isInt()){
        throw std::logic_error("function Json::asInt() error, the type of Json is not int");
    }
    return this->m_value.m_int;
}

double Json::asDouble() const{
    if(!this->isDouble()){
        throw std::logic_error("function Json::asDouble() error, the type of Json is not double");
    }
    return this->m_value.m_double;
}

std::string Json::asString() const{
    if(!this->isString()){
        throw std::logic_error("function Json::asString() error, the type of Json is not string");
    }
    return *(this->m_value.m_string);
}

void Json::copy(const Json &other){
    this->clear();
    this->set(other.m_type);
    switch (this->m_type)
    {
    case json_null:
        /* code */
        break;
    case json_bool:
        this->set(other.m_value.m_bool);
        break;
    case json_int:
        this->set(other.m_value.m_int);
        break;
    case json_double:
        this->set(other.m_value.m_double);
        break;
    case json_string:
        this->set(*(other.m_value.m_string));
        break;
    case json_array:
        this->set(*(other.m_value.m_array));
        break;
    case json_object:   
        this->set(*(other.m_value.m_object));
        break;
    default:
        break;
    }
}

int Json::size() const{
    switch (this->getType())
    {
    case json_null:
        return 0;
    case json_bool:
        return 1;
    case json_int:
        return 1;
    case json_double:
        return 1;
    case json_string:
        return 1;
    case json_array:
        return int((*(this->m_value.m_array)).size());
    case json_object:
        return int((*(this->m_value.m_object)).size());
    default:
        break;
    }
}

bool Json::empty() const{
    switch (this->getType())
    {
    case json_null:
        return true;
    case json_array:
        return (*(this->m_value.m_array)).empty();
    case json_object:
        return (*(this->m_value.m_object)).empty();
    
    default:
        return false;
    }
}

void Json::clear(){
    switch (this->getType())
    {
    case json_null:
        /* code */
        break;
    case json_bool:
        this->set(false);
        break;
    case json_int:
        this->set(0);
        break;
    case json_double:
        this->set(0.0);
        break;
    case json_string:
        (*(this->m_value.m_string)).clear();
        break;
    case json_array:
        (*(this->m_value.m_array)).clear();
        break;
    case json_object:
        (*(this->m_value.m_object)).clear();
        break;
    
    default:
        break;
    }
    this->m_type = json_null;
}

void Json::set(Type type){
    this->m_type = type;
}

void Json::set(bool value){
    this->m_value.m_bool = value;
}

void Json::set(int value){
    this->m_value.m_int = value;
}

void Json::set(double value){
    this->m_value.m_double = value;
}

void Json::set(const std::string &value){
    this->m_value.m_string = new std::string(value);
}

void Json::set(const char *value){
    this->m_value.m_string = new std::string(value);
}

bool Json::has(int index) const{
    if(!this->isArray()){
        throw std::logic_error("function Json::has(int) type error");
    }
    if(index < 0 || index >= this->size()) return false;
    return true;
}

bool Json::has(const char *key) const{
    if(!this->isObject()){
        throw std::logic_error("function Json::has(const char *) type error");
    }
    std::string name(key);
    return this->has(name);
}

bool Json::has(const std::string &key) const{
    if(!this->isObject()){
        throw std::logic_error("function Json::has(const std::string) type error");
    }
    std::unordered_map<std::string, Json>::const_iterator it = (*(this->m_value.m_object)).find(key);
    if(it != (*(this->m_value.m_object)).end()){
        return false;
    }
    return true;
}

const Json &Json::get(int index) const{
    if(!this->has(index)){
        throw std::logic_error("function Json::get(int) Subscript out-of-bounds");
    }
    return (*(this->m_value.m_array)).at(index);
}

const Json &Json::get(const char *key) const{
    if(!this->has(key)){
        throw std::logic_error("function Json::get(cosnt char *) value error");
    }
    return (*(this->m_value.m_object))[key];
}

const Json &Json::get(const std::string &key) const{
    if(!this->has(key)){
        throw std::logic_error("function Json::get(cosnt std::string &) value error");
    }
    return (*(this->m_value.m_object))[key];
}