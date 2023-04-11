#pragma once

#include<string>
#include<vector>
#include<unordered_map>

namespace gotomove{
namespace jsonP{

class Json{
public:
    enum Type{
        json_null,
        json_bool,
        json_int,
        json_double,
        json_string,
        json_array,
        json_object
    };

//构造函数 & 析构函数
    Json();
    Json(bool value);
    Json(int value);
    Json(double value);
    Json(const char *value);
    Json(const std::string &value);
    Json(Type type);
    Json(const Json &other);
    ~Json();

//判断属性
    bool isNull() const;
    bool isBool() const;
    bool isInt() const;
    bool isDouble() const;
    bool isString() const;
    bool isArray() const;
    bool isObject() const;

//返回函数返回体变量的值，如果变量类型不匹配，返回异常
    bool asBool() const;
    int asInt() const;
    double asDouble() const;
    std::string asString() const;
    

//辅助功能函数
    Type getType() const;
    void copy(const Json &other);
    int size() const;
    bool empty() const;
    void clear();

//对成员变量进行赋值操作
    void set(Type type);
    void set(bool value);
    void set(int value);
    void set(double value);
    void set(const std::string &value);
    void set(const char *value);
    void set(std::vector<Json> &value);
    void set(std::unordered_map<std::string, Json> &value);

//array、object的删除操作
    void remove(int index);
    void remove(const char *key);
    void remove(const std::string &key);

//查询array、object是否有某元素
    bool has(int index) const;
    bool has(const char *key) const;
    bool has(const std::string &key) const;

//获取array、object中的元素
    const Json &get(int index) const;
    const Json &get(const char *key) const;
    const Json &get(const std::string &key) const;
    
//往数组后面添加对象
    Json &push_back(const Json &value);

//重载赋值函数
    Json &operator = (const Json &other);
    Json &operator = (bool value);
    Json &operator = (int value);
    Json &operator = (double value);
    Json &operator = (const std::string &value);
    Json &operator = (const char *value);

private:
    union Value{
        bool m_bool;
        int m_int;
        double m_double;
        std::string *m_string;
        std::vector<Json> *m_array;
        std::unordered_map<std::string, Json> *m_object;
    };

    Type m_type;
    Value m_value;
};

}}