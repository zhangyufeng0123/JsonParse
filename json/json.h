#pragma once

#include<string>
#include<vector>
#include<map>

namespace gotomove{
namespace json{
    
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

//默认构造函数、有参构造、拷贝构造
    Json();
    Json(bool value);
    Json(int value);
    Json(double value);
    Json(const char *value);
    Json(const std::string &value);
    Json(Type type);
    Json(const Json &other);
    ~Json();

//返回对象类型
    Type type() const;

//判断属性
    bool isNull() const;
    bool isBool() const;
    bool isInt() const;
    bool isDouble() const;
    bool isString() const;
    bool isArray() const;
    bool isObject() const;

//返回值
    bool asBool() const;
    int asInt() const;
    double asDouble() const;
    std::string asString() const;

//复制另一个Json对象
    void copy(const Json &other);

//获取array的长度或者object的长度
    int size() const;

//判断一个对象是否为空
    bool empty() const;

//清空所有内容
    void clear();

//移除数组、对象中元素的位置
    void remove(int index);
    void remove(const char *key);
    void remove(const std::string &key);

//判断数组、对象中是否还有该元素
    bool has(int index) const;
    bool has(const char *key) const;
    bool has(const std::string &key) const;

//获取数组、对象中的元素
    const Json &get(int index) const;
    const Json &get(const char *key) const;
    const Json &get(const std::string &key) const;

//重新设置对象
    void set(const Json &other);
    void set(bool value);
    void set(int value);
    void set(double value);
    void set(const std::string &value);
    void set(const char *value);
    
//往数组后面添加对象
    Json &push_back(const Json &value);

//重载赋值函数
    Json &operator = (const Json &other);
    Json &operator = (bool value);
    Json &operator = (int value);
    Json &operator = (double value);
    Json &operator = (const std::string &value);
    Json &operator = (const char *value);

//重载判断相等函数
    bool operator == (const Json &other);
    bool operator == (bool value);
    bool operator == (int value);
    bool operator == (double value);
    bool operator == (const std::string &value);
    bool operator == (const char *value);

//重载判断不相等函数
    bool operator != (const Json &other);
    bool operator != (bool value);
    bool operator != (int value);
    bool operator != (double value);
    bool operator != (const std::string &value);
    bool operator != (const char *value);

//将Json对象返回相应的类型
    operator bool();
    operator int();
    operator double();
    operator std::string();
    operator std::string() const;

//根据随机型的allocator来获取数组的内容
    const Json & operator[] (int index) const;

//在map中通过[]添加key和查找
    Json &operator[] (const char *key);
    const Json &operator[](const char *key) const;

    Json &operator[] (const std::string &key);
    const Json &operator[] (const std::string &key) const;

//输出Json对象中的内容
    std::string to_String() const;

//解析
    void parse(const std::string &str);

    typedef std::vector<Json>::iterator iterator;
    typedef std::vector<Json>::const_iterator const_iterator;

    iterator begin(){
        return this->m_array.begin();
    }

    iterator end(){
        return this->m_array.end();
    }

    const_iterator begin() const{
        return this->m_array.begin();
    }

    const_iterator end() const{
        return this->m_array.end();
    }
private:
    Type m_type;

    bool m_bool;
    int m_int;
    double m_double;
    std::string m_string;
    std::vector<Json> m_array;
    std::map<std::string, Json> m_object;
};

}} // namespace gotomove