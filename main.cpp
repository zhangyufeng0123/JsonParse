#include"jsonP.h"
#include<iostream>

using namespace gotomove::jsonP;

void test01();  //测试构造函数
void test02();  //测试判断对象数据类型的函数
void test03();  //测试返回

int main(){
    test03();
 
    std::cout << "finish" << std::endl;
    return 0;
}

void test03(){
    Json v1;
    Json v2 = true;
    Json v3 = 13;
    Json v4 = 1.3;
    Json v5 = "hello json";
    Json v6(v1);

//asBool()
    try{
        bool b1 = v2.asBool();
        std::cout << "b1 can get value" << std::endl;
        bool b2 = v3.asBool();
        std::cout << "b2 can get value" << std::endl;
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }

//asInt()
    try{
        int b1 = v3.asInt();
        std::cout << "b1 can get value" << std::endl;
        int b2 = v4.asInt();
        std::cout << "b2 can get value" << std::endl;
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }

//asDouble()
    try{
        double b1 = v4.asDouble();
        std::cout << "b1 can get value" << std::endl;
        double b2 = v5.asDouble();
        std::cout << "b2 can get value" << std::endl;
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }

//asString()
    try{
        std::string b1 = v5.asString();
        std::cout << "b1 can get value" << std::endl;
        std::string b2 = v6.asString();
        std::cout << "b2 can get value" << std::endl;
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

void test02(){
    Json v1;
    Json v2 = true;
    Json v3 = 13;
    Json v4 = 1.3;
    Json v5 = "hello json";
    Json v6(v1);

//isNull() 函数测试
    if(v1.isNull()) std::cout << "v1 is null" << std::endl;
    else std::cout << "v1 is not null" << std::endl;

    if(v2.isNull()) std::cout << "v1 is null" << std::endl;
    else std::cout << "v2 is not null" << std::endl;

//isBool() 函数测试
    if(v2.isBool()) std::cout << "v2 is bool" << std::endl;
    else std::cout << "v2 is not bool" << std::endl;

    if(v3.isBool()) std::cout << "v3 is bool" << std::endl;
    else std::cout << "v3 is not bool" << std::endl;

//isInt()
    if(v3.isInt()) std::cout << "v3 is int" << std::endl;
    else std::cout << "v3 is not int" << std::endl;

    if(v4.isInt()) std::cout << "v4 is int" << std::endl;
    else std::cout << "v4 is not int" << std::endl;

//isDouble()
    if(v4.isDouble()) std::cout << "v4 is double" << std::endl;
    else std::cout << "v4 is not double" << std::endl;

    if(v5.isDouble()) std::cout << "v5 is double" << std::endl;
    else std::cout << "v5 is not double" << std::endl;

//isString()
    if(v5.isString()) std::cout << "v5 is string" << std::endl;
    else std::cout << "v5 is not string" << std::endl;

    if(v6.isString()) std::cout << "v6 is string" << std::endl;
    else std::cout << "v6 is not string" << std::endl;

//TODO:isArray()

//TODO:isObject()
}

void test01(){
    Json::Type type = Json::Type::json_int;
    Json v1;
    Json v2 = true;
    Json v3 = 13;
    Json v4 = 1.3;
    Json v5 = "hello json";
    Json v6(v1);
    Json v7(type);
}