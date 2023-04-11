#include<iostream>
#include"json.h"

using namespace gotomove::json;

/**
 * TODO:测试map的使用
*/

void test01();  //测试构造函数+判断类型
void test02();  //测试返回值
void test03();  //测试将Json对象转换为对应的变量类型
void test04();  //测试打印输出Json对象的内容，数组扩充
void test05();  //测试解析

// int main(){
//     // test01();
//     // test02();
//     // test03();
//     // test04();
//     test05();
//     std::cout << "hello world" << std::endl;

//     return 0;
// }

void test05(){
    try{
        const std::string str = "\"hello world\"";
        Json v;
        v.parse(str);
        std::cout << v.to_String() << std::endl;
    }catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

void test04(){
    Json v1;
    Json v2(123);
    Json v3(1.23);
    Json v4(true);
    Json v5("hello world");
    Json v6(v2);

    try{
        v1.push_back(v2);
        v1.push_back(v3);
        v1.push_back(v4);
        v1.push_back(v5);
        v1.push_back(v6);
        std::cout << v1.to_String() << std::endl;
    }catch(const std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

void test03(){
    Json v1;
    Json v2(123);
    Json v3(1.23);
    Json v4(true);
    Json v5("hello world");
    Json v6(v2);

    try{
        std::string a1 = v5;
        std::cout << a1 << std::endl;
    }catch(const std::exception &e){
        std::cout << e.what() << std::endl;
    }

}

void test02(){
    std::cout << "begin test02 " << std::endl;
    
    Json v1;
    Json v2(123);
    Json v3(1.23);
    Json v4(true);
    Json v5("hello world");
    Json v6(v2);


    try{
        std::cout << v2.asBool() << std::endl;
        std::cout << v2.asDouble() << std::endl;
        std::cout << v2.asInt() << std::endl;
        std::cout << v2.asString() << std::endl;
    }catch(const std::exception &e){
        std::cout << e.what() << std::endl;
    }    

    std::cout << "finish test02" << std::endl;
}

void test01(){
    std::cout << "begin test01 " << std::endl;

    Json v1;
    Json v2(123);
    Json v3(1.23);
    Json v4(true);
    Json v5("hello world");
    Json v6(v2);

    if(v1.isNull()){
        std::cout << "v1 is NULL" << std::endl;
    }else {
        std::cout << "v1 is not NULL" << std::endl;
    }

    if(v2.isInt()){
        std::cout << "v2 is INT" << std::endl;
    }else{
        std::cout << "v2 is not INT" << std::endl;
    }

    if(v3.isDouble()){
        std::cout << "v3 is DOUBLE" << std::endl;
    }else{
        std::cout << "v3 is not DOUBLE" << std::endl;
    }

    if(v4.isBool()){
        std::cout << "v4 is BOOL" << std::endl;
    }else{
        std::cout << "v4 is not BOOL" << std::endl;
    }

    if(v5.isString()){
        std::cout << "v5 is String" << std::endl;
    }else{
        std::cout << "v5 is not String" << std::endl;
    }

    std::cout << "finish test01" << std::endl;
}