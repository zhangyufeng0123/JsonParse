# 项目文档

## **Json**

### **什么是Json**

根据[wiki](https://zh.wikipedia.org/wiki/JSON)

> Json(JavaScrip Object Notation)是由道格拉斯·克罗克服特构想和设计的一种轻量级资料交换格式。其内容由属性和值所组成，因此也有益于阅读和处理的优势。

### **Json的数据类型**

Json的数据类型主要分为六大类
1. **对象(object)**  
格式类似于
```
{
    "key1": value1;
    "key2": value2;
    ...
}
```

2. **数组(array)**  
格式类似于
```
"key": [
    value1, 
    value2, 
    value3, 
    ...];
```

3. **字符串(string)**  
格式类似于
```
"key": "string";
```

4. **数字(number)**  
数字可以分为两种，一种整数型，一种浮点型，两种储存方式不同

5. **布尔(bool)**  
布尔类型的值也是由两种组成，一个是`true`，另一个是`false`

6. **空值(null)**

### **Json不同类型的存储方式**  
TODO:[截图](https://www.json.org/json-en.html)

## **数据定义**

`Json`所需的成员变量主要是两种，一个是类型，另一个是`value`，其中不同类型对应不同的`value`存储方式。  
我们先定义类型，该处用了一个枚举类来定义Json的类型
```cpp
enum Type{
    json_null,
    json_bool,
    json_int,
    json_double,
    json_string,
    json_array,
    json_object
};
```
因为数字有整数型和浮点型，C++对这两类的存储方式不同，因此我们需要定义七种类型。  
定义完类型之后，我们需要对其`value`进行定义：  
当前我们所做的版本是阉割版，即不考虑内存消耗，因此我们对成员变量的定义也是简单粗暴。
```cpp
bool m_bool;
int m_int;
double m_double;
std::string m_string;
std::vector<Json> m_array;
std::map<std::string, Json> m_object;
```

## **API设计**
以下介绍的就是本项目的各种接口的实现

### **构造函数**

我们将构造函数分为**默认构造函数**、**有参构造函数**、**拷贝构造函数**。  
不同的构造函数对应不同的功能。

1. **默认构造函数**

```cpp
Json();
```
默认构造函数实现的是构建一个类型为`null`的`Json`对象

2. **有参构造函数**

有参构造函数是为了应对初始化不同类型的`Json`对象，上面说了Json的对象主要分为6种，我们分别对**布尔类型**、**数字**、**字符串**进行有参构造，其中字符串要注意构造方式有两种。

2-1. 布尔类型的有参构造
```cpp
Json(bool value);
```
将布尔类型的值赋给Json对象

2-2. 数字类型的有参构造

在C++中整数和浮点数是用不同的方式储存的，因此我们需要用两个有参构造类分别构造Json对象。

```cpp
Json(int value);
```
这是对整数型的Json进行构造

```cpp
Json(double value);
```
这是对浮点型的Json进行构造

2-3. 字符串类型的有参构造
```cpp
Json(const char *value);
```
该构造将C语言的字符串存储方式作为对象进行构造，具体构造还需要将`char *`转换成`string`

```cpp
Json(const std::string &value);
```

2-4. 属性的有参构造
我们对不同类型的属性有着不同的初始化  
因为我们的构造函数涉及到的数据类型只有空值、数值型、字符串型、布尔型，所以我们只针对这些数据类型进行初始化
```cpp
Json(const Json &other);
```
- `json_null` : `value`不做处理
- `json_int` : `value = 0`
- `json_double` : `value = 0.0`
- `json_bool` : `value = false`
- `json_string` : `value = ""`

3. **拷贝构造函数**
### **判断属性**

为了避免直接操作对象的成员变量，我们用成员函数来确认该Json对象是否是我们需要的类型。

1. 判断是否为空值  

```cpp
bool isNull() const;
```

2. 判断是否为布尔类型  
```cpp
bool isBool() const;
```

3. 判断是否为整数型  
```cpp
bool isInt() const;
```

4. 判断是否为浮点型  
```cpp
bool isDouble() const;
```

5. 判断是否为字符串型  
```cpp
bool isString() const;
```

6. 判断是否为数组
```cpp
bool isArray() const;
```

7. 判断是否为哈希
```cpp
bool isObject() const;
```

上述函数都在函数名末尾加了`const`，加`const`是为了防止函数体有对该对象的成员变量进行修改。

### **返回对象类型**

在具体操作过程中，我们得知道该Json对象的具体类型，但是又不能操作成员变量，这个时候我们就可以通过成员函数来获取对象类型

```cpp
Type type() const;
```

### **返回Json的对应的值**
作为一个对象，我们希望他们能返回相应变量的值，当然，如果数据类型不匹配，则需要输出异常通知用户。  
下面几个函数当且仅当`Json`对象和函数对象的数据类型一致时才返回`Json`的value值

1. 返回`bool`类型的`Json`对象
```cpp
bool asBool() const;
```

2. 返回`int`类型的`Json`对象
```cpp
int asInt() const;
```

3. 返回`double`类型的`Json`对象
```cpp
double asDouble() const;
```

4. 返回`std::string`类型的`Json`对象
```cpp
std::string asString() const;
```

### **针对数组和对象的删除操作**

1. 针对数组的删除操作  
```cpp
void remove(int index);
```
对于传入的index我们得先判断是否合法，如果不合法，则输出传回异常，否则利用底层的`vector`容器的`erase`删除即可

2. 针对对象的删除操作
```cpp
void remove(const char *key);
void remove(const std::string &key);
```
针对传入值的两种不同体现方式，我们用两个函数来实现，但是其中我们可以在第一个函数将`const char*`转换成`std::string`之后再调用第二个函数来完成删除操作。  

对于传入的`key`值，我们得先找到`std::map`容器中是否存储该键值，如果没有那就返回异常，如果有则删除。

### **针对数组/对象是否存在某个键值**

利用了三个函数（实际上两个，但是需要三个实现）来判断数组/对象是否存在某个元素  

1. 判断数组中是否存在某个索引值的值
```cpp
bool has(int index) const;
```
因为这边只需要判断即可，所以下标越界不返回异常，但是如果`Json`类型不是数组类型则需要返回异常。

2. 判断对象中是否存在某个键值的值
```cpp
bool has(const char *key) const;
bool has(const std::string &key) const;
```
这边也是需要和上面一样，如果`Json`类型不符才需要返回异常，否则只要判断有无该键值即可

### **获取数组/对象中的值**

利用三个函数来获取数组/对象中的值
1. 获取数组中对应索引值的`value`值
```cpp
const Json &get(int index) const;
```

2. 获取对象中对应键值的`value`值
```cpp
const Json &get(const char *key) const;
const Json &get(const std::string &key) const;
```
上述三个函数都需要`Json`是对应的数据类型

### **重新初始化Json对象**

利用`set()`的重载函数针对不同的数据类型进行重新初始化

1. 根据另一个`Json`对象进行拷贝初始化  
```cpp
void set(const Json &other);
```

2. 根据布尔类型进行初始化
```cpp
void set(bool value);
```

3. 根据整型进行初始化
```cpp
void set(int value);
```

4. 根据浮点型进行初始化
```cpp
void set(double value);
```

5. 根据字符串进行初始化
```cpp
void set(const std::string &value);
void set(const char *value);
```

### **辅助函数**

1. 复制另一个`Json`对象
```cpp
void copy(const Json &other);
```
将另一个对象的数据类型和数据值拷贝过来

2. 获取数组/对象长度

```cpp
int size() const;
```
这个函数是针对`array`和`object`的，因此如果是其他数据类型则需要返回异常

3. 判断`Json`是否为空
```cpp
bool empty() const;
```
Json什么时候才为空呢？只有三种情况，一种是array长度为0，一种是object长度为0，另一种是Json的数据类型就是null类型

4. 清空Json对象中的所有内容
```cpp
void clear();
```
将Json对象的数据类型换成json_null，并将原来的数据类型对应的数值进行初始化操作。

5. 输出Json对象的所有内容

```cpp
std::string to_String() const;
```

### **重载赋值函数**

1. 赋值另一个Json对象
```cpp
Json &operator = (const Json &other);
```

2. 赋值布尔类型的值
```cpp
Json &operator = (bool value);
```

3. 赋值整型的值
```cpp
Json &operator = (int value);
```

4. 赋值浮点型的值
```cpp
Json &operator = (double value);
```

5. 赋值字符串型的值
```cpp
Json &operator = (const char *value);
Json &operator = (cosnt std::string &value);
```

### **重载判断相等**

1. 判断两个Json对象是否相等
```cpp
bool operator == (const Json &other);
```

2. 判断Json对象与布尔类型的值是否相等
```cpp
bool operator == (bool value);
```

3. 判断Json对象与整数型的值是否相等
```cpp
bool operator == (int value);
```

4. 判断Json对象与浮点型的值是否相等
```cpp
bool operator == (double value);
```

5. 判断Json对象与字符串型的值是否相等
```cpp
bool operator == (const std::string &value);
bool operator == (const char *value);
```

### 重载判断不相等

判断不相等的函数体很好写，因为我们只要在对应的判断相等前加个**非**即可，但是要注意数据类型，数据类型不同要返回异常

1. 判断两个Json对象不相等
```cpp
bool operator != (const Json &other);
```

2. 判断Json对象与布尔型的值不相等
```cpp
bool operator != (bool value);
```

3. 判断Json对象与整型的值不相等
```cpp
bool operator != (int value);
```

4. 判断Json对象与浮点型的值不相等
```cpp
bool operator != (double value);
```

5. 判断Json对象与字符串型的值不相等
```cpp
bool operator != (const std::string &value);
bool operator != (const char *key);
```

### 返回类型重载
将Json对象具体赋值给某些具体数据类型时需要用到这些重载函数  
比如
```cpp
Json v1 = true;
bool b = v1;
```
要想实现如上的操作，就需要对赋值进行重载

1. 对json_bool进行重载

```cpp
operator bool();
```

2. 对json_int进行重载
```cpp
operator int();
```

3. 对json_double进行重载
```cpp
operator double();
```

4. 对json_string进行重载
```cpp
operator std::string();
operator std::string() const;
```

### **array的增查操作**

1. **array**增加元素

目前实现了array的往后添加元素的操作，利用了vector容器的push_back()操作
```cpp
Json &push_back(const Json &value);
```

2. **array**查询元素

```cpp
const Json &operator[](int index) const;
```

### **object的增查操作**
1. **object**增加元素
利用`[]`操作往std::map中添加<key, value>组合对

```cpp
Json &operator[] (const std::string &key);
Json &operator[] (const char *key);
```

2. **object**查找元素

```cpp
const Json &operator[](const char *key) const;
const Json &operator[] (const std::string &key) const;
```



## 编写代码时遇到的问题

### 不完全类
刚开始的时候储存对象我用的变量类型是`unordered_map<string, Json>`，但是因为`Json`是不完全类，`Json`还未完全定义我就将它变成变量类型来使用，然后就一直报错。如果我要使用不完全类作为变量的话，那就需要用指针，用指针的时候我将`Json`作为`unordered_map`的第二参数就是可以的。
这里我将`unordered_map`换成了`map`也可以运行。

### const修饰函数时map根据key值获取value的方式将会改变
在编写`const Json &get(const std::string &key) const;`函数时遇到了使用[]不能根据`key`值获取`value`，之后查阅资料才发现：

> 对于const的对象使用了非const的成员函数：std::map::[]本身不是const成员函数（操作符），对于不在map中的关键字，使用下标操作符会创建新的条目，改变了map


## 待解决的问题

为什么不完全类作为变量类型时可以用`map`来存储，而不能用`unordered_map`来存储。

