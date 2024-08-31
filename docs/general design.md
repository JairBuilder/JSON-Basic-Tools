# 概要设计说明书

## 对外接口
- generate
    功能：将JSON对象转为JSON字符串
    参数：JSON对象
    返回值：JSON字符串
- parser
    功能：解析JSON字符串，解析结果保存在一个JSON对象中，可以是多层的
    参数：JSON字符串
    返回值：JSON对象
- to_struct
    功能：将JSON对象转为T对象
    参数：JSON对象，T对象
    返回值：T对象
- to_json
    功能：将T对象转为JSON对象
    参数：T对象
    返回值：JSON对象
- add
    功能：添加键值对
    参数：JSON对象，Key，Value
    返回值：无

## 别名及宏定义
Key：string
Value: shared_ptr<JSON_VALUE>

## 数据结构
- JSONParser
    - 功能：作为对外的接口类之一，可被使用者定义，用于解析JSON字符串，并将结果保存在一个JSON对象中
    - 私有变量：
        1. unordered_set<char> blank_chars 空白字符
        1. unordered_set<char> number_chars 数字字符
        1. unordered_set<char> word_chars 单词字符
        1. size_t idx;
    - 公有函数：
        1. JSON & parse(const string &) 解析JSON字符串, 返回JSON对象
    - 私有函数：
        1. next_pair() 获取下一个键值对
        1. next_word() 获取下一个单词
        1. next_string() 获取下一个双引号括住的字符串
        1. next_char() 获取下一个字符
        1. parse_number() 解析number :下一个字符为数字
        1. parse_int() 解析int :下一个字符为数字且没有.
        1. parse_string() 解析string :下一个字符为"
        1. parse_double() 解析double :下一个字符为数字含有.
        1. parse_bool() 解析bool :下一个单词为true或false
        1. parse_null() 解析null :下一个单词为null
        1. parse_array() 解析array  :下一个字符为[
        1. parse_object() 解析object :下一个字符为{

- JSON
    - 功能：作为主要公有类之一，可被使用者定义，用于实现JSON字符串的生成，以及作为结果的存储数据结构
    - 私有变量：
        1. map<Key, Value> data 存放JSON的所有键值对
    - 公有函数：
        1. void add(Key, Value) 添加键值对, Value可以是常量或变量
        1. string get_str_value(Key) 获取键值对, 返回Value字符串
        1. void* get_value(Key) 获取值, 返回Value指针，指向拷贝的value，而非data的value
        1. JSON_VALUE get_json_value(Key) 获取值, 返回JSON_VALUE对象拷贝
        1. string generate() 生成JSON字符串

    - 静态函数：
        1. to_struct<T>(JSON) 将JSON对象转为T对象
        1. to_json(T) 将T对象转为JSON对象

- JSON_VALUE
    - 功能：作为各种JSON类型的基类，实现赋值操作，利用多态使不同类型的值存储在一个JSON对象中
    - 私有变量：
        1. 无
    - 公有函数：
        1. virtual ~JSON_VALUE() {}
        1. virtual string str() = 0;    用于生成JSON字符串
        1. virtual string type() = 0; 返回JSON_VALUE的类型
        以下用于实现赋值操作，可直接用常量或变量赋值而无需转化为指针，均有默认实现，子类选择性重载
        1. virtual JSON_VALUE& operator=(const int &other);
        1. virtual JSON_VALUE& operator=(const string &other);
        1. virtual JSON_VALUE& operator=(const double &other);
        1. virtual JSON_VALUE& operator=(const bool &other);

- JSON_INT
    - 功能：实现INT类型
    - 私有变量：
        1. int value
    - 公有函数：
        1. JSON_INT(int value)
        1. string str() override
        1. string type() override
        1. JSON_VALUE& operator=(const int& other) override

- JSON_STRING
    - 功能：实现STRING类型
    - 私有变量：
        1. string value
    - 公有函数：
        1. JSON_STRING(string value)
        1. string str() override
        1. string type() override
        1. JSON_VALUE& operator=(const string& other) override

- JSON_DOUBLE
    - 功能：实现DOUBLE类型
    - 私有变量：
        1. double value
    - 公有函数：
        1. JSON_DOUBLE(double value)
        1. string str() override
        1. string type() override
        1. JSON_VALUE& operator=(const double& other) override

- JSON_BOOL
    - 功能：实现BOOL类型
    - 私有变量：
        1. bool value
    - 公有函数：
        1. JSON_BOOL(bool value)
        1. string str() override
        1. string type() override
        1. JSON_VALUE& operator=(const bool& other) override

- JSON_ARRAY
    - 功能：是对外的接口类之一，可被使用者定义，用于构造JSON的数组Array，允许存放不同种类的数据，并支持嵌套存放
    - 私有变量：
        1. vector<Value> value
    - 公有函数：
        1. JSON_ARRAY(vector<Value> value)
        1. string str() override
        1. string type() override
        1. JSON_VALUE& operator=(const vector<Value>& other) override
        1. add(const int &) 添加int元素
        1. add(const string &) 添加string元素
        1. add(const double &) 添加double元素
        1. add(const bool &) 添加bool元素
        1. add(const JSON_ARRAY &) 添加JSON_ARRAY元素
        1. add(const JSON_OBJECT &) 添加JSON_OBJECT元素

- JSON_OBJECT
    - 功能：同上，用于构造JSON的对象Object，允许存放不同种类的数据，并支持嵌套存放
    - 私有变量：
        1. JSON value
    - 公有函数：
        1. JSON_OBJECT(JSON value)
        1. string str() override
        1. string type() override
        1. JSON_VALUE& operator=(const JSON &) override
        1. add(const Key &, const Value &) 添加键值对

- JSON_NULL
    - 功能：实现NULL类型
    - 私有变量：
        1. 无
    - 公有函数：
        1. JSON_NULL()
        1. string str() override
        1. string type() override
