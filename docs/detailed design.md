# 详细设计说明书

## 架构设计

## 数据设计

## 功能设计

```
generate {
    def str, oss
    oss store '{' at first
    use oss contact the key:value from data
    in the for {
        key = first
        value = second.str // 这里的str()是JSON_VALUE的虚函数，是核心步骤之一
        oss store "key":value //value如果是字符串，str返回双引号，均直接返回对应的格式
        if data have next item, oss store ','
    }
    oss store '}' at end
    get str from oss
    return str
}
```

```
all other str {
    def oss
    oss store value
    return oss.str
    if value is string, oss store " at first and " at end
}
array str {
    def oss
    oss store '[' at first
    use oss contact the value from value
    in the for {
        oss store it.str
        if value have next item, oss store ','
    }
    oss store ']' at end
    get str from oss
    return str
}
object str {
    return generate
}
```

```
parse {
    def json;
    while (idx not end) {
        json add next_pair
    }
    return json
}
```

```
next_pair {
    def key, value
    key = next_string
    next_char // on ':'
    value = parse_value
    return key, value
}

excape blank { //move to the first vilid char
    idx++;  // skip ':'
    while str[idx] is blank char : idx++;
}

next_char {
    excape blank
    return str[idx]
}

next_string {
    excape blank
    def str
    while str[idx] is not '"' : escape, idx++
    while str[idx] is not '"' : str += str[p], idx++
    //idx on "
    return str
}

next_word {
    excape blank
    def word
    while str[idx] in word chars : word += str[idx] idx++;
    idx--;//move to the last char, because not sure the next char is blank or a vilid char
    return word
}

next_number {
    escape blank
    def num
    while str[idx] in number chars : num += str[idx] idx++;
    idx--;
    return num
}
```

```
parse_value {
    def pre = idx
    char c = next_char
    idx = pre   //still on :
    if c is number char : value = parse_number;
    else if c is " : value = parse_string;
    else if c is [ : value = parse_array;
    else if c is { : value = parse_object;
    else :
        string s = next_word
        idx = pre
        if s is "true" or "false" : value = parse_bool;
        else if s is "null" : value = parse_null;
        else : throw exception;
    else : throw exception;
}

parse_number {
    get next_number to num
    if find . in num : return parse_double num
    else if find char not in number chars or have more than one . : throw exception
    else : return parse_int num
}

parse_int {
    num to int
    def JSON_INT = num
    return JSON_INT
}

parse_double {
    num to double
    def JSON_DOUBLE = num
    return JSON_DOUBLE
}

parse_string {
    def str
    str = next_string
    def JSON_STRING = str
    return JSON_STRING
}

parse_bool {
    def str
    str = next_word
    def JSON_BOOL = false
    if str is "true" : JSON_BOOL = true
    return JSON_BOOL
}

parse_null {
    return JSON_NULL
}
```

```
parse_array {
    def JSON_ARRAY
    def c = next_char // move to [
    while (c is not ']') {
        JSON_ARRAY add parse_value
        c = next_char   // move to , or ]
        if (c is not , or ]) : throw exception
    }
    return JSON_ARRAY
}

parse_object {
    def JSON_OBJECT
    def c = next_char // move to {
    while (c is not '}') {
        JSON_OBJECT add next_pair
        c = next_char   // move to , or }
        if (c is not , or }) : throw exception
    }
    return JSON_OBJECT
}
```
## 测试策略

