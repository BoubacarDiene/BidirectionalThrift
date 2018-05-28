namespace cpp generated.shared

typedef string Text

enum MyEnum {
    VAL1 = 1,
    VAL2 = 2
}

struct Request {
    1: required i32 sleepTime,
    2: optional MyEnum myEnum
}

struct Result {
    1: required Text value
}
