#include <cmath>
#include <cstdio>
#include <iostream>
#include <utility>
#include <vector>


const float c_15 = 1.5F;

float qsqrt(float p_src)
{   
    float y = p_src;
    long i = *(long *)&y;
    i = 0x5f3759df - (i >> 1);
    //printf("%x\n", i);
    //i = 0x5f375a86 - (i >> 1);
    y = *(float *)&i;
    y = y*(c_15 - 0.5F * p_src * y * y);
    return (float)1/y;
}


float qsqrt2(float p_src)
{
    float y = p_src;
    long i = *(long *)&y;
    i = 0x1fbd1df5 + (i >> 1);
    y = *(float *)&i;
    y = 0.5F*(y + p_src / y);
    return y;
}


void process_value(const int& p_val)
{
    std::cout << "const LValue reference processed: " << p_val << std::endl;
}


void process_value(const int&& p_val)
{
    std::cout << "const RValue reference processed: " << p_val << std::endl;
}


void process_value(int& p_val)
{
    std::cout << "LValue reference processed: " << p_val << std::endl;
}


void process_value(int&& p_val)
{
    std::cout << "RValue reference processed: " << p_val << std::endl;
}


template<typename T>
void forward_value(T&& p_val)
{
    process_value(p_val);
}


template<typename T>
void forward_value_original(T val)
{
    process_value(val);
}


template<class T1, class T2>
void print_is_same() {
    std::cout << std::is_same<T1, T2>() << '\n';
}


class MyString 
{
private:
    char* _data;
    size_t _len;
    void _init_data(const char *p_src) 
    {
        _data = (char *)malloc(sizeof(char)*(_len + 1));
        memcpy(_data, p_src, _len);
        _data[_len] = '\0';
    }

public:
    MyString() 
    {
        _data = NULL;
        _len = 0;
    }

    MyString(const char* p) 
    {
        _len = strlen(p);
        _init_data(p);
        std::cout << "Constructor is called!" << std::endl 
            << "origin: " << (int)_data << std::endl
            << "content: " << _data << std::endl;
    }

    MyString(const MyString& str) 
    {
        _len = str._len;
        _init_data(str._data);
        std::cout << "Copy Constructor is called!" << std::endl
            << "src: " << (int)str._data << std::endl
            << "des: " << (int)_data << std::endl
            << "content: " << _data << std::endl;
    }

    MyString(MyString&& str)
    {
        _len = str._len;
        _data = str._data;
        str._len = 0;
        std::cout << "Move Constructor is called!" << std::endl
            << "src: " << (int)str._data << std::endl
            << "des: " << (int)_data << std::endl
            << "content: " << _data << std::endl;
        str._data = NULL;
    }

    MyString& operator=(const MyString& str)
    {
        if (this != &str) 
        {
            _len = str._len;
            _init_data(str._data);
            std::cout << "Copy Assignment is called!" << std::endl
                << "src: " << (int)str._data << std::endl
                << "des: " << (int)_data << std::endl
                << "content: " << _data << std::endl;
        }
        return *this;
    }

    MyString& operator=(MyString&& str)
    {
        if (this != &str)
        {
            _len = str._len;
            _data = str._data;
            str._len = 0;
            std::cout << "Move Assignment is called!" << std::endl 
                << "src: " << (int)str._data << std::endl
                << "des: " << (int)_data << std::endl
                << "content: " << _data << std::endl;
            str._data = NULL;
        }
        return *this;
    }

    virtual ~MyString() 
    {
        if (_data)
        {
            free(_data);
            _data = NULL;
        }
        std::cout << "Destructor is called." << std::endl;
    }
};


int main()
{
    /*for (int i = 1; i <= 10; ++i)
    {
        std::cout << qsqrt((float)i) << std::endl;
        std::cout << qsqrt2((float)i) << std::endl;
    }*/
    int var = 1;
    const int con = 2;
    process_value(var);
    process_value(std::move(var));
    process_value(con);
    process_value(std::move(con));
    forward_value(var);
    forward_value(std::move(var));
    forward_value(con);
    forward_value(std::move(con));
    forward_value_original(var);
    forward_value_original(std::move(var));
    forward_value_original(con);
    forward_value_original(std::move(con));

    int lval = 7;              // lvalue.
    int& lref = lval;          // lvalue ref. could bind to either a lvalue or a rvalue.
    int&& rref = 2;            // rvalue ref. could only bind to a rvalue.
    const int clval = 3;       // const lvalue.
    const int& clref = clval;  // no means. ref basically cannot change.
    const int&& crref = 2;      // no means. ref basically cannot change.


    const int& cilr0 = lref;   // bind a const int& to a const int& lvalue.
    const int& cilr1 = clref;  // bind a cosnt int& to a int& lvalue.
    const int& cilr2 = std::move(rref);   // bind a cosnt int& to a int& rvalue.
    const int& cilr3 = std::move(crref);  // bind a cosnt int& to a int& lvalue.
    const int& cilr4 = 7;      // bind a const int& to a const int rvalue.
    const int& cilr5 = lval;   // bind a const int& to a int lvalue.
    const int& cilr6 = clval;  // bind a const int& to a const int lvalue.

    int& ilr0 = lref;         // bind a int& to a int& lvalue.
    // int& ilr1 = clref;     // cannot bind a int& to a const int& lvalue.
    // int& ilr2 = std::move(rref); 
    // int& ilr3 = std::move(crref); 
    // int& ilr4 = 7;         // cannot bind a int& to a const int rvalue.
    int& ilr5 = lval;         // bind a int& to a int lvalue.
    // int& ilr4 = clval;     // cannot bind a int& to a const int lvalue.

    // const int&& cirr0 = lref;   // cannot bind a const int&& to a int& lvalue.
    // const int&& cirr1 = clref;  // cannot bind a const int&& to a const int& lvalue.
    const int&& cirr2 = std::move(rref);   // 
    const int&& cirr3 = std::move(crref);  // 
    const int&& cirr4 = 7;
    // const int&& cirr5 = lval;   // cannot bind a const int&& to a int lvalue.
    // const int&& cirr6 = clval;  // cannot bind a const int&& to a const int lvalue.

    // const int&& irr0 = lref;   // cannot bind a int&& to a int& lvalue.
    // const int&& irr1 = clref;  // cannot bind a int&& to a const int& lvalue.
    int&& irr2 = std::move(rref);   // 
    // int&& cirr3 = std::move(crref);  // 
    int&& irr4 = 7;
    // const int&& irr5 = lval;   // cannot bind a int&& to a int lvalue.
    // const int&& irr6 = clval;  // cannot bind a int&& to a const int lvalue.

    std::cout << std::boolalpha;

    print_is_same<int, int>();    // true
    print_is_same<int, int &>();  // false
    print_is_same<int, int &&>(); // false

    print_is_same<int, std::remove_reference<int>::type>();    // true
    print_is_same<int, std::remove_reference<int &>::type>();  // true
    print_is_same<int, std::remove_reference<int &&>::type>(); // true

    std::cout << std::is_reference<int>::value << '\n';
    std::cout << std::is_reference<int&>::value << '\n';
    std::cout << std::is_reference<int&&>::value << '\n';

    std::cout << std::is_lvalue_reference<int>::value << '\n';
    std::cout << std::is_lvalue_reference<int&>::value << '\n';
    std::cout << std::is_lvalue_reference<int&&>::value << '\n';

    std::cout << std::is_rvalue_reference<int>::value << '\n';
    std::cout << std::is_rvalue_reference<int&>::value << '\n';
    std::cout << std::is_rvalue_reference<int&&>::value << '\n';

    MyString myString = MyString("Hello World 1");
    std::vector<MyString> vec;
    vec.push_back(MyString("Hello World 2"));
    std::cout << vec.capacity() << std::endl;
    vec.push_back(std::move(MyString("Hello World 3")));
    std::cout << vec.capacity() << std::endl;
    // vector capacity changes, so it will call an extra move copy function.
    MyString myString1;
    myString1 = myString;
    MyString myString2;
    myString2 = std::move(myString);

    int arr[5] = { 1 };
    int n = *(&arr + 1) - arr;
    std::cout << n << std::endl;
    return 0;
}