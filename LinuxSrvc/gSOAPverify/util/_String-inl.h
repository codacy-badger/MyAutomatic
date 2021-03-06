#ifdef _STRING_
#include <string>
//未使用STL的string类时
typedef std::string _String;

inline unsigned char* fix_strerr(unsigned char* str)
{
    for (int i = 0; i < (int)strlen((const char*)str); i++)
        switch (str[i])
        {
        case 0xcc:/*烫 未初始化*/
        case 0xCD:/*heapk(new)*/
        case 0xDD://已收回的堆(delete)
        case 0xFD://隔离（栅栏字节）字节 下标越界
        case 0xAB://Memory allocated by LocalAlloc()
        case 0xBAADF00D://    Memory allocated by LocalAlloc() with LMEM_FIXED,
                        //    but not yet written to.
        case 0xFEEEFEEE:/*  OS fill heap memory, which was marked for usage,\
                        but wasn't allocated by HeapAlloc() or LocalAlloc()\
                        Or that memory just has been freed by HeapFree().
                        */
            str[i] = '\0';
            break;
        default:break;
        }
    return str;
}
#else
#define __STRING_

#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#if (defined __linux ) || (defined sprintf_s)
#undef sprintf_s
#define sprintf_s sprintf
#endif // __linux

#define Conn(x,y) x##y
// #define ToChar(x) #@x
#define ToString(x) #x

using namespace std;

class _String {
    friend ostream& operator<<(ostream&, const _String&);
    friend istream& operator >> (istream&, _String&);
public:
    _String(const char* str = NULL);//赋值兼默认构造函数（char）
    _String(const _String& other);  //赋值构造函数（_String）
    _String& operator=(const _String& other);
    _String/*&*/ operator+(const _String& other);
    bool operator==(const _String&);
    char& operator[](unsigned int) const;
    char* _strcpy(char* strDest, const char* strSrc, int N = 1024);
    char* /*__cdecl*/_strcat(char * strDest, const char * strSrc);
    char* _itoa(int num, char *str, int radix);
    unsigned char* _strsub(unsigned char* ch, int pos, int len);
    int _strcut(unsigned char* str, char ch, char* str1, char* str2);
    size_t _strlen(const char* str);
    char* _strmove(char* w, int m, bool fore = false);
    char* _charmove(char* w, char c, int b, bool hind = false/*默认向左*/);
    char* _intmove(char* w, int m, int b, bool hind = false);
    int find_char(char **arr, char ch, int m = 1/*1st dim of arr*/);
    char* _op_order(char * src, char* dst);
    char* _op_order(char * str);
    char* _c_str() const;
    size_t size() {
        int len;
        for (len = 0; m_data[len] != '\0'; len++)
            /*if (m_data[len] = '\0')
            break*/;
        if (len == (sizeof(m_data) / sizeof(char*) + 1))
            return len;
        else
            return strlen(m_data);
    }
    ~_String(void) { delete[] m_data; }
private:
    char* m_data;
};
//inline执行时直接语句替换
inline _String::_String(const char* str)
{
    if (!str)
        m_data = 0;
    else {
        m_data = new char[strlen(str) + 1];
        _strcpy(m_data, str);
    }
}

inline _String::_String(const _String& other)
{//类的成员函数内可以访问同种对象的私有成员（同种类为友元关系的类）
    if (!other.m_data)
        m_data = 0;
    else
    {
        m_data = new char[strlen(other.m_data) + 1];
        _strcpy(m_data, other.m_data);
    }
}
//字符串拷贝
inline char* _String::_strcpy(char* strDest, const char* strSrc, int N)
{
    assert((strDest != NULL) && (strSrc != NULL));
    size_t available = N;
    char* strDestCopy = strDest;
    while ((*strDest++ = *strSrc++) != '\0' && --available > 0)
        N = (int)NULL;
    return strDestCopy; //返回字符串以支持链式表达式
}
//字符串拼接
inline char * /*__cdecl*/ _String::_strcat(char * strDest, const char * strSrc)
{
    if ((strDest == NULL) || (strSrc == NULL))
        throw "buffer is empty";
    char * cp = strDest;
    while (*cp)
        cp++; /* find end of strDest */
    while (bool((*cp++ = *strSrc++) != '\0')); /* Copy strSrc to end of strDest */
    return(strDest);
}
//从第pos位开始截取ch的len个字符。
inline unsigned char* _String::_strsub(unsigned char* ch, int pos, int len)
{
    //定义一个字符指针，指向传递进来的ch地址
    unsigned char* pch = ch;
    //通过calloc来分配一个len长度的字符数组，返回的是字符指针
    unsigned char* subch = (unsigned char*)calloc(sizeof(unsigned char), len + 1);
    int i;
    //只有在C99下for循环中才可以声明变量，这里写在外面，提高兼容性  
    pch = pch + pos;
    //是pch指针指向pos位置
    for (i = 0; i < len; i++)
    {//循环遍历赋值数组
        subch[i] = *(pch++);
    }
    //加上字符串结束符
    subch[len] = '\0';
    //返回分配的字符数组地址
    return subch;
    //该地址指向的内存必须在函数外释放(free)
}
//截取字符串str内字符ch左右两边的子串。
inline int _String::_strcut(unsigned char* str, char ch, char* str1, char* str2)
{
    char s1[16];
    char s2[16];
    unsigned int i = 0;
    for (i = 0; i < strlen((char*)str); i++)
        if (str[i] == ch)
            break;
    sprintf_s(s1, "%s", (char*)_strsub(str, 0, i));
    memcpy(str1, s1, strlen(s1) + 1);
    sprintf_s(s2, "%s", (char*)_strsub(str, i + 1, strlen((char*)str) + 1 - i));
    memcpy(str2, s2, strlen(s2) + 1);
    return i;
}
//计算字符个数（字符串长度）
inline size_t _String::_strlen(const char * str)
{
    if (str == NULL)
        throw "buffer is empty";
    const char* tmp = str;
    for (; *tmp != '\0'; ++tmp);
    return tmp - str;
}
//字符串整体向左移动
inline char* _String::_strmove(char* w, int m, bool fore)
{
    int i = 0, len = strlen(w);
    char s = *w;
    if (m > len)
        m = len;
    if (!fore)
    {
        while (w[m++] != '\0')
        {
            w[i++] = w[m - 1];
        }
        for (; i <= m; i++)
        {
            w[i] = s++;
        }
    }
    else
    {
        for (int t = 0; t < len - m; t++)
        {
            w[t + m] = s + t;
        }
        while (w[len - m + (i++)] != '\0')
        {
            w[i - 1] = s + len - m + i - 1;
        }
    }
    w[len] = '\0';
    return w;
}
/**
  * 单个字符的移动
  * 字符串 w
  * 移动的字符 c
  * 移动的位数 b
  * 移动的方向 hind(后)
  **/
inline char* _String::_charmove(char* w, char c, int b, bool hind)
{
    int i = 0;
    char s = *w;
    char* t = w;
    while (*t)
    {
        if (*t == c)
            break;
        ++t;
    }
    int m = c - s;
    if (hind)
    {
        (b > (int)_strlen(w) - m) ? (b = (int)_strlen(w) - m) : 0;
        for (i = 0; i < b; i++)
            w[m + i] = c + (i + 1);
        w[m + b] = c;
    }
    else
    {
        (b > m) ? (b = m) : 0;
        for (i = 0; i < b; i++)
            w[m - i] = c - (i + 1);
        w[m - b] = c;
    }
    return w;
}
// 单个字符的移动
// m: 字符位置
inline char* _String::_intmove(char* w, int m, int b, bool hind)
{
    int i = 0;
    m -= 1;
    if (hind)
    {
        (b > (int)_strlen(w) - m) ? (b = (int)_strlen(w) - m) : 0;
        for (i = 0; i < b; i++)
            w[m + i] = *w + m + (i + 1);
        w[m + b] = *w + m;
    }
    else
    {
        (b > m) ? (b = m) : 0;
        for (i = 0; i < b; i++)
            w[m - i] = *w + m - (i + 1);
        w[m - b] = *w + m;
    }
    return w;
}
// 返回字符串数组str含有的字符ch数; Usage:
/*
    char l[][16] = { "acvhhj", "222", "ccc" };
    int m = 3;
    char *a[16] = { NULL };
    for(int i = 0; i < m; i++)
        a[i] = l[i]; // (char*)[const char* point]
    int s = find_char(a, 'c', m);
*/
inline int _String::find_char(char **arr, char ch, int m)
{
    int i = 0;
    int num = 0;
    char *str = NULL;
    if(arr == NULL)
        return -1;
    while ((str = *arr++) != NULL)
    {
        if (i >= m)
            break;
        while (*str != '\0')
        {
            if (*str++ == ch)
            {
                num++;
            }
        }
        i++;
    }
    return num;
}

// 字符串逆序输出
inline char* _String::_op_order(char * src, char *cst)
{
    int len = strlen(src);
    char* dest = (char*)malloc(len + 1);//为\0分配一个空间
    char *d = dest;
    char* s = &src[len - 1];//指向最后一个字符
    while (len-- != 0)
        *d++ = *s--;
    *d = 0;//尾部加\0
    _strcpy(cst, dest);
    assert(dest);
    free(dest);//释放空间
    return cst;
}

inline char* _String::_op_order(char * str)
{
    int len = strlen(str);
    char t;
    for (int i = 0; i < len / 2; i++)
    {
        t = str[i];
        str[i] = str[len - i - 1]; str[len - i - 1] = t;
    }
    return str;
}

inline char* _String::_itoa(int num, char *str, int radix)
{
    if (num == 0)
    {
        str[0] = '0'; str[1] = '\0';
        return str;
    }
    char  string[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char* ptr = str;
    int i; int j;
    int value = num;
    if (num < 0) num = -num;
    while (num >= radix)
    {
        *ptr++ = string[num % radix];
        num /= radix;
    }
    if (num)
    {
        *ptr++ = string[num];
        *ptr = '\0';
    }
    int n = j = ptr - str - 1;
    for (i = 0; i < (ptr - str) / 2; i++)
    {
        int temp = str[i]; str[i] = str[j]; str[j--] = temp;
    }
    if (value < 0)
    {
        for (j = n; j >= 0; --j) str[j + 1] = str[j];
        str[0] = '-';
    }
    str[n + 2] = '\0';
    return str;
}

inline char* _String::_c_str() const
{
    return m_data;
}

inline _String & _String::operator=(const _String & other)
{
    if (this != &other)
    {
        delete[] m_data;
        if (!other.m_data)
            m_data = 0;
        else
        {
            m_data = new char[strlen(other.m_data) + 1];
            _strcpy(m_data, other.m_data);
        }
    }
    return *this;
}

inline _String /*&*/ _String::operator+(const _String & other)
{
    _String newstring;
    if (!other.m_data)
        newstring = *this;
    else if (!m_data)
        newstring = other;
    else
    {
        newstring.m_data = new char[strlen(m_data) + strlen(other.m_data) + 1];
        newstring._strcpy(newstring.m_data, m_data);
        newstring._strcat(newstring.m_data, other.m_data);
    }//内联函数不该返回局部变量的引用
    return newstring;
}

inline bool _String::operator==(const _String& s)
{
    if (strlen(s.m_data) != strlen(m_data))
        return false;
    return strcmp(m_data, s.m_data) ? false : true;
}

inline char & _String::operator[](unsigned int e) const
{
    if (e >= 0 && e <= strlen(m_data))
        return m_data[e];
}
inline ostream & operator<<(ostream& os, const _String& str)
{
    os << str.m_data;
    return os;
}
inline istream & operator >> (istream &input, _String &s)
{
    char temp[255];//存储输入流
    input >> setw(255) >> temp;
    s = temp;//赋值
    return input;//支持连续使用>>运算符
}
#endif
