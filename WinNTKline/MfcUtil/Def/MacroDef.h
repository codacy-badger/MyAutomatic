#ifndef SET_MACRO_H_
#define SET_MACRO_H_

#define _PI_ 3.1415926535897932384626433832795

#define WM_MSG_OGL	WM_USER + 0x001
#define WM_MSG_SHOW WM_USER + 0x010
#define WM_MSG_LIST WM_USER + 0x011
#define WM_MSG_MENU WM_USER + 0x100
#define WM_MSG_BKG	WM_USER + 0x101
#define WM_MSG_DEP	WM_USER + 0x110
#define WM_MSG_QUIT	WM_USER + 0x111
#define WM_MSG_BOX	WM_USER	+ 0x1000
#define WM_MSG_TITL WM_USER + 0x1001
#define WM_MSG_NAVIURL	WM_USER + 0x1010

#define fixpixely 0.0035277777777778	//1.27/360

#if 0
#if !defined(nullptr)
#if __cplusplus <= 199711L
#error "Should use --std=c++11 option for compile."
const class nullptr_t
{
public:
    template<class T>
    inline operator T*() const
    {
        return 0;
    }
    template<class C, class T>
    inline operator T C::*() const
    {
        return 0;
    }
private:
    void operator&() const;
public:
    nullptr_t *null;
#undef NULL
#define NULL null
};
#endif
#endif
#endif

#endif // !SET_MACRO_H_
