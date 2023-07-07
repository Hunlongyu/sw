#pragma once

#include "App.h"
#include "Dip.h"
#include "Font.h"
#include "ICtlColor.h"
#include "Point.h"
#include "ProcMsg.h"
#include "Property.h"
#include "Rect.h"
#include "WndMsg.h"
#include <Windows.h>
#include <string>

namespace sw
{
    class WndBase
    {
    private:
        /**
         * @brief 窗口过程函数，调用对象的WndProc
         */
        static LRESULT CALLBACK _WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    private:
        /**
         * @brief 窗口句柄
         */
        HWND _hwnd = NULL;

        /**
         * @brief 字体句柄
         */
        HFONT _hfont = NULL;

        /**
         * @brief 字体信息
         */
        sw::Font _font;

        /**
         * @brief 窗口的位置和尺寸
         */
        sw::Rect _rect = sw::Rect();

        /**
         * @brief 窗口标题或文本
         */
        std::wstring _text = L"";

        /**
         * @brief 当前对象是控件时该函数指针指向控件原本的WndProc
         */
        WNDPROC _controlOldWndProc = NULL;

    public:
        /**
         * @brief 窗口句柄
         */
        const ReadOnlyProperty<HWND> Handle;

        /**
         * @brief 字体
         */
        const Property<sw::Font> Font;

        /**
         * @brief 字体名称
         */
        const Property<std::wstring> FontName;

        /**
         * @brief 字体大小
         */
        const Property<double> FontSize;

        /**
         * @brief 字体粗细
         */
        const Property<sw::FontWeight> FontWeight;

        /**
         * @brief 位置和尺寸
         */
        const Property<sw::Rect> Rect;

        /**
         * @brief 左边
         */
        const Property<double> Left;

        /**
         * @brief 顶边
         */
        const Property<double> Top;

        /**
         * @brief 宽度
         */
        const Property<double> Width;

        /**
         * @brief 高度
         */
        const Property<double> Height;

        /**
         * @brief 用户区尺寸
         */
        const ReadOnlyProperty<sw::Rect> ClientRect;

        /**
         * @brief 用户区宽度
         */
        const ReadOnlyProperty<double> ClientWidth;

        /**
         * @brief 用户区高度
         */
        const ReadOnlyProperty<double> ClientHeight;

        /**
         * @brief 窗口或控件是否可用
         */
        const Property<bool> Enabled;

        /**
         * @brief 窗口或控件是否可见
         */
        const Property<bool> Visible;

        /**
         * @brief 窗口标题或控件文本
         */
        const Property<std::wstring> Text;

        /**
         * @brief 父窗口
         */
        const ReadOnlyProperty<WndBase *> Parent;

    protected:
        WndBase();
        ~WndBase();

        WndBase(const WndBase &)            = delete; // 删除拷贝构造函数
        WndBase(WndBase &&)                 = delete; // 删除移动构造函数
        WndBase &operator=(const WndBase &) = delete; // 删除拷贝赋值运算符
        WndBase &operator=(WndBase &&)      = delete; // 删除移动赋值运算符

        /**
         * @brief 初始化为窗口，该函数会调用CreateWindowExW
         */
        void InitWindow(LPCWSTR lpWindowName, DWORD dwStyle, HWND hWndParent, HMENU hMenu);

        /**
         * @brief 初始化为控件，该函数会调用CreateWindowExW
         */
        void InitControl(LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle);

        /**
         * @brief 更新字体
         */
        void UpdateFont();

        /**
         * @brief 获取窗口样式
         */
        LONG_PTR GetStyle();

        /**
         * @brief 设置窗口样式
         */
        void SetStyle(LONG_PTR style);

        /**
         * @brief 获取窗口的某个样式
         */
        bool GetStyle(LONG_PTR style);

        /**
         * @brief 设置窗口的某个样式
         */
        void SetStyle(LONG_PTR style, bool value);

        /**
         * @brief 获取扩展窗口样式
         */
        LONG_PTR GetExtendedStyle();

        /**
         * @brief 设置扩展窗口样式
         */
        void SetExtendedStyle(LONG_PTR style);

        /**
         * @brief 获取窗口的某个扩展样式
         */
        bool GetExtendedStyle(LONG_PTR style);

        /**
         * @brief 设置窗口的某个扩展样式
         */
        void SetExtendedStyle(LONG_PTR style, bool value);

        /**
         * @brief 调用默认的WndProc，对于窗口则调用DefWindowProcW，控件则调用_controlOldWndProc
         */
        LRESULT DefaultWndProc(const ProcMsg &refMsg);

        /**
         * @brief 对WndProc的封装
         */
        virtual LRESULT WndProc(const ProcMsg &refMsg);

        /**
         * @brief  接收到WM_CREATE时调用该函数
         * @return 若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnCreate();

        /**
         * @brief  接收到WM_CLOSE时调用该函数
         * @return 若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnClose();

        /**
         * @brief  接收到WM_DESTROY时调用该函数
         * @return 若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnDestroy();

        /**
         * @brief  接收到WM_PAINT时调用该函数
         * @return 若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnPaint();

        /**
         * @brief  接收到WM_MOVE时调用该函数
         * @return 若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnMove(double newLeft, double newTop);

        /**
         * @brief  接收到WM_SIZE时调用该函数
         * @return 若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnSize(double newClientWidth, double newClientHeight);

        /**
         * @brief         Text属性被赋值时调用此函数
         * @param newText Text的新值
         * @return        若要修改Text则返回true，否则返回false
         */
        virtual bool OnSetText(std::wstring &newText);

        /**
         * @brief Visible属性改变时调用此函数
         */
        virtual void VisibleChanged(bool newVisible);

        /**
         * @brief  设置父窗口
         * @return 设置是否成功
         */
        virtual bool SetParent(WndBase *parent);

        /**
         * @brief           父窗口改变时调用此函数
         * @param newParent 新的父窗口
         */
        virtual void ParentChanged(WndBase *newParent);

        /**
         * @brief      接收到WM_ParentReceivedCommand消息时调用此函数
         * @param code 通知代码
         */
        virtual void ParentReceivedCommand(int code);

    public:
        /**
         * @brief 该函数调用ShowWindow
         */
        void Show(int nCmdShow);

        /**
         * @brief 发送关闭消息
         */
        void Close();

        /**
         * @brief 该函数调用UpdateWindow
         */
        void Update();

        /**
         * @brief 重画
         */
        void Redraw();

        /**
         * @brief 判断当前对象是否是控件
         */
        bool IsControl();

        /**
         * @brief 将窗口置于 Z 顺序的顶部
         */
        void MoveToTop();

        /**
         * @brief 将窗口置于 Z 顺序的底部
         */
        void MoveToBottom();

        /**
         * @brief       获取用户区点在屏幕上点的位置
         * @param point 用户区坐标
         * @return      该点在屏幕上的坐标
         */
        Point PointToScreen(const Point &point);

        /**
         * @brief             获取屏幕上点在当前用户区点的位置
         * @param screenPoint 屏幕上点的坐标
         * @return            该点在用户区的坐标
         */
        Point PointFromScreen(const Point &screenPoint);

        /**
         * @brief      通过窗口句柄获取WndBase
         * @param hwnd 窗口句柄
         * @return     若函数成功则返回对象的指针，否则返回nullptr
         */
        static WndBase *GetWndBase(HWND hwnd);
    };
}
