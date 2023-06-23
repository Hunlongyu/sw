#pragma once

#include <string>
#include <Windows.h>
#include "Property.h"
#include "ProcMsg.h"
#include "Rect.h"
#include "App.h"
#include "Dpi.h"

namespace sw
{
    class WndBase
    {
    private:
        static LRESULT CALLBACK _WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    protected:
        static const PCWSTR WndBaseClassName;

        /**
         * @brief 该函数会调用DefWindowProcW
         */
        static LRESULT DefaultWndProc(const ProcMsg &refMsg);

    private:
        HWND _hwnd;
        sw::Rect _rect;
        std::wstring _text;

    public:
        const ReadOnlyProperty<HWND> Handle;
        const Property<sw::Rect> Rect;
        const Property<double> Left;
        const Property<double> Top;
        const Property<double> Width;
        const Property<double> Height;
        const ReadOnlyProperty<sw::Rect> ClientRect;
        const ReadOnlyProperty<double> ClientWidth;
        const ReadOnlyProperty<double> ClientHeight;
        const Property<bool> Enabled;
        const Property<bool> Visible;
        const Property<std::wstring> Text;

    protected:
        WndBase();

        /**
         * @brief 初始化WndBase，该函数会调用CreateWindowExW创建窗口
         */
        void InitWndBase(DWORD dwExStyle, LPCWSTR lpWindowName, DWORD dwStyle, HWND hWndParent, HMENU hMenu);

        /**
         * @brief 对WndProc的封装
         */
        virtual LRESULT WndProc(const ProcMsg &refMsg);

        /**
         * @brief  接收到WM_CREATE时调用该函数
         * @return 若已处理该消息则返回true，否则返回false以调用DefWindowProcW
         */
        virtual bool OnCreate();

        /**
         * @brief  接收到WM_DESTROY时调用该函数
         * @return 若已处理该消息则返回true，否则返回false以调用DefWindowProcW
         */
        virtual bool OnDestroy();

        /**
         * @brief  接收到WM_PAINT时调用该函数
         * @return 若已处理该消息则返回true，否则返回false以调用DefWindowProcW
         */
        virtual bool OnPaint();

        /**
         * @brief  接收到WM_MOVE时调用该函数
         * @return 若已处理该消息则返回true，否则返回false以调用DefWindowProcW
         */
        virtual bool OnMove(double newLeft, double newTop);

        /**
         * @brief  接收到WM_SIZE时调用该函数
         * @return 若已处理该消息则返回true，否则返回false以调用DefWindowProcW
         */
        virtual bool OnSize(double newClientWidth, double newClientHeight);

        /**
         * @brief         Text属性被赋值时调用此函数
         * @param newText Text的新值
         * @return        若要修改Text则返回true，否则返回false
         */
        virtual bool OnSetText(std::wstring &newText);

    public:
        void Show(int nCmdShow);
        void Close();
    };
}
