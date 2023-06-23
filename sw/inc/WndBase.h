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
         * @brief �ú��������DefWindowProcW
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
         * @brief ��ʼ��WndBase���ú��������CreateWindowExW��������
         */
        void InitWndBase(DWORD dwExStyle, LPCWSTR lpWindowName, DWORD dwStyle, HWND hWndParent, HMENU hMenu);

        /**
         * @brief ��WndProc�ķ�װ
         */
        virtual LRESULT WndProc(const ProcMsg &refMsg);

        /**
         * @brief  ���յ�WM_CREATEʱ���øú���
         * @return ���Ѵ������Ϣ�򷵻�true�����򷵻�false�Ե���DefWindowProcW
         */
        virtual bool OnCreate();

        /**
         * @brief  ���յ�WM_DESTROYʱ���øú���
         * @return ���Ѵ������Ϣ�򷵻�true�����򷵻�false�Ե���DefWindowProcW
         */
        virtual bool OnDestroy();

        /**
         * @brief  ���յ�WM_PAINTʱ���øú���
         * @return ���Ѵ������Ϣ�򷵻�true�����򷵻�false�Ե���DefWindowProcW
         */
        virtual bool OnPaint();

        /**
         * @brief  ���յ�WM_MOVEʱ���øú���
         * @return ���Ѵ������Ϣ�򷵻�true�����򷵻�false�Ե���DefWindowProcW
         */
        virtual bool OnMove(double newLeft, double newTop);

        /**
         * @brief  ���յ�WM_SIZEʱ���øú���
         * @return ���Ѵ������Ϣ�򷵻�true�����򷵻�false�Ե���DefWindowProcW
         */
        virtual bool OnSize(double newClientWidth, double newClientHeight);

        /**
         * @brief         Text���Ա���ֵʱ���ô˺���
         * @param newText Text����ֵ
         * @return        ��Ҫ�޸�Text�򷵻�true�����򷵻�false
         */
        virtual bool OnSetText(std::wstring &newText);

    public:
        void Show(int nCmdShow);
        void Close();
    };
}
