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
        /**
         * @brief ���ڹ��̺��������ö����WndProc
         */
        static LRESULT CALLBACK _WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

    protected:
        /**
         * @brief �ú��������DefWindowProcW
         */
        static LRESULT DefaultWndProc(const ProcMsg &refMsg);

    private:
        HWND _hwnd;
        sw::Rect _rect;
        std::wstring _text;

    public:
        /**
         * @brief ���ھ��
         */
        const ReadOnlyProperty<HWND> Handle;

        /**
         * @brief λ�úͳߴ�
         */
        const Property<sw::Rect> Rect;

        /**
         * @brief ���
         */
        const Property<double> Left;

        /**
         * @brief ����
         */
        const Property<double> Top;

        /**
         * @brief ���
         */
        const Property<double> Width;

        /**
         * @brief �߶�
         */
        const Property<double> Height;

        /**
         * @brief �û����ߴ�
         */
        const ReadOnlyProperty<sw::Rect> ClientRect;

        /**
         * @brief �û������
         */
        const ReadOnlyProperty<double> ClientWidth;

        /**
         * @brief �û����߶�
         */
        const ReadOnlyProperty<double> ClientHeight;

        /**
         * @brief ���ڻ�ؼ��Ƿ����
         */
        const Property<bool> Enabled;

        /**
         * @brief ���ڻ�ؼ��Ƿ�ɼ�
         */
        const Property<bool> Visible;

        /**
         * @brief ���ڱ����ؼ��ı�
         */
        const Property<std::wstring> Text;

        /**
         * @brief ������
         */
        const Property<WndBase *> Parent;

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
         * @brief  ���յ�WM_CLOSEʱ���øú���
         * @return ���Ѵ������Ϣ�򷵻�true�����򷵻�false�Ե���DefWindowProcW
         */
        virtual bool OnClose();

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
        /**
         * @brief �ú�������ShowWindow
         */
        void Show(int nCmdShow);

        /**
         * @brief ���͹ر���Ϣ
         */
        void Close();

        /**
         * @brief �ú�������UpdateWindow
         */
        void Update();
    };
}
