#pragma once

#include "UIElement.h"
#include "Screen.h"
#include "Color.h"

namespace sw
{
    class Window : public UIElement
    {
    public:
        enum WindowState {
            Normal,    // ��ͨ����
            Minimized, // ��С������
            Maximized, // ��󻯴���
        };

        enum WindowStartupLocation {
            Manual,       // ʹ��ϵͳĬ�ϻ��ֶ�����
            CenterScreen, // ��Ļ����
        };

    private:
        bool _isFirstShow = true;
        Color _background = Color::White;

    public:
        /**
         * @brief �Ƿ��ڹر����д��ں��˳�����
         */
        static bool PostQuitWhenAllClosed;

        /**
         * @brief ����״̬
         */
        const Property<WindowState> State;

        /**
         * @brief �����Ƿ�ɵ�����С
         */
        const Property<bool> SizeBox;

        /**
         * @brief ��󻯰�ť�Ƿ����
         */
        const Property<bool> MaximizeBox;

        /**
         * @brief ��С����ť�Ƿ����
         */
        const Property<bool> MinimizeBox;

        /**
         * @brief �����Ƿ��ö�
         */
        const Property<bool> Topmost;

        /**
         * @brief �Ƿ���ʾΪToolWindow (խ�߿�)
         */
        const Property<bool> ToolWindow;

        /**
         * @brief ������ɫ
         */
        const Property<Color> Background;

        /**
         * @brief ���ڳ���������λ��
         */
        WindowStartupLocation StartupLocation = Manual;

    public:
        Window();

    private:
        bool GetStyle(LONG_PTR style);
        void SetStyle(LONG_PTR style, bool value);
        bool GetExtendedStyle(LONG_PTR style);
        void SetExtendedStyle(LONG_PTR style, bool value);

    protected:
        /**
         * @brief ��WndProc�ķ�װ
         */
        virtual LRESULT WndProc(const ProcMsg &refMsg);

        /**
         * @brief  ���յ�WM_CLOSEʱ���øú���
         * @return ���Ѵ������Ϣ�򷵻�true�����򷵻�false�Ե���DefWindowProcW
         */
        virtual bool OnClose();

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

    public:
        /**
         * @brief ��ʾ����
         */
        void Show();
    };
}
