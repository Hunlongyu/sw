#pragma once

#include "AbsoluteLayout.h"
#include "Color.h"
#include "LayoutHost.h"
#include "Screen.h"
#include "UIElement.h"

namespace sw
{
    class Window : public UIElement
    {
    public:
        enum WindowState {
            Normal,    // 普通窗口
            Minimized, // 最小化窗口
            Maximized, // 最大化窗口
        };

        enum WindowStartupLocation {
            Manual,       // 使用系统默认或手动设置
            CenterScreen, // 屏幕中心
        };

    private:
        bool _isFirstShow             = true;
        Color _background             = Color::White;
        double _maxWidth              = -1;
        double _maxHeight             = -1;
        double _minWidth              = -1;
        double _minHeight             = -1;
        bool _layoutDisabled          = false;
        LayoutHost *_layout           = nullptr;
        AbsoluteLayout _defaultLayout = AbsoluteLayout();

    public:
        /**
         * @brief 是否在关闭所有窗口后退出程序
         */
        static bool PostQuitWhenAllClosed;

        /**
         * @brief 窗口状态
         */
        const Property<WindowState> State;

        /**
         * @brief 窗口是否可调整大小
         */
        const Property<bool> SizeBox;

        /**
         * @brief 最大化按钮是否可用
         */
        const Property<bool> MaximizeBox;

        /**
         * @brief 最小化按钮是否可用
         */
        const Property<bool> MinimizeBox;

        /**
         * @brief 窗口是否置顶
         */
        const Property<bool> Topmost;

        /**
         * @brief 是否显示为ToolWindow (窄边框)
         */
        const Property<bool> ToolWindow;

        /**
         * @brief 背景颜色
         */
        const Property<Color> Background;

        /**
         * @brief 最大宽度，当值不大于0时表示不限制
         */
        const Property<double> MaxWidth;

        /**
         * @brief 最大高度，当值不大于0时表示不限制
         */
        const Property<double> MaxHeight;

        /**
         * @brief 最小宽度，当值不大于0时表示不限制
         */
        const Property<double> MinWidth;

        /**
         * @brief 最小高度，当值不大于0时表示不限制
         */
        const Property<double> MinHeight;

        /**
         * @brief 窗口布局方式
         */
        const Property<LayoutHost *> Layout;

        /**
         * @brief 窗口初次启动的位置
         */
        WindowStartupLocation StartupLocation = Manual;

    public:
        Window();

    protected:
        /**
         * @brief 对WndProc的封装
         */
        virtual LRESULT WndProc(const ProcMsg &refMsg);

        /**
         * @brief  接收到WM_CLOSE时调用该函数
         * @return 若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnClose();

        /**
         * @brief  接收到WM_CREATE时调用该函数
         * @return 若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnCreate();

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
         * @brief               测量控件所需尺寸
         * @param availableSize 可用的尺寸
         */
        virtual void Measure(const Size &availableSize);

        /**
         * @brief           安排控件位置
         * @param finalSize 最终控件所安排的位置
         */
        virtual void Arrange(const sw::Rect &finalPosition);

        /**
         * @brief 获取Layout，若Layout为空则返回默认Layout
         */
        LayoutHost &GetLayoutHost();

        /**
         * @brief 更新布局
         */
        void UpdateLayout();

    public:
        /**
         * @brief 显示窗口
         */
        void Show();

        /**
         * @brief 禁用布局
         */
        void DisableLayout();

        /**
         * @brief 启用布局
         */
        void EnableLayout();
    };
}
