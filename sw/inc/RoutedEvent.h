#pragma once

#include <cstdint>
#include <functional>

namespace sw
{
    /**
     * @brief 路由事件类型枚举
     */
    enum RoutedEventType : uint32_t {
        UserEventBegin = 0,
        UserEventEnd   = 0x80000000,

        /**
         * @brief 尺寸改变，参数类型为sw::SizeChangedEventArgs
         */
        UIElement_SizeChanged,

        /**
         * @brief 位置改变，参数类型为sw::PositionChangedEventArgs
         */
        UIElement_PositionChanged,

        /**
         * @brief Text属性发生变化，参数类型为sw::TextChangedEventArgs
         */
        UIElement_TextChanged,

        /**
         * @brief 获取到焦点，参数类型为sw::RoutedEventArgs
         */
        UIElement_GotFocus,

        /**
         * @brief 失去焦点，参数类型为sw::RoutedEventArgs
         */
        UIElement_LostFocus,

        /**
         * @brief 窗口正在关闭，参数类型为sw::WindowClosingEventArgs
         */
        Window_Closing,

        /**
         * @brief 窗口已关闭，参数类型为sw::RoutedEventArgs
         */
        Window_Closed,

        /**
         * @brief 按钮被单击，参数类型为sw::RoutedEventArgs
         */
        ButtonBase_Clicked,

        /**
         * @brief 按钮被双击，参数类型为sw::RoutedEventArgs
         */
        ButtonBase_DoubleClicked,
    };

    /*================================================================================*/

    /**
     * @brief 路由事件的参数
     */
    struct RoutedEventArgs {
        /**
         * @brief 事件类型
         */
        RoutedEventType eventType;

        /**
         * @brief 事件是否已被处理，若将此字段设为true，则事件不会继续往上传递
         */
        bool handled = false;

        /**
         * @brief RoutedEventArgs构造函数
         */
        RoutedEventArgs(RoutedEventType eventType);
    };

    class UIElement; // UIElement.h
    /**
     * @brief 路由事件类型
     */
    typedef std::function<void(UIElement &, RoutedEventArgs &)> RoutedEvent;
}
