#pragma once

#include "Alignment.h"
#include "ILayout.h"
#include "RoutedEvent.h"
#include "RoutedEventArgs.h"
#include "Thickness.h"
#include "WndBase.h"
#include "WndMsg.h"
#include <map>
#include <string>
#include <vector>

namespace sw
{
    class UIElement : public WndBase, public ILayout
    {
    private:
        /**
         * @brief 是否正在Arrange，当该字段为true时调用NotifyLayoutUpdated函数不会触发WM_UpdateLayout消息
         */
        bool _arranging = false;

        /**
         * @brief 是否在不可见时不参与布局
         */
        bool _collapseWhenHide = true;

        /**
         * @brief 当前元素所需要占用的尺寸
         */
        Size _desireSize = Size();

        /**
         * @brief 当对齐方式为拉伸时用该字段存储原始大小
         */
        Size _origionalSize = Size();

        /**
         * @brief 边距
         */
        Thickness _margin = Thickness();

        /**
         * @brief 水平对齐方式
         */
        HorizontalAlignment _horizontalAlignment = HorizontalAlignment::Center;

        /**
         * @brief 垂直对齐方式
         */
        VerticalAlignment _verticalAlignment = VerticalAlignment::Center;

        /**
         * @brief 指向父元素的指针，在调用SetParent后会更新该值
         */
        UIElement *_parent = nullptr;

        /**
         * @brief 所有子窗口
         */
        std::vector<UIElement *> _children{};

        /**
         * @brief 参与布局的子窗口，在调用GetChildLayoutCount后会更新，不可见且CollapseWhenHide为true的控件会被忽略
         */
        std::vector<UIElement *> _childrenNotCollapsed{};

        /**
         * @brief 记录路由事件的map
         */
        std::map<RoutedEventType, RoutedEvent> _eventMap{};

    public:
        /**
         * @brief 描述
         */
        std::wstring Description = L"";

        /**
         * @brief 边距
         */
        const Property<Thickness> Margin;

        /**
         * @brief 水平对齐方式
         */
        const Property<HorizontalAlignment> HorizontalAlignment;

        /**
         * @brief 垂直对齐方式
         */
        const Property<VerticalAlignment> VerticalAlignment;

        /**
         * @brief 子控件数量
         */
        const ReadOnlyProperty<int> ChildCount;

        /**
         * @brief 是否在不可见时不参与布局
         */
        const Property<bool> CollapseWhenHide;

        /**
         * @brief 指向父元素的指针，当前元素为顶级窗口时该值为nullptr
         */
        const ReadOnlyProperty<UIElement *> Parent;

    public:
        UIElement();
        ~UIElement();

        /**
         * @brief           注册路由事件处理函数，当事件已注册时会覆盖已注册的函数
         * @param eventType 路由事件类型
         * @param event     处理函数，当值为nullptr时可取消注册
         */
        void RegisterRoutedEvent(RoutedEventType eventType, const RoutedEvent &event);

        /**
         * @brief           取消对应类型路由事件的注册
         * @param eventType 路由事件类型
         */
        void UnregisterRoutedEvent(RoutedEventType eventType);

        /**
         * @brief           判断路由事件是否已被注册
         * @param eventType 路由事件类型
         */
        bool IsRoutedEventRegistered(RoutedEventType eventType);

        /**
         * @brief  添加子控件
         * @return 添加是否成功
         */
        bool AddChild(UIElement *element);

        /**
         * @brief  添加子控件
         * @return 添加是否成功
         */
        bool AddChild(UIElement &element);

        /**
         * @brief  移除子控件
         * @return 移除是否成功
         */
        bool RemoveChild(UIElement *element);

        /**
         * @brief  移除子控件
         * @return 移除是否成功
         */
        bool RemoveChild(UIElement &element);

        /**
         * @brief 移除所有子控件
         */
        void Clear();

        /**
         * @brief         获取指定元素的索引
         * @param element 要查找的元素
         * @return        若找到指定元素则返回对应的索引，否则返回-1
         */
        int IndexOf(UIElement *element);

        /**
         * @brief         获取指定元素的索引
         * @param element 要查找的元素
         * @return        若找到指定元素则返回对应的索引，否则返回-1
         */
        int IndexOf(UIElement &element);

        /**
         * @brief 通过索引获取子控件
         */
        UIElement &operator[](int index) const;

        /**
         * @brief 获取参与布局的子控件数量
         */
        virtual int GetChildLayoutCount() override;

        /**
         * @brief 获取对应索引处的子控件，使用此函数前必须先调用GetChildLayoutCount
         */
        virtual ILayout &GetChildLayoutAt(int index) override;

        /**
         * @brief 获取控件所需尺寸
         */
        virtual Size GetDesireSize() override;

        /**
         * @brief 设置当前控件所需的尺寸
         */
        virtual void SetDesireSize(const Size &size) override;

        /**
         * @brief               测量控件所需尺寸
         * @param availableSize 可用的尺寸
         */
        virtual void Measure(const Size &availableSize) override;

        /**
         * @brief           安排控件位置
         * @param finalSize 最终控件所安排的位置
         */
        virtual void Arrange(const sw::Rect &finalPosition) override;

    protected:
        /**
         * @brief           触发路由事件
         * @param eventType 事件类型
         */
        void RaiseRoutedEvent(RoutedEventType eventType);

        /**
         * @brief           触发路由事件
         * @param eventArgs 要触发事件的事件参数
         */
        void RaiseRoutedEvent(RoutedEventArgs &eventArgs);

        /**
         * @brief 获取顶级窗口
         */
        UIElement &GetRootElement();

        /**
         * @brief 判断当前对象是否为顶级窗口
         */
        bool IsRootElement();

        /**
         * @brief 通知顶级窗口布局改变
         */
        void NotifyLayoutUpdated();

        /**
         * @brief  设置父窗口
         * @return 设置是否成功
         */
        virtual bool SetParent(WndBase *parent) override;

        /**
         * @brief           父窗口改变时调用此函数
         * @param newParent 新的父窗口
         */
        virtual void ParentChanged(WndBase *newParent) override;

        /**
         * @brief  接收到WM_CLOSE时调用该函数
         * @return 若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnClose() override;

        /**
         * @brief                   接收到WM_MOVE时调用该函数
         * @param newClientPosition 移动后用户区左上角的位置
         * @return                  若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnMove(Point newClientPosition) override;

        /**
         * @brief               接收到WM_SIZE时调用该函数
         * @param newClientSize 改变后的用户区尺寸
         * @return              若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnSize(Size newClientSize) override;

        /**
         * @brief         Text属性更改时调用此函数
         * @param newText Text的新值
         */
        virtual void OnTextChanged(const std::wstring &newText) override;

        /**
         * @brief Visible属性改变时调用此函数
         */
        virtual void VisibleChanged(bool newVisible) override;

        /**
         * @brief            接收到WM_SETFOCUS时调用该函数
         * @param hPrevFocus 丢失焦点的hwnd，可能为NULL
         * @return           若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnSetFocus(HWND hPrevFocus) override;

        /**
         * @brief            接收到WM_KILLFOCUS时调用该函数
         * @param hNextFocus 接收到焦点的hwnd，可能为NULL
         * @return           若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnKillFocus(HWND hNextFocus) override;

        /**
         * @brief       接收到WM_CHAR时调用该函数
         * @param ch    按键的字符代码
         * @param flags 附加信息
         * @return      若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnChar(wchar_t ch, KeyFlags flags) override;

        /**
         * @brief       接收到WM_KEYDOWN时调用该函数
         * @param key   虚拟按键
         * @param flags 附加信息
         * @return      若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnKeyDown(VirtualKey key, KeyFlags flags) override;

        /**
         * @brief       接收到WM_KEYUP时调用该函数
         * @param key   虚拟按键
         * @param flags 附加信息
         * @return      若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnKeyUp(VirtualKey key, KeyFlags flags) override;

        /**
         * @brief               接收到WM_MOUSEMOVE时调用该函数
         * @param mousePosition 鼠标在用户区中的位置
         * @param keyState      指示某些按键是否按下
         * @return              若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnMouseMove(Point mousePosition, MouseKey keyState) override;

        /**
         * @brief  接收到WM_MOUSELEAVE时调用该函数
         * @return 若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnMouseLeave() override;

        /**
         * @brief               接收到WM_MOUSEWHEEL时调用该函数
         * @param wheelDelta    滚轮滚动的距离，为120的倍数
         * @param mousePosition 鼠标在用户区中的位置
         * @param keyState      指示某些按键是否按下
         * @return              若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnMouseWheel(int wheelDelta, Point mousePosition, MouseKey keyState) override;

        /**
         * @brief               接收到WM_LBUTTONDOWN时调用该函数
         * @param mousePosition 鼠标在用户区中的位置
         * @param keyState      指示某些按键是否按下
         * @return              若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnMouseLeftButtonDown(Point mousePosition, MouseKey keyState) override;

        /**
         * @brief               接收到WM_LBUTTONUP时调用该函数
         * @param mousePosition 鼠标在用户区中的位置
         * @param keyState      指示某些按键是否按下
         * @return              若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnMouseLeftButtonUp(Point mousePosition, MouseKey keyState) override;

        /**
         * @brief               接收到WM_RBUTTONDOWN时调用该函数
         * @param mousePosition 鼠标在用户区中的位置
         * @param keyState      指示某些按键是否按下
         * @return              若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnMouseRightButtonDown(Point mousePosition, MouseKey keyState) override;

        /**
         * @brief               接收到WM_RBUTTONUP时调用该函数
         * @param mousePosition 鼠标在用户区中的位置
         * @param keyState      指示某些按键是否按下
         * @return              若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnMouseRightButtonUp(Point mousePosition, MouseKey keyState) override;

        /**
         * @brief               接收到WM_MBUTTONDOWN时调用该函数
         * @param mousePosition 鼠标在用户区中的位置
         * @param keyState      指示某些按键是否按下
         * @return              若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnMouseMiddleButtonDown(Point mousePosition, MouseKey keyState) override;

        /**
         * @brief               接收到WM_MBUTTONUP时调用该函数
         * @param mousePosition 鼠标在用户区中的位置
         * @param keyState      指示某些按键是否按下
         * @return              若已处理该消息则返回true，否则返回false以调用DefaultWndProc
         */
        virtual bool OnMouseMiddleButtonUp(Point mousePosition, MouseKey keyState) override;
    };

    /*====================================================================================================*/

    /**
     * @brief                   根据事件参数类型注册路由事件
     * @tparam TEventArgs       路由事件参数类型
     * @param elementToRegister 要注册该事件的对象
     * @param handler           处理该事件的函数
     */
    template <
        typename TEventArgs,
        typename std::enable_if<std::is_base_of<RoutedEventArgs, TEventArgs>::value, int>::type = 0>
    inline void RegisterRoutedEvent(UIElement &elementToRegister, std::function<void(UIElement &, TEventArgs &)> handler)
    {
        if (!handler) {
            elementToRegister.UnregisterRoutedEvent(TEventArgs::TYPE);
            return;
        }
        elementToRegister.RegisterRoutedEvent(TEventArgs::TYPE, [handler](UIElement &element, RoutedEventArgs &args) {
            handler(element, static_cast<TEventArgs &>(args));
        });
    }

    /**
     * @brief                   注册特定类型的路由事件，当类型不匹配时自动忽略
     * @tparam TElement         发出该事件对象的类型
     * @tparam TEventArgs       该事件的事件参数类型
     * @param elementToRegister 要注册该事件的对象
     * @param handler           处理该事件的函数
     */
    template <
        typename TElement,
        typename TEventArgs,
        typename std::enable_if<std::is_base_of<UIElement, TElement>::value, int>::type         = 0,
        typename std::enable_if<std::is_base_of<RoutedEventArgs, TEventArgs>::value, int>::type = 0>
    inline void RegisterRoutedEvent(UIElement &elementToRegister, std::function<void(TElement &, TEventArgs &)> handler)
    {
        if (!handler) {
            elementToRegister.UnregisterRoutedEvent(TEventArgs::TYPE);
            return;
        }
        elementToRegister.RegisterRoutedEvent(TEventArgs::TYPE, [handler](UIElement &element, RoutedEventArgs &args) {
            TElement *pElement = dynamic_cast<TElement *>(&element);
            if (pElement != nullptr)
                handler(*pElement, static_cast<TEventArgs &>(args));
        });
    }
}
