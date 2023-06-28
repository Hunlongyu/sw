#pragma once

#include "ILayout.h"
#include "RoutedEvent.h"
#include "Thickness.h"
#include "WndBase.h"
#include <Alignment.h>
#include <map>
#include <string>
#include <vector>

namespace sw
{
    class UIElement : public WndBase,
                      public ILayout
    {
    private:
        bool _arranging                          = false;
        Size _desireSize                         = Size();
        Thickness _margin                        = Thickness();
        HorizontalAlignment _horizontalAlignment = HorizontalAlignment::Stretch;
        VerticalAlignment _verticalAlignment     = VerticalAlignment::Stretch;
        std::vector<UIElement *> _children{};
        std::map<RoutedEventType, RoutedEvent> _eventMap{};

    public:
        /**
         * @brief 描述
         */
        std::wstring Description = L"";

        /**
         * @brief 边缘空白大小
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

    public:
        UIElement();

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
         * @brief 通知父窗口布局改变
         */
        void NotifyLayoutUpdated();

        /**
         * @brief  添加子控件
         * @return 添加是否成功
         */
        bool AddChild(UIElement *element);

        /**
         * @brief  移除子控件
         * @return 移除是否成功
         */
        bool RemoveChild(UIElement *element);

        /**
         * @brief 通过索引获取子控件
         */
        UIElement *operator[](int index) const;

        /**
         * @brief 获取子控件的数量
         */
        virtual int GetChildLayoutCount();

        /**
         * @brief 获取对应索引处的子控件
         */
        virtual ILayout &GetChildLayoutAt(int index);

        /**
         * @brief 获取控件所需尺寸
         */
        virtual Size GetDesireSize();

        /**
         * @brief 设置当前控件所需的尺寸
         */
        virtual void SetDesireSize(const Size &size);

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

    protected:
        /**
         * @brief 触发路由事件
         */
        void RaiseRoutedEvent(RoutedEventType eventType, void *param = nullptr);

        /**
         * @brief 获取顶级窗口
         */
        UIElement &GetRootElement();

        /**
         * @brief  设置父窗口
         * @return 设置是否成功
         */
        virtual bool SetParent(WndBase *parent);
    };
}
