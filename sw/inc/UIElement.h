#pragma once

#include <map>
#include <string>
#include "WndBase.h"
#include "RoutedEvent.h"

namespace sw
{
    class UIElement : public WndBase
    {
    private:
        std::map<RoutedEventType, RoutedEvent> _eventMap{};

    public:
        std::wstring Description = L"";

    public:
        UIElement();

        /**
         * @brief           ע��·���¼������������¼���ע��ʱ�Ḳ����ע��ĺ���
         * @param eventType ·���¼�����
         * @param event     ����������ֵΪnullptrʱ��ȡ��ע��
         */
        void RegisterRoutedEvent(RoutedEventType eventType, const RoutedEvent &event);

        /**
         * @brief           ȡ����Ӧ����·���¼���ע��
         * @param eventType ·���¼�����
         */
        void UnregisterRoutedEvent(RoutedEventType eventType);

        /**
         * @brief           �ж�·���¼��Ƿ��ѱ�ע��
         * @param eventType ·���¼�����
         */
        bool IsRoutedEventRegistered(RoutedEventType eventType);
    };
}
