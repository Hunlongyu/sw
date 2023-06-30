#pragma once

#include "Alignment.h"
#include "WrapLayoutH.h"
#include "WrapLayoutV.h"

namespace sw
{
    class WrapLayout : public WrapLayoutH,
                       public WrapLayoutV
    {
    public:
        /**
         * @brief 排列方式
         */
        Orientation orientation = Orientation::Horizontal;

        /**
         * @brief 计算所需尺寸
         */
        virtual void MeasureOverride(Size &availableSize);

        /**
         * @brief 安排控件
         */
        virtual void ArrangeOverride(Size &finalSize);
    };
}
