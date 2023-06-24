#pragma once

#include <Windows.h>
#include <cstdint>

namespace sw
{
    struct Color {
        uint8_t r;
        uint8_t g;
        uint8_t b;

        Color();
        Color(uint8_t r, uint8_t g, uint8_t b);
        Color(COLORREF color);
        operator COLORREF() const;

        /*==================================================*/

        enum SolidColors : COLORREF {
            AliceBlue            = RGB(240, 248, 255), // ����˿��
            AntiqueWhite         = RGB(250, 235, 215), // �Ŷ���
            Aqua                 = RGB(0, 255, 255),   // ��ɫ
            Aquamarine           = RGB(127, 255, 212), // ����ɫ
            Azure                = RGB(240, 255, 255), // ε��ɫ
            Beige                = RGB(245, 245, 220), // ��ɫ
            Bisque               = RGB(255, 228, 196), // �ٻ�ɫ
            Black                = RGB(0, 0, 0),       // ��ɫ
            BlanchedAlmond       = RGB(255, 235, 205), // �Ӱ�ɫ
            Blue                 = RGB(0, 0, 255),     // ��ɫ
            BlueViolet           = RGB(138, 43, 226),  // ����ɫ
            Brown                = RGB(165, 42, 42),   // ��ɫ
            BurlyWood            = RGB(222, 184, 135), // ʵľɫ
            CadetBlue            = RGB(95, 158, 160),  // ������
            Chartreuse           = RGB(127, 255, 0),   // ���ؾ���
            Chocolate            = RGB(210, 105, 30),  // �ɿ���ɫ
            Coral                = RGB(255, 127, 80),  // ɺ����
            CornflowerBlue       = RGB(100, 149, 237), // ʸ������
            Cornsilk             = RGB(255, 248, 220), // ����˿ɫ
            Crimson              = RGB(220, 20, 60),   // ���ɫ
            Cyan                 = RGB(0, 255, 255),   // ��ɫ
            DarkBlue             = RGB(0, 0, 139),     // ����ɫ
            DarkCyan             = RGB(0, 139, 139),   // ����ɫ
            DarkGoldenrod        = RGB(184, 134, 11),  // ����ɫ
            DarkGray             = RGB(169, 169, 169), // ���ɫ
            DarkGreen            = RGB(0, 100, 0),     // ����ɫ
            DarkKhaki            = RGB(189, 183, 107), // ���ɫ
            DarkMagenta          = RGB(139, 0, 139),   // �����ɫ
            DarkOliveGreen       = RGB(85, 107, 47),   // �������
            DarkOrange           = RGB(255, 140, 0),   // ���ɫ
            DarkOrchid           = RGB(153, 50, 204),  // ��������
            DarkRed              = RGB(139, 0, 0),     // ���ɫ
            DarkSalmon           = RGB(233, 150, 122), // ��Ⱥ�
            DarkSeaGreen         = RGB(143, 188, 143), // ���ɫ
            DarkSlateBlue        = RGB(72, 61, 139),   // ��ʯ����
            DarkSlateGray        = RGB(47, 79, 79),    // ��ʯ���
            DarkTurquoise        = RGB(0, 206, 209),   // ������ɫ
            DarkViolet           = RGB(148, 0, 211),   // ��������ɫ
            DeepPink             = RGB(255, 20, 147),  // ��ۺ�ɫ
            DeepSkyBlue          = RGB(0, 191, 255),   // ������ɫ
            DimGray              = RGB(105, 105, 105), // ���ɫ
            DodgerBlue           = RGB(30, 144, 255),  // ������
            Firebrick            = RGB(178, 34, 34),   // ��שɫ
            FloralWhite          = RGB(255, 250, 240), // ���İ�ɫ
            ForestGreen          = RGB(34, 139, 34),   // ɭ����
            Fuchsia              = RGB(255, 0, 255),   // �Ϻ�ɫ
            Gainsboro            = RGB(220, 220, 220), // ����ɫ
            GhostWhite           = RGB(248, 248, 255), // �����
            Gold                 = RGB(255, 215, 0),   // ��ɫ
            Goldenrod            = RGB(218, 165, 32),  // ������ɫ
            Gray                 = RGB(128, 128, 128), // ��ɫ
            Green                = RGB(0, 128, 0),     // ��ɫ
            GreenYellow          = RGB(173, 255, 47),  // �̻�ɫ
            Honeydew             = RGB(240, 255, 240), // �۹�ɫ
            HotPink              = RGB(255, 105, 180), // ����ۺ�ɫ
            IndianRed            = RGB(205, 92, 92),   // ӡ�Ⱥ�
            Indigo               = RGB(75, 0, 130),    // ����ɫ
            Ivory                = RGB(255, 255, 240), // ����ɫ
            Khaki                = RGB(240, 230, 140), // ����ɫ
            Lavender             = RGB(230, 230, 250), // ޹�²ݵ���ɫ
            LavenderBlush        = RGB(255, 240, 245), // ���Ϻ�ɫ
            LawnGreen            = RGB(124, 252, 0),   // ��ƺ��
            LemonChiffon         = RGB(255, 250, 205), // ���ʳ�ɫ
            LightBlue            = RGB(173, 216, 230), // ����ɫ
            LightCoral           = RGB(240, 128, 128), // ǳɺ��ɫ
            LightCyan            = RGB(224, 255, 255), // ����ɫ
            LightGoldenrodYellow = RGB(250, 250, 210), // ǳ��ջ�ɫ
            LightGray            = RGB(211, 211, 211), // ǳ��ɫ
            LightGreen           = RGB(144, 238, 144), // ǳ��ɫ
            LightPink            = RGB(255, 182, 193), // ǳ�ۺ�ɫ
            LightSalmon          = RGB(255, 160, 122), // ǳ������ɫ
            LightSeaGreen        = RGB(32, 178, 170),  // ǳ������ɫ
            LightSkyBlue         = RGB(135, 206, 250), // ǳ����ɫ
            LightSlateGray       = RGB(119, 136, 153), // ǳʯ���
            LightSteelBlue       = RGB(176, 196, 222), // ǳ����ɫ
            LightYellow          = RGB(255, 255, 224), // ǳ��ɫ
            Lime                 = RGB(0, 255, 0),     // ���ɫ
            LimeGreen            = RGB(50, 205, 50),   // �����ɫ
            Linen                = RGB(250, 240, 230), // ����ɫ
            Magenta              = RGB(255, 0, 255),   // ���ɫ
            Maroon               = RGB(128, 0, 0),     // ��ɫ
            MediumAquamarine     = RGB(102, 205, 170), // ���̱�ʯɫ
            MediumBlue           = RGB(0, 0, 205),     // ����ɫ
            MediumOrchid         = RGB(186, 85, 211),  // ��������
            MediumPurple         = RGB(147, 112, 219), // ����ɫ
            MediumSeaGreen       = RGB(60, 179, 113),  // �к�����ɫ
            MediumSlateBlue      = RGB(123, 104, 238), // ��ʯ����ɫ
            MediumSpringGreen    = RGB(0, 250, 154),   // �д���ɫ
            MediumTurquoise      = RGB(72, 209, 204),  // ���̱�ʯɫ
            MediumVioletRed      = RGB(199, 21, 133),  // ��������ɫ
            MidnightBlue         = RGB(25, 25, 112),   // ��ҹ��
            MintCream            = RGB(245, 255, 250), // ��������ɫ
            MistyRose            = RGB(255, 228, 225), // ǳõ��ɫ
            Moccasin             = RGB(255, 228, 181), // ¹Ƥɫ
            NavajoWhite          = RGB(255, 222, 173), // ���߰�
            Navy                 = RGB(0, 0, 128),     // ������
            OldLace              = RGB(253, 245, 230), // �ϻ�ɫ
            Olive                = RGB(128, 128, 0),   // ���ɫ
            OliveDrab            = RGB(107, 142, 35),  // ��魺�ɫ
            Orange               = RGB(255, 165, 0),   // ��ɫ
            OrangeRed            = RGB(255, 69, 0),    // �Ⱥ�ɫ
            Orchid               = RGB(218, 112, 214), // ������
            PaleGoldenrod        = RGB(238, 232, 170), // ������ɫ
            PaleGreen            = RGB(152, 251, 152), // ����ɫ
            PaleTurquoise        = RGB(175, 238, 238), // �Ա�ʯ��
            PaleVioletRed        = RGB(219, 112, 147), // ��������ɫ
            PapayaWhip           = RGB(255, 239, 213), // ��ľɫ
            PeachPuff            = RGB(255, 218, 185), // ��ɫ
            Peru                 = RGB(205, 133, 63),  // ��³ɫ
            Pink                 = RGB(255, 192, 203), // �ۺ�ɫ
            Plum                 = RGB(221, 160, 221), // ����ɫ
            PowderBlue           = RGB(176, 224, 230), // ����ɫ
            Purple               = RGB(128, 0, 128),   // ��ɫ
            Red                  = RGB(255, 0, 0),     // ��ɫ
            RosyBrown            = RGB(188, 143, 143), // õ���ɫ
            RoyalBlue            = RGB(65, 105, 225),  // �ʼ���
            SaddleBrown          = RGB(139, 69, 19),   // ����ɫ
            Salmon               = RGB(250, 128, 114), // ����ɫ
            SandyBrown           = RGB(244, 164, 96),  // ɳ��ɫ
            SeaGreen             = RGB(46, 139, 87),   // ������ɫ
            SeaShell             = RGB(255, 245, 238), // ������ɫ
            Sienna               = RGB(160, 82, 45),   // ������ɫ
            Silver               = RGB(192, 192, 192), // ��ɫ
            SkyBlue              = RGB(135, 206, 235), // ����ɫ
            SlateBlue            = RGB(106, 90, 205),  // ʯ����ɫ
            SlateGray            = RGB(112, 128, 144), // ʯ���
            Snow                 = RGB(255, 250, 250), // ѩ��ɫ
            SpringGreen          = RGB(0, 255, 127),   // ����ɫ
            SteelBlue            = RGB(70, 130, 180),  // ����ɫ
            Tan                  = RGB(210, 180, 140), // ��ɫ
            Teal                 = RGB(0, 128, 128),   // ˮѼɫ
            Thistle              = RGB(216, 191, 216), // ��ɫ
            Tomato               = RGB(255, 99, 71),   // ����ɫ
            Turquoise            = RGB(64, 224, 208),  // �̱�ʯɫ
            Violet               = RGB(238, 130, 238), // ������ɫ
            Wheat                = RGB(245, 222, 179), // ǳ��ɫ
            White                = RGB(255, 255, 255), // ��ɫ
            WhiteSmoke           = RGB(245, 245, 245), // �̰�ɫ
            Yellow               = RGB(255, 255, 0),   // ��ɫ
            YellowGreen          = RGB(154, 205, 50),  // ����ɫ
        };
    };
}
