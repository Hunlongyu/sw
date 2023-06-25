#pragma warning(disable:4819)
#include "Window.h"

using namespace sw;

int WINAPI wWinMain(
    _In_     HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_     PWSTR     pCmdLine,
    _In_     INT       nCmdShow)
{
    Window window;
    window.Show();

    window.RegisterRoutedEvent(RoutedEventType::WindowClosing,
        [](UIElement& element, RoutedEventArgs& args) {
            bool& cancel = *reinterpret_cast<bool*>(args.param);
            if (MessageBoxW(element.Handle, L"�Ƿ�رգ�", L"��ʾ", MB_YESNO | MB_ICONQUESTION) == IDNO) {
                cancel = true;
                element.Text = L"��ȡ���ر�";
            }
            args.handled = true;
        }
    );

    App::MsgLoop();
    return 0;
}
