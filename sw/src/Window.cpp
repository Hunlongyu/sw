#include "Window.h"
#include "Utils.h"
#include <cmath>

/**
 * @brief 记录当前创建的窗口数
 */
static int _windowCount = 0;

/**
 * @brief DPI更新时调用该函数递归地更新所有子项的字体
 */
static void _UpdateFontForAllChild(sw::UIElement &element);

/**
 * @brief  获取窗口默认图标（即当前exe图标）
 * @return 图标句柄
 */
static HICON _GetWindowDefaultIcon();

/**
 * @brief 程序的当前活动窗体
 */
const sw::ReadOnlyProperty<sw::Window *> sw::Window::ActiveWindow(
    []() -> sw::Window *const & {
        static sw::Window *pWindow;
        HWND hwnd = GetForegroundWindow();
        pWindow   = dynamic_cast<sw::Window *>(sw::WndBase::GetWndBase(hwnd));
        return pWindow;
    } //
);

sw::Window::Window()
    : State(
          // get
          [&]() -> const WindowState & {
              static WindowState state;
              HWND hwnd = this->Handle;
              if (IsIconic(hwnd)) {
                  state = WindowState::Minimized;
              } else if (IsZoomed(hwnd)) {
                  state = WindowState::Maximized;
              } else {
                  state = WindowState::Normal;
              }
              return state;
          },
          // set
          [&](const WindowState &value) {
              HWND hwnd = this->Handle;
              switch (value) {
                  case WindowState::Normal:
                      ShowWindow(hwnd, SW_RESTORE);
                      break;
                  case WindowState::Minimized:
                      ShowWindow(hwnd, SW_MINIMIZE);
                      break;
                  case WindowState::Maximized:
                      ShowWindow(hwnd, SW_MAXIMIZE);
                      break;
              }
          }),

      SizeBox(
          // get
          [&]() -> const bool & {
              static bool result;
              result = this->GetStyle(WS_SIZEBOX);
              return result;
          },
          // set
          [&](const bool &value) {
              this->SetStyle(WS_SIZEBOX, value);
          }),

      MaximizeBox(
          // get
          [&]() -> const bool & {
              static bool result;
              result = this->GetStyle(WS_MAXIMIZEBOX);
              return result;
          },
          // set
          [&](const bool &value) {
              this->SetStyle(WS_MAXIMIZEBOX, value);
          }),

      MinimizeBox(
          // get
          [&]() -> const bool & {
              static bool result;
              result = this->GetStyle(WS_MINIMIZEBOX);
              return result;
          },
          // set
          [&](const bool &value) {
              this->SetStyle(WS_MINIMIZEBOX, value);
          }),

      Topmost(
          // get
          [&]() -> const bool & {
              static bool result;
              result = this->GetExtendedStyle(WS_EX_TOPMOST);
              return result;
          },
          // set
          [&](const bool &value) {
              /*this->SetExtendedStyle(WS_EX_TOPMOST, value);*/
              HWND hWndInsertAfter = value ? HWND_TOPMOST : HWND_NOTOPMOST;
              SetWindowPos(this->Handle, hWndInsertAfter, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
          }),

      ToolWindow(
          // get
          [&]() -> const bool & {
              static bool result;
              result = this->GetExtendedStyle(WS_EX_TOOLWINDOW);
              return result;
          },
          // set
          [&](const bool &value) {
              this->SetExtendedStyle(WS_EX_TOOLWINDOW, value);
          }),

      BackColor(
          // get
          [&]() -> const Color & {
              return this->_backColor;
          },
          // set
          [&](const Color &value) {
              this->_backColor = value;
              this->Redraw();
          }),

      MaxWidth(
          // get
          [&]() -> const double & {
              return this->_maxWidth;
          },
          // set
          [&](const double &value) {
              this->_maxWidth = value;
              this->Width     = this->Width;
          }),

      MaxHeight(
          // get
          [&]() -> const double & {
              return this->_maxHeight;
          },
          // set
          [&](const double &value) {
              this->_maxHeight = value;
              this->Height     = this->Height;
          }),

      MinWidth(
          // get
          [&]() -> const double & {
              return this->_minWidth;
          },
          // set
          [&](const double &value) {
              this->_minWidth = value;
              this->Width     = this->Width;
          }),

      MinHeight(
          // get
          [&]() -> const double & {
              return this->_minHeight;
          },
          // set
          [&](const double &value) {
              this->_minHeight = value;
              this->Height     = this->Height;
          })
{
    this->InitWindow(L"Window", WS_OVERLAPPEDWINDOW, NULL, NULL);
    this->SetCursor(StandardCursor::Arrow);
    this->SetIcon(_GetWindowDefaultIcon());
}

LRESULT sw::Window::WndProc(const ProcMsg &refMsg)
{
    switch (refMsg.uMsg) {
        case WM_SHOWWINDOW: {
            // 窗口首次启动时按照StartupLocation修改位置
            if (this->_isFirstShow) {
                this->_isFirstShow = false;
                if (this->StartupLocation == WindowStartupLocation::CenterScreen) {
                    sw::Rect rect = this->Rect;
                    rect.left     = (Screen::Width - rect.width) / 2;
                    rect.top      = (Screen::Height - rect.height) / 2;
                    this->Rect    = rect;
                } else if (this->StartupLocation == WindowStartupLocation::CenterOwner) {
                    if (this->IsModal()) {
                        sw::Rect windowRect = this->Rect;
                        sw::Rect ownerRect  = this->_modalOwner->Rect;
                        windowRect.left     = ownerRect.left + (ownerRect.width - windowRect.width) / 2;
                        windowRect.top      = ownerRect.top + (ownerRect.height - windowRect.height) / 2;
                        this->Rect          = windowRect;
                    }
                }
            }
            return this->UIElement::WndProc(refMsg);
        }

        case WM_GETMINMAXINFO: {
            double scaleX     = Dip::ScaleX;
            double scaleY     = Dip::ScaleY;
            PMINMAXINFO pInfo = reinterpret_cast<PMINMAXINFO>(refMsg.lParam);
            // 按照设置限制窗口大小
            if (this->_maxWidth > 0) {
                LONG maxWidth           = std::lround(this->_maxWidth / scaleX);
                pInfo->ptMaxTrackSize.x = Utils::Min(pInfo->ptMaxTrackSize.x, maxWidth);
            }
            if (this->_maxHeight > 0) {
                LONG maxHeight          = std::lround(this->_maxHeight / scaleY);
                pInfo->ptMaxTrackSize.y = Utils::Min(pInfo->ptMaxTrackSize.y, maxHeight);
            }
            if (this->_minWidth > 0) {
                LONG minWidth           = std::lround(this->_minWidth / scaleX);
                pInfo->ptMinTrackSize.x = Utils::Max(pInfo->ptMinTrackSize.x, minWidth);
            }
            if (this->_minHeight > 0) {
                LONG minHeight          = std::lround(this->_minHeight / scaleY);
                pInfo->ptMinTrackSize.y = Utils::Max(pInfo->ptMinTrackSize.y, minHeight);
            }
            return 0;
        }

        case WM_DPICHANGED: {
            Dip::Update(LOWORD(refMsg.wParam), HIWORD(refMsg.wParam));
            this->UpdateLayout();
            _UpdateFontForAllChild(*this);
            return 0;
        }

        case WM_UpdateLayout: {
            this->UpdateLayout();
            return 0;
        }

        default: {
            return this->UIElement::WndProc(refMsg);
        }
    }
}

bool sw::Window::OnClose()
{
    WindowClosingEventArgs args;
    RaiseRoutedEvent(args);

    if (!args.cancel) {
        this->UIElement::OnClose();
    }

    return true;
}

bool sw::Window::OnCreate()
{
    ++_windowCount;
    return true;
}

bool sw::Window::OnDestroy()
{
    // 触发路由事件
    RaiseRoutedEvent(RoutedEventType::Window_Closed);

    // 若当前窗口为模态窗口则在窗口关闭时退出消息循环
    if (this->IsModal()) {
        App::QuitMsgLoop();
    }

    // 所有窗口都关闭时若App::QuitMode为Auto则退出主消息循环
    if (--_windowCount <= 0 && App::QuitMode.Get() == AppQuitMode::Auto) {
        App::QuitMsgLoop();
    }

    return true;
}

bool sw::Window::OnPaint()
{
    PAINTSTRUCT ps;
    HWND hwnd     = this->Handle;
    HDC hdc       = BeginPaint(hwnd, &ps);
    HBRUSH hBrush = CreateSolidBrush(this->_backColor);
    FillRect(hdc, &ps.rcPaint, hBrush);
    DeleteObject(hBrush);
    EndPaint(hwnd, &ps);
    return true;
}

bool sw::Window::OnMouseMove(Point mousePosition, MouseKey keyState)
{
    ::SetCursor(this->_hCursor);
    return this->UIElement::OnMouseMove(mousePosition, keyState);
}

void sw::Window::Show()
{
    this->WndBase::Show(SW_SHOW);
}

void sw::Window::ShowDialog(Window &owner)
{
    if (this->IsModal() || this == &owner || this->IsDestroyed) {
        return;
    }

    this->_modalOwner = &owner;
    SetWindowLongPtrW(this->Handle, GWLP_HWNDPARENT, reinterpret_cast<LONG_PTR>(owner.Handle.Get()));

    bool oldIsEnabled = owner.Enabled;
    owner.Enabled     = false;

    this->Show();
    App::MsgLoop();
    SetForegroundWindow(owner.Handle);

    if (oldIsEnabled) {
        owner.Enabled = true;
    }
}

void sw::Window::SetCursor(HCURSOR hCursor)
{
    this->_hCursor = hCursor;
}

void sw::Window::SetCursor(StandardCursor cursor)
{
    this->SetCursor(CursorHelper::GetCursorHandle(cursor));
}

void sw::Window::SetIcon(HICON hIcon)
{
    this->SendMessageW(WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    this->SendMessageW(WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
}

void sw::Window::SetMenu(HMENU hMenu)
{
    ::SetMenu(this->Handle, hMenu);
}

bool sw::Window::IsModal()
{
    return this->_modalOwner != nullptr;
}

void sw::Window::Measure(const Size &availableSize)
{
    this->Layer::Measure(availableSize);
}

void sw::Window::Arrange(const sw::Rect &finalPosition)
{
    this->Layer::Arrange(finalPosition);
}

void _UpdateFontForAllChild(sw::UIElement &element)
{
    element.UpdateFont();

    int count = element.ChildCount;
    for (int i = 0; i < count; ++i) {
        _UpdateFontForAllChild(element[i]);
    }
}

HICON _GetWindowDefaultIcon()
{
    static HICON hIcon = NULL;
    if (hIcon == NULL)
        hIcon = ExtractIconW(sw::App::Instance, sw::App::ExePath->c_str(), 0);
    return hIcon;
}
