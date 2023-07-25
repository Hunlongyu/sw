#include "WndBase.h"
#include <cmath>

/**
 * @brief 窗口类名
 */
static PCWSTR WINDOW_CLASS_NAME = L"sw::WndBase";

/**
 * @brief 控件初始化时所在的窗口
 */
static HWND _controlInitContainer = NULL;

LRESULT sw::WndBase::_WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    WndBase *pWnd = WndBase::GetWndBase(hwnd);

    if (pWnd == NULL && (uMsg == WM_NCCREATE || uMsg == WM_CREATE)) {
        LPCREATESTRUCTW pCreate;
        pCreate = reinterpret_cast<LPCREATESTRUCTW>(lParam);
        pWnd    = reinterpret_cast<WndBase *>(pCreate->lpCreateParams);
    }

    if (pWnd != NULL) {
        return pWnd->WndProc(ProcMsg(hwnd, uMsg, wParam, lParam));
    } else {
        return DefWindowProcW(hwnd, uMsg, wParam, lParam);
    }
}

sw::WndBase::WndBase()
    : Handle(
          // get
          [&]() -> const HWND & {
              return this->_hwnd;
          }),

      Font(
          // get
          [&]() -> const sw::Font & {
              return this->_font;
          },
          // set
          [&](const sw::Font &value) {
              this->_font = value;
              this->UpdateFont();
          }),

      FontName(
          // get
          [&]() -> const std::wstring & {
              return this->_font.name;
          },
          // set
          [&](const std::wstring &value) {
              this->_font.name = value;
              this->UpdateFont();
          }),

      FontSize(
          // get
          [&]() -> const double & {
              return this->_font.size;
          },
          // set
          [&](const double &value) {
              this->_font.size = value;
              this->UpdateFont();
          }),

      FontWeight(
          // get
          [&]() -> const sw::FontWeight & {
              return this->_font.weight;
          },
          // set
          [&](const sw::FontWeight &value) {
              this->_font.weight = value;
              this->UpdateFont();
          }),

      Rect(
          // get
          [&]() -> const sw::Rect & {
              return this->_rect;
          },
          // set
          [&](const sw::Rect &value) {
              /*RECT rect = value.GetRECT();
              MoveWindow(this->_hwnd, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, TRUE);*/
              double scaleX = Dip::ScaleX;
              double scaleY = Dip::ScaleY;
              int left      = std::lround(value.left / scaleX);
              int top       = std::lround(value.top / scaleY);
              int width     = std::lround(value.width / scaleX);
              int height    = std::lround(value.height / scaleY);
              SetWindowPos(this->_hwnd, NULL, left, top, width, height, SWP_NOACTIVATE | SWP_NOZORDER);
          }),

      Left(
          // get
          [&]() -> const double & {
              return this->_rect.left;
          },
          // set
          [&](const double &value) {
              int x = std::lround(value / Dip::ScaleX);
              int y = std::lround(this->_rect.top / Dip::ScaleY);
              SetWindowPos(this->_hwnd, NULL, x, y, 0, 0, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
          }),

      Top(
          // get
          [&]() -> const double & {
              return this->_rect.top;
          },
          // set
          [&](const double &value) {
              int x = std::lround(this->_rect.left / Dip::ScaleX);
              int y = std::lround(value / Dip::ScaleY);
              SetWindowPos(this->_hwnd, NULL, x, y, 0, 0, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
          }),

      Width(
          // get
          [&]() -> const double & {
              return this->_rect.width;
          },
          // set
          [&](const double &value) {
              int cx = std::lround(value / Dip::ScaleX);
              int cy = std::lround(this->_rect.height / Dip::ScaleY);
              SetWindowPos(this->_hwnd, NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOMOVE);
          }),

      Height(
          // get
          [&]() -> const double & {
              return this->_rect.height;
          },
          // set
          [&](const double &value) {
              int cx = std::lround(this->_rect.width / Dip::ScaleX);
              int cy = std::lround(value / Dip::ScaleY);
              SetWindowPos(this->_hwnd, NULL, 0, 0, cx, cy, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOMOVE);
          }),

      ClientRect(
          // get
          [&]() -> const sw::Rect & {
              static sw::Rect swRect;
              RECT rect;
              GetClientRect(this->_hwnd, &rect);
              swRect = rect;
              return swRect;
          }),

      ClientWidth(
          // get
          [&]() -> const double & {
              return this->ClientRect->width;
          }),

      ClientHeight(
          // get
          [&]() -> const double & {
              return this->ClientRect->height;
          }),

      Enabled(
          // get
          [&]() -> const bool & {
              static bool enabled;
              enabled = IsWindowEnabled(this->_hwnd);
              return enabled;
          },
          // set
          [&](const bool &value) {
              EnableWindow(this->_hwnd, value);
          }),

      Visible(
          // get
          [&]() -> const bool & {
              static bool visible;
              visible = IsWindowVisible(this->_hwnd);
              return visible;
          },
          // set
          [&](const bool &value) {
              if (value != this->Visible) {
                  ShowWindow(this->_hwnd, value ? SW_SHOW : SW_HIDE);
                  this->VisibleChanged(value);
              }
          }),

      Text(
          // get
          [&]() -> const std::wstring & {
              return this->_text;
          },
          // set
          [&](const std::wstring &value) {
              std::wstring newText = value;
              if (this->OnSetText(newText))
                  SetWindowTextW(this->_hwnd, newText.c_str());
          }),

      Focused(
          // get
          [&]() -> const bool & {
              return this->_focused;
          },
          // set
          [&](const bool &value) {
              SetFocus(value ? this->_hwnd : NULL);
          }),

      Parent(
          // get
          [&]() -> WndBase *const & {
              static WndBase *pWndBase;
              HWND hwnd = GetParent(this->_hwnd);
              pWndBase  = WndBase::GetWndBase(hwnd);
              return pWndBase;
          }),

      IsDestroyed(
          // get
          [&]() -> const bool & {
              return this->_isDestroyed;
          })
{
    static WNDCLASSEXW wc = {0};

    if (wc.cbSize == 0) {
        wc.cbSize        = sizeof(wc);
        wc.hInstance     = App::Instance;
        wc.lpfnWndProc   = WndBase::_WndProc;
        wc.lpszClassName = WINDOW_CLASS_NAME;
    }

    RegisterClassExW(&wc);
    this->_font = sw::Font::GetDefaultFont();
}

sw::WndBase::~WndBase()
{
    if (this->_hwnd != NULL) {
        DestroyWindow(this->_hwnd);
    }
    if (this->_hfont != NULL) {
        DeleteObject(this->_hfont);
    }
}

void sw::WndBase::InitWindow(LPCWSTR lpWindowName, DWORD dwStyle, HWND hWndParent, HMENU hMenu)
{
    if (this->_hwnd == NULL) {

        this->_text = lpWindowName ? lpWindowName : L"";

        this->_hwnd = CreateWindowExW(
            0,                 // Optional window styles
            WINDOW_CLASS_NAME, // Window class
            lpWindowName,      // Window text
            dwStyle,           // Window style

            // Size and position
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

            hWndParent,    // Parent window
            hMenu,         // Menu
            App::Instance, // Instance handle
            this           // Additional application data
        );

        this->HandleInitialized(this->_hwnd);

        RECT rect;
        GetWindowRect(this->_hwnd, &rect);
        this->_rect = rect;

        SetWindowLongPtrW(this->_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
        this->UpdateFont();
    }
}

void sw::WndBase::InitControl(LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle)
{
    if (_controlInitContainer == NULL) {
        _controlInitContainer = CreateWindowExW(0, WINDOW_CLASS_NAME, L"", WS_POPUP, 0, 0, 0, 0, NULL, NULL, NULL, NULL);
    }

    if (this->_hwnd == NULL) {

        this->_text = lpWindowName ? lpWindowName : L"";

        this->_hwnd = CreateWindowExW(
            0,            // Optional window styles
            lpClassName,  // Window class
            lpWindowName, // Window text
            dwStyle,      // Window style

            // Size and position
            0, 0, 0, 0,

            _controlInitContainer, // Parent window
            NULL,                  // Menu
            App::Instance,         // Instance handle
            this                   // Additional application data
        );

        this->HandleInitialized(this->_hwnd);

        this->_controlOldWndProc =
            reinterpret_cast<WNDPROC>(SetWindowLongPtrW(this->_hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndBase::_WndProc)));

        RECT rect;
        GetWindowRect(this->_hwnd, &rect);
        this->_rect = rect;

        SetWindowLongPtrW(this->_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
        this->UpdateFont();
    }
}

LONG_PTR sw::WndBase::GetStyle()
{
    return GetWindowLongPtrW(this->_hwnd, GWL_STYLE);
}

void sw::WndBase::SetStyle(LONG_PTR style)
{
    SetWindowLongPtrW(this->_hwnd, GWL_STYLE, style);
}

bool sw::WndBase::GetStyle(LONG_PTR style)
{
    return GetWindowLongPtrW(this->_hwnd, GWL_STYLE) & style;
}

void sw::WndBase::SetStyle(LONG_PTR style, bool value)
{
    if (value) {
        style = GetWindowLongPtrW(this->_hwnd, GWL_STYLE) | style;
    } else {
        style = GetWindowLongPtrW(this->_hwnd, GWL_STYLE) & ~style;
    }
    SetWindowLongPtrW(this->_hwnd, GWL_STYLE, style);
}

LONG_PTR sw::WndBase::GetExtendedStyle()
{
    return GetWindowLongPtrW(this->_hwnd, GWL_EXSTYLE);
}

void sw::WndBase::SetExtendedStyle(LONG_PTR style)
{
    SetWindowLongPtrW(this->_hwnd, GWL_EXSTYLE, style);
}

bool sw::WndBase::GetExtendedStyle(LONG_PTR style)
{
    return GetWindowLongPtrW(this->_hwnd, GWL_EXSTYLE) & style;
}

void sw::WndBase::SetExtendedStyle(LONG_PTR style, bool value)
{
    if (value) {
        style = GetWindowLongPtrW(this->_hwnd, GWL_EXSTYLE) | style;
    } else {
        style = GetWindowLongPtrW(this->_hwnd, GWL_EXSTYLE) & ~style;
    }
    SetWindowLongPtrW(this->_hwnd, GWL_EXSTYLE, style);
}

HFONT sw::WndBase::GetFontHandle()
{
    return this->_hfont;
}

LRESULT sw::WndBase::DefaultWndProc(const ProcMsg &refMsg)
{
    WNDPROC wndproc = this->IsControl() ? this->_controlOldWndProc : DefWindowProcW;
    return wndproc(refMsg.hwnd, refMsg.uMsg, refMsg.wParam, refMsg.lParam);
}

LRESULT sw::WndBase::WndProc(const ProcMsg &refMsg)
{
    switch (refMsg.uMsg) {
        case WM_CREATE: {
            return this->OnCreate() ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_CLOSE: {
            return this->OnClose() ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_DESTROY: {
            this->_isDestroyed = true;
            return this->OnDestroy() ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_PAINT: {
            return this->OnPaint() ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_WINDOWPOSCHANGED: {
            PWINDOWPOS pWndPos = reinterpret_cast<PWINDOWPOS>(refMsg.lParam);
            double scaleX      = Dip::ScaleX;
            double scaleY      = Dip::ScaleY;
            this->_rect.left   = scaleX * pWndPos->x;
            this->_rect.top    = scaleY * pWndPos->y;
            this->_rect.width  = scaleX * pWndPos->cx;
            this->_rect.height = scaleY * pWndPos->cy;
            return this->DefaultWndProc(refMsg);
        }

        case WM_MOVE: {
            int xPos = (int)(short)LOWORD(refMsg.lParam); // horizontal position
            int yPos = (int)(short)HIWORD(refMsg.lParam); // vertical position
            return this->OnMove(Point(xPos, yPos)) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_SIZE: {
            int width  = LOWORD(refMsg.lParam); // the new width of the client area
            int height = HIWORD(refMsg.lParam); // the new height of the client area
            return this->OnSize(Size(width, height)) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_SETTEXT: {
            LRESULT result = this->DefaultWndProc(refMsg);
            if (result == TRUE) {
                this->_text = reinterpret_cast<PCWSTR>(refMsg.lParam);
                this->OnTextChanged(this->_text);
            }
            return result;
        }

        case WM_SETFOCUS: {
            this->_focused = true;
            return this->OnSetFocus((HWND)refMsg.wParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_KILLFOCUS: {
            this->_focused = false;
            return this->OnKillFocus((HWND)refMsg.wParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_MOUSEMOVE: {
            POINT mousePosition{GET_X_LPARAM(refMsg.lParam), GET_Y_LPARAM(refMsg.lParam)};
            return this->OnMouseMove(Point(mousePosition), (MouseKey)refMsg.wParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_MOUSELEAVE: {
            return this->OnMouseLeave() ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_MOUSEWHEEL: {
            int fwKeys = GET_KEYSTATE_WPARAM(refMsg.wParam);
            int zDelta = GET_WHEEL_DELTA_WPARAM(refMsg.wParam);
            POINT mousePosition{GET_X_LPARAM(refMsg.lParam), GET_Y_LPARAM(refMsg.lParam)};
            return this->OnMouseWheel(zDelta, Point(mousePosition), (MouseKey)fwKeys) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_LBUTTONDOWN: {
            POINT mousePosition{GET_X_LPARAM(refMsg.lParam), GET_Y_LPARAM(refMsg.lParam)};
            return this->OnMouseLeftButtonDown(Point(mousePosition), (MouseKey)refMsg.wParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_LBUTTONUP: {
            POINT mousePosition{GET_X_LPARAM(refMsg.lParam), GET_Y_LPARAM(refMsg.lParam)};
            return this->OnMouseLeftButtonUp(Point(mousePosition), (MouseKey)refMsg.wParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_LBUTTONDBLCLK: {
            POINT mousePosition{GET_X_LPARAM(refMsg.lParam), GET_Y_LPARAM(refMsg.lParam)};
            return this->OnMouseLeftButtonDoubleClick(Point(mousePosition), (MouseKey)refMsg.wParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_RBUTTONDOWN: {
            POINT mousePosition{GET_X_LPARAM(refMsg.lParam), GET_Y_LPARAM(refMsg.lParam)};
            return this->OnMouseRightButtonDown(Point(mousePosition), (MouseKey)refMsg.wParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_RBUTTONUP: {
            POINT mousePosition{GET_X_LPARAM(refMsg.lParam), GET_Y_LPARAM(refMsg.lParam)};
            return this->OnMouseRightButtonUp(Point(mousePosition), (MouseKey)refMsg.wParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_RBUTTONDBLCLK: {
            POINT mousePosition{GET_X_LPARAM(refMsg.lParam), GET_Y_LPARAM(refMsg.lParam)};
            return this->OnMouseRightButtonDoubleClick(Point(mousePosition), (MouseKey)refMsg.wParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_MBUTTONDOWN: {
            POINT mousePosition{GET_X_LPARAM(refMsg.lParam), GET_Y_LPARAM(refMsg.lParam)};
            return this->OnMouseMiddleButtonDown(Point(mousePosition), (MouseKey)refMsg.wParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_MBUTTONUP: {
            POINT mousePosition{GET_X_LPARAM(refMsg.lParam), GET_Y_LPARAM(refMsg.lParam)};
            return this->OnMouseMiddleButtonUp(Point(mousePosition), (MouseKey)refMsg.wParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_MBUTTONDBLCLK: {
            POINT mousePosition{GET_X_LPARAM(refMsg.lParam), GET_Y_LPARAM(refMsg.lParam)};
            return this->OnMouseMiddleButtonDoubleClick(Point(mousePosition), (MouseKey)refMsg.wParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_CHAR: {
            return this->OnChar((wchar_t)refMsg.wParam, refMsg.lParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_DEADCHAR: {
            return this->OnDeadChar((wchar_t)refMsg.wParam, refMsg.lParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_KEYDOWN: {
            return this->OnKeyDown((VirtualKey)refMsg.wParam, refMsg.lParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_KEYUP: {
            return this->OnKeyUp((VirtualKey)refMsg.wParam, refMsg.lParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_SYSCHAR: {
            return this->OnSysChar((wchar_t)refMsg.wParam, refMsg.lParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_SYSDEADCHAR: {
            return this->OnSysDeadChar((wchar_t)refMsg.wParam, refMsg.lParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_SYSKEYDOWN: {
            return this->OnSysKeyDown((VirtualKey)refMsg.wParam, refMsg.lParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_SYSKEYUP: {
            return this->OnSysKeyUp((VirtualKey)refMsg.wParam, refMsg.lParam) ? 0 : this->DefaultWndProc(refMsg);
        }

        case WM_COMMAND: {
            this->OnCommand(refMsg.wParam, refMsg.lParam);
            return 0;
        }

        case WM_ParentReceivedCommand: {
            this->ParentReceivedCommand(HIWORD(refMsg.wParam));
            return 0;
        }

        case WM_CTLCOLORBTN:
        case WM_CTLCOLOREDIT:
        case WM_CTLCOLORDLG:
        case WM_CTLCOLORLISTBOX:
        case WM_CTLCOLORSCROLLBAR:
        case WM_CTLCOLORSTATIC: {
            HDC hdc              = (HDC)refMsg.wParam;
            HWND hwnd            = (HWND)refMsg.lParam;
            WndBase *pWnd        = WndBase::GetWndBase(hwnd);
            ICtlColor *pCtlColor = dynamic_cast<ICtlColor *>(pWnd);

            return pCtlColor == nullptr
                       ? this->DefaultWndProc(refMsg)
                       : pCtlColor->CtlColor(hdc, hwnd);
        }

        case WM_SETCURSOR: {
            HWND hwnd   = (HWND)refMsg.wParam;
            int hitTest = LOWORD(refMsg.lParam);
            int message = HIWORD(refMsg.lParam);

            bool useDefaultWndProc = true;

            bool result = this->OnSetCursor(hwnd, hitTest, message, useDefaultWndProc);
            return useDefaultWndProc ? this->DefaultWndProc(refMsg) : result;
        }

        default: {
            return this->DefaultWndProc(refMsg);
        }
    }
}

bool sw::WndBase::OnCreate()
{
    return true;
}

bool sw::WndBase::OnClose()
{
    DestroyWindow(this->_hwnd);
    return true;
}

bool sw::WndBase::OnDestroy()
{
    return true;
}

bool sw::WndBase::OnPaint()
{
    return false;
}

bool sw::WndBase::OnMove(Point newClientPosition)
{
    return true;
}

bool sw::WndBase::OnSize(Size newClientSize)
{
    return true;
}

bool sw::WndBase::OnSetText(std::wstring &newText)
{
    return true;
}

void sw::WndBase::OnTextChanged(const std::wstring &newText)
{
}

bool sw::WndBase::OnSetFocus(HWND hPrevFocus)
{
    return true;
}

bool sw::WndBase::OnKillFocus(HWND hNextFocus)
{
    return true;
}

bool sw::WndBase::OnMouseMove(Point mousePos, MouseKey keyState)
{
    return false;
}

bool sw::WndBase::OnMouseLeave()
{
    return false;
}

bool sw::WndBase::OnMouseWheel(int wheelDelta, Point mousePosition, MouseKey keyState)
{
    return false;
}

bool sw::WndBase::OnMouseLeftButtonDown(Point mousePos, MouseKey keyState)
{
    return false;
}

bool sw::WndBase::OnMouseLeftButtonUp(Point mousePos, MouseKey keyState)
{
    return false;
}

bool sw::WndBase::OnMouseLeftButtonDoubleClick(Point mousePos, MouseKey keyState)
{
    return false;
}

bool sw::WndBase::OnMouseRightButtonDown(Point mousePos, MouseKey keyState)
{
    return false;
}

bool sw::WndBase::OnMouseRightButtonUp(Point mousePos, MouseKey keyState)
{
    return false;
}

bool sw::WndBase::OnMouseRightButtonDoubleClick(Point mousePos, MouseKey keyState)
{
    return false;
}

bool sw::WndBase::OnMouseMiddleButtonDown(Point mousePos, MouseKey keyState)
{
    return false;
}

bool sw::WndBase::OnMouseMiddleButtonUp(Point mousePos, MouseKey keyState)
{
    return false;
}

bool sw::WndBase::OnMouseMiddleButtonDoubleClick(Point mousePos, MouseKey keyState)
{
    return false;
}

bool sw::WndBase::OnChar(wchar_t ch, KeyFlags flags)
{
    return false;
}

bool sw::WndBase::OnDeadChar(wchar_t ch, KeyFlags flags)
{
    return false;
}

bool sw::WndBase::OnKeyDown(VirtualKey key, KeyFlags flags)
{
    return false;
}

bool sw::WndBase::OnKeyUp(VirtualKey key, KeyFlags flags)
{
    return false;
}

bool sw::WndBase::OnSysChar(wchar_t ch, KeyFlags flags)
{
    return false;
}

bool sw::WndBase::OnSysDeadChar(wchar_t ch, KeyFlags flags)
{
    return false;
}

bool sw::WndBase::OnSysKeyDown(VirtualKey key, KeyFlags flags)
{
    return false;
}

bool sw::WndBase::OnSysKeyUp(VirtualKey key, KeyFlags flags)
{
    return false;
}

void sw::WndBase::VisibleChanged(bool newVisible)
{
}

bool sw::WndBase::SetParent(WndBase *parent)
{
    bool success;
    HWND hParent;

    if (parent == nullptr) {
        hParent = this->IsControl() ? _controlInitContainer : NULL;
    } else {
        hParent = parent->Handle;
    }

    success = ::SetParent(this->_hwnd, hParent) != NULL;

    if (success) {
        this->ParentChanged(parent);
    }

    return success;
}

void sw::WndBase::ParentChanged(WndBase *newParent)
{
}

void sw::WndBase::OnCommand(WPARAM wParam, LPARAM lParam)
{
    if (lParam != NULL) {
        // 接收到控件消息
        ::SendMessageW((HWND)lParam, WM_ParentReceivedCommand, wParam, lParam);
    } else {
        // Menu / Accelerator
        // ...
    }
}

void sw::WndBase::ParentReceivedCommand(int code)
{
}

void sw::WndBase::HandleInitialized(HWND hwnd)
{
}

void sw::WndBase::FontChanged(HFONT hfont)
{
}

bool sw::WndBase::OnSetCursor(HWND hwnd, int hitTest, int message, bool &useDefaultWndProc)
{
    return false;
}

void sw::WndBase::Show(int nCmdShow)
{
    ShowWindow(this->_hwnd, nCmdShow);
}

void sw::WndBase::Close()
{
    this->SendMessageW(WM_CLOSE, NULL, NULL);
}

void sw::WndBase::Update()
{
    UpdateWindow(this->_hwnd);
}

void sw::WndBase::UpdateFont()
{
    if (this->_hfont != NULL) {
        DeleteObject(this->_hfont);
    }
    this->_hfont = this->_font.CreateHandle();
    this->SendMessageW(WM_SETFONT, (WPARAM)this->_hfont, TRUE);
    this->FontChanged(this->_hfont);
}

void sw::WndBase::Redraw(bool erase)
{
    InvalidateRect(this->_hwnd, NULL, erase);
    UpdateWindow(this->_hwnd);
}

bool sw::WndBase::IsControl()
{
    return this->_controlOldWndProc != nullptr;
}

void sw::WndBase::MoveToTop()
{
    SetWindowPos(this->_hwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
}

void sw::WndBase::MoveToBottom()
{
    SetWindowPos(this->_hwnd, HWND_BOTTOM, 0, 0, 0, 0, SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOSIZE);
}

sw::Point sw::WndBase::PointToScreen(const Point &point)
{
    POINT p = point;
    ClientToScreen(this->_hwnd, &p);
    return p;
}

sw::Point sw::WndBase::PointFromScreen(const Point &screenPoint)
{
    POINT p = screenPoint;
    ScreenToClient(this->_hwnd, &p);
    return p;
}

LRESULT sw::WndBase::SendMessageW(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return ::SendMessageW(this->_hwnd, uMsg, wParam, lParam);
}

sw::WndBase *sw::WndBase::GetWndBase(HWND hwnd)
{
    return reinterpret_cast<WndBase *>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
}

bool sw::operator==(const WndBase &left, const WndBase &right)
{
    return &left == &right;
}

bool sw::operator!=(const WndBase &left, const WndBase &right)
{
    return &left != &right;
}
