#include "GUIInterface.h"
#include "Funcions.h"
#include "Point.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Line.h"
#include "Triangle.h"
#include "Rectangle.h"
#include <vector>
#include <cassert>
#include <algorithm>


namespace KHAS {


    GUIInterface::GUIInterface(long width, long height)
        : hwnd_(GetConsoleWindow())
        , hdc_(GetDC(hwnd_))
        , window_rect_({ 0l, 0l, width, height })
        , drawing_rect_()
        , header_rect_()
        , menu_rect_()
        , text_metric_()
        , drawing_section_background_color_(Functions::rgbToCOLORREF(180, 200, 200))
        , rest_section_background_color_(Functions::rgbToCOLORREF(160, 180, 180))
        , rest_section_text_color_(Functions::rgbToCOLORREF(10, 30, 80))
        , top_offset_(39)
        , right_offset_(16)
        , active_figure_(MenuItems::Empty)
        , move_type_(MoveTypes::Empty)
    {
        GetTextMetrics(hdc_, &text_metric_);
        setWindowPosition();
        setBufferWindowSize();
        hideCursor();
        disableSelectionInConsole();
        deletePropertiesFromSystemMenu();
        updateStyleWindow();

        GetClientRect(hwnd_, &window_rect_);

        assert(window_rect_.bottom >= (180 + 280 - top_offset_));
        assert(window_rect_.right >= (640 - right_offset_));

        header_rect_ = RECT{ 0, 0, window_rect_.right, 180 };
        menu_rect_ = RECT{ 0, window_rect_.bottom - 180, window_rect_.right,window_rect_.bottom };

        drawing_rect_ = RECT{ 0, header_rect_.bottom, window_rect_.right,menu_rect_.top };

    }

    inline bool GUIInterface::isKeyDown(int key) const
    {
        return (GetKeyState(key) & 0x8000) != 0;
    }

    inline bool GUIInterface::isKeyUp(int key) const
    {
        bool ret{};
        while ((GetKeyState(key) & 0x8000) != 0) {
            Sleep(10);
            ret = true;
        }
        return ret;
    }

    void GUIInterface::hideCursor() const
    {
        HANDLE handle{ GetStdHandle(STD_OUTPUT_HANDLE) };
        CONSOLE_CURSOR_INFO structCursorInfo;
        GetConsoleCursorInfo(handle, &structCursorInfo);
        if (structCursorInfo.bVisible) {
            structCursorInfo.bVisible = false;
            SetConsoleCursorInfo(handle, &structCursorInfo);
        }
    }

    void GUIInterface::setWindowPosition() const
    {
        HANDLE handle{ GetStdHandle(STD_OUTPUT_HANDLE) };
        auto width{ window_rect_.right - window_rect_.left };
        auto height{ window_rect_.bottom - window_rect_.top };

        auto window_pos_x{ (GetSystemMetrics(SM_CXSCREEN) >> 1) - (width >> 1) };
        auto window_pos_y{ (GetSystemMetrics(SM_CYSCREEN) >> 1) - (height >> 1) };
        MoveWindow(hwnd_, window_pos_x, window_pos_y, width, height, TRUE);
    }

    void GUIInterface::setBufferWindowSize() const
    {
        CONSOLE_SCREEN_BUFFER_INFO csi;
        GetConsoleScreenBufferInfo(hwnd_, &csi);
        short y{ csi.srWindow.Bottom - csi.srWindow.Top + 1 };
        SetConsoleScreenBufferSize(hwnd_, { csi.dwSize.X, y });
    }

    void GUIInterface::updateStyleWindow() const
    {
        LONG_PTR style_ptr{ SetWindowLongPtr(hwnd_, GWL_STYLE
            , WS_SIZEBOX & ~WS_THICKFRAME | WS_MINIMIZEBOX | WS_SYSMENU | WS_CAPTION) };
        SetWindowPos(hwnd_, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);
        ShowWindow(hwnd_, SW_SHOW);
    }

    void GUIInterface::disableSelectionInConsole() const
    {
        HANDLE hConsole{ GetStdHandle(STD_INPUT_HANDLE) };
        DWORD prevConsoleMode{};
        GetConsoleMode(hConsole, &prevConsoleMode);
        SetConsoleMode(hConsole, ENABLE_EXTENDED_FLAGS |
            (prevConsoleMode & ~ENABLE_QUICK_EDIT_MODE));
    }
        
    void GUIInterface::deletePropertiesFromSystemMenu() const
    {
        HMENU hMenu{ GetSystemMenu(hwnd_, false) };
        DeleteMenu(hMenu, GetMenuItemCount(hMenu) - 1, MF_BYPOSITION);
        DeleteMenu(hMenu, GetMenuItemCount(hMenu) - 1, MF_BYPOSITION);
        DeleteMenu(hMenu, GetMenuItemCount(hMenu) - 1, MF_BYPOSITION);
        DeleteMenu(hMenu, 0, MF_BYPOSITION);
        DeleteMenu(hMenu, 1, MF_BYPOSITION);
        DeleteMenu(hMenu, 2, MF_BYPOSITION);
    }

    void GUIInterface::showHeader(const HDC& hdc) const
    {
        assert(hdc != NULL);

        fillRect(hdc, header_rect_, rest_section_background_color_);

        std::vector<std::wstring> base{
            { joinToString(L"Дисциплина:", delimiter(20), L"Объектно-ориентированное программирование")}
            , { joinToString(L"Лабораторная работа:", delimiter(5), L"№ 3") }
            , { joinToString(L"Вариант:", delimiter(27), L"№1") }
            , { joinToString(L"Тема:", delimiter(32), L"Принцип полиморфизма.") }
            , { joinToString(delimiter(42), L"Использование виртуальных методов.") }
            , { joinToString(L"Студент:", delimiter(27), L"Хакимов А.С.") }
            , { joinToString(L"Группа:", delimiter(29), L"ПБ-11") }
        };


        SetBkMode(hdc, TRANSPARENT);
        SelectObject(hdc, GetStockObject(DC_PEN));
        SetTextColor(hdc, rest_section_text_color_);
        {
            int step{ 10 };
            auto del{ delimiter(78, '=') };
            TextOut(hdc, 0, step, del.c_str(), static_cast<int>(del.length()));
            for (auto&& elem : base) {
                TextOut(hdc, 100, (step += 20), elem.c_str(), static_cast<int>(elem.length()));
            }

            TextOut(hdc, 0, step + 20, del.c_str(), static_cast<int>(del.length()));
        }
        
    }

    void GUIInterface::showMenuFigureSelected(const HDC& hdc)
    {
        fillRect(hdc, menu_rect_, rest_section_background_color_);

        static std::vector<std::pair<MenuItems, std::wstring>> base{
            { MenuItems::Point, L"Точка" }
            , { MenuItems::Circle, L"Окружность" }
            , { MenuItems::Ellipse, L"Эллипс" }
            , { MenuItems::Line, L"Отрезок" }
            , { MenuItems::Triangle, L"Треугольник" }
            , { MenuItems::Rectangle, L"Прямоугольник" }
        };

        static auto iter{ base.begin() };

        drawMenu(base, hdc, iter->first);

        if (isKeyUp(VK_DOWN)) {
            ++iter;
            if (iter == base.end()) iter = base.end() - 1;
        }
        else if (isKeyUp(VK_UP)) {
            if (iter == base.begin()) return;
            --iter;
        }

        if (isKeyUp(VK_RETURN)) {
            active_figure_ = iter->first;
            iter = base.begin();
        }
    }

    void GUIInterface::showMenuMoveTypes(const HDC& hdc)
    {
        fillRect(hdc, menu_rect_, rest_section_background_color_);

        static std::vector<std::pair<MoveTypes, std::wstring>> base{
            { MoveTypes::Random, L"Случайное движение" }
            , { MoveTypes::Movement, L"Ручное движение" }
            , { MoveTypes::Back, L"Выход на главную" }
        };

        static auto iter{ base.begin() };

        drawMenu(base, hdc, iter->first);

        if (isKeyUp(VK_DOWN)) {
            ++iter;
            if (iter == base.end()) iter = base.end() - 1;
        }
        else if (isKeyUp(VK_UP)) {
            if (iter == base.begin()) return;
            --iter;
        }
        else if (isKeyUp(VK_ESCAPE)) active_figure_ = MenuItems::Empty;
        else if (isKeyUp(VK_RETURN)) {
            move_type_ = iter->first;
            iter = base.begin();
        }

    }

    void GUIInterface::showDraw(const HDC& hdc)
    {
        if (move_type_ == MoveTypes::Back) {
            active_figure_ = MenuItems::Empty;
            move_type_ = MoveTypes::Empty;
            return;
        }

        switch (active_figure_)
        {
        case KHAS::MenuItems::Point:        objectDraw<Point>(hdc);         break;
        case KHAS::MenuItems::Circle:       objectDraw<Circle>(hdc);        break;
        case KHAS::MenuItems::Ellipse:      objectDraw<MyEllipse>(hdc);     break;
        case KHAS::MenuItems::Line:         objectDraw<Line>(hdc);          break;
        case KHAS::MenuItems::Triangle:     objectDraw<Triangle>(hdc);      break;
        case KHAS::MenuItems::Rectangle:    objectDraw<MyRectangle>(hdc);   break;
        case KHAS::MenuItems::Empty:                                        break;
        }


        fillRect(hdc, menu_rect_, rest_section_background_color_);

        static std::vector<std::pair<DrawMenuItems, std::wstring>> base{
            { DrawMenuItems::Back, L"Вернуться назад" }
            , { DrawMenuItems::Exit, L"Выход на главную" }
        };
        static auto iter{ base.begin() };

        drawMenu(base, hdc, iter->first);

        std::wstring description{ L"Для управления кнопками меню, нажмите CTRL и стрелку вврехр или вниз." };
        TextOut(hdc, 40, menu_rect_.bottom - 50, description.c_str(), static_cast<int>(description.length()));

        if (isKeyDown(VK_CONTROL) && isKeyUp(VK_DOWN)) {
            ++iter;
            if (iter == base.end()) iter = base.end() - 1;
        }
        else if (isKeyDown(VK_CONTROL) && isKeyUp(VK_UP)) {
            if (iter == base.begin()) return;
            --iter;
        }
        else if (isKeyUp(VK_RETURN)) {
            if (iter->first == DrawMenuItems::Back) move_type_ = MoveTypes::Empty;
            else if (iter->first == DrawMenuItems::Exit) {
                move_type_ = MoveTypes::Empty;
                active_figure_ = MenuItems::Empty;
            };
            iter = base.begin();
        }
    }

    void GUIInterface::fillRect(const HDC& hdc, const RECT& rect, COLORREF color) const
    {
        HBRUSH solidBrush{ CreateSolidBrush(color) };
        assert(solidBrush != NULL);
        auto fillRect{ FillRect(hdc, &rect, solidBrush) };
        assert( fillRect != 0);
        DeleteObject(solidBrush);
    }

    constexpr std::wstring GUIInterface::delimiter(size_t lenght, char del) const
    {
        return std::wstring(lenght, del);
    }

    
    void GUIInterface::loop()
    {        

        while (true) {
            
            HDC memDC{ CreateCompatibleDC(hdc_) };
            assert(memDC != NULL);
            auto width{ window_rect_.right - window_rect_.left };
            auto height{ window_rect_.bottom - window_rect_.top };

            HBITMAP memBM{ CreateCompatibleBitmap(hdc_, width, height) };
            assert(memBM != NULL);

            SelectObject(memDC, memBM);
            HBRUSH drawingSolidBrush{ CreateSolidBrush(drawing_section_background_color_) };
            assert(drawingSolidBrush != NULL);

            auto fill{ FillRect(memDC, &window_rect_, drawingSolidBrush) };
            assert(fill != 0);
            /*//////////////////////////////////*/
            
            if (active_figure_ == MenuItems::Empty) showMenuFigureSelected(memDC);
            else if (move_type_ == MoveTypes::Empty) showMenuMoveTypes(memDC);
            else showDraw(memDC);

            showHeader(memDC);
            /*/////////////////////////////////*/

            BitBlt(hdc_, 0, 0, width, height, memDC, 0, 0, SRCCOPY);
            DeleteObject(drawingSolidBrush);
            DeleteObject(memBM);
            DeleteDC(memDC);

            Sleep(50);
        }
    }


}