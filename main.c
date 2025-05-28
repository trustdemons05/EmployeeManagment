#include "employee_management.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
    /* Initialize Common Controls */
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_LISTVIEW_CLASSES | ICC_BAR_CLASSES;
    InitCommonControlsEx(&icex);

    /* Create fonts */
    hFont = CreateFont(16, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");

    hBoldFont = CreateFont(16, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE,
        DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
        CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Segoe UI");

    /* Create brushes */
    hBackgroundBrush = CreateSolidBrush(backgroundColor);
    hHeaderBrush = CreateSolidBrush(headerColor);

    /* Register the window class */
    const wchar_t CLASS_NAME[] = L"Employee Management System";

    WNDCLASSW wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = hBackgroundBrush;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    RegisterClassW(&wc);

    /* Create the main window */
    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Employee Management System",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1200, 800,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    /* Message loop */
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    /* Cleanup */
    DeleteObject(hFont);
    DeleteObject(hBoldFont);
    DeleteObject(hBackgroundBrush);
    DeleteObject(hHeaderBrush);

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        /* Create header */
        HWND hHeader = CreateWindowExW(
            0,
            L"STATIC",
            L"Employee Management System",
            WS_CHILD | WS_VISIBLE | SS_CENTER,
            0, 0, 1200, 40,
            hwnd,
            NULL,
            NULL,
            NULL
        );
        SendMessage(hHeader, WM_SETFONT, (WPARAM)hBoldFont, TRUE);
        HDC hdc = GetDC(hHeader);
        SetTextColor(hdc, RGB(255, 255, 255));
        ReleaseDC(hHeader, hdc);

        /* Create ListView with modern style */
        hListView = CreateWindowExW(
            WS_EX_CLIENTEDGE,
            WC_LISTVIEWW,
            L"",
            WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS,
            20, 60, 1140, 400,
            hwnd,
            (HMENU)ID_LISTVIEW,
            NULL,
            NULL
        );

        /* Set ListView font and style */
        SendMessage(hListView, WM_SETFONT, (WPARAM)hFont, TRUE);
        ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

        /* Create input fields with modern style */
        CreateModernLabel(hwnd, L"Employee ID:", 20, 480, 100, 25);
        hIdEdit = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
            130, 480, 150, 25, hwnd, (HMENU)ID_ID_EDIT, NULL, NULL);

        CreateModernLabel(hwnd, L"Name:", 300, 480, 100, 25);
        hNameEdit = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
            410, 480, 250, 25, hwnd, (HMENU)ID_NAME_EDIT, NULL, NULL);

        CreateModernLabel(hwnd, L"Salary:", 680, 480, 100, 25);
        hSalaryEdit = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
            790, 480, 150, 25, hwnd, (HMENU)ID_SALARY_EDIT, NULL, NULL);

        CreateModernLabel(hwnd, L"Department:", 20, 520, 100, 25);
        hDeptEdit = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
            130, 520, 250, 25, hwnd, (HMENU)ID_DEPT_EDIT, NULL, NULL);

        CreateModernLabel(hwnd, L"Position:", 400, 520, 100, 25);
        hPosEdit = CreateWindowExW(WS_EX_CLIENTEDGE, L"EDIT", L"",
            WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
            510, 520, 250, 25, hwnd, (HMENU)ID_POS_EDIT, NULL, NULL);

        /* Create modern buttons */
        CreateModernButton(hwnd, L"Add Employee", 20, 560, 120, 35, ID_ADD_BUTTON);
        CreateModernButton(hwnd, L"Update", 150, 560, 120, 35, ID_UPDATE_BUTTON);
        CreateModernButton(hwnd, L"Delete", 280, 560, 120, 35, ID_DELETE_BUTTON);
        CreateModernButton(hwnd, L"Search", 410, 560, 120, 35, ID_SEARCH_BUTTON);
        CreateModernButton(hwnd, L"Clear", 540, 560, 120, 35, ID_CLEAR_BUTTON);
        CreateModernButton(hwnd, L"Export to CSV", 670, 560, 120, 35, ID_EXPORT_BUTTON);
        CreateModernButton(hwnd, L"Import from CSV", 800, 560, 120, 35, ID_IMPORT_BUTTON);

        /* Set fonts for all controls */
        HWND controls[] = { hIdEdit, hNameEdit, hSalaryEdit, hDeptEdit, hPosEdit };
        for (int i = 0; i < 5; i++) {
            SendMessage(controls[i], WM_SETFONT, (WPARAM)hFont, TRUE);
        }

        InitializeListView(hwnd);
        break;
    }

    case WM_SIZE: {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        /* Header */
        HWND hHeader = FindWindowEx(hwnd, NULL, L"STATIC", NULL);
        MoveWindow(hHeader, 0, 0, width, 40, TRUE);
        /* ListView */
        MoveWindow(hListView, 20, 60, width - 40, height - 320, TRUE);
        /* Input fields and labels */
        int inputY = height - 240;
        int labelW = 100, labelH = 25, editH = 25, spacing = 10;
        int fieldW = (width - 60 - 4 * labelW - 3 * spacing) / 4;
        /* Employee ID */
        MoveWindow(hIdEdit, 20 + labelW, inputY, fieldW, editH, TRUE);
        /* Name */
        MoveWindow(hNameEdit, 20 + labelW + fieldW + labelW + spacing, inputY, fieldW, editH, TRUE);
        /* Salary */
        MoveWindow(hSalaryEdit, 20 + labelW + 2 * (fieldW + labelW + spacing), inputY, fieldW, editH, TRUE);
        /* Department */
        MoveWindow(hDeptEdit, 20 + labelW, inputY + 40, fieldW, editH, TRUE);
        /* Position */
        MoveWindow(hPosEdit, 20 + labelW + fieldW + labelW + spacing, inputY + 40, fieldW, editH, TRUE);
        /* Labels */
        HWND hLabel;
        hLabel = FindWindowEx(hwnd, NULL, L"STATIC", L"Employee ID:");
        MoveWindow(hLabel, 20, inputY, labelW, labelH, TRUE);
        hLabel = FindWindowEx(hwnd, hLabel, L"STATIC", L"Name:");
        MoveWindow(hLabel, 20 + labelW + fieldW + spacing, inputY, labelW, labelH, TRUE);
        hLabel = FindWindowEx(hwnd, hLabel, L"STATIC", L"Salary:");
        MoveWindow(hLabel, 20 + 2 * (labelW + fieldW + spacing), inputY, labelW, labelH, TRUE);
        hLabel = FindWindowEx(hwnd, hLabel, L"STATIC", L"Department:");
        MoveWindow(hLabel, 20, inputY + 40, labelW, labelH, TRUE);
        hLabel = FindWindowEx(hwnd, hLabel, L"STATIC", L"Position:");
        MoveWindow(hLabel, 20 + labelW + fieldW + spacing, inputY + 40, labelW, labelH, TRUE);
        /* Buttons */
        int btnW = (width - 60) / 7, btnH = 35, btnY = height - 80;
        HWND hBtn;
        hBtn = GetDlgItem(hwnd, ID_ADD_BUTTON);
        MoveWindow(hBtn, 20, btnY, btnW, btnH, TRUE);
        hBtn = GetDlgItem(hwnd, ID_UPDATE_BUTTON);
        MoveWindow(hBtn, 20 + btnW, btnY, btnW, btnH, TRUE);
        hBtn = GetDlgItem(hwnd, ID_DELETE_BUTTON);
        MoveWindow(hBtn, 20 + 2 * btnW, btnY, btnW, btnH, TRUE);
        hBtn = GetDlgItem(hwnd, ID_SEARCH_BUTTON);
        MoveWindow(hBtn, 20 + 3 * btnW, btnY, btnW, btnH, TRUE);
        hBtn = GetDlgItem(hwnd, ID_CLEAR_BUTTON);
        MoveWindow(hBtn, 20 + 4 * btnW, btnY, btnW, btnH, TRUE);
        hBtn = GetDlgItem(hwnd, ID_EXPORT_BUTTON);
        MoveWindow(hBtn, 20 + 5 * btnW, btnY, btnW, btnH, TRUE);
        hBtn = GetDlgItem(hwnd, ID_IMPORT_BUTTON);
        MoveWindow(hBtn, 20 + 6 * btnW, btnY, btnW, btnH, TRUE);
        break;
    }

    case WM_CTLCOLORSTATIC: {
        HDC hdcStatic = (HDC)wParam;
        SetTextColor(hdcStatic, labelTextColor);
        SetBkColor(hdcStatic, backgroundColor);
        return (LRESULT)hBackgroundBrush;
    }

    case WM_CTLCOLOREDIT: {
        HDC hdcEdit = (HDC)wParam;
        SetTextColor(hdcEdit, editTextColor);
        SetBkColor(hdcEdit, editBackgroundColor);
        return (LRESULT)CreateSolidBrush(editBackgroundColor);
    }

    case WM_CTLCOLORBTN: {
        HDC hdcBtn = (HDC)wParam;
        SetTextColor(hdcBtn, buttonTextColor);
        SetBkColor(hdcBtn, buttonColor);
        return (LRESULT)CreateSolidBrush(buttonColor);
    }

    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case ID_ADD_BUTTON:
            AddEmployee();
            break;
        case ID_UPDATE_BUTTON:
            UpdateEmployee();
            break;
        case ID_DELETE_BUTTON:
            DeleteEmployee();
            break;
        case ID_SEARCH_BUTTON:
            SearchEmployee();
            break;
        case ID_CLEAR_BUTTON: {
            int result = MessageBoxW(hwnd, L"Are you sure you want to clear all employee records? This cannot be undone.", L"Confirm Clear", MB_ICONWARNING | MB_YESNO);
            if (result == IDYES) {
                ClearAllRecords();
            }
            ClearInputFields();
            break;
        }
        case ID_EXPORT_BUTTON:
            ExportToCSV();
            break;
        case ID_IMPORT_BUTTON:
            ImportFromCSV();
            break;
        }
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
} 