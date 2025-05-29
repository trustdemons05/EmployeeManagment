#include "employee_management.h"

/* Custom colors for dark theme */
COLORREF backgroundColor = RGB(24, 24, 24); /* Main background */
COLORREF headerColor = RGB(24, 24, 24);     /* Header background */
COLORREF buttonColor = RGB(0, 122, 204);    /* Blue buttons */
COLORREF buttonHoverColor = RGB(0, 102, 184); /* Darker blue on hover */
COLORREF buttonTextColor = RGB(255, 255, 255); /* White text */
COLORREF editBackgroundColor = RGB(40, 40, 40); /* Input fields */
COLORREF editTextColor = RGB(255, 255, 255);    /* White text */
COLORREF labelTextColor = RGB(255, 255, 255);   /* White labels */
COLORREF listviewBackgroundColor = RGB(32, 32, 32); /* ListView background */
COLORREF listviewTextColor = RGB(255, 255, 255);    /* ListView text */
COLORREF listviewGridColor = RGB(0, 122, 204);      /* Blue grid lines */

/* Global variables */
Employee employees[MAX_EMPLOYEES];
int employeeCount = 0;
HWND hListView;
HWND hIdEdit, hNameEdit, hSalaryEdit, hDeptEdit, hPosEdit;
HFONT hFont, hBoldFont;
HBRUSH hBackgroundBrush, hHeaderBrush;
BOOL isButtonHovered = FALSE;
int hoveredButtonId = 0;

void CreateModernButton(HWND hwnd, const wchar_t* text, int x, int y, int width, int height, int id) {
    HWND hButton = CreateWindowW(
        L"BUTTON",
        text,
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        x, y, width, height,
        hwnd,
        (HMENU)id,
        NULL,
        NULL
    );
    SendMessage(hButton, WM_SETFONT, (WPARAM)hFont, TRUE);
    /* Set white text for button */
    SetWindowTheme(hButton, L"", L"");
}

void CreateModernLabel(HWND hwnd, const wchar_t* text, int x, int y, int width, int height) {
    HWND hLabel = CreateWindowW(
        L"STATIC",
        text,
        WS_CHILD | WS_VISIBLE | SS_LEFT,
        x, y, width, height,
        hwnd,
        NULL,
        NULL,
        NULL
    );
    SendMessage(hLabel, WM_SETFONT, (WPARAM)hFont, TRUE);
}

void InitializeListView(HWND hwnd) {
    LVCOLUMNW lvc;
    lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

    /* Add columns */
    lvc.iSubItem = 0;
    lvc.pszText = (LPWSTR)L"ID";
    lvc.cx = 50;
    ListView_InsertColumn(hListView, 0, &lvc);

    lvc.iSubItem = 1;
    lvc.pszText = (LPWSTR)L"Name";
    lvc.cx = 200;
    ListView_InsertColumn(hListView, 1, &lvc);

    lvc.iSubItem = 2;
    lvc.pszText = (LPWSTR)L"Salary";
    lvc.cx = 100;
    ListView_InsertColumn(hListView, 2, &lvc);

    lvc.iSubItem = 3;
    lvc.pszText = (LPWSTR)L"Department";
    lvc.cx = 150;
    ListView_InsertColumn(hListView, 3, &lvc);

    lvc.iSubItem = 4;
    lvc.pszText = (LPWSTR)L"Position";
    lvc.cx = 200;
    ListView_InsertColumn(hListView, 4, &lvc);

    /* Set ListView background and text color */
    ListView_SetBkColor(hListView, listviewBackgroundColor);
    ListView_SetTextColor(hListView, listviewTextColor);
    ListView_SetTextBkColor(hListView, listviewBackgroundColor); /* Ensure all rows are dark */
    ListView_SetExtendedListViewStyle(hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_DOUBLEBUFFER);
}

void AddEmployeeToListView(Employee* emp) {
    LVITEM lvi = { 0 };
    wchar_t buffer[50];

    lvi.mask = LVIF_TEXT;
    lvi.iItem = ListView_GetItemCount(hListView);

    /* ID */
    wsprintfW(buffer, L"%d", emp->id);
    lvi.iSubItem = 0;
    lvi.pszText = buffer;
    ListView_InsertItem(hListView, &lvi);

    /* Name */
    lvi.iSubItem = 1;
    lvi.pszText = emp->name;
    ListView_SetItem(hListView, &lvi);

    /* Salary */
    wsprintfW(buffer, L"%.2f", emp->salary);
    lvi.iSubItem = 2;
    lvi.pszText = buffer;
    ListView_SetItem(hListView, &lvi);

    /* Department */
    lvi.iSubItem = 3;
    lvi.pszText = emp->department;
    ListView_SetItem(hListView, &lvi);

    /* Position */
    lvi.iSubItem = 4;
    lvi.pszText = emp->position;
    ListView_SetItem(hListView, &lvi);
}

void RefreshListView(void) {
    ListView_DeleteAllItems(hListView);
    for (int i = 0; i < employeeCount; i++) {
        AddEmployeeToListView(&employees[i]);
    }
}

void ClearInputFields(void) {
    SetWindowTextW(hIdEdit, L"");
    SetWindowTextW(hNameEdit, L"");
    SetWindowTextW(hSalaryEdit, L"");
    SetWindowTextW(hDeptEdit, L"");
    SetWindowTextW(hPosEdit, L"");
} 