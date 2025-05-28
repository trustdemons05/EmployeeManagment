#ifndef EMPLOYEE_MANAGEMENT_H
#define EMPLOYEE_MANAGEMENT_H

#define _WIN32_IE 0x0600
#define _WIN32_WINNT 0x0600
#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uxtheme.h>
#include <vssym32.h>
#include <windowsx.h>

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "uxtheme.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#define MAX_EMPLOYEES 100
#define MAX_NAME_LENGTH 50

/* Control IDs */
#define ID_ADD_BUTTON 1
#define ID_UPDATE_BUTTON 2
#define ID_DELETE_BUTTON 3
#define ID_SEARCH_BUTTON 4
#define ID_LISTVIEW 5
#define ID_ID_EDIT 6
#define ID_NAME_EDIT 7
#define ID_SALARY_EDIT 8
#define ID_DEPT_EDIT 9
#define ID_POS_EDIT 10
#define ID_CLEAR_BUTTON 11
#define ID_EXPORT_BUTTON 12
#define ID_IMPORT_BUTTON 13

/* Custom colors for dark theme */
extern COLORREF backgroundColor;
extern COLORREF headerColor;
extern COLORREF buttonColor;
extern COLORREF buttonHoverColor;
extern COLORREF buttonTextColor;
extern COLORREF editBackgroundColor;
extern COLORREF editTextColor;
extern COLORREF labelTextColor;
extern COLORREF listviewBackgroundColor;
extern COLORREF listviewTextColor;
extern COLORREF listviewGridColor;

/* Structure to store employee information */
typedef struct {
    int id;
    wchar_t name[MAX_NAME_LENGTH];
    float salary;
    wchar_t department[MAX_NAME_LENGTH];
    wchar_t position[MAX_NAME_LENGTH];
} Employee;

/* Global variables */
extern Employee employees[MAX_EMPLOYEES];
extern int employeeCount;
extern HWND hListView;
extern HWND hIdEdit, hNameEdit, hSalaryEdit, hDeptEdit, hPosEdit;
extern HFONT hFont, hBoldFont;
extern HBRUSH hBackgroundBrush, hHeaderBrush;
extern BOOL isButtonHovered;
extern int hoveredButtonId;

/* Function prototypes */
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void InitializeListView(HWND hwnd);
void AddEmployeeToListView(Employee* emp);
void RefreshListView(void);
void AddEmployee(void);
void UpdateEmployee(void);
void DeleteEmployee(void);
void SearchEmployee(void);
void ClearInputFields(void);
void CreateModernButton(HWND hwnd, const wchar_t* text, int x, int y, int width, int height, int id);
void CreateModernLabel(HWND hwnd, const wchar_t* text, int x, int y, int width, int height);
void ExportToCSV(void);
void ImportFromCSV(void);
void ClearAllRecords(void);

#endif /* EMPLOYEE_MANAGEMENT_H */ 