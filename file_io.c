#include "employee_management.h"

void ExportToCSV(void) {
    FILE* file;
    if (_wfopen_s(&file, L"employees.csv", L"w") != 0) {
        MessageBoxW(NULL, L"Could not create export file!", L"Error", MB_ICONERROR);
        return;
    }

    /* Write header */
    fwprintf(file, L"ID,Name,Salary,Department,Position\n");

    /* Write data */
    for (int i = 0; i < employeeCount; i++) {
        fwprintf(file, L"%d,%s,%.2f,%s,%s\n",
            employees[i].id,
            employees[i].name,
            employees[i].salary,
            employees[i].department,
            employees[i].position);
    }

    fclose(file);
    MessageBoxW(NULL, L"Data exported successfully to employees.csv!", L"Success", MB_ICONINFORMATION);
}

void ImportFromCSV(void) {
    FILE* file;
    if (_wfopen_s(&file, L"employees.csv", L"r") != 0) {
        MessageBoxW(NULL, L"Could not open import file!", L"Error", MB_ICONERROR);
        return;
    }

    wchar_t line[1024];
    /* Skip header */
    fgetws(line, sizeof(line) / sizeof(wchar_t), file);

    employeeCount = 0;
    while (fgetws(line, sizeof(line) / sizeof(wchar_t), file) && employeeCount < MAX_EMPLOYEES) {
        /* Remove trailing newline */
        size_t len = wcslen(line);
        if (len > 0 && (line[len - 1] == L'\n' || line[len - 1] == L'\r')) line[len - 1] = 0;
        if (len > 1 && (line[len - 2] == L'\r')) line[len - 2] = 0;
        if (wcslen(line) == 0) continue; /* skip empty lines */
        wchar_t* context = NULL;
        wchar_t* token = wcstok_s(line, L",", &context);
        if (token == NULL) continue;
        employees[employeeCount].id = _wtoi(token);

        token = wcstok_s(NULL, L",", &context);
        if (token == NULL) continue;
        wcscpy_s(employees[employeeCount].name, MAX_NAME_LENGTH, token);

        token = wcstok_s(NULL, L",", &context);
        if (token == NULL) continue;
        employees[employeeCount].salary = (float)_wtof(token);

        token = wcstok_s(NULL, L",", &context);
        if (token == NULL) continue;
        wcscpy_s(employees[employeeCount].department, MAX_NAME_LENGTH, token);

        token = wcstok_s(NULL, L",", &context);
        if (token == NULL) continue;
        wcscpy_s(employees[employeeCount].position, MAX_NAME_LENGTH, token);

        employeeCount++;
    }

    fclose(file);
    RefreshListView();
    MessageBoxW(NULL, L"Data imported successfully from employees.csv!", L"Success", MB_ICONINFORMATION);
} 