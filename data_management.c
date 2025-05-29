#include "employee_management.h"

void AddEmployee(void) {
    if (employeeCount >= MAX_EMPLOYEES) {
        MessageBoxW(NULL, L"Maximum employee limit reached!", L"Error", MB_ICONERROR);
        return;
    }

    wchar_t idStr[20], nameStr[MAX_NAME_LENGTH], salaryStr[20], deptStr[MAX_NAME_LENGTH], posStr[MAX_NAME_LENGTH];

    GetWindowTextW(hIdEdit, idStr, 20);
    GetWindowTextW(hNameEdit, nameStr, MAX_NAME_LENGTH);
    GetWindowTextW(hSalaryEdit, salaryStr, 20);
    GetWindowTextW(hDeptEdit, deptStr, MAX_NAME_LENGTH);
    GetWindowTextW(hPosEdit, posStr, MAX_NAME_LENGTH);

    int id = _wtoi(idStr);
    float salary = (float)_wtof(salaryStr);

    /* Validate input */
    if (id <= 0 || wcslen(nameStr) == 0 || salary <= 0 || wcslen(deptStr) == 0 || wcslen(posStr) == 0) {
        MessageBoxW(NULL, L"Please fill all fields with valid data!", L"Error", MB_ICONERROR);
        return;
    }

    /* Check if ID exists */
    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == id) {
            MessageBoxW(NULL, L"Employee ID already exists!", L"Error", MB_ICONERROR);
            return;
        }
    }

    /* Add new employee */
    Employee newEmp = { id, L"", salary, L"", L"" };
    wcscpy_s(newEmp.name, MAX_NAME_LENGTH, nameStr);
    wcscpy_s(newEmp.department, MAX_NAME_LENGTH, deptStr);
    wcscpy_s(newEmp.position, MAX_NAME_LENGTH, posStr);

    employees[employeeCount++] = newEmp;
    AddEmployeeToListView(&newEmp);
    ClearInputFields();

    MessageBoxW(NULL, L"Employee added successfully!", L"Success", MB_ICONINFORMATION);
}

void UpdateEmployee(void) {
    wchar_t idStr[20];
    GetWindowTextW(hIdEdit, idStr, 20);
    int id = _wtoi(idStr);

    if (id <= 0) {
        MessageBoxW(NULL, L"Please enter a valid ID!", L"Error", MB_ICONERROR);
        return;
    }

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == id) {
            wchar_t nameStr[MAX_NAME_LENGTH], salaryStr[20], deptStr[MAX_NAME_LENGTH], posStr[MAX_NAME_LENGTH];

            GetWindowTextW(hNameEdit, nameStr, MAX_NAME_LENGTH);
            GetWindowTextW(hSalaryEdit, salaryStr, 20);
            GetWindowTextW(hDeptEdit, deptStr, MAX_NAME_LENGTH);
            GetWindowTextW(hPosEdit, posStr, MAX_NAME_LENGTH);

            float salary = (float)_wtof(salaryStr);

            if (wcslen(nameStr) == 0 || salary <= 0 || wcslen(deptStr) == 0 || wcslen(posStr) == 0) {
                MessageBoxW(NULL, L"Please fill all fields with valid data!", L"Error", MB_ICONERROR);
                return;
            }

            wcscpy_s(employees[i].name, MAX_NAME_LENGTH, nameStr);
            employees[i].salary = salary;
            wcscpy_s(employees[i].department, MAX_NAME_LENGTH, deptStr);
            wcscpy_s(employees[i].position, MAX_NAME_LENGTH, posStr);

            RefreshListView();
            ClearInputFields();
            MessageBoxW(NULL, L"Employee updated successfully!", L"Success", MB_ICONINFORMATION);
            return;
        }
    }

    MessageBoxW(NULL, L"Employee not found!", L"Error", MB_ICONERROR);
}

void DeleteEmployee(void) {
    wchar_t idStr[20];
    GetWindowTextW(hIdEdit, idStr, 20);
    int id = _wtoi(idStr);

    if (id <= 0) {
        MessageBoxW(NULL, L"Please enter a valid ID!", L"Error", MB_ICONERROR);
        return;
    }

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == id) {
            /* Shift remaining employees */
            for (int j = i; j < employeeCount - 1; j++) {
                employees[j] = employees[j + 1];
            }
            employeeCount--;
            RefreshListView();
            ClearInputFields();
            MessageBoxW(NULL, L"Employee deleted successfully!", L"Success", MB_ICONINFORMATION);
            return;
        }
    }

    MessageBoxW(NULL, L"Employee not found!", L"Error", MB_ICONERROR);
}

void SearchEmployee(void) {
    wchar_t idStr[20];
    GetWindowTextW(hIdEdit, idStr, 20);
    int id = _wtoi(idStr);

    if (id <= 0) {
        MessageBoxW(NULL, L"Please enter a valid ID!", L"Error", MB_ICONERROR);
        return;
    }

    for (int i = 0; i < employeeCount; i++) {
        if (employees[i].id == id) {
            wchar_t buffer[20];

            SetWindowTextW(hNameEdit, employees[i].name);
            wsprintfW(buffer, L"%.2f", employees[i].salary);
            SetWindowTextW(hSalaryEdit, buffer);
            SetWindowTextW(hDeptEdit, employees[i].department);
            SetWindowTextW(hPosEdit, employees[i].position);
            return;
        }
    }

    MessageBoxW(NULL, L"Employee not found!", L"Error", MB_ICONERROR);
}

void ClearAllRecords(void) {
    employeeCount = 0;
    RefreshListView();
} 