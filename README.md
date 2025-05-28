# Employee Management System

A modern, user-friendly Windows application for managing employee records. Built with C and the Windows API, this application provides a sleek dark-themed interface for efficient employee data management.

## Features

- 📝 Add, update, and delete employee records
- 🔍 Search employees by ID
- 📊 View all employees in a modern list view
- 💾 Import/Export data to/from CSV files
- 🎨 Modern dark theme UI
- 📱 Responsive window design

## Screenshots

![image](https://github.com/user-attachments/assets/ca75e0ac-993f-485c-90c8-52c2ec83d5fa)


## Prerequisites

- Windows 10 or later
- Visual Studio 2022 (or compatible version)
- Windows SDK 10.0

## Installation

1. Clone the repository:
```bash
git clone https://github.com/yourusername/employee-management.git
```

2. Open the solution in Visual Studio:
   - Open `EmployeeManagement.sln`
   - Select "Debug" configuration
   - Build the solution (F7)

3. Run the application:
   - Press F5 to start debugging
   - Or run `EmployeeManagement.exe` from the Debug folder

## Project Structure

The project is organized into modular components:

### 1. Header File (`employee_management.h`)
- Central interface file
- Contains shared definitions and structures
- Defines the Employee structure and UI constants

### 2. UI Component (`ui.c`)
- Handles all visual elements
- Implements modern UI styling
- Manages the ListView display

### 3. Data Management (`data_management.c`)
- Implements CRUD operations
- Handles data validation
- Manages employee records

### 4. File I/O (`file_io.c`)
- Handles CSV import/export
- Manages file operations
- Ensures data persistence

### 5. Main Application (`main.c`)
- Application entry point
- Window procedure
- Message loop handling

## Usage

1. **Adding an Employee**
   - Fill in the employee details
   - Click "Add Employee"

2. **Updating an Employee**
   - Search for the employee by ID
   - Modify the details
   - Click "Update"

3. **Deleting an Employee**
   - Enter the employee ID
   - Click "Delete"

4. **Searching an Employee**
   - Enter the employee ID
   - Click "Search"

5. **Importing/Exporting Data**
   - Click "Export to CSV" to save data
   - Click "Import from CSV" to load data

## CSV Format

The application uses a simple CSV format for data storage:

```csv
ID,Name,Salary,Department,Position
1,Arnav Gupta,50000.00,IT,Developer
2,Ameya Borkar,60000.00,HR,Manager
```

## Team Members

- [Ameya Borkar] - UI Component
- [Aditya chimurkar] - Data Management
- [Arnav Gupta] - File I/O
- [Aarush Bakshi] - Main Application & Header File


## Contact

[Aarush Bakshi] - [Bakshiaarush05@gmail.com]
