# 🎓 Student Management System

A comprehensive, production-ready C program for managing student records with role-based access control and advanced analytics.

[![Language](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)](https://www.microsoft.com/windows)
[![License](https://img.shields.io/badge/License-Educational-green.svg)](LICENSE)
[![Status](https://img.shields.io/badge/Status-Production%20Ready-brightgreen.svg)](README.md)

---

## 📋 Table of Contents
- [Features](#-features)
- [Screenshots](#-screenshots)
- [Installation](#-installation)
- [Usage](#-usage)
- [User Roles](#-user-roles)
- [Menu Options](#-menu-options)
- [Grade Statistics](#-grade-statistics)
- [File Structure](#-file-structure)
- [Technical Details](#-technical-details)
- [Troubleshooting](#-troubleshooting)

---

## ✨ Features

### Core Functionality
- ✅ **Student Management**: Add, view, search, update, and delete student records
- ✅ **Grade Analytics**: Comprehensive statistics with visual charts
- ✅ **Role-Based Access**: 4 user levels with different permissions
- ✅ **Secure Login**: Password masking with attempt limiting
- ✅ **Data Validation**: Complete input validation and error handling
- ✅ **Duplicate Prevention**: Automatic roll number verification

### Advanced Features
- 📊 **Statistics Dashboard**:
  - Overall class performance metrics
  - Grade distribution (A/B/C/D/F)
  - Top performer identification
  - Visual bar charts
  - Pass rate calculation
  
- 🔒 **Security Features**:
  - Password masking with asterisks
  - 3-attempt login limit
  - Buffer overflow protection
  - Safe string operations
  - Input sanitization

- 💪 **Robust Error Handling**:
  - File operation validation
  - Input type checking
  - Range validation
  - Graceful error messages

---

## 📸 Screenshots

### Login Screen
```
========================================
  STUDENT MANAGEMENT SYSTEM
========================================

===== LOGIN =====
Username: admin
Password: ********
```

### Statistics Dashboard
```
============================================================
          GRADE STATISTICS & ANALYTICS
============================================================

>> OVERALL STATISTICS:
------------------------------------------------------------
   Total Students:        2
   Average Marks:         90.12
   Highest Marks:         90.25
   Lowest Marks:          90.00
   Pass Rate:             100.0% (2/2)

>> TOP PERFORMER:
------------------------------------------------------------
   Roll: 102  |  Name: Sneha  |  Marks: 90.25

>> VISUAL GRADE DISTRIBUTION:
------------------------------------------------------------
   A: ################################################## 2
   B:  0
```

---

## 🚀 Installation

### Prerequisites
- **Compiler**: GCC (MinGW for Windows)
- **OS**: Windows (uses `conio.h`)
- **Terminal**: PowerShell or Command Prompt

### Compile the Program
```bash
gcc student.c -o student_system.exe
```

### Run the Program
```bash
.\student_system.exe
```

---

## 📖 Usage

### First Time Setup
1. **Run the program** - Files are auto-created on first launch
2. **Login** with default credentials (see below)
3. **Start managing students!**

### Default Login Credentials

| Username | Password   | Role  | Permissions                      |
|----------|------------|-------|----------------------------------|
| `admin`  | `admin123` | ADMIN | Full access (all operations)     |
| `staff`  | `staff123` | STAFF | View, search, update marks only  |
| `user`   | `user123`  | USER  | View and search only             |
| `guest`  | `guest123` | GUEST | Auto-view students and exit      |

---

## 👥 User Roles

### 🔴 ADMIN (Full Access)
- ✅ Add new students
- ✅ Display all students
- ✅ Search by roll number
- ✅ Update name and marks
- ✅ Delete students
- ✅ View statistics
- ✅ Logout

### 🟡 STAFF (Limited Modifications)
- ✅ Display all students
- ✅ Search by roll number
- ✅ Update marks ONLY (name locked)
- ✅ View statistics
- ✅ Logout

### 🟢 USER (Read-Only)
- ✅ Display all students
- ✅ Search by roll number
- ✅ View statistics
- ✅ Logout

### 🔵 GUEST (Auto-View)
- ✅ Automatically displays students
- ✅ Exits immediately after viewing

---

## 📋 Menu Options

### ADMIN Menu
```
===== ADMIN MENU =====
1. Add Student
2. Display Students
3. Search Student
4. Update Student
5. Delete Student
6. View Statistics
7. Logout
```

### STAFF Menu
```
===== STAFF MENU =====
1. Display Students
2. Search Student
3. Update Student Marks Only
4. View Statistics
5. Logout
```

### USER Menu
```
===== USER MENU =====
1. Display Students
2. Search Student
3. View Statistics
4. Logout
```

---

## 📊 Grade Statistics

The statistics feature provides comprehensive analytics:

### Metrics Displayed
- **Total Students**: Count of all enrolled students
- **Average Marks**: Class average percentage
- **Highest/Lowest Marks**: Range of performance
- **Pass Rate**: Percentage of students scoring ≥60%

### Grade Distribution
| Grade | Range    | Description      |
|-------|----------|------------------|
| A     | 90-100   | Excellent        |
| B     | 80-89    | Good             |
| C     | 70-79    | Average          |
| D     | 60-69    | Below Average    |
| F     | Below 60 | Fail             |

### Visual Charts
- Bar graph representation using `#` symbols
- Easy-to-read at-a-glance performance overview

---

## 📁 File Structure

```
student-management-system/
│
├── student.c              # Main source code (846 lines)
├── student_system.exe     # Compiled executable (auto-generated)
├── students.txt           # Student database (auto-created)
├── credentials.txt        # User credentials (auto-created)
├── .gitignore            # Git ignore file
└── README.md             # This file
```

### Data Files Format

**students.txt:**
```
roll name marks
101 John 85.50
102 Sarah 92.00
```

**credentials.txt:**
```
username password role
admin admin123 ADMIN
staff staff123 STAFF
```

---

## 🔧 Technical Details

### Input Validation
- **Roll Numbers**: 1 to 999,999
- **Marks**: 0.00 to 100.00
- **Names**: Alphanumeric + underscore + hyphen only
- **Automatic**: Buffer clearing to prevent infinite loops

### Security Features
- ✅ Buffer overflow protection
- ✅ Safe string operations (`strncpy`)
- ✅ Input sanitization
- ✅ Password masking
- ✅ Attempt limiting

### Code Quality
- **Compilation**: Zero warnings with `-Wall -Wextra`
- **Lines of Code**: 846 lines
- **Functions**: 20+ well-documented functions
- **Error Handling**: Comprehensive for all operations
- **File Validation**: Automatic file initialization and validation

---

## 🛠️ Troubleshooting

### Problem: Compilation errors
**Solution**: Ensure you have GCC/MinGW installed
```bash
gcc --version
```

### Problem: `conio.h` not found
**Solution**: This program requires Windows. Use MinGW compiler.

### Problem: Files not created
**Solution**: Ensure write permissions in the directory.

### Problem: Login fails
**Solution**: Check `credentials.txt` exists and has correct format:
```
admin admin123 ADMIN
```

### Problem: Cannot see statistics
**Solution**: Ensure `students.txt` has data. Add at least one student first.

---

## 📝 Development Notes

### Compilation Commands
```bash
# Basic compilation
gcc student.c -o student_system.exe

# With warnings
gcc student.c -o student_system.exe -Wall -Wextra

# Strict mode
gcc student.c -o student_system.exe -Wall -Wextra -pedantic
```

### Testing Checklist
- ✅ Login with all 4 user roles
- ✅ Add students with various marks
- ✅ Test duplicate roll number prevention
- ✅ Verify input validation (negative marks, invalid names)
- ✅ Update student records
- ✅ Delete student records
- ✅ View statistics with different data sets
- ✅ Test edge cases (empty file, single student)

---

## 🎯 Use Cases

### Educational Institutions
- Schools managing student grades
- Tutoring centers tracking performance
- Training institutes monitoring progress

### Learning Projects
- C programming practice
- File handling demonstration
- Role-based access control example
- Data structure implementation

---

## 📚 Learning Outcomes

This project demonstrates:
- ✅ File I/O operations in C
- ✅ Struct usage and data structures
- ✅ Input validation techniques
- ✅ Error handling best practices
- ✅ Secure coding practices
- ✅ Menu-driven program design
- ✅ Statistical calculations
- ✅ Role-based access implementation

---

## 🏆 Features Highlights

### What Makes This Special?
1. **Production-Ready**: Zero compilation warnings, comprehensive error handling
2. **User-Friendly**: Clear menus, helpful messages, professional formatting
3. **Secure**: Buffer protection, input validation, password security
4. **Advanced**: Statistics dashboard with visual analytics
5. **Robust**: Handles all edge cases and error conditions
6. **Well-Documented**: Clean code with clear comments

---

## 📞 Support

### Common Questions

**Q: Can I change passwords?**  
A: Edit `credentials.txt` manually (feature coming in future version)

**Q: Can I export data?**  
A: Currently data is in `students.txt` (CSV export planned)

**Q: Maximum students?**  
A: No hard limit, constrained only by system memory

**Q: Can I add subjects?**  
A: Current version supports single marks field (multi-subject planned)

---

## 🚀 Future Enhancements (Planned)

- [ ] Multi-subject support with GPA calculation
- [ ] CSV export functionality
- [ ] Attendance tracking
- [ ] Report card generation
- [ ] Backup and restore features
- [ ] Advanced search filters
- [ ] Batch operations
- [ ] Password change option

---

## 📄 License

This project is created for **educational purposes**.  
Feel free to use, modify, and learn from the code.

---

## 👨‍💻 Version Information

- **Version**: 2.0 (Production Ready)
- **Last Updated**: December 2024
- **Language**: C (C99 Standard)
- **Platform**: Windows
- **Status**: Stable ✅
- **Author**: vaishnavipolnati-pixel

---

## 🎓 About

This Student Management System is a comprehensive solution for educational institutions and learning purposes. It demonstrates professional C programming practices with a focus on security, reliability, and user experience.

**Built with ❤️ for education**

---

## 👤 Author & Repository

- **GitHub**: [@vaishnavipolnati-pixel](https://github.com/vaishnavipolnati-pixel)
- **Repository**: [Student_Record_Management_in_c](https://github.com/vaishnavipolnati-pixel/Student_Record_Management_in_c)
- **Email**: vaishnav_polnati@srmap.edu.in

---

### Quick Start
```bash
# 1. Compile
gcc student.c -o student_system.exe

# 2. Run
.\student_system.exe

# 3. Login
Username: admin
Password: admin123

# 4. Enjoy! 🎉
```

---

**Questions? Issues? Feel free to explore the code and learn!**

