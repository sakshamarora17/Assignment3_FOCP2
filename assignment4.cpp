#include <iostream>
#include <vector>
#include <string>
#include <exception>
#include <stdexcept>
using namespace std;

// ===== Custom Exceptions =====
class UniversitySystemException : public exception {
protected:
    string message;
public:
    UniversitySystemException(string msg) : message(msg) {}
    const char* what() const noexcept override {
        return message.c_str();
    }
};

class EnrollmentException : public UniversitySystemException {
public:
    EnrollmentException(string msg) : UniversitySystemException("Enrollment Error: " + msg) {}
};

class GradeException : public UniversitySystemException {
public:
    GradeException(string msg) : UniversitySystemException("Grade Error: " + msg) {}
};

class PaymentException : public UniversitySystemException {
public:
    PaymentException(string msg) : UniversitySystemException("Payment Error: " + msg) {}
};

// ===== Basic Person Classes =====
class Person {
protected:
    string name;
    int age;

public:
    Person(string n, int a) : name(n), age(a) {
        if (a <= 0) throw UniversitySystemException("Invalid age for person: " + to_string(a));
    }
    virtual void displayDetails() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
    virtual double calculatePayment() { return 0.0; }
    virtual ~Person() {}
};

class Student : public Person {
    vector<string> enrolledCourses;
public:
    Student(string n, int a) : Person(n, a) {}

    void enroll(string course, bool isFull, bool hasPrereq, bool beforeDeadline) {
        if (isFull) throw EnrollmentException("Course is full: " + course);
        if (!hasPrereq) throw EnrollmentException("Missing prerequisites for: " + course);
        if (!beforeDeadline) throw EnrollmentException("Enrollment deadline passed for: " + course);
        enrolledCourses.push_back(course);
        cout << name << " enrolled in " << course << endl;
    }
};

// ===== GradeBook Class =====
class GradeBook {
    vector<pair<string, double>> grades;
public:
    void addGrade(string studentID, double grade) {
        if (grade < 0.0 || grade > 100.0)
            throw GradeException("Invalid grade: " + to_string(grade));
        grades.push_back({studentID, grade});
    }
};

// ===== University System Integration =====
class UniversitySystem {
    vector<Student*> students;
    GradeBook gradebook;

public:
    void addStudent(Student* s) {
        students.push_back(s);
    }

    void enrollStudentInCourse(Student* s, string course) {
        try {
            s->enroll(course, false, true, true); // Simulated flags
        } catch (EnrollmentException& e) {
            cerr << e.what() << endl;
        }
    }

    void enterGrade(string studentID, double grade) {
        try {
            gradebook.addGrade(studentID, grade);
        } catch (GradeException& e) {
            cerr << e.what() << endl;
        }
    }

    void generateReport() {
        cout << "Generating university report...\n";
    }
};

// ===== Main Function =====
int main() {
    UniversitySystem uni;
    Student* s1 = new Student("Prateek", 18);
    uni.addStudent(s1);

    // Enroll in course
    uni.enrollStudentInCourse(s1, "C++ Programming");

    // Enter grade
    uni.enterGrade("S101", 95);
    uni.enterGrade("S101", -10);  // Triggers exception

    // Report
    uni.generateReport();

    delete s1;
    return 0;
}
