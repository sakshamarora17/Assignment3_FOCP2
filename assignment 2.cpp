#include <iostream>
#include <vector>
using namespace std;

// Base class
class Person {
protected:
    string name;
    int age;
    string ID;
    string contact;

public:
    Person(string n, int a, string id, string c) {
        setName(n);
        setAge(a);
        ID = id;
        contact = c;
    }

    virtual ~Person() {}

    void setName(string n) {
        name = n.empty() ? "Unknown" : n;
    }

    void setAge(int a) {
        age = (a > 0 && a <= 120) ? a : 18;
    }

    string getName() { return name; }
    int getAge() { return age; }
    string getID() { return ID; }

    virtual void displayDetails() {
        cout << "Name: " << name << ", Age: " << age << ", ID: " << ID << ", Contact: " << contact << endl;
    }

    virtual double calculatePayment() {
        return 0.0;
    }
};

// Student class
class Student : public Person {
    string program;
    double GPA;
    string enrollmentDate;

public:
    Student(string n, int a, string id, string c, string ed, string p, double g)
        : Person(n, a, id, c), enrollmentDate(ed), program(p) {
        setGPA(g);
    }

    void setGPA(double g) {
        GPA = (g >= 0.0 && g <= 4.0) ? g : 0.0;
    }

    double getGPA() { return GPA; }

    void displayDetails() override {
        Person::displayDetails();
        cout << "Program: " << program << ", GPA: " << GPA << ", Enrolled: " << enrollmentDate << endl;
    }

    double calculatePayment() override {
        return 10000.0;
    }
};

// Professor class
class Professor : public Person {
    string department;
    string specialization;
    string hireDate;

public:
    Professor(string n, int a, string id, string c, string d, string s, string h)
        : Person(n, a, id, c), department(d), specialization(s), hireDate(h) {}

    void displayDetails() override {
        Person::displayDetails();
        cout << "Department: " << department << ", Specialization: " << specialization << ", Hire Date: " << hireDate << endl;
    }

    double calculatePayment() override {
        return 50000.0;
    }
};

// Course class
class Course {
    string code, title, description;
    int credits;

public:
    Course(string c, string t, int cr, string d) {
        code = c;
        title = t;
        description = d;
        setCredits(cr);
    }

    void setCredits(int c) {
        credits = (c > 0) ? c : 1;
    }

    void showCourse() {
        cout << "Course: " << code << " - " << title << ", Credits: " << credits << endl;
    }
};

// Department class
class Department {
    string name, location;
    double budget;

public:
    Department(string n, string l, double b) : name(n), location(l), budget(b) {}

    void showDept() {
        cout << "Department: " << name << ", Location: " << location << ", Budget: $" << budget << endl;
    }
};

// GradeBook class
class GradeBook {
    string studentIDs[10];
    double grades[10];
    int count;

public:
    GradeBook() {
        count = 0;
    }

    void addGrade(string studentID, double grade) {
        if (count < 10) {
            studentIDs[count] = studentID;
            grades[count] = grade;
            count++;
        }
    }

    double calculateAverageGrade() {
        if (count == 0) return 0;
        double sum = 0;
        for (int i = 0; i < count; i++) {
            sum += grades[i];
        }
        return sum / count;
    }

    double getHighestGrade() {
        double max = 0;
        for (int i = 0; i < count; i++) {
            if (grades[i] > max)
                max = grades[i];
        }
        return max;
    }

    void getFailingStudents() {
        for (int i = 0; i < count; i++) {
            if (grades[i] < 50)
                cout << "Failing Student ID: " << studentIDs[i] << endl;
        }
    }
};

// EnrollmentManager class
class EnrollmentManager {
    string courseCodes[10];
    string studentIDs[10][10];
    int studentCounts[10];
    int courseCount;

public:
    EnrollmentManager() {
        courseCount = 0;
        for (int i = 0; i < 10; i++) studentCounts[i] = 0;
    }

    void enrollStudent(string courseCode, string studentID) {
        int index = findCourse(courseCode);
        if (index == -1) {
            index = courseCount++;
            courseCodes[index] = courseCode;
        }
        if (studentCounts[index] < 10) {
            studentIDs[index][studentCounts[index]++] = studentID;
        }
    }

    void dropStudent(string courseCode, string studentID) {
        int index = findCourse(courseCode);
        if (index == -1) return;
        for (int i = 0; i < studentCounts[index]; i++) {
            if (studentIDs[index][i] == studentID) {
                for (int j = i; j < studentCounts[index] - 1; j++) {
                    studentIDs[index][j] = studentIDs[index][j + 1];
                }
                studentCounts[index]--;
                break;
            }
        }
    }

    int getEnrollmentCount(string courseCode) {
        int index = findCourse(courseCode);
        return (index != -1) ? studentCounts[index] : 0;
    }

private:
    int findCourse(string code) {
        for (int i = 0; i < courseCount; i++) {
            if (courseCodes[i] == code)
                return i;
        }
        return -1;
    }
};

// Main program
int main() {
    Student s1("Saksham", 18, "S101", "9999", "2023-08-01", "BTech CSE", 3.8);
    Student s2("Rahul", 19, "S102", "8888", "2023-08-01", "BTech IT", 3.5);

    Professor p1("Dr. X", 45, "P201", "7777", "CSE", "AI", "2015-07-10");
    Professor p2("Dr. Y", 50, "P202", "6666", "ECE", "VLSI", "2010-05-21");

    Person* people[4] = { &s1, &s2, &p1, &p2 };

    for (int i = 0; i < 4; i++) {
        people[i]->displayDetails();
        cout << "Payment: " << people[i]->calculatePayment() << "\n\n";
    }

    Course c1("CS101", "Intro to Programming", 3, "Basics of C++");
    Course c2("CS102", "Data Structures", 4, "Stacks, Queues, Trees");

    c1.showCourse();
    c2.showCourse();

    Department d1("Computer Science", "Block A", 500000);
    d1.showDept();

    GradeBook gb;
    gb.addGrade("S101", 85);
    gb.addGrade("S102", 45);
    cout << "\nAverage Grade: " << gb.calculateAverageGrade() << endl;
    cout << "Highest Grade: " << gb.getHighestGrade() << endl;
    gb.getFailingStudents();

    EnrollmentManager em;
    em.enrollStudent("CS101", "S101");
    em.enrollStudent("CS101", "S102");
    cout << "Enrollment in CS101: " << em.getEnrollmentCount("CS101") << endl;

    em.dropStudent("CS101", "S102");
    cout << "Enrollment in CS101 after drop: " << em.getEnrollmentCount("CS101") << endl;

    return 0;
}
