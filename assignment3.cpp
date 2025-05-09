#include <iostream>
#include <vector>
using namespace std;

// ===== Base Class =====
class Person {
protected:
    string name;
    int age;

public:
    Person(string n, int a) : name(n), age(a) {}
    virtual void displayDetails() {
        cout << "Name: " << name << ", Age: " << age << endl;
    }
    virtual double calculatePayment() { return 0.0; }
    virtual ~Person() {}
};

// ===== Student and Derived Classes =====
class Student : public Person {
protected:
    string program;
    double gpa;

public:
    Student(string n, int a, string prog, double g) : Person(n, a), program(prog), gpa(g) {}
    void displayDetails() override {
        cout << "Student - "; Person::displayDetails();
        cout << "Program: " << program << ", GPA: " << gpa << endl;
    }
    double calculatePayment() override {
        return 10000;  // base tuition fee
    }
};

class UndergraduateStudent : public Student {
    string major;
public:
    UndergraduateStudent(string n, int a, string prog, double g, string m)
        : Student(n, a, prog, g), major(m) {}
    void displayDetails() override {
        Student::displayDetails();
        cout << "Major: " << major << endl;
    }
};

class GraduateStudent : public Student {
    string thesis;
public:
    GraduateStudent(string n, int a, string prog, double g, string t)
        : Student(n, a, prog, g), thesis(t) {}
    void displayDetails() override {
        Student::displayDetails();
        cout << "Thesis: " << thesis << endl;
    }
};

// ===== Professor and Derived Classes =====
class Professor : public Person {
protected:
    int yearsOfService;

public:
    Professor(string n, int a, int y) : Person(n, a), yearsOfService(y) {}
    void displayDetails() override {
        cout << "Professor - "; Person::displayDetails();
        cout << "Years of Service: " << yearsOfService << endl;
    }
};

class AssistantProfessor : public Professor {
public:
    AssistantProfessor(string n, int a, int y) : Professor(n, a, y) {}
    double calculatePayment() override {
        return 50000 + 1000 * yearsOfService;
    }
};

class AssociateProfessor : public Professor {
public:
    AssociateProfessor(string n, int a, int y) : Professor(n, a, y) {}
    double calculatePayment() override {
        return 70000 + 1500 * yearsOfService;
    }
};

class FullProfessor : public Professor {
    double researchGrant;
public:
    FullProfessor(string n, int a, int y, double g) : Professor(n, a, y), researchGrant(g) {}
    double calculatePayment() override {
        return 90000 + 2000 * yearsOfService + 0.1 * researchGrant;
    }
};

// ===== Course and Department (Relationships) =====
class Course {
    string title;
    Professor* instructor;

public:
    Course(string t, Professor* p) : title(t), instructor(p) {}
    void showCourse() {
        cout << "Course: " << title << endl;
        if (instructor) instructor->displayDetails();
    }
};

class Department {
    string name;
    vector<Professor*> profs;

public:
    Department(string n) : name(n) {}
    void addProfessor(Professor* p) {
        profs.push_back(p);
    }
    void showProfessors() {
        cout << "Department: " << name << endl;
        for (auto p : profs)
            p->displayDetails();
    }
};

// ===== Main Function =====
int main() {
    UndergraduateStudent u1("Saksham", 18, "BTech", 3.8, "CSE");
    GraduateStudent g1("Rahul", 24, "MTech", 3.9, "AI Thesis");

    AssistantProfessor ap("Dr. Khan", 35, 5);
    FullProfessor fp("Dr. Sharma", 50, 20, 50000);

    Course c1("OOP in C++", &ap);

    Department d1("Computer Science");
    d1.addProfessor(&ap);
    d1.addProfessor(&fp);

    // Display details
    u1.displayDetails();
    cout << "Payment: " << u1.calculatePayment() << endl;

    g1.displayDetails();
    cout << "Payment: " << g1.calculatePayment() << endl;

    ap.displayDetails();
    cout << "Payment: " << ap.calculatePayment() << endl;

    fp.displayDetails();
    cout << "Payment: " << fp.calculatePayment() << endl;

    c1.showCourse();
    d1.showProfessors();

    return 0;
}
