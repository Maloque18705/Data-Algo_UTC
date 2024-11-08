#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Student
{
    private:
        string name;            // Ten sinh vien
        string studentID;       // Ma Sinh vien
        int age;                // Tuoi
        float point;            // Diem sinh vien
    public:
        Student() : name(""), studentID(""), age(0), point(0.0) {}
        Student(string n, int a, string id, float p): name(n), age(a), studentID(id), point(p) {}
        friend istream& operator>>(istream& in, Student& s){
            cout << "Ten sinh vien: ";
            in.ignore();            //Loai bo ky tu xuong dong
            getline(in, s.name);    //Cho phep dau cach trong ten
            cout << "Ma sinh vien: "; in>> s.studentID;
            cout << "Tuoi: "; in>> s.age;
            cout << "Diem: "; in>> s.point;
            return in;
        }
        friend ostream& operator<<(ostream& out, const Student& s){
            out << "Ten: " << s.name << endl;
            out << "Ma sinh vien: " << s.studentID << endl;
            out << "Tuoi: " << s.age << endl;
            out << "Diem: " << s.point << endl;
            return out;
        }

        // Phuong thuc Get
        string getName() const {return name; }
        string getStudentID() const {return studentID; }
        int getAge() const {return age; }
        float getPoint() const {return point; }
};

class StudentList
{
    private:
        Student* students;
        int size;
        int capacity;

        void expand(){
            capacity *=2;
            Student* newArray = new Student[capacity];
            for(int i = 0; i< size; ++i){
                newArray[i] = students[i];
            }
            delete[] students;
            students = newArray;
        }
    public:
        StudentList(int cap = 10): size(0), capacity(cap){
            students = new Student[capacity];
        }

        ~StudentList() {delete[] students;}

        void addStudent(const Student& s){
            if (size == capacity) expand();
            students[size++] = s;
        }

        void removeStudent(const string& studentID){
            for(int i = 0; i<size; i++){
                if(students[i].getStudentID() == studentID){
                    for(int j = i;  j<size-1; ++j){
                        students[j] = students[j+1];
                    }
                    --size;
                    break;
                }
            }
        }

        void display() const{
            for (int i = 0; i<size; i++){
                cout << students[i] << endl;
            }
        }
        void sortByPoint(){
            for (int i = 0; i<size-1; ++i){
                for (int j = 0; j<size-i-1; ++j){
                    if(students[j].getPoint() > students[j+1].getPoint()){
                        swap(students[j], students[j+1]);
                    }
                }
            }
        }
};

class Menu
{
    private:
        StudentList studentList;
    public:
        void displayMenu(){
            int choice;
            do {
                cout << "\n---Chon 1 trong cac lua chon sau---\n";
                cout << "1. Them sinh vien\n";
                cout << "2. Xoa sinh vien\n";
                cout << "3. Xem danh sach sinh vien\n";
                cout << "4. Sap xep sinh vien theo diem\n";
                cout << "0. Thoat\n";
                cout << "Nhap lua chon: ";
                cin >> choice;

                switch (choice)
                {
                    case 1:{
                        Student s;
                        cin >> s;
                        studentList.addStudent(s);
                        break;
                    }
                    case 2:{
                        string studentID;
                        cout << "Nhap ma sinh vien can xoa: ";
                        cin >> studentID;
                        studentList.removeStudent(studentID);
                        break;
                    }
                    case 3:{
                        studentList.display();
                        break;
                    }
                    case 4:{
                        studentList.sortByPoint();
                        break;
                    }
                    case 0:{
                        cout << "Thoat chuong trinh...\n";
                        break;
                    }
                    default:
                        cout << "Lua chon khong phu hop. Vui long thu lai.\n";
                }
            } while (choice != 0);
        }
};
int main(){
    Menu menu;
    menu.displayMenu();
    return 0;
}