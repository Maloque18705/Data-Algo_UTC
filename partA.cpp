#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Car
{
    private:
        string brand;           // Ten thuong hieu
        string model;           // Ten mau xe
        string vin;             // So VIN cua xe
        int year;               // Nam san xuat
        float price;            // Gia xe
    public:
        Car() : brand(""), model(""), vin(""), year(0), price(0.0) {}
        friend istream& operator>>(istream& in, Car& c){
            cout << "Thuong hieu: ";
            in.ignore();            // Loai bo ky tu xuong dong
            getline(in, c.brand);   // Cho phep dau cach trong xau
            cout << "Dong xe: ";
            in.ignore();            // Loai bo ky tu xuong dong
            getline(in, c.model);   // Cho phep dau cach trong xau
            cout << "So VIN: "; in>> c.vin;
            cout << "Nam san xuat: "; in>> c.year;
            cout << "Gia: "; in>> c.price;
            return in;
        }
        friend ostream& operator<<(ostream& out, const Car& c){
            out << "Thuong hieu: " << c.brand << endl;
            out << "Dong xe: " << c.brand << endl;
            out << "So VIN: " <<  c.vin << endl;
            out << "Nam san xuat: " << c.year << endl;
            out << "Gia: " << c.price << endl;
            return out;
        }
        void test();
        string getBrand() const {return brand; }
        string getModel() const {return model; }
        string getVIN() const {return vin; }
        int getYear() const {return year; }
        float getPrice() const {return price; }
        
};

class CarList
{
    private:
        Car* cars;
        int size;
        int capacity;

        void expand(){
            capacity *=2;
            Car* newArray = new Car[capacity];
            for (int i = 0; i < size; ++i){
                newArray[i] = cars[i];
            }
            delete[] cars;
            cars = newArray;
        }
    public:
        CarList(int cap = 10): size(0), capacity(cap){
            cars = new Car[capacity];
        }

        ~CarList() {delete[] cars;}

        void addCar(const Car& c){
            if (size == capacity) expand();
                cars[size++] = c;
        }

        void removeCar(const string& vin){
            for (int i = 0; i<size; i++){
                if(cars[i].getVIN() == vin){
                    for (int j = i; j < size-1; ++j){
                        cars[j] = cars[j+1];
                    }
                    --size;
                    break;
                }
            }
        }
        
        void displayAll() const{
            for (int i = 0; i < size; i++){
                cout << cars[i] << endl;
            }
        }

        void sortByPrice(){
            for (int i = 0; i < size-1; ++i){
                for (int j = 0; j < size - i - 1; ++j){
                    if(cars[j].getPrice() > cars[j+1].getPrice()){
                        swap(cars[j], cars[j+i]);
                    }
                }
            }
        }
        
        void sortByYear(){
            for (int i = 0; i < size - 1; ++i){
                for (int j = 0; j < size - i - 1; ++j){
                    if(cars[j].getYear() > cars[j+1].getYear()){
                        swap(cars[j], cars[j+1]);
                    }
                }
            }
        }
};

class Menu{
    private:
        CarList carList;
    public:
        void displayMenu(){
            int choice;
            do {
                cout << "\n---Chon mot trong cac lua chon sau---\n";
                cout << "1. Them mot mau xe\n";
                cout << "2. Xoa mot mau xe\n";
                cout << "3. Xem danh sach cac mau xe\n";
                cout << "4. Sap xep cac mau xe theo gia\n";
                cout << "5. Sap xep cac mau xe theo nam san xuat\n";
                cout << "0. Thoat\n";
                cout << "Nhap lua chon: ";
                cin >> choice;

                switch (choice)
                {
                    case 1:{
                        Car c;
                        cin >> c;
                        carList.addCar(c);
                        break;
                    }
                    case 2:{
                        string vin;
                        cout << "Nhap so VIN cua xe can xoa: ";
                        cin >> vin;
                        carList.removeCar(vin);
                        break;
                    }
                    case 3:{
                        carList.displayAll();
                        break;
                    }
                    case 4:{
                        carList.sortByPrice();
                        cout << "Danh sach xe da sap xep theo gia: " << endl;
                        carList.displayAll();
                        break;
                    }
                    case 5:{
                        carList.sortByYear();
                        cout << "Danh sach xe da sap xep theo nam san xuat: " << endl;
                        carList.displayAll();
                        break;
                    }
                    case 0:{
                        cout << "Thoat chuong trinh.\n";
                        break;
                    }
                    default:
                        cout << "Lua chon khong phu hop. Vui long thu lai.";
                }
            } while(choice != 0);
        }
};
int main(){
    Menu menu;
    menu.displayMenu();
    return 0;
}
