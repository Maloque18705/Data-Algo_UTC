#include <iostream>
#include <string>
#include <vector>
#include "Car.cpp"
#include "CarList.cpp"

using namespace std;

#ifndef __app__cpp__
#define __app__cpp__


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
#endif