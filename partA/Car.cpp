#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef __car__cpp__
#define __car__cpp__

class Car
{
    private:
        string brand;           // Ten thuong hieu
        string model;           // Ten mau xe
        string vin;             // So VIN cua xe
        int year;               // Nam san xuat
        float price;            // Gia xe
    public:
        Car(){
            this->brand = "";
            this->model = "";
            this->vin = "";
            this->year = 0;
            this->price = 0.0;
        }
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
            out << "Dong xe: " << c.model << endl;
            out << "So VIN: " <<  c.vin << endl;
            out << "Nam san xuat: " << c.year << endl;
            out << "Gia: " << c.price << endl;
            return out;
        }
        string getBrand() const {return brand; }
        string getModel() const {return model; }
        string getVIN() const {return vin; }
        int getYear() const {return year; }
        float getPrice() const {return price; }
        
};
#endif