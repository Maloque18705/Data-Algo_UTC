#include <iostream>
#include <string>
#include <vector>
#include "Car.cpp"

using namespace std;

#ifndef __CarList__cpp__
#define __CarList__cpp__

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
#endif