#include <iostream>
using namespace std;
//using ui = unsigned int;
typedef unsigned int ui;

class Base{
    ui people_on_base; //-количество людей на территории базы;
    ui vehicles_on_base; //-количество транспортных средств на территории базы;
    double petrol_on_base; //-количество бензина на местной "заправке" (в литрах);
    double goods_on_base; //-количество "груза" - различных материальных ценностей(в тоннах).
    static Base* pointer;

    Base() : Base(100, 50, 500, 350){
        cout << "base\n";
    }
    
    Base(int people_on_base, int vehicles_on_base, double petrol_on_base, double goods_on_base){
        this->people_on_base = people_on_base;
        this->vehicles_on_base = vehicles_on_base;
        this->petrol_on_base = petrol_on_base;
        this->goods_on_base = goods_on_base;
        //pointer = new Base;
    }

public:
    void SetPeopleOnBase(int people_on_base) {
        this->people_on_base = people_on_base;
    }

    int GetPeopleOnBase() const {
        return people_on_base;
    }

    void SetVehiclesOnBase(int vehicles_on_base) {
        this->vehicles_on_base = vehicles_on_base;
    }

    int GetVehiclesOnBase() const {
        return vehicles_on_base;         
    }

    void SetPetrolOnBase(double petrol_on_base) {
        this->petrol_on_base = petrol_on_base;
    }

    double GetPetrolOnBase() const {
        return petrol_on_base;
    }

    void SetGoodsOnBase(double goods_on_base) {
        this->goods_on_base = goods_on_base;
    }

    double GetGoodsOnBase() const {
        return goods_on_base;
    }

    static Base* GetPointer()
    {
        return pointer == nullptr ? pointer = new Base : pointer;
    }

    void Print() const {
        cout << "People on base: " << people_on_base << "\n";
        cout << "Vehicles on base: " << vehicles_on_base << "\n";
        cout << "Petrol on base: " << petrol_on_base << "\n";
        cout << "Goods on base: " << goods_on_base << "\n";
    }
};

Base* Base::pointer = new Base;
class Vehicle{
    double petrol_amount = 0;
    double tank_volume = 0;
    Base* pointer = Base::GetPointer();

public:
    Vehicle(double petrol_amount, double tank_volume){
        this->petrol_amount = petrol_amount;
        this->tank_volume = tank_volume;
    }

    void SetPetrolAmount(double petrol_amount) {
        this->petrol_amount = petrol_amount;
    }

    double GetPetrolAmount() const {
        return petrol_amount;
    }

    void SetTankVolume(double tank_volume) {
        this->tank_volume = tank_volume;
    }

    double GetTankVolume() const {
        return tank_volume;
    }

    //-приехать на базу;
    void Arrive() { 
        cout << "\t\tArrive\n";
        pointer->SetPeopleOnBase(pointer->GetPeopleOnBase() + 1);
        pointer->SetVehiclesOnBase(pointer->GetVehiclesOnBase() + 1);
        petrol_amount -= 1 + ((double)rand() / RAND_MAX) * (petrol_amount - 1);// дорога
    }

    //-залить полный бак и покинуть базу; в случае невозможности уехать возвращает false;
    bool Leave() {
        cout << "\t\t:Leave:\n";
        pointer->SetVehiclesOnBase(pointer->GetVehiclesOnBase() - 1);
        if(pointer->GetPeopleOnBase() - 1 >= 0)
        {
            pointer->SetPeopleOnBase(pointer->GetPeopleOnBase() - 1);
        }
        if (pointer->GetPetrolOnBase() - tank_volume + petrol_amount >= 0)
        {
            pointer->SetPetrolOnBase(pointer->GetPetrolOnBase() - tank_volume + petrol_amount);
            petrol_amount = tank_volume;
        }
        else
            return false;
        
        return true;
    } 

    void Print() const {
        cout << "Petrol amount: " << petrol_amount << "\n";
        cout << "Tank volume: " << tank_volume << "\n";
        cout << "Count peoples on base: " << pointer->GetPeopleOnBase() << "\n";
        cout << "Count petrol on base: " << pointer->GetPetrolOnBase() << "\n";
    }
};

class Bus : public Vehicle{
    int people_in_bus = 0;
    int max_people = 0;
    double petrol = 0;
    double max_petrol = 0;
    Base* pointer = Base::GetPointer();
  
public:
    Bus() : Bus(10, 35, 26.5, 50.4) {}
    Bus(int people_in_bus, int max_people, double petrol, double max_petrol) : Vehicle(petrol, max_petrol) {
        this->people_in_bus = people_in_bus;
        this->max_people = max_people;
        this->petrol = petrol;
        this->max_petrol = max_petrol;
    }

    void SetPeople(int people_in_bus) {
        this->people_in_bus = people_in_bus;
    }

    int GetPeople() const {
        return people_in_bus;
    }

    void SetMaxPeople(int max_people) {
        this->max_people = max_people;
    }

    int GetMaxPeople() const {
        return max_people;
    }

    void SetPetrol(double petrol) {
        this->petrol = petrol;
    }
    double GetPetrol() const{
        return petrol;
    }

    void SetMaxPetrol(double max_petrol) {
        this->max_petrol = max_petrol;
    }

    double GetMaxPetrol() const {
        return max_petrol;        
    }    

    void Print() const {
        cout << "Petrol amount: " << petrol << "\n";
        cout << "Tank volume: " << max_petrol << "\n";
        cout << "Count peoples on base: " << pointer->GetPeopleOnBase() << "\n";
        cout << "Count petrol on base: " << pointer->GetPetrolOnBase() << "\n";
        cout << "People count in bus: " << people_in_bus << "\n";
        cout << "Max people value: " << max_people << "\n";
    }
    
    void Arrive(){
        cout << "\t\tArrive\n";
        pointer->SetPeopleOnBase(pointer->GetPeopleOnBase() + people_in_bus + 1);
        people_in_bus = 0;
        petrol -= 1 + ((double)rand() / RAND_MAX) * (petrol - 1);// min_value + ((double)rand() / RAND_MAX) * (max_value - min_value);
        pointer->SetVehiclesOnBase(pointer->GetVehiclesOnBase() + 1);
    }

    bool Leave(){
        cout << "\t\t:Leave:\n";
        pointer->SetVehiclesOnBase(pointer->GetVehiclesOnBase() - 1);
        people_in_bus = rand() % max_people;
        if (pointer->GetPeopleOnBase() - 1 - people_in_bus >= 0)
        {
            pointer->SetPeopleOnBase(pointer->GetPeopleOnBase() - people_in_bus - 1);
        }
        if (pointer->GetPetrolOnBase() - max_petrol + petrol >= 0)
        {
            pointer->SetPetrolOnBase(pointer->GetPetrolOnBase() - max_petrol + petrol);
            petrol = max_petrol;
        }
        else
            return false;
        return true;
    }
};

class Truck : public Vehicle{
    double load = 0;
    double max_load = 0;
    double petrol = 0;
    double max_petrol = 0;
    Base* pointer = Base::GetPointer();
public:
    Truck() : Truck(0, 25, 30, 70) {}

    Truck(double load, double max_load, double petrol, double max_petrol) : Vehicle(petrol, max_petrol){
        this->load = load;
        this->max_load = max_load;
        this->petrol = petrol;
        this->max_petrol = max_petrol;
    }

    void SetLoad(double load){
        this->load = load;
    }

    double GetLoad() const{
        return load;
    }

    void SetMaxLoad(double max_load) {
        this->max_load = max_load;
    }

    double GetMaxLoad() const {
        return max_load;
    }

    void SetPetrol(double petrol) {
        this->petrol = petrol;
    }

    double GetPetrol() const {
        return petrol;
    }

    void SetMaxPetrol(double max_petrol) {
        this->max_petrol = max_petrol;
    }

    double GetMaxPetrol() const {
        return max_petrol;
    }

    void Arrive() {
        cout << "\t\tArrive\n";
        pointer->SetPeopleOnBase(pointer->GetPeopleOnBase() + 1);
        pointer->SetVehiclesOnBase(pointer->GetVehiclesOnBase() + 1);
        pointer->SetGoodsOnBase(pointer->GetGoodsOnBase() + load); 
        load = 0;
        petrol -= 1 + ((double)rand() / RAND_MAX) * (petrol - 1);// min_value + ((double)rand() / RAND_MAX) * (max_value - min_value);
    }

    bool Leave() {
        cout << "\t\t:Leave:\n";
        pointer->SetVehiclesOnBase(pointer->GetVehiclesOnBase() - 1);
        if(pointer->GetPeopleOnBase() - 1 >= 0)
        {
            pointer->SetPeopleOnBase(pointer->GetPeopleOnBase() - 1);
        }
        if (pointer->GetGoodsOnBase() - max_load >= 0)
        {
            load = 0 + ((double)rand() / RAND_MAX) * (max_load - 0);
            pointer->SetGoodsOnBase(pointer->GetGoodsOnBase() - load);
        }
        if (pointer->GetPetrolOnBase() - max_petrol + petrol >= 0)
        {
            pointer->SetPetrolOnBase(pointer->GetPetrolOnBase() - max_petrol + petrol);
            petrol = max_petrol;
        }
        else
            return false;
        return true;
    }

    void Print()
    {
        cout << "Petrol amount: " << petrol << "\n";
        cout << "Tank volume: " << max_petrol << "\n";
        cout << "Count peoples on base: " << pointer->GetPeopleOnBase() << "\n";
        cout << "Count goods on base: " << pointer->GetGoodsOnBase() << "\n";
        cout << "Count petrol on base: " << pointer->GetPetrolOnBase() << "\n";
        cout << "Goods count in truck: " << load << "\n";
        cout << "Max good value: " << max_load << "\n";
    }

};
int main()
{
    srand(time(0));
    auto pointer = Base::GetPointer();
    Vehicle veh(20.9, 55.4);
    Truck tr/*(30, 40, 25, 56)*/;
    Bus b(10, 20, 20, 40);
    
    /*tr.Print();
    cout << tr.Leave() << "\n";
    tr.Print();
    tr.Arrive();
    tr.Print();*/

    /*b.Print();
    cout << b.Leave() << "\n";
    b.Print();
    b.Arrive();
    b.Print();
    b.Leave();
    b.Print();*/

    veh.Print();  
    cout << veh.Leave() << "\n";
    veh.Print();
    veh.Arrive();
    veh.Print();
}
