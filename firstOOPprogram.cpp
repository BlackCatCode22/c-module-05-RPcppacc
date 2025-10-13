// Crated 10/13/25 by Roman Pena
// feilds and methods make object oriented programming
// this is realted to encapsulation

#include <iostream>

using namespace std;
//classes should start with a upper case

class AbstractPerson {
    virtual void AskForPromotion()=0;
};

class Employee:AbstractPerson {

private:
    string name;
    string company;
    int  age;

    public:
void setName(string name) {
    name = name;
}
    string getName() {
    return name;
}
    void setCompany(string company) {
    company = company;
}
string getCompany() {
    return company;
}
    void setAge(int age) {
    if (age >= 18)
    age = age;
}
    int getAge() {
    return age;
}
   // string name;
  //  string company;
   // int  age;

    void introduce() {

    Employee(string name, string company, int age){}
}
       // cout<<"Name - "<< name << endl;
       // cout<<"Company - "<< company << endl;
       // cout<<"Age - "<< age << endl;

    void AskForPromotion() {
        if (age > 30)
            cout << name <<" GET promo"<<endl;
        else
            cout << name <<" No Promo "<<endl;
        }

    Employee(string name, string company, int age) {
        name=name;
        company=company;
        age=age;

    }
};


int main() {


Employee employee1 = Employee("Roman", "C++ INC",25);

    employee1.introduce();

   // employee1.name = "Roman";
   // employee1.company = "C++ inc.";
   // employee1.age = 25;


    //Employee employee2;
    //employee2.name = "Johan";
   // employee2.company = "python inc.";
   // employee2.age = 22;
   // employee2.introduce();

employee1.setAge(25);
    cout << "is " << employee1.getAge() << endl;
return 0;
}