#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<vector>
using namespace std;
class imfo {
private:
	char departure[30];
	char arrival[30];
	float price;
	int departure_time;
	int arrival_time;
	int type;
	string number;
public:
	imfo(float p = 0, int d_time = 0, int a_time = 0, string num = "",int type=0);
	imfo(const imfo &imfo_copied);
	~imfo();
	void Set_departure(char *copied);
	void Set_arrvial(char *copied);
	void Set_price(float money);
	void Set_departure_time(int time);
	void Set_arrival_time(int time);
	void Set_number(string num);
	void Set_type(int travel_type);
	float Get_price();
	int Get_departure_time();
	int Get_arrival_time();
	string Get_number();
	void print();
	void printout();
	void nametonum(int &x, int &y);
    char* get_departure(){
        return departure;
    }
    char* get_arrival(){
        return arrival;
    }
    int get_departure_time(){
        return departure_time;
    }
    int get_arrival_time(){
        return arrival_time;
    }
    int get_type(){
        return type;
    }
};
