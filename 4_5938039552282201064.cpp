#include<iostream>
#include<string>
#include<fstream>
using namespace std;

int n = 0, choice = 0;
struct product_info {
	int id = 0;
	string name = "";
	int price = 0;
	int count = 0;
}*products;

void menu();
void show_list();
void load();
void in_file();
int search_ID(int ID);
void search();
void add();
void edit();
void buy();
void del();
void count_n();

int main() {
	count_n();
	if(n>0)
		load();
	while (choice != 7) {
		menu();
		switch (choice) {
		case 1: add(); load(); break;
		case 2: edit(); in_file(); load(); break;
		case 3: del(); in_file(); load(); break;
		case 4: search(); break;
		case 5: show_list(); break;
		case 6: buy(); in_file(); load();  break;
		}
	}
	in_file();
	return 0;
}

void show_list() {
	for (int i = 0; i < n; i++) {
		cout << endl << "Product " << i + 1 << ":" << endl;
		cout << "id:" << products[i].id << endl;
		cout << "name:" << products[i].name << endl;
		cout << "price:" << products[i].price << endl;
		cout << "count:" << products[i].count << endl;
	}
}
void load() {
	string line;
	ifstream Product_info;
	Product_info.open("products.txt");
	int k = 0;
	delete[] products;
	products = new product_info[n];
	while (getline(Product_info, line))
	{
		string array[4];
		int j = 0;
		for (int i = 0; i < line.length(); i++)
		{
			if (line[i] != ',')
				array[j] = array[j] + line[i];
			if (line[i] == ',' || i == line.length() - 1) {
				switch (j) {
				case 0:
					products[k].id = stoi(array[j]);
					break;
				case 1:
					products[k].name = array[j];
					break;
				case 2:
					products[k].price = stoi(array[j]);
					break;
				case 3:
					products[k].count = stoi(array[j]);
					break;
				}
				j++;
			}
		}
		k++;
	}
	Product_info.close();
}

void in_file(){
	ofstream Product_info;
	Product_info.open("products.txt");
	int i;
	for (i = 0; i < n; i++) {
		Product_info << products[i].id << "," << products[i].name << "," << products[i].price << "," << products[i].count;
		if(i!=n-1)
			Product_info << endl;
	}
	Product_info.close();
}

int search_ID(int a){
	for (int i = 0; i < n; i++)
		if (products[i].id == a) 
			return i;
	return -1;
}

void search(){
	int id;
	cout << "Enter id:";
	cin >> id;
	int i = search_ID(id);
	cout << "Product " << i + 1 << ":" << endl;
	cout << "id:" << products[i].id << endl;
	cout << "name:" << products[i].name << endl;
	cout << "price:" << products[i].price << endl;
	cout << "count:" << products[i].count << endl;
}

void add(){
	product_info p;
	ofstream Product_info;
	Product_info.open("products.txt", ios::app);
	cout << "Enter id:";
	cin >> p.id;
	cout << "Enter name:";
	cin >> p.name;
	cout << "Enter price:";
	cin >> p.price;
	cout << "Enter count:";
	cin >> p.count;
	if (n != 0)
		Product_info << endl;
	Product_info << p.id << "," << p.name << "," << p.price << "," << p.count;
	n++;
	Product_info.close();
}

void edit(){
	int id;
	cout << "Enter id:";
	cin >> id;
	int i = search_ID(id);
	cout << "Enter name:";
	cin >> products[i].name;
	cout << "Enter price:";
	cin >> products[i].price;
	cout << "Enter count:";
	cin >> products[i].count;
}

void del(){
	int id,j;
	cout << "Enter id:";
	cin >> id;
	int i = search_ID(id);
	n--;
	for ( j = i; j < n; j++)
		products[j] = products[j + 1];
}

void buy()
{
	bool Q= true;
	int sum=0,j=0,i;
	product_info p[100];
	while (Q){
		int id;
		cout << "Enter id:";
		cin >> id;
		i = search_ID(id);
		if (i >= 0) {
			cout << "Enter count: ";
			cin >> p[j].count;
			if (p[j].count <= products[i].count) {
				products[i].count -= p[j].count;
				p[j].id = products[i].id;
				p[j].name = products[i].name;
				p[j].price = products[i].price;
				sum = sum + p[j].price*p[j].count;
				j++;
			}
			else 
				cout << "Not enough!";
		}
		if (j >= 100)
			break;
		cout << "Enter 0 for Exit:";
		cin >> Q;
	}
	cout << "____________list_______________" << endl;
	for (int i = 0; i < j; i++){
		cout << "name:" << p[i].name << endl;
		cout << "price:" << p[i].price << endl;
		cout <<"count:" << p[i].count << endl;
		cout << "_______________________________" << endl;
	}
	cout << "sum = " << sum << endl;
}
void count_n() {
	ifstream Product_info;
	Product_info.open("products.txt");
	string line;
	while (getline(Product_info, line))
		n++;
}
void menu() {
	cout << "\tSTORE MENU\n1-Add Product\n2-Edit Product\n3-Delete Product\n4-Search\n5-Show list\n6-Buy\n7-Exit\n";
	cin >> choice;
}
