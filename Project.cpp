#include <iostream>
#include <conio.h>
#include <fstream>
#include <vector>

using namespace std;

void showmainmenu();
void loginscreen();
void showadminpanel();
void addemployee();
void getemployeedetails();
void addnewmedicine();
void showmedicinelist();
void showhistory();
string compare(string str1, string str2);

bool login = 0;
bool cartempty = 1;

class Medicine
{
public:
	int stock, price;
	string name;

	Medicine* next;
	Medicine* left, * right;

	Medicine()
	{
		stock = price = -1;
		name = "";

		next = NULL;
		left = right = NULL;
	}

	Medicine(string name, int price, int stock)
	{
		this->name = name;
		this->price = price;
		this->stock = stock;

		next = NULL;
		left = right = NULL;
	}

	void printdetails()
	{
		cout << "Name: " << name
			<< "\nPrice: Rs. " << price
			<< "\nStock: " << stock << "\n\n";
	}
};

class Employee
{
public:
	int id, salary;
	string access_level, password, name;

	Employee* next, * prev;

	Employee()
	{
		id = salary = -1;
		access_level = password = name = "";

		next = prev = NULL;
	}

	Employee(int id, string name, string password, int salary, string access_level)
	{
		this->id = id;
		this->salary = salary;
		this->access_level = access_level;
		this->password = password;
		this->name = name;

		next = prev = NULL;
	}

	void showdetails()
	{
		cout << "\nName: " << name
			<< "\nID: " << id
			<< "\nSalary: " << salary
			<< "\nAccess Level: " << access_level << "\n";
	}
};

class Stack
{
public:
	Medicine* top;

	Stack()
	{
		top = NULL;
	}

	void push(Medicine* node)
	{
		if (top == NULL)
			top = node;

		else
		{
			node->next = top;
			top = node;
		}
	}
};

class BST
{
public:
	Medicine* root;

	BST()
	{
		root = NULL;
	}

	Medicine* insert(Medicine* root, Medicine* node)
	{
		if (root == NULL)
			return node;

		if (compare(root->name, node->name) == "l")
			root->left = insert(root->left, node);

		else if (compare(root->name, node->name) == "r")
			root->right = insert(root->right, node);

		return root;
	}

	void insert(Medicine node)
	{
		Medicine* newnode = new Medicine(node.name, node.price, node.stock);

		root = insert(root, newnode);
	}

	void inorder(Medicine* root)
	{
		if (root == NULL)
			return;

		inorder(root->left);
		root->printdetails();
		inorder(root->right);
	}

	Medicine* search(Medicine* root, string name)
	{
		if (root == NULL)
			return NULL;

		if (root->name == name)
			return root;

		if (compare(root->name, name) == "l")
			return search(root->left, name);

		else if (compare(root->name, name) == "r")
			return search(root->left, name);

		return NULL;
	}

} bst;

class List
{
public:
	Employee* front, * rear;

	List()
	{
		front = rear = NULL;
	}

	void insert(Employee e1)
	{
		Employee* node = new Employee;
		
		node->access_level = e1.access_level;
		node->id = e1.id;
		node->name = e1.name;
		node->password = e1.password;
		node->salary = e1.salary;

		if (front == NULL)
			front = rear = node;

		else
		{
			node->next = front;
			front = node;
		}
	}
} employees;

string compare(string str1, string str2)
{
	int len1 = str1.length();
	int len2 = str2.length();

	for (int i = 0; i < len1 && i < len2; i++)
	{
		if (str1[i] > str2[i])
			return "l";

		else if (str1[i] < str2[i])
			return "r";
	}

	if (len1 > len2)
		return "l";
	else if (len1 < len2)
		return "r";

	return "same";
}

class Transaction
{
public:
	int noofitems, totalbill, amount, change;
	string phone_num;

	Stack meds;

	Transaction()
	{
		noofitems = 0;
		totalbill = amount = change = -1;
		phone_num = "";
	}

	int get_noofitems()
	{
		return noofitems;
	}

	void additemtocart()
	{
		system("cls");

		string medname;

		cout << "[ADDING MEDICINE TO CART]\n\n";
		cout << "Name: ";
		cin >> medname;

		Medicine* node = bst.search(bst.root, medname);

		if (node == NULL)
		{
			cout << "Error: Medicine not found!\n\n1. Enter Again\t2. Go Back";
			char ch = _getch();

			if (ch == '1')
				additemtocart();
			else
				showmedicinelist();
		}

		Medicine* entry = new Medicine;
		
		if (node != NULL)
			entry->name = node->name;

		int count;
		cout << "Quantity: ";
		cin >> count;

		while (node->stock < count && node != NULL)
		{
			cout << "Not enough stock! Input a lower number: ";
			cin >> count;
		}

		entry->stock = count;
		entry->price = node->price;

		totalbill += entry->price * entry->stock;

		meds.push(entry);

		noofitems++;
		cartempty = 0;

		cout << "\nSuccessfully Added to cart! Press any key to continue.";

		_getch();

		showmedicinelist();
	}

	void viewcart()
	{
		system("cls");

		cout << "[CART]\n";

		Medicine* temp = meds.top;

		while (temp != NULL)
		{
			cout << endl << temp->name
				<< "\nQuantity: " << temp->stock
				<< "\nPrice: " << temp->price * temp->stock << endl;

			temp = temp->next;
		}

		cout << "\n----------------------------------";
		cout << "\nITEMS: " << noofitems;
		cout << "\n----------------------------------";

		cout << "\n\n1. Proceed to Check Out\n2. Go Back\n\n9. Go To Main Menu\n";

		char c;
		c = _getch();

		if (c == '1')
			checkout();

		else if (c == '2')
			showmedicinelist();

		else
			showmainmenu();
	}

	void checkout()
	{
		system("cls");

		cout << "[CHECKOUT PAGE]\n\n";

		Medicine* temp = meds.top;

		int count = 0;

		while (temp != NULL)
		{
			cout << "[ITEM " << ++count << "] "
				<< temp->name
				<< "\nQuantity: " << temp->stock
				<< "\nPrice: " << temp->price * temp->stock << "\n\n";

			temp = temp->next;
		}

		cout << "----------------------------------";
		cout << "\nITEMS: " << noofitems;
		cout << "\nTOTAL BILL: " << totalbill;
		cout << "\n----------------------------------";

		cout << "\nEnter Your Phone Number: ";
		cin >> phone_num;

		cout << "Enter Amount: ";

		cin >> amount;

		while (amount < totalbill)
		{
			cout << "Amount cannot be less than bill!\nEnter Amount: ";
			cin >> amount;
		}

		change = amount - totalbill;

		cout << "Change: " << change << endl;

		fstream f1("Transactions.dat", ios::app | ios::binary);

		f1.write((char*)&t1, sizeof(t1));

		f1.close();

		cout << "\nTHANK YOU FOR SHOPPING WITH US! PLEASE TAKE YOUR RECEIPT.\n\n";

		cout << "Press any key to return to main menu.";

		char c;
		c = _getch();

		resettransaction();
	}

	void resettransaction()
	{
		Medicine* temp = meds.top;

		while (temp != NULL)
		{
			Medicine* temp2 = temp;
			temp = temp->next;
			delete temp2;
		}

		amount = 0;
		change = 0;
		noofitems = 0;
		phone_num = "";
		totalbill = 0;

		showmainmenu();
	}

} t1;

void showmainmenu()
{
	system("cls");

	cout << "**** WELCOME TO FAST PHARMACEUTICAL! ****\n\n";
	cout << "Your one stop solution for all your drug needs!\n\n";
	cout << "What do you wish to do today ? \n\n";
	cout << "1. Shop For Medicines\n2. View Purchase History\n";

	if (login == 1) cout << "3. Admin Panel\n";
	else if (login == 0) cout << "3. Sign In\n";

	cout << "\nEnter your choice: ";

	char x;
	x = _getche();

	if (x == '1')
	{
		showmedicinelist();
	}
	else if (x == '2')
	{
		showhistory();
	}
	else if (x == '3')
	{
		if (login == 0)
			loginscreen();

		else if (login == 1)
			showadminpanel();
	}
	else showmainmenu();
}

int main()
{
	showmainmenu();
}

void showhistory()
{
	system("cls");

	string number;

	cout << "[PURCHASE HISTORY]\n\n";

	cout << "Enter Your Number: ";
	cin >> number;

	fstream f1("Transactions.dat", ios::in | ios::binary);
	Transaction temp;

	int count = 0;
	int logfound = 0;

	while (f1.read((char*)&temp, sizeof(temp)) && !logfound)
	{
		if (number == temp.phone_num)
		{
			cout << "\n[TRANSACTION " << ++count << "]"
				<< "\nNumber Of Items: " << temp.noofitems
				<< "\nTotal Bill: " << temp.totalbill
				<< "\nAmount Paid: " << temp.amount
				<< "\nChange Given: " << temp.change << endl;

			logfound = 1;
		}
	}
	if (!logfound)
		cout << "No Log Found!\n";

	cout << "\nPress any key to go back to main menu!";

	char c;
	c = _getch();

	showmainmenu();
}

void showmedicinelist()
{
	system("cls");

	cout << "[LIST OF AVAILABLE MEDICINES]\n\n";

	fstream f1("Medicines.dat", ios::in | ios::binary);
	Medicine temp;

	while (f1.read((char*)&temp, sizeof(temp)))
	{
		bst.insert(temp);
	}
	f1.close();

	bst.inorder(bst.root);

	cout << "----------------------------------\n";
	cout << "CART: " << t1.get_noofitems() << endl;
	cout << "----------------------------------\n";

	cout << "\n1. Add item to cart";

	if (!cartempty)
		cout << "\n2. View Cart and Checkout";

	cout << "\n\n9. Back to Main Menu";

	char c;
	c = _getch();

	if (c == '1')
	{
		t1.additemtocart();
	}
	else if (c == '2')
	{
		t1.viewcart();
	}
	else if (c == '9')
	{
		showmainmenu();
	}
	else showmedicinelist();

}

void loginscreen()
{
	system("cls");

	cout << "[EMPLOYEE LOGIN]\n\n";

	bool correct;
	do
	{
		correct = 0;
		string username, password;

		cout << "Username: ";
		cin >> username;

		char tempchar;
		cout << "Password: ";
		tempchar = _getch();

		while (tempchar != 13)
		{
			password.push_back(tempchar);
			cout << "*";
			tempchar = _getch();
		}

		fstream f1("Employees.dat", ios::in | ios::binary);
		Employee temp;

		while (f1.read((char*)&temp, sizeof(temp)))
		{
			if (temp.name == username && temp.password == password)
			{
				if (temp.access_level == "Admin")
				{
					correct = 1;
					login = 1;
					showadminpanel();
				}
				else
				{
					cout << "You don't have Admin access!\nPress any key to continue.";

					char c;
					c = _getch();

					correct = 0;
					login = 0;
					showmainmenu();
				}
			}
		}

		f1.close();

		if (username == "Mohsin" && password == "12345")
		{
			correct = 1;
			login = 1;
			showadminpanel();
		}
		else
		{
			system("cls");

			cout << "[EMPLOYEE LOGIN] ";

			cout << "Incorrect ID or Password! Try again.\n\n";
			correct = 0;
		}
	} while (!correct);
}

void showadminpanel()
{
	system("cls");

	cout << "[ADMIN PANEL]\n\n";
	cout << "1. Add New Employee\n2. Get Employee Details\n3. Add new Medicine\n4. Sign Out\n\n9. Main Menu\n";

	cout << "\nWhat do you want to do? ";

	char choice;
	choice = _getche();

	if (choice == '1')
	{
		addemployee();
	}
	else if (choice == '2')
	{
		getemployeedetails();
	}
	else if (choice == '3')
	{
		addnewmedicine();
	}
	else if (choice == '4')
	{
		login = 0;
		showmainmenu();
	}
	else if (choice == '9')
	{
		showmainmenu();
	}
	else
	{
		showadminpanel();
	}
}

void addemployee()
{
	system("cls");

	cout << "[ADD EMPLOYEE]\n\n";

	Employee e1;

	cout << "Enter Name: ";
	cin >> e1.name;

	cout << "Set Password: ";
	cin >> e1.password;

	cout << "ID: ";
	cin >> e1.id;

	cout << "Set Salary: ";
	cin >> e1.salary;

	cout << "Access Level (Employee/Admin): ";
	cin >> e1.access_level;

	fstream f1("Employees.dat", ios::app | ios::binary);

	f1.write((char*)&e1, sizeof(e1));

	f1.close();

	cout << "\nEmployee Added Successfully! Press any key to go back to the admin panel.";
	_getch();

	showadminpanel();
}

void reademployees()
{
	fstream f1("Employees.dat", ios::in | ios::binary);
	Employee temp;

	while (f1.read((char*)&temp, sizeof(temp)))
	{
		employees.insert(temp);
	}

	f1.close();
}

void getemployeedetails()
{
	system("cls");

	cout << "[EMPLOYEES]\n";

	reademployees();
	Employee* temp = employees.front;

	while (temp != NULL)
	{
		temp->showdetails();
		temp = temp->next;
	}

	cout << "\nPress any key to go back to the Admin Panel.";

	_getch();
	showadminpanel();
}

void addnewmedicine()
{
	system("cls");

	cout << "[ADDING NEW MEDICINE TO INVENTORY]\n\n";

	Medicine m1;

	cout << "Name: ";
	cin >> m1.name;

	cout << "Price: ";
	cin >> m1.price;

	cout << "Stock: ";
	cin >> m1.stock;

	fstream f1("Medicines.dat", ios::app | ios::binary);

	f1.write((char*)&m1, sizeof(m1));

	f1.close();

	cout << "\nMedicine Added Successfully!\n\nPress '1' to add another medicine, or press any other key to go back to Admin Panel.";

	char key;
	key = _getch();

	if (key == '1')
		addnewmedicine();

	else showadminpanel();
}