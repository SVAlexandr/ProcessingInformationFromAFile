#include <iostream>
#include <string>
#include <ctime>
#include <Windows.h>
#include <fstream>
#include <memory>
using namespace std;
#define FCats "Cats.txt"
#define FResults "Results.txt"

int RandInt(int a)
{
	srand(time(NULL));
	return rand() % a;
}

enum State
{
	OFF,
	ADDH,
	ADDA,
	PLAY,
	SEE
};

struct Cat
{

	int position;
	string type;
	string name;
	string color;
	int age;
	string par;
	string sname;

	Cat()
	{
		this->position = 0;
		this->type = "Безродная";
		this->name = "Безымянная";
		this->color = "Безцветная";
		this->age = 0;
		this->par = "н/д";
		this->sname = "н/д";
	}

	Cat(int position,char type,string name,string color, int age, string par, string sname)
	{
		this->position = position;
		this->type = type;
		this->name = name;
		this->color = color;
		this->age = age;
		this->par = par;
		this->sname = sname;
	}

	void OutCat()
	{
		cout << this->position << "\t" << this->type + "\t" << this->name + "\t" << this->color + "\t" << this->age << "\t" << this->par + "\t" << this->sname + "\n";
	}

	/*~Cat()
	{
		delete this->type.data();
		delete this->name.data();
		delete this->color.data();
		delete this->par.data();
		delete this->sname.data();
	}*/

};

void AddCatH(Cat cat, State* state)
{
	if (*state == ADDH)
	{
		for (int i = 0; i < 7; i++)
		{
			switch (i)
			{
			case 2:
			{
				cout << "Введите породу кошки\n";
				cin >> cat.type;
				break;
			}
			case 1:
			{
				cout << "Введите кличку кошки\n";
				cin >> cat.name;
				break;
			}
			case 3:
			{
				cout << "Введите окрас кошки\n";
				cin >> cat.color;
				break;
			}
			case 4:
			{
				cout << "Введите возраст кошки\n";
				cin >> cat.age;
				break;
			}
			case 5:
			{
				cout << "Введите родителей (через'/') кошки\n";
				cin >> cat.par;
				break;
			}
			case 6:
			{
				cout << "Введите фамилию хозяина кошки\n";
				cin >> cat.sname;
				break;
			}
			case 0:
			{
				//cout << "Введите место в конкурсе кошки\n";
				(cat.position) = 0;
				break;
			}
			default:
			{
				cout << "Ошибка!\n";
				break;
			}
			}
		}
	}/*else if(state==ADDA)
	{

	}*/
	ofstream Cats;
	Cats.open(FCats, ofstream::app);
	if (!Cats.is_open())
	{
		cout << "Ошибка чтения файла\n";
	}else
	{
		Cats.write((char*)&cat, sizeof(Cat));
		Cats.close();
	}
}

void ChangeState(State* state, char a);

void AddCat(Cat cat,State* state)
{
	char a ='a';
	cout << "Записать кошку на соревнование (h)/ в автоматическом режиме, для масовки(a)\n";
	cin >> a;
	ChangeState(state, a);
	if (a=='h')
	{
		AddCatH(cat, state);
	}else
	{
		ofstream Cats;
		Cats.open(FCats, ofstream::app);
		if (!Cats.is_open())
		{
			cout << "Ошибка открытия файла\n";
		}else
		{
			Cats.write((char*)&cat, sizeof(Cat));
			Cats.close();
		}
	}
}

void ChangeState(State*state,char a)
{
	switch (a)
	{
	case 'a': *state = ADDA;
		break;
	case 'p': *state = PLAY;
		break;
	case 's': *state = SEE;
		break;
	case 'n': *state = OFF;
		break;
	case 'h': *state = ADDH;
		break;
	default:
		break;
	}
}

void PlayCats()
{
	fstream Cats;
	Cats.open(FCats, fstream::in | fstream::out | fstream::app);
	if (!Cats.is_open())
	{
		cout << "Ошибка открытия файла\n";
	}
	else
	{
		Cats.seekp(0, ios::end);
		int size = int(Cats.tellp() / sizeof(Cat));
		Cats.seekp(0, ios::beg);
		Cat* cats = new Cat[size];
		for (int i = 0; i < size; i++)
		{
			Cats.read((char*)&cats[i], sizeof(Cat));
			cats[i].position = 0;
			bool b = true;
			while (b)
			{
				//srand(time(NULL));
				int poz = RandInt(size) + 1;
				for (int j=0;j<=i;j++)
				{
					if (cats[j].position==poz)
					{
						break;
					}
					if(j==i)
					{
						cats[i].position = poz;
						b = false;
					}
				}
			}
		}
		Cats.close();
		Cats.open(FCats, fstream::in | fstream::out);
		if (!Cats.is_open())
		{
			cout << "Ошибка открытия файла\n";
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				Cats.write((char*)&cats[i], sizeof(Cat));
			}
			Cats.close();
		}
		delete[] cats;
	}
}

void OutCats(/*Cat cat*/)
{
	ifstream Cats;
	//Cat* cat=new Cat;
	//Cat cat;
	Cats.open(FCats);
	if (!Cats.is_open())
	{
		cout << "Ошибка чтения файла\n";
	}else
	{
		static Cat cat;
		while (Cats.read((char*)&cat, sizeof(Cat)))
		{
			cat.OutCat();
		}
		Cats.close();
	}
	//Cats.close();
	//delete cat;
}

void SeeCats()
{
	fstream Cats;
	Cats.open(FCats,fstream::in|fstream::app);
	if (!Cats.is_open())
	{
		cout << "Ошибка открытия файла\n";
	}
	else
	{
		Cats.seekp(0, ios::end);
		int size = int(Cats.tellp() / sizeof(Cat));
		Cats.seekp(0, ios::beg);
		Cat* cats = new Cat[size];
		for (int i = 0; i < size; i++)
		{
			Cats.read((char*)&cats[i], sizeof(Cat));
		}
		Cats.close();
		ofstream CatsOut;
		CatsOut.open(FResults);
		if (!CatsOut.is_open())
		{
			cout << "Ошибка открытия файла\n";
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				CatsOut<< cats[i].position << "\t" << cats[i].type + "\t" << cats[i].name + "\t" << cats[i].color + "\t" << cats[i].age << "\t" << cats[i].par + "\t" << cats[i].sname + "\n";
			}
			//CatsOut.close();
		}
		CatsOut.close();
		delete[] cats;
		cats = nullptr;
	}
}

int main()
{
	setlocale(LC_ALL, "Ru");
	char a;
	State state = ADDA;
	//Cat cate;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	while (state!=OFF)
	{
		cout << "Введите:\na - для записи кошки на состязание;\np - для проведения состязания;\ns - для вывода результатов;\nn - для выхода из программы\n";
		cin >> a;
		ChangeState(&state, a);
		if (state==ADDA)
		{
			Cat cat;
			AddCat(cat, &state);
		}
		else if (state == PLAY)
		{
			PlayCats();
		}else if (state==SEE)
		{
			OutCats(/*cate*/);
			SeeCats();
		}
	}
	SetConsoleCP(866);
	SetConsoleOutputCP(866);
}