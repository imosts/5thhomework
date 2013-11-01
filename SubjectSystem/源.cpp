#include<iostream>
#include<string>
#include<vector> 
using namespace std;

class Student{
public:
	Student(){
		this->choice=1;
		this->grade=0;
	}

	string getName(){
		return this->name;
	}
	string getNumber(){
		return this->number;
	}
	bool getChoice(){
		return choice;
	}
	int getGrade(){
		return this->grade;
	}
	void SeleSubject(bool a){
		this->choice=a;
	}
	void InputGrade(int a){
		this->grade=a;
	}
	void input();				//用于输入姓名和学号
	void inputNumber();			//只输入学号查找
private:
	string name;
	string number;
	int grade;
	bool choice;
};

void Student::input(){
	cout<<"请输入学生姓名:"<<endl;
	cin>>this->name;
	cout<<"请输入学号:"<<endl;
	cin>>this->number;
}

void Student::inputNumber(){
	cout<<"请输入学号:"<<endl;
	cin>>this->number;
}


class MenuItem{
public:
	MenuItem(string a):caption(a){}
	string getCaption(){
		return caption;							// this->caption 和 caption 有什么区别？
	}
	virtual bool act() = 0;
private:
	string caption;
};

class Menu{
public:
    void append(MenuItem* mi);
    int run();
private:
    void show();
	vector<MenuItem*> items;
};

class SelectObject{
	public:
    SelectObject();
    int run();
	Menu menu;
};

class Operator{
public:
	void list();
	void add();
	void sele();
	void grad();
private:
	vector<Student *> students;
	Student * find(Student * student);
};

Operator operators;

class ShowList:public MenuItem{
public:
	ShowList():MenuItem("查看学生信息"){}
	bool act(){
		operators.list();
		return false;
	}
};

class Input:public MenuItem{
public:
	Input():MenuItem("添加学生"){}
	bool act(){
		operators.add();
		return false;
	}
};

class Object:public MenuItem{
public:
	Object():MenuItem("学生选课"){}
	bool act(){
		operators.sele();
		return false;
	}
};

class getGrade:public MenuItem{
public:
	getGrade():MenuItem("输入成绩"){}
	bool act(){
		operators.grad();
		return false;
	}
};

class Exit:public MenuItem{
public:
    Exit():MenuItem("退出程序"){}
    bool act(){
        cout << "退出程序！" << endl;
        return true;
    }
};

void Menu::append(MenuItem* mi){
    this->items.push_back(mi);
}

SelectObject::SelectObject(){
    menu.append(new ShowList());
    menu.append(new Input());
    menu.append(new Object());
	menu.append(new getGrade());
    menu.append(new Exit());
}

int SelectObject::run(){
	return menu.run();
}

int Menu::run(){
 int index;
    while(1){
        this->show();
        cin>>index;
        if(!cin || index<1 || index>items.size()){
            cout << "错误的菜单项，请重新输入："<<endl;
            if(!cin){
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            continue;
        }
        if(items[index-1]->act()) break;
    }
    return 0;
}

void Menu::show(){
    int i=0;
    for(auto &item:items){
        cout<< ++i <<")" <<item->getCaption() <<endl;
    }
}

void Operator::list(){
	cout<<"--------------------------------查看学生信息--------------------------------"<<endl<<endl;
	cout<<"学生姓名\t"<<"学号\t\t"<<"是否选课（1代表选，0代表没选）\t\t"<<"成绩\t"<<endl;
	for(int i=0; i<this->students.size(); i++){
        cout<<this->students[i]->getName()<<"\t";
		cout<<this->students[i]->getNumber()<<"\t\t\t";
		cout<<this->students[i]->getChoice()<<"\t\t\t";
		cout<<this->students[i]->getGrade()<<"\t";
    }
	cout<<endl;
    cout<<"--------------------------------查看学生信息--------------------------------"<<endl<<endl;

}

void Operator::add(){
	int a;
	do{
	cout<<"--------------------------------请输入学生信息--------------------------------"<<endl;
	cout<<endl;
	Student* temp = new Student;
    temp->input();
    Student* result = this->find(temp);
    if(result == NULL){
		this->students.push_back(temp);
		cout<<"添加成功！"<<endl;
    }else{
       cout<<"该学生已存在"<<endl;
    }
		cout<<"继续请按1，否则按0"<<endl;
		cin>>a;
		
	}while(a);
}

void Operator::sele(){
	bool select;
	cout<<"--------------------------------请输入学生信息--------------------------------"<<endl;
	cout<<endl;
	Student* temp = new Student;
    temp->inputNumber();
    Student* result = this->find(temp);
    if(result == NULL){
		cout<<"该学生不存在！请先输入该学生的信息！"<<endl;
    }else{
		cout<<"--------------------------------请检查学生信息--------------------------------"<<endl;
		cout<<"学生姓名："<<result->getName()<<endl;
		cout<<"学号："<<result->getNumber()<<endl;
		cout<<"是否选课："<<result->getChoice()<<endl;
		cout<<"分数："<<result->getGrade()<<endl;
		cout<<"确认选课请输入1，否者输入0."<<endl;
		cin>>select;
		result->SeleSubject(select);
	}
}

void Operator::grad(){
	int grade;
	cout<<"--------------------------------请输入学生信息--------------------------------"<<endl;
	cout<<endl;
	Student* temp = new Student;
    temp->inputNumber();
    Student* result = this->find(temp);
    if(result == NULL){
		cout<<"该学生不存在！请先输入该学生的信息！"<<endl;
    }else{
		if(!result->getChoice())
			cout<<"该学生没有选课，无法输入成绩！"<<endl;
		else
		{
		cout<<"--------------------------------请检查学生信息--------------------------------"<<endl;
		cout<<"学生姓名："<<result->getName()<<endl;
		cout<<"学号："<<result->getNumber()<<endl;
		cout<<"是否选课："<<result->getChoice()<<endl;
		cout<<"分数："<<result->getGrade()<<endl;
		cout<<"请输入学生成绩"<<endl;
		cin>>grade;
		result->InputGrade(grade);
		}
	}
}

Student* Operator::find(Student* sudents){
	for(int i=0; i<this->students.size(); i++){
		if(sudents->getNumber()==students[i]->getNumber())
			return students[i];
	}
        return NULL;
}

int main(){
	SelectObject SO;
	return SO.run();
}