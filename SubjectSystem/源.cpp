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
	void input();				//��������������ѧ��
	void inputNumber();			//ֻ����ѧ�Ų���
private:
	string name;
	string number;
	int grade;
	bool choice;
};

void Student::input(){
	cout<<"������ѧ������:"<<endl;
	cin>>this->name;
	cout<<"������ѧ��:"<<endl;
	cin>>this->number;
}

void Student::inputNumber(){
	cout<<"������ѧ��:"<<endl;
	cin>>this->number;
}


class MenuItem{
public:
	MenuItem(string a):caption(a){}
	string getCaption(){
		return caption;							// this->caption �� caption ��ʲô����
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
	ShowList():MenuItem("�鿴ѧ����Ϣ"){}
	bool act(){
		operators.list();
		return false;
	}
};

class Input:public MenuItem{
public:
	Input():MenuItem("���ѧ��"){}
	bool act(){
		operators.add();
		return false;
	}
};

class Object:public MenuItem{
public:
	Object():MenuItem("ѧ��ѡ��"){}
	bool act(){
		operators.sele();
		return false;
	}
};

class getGrade:public MenuItem{
public:
	getGrade():MenuItem("����ɼ�"){}
	bool act(){
		operators.grad();
		return false;
	}
};

class Exit:public MenuItem{
public:
    Exit():MenuItem("�˳�����"){}
    bool act(){
        cout << "�˳�����" << endl;
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
            cout << "����Ĳ˵�����������룺"<<endl;
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
	cout<<"--------------------------------�鿴ѧ����Ϣ--------------------------------"<<endl<<endl;
	cout<<"ѧ������\t"<<"ѧ��\t\t"<<"�Ƿ�ѡ�Σ�1����ѡ��0����ûѡ��\t\t"<<"�ɼ�\t"<<endl;
	for(int i=0; i<this->students.size(); i++){
        cout<<this->students[i]->getName()<<"\t";
		cout<<this->students[i]->getNumber()<<"\t\t\t";
		cout<<this->students[i]->getChoice()<<"\t\t\t";
		cout<<this->students[i]->getGrade()<<"\t";
    }
	cout<<endl;
    cout<<"--------------------------------�鿴ѧ����Ϣ--------------------------------"<<endl<<endl;

}

void Operator::add(){
	int a;
	do{
	cout<<"--------------------------------������ѧ����Ϣ--------------------------------"<<endl;
	cout<<endl;
	Student* temp = new Student;
    temp->input();
    Student* result = this->find(temp);
    if(result == NULL){
		this->students.push_back(temp);
		cout<<"��ӳɹ���"<<endl;
    }else{
       cout<<"��ѧ���Ѵ���"<<endl;
    }
		cout<<"�����밴1������0"<<endl;
		cin>>a;
		
	}while(a);
}

void Operator::sele(){
	bool select;
	cout<<"--------------------------------������ѧ����Ϣ--------------------------------"<<endl;
	cout<<endl;
	Student* temp = new Student;
    temp->inputNumber();
    Student* result = this->find(temp);
    if(result == NULL){
		cout<<"��ѧ�������ڣ����������ѧ������Ϣ��"<<endl;
    }else{
		cout<<"--------------------------------����ѧ����Ϣ--------------------------------"<<endl;
		cout<<"ѧ��������"<<result->getName()<<endl;
		cout<<"ѧ�ţ�"<<result->getNumber()<<endl;
		cout<<"�Ƿ�ѡ�Σ�"<<result->getChoice()<<endl;
		cout<<"������"<<result->getGrade()<<endl;
		cout<<"ȷ��ѡ��������1����������0."<<endl;
		cin>>select;
		result->SeleSubject(select);
	}
}

void Operator::grad(){
	int grade;
	cout<<"--------------------------------������ѧ����Ϣ--------------------------------"<<endl;
	cout<<endl;
	Student* temp = new Student;
    temp->inputNumber();
    Student* result = this->find(temp);
    if(result == NULL){
		cout<<"��ѧ�������ڣ����������ѧ������Ϣ��"<<endl;
    }else{
		if(!result->getChoice())
			cout<<"��ѧ��û��ѡ�Σ��޷�����ɼ���"<<endl;
		else
		{
		cout<<"--------------------------------����ѧ����Ϣ--------------------------------"<<endl;
		cout<<"ѧ��������"<<result->getName()<<endl;
		cout<<"ѧ�ţ�"<<result->getNumber()<<endl;
		cout<<"�Ƿ�ѡ�Σ�"<<result->getChoice()<<endl;
		cout<<"������"<<result->getGrade()<<endl;
		cout<<"������ѧ���ɼ�"<<endl;
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