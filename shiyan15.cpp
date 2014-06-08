/*
   这个程序更加要注意，一定将两个基类的析构函数设置为virtual
   否则会出现很严重的后果，仔细分析就可以发现
   */
#include<iostream>
#include<string>
using namespace std;
enum GRADE{one=1,two,three,four};
class people
{
	private:
		static int num_of_people;//开始就初始为0
		static int set_num_of_people(const int &n );
		short p_age;
	public:
		people(int a=0):p_age(a){}
		int print_num_of_people() const;
		int add_people() { return ++num_of_people; }
		int del_people() { return --num_of_people; }
		short get_age() const
		{
			return p_age;
		}
		virtual ~people(){};
		int set_age(int a){ p_age+=a;}
};
///////////pppppppppppppppppppppppppppppppppppppppppppppppppppppp
///AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
class attend_class
{
	public:
		virtual int attend()=0;
		virtual ~attend_class(){ };
};
///AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
int people::num_of_people=0;
int people::set_num_of_people(const int &n)
{
	people::num_of_people=n;
	return n;
}
int people::print_num_of_people() const
{
	cout<<"num_of_people: "<<people::num_of_people<<endl;
}
///////////ppppppppppppppppppppppppppppppppppppppppppppppppppppppp
class course// 功课类
{
	private:
		string c_id;
		string c_name;
		int c_score;
	public:
		course();
		int print()
		{
			cout<<"c_id:"<<c_id<<' '<<"c_name:"<<c_name<<' '<<"c_score:"<<c_score<<endl;
			return 0;
		}
		friend istream & operator>>(istream &in,course &cou);
};
class student:public people,public attend_class
{
	private:
		string s_id;
		string s_name;
		enum GRADE s_grade;
		string s_class_id;
		int s_c_num;//选修课程数目
		course *s_c_select;
	public:
		student operator+(const int &age) const;
		student operator+(const enum GRADE &grage) const;
		student operator+(const course &course) const;
		student operator=(const student &stu);
		int print() const;
		student();
		friend istream & operator>>(istream &in,student &stu);
		student(const student &stu);
		int tr_point() const;//遍历s_c_select
		virtual int attend();//前面的virtual可以不用加
		~student();
};
class my_grade
{
	private:
		int s_num; 
		student *g_stu;
		string g_id;
		string g_name;
	public:
		my_grade(const char *id);
		my_grade(const string &id);
		my_grade();
		~my_grade();
		friend istream & operator>>(istream &in,my_grade &gra);
		int tr_point() const;
		int print()
		{
			cout<<"s_num:"<<s_num<<endl;
			cout<<"g_id:"<<g_id<<endl;
			return 0;
		}
		my_grade operator+(const student &stu) const ;//一个学生
		my_grade(const my_grade &gra);
		my_grade operator=(const my_grade &gra);
		//添加一批一批学生循环调用添加一个学生就行了
};
class teacher:public people,public attend_class
{
	private:
		string t_id;
		string t_name;
	public:
		teacher();
		~teacher();
		virtual int attend();
		teacher operator+(const int &age) const;
};
//////////////ttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt
teacher teacher::operator+(const int &age) const
{
	teacher temp(*this);
	temp.set_age(age+temp.get_age());
	return temp;
}
teacher::teacher():people(0)
{
	add_people();
	print_num_of_people();
	return ;
}
teacher::~teacher()
{
	del_people();
}
int teacher::attend()
{
	cout<<"这是老师在上课 ^_^"<<endl;
	return 0;
}
//////////////ttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttttt
course::course():c_score(0)
{
	//cout<<"this is construct of course \n";
	return ;
}
istream & operator>>(istream &in,course &cou)
{
	in>>cou.c_id>>cou.c_name>>cou.c_score;
	return in;
}
int student::attend()
{
	cout<<"这是学生在上课 ^_^"<<endl;
	return 0;
}
istream & operator>>(istream &in,student &stu)
{
	in>>stu.s_id>>stu.s_name>>stu.s_class_id;
	return in;
}
student::student():people(0),s_grade(one),s_c_num(0)
{
	add_people();
	print_num_of_people();
	s_c_select=new course[20];
	return ;
}
student::~student()
{
	del_people();
	delete [] s_c_select;
}
int student::print() const
{
	cout<<"s_age:"<<get_age()<<endl;
	cout<<"s_grade:"<<s_grade<<endl;
	cout<<"s_c_num:"<<s_c_num<<endl;
	return 0;
}
student student::operator+(const int &age) const
{
	student temp(*this);
	temp.set_age(age+temp.get_age());
	return temp;
}
student student::operator+(const enum GRADE &grade) const
{
	student temp(*this);
	temp.s_grade=GRADE(int(grade)+int(temp.s_grade));
	return temp;
}
student student::operator+(const course &course) const
{
	student temp(*this);
	temp.s_c_select[temp.s_c_num]=course;
	temp.s_c_num++;
	if(temp.s_c_num > 19)//保证课程数组不越界
		temp.s_c_num=19;
	return temp;
}
student student::operator=(const student &stu)
{
	//下面的this 可以去掉
	this->s_id=stu.s_id;
	this->s_name=stu.s_name;
	this->set_age(stu.get_age());
	this->s_grade=stu.s_grade;
	this->s_class_id=stu.s_class_id;
	this->s_c_num=stu.s_c_num;
	for(int i=0;i<s_c_num;i++)
		s_c_select[i]=stu.s_c_select[i];
	return *this;
}
int student::tr_point() const //遍历s_c_select
{
	cout<<"studemt tr_point c_num:"<<s_c_num<<endl;
	for(int i=0;i<s_c_num;i++)
		s_c_select[i].print();
	return 0;
}

my_grade::my_grade(const char *id):s_num(0)//转换构造函数 char to string
{
	g_stu=new student [100];//////////////////////////////
	string temp_id(id);
	g_id=temp_id;
	return ;
}
my_grade::my_grade(const string &id):s_num(0)//转换构造函数 string 还是string
{
	g_stu=new student [100];
	g_id=id;
	return ;
}
my_grade::my_grade():s_num(0)
{
	g_stu=new student [100];
	return ;
}
istream & operator>>(istream &in,my_grade &gra)
{
	in>>gra.s_num>>gra.g_id>>gra.g_name;
	return in;
}
student::student(const student &stu)
{//this 可以不要
	add_people();
	print_num_of_people();
	s_c_select=new course[20];
	this->s_id=stu.s_id;
	this->s_name=stu.s_name;
	this->set_age(stu.get_age());
	this->s_grade=stu.s_grade;
	this->s_class_id=stu.s_class_id;
	this->s_c_num=stu.s_c_num;
	for(int i=0;i<s_c_num;i++)
		s_c_select[i]=stu.s_c_select[i];
}
my_grade::~my_grade()
{
	delete [] g_stu;
}
int my_grade::tr_point() const
{
	cout<<"my_grade tr_point s_num:"<<s_num<<endl;
	for(int i=0;i<s_num;i++)
		g_stu[i].print();
	return 0;
}
my_grade::my_grade(const my_grade &gra)
{
	g_stu=new student [100];
	s_num=gra.s_num;
	//student *g_stu=gra.g_stu;
	g_id=gra.g_id;
	g_name=gra.g_name;
	for(int i=0;i<s_num;i++)
		g_stu[i]=gra.g_stu[i];
}
my_grade my_grade::operator=(const my_grade &gra)
{
	s_num=gra.s_num;
	//student *g_stu=gra.g_stu;
	g_id=gra.g_id;
	g_name=gra.g_name;
	for(int i=0;i<s_num;i++)
		g_stu[i]=gra.g_stu[i];
	return *this;
}
my_grade my_grade::operator+(const student &stu) const//添加一个学生
{
	my_grade temp(*this);
	temp.g_stu[s_num]=stu;
	temp.s_num++;
	if(temp.s_num>99)
		temp.s_num=99;
	return temp;
}
int main()
{

	cout<<"前面输出那么多是在定义班级的时候有一个100的对象数组"<<endl;
	int i;
	string id("2011310200810");
	student s;
	my_grade m(id);
	course c;
	s.print();
	m.print();
	m=m+s;
	m.print();
	cout<<"ok"<<endl;
	s=s+1;
	cout<<"s.print()"<<endl;
	s.print();
	cout<<"s.print()"<<endl;
	GRADE g=one;
	s=s+g;
	s=s+c;
	s.print();
	m.tr_point();
	s.tr_point();
	cout<<"测试输出人数:"<<endl;
	people *p[10],*q[10];
	for(i=0;i<10;i++)
	{
		p[i]=new student;
		q[i]=new teacher;
	}
	for(i=0;i<10;i++)
	{
		delete p[i];
		delete q[i];
	}

	cout<<"最后需函数测试："<<endl;
	attend_class *a1,*a2;
	a1=new teacher;
	a2=new student;
	a1->attend();
	a2->attend();
	delete a1;
	delete a2;
	cout<<"输入运算符重载测试"<<endl;
	course c1;
	cin>>c1;
	c1.print();
	student c2;
	//cin>>c2;
	//c2.print();
	return 0;
}
