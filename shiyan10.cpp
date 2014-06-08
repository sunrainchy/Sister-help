#include<iostream>
#include<string>
using namespace std;
enum GRADE{one=1,two,three,four};
class course// 功课类
{
	private:
		string c_id;
		string c_name;
		int c_score;
	public:
		course();
};
class student
{
	private:
		string s_id;
		string s_name;
		short s_age;
		enum GRADE s_grade;
		string s_class_id;
		int s_c_num;//选修课程数目
		course s_c_select[20];
	public:
		student operator+(const int &age) const;
		student operator+(const enum GRADE &grage) const;
		student operator+(const course &course) const;
		int print();
		student();
};
class my_grade
{
	private:
		int s_num; 
		student g_stu[100];
		string g_id;
		string g_name;
	public:
		my_grade();
		int print()
		{
			cout<<"s_num:"<<s_num<<endl;
			return 0;
		}
		my_grade operator+(const student &stu) const ;//一个学生
		//添加一批一批学生循环调用添加一个学生就行了
};
course::course():c_score(0)
{
	//cout<<"this is construct of course \n";
	return ;
}
student::student():s_age(0),s_grade(one),s_c_num(0)
{
	return ;
}
int student::print()
{
	cout<<"s_age:"<<s_age<<endl;
	cout<<"s_grade:"<<s_grade<<endl;
	cout<<"s_c_num:"<<s_c_num<<endl;
	return 0;
}
student student::operator+(const int &age) const
{
	student temp(*this);
	temp.s_age+=age;
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
my_grade::my_grade():s_num(0)
{
	return ;
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
	student s;
	my_grade m;
	course c;
	s.print();
	m.print();
	m=m+s;
	m.print();
	s=s+1;
	GRADE g=one;
	s=s+g;
	s=s+c;
	s.print();
	return 0;
}
