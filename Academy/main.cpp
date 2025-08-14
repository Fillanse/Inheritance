#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>

using std::cin;
using std::cout;
using std::endl;

#define delimiter "\n------------------------------------\n"

#define HUMAN_TAKE_PARAMETERS const std::string& last_name, const std::string& first_name, int age
#define HUMAN_GIVE_PARAMETERS last_name, first_name, age

class Human
{
	static const int LAST_NAME_WIDTH = 15;
	static const int FIRST_NAME_WIDTH = 15;
	static const int AGE_WIDTH = 3;
	static int count;
	std::string last_name;
	std::string first_name;
	int age;
public:
	static int get_count() { return count; }
	const std::string& get_last_name()const { return last_name; }
	const std::string& get_first_name()const { return first_name; }
	int get_age()const { return age; }
	void set_last_name(const std::string& last_name) { this->last_name = last_name; }
	void set_first_name(const std::string& first_name) { this->first_name = first_name; }
	void set_age(int age) { this->age = age; }

	Human(HUMAN_TAKE_PARAMETERS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		count++;
		cout << "HConstructor:\t" << this << endl;
	}
	virtual ~Human()
	{
		count--;
		cout << "HDestructor:\t" << this << endl;
	}

	virtual std::ostream& info(std::ostream& os)const
	{
		os.width(LAST_NAME_WIDTH);
		os << std::left << last_name;
		os.width(FIRST_NAME_WIDTH);
		os << first_name;
		os.width(AGE_WIDTH);
		os << age;
		return os;
	}

	// для записи в файл
	virtual void save(std::ostream& os) const
	{
		os << "Human;" << last_name << ";" << first_name << ";" << age << "\n";
	}
};

int Human::count = 0;

std::ostream& operator<<(std::ostream& os, const Human& obj)
{
	return obj.info(os);
}

#define STUDENT_TAKE_PARAMETERS const std::string& speciality, const std::string& group, double rating, double attendance
#define STUDENT_GIVE_PARAMETERS speciality, group, rating, attendance

class Student :public Human
{
	static const int SPECIALITY_WIDTH = 22;
	static const int GROUP_WIDTH = 8;
	static const int RATING_WIDTH = 5;
	std::string speciality;
	std::string group;
	double rating;
	double attendance;
public:
	const std::string& get_speciality()const { return speciality; }
	const std::string& get_group()const { return group; }
	double get_rating()const { return rating; }
	double get_attendance()const { return attendance; }

	void set_speciality(const std::string& speciality) { this->speciality = speciality; }
	void set_group(const std::string& group) { this->group = group; }
	void set_rating(double rating) { this->rating = rating; }
	void set_attendance(double attendance) { this->attendance = attendance; }

	Student(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS)
		:Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		set_attendance(attendance);
		cout << "SConstructor:\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t" << this << endl;
	}

	std::ostream& info(std::ostream& os)const override
	{
		Human::info(os);
		os.width(SPECIALITY_WIDTH);
		os << speciality;
		os.width(GROUP_WIDTH);
		os << group;
		os.width(RATING_WIDTH);
		os << rating;
		os.width(RATING_WIDTH);
		os << attendance;
		return os;
	}

	void save(std::ostream& os) const override
	{
		os << "Student;" << get_last_name() << ";" << get_first_name() << ";" << get_age()
			<< ";" << speciality << ";" << group << ";" << rating << ";" << attendance << "\n";
	}
};

#define TEACHER_TAKE_PARAMETERS const std::string& speciality, int experience
#define TEACHER_GIVE_PARAMETERS speciality, experience

class Teacher :public Human
{
	static const int SPECIALITY_WIDTH = 22;
	static const int EXPERIENCE_WIDTH = 3;
	std::string speciality;
	int experience;
public:
	const std::string& get_speciality()const { return speciality; }
	int get_experience()const { return experience; }

	void set_speciality(const std::string& speciality) { this->speciality = speciality; }
	void set_experience(int experience) { this->experience = experience; }

	Teacher(HUMAN_TAKE_PARAMETERS, TEACHER_TAKE_PARAMETERS)
		:Human(HUMAN_GIVE_PARAMETERS)
	{
		set_speciality(speciality);
		set_experience(experience);
		cout << "TConstructor:\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	std::ostream& info(std::ostream& os)const override
	{
		Human::info(os);
		os.width(SPECIALITY_WIDTH);
		os << speciality;
		os.width(EXPERIENCE_WIDTH);
		os << experience;
		return os;
	}

	void save(std::ostream& os) const override
	{
		os << "Teacher;" << get_last_name() << ";" << get_first_name() << ";" << get_age()
			<< ";" << speciality << ";" << experience << "\n";
	}
};

class Graduate :public Student
{
	std::string subject;
public:
	Graduate(HUMAN_TAKE_PARAMETERS, STUDENT_TAKE_PARAMETERS, const std::string& subject)
		:Student(HUMAN_GIVE_PARAMETERS, STUDENT_GIVE_PARAMETERS)
	{
		this->subject = subject;
		cout << "GConstructor:\t" << this << endl;
	}
	~Graduate()
	{
		cout << "GDestructor:\t" << this << endl;
	}

	std::ostream& info(std::ostream& os)const override
	{
		Student::info(os) << " ";
		return os << subject;
	}

	void save(std::ostream& os) const override
	{
		os << "Graduate;" << get_last_name() << ";" << get_first_name() << ";" << get_age()
			<< ";" << get_speciality() << ";" << get_group() << ";" << get_rating() << ";" << get_attendance()
			<< ";" << subject << "\n";
	}
};

void save_group(const std::vector<Human*>& group, const std::string& filename)
{
	std::ofstream fout(filename);
	for (auto* person : group)
	{
		person->save(fout);
	}
}

std::vector<Human*> load_group(const std::string& filename)
{
	std::vector<Human*> group;
	std::ifstream fin(filename);
	std::string line;

	while (std::getline(fin, line))
	{
		std::stringstream ss(line);
		std::string type;
		std::getline(ss, type, ';');

		if (type == "Human")
		{
			std::string last, first;
			int age;
			std::getline(ss, last, ';');
			std::getline(ss, first, ';');
			ss >> age;
			group.push_back(new Human(last, first, age));
		}
		else if (type == "Student")
		{
			std::string last, first, spec, group_name;
			int age;
			double rating, attendance;
			std::getline(ss, last, ';');
			std::getline(ss, first, ';');
			ss >> age; ss.ignore();
			std::getline(ss, spec, ';');
			std::getline(ss, group_name, ';');
			ss >> rating; ss.ignore();
			ss >> attendance;
			group.push_back(new Student(last, first, age, spec, group_name, rating, attendance));
		}
		else if (type == "Teacher")
		{
			std::string last, first, spec;
			int age, exp;
			std::getline(ss, last, ';');
			std::getline(ss, first, ';');
			ss >> age; ss.ignore();
			std::getline(ss, spec, ';');
			ss >> exp;
			group.push_back(new Teacher(last, first, age, spec, exp));
		}
		else if (type == "Graduate")
		{
			std::string last, first, spec, group_name, subj;
			int age;
			double rating, attendance;
			std::getline(ss, last, ';');
			std::getline(ss, first, ';');
			ss >> age; ss.ignore();
			std::getline(ss, spec, ';');
			std::getline(ss, group_name, ';');
			ss >> rating; ss.ignore();
			ss >> attendance; ss.ignore();
			std::getline(ss, subj);
			group.push_back(new Graduate(last, first, age, spec, group_name, rating, attendance, subj));
		}
	}
	return group;
}

int main()
{
	setlocale(LC_ALL, "");

	std::vector<Human*> group =
	{
		new Human("Montana", "Antonio", 25),
		new Student("Pinkman", "Jessie", 22, "Chemistry", "WW_220", 95, 99),
		new Teacher("White", "Walter", 50, "Chemistry", 25),
		new Graduate("Schreder", "Hank", 40, "Criminalistic", "WW_220", 40, 60, "How to catch Heisenberg"),
		new Student("Vercetty", "Tommy", 30, "Theft", "Vice", 98, 99),
		new Teacher("Diaz", "Ricardo", 50, "Weapons distribution", 20),
		new Graduate("Targarian", "Daineris", 22, "Flight", "GoT", 91, 92, "How to make smoke"),
		new Teacher("Schwartzneger", "Arnold", 85, "Heavy Metal", 60)
	};

	cout << "Исходная группа:\n";
	for (auto* person : group)
	{
		cout << *person << endl << delimiter << endl;
	}

	save_group(group, "group.txt");

	for (auto* person : group) delete person;
	group.clear();

	cout << "\nГруппа загружена из файла:\n";
	group = load_group("group.txt");
	for (auto* person : group)
	{
		cout << *person << endl << delimiter << endl;
	}

	for (auto* person : group) delete person;
}
