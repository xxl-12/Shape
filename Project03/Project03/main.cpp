#include <iostream>
#include "math.h"
#include <vector>
using namespace std;
//����������Shape
class Shape
{
public:
	virtual double area() const = 0; //������麯��
	virtual double perimeter() const = 0; //�ܳ����麯��
	virtual string type() const = 0; //��״���麯��
	virtual void add(Shape* p) = 0;  //�����״
	virtual void remove(Shape* p) = 0;  //ɾ����״
};

//����Round��
class Round :public Shape
{
public:
	Round(double r) :m_radius(r) {}                                     
	virtual double area() const 
	{
		return 3.1415926 * m_radius * m_radius;
	}
	virtual double perimeter() const 
	{ 
		return 3.1415926 * m_radius * 2;
	}
	virtual string type() const 
	{
		return "Round"; 
	}
	virtual void add(Shape* p)
	{
		cout << "Round cannot add" << endl; 
	}
	virtual void remove(Shape* p)
	{
		cout << "Round cannot remove" << endl;
	}
protected:
	double m_radius;                                                 //�뾶
};

//����Square��
class Square :public Shape
{
public:
	Square(double s) :m_side(s) {}                                     
	virtual double area() const 
	{ 
		return m_side * m_side; 
	}
	virtual double perimeter() const 
	{ 
		return 4 * m_side;
	}
	virtual string type() const 
	{
		return "Square";
	}
	virtual void add(Shape* p)
	{
		cout << "Square cannot add" << endl;
	}
	virtual void remove(Shape* p)
	{
		cout << "Square cannot remove" << endl;
	}
protected:
	double m_side;                                                 //�߳�
};

//����Rectangle��
class Rectangle :public Shape
{
public:
	Rectangle(double w, double h) :m_width(w), m_height(h) {}             
	virtual double area() const 
	{
		return m_width * m_height;
	}
	virtual double perimeter() const 
	{
		return m_width * 2 + m_height * 2;
	}
	virtual string type() const 
	{
		return "Rectangle";
	}
	virtual void add(Shape* p)
	{
		cout << "Rectangle cannot add" << endl;
	}
	virtual void remove(Shape* p)
	{
		cout << "Rectangle cannot remove" << endl;
	}
protected:
	double m_width, m_height;                                           //�����
};

//����Triangle��
class Triangle :public Shape
{
public:
	Triangle(double f, double s, double t)
		:m_fristSide(0), m_secondSide(0), m_thirdSide(0)
	{
		try {
			if (f + s > t&& f + t > s&& s + t > f)				//�Ƿ��ܹ���������
			{
				this->m_fristSide = f;
				this->m_secondSide = s;
				this->m_thirdSide = t;
			}
			else
			{
				throw "����Triangleʧ�ܣ����߳������������ι�ϵ";	//�׳��쳣
			}
		}
		catch (const char* msg) {
			cerr << msg << endl;					//�쳣����
		}

	}
	virtual double area() const
	{
		double p = (m_fristSide + m_secondSide + m_thirdSide)/2;
		return sqrt(p * (p - m_fristSide) * (p - m_secondSide) * (p - m_thirdSide));
	}     
	virtual double perimeter() const 
	{
		return m_fristSide + m_secondSide + m_thirdSide;
	}
	virtual string type() const
	{
		return "Triangle";
	};  
	virtual void add(Shape* p) 
	{
		cout << "Triangle cannot add" << endl;
	}
	virtual void remove(Shape* p)
	{
		cout << "Triangle cannot remove" << endl;
	}
protected:
	double m_fristSide,m_secondSide,m_thirdSide;                                            //����
};
//���� Trapezoid(����)��
class Trapezoid :public Shape
{
public:
	Trapezoid(double t, double b, double l, double r) :m_top(t), m_bottom(b), m_left(l), m_right(r) {} 

	virtual double area() const 
	{
		double height = sqrt(m_left * m_left - ((m_top * m_top + m_bottom * m_bottom + m_left * m_left - m_right * m_right - 2 * m_top * m_bottom) / (2 * (m_bottom - m_top))));
		return 0.5 * (m_top + m_bottom) * height;
	}
	virtual double perimeter() const 
	{
		return m_top + m_bottom + m_left + m_right;
	}

	virtual string type() const 
	{
		return "Trapezoid";
	}
	virtual void add(Shape* p)
	{
		cout << "Trapezoid cannot add" << endl;
	}
	virtual void remove(Shape* p)
	{
		cout << "Trapezoid cannot remove" << endl;
	}
protected:
	double m_top, m_bottom, m_left, m_right;  //�ϵס��µס� ��߳� ���ұ߳�
};

class Compoundshape : public Shape
{
private:
	// ʹ������ָ�벻���Լ��ͷ�new���ڴ�
	vector<shared_ptr<Shape>> m_vec;
public:
	Compoundshape() {};
	virtual ~Compoundshape()
	{
		if (!m_vec.empty())
			m_vec.clear(); 
	}
	virtual void add(Shape* p)
	{
		// ʹ��find_if��lambda���ʽ��������ͬ��Shape
		auto it = find_if(m_vec.begin(), m_vec.end(), [p](shared_ptr<Shape> ptr) {return p == ptr.get(); });
		if (it == m_vec.end())
			m_vec.push_back(shared_ptr<Shape>(p));
	}
	virtual void remove(Shape* p)
	{
		// ʹ��find_if��lambda���ʽ��������ͬ��Shape
		auto it = find_if(m_vec.begin(), m_vec.end(), [p](shared_ptr<Shape> ptr) {return p == ptr.get(); });
		if (it == m_vec.end()) 
			return;
		m_vec.erase(it);
	}
	virtual double area() const
	{ 
		double areaSum = 0;
		for (auto it = m_vec.cbegin(); it != m_vec.cend(); it++)
		{
			areaSum +=(*it)->area();
		}
		return areaSum;
	}   
	virtual double perimeter() const
	{
		double perimeterSum = 0;
		for (auto it = m_vec.cbegin(); it != m_vec.cend(); it++)
		{
			perimeterSum += (*it)->perimeter();
		}
		return perimeterSum;
	}
	virtual string type() const { return "Compoundshape"; }; 
};

void showShape(const Shape* shape)
{
	cout << "���ͣ�" << shape->type() << endl;
	cout << "�����" << shape->area() << endl;
	cout << "�ܳ���" << shape->perimeter() << endl;
}
int main()
{
	Shape* shape = nullptr;							//ָ�򵥸���״
	Shape* compoundShape1 = new Compoundshape();		//ָ�򸴺���״1
	Shape* compoundShape2 = new Compoundshape();		//ָ�򸴺���״2

	cout << "compoundShape1" << endl;

	shape = new Square(4.15);							
	showShape(shape);
	compoundShape1->add(shape);						//��Square��ӵ�compoundShape1
	showShape(compoundShape1);

	shape = new Round(12.25);						//��Round��ӵ�compoundShape1
	showShape(shape);
	compoundShape1->add(shape);
	showShape(compoundShape1);

	shape = new Rectangle(3.24, 2.65);				//��Rectangle��ӵ�compoundShape1
	showShape(shape);
	compoundShape1->add(shape);
	showShape(compoundShape1);

	cout << "compoundShape2" << endl;

	shape = new Triangle(2.12, 5.4, 4.2);			//��Triangle��ӵ�compoundShape2
	showShape(shape);
	compoundShape2->add(shape);
	showShape(compoundShape2);

	shape = new Triangle(2.12, 54, 4.2);	//���������������߹�ϵ�׳��쳣����
	showShape(shape);

	shape = new Trapezoid(1,2,3,3);					//��Trapezoid��ӵ�compoundShape2
	showShape(shape);
	compoundShape2->add(shape);
	showShape(compoundShape2);

	compoundShape2->remove(shape);					//��Trapezoid��compoundShape2�Ƴ�
	showShape(compoundShape2);

	compoundShape2->add(compoundShape1);			//��compoundShape1��ӵ�compoundShape2
	showShape(compoundShape2);

	compoundShape2->remove(compoundShape1);					//��compoundShape1��compoundShape2�Ƴ�
	showShape(compoundShape2);
}