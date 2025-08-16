#include<iostream>
using namespace std;

enum Color
{
	Red = 0x000000FF,
	Green = 0x0000FF00,
	Blue = 0x00FF0000,
	Yellow = 0x0000FFFF,
	Purple = 0x00FF00FF
};

class Shape
{
	Color color;
public:
	void set_color(Color color) {
		this->color = color;
	}
	Color get_color()const {
		return color;
	}
	Shape(Color color) : color(color) {}
	virtual double get_area() const = 0;
	virtual double get_perimeter() const = 0;
	virtual void draw() const = 0;
	virtual void info() const {
		cout << typeid(*this).name() << endl;
		cout << "Area:" << get_area() << endl;
		cout << "Perimeter" << get_perimeter() << endl;
	}
};
class Square : public Shape {
	double side;
public:
	Square(double side, Color color) : side(side), Shape(color) {}
	void set_side(double side) {
		this->side = side;
	}
	double get_side() const {

		return side;
	}
	double get_area()const override {
		return side * side;
	}
	double get_perimeter() const override {
		return side * 4;
	}
	void draw() const override {
		for (int i = 0; i < side; ++i) {
			for (int j = 0; j < side; ++j) {
				cout << "* ";
			}
			cout << endl;
		}
	}
	void info()const override {
		Shape::info();
		cout << "Side: " << get_side() << endl;
	}
};

void main() {
	Square square(5, Red);
	square.info();
	square.draw();
}