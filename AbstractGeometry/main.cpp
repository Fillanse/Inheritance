#include<iostream>
#include<Windows.h>
using namespace std;
namespace Geometry
{

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
	class Rectangle : public Shape {
		double height;
		double width;
	public:
		Rectangle(double height, double width, Color color) : height(height), width(width), Shape(color) {}
		double set_height(double height) {
			this->height = height;
		}
		double set_width(double width) {
			this->width = width;
		}
		double get_height() const {
			return height;
		}
		double get_width() const {
			return width;
		}
		double get_area()const override {
			return height * width;
		}
		double get_perimeter() const override {
			return 2 * (height + width);
		}
		void draw() const override {
			HWND hWnd = GetConsoleWindow();
			HDC hDc = GetDC(hWnd);
			HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hDc, hPen);
			SelectObject(hDc, hBrush);

			::Rectangle(hDc, 200, 200, 400, 400);
			
			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hWnd, hDc);
		}
		void info()const override {
			Shape::info();
			cout << "Height: " << get_height() << endl;
			cout << "Width: " << get_width() << endl;
		}
	};
}

void main() {
	Geometry::Square square(5, Geometry::Red);
	square.info();
	square.draw();

	Geometry::Rectangle rectangle(15, 20, Geometry::Red);
	rectangle.info();
	rectangle.draw();

}