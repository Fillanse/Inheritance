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
#define SHAPE_TAKE_PARAMETERS int start_x, int start_y, int line_width, Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color
	class Shape
	{
		static const int  MIN_START_X = 100;
		static const int  MIN_START_Y = 100;
		static const int  MAX_START_X = 800;
		static const int  MAX_START_Y = 600;
		static const int  MIN_LINE_WIDTH = 1;
		static const int  MAX_LINE_WIDTH = 32;
		static const int  MIN_SIZE = 32;
		static const int  MAX_SIZE = 800;

		Color color;
		int start_x;
		int start_y;
		int line_width;
	public:
		Shape(SHAPE_TAKE_PARAMETERS) : start_x(start_x), start_y(start_y), line_width(line_width), color(color) {}
		Shape(Color color) : color(color) {}

		void set_start_x(int start_x) {
			this->start_x = start_x < MIN_START_X ? MIN_START_X : start_x > MAX_START_X ? MAX_START_X : start_x;
		}
		void set_start_y(int start_y) {
			this->start_y = start_y < MIN_START_Y ? MIN_START_Y : start_y > MAX_START_Y ? MAX_START_Y : start_y;
		}
		void set_line_width(int line_width) {
			this->line_width = line_width < MIN_LINE_WIDTH ? MIN_LINE_WIDTH : line_width > MAX_LINE_WIDTH ? MAX_LINE_WIDTH : line_width;
		}
		int get_start_x() const {
			return start_x;
		}
		int get_start_y() const {
			return start_y;
		}
		int get_line_width() const {
			return line_width;
		}
		void set_color(Color color) {
			this->color = color;
		}
		Color get_color()const {
			return color;
		}
		virtual double get_area() const = 0;
		virtual double get_perimeter() const = 0;
		virtual void draw() const = 0;
		virtual void info() const {
			cout << typeid(*this).name() << endl;
			cout << "Area:" << get_area() << endl;
			cout << "Perimeter" << get_perimeter() << endl;
		}
	};

	//class Square : public Shape {
	//	double side;
	//public:
	//	Square(double side, Color color) : side(side), Shape(color) {}
	//	Square(double side, SHAPE_TAKE_PARAMETERS) : side(side), Shape(SHAPE_GIVE_PARAMETERS) {}
	//	void set_side(double side) {
	//		this->side = side;
	//	}
	//	double get_side() const {
	//		return side;
	//	}
	//	double get_area()const override {
	//		return side * side;
	//	}
	//	double get_perimeter() const override {
	//		return side * 4;
	//	}
	//	void draw() const override {
	//		for (int i = 0; i < side; ++i) {
	//			for (int j = 0; j < side; ++j) {
	//				cout << "* ";
	//			}
	//			cout << endl;
	//		}
	//	}
	//	void info()const override {
	//		Shape::info();
	//		cout << "Side: " << get_side() << endl;
	//	}
	//};

	class Rectangle : public Shape {
		double height;
		double width;
	public:
		Rectangle(double height, double width, Color color) : height(height), width(width), Shape(color) {}
		Rectangle(double height, double width, SHAPE_TAKE_PARAMETERS) : height(height), width(width), Shape(SHAPE_GIVE_PARAMETERS) {}

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
			HPEN hPen = CreatePen(PS_SOLID, get_line_width(), get_color());
			HBRUSH hBrush = CreateSolidBrush(get_color());
			SelectObject(hDc, hPen);
			SelectObject(hDc, hBrush);

			::Rectangle(hDc, get_start_x(), get_start_y(), get_start_x() + width, get_start_y() + height);

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
	class Square : public Rectangle
	{
	public:
		Square(double side, Color color) : Rectangle(side, side, color) {}
		Square(double side, SHAPE_TAKE_PARAMETERS) : Rectangle(side, side, SHAPE_GIVE_PARAMETERS) {}
		void info()const override {
			Shape::info();
			cout << "Sides: " << get_height() << endl;
		}
	};
	class Triangle : public Shape {
		double sideA;
		double sideB;
		double base;
	public:
		Triangle(double sideA, double sideB, double base, Color color) : sideA(sideA), sideB(sideB), base(base), Shape(color) {}
		Triangle(double sideA, double sideB, double base, SHAPE_TAKE_PARAMETERS) : sideA(sideA), sideB(sideB), base(base), Shape(SHAPE_GIVE_PARAMETERS) {}

		double set_sideA(double sideA) {
			this->sideA = sideA;
		}
		double set_sideB() {
			this->sideB = sideB;
		}
		double set_base() {
			this->base = base;
		}
		double get_sideA()const {
			return sideA;
		}
		double get_sideB()const {
			return sideB;
		}
		double get_base()const {
			return base;
		}
		double get_area() const override {
			double s = get_perimeter() / 2.0;
			return sqrt(s * (s - sideA) * (s - sideB) * (s - base));
		}
		double get_perimeter() const override {
			return sideA + sideB + base;
		}
		void draw() const override {
			HWND hWnd = GetConsoleWindow();
			HDC hDc = GetDC(hWnd);
			HPEN hPen = CreatePen(PS_SOLID, get_line_width(), get_color());
			HBRUSH hBrush = CreateSolidBrush(get_color());

			SelectObject(hDc, hPen);
			SelectObject(hDc, hBrush);

			POINT vertices[3];
			vertices[0].x = get_start_x();
			vertices[0].y = get_start_y();
			vertices[1].x = get_start_x() + base;
			vertices[1].y = get_start_y();

			double angleA = acos((sideB * sideB + base * base - sideA * sideA) / (2 * sideB * base));

			vertices[2].x = get_start_x() + sideB * cos(angleA);
			vertices[2].y = get_start_y() - sideB * sin(angleA);
			::Polygon(hDc, vertices, sizeof(vertices) / sizeof(vertices[0]));


			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hWnd, hDc);
		}
		void info() const override {
			Shape::info();
			cout << "Side A: " << get_sideA() << endl;
			cout << "Side B: " << get_sideB() << endl;
			cout << "Base: " << get_base() << endl;
		}

	};
	class Ellipse : public Shape {
		double radiusX;
		double radiusY;
		const float pi = 2 * acos(0);
	public:
		Ellipse(double radiusX, double radiusY, Color color) : radiusX(radiusX), radiusY(radiusY), Shape(color) {}

		Ellipse(double radiusX, double radiusY, SHAPE_TAKE_PARAMETERS) : radiusX(radiusX), radiusY(radiusY), Shape(SHAPE_GIVE_PARAMETERS) {}

		void set_radiusX(double radiusX) {
			this->radiusX = radiusX;
		}
		void set_radiusY(double radiusY) {
			this->radiusY = radiusY;
		}
		double get_pi() const{
			return pi;
		}
		double get_radiusX() const {
			return radiusX;
		}
		double get_radiusY() const {
			return radiusY;
		}
		double get_area() const override {
			return pi * radiusX * radiusY;
		}
		double get_perimeter() const override {
			double h = pow((radiusX - radiusY), 2) / pow((radiusX + radiusY), 2);
			return pi * (radiusX + radiusY) * (1 + (3 * h) / (10 + sqrt(4 - 3 * h)));
		}
		void draw() const override {
			HWND hWnd = GetConsoleWindow();
			HDC hDc = GetDC(hWnd);
			HPEN hPen = CreatePen(PS_SOLID, get_line_width(), get_color());
			HBRUSH hBrush = CreateSolidBrush(get_color());

			SelectObject(hDc, hPen);
			SelectObject(hDc, hBrush);

			::Ellipse(hDc, get_start_x() - radiusX, get_start_y() - radiusY, get_start_x() + radiusX, get_start_y() + radiusY);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hWnd, hDc);
		}
		void info() const override {
			Shape::info();
			cout << "Radius X: " << get_radiusX() << endl;
			cout << "Radius Y: " << get_radiusY() << endl;
		}
	};

	class Circle : public Ellipse {
	public:
		Circle(double radius, Color color) : Ellipse(radius, radius, color) {}
		Circle(double radius, SHAPE_TAKE_PARAMETERS) : Ellipse(radius, radius, SHAPE_GIVE_PARAMETERS) {}
		double get_perimeter() const override {
			return get_pi() * 2 * get_radiusX();
		}
		void info() const override {
			Shape::info();
			cout << "Radius: " << get_radiusX() << endl;
		}
	};
}

void main() {
	Geometry::Square square(50, 800, 100, 5, Geometry::Color::Red);
	square.info();
	square.draw();

	Geometry::Rectangle rectangle(200, 150, 550, 100, 1, Geometry::Color::Blue);
	rectangle.info();
	rectangle.draw();

	Geometry::Triangle triangle(100, 80, 150, 300, 200, 3, Geometry::Color::Green);
	triangle.info();
	triangle.draw();

	Geometry::Ellipse ellipse(100, 50, 300, 300, 3, Geometry::Color::Yellow);
	ellipse.info();
	ellipse.draw();

	Geometry::Circle circle(50, 550, 300, 3, Geometry::Color::Purple);
	circle.info();
	circle.draw();
}