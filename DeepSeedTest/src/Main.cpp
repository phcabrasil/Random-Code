#include <iostream>
#include <iomanip>
#include <math.h>
#include <string>
#include <vector>

using namespace std;

class Point {
private:
    double xVal;
    double yVal;

public:
    Point(double x = 0.00, double y = 0.00) : xVal(x), yVal(y) {
        xVal = x;
        yVal = y;
    }

    double x() { return xVal; }
    double y() { return yVal; }

    double distance(Point other) {
        double dx = x() - other.x();
        double dy = y() - other.y();
        return sqrt(dx * dx + dy * dy);
    }
    double slopeWith(Point other) {
        double dx = x() - other.x();
        double dy = y() - other.y();
        return dy / dx;
    }
    bool equals(Point other) {
        double dx = x() - other.x();
        double dy = y() - other.y();
        if (dx == 0 && dy == 0)
            return true;
        else
            return false;
    }
};

class Triangle {
private:
    Point A;
    Point B;
    Point C;
    double sideA;
    double sideB;
    double sideC;

public:
    Triangle(Point a, Point b, Point c) {
        A = a;
        B = b;
        C = c;
        sideA = B.distance(C);
        sideB = C.distance(A);
        sideC = A.distance(B);
    }

    double getSideA() { return sideA; }
    double getSideB() { return sideB; }
    double getSideC() { return sideC; }

    double getAngleA() {
        if (!isTriangle())
            return 0;
        else
            return acos((sideA * sideA - sideB * sideB - sideC * sideC) / (-2 * sideB * sideC)) * 180 / 3.1415;
    }
    double getAngleB() {
        if (!isTriangle())
            return 0;
        else
            return acos((sideB * sideB - sideA * sideA - sideC * sideC) / (-2 * sideA * sideC)) * 180 / 3.1415;
    }
    double getAngleC() {
        if (!isTriangle())
            return 0;
        else
            return acos((sideC * sideC - sideB * sideB - sideA * sideA) / (-2 * sideB * sideA)) * 180 / 3.1415;
    }

    double getArea() {
        if (isColinear() || !isTriangle() || hasCoincidentPoints())
            return 0;
        else
            return abs(A.x() * (B.y() - C.y()) + B.x() * (C.y() - A.y()) + C.x() * (A.y() - B.y()) * (1 / 2));
    }

    bool hasCoincidentPoints() {
        if (A.equals(B) || B.equals(C) || C.equals(A))
            return true;
        else
            return false;
    }
    bool isColinear() {
        if (A.slopeWith(B) == B.slopeWith(C) && A.slopeWith(B) == C.slopeWith(A))
            return true;
        else
            return false;
    }
    bool isTriangle() {
        if (sideA + sideB <= sideC || sideA + sideC <= sideB || sideB + sideC <= sideA)
            return false;
        else if (isColinear() || hasCoincidentPoints())
            return false;
        else
            return true;
    }

    string getTypeByInternalAngle() {
        if (isTriangle()) {
            if (getAngleA() == 90 || getAngleB() == 90 || getAngleC() == 90)
                return "Right Angled";
            else if (getAngleA() < 90 && getAngleB() < 90 && getAngleC() < 90)
                return "Acute";
            else
                return "Obtuse";
        }
        else
            return "None: Not a Triangle";
    }

    string getTypeByLengthSides() {
        if (isTriangle()) {
            if (sideA == sideB && sideB == sideC)
                return "Equilateral";
            else if (sideA != sideB && sideA != sideC && sideB != sideC)
                return "Scalene";
            else
                return "Isosceles";
        }
        else
            return "None: Not a Triangle";
    }
};

int main() {
    string input;
    string::size_type size;

    double xCoords[3];
    double yCoords[3];

    getline(cin, input);

    for (int i = 0; i < 3; i++) {
        xCoords[i] = stod(input, &size);
        input = input.substr(size);
        yCoords[i] = stod(input, &size);
        input = input.substr(size);
    }

    Point A(xCoords[0], yCoords[0]);
    Point B(xCoords[1], yCoords[1]);
    Point C(xCoords[2], yCoords[2]);

    Triangle triangle(A, B, C);

    cout << "\nTriangle Information:\n" << endl;
    cout <<  setprecision(4) << fixed;
    cout << "Length of Side Oppposite to A: " << triangle.getSideA() << endl;
    cout << "Length of Side Oppposite to B: " << triangle.getSideB() << endl;
    cout << "Length of Side Oppposite to C: " << triangle.getSideC() << endl;
    cout << "Type based on Side Lenghts: " << triangle.getTypeByLengthSides() << endl;
    cout << "Angle at Vertice A: " << triangle.getAngleA() << endl;
    cout << "Angle at Vertice B: " << triangle.getAngleB() << endl;
    cout << "Angle at Vertice C: " << triangle.getAngleC() << endl;
    cout << "Type based on Internal Angles: " << triangle.getTypeByInternalAngle() << endl;
    cout << "Area of Triangle: " << triangle.getArea() << endl;
}