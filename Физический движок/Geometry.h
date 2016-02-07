#pragma once

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::vector;
#define $ cout << "\nNOTE:\t" << __FILE__ << " / " << __func__ << " / " << __LINE__ << endl << endl;

//========================Number======================
union Number
{
	int int_value;
	double double_value;
};

//========================Point=======================
class Point
{
public:
	double x, y;
	Point(double x1, double y1);
	~Point();
	friend Point nan_point();
	bool isNan();
	friend bool operator==(const Point& point1, const Point& point2);
	friend ostream& operator<<(ostream& os, const Point& pnt);
};

//=====================PointsGroup====================
class PointsGroup
{
protected:
	vector<Point> point;
	int count;
public:
	PointsGroup(int n);
	~PointsGroup();
	
	// Getters:
	int getCount();
	Point getPoint(int idx);

	// Setters:
	void setCount(int n);
	void setPoint(Point pnt, int idx);
	
	// Other:
	void addPoint(Point pnt);
};

//=======================Vector=======================
typedef Point RVector;

//=====================LineSegment====================
class LineSegment
{
public:
	Point A, B;
	LineSegment(Point point1, Point point2);
	~LineSegment();
	friend ostream& operator<<(ostream& os, const LineSegment& sgmt);
	bool point_inside_square(const Point* point);
	friend Point crossing(LineSegment* segment1,LineSegment* segment2);
	friend bool check_collision1(LineSegment* segment1, LineSegment* segment2);
	friend bool check_collision(LineSegment* segment1, LineSegment* segment2);
};

//=======================Polygon======================
class Polygon : public PointsGroup
{
private:
	double S;
	Point MC;
	sf::ConvexShape shape;
public:
	//TODO: Random polygon generator
	Polygon(int n);
	~Polygon();

	// Getters:
	double getS();
	Point getMC();
	LineSegment getEdge(int idx);
	sf::ConvexShape* getShape();
	
	// Setters:
	int setFromFile(const char* filename);
	
	// Other:
	int calculate_S();
	int calculate_MC();
	int calculate_shape();
	void print();
	friend bool check_collision(Polygon* polygon1, Polygon* polygon2);
	friend PointsGroup* findCrossPoints(Polygon* polygon1, Polygon* polygon2);
};

#include "Geometry.cpp"
