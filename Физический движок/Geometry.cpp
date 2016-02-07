#pragma once

#include "Geometry.h"
#include <assert.h>
#define PRINT(a) cout << #a": " << a << endl

//========================Point=======================
Point::Point(double x1 = 0, double y1 = 0): x(x1), y(y1)
{
	//printf("Creating Point\n");
}

Point::~Point()
{
	//printf("Deleting Point\n");
}

Point nan_point()
{
	Point result(NAN, NAN);
	//result.x = (double)(result.x / result.x);
	//result.y = (double)(result.y / result.y);
	return result;
}

bool Point::isNan()
{
	return (x != x && y != y);
}

bool operator==(const Point& point1, const Point& point2)
{
	return ((point1.x == point2.x) && (point1.y == point2.y));
}

ostream& operator<<(ostream& os, const Point& pnt)
{
    os << '(' << pnt.x << "; " << pnt.y << ')';
    return os;
}

//=====================PointsGroup====================
PointsGroup::PointsGroup(int n = 0): count(n)
{
	point.reserve(n);
	cout << "POINTSGPOUP created\n";
}

PointsGroup::~PointsGroup()
{
	count = -1;
	cout << "POINTSGPOUP deleted\n";
}

int PointsGroup::getCount()
{
	return count;
}

Point PointsGroup::getPoint(int idx)
{
	return point[idx];
}

void PointsGroup::setCount(int n)
{
	count = n;
	point.reserve(count);
}

void PointsGroup::setPoint(Point pnt, int idx)
{
	// $
	// PRINT(idx);
	// PRINT(point.size());
	// PRINT(point[idx]);
	// $
	point[idx].x = pnt.x;
	point[idx].y = pnt.y;
}

void PointsGroup::addPoint(Point pnt)
{
	++count;
	point.push_back(pnt);
}

//=======================LineSegment======================
LineSegment::LineSegment(Point point1 = Point(-1, -1), Point point2 = Point(-1, -1)): A(point1), B(point2)
{
//	cout << "Creating LineSegment\n";
}

LineSegment::~LineSegment()
{
//	cout << "Deleting LineSegment\n";
}

ostream& operator<<(ostream& os, const LineSegment& sgmt)
{
    os << '(' << sgmt.A << " - " << sgmt.B << ')';
    return os;
}

bool LineSegment::point_inside_square(const Point* point)
{
	assert(point);

	if (((A.x < B.x && point->x >= A.x && point->x <= B.x) ||
		(A.x >= B.x && point->x <= A.x && point->x >= B.x)) &&
		((A.y < B.y && point->y >= A.y && point->y <= B.y) ||
		(A.y >= B.y && point->y <= A.y && point->y >= B.y)))
		return true;
	return false;
}

Point crossing(LineSegment* segment1, LineSegment* segment2)
{
	assert(segment1);
	assert(segment2);

	double dx1, dy1, dx2, dy2;
	dx1 = segment1->B.x - segment1->A.x;
	dy1 = segment1->B.y - segment1->A.y;
	dx2 = segment2->B.x - segment2->A.x;
	dy2 = segment2->B.y - segment2->A.y;
	double denom = dy1*dx2 - dy2*dx1;
	//PRINT(denom);
	if (denom == 0) {
		if (dy2*(segment1->A.x - segment2->A.x) - dx2*(segment1->A.y - segment2->A.y) == 0)
			return nan_point(); //TODO: do something
		else
			return nan_point();
	}
	double x = (segment1->A.x*dy1*dx2 - segment2->A.x*dy2*dx1 - dx1*dx2*(segment1->A.y - segment2->A.y)) / denom;
	double y = dy1 / dx1 * (x - segment1->A.x) + segment1->A.y;
	Point cross_point(x, y);
	//PRINT(cross_point);
	if (!segment1->point_inside_square(&cross_point) || !segment2->point_inside_square(&cross_point))
		return nan_point();
	return cross_point;
}

bool check_collision1(LineSegment* segment1, LineSegment* segment2)
{
	assert(segment1);
	assert(segment2);

	Point cross_point = crossing(segment1, segment2);
	if (cross_point.isNan());
		return false;
	return true;
}

bool check_collision(LineSegment* segment1, LineSegment* segment2)
{
	assert(segment1);
	assert(segment2);

	double dx1, dy1, dx2, dy2;
	double x11 = segment1->A.x; // 0
	double y11 = segment1->A.y; // 0
	double x12 = segment1->B.x; // 100
	double y12 = segment1->B.y; // 100
	double x21 = segment2->A.x; // 100
	double y21 = segment2->A.y; // 0
	double x22 = segment2->B.x; // 0
	double y22 = segment2->B.y; // 100
	dx1 = x12 - x11; // 100
	dy1 = y12 - y11; // 100
	dx2 = x22 - x21; // -100
	dy2 = y22 - y21; // 100
	//cout << dx1 << " " << dy1 << " " << dx2 << " " << dy2 << endl;

	double eq2dot11 = (x11 - x21)*dy2 - (y11 - y21)*dx2;
	double eq2dot12 = (x12 - x21)*dy2 - (y12 - y21)*dx2;
	double eq1dot21 = (x21 - x11)*dy1 - (y21 - y11)*dx1;
	double eq1dot22 = (x22 - x11)*dy1 - (y22 - y11)*dx1;
	//cout << eq2dot11 << " " << eq2dot12 << " " << eq1dot21 << " " << eq1dot22 << endl;

	double sign1 = eq2dot11*eq2dot12;
	double sign2 = eq1dot21*eq1dot22;

	if (sign1 == 0 && sign2 == 0)
		if (segment1->point_inside_square(&segment2->A) || segment1->point_inside_square(&segment2->B))
			return true;
		else
			return false;

	return (sign1 <= 0) && (sign2 <= 0);
}

//=======================Polygon======================
Polygon::Polygon(int n = rand()%10) : PointsGroup(n)
{
	cout << "Creating Polygon\n";
	S = 0;
}

Polygon::~Polygon() { cout << "Deleting Polygon\n"; }

double Polygon::getS() { return S; }

Point Polygon::getMC() { return MC; }

LineSegment Polygon::getEdge(int idx) { return LineSegment(point[idx], point[(idx + 1)%count]); }

sf::ConvexShape* Polygon::getShape() { return &shape; }

int Polygon::setFromFile(const char* filename)
{
	assert(filename);

	FILE* input = fopen(filename, "r");
	fscanf(input, "%d", &count);
	PRINT(count);
	for (int i = 0; i < count; ++i)
		fscanf(input, "%lf,%lf ", &point[i].x, &point[i].y);
	fclose(input);
	int errors = calculate_S() or calculate_MC() or calculate_shape();
	return errors;
}

int Polygon::calculate_S()
{
	//cout << "Calculating S\n";
	if (S > 0) return 1;
	double result = 0;
	for (int i = 0; i < count - 1; ++i)
	{
		result += (point[i].x + point[i+1].x)*(point[i+1].y - point[i].y);
		//printf("%d ", result);
	}
	result = abs(result + (point[count - 1].x + point[0].x)*(point[0].y - point[count - 1].y)) / 2.0;
	S = result;
	PRINT(S);
	return 0;
}

int Polygon::calculate_MC()
{
	cout << "Calculating MC" << endl;
	if (MC.x >= 0 and MC.y >= 0) return 1;
	MC.x = 0;
	MC.y = 0;
	for (int i = 0; i < count; ++i)
	{
		MC.x += point[i].x;
		MC.y += point[i].y;
	}
	PRINT(MC);
	return 0;
}

int Polygon::calculate_shape()
{
	cout << "Calculating shape\n";
	shape.setPointCount(count);
	for(int i = 0; i < count; ++i)
		shape.setPoint(i, sf::Vector2f(point[i].x, point[i].y));
	return 0;
}

void Polygon::print()
{
	PRINT(count);
	for (int i = 0; i < count; ++i)
		PRINT(point[i]);
}


bool check_collision(Polygon* polygon1, Polygon* polygon2)
{
	LineSegment edge1, edge2;
	for (int i = 0; i < polygon1->getCount(); ++i)
		for (int j = 0; j < polygon2->getCount(); ++j) 
		{
			//cout << "REBRO: " <<  i << ',' << j << endl;
			edge1 = polygon1->getEdge(i);
			edge2 = polygon2->getEdge(j);
			// PRINT(edge1);
			// PRINT(edge2);
			if (check_collision(&edge1, &edge2))
				return true;
		}
	return false;
}

PointsGroup* findCrossPoints(Polygon* polygon1, Polygon* polygon2)
{
	PointsGroup* Result = new PointsGroup;
	LineSegment edge1, edge2;
	for (int i = 0; i < polygon1->getCount(); ++i)
		for (int j = 0; j < polygon2->getCount(); ++j) 
		{
			cout << "REBRO: " <<  i << ',' << j << endl;
			edge1 = polygon1->getEdge(i);
			edge2 = polygon2->getEdge(j);
			PRINT(edge1);
			PRINT(edge2);
			if (check_collision(&edge1, &edge2)) // , isnan(crossPoint)
			{
				Result->addPoint(crossing(&edge1, &edge2));
			}
		}
	return Result;
}