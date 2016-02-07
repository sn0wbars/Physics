#pragma once
#include "Object.h"


Object::Object(double user_ro = 1, Polygon* user_polygon = NULL)
{
	cout << "Creating Object\n";
	if (user_polygon == NULL) 
	{
		polygon = new Polygon;
	}
	else polygon = user_polygon;
	ro = user_ro;
	m = -1;
	calculate_m();
}

Object::~Object()
{
	cout << "Deleting Object\n";
	delete polygon;
}

double Object::getM() { return m; }

Polygon* Object::getPolygonP() { return polygon; }

sf::ConvexShape* Object::getShape() { return polygon->getShape(); }

int Object::calculate_m()
{
	cout << "Calculating m\n";
	if (m > 0) return 1;
	polygon->calculate_S();
	m = ro * polygon->getS();
	return 0;
}

int Object::setFromFile(const char* filename)
{
	assert(filename);

	int temp;
	Point temp_point;

	std::ifstream fin(filename);
	fin >> ro;
	fin >> temp;
	polygon->setCount(temp);
	PRINT(temp);
	for (int i = 0; i < temp; ++i) 
	{

		fin >> temp_point.x;
		fin >> temp_point.y;
		// PRINT(polygon->getCount());
		// PRINT(polygon->getPoint(i));
		polygon->setPoint(temp_point, i);
	}
	fin.close();
	cout << "Errors sum: " << (polygon->calculate_S() + polygon->calculate_MC() + polygon->calculate_shape() + calculate_m()) << endl;
	return 0;
}

bool check_collision(Object* object1, Object* object2) { return check_collision(object1->polygon, object2->polygon); }