#pragma once

#include <stdio.h>
#include "Geometry.h"


class Object
	{
	private:
		
		double ro; // Density
		double m; // Mass
		Polygon* polygon;
		
	public:
		Object(double user_ro, Polygon* user_polygon);
		~Object();

		// Getters:
		double getM();
		Polygon* getPolygonP();
		sf::ConvexShape* getShape();;

		// Other:
		int calculate_m();
		int setFromFile(const char* filename);
		friend bool check_collision(Object* object1, Object* object2);
		int move();
	};

#include "Object.cpp"
