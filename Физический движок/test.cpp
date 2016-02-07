#include <SFML/Graphics.hpp>
#include "Geometry.h"
#include "Object.h"
#include <stdio.h>
#include <errno.h>

void test() 
{
    Point a(0,0), b(50,50), c(51,51), d(51, 51);
    LineSegment ls1(a,b), ls2(c,d);
    // printf("Cross: %d\n", (int)check_collision(&ls1, &ls2));
    // printf("Cross: %d\n", (int)check_collision1(&ls1, &ls2));
    const int N = 20000000;
    cout << "Start!" << endl;
    for (int i = 0; i < N; ++i)
        check_collision(&ls1, &ls2);
    cout << "End!\nStart1!" << endl;
    for (int i = 0; i < N; ++i)
        check_collision1(&ls1, &ls2);
    cout << "End1!" << endl;
}

int cycle()
{
	Object o1, o2;
	o1.setFromFile("o1.txt");
    o2.setFromFile("o2.txt");
    // if (check_collision(&o1, &o2))
    //     cout << "Collision!\n";
    // else
    //     cout << "No collision!\n";
    
    //test();
    // PointsGroup* croPoints = findCrossPoints(o1.getPolygonP(), o2.getPolygonP());
    // sf::CircleShape shape(5);
    // shape.setOrigin(5,5);
	sf::RenderWindow window(sf::VideoMode(1000, 600), "Platypus");
    sf::CircleShape shape(100.f);
    o1.getShape()->setFillColor(sf::Color::Green);
    o2.getShape()->setFillColor(sf::Color::Yellow);
    shape.setFillColor(sf::Color::Red);
    //sf::ConvexShape shape;
    while (window.isOpen())
    //for (int i = 0; i < 100; ++i)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }    

        window.clear();
        //o2.getShape()->move(1,1);
		//window.draw(*o1.getShape());
        //window.draw(*o2.getShape());
        shape.move(1.f,1.f);
        window.draw(shape);

        window.display();
    }

	return 0;
}

int main()
{
    cout << "\033[2J\033[1;1H";
    cycle();
    return 0;
}


        // for (int i = 0; i < croPoints->getCount(); ++i)
        // {
        //     shape.setPosition(croPoints->getPoint(i).x, croPoints->getPoint(i).y);
        //     window.draw(shape);
        // }