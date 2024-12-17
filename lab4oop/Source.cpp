#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include <vector>
#include <memory>


class Figure 
{
protected:
    int x, y;
public:
    Figure(int x, int y) : x(x), y(y) {}
    virtual void Draw(sf::RenderWindow& window) = 0;
    virtual void MoveRight(sf::RenderWindow& window) = 0;
};

class Circle : public Figure 
{
    int radius;
    sf::CircleShape shape;
public:
    Circle(int x, int y, int r) : Figure(x, y), radius(r), shape(r) 
    {
        shape.setFillColor(sf::Color::Black);
    }
    void Draw(sf::RenderWindow& window) override 
    {
        shape.setPosition(x - radius, y - radius);
        window.draw(shape);
    }
    void MoveRight(sf::RenderWindow& window) override 
    {
        x += 5;
        Draw(window);
    }
};
class Square : public Figure 
{
    int sideLength;
    sf::RectangleShape shape;
public:
    Square(int x, int y, int side) : Figure(x, y), sideLength(side), shape(sf::Vector2f(side, side)) 
    {
        shape.setFillColor(sf::Color::Black);
    }
    void Draw(sf::RenderWindow& window) override 
    {
        shape.setPosition(x - sideLength / 2, y - sideLength / 2);
        window.draw(shape);
    }
    void MoveRight(sf::RenderWindow& window) override 
    {
        x += 5;
        Draw(window);
    }
};
class Rhomb : public Figure 
{
    int horDiagLen, vertDiagLen;
    sf::ConvexShape shape;

public:
    Rhomb(int x, int y, int h, int v) : Figure(x, y), horDiagLen(h), vertDiagLen(v) 
    {
        shape.setPointCount(4);
        shape.setFillColor(sf::Color::Black);
    }
    void Draw(sf::RenderWindow& window) override 
    {
        shape.setPoint(0, sf::Vector2f(x, y - vertDiagLen / 2));
        shape.setPoint(1, sf::Vector2f(x + horDiagLen / 2, y));
        shape.setPoint(2, sf::Vector2f(x, y + vertDiagLen / 2));
        shape.setPoint(3, sf::Vector2f(x - horDiagLen / 2, y));
        window.draw(shape);
    }
    void MoveRight(sf::RenderWindow& window) override 
    {
        x += 5;
        Draw(window);
    }
};
int main() 
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dynamic Figures with Buttons");
    std::vector<std::shared_ptr<Figure>> figures;
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) 
            {
                if (event.key.code == sf::Keyboard::C) 
                {
                    figures.push_back(std::make_shared<Circle>(100, 300, 50));
                }
                else if (event.key.code == sf::Keyboard::S) 
                {
                    figures.push_back(std::make_shared<Square>(100, 300, 100));
                }
                else if (event.key.code == sf::Keyboard::R) 
                {
                    figures.push_back(std::make_shared<Rhomb>(100, 300, 120, 80));
                }
            }
        }
        window.clear(sf::Color::White);
        for (auto& figure : figures) 
        {
            figure->MoveRight(window);
        }
        window.display();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
}
