#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
const int width = 800;
const int height = 600;



struct windowinfo {
    int width;
    int height;
};

struct font {
    std::string filelocation;
    int size;
    int red, green, blue;
};

struct Circle {
    std::string name;
    float firstPosX;
    float firstPosY;
    float initialSpeedX;
    float initialSpeedY;
    int red, green, blue;
    int radius;
};

struct Rectangle {
    std::string name;
    float firstPosX;
    float firstPosY;
    float initialSpeedX;
    float initialSpeedY;
    int red, green, blue;
    int Width, Height;
};

std::vector<font>fonts;
std::vector<Circle>circles;
std::vector<Rectangle>rectangles;

void fileread(std::string& filename) {
    std::ifstream file(filename);
    std::string temp;
    windowinfo window;
    font tempFont;
    Circle tempCircle;
    Rectangle tempRectangle;
    while (file >> temp)
    {
        if (temp == "Window")
        {
            file >> window.width;
            file >> window.height;
        }
        else if (temp == "Font") {
            file >> tempFont.filelocation;
            file >> tempFont.size;
            file >> tempFont.red;
            file >> tempFont.blue;
            file >> tempFont.green;
            fonts.push_back(tempFont);
        }
        else if (temp == "Circle")
        {   
            file >> tempCircle.name;
            file >> tempCircle.firstPosX;
            file >> tempCircle.firstPosY;
            file >> tempCircle.initialSpeedX;
            file >> tempCircle.initialSpeedY;
            file >> tempCircle.red >> tempCircle.green >> tempCircle.blue ;

            circles.push_back(tempCircle);
        } else if (temp == "Rectangle") {
            file >> tempRectangle.name >> tempRectangle.firstPosX >> tempRectangle.firstPosY >> tempRectangle.initialSpeedX >> tempRectangle.initialSpeedY >> tempRectangle.red >> tempRectangle.green >> tempRectangle.blue >> tempRectangle.Width >> tempRectangle.Height;

            rectangles.push_back(tempRectangle);
        }
    }
}


int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(width, height), "My window is that time i got reincarneated as a slime");
    

    sf::CircleShape shape(50.f);
    sf::Texture text;
    sf::Font font;


    #ifdef __linux
    text.loadFromFile("bin/OIP.jpg");
    font.loadFromFile("bin/fonts/PoppkornRegular-MzKY.ttf");
    #endif

    #ifdef __WIN64__
    text.loadFromFile("OIP.jpg");
    if (!font.loadFromFile("fonts/PoppkornRegular-MzKY.ttf")) {
        std::cerr << "font cannot load\n";
    }
    #endif

    sf::Text sar("Sample Text", font, 50);
    sar.setPosition(0, height - (float)sar.getCharacterSize());
    //sar.setPosition(0, 0);
    
    //shape.setFillColor(sf::Color(150, 50, 250));
    text.setSmooth(true);
    shape.setTexture(&text);
    

    // set a 10-pixel wide orange outline
    /*shape.setOutlineThickness(10.f);
    shape.setOutlineColor(sf::Color(250, 150, 100));*/
    shape.setPosition(sf::Vector2f(400, 200));
    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                std::cout << "Key pressed with code: " << event.key.code << "\n";

                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        // clear the window with black color
        window.clear(sf::Color::Blue);
        window.draw(shape);
        window.draw(sar);
        // draw everything here...
        //sf::Time elapsed2 = clock.getElapsedTime();/*
        //std::cout << elapsed2.asSeconds() << std::endl;*/

        // window.draw(...);

        // end the current frame
        
        window.display();
    }

    return 0;
}
