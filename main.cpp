#include <SFML/Graphics.hpp>
#include <iostream>


using namespace sf;
using namespace std;


class playerClass
{
    //setting referencetyp
    public:
        playerClass(){
            cout << "klfjg" << endl;

        }

};



int main()
{
    const int windowWidth = 400; // Define window width
    const int windowHeight = 300; // Define window height

    RenderWindow window(VideoMode(windowWidth, windowHeight), "plattformer"); // Change window title
    
    bool up, down, left, right = false;

    playerClass playerObjcet;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}
