#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <math.h>
#define pi 3.14159265358979323846

void mainGame();

int main ()
{
    mainGame();
    return 0;
}

class Player
{
public:

    explicit Player(float initX = 0.0, float initY = 0);

    sf::Sprite& handleMove();
    void handleMoveAmount();

protected:

    int turnAmount = 5;
    float moveAmt = 0, angle = 0;
    float posX, posY;
    float changeX = 0, changeY = 0;

    sf::Sprite sprite;
    sf::Texture texture;
};

Player::Player(float initX, float initY):
    posX(initX), posY(initY)
{
    texture.loadFromFile("ship_block.jpg");
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
    sprite.setRotation(0);
    sprite.setOrigin(19.0, 25.0);
}

void mainGame()
{
    sf::RenderWindow winmain (sf::VideoMode(500,500),"Main");
    sf::Event event;

    Player player(250.0, 250.0);

    //Used to lock window refresh rate

    std::chrono::system_clock::time_point rof = std::chrono::system_clock::now();
    std::chrono::system_clock::time_point ter;

    while(winmain.isOpen())
    {
        ter = std::chrono::system_clock::now();

        //The following if statement locks
        //the window refresh rate to a max of
        //62.5 frames per second (1000/16 = 62.5)

        if((std::chrono::duration_cast<std::chrono::milliseconds>(ter - rof).count()) >= 16)
        {
            rof = std::chrono::system_clock::now();

            winmain.clear(sf::Color::Black);
            winmain.draw(player.handleMove());
            player.handleMoveAmount();

            while(winmain.pollEvent(event))
            {
                switch(event.type)
                {
                case sf::Event::Closed:
                    winmain.close();
                    break;
                default:
                    break;
                }
            }
            winmain.display();
        }
    }

}

sf::Sprite& Player::handleMove()
{
    if(moveAmt)
    {
        float radianAngle;
        radianAngle = 2 * pi * (angle/360);

        changeX += (moveAmt * sin(radianAngle));
        changeY += (-1 * (moveAmt * cos(radianAngle)));

        moveAmt = 0;
    }

    if((posX + changeX) > 450 || (posX + changeX) < 50)
    {
        changeX = 0;
    }
    if((posY + changeY) > 450 || (posY + changeY) < 50)
    {
        changeY = 0;
    }

    //Limits speed, but causes the ship to
    //move akwardly due to the aspect ratio
    //making the ship appear to move faster
    //along one axis at max X,Y speed

    //changeX > 5 ? changeX = 5 : changeX = changeX;
    //changeY > 5 ? changeY = 5 : changeY = changeY;

    posX += changeX, posY += changeY;

    //Debug; send position to console

    //std::cout << posX << " " << posY << std::endl;

    sprite.setPosition(posX, posY);
    sprite.setRotation(angle);

    return sprite;
}

void Player::handleMoveAmount()
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        moveAmt += 0.5;
        std::cout << moveAmt << std::endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        moveAmt -= 0.5;
        std::cout << moveAmt << std::endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        angle + turnAmount >= 360 ? angle = 0 : angle += turnAmount;
        std::cout << angle << std::endl;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        angle - turnAmount < 0 ? angle = 359 : angle -= turnAmount;
        std::cout << angle << std::endl;
    }
}
