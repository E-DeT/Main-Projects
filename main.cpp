#include <SFML/Graphics.hpp>
#include <iostream>
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

    explicit Player(int initX = 0, int initY = 0);
    sf::Text& handleMove();
    void handleMoveAmount();

protected:

    int turnAmount = 5;
    float moveAmt = 0, angle = 0;
    float posX, posY;
    float changeX = 0, changeY = 0;

    unsigned int rof = 8224; ///Symbol for the player

    sf::Text text;
    sf::Font font;
};

Player::Player(int initX, int initY):
    posX(initX), posY(initY)
{
    font.loadFromFile("mainfont.ttf");
    text.setString(rof);
    text.setPosition(posX, posY);
    text.setFont(font);
    text.setCharacterSize(50.0);
}

void mainGame()
{
    sf::RenderWindow winmain (sf::VideoMode(500,500),"Main");
    sf::Event event;

    Player player(250, 250);

    //The game handles a second
    //player perfectly fine, apparently

    //Player playerTwo (200, 200);

    while(winmain.isOpen())
    {
        winmain.clear(sf::Color::Black);

        winmain.draw(player.handleMove());
        player.handleMoveAmount();

        //winmain.draw(playerTwo.handleMove());
        //playerTwo.handleMoveAmount();

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

sf::Text& Player::handleMove()
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

    changeX > 5 ? changeX = 5 : changeX = changeX;
    changeY > 5 ? changeY = 5 : changeY = changeY;

    posX += changeX, posY += changeY;

    std::cout << posX << " " << posY << std::endl;

    text.setPosition(posX, posY);
    text.setRotation(angle);

    return text;
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
        angle - turnAmount < 0 ? angle = 359.5 : angle -= turnAmount;
        std::cout << angle << std::endl;
    }
}
