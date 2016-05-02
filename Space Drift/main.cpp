#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#define pi 3.14159265358979323846

void mainGame();
class Ship_Head;

int main ()
{
    mainGame();
    return 0;
}

class Ship_Block
{
public:
    explicit Ship_Block(int x, int y);
    void setCOMDist(Ship_Head& ship);
    void movePiece(float x, float y, float rotation);
    unsigned int COM_Dist;
    float posX, posY;
//protected:
    sf::Sprite sprite;
    sf::Texture texture;
};

void Ship_Block::movePiece(float x, float y, float rotation)
{
    sprite.setPosition(posX += x, posY += y);
    sprite.setRotation(rotation);
}

Ship_Block::Ship_Block(int x, int y):
    posX(x), posY(y)
{
    texture.loadFromFile("ship_block.jpg"); //50x38
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
    sprite.setRotation(0);
    sprite.setOrigin(19.0, 25.0);
}

class Ship_Head
{
public:
    explicit Ship_Head(int x, int y);
    void draw_Ship(sf::RenderWindow& window);
    void handleMoveAmount();
    void handleMove ();

    float COMX, COMY;
    Ship_Block* shipParts[9];

    int turnAmount = 5, shipSize;
    float moveAmt = 0, angle = 0;
    float changeX = 0, changeY = 0;

};

void Ship_Head::draw_Ship(sf::RenderWindow& window)
{
    for(int i = 0; i < shipSize; i++)
    {
        window.draw((*shipParts[i]).sprite);
    }
}

Ship_Head::Ship_Head(int initX, int initY)
{
    shipSize = 9;
    shipParts[0] = new Ship_Block(initX, initY);
    shipParts[1] = new Ship_Block(initX, initY + 50);
    shipParts[2] = new Ship_Block(initX, initY + 100);
    shipParts[3] = new Ship_Block(initX, initY - 50);
    shipParts[4] = new Ship_Block(initX, initY - 100);
    shipParts[5] = new Ship_Block(initX + 38, initY - 100);
    shipParts[6] = new Ship_Block(initX - 38, initY - 100);
    shipParts[7] = new Ship_Block(initX + 38, initY + 100);
    shipParts[8] = new Ship_Block(initX - 38, initY + 100);
    for(int i = 0; i < shipSize; i++)
    {
        COMX += (*shipParts[i]).posX;
        COMY += (*shipParts[i]).posY;
    }
    COMX = (COMX / shipSize), COMY = (COMY / shipSize);
    for(int i = 0; i < shipSize; i++)
    {
        (*shipParts[i]).setCOMDist(*this);
    }
}

void Ship_Head::handleMove()
{
    if(moveAmt)
    {
        float radianAngle;
        radianAngle = 2 * pi * (angle/360);

        changeX += (moveAmt * sin(radianAngle));
        changeY += (-1 * (moveAmt * cos(radianAngle)));

        moveAmt = 0;
    }

    if((COMX + changeX) > 1450 || (COMX + changeX) < 50)
    {
        changeX = 0;
    }
    if((COMY + changeY) > 750 || (COMY + changeY) < 50)
    {
        changeY = 0;
    }

    COMX += changeX, COMY += changeY;
    std::cout << COMX << " " << COMY << std::endl;
    for(int i = 0; i < shipSize; i++)
    {
        (*shipParts[i]).movePiece(changeX, changeY, angle);
    }
}

void Ship_Head::handleMoveAmount ()
{
    sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ? moveAmt += 0.5 :
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ?  moveAmt -= 0.5 : moveAmt;

    sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ? (angle + turnAmount >= 360 ? angle = 0 : angle += turnAmount) :
        sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ? (angle - turnAmount < 0 ? angle = 359 : angle -= turnAmount) : turnAmount;
}
void Ship_Block::setCOMDist(Ship_Head& ship)
{
    //Distance formula
    float x, y, temp;
    x = posX - ship.COMX;
    x *= x;
    y = posY - ship.COMY;
    y *= y;
    temp = x + y;
    COM_Dist = sqrt(temp);
}

void mainGame()
{
    sf::RenderWindow winmain (sf::VideoMode(1500,800),"Main");
    sf::Event event;

    //Player player(750, 400);
    Ship_Head player(750, 400);

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
            player.handleMove();
            player.handleMoveAmount();
            player.draw_Ship(winmain);

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
