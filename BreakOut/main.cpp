#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <windows.h>
#include "functions.h"
using namespace sf;


int main()
{
    //creating function object to call functions
    functions myFunctions;
    //setting up screen and fps
    RenderWindow app(VideoMode(519, 600), "BreakOut by Faisl Qurishi");
    app.setFramerateLimit(60);


    // creating blocks, vector
    std::vector<RectangleShape> block(100);

    //creating paddle
    RectangleShape paddle(Vector2f(48, 7));
    paddle.setOutlineThickness(2);
    paddle.setOutlineColor(Color(255,127,39,255));
    paddle.setFillColor(Color(255,242,0,255));

    //creating background
    RectangleShape background(Vector2f(505,600));
    background.setOutlineThickness(7);
    background.setOutlineColor(Color(127,127,127,255));
    background.setFillColor(Color(0,0,0,255));
    background.setPosition(7,57);

    //creating ball
    CircleShape ball(6);
    ball.setFillColor(sf::Color(255,255,255,255));

    //adding sounds
    SoundBuffer b1,b2,b3,b4,b5;
    Sound s1,s2,s3,s4, bg;
    b1 = myFunctions.LoadBufferFromResource("SOUND1");
    b2 = myFunctions.LoadBufferFromResource("SOUND2");
    b3 = myFunctions.LoadBufferFromResource("SOUND3");
    b4 = myFunctions.LoadBufferFromResource("SOUND4");
    b5 = myFunctions.LoadBufferFromResource("SOUND5");
    s1.setBuffer(b1);
    s2.setBuffer(b2);
    s3.setBuffer(b3);
    s4.setBuffer(b4);
    bg.setBuffer(b5);


    //setting up block setup and colors
    int n=0, blockX=8, blockY=59, lives =3, points =0;
    for (int i=0;i<=7;i++)
    for (int j=0;j<=11;j++)
      {
          block[n].setSize(Vector2f(40, 18));
         if (n >= 0){
                block[n].setFillColor(Color(192,192,192,255));
                block[n].setOutlineThickness(2);
                block[n].setOutlineColor(Color(180,180,180,255));
         }
         if (n > 11){
                block[n].setFillColor(Color(255,0,255,255));
                block[n].setOutlineThickness(2);
                block[n].setOutlineColor(Color(243,0,243,255));
         }
         if (n > 23){
                block[n].setFillColor(Color(255,0,0,255));
                block[n].setOutlineThickness(2);
                block[n].setOutlineColor(Color(243,0,0,255));
         }
         if (n > 35){
                block[n].setFillColor(Color(255,69,0,255));
                block[n].setOutlineThickness(2);
                block[n].setOutlineColor(Color(243,57,0,255));
         }
         if (n > 47){
                block[n].setFillColor(Color(255,165,0,255));
                block[n].setOutlineThickness(2);
                block[n].setOutlineColor(Color(243,153,0,255));
         }
         if (n > 59){
                block[n].setFillColor(Color(204,204,0,255));
                block[n].setOutlineThickness(2);
                block[n].setOutlineColor(Color(192,192,0,255));
         }
         if (n > 71){
                block[n].setFillColor(Color(0,235,0,255));
                block[n].setOutlineThickness(2);
                block[n].setOutlineColor(Color(0,223,0,255));
         }
         if (n > 83){
                block[n].setFillColor(Color(0,0,255,255));
                block[n].setOutlineThickness(2);
                block[n].setOutlineColor(Color(0,0,243,255));
         }
         block[n].setPosition((blockX)+ (j*42),(blockY)+(i*22));
         n++;
      }
    //setting up points for paddle and ball. Bool for when game is won.
    //ball movement implemented with dx and dy and dspeeds
    //to be added bools for menu + screen selection
    float dx=4, dy=5;
    float dxSpeed=0, dySpeed=0;
    float ballX=250, ballY=360;
    float paddleX=230;
    bool won = false, title = true;
    //add flash timer for flashing enter in title
    int flash = 0;
    //add flash bool
    bool flashBool = true;

    //adding fonts and text
    Font eightBit;
    eightBit = myFunctions.LoadFontFromResource("FONT1");
    Text score, gameOver, youWin, startMessage, startMenu, enter;
    score.setFont(eightBit);
    gameOver.setFont(eightBit);
    youWin.setFont(eightBit);
    startMessage.setFont(eightBit);
    startMenu.setFont(eightBit);
    enter.setFont(eightBit);
    String getPoints;
    score.setCharacterSize(30);
    score.setFillColor(Color(127,127,127,255));
    getPoints = std::to_string(points) + "\t" + std::to_string(lives);
    score.setString(getPoints);
    gameOver.setCharacterSize(15);
    gameOver.setFillColor(Color::White);
    startMessage.setCharacterSize(15);
    startMessage.setFillColor(Color::White);
    startMessage.setString("\t\t\tPress Space To Drop\n\narrow keys or a and w to move pad");
    youWin.setCharacterSize(30);
    youWin.setFillColor(Color::White);
    startMenu.setCharacterSize(30);
    startMenu.setFillColor(Color::White);
    startMenu.setString("\t  BreakOut\n\nBy Faisl Qurishi");
    enter.setCharacterSize(20);
    enter.setString("PRESS\nENTER");
    score.setPosition(330, 10);
    startMessage.setPosition(18, 260);
    startMenu.setPosition(55, 100);
    enter.setPosition(200,300);
    //play background music
    bg.play();
    bg.setLoop(true);

    //creating the action in the app
    while (app.isOpen())
    {
       Event e;
       while (app.pollEvent(e))
       {
         if (e.type == Event::Closed)
             app.close();
       }

    if(title == false){

    //creating balls speed and physics and collisions with blocks
    ballX-=dx * dxSpeed;
    for (int i=0;i<n;i++){
        if ( FloatRect(ballX+3,ballY+3,6,6).intersects(block[i].getGlobalBounds()) )
        {
            s2.play();
            block[i].setPosition(-100,0);
            dx=-dx;
            points++;
            getPoints = std::to_string(points) + "\t" + std::to_string(lives);
            score.setString(getPoints);
        }
    }

    ballY+=dy * dySpeed;
    for (int i=0;i<n;i++){
        if ( FloatRect(ballX+3,ballY+3,6,6).intersects(block[i].getGlobalBounds()) )
        {
            s2.play();
            block[i].setPosition(-100,0);
            dy=-dy;
            points++;
            getPoints = std::to_string(points) + "\t" + std::to_string(lives);
            score.setString(getPoints);
        }
    }

    //balls boundaries and loss of life
    //if ball goes left or right and hits walls
    if ((ballX<7 && lives !=0) || ballX>500){
        s3.play();
        dx=-dx;
    }
    //if ball hits ceiling
    if (ballY<60){
        s3.play();
        dy=-dy;
    }
    //if ball falls, restart conditions and play sound, update score
    if (ballY > 600){
       s1.play();
        lives--;
        getPoints = std::to_string(points) + "\t" + std::to_string(lives);
        score.setString(getPoints);
        ballY = 300;
        ballX = 250;
        dySpeed = 0;
        dxSpeed = 0;
        //if out of lives, show game over screen
        if(lives == 0)
        {
            for (int i=0;i<n;i++)
            {
                    block[i].setPosition(-100,0);
            }
            ballX = -300;
            paddleX = -150;
            gameOver.setPosition(90, 70);
            gameOver.setString("\t\t\tGame Over\n\n\t\tLOL YOU ARE BAD\n\n\n\n\nPress space to try again");
        }
    }
    //to start ball fall
    if (Keyboard::isKeyPressed(Keyboard::Space) && dySpeed == 0 && won == false){
            dxSpeed = 0;
            dySpeed = 1;
            startMessage.setString("");
        }


    //restart game
    if (Keyboard::isKeyPressed(Keyboard::Space) && lives == 0){
        lives = 3;
        dxSpeed = 0;
        dySpeed = 1;
        ballX = 250;
        ballY = 300;
        paddleX = 230;
        points = 0;
        getPoints = std::to_string(points) + "\t" + std::to_string(lives);
        score.setString(getPoints);
        gameOver.setString("");
        n = 0;
         for (int i=0;i<=7;i++)
         for (int j=0;j<=11;j++)
            {
                    block[n].setPosition((blockX)+ (j*42),(blockY)+(i*22));
                    n++;
            }

    }

    //paddles movement and collision with ball
    if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && lives != 0 && won == false) paddleX = paddleX + 10;
    if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && won == false) paddleX = paddleX - 10;
    if ( FloatRect(ballX,ballY,10,10).intersects(paddle.getGlobalBounds()) )
    {
        s3.play();
        ballY -= 5;
        dy=-(dy);
        dxSpeed=1;
        dySpeed= dySpeed + 0.05;
    }
    //paddles boundaries
    if (paddleX < 5 && lives != 0){
        paddleX = paddleX + 25;
    }
    if (paddleX > 465){
        paddleX = paddleX - 25;
    }
    //game ends if score reaches 96
    if (points == 96){
        won = true;
        if (won == true){
            youWin.setPosition(120, 150);
            youWin.setString("  YOU WON\n\nGREAT JOB");
            dxSpeed = 0;
            dySpeed = 0;
        }
    }

    //setting position for ball and paddle
    ball.setPosition(ballX,ballY);
    paddle.setPosition(paddleX,580);
    }else{
    flash++;
    if(80/flash == 1){
        flashBool = !flashBool;
        flash = 0;
    }
    if(flashBool == true){
        enter.setFillColor(Color::White);
    }
    else{
        enter.setFillColor(Color::Black);
    }
    }

    //creating the application and drawing objects
    app.clear();
    //change scene from title to game
    if (title == true){
        app.draw(startMenu);
        app.draw(enter);
        if(Keyboard::isKeyPressed(Keyboard::Enter)){
            s4.play();
            title = false;
            bg.pause();
        }
    }
    else{
        app.draw(background);
        app.draw(score);
        app.draw(startMessage);
        app.draw(ball);
        app.draw(paddle);
        app.draw(gameOver);
        for (int i=0;i<n;i++){
        app.draw(block[i]);
        }
        app.draw(youWin);
    }

    app.display();
    }

  return 0;
}
