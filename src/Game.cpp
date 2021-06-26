#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"
#include "Bullet.h"
#include "Alien.h"
#include "Ship.h"
#include "GameState.h"
#include <string>
#include <ctime>
#include <fstream>

Game::Game() {
    score = 0;
    lives = 20;
}

void Game::play() {


    // seeding randomizer
    std::srand(0);

    // reading hs from txt file
    int highScore;
    std::fstream inFile;
    inFile.open("num.txt", std::ios::in);
    inFile >> highScore;
    inFile.close(); // good practice




    GameState gameState;
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");

    // load fonts from "openSansFont.ttf", and others
    sf::Font font;
    if (!font.loadFromFile("openSansFont.ttf")) {
        std::cout<<"Error loading font file"<<std::endl;
    }
    sf::Font gameFont;
    if (!gameFont.loadFromFile("gameType.ttf")) {
        std::cout<<"Error loading font file"<<std::endl;
    }
    sf::Font titleFont;
    if (!titleFont.loadFromFile("title.ttf")) {
        std::cout<<"Error loading font file"<<std::endl;
    }

    std::string scoreText = "Score: "+std::to_string(score);
    sf::Text text;
    text.setFont(gameFont);
    text.setPosition(0, 475);
    text.setCharacterSize(25);
    text.setString(scoreText);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Style::Bold | sf::Text::Style::Underlined);
    text.setOutlineColor(sf::Color::Yellow);
    text.setOutlineThickness(2);

    sf::Text highScoreText = text;
    std::string highScoreString = "High Score: "+std::to_string(highScore);
    highScoreText.setString(highScoreString);
    highScoreText.setPosition(0, 525);

    std::string livesText = "Lives: "+std::to_string(lives);
    sf::Text text2 = text;
    text2.setString(livesText);
    text2.setPosition(0, 440);

    sf::Text openingText = text;
    openingText.setFont(titleFont);
    openingText.setString("Welcome");
    openingText.setPosition(150, 200);
    openingText.setCharacterSize(85);
    openingText.setOutlineThickness(2);

    sf::Text enterNote = text;
    enterNote.setString("Please press enter to begin!");
    enterNote.setPosition(160, 320);
    enterNote.setFont(gameFont);
    enterNote.setCharacterSize(30);
    enterNote.setOutlineColor(sf::Color::Black);
    enterNote.setFillColor(sf::Color::Yellow);
    enterNote.setStyle(sf::Text::Style::Regular);

    sf::Text gameOverText = openingText;
    gameOverText.setFont(gameFont);
    gameOverText.setString("Game Over");
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setOutlineColor(sf::Color::Black);
    gameOverText.setPosition(100, 100);
    gameOverText.setCharacterSize(115);

    sf::Texture enemyTexture;
    enemyTexture.loadFromFile("enemy.png");

    // bullet texture
    sf::Texture bulletTexture;
    bulletTexture.loadFromFile("bulletTexture.png");

    std::vector<Alien> alienArray;
    std::vector<Alien> alienPositions;
    std::vector<Bullet> enemyBullets;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 10; j++) {
            Alien a;
            a.setPosition(j*60+120, i*15+8);
            a.setXPos(j*60+120);
            a.setYPos(i*15+8);
            // setting the bullet's position doesn't follow
            Bullet enemyBullet;
            enemyBullet.setPosition(j*60+130, i*15+40);
            enemyBullet.setFillColor(sf::Color::Magenta);
            enemyBullet.setYSpeed(-enemyBullet.getYSpeed());
            enemyBullet.setTexture(&bulletTexture);

            a.setTexture(&enemyTexture);


            if (i==0) {
                a.setFillColor(sf::Color::Red);
                a.setValue(25);
            } else if (i==1) {
                a.setFillColor(sf::Color::Yellow);
                a.setValue(20);
            } else if (i==2) {
                a.setFillColor(sf::Color::Green);
                a.setValue(15);
            } else if (i==3) {
                a.setFillColor(sf::Color(228, 191, 154, 255));
                a.setValue(10);
            }
            alienArray.push_back(a);
            // set bullet values
            enemyBullets.push_back(enemyBullet);

        }
    }

    Ship ship;
    sf::Texture texture;
    texture.loadFromFile("ship.png");
    ship.setTexture(&texture);

    // beginning screen ship
    Ship bigShip = ship;
    bigShip.setSize(sf::Vector2f(200.f, 80.f));
    bigShip.setPosition(800.f/2.f-50, 500.f-30.f);

    // explosion but using big ship properties
    sf::Texture explosionTexture;
    explosionTexture.loadFromFile("explosion.png");
    Ship explosion = bigShip;
    explosion.setTexture(&explosionTexture);
    explosion.setFillColor(sf::Color::Red);
    explosion.setSize(sf::Vector2f(2000.f, 1500.f));
    explosion.setPosition(800.f/3.f-135, 300.f-30.f);


    //Bullet bullet;
    Bullet b = ship.getBullet();
    b.setPosition(ship.getPosition().x+10, ship.getPosition().y-5);
    b.setYSpeed(-40);

    /*
    b.setTexture(&bulletTexture);
    b.scale(-1,-1);
    */



    // endline
    sf::RectangleShape line(sf::Vector2f(800, 5));
    line.setPosition(0, ship.getPosition().y + 20);


    int killedAliens = 0;
    int levels = 1;
    // Start the game loop
    while (app.isOpen()) {
        // Process events
        sf::Event event;
        while (app.pollEvent(event)) {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }

        // game logic
        if (gameState.getGameState() == "open") {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                gameState.setGameState("start");
            }
        }

        else if (gameState.getGameState() == "start") {

            if (killedAliens > 39) {
                int counter = 0;
                for (auto &val:alienArray) {
                    val.setPosition(val.getXPos(), val.getYPos()-100);
                    enemyBullets[counter++].setPosition(val.getXPos()+10, val.getYPos()-100+32);
                    val.setXSpeed(3);
                    val.setYSpeed(.5);
                    levels++;
                }
                killedAliens = 0;
            }

            ship.moveShip();
            b.moveBullet();

            if (b.getPosition().y < 0) {
                b.setPosition(ship.getPosition().x+10, ship.getPosition().y-5);
            }




            // reposition (instead of deleting aliens, reposition at collision)

            for (int i = 0; i < alienArray.size(); i++) {

                if (alienArray[i].getGlobalBounds().intersects(line.getGlobalBounds()) || lives < 1) {
                    std::cout<<"Game Over"<<std::endl;
                    gameState.setGameState("end");
                    highScore = highScore < score ? score: highScore;
                    highScoreText.setString("High Score: "+std::to_string(highScore));

                    std::fstream outFile;
                    outFile.open("num.txt", std::ios::out);
                    outFile<<highScore;
                    outFile.close();

                    gameState.setGameState("end");
                    break;

                }

                if (b.getGlobalBounds().intersects(alienArray[i].getGlobalBounds())) {
                    alienArray[i].move(10000, -10000);
                    enemyBullets[i].move(10000,-10000);
                    b.setPosition(ship.getPosition().x+10, ship.getPosition().y-5);
                    score += alienArray[i].getValue();
                    scoreText = "Score: "+std::to_string(score);
                    killedAliens++;
                }

                else {
                    if (i % 13 == 0) {
                        enemyBullets[i].moveBullet();
                        enemyBullets[i].setLaunch(true);
                        if (enemyBullets[i].getGlobalBounds().intersects(ship.getGlobalBounds())) {
                            lives--;
                            livesText = "Lives: "+std::to_string(lives);
                            enemyBullets[i].setPosition(alienArray[i].getPosition().x+10, alienArray[i].getPosition().y+32);
                            enemyBullets[i].setLaunch(false);
                        } else if (b.getGlobalBounds().intersects(enemyBullets[i].getGlobalBounds())) {
                            b.setPosition(ship.getPosition().x+10, ship.getPosition().y-5);
                            enemyBullets[i].setPosition(alienArray[i].getPosition().x+10, alienArray[i].getPosition().y+32);
                            enemyBullets[i].setLaunch(false);

                        } else if (enemyBullets[i].getPosition().y > 590) {
                            enemyBullets[i].setPosition(alienArray[i].getPosition().x+10, alienArray[i].getPosition().y+32);
                            enemyBullets[i].setLaunch(false);
                        }
                        if (levels > 1) {
                            alienArray[i].move(alienArray[i].getXSpeed()+(levels/1000), alienArray[i].getYSpeed()+(levels/1000));

                        } else {
                            alienArray[i].move(alienArray[i].getXSpeed(), alienArray[i].getYSpeed());
                        }

                    } else {
                        if (levels > 1) {
                            alienArray[i].move(alienArray[i].getXSpeed()+(levels/1000), alienArray[i].getYSpeed()+(levels/1000));
                            enemyBullets[i].move(alienArray[i].getXSpeed()+(levels/1000), alienArray[i].getYSpeed()+(levels/1000));

                        } else {
                            enemyBullets[i].move(alienArray[i].getXSpeed(), alienArray[i].getYSpeed());
                            alienArray[i].move(alienArray[i].getXSpeed(), alienArray[i].getYSpeed());
                        }

                    }

                    if (alienArray[i].getPosition().x>= 750 || alienArray[i].getPosition().x<= 50) {
                        alienArray[i].setXSpeed(-alienArray[i].getXSpeed());
                        if (levels> 1) {
                            alienArray[i].setYSpeed(alienArray[i].getYSpeed()+0.001);
                        } else {
                            alienArray[i].setYSpeed(alienArray[i].getYSpeed()+0.05);
                        }

                    }

                }

            }


        }


        // Clear screen
        app.clear(sf::Color::Black);

        text.setString(scoreText);
        text2.setString(livesText);

        // Draw the sprite
        if (gameState.getGameState() == "open") {
            app.draw(enterNote);
            app.draw(openingText);
            app.draw(bigShip);
        } else if (gameState.getGameState() == "start") {
            // text
            app.draw(text);
            app.draw(text2);
            app.draw(highScoreText);

            for (auto val:enemyBullets) {
                if (val.getLaunch()) {
                    app.draw(val);
                }
            }
            for (auto val:alienArray) {
                app.draw(val);
            }

            app.draw(b);
            app.draw(line);
            app.draw(ship);


        } else if (gameState.getGameState() == "end") {
            app.draw(gameOverText);
            app.draw(explosion);
            text.setPosition(800 * 5/8, 400);
            highScoreText.setPosition(800 * 5/8, 450);
            app.draw(text);
            app.draw(highScoreText);
        }


        app.setFramerateLimit(30);


        // Update the window
        app.display();
    }
}
