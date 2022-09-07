#include "Game.h"

// Private functions
void Game::initVariables()
{
	this->window = nullptr;

    // Game logic
    this->endGame = false;
    this->points = 0;
    this->health = 20;
    this->enemySpawnTimer = 20.f;
    this->enemySpawnTimerMax = this->enemySpawnTimer;
    this->maxEnemies = 5;
    this->mouseHeld = false;
}

void Game::initWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "1st Game", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
    if (this->font.loadFromFile("Fonts/DroidSansMono.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONTS::Failed! to load font!" << "\n";
    }
}

void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2f(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Cyan);
    // this->enemy.setOutlineColor(sf::Color::Green);
    // this->enemy.setOutlineThickness(1.f);
}

// Constructors / Desturctors
Game::Game()
{
	this->initVariables();
	this->initWindow();
    this->initFonts();
    this->initText();
    this->initEnemies();
}

Game::~Game()
{
	delete this->window;
}

// Accessors
const bool Game::running() const 
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return this->endGame;
}


// Function
void Game::spawnEnemy()
{
    /*
        @return void

        Spawns enemies and sets their types and colors. Spawn them at random position.
        - Sets a random type (diff).
        - Sets a random position.
        - Sets a random color.
        - Adds enemy to the vector.
    */

    this->enemy.setPosition(
        static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
    );

    // Randomize enemy type
    int type = rand() % 5;

    switch (type)
    {
    case 0:
        this->enemy.setSize(sf::Vector2f(10.f, 10.f));
        this->enemy.setFillColor(sf::Color::Magenta);
        break;
    case 1:
        this->enemy.setSize(sf::Vector2f(30.f, 30.f));
        this->enemy.setFillColor(sf::Color::Blue);
        break;
    case 2:
        this->enemy.setSize(sf::Vector2f(50.f, 50.f));
        this->enemy.setFillColor(sf::Color::Cyan);
        break;
    case 3:
        this->enemy.setSize(sf::Vector2f(70.f, 70.f));
        this->enemy.setFillColor(sf::Color::Green);
        break;
    case 4:
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        this->enemy.setFillColor(sf::Color::Red);
        break;
    default:
        this->enemy.setSize(sf::Vector2f(100.f, 100.f));
        this->enemy.setFillColor(sf::Color::Yellow);
        break;
    }

    // Spawn the enemy
    this->enemies.push_back(this->enemy);
    
}


void Game::pollEvents()
{
    // Event polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

void Game::updateMousePosition()
{
    /*
        @ return void

        Updates the mouse position:
        - Mouse position relative to window (Vector2i)
    */

    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
    std::stringstream ss;

    ss << "Point: " << this->points << "\n"
        << "Health: " << this->health << "\n";

    this->uiText.setString(ss.str());
}


void Game::updateEnemies()
{
    /**
        @return void

        Updates the enemy spawn timer and spawns enemies.
        When the totel amount of enemies is smaller than the maximum.
        Moves the enemies downwards.
        Removes the enemies at the edge of screen.
    */

    // Updating the timer for enemy spawning 
    if (this->enemies.size() < this->maxEnemies)
    {
        if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            // Spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
            this->enemySpawnTimer += 1.f;
    }

    // Moving (position and speed) and Updating (deleted) enemies
    for (int i = 0; i < this->enemies.size(); i++)
    {
        bool deleted = false;

        this->enemies[i].move(0.f, 2.f);

        // Check if enemies below the screen
        if (this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
        }

    }

    // Check if clicked upon (Attack enemies)
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (this->mouseHeld == false)
        {
            this->mouseHeld = true;

            // -> use boolean instead break
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
            {
                if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {
                    // Gain points
                    if (this->enemies[i].getFillColor() == sf::Color::Magenta)
                        this->points += 10;
                    else if (this->enemies[i].getFillColor() == sf::Color::Blue)
                        this->points += 7;
                    else if (this->enemies[i].getFillColor() == sf::Color::Cyan)
                        this->points += 5;
                    else if (this->enemies[i].getFillColor() == sf::Color::Green)
                        this->points += 3;
                    else if (this->enemies[i].getFillColor() == sf::Color::Red)
                        this->points += 1;

                    // Delete the enemy
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }

            }
        }
    }        
    else
    {
        this->mouseHeld = false;
    }
}


void Game::update()
{

    this->pollEvents();

    if (this->endGame == false)
    {
        this->updateMousePosition();

        this->updateText();

        this->updateEnemies();
    }

    // End game condition
    if (this->health <= 0)
        this->endGame = true;
}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    // Render all the enemies
    for (auto &e : this->enemies)
    {
        target.draw(e); 
    }
}


void Game::render()
{
    /*
        @return void

        = clear old frame
        - render objects
        - display frame in window

        Renders the game object.
    
    */
    this->window->clear(); 

    // Draw game object
    this->renderEnemies(*this->window);

    this->renderText(*this->window);

    this->window->display();

}

