#include "Game.hpp"

// Les fonctions d'initialisation
void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(this->SCREEN_WIDTH, this->SCREEN_HEIGHT), this->WINDOW_TITLE);
    this->window->setFramerateLimit(this->FRAMERATE_LIMIT);
    this->window->setMouseCursorVisible(this->IS_MOUSE_CURSOR_VISIBLE);
}

void Game::initVariables() {
    SetConsoleOutputCP(1252);
    srand((unsigned int)time(0));

    // 0 = Blanc, 1 = Rouge, 2 = Vert, 3 = Bleu, 4 = Jaune, 5 = Noir
    this->colorTable[0] = sf::Color::White;
    this->colorTable[1] = sf::Color::Red;
    this->colorTable[2] = sf::Color::Green;
    this->colorTable[3] = sf::Color::Blue;
    this->colorTable[4] = sf::Color::Yellow;
    this->colorTable[5] = sf::Color::Black;

    // Mise à 0 du tableau
    for(int i = 0; i < this->LINES_NUMBER; i++) {
        for(int j = 0; j < this->COLUMNS_NUMBER; j++) {
            gameBoard[i][j] = 0;
        }
    }

    this->goodAnswerNumber = 0;
    this->isGameWin = false;

    // Génération de la réponse aléatoirement
    for(int i = 0; i < this->COLUMNS_NUMBER; i++) {
        this->theAnswer[i] = (rand() % ((6 - 1) - 0 + 1)) + 0; // (rand() % (MAX - MIN + 1)) + MIN;
    }

    this->tileRectangle.setSize(sf::Vector2f(this->TILE_WIDTH, this->TILE_HEIGHT));
    this->tileRectangle.setOutlineColor(sf::Color::Red);
    this->tileRectangle.setFillColor(sf::Color::White);
    this->tileRectangle.setOutlineThickness(this->TILE_OUTLINE_THICKNESS);
    this->tileRectangle.setPosition(sf::Vector2f(this->BOARD_X, this->BOARD_Y));
}

// Les constructeur/destructeurs
Game::Game() {
    this->initVariables();
    this->initWindow();
}

Game::~Game() {
    delete this->window;
}

//Fonctions
void Game::updateSFMLEvents() {
    while(this->window->pollEvent(this->sfEvent)) {
        if(this->sfEvent.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { // On peut fermer la fenêtre en appuyant sur Escape
            this->window->close();
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->currentMouseState = true;
        } else {
            this->currentMouseState = false;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            this->currentEnterPressed = true;
        } else {
            this->currentEnterPressed = false;
        }
    }
}

void Game::update() {
    if(this->isGameWin == false) {
        this->updateSFMLEvents();

        if(sf::Mouse::getPosition(*window).x > this->BOARD_X &&
           sf::Mouse::getPosition(*window).x < this->BOARD_X + this->BOARD_WIDTH &&
           sf::Mouse::getPosition(*window).y > this->BOARD_Y &&
           sf::Mouse::getPosition(*window).y < this->BOARD_Y + this->BOARD_HEIGHT)
        {
            if(this->currentMouseState == true && this->oldMouseState == false) { // Il y a un clic dans la grille, il faut donc trouver sur quelle case et changer la couleur de celle-ci
                int colonne = (((sf::Mouse::getPosition(*window).x - this->BOARD_X) * this->COLUMNS_NUMBER) / this->BOARD_WIDTH);

                if(gameBoard[this->currentLine][colonne] == 5) {
                    gameBoard[this->currentLine][colonne] = 0;
                } else {
                    this->gameBoard[this->currentLine][colonne] += 1;
                }
            }

            if(this->currentEnterPressed == true && this->oldEnterPressed == false) { // Quand la touche entrée est pressée

                this->goodAnswerNumber = 0;
                std::system("cls");

                for(int i = 0; i < this->COLUMNS_NUMBER; i++) {
                    if(this->gameBoard[this->currentLine][i] == this->theAnswer[i]) {
                        std::cout << "La couleur de la case " << (i + 1) << " est correcte." << std::endl;
                        this->goodAnswerNumber++;
                    } else {
                        std::cout << "La couleur de la case " << (i + 1) << " est incorrecte." << std::endl;
                    }
                }

                if(this->goodAnswerNumber == this->COLUMNS_NUMBER) { // La partie est maintenant gagnée
                    this->isGameWin = true;
                }

                // Cette condition est à virer/refractor
                if(!(this->currentLine == this->LINES_NUMBER - 1)) { // Le -1 c'est parce que gameBoard est un tableau et donc il s'arrête à 9
                    this->currentLine++;
                }
            }
        }

        this->oldMouseState = this->currentMouseState; // Pour éviter d'avoir les 60 clics par secondes
        this->oldEnterPressed = this->currentEnterPressed; // Pour éviter de sauter des lignes
    } else { // Si la partie est gagnée
        std::cout << "Bravo, vous avez gagné" << std::endl;
    }
}

void Game::render() {
    this->window->clear();

    if(this->isGameWin == false) {
        // Affichage complet de la grille
        for(int i = 0; i < this->LINES_NUMBER; i++) {
            for(int j = 0; j < this->COLUMNS_NUMBER; j++) {
                // Changement de la couleur en fonction de la couleur adressée dans le tableau de couleur
                this->tileRectangle.setFillColor(this->colorTable[gameBoard[i][j]]);
                this->tileRectangle.setPosition(sf::Vector2f(this->BOARD_X + (j * this->TILE_WIDTH), this->BOARD_Y + i * (this->TILE_HEIGHT)));
                this->window->draw(tileRectangle);
            }
        }
    } else {
        // Ecran de victoire -> A coder
    }


    this->window->display();
}

void Game::run() {
    while(this->window->isOpen()) {
        this->update();
        this->render();
    }
}
