#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

// Includes
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <math.h>

#define NOMINMAX
#include <Windows.h>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

class Game {

private:
    sf::RenderWindow *window;
    sf::Event sfEvent;

    bool currentMouseState;
    bool oldMouseState;

    bool currentEnterPressed;
    bool oldEnterPressed;

    const std::string WINDOW_TITLE = "Mastermind by Zahkthar";
    const int FRAMERATE_LIMIT = 60;
    const bool IS_MOUSE_CURSOR_VISIBLE = true;

    // Les trucs graphiques

    const int TILE_OUTLINE_THICKNESS = 3;

    const static int COLUMNS_NUMBER = 4;
    const static int LINES_NUMBER = 10;

    const int BOARD_X = 10;
    const int BOARD_Y = 10;

    const int SCREEN_HEIGHT = 720;

    const int BOARD_HEIGHT = SCREEN_HEIGHT - (BOARD_X * 2); // La hauteur du tableau est fixe
    const int TILE_HEIGHT = BOARD_HEIGHT / LINES_NUMBER; // La largeur d'une case est la hauteur du tableau divisée par le nombre de lignes
    const int TILE_WIDTH = TILE_HEIGHT; // Ce sont des carrés, donc largeur = longueur
    const int BOARD_WIDTH = TILE_WIDTH * COLUMNS_NUMBER; // Largeur du tableau est la largeur d'une tuile fois le nombre de tuile

    const int SCREEN_WIDTH = BOARD_WIDTH + BOARD_X + (TILE_OUTLINE_THICKNESS * COLUMNS_NUMBER);

    // La couleur dépendra du nombre dans les crochets.
    int gameBoard[LINES_NUMBER][COLUMNS_NUMBER]; // gameBoard[Ligne][Colonne]
    int currentLine = 0; // La ligne (= la tentative) actuelle

    int goodAnswerNumber = 0;
    bool isGameWin = false;

    int theAnswer[COLUMNS_NUMBER];

    // 0 = Blanc, 1 = Rouge, 2 = Vert, 3 = Bleu, 4 = Jaune, 5 = Noir
    sf::Color colorTable[6];

    sf::RectangleShape tileRectangle;

    // Les fonctions privées
    void initWindow();
    void initVariables();
public:
    // Constructeurs/Destructeurs
    Game();
    ~Game();

    // Fonctions
    void updateSFMLEvents();
    void update();
    void render();
    void run();
};

#endif
