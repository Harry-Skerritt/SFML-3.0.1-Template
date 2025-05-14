
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window) {
  srand(time(NULL));
}
Game::~Game()
{

}

bool Game::init()
{

  return true;
}

void Game::update(float dt) {

}

void Game::render() {

}

// *** Keyboard Events ***
void Game::keyPressed(sf::Event::KeyPressed key_press) {

}

void Game::keyReleased(sf::Event::KeyReleased key_released) {

}

// *** Mouse Events ***
void Game::mousePressed(sf::Event::MouseButtonPressed mouse_pressed) {

}

void Game::mouseReleased(sf::Event::MouseButtonReleased mouse_released) {

}

void Game::mouseScrolled(sf::Event::MouseWheelScrolled mouse_scroll) {

}

void Game::mouseMoved(sf::Event::MouseMoved mouse_moved) {

}





