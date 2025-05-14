
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();


  void keyPressed(sf::Event::KeyPressed key_press);
  void keyReleased(sf::Event::KeyReleased key_released);

  void mousePressed(sf::Event::MouseButtonPressed mouse_pressed);
  void mouseReleased(sf::Event::MouseButtonReleased mouse_released);
  void mouseScrolled(sf::Event::MouseWheelScrolled mouse_scroll);
  void mouseMoved(sf::Event::MouseMoved mouse_moved);


 private:
  sf::RenderWindow& window;

};

#endif // GAME_H
