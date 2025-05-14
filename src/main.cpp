#if defined(__APPLE__)
#include <CoreFoundation/CoreFoundation.h>
#include <unistd.h>
#include <limits.h>
#endif
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"


int main()
{
  #if defined(__APPLE__)
    // Change working directory to Contents/Resources
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if (CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX)) {
      chdir(path);
    }
    CFRelease(resourcesURL);
  #endif

  // create window and set up
  sf::RenderWindow window(sf::VideoMode({1080, 720}), "SFML Project!");

  //initialise an instance of the game class
  Game game(window);
  
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);

  sf::Image icon;
  if (icon.loadFromFile("Data/Images/icon.png")) {
    window.setIcon(icon);
  }

  // A Clock starts counting as soon as it's created
  sf::Clock clock;


  //run the init function of the game class and check it all initialises ok
  if (!game.init())
  {
    return 0;
  }


  // Game loop: run the program as long as the window is open
  while (window.isOpen()) {
    //calculate delta time
    sf::Time time = clock.restart();
    float dt = time.asSeconds();

    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }

      else if (const auto* key_pressed = event->getIf<sf::Event::KeyPressed>()) {
        game.keyPressed(*key_pressed);
      }

      else if (const auto* key_released = event->getIf<sf::Event::KeyReleased>()) {
        game.keyReleased(*key_released);
      }

      else if (const auto* mouse_pressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        game.mousePressed(*mouse_pressed);
      }

      else if (const auto* mouse_released = event->getIf<sf::Event::MouseButtonReleased>()) {
        game.mouseReleased(*mouse_released);
      }

      else if (const auto* mouse_moved = event->getIf<sf::Event::MouseMoved>()) {
        game.mouseMoved(*mouse_moved);
      }

      else if (const auto* mouse_scroll = event->getIf<sf::Event::MouseWheelScrolled>()) {
        game.mouseScrolled(*mouse_scroll);
      }

    }

    //'update' element of the game loop
    game.update(dt);

    window.clear(sf::Color::Black);

    //'render' element of the game loop
    game.render();
    window.display();
  }

  return 0;
}
