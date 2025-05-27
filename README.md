Pixel Forge
Pixel Forge is a 2D crafting-adventure game built using C++ and the SFML library. Explore a grid-based world, collect resources like wood and stone, craft tools such as axes and pickaxes, and build structures like houses to increase your score. This open-source project showcases C++ game development with a focus on exploration and creativity. Your support through GitHub Sponsors helps us enhance the game with new features and keep it free for everyone!
Features

Grid-based exploration with smooth player movement.
Resource collection (wood, stone) and crafting system (axe, pickaxe, house).
Building mechanics to place crafted items on the map.
Score tracking based on collecting, crafting, and building.
Audio feedback for collecting, crafting, and building actions.
Lightweight and extensible codebase.

Gameplay

Objective: Explore the world, gather resources, craft tools, and build structures to maximize your score.
Controls:
Arrow Keys: Move the player across the grid.
C: Collect resources (wood or stone) at the player’s position.
1: Craft an axe (requires 3 wood).
2: Craft a pickaxe (requires 3 stone).
3: Craft a house (requires 5 wood and 5 stone).
B: Build the selected item at the player’s position.


Scoring:
Collect resource: +5 points.
Craft axe or pickaxe: +10 points.
Craft house: +20 points.
Build axe or pickaxe: +20 points.
Build house: +50 points.



Prerequisites
To build and run Pixel Forge, you need:

A C++ compiler (e.g., g++).
SFML 2.5.1 or later installed and configured.
A font file (arial.ttf) for the HUD display.
Sound files (collect.wav, craft.wav, build.wav) for audio effects.

Installation

Clone the Repository:
git clone https://github.com/yourusername/PixelForge.git
cd PixelForge


Install SFML:

Download SFML from sfml-dev.org.
Follow the installation instructions for your platform (Windows, macOS, or Linux).
Link SFML libraries (graphics, window, system, audio) in your project.


Add Resources:

Place arial.ttf (e.g., from Google Fonts) in the project directory.
Place collect.wav, craft.wav, and build.wav (e.g., from Freesound) in the project directory.


Build the Project:

Example using g++:g++ -c main.cpp -I/path/to/sfml/include
g++ main.o -o PixelForge -L/path/to/sfml/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio




Run the Game:
./PixelForge



Project Structure

main.cpp: The main game source code.
arial.ttf: Font file for HUD display (not included, must be added).
collect.wav, craft.wav, build.wav: Sound files for game actions (not included, must be added).

Contributing
We welcome contributions to improve Pixel Forge! You can:

Report bugs or suggest features via GitHub Issues.
Submit pull requests with enhancements or fixes.
Share feedback to enhance gameplay or code.

To contribute:

Fork the repository.
Create a new branch (git checkout -b feature/your-feature).
Commit your changes (git commit -m 'Add your feature').
Push to the branch (git push origin feature/your-feature).
Open a pull request.

Support the Project
Love Pixel Forge and want to see it grow? Support us through GitHub Sponsors! Your contributions help:

Add new features like new resources, tools, or enemies.
Improve visuals with sprites and animations.
Maintain and optimize the codebase for the community.

Every donation helps keep Pixel Forge thriving—thank you!
Future Plans

Add a main menu and save/load system for progress.
Introduce enemies or environmental hazards.
Implement sprite-based graphics instead of colored rectangles.
Add more craftable items and building types.
Include background music and enhanced sound effects.

License
This project is licensed under the MIT License. See the LICENSE file for details.
Acknowledgments

Built with SFML.
Inspired by crafting and sandbox adventure games.
Thanks to the open-source community for tools and resources.


Forge your pixel world and thank you for playing Pixel Forge!
