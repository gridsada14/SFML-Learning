# SFML_Learning
## Setup SFML in Visual Studio 
1. Add External (include, lib) same path as .sln
2. Add all .dll file same path as main.c 
3. Property page (Alt + Enter)
	1. C/C++ -> Genaral -> Additional Include Directories
	```$(SolutionDir)\External\include```
	2. Linker -> General -> Additional Library Directories 
	```$(SolutionDir)\External\lib```
	3. Linker -> Input -> Additional Depencies
	*[configration: Release]*
	```sfml-system.lib
	   sfml-graphics.lib
  	   sfml-window.lib
	   sfml-audio.lib
	   sfml-network.lib
	```
	*[configration: Debug]*
	```sfml-system-d.lib
	   sfml-graphics-d.lib
  	   sfml-window-d.lib
	   sfml-audio-d.lib
	   sfml-network-d.lib
	```


## Fix problem
1. problem : ... sfml-system-d-2.dll was not found 
   fixed   : put all .dll of SFML at same path with main.cpp		


## Game 1 : Falling Enemies 
1. Creating the window
	- Create simple window
2. Creating the game class
	- Code time line [make] -> [update] -> [render]
	- Organize file
		- Game.h   : include and variable
		- Game.cpp : Event and function
		- main.cpp : main for run game
3. Enemy(simple shape) and mouse position.
	- Simple create static shape
	- Get and update mouse position
	- Trick 
		- Top left is 0,0
		- In default getPosition() is relative to screen.
	      (*this->window) make it relative to window 
4. Enemies
	- Random spawn enemy on top screen
	- Enemy move downward 
	- [Enemy Task] Spawn(position) -> Update(spawn time, move) -> Render(draw)
	- Trick
		- At spawn enemy position can input 0.f instead random it will spawn at edge screen.
5. Killing enemies
	- The effective way id check click before mouse in enemy position
	- Event that enemies die (click, out of screen)
	- Trick
		- Don't want a lot of for loop cause might bug out later
		  Should have 1-2 for loop for your enemies
		- Iterators in C++ make for loop much faster 
		- Best way is to have own vertor class for easy and quick way to deleate stuff
6. Points and Health
	- Fix for can't hold down the mouse
	- Count score and health
	- Create endgame function
	- Trick
		- Use boolean to cancel the loop instead break cause i can forgot break
		- Point use unsigned instead integer cause point doesn't < 0
7. Fonts and Text
	- In text funtion have many setting, you can choose by own.
	- [Game.h]declear variable at private -> declear init function(link to Game.cpp) at private -> [Game.cpp]declear init variable -> setting in init function -> [Game.h] create update and init at public function
	- Trick
		- [Game.cpp] Should render text at last in main render.

		- [Game.h] In declear public function and [Game.cpp]render function should input "sf::RenderTarget& target" for easy to maintain
		- include sstream.h will make long string mixed with other variable type
8. Enemy types & difficulties
	- Create 5 types of enemies, Each type has different score.



## Game 2 : Pickup Swag Balls
1. Setting up Game class
	- Organize file
	- Setup Visual Studio and Game class 
2. Game loop (Updating and Rendering)
	- Escape button (Esc)
	- Create player class and simple set player
	- Trick 
		- \#include SFML folder is in player.h (deepest)
		- Class calling (Create object) : main.cpp <- Game.h <- player.h  		
3. Moving the player
	- Player moveable form keyboard
	- Create class SwagBall
	- Trick 
		- sf::Keyboard -> (right click) -> F12 = know the code of any key on keyboard
		- move() will take current position then add position
4. Window bounds collision
	- Invisible wall at edge of screen
	- Setup SwagBall class
5. Spawning balls (enemies)
	- Fix bug _can walk through corner_ 
	  Fixed : use default global var instead declear as new var
	- Spawn enemies in screen
6. Colliding and kiling balls
	- Check intersect of player and enemies = killing
	- Order the line of code = layer of sprite
	- collision = fight <- use intersect to decide
7. Fonts and text (points)
	- Create text and fonts object 
	- Text display points counter when touch enemies
	- count points and health
8. Ball type and behaviour
	- Each ball type have own behaviour
		- random color : increase points
		- red color    : damage
		- green color  : heal
9. Ending game and player dead
	- Create object to set change to random type 
		1. random 1 - 100
 		2. if random in range will happend (ex. 60 < x < 80 will be heal)
	- Create endgame object 
		- Put _!endGame_ at function that check game is running @[Game.cpp]
	- Create object update player
		- For check is player dead
	- Create endgame text
		- _if endgame == false_ will run function in Game::update()
		- In render _if endgame == true_ will draw endgameText
	- Trick 
		- rand() % 100 + 1 = random 1 - 100

	

	
