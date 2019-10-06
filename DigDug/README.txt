GITHUB LINK: https://github.com/VanHoosteWannes/Programming4ExamAssignment

///////////////
About the game:
///////////////

movement player1:
 
wasd to move OR controller D-Pad
space to shoot OR controller A
P to select button OR controller START

movement player2:

arrows to move OR controller D-Pad
shift to shoot OR controller A

/////////////////
About the engine:
/////////////////

Key parts:

Observer pattern: classes are in but it is not used within my game.

Command pattern: Each command needs a GameObject to execute the command on. i chose for this approach because every time a command needs to get executed it needs a GameObject to do it on anyway, if this isnt the case the user can just use the IsPressed() function on a button to execute something.

State(machine): There is a state machine class in the engine that makes use of transitions, actions and conditions to switch states.  (based off Gameplay Programming)

Pathfinding: Implemented A* pathfinding in the engine. (based off Gameplay Programming)

Game Loop: The game loop works with elapsedSeconds and each component gets this elapsedSec passes in his update function.

Namespace: each class uses namespace dae.

Threading: i haven't implemented multithreading because i had no time.

Loactor: there is a locator in the engine you can use to locate players, enemies and a buttonmanager.

Inputmanager: there is controller and keyboard support for every key and button on a controller/keyboard. (based off Overlord Engine)

Scenemanager: you can easily create new scenes and switch between them to create new levels and keep everything clean. (based off Overlord Engine)

Buttonmanager: you can easily create new buttons and add them to the manager to cycle between them. you can give each button a function to activate when u press the button.

Collision: i make use of a tag system for collision, you can enable/disable collsion between different tags. At this moment it only supports quads.

Sounds: you can add sounds to your games with the SoundEffects class.

MapComponent: loads in the map based on a binary file that says which blocks are passed/broken.

Other parts:

fallingcomponent: makes sure something falls if tile underneath is passed/broken

FPScomponent: draws the fps on the screen where you want it

SpriteComponent: draws sprites