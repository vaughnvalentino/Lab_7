#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
	// Render Window
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	// Ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(100, 300));
	ball.setRadius(20);
	ball.applyImpulse(Vector2f(1, 0));  
	world.AddPhysicsBody(ball);

	// Floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	// Ceiling
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	// Right Wall
	PhysicsRectangle rwall;   
	rwall.setSize(Vector2f(20, 600));
	rwall.setCenter(Vector2f(790, 300));
	rwall.setStatic(true);
	world.AddPhysicsBody(rwall);   

	// Left Wall
	PhysicsRectangle lwall; 
	lwall.setSize(Vector2f(20, 600)); 
	lwall.setCenter(Vector2f(10, 300));
	lwall.setStatic(true);
	world.AddPhysicsBody(lwall); 

	// Center Square
	PhysicsRectangle rect;
	rect.setSize(Vector2f(100, 100));
	rect.setCenter(Vector2f(400, 300));
	rect.setStatic(true);
	world.AddPhysicsBody(rect);

	// Boundary Collision
	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "Thud " << thudCount << endl;
		thudCount++;
		};
	ceiling.onCollision = [&thudCount](PhysicsBodyCollisionResult result) { 
		cout << "Thud " << thudCount << endl;
		thudCount++;
		};
	rwall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) { 
		cout << "Thud " << thudCount << endl;
		thudCount++;
		};
	lwall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) { 
		cout << "Thud " << thudCount << endl;
		thudCount++;
		};

	// Square Collision
	int bangCount(0);
	rect.onCollision = [&bangCount](PhysicsBodyCollisionResult result) { 
		cout << "Bang " << bangCount << endl;
		bangCount++;
		};

	// Program Runs Until Ball Strikes Center Square Twice (Bang 0 = First Touch)
	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (bangCount <= 1) {
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}

		// Displays Boundaries, Center Square, And Ball
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(floor);
		window.draw(ceiling); 
		window.draw(rwall); 
		window.draw(lwall);
		window.draw(rect);  
		window.display();
	}
}
