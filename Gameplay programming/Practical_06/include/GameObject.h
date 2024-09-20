#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream> 
#include <stdlib.h>     
#include <time.h>       
#include <math.h>  
#include <SFML/Graphics.hpp>

using namespace sf;

class GameObject {
public:
	GameObject();
	~GameObject();
	void initialize(String);
	void update();
	void draw(sf::RenderWindow&);
	void setPosition(Vector2f);
	Vector2f getPosition();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();

	void run();
	void jump();
	void crouch();
	void attack();
	void shield();
protected:
	Vector2f position;
	Sprite sprite;
	Texture texture;
};
#endif // !GAMEOBJECT_H