#include <./include/GameObject.h>
#include <iostream>

GameObject::GameObject(){
}

GameObject::~GameObject(){
}

void GameObject::initialize(String image){
	if (!texture.loadFromFile(image + ".png"))
	{
		std::cout << "Image file not found";
	}
	sprite.setTexture(texture); 
	sprite.setPosition(sf::Vector2f(position.x, position.y));
}

void GameObject::update()
{
	sprite.setPosition(this->position);
}

void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void GameObject::setPosition(Vector2f position)
{
	this->position = position;
}

Vector2f GameObject::getPosition()
{
	return this->position;
}

void GameObject::moveUp()
{
	this->position.y -= 5;
	std::cout<<"You are moving up"<<std::endl;
}

void GameObject::moveDown()
{
	this->position.y += 5;
	std::cout<<"You are moving down"<<std::endl;
}

void GameObject::moveLeft()
{
	this->position.x -= 5;
	std::cout<<"You are moving left"<<std::endl;
}

void GameObject::moveRight()
{
	this->position.x += 5;
	std::cout<<"You are moving right"<<std::endl;
}



void GameObject::run()
{
	std::cout<<"You are running"<<std::endl;
}

void GameObject::attack()
{
	std::cout<<"You are attacking"<<std::endl;
}

void GameObject::crouch()
{
	std::cout<<"You are crouching"<<std::endl;
}

void GameObject::jump()
{
	std::cout<<"You are jumping"<<std::endl;
}

void GameObject::shield()
{
	std::cout<<"You are shielding"<<std::endl;
}