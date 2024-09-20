#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

using namespace std;

typedef struct Position
{
	int x;
	int y;
	void
	print()
	{
		cout << "[ x: " << x << " ]" << "[ y: " << y << " ]" << endl;
	}
} Coordinates;

typedef struct Circle {
	Coordinates coordinates;
	int r;

	void print() {
		cout << "Collision [x:" << coordinates.x << "]" << "[y:" << coordinates.y << "]" << "[r: " << r << "]" << endl;
	}
	int square(int num) {
		return num * num;
	}
	bool checkCollision(Circle collision) {
		bool result = false;
		float distance;
		
		distance = sqrt((square(collision.getX() - this->getX()))+ square((collision.getY()- this->getY())));

		if(distance <= this->getR() + collision.getR()) {
			result = true;
		}

		return result;
			
	}
	int getX() {
		return coordinates.x;
	}
	int getY() {
		return coordinates.y;
	}
	int getR() {
		return r;
	}
}Collision;

typedef struct Rectangle {
	Coordinates coordinates;
	int height;
	int width;

	void print() {
		cout << "Collision [ Bottom left: "<< coordinates.x << "," << coordinates.y << "]" << endl;
		cout << "Collision [Top right: " << coordinates.x + width << "," << coordinates.y + height << "]" << endl;
	} 
	bool checkCollision(Rectangle collision) {
		bool result = false;
			if(this->getX() + this->getWidth() >= collision.getX() && this->getX() <= collision.getX() + collision.getWidth() &&
			 this->getY() + this->getHeight() >= collision.getY() && this->getY() <= collision.getY() + collision.getHeight())
			 {
				result = true;
			 }
			 return result;
	}

	int getX() {
		return coordinates.x;
	}
	int getY() {
		return coordinates.y;
	}
	int getWidth() {
		return width;
	}
	int getHeight() {
		return height;
	}

}RectangleCollision;



enum WarHead
{
	EXPLOSIVE,
	NUCLEAR
};

typedef struct Enemy
{
	Coordinates coordinates;
	Collision ccollision;
	RectangleCollision rcollision;
} Target;

struct Missile
{
	WarHead payload;
	Coordinates coordinates;
	Target target;
	Collision ccollision;
	RectangleCollision rcollision;

	bool armed;

	void arm()
	{
		if (armed)
			armed = false;
		else
			armed = true;
	}

	void update()
	{
		coordinates.x += 1;
		coordinates.y += 2;
	}
};

WarHead selectWarhead();

WarHead selectWarhead() 
{
	WarHead selected;

	std::cout << "select warhead" << '\n' << "e.Explosive" << '\n' << "n.Nuclear" << '\n';
	char input = cin.get();

	if(input == 'e')
	{
		selected = WarHead::EXPLOSIVE;
		std::cout << "You have selected Explosive" << '\n';
	}
	if(input == 'n')
	{
		selected = WarHead::NUCLEAR;
		std::cout << "You have selected Nuclear" << '\n';
	}
		
	return selected;
}

void aquireTarget(int& x,int& y)
{

 std::cout<< "Aquire target(0-15)" << '\n';
 std::cin >> x;
 std::cin >> y;
 std::cout<< "You have selected the location: "<< x << "," << y <<'\n';

}

int main()
{
	// Create a new Enemy
	Enemy *e = new Enemy();

	srand(time(NULL)); // seed the random number generator
	int minPosition = 0; // sets the min position for the enemy
	int maxPosition = 15; // sets the max position for the enemy 

	// Set Enemy Position / Target
	e->coordinates.x = minPosition + rand() % (maxPosition - minPosition + 1); // This generates the random position for the enemy within the range
	e->coordinates.y = minPosition + rand() % (maxPosition - minPosition + 1);

	// Create a new Missile
	Missile *m = new Missile();

	// Set Missile Payload
	m->payload = selectWarhead();

	// Set Missile Target by dereferencing Enemy pointer
	m->target = *e;

	// Set Initial Position
	m->coordinates.x = 0;
	m->coordinates.y = 0;


	if(m->payload == EXPLOSIVE)	{
		m->ccollision.coordinates = m->coordinates;
		m->ccollision.r = 2;

		e->ccollision.coordinates = e->coordinates;
		e->ccollision.r = 2;
		
		cout << "Collision missile position" << endl;
		m->ccollision.print();
	}
	else {
		m->rcollision.width = 2;
		m->rcollision.height = 2;
		m->rcollision.coordinates.x = m->coordinates.x - (m->rcollision.width / 2);
		m->rcollision.coordinates.y = m->coordinates.y - (m->rcollision.height / 2);
		

		e->rcollision.width = 2;
		e->rcollision.height = 4;
		e->rcollision.coordinates.x = e->coordinates.x - (e->rcollision.width / 2);
		e->rcollision.coordinates.y = e->coordinates.y - (e->rcollision.height / 2);
		

		cout << "Collision missile position" << endl;
		m->rcollision.print();
	}
	

	


	// Print Position
	cout << "Missile Position" << endl;
	m->coordinates.print();

	// Update Position
	aquireTarget(m->coordinates.x, m->coordinates.y);

	if(m->payload == EXPLOSIVE)	{
		m->ccollision.coordinates = m->coordinates;
		m->ccollision.print();
	}
	else {
		m->rcollision.coordinates = m->coordinates;
		m->rcollision.print();
	}
	

	// Print Missile Position
	cout << "Missile Position after an Update" << endl;
	m->coordinates.print();

	int launch;
	cout<<"Please type launch code(1234)"<<'\n';
	cin >> launch;	

	if(launch == 1234)
	{
		cout<<"Launch code accepted"<<'\n';	
	}
	else
	{
		cout << "Incorrect launch code please try again" << '\n';
	}
	
	
	
	int armed;
	cout<<"Code to arm missile(4321)" << '\n';
	cin >> armed;
	if(armed == 4321)
	{
		cout<<"you have armed the missile" << '\n';
	}
	else
	{
		cout<<"Incorrect code, missile not armed"<<'\n';
	}
	

	// Print Missile target
	cout << " Enemy Target Position" << endl;
	m->target.coordinates.print();

//	if(m->coordinates.x == e->coordinates.x && m->coordinates.y == e->coordinates.y)
//	{
//		cout<<"Hit"<<'\n';
//		
//	}
//	else
//	{
//		cout<<"Miss"<<'\n';
//	}

	if(m->payload == EXPLOSIVE) {
		if(m->ccollision.checkCollision(e->ccollision)) {
			cout << "Collision detected" << endl;
		}
		else {
			cout << "No Collision" << endl;
		}
		
	}
	else {
		if(m->rcollision.checkCollision(e->rcollision)) {
			cout << "Collision detected" << endl;
		}
		else {
			cout << "No Collision" << endl;
		}
	}
	
	

	cin.get();
}