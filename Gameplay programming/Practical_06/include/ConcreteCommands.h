#ifndef CONCRETE_COMMANDS_H
#define CONCRETE_COMMANDS_H

#include <./include/Command.h>
#include <iostream>

class MoveUpCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		previous = gameobject->getPosition();
		gameobject->moveUp();
	}
	virtual void undo(GameObject *gameobject)
	{
		gameobject->setPosition(previous);
	}
	Command *copy()
	{
		return new MoveUpCommand(*this);
	}

private:
	Vector2f previous;
};

class MoveDownCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		previous = gameobject->getPosition();
		gameobject->moveDown();
	}
	virtual void undo(GameObject *gameobject)
	{
		gameobject->setPosition(previous);
	}
	Command *copy()
	{
		return new MoveDownCommand(*this);
	}

private:
	Vector2f previous;
};

class MoveLeftCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		previous = gameobject->getPosition();
		gameobject->moveLeft();
	}
	virtual void undo(GameObject *gameobject)
	{
		gameobject->setPosition(previous);
	}
	Command *copy()
	{
		return new MoveLeftCommand(*this);
	}

private:
	Vector2f previous;
};

class MoveRightCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		previous = gameobject->getPosition();
		gameobject->moveRight();
	}
	virtual void undo(GameObject *gameobject)
	{
		gameobject->setPosition(previous);
	}
	Command *copy()
	{
		return new MoveRightCommand(*this);
	}
	private:
	Vector2f previous;
};

	class RunCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		gameobject->run();
	}
	virtual void undo(GameObject *gameobject)
	{
		std::cout<< "undo run" << std::endl;
	}
	Command *copy()
	{
		return new RunCommand(*this);
	}
};

	class AttackCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		gameobject->attack();
	}
	virtual void undo(GameObject *gameobject)
	{
		std::cout<< "undo attack" << std::endl;
	}
	Command *copy()
	{
		return new AttackCommand(*this);
	}
};

	class CrouchCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		gameobject->crouch();
	}
	virtual void undo(GameObject *gameobject)
	{
		std::cout<< "undo crouch" << std::endl;
	}
	Command *copy()
	{
		return new CrouchCommand(*this);
	}
};

	class JumpCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		gameobject->jump();
	}
	virtual void undo(GameObject *gameobject)
	{
		std::cout<< "undo jump" << std::endl;
	}
	Command *copy()
	{
		return new JumpCommand(*this);
	}
};

	class ShieldCommand : public Command
{
public:
	virtual void execute(GameObject *gameobject)
	{
		gameobject->shield();
	}
	virtual void undo(GameObject *gameobject)
	{
		std::cout<< "undo shield" << std::endl;
	}
	Command *copy()
	{
		return new ShieldCommand(*this);
	}
};

#endif // !CONCRETE_COMMANDS_H