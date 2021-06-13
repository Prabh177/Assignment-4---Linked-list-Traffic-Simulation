#include "Car.h"

Car::Car(int id, int pos){
	this->id = id;
	this->position = pos;
}

int Car::get_id()
{
    return id;
}

int Car::get_position()
{
	return position;
}

void Car::set_position(int pos)
{
	this->position = pos;
}

void Car::set_next(Car* v)
{
    next = v;
}

void Car::set_prev(Car* v)
{
    prev = v;
}

Car* Car::get_next()
{
    return next;
}

Car* Car::get_prev()
{
    return prev;
}

// sets if it has moved to true of false input
void Car :: set_has_moved(bool x)
{
		has_moved = x;
}

//true -> the car has moved && false -> car hasn't
bool Car:: get_has_moved()
{
	return has_moved;
}
