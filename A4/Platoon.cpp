#include "Platoon.h"



Platoon::Platoon(string init)
{
    // the string 'init' looks like:
    // a,b ; c,d ; ... where, a and c are the vehicle id, b and d are positions.
    stringstream ss(init);
	string segment;
	while(getline(ss, segment, ';'))
	{
		size_t found = segment.find(",");
		if (found!=std::string::npos){
			string id = segment.substr(0, found);
			string pos = segment.substr(found+1, segment.size()-1);

			// conversion to integer
			stringstream s1(id);
			int id_value;
			s1 >> id_value;
			stringstream s2(pos);
			int pos_value;
			s2 >> pos_value;
			Car* car = new Car(id_value, pos_value);

            if (head == NULL)
            {
                head = car;
                tail = car;
            }
            else
            {
                tail->set_next(car);
                car->set_prev(tail);
                tail = car;
                car->set_next(NULL);
            }
		}
	}
}

Car* Platoon::get_tail()
{
	return tail;
}

Car* Platoon::get_head()
{
	return head;
}

void Platoon :: prepend (Car* car)
{
  if (head == NULL){
    head = car;
    tail = car;
    car-> set_next(NULL);
    car->set_prev(NULL);
  }
  else {
    car-> set_next(head);
    head->set_prev(car);
    head = car;
    car->set_prev(NULL);
  }

}

void Platoon :: append (Car* car)
{
    car-> set_next(NULL);
    car-> set_prev(tail);
    tail->set_next(car);
    tail= car;

}

void Platoon :: insert (Car* car)
{
  Car* pointer = head;
  while (pointer-> get_position() < car -> get_position()) {
      pointer = pointer -> get_next();
  }

  car -> set_next(pointer);
  car -> set_prev(pointer-> get_prev());

  pointer-> set_prev(car);
  pointer = pointer-> get_prev();
  pointer-> set_next(car);

}

void Platoon::remove (Car* car)
{
    if (head == car && tail == car){
      head = NULL;
      tail = NULL;
    }

    else if(car->get_prev()== NULL) { //removing head
      head = car-> get_next();
      head-> set_prev(NULL);
    }

    else if (car-> get_next() == NULL) { //removing tail
      tail = car-> get_prev();
      tail -> set_next(NULL);
    }

    else {
      car->get_prev()->set_next(car->get_next());
      car-> get_next()->set_prev(car->get_prev());
    }

}

// adds to car to platoon without the used wondering when to use prepend,
// append, insert
void Platoon :: add_to_platoon(Car* car)
{
	if (car->get_position() < head -> get_position() || (head == NULL && tail == NULL)){
			prepend(car);
 	}
	else if (car -> get_position() > tail -> get_position()){
			append(car);
	}
	else {
      insert(car);
  }
}

//returns true if position is occupied
bool Platoon :: check_occupied(int pos)
{
  Car* check = tail;
	while (check != NULL){
    if (pos == check->get_position()){
      return true;
    }
    check = check-> get_prev();
  }
  return false;

}
