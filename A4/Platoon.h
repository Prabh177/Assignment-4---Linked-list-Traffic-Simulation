#ifndef _Platoon_H_
#define _Platoon_H_

#include <vector>
#include <string>
#include <sstream>
#include "Car.h"

using namespace std;

class Platoon
{
    private:
        Car* head = NULL;
        Car* tail = NULL;

    public:
        Platoon(string init);
        Car* get_tail();
        Car* get_head();


         void remove(Car* car);
         void append(Car* car);
         void prepend(Car* car);
         void insert(Car* car);



         //Helper functions
        void add_to_platoon(Car* car);
     		bool check_occupied(int pos);

      


};
#endif
