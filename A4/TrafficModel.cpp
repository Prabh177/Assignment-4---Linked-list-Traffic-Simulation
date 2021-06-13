#include "TrafficModel.h"




TrafficModel::TrafficModel() { }
TrafficModel::~TrafficModel(){ }

void TrafficModel::set_commands(vector<string> commands)
{
	this->commands = commands;
}

/* A helper function.
 * Given a specific id as the input, it searches the lane change command stored in
 * "commands". Returns the value of the turn-light in the command for this car id.
 * 0 = no light, 1 = left light, 2 = right light.
 */
int TrafficModel::get_lane_change_command(int id)
{
	int count = commands.size();
	for (int i = 0; i < count; i++){
		size_t found = commands[i].find(',');
		string iter_id = commands[i].substr(0, found);
		string light = commands[i].substr(found+1, commands[i].size()-1);
		stringstream ss1(iter_id);
		int id_value;
		ss1 >> id_value;
		if (id_value == id){
			stringstream ss2(light);
			int light_value;
			ss2 >> light_value;
			return light_value;
		}
	}
	return 0;
}

/*
 * The function that updates the vehicle positions and states.
 */
void TrafficModel::update()
{
	// TODO: complete this function
		for (uint i = 0; i < platoons.size(); i++){

			Car* temp = platoons[i].get_tail();
			Car* tempTwo = temp;
			uint max_lane = platoons.size() - 1;

			while (temp != NULL){

				//Changeing left lane
					if (get_lane_change_command(temp->get_id()) == 1
							&&  i != 0 && temp->get_has_moved() == false){
							if (platoons[i-1].get_head() == NULL){
								tempTwo = temp->get_prev();
								platoons[i].remove(temp);
								platoons[i-1].prepend(temp);
								temp -> set_has_moved(true);
								temp = tempTwo;
							}

							else if ( platoons[i-1].check_occupied(temp->get_position()) == false) {
								tempTwo = temp->get_prev();
								platoons[i].remove(temp);
					 		  platoons[i-1].add_to_platoon(temp);
					 			temp -> set_has_moved(true);
					 			temp = tempTwo;
							}
							else {
								temp -> set_position(temp->get_position()+1);
								temp -> set_has_moved(true);
								temp = temp -> get_prev();
							}
				  }
				 // changing right lane

				 else if (get_lane_change_command(temp->get_id()) == 2
			 						&& i != max_lane && temp -> get_has_moved() == false){

							if (platoons[i+1].get_head() == NULL){
								tempTwo = temp->get_prev();
								platoons[i].remove(temp);
								platoons[i+1].prepend(temp);
								temp -> set_has_moved(true);
								temp = tempTwo;

							}
							else if( platoons[i+1].check_occupied( temp->get_position() ) == false){
								tempTwo = temp->get_prev();
								platoons[i].remove(temp);
								platoons[i+1].add_to_platoon(temp);
								temp -> set_has_moved(true);
								temp = tempTwo;
							}
							else {
								temp -> set_position(temp->get_position()+1);
								temp -> set_has_moved(true);
								temp = temp -> get_prev();
							}

			 	} // end lane change right

				 //Going striaght and if it has moved
				  else if ( temp->get_has_moved() == false
										&& platoons[i].check_occupied(temp->get_position()+1) == false) {
						tempTwo = temp->get_prev();
						temp -> set_position(temp->get_position()+1);
						temp -> set_has_moved(true);
						temp = tempTwo;

				  } // end stright

				 // if it has moved
				  else if (temp -> get_has_moved() == true){
					  temp = temp-> get_prev();
				  }
		 }// end while
	 }	//end for

// resets has changed flag
	 for (uint i = 0; i < platoons.size(); i++){

		 Car* temp = platoons[i].get_tail();

		 while (1) {
			 	temp->set_has_moved(false);
				if (temp->get_prev() != NULL) {
					temp = temp->get_prev();
				} else break;
		 }
	 }


}//end function


/*
 * Initialization based on the input information
 */
void TrafficModel::initialize(vector<string> info)
{
	int lane_count = info.size();
	for (int i = 0; i < lane_count; i++){
		Platoon p = Platoon(info[i]);
		platoons.push_back(p);
	}
}

// Returns all the vehicle states in the system
vector<string> TrafficModel::get_system_state()
{
	vector<string> output;
	int size = platoons.size();
	for (int i = 0; i < size; i++){
		// get the last vehicle in the platoon
		Car* temp = platoons[i].get_tail();
		string s = "";
		ostringstream out;
		while (temp != NULL){
			out << ";(" << temp->get_id() << "," << i << "," << temp->get_position() << \
					 "," << get_lane_change_command(temp->get_id()) << ")";
			temp = temp->get_prev();
		}

		output.push_back(out.str());
	}
	return output;
}
