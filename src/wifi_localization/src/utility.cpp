/*
 * utility.cpp
    Copyright (C) 2014  Timothy Sweet

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "utility.h"

namespace utility {
void merge_wifiData(const wifi_localization::WifiData::_data_type& merge_from, wifi_localization::WifiData::_data_type& merge_into) {
	//for each observation in the from set
	wifi_localization::WifiData::_data_type::const_iterator from_iterator = merge_from.begin();
	while (from_iterator!=merge_from.end()) {
		//find an element with the same MAC address in the second vector
		wifi_localization::WifiData::_data_type::iterator into_iterator = merge_into.begin();
		while(into_iterator!=merge_into.end()) {
			if(from_iterator->mac_address == into_iterator->mac_address) {
				//found the same access point in both lists, average their strengths
				into_iterator->ss = (into_iterator->ss + from_iterator->ss)/2;
				break;
			}
			else {
				++into_iterator;
			}
		}
		if (into_iterator==merge_into.end()) {
			//we got to the end of the list without seeing the MAC address from the first list
			//so add it to the second list directly
			merge_into.push_back(*from_iterator);
		}
		++from_iterator;
	}
}

float compare_observation(const wifi_localization::WifiData::_data_type& truth,const wifi_localization::WifiData::_data_type& observation) {
	//counter to hold the observation's total deviation from the truth
	int total_deviation(1);
	//for every observation in the truth
	wifi_localization::WifiData::_data_type::const_iterator truth_it = truth.begin();
	while(truth_it!=truth.end()) {
		//find the corresponding observation (the one with the same MAC address
		wifi_localization::WifiData::_data_type::const_iterator observation_it = observation.begin();
		while(observation_it!=observation.end()) {
			if(truth_it->mac_address == observation_it->mac_address) {
				//found the same access point in both lists, compare their strengths
				total_deviation += abs(truth_it->ss-observation_it->ss);
				break;
			}
			else {
				++observation_it;
			}
		}
		++truth_it;
	}

	return 1.0/total_deviation;
}
int find_likelyhood(const std::vector<float>& cdf, float value_to_find) {
	//find via halfing search since they are in order
	int upper_bound = cdf.size()-1;
	int lower_bound = 0;
	while((upper_bound-1) > lower_bound) {
		int current_index = (upper_bound-lower_bound)/2+lower_bound;
		if(cdf[current_index] > value_to_find) {
			upper_bound = current_index;
		}
		else {
			lower_bound = current_index;
		}
	}
	return upper_bound;
}
} //namespace utility
