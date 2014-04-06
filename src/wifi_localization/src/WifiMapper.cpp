/*
 * WifiMapper.cpp
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
//The header this file refers to
#include "WifiMapper.h"

//STL includes
#include <string>
#include <functional>
#include <algorithm>

//Libary Includes

//Project includes
#include "utility.h"
#include "PgmImage.h"

WifiMapper::WifiMapper() :
		handle_("~") {

	//do init stuff
	int particles;
	int seed;
	handle_.param( "x_size", wifi_map_x_size_, 75 );
	handle_.param( "y_size", wifi_map_y_size_, 75 );
	handle_.param( "map_scale",wifi_map_scale_,2.5);
	handle_.param( "particles",particles,5600);
	handle_.param( "seed",seed,(int)time(NULL));
	srand(seed);

	wifi_map_.resize(boost::extents[wifi_map_x_size_][wifi_map_y_size_]);
	std::fill(wifi_map_.data(),wifi_map_.data()+wifi_map_.num_elements(),static_cast<WifiDatapoint*>(0));


	//generate random distribution in filter
/*
	for(int i=0;i<particles;i++) {
		Particle temp;
		temp.location.setOrigin(tf::Vector3(rand()%wifi_map_x_size_,rand()%wifi_map_y_size_,0));
		particles_.push_back(temp);
	}
*/


	wifi_in_stream_ = handle_.subscribe("/wifi_map_data",10,&WifiMapper::wifi_map_cb,this);
	wifi_map_in_stream_ = handle_.subscribe("/wifi_data",10,&WifiMapper::wifi_cb,this);
}

//callback for points which should be added to the ground truth
void WifiMapper::wifi_map_cb(const wifi_localization::WifiDataConstPtr& wifi_msg) {
	//try to add the data point to the mapping
	if(tf_in_stream_.waitForTransform("odom","base_link",wifi_msg->header.stamp,ros::Duration(1),ros::Duration(0.1))) {
		//transform is valid
		tf::StampedTransform location;
		tf_in_stream_.lookupTransform("odom","base_link",wifi_msg->header.stamp,location);

		//convert tf position representation to internal map representation by scaling it by scale_
		//and translating it to the center
		int x_position_scaled = location.getOrigin().getX()/wifi_map_scale_ + wifi_map_x_size_/2;
		int y_position_scaled = location.getOrigin().getY()/wifi_map_scale_ + wifi_map_y_size_/2;

		//add this point to the wifi map
		//bounds checking
		if((x_position_scaled >=0 && x_position_scaled < wifi_map_x_size_) &&
		   (y_position_scaled >=0 && y_position_scaled < wifi_map_y_size_) ) {
			//check if this is the first observation in this unit
			if(wifi_map_[x_position_scaled][y_position_scaled]==NULL) {
				//this is the first observation
				ROS_DEBUG_STREAM("Adding a new observation to the map");
				wifi_map_[x_position_scaled][y_position_scaled] = new WifiDatapoint(*wifi_msg);
				Particle temp;
				temp.location.setOrigin(tf::Vector3(x_position_scaled,y_position_scaled,0));
				particles_.push_back(temp);
				std::cout<<"Num particles: "<<particles_.size()<<std::endl;
			}
			else {
				//an observation has been made in this unit before
				//merge it with the previous observation
				ROS_DEBUG_STREAM("Merging a new observation with a previous observation");
				utility::merge_wifiData(wifi_msg->data,wifi_map_[x_position_scaled][y_position_scaled]->data.data);
			}

		} else {
			ROS_WARN("Wifi message was outside of map bounds, increase map size to fix this. Dropping this data point");
		}
		PgmImage observation_map(wifi_map_x_size_,wifi_map_y_size_);
		for(int y=0;y<wifi_map_y_size_;y++) {
			for(int x=0;x<wifi_map_y_size_;x++) {
				if(wifi_map_[x][y]!=NULL) {
					observation_map.data[y][x] = 255;
				}
			}
		}
		observation_map.write("observation_map.pgm");

	}
	else {
		ROS_WARN("Unable to lookup transform for last wifi message");
	}
}

//callback for points which should have the particle filter applied to them
void WifiMapper::wifi_cb(const wifi_localization::WifiDataConstPtr& wifi_msg) {
	//need the cumulative density function for all the particles
	std::vector<float> cdf;
	cdf.push_back(0);
	//weight each particle based on the current observation
	WifiMapper::FilterType::iterator particle_it = particles_.begin();
	//for each particle
	ROS_DEBUG("Weighting particles");
	while(particle_it!=particles_.end()) {
		//get its likelyhood
		//get its location
		int particle_x = particle_it->location.getOrigin().getX();
		int particle_y = particle_it->location.getOrigin().getY();
		//get the known signal strength data associated with the particle
		WifiDatapoint* particle_data = wifi_map_[particle_x][particle_y];
		//check if there is an observation at that location in the map
		if(particle_data!=NULL) {
			//compare particle's known signal strength to current signal strength
			particle_it->likelyhood = utility::compare_observation(particle_data->data.data,wifi_msg->data);
			cdf.push_back( cdf[cdf.size()-1] + particle_it->likelyhood);
		}
		else {
			//there was no mapped observation in that location, so it is highly unlikely we are there
			particle_it->likelyhood = 0;
			cdf.push_back(cdf[cdf.size()-1]);
		}

		++particle_it;
	}
	//now every particle has a likelyhood that it represents the observation
	//resample
	ROS_DEBUG("Resampling particles");
	FilterType new_particles;
	const float max(cdf[cdf.size()-1]);
	const int num_particles(particles_.size());
	const float scale(num_particles/max);
	for(int i=0;i<num_particles;i++) {
		//select a random number between 0 and max(cdf)
		float particle_to_select = (rand()%num_particles)/scale;
		//find the particle which is just barely larger than that number
		int new_particle_index = utility::find_likelyhood(cdf,particle_to_select);
		//push the new particle into new_particles
		new_particles.push_back(particles_[new_particle_index]);
		//ROS_DEBUG_STREAM("Selecting particle: "<<new_particle_index<<" which had likelyhood: "<<particles_[new_particle_index].likelyhood);
	}
	new_particles.swap(particles_);
	ROS_DEBUG("Writing image of particles");
	//create image of the new particles
	PgmImage current_particles(wifi_map_x_size_,wifi_map_y_size_);
	for(int i=0;i<particles_.size();i++) {
		current_particles.data[(int)particles_[i].location.getOrigin().getY()][(int)particles_[i].location.getOrigin().getX()] += 10;
	}
	current_particles.write("current_particles.pgm");

	//TODO:
	/*
	 * Then add control movement
	 * Should work after that
	 */
}

void delete_data (WifiDatapoint* ptr) {
  if(ptr!=NULL) delete ptr;
}

WifiMapper::~WifiMapper() {
	std::for_each(wifi_map_.data(),wifi_map_.data()+wifi_map_.num_elements(),delete_data);
}
