/*
 * wifi_mapping.cpp
    Copyright (C) 2013  Timothy Sweet

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

//STL includes
#include <vector>

//Library includes
#include <ros/ros.h>
#include <tf/transform_listener.h>


//Project includes
#include "wifi_localization/WifiData.h"

struct wifi_localization {
	wifi_localization::WifiData wifi_points;
	tf::StampedTransform location;
};


class WifiMapper {
public:
	WifiMapper();
	bool startLocalization();
private:
	ros::NodeHandle handle_;
	ros::Subscriber wifi_in_stream_,wifi_map_in_stream_;
	void wifi_cb(const wifi_localization::WifiDataConstPtr& wifi_msg);
	void wifi_map_cb(const wifi_localization::WifiDataConstPtr& wifi_msg);

};

int main(int argc, char* argv[]) {

	ros::init(argc,argv,"Wifi_Maping");
	//create mapping object
	setLoggerDebug();
	WifiMapper wm;

	//spin
	ros::spin();
	return 0;
}

WifiMapper::WifiMapper() :
		handle_("~") {

	wifi_in_stream_ = handle_.subscribe("/wifi_tools/wifi_map_data",10,&WifiMapper::wifi_map_cb,this);
	wifi_map_in_stream_ = handle_.subscribe("/wifi_tools/wifi_data",10,&WifiMapper::wifi_cb,this);
}

void WifiMapper::wifi_cb(const wifi_localization::WifiDataConstPtr& wifi_msg) {
	//add the data point to the mapping
	ROS_DEBUG_STREAM("Got a wifi message");
}

void WifiMapper::wifi_map_cb(const wifi_localization::WifiDataConstPtr& wifi_msg) {
	//add the data point to the mapping
	ROS_DEBUG_STREAM("Got a wifi map message");
}
