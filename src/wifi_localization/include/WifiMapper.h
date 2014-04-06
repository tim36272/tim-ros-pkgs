/*
 * WifiMapper.h
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

#ifndef WIFIMAPPER_H_
#define WIFIMAPPER_H_

//STL includes
#include <vector>
#include <boost/multi_array.hpp>

//Library Includes
#include <tf/transform_listener.h>

//project includes
#include "common.h"
#include "wifi_localization/WifiData.h"

struct WifiDatapoint {
	WifiDatapoint() {}
	WifiDatapoint(const wifi_localization::WifiData& data_in) {
		data = data_in;
	}
	wifi_localization::WifiData data;
};

struct Particle {
	tf::Transform location;
	float likelyhood;
	Particle() {
		likelyhood = 0;
	}
};

class WifiMapper {
public:
	WifiMapper();
	~WifiMapper();
	bool startLocalization();
private:
	DISALLOW_COPY_AND_ASSIGN(WifiMapper);
	ros::NodeHandle handle_;
	ros::Subscriber wifi_in_stream_,wifi_map_in_stream_;
	tf::TransformListener tf_in_stream_;
	void wifi_cb(const wifi_localization::WifiDataConstPtr& wifi_msg);
	void wifi_map_cb(const wifi_localization::WifiDataConstPtr& wifi_msg);

	typedef boost::multi_array<WifiDatapoint*,2> WifiMapType;
	WifiMapType wifi_map_;
	typedef std::vector<Particle> FilterType;
	FilterType particles_;

	double wifi_map_scale_;
	int wifi_map_x_size_,wifi_map_y_size_;
	void weight_particle(const wifi_localization::AccessPoint& input);
};

#endif /* WIFIMAPPER_H_ */
