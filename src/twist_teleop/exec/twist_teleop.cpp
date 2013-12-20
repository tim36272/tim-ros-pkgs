/*
 * twist_teleop.cpp
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

//STL Includes

//library includes
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

//project includes

//types
enum compass {forward,reverse,left,right};

class TwistPublisher {
	TwistPublisher();
	TwistPublisher(const std::string& topic);

	void callback(ros::TimerEvent& event);

	void increaseLinearRate() { linear_rate_ = (linear_rate_ < 0.5) ? linear_rate_+0.02 : 0.5; }
	void decreaseLinearRate() { linear_rate_ = (linear_rate_ > -0.5) ? linear_rate_-0.02 : -0.5; }
	void increaseAngularRate() { angular_rate_ = (angular_rate_ < 0.5) ? angular_rate_+0.02 : 0.5; }
	void decreaseAngularRate() { angular_rate_ = (angular_rate_ > -0.5) ? angular_rate_-0.02 : -0.5; }
	float getLinearRate() { return linear_rate_; }
	float getAngularRate() {return angular_rate_;}

	void setDirection(compass direction) { if(direction >=forward && direction <=right) direction_ = direction; }

private:
	ros::NodeHandle handle_;
	ros::Publisher twist_out_stream;
	int linear_rate_,angular_rate_;
	compass direction_;
	std::string topic_;
	void init(const std::string& topic);

	//assignment and copy is not allowed, these have no implementation
	TwistPublisher operator = (const TwistPublisher& rhs);
	TwistPublisher(const TwistPublisher& rhs);
};

int main(int argc, char* argv[]) {
	ros::init(argc,argv,"twist_teleop");
	ros::NodeHandle handle("~");

	//ros parameters
	int rate; /* the publishing rate*/

	if(!handle.getParam("rate", rate))
		rate = 1000;

	TwistPublisher pub;
	ros::Timer timer = handle.createTimer(ros::Duration(1./rate), &TwistPublisher::callback, &pub);


}

TwistPublisher::TwistPublisher() {
	init("/cmd_vel");
}

TwistPublisher::TwistPublisher(const std::string& topic) {
	init(topic);
}

void TwistPublisher::init(const std::string& topic) {
	topic_ = topic;

	//advertise the msg
	twist_out_stream = handle_.advertise<geometry_msgs::Twist>(topic_,1000);
}

void TwistPublisher::callback(ros::TimerEvent& event) {
	//publish the current message
	geometry_msgs::Twist msg;
	switch(direction_) {
	case forward:
		msg.linear.x = linear_rate_;
		msg.angular.z = 0;
		break;
	case reverse:
		msg.linear.x = -linear_rate_;
		msg.angular.z = 0;
		break;
	case left:
		msg.linear.x = 0;
		msg.angular.z = angular_rate_;
		break;
	case right:
		msg.linear.x = 0;
		msg.angular.z = -angular_rate_;
		break;
	}
	twist_out_stream.publish(msg);
}
