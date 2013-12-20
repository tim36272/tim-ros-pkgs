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
#include <string>

//library includes
#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>

//project includes


class OdomDriftCorrector {
public:
	OdomDriftCorrector();



	//assignment and copy is not allowed, these have no implementation
	OdomDriftCorrector operator = (const OdomDriftCorrector& rhs);
	OdomDriftCorrector(const OdomDriftCorrector& rhs);

private:
	ros::NodeHandle handle_;
	ros::Publisher odom_out_stream_;
	ros::Subscriber odom_in_stream_;
	ros::Subscriber tf_in_stream_;
	tf::TransformBroadcaster tf_out_stream;

	std::string in_topic_,out_topic_;
	void callback(const nav_msgs::Odometry& msg);
	void tfCb(const tf::tfMessage& msg);


};

int main(int argc, char* argv[]) {
	ros::init(argc,argv,"odom_drift_corrector");
	ros::NodeHandle handle("~");

	//start the systme
	OdomDriftCorrector corrector;

	//spppiinnn!
	ros::spin();

	return 0;


}

OdomDriftCorrector::OdomDriftCorrector() : out_topic_("odom"), in_topic_("odom_old"){
	odom_out_stream_ = handle_.advertise<nav_msgs::Odometry>(out_topic_,1);
	odom_in_stream_ = handle_.subscribe(in_topic_, 5, &OdomDriftCorrector::callback,this);
	tf_in_stream_ = handle_.subscribe("tf",5,&OdomDriftCorrector::tfCb,this);
}

void OdomDriftCorrector::callback(const nav_msgs::Odometry& msg_in) {
	nav_msgs::Odometry msg = msg_in;
	static int x_offset=0;
	static int y_offset=0;

	static const int x_total_offset=34.137;
	static const int y_total_offset=-7.834;
	static const int frames = 7096;
	static int current_frame = 0;
	current_frame++;
	msg.pose.pose.position.x+=x_total_offset*(double)current_frame/(double)frames;
	msg.pose.pose.position.y+=y_total_offset*(double)current_frame/(double)frames;

	odom_out_stream_.publish(msg);

}


void OdomDriftCorrector::tfCb(const tf::tfMessage& msg) {
	static int x_offset=0;
	static int y_offset=0;

	static const int x_total_offset=34.137;
	static const int y_total_offset=-7.834;
	static const int frames = 7096;
	static int current_frame = 0;
	current_frame++;



	//loop through each transform in the message and find an odom->base_link
	for(int i=0;i<msg.transforms.size();i++) {
		if(msg.transforms[i].header.frame_id=="odom" && msg.transforms[i].child_frame_id=="base_link") {
			static ros::Time last_stamp = msg.transforms[i].header.stamp;
			//this prevents re-correcting the same message multiple times
			if(msg.transforms[i].header.stamp==last_stamp) ROS_INFO_STREAM("avoiding rebroadcast of last transform");
			last_stamp = msg.transforms[i].header.stamp;
			int x = msg.transforms[i].transform.translation.x;
			int y = msg.transforms[i].transform.translation.y;

			tf::Quaternion rotation(msg.transforms[i].transform.rotation.x,
									msg.transforms[i].transform.rotation.y,
									msg.transforms[i].transform.rotation.z,
									msg.transforms[i].transform.rotation.w);



		    tf::Transform transform_out;
		    transform_out.setOrigin( tf::Vector3(x+x_total_offset*(double)current_frame/frames,
		    								 y+y_total_offset*(double)current_frame/frames, 0.0) );
		    transform_out.setRotation( rotation );
		    tf_out_stream.sendTransform(tf::StampedTransform(transform_out, msg.transforms[i].header.stamp, "odom", "base_link"));
		    ROS_INFO_STREAM("Sent a modified transform");
		}
		else {
			std::cout<<"Frame id: "<<msg.transforms[i].header.frame_id<<" child: "<<msg.transforms[i].child_frame_id<<std::endl;
		}
	}





};
