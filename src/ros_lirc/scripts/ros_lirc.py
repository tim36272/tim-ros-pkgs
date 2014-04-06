#!/usr/bin/env python
import rospy
from subprocess import call
from ros_lirc.msg import Lirc
def callback(data):
	print data.cmd

def listener():
	rospy.init_node('ros_lirc')
	rospy.Subscriber("/lirc",String,callback)
	rospy.spin()

if __name__ == '__main__':
	listener()
