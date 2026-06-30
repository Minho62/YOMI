#!/usr/bin/env python

import rospy
from std_msgs.msg import Int16MultiArray

def callback(msg):
    rospy.loginfo(f"Received from Arduino: {msg.data}")

def received_subscriber():
    rospy.init_node('received_checker', anonymous=True)
    rospy.Subscriber('/received_angles', Int16MultiArray, callback)
    rospy.spin()

if __name__ == '__main__':
    try:
        received_subscriber()
    except rospy.ROSInterruptException:
        pass
