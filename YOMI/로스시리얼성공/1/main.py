#!/usr/bin/env python

import rospy
from std_msgs.msg import Int16MultiArray
import random

def motor_publisher():
    rospy.init_node('motor_publisher', anonymous=True)
    pub = rospy.Publisher('/motor_angles', Int16MultiArray, queue_size=10)

    rate = rospy.Rate(80)  # 10Hz

    while not rospy.is_shutdown():
        angles = Int16MultiArray()
        angles.data = [random.randint(0, 360) for _ in range(10)]  # 테스트용 데이터
        rospy.loginfo(f"Publishing: {angles.data}")
        pub.publish(angles)
        rate.sleep()

if __name__ == '__main__':
    try:
        motor_publisher()
    except rospy.ROSInterruptException:
        pass
