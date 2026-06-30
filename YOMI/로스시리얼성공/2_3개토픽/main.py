#!/usr/bin/env python

import rospy
from std_msgs.msg import Int16MultiArray
import random

def motor_control_publisher():
    rospy.init_node('motor_control_publisher', anonymous=True)

    # 3개의 토픽 생성
    speed_pub = rospy.Publisher('/motor_speed', Int16MultiArray, queue_size=10)
    position_pub = rospy.Publisher('/motor_position', Int16MultiArray, queue_size=10)
    servo_pub = rospy.Publisher('/servo_angle', Int16MultiArray, queue_size=10)

    rate = rospy.Rate(10)  # 10Hz (0.1초마다 전송)

    while not rospy.is_shutdown():
        # 1️⃣ DC 모터 속도 (10개)
        speed_msg = Int16MultiArray()
        speed_msg.data = [random.randint(0, 100) for _ in range(10)]

        # 2️⃣ DC 모터 각도 (10개)
        position_msg = Int16MultiArray()
        position_msg.data = [random.randint(0, 360) for _ in range(10)]

        # 3️⃣ 서보 모터 각도 (8개)
        servo_msg = Int16MultiArray()
        servo_msg.data = [random.randint(0, 180) for _ in range(8)]

        # 데이터 발행
        rospy.loginfo(f"Publishing Motor Speeds: {speed_msg.data}")
        speed_pub.publish(speed_msg)

        rospy.loginfo(f"Publishing Motor Positions: {position_msg.data}")
        position_pub.publish(position_msg)

        rospy.loginfo(f"Publishing Servo Angles: {servo_msg.data}")
        servo_pub.publish(servo_msg)


        rospy.loginfo(f" ")
        rate.sleep()

if __name__ == '__main__':
    try:
        motor_control_publisher()
    except rospy.ROSInterruptException:
        pass
