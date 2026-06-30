#include <ros.h>
#include <std_msgs/Int16MultiArray.h>
#include <Servo.h>

ros::NodeHandle nh;
Servo motors[10];  // 10개의 서보 모터

std_msgs::Int16MultiArray received_msg;
ros::Publisher received_pub("received_angles", &received_msg);

void motorCallback(const std_msgs::Int16MultiArray &msg) {
    received_msg.data_length = 10;  // 반드시 크기 설정
    static int16_t received_data[10];  // 데이터 저장을 위한 배열 선언
    received_msg.data = received_data;  // 배열을 메시지와 연결

    for (int i = 0; i < 10; i++) {
        int angle = msg.data[i];

        // 서보 모터가 0~180도라면 범위 제한
        //if (angle < 0) angle = 0;
        //if (angle > 180) angle = 180;

        motors[i].write(angle);
        received_data[i] = angle;  // 받은 값을 그대로 저장
    }

    received_pub.publish(&received_msg);  // 데이터를 Jetson으로 다시 보냄
}

ros::Subscriber<std_msgs::Int16MultiArray> sub("motor_angles", motorCallback);

void setup() {
    nh.initNode();
    nh.subscribe(sub);
    nh.advertise(received_pub);

    for (int i = 0; i < 10; i++) {
        motors[i].attach(2 + i);  // 핀 번호 2~11번에 모터 연결
    }
}

void loop() {
    nh.spinOnce();
}
