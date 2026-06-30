#include <ros.h>
#include <std_msgs/Int16MultiArray.h>
#include <Servo.h>

#define tx_enable 12
#define MAX485_TX digitalWrite(tx_enable, HIGH); delayMicroseconds(10);
#define MAX485_RX digitalWrite(tx_enable, LOW); delayMicroseconds(10);

// 서보 모터 객체 생성
Servo servos[8];  // 8개의 서보 모터

// DC 모터 변수
int velocity[10];  // 10개의 모터 속도
int position[10];    // 10개의 모터 각도

ros::NodeHandle nh;

// ROS 메시지 객체 생성
std_msgs::Int16MultiArray received_speed_msg;
std_msgs::Int16MultiArray received_position_msg;
std_msgs::Int16MultiArray received_servo_msg;

ros::Publisher speed_pub("received_motor_speed", &received_speed_msg);
ros::Publisher position_pub("received_motor_position", &received_position_msg);
ros::Publisher servo_pub("received_servo_angle", &received_servo_msg);

// 1️⃣ DC 모터 속도 수신 콜백
void speedCallback(const std_msgs::Int16MultiArray &msg) {
    if (msg.data_length != 10) return;

    for (int i = 0; i < 10; i++) {
        velocity[i] = msg.data[i];
    }

    // 받은 데이터를 Jetson으로 다시 전송
    received_speed_msg.data_length = 10;
    received_speed_msg.data = (int*)velocity;
    speed_pub.publish(&received_speed_msg);
}

ros::Subscriber<std_msgs::Int16MultiArray> speed_sub("motor_speed", speedCallback);

// 2️⃣ DC 모터 각도 수신 콜백
void positionCallback(const std_msgs::Int16MultiArray &msg) {
    if (msg.data_length != 10) return;

    for (int i = 0; i < 10; i++) {
        position[i] = msg.data[i];
    }

    // 받은 데이터를 Jetson으로 다시 전송
    received_position_msg.data_length = 10;
    received_position_msg.data = position;
    position_pub.publish(&received_position_msg);
}

ros::Subscriber<std_msgs::Int16MultiArray> position_sub("motor_position", positionCallback);

// 3️⃣ 서보 모터 각도 수신 콜백
void servoCallback(const std_msgs::Int16MultiArray &msg) {
    if (msg.data_length != 8) return;

    for (int i = 0; i < 8; i++) {
        int servo_angle = msg.data[i];

        servos[i].write(servo_angle);
    }

    // 받은 데이터를 Jetson으로 다시 전송
    received_servo_msg.data_length = 8;
    received_servo_msg.data = msg.data;
    servo_pub.publish(&received_servo_msg);
}

ros::Subscriber<std_msgs::Int16MultiArray> servo_sub("servo_angle", servoCallback);

void setup() {
    nh.initNode();
    nh.subscribe(speed_sub);
    nh.subscribe(position_sub);
    nh.subscribe(servo_sub);

    nh.advertise(speed_pub);
    nh.advertise(position_pub);
    nh.advertise(servo_pub);

    // 서보 모터 핀 설정 (D2~D10)
    servos[0].attach(2);
    servos[1].attach(3);
    servos[2].attach(4);
    servos[3].attach(5);
    servos[4].attach(7);
    servos[5].attach(8);
    servos[6].attach(9);
    servos[7].attach(10);
}

void loop() {
    nh.spinOnce();  // ROS 메시지 처리
    delay(10);
}
