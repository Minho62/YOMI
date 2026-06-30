#include <ros.h>
#include <std_msgs/Int16.h>
#include <Servo.h>

#define tx_enable 12
#define MAX485_TX digitalWrite(tx_enable, HIGH); delayMicroseconds(10);
#define MAX485_RX digitalWrite(tx_enable, LOW); delayMicroseconds(10);

// 서보 모터 객체 생성
Servo servos[8];
int servo_pins[8] = {2, 3, 4, 5, 7, 8, 9, 10};

// DC 모터 속도 및 위치 배열
int velocity_set1[10] = {70, 70, 70, 70, 70, 70, 70, 70, 70, 70};
int position_set1[10] = {180, 180, 180, 180, 180, 180, 180, 180, 180, 180};

// ROS 노드 생성
ros::NodeHandle nh;

// 1️⃣ DC 모터 속도 수신 콜백
void speedCallback_1(const std_msgs::Int16 &msg) { velocity_set1[0] = msg.data; }
void speedCallback_2(const std_msgs::Int16 &msg) { velocity_set1[1] = msg.data; }
void speedCallback_3(const std_msgs::Int16 &msg) { velocity_set1[2] = msg.data; }
void speedCallback_4(const std_msgs::Int16 &msg) { velocity_set1[3] = msg.data; }
void speedCallback_5(const std_msgs::Int16 &msg) { velocity_set1[4] = msg.data; }
void speedCallback_6(const std_msgs::Int16 &msg) { velocity_set1[5] = msg.data; }
void speedCallback_7(const std_msgs::Int16 &msg) { velocity_set1[6] = msg.data; }
void speedCallback_8(const std_msgs::Int16 &msg) { velocity_set1[7] = msg.data; }
void speedCallback_9(const std_msgs::Int16 &msg) { velocity_set1[8] = msg.data; }
void speedCallback_10(const std_msgs::Int16 &msg) { velocity_set1[9] = msg.data; }

ros::Subscriber<std_msgs::Int16> speed_subs[10] = {
    ros::Subscriber<std_msgs::Int16>("motor_1/speed", speedCallback_1),
    ros::Subscriber<std_msgs::Int16>("motor_2/speed", speedCallback_2),
    ros::Subscriber<std_msgs::Int16>("motor_3/speed", speedCallback_3),
    ros::Subscriber<std_msgs::Int16>("motor_4/speed", speedCallback_4),
    ros::Subscriber<std_msgs::Int16>("motor_5/speed", speedCallback_5),
    ros::Subscriber<std_msgs::Int16>("motor_6/speed", speedCallback_6),
    ros::Subscriber<std_msgs::Int16>("motor_7/speed", speedCallback_7),
    ros::Subscriber<std_msgs::Int16>("motor_8/speed", speedCallback_8),
    ros::Subscriber<std_msgs::Int16>("motor_9/speed", speedCallback_9),
    ros::Subscriber<std_msgs::Int16>("motor_10/speed", speedCallback_10)
};

// 2️⃣ DC 모터 위치 수신 콜백
void positionCallback_1(const std_msgs::Int16 &msg) { position_set1[0] = msg.data; }
void positionCallback_2(const std_msgs::Int16 &msg) { position_set1[1] = msg.data; }
void positionCallback_3(const std_msgs::Int16 &msg) { position_set1[2] = msg.data; }
void positionCallback_4(const std_msgs::Int16 &msg) { position_set1[3] = msg.data; }
void positionCallback_5(const std_msgs::Int16 &msg) { position_set1[4] = msg.data; }
void positionCallback_6(const std_msgs::Int16 &msg) { position_set1[5] = msg.data; }
void positionCallback_7(const std_msgs::Int16 &msg) { position_set1[6] = msg.data; }
void positionCallback_8(const std_msgs::Int16 &msg) { position_set1[7] = msg.data; }
void positionCallback_9(const std_msgs::Int16 &msg) { position_set1[8] = msg.data; }
void positionCallback_10(const std_msgs::Int16 &msg) { position_set1[9] = msg.data; }

ros::Subscriber<std_msgs::Int16> position_subs[10] = {
    ros::Subscriber<std_msgs::Int16>("motor_1/position", positionCallback_1),
    ros::Subscriber<std_msgs::Int16>("motor_2/position", positionCallback_2),
    ros::Subscriber<std_msgs::Int16>("motor_3/position", positionCallback_3),
    ros::Subscriber<std_msgs::Int16>("motor_4/position", positionCallback_4),
    ros::Subscriber<std_msgs::Int16>("motor_5/position", positionCallback_5),
    ros::Subscriber<std_msgs::Int16>("motor_6/position", positionCallback_6),
    ros::Subscriber<std_msgs::Int16>("motor_7/position", positionCallback_7),
    ros::Subscriber<std_msgs::Int16>("motor_8/position", positionCallback_8),
    ros::Subscriber<std_msgs::Int16>("motor_9/position", positionCallback_9),
    ros::Subscriber<std_msgs::Int16>("motor_10/position", positionCallback_10)
};

// 3️⃣ 서보 모터 각도 수신 콜백
void servoCallback_1(const std_msgs::Int16 &msg) { servos[0].write(msg.data); }
void servoCallback_2(const std_msgs::Int16 &msg) { servos[1].write(msg.data); }
void servoCallback_3(const std_msgs::Int16 &msg) { servos[2].write(msg.data); }
void servoCallback_4(const std_msgs::Int16 &msg) { servos[3].write(msg.data); }
void servoCallback_5(const std_msgs::Int16 &msg) { servos[4].write(msg.data); }
void servoCallback_6(const std_msgs::Int16 &msg) { servos[5].write(msg.data); }
void servoCallback_7(const std_msgs::Int16 &msg) { servos[6].write(msg.data); }
void servoCallback_8(const std_msgs::Int16 &msg) { servos[7].write(msg.data); }

ros::Subscriber<std_msgs::Int16> servo_subs[8] = {
    ros::Subscriber<std_msgs::Int16>("servo_1/angle", servoCallback_1),
    ros::Subscriber<std_msgs::Int16>("servo_2/angle", servoCallback_2),
    ros::Subscriber<std_msgs::Int16>("servo_3/angle", servoCallback_3),
    ros::Subscriber<std_msgs::Int16>("servo_4/angle", servoCallback_4),
    ros::Subscriber<std_msgs::Int16>("servo_5/angle", servoCallback_5),
    ros::Subscriber<std_msgs::Int16>("servo_6/angle", servoCallback_6),
    ros::Subscriber<std_msgs::Int16>("servo_7/angle", servoCallback_7),
    ros::Subscriber<std_msgs::Int16>("servo_8/angle", servoCallback_8)
};

void setup() {
    Serial.begin(57600);
    nh.initNode();

    for (int i = 0; i < 10; i++) {
        nh.subscribe(speed_subs[i]);
        nh.subscribe(position_subs[i]);
    }
    for (int i = 0; i < 8; i++) {
        nh.subscribe(servo_subs[i]);
        servos[i].attach(servo_pins[i]);
    }

    Serial.println("Arduino ROS Initialized.");
}

void loop() {
    nh.spinOnce();
    delay(10);
}
