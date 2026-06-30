#include <ros.h>
#include <std_msgs/Int16MultiArray.h>
#include <Servo.h>

#define tx_enable 12
#define MAX485_TX digitalWrite(tx_enable, HIGH); delayMicroseconds(10);
#define MAX485_RX digitalWrite(tx_enable, LOW); delayMicroseconds(10);

// 서보 모터 객체 생성
Servo servos[8];  
int servo_pins[8] = {2, 3, 4, 5, 7, 8, 9, 10};

// DC 모터 속도 및 위치 배열
int velocity_set1[10] = { 70, 70, 70, 70, 70, 70, 70, 70, 70, 70 };
int position_set1[10] = { 180, 180, 180, 180, 180, 180, 180, 180, 180, 180 };

// ROS 노드 생성
ros::NodeHandle nh;

// DC 모터 속도 수신 콜백
void speedCallback(const std_msgs::Int16MultiArray &msg) {
    if (msg.data_length != 10) return;

    bool updated = false;
    for (int i = 0; i < 10; i++) {
        if (msg.data[i] != velocity_set1[i]) {  // 값이 변경된 경우만 업데이트
            velocity_set1[i] = msg.data[i];
            updated = true;
        }
    }

    if (updated) {
        publishMotorSpeed();  // 변경 사항이 있을 때만 발행
    }
}

ros::Subscriber<std_msgs::Int16MultiArray> speed_sub("motor_speed", speedCallback);

// DC 모터 위치 수신 콜백
void positionCallback(const std_msgs::Int16MultiArray &msg) {
    if (msg.data_length != 10) return;

    bool updated = false;
    for (int i = 0; i < 10; i++) {
        if (msg.data[i] != position_set1[i]) {
            position_set1[i] = msg.data[i];
            updated = true;
        }
    }

    if (updated) {
        publishMotorPosition();
    }
}

ros::Subscriber<std_msgs::Int16MultiArray> position_sub("motor_position", positionCallback);

// 서보 모터 각도 수신 콜백
void servoCallback(const std_msgs::Int16MultiArray &msg) {
    if (msg.data_length != 8) return;

    for (int i = 0; i < 8; i++) {
        servos[i].write(msg.data[i]);  // 서보 모터 적용
    }

    publishServoAngles();  // 변경 사항 즉시 발행
}

ros::Subscriber<std_msgs::Int16MultiArray> servo_sub("servo_angle", servoCallback);

// 🆕 GUI에서 현재 모터 속도를 요청하는 콜백 추가
void requestSpeedCallback(const std_msgs::Int16MultiArray &msg) {
    // GUI에서 요청을 받으면 현재 모터 속도 퍼블리시
    publishMotorSpeed();
}

ros::Subscriber<std_msgs::Int16MultiArray> speed_request_sub("motor_speed_request", requestSpeedCallback);

// Publisher for Feedback, OPENCR -> PC
std_msgs::Int16MultiArray motor_speed_msg;
ros::Publisher motor_speed_pub("motor_speed", &motor_speed_msg);

std_msgs::Int16MultiArray motor_position_msg;
ros::Publisher motor_position_pub("motor_position", &motor_position_msg);

std_msgs::Int16MultiArray servo_angle_msg;
ros::Publisher servo_angle_pub("servo_angle", &servo_angle_msg);

// 모터 속도 퍼블리시 함수
void publishMotorSpeed() {
    motor_speed_msg.data_length = 10;
    motor_speed_msg.data = velocity_set1;
    motor_speed_pub.publish(&motor_speed_msg);
    Serial.println("Published Motor Speeds.");
}

// 모터 위치 퍼블리시 함수
void publishMotorPosition() {
    motor_position_msg.data_length = 10;
    motor_position_msg.data = position_set1;
    motor_position_pub.publish(&motor_position_msg);
}

// 서보 모터 각도 퍼블리시 함수
void publishServoAngles() {
    servo_angle_msg.data_length = 8;
    servo_angle_msg.data = servo_pins;
    servo_angle_pub.publish(&servo_angle_msg);
}

void setup() {
    Serial.begin(57600);  // ROS Serial 통신
    nh.initNode();
    
    nh.subscribe(speed_sub);
    nh.subscribe(position_sub);
    nh.subscribe(servo_sub);
    nh.subscribe(speed_request_sub);  // 🆕 GUI에서 요청을 받는 토픽 추가

    nh.advertise(motor_speed_pub);
    nh.advertise(motor_position_pub);
    nh.advertise(servo_angle_pub);
    
    // 서보 모터 핀 설정
    for (int i = 0; i < 8; i++) {
        servos[i].attach(servo_pins[i]);
    }

    Serial.println("Arduino ROS Initialized.");

    publishMotorSpeed();
    publishMotorPosition();
    publishServoAngles();
}

void loop() {
    nh.spinOnce();  // ROS 메시지 처리
    delay(10);
}
