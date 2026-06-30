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

// 1️⃣ DC 모터 속도 수신 콜백
void speedCallback(const std_msgs::Int16MultiArray &msg) {
    if (msg.data_length != 10) return;

    for (int i = 0; i < 10; i++) {
        velocity_set1[i] = msg.data[i];  // 속도 업데이트
    }

    // 모터 속도 적용
    for (int i = 0; i < 10; i++) {
        Serial.print("Motor ");
        Serial.print(i + 1);
        Serial.print(" Speed: ");
        Serial.println(velocity_set1[i]);
    }
}

ros::Subscriber<std_msgs::Int16MultiArray> speed_sub("motor_speed", speedCallback);

// 2️⃣ DC 모터 위치 수신 콜백
void positionCallback(const std_msgs::Int16MultiArray &msg) {
    if (msg.data_length != 10) return;

    for (int i = 0; i < 10; i++) {
        position_set1[i] = msg.data[i];  // 위치 업데이트
    }

    // 모터 위치 적용
    for (int i = 0; i < 10; i++) {
        Serial.print("Motor ");
        Serial.print(i + 1);
        Serial.print(" Position: ");
        Serial.println(position_set1[i]);
    }
}

ros::Subscriber<std_msgs::Int16MultiArray> position_sub("motor_position", positionCallback);

// 3️⃣ 서보 모터 각도 수신 콜백
void servoCallback(const std_msgs::Int16MultiArray &msg) {
    if (msg.data_length != 8) return;

    for (int i = 0; i < 8; i++) {
        servos[i].write(msg.data[i]);  // 서보 모터 적용
    }

    // 서보 모터 값 출력
    for (int i = 0; i < 8; i++) {
        Serial.print("Servo ");
        Serial.print(i + 1);
        Serial.print(" Angle: ");
        Serial.println(msg.data[i]);
    }
}

ros::Subscriber<std_msgs::Int16MultiArray> servo_sub("servo_angle", servoCallback);

void setup() {
    Serial.begin(57600);  // ROS Serial 통신
    nh.initNode();
    
    nh.subscribe(speed_sub);
    nh.subscribe(position_sub);
    nh.subscribe(servo_sub);

    // 서보 모터 핀 설정
    for (int i = 0; i < 8; i++) {
        servos[i].attach(servo_pins[i]);
    }

    Serial.println("Arduino ROS Initialized.");
}

void loop() {
    nh.spinOnce();  // ROS 메시지 처리
    delay(10);
}
