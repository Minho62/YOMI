#include <Servo.h>
#include <ros.h>
#include <std_msgs/Bool.h>

#define tx_enable 12
#define MAX485_TX \
  digitalWrite(tx_enable, HIGH); \
  delayMicroseconds(10);
#define MAX485_RX \
  digitalWrite(tx_enable, LOW); \
  delayMicroseconds(10);

// 사용할 스위치 핀 (A8~A11)
const int buttonPins[4] = {A8, A9, A10, A11};
volatile bool buttonState[4] = {HIGH, HIGH, HIGH, HIGH};  // 스위치 상태 저장

// 개별적인 ROS 퍼블리셔 추가 (bool 타입 사용)
std_msgs::Bool switch_msgs[4];  // 각 스위치 상태 메시지
ros::Publisher switch_pubs[4] = {
    ros::Publisher("switch_1_state", &switch_msgs[0]),
    ros::Publisher("switch_2_state", &switch_msgs[1]),
    ros::Publisher("switch_3_state", &switch_msgs[2]),
    ros::Publisher("switch_4_state", &switch_msgs[3])
};

void setup() {
  Serial.begin(115200);

  // 스위치 핀을 입력 + 풀업 저항 설정
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  // PCICR: 핀 체인지 인터럽트 활성화 (PCINT2 그룹)
  PCICR |= (1 << PCIE2);  // PCINT2 그룹(A8~A15) 활성화

  // PCMSK2: A8~A11에 해당하는 PCINT 활성화 (PCINT24~27)
  PCMSK2 |= 0x0F;  // PCINT24~PCINT27 활성화 (A8~A11)

  // ROS 노드에 스위치 퍼블리셔 등록
  for (int i = 0; i < 4; i++) {
    nh.advertise(switch_pubs[i]);
  }
}

// PCINT2_vect: A8~A11 핀 상태 변화 감지
ISR(PCINT2_vect) {
  for (int i = 0; i < 4; i++) {
    bool newState = digitalRead(buttonPins[i]);

    if (newState != buttonState[i]) {  // 상태 변화 감지
      buttonState[i] = newState;

      // 상태 변경 시 개별 토픽에 퍼블리시
      switch_msgs[i].data = (newState == LOW);  // LOW = 버튼 눌림 (true), HIGH = 버튼 해제 (false)
      switch_pubs[i].publish(&switch_msgs[i]);
      
    }
  }
}

void loop() {
  nh.spinOnce();  // ROS 이벤트 처리
}
