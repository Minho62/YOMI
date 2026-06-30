# YOMI

YOMI는 다중 페르소나 기반 사용자 상호작용 로봇 개발 프로젝트입니다.  
Jetson Orin NX, ROS Noetic, TurtleBot3 기반 자율주행 시스템, ATmega2560 기반 모터 제어부, DYNAMIXEL XM430, 서보모터, LIDAR, 카메라 등을 통합하여 사용자 인식 및 로봇 반응 제어를 수행합니다.

## Project Overview
<img width="312" height="416" alt="image" src="https://github.com/user-attachments/assets/d2122b8a-e40c-4be0-9286-39908516a6d7" /> <img width="312" height="416" alt="image" src="https://github.com/user-attachments/assets/bc82b12c-3d84-4fda-b453-afcc05495399" /> <img width="269" height="461" alt="image" src="https://github.com/user-attachments/assets/23239990-c5f2-4124-b890-1a4ae671874b" />

<img width="274" height="481" alt="image" src="https://github.com/user-attachments/assets/0356536c-2b24-4d38-9c8a-e21c729cd052" /> <img width="604" height="833" alt="image" src="https://github.com/user-attachments/assets/d1ff21d6-a79b-4f2e-9112-35b12481c088" />

<img width="309" height="398" alt="image" src="https://github.com/user-attachments/assets/454f76ed-b38e-4288-83c5-e0944b8946c2" /> <img width="309" height="399" alt="image" src="https://github.com/user-attachments/assets/94eb4624-3a1a-4a8d-8f7b-1cdc2d793438" />



본 프로젝트는 사용자와 상호작용할 수 있는 서비스 로봇을 목표로 하며, 다음 기능을 중심으로 개발되었습니다.

- TurtleBot3 기반 자율주행 및 SLAM
- YDLIDAR G2 기반 주변 환경 인식
- Jetson Orin NX 기반 ROS 제어 환경 구축
- ATmega2560 기반 XM430 및 서보모터 제어
- Tkinter 기반 통합 제어 GUI 제작
- 모션 저장 및 시퀀스 실행 기능
- YOLOv5 기반 객체 인식 테스트
- 스위치 센서 기반 사용자 접촉 피드백

## Hardware

- Jetson Orin NX
- OpenCR
- ATmega2560
- DYNAMIXEL XM430-W350 계열 모터
- MG92B Servo Motor
- YDLIDAR G2
- Camera
- Speaker / Microphone
- Custom Power Management PCB
- Custom Control PCB
- Pressure / Switch Sensor PCB

## Software Environment

- Ubuntu 20.04
- ROS Noetic
- Python 3.8
- Tkinter
- rosserial
- TurtleBot3 Packages
- YDLIDAR ROS Driver
- YOLOv5
- PyTorch for Jetson

## Main Features

### 1. Autonomous Navigation

TurtleBot3 기반 패키지를 활용하여 SLAM, Mapping, Navigation 기능을 구현했습니다.  
실제 로봇의 바퀴 위치, 본체 크기, LIDAR 위치에 맞게 URDF 및 costmap parameter를 수정하여 주행 안정성을 개선했습니다.

### 2. Motor Control

ATmega2560과 MAX485를 활용하여 RS485 Half-Duplex 방식으로 XM430 모터를 제어했습니다.  
DYNAMIXEL Protocol 2.0 기반 Packet 송신, CRC 계산, 위치 제어, 속도/가속도 설정 기능을 구현했습니다.

### 3. GUI Control System

Tkinter 기반 GUI를 제작하여 다음 항목을 제어할 수 있도록 구성했습니다.
<img width="621" height="354" alt="image" src="https://github.com/user-attachments/assets/a6a71e66-dff6-4f12-bc89-0b5f907e4e10" />


- XM430 모터 속도 제어
- XM430 모터 위치 제어
- 서보모터 각도 제어
- 스위치 상태 확인
- 모션 저장
- 모션 불러오기
- 시퀀스 실행

### 4. Vision Recognition

Jetson Orin NX에서 YOLOv5 환경을 구축하고, USB 카메라 기반 실시간 객체 인식 테스트를 진행했습니다.
<img width="429" height="347" alt="image" src="https://github.com/user-attachments/assets/402f0532-a069-4016-b6cc-0f132c0fce9b" />

### 5. Custom PCB Design

전원 관리 및 제어 안정성을 위해 PCB를 분리 설계했습니다.

- Power Management PCB
- Control PCB
- Switch Sensor PCB

전원부에는 퓨즈와 피드백 LED를 적용하여 과전류 및 단락 상황을 확인할 수 있도록 설계했습니다.

## 6. Block Diagram
<img width="1280" height="720" alt="POWER" src="https://github.com/user-attachments/assets/1ba21481-543e-44ec-a54f-f452b23878c9" />
<img width="1280" height="720" alt="MCU" src="https://github.com/user-attachments/assets/4039d8af-c80b-4506-bd6c-45762b70f134" />

## 7. Circuit Schematic
<img width="1169" height="824" alt="image" src="https://github.com/user-attachments/assets/f5dab2c6-bf32-4ed8-82ba-1aa045317e90" />
<img width="1167" height="824" alt="image" src="https://github.com/user-attachments/assets/cd693a2c-3b10-4020-8fe2-855b22ce23ae" />
<img width="1167" height="824" alt="image" src="https://github.com/user-attachments/assets/41830f39-21f3-43c3-b59b-3824b59d4859" />
<img width="1165" height="824" alt="image" src="https://github.com/user-attachments/assets/8c1cbd11-14a5-453b-bdbe-e61f62a17fd1" />


## 8. PCB Layout
<img width="728" height="303" alt="image" src="https://github.com/user-attachments/assets/a2c339f7-2be6-4d38-9a39-5ec27a940e39" />
<img width="732" height="674" alt="image" src="https://github.com/user-attachments/assets/4dc85825-166e-4376-9092-af0aefc272cb" />
<img width="774" height="1101" alt="image" src="https://github.com/user-attachments/assets/3072295b-3b88-421e-ad2c-d0471f50880c" />
<img width="761" height="551" alt="image" src="https://github.com/user-attachments/assets/0ebf646e-16c7-40a0-84bd-598c829538a1" />

## 9. YOMI User Manual
[![Notion Manual](https://img.shields.io/badge/Read%20Manual%20on%20Notion-000000?style=for-the-badge&logo=notion&logoColor=white)](https://app.notion.com/p/YOMI-1f447f225aae80bbb7ced6e6f21c5dcd?source=copy_link)


## Repository Structure

```text
catkin_ws/
├── src/
│   ├── yomi/
│   ├── turtlebot3_description/
│   ├── turtlebot3_navigation/
│   └── ydlidar_ros_driver/
README.md
.gitignore
