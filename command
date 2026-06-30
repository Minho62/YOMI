#모든 터미널에 적용(alt+a)
cd catkin_ws/

#(alt+o)

#무조건 실행(ROS 마스터)
roscore
________________________________________________________________________________________
#바퀴(주행) 사용 시에 입력
roslaunch turtlebot3_bringup turtlebot3_robot.launch

#키보드 주행 시
roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch
#조이스틱 주행 시
roslaunch logitech_f710_joy_ros joy_teleop.launch

#맵핑
roslaunch turtlebot3_slam turtlebot3_slam.launch

#맵핑 저장 명령어('map'은 저장되는 파일의 이름임. 수정 후 사용)
rosrun map_server map_saver -f ~/map

#맵핑 후 그림판으로 노이즈 및 벽 라인 확실하게 정비
kolourpint


#완성 된 맵을 이용한 navigation ('mapgodd' 대신 저장한 파일 이름 입력)
roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:=$HOME/mapgodd.yaml
________________________________________________________________________________________
________________________________________________________________________________________
#상체 모터 및 스위치 사용 시 입력
rosrun rosserial_python serial_node.py _port:=/dev/arduino _baud:=57600

#GUI를 통한 제어(모션 생성 및 테스트, 스위치 피드백)
rosrun yomi yomi_gui.py

#실제 개발 시 이용할 코드
rosrun yomi yomi_main.py
________________________________________________________________________________________
________________________________________________________________________________________
#영상 인식
cd /Downloads/yolov5

#기본 제공 패키지 원하는 모델로 이용 할 것.
python3 detect.py --weights yolov5m.pt --device 0 --source 0
________________________________________________________________________________________
