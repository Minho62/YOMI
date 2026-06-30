import sys
import rospy
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QLabel, QVBoxLayout, QLineEdit
from yomi_msgs.msg import SetMotor

rospy.init_node('gui_publisher', anonymous=True)

speed_pub = rospy.Publisher('/set_motor_speed', SetMotor, queue_size=10)
position_pub = rospy.Publisher('/set_motor_position', SetMotor, queue_size=10)
servo_pub = rospy.Publisher('/set_servo_angle', SetMotor, queue_size=10)

class MotorControlGUI(QWidget):
    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):
        layout = QVBoxLayout()

        self.label1 = QLabel('Motor Index:')
        self.index_input = QLineEdit()
        self.label2 = QLabel('Value:')
        self.value_input = QLineEdit()

        self.speed_button = QPushButton('Set Speed', self)
        self.position_button = QPushButton('Set Position', self)
        self.servo_button = QPushButton('Set Servo', self)

        self.speed_button.clicked.connect(self.send_motor_speed)
        self.position_button.clicked.connect(self.send_motor_position)
        self.servo_button.clicked.connect(self.send_servo_angle)

        layout.addWidget(self.label1)
        layout.addWidget(self.index_input)
        layout.addWidget(self.label2)
        layout.addWidget(self.value_input)
        layout.addWidget(self.speed_button)
        layout.addWidget(self.position_button)
        layout.addWidget(self.servo_button)

        self.setLayout(layout)
        self.setWindowTitle('Motor Control')
        self.show()

    def send_motor_speed(self):
        index = int(self.index_input.text())
        value = int(self.value_input.text())
        msg = SetMotor()
        msg.index = index
        msg.value = value
        speed_pub.publish(msg)
        print(f"Sent Motor Speed {index}: {value}")

    def send_motor_position(self):
        index = int(self.index_input.text())
        value = int(self.value_input.text())
        msg = SetMotor()
        msg.index = index
        msg.value = value
        position_pub.publish(msg)
        print(f"Sent Motor Position {index}: {value}")

    def send_servo_angle(self):
        index = int(self.index_input.text())
        value = int(self.value_input.text())
        msg = SetMotor()
        msg.index = index
        msg.value = value
        servo_pub.publish(msg)
        print(f"Sent Servo Angle {index}: {value}")

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = MotorControlGUI()
    sys.exit(app.exec_())

