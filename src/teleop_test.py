#!/usr/bin/env python

import rospy

from geometry_msgs.msg import Twist
from ackermann_msgs.msg import AckermannDrive


class _AckermannMove(object):

    def __init__(self):
        rospy.init_node("teleop_ackermann")

        self._ackermann_speed = 0.0
        self._ackermann_accel = 0.5
        self._ackermann_steer_ang = 0.0
        self._ackermann_steer_ang_vel = 0.2

        self.ackermann_msg = AckermannDrive()
        self.twist_sub = rospy.Subscriber('/cmd_vel', Twist, self.ackermann_cb, queue_size=1)
        self.ackermann_pub = rospy.Publisher('/basic_laser_pig/ackermann_cmd', AckermannDrive, queue_size=1)

    def ackermann_cb(self, data):
        cmd_data = data
        self._ackermann_speed = cmd_data.linear.x
        self.ackermann_msg.speed = self._ackermann_speed
        self.ackermann_msg.acceleration = self._ackermann_accel
        self.ackermann_msg.steering_angle_velocity = self._ackermann_steer_ang_vel
        self.ackermann_msg.steering_angle = cmd_data.angular.z

        return self.ackermann_msg

    def spin(self):
        while not rospy.is_shutdown():
            rospy.loginfo("Attempting...")
            self.ackermann_pub.publish(self.ackermann_msg)
            rospy.sleep(0.1)


if __name__ == '__main__':
    ctrl = _AckermannMove()
    ctrl.spin()
