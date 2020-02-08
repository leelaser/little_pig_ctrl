#!/usr/bin/env python

#from __future__ import print_function
import math
from math import pi
import rospy

from geometry_msgs.msg import Twist

import can
import struct

class _CanMove(object):

    def __init__(self):
        rospy.init_node("teleop_can")

        self._can_steer_angle = 0.0
        self._can_steer_angle_vel = 0.0
        
        self.twist_sub = rospy.Subscriber('/cmd_vel', Twist, self.can_cb, queue_size=1)

    def spin(self):
        while not rospy.is_shutdown():
            rospy.loginfo("Attempting...")
            self.send_one(self._can_steer_angle * 8960 / (2 * pi))
            rospy.sleep(2.0)

    
    def can_cb(self, data):
        cmd_data = data

        self._can_steer_angle = data.angular.z

        return self._can_steer_angle

    def send_one(self, output):
    
        bus0 = can.interface.Bus(bustype='socketcan', channel='can0',bitrate=250000)
        #msg = can.Message(arbitration_id=0x20C,data=(output).to_bytes(4, byteorder="little",signed=True) + (0).to_bytes(4, byteorder="little",signed=True),is_extended_id=False)
        msg = can.Message(arbitration_id=0x199,data=struct.pack('<ii',output,0),is_extended_id=False)
    
        try:
            bus0.send(msg)
            rospy.loginfo("Message sent on {}".format(bus0.channel_info))
        except can.CanError:
            rospy.loginfo("Message NOT sent")

#end of def send_one

#def startup():
    
#    bus0 = can.interface.Bus(bustype='socketcan', channel='can0',bitrate=250000)


#startup()

if __name__ == '__main__':
    ctrl = _CanMove()
    ctrl.spin()
