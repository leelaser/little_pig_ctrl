#from __future__ import print_function

import rospy

from geometery_msgs.msg import Twist

import can
import struct

def read_cmd_vel():
    cmd_pub = rospy.Subscriber('/cmd_vel', Twist, can_callback, queue_size 1)


def send_one(output):
    
    bus0 = can.interface.Bus(bustype='socketcan', channel='can0',bitrate=250000)
    #msg = can.Message(arbitration_id=0x20C,data=(output).to_bytes(4, byteorder="little",signed=True) + (0).to_bytes(4, byteorder="little",signed=True),is_extended_id=False)
    msg = can.Message(arbitration_id=0x20C,data=struct.pack('<ii',output,0),is_extended_id=False)

    
    print(output)
    try:
        bus0.send(msg)
        print("Message sent on {}".format(bus0.channel_info))
    except can.CanError:
        print("Message NOT sent")

#end of def send_one

#def startup():
    
#    bus0 = can.interface.Bus(bustype='socketcan', channel='can0',bitrate=250000)


#startup()

pos = 0
key_in = "\n";

while(key_in != "f"):
    key_in = raw_input("input a key")
    if((key_in == "A") or (key_in == "a")):
        pos = pos + 1000
    elif((key_in == "D") or (key_in == "d")):
        pos = pos - 1000

    print(pos)
