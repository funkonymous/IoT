
#---------------------------Code #1---------------------------------------------#

import sys
from bluepy.btle import UUID, Peripheral
import bluepy.btle as bp
import time

def enable_notify(self,  chara_uuid):
    setup_data = b"\x01\x00"
    notify = self.getCharacteristics(uuid=chara_uuid)[0]
    notify_handle = notify.getHandle() + 1
    self.writeCharacteristic(notify_handle, setup_data, withResponse=True)

 
print "\nAttempting to connect to peripheral...\n"

p = Peripheral("80:ea:ca:70:a5:94", bp.ADDR_TYPE_PUBLIC, "0")

print "-----------Printing Charasteristics-------------\n\n"

chList = p.getCharacteristics()
print "Handle   UUID                                Properties"
print "-------------------------------------------------------"
for ch in chList:
	print ("  0x"+ format(ch.getHandle(),'02X') +"   "+str(ch.uuid) +" " + ch.propertiesToString())

ch1 = chList[28]

ch2 = chList[26]

#print ch1.uuid
#print ch2.uuid

print "\n---------------------------------------------------------------------------------\n"
print "Notify ON..."
enable_notify(p,ch1.uuid)

print "Writing '0x0101' to Charasteristic 2..."
p.writeCharacteristic(ch2.getHandle(), b"\x01\x01", withResponse=True)

print "Reading data from Charasteristic 1 and writing to data.txt...\n"

file = open("data.txt","w") 
counter = 0
while (True) :
	s = p.readCharacteristic(ch1.getHandle())
	file = open("data.txt","a") 
	file.write(":".join("{:02x}".format(ord(c)) for c in s))
	file.write("\n")
	file.close()
	print ":".join("{:02x}".format(ord(c)) for c in s)
	time.sleep(1)
	#counter = counter + 1 #Get the first 5000 values to test the code
	#if (counter > 5000):
	#	break


