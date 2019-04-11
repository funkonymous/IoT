
#---------------------------Code #2---------------------------------------------#

from __future__ import print_function
import json
import sys
import ssl
import time
import datetime
import logging, traceback
import paho.mqtt.client as mqtt

IoT_protocol_name = "x-amzn-mqtt-ca"
aws_iot_endpoint = "aa4kn6a1t7ut8-ats.iot.eu-central-1.amazonaws.com" # <random>.iot.<region>.amazonaws.com
url = "https://{}".format(aws_iot_endpoint)

ca = "./root_CA.pem" 
cert = "./2c78acf700-certificate.pem.crt"
private = "./2c78acf700-private.pem.key"

logger = logging.getLogger()
logger.setLevel(logging.DEBUG)
handler = logging.StreamHandler(sys.stdout)
log_format = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
handler.setFormatter(log_format)
logger.addHandler(handler)

def ssl_alpn():
    try:
        #debug print opnessl version
        logger.info("open ssl version:{}".format(ssl.OPENSSL_VERSION))
        ssl_context = ssl.create_default_context()
        ssl_context.set_alpn_protocols([IoT_protocol_name])
        ssl_context.load_verify_locations(cafile=ca)
        ssl_context.load_cert_chain(certfile=cert, keyfile=private)

        return  ssl_context
    except Exception as e:
        print("exception ssl_alpn()")
        raise e

if __name__ == '__main__':
    topic = "data"
    try:
        mqttc = mqtt.Client()
        ssl_context= ssl_alpn()
        mqttc.tls_set_context(context=ssl_context)
        logger.info("start connect")
        mqttc.connect(aws_iot_endpoint, port=443)
        logger.info("connect success")
        mqttc.loop_start()

        while True:
			a= []
			with open('test.txt') as fp:
				for line in fp:
					a.append(line)
			
			now = { a[0][0:3] : a[0][4:-1] }
			logger.info("try to publish:{}".format(now))
			print (json.dumps(now))
			mqttc.publish(topic, json.dumps(now), qos=0)
			time.sleep(0.5)
			now = { a[1][0:3] : a[1][4:-1] }
			logger.info("try to publish:{}".format(now))
			mqttc.publish(topic, json.dumps(now), qos=0)
			time.sleep(0.5)
			now = { a[2][0:3] : a[2][4:-1] }
			logger.info("try to publish:{}".format(now))
			mqttc.publish(topic, json.dumps(now), qos=0)
	   		time.sleep(0.5)

    except Exception as e:
        logger.error("exception main()")
        logger.error("e obj:{}".format(vars(e)))
        logger.error("message:{}".format(e.message))
        traceback.print_exc(file=sys.stdout)
