import socket
import time
import json
import math

local_ip = "127.0.0.1"
local_port = 20001
buffer_size = 1024
client_address = (local_ip, 9870)


# Create a datagram socket
udp_server_socket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

# Bind to address and ip
udp_server_socket.bind((local_ip, local_port))

i = 0
while True:
    msg_dict = {"timestamp": i, "value": math.sin(i / 100.0 * 2.0 * math.pi)}
    msg = json.dumps(msg_dict, indent=4)
    bytes_to_send = str.encode(msg)
    print(f"Send: {msg}")
    udp_server_socket.sendto(bytes_to_send, client_address)
    time.sleep(1)
    i += 1
