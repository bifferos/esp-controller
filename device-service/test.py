#!/usr/bin/env python3


import os
import socket
import unittest
import time
from pathlib import Path


UDP_IP = "127.0.0.1"
UDP_PORT = 6060  # Replace with your actual port
FILENAME = "testfile"
DIR = "/var/lib/esp-controller"


class TestUdpServerFileMissing(unittest.TestCase):
    def setUp(self):
        # Ensure the file does not exist
        file_path = os.path.join(DIR, FILENAME)
        if os.path.exists(file_path):
            os.remove(file_path)

    def test_file_not_found_udp(self):
        # Send UDP packet
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.settimeout(2)
        sock.sendto(FILENAME.encode(), (UDP_IP, UDP_PORT))

        # Try to receive the response
        try:
            data, _ = sock.recvfrom(1024)
            response = data.decode().strip()
        except socket.timeout:
            self.fail("No response received from UDP server")
        finally:
            sock.close()

        self.assertEqual(response, "false")


class TestUdpServerFileExists(unittest.TestCase):
    def setUp(self):
        # Ensure the file does exist
        file_path = os.path.join(DIR, FILENAME)
        if not os.path.exists(file_path):
            Path(file_path).touch()

    def test_filefound_udp(self):
        # Send UDP packet
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        sock.settimeout(2)
        sock.sendto(FILENAME.encode(), (UDP_IP, UDP_PORT))

        # Try to receive the response
        try:
            data, _ = sock.recvfrom(1024)
            response = data.decode().strip()
        except socket.timeout:
            self.fail("No response received from UDP server")
        finally:
            sock.close()

        self.assertEqual(response, "true")



if __name__ == "__main__":
    unittest.main()
