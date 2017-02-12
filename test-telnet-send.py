import sys
import telnetlib

HOST = "192.168.101.107"

tn = telnetlib.Telnet(HOST)

## Clear command
tn.write("/");
tn.write("Hi telnet");
