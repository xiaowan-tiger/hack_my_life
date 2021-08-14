#!/usr/bin/python3

import requests
import re

user = "natas1"
next_level_user = "natas2"
pwd = "gtVrDuiDfck831PqWsLEZy5gyDz1clto" 

url = "http://%s.natas.labs.overthewire.org" % user

response = requests.get(url, auth=(user, pwd))
reg = "<!--The password for %s is (.*) -->" % next_level_user
print(re.findall(reg, response.text)[0])
