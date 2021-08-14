#!/usr/bin/python3

import requests
import re

user = "natas0"
pwd = "natas0"

url = "http://%s.natas.labs.overthewire.org" % user

response = requests.get(url, auth=(user, pwd))
print(response.text)
