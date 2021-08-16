#!/usr/bin/python3

import requests
import re

user = "natas6"
pwd = "aGoY4q2Dc6MgDq4oL4YtoKtyAg9PeHa1"
url = "http://%s.natas.labs.overthewire.org/index-source.html" % user

cookies = {"loggedin": "1"}
session = requests.Session()
print(session)

response = session.get(url, auth=(user, pwd))
print(response.text)
