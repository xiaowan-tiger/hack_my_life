

import requests
import re

user = "natas2"
next_level_user = "natas3"
pwd = "ZluruAthQk7Q2MqmDeTiUij2ZvWy2mBi"

url = "http://%s.natas.labs.overthewire.org/files/users.txt" % user

response = requests.get(url, auth=(user, pwd))
reg = "<!--The password for %s is (.*) -->" % next_level_user
print(re.findall(reg, response.text))

print(response.text)
