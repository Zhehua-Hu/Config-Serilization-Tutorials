#!/usr/bin/python
# coding=utf-8
"""


"""


import json

data = [ { 'a' : 1,
           'b' : 2,
           'c' : 3,
           'd' : 4,
           'e' : 5 } ]

# json = json.dumps(data)
# json = json.dumps(data, sort_keys=True, indent=4, separators=(',', ': '))
# print(json)


jsonData = '{"a":1,"b":2,"c":3,"d":4,"e":5}'
text = json.loads(jsonData)
print(text)