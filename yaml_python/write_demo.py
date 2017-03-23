#!/usr/bin/env python
# coding=utf-8
""" """

import datetime
import yaml
import pprint # for better print



filename = "test2.yaml"
f = open(filename, "w+")

yfile = {'DictDemo': {'key1': 'hello',
              'key2': 'hello_string',
              'key3': True,
              'key4': 1.1,
              'key5': None,
              'key6': None,
              'key7': datetime.date(1976, 7, 31),
              'key8': '123'},
 'ListDemo': ['list1', {'list2': 'hello_list'}, ['sublist1', 'sublist2']],
 'password': 123456,
 'username': 'admin'}


print type(yfile)
pprint.pprint(yfile)


yaml.dump(yfile, f)
f.close()


print("Read________________________________")
f = open(filename, "r+")
yfile = yaml.load(f)


print type(yfile)
pprint.pprint(yfile)

print(yfile["username"])
print(yfile["password"])
for i in range(1,9):
	print(yfile["DictDemo"]["key"+str(i)])
print(yfile["ListDemo"][0])
print(yfile["ListDemo"][1])
print(yfile["ListDemo"][2][0])
print(yfile["ListDemo"][2][1])
