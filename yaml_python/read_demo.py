#!/usr/bin/env python
# coding=utf-8
""" """


import yaml
import pprint # for better print

filename = "test1.yaml"
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