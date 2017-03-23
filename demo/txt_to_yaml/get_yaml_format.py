#!/usr/bin/env python
# coding=utf-8
""" """


import yaml
import pprint # for better print

filename = "/home/zhehua/Github/Config-Serilization-Tutorials/demo/txt_to_yaml/000001.yml"
f = open(filename, "r+")
yfile = yaml.load(f)


print type(yfile)
pprint.pprint(yfile)
