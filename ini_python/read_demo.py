#!/usr/bin/python
# coding=utf-8
""" """


import ConfigParser


filename = 'test1.ini'


config = ConfigParser.ConfigParser()
config.readfp(open(filename))

print(config.get("Default","String"))