#!/usr/bin/python
# coding=utf-8
""" """


import ConfigParser


filename = 'test2.ini'
config = ConfigParser.ConfigParser()


# 设置section段及对应的值
# 使用Default会报错
config.add_section("NotDefault")
config.set("NotDefault", "String", "Test")

# 写入文件
config.write(open(filename, "w"))