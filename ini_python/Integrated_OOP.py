#!/usr/bin/python
# coding=utf-8
""" """

import ConfigParser
import os

def create_if_not_exist(filename):
	if not os.path.exists(filename):
		os.system("touch " + filename)
	return filename

class INIFILE():
	def __init__(self, filename):
		self.filename = filename
		self.cfg = ConfigParser.ConfigParser()
		try:
			create_if_not_exist(self.filename)
			self.readhandle = open(self.filename, 'r+')
			self.writehandle = open(self.filename, 'w+')

			self.cfg.readfp(self.readhandle)
			self.initflag = True
		except:
			self.initflag = False

	def Close(self):
		if self.initflag:
			self.readhandle.close()
			self.writehandle.close()

	def GetValue(self, Section, Key, Default = ""):
		try:
			value = self.cfg.get(Section, Key)
		except:
			value = Default
		return value

	def SetValue(self, Section, Key, Value):
		try:
			self.cfg.set(Section, Key, Value)
		except:
			self.cfg.add_section(Section)
			self.cfg.set(Section, Key, Value)
			self.cfg.write(open(self.filename, 'w+'))


filename = 'test3.ini'
ini1 = INIFILE(filename)
if ini1.initflag:
	print("Initial Success!")

ini1.SetValue("Demo1", "String", "Test")
ini1.SetValue("Demo2", "String", "Test")
print(ini1.GetValue("Demo1", "String", "Empty"))
print(ini1.GetValue("Demo3", "String", "Empty"))

ini1.Close()

