#!/usr/bin/env python
# coding=utf-8
""" """

import os
from FileList import FileList

import yaml
import pprint  # for better print

# Set Path
input_folder_prefix = os.path.join(os.path.dirname(__file__), "txt")
input_foldername_prefix = "dayTraining_"

output_folder_prefix = os.path.join(os.path.dirname(__file__), "yaml")

for i in range(1, 3):
	input_folder = os.path.join(input_folder_prefix, input_foldername_prefix) + str(i)
	flist = FileList(input_folder)

	for item in flist.getFilesPathList():
		# for every .txt
		# print(item)

		# Read content
		item_list = []
		with open(item, "r") as rf:
			for row in rf:
				item_list.append(row)

		output_yaml = {'annotation': {'filename': '000001.jpg',
									  'folder': 'VOC2007',
									  'object': [],
									  'owner': {'flickrid': 'Fried Camels',
												'name': 'Jinky the Fruit Bat'},
									  'segmented': '0',
									  'size': {'depth': '3', 'height': '500', 'width': '353'},
									  'source': {'annotation': 'PASCAL VOC2007',
												 'database': 'The VOC2007 Database',
												 'flickrid': '341012865',
												 'image': 'flickr'}}}

		# [1] Write filename
		output_yaml["annotation"]["filename"] = item_list[0][12:(12 + 19)]
		# print(item_list[0][12:(12+19)])

		# [2] Write objects
		for i in range(1, len(item_list)):
			split_list = item_list[i][:-1].split(' ')
			# print(split_list)

			insert_item = {'bndbox': {'xmax': '0',
									  'xmin': '0',
									  'ymax': '0',
									  'ymin': '0'},
						   'difficult': '0',
						   'name': 'default',
						   'pose': 'Left',
						   'truncated': '0'}

			insert_item['name'] = split_list[0]
			insert_item['bndbox']["xmin"] = str(split_list[1])
			insert_item['bndbox']["ymin"] = str(split_list[2])
			insert_item['bndbox']["xmax"] = str(split_list[3])
			insert_item['bndbox']["ymax"] = str(split_list[4])
			# print(insert_item)

			output_yaml["annotation"]["object"].append(insert_item)

		# OUTPUT____________________________
		# for ouput .yml
		output_filename = os.path.join(output_folder_prefix, os.path.basename(item)[:-4]) + ".yml"
		print(output_filename)
		# pprint.pprint(output_yaml)

		with open(output_filename, "w+") as wf:
			yaml.dump(output_yaml, wf)
