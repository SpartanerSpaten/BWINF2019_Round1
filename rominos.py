#!/usr/bin/python3
import sys

def get_sourrounding_coords(coord):								# return all coords around this coord
	x_base, y_base = coord
	coords = []
	for x_coord in (x_base - 1, x_base, x_base + 1):
		for y_coord in (y_base - 1, y_base, y_base + 1):
			coords.append((x_coord, y_coord))
	del coords[4]												# remove base coord
	return coords

def get_free_border_squares(romino):							# get coords off free squares next to romino squares
	coords = set()												# prevent duplicates
	for square in romino:
		for coord in get_sourrounding_coords(square):
			if coord not in romino:
				coords.add(coord)
	return coords
	
def get_romino_pairs(romino, free_border_squares):				# get all sqare pairs wich are touching at one corner and dont have the same neighbor square
	pass
	# TODO

def upgrade_rominos(rominos):									# upgrade from n rominos to n+1 rominos
	return 0
	# TODO

def get_mirrors(romino):										# mirror along x and y axis
	pass
	# TODO

def normalise(romino):											# move romino to touch x and y axis
	smallest_x = None
	smallest_y = None
	for x, y in romino:
		if smallest_x == None or x < smallest_x:
			smallest_x = x
		if smallest_y == None or y < smallest_y:
			smallest_y = y
	div_x = 0 - smallest_x
	div_y = 0 - smallest_y
	if not (div_x == 0 and div_y == 0):							# need adjustment
		new_romino = []
		for x, y in romino:
			new_romino.append((x + div_x, y + div_y))
		return frozenset(new_romino)
	else:
		return romino

def get_int(question):											# get integer from user
	while True:
		text = input(question)
		if text.isdecimal():
			return int(text)
		else:
			print("Fehler: Sie haben keine Nummer eingegeben")

def draw(romino):
	print(romino)
	# TODO

rominos = {frozenset(((0, 0), (1, 1)))}									# structure: {frozenset(((x, y), ...)), ...}, starting rominos (n=2)
n = get_int("Aus wie vielen Quadraten sollen die Rominos bestehen? ")
if n >= 2:
	for i in range(2, n):												# Determine number recursively
		rominos = upgrade_rominos(rominos)
	draw(rominos)
	sys.exit(0)
else:
	print("Für n kleiner als 2 existieren keine Rominos")				# rominos have at least 2 squares