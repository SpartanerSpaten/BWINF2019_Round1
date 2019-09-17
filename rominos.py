#!/usr/bin/python3

def get_sourrounding_coords(coord):								# return all coords around this coord
	x_base, y_base = coord
	coords = []
	for x_coord in (x_base - 1, x_base, x_base + 1):
		for y_coord in (y_base - 1, y_base, y_base + 1):
			coords.append((x_coord, y_coord))
	del coords[4]												# remove base coord
	return coords

def get_border_squares(romino):									# return coords of all squares with place beside them
	coords = []
	for square in romino:
		is_border = False										# fallback if no free squares are found
		for coord in get_sourrounding_coords(square):			# check if at least 1 sourrounding square is free
			if coord not in romino:								# free square found, abort search
				is_border = True
				break
		if is_border:
			coords.append(square)
	return coords
	
def get_romino_pairs(romino):									# get all sqare pairs wich are touching at one corner and dont have the same neighbor square
	for square in get_border_squares(romino):					# only check squares wich have a chance
		x_coord, y_coord = square
		# TODO
		

def get_int(question):											# get integer from user
	while True:
		text = input(question)
		if text.isdecimal():
			return int(text)
		else:
			print("Fehler: Sie haben keine Nummer eingegeben")
		
rominos = [((0, 0), (0, 1))]									# structure: [((x, y), (x, y), ...), ...]
n = get_int("Aus wie vielen Quadraten sollen die Rominos bestehen? ")
# TODO