import argparse

class Romino:
    def __init__(self, coords):
        self.coords = self.__normalise(coords)

    def __hash__(self):                                             # with __eq__ for use in set()
        return hash(self.get_variants())

    def __eq__(self, sample):
        if isinstance(sample, type(self)):
            return self.get_variants() == sample.get_variants()
        else:
            raise NotImplementedError
    
    def __normalise(self, coords):                                  # move romino to touch x and y axis
	    smallest_x = None
	    smallest_y = None
	    for x, y in coords:
	    	if smallest_x == None or x < smallest_x:
	    		smallest_x = x
	    	if smallest_y == None or y < smallest_y:
	    		smallest_y = y
	    div_x = 1 - smallest_x
	    div_y = 1 - smallest_y
	    if not (div_x == 0 and div_y == 0):							# needs adjustment
	    	new_coords = []
	    	for x, y in coords:
	    		new_coords.append((x + div_x, y + div_y))
	    	return frozenset(new_coords)
	    else:
	    	return frozenset(coords)

    def get_variants(self):                                         # get all twisted and mirrored variants, including normal version
        variants = []
        for twist in self.__get_twists(self.coords):
            variants.append(self.__normalise(twist))
            for mirror in self.__get_mirrors(twist):
                variants.append(self.__normalise(mirror))
        return frozenset(variants)

    def __get_mirrors(self, coords):                                # get 1., 2. and 3. mirror
        mirror_1 = []                                               # coords on Y
        mirror_2 = []                                               # mirror_1 on X
        mirror_3 = []                                               # coords on X
        for x, y in coords:
            mirror_1.append((-x, y))
            mirror_2.append((-x, -y))
            mirror_3.append((x, -y))
        return frozenset(mirror_1), frozenset(mirror_2), frozenset(mirror_3)

    def __get_twists(self, coords):                                 # get 1., 2. and 3. twist, including base
        twist_1 = []                                                # + 90°
        twist_2 = []                                                # + 180°
        twist_3 = []                                                # - 90°
        for x, y in coords:
            twist_1.append((-y, x))
            twist_2.append((-x, -y))
            twist_3.append((y, -x))
        return frozenset(coords), frozenset(twist_1), frozenset(twist_2), frozenset(twist_3)

    def upgrade(self):                                              # upgrade to n + 1 rominos
        rominos = []
        for free_coord in self.get_free_border_coords():
            romino = self.coords.union((free_coord, ))              # add free coord to self
            if self.__is_romino(romino):
                rominos.append(romino)
        return rominos

    def __get_sourrounding_coords(self, coord):                     # return all coords around this coord
        x, y = coord
        return (x + 1, y + 1), (x + 1, y), (x + 1, y - 1), (x, y + 1), (x, y - 1), (x - 1, y + 1), (x - 1, y), (x - 1, y - 1)

    def get_free_border_coords(self):                               # get coords off free coords next to romino coords
        free_coords = set()                                         # prevent duplicates
        for coord in self.coords:
            for sourrounding_coord in self.__get_sourrounding_coords(coord):
                if sourrounding_coord not in self.coords:
                    free_coords.add(sourrounding_coord)
        return free_coords

    def __is_romino(self, coords):                                  # check for at least 1 existing pair
        for x, y in coords:
            for neighbor_x, neighbor_y in (x + 1, y + 1), (x + 1, y - 1), (x - 1, y + 1), (x - 1, y - 1):   # check all diagonal neighbors
                if (neighbor_x, neighbor_y) in coords:                                                      # exists
                    if (x, neighbor_y) not in coords and (neighbor_x, y) not in coords:			            # if same neighbors are empthy
                        return True                                                                         # at least 1 pair is existing
        return False                                                                                        # no pair was found

    def draw(self):                                                 # draw romino (currently ASCII style)
        grid = {}
        for x, y in self.coords:
            if y not in grid:                                       # expand grid
               grid[y] = []
            if x > len(grid[y]):                                    # expand list
                for i in range(len(grid[y]), x):
                    grid[y].append("_")                             # fill empty space
            grid[y][x - 1] = "#"
        for row in sorted(grid.keys(), reverse=True):               # print every row starting with highest y
            for char in grid[row]:
                print(char, end="")
            print()                                                 # new line


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Program to calculate and display Rominos")
    parser.add_argument("n", type=int, help="Number of Squares in Rominos")
    parser.add_argument("--draw", help="Draw Rominos" , action="store_true")
    parser.add_argument("--show-steps", help="Show number for every generated n", action="store_true")
    args = parser.parse_args()

    rominos = set((Romino(((0, 0), (1, 1))), ))
    if args.n >= 2:
        for i in range(2, args.n):                                  # Determine number recursively
            print("Generating Rominos for n = %s" % (i + 1))
            new_rominos = set()
            for romino in rominos:
                for upgraded_romino in romino.upgrade():
                    new_rominos.add(Romino(upgraded_romino))
            if args.show_steps:
                print("Length: %s" % len(new_rominos))
            rominos = new_rominos
        print("============= Result =============")
        if args.draw:                                               # skip drawing if false
            for romino in rominos:
                print()                                             # add newline for better Overview
                romino.draw()
        print("Rominos: %s" % len(rominos))
    else:
        print("There are no Rominos for n < 2")                     # Rominos have to contain a Romino-pair, wich is consisting of at least 2 squares
