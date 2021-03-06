#!/usr/bin/python3
import argparse
import tkinter
import math


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
        smallest_x = None                                           # to support set which has no indexing
        smallest_y = None
        for x, y in coords:                                         # get smallest x and y
            if smallest_x == None or x < smallest_x:
                smallest_x = x
            if smallest_y == None or y < smallest_y:
                smallest_y = y
        div_x = 1 - smallest_x
        div_y = 1 - smallest_y
        if not (div_x == 0 and div_y == 0):							# needs adjustment
            new_coords = frozenset((x + div_x, y + div_y) for x, y in coords)   # adjust every coord
            return new_coords
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
            if self.__is_romino(romino):                            # check if new object is still a Romino
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

    def draw(self, canvas, pre_x, pre_y):                           # draw romino on Canvas, 0|0 at pre_x|pre_y
        for x, y in self.coords:                                    # because of axis position in tkinter, romino will be mirrored
            canvas.create_rectangle(x*10 + pre_x, y*10 + pre_y, x*10 + pre_x + 10, y*10 + pre_y + 10, fill="red") # draw 10x10 square


def get_int(question):												# get integer from user
    while True:
        answer = input(question)
        if answer.isdecimal():
            return int(answer)
        else:														# ask again
            print("Please enter a valid number!")

def get_dimensions(n, romino_count, width, height):                 # claculate Width (is also height) available for each Romino, Rominos per Row, Rows and height of Scrollbar
    r_width = n * 10 + 10                                           # 10 per Square, 10 as border to next Romino
    per_row = int(width / r_width)                                  # using int because Rominos cant be split
    if per_row == 0:                                                # window width too small for one romino
        raise ValueError("Window width is too small, has to be at least %s" % r_width)
    rows = math.ceil(romino_count / per_row)                        # round up if last row cant be filled completely
    return r_width, r_width, per_row, rows, rows * r_width 

def get_window(width, height, scroll_height):                       # get Tk window with vertical Scrollbar
    window = tkinter.Tk()                                           # get window
    window.title("BWINF Rominos")                                   # set name
    frame = tkinter.Frame(window, width=width, height=height)       # frame for canvas
    frame.grid(row=0, column=0)
    canvas = tkinter.Canvas(frame, width=width, height=height, scrollregion=(0, 0, width, scroll_height))   # canvas with scrollregion
    vsbar = tkinter.Scrollbar(frame, orient=tkinter.VERTICAL)
    vsbar.pack(side=tkinter.RIGHT, fill=tkinter.Y)                  # pack to right side
    vsbar.config(command=canvas.yview)                              # connect scrollbar with canvas
    canvas.config(yscrollcommand=vsbar.set)
    canvas.pack(side=tkinter.LEFT, expand=True, fill=tkinter.BOTH)
    return window, canvas

def generate_rominos_recur(n, show_steps=False):					# determine rominos recursively
    if n == 2:														# end condition
        return set((Romino(((0, 0), (1, 1))), ))                    # minimal romino, used for generating n > 2 rominos
    else:
        rominos = generate_rominos_recur(n - 1, show_steps=show_steps)	# upgrade n - 1 rominos to n rominos
        upgraded_rominos = set()
        print("Generating Rominos for n = %s" % (n))
        for romino in rominos:
            for upgraded_romino in romino.upgrade():
                upgraded_rominos.add(Romino(upgraded_romino))
        if show_steps:
            print("Rominos: %s" % len(upgraded_rominos))
        return upgraded_rominos
	
def generate_rominos_iter(n, show_steps=False):						# determine rominos iteratively
    rominos = set((Romino(((0, 0), (1, 1))), ))                     # minimal romino, used for generating n > 2 rominos
    for i in range(2, args.n):
        print("Generating Rominos for n = %s" % (i + 1))
        new_rominos = set()
        for romino in rominos:
            for upgraded_romino in romino.upgrade():
                new_rominos.add(Romino(upgraded_romino))
        if show_steps:                                              # print romino count for current n
            print("Rominos: %s" % len(new_rominos))
        rominos = new_rominos
    return rominos

if __name__ == "__main__":                                          # run programm
    parser = argparse.ArgumentParser(description="Program to calculate and display Rominos")
    parser.add_argument("--n", type=int, help="Number of Squares in Rominos", default=None)
    parser.add_argument("--method", type=str, help="Method for generating Rominos, iter or recur (Default)", default="recur")
    parser.add_argument("--draw", help="Draw Rominos" , action="store_true")
    parser.add_argument("--show-steps", help="Show number for every generated n", action="store_true")
    parser.add_argument("--resolution", type=str, help="Width and Height seperated with an x (default is 1024x768)", default="1024x768")
    args = parser.parse_args()

    if args.n is None:												# ask for it
	    args.n = get_int("Value of n? ")

    if args.n >= 2:
        if args.method == "iter":
            rominos = generate_rominos_iter(args.n, show_steps=args.show_steps)
        elif args.method == "recur":			
            rominos = generate_rominos_recur(args.n, show_steps=args.show_steps)
        else:
            raise ValueError("Unknown Method '%s'" % args.method)
        print("============= Result =============")
        print("Rominos: %s" % len(rominos))

        if args.draw:                                               # skip drawing if false
            width, height = tuple(int(i) for i in args.resolution.split("x"))   # convert to int
            romino_width, romino_height, per_row, rows, scroll_height = get_dimensions(args.n, len(rominos), width, height)
            window, canvas = get_window(width, height, scroll_height)
            current_per_row = 0
            pre_x = 0                                               # to prevent rominos from drawing over each other
            pre_y = 0
            for romino in rominos:
                if current_per_row == per_row:                      # new row
                    pre_y += romino_height
                    current_per_row = 0                             # reset
                    pre_x = 0
                romino.draw(canvas, pre_x, pre_y)
                pre_x += romino_width
                current_per_row += 1  
            window.mainloop()                                       # wait for user to close the window

    else:
        print("There are no Rominos for n < 2")                     # Rominos have to contain a Romino-pair, wich is consisting of at least 2 squares
