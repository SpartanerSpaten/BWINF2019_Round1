class Romino:
    def __init__(self, coords):
        self.coords = self.__normalise(coords)
        self.variants = self.get_variants()
    
    def __normalise(self, coords):                              # move romino to touch x and y axis
	    smallest_x = None
	    smallest_y = None
	    for x, y in coords:
	    	if smallest_x == None or x < smallest_x:
	    		smallest_x = x
	    	if smallest_y == None or y < smallest_y:
	    		smallest_y = y
	    div_x = 1 - smallest_x
	    div_y = 1 - smallest_y
	    if not (div_x == 0 and div_y == 0):							# need adjustment
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

    def __hash__(self):                                             # with __eq__ for use in set()
        return hash(self.variants)

    def __eq__(self, sample):
        if isinstance(sample, type(self)):
            return self.variants == sample.variants
        else:
            raise NotImplementedError

    def upgrade(self):
        pass

    def draw(self):
        pass
