from typing import List, Tuple, Dict

# b, y, g,o, r, t
colorsint2str: Dict[int, str] = {0: "blue", 1: "yellow", 2: "green", 3: "orange", 4: "rosa", 5: "red", 6: "turquoise"}
colorsstr2int: Dict[str, int] = dict((v, k) for k, v in colorsint2str.items())

color_translate: Dict[str, str] = {"blau": 0, "gelb": 1, "gruen": 2, "orange": 3, "rosa": 4, "rot": 5, "tuerkis": 6}


class User_Input:

    colors_count: int = 0  # Additional Colors

    preferences: List[Tuple[int, int, int]] = []

    used_colors: List[int] = []  # Every Predefined Used Color

    open_colors: List[int] = []  # Inverse of used_colors -> not chossen colors

    def makec(self, colors: List[str]):
        for c in colors:
            self.used_colors.append(colorsstr2int[c])

        self.gen_open()

    def german_makec(self, colors: List[str]):
        for c in colors:
            self.used_colors.append(color_translate[c])

        self.gen_open()

    def gen_open(self):

        for x in range(7):
            if x not in self.used_colors:
                self.open_colors.append(x)

        self.size = len(self.used_colors) + self.colors_count
        self.spare = 7 - self.size + 1

        if self.size > 7:
            raise OverflowError()
