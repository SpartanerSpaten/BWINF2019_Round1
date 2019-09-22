from typing import Tuple, Dict, List
from Blumenbeet.src.Base_Classes import User_Input
import random


class PlaceHolder:

    connected_to: list = []


class Field:

    config: List[int] = [-1] * 9

    # Sind wie viel daneben liegende (angrenzende) Pflanzen es gibt
    pairs_value: Tuple[(int,) * 9] = (2, 4, 4, 3, 6, 3, 4, 4, 2)

    neighbors: List[tuple] = [
        (1, 2),
        (0, 2, 3, 4),
        (0, 1, 4, 5),
        (1, 4, 6),
        (1, 2, 3, 5, 6, 7),
        (2, 4, 7),
        (3, 4, 7, 8),
        (5, 4, 6, 8),
        (6, 7),
    ]

    @staticmethod
    def get(pref: Dict[Tuple[int, int], int], search: Tuple[int, int]) -> int:
        if search in pref.keys():
            return pref[search]
        else:
            if (search[1], search[0]) in pref.keys():
                return pref[(search[1], search[0])]
            else:
                return 0

    def __getitem__(self, item):
        return self.config[item]

    def advanced_parsing(self, x: list) -> list:
        return_value: List[int] = []
        for y in x:
            return_value.append(self[y])
        return return_value

    def calculate_rating(self) -> int:

        rating: int = 0

        pref = self.prepared

        rating += self.get(pref, (self.config[1], self.config[0]))
        rating += self.get(pref, (self.config[2], self.config[0]))

        rating += self.get(pref, (self.config[2], self.config[1]))

        rating += self.get(pref, (self.config[1], self.config[3]))
        rating += self.get(pref, (self.config[1], self.config[4]))

        rating += self.get(pref, (self.config[2], self.config[4]))
        rating += self.get(pref, (self.config[2], self.config[5]))

        rating *= 2  # Weil gespiegelt

        rating += self.get(pref, (self.config[3], self.config[4]))
        rating += self.get(pref, (self.config[5], self.config[4]))

        return rating

    def prepare_data(self, pref: List[Tuple[int, int, int]]) -> None:
        return_value: Dict[Tuple[int, int], int] = {}

        for element in pref:
            return_value.update({(element[0], element[1]): element[2]})

        self.prepared = return_value


def Value(Field):
    def __init__():
        pass


class HighPriorityPositionALGO:
    def __init__(self, user_input: User_Input):

        self.field = Field()
        self.user_input = user_input
        self.field.prepare_data(self.user_input.preferences)

        self.__calcualate_value()
        self.__detect_the_two_colors()
        self.generate_random_colors()
        self.__placing()

    def query_highest_syn(self, color: list, already_used: list, possible_colors: list) -> int:
        ratings: list = [0] * 7

        for x in possible_colors:
            if x in self.user_input.used_colors and x not in already_used:
                for c in color:
                    ratings[x] += Field.get(self.field.prepared, (c, x))

        if ratings == [0] * 7:
            i = random.choice(possible_colors)
        else:
            i = ratings.index(max(ratings))
        return i

    def generate_random_colors(self):
        self.additional_random: List[int] = []
        self.final_colors: List[int] = self.user_input.used_colors
        if self.user_input.colors_count > 0:
            for x in range(self.user_input.colors_count):
                ran: int = random.choice(self.user_input.open_colors)
                del self.user_input.open_colors[self.user_input.open_colors.index(ran)]
                self.additional_random.append(ran)

    def __calcualate_value(self):

        self.colour_values: List[int] = [0] * 7

        # Element
        # 0 First Colour
        # 1 Second Colour
        # 2 Weight

        for element in self.user_input.preferences:

            self.colour_values[element[0]] += element[2] ** 2 + 1
            self.colour_values[element[1]] += element[2] ** 2 + 1

        return

    def __detect_the_two_colors(self):
        if self.colour_values == [0] * 7:
            self.cmax1 = random.randint(0, 4)
            self.cmax2 = random.randint(4, 7)
            self.user_input.used_colors.append(self.cmax1)
            self.user_input.used_colors.append(self.cmax2)
        else:
            self.cmax1 = self.colour_values.index(max(self.colour_values))

            temp = self.colour_values.copy()
            del temp[self.cmax1]
            # temp.remove(self.cmax1)
            self.cmax2 = self.colour_values.index(max(temp))

            return

    def __place_spare(self, spare: int):

        if spare >= 1:
            self.field.config[0] = self.cmax1
        if spare >= 2:
            self.field.config[2] = self.cmax2
        if spare >= 3:
            self.field.config[8] = self.cmax1
        if spare >= 4:
            self.field.config[6] = self.cmax2
        if spare >= 5:
            self.field.config[3] = self.cmax2
        if spare >= 6:
            self.field.config[5] = self.cmax2

        return [self.cmax1, self.cmax2]

    def __placing(self):

        already_used: List[int] = []
        spare: int = self.user_input.spare

        self.field.config[4] = self.cmax1  # Native
        self.field.config[1] = self.cmax2  # Artifical
        self.field.config[7] = self.cmax2  # Artifical

        already_used += self.__place_spare(spare)
        used_cols = self.user_input.used_colors
        del used_cols[used_cols.index(self.cmax1)]
        del used_cols[used_cols.index(self.cmax2)]

        possible_colors: List[int] = self.additional_random
        possible_colors += used_cols

        # already_used.append(self.cmax1)
        i: int = 0
        for count, connections in enumerate(self.field.neighbors):
            if self.field.config[count] == -1:

                sorrounding_colors = self.field.advanced_parsing(list(self.field.neighbors[count]))

                best_color: int = self.query_highest_syn(sorrounding_colors, already_used, possible_colors)

                self.field.config[count] = best_color

                already_used.append(best_color)
                del possible_colors[possible_colors.index(best_color)]

                i += 1
