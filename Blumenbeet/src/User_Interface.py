from typing import List
from Blumenbeet.src.Base_Classes import colorsint2str, colorsstr2int, User_Input, color_translate
from Blumenbeet.src.Field import Field
import urllib.request


class UserInterface:
    def __validate_is_int(self, string: str) -> bool:
        if string.isdigit() and string.isalnum():
            return True
        return False

    def __validate_colour(self, string: str) -> bool:
        return string in colorsint2str.values()

    def check_if_right_range(self, integer: str) -> bool:
        if self.__validate_is_int(integer):
            return int(integer) > 0 and int(integer) <= 3
        return False

    def __validate_add_color(self, integer: str, size: int) -> bool:
        if self.__validate_is_int(integer):
            return (7 - size) >= int(integer)
        return False

    def get_content(self, num):
        user_input: User_Input = User_Input()
        content: str = urllib.request.urlopen(
            "https://bwinf.de/fileadmin/user_upload/BwInf/2019/38/1._Runde/Material/A1/blumen" + num + ".txt"
        ).read().decode("utf-8").split("\n")[0:-1]
        raw_colors: List[str] = []
        amount_colors: int = int(content[0])
        amount_wished: int = int(content[1])

        for x in content[2:]:
            c1: str = x.split(" ")[0]
            c2: str = x.split(" ")[1]
            weight: str = x.split(" ")[2]
            if c1 not in raw_colors:
                raw_colors.append(c1)
            if c2 not in raw_colors:
                raw_colors.append(c2)

            # Have to use color_translate becouse the BWINF Webpage used german
            user_input.preferences.append((color_translate[c1], color_translate[c2], int(weight)))

        user_input.colors_count = amount_colors - len(raw_colors)
        user_input.german_makec(raw_colors)

        return user_input

    def request_input(self) -> User_Input:

        user_input: User_Input = User_Input()

        raw_colors: List[str] = []

        print("Do you want to run one of the Examples from the BWINF Webpage [y]")

        x: str = input(">>>")

        if x == "y" or x == "Y" or x == "yes" or x == "Yes":
            print("Which number no you wanna test ?")
            x = input(">>")
            return self.get_content(x)
        else:
            print(
                "Now your color combination preferences just write the two colors you like and add a weight (1-3) that tells how strongly you like this combination"
            )

            print("Just press ENTER and leave the input field empty when you done")

            i: int = 1

            while True:
                print("Your", i, "Preference")
                c1: str = input("first colour >>>").rstrip()
                if c1 == "":
                    break

                c2: str = input("second colour >>>").rstrip()
                if c2 == "":
                    break

                if not self.__validate_colour(c1) or not self.__validate_colour(c2):
                    print("You colours are invalid write them again")
                    continue

                else:

                    if c1 not in raw_colors:
                        raw_colors.append(c1)
                    if c2 not in raw_colors:
                        raw_colors.append(c2)

                    print("Your weight ranging from 1 too 3")

                    xinput: str = input(">>>").rstrip()
                    while not self.check_if_right_range(xinput):
                        xinput = input(">>>").rstrip()

                    weight: int = int(xinput)

                    user_input.preferences.append((colorsstr2int[c1], colorsstr2int[c2], weight))

            print("Do you want additional colors ?")

            xinput: str = input(">>>").rstrip()
            while not self.__validate_add_color(xinput, len(raw_colors)):
                xinput = input(">>>").rstrip()

            user_input.colors_count = int(xinput)
            user_input.makec(raw_colors)

            return user_input

    def print(self, field: Field) -> None:

        print("\n" * 2 + "RESULT:")

        print(" " * 10, colorsint2str[field.config[0]][0:2])
        print(" " * 8, colorsint2str[field.config[1]][0:2], " ", colorsint2str[field.config[2]][0:2])
        print(
            " " * 6,
            colorsint2str[field.config[3]][0:2],
            " ",
            colorsint2str[field.config[4]][0:2],
            " ",
            colorsint2str[field.config[5]][0:2],
        )
        print(" " * 8, colorsint2str[field.config[6]][0:2], " ", colorsint2str[field.config[7]][0:2])
        print(" " * 10, colorsint2str[field.config[8]][0:2])
        print("\nThe Resulting Rating:", field.calculate_rating())
