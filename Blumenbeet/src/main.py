from Blumenbeet.User_Interface import UserInterface
from Blumenbeet.src.Field import HighPriorityPositionALGO

if __name__ == "__main__":
    i = UserInterface()
    x = i.request_input()
    y = HighPriorityPositionALGO(x)
    i.print(y.field)
