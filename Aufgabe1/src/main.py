from User_Interface import UserInterface
from Field import HighPriorityPositionALGO

if __name__ == "__main__":
    i: UserInterface = UserInterface()
    x = i.request_input()
    y: HighPriorityPositionALGO = HighPriorityPositionALGO(x)
    i.print(y.field)
