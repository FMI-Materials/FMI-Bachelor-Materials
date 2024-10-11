from tkinter import *

# widgets = GUI elements: buttons, textboxes, labels, images
# windows = serves as a container to hold or contain these widgets

window = Tk() # instantiate an instance of a window
window.geometry("1920x1080")
window.title("First GUI Program")

icon = PhotoImage(file='icon.png')
window.iconphoto(True, icon)

# hex color picker on google
window.config(background="#0a2d6e")
# window.config(background="black")

window.mainloop() # place window on computer screen, listen for events