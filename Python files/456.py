from tkinter import *  # Use this if use python 3.xx
import tkinter as tk
#from Tkinter import *   # Use this if use python 2.xx
root=Tk()
a = tk.Button(root,text="Center Button")
b = tk.Button(root,text="Top Left Button")
c = tk.Button(root,text="Bottom Right Button")
var1 = StringVar()

label = Label(root,textvariable=var1, padx=10)
var1.set("Question")
label.place(relx=0.5, rely=0.5, anchor=CENTER)


a.place(relx=1, rely=1, anchor=CENTER)
b.place(relx=0, rely=0, anchor=NW)
c.place(relx=0, rely=0, anchor=SE)
tk.mainloop()