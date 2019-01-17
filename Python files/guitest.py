from tkinter.ttk import *
from tkinter import *

from threading import Thread
import serial
import time
import collections
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
import tkinter as Tk
from tkinter.ttk import Frame
import struct





class serialPlot():
    def __init__(self, serialPort = 'COM23', serialBaud = 38400, plotLength = 100, dataNumBytes = 2):
       # print(h.numero)
        self.port = serialPort
        self.baud = serialBaud
        self.plotMaxLength = plotLength
        self.dataNumBytes = dataNumBytes
        self.rawData = bytearray(dataNumBytes)
        self.data = collections.deque([0] * plotLength, maxlen=plotLength)
        self.isRun = True
        self.isReceiving = False
        self.thread = None
        self.plotTimer = 0
        self.previousTimer = 0
        self.dtemp=0
        self.dsp=0
        self.dpulse=0
        self.decg=0
        self.demg=0
        self.dgsr=0
        # self.csvData = []

        print('Trying to connect to: ' + str(serialPort) + ' at ' + str(serialBaud) + ' BAUD.')
        try:
            self.serialConnection = serial.Serial(serialPort, serialBaud, timeout=4)
            print('Connected to ' + str(serialPort) + ' at ' + str(serialBaud) + ' BAUD.')
        except:
            print("Failed to connect with " + str(serialPort) + ' at ' + str(serialBaud) + ' BAUD.')

    def readSerialStart(self):

        if self.thread == None:
            self.thread = Thread(target=self.backgroundThread)
            self.thread.start()
            # Block till we start receiving values
            while self.isReceiving != True:
                time.sleep(0.1)

    def getSerialData(self, frame, lines, lineValueText, lineLabel, timeText):
        currentTimer = time.clock()
        self.plotTimer = int((currentTimer - self.previousTimer) * 1000)     # the first reading will be erroneous
        self.previousTimer = currentTimer
        timeText.set_text('Plot Interval = ' + str(self.plotTimer) + 'ms')
        hola=self.rawData.decode()
        #print("raw data : ")
        #print(self.rawData)
        #print("value : ")
        #print(hola[25])
        #ndato=hola[1:5]
        #print(ndato)
        self.diferenciar(hola)
        value =1.00#struct.unpack('f',hola )    # use 'h' for a 2 byte integer
        self.data.append(value)    # we get the latest data point and append it to our array
        lines.set_data(range(self.plotMaxLength), self.data)
        lineValueText.set_text('[' + lineLabel[0] + '] = ' + str(value))
        h.tempv["text"]=str(self.dtemp)
        h.pulsov["text"]=str(self.dpulse)
        h.oconv["text"]=str(self.dsp)
        #sos=float(value)

        # self.csvData.append(self.data[-1])

    def diferenciar(self,dato):
        #ndato=dato[1:5]
        if dato[0] == "a":
            self.dtemp=float(dato[1:5])
            print("a")
        if dato[5] == "b":
            self.dsp=float(dato[6:10])
            print("b")
        if dato[10] == "c":
            self.dpulse=float(dato[11:15])
            print("c")
        if dato[15] == "d":
            self.decg=float(dato[16:20])
            print("d")
        if dato[20] == "e":
            self.demg=float(dato[21:25])
            print("e")
        if dato[25] == "f":
           self.dgsr=float(dato[26:30])
           print("f")




    def backgroundThread(self):    # retrieve data
        #print("value : ")
        time.sleep(1.0)  # give some buffer time for retrieving data
        self.serialConnection.reset_input_buffer()
        while (self.isRun):

            self.serialConnection.readinto(self.rawData)
            self.isReceiving = True
            #print(self.rawData)
            #print(self.rawData)

    def close(self):
        self.isRun = False
        self.thread.join()
        self.serialConnection.close()
        print('Disconnected...')
        # df = pd.DataFrame(self.csvData)
        # df.to_csv('/home/rikisenia/Desktop/data.csv')



class Window(Frame):
    def __init__(self, figure, master,prueba):
        Frame.__init__(self, master)
        #Tk.config(self,background='black')
        self.s=prueba
        self.numero=0
        self.pack()
        self.createWidgets()
        self.entry = None
        self.setPoint = None
        self.master = master  # a reference to the master window
        # self.serialReference = SerialReference      # keep a reference to our serial connection so that we can use it for bi-directional communicate from this class
        self.master.bind("<Escape>", exit)
        w, h = self.master.winfo_screenwidth(), self.master.winfo_screenheight()
        # use the next line if you also want to get rid of the titlebar
        self.master.overrideredirect(1)
        self.master.geometry("%dx%d+0+0" % (w, h))
        self.initWindow(figure)  # initialize the window with our settings

    def initWindow(self, figure):
        self.master.title("Real Time Plot")
        canvas = FigureCanvasTkAgg(figure, master=self.master)
        toolbar = NavigationToolbar2TkAgg(canvas, self.master)
        canvas.get_tk_widget().place( relx=0.35, rely=0.55, anchor=CENTER)


    def exit(self,event):
        self.s.close()
        root.quit()



    def sumarnumero(self):
        self.numero=self.numero+1
        self.pulsov["text"]=str(self.numero)


    def createWidgets(self):
        but1font = ('Helvetica', 10, 'bold')
        self.ecg = Tk.Button(self.master)
        self.ecg["text"] = "ECG"
        self.ecg["bg"] = "white"
        self.ecg["height"] = 8
        self.ecg["width"] = 15
        self.ecg["fg"] = "black"
        self.ecg["font"] = but1font
        self.ecg["command"] = self.sumarnumero
        self.ecg.place( relx=0.82, rely=0.7, anchor=CENTER)

        self.emg = Tk.Button(self.master)
        self.emg["text"] = "EMG"
        self.emg["bg"] = "white"
        self.emg["height"] = 8
        self.emg["width"] = 15
        self.emg["fg"] = "black"
        self.emg["font"] = but1font
        self.emg.place(relx=0.87, rely=0.7, anchor=CENTER)

        self.gsr = Tk.Button(self.master)
        self.gsr["text"] = "GSR"
        self.gsr["bg"] = "white"
        self.gsr["height"] = 8
        self.gsr["width"] = 15
        self.gsr["fg"] = "black"
        self.gsr["font"] = but1font
        self.gsr.place(relx=0.92, rely=0.7, anchor=CENTER)

        self.salir = Tk.Button(self.master)
        self.salir["text"] = "X"
        self.salir["bg"] = "white"
        self.salir["height"] = 2
        self.salir["width"] = 3
        self.salir["fg"] = "black"
        self.salir["font"] = but1font
        self.salir["command"] =self.exit(self)
        self.salir.place(relx=0.99, rely=0.01, anchor=CENTER)

        #var1 = StringVar()
        labelfont=('Helvetica',60,'bold')
        hola = Label(self.master, bg='black', fg='white', font=labelfont ,text="B-learning Tools", pady=5,padx=5, relief=FLAT)
        # hola.config(bg='white')
        #hola.in(INSERT, "HELLOOOOOO")
        #var1.set("Question")
        hola.place(relx=0.5, rely=0.1, anchor=CENTER)

        labelfont1 = ('Helvetica', 40, 'bold')
        pulso = Label(self.master, bg='black', fg='white', font=labelfont1, text="PRbpm♥", pady=5, padx=5,relief=FLAT)
        pulso.place(relx=0.82, rely=0.25, anchor=CENTER)

        lf1 = ('Helvetica', 40, 'bold')
        self.pulsov = Label(self.master, bg='black', fg='white', font=lf1, text=str(self.numero), pady=5, padx=5,relief=FLAT)
        self.pulsov.place(relx=0.92, rely=0.25, anchor=CENTER)

        labelfont2 = ('Helvetica', 40, 'bold')
        ocon = Label(self.master, bg='black', fg='white', font=labelfont2, text="%SpO2", pady=5, padx=5,relief=FLAT)
        ocon.place(relx=0.82, rely=0.35, anchor=CENTER)

        lf2 = ('Helvetica', 40, 'bold')
        self.oconv = Label(self.master, bg='black', fg='white', font=lf2, text="####", pady=5, padx=5,relief=FLAT)
        self.oconv.place(relx=0.92, rely=0.35, anchor=CENTER)

        labelfont3 = ('Helvetica', 40, 'bold')
        signs = Label(self.master, bg='black', fg='white', font=labelfont3, text="View Signals", pady=5, padx=5,relief=FLAT)
        signs.place(relx=0.87, rely=0.55, anchor=CENTER)

        temp = Label(self.master, bg='black', fg='white', font=labelfont3, text="Temp °:", pady=5, padx=5,relief=FLAT)
        temp.place(relx=0.82, rely=0.45, anchor=CENTER)

        lf3 = ('Helvetica', 40, 'bold')
        self.tempv = Label(self.master, bg='black', fg='white', font=lf3, text="#####", pady=5, padx=5,relief=FLAT)
        self.tempv.place(relx=0.92, rely=0.45, anchor=CENTER)


        # self.hi_there.pack({"side": "top"})
        # self.hi_there.grid(row=4, column=8)
        #self.QUIT.place(relx=1, rely=0)

    def say_hi(self):
        print("hi there, everyone!")


def main():


    fig.patch.set_facecolor('black')

    pltInterval = 50  # Period at which the plot animation updates [ms]
    xmin = 0
    xmax = 100
    ymin = -(1)
    ymax = 1
    ax = plt.axes(xlim=(xmin, xmax), ylim=(float(ymin - (ymax - ymin) / 10), float(ymax + (ymax - ymin) / 10)))

    ax.set_facecolor((0.129, 0.105, 0.2))
    ax.spines['bottom'].set_color('white')
    ax.spines['top'].set_color('white')
    ax.spines['left'].set_color('white')
    ax.spines['right'].set_color('white')
    ax.tick_params(axis='x',colors='white')
    ax.tick_params(axis='y', colors='white')

    ax.set_title('e-HEALTH Monitor', color="white",fontsize=18)
    ax.set_xlabel("Time", color="white",fontsize=18)
    ax.set_ylabel("Output Value", color="white",fontsize=18)


    lineLabel = ['X', 'Y', 'Z']
    style = ['w-', 'c-', 'b-']  # linestyles for the different plots

    timeText = ax.text(0.50, 0.95, '', transform=ax.transAxes)
    lines = ax.plot([], [], label=lineLabel)[0]
    lineValueText = ax.text(0.50, 0.90, '', transform=ax.transAxes)
    #s.getSerialData(root,lines,lineValueText,lineLabel,timeText)
    #lines.append(ax.plot([], [], style[0], label=lineLabel[0])[0])
    #lineValueText.append(ax.text(0.70, 0.90 - 1 * 0.05, '', transform=ax.transAxes))

    anim = animation.FuncAnimation(fig, s.getSerialData, fargs=(lines, lineValueText, lineLabel, timeText),interval=pltInterval)  # fargs has to be a tuple

    root.mainloop()

    s.close()

if __name__ == '__main__':
    portName = 'COM23'     # for windows users
    baudRate = 38400
    maxPlotLength = 100
    dataNumBytes = 30       # number of bytes of 1 data point
    root = Tk.Tk()
    root.config(background='black')
    fig = plt.figure(figsize=(20, 12))
    s = serialPlot(portName, baudRate, maxPlotLength, dataNumBytes)
    s.readSerialStart()
    h = Window(fig, root,s)

    main()
