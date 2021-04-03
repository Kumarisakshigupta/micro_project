import sys
import time # Required to use delay functions
import pyautogui
import serial # Serial imported for Serial communication
from PyQt5.QtWidgets import QApplication, QDialog
from GestureControlledMouse import *
class ControllerClass(QDialog):
 def __init__(self):
 super().__init__()
 self.ui = Ui_Dialog()
 self.ui.setupUi(self)
 
self.ui.submitButton.clicked.connect(self.on_submitButton_clicked)
 self.show()
 
 def on_submitButton_clicked(self):
 # self.ui.label1.setText("Welcome: " + 
self.ui.lineEdit.text())
 # Getting Text from text box
 Action1 = (self.ui.Action1.text()).lower()
 Action2 = (self.ui.Action2.text()).lower()
 Action3 = (self.ui.Action3.text()).lower()
 Action4 = (self.ui.Action4.text()).lower()
 Action5 = (self.ui.Action5.text()).lower()
 # Some Preprocessing
 Action1 = Action1.replace(" ", "")
Action2 = Action2.replace(" ", "")
 Action3 = Action3.replace(" ", "")
 Action4 = Action4.replace(" ", "")
 Action5 = Action5.replace(" ", "")
 # Extracting all the keys from the input
 Action1 = Action1.split(',')
 Action2 = Action2.split(',')
 Action3 = Action3.split(',')
 Action4 = Action4.split(',')
 Action5 = Action5.split(',')
 self.perform_action(Action1)
 
 # Performing actions
 try:
 ArduinoSerial = serial.Serial('com4',9600) #Create 
Serial port object called arduinoSerialData 
 time.sleep(2) #wait for 2 seconds for the communication 
to get established 
 except Exception as error:
 print(error)
 return
 while 1: 
 incoming = str (ArduinoSerial.readline()) #read the 
serial data and print it as line 
 print (incoming) 
 if 'Action1' in incoming: 
 self.perform_action(Action1) 
 
 if 'Action2' in incoming: 
 self.perform_action(Action2) 
 
 if 'Action3' in incoming: 
 self.perform_action(Action3) 
 
 if 'Action4' in incoming: 
 self.perform_action(Action4) 
 
 if 'Action5' in incoming: 
 self.perform_action(Action5) 
 if 'Stop' in incoming:
 break
 def perform_action(self, Actions):
 for key in Actions:
 pyautogui.keyDown(key)
 Actions.reverse()
 for key in Actions:
 pyautogui.keyUp(key)
app = QApplication(sys.argv)
widget = ControllerClass()
widget.show()
sys.exit(app.exec())
