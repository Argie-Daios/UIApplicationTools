import tkinter
import customtkinter
import os
import subprocess as sp
import time

# Functions
def OnClickFunction():
    project_name = input_box.get()
    GenerateProjectOnPremake(project_name)
    f = open("project_name.txt", "w")
    f.write(project_name)
    exit(0)

def InsertProjectName(project_name, file_string):
    replaced_string = file_string.replace('#projectName', project_name)
    return replaced_string

def GenerateProjectOnPremake(project_name):
    project_template = open(template_for_project_path, 'r')
    premake_file = open(main_premake_path, 'a')
    file_string = project_template.read()
    final_project_form = InsertProjectName(project_name, file_string)

    premake_file.write('\n\n' + final_project_form)

# Constants
root_path = "../"
main_premake_path = root_path + "premake5.lua"
template_for_project_path = "PremakeTemplate.txt"

# System Settings
customtkinter.set_appearance_mode("System")
customtkinter.set_default_color_theme("blue")

# Window Properties
app = customtkinter.CTk()
app.geometry("720x480")
app.title("UIApplication Project Setup")

# Application Implementation
title = customtkinter.CTkLabel(app, text = "Project Setup", font=("Arial", 70))
title.pack()

label = customtkinter.CTkLabel(app, text = "Project Name", font=("Arial", 30))
label.pack(pady=50)

string = tkinter.StringVar()
input_box = customtkinter.CTkEntry(app, width = 400, height=50, textvariable=string)
input_box.pack()

button = customtkinter.CTkButton(app,text="Create Project" , command = OnClickFunction)
button.pack(pady=30)

# Main Loop
app.mainloop()