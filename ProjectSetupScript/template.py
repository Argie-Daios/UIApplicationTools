import os

def ReplaceString(string, word, replacement):
    new_string = string.replace(word, replacement)
    return new_string

f = open("project_name.txt", 'r')
project_name = f.read()
scene_name = "DefaultScene"
root_dir_path = "../"
source_folder = root_dir_path + project_name + "/src/"
os.mkdir(source_folder)

appTemplateHeader = open("appTemplate.h", "r")
appTemplateSource = open("appTemplate.cpp", "r")
sceneTemplateHeader = open("sceneTemplate.h", "r")
sceneTemplateSource = open("sceneTemplate.cpp", "r")

final_appTemplateHeader = ReplaceString(appTemplateHeader.read(), "#projectName", project_name)
final_appTemplateHeader = ReplaceString(final_appTemplateHeader, "#sceneName", scene_name)

final_appTemplateSource = ReplaceString(appTemplateSource.read(), "#projectName", project_name)
final_appTemplateSource = ReplaceString(final_appTemplateSource, "#sceneName", scene_name)

final_sceneTemplateHeader = ReplaceString(sceneTemplateHeader.read(), "#projectName", project_name)
final_sceneTemplateHeader = ReplaceString(final_sceneTemplateHeader, "#sceneName", scene_name)

final_sceneTemplateSource = ReplaceString(sceneTemplateSource.read(), "#projectName", project_name)
final_sceneTemplateSource = ReplaceString(final_sceneTemplateSource, "#sceneName", scene_name)

appTemplateHeader.close()
appTemplateSource.close()
sceneTemplateHeader.close()
sceneTemplateSource.close()

appHeaderFile = open(source_folder + project_name + '.h', 'w')
appSourceFile = open(source_folder + project_name + '.cpp', 'w')

sceneHeaderFile = open(source_folder + scene_name + '.h', 'w')
sceneSourceFile = open(source_folder + scene_name + '.cpp', 'w')

appHeaderFile.write(final_appTemplateHeader)
appSourceFile.write(final_appTemplateSource)
sceneHeaderFile.write(final_sceneTemplateHeader)
sceneSourceFile.write(final_sceneTemplateSource)

appHeaderFile.close()
appSourceFile.close()
sceneHeaderFile.close()
sceneSourceFile.close()