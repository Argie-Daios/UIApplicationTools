@echo off
pushd ..\ProjectSetupScript
python main.py
popd
call WinGenProjects.bat
pushd ..\ProjectSetupScript
python template.py
del project_name.txt
popd
call WinGenProjects.bat
PAUSE