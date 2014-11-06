:: this is to get the code coverage results for photoshop
@echo off
set LOGDIR=%EXALGO_OUTPUT_FOLDER%
set DREXPORT=%DYNAMORIO_HOME%\exports
set PHOTOSHOP32="C:\Program Files (x86)\Adobe\Adobe Photoshop CS6\Photoshop.exe"
set PHOTOSHOP64="C:\Program Files\Adobe\Adobe Photoshop CS6 (64 Bit)\Photoshop.exe"
set GIMP="C:\Program Files\GIMP 2\bin\gimp-2.8.exe"
set PPT="C:\Program Files (x86)\Microsoft Office\Office15\POWERPNT.EXE"



if "%1"=="m32" (
 if "%2"=="photoshop" (
	%DREXPORT%\bin32\drrun.exe -root %DREXPORT% -t drcov -dump_text -logdir %LOGDIR% -- %PHOTOSHOP32%
 )
 if "%2"=="gimp" (
	%DREXPORT%\bin32\drrun.exe -root %DREXPORT% -t drcov -dump_text -logdir %LOGDIR% -- %GIMP%
 )
 if "%2"=="ppt" (
	echo %PPT%
	%DREXPORT%\bin32\drrun.exe -root %DREXPORT% -t drcov -dump_text -logdir %LOGDIR% -- %PPT%
 )
)

if "%1"=="m64" (
 if "%2"=="photoshop" (
	%DREXPORT%\bin64\drrun.exe -root %DREXPORT% -t drcov -dump_text -logdir %LOGDIR% -- %PHOTOSHOP64%
 )
 if "%2"=="gimp" (
	%DREXPORT%\bin64\drrun.exe -root %DREXPORT% -t drcov -dump_text -logdir %LOGDIR% -- %GIMP%
 )
)



