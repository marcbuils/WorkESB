@echo off
echo "<<< OpenSplice HDE Release V5.5.1OSS For x86.win32 >>>"
if "%SPLICE_ORB%"=="" set SPLICE_ORB=DDS_OpenFusion_1_6_1
set OSPL_HOME=%~dp0\..\libs\HDE\x86.win32
set OSPL_TARGET=x86.win32
set PATH=%OSPL_HOME%\bin;%OSPL_HOME%\lib;%OSPL_HOME%\examples\lib;%PATH%
set OSPL_TMPL_PATH=%OSPL_HOME%\etc\idlpp
set OSPL_URI="file://%OSPL_HOME%\etc\config\ospl.xml"
set CLASSPATH=%OSPL_HOME%\jar\dcpssaj.jar;%CLASSPATH%
set CLASSPATH=%OSPL_HOME%\jar\dcpscj.jar;%CLASSPATH%
%*
@echo on
ospl start
sequencer
ospl stop