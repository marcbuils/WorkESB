# WorkESB

WorkESB is an  Entreprise Services Bus for Javascript. 

The team leader is Marc Buils (http://www.marcbuils.fr), HTML5 front en and middleware engineer in freelance.

This is a fork of M2Bench, a project maked by a R&T team of MATIS Group (http://www.matis-group.com) and provided under Lesser GPL license in June 2012.

## Information
Recent WebBrowser is Required

Tested on Firefox 15, Chrome 22, Opera 12 and Internet Explorer 10

For Opera: Enable Websockets via opera:config#UserPrefs|EnableWebSockets

## Compilation

### Problems known
- Compilation error with Boost 1.51.0 on Windows 8

### Windows
* Download WorkESB sources: git clone https://github.com/marcbuils/WorkESB.git
* Download and install Visual C++ 2010 express (http://msdn.microsoft.com/fr-fr/gg699327)
* Download the required external libraries (http://goo.gl/J8hOU) and extract the archive on the following directory: [WorkESB_path]/build/.
* Compil WorkESB sources :
-- Open a Visual Studio 2010 console
-- Open build directory: cd [WorkESB_path]/build/
-- Execute "environment.bat": environment.bat
-- Execute "Compil_full.bat": compil_full.bat
-- Open [WorkESB_path]/build/sequencer folder
-- Execute startesb_dev.bat
-- Open your favorite HTML5 browser on http://localhost:8080/admin/ or http://localhost:8080/demo/

