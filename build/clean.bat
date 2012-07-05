rem make init
msbuild "../WESBMessenger/WESBMessenger/WESBMessenger.sln" /t:Clean /p:Configuration=Release
msbuild "../messenger_gateway_websockets/win32port/win32port.sln" /t:Clean /p:Configuration=Release
msbuild "../messenger/messenger.sln" /t:Clean /p:Configuration=Release
msbuild "../sequencer/sequencer.sln" /t:Clean /p:Configuration=Release
msbuild "../WESBMessenger/WESBMessenger/WESBMessenger.sln" /t:Clean /p:Configuration=Debug
msbuild "../messenger_gateway_websockets/win32port/win32port.sln" /t:Clean /p:Configuration=Debug
msbuild "../messenger/messenger.sln" /t:Clean /p:Configuration=Debug
msbuild "../sequencer/sequencer.sln" /t:Clean /p:Configuration=Debug

RMDIR sequencer /s /q
RMDIR sequencer_debug /s /q
rem make clean
