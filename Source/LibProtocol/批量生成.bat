@echo off


echo ��ʼ����
CALL protoc.exe  itemslots.proto --cpp_out=.
CALL protoc.exe  character.proto --cpp_out=.
CALL protoc.exe  sorlists.proto --cpp_out=.
CALL protoc.exe  chatmsg.proto --cpp_out=.

echo �����ļ����
pause
