#pragma once
#include "Base/pch.h"
#include <string>
#include <codecvt>

//@fn �������Path�ϊ�
//@param (path) �ϊ����镶���� 
static ::std::wstring ConvertStringFilePath(std::string pathname)
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(pathname);
}
//@fn ��������t�@�C���ǂݍ��݂Ɏg����悤�ɕϊ�
//@param (path) �ϊ����镶���� 
static LPCWSTR ConvertStringFileName(std::string filename)
{
	static ::std::wstring path;
	path = ConvertStringFilePath(filename);
	return path.c_str();
}
