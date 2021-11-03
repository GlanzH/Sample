#pragma once
#include "Base/pch.h"
#include <string>
#include <codecvt>

//@fn 文字列のPath変換
//@param (path) 変換する文字列 
static ::std::wstring ConvertStringFilePath(std::string pathname)
{
	return std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes(pathname);
}
//@fn 文字列をファイル読み込みに使えるように変換
//@param (path) 変換する文字列 
static LPCWSTR ConvertStringFileName(std::string filename)
{
	static ::std::wstring path;
	path = ConvertStringFilePath(filename);
	return path.c_str();
}
