// 20180406_bin2text_text2bin.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


/*  IHexCvt - Intel HEX File <=> Binary Converter (C++)
Copyright (C) 2014  Ali Nakisaee

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.


This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.


You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.*/

//Include needed stuff from C++
#include <iostream>
#include <fstream>
#include <string>

//... and also from C
#include <stdio.h>
#include <tchar.h>

//Avoid repeating 'std::':
using namespace std;

//The following function reads a hexadecimal number from a text file.
template <class T>
bool ReadValueFromHex(ifstream& InputFile, T& outCh, unsigned char* ApplyChecksum)
{
	char V, L;
	T X = 0;
	outCh = 0;

	//Get the characters one by one.
	//Remember: These values are big-endian.
	//Remember: Every two hex characters (0-9/A-F) indicate ONE byte.
	for (int i = 0; i < 2 * sizeof(T); i++)
	{
		InputFile.get(V);
		if (InputFile.fail())
			return false;

		X <<= 4;
		if (V >= '0' && V <= '9')
			L = (V - '0');
		else if (V >= 'a' && V <= 'f')
			L = (V - 'a' + 10);
		else if (V >= 'A' && V <= 'F')
			L = (V - 'A' + 10);
		else
			return false;
		X |= L;

		//Apply this character to the checksum
		if (ApplyChecksum && i % 2 == 1) *ApplyChecksum += X & 0xFF;
	}

	//Return...
	outCh = X;
	return true;
}

//The following function writes a hexadecimal number from a text file.
template <class T>
bool WriteHexValue(ofstream& OutFile, T Value, unsigned char* CalcChecksum)
{
	unsigned char V0 = 0;
	char C;

	//Remember: These values are big-endian.
	for (int i = 0; i < sizeof(T); i++)
	{
		//Get byte #i from the value.
		V0 = (Value >> ((sizeof(T) - i - 1) * 8)) & 0xFF;

		//Extract the high nibble (4-bits)
		if ((V0 & 0xF0) <= 0x90)
			C = (V0 >> 4) + '0';
		else
			C = (V0 >> 4) + ('A' - 10);
		OutFile.put(C);

		//Extract the low nibble (4-bits)
		if ((V0 & 0xF) <= 0x9)
			C = (V0 & 0xF) + '0';
		else
			C = (V0 & 0xF) + ('A' - 10);
		OutFile.put(C);

		//Calculate the checksum
		if (CalcChecksum) *CalcChecksum += V0;
	}
	return true;
}

//Skip any incoming whitespaces
void SkipWhitespace(ifstream& InputFile)
{
	for (;;)
	{
		char C;
		InputFile.get(C);
		if (InputFile.eof() || InputFile.fail()) break;
		if (!(C == '\n' || C == '\r' || C == ' ' || C == '\t' || C == '\v'))
		{
			InputFile.putback(C);
			break;
		}
	}
}

//The function responsible for conversion from HEX files to BINary.
void Hex2Bin(const wchar_t* SrcName, const wchar_t* DstName, bool IgnoreChecksum)
{
	ifstream Src(SrcName);
	if (Src.bad())
	{
		cout << "ERROR: Could not open source file." << endl;
		return;
	}

	ofstream Dst(DstName, ios_base::binary);
	if (Dst.bad())
	{
		cout << "ERROR: Could not open destination file." << endl;
		return;
	}

	char Ch;
	int LineIdx = 1;

	unsigned char ByteCount;
	unsigned short AddressLow;
	unsigned short Extra;
	unsigned long ExtraL;
	unsigned long AddressOffset = 0;
	unsigned char RecordType;
	unsigned char Data[255];
	unsigned char CurChecksum;
	unsigned char FileChecksum;
	bool EOFMarker = false;
	bool EOFWarn = false;

	for (;; )
	{
		Src.get(Ch);
		if (Src.eof())
			break;
		if (EOFMarker && !EOFWarn)
		{
			EOFWarn = true;
			cout << "WARNING: (Line " << LineIdx << ") Gone beyond EOF marker." << endl;
		}
		if (Ch != ':') goto genericErr;

		CurChecksum = 0;
		if (!ReadValueFromHex(Src, ByteCount, &CurChecksum)) goto genericErr;
		if (!ReadValueFromHex(Src, AddressLow, &CurChecksum)) goto genericErr;
		if (!ReadValueFromHex(Src, RecordType, &CurChecksum)) goto genericErr;

		switch (RecordType)
		{
		case 0x00: //Data record
			for (int i = 0; i < ByteCount; i++)
				if (!ReadValueFromHex(Src, Data[i], &CurChecksum)) goto genericErr;
			break;
		case 0x01: //End Marker
			if (ByteCount != 0)
			{
				cout << "ERROR: (Line " << LineIdx << ") Invalid EOF Marker" << endl;
				goto onErrExit;
			}
			cout << "EOFMarker: (Line " << LineIdx << ") - Address = " << hex << AddressLow + AddressOffset << dec << endl;
			EOFMarker = true;
			break;
		case 0x02: //Extended Segment Address
			if (ByteCount != 2 || AddressLow != 0)
			{
				cout << "ERROR: (Line " << LineIdx << ") Invalid Extended Segment Address Record" << endl;
				goto onErrExit;
			}
			if (!ReadValueFromHex(Src, Extra, &CurChecksum)) goto genericErr;
			AddressOffset = (unsigned long)Extra << 4;
			break;
		case 0x03: //Start Segment Address
			if (ByteCount != 4 || AddressLow != 0)
			{
				cout << "ERROR: (Line " << LineIdx << ") Invalid Start Segment Address Record" << endl;
				goto onErrExit;
			}
			if (!ReadValueFromHex(Src, ExtraL, &CurChecksum)) goto genericErr;
			cout << "CS:IP = (Line " << LineIdx << ") " << hex << (int)((ExtraL >> 16) & 0xFF) <<
				hex << (int)(ExtraL & 0xFF) << dec << endl;
			break;
		case 0x04: //Extended Linear Address
			if (ByteCount != 2 || AddressLow != 0)
			{
				cout << "ERROR: (Line " << LineIdx << ") Invalid Extended Linear Address Record" << endl;
				goto onErrExit;
			}
			if (!ReadValueFromHex(Src, Extra, &CurChecksum)) goto genericErr;
			AddressOffset = (unsigned long)Extra << 16;
			break;
		case 0x05: //Start Linear Address
			if (ByteCount != 4 || AddressLow != 0)
			{
				cout << "ERROR: (Line " << LineIdx << ") Invalid Start Linear Address Record" << endl;
				goto onErrExit;
			}
			if (!ReadValueFromHex(Src, ExtraL, &CurChecksum)) goto genericErr;
			cout << "EIP = (Line " << LineIdx << ") " << hex << ExtraL << dec << endl;
			break;
		}

		//Verify checksum
		CurChecksum = (~(CurChecksum & 0xFF) + 1) & 0xFF;
		if (!ReadValueFromHex(Src, FileChecksum, NULL)) goto genericErr;
		if (CurChecksum != FileChecksum)
		{
			cout << (IgnoreChecksum ? "WARNING" : "ERROR") << ": Checksum Failure on Line " <<
				LineIdx << " - Computed " << hex << (int)CurChecksum <<
				", File " << hex << (int)FileChecksum << dec << endl;
			if (!IgnoreChecksum) goto onErrExit;
		}

		//Put Data
		if (RecordType == 0x00)
		{
			Dst.seekp(AddressLow + AddressOffset);
			for (int i = 0; i < ByteCount; i++)
			{
				Dst.put(Data[i]);
			}
		}

		//Skip any white space
		SkipWhitespace(Src);

		LineIdx++;
	}

	Dst << flush;
	Dst.close();
	cout << "Done" << endl;

	return;

genericErr:
	cout << "ERROR: (Line " << LineIdx << ") Invalid Source File" << endl;

onErrExit:
	Dst.close();
	Src.close();
	_wremove(DstName);
}

//The function responsible for conversion from BINary files to HEX.
void Bin2Hex(const wchar_t* SrcName, const wchar_t* DstName)
{
	ifstream Src(SrcName, ios_base::binary);
	if (Src.bad())
	{
		cout << "ERROR: Could not open source file." << endl;
		return;
	}

	ofstream Dst(DstName);
	if (Dst.bad())
	{
		cout << "ERROR: Could not open destination file." << endl;
		return;
	}

	const int Packing = 16;
	unsigned long Address = 0;
	char Data[Packing];
	unsigned long nRead;
	unsigned long TotalRead = 0;
	unsigned short AddressLow = 0;
	unsigned short AddressHigh = 0;
	unsigned short AddressHighLast = 0;
	unsigned char Checksum;

	for (;; )
	{   //��ȡ�ļ�
		Src.read(Data, Packing);                        //���ļ��ж�ȡ16���ֽڵ�������
		nRead = (unsigned long)Src.gcount();
		TotalRead += nRead;                             //ͳ���ܹ���Ҫ������ֽ���
		if (nRead == 0) 
			break;

		AddressLow = Address & 0xFFFF;
		AddressHigh = (Address >> 16) & 0xFFFF;
		if (AddressHigh != AddressHighLast)
		{
			//Print New Extended Linear Address
			Dst.put(':');
			Checksum = 0;
			WriteHexValue(Dst, (char)2, &Checksum); //byte count
			WriteHexValue(Dst, (short)0, &Checksum); //address
			WriteHexValue(Dst, (char)4, &Checksum); //field type
			WriteHexValue(Dst, (short)AddressHigh, &Checksum); //'AddressHigh'
			WriteHexValue(Dst, (char)(~Checksum + 1), NULL); //checksum
			Dst << "\n";
			AddressHighLast = AddressHigh;
		}

		//Print Data
		Dst.put(':');
		Checksum = 0;
		WriteHexValue(Dst, (char)nRead, &Checksum); //byte count
		WriteHexValue(Dst, (short)AddressLow, &Checksum); //address
		WriteHexValue(Dst, (char)0, &Checksum); //field type (data)
												//data
		for (unsigned long i = 0; i < nRead; i++)
		{
			WriteHexValue(Dst, (char)Data[i], &Checksum); //data[i]
		}
		WriteHexValue(Dst, (char)(~Checksum + 1), NULL); //checksum
		Dst << "\n";

		Address += nRead;
		if (nRead < Packing) break;
	}

	//Print EOF Marker
	Dst.put(':');
	Checksum = 0;
	WriteHexValue(Dst, (char)0, &Checksum); //byte count
	WriteHexValue(Dst, (short)0, &Checksum); //address
	WriteHexValue(Dst, (char)1, &Checksum); //field type
	WriteHexValue(Dst, (char)(~Checksum + 1), NULL); //checksum
	Dst << "\n";

	cout << "Total Read Bytes : " << TotalRead << endl;

	Dst << flush;
	Dst.close();
	cout << "Done" << endl;

	return;
}

int wmain(int argc, wchar_t* argv[])
{
	argc = 4;
	argv[1] = L"-B";
	argv[2] = L"D:\\20171111-test.exe";
	argv[3] = L"D:\\20171111-test.txt";

	if (argc < 2)
	{
		cout << "IHexCvt - Converts Intel HEX Files into Binary Files and Vice Versa\n"
			"By Ali Nakisaee, released under the GPLv2\n\t(GNU General Public License Version 2)\n\n"
			"Usage: IHexCvt.exe <-H | -B> [-NC] InputFile OutputFile\n"
			"  -H\t\tSpecifies that input file is an Intel HEX file.\n"
			"  -B\t\tSpecifies that input file is a binary file.\n"
			"  -NC\t\tIgnore checksums of input file, used with -H.\n" << endl;
		return 0;
	}

	const wchar_t* pInputFile = nullptr;
	const wchar_t* pOutputFile = nullptr;
	enum WORK_MODE
	{
		WM_HEX2BIN,
		WM_BIN2HEX,
	} Mode;
	bool IgnoreCheckSum = false;
	int PIndex = 1;
	//ѡ��ģʽ
	if (_wcsicmp(argv[PIndex], L"-H") == 0)
		Mode = WM_HEX2BIN;
	else if (_wcsicmp(argv[PIndex], L"-B") == 0)
		Mode = WM_BIN2HEX;
	else
	{
		wcout << L"ERROR: First parameter must be either -H or -B. \"" << argv[PIndex] << L"\" specified." << endl;
		return 1;
	}
	PIndex++;

	if (PIndex < argc && _wcsicmp(argv[PIndex], L"-NC") == 0)
	{
		IgnoreCheckSum = true;
		PIndex++;
	}

	if (PIndex >= argc)
	{
		cout << "ERROR: Too few parameters." << endl;
		return 1;
	}
	pInputFile = argv[PIndex++];
	wcout << ((Mode == WM_HEX2BIN) ? L"hex:" : L"bin:") << pInputFile << endl;

	if (PIndex >= argc)
	{
		cout << "ERROR: Too few parameters." << endl;
		return 1;
	}
	pOutputFile = argv[PIndex++];
	wcout << ((Mode == WM_HEX2BIN) ? L"bin:" : L"hex:") << pOutputFile << endl;

	if (PIndex < argc)
	{
		cout << "ERROR: Too many parameters specified." << endl;
		return 1;
	}

	//--------------------------------------------------------------//
	if (Mode == WM_HEX2BIN)
		Hex2Bin(pInputFile, pOutputFile, IgnoreCheckSum);
	else
		Bin2Hex(pInputFile, pOutputFile);

	return 0;
}

