// 2017_GetPE_IMAGE_EXPORT_DIRECTORY.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>


//获取PE文件导出表
//编程思路：
//1、打开文件，获取文件句柄
//2、读取文件到内存缓冲区
//3、获取DOS头结构
//4、获取NT头结构
//5、获取扩展头结构
//6、获取数据目录表
//7、获取导出表
//8、封装相对虚拟地址转换文件偏移地址函数



/////////////////////////////////////////
//          RVA转FOA函数               //
/////////////////////////////////////////
DWORD   RvaToOffset(const void* pFileData, DWORD dwRva)
{

	// 获取DOS头
	IMAGE_DOS_HEADER *pDosHeader = (IMAGE_DOS_HEADER*)pFileData;

	// 获取NT头
	IMAGE_NT_HEADERS *pNtHeader = (IMAGE_NT_HEADERS*)((DWORD)pDosHeader + pDosHeader->e_lfanew);

	// 得到区段个数
	DWORD   dwSectionNumber = pNtHeader->FileHeader.NumberOfSections;

	// 得到区段
	IMAGE_SECTION_HEADER* pSectionHeader = IMAGE_FIRST_SECTION(pNtHeader);

	// 遍历区段表，找到RVA所在的区段
	/*
	* 每个偏移，不管是在文件中，还是在内存中，它们距离区段开始位置的距离
	* 总是相等的。
	* 而且，区段表中，保存着两个开始偏移：
	*  1. 文件中的开始偏移
	*  2. 内存中的开始偏移
	* 具体过程：
	*  找到RVA所在区段， 然后计算出这个RVA到区段在内存中的开始位置的距离。
	*  用这个距离加上区段在文件中的开始位置就得到文件偏移了
	*/

	for (int i = 0; i < dwSectionNumber; ++i) {

		// 区段的起始相对虚拟地址RVA
		DWORD dwSectionBeginRva = pSectionHeader[i].VirtualAddress;

		// 区块的结束相对虚拟地址RVA = 区段的RVA地址 + 文件中的区段对齐大小
		DWORD dwSectionEndRva = pSectionHeader[i].VirtualAddress + pSectionHeader[i].SizeOfRawData;


		// 判断RVA是否在当前的区段中
		if (dwRva >= dwSectionBeginRva
			&& dwRva <= dwSectionEndRva) {

			// 计算出RVA对应的文件偏移
			// 公式：文件偏移  =  RVA - 区段的起始相对虚拟地址RVA + 区段的起始文件偏移FOA
			// 1. 要转换的RVA - 区段的起始相对虚拟地址RVA
			DWORD dwTemp = dwRva - pSectionHeader[i].VirtualAddress;
			// 2. 加上区段的起始文件偏移FOA，dwOffset为FOA
			DWORD dwOffset = dwTemp + pSectionHeader[i].PointerToRawData;
			// 3. 得到文件偏移FOA
			return dwOffset;
		}
	}

	return -1;
}


int main()
{
	// 要解析的PE文件
	//char dllPath[MAX_PATH] = "D:\\PEDemo.dll";
	//char dllPath[MAX_PATH] = "D:\\PEDemofnPEDemoFunB@2fnPEDemoFunA@3.dll";
	char dllPath[MAX_PATH] = "D:\\PEDemofnPEDemoFunB@2NONAME.dll";
	//char dllPath[MAX_PATH] = "D:\\PEDemofnPEDemoFunB@2private.dll";


	// 读取PE文件
	HANDLE hFile = INVALID_HANDLE_VALUE;
	hFile = CreateFileA(dllPath,   //PE文件路径
		GENERIC_READ,              //文件访问的权限，通常用GENERIC_READ, GENERIC_WRITE
		FILE_SHARE_READ,           //打开文件的操作方式
		NULL,                      //安全描述符
		OPEN_EXISTING,             //对存在的文件采用的操作
		FILE_ATTRIBUTE_NORMAL,     //文件或设备属性和标志
		NULL);                     //为创建的文件提供文件属性和扩展属性

	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("文件不存在，或者被占用\n");
		return 0;
	}

	// 获取文件大小
	DWORD dwFileSize = GetFileSize(hFile, NULL);
	// 申请缓冲区保存文件内容
	BYTE* pFileData = new BYTE[dwFileSize];
	DWORD dwRead = 0;
	// 将文件读取到缓冲区
	ReadFile(hFile, pFileData, dwFileSize, &dwRead, NULL);

	// 使用DOS头结构指向缓冲区
	IMAGE_DOS_HEADER* pDosHeader = (IMAGE_DOS_HEADER*)pFileData;

	// 获取IMAGE_NT_HEADERS，NT头
	IMAGE_NT_HEADERS* pNtHeader = (IMAGE_NT_HEADERS*)(pDosHeader->e_lfanew + (DWORD)pFileData);

	// 获取IMAGE_OPTIONAL_HEADER32，扩展头
	IMAGE_OPTIONAL_HEADER* pOptionHeader = (IMAGE_OPTIONAL_HEADER*)&pNtHeader->OptionalHeader;

	// 获取IMAGE_DATA_DIRECTORIES，数据目录表 
	IMAGE_DATA_DIRECTORY* pDataDirectory = pOptionHeader->DataDirectory;

	// 获取IMAGE_DATA_DIRECTORY.Export，数据目录表.导出表
	DWORD dwExportTableRva = pDataDirectory[0].VirtualAddress;

	// RVA转FOA，IMAGE_DATA_DIRECTORY.Export转文件偏移
	DWORD dwExportTableOffset = RvaToOffset(pFileData, dwExportTableRva);

	////////////////////////////////////////////////////////////
	// 获取导出表IMAGE_EXPORT_DIRECTORY结构体文件偏移位置，以下是结构体含义：
	//IMAGE_EXPORT_DIRECTORY{
	//    DWORD   Characteristics;        // 1)  保留，恒为0x00000000
	//    DWORD   TimeDateStamp;          // 2)  时间戳，导出表创建的时间（GMT时间）
	//    WORD MajorVersion;              // 3)  主版本号：导出表的主版本号
	//    WORDMinorVersion;               // 4)  子版本号：导出表的子版本号
	//    DWORD   Name;                   // 5)  (有用)指向模块名称的RVA，指向模块名（导出表所在模块的名称）的ASCII字符的RVA
	//    DWORD   Base;                   // 6)  (有用)导出表用于输出API函数索引值的基数（函数索引值=导出函数索引值-基数）
	//    DWORD   NumberOfFunctions;      // 7)  (有用)EAT 导出地址表中的成员个数
	//    DWORD   NumberOfNames;          // 8)  (有用)ENT 导出名称表中的成员个数
	//    DWORD   AddressOfFunctions;     // 9)  (有用)EAT 函数地址表的相对虚拟地址(RVA),每一个非0的项都对应一个被导出的函数名称或序号
	//    DWORD   AddressOfNames;         // 10) (有用)ENT 函数名称表的相对虚拟地址(RVA)，每一个非0的项都对应一个被导出的函数地址或序号
	//    DWORD  AddressOfNameOrdinals;   // 11) (有用)指向导出函数序列号的数组，导出序号表的相对虚拟地址(RVA)
	//} IMAGE_EXPORT_DIRECTORY, *PIMAGE_EXPORT_DIRECTORY;
	////////////////////////////////////////////////////////////
	IMAGE_EXPORT_DIRECTORY* pExportTable = /*换行*/
		(IMAGE_EXPORT_DIRECTORY*)(dwExportTableOffset + (DWORD)pFileData);

	//输出会用到的值
	printf("IMAGE_EXPORT_DIRECTORY.Name：0x%08X\n", pExportTable->Name);                            // 模块名称
	printf("IMAGE_EXPORT_DIRECTORY.Base：0x%08X\n", pExportTable->Base);                            // 函数索引值的基数
	printf("IMAGE_EXPORT_DIRECTORY.NumberOfFunctions：0x%08X\n", pExportTable->NumberOfFunctions);  // 导出地址表中的成员个数
	printf("IMAGE_EXPORT_DIRECTORY.NumberOfNames：0x%08X\n", pExportTable->NumberOfNames);          // 导出名称表中的成员个数
	printf("IMAGE_EXPORT_DIRECTORY.AddressOfFunctions：0x%08X\n", pExportTable->AddressOfFunctions);// 函数地址表的相对虚拟地址(RVA)
	printf("IMAGE_EXPORT_DIRECTORY.AddressOfNames：0x%08X\n", pExportTable->AddressOfNames);        // 函数名称表的相对虚拟地址(RVA)
	printf("IMAGE_EXPORT_DIRECTORY.AddressOfNameOrdinals：0x%08X\n", pExportTable->AddressOfNameOrdinals); // 指向导出函数序列号的数组


	// IMAGE_EXPORT_DIRECTORY.Name转换为FOA，获取指向导出表文件名的字符串
	DWORD dwNameOffset = RvaToOffset(pFileData, pExportTable->Name);

	// IMAGE_EXPORT_DIRECTORY.Base转换为FOA，获取基数
	DWORD dwBaseOffset = RvaToOffset(pFileData, pExportTable->Base);

	// IMAGE_EXPORT_DIRECTORY.AddressOfFunctions转换为FOA，获取导出函数地址表
	DWORD dwAddressOfFunctionsOffset = RvaToOffset(pFileData, pExportTable->AddressOfFunctions);

	// IMAGE_EXPORT_DIRECTORY.AddressOfNames转换为FOA，获取导出函数名称地址表
	DWORD dwAddressOfNamesOffset = RvaToOffset(pFileData, pExportTable->AddressOfNames);

	// IMAGE_EXPORT_DIRECTORY.AddressOfNameOrdinals转换为FOA，获取导出函数序号表
	DWORD dwAddressOfNameOrdinalsOffset = RvaToOffset(pFileData, pExportTable->AddressOfNameOrdinals);

	//  IMAGE_EXPORT_DIRECTORY.Name 指向导出表Name字段，内容存储的是模块函数名称的ASCII字符
	char* pDllName = (char*)(dwNameOffset + (DWORD)pFileData);
	printf("\nDll_Name: %s\n", pDllName);

	/////////////////////////////////////////
	// 把所有的导出的函数地址打印出来。
	// 并且，如果是以名称导出，则输出该名称
	// 如果是以序号导出，则输出该序号。
	/////////////////////////////////////////

	// IMAGE_EXPORT_DIRECTORY.AddressOfFunctions指向导出函数地址表
	DWORD* pAddressTable = /*换行*/
		(DWORD*)((DWORD)pFileData + dwAddressOfFunctionsOffset);

	// IMAGE_EXPORT_DIRECTORY.AddressOfNameOrdinals指向导出函数序号表
	// WORD* pOrdinalTable =(WORD*)((DWORD)pFileData + RvaToOffset(pFileData, pExportTable->AddressOfNameOrdinals));
	WORD* pOrdinalTable = (WORD*)((DWORD)pFileData + dwAddressOfNameOrdinalsOffset);

	// 导出函数名称，需要再转换一层RVA，才能得到函数名称所在的位置
	DWORD* pNameTable =(DWORD*)((DWORD)pFileData + dwAddressOfNamesOffset);

	// 判断是以序号导出，还是以函数名导出
	BOOL bIndexIsExist = FALSE;

	//////////////////////////////////////////////////////////////////////////////////////
	/// pExportTable->NumberOfFunctions 对应了IMAGE_EXPORT_DIRECTORY.NumberOfFunctions ///
	/// 导出地址表中的成员个数                                                         ///
	//////////////////////////////////////////////////////////////////////////////////////
	for (int i = 0; i < pExportTable->NumberOfFunctions; ++i) {

		// 打印虚序号、导出函数地址表(RVA)
		printf("虚序号[%d] ", i);
		printf("地址(RVA)： %08X", pAddressTable[i]);

		// 判断当前的这个地址是否是以名称方式导出的
		// 判断依据：
		//   序号表保存的是地址表的一个下标，这个下标记录着
		//   地址表中哪个地址是以名称方式导出的。
		//   如果当前的这个下标保存在序号表中，则说明这个地址
		//   是一个名称方式导出，如果这个下标在序号表中不存在，
		//   则说明，这个地址不是一个名称方式导出，而是以序号进行导出
		bIndexIsExist = FALSE;


		// 以导出名称导出的函数个数的数量循环
		int nNameIndex = 0;
		for (; nNameIndex < pExportTable->NumberOfNames; ++nNameIndex) {

			// 判断地址表的下标是否存在于序号表中
			if (i == pOrdinalTable[nNameIndex]) {
				bIndexIsExist = TRUE;
				break;
			}
		}

		// 判断如果bIndexIsExist为真就是函数名导出，否则以函数序号导出。
		// 函数名要多转换一层RVA
		if (bIndexIsExist == TRUE) {

			// 得到名称表中的RVA
			DWORD dwNameRva = pNameTable[nNameIndex];

			// 将名称Rva转换成存有真实函数名称的文件偏移
			char* pFunName =
				(char*)((DWORD)pFileData + RvaToOffset(pFileData, dwNameRva));

			printf(" 函数名:【%s】\t", pFunName);
			// i ： 是地址表中的索引号，也就是一个虚序号
			// 真正的序号 = 虚序号 + 序号基数
			printf(" 序号:【%d】 ", i + pExportTable->Base);
		}
		// 当没有导出函数名称，则是以序号进行导出使用
		if (bIndexIsExist == FALSE)
		{

			// 判断地址表当前索引到的袁术是否保存着地址
			if (pAddressTable[i] != 0) {

				printf(" 函数名:【-】\t");
				// i ： 是地址表中的索引号，也就是一个虚序号
				// 真正的序号 = 虚序号 + 序号基数
				printf(" 序号:【%d】", i + pExportTable->Base);
			}
		}

		printf("\n");
	}

	system("pause");
	return 0;
}