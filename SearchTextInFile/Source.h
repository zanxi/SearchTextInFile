//Daler
#define WIN32_LEAN_AND_MEAN 
#define NOATOM
#define NOCLIPBOARD
#define NOCOMM
#define NOCTLMGR
#define NOCOLOR
#define NODEFERWINDOWPOS
#define NODESKTOP
#define NODRAWTEXT
#define NOEXTAPI
#define NOGDICAPMASKS
#define NOHELP
#define NOICONS
#define NOTIME
#define NOIMM
#define NOKANJI
#define NOKERNEL
#define NOKEYSTATES
#define NOMCX
#define NOMEMMGR
#define NOMENUS
#define NOMETAFILE
#define NOMSG
#define NONCMESSAGES
#define NOPROFILER
#define NORASTEROPS
#define NORESOURCE
#define NOSCROLL
//#define NOSERVICE		/* Windows NT Services */
#define NOSHOWWINDOW
#define NOSOUND
#define NOSYSCOMMANDS
#define NOSYSMETRICS
#define NOSYSPARAMS
#define NOTEXTMETRIC
#define NOVIRTUALKEYCODES
#define NOWH
#define NOWINDOWSTATION
#define NOWINMESSAGES
#define NOWINOFFSETS
#define NOWINSTYLES
#define OEMRESOURCE
#pragma warning(disable : 4996)

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <io.h>
#include <WinSock2.h>

#if !defined(_Wp64)
#define DWORD_PTR DWORD
#define LONG_PTR LONG
#define INT_PTR INT
#endif


WORD WINAPI FindString(LPTSTR); //prototype for FindString

char *characters; //my dynamic array

HANDLE *handles;

//My main

int _tmain2(int argc, LPTSTR argv[])
{

	//Reading the input

	HANDLE STDInput;

	STDInput = GetStdHandle(STD_INPUT_HANDLE);

	LARGE_INTEGER FileSize;

	GetFileSizeEx(STDInput, &FileSize); 

	char data;

	DWORD BIn, Bout;

	characters = malloc(FileSize.QuadPart); //giving memory

	int numberOfElements = FileSize.QuadPart; //number of the chars (including spaces)

	ReadFile(STDInput, characters, numberOfElements, &BIn, NULL);


	
	//Starting up the thread

	int numberOfHandles = argc - 1;

	handles = malloc(numberOfHandles*4);


	for (int i = 1; i <= numberOfHandles; i++) {

		handles[i-1] = (HANDLE)_beginthreadex(NULL, 0, FindString, argv[i], 0, NULL);


		if (argv[i] == NULL) {

			printf("Could not start up thread!");

		}

	}

	for (int i = 1; i <= numberOfHandles; i++) {

	WaitForSingleObject(handles[i - 1], INFINITE);

	}

	system("pause");

	return 0;
}



WORD WINAPI FindString(LPTSTR WhatToSearch)
{

	HANDLE STDInput;  //I know I am wasting a little memory here by declaring all these again, but GetStdHandle is not working when I declare it globally 

	STDInput = GetStdHandle(STD_INPUT_HANDLE);

	LARGE_INTEGER FileSize;

	GetFileSizeEx(STDInput, &FileSize);



	int temp = strlen(WhatToSearch);

	srand(time(NULL));


	int Galaindex = 0;
	int Mystrindex = 0;
	int kig = 0;
	
	int sizeofstring = strlen(WhatToSearch);

	while (Galaindex < FileSize.QuadPart) { //186 must be changed to smt dynamic

		if (characters[Galaindex] == WhatToSearch[Mystrindex]) {
			Galaindex++;
			Mystrindex++;

			if (Mystrindex == sizeofstring) {
				kig++;
				//printf("%d",kig);
				Mystrindex = 0;
			}

		}
		else {

			if (Mystrindex > 1) {
				Mystrindex = 0;
			}
			else {
				Galaindex++;
				Mystrindex = 0;
			}

		}
		
	}

	printf("%d %s \n", kig, WhatToSearch);
}
