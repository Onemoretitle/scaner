#pragma once
#define MaxText 10000 //максимальная длина текста ИМ
#define MaxLex 20 //максимальная длина лексемы
#define MaxKeyw 8

#define TIf 1
#define TElse 2
#define TInt 3
#define TDouble 4
#define TPublic 5
#define TPrivate 6
#define TReturn 7

#define TIdent 10

#define TConstInt 20
#define TConstStr 21

#define TComma 30
#define TSemicolon 31
#define TOBracket 32
#define TCBracket 33
#define TOBrace 34
#define TCBrace 35
	
#define TPlus 40
#define TMinus 41	
#define TMult 42
#define TDiv 43
#define TMod 44
#define TShiftF 45
#define TShiftB 46
#define TSave 47
#define TLess 48
#define TMore 49
#define TEQLess 50
#define TEQMore 51
#define TEQ 52
#define TNEQ 53

#define TErr 60
#define TEnd 61
#define TDebugInfo 100

#define STEP l[i++] = t[uk++]; pos++;

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

typedef char IM[MaxText]; // текст ИМ
typedef char LEX[MaxLex]; // лексема.
//#define _CRT_SECURE_NO_WARNINGS
