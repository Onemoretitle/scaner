#pragma once
#ifndef __DIAGRAM
#define __DIAGRAM
#include "scaner.h"
#include "semant.h"
#include "dfs.h"
class TDiagram
{
	private:
		TScaner* sc;
		Tree* Root = nullptr;

	public:
		TDiagram(TScaner* s)
		{
			sc = s;
			Node* b = new Node();
			memcpy(&b->id, &"EMPTY", strlen("EMPTY") + 1); 
			b->data.dataType = TYPE_EMPTYDATA; 
			b->NodeType = TYPE_EMPTYNODE;
			Root = new Tree(NULL, NULL, NULL, b);
			Root->SetCur(Root);
		}
		~TDiagram() {}
		void S(); // программа
		void D(); // операторы и описания
		void F(); // функция
		void AV(); // переменая
		Data ARD(); // + -
		Data FSD(); // * / %
		Data SSD(); // сдвиги
		Data TSD(); // сравнение
		Data FFSD(); // присваивание
		void L(); // оператор if
		void LO(); // операция
		void LD(); // совставной оператор
		void LD(LEX ID); // совставной оператор
};
#endif