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
		void S(); // ���������
		void D(); // ��������� � ��������
		void F(); // �������
		void AV(); // ���������
		Data ARD(); // + -
		Data FSD(); // * / %
		Data SSD(); // ������
		Data TSD(); // ���������
		Data FFSD(); // ������������
		void L(); // �������� if
		void LO(); // ��������
		void LD(); // ���������� ��������
		void LD(LEX ID); // ���������� ��������
};
#endif