#include "Diagram.h"


void TDiagram::S()
// 
// S → public class TIdent{<D>}
//
{
	LEX l;
	int t;
	t = sc->scaner(l);
	if ((t != TPublic) && (t != TPrivate))
	{
		sc->PrintError("ожидался модификатор доступа", l);
	}
	for (int i = 0; i < 2; i++) {
		t = sc->scaner(l);
		if (t != TIdent)
		{
			sc->PrintError("ожидался индетификатор", l);
		}
	}
	Tree* newClass = Root->SemSetFunct(l, TYPE_CLASS, sc->GetUK());
	t = sc->scaner(l);
	if (t != TOBrace)
	{
		sc->PrintError("ожидался знак {", l);
	}
	D();
	Root->SetCur(newClass);
	if (Tree::getFlagInter())
		Root->Cur->remRightSubtree();
	t = sc->scaner(l);
	if (t != TCBrace)
	{
		sc->PrintError("ожидался знак }", l);
	}
	Root->Print();
}

void TDiagram::D()
//	
//	D → <D><F> | <D><AV> | ɛ
//
{
	LEX l;
	int t, uk1;
	uk1 = sc->GetUK();
	t = sc->scaner(l);
	sc->PutUK(uk1);
	while (t != TCBrace)
	{
		if ((t == TPublic) || (t == TPrivate))
		{
			F();	//функция или класс
		}
		else if ((t == TInt) || (t == TDouble))
		{
			AV();	//выражение
		}
		else 
		{
			sc->PrintError("Ождиалось описание данных или функций", l);
		}
		uk1 = sc->GetUK();
		t = sc->scaner(l);
		sc->PutUK(uk1);
	}
}

void TDiagram::F()
//
// F →  public int TIdent () {< LD >} | public double TIdent () {< LD >}
//
{
	LEX l;
	int t, tempT;
	t = sc->scaner(l);
	if ((t != TPublic) && (t != TPrivate))
	{
		sc->PrintError("ожидался модификатор доступа", l);
	}
	t = sc->scaner(l);
	if ((t != TInt) && (t != TDouble))
	{
		sc->PrintError("ожидался тип данных", l);
	}
	tempT = t;
	t = sc->scaner(l);
	if (t != TIdent)
	{
		sc->PrintError("ожидался индетификатор", l);
	}
	Tree* newFunc;
	if (_stricmp(l, "init"))
	{
		newFunc = Root->SemSetFunct(l, TYPE_FUNCT, sc->GetUK());
	}
	else 
	{
		newFunc = Root->SemSetFunct(l, TYPE_INITFUNCT, sc->GetUK());
	}
	if (tempT == TInt)
	{
		Root->SemSetType(newFunc, TYPE_INTEGER);
	}
	else
	{
		Root->SemSetType(newFunc, TYPE_DOUBLE);
	}
	t = sc->scaner(l);
	if (t != TOBracket)
	{
		sc->PrintError("ожидался знак (", l);
	}
	t = sc->scaner(l);
	if (t != TCBracket)
	{
		sc->PrintError("ожидался знак )", l);
	}

	t = sc->scaner(l);
	if (t != TOBrace)
	{
		sc->PrintError("ожидался знак {", l);
	}
	Root->SemSetUk(newFunc, sc->GetUK());
	bool LocalFInit = Tree::getFlagInter();
	if (Tree::getFlagInter())
		if(newFunc->n->NodeType != TYPE_INITFUNCT)
			Tree::setFlagInter(false);
	LD();
	Tree::setFlagInter(LocalFInit);

	Root->SetCur(newFunc);
	if (Tree::getFlagInter())
		Root->Cur->remRightSubtree();
	t = sc->scaner(l);
	if (t != TCBrace)
	{
		sc->PrintError("ожидался знак }", l);
	}

}

void TDiagram::AV()
// 
// AV → int<VR>; | double<VR>;
//
{
	LEX l;
	int t, uk1, tempT;
	t = sc->scaner(l);
	if (t != TInt && t != TDouble)
	{
		sc->PrintError("ожидался тип данных", l);
	}
	tempT = t;
	do {
		t = sc->scaner(l);
		if (t != TIdent)
		{
			sc->PrintError("ожидался идентификатор", l);
		}
		Tree* newVar = Root->SemSetVar(l, TYPE_VAR, sc->GetUK());
		if (tempT == TInt)
		{
			Root->SemSetType(newVar, TYPE_INTEGER);
		}
		else
		{
			Root->SemSetType(newVar, TYPE_DOUBLE);
		}
		uk1 = sc->GetUK();
		t = sc->scaner(l);
		if (t == TSave)
		{
			Data newValue = ARD();
			Root->SetInit(newVar);
			Root->SemAssign(newVar, newValue, false, l, sc->GetUK());
			uk1 = sc->GetUK();
			t = sc->scaner(l);
		}
	} while (t == TComma);
	sc->PutUK(uk1);
	
	t = sc->scaner(l);
	if (t != TSemicolon) 
	{
		sc->PrintError("ожидался символ ;", l);
	}
}

Data TDiagram::ARD()
{
	LEX l;
	int type, uk1;
	Data tip1, tip2;
	tip1 = FSD();
	uk1 = sc->GetUK();
	type = sc->scaner(l);
	while ((type == TPlus) || (type == TMinus))
	{
		tip2 = FSD();
		if(tip1.dataType != DATA_TYPE::TYPE_EMPTYDATA && Tree::flagInterpret)
			if (type == TPlus)
			{
				printf("\nСложение: ");
				if (tip1.dataType == DATA_TYPE::TYPE_INTEGER)
					printf("%d +", tip1.dataValue.DataAsInteger);
				else if (tip1.dataType == DATA_TYPE::TYPE_DOUBLE)
					printf("%lf +", tip1.dataValue.DataAsDouble);

				if (tip2.dataType == DATA_TYPE::TYPE_INTEGER)
					printf(" %d", tip2.dataValue.DataAsInteger);
				else if (tip1.dataType == DATA_TYPE::TYPE_DOUBLE)
					printf(" %lf", tip2.dataValue.DataAsDouble);
			}
			else
			{
				printf("\nВычитание: ");
				if (tip1.dataType == DATA_TYPE::TYPE_INTEGER)
					printf("%d -", tip1.dataValue.DataAsInteger);
				else if (tip1.dataType == DATA_TYPE::TYPE_DOUBLE)
					printf("%lf -", tip1.dataValue.DataAsDouble);

				if (tip2.dataType == DATA_TYPE::TYPE_INTEGER)
					printf(" %d", tip2.dataValue.DataAsInteger);
				else if (tip1.dataType == DATA_TYPE::TYPE_DOUBLE)
					printf(" %lf", tip2.dataValue.DataAsDouble);
			}
		tip1 = Root->SemGetType(tip1, tip2, type, l);
		if (tip1.dataType == DATA_TYPE::TYPE_INTEGER)
			printf(" = %d", tip1.dataValue.DataAsInteger);
		else if (tip1.dataType == DATA_TYPE::TYPE_DOUBLE)
			printf(" = %lf", tip1.dataValue.DataAsDouble);
		printf("\n");
		uk1 = sc->GetUK();
		type = sc->scaner(l);
	}
	sc->PutUK(uk1);

	return tip1;
}

Data TDiagram::FSD()
{
	LEX l;
	int type, uk1;
	Data tip1, tip2;
	tip1 = SSD();
	uk1 = sc->GetUK();
	type = sc->scaner(l);
	while (type == TMult || type == TDiv || type == TMod)
	{
		tip2 = SSD();
		if (tip1.dataType != DATA_TYPE::TYPE_EMPTYDATA && Tree::flagInterpret)
			switch (type)
			{
			case TMult:
			{
				printf("\nУмножение: ");
				if (tip1.dataType == DATA_TYPE::TYPE_INTEGER)
					printf("%d *", tip1.dataValue.DataAsInteger);
				else if (tip1.dataType == DATA_TYPE::TYPE_DOUBLE)
					printf("%lf *", tip1.dataValue.DataAsDouble);

				if (tip2.dataType == DATA_TYPE::TYPE_INTEGER)
					printf(" %d", tip2.dataValue.DataAsInteger);
				else if (tip1.dataType == DATA_TYPE::TYPE_DOUBLE)
					printf(" %lf", tip2.dataValue.DataAsDouble);
				break;
			}
			case TDiv:
			{
				printf("\nЦелочисленное деление: ");
				if (tip1.dataType == DATA_TYPE::TYPE_INTEGER)
					printf("%d /", tip1.dataValue.DataAsInteger);
				else if (tip1.dataType == DATA_TYPE::TYPE_DOUBLE)
					printf("%lf /", tip1.dataValue.DataAsDouble);

				if (tip2.dataType == DATA_TYPE::TYPE_INTEGER)
					printf(" %d", tip2.dataValue.DataAsInteger);
				else if (tip1.dataType == DATA_TYPE::TYPE_DOUBLE)
					printf(" %lf", tip2.dataValue.DataAsDouble);
				break;
			}
			case TMod:
			{
				printf("\nОстаток: ");
				if (tip1.dataType == DATA_TYPE::TYPE_INTEGER)
					printf("%d mod", tip1.dataValue.DataAsInteger);
				else if (tip1.dataType == DATA_TYPE::TYPE_DOUBLE)
					printf("%lf mod", tip1.dataValue.DataAsDouble);

				if (tip2.dataType == DATA_TYPE::TYPE_INTEGER)
					printf(" %d", tip2.dataValue.DataAsInteger);
				else if (tip1.dataType == DATA_TYPE::TYPE_DOUBLE)
					printf(" %lf", tip2.dataValue.DataAsDouble);
				break;
			}
			}
		tip1 = Root->SemGetType(tip1, tip2, type, l);
		if (tip1.dataType == DATA_TYPE::TYPE_INTEGER)
			printf(" = %d", tip1.dataValue.DataAsInteger);
		else if (tip1.dataType == DATA_TYPE::TYPE_DOUBLE)
			printf(" = %lf", tip1.dataValue.DataAsDouble);
		printf("\n");
		uk1 = sc->GetUK();
		type = sc->scaner(l);
	}
	sc->PutUK(uk1);

	return tip1;
}

Data TDiagram::SSD()
{
	LEX l;
	int type, uk1;
	Data tip1, tip2;
	tip1 = TSD();
	uk1 = sc->GetUK();
	type = sc->scaner(l);
	while ((type <= TShiftB) && (type >= TShiftF))
	{
		tip2 = TSD();
		if (tip1.dataType != DATA_TYPE::TYPE_EMPTYDATA)
			if (type == TShiftF)
			{
				printf("\nСдвиг вперёд: ");
				if (tip1.dataType == DATA_TYPE::TYPE_INTEGER)
					printf("%d >>", tip1.dataValue.DataAsInteger);
				else if (tip1.dataType == DATA_TYPE::TYPE_DOUBLE)
					printf("%lf >>", tip1.dataValue.DataAsDouble);

				if (tip2.dataType == DATA_TYPE::TYPE_INTEGER)
					printf(" %d", tip2.dataValue.DataAsInteger);
				else if (tip1.dataType == DATA_TYPE::TYPE_DOUBLE)
					printf(" %lf", tip2.dataValue.DataAsDouble);
			}

			else 
			{
				printf("\nСдвиг назад: ");
				if (tip1.dataType == DATA_TYPE::TYPE_INTEGER)
					printf("%d <<", tip1.dataValue.DataAsInteger);
				else if (tip1.dataType == DATA_TYPE::TYPE_DOUBLE)
					printf("%lf <<", tip1.dataValue.DataAsDouble);

				if (tip2.dataType == DATA_TYPE::TYPE_INTEGER)
					printf(" %d", tip2.dataValue.DataAsInteger);
				else if (tip1.dataType == DATA_TYPE::TYPE_DOUBLE)
					printf(" %lf", tip2.dataValue.DataAsDouble);
			}
		tip1 = Root->SemGetType(tip1, tip2, type, l);
		if (tip1.dataType == DATA_TYPE::TYPE_INTEGER)
			printf(" = %d", tip1.dataValue.DataAsInteger);
		else if (tip1.dataType == DATA_TYPE::TYPE_DOUBLE)
			printf(" = %lf", tip1.dataValue.DataAsDouble);
		printf("\n");
		uk1 = sc->GetUK();
		type = sc->scaner(l);
	}
	sc->PutUK(uk1);

	return tip1;
}

Data TDiagram::TSD()
{
	LEX l;
	int type, uk1;
	Data tip1, tip2;
	tip1 = FFSD();
	uk1 = sc->GetUK();
	type = sc->scaner(l);
	while ((type >= TLess && type <= TEQ) || type == TNEQ)
	{
		tip2 = FFSD();
		tip1 = Root->SemGetType(tip1, tip2, type, l);
		uk1 = sc->GetUK();
		type = sc->scaner(l);
	}
	sc->PutUK(uk1);
	return tip1;
}

Data TDiagram::FFSD()
{
	LEX l;
	int type, uk1;
	Data retData;
	retData.dataType = DATA_TYPE::TYPE_EMPTYDATA;
	uk1 = sc->GetUK();
	type = sc->scaner(l);
	sc->PutUK(uk1);

	if (type == TIdent)
	{
		type = sc->scaner(l);
		Tree* viewNode = Root->FindUp(Root->Cur, l);
		if(viewNode != nullptr)
		{
			if ((viewNode->n->NodeType == TYPE_FUNCT || viewNode->n->NodeType == TYPE_INITFUNCT) && Tree::flagInterpret)
			{
				type = sc->scaner(l);
				if (type != TOBracket)
				{
					sc->PrintError("ожидался символ (", l);
				}
				type = sc->scaner(l);
				if (type != TCBracket)
				{
					sc->PrintError("ожидался символ )", l);
				}
				uk1 = sc->GetUK();
				Tree* nodeUK = Root->GetCur();
				bool LocalFinit = Tree::getFlagInter();
				Tree::setFlagInter(true);
				sc->PutUK(viewNode->n->text);
				Root->SetCur(viewNode);
				LD(viewNode->n->id);
				sc->PutUK(uk1);
				Root->SetCur(nodeUK);
				Tree::setFlagInter(LocalFinit);
			}
			retData = Root->CheckID(Root->Cur, viewNode->n->id); //проверка на наличие в таблице
		}
	}
	else if (type == TConstInt || type == TConstStr)
	{
		retData = Tree::buildDataFromConst(type, l);
		retData.dataType = DATA_TYPE::TYPE_INTEGER;
		type = sc->scaner(l);
		return retData;
	}
	else if (type == TOBracket)
	{
		type = sc->scaner(l);
		retData = ARD();
		type = sc->scaner(l);
		if (type != TCBracket)
			sc->PrintError("Ожидался символ )", l);
	}
	else if (type == TCBracket)
	{
		sc->PrintError("Пустое выражение", l);
	}
	else
	{
		sc->PrintError("Некоректное выражение", l);
	}
	return retData;
}

void TDiagram::L()
// 
// L → if(<AR>) {<LO>} | if(<AR>) {<LO>} else {<LO>}
//
{
	LEX l;
	int t, uk1, LocalFInit = Tree::getFlagInter();
	t = sc->scaner(l);
	if (t != TIf)
	{
		sc->PrintError("ожидался if", l);
	}
	t = sc->scaner(l);
	if (t != TOBracket)
	{
		sc->PrintError("ожидался символ (", l);
	}
	Data check = ARD();

	if (Tree::flagInterpret && (check.dataValue.DataAsInteger != 0 || check.dataValue.DataAsDouble != 0))
	{
		Tree::setFlagInter(true);
	}
	else
	{
		Tree::setFlagInter(false);
	}

	t = sc->scaner(l);
	if (t != TCBracket)
	{
		sc->PrintError("ожидался символ )", l);
	}

	uk1 = sc->GetUK();
	t = sc->scaner(l);
	if (t != TOBrace)
	{
		sc->PrintError("ожидался символ {", l);
	}
	sc->PutUK(uk1);
	Tree* newIf = Root->SemSetOper(TYPE_IF);
	LO();
	Root->SetCur(newIf);
	if (Tree::getFlagInter())
		newIf->remRightSubtree();
	
	//uk1 = sc->GetUK();
	t = sc->scaner(l);
	if (t != TCBrace)
	{
		sc->PrintError("ожидался символ }", l);
	}

	if (LocalFInit) 
	{
		Tree::setFlagInter(1 - Tree::getFlagInter());
	}

	uk1 = sc->GetUK();
	t = sc->scaner(l);
	//sc->PutUK(uk1);
	if (t == TElse)
	{
		uk1 = sc->GetUK();
		t = sc->scaner(l);
		if (t != TOBrace)
		{
			sc->PrintError("ожидался символ {", l);
		}
		sc->PutUK(uk1);
		Tree* newElse = Root->SemSetOper(TYPE_ELSE);
		LO();
		Root->SetCur(newElse);
		if (Tree::getFlagInter())
			newElse->remRightSubtree();
		
		t = sc->scaner(l);
		if (t != TCBrace)
		{
			sc->PrintError("ожидался символ }", l);
		}
	}
	if(!Tree::haveInitend)
		Tree::setFlagInter(true);

}

void TDiagram::LO()
// 
// LO → <L> | TIdent = <AR>| TIdent() "<LD>" ; | <LD>| ;
//
{
	LEX l;
	int t, uk1;
	uk1 = sc->GetUK();
	t = sc->scaner(l);
	if (t == TIf)
	{
		sc->PutUK(uk1);
		L();
		return;
	}
	if (t == TIdent)
	{
		Root->CheckID(Root->Cur, l);
		Tree *viewNode = Root->FindUp(Root->Cur, l);
		uk1 = sc->GetUK();
		t = sc->scaner(l);
		if (t == TSave)
		{
			Data res = ARD();
			Root->SemAssign(viewNode, res, false, l, sc->GetUK());
		}
	
		if (t == TOBracket) 
		{
			t = sc->scaner(l);
			if (t != TCBracket)
			{
				sc->PrintError("ожидался символ )", l);
			}
			if (Tree::flagInterpret) 
			{
				uk1 = sc->GetUK();
				Tree* nodeUK = Root->GetCur();
				sc->PutUK(viewNode->n->text);
				Root->SetCur(viewNode);
				LD(viewNode->n->id);
				sc->PutUK(uk1);
				Root->SetCur(nodeUK);
			}
		}

		uk1 = sc->GetUK();
		t = sc->scaner(l);
		if (t != TSemicolon)
		{
			sc->PrintError("ожидался символ ;", l);
		}
	}
	else
	{
		uk1 = sc->GetUK();
		if (t != TOBrace)
		{
			sc->PrintError("ожидался знак {", l);
		}
		LD();
		uk1 = sc->GetUK();
		t = sc->scaner(l);
		if (t != TCBrace)
		{
			sc->PrintError("ожидался знак }", l);
		}
		sc->PutUK(uk1);
	}
}

void TDiagram::LD()
//
// LD → <LD><LO> | <LD><AV>| ɛ
//
{
	LEX l;
	int t, uk1;
	uk1 = sc->GetUK();
	t = sc->scaner(l);
	while (t != TCBrace)
	{
		if ((t == TIdent) || (t == TIf) || (t == TOBrace))
		{
			sc->PutUK(uk1);
			LO();
		}
		if ((t == TInt) || (t == TDouble))
		{
			sc->PutUK(uk1);
			AV();
		}
		if (t == TReturn)
		{
			Data tp = ARD();
			Tree* v = Root->RetNearestFunc(Root->Cur), *tmp = Root->GetCur();
			if (v->n->NodeType == TYPE_INITFUNCT && Tree::flagInterpret)
				Tree::setFlagEnd(true);
			Root->SetCur(v);
			Root->SemSetType(Root->Cur, tp);
			Root->SetCur(tmp);
			if (tp.dataType != v->n->data.dataType)
			{
				PrintWarning("Функция возвращет другой тип данных.");
			}
			uk1 = sc->GetUK();
			t = sc->scaner(l);
			if (t != TSemicolon)
			{
				PrintError("Ожидался символ ;", l);
			}
			sc->PutUK(uk1);
			if (Tree::haveInitend)
				Tree::setFlagInter(false);
		}
		uk1 = sc->GetUK();
		t = sc->scaner(l);
	}
	sc->PutUK(uk1);
}

void TDiagram::LD(LEX id)
//
// LD → <LD><LO> | <LD><AV>| ɛ
//
{
	LEX l;
	int t, uk1;
	uk1 = sc->GetUK();
	t = sc->scaner(l);
	while (t != TCBrace)
	{
		if ((t == TIdent) || (t == TIf) || (t == TOBrace))
		{
			sc->PutUK(uk1);
			LO();
		}
		if ((t == TInt) || (t == TDouble))
		{
			sc->PutUK(uk1);
			AV();
		}
		if (t == TReturn)
		{
			Data tp = ARD();
			Tree* v = Root->FindUp(Root->Cur, id);
			Tree* tmp = Root->GetCur();
			
			Root->SetCur(v);
			Root->SemSetType(Root->Cur, tp);
			Root->SetCur(tmp);

			if (tp.dataType != v->n->data.dataType)
			{
				PrintWarning("Функция возвращет другой тип данных.");
			}

			uk1 = sc->GetUK();
			t = sc->scaner(l);
			if (t != TSemicolon)
			{
				PrintError("Ожидался символ ;", l);
			}
			sc->PutUK(uk1);
		}
		uk1 = sc->GetUK();
		t = sc->scaner(l);
	}
	sc->PutUK(uk1);
}
