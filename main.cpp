#include "dfs.h"
#include "scaner.h"
#include "Diagram.h"
int main(int argc, char * argv[])
{
	setlocale(LC_CTYPE, "rus");
	int type; 
	LEX l;
	
	TScaner *sc;
	if (argc <= 1) 
	{
		sc = new TScaner("input.txt");
	}
	else
	{
		sc = new TScaner(argv[1]);
	}

	TDiagram* dg = new TDiagram(sc);
	dg->S();
	type = sc->scaner(l);
	if (type == TEnd)
	{
		printf("Синтаксических ошибок не обнаружено. \n");
	}
	else
	{
		sc->PrintError("Лишний текст в конце программы.", l);
	}
	return 0;
}
