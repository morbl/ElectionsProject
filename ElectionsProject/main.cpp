#include "mainFunction.h"
#include <unordered_map>

int main()
{
	Date date(2020, 4);

	ElectionCycle election(date);
	firstInit(election);

	interActiveMenu(election);
}

