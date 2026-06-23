// dev tests
ref rOldPchar;
ref rOldCharacterRef;

void test__DLG_RunTests()
{
	DLG_InitTestContext();
	// Пока запуск тестов происходит сразу после запуска игры, соответственно сущности типа pchar - недоступны
	object tests;
	DLG_SetTests(&tests);
	aref test;

	for (int i=0; i<GetAttributesNum(&tests); i++)
	{
		test = GetAttributeN(&tests, i);
		test.success = false;
		string testName = GetAttributeName(&test);
		DLG_RunTest(&test);
		assert(int(test.success) == 1, "Test " + testName + " is failed");
		if (int(test.success) == 1)
		{
			continue;
		}

		trace("========================");
		trace("Test " + testName + " is failed");
		DumpAttributes(&test);
		trace("========================");
	}

	DLG_RevertTestContext();
}

void DLG_SetTests(ref tests)
{
  tests.rand0 = "$rand(A|B)";
  tests.rand0.expect = "A|B";
  tests.rand1 = "$rand(C|D)";
  tests.rand1.expect = "C|D";

  tests.manWoman0 = "$manWoman(i'm a man|i'm a woman)";
  tests.manWoman0.expect = "i'm a man";
  tests.manWoman0.context = "man";

  tests.manWoman1 = "$manWoman(i'm a man|i'm a woman)";
  tests.manWoman1.expect = "i'm a man|i'm a woman";
  tests.manWoman2 = "$ctxManWoman(i'm a man|i'm a woman)";

  tests.manWoman2.expect = "i'm a man";
  tests.manWoman2.context = "man";

  tests.manWoman3 = "$ctxManWoman(|i'm a woman)";
  tests.manWoman3.expect = "";
  tests.manWoman3.context = "man";

  tests.hasAttr0 = "$hasAttr(sex|A|B)";
  tests.hasAttr0.expect = "A";

	/*
	Поменял тест. Насколько я его понял, если отсутствует поле context, то DLG_GetTestContext вернет NullCharacter,
	в котором не будет атрибута sex. Поэтому возвращаем B
	*/

  tests.hasAttr1 = "$ctxhasAttr(sex|A|B)";
  tests.hasAttr1.expect = "B";

  tests.hasAttr2 = "$ctxhasAttr(sex|A|B)";
  tests.hasAttr2.expect = "A";
  tests.hasAttr2.context = "woman";

  tests.shipName0 = "$ctxShipName";
  tests.shipName0.expect = "Krusenstern";
  tests.shipName0.context = "withship";

  tests.shipClass0 = "$ctxShipClass()";
  tests.shipClass0.expect = xiStr("Lugger");
  tests.shipClass0.context = "withShipClassMan";

  tests.shipClass1 = "$ctxShipClass()";
  tests.shipClass1.expect = xiStr("Brigantine");
  tests.shipClass1.context = "withShipClassWoman";

  tests.shipClass2 = "$ctxShipClass(Dat)";
  tests.shipClass2.expect = xiStr("LuggerDat");
  tests.shipClass2.context = "withShipClassMan";

  tests.shipClass3 = "$ctxShipClass(Dat)";
  tests.shipClass3.expect = xiStr("BrigantineDat");
  tests.shipClass3.context = "withShipClassWoman";

  tests.attr0 = "$attr($context.sex)";
  tests.attr0.expect = "man";
  tests.attr0.context = "man";

  tests.attr1 = "$name $attr($context.sex)";
  tests.attr1.expect = pchar.name + " " + pchar.sex;
  tests.attr1.context = "pchar";

  tests.upper0 = "^hell^O ^";
  tests.upper0.expect = "HellO ^";

  tests.lower0 = "_Hell_o _";
  tests.lower0.expect = "hello _";

  tests.custom0 = "$GetCityName(bridgetown) $name";
  tests.custom0.expect = GetCityName("bridgetown") + " " + pchar.name;
  tests.custom0.context = "pchar";

  tests.common0 = "$rand($player.name|$npc.name)";
  tests.common0.expect = pchar.name + "|" + CharacterRef.name;
}

void DLG_RunTest(ref test)
{
  string input = GetAttributeValue(test);
  test.input = input;
  test.output = DLGO(input, DLG_GetTestContext(&test));
  aref expect;
  makearef(expect, test.expect);
  DLG_SplitString(&expect, test.expect, "|", 0);

  for (int i=0; i < GetAttributesNum(&expect); i++)
  {
    string attrName = "var" + i;
    if (test.output != expect.(attrName)) continue;

    test.success = true;
    break;
  }
}

object DLG_GetTestContext(ref test)
{
  	if (!CheckAttribute(&test, "context")) return NullCharacter;

	object result;
	CopyAttributes(&result, NullCharacter);
	result.sex = "man";

	switch(test.context)
	{
		case "woman":
			result.sex = "woman";
		break;
		case "pchar":
			CopyAttributes(&result, pchar);
		break;
		case "withship":
			result.ship.name = "Krusenstern";
		break;
		case "withShipClassMan":
			result.Ship.Type = CreateBaseShip(SHIP_LUGGER);
		break;
		case "withShipClassWoman":
			result.Ship.Type = CreateBaseShip(SHIP_BRIGANTINE);
		break;
	}

	return result;
}


// func(obj, "a|b|c", "|", 0) →
//   obj.var0 = a
//   obj.var1 = b
//   obj.var2 = c
void DLG_SplitString(ref result, string input, string bySym, int iteration)
{
	string varName = "var" + iteration;
	int iPos = findsubstr(&input, bySym, 0);
	result.(varName) = input;
	if (iPos < 0) return;
	int len = strlen(&input);

	if (iPos == 0) result.(varName) = "";
	else result.(varName) = strcut(&input, 0, iPos-1);

	if (iPos +1 == len) return;
	DLG_SplitString(result, strcut(&input, iPos+1, len-1), bySym, iteration+1);
}


void DLG_InitTestContext()
{
	rOldPchar = pchar;
	rOldCharacterRef = CharacterRef;
	pchar = &Characters[1];
	CharacterRef = &Characters[2];
}

void DLG_RevertTestContext()
{
	pchar = rOldPchar;
	CharacterRef = rOldCharacterRef;
}