//Jason общий диалог уличных контриков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Czego chcesz?";
			link.l1 = "Nic.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("Mam do ciebie pytanie.","Potrzebuję informacji.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Marginpassenger"))//захват пассажира
				{
					dialog.text = "Hej, kapitanie! Tak, do ciebie mówię. Chodź tutaj, mam dla ciebie interes...";
					link.l1 = "I co to za sprawa?";
					link.l1.go = "passenger";
					link.l2 = "Spieszę się, przyjacielu. Może następnym razem.";
					link.l2.go = "exit_quest";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("Ej, kapitanie, jestem teraz zajęty. Czego potrzebujesz?","Czego chcesz, kapitanie?","Kapitanie, nie jestem w nastroju do rozmów. Czego chcesz?");
				link.l1 = "Witaj, "+GetAddress_FormToNPC(NPChar)+"  Zaczekaj chwilę, chcę, żebyś mi coś powiedział.";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("Mam do ciebie pytanie.","Potrzebuję informacji.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "To nic, jestem w drodze do tawerny...";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

//----------------------------------------захват пассажиров для выкупа------------------------------------------
			case "passenger":
				DeleteAttribute(npchar, "talker");
				dialog.text = "Hm. Jesteś kapitanem statku, ale nie wyglądasz na kupca. Wygląda na to, że masz trochę monet w kieszeni... Co powiesz na zdobycie ciekawych informacji w zamian za garść dublonów?";
				link.l1 = "Najpierw udowodnij, że twoje informacje są warte choćby jednego reala.";
				link.l1.go = "passenger_1";
			break;
		
			case "passenger_1":
				dialog.text = "Tak jest, kapitanie, tak jest. To kosztuje znacznie więcej, niż proszę. Daj mi złoto, a powiem ci, kiedy i na którym statku popłynie pewna bardzo ważna osoba. Będziesz mógł ją wykupić za bardzo dobrą cenę... Nawet powiem ci imię kupca. Umowa stoi?";
				link.l1 = "Nie ma mowy! Nie jestem porywaczem. Wynocha!";
				link.l1.go = "exit_quest";
				link.l2 = "A jak mogę wiedzieć, że mówisz prawdę?";
				link.l2.go = "passenger_2";
			break;
		
			case "passenger_2":
				pchar.GenQuest.Marginpassenger.Dublon = 70+hrand(5)*10;
				dialog.text = "Byłoby bardzo nierozsądnie oszukiwać cię, wilku morski. Mieszkam w tym mieście i nie potrzebuję kłopotów. Za jedyne "+sti(pchar.GenQuest.Marginpassenger.Dublon)+" doubloonów dostarczę pełne informacje. Zarobisz znacznie więcej.";
				if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "Masz rację. Weź złoto i zacznij mówić.";
					link.l1.go = "passenger_4";
				}
				link.l2 = "Nie mam teraz przy sobie wystarczającej ilości monet.";
				link.l2.go = "passenger_3";
				link.l3 = "Żartujesz sobie? Płacić prawdziwe złoto za puste obietnice? Zjeżdżaj...";
				link.l3.go = "exit_quest";
			break;
		
			case "passenger_3":
				dialog.text = "Nie chcesz? Dobrze, kapitanie. Mogę poczekać jeszcze kilka dni, a ta informacja również. Znajdź mnie, gdy zdobędziesz swoje złoto. Nie będzie trudno mnie znaleźć... dzisiaj, ha-ha-ha!";
				link.l1 = "Nie szczerz tak zębów. Dobrze, przyniosę ci złoto... jeśli się nie rozmyślę.";
				link.l1.go = "passenger_wait";
			break;
			
			case "passenger_wait":
			DialogExit();
				SetFunctionTimerCondition("Marginpassenger_Over", 0, 0, 2, false);
				npchar.dialog.currentnode = "passenger_repeat";
			break;

			case "passenger_repeat":
				dialog.text = "Czy przyniosłeś moje złoto?";
				if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "Tak. Weź to. Nawet nie próbuj teraz kłamać...";
					link.l1.go = "passenger_4";
				}
				link.l2 = "Jeszcze nie. Może później...";
				link.l2.go = "exit";
				Nextdiag.Tempnode = "passenger_repeat";
			break;
			
			case "passenger_4"://установка параметров
				pchar.quest.Marginpassenger_Over.over = "yes"; //снять возможный таймер
				RemoveItems(pchar, "gold_dublon", sti(pchar.GenQuest.Marginpassenger.Dublon));
				pchar.GenQuest.Marginpassenger.Name = GetFullName(npchar);
				pchar.GenQuest.Marginpassenger.City = npchar.city;
				pchar.GenQuest.Marginpassenger.Targetcity = SelectAnyColony(npchar.city); 
				pchar.GenQuest.Marginpassenger.Nation = npchar.nation;
				pchar.GenQuest.Marginpassenger.Days = 10+hrand(5);
				pchar.GenQuest.Marginpassenger.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
				pchar.GenQuest.Marginpassenger.q2Name = GenerateRandomName(sti(npchar.nation), "man");
				pchar.GenQuest.Marginpassenger.Chance = 0.8+frand(0.4);
				SelectMarginpassengerParameter();
				log_testinfo(pchar.GenQuest.Marginpassenger.Targetcity);
				dialog.text = "Trzymaj proch suchy, wkrótce będzie ci potrzebny, kapitanie. Teraz słuchaj, w "+FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days))+"  statek odpłynie z naszej kolonii, statek jest "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Imię")))+" nazwany '"+pchar.GenQuest.Marginpassenger.ShipName+" i będzie zmierzać do "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity+"Gen")+". Będzie pasażer - "+pchar.GenQuest.Marginpassenger.Text+", nazwany "+pchar.GenQuest.Marginpassenger.q1Name+"\nKapitan "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Imię")+"Generał"))+" to żółtodzioby tchórz jak wszyscy handlarze, ha-ha-ha! Może nawet unikniesz walki. Wystarczy, że napełnisz go strachem przed diabłem, a sam odda cel, he-he\nJak rozumiesz, "+pchar.GenQuest.Marginpassenger.Text1+", prawdopodobnie dostaniesz swoje monety, tak, ale lokalne władze będą cię ścigać na śmierć po tym. Lepiej przynieś swoją zdobycz do "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+"Znajdziesz tam człowieka o imieniu "+pchar.GenQuest.Marginpassenger.q2Name+"\n"+pchar.GenQuest.Marginpassenger.Text2+" i nawet nie będziesz musiał podawać swojego imienia. To twoja decyzja, gdzie wykupić swojego człowieka, ale nie bierz na siebie zbyt wiele... Ale "+sti(pchar.GenQuest.Marginpassenger.Dublon)*4+"  doubloonów możesz zażądać na pewno. Zrozumiano?";
				link.l1 = "Tak. Wrócę na mój statek i zapiszę to w dzienniku.";
				link.l1.go = "passenger_5";
			break;
		
			case "passenger_5":
				dialog.text = "Dokładnie! Słuszny wybór. Dobrze, kapitanie, powodzenia w tym łatwym zadaniu. Ach tak, prawie zapomniałem: "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Imię")))+"popłynie nie z portu, lecz z jednej z pobliskich zatok. Uważaj na to. Powodzenia i dzięki za złoto!";
				link.l1 = "Proszę bardzo. Nie wydawaj wszystkiego w jedną noc.";
				link.l1.go = "exit_quest";
				npchar.lifeday = 0;
				ReOpenQuestHeader("Marginpassenger");
				AddQuestRecord("Marginpassenger", "1");
				AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
				AddQuestUserData("Marginpassenger", "sTargetCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity));
				AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
				AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
				AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
				AddQuestUserData("Marginpassenger", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days)));
				AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Voc")));
				AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
				AddQuestUserData("Marginpassenger", "sText", pchar.GenQuest.Marginpassenger.Text1);
				pchar.GenQuest.Marginpassenger = "begin";
				SetFunctionTimerCondition("Marginpassenger_InWorld", 0, 0, sti(pchar.GenQuest.Marginpassenger.Days), false);
			break;
			
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Słuchaj, kamracie, uspokój się i schowaj broń.","Słuchaj, kamracie, uspokój się i schowaj broń.");
			link.l1 = LinkRandPhrase("Dobrze.","Dobrze.","Jak sobie życzysz.");
			link.l1.go = "exit";
		break;
		
		case "question":
			dialog.text = LinkRandPhrase("Nie owijaj w bawełnę, kapitanie. Mów, czego chcesz!","Och, dobrze. Czego chcesz?","Pytania? Dobrze, marynarzu, słucham.");
			link.l1 = LinkRandPhrase("Czy możesz mi opowiedzieć najnowsze plotki?"," Czy wydarzyło się tu ostatnio coś ciekawego?","Co się dzieje na Karaibach?");
			link.l1.go = "rumours_marginal";
		break;
		
		case "exit_quest":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void SelectMarginpassengerParameter()
{
	if (hrand(1) == 0)
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "woman");
		pchar.GenQuest.Marginpassenger.model = "women_"+(rand(5)+11);
		pchar.GenQuest.Marginpassenger.sex = "woman";
		pchar.GenQuest.Marginpassenger.ani = "towngirl";
		pchar.GenQuest.Marginpassenger.Text2 = "He wants to marry her and will pay a significant sum for the girl.";
		switch (hrand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = "store keeper's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the store keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "shipyard's master's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "tavern keeper's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "banker's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "harbor master's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the harbor master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	else
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "man");
		pchar.GenQuest.Marginpassenger.model = "citiz_"+(rand(9)+11);
		pchar.GenQuest.Marginpassenger.sex = "man";
		pchar.GenQuest.Marginpassenger.ani = "man";
		pchar.GenQuest.Marginpassenger.Text2 = "He has been planning to ingratiate himself with this family and he will pay a lot for the prisoner ";
		switch (hrand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = "trader's relative, shipmaster's";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipmaster";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "shipyard's master's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "tavern keeper's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "banker's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "harbor master's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the harbor master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	if (sti(pchar.rank) < 5) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 10) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 10 && sti(pchar.rank) < 17) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_4 + FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 17 && sti(pchar.rank) < 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
}
