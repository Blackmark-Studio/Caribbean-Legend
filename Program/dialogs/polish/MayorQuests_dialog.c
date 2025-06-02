void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		//----------------- уничтожение банды ----------------------
		case "DestroyGang_begin":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //боевке можно
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.DestroyGang.Location)], "DisableEncounters"); //энкаунтеры можно 
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)]);
			dialog.text = LinkRandPhrase("Płatność na beczce "+GetSexPhrase("kumple","dziewczyno")+"! Nazywam się "+GetFullName(npchar)+", a nie jestem przyzwyczajony do sprzeciwów...","Teraz pokaż mi swój sakiewkę, "+GetSexPhrase("kumpel","dziewczyna")+", i bądź szybki! Moje imię to  "+GetFullName(npchar)+", a mam nadzieję, że o mnie słyszałeś...","Daj mi wszystko co masz cennego, również zawartość twojego portfela. I pospiesz się, cierpliwość nie jest moją mocną stroną. Nie mogę powiedzieć tego samego o mojej żądzy krwi!");
			Link.l1 = LinkRandPhrase("Heh, więc ty jesteś tym słynnym bandytą "+GetFullName(npchar)+", o którym miejscowy gubernator "+sTemp+" nigdy nie przestaje mówić?","Ach, więc ty jesteś tym bandytą, którego ściga miejscowy gubernator "+sTemp+"?!","Cieszę się"+GetSexPhrase("","")+", aby cię zobaczyć, "+GetFullName(npchar)+". Lokalny gubernator, "+sTemp+" mówi tylko o tobie.");
			Link.l1.go = "DestroyGang_1";
		break;		
		case "DestroyGang_1":
			dialog.text = LinkRandPhrase("Tak, jestem dobrze znany w tych stronach, he-he... Czekaj, czy ty nie jesteś kolejnym "+GetSexPhrase("brudny łajdak","brudna suka")+" gubernatora, którego wysłał, aby mnie tropić?","Gubernator to mój dobry przyjaciel, to prawda. A czy ty przypadkiem, "+GetSexPhrase("kolejny bohater, wysłany","kolejna bohaterka, wysłana")+" za moją głowę?","Gubernator to mój najlepszy kumpel, to nie jest tajemnicą, he-he. Ale skąd ty to wiesz? Może on cię po mnie wysłał?");
			Link.l1 = LinkRandPhrase("Dokładnie, łotrzyku. Przygotuj się na śmierć!","Nie jesteś szybki w dechy! Dobrze, czas rozpocząć twoją likwidację. Dość gadania.","Tak, to ja. Wyjmij swoją broń, kumplu! Zobaczymy, jakiego koloru jest twoja krew.");
			Link.l1.go = "DestroyGang_ExitFight";	
			Link.l2 = LinkRandPhrase("Och, nieważne! Nie potrzebuję wcale takich kłopotów...","Nie, nie, w żadnym wypadku nie jestem bohaterem...","Nie, nie, nigdy bym tego nie zrobił! Nie potrzebuję kłopotów...");
			Link.l2.go = "DestroyGang_2";	
		break;
		case "DestroyGang_2":
			dialog.text = LinkRandPhrase("To lepiej, "+GetSexPhrase("kumpel","dziewczyno")+"...A teraz znikaj!","I to jest słuszna decyzja. Chciałbyś wiedzieć, ilu bohaterów wysłałem do innego świata... Dobrze, mniej słów. Spadaj, "+GetSexPhrase("kawał gówna","suka")+"!","Dobry "+GetSexPhrase("chłopiec","dziewczyna")+"! Bardzo mądra decyzja - nie wtrącać się w sprawy innych... No dobrze, znikaj już, "+GetSexPhrase("kumpel","dziewczyno")+".");
			Link.l1 = "Pożegnanie i powodzenia...";
			Link.l1.go = "DestroyGang_ExitAfraid";	
		break;

		case "DestroyGang_ExitAfraid":
			pchar.GenQuest.DestroyGang = "Found"; //флаг нашёл, но струсил
			npchar.money = AddMoneyToCharacter(npchar, sti(pchar.money));
			pchar.money = 0;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar)-1, false, "DestroyGang_SuddenAttack");
			for(i = 1; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;	
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
				LAi_SetImmortal(sld, true);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DestroyGang_SuddenAttack");
			}
			DialogExit();
		break;

		case "DestroyGang_ExitFight":
			for(i = 0; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// ОЗГ - пассажир
		case "ContraPass_abordage":
			dialog.text = "Arghh, łotrzyku! Jak śmiałeś zaatakować mój statek?! Zapłacisz za to!";
			link.l1 = "Wręcz przeciwnie, dostaję za to zapłatę. Masz na pokładzie pewnego człowieka o imieniu "+pchar.GenQuest.TakePassenger.Name+". On jest tym, którego potrzebuję.";
			link.l1.go = "ContraPass_abordage_1";
		break;
		
		case "ContraPass_abordage_1":
			dialog.text = "Wiedziałem, że ten łajdak przysporzy nam kłopotów... Ale nie dostaniesz mnie tak łatwo! Broń się, brudny piracie!";
			link.l1 = "To ty powinieneś myśleć o obronie, szczeniaku.";
			link.l1.go = "ContraPass_abordage_2";
		break;
		
		case "ContraPass_abordage_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "ContraPass_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Tempsailor":
			dialog.text = "Kapitanie, przeszukaliśmy kajuty i ładownię, jak nakazałeś. Ten łajdak próbował się ukryć, ale go znaleźliśmy.";
			link.l1 = "Świetnie! Gdzie on jest teraz?";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "On jest w ładowni, jak nam kazałeś.";
			link.l1 = "Świetnie! Teraz opuśćmy ten stary kibel. Czas wracać.";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "Natychmiast, kapitanie!";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			sld = GetCharacter(NPC_GenerateCharacter("ContraPass", "citiz_"+(rand(9)+11), "man", "man", 10, sti(pchar.GenQuest.TakePassenger.Nation), -1, true, "quest"));
			sld.name = pchar.GenQuest.TakePassenger.Name;
			sld.lastname = "";
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.TakePassenger.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
		break;
		
		case "Fugitive_city": // ходит по городу
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Co pan sobie życzy, panie?";
			link.l1 = "Cóż-cóż... Więc ty jesteś "+pchar.GenQuest.FindFugitive.Name+", czyż nie? Bardzo się cieszę, że cię widzę...";
			link.l1.go = "Fugitive_city_1";
		break;
		
		case "Fugitive_city_1":
			dialog.text = "Cóż, to ja, rzeczywiście, choć nie wiem, dlaczego cieszy cię moje widzenie? Wydaje mi się to dziwne, ponieważ nigdy cię wcześniej nie widziałem... Mógłbyś się tłumaczyć?";
			link.l1 = "Ale oczywiście. Przybyłem z "+XI_ConvertString("Kolonia"+pchar.GenQuest.FindFugitive.Startcity+"Gen")+", na rozkaz miejscowego gubernatora. Jesteś aresztowany i muszę cię dostarczyć do tego samego miasta... O, i ręce z dala od szabli! Nie próbuj niczego głupiego dobry człowieku, bo skończy się źle dla ciebie!";
			link.l1.go = "Fugitive_city_2";
		break;
		
		case "Fugitive_city_2":
			dialog.text = "Cóż, znalazłeś mnie w końcu... Panie, posłuchaj mnie, a może zmienisz zdanie. Tak, uciekłem z garnizonu. Ale nie mogłem obserwować upadku naszej armii!\nChciałem spokojnego życia i znalazłem takie życie tutaj, w tej wiosce... Zostaw mnie w spokoju, powiedz im, że nie udało ci się mnie znaleźć lub że uciekłem z piratami na otwarte morze. W zamian dam ci ten woreczek bursztynu. Bardzo cenny przedmiot, muszę powiedzieć...";
			link.l1 = "Nie myśl nawet o przekupieniu mnie, panie! Oddaj broń i idź za mną!";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "Hmm... Degradacja? Cichy i spokojny żywot? Dobrze, chyba mogę spełnić twoje życzenie. Gdzie jest twój bursztyn?";
			link.l2.go = "Fugitive_city_gift";
		break;
		
		case "Fugitive_city_fight":
			dialog.text = "Wtedy wyjmij swój miecz, najemniku! Nie dostaniesz mnie tak łatwo!";
			link.l1 = "Dobrze, zobaczmy na co cię stać!";
			link.l1.go = "Fugitive_fight_1";
		break;
		
		case "Fugitive_city_gift":
			TakeNItems(pchar, "jewelry8", 50+hrand(25));
			TakeNItems(pchar, "jewelry7", 2+hrand(5));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received amber");
			dialog.text = "Tutaj... I mam nadzieję, że nigdy więcej nie zobaczę ani ciebie, ani innych 'wysłanników'.";
			link.l1 = "Zapewniam cię, że nie. Do widzenia, panie!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_gift_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.FindFugitive = "Found"; //флаг провалил
			AddQuestRecord("MayorsQuestsList", "12-4");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity));
		break;
		
		case "Fugitive_fight_1":// в городе и бухте
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Fugitive_afterfight":
			dialog.text = "Arrgh! Wygrałeś, pieprzyć cię! Poddaję się...";
			link.l1 = "Pilnuj języka, panie! A teraz, daj mi swój szablę, proszę... Idź za mną, i bez głupich sztuczek!";
			link.l1.go = "Fugitive_afterfight_1";
		break;
		
		case "Fugitive_afterfight_1":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			//DeleteAttribute(npchar, "LifeDay");
			npchar.lifeday = 0;
			LAi_SetImmortal(npchar, true);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.FindFugitive.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			pchar.GenQuest.FindFugitive = "Execute"; //флаг выполнил успешно
			pchar.quest.FindFugitive1.win_condition.l1 = "location";
			pchar.quest.FindFugitive1.win_condition.l1.location = pchar.GenQuest.FindFugitive.Startcity+"_townhall";
			pchar.quest.FindFugitive1.function = "FindFugitive_inResidence";
			SetFunctionTimerCondition("FindFugitive_Over", 0, 0, 30, false);
		break;
		
		case "Fugitive_shore": // в бухте
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Panie, nie jestem w nastroju rozmawiać z tobą, więc...";
			link.l1 = "Mimo to, będziesz musiał ze mną rozmawiać. Jesteś "+pchar.GenQuest.FindFugitive.Name+", nieprawdaż? Myślę, że nie powinieneś tego zaprzeczać.";
			link.l1.go = "Fugitive_shore_1";
		break;
		
		case "Fugitive_shore_1":
			dialog.text = "I nie zamierzam tego zaprzeczać, to ja. Ale czego ty chcesz?";
			link.l1 = "Muszę cię przyprowadzić do "+XI_ConvertString("Kolonia"+pchar.GenQuest.FindFugitive.Startcity)+", miejscowy gubernator nie może się doczekać, aby cię zobaczyć. Bez głupich sztuczek, proszę! Oddaj swoją broń i chodź za mną!";
			link.l1.go = "Fugitive_shore_2";
		break;
		
		case "Fugitive_shore_2":
			dialog.text = "Rozumiem... Panie, zanim strzelisz na oślep, pozwól mi coś powiedzieć. Tak, uciekłem z garnizonu. Ale miałem na to powody. Nie mogę pozostać na służbie, to więcej, niż mogę znieść! Rozumiesz mnie? Nie mogę!\nChcę spokojnego życia i znalazłem takie życie tutaj, w tej wiosce... Zostaw mnie w spokoju, powiedz im, że nie udało ci się mnie znaleźć albo że uciekłem z piratami w otwarte morze. W zamian dam ci moje tygodniowe połowy pereł. To wszystko, co mam.";
			link.l1 = "Nie myśl nawet o przekupstwie, panie! Oddaj swoją broń i idź za mną!";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "Hmm... Zmęczony służbą wojskową? Chcesz spokojnego życia? Dobrze, myślę, że mogę spełnić twoje życzenie. Gdzie są twoje perły?";
			link.l2.go = "Fugitive_shore_gift";
		break;
		
		case "Fugitive_shore_gift":
			TakeNItems(pchar, "jewelry52", 100+hrand(40));
			TakeNItems(pchar, "jewelry53", 400+hrand(100));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received pearls");
			dialog.text = "Tutaj... I mam nadzieję, że nigdy więcej nie zobaczę ani ciebie, ani innych 'posłańców'.";
			link.l1 = "Zapewniam cię, że nie. Do widzenia, panie!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern": // в таверне
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			dialog.text = "Ehhh... hic! Panie, nie szukam towarzystwa - szczególnie twojego. Zgubić się!";
			link.l1 = "Ale JA szukam twojego towarzystwa, "+pchar.GenQuest.FindFugitive.Name+"! I będziesz tolerować moje towarzystwo w ładowni mojego statku. Idziemy do  "+XI_ConvertString("Kolonia"+pchar.GenQuest.FindFugitive.Startcity)+", do gubernatora miasta. On prawie umiera z chęci cię zobaczyć.";
			link.l1.go = "Fugitive_tavern_1";
		break;
		
		case "Fugitive_tavern_1":
			dialog.text = "H-Hic!"+RandSwear()+" Więc jednak mnie dogonił! Słuchaj, kumpel, nie wiesz co się stało, nie byłeś tam! Nie mogłem zostać na służbie, po prostu nie mogłem! Nadal co wieczór upijam się, żeby zapomnieć o tym\nPosłuchaj, zawrzyjmy umowę. Powiedz mu, że nie udało ci się mnie znaleźć lub że uciekłem z piratami na otwarte morze. W zamian oddam ci wszystkie samorodki, które znalazłem w lokalnej jaskini. To wszystko, co mam, widzisz, oddaję ci wszystko, tylko żeby nigdy więcej go nie zobaczyć "+XI_ConvertString("Kolonia"+pchar.GenQuest.FindFugitive.Startcity)+"...";
			link.l1 = "Nie myśl nawet o przekupieniu mnie, panie! Złóż broń i chodź za mną!";
			link.l1.go = "Fugitive_tavern_fight";
			link.l2 = "Hmm... Nieprzyjemna historia? Dręczą cię koszmary czy wyrzuty sumienia? Dobrze, chyba mogę zostawić cię z tym samemu. Gdzie są twoje samorodki?";
			link.l2.go = "Fugitive_tavern_gift";
		break;
		
		case "Fugitive_tavern_gift":
			TakeNItems(pchar, "jewelry5", 50+hrand(30));
			TakeNItems(pchar, "jewelry6", 100+hrand(50));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received nuggets");
			dialog.text = "Tutaj... I mam nadzieję, że nigdy więcej nie zobaczę ani ciebie, ani innych 'posłańców'.";
			link.l1 = "Zapewniam cię, że nie. Do widzenia, panie!";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern_fight":
			dialog.text = "Wtedy wyjmij swój miecz, najemniku! Nie dostaniesz mnie tak łatwo!";
			link.l1 = "Dobrze, zobaczmy jak dużo jesteś wart!";
			link.l1.go = "Fugitive_fight_2";
		break;
		
		case "Fugitive_fight_2":// в таверне
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetImmortal(npchar, false);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
