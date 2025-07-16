// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	int i,n;
	string month;
	
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Już próbowałeś zadać mi pytanie "+GetAddress_Form(NPChar)+"...","Rozmawiasz o tej kwestii już trzeci raz dzisiaj...","Spójrz, jeśli nie masz nic do powiedzenia o sprawach portowych, to nie zawracaj mi głowy swoimi pytaniami.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie.","Nie mam o czym rozmawiać."),"Nieważne.","Rzeczywiście, już trzeci raz...","Przykro mi, ale na razie nie interesują mnie sprawy portu.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello_1")
            {
                link.l1 = "Dzień dobry. Chciałbym dowiedzieć się, gdzie jest kapitan Francois Gontier. Mam ważną sprawę.";
                link.l1.go = "Portobello_ratP_1";
            }
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toPBPortOffice" || pchar.questTemp.SharkGoldFleet == "KillCurier")
				{
					link.l1 = "Jestem kupcem, przybyłem z Caracas, a twój kolega z miejscowego urzędu portowego poprosił mnie, abym przekazał ci pewną korespondencję...";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "MoneySpeak")
				{
					link.l1 = "Tak, jestem po zapłatę.";
					link.l1.go = "SharkGoldFleet_11";
				}
			}
			//<-- на пару с Акулой
		break;

		case "Portobello_ratP_1":
			dialog.text = "Sprawa ważna, powiadasz? Zobaczmy. Cóż...  Francois Gontier, na korwecie '"+pchar.questTemp.Slavetrader.ShipName+"... Według moich notatek, señor Gontier zmierzał na Jamajkę.";
			link.l1 = "Dziękuję! Bardzo pomogłeś!";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatJamaica";
			AddQuestRecord("Slavetrader", "21_3");
			AddQuestUserData("Slavetrader", "sShip", pchar.questTemp.Slavetrader.ShipName);
		break;
		// на пару с Акулой -->
		case "SharkGoldFleet":
			if(!bImCasual) pchar.quest.SharkGoldFleetToPB10.over = "yes"; 
			RemoveItems(PChar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_1");
			dialog.text = "Ach, cóż, nareszcie! Czy mówisz, że jesteś kupcem? Znowu próbują oszczędzać na kurierach i odkładają wysyłkę do ostatniej cholery... Tak, cóż, na pewno! To prawda. I jak mam wyposażyć eskadrę w takim czasie?...";
			link.l1 = "Wydaje się nieodpowiedzialne...";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Tak można to ująć! No cóż, trudno. Spotkamy się z czasem... Mówię o swoim czasie, nie zwracaj uwagi. Słuchaj, wracasz może przypadkiem?";
			link.l1 = "No cóż, właściwie to zamierzałem sprzedać tu towary, a potem - tak, wrócić do Caracas ...";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Świetnie! Teraz napiszę im odpowiedź i poproszę cię, abyś ją odesłał. Więc... Dostarcz to, proszę, w ciągu dziesięciu dni, w przeciwnym razie nie będą mieli czasu na zrobienie czegokolwiek na czas... I podaj swoje imię.";
			if(pchar.questTemp.SharkGoldFleet == "KillCurier")
			{
				link.l1 = "Moje imię to "+GetFullName(pchar)+".";
				link.l1.go = "SharkGoldFleet_03";
			}
			else
			{
				link.l1 = "Nazywam się Andreas Garcia.";
				link.l1.go = "SharkGoldFleet_09";
			}
		break;
		
		case "SharkGoldFleet_03":
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			dialog.text = "Poczekaj chwilę... Zapisane. Proszę bardzo. Pamiętaj: dziesięć dni! W międzyczasie przeczytam dokładniej, co mi przyniosłeś.";
			link.l1 = "Tak, pamiętam. Do widzenia!";
			link.l1.go = "SharkGoldFleet_04";
		break;

		case "SharkGoldFleet_04":
			dialog.text = "Poczekaj chwilę... Nie rozumiem... Jeszcze raz, jak powiedziałeś, że się nazywasz?";
			link.l1 = "Ja?.. Cóż... Czemu to takie ważne?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("target_month_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			dialog.text = "To bardzo ważne! Mówi... Więc... "+n+" "+month+"... Nie, to nie to... 12, 50, 69, 55... Ale gdzie to jest... Ach, tutaj jest! List musi być dostarczony przez kapitana "+pchar.questTemp.SharkGoldFleet.CurierName+" "+pchar.questTemp.SharkGoldFleet.Curierlastname+" A ty powiedziałeś, że twoje imię to... "+GetFullName(pchar)+"?";
			link.l1 = "Musiała zajść jakaś pomyłka...";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.CurierName");
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.Curierlastname");
			dialog.text = "Nie, nie może być pomyłki. Oddaj mi list, który ci dałem. Muszę to rozgryźć!";
			link.l1 = "Chodź... Dostarczę to, wszystko będzie dobrze.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Nie! Oddaj mi list! Straże!!!";
			link.l1 = "Ach, chcesz to załatwić po trudnemu, co?";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "DifficultVar";
			if (CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				TakeNationLicence(HOLLAND);
				log_info("Trading license cancelled!");
			}
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Sold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", sti(pchar.rank), SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, sti(pchar.rank), true);         
				ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto3");
				LAi_SetWarriorType(sld); 
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				LAi_group_Attack(sld, Pchar);
			}
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			SetFunctionExitFromLocationCondition("SharkGoldFleetExitPO", pchar.location, false);
		break; 
		
		case "SharkGoldFleet_09":
			dialog.text = "Chwileczkę... Proszę bardzo. Następnie zapiszę twoje imię w liście zwrotnym. Proszę, oto on. Pamiętaj: masz dziesięć dni! W międzyczasie przeczytam dokładniej, co mi przyniosłeś.";
			link.l1 = "Tak, pamiętam. Do widzenia!";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "MoneySpeak";
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			AddQuestRecord("SharkGoldFleet", "17");
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
		break;
		
		case "SharkGoldFleet_11":
			dialog.text = "Zapłata?..";
			link.l1 = "W Caracas twój kolega powiedział mi, że zapłacisz za dostarczenie listu.";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "Nie, cóż, oni tam zupełnie zwariowali! Teraz muszę za nich płacić!";
			link.l1 = "... ";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "Ile ci obiecali?";
			link.l1 = "Pięć tysięcy pesos.";
			link.l1.go = "SharkGoldFleet_14";
			link.l2 = "Dziesięć tysięcy pesos.";
			link.l2.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_14":
			pchar.questTemp.SharkGoldFleet = 5000;
			dialog.text = "Najwyraźniej postanowili tam żyć na mój koszt... Nie dość, że nie chcą wydawać pieniędzy na kurierów, powierzając takie sprawy przepływającym statkom handlowym, to jeszcze obarczają mnie wydatkami! Napiszę na nich skargę do Hawany!";
			link.l1 = "Rozumiem twoje oburzenie, senor, ale co mam zrobić?";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_15":
			pchar.questTemp.SharkGoldFleet = 10000;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeOfficersLoyality("bad", 1);
			dialog.text = "Najwyraźniej postanowili tam żyć na mój koszt... Nie dość, że nie chcą wydawać pieniędzy na kurierów, powierzając takie sprawy przepływającym statkom handlowym, to jeszcze obciążają mnie kosztami! Napiszę na nich skargę do Hawany!";
			link.l1 = "Rozumiem twoje oburzenie, senor, ale co mam zrobić?";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "Argh, nie można cię winić za chciwość urzędników Nowej Hiszpanii w Caracas. Ale po prostu nie mam teraz przy sobie takich pieniędzy. A budżet powinien nadejść dopiero jutro... Poczekaj tutaj, proszę, pójdę teraz do lichwiarza - i zaraz wrócę.";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			LAi_SetStayType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto2");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1","SGF_toUsurer", -1);
		break;
		
		case "SharkGoldFleet_18":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.SharkGoldFleet));
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("target_month_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			AddQuestRecord("SharkGoldFleet", "18");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			LAi_SetHuberType(npchar);
			Lai_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			dialog.text = "Przepraszam za czekanie. Oto twój "+makeint(pchar.questTemp.SharkGoldFleet)+" kawałki ośmiu. A w tym przypadku oni sami zapłacą za odpowiedź w Caracas. Powiedz mi, co zrobiłem.";
			link.l1 = "Dobrze, przekażę to. Dziękuję i powodzenia!";
			link.l1.go = "exit";
			pchar.questTemp.SharkGoldFleet = "LightVar";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
