void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Błąd. Upewnij się, że poinformujesz deweloperów.";
			link.l1 = "Dobrze";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarginCap":
			dialog.text = "Witam, kapitanie. Czy czegoś ode mnie potrzebujesz?";
			link.l1 = "Tak. Dokładnie, "+GetAddress_FormToNPC(NPChar)+"  Jest pasażer na twoim statku, którym jestem bardzo zainteresowany. Nazywam się "+pchar.GenQuest.Marginpassenger.q1Name+"Chcę, aby twój pasażer stał się moim pasażerem. Jeśli ci to odpowiada, wtedy się rozstaniemy i już nigdy więcej się nie zobaczymy.";
			link.l1.go = "MarginCap_1";
		break;
	
		case "MarginCap_1":
			dialog.text = "Czyżby? A co jeśli powiem nie?";
			link.l1 = "W takim razie będę musiał zmusić cię do przemyślenia swojej decyzji kilkoma salwami z moich dział, które w tej chwili są skierowane w twoim kierunku. Nie próbuj swojego szczęścia, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "MarginCap_2";
		break;
		
		case "MarginCap_2":
			int MCparam = (7-sti(RealShips[sti(pchar.ship.type)].Class))*100+sti(pchar.ship.Crew.Morale)+sti(pchar.Ship.Crew.Exp.Sailors)+sti(pchar.Ship.Crew.Exp.Cannoners)+sti(pchar.Ship.Crew.Exp.Soldiers);
			int NPCparam = (7-sti(RealShips[sti(npchar.ship.type)].Class))*100+sti(npchar.ship.Crew.Morale)+sti(npchar.Ship.Crew.Exp.Sailors)+sti(npchar.Ship.Crew.Exp.Cannoners)+sti(npchar.Ship.Crew.Exp.Soldiers);
			if (MCparam > NPCparam)//отдаст сам
			{
				dialog.text = "Nie mam więc wyboru. Los mojej załogi jest dla mnie cenniejszy niż los jednego człowieka. Ale nie ujdzie ci to na sucho! Nie zapomnę tego!";
				link.l1 = "Spokojnie, oszczędź sobie zawału serca... Przyprowadź mi mojego nowego pasażera!";
				link.l1.go = "MarginCap_3";
			}
			else
			{
				dialog.text = "Radziłbym ci opuścić mój statek, panie, póki jeszcze ci na to pozwalam. Nie próbuj mnie straszyć. I nie waż się atakować mojego statku, w przeciwnym razie zostaniesz natychmiast odparty. Wynoś się, póki jestem jeszcze w dobrym nastroju!";
				link.l1 = "Zostałeś ostrzeżony. Jestem w drodze. Do zobaczenia wkrótce, "+GetAddress_FormToNPC(NPChar)+"!";
				link.l1.go = "MarginCap_4";
			}
		break;
	
		case "MarginCap_3":
			DialogExit();
			npchar.Dialog.CurrentNode = "MarginCap_repeat";
			//отдаем пассажира
			sld = GetCharacter(NPC_GenerateCharacter("MarginPass", pchar.GenQuest.Marginpassenger.model, pchar.GenQuest.Marginpassenger.sex, pchar.GenQuest.Marginpassenger.ani, 2, sti(pchar.GenQuest.Marginpassenger.Nation), -1, true, "quest"));
			sld.Dialog.Filename = "Quest\Marginpassenger.c";
			sld.Dialog.currentnode = "MarginPass";
			sld.name = pchar.GenQuest.Marginpassenger.q1Name;
			sld.lastname = "";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			Map_ReleaseQuestEncounter(npchar.id);
			npchar.Abordage.Enable = false; // запрет абордажа
			npchar.ShipEnemyDisable = true;
			npchar.AlwaysFriend = true;
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_4":
			DialogExit();
			NextDiag.CurrentNode = "MarginCap_repeat";
			pchar.GenQuest.Marginpassenger.Mustboarding = "true";
			AddQuestRecord("Marginpassenger", "5");
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -1);
		break;
		
		case "MarginCap_repeat":
			dialog.text = "Już rozmawialiśmy, pamiętasz? Zabieraj się z mojego statku!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarginCap_repeat";
		break;
		
		case "MarginCap_abordage":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Mustboarding"))
			{
				dialog.text = "Argh, łajdaku! Płoń w piekle za swe czyny!";
				link.l1 = "Zaproponowałem, abyś oddał mi pasażera po dobroci... a ty odrzuciłeś moją ofertę. Teraz tylko ty jesteś winny!";
				link.l1.go = "MarginCap_abordage_1";
			}
			else
			{
				dialog.text = "Argh, bękarcie! Dlaczego zaatakowałeś spokojny statek? Nie mamy złota ani cennych towarów!";
				link.l1 = "Ale masz na pokładzie cenną osobę..."+pchar.GenQuest.Marginpassenger.q1Name+"Chcę twojego pasażera.";
				link.l1.go = "MarginCap_abordage_2";
			}
		break;
		
		case "MarginCap_abordage_1":
			dialog.text = "Ty... jesteś plugawym piratem!";
			link.l1 = "Mniej gadania, przyjacielu...";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_2":
			dialog.text = "I dlatego dokonałeś rzezi na moim statku? Wielu ludzi nie żyje! Piracie!";
			link.l1 = "Mniej gadania, przyjacielu...";
			link.l1.go = "MarginCap_abordage_3";
		break;
		
		case "MarginCap_abordage_3":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Marginpassenger_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "MarginNeed":
			dialog.text = "Czego chcesz, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Jesteś "+pchar.GenQuest.Marginpassenger.q2Name+"?";
			link.l1.go = "MarginNeed_1";
		break;
		
		case "MarginNeed_1":
			dialog.text = "Tak, to ja. Czy chcesz złożyć wniosek? W takim razie powinieneś wiedzieć, że...";
			link.l1 = "Chwileczkę, panie. Mam nieco inny rodzaj prośby... Czy znasz kogoś o imieniu "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1.go = "MarginNeed_2";
		break;
		
		case "MarginNeed_2":
			switch (pchar.GenQuest.Marginpassenger.sex)
			{
				case "woman":
					dialog.text = "Tak, znam ją... Oczywiście, że znam! Co się stało?";
					link.l1 = "Ona wplątała się w bardzo nieprzyjemną historię: jej statek został przejęty przez piratów. Na szczęście, miałem okazję wejść na ich statek i uratować biedną duszę. Powiedziała mi twoje imię i oto jestem.";
					link.l1.go = "MarginNeed_woman";
				break;
				case "man":
					dialog.text = "Tak, znam tego człowieka bardzo dobrze. O co chodzi?";
					link.l1 = "On wpakował się w bardzo nieprzyjemną historię: jego statek został zdobyty przez piratów. Na szczęście, udało mi się wejść na ich statek i uratować tego więźnia. Powiedział mi twoje imię i oto jestem.";
					link.l1.go = "MarginNeed_man";
				break;
			}
		break;
		
		case "MarginNeed_woman":
			dialog.text = "O Boże! Gdzie ona teraz jest? Dlaczego jej tu nie przyprowadziłeś?";
			link.l1 = "Jest bezpieczna. A jeśli chodzi o twoje pytanie... to nie takie proste. Mogłem ją sam zabrać do domu, ale mogę dać ci tę okazję. Oczywiście za niewielką opłatą.";
			link.l1.go = "MarginNeed_woman_1";
		break;
		
		case "MarginNeed_woman_1":
			dialog.text = "Hm... Nie rozumiem...";
			link.l1 = "Czemu nie? Zapłacisz mi złotem, dam ci dziewczynę i będziesz mógł wykorzystać tę sytuację dla swoich celów... Chcesz się z nią ożenić, prawda? A ja naprawię mój statek za te monety, został uszkodzony podczas tej walki z piratami.";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_man":
			dialog.text = "O Boże! Gdzie on teraz jest? Dlaczego go tu nie przyniosłeś?";
			link.l1 = "On jest bezpieczny. A co do twojego pytania... to nie jest takie proste. Mogłem go sam zabrać do domu, ale mogę dać ci tę możliwość, zważywszy że masz swoje własne interesy w jego rodzinie. Oczywiście za niewielką opłatą.";
			link.l1.go = "MarginNeed_man_1";
		break;
		
		case "MarginNeed_man_1":
			dialog.text = "Hm... Nie rozumiem...";
			link.l1 = "Czemu nie? Zapłacisz mi złotem, oddam ci twojego przyjaciela i będziesz mógł wykorzystać tę sytuację na swoją korzyść. Mam pewne informacje, wiesz... Naprawię mój statek za te monety, został uszkodzony podczas tej walki z piratami.";
			link.l1.go = "MarginNeed_money";
		break;
		
		case "MarginNeed_money":
			dialog.text = "„No cóż... a ile chcesz?”";
			link.l1 = "Rozważ, że chcę dublony, nie peso.";
			link.l1.go = "MarginNeed_money_1";
		break;
		
		case "MarginNeed_money_1":
			dialog.text = "Dobrze, dobrze... Ile dublonów chcesz?";
			Link.l1.edit = 1;			
			link.l1 = "";
			link.l1.go = "MarginNeed_money_2";
		break;
		
		case "MarginNeed_money_2":
		iTemp = sti(dialogEditStrings[1]);
		int iSum = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*5*stf(pchar.GenQuest.Marginpassenger.Chance));
		if (iTemp <= 0)
		{
			dialog.text = "Bardzo zabawne. Dobrze, udawajmy, że twój żart był zabawny. Żegnaj!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 0 && iTemp <= iSum)
		{
			if (hrand(2) > 1) // Addon-2016 Jason уменьшаем раздачу дублонов
			{
				dialog.text = "Zgoda, zgadzam się. Posiadam wymaganą sumę. Gdzie jest "+pchar.GenQuest.Marginpassenger.q1Name+"?";
				link.l1 = "Musisz być już na molo. Więc możesz iść i zabrać pasażera.";
				link.l1.go = "MarginNeed_dublon";
			}
			else
			{
				dialog.text = "Przykro mi, ale nie mam tylu dublonów. Czy peso będą w porządku?";
				link.l1 = "Chcę dublonów, ale przypuszczam, że kapitan statku przyjmie pesos... Daj mi je.";
				link.l1.go = "MarginNeed_peso";
				link.l2 = "Nie, potrzebuję tylko dublonów.";
				link.l2.go = "MarginNeed_dublon_exit";
			}
			break;
		}
		if (iTemp > iSum && iTemp < 1000)
		{
			dialog.text = "Niestety, nie mam takiej sumy. Więc nie mogę przyjąć twojej propozycji, nawet jeśli bardzo bym tego chciał.";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
		if (iTemp > 1000 && iTemp < 3000)
		{
			dialog.text = "Panie, czy ty w ogóle rozumiesz, o czym mówisz? Czy jesteś świadom, że ta suma jest zbyt ogromna? Wynoś się stąd do diabła!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
			break;
		}
			dialog.text = "Cóż... Panie, musisz natychmiast udać się do lekarza. Wygląda na to, że masz bardzo silną gorączkę lub... w każdym razie, potrzebujesz lekarza. A ja jestem zbyt zajęty. Żegnaj!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_dublon":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1]);
			TakeNItems(pchar, "gold_dublon", iTemp);
			AddQuestRecord("Marginpassenger", "9");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
		
		case "MarginNeed_peso":
			dialog.text = "Oto jest, cała suma w pesos, dokładnie to, czego chciałeś... Gdzie jest "+pchar.GenQuest.Marginpassenger.q1Name+"?";
			link.l1 = "Musi być już na molo. Więc możesz iść po pasażera..";
			link.l1.go = "MarginNeed_peso_1";
		break;
		
		case "MarginNeed_peso_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			npchar.lifeday = 0;
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			iTemp = sti(dialogEditStrings[1])*100;
			AddMoneyToCharacter(pchar, iTemp);
			AddQuestRecord("Marginpassenger", "10");
			AddQuestUserData("Marginpassenger", "sSum", FindRussianMoneyString(iTemp));
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddCharacterExpToSkill(pchar, "Fortune", 80);//везение
		break;
		
		case "MarginNeed_dublon_exit":
			dialog.text = "Nie mogę wtedy przyjąć twojej propozycji, nawet z całym moim pragnieniem, aby to zrobić. Żegnaj!";
			link.l1 = "Hm...";
			link.l1.go = "MarginNeed_exit";
		break;
		
		case "MarginNeed_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Marginpassenger", "11");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
			// belamour gen: Добряку недолго осталось -->
			if(CheckAttribute(pchar, "questTemp.LongHappy"))
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Puerto Principe, to the Black Pastor");
			}
			else
			{
				AddQuestUserData("Marginpassenger", "sBaron", "to Le Francois, to Kindly Jacques");
			}
			// <-- belamour gen
			pchar.GenQuest.Marginpassenger = "cabin";
		break;
		
		case "MarginPass":
			dialog.text = "Co się... Co się tutaj dzieje?!";
			link.l1 = "To jest bardzo proste, "+NPCharSexPhrase(NPChar,"kamrat","dziewczyna")+"  Jesteś teraz moim drogim pasażerem. Pilnie strzeżonym pasażerem. Nie próbuj się opierać, bo skończysz w ładowni.";
			link.l1.go = "MarginPass_1";
		break;
		
		case "MarginPass_1":
			dialog.text = "Czy chcesz powiedzieć, że jestem twoim więźniem?";
			link.l1 = "O, nie. Oczywiście, że nie. Nie więzień, lecz drogi gość. Bardzo wartościowy gość...";
			link.l1.go = "MarginPass_2";
		break;
		
		case "MarginPass_2":
			dialog.text = "Ty... zapłacisz za swoje czyny!";
			link.l1 = "Znowu się mylisz,"+NPCharSexPhrase(NPChar,", kumpel",", drogi")+"Nie zapłacę, ale to mnie mają zapłacić. Dość gadania, idź do swojej kajuty!";
			link.l1.go = "MarginPass_3";
		break;
		
		case "MarginPass_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "", "", "none", "", "", "", 1.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.Marginpassenger_InWorldOver.over = "yes"; //снять прерывание
			pchar.quest.Marginpassenger_Sink.over = "yes"; //снять прерывание
			pchar.GenQuest.Marginpassenger = "take";
			if (rand(2) == 1) pchar.GenQuest.Marginpassenger.lose = "true";
			else Marginpassenger_CreateNeedman();
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.Boarding")) AddQuestRecord("Marginpassenger", "6");
			else AddQuestRecord("Marginpassenger", "4");
			AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Acc")));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
