// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//регата
			if (CheckAttribute(pchar, "questTemp.Regata.Go") && !CheckAttribute(npchar, "quest.regatatalk"))
			{
				dialog.text = "Czego chcesz? A-ha, jesteś uczestnikiem regat! Mam rację?";
				link.l1 = "Dokładnie, sir. Muszę się tu zarejestrować zgodnie z zasadami.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakiego rodzaju pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Już próbowałeś zadać mi pytanie "+GetAddress_Form(NPChar)+"... ","Już trzeci raz dzisiaj rozmawiasz o tej sprawie...","Spójrz, jeśli nie masz nic do powiedzenia na temat spraw portowych, to nie zawracaj mi głowy swoimi pytaniami.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie.","Nie mam o czym rozmawiać."),"Nieważne.","Rzeczywiście, już trzeci raz...","Przykro mi, ale nie interesują mnie teraz sprawy portu.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Żegluję do Blueweld, by sprzedać trochę papryki. Powiedz mi, panie, czy masz jakichś pasażerów, którzy zmierzają do Blueweld? Albo chociaż do Port-Royal. Byłoby świetnie zarobić trochę pieniędzy na pasażerze, mogłoby to pomóc spłacić wynagrodzenie załogi. Już zredukowałem je do minimum, ale te leniwe dranie wciąż domagają się pieniędzy...";
                link.l1.go = "PortofficeDone";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados")
			{
				link.l1 = "Był galeon o nazwie 'Admirable', załadowany w Philipsburgu pod dowództwem Gaiusa Marchaisa. Miał dostarczyć tutaj ładunek papryki. Czy możesz mi pomóc znaleźć tego kapitana?";
                link.l1.go = "guardoftruth";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.garpiya"))
			{
				if (CheckAttribute(npchar, "questTemp.caleuche"))
				{
					link.l1 = "Chciałem zapytać o szebek o dziwnej nazwie.";
					link.l1.go = "caleuche_2";
				}
				else
				{
					link.l1 = "Słyszałem, że do waszego portu często zawija szebeka kapitana Jacka... czy Jacksona. Czy możesz mi powiedzieć, gdzie go szukać?";
					link.l1.go = "caleuche";
				}
			}
		break;

		//Голландский гамбит
		case "PortofficeDone":
			dialog.text = "Niestety, nie ma pasażerów do Blueweld ani do Port-Royal. Wróć jutro lub pojutrze.";
			link.l1 = "Szkoda. Żegnaj zatem.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-9");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;

		//регата
		case "Regata_check":
		iTest = FindColony(npchar.city); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Sentjons") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "Chm... Złamałeś zasady regat i muszę cię zdyskwalifikować. Przykro mi. Nie bierzesz udziału w następnej podróży. Już przygotowałem depeszę do Port-Royal.";
				link.l1 = "Eh... co za szkoda! Ale nic tu nie mogę zrobić, byłeś zbyt czujny. Żegnaj!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				pchar.questTemp.Regata.FourthTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1+2+3+4 переход
				dialog.text = "Może zauważyłeś, kapitanie, że miasto jest oblężone. Spodziewamy się ataku ze strony Hiszpanów w każdej chwili i mobilizujemy nasze siły. Ale regaty nadal trwają\nZarejestrujmy się: kapitanie "+GetFullName(pchar)+", statek jest - "+pchar.Ship.Name+"... Czas regat w godzinach to "+sti(pchar.questTemp.Regata.FourthTransitionTime)+"Zrobione, twój wynik jest zarejestrowany, możesz kontynuować swoją drogę.";
				link.l1 = "Powiedz mi mój stopień.";
				link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "Jesteś tutaj, ale nie widzę twojego statku. Gdzie on jest?";
			link.l1 = "Przepraszam, panie. Natychmiast przetransportuję mój statek do portu.";
			link.l1.go = "exit";
		}
		break;
		
		case "Regata_info":
			int n=1;
			string sTemp, sName, sShip;
			for (int i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				if (pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FourthTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "Ach, tak... Przepraszam, byłem zbyt zajęty. Jesteś pierwszy.";
			link.l1 = "Rozumiem. Dzięki za informację.";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "22");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Ach, tak... Przepraszam, jestem zbyt zajęty na to. Jesteś ostatni.";
				link.l1 = "Rozumiem. Dzięki za informacje.";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "27");
				}
				else
				{
					if (n==2)
					{
						dialog.text = "Ach, tak... Przepraszam, jestem zbyt zajęty na to. Jesteś drugi. Jest tylko jeden kapitan, który cię wyprzedza. Nazywa się "+sName+" na statku "+sShip+".";
						link.l1 = "Rozumiem. Dziękuję za informacje.";
						link.l1.go = "exit";
						AddQuestRecord("Regata", "23");
					}
					else
					{
						dialog.text = "Ach, tak... Przepraszam, jestem zbyt zajęty na to. Twój stopień to "+n+" . Twój najbliższy przeciwnik to "+sName+" na statku "+sShip+".";
						link.l1 = "Rozumiem. Dziękuję za informacje.";
						link.l1.go = "exit";
						if (n==3) AddQuestRecord("Regata", "24");
						if (n==4) AddQuestRecord("Regata", "25");
						if (n==5) AddQuestRecord("Regata", "26");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Defence", 30);//защита
			AddCharacterExpToSkill(pchar, "Repair", 30);//починка
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 30);//скрытность
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Bridgetown = "true";//отметка Бриджтауна
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Caracas";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check3.win_condition.l1 = "location";
			pchar.quest.Regata_Check3.win_condition.l1.location = "PortoBello";
			pchar.quest.Regata_Check3.function = "RegataCheck";//проверка 3
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Jamaica";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 4
			pchar.questTemp.Regata.AttackIsland = "Curacao";
			pchar.questTemp.Regata.AttackNation = HOLLAND;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Attack.function = "RegataAttack_Brigantine";
			pchar.quest.Regata_Attack1.win_condition.l1 = "location";
			pchar.quest.Regata_Attack1.win_condition.l1.location = "Curacao";
			pchar.quest.Regata_Attack1.function = "RegataAttack_Corvette";//третья засада
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Barbados";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Барбадоса
			pchar.quest.Regata_Finish.win_condition.l1 = "location";
			pchar.quest.Regata_Finish.win_condition.l1.location = "Jamaica";
			pchar.quest.Regata_Finish.function = "RegataFinishSea";
			pchar.quest.Regata_Finish1.win_condition.l1 = "location";
			pchar.quest.Regata_Finish1.win_condition.l1.location = "Portroyal_town";
			pchar.quest.Regata_Finish1.function = "RegataFinishTown";//финиш регаты
			//ситуации
			pchar.quest.Regata_Siege.win_condition.l1 = "location";
			pchar.quest.Regata_Siege.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_Siege.function = "RegataSiegeOfficer";//на квест по вывозу жителей
		break;
		//регата
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "Tak, ten galeon tu był, został uwolniony od swoich towarów i później opuścił nasz port. Informacje o jego destynacji... hm... brak, nie ma nic. Przykro mi, ale nic nie mogę zrobić.";
			link.l1 = "Widzę. Szkoda... Będę dalej go szukać.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			DialogExit();
			AddQuestRecord("Guardoftruth", "13");
			pchar.questTemp.Guardoftruth = "barbados1";
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Proszę pana, potrzebuję dokładnej nazwy statku. Mamy mnóstwo Jacków i Jacksonów przepływających przez nasz port. Więc, jaka to nazwa?";
			link.l1 = "";
			Link.l1.edit = 2;
			link.l1.go = "caleuche_name";
			link.l2 = "Kłopot w tym, że nie znam nazwy jego starej łajby. To dziwne, jakaś ptasia kobieta, urodzona...";
			link.l2.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Panie, idź opowiadać swoje historie i zagadki w tawernie, my tu mamy poważny zakład. Albo mi powiesz nazwę tego szebeka, albo przestań przeszkadzać mi w pracy.";
			link.l1 = "Dobrze, spróbuję się dowiedzieć.";
			link.l1.go = "exit";
			npchar.questTemp.caleuche = "true";
		break;
		
		case "caleuche_2":
			dialog.text = "Więc? Masz nazwę statku? Słucham.";
			link.l1 = " ";
			Link.l1.edit = 2;
			link.l1.go = "caleuche_name";
		break;
		
		case "caleuche_name":
			if (GetStrSmallRegister(dialogEditStrings[2]) == "harpy")
			{
				dialog.text = "'Harpy'? Oczywiście, znam ten szybek. Jego kapitanem jest Reginald Jackson. Ale nie był w Bridgetown od dłuższego czasu. Słyszałem, że teraz pracuje dla Holenderskiej Kompanii Zachodnioindyjskiej. Powinieneś więc szukać go w Willemstad.";
				link.l1 = "Dziękuję bardzo! Bardzo mi pomogłeś.";
				link.l1.go = "caleuche_3";
			}
			else
			{
				dialog.text = "Przykro mi, ale to nic mi nie mówi. Czy jesteś pewien, że twój kapitan kiedykolwiek był tutaj, w Bridgetown?";
				link.l1 = "Jestem pewien. Dobrze, może coś wymyślę ...";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "18");
			pchar.questTemp.Caleuche.Garpiya = "gwik"; 
			npchar.quest.garpiya = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
