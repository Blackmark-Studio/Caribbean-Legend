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
				dialog.text = "Czego chcesz? A-ha, jesteś uczestnikiem regaty! Czy mam rację?";
				link.l1 = "Dokładnie, panie. Muszę się tu zarejestrować zgodnie z zasadami.";
				link.l1.go = "Regata_check";
				break;
			}
			//регата
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania?","Czego chcesz, "+GetAddress_Form(NPChar)+"?"),"Już próbowałeś zadać mi pytanie "+GetAddress_Form(NPChar)+"...","Już trzeci raz dzisiaj mówisz o jakimś pytaniu...","Patrz, jeśli nie masz niczego do powiedzenia mi o sprawach portu, to nie zawracaj mi głowy swoimi pytaniami.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie.","Nie mam o czym rozmawiać."),"Nieważne.","Rzeczywiście, już trzeci raz...","Przykro mi, ale na razie nie interesują mnie sprawy portu.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Грани справедливости
			if (CheckAttribute(pchar, "questTemp.GS_Portman"))
			{
				link.l1 = "Dotarły do mnie plotki, że dokonano na was zamachu i próbujecie znaleźć napastnika?";
				link.l1.go = "GS_Portman_1";
			}
			if (CheckAttribute(pchar, "questTemp.GS_NaemnikMertv"))
			{
				link.l1 = "Człowiek, który targnął się na wasze życie, poległ, panie "+npchar.lastname+". Nic już wam nie grozi.";
				link.l1.go = "GS_Portman_6";
			}
			//<-- Грани справедливости

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
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
			dialog.text = "Hm... Złamałeś zasady regat i muszę cię zdyskwalifikować. Przykro mi. Nie bierzesz udziału w następnym rejsie. Już przygotowałem depeszę do Port-Royal.";
			link.l1 = "Ups... co za szkoda! Ale nic tu nie poradzę, byłeś zbyt czujny. Żegnaj!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Regata");
			pchar.quest.Regata_PU.over = "yes"; // mitrokosta снимаем прерывание
			AddQuestRecord("Regata", "45");
			CloseQuestHeader("Regata");
			}
			else
			{
			pchar.questTemp.Regata.FirstTransitionTime = GetPastTime("hour", sti(pchar.questTemp.Regata.StartYear), sti(pchar.questTemp.Regata.StartMonth), sti(pchar.questTemp.Regata.StartDay), stf(pchar.questTemp.Regata.StartTime), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());//истратил ГГ в часах на 1 переход
			dialog.text = "Zarejestrujmy się: kapitanie "+GetFullName(pchar)+", statek jest "+pchar.Ship.Name+"... czas regat w godzinach to "+sti(pchar.questTemp.Regata.FirstTransitionTime)+"Zrobione, twój wynik został zarejestrowany, możesz kontynuować swoją drogę.";
			link.l1 = "Powiedz mi moją rangę.";
			link.l1.go = "Regata_info";
			}
		}
		else
		{
			dialog.text = "Jesteś tutaj, ale nie widzę twojego statku. Gdzie on jest?";
			link.l1 = "Przepraszam, panie. Natychmiast przeniosę mój statek do portu.";
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
				if (pchar.questTemp.Regata.AdversaryFirstTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FirstTransitionTime))
				{
					n++;
					sName = pchar.questTemp.Regata.AdversaryName.(sTemp);//имя ближайшего противника
					sShip = pchar.questTemp.Regata.AdversaryShipName.(sTemp);//его корабль
				}
			}
			if (n==1)
			{
			dialog.text = "Jesteś na prowadzeniu. Gratulacje! Tak trzymaj!";
			link.l1 = "Dzięki!";
			link.l1.go = "exit";
			AddQuestRecord("Regata", "4");
			}
			else
			{
				if (n==6)
				{
				dialog.text = "Jesteś ostatni. Powinieneś się pospieszyć.";
				link.l1 = "Jestem w drodze!";
				link.l1.go = "exit";
				AddQuestRecord("Regata", "9");
				}
				else
				{
					if (n==2)
					{
					dialog.text = "Jesteś drugi. Przywódca to "+sName+" na statku "+sShip+"Przypuszczam, że wciąż możesz go prześcignąć.";
					link.l1 = "Dzięki! Spróbuję!";
					link.l1.go = "exit";
					AddQuestRecord("Regata", "5");
					}
					else
					{
					dialog.text = "Twoja ranga to "+n+". Twój najbliższy przeciwnik to "+sName+" na statku "+sShip+".";
					link.l1 = "Dzięki!";
					link.l1.go = "exit";
					if (n==3) AddQuestRecord("Regata", "6");
					if (n==4) AddQuestRecord("Regata", "7");
					if (n==5) AddQuestRecord("Regata", "8");
					}
				}
			}
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			npchar.quest.regatatalk = "true";
			pchar.questTemp.Regata.Beliz = "true";//отметка Белиза
			pchar.quest.Regata_Check1.win_condition.l1 = "location";
			pchar.quest.Regata_Check1.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Check1.function = "RegataCheck";//проверка 1
			pchar.quest.Regata_Check2.win_condition.l1 = "location";
			pchar.quest.Regata_Check2.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Check2.function = "RegataCheck";//проверка 2
			pchar.quest.Regata_Check.win_condition.l1 = "location";
			pchar.quest.Regata_Check.win_condition.l1.location = "Hispaniola2";
			pchar.quest.Regata_Check.function = "RegataCheck";//проверка 3
			pchar.questTemp.Regata.AttackIsland = "Cuba1";
			pchar.questTemp.Regata.AttackNation = SPAIN;
			pchar.quest.Regata_Attack.win_condition.l1 = "location";
			pchar.quest.Regata_Attack.win_condition.l1.location = "Cuba1";
			pchar.quest.Regata_Attack.function = "RegataAttack_Lugger";//первая засада у Сантьяго
			pchar.quest.Regata_Hunter.win_condition.l1 = "location";
			pchar.quest.Regata_Hunter.win_condition.l1.location = "Cuba2";
			pchar.quest.Regata_Hunter.function = "RegataAttack_Hunter";//ДУ у Гаваны
			pchar.questTemp.Regata.Town = "Portpax";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Portpax_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
		break;
		//регата
		
		//--> Грани справедливости
		case "GS_Portman_1":
			dialog.text = "Zamach rzeczywiście miał miejsce, to prawda. Ale jeśli chodzi o poszukiwania... to trochę inaczej. Nie potrzebuję zbiegłego przestępcy – potrzebuję jego głowy. Tylko wtedy odzyskam spokój.";
			Link.l1 = "Macie podejrzenia, kto na was napadł i dlaczego?";
			Link.l1.go = "GS_Portman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "GS_Portman_2":
			dialog.text = "Ja... Nie wiem, kim on jest! Nie wiem, skąd się wziął i po co mnie zaatakował. Ale jedno jest pewne – chciał mojej śmierci. A teraz... teraz ja chcę jego śmierci z tą samą furią! Rozumiecie mnie?\nWięc zostawcie te bezużyteczne pytania. Wasza ciekawość mnie nie interesuje, tylko czyny mogą mi pomóc. Dwieście dubonów za jego głowę – oto moja cena. Szukajcie go albo nie traćcie mojego czasu na puste gadanie.";
			Link.l1 = "Rozumiem, że strach i złość zaćmiewają wam umysł i nawet wybaczę wam ten ton. Ale weźcie się w garść. Nie widzę kolejki chętnych do rozwiązywania waszych problemów, więc ostudźcie zapał. Dwieście dubonów mi odpowiada, ale zanim się za to zabiorę, muszę wiedzieć wszystko.";
			Link.l1.go = "GS_Portman_3";
			Link.l2 = "Wasze słowa to tylko puste gadanie, a wskazówek brak. Szukanie nie wiadomo kogo w dżungli to jak szukanie igły w stogu siana. Nie zamierzam marnować czasu na bezsensowne poszukiwania. Życzę wam powodzenia. Na pewno się przyda.";
			Link.l2.go = "GS_Portman_End";
		break;
		
		case "GS_Portman_End":
			DialogExit();
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
		break;
		
		case "GS_Portman_3":
			dialog.text = "Argh... Proszę wybaczyć, "+GetAddress_Form(NPChar)+", jestem cały w nerwach... Co dokładnie chcecie wiedzieć?";
			Link.l1 = "Zapamiętaliście jakieś cechy, które pomogą mi go rozpoznać? Był sam czy za nim stoi ktoś potężniejszy? Im więcej powiecie, tym szybciej zaznacie spokoju.";
			Link.l1.go = "GS_Portman_4";
		break;
		
		case "GS_Portman_4":
			dialog.text = "Jaki wróg?! Nie mam żadnych wrogów! I nigdy nie miałem! Nie robię niczego, co zasługiwałoby na śmierć w biały dzień na środku ulicy\nTen łotr... to po prostu wściekły szaleniec, jakich pełno w tych kolonialnych osadach\nJeśli chodzi o miejsce, gdzie go szukać... myślę, że ukrywa się w dżungli. W tych przeklętych lasach łatwo się zgubić, ale jestem pewien – skieruje się do grot lub zatok, tam łatwiej się schować\nCo do wyglądu – twarz zakryta chustą, na głowie kapelusz, a uzbrojony bardziej niż królewski strażnik. Nie było czasu przyjrzeć się lepiej.";
			Link.l1 = "Cóż, informacji niewiele, ale wystarczy, by zacząć poszukiwania. Wyruszam natychmiast. Nie chowajcie złota za głęboko – wkrótce wrócę.";
			Link.l1.go = "GS_Portman_5";
		break;
		
		case "GS_Portman_5":
			DialogExit();
			AddQuestRecord("GS", "2");
			DeleteAttribute(pchar, "questTemp.GS_Portman");
			
			PChar.quest.GS_Peshera.win_condition.l1 = "location";
			PChar.quest.GS_Peshera.win_condition.l1.location = "Beliz_Cave";
			PChar.quest.GS_Peshera.function = "GS_Peshera";
			locations[FindLocation("Beliz_Cave")].DisableEncounters = true;
			
			PChar.quest.GS_Peshera_pusto.win_condition.l1 = "location";
			PChar.quest.GS_Peshera_pusto.win_condition.l1.location = "Beliz_Cave_2";
			PChar.quest.GS_Peshera_pusto.function = "GS_Peshera_pusto";
		break;
		
		case "GS_Portman_6":
			dialog.text = "Znakomicie, "+GetFullName(pchar)+"! To po prostu znakomite! Udowodniłeś, że twoje mistrzostwo nie ma sobie równych. Oto twoja nagroda – dwieście dublonów. Proszę, odbierz ją!";
			Link.l1 = "Dziękuję! Ale powiedzcie, czy nie macie podstaw sądzić, że zabójcę wynajął ktoś z waszych byłych klientów?";
			Link.l1.go = "GS_Portman_7";
			AddItems(pchar, "gold_dublon", 200);
			DelLandQuestMark(npchar);
		break;

		case "GS_Portman_7":
			dialog.text = "Byli klienci?.. Co za bzdury!.. Jestem uczciwym człowiekiem, a moje interesy zawsze były czyste! Ale skoro mi pomogłeś, opowiem. Niedawno przyszli do mnie piraci. Oferowali mi sprzedaż informacji o statkach handlowych za pieniądze. Odmówiłem, a oni rzucili na mnie groźby i przekleństwa, a potem odeszli. Myślę, że ten zabójca to ich robota. Nie znoszą odmowy.";
			Link.l1 = "W takim razie, dbajcie o siebie. Kto wie, ilu jeszcze najemnych zabójców wyślą ci, jak to ujęliście, 'piraci'. Zatem muszę się pożegnać, obowiązki czekają.";
			Link.l1.go = "GS_Portman_8";
		break;

		case "GS_Portman_8":
			dialog.text = "Poczekajcie, kapitanie. Chcę jeszcze raz wam podziękować. Oprócz pieniędzy, zasłużyliście na moje uznanie. Dopóki jestem tutaj szefem portu, możecie zostawiać swój statek tutaj na dowolny czas z pięćdziesięcioprocentową zniżką. Co sądzicie o takiej propozycji?";
			Link.l1 = "To bardzo hojnie z waszej strony! Jeszcze raz dziękuję!";
			Link.l1.go = "GS_Portman_9";
		break;

		case "GS_Portman_9":
			dialog.text = "A ja jeszcze raz dziękuję wam za wykonaną pracę. Jestem pewien, że jeśli niepotrzebne myśli nie będą was rozpraszać, wasze interesy nadal będą tak samo udane jak dziś. Do widzenia, kapitanie.";
			Link.l1 = "Do widzenia.";
			Link.l1.go = "GS_Portman_10";
		break;

		case "GS_Portman_10":
			DialogExit();
			AddQuestRecord("GS", "4");
			CloseQuestHeader("GS");
			DeleteAttribute(pchar, "questTemp.GS_NaemnikMertv");
			pchar.questTemp.GS_BelizSkidka = true;
		break;
		//<-- Грани справедливости
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
