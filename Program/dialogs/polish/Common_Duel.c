//navy 26.07.06
//генератор дуэлей...
//в диалоге НПС делаем линк с проверкой флага оскорбления... по нему переход на "outraged"
//если НПС сделал что-то ГГ (продажа фальшивки) или ГГ наехал на НПС, вешаем на него флаг.
//для некоторых, например ПГГ, можно делать переход сразу на вызов: "let_s_duel"
void ProcessDuelDialog(ref NPChar, aref Link, aref NextDiag)
{
	int iHour;
	string sLocation;

	//флаг убираем
	DeleteAttribute(NPChar, "Outrage");
    switch (Dialog.CurrentNode)
	{
	case "outraged":
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Jak śmiesz mnie obrażać, łotrze?!","Te słowa będą cię drogo kosztować!"),RandPhraseSimple("Znieważyłeś mój honor, "+GetAddress_Form(NPChar)+"Zapłacisz za to.","Jak śmiesz? Natychmiast cofnij swoje słowa!"));

		//это такая засада.. чтобы читали текст :)
		MakeRandomLinkOrderTwo(link, 
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("Ha?! I don't even want to stain my sword with your blood!", "Ha?! I don't even want to stain my sword with your blood!"), 
				RandPhraseSimple("I am always at your service!", "I am not going to choose words while speaking with the rabble!")), "outraged_1",
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("I didn't mean it!", "I fired up..."), 
				RandPhraseSimple("That was a mistake. I am sorry.", "I took you for someone else, " + GetAddress_FormToNPC(NPChar) + ". Please forgive me.")), "change_mind");
		break;

	case "outraged_1":
		Dialog.Text = NPCharRepPhrase(NPChar,RandPhraseSimple("Utnę ci uszy!","Wypruję ci serce!"),RandPhraseSimple(" Mam nadzieję, że usłyszę twoje wymówki, bo inaczej nie mogę zagwarantować, że się opanuję!","Czy zdajesz sobie sprawę, co to oznacza... czyż nie?"));

		MakeRandomLinkOrderTwo(link,
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("I hope that your saber is as swift as your tongue!", "My blade will speak for me."), 
				RandPhraseSimple("I challenge you to a duel!", "That's a matter of honor!")), "let_s_duel",
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("I think I am not ready yet!", "Think, we shouldn't get excited! These are words only!"), 
				RandPhraseSimple("I remembered, I am waiting. All blessings...", "Ah! Seems, my ship is sailing already. Bye.")), "change_mind");
		break;

	case "let_s_duel":
		//проверка на начатые дуэли.
		if (CheckAttribute(PChar, "questTemp.duel.Start") && int(PChar.questTemp.duel.Start))
		{
			Dialog.Text = "Najpierw załatw sprawy z innymi, a potem porozmawiamy.";
			if (PChar.questTemp.duel.enemy == NPChar.id)
			{
				Dialog.Text = "Już doszliśmy do porozumienia.";
			}
			link.l1 = RandSwear()+"Och, jak mogłem zapomnieć...";
			link.l1.go = "exit";
			break
		}
		//может отказаться.
		if (rand(100) < 30)
		{
			Dialog.Text = RandPhraseSimple("Pojedynek?! Zjeżdżaj, nie jesteś wart, by marnować na ciebie czas."," Pojedynek? Nie zasługujesz na ten zaszczyt! Zjeżdżaj! ");
			link.l1 = RandPhraseSimple("Dobrze...","Chyba mogę poczekać...");
			link.l1.go = "exit";
/**/
			//можно дать возможность драться полюбому :)			
			if (rand(100) < 30)
			{
				link.l1 = RandPhraseSimple("Tak myślisz? Nie bądź taki pewny, drańu!!!","O, naprawdę?! Zobaczę, jakiego koloru jest twoja krew!");
				link.l1.go = "fight_right_now";
			}
/**/
			break;
		}

		//согласен.
		Dialog.Text = RandPhraseSimple("Pojedynek, mówisz? To mi pasuje. Szable i pistolety będą naszą bronią.","Potrafisz w ogóle trzymać miecz?");
		link.l1 = RandPhraseSimple("Będziesz błagać o litość, klęcząc na kolanach.","Uduszę cię gołymi rękami, łotrze!");
		link.l1.go = "land_duel";
		if (int(pchar.Ship.Type) != SHIP_NOTUSED && int(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			Dialog.Text = RandPhraseSimple(Dialog.Text+" A możemy wypłynąć na morze i zobaczyć, kto jest kim!","Pojedynek?!! Ha, rozgniotę cię jak robaka! Wybierz, jak chcesz umrzeć!");
			link.l2 = RandPhraseSimple("Na morzu, jestem najlepszym z nich wszystkich.","Moja łajba łatwo zatopi twój stary koryto!");
			link.l2.go = "sea_duel";
		}
		link.l3 = "Zmieniam zdanie...";
		link.l3.go = "change_mind";
		break;

	//дуэль на подводных лодках :))))
	case "sea_duel":
		Dialog.Text = RandPhraseSimple("Nie widzę twojego statku w porcie...","Zjeżdżaj, dopóki nie znajdziesz chociażby jakiejś starej łajby!");
		link.l1 = RandPhraseSimple("Moja pomyłka...","W takim razie zostawiam cię.");
		link.l1.go = "exit";
		if (pchar.location.from_sea == GetCurrentTown() + "_town")
		{
			Dialog.Text = "Dobrze, będę czekał na ciebie przy wyjściu z zatoki...";
			link.l1 = "Nie każę ci czekać zbyt długo.";

			pchar.questTemp.Duel.enemy = NPChar.id;
			pchar.questTemp.Duel.Sea_Location = Islands[GetCharacterCurrentIsland(PChar)].id;
			AddDialogExitQuestFunction("Duel_Sea_Prepare");
		}

		break;

	//на суше
	case "land_duel":
		iHour = 1 + rand(2);
		if (GetTime() > 4.0 && GetTime() < 17.0)
		{
//			iHour = int(18.0 - GetTime()) + rand(2); //раскоментировать для дуэлей только по ночам
		}
		pchar.questTemp.Duel.WaitTime = iHour;
		Dialog.Text = RandSwear()+RandPhraseSimple("Do broni, i zobaczmy, jakiego koloru jest twoja krew!","Cóż, jeśli chcesz śmierci...");
		link.l1 = RandPhraseSimple("Lepiej pójdźmy w miejsce, gdzie nie ma zbyt wielu świadków. Znam doskonałe miejsce za bramami miasta. Spotkajmy się tam w "+iHour+" godziny.","Trzymaj konie. Takie rzeczy lepiej załatwiać bez świadków. Wejdź "+iHour+"  godziny do wejścia do miasta.");
		link.l1.go = "fight_off_town";
		link.l2 = RandPhraseSimple("No, jeśli tak bardzo chcesz zginąć...","Cholera! Pomogę ci ujrzeć piekło na własne oczy!");
		link.l2.go = "fight_right_now";
		link.l3 = "Zmieniłem zdanie...";
		link.l3.go = "change_mind";

		if (rand(1))
		{
			Dialog.Text = RandSwear()+RandPhraseSimple("Chyba lepiej, żebyśmy przeszli przez bramy miasta. Będę tam na ciebie czekać "+pchar.questTemp.Duel.WaitTime+" godzin. Nie zwlekaj!","To nie jest najlepsze miejsce do rozstrzygania sporów. Lepiej wynieśmy się z miasta. W "+pchar.questTemp.Duel.WaitTime+" godzin będę tam.");
			link.l1 = RandPhraseSimple("Nie zasługujesz na ten zaszczyt! Broń się!","Nie mam czasu! Wyciągaj stal!");
			link.l1.go = "fight_right_now";
			link.l2 = RandPhraseSimple("Dobrze, przejdźmy się.","Pewnie masz rację. Spotkajmy się za bramami.");
			link.l2.go = "fight_off_town_prep";
		}
		break;

	//предложение "пойдём выйдем" рассматривается
	case "fight_off_town":
		Dialog.Text = RandPhraseSimple("Nie zasługujesz na ten zaszczyt! Broń się!","Nie mam czasu! Tu i teraz!");
		link.l1 = RandPhraseSimple("Cóż, jeśli tak bardzo chcesz umrzeć...","Cholercia! Pomogę ci zobaczyć piekło na własne oczy!");
		link.l1.go = "fight_right_now";
		if (rand(1))
		{
			Dialog.Text = RandPhraseSimple("Dobrze, przejdźmy się.","Masz pewnie rację. Spotkajmy się za bramami.");
			link.l1 = RandPhraseSimple("Będę tam na ciebie czekał.","Nie zwlekaj.");
			link.l1.go = "fight_off_town_prep";
		}
		break;

	//что ж, пойдём выйдем
	case "fight_off_town_prep":
		SaveCurrentQuestDateParam("questTemp.Duel.StartTime");
		PChar.questTemp.duel.Start = true;
		PChar.questTemp.duel.enemy = NPChar.id;
		sLocation = GetCurrentTown();
		if (sLocation != "")
		{
			//где?
			sLocation += "_ExitTown";
			pchar.questTemp.duel.place = sLocation;

			Locations[FindLocation(sLocation)].DisableEncounters = true;
			//приходит ко времени.
			pchar.quest.duel_move_opponent2place.win_condition.l1 = "Location";
			pchar.quest.duel_move_opponent2place.win_condition.l1.location = pchar.questTemp.duel.place;
			pchar.quest.duel_move_opponent2place.function = "Duel_Move_Opponent2Place";
			//на случай, если не дождется, часа вполне достаточно
			SetTimerConditionParam("duel_move_opponentBack", "Duel_Move_OpponentBack", 0, 0, 0, int(GetTime() + 0.5) + int(pchar.questTemp.Duel.WaitTime) + 1, false);
			pchar.quest.duel_move_opponentBack.function = "Duel_Move_OpponentBack";
			if (CheckAttribute(NPChar, "CityType"))
			{
				DeleteAttribute(NPChar, "City"); // чтоб не было ругани с нацией
	    		DeleteAttribute(NPChar, "CityType");
				if (!CheckAttribute(NPChar, "PGGAi")) 
				{
					if (!CheckAttribute(NPChar, "LifeDay")) npchar.LifeDay = 0;
					npchar.LifeDay = int(npchar.LifeDay) + 3; // чтоб до дуэли не помер
				}
    		}
		}
		NextDiag.CurrentNode = "let_s_duel";
		DialogExit();
		break;

	//последнее слово перед боем
	case "talk_off_town":
		Dialog.Text = "Zatem, jesteś gotowy?";
		link.l1 = "Tak. Zobaczmy, kto jest lepszym człowiekiem!";
		link.l1.go = "fight_right_now";
		link.l2 = "Nie, postanowiłem przynieść ci przeprosiny. Myliłem się, wpadłem w złość.";
		link.l2.go = "change_mind";
		if (rand(100) < 20)
		{
			Dialog.Text = RandPhraseSimple("Słuchaj, myślałem o tym i teraz widzę, że się myliłem. Przepraszam.","Do diabła! To wszystko przez ten przeklęty rum!!! Przepraszam, "+GetSexPhrase("bracie","siostra")+"!");
			link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Nie, tylko twoja krew może mnie teraz zadowolić!","Wyciągnij broń i przestań być taką płaczącą dziewczynką!"),RandPhraseSimple("Nie! Żądam satysfakcji!","Jesteś hańbą dla swojej rodziny! Dobywaj miecz!"));
			link.l1.go = "fight_right_now";
			link.l2 = NPCharRepPhrase(pchar,RandPhraseSimple("Dobrze, zgadzam się. Trochę się unieśliśmy.","Kto prowadzi rachunki między przyjaciółmi!"),RandPhraseSimple("Pewnie masz rację. Nie powinniśmy przelewać krwi z takich błahych powodów.","Moja hojność nie zna granic! Jesteś wybaczony!"));
			link.l2.go = "peace";
		}
		NextDiag.TempNode = npchar.BackUp.DialogNode;
		pchar.questTemp.Duel.End = true;
		break;

	//дуэли быть!
	case "fight_right_now":
		PChar.questTemp.duel.enemy = NPChar.id;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight_right_now_1":	
		PChar.questTemp.duel.enemy = NPChar.id;
		PChar.questTemp.duel.enemyQty = rand(2) + 1;
		AddDialogExitQuestFunction("Duel_Prepare_Fight");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();	
		break;
		
	//передумал, э... не хорошо ;)
	case "change_mind":
		if (CheckAttribute(pchar, "questTemp.Duel.End")) LAi_SetWarriorType(NPChar);
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("To się zgub!","Zmykaj stąd, zanim zmienię zdanie."),RandPhraseSimple("W takim razie nie będę cię dłużej zatrzymywał!","Lepiej odejdź, zanim zmienię zdanie."));
		link.l1 = "Już odchodzę...";
		link.l1.go = "peace";
		break;

	case "after_peace":
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("Zjeżdżaj!","Zniknij mi z oczu, zanim zmienię zdanie."),RandPhraseSimple("Czy mogę ci pomóc?","Czego sobie życzysz?"));
		link.l1 = "Odchodzę.";
		link.l1.go = "peace";
		break;

	//мир и все такое.
	case "peace":
		LAi_SetWarriorType(NPChar);
		NextDiag.CurrentNode = "after_peace";
		DialogExit();
		break;
	}
}
