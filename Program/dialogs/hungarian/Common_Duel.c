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
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
				RandPhraseSimple("Hogy merészelsz sértegetni, te gazember?!", "Ezek a szavak sokba fognak neked kerülni!"), 
				RandPhraseSimple("Megsértetted a becsületemet, " + GetAddress_Form(NPChar) + "! És ezért meg fogsz fizetni.", "Hogy merészeled? Azonnal vond vissza a szavaidat!"));

		//это такая засада.. чтобы читали текст :)
		MakeRandomLinkOrderTwo(link, 
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("Ha?! Még a kardomat sem akarom bemocskolni a véreddel!", "Ha?! Nem akarom a kardomat a véreddel bemocskolni!"), 
				RandPhraseSimple("Mindig a szolgálatodra állok!", "Nem fogok szavakat választani, miközben a csôcselékkel beszélek!")), "outraged_1",
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("Nem gondoltam komolyan!", "Tüzeltem..."), 
				RandPhraseSimple("Ez hiba volt. Bocsánat.", "Másnak néztelek, " + GetAddress_FormToNPC(NPChar) + ". Kérlek, bocsáss meg nekem.")), "change_mind");
		break;

	case "outraged_1":
		Dialog.Text = NPCharRepPhrase(NPChar,  
				RandPhraseSimple("Levágom a füledet!", "Kivágom a szívedet!"), 
				RandPhraseSimple("Remélem, hogy meghallom a kifogásaidat, különben nem garantálom, hogy uralkodni fogok magamon!", "Felfogod, hogy ez mit jelent... ugye?"));

		MakeRandomLinkOrderTwo(link,
					NPCharRepPhrase(pchar, RandSwear() + 
				RandPhraseSimple("Remélem, hogy a szablyád olyan gyors, mint a nyelved!", "A pengém beszélni fog helyettem."), 
				RandPhraseSimple("Kihívlak párbajra!", "Ez becsület kérdése!")), "let_s_duel",
					NPCharRepPhrase(pchar, 
				RandPhraseSimple("Azt hiszem, még nem állok készen!", "Gondolkodj, ne izguljunk! Ezek csak szavak!"), 
				RandPhraseSimple("Eszembe jutott, várok. Minden áldás...", "Ah! Úgy látszik, a hajóm máris elindult. Viszlát!")), "change_mind");
		break;

	case "let_s_duel":
		//проверка на начатые дуэли.
		if (CheckAttribute(PChar, "questTemp.duel.Start") && sti(PChar.questTemp.duel.Start))
		{
			Dialog.Text = "Elôször intézd el a dolgaidat másokkal, aztán beszélünk.";
			if (PChar.questTemp.duel.enemy == NPChar.id)
			{
				Dialog.Text = "Már megegyeztünk.";
			}
			link.l1 = RandSwear() + "Ó, hogy is felejthettem el...";
			link.l1.go = "exit";
			break
		}
		//может отказаться.
		if (rand(100) < 30)
		{
			Dialog.Text = RandPhraseSimple("Párbaj?! Tûnj el, nem érdemes rád idôt pazarolni.", "Párbaj? Nem érdemled meg ezt a megtiszteltetést! Tûnj el!");
			link.l1 = RandPhraseSimple("Rendben...", "Gondolom, tudok várni...");
			link.l1.go = "exit";
/**/
			//можно дать возможность драться полюбому :)			
			if (rand(100) < 30)
			{
				link.l1 = RandPhraseSimple("Gondolod? Ne légy olyan biztos benne, te szemétláda!!!", "Ó, tényleg?! Majd meglátom milyen színû a véred!");
				link.l1.go = "fight_right_now";
			}
/**/
			break;
		}

		//согласен.
		Dialog.Text = RandPhraseSimple("A párbaj, azt mondod? Nekem megfelel. Kardok és pisztolyok lesznek a fegyvereink.", 
			"Tudsz egyáltalán kardot fogni?");
		link.l1 = RandPhraseSimple("Térden állva fogsz kegyelemért könyörögni.", "Puszta kézzel fojtalak meg, te gazember!");
		link.l1.go = "land_duel";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			Dialog.Text = RandPhraseSimple(Dialog.Text + " Vagy kihajózhatunk és megnézhetjük, ki kicsoda!", 
				"A párbaj?!! Ha, szétzúzlak, mint egy bogarat! Válaszd ki, hogyan szeretnél meghalni!");
			link.l2 = RandPhraseSimple("A tengeren én vagyok a legjobb.", "Hajóm könnyedén elsüllyeszti a régi kádadat!");
			link.l2.go = "sea_duel";
		}
		link.l3 = "Meggondoltam magam...";
		link.l3.go = "change_mind";
		break;

	//дуэль на подводных лодках :))))
	case "sea_duel":
		Dialog.Text = RandPhraseSimple("Nem látom a hajóját a kikötôben...", "Tûnj el, amíg legalább egy ócska öreg kádat nem találsz!");
		link.l1 = RandPhraseSimple("Az én hibám...", "Akkor elhagylak.");
		link.l1.go = "exit";
		if (pchar.location.from_sea == GetCurrentTown() + "_town")
		{
			Dialog.Text = "Rendben, várlak az öböl kijáratánál...";
			link.l1 = "Nem akarlak túl sokáig várakoztatni.";

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
//			iHour = MakeInt(18.0 - GetTime()) + rand(2); //раскоментировать для дуэлей только по ночам
		}
		pchar.questTemp.Duel.WaitTime = iHour;
		Dialog.Text = RandSwear() + RandPhraseSimple("Rajzolj acélt, és lássuk, milyen színû a véred!", "Nos, ha halálvágyad van...");
		link.l1 = RandPhraseSimple("Jobb, ha olyan helyre megyünk, ahol nincs túl sok szemtanú. Tudok egy megfelelô helyet a város kapui mögött. Találkozzunk ott " + iHour + " óra múlva.",
			"Nyugalom. Az ilyen dolgokat jobb tanúk nélkül elintézni. Gyertek " + iHour + "  órán belül a város bejáratához.");
		link.l1.go = "fight_off_town";
		link.l2 = RandPhraseSimple("Nos, ha ennyire meg akarsz halni...", "Francba! Segítek neked, hogy a saját szemeddel lásd a poklot!");
		link.l2.go = "fight_right_now";
		link.l3 = "Meggondoltam magam...";
		link.l3.go = "change_mind";

		if (rand(1))
		{
			Dialog.Text = RandSwear() + RandPhraseSimple("Azt hiszem, jobb, ha elmegyünk a városkapun túlra. Ott várom önöket " + pchar.questTemp.Duel.WaitTime + " órán belül. Ne késlekedjetek!", 
				"Ez nem a legjobb hely a viták rendezésére. Jobb, ha elhagyjuk a várost. " + pchar.questTemp.Duel.WaitTime + " órán belül ott leszek.");
			link.l1 = RandPhraseSimple("Nem érdemled meg ezt a megtiszteltetést! Védd meg magad!", "Nincs idôm! Húzd ki az acélt!");
			link.l1.go = "fight_right_now";
			link.l2 = RandPhraseSimple("Rendben, sétáljunk egyet.", "Valószínûleg igazad van. Találkozzunk a kapuk mögött.");
			link.l2.go = "fight_off_town_prep";
		}
		break;

	//предложение "пойдём выйдем" рассматривается
	case "fight_off_town":
		Dialog.Text = RandPhraseSimple("Nem érdemled meg ezt a megtiszteltetést! Védd meg magad!", "Nincs idôm! Itt és most!");
		link.l1 = RandPhraseSimple("Nos, ha ennyire meg akarsz halni...", "Francba! Segítek neked, hogy a saját szemeddel lásd a poklot!");
		link.l1.go = "fight_right_now";
		if (rand(1))
		{
			Dialog.Text = RandPhraseSimple("Rendben, sétáljunk egyet.", "Valószínûleg igazad van. Találkozzunk a kapuk mögött.");
			link.l1 = RandPhraseSimple("Ott fogok várni rád.", "Ne késlekedj.");
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
			SetTimerConditionParam("duel_move_opponentBack", "Duel_Move_OpponentBack", 0, 0, 0, sti(GetTime() + 0.5) + sti(pchar.questTemp.Duel.WaitTime) + 1, false);
			pchar.quest.duel_move_opponentBack.function = "Duel_Move_OpponentBack";
			if (CheckAttribute(NPChar, "CityType"))
			{
				DeleteAttribute(NPChar, "City"); // чтоб не было ругани с нацией
	    		DeleteAttribute(NPChar, "CityType");
				if (!CheckAttribute(NPChar, "PGGAi")) 
				{
					if (!CheckAttribute(NPChar, "LifeDay")) npchar.LifeDay = 0;
					npchar.LifeDay = sti(npchar.LifeDay) + 3; // чтоб до дуэли не помер
				}
    		}
		}
		NextDiag.CurrentNode = "let_s_duel";
		DialogExit();
		break;

	//последнее слово перед боем
	case "talk_off_town":
		Dialog.Text = "Szóval, készen állsz?";
		link.l1 = "Igen, készen. Lássuk, ki a jobb ember!";
		link.l1.go = "fight_right_now";
		link.l2 = "Nem, úgy döntöttem, hogy elhozom a bocsánatkérést neked. Tévedtem, felbôszültem.";
		link.l2.go = "change_mind";
		if (rand(100) < 20)
		{
			Dialog.Text = RandPhraseSimple("Hé, figyelj, gondolkodtam rajta, és most már látom, hogy tévedtem. Elnézést kérek.", 
				"Francba! Az a sok átkozott rum!!! Elnézést kérek, "+ GetSexPhrase("testvér","nôvér") +"!");
			link.l1 = NPCharRepPhrase(pchar, 
				RandPhraseSimple("Nem, most már csak a véred adhat nekem elégtételt!", "Rajzolj lopva, és ne legyél már ilyen sírós lány!"), 
				RandPhraseSimple("Nem! Kielégítést követelek!", "Szégyent hozol a családodra! Vedd le a kardodat!"));
			link.l1.go = "fight_right_now";
			link.l2 = NPCharRepPhrase(pchar, 
				RandPhraseSimple("Rendben, egyetértek. Kicsit felhúztuk magunkat.", "Ki tartja számon a barátok között!"), 
				RandPhraseSimple("Valószínûleg igazad van. Nem kéne ilyen pitiáner dolgok miatt vért ontani.", "Nagylelkûségem nem ismer határokat! Megbocsátok neked!"));
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
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() + 
				RandPhraseSimple("Akkor tûnj el!", "Akkor tûnj el, mielôtt meggondolom magam."), 
				RandPhraseSimple("Ebben az esetben nem késleltetlek tovább!", "Akkor jobb, ha elmész, mielôtt meggondolom magam."));
		link.l1 = "Már megyek is...";
		link.l1.go = "peace";
		break;

	case "after_peace":
		Dialog.Text = NPCharRepPhrase(NPChar, RandSwear() +
				RandPhraseSimple("Tûnj el!", "Tûnj el a szemem elôl, mielôtt meggondolom magam."),
				RandPhraseSimple("Segíthetek?", "Akarsz valamit?"));
		link.l1 = "Elmegyek.";
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
