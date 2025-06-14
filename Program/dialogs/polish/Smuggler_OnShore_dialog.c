void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, Diag;
	string NPC_Meeting;	
	int Shit, i;
	ref refStore;
	ref sld;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
        case "exit":
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

        case "First time":
			Diag.TempNode = "first time";
			if(CheckAttribute(PChar, "quest.Contraband.active"))
			{
				int iTmp = false;
				int iChIdx;

				// поиск мин.  те старшего класса
				for (i=0; i<COMPANION_MAX; i++)
				{
					iChIdx = GetCompanionIndex(GetMainCharacter(), i);
					if (iChIdx>=0)
					{
						sld = GetCharacter(iChIdx);
            			if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
					}
				}
				
				if (iTmp)
				{
					dialog.text = NPCStringReactionRepeat("Czy nie mówiono ci, żebyś nie przychodził tutaj na takim rzucającym się w oczy statku! Dlaczego nie przyprowadzisz paru okrętów wojennych? Spływaj i wróć na mniejszym statku.","Znikaj! Albo sami wydamy cię patrolowi.","Idź do swojej łodzi i znikaj.","Tak cię już mam dosyć...","block",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Dobrze, dobrze, zamierzam zmienić mój statek.","Uspokój się, już idę.","Cholera, myślałem, że to zadziała...","Tak, jestem naprawdę uparty!",npchar,Dialog.CurrentNode);
						link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
					break;
				}
			
				Dialog.snd = "voice\SMSH\SMSH001";
				dialog.Text = RandPhraseSimple("Hej, a ty tu co, "+GetSexPhrase("kolego","koleżanko")+"?",RandSwear()+"Jaki masz tu interes?!");
				Link.l1 = "Spokojnie, kumplu, jestem tu by handlować!";
				Pchar.quest.Contraband.Counter = 0; // не торговали
				if(Pchar.Location == Pchar.location.from_sea)
				{
					Link.l1.go = "Exchange";
				}
				else
				{
					Link.l1.go = "No_Ship";
				}
				//по заданию губернатора, истребление контры, только эта ветка.
				if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))				
				{
					Link.l2 = "Jestem tutaj na rozkaz gubernatora z "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen")+"! Ty i twoi przylaciele mają rzucić swoją broń i pójść ze mną, jesteście aresztowani!";
					Link.l2.go = "GenQuestKillContraband_1";
				}
			}
			else
			{
//================ METRO ====================
				//если заплатил, то разговаривают, иначе посылают
				if (CheckAttribute(PChar, "GenQuest.contraTravel.payed") && sti(PChar.GenQuest.contraTravel.payed) == true)
				{
                    dialog.Text = RandPhraseSimple("Ach, w końcu! Czekaliśmy na ciebie. Ruszajmy, czas odpłynąć.","Zróbmy to szybko. Wszędzie są patrole. Musimy stąd uciec!");
					//по заданию губернатора, истребление контры, только эта ветка.
					if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))
					{
						Link.l1 = "Jestem tutaj na rozkaz gubernatora "+XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen")+"! Ty i twoi przylaciele mają rzucić swoją broń i pójść ze mną, jesteście aresztowani!";
						Link.l1.go = "GenQuestKillContraband_1";
						break;
					}
					//если набрал пассажиров, в сад..
					if (GetPassengersQuantity(PChar) > 0)
					{
						dialog.Text = "A to niby kto do cholery? Mówiliśmy tylko o jednym pasażerze!";
						Link.l1 = "Ups..";
						Link.l1.go = "Exit";
						break;
					}
					//если набрал компаньонов или купил корабль себе уже :), в сад..
					if (GetCompanionQuantity(PChar) > 1 || sti(PChar.ship.type) != SHIP_NOTUSED)
					{
						dialog.Text = RandPhraseSimple("Kim jesteś? Czekaliśmy na pasażera, a nie na kapitana.","Zejdź na bok! Nie wracaj, dopóki się nie pozbędziesz swojego statku.");
						Link.l1 = "Cholera!";
						Link.l1.go = "Exit";
						break;
					}
					//типа помог отбиться, свой парень... 
					if (CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight") && sti(PChar.GenQuest.contraTravel.PatrolFight) == true)
					{
						if (chrDisableReloadToLocation) // ещё бой идёт
						{
						    dialog.Text = "Cholera, patrol! My cię nie znamy, a ty nas nie znasz.";
							Link.l1 = "Dobrze...";
							Link.l1.go = "Exit";
							break;
						}
						dialog.Text = RandPhraseSimple("Dziękuję za twoją pomoc. Nie zapomnimy tego. Płyniemy teraz.","Dobra robota! Dobra walka. Ruszajmy.");
						ChangeContrabandRelation(PChar, 5);
						PChar.GenQuest.contraTravel.PatrolFight = false;
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
					//тут все ок, отправляемся.
					Link.l2 = "Jestem w drodze.";
					Link.l2.go = "Exit";
					//а это патруль... 
					if (GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < frandSmall(13.0*(1.0 - pow(0.9, sti(PChar.rank)))) && !CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight"))
					{
						AddDialogExitQuest("Rand_ContrabandInterruption");
						PChar.GenQuest.contraTravel.PatrolFight = true;
					}
					else 
					{
						//поместим Грея в локацию.
						refStore = CharacterFromID("Abracham_Gray");
						ChangeCharacterAddressGroup(refStore, "Ship_deck", "goto", "goto2");
						refStore.dialog.Filename = "Smuggler_Ship_dialog.c";
                        refStore.dialog.CurrentNode = "Travel_talkStart";
						//поплыл, иначе RemoveTravelSmugglers грохнет всю ветку
						PChar.GenQuest.contraTravel.ship = true;
						PChar.quest.Munity = "";  // признак выхода с палубы
						
						SetLaunchFrameFormParam(".. " + sti(Pchar.GenQuest.contraTravel.destination.days) + " days passed." + NewStr() + "Smuggler's ship deck.",
						                        "Reload_To_Location", 0.1, 5.0);
                        bQuestCheckProcessFreeze = true;
						WaitDate("", 0, 0, sti(Pchar.GenQuest.contraTravel.destination.days), rand(20), 0);
						bQuestCheckProcessFreeze = false;
						MakeCloneShipDeck(refStore, true); // подмена палубы
						SetLaunchFrameReloadLocationParam("Ship_deck", "reload", "reload1", "Travel_talkOnDeck");
						AddDialogExitQuest("LaunchFrameForm");
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
//================ METRO ====================
				}
				else
				{
                    // если таможня уже бежит
					if (CheckAttribute(NPChar, "ContrabandInterruption"))
					{
					    dialog.Text = RandSwear()+"To był patrol! My cię nie znamy, a ty nas nie znasz.";
						Link.l1 = "Dobrze!";
						Link.l1.go = "Exit";
					}
					else
					{
						dialog.Text = "Znikaj! Rozprujemy ci flaki, jeśli zepsujesz nasz interes.";
						Link.l1 = RandPhraseSimple("Ośmielasz się mi grozić, kundlu!?","Zadławisz się swoimi słowami!");
						Link.l1.go = "Exit_fight";
						Link.l2 = "Nie martw się, wiem, co to jest biznes. Do widzenia.";
						Link.l2.go = "Exit";
					}
				}
			}
		break;

		case "No_Ship":
			Dialog.snd = "voice\SMSH\SMSH003";
			dialog.Text = "Czy nosisz to na swoim kręgosłupie? Gdzie jest twój statek?";
			Link.l1 = RandPhraseSimple("Spokojnie, chciałbym zobaczyć, czy jest w tym jakiś haczyk.","Nie chciałem ryzykować statkiem. Wolę widzieć wszystko na własne oczy.");
			Link.l1.go = "No_ship_1";
			Link.l2 = "Umowa jest skończona!";
			Link.l2.go = "Cancellation";
		break;

		case "No_ship_1":
			Dialog.snd = "voice\SMSH\SMSH004";
			dialog.Text = "Jesteśmy uczciwymi ludźmi i nie oszukamy cię. Przywieź tu swój statek, tylko nie zwracaj na siebie uwagi patrolów.";
			Link.l1 = "Dobrze. Czekaj na mnie tutaj.";
			Link.l1.go = "Exit";
		break;

		case "Cancellation":
            if (sti(Pchar.quest.Contraband.Counter) == 0)
            {
    			dialog.Text = "Skończona? Pewnie sobie żartujesz!";
    			Link.l1 = "Jestem poważny.";
    			Link.l1.go = "Cancellation_1";
			}
			else
            {
    			dialog.Text = "Dobrze więc. Mieliśmy dzisiaj dobre wymiany handlowe.";
    			Link.l1 = "Dokładnie!";
    			Link.l1.go = "Finish_exit";
			}
		break;

		case "Cancellation_1":
			if( makeint(Pchar.rank) <= 3 || GetSummonSkillFromNameToOld(Pchar, SKILL_FENCING) <= 5 || GetSummonSkillFromNameToOld(Pchar, SKILL_LEADERSHIP) <= 5 )
			{
				if(Rand(1) == 1)
				{
					ChangeContrabandRelation(pchar, -30);
					Dialog.snd = "voice\SMSH\SMSH006";
					dialog.Text = "Ty bękarcie! Nie oszukasz nas tak po prostu! Zapłacisz za to swoją własną głową!";
					Link.l1 = "Wątpię w to!";
					Link.l1.go = "Exit_fight";			
				}
				else
				{
					ChangeContrabandRelation(pchar, -10);
					Dialog.snd = "voice\SMSH\SMSH007";
					dialog.Text = "Nie ujdzie ci to na sucho!";
					Link.l1 = "Idź szczekać gdzie indziej, psie!";
					Link.l1.go = "Exit_cancel";
				}
			}	
			else
			{
				ChangeContrabandRelation(pchar, -10);
				Dialog.snd = "voice\SMSH\SMSH008";
				dialog.Text = "Pożałujesz tego!";
				Link.l1 = "Chciałbyś.";
				Link.l1.go = "Exit_cancel";			
			}	
		break;

		case "GenQuestKillContraband_1":
			//счетчик подстав по "метро"...
			if(CheckAttribute(PChar, "GenQuest.contraTravel.active") && sti(PChar.GenQuest.contraTravel.active) == true)
			{
				Statistic_AddValue(PChar, "contr_TravelKill", 1);
				ChangeContrabandRelation(pchar, -20); //репу контры вниз
			}
			dialog.Text = "Nigdzie nie idziemy!";
			Link.l1 = "Wtedy wszyscy jesteście martwi. Mam jasny rozkaz - zlikwidować was wszystkich, jeśli będziecie stawiać opór.";
			Link.l1.go = "Exit_fight";
		break;
		
		case "Exit_Cancel":
            DeleteAttribute(Pchar, "quest.Contraband");
            CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;
		
		case "Exit_fight":
            DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");			

			AddSimpleRumourCity("Słyszałeś najnowsze wieści? Miejscowi przemytnicy zostali niedawno złapani przez patrol. I wiesz co? Kapitan, który miał z nimi układ, uciekł!" +
				"Miał w swojej załodze dzielnych chłopaków, a cały patrol został zabity. A nasi lokalni przemytnicy po prostu zniknęli. Na brzegu nic nie znaleziono. Żadnych towarów, żadnej skrytki i przemytników. Zobacz, jak oni tu robią interesy!", Pchar.quest.contraband.City, 3, 5, "");	

			CloseQuestHeader("Gen_Contraband");
			Pchar.quest.Rand_Smuggling.over = "yes";
			LAi_group_FightGroups(LAI_GROUP_PLAYER, pchar.GenQuest.Smugglers_Group, true);
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
			LAi_SetFightMode(Pchar, true);

			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "Finish_exit":
            // таможня на суше
            if(GetSummonSkillFromName(pchar, "Sneak") < Rand(120))
			{
				AddDialogExitQuest("Rand_ContrabandInterruption");
				for (i=1; i<=3; i++)
				{
					characters[GetCharacterIndex("Rand_Smug0"+i)].ContrabandInterruption = true;
				}
			}
			AddCharacterExpToSkill(Pchar, "Sneak", 100);
			Diag.CurrentNode = Diag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
			ChangeContrabandRelation(pchar, 15);
            OfficersReaction("bad");
            ChangeCharacterComplexReputation(pchar,"nobility", -1);
            
            CloseQuestHeader("Gen_Contraband");
            
			DeleteAttribute(Pchar, "quest.Contraband.active");
			DeleteAttribute(Pchar, "quest.Contraband.counter");
	
			Pchar.quest.Rand_Smuggling.over = "yes";
			RemoveSmugglersFromShore();
			RemoveAllContraGoods(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId));
		break;

		case "Exchange":
			// сама торговля -->
            if(FindContrabandGoods(Pchar) == -1 && sti(Pchar.quest.Contraband.Counter) == 0)
            {
				dialog.Text = "I co tu robisz? Nie masz nic do sprzedania! Każdy towar w twoim ładunku można sprzedać w mieście!";
				Link.l1 = "Nie ma szczęścia tym razem.";
				Link.l1.go = "NoGoods";
			}
			else
			{
                // установим окружение -->
                if (sti(Pchar.quest.Contraband.Counter) == 0) // не торговали ещё
                {
                    if(hrand(11) == 3)
                    {
        				dialog.Text = "Rozumiem... Wiesz, weźmiemy twoje towary za darmo. Poskarżyć się nie będziesz miał komu.";
        				Link.l1 = "Ja ci zaraz wezmę za darmo, ty szumowino!";
        				Link.l1.go = "Exit_fight";
                        break;
        			}
        			// море и солдаты на суше НЕЗАВИСИМЫ!!!
        			if(GetSummonSkillFromNameToOld(Pchar, SKILL_SNEAK) < Rand(12))
        			{
                        SetCoastalGuardPursuit();
        			}
        			// при убегании от патруля на карту - корабли трем
        			SetTimerCondition("Rand_ContrabandInterruptionAtSeaEnded", 0, 0, 2, false);// если в порту сидим, спим, то 2 день
        			
                    Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition.l1 = "MapEnter";
        			Pchar.quest.Rand_ContrabandAtSeaEnded.win_condition = "Rand_ContrabandAtSeaEnded";
    			}
    			// установим окружение <--
				dialog.text = "Dobra, zobaczmy co tam masz.";										  
				Link.l1 = "Śmiało, rzuć na to okiem.";
				Link.l1.go = "Exchange1"; 
				if (sti(Pchar.quest.Contraband.Counter) == 0)
    			{
        			Link.l99 = "Zmieniłem zdanie.";
    				Link.l99.go = "Cancellation";
				}				
            }
		break;
		
		case "Exchange1":
			NPChar.quest.meeting = NPC_Meeting;
			Diag.CurrentNode = Diag.TempNode;		 
			DialogExit();
			// belamour legendary edition опасный груз
			pchar.GenQuest.Smugglerzpq = npchar.id;
			
			LaunchContrabandTrade(CharacterFromId(pchar.GenQuest.Contraband.SmugglerId),  sti(pchar.FindContrabandGoods.StoreIdx));	
		break;				
		// belamour legendary edition опасный груз -->
		case "SmugglerZPQ":
			dialog.text = "Dobry interes, kapitanie! Jeśli są jakieś inne interesujące produkty - skontaktuj się z nami!";										  
			Link.l1 = "Zgadzam się, jestem również zadowolony z naszego handlu. Ach, gdybym tylko mógł kupić wszystkie towary po tak dobrej cenie...";
			Link.l1.go = "SmugglerZPQ_1"; 
		break;

		case "SmugglerZPQ_1":
			dialog.text = "Dlaczego musimy kupować zwykłe towary po takich cenach, skoro można je legalnie nabyć w sklepie? Ale nie zniechęcaj się: tak naprawdę każdy produkt można sprzedać, nawet zwykły proch strzelniczy! Mogłbyś sprzedać po kosmicznej cenie, wystarczy znać miejsce.";										  
			Link.l1 = "Daj spokój. Kto kupi proch strzelniczy po astronomicznej cenie?";
			Link.l1.go = "SmugglerZPQ_2"; 
		break;
		
		case "SmugglerZPQ_2":
			dialog.text = "Cóż, to właśnie ci powiedziałem, hehe... Chociaż... Wiesz, naprawdę istnieje taka możliwość, aby sprzedać proch za fortunę, ale ten interes nadal nam nie świeci, bo do tego trzeba mieć dość dobrą reputację, a my, jak rozumiesz, nie jesteśmy szlachcicami.";										  
			Link.l1 = "Cóż, może mogę to sprawdzić. Potrafię być dobry i uprzejmy kiedy trzeba. Czy możesz mi powiedzieć o tej umowie?";
			Link.l1.go = "SmugglerZPQ_3"; 
		break;
		
		case "SmugglerZPQ_3":
			dialog.text = "Wszystko kosztuje pieniądze w tym świecie, kapitanie, nawet informacje. Powiedziałbym nawet, szczególnie informacje. Proponuję to: dam ci ten wskazówkę za symboliczną kwotę ... powiedzmy pięć tysięcy peso. Czy to ci odpowiada?";										  
			Link.l1 = "Zapłacić pięć tysięcy pesos za wątpliwe informacje o miejscu, gdzie można sprzedać proch za wysoką cenę? Nie, myślę, że jakoś poradzę sobie bez tej wskazówki.";
			Link.l1.go = "SmugglerZPQ_NM"; 
			if(sti(pchar.money) > 4999)
			{
				Link.l2 = "Mam wrażenie, że mogę zarobić na tej transakcji więcej niż tylko pięć tysięcy. Dobrze, zgadzam się.";
				Link.l2.go = "SmugglerZPQ_4";
			}
		break;	
		
		case "SmugglerZPQ_NM":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "To zależy od ciebie, kapitanie. W każdym razie mieliśmy dobry interes. Powodzenia... i nie wpadnij na patrol!";										  
			Link.l1 = "Ty też. Do widzenia.";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_4":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Znakomicie, kapitanie! Jest pan niesamowitym klientem, wie pan. Więc słuchaj. Ktoś mi szeptem powiedział, że w niektórych hiszpańskich miastach na kontynencie był problem z prochem strzelniczym. Czy to tropikalne deszcze, czy coś innego - ogólnie rzecz biorąc, w forcie, który strzeże kolonii, jest bardzo mało zapasów. A komendant tego fortu szuka kogoś, kto mógłby mu pomóc w tej trudnej sytuacji.\nSą tylko dwa problemy: po pierwsze, to jest delikatna sprawa, i komendant nie będzie o tym rozmawiać z jakimikolwiek szubrawcą, a po drugie, mówimy o bardzo dużej partii - nie każdy statek zmieści tyle prochu strzelniczego, więc mogą być potrzebne floty. Również nie każdy kapitan zgodzi się zamienić swój statek w pływającą bombę, która może łatwo zniszczyć całą wyspę, jeśli zostanie trafiona błądzącą kulką armatnią.";
			if(CheckAttribute(pchar,"questTemp.zpq"))
			{
				Link.l1 = "Przykro mi, ale już wiem o tej transakcji. Tak czy inaczej, umowa jest warta więcej niż pieniądze, więc zasługujesz na pięć tysięcy.";
				Link.l1.go = "SmugglerZPQ_5"; 
			}
			else
			{
				Link.l1 = "Cenne informacje, dziękuję. Jeśli będę na Maine, zapytam miejscowych dowódców fortów o ich nieszczęścia. I jakoś mam nadzieję, że poradzę sobie z tymi problemami lub je wykorzystam he-he.";
				Link.l1.go = "SmugglerZPQ_6"; 
			}
		break;
		
		case "SmugglerZPQ_5":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "Tak to już jest. W każdym razie, mieliśmy dobry interes. Powodzenia... i nie wpadnij na patrol!";										  
			Link.l1 = "Ty też. Do widzenia.";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_6":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			AddQuestRecord("zpq", "0");
			dialog.text = "Tak to się zdarza. W każdym razie, mieliśmy dobry interes. Powodzenia... i nie wpadnij na patrol!";										  
			Link.l1 = "Ty też. Do widzenia.";
			Link.l1.go = "exit"; 
		break;
		// <-- legendary edition опасный груз
	}
}
