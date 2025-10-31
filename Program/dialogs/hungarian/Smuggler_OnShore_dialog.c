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
				
				float fMaxClass = ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5);
				if (IsEquipCharacterByArtefact(pchar, "talisman21")) fMaxClass = 2.0;
				
				if (GetCompanionQuantity(pchar) > 1) iTmp = true;
				if (GetCharacterShipClass(pchar) < fMaxClass) iTmp = true;

				// поиск мин.  те старшего класса
				/* for (i=0; i<COMPANION_MAX; i++)
				{
					iChIdx = GetCompanionIndex(GetMainCharacter(), i);
					if (iChIdx>=0)
					{
						sld = GetCharacter(iChIdx);
            			if (GetCharacterShipClass(sld) < ((MOD_SKILL_ENEMY_RATE/5.0) + 1.5)) iTmp = true;
					}
				} */
				
				if (iTmp)
				{
					dialog.text = NPCStringReactionRepeat("Nem megmondták, hogy ne jöjjön ide ilyen feltûnô hajóval! Miért nem hoztál egy pár harci páncélt? Tûnjetek el, és gyertek egy kisebb hajóval.", 
						"Kifelé! Vagy mi magunk adunk fel az ôrjáratnak.", 
						"Menjetek a hajótokra, és tûnjetek el!",
						"Annyira elegem van belôled...", "block", 1, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("Rendben, rendben, megváltoztatom az edényemet.", 
						"Nyugodj meg, úton vagyok.",
						"Francba, azt hittem, hogy mûködni fog...", 
						"Igen, nagyon makacs vagyok!", npchar, Dialog.CurrentNode);
						link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);	
					break;
				}
			
				Dialog.snd = "voice\SMSH\SMSH001";
				dialog.Text = RandPhraseSimple("Hé, mit keresel itt, "+ GetSexPhrase("haver","lány") +"?",
                                          RandSwear() + "Mit keresel itt?!");
				Link.l1 = "Nyugi, haver, cseréljünk!";
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
					Link.l2 = "A " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen") + "kormányzójának parancsára vagyok itt! Dobják el a fegyvert és kövessenek, le vannak tartóztatva!";
					Link.l2.go = "GenQuestKillContraband_1";
				}
			}
			else
			{
//================ METRO ====================
				//если заплатил, то разговаривают, иначе посылают
				if (CheckAttribute(PChar, "GenQuest.contraTravel.payed") && sti(PChar.GenQuest.contraTravel.payed) == true)
				{
                    dialog.Text = RandPhraseSimple("Á, végre! Már vártunk rád. Induljunk, itt az idô, hogy elhajózzunk.", "Gyorsan csináljuk. Mindenhol ôrjáratok vannak. El kell tûnnünk innen!");
					//по заданию губернатора, истребление контры, только эта ветка.
					if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers == "" && pchar.GenQuest.KillSmugglers.Areal == GiveArealByLocation(&locations[FindLocation(pchar.location)]))
					{
						Link.l1 = "A " + XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city+"Gen") + "kormányzójának parancsára vagyok itt! Dobják el a fegyvert és kövessenek, le vannak tartóztatva!";
						Link.l1.go = "GenQuestKillContraband_1";
						break;
					}
					//если набрал пассажиров, в сад..
					if (GetPassengersQuantity(PChar) > 0)
					{
						dialog.Text = "És te ki vagy? Csak egy utasról beszéltünk!";
						Link.l1 = "Hoppá..";
						Link.l1.go = "Exit";
						break;
					}
					//если набрал компаньонов или купил корабль себе уже :), в сад..
					if (GetCompanionQuantity(PChar) > 1 || sti(PChar.ship.type) != SHIP_NOTUSED)
					{
						dialog.Text = RandPhraseSimple("Ki vagy te? Egy utast vártunk, nem egy kapitányt.", "Tûnj el! Ne gyere vissza, amíg meg nem szabadulsz a hajódtól!");
						Link.l1 = "Basszus!";
						Link.l1.go = "Exit";
						break;
					}
					//типа помог отбиться, свой парень... 
					if (CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight") && sti(PChar.GenQuest.contraTravel.PatrolFight) == true)
					{
						if (chrDisableReloadToLocation) // ещё бой идёт
						{
						    dialog.Text = "A francba, ôrjárat! Nem ismerjük magukat, és maguk sem ismernek minket.";
							Link.l1 = "Rendben...";
							Link.l1.go = "Exit";
							break;
						}
						dialog.Text = RandPhraseSimple("Köszönöm a segítségét. Ezt nem fogjuk elfelejteni. Vitorlázzunk most.", "Szép munka! Jó harcot. Induljunk.");
						ChangeContrabandRelation(PChar, 5);
						PChar.GenQuest.contraTravel.PatrolFight = false;
						AddCharacterExpToSkill(Pchar, "Sneak", 50);
					}
					//тут все ок, отправляемся.
					Link.l2 = "Már úton vagyok.";
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
						
						SetLaunchFrameFormParam(".. " + sti(Pchar.GenQuest.contraTravel.destination.days) + " nap telt el." + NewStr() + "A csempészhajó fedélzetén.",
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
					    dialog.Text = RandSwear()+ "Ôrjárat! Nem ismerünk titeket, és ti sem ismertek minket.";
						Link.l1 = "Rendben!";
						Link.l1.go = "Exit";
					}
					else
					{
						dialog.Text = "Tûnjetek el! Kitépjük a beleiteket, ha elrontjátok az üzletünket.";
						Link.l1 = RandPhraseSimple("Hogy merészelsz megfenyegetni, te korcs!?", "Meg fogsz fulladni a szavaidtól!");
						Link.l1.go = "Exit_fight";
						Link.l2 = "Ne aggódj, tudom, mi az üzlet. Viszlát.";
						Link.l2.go = "Exit";
					}
				}
			}
		break;

		case "No_Ship":
			Dialog.snd = "voice\SMSH\SMSH003";
			dialog.Text = "A gerinceden hordod? Hol van a hajód?";
			Link.l1 = RandPhraseSimple("Elôször is szeretném megnézni, hogy van-e benne valami csapda.", "Nem akartam kockáztatni a hajót. Jobban szeretek mindent a saját szememmel látni.");
			Link.l1.go = "No_ship_1";
			Link.l2 = "Az üzletnek vége!";
			Link.l2.go = "Cancellation";
		break;

		case "No_ship_1":
			Dialog.snd = "voice\SMSH\SMSH004";
			dialog.Text = "Mi becsületes emberek vagyunk, és nem fogunk becsapni téged. Hozd ide a hajódat, csak ne kelljen járôröket küldened utánad.";
			Link.l1 = "Jól van, rendben. Várjatok meg itt.";
			Link.l1.go = "Exit";
		break;

		case "Cancellation":
            if (sti(Pchar.quest.Contraband.Counter) == 0)
            {
    			dialog.Text = "Vége? Most biztos csak viccelsz velem!";
    			Link.l1 = "Komolyan mondom.";
    			Link.l1.go = "Cancellation_1";
			}
			else
            {
    			dialog.Text = "Akkor jó. Ma amúgy is jó üzleteket kötöttünk.";
    			Link.l1 = "Helyes!";
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
					dialog.Text = "Te szemétláda! Nem verhetsz át minket csak így! A saját fejeddel fogsz fizetni érte!";
					Link.l1 = "Ezt kétlem!";
					Link.l1.go = "Exit_fight";			
				}
				else
				{
					ChangeContrabandRelation(pchar, -10);
					Dialog.snd = "voice\SMSH\SMSH007";
					dialog.Text = "Ezt nem úszod meg!";
					Link.l1 = "Menjetek máshova ugatni, kutyák!";
					Link.l1.go = "Exit_cancel";
				}
			}	
			else
			{
				ChangeContrabandRelation(pchar, -10);
				Dialog.snd = "voice\SMSH\SMSH008";
				dialog.Text = "Ezt még megbánjátok!";
				Link.l1 = "Túl sokat beszélsz.";
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
			dialog.Text = "Ezért felelni fogtok!";
			Link.l1 = "Akkor mindannyian halottak vagytok. Világos parancsot kaptam - mindannyiótokat meg kell semmisítenem, ha ellenálltok.";
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

			AddSimpleRumourCity("Hallottad a legfrissebb híreket? A helyi csempészeket nemrég egy ôrjárat begyûjtötte. És tudjátok mit? A kapitány, akivel üzletet kötöttek, megszökött!" +
				"He had dashing lads in his crew and the whole patrol was killed. And our local smugglers just vanished. There was nothing found on the shore. No goods, no stash and smugglers. See, how they do their business here!", Pchar.quest.contraband.City, 3, 5, "");	

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
				dialog.Text = "És te mit keresel itt? Nincs mit eladnod! A rakományotok minden áruját el lehet adni a városban!";
				Link.l1 = "Ezúttal nem volt szerencséd.";
				Link.l1.go = "NoGoods";
			}
			else
			{
                // установим окружение -->
                if (sti(Pchar.quest.Contraband.Counter) == 0) // не торговали ещё
                {
                    if(hrand(11) == 3)
                    {
        				dialog.Text = "Értem... Tudod, ingyen elvisszük az árudat. Kétlem, hogy panaszkodni tudnátok.";
        				Link.l1 = "Próbáld ki, söpredék!";
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
				dialog.text = "Rendben, lássuk, mit tudsz.";										  
				Link.l1 = "Mutasd meg, mit tudsz.";
				Link.l1.go = "Exchange1"; 
				if (sti(Pchar.quest.Contraband.Counter) == 0)
    			{
        			Link.l99 = "Meggondoltam magam.";
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
			dialog.text = "Jó üzlet, kapitány! Ha van még valami érdekes termék - jelentkezz!";										  
			Link.l1 = "Egyetértek, én is elégedett vagyok az üzletünkkel. Ó, bárcsak megvehetném az összes árut ilyen jó áron...";
			Link.l1.go = "SmugglerZPQ_1"; 
		break;

		case "SmugglerZPQ_1":
			dialog.text = "Miért kell ilyen áron megvenni a közönséges árut, ha legálisan meg lehet venni egy boltban? De ne csüggedjetek: valójában bármilyen terméket lehet árulni, még a közönséges puskaport is! Égig érô áron lehet eladni, csak ismerni kell a helyet.";										  
			Link.l1 = "Gyerünk! Ki vesz puskaport egekbe szökô áron?";
			Link.l1.go = "SmugglerZPQ_2"; 
		break;
		
		case "SmugglerZPQ_2":
			dialog.text = "Hát, ezt mondtam én is, hehe ... Bár... Tudod, tényleg van egy ilyen lehetôség, hogy egy vagyonért eladjuk a lôport, de ez az üzlet még mindig nem ragyog számunkra, ehhez elég jó hírnév kell, és mi, mint érted, nem vagyunk nemesek.";										  
			Link.l1 = "Nos, talán utánanézhetek a dolognak. Tudok jó és kedves lenni, ha kell. Mesélnél nekem az üzletrôl?";
			Link.l1.go = "SmugglerZPQ_3"; 
		break;
		
		case "SmugglerZPQ_3":
			dialog.text = "Ebben a világban minden pénzbe kerül, kapitány, még az információ is. Sôt, azt mondanám, különösen az információ. A következôt javaslom: Ezt a tippet adom önnek egy jelképes összegért... mondjuk ötezer pezóért. Ez megfelel önnek?";										  
			Link.l1 = "Ötezer pezót fizetni kétes információkért arról, hogy hol lehet magas áron puskaport eladni? Nem, azt hiszem, valahogy meg tudok élni e borravaló nélkül is.";
			Link.l1.go = "SmugglerZPQ_NM"; 
			if(sti(pchar.money) > 4999)
			{
				Link.l2 = "Azt hiszem, többet is tudok keresni ezen az üzleten, mint ötezer. Rendben, akkor egyetértek.";
				Link.l2.go = "SmugglerZPQ_4";
			}
		break;	
		
		case "SmugglerZPQ_NM":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "Magán múlik, kapitány. Mindenesetre jó üzletet kötöttünk. Sok szerencsét... és ne fusson bele egy ôrjáratba!";										  
			Link.l1 = "Neked is. Viszontlátásra.";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_4":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "Kitûnô, kapitány! Maga egy csodálatos ügyfél, tudja. Figyeljen ide. A fülembe súgták, hogy a Maine-en lévô spanyol városok némelyikében gond van a puskaporral. Akár trópusi záporok, akár valami más - általában a kolóniát ôrzô erôdben nagyon kevés a tartalék. És ennek az erôdnek a parancsnoka keres valakit, aki ebben a nehéz helyzetben segíteni tudna neki.\nEzzel csak két probléma van: elôször is, ez egy kényes ügy, és a parancsnok nem fog errôl beszélni semmilyen csalóval, másodszor, nagyon nagy tételrôl van szó - nem minden hajóba fér ennyi lôpor, így lehet, hogy egy flottára lesz szükség. Továbbá nem minden kapitány fog beleegyezni abba, hogy a hajóját egy úszó bombává változtassa, amely könnyedén elpusztíthat egy egész szigetet, ha eltalálja egy kóbor ágyúgolyó.";
			if(CheckAttribute(pchar,"questTemp.zpq"))
			{
				Link.l1 = "Bocsánat, de én már tudok errôl az üzletrôl. Mindenesetre az alku többet ér, mint a pénz, úgyhogy megérdemelsz ötezret.";
				Link.l1.go = "SmugglerZPQ_5"; 
			}
			else
			{
				Link.l1 = "Értékes információ, köszönöm. Ha Maine-en leszek, megkérdezem az erôdök helyi parancsnokait a szerencsétlenségükrôl. És valahogy remélem, hogy foglalkozni fogok ezekkel a problémákkal, vagy visszaélni velük he-he.";
				Link.l1.go = "SmugglerZPQ_6"; 
			}
		break;
		
		case "SmugglerZPQ_5":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			dialog.text = "Így szokott ez történni. Mindenesetre jó üzletet kötöttünk. Sok szerencsét... és ne fuss bele egy ôrjáratba!";										  
			Link.l1 = "Neked is. Viszontlátásra.";
			Link.l1.go = "exit"; 
		break;
		
		case "SmugglerZPQ_6":
			npchar.Dialog.CurrentNode = "first time";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.Smugglerzpq");
			AddQuestRecord("zpq", "0");
			dialog.text = "Így szokott ez történni. Mindenesetre jó üzletet kötöttünk. Sok szerencsét... és ne fuss bele egy ôrjáratba!";										  
			Link.l1 = "Neked is. Viszontlátásra.";
			Link.l1.go = "exit"; 
		break;
		// <-- legendary edition опасный груз
	}
}
