// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek, " + GetAddress_Form(NPChar) + "?"), "Nemrég próbáltál feltenni nekem néhány kérdést, " + GetAddress_Form(NPChar) + "...", "Ez már a harmadik alkalom, hogy zaklatsz engem...",
                          "Gondolom, még több kérdés?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Igen, ez tényleg a harmadik alkalom...", "Nem, milyen kérdéseket?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит /за Англию/
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Szeretnék egy italt. Tölts nekem a legjobb rumodból.";
                link.l1.go = "TavernDone";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "toBarbados")
            {
                link.l1 = "Figyelj, hol van Callow Gaston?";
                link.l1.go = "Tonzag_Letter";
            }
			//Голландский гамбит /против всех/
			if (!CheckAttribute(npchar, "quest.HWICTake") && CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Self") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
                link.l1 = "Van valami munkája? Vagy talán tudnál ajánlani valamit?";
                link.l1.go = "Tonzag_check";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FernandoDie")
			{
                link.l1 = "Befejeztem a munkát. Fernando Rodriguez halott.";
                link.l1.go = "Task_check";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Figyeljen, volt itt egy alkimista, aki idejött ebbe a városba, egy orvos? Olasz, körülbelül harminc éves, a neve Gino Gvineili. Hallottál róla valamit?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Голландский гамбит /за Англию/
		case "TavernDone":
			dialog.text = "Itt az italod. A legjobb rumot az új vendégünknek! Ez egy különleges alkalom, vagy csak beugrott, hogy megnedvesítse a fütyülését?";
			link.l1 = "Igen, mondhatjuk, hogy ez egy különleges alkalom. Elviszek néhány négert Blueweldbe. Nemrég átalakítottam az új briggem rakterét kifejezetten erre a célra. Most álltam meg egy ültetvényen, és beszéltem a felügyelôvel, aki rendelt tôlem egy szép adag 'fekete elefántcsontot' . Úgyhogy várjatok vissza hamarosan a kocsmába. Árut szállítok Blueweldnek, és aztán még egy kis üzletet kötök itt Barbadoson, yo ho!";
			link.l1.go = "TavernDone_1";
		break;
		
		case "TavernDone_1":
			dialog.text = "Tényleg? Nos, nem szégyen, ha egy jó üzletért iszunk! Szóval, azt mondod, hogy üzletelni fogsz Barbadoson? Ez nagyszerû! Egészségedre, kapitány!";
			link.l1 = "Köszönöm szépen, pajtás. Rendben... Keresek egy helyet, ahová leülhetek.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-12");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "Tonzag_Letter":
			dialog.text = "Gaston két nappal a 'trader' act után elhagyta a várost. Micsoda show-t csináltál itt, ha! A megtévesztésed gyorsan leleplezôdött, ez a város kicsi, és a pletykák gyorsan terjednek. Ez arra késztette Gastont, hogy elbúcsúzzon. Azóta senki sem látta itt többé. Egy levelet hagyott neked, bár\nkért, hogy személyesen adjam át neked, ha esetleg elôbb jelennél meg itt, mint ô. Valójában nem ön az elsô ember, aki Gastont keresi. Volt valami keskeny szemû nagydarab férfi, meg egy öreg, spanyolnak vagy portugálnak nézett ki, nem tudom biztosan megmondani. De az arcát nem tudom elfelejteni, valami nagyon nem stimmelt vele...";
			link.l1 = "Add ide azt a levelet... Köszönöm!";
			link.l1.go = "Tonzag_Letter_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
		break;
		
		case "Tonzag_Letter_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-22");
			AddQuestRecordInfo("LetterFromGaston", "1");
			pchar.questTemp.HWIC.Eng = "toCuracao";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);//закрыть дом Флитвуда
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", true);//закрыть подземелье
			pchar.quest.Knippel_Shore.win_condition.l1 = "location";
			pchar.quest.Knippel_Shore.win_condition.l1.location = "Shore24";
			pchar.quest.Knippel_Shore.function = "KnippelOnCuracao";
			AddMapQuestMarkShore("Shore24", true);
		break;
		
		//Голландский гамбит /против всех/
		case "Tonzag_check"://начинаем проверять нашего ГГ по всем статьям
			if(sti(pchar.reputation.nobility) > 48)//высокая репа
			{
				// belamour legendary edition покажем критерии
				notification("Túl alacsony a hírneve! (Rogue)", "None");
				PlaySound("Voice\English\hambit\Ercule Tongzag-03.wav");
				dialog.text = "Nincs szükségem egy gazember szolgálataira. Nincs semmilyen feladat, amit fel tudnék ajánlani.";
				link.l1 = "Hé, hé, hé! Óvatosan a nyelvvel, haver!";
				link.l1.go = "exit";
				break;
			}
			bool bOk = GetSummonSkillFromName(pchar, SKILL_F_LIGHT) > 34 || GetSummonSkillFromName(pchar, SKILL_FENCING) > 34 || GetSummonSkillFromName(pchar, SKILL_F_HEAVY) > 34 || GetSummonSkillFromName(pchar, SKILL_PISTOL) > 34;
			if(!bOk)//слабое фехтование
			{
				// belamour legendary edition покажем критерии -->
				notification("Képességpróba Sikertelen (35)", SKILL_F_LIGHT);
				notification("Képességpróba Sikertelen (35)", SKILL_FENCING);
				notification("Képességpróba Sikertelen (35)", SKILL_F_HEAVY);
				notification("Képességpróba Sikertelen (35)", SKILL_PISTOL);
				// <--
				dialog.text = "Kapitány, maga túl puhány. Nekem egy nálad jó hírûbb harcosra van szükségem. Jöjjön vissza, ha megtanulta, hogyan kell bánni az övén lógó acéllal. És egy kis pontosság a lövészetben sem ártana.";
				link.l1 = "Értem. Akkor majd késôbb meglátogatom.";
				link.l1.go = "exit";
				break;
			}
			PlaySound("Voice\English\hambit\Ercule Tongzag-02.wav");
			dialog.text = "Hm... Igazából idôben érkeztél. Van egy megbízásom, amit azonnal el kell végeznem. Ha jó színben tûnsz fel, bemutatlak néhány befolyásos embernek. Figyelj, a következôt kell tenned.";
			link.l1 = "Csupa fül vagyok.";
			link.l1.go = "Tonzag_task";
		break;
		
		case "Tonzag_task":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Self.SpainCity = FindSpainCity();
			log_Testinfo(pchar.questTemp.HWIC.Self.SpainCity);
			dialog.text = "Egy hidalgo nemrég érkezett Sevillából azzal a szándékkal, hogy elkerülje egy párbaj nem kívánt következményeit Európában. A bosszú azonban nem ismer határokat, és egy spanyol nemesi család holtan kívánja ezt a hidalgót. Teljesítsd a kérésüket minden szükséges eszközzel\nViszed magaddal a férfi ujját a gyûrûjével együtt bizonyítékként. Hozd el az összes többi tárgyat is, amit a holttestén találsz. Készen állsz a feladatra?";
			link.l1 = "Ha a fizetség jó, akkor benne vagyok.";
			link.l1.go = "Tonzag_task_1";
			link.l2 = "Orgyilkosként dolgozni? Kizárt dolog!";
			link.l2.go = "Tonzag_exit";
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Self = "true";//признак, что против всех уже бралась
		break;
		
		case "Tonzag_exit":
			dialog.text = "Akkor húzz a picsába, és felejtsd el, amirôl beszéltünk.";
			link.l1 = "Elmegyek.";
			link.l1.go = "exit";	
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//откат к двум другим вариантам
			pchar.questTemp.HWIC.Fail3 = "true";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
		break;
		
		case "Tonzag_task_1":
			dialog.text = "A jutalmad 30.000 darab pesó lesz, jó pénz. Ezen felül minden érmét elvihetsz, amit a testén találsz. Most pedig beszéljük meg a részleteket. A neve Don Fernando Rodriguez, 35 éves, magas, vöröses bôrû, katonatisztnek öltözött. Jó tengerész és tapasztalt vívó\nNem tudom megmondani, hol találjátok meg, csak annyit tudok, hogy valahol a Karib-tengeren van\nKeresd át minden spanyol várost, amíg el nem kapod. Két hónapotok van rá. Még egy utolsó dolog: tisztában vagyok vele, hogy mit hord magánál, szóval eszébe se jusson elrejteni elôlem bármilyen tárgyat. Kérdések?";
			link.l1 = "Nekem nincsenek kérdéseim. Már úton vagyok!";
			link.l1.go = "Tonzag_task_2";	
		break;
		
		case "Tonzag_task_2":
			DialogExit();
			pchar.questTemp.HWIC.Self = "start";
			SetFunctionTimerCondition("TargetFernandoOver", 0, 0, 60, false); //таймер
			//SetFunctionExitFromLocationCondition("CreateMapMarksTonzag", pchar.location, false);
			AddQuestRecord("Holl_Gambit", "3-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила . чтобы вышел из архива																				  
			Log_TestInfo(""+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Self.SpainCity)+"");
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Lucas"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Self.SpainCity, true);
			AddLandQuestMark(characterFromId(pchar.questTemp.HWIC.Self.SpainCity+"_tavernkeeper"), "questmarkmain");
		break;
		
		case "Task_check":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "Van nálad az ujjad, amin a gyûrû van? Hadd lássam!";
			if (CheckCharacterItem(pchar, "Finger"))
			{
				link.l1 = "Igen, persze. Itt is van.";
				link.l1.go = "Task_check_1";	
			}
			else
			{
				link.l1 = "Nem. Fernando elsüllyedt a vízben a hajójával együtt, és az ujj is elsüllyedt Fernandóval együtt.";
				link.l1.go = "Task_fail";	
			}
		break;
		
		case "Task_fail":
			dialog.text = "Az ujj a gyûrûvel kötelezô feltétel volt a szerzôdésben. A megbízó halálának megerôsítésére kellett volna szolgálnia. Ki tudja, hogy Rodriquez kiúszott-e a partra az elsüllyedt hajóról? Ellenôrizted? Nem. Alapvetôen megbukott a megbízáson, így a megállapodásunknak vége. Minden jót.";
			link.l1 = "De én megszabadultam tôle. Elment! Ó, baszd meg... Rengeteg más dolgot is lehet csinálni a Karib-tengeren. Viszlát. Viszlát.";
			link.l1.go = "exit";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
			pchar.questTemp.HWIC.Fail3 = "true";
			AddQuestRecord("Holl_Gambit", "3-8");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
		break;
		
		case "Task_check_1":
			RemoveItems(PChar, "Finger", 1);
			dialog.text = "Csodálatos! Majd én megtartom az ujjam. Most pedig a zsebe tartalmát. Nézzük meg, mit hozott magával.";
			link.l1 = "Gyerünk, nézd meg...";
			link.l1.go = "Task_check_2";	
		break;
		
		case "Task_check_2":
			if (CheckCharacterItem(pchar, "jewelry7") && CheckCharacterItem(pchar, "totem_05") && CheckCharacterItem(pchar, "amulet_1"))
			{
				dialog.text = "Aha, ez minden, amire szükségem van. Szép munka! Jó munkát végeztél. Nagyon elégedett vagyok veled.";
				link.l1 = "Köszönöm, köszönöm! Mindig jó érzés, ha megdicsérik a jól végzett munkáért.";
				link.l1.go = "Task_complete";	
			}
			else
			{
				dialog.text = "Hm... Figyelmeztettelek, hogy tudom, mi az, ami nélkül Rodriguez soha nem tenné meg. És nem látom, hogy mire van szükségem. Zsebre tetted azokat a dolgokat? Elvesztetted ôket? Nem számít. Nem akarok többé veled lenni. Tûnj el innen.";
				link.l1 = "Oh, cseszd meg...";
				link.l1.go = "exit";
				pchar.questTemp.HWIC.Fail3 = "true";
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
				{
					AddMapQuestMarkCity("Villemstad", false);
					AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
				}
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
				{
					AddMapQuestMarkCity("SentJons", false);
					AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
				}
				AddQuestRecord("Holl_Gambit", "3-9");
				CloseQuestHeader("Holl_Gambit");
				DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
			}
		break;
		
		case "Task_complete":
			RemoveItems(PChar, "jewelry7", 1);
			RemoveItems(PChar, "totem_05", 1);
			RemoveItems(PChar, "amulet_1", 1);
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "Itt a jutalmad, ahogy ígértem, harmincezer. És van egy további, nagy felelôsségû, kockázatos megbízásom is, de a fizetés ennek megfelelôen emelkedik, negyvenezer pezó.";
			link.l1 = "Csupa fül vagyok. Ki a következô ügyfél?";
			link.l1.go = "Fleetwood_house";	
		break;
		
		//2 задание
		case "Fleetwood_house":
			PlaySound("Voice\English\hambit\Ercule Tongzag-05.wav");
			dialog.text = "Ezúttal nem egy emberre, hanem egy tárgyra fogsz vadászni. Be kell osonnod Richard Fleetwood házába Antiguán, és el kell lopnod a naplóját. Ô egy angol kapitány. A helyet szigorúan ôrzik, és maga Richard is ritkán látogatja a házát\nA terv egyszerû. St. Jones kormányzója tíz nap múlva zártkörû partit rendez, Fleetwood részt vesz rajta. Éjjel egy és három óra között kell bejutnia a házába. Csak egy katona lesz bent\nSzabadulj meg tôle. Keress egy naplót Richard lakásában. Vedd el ezt a kulcsot.";
			link.l1 = "Hm... Érdekes. Megértettem, mit kell tennem. Készen állok az indulásra!";
			link.l1.go = "Fleetwood_house_1";	
		break;
		
		case "Fleetwood_house_1":
			GiveItem2Character(pchar, "key3");
			dialog.text = "Légy óvatos. Ne osonj be a házba a megadott idôpont elôtt. Különben a legjobb esetben is csak kirúgnak onnan, vagy a legrosszabb esetben rács mögé kerülsz. Ismételd meg nekem a dátumot és az idôpontot.";
			link.l1 = "Pontosan tíz nap múlva, hajnali egy és három óra között.";
			link.l1.go = "Fleetwood_house_2";	
		break;
		
		case "Fleetwood_house_2":
			dialog.text = "Rendben. Elmehetsz. Sok szerencsét!";
			link.l1 = "Köszönöm, Gaston.";
			link.l1.go = "Fleetwood_house_3";
		break;
		
		case "Fleetwood_house_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-10");
			pchar.questTemp.HWIC.Self = "theft";
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//комнату закроем
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.FleetwoodJournal = 1;//положим в комод СЖ
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.sand_clock = 1;//и песочные часы
			AddDialogExitQuestFunction("CreateFleetwoodSoldiers");//4 солдат в доме
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
			SetFunctionTimerCondition("FleetwoodJournalOver", 0, 0, 11, false);//таймер
			pchar.quest.Fleetwood_Journal.win_condition.l1 = "Timer";
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l2 = "Hour";
			pchar.quest.Fleetwood_Journal.win_condition.l2.start.hour = 0;
			pchar.quest.Fleetwood_Journal.win_condition.l2.finish.hour = 3;
			pchar.quest.Fleetwood_Journal.win_condition.l3 = "locator";
			pchar.quest.Fleetwood_Journal.win_condition.l3.location = "SentJons_town";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator_group = "reload";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator = "houseSP3";//доступно открывание двери
			pchar.quest.Fleetwood_Journal.function = "FleetwoodHouseEnter";
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//если надумает раньше заявиться
			AddMapQuestMarkCity("sentjons", true);
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Nem, még nem. Vannak gyógynövényszakértôink és orvosaink, de egyiküknek sincs ilyen neve.","Most hallottam elôször ilyen furcsa nevet. Nem, még soha nem látogatott meg minket az az ember, akirôl beszél.","Nálunk egyáltalán nincsenek alkimisták. Orvosaink vannak, de ilyen furcsa nevûek nincsenek.");
			link.l1 = "Értem. Az nagy kár. Tovább keresgélek!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

string FindSpainCity()//Jason выбрать радномный испанский город - пусть побегает
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation == SPAIN && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}
