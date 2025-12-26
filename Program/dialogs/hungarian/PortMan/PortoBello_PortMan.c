// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	int i,n;
	string month;
	
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdések?", "Mit akarsz, " + GetAddress_Form(NPChar) + "?"), "Már próbáltál kérdezni " + GetAddress_Form(NPChar) + "...", "Ma már harmadszor beszélsz valamilyen kérdésrôl...",
                          "Nézze, ha nincs mondanivalója a kikötô ügyeirôl, akkor ne zavarjon a kérdéseivel.", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam.", "Nincs mirôl beszélnem."), "Nevermind.", "Valóban, már harmadszor...", 
						"Sajnálom, de egyelôre nem érdekelnek a kikötô ügyei.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello_1")
            {
                link.l1 = "Jó napot kívánok. Szeretném megtudni, hol van Francois Gontier kapitány. Van egy fontos ügyem.";
                link.l1.go = "Portobello_ratP_1";
            }
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toPBPortOffice" || pchar.questTemp.SharkGoldFleet == "KillCurier")
				{
					link.l1 = "Kereskedô vagyok, Caracasból jöttem, és az ön kollégája a helyi kikötôi hatóságtól megkért, hogy adjak át önnek néhány levelet ...";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "MoneySpeak")
				{
					link.l1 = "Igen, a fizetségért jöttem.";
					link.l1.go = "SharkGoldFleet_11";
				}
			}
			//<-- на пару с Акулой
		break;

		case "Portobello_ratP_1":
			dialog.text = "Azt mondja, fontos ügy? Lássuk csak. Nos...  Francois Gontier, a korvettben '" + pchar.questTemp.Slavetrader.ShipName + "'... A jegyzeteim szerint Senor Gontier Jamaica felé tartott.";
			link.l1 = "Köszönöm, uram! Sokat segítettél!";
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
			dialog.text = "Á, végre! Azt mondja, maga kereskedô? Megint megpróbálnak spórolni a futárokon, és az utolsó pillanatig halogatják a szállítást... Igen, hát persze, hogyne! Ez így igaz. És így kellene felszerelnem velük a századot ilyen idôkeretben?...";
			link.l1 = "Felelôtlenül hangzik...";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Így is lehet ezt mondani! Nos, rendben, mit tegyünk. Idôben találkozunk... Én az enyémrôl beszélek, ne is figyelj oda. Figyelj, véletlenül nem mész vissza?";
			link.l1 = "Hát, tulajdonképpen úgy volt, hogy itt fogom eladni az árut, aztán - igen, visszamegyek Caracasba ...";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Nagyszerû! Most majd írok nekik egy választ, és megkérem, hogy küldje vissza. Szóval... Szállítsa le, kérem, tíz napon belül, különben nem lesz idejük idôben csinálni semmit... És mondd meg a neved.";
			if(pchar.questTemp.SharkGoldFleet == "KillCurier")
			{
				link.l1 = "A nevem "+GetFullName(pchar)+".";
				link.l1.go = "SharkGoldFleet_03";
			}
			else
			{
				link.l1 = "A nevem Andreas Garcia.";
				link.l1.go = "SharkGoldFleet_09";
			}
		break;
		
		case "SharkGoldFleet_03":
			TakeNItems(pchar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_SharkGoldFleet_2");
			dialog.text = "Várj egy percet... Felvétel. Tessék, tessék. Ne feledje: tíz nap! Addig is elolvasom részletesebben, amit hoztál nekem.";
			link.l1 = "Igen, emlékszem. Viszontlátásra!";
			link.l1.go = "SharkGoldFleet_04";
		break;

		case "SharkGoldFleet_04":
			dialog.text = "Várj egy percet... Nem értem... Még egyszer, mit is mondtál, hogy hívnak?";
			link.l1 = "Én?... Hát... Miért olyan fontos ez?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			n = GetAddingDataDay(0,0,21);
			if(n<21) i = GetAddingDataMonth(0,1,0);
			else i = GetDataMonth();
			month = XI_ConvertString("MonthGen_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Felfedezô mód: az idôzítô ki van kapcsolva.");
			dialog.text = "Ez nagyon fontos! Azt mondja... Tehát... "+n+" "+month+"... Nem, ez nem az... 12, 50, 69, 55... De hol van... Á, itt van! A levelet a kapitánynak kell kézbesítenie "+pchar.questTemp.SharkGoldFleet.CurierName+" "+pchar.questTemp.SharkGoldFleet.Curierlastname+". És azt mondta, hogy a neve... "+GetFullName(pchar)+"?";
			link.l1 = "Biztos valami tévedés történt...";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.CurierName");
			DeleteAttribute(pchar,"questTemp.SharkGoldFleet.Curierlastname");
			dialog.text = "Nem, nem lehet tévedés. Adja vissza a levelet, amit adtam. Ki kell derítenem ezt az egészet!";
			link.l1 = "Gyerünk már... Átadom, minden rendben lesz.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Ne! Ne! Add vissza a levelet! Ôrség!!!";
			link.l1 = "Ah, a nehezebb utat akarod választani, mi?";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			pchar.questTemp.SharkGoldFleet = "DifficultVar";
			if (CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				TakeNationLicence(HOLLAND);
				log_info("Kereskedelmi engedélyt törölték!");
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
			dialog.text = "Várj egy percet... Itt is van. Akkor majd felírom a neved a válaszlevélbe. Tessék, tessék. Ne feledje: tíz napja van! Addig is elolvasom részletesebben, amit hoztál nekem.";
			link.l1 = "Igen, emlékszem. Viszontlátásra!";
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
			dialog.text = "Fizetés?..";
			link.l1 = "Caracasban a kollégája azt mondta nekem, hogy a levél kézbesítéséért fizetni fog.";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "Nem, hát ott teljesen megôrültek! Most nekem kell fizetnem értük!";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "És mennyit ígértek neked?";
			link.l1 = "Ötezer pezót.";
			link.l1.go = "SharkGoldFleet_14";
			link.l2 = "Tízezer pezó.";
			link.l2.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_14":
			pchar.questTemp.SharkGoldFleet = 5000;
			dialog.text = "Úgy tûnik, úgy döntöttek, hogy az én költségemen fognak ott élni... Nem elég, hogy nem akarnak pénzt költeni futárokra, az ilyen ügyeket átutazó kereskedôhajókra bízzák, még a költségeket is rám akasztják! Panaszt fogok írni ellenük Havannába!";
			link.l1 = "Megértem a felháborodását, senor, de mit tegyek?";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_15":
			pchar.questTemp.SharkGoldFleet = 10000;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeOfficersLoyality("bad", 1);
			dialog.text = "Úgy látszik, úgy döntöttek, hogy az én költségemen élnek ott... Nem elég, hogy nem akarnak pénzt költeni futárokra, az ilyen ügyeket átutazó kereskedelmi hajókra bízzák, még a költségeket is rám akasztják! Panaszt fogok írni ellenük Havannába!";
			link.l1 = "Megértem a felháborodását, senor, de mit tegyek?";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "Argh, nem ön tehet a caracasi új-spanyol tisztviselôk kapzsiságáról. De nekem most nincs nálam annyi pénz. És a költségvetésnek csak holnap kellene megérkeznie ... Várjon itt, kérem, most elmegyek a pénzkölcsönzôhöz - és mindjárt visszajövök.";
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
			month = XI_ConvertString("MonthGen_" + i);
			pchar.questTemp.SharkGoldFleet.Date = ""+n+" "+month+"";
			SetFunctionTimerCondition("SharkGoldFleet1269fail", 0, 0, 22, false);
			SetFunctionTimerCondition("SGF_FleetTime", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToCPO10", 0, 0, 10, false);
			else NewGameTip("Felfedezô mód: az idôzítô ki van kapcsolva.");
			AddQuestRecord("SharkGoldFleet", "18");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			LAi_SetHuberType(npchar);
			Lai_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			dialog.text = "Elnézést a várakozásért. Itt van a "+makeint(pchar.questTemp.SharkGoldFleet)+" nyolc darab. És ebben az esetben ôk maguk fizetnek a válaszért Caracasban. Mondd, hogy én voltam.";
			link.l1 = "Rendben, majd én továbbítom. Köszönöm és sok szerencsét!";
			link.l1.go = "exit";
			pchar.questTemp.SharkGoldFleet = "LightVar";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
