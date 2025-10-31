// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref FortChref;
	FortChref = GetFortCommander(NPChar.City);
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Mit akarsz? Kérdezzen csak.", "Figyelek rád, mi a kérdés?"), "Ez már a második alkalom, hogy megpróbálsz kérdezni...", "Ez a harmadik alkalom, hogy megpróbálod megkérdezni...",
                          "Mikor lesz ennek vége?! Elfoglalt ember vagyok, gyarmati ügyekkel foglalkozom, és te még mindig zaklatsz!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Ne most. Rossz helyen és rossz idôben."), "Igaz... De késôbb, nem most...",
                      "Megkérdezem... De egy kicsit késôbb...", "Sajnálom, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);			  
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_6")
			{
				link.l1 = "Excellenciás uram, a bebörtönzött tiszt, Lope Montoro miatt vagyok itt...";
                link.l1.go = "Mtraxx";
			}
		break;
		
		case "Cupture_after":
            dialog.text = RandPhraseSimple("Már mindent elvettél. Mit akarsz még?", "Maradt még valami, amit nem vittél el?");
            link.l1 = RandPhraseSimple("Csak körülnézek...", "Csak ellenôrzöm, lehet, hogy elfelejtettem valamit...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "Slavetrader_HavanaAttack":
			dialog.text = "Átkozott ladrones! Meg meritek támadni Havannát?! Mit akartok?!";
			link.l1 = "Gondolkodj egy kicsit, és meg fogod érteni.";
			link.l1.go = "Slavetrader_HavanaAttack_1";
			pchar.quest.Slavetrader_HavanaOver.over = "yes";
			AfterTownBattle();
        break;
		
		case "Slavetrader_HavanaAttack_1":
			dialog.text = "Aranyat, természetesen! Mi más érdekelhetne titeket, mint az arany?! És nekünk nincs... Csak néhány mérô a boltban.";
			link.l1 = "Ha-ha... Nem, minket nem érdekel az arany. Az elefántcsontért jöttünk ide... a feketéért. Megértettétek?";
			link.l1.go = "Slavetrader_HavanaAttack_2";
        break;
		
		case "Slavetrader_HavanaAttack_2":
			if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)//для особо хитрых - нефиг лезть с суши
			{
				dialog.text = "Ha! Gyanítottam, hogy rabszolgákért jöttetek ide. De azok az erôdben vannak. Az erôsítésünk most érkezik ide, és a bandátokat egy pillanat alatt elpusztítjuk.";
				link.l1 = "A francba! Rendben, ülj itt és ne mozdulj... Menjünk innen! A francba...";
				link.l1.go = "Slavetrader_HavanaAttack_lose";
			}
			else
			{
				dialog.text = "De hogyan... Honnan tudtad ezt?";
				link.l1 = "Ha! Csak egy idióta tud 5000 rabszolgát összegyûjteni egy helyre, és azt remélni, hogy senki sem tudja meg. Bûzlenek innen az istenverte Tortugáig... Remélem, megértitek, hogy elvisszük ôket tôletek.";
				link.l1.go = "Slavetrader_HavanaAttack_3";
			}
        break;
		
		case "Slavetrader_HavanaAttack_3":
			dialog.text = "Rendben, úgyis gyôztetek, és engedelmeskednünk kell az erôszakotoknak. De ne reméljétek, hogy megússzátok az igazságszolgáltatást azután a rablás és két spanyol hadihajó elsüllyesztése után.";
			link.l1 = "Ne fújd fel magad így, mert még szívrohamot kapsz. Ülj itt és ne mozdulj...";
			link.l1.go = "Slavetrader_HavanaAttack_4";
			ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 50);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
        break;
		
		 case "Slavetrader_HavanaAttack_4":
			string sTemp;
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//теперь можно на карту
            SetCharacterGoods(pchar, GOOD_SLAVES, 5000+rand(500));// c перегрузом пойдёт
            Log_SetStringToLog("Slaves have been put onto your ship");
			Log_SetStringToLog("You've got 30 days to deliver the slaves to your employer");
			chrDisableReloadToLocation = false;
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			AddQuestRecord("Slavetrader", "27");
			AddQuestUserData("Slavetrader", "sQty", sTemp);
			SetFunctionTimerCondition("Slavetrader_FiveTSlavesOver", 0, 0, 30, false);	//таймер
			pchar.questTemp.Slavetrader = "Win_HavanaFort";
        break;
		
		case "Slavetrader_HavanaAttack_lose":
            NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -8);
            Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			chrDisableReloadToLocation = false;
			pchar.quest.Slavetrader_DieHardHavana.over = "yes";//можно на карту
			pchar.quest.Slavetrader_HavanaAttack.over = "yes";//если из Сантьяго по суше пришёл - уберем корабли
			AddQuestRecord("Slavetrader", "27_1");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
        break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "Mtraxx":
            dialog.text = "Milyen kíváncsi... még több panasz?";
			link.l1 = "Nem, nem, épp ellenkezôleg, excellenciás uram. Lope régi katona barátom, együtt harcoltunk Európában... Szeretnék segíteni neki, és azért jöttem, hogy a segítségét kérjem.";
			link.l1.go = "Mtraxx_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtraxx_1":
            dialog.text = "Hm... Nos, feltételezem, ha már eljött hozzám, akkor már ismeri ezt az... abszurd történetet?";
			link.l1 = "Igen, excellenciás uram.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "Azt javaslom, lépjen kapcsolatba don Rosario Gusmannal. Ô is, akárcsak ön, segíteni akar don Lope Monteronak. Megpróbált kapcsolatba lépni az áldozattal, de a tárgyalások nem vezettek eredményre. Találkozzon vele, ô majd elmagyarázza a részleteket. Don Rosario-t délután négy és nyolc óra között találja az utcán. Minden nap teljes ellenôrzést tart a városôrségnél.";
			link.l1 = "Köszönöm, Excellenciád!";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_7";
			AddQuestRecord("Roger_1", "17");
			Mtraxx_CreateRosario();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
