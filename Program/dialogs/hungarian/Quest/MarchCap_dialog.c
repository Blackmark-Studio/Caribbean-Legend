void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iQty;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Egy bogár. Mindenképpen szólj a fejlesztôknek.";
			link.l1 = "OK.";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarchCap":
			pchar.quest.MarchCapOver.over = "yes"; //снять прерывание
			dialog.text = "Tessék, kapitány. Beszéljük meg az ajánlatom részleteit. Meg fogja érteni, miért nem akartam errôl nyilvánosan beszélni.";
			link.l1 = "Folytassa, uram. Hallgatom.";
			link.l1.go = "MarchCap_1";
		break;
		
		case "MarchCap_1":
			pchar.GenQuest.MarchCap.Goods = SelectMarchCapGoods1();//целевой товар
			switch (rand(2))
			{
				case 0: //конвой у острова, установка параметров
					pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					while(pchar.GenQuest.MarchCap.Island == pchar.GenQuest.MarchCap.Startisland)
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					}
					pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
					while(pchar.GenQuest.MarchCap.Island.Shore == "")
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
						pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
						if (!isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island) || !isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island.Shore)) pchar.GenQuest.MarchCap.Island.Shore = "";
					}
					pchar.GenQuest.MarchCap.DaysQty = GetMaxDaysFromIsland2Island(pchar.GenQuest.MarchCap.Startisland, pchar.GenQuest.MarchCap.Island)+3;
					dialog.text = "Sikerült megtudnom, hogy a "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" zászló alatt egy kis kereskedelmi konvoj "+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+", két kereskedelmi hajó és egy ôrhajó, a "+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen")+"közelében fog hajózni, ez nem messze van a "+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen")+". A kereskedôk rengeteg "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" van a rakterükben. Butaság lenne nem kihasználni ezt az információt, kapitány\nazt, hogy mi ketten könnyedén elbánunk az ôrökkel, és magunkhoz vehetjük a rakományt. Szóval, benne vagy?";
					link.l1 = "Csábítóan hangzik. Én igent mondanék!";
					link.l1.go = "MarchCap_1_1";
					link.l2 = "Néhány"+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" nem elég nekem, hogy elrontsam a kapcsolatomat a "+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+". Nem, ezt nem fogom megtenni! Viszontlátásra, uram, és meg se próbáljon megállítani!";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 1: //энкаунтер на глобалке, установка параметров
					pchar.GenQuest.MarchCap.Startcity = SelectAnyColony(pchar.GenQuest.MarchCap.basecity);
					pchar.GenQuest.MarchCap.Finishcity = SelectAnyColony2(pchar.GenQuest.MarchCap.basecity, pchar.GenQuest.MarchCap.Startcity);
					pchar.GenQuest.MarchCap.DaysQty = 5+hrand(5);
					dialog.text = "Sikerült megtudnom, hogy "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" egy kis kereskedelmi konvoj a "+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+"zászló alatt , két kereskedelmi hajó és egy ôrhajó, fog közlekedni "+XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Startcity+"Gen")+" és "+XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Finishcity+"Acc")+"között. A kereskedôk rakterében sok "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" van. Butaság lenne nem felhasználni ezt az információt, kapitány.\nMaga és én könnyen elbánhatunk az ôrökkel, és magunkhoz vehetjük a rakományt. A legnehezebb a két kolónia közötti nyílt tengeren megtalálni ôket. Szóval, benne vagytok?";
					link.l1 = "Csábítóan hangzik. Én igent mondanék!";
					link.l1.go = "MarchCap_2_1";
					link.l2 = "Néhány "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" nem elég nekem, hogy elrontsam a kapcsolatomat a "+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+". Nem, ezt nem fogom megtenni! Viszontlátásra, uram, és meg se próbáljon megállítani!";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 2: //одиночный пиратский кулсейлор у бухты, установка параметров
					pchar.GenQuest.MarchCap.Goods = GOOD_GOLD + hrand(makeint(GOOD_SILVER - GOOD_GOLD));
					pchar.GenQuest.MarchCap.GoodsQty = sti(pchar.rank)*50+170+rand(30);
					if (sti(pchar.GenQuest.MarchCap.GoodsQty) > 1600) pchar.GenQuest.MarchCap.GoodsQty = 1500+rand(100);
					pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					while(pchar.GenQuest.MarchCap.Island == pchar.GenQuest.MarchCap.Startisland)
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
					}
					pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
					while(pchar.GenQuest.MarchCap.Island.Shore == "")
					{
						pchar.GenQuest.MarchCap.Island = GetRandIslandId();
						pchar.GenQuest.MarchCap.Island.Shore = GetIslandRandomShoreId(pchar.GenQuest.MarchCap.Island);
						if (!isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island) || !isLocationFreeForQuests(pchar.GenQuest.MarchCap.Island.Shore)) pchar.GenQuest.MarchCap.Island.Shore = "";
					}
					pchar.GenQuest.MarchCap.DaysQty = GetMaxDaysFromIsland2Island(pchar.GenQuest.MarchCap.Startisland, pchar.GenQuest.MarchCap.Island)+1;
					pchar.GenQuest.MarchCap.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);//пират
					pchar.GenQuest.MarchCap.ShipType = SelectPirateShipType();
					pchar.GenQuest.MarchCap.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.MarchCap.ShipType));
					dialog.text = "Egy "+GetName( NAMETYPE_ORIG, pchar.GenQuest.MarchCap.PirateName, NAME_NOM)+"nevû kalózról tájékoztattak. Ez a bandita nemrégiben megcsípte "+RandPhraseSimple(RandPhraseSimple("angol","francia"), RandPhraseSimple("spanyol","holland"))+" és megrakta a rakterét "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+". De milyen kár, hogy hajója "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.ShipType), "neve")+"Acc"))+" súlyosan megsérült, így idôt kellett szánnia a javításra.\nÔ jelenleg "+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen")+" a "+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen")+". Azt hiszem, hogy körülbelül "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" kell neki, hogy kijavítsa az árbocokat és a hajótesten lévô lyukakat. Idôben odaérhetünk, ha sietünk, és az egész "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" a miénk lesz\nEgyedül nem fogok tudni elbánni ezzel a kalózzal, nagyon jó tengerész és harcos, de ketten sikeresen szembeszállhatunk vele a tapasztalata ellenére. Szóval, benne vagy vagy nem?";
					link.l1 = "Csábítóan hangzik. Én igent mondanék!";
					link.l1.go = "MarchCap_3_1";
					link.l2 = "Hm. Úgy tûnik, hogy ez a díj nem csak számodra, hanem mindkettônk számára elérhetetlen. Nem, én ezt nem fogom megtenni, viszlát, uram, és meg se próbáljon megállítani!";
					link.l2.go = "MarchCap_exit";
				break;
			}
		break;
		
		case "MarchCap_1_1":
			dialog.text = "Tudtam, hogy számíthatok rád! Ne vesztegessünk el egyetlen percet sem! Menjen a hajójához és menjen az élre, én követem. Itt az ideje, hogy kihajózzunk!";
			link.l1 = "Parancsot kapitány, horgonyt fel, kapitány!";
			link.l1.go = "MarchCap_1_2";
		break;
		
		case "MarchCap_1_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "Timer";
			pchar.quest.MarchCap1_1.win_condition.l1.date.hour  = sti(GetTime()+rand(10));
			pchar.quest.MarchCap1_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l2 = "location";
			pchar.quest.MarchCap1_1.win_condition.l2.location = pchar.GenQuest.MarchCap.Island;
			pchar.quest.MarchCap1_1.function = "MarchCap1_CreateConvoy";
			SetFunctionTimerCondition("MarchCap_Attack_Over", 0, 0, sti(pchar.GenQuest.MarchCap.DaysQty)+2, false); //таймер на нахождение
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "1");
			AddQuestUserData("MarchCap", "sShore", XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen"));
			AddQuestUserData("MarchCap", "sIsland", XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
		break;
		
		case "MarchCap_TimeOver":
			dialog.text = "És miért keveredtem magával, kapitány? Miattad vesztettünk el egy ilyen értékes zsákmányt! Legközelebb inkább egyedül hajózom...";
			link.l1 = "A te hibád, nem az enyém. Viszontlátásra.";
			link.l1.go = "MarchCap_Talk_exit";
			pchar.GenQuest.MarchCap = "late";
		break;
		
		case "MarchCap_Talk_exit":
			pchar.quest.MarchCap1_fail2.over = "yes"; //снять прерывание
			pchar.quest.MarchCap1_fail1.over = "yes"; //снять прерывание
			pchar.quest.MarchCap1_fail.over = "yes"; //снять прерывание
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			DeleteAttribute(npchar, "AlwaysFriend");
			npchar.DontDeskTalk = true;
			if (CheckAttribute(pchar, "GenQuest.MarchCap.Deck"))
			{
				PChar.quest.Munity = "Deads";
				LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			}
			else
			{
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				chrDisableReloadToLocation = false;
			}
			RemoveCharacterCompanion(pchar, npchar);
			npchar.location = pchar.location;
			if (pchar.GenQuest.MarchCap == "late") AddQuestRecord("MarchCap", "2");
			if (pchar.GenQuest.MarchCap == "bad") AddQuestRecord("MarchCap", "5");
			if (pchar.GenQuest.MarchCap == "poor" || pchar.GenQuest.MarchCap == "good" || pchar.GenQuest.MarchCap == "exellent")
			{
				iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
				iTemp = iQty-sti(pchar.GenQuest.MarchCap.CapPart);
				RemoveCharacterGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods), iQty);
				AddCharacterGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods), iTemp);
				if (pchar.GenQuest.MarchCap == "poor") AddQuestRecord("MarchCap", "6");
				if (pchar.GenQuest.MarchCap == "good") AddQuestRecord("MarchCap", "7");
				if (pchar.GenQuest.MarchCap == "exellent") AddQuestRecord("MarchCap", "8");
			}
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
			CloseQuestHeader("MarchCap");
			DeleteAttribute(pchar, "GenQuest.MarchCap");
		break;
		
		case "MarchCap_AfterBattle":
			iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty))*sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
			iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
			pchar.GenQuest.MarchCap.CapPart = iQty/sti(pchar.GenQuest.MarchCap.Parts);
			if (iTemp < 50)
			{
				dialog.text = "Maga egy vesztes, kapitány! Nem kaptunk egy darabot sem! És ez mind miattad van! Te vagy az oka a mi hibánknak, a fenébe is!";
				link.l1 = "Tényleg? Nézz magadra! Nem segítettél nekem a csatában! Csak az idômet vesztegettem veled... Tûnj el a hajómról!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 50 && iTemp < 500)
			{
				dialog.text = "Nos, ez a rajtaütés nem volt olyan sikeres, mint vártam, a zsákmányunk nagyon szerény... Mindegy, kapitány, osszuk meg ezeket a maradékokat és búcsúzzunk el egymástól.";
				link.l1 = "Ha segítettél volna nekem ahelyett, hogy madarakat számolsz az égen, a rajtaütés sikeres lett volna... Vedd ki a részed - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+" és tûnj el!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 500 && iTemp < 1500)
			{
				dialog.text = "Szép munka, kapitány! Ahogy mondtam - elég könnyû volt kiüríteni a raktereket azoktól a kereskedôktôl, ha-ha... A nyeremény "+FindRussianQtyString(iQty)+" darab. Az én részem "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
				link.l1 = "Helyes, "+npchar.name+". Nincs ellenvetésem. A hosszúhajókat éppen most rakodják. Talán a jövôben még egyszer együtt fogunk rajtaütni? Megfelelô társnak tûnsz számomra.";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "Kitûnô, kapitány! Ahogy mondtam - viszonylag könnyû volt kiüríteni a raktereket azoktól a kereskedôktôl, ha-ha... A nyeremény hatalmas, sokkal több, mint amire számítottam. Ez "+FindRussianQtyString(iQty)+" darab. Az én részem "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
			link.l1 = "Helyes, "+npchar.name+". Nincs ellenvetésem. A hosszúhajókat éppen most rakodják. Talán a jövôben még egyszer együtt fogunk rajtaütni? Megfelelô társnak tûnsz számomra.";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		//если будет время - здесь создаем ещё одного клона с уникальным ИД для продолжения квеста
		case "MarchCap_Deck_continue":
			dialog.text = "Van egy lehetôség, kapitány. Megkereslek, ha kapok egy másik jövedelmezô nyomot, amit egyedül nem tudnék megtenni. Úgy nézel ki, mint egy megbízható harcostárs számomra is.";
			link.l1 = "Szép volt! Viszlát, kapitány. Sok szerencsét!";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_2_1":
			dialog.text = "Tudtam, hogy számíthatok rád! Ne vesztegessünk el egyetlen percet sem! Menjen a hajójához és menjen az élre, én követem. Itt az ideje, hogy kihajózzunk!";
			link.l1 = "Parancs a lehorgonyzásra, kapitány.";
			link.l1.go = "MarchCap_2_2";
		break;
		
		case "MarchCap_2_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "Timer";
			pchar.quest.MarchCap1_1.win_condition.l1.date.hour  = sti(GetTime()+rand(10));
			pchar.quest.MarchCap1_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.function = "MarchCap2_CreateConvoy";
			pchar.GenQuest.MarchCap.WdmEnc = "true";
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "10");
			AddQuestUserData("MarchCap", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Startcity+"Gen"));
			AddQuestUserData("MarchCap", "sCity2", XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Finishcity+"Acc"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
		break;
		
		case "MarchCap_3_1":
			dialog.text = "Tudtam, hogy számíthatok rád! Ne vesztegessünk el egy percet sem. Menj a hajódhoz és vezess engem. Itt az idô, hogy kihajózzunk!";
			link.l1 = "Parancsot kapitány, horgonyt fel, kapitány.";
			link.l1.go = "MarchCap_3_2";
		break;
		
		case "MarchCap_3_2":
			DialogExit();
			NextDiag.CurrentNode = "MarchCap_repeat";
			Group_DelCharacter("MarchGroup", "MarchCap");
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			SetCharacterRemovable(npchar, false);
			Character_SetAbordageEnable(npchar, false);
			npchar.Tasks.CanBoarding = false; // запрет идти на абордаж // Addon 2016-1 Jason Пиратская линейка
			pchar.quest.MarchCap1_1.win_condition.l1 = "location";
			pchar.quest.MarchCap1_1.win_condition.l1.location = pchar.GenQuest.MarchCap.Island;
			pchar.quest.MarchCap1_1.function = "MarchCap3_CreatePirate";
			SetFunctionTimerCondition("MarchCap_Attack_Over", 0, 0, sti(pchar.GenQuest.MarchCap.DaysQty), false); //таймер
			pchar.quest.MarchCap1_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.MarchCap1_fail.win_condition.l1.character = "MarchCap";
			pchar.quest.MarchCap1_fail.function = "MarchCap_fail";
			pchar.GenQuest.MarchCap.Pirate = "true";
			ReOpenQuestHeader("MarchCap");
			AddQuestRecord("MarchCap", "11");
			AddQuestUserData("MarchCap", "sShore", XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen"));
			AddQuestUserData("MarchCap", "sIsland", XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen"));
			AddQuestUserData("MarchCap", "sDays", FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty)));
			AddQuestUserData("MarchCap", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods)));
			AddQuestUserData("MarchCap", "sName", GetFullName(npchar));
			AddQuestUserData("MarchCap", "sName1", GetName(NAMETYPE_ORIG, pchar.GenQuest.MarchCap.PirateName, NAME_NOM));
		break;
		
		case "MarchCap_DieHard":
			dialog.text = "Gyáva vagy, a fenébe is! Épp most futottál el a csatatérrôl!";
			link.l1 = "És mit gondolsz, mit kellett volna tennem? Hagyni, hogy az a kalóz elsüllyessze a hajómat? Szó sem lehet róla, inkább legyek élô gyáva, mint egy halott idióta!";
			link.l1.go = "MarchCap_DieHard_1";
		break;
		
		case "MarchCap_DieHard_1":
			dialog.text = "És miért is keveredtem veled össze, kapitány? Találnom kellett volna egy olyan embert, aki nem fél a deszantkardoktól!";
			link.l1 = " Most pedig kérem, hagyja el a hajómat - meg kell javítanom.";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_AfterBattleGold":
			iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty))*sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
			iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
			pchar.GenQuest.MarchCap.CapPart = iQty/sti(pchar.GenQuest.MarchCap.Parts);
			if (iTemp < 10)
			{
				dialog.text = "Maga egy vesztes, kapitány! Egy darabot sem kaptunk a zsákmányunkból! És ez mind miattad van! Te vagy az oka a hibánknak, a fenébe is!";
				link.l1 = "Tényleg? Nézz magadra! Nem segítettél nekem a csatában! Csak az idômet vesztegettem veled... Tûnj el a hajómról!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 10 && iTemp < 100)
			{
				dialog.text = "Nos, ez a rajtaütés nem volt olyan sikeres, mint vártam, a zsákmányunk nagyon szerény... Mindegy, kapitány, osszuk meg ezeket a maradékokat és búcsúzzunk el egymástól.";
				link.l1 = "Ha segítettél volna nekem ahelyett, hogy madarakat számolsz az égen, a rajtaütés sikeres lett volna... Vedd ki a részed - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+" és tûnj el!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 100 && iTemp < 500)
			{
				dialog.text = "Szép munka, kapitány! A nyeremény "+FindRussianQtyString(iQty)+" darab. Az én részem "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
				link.l1 = "Helyes, "+npchar.name+". Nincs ellenvetésem. A hosszúhajókat éppen most rakodják. Talán még találkozunk...";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "Nagyszerû, kapitány! Ahogy mondtam - elég könnyû volt, ha-ha... A nyeremény hatalmas, sokkal több, mint amire számítottam. Ez "+FindRussianQtyString(iQty)+" darab. Az én részem "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
			link.l1 = "Helyes, "+npchar.name+". Nincs ellenvetésem. A hosszúhajókat éppen most rakodják. Talán a jövôben még egyszer együtt fogunk rajtaütni? Megfelelô társnak tûnsz számomra.";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "MarchCap_repeat":
			dialog.text = ""+GetAddress_Form(NPChar)+", Menjetek a hajótokra. Nincs idônk beszélgetni. Vitorlát bontani!";
			link.l1 = "Igen, igen, persze, igazad van.";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarchCap_repeat";
		break;
		
		case "MarchCap_exit":
			dialog.text = "Hm... Nem fogok. Tûnjetek el! Majd én megcsinálom egyedül!";
			link.l1 = "Nos, nos, akkor jó utat...";
			link.l1.go = "MarchCap_DeckExit";
		break;
		
		case "MarchCap_DeckExit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(npchar, "AlwaysFriend");
			npchar.DontDeskTalk = true;
			DeleteAttribute(pchar, "GenQuest.MarchCap");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

int SelectMarchCapGoods1()
{
	int iGoods;
	switch (hrand(5))
	{
		case 0: iGoods = GOOD_EBONY; break;
		case 1: iGoods = GOOD_MAHOGANY; break;
		case 2: iGoods = GOOD_CINNAMON; break;
		case 3: iGoods = GOOD_COFFEE; break;
		case 4: iGoods = GOOD_CHOCOLATE; break;
		case 5: iGoods = GOOD_TOBACCO; break;
	}
	return iGoods;
}

int SelectPirateShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 5;
	if(iRank >= 12 && iRank < 21) iClass = 4;
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
}
