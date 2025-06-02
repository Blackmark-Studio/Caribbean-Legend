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
			dialog.text = "Ein Fehler. Stell sicher, dass du es den Entwicklern sagst.";
			link.l1 = "OK.";
			link.l1.go = "exit";
		break;
		
		//разговор на палубе
		case "MarchCap":
			pchar.quest.MarchCapOver.over = "yes"; //снять прерывание
			dialog.text = "Hier sind Sie, Kapitän. Lassen Sie uns die Details meines Angebots besprechen. Sie werden verstehen, warum ich nicht in der Öffentlichkeit darüber sprechen wollte.";
			link.l1 = "Gehen Sie weiter, Herr. Ich höre zu.";
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
					dialog.text = "Ich habe herausgefunden, dass in "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" eine kleine Handelskonvoi unter der Flagge von "+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+", zwei Handelsschiffe und ein Wachschiff, werden in der Nähe segeln "+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen")+", das ist nicht weit von "+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Geschlecht")+". Die Händler haben viel von "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" in ihren Laderäumen. Es wäre dumm, diese Information nicht zu nutzen, Kapitän\nWir beide können uns leicht mit den Wachen auseinandersetzen und die Ladung für uns nehmen. Also, bist du dabei?";
					link.l1 = "Klingt verlockend. Ich würde ja sagen!";
					link.l1.go = "MarchCap_1_1";
					link.l2 = "Etwas"+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" reicht mir nicht aus, um meine Beziehungen zu verderben mit "+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+". Nein, ich werde das nicht tun! Lebewohl, Herr, und versuchen Sie nicht einmal, mich aufzuhalten!";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 1: //энкаунтер на глобалке, установка параметров
					pchar.GenQuest.MarchCap.Startcity = SelectAnyColony(pchar.GenQuest.MarchCap.basecity);
					pchar.GenQuest.MarchCap.Finishcity = SelectAnyColony2(pchar.GenQuest.MarchCap.basecity, pchar.GenQuest.MarchCap.Startcity);
					pchar.GenQuest.MarchCap.DaysQty = 5+hrand(5);
					dialog.text = "Ich habe es geschafft herauszufinden, dass in "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" ein kleiner Handelskonvoi unter der Flagge von "+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+", zwei Handelsschiffe und ein Wachschiff werden von "+XI_ConvertString("Kolonie"+pchar.GenQuest.MarchCap.Startcity+"Gen")+" zu "+XI_ConvertString("Kolonie"+pchar.GenQuest.MarchCap.Finishcity+"Akk")+". Die Händler haben viel von "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" in ihren Laderäumen. Es wäre dumm, diese Informationen nicht zu nutzen, Kapitän.\nSie und ich können die Wachen leicht ausschalten und die Fracht für uns selbst nehmen. Der schwierigste Teil ist, sie auf offener See zwischen diesen beiden Kolonien zu finden. Also, bist du dabei?";
					link.l1 = "Klingt verlockend. Ich würde ja sagen!";
					link.l1.go = "MarchCap_2_1";
					link.l2 = "Etwas "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" reicht mir nicht aus, um meine Beziehungen zu verderben mit "+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+". Nein, ich werde das nicht tun! Auf Wiedersehen, Herr, und versuchen Sie nicht einmal, mich aufzuhalten!";
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
					dialog.text = "Ich wurde über einen Piraten namens "+GetName(NAMETYPE_ORIG,pchar.GenQuest.MarchCap.PirateName,NAME_NOM)+". Dieser Bandit hat kürzlich geklaut "+RandPhraseSimple(RandPhraseSimple("Englisch","Französisch"),RandPhraseSimple("Spanisch","Holländer"))+" und belud seinen Laderaum mit "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+". Aber, was für ein Jammer, sein Schiff "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.ShipType),"Name")+"Akk"))+" wurde stark beschädigt, daher musste er sich Zeit nehmen, um sie zu reparieren.\nEr ist derzeit bei "+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen")+" von "+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen")+". Ich denke, dass es ungefähr dauern wird "+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+" damit er die Masten und Löcher im Rumpf reparieren kann. Wenn wir uns beeilen, können wir rechtzeitig dort sein und alles "+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+" wird unser sein\nIch werde alleine nicht mit diesem Piraten fertig werden können, er ist ein sehr guter Seemann und Kämpfer, aber wir beide können ihm trotz seiner Erfahrung erfolgreich entgegentreten. Also, bist du dabei oder nicht?";
					link.l1 = "Klingt verlockend. Ich würde ja sagen!";
					link.l1.go = "MarchCap_3_1";
					link.l2 = "Hm. Es scheint, dass dieser Preis nicht nur für Sie, sondern für uns beide unerreichbar ist. Nein, ich werde das nicht tun, auf Wiedersehen, Herr, und versuchen Sie nicht einmal, mich aufzuhalten!";
					link.l2.go = "MarchCap_exit";
				break;
			}
		break;
		
		case "MarchCap_1_1":
			dialog.text = "Ich wusste, dass ich auf dich zählen konnte! Lass uns keine einzige Minute verschwenden. Geh zu deinem Schiff und übernimm das Kommando, ich werde folgen. Es ist Zeit, die Segel zu setzen!";
			link.l1 = "Befehl zum Ankern, Kapitän!";
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
			dialog.text = "Und warum habe ich mich mit euch, Kapitän, eingelassen? Wir haben wegen euch einen so wertvollen Preis verloren! Nächstes Mal segel ich lieber alleine...";
			link.l1 = "Dein Fehler, nicht meiner. Tschüss.";
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
				dialog.text = "Du bist so ein Verlierer, Kapitän! Wir haben kein Stück bekommen! Und das alles nur wegen dir! Du bist der Grund für unser Versagen, verdammt noch mal!";
				link.l1 = "Bin ich das? Sieh dich an! Du hast mir im Kampf nicht geholfen! Ich habe nur meine Zeit mit dir verschwendet... Verlasse mein Schiff!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 50 && iTemp < 500)
			{
				dialog.text = "Nun, dieser Überfall war nicht so erfolgreich, wie ich erwartet hatte, unsere Beute ist wirklich bescheiden... Wie auch immer, Kapitän, teilen wir diese Fetzen und verabschieden uns voneinander.";
				link.l1 = "Wenn du mir geholfen hättest, statt Vögel am Himmel zu zählen, wäre der Überfall erfolgreich gewesen... Nimm deinen Anteil - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+" und verschwinde!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 500 && iTemp < 1500)
			{
				dialog.text = "Gut gemacht, Kapitän! Wie ich sagte - es war ziemlich einfach, die Laderäume dieser Händler zu leeren, ha-ha... Der Preis ist "+FindRussianQtyString(iQty)+" Stücke. Mein Anteil ist "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
				link.l1 = "Das ist korrekt, "+npchar.name+". Ich habe keine Einwände. Die Langboote werden gerade beladen. Vielleicht werden wir in Zukunft noch einen Überfall zusammen machen? Du siehst aus wie ein passender Begleiter für mich.";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "Ausgezeichnet, Kapitän! Wie ich sagte - es war relativ einfach, die Frachträume dieser Händler zu leeren, ha-ha... Die Beute ist riesig, viel mehr als ich erwartet habe. Es ist "+FindRussianQtyString(iQty)+" Stücke. Mein Anteil ist "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
			link.l1 = "Es ist korrekt, "+npchar.name+". Ich habe keine Einwände. Die Langboote werden gerade beladen. Vielleicht werden wir in der Zukunft noch einmal zusammen einen Überfall machen? Du siehst aus wie ein passender Gefährte für mich.";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		//если будет время - здесь создаем еще одного клона с уникальным ИД для продолжения квеста
		case "MarchCap_Deck_continue":
			dialog.text = "Es besteht eine Möglichkeit, Kapitän. Ich werde Sie finden, wenn ich eine weitere profitable Spur bekomme, die ich alleine nicht bewältigen kann. Sie sehen für mich aus wie ein zuverlässiger Kampfgefährte.";
			link.l1 = "Schön! Auf Wiedersehen, Kapitän. Viel Glück!";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_2_1":
			dialog.text = "Ich wusste, dass ich auf dich zählen konnte! Lass uns keine einzige Minute verschwenden. Geh zu deinem Schiff und übernimm die Führung, ich folge dir. Es ist Zeit, die Segel zu setzen!";
			link.l1 = "Befehl zum Ankern, Kapitän.";
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
			dialog.text = "Ich wusste, dass ich auf dich zählen kann! Lass uns keine einzige Minute verschwenden. Geh zu deinem Schiff und führe mich. Es ist Zeit in See zu stechen!";
			link.l1 = "Befehl zum Ankern, Kapitän.";
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
			dialog.text = "Du bist ein Feigling, verdammt sei dich! Du bist einfach vom Schlachtfeld geflohen!";
			link.l1 = "Und was denkst du, was ich hätte tun sollen? Den Piraten mein Schiff versenken lassen? Auf keinen Fall, ich bin lieber ein lebender Feigling als ein toter Idiot!";
			link.l1.go = "MarchCap_DieHard_1";
		break;
		
		case "MarchCap_DieHard_1":
			dialog.text = "Und warum habe ich mich mit Ihnen eingelassen, Kapitän? Ich hätte einen Mann finden sollen, der keine Angst vor Enterdolchen hat!";
			link.l1 = " Nun bitte ich Sie, mein Schiff zu verlassen - Ich muss sie reparieren.";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_AfterBattleGold":
			iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty))*sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
			iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
			pchar.GenQuest.MarchCap.CapPart = iQty/sti(pchar.GenQuest.MarchCap.Parts);
			if (iTemp < 10)
			{
				dialog.text = "Du bist so ein Verlierer, Kapitän! Wir haben kein einziges Stück von unserer Beute bekommen! Und das ist alles wegen dir! Du bist der Grund für unser Versagen, verdammt seist du!";
				link.l1 = "Bin ich? Schau dich an! Du hast mir im Kampf nicht geholfen! Ich habe nur meine Zeit mit dir verschwendet... Verlasse mein Schiff!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 10 && iTemp < 100)
			{
				dialog.text = "Nun, dieser Überfall war nicht so erfolgreich, wie ich erwartet hatte, unsere Beute ist wirklich bescheiden... Wie auch immer, Kapitän, teilen wir diese Reste und verabschieden uns voneinander.";
				link.l1 = "Wenn du mir geholfen hättest, statt Vögel am Himmel zu zählen, wäre der Überfall erfolgreich gewesen... Nimm deinen Anteil - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+" und verschwinde!";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 100 && iTemp < 500)
			{
				dialog.text = "Gut gemacht, Kapitän! Der Preis ist "+FindRussianQtyString(iQty)+" Stücke. Mein Anteil ist "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
				link.l1 = "Das ist richtig, "+npchar.name+". Ich habe keine Einwände. Die Langboote werden gerade beladen. Vielleicht treffen wir uns wieder...";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "Prächtig, Kapitän! Wie ich sagte - es war ziemlich einfach, ha-ha... Der Preis ist riesig, viel mehr als ich erwartet habe. Es ist "+FindRussianQtyString(iQty)+" Stücke. Mein Anteil ist "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+".";
			link.l1 = "Das ist korrekt, "+npchar.name+". Ich habe keine Einwände. Die Langboote werden gerade beladen. Vielleicht werden wir in der Zukunft noch einmal zusammen einen Überfall machen? Du siehst aus wie ein passender Gefährte für mich.";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "MarchCap_repeat":
			dialog.text = ""+GetAddress_Form(NPChar)+", geh zu deinem Schiff. Wir haben keine Zeit zum Plaudern. Lass uns in See stechen!";
			link.l1 = "Ja, ja, natürlich, du hast recht.";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarchCap_repeat";
		break;
		
		case "MarchCap_exit":
			dialog.text = "Hm... Ich werde das nicht tun. Verschwinde! Ich mache das selbst!";
			link.l1 = "Nun, nun, dann gute Reise...";
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
