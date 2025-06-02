void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		bool ok = CheckFreeSitFront(npchar);
			if(hrand(11) > 8 && ok && !CheckAttribute(pchar, "GenQuest.Racing.Go") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0)//гонки на гидропланах
			{
				dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Mein Name ist "+GetFullName(NPChar)+", Ich bin ein Kapitän. Ich sehe, dass du auch ein Kapitän bist. Möchtest du dich mir anschließen und zusammen einen trinken? Auf meine Kosten.";
				link.l1 = "Warum nicht? Ich hätte nichts dagegen, ein paar Drinks in guter Gesellschaft zu haben.";
				link.l1.go = "Race_prepare";
				link.l2 = "Es tut mir leid, aber ich habe es eilig. Nächstes Mal.";
				link.l2.go = "exit";
				npchar.quest.race = "true";
			}
			else
			{
			//конвой торгового судна
				if(!CheckAttribute(pchar, "GenQuest.Escort.Trader") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && !CheckAttribute(npchar, "repeat_work") && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0 && GetCompanionQuantity(pchar) < 3)
				{
					dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Ich bin "+GetFullName(NPChar)+", ein Kaufmann. Ich nehme an, dass Sie ein Kapitän sind. Wie wäre es, ein paar tausend Pesos zu verdienen?";
					link.l1 = "Ich bin immer bereit, ein paar Münzen zu verdienen. Um welche Art von Arbeit handelt es sich?";
					link.l1.go = "Escort_choice";
					link.l2 = "Und welche Art von Arbeit kann der Händler vorschlagen, hm? Sein verrottetes Schiff zu schützen? Ich helfe nicht Profiteuren.";
					link.l2.go = "exit_distress";
					SaveCurrentNpcQuestDateParam(npchar, "repeat_work");
				}
				else
				{
					dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Wie geht es dir? Brauchst du etwas?";
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". Nein, das tue ich nicht. Wollte nur Hallo sagen. Genießen Sie Ihren Aufenthalt!";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "exit_distress":
			DialogExit();
			NextDiag.CurrentNode = "Trader_distress";
		break;
		
		case "Trader_distress":
			dialog.text = "Kapitän, wir haben bereits gesprochen, richtig? Sie 'helfen keinen Profitmachern', also was wollen Sie jetzt von mir?";
			link.l1 = "Ja, und du hast recht. Gut, sitz einfach hier auf deinem fetten Hintern und trink deinen Rum. Ich muss gehen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Trader_distress";
		break;
		
		case "Escort_choice"://первые развилки - выбираем между городом, бухтой и необитайкой
			pchar.GenQuest.Escort.Trader.StartCity = GetCurrentTown();//стартовый город
			pchar.GenQuest.Escort.Trader.ShipType = TraderShipType(&iTemp);//тип корабля торговца
			pchar.GenQuest.Escort.Trader.Nation = npchar.nation;//нация торговца
			switch (hrand(2))
			{
				case 0://город дружественный
					pchar.GenQuest.Escort.Trader.City = FindFriendCityToMC(false);//целевой город
					pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), GetArealByCityName(pchar.GenQuest.Escort.Trader.City))+5;//дни
					pchar.GenQuest.Escort.Trader.Money =  makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty) * 400 * ShipFactorMC() + iTemp * 700);//оплата от расстояния и классов кораблей ГГ и неписи
					pchar.GenQuest.Escort.Trader.Type1 = "true";//тип задания
					pchar.GenQuest.Escort.Trader.Chance = rand(1);
					pchar.GenQuest.Escort.Trader.Add = "to "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+"";
					dialog.text = "Ich möchte Sie bitten, mich zu begleiten zu "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+" innerhalb "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". Ich werde dich bezahlen "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "Und warum nicht? Es ist immer sicherer, zusammen zu segeln, das kann ich verstehen. Ich stimme zu.";
					link.l1.go = "EscortType";
					link.l2 = "Ich würde gerne helfen, aber ich gehe in eine andere Richtung.";
					link.l2.go = "Escort_exit";
				break;
				case 1://бухта
					GetEscortTraderShore();//целевая бухта
					while(pchar.GenQuest.Escort.Trader.City == "Terks" || pchar.GenQuest.Escort.Trader.City == "caiman" || pchar.GenQuest.Escort.Trader.City == "dominica" 
							|| pchar.GenQuest.Escort.Trader.City == "Pearl" || pchar.GenQuest.Escort.Trader.City == "Tenotchitlan")
					{
						GetEscortTraderShore();
					} // patch-6
					pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), pchar.GenQuest.Escort.Trader.Island)+5;//дни
					pchar.GenQuest.Escort.Trader.Money =  makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty) * 400 * ShipFactorMC() + iTemp * 700);//оплата
					pchar.GenQuest.Escort.Trader.Type2 = "true";//тип задания
					pchar.GenQuest.Escort.Trader.Chance = rand(2);
					pchar.GenQuest.Escort.Trader.Add = "to "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+", not far from "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+"";
					dialog.text = "Ich möchte Sie bitten, mich zu begleiten zu "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+", nicht weit von "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+" innerhalb "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". Ich werde dich bezahlen "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "Und warum nicht? Es ist immer sicherer, zusammen zu segeln, das kann ich verstehen. Ich stimme zu.";
					link.l1.go = "EscortType";
					link.l2 = "Ich würde gerne helfen, aber ich gehe in die andere Richtung.";
					link.l2.go = "Escort_exit";
				break;
				case 2://необитайка
					pchar.GenQuest.Escort.Trader.Island = DesIsland();//целевой остров
					pchar.GenQuest.Escort.Trader.Shore = SelectQuestShoreLocationFromSea(pchar.GenQuest.Escort.Trader.Island);//и бухта на нём
					pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), pchar.GenQuest.Escort.Trader.Island)+5;//дни
					pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty) * 400 * ShipFactorMC() + iTemp * 700);//оплата
					pchar.GenQuest.Escort.Trader.Type3 = "true";//тип задания
					pchar.GenQuest.Escort.Trader.Chance = rand(2);
					pchar.GenQuest.Escort.Trader.Add = "to "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+" of inhabitant island "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Island)+"";
					dialog.text = "Ich möchte Sie bitten, mich zu begleiten zu "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+" welcher ist bei "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Island)+", in "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". Ich werde dich bezahlen "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "Und warum nicht? Es ist immer sicherer zusammen zu segeln, das kann ich verstehen. Ich stimme zu. Aber ich habe noch nie von Geschäften und Handelsposten dort gehört.";
					link.l1.go = "EscortType";
					link.l2 = "Ich würde gerne helfen, aber ich gehe in die andere Richtung.";
					link.l2.go = "Escort_exit";
				break;
			}
		break;
		
		case "Escort_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Escort.Trader");
		break;
		
		case "Trader_wait":
			dialog.text = "Sind Sie bereit zu segeln, Kapitän? Ich warte auf Ihre Befehle.";
			link.l1 = "Ja, wir werden jetzt in See stechen. Wir sehen uns im Hafen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Trader_wait";
		break;
		
		case "EscortType":
			dialog.text = "Herrlich! Ich bin froh, dass wir einen Deal gemacht haben. Ich hoffe, dass unsere Reise sicher sein wird.";
			link.l1 = "So auch ich. Es ist Zeit, die Segel zu setzen!";
			link.l1.go = "EscortType_go";
			NextDiag.CurrentNode = "Trader_wait";
		break;
		
		case "EscortType_go":
			//общие параметры
			DialogExit();
			pchar.GenQuest.Escort.Trader.id = npchar.id;
			CreateTraderShipAndAdd(npchar);//присоединяем торговца
			pchar.GenQuest.Escort.Trader.ShipMaxHP = sti(npchar.ship.HP);
			ReOpenQuestHeader("TraderEscort");
			AddQuestRecord("TraderEscort", "1");
			AddQuestUserData("TraderEscort", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty)));
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddQuestUserData("TraderEscort", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.StartCity+"Gen"));
			AddQuestUserData("TraderEscort", "sAdd", pchar.GenQuest.Escort.Trader.Add);
			pchar.GenQuest.Escort.Trader = "begin";
			//различные параметры
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type1"))//в дружественный город
			{
				pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.City+"_tavern";
			if (sti(pchar.GenQuest.Escort.Trader.Chance) == 1) CoolTraderHunterOnMap();
				else TraderHunterOnMap();//запуск ДУ на глобалке
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2"))//в бухту
			{
				pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.Shore;
				if (sti(pchar.GenQuest.Escort.Trader.Chance) != 2) TraderHunterOnMap();
				else
				{
					pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
					pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
					pchar.quest.EscortTrader_Attack.function = "EscortTraderAttackInShore";
				}
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type3"))//на необитайку
			{
				pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.Shore;
				if (sti(pchar.GenQuest.Escort.Trader.Chance) == 0) TraderHunterOnMap();
				if (sti(pchar.GenQuest.Escort.Trader.Chance) == 1) 
				{
					if(sti(RealShips[sti(pchar.Ship.Type)].Class) >= sti(RealShips[sti(pchar.GenQuest.Escort.Trader.ShipType)].Class) && sti(RealShips[sti(pchar.Ship.Type)].BaseType) != SHIP_GALEON_H && GetCompanionQuantity(pchar) < 3)//меряемся кораблями
					{//нападет сам
						pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
						pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
						pchar.quest.EscortTrader_Attack.function = "DesIslandAttack";
					}
					else CoolTraderHunterOnMap();
				}
				else
				{//будет засада + сам нападет
					pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
					pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
					pchar.quest.EscortTrader_Attack.function = "DesIslandAttack";
				}
			}
			pchar.quest.EscortTrader_Complete.win_condition.l1 = "location";
			pchar.quest.EscortTrader_Complete.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Location;
			pchar.quest.EscortTrader_Complete.function = "EscortTraderComplete";
			SetFunctionTimerCondition("EscortTrader_Over", 0, 0, sti(pchar.GenQuest.Escort.Trader.DaysQty), false);
			pchar.quest.EscortTrader_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.EscortTrader_fail.win_condition.l1.character = pchar.GenQuest.Escort.Trader.id;
			pchar.quest.EscortTrader_fail.function = "EscortTrader_failed";
		break;
		
		case "EscortTrader_complete"://сдаём квест
			sld = characterFromId(pchar.GenQuest.Escort.Trader.id);
			if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP)/4))//если корпуса осталось меньше 1/4 - первая проверка
			{
				dialog.text = "Kapitän, sag mir, warum habe ich dich angeheuert? Schau dir mein Schiff an! Wie sieht es aus? Es ist ruiniert! Es hält sich kaum über Wasser. Siehst du das nicht? Ich verstehe es nicht - wer hat wen begleitet? Wie dem auch sei, du wirst keine Belohnung bekommen, vergiss es.";
				link.l1 = "Wenn es mich nicht gäbe, würdest du die Krabben füttern, du dummer Kaufmann. Gut, es ist dein Glückstag, aber die Welt ist klein und ich werde dich eines Tages auf offener See treffen!";
				link.l1.go = "EscortTrader_complete_1";
				break;
			}
			if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP)/2))//если корпуса осталось меньше 1/2 - вторая проверка
			{
				pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.Money))/2;
				dialog.text = "Kapitän, sag mir, warum habe ich dich eingestellt? Schau dir mein Schiff an! Wie sieht es aus? Es ist ruiniert! Es hält sich kaum über Wasser.. Siehst du das nicht? Wie auch immer, ich werde dir nur die Hälfte deiner Belohnung zahlen. Rechne nicht damit, mehr zu bekommen!";
				link.l1 = "Hmm... Gut, ich stimme zu. Dein Schiff ist wirklich... ein bisschen beschädigt...";
				link.l1.go = "EscortTrader_complete_2";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2") && sti(pchar.GenQuest.Escort.Trader.Chance) == 1)//вместо денег - наводка
			{
				dialog.text = "Kapitän, Sie sehen... Ich habe kein Geld, um Sie für Ihre Arbeit zu bezahlen. Aber machen Sie sich bitte keine Sorgen, ich möchte Ihnen eine andere Art von Bezahlung anbieten, die viel größer ist als das, was ich Ihnen zuvor versprochen habe!";
				link.l1 = "Hmm... Eigentlich habe ich erwartet, jetzt Münzen zu bekommen. Aber ich bin ganz Ohr, wenn das der Fall ist.";
				link.l1.go = "EscortTrader_complete_4";
				break;
			}
			dialog.text = "Vielen Dank, Kapitän. Trotz aller Gefahren war es eine sichere Fahrt mit Ihnen. Hier, nehmen Sie Ihre Belohnung.";
			link.l1 = "Sie sind willkommen... Ich habe nur meine Pflicht getan.";
			link.l1.go = "EscortTrader_complete_3";
		break;
		
		case "EscortTrader_complete_1":
			dialog.text = "Lass den Versuch, mir Angst zu machen! Deine Kampffähigkeiten machen deine Drohungen lächerlich. Lebewohl!";
			link.l1 = "Verschwinde, solange du kannst, Profitmacher...";
			link.l1.go = "complete_exit";
			AddQuestRecord("TraderEscort", "4");
			AddComplexSeaExpToScill(20, 20, 20, 0, 20, 0, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 20);//везение
		break;
		
		case "EscortTrader_complete_2":
			dialog.text = "Ja, eine sehr weise Beobachtung... Hier, nimm deinen "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+" und Lebewohl.";
			link.l1 = "Auf Wiedersehen, "+npchar.name+".";
			link.l1.go = "complete_exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
			AddQuestRecord("TraderEscort", "5");
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddComplexSeaExpToScill(50, 50, 50, 0, 50, 0, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 40);//везение
		break;
		
		case "EscortTrader_complete_3":
			dialog.text = "Du hast großartige Arbeit geleistet! Nun, ich muss jetzt gehen. Auf Wiedersehen, Kapitän!";
			link.l1 = "Viel Glück, "+npchar.name+"!";
			link.l1.go = "complete_exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
			AddQuestRecord("TraderEscort", "6");
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddComplexSeaExpToScill(100, 100, 100, 50, 100, 100, 150);
			AddCharacterExpToSkill(pchar, "Leadership", 80);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 80);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "EscortTrader_complete_4":
			pchar.GenQuest.Escort.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man");
			GetEnemyTraderGoods();
			pchar.GenQuest.Escort.Trader.EnIsland = DesIsland();
			dialog.text = "Es gibt einen Händler - "+pchar.GenQuest.Escort.Trader.Enemyname+". Er besitzt und kommandiert eine Flöte. Mir wurde mitgeteilt, dass er in zwei Wochen auf der bewohnten Insel ankommen wird "+XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland)+", um seine Wasservorräte wieder aufzufüllen und mit den einheimischen Indianern zu handeln. Er wird viel zu tun haben. "+pchar.GenQuest.Escort.Trader.add+" an Bord. Ein erbärmlicher Kämpfer, du wirst keine Probleme haben, sein Schiff zu nehmen\nSo wirst du sowieso davon profitieren, Kapitän.";
			link.l1 = "Ist der Mensch dem Menschen ein Wolf?";
			link.l1.go = "EscortTrader_complete_5";
		break;
		
		case "EscortTrader_complete_5":
			dialog.text = "Entschuldigung?";
			link.l1 = "Sie 'verraten' Ihren Kollegen auf so einfache und ehrliche Weise... Aber ich kümmere mich wenig um Ihr Gewissen und danke Ihnen für diese Information. Viel Glück, Herr!";
			link.l1.go = "EscortTrader_complete_6";
		break;
		
		case "EscortTrader_complete_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.EscortTrader_fail.over = "yes";
			pchar.quest.EscortTrader_Over.over = "yes";//снять оба прерывания
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			RemoveCharacterCompanion(Pchar, npchar);
			AddQuestRecord("TraderEscort", "7");
			AddQuestUserData("TraderEscort", "sIsland", XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland));
			AddQuestUserData("TraderEscort", "sAdd", pchar.GenQuest.Escort.Trader.add);
			pchar.quest.EscortTrader_EnTrader.win_condition.l1 = "Timer";
			pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 12);
			pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 12);
			pchar.quest.EscortTrader_EnTrader.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 12);
			pchar.quest.EscortTrader_EnTrader.win_condition.l2 = "location";
			pchar.quest.EscortTrader_EnTrader.win_condition.l2.location = pchar.GenQuest.Escort.Trader.EnIsland;
			pchar.quest.EscortTrader_EnTrader.function = "Create_EnemyTraderFleut";
			SetFunctionTimerCondition("EscortTraderEnemy_Over", 0, 0, 16, false); // таймер
			AddComplexSeaExpToScill(100, 100, 100, 50, 100, 100, 150);
			AddCharacterExpToSkill(pchar, "Leadership", 80);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 80);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "complete_exit":
			DialogExit();
			CloseQuestHeader("TraderEscort");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.EscortTrader_fail.over = "yes";
			pchar.quest.EscortTrader_Over.over = "yes";//снять оба прерывания
			pchar.quest.EscortTrader_Attack.over = "yes"; // patch-8
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			RemoveCharacterCompanion(Pchar, npchar);
			DeleteAttribute(pchar, "GenQuest.Escort.Trader");
		break;
		
		case "Race_prepare":
			NextDiag.TempNode = "Race_begin";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;
		
		case "exit_sit":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		
		case "Race_begin"://гонки на гидропланах
			dialog.text = "Eh, lasst uns einen guten alten Rum trinken, Kapitän! Wie geht es Ihnen, wie läuft Ihr Handel?";
			link.l1 = "Ich bin eigentlich kein Händler. Aber mir geht es ganz gut.";
			link.l1.go = "Race_begin_1";
		break;
		
		case "Race_begin_1":
			dialog.text = "Und das ist das Wichtigste! Angesichts der Gefahren auf hoher See.";
			link.l1 = "Ja, du hast recht. Besonders für euch Händler gibt es viele Jäger nach eurer Ladung. Und ihr seid selten in der Lage, weder zu fliehen noch zurückzuschlagen. Eure Schiffe sind langsam und eure Kanonen sind klein, da ihr eure Gewinne an erster Stelle setzt. In Konvois mit vier oder fünf Schiffen zusammen zu segeln, das ist es, was euch rettet.";
			link.l1.go = "Race_begin_2";
		break;
		
		case "Race_begin_2":
			dialog.text = "Nun, wir sind nicht alle so, Freund. Ich segel immer alleine, ich brauche keinen Ballast. Ich kenne die Karibik perfekt und darf ich sagen, ich bin wirklich gut im Navigieren, Segeln und Befehligen meiner Männer. Ich kann jeden Piraten überholen.";
			link.l1 = "Wirklich? Das kann ich kaum glauben. Mit voll geladener Fracht? Auf dem Handelsschiff? Meinen Sie also, dass Sie einer Piratenbrigg, einem Logger oder einer schnellen Korvette entkommen können?";
			link.l1.go = "Race_begin_3";
		break;
		
		case "Race_begin_3":
			dialog.text = "Sieht so aus, als würdest du, Kumpel, daran zweifeln, dass mein Schiff schnell segeln kann? Gut. Ich biete dir eine Wette an.";
			link.l1 = "Welche Art von Wette?";
			link.l1.go = "Race_begin_4";
		break;
		
		case "Race_begin_4"://тут устанавливаем все параметры
			if (!CheckAttribute(pchar, "GenQuest.Racing")) pchar.GenQuest.Racing.Count = 0;
			pchar.GenQuest.Racing.Go.Nation = npchar.nation;
			pchar.GenQuest.Racing.Go.StartCity = GetCurrentTown();
			pchar.GenQuest.Racing.Go.City = FindFriendCityToMC(false);//целевой дружественный город
			pchar.GenQuest.Racing.Go.Island = GetIslandByCityName(pchar.GenQuest.Racing.Go.City);
			pchar.GenQuest.Racing.Go.DaysQty = makeint((GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Racing.Go.StartCity), GetArealByCityName(pchar.GenQuest.Racing.Go.City)))/1.3);//дни
			pchar.GenQuest.Racing.Go.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			if (sti(pchar.GenQuest.Racing.Go.DaysQty) < 1) pchar.GenQuest.Racing.Go.DaysQty = 1; // patch-8
			dialog.text = "Hör zu. Ich werde heute in See stechen um "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+". Und ich sage, dass ich da sein werde in "+FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty)+". Versuche mich zu überholen und komme zu "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+" früher. Die Zeit fängt jetzt an zu ticken. Willst du es riskieren? Oder ist es zu hart für dich?";
			link.l1 = "Für wen? Für mich? Sei nicht so lustig. Du wirst es in dieser Zeit schaffen? Lächerlich. Gut, ich nehme deine Wette an. Wie viel bist du bereit zu verlieren?";
			link.l1.go = "Race_begin_5";
			link.l2 = "Ich bin zu beschäftigt, um wegen einiger alberner Prahlerei ein Rennen zu beginnen.";
			link.l2.go = "Race_exit";
		break;
		
		case "Race_exit":
			dialog.text = "Hm... Hast du Angst zu verlieren? Wie auch immer. Aber urteile nicht so schnell über andere Leute, es gibt viele erfahrene Seefahrer unter den Händlern... weit erfahrener als du es bist.";
			link.l1 = "Gut, gut, belehre mich nicht Philosoph. Auf Wiedersehen...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Race_begin_5":
			dialog.text = "Es ist Ihre Wahl, Kapitän.";
			iTemp = 1;
			for (i=5; i>=1; i--)
			{
					sTemp = "l"+iTemp;
					link.(sTemp) = ""+FindRussianMoneyString(sti(10000*i))+"";
					link.(sTemp).go = "Racing_rate"+i;
					iTemp++;
			}
		break;
		
		case "Racing_rate5"://50 000
			if (hrand(9, "&RacRa") > 6)
			{
			dialog.text = "Gut. Ich stimme zu. Deine Münzen bitte. Hier ist mein Einsatz.";
			link.l1 = "Lass mich nur meine Geldbörse holen...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 50000;
			}
			else
			{
			dialog.text = "Was für ein sinnloses Angebot, Kapitän? Für so viel Geld kannst du eine Schoner kaufen und einen ganzen Monat lang Rum trinken. Biete eine vernünftige Summe an.";
			link.l1 = "Diese Summe scheint mir vernünftig genug, und ich werde meine Zeit nicht mit dir für weniger verschwenden. Wir sind keine Bettler, um auf ein paar Pesos zu wetten. Gut... wir haben geredet, genug jetzt. Wenn du Angst hast zu wetten, ist es deine Wahl... Prahlerei ist nicht billig.";
			link.l1.go = "Race_exit";
			link.l2 = "Wirklich? Gut. Lass mich nachdenken...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate4"://40 000
			if (hrand(9, "&RacRa") > 4)
			{
			dialog.text = "Gut. Ich stimme zu. Deine Münzen bitte. Hier ist mein Einsatz.";
			link.l1 = "Lass mich nur meine Geldbörse holen...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 40000;
			}
			else
			{
			dialog.text = "Was für ein sinnloses Angebot, Kapitän? Sie können für dieses Geld eine Bark kaufen und einen ganzen Monat lang Rum trinken. Bieten Sie eine vernünftige Summe an.";
			link.l1 = "Diese Summe scheint mir vernünftig genug, und ich werde meine Zeit nicht mit dir für weniger verschwenden. Wir sind keine Bettler, um für ein paar Pesos zu wetten. Gut... wir haben unser Gespräch gehabt, genug jetzt. Wenn du Angst hast zu wetten, ist es deine Wahl... Prahlerei ist nicht billig.";
			link.l1.go = "Race_exit";
			link.l2 = "Wirklich? Gut. Lass mich nachdenken...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate3"://30 000
			if (hrand(9, "&RacRa") > 2)
			{
			dialog.text = "Gut. Ich stimme zu. Deine Münzen bitte. Hier ist mein Einsatz.";
			link.l1 = "Lass mich nur meine Geldbörse holen...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 30000;
			}
			else
			{
			dialog.text = "Was für ein sinnloses Angebot, Kapitän? Für so viel Geld könntest du eine Schaluppe kaufen und einen ganzen Monat lang Rum trinken. Biete eine vernünftige Summe an.";
			link.l1 = "Diese Summe scheint mir vernünftig genug, und ich werde meine Zeit mit dir nicht für weniger verschwenden. Wir sind keine Bettler, die um ein paar Pesos wetten. Gut... wir haben geredet, jetzt reicht's. Wenn du Angst hast zu wetten, ist das deine Entscheidung... Prahlerei ist nicht billig.";
			link.l1.go = "Race_exit";
			link.l2 = "Wirklich? Fein. Lass mich nachdenken...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate2"://20 000
			if (hrand(9, "&RacRa") > 0)
			{
			dialog.text = "Gut. Ich stimme zu. Deine Münzen bitte. Hier ist mein Einsatz.";
			link.l1 = "Lass mich nur meine Geldbörse holen...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 20000;
			}
			else
			{
			dialog.text = "Was für ein sinnloses Angebot, Kapitän? Für so viel Geld kann man eine Schaluppe kaufen und einen ganzen Monat lang Rum trinken. Bieten Sie eine vernünftige Summe an.";
			link.l1 = "Diese Summe scheint mir angemessen genug, und ich werde meine Zeit nicht mit dir für weniger verschwenden. Wir sind keine Bettler, die um ein paar Pesos wetten. Gut... wir haben geredet, jetzt ist genug. Wenn du Angst hast zu wetten, ist das deine Wahl... Prahlerei ist nicht billig.";
			link.l1.go = "Race_exit";
			link.l2 = "Wirklich? Gut. Lass mich nachdenken...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate1"://10 000
			dialog.text = "Gut. Ich stimme zu. Eure Münzen bitte. Hier ist mein Einsatz.";
			link.l1 = "Lass mich nur meine Geldbörse holen...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 10000;
		break;
		
		case "Racing_rate":
			dialog.text = "Na und?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Racing.Go.Money))
			{
			link.l1 = "Hier!";
			link.l1.go = "Racing_Go";
			}
			else
			{
			link.l1 = "Hm... es sieht so aus, als hätte ich nicht so viel.";
			link.l1.go = "Racing_rate_nomoney";
			}
		break;
		
		case "Racing_rate_nomoney":
			if (sti(pchar.GenQuest.Racing.Go.Money) == 10000 || sti(pchar.Money) < 10000)
			{
			dialog.text = "Nun, du weißt, wir sind keine Bettler, die um ein paar Pesos wetten, oder hast du einfach nur Angst? Gut, zur Hölle mit dir. Aber urteile nicht so schnell über andere, unter den Händlern gibt es viele erfahrene Seemänner... viel erfahrener als du es bist.";
			link.l1 = "Schön, schön, belehre mich nicht, Philosoph. Auf Wiedersehen...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
			}
			else
			{
			dialog.text = "Also warum überprüfst du nicht dein Geldbeutel oder setzt einen kleineren Einsatz?";
			link.l1 = "Gut, ich werde versuchen zu erinnern, wie viel Münzen ich habe...";
			link.l1.go = "Race_begin_5";
			link.l2 = "Ich habe meine Meinung geändert.";
			link.l2.go = "Racing_exit";
			}
		break;
		
		case "Racing_exit":
			dialog.text = "Hast du deine Meinung geändert, hm? Hast du einfach nur Angst? Gut, zur Hölle mit dir. Aber urteile nicht so schnell über andere Leute, es gibt viele erfahrene Seeleute unter den Händlern... viel erfahrener als du.";
			link.l1 = "Gut, gut, belehre mich nicht Philosoph. Lebewohl...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Racing_Go":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Racing.Go.Money));
			dialog.text = "Dann haben wir eine Wette! Lassen wir einen Schankwirt Zeuge sein, wenn es Ihnen nichts ausmacht... und geben wir ihm unseren Einsatz. Der Gewinner wird zurückkehren und die gesamte Summe nehmen. Betrug ist unmöglich, da Klatsch und Tratsch sich sehr schnell über das Archipel verbreiten, so dass er wissen wird, wer der Gewinner ist.";
			link.l1 = "Ich stimme zu. Das scheint richtig zu sein.";
			link.l1.go = "Racing_Go_1";
		break;
		
		case "Racing_Go_1":
			dialog.text = "Nun, ich denke, es ist Zeit für uns, auf unsere Schiffe zu steigen und Segel zu setzen, die Zeit tickt. Ich weiß nicht, wie es dir geht, aber ich werde sofort in See stechen. Oh, und mein Schiff ist eine Flöte und ihr Name ist "+pchar.GenQuest.Racing.Go.ShipName+". Ich vermute, dass Sie sie im Hafen leicht erkennen werden, sobald Sie ankommen.";
			link.l1 = "Freu dich nicht zu früh. Wir sehen uns in der Taverne von "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City+"Gen")+"!";
			link.l1.go = "Racing_Go_2";
		break;
		
		case "Racing_Go_2":
			DialogExit();
			npchar.lifeday = 0;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.GenQuest.Racing.Go.StartCity + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "exit_sit", -1);
			//работает корректно только через клон :(
			sTemp = npchar.model;
			int iNation = sti(npchar.Nation);
			sld = GetCharacter(NPC_GenerateCharacter("RaceTrader", sTemp, "man", "man", sti(PChar.rank)+5, iNation, -1, true, "quest"));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.Dialog.Filename = "Quest\QuestTrader_dialog.c";
			pchar.quest.Racing_Timer.win_condition.l1 = "Timer";
			pchar.quest.Racing_Timer.win_condition.l1.date.hour  = sti(GetTime()+rand(6));
			pchar.quest.Racing_Timer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty));
			pchar.quest.Racing_Timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty));
			pchar.quest.Racing_Timer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty));
			pchar.quest.Racing_Timer.function = "TraderRaceInTargetCity";
			pchar.quest.Racing_Finish.win_condition.l1 = "location";
			pchar.quest.Racing_Finish.win_condition.l1.location = pchar.GenQuest.Racing.Go.City + "_town";
			pchar.quest.Racing_Finish.function = "MCRaceInTargetCity";
			SetFunctionTimerCondition("RacingTimeOver", 0, 0, sti(pchar.GenQuest.Racing.Go.DaysQty)+10, false);
			ReOpenQuestHeader("Racing");
			AddQuestRecord("Racing", "1");
			AddQuestUserData("Racing", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Gen"));
			AddQuestUserData("Racing", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City+"Gen"));
			AddQuestUserData("Racing", "sDay", FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty));
			AddQuestUserData("Racing", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Racing.Go.Money)));
		break;
		
		case "Racing_Finished":
			if (CheckAttribute(pchar, "GenQuest.Racing.Go.MCWin"))
			{
			dialog.text = "Heh! Ich bin tatsächlich überrascht... Gratulation, Kapitän! Sie sind wirklich schneller als ich. Man sagt, dass es für jede Kraft immer eine stärkere Kraft gibt, habe ich recht?";
			link.l1 = "Genau, Herr. Aber ich möchte Ihnen sagen, dass Sie für einen Kapitän des Handelsschiffs erstaunlich erfahren und geschickt sind. Nicht jeder Kaufmann kann auf einer Flöte so kurzfristig segeln.";
			link.l1.go = "Racing_Finished_1";
			}
			else
			{
			dialog.text = "Nun, bist du überrascht, Kapitän? Wie ich sagte, kenne ich das Meer perfekt und segel mein Schiff gut genug. Siehst du jetzt?";
			link.l1 = "Argh! Unglaublich! Auf einer Flöte... so weit und in so kurzer Zeit... Herzlichen Glückwunsch, Kapitän!";
			link.l1.go = "Racing_Finished_2";
			}
			//bDisableFastReload = false;
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload1_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload2_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "gate_back", false);
		break;
		
		case "Racing_Finished_1":
			dialog.text = "Nun, du bist der Gewinner. Jetzt musst du zurückkehren zu "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity)+" und nimm dein Geld vom Barkeeper. Du hast es sicherlich verdient!";
			link.l1 = "Auf dem Weg. Es war mir ein Vergnügen. Auf Wiedersehen!";
			link.l1.go = "Racing_end";
			pchar.GenQuest.Racing.Count = sti(pchar.GenQuest.Racing.Count)+1;
			//запустить регату
			if (!CheckAttribute(pchar, "questTemp.RegataGo") && sti(pchar.GenQuest.Racing.Count) == 3)
			{
				pchar.questTemp.RegataGo = "true";
				pchar.questTemp.Regata.CureerCity = FindFriendCityToMC(true);//город, в котором вестовой подойдет
				if (pchar.questTemp.Regata.CureerCity == "PortRoyal") pchar.questTemp.Regata.CureerCity = "SentJons";
				pchar.quest.Regata_Cureer.win_condition.l1 = "location";
				pchar.quest.Regata_Cureer.win_condition.l1.location = pchar.questTemp.Regata.CureerCity+"_town";
				pchar.quest.Regata_Cureer.function = "PrepareToRegata";
				log_testinfo(pchar.questTemp.Regata.CureerCity);
			}
			pchar.GenQuest.Racing.Go.Advantage = "true";
			npchar.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Sailing", 200);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 100);//харизма
			ChangeCharacterComplexReputation(pchar,"authority", 3);
			ChangeOfficersLoyality("good_all", 3);
		break;
		
		case "Racing_Finished_2":
			dialog.text = "Es gibt kein Geheimnis darin, nur Fähigkeit und Erfahrung. Und ich muss gehen zu "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Kto")+" um meinen Preis zu sammeln.";
			link.l1 = "Du hast es verdient. Auf Wiedersehen!";
			link.l1.go = "Racing_end";
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 20);//харизма
			ChangeCharacterComplexReputation(pchar,"authority", 1);
			AddQuestRecord("Racing", "5");
			CloseQuestHeader("Racing");
		break;
		
		case "Racing_end":
			DialogExit();
			NextDiag.currentNode = "Racing_end_repeat";
			pchar.quest.Racing_fail.over = "yes";
			Group_DeleteGroup("RacingTrader");
			sld = characterFromId("RaceTraderSkiper");
			sld.lifeday = 0;
		break;
		
		case "Racing_end_repeat":
			dialog.text = "Gibt es noch etwas, über das Sie sprechen möchten?";
			link.l1 = "Nein, es ist nichts.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Racing_end_repeat";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

float ShipFactorMC()//коэффициент от класса корабля ГГ
{
	float f;
	switch (sti(RealShips[sti(pchar.Ship.Type)].Class))
	{
		case 1: f = 1.0 break;
		case 2: f = 1.2 break;
		case 3: f = 1.5 break;
		case 4: f = 2.2 break;
		case 5: f = 3.0 break;
		case 6: f = 4.5 break;
		case 7: f = 5.5 break;
	}
	return f;
}

int TraderShipType(ref iShipCoef)//корабль торговца
{
	int iRank = sti(pchar.rank);
	int iShip;
	
	if(iRank < 5)
	{
		switch (rand(2))
		{
			case 0:
				iShip = SHIP_BARKENTINE;
				iShipCoef = 2;
			break;
			case 1:
				iShip = SHIP_LUGGER;
				iShipCoef = 3;
			break;
			case 2:
				iShip = SHIP_BARQUE;
				iShipCoef = 4;
			break;
		}
	}
	if(iRank >= 5 && iRank < 11)
	{
		switch (rand(2))
		{
			case 0:
				iShip = SHIP_BARKENTINE;
				iShipCoef = 2;
			break;
			case 1:
				iShip = SHIP_BARQUE;
				iShipCoef = 4;
			break;
			case 2:
				iShip = SHIP_SCHOONER;
				iShipCoef = 5;
			break;
		}
	}
	if(iRank >= 11 && iRank < 18)
	{
		switch (rand(3))
		{
			case 0:
				iShip = SHIP_SCHOONER;
				iShipCoef = 5;
			break;
			case 1:
				iShip = SHIP_FLEUT;
				iShipCoef = 6;
			break;
			case 2:
				iShip = SHIP_CARAVEL;
				iShipCoef = 7;
			break;
			case 3:
				iShip = SHIP_BRIGANTINE;
				iShipCoef = 8;
			break;
		}
	}
	if(iRank >= 18 && iRank < 25)
	{
		switch (rand(4))
		{
			case 0:
				iShip = SHIP_CARAVEL;
				iShipCoef = 7;
			break;
			case 1:
				iShip = SHIP_BRIGANTINE;
				iShipCoef = 8;
			break;
			case 2:
				iShip = SHIP_PINNACE;
				iShipCoef = 9;
			break;
			case 3:
				iShip = SHIP_GALEON_L;
				iShipCoef = 10;
			break;
			case 4:
				iShip = SHIP_EASTINDIAMAN;
				iShipCoef = 11;
			break;
		}
	}
	if(iRank > 25)
	{
		switch (rand(3))
		{
			case 0:
				iShip = SHIP_PINNACE;
				iShipCoef = 9;
			break;
			case 1:
				iShip = SHIP_GALEON_L;
				iShipCoef = 10;
			break;
			case 2:
				iShip = SHIP_EASTINDIAMAN;
				iShipCoef = 11;
			break;
			case 3:
				iShip = SHIP_NAVIO;
				iShipCoef = 12;
			break;
		}
	}
	return iShip;
}

void GetEnemyTraderGoods()//выберем товар
{
switch (rand(7))
	{
		case 0:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_EBONY;
			pchar.GenQuest.Escort.Trader.add = "ebony";
			break;
		case 1:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_MAHOGANY;
			pchar.GenQuest.Escort.Trader.add = "redwood";
			break;
		case 2:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_TOBACCO;
			pchar.GenQuest.Escort.Trader.add = "tobacco";
			break;
		case 3:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_COFFEE;
			pchar.GenQuest.Escort.Trader.add = "coffee";
			break;
		case 4:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_CINNAMON;
			pchar.GenQuest.Escort.Trader.add = "cinnamon";
			break;
		case 5:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_FOOD;
			pchar.GenQuest.Escort.Trader.add = "provision";
			break;
		case 6:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_WEAPON;
			pchar.GenQuest.Escort.Trader.add = "weapon";
			break;
		case 7:
			pchar.GenQuest.Escort.Trader.Goods = GOOD_CHOCOLATE;
			pchar.GenQuest.Escort.Trader.add = "cacao";
			break;
	}
}

bool CheckFreeSitFront(ref _npchar)
{
 	ref rCharacter;
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator")) return false;
	
	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
		{
            if (rCharacter.location.locator == _npchar.Default.ToLocator)
                return  false;
		}
    }
    return  true;
}
