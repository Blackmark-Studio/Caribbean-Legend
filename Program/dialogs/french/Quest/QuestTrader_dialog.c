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
				dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Mon nom est "+GetFullName(NPChar)+", je suis capitaine. Je vois que vous êtes capitaine aussi. Voudriez-vous vous joindre à moi et prendre un verre ensemble ? C'est moi qui régale.";
				link.l1 = "Pourquoi pas ? Cela ne me dérangerait pas de boire quelques verres en bonne compagnie.";
				link.l1.go = "Race_prepare";
				link.l2 = "Je suis désolé, mais je suis pressé. La prochaine fois.";
				link.l2.go = "exit";
				npchar.quest.race = "true";
			}
			else
			{
			//конвой торгового судна
				if(!CheckAttribute(pchar, "GenQuest.Escort.Trader") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && !CheckAttribute(npchar, "repeat_work") && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0 && GetCompanionQuantity(pchar) < 3)
				{
					dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Je suis "+GetFullName(NPChar)+", un marchand. Je suppose que vous êtes capitaine. Que diriez-vous de gagner quelques milliers de pesos ?";
					link.l1 = "Je suis toujours avide de gagner quelques pièces. De quel genre de travail s'agit-il ?";
					link.l1.go = "Escort_choice";
					link.l2 = "Et quel genre de travail le marchand peut-il proposer, hein ? Proteger son navire pourri ? Je n'aide pas les profiteurs.";
					link.l2.go = "exit_distress";
					SaveCurrentNpcQuestDateParam(npchar, "repeat_work");
				}
				else
				{
					dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Comment ça va ? Besoin de quelque chose ?";
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". Non, je ne le fais pas. Je voulais juste dire bonjour. Profitez de votre séjour !";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "exit_distress":
			DialogExit();
			NextDiag.CurrentNode = "Trader_distress";
		break;
		
		case "Trader_distress":
			dialog.text = "Capitaine, nous avons déjà eu une discussion, n'est-ce pas ? Vous 'n'aidez pas les profiteurs', alors que voulez-vous de moi maintenant ?";
			link.l1 = "Oui, et tu as raison. Très bien, reste assis sur ton gros derrière ici et bois ton rhum. Je dois y aller.";
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
					dialog.text = "Je voudrais vous demander de m'escorter jusqu'à "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+" à l'intérieur "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". Je te paierai "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "Et pourquoi pas ? Il est toujours plus sûr de naviguer ensemble, je peux le comprendre. Je suis d'accord.";
					link.l1.go = "EscortType";
					link.l2 = "Je serais ravi d'aider, mais je me dirige dans une direction différente.";
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
					pchar.GenQuest.Escort.Trader.Money =   makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty) * 400 * ShipFactorMC() + iTemp * 700);//оплата
					pchar.GenQuest.Escort.Trader.Type2 = "true";//тип задания
					pchar.GenQuest.Escort.Trader.Chance = rand(2);
					pchar.GenQuest.Escort.Trader.Add = "to "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+", not far from "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+"";
					dialog.text = "Je voudrais vous demander de m'escorter jusqu'à "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+", pas loin de "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+" à l'intérieur "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". Je te paierai "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "Et pourquoi pas ? Il est toujours plus sûr de naviguer ensemble, je peux le comprendre. Je suis d'accord.";
					link.l1.go = "EscortType";
					link.l2 = "Je serais ravi d'aider, mais je vais dans une direction différente.";
					link.l2.go = "Escort_exit";
				break;
				case 2://необитайка
					pchar.GenQuest.Escort.Trader.Island = DesIsland();//целевой остров
					pchar.GenQuest.Escort.Trader.Shore = SelectQuestShoreLocationFromSea(pchar.GenQuest.Escort.Trader.Island);//и бухта на нём
					pchar.GenQuest.Escort.Trader.DaysQty = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.Escort.Trader.StartCity), pchar.GenQuest.Escort.Trader.Island)+5;//дни
					pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty)*400*ShipFactorMC()+sti(pchar.GenQuest.Escort.Trader.ShipType)*700);//оплата
					pchar.GenQuest.Escort.Trader.Type3 = "true";//тип задания
					pchar.GenQuest.Escort.Trader.Chance = rand(2);
					pchar.GenQuest.Escort.Trader.Add = "to "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+" of inhabitant island "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Island)+"";
					dialog.text = "Je voudrais vous demander de m'escorter jusqu'à "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+" qui est à "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Island)+", dans "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+"  Je vous paierai  "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "Et pourquoi pas? Il est toujours plus sûr de naviguer ensemble, je peux le comprendre. Je suis d'accord. Mais je n'ai jamais entendu parler de boutiques et de comptoirs là-bas.";
					link.l1.go = "EscortType";
					link.l2 = "Je serais ravi d'aider, mais je vais dans une autre direction.";
					link.l2.go = "Escort_exit";
				break;
			}
		break;
		
		case "Escort_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Escort.Trader");
		break;
		
		case "Trader_wait":
			dialog.text = "Es-tu prêt à appareiller, capitaine ? J'attends tes ordres.";
			link.l1 = "Oui, nous allons appareiller maintenant. A bientôt au port.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Trader_wait";
		break;
		
		case "EscortType":
			dialog.text = "Splendide ! Je suis ravi que nous ayons conclu un accord. J'espère que notre voyage sera sûr.";
			link.l1 = "Moi aussi. Il est temps de lever l'ancre !";
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
				dialog.text = "Capitaine, dis-moi pourquoi je t'ai engagé ? Regarde mon navire ! A quoi ressemble-t-il ? Il est ruiné ! Il se maintient à peine au-dessus de l'eau. Ne vois-tu pas cela ? Je ne comprends pas - qui escortait qui ? Quoi qu'il en soit, tu n'auras aucune récompense, oublie ça.";
				link.l1 = "Si ce n'était pas pour moi, tu nourrirais les crabes, imbécile de marchand. Bon, c'est ton jour de chance, mais le monde est petit et je te rencontrerai un jour en pleine mer !";
				link.l1.go = "EscortTrader_complete_1";
				break;
			}
			if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP)/2))//если корпуса осталось меньше 1/2 - вторая проверка
			{
				pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.Money))/2;
				dialog.text = "Capitaine, dis-moi pourquoi je t'ai engagé ? Regarde mon navire ! A quoi ressemble-t-elle ? Elle est en ruine ! Elle tient à peine au-dessus de l'eau... Ne vois-tu pas cela ? Quoi qu'il en soit, je ne te paierai que la moitié de ta récompense. Ne compte pas en obtenir plus !";
				link.l1 = "Hmm... Bon, je suis d'accord. Ton navire est vraiment... un peu endommagé...";
				link.l1.go = "EscortTrader_complete_2";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2") && sti(pchar.GenQuest.Escort.Trader.Chance) == 1)//вместо денег - наводка
			{
				dialog.text = "Capitaine, vous voyez... Je n'ai pas d'argent pour vous payer pour votre travail. Mais ne vous inquiétez pas, je souhaite vous offrir un autre type de paiement qui est bien plus grand que ce que je vous avais promis auparavant !";
				link.l1 = "Hmm... En fait, je m'attendais à recevoir des pièces dès maintenant. Mais je suis tout ouïe si c'est le cas.";
				link.l1.go = "EscortTrader_complete_4";
				break;
			}
			dialog.text = "Merci beaucoup, capitaine. Ce fut une navigation sûre avec vous malgré tous les dangers. Tenez, prenez votre récompense.";
			link.l1 = "Vous etes le bienvenu... J'ai juste fait mon travail.";
			link.l1.go = "EscortTrader_complete_3";
		break;
		
		case "EscortTrader_complete_1":
			dialog.text = "Ne cherche pas à m'effrayer ! Tes compétences de combat rendent tes menaces pathétiques. Adieu !";
			link.l1 = "Perds-toi tant que tu le peux, flibustier...";
			link.l1.go = "complete_exit";
			AddQuestRecord("TraderEscort", "4");
			AddComplexSeaExpToScill(20, 20, 20, 0, 20, 0, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 20);//везение
		break;
		
		case "EscortTrader_complete_2":
			dialog.text = "Oui, une observation très sage... Tenez, prenez votre "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+" et adieu.";
			link.l1 = "À bientôt, "+npchar.name+".";
			link.l1.go = "complete_exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
			AddQuestRecord("TraderEscort", "5");
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddComplexSeaExpToScill(50, 50, 50, 0, 50, 0, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 40);//везение
		break;
		
		case "EscortTrader_complete_3":
			dialog.text = "Tu as fait du bon boulot ! Eh bien, je dois y aller maintenant. Adieu, capitaine !";
			link.l1 = "Bonne chance, "+npchar.name+" !";
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
			dialog.text = "Il y a un marchand - "+pchar.GenQuest.Escort.Trader.Enemyname+". Il possede et commande une flute. On m'a informe que dans deux semaines il arrivera sur l'ile habitee "+XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland)+", afin de reconstituer ses réserves d'eau et de commercer avec les Indiens locaux. Il aura beaucoup de "+pchar.GenQuest.Escort.Trader.add+" à bord. Un combattant pathétique, vous ne rencontrerez aucun problème à prendre son navire\nVous en profiterez donc de toute façon, capitaine.";
			link.l1 = "L'homme est un loup pour l'homme ?";
			link.l1.go = "EscortTrader_complete_5";
		break;
		
		case "EscortTrader_complete_5":
			dialog.text = "Excusez-moi ?";
			link.l1 = "Vous 'trahissez' votre collègue d'une manière si simple et honnête... Mais je me soucie peu de votre conscience et je vous remercie pour cette information. Bonne chance, monsieur !";
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
			dialog.text = "Eh, buvons un bon vieux rhum, capitaine ! Comment ça va, comment va ton commerce ?";
			link.l1 = "Je ne suis pas vraiment un marchand. Mais je me débrouille bien.";
			link.l1.go = "Race_begin_1";
		break;
		
		case "Race_begin_1":
			dialog.text = "Et c'est le plus important ! Considérant les dangers en haute mer.";
			link.l1 = "Oui, tu as raison. Surtout pour vous, les marchands, il y a beaucoup de chasseurs pour votre cargaison. Et vous êtes rarement capables de fuir ou de riposter. Vos navires sont lents et vos canons sont petits, puisque vous privilégiez vos profits. Naviguer en convois avec quatre ou cinq navires ensemble, c'est ce qui vous sauve.";
			link.l1.go = "Race_begin_2";
		break;
		
		case "Race_begin_2":
			dialog.text = "Eh bien, nous ne sommes pas tous comme ça, ami. Je navigue toujours seul, je n'ai pas besoin de lest. Je connais parfaitement la mer des Caraïbes et puis-je dire, je suis vraiment bon en navigation, en navigation à voile et en commandement de mes hommes. Je suis capable de distancer n'importe quel pirate.";
			link.l1 = "Vraiment? J'ai du mal à le croire. Avec une cale pleine de marchandises? Sur le navire de commerce? Donc, tu veux dire que tu peux échapper à une brigantine pirate, un lougre, ou une corvette rapide?";
			link.l1.go = "Race_begin_3";
		break;
		
		case "Race_begin_3":
			dialog.text = "Il semble que toi, l'ami, tu doutes que mon navire puisse naviguer vite ? Très bien. Je te propose un pari.";
			link.l1 = "Quel genre de pari ?";
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
			dialog.text = "Ecoute. Je vais mettre les voiles aujourd'hui vers "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+". Et je dis que j'y serai dans "+FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty)+"Essaie de me distancer et d'atteindre "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+" plus tôt. Le temps commence à s'écouler maintenant. Voulez-vous prendre le risque? Ou est-ce trop difficile pour vous?";
			link.l1 = "Pour qui ? Pour moi ? Ne sois pas si drôle. Tu vas y arriver dans ce temps-là ? Ridicule. D'accord, j'accepte ton pari. Combien es-tu prêt à perdre ?";
			link.l1.go = "Race_begin_5";
			link.l2 = "Je suis trop occupé pour commencer une course à cause de quelques fanfaronnades stupides.";
			link.l2.go = "Race_exit";
		break;
		
		case "Race_exit":
			dialog.text = "Hm... As-tu peur de perdre ? Peu importe. Mais ne sois pas si prompt à juger les autres, il y a beaucoup de marins expérimentés parmi les marchands... bien plus expérimentés que toi.";
			link.l1 = "Très bien, très bien, ne me fais pas la morale, philosophe. Adieu...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Race_begin_5":
			dialog.text = "C'est votre choix, capitaine.";
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
			dialog.text = "Très bien. J'accepte. Vos pièces s'il vous plaît. Voici mon pari.";
			link.l1 = "Attends, que je prenne ma bourse...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 50000;
			}
			else
			{
			dialog.text = "Quelle offre insensée, capitaine ? Vous pouvez acheter une goelette pour cette somme et boire du rhum pendant tout un mois. Proposez une somme raisonnable.";
			link.l1 = "Cette somme me paraît assez raisonnable, et je ne vais pas perdre mon temps avec toi pour moins. Nous ne sommes pas des mendiants à parier pour quelques pesos. Bien... nous avons parlé, c'est suffisant maintenant. Si tu crains de parier, c'est ton choix... Se vanter n'est pas bon marché.";
			link.l1.go = "Race_exit";
			link.l2 = "Vraiment ? Très bien. Laisse-moi réfléchir...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate4"://40 000
			if (hrand(9, "&RacRa") > 4)
			{
			dialog.text = "D'accord. J'accepte. Vos pieces s'il vous plait. Voici mon pari.";
			link.l1 = " Laisse-moi juste prendre ma bourse...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 40000;
			}
			else
			{
			dialog.text = "Quelle offre insensée, capitaine ? Vous pouvez acheter une barque pour cette somme et boire du rhum pendant un mois entier. Proposez une somme raisonnable.";
			link.l1 = "Cette somme me paraît bien raisonnable, et je ne vais pas perdre mon temps avec toi pour moins. Nous ne sommes pas des mendiants à parier pour quelques pesos. Bon... nous avons eu notre discussion, c'en est assez maintenant. Si tu crains de parier, c'est ton choix... Se vanter n'est pas gratuit.";
			link.l1.go = "Race_exit";
			link.l2 = "Vraiment ? Très bien. Laisse-moi réfléchir...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate3"://30 000
			if (hrand(9, "&RacRa") > 2)
			{
			dialog.text = "D'accord. J'accepte. Vos pièces s'il vous plaît. Voici mon pari.";
			link.l1 = " Laisse-moi juste prendre ma bourse...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 30000;
			}
			else
			{
			dialog.text = "Quelle offre insensée, capitaine ? Vous pouvez acheter un sloop pour cette somme et boire du rhum pendant tout un mois. Proposez une somme raisonnable.";
			link.l1 = "Cette somme me semble suffisamment raisonnable, et je ne vais pas perdre mon temps avec toi pour moins. Nous ne sommes pas des mendiants à parier pour quelques pesos. Bien... nous avons eu notre discussion, c'est assez maintenant. Si tu crains de parier, c'est ton choix... Se vanter n'est pas donné.";
			link.l1.go = "Race_exit";
			link.l2 = "Vraiment ? Très bien. Laisse-moi réfléchir...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate2"://20 000
			if (hrand(9, "&RacRa") > 0)
			{
			dialog.text = "D'accord. Je suis d'accord. Vos pieces, s'il vous plait. Voici mon pari.";
			link.l1 = " Laisse-moi juste prendre ma bourse...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 20000;
			}
			else
			{
			dialog.text = "Quelle offre insensée, capitaine ? Vous pouvez acheter une chaloupe pour cette somme et boire du rhum pendant tout un mois. Offrez une somme raisonnable.";
			link.l1 = "Cette somme me semble suffisamment raisonnable, et je ne vais pas perdre mon temps avec toi pour moins. Nous ne sommes pas des mendiants pour parier pour quelques pesos. Bien... nous avons eu notre discussion, assez maintenant. Si tu crains de parier, c'est ton choix... Se vanter n'est pas gratuit.";
			link.l1.go = "Race_exit";
			link.l2 = "Vraiment ? Très bien. Laisse-moi réfléchir...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate1"://10 000
			dialog.text = "D'accord. J'accepte. Vos pièces s'il vous plaît. Voici mon pari.";
			link.l1 = " Laisse-moi juste prendre ma bourse... ";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 10000;
		break;
		
		case "Racing_rate":
			dialog.text = "Alors ?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Racing.Go.Money))
			{
			link.l1 = "Tiens !";
			link.l1.go = "Racing_Go";
			}
			else
			{
			link.l1 = "Hm... il semble que je n'en ai pas autant.";
			link.l1.go = "Racing_rate_nomoney";
			}
		break;
		
		case "Racing_rate_nomoney":
			if (sti(pchar.GenQuest.Racing.Go.Money) == 10000 || sti(pchar.Money) < 10000)
			{
			dialog.text = "Eh bien, tu sais que nous ne sommes pas des mendiants pour parier quelques pesos ou as-tu juste peur ? Très bien, au diable avec toi. Mais ne juge pas trop vite les autres, il y a beaucoup de marins expérimentés parmi les marchands... bien plus expérimentés que toi.";
			link.l1 = "D'accord, d'accord, ne me fais pas la morale, philosophe. Adieu...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
			}
			else
			{
			dialog.text = "Alors pourquoi ne vérifies-tu pas ta bourse ou ne fais-tu un enjeu moindre ?";
			link.l1 = "D'accord, je vais essayer de me souvenir combien de pieces j'ai...";
			link.l1.go = "Race_begin_5";
			link.l2 = "J'ai changé d'avis.";
			link.l2.go = "Racing_exit";
			}
		break;
		
		case "Racing_exit":
			dialog.text = "Tu as changé d'avis, hein ? Tu n'es qu'un trouillard, hein ? Très bien, va te faire foutre. Mais ne sois pas si prompt à juger les autres, il y a beaucoup de marins expérimentés parmi les marchands... bien plus expérimentés que toi.";
			link.l1 = "Très bien, très bien, ne me fais pas la leçon, philosophe. Adieu...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Racing_Go":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Racing.Go.Money));
			dialog.text = "Alors, nous avons un pari ! Faisons venir un barman pour en être témoin, si cela ne vous dérange pas... et remettons-lui nos enjeux. Le vainqueur reviendra et prendra la somme totale. Tricher est impossible puisque les rumeurs se répandent très vite sur l'archipel, donc il saura qui est le gagnant.";
			link.l1 = "D'accord. Cela semble correct.";
			link.l1.go = "Racing_Go_1";
		break;
		
		case "Racing_Go_1":
			dialog.text = "Eh bien, je suppose qu'il est temps pour nous de monter sur nos navires et de prendre la mer, le temps presse. Je ne sais pas pour vous, mais je vais appareiller immédiatement. Oh, et mon navire est une flute et son nom est "+pchar.GenQuest.Racing.Go.ShipName+"  Je suppose que vous la reconnaitrez facilement au port une fois arrivé.  ";
			link.l1 = "N' saute pas de joie si tôt. On se voit à la taverne de "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City+"Gen")+"!";
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
			dialog.text = "Hein! Je suis surpris en fait... Félicitations, capitaine! Vous êtes vraiment plus rapide que moi. Ils disent qu'il y a toujours une force plus forte pour n'importe quelle force, ai-je raison?";
			link.l1 = "Exactement, monsieur. Mais je veux vous dire que vous êtes étonnamment expérimenté et habile pour un capitaine de navire marchand. Tous les marchands ne sont pas capables de naviguer de cette façon sur une flute en si peu de temps.";
			link.l1.go = "Racing_Finished_1";
			}
			else
			{
			dialog.text = "Eh bien, n'êtes-vous pas surpris, capitaine ? Comme je l'ai dit, je connais parfaitement la mer et je navigue sur mon navire suffisamment bien. Vous voyez maintenant ?";
			link.l1 = "Argh ! Incroyable ! Sur une flute... aussi loin et en si peu de temps... Félicitations, capitaine !";
			link.l1.go = "Racing_Finished_2";
			}
			//bDisableFastReload = false;
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload1_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload2_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "gate_back", false);
		break;
		
		case "Racing_Finished_1":
			dialog.text = "Eh bien, vous êtes le vainqueur. Maintenant, vous devez retourner à "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity)+" et prends ton argent au barman. Tu l'as bien mérité !";
			link.l1 = "Je suis déjà en route. Ce fut un plaisir. Adieu !";
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
			dialog.text = "Il n'y a pas de secret là-dedans, juste de l'habileté et de l'expérience. Et je dois y aller "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Accord")+" pour obtenir ma récompense.";
			link.l1 = "Tu l'as mérité. Adieu !";
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
			dialog.text = "Y a-t-il autre chose dont tu veux parler ?";
			link.l1 = "Non, ce n'est rien.";
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
