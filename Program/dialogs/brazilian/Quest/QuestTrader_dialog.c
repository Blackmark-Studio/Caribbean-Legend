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
				dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Meu nome é "+GetFullName(NPChar)+", eu sou capitão. Vejo que você também é capitão. Aceita tomar um drink comigo? Eu pago.";
				link.l1 = "Por que não? Eu não me importaria de tomar uns drinks em boa companhia.";
				link.l1.go = "Race_prepare";
				link.l2 = "Desculpe, mas estou com pressa. Fica para a próxima.";
				link.l2.go = "exit";
				npchar.quest.race = "true";
			}
			else
			{
			//конвой торгового судна
				if(!CheckAttribute(pchar, "GenQuest.Escort.Trader") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && !CheckAttribute(npchar, "repeat_work") && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0 && GetCompanionQuantity(pchar) < 3)
				{
					dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Eu sou "+GetFullName(NPChar)+", um comerciante. Imagino que seja capitão. Que tal ganhar uns milhares de pesos?";
					link.l1 = "Sempre estou disposto a ganhar umas moedas. Que tipo de trabalho estamos falando?";
					link.l1.go = "Escort_choice";
					link.l2 = "E que tipo de trabalho esse mercador pode oferecer, hein? Proteger o navio podre dele? Eu não ajudo exploradores.";
					link.l2.go = "exit_distress";
					SaveCurrentNpcQuestDateParam(npchar, "repeat_work");
				}
				else
				{
					dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Como você está? Precisa de alguma coisa?";
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+". Não, não quero nada. Só queria cumprimentar você. Aproveite sua estadia!";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "exit_distress":
			DialogExit();
			NextDiag.CurrentNode = "Trader_distress";
		break;
		
		case "Trader_distress":
			dialog.text = "Capitão, nós já conversamos, não foi? Você 'não ajuda aproveitadores', então o que quer de mim agora?";
			link.l1 = "Sim, e você está certo. Tudo bem, fique aí sentado nessa sua bunda gorda e beba seu rum. Eu tenho que ir.";
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
					pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty) * 400 * ShipFactorMC() + iTemp * 700);//оплата от расстояния и классов кораблей ГГ и неписи
					pchar.GenQuest.Escort.Trader.Type1 = "true";//тип задания
					pchar.GenQuest.Escort.Trader.Chance = rand(1);
					pchar.GenQuest.Escort.Trader.Add = "to "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+"";
					dialog.text = "Gostaria de pedir que me acompanhe até "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+" dentro de "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". Eu vou te pagar "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "E por que não? Sempre é mais seguro navegar juntos, eu entendo isso. Concordo.";
					link.l1.go = "EscortType";
					link.l2 = "Eu ficaria feliz em ajudar, mas estou indo para outro lado.";
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
					pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.DaysQty) * 400 * ShipFactorMC() + iTemp * 700);//оплата
					pchar.GenQuest.Escort.Trader.Type2 = "true";//тип задания
					pchar.GenQuest.Escort.Trader.Chance = rand(2);
					pchar.GenQuest.Escort.Trader.Add = "to "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+", not far from "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+"";
					dialog.text = "Eu gostaria de pedir que você me acompanhasse até "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+", não muito longe de "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+" dentro "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". Eu vou te pagar "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "E por que não? Sempre é mais seguro navegar juntos, eu entendo isso. Concordo.";
					link.l1.go = "EscortType";
					link.l2 = "Eu ficaria feliz em ajudar, mas estou indo para outro lado.";
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
					dialog.text = "Gostaria de pedir que me acompanhe até "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+" que fica em "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Island)+", em "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". Eu vou te pagar "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "E por que não? Sempre é mais seguro navegar em grupo, eu entendo isso. Concordo. Mas nunca ouvi falar de lojas e postos de comércio por lá.";
					link.l1.go = "EscortType";
					link.l2 = "Eu adoraria ajudar, mas estou indo para outro lado.";
					link.l2.go = "Escort_exit";
				break;
			}
		break;
		
		case "Escort_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Escort.Trader");
		break;
		
		case "Trader_wait":
			dialog.text = "Está pronto para zarpar, capitão? Estou esperando suas ordens.";
			link.l1 = "Sim, vamos zarpar agora. Te vejo no porto.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Trader_wait";
		break;
		
		case "EscortType":
			dialog.text = "Excelente! Fico feliz que tenhamos feito um acordo. Espero que nossa jornada seja segura.";
			link.l1 = "Eu também. É hora de zarpar!";
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
			if (sti(pchar.GenQuest.Escort.Trader.Chance) == 1) TraderHunterOnMap(true);
				else TraderHunterOnMap(false);//запуск ДУ на глобалке
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2"))//в бухту
			{
				pchar.GenQuest.Escort.Trader.Location = pchar.GenQuest.Escort.Trader.Shore;
				if (sti(pchar.GenQuest.Escort.Trader.Chance) != 2) TraderHunterOnMap(false);
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
				if (sti(pchar.GenQuest.Escort.Trader.Chance) == 0) TraderHunterOnMap(false);
				if (sti(pchar.GenQuest.Escort.Trader.Chance) == 1) 
				{
					if(sti(RealShips[sti(pchar.Ship.Type)].Class) >= sti(RealShips[sti(pchar.GenQuest.Escort.Trader.ShipType)].Class) && sti(RealShips[sti(pchar.Ship.Type)].BaseType) != SHIP_GALEON_H && GetCompanionQuantity(pchar) < 3)//меряемся кораблями
					{//нападет сам
						pchar.quest.EscortTrader_Attack.win_condition.l1 = "location";
						pchar.quest.EscortTrader_Attack.win_condition.l1.location = pchar.GenQuest.Escort.Trader.Island;
						pchar.quest.EscortTrader_Attack.function = "DesIslandAttack";
					}
					else TraderHunterOnMap(true);
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
				dialog.text = "Capitão, me diga, por que eu te contratei? Olhe para o meu navio! O que você vê? Ela está arruinada! Mal consegue se manter flutuando. Não está vendo? Não entendo – quem estava escoltando quem? Enfim, você não vai receber recompensa, esqueça isso.";
				link.l1 = "Se não fosse por mim, você já estaria servindo de comida para os caranguejos, seu mercador idiota. Tudo bem, hoje é seu dia de sorte, mas o mundo é pequeno e um dia vou te encontrar em alto-mar!";
				link.l1.go = "EscortTrader_complete_1";
				break;
			}
			if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP)/2))//если корпуса осталось меньше 1/2 - вторая проверка
			{
				pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.Money))/2;
				dialog.text = "Capitão, me diga, por que eu te contratei? Olhe para o meu navio! O que você vê? Ela está arruinada! Mal consegue se manter flutuando... Não está vendo isso? De qualquer forma, vou te pagar só metade da recompensa. Não espere receber mais!";
				link.l1 = "Hmm... Tudo bem, eu concordo. Seu navio está mesmo... um pouco danificado...";
				link.l1.go = "EscortTrader_complete_2";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2") && sti(pchar.GenQuest.Escort.Trader.Chance) == 1)//вместо денег - наводка
			{
				dialog.text = "Capitão, veja... Eu não tenho o dinheiro para te pagar pelo seu trabalho. Mas, por favor, não se preocupe, quero te oferecer outro tipo de pagamento, que é muito melhor do que prometi antes!";
				link.l1 = "Hum... Na verdade, eu estava esperando receber umas moedas agora. Mas, se for esse o caso, estou ouvindo.";
				link.l1.go = "EscortTrader_complete_4";
				break;
			}
			dialog.text = "Muito obrigado, capitão. Foi seguro navegar com você, apesar de todos os perigos. Aqui, pegue sua recompensa.";
			link.l1 = "De nada... Eu só estava fazendo meu trabalho.";
			link.l1.go = "EscortTrader_complete_3";
		break;
		
		case "EscortTrader_complete_1":
			dialog.text = "Não tente me assustar! Suas habilidades de luta tornam suas ameaças patéticas. Adeus!";
			link.l1 = "Vaza enquanto ainda pode, aproveitador...";
			link.l1.go = "complete_exit";
			AddQuestRecord("TraderEscort", "4");
			AddComplexSeaExpToScill(20, 20, 20, 0, 20, 0, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 20);//везение
		break;
		
		case "EscortTrader_complete_2":
			dialog.text = "Sim, uma observação muito perspicaz... Aqui, pegue seu "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+" e adeus.";
			link.l1 = "Até mais, "+npchar.name+".";
			link.l1.go = "complete_exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
			AddQuestRecord("TraderEscort", "5");
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddComplexSeaExpToScill(50, 50, 50, 0, 50, 0, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 40);//везение
		break;
		
		case "EscortTrader_complete_3":
			dialog.text = "Você foi muito bem! Bem, preciso ir agora. Adeus, capitão!";
			link.l1 = "Boa sorte, "+npchar.name+"!";
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
			dialog.text = "Tem um mercador - "+pchar.GenQuest.Escort.Trader.Enemyname+". Ele é dono e comandante de um fluyt. Fiquei sabendo que em duas semanas ele vai chegar à ilha habitada "+XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland)+", para reabastecer sua água e negociar com os índios locais. Ele terá muito "+pchar.GenQuest.Escort.Trader.add+" a bordo. Um lutador patético, você não terá dificuldade em tomar o navio dele\nEntão você vai sair ganhando de qualquer jeito, capitão.";
			link.l1 = "Homo homini lupus est?";
			link.l1.go = "EscortTrader_complete_5";
		break;
		
		case "EscortTrader_complete_5":
			dialog.text = "Com licença?";
			link.l1 = "Você está 'entregando' seu colega de forma tão fácil e sincera... Mas pouco me importa sua consciência, e agradeço por essa informação. Boa sorte, senhor!";
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
			dialog.text = "Ei, vamos tomar um bom rum, capitão! Como você está, como vão os seus negócios?";
			link.l1 = "Na verdade, eu não sou um comerciante. Mas estou me virando bem.";
			link.l1.go = "Race_begin_1";
		break;
		
		case "Race_begin_1":
			dialog.text = "E isso é o mais importante! Ainda mais com os perigos do mar aberto.";
			link.l1 = "Sim, você está certo. Principalmente para vocês, mercadores, há muitos caçadores atrás da sua carga. E vocês quase nunca conseguem fugir ou revidar. Seus navios são lentos e seus canhões são pequenos, porque vocês colocam o lucro acima de tudo. Navegar em comboios de quatro ou cinco navios juntos, é isso que salva vocês.";
			link.l1.go = "Race_begin_2";
		break;
		
		case "Race_begin_2":
			dialog.text = "Bem, nem todos nós somos assim, amigo. Eu sempre navego sozinho, não preciso de peso morto. Conheço o Mar do Caribe como a palma da minha mão e, se me permite dizer, sou realmente habilidoso em navegação, vela e comando dos meus homens. Posso deixar qualquer pirata comendo poeira.";
			link.l1 = "Sério? Mal posso acreditar nisso. Com a carga cheia? Em um navio mercante? Então você quer dizer que consegue escapar de um brigantim pirata, uma escuna ou uma corveta veloz?";
			link.l1.go = "Race_begin_3";
		break;
		
		case "Race_begin_3":
			dialog.text = "Parece que você, camarada, está duvidando se meu navio consegue velejar rápido? Muito bem. Eu te proponho uma aposta.";
			link.l1 = "Que tipo de aposta?";
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
			dialog.text = "Escute. Hoje eu zarpo para "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+". E eu digo que estarei lá "+FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty)+". Tente me ultrapassar e chegue até "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+" mais cedo. O tempo começa a correr agora. Quer arriscar? Ou é difícil demais pra você?";
			link.l1 = "Para quem? Para mim? Não me faça rir. Você acha mesmo que vai conseguir nesse tempo? Ridículo. Tudo bem, aceito sua aposta. Quanto está disposto a perder?";
			link.l1.go = "Race_begin_5";
			link.l2 = "Estou ocupado demais para começar uma corrida por causa de uma provocação boba.";
			link.l2.go = "Race_exit";
		break;
		
		case "Race_exit":
			dialog.text = "Hm... Está com medo de perder? Tanto faz. Mas não julgue os outros tão rápido assim, há muitos comerciantes que já navegaram bastante... muito mais do que você.";
			link.l1 = "Tá bom, tá bom, não venha me dar sermão, filósofo. Adeus...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Race_begin_5":
			dialog.text = "É sua escolha, capitão.";
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
			dialog.text = "Certo. Eu concordo. Suas moedas, por favor. Aqui está minha aposta.";
			link.l1 = "Deixe-me só pegar minha bolsa...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 50000;
			}
			else
			{
			dialog.text = "Que oferta sem sentido, capitão. Com esse dinheiro, você poderia comprar uma escuna e beber rum por um mês inteiro. Faça uma proposta razoável.";
			link.l1 = "Essa quantia me parece razoável, e não vou perder meu tempo com você por menos. Não somos mendigos para apostar uns poucos pesos. Muito bem... já conversamos, isso basta por agora. Se tem medo de apostar, é escolha sua... Ficar se gabando não sai barato.";
			link.l1.go = "Race_exit";
			link.l2 = "Sério? Tá bom. Deixa eu pensar...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate4"://40 000
			if (hrand(9, "&RacRa") > 4)
			{
			dialog.text = "Certo. Eu concordo. Suas moedas, por favor. Aqui está minha aposta.";
			link.l1 = "Deixa eu pegar minha bolsa...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 40000;
			}
			else
			{
			dialog.text = "Que proposta sem sentido, capitão! Com esse dinheiro, você poderia comprar uma barca e beber rum por um mês inteiro. Faça uma oferta mais razoável.";
			link.l1 = "Essa quantia me parece razoável, e não vou perder meu tempo com você por menos. Não somos mendigos para apostar uns poucos pesos. Muito bem... já conversamos, isso basta. Se tem medo de apostar, é sua escolha... Ficar se gabando não sai barato.";
			link.l1.go = "Race_exit";
			link.l2 = "Sério? Tá bom. Deixa eu pensar...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate3"://30 000
			if (hrand(9, "&RacRa") > 2)
			{
			dialog.text = "Certo. Eu concordo. Suas moedas, por favor. Aqui está minha aposta.";
			link.l1 = "Deixe-me só pegar minha bolsa...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 30000;
			}
			else
			{
			dialog.text = "Que proposta sem sentido, capitão. Com esse dinheiro, você poderia comprar uma escuna e beber rum o mês inteiro. Faça uma oferta mais razoável.";
			link.l1 = "Essa quantia me parece razoável, e não vou perder meu tempo com você por menos. Não somos mendigos para apostar por alguns pesos. Muito bem... já conversamos, isso basta por agora. Se tem medo de apostar, é sua escolha... Ficar se gabando não sai barato.";
			link.l1.go = "Race_exit";
			link.l2 = "Sério? Tudo bem. Deixe-me pensar...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate2"://20 000
			if (hrand(9, "&RacRa") > 0)
			{
			dialog.text = "Certo. Eu concordo. Suas moedas, por favor. Aqui está minha aposta.";
			link.l1 = "Deixa eu pegar minha bolsa...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 20000;
			}
			else
			{
			dialog.text = "Que proposta sem sentido, capitão. Com esse dinheiro, você poderia comprar uma escuna e beber rum por um mês inteiro. Faça uma oferta mais razoável.";
			link.l1 = "Essa quantia me parece razoável, e não vou perder meu tempo com você por menos. Não somos mendigos para apostar uns poucos pesos. Muito bem... já conversamos, chega por agora. Se tem medo de apostar, é escolha sua... Ficar se gabando não sai barato.";
			link.l1.go = "Race_exit";
			link.l2 = "Sério? Tá bom. Deixa eu pensar...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate1"://10 000
			dialog.text = "Certo. Eu aceito. Suas moedas, por favor. Aqui está minha aposta.";
			link.l1 = "Deixe-me só pegar minha bolsa...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 10000;
		break;
		
		case "Racing_rate":
			dialog.text = "E aí?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Racing.Go.Money))
			{
			link.l1 = "Aqui!";
			link.l1.go = "Racing_Go";
			}
			else
			{
			link.l1 = "Hm... parece que não tenho tanto assim.";
			link.l1.go = "Racing_rate_nomoney";
			}
		break;
		
		case "Racing_rate_nomoney":
			if (sti(pchar.GenQuest.Racing.Go.Money) == 10000 || sti(pchar.Money) < 10000)
			{
			dialog.text = "Well, you know we are not beggars to bet for a few pesos, or are you just scared? Fine, to hell with you. But don't be so quick to judge others; there are plenty of experienced sailors among merchants... much more experienced than you are.";
			link.l1 = "Tá bom, tá bom, não venha me dar sermão, filósofo. Adeus...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
			}
			else
			{
			dialog.text = "Então por que você não confere sua bolsa ou aposta menos?";
			link.l1 = "Certo, vou tentar lembrar quanto dinheiro eu tenho...";
			link.l1.go = "Race_begin_5";
			link.l2 = "Mudei de ideia.";
			link.l2.go = "Racing_exit";
			}
		break;
		
		case "Racing_exit":
			dialog.text = "Mudou de ideia, hein? Não está só com medo? Tudo bem, vá pro inferno. Mas não seja tão rápido pra julgar os outros, tem muito mercador por aí que é marinheiro experiente... bem mais do que você.";
			link.l1 = "Tá bom, tá bom, não vem me dar sermão, filósofo. Adeus...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Racing_Go":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Racing.Go.Money));
			dialog.text = "Então temos uma aposta! Vamos chamar o barman para ser nossa testemunha, se você não se importar... e deixar as apostas com ele. O vencedor volta e leva tudo. Não tem como trapacear, porque as fofocas se espalham rápido pelo arquipélago, então ele vai saber quem ganhou.";
			link.l1 = "Concordo. Parece certo.";
			link.l1.go = "Racing_Go_1";
		break;
		
		case "Racing_Go_1":
			dialog.text = "Bem, acho que está na hora de embarcarmos em nossos navios e zarparmos, o tempo está passando. Não sei você, mas eu vou partir agora mesmo. Ah, e meu navio é um fluyt e o nome dela é "+pchar.GenQuest.Racing.Go.ShipName+". Suponho que você vai reconhecê-la facilmente no porto assim que chegar.";
			link.l1 = "Não comemore ainda. Te vejo na taverna em "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City+"Gen")+"!";
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
			dialog.text = "Heh! Na verdade, estou surpreso... Parabéns, capitão! Você realmente é mais rápido do que eu. Dizem que sempre existe uma força maior para qualquer força, não é mesmo?";
			link.l1 = "Exatamente, senhor. Mas devo dizer, você é surpreendentemente experiente e habilidoso para o capitão de um navio mercante. Nem todo comerciante consegue comandar uma flauta dessas tão bem em tão pouco tempo.";
			link.l1.go = "Racing_Finished_1";
			}
			else
			{
			dialog.text = "Bem, não está surpreso, capitão? Como eu disse, conheço o mar muito bem e sei conduzir meu navio como poucos. Viu só?";
			link.l1 = "Argh! Incrível! Num saveiro... tão longe e em tão pouco tempo... Parabéns, capitão!";
			link.l1.go = "Racing_Finished_2";
			}
			//bDisableFastReload = false;
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload1_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload2_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "gate_back", false);
		break;
		
		case "Racing_Finished_1":
			dialog.text = "Bem, você é o vencedor. Agora, você precisa voltar para "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity)+" e pegue seu dinheiro com o barman. Você com certeza merece!";
			link.l1 = "Já estou a caminho. Foi um prazer. Adeus!";
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
			dialog.text = "Não há segredo nisso, só habilidade e experiência. E eu preciso ir para "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Acc")+" para receber meu prêmio.";
			link.l1 = "Você merece isso. Adeus!";
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
			dialog.text = "Tem mais alguma coisa sobre a qual você queira falar?";
			link.l1 = "Não, não é nada.";
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
	if(iRank >= 25)
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
switch (rand(6))
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
