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
				dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"！俺の名前は "+GetFullName(NPChar)+"、俺は船長だ。あんたも船長みたいだな。一杯どうだ？俺のおごりだぜ。";
				link.l1 = "なぜだ？いい仲間と一杯やるのも悪くねえだろう。";
				link.l1.go = "Race_prepare";
				link.l2 = "申し訳ないが、急いでいるんだ。次の機会にな。";
				link.l2.go = "exit";
				npchar.quest.race = "true";
			}
			else
			{
			//конвой торгового судна
				if(!CheckAttribute(pchar, "GenQuest.Escort.Trader") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && !CheckAttribute(npchar, "repeat_work") && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0 && GetCompanionQuantity(pchar) < 3)
				{
					dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"！俺は "+GetFullName(NPChar)+"、商人だ。あんたは船長だろう？何千ペソか稼いでみないか？";
					link.l1 = "俺はいつだって小銭を稼ぐのに乗り気だぜ。どんな仕事なんだ？";
					link.l1.go = "Escort_choice";
					link.l2 = "で、商人がどんな仕事を寄越すってんだ？あいつの腐った船を守れってか？俺は金儲け野郎なんざ助けねえよ。";
					link.l2.go = "exit_distress";
					SaveCurrentNpcQuestDateParam(npchar, "repeat_work");
				}
				else
				{
					dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"！調子はどうだ？何か用か？";
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+"。いや、ないよ。ただ挨拶したかっただけだ。滞在を楽しんでくれ！";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "exit_distress":
			DialogExit();
			NextDiag.CurrentNode = "Trader_distress";
		break;
		
		case "Trader_distress":
			dialog.text = "船長、もう話はしたよな？あんたは「成金どもは助けねえ」って言ったじゃねえか、それで今さら俺に何の用だ？";
			link.l1 = "ああ、その通りだ。まあいい、ここでそのデカい尻を椅子に乗せてラムでも飲んでろ。俺は行かなきゃならねえ。";
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
					dialog.text = "私をそこまで護衛してほしいんだが "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+" 内部で "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+"。支払おう "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "なぜいけねえんだ？一緒に航海したほうが安全なのはわかってるぜ。俺も同意だ。";
					link.l1.go = "EscortType";
					link.l2 = "助けてやりたいが、俺は別の方向に向かっているんだ。";
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
					dialog.text = "私をそこまで護衛してほしいんだが "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+"、のすぐ近くで "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+" 内部で "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+"。俺が払うぜ "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "なぜいけねえんだ？一緒に航海したほうが安全なのは分かってるぜ。俺も賛成だ。";
					link.l1.go = "EscortType";
					link.l2 = "助けてやりたいが、俺は別の方向へ向かっているんだ。";
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
					dialog.text = "私をそこまで護衛してほしいんだが "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+" 「がある」 "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Island)+"、で "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+"。支払おう "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "なぜいけねえんだ？一緒に航海した方がいつだって安全だ、それは分かるぜ。俺も同意だ。だが、 あそこに店や交易所があるなんて聞いたことがねえな。";
					link.l1.go = "EscortType";
					link.l2 = "助けてやりたいが、俺は別の方向へ向かっているんだ。";
					link.l2.go = "Escort_exit";
				break;
			}
		break;
		
		case "Escort_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Escort.Trader");
		break;
		
		case "Trader_wait":
			dialog.text = "出航の準備はできているか、船長？俺は命令を待っているぜ。";
			link.l1 = "ああ、これから出航するぜ。港で会おうな。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Trader_wait";
		break;
		
		case "EscortType":
			dialog.text = "素晴らしい！取引が成立して嬉しいぜ。俺たちの航海が無事であることを願うぜ。";
			link.l1 = "俺もだ。出航の時間だぜ！";
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
				dialog.text = "船長、教えてくれ、なぜお前を雇ったんだ？俺の船を見ろ！どんな有様だと思う？ボロボロじゃねえか！ やっとのことで沈まずに浮かんでるだけだ。わからねえのか？一体誰が誰を護衛してたんだ？\nとにかく、報酬なんてやらねえ、諦めろ。";
				link.l1 = "俺がいなけりゃ今ごろカニの餌だぞ、この間抜けな商人め。まあいい、今日は運が良かったな。でも世間は狭いからな、 いつか外海でまた会うぜ！";
				link.l1.go = "EscortTrader_complete_1";
				break;
			}
			if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP)/2))//если корпуса осталось меньше 1/2 - вторая проверка
			{
				pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.Money))/2;
				dialog.text = "船長、教えてくれ、なぜお前を雇ったんだ？俺の船を見ろ！どんな有様だ？ボロボロじゃねえか！今にも沈みそうだぞ……それが見えねえのか？とにかく、報酬は半分しか払わねえ。これ以上は期待するなよ！";
				link.l1 = "ふむ……まあ、いいだろう。お前の船は確かに……ちょっと傷んでるな……";
				link.l1.go = "EscortTrader_complete_2";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2") && sti(pchar.GenQuest.Escort.Trader.Chance) == 1)//вместо денег - наводка
			{
				dialog.text = "船長、実は……あなたにお支払いする金がないんだ。でも、心配しないでくれ、 前に約束した以上の価値がある別の報酬を用意しているんだ！";
				link.l1 = "ふむ……実は今すぐ金貨をもらえると思ってたんだが。だが、そういう話なら耳を傾けようじゃねえか。";
				link.l1.go = "EscortTrader_complete_4";
				break;
			}
			dialog.text = "本当にありがとうございます、船長。いろいろ危険はあったが、あなたと一緒なら無事に航海できました。さあ、 これがあなたへの報酬です。";
			link.l1 = "どういたしまして……俺は自分の仕事をしていただけだ。";
			link.l1.go = "EscortTrader_complete_3";
		break;
		
		case "EscortTrader_complete_1":
			dialog.text = "俺を脅かそうなんて思うなよ！お前の腕前じゃ脅しにもならねえぜ。じゃあな！";
			link.l1 = "今のうちに消え失せろ、成金野郎……";
			link.l1.go = "complete_exit";
			AddQuestRecord("TraderEscort", "4");
			AddComplexSeaExpToScill(20, 20, 20, 0, 20, 0, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 20);//везение
		break;
		
		case "EscortTrader_complete_2":
			dialog.text = "ああ、実に賢い指摘だ……さあ、これを受け取れ "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+" そして、さらばだ。";
			link.l1 = "じゃあな "+npchar.name+".";
			link.l1.go = "complete_exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
			AddQuestRecord("TraderEscort", "5");
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddComplexSeaExpToScill(50, 50, 50, 0, 50, 0, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 40);//везение
		break;
		
		case "EscortTrader_complete_3":
			dialog.text = "よくやったな！さて、俺はもう行かなくちゃ。じゃあな、船長！";
			link.l1 = "幸運を祈るぜ。 "+npchar.name+"!";
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
			dialog.text = "商人が一人いる―― "+pchar.GenQuest.Escort.Trader.Enemyname+"。彼はフリュート船の所有者であり船長だ。二週間後に有人島へ到着するという情報を得た\n "+XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland)+"、水の補給を回復し、現地のインディアンと交易するためだ。彼には多くの "+pchar.GenQuest.Escort.Trader.add+" 乗り込め。あいつは情けない戦士だから、船を奪うのに苦労はしねえだろう\nだから結局はお前の得になるぜ、船長。";
			link.l1 = "「人は人にとって狼か？」";
			link.l1.go = "EscortTrader_complete_5";
		break;
		
		case "EscortTrader_complete_5":
			dialog.text = "「なんだって？」";
			link.l1 = "こんなにあっさり正直に仲間を“売る”とはな……だが、お前の良心なんぞ俺にはどうでもいい。この情報には感謝するぜ。幸運を祈る、旦那！";
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
			dialog.text = "おう、船長、たまにはラムでも飲もうぜ！調子はどうだ、商売の方はうまくいってるか？";
			link.l1 = "俺は本当の商人じゃねえ。でも、うまくやってるぜ。";
			link.l1.go = "Race_begin_1";
		break;
		
		case "Race_begin_1":
			dialog.text = "それが一番大事なんだぜ！外洋の危険を考えりゃな。";
			link.l1 = "ああ、その通りだ。特にお前たち商人にとっては、積み荷を狙う狩人が山ほどいるからな。しかも、 お前たちは逃げることも反撃することもほとんどできねえ。船は遅いし、大砲も小さい。利益を最優先にしてるからだ。 四隻か五隻の船で護衛隊を組んで航海する――それだけが命綱ってわけだ。";
			link.l1.go = "Race_begin_2";
		break;
		
		case "Race_begin_2":
			dialog.text = "まあ、俺たち全員がそうってわけじゃねえよ、相棒。俺はいつも一人で航海してる、余計な重りなんざいらねえ。 カリブ海のことは完璧に知り尽くしてるし、言わせてもらえば、航海術も操船も部下の指揮も本当に得意なんだ。 どんな海賊よりも速く逃げ切れるぜ。";
			link.l1 = "本当か？信じがたいな。満載の積荷で？しかも商船で？つまり、お前は海賊のブリガンティンやラガー、 それに快速のコルベットから逃げ切れるってことか？";
			link.l1.go = "Race_begin_3";
		break;
		
		case "Race_begin_3":
			dialog.text = "どうやらお前、俺の船が速く航海できるか疑ってるみたいだな？いいだろう。賭けをしようじゃねえか。";
			link.l1 = "どんな賭けだ？";
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
			dialog.text = "聞け。俺は今日、出航して "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+"。そして俺は、そこに行くと言っておくぜ "+FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty)+"。俺を出し抜いて"+ XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+" もっと早くな。今から時間が動き出すぜ。やってみるか？それとも、お前にはきつすぎるか？";
			link.l1 = "誰のためだ？俺のためか？冗談じゃねえよ。その時間で本当にやれるつもりか？馬鹿げてるぜ。いいだろう、 賭けに乗ってやる。どれだけ負ける覚悟があるんだ？";
			link.l1.go = "Race_begin_5";
			link.l2 = "くだらない自慢話で競争を始めるほど暇じゃねえんだ。";
			link.l2.go = "Race_exit";
		break;
		
		case "Race_exit":
			dialog.text = "ふん……負けるのが怖いのか？まあいいさ。\nだがな、他人をそんなに早く判断するなよ。商人の中には経験豊富な船乗りがたくさんいるんだ……お前よりずっとな。";
			link.l1 = "わかった、わかった、説教はやめてくれよ、哲学者さん。じゃあな……";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Race_begin_5":
			dialog.text = "選ぶのはあんた次第だぜ、船長。";
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
			dialog.text = "よし、わかった。賛成だ。コインを出してくれ。これが俺の賭け金だ。";
			link.l1 = "「ちょっと財布を取ってくるからな…」";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 50000;
			}
			else
			{
			dialog.text = "なんて馬鹿げた申し出だ、船長。その金があればスクーナー船が買えるし、一ヶ月はラム酒を飲み明かせるぜ。 もっとまともな額を出しな。";
			link.l1 = "この金額なら俺には十分妥当だぜ。これより安くてお前に付き合う気はねえ。俺たちは物乞いじゃねえんだ、 数ペソで賭けるような真似はしねえよ。よし……話はもう済んだ、これで十分だろう。賭けるのが怖いなら、それはお前の勝手だ……大口叩くのはタダじゃねえぞ。";
			link.l1.go = "Race_exit";
			link.l2 = "本当か？まあいい。ちょっと考えさせてくれ……";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate4"://40 000
			if (hrand(9, "&RacRa") > 4)
			{
			dialog.text = "よし、わかった。賛成だ。金貨を出してくれ。これが俺の賭け金だ。";
			link.l1 = "「ちょっと財布を取ってくるから……」";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 40000;
			}
			else
			{
			dialog.text = "なんて馬鹿げた申し出だ、船長！その金があればバルク船が買えるし、ひと月はラム酒が飲めるぜ。 もっとまともな額を出しな。";
			link.l1 = "この金額なら俺には十分妥当だと思うぜ。これより安くてお前に付き合うほど暇じゃねえ。 俺たちは数ペソのために物乞いする乞食じゃねえんだ。よし……話はこれで十分だろう。賭けるのが怖いなら、それもお前の勝手さ……虚勢を張るのは安くねえぞ。";
			link.l1.go = "Race_exit";
			link.l2 = "本当か？まあいい。ちょっと考えさせてくれ……";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate3"://30 000
			if (hrand(9, "&RacRa") > 2)
			{
			dialog.text = "よし、わかった。賭けに乗るぜ。コインを出しな。これが俺の賭け金だ。";
			link.l1 = "「ちょっと財布を取ってくるから……」";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 30000;
			}
			else
			{
			dialog.text = "なんて馬鹿げた申し出だ、船長。その金があればスループ船が買えるし、一ヶ月はラム酒を飲み明かせるぜ。 もっとまともな額を出しな。";
			link.l1 = "この金額なら俺には十分妥当だぜ。これより少ない額でお前に付き合うつもりはねえ。 俺たちは数ペソのために物乞いする乞食じゃねえんだ。よし……話は済んだ、もう十分だろう。賭けるのが怖いなら、それはお前の勝手だ……大口叩くのもタダじゃねえんだぜ。";
			link.l1.go = "Race_exit";
			link.l2 = "本当か？まあいい。ちょっと考えさせてくれ……";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate2"://20 000
			if (hrand(9, "&RacRa") > 0)
			{
			dialog.text = "よし、わかった。賛成だ。コインを出してくれ。これが俺の賭け金だ。";
			link.l1 = "「ちょっと財布を取ってくるから……」";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 20000;
			}
			else
			{
			dialog.text = "なんて馬鹿げた申し出だ、船長。その金があればラガー船を買って、ひと月はラム酒を飲んで過ごせるぜ。 もっとまともな額を出しな。";
			link.l1 = "この金額なら俺には十分だぜ。これより少ない額でお前に付き合う気はねえ。俺たちは物乞いじゃねえんだ、 数ペソのために賭けるようなな。\nよし……話はこれで十分だろう。賭けるのが怖いなら、それはお前の勝手だ……大口叩くのはタダじゃねえぞ。";
			link.l1.go = "Race_exit";
			link.l2 = "本当か？まあいい。考えさせてくれ……";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate1"://10 000
			dialog.text = "よし、わかった。賭けに乗るぜ。コインを出しな。これが俺の賭け金だ。";
			link.l1 = "「ちょっと財布を取ってくるから……」";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 10000;
		break;
		
		case "Racing_rate":
			dialog.text = "それで？";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Racing.Go.Money))
			{
			link.l1 = "「ここだ！」";
			link.l1.go = "Racing_Go";
			}
			else
			{
			link.l1 = "ふむ……そんなに持っていないようだな。";
			link.l1.go = "Racing_rate_nomoney";
			}
		break;
		
		case "Racing_rate_nomoney":
			if (sti(pchar.GenQuest.Racing.Go.Money) == 10000 || sti(pchar.Money) < 10000)
			{
			dialog.text = "まあ、俺たちは数ペソ賭けるために物乞いしてるわけじゃねえんだぜ。それとも、びびってるのか？いいさ、 くたばっちまえよ。\nだがな、他人をそんなに早く見くびるなよ。商人の中には腕の立つ船乗りがたくさんいるんだ……お前よりずっと経験豊富な連中がな。";
			link.l1 = "わかった、わかった、説教はやめてくれよ、哲学者さん。じゃあな……";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
			}
			else
			{
			dialog.text = "じゃあ、自分の財布を確認するか、賭け金をもっと少なくしたらどうだ？";
			link.l1 = "よし、どれだけ金貨が残ってるか思い出してみるか……";
			link.l1.go = "Race_begin_5";
			link.l2 = "考えを変えた。";
			link.l2.go = "Racing_exit";
			}
		break;
		
		case "Racing_exit":
			dialog.text = "気が変わったのか？怖じ気づいたんじゃねえのか？まあ、勝手にしやがれ。だがな、他人を簡単に見くびるんじゃねえぞ、 商人の中には経験豊富な船乗りがたくさんいるんだ……お前よりずっとな。";
			link.l1 = "わかった、わかった、説教はやめてくれよ、哲学者さん。じゃあな……";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Racing_Go":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Racing.Go.Money));
			dialog.text = "じゃあ、賭けは成立だな！もし構わねえなら、証人として酒場の親父を呼ぼうぜ…それと、賭け金もあいつに預けよう。勝ったやつが戻ってきて、全部受け取るってわけだ。ズルはできねえぞ、 この諸島じゃ噂がすぐ広まるから、誰が勝者か親父にもすぐ分かるさ。\n";
			link.l1 = "同感だ。それで間違いないな。";
			link.l1.go = "Racing_Go_1";
		break;
		
		case "Racing_Go_1":
			dialog.text = "さて、そろそろ俺たちも船に乗って出航する時間だな、時間が迫ってるぜ。お前はどうか知らねえが、 俺はすぐにでも出航するつもりだ。ああ、それと俺の船はフリュートで、名前は\n "+pchar.GenQuest.Racing.Go.ShipName+"。港に着いたら、すぐに彼女を見分けられるだろう。";
			link.l1 = "まだ喜ぶのは早いぜ。酒場で会おうな\n "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City+"Gen")+"!";
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
			dialog.text = "へっ！実は驚いたぜ……おめでとう、船長！本当に俺より速いんだな。どんな力にも上には上がいるって言うが、そうだろ？";
			link.l1 = "まさにその通りだ、旦那。しかし正直に言わせてもらうが、貿易船の船長にしては驚くほど経験豊富で腕が立つな。 あんな短期間でフルートをあそこまで操れる商人なんて、そうはいないぜ。";
			link.l1.go = "Racing_Finished_1";
			}
			else
			{
			dialog.text = "おや、驚いたかい、船長？言っただろ、俺は海のことなら何でも知ってるし、自分の船もちゃんと操れるんだぜ。 これで分かっただろ？";
			link.l1 = "アルッ！信じられねえ！スループ船で…あんな遠くまで、それもこんな短時間で…おめでとう、船長！";
			link.l1.go = "Racing_Finished_2";
			}
			//bDisableFastReload = false;
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload1_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload2_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "gate_back", false);
		break;
		
		case "Racing_Finished_1":
			dialog.text = "さて、お前が勝者だ。さあ、今度は戻らなきゃならねえぞ\n "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity)+" 酒場の主人から金を受け取れ。お前は間違いなくそれに値する働きをしたぜ！";
			link.l1 = "もう行くぜ。楽しかった。じゃあな！";
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
			dialog.text = "それに秘密なんてない、ただ腕と経験だけさ。さて、俺は行かなくちゃならねえんだ "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Acc")+" 俺の報酬を受け取るためにな。";
			link.l1 = "お前が勝ち取ったんだ。じゃあな！";
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
			dialog.text = "他に話したいことはあるか？";
			link.l1 = "いや、なんでもねえよ。";
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
