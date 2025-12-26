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
				dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Benim adım "+GetFullName(NPChar)+", Ben bir kaptanım. Senin de kaptan olduğunu görüyorum. Bir içki içmek ister misin? Benden olsun.";
				link.l1 = "Neden olmasın? Güzel bir ortamda birkaç kadeh içmeye hayır demem.";
				link.l1.go = "Race_prepare";
				link.l2 = "Üzgünüm, ama acelem var. Bir dahaki sefere.";
				link.l2.go = "exit";
				npchar.quest.race = "true";
			}
			else
			{
			//конвой торгового судна
				if(!CheckAttribute(pchar, "GenQuest.Escort.Trader") && !CheckAttribute(npchar, "quest.race") && sti(Pchar.Ship.Type) != SHIP_NOTUSED && !CheckAttribute(npchar, "repeat_work") && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0 && GetCompanionQuantity(pchar) < 3)
				{
					dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Ben "+GetFullName(NPChar)+", bir tüccar. Sanırım siz bir kaptansınız. Birkaç bin peso kazanmak ister misiniz?";
					link.l1 = "Her zaman birkaç kuruş kazanmak isterim. Ne tür bir işten bahsediyoruz?";
					link.l1.go = "Escort_choice";
					link.l2 = "Peki, tüccar ne tür bir iş önerebilir, ha? Çürük gemisini mi koruyacağım? Ben çıkarcılara yardım etmem.";
					link.l2.go = "exit_distress";
					SaveCurrentNpcQuestDateParam(npchar, "repeat_work");
				}
				else
				{
					dialog.text = TimeGreeting()+", "+GetAddress_Form(NPChar)+"! Nasılsın? Bir şeye ihtiyacın var mı?";
					link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+" Hayır, istemiyorum. Sadece merhaba demek istedim. Keyifli vakit geçir!";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "exit_distress":
			DialogExit();
			NextDiag.CurrentNode = "Trader_distress";
		break;
		
		case "Trader_distress":
			dialog.text = "Kaptan, zaten konuşmuştuk, değil mi? 'Tüccarlara yardım etmem' dedin, peki şimdi benden ne istiyorsun?";
			link.l1 = "Evet, haklısın. Peki, o zaman burada kal, geniş kıçını sandalyeye yapıştır ve romunu iç. Benim gitmem lazım.";
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
					dialog.text = "Beni   oraya kadar   eşlik etmeni   rica ediyorum "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+" içinde "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+".   Sana   ödeme   yapacağım "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "Ve neden olmasın? Birlikte yelken açmak her zaman daha güvenlidir, bunu anlıyorum. Katılıyorum.";
					link.l1.go = "EscortType";
					link.l2 = "Sana yardım etmeyi isterdim, ama ben başka bir yöne gidiyorum.";
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
					dialog.text = "Beni   oraya   kadar   eşlik   etmeni   rica   ediyorum "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+",   çok   uzakta   olmayan "+XI_ConvertString("Colony"+pchar.GenQuest.Escort.Trader.City+"Gen")+" içinde "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". Sana ödeme yapacağım "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "Ve neden olmasın? Birlikte yelken açmak her zaman daha güvenlidir, bunu anlıyorum. Katılıyorum.";
					link.l1.go = "EscortType";
					link.l2 = "Sana yardımcı olmak isterdim, ama ben başka bir yöne gidiyorum.";
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
					dialog.text = "Beni   oraya   kadar   eşlik   etmeni   rica   edeceğim "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Shore+"Gen")+"   şu anda   "+XI_ConvertString(pchar.GenQuest.Escort.Trader.Island)+", in "+FindRussianDaysString(sti(pchar.GenQuest.Escort.Trader.DaysQty))+". Sana ödeme yapacağım "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+".";
					link.l1 = "Ve neden olmasın? Birlikte yelken açmak her zaman daha güvenlidir, bunu anlayabiliyorum. Katılıyorum. Ama orada dükkanlar ve ticaret noktaları olduğunu hiç duymadım.";
					link.l1.go = "EscortType";
					link.l2 = "Sana yardımcı olmak isterdim ama ben başka bir yöne gidiyorum.";
					link.l2.go = "Escort_exit";
				break;
			}
		break;
		
		case "Escort_exit":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Escort.Trader");
		break;
		
		case "Trader_wait":
			dialog.text = "Seyahate hazır mısınız, kaptan? Emirlerinizi bekliyorum.";
			link.l1 = "Evet, şimdi yelken açıyoruz. Limanda görüşürüz.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Trader_wait";
		break;
		
		case "EscortType":
			dialog.text = "Harika! Anlaşmaya vardığımıza sevindim. Umarım yolculuğumuz güvenli geçer.";
			link.l1 = "Ben de öyle. Artık yelken açma zamanı!";
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
				dialog.text = "Kaptan, söyle bana, seni neden tuttum? Şu gemime bak! Ne halde? Tamamen mahvolmuş! Zar zor suyun üstünde duruyor. Bunu görmüyor musun? Anlamıyorum – kim kimi koruyordu? Neyse, ödül falan yok, unut gitsin.";
				link.l1 = "Ben olmasaydım şimdi yengeçlere yem olurdun, aptal tüccar. Neyse, bugün şanslı günündesin, ama dünya küçük ve bir gün açık denizde tekrar karşılaşacağız!";
				link.l1.go = "EscortTrader_complete_1";
				break;
			}
			if (sti(sld.ship.HP) < makeint(sti(pchar.GenQuest.Escort.Trader.ShipMaxHP)/2))//если корпуса осталось меньше 1/2 - вторая проверка
			{
				pchar.GenQuest.Escort.Trader.Money = makeint(sti(pchar.GenQuest.Escort.Trader.Money))/2;
				dialog.text = "Kaptan, söyle bana, seni neden tuttum? Şu gemime bir bak! Ne halde görünüyor? Tamamen harap olmuş! Zar zor su üstünde duruyor... Bunu göremiyor musun? Her neyse, ödülünün ancak yarısını ödeyeceğim. Fazlasını bekleme!";
				link.l1 = "Hmm... Peki, kabul ediyorum. Gemin gerçekten de... biraz hasar görmüş...";
				link.l1.go = "EscortTrader_complete_2";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.Escort.Trader.Type2") && sti(pchar.GenQuest.Escort.Trader.Chance) == 1)//вместо денег - наводка
			{
				dialog.text = "Kaptan, bakın... Size işinizin karşılığında ödeyecek param yok. Ama lütfen endişelenmeyin, size daha önce vaat ettiğimden çok daha değerli başka bir ödeme teklif etmek istiyorum!";
				link.l1 = "Hmm... Aslında şu anda birkaç sikke bekliyordum. Ama durum buysa, seni dinliyorum.";
				link.l1.go = "EscortTrader_complete_4";
				break;
			}
			dialog.text = "Çok teşekkür ederim, kaptan. Tüm tehlikelere rağmen sizinle yolculuk etmek güvenliydi. Buyurun, ödülünüzü alın.";
			link.l1 = "Rica ederim... Sadece görevimi yapıyordum.";
			link.l1.go = "EscortTrader_complete_3";
		break;
		
		case "EscortTrader_complete_1":
			dialog.text = "Beni korkutmaya çalışma! Dövüş yeteneklerin tehditlerini gülünç kılıyor. Elveda!";
			link.l1 = "Defol git, hâlâ vaktin varken, paragöz...";
			link.l1.go = "complete_exit";
			AddQuestRecord("TraderEscort", "4");
			AddComplexSeaExpToScill(20, 20, 20, 0, 20, 0, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 20);//везение
		break;
		
		case "EscortTrader_complete_2":
			dialog.text = "Evet, çok akıllıca bir gözlem... Al bakalım, işte senin "+FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money))+" ve elveda.";
			link.l1 = "Görüşürüz, "+npchar.name+".";
			link.l1.go = "complete_exit";
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Escort.Trader.Money));
			AddQuestRecord("TraderEscort", "5");
			AddQuestUserData("TraderEscort", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Escort.Trader.Money)));
			AddComplexSeaExpToScill(50, 50, 50, 0, 50, 0, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 40);//везение
		break;
		
		case "EscortTrader_complete_3":
			dialog.text = "İyi iş çıkardın! Şimdi gitmem gerek. Hoşça kal, kaptan!";
			link.l1 = "İyi şanslar, "+npchar.name+"!";
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
			dialog.text = "Bir tüccar var - "+pchar.GenQuest.Escort.Trader.Enemyname+". Bir fluytun sahibi ve kaptanı. İki hafta içinde yerleşim olan adaya varacağını öğrendim "+XI_ConvertString(pchar.GenQuest.Escort.Trader.EnIsland)+",   su kaynaklarını yenilemek ve yerli halkla ticaret yapmak için. Onun çok fazla "+pchar.GenQuest.Escort.Trader.add+" gemide. Zavallı bir dövüşçü, gemisini ele geçirirken hiçbir zorluk yaşamazsın\nYani bundan yine de kârlı çıkacaksın, kaptan.";
			link.l1 = "Homo homini lupus est?";
			link.l1.go = "EscortTrader_complete_5";
		break;
		
		case "EscortTrader_complete_5":
			dialog.text = "Affedersiniz?";
			link.l1 = "Meslektaşını bu kadar kolay ve dürüstçe 'ele veriyorsun'... Ama vicdanın umurumda değil, bu bilgi için sana teşekkür ederim. İyi şanslar, bayım!";
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
			dialog.text = "Eh, hadi biraz eski güzel rom içelim, kaptan! Nasılsın, ticaretin nasıl gidiyor?";
			link.l1 = "Ben aslında bir tüccar değilim. Ama gayet iyi idare ediyorum.";
			link.l1.go = "Race_begin_1";
		break;
		
		case "Race_begin_1":
			dialog.text = "Ve bu en önemli şey! Açık denizdeki tehlikeleri düşününce.";
			link.l1 = "Evet, haklısınız. Özellikle de sizin gibi tüccarlar için, yükünüzün peşinde çok avcı var. Ve çoğu zaman ne kaçabiliyor ne de karşılık verebiliyorsunuz. Gemileriniz yavaş, toplarınız küçük, çünkü önce kârınızı düşünüyorsunuz. Dört beş gemilik konvoylar halinde seyretmek, sizi kurtaran da bu zaten.";
			link.l1.go = "Race_begin_2";
		break;
		
		case "Race_begin_2":
			dialog.text = "Pek çoğumuz öyle değiliz, dostum. Ben her zaman tek başıma seyrederim, fazladan yük taşımam. Karayip Denizi'ni çok iyi bilirim ve izin verirsen, seyir, denizcilik ve adamlarımı yönetme konusunda gerçekten yetenekliyim. Herhangi bir korsandan daha hızlı hareket edebilirim.";
			link.l1 = "Gerçekten mi? Buna inanmakta zorlanıyorum. Tam dolu bir kargo ile mi? Bir ticaret gemisinde mi? Yani bir korsan brigantinden, bir luggerdan ya da hızlı bir korvetten kaçabileceğini mi söylüyorsun?";
			link.l1.go = "Race_begin_3";
		break;
		
		case "Race_begin_3":
			dialog.text = "Görünüşe bakılırsa, dostum, gemimin hızlı gidebileceğinden şüphe ediyorsun? Peki. Sana bir iddia teklif ediyorum.";
			link.l1 = "Ne tür bir iddia?";
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
			dialog.text = "Dinle. Bugün yelken açıyorum "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+". Ve ben de orada olacağımı söylüyorum "+FindRussianDaysString(pchar.GenQuest.Racing.Go.DaysQty)+" . Beni geçmeye çalış ve oraya ulaş "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City)+" daha erken. Zaman şimdi işlemeye başlıyor. Risk almak ister misin? Yoksa bu sana fazla mı zor?";
			link.l1 = "Kimin için? Benim için mi? Komik olma. Gerçekten o sürede başarabileceğini mi sanıyorsun? Saçma. Peki, iddianı kabul ediyorum. Ne kadar kaybetmeye hazırsın?";
			link.l1.go = "Race_begin_5";
			link.l2 = "Saçma bir övünme yüzünden yarış başlatacak kadar boş vaktim yok.";
			link.l2.go = "Race_exit";
		break;
		
		case "Race_exit":
			dialog.text = "Hm... Kaybetmekten mi korkuyorsun? Neyse. Ama başkalarını hemen yargılama, tüccarların arasında da çok tecrübeli denizciler var... hem de senden çok daha tecrübeli.";
			link.l1 = "Peki, peki, bana vaaz verme, filozof. Hoşça kal...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Race_begin_5":
			dialog.text = "Karar senin, kaptan.";
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
			dialog.text = "Pekala. Kabul ediyorum. Paralarını ver, lütfen. İşte bahsim.";
			link.l1 = "Cüzdanımı almama izin ver...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 50000;
			}
			else
			{
			dialog.text = "Ne anlamsız bir teklif, kaptan. O kadar parayla bir şalopa alır, bir ay boyunca rom içersiniz. Makul bir miktar teklif edin.";
			link.l1 = "Bu miktar bana gayet makul görünüyor, ve daha azı için seninle vakit kaybetmeyeceğim. Birkaç peso için dilenecek hâlimiz yok. Peki... konuştuk, bu kadar yeter. Bahse girmekten korkuyorsan, bu senin tercihin... Övünmek ucuz değil.";
			link.l1.go = "Race_exit";
			link.l2 = "Gerçekten mi? Peki. Bir düşüneyim...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate4"://40 000
			if (hrand(9, "&RacRa") > 4)
			{
			dialog.text = "Pekala. Kabul ediyorum. Paralarını ver, lütfen. İşte benim bahsim.";
			link.l1 = "Cüzdanımı almama izin ver...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 40000;
			}
			else
			{
			dialog.text = "Ne anlamsız bir teklif, kaptan! O kadar parayla bir barque alıp bir ay boyunca rom içebilirdiniz. Makul bir miktar teklif edin.";
			link.l1 = "Bu miktar bana gayet makul görünüyor, daha azı için seninle vakit kaybetmeyeceğim. Birkaç peso için dilenecek halimiz yok. Peki... konuştuk, bu kadar yeter. Bahse girmekten korkuyorsan, bu senin tercihin... Övünmek ucuz değil.";
			link.l1.go = "Race_exit";
			link.l2 = "Gerçekten mi? Peki. Bir düşüneyim...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate3"://30 000
			if (hrand(9, "&RacRa") > 2)
			{
			dialog.text = "Peki. Kabul ediyorum. Paralarını ver, lütfen. İşte bahsim.";
			link.l1 = "Sadece cüzdanımı alayım...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 30000;
			}
			else
			{
			dialog.text = "Ne saçma bir teklif, kaptan. O parayla bir şalopa alır, bir ay boyunca rom içersiniz. Makul bir miktar önerin.";
			link.l1 = "Bu miktar bana gayet makul görünüyor, daha azı için seninle vakit kaybetmem. Birkaç peso için dilenecek hâlimiz yok. Peki... konuştuk, bu kadar yeter. Bahse girmekten korkuyorsan, bu senin seçimin... Övünmek ucuz bir şey değil.";
			link.l1.go = "Race_exit";
			link.l2 = "Gerçekten mi? Peki. Bir düşüneyim...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate2"://20 000
			if (hrand(9, "&RacRa") > 0)
			{
			dialog.text = "Pekala. Kabul ediyorum. Paralarını ver, işte benim bahsim.";
			link.l1 = "Cüzdanımı almama izin ver...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 20000;
			}
			else
			{
			dialog.text = "Ne saçma bir teklif, kaptan. O kadar parayla bir lugger alıp bir ay boyunca rom içebilirsin. Makul bir miktar öner.";
			link.l1 = "Bu miktar bana gayet makul görünüyor, ve daha azı için seninle vakit kaybetmeyeceğim. Biz birkaç peso için dilenecek insanlar değiliz. Peki... konuştuk, bu kadar yeter. Bahse girmekten korkuyorsan, bu senin seçimin... Övünmek ucuz değil.";
			link.l1.go = "Race_exit";
			link.l2 = "Gerçekten mi? Peki. Bir düşüneyim...";
			link.l2.go = "Race_begin_5";
			}
		break;
		
		case "Racing_rate1"://10 000
			dialog.text = "Pekâlâ. Kabul ediyorum. Paralarını ver, lütfen. İşte benim bahsim.";
			link.l1 = "Cüzdanımı almama izin ver...";
			link.l1.go = "Racing_rate";
			pchar.GenQuest.Racing.Go.Money = 10000;
		break;
		
		case "Racing_rate":
			dialog.text = "Ee?";
			if (sti(pchar.money) >= sti(pchar.GenQuest.Racing.Go.Money))
			{
			link.l1 = "Burada!";
			link.l1.go = "Racing_Go";
			}
			else
			{
			link.l1 = "Hm... galiba o kadarım yok.";
			link.l1.go = "Racing_rate_nomoney";
			}
		break;
		
		case "Racing_rate_nomoney":
			if (sti(pchar.GenQuest.Racing.Go.Money) == 10000 || sti(pchar.Money) < 10000)
			{
			dialog.text = "Well, you know we are not beggars to bet for a few pesos, or are you just scared? Fine, to hell with you. But don't be so quick to judge others; there are plenty of experienced sailors among merchants... much more experienced than you are.";
			link.l1 = "Peki, peki, bana vaaz verme, filozof. Hoşça kal...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
			}
			else
			{
			dialog.text = "O zaman neden keseni kontrol etmiyorsun ya da daha küçük bir bahis koymuyorsun?";
			link.l1 = "Pekala, ne kadar param olduğunu hatırlamaya çalışacağım...";
			link.l1.go = "Race_begin_5";
			link.l2 = "Fikrimi değiştirdim.";
			link.l2.go = "Racing_exit";
			}
		break;
		
		case "Racing_exit":
			dialog.text = "Fikrini değiştirdin, öyle mi? Yoksa sadece korktun mu? Peki, cehenneme kadar yolun var. Ama başkalarını hemen yargılama, tüccarların arasında çok tecrübeli denizciler var... hem de senden çok daha tecrübeli.";
			link.l1 = "Peki, peki, bana vaaz verme, filozof. Elveda...";
			link.l1.go = "exit_sit";
			DeleteAttribute(pchar, "GenQuest.Racing.Go");
			NextDiag.TempNode = "First time";
		break;
		
		case "Racing_Go":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Racing.Go.Money));
			dialog.text = "O halde iddiaya girdik! Eğer sakıncası yoksa, barmenin şahit olmasını sağlayalım... ve bahsi ona teslim edelim. Kazanan geri gelip tüm parayı alacak. Hile yapmak imkânsız, çünkü dedikodu Karayipler'de çok çabuk yayılır, bu yüzden kimin kazandığını o mutlaka öğrenecek.";
			link.l1 = "Katılıyorum. Öyle görünüyor.";
			link.l1.go = "Racing_Go_1";
		break;
		
		case "Racing_Go_1":
			dialog.text = "Pekala, sanırım artık gemilerimize binip yelken açma zamanı geldi, zaman daralıyor. Sen bilirsin ama ben hemen yola çıkacağım. Ha, bu arada gemim bir flüt ve adı da "+pchar.GenQuest.Racing.Go.ShipName+". Limana vardığınızda onu kolayca tanıyacağınızı sanıyorum.";
			link.l1 = "Daha kutlama yapma. Hanede görüşürüz "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.City+"Gen")+"!";
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
			dialog.text = "Heh! Aslında şaşırdım... Tebrikler, kaptan! Gerçekten benden hızlıymışsın. Derler ki, her gücün üstünde bir güç vardır, değil mi?";
			link.l1 = "Kesinlikle, efendim. Ama şunu söylemeliyim ki, bir ticaret gemisinin kaptanı için şaşırtıcı derecede deneyimli ve yeteneklisiniz. Her tüccar, bir flütü bu kadar kısa sürede böyle idare edemez.";
			link.l1.go = "Racing_Finished_1";
			}
			else
			{
			dialog.text = "Pek şaşırmadın mı, kaptan? Dediğim gibi, denizi çok iyi bilirim ve gemimi de gayet iyi kullanırım. Şimdi gördün mü?";
			link.l1 = "Vay canına! İnanılmaz! Bir şalopla... o kadar yolu, hem de bu kadar kısa sürede... Tebrikler, kaptan!";
			link.l1.go = "Racing_Finished_2";
			}
			//bDisableFastReload = false;
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload1_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "reload2_back", false);
			//LocatorReloadEnterDisable(pchar.GenQuest.Racing.Go.City + "_town", "gate_back", false);
		break;
		
		case "Racing_Finished_1":
			dialog.text = "Pekala, kazanan sensin. Şimdi, geri dönmen gerekiyor "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity)+" ve parasını barmenden al. Bunu kesinlikle hak ettin!";
			link.l1 = "Zaten yoldayım. Tanıştığımıza memnun oldum. Hoşça kal!";
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
			dialog.text = "Bunda bir sır yok, sadece yetenek ve tecrübe. Ve şimdi gitmem gerekiyor "+XI_ConvertString("Colony"+pchar.GenQuest.Racing.Go.StartCity+"Acc")+" ödülümü almak için.";
			link.l1 = "Bunu hak ettin. Hoşça kal!";
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
			dialog.text = "Başka konuşmak istediğin bir şey var mı?";
			link.l1 = "Hayır, bir şey değil.";
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
