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
			dialog.text = "发现一个漏洞, 请务必告知开发者。 ";
			link.l1 = "好的。 ";
			link.l1.go = "exit";
		break;
		
		//甲板上的对话
		case "MarchCap":
			pchar.quest.MarchCapOver.over = "yes"; //移除中断
			dialog.text = "您来了, 船长。 我们来讨论一下我提议的细节。 您会明白为什么我不想在公开场合谈论这个。 ";
			link.l1 = "请说, 先生。 我在听。 ";
			link.l1.go = "MarchCap_1";
		break;
		
		case "MarchCap_1":
			pchar.GenQuest.MarchCap.Goods = SelectMarchCapGoods1();//目标货物
			switch (rand(2))
			{
				case 0: //岛屿附近的 convoy, 设置参数
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
					dialog.text = "我发现"+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+"后, 一支挂着"+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+"旗帜的小型贸易护航队 —两艘商船和一艘护卫船, 将在"+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen")+"附近航行, 离"+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen")+"不远。 商人的货舱里有很多"+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+"。 船长, 不利用这个信息就太愚蠢了\n您和我可以轻松解决护卫队, 把货物据为己有。 那么, 您加入吗? ";
					link.l1 = "听起来很诱人。 我同意! ";
					link.l1.go = "MarchCap_1_1";
					link.l2 = "一些"+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+"不足以让我破坏与"+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+"的关系。 不, 我不打算这么做! 再会, 先生, 别试图阻止我! ";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 1: //全局地图上的遭遇, 设置参数
					pchar.GenQuest.MarchCap.Startcity = SelectAnyColony(pchar.GenQuest.MarchCap.basecity);
					pchar.GenQuest.MarchCap.Finishcity = SelectAnyColony2(pchar.GenQuest.MarchCap.basecity, pchar.GenQuest.MarchCap.Startcity);
					pchar.GenQuest.MarchCap.DaysQty = 5+hrand(5);
					dialog.text = "我发现"+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+"后, 一支挂着"+NationNameGenitive(sti(pchar.GenQuest.MarchCap.Nation))+"旗帜的小型贸易护航队 —两艘商船和一艘护卫船, 将从"+XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Startcity+"Gen")+"航行到"+XI_ConvertString("Colony"+pchar.GenQuest.MarchCap.Finishcity+"Acc")+"。 商人的货舱里有很多"+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+"。 船长, 不利用这个信息就太愚蠢了\n您和我可以轻松解决护卫队, 把货物据为己有。 最难的部分是在这两个殖民地之间的公海上找到他们。 那么, 您加入吗? ";
					link.l1 = "听起来很诱人。 我同意! ";
					link.l1.go = "MarchCap_2_1";
					link.l2 = "一些"+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+"不足以让我破坏与"+NationNameAblative(sti(pchar.GenQuest.MarchCap.Nation))+"的关系。 不, 我不打算这么做! 再会, 先生, 别试图阻止我! ";
					link.l2.go = "MarchCap_exit";
				break;
				
				case 2: //海湾附近的单个海盗独桅帆船, 设置参数
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
					pchar.GenQuest.MarchCap.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);//海盗
					pchar.GenQuest.MarchCap.ShipType = SelectPirateShipType();
					pchar.GenQuest.MarchCap.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.MarchCap.ShipType));
					dialog.text = "我得到消息, 有个叫"+GetName( NAMETYPE_ORIG, pchar.GenQuest.MarchCap.PirateName, NAME_NOM)+"的海盗。 这个强盗最近劫持了"+RandPhraseSimple(RandPhraseSimple("英国","法国"), RandPhraseSimple("西班牙","荷兰"))+"的船只, 货舱里装满了"+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+"。 但遗憾的是, 他的"+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.ShipType), "Name")+"Acc"))+"号船严重受损, 不得不花时间修理\n他目前在"+XI_ConvertString(pchar.GenQuest.MarchCap.Island.Shore+"Gen")+"的"+XI_ConvertString(pchar.GenQuest.MarchCap.Island+"Gen")+"。 我想他需要大约"+FindRussianDaysString(sti(pchar.GenQuest.MarchCap.DaysQty))+"来修理桅杆和船体的破洞。 如果我们抓紧时间, 就能及时赶到, 所有"+GetGoodsNameAlt(sti(pchar.GenQuest.MarchCap.Goods))+"都将归我们所有\n我自己对付不了这个海盗, 他是个非常优秀的水手和战士, 但我们两人可以成功面对他, 不管他多有经验。 那么, 您加入吗? ";
					link.l1 = "听起来很诱人。 我同意! ";
					link.l1.go = "MarchCap_3_1";
					link.l2 = "嗯。 看来这个奖品不仅您够不着, 我们俩也够不着。 不, 我不打算这么做, 再会, 先生, 别试图阻止我! ";
					link.l2.go = "MarchCap_exit";
				break;
			}
		break;
		
		case "MarchCap_1_1":
			dialog.text = "我就知道可以指望您! 我们不要浪费一分钟。 去您的船, 带头出发, 我会跟上。 是时候起航了! ";
			link.l1 = "下令起锚, 船长! ";
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
			npchar.Tasks.CanBoarding = false; // 禁止进行登船攻击 // Addon 2016-1 Jason 海盗舰队
			pchar.quest.MarchCap1_1.win_condition.l1 = "Timer";
			pchar.quest.MarchCap1_1.win_condition.l1.date.hour  = sti(GetTime()+rand(10));
			pchar.quest.MarchCap1_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, sti(pchar.GenQuest.MarchCap.DaysQty));
			pchar.quest.MarchCap1_1.win_condition.l2 = "location";
			pchar.quest.MarchCap1_1.win_condition.l2.location = pchar.GenQuest.MarchCap.Island;
			pchar.quest.MarchCap1_1.function = "MarchCap1_CreateConvoy";
			SetFunctionTimerCondition("MarchCap_Attack_Over", 0, 0, sti(pchar.GenQuest.MarchCap.DaysQty)+2, false); //寻找计时器
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
			dialog.text = "我为什么要和您一起干, 船长? 因为您, 我们失去了如此宝贵的奖品! 下次我最好独自航行... ";
			link.l1 = "是您的错, 不是我的。 再见。 ";
			link.l1.go = "MarchCap_Talk_exit";
			pchar.GenQuest.MarchCap = "late";
		break;
		
		case "MarchCap_Talk_exit":
			pchar.quest.MarchCap1_fail2.over = "yes"; //移除中断
			pchar.quest.MarchCap1_fail1.over = "yes"; //移除中断
			pchar.quest.MarchCap1_fail.over = "yes"; //移除中断
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
				dialog.text = "您真是个失败者, 船长! 我们一块都没拿到! 这都是因为您! 您是我们失败的原因, 该死的! ";
				link.l1 = "是吗? 看看您自己! 您在战斗中根本没帮我! 我只是跟您浪费时间... 从我的船上滚出去! ";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 50 && iTemp < 500)
			{
				dialog.text = "好吧, 这次突袭不如我预期的成功, 我们的奖品真的很少... 不管怎样, 船长, 我们分了这些残羹剩饭, 然后告别吧。 ";
				link.l1 = "如果您不是在数天上的鸟, 而是帮我, 突袭本会成功... 拿走您的份额 - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+", 然后消失! ";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 500 && iTemp < 1500)
			{
				dialog.text = "干得好, 船长! 正如我所说 - 清空那些商人的货舱相当容易, 哈哈... 奖品是"+FindRussianQtyString(iQty)+"件。 我的份额是"+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+"。 ";
				link.l1 = "没错, "+npchar.name+"。 我没有异议。 长艇正在装货。 也许我们将来会再次一起突袭? 您看起来适合做我的同伴。 ";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "太棒了, 船长! 正如我所说 - 清空那些商人的货舱相对容易, 哈哈... 奖品非常丰厚, 比我预期的多得多。 有"+FindRussianQtyString(iQty)+"件。 我的份额是"+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+"。 ";
			link.l1 = "没错, "+npchar.name+"。 我没有异议。 长艇正在装货。 也许我们将来会再次一起突袭? 您看起来适合做我的同伴。 ";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		//如果有时间 - 这里创建另一个具有唯一ID的克隆来继续任务
		case "MarchCap_Deck_continue":
			dialog.text = "有可能, 船长。 如果我有另一个自己无法完成的有利线索, 我会找到您。 您看起来也是我可靠的战斗伙伴。 ";
			link.l1 = "太好了! 再会, 船长。 祝您好运! ";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_2_1":
			dialog.text = "我就知道可以指望您! 我们不要浪费一分钟。 去您的船, 带头出发, 我会跟上。 是时候起航了! ";
			link.l1 = "下令起锚, 船长。 ";
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
			npchar.Tasks.CanBoarding = false; // 禁止进行登船攻击 // Addon 2016-1 Jason 海盗舰队
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
			dialog.text = "我就知道可以指望您! 我们不要浪费一分钟。 去您的船, 带领我。 是时候起航了! ";
			link.l1 = "下令起锚, 船长。 ";
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
			npchar.Tasks.CanBoarding = false; // 禁止进行登船攻击 // Addon 2016-1 Jason 海盗舰队
			pchar.quest.MarchCap1_1.win_condition.l1 = "location";
			pchar.quest.MarchCap1_1.win_condition.l1.location = pchar.GenQuest.MarchCap.Island;
			pchar.quest.MarchCap1_1.function = "MarchCap3_CreatePirate";
			SetFunctionTimerCondition("MarchCap_Attack_Over", 0, 0, sti(pchar.GenQuest.MarchCap.DaysQty), false); //计时器
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
			dialog.text = "您是个懦夫, 该死的! 您刚刚从战场上逃跑了! ";
			link.l1 = "您认为我该怎么做? 让那个海盗击沉我的船? 没门, 我宁愿做个活着的懦夫, 也不做死了的白痴! ";
			link.l1.go = "MarchCap_DieHard_1";
		break;
		
		case "MarchCap_DieHard_1":
			dialog.text = "我为什么要和您一起干, 船长? 我应该找一个不怕登船军刀的人! ";
			link.l1 = "现在, 请您离开我的船 - 我需要修理它。 ";
			link.l1.go = "MarchCap_Talk_exit";
		break;
		
		case "MarchCap_AfterBattleGold":
			iTemp = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty))*sti(Goods[sti(pchar.GenQuest.MarchCap.Goods)].Weight);
			iQty = makeint(GetSquadronGoods(pchar, sti(pchar.GenQuest.MarchCap.Goods))-sti(pchar.GenQuest.MarchCap.StartGoodsQty));
			pchar.GenQuest.MarchCap.CapPart = iQty/sti(pchar.GenQuest.MarchCap.Parts);
			if (iTemp < 10)
			{
				dialog.text = "您真是个失败者, 船长! 我们一块奖品都没拿到! 这都是因为您! 您是我们失败的原因, 该死的! ";
				link.l1 = "是吗? 看看您自己! 您在战斗中根本没帮我! 我只是跟您浪费时间... 从我的船上滚出去! ";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "bad";
				break;
			}
			if (iTemp > 10 && iTemp < 100)
			{
				dialog.text = "好吧, 这次突袭不如我预期的成功, 我们的奖品真的很少... 不管怎样, 船长, 我们分了这些残羹剩饭, 然后告别吧。 ";
				link.l1 = "如果您不是在数天上的鸟, 而是帮我, 突袭本会成功... 拿走您的份额 - "+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+", 然后消失! ";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "poor";
				break;
			}
			if (iTemp > 100 && iTemp < 500)
			{
				dialog.text = "干得好, 船长! 奖品是"+FindRussianQtyString(iQty)+"件。 我的份额是"+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+"。 ";
				link.l1 = "没错, "+npchar.name+"。 我没有异议。 长艇正在装货。 也许我们会再见面... ";
				link.l1.go = "MarchCap_Talk_exit";
				pchar.GenQuest.MarchCap = "good";
				break;
			}
			dialog.text = "太棒了, 船长! 正如我所说 - 相当容易, 哈哈... 奖品非常丰厚, 比我预期的多得多。 有"+FindRussianQtyString(iQty)+"件。 我的份额是"+FindRussianQtyString(sti(pchar.GenQuest.MarchCap.CapPart))+"。 ";
			link.l1 = "没错, "+npchar.name+"。 我没有异议。 长艇正在装货。 也许我们将来会再次一起突袭? 您看起来适合做我的同伴。 ";
			link.l1.go = "MarchCap_Deck_continue";
			pchar.GenQuest.MarchCap = "exellent";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "MarchCap_repeat":
			dialog.text = ""+GetAddress_Form(NPChar)+", 去您的船。 我们没有时间闲聊。 让我们起航! ";
			link.l1 = "是的, 是的, 当然, 您说得对。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "MarchCap_repeat";
		break;
		
		case "MarchCap_exit":
			dialog.text = "嗯... 我不会去的。 滚吧! 我自己干! ";
			link.l1 = "好吧, 好吧, 祝您旅途愉快... ";
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