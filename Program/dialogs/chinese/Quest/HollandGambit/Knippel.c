// 查理.克尼佩尔 - 老炮兵
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i, iTemp, amount;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индeкс в концe
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		// 选择英国路线的分支
		if(CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Eng") && !CheckAttribute(npchar, "quest.HWICTake") && !CheckAttribute(pchar, "questTemp.HWIC.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
		{
			dialog.text = "啊哈, 伙计, 链弹打我屁股! 什么风把你吹来了? ";
			link.l1 = "链弹打你... 什么? 哦没关系, 只是想打个招呼。 ";
			link.l1.go = "exit";
			link.l2 = "问候你, 克尼佩尔先生。 哈, 我知道为什么他们叫你克尼佩尔了。 不管怎样, 有传言说你曾在英国海军服役。 我有一艘好船和熟练的船员, 想为英国王室... 呃... 联邦效力。 你能给我一些建议, 或者推荐我给某人, 或者在这件事上帮助我吗? ";
			link.l2.go = "Knippel_check";
			break;
		}
		// 选择荷兰路线
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "toKnippel")
			{
				dialog.text = "啊哈伙计, 链弹打我屁股! 什么风把你吹来了? ";
				link.l1 = "问候你, 克尼佩尔先生。 哈, 我知道为什么他们叫你克尼佩尔了。 有传言说你曾在英国海军服役, 所以我想请你帮忙... ";
				link.l1.go = "Dominica";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "链弹打我屁股! 你想要什么, 伙计? ";
			link.l1 = "不, 没什么。 我走了。 ";
			link.l1.go = "exit";
			break;
		}
		// 选择英国路线
		if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
		{
			if (pchar.questTemp.HWIC.Eng == "TakeHollConvoy")
			{
				dialog.text = "啊哈船长, 我听说了一些关于银色商队被拦截的传言... ";
				link.l1 = "你消息很灵通, 克尼佩尔先生。 ";
				link.l1.go = "HollConvoy_Check";
				DelLandQuestMark(npchar);
				DelMapQuestMarkCity("SentJons");
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Wait")
			{
				dialog.text = "有问题吗, 船长? ";
				link.l1 = "不, 没什么。 我走了。 ";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Eng == "Start_main")
			{
				dialog.text = "很高兴见到你, 船长! 我的指挥官理查德.弗利特伍德本打算亲自来这里认识你, 但昨晚发生了意外... 有人甚至在街道中央试图杀死他, 链弹打我屁股! ";
				link.l1 = "不可能! 卫兵在做什么? ";
				link.l1.go = "Fleetwood_house";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "有问题吗, 船长? ";
			link.l1 = "不, 没什么。 我走了。 ";
			link.l1.go = "exit";
		break;
		}
			dialog.text = "啊哈伙计, 链弹打我屁股! 什么风把你吹来了? ";
			link.l1 = "你好, 只是路过。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------选择荷兰路线--------------------------------------------------	
		case "Dominica":
			dialog.text = "啊哈, 是这样吗? 一个老水手怎么能帮助你呢, 伙计? ";
			link.l1 = "看... 我只是一个普通船长, 在马提尼克和库拉索之间定期航行。 所以我在马提尼克附近两次被幽灵船袭击... 不过事情是这样的, 她不是法塔莫加纳或飞翔的荷兰人。 我能用普通炮弹撕裂她的帆! ";
			link.l1.go = "Dominica_1";			
		break;
		
		case "Dominica_1":
			dialog.text = "是这样吗? 幽灵船被实心弹打坏帆布, 这可不像幽灵船该有的样子, 真让我震惊... ";
			link.l1 = "我们能幸存只是因为我的船在顶风航行时能超过它。 上次我不得不把所有货物扔到海里来减轻船体才能逃脱... 你能想象损失吗? 令人心碎! ";
			link.l1.go = "Dominica_2";			
		break;
		
		case "Dominica_2":
			dialog.text = "真让我失望, 船长... ";
			link.l1 = "库拉索总督马蒂亚斯.贝克对我的抱怨置之不理。 他说幽灵船的故事是无稽之谈, 我的守望员喝醉酒了。 马提尼克总督承诺派巡逻队去那里, 但他的眼神告诉我他根本不想做任何事。 在那个混蛋海盗'幽灵'徘徊的时候, 我无法返回马提尼克。 我的船很小, 船员也少, 第三次相遇可能无法幸存... ";
			link.l1.go = "Dominica_3";			
		break;
		
		case "Dominica_3":
			dialog.text = "太遗憾了, 伙计。 但我怎么帮你? ";
			link.l1 = "我从这里的水手那里听说, 圣约翰有一位名叫理查德.弗利特伍德的船长曾追捕过这艘幽灵船。 我不认识他, 所以把我的不幸故事告诉你, 也许你可以把我的遭遇转告给他? 我确信这个肮脏的海盗藏在多米尼加的荒野海岸附近, 在巴巴多斯和马提尼克之间袭击。 ";
			link.l1.go = "Dominica_4";			
		break;
		
		case "Dominica_4":
			dialog.text = "在巴巴多斯和马提尼克之间? 呀哈! 一条肥美的贸易航线。 听起来很像那种混蛋会做的事。 ";
			link.l1 = "我不富有也不肥胖, 没有钱贿赂海军船长获得军事护送。 但是, 如果弗利特伍德爵士已经在追捕这个混蛋, 你能告诉他在哪里可以找到这个'飞翔的荷兰人'吗? ";
			link.l1.go = "Dominica_5";			
		break;
		
		case "Dominica_5":
			dialog.text = "你来到这里做了件好事, 伙计。 我会把你的故事告诉合适的人, 链弹打我的肝! 很快, 你就能再次和马提尼克进行贸易了。 ";
			link.l1 = "希望上帝能听到你的话! 谢谢你听我说, 查理。 我真的希望最好的结果。 再见, 避开链弹! ";
			link.l1.go = "Dominica_6";			
		break;
		
		case "Dominica_6":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toDominica";
			AddQuestRecord("Holl_Gambit", "1-17");
			pchar.quest.toDominica.win_condition.l1 = "location";
			pchar.quest.toDominica.win_condition.l1.location = "Dominica";
			pchar.quest.toDominica.function = "PrepareToFleetwoodAttack";
			DelMapQuestMarkShore("Shore1");
			DelMapQuestMarkShore("Shore2");
			AddMapQuestMarkIsland("Dominica", true);
		break;

//----------------------------------------------选择英国路线--------------------------------------------------	
		case "Knippel_check"://开始检查玩家的各项条件
			if(makeint(PChar.reputation.nobility) < 48)//贵族声誉低
			{
				Notification_Reputation(false, 48, "low");
				PlaySound("Voice\English\hambit\Charlie Knippel-04.wav");
				dialog.text = "快乐的老英格兰不需要流氓的服务, 链弹打我屁股! 恭敬地说, 你可以滚蛋了。 ";
				link.l1 = "嘿, 伙计, 注意你的嘴, 否则我就把它缝起来! ";
				link.l1.go = "exit";
				break;
			}
			else
			{
				Notification_Reputation(true, 48, "low");
			}
			if(GetSummonSkillFromName(pchar, SKILL_SAILING) < 30)//航海技能低
			{
				dialog.text = "船长, 我直说了。 你连湿麻袋都开不出去。 等你有更多航海技能再来, 懂吗? ";
				// belamour legendary edition 显示标准  -->
				notification("技能检查失败 (30)", SKILL_SAILING);
				//<--
				dialog.text = "船长, 我们的舰队需要有经验的船长, 不是笨手笨脚的人。 等你掌握了航海艺术再来。 ";							
				link.l1 = "我明白... 那我稍后见。 ";
				link.l1.go = "exit";
				break;
			}
			else
			{
				notification("技能检查通过", SKILL_SAILING);
			}
			dialog.text = "啊哈, 你来得正是时候, 船长, 链弹打我屁股! 理查德不知道该依靠谁来做这个危险的事情, 他甚至考虑过拒绝... 所以今天机会的小鸟在你耳边甜蜜地歌唱。 如果你达到我们的标准, 我会把你推荐给某个非常重要的人。 你有足够的勇气处理吗? ";
			link.l1 = "我的炮筒里装满了葡萄弹, 克尼佩尔先生。 ";
			link.l1.go = "Knippel_task";
		break;
		
		case "Knippel_task"://第一个任务
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Lucas"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "啊哈! 我看你很有勇气, 船长! 很快就会有火光! 现在仔细听着。 荷兰西印度公司的银色舰队一两天前从库拉索的威廉斯塔德出发, 正驶向菲利普斯堡。 这次舰队只有几艘船, 一艘载有银货的大帆船和两艘护卫舰。 拦截银色舰队, 捕获载有银货的东印度大帆船并带到安提瓜。 你可以击沉护卫舰, 它们是可牺牲的。 链弹打它们的肝, 呀! ";
			link.l1 = "它们的日子不多了。 ";
			link.l1.go = "Knippel_task_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_task_1":
			dialog.text = "一些建议, 船长。 从库拉索到圣马丁的贸易航线离圣克里斯托弗海岸不远。 我建议在那里准备伏击。 为这次交战好好准备你和你的船。 与西印度公司纠缠不是和漂亮女孩在公园散步。 ";
			link.l1 = "我知道我在做什么, 但我欣赏你的坦率, 克尼佩尔先生。 我会带着荷兰的银子回来。 ";
			link.l1.go = "Knippel_task_2";			
		break;
		
		case "Knippel_task_2":
			DialogExit();
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Eng = "true";//标志已选择英国路线
			HWICSilverConvoyInWorld();
			AddQuestRecord("Holl_Gambit", "2-1");
			ReOpenQuestHeader("Holl_Gambit"); // 丹尼拉, 以便从档案中取出
			pchar.questTemp.HWIC.Eng = "begin";
			SetFunctionTimerCondition("HollConvoy_Over", 0, 0, 15, false);
		break;
		
		case "HollConvoy_Check"://开始检查
			int iHal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_GALEON_L) iHal++;
				}
			}//标志中队中是否有大型帆船
			if (iHal > 0)
			{
				amount = sti(pchar.questTemp.HWIC.Eng.SlvQty) - GetSquadronGoods(pchar, GOOD_SILVER);
				if (amount <= 0)
				{
					dialog.text = "不需要告诉我发生了什么, 船长。 海关人员检查你的船时我已经知道了一切... 你做得很好, 船长。 非常出色! 听起来不容易, 链弹打我屁股! ";
					link.l1 = "被欣赏的感觉很好。 ";
					link.l1.go = "HollConvoy_complete";
				}
				else
				{
					dialog.text = "不需要告诉我发生了什么, 伙计。 海关人员检查你的船时我已经知道了一切... 你没能带回全部银子, 链弹打我屁股! 我确切知道那艘东印度船上有多少银子, 精确到比索。 这次任务的目的不仅是测试你的战斗技能, 更是测试你的诚实。 你后者失败了。 滚出我的房子, 水手! ";
					link.l1 = "那你去死吧, 傻瓜! ";
					link.l1.go = "HollConvoy_fail";
				}
			}
			else
			{
				dialog.text = "停, 伙计。 我没在你的中队看到荷兰东印度船。 我告诉过你把她作为战利品带来。 你卖了她, 想自己留钱, 嗯? ";
				link.l1 = "等等, 我应该带船来吗? 我以为你只想要银子。 ";
				link.l1.go = "HollConvoy_noShip";
			}
		break;
		
		case "HollConvoy_noShip":
			dialog.text = "没有人能把查理.克尼佩尔当傻瓜, 伙计! 我清楚地记得我告诉过你什么, 没告诉过你什么。 你违反了我们的交易条款, 没有诚实的英国人会和你合作, 这里没有无赖的位置。 滚出我的房子, 水手! ";
			link.l1 = "那你去死吧, 傻瓜! ";
			link.l1.go = "HollConvoy_fail";
		break;
		
		case "HollConvoy_fail":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-3");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Eng");//清除以便回滚到荷兰路线
			pchar.questTemp.HWIC.Fail2 = "true";
		break;
		
		case "HollConvoy_complete":
			dialog.text = "明天来见我, 我会把你介绍给我的赞助人。 他会给你一些更值得你技能的工作。 另外他会考虑你的... 经济奖励。 出发! ";
			link.l1 = "很好, 克尼佩尔先生。 我明天会来。 ";
			link.l1.go = "exit";
			npchar.greeting = "knippel_2";
			AddDialogExitQuestFunction("HollConvoy_Remove");
			AddQuestRecord("Holl_Gambit", "2-4");
			SetTimerFunction("EnglandGambit_2_ZadanieStart", 0, 0, 1);
			pchar.questTemp.HWIC.Eng = "Wait";
			AddSimpleRumourCity("他们说你捕获了一艘装满银子的荷兰船。 干得好! 你是个勇敢的水手, 船长! 祝你好运! ", "SentJons", 10, 3, "");
		break;
		
		case "Fleetwood_house":
			dialog.text = "我也在问自己同样的问题... 某个混蛋在理查德甚至来不及抓住他的刀之前, 把胡椒粉撒进弗利特伍德船长的眼睛, 并刺伤了他的胸部。 凶手希望一击致命, 因为他没有时间再刺一次, 但他失败了。 弗利特伍德船长总是在外套下穿胸甲\n那个肮脏的人渣, 链弹打他的肝, 设法逃跑并躲藏起来。 看起来他在镇上有朋友。 船长记得的唯一细节是刺客只有一只眼睛。 但这对我们帮助不大, 如今码头到处都是像他这样的独眼龙\n理查德失血很多, 胡椒粉严重刺激了他的眼睛, 现在几乎失明... ";
			link.l1 = "胡椒粉? 那是让某人失明的昂贵方式。 弗利特伍德一定真的惹到了什么人。 我为你的船长感到遗憾。 寻找袭击者有什么发现吗? ";
			link.l1.go = "Fleetwood_house_1";
		break;
		
		case "Fleetwood_house_1":
			dialog.text = "弗利特伍德船长的海军陆战队员搜查了整个城镇和当地海湾, 但什么也没找到, 链弹打他们的脖子! 如果我们在袭击后没有立即找到他, 现在就没有希望找到那个混蛋了。 弗利特伍德船长有很多敌人... 但是, 船长, 尽管发生了意外, 我的指挥官还是想见你。 他现在在他的房子里休息, 所以我们去见他吧。 跟我来! ";
			link.l1 = "带路吧, 克尼佩尔先生。 ";
			link.l1.go = "Fleetwood_house_2";
		break;
		
		case "Fleetwood_house_2":
			chrDisableReloadToLocation = true;//关闭地点
			bDisableFastReload = true;//关闭快速传送
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//防止逃跑
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_town", "reload", "houseH1", "OpenTheDoors", -1);
			pchar.quest.Knippel_Outside.win_condition.l1 = "location";
			pchar.quest.Knippel_Outside.win_condition.l1.location = "SentJons_town";
			pchar.quest.Knippel_Outside.function = "Knippel_GoTown";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);
			sld = characterFromId("Fleetwood");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
			AddLandQuestMark(sld, "questmarkmain");
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.money = 110000;
		break;
		
		case "InFleetwoodHouse":
			dialog.text = "弗利特伍德船长在楼上他的房间里。 去找他, 他在等你。 我留在这里。 ";
			link.l1 = "明白了, 克尼佩尔先生。 我这就去。 ";
			link.l1.go = "exit";	
		break;
		
		case "Knippel_ToOfficer":
			dialog.text = "听着, 船长... 弗利特伍德船长现在安全且受到良好照顾。 我想帮你向袭击他的混蛋报仇。 我提供我的服务作为炮术军官。 我不太擅长击剑, 太老了, 但我可以在一千步外打掉商船的顶桅。 ";
			link.l1 = "现在我想看看。 欢迎登船, 克尼佩尔先生! ";
			link.l1.go = "Knippel_ToOfficer_1";	
		break;
		
		case "Knippel_ToOfficer_1":
			ForceHeroAutolevel(npchar);
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", false);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", false);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", false);//打开定位器
			// 克尼佩尔 - 成为军官
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //不要试图离开
			npchar.HalfImmortal = true;//半不朽
			npchar.loyality = 20;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			SetFunctionTimerCondition("GotoBridgetownOver", 0, 0, 30, false);//一个月内完成所有事情
			AddSimpleRumourCity("他们说理查德.弗利特伍德爵士本人都欠你的人情。 你在我们镇上是个非常重要的人, 先生", "SentJons", 10, 3, "");
		break;
		
		case "hired":
			dialog.text = "啊哈船长! 需要什么? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			if (pchar.questTemp.HWIC.Eng == "MirageFail")
			{
				dialog.text = "你是个十足的小丑, 伙计, 链弹打我屁股! 你连一个基本任务都失败了 - 捕获'幻影'而不失去'瓦尔基里'\n我们的船员不会再在你的指挥下服务。 我们确信弗利特伍德爵士会批准我们的决定, 他和我们一样不喜欢白痴。 ";
				link.l1 = "去你和你主人的! ";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "GotoBridgetown" || pchar.questTemp.HWIC.Eng == "SeekVanBerg")
			{
				dialog.text = "你是个十足的白痴, 伙计, 链弹打我屁股! 我们浪费了太多时间解决你的个人问题\n我们的船员不会再为你服务。 我们确信弗利特伍德爵士会批准我们的决定, 他和我们一样不喜欢白痴。 ";
				link.l1 = "去你和你主人的! ";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "VanBergFailInWorld")
			{
				dialog.text = "你是个十足的白痴, 伙计, 链弹打我屁股! 你被告知要在'瓦尔基里'上扮演一个孤独的商人, 你做了什么? 你用你的舰队把海盗吓跑了! \n我们确信弗利特伍德爵士会批准我们的决定, 他和我们一样不喜欢白痴。 ";
				link.l1 = "去你和你主人的! ";
				link.l1.go = "exit";
			}
			if (pchar.questTemp.HWIC.Eng == "MirageTake")
			{
				dialog.text = "你是个十足的白痴, 伙计, 链弹打我屁股! 你决定浪费我们的时间做任何事, 除了捕获'幻影'和航行到安提瓜? \n我们的船员不会再为你服务。 我们确信弗利特伍德爵士会批准我们的决定, 他和我们一样不喜欢白痴。 ";
			link.l1 = "去你和你主人的! ";
			link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_VALCIRIA)//如果自己在瓦尔基里上
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "Boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA)
						{
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Eng.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "SentJons_houseH1", "goto", "goto1");//克尼佩尔回家
			pchar.questTemp.HWIC.Eng = "end";
			pchar.questTemp.HWIC.Detector = "eng_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "OnCuracao":
			pchar.quest.HWICEng_toBarbadosOver.over = "yes";//取消中断
			dialog.text = "问候你, 船长。 很高兴见到你! ";
			link.l1 = "问候你, 克尼佩尔先生。 你有钱吗? 给我, 我们去威廉斯塔德接阿比盖尔。 你会加入我吗? ";
			link.l1.go = "OnCuracao_1";	
		break;
		
		case "OnCuracao_1":
			dialog.text = "船长, 听着... 现在不需要去任何地方。 ";
			link.l1 = "你在说什么? 这是胡说八道! ";
			link.l1.go = "OnCuracao_2";	
		break;
		
		case "OnCuracao_2":
			dialog.text = "我有一封弗利特伍德船长给你的信, 还有钱。 但这笔钱不是给阿比盖尔父亲的, 而是给你的。 二十万比索。 读这封信, 尽量不要太严厉地评判他... ";
			link.l1 = "这些天到底发生了什么? 又是一个不愉快的惊喜? 把信给我! ";
			link.l1.go = "OnCuracao_3";	
		break;
		
		case "OnCuracao_3":
			DialogExit();
			NextDiag.CurrentNode = "OnCuracao_4";
			AddMoneyToCharacter(pchar, 200000);
			LAi_SetCitizenType(npchar);
			npchar.lifeday = 1;//再让他在海滩上多走几天
			pchar.quest.Holland_ShoreAttack.win_condition.l1 = "location";
			pchar.quest.Holland_ShoreAttack.win_condition.l1.location = "Curacao";
			pchar.quest.Holland_ShoreAttack.function = "CreateHollandShorePatrol";//在沿海水域巡逻
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", false);//打开地下室
			pchar.questTemp.HWIC.Eng = "MerdokMeeteng";
			AddQuestRecordInfo("LetterFromFleetwood", "1");
			AddQuestRecord("Holl_Gambit", "2-23");
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "OnCuracao_4":
			dialog.text = "你读了吗, 船长? 我直说了。 我为弗利特伍德船长和他所做的事感到羞耻, 链弹打他的... 啊, 去他的。 罗登堡得知阿比盖尔和理查德的恋情后非常愤怒。 巡逻队正在搜查库拉索, 公司的军舰在当地水域巡航。 我们需要离开这里。 \n船长, 你需要炮手吗? 我不需要奢侈 - 只要定期有正常的海粮。 我不太擅长击剑, 太老了, 但我可以在一千步外打掉商船的顶桅。 ";
			link.l1 = "好吧, 该死, 我想看看你能不能做到, 克尼佩尔先生。 欢迎加入船员! ";
			link.l1.go = "Knippel_hire";
			link.l2 = "我后悔一开始就帮助你们这些英国混蛋。 我现在不知道如何摆脱这个烂摊子。 走你自己的路, 我受够了惊喜。 ";
			link.l2.go = "Knippel_exit";
			DelLandQuestMark(npchar);
		break;
		
		case "Knippel_hire":
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			npchar.quest.OfficerPrice = sti(pchar.rank)*200;
			npchar.OfficerWantToGo.DontGo = true;
			DeleteAttribute(npchar, "CompanionDisable");//现在可以加入伙伴
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.loyality = MAX_LOYALITY;
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
		
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 120, 120);
			LAi_SetOfficerType(npchar);
			npchar.greeting = "knippel_hire";
			NextDiag.CurrentNode = "Knippel_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			ForceHeroAutolevel(npchar);
			
			// Sinistra - 两个月后启动查理.克尼佩尔的个人任务"旧罪的长影"
			SetTimerCondition("DTSG_Start", 0, 0, 60, false);
		break;
		
		case "Knippel_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
		break;
		
//------------------------------------------------对抗所有人-----------------------------------------------
		case "Knippel_abordage":
			dialog.text = "停, 你这个混蛋! 你为什么攻击这艘和平的荷兰船? 我没有任何贵重物品或黄金, 链弹打我屁股! ";
			link.l1 = "荷兰船? 哈哈! 别让我笑了,'荷兰人'。 我攻击你的双桅帆船是为了捕获你, 亲爱的查理。 欢迎来到我的货舱。 我们会谈谈你要去哪里航行, 为什么... ";
			link.l1.go = "Knippel_abordage_1";	
		break;
		
		case "Knippel_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-20");
            pchar.quest.Knippel_DieHard.over = "yes";
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "KnippelPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveKnippelOver", 0, 0, 1, false);//таймeр до конца суток, ибо нeфиг
		break;
		
		case "Knippel_prisoner":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\hambit\Charlie Knippel-07.wav");
			dialog.text = "你是个魔鬼, 海盗... 你会因所有罪孽在地狱燃烧! 尖叫... ";
			link.l1 = "放松, 传教士。 你像清教徒一样传教。 你最好先看看自己的灵魂状态。 ";
			link.l1.go = "Knippel_prisoner_1";
		break;
		
		case "Knippel_prisoner_1":
			dialog.text = "你计划什么, 恶棍? 你想从我指挥官和可怜的荷兰女孩那里得到什么? ";
			link.l1 = "这不关你的事, 查理。 我不再需要你了。 起来。 ";
			link.l1.go = "Knippel_prisoner_2";	
		break;
		
		case "Knippel_prisoner_2":
			dialog.text = "你想杀我吗? 值得像你这样的混蛋。 *吐口水* 去你的! ";
			link.l1 = "起来, 查理。 做最后的祈祷。 ";
			link.l1.go = "Knippel_prisoner_3";	
		break;
		
		case "Knippel_prisoner_3":
			DialogExit();
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "Kill_Knippel", 3.5);
			pchar.quest.RemoveKnippelOver.over = "yes";//取消计时器
		break;
		
		//--> --------------------------------- —军官模块 ------------------------------------------
		case "Knippel_officer":
			dialog.text = "啊哈船长, 链弹打我屁股! ";
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "炮弹塞我肝里吧, 船长。 老子以后再也不上岸了。 上次在酒馆里掷骰子的时候, 有个杂种把我兜里的钱偷得一干二净。";
				Link.l1 = "哈哈, 你确定不是自己输光的吗, "+npchar.name+"? 不过, 这不重要…… 我其实是想和你谈件事。 我决定去欧洲——搭别人的船, 当个乘客。 我不知道什么时候才能回来, 也不指望你在这儿等我, 更不会把你硬拖着一起走。 ";
				Link.l1.go = "SharlieEpilog_Knippel_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "克尼佩尔先生, 我要去古老失落的印第安城市泰亚萨尔。 我直说, 这将是一次非常危险的旅行, 也很不寻常 - 我们需要通过这个... 魔法偶像到达那里。 你会加入我吗? ";
				Link.l4.go = "tieyasal";
			}
			
			// 军需官报告
           	// boal отчёт о кораблe
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
				Link.l11 = "克尼佩尔先生, 给我一份完整的船只报告。 ";
				Link.l11.go = "QMASTER_1";
				
				// 战船自动购买货物
				Link.l12 = "我希望你每次靠港时购买特定货物。 ";
				Link.l12.go = "QMASTER_2";
			}
			
			if (CheckAttribute(NPChar, "IsCompanionClone"))// 伙伴模式
			{
				//dialog.text = "Я прибыл по вашeму распоряжeнию, капитан.";
				Link.l2 = "我需要给你下达几个命令。 ";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Knippel_officer";
				break;
			}
			Link.l1 = "听我的命令! ";
            Link.l1.go = "stay_follow";
			link.l2 = "没什么。 解散! ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Knippel_officer";
		break;
		
		// 军需官响应
		case "QMASTER_1":
			dialog.Text = "击沉我... 枪支没问题, 我们更换爆炸的枪支, 保持火药干燥安全。 你期望什么样的报告, 船长? 我是个老炮手, 不是事务长。 链弹打我屁股, 不过我是加勒比最好的炮手, 记住! ";
			Link.l1 = "这里不争论, 克尼佩尔先生, 你确实了解你的行当。 我会自己找事务长, 别担心。 ";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "你想让老查理把炮甲板换成后甲板? 船长, 我击沉船只, 不是为每个比索争吵。 我确信我们在第一个殖民地尝试这个时就会被敲诈。 ";
			link.l1 = "当然, 克尼佩尔先生。 我应该开始找一个合适的事务长。 ";
			link.l1.go = "exit";
		break;
		
		// 伙伴命令 19.02.08 -->
		case "Companion_Tasks":
			dialog.Text = "我在听你说。 ";
			Link.l1 = "这是关于登船的。 ";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "这是关于你的船的。 ";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // 仅在测试版中
			{
				Link.l3 = "我希望你暂时离开我的中队, 自己去寻找财富。 ";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "目前没有。 ";
			Link.l8.go = "exit";
			break;

		case "Companion_TaskBoarding":
			dialog.Text = "那么你的愿望是什么。 ";
			Link.l1 = "不要登敌船。 照顾好自己和船员。 ";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "我希望你登敌船。 ";
			Link.l2.go = "Companion_TaskBoardingYes";
			break;

		case "Companion_TaskChange":
			dialog.Text = "那么你的愿望是什么。 ";
			Link.l1 = "我希望你登船后不要换船。 你的船太有价值了。 ";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "当你登敌船时, 如果它们不错, 你可以自己拿下。 ";
			Link.l2.go = "Companion_TaskChangeYes";
			break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "是! ";
			Link.l1 = "稍息。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
			break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "会完成的。 ";
			Link.l1 = "稍息。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
			break;

		case "Companion_TaskChangeNo":
			dialog.Text = "是! ";
			Link.l1 = "会完成的。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
			break;

		case "Companion_TaskChangeYes":
			dialog.Text = "会完成的。 ";
			Link.l1 = "稍息。 ";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
			break;
			// <========////////////////////////////////////////

		case "stay_follow":
			dialog.Text = "命令? ";
			Link.l1 = "待在这里! ";
            Link.l1.go = "Boal_Stay";
			Link.l2 = "跟我来, 跟上! ";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "更改你的火器弹药类型。 ";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "选择弹药类型: ";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
			dialog.Text = "部署变更! ";
			Link.l1 = "解散。 ";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
			dialog.Text = "部署变更! ";
			Link.l1 = "解散。 ";
            Link.l1.go = "Exit";
        break;
	//< —--------------------------------- —军官模块 ----------------------------------------
	
	// 前往泰亚萨尔
		case "tieyasal":
			dialog.text = "在我服务期间, 我真的很喜欢你, " +pchar.name+ ", 我不会让我的船长陷入困境。 如果需要, 我会跟着你穿过地狱。 我和你一起去! ";
			link.l1 = "谢谢你, 克尼佩尔先生! 我很高兴我对你的看法是对的。 ";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "我们什么时候开始, 链弹打我的眼睛? ";
			link.l1 = "稍后。 我们必须为此做好准备。 ";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "22");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// Эпилог
		case "SharlieEpilog_Knippel_1":
			dialog.text = "那可真是白白浪费了, 炮弹砸我桅杆吧。我说不定还真想去欧洲看看。";
			link.l1 = "真没想到你会这么说。 那好吧, 欢迎登上轻帆船‘"+GetShipName("Ulysse")+"’。 要是你愿意, 我们还能顺路去拜访一下那位老熟人 一 理查德·弗利特伍德。 我想, 你肯定有话想对他说。 ";
			link.l1.go = "SharlieEpilog_Knippel_2";
		break;

		case "SharlieEpilog_Knippel_2":
			dialog.text = "不了, 先生。理查德见鬼去吧。我既不想听到他的名字, 更不想见到他的人。";
			link.l1 = "随你吧, "+npchar.name+", 随你吧。 我们两周后起航。 我打算办一场告别酒宴。 希望你也能来。";
			link.l1.go = "SharlieEpilog_Knippel_3";
		break;

		case "SharlieEpilog_Knippel_3":
			dialog.text = "要是我拒绝了, 就让炮弹把我脖子打断吧, 船长! ";
			link.l1 = "太好了。 那等我把所有事情处理完, 我们就在酒馆见。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Knippel_officer";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			pchar.questTemp.SharlieEpilog_Knippel = true;
			pchar.questTemp.SharlieEpilog_Friends = sti(pchar.questTemp.SharlieEpilog_Friends) + 1;
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> 处理尝试打开箱子的反应块
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("你是个"+ GetSexPhrase("小偷, 先生! 卫兵, 抓住他","小偷, 女孩! 卫兵, 抓住她") +"!!!", "看看那个! 我一转身, 你就决定检查我的箱子! 抓住小偷!!! ", "卫兵! 抢劫! 抓住小偷!!! ");
			link.l1 = "该死的! ";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- 处理尝试打开箱子的反应块
	}
}