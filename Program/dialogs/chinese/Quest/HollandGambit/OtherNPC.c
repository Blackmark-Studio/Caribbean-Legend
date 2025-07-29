// 其他NPC的对话
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "一个漏洞。 告诉开发者。 ";
			link.l1 = "我会的! ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if (npchar.id == "HWICFernando") NextDiag.CurrentNode = "Fernando";
			DialogExit();
		break;
	
//---------------------------------------前往荷兰--------------------------------------------------
		//护送商人
		case "Baltazar":
			pchar.quest.Create_BaltazarOver.over = "yes";//取消中断
			dialog.text = "运气真好! 船长, 我刚好急需一名护卫送我去菲利普斯堡... ";
			link.l1 = "你是巴尔塔扎尔.里德博克吗? ";
			link.l1.go = "Baltazar_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Baltazar_1":
			dialog.text = "该死, 我已经比总督还出名了! 你是谁? 你想要什么? ";
			link.l1 = "我是" +GetFullName(pchar)+ "船长。 卢卡斯.罗登堡派我来的。 我被授权保护你和你的船。 ";
			link.l1.go = "Baltazar_2";			
		break;
		
		case "Baltazar_2":
			dialog.text = "哦, 罗登堡先生一定是听到了我的求助! 你看, 有个私掠者... ";
			link.l1 = "我们跳过你故事的细节吧, 我已经知道了。 ";
			link.l1.go = "Baltazar_3";			
		break;
		
		case "Baltazar_3":
			dialog.text = "当然! 我已经浪费太多时间了... 我必须不迟于两周内到达菲利普斯堡。 ";
			link.l1 = "那就去你的船上准备航行。 我们马上起航! ";
			link.l1.go = "Baltazar_4";			
		break;
		
		case "Baltazar_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4);
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //始终为友
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			AddQuestRecord("Holl_Gambit", "1-3");
			AddMapQuestMarkCity("Marigo", true);
			if(bImCasual)
			{
				NewGameTip("探索模式: 任务时长翻倍");
				SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 28, false);
			}
			else SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 14, false); //计时器
			pchar.quest.BaltazarConvoy_fail.win_condition.l1 = "NPC_Death";//护送对象沉没时的中断
			pchar.quest.BaltazarConvoy_fail.win_condition.l1.character = "Baltazar";
			pchar.quest.BaltazarConvoy_fail.function = "Baltazar_fail";
			pchar.quest.BaltazarConvoy_complete.win_condition.l1 = "location";//完成时的中断
			pchar.quest.BaltazarConvoy_complete.win_condition.l1.location = "Marigo_town";
			pchar.quest.BaltazarConvoy_complete.function = "Baltazar_complete";
			if (rand(1) == 0)
			{
				BaltazarPirateGlobalCreate();
			}
			else
			{
				pchar.questTemp.HWIC.Holl.BaltazarAttack = "true";
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1 = "location";//完成时的中断
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1.location = "SentMartin";
				pchar.quest.BaltazarConvoy_Attack.function = "BaltazarPirateSeaCreate";
			}
		break;
		
		case "Baltazar_5":
			dialog.text = "感谢你的帮助, 船长! 你的保护来得正是时候, 请接受我的感谢和这5000比索。 ";
			link.l1 = "嗯... 这对于拯救生命来说不是很慷慨的奖励... ";
			link.l1.go = "Baltazar_6";			
		break;
		
		case "Baltazar_6":
			dialog.text = "此外, 我一有机会就会给罗登堡先生写信 —对你的行为给予最高评价。 我现在得走了。 ";
			link.l1 = "好吧, 再见, 巴尔塔扎尔。 ";
			link.l1.go = "Baltazar_7";			
		break;
		
		case "Baltazar_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 3.0);
			AddQuestRecord("Holl_Gambit", "1-6");
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2); 
			ChangeCharacterNationReputation(pchar, HOLLAND, 1);
			ChangeOfficersLoyality("good_all", 1);
			pchar.questTemp.HWIC.Holl = "BaltazarCom";
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		//圣地亚哥的调遣
		case "Santiago_Trip":
			dialog.text = "先生! 等等... 好像你掉了什么东西... ";
			link.l1 = "什么? 啊? ! ";
			link.l1.go = "Santiago_Trip_1";
		break;
		
		case "Santiago_Trip_1":
			DialogExit();
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("你被人从背后打晕了", "", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 15, 10); //转动时间
			RecalculateJumpTable();
			DoQuestFunctionDelay("SantiagoTripInHouse", 4.0);
		break;
		
		case "Santiago_Trip_2":
			dialog.text = "抱歉, 朋友 —我不得不轻轻打你一下, 这样你就不会惹麻烦了。 我知道你可能头疼, 但不管怎样, 你会活下来的。 如果有时间的话... ";
			link.l1 = "你到底是谁, 该死的, 这里发生了什么? ";
			link.l1.go = "Santiago_Trip_3";
		break;
		
		case "Santiago_Trip_3":
			dialog.text = "放松, 放松, 朋友 —否则我不得不再次让你冷静下来。 我们不想让这些拘泥于形式的人闯进来, 挥舞着他们生锈的剑, 对吧? 我们需要安静地谈谈。 ";
			link.l1 = "把我的剑还给我, 混蛋, 我们会好好谈谈, 我发誓! ";
			link.l1.go = "Santiago_Trip_4";
		break;
		
		case "Santiago_Trip_4":
			dialog.text = "你是个敏捷的小家伙, 不是吗? 现在不需要用钢刃。 告诉我我想知道的, 也许你能完整地离开这个地方。 清楚了吗? 那我们聊一聊。 \n保持沉默? 很好, 我们达成协议了。 你从罗登堡那里给银行家带了什么? ";
			link.l1 = "一封信。 ";
			link.l1.go = "Santiago_Trip_5";
		break;
		
		case "Santiago_Trip_5":
			dialog.text = "聪明。 我知道那不是一束雏菊。 那封信里是什么, 孩子? ";
			link.l1 = "我怎么知道? 我没有阅读委托给我的信件的习惯。 也许是封情书。 你知道有权势的人... ";
			link.l1.go = "Santiago_Trip_6";
		break;
		
		case "Santiago_Trip_6":
			dialog.text = "... 在这个悲惨的时代, 诚实的船长真是罕见。 好吧, 这对你来说是个坏消息。 那个该死的银行家收到包裹时说了什么? 他和荷兰人有什么生意? ";
			link.l1 = "他们在交易从法国走私的香水... 或者巴伐利亚的牛粪, 我想。 ";
			link.l1.go = "Santiago_Trip_7";
			link.l2 = "问题是关于某种补偿的。 我只知道这些。 ";
			link.l2.go = "Santiago_Trip_8";
		break;
		
		case "Santiago_Trip_7":
			dialog.text = "你是个勇敢的家伙... 还有幽默感。 杀了你会很可惜。 加斯顿会喜欢你的。 虽然... 暂时待在这里。 我得去检查点东西, 我不在的时候米格尔会看着你。 ";
			link.l1 = "我发誓, ‘我的朋友’ —你会后悔的! ";
			link.l1.go = "Santiago_Trip_9";
		break;
		
		case "Santiago_Trip_8":
			dialog.text = "傲慢消失了... 当情况严峻时, 我们勇敢的船长展现出了理智。 你本可以早点这样做, 节省我们的时间和麻烦。 好吧, 我得去检查点东西, 但之后我会回来, 我们再谈, 如果还有必要的话。 暂时待在这里。 我不在的时候米格尔会看着你。 ";
			link.l1 = "我发誓, ‘我的朋友’ —你会后悔的! ";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_9":
			dialog.text = "当然。 保持安静, ‘英雄’ —也许一切都会好起来的。 ";
			link.l1 = "... ";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_10":
			dialog.text = "待在这里, 希望你的灵活性能证明自己。 ";
			link.l1 = "... ";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_11":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-44");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Santiago_HouseSp2", "goto", "goto4", "", -1);
			pchar.quest.Santiago_Trip1.win_condition.l1 = "item";
			pchar.quest.Santiago_Trip1.win_condition.l1.item = "slave_01";
			pchar.quest.Santiago_Trip1.function = "SantiagoTrip_wait";
		break;
		
		case "Santiago_Trip_12":
			dialog.text = "搞什么鬼? ! ";
			link.l1 = "准备受死吧, 你这个无赖! ";
			link.l1.go = "Santiago_Trip_13";
		break;
		
		case "Santiago_Trip_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitFromRoom");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Santiago_Trip_14":
			dialog.text = "真是一团糟! 我一直在想这噪音是怎么回事。 恭喜你 —你是个聪明人! ";
			link.l1 = "比你想象的更聪明... 现在看看你能对一个武装对手做什么! ";
			link.l1.go = "Santiago_Trip_15";
		break;
		
		case "Santiago_Trip_15":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitHouse");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//第5个任务的军官信使
		case "HollQuest_Officer":
			dialog.text = "卢卡斯.罗登堡先生想立刻见你。 马上来见他。 ";
			link.l1 = "这就去。 ";
			link.l1.go = "HollQuest_Officer_exit";			
		break;
		
		case "HollQuest_Officer_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.HWIC.Holl = "MerdokStart";
			AddQuestRecord("Holl_Gambit", "1-36");
		break;
		
//---------------------------------------------对抗所有人----------------------------------------------
		//除掉西班牙贵族
		case "Fernando":
			dialog.text = "你想从我这里得到什么? ";
			link.l1 = "你的头! ";
			link.l1.go = "Fernando_fight";
			link.l2 = "没什么, 没关系。 ";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";
		break;
		
		case "Fernando_repeat":
			dialog.text = "又是你? 你想从我这里得到什么? ! 解释一下! ";
			link.l1 = "你的头! ";
			link.l1.go = "Fernando_fight";
			link.l2 = "没什么, 没关系。 ";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";		
		break;
		
		case "Fernando_fight":
			chrDisableReloadToLocation = true;//关闭出口
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.HWIC_Fernando.win_condition.l1 = "NPC_Death";
			pchar.quest.HWIC_Fernando.win_condition.l1.character = "HWICFernando";
			pchar.quest.HWIC_Fernando.function = "Fernando_died";
		break;
		
		//在弗利特伍德的房子里
		case "Fleetwood_soldier"://给喜欢多管闲事的人
			if (CheckAttribute(npchar, "quest.talked"))
			{
			dialog.text = "又是你? 你为什么在这里嗅来嗅去? 我一点都不喜欢。 好吧, 我要逮捕你, 把你送到指挥官办公室调查。 孩子们, 抓住这个人! ";
			link.l1 = "但我只是想... ";
			link.l1.go = "Fleetwood_soldier_4";	
			}
			else
			{
			dialog.text = "你是谁, 想要什么? 解释一下! ";
			link.l1 = "对不起, 先生, 好像我走错房子了。 请原谅。 ";
			link.l1.go = "Fleetwood_soldier_1";	
			link.l2 = "我想见理查德.弗利特伍德。 ";
			link.l2.go = "Fleetwood_soldier_2";		
			}
		break;
		
		case "Fleetwood_soldier_1":
			dialog.text = "没错。 你和错误的人说话了。 请立刻离开! ";
			link.l1 = "好的。 当然。 ";
			link.l1.go = "Fleetwood_soldier_3";			
		break;
		
		case "Fleetwood_soldier_2":
			dialog.text = "真的吗? 谁告诉你他住在这里的? 这似乎很可疑... 好吧, 我要逮捕你, 把你送到指挥官办公室调查。 孩子们, 抓住这个人! ";
			link.l1 = "但我只是想见理查德... ";
			link.l1.go = "Fleetwood_soldier_4";	
		break;
		
		case "Fleetwood_soldier_3":
			DialogExit();
			npchar.quest.talked = "true";
			DoQuestReloadToLocation("SentJons_town", "reload", "houseSP3", "");
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//给固执的人
		break;
		
		case "Fleetwood_soldier_4":
			DialogExit();
			GoToPrison("SentJons", 1000, 10);			
		break;
		
		case "Theft_soldier":
			dialog.text = "啊! 小偷? 间谍? 现在小心了! ";
			link.l1 = "哼! ";
			link.l1.go = "Attack_Theft_soldier";			
		break;
		
		case "Attack_Theft_soldier":
			LAi_group_Delete("EnemyFight");
			LAi_SetHP(npchar, 500, 500);
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Attack_soldier":
			dialog.text = "啊! 这家伙在这里干什么? 孩子们, 我们抓到一个间谍! 拿起武器! ";
			link.l1 = "哼! ";
			link.l1.go = "Attack_soldier_fight";			
		break;
		
		case "Attack_soldier_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//取消战斗禁止
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
			sld = characterFromId("Attack_sold_"+i);	
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareToStreetFight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//囚室里的克尼佩尔俘虏
		case "Sailor_deck":
			chrDisableReloadToLocation = true;
			dialog.text = "船长, 我们按你说的审问了这个恶棍。 我们不得不稍微灼烧了他一下... 他身上有这封信。 他想吃掉它, 但我们没让。 正如我们所想, 他要在威廉斯塔德带走一个女孩, 把她交给他的老板。 ";
			link.l1 = "一封信? 让我看看。 然后我自己和他谈。 ";
			link.l1.go = "Sailor_deck_1";			
		break;
		
		case "Sailor_deck_1":
			DialogExit();
			AddLandQuestMark(characterFromId("KnippelClone"), "questmarkmain");
			GiveItem2Character(pchar, "NPC_Letter");
			AddQuestRecordInfo("LetterToAbi", "1");
		break;
		
		case "Sailor_deck_2":
			dialog.text = "你有什么命令, 船长? ";
			link.l1 = "把尸体扔到海里。 准备上岸! ";
			link.l1.go = "Sailor_deck_3";			
			// belamour legendary edition -->
			link.l2 = "以全部军事荣誉将他海葬。 那个老人勇敢战斗到最后。 甚至在大炮从炮架上被击落之后, 他还在装填和瞄准。 真可惜。 在另一个世界我们可能会成为战友... ";
			link.l2.go = "Sailor_deck_3a";
		break;
		
		case "Sailor_deck_3a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			dialog.text = "是, 船长! ";
			link.l1 = "... ";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_3":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// < —legendary edition
			dialog.text = "是, 船长! ";
			link.l1 = "... ";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-21");
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "ReturnMCPlayer", 3);
			}
			pchar.questTemp.HWIC.Self = "toVillemstad";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//打开阿比的房子
			LocatorReloadEnterDisable("Villemstad_houseSP2", "reload2", true);//关闭阿比的房间
		break;
		
		//囚室里的朗威俘虏
		case "Sailor_deck_5":
			chrDisableReloadToLocation = true;
			dialog.text = "我们已经按你的命令准备好审问那个中国人了, 船长。 他身上什么都没有, 没有文件。 已经准备好火盆, 我们现在正在把镣铐和钳子烧红。 ";
			link.l1 = "干得好, 阿隆索。 但在你开始之前, 我想试着和他讲道理。 也许他会愿意合作? ";
			link.l1.go = "Sailor_deck_6";			
		break;
		
		case "Sailor_deck_6":
			dialog.text = "如你所说, 船长。 ";
			link.l1 = "... ";
			link.l1.go = "exit";	
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Sailor_deck_7":
			dialog.text = "是的, 船长? ";
			link.l1 = "给他戴上镣铐, 在我们到达瓜德罗普岛之前一直盯着他。 你们三个必须一直在这里。 你们要用生命为他负责。 ";
			link.l1.go = "Sailor_deck_8";			
		break;
		
		case "Sailor_deck_8":
			dialog.text = "是, 船长! ";
			link.l1 = "";
			link.l1.go = "Sailor_deck_9";			
		break;
		
		case "Sailor_deck_9":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-48");
			sld = characterFromId("LongwayClone");
			LAi_SetActorType(sld);
			LAi_SetGroundSitType(sld);
			DialogExit();
			pchar.quest.Longway_Shore.win_condition.l1 = "location";
			pchar.quest.Longway_Shore.win_condition.l1.location = "Shore31";
			pchar.quest.Longway_Shore.function = "LongwayInShore";
			AddMapQuestMarkShore("Shore31", true);
			if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 遵守最后期限! ");
		break;
		
		//醉汉 - 给弗利特伍德送信
		case "Drunkard":
			DelLandQuestMark(npchar);
			dialog.text = "哈-嗝! 晚上好, 先生! 你想要什么? 也许你可以给一个老醉鬼买杯酒? 而我会... ";
			link.l1 = "听着, 老醉鬼... 你是杰克.哈里森吗? ";
			link.l1.go = "Drunkard_1";			
		break;
		
		case "Drunkard_1":
			dialog.text = "哦! 是的, 是我。 还能是谁? 怎么了? 我-们-该-拿-一-个-醉-酒-的-水-手-怎-么-办... ";
			link.l1 = "哦, 我的上帝, 给我点耐心! 什么水手? 你脸上写着你是个陆地lubber... 你想赚钱吗? ";
			link.l1.go = "Drunkard_2";			
		break;
		
		case "Drunkard_2":
			dialog.text = "我总是想赚钱。 我该做什么? 但我不会杀人, 也不会偷东西, 而且你不是我喜欢的类型。 ";
			link.l1 = "你不必杀人, 我怀疑你实际上也做不到。 你太笨手笨脚了。 现在, 这是一封信。 把它送到总督官邸左边的房子, 是给理查德.弗利特伍德的。 ";
			link.l1.go = "Drunkard_3";			
		break;
		
		case "Drunkard_3":
			dialog.text = "给理查德.弗利特伍德? 不... 我一出现就会被逮捕。 ";
			link.l1 = "闭嘴听着。 没人会逮捕你。 你就说你是从查理.克尼佩尔那里来的, 关于阿比盖尔。 你会被允许进去的。 重复我刚才说的话。 ";
			link.l1.go = "Drunkard_4";			
		break;
		
		case "Drunkard_4":
			dialog.text = "阿比盖尔是谁? 我认识克尼佩尔... ";
			link.l1 = "这不关你的事。 你知道的越少, 活得越久。 好了, 我等着。 重复。 ";
			link.l1.go = "Drunkard_5";			
		break;
		
		case "Drunkard_5":
			dialog.text = "我从查理.克尼佩尔那里来, 关于呃... .. 阿比盖尔。 就这样。 ";
			link.l1 = "做得好。 完成任务你会得到5000比索。 ";
			link.l1.go = "Drunkard_6";			
		break;
		
		case "Drunkard_6":
			if (makeint(Pchar.money) >= 5000)
			{
				dialog.text = "5000比索? 哦... 。 只送一封信? ";
				link.l1 = "不, 你还会收到另一封信。 你要带着它来酒馆, 坐在这里。 我会从你那里拿走。 别做蠢事, 别害怕 —我会看着你, 离你很近。 拿这笔钱作为预付款, 让你安心点。 ";
				link.l1.go = "Drunkard_7";	
			}
			else
			{
				dialog.text = "五千? 你甚至有这么多钱吗? ";
				link.l1 = "哈! 当然有。 我现在就去拿。 ";
				link.l1.go = "Drunkard_no_money";	
				NextDiag.CurrentNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_no_money":
			dialog.text = "你把五千带来了吗? ";
			if (makeint(Pchar.money) >= 5000)
			{
				link.l1 = "是的。 给你。 别担心。 ";
				link.l1.go = "Drunkard_7";
			}
			else
			{
				link.l1 = "没有。 等等。 我很快回来。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_7":
			AddMoneyToCharacter(pchar, -5000);
			RemoveItems(PChar, "MC_Letter", 1);
			dialog.text = "嗯... 我现在该走了吗, 先生? ";
			link.l1 = "不, 星期四早上... 当然是现在, 你这个笨蛋! 现在喝完你的朗姆酒, 走吧! ";
			link.l1.go = "Drunkard_8";			
		break;
		
		case "Drunkard_8":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-26");
			LAi_SetStayType(npchar);
			LAi_RemoveLoginTime(npchar);//删除加载时间
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "sentjons_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "sentjons_town", "reload", "reload4_back", "DrunkardGoTown", -1);
			chrDisableReloadToLocation = true;//关闭地点
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//防止他逃跑
		break;
		
		case "Drunkard_9":
			DelLandQuestMark(npchar);
			dialog.text = "啊, 你来了, 先生... 我真不该这么做。 理查德读完后勃然大怒, 我以为他会杀了我。 ";
			link.l1 = "但你在这里! 别担心 —他不敢这么做 —那一刻你对他来说非常有价值, 哈哈哈! 你甚至无法想象有多么... ";
			link.l1.go = "Drunkard_10";			
		break;
		
		case "Drunkard_10":
			dialog.text = "我需要喝一杯... 这是他给你的回复。 ";
			link.l1 = "给我! 闭上你的嘴! ";
			link.l1.go = "Drunkard_11";			
		break;
		
		case "Drunkard_11":
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter1");
			AddQuestRecordInfo("FleetwoodAnswer", "1");
			dialog.text = "接下来几天我说话会很困难... 再见... 希望再也不要见到你。 ";
			link.l1 = "放轻松, 老醉鬼, 哈哈哈! 我-们-该-拿-一-个-醉-酒-的-水-手-怎-么-办... 喝一杯, 放松一下 —现在一切都结束了! ";
			link.l1.go = "Drunkard_12";			
		break;
		
		case "Drunkard_12":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-27");
			pchar.questTemp.HWIC.Self = "FleetwoodAgree";
			AddCharacterExpToSkill(pchar, "Sneak", 300);//隐蔽性
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		//邮船的船长
		case "Cureer_abordage":
			dialog.text = "你到底为什么攻击我的船? 我既没有贵重物品也没有钱 —只有文件, 反正对你也没用! ";
			link.l1 = "闭嘴。 你输了, 现在听我说。 我既不需要你的船, 也不需要你的文件。 我需要你把这个口信带给你的老板, 那个卑鄙的老鼠卢卡斯.罗登堡。 告诉他弗利特伍德船长向他问好。 ";
			link.l1.go = "Cureer_abordage_1";			
		break;
		
		case "Cureer_abordage_1":
			dialog.text = "弗利特伍德船长? 但是... ";
			link.l1 = "你会把这封信交给你的老板 —还是我该刺穿你? 我也可以找其他送信的人选。 你知道, 由于无聊, 我每个周末都会抢劫你们公司的船。 ";
			link.l1.go = "Cureer_abordage_2";			
		break;
		
		case "Cureer_abordage_2":
			dialog.text = "好吧, 弗利特伍德先生。 我会送达的。 ";
			link.l1 = "太好了。 现在我们可以道别了, 先生。 你今天算很幸运。 到达后别忘了去教堂! ";
			link.l1.go = "Cureer_abordage_3";			
		break;
		
		case "Cureer_abordage_3":
			DialogExit();
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			pchar.quest.HWICCureer_AfterBattle.over = "yes";
			pchar.quest.HWICCureerOnMapOver.over = "yes";
			AddQuestRecord("Holl_Gambit", "3-39");
			Log_TestInfo("信件已送达! ");
			RemoveItems(PChar, "MC_Letter", 1);
			pchar.questTemp.HWIC.Self = "LetterToLucasSent";
			pchar.quest.Curacao_exploring.win_condition.l1 = "location";
			pchar.quest.Curacao_exploring.win_condition.l1.location = "Curacao";
			pchar.quest.Curacao_exploring.function = "CuracaoExploring";
			DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
			AddComplexSeaExpToScill(50, 50, 50, 100, 50, 50, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		//监狱里的马蒂亚斯.贝克
		case "MatiasBek"://以防玩家想聊天
			dialog.text = "我是被非法逮捕的! 我和英国人没有任何联系! 这些都是罗登堡的阴谋。 没关系。 彼得.施托伊弗桑特很快就会到达 —他会把一切都弄清楚的! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "MatiasBek";
		break;
		
		//官邸入口的守卫
		case "QuestGuard":
			dialog.text = "卢卡斯.罗登堡先生现在不想见任何人。 请马上离开官邸。 ";
			link.l1 = "嗯。 我明白了。 我一周后再来... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "QuestGuard";		
		break;
		
		//彼得.施托伊弗桑特
		case "Stivesant":
			dialog.text = "我们要去官邸, 船长。 我已经派我的人去堡垒了解马蒂亚斯.贝克的情况。 如果他现在真的在监狱里, 他一定已经被释放并护送到镇上了。 跟我来! ";
			link.l1 = "好的, 施托伊弗桑特先生。 ";
			link.l1.go = "Stivesant_1";			
		break;
		
		case "Stivesant_1":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Villemstad_townhall", "goto", "goto2", "OpenVillemstadResidence", -1);
		break;
		
		case "ArestLucas_1":
			dialog.text = "卢卡斯! 这里发生了什么? 马蒂亚斯.贝克在哪里? 你真的把他送进监狱了吗? ";
			link.l1 = "";
			link.l1.go = "ArestLucas_2";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_2":
			StartInstantDialog("Lucas", "ArestLucas_3", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_3":
			dialog.text = "你好, 施托伊弗桑特先生。 我有证据证明他与英国情报部门有联系, 并且直接与弗利特伍德船长有关。 他通风报信给那个该死的英国人, 让其攻击我们的邮船, 以获取公司的机密信件。 ";
			link.l1 = "";
			link.l1.go = "ArestLucas_4";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_4":
			StartInstantDialog("Stivesant", "ArestLucas_5", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_5":
			dialog.text = "你从哪里得到的这个信息? ";
			link.l1 = "";
			link.l1.go = "ArestLucas_6";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_6":
			StartInstantDialog("Lucas", "ArestLucas_7", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_7":
			dialog.text = "这是邮船船长说的。 理查德.弗利特伍德登上了他的船, 拿走了他的文件; 然后船被释放了。 除了我。 你和马蒂亚斯.贝克, 没有人知道路线或时间表。 ";
			link.l1 = "";
			link.l1.go = "ArestLucas_8";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
		break;
		
		case "ArestLucas_8":
			StartInstantDialog("Stivesant", "ArestLucas_9", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_9":
			dialog.text = "这就是为什么你认为贝克通风报信给弗利特伍德攻击邮船? 什么垃圾! 弗利特伍德是个普通海盗; 他只攻击商船。 他为什么需要那些文件, 顺便说一下, 里面只包含记账信息? ";
			link.l1 = "";
			link.l1.go = "ArestLucas_10";		
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_10":
			StartInstantDialog("Lucas", "ArestLucas_11", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_11":
			dialog.text = "先生, 邮船还运送了其他重要的公司文件 —不只是通常的报告。 现在它们都在英国人手里。 这就是为什么我决定逮捕贝克。 ";
			link.l1 = "";
			link.l1.go = "ArestLucas_12";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_12":
			StartInstantDialog("Stivesant", "ArestLucas_13", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_13":
			dialog.text = "该死! 这是真正的权力篡夺! 你有没有意识到你在做什么, 卢卡斯? 邮船船长在哪里? ";
			link.l1 = "";
			link.l1.go = "ArestLucas_14";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_14":
			StartInstantDialog("Lucas", "ArestLucas_15", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_15":
			dialog.text = "他去菲利普斯堡了, 先生。 ";
			link.l1 = "";
			link.l1.go = "ArestLucas_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_16":
			StartInstantDialog("Stivesant", "ArestLucas_17", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_17":
			dialog.text = "好吧, 那么。 我已经下令释放贝克。 他会被带到这里, 然后我们三个人谈谈。 ";
			link.l1 = "";
			link.l1.go = "ArestLucas_18";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_18":
			StartInstantDialog("Lucas", "ArestLucas_19", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_19":
			dialog.text = "好吧, 我不介意。 我们三个人 —好的。 谈谈吧。 ";
			link.l1 = "";
			link.l1.go = "ArestLucas_20";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_20":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "governor1", "DoubleTalkWithLucas", -1.0);
			locCameraFromToPos(4.70, 2.92, -4.19, false, 3.60, -0.70, 5.00);
			DoQuestCheckDelay("PiterTalkWithLucas_2", 4.5);
		break;
		
		case "ArestLucas_40":
			dialog.text = "你会为你的无法无天付出代价, 罗登堡! 你的指控是荒谬的。 你甚至不让我见邮船船长! 你没有提出任何证据, 所有指控都来自你个人。 \n我向上帝发誓, 我是无辜的! 我现在和过去都没有与英国人有任何接触! ";
			link.l1 = "";
			link.l1.go = "ArestLucas_41";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_41":
			StartInstantDialog("Lucas", "ArestLucas_42", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_42":
			dialog.text = "哦, 真的吗? 那么弗利特伍德是怎么知道我们的邮船, 并且知道她不仅载有通常的文件? ";
			link.l1 = "";
			link.l1.go = "ArestLucas_43";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Villemstad_Mayor"));
		break;
		
		case "ArestLucas_43":
			dialog.text = "... ";
			link.l1 = "罗登堡在撒谎。 理查德.弗利特伍德不可能攻击邮船。 ";
			link.l1.go = "ArestLucas_44";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			sld = characterFromId("Stivesant");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			sld = characterFromId("Villemstad_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "ArestLucas_44":
			dialog.text = "你是谁, 先生? 你凭什么做出这样的陈述? ";
			link.l1 = "我叫" +GetFullName(pchar)+ "。 我亲自设陷阱除掉了弗利特伍德船长。 他的尸体正在特克斯海岸被海鸥吃掉。 官员们未能保护我们荷兰商人免受他的侵略, 所以我自己解决了他。 而这发生在邮船被抢劫之前... ";
			link.l1.go = "ArestLucas_46";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "ArestLucas_46":
			dialog.text = "";
			link.l1 = "弗利特伍德根本不可能这么做, 他已经死了。 我从酒馆里的当地人那里得知马蒂亚斯.贝克被逮捕了, 所以我决定调查此事, 因为我一直认为贝克先生是个声誉清白的人... ";
			link.l1.go = "ArestLucas_47";			
		break;
		
		case "ArestLucas_47":
			dialog.text = "";
			link.l1 = "港口的人告诉我, 你在你的双桅船上装载了各种罪犯和雇佣兵, 公司的卫兵被留在了岸上。 我跟踪你的船并俘获了她, 杀死了你雇佣的每一个恶棍。 我审问了朗威船长, 作为交换他的自由, 他告诉了我一切, 罗登堡先生... ";
			link.l1.go = "ArestLucas_48";			
		break;
		
		case "ArestLucas_48":
			dialog.text = "";
			link.l1 = "你计划夺取库拉索岛的权力, 并命令朗威击沉施托伊弗桑特先生的大帆船。 了解你的手段, 我确信邮船的可怜船长已经死了。 你一定是组织了对邮船的袭击, 以便制造一个先例, 对吗? 而这一行为是由你的刺客雅各布.范伯格执行的? 朗威告诉了我很多关于那个人的事情。 ";
			link.l1.go = "ArestLucas_49";			
		break;
		
		case "ArestLucas_49":
			dialog.text = "这... 这是公然的谎言! 你在说什么, 先生? 你到底是谁? ";
			link.l1 = "我是一个独立船长, 想清除海上和陆地上的那个恶棍弗利特伍德, 并卷入了你的政治阴谋! 我警告过施托伊弗桑特先生他面临的危险。 我来这里是为了和合法当局一起结束你在库拉索岛的掠夺! ";
			link.l1.go = "ArestLucas_50";			
		break;
		
		case "ArestLucas_50":
			dialog.text = "多么无礼! 你会为你的话付出代价的, ‘独立船长’先生! 你... ";
			link.l1 = "";
			link.l1.go = "ArestLucas_51";
		break;
		
		case "ArestLucas_51":
			StartInstantDialog("Stivesant", "ArestLucas_52", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_52":
			dialog.text = "够了, 卢卡斯。 你会为你的罪行付出代价的! 我听够了, 也看够了。 卢卡斯.罗登堡, 我以企图谋杀公司董事。 企图以武力夺权和涉嫌谋杀邮船船长的罪名逮捕你。 \n此外, 我相信在正式调查期间, 我们会发现更多关于你生平的有趣部分。 你将被拘留并送往阿姆斯特丹, 在那里你将被起诉。 把他带走! ";
			link.l1 = "";
			link.l1.go = "ArestLucas_53";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromID("Stivesant"));					
		break;
		
		case "ArestLucas_53":
			StartInstantDialog("Lucas", "ArestLucas_54", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_54":
			dialog.text = "但是... ";
			link.l1 = "";
			link.l1.go = "ArestLucas_55";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_55":
			DialogExit();
			LAi_ActorTurnToCharacter(pchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetImmortal(sld, true);//防止作弊
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "LucasGoToPrison", -1);
			for (i=3; i<=5; i++)
			{
			sld = characterFromId("StivesantGuard_"+i);
			LAi_ActorFollow(sld, characterFromID("Lucas"), "", -1);
			}
			LAi_SetActorType(PChar);
			locCameraFromToPos(4.70, 2.92, -4.19, false, -4.60, -1.70, 5.50);
			DoQuestFunctionDelay("SecondDayInVillemstad", 6.0);
		break;
		
		case "Stivesant_10":
			dialog.text = "" + GetFullName(pchar) + "船长! 我代表威廉斯塔德殖民地行政当局, 请接受我们对你的真诚感谢, 感谢你帮助我们逮捕了那个危险的罪犯。 我也想亲自感谢你, 因为我可能欠你一条命。 ";
			link.l1 = "我是为了所有荷兰殖民地的利益而行动, 先生。 ";
			link.l1.go = "Stivesant_11";			
		break;
		
		case "Stivesant_11":
			dialog.text = "你的谦逊值得尊敬, 我的朋友。 现在我想处理一些正式手续: 既然你夺取‘美凤号’只是为了正当目的和在危急情况下, 不会有任何索赔。 但这艘船属于公司, 我恳请你归还她。 ";
			link.l1 = "当然, 先生。 ";
			link.l1.go = "Stivesant_12";			
		break;
		
		case "Stivesant_12":
		//删除美凤号
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//删除任务船属性
		if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
		{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "A boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);//让其乘坐小帆船
		}
		else
		{
			for(i = 1; i < COMPANION_MAX; i++)
			{
			int iTemp = GetCompanionIndex(PChar, i);
			if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
					{
						pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
						sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
						RemoveCharacterCompanion(PChar, sld);
						AddPassenger(PChar, sld, false);
					}
				}
			}
		}
			dialog.text = "请明天到我的住所来 —你将代表自由省共和国, 因其最符合国家利益的行为而获得奖励。 我恳请你不要离开城镇。 ";
			link.l1 = "好的, 先生。 我明天会来。 ";
			link.l1.go = "Stivesant_13";			
		break;
		
		case "Stivesant_13":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.dialog.currentnode = "Bek_2";
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "Bek_2":
			dialog.text = "船长, 我也想亲自感谢你, 感谢你的进取精神和及时帮助。 别忘了明天来这里, 我会为你准备一份珍贵的礼物。 ";
			link.l1 = "谢谢你, 贝克先生。 我会去的! ";
			link.l1.go = "Bek_3";			
		break;
		
		case "Bek_3":
			DialogExit();
			pchar.quest.Award_FromPiter.win_condition.l1 = "Timer";
			pchar.quest.Award_FromPiter.win_condition.l1.date.hour  = 9.0;
			pchar.quest.Award_FromPiter.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Award_FromPiter.function = "OpenResidenceDoor";
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload5_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload10_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload3_back", true);//关闭住所入口
			LocatorReloadEnterDisable("Villemstad_town", "reloadR2", true);//关闭住所侧门入口
			AddQuestRecord("Holl_Gambit", "3-53");
			DoQuestReloadToLocation("Villemstad_prison", "goto", "goto23", "TalkWithLucasPrisoner");
			for (i=4; i<=5; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//清理士兵
			}
		break;
		
		case "Stivesant_14":
			dialog.text = "" +GetFullName(pchar)+ ", 代表自由省共和国, 特此授予你个人武器和10万比索奖金, 以表彰你主动消灭所有荷兰人民的敌人。 国家罪犯理查德.弗利特伍德的行为。 恭喜! ";
			link.l1 = "谢谢你, 司徒维桑特先生! ";
			link.l1.go = "Stivesant_15";			
		break;
		
		case "Stivesant_15":
			dialog.text = "此外, 鉴于你空前的勇气。 揭露公司内部的叛逆阴谋以及冒险抓获公司前副总裁的行动, 再授予你15万比索。 你还将被允许与荷兰西印度公司签订合同\n我相信我们的新副董事将为像你这样勇敢的船长找到一份高薪工作。 ";
			link.l1 = "谢谢! 我会记住的。 ";
			link.l1.go = "Stivesant_16";			
		break;
		
		case "Stivesant_16":
			AddMoneyToCharacter(pchar, 250000);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition 使用GetGeneratedItem, 否则从数组第一部分获取一堆相同的剑
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "请注意, 只要你站在荷兰一边并为荷兰利益行事, 在任何交易中你都可以一直指望我的帮助。 现在让我们听听威廉斯塔德总督马蒂亚斯.贝克想说什么。 ";
			link.l1 = "";
			link.l1.go = "Stivesant_17";			
		break;
		
		case "Stivesant_17":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "Bek_4";
			LAi_ActorDialog(sld, pchar, "", -1, 0);		
		break;
		
		case "Bek_4":
			dialog.text = "船长, 我对你发现反国家阴谋的勇气和洞察力表示诚挚的感谢。 我想向你赠送这件珍贵的导航仪器, 这对任何战舰上的人来说都是无价之宝。 ";
			link.l1 = "谢谢你, 贝克先生";
			link.l1.go = "Bek_5";			
		break;
		
		case "Bek_5":
			GiveItem2Character(pchar, "bussol");
			dialog.text = "我想让你知道: 你现在是我的朋友, 这意义重大。 你在我的住所永远是受欢迎的客人。 随时因任何原因过来 —我很乐意提供你可能需要的任何帮助。 ";
			link.l1 = "听到这个我很高兴, 先生! ";
			link.l1.go = "Bek_6";			
		break;
		
		case "Bek_6"://整顿城市
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-54");
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetHuberStayType(sld);
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//清理士兵
			}
			sld = characterFromId("Stivesant");
			LAi_ActorGoToLocator(sld, "goto", "goto6", "StivesantSitDown", -1);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//运气
			DelMapQuestMarkCity("Villemstad");
		break;
		
		case "Bek_7":
			dialog.text = "荷兰为你感到骄傲, 先生。 像你这样的船长是荷兰舰队在加勒比海的支柱。 给你, 请接受你的奖励。 ";
			link.l1 = "谢谢你, 先生。 能为荷兰服务我很荣幸! ";
			link.l1.go = "Bek_8";
		break;
		
		case "Bek_8":
			TakeNItems(pchar, "gold_dublon", 1000);
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			ChangeCharacterNationReputation(pchar, HOLLAND, 20);
			DialogExit();
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "LucasAward_2";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Stivesant_18":
			dialog.text = "很高兴见到你。 你好吗? ";
			link.l1 = "我很好。 我只是顺道来看看你。 ";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Stivesant_18";
		break;
		
		// Jason 悬赏
		case "Stivesant_19":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "看看这是谁! 是" +GetFullName(pchar)+ "。 我们最近派了猎头, 他们不得不把你带到这里来。 而这项服务确实花费了很多。 ";
				link.l1 = "嗯... 我该走了... ";
				link.l1.go = "arest";
				break;
			}
			// belamour legendary edition 修复对装备制服和火枪的检查
			if (pchar.questTemp.Patria == "epizode_4" && IsUniformEquip())
			{
				dialog.text = "你是法国海军的船长吗? 好的, 我时间不多, 但我会听听你要说什么。 什么风把你吹来了? ";
				link.l1 = "司徒维桑特先生, 我从圣克里斯托弗来, 带来了法国殖民地总督德.波因西骑士的口信。 ";
				link.l1.go = "Stivesant_20";
			}
			else
			{
				dialog.text = "抱歉, 船长, 但我现在非常忙, 不能给你足够的时间。 和马蒂亚斯.贝克先生谈谈, 让他听听你要说的话。 ";
				link.l1 = "嗯... ";
				link.l1.go = "Stivesant_19_1";
			}
		break;
		
		case "Stivesant_19_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
		break;
		
		case "Stivesant_20":
			sld = characterFromId("Patria_FlautCap");
			dialog.text = "从德.波因西骑士那里来的? 绝对没想到会这么快... 咳... 骑士怎么样了? ";
			link.l1 = "一切都好, 先生。 德.波因西先生命令我把这封信交给你。 我的另一项任务是护送载有给贵公司货物的‘"+sld.ship.name+"’到威廉斯塔德港。 船只在码头, 货物没有损坏。 ";
			link.l1.go = "Stivesant_21";
		break;
		
		case "Stivesant_21":
			dialog.text = "为我们公司运送货物的船队? 很有趣... 还有信呢, 船长? ";
			link.l1 = "在这里。 请拿去吧。 ";
			link.l1.go = "Stivesant_22";
		break;
		
		case "Stivesant_22":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "嗯... (阅读中) 。 来自宗主国的检查... 咳... 嗯, 好吧... 很有趣, 呵呵... 顺便说一句, 船长, 我听说法国在加勒比海与西班牙交战? 围攻和洗劫圣何塞堡垒, 在古巴东海岸摧毁西班牙战舰中队... ";
			link.l1 = "在太子港附近的伊斯帕尼奥拉岛西海岸, 先生。 围攻圣何塞的唯一目的是从西班牙人那里获得他们袭击圣皮埃尔的经济补偿。 我们与西班牙的关系不好已经有一段时间了... 我什么时候回来取回信? ";
			link.l1.go = "Stivesant_23";
		break;
		
		case "Stivesant_23":
			dialog.text = "我不耽误你了, 船长, 你是军人, 可能有很多事务, 而且我相信骑士急切地等待你的归来。 请在这里, 在客厅等两个小时, 直到我写完给那封信的回复。 请坐在这里休息, 如果你愿意, 会为你提供葡萄酒或朗姆酒... ";
			link.l1 = "我很感激, 先生, 我更喜欢一杯美酒... ";
			link.l1.go = "Stivesant_24";
		break;
		
		case "Stivesant_24":
			chrDisableReloadToLocation = true;//关闭地点
			pchar.quest.Patria_CureerTimeOver.over = "yes"; //移除计时器
			pchar.quest.Patria_CureerFail.over = "yes"; //移除中断
			sld = characterFromId("Patria_FlautCap");
			RemoveCharacterCompanion(pchar, sld);
			sld.lifeday = 0;
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_25";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "Patria_StivesantWait", -1);
			pchar.questTemp.Patria = "epizode_4_return";
		break;
		
		case "Stivesant_25":
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_2");
			dialog.text = "给德.波因西先生的回信准备好了。 给, 请拿去吧... 祝你好运, 船长。 ";
			link.l1 = "谢谢你, 先生。 再见! ";
			link.l1.go = "Stivesant_26";
		break;
		
		case "Stivesant_26":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
			chrDisableReloadToLocation = false;
			AddQuestRecord("Patria", "23");
			SetFunctionTimerCondition("Patria_CureerBackOver", 0, 0, 31, false);
		break;
		
		case "Stivesant_27":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "看看这是谁! 是" +GetFullName(pchar)+ "。 我们最近派了猎头, 他们不得不把你带到这里来。 而这项服务确实花费了很多。 ";
				link.l1 = "嗯... 我该走了..";
				link.l1.go = "arest";
				break;
			}
			if (pchar.questTemp.Patria == "epizode_6" && IsUniformEquip())
			{
				dialog.text = "你又带着菲利普.德.波因西总督的口信来了, 不是吗? ";
				link.l1 = "是的, 司徒维桑特先生。 在圣马丁岛海岸发生了一个不愉快的误会 —一艘载有来自巴黎的检查员诺埃尔.福盖男爵的船只被菲利普斯堡堡垒炮击了, 并且... ";
				link.l1.go = "Stivesant_28";
			}
			else
			{
				dialog.text = "抱歉, 船长, 但我现在非常忙, 不能给你足够的时间。 和马蒂亚斯.贝克先生谈谈, 让他听听你要说的话。 ";
				link.l1 = "嗯... ";
				link.l1.go = "Stivesant_27_1";
			}
		break;
		
		case "Stivesant_27_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_27";
		break;
		
		case "Stivesant_28":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "这就是你来这里的原因, 船长。 我不会进行外交讨论: 告诉骑士, 他不再负责圣马丁岛了。 他做得够多了。 关于宗主国的检查 —让他想办法吧, 德.波因西把一切颠倒过来从来都不难。 ";
				link.l1 = "这就是我应该告诉他的吗? ";
				link.l1.go = "Stivesant_29";
			}
			else
			{
				dialog.text = "这就是你来这里的原因, 船长。 我不会进行外交讨论: 你的君主最近在圣马丁岛太贪婪了, 所以是时候抑制他无法满足的欲望了。 而且我相信他完全明白这一点。 对于你, 查尔斯.德.莫尔船长, 我们也有关于最近与名叫理查德.弗利特伍德的英国强盗有关事件的问题, 所以你将不得不在这里待一段时间。 \n中士! 拿走船长的武器, 把他带到指挥官办公室! ";
				link.l1 = "扣留一名执行任务的法国军官是不可接受的! ";
				link.l1.go = "Stivesant_31";
			}
		break;
		
		case "Stivesant_29":
			dialog.text = "我自己也不能说得更好了, 船长。 你的指挥官会明白一切, 但你不需要深入了解, 那不会改变任何事情。 祝你一切顺利。 中士, 把查尔斯.德.莫尔先生带到出口! ";
			link.l1 = "... ";
			link.l1.go = "Stivesant_30";
		break;
		
		case "Stivesant_30":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload3", "Patria_DiplomatGetOut");
		break;
		
		case "Stivesant_31":
			dialog.text = "不幸的是, 我有不同的看法。 中士! 如果遇到抵抗, 就使用武力! ";
			link.l1 = "你只是还不知道你在和谁打交道, 先生... ";
			link.l1.go = "Stivesant_32";
		break;
		
		case "Stivesant_32":
			DialogExit();
			Patria_DiplomatFight();
		break;
		
		case "Stivesant_33":
			dialog.text = "查尔斯.德.莫尔船长, 看到你扮演这个角色有点奇怪... 我希望你能保证来和你谈判的人的豁免权。 ";
			link.l1 = "你可以相信这一点, 司徒维桑特先生。 ";
			link.l1.go = "Stivesant_34";
		break;
		
		case "Stivesant_34":
			dialog.text = "那么, 你能给我一个机会阅读你准备的协议吗? 据我了解, 它包含信中的内容? ";
			link.l1 = "正是如此, 先生, 只是以正式形式。 法国方面 —恢复关系至中立, 放弃对圣马丁岛的任何主张。 英国方面 —结束贸易战。 细节都在这里描述... 当然, 还有因你方发起的军事行动而给我们造成损失的经济补偿。 ";
			link.l1.go = "Stivesant_35";
		break;
		
		case "Stivesant_35":
			dialog.text = "请把文件给我。 ";
			link.l1 = "当然。 ";
			link.l1.go = "Stivesant_36";
		break;
		
		case "Stivesant_36":
			dialog.text = "... (阅读中)... ";
			link.l1 = "... ";
			link.l1.go = "Stivesant_37";
		break;
		
		case "Stivesant_37":
			LAi_Fade("", "");
			dialog.text = "既然你没有给我选择, 我就签署这份协议。 但对我来说, 保护威廉斯塔德及其居民是最重要的。 ";
			link.l1 = "那么我们将用签名验证所有三份副本。 我受菲利普.德.波因西总督授权代表法国方面签署文件, 多伊利上校将代表英国签署。 ";
			link.l1.go = "Stivesant_38";
		break;
		
		case "Stivesant_38":
			dialog.text = "... (签名中)... ";
			link.l1 = "完美! 现在我们应该签这个... ";
			link.l1.go = "Stivesant_39";
		break;
		
		case "Stivesant_39":
			LAi_Fade("", "");
			dialog.text = "那么, 我相信你现在会解除围困吧? ";
			link.l1 = "毫无疑问。 我希望协议的所有条款都将被荷兰方面遵守, 不出现违约情况。 ";
			link.l1.go = "Stivesant_40";
		break;
		
		case "Stivesant_40":
			dialog.text = "如果英国或法国没有违约, 那么我们将遵守合同条款, 不用担心。 ";
			link.l1 = "贸易总是比战争好, 司徒维桑特先生。 现在你可以安全返回威廉斯塔德了。 围困将解除, 我们的中队很快将离开库拉索水域。 ";
			link.l1.go = "Stivesant_41";
		break;
		
		case "Stivesant_41":
			DialogExit(); // 司徒维桑特离开, 多伊利靠近
			Patria_CuracaoStivesantGo();
		break;
		
		case "Stivesant_42":
			dialog.text = "那么, 你是诺埃尔.福盖男爵吗? 嗯, 你一定是查尔斯.德.莫尔先生本人! 问候你, 舰队副司令! 你被称为群岛上最狡猾的策划者是有原因的 —人们可能永远不知道你目前站在谁的一边... ";
			link.l1 = "目前, 舰队副司令 站在国王和您真诚的, 他的授权代表一边。 ";
			link.l1.go = "Stivesant_43";
		break;
		
		case "Stivesant_43":
			dialog.text = "国王离这里很远, 法国也是, 男爵, 但圣克里斯托弗和德.波因西骑士很近。 他是法国殖民地的真正主人。 事实上... 然而, 你是来这里获取任何在财政部长眼中损害德.波因西形象的东西的吗? ";
			link.l1 = "正是如此, 先生。 ";
			link.l1.go = "Stivesant_44";
		break;
		
		case "Stivesant_44":
			dialog.text = "我有这样的文件。 这是一本完整的账簿, 记录了我和德.波因西在矿山和其他一些事务上的账目。 里面还有一大堆与这笔生意相关的文件, 带有菲利普.德.波因西的个人签名。 我向你保证, 这些文件的内容落在感兴趣的人手中, 将使骑士比加勒比海的海底陷得更深。 ";
			link.l1 = "你想要这本账簿换什么? ";
			link.l1.go = "Stivesant_45";
		break;
		
		case "Stivesant_45":
			dialog.text = "我以很低的价格出售它。 仅仅一百万比索的白银。 ";
			link.l1 = "一百万比索? !!";
			link.l1.go = "Stivesant_46";
		break;
		
		case "Stivesant_46":
			dialog.text = "没错, 男爵。 这笔钱将至少部分弥补最近战争造成的损失。 我给你一个建议: 去找查尔斯.德.莫尔先生。 在他为德.波因西和嗯... 其他人服务期间, 他可能发了大财, 得到一百万对他来说不是问题。 我几乎可以肯定。 \n我给你一个期限 - 一个月。 如果这个时间过后你没有带来指定的金额, 我会给骑士写一封信, 描述你拜访我的细节。 你可以猜到接下来会发生什么。 ";
			link.l1 = "你在敲诈我! 你必须明白, 我在殖民地不可能有一百万! ";
			link.l1.go = "Stivesant_47";
		break;
		
		case "Stivesant_47":
			dialog.text = "我当然明白。 因此, 我立即向你指出拥有这一百万的人。 如果德.莫尔先生拒绝, 男爵, 你最好在骑士收到我的信之前航行到欧洲, 否则你有可能永远留在这里。 至于德.莫尔先生... 当然, 他会失去他的舰队司令军衔, 但他会摆脱... 也许甚至用他的方法摆脱德.波因西, 我对此完全没问题。 \n好吧, 先生们, 你们听到了我的话。 我将在一个月后在我的住所等待你们带着一百万来。 保证自由进出。 ";
			link.l1 = "... ";
			link.l1.go = "Stivesant_48";
		break;
		
		case "Stivesant_48":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			locCameraTarget(pchar);
			locCameraFollow();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;
			sld = CharacterFromID("Noel");
			sld.dialog.currentnode = "noel_84";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			sld = CharacterFromID("Stivesant");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Patria_CondotierStivesantInHall", 12.0);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("Stivesant_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			}
		break;
		
		case "Stivesant_49":
			if (sti(pchar.money) >= 1000000)
			{
				dialog.text = "我甚至没有怀疑, 查尔斯.德.莫尔舰队副司令, 你会给我带来这笔钱。 也许, 我甚至向你要得太少了, 但哦, 好吧... 男爵只是你下一盘棋中的一个棋子, 对吗? 军衔和金钱对你来说还不够, 现在你想取代德.波因西的位置, 对吗? 你必须承认, 对于法国殖民地总督的职位来说, 一百万是一笔小数目! 考虑到你铁腕手段, 你将在几个月内收回这笔钱。 ";
				link.l1 = "拿上你的一百万, 先生。 我想收到我承诺的账簿。 ";
				link.l1.go = "Stivesant_50";
			}
			else
			{
				dialog.text = "你最好集中精力筹集一百万, 先生, 而不是把时间浪费在无意义的访问上。 ";
				link.l1 = "... ";
				link.l1.go = "Stivesant_49_1";
			}
		break;
		
		case "Stivesant_49_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_49";
		break;
		
		case "Stivesant_50":
			pchar.quest.Patria_CondotierStivesantTimeOver.over = "yes"; // 移除计时器
			AddMoneyToCharacter(pchar, -1000000);
			GiveItem2Character(pchar, "Reserve_item_01");
			ref itm = ItemsFromID("Reserve_item_01");
			itm.picIndex = 15;
			itm.picTexture = "ITEMS_26";
			itm.price = 0;
			itm.Weight = 2.0;
			itm.name = "itmname_Reserve_item_01_1";
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_4");
			dialog.text = "当然, 舰队副司令。 不要皱眉: 当你成为总督时, 你会看到荷兰西印度贸易公司是比贪婪好战的英国人更有利可图的商业伙伴。 你不知道如果给一个英国人一根手指, 他会拿走整个手吗? 如果不知道, 你会吃尽苦头学到的。 所以我还不是在和你告别。 保留你的文件。 我希望你的男爵有足够的能力击败骑士。 ";
			link.l1 = "谢谢。 再见, 司徒维桑特先生。 ";
			link.l1.go = "Stivesant_51";
		break;
		
		case "Stivesant_51":
			DialogExit();
			AddQuestRecord("Patria", "84");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			pchar.quest.Patria_CondotierCabin.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCabin.win_condition.l1.location = "Curacao";
			pchar.quest.Patria_CondotierCabin.function = "Patria_CondotierCabin";
		break;
		
		case "vanberg_sold":
			dialog.text = "哈哈哈! 看看这个! 雅各布一如既往是对的 —这只狐狸来岛上是有充分理由的。 看来箱子里有相当多的金子。 你一个人来这里太粗心了, 伙计。 但话说回来, 这让我们的工作变得更容易了! ";
			link.l1 = "这些人渣跟踪我到了这里! 我没料到... 但我不会轻易成为猎物! ";
			link.l1.go = "vanberg_sold_1";			
		break;
		
		case "vanberg_sold_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//允许战斗
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("vanberg_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareMassakraInShore");
			AddDialogExitQuest("MainHeroFightModeOn");			
		break;
		
		case "Abihouselady":
			dialog.text = "你在找人吗? ";
			link.l1 = "是的。 所罗门和阿比盖尔.施努尔在哪里? ";
			link.l1.go = "Abihouselady_1";			
		break;
		
		case "Abihouselady_1":
			dialog.text = "他们不再住在这里了。 他们根本住不起这个地方。 可怜的女孩阿比盖尔在总督家当仆人。 她每天努力工作, 为自己和父亲谋生。 所罗门每天都在酒馆喝酒, 他无法承受发生在他们身上的事情。 他们现在住在海边的一个小屋里... ";
			link.l1 = "哦... 好的, 谢谢你提供的信息。 我得走了。 ";
			link.l1.go = "Abihouselady_2";
		break;
		
		case "Abihouselady_2":
			DialogExit();
			NextDiag.CurrentNode = "Abihouselady_3";
		break;
		
		case "Abihouselady_3":
			dialog.text = "你还想知道什么, 先生? ";
			link.l1 = "没什么, 没关系。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abihouselady_3";
		break;
		
		//任务失败时删除美凤号
		case "TempOffGuard":
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//删除任务船属性
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "A boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);//让其乘坐小帆船
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
						iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			dialog.text = "船长, 你挪用了荷兰西印度公司的一艘船。 我被授权没收它, 并在遇到抵抗时使用武力。 这是彼得.司徒维桑特的命令。 ";
			link.l1 = "好吧, 如果这是彼得.司徒维桑特本人的命令... 我不会因为一艘船与荷兰开战。 拿去吧。 ";
			link.l1.go = "TempOffGuard_1";			
		break;
		
		case "TempOffGuard_1":
			dialog.text = "你表现出理智很好。 ";
			link.l1 = "... ";
			link.l1.go = "TempOffGuard_2";
		break;
		
		case "TempOffGuard_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//打开地点
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");
		break;
		
		// Jason 悬赏
		case "arest":
			dialog.text = "当然是时候离开了, 你甚至会有人陪同。 卫兵! 抓住他! ";
			link.l1 = "试试看! ";
		    link.l1.go = "fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_LockFightMode(Pchar, true); // 用脚逃跑
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Attack(NPChar, Pchar); // 对不朽的市长不起作用 :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // 幽灵士兵
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		//关于公民类型角色发现武器外露的说明
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar, "嘿, 听着! 作为这个城镇的公民, 我恳请你不要带着出鞘的刀刃四处走动。 ", "你知道, 作为这个城镇的公民, 我恳请你不要带着出鞘的刀刃四处走动。 ");
			link.l1 = LinkRandPhrase("好的。 ", "好吧。 ", "如你所说... ");
			link.l1.go = "exit";
		break;
	}
}