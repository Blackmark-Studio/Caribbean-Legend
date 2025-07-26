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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "你需要什么? ";
			link.l1 = "没什么。 ";
			link.l1.go = "exit";
		break;
		
		case "dwh_gypsy_0":
			dialog.text = "... ";
			link.l1 = "听着, 黑眉毛的, 我听说你能给人治病, 甚至是重病。 是真的吗? ";
			link.l1.go = "dwh_gypsy_1";
			DelLandQuestMark(npchar);
		break;
		
		case "dwh_gypsy_1":
			dialog.text = "是真的, "+GetSexPhrase("亲爱的","美人")+"。 我有自己的办法对付各种疾病。 我帮助过平民。 商人, 甚至让富人重新站起来。 就连总督在无人能帮时也求助过我的药水。 疾病不惧黄金, 但无法抗拒我的疗法。 ";
			link.l1 = "那你为什么拒绝治疗重病的女孩, 托马斯.莫里森的女儿? ";
			link.l1.go = "dwh_gypsy_2";
			pchar.questTemp.DWH_gipsy = true;
		break;
		
		case "dwh_gypsy_2":
			dialog.text = "谁告诉你这种废话的, "+GetSexPhrase("小猎鹰","小鸽子")+"? 我没有拒绝帮助。 是她父亲把我从家里赶了出去。 我们原本约定我来治疗她, 他却突然改变主意, 把我像死敌一样扔了出来。 ";
			link.l1 = "所以他亲手判了女儿受苦? ";
			link.l1.go = "dwh_gypsy_2_1";
		break;
		
		case "dwh_gypsy_2_1":
			dialog.text = "不, 不, 他是个慈爱的父亲。 很难想象他为什么会那样做。 ";
			link.l1 = "你试过再和他谈谈吗? ";
			link.l1.go = "dwh_gypsy_3";
		break;
		
		case "dwh_gypsy_3":
			dialog.text = "他甚至不让我靠近房子。 听着, "+GetSexPhrase("亲爱的","美人")+", 既然你关心一个可怜女孩的命运, 也许你可以试着弄清楚怎么回事? 和托马斯谈谈, 帮我把孩子从苦难中救出来。 ";
			link.l1 = "我当然会帮忙。 我在哪里能找到托马斯? ";
			link.l1.go = "dwh_gypsy_4";
			link.l2 = "不, 黑眉毛的。 不管怎样, 我相信她父亲拒绝你的帮助有他的理由。 我不会卷入其中。 让他决定吧 --她是他的女儿。 ";
			link.l2.go = "dwh_gypsy_otkaz";
		break;
		
		case "dwh_gypsy_otkaz":
			DialogExit();
			CloseQuestHeader("DWH");
		break;
		
		case "dwh_gypsy_4":
			dialog.text = "他们的房子在城墙边, 小镇北部, 挨着一座有圆柱的豪宅。 去吧, "+GetSexPhrase("小猎鹰","小鸽子")+", 和他谈谈, 然后回来找我。 ";
			link.l1 = "我很快回来。 ";
			link.l1.go = "dwh_gypsy_5";
		break;
		
		case "dwh_gypsy_5":
			DialogExit();
			
			AddQuestRecord("DWH", "2");
			
			sld = CharacterFromID("DWH_gypsy");
			sld.dialog.currentnode = "dwh_gypsy_repeat";
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_Tomas", "citiz_13", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "托马斯";
			sld.lastname = "莫里森";
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas";
			ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "goto", "goto1");
			sld.City = "SentJons";
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "dwh_gypsy_repeat":
			dialog.text = "那么, "+GetSexPhrase("亲爱的","甜心")+", 你和托马斯谈过了吗? ";
			link.l1 = "还没有。 ";
			link.l1.go = "dwh_exit";
		break;

		case "dwh_exit":
			DialogExit();
			NextDiag.TempNode = "dwh_gypsy_repeat";
		break;
		
		case "Tomas":
			dialog.text = ""+TimeGreeting()+"! 什么风把你吹到我家来了? ";
			link.l1 = "我叫"+GetFullName(pchar)+"船长。 我是应那个吉普赛女人的请求来的。 她想知道你为什么拒绝她的帮助。 你真的能拒绝任何一丝治愈你女儿的机会吗? ";
			link.l1.go = "Tomas_1";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_1":
			dialog.text = "哦, 船长... 请理解, 我不得不拒绝, 但并非出于自愿。 相信我, 我愿意付出一切让埃丝特康复。 ";
			link.l1 = "是什么让你拒绝了你如此迫切需要的帮助? ";
			link.l1.go = "Tomas_2";
		break;

		case "Tomas_2":
			dialog.text = "你看, 我们家族一直很虔诚。 我妻子奥利维亚死后, 我全靠信仰支撑。 当吉普赛人提出帮助时, 我同意了 --任何能救我女儿的方法都行。 但是... 我们的牧师知道了这件事。 ";
			link.l1 = "让我猜猜: 他反对这种帮助? ";
			link.l1.go = "Tomas_3";
		break;

		case "Tomas_3":
			dialog.text = "正是如此。 他说服我只有祈祷和主的意志才能治愈我女儿。 如果我偏离这条道路 --通过使用‘女巫’的帮助 --他威胁要将我逐出教会。 你明白吗? 逐出教会! ";
			link.l1 = "所以埃丝特的健康完全取决于牧师的话? ";
			link.l1.go = "Tomas_4";
		break;

		case "Tomas_4":
			dialog.text = "我和女儿靠教会生活。 信仰对我们就是一切。 如果吉普赛人失败了, 我不仅会失去女儿, 还会失去在这个世界上剩下的立足之地。 人们会疏远我们, 教会会拒绝我们。 埃丝特和我会完全孤立无援。 ";
			link.l1 = "如果牧师同意呢? 你会允许吉普赛人尝试吗? ";
			link.l1.go = "Tomas_5";
		break;

		case "Tomas_5":
			dialog.text = "是的。 如果教会祝福她的行为... 那我就会信任她。 我准备尝试任何可能有帮助的方法。 ";
			link.l1 = "我明白了。 很好, 托马斯, 我会帮你。 我会和你们的牧师谈谈。 也许我能说服他。 ";
			link.l1.go = "Tomas_6";
		break;

		case "Tomas_6":
			dialog.text = "你... 你真的愿意帮助我们? 船长, 我会为你的成功祈祷。 但请记住... 我们的牧师很固执且坚持原则, 说服他并不容易。 ";
			link.l1 = "原则可以用有说服力的论据克服。 等我, 我很快回来。 ";
			link.l1.go = "Tomas_7";
		break;

		case "Tomas_7":
			DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("DWH", "3");
			pchar.questTemp.DWH_pastor = true;
			AddLandQuestMark(characterFromId("SentJons_Priest"), "questmarkmain");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterDisableDialog(sld);
		break;
		
		case "Tomas_11":
			dialog.text = "... ";
			link.l1 = "托马斯, 我设法说服了牧师。 ";
			link.l1.go = "Tomas_12";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_12":
			dialog.text = "真的吗? 难以置信! 那我们尽快邀请吉普赛人吧。 ";
			link.l1 = "我们当然会, 但有一个细节。 牧师希望这不会动摇你的信仰, 并期待真诚的忏悔和善行。 其中一件善行可以是为教区购买一口新钟。 ";
			link.l1.go = "Tomas_13";
		break;

		case "Tomas_13":
			dialog.text = "哦, 船长... 一口钟要花不少钱。 我可能得卖掉亡妻的一些珠宝了。 但为了埃丝特, 我愿意付出所有 --甚至更多。 当然, 我会祈求主的宽恕。 我会去找铁匠, 下订单, 然后找到吉普赛人。 \n请告诉牧师钟很快就会准备好。 就算要我到地下去找, 我也会弄到的。 ";
			link.l1 = "很好, 托马斯。 ";
			link.l1.go = "Tomas_14";
		break;
		
		case "Tomas_14":
			DialogExit();
			
			LAi_SetActorType(npchar);
			pchar.questTemp.DWH_pastor_PrinesDengi = true;
			AddLandQuestMark(characterFromId("SentJons_Priest"), "questmarkmain");
		break;
		
		case "Tomas_15":
			dialog.text = "... ";
			link.l1 = "我把你的话告诉了牧师。 他不再阻拦你了, 所以你可以开始了。 ";
			link.l1.go = "Tomas_16";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_16":
			dialog.text = "谢谢你, 船长, 感谢你的介入! 请收下这五十枚达布隆。 这是我能为你做的最少的事, 也是我目前所有的... ";
			link.l1 = "胡说! 我帮助你不是为了钱。 那么, 一切都准备好... 嗯... 治疗了吗? ";
			link.l1.go = "Tomas_16_1";
			link.l2 = "好吧, 如果你坚持... 还有什么我能做的吗? ";
			link.l2.go = "Tomas_16_2";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
		break;

		case "Tomas_16_1":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.DWH_GoodChoice = true;
		break;
		
		case "Tomas_16_2":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			AddItems(pchar, "gold_dublon", 50);
		break;
		
		case "gypsy_1":
			dialog.text = "要制备恢复女孩健康的药物, 我需要曼加罗萨 --一种生长在人迹罕至地方的稀有植物。 我知道城外有个洞穴, 经常有... 地痞流氓出没。 他们烧曼加罗萨来抽烟, 却不知道它的功效。 帮帮我, "+GetSexPhrase("小猎鹰","小鸽子")+", 帮我弄些曼加罗萨, 没有它什么都做不了。 ";
			if (CheckAttribute(pchar, "questTemp.Mangarosa"))
			{
				link.l1 = "曼加罗萨? 我熟悉那种植物。 ";
				link.l1.go = "gypsy_VD_manga_1";
			}
			else
			{
				link.l1 = "它长什么样? ";
				link.l1.go = "gypsy_VD_no_manga";
			}
		break;

		case "gypsy_VD_no_manga":
			dialog.text = "那是一种相当高的植物, 叶子分裂, 有令人愉悦的。 令人眩晕的气味。 你不会把它认错的。 ";
			link.l1 = "好的, 我会找到这种曼加罗萨。 ";
			link.l1.go = "gypsy_2";
		break;

		case "gypsy_VD_manga_1":
			dialog.text = "你也把它和烟草混在一起? ";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "不, 完全不是! 有个叫阿梅利亚的治疗师。 她用它来酿造能让你神魂颠倒的药水。 ";
				link.l1.go = "gypsy_VD_manga_1_2";
			}
			else
			{
				link.l1 = "不, 但我处理过几次曼加罗萨。 ";
				link.l1.go = "gypsy_VD_manga_2";
			}
		break;

		case "gypsy_VD_manga_1_2":
			dialog.text = "这么说你认识阿梅利亚? 好吧, "+GetSexPhrase("小猎鹰","小鸽子")+", 很快你就会给我带来真正的竞争了。 但现在不是说这个的时候。 去取曼加罗萨, 我会准备好一切。 ";
			link.l1 = "我这就去。 ";
			link.l1.go = "gypsy_2";
			AddCharacterExpToSkill(pchar, "Fortune", 200);
		break;

		case "gypsy_VD_manga_2":
			dialog.text = "我明白了, 你不是普通人, "+GetSexPhrase("小猎鹰","小鸽子")+"。 你的知识渊博, 思维如刀刃般敏锐! 你不害怕探索未知, 渴望掌握别人回避的东西。 托马斯有你帮忙真是幸运。 现在去吧, 给我带曼加罗萨来, 我会治好那个女孩。 ";
			link.l1 = "... ";
			link.l1.go = "gypsy_2";
		break;
		
		case "gypsy_2":
			DialogExit();
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			
			AddQuestRecord("DWH", "5");
			
			// 前往寻找曼加罗萨
			LAi_LocationDisableOfficersGen("Antigua_Grot", true);
			locations[FindLocation("Antigua_Grot")].DisableEncounters = true;
			PChar.quest.DWH_Grot.win_condition.l1 = "location";
			PChar.quest.DWH_Grot.win_condition.l1.location = "Antigua_Grot";
			PChar.quest.DWH_Grot.function = "DWH_Grot";
		break;
		
		case "Bandit_1":
			dialog.text = "哈哈。 我告诉你, 马克, 他是个傻瓜。 他甚至不锁房子。 ";
			link.l1 = "你确定他的老婆不会坐在家里? ";
			link.l1.go = "Bandit_2";
			
			locCameraSleep(true);
			sld = CharacterFromID("DWH_Bandit_1");
			CharacterTurnToLoc(sld, "goto", "ass4");
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "ass2");
		break;
		
		case "Bandit_2":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "", -1);
			DoQuestFunctionDelay("DWH_Grot_2", 4.0);
		break;
		
		case "Bandit_3":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "好吧, 好吧, 新鲜的鱼儿游进了我们的网里! 过来, 别光站着。 把口袋翻出来, 快点, 趁我们还没失去好心情。 ";
			link.l1 = "放轻松, 强盗们。 我是来办事的。 "+sld.name+"派我来的。 我需要曼加罗萨。 ";
			link.l1.go = "Bandit_4";

			locCameraSleep(false);
			locCameraFromToPos(3.39, 1.16, -1.80, true, 3.62, -0.50, 3.63);
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "goto2");
		break;

		case "Bandit_4":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "你说"+sld.name+"派你来的? 好吧, 我们有曼加罗萨。 给我们十枚金币, 它就是你的了。 ";
			if (PCharDublonsTotal() >= 10)
			{
				link.l1 = "给你。 ";
				link.l1.go = "Bandit_5";
			}
			link.l2 = "钱? 为什么? 我可不施舍。 但我可以给你两磅钢铁! ";
			link.l2.go = "Bandit_7";
		break;

		case "Bandit_5":
			dialog.text = "好吧, 这是你的曼加罗萨。 记住, 你从没见过我们。 ";
			link.l1 = "呵。 不需要警告。 ";
			link.l1.go = "Bandit_6";
			GiveItem2Character(PChar, "cannabis7");
			RemoveDublonsFromPCharTotal(10);
		break;
		
		case "Bandit_6":
			DialogExit();
			
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			LAi_LocationDisableOfficersGen("Antigua_Grot", false);
			locations[FindLocation("Antigua_Grot")].DisableEncounters = false;
			
			/*if (CheckAttribute(pchar, "questTemp.DWH_GoodChoice"))*/ SetFunctionLocatorCondition("DWH_VorovstvoSunduk", "Antigua_Grot", "box", "box1", false)
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_3";
			AddLandQuestMark(sld, "questmarkmain");
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("DWH_Bandit_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DWH_Podkreplenie");
			}
		break;
		
		case "Bandit_7":
			DialogExit();
			
			chrDisableReloadToLocation = true;
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			GiveItem2Character(NPChar, "cannabis7");
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("DWH_Bandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=3; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DWH_Bandit_"+i, "citiz_48", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
				if (i==4) sld.model = "citiz_49";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "Antigua_Grot", "reload", "reload1");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "DWH_Grot_4");
		break;
		
		case "gypsy_3":
			if (CheckCharacterItem(PChar, "cannabis7"))
			{
				dialog.text = "... ";
				link.l1 = "看看这个, "+npchar.name+", 这是你需要的植物吗? ";
				link.l1.go = "gypsy_4";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "你把我要的东西带来了吗? ";
				link.l1 = "还没有, 我正在办。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "gypsy_3";
			}
		break;

		case "gypsy_4":
			dialog.text = "是的, 就是这个。 现在我需要的东西都齐了, 可以开始了。 ";
			link.l1 = "... ";
			link.l1.go = "gypsy_5";
			TakeItemFromCharacter(pchar, "cannabis7");
		break;

		case "gypsy_5":
			StartInstantDialog("DWH_Tomas", "Tomas_17", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
		break;

		case "Tomas_17":
			dialog.text = "我们快点去吧, 不能浪费时间。 ";
			link.l1 = "... ";
			link.l1.go = "Tomas_18";
			CharacterTurnByChr(npchar, CharacterFromID("DWH_gypsy"));
		break;

		case "Tomas_18":
			dialog.text = "船长, 如果你不介意, 我们稍后再谈。 我们现在面临最关键的部分... 治疗。 ";
			link.l1 = "当然, 托马斯。 我希望你女儿早日康复。 ";
			link.l1.go = "Tomas_19";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tomas_19":
			DialogExit();
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "gypsy_6":	// 如果未通过牧师的VD检查
			dialog.text = "... ";
			link.l1 = ""+npchar.name+", 托马斯不是自愿拒绝你的。 牧师威胁他, 如果接受你的帮助就逐出教会。 ";
			link.l1.go = "gypsy_7";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_7":
			dialog.text = "我马上就知道, "+GetSexPhrase("亲爱的","美人")+", 他是怀着沉重的心情拒绝我的。 ";
			link.l1 = "有没有办法在不冒犯教会的情况下帮助他? ";
			link.l1.go = "gypsy_8";
		break;

		case "gypsy_8":
			dialog.text = "哦, "+GetSexPhrase("亲爱的","美人")+", 这不是易事, 但我知道方法, 我知道该怎么做。 只是, 没有你的帮助我做不到, 你明白的。 ";
			link.l1 = "当然, 你可以指望我。 ";
			link.l1.go = "gypsy_10";
			link.l2 = "抱歉, 黑眉毛的, 但我完全没时间做这个。 我已经尽了全力。 现在我必须处理自己的事。 ";
			link.l2.go = "gypsy_9";
		break;
		
		case "gypsy_9":
			DialogExit();
			CloseQuestHeader("DWH");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			
			sld = CharacterFromID("DWH_Tomas");
			sld.lifeday = 0;
		break;
		
		case "gypsy_10":
			dialog.text = "那么我需要这些: 女孩的一件物品, 两枝曼陀罗, 一枝吐根, 一枝马鞭草。 如果你把这些都带给我, 我就能为她制备治疗药水。 ";
			link.l1 = "好的, 我会弄到所需的一切。 ";
			link.l1.go = "gypsy_11";
		break;

		
		case "gypsy_11":
			DialogExit();
			AddQuestRecord("DWH", "7");
			
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_21":
			dialog.text = "... ";
			link.l1 = "托马斯, 不幸的是, 牧师不听我的话。 但吉普赛人和我可以帮你。 我需要... ";
			link.l1.go = "Tomas_22";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_22":
			dialog.text = "你是在建议我违背教会吗? ";
			link.l1 = "我们会悄悄做, 没人会知道。 很快你女儿就能重新享受生活, 像一位年轻女士那样自由地在镇上走动。 ";
			link.l1.go = "Tomas_23";
			link.l2 = "该死的, 托马斯.莫里森, 你是想让女儿康复, 还是只是躲在漂亮话后面? ";
			link.l2.go = "Tomas_24";
		break;

		case "Tomas_23":
			dialog.text = "好吧, 我同意。 但请小心行事。 我不想要不必要的谣言和麻烦。 ";
			link.l1 = "绝对的。 那么, 我需要你女儿的一件私人物品。 她依恋的东西。 ";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Sneak", 200);
		break;

		case "Tomas_24":
			dialog.text = "好吧, 我同意。 但请小心行事。 我不想要不必要的谣言和麻烦。 ";
			link.l1 = "绝对的。 那么, 我需要你女儿的一件私人物品。 她依恋的东西。 ";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Tomas_25":
			dialog.text = "嗯... 对! 我知道什么有用。 在这里等我, 我马上回来。 ";
			link.l1 = "我等着... ";
			link.l1.go = "Tomas_26";
		break;

		case "Tomas_26":
			DialogExit();
			SetLaunchFrameFormParam("几分钟后... ", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("DWH_TomasGovotitAgain", 0.0);
			LaunchFrameForm();
		break;
		
		case "Tomas_27":
			dialog.text = "给。 这是玉珠。 埃丝特从不离身, 它们对她很珍贵。 ";
			link.l1 = "太好了。 现在, 你只需等待。 很快见, 托马斯。 ";
			link.l1.go = "Tomas_28";
			GiveItem2Character(PChar, "jewelry49");
		break;

		case "Tomas_28":
			DialogExit();
			AddQuestRecord("DWH", "8");

			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest/MiniEvents/DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "gypsy_21":
			dialog.text = "你设法弄到所需的一切了吗? ";
			if (GetCharacterItem(pchar, "cannabis1") >= 2 && GetCharacterItem(pchar, "cannabis4") >= 1 && GetCharacterItem(pchar, "cannabis3") >= 1)
			{
				link.l1 = "我已经弄到所需的一切了。 ";
				link.l1.go = "gypsy_22";
			}
			link.l2 = "提醒我需要带什么。 ";
			link.l2.go = "gypsy_napomni";
		break;

		case "gypsy_napomni":
			dialog.text = "那么我需要这些: 女孩的一件物品, 两枝曼陀罗, 两枝吐根, 一枝马鞭草。 如果你把这些都带给我, 我就能为她制备草药汁。 ";
			link.l1 = "好的, 我会弄到所需的一切。 ";
			link.l1.go = "gypsy_napomni_2";
		break;

		case "gypsy_napomni_2":
			DialogExit();
			NextDiag.TempNode = "gypsy_21";
		break;

		case "gypsy_22":
			dialog.text = "太好了。 现在我可以为女孩制备治疗药水了。 最早明天早上就能准备好。 你可以像往常一样在镇上的街道上找到我。 ";
			link.l1 = "很好, 到时见。 ";
			link.l1.go = "gypsy_23";
			DelLandQuestMark(npchar);
			RemoveItems(pchar, "cannabis1", 2);
			RemoveItems(pchar, "cannabis4", 1);
			RemoveItems(pchar, "cannabis3", 1);
			RemoveItems(pchar, "jewelry49", 1);
		break;
		
		case "gypsy_23":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("DWH", "11");
			SetTimerFunction("DWH_GypsyPrigotovilaZelie", 0, 0, 1);
		break;
		
		case "gypsy_31":
			dialog.text = "... ";
			link.l1 = "那么, "+npchar.name+", 你的药水准备好了吗? ";
			link.l1.go = "gypsy_32";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_32":
			dialog.text = "给你, "+GetSexPhrase("亲爱的","美人")+"。 让女孩戴上这些珠子, 把瓶里的药水一饮而尽。 不出一个月, 她就会完全康复。 ";
			link.l1 = "我马上把这个带给托马斯。 再见, 黑眉毛的。 ";
			link.l1.go = "gypsy_33";
			GiveItem2Character(PChar, "quest_potion");
			GiveItem2Character(PChar, "jewelry49");
		break;

		case "gypsy_33":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);

			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest/MiniEvents/DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "Tomas_31":
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				dialog.text = "... ";
				link.l1 = "托马斯, 一切都准备好了。 埃丝特应该戴上这些珠子, 把药水一口气喝完。 ";
				link.l1.go = "Tomas_32";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "... ";
				link.l1 = "... ";
				link.l1.go = "exit";
				NextDiag.TempNode = "Tomas_31";
			}
		break;

		case "Tomas_32":
			dialog.text = "谢谢你, "+pchar.name+"! 请原谅我, 我不想浪费一分钟... ";
			link.l1 = "当然, 当然。 ";
			link.l1.go = "Tomas_33";
			TakeItemFromCharacter(pchar, "quest_potion");
		break;
		
		case "Tomas_33":
			DialogExit();
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "Tomas_41":
			dialog.text = "问候你, "+pchar.name+"! 我的埃丝特康复了! 她完全健康了, 现在正在教堂里, 感谢上帝派你和吉普赛人来帮助我们! ";
			link.l1 = "托马斯, 我很高兴一切顺利! 照顾好女孩, 她现在有漫长幸福的生活在前面。 ";
			link.l1.go = "Tomas_42";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_42":
			dialog.text = "收下这三百枚达布隆。 不幸的是, 我只能拿出这么多了, 因为我不得不负债才凑齐这笔钱。 但要知道, 任何言语和黄金都无法表达我对您的感激之情, 船长。 您不仅把我从失去她的恐惧中解放出来, 还给予了我们家庭未来的希望。 我将永远欠您的情! ";
			link.l1 = "谢谢你! 三百枚达布隆非常慷慨了, 请放心 --你已经感谢得足够多了! ";
			link.l1.go = "Tomas_43";
			link.l2 = "我不会拿你的钱, 托马斯。 别想坚持! 最好给年轻的埃丝特买件漂亮的裙子, 她值得拥有。 ";
			link.l2.go = "Tomas_46";
		break;

		case "Tomas_43":
			dialog.text = ""+pchar.name+", 随时来拜访我们。 你在我们家永远受欢迎。 还有, 和那个吉普赛女人谈谈, 她想见你。 ";
			link.l1 = "我将视之为荣幸! 现在我必须告辞了 --潮水不等人。 ";
			link.l1.go = "Tomas_44";
			AddItems(pchar, "gold_dublon", 300);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;

		case "Tomas_44":
			dialog.text = "当然, 当然。 愿上帝与你同在, "+GetFullName(pchar)+"! ";
			link.l1 = "再见。 ";
			link.l1.go = "Tomas_45";
		break;
		
		case "Tomas_45":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_41";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_46":
			dialog.text = "你是个非常高尚的人, "+GetFullName(pchar)+"! 愿圣母玛利亚与你同在! 来拜访我们, 你在我们家永远是受欢迎的客人。 还有, "+pchar.name+", 和吉普赛人谈谈, 她想见你。 ";
			link.l1 = "当然! 现在我必须走了 --大海在召唤。 ";
			link.l1.go = "Tomas_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Tomas_47":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_44";
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.DWH_QuestCompleted = true;
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1;
			
			AddSimpleRumourCity("你听说了吗? "+GetFullName(pchar)+"为托马斯.莫里森的女儿弄到了一种药物, 奇迹般地恢复了这个可怜女孩的健康! ", "SentJons", 10, 1, "");
			AddSimpleRumourCity("托马斯.莫里森每天在教区为"+GetFullName(pchar)+"的健康点蜡烛。 据说多亏了他 (她) 的努力, 托马斯的女儿才从长期疾病中康复。 ", "SentJons", 10, 1, "");
			AddSimpleRumourCity("埃丝特.莫里森在我们眼前绽放了。 好像她从未生过病一样。 没有人能真正解释是什么让疾病消退了。 ", "SentJons", 10, 1, "");
		break;
		
		case "gypsy_41":
			dialog.text = "你来了, "+GetSexPhrase("小猎鹰","小鸽子")+"! 我就知道你会回来。 多亏了你的努力, 女孩康复了, 现在像鸽子一样四处走动。 整个小镇都在惊奇地谈论她。 ";
			link.l1 = "好了, 黑眉毛的, 这不仅仅是我的功劳 --别给我太多赞誉。 是你的药水恢复了她的健康, 所以别贬低你在这件事中的作用。 ";
			link.l1.go = "gypsy_42";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_42":
			dialog.text = "你有一颗善良的心, "+GetSexPhrase("小猎鹰","小鸽子")+", 还有敏锐的头脑! 你注定要成就伟大 --这是我的预言。 ";
			link.l1 = "呵... 好吧, 谢谢你, "+npchar.name+"。 ";
			link.l1.go = "gypsy_43";
		break;
		
		case "gypsy_43": // 坏结局
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "9");
			CloseQuestHeader("DWH");
		break;
		
		case "gypsy_44":
			dialog.text = "你来了, "+GetSexPhrase("小猎鹰","小鸽子")+"! 我就知道你会再次出现在这里。 多亏了你的努力, 女孩康复了, 现在像鸽子一样轻快。 整个小镇都在赞美她。 ";
			link.l1 = "得了吧, 是你救了那个女孩, 你却想让我独占功劳? 那可不行! 是你制备了药水, 是你让她康复, 你应该接受这份荣誉。 ";
			link.l1.go = "gypsy_45";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_45":
			dialog.text = "你有一颗善良的心, "+GetSexPhrase("小猎鹰","小鸽子")+", 还有高尚的灵魂。 我有一份礼物给你 --任何船长都会欣赏的礼物。 给你。 现在你船上的老鼠将既没有快乐也没有安宁! ";
			link.l1 = "给我的礼物? 老天, 太意外了! ";
			link.l1.go = "gypsy_46";
			GiveItem2Character(PChar, "rat_poison");
		break;

		case "gypsy_46":
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				dialog.text = "我看你灵魂纯净, 不会为了一时之快而燃烧曼加罗萨。 如果急需, 就来找我, "+GetSexPhrase("小猎鹰","小鸽子")+"。 三枝要三百五十枚达布隆\n这草药很 capricious, 不是每个人都能找到。 所以别催我 --每月不要问超过一次, 反正我也弄不到。 ";
			}
			else
			{
				dialog.text = "我看你灵魂明亮, 不傻, 懂草药不亚于某些治疗师。 你能找到很多东西, 尽管运气不会总是眷顾。 有一种稀有植物不是每个人都能找到。 它叫曼加罗萨。 如果你需要, 就来找我, "+GetSexPhrase("小猎鹰","小鸽子")+"。 我会弄三枝, 但不会免费给 --我要三百五十枚达布隆\n但这草药很任性, 所以别催我。 每月不要问超过一次 --即使你摆出所有命运的牌, 我也无法更快弄到。 ";
			}
			link.l1 = "好吧, 谢谢你, "+npchar.name+"。 ";
			link.l1.go = "gypsy_47";
		break;
		
		case "gypsy_47": // 好结局
			DialogExit();
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "10");
			CloseQuestHeader("DWH");
			AddQuestRecordInfo("Useful_Acquaintances", "1");
			
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
		
		case "Tomas_51":
			dialog.text = "船长, 我一直在想 --一定是主自己在正确的时间指引你来到这里! 你救了我女儿, 我永远不会忘记。 ";
			link.l1 = "也许吧, 托马斯。 主的道路是不可测的。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tomas_52";
			SetTimerFunction("DWH_Tomas_HelloAgain", 0, 0, 1);
		break;

		case "Tomas_52":
			dialog.text = "你想喝点酒吗, 船长? 我有特别为贵客准备的东西。 ";
			link.l1 = "谢谢你, 托马斯, 但不幸的是, 我必须走了。 ";
			link.l1.go = "exit";
		break;

		case "gypsy_Mangarosa":
			dialog.text = "你需要什么, 我的猎鹰? ";
			if (CheckAttribute(pchar, "questTemp.DWH_Mangarosa"))
			{
				link.l1 = "告诉我, 黑眉毛的, 你有曼加罗萨给我吗? ";
				link.l1.go = "gypsy_Mangarosa_1";
			}
			link.l2 = "只是路过打个招呼。 我该走了! ";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;
		
		case "gypsy_Mangarosa_1":
			dialog.text = "除了我还有谁, "+GetSexPhrase("亲爱的","美人")+"能给你这种稀有之物? 三百五十枚达布隆 --就是你的了, 三枝, 不多不少。 ";
			if (PCharDublonsTotal() >= 350)
			{
				link.l1 = "你的价格很公道。 黄金是你的了。 ";
				link.l1.go = "gypsy_Mangarosa_2";
			}
			link.l2 = "该死! 我的钱包太轻了。 等命运眷顾我时我会回来。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;

		case "gypsy_Mangarosa_2":
			dialog.text = "这就对了。 拿着。 注意别无谓地浪费, 你知道 --曼加罗萨不是普通的草药, 其中隐藏着不是每个人都能驾驭的力量。 ";
			link.l1 = "别担心, 黑眉毛的, 我会为它的力量找到 worthy 的用途。 ";
			link.l1.go = "gypsy_Mangarosa_3";
			AddItems(pchar, "cannabis7", 3);
			RemoveDublonsFromPCharTotal(350);
		break;
		
		case "gypsy_Mangarosa_3":
			DialogExit();
			
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			DeleteAttribute(pchar, "questTemp.DWH_Mangarosa");
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
	}
}