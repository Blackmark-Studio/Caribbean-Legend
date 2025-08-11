void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;
		//--------------- —摧毁帮派 ----------------------
		case "DestroyGang_begin":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // 允许战斗
			DeleteAttribute(&locations[FindLocation(pchar.GenQuest.DestroyGang.Location)], "DisableEncounters"); // 允许遭遇战
			for(i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)]);
			dialog.text = LinkRandPhrase("把钱交出来, " + GetSexPhrase("伙计","姑娘") + "! 我叫" + GetFullName(npchar) + ", 我不习惯被拒绝... ",
				"现在把你的钱包拿出来, " + GetSexPhrase("伙计","姑娘") + ", 快点! 我叫" + GetFullName(npchar) + ", 希望你听说过我... ",
				"把你所有值钱的东西都给我, 我还要征用你钱包里的东西。 快点, 耐心不是我的强项。 不能说我不嗜血! ");
			Link.l1 = LinkRandPhrase("呵, 原来你就是那个当地总督" + sTemp + "一直在说的著名强盗" + GetFullName(npchar) + "? ",
				"哦, 原来你就是那个被当地总督" + sTemp + "追捕的强盗? ! ", 
				"很" + GetSexPhrase("","") + "高兴见到你, " + GetFullName(npchar) + "。 当地总督" + sTemp + "只谈论你。 ");
			Link.l1.go = "DestroyGang_1";
		break;		
		case "DestroyGang_1":
			dialog.text = LinkRandPhrase("是的, 我在这一带很有名, 嘿嘿... 等等, 你不是总督派来追踪我的另一个" + GetSexPhrase("肮脏的猎犬","肮脏的母狗") + "吗? ",
				"总督是我的好朋友, 这是真的。 你不会是他派来取我人头的" + GetSexPhrase("另一个英雄","另一个女英雄") + "吧? ",
				"总督是我最好的伙伴, 这不是秘密, 嘿嘿。 但你怎么知道的? 也许是他派你来的? ");
			Link.l1 = LinkRandPhrase("正是, 混蛋。 准备受死吧! ", "你还挺机灵! 好吧, 是时候解决你了。 废话少说。 ", "是的, 是我。 拿出你的武器, 伙计! 让我看看你的血是什么颜色的。 ");
			Link.l1.go = "DestroyGang_ExitFight";	
			Link.l2 = LinkRandPhrase("哦, 没关系! 我根本不需要这种麻烦... ", "不, 不, 我绝不是什么英雄... ", "不, 不, 我绝不会! 我不需要麻烦... ");
			Link.l2.go = "DestroyGang_2";	
		break;
		case "DestroyGang_2":
			dialog.text = LinkRandPhrase("这就对了, " + GetSexPhrase("伙计","姑娘") + "... 现在滚吧! ",
				"这是个正确的决定。 你知道我送了多少英雄去另一个世界吗... 好了, 少说废话。 滚吧, " + GetSexPhrase("废物","婊子") + "! ",
				"好" + GetSexPhrase("小子","姑娘") + "! 非常明智的决定 - 不干涉别人的事... 好了, 快滚吧, " + GetSexPhrase("伙计","姑娘") + "。 ");
			Link.l1 = "再见, 祝你好运... ";
			Link.l1.go = "DestroyGang_ExitAfraid";	
		break;

		case "DestroyGang_ExitAfraid":
			pchar.GenQuest.DestroyGang = "Found"; // 标记为找到, 但被吓跑
			npchar.money = AddMoneyToCharacter(npchar, sti(pchar.money));
			pchar.money = 0;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar)-1, false, "DestroyGang_SuddenAttack");
			for(i = 1; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;	
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
				LAi_SetImmortal(sld, true);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DestroyGang_SuddenAttack");
			}
			DialogExit();
		break;

		case "DestroyGang_ExitFight":
			for(i = 0; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// 禁运乘客
		case "ContraPass_abordage":
			dialog.text = "啊, 你这个混蛋! 你怎么敢攻击我的船? ! 你会为此付出代价的! ";
			link.l1 = "恰恰相反, 我其实是为此得到报酬的。 你船上有一个特定的人, 名叫" + pchar.GenQuest.TakePassenger.Name + "。 他是我需要的人。 ";
			link.l1.go = "ContraPass_abordage_1";
		break;
		
		case "ContraPass_abordage_1":
			dialog.text = "我就知道这个骗子会给我们带来麻烦... 但你不会轻易抓到我的! 保护好自己, 肮脏的海盗! ";
			link.l1 = "需要考虑防御的是你, 杂种。 ";
			link.l1.go = "ContraPass_abordage_2";
		break;
		
		case "ContraPass_abordage_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "ContraPass_GivePrisoner");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Tempsailor":
			dialog.text = "船长, 我们按您的命令搜查了客舱和货舱。 那个混蛋试图躲藏, 但我们找到了他。 ";
			link.l1 = "太好了! 他现在在哪里? ";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "按您的命令, 他在货舱里。 ";
			link.l1 = "太好了! 现在让我们离开这艘旧船。 是时候返回了。 ";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "马上就来, 船长! ";
			link.l1 = "... ";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			sld = GetCharacter(NPC_GenerateCharacter("ContraPass", "citiz_"+(rand(9)+11), "man", "man", 10, sti(pchar.GenQuest.TakePassenger.Nation), -1, true, "quest"));
			sld.name = pchar.GenQuest.TakePassenger.Name;
			sld.lastname = "";
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.TakePassenger.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
		break;
		
		case "Fugitive_city": // 在城市中
			pchar.quest.AllMayorsQuests_Late.over = "yes"; // 移除总计时器
			dialog.text = "先生, 你想要什么? ";
			link.l1 = "好啊... 所以你就是" + pchar.GenQuest.FindFugitive.Name + ", 不是吗? 我很高兴见到你... ";
			link.l1.go = "Fugitive_city_1";
		break;
		
		case "Fugitive_city_1":
			dialog.text = "嗯, 确实是我, 但你为什么高兴见到我? 我觉得很奇怪, 因为我以前从未见过你... 介意解释一下吗? ";
			link.l1 = "当然。 我来自" + XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity+"Gen") + ", 奉当地总督的命令。 你被捕了, 我必须把你送回那个城市... 哦, 手离你的军刀远点! 别做傻事, 好人, 否则后果对你不利! ";
			link.l1.go = "Fugitive_city_2";
		break;
		
		case "Fugitive_city_2":
			dialog.text = "所以, 你终究还是找到我了... 先生, 听我说, 也许你会改变主意。 是的, 我从驻军擅离了。 但我无法眼睁睁看着我们的军队堕落! \n我想要平静的生活, 我在这个村庄找到了这样的生活... 别管我, 告诉他们你没找到我, 或者说我和海盗一起逃到了公海。 作为回报, 我会给你这袋琥珀。 我应该说这是非常有价值的物品... ";
			link.l1 = "先生, 别想贿赂我! 放下武器, 跟我走! ";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "嗯... 堕落? 平静的生活? 好吧, 我想我可以实现你的愿望。 你的琥珀在哪里? ";
			link.l2.go = "Fugitive_city_gift";
		break;
		
		case "Fugitive_city_fight":
			dialog.text = "那就拔出你的剑, 雇佣兵! 你不会轻易抓到我的! ";
			link.l1 = "好的, 让我看看你的本事! ";
			link.l1.go = "Fugitive_fight_1";
		break;
		
		case "Fugitive_city_gift":
			TakeNItems(pchar, "jewelry8", 50+hrand(25));
			TakeNItems(pchar, "jewelry7", 2+hrand(5));
			PlaySound("interface\important_item.wav");
			Log_Info("你已收到琥珀");
			dialog.text = "给你... 我希望再也见不到你或其他'使者'了。 ";
			link.l1 = "我向你保证你不会的。 再见, 先生! ";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_gift_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.FindFugitive = "Found"; // 标记为失败
			AddQuestRecord("MayorsQuestsList", "12-4");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity));
		break;
		
		case "Fugitive_fight_1":// 在城市和海湾
			chrDisableReloadToLocation = true;// 关闭地点
			DialogExit();
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Fugitive_afterfight":
			dialog.text = "啊! 你赢了, 去你的! 我投降... ";
			link.l1 = "注意你的言辞, 先生! 现在, 请把你的军刀给我... 跟我来, 别耍花招! ";
			link.l1.go = "Fugitive_afterfight_1";
		break;
		
		case "Fugitive_afterfight_1":
			DialogExit();
			RemoveAllCharacterItems(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			//DeleteAttribute(npchar, "LifeDay");
			npchar.lifeday = 0;
			LAi_SetImmortal(npchar, true);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.GenQuest.FindFugitive.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			pchar.GenQuest.FindFugitive = "Execute"; // 标记为成功完成
			pchar.quest.FindFugitive1.win_condition.l1 = "location";
			pchar.quest.FindFugitive1.win_condition.l1.location = pchar.GenQuest.FindFugitive.Startcity+"_townhall";
			pchar.quest.FindFugitive1.function = "FindFugitive_inResidence";
			SetFunctionTimerCondition("FindFugitive_Over", 0, 0, 30, false);
		break;
		
		case "Fugitive_shore": // 在海湾
			pchar.quest.AllMayorsQuests_Late.over = "yes"; // 移除总计时器
			dialog.text = "先生, 我没心情和你说话, 所以... ";
			link.l1 = "尽管如此, 你还是得和我说话。 你是" + pchar.GenQuest.FindFugitive.Name + ", 不是吗? 我想你不应该否认。 ";
			link.l1.go = "Fugitive_shore_1";
		break;
		
		case "Fugitive_shore_1":
			dialog.text = "我也不打算否认, 是我。 但你想要什么? ";
			link.l1 = "我需要把你带到" + XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity) + ", 当地总督非常想见你。 请不要耍花招! 放下武器, 跟我走! ";
			link.l1.go = "Fugitive_shore_2";
		break;
		
		case "Fugitive_shore_2":
			dialog.text = "我明白了... 先生, 在你冲动行事之前, 让我告诉你一些事情。 是的, 我从驻军擅离了。 但我这样做是有原因的。 我无法继续服役, 这超出了我的承受能力! 你明白吗? 我不能! \n我想要平静的生活, 我在这个村庄找到了这样的生活... 别管我, 告诉他们你没找到我, 或者说我和海盗一起逃到了公海。 作为回报, 我会给你我每周捕捞的珍珠。 这是我所有的了。 ";
			link.l1 = "先生, 别想贿赂我! 放下武器, 跟我走! ";
			link.l1.go = "Fugitive_city_fight";
			link.l2 = "嗯... 厌倦了兵役? 想要平静的生活? 好吧, 我想我可以实现你的愿望。 你的珍珠在哪里? ";
			link.l2.go = "Fugitive_shore_gift";
		break;
		
		case "Fugitive_shore_gift":
			TakeNItems(pchar, "jewelry52", 100+hrand(40));
			TakeNItems(pchar, "jewelry53", 400+hrand(100));
			PlaySound("interface\important_item.wav");
			Log_Info("你已收到珍珠");
			dialog.text = "给你... 我希望再也见不到你或其他'使者'了。 ";
			link.l1 = "我向你保证你不会的。 再见, 先生! ";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern": // 在酒馆
			pchar.quest.AllMayorsQuests_Late.over = "yes"; // 移除总计时器
			dialog.text = "呃... 嗝! 先生, 我不想找伴 - 尤其是你。 滚! ";
			link.l1 = "但我正在找你的伴, " + pchar.GenQuest.FindFugitive.Name + "! 你将在我船的货舱里忍受我的陪伴。 我们要去" + XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity) + ", 去见镇长。 他非常想见你。 ";
			link.l1.go = "Fugitive_tavern_1";
		break;
		
		case "Fugitive_tavern_1":
			dialog.text = "哈-嗝! " + RandSwear() + " 原来他终究还是追着我来了! 听着, 兄弟, 你不知道发生了什么, 你不在场! 我不能继续服役, 我就是不能! 我每天晚上都喝得酩酊大醉, 以此忘记那件事\n看, 我们做个交易。 告诉他你没找到我, 或者说我和海盗一起逃到了公海。 作为回报, 我会把我在当地山洞里找到的所有金块都给你。 这是我所有的了, 看, 我把一切都给你, 只是为了再也不见" + XI_ConvertString("Colony"+pchar.GenQuest.FindFugitive.Startcity) + "... ";
			link.l1 = "先生, 别想贿赂我! 放下武器, 跟我走! ";
			link.l1.go = "Fugitive_tavern_fight";
			link.l2 = "嗯... 有不愉快的故事? 被噩梦或内疚感折磨? 好吧, 我想我可以让你自己处理。 你的金块在哪里? ";
			link.l2.go = "Fugitive_tavern_gift";
		break;
		
		case "Fugitive_tavern_gift":
			TakeNItems(pchar, "jewelry5", 50+hrand(30));
			TakeNItems(pchar, "jewelry6", 100+hrand(50));
			PlaySound("interface\important_item.wav");
			Log_Info("你已收到金块");
			dialog.text = "给你... 我希望再也见不到你或其他'使者'了。 ";
			link.l1 = "我向你保证你不会的。 再见, 先生! ";
			link.l1.go = "Fugitive_gift_exit";
		break;
		
		case "Fugitive_tavern_fight":
			dialog.text = "那就拔出你的剑, 雇佣兵! 你不会轻易抓到我的! ";
			link.l1 = "好的, 让我看看你的本事! ";
			link.l1.go = "Fugitive_fight_2";
		break;
		
		case "Fugitive_fight_2":// 在酒馆
			DialogExit();
			chrDisableReloadToLocation = true;// 关闭地点
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);// 允许战斗
			LAi_SetImmortal(npchar, false);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			Diag.currentnode = "Fugitive_afterfight";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}