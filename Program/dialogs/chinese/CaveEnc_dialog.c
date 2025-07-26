// 洞穴遭遇战
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, sGroup;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	sTemp = "CaveBandos" + locations[FindLocation(npchar.location)].index + "_";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "你想要什么? ";
			link.l1 = "不, 什么都不要。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "CaveBanditosSit":
			if (hrand(2) == 1) 
			{
				dialog.text = NPCStringReactionRepeat("哇哦, 看看谁来了! 好吧, 今天算你走运, 伙计。 我们是好人, 知道吗, 正在煮东西吃... 我不是要请你吃饭, 但你最好趁现在赶紧滚开。 ", "现在就滚开, 别烦我们。 明天再来 --别忘了带上你的钱包, 哈哈哈! ", "别惹我生气, 水手! 你还记得洞穴的入口在哪里吗? 你现在应该马上。 非常非常快地去那里... ", "好吧, 现在你越界了, 伙计! 我想我得放下手头的事来对付你了, 混蛋! ", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("你真是太好心了, 伙计... ", "我看你挺会开玩笑的... ", "好吧, 那你继续煎你的薄饼吧... ", "这就对了, 哈哈哈! ", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("哇, 我的天! 没必要去打猎了 --猎物自己送上门了... 嘿, 伙计们 --我们来搜搜这个花花公子的身, 好吗? ", "没人邀请你来这里, 伙计... 但你既然来了, 正好。 让我们看看你的钱包有多沉! ", "没人强迫你来这里, 嘿嘿... 但既然你已经来了, 我们不妨逗逗你, 看看你口袋里能掉出什么来... ");
				link.l1 = LinkRandPhrase("现在我要把你的舌头剪短一点... ", "我希望你的剑术能配得上你的小聪明, 碎嘴子! ", "好吧, 看来是时候在你这脆弱的身体上多开几个洞了... ");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveBanditosSit";
		break;
		
		case "CaveBanditosStay":
			dialog.text = LinkRandPhrase("哇, 我的天! 没必要去打猎了 --猎物自己送上门了... 嘿, 伙计们 --我们来搜搜这个花花公子的身, 好吗? ", "没人邀请你来这里, 伙计... 但你既然来了, 正好。 让我们看看你的钱包有多沉! ", "没人强迫你来这里, 嘿嘿... 但既然你已经来了, 我们不妨逗逗你, 看看你口袋里能掉出什么来... ");
			link.l1 = LinkRandPhrase("现在我要把你的舌头剪短一点... ", "我希望你的剑术能配得上你的小聪明, 碎嘴子! ", "好吧, 看来是时候在你这脆弱的身体上多开几个洞了... ");
			link.l1.go = "fight";
		break;
		
		case "CaveBanditosTreasure":
			dialog.text = NPCStringReactionRepeat("滚开, 伙计。 这里没你的事! ", "嘿, 我友好地提醒你: 滚开。 你永远不知道会发生什么... ", "最后警告: 如果你现在不滚开, 你会后悔来这里的。 ", "够了, 伙计, 你自找的。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("别告诉我该做什么, 好吗? ", "下面有什么特别的? 不过是个洞穴, 没什么大不了的... ", "哦, 得了吧... ", "哈! 好吧, 让我们看看谁更厉害, 蛆虫! ", npchar, Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "CaveBanditosTreasure";
		break;
		
		case "CaveCaribSit":
			if (hrand(2) == 2) 
			{
				dialog.text = NPCStringReactionRepeat("白脸人走开。 "+npchar.name+"仁慈, 你该庆幸。 今天神明会怜悯你。 ", "在我和我兄弟们生气之前, 从我的洞穴里滚出去! ", "滚出去, 白脸狗! ", "你的运气和性命都到头了, 白狗! ", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("好吧, 谢谢你, 伙计, 你真是太好了... ", "这个洞穴不是你的, 我想去哪就去哪。 ", "收敛点, 沼泽里的家伙。 ", "现在我要把这些话塞回你喉咙里, 畜生... ", npchar, Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("该死的白脸人来到了我们的营火旁! 哇哦! 你死定了! ", "愚蠢的白脸人来到了美洲豹的巢穴。 我要煎了你的肝! ", "傲慢的白脸人竟敢来到我的洞穴? 那他就别想活着出去! ");
				link.l1 = LinkRandPhrase("现在我要扯出你的舌头... ", "现在世界上会少几个食人族... ", "好吧, 看来是时候在你这脆弱的身体上多开几个洞了, 你这红脸的猿猴。 ");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveCaribSit";
		break;
		
		case "CaveCaribStay":
			dialog.text = LinkRandPhrase("肮脏的白脸人来到了我们的洞穴! 嘿嘿! 我要割下你的舌头煎了! ", "愚蠢的白脸人来到了美洲豹的巢穴。 兄弟们, 宰了这该死的白狗! ", "傲慢的白脸人竟敢来到我的洞穴? 那他就别想活着出去! ");
			link.l1 = LinkRandPhrase("我要砍下你那该死的脑袋... ", "现在世界上会少几个食人族... ", "好吧, 准备去见你的祖先吧, 红皮肤。 下地狱去吧! ");
			link.l1.go = "fight";
		break;
		
		case "exit_talk":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
		break;
		
		case "fight":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "CaveEnc_RaidersAfrer");
			chrDisableReloadToLocation = true;
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}