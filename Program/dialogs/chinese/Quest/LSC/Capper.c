// 查德.卡珀 - 鲨鱼的水手长和狱卒
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
			dialog.text = "想要点什么? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// 选项 R
		case "Chimiset":
			dialog.text = "呵呵... 所以你就是那个神秘的小偷? 嗯... 你看起来不像个可怜的小偷。 ";
			link.l1 = "听着, 先生, 你弄错了。 我是刚来这里的, 我怎么会知道你们的人在货舱抓住我, 那是你们的私人区域? ";
			link.l1.go = "Chimiset_1";
		break;
		
		case "Chimiset_1":
			dialog.text = "哦, 真的吗? 说得好听, 伙计... 那你从哪里来? ";
			link.l1 = "从主大陆... 穿过一个奇怪的雕像。 我自己也不知道该怎么解释发生了什么。 ";
			link.l1.go = "Chimiset_2";
		break;
		
		case "Chimiset_2":
			dialog.text = "雕像? 哈哈! 你是个有趣的小伙子, 不是吗... 好吧, 我自己来给你解释: 你从船上的洞游进来, 想潜入我们的仓库。 我怎么不认识你的脸? 我认识所有的里瓦多斯人... ";
			link.l1 = "什么里瓦多斯? 我不知道你在说什么! 听着, 我大约一小时前才到这里... ";
			link.l1.go = "Chimiset_3";
		break;
		
		case "Chimiset_3":
			dialog.text = "别喊, 我不是傻瓜。 是的, 我听够了你关于雕像的胡扯, 我觉得很有趣。 我觉得这太他妈好笑了。 我们一起笑怎么样? 哈哈哈! ... 你为什么不笑? 这是个好笑话... 里瓦多斯。 但现在笑话结束了。 我会让你在监狱里腐烂, 伙计。 ";
			link.l1 = "我不是里瓦多斯! 我叫查尔斯.德.莫尔! ";
			link.l1.go = "Chimiset_4";
		break;
		
		case "Chimiset_4":
			dialog.text = "第一次来, 是吗? 嗯... 也许你说的是实话。 回答我, 你是他们中的一员吗? ! ";
			link.l1 = "我向你发誓, 我以前从未听过这个名字, 我不是他们中的一员! ";
			link.l1.go = "Chimiset_5";
		break;
		
		case "Chimiset_5":
			dialog.text = "真的吗? 好的。 证明一下。 下楼去, 有一个里瓦多斯人坐在笼子里。 他是个危险的巫师。 杀了他, 我才会相信。 我也会忘记你非法闯入我们仓库的事\n那么? 你准备好了吗? 别害怕, 巫师手无寸铁, 身体虚弱。 嗯, 他可能会用某种咒语把你化为灰烬, 就像把你送到圣奥古斯丁货舱的那个咒语一样... ";
			link.l1 = "如果你见过那个咒语的效果, 你就不会这么怀疑了。 我怀疑你甚至都活不下来... ";
			link.l1.go = "Chimiset_6";
		break;
		
		case "Chimiset_6":
			dialog.text = "别废话了! 你做不做? 如果做, 就拿这把弯刀去对付那个巫师。 否则你将在笼子里度过余生。 明白了吗? ";
			link.l1 = "两害相权取其轻。 把弯刀给我。 ";
			link.l1.go = "Chimiset_7";
		break;
		
		case "Chimiset_7":
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "slave_02");
			EquipCharacterbyItem(pchar, "slave_02");
			dialog.text = "好孩子。 拿着, 去杀了那个黑人。 他的笼子没锁。 现在别耍什么花招, 如果我们察觉到你有任何想法, 会毫不犹豫地解决你! 现在就去! ";
			link.l1 = "为什么? 你怕我用这破铜烂铁把你们这帮家伙开膛破肚? ";
			link.l1.go = "Chimiset_8";
		break;
		
		case "Chimiset_8":
			dialog.text = "我快没耐心了。 去货舱, 按我说的做! ";
			link.l1 = "好的, 好的, 放松。 我这就走... ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//解锁F2
		break;
		
		case "Chimiset_9":
			dialog.text = "你在考验我的耐心, 混蛋! 你不会想惹我生气的... ";
			link.l1 = "好的, 好的, 放松。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "Chimiset_9";
		break;
		
		case "Fightfail_Final":
			dialog.text = "你杀了那个黑人巫师吗? 很好... 我很高兴。 你已经证明了你不是里瓦多斯人。 ";
			link.l1 = "我什么时候才能从这个该死的地方出去? 我需要立即见鲨鱼。 ";
			link.l1.go = "Fightfail_Final_1";
		break;
		
		case "Fightfail_Final_1":
			dialog.text = "你会见到他的, 当然... 你会在去地狱的路上见到他! ";
			link.l1 = "什么? ! ";
			link.l1.go = "Fightfail_Final_2";
		break;
		
		case "Fightfail_Final_2":
			DialogExit();
			DoQuestCheckDelay("LSC_ChadGuardAttack_Fail", 0.1);
		break;
		
		// 选项 N
		case "prisoner":
			dialog.text = "哈! 看看这是谁。 你在我的监狱里干什么? ";
			link.l1 = "你叫查德.卡珀, 对吧? 我叫"+GetFullName(pchar)+", 我代表鲨鱼.多德森来这里。 他给了我钥匙。 ";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "来自舰队司令? 嗯, 我明白了。 你是他的新跑腿的? ";
			link.l1 = "放尊重点, 先生。 我不伺候任何人, 不管是鲨鱼还是你, 我也不会容忍这种语言。 ";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "哈哈, 我喜欢你, 伙计! 忘了我说的话... 那么, 你在这里有什么事? ";
			link.l1 = "鲨鱼下令释放奇米塞特, 他被关押在这里。 ";
			link.l1.go = "prisoner_3";
		break;
		
		case "prisoner_3":
			dialog.text = "里瓦多斯的巫师? 嗯。 这很奇怪, 听到这个我真的很惊讶... ";
			link.l1 = "鲨鱼下了命令。 他想与里瓦多斯和解。 ";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "啊-啊, 现在我明白了。 好的, 我会派人去里瓦多斯。 他们会来这里带走他们的小丑。 ";
			link.l1 = "你为什么不直接放了他? ";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "我可以, 但这对他来说太危险了。 奇米塞特在这里很有名, 一旦他踏上'埃斯梅拉达号'--他的敌人独角鲸帮的地盘, 他的生命就一文不值了。 从塔塔罗斯没有其他路可走, 我们不能让这个老人绕着岛游泳! \n如果有人杀了他, 里瓦多斯会责怪我们, 具体来说是我! 明白吗, 我不想惹可以避免的麻烦。 所以我只会在他帮派的战士保护下才会放他出去。 也许, 你想亲自和奇米塞特谈谈? 他是个有趣的人... ";
			if (CheckAttribute(npchar, "quest.chimiset_talk")) link.l1 = "我已经和他谈过了, 他确实是个奇怪的人。 不管怎样, 我得走了。 再见, 查德! ";
			else link.l1 = "这正是我打算的。 我去和他谈谈。 ";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			DialogExit();
			sld = characterFromId("Chimiset");
			sld.quest.capper_talk = "true"; // 与卡珀的谈话已发生
			if (!CheckAttribute(npchar, "quest.chimiset_talk")) chrDisableReloadToLocation = true;//关闭位置
			else chrDisableReloadToLocation = false;//打开位置
			NextDiag.CurrentNode = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "我会派一个信使去里瓦多斯, 他们会带走他们的巫师。 别担心, 伙计, 你可以走了。 ";
			link.l1 = "好的。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_7";
		break;
		
		// 选项 M
		case "Aeva_attack":
			dialog.text = "... 他一定已经打开了桶, 我确定。 这是他最喜欢的威士忌, 该死的爱尔兰货。 很快就会结束, 我放了足够多的砒霜, 足以杀死一群... ";
			link.l1 = "";
			link.l1.go = "Aeva_attack_1";
			CharacterTurnToLoc(npchar, "quest", "quest2");
		break;
		
		case "Aeva_attack_1":
			dialog.text = "啊? 该死的, 你在这里干什么? 滚出去! ";
			link.l1 = "我找了你很久... 投毒者。 奇怪的是, 我没看到独眼龙。 你想取代鲨鱼的位置, 对吗? ";
			link.l1.go = "Aeva_attack_2";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Aeva_attack_2":
			dialog.text = "哈哈, 鲨鱼现在一定死了! 你很快也会跟着他去的, 间谍! ";
			link.l1 = "... ";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Aeva_attack_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("ChadNarval_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_CapperDieAeva");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Aeva_attack_2":
			dialog.text = "... 这将是一杯该死的烈酒。 那个爱尔兰人很久以来一直梦想着这瓶威士忌, 所以他会在一秒钟内把它喝光。 砒霜在哪里? 多倒点, 确保万无一失... 然后我们的朋友法奇奥会把这个桶作为独角鲸帮的礼物送给舰队司令, 哈哈! 我说得对吗, 亲爱的朱塞佩? 你想活下去吗? \n啊! 看, 我们有客人! 你想要什么, 混蛋? 在我们钉死你之前滚出去! ";
			link.l1 = "你的计划失败了, 卡珀。 我一直在跟踪你, 我知道你和你的独眼龙朋友打算做什么。 把砒霜扔掉! 你不能毒害鲨鱼! ";
			link.l1.go = "Aeva_attack_3";
		break;
		
		case "Aeva_attack_3":
			dialog.text = "啊, 侦探! 好吧, 那你先死! 伙计们, 拿起武器! ";
			link.l1 = "... ";
			link.l1.go = "Aeva_attack_fight";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}