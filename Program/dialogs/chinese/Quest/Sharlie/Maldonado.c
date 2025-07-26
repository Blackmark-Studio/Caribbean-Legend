//阿隆索.德.马尔多纳多
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "你有什么需要吗? ";
			link.l1 = "不, 没什么。 ";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "ksochitam":
			dialog.text = "停下, "+GetFullName(pchar)+"船长... ";
			link.l1 = "不知为何, 我对西班牙士兵出现在这里甚至都不感到惊讶... 我想我已经习惯了总有人在追踪我。 卡斯蒂利亚人, 你在这个被上帝遗弃的岛上找什么? 想找个快死的方式吗? ";
			link.l1.go = "ksochitam_1";
		break;
		
		case "ksochitam_1":
			dialog.text = "我叫阿隆索.德.马尔多纳多。 这名字可能你没听过, 但迭戈.德.蒙托亚或许能让你想起什么。 他是我最好的朋友, 他救过我的命, 而现在他的血沾在你手上。 ";
			link.l1 = "我猜你跟着我到这里是为了复仇? ";
			link.l1.go = "ksochitam_2";
		break;
		
		case "ksochitam_2":
			dialog.text = "我不只是来复仇的。 据我所知, 你有库库尔坎的面具? ";
			link.l1 = "好家伙! 又一个寻宝人! 是为了唐.迭戈没完成的事而来? ";
			link.l1.go = "ksochitam_3";
		break;
		
		case "ksochitam_3":
			dialog.text = "我对宝藏没兴趣。 我见过塔亚萨尔的财富, 米格尔.迪乔索除了一点零碎外没带出多少东西。 我想要的是面具。 ";
			link.l1 = "你去过塔亚萨尔? 这很难相信。 据我所知, 迪乔索是那次探险唯一的幸存者。 ";
			link.l1.go = "ksochitam_4";
		break;
		
		case "ksochitam_4":
			dialog.text = "我比迪乔索早二十年去了塔亚萨尔, 就在那个疯狂的巫师卡内克用卑鄙的人祭仪式把面具藏在这个岛上的同一时间。 ";
			link.l1 = "我简直不敢相信! 你是当年被带到那里作为祭品的那群征服者之一? 你们都该死! ";
			link.l1.go = "ksochitam_5";
		break;
		
		case "ksochitam_5":
			dialog.text = "不是所有人都死了, 我活下来了。 ";
			link.l1 = "为什么伊察人决定放过你? 你有什么不同? ";
			link.l1.go = "ksochitam_6";
		break;
		
		case "ksochitam_6":
			dialog.text = "你不会明白的, 连我自己都不明白。 没人放过我, 我记得就像昨天一样... 在那个野蛮人用匕首从卡斯柯背上剥下一块皮, 然后把他处死并开始像疯子一样嚎叫之后, 我好像被吸进了那个神像里。 二十年后, 我在远离塔亚萨尔的地方醒来, 感觉就像只过了一瞬间! ";
			link.l1 = "时空漏斗... 该死的, 克萨特.查说的完全正确! 你怎么知道面具的? 你需要它做什么? ";
			link.l1.go = "ksochitam_7";
		break;
		
		case "ksochitam_7":
			dialog.text = "我必须阻止那个被疯狂印第安巫师召唤的地狱产物, 这个怪物打算把我们的世界烧成灰烬! ";
			link.l1 = "嗯... 你和文森特神父谈过, 对吧? 那位审判官既想保持中立又想参与其中, 真让人惊讶。 他派你来追踪我进行一场生死决战? 干得好, 唐.阿隆索! ";
			link.l1.go = "ksochitam_8";
		break;
		
		case "ksochitam_8":
			dialog.text = "上帝在与邪恶的战斗中坚定了我的手。 我将返回塔亚萨尔, 用面具永远封死那些门, 再也没有人形恶魔能进入我们的世界。 ";
			link.l1 = "你的计划里有个小问题, 唐.阿隆索。 恶魔已经在我们中间了。 我们需要做的就是不让他穿过这些门离开。 只要你不让他拿到面具, 他就做不到。 ";
			link.l1.go = "ksochitam_9";
		break;
		
		case "ksochitam_9":
			dialog.text = "需要做的不止这些。 不管我们谁对谁错, 有一点是肯定的: 门必须永远关闭。 只有一种方法能做到这一点: 在塔亚萨尔的祭坛上毁掉面具。 这样做, 恶魔就会失去所有力量。 ";
			link.l1 = "嗯, 我同意这是最好的办法... 你打算怎么去塔亚萨尔? 你知道路吗? ";
			link.l1.go = "ksochitam_10";
		break;
		
		case "ksochitam_10":
			dialog.text = "我们以前用的捷径已经不存在了, 道路被石头掩埋, 消失在丛林中。 还有另一条通往城市的路, 但又长又危险。 这条路从尤卡坦最北部的海湾开始。 \n在文森特神父和唐.拉蒙.德.门多萨的帮助下, 我将召集一队精锐士兵, 我们将杀出一条血路, 穿过伊察野蛮人保护的丛林。 这不会容易, 但上帝会赐予我们力量和勇气, 让我们为信仰而战。 ";
			link.l1 = "唐.阿隆索, 我的目标正好与你一致。 难道现在不是放下恩怨。 联合力量的时候吗? 我们一起更有可能成功完成这场 crusade。 ";
			link.l1.go = "ksochitam_11";
		break;
		
		case "ksochitam_11":
			dialog.text = "我是西班牙士兵, 我不与异端结盟, 也不与法国人做交易。 此外, 我已经为唐.迭戈向你宣战了, 一命抵一命! ";
			link.l1 = "你固执得像头牛, 唐.阿隆索! 你站在那里宣扬世界受到巨大邪恶的威胁, 却拒绝我的帮助来完成如此艰巨的任务! ";
			link.l1.go = "ksochitam_12";
		break;
		
		case "ksochitam_12":
			dialog.text = "现在由我做决定, 不是文森特神父! 祈祷吧, 准备去死吧, 法国船长! ..";
			link.l1 = "哦, 过去几个月我听了太多次这种话了! 接招吧, 顽固的绅士! ";
			link.l1.go = "ksochitam_13";
		break;
		
		case "ksochitam_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_soldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Maldonado_mushketer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_MaldonadoDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			if (MOD_SKILL_ENEMY_RATE > 4) Ksochitam_CreateMaldonadoHelpers();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}