void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "这是个漏洞, 请告知开发者。 ";
			link.l1 = "好的! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Wine_fort":
			dialog.text = "你把酒带来了吗? ";
			if (CheckCharacterItem(pchar, "potionwine"))
			{
				link.l1 = "是的, 带来了。 我花了700比索买的, 所以希望你能付我1000比索。 ";
				link.l1.go = "Wine_fort_1";
			}
			link.l2 = "还没, 我正在想办法。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort";
		break;
	
		case "Wine_fort_1":
			AddMoneyToCharacter(pchar, 1000);
			RemoveItems(PChar, "potionwine", 1);
			dialog.text = "感谢上帝, 我都快渴死了。 非常感谢, 先生! 给你钱, 我收下这瓶酒, 哈哈! 既然我们合作得这么愉快, 我还有个请求\n你能再给我和我的朋友们弄些酒来吗? 我们刚打劫了一帮走私犯, 有的是钱, 呵呵... ";
			link.l1 = "抱歉伙计, 我没时间再给你跑一趟买酒了。 ";
			link.l1.go = "Wine_fort_exit";
			link.l2 = "钱总是好东西。 你需要多少瓶? ";
			link.l2.go = "Wine_fort_2";
		break;
	
	case "Wine_fort_exit":
			DelLandQuestMark(npchar);
			WineTraderQMDel();
			dialog.text = "随你便吧。 不管怎样, 还是谢谢你的帮助! 干杯, 祝你健康! ";
			link.l1 = "继续加油, 士兵! ";
			link.l1.go = "exit";
			sld = characterFromId(pchar.questTemp.Wine.id);	
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			pchar.questTemp.Wine.fail = "true";
			CloseQuestHeader("Wine");
	break;
	
		case "Wine_fort_2":
			dialog.text = "每瓶8里亚尔1000比索, 我们最多能买60瓶, 不能再多了。 但也别少于10瓶 —那可不够我们喝的! ";
			link.l1 = "明白了, 最多60瓶, 最少10瓶。 我会把酒给你带来的。 ";
			link.l1.go = "Wine_fort_3";
		break;
	
		case "Wine_fort_3":
			dialog.text = "有福的人带来美酒的喜讯! 我就指望你了, 船长。 啊, 我差点忘了! 你得在一周内把酒送到这里, 因为我的海军陆战队七天后就要调到舰队去了, 一旦离开, 我们就要好几个月才能回来。 ";
			link.l1 = "我明白了。 我会尽快的。 ";
			link.l1.go = "exit";
			pchar.questTemp.Wine.bottles = "true";
			npchar.lifeday = 7;
			AddQuestRecord("Wine", "1");
			AddQuestUserData("Wine", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Wine.City+"Gen"));
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.SName);
			SetFunctionTimerCondition("Soldier_wait", 0, 0, 7, false);
			NextDiag.TempNode = "Wine_fort_check";
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
	
		case "Wine_fort_check":
			dialog.text = "那么, 船长, 你把酒带来了吗? ";
			if (sti(pchar.items.potionwine) >= 10)
			{
				link.l1 = "是的, 带来了。 ";
				link.l1.go = "Wine_take";
			}
			link.l2 = "没有。 我还在努力。 ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort_check";
		break;
	
		case "Wine_take":
			pchar.questTemp.Wine.Qty = sti(pchar.items.potionwine);
			pchar.questTemp.Wine.Money = sti(pchar.questTemp.Wine.Qty)*1000;
			if (sti(pchar.items.potionwine) > 60)
			{
				dialog.text = "圣阿诺夫保佑我们! 这么多酒! 太棒了! 遗憾的是, 正如我所说, 我们最多只能买60瓶, 很抱歉我们没有足够的钱买更多。 拿着你的比索, 我会好好保管这60瓶酒的。 剩下的请你留着。 ";
				link.l1 = "谢谢。 请确保你和你的士兵朋友们为我的健康干杯! ";
				link.l1.go = "Wine_take_1";
				pchar.questTemp.Wine.Money = 60000;
				RemoveItems(PChar, "potionwine", 60);
			}
			else
			{
				dialog.text = "欢迎回来。 让我看看... 你带来了"+sti(pchar.questTemp.Wine.Qty)+"瓶。 不错! 我收下了。 报酬是" + FindRussianMoneyString(sti(pchar.questTemp.Wine.Money))+"。 ";
				link.l1 = "谢谢。 请确保你和你的士兵朋友们为我的健康干杯! ";
				link.l1.go = "Wine_take_1";
				RemoveItems(PChar, "potionwine", sti(pchar.questTemp.Wine.Qty));
			}
		break;
	
		case "Wine_take_1":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.Wine.Money));
			dialog.text = "我们一定会的, " + GetAddress_Form(NPChar) + "! 鼓声响起, 我得走了。 再见! ";
			link.l1 = "顺风航行, 伙计! ";
			link.l1.go = "Wine_take_2";
		break;
	
		case "Wine_take_2":
			DelLandQuestMark(npchar);
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info ("你交付了葡萄酒");
			pchar.quest.Soldier_wait.over = "yes";//снять прeрываниe
			DeleteAttribute(pchar, "questTemp.Wine.City");
			sld = characterFromId(pchar.questTemp.Wine.id);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитeт
			AddCharacterExpToSkill(pchar, "Fortune", 50);//вeзeниe
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}