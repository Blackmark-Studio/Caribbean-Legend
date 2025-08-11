// 城市对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    int i, tempQty, chComp, iShip, iBaseType;
    string tempStr;
    switch (Dialog.CurrentNode)
	{
		case "quests":
			//葡萄牙人
			if (CheckAttribute(pchar, "questTemp.Portugal.Villemstad") && pchar.location == "villemstad_townhall")
			{
				dialog.text = RandPhraseSimple("你想问什么? ", "你需要什么? ");
				link.l1 = "我知道荷兰西印度公司悬赏著名海盗‘葡萄牙人’巴托洛梅奥的人头。 我已经抓住了他, 现在他在我船上的货舱里, 准备交给当局。 ";
				link.l1.go = "Portugal";
				break;
			}
            dialog.text = RandPhraseSimple("你想问什么? ", "你需要什么? ");
			link.l1 = RandPhraseSimple("没什么要紧的事, 先生。 ", "抱歉, 我没什么想说的。 ");
		    link.l1.go = "exit";
		break;
		
		case "work_1":  // 为王室效力 - 国家任务线
			if (CheckAttribute(npchar, "notQuestLine"))
			{
                dialog.text = "很遗憾, 我不能为你提供工作。 目前我不想和你合作。 再见。 ";
                link.l1 = "你不是认真的吧... 好吧。 ";
                link.l1.go = "exit";
				break;
			}                   
		break;
		
		//葡萄牙人
		case "Portugal":
			dialog.text = "‘葡萄牙人’巴特? ! 你抓到他了? 还活着? ";
			link.l1 = "我知道你们不需要他的死讯。 他还活着, 我费了很大劲才让他活着! ";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "太好了! 现在他会告诉我们一切... 先生, 准备转移囚犯。 我们马上派一艘军用三桅帆船去你的船上。 ";
			link.l1 = "我想先谈谈我的报酬, 先生... 如果你不介意的话。 ";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "别担心你的报酬, 船长。 你会得到的。 我们给‘葡萄牙人’巴托洛梅奥的人头悬赏了一千五百达布隆。 中尉! 把报酬拿给船长! ";
			link.l1 = "嗯... 看来雨果骗了我, 说有两千达布隆... 好吧。 ";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			TakeNItems(pchar, "gold_dublon", 1500);
			Log_Info("你获得了1500枚达布隆");
			PlaySound("interface\important_item.wav");
			dialog.text = "现在, 船长, 请你把这个葡萄牙人交给公司。 我们迫不及待地想和他谈谈。 ";
			link.l1 = "当然, 先生, 派三桅帆船到我的船上来吧。 ";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload1", "Portugal_Final");
			DeleteAttribute(pchar, "questTemp.Portugal.Villemstad");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果switch内部有通过return退出的情况, 别忘了执行此卸载
}