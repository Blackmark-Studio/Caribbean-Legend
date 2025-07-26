// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("说吧, 你想要什么? ",
                          "我们刚聊过这个。 你肯定是忘了... ", "这已经是今天你第三次问这类问题了... ",
                          "听着, 这是商店。 人们来这儿买东西。 别打扰我! ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("你知道吗, " + Npchar.name+ ", 或许下次吧。 ", "对, 不知怎么就忘了... ",
                      "是啊, 真的是第三次了... ", "嗯, 我不会了... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason --> 葡萄牙人
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Findcloves" && !CheckAttribute(npchar, "quest.Portugal"))
			{
   				link.l1 = "听着, 我需要一些华丽的衣服。 要贵的, 我想打扮得像个真正的贵族。 你有类似的东西吗? ";
				link.l1.go = "Portugal_cloves";
			}
			//<—— 葡萄牙人
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten")
			{
				link.l1 = "最近有艘名为‘令人钦佩’的大帆船给你运来了一批兽皮货物。 你还记得吗? ";
                link.l1.go = "guardoftruth";
			}
		break;
		
		//Jason --> 葡萄牙人
		case "Portugal_cloves":
			dialog.text = "贵族服饰? 当然, 我这儿有一套: 裤子。 短上衣。 丝绸衬衫和靴子。 售价20000比索。 这衣服质量非常好, 穿着舒适且外观出众, 所以这个价不能再低了。 ";
			if (sti(pchar.money) >= 20000)
			{
				link.l1 = "太好了! 给我吧。 ";
				link.l1.go = "Portugal_cloves_1";
			}
			link.l2 = "嗯... 我现在没那么多钱。 ";
			link.l2.go = "Portugal_cloves_nomoney";
		break;
		
		case "Portugal_cloves_nomoney":
			dialog.text = "那等你有钱了再来吧。 ";
			link.l1 = "好的。 我会再来的! ";
			link.l1.go = "exit";
		break;
		
		case "Portugal_cloves_1":
			AddMoneyToCharacter(pchar, -20000);
			GiveItem2Character(pchar, "suit_1");
			Log_Info("你获得了贵重服饰");
			PlaySound("interface\important_item.wav");
			dialog.text = "给你。 ";
			link.l1 = "谢谢你! ";
			link.l1.go = "exit";
			npchar.quest.Portugal = "true";
			sld = characterFromId("PortugalDoctor");
			sld.dialog.currentnode = "Portugal_doctor_4";
			DelLandQuestMark(characterFromId("Marigo_trader"));
			AddLandQuestMark(characterFromId("PortugalDoctor"), "questmarkmain");
			QuestPointerDelLoc("marigo_town", "reload", "reload6_back");
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		//<—— 葡萄牙人
		case "guardoftruth":
			dialog.text = "记得。 他准时到达, 卸下货物, 我按约定付了款。 你为什么问这个? ";
			link.l1 = "那艘船的船长是盖乌斯.马沙, 我的老熟人。 所以我在试着找他。 你能告诉我他之后做了什么吗? 也许你给了他额外的货运任务, 或者他提到过要去哪里? ";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "没什么特别的。 我没给他安排额外货运, 他甚至都没问过。 他也没跟我分享过未来的计划。 你知道从那以后有多少人进出这里吗? 我连所有细节都记不清了。 他卸完货就起航了, 关于他我只能说这么多。 ";
			link.l1 = "好吧。 无论如何还是谢谢你。 祝你一切顺利! ";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "11");
			pchar.questTemp.Guardoftruth = "maarten1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}