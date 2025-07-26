// 城市对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你想要什么? ", "你想了解什么? "), "你需要什么, " + GetAddress_Form(NPChar) + "? ", "这是你第三次想问我了... ", "我受够你了, 滚开! ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("抱歉, 我改变主意了。 ", "没什么, 抱歉。 "), "我忘了, 抱歉... ",
                      "事不过三, 对吧? 打扰了... ", "抱歉抱歉! 那我先告辞了... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak")
			{
				link.l1 = "你好。 圣地亚哥的审判官达德雷.文森特在信中提到了你, 他说你可能会帮我。 ";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "mayak_next")
			{
				link.l1 = npchar.name+ ", 有帕德雷.文森特的消息吗? ";
                link.l1.go = "guardoftruth_5";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && CheckCharacterItem(pchar, "jewelry33") && CheckCharacterItem(pchar, "jewelry34") && CheckCharacterItem(pchar, "jewelry35"))
			{
				link.l1 = "我需要见帕德雷.文森特, 我找到了他感兴趣的物品。 ";
                link.l1.go = "guardoftruth_7";
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "inquisition")
			{
				link.l1 = npchar.name+ ", 帕德雷.文森特跟你说了什么? ";
                link.l1.go = "guardoftruth_11";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "当然, 先生。 如果帕德雷.文森特亲自与你打交道, 那你一定是个声名显赫的人。 ";
			link.l1 = "太好了。 那你就是我们的信使了。 听着, 这个人对帕德雷.文森特来说非常重要, 现在他由你负责, 你得把他送到圣地亚哥, 或者找个人送去。 ";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "... ";
			link.l1 = "你代表审判官负责这个囚犯。 我建议你别解开他的枷锁, 盖乌斯.马沙伊斯是个强壮的人。 把这封信交给帕德雷.文森特, 告诉他我等他两天内回复, 希望这足够了。 ";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			Log_Info("你交出了信件");
			PlaySound("interface\important_item.wav");
			dialog.text = "明白了, 先生。 我会尽力而为, 这不是我第一次帮神父了。 ";
			link.l1 = "不止这些。 卡拉卡船‘圣格雷戈里奥号’的船长卡洛斯.格瓦拉一定来过这里, 他给我带了香草。 他把我的信给你了吗? ";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "是的, 先生, 你的货物完好无损, 在等你。 ";
			link.l1 = "很好, 那我让人把它搬到我的船上。 我会在这里等两天, 等帕德雷.文森特的回复。 " + npchar.name+ ", 这不算告别! ";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			LocatorReloadEnterDisable("mayak9", "boat", false);
			ref sld = characterFromId("GOT_Marshe");
			LAi_SetStayType(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakNextStage", 0, 0, 2, false);
			SetCharacterGoods(pchar, GOOD_CINNAMON, GetCargoGoods(pchar, GOOD_CINNAMON) + sti(pchar.questTemp.Guardoftruth.VanilleQty));
			AddQuestRecord("Guardoftruth", "21");
		break;
		
		case "guardoftruth_5":
			dialog.text = "是的, 先生。 这是帕德雷.文森特的信, 他对你非常满意, 其余的你可以从信中得知。 ";
			link.l1 = "太好了。 " + npchar.name+ ", 后会有期, 现在告辞了。 ";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_exit";
			GiveItem2Character(pchar, "specialletter");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_next";
		break;
		
		case "guardoftruth_7":
			dialog.text = "很好, 把它们给我, 我会带给神父。 ";
			link.l1 = "没门, 伙计! 弄到这些东西不容易, 我不会就这么交出去, 我要亲自交给帕德雷.文森特。 ";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "但是先生! 我怎么知道你不是在骗我? ";
			link.l1 = "看看吧: 香炉。 圣杯和带天青石的十字架... " + npchar.name+ ", 你以为我是谁? 你真觉得我蠢到不带这些东西就去宗教法庭吗? ";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "原谅我, 先生... 明天来, 我会告诉帕德雷.文森特你来了。 ";
			link.l1 = "好的, 明天见。 ";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			pchar.questTemp.Guardoftruth = "mayak_wait";
			SetFunctionTimerCondition("GuardOT_MayakLastStage", 0, 0, 1, false);
		break;
		
		case "guardoftruth_11":
			dialog.text = "大人会接见你, 先生。 别耽误了, 这是文件, 给卫兵看, 他们会让你进去, 但先升起西班牙国旗, 否则士兵可能会逮捕你。 ";
			link.l1 = "知道了, 挂西班牙旗。 谢了, 兄弟! 我这就去! ";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			DialogExit();
			GiveItem2Character(pchar, "VerifyPaper");
			ChangeItemDescribe("VerifyPaper", "itmdescr_VincentoPaper");
			pchar.questTemp.Guardoftruth = "santiago";
			AddQuestRecord("Guardoftruth", "34");
			AddCharacterExpToSkill(pchar, "Fortune", 200);//运气
			AddCharacterExpToSkill(pchar, "Sneak", 400);//隐匿
			GuardOT_SetPadreVincento();
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}