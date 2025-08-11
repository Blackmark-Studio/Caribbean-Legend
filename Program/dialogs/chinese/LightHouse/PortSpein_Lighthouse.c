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
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "听着, 1654年4月, 米格尔.迪乔索指挥的一艘护卫舰曾在这附近出现, 后来就消失了。 你能多告诉我一些关于他那艘船的事吗? 也许你看到了发生了什么或者它去了哪里? 你还记得什么吗? ";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "哦吼... 是的, 先生, 那可真是个奇观! 这种事谁都不会忘记, 哈哈! ";
			link.l1 = "你能告诉我发生了什么吗? ";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "迪乔索先生的护卫舰在圣何塞港抛了锚。 我看得很清楚, 没错。 跟你说, 那是一艘极好的护卫舰, 一件杰作, 我敢发誓! 船员们吹嘘它的速度, 能达到十六节! \n他们在这儿待了一天, 然后就朝着多巴哥岛起航了。 然后, 你都不敢相信, 他们刚消失在地平线后, 天气就开始出现怪事。 当时好几天天气都很好, 一朵云都没有! \n可突然就来了这场可怕的风暴, 看起来就像海神尼普顿亲自到访一样! 我爬上灯塔顶部去点灯, 然后就看到了她... ‘圣基特里亚号’! 她在巨大的海浪中疾驰, 旁边还有一个巨大的龙卷风! \n那艘护卫舰像火花一样从我的灯塔旁飞过, 然后被风暴卷向了西北方向! 从那以后就没人再见过‘圣基特里亚号’。 仅仅一个小时后, 风停雨住, 云散日出, 一点风暴的痕迹都没有了! 我从未见过这样的事! 不过那天我从海湾里捡到了好多琥珀... ";
			link.l1 = "这么说风暴把护卫舰吹回加勒比海了? ";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "没错! 一直吹到了马提尼克岛那边。 我怀疑迪乔索没能在那场风暴中幸存下来, 不过他已经尽力了! 那艘护卫舰没沉, 但‘圣基特里亚号’现在肯定已经沉在珊瑚丛里了... 其实你不是第一个问起迪乔索和他那艘护卫舰的人。 ";
			link.l1 = "真的吗? 还有谁对米格尔感兴趣? ";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "是西班牙舰队的一个时髦船长, 而且来头不小! 他自称... 哦... 我忘了... 啊! 迭戈先生, 他叫迭戈, 不过姓氏... 德.蒙塔尼亚还是德.蒙托亚, 差不多这样。 他当时就像你一样听我讲, 谢过我之后就走了, 之后再也没见过他。 ";
			if (sti(Pchar.money) >= 5000)
			{
				link.l1 = "明白了。 非常感谢你讲的故事, 你帮了我大忙。 这是我的一点心意。 再见。 ";
				AddMoneyToCharacter(pchar, -5000);
				AddCharacterExpToSkill(pchar, "Leadership", 250);
			}
			else
			{
				link.l1 = "明白了。 非常感谢你讲的故事, 你帮了我大忙。 再见。 ";
			}
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			AddQuestRecord("Guardoftruth", "41");
			pchar.questTemp.Guardoftruth.Trinidad = "mayak";
			pchar.quest.GuardOT_setDiego.win_condition.l1 = "ExitFromLocation";
			pchar.quest.GuardOT_setDiego.win_condition.l1.location = pchar.location;
			pchar.quest.GuardOT_setDiego.function = "GuardOT_SetDiegoOnMayak";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}