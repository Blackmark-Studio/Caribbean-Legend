// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题? ", "我能为你提供什么帮助, " + GetAddress_Form(NPChar) + "? "), "你不久前刚问过我问题, " + GetAddress_Form(NPChar) + "... ", "一整天下来, 这已经是你第三次问这类问题了... ",
                          "我猜你又有问题要问? ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么想聊的。 "), "嗯, 我的记性哪去了... ",
                      "是的, 确实是第三次了... ", "不, 什么问题? ... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";            
            if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "听着, 你见过一个叫弗朗索瓦.贡捷的私掠者吗? 他最近来过你们镇。 ";
                link.l1.go = "Portobello_rat_1";
            }            
            // 加勒比习俗
            if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && !CheckAttribute(npchar, "quest.trial"))
            {
                link.l1 = "听着, 你能告诉我去哪里找一个叫海梅.西利西奥的商人吗? 他应该来见你... ";
                link.l1.go = "trial";
            }
            // Addon-2016 Jason FMK-瓜德罗普
            if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && !CheckAttribute(npchar, "quest.FMQG"))
            {
                link.l1 = "听着, 我在找一个叫贝特朗.皮内特的人, 你听说过他吗? 他不久前到了贝洛港。 一个戴着卷发假发的威风绅士, 做贸易的, 可能来过这里... ";
                link.l1.go = "FMQG";
            }
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Tavern_1"))
            {
                link.l1 = "你知道我在哪儿能找到玛丽萨·卡尔德拉吗? ";
                link.l1.go = "LFD_Tavern_1_1";
            }
			//<-- Письмо от покойника
        break;
        
        case "Portobello_rat_1":
            dialog.text = NPCStringReactionRepeat("不, 不认识。 他没去过酒馆, 我在镇上也没见过他。 ", "你已经问过这个问题了, 我也回答过了。 ", "我告诉过你‘你已经问过那个贡捷了’。 ", "听着, 走开别烦我! 你是不是完全昏了头? ", "block", 0, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("那好吧, 我会继续找。 ", "嗯, 我想是这样... ", "是的, 对, 我问过... ", "抱歉, " + npchar.name+ "... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
        break;        

        case "trial":
            DelLandQuestMark(npchar);
            npchar.quest.trial = true;
            
            dialog.text = "原谅我, 先生, 但只有叛徒或醉汉才会和陌生人讨论这种事。 我不想惹麻烦。 ";
            link.l1 = "你说醉汉? 回头见, 伙计。 ";
            link.l1.go = "exit";
        break;
        
        // Addon-2016 Jason FMK-瓜德罗普
        case "FMQG":
            dialog.text = "从没听说过他, 伙计。 ";
            link.l1 = "他是唐.卡洛斯.德.米利亚的熟人。 你确定从没听说过他? ";
            link.l1.go = "FMQG_1";
        break;
        
        case "FMQG_1":
            dialog.text = "确定。 如果他是德.米利亚的朋友, 就去找总督, 问问卡洛斯先生。 他会告诉你这个商人的情况。 ";
            link.l1 = "我会的。 谢谢你的建议! ";
            link.l1.go = "FMQG_2";
        break;
        
        case "FMQG_2":
            DialogExit();
            AddQuestRecord("FMQ_Guadeloupe", "9");
            npchar.quest.FMQG = true;
        break;
		
		//--> Письмо от покойника
		case "LFD_Tavern_1_1":
			dialog.text = "马丽萨? 哼…… 我好久没见到她了。自从她得知丈夫去世的消息后, 就再也没在城里露面。";
			link.l1 = "所以, 她成了寡妇? ";
			link.l1.go = "LFD_Tavern_1_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LFD_Tavern_1_2":
			dialog.text = "是的。她丈夫曾是商船“破浪者号”的船长。凭借荷兰西印度公司的许可证, 他几乎可以进入整个群岛的所有港口。传言说他在从伯利兹前往卡普斯特维尔途中遭遇海盗袭击, 不幸遇难。类似的事在这片海域并不少见, 但对她来说却是沉重的打击。";
			link.l1 = "那她就这么消失了? ";
			link.l1.go = "LFD_Tavern_1_3";
		break;
		
		case "LFD_Tavern_1_3":
			dialog.text = "嗯, 说她‘消失了’有点夸张。但从那以后, 她几乎不再出现在城里。不过, 奇怪的是…… 时不时有男人打听她。就像你一样, 船长。如果她不是那么虔诚, 我都以为她…… 是躲了起来, 靠别的手段谋生。但马丽萨在丈夫死前, 从不缺席任何一次弥撒, 几乎住在教堂里, 所以这种可能性不大。";
			link.l1 = "就这些? 你就知道这么多? ";
			link.l1.go = "LFD_Tavern_1_4";
		break;
		
		case "LFD_Tavern_1_4":
			dialog.text = "我知道的就这些了, 船长。";
			link.l1 = "...";
			link.l1.go = "LFD_Tavern_1_5";
		break;
		
		case "LFD_Tavern_1_5":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Tavern_1");
		break;
		//<-- Письмо от покойника
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}