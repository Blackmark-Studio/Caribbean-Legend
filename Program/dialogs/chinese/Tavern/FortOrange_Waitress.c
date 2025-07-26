// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("有什么问题吗, " + GetAddress_Form(NPChar) + "? ", "我能为你提供什么帮助, " + GetAddress_Form(NPChar) + "? "), "" + GetSexPhrase("嗯, 你有什么打算, " + GetAddress_Form(NPChar) + "? ", "又是这些奇怪的问题? 伙计, 去喝杯朗姆酒什么的吧... ") + "", "一整天下来, 这已经是你第三次问这类问题了... " + GetSexPhrase(" 这是在引起注意吗? ", ""),
                          "我猜你又有问题要问吧, " + GetAddress_Form(NPChar) + "? ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了", "我现在没什么想聊的。 "), "不, 没什么要紧的... ",
                      "没门儿, 亲爱的... ", "不, 什么问题? ... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            if (pchar.questTemp.Slavetrader == "FindRatJamaica_W")
            {
                link.l1 = "听着, 女士, 他们说你和我的老伙计弗朗索瓦.贡捷关系很近。 非常近... ";
                link.l1.go = "Jamaica_ratW_1";
            }
			
            if (pchar.questTemp.Slavetrader == "FindRatJamaica_WP")
            {
                if (CheckCharacterItem(pchar, "jewelry43"))
                {
                    link.l1 = "我把你镶宝石的项链带来了。 给你。 愿上帝保佑我以后别再遇到像你这样贪婪的女人。 ";
                    link.l1.go = "Jamaica_ratW_5";
                }
                else
                {
                    link.l1 = "目前没什么。 我在找你的项链。 ";
                    link.l1.go = "exit";
                }
            }
			
        break;
        
        case "Jamaica_ratW_1":
            dialog.text = "是的, 我们关系很近。 那又怎样? 我不是已婚妇女, 我想和谁在一起就和谁在一起。 弗朗索瓦是个非常体面的水手, 不像我们当地的渔民和农民。 他很... 哦! 而且他给了我很多漂亮的礼物! ";
            link.l1 = "好了, 够了! 我知道我伙计的优点, 你不用给我一一列举。 我不在乎你们之间发生了什么。 你们甚至可以结婚, 我不在乎。 我需要马上找到他, 明白吗? 你知道他去哪儿了吗? ";
            link.l1.go = "Jamaica_ratW_2";
        break;
        
        case "Jamaica_ratW_2":
            dialog.text = "嘻嘻... 你是他的伙伴, 却不知道他去哪儿了。 真有趣! ";
            link.l1 = "这没什么有趣的, 女士。 我们约好在牙买加见面, 然后一起航行... 如果你明白我的意思。 我一个人做不到, 而他却不知去向! ";
            link.l1.go = "Jamaica_ratW_3";
        break;
        
        case "Jamaica_ratW_3":
            dialog.text = "我明白了。 好吧, 考虑到你和弗朗索瓦是朋友, 而且有这么赚钱的航行机会... 我会告诉你他去哪儿了, 但需要一点报酬。 ";
            link.l1 = "好, 我知道规矩。 你想要多少? ";
            link.l1.go = "Jamaica_ratW_4";
        break;
        
        case "Jamaica_ratW_4":
            dialog.text = "哦, 真是贪财! 我不需要钱。 不, 我想要点特别的。 弗朗索瓦答应给我一条漂亮的镶宝石项链。 我已经跟朋友们吹嘘过了, 可他直接走了... 把那个吊坠给我, 我就告诉你他去哪儿了, 嘿嘿! ";
            link.l1 = "你这个厚脸皮的荡妇! 你们荷兰女人真是贪婪至极! 好吧, 你会得到你的项链。 ";
            link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "21_5");
            pchar.questTemp.Slavetrader = "FindRatJamaica_WP";
        break;
        
        case "Jamaica_ratW_5":
            dialog.text = "啊, 真漂亮! 现在我的朋友们该嫉妒得发疯了! ";
            link.l1 = "替我向她们表示哀悼。 现在开始说吧。 弗朗索瓦去哪儿了? ";
            link.l1.go = "Jamaica_ratW_6";
            RemoveItems(PChar, "jewelry43", 1);
        break;
        
        case "Jamaica_ratW_6":
            dialog.text = "好的, 当然, 先生。 弗朗索瓦已经起航前往古巴的哈瓦那了。 ";
            link.l1 = "谢谢你这个昂贵的提示, 荡妇。 这就是我想知道的。 ";
            link.l1.go = "exit";
            AddQuestRecord("Slavetrader", "21_6");
            pchar.questTemp.Slavetrader = "FindRatHavana";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}