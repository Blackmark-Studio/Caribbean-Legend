// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch(Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = "说吧, 我在听";
            link.l1 = "我搞错了。 再见。 ";
            link.l1.go = "Exit";
            // 肺结核的代价
            if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin")
            {
                link.l1 = "我听说这里爆发了流行病, 对吗? ";
                link.l1.go = "Consumption";
            }
        break;
        
        //--> 肺结核的代价
        case "Consumption":
            dialog.text = "你说得对, 所以没有重要原因就别去地牢。 你为什么对这事感兴趣? ";
            link.l1 = "只是好奇。 那么, 如果我的手下喝得太醉, 太吵, 最后被关到这里, 我是不是该准备些黄色亚麻布? ";
            link.l1.go = "Consumption_1";
        break;
        
        case "Consumption_1":
            dialog.text = "唉, 先生, 如果你在开玩笑, 我没听懂。 地牢又湿又冷, 你也知道这里的气候。 肺结核在地牢里是常客。 我甚至得付钱给手下, 让他们把食物送到牢房里。 在那里巡逻被认为和服苦役一样。 ";
            link.l1 = "对不起, 我只是想知道, 情况有多严重? ";
            link.l1.go = "Consumption_2";
        break;
        
        case "Consumption_2":
            dialog.text = "非常严重。 我们这里连个医生都没有, 他也死于该死的肺结核。 现在只有当地驻军的一名军医每周检查一次囚犯。 但谁会在乎这些流浪汉和罪犯呢? \n大多数人认为他们罪有应得, 很难反驳这一点。 ";
            link.l1 = "我的医学知识有限, 但据我所知, 肺结核虽然危险致命, 但不会像这里这样几天内就致人死亡。 受害者不是应该痛苦几个月甚至几年吗? ";
            link.l1.go = "Consumption_3";
        break;
        
        case "Consumption_3":
            dialog.text = "正如你刚才提到的, 你不是医生, 所以谈论疾病的特征可能只是... 编造的谎言。 我只是重复了我们的医生在被疾病夺走生命之前所说的话。 所以我不理解你的好奇心和愤世嫉俗的行为。 这里有人死去! ";
            link.l1 = "你不是刚说他们罪有应得吗? ";
            link.l1.go = "Consumption_4";
        break;
        
        case "Consumption_4":
            dialog.text = "够了, 先生! 我认为你和我有其他事情要做, 而不是比拼智慧。 门就在你身后。 ";
            link.l1 = "好吧, 请原谅我的冒昧, 我这就走。 ";
            link.l1.go = "Consumption_5";
        break;
        
        case "Consumption_5":
            DialogExit();
            npchar.quest.Consumption = "true";
            pchar.questTemp.Consumption.Commandant = "true";
            AddQuestRecord("Consumption", "3");
            pchar.quest.Consumption.win_condition.l1 = "location";
            pchar.quest.Consumption.win_condition.l1.location = "PortSpein_houseF2";
            pchar.quest.Consumption.function = "Consumption_CommandantHouse";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}