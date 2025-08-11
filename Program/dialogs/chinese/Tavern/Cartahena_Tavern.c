// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat("关于" + GetCityName(npchar.city) + "的所有传闻都为你效劳。 你想了解什么? ",
                          "我们刚才还在说这个。 你一定是忘了... ", "这已经是你第三次来烦我了... ",
                          "你像只鹦鹉一样重复同样的话... ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("你知道吗, " + Npchar.name+ ", 也许下次吧。 ", "对, 不知怎么的我忘了... ",
                      "是的, 确实是第三次了... ", "嗯... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && !CheckAttribute(npchar, "quest.gonsales"))
            {
                link.l1 = "我在找恩里克.冈萨雷斯。 你能告诉我怎么找到他吗? ";
                link.l1.go = "saga";                
            }
        break;
			
        case "saga":
            dialog.text = "每个人都认识冈萨雷斯先生! 他的房子在港务局旁边。 ";
            link.l1 = "他多大年纪了? ";
            link.l1.go = "saga_1";
        break;
        
        case "saga_1":
            dialog.text = "嗯, 我不太确定, 但他看起来至少五十岁了。 他在那栋房子里住了很长时间。 他喜欢讲各种各样关于海盗的荒诞故事, 可能这些故事他只在梦里见过。 ";
            link.l1 = "看来他就是我要找的人。 谢谢你, " + npchar.name+ ", 你帮了大忙! ";
            link.l1.go = "saga_2";
        break;
        
        case "saga_2":
            DialogExit();
            npchar.quest.gonsales = "true";
            pchar.questTemp.Saga.Gonsales = "true";
            pchar.quest.Saga_Gonsales1.win_condition.l1 = "location";
            pchar.quest.Saga_Gonsales1.win_condition.l1.location = "Cartahena_houseF2";
            pchar.quest.Saga_Gonsales1.function = "Saga_CreateGonsalesA";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}