// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat("关于" + GetCityName(npchar.city) + "的所有传闻都为您效劳。 您想了解什么? ",
                          "我们刚才还在说这个呢。 您一定是忘了... ", "今天这已经是您第三次问这类问题了... ",
                          "您像只鹦鹉一样反复问同样的话... ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("您知道吗, " + Npchar.name+ ", 或许下次吧。 ", "对, 不知怎么的我就忘了... ",
                      "是的, 确实是第三次了... ", "嗯... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince")
            {
                link.l1 = "告诉我, 最近有没有一艘名为‘圣玛格丽塔号’的大帆船停靠在你们的殖民地? 也许是作为私掠船的战利品? ";
                link.l1.go = "guardoftruth";
            }
            //--> 被窃的记忆
            if (CheckAttribute(pchar, "questTemp.UV_DialogCitizen"))
            {
                link.l1 = "特里斯坦.雷尼尔最近来过这里吗? ";
                link.l1.go = "UV_DialogTavern";
            }
            //<—— 被窃的记忆
        break;
        
        case "guardoftruth":
            dialog.text = "伙计, 很少有人带着战利品停靠我们的殖民地, 而且我们也没见过那样名字的大帆船。 伊斯帕尼奥拉是个荒凉的岛屿, 我们只是个小殖民地。 这里很安静。 我们和高地的海盗交易牛皮和牛肉干。 私掠船通常不会在这里逗留, 我们这里没有妓院, 而且西班牙人就在附近。 去别的地方找你的大帆船吧。 ";
            link.l1 = "明白了。 谢谢你的建议! ";
            link.l1.go = "exit";
            AddQuestRecord("Guardoftruth", "7");
            pchar.questTemp.Guardoftruth = "tortuga";
        break;
        
        //--> 被窃的记忆
        case "UV_DialogTavern":
            dialog.text = "雷尼尔? 是的, 他不仅来过这里, 而且还没离开。 他租了个房间。 ";
            link.l1 = "幸运之神眷顾我! 我和这位好船长的事刻不容缓 --他的隐私必须为急事让路。 我能在哪个房间找到他? ";
            link.l1.go = "exit";
            AddDialogExitQuestFunction("UV_GoldSeagull_RoomInTavern");
            DelLandQuestMark(npchar);
        break;
        //<-- 被窃的记忆

    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}