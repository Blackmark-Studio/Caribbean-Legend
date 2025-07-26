// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch(Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = "说吧, 我在听";
            link.l1 = "我搞错了。 再见。 ";
            link.l1.go = "Exit";
            // 插件2016-1 Jason海盗线
            if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_4")
            {
                link.l1 = "军官, 我注意到'坎塔夫罗'号的一名军官被关押在这里。 对吗? ";
                link.l1.go = "Mtraxx";
            }
            if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_8")
            {
                link.l1 = "我回来再次询问洛佩阁下的情况, 军官。 你已经收到释放他的命令了吗? ";
                link.l1.go = "Mtraxx_5";
            }
        break;
        
        // 插件2016-1 Jason海盗线
        case "Mtraxx":
            dialog.text = "坎塔夫罗号的军官? 洛佩.蒙托罗阁下? 是的, 他被关押在这里。 你有什么事? ";
            link.l1 = "我想获得探视他的许可。 ";
            link.l1.go = "Mtraxx_1";
            DelLandQuestMark(npchar);
            AddLandQuestMark(characterFromId("Lope"), "questmarkmain");
        break;
        
        case "Mtraxx_1":
            dialog.text = "对不起, 请问你凭什么要求探视? ";
            link.l1 = "只是个人私事。 我在欧洲就认识他, 听到他入狱的消息以及全镇流传的流言感到很震惊。 我想和他谈谈。 ";
            link.l1.go = "Mtraxx_2";
        break;
        
        case "Mtraxx_2":
            dialog.text = "嗯... ";
            link.l1 = "军官, 也许我可以... 为让我探视他而'感谢'你? ";
            link.l1.go = "Mtraxx_3";
        break;
        
        case "Mtraxx_3":
            dialog.text = "不必了。 我允许你会见蒙托罗阁下。 卫兵会让你过去的。 ";
            link.l1 = "谢谢! ";
            link.l1.go = "Mtraxx_4";
        break;
        
        case "Mtraxx_4":
            DialogExit();
            pchar.questTemp.jailCanMove = true;
            pchar.questTemp.Mtraxx = "jewelry_5";
        break;
        
        case "Mtraxx_5":
            dialog.text = "确实, 我的命令是直接将洛佩.蒙托罗阁下交给指挥官。 但我想他还要在牢房里待几个星期。 不过, 趁他还在这里, 你可以去看看他。 ";
            link.l1 = "谢谢你, 军官, 这正是我来的目的。 ";
            link.l1.go = "Mtraxx_6";
            DelLandQuestMark(npchar);
        break;
        
        case "Mtraxx_6":
            DialogExit();
            pchar.questTemp.jailCanMove = true;
            pchar.questTemp.Mtraxx = "jewelry_9";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}