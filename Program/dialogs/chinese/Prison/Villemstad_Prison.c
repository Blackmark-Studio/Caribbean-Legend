// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch(Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = "说吧, 我在听";
            link.l1 = "我搞错了。 再见。 ";
            link.l1.go = "Exit";
            // 葡萄牙人
            if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalInPrison")
            {
                link.l1 = "军官, 你们这里关押着一个名叫葡萄牙人巴托洛梅奥的囚犯... ";
                link.l1.go = "Portugal";
            }
        break;
        
        // 葡萄牙人
        case "Portugal":
            dialog.text = "我们确实关押着他。 你为什么关心这个? 只有荷兰西印度公司的使者并持有总督的书面命令才能见他。 现在公司的一名军官正在审问这个海盗。 所以如果你只是来见他的, 最好走开, 等他被绞死时你会看到他的, 现在走开。 ";
            link.l1 = "我来这里不是为了见他。 ";
            link.l1.go = "Portugal_1";
        break;
        
        case "Portugal_1":
            dialog.text = "如果可以的话, 请问你为什么来? ";
            link.l1 = "我来这里... 是为了救他! ";
            link.l1.go = "fight";
            chrDisableReloadToLocation = true;
            //pchar.quest.InMarigoResidenceOver.over = "yes"; // 移除计时器
            InterfaceStates.Buttons.Save.enable = false;// 禁止保存
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}