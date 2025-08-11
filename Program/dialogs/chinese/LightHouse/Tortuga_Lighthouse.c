// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你想要什么? ", "你想知道什么? "), "您需要什么, " + GetAddress_Form(NPChar) + "? ", "这已经是你第三次试图问我... ", "我受够你了, 滚! ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("抱歉, 我改变主意了。 ", "没什么, 抱歉。 "), "我忘了, 抱歉... ",
                      "事不过三, 对吧? 对不起... ", "对不起, 对不起! 那我就告辞了... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
        break;
    }
    UnloadSegment(NPChar.FileDialog2); 
}