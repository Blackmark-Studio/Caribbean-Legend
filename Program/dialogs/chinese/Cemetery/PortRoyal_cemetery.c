// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("我能为你提供什么帮助? ", "有什么可以为你效劳的? "), "告诉我, " + GetAddress_Form(NPChar) + ", 是什么困扰着你? ", "这已经是第三次了, " + GetAddress_Form(NPChar) + ", 你到底需要什么? ", "我受够你了, 滚出去! ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了, 抱歉。 ", "没什么事, 打扰了。 "), "请原谅我, 没什么要紧的。 ",
                      "你说得对, 已经第三次了。 请宽恕我... ", "抱歉。 ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
        break;
    }
    UnloadSegment(NPChar.FileDialog2); 
}