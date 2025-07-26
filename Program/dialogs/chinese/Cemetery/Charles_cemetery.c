// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("我能为您做些什么? ", "有什么可以帮您的? "), "告诉我, " + GetAddress_Form(NPChar) + ", 什么事困扰着您? ", "这已经是第三次了, " + GetAddress_Form(NPChar) + ", 您需要什么? ", "我受够您了, 滚出去! ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了, 抱歉。 ", "没什么, 打扰了。 "), "请原谅我, 没什么事。 ",
                      "您说得对, 已经第三次了。 请原谅我... ", "抱歉。 ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
        break;
    }
    UnloadSegment(NPChar.FileDialog2); 
}