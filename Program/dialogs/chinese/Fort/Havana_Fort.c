// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你觉得我们的堡垒如何? 看起来不错, 对吧? 驻军也不差, 哈... ", "堡垒士兵的生活相当枯燥... 守卫。 巡逻。 睡觉。 休息, 然后周而复始。 但城里就不一样了... 你想要什么, " + GetAddress_Form(NPChar) + "? "), "用愚蠢的问题打扰士兵可不受欢迎, " + GetAddress_Form(NPChar) + "... ", "今天你已经是第三次想问我了... ",
                          "当兵不容易, 而你又来"+ GetSexPhrase(", 混蛋, ", " ") +"想惹我生气。 小心点, 不然你会被关进堡垒的地下室... ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了, 抱歉打扰你。 ", "我没什么可说的, 抱歉。 "), "你说得对, 我道歉。 ",
                      "你说得对, 已经第三次了。 请原谅。 ", "抱歉, 没什么。 ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}