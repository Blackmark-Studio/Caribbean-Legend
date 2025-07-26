// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你觉得我们的堡垒如何? 看起来很不错, 是吧? 驻军也毫不逊色, 哈…", "堡垒里士兵的生活相当乏味…站岗。 巡逻。 睡觉。 休息, 然后周而复始。 但城里就不一样了…你想做什么, " + GetAddress_Form(NPChar) + "? "), "别用愚蠢的问题打扰士兵, " + GetAddress_Form(NPChar) + "…", "今天你已经是第三次想问我了…",
                          "当兵不容易, 可你又来"+ GetSexPhrase(", 混蛋, ", " ") +"想惹我生气。 小心点, 不然你会被关进堡垒的地下室…", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了, 抱歉打扰你。 ", "我没什么想说的了, 抱歉。 "), "你说得对, 我道歉。 ",
                      "你说得对, 已经是第三次了。 请原谅。 ", "抱歉, 没什么事。 ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 若switch内部某处通过return退出, 切记执行卸载
}