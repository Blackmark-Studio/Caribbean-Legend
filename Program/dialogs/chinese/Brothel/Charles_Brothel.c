// 城市对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么样的问题啊, " + GetSexPhrase("年轻人", "姑娘") + "? ", "你需要什么, " + GetSexPhrase("帅哥", "美女") + "? 问吧。 "), "又问问题? ", "嘻嘻, 要是你不介意的话 —接着问吧... ",
                          "" + GetSexPhrase("嗯, 你怎么不自己挑个美人呢? 我开始怀疑你了... ", "嗯, 你怎么不自己挑个美人呢? 恐怕我们这儿可没有男孩子哦, 嘻嘻... ") + "", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改主意了, 抱歉。 ", "其实, 算了... "), "我... 抱歉, 目前没什么问题了。 ",
                      "你说得对, 这都第三次了。 请原谅。 ", "也许下次吧, 夫人。 ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 若switch内部有通过return退出的情况, 别忘了执行卸载
}