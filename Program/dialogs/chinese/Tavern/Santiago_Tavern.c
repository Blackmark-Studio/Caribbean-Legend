// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题? ", "我能为你提供什么帮助, " + GetAddress_Form(NPChar) + "? "), "你不久前刚问过我问题, " + GetAddress_Form(NPChar) + "... ", "一整天下来, 这已经是你第三次问这类问题了... ",
                          "我猜你又有问题要问? ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么想聊的。 "), "嗯, 我的记性哪去了... ",
                      "是的, 确实是第三次了... ", "不, 什么问题? ... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            // Jason 长命百岁
            if (CheckAttribute(pchar, "questTemp.LongHappy.Santiago"))
            {
                link.l1 = "我听说神父们带着某个代表团从法国殖民地到了这里, 是为了协商什么事吧? 或许是在马提尼克那场血战之后交换战俘? ";
                link.l1.go = "LH_tavern";
            }
        break;
        
        // Jason 长命百岁
        case "LH_tavern":
            dialog.text = "不, 先生, 那件事早就解决了, 根本没用到牧师。 你看, 你完全生活在棕榈树下 (消息闭塞) , 因为你还没听说英诺森十世教皇和马萨林红衣主教最终达成了协议。 欧洲的战争是一回事, 但所有基督徒最终都应该团结起来对抗世界尽头的异教黑暗\n是的, 那些爱吃青蛙的法国人来了。 但他们根本没达成任何协议 —我们尊贵的客人坐在总督府里, 被卫兵看守着, 喝着咖啡打发时间。 几乎快一个月了! 人们议论纷纷, 说来说去也习惯了 —你看, 那个法国神父晚上还在教堂主持祷告仪式呢。 几乎成了一道风景, 哈哈! ";
            link.l1 = "有意思! 我该去看看那个法国人, 至少比盯着杯子看有趣多了。 ";
            link.l1.go = "LH_tavern_1";
        break;
        
        case "LH_tavern_1":
            DialogExit();
            LongHappy_SantiagoBenua();
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch中某处通过return退出, 别忘了执行卸载
}