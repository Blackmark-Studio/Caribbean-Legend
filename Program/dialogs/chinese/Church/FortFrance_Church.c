// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么样的问题啊, " + GetSexPhrase("我的孩子", "我的孩子") + "? ", "但说无妨, 我在听着呢…"), "我在听呢, 现在就说吧, " + GetSexPhrase("我的孩子", "我的孩子") + "…", "这都第三次了, " + GetSexPhrase("我的孩子", "我的孩子") + ", 需要什么就直说。 ",
                          "神职人员事务繁多, 你这是在打扰我呢, " + GetSexPhrase("我的孩子", "我的孩子") + "…", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改主意了…", "现在先不问了, 神父…"), "没什么想说的了, 抱歉。 ",
                      "我回头再问吧, 神父, 还请原谅。 ", "恕罪, 神父…", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            // Jason 地久天长
            if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "choose" && !CheckAttribute(npchar, "quest.LongHappy"))
            {
                link.l1 = "神父, 我在找贝努瓦院长, 有急事找他。 您能告诉我去哪里能找到他吗? ";
                link.l1.go = "LH_church";
            }
        break;
        
        // Jason 地久天长
        case "LH_church":
            dialog.text = "贝努瓦院长因教会事务离开了城市, 与西班牙天主教使团在新大陆的代表会面。 我不清楚具体细节, 但院长离开已久, 恐怕谈判被拖延了, 或者途中出了什么事。 我们都很不安, 但只能祈祷并等待消息。 ";
            link.l1 = "看来事情并不简单。 神父, 您能告诉我贝努瓦院长具体去了哪里吗? 我需要尽快找到他。 ";
            link.l1.go = "LH_church_1";
        break;
        
        case "LH_church_1":
            dialog.text = "恐怕不行, 我的孩子。 据我所知, 贝努瓦院长去和新西班牙的主教以及宗教裁判所的神父文森特.帕洛蒂谈判了, 但他没说会议在哪里举行。 ";
            link.l1 = "这就够了, 神父, 谢谢您。 我对帕洛蒂神父有所了解…我会去圣地亚哥找找看。 ";
            link.l1.go = "LH_church_2";
        break;
        
        case "LH_church_2":
            DialogExit();
            npchar.quest.LongHappy = "true";
            LongHappy_GoToSantiago();
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 若switch内部某处通过return退出, 切记执行卸载
}