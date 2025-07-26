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
        break;
        
        case "Gravel1":
            dialog.text = "我能为你做什么, 我的孩子? ";
            link.l1 = "我在找你, 乔治。 ";
            link.l1.go = "Gravel2";
            DelLandQuestMark(npchar);
        break;
        
        case "Gravel2":
            dialog.text = "找我? 但为什么? ";
            link.l1 = "朗威和范.默登先生需要你再去调查一次。 朗威在他上次…巡视之后, 不能在这里露面。 ";
            link.l1.go = "Gravel3";
        break;
        
        case "Gravel3":
            AddQuestRecord("PZ", "23");
            dialog.text = "看在上帝的份上, 小点声! 但我明白。 我会尽力的。 ";
            link.l1 = "太好了, 乔治。 你是我们最有价值的盟友之一。 回头见。 ";
            link.l1.go = "Exit";
            DelMapQuestMarkCity("Charles");
            
            pchar.questTemp.PZ_Etap5_Start = true;
            
            if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
            {
                PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
                PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
                PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
                AddMapQuestMarkCity("Pirates", false);
            }
            if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1 && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
            {
                PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
                PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
                PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
                AddMapQuestMarkCity("Pirates", false);
            }
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 若switch内部某处通过return退出, 切记执行卸载
}