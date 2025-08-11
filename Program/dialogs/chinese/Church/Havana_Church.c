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
            // 卡莱乌切
            if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana")
            {
                ref sld = characterFromId("Villemstad_Priest");
                link.l1 = "神父您好。 威廉斯塔德教堂的院长"+sld.name+"派我来的。 您曾告诉他在古巴的一个山洞里看到了奇怪的景象。 ";
                link.l1.go = "caleuche";
            }
            if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana1")
            {
                link.l1 = "神父, 我已经去过丛林里的那个山洞了。 ";
                link.l1.go = "caleuche_4";
            }
        break;
        
        case "caleuche":
            dialog.text = "感谢上帝, 他终于留意到了! 我一听到关于活死人的传言, 就立刻通知了圣地亚哥的宗教裁判官文森特神父大人。 他答应会调查, 但至今仍未采取行动! 恐怕神父大人还有更重要的事务要处理…";
            link.l1 = "我会亲自去调查。 再说了, 这些传言不过是喝醉的猎人胡说八道罢了 —所以宗教裁判所才没把它们当回事。 我会去丛林里亲眼看看。 ";
            link.l1.go = "caleuche_1";
        break;
        
        case "caleuche_1":
            dialog.text = "我向你保证, 我的孩子, 这很重要。 告诉我活死人之事的那个人, 我可以用性命担保他的话。 ";
            link.l1 = "那好吧, 我会准备战斗。 如果那些邪恶的生物真的在山洞里扎根了, 我会把它们从这个世界清除掉。 ";
            link.l1.go = "caleuche_2";
        break;
        
        case "caleuche_2":
            dialog.text = "带着主的祝福出发吧, 我的孩子! 拿着这个圣化的护身符, 它会帮助你完成任务。 去吧, 消灭那些邪恶的造物! ";
            link.l1 = "再见, "+npchar.name+"神父。 我一完成任务就立刻回来见您。 ";
            link.l1.go = "caleuche_3";
        break;
        
        case "caleuche_3":
            DialogExit();
            AddQuestRecord("Caleuche", "27");
            pchar.questTemp.Caleuche = "cave";
            Log_Info("你获得了一枚教会护身符");
            PlaySound("interface\important_item.wav");
            GiveItem2Character(pchar, "amulet_7"); 
            if (GetCharacterIndex("cavehunter") != -1)
            {
                sld = characterFromId("cavehunter");
                sld.dialog.currentnode = "cavehunter_5";
                LAi_SetGuardianType(sld);
                sld.protector = true;
                LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
            }
            LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", false);
            pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1 = "location";
            pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1.location = "Cuba_CaveEntrance";
            pchar.quest.Caleuche_cuba_caveentrance.function = "Caleuche_CubaCaveEntrance";
        break;
        
        case "caleuche_4":
            dialog.text = "你看到了什么, 我的孩子? 我们的担心是多余的吗? ";
            link.l1 = "恐怕不是, "+npchar.name+"神父。 山洞里爬满了不死生物, 但在上帝的帮助下, 我胜利归来。 它们再也不会打扰任何人了。 ";
            link.l1.go = "caleuche_5";
        break;
        
        case "caleuche_5":
            dialog.text = "赞美主! 你真是他的惩戒之剑, 我的孩子! 请允许我代表哈瓦那全体教区居民向你表达最深切的感谢。 请接受这些圣化的护身符, 作为感谢的象征。 在你危险的旅途中, 它们肯定会派上用场。 ";
            link.l1 = "谢谢你, "+npchar.name+"神父。 ";
            link.l1.go = "caleuche_6";
        break;
        
        case "caleuche_6":
            Log_Info("你获得了教会护身符");
            PlaySound("interface\important_item.wav");
            GiveItem2Character(pchar, "amulet_3"); 
            GiveItem2Character(pchar, "amulet_9"); 
            GiveItem2Character(pchar, "obereg_7"); 
            GiveItem2Character(pchar, "obereg_11"); 
            dialog.text = "此外, 我会确保平民和贵族都知道你的英雄事迹, 并且我会日夜不停地为你祈祷。 ";
            link.l1 = "谢谢你, 神父。 我还有一个问题要问。 ";
            link.l1.go = "caleuche_7";
        break;
        
        case "caleuche_7":
            dialog.text = "问吧, 我的孩子。 ";
            link.l1 = "告诉我, "+npchar.name+"神父, 最近有没有一个叫约阿希姆.梅里曼的人来到你们镇上? 中年绅士, 葡萄牙人, 留着小胡子。 帝王式胡须和锐利的眼睛? ";
            link.l1.go = "caleuche_8";
        break;
        
        case "caleuche_8":
            sld = characterFromId("Villemstad_Priest");
            dialog.text = "名字和相貌都没印象, 很抱歉。 这个人是谁? ";
            link.l1 = "梅里曼是个男巫。 宗教裁判所追捕他很久了。 "+sld.name+"神父和我怀疑古巴活死人的出现是他的杰作。 不久前他还住在威廉斯塔德, 然后突然消失了。 不久之后, 收留他的那个女人就变成了行走的骷髅。 ";
            link.l1.go = "caleuche_9";
        break;
        
        case "caleuche_9":
            dialog.text = "真是噩梦! 我会立刻通知宗教裁判官, 通知文森特神父本人! 他必须知道这里发生的事! 告诉我, 我的孩子, 你觉得丛林里失踪的那些人…? ";
            link.l1 = "的确, 我几乎可以肯定山洞里的那些活死人就是你们以前的市民。 我想在古巴找到这个葡萄牙人, 让他受到惩罚! 那个恶棍弄到了一件古老的异教遗物 —尤姆.奇米尔的玉头骨。 如果没有人尽快阻止他, 恐怕有了这件神器和印第安巫术, 梅里曼会制造更多麻烦。 ";
            link.l1.go = "caleuche_10";
        break;
        
        case "caleuche_10":
            dialog.text = "你认为不死生物还会再出现吗? ";
            link.l1 = "几乎可以肯定。 我不确定是什么在驱使他, 但他的野心肯定不是善良的。 ";
            link.l1.go = "caleuche_11";
        break;
        
        case "caleuche_11":
            dialog.text = "愿全能的主怜悯我们! 去找他吧, 我的孩子! 我以我们神圣教会的名义, 允许你对他采取任何措施! 我会立刻派一名信使去圣地亚哥, 向文森特神父汇报。 ";
            link.l1 = "你就这么做吧。 再见, "+npchar.name+"神父。 ";
            link.l1.go = "caleuche_12";
        break;
        
        case "caleuche_12":
            DialogExit();
            AddQuestRecord("Caleuche", "29");
            pchar.questTemp.Caleuche = "graveyard";
            AddCharacterMaxHealth(pchar, 3);
            ChangeCharacterComplexReputation(pchar, "nobility", 3);
            ChangeCharacterComplexReputation(pchar, "authority", 2);
            ChangeCharacterComplexReputation(pchar, "fame", 3);
            ChangeCharacterNationReputation(pchar, SPAIN, 10);
            AddCharacterExpToSkill(pchar, "Leadership", 500);
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 若switch内部某处通过return退出, 切记执行卸载
}