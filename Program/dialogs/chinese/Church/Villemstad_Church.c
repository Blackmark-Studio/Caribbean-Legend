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
            // 卡莱乌切 (幽灵船) 
            if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "priest")
            {
                link.l1 = "打扰了, 神父, 您教区的一位神职人员让我调查约阿希姆.梅里曼曾租住的那栋房子…";
                link.l1.go = "caleuche";
            }
        break;
        
        // 卡莱乌切 (幽灵船) 
        case "caleuche":
            dialog.text = "那么? 你去过那里了吗, 我的孩子? ";
            link.l1 = "去过了。 但说实话, 我宁愿没去过。 在上层房间里, 我遭到一个拿着巨大斧头的骷髅袭击。 尽管过程绝非易事, 但我最终还是胜利了。 ";
            link.l1.go = "caleuche_1";
        break;
        
        case "caleuche_1":
            dialog.text = "主啊, 怜悯我们的灵魂吧! 我最担心的事情还是发生了! ";
            link.l1 = "还不止这些, 神父。 当我终于打倒它时, 它发出了类似女人的尖叫声。 我在骨骼中发现了一些珠宝, 所以可以确定这是那位失踪的女房东。 ";
            link.l1.go = "caleuche_2";
        break;
        
        case "caleuche_2":
            dialog.text = "(在自己身上画十字)... 可怜的上帝仆人, 愿主让她的灵魂安息... ";
            link.l1 = "看来梅里曼确实是个巫师。 我完全不知道一个人如何能把活生生的人变成这种怪物。 ";
            link.l1.go = "caleuche_3";
        break;
        
        case "caleuche_3":
            dialog.text = "约阿希姆.梅里曼是个非常可怕的巫师, 我的孩子。 我在欧洲就认识他, 但那时他还做不出这种事。 在加勒比海这里, 他设法得到了某种赋予他超自然力量的东西。 ";
            link.l1 = "您认识梅里曼吗, 神父? ";
            link.l1.go = "caleuche_4";
        break;
        
        case "caleuche_4":
            dialog.text = "确实认识。 那时我还只是里斯本一个教区的谦卑神父。 约阿希姆.梅里曼是个富有的贵族, 后来他开始对水手从遥远国度带来的古老手稿和卷轴产生兴趣。 他还开始研究炼金术, 但一段时间后就隐居了。 \n人们看到他的房子里有闪光, 有时还能闻到奇怪的气味。 后来有人看到他夜里出现在墓地, 有一次甚至看到他挖出一具新鲜的尸体带回家。 当当地人的耐心耗尽后, 教区主教联系了宗教裁判所。 \n当卫兵撞开梅里曼的房门时, 他已经通过秘密通道逃跑了。 他们在地下室发现了一个实验室, 即使是经验丰富的士兵也对所见之物感到震惊和恶心: 整具腐烂和被肢解的尸体。 人类和动物的骨骼。 奇怪的东西... 对梅里曼的恐惧和憎恨如此之深, 以至于他的房子立刻被拆毁了。 \n梅里曼消失得无影无踪。 宗教裁判所开始搜寻他, 缺席判处他作为危险的巫师被处以火刑, 但始终没有找到他。 而现在, 这么多年后, 我在威廉斯塔德的街头又见到了他。 ";
            link.l1 = "那您为什么不告诉宗教裁判所的人? ";
            link.l1.go = "caleuche_5";
        break;
        
        case "caleuche_5":
            dialog.text = "我的孩子, 你不知道我们的教会与宗教裁判所不合吗? 我宁愿避开文森特神父和他的暴徒们。 ";
            link.l1 = "我明白了。 神父, 我想我知道梅里曼的力量从何而来了。 他得到了一件古老的神器, 一个玉制的死亡之神尤姆.西米利的头骨, 这是查文部落印第安人崇拜的古老死神。 ";
            link.l1.go = "caleuche_6";
        break;
        
        case "caleuche_6":
            dialog.text = "嗯, 梅里曼以对尸体进行巫术仪式和实验而闻名, 所以这很可能是真的。 感谢上帝, 这个可怕的男人已经离开了威廉斯塔德, 而且你摧毁了他试图在这里播下的邪恶种子。 我们非常感激你, 我的孩子。 请接受这些圣化的物品作为奖励。 ";
            link.l1 = "谢谢您, 神父。 ";
            link.l1.go = "caleuche_7";
        break;
        
        case "caleuche_7":
            Log_Info("你获得了教会护身符");
            PlaySound("interface\important_item.wav");
            GiveItem2Character(pchar, "amulet_2"); 
            GiveItem2Character(pchar, "amulet_6"); 
            GiveItem2Character(pchar, "amulet_8"); 
            GiveItem2Character(pchar, "amulet_10"); 
            ref sld = characterFromId("Havana_Priest");
            dialog.text = "但我们的麻烦还没结束, 我的孩子。 最近我收到了 "+sld.name+" 的信, 他是哈瓦那教会的主教。 他带来了可怕的消息: 在古巴丛林的一个洞穴里, 猎人看到了可怕的怪物 —行走的死人。 更令人不安的是, 最近有人进入丛林后失踪了。 ";
            link.l1 = "嗯... 您是说这也是梅里曼的所作所为吗? ";
            if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 30) link.l1.go = "caleuche_8_1";
            else link.l1.go = "caleuche_8";
        break;
        
        case "caleuche_8":
            sld = characterFromId("Havana_Priest");
            dialog.text = "我不知道该怎么想, 我的孩子。 但如果那个黑巫师变得如此强大, 群岛上的所有居民都处于极大的危险之中。 只有上帝知道这个恶魔的仆人心里在想什么\n我希望 "+sld.name+" 神父是错的, 但无论如何 —请去哈瓦那和他谈谈。 我为你准备了一张有效期一个月的贸易许可证, 有了它, 你可以毫无困难地进入哈瓦那港口。 ";
            link.l1 = "好的, 神父。 我会前往哈瓦那。 ";
            link.l1.go = "caleuche_9";
            npchar.quest.givelicence = true;
        break;
        
        case "caleuche_8_1":
            sld = characterFromId("Havana_Priest");
            dialog.text = "我不知道该怎么想, 我的孩子。 但如果那个黑巫师变得如此强大, 群岛上的所有居民都处于极大的危险之中。 只有上帝知道这个恶魔的仆人心里在想什么\n我希望 "+sld.name+" 神父是错的, 但无论如何 —我请你前往哈瓦那和他谈谈。 ";
            link.l1 = "当然, 神父。 我马上就去哈瓦那。 ";
            link.l1.go = "caleuche_9";
        break;
        
        case "caleuche_9":
            dialog.text = "我很高兴你是教会的忠实子民。 我会日夜为你的健康和平安祈祷。 带着我的祝福出发吧。 愿主在你与这些邪恶力量的斗争中赐予你力量。 ";
            link.l1 = "谢谢您, 神父, 再会。 ";
            link.l1.go = "caleuche_10";
        break;
        
        case "caleuche_10":
            DialogExit();
            AddQuestRecord("Caleuche", "26");
            AddCharacterMaxHealth(pchar, 1);
            if (CheckAttribute(npchar, "quest.givelicence")) GiveNationLicence(HOLLAND, 30);
            ChangeCharacterComplexReputation(pchar, "nobility", 2);
            ChangeCharacterComplexReputation(pchar, "authority", 1);
            ChangeCharacterComplexReputation(pchar, "fame", 3);
            ChangeCharacterNationReputation(pchar, HOLLAND, 5);
            AddCharacterExpToSkill(pchar, "Leadership", 300);
            pchar.questTemp.Caleuche = "havana";
            Caleuche_PrepareCubaGrot();
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 若switch内部某处通过return退出, 切记执行卸载
}