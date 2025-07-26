// 城市相关对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch(Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = "说吧, 我在听";
            link.l1 = "我搞错了。 再见。 ";
            link.l1.go = "Exit";
            // 卡勒幽船
            if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "start")
            {
                link.l1 = "我听说在伯利兹附近和镇上有一伙盗贼和强盗活动。 ";
                link.l1.go = "caleuche";
            }
            if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "know" && CheckAttribute(pchar, "questTemp.Caleuche.belizbandos") && GetQuestPastDayParam("questTemp.Caleuche.belizbandos") < 3)
            {
                link.l1 = "我可以给你提供关于这伙人的信息。 ";
                link.l1.go = "caleuche_3";
            }
            if (CheckAttribute(pchar, "questTemp.Caleuche.BelizRegard"))
            {
                link.l1 = "关于这伙人有什么消息吗? 你们在洞穴里抓住他们了吗? ";
                link.l1.go = "caleuche_7";
            }
            // 导航之星 ==>
            if (CheckAttribute(pchar, "questTemp.PZ_Beliz_Komendant"))
            {
                link.l1 = "整个镇子似乎都在庆祝抓住了一名海盗。 你能给我多讲讲这件事吗? ";
                link.l1.go = "PZ_Beliz_Komendant_1";
                DeleteAttribute(pchar, "questTemp.PZ_Beliz_Komendant");
            }
            // <== 导航之星
        break;
        
        // 导航之星 ==>
        case "PZ_Beliz_Komendant_1":
            dialog.text = "乐意效劳! 这可不是一般的海盗 --这是那个恶棍, 马修.勒特尔。 ";
            link.l1 = "每个人的运气总有耗尽的时候。 ";
            link.l1.go = "PZ_Beliz_Komendant_2";
            DelLandQuestMark(npchar);
        break;
        
        case "PZ_Beliz_Komendant_2":
            dialog.text = "你不是英国人, 也不像商人, 所以我能理解你为什么没那么激动。 勒特尔多年来一直在这些海域为非作歹, 袭击我们和西班牙人, 但更多的是袭击我们。 他总能躲开我们的海岸巡逻队, 驾驶着他的护卫舰'海鸥号', 那曾经是群岛中最快的船。 只有上帝知道他是怎么得到这样一艘战舰的指挥权的。 ";
            link.l1 = "所以说他真的输给了一个商人? 在护卫舰上? 听起来难以置信。 ";
            link.l1.go = "PZ_Beliz_Komendant_3";
        break;
        
        case "PZ_Beliz_Komendant_3":
            dialog.text = "尽管听起来很奇怪, 但这是真的。 一个商人, 而且还是个西班牙人! 我们的海军可以从他身上学到一两招。 索塔船长意识到无法逃脱, 便准备战斗... ";
            link.l1 = "这个索塔真是个不寻常的人。 ";
            link.l1.go = "PZ_Beliz_Komendant_4";
        break;
        
        case "PZ_Beliz_Komendant_4":
            dialog.text = "也许吧。 他让人把船改装得尽可能多装货物, 这使得逃跑变得不可能。 知道海盗们是冲着他的货物来的, 他假装船在漂流。 然后... ";
            link.l1 = "... 他在合适的时机升起了船帆? ";
            link.l1.go = "PZ_Beliz_Komendant_5";
            if (!CharacterIsHere("Longway"))
            {
                sld = CharacterFromID("Longway");
                ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
                LAi_SetActorType(sld);
                LAi_ActorFollow(sld, pchar, "", -1);
            }
        break;
        
        case "PZ_Beliz_Komendant_5":
            dialog.text = "哈! 不, 当勒特尔靠近时, 他近距离发射了一轮葡萄弹, 然后亲自登上了海盗船! 当他发现勒特尔是谁时, 就把他交给了我们。 真是个英雄, 一个有荣誉感的人! ";
            link.l1 = "驱使他的不只是荣誉 --抓住这个吹牛大王肯定有赏。 ";
            link.l1.go = "PZ_Beliz_Komendant_6";
        break;
        
        case "PZ_Beliz_Komendant_6":
            dialog.text = "有时候利益与善意是一致的。 但没错, 他得到了丰厚的奖赏。 在他起航前, 大人送了他许多昂贵的货物, 以表达我们城市的感激之情。 ";
            link.l1 = "真希望我能见到他 --我想和他握握手。 告诉我... ";
            link.l1.go = "PZ_Beliz_Komendant_7";
        break;
        
        case "PZ_Beliz_Komendant_7":
            StartInstantDialog("Longway", "PZ_Beliz_Komendant_8", "Quest\CompanionQuests\Longway.c");
        break;
        // <== 导航之星
        
        // 卡勒幽船
        case "caleuche":
            dialog.text = "你的消息来源说的是真的。 这些土匪已经成了我们的一大麻烦。 你有关于他们的什么消息要告诉我们吗? ";
            link.l1 = "除了他们从我这里偷走了一件重要的东西 --没什么别的了。 我原以为你能告诉我一些关于他们的事情。 也许他们中的一个被抓住了, 现在准备作证... ";
            link.l1.go = "caleuche_1";
        break;
        
        case "caleuche_1":
            dialog.text = "很抱歉让你失望了, 船长, 但我没有关于他们的任何信息。 我只知道他们藏在丛林的某个地方, 而且他们在镇上有同伙, 仅此而已。 现在, 如果你了解到关于他们的任何新消息, 请立即告诉我。 ";
            link.l1 = "好的, 军官。 我会的。 ";
            link.l1.go = "caleuche_2";
        break;
        
        case "caleuche_2":
            DialogExit();
            AddQuestRecord("Caleuche", "10");
            pchar.questTemp.Caleuche.Bandos = "seek";
        break;
        
        case "caleuche_3":
            string sTime;
            if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 0) sTime = "三天后";
            if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 1) sTime = "后天";
            if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 2) sTime = "明天";
            dialog.text = "你是认真的吗, 船长? 说吧, 我洗耳恭听。 ";
            link.l1 = "我在镇上找到了他们的一个线人。 他告诉我, 他们的团伙正准备袭击一艘船, 这艘船应该会抵达切图马尔峡。 这些恶棍" + sTime + "晚上会在离伯利兹不远的一个洞穴附近聚集。 要到那里, 只需在丛林的岔路口走左边的路。 ";
            link.l1.go = "caleuche_4";
        break;
        
        case "caleuche_4":
            dialog.text = "在洞穴里? 太好了。 我会下令为这些恶棍准备一个伏击。 如果你说的没错, 你的线人说的是实话, 我们就会抓住这些混蛋, 然后我会在总督面前为你请求奖赏。 ";
            link.l1 = "谢谢! 事情结束后我会来看你的。 ";
            link.l1.go = "caleuche_5";
        break;
        
        case "caleuche_5":
            dialog.text = "好的。 就这样吧。 ";
            link.l1 = "再见, 军官。 ";
            link.l1.go = "caleuche_6";
        break;
        
        case "caleuche_6":
            DialogExit();
            AddQuestRecord("Caleuche", "15");
            pchar.questTemp.Caleuche.Bandos = "comendant";
            pchar.questTemp.Caleuche.BelizChance = hrand(3);
            SetFunctionTimerCondition("Caleuche_BelizRegard", 0, 0, 3, false); // 计时器
        break;
        
        case "caleuche_7":
            if (sti(pchar.questTemp.Caleuche.BelizChance) < 3)
            {
                dialog.text = "我们为这些恶棍准备了一个热烈的欢迎仪式, 哈哈哈! 要是你能看到他们的表情就好了! 我们把所有人都抓住了, 包括头目! 有些人试图反抗, 但被我们勇敢的士兵消灭了。 ";
                link.l1 = "太好了, 军官! 现在伯利兹的市民终于可以安心睡觉了。 ";
                link.l1.go = "caleuche_12";
            }
            else
            {
                dialog.text = "嗯... 我的士兵在洞穴里等了他们一整夜, 但没有人出现。 中士非常生气。 还好他没有抓住你。 ";
                link.l1 = "该死! 这不可能! 你们在哪里设的伏击? 那里有两个洞穴! ";
                link.l1.go = "caleuche_8";
            }
        break;
        
        case "caleuche_8":
            dialog.text = "你告诉我的地方。 在岔路口右边的那个... ";
            link.l1 = "是左边的那个! 在岔路口左边, 你们这些笨蛋! ";
            link.l1.go = "caleuche_9";
        break;
        
        case "caleuche_9":
            dialog.text = "但我清楚地记得你说的是'右边'。 ";
            link.l1 = "哦, 我的上帝! 是左边! 我说的是! 左! 边! 你们让他们跑了, 这是你们的错! ";
            link.l1.go = "caleuche_10";
        break;
        
        case "caleuche_10":
            AddQuestRecord("Caleuche", "16");
            dialog.text = "那你肯定是小声嘟囔了什么。 你知道的, 我听力很好。 ";
            link.l1 = "好吧, 军官, 我不想争论。 我想帮你, 但你这种人是帮不了的。 再见。 ";
            link.l1.go = "caleuche_11";
        break;
        
        case "caleuche_11":
            DialogExit();
            DeleteAttribute(pchar, "questTemp.Caleuche.BelizChance");
            DeleteAttribute(pchar, "questTemp.Caleuche.BelizRegard");
        break;
        
        case "caleuche_12":
            dialog.text = "我已向总督报告了你在剿灭这伙土匪中所起的作用。 他非常重视你的贡献, 并授权我向你颁发奖赏: 一笔奖金和一支战利品火绳枪。 ";
            link.l1 = "谢谢! ";
            link.l1.go = "caleuche_13";
        break;
        
        case "caleuche_13":
            Log_Info("你收到了一箱杜布隆金币");
            Log_Info("你收到了一支火绳枪");
            PlaySound("interface\important_item.wav");
            AddQuestRecord("Caleuche", "17");
            GiveItem2Character(pchar, "chest"); 
            GiveItem2Character(pchar, "mushket3"); 
            dialog.text = "感谢你的服务, 船长! 要是我们所有的公民都像你一样尽责, 我们早就彻底消灭犯罪了! 祝你好运! ";
            link.l1 = "再见, 军官! 祝你在工作中一切顺利! ";
            link.l1.go = "caleuche_11";
            ChangeCharacterComplexReputation(pchar, "nobility", 5);
            ChangeCharacterComplexReputation(pchar, "authority", 3);
            ChangeCharacterComplexReputation(pchar, "fame", 3);
            OfficersReaction("good");
            ChangeCharacterNationReputation(pchar, ENGLAND, 8);
            AddCharacterExpToSkill(pchar, "Leadership", 300);//权威
            AddCharacterExpToSkill(pchar, "Fortune", 200);//运气
            AddCharacterExpToSkill(pchar, "Sneak", 200);//隐蔽
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部某处通过return退出, 别忘了进行卸载
}