// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("我能为您提供什么帮助? ", "有什么可以为您效劳的? "), "告诉我, " + GetAddress_Form(NPChar) + ", 是什么困扰着您? ", "这已经是第三次了, " + GetAddress_Form(NPChar) + ", 您到底需要什么? ", "我受够您了, 滚出去! ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了, 抱歉。 ", "没什么事, 打扰了。 "), "请原谅我, 没什么要紧的。 ",
                      "您说得对, 已经第三次了。 请宽恕我... ", "抱歉。 ", npchar, Dialog.CurrentNode);        
            link.l1.go = "exit";
            // 卡莱乌切
            if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
            {
                link.l1 = "听着, 您在哈瓦那或附近见过一个叫约阿希姆.梅里曼的人吗? 他是个中年绅士, 葡萄牙人, 留着小胡子。 帝王式胡须和锐利的眼睛。 也许在海湾或丛林里? 我在找他。 ";
                link.l1.go = "caleuche";
            }
        break;
        
        // 卡莱乌切
        case "caleuche":
            dialog.text = "不-不, 水手, 当-当然没有。 您知道, 我这儿很少有访客, 呃... 而我... 我结-结巴是从孩-孩童时期就有的... ";
            link.l1 = "真的吗? 那您为什么口吃还不敢看我? 别骗我了, 您知道真相。 最好再告诉我一遍 —您见过那个人吗? ";
            link.l1.go = "caleuche_1";
        break;
        
        case "caleuche_1":
            dialog.text = "我-我告诉您, 先生, 我没-没见过任何人! 我-我从-从小就口-口吃... ";
            link.l1 = "谎言, 全是谎言。 我从您眼里看得出来。 他在哪儿, 梅里曼在哪儿? 告诉我, 现在就说! ";
            link.l1.go = "caleuche_2";
        break;
        
        case "caleuche_2":
            dialog.text = "我不认识什么梅里曼! 我也从没听过这个名字! 别想伤害我, 不然指挥官会在堡垒把您吊死! 所以小心点, 小子! ";
            link.l1 = "哦, 您这么认为? 好吧。 现在, 您仔细听好: 约阿希姆.梅里曼是个男巫。 宗教裁判所正在找他。 多年前在欧洲, 他因盗墓。 亵渎死者和施行巫术被判处火刑。 而我确定他现在就藏在哈瓦那郊区的某个地方... ";
            link.l1.go = "caleuche_3";
        break;
        
        case "caleuche_3":
            dialog.text = "... ";
            link.l1 = "... 最近我清理了附近的僵尸洞穴, 我知道是谁干的! 当然, 除了墓地, 梅里曼还能去哪儿呢? 您知道他在哪儿。 但随您便, 我不会碰您一根手指, 但我会去圣地亚哥拜访裁判官。 文森特神父会很感兴趣 —约阿希姆.梅里曼正和他的同伙, 也就是当地的看守, 藏在哈瓦那的墓地里... ";
            link.l1.go = "caleuche_4";
        break;
        
        case "caleuche_4":
            dialog.text = "... ";
            link.l1 = "... 您的脸已经吓得没血色了吧? 我以贵族的名义发誓: 我报告发现后的一天内, 整个岛屿将布满西班牙士兵。 您会被绑在刑架上, 哭着求饶, 直到说出那个男巫藏在哪里。 随后您会被当作他的同伙烧死, 而我会观看那场宗教火刑。 您觉得怎么样? ";
            link.l1.go = "caleuche_5";
        break;
        
        case "caleuche_5":
            dialog.text = "求-求您了, 先生! 我发誓我没参与任何事! 我... 我只是无能为力... 我怎么能对抗他呢? 他是个可怕的人, 他能... 您不知道他能做什么! 求求您慈悲! ";
            link.l1 = "相信我, 我知道他能做什么。 我亲眼见过。 那么? 他在哪儿? 告诉我, 我保证不会让您卷入这件事。 ";
            link.l1.go = "caleuche_6";
        break;
        
        case "caleuche_6":
            dialog.text = "他... 他藏在墓地下面的一个洞穴里。 只有通过小教堂的门才能进去。 他出去的时候, 我就躲在房子里坐着。 您不知道我多想摆脱这场噩梦! \n但我连靠近都不敢。 我... 我见过他挖新坟, 然后... 然后死人就站起来, 在月光下绕着墓地走! 我当时差点疯了! 但梅里曼禁止我离开。 他威胁说, 如果我未经允许离开房子哪怕半天, 他就会找到我, 把我变成那种怪物... 一个行走的骷髅! ";
            link.l1 = "他多久离开一次洞穴? ";
            link.l1.go = "caleuche_7";
        break;
        
        case "caleuche_7":
            dialog.text = "嗯, 我从镇上给他带食物和治疗药水... 还有他要的其他东西。 他每月离开一两次... 在满月的时候。 他会在门口留张纸条, 写下需要的东西... 我送去放在门口, 他回来后会拿走。 ";
            link.l1 = "我明白了。 通往他巢穴的那扇门 —上锁了吗? ";
            link.l1.go = "caleuche_8";
        break;
        
        case "caleuche_8":
            dialog.text = "是的, 一直锁着。 门很结实, 锁又大又复杂。 ";
            link.l1 = "嗯... 梅里曼不是傻瓜, 他肯定像在欧洲的房子一样, 巢穴还有另一个出口。 如果我们强行开门, 他会溜走, 再也找不到了。 嗯... ";
            link.l1.go = "caleuche_9";
        break;
        
        case "caleuche_9":
            dialog.text = "先生, 您能发誓不把我交给宗教裁判所吗? ";
            link.l1 = "我向您保证, 贵族的话是神圣的。 我发誓不会揭发您。 ";
            link.l1.go = "caleuche_10";
        break;
        
        case "caleuche_10":
            dialog.text = "哦, 上帝保佑您, 先生! 我知道怎么去那个洞穴。 有一把钥匙, 第二把钥匙... 在我这儿。 梅里曼不知道那把锁有两把钥匙。 我从不敢进去, 但您... ";
            link.l1 = "把钥匙给我, 我会帮您摆脱这场噩梦。 ";
            link.l1.go = "caleuche_11";
        break;
        
        case "caleuche_11":
            GiveItem2Character(pchar, "kaleuche_key");
            ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_crypt");
            dialog.text = "给您, 先生。 您真的要进他的巢穴吗? ";
            link.l1 = "是的。 我进去时您把自己锁在房子里等着。 如果我没回来, 就丢下一切尽快跑。 ";
            link.l1.go = "caleuche_12";
        break;
        
        case "caleuche_12":
            dialog.text = "但请小心, 先生。 他的洞穴里传出过可怕的声音, 我甚至不敢想里面住着什么。 但梅里曼不是一个人 —这一点可以肯定。 ";
            link.l1 = "我会尽可能做好准备。 再见。 ";
            link.l1.go = "caleuche_13";
        break;
        
        case "caleuche_13":
            DialogExit();
            AddQuestRecord("Caleuche", "30");
            pchar.questTemp.Caleuche = "merriman";
            pchar.quest.caleuche_merriman_cave.win_condition.l1 = "locator";
            pchar.quest.caleuche_merriman_cave.win_condition.l1.location = "Havana_CryptBig2";
            pchar.quest.caleuche_merriman_cave.win_condition.l1.locator_group = "reload";
            pchar.quest.caleuche_merriman_cave.win_condition.l1.locator = "reload2";
            pchar.quest.caleuche_merriman_cave.function = "Caleuche_OpenMerrimanCave";
            pchar.quest.caleuche_merriman_cave1.win_condition.l1 = "location";
            pchar.quest.caleuche_merriman_cave1.win_condition.l1.location = "Havana_CryptDungeon";
            pchar.quest.caleuche_merriman_cave1.function = "Caleuche_InMerrimanCave";
            if(bImCasual) NewGameTip("探索模式: 计时器未禁用。 请在期限内完成! ");
            SetFunctionTimerCondition("Caleuche_MerrimanCaveOver", 0, 0, 3, false); // 计时器
            npchar.quest.caleuche = "true";
            // 梅里曼的巢穴
            int n = Findlocation("Havana_CryptDungeon");
            locations[n].id.label = "Merrimancave";
        break;
    }
    UnloadSegment(NPChar.FileDialog2); 
}