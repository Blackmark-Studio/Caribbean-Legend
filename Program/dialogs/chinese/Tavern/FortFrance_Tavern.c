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
            /* //--> Jason, 加斯科涅人的负担
            if (!CheckAttribute(npchar, "quest.Rum") && CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.questTemp.Sharlie == "ship" && makeint(environment.time) > 5.0 && makeint(environment.time) < 19.0)
            {
                link.l1 = "先生, 我在找工作。 你有什么活儿吗? ";
                link.l1.go = "Sharlie_rum";
            }
            if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") && pchar.questTemp.Sharlie.Rum == "regard")
            {
                link.l1 = "我已经完成了你的任务。 装朗姆酒的长艇已经送到勒弗朗索瓦湾, 并交给你的人了。 ";
                link.l1.go = "Sharlie_rum_5";
            }    
            //< —加斯科涅人的负担 */
            
            // Jason, 葡萄牙人
            if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToMartinique" && !CheckAttribute(npchar, "quest.Portugal"))
            {
                link.l1 = "我需要租你的一个房间住两三天。 我船上有个人受伤了, 他需要休息和恢复。 ";
                link.l1.go = "Portugal";
            }
            if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernorEnd")
            {
                link.l1 = "告诉我, 我租房间的那个朋友, 他离开了吗? 他答应等我的, 但房间里没人。 ";
                link.l1.go = "Portugal_2";
            }
            // 葡萄牙人
            // Jason 长长久久与幸福
            if (!CheckAttribute(npchar, "quest.LongHappy") && CheckAttribute(PChar, "questTemp.LongHappy.MarryRum") && LongHappy_CheckTavernGoods())
            {
                link.l1 = "我打算为我的手下安排一场聚会, 我想你已经知道了吧? ";
                link.l1.go = "LH_tavern_SP";
            }
            if (CheckAttribute(npchar, "quest.LongHappy.Nomoney") && LongHappy_CheckTavernGoods() && sti(Pchar.money) >= 100000+sti(pchar.questTemp.LongHappy.MarryMoney))
            {
                link.l1 = "我把庆祝所需的一切都带来了。 ";
                link.l1.go = "LH_tavern_SP_3";
            }
        break;
        
        //--> Jason, 加斯科涅人的负担
        case "Sharlie_rum":
            DelLandQuestMark(npchar);
            dialog.text = "一份工作? 嗯... 你看起来挺机灵的, 孩子。 我可能有适合你的活儿。 这工作听起来简单, 但需要责任感和头脑。 我不能相信这些蠢货去做生意, 他们肯定会搞砸的... ";
            link.l1 = "听着, 你能不能直接告诉我你想让我做什么? 我发誓, 我不会让你失望, 至少我会尽力而为。 ";
            link.l1.go = "Sharlie_rum_1";
        break;
        
        case "Sharlie_rum_1":
            switch(rand(4))
            {
                case 0:
                    pchar.questTemp.Sharlie.Rum.Pass = "老托马斯已经等啤酒等得不耐烦了";
                break;
                case 1:
                    pchar.questTemp.Sharlie.Rum.Pass = "木板和麻絮早上就会到";
                break;
                case 2:
                    pchar.questTemp.Sharlie.Rum.Pass = "别等南风了";
                break;
                case 3:
                    pchar.questTemp.Sharlie.Rum.Pass = "海湾已准备好下船";
                break;
                case 4:
                    pchar.questTemp.Sharlie.Rum.Pass = "骆驼正在向北走";
                break;
            }
            dialog.text = "好的。 我需要有人把几箱优质牙买加朗姆酒送到我的酒馆。 事情是这样的, 进口关税削减了我的利润, 而我最好的顾客们都渴了, 所以我们需要聪明点, 避开海关官员。 ‘幽灵’号小帆船今晚将抵达马提尼克岛附近。 它们会在拉芒坦湾不远处抛锚。 你必须找到这艘船并登上去。 我会给你提供一艘长艇和五名水手, 他们会听从你的命令。 一旦你上船, 会有一个人接近你。 你必须告诉他密码: ‘" + pchar.questTemp.Sharlie.Rum.Pass + "’。 答案会是‘水手, 为什么不来杯朗姆酒呢? ’。 你只有一次机会, 所以写下来, 别搞错了, 否则交易就取消了。 这就是为什么我不能把它交给那些和你 一 起航行的没脑子的蠢货。 重复一下密码。 ";
            link.l1 = "'" + pchar.questTemp.Sharlie.Rum.Pass + "'。 ";
            link.l1.go = "Sharlie_rum_2";
        break;
        
        case "Sharlie_rum_2":
            dialog.text = "很好。 你自己再重复几遍, 或者最好写在什么地方。 你向小帆船船长提到密码后, 装着朗姆酒瓶的板条箱就会被装上长艇, 然后你需要把长艇开到海盗定居点勒弗朗索瓦湾 —在那里会有人迎接你。 这就是整个任务。 你可以从勒弗朗索瓦湾步行到圣皮埃尔 —长艇会留在海湾。 任务完成后我会付你五千比索。 ";
            link.l1 = "走私听起来既刺激又赚钱。 我会按你说的做。 长艇在哪儿? ";
            link.l1.go = "Sharlie_rum_3";
            link.l2 = "所以, 你建议我从事走私活动? 嗯... 你知道, 我不能拿我的名声冒险。 请原谅, 我们就当我什么都没听到。 ";
            link.l2.go = "Sharlie_rum_exit";
        break;
        
        case "Sharlie_rum_exit":
            dialog.text = "如你所愿, 先生。 我没有其他工作了。 ";
            link.l1 = "我明白了。 那么祝你一切顺利, " + npchar.name+ "。 ";
            link.l1.go = "exit";
            DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
            SetCurrentTime(23, 0);
            Sharlie_removeLocks("");
        break;
        
        case "Sharlie_rum_3":
            dialog.text = "长艇将在晚上七点到达码头。 长艇上的船员技术娴熟, 所以你应该能很快到达小帆船。 整个任务不应该超过四个小时 —我相信你晚上十一点前就能回到圣皮埃尔。 拿着这个望远镜, 虽然是个垃圾, 但总比没有好。 拉芒坦海滩位于岛的北部, 所以离开港口后, 保持正北航向。 祝你好运! ";
            link.l1 = "好的, 知道了。 很快见, " + npchar.name+ "! ";
            link.l1.go = "Sharlie_rum_4";
        break;
        
        case "Sharlie_rum_4":
            DialogExit();
            AddQuestRecord("SharlieB", "1");
            AddQuestUserData("SharlieB", "sPassword", pchar.questTemp.Sharlie.Rum.Pass);
            GiveItem2Character(pchar, "spyglass1"); 
            Log_Info("你收到了一个望远镜");
            PlaySound("interface\important_item.wav");
            if(CheckAttribute(pchar, "questTemp.Sharlie.FastStart"))
            {
                GiveItem2Character(pchar, "map_martiniqua");
                Log_Info("你收到了马提尼克岛的地图");
                RefreshEquippedMaps(GetMainCharacter());
            }
            /* pchar.quest.Sharlie_rum.win_condition.l1 = "location";
            pchar.quest.Sharlie_rum.win_condition.l1.location = "Fortfrance_town"; */
            //pchar.quest.Sharlie_rum.win_condition.l1.locator_group = "rld";
            //pchar.quest.Sharlie_rum.win_condition.l1.locator = "loc0";
            pchar.quest.Sharlie_rum.win_condition.l1 = "HardHour";
            pchar.quest.Sharlie_rum.win_condition.l1.hour = 19.00;
            pchar.quest.Sharlie_rum.function = "Rum_CreateBarkas";
            SetFunctionTimerCondition("Rum_CreateBarkasOver", 0, 0, 1, false);
            pchar.questTemp.Sharlie.Rum = "true";
            npchar.quest.Rum = "true";
            NewGameTip("打开你的物品栏 (F1) 并装备望远镜。 ");
            pchar.quest.NgtBarkas.win_condition.l1 = "location";
            pchar.quest.NgtBarkas.win_condition.l1.location = "Fortfrance_town";
            pchar.quest.NgtBarkas.win_condition.l2 = "HardHour";
            pchar.quest.NgtBarkas.win_condition.l2.hour = 19.00;
            pchar.quest.NgtBarkas.function = "NgtBarkas";
            AddTimeToCurrent(1,30);
            QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
            QuestPointerToLoc("fortfrance_town", "reload", "reload1_back");
        break;
        
        case "Sharlie_rum_5":
            dialog.text = "太棒了! 我就知道能指望你。 难吗? ";
            link.l1 = "嗯, 这取决于你如何定义‘难’... ";
            link.l1.go = "Sharlie_rum_6";
        break;
        
        case "Sharlie_rum_6":
            dialog.text = "好吧, 这是你的奖励: 五千比索。 望远镜你可以留着。 还有, 另一个小礼物, 请拿这三瓶朗姆酒。 你试过之后, 就会明白为什么它的需求如此之大了。 ";
            link.l1 = "谢谢你! 和你合作很愉快! 回头见! ";
            link.l1.go = "Sharlie_rum_7";
        break;
        
        case "Sharlie_rum_7":
            DialogExit();
            AddMoneyToCharacter(pchar, 5000);
            TakeNItems(pchar, "potionrum", 3);
            AddQuestRecord("SharlieB", "5");
            CloseQuestHeader("SharlieB");
            DeleteAttribute(pchar, "questTemp.Sharlie.Rum");
            // Rebbebion, 新的目的地标记
            QuestPointerDelLoc("lefransua_town", "reload", "gate_back");
            QuestPointerDelLoc("lefransua_exittown", "reload", "reload2_back");
            QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
            QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
            QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
            QuestPointerDelLoc("fortfrance_town", "reload", "reload4_back");
            DelLandQuestMark(npchar);
            if(!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo"))
            {
                pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1 = "Hour";
                pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.start.hour = 6.00;
                pchar.quest.Sharlie_CreatShipyardMarker.win_condition.l1.finish.hour = 22.00;
                pchar.quest.Sharlie_CreatShipyardMarker.function = "Sharlie_CreatShipyardMarker";
            }
        break;
        //< —加斯科涅人的负担
		
        // 葡萄牙人
		case "Portugal":
            dialog.text = "没问题, 我有一间房。 50比索, 你可以住三天。 ";
            if (sti(pchar.money) >= 50)
            {
                link.l1 = "给你。 ";
                link.l1.go = "Portugal_1";
            }
            else
            {
                link.l1 = "我去司库那里取钱, 马上回来。 ";
                link.l1.go = "exit";
            }
        break;
        
        case "Portugal_1":
            ref sld;
            DialogExit();
            AddMoneyToCharacter(pchar, -50);
            npchar.quest.Portugal = "true";
            LocatorReloadEnterDisable("Fortfrance_tavern", "reload2_back", false);
            pchar.quest.Portugal_Ill3.over = "yes";
            LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", true);
            LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", true);
            LocatorReloadEnterDisable("Fortfrance_town", "gate_back", true);//关闭出城通道
            sld = characterFromId("Portugal");
            ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto3");
            sld = characterFromId("PortugalDoctor");
            ChangeCharacterAddressGroup(sld, "FortFrance_tavern_upstairs", "goto", "goto1");
            pchar.quest.Portugal_tavernroom.win_condition.l1 = "location";
            pchar.quest.Portugal_tavernroom.win_condition.l1.location = "FortFrance_tavern_upstairs";
            pchar.quest.Portugal_tavernroom.function = "PortugalInTavernRoom";
        break;
        
        case "Portugal_2":
            dialog.text = "先生, 我不能说他是自己起身离开房间的。 昨天有人来过这里。 其中一个是独眼高瘦的男人 —从外表看显然是个强盗, 还有一个说话口齿不清的男人, 看起来像卡斯蒂利亚人。 我当时只是惊讶, 但那个口齿不清的人看了我一眼... 就像要拍打虱子前的眼神。 于是他们问起你朋友的事... 我就告诉他们了。 我还能怎么办? ";
            link.l1 = "我知道, " + npchar.name+ ", 你不是英雄, 没错。 你还看到了什么? 他们去哪儿了? ";
            link.l1.go = "Portugal_3";
        break;
        
        case "Portugal_3":
            dialog.text = "就这些... 等等, 不! 等等, 那个独眼男人提到了马车。 我猜他们用马车把你朋友拖到了岛的另一边。 真的就这些了, 先生! 我本想叫卫兵, 但那个口齿不清的人临走时说我妻子很漂亮... 明白吗? 要是他们知道我告诉你这些, 他们会... ";
            if (pchar.money >= 1000)
            {
                link.l1 = "别害怕, 他们只会从我这里听到子弹声。 你帮了大忙, 谢谢。 这1000比索你拿着当谢礼。 ";
                link.l1.go = "Portugal_4";
            }
            link.l2 = "钱不多, 但还是谢谢你。 下次记得叫卫兵, 别这么窝囊。 ";
            link.l2.go = "Portugal_5";
        break;
        
        case "Portugal_4":
            AddMoneyToCharacter(pchar, -1000);
            dialog.text = "谢谢您, 先生。 我敢保证你朋友差不多康复了, 至少能自己走路了。 还有个安静的荷兰人, 当时从外面进来, 看到一团糟又跳出去了, 之后就没影了。 ";
            link.l1 = "我猜他已经搭最早的船走了。 谢谢你的消息, 我该走了。 ";
            link.l1.go = "Portugal_6";
        break;
        
        case "Portugal_5":
            dialog.text = "不是每个人都能拔剑当英雄的, 船长。 ";
            link.l1 = "嗯... 这是个人选择。 ";
            link.l1.go = "Portugal_6";
        break;
        
        case "Portugal_6":
            DialogExit();
            sld = characterFromId("Avendel");
            sld.dialog.currentnode = "Avendel_seapatrol_9";
            LAi_SetActorType(sld);
            LAi_ActorDialog(sld, pchar, "", -1, 0);
        break;
        //葡萄牙人
        
        // 杰森.长长久久与幸福
        case "LH_tavern_SP":
            npchar.quest.LongHappy = "true";
            dialog.text = "是的, 你助手来过, 但我跟她说过也得跟你重复 —我见惯了喝醉的水手扎堆, 但你们的派对我可知道。 最后这儿估计跟西班牙方阵洗劫过的安特卫普一样惨。 要是墙没倒我都谢天谢地了。 所以你要是想让大家撒欢儿闹, 除了已经带来的东西, 还得交笔不退的押金。 以防万一嘛。 ";
            link.l1 = "你这老狐狸! 我跟海员喝酒这么多年, 什么场子没见过... 我带的钱够把你这酒馆拆了重建! 想趁机敲竹杠是吧? 行, 我要办婚礼, 没心情跟你扯这些 —你要多少? ";
            link.l1.go = "LH_tavern_SP_1";
        break;
        
        case "LH_tavern_SP_1":
            dialog.text = "再加10万八里亚尔应该够了, 放心 —我肯定办得漂漂亮亮。 你的人能记这派对一辈子, 我打包票! ";
            if (sti(Pchar.money) >= 100000 + sti(pchar.questTemp.LongHappy.MarryMoney))
            {
                link.l1 = "你可得用心办 —这可是特殊场合。 还有, 庆祝完了就算酒馆烧了也别来找我抱怨。 ";
                link.l1.go = "LH_tavern_SP_4";
            }
            else
            {
                link.l1 = "搞得跟给国王办婚礼似的! 等我, 马上回来。 ";
                link.l1.go = "LH_tavern_SP_2";
            }
        break;
        
        case "LH_tavern_SP_2":
            DialogExit();
            npchar.quest.LongHappy.Nomoney = "true";
        break;
        
        case "LH_tavern_SP_3":
            dialog.text = "你的人肯定能记这派对一辈子, 我打包票! ";
            link.l1 = "你可得用心办 —这可是特殊场合。 我手下要是不小心把你酒馆烧了, 别来找我哭丧。 ";
            link.l1.go = "LH_tavern_SP_4";
        break;
        
        case "LH_tavern_SP_4":
            DialogExit();
            RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.questTemp.LongHappy.MarryRum));
            AddMoneyToCharacter(pchar, -sti(pchar.questTemp.LongHappy.MarryMoney));
            AddMoneyToCharacter(pchar, -100000);
            DeleteAttribute(npchar, "quest.LongHappy.Nomoney");
            pchar.questTemp.LongHappy.DrinkReady = "true";
            pchar.questTemp.LongHappy.MarrySP = "true";
            DeleteAttribute(pchar, "questTemp.LongHappy.MarryMoney");
            DeleteAttribute(pchar, "questTemp.LongHappy.MarryRum");
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 若switch中某处通过return退出, 务必执行卸载
}