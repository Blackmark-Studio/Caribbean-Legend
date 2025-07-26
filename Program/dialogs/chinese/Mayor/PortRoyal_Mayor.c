// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你想要什么? 问吧。 ", "我在听, 你有什么问题? "), "这是你第二次尝试提问... ", "这是你第三次尝试提问... ",
                          "这要到什么时候才结束? ! 我是个忙人, 在处理殖民地事务, 而你还在烦我! ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "现在不行。 地点和时间不对。 "), "确实... 但以后吧, 不是现在... ",
                      "我会问的... 但过一会儿... ", "抱歉, " + GetAddress_FormToNPC(NPChar) + "... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            // 插件2016-1 杰森海盗线
            if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_8")
            {
                link.l1 = "大人, 我想举报本岛的非法贸易活动。 ";
                link.l1.go = "Mtraxx";
            }
            if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_12")
            {
                link.l1 = "我想听取你关于丝绸帆布走私任务的报告。 ";
                link.l1.go = "Mtraxx_4";
            }
            // 杰森 圣马丁岛
            if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_10_continue" && !CheckAttribute(npchar, "quest.slaveships"))
            {
                link.l1 = "我代表总督菲利普.德.潘西前来。 我的任务是把从荷兰人那里俘获的奴隶带给您, 对吗? ";
                link.l1.go = "patria_Sl";
            }
            if (CheckAttribute(npchar, "quest.slaveships.wait") && GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000)
            {
                link.l1 = "我按约定把奴隶带来了。 ";
                link.l1.go = "patria_Sl_2";
            }
            if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_start" && CheckAttribute(pchar, "questTemp.Patria.Curacao.DoilyReady"))
            {
                link.l1 = "我按总督菲利普.德.潘西的指示前来, 参加针对库拉索荷兰人的联合远征。 ";
                link.l1.go = "patria_Sl_4";
            }
            if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_wait" && GetCompanionQuantity(pchar) < 3)
            {
                link.l1 = "我的中队已缩减, 现在可以出发了。 ";
                link.l1.go = "patria_Sl_6";
            }
        break;
        
        // 插件2016-1 杰森海盗线
        case "Mtraxx":
            dialog.text = "有意思。 我洗耳恭听。 ";
            link.l1 = "我有可靠消息称, 一艘挂英国国旗的荷兰双桅帆船‘乌得勒支号’长期在波特兰峡卸载大量丝绸帆布。 他们已经运作了一年多, 每月10日至15日夜间活动。 ";
            link.l1.go = "Mtraxx_1";
        break;
        
        case "Mtraxx_1":
            dialog.text = "你确定消息来源可靠吗? ";
            link.l1 = "有时我连自己都不信, 但透露消息的人很可靠。 此外, 他没有理由撒谎。 ";
            link.l1.go = "Mtraxx_2";
        break;
        
        case "Mtraxx_2":
            string sTemp = "本月";
            if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "下月";
            dialog.text = "很好, 船长。 这是严重的事件, 即便你的线人撒谎或判断错误, 我也必须根据情报行动。 我会在指定时间派遣海岸巡逻队, 若情报属实将给予你丰厚奖励, 此类非法活动必须严厉打击。 ";
            link.l1 = sTemp + "16日我再来见您。 届时情况定会水落石出。 ";
            link.l1.go = "Mtraxx_3";
        break;
        
        case "Mtraxx_3":
            DialogExit();
            pchar.questTemp.Mtraxx = "silk_11";
            int month = sti(pchar.questTemp.Mtraxx.month);
            pchar.quest.mtr_silk_smuggler.over = "yes";
            pchar.quest.mtr_silk_smuggler_over.over = "yes";
            DeleteQuestCondition("Mtraxx_SilkCreateSmuggler");
            DeleteQuestCondition("Mtraxx_SilkSmugglerFail");
            pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1 = "Timer";
            pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.hour  = 6;
            pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.day   = 16;
            pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
            pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.year  = GetAddingDataYear(0, month, 0);
            pchar.quest.mtr_silk_smuggler_patrol.function = "Mtraxx_SilkSmugglerPatrol";
            sTemp = "本月";
            if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "下月";
            AddQuestRecord("Roger_2", "19");
            AddQuestUserData("Roger_2", "sDate", sTemp);
            if (CharacterIsAlive("Mtr_Utreht"))
            {
                sld = CharacterFromID("Mtr_Utreht");
                sld.lifeday = 0;
            }
        break;
        
        case "Mtraxx_4":
            dialog.text = "船长, 你的情报证实是正确的。 我们在交易时伏击了罪犯。 ‘乌得勒支号’试图逃跑并抵抗, 但被我们的巡逻护卫舰击沉。 四名买家拒捕, 一人被枪杀, 另三人逃进丛林。 80卷丝绸全部缴获并移交皇家港国库。 尽管未能查明网络头目 --死者身份不明, 其他人也已逃脱, 但我宣布行动完全成功。 我怀疑这些恶棍再也不敢来此作案了。 \n你勤勉尽责地揪出了骗子, 为我们做出了重大贡献, 船长。 这是1万比索的奖励。 ";
            link.l1 = "非常感谢, 大人。 我很高兴看到一切按计划进行, 走私者得到了应有的惩罚。 就此告辞, 祝您愉快。 ";
            link.l1.go = "Mtraxx_5";
        break;
        
        case "Mtraxx_5":
            DialogExit();
            pchar.questTemp.Mtraxx = "silk_13";
            AddQuestRecord("Roger_2", "20");
            AddMoneyToCharacter(pchar, 10000);
            ChangeCharacterComplexReputation(pchar, "nobility", 3);
            ChangeCharacterNationReputation(pchar, ENGLAND, 5);
            AddCharacterExpToSkill(pchar, "Leadership", 200);
        break;
        
        // 杰森 圣马丁岛
        case "patria_Sl":
            if (GetSquadronGoods(pchar, GOOD_SLAVES) < 500)
            {
                dialog.text = "没错。 你带来了多少奴隶? ";
                link.l1 = "我还在努力。 很快就会带着结果回来。 ";
                link.l1.go = "patria_Sl_wait";
                break;
            }
            dialog.text = "没错。 你带来了多少奴隶? ";
            link.l1 = ""+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SLAVES))+"。 ";
            if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000) link.l1.go = "patria_Sl_2";
            else link.l1.go = "patria_Sl_1";
        break;
        
        case "patria_Sl_wait":
            DialogExit();
            npchar.quest.slaveships.wait = "true";
        break;
        
        case "patria_Sl_1":
            dialog.text = "嗯, 谢瓦利埃承诺过不少于3000名奴隶";
            link.l1 = "是的。 这是我的错: 有些奴隶在敌舰炮火中丧生, 有些在途中死亡。 我会纠正错误并回来见您, 一切将按合同完成。 ";
            link.l1.go = "patria_Sl_wait";
        break;
        
        case "patria_Sl_2":
            DeleteAttribute(npchar, "quest.slaveships.wait");
            dialog.text = "太好了! 和谢瓦利埃.德.潘西合作确实靠谱。 告诉总督我的库拉索攻击中队一个月后准备就绪。 我相信他会派你参加这次战役, 所以很快就会再见到你, 德.莫尔先生。 ";
            link.l1 = "很高兴能再次见到您, 上校。 现在请允许我告辞。 ";
            link.l1.go = "patria_Sl_3";
        break;
        
        case "patria_Sl_3":
            DialogExit();
            npchar.quest.slaveships = "true";
            RemoveCharacterGoods(pchar, GOOD_SLAVES, GetSquadronGoods(pchar, GOOD_SLAVES));
            AddQuestRecord("Patria", "57");
            pchar.questTemp.Patria = "epizode_10_return";
            pchar.quest.Patria_SlaveShipsJamaicaTimeOver.over = "yes"; // 移除奴隶运送计时器
            SetFunctionTimerCondition("Patria_CuracaoDoilyReady", 0, 0, 30, false); // 给d'Oyly中队准备时间设1个月计时器
            SetFunctionTimerCondition("Patria_CuracaoTimeOver", 0, 0, 62, false); // 给往返潘西的时间设2个月计时器
            SaveCurrentQuestDateParam("questTemp.Patria.Curacao.Date"); // 记录日期
            // 改变国家关系
            pchar.questTemp.Patria.Friend = "true";
            LaunchNationLegend();
            DeleteAttribute(pchar, "questTemp.Patria.Friend");
            DoQuestCheckDelay("sea_victory", 0.2);
        break;
        
        case "patria_Sl_4":
            dialog.text = "我就知道会是你。 这更好! 我们的中队已准备就绪: 1艘一级战列舰和2艘四级舰。 整个中队最大规模不得超过5艘船。 ";
            if (GetCompanionQuantity(pchar) > 2)
            {
                link.l1 = "那我把多余的船留在码头, 只保留2艘。 这样我们就有5艘船了。 ";
                link.l1.go = "patria_Sl_5";
            }
            else
            {
                link.l1 = "对, 正好5艘, 不多不少。 我们该出发了。 ";
                link.l1.go = "patria_Sl_6";
            }
        break;
        
        case "patria_Sl_5":
            DialogExit();
            pchar.questTemp.Patria = "epizode_11_wait";
        break;
        
        case "patria_Sl_6":
            dialog.text = "很好。 现在我向你解释我们的行动计划: 也许你想修改或补充什么, 我们可以讨论。 ";
            link.l1 = "我洗耳恭听, 上校。 ";
            link.l1.go = "patria_Sl_7";
        break;
        
        case "patria_Sl_7":
            dialog.text = "攻占库拉索没有意义: 它是群岛中主要的荷兰殖民地, 即便我们在威廉斯塔德堡垒夺取他们的旗帜并升起英国或法国旗帜, 也很难守住该岛。 荷兰人会不惜一切代价夺回来, 并派军事中队 targeting 它。 总之, 攻占它没有意义, 因为这不是必须的。 对我们更重要的是迫使斯特伊弗桑特签署对我们有利的条约, 为此只需摧毁敌人的主要防御工事, 并让荷兰人面临威廉斯塔德殖民地被彻底摧毁的威胁。 ";
            link.l1 = "条约的内容是什么? ";
            link.l1.go = "patria_Sl_8";
        break;
        
        case "patria_Sl_8":
            dialog.text = "条约由我和谢瓦利埃.德.潘西起草, 涉及贸易各方面。 结束公司与英国的‘贸易战’。 否认施托伊弗桑特对圣马丁岛的主张以及其他你不太感兴趣的政治要点。 ";
            link.l1 = "明白了。 ";
            link.l1.go = "patria_Sl_9";
        break;
        
        case "patria_Sl_9":
            dialog.text = "计划如下: 首先, 我们将全力以赴攻击堡垒并摧毁它。 荷兰人会预期部队登陆, 但我们不会那样做 --从海上攻占堡垒通常伤亡最大。 相反, 我们将在岛上两个地点登陆突击队: 圣玛丽亚角和布兰卡泻湖, 然后从陆路向威廉斯塔德城门推进。 我下令将野战炮带上船 --库拉索没有难以通行的丛林, 我们可以毫无困难地用轮子将大炮推到地面上。 \n当荷兰人困惑于发生了什么时, 我们将从丛林中瞄准城镇, 并阻断从堡垒通过陆路派遣援军的任何机会。 之后, 我们将用大炮轰击城镇。 当然, 堡垒的驻军会试图进攻, 但他们无法对抗野战炮和我们的火枪手, 而且如果堡垒中的大炮仍然可用, 他们也无法将其带到丛林中。 \n此外, 我们的船只将模拟从海上登陆部队的准备工作, 以震慑敌人并降低他们的士气。 一段时间后, 当荷兰人充分意识到自己的绝望处境时, 我们将召集议员进行谈判。 你觉得如何, 船长? ";
            link.l1 = "绝妙的计划! 最棒的是我们不会在堡垒墙下损失任何士兵。 ";
            link.l1.go = "patria_Sl_10";
        break;
        
        case "patria_Sl_10":
            dialog.text = "很高兴你喜欢我的想法。 那我们出发吧! ";
            link.l1 = "出发! ";
            link.l1.go = "patria_Sl_11";
        break;
        
        case "patria_Sl_11":
            DialogExit();
            chrDisableReloadToLocation = true;
            pchar.questTemp.Patria = "epizode_11_continue";
            AddQuestRecord("Patria", "60");
            pchar.quest.Patria_CuracaoTimeOver.over = "yes"; // 移除2个月计时器
            LAi_SetActorType(npchar);
            ChangeCharacterAddressGroup(npchar, "PortRoyal_townhall", "goto", "goto4");
            LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 7.0);
            Patria_CuracaoSail();
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部有通过return退出的情况, 别忘了执行此卸载
}