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
            // --> 治愈的 dark waters (黑暗之水) 
            if (CheckAttribute(pchar, "questTemp.DWH_pastor"))
            {
                link.l1 = "神父, 我想谈谈托马斯.莫里森的女儿。 ";
                link.l1.go = "dwh_pastor_1";
            }
            if (CheckAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi"))
            {
                link.l1 = "神父, 托马斯让我转告您, 他接受忏悔之路, 将致力于行善, 并将不惜一切代价为教区提供一口新钟。 ";
                link.l1.go = "dwh_pastor_VD_5";
            }
            // < —治愈的 dark waters (黑暗之水) 
        break;

        // --> 治愈的 dark waters (黑暗之水) 
        case "dwh_pastor_1":
            dialog.text = "说吧, 我的孩子, 我在听。 ";
            link.l1 = "我知道您反对吉普赛人帮助那个女孩。 但您怎么能强迫 一 位父亲拒绝哪怕是拯救女儿的 一 丝机会呢? 她的方法或许有争议, 但她拥有可能有用的知识。 ";
            link.l1.go = "dwh_pastor_2";
            DelLandQuestMark(npchar);
        break;

        case "dwh_pastor_2":
            dialog.text = "我的孩子, 只有主能治愈那个女孩。 相信祂的安排是我们度过试炼的依靠。 如果托马斯虔诚祈祷, 遵循上帝的话语, 并慷慨捐献给教会, 主会聆听他的祈祷并施以怜悯。 ";
            if (IsCharacterPerkOn(pchar, "Trustworthy"))
            {
                link.l1 = "(值得信赖) 但您也必须承认, 主通过人来行事。 如果那个吉普赛人只是祂意志的工具呢? 如果祂的设计如此深奥, 我们凡人无法理解呢? 主的作为总是神秘莫测, 不是吗? ";
                link.l1.go = "dwh_pastor_VD_1";
                Notification_Perk(true, "Trustworthy");
            }
            else
            {
                link.l1 = "您在强迫一位父亲看着女儿日渐衰弱, 而不是让他尝试拯救她。 这是仁慈的吗? ";
                link.l1.go = "dwh_pastor_bez_VD_1";
                notification("能力未解锁", "Trustworthy");
            }
        break;

        case "dwh_pastor_VD_1":
            dialog.text = "你的话很明智, 船长。 但我仍然不能允许异端邪说渗入我们教众的核心, 并动摇我们最虔诚的信徒之一的信仰。 ";
            link.l1 = "没有什么比失去女儿更能动摇他的信仰了。 但如果您允许他使用一切手段, 即使那些被视为有罪的手段, 他的信仰会变得更强, 而不是更弱。 ";
            link.l1.go = "dwh_pastor_VD_2";
        break;

        case "dwh_pastor_VD_2":
            dialog.text = "但是... 这会给会众的其他人树立什么样的榜样呢? ";
            link.l1 = "一个榜样, 表明教会不是盲目惩罚, 而是引导和带领人们走向真正的忏悔。 圣经不是教导我们, 真诚的忏悔和善行可以赎回罪孽吗? 向教会慷慨捐赠可能是赎回的第一步。 ";
            link.l1.go = "dwh_pastor_VD_3";
        break;

        case "dwh_pastor_VD_3":
            dialog.text = "也许你是对的, 船长。 我愿意给托马斯这个机会。 但要知道 —如果他偏离正义之路并失去信仰, 你也将承担责任! 至于捐赠 —教会不需要财富, 我们拥有所需要的。 除了... 那口钟在西班牙人的袭击中损坏了... ";
            link.l1 = "我会把您的话转告托马斯。 感谢您的时间, 神父。 愿主保佑您。 ";
            link.l1.go = "dwh_pastor_VD_4";
        break;

        case "dwh_pastor_VD_4":
            DialogExit();
            DeleteAttribute(pchar, "questTemp.DWH_pastor");
            AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
            
            sld = CharacterFromID("DWH_Tomas");
            LAi_SetStayType(sld);
            sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
            sld.dialog.currentnode = "Tomas_11";
        break;

        case "dwh_pastor_bez_VD_1":
            dialog.text = "这不是无情, 船长, 这是信仰。 我们没有放弃女孩的命运, 我们把它交在主的手中。 如果托马斯祈祷。 相信并谦卑等待, 我确信主会聆听我们的祈祷并治愈她。 ";
            link.l1 = "您知道甚至岛上的贵族, 包括总督, 都使用过那个吉普赛人的服务。 他们并没有被逐出教会。 那您为什么对托马斯如此严格? ";
            link.l1.go = "dwh_pastor_bez_VD_2";
        break;

        case "dwh_pastor_bez_VD_2":
            dialog.text = "我当然知道, 我的孩子。 但他们是迷失的灵魂, 尚未被主的真光触及。 托马斯是我们教众的支柱, 最优秀的之一。 允许邪恶侵蚀他的信仰会危及整个教会, 我不能允许这样严重的罪孽。 ";
            link.l1 = "所以您甚至拒绝给一个小小的机会? 这真的是正义的吗? ";
            link.l1.go = "dwh_pastor_bez_VD_3";
        break;

        case "dwh_pastor_bez_VD_3":
            dialog.text = "你所说的救赎很可能导致毁灭。 我是从经验中说的。 有一次, 违背我的意愿, 一个像她一样的治疗者治疗了我的侄女。 一个小女孩, 她在痛苦中死去。 只有主知道她的灵魂是否被那些仪式定罪。 不要试图说服我 —这是徒劳的。 ";
            link.l1 = "很好。 如果这是您的最终决定, 我不会争辩。 愿主保佑您。 ";
            link.l1.go = "dwh_pastor_bez_VD_4";
        break;

        case "dwh_pastor_bez_VD_4":
            DialogExit();
            DeleteAttribute(pchar, "questTemp.DWH_pastor");
            
            AddQuestRecord("DWH", "4");
            
            sld = CharacterFromID("DWH_gypsy");
            LAi_SetCitizenType(sld);
            sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
            sld.dialog.currentnode = "gypsy_6";
            ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto23");
            LAi_SetImmortal(sld, true);
            AddLandQuestMark(sld, "questmarkmain");
            LAi_CharacterEnableDialog(sld);
        break;

        case "dwh_pastor_VD_5":
            dialog.text = "太好了, 我的孩子。 一口新钟将是他对主和教会奉献的象征。 让他做需要做的事, 但提醒他 —全能者的眼睛注视着每一个行为, 没有什么能逃脱祂的意志。 ";
            link.l1 = "就这样吧, 神父。 再会。 ";
            link.l1.go = "dwh_pastor_VD_6";
            DelLandQuestMark(npchar);
        break;

        case "dwh_pastor_VD_6":
            DialogExit();
            DeleteAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi");
            AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
            
            sld = CharacterFromID("DWH_Tomas");
            LAi_SetStayType(sld);
            sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
            sld.dialog.currentnode = "Tomas_15";
            
            sld = CharacterFromID("DWH_gypsy");
            LAi_SetActorType(sld);
            ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "barmen", "bar1");
            DelLandQuestMark(sld);
            LAi_RemoveLoginTime(sld);
        break;
        // <-- 治愈的 dark waters (黑暗之水) 
    }
    UnloadSegment(NPChar.FileDialog2);  // 若switch内部某处通过return退出, 切记执行卸载
}