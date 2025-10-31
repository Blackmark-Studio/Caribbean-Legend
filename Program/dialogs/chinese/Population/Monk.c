// 杰森街头修士通用对话
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    int i, iTemp, iTest;
    string sTemp, sTitle;

    DeleteAttribute(&Dialog,"Links");

    makeref(NPChar,CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);
    
    // 调用城市相关对话 -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
    {
        ProcessCommonDialog(NPChar, Link, NextDiag);
        UnloadSegment(NPChar.FileDialog2);
    }
    // 调用城市相关对话 <--
    
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);
    
    iTest = FindColony(NPChar.City);
    ref rColony;
    if (iTest != -1)
    {
        rColony = GetColonyByIndex(iTest);
    }
    
    switch(Dialog.CurrentNode)
    {
        case "First time":
            //--> 首次见面对话
            if (npchar.quest.meeting == "0")
            {
                if (CheckAttribute(npchar, "quest.donation"))// 捐赠
                {
                    dialog.text = "日安, 我的孩子。 我请求你展现善意, 捐赠几枚银币, 以帮助穷人。 拯救你的灵魂, 并支持圣母教会。 ";
                    link.l1 = "好的, 神父, 我认为我们都应该按照基督和教会的教导互相帮助。 你能告诉我这些钱将用于何处吗? ";
                    link.l1.go = "donation";
                    link.l2 = "原谅我, 神父, 但我现在一贫如洗。 ";
                    link.l2.go = "exit";
                    npchar.quest.meeting = "1";
                    DeleteAttribute(npchar, "talker"); // 移除对话标记
                    break;
                }
                bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
                if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Monkpassenger") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) < 3)// 修士乘客
                {
                    dialog.text = "日安, 我的孩子。 我想请你帮个忙, 当然我会付钱。 ";
                    link.l1 = "我在听, 神父。 你需要什么? ";
                    link.l1.go = "passenger";
                    link.l2 = "非常抱歉, 神父, 但我必须走了。 ";
                    link.l2.go = "exit";
                    npchar.quest.meeting = "1";
                    DeleteAttribute(npchar, "talker"); // 移除对话标记
                    break;
                }
                if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.capellan") && !CheckAttribute(pchar, "questTemp.ShipCapellan"))// 船载牧师
                {
                    dialog.text = "问候你, 我的孩子。 我猜你是船长, 所以我有个提议给你。 ";
                    link.l1 = "我在听, 神父。 ";
                    link.l1.go = "capellan";
                    npchar.quest.meeting = "1";
                    DeleteAttribute(npchar, "talker"); // 移除对话标记
                    break;
                }
                dialog.text = PCharRepPhrase(LinkRandPhrase("问候你, 我的孩子。 你有什么烦恼? ","问候你, 我的孩子。 如果你想忏悔, 就去找牧师。 ","问候你, 我的孩子。 ‘你当在年幼时记念造你的主。 ’"),LinkRandPhrase("问候你, 我的孩子。 你有什么烦恼? ","日安, 我的孩子, 愿上帝保佑你! ","日安, 我的孩子, 愿上帝的脸光照你! "));
                link.l1 = LinkRandPhrase("也问候你, 神父。 你好吗? ","日安, 神父。 你的教区怎么样? ","你好吗, 神父? ");
                link.l1.go = "check";// 检查可能的任务发放
                link.l2 = RandPhraseSimple("我有个问题问你, 神父。 ", "我需要信息。 ");
                link.l2.go = "quests";// (转发到城市文件)
                if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10)
                {
                    link.l3 = "神父, 我船上有人。 他们是奴隶, 既有基督徒也有未受洗的异教徒。 我希望你为异教徒施洗, 并为基督徒主持圣餐。 之后, 为了上帝和教会的荣耀, 我会释放他们所有人。 ";
                    link.l3.go = "slaves";
                }
                if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
                {
                    link.l4 = "神父, 我希望你为我的船祝福, 并为我的船员主持弥撒。 这需要多少钱? ";
                    link.l4.go = "shipshine";
                }
                link.l10 = LinkRandPhrase("抱歉, 神父, 但我必须走了。 ","抱歉打扰你, 神父。 ","我需要回到我的船上, 神父。 再见! ");
                link.l10.go = "exit";
                npchar.quest.meeting = "1";
            }
            else
            {
                //--> 再次见面对话
                dialog.text = LinkRandPhrase("又是你, 我的孩子? 你想要什么? ","还有什么要告诉我的吗, 我的孩子? ","很高兴再次见到你, 我的孩子。 ");
                link.l1 = LinkRandPhrase("也问候你, 神父。 你好吗? ","日安, 神父。 你的教区怎么样? ","你好吗, 神父? ");
                link.l1.go = "check";// 检查可能的任务发放
                link.l2 = RandPhraseSimple("我有个问题问你, 神父。 ", "我需要信息。 ");
                link.l2.go = "quests";// (转发到城市文件)
                if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES)*10 && !CheckAttribute(npchar, "quest.slaves"))
                {
                    link.l3 = "神父, 我船上有人。 他们是奴隶, 既有基督徒也有未受洗的异教徒。 我希望你为异教徒施洗, 并为基督徒主持圣餐。 之后, 为了上帝和教会的荣耀, 我会释放他们所有人。 ";
                    link.l3.go = "slaves";
                }
                if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
                {
                    link.l4 = "神父, 我希望你为我的船祝福, 并为我的船员主持弥撒。 这需要多少钱? ";
                    link.l4.go = "shipshine";
                }
                link.l10 = LinkRandPhrase("抱歉, 神父, 但我必须走了。 ","抱歉打扰你, 神父。 ","我需要到我的船上, 神父。 再见! ");
                link.l10.go = "exit";
            }
            NextDiag.TempNode = "First time";
        break;
        
        case "check":
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) < 3 && !CheckAttribute(npchar, "quest.monkletter") && !CheckAttribute(pchar, "GenQuest.Monkletter") && !CheckAttribute(npchar, "quest.passenger")) // 教会急件
            {
                pchar.GenQuest.Monkletter.City = FindFriendCityToMC(false);
                pchar.GenQuest.Monkletter.StartCity = npchar.city;// 任务发放城市
                dialog.text = "我有一件急事找你, 我的孩子。 我需要把这些文件交给" + XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen") + "的牧师。 你会朝那个方向航行吗? 这些文件必须在两周内送达... ";
                link.l1 = "很简单, 神父。 把那些文件给我, 我会把它们送到" + XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen") + "。 ";
                link.l1.go = "Monkletter";
                link.l2 = "我很乐意这么做, 神父, 但我要朝另一个方向航行。 ";
                link.l2.go = "exit_monkletter";
                npchar.quest.monkletter = "true";
                break;
            }
            if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) > 5 && sti(pchar.rank < 11) && !CheckAttribute(npchar, "quest.churchbooks") && !CheckAttribute(pchar, "GenQuest.Churchbooks") && !CheckAttribute(npchar, "quest.passenger")) // 运送祈祷书
            {
                pchar.GenQuest.Churchbooks.StartCity = npchar.city;// 任务发放城市
                pchar.GenQuest.Churchbooks.Nation = npchar.nation;
                dialog.text = "我的孩子, 你愿意帮我处理一件紧急的事情吗? 我们的教堂缺少圣经和祈祷书, 这些是我们提供给所有需要的人的。 \n你能航行到" + NationNameGenitive(sti(npchar.nation)) + "最近的殖民地, 从当地教堂取一些圣经和祈祷书并带到这里来吗? 请尽量在一个月内完成, 我们剩下的不多了。 ";
                link.l1 = "我很乐意帮助你的教堂。 我可以从任何牧师那里得到这些书吗? ";
                link.l1.go = "Churchbooks";
                link.l2 = "我很乐意这么做, 神父, 但我现在不能。 ";
                link.l2.go = "exit_churchbooks";
                npchar.quest.churchbooks = "true";
                break;
            }
            
            dialog.text = RandPhraseSimple("没事的, 我的孩子。 谢谢你的客气话。 ", "我们的教区很好, 我的孩子。 谢谢你的关心。 ");
            link.l1 = "那我得走了, 神父。 ";
            link.l1.go = "exit";
        break;
        
//-------------------------------------------------捐赠------------------------------------------------
        case "donation":
            sTemp = DonationType();
            dialog.text = "当然, 我的孩子。 " + sTemp + "";
            link.l1 = "什么样的捐赠会被认为是足够的? ";
            link.l1.go = "donation_1";
        break;
        
        case "donation_1":
            dialog.text = "这完全取决于你的钱包和个人意愿, 我的孩子。 ‘上帝爱乐意奉献的人。 ’我们对任何捐赠都深表感激。 ";
            link.l1 = "100比索";
            link.l1.go = "donation_rate_1";
            link.l2 = "1000比索";
            link.l2.go = "donation_rate_2";
            link.l3 = "5000比索";
            link.l3.go = "donation_rate_3";
            link.l4 = "10000比索";
            link.l4.go = "donation_rate_4";
        break;
        
        case "donation_rate_1":// 没有额外奖励
            if (sti(pchar.money) >= 100)
            {
                AddMoneyToCharacter(pchar, -100);
                dialog.text = "感谢你的硬币, 我的孩子! 它们将用于正当的事业! ";
                link.l1 = "不客气, 神父。 ";
                link.l1.go = "exit";
            }
            else
            {
                dialog.text = "‘不要自欺, 神是轻慢不得的。 人种的是什么, 收的也是什么。 顺着情欲撒种的, 必从情欲收败坏; 顺着圣灵撒种的, 必从圣灵收永生。 ’";
                link.l1 = "哈哈! 收起你的说教, 我不做慈善。 滚开! ";
                link.l1.go = "donation_exit";
            }
        break;
        
        case "donation_rate_2":
            if (sti(pchar.money) >= 1000)
            {
                AddMoneyToCharacter(pchar, -1000);
                dialog.text = "我感谢你, 我的孩子。 这笔钱将真正帮助我们的教区使命。 愿你蒙福! ";
                link.l1 = "祝你好运, 神父! ";
                link.l1.go = "exit";
                AddCharacterHealth(pchar, 5);
                AddCharacterExpToSkill(pchar, "Leadership", 20);
                AddCrewMorale(pchar, 2);
            }
            else
            {
                dialog.text = "上帝的惩罚在等着你, 小子! 嘲笑基督圣教会的仆人是亵渎神明! ";
                link.l1 = "哈哈! 我不做慈善。 滚开! ";
                link.l1.go = "donation_exit";
            }
        break;
        
        case "donation_rate_3":
            if (sti(pchar.money) >= 5000)
            {
                AddMoneyToCharacter(pchar, -5000);
                dialog.text = "我甚至无法想象你会如此慷慨, 我的孩子! 我会在给主教的下一封信中提到你, 我们每天都会为你祈祷! 我祝福你, 并感激地接受你的钱! ";
                link.l1 = "金钱若不用来实现上帝的旨意, 就毫无价值! 祝你好运, 神父! ";
                link.l1.go = "exit";
                AddCharacterHealth(pchar, 5);
                AddCharacterExpToSkill(pchar, "Leadership", 40);
                AddCrewMorale(pchar, 3);
                ChangeCharacterComplexReputation(pchar, "nobility", 1);
                ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
            }
            else
            {
                dialog.text = "上帝的惩罚在等着你, 小子! 嘲笑基督圣教会的仆人是亵渎神明! ";
                link.l1 = "哈哈! 我不做慈善。 滚开! ";
                link.l1.go = "donation_exit";
            }
        break;
        
        case "donation_rate_4":
            if (sti(pchar.money) >= 10000)
            {
                AddMoneyToCharacter(pchar, -10000);
                dialog.text = "什么... 我没听错吧? 你真的要捐赠一万比索! ? 我祝福你, 并感激地接受你的钱。 我会在给主教的下一封信中提到你, 我们每天都会为你祈祷! 这对教会是巨大的帮助! ";
                link.l1 = "‘多给谁, 就向谁多取, ’对吗? 祝你好运, 神父。 ";
                link.l1.go = "exit";
                AddCharacterHealth(pchar, 10);
                AddCharacterExpToSkill(pchar, "Leadership", 60);
                AddCrewMorale(pchar, 5);
                ChangeCharacterComplexReputation(pchar, "nobility", 1);
                ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
                ChangeCrewExp(pchar, "Sailors", 5);
                ChangeCrewExp(pchar, "Cannoners", 5);
                ChangeCrewExp(pchar, "Soldiers", 5);
            }
            else
            {
                dialog.text = "上帝的惩罚在等着你, 小子! 嘲笑基督圣教会的仆人是亵渎神明! ";
                link.l1 = "哈哈! 我不做慈善。 滚开! ";
                link.l1.go = "donation_exit";
            }
        break;
        
        case "donation_exit":
            DialogExit();
            ChangeCharacterComplexReputation(pchar, "nobility", -1);
            AddCharacterHealth(pchar, -5);
            LAi_CharacterDisableDialog(npchar);
        break;
        
//-------------------------------------------释放奴隶---------------------------------------------------
        case "slaves":
            dialog.text = "当然, 我的孩子。 帮助这些可怜的人是我们的神圣职责。 我会按你的要求去做。 ";
            link.l1 = "谢谢你, 神父。 我会为每个受洗和领圣餐的囚犯捐赠十个八里亚尔。 ";
            link.l1.go = "slaves_1";
        break;
        
        case "slaves_1":
            AddMoneyToCharacter(pchar, -GetSquadronGoods(pchar, GOOD_SLAVES) * 10);
            dialog.text = "虽然不是必须的, 但我感激地接受你的奉献。 你的钱将用于我们教区的各种传教活动。 你能带我到你的船上吗? ";
            link.l1 = "是的, 神父。 跟我来。 ";
            link.l1.go = "slaves_2";
        break;
        
        case "slaves_2":
            npchar.quest.slaves = "true";
            DialogExit();
            SetLaunchFrameFormParam("两小时后" + NewStr() + "奴隶已被释放", "Monk_RemoveSlaves", 0, 4);
            LaunchFrameForm();
            WaitDate("", 0, 0, 0, 2, 10); //转动时间
            RecalculateJumpTable();
        break;
//< —释放奴隶

//----------------------------------------------祝福船只------------------------------------------------
        case "shipshine":
            //寻找最高船级
            iTemp = 7;
            for (i = 0; i < COMPANION_MAX; i++)
            {
                int iIdx = GetCompanionIndex(GetMainCharacter(), i);
                if (iIdx >= 0)
                {
                    sld = GetCharacter(iIdx);
                    if (GetCharacterShipClass(sld) < iTemp) iTemp = GetCharacterShipClass(sld);
                }
            }
            switch (GetCompanionQuantity(pchar))
            {
                case 1: 
                    sTemp = "我的舰队中只有一艘船, 它是" + iTemp + "级。 ";
                    pchar.GenQuest.Shipshine.Money = 5000 * (7 - iTemp);
                break;
                case 2:
                    sTemp = "我的舰队中有两艘船, 最大的一艘是" + iTemp + "级。 ";
                    pchar.GenQuest.Shipshine.Money = makeint(1.8 * (5000 * (7 - iTemp)));
                break;
                case 3:
                    sTemp = "我的舰队中有三艘船, 最大的一艘是" + iTemp + "级。 ";
                    pchar.GenQuest.Shipshine.Money = makeint(2.6 * (5000 * (7 - iTemp)));
                break;
                case 4:
                    sTemp = "我的舰队中有四艘船, 最大的一艘是" + iTemp + "级。 ";
                    pchar.GenQuest.Shipshine.Money = makeint(3.4 * (5000 * (7 - iTemp)));
                break;
                case 5:
                    sTemp = "我的舰队中有五艘船, 最大的一艘是" + iTemp + "级。 ";
                    pchar.GenQuest.Shipshine.Money = makeint(4.2 * (5000 * (7 - iTemp)));
                break;
            }
            dialog.text = "这取决于你舰队中船只的总数和它们的大小。 ";
            link.l1 = "" + sTemp + "";
            link.l1.go = "shipshine_1";
        break;
        
        case "shipshine_1":
            dialog.text = "这将花费你" + FindRussianMoneyString(sti(pchar.GenQuest.Shipshine.Money)) + ", 我的孩子。 ";
            if (sti(pchar.money) >= sti(pchar.GenQuest.Shipshine.Money))
            {
                link.l1 = "我可以付这笔钱, 神父。 拿去吧。 ";
                link.l1.go = "shipshine_2";
            }
            link.l2 = "不幸的是, 我身上没有那么多钱。 ";
            link.l2.go = "shipshine_exit";
        break;
        
        case "shipshine_2":
            AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Shipshine.Money));
            dialog.text = "很好, 我的孩子。 让我收集圣器, 然后我们去港口。 ";
            link.l1 = "跟我来, 神父。 ";
            link.l1.go = "shipshine_3";
        break;
        
        case "shipshine_3":
            DialogExit();
            SetLaunchFrameFormParam("几小时后" + NewStr() + "神父已在你的船上举行弥撒并为其祝福", "Monk_Shipshine", 0, 4);
            LaunchFrameForm();
            WaitDate("", 0, 0, 0, GetCompanionQuantity(pchar), 10); //转动时间
            RecalculateJumpTable();
        break;
        
        case "shipshine_exit":
            DialogExit();
            DeleteAttribute(Pchar, "GenQuest.Shipshine");
        break;
//< —祝福船只

//------------------------------------------船载牧师-----------------------------------------------
        case "capellan":
            dialog.text = "你好, 船长, 请允许我介绍自己。 我是一名牧师, 在军舰上担任 chaplain 有相当丰富的经验。 我离开上一艘船是因为船长和我在道德上有一些分歧。 你想让我加入你的船员吗? ";
            link.l1 = "船上有牧师? 告诉我, 神父, 船载牧师的职责是什么? ";
            link.l1.go = "capellan_1";
            pchar.questTemp.ShipCapellan = "true";
        break;
        
        case "capellan_1":
            dialog.text = "这很明显。 我为你和你的船员向上帝祈祷, 每天举行弥撒, 为你的人祝福, 并在战斗前听取忏悔。 上帝的话语会给你船员的双手和精神带来力量。 你的船员将有机会定期领受圣餐和忏悔。 相信我, 处于恩典状态的水手在面对困境时会坚定不移, 而不敬虔的水手则会畏缩。 \n我对自己的要求不多: 为我的家乡教区一次性支付五万比索, 在船舱里有一个简单的铺位, 以及和你的军官一样的伙食。 就这样。 ";
            if (sti(pchar.money) >= 50000)
            {
                link.l1 = "有趣... 你说得对, 一个好船长不仅要关心船员的身体, 还要关心他们的灵魂。 欢迎登船, 神父! ";
                link.l1.go = "capellan_2";
            }
            link.l2 = "不, 神父。 对不起, 我负担不起你的服务。 ";
            link.l2.go = "capellan_exit";
        break;
        
        case "capellan_exit":
            DialogExit();
            LAi_CharacterDisableDialog(npchar);
        break;
        
        case "capellan_2":
            AddMoneyToCharacter(pchar, -50000);
            chrDisableReloadToLocation = true;//关闭地点
            dialog.text = "感谢你的信任, 我的孩子。 你明智地花了钱。 但我警告你, 我只服务于有价值的船长, 无论是商人还是私掠者, 都无关紧要。 但我永远不会在海盗船上传教! \n所以, 如果你升起魔鬼的海盗旗, 我会在第一个港口立即离开你的船。 ";
            link.l1 = "我会考虑的, 神父, 我会尽量不让你失望。 请上船并向船员介绍自己! ";
            link.l1.go = "capellan_3";
        break;
        
		case "capellan_3":
			DialogExit();
			pchar.questTemp.ShipCapellan.id = npchar.id;
			AddDialogExitQuestFunction("Monk_Capellan_DlgExit");
		break;
        
        case "capellan_4":
            dialog.text = "需要什么吗, 我的孩子? ";
            link.l1 = "不, 没什么, 神父。 ";
            link.l1.go = "exit";
            link.l2 = "神父, 我希望你在下一个港口离开船。 我不会进一步解释。 ";
            link.l2.go = "capellan_5";
            NextDiag.TempNode = "capellan_4";
        break;
        
        case "capellan_5":
            dialog.text = "很好, 我的孩子。 这里由你负责。 我会在下一个定居点离开你的船。 ";
            link.l1 = "感谢你的理解, 神父。 ";
            link.l1.go = "capellan_6";
        break;
        
        case "capellan_6":
            DialogExit();
            LAi_CharacterDisableDialog(npchar);
            ShipCapellan_Remove();
        break;
        
        case "capellan_7":
            dialog.text = "呸, 船长! 我警告过你, 如果你升起海盗旗, 我就会离开你! 我将在下一个港口离开你的船。 我会为你立即悔改并回到圣母教会的怀抱祈祷。 ";
            link.l1 = "好吧, 该死的... ";
            link.l1.go = "exit";
            NextDiag.TempNode = "capellan_7";
        break;
//< —船载牧师

//--------------------------------------------修士乘客---------------------------------------------------
        case "passenger":
            if (hrand(19) < 15) SetPassengerParameter("Monkpassenger", false);
            else SetPassengerParameter("Monkpassenger", true);
            if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
            {
                dialog.text = "我的" + GetSexPhrase("儿子", "女儿") + ", 我必须到达" + XI_ConvertString("Colony" + pchar.GenQuest.Monkpassenger.City) + ", 它在" + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City) + "Dat") + ", 行程" + FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)) + "。 我会为此支付你" + FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)) + "。 你觉得怎么样? ";
            }
            else
            {
                dialog.text = "我的" + GetSexPhrase("儿子", "女儿") + ", 主的作为神秘莫测, 所以我在寻找一位可靠的船长。 你能帮我到达" + XI_ConvertString("Colony" + pchar.GenQuest.Monkpassenger.City) + "吗? 它在" + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City) + "Dat") + "。 我知道这就像前往炽热的地狱, 因为我们的敌人从不睡觉。 我知道你不是耶稣基督, 但我也不是使徒, 因此我有一些积蓄。 " + FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money)) + "对你来说足够吗? ";
            }
            link.l1 = "我同意, 神父。 ";
            link.l1.go = "passenger_1";
            link.l2 = "对不起, 神父, 但我要朝不同的方向航行。 无法帮助你。 ";
            link.l2.go = "passenger_exit";
            npchar.quest.passenger = true;
        break;
        
        case "passenger_exit":
            dialog.text = "这是上帝对所有人的旨意, 我的孩子。 我会等待另一艘船。 愿你平安! ";
            link.l1 = "再见, 神父。 ";
            link.l1.go = "exit";
            DeleteAttribute(pchar, "GenQuest.Monkpassenger");
        break;
        
        case "passenger_1":
            dialog.text = "愿上帝保佑你! 到达目的地后你会得到报酬。 ";
            link.l1 = "前往我的船, 神父。 我们很快就要出发了。 ";
            link.l1.go = "passenger_2";
        break;
        
        case "passenger_2":
            DialogExit();
            pchar.GenQuest.Monkpassenger.id = npchar.id;
            DeleteAttribute(npchar, "LifeDay");
            LAi_RemoveLoginTime(npchar);
            DeleteAttribute(npchar, "CityType");//删除幽灵标志, 否则会出现空城市
            LAi_SetImmortal(npchar, true);
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
            AddPassenger(pchar, npchar, false);
            SetCharacterRemovable(npchar, false);
            sTitle = npchar.index + "Citizpassenger";

// LDH 13Sep17 - 不要添加到现有的 Citizpassenger 记录 -->
// 通过将任务记录复制到新名称并删除旧记录来'重命名'任务记录
            if (CheckAttribute(pchar, "questinfo." + sTitle))
            {
                string sTempLDH = frand(1);
                sTempLDH = strcut(sTempLDH, 2, 5);    // 4 位随机数字
                string sTitle1 = sTitle + sTempLDH;

                aref arTo, arFrom;
                makearef(arFrom, pchar.questinfo.(sTitle));
                makearef(arTo,   pchar.questinfo.(sTitle1));
                CopyAttributes(arTo, arFrom);
                pchar.questinfo.(sTitle1) = "";

                DeleteAttribute(pchar, "questinfo." + sTitle);

                Trace("重复的 Citizpassenger 记录 " + sTitle + " 已复制到 " + sTitle1 + " **");
            }
// <--

            AddQuestRecordEx(sTitle, "Citizpassenger", "1");
            AddQuestUserDataForTitle(sTitle, "sType", "修道士");
            AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
            sTemp = XI_ConvertString("Colony" + pchar.GenQuest.Monkpassenger.City + "Gen") + ", 它在" + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City) + "Voc") + "。 "; // belamour gen
            AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
            AddQuestUserData(sTitle, "sName", GetFullName(npchar));
            AddQuestUserData(sTitle, "sCity", sTemp);
            AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)));
            AddQuestUserData(sTitle, "sSex", GetSexPhrase("", ""));
            if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)));
            else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money)));
            AddQuestUserData(sTitle, "sName", GetFullName(npchar));
            pchar.quest.Monkpassenger.win_condition.l1 = "location";
            pchar.quest.Monkpassenger.win_condition.l1.location = pchar.GenQuest.Monkpassenger.City + "_town";
            pchar.quest.Monkpassenger.function = "Monkpassenger_complete";
            SetFunctionTimerCondition("Monkpassenger_Over", 0, 0, sti(pchar.GenQuest.Monkpassenger.DaysQty), false);
        break;
        
        case "passenger_3":
            pchar.quest.Monkpassenger_Over.over = "yes"; //移除计时器
            dialog.text = "谢谢你, 我的" + GetSexPhrase("儿子", "女儿") + "。 你已经履行了你的承诺, 现在轮到我了。 按照我承诺的拿你的钱吧。 ";
            link.l1 = "谢谢你。 祝你好运, 神父。 ";
            link.l1.go = "passenger_4";
        break;
		
        case "passenger_4":
            DialogExit();
            npchar.lifeday = 0;
            RemovePassenger(Pchar, npchar);
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
            ChangeCharacterComplexReputation(pchar, "nobility", 1);
            ChangeCharacterComplexReputation(pchar, "fame", 1);
            OfficersReaction("good");                
            AddCharacterExpToSkill(pchar, "Sailing", 80);
            AddCharacterExpToSkill(pchar, "Leadership", 20);
            if (CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
            {
                AddCharacterExpToSkill(pchar, "Sneak", 50);
                TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Monkpassenger.Money));
            }
            else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Monkpassenger.Money));
            sTitle = npchar.index+"Citizpassenger";
            AddQuestRecordEx(sTitle, "Citizpassenger", "3");
            CloseQuestHeader(sTitle);
            DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
        break;
//< —修士乘客

//---------------------------------------------教会急件-------------------------------------------------
        case "exit_monkletter":
            DialogExit();
            DeleteAttribute(pchar, "GenQuest.Monkletter");
        break;
        
        case "Monkletter":
            dialog.text = "给你。 拿着这个包裹, 我的孩子。 记住你只有两周时间来送达。 牧师在等着它。 去吧, 愿上帝与你同在! ";
            link.l1 = "我不会让你失望的, 神父。 再见。 ";
            link.l1.go = "Monkletter_1";
        break;
        
        case "Monkletter_1":
            DialogExit();
            GiveItem2Character(pchar, "letter_church");
            ReOpenQuestHeader("Monkletter");
            AddQuestRecord("Monkletter", "1");
            AddQuestUserData("Monkletter", "sSex1", GetSexPhrase("",""));
            AddQuestUserData("Monkletter", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.City+"Gen"));
            AddQuestUserData("Monkletter", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Monkletter.StartCity));
            SetFunctionTimerCondition("Monkletter_Over", 0, 0, 15, false);
            OfficersReaction("good");
        break;
//< —教会急件

//-------------------------------------------运送祈祷书---------------------------------------------
        case "exit_churchbooks":
            DialogExit();
            DeleteAttribute(pchar, "GenQuest.Churchbooks");
        break;

        case "Churchbooks":
            dialog.text = "是的。 你可以在任何" + NationNameGenitive(sti(npchar.nation)) + "殖民地找到它们。 把你找到的所有书籍带给我们教堂的牧师。 愿上帝保佑你! ";
            link.l1 = "谢谢! 你很快就会收到你的书。 ";
            link.l1.go = "Churchbooks_1";
        break;
        
        case "Churchbooks_1":
            DialogExit();
            ReOpenQuestHeader("Churchbooks");
            AddQuestRecord("Churchbooks", "1");
            AddQuestUserData("Churchbooks", "sNation", NationNameGenitive(sti(pchar.GenQuest.Churchbooks.Nation)));
            AddQuestUserData("Churchbooks", "sStartCity", XI_ConvertString("Colony"+pchar.GenQuest.Churchbooks.StartCity));
            SetFunctionTimerCondition("Churchbooks_Over", 0, 0, 30, false);
            pchar.GenQuest.Churchbooks = "go";
            switch (rand(4))
            {
                case 0: pchar.GenQuest.Churchbooks.Item = "amulet_2"; break;
                case 1: pchar.GenQuest.Churchbooks.Item = "amulet_3"; break;
                case 2: pchar.GenQuest.Churchbooks.Item = "amulet_6"; break;
                case 3: pchar.GenQuest.Churchbooks.Item = "amulet_7"; break;
                case 4: pchar.GenQuest.Churchbooks.Item = "amulet_10"; break;
            }
            OfficersReaction("good");
        break;
//< —运送祈祷书
        
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
    }
}

string DonationType()
{
    string sText;
    switch (hrand(9))
    {
        case 0: sText = "我正在筹集资金建造" + LinkRandPhrase("一座小教堂","一所救济院","一家医院") + "。 当地市民施舍甚少, 所以我必须向像你这样富有的人求助。 "; break;
        case 1: sText = "我正在为我们的教堂筹集捐款。 水手们通常没有太多时间去上帝的殿堂, 但每个人都必须尽力拯救自己的灵魂。 "; break;
        case 2: sText = "我正在筹集资金为我们的救济院购买食物和药品, 那里收容着病人。 寡妇。 孤儿和体弱者。 请捐款吧, 先生, 因为若不是上帝的恩典, 我们都可能陷入同样的境地。 "; break;
        case 3: sText = "我正在筹集资金购买新的圣器, 我们从欧洲带来的那些已经因长期使用而破损。 照顾我们的教会是每个基督徒的责任。 "; break;
        case 4: sText = "我正在筹集资金翻新我们的教堂, 屋顶漏水严重, 长椅也需要修理。 照顾我们的教会是每个基督徒的责任。 "; break;
        case 5: sText = "我正在筹集资金聘请一位优秀的艺术家来绘制我们教堂的墙壁, 并为我们那些不识字的教友绘制圣经场景。 照顾自己的教会是每个基督徒的责任。 "; break;
        case 6: sText = "我正在筹集资金为我们的教堂建造一个新的主祭坛。 我们的教区很穷, 我们希望为圣体提供一个高贵的座位。 我确实希望得到你的帮助。 "; break;
        case 7: sText = "我们医院里有很多因海盗袭击而受伤的水手。 他们需要药品和绷带。 请帮助他们, 因为你能真正理解普通水手的痛苦。 "; break;
        case 8: sText = "我正在努力为我们最贫穷的市民筹集衣服和食物的钱。 他们唯一的希望就是我们的圣教会。 请帮助他们。 "; break;
        case 9: sText = "我打算深入我们的岛屿进行传教工作, 将基督福音的光芒带给迷失的异教印第安灵魂。 我正在为这次远征筹集资金。 请帮助我们的善举! "; break;
    }
    return sText;
}