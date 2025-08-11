// 贵族通用对话系统
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;
    int iTemp, iTest;
    string sTemp, sTitle;
    float locx, locy, locz;

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
    
    iTest = FindColony(NPChar.City); // 170712
    ref rColony;
    if (iTest != -1)
    {
        rColony = GetColonyByIndex(iTest);
    }
    
    switch(Dialog.CurrentNode)
    {
        case "First time":
            //--> 检查国家间关系
            if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
            {
                dialog.text = NPCStringReactionRepeat("哼。 你挂着"+NationNameGenitive(sti(pchar.nation))+"的旗帜航行, 伙计。 你到底在我们镇上干什么? 快滚! ", 
                    "我可不想被怀疑是"+NationNameAblative(sti(pchar.nation))+"的朋友! 快滚, 否则我就叫卫兵了! ", 
                    "这是你最后的机会。 否则你只能自食其果。 ",
                    "我警告过你了。 现在你要为你的无礼付出代价, 混蛋! ", "block", 1, npchar, Dialog.CurrentNode);
                link.l1 = HeroStringReactionRepeat("真是个爱国者, 哈! ", 
                    "好吧, 好吧, 冷静点。 我这就走。 ",
                    "别这么大声嚷嚷。 我走就是了。 ", 
                    "什么? ! ", npchar, Dialog.CurrentNode);
                link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
                break;
            }
            
            //--> 检查声望 - 贵族鄙视声望极低的人
            if (sti(pchar.reputation.nobility) < 10)
            {
                dialog.text = NPCStringReactionRepeat("看看这个! 我们的卫兵怎么能让你这样的混蛋在镇上闲逛? 简直难以置信... ", 
                    "滚远点, 我甚至不想和你说话! 刽子手... ", 
                    "这是你最后的机会。 否则你只能自食其果。 ",
                    "我警告过你了。 现在你要为你的无礼付出代价, 混蛋! ", "block", 1, npchar, Dialog.CurrentNode);
                link.l1 = HeroStringReactionRepeat("嘿嘿! 对我尊重一点, 先生! ", 
                    "看看你自己, 圣人... ",
                    "冷静点... ", 
                    "什么? ! ", npchar, Dialog.CurrentNode);
                link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
                break;
            }
            
            //--> 首次见面对话
            if(NPChar.quest.meeting == "0")
            {
                // 检查港口是否有船
                bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
                if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && CheckAttribute(pchar, "questTemp.StatusCity") && pchar.questTemp.StatusCity == npchar.city)//贵族乘客
                {
                    dialog.text = "你好, "+GetAddress_Form(NPChar)+"。 我看你是一艘坚固船只的船长。 我想请你帮个忙。 你可以接受也可以拒绝。 ";
                    link.l1 = "我在听, "+GetAddress_FormToNPC(NPChar)+"。 你是什么意思? ";
                    link.l1.go = "passenger";
                    link.l2 = "对不起, "+GetAddress_FormToNPC(NPChar)+", 但我赶时间。 ";
                    link.l2.go = "exit";
                    npchar.quest.meeting = "1";
                    DeleteAttribute(npchar, "talker"); //移除对话标记
                    break;
                }
                if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsUniversalShipType(pchar), IsMerchantShipType(pchar)))//贵族乘客
                {
                    dialog.text = "你好, "+GetAddress_Form(NPChar)+"。 我看你是一艘坚固船只的船长。 我想请你帮个忙。 你可以接受也可以拒绝。 ";
                    link.l1 = "我在听, "+GetAddress_FormToNPC(NPChar)+"。 你是什么意思? ";
                    link.l1.go = "passenger";
                    link.l2 = "对不起, "+GetAddress_FormToNPC(NPChar)+", 但我赶时间。 ";
                    link.l2.go = "exit";
                    npchar.quest.meeting = "1";
                    DeleteAttribute(npchar, "talker"); //移除对话标记
                    break;
                }
                if (CheckAttribute(npchar, "quest.donation"))//请求捐款
                {
                    dialog.text = "啊哈, 很高兴在我们小镇见到一位绅士! 我相信你刚从欧洲来。 听着, 我想请你帮个忙 —作为绅士之间的帮助。 我希望你能正确理解我的意思。 ";
                    link.l1 = "日安, 先生。 我在听。 ";
                    link.l1.go = "donation";
                    npchar.quest.meeting = "1";
                    break;
                }
                if (CheckAttribute(npchar, "quest.lombard") && !CheckAttribute(pchar, "GenQuest.Noblelombard"))//家族遗物
                {
                    dialog.text = "日安, "+GetAddress_Form(NPChar)+"! 很高兴在我们镇的街道上遇到一位绅士! 能占用你几分钟时间吗? ";
                    link.l1 = "当然可以, 先生。 我在听。 ";
                    link.l1.go = "lombard";
                    npchar.quest.meeting = "1";
                    break;
                }
                if (CheckAttribute(npchar, "quest.slaves") && !CheckAttribute(&Colonies[FindColony(npchar.city)], "questslaves"))//运送奴隶
                {
                    dialog.text = "日安, 船长! 很高兴见到你, 因为你看起来像是一个能解决问题的人。 ";
                    link.l1 = "这要看是什么问题了。 我擅长用暴力解决问题, 这是你想要的吗, "+GetAddress_FormToNPC(NPChar)+"? ";
                    link.l1.go = "slaves";
                    npchar.quest.meeting = "1";
                    break;
                }
                dialog.text = RandPhraseSimple("你好, "+GetAddress_Form(NPChar)+"。 你有什么事吗? ", "你想要什么, 先生? ");
                link.l1 = TimeGreeting()+", "+GetAddress_FormToNPC(NPChar)+"。 我不会占用你太多时间, 只是想问... ";
                link.l1.go = "question";
                link.l2 = RandPhraseSimple("我需要关于你们殖民地的信息。 ", "我需要信息。 ");
                link.l2.go = "quests";//(转发到城市文件)
                npchar.quest.meeting = "1";
                
                //==> 圣慈悲号上的检查官来了
                if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
                {
                    dialog.Text = LinkRandPhrase(LinkRandPhrase("整个城市都人心惶惶 —皇家检查官费尔南多.德.阿拉米达来了。 你知道吗, 我在这里见过很多, 但这次... 改变人的不是悲伤, 而是他们应对悲伤的方式。 据说他父亲去世后他完全变了一个人。 现在在整个群岛上, 你找不到比他更廉洁... 和无情的王室仆人了。 ", "看看那艘'圣慈悲号'! 据说那是国王亲自下令按照特殊设计建造的。 注意看 —连一道划痕都没有。 好像圣母玛利亚亲自保护它一样。 不过我听说了一些传言... 也许保护它的不是圣母。 ", "你知道有多少次有人试图暗杀费尔南多先生吗? 公海上十二次袭击 —这还只是去年的统计! 嗯, 有这么忠诚和训练有素的船员, 再加上上帝的保护 —他也能挺过第十三次。 "), LinkRandPhrase("你听说了吗? 费尔南多.德.阿拉米达来到我们城市了, 据说他现在就在街上的某个地方。 真希望亲眼见见他... ", "一个复杂的人, 这个费尔南多先生。 有人说他是救世主, 在净化祖国的污垢。 另一些人则小声说, 他父亲去世后他的某些东西破碎了, 很快我们都会哭泣。 但我告诉你: 别害怕他。 害怕那些把他变成这样的人。 ", "费尔南多先生真是个英俊的男人! 但你知道什么奇怪的吗? 他好像谁都看不见。 全是职责和服务。 我听说曾经有个女孩... 但在和某个牧师会面后, 他完全拒绝了世俗的享乐。 好像他发了誓一样。 "), RandPhraseSimple(RandPhraseSimple("该死的检查官! 他在这里的时候 —整个城市就像死了一样。 没有贸易, 没有乐趣。 就连呼吸, 似乎也得小声点。 你知道最可怕的是什么吗? 每个港口都是这样。 像时钟一样准时。 国王陛下是不是故意发明了这种折磨来对付我们所有人! ", "费尔南多先生又去孤儿院了。 慷慨捐赠, 祈祷数小时。 这样一个值得尊敬的人应该被树立为那些被诅咒的贪污者的榜样! "), RandPhraseSimple("哈!'圣'费尔南多又关闭了所有妓院。 好吧, 没关系, 他很快就会起航离开, 它们马上又会重新开业。 ", "检查... 检查官来了, 就是这样! 费尔南多.德.阿尔梅达, 或者, 他叫什么来着, 阿拉米达! 太重要了, 连总督自己都对他小心翼翼。 据说他看着你的眼睛就能看到你所有的罪过。 太可怕了! ")));
                    link.l1 = "... ";
                    link.l1.go = "exit";
                    DeleteAttribute(link, "l2");
                }
                //<== 圣慈悲号上的检查官来了
                //==> 贝丝夫人在港口城市
                if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
                {
                    dialog.Text = findLedyBethRumour(npchar);
                    link.l1 = "... ";
                    link.l1.go = "exit";
                    DeleteAttribute(link, "l2");
                }
                //<== 贝丝夫人在港口城市
            }
            else //--> 再次对话
            {
                dialog.text = NPCStringReactionRepeat("什么? 又来了? 我没时间陪你。 找别人说话去吧。 街上有的是平民。 而我得走了, 今晚总督官邸有宴会, 我得准备我的服装... ", 
                    "不, 现在真的很烦人! 你就不明白吗? 还是说你脑子有问题? ", 
                    "先生, 我开始怀疑你不仅是个白痴, 还是个乡巴佬和粗人。 我警告你, 离我远点, 否则你会后悔打扰我的。 ",
                    "够了。 我要教训你, 无礼的家伙! ", "block", 1, npchar, Dialog.CurrentNode);
                link.l1 = HeroStringReactionRepeat("我明白了。 再见。 ", 
                    "是的-是的, 只是忘了我想问什么... ",
                    "你误解我了... ", 
                    "什么? ! ", npchar, Dialog.CurrentNode);
                link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
            }
            NextDiag.TempNode = "First time";
        break;

        case "question":
            dialog.text = LinkRandPhrase("继续说。 ","你想要什么? ","问题? 好吧, 水手, 我在听。 ");
            link.l1 = LinkRandPhrase("你能告诉我你们镇上最近的八卦吗? ","这里最近有什么有趣的事情发生吗? ","有什么关于加勒比海的消息吗, 先生? ");
            link.l1.go = "rumours_nobleman";
            NextDiag.TempNode = "First time";
        break;

//--------------------------------------------贵族乘客---------------------------------------------------
        case "passenger":
            if (hrand(19) > 9) SetPassengerParameter("Noblepassenger", false);
            else SetPassengerParameter("Noblepassenger", true);
            if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
            {
                dialog.text = ""+GetSexPhrase("先生","女士")+", 我需要尽快到达"+XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Acc")+"殖民地, 它在"+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+"上, 还有"+FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty))+"。 与这里大多数小船相比, 你的船看起来坚固而快速。 我可以付给你"+FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money))+"。 你怎么说? "; // belamour gen
            }
            else
            {
                dialog.text = "你好, "+GetSexPhrase("先生","女士")+"! 我需要去"+XI_ConvertString("Colony"+pchar.GenQuest.Noblepassenger.City+"Acc")+"! 顺便说一下, 它在"+XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Voc")+"上。 是的, 是的, 我知道 —那些混蛋正等着我们出现在那里。 但我在那里有一个非常紧急和重要的会议! 我不是一个吝啬的人 —虽然我不喜欢付钱, 但我总是会付钱。 放下你手头的一切, 我们一到那里, 我就会给你"+FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money))+"。 ";
            }
            link.l1 = "嗯。 我也正往那个方向走, 所以我愿意以这些条件载你上船。 ";
            link.l1.go = "passenger_1";
            link.l2 = "对不起, "+GetAddress_FormToNPC(NPChar)+", 但我要驶向另一个方向。 我帮不了你。 ";
            link.l2.go = "passenger_exit";
        break;
        
        case "passenger_exit":
            dialog.text = "太遗憾了。 好吧, 我会等另一艘船。 再见。 ";
            link.l1 = "再见。 ";
            link.l1.go = "exit";
            DeleteAttribute(pchar, "GenQuest.Noblepassenger");
        break;
        
        case "passenger_1":
            dialog.text = "太好了! 我等不及了。 我们到那里后你会拿到报酬的。 ";
            link.l1 = "去我的船上吧, "+GetAddress_FormToNPC(NPChar)+"。 我们很快就出发。 ";
            link.l1.go = "passenger_2";
        break;
        
        case "passenger_2":
            DialogExit();
            pchar.GenQuest.Noblepassenger.id = npchar.id;
            LAi_SetImmortal(npchar, true);
            DeleteAttribute(npchar, "LifeDay");
            LAi_RemoveLoginTime(npchar);
            DeleteAttribute(npchar, "CityType");//移除幽灵标记, 否则会出现空城市
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
            AddPassenger(pchar, npchar, false);
            SetCharacterRemovable(npchar, false);
            sTitle = npchar.index+"Citizpassenger";

// LDH 13Sep17 - 不要添加到现有的Citizpassenger记录 -->
// "重命名"任务记录, 方法是将其复制到新名称并删除旧记录
            if (CheckAttribute(pchar, "questinfo."+sTitle))
            {
                string sTempLDH = frand(1);
                sTempLDH = strcut(sTempLDH, 2, 5);    // 4位随机数
                string sTitle1 = sTitle+sTempLDH;

                aref arTo, arFrom;
                makearef(arFrom, pchar.questinfo.(sTitle));
                makearef(arTo,   pchar.questinfo.(sTitle1));
                CopyAttributes(arTo, arFrom);
                pchar.questinfo.(sTitle1) = "";

                DeleteAttribute(pchar, "questinfo."+sTitle);

                Trace("重复的Citizpassenger记录"+sTitle+"已复制到"+sTitle1+" **");
            }
// <--

            AddQuestRecordEx(sTitle, "Citizpassenger", "1");
            AddQuestUserDataForTitle(sTitle, "sType", "贵族成员");
            AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
            sTemp = XI_ConvertString("Colony" +pchar.GenQuest.Noblepassenger.City+"Gen") + ", 在" + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City)+"Dat")+".";
            AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
            AddQuestUserData(sTitle, "sName", GetFullName(npchar));
            AddQuestUserData(sTitle, "sCity", sTemp);
            AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty)));
            AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
            if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity")) AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money)));
            else AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money)));
            AddQuestUserData(sTitle, "sName", GetFullName(npchar));
            pchar.quest.Noblepassenger.win_condition.l1 = "location";
            pchar.quest.Noblepassenger.win_condition.l1.location = pchar.GenQuest.Noblepassenger.City+"_town";
            pchar.quest.Noblepassenger.function = "Noblepassenger_complete";
            SetFunctionTimerCondition("Noblepassenger_Over", 0, 0, sti(pchar.GenQuest.Noblepassenger.DaysQty), false);
        break;
        
        case "passenger_3":
            pchar.quest.Noblepassenger_Over.over = "yes"; //移除计时器
            dialog.text = "我们到了, 非常出色! 在你的船上旅行相当令人满意。 你的船员纪律严明, 甲板干净! 谢谢你。 拿着你的钱, 先生。 ";
            link.l1 = "祝你好运, "+GetAddress_FormToNPC(NPChar)+"! 再见! ";
            link.l1.go = "passenger_4";
        break;
        
        case "passenger_4":
            chrDisableReloadToLocation = false;//打开位置
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
            if (CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
            {
                AddCharacterExpToSkill(pchar, "Sneak", 50);
                TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Noblepassenger.Money));
            }
            else AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Noblepassenger.Money));
            sTitle = npchar.index+"Citizpassenger";
            AddQuestRecordEx(sTitle, "Citizpassenger", "3");
            CloseQuestHeader(sTitle);
            DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
        break;
//< —贵族乘客

//-------------------------------------------------金钱援助------------------------------------------------
        case "donation":
            sTemp = DonationText();
            dialog.text = "我有一件相当微妙的事情... "+sTemp+" 我现在需要钱, 否则我就麻烦大了。 我通常绝不会向另一位绅士借钱, 但情况真的很糟糕。 ";
            link.l1 = "你需要多少? ";
            link.l1.go = "donation_1";
        break;
        
        case "donation_1":
            iTemp = hrand(4)+1;
            pchar.GenQuest.Nobledonation.Money = iTemp*1000+rand(iTemp)*150;
            dialog.text = "金额相当小, 是"+FindRussianMoneyString(sti(pchar.GenQuest.Nobledonation.Money))+"。 那么, 你能帮我吗? ";
            if (sti(pchar.money) >= sti(pchar.GenQuest.Nobledonation.Money))
            {
                link.l1 = "是的, 当然。 拿去吧。 ";
                link.l1.go = "donation_2";
            }
            link.l2 = "我很想帮忙, 但我的口袋也空了 —连一个多余的比索都没有。 ";
            link.l2.go = "donation_exit";
        break;
        
        case "donation_exit":
            DialogExit();
            ChangeOfficersLoyality("bad_all", 1);
            LAi_CharacterDisableDialog(npchar);
            npchar.lifeday = 0;
            DeleteAttribute(pchar, "GenQuest.Nobledonation");
        break;
        
        case "donation_2":
            AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Nobledonation.Money));
            dialog.text = "非常感谢, "+GetAddress_Form(NPChar)+"! 你救了我! 我在总督官邸有朋友, 我会告诉他们你的慷慨。 再次万分感谢! ";
            link.l1 = "不客气, 先生。 我相信如果你处在我的位置也会这么做的。 ";
            link.l1.go = "donation_3";
        break;
        
        case "donation_3":
            DialogExit();
            ChangeOfficersLoyality("good_all", rand(2)+1);
            ChangeCharacterNationReputation(pchar, sti(npchar.Nation), rand(1)+2);
            LAi_CharacterDisableDialog(npchar);
            npchar.lifeday = 0;
            DeleteAttribute(pchar, "GenQuest.Nobledonation");
        break;
//< —金钱援助

//-------------------------------------------------家族遗物---------------------------------------------
        case "lombard":
            LombardText();
            dialog.text = "我需要你的帮助。 你很富有, 是一位绅士, 所以我希望你能理解。 不久前我急需用钱, 所以不得不去找银行家, 典当"+pchar.GenQuest.Noblelombard.Item+"\n他提出了不错的条件。 每月百分之十的利息, 总共三个月。 但时间到了, 由于不幸的变故, 我没有钱赎回这件物品\n现在他说他已经找到了"+pchar.GenQuest.Noblelombard.Item+"的买家, 如果我不立即偿还债务和利息, 他就会把它卖掉。 但我现在没有多少钱, 而我典当的物品非常昂贵... ";
            link.l1 = "我怎么帮你呢, "+GetAddress_FormToNPC(NPChar)+"?";
            link.l1.go = "lombard_1";
        break;
        
        case "lombard_1":
            dialog.text = "我请求你和我们的银行家谈谈。 给他钱, 为我担保... 或者做些别的。 不幸的是, 我没有人可以求助, 我所有的好朋友突然都'破产'了。 三个月后"+pchar.GenQuest.Noblelombard.Text+", 我会加倍偿还你所有的费用! 我以绅士的名义向你保证! ";
            link.l1 = "好吧, 我会试着在这件事上帮助你。 ";
            link.l1.go = "lombard_2";
            link.l2 = "不幸的是, 我现在也是个'破产者'。 所以我帮不了你, 非常抱歉! ";
            link.l2.go = "lombard_exit";
        break;
        
        case "lombard_exit":
            DialogExit();
            LAi_CharacterDisableDialog(npchar);
            npchar.lifeday = 0;
            DeleteAttribute(pchar, "GenQuest.Noblelombard");
        break;
        
        case "lombard_2":
            dialog.text = "感谢你的理解。 我会在酒馆等你。 尽快到那里去。 ";
            link.l1 = "... ";
            link.l1.go = "lombard_3";
        break;
        
        case "lombard_3":
            DialogExit();
            pchar.GenQuest.Noblelombard = "true";
            pchar.GenQuest.Noblelombard.Name = GetFullName(npchar);
            pchar.GenQuest.Noblelombard.id = npchar.id;
            pchar.GenQuest.Noblelombard.City = npchar.city;
            pchar.GenQuest.Noblelombard.Money = 20000+hrand(60)*500;
            pchar.GenQuest.Noblelombard.Percent = makeint(sti(pchar.GenQuest.Noblelombard.Money)*0.3);
            pchar.GenQuest.Noblelombard.Summ = sti(pchar.GenQuest.Noblelombard.Money)+sti(pchar.GenQuest.Noblelombard.Percent);
            pchar.GenQuest.Noblelombard.Chance = hrand(9);
            chrDisableReloadToLocation = true;//关闭位置
            LAi_SetActorType(npchar);
            LAi_RemoveLoginTime(npchar);
            DeleteAttribute(npchar, "CityType");//移除幽灵标记
            FreeSitLocator(pchar.GenQuest.Noblelombard.City + "_tavern", "sit1");
            LAi_ActorRunToLocation(npchar, "reload", "reload4_back", pchar.GenQuest.Noblelombard.City+"_tavern", "sit", "sit1", "Nobleman_lombardTavern", 10);
            SetFunctionTimerCondition("Noblelombard_Over", 0, 0, 1, false); //到当天结束的计时器
            ReOpenQuestHeader("Noblelombard");
            AddQuestRecord("Noblelombard", "1");
            AddQuestUserData("Noblelombard", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Noblelombard.City));
            AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
        break;
        
        case "lombard_4":
            if (CheckAttribute(pchar, "GenQuest.Noblelombard.Regard"))
            {
                pchar.quest.Noblelombard_Over.over = "yes"; //移除计时器
                dialog.text = "你怎么说, "+GetAddress_Form(NPChar)+"? 你去过银行了吗? 有好消息还是坏消息? ";
                if (pchar.GenQuest.Noblelombard == "full") link.l1 = "去过了。 我已经还清了你所有的债务。 你可以去那里拿回你的遗物了。 ";
                if (pchar.GenQuest.Noblelombard == "maxpercent") link.l1 = "去过了。 我已经还清了过去三个月的所有利息, 甚至还预付了接下来三个月的。 你可以放心地等你的钱。 只是别忘了在三个月内还清你的主要债务。 ";
                if (pchar.GenQuest.Noblelombard == "minpercent") link.l1 = "去过了。 我已经还清了过去三个月的所有利息。 银行家同意再等三个月, 直到你凑齐全款。 ";
                link.l1.go = "lombard_5";
                break;
            }
            if (pchar.GenQuest.Noblelombard == "fail")
            {
                dialog.text = "你怎么说, "+GetAddress_Form(NPChar)+"? 你去过银行了吗? 有好消息还是坏消息? ";
                link.l1 = "去过了。 那个吝啬鬼要了一笔不可思议的钱。 他拒绝了任何让步的请求, 而我没有所需的钱数。 所以我帮不了你。 对不起。 ";
                link.l1.go = "lombard_fail";
            }
            else
            {
                dialog.text = "你怎么说, "+GetAddress_Form(NPChar)+"? 你去过银行了吗? 有好消息还是坏消息? ";
                link.l1 = "我正在处理。 等一下。 ";
                link.l1.go = "exit";
                NextDiag.TempNode = "lombard_4";
            }
        break;
        
        case "lombard_fail":
            pchar.quest.Noblelombard_Over.over = "yes"; //移除计时器
            dialog.text = "唉, "+GetAddress_Form(NPChar)+"... 现在你也是这些该死的贪婪放债人的见证者了。 以上帝的名义, 先生, 他们比犹太人还可耻! 当你像我一样试图向他们借钱时, 记住这一点。 至少感谢你的尝试... ";
            link.l1 = "我从来就不喜欢他们。 嗯, 谁会喜欢放债人呢? 对不起, "+GetAddress_FormToNPC(NPChar)+"。 再见。 ";
            link.l1.go = "lombard_fail_1";
        break;
        
        case "lombard_fail_1":
            DialogExit();
            LAi_CharacterDisableDialog(npchar);
            npchar.lifeday = 0;
            AddQuestRecord("Noblelombard", "4");
            AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
            CloseQuestHeader("Noblelombard");
            sld = characterFromId(pchar.GenQuest.Noblelombard.City+"_usurer");
            DeleteAttribute(sld, "quest.noblelombard");
            DeleteAttribute(Pchar, "GenQuest.Noblelombard");
        break;
        
        case "lombard_5":
            dialog.text = "难以置信! 你刚刚救了我, "+GetAddress_Form(NPChar)+"! 我永远不会忘记。 我向你保证, 你所有的费用都会加倍偿还。 三个月后去找我们的银行家。 我会以你的名义开一个存款账户。 ";
            link.l1 = "好吧, 我会照你说的做。 再见! ";
            link.l1.go = "lombard_6";
        break;
        
        case "lombard_6":
            dialog.text = "再次感谢, 船长。 祝你好运! ";
            link.l1 = "... ";
            link.l1.go = "lombard_7";
        break;
        
        case "lombard_7":
            DialogExit();
            LAi_CharacterDisableDialog(npchar);
            npchar.lifeday = 0;
            ChangeCharacterComplexReputation(pchar, "authority", 2);
            ChangeOfficersLoyality("good_all", 1);
            AddQuestRecord("Noblelombard", "5");
            AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
            SetFunctionTimerCondition("Noblelombard_Regard", 0, 0, 90, false); //计时器
        break;
//< —家族遗物

//------------------------------------------运送奴隶--------------------------------------------
        case "slaves":
            npchar.quest.slaves.price = 3+hrand(1);//奴隶价格 (杜布隆) 
            npchar.quest.slaves.qty = 50+hrand(5)*10;//数量
            npchar.quest.slaves.money = sti(npchar.quest.slaves.qty)*sti(npchar.quest.slaves.price);
            dialog.text = "我拥有一家"+LinkRandPhrase("工厂","矿山","种植园")+", 总是需要新鲜的奴隶。 这里的气候真的很折磨他们。 现在我需要"+sti(npchar.quest.slaves.qty)+"个。 我愿意订购一批。 我会为每个奴隶支付金币, "+sti(npchar.quest.slaves.price)+"杜布隆\n不着急, 如果你能弄到我需要的东西, 我不会给你限定时间。 当然, 也要合理, 别拖半年以上。 那么你怎么说? 成交吗? ";
            link.l1 = "成交! 奴隶贸易是肮脏的生意, 但值得冒险。 ";
            link.l1.go = "slaves_1";
            link.l2 = "对不起, 但我不是奴隶贩子。 这不是我的行当。 ";
            link.l2.go = "exit_slaves";
        break;
        
        case "exit_slaves":
            DialogExit();
            LAi_CharacterDisableDialog(npchar);
            npchar.lifeday = 0;
        break;
        
        case "slaves_1":
            dialog.text = "很好。 等你把货物带来时我会等你的。 你每天上午11点到下午1点可以在教堂找到我。 剩下的时间我很忙, 或者在工作。 ";
            link.l1 = "好的。 我会记住的。 再见, "+GetAddress_FormToNPC(NPChar)+"。 ";
            link.l1.go = "slaves_2";
        break;
        
        case "slaves_2":
            DialogExit();
            sGlobalTemp = npchar.id;
            DeleteAttribute(npchar, "LifeDay");
            DeleteAttribute(npchar, "CityType");//移除幽灵标记, 否则会出现空城市
            SaveCurrentNpcQuestDateParam(npchar, "slaves_date");//记录日期
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload4_back", npchar.city+"_church", "sit", "sit"+(1+rand(5)), "Nobleslaves_Place", 10.0);
            chrDisableReloadToLocation = true;//关闭位置
            Colonies[FindColony(npchar.city)].questslaves = true;
            sTitle = npchar.city+"Nobleslaves";
            ReOpenQuestHeader(sTitle);
            AddQuestRecordEx(sTitle, "Nobleslaves", "1");
            AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData(sTitle, "sName", GetFullName(npchar));
            AddQuestUserData(sTitle, "sQty", sti(npchar.quest.slaves.qty));
            AddQuestUserData(sTitle, "sMoney", sti(npchar.quest.slaves.money));
        break;
        
        case "slaves_3":
            if (GetNpcQuestPastDayParam(npchar, "slaves_date") < 180)
            {
                dialog.text = "你带来了我要的"+sti(npchar.quest.slaves.qty)+"个奴隶了吗, 船长? ";
                if (GetSquadronGoods(pchar, GOOD_SLAVES) >= sti(npchar.quest.slaves.qty))
                {
                    link.l1 = "带来了。 整批货物都在我的货舱里。 我准备好把它们交给你了。 ";
                    link.l1.go = "slaves_4";
                }
                else
                {
                    link.l1 = "没有, 我正在处理。 ";
                    link.l1.go = "exit";
                    NextDiag.TempNode = "slaves_3";
                }
            }
            else
            {
                dialog.text = "船长, 如果你是为那些奴隶而来... 我已经买够了, 现在不需要更多了。 你花的时间太长了, 对不起。 ";
                link.l1 = "太遗憾了! 但你是对的, 我不够快。 再见! ";
                link.l1.go = "slaves_8";
            }
        break;
        
        case "slaves_4":
            dialog.text = "太好了。 我马上派一艘小艇去取。 ";
            link.l1 = "我的报酬呢? ";
            link.l1.go = "slaves_5";
        break;
        
        case "slaves_5":
            dialog.text = "别担心, 我记得。 给你, 收下这笔钱, 每个奴隶"+sti(npchar.quest.slaves.price)+"杜布隆。 对我们双方来说都是一笔好交易, 不是吗? ";
            link.l1 = "谢谢。 很高兴和你做生意。 ";
            link.l1.go = "slaves_6";
        break;
        
        case "slaves_6":
            RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(npchar.quest.slaves.qty));
            TakeNItems(pchar, "gold_dublon", sti(npchar.quest.slaves.money));
            Log_Info("你收到了"+FindRussianDublonString(sti(npchar.quest.slaves.money))+"");
            PlaySound("interface\important_item.wav");
            dialog.text = "我得说... 对不起, 我得走了。 再见! ";
            link.l1 = "祝你好运, "+GetAddress_FormToNPC(NPChar)+"。 ";
            link.l1.go = "slaves_7";
        break;
        
        case "slaves_7":
            DialogExit();
            npchar.lifeday = 0;
            DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
            LAi_SetActorType(npchar);
            GetCharacterPos(pchar, &locx, &locy, &locz);
            ChangeCharacterAddressGroup(npchar, npchar.city+"_church", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
            LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
            AddCharacterExpToSkill(pchar, "Commerce", 150);//贸易
            AddCharacterExpToSkill(pchar, "Sailing", 50);//航海
            AddCharacterExpToSkill(pchar, "Fortune", 30);//幸运
            ChangeCharacterComplexReputation(pchar, "nobility", -1);
            sTitle = npchar.city+"Nobleslaves";
            AddQuestRecordEx(sTitle, "Nobleslaves", "2");
            CloseQuestHeader(sTitle);
        break;

        case "slaves_8":
            DialogExit();
            npchar.lifeday = 0;
            LAi_CharacterDisableDialog(npchar);
            DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
            sTitle = npchar.city+"Nobleslaves";
            AddQuestRecordEx(sTitle, "Nobleslaves", "3");
            CloseQuestHeader(sTitle);
        break;
//< —运送奴隶

        //公民角色对露出武器的评论
        case "CitizenNotBlade":
            dialog.text = NPCharSexPhrase(NPChar, "听着, 作为这个城镇的公民, 我请求你把剑收起来。 ", "听着, 作为这个城镇的公民, 我请求你把剑收起来。 ");
            link.l1 = LinkRandPhrase("好的。 ", "如你所愿。 ", "好的。 ");
            link.l1.go = "exit";
        break;

        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;

        case "fight":
            DialogExit();
            NextDiag.CurrentNode = NextDiag.TempNode;
            LAi_SetHP(NPChar, 400, 400);
            TakeNItems(NPChar, "potion2", 3);
            SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
            LAi_group_MoveCharacter(NPChar, "TempFight");
            LAi_group_Attack(NPChar, Pchar);
            AddDialogExitQuest("MainHeroFightModeOn");
            ChangeCharacterNationReputation(pchar, sti(npchar.nation), -3);
        break;
    }
}

string DonationText()
{
    string sText;
    switch (hrand(5))
    {
        case 0: sText = "我昨天在赌博中输光了所有的钱, 现在没有足够的钱来还债。 你能帮我吗? "; break;
        case 1: sText = "昨天我和一个... 特定的风尘女子度过了一段美好时光, 现在她试图勒索我。 我需要先付钱给她, 然后再对付她... 你能借我点钱吗? "; break;
        case 2: sText = "最近我用我的细剑刺穿了一个当地的傻瓜, 现在指挥官要求贿赂来掩盖这件事。 我现在缺钱。 你能帮我吗? "; break;
        case 3: sText = "我不幸输了一场赌局, 现在没有一笔小钱来偿还荣誉债务。 你能帮我吗? "; break;
        case 4: sText = "某个混蛋知道我... 与一个已婚女人的不检点行为。 我没有足够的钱堵住他的嘴。 只需要几枚金币... "; break;
        case 5: sText = "某个混蛋从我的房子里偷走了重要文件, 并索要一大笔钱才肯归还。 我几乎凑够了, 只需要再多几枚硬币。 你能帮我吗? "; break;
    }
    return sText;
}

void LombardText()
{
    switch (hrand(5))
    {
        case 0:
            pchar.GenQuest.Noblelombard.Item = "我母亲的钻石吊坠, 由马德里的一位珠宝商制作";
            pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("我将得到我的遗产","我的船将从非洲满载奴隶归来");
        break;
        case 1: pchar.GenQuest.Noblelombard.Item = "我姐姐的翡翠项链, 由巴黎的一位珠宝商制作";
                pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("我将继承欧洲的一个郡","我的船将从印度满载香料和丝绸归来");
        break;
        case 2:
            pchar.GenQuest.Noblelombard.Item = "带有我们家族徽章的家族戒指";
            pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("我的探险队将从西班牙大陆带回金锭","我将得到我的遗产");
        break;
        case 3:
            pchar.GenQuest.Noblelombard.Item = "我妻子的红宝石手镯, 她母亲送的礼物";
            pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("我将从欧洲银行收回我的投资和利息","我将从我的种植园获得利润");
        break;
        case 4:
            pchar.GenQuest.Noblelombard.Item = "一条由黄金和钻石制成的项链, 手工制作, 我妻子的骄傲";
            pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("我将从目前的生意中获利","我的船将从非洲归来, 货舱里塞满了黑色象牙");
        break;
        case 5:
            pchar.GenQuest.Noblelombard.Item = "一根由半宝石制成的象牙手杖, 我祖父送的礼物";
            pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("我的船将从印度归来, 货舱里装满了丝绸和香料","我将从欧洲银行收到我的利息");
        break;
    }
}