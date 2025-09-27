// 杰森贵族小姐通用对话
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag;

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
    
    switch(Dialog.CurrentNode)
    {
        case "First time":
            //首次见面
            if(NPChar.quest.meeting == "0")
            {
                if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//检查国家间关系
                {
                    dialog.text = "嗯。 你挂着" + NationNameGenitive(sti(pchar.nation)) + "的旗帜航行, 船长。 我不想和我国的敌人说话。 哼! ";
                    link.l1 = "啊, 对。 真是个爱国者... ";
                    link.l1.go = "exit";
                }
                else
                {
                    dialog.text = RandPhraseSimple("你想从我这里得到什么, " + GetAddress_Form(NPChar) + "? 普通水手和贵族小姐交谈不太合适, 但我在听你说。 ", "哦, 这么勇敢的船长想从我这里得到什么呢? ");
                    link.l1 = TimeGreeting() + ", " + GetAddress_FormToNPC(NPChar) + "。 我不会占用你太多时间, 只是想问... ";
                    link.l1.go = "question";
                    link.l2 = RandPhraseSimple("我需要知道你们殖民地发生了什么。 ", "我需要一些信息。 ");
                    link.l2.go = "quests";//(转发到城市文件)
                }
                npchar.quest.meeting = "1";
                
                //==> 圣慈悲号上的检查官来了
                if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
                {
                    dialog.Text = LinkRandPhrase(LinkRandPhrase("整个城市都人心惶惶 —皇家检查官费尔南多.德.阿拉米达来了。 你知道吗, 我在这里见过很多, 但这次... 改变人的不是悲伤, 而是他们应对悲伤的方式。 据说他父亲去世后他完全变了一个人。 现在在整个群岛上, 你找不到比他更廉洁... 和无情的王室仆人了。 ", "看看那艘‘圣慈悲号’! 据说那是国王亲自下令按照特殊设计建造的。 注意看 —连一道划痕都没有。 好像圣母玛利亚亲自保护它一样。 不过我听说了一些传言... 也许保护它的不是圣母。 ", "你知道有多少次有人试图暗杀费尔南多先生吗? 公海上十二次袭击 —这还只是去年的统计! 嗯, 有这么忠诚和训练有素的船员, 再加上上帝的保护 —他也能挺过第十三次。 "), LinkRandPhrase("你听说了吗? 费尔南多.德.阿拉米达来到我们城市了, 据说他现在就在街上的某个地方。 真希望亲眼见见他... ", "一个复杂的人, 这个费尔南多先生。 有人说他是救世主, 在净化祖国的污垢。 另一些人则小声说, 他父亲去世后他的某些东西破碎了, 很快我们都会哭泣。 但我告诉你: 别害怕他。 害怕那些把他变成这样的人。 ", "费尔南多先生真是个英俊的男人! 但你知道什么奇怪的吗? 他好像谁都看不见。 全是职责和服务。 我听说曾经有个女孩... 但在和某个牧师会面后, 他完全拒绝了世俗的享乐。 好像他发了誓一样。 "), RandPhraseSimple(RandPhraseSimple("该死的检查官! 他在这里的时候 —整个城市就像死了一样。 没有贸易, 没有乐趣。 就连呼吸, 似乎也得小声点。 你知道最可怕的是什么吗? 每个港口都是这样。 像时钟一样准时。 国王陛下是不是故意发明了这种折磨来对付我们所有人! ", "费尔南多先生又去孤儿院了。 慷慨捐赠, 祈祷数小时。 这样一个值得尊敬的人应该被树立为那些被诅咒的贪污者的榜样! "), RandPhraseSimple("哈! ‘圣’费尔南多又关闭了所有妓院。 好吧, 没关系, 他很快就会起航离开, 它们马上又会重新开业。 ", "检查... 检查官来了, 就是这样! 费尔南多.德.阿尔梅达, 或者, 他叫什么来着, 阿拉米达! 太重要了, 连总督自己都对他小心翼翼。 据说他看着你的眼睛就能看到你所有的罪过。 太可怕了! ")));
                    link.l1 = "... ";
                    link.l1.go = "exit";
                    DeleteAttribute(link, "l2");
                }
                //<== 圣慈悲号上的检查官来了
                //==> 贝丝女士在港口城市
                if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
                {
                    dialog.Text = findLedyBethRumour(npchar);
                    link.l1 = "... ";
                    link.l1.go = "exit";
                    DeleteAttribute(link, "l2");
                }
                //<== 贝丝女士在港口城市
            }
            else
            {
                //再次对话
                if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
                {
                    dialog.text = "要我重复一遍吗? 我不想被怀疑是" + NationNameAblative(sti(pchar.nation)) + "的朋友! 离开, 否则我就叫卫兵了! 他们会很高兴和你谈谈。 ";
                    link.l1 = "好, 好, 冷静点。 我这就走。 ";
                    link.l1.go = "exit";
                }
                else
                {
                    dialog.text = NPCStringReactionRepeat("什么? 又是你? 去找别人说话吧。 街上有很多平民, 他们更适合你。 我现在得走了, 今晚总督官邸有宴会, 我的蓬帕杜发型还没弄好呢! ", 
                        "不, 你现在真的很烦人! 你不明白吗? 还是你脑子不好使? ", 
                        "先生, 我开始怀疑你不仅是个白痴, 还是个无赖和粗人。 我警告你, 如果你再用你愚蠢的问题打扰我, 我就叫我丈夫了! ",
                        "再多说一个字, 我就告诉指挥官来对付你! ", "block", 1, npchar, Dialog.CurrentNode);
                    link.l1 = HeroStringReactionRepeat("我明白了。 再见。 ", 
                        "是是, 我记得, 只是忘了问... ",
                        "你误会我了... ", 
                        "冷静点, 女士, 我这就走... ", npchar, Dialog.CurrentNode);
                    link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
                }
            }
            NextDiag.TempNode = "First time";
        break;

        // 在此插入任何任务检查和引导
        case "question":
            dialog.text = LinkRandPhrase("好吧, 说来听听。 ", "哦, 好吧。 你想要什么? ", "问题? 好吧, 水手, 我在听。 ");
            link.l1 = LinkRandPhrase("你能告诉我这个镇上最新的八卦吗? ", "这里最近发生了什么有趣的事吗? ", "有什么来自加勒比海的消息吗, 女士? ");
            link.l1.go = "rumours_noblegirl";
            NextDiag.TempNode = "First time";
        break;

        // 公民角色对露出武器的评论
        case "CitizenNotBlade":
            dialog.text = NPCharSexPhrase(NPChar, "你疯了吗? ! 你吓到我了! 收起你的武器, 否则我就告诉指挥官把你吊死在堡垒里! ", "你疯了吗? ! 你吓到我了! 收起你的武器, 否则我就告诉指挥官把你吊死在堡垒里! ");
            link.l1 = LinkRandPhrase("好的。 ", "如你所愿。 ", "好。 ");
            link.l1.go = "exit";
        break;

        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
    }
}