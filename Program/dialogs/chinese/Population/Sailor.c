// 杰森街头水手通用对话
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
    ref NPChar;
    aref Link, NextDiag;
    string sTemp;
    int iTemp;

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
            if (npchar.quest.meeting == "0")
            {
                if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.crew"))//招募船员
                {
                    dialog.text = "日安, "+GetAddress_Form(NPChar)+"。 我知道你是自己船只的船长。 我有个交易想和你谈。 ";
                    link.l1 = "我在听, "+GetAddress_FormToNPC(NPChar)+"。 什么样的交易? ";
                    link.l1.go = "crew";
                    link.l2 = "抱歉, "+GetAddress_FormToNPC(NPChar)+", 但我赶时间。 ";
                    link.l2.go = "exit";
                    npchar.quest.meeting = "1";
                    DeleteAttribute(npchar, "talker"); //移除对话标记
                    break;
                }
                dialog.text = LinkRandPhrase("嘿, 船长! 你想从一个普通水手这里得到什么? ","日安, 先生。 我能为你做什么? ","日安, 先生。 你需要什么吗? ");
                link.l1 = "很高兴见到你, 伙计! 我叫"+GetFullName(pchar)+"。 有时间聊聊吗? ";
                link.l1.go = "question";
                link.l2 = RandPhraseSimple("我有个问题要问你。 ", "我需要一些关于这个殖民地的信息。 ");
                link.l2.go = "quests";//(转发到城市文件)
                link.l3 = "只是想打个招呼。 再见! ";
                link.l3.go = "exit";
                npchar.quest.meeting = "1";
            }
            else
            {
                dialog.text = "又是你, 先生? 你还想干什么? ";
                link.l1 = "有时间聊聊吗? ";
                link.l1.go = "question";
                link.l2 = RandPhraseSimple("我有个问题要问你。 ", "我需要一些关于这个殖民地的信息。 ");
                link.l2.go = "quests";//(转发到城市文件)
                link.l3 = "不, 伙计, 没什么事。 祝你好运! ";
                link.l3.go = "exit";
            }
            NextDiag.TempNode = "First time";
        break;

        case "question":
            dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+"为您效劳, 好先生! 你想知道什么? ", 
                "很高兴和你聊天, 船长! ", 
                "嗯... 我想我还有点时间可以聊聊... ",
                "不幸的是, 我现在得走了。 再见! ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("有什么有趣的事要告诉我吗? ", 
                "有什么有趣的事要告诉我吗? ",
                "有什么有趣的事要告诉我吗? ", 
                "当然。 祝你好运! ", npchar, Dialog.CurrentNode);
            link.l1.go = DialogGoNodeRepeat("rumours_sailor", "rumours_sailor", "rumours_sailor", "exit", npchar, Dialog.CurrentNode);
        break;

        case "crew":
            switch (hrand(2))
            {
                case 0: sTemp = "我和我的伙伴们因为各种疾病和受伤, 从上一艘船被遣散到岸上。 但我们现在都健康了, 想再次作为水手回去工作。 你想雇佣我们吗? "; break;
                case 1: sTemp = "我和我的几个兄弟因为商船合同到期而被解雇。 我们已经很久没有一分钱了, 所以想重新回去工作。 你需要为你的船员招募一些熟练的水手吗? "; break;
                case 2: sTemp = "我和我的伙伴们两周前刚从一次航行中回来。 船长解雇了我们, 我们玩得很开心。 但现在我们的口袋空了, 所以是时候再次起航了。 你想雇佣我们吗, 船长? "; break;
            }
            dialog.text = sTemp;
            link.l1 = "好吧, 我准备讨论你的提议。 你们有多少人, 擅长什么? ";
            link.l1.go = "crew_1";
            link.l2 = "抱歉, 水手, 但我已经有足够的人手了。 你应该去找另一个船长。 ";
            link.l2.go = "exit";
        break;
        
        case "crew_1":
            switch (sti(npchar.quest.crew.type))
            {
                case 0: sTemp = "我们最擅长操作帆和索具。 毫不谦虚地说, 我们是船舶操控方面的专业人士, 所以别担心, 即使在最强的风暴中, 我们也不会让你失望。 "; break;
                case 1: sTemp = "我们最喜欢在加农炮甲板上。 我们中有些人甚至在真正的战船上服役过。 我们装炮和开炮的方式是你船上的人比不了的。 在任何艰苦的战斗中, 你都可以依靠我们! "; break;
                case 2: sTemp = "我们是真正的优秀登船队员, 船长, 在此之前曾在私掠船上干过几次。 我们知道弯刀的闪光和火药与血的气味。 这是我们的使命。 在肉搏战中击败我们可不容易, 所以你总是可以依靠我们的刀刃, 船长! "; break;
            }
            dialog.text = "我们有"+sti(npchar.quest.crew.qty)+"个人, 我们只会一起被雇佣。 我们可以完成所有基本的水手任务。 "+sTemp+"";
            if (GetFreeCrewQuantity(pchar) >= sti(npchar.quest.crew.qty))
            {
                link.l1 = "听起来像是我要找的人。 你们的预付金呢? ";
                link.l1.go = "crew_2";
                link.l2 = "抱歉, 水手, 但我目前需要其他技能。 你应该去找另一个船长。 ";
                link.l2.go = "exit";
            }
            else
            {
                link.l1 = "抱歉, 水手, 但我的船上没有足够的空间。 你应该去找另一个船长。 ";
                link.l1.go = "exit";
            }
        break;
        
        case "crew_2":
            iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
            dialog.text = ""+FindRussianMoneyString(sti(npchar.quest.crew.money))+"每人。 然后是每月普通水手的工资。 我们不会要求过多, 船长。 ";
            if (sti(pchar.money) >= iTemp)
            {
                link.l1 = "你们被雇佣了! 拿上你们的硬币。 现在去我的船那里, 它叫‘"+pchar.ship.name+"’, 就在港口。 水手长会在船员宿舍给你们分配吊床, 并安排你们的伙食。 ";
                link.l1.go = "crew_3";
            }
            link.l2 = "不幸的是, 我付不起你们所有人的工资。 你应该去找另一个船长。 ";
            link.l2.go = "exit";
        break;
        
        case "crew_3":
            iTemp = sti(npchar.quest.crew.money)*sti(npchar.quest.crew.qty);
            AddMoneyToCharacter(pchar, -iTemp);
            dialog.text = "是, 是, 船长! 我会召集伙计们, 我们马上出发。 ";
            link.l1 = "快点, 我们随时起航。 ";
            link.l1.go = "crew_4";
        break;
        
        case "crew_4":
            DialogExit();
            AddCharacterCrew(pchar, sti(npchar.quest.crew.qty));
            //增加经验
            iTemp = makeint(sti(npchar.quest.crew.qty)*50/sti(pchar.ship.crew.quantity));
            switch (sti(npchar.quest.crew.type))
            {
                case 0: ChangeCrewExp(pchar, "Sailors", iTemp); break;
                case 1: ChangeCrewExp(pchar, "Cannoners", iTemp); break;
                case 2: ChangeCrewExp(pchar, "Soldiers", iTemp); break;
            }
            //增加士气
            iTemp = makeint(sti(npchar.quest.crew.qty)/10)+1;
            AddCrewMorale(pchar, iTemp);
            LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
            npchar.lifeday = 0;
        break;

        //公民角色对露出武器的评论
        case "CitizenNotBlade":
            dialog.text = NPCharSexPhrase(NPChar, "嘿, 把你的剑收起来, 船长。 我们谁都不需要麻烦, 对吧? ", "嘿, 把你的剑收起来, 船长。 我们谁都不需要麻烦, 对吧? ");
            link.l1 = LinkRandPhrase("好的。 ", "如你所愿。 ", "如你所说。 ");
            link.l1.go = "exit";
        break;

        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
    }
}