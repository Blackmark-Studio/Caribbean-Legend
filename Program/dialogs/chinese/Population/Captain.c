// 杰森街头庆祝的船长通用对话
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
    ref NPChar, sld;
    aref Link, NextDiag;

    DeleteAttribute(&Dialog,"Links");

    makeref(NPChar,CharacterRef);
    makearef(Link, Dialog.Links);
    makearef(NextDiag, NPChar.Dialog);
    
    ProcessCommonDialogRumors(NPChar, Link, NextDiag);
    
    switch(Dialog.CurrentNode)
    {
        case "First time":
            //首次见面
            if (npchar.quest.meeting == "0")
            {
                if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)//检查国家间关系
                {
                    dialog.text = "停! 你挂着"+NationNameGenitive(sti(pchar.nation))+"的旗帜航行, 水手。 我不想和你说话, 也不想惹麻烦... 滚! ";
                    link.l1 = "你还自称船长... ";
                    link.l1.go = "exit";
                    break;
                }
                if (CheckAttribute(npchar, "quest.march") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && GetCompanionQuantity(pchar) < 5)//战斗生成任务 2015
                {
                    dialog.text = "哈! 你来得正是时候, 船长... 我有个生意要和你谈。 你能抽出几个小时吗? ";
                    link.l1 = "不能。 我赶时间, 伙计。 也许下次吧。 ";
                    link.l1.go = "exit_quest";
                    link.l2 = "行, 也许可以。 要看你给我什么。 我们去酒馆聊聊怎么样? ";
                    link.l2.go = "march";
                    break;
                }
                dialog.text = "幸会幸会! 见到一位成功的同行真是太好了! ";
                link.l1 = "很高兴见到你, 先生! 我叫"+GetFullName(pchar)+"。 你有时间聊几句吗? ";
                link.l1.go = "question";
                npchar.quest.meeting = "1";
            }
            else
            {
                //再次对话
                if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
                {
                    dialog.text = "要我重复一遍吗? 我不想被怀疑是"+NationNameAblative(sti(pchar.nation))+"的朋友! 快滚, 否则我就叫卫兵了! ";
                    link.l1 = "好吧, 好吧, 冷静点。 我这就走。 ";
                    link.l1.go = "exit";
                }
                else
                {
                    dialog.text = "你想要什么? ";
                    link.l1 = "没什么。 ";
                    link.l1.go = "exit";
                }
            }
            NextDiag.TempNode = "First time";
        break;

        case "question":
            dialog.text = NPCStringReactionRepeat(""+GetFullName(npchar)+"为您效劳, 好先生! 你想知道什么? ", 
                "很高兴和你聊天, 船长! ", 
                "嗯, 我想我有空闲时间聊几句... ",
                "不幸的是, 我得走了。 再见! ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat("你有什么有趣的事情要告诉我吗? ", 
                "你有什么有趣的事情要告诉我吗? ",
                "你有什么有趣的事情要告诉我吗? ", 
                "当然。 祝你好运! ", npchar, Dialog.CurrentNode);
            link.l1.go = DialogGoNodeRepeat("rumours_landcaptain", "rumours_landcaptain", "rumours_landcaptain", "exit", npchar, Dialog.CurrentNode);
        break;
        
        //任务部分
        case "march":
            dialog.text = "不, 船长, 街道和酒馆里有很多耳目, 我们不需要他们, 相信我。 可以说, 这个提议完全是关于... 敌意收购的。 我们去我的船上谈吧。 ";
            link.l1 = "好吧, 我听听... 你的船叫什么名字? ";
            link.l1.go = "march_1";
            link.l2 = "哈! 听起来很可疑。 我想还是算了。 再见, 先生! ";
            link.l2.go = "exit_quest";
        break;
        
        case "march_1":
            //在主角身上生成并存储参数, 因为通过NPC存储不太正常:(
            pchar.GenQuest.MarchCap.Startisland = Islands[GetCharacterCurrentIsland(PChar)].id;
            pchar.GenQuest.MarchCap.Parts = GetCompanionQuantity(pchar)+1;
            pchar.GenQuest.MarchCap.shiptype = SelectCaptainShipType();
            pchar.GenQuest.MarchCap.shipname = GenerateRandomNameToShip(sti(npchar.nation));
            pchar.GenQuest.MarchCap.nation = sti(npchar.Nation);
            pchar.GenQuest.MarchCap.model = npchar.model;
            pchar.GenQuest.MarchCap.rank = sti(npchar.rank);
            pchar.GenQuest.MarchCap.name = npchar.name;
            pchar.GenQuest.MarchCap.lastname = npchar.lastname;
            pchar.GenQuest.MarchCap.BaseNation = npchar.nation;
            pchar.GenQuest.MarchCap.Nation = hrand(NON_PIRATES);
            pchar.GenQuest.MarchCap.basecity = npchar.city;
            dialog.text = "我的船是"+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.MarchCap.shiptype), "Name")))+"'"+pchar.GenQuest.MarchCap.shipname+"'。 她现在在港口。 别迟到, 船长, 我六个小时后就走! ";
            link.l1 = "我知道了, 我会尽量准时。 再见! ";
            link.l1.go = "march_2";
        break;
        
        case "march_2":
            DialogExit();
            LAi_SetActorType(npchar);
            LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 30.0);
            npchar.lifeday = 0;
            pchar.quest.MarchCapOver.win_condition.l1 = "Timer";
            pchar.quest.MarchCapOver.win_condition.l1.date.hour  = sti(GetTime() + 6);
            pchar.quest.MarchCapOver.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
            pchar.quest.MarchCapOver.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
            pchar.quest.MarchCapOver.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
            pchar.quest.MarchCapOver.function = "MarchCap_Over";
            pchar.quest.MarchCap_Create.win_condition.l1 = "location";
            pchar.quest.MarchCap_Create.win_condition.l1.location = pchar.GenQuest.MarchCap.Startisland;
            pchar.quest.MarchCap_Create.function = "MarchCap_Create";
            log_Testinfo(pchar.GenQuest.MarchCap.Startisland);
        break;
        
        //公民角色对露出武器的评论
        case "CitizenNotBlade":
            dialog.text = NPCharSexPhrase(NPChar, "听着, 作为这个城镇的公民, 我请求你把剑收起来。 ", "听着, 作为这个城镇的公民, 我请求你把武器收起来。 ");
            link.l1 = LinkRandPhrase("好的。 ", "如你所愿。 ", "如你所说... ");
            link.l1.go = "exit";
        break;
        
        case "exit_quest":
            DialogExit();
            LAi_CharacterDisableDialog(npchar);
        break;
        
        case "Exit":
            NextDiag.CurrentNode = NextDiag.TempNode;
            DialogExit();
        break;
    }
}

int SelectCaptainShipType()
{
    int iClassFlag = FLAG_SHIP_CLASS_6;
    if (sti(pchar.rank) >= 19) iClassFlag = FLAG_SHIP_CLASS_2;    
    if (sti(pchar.rank) >= 13 && sti(pchar.rank) < 19) iClassFlag = FLAG_SHIP_CLASS_3;    
    if (sti(pchar.rank) >= 8 && sti(pchar.rank) < 12) iClassFlag = FLAG_SHIP_CLASS_4;
    if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 8) iClassFlag = FLAG_SHIP_CLASS_5;
    if (sti(pchar.rank) < 5) iClassFlag = FLAG_SHIP_CLASS_6;
    
    return GetRandomShipType(iClassFlag, FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
}