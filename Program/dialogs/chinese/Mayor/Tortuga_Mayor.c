// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你想要什么? 问吧。 ", "我在听, 你有什么问题? "), "这是你第二次尝试提问... ", "这是你第三次尝试提问... ",
                          "这要到什么时候才结束? ! 我是个忙人, 在处理殖民地事务, 而你还在烦我! ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了, 抱歉。 ", "现在不行。 地点和时间不对。 "), "是的, 我现在没什么要说的, 抱歉。 ",
                      "我稍后再问。 ", "抱歉, " + GetAddress_FormToNPC(NPChar) + "... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            // 插件2016 杰森, 法国迷你任务 (FMQ) 托尔图加
            if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "huber")
            {
                link.l1 = "总督先生, 我有个坏消息要告诉你。 长话短说: 你的妻子想抢劫你。 她试图说服我撬开你的一个柜子。 我觉得你应该知道这件事。 ";
                link.l1.go = "FMQT";
            }
            // 杰森 圣马丁岛
            if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
            {
                link.l1 = TimeGreeting() + ", 先生。 我是奉总督谢瓦利埃.德.潘西之命而来。 我的任务是将一位名叫诺埃尔.福热的男爵护送到托尔图加, 他从母国带着视察殖民地的命令而来。 他的主要目的是建立一家法属西印度贸易公司。 让我把他介绍给你... 他会亲自解释所有细节。 ";
                link.l1.go = "patria_tortuga";
            }
        break;
        
        case "FMQT":
            dialog.text = "什 —么? 又来? 那个贱人! 她会为此后悔的, 我发誓! 坎帕乔会让她尖叫的。 你还在这里干什么? 给我滚出去! ";
            link.l1 = "我以为... ";
            if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 25) link.l1.go = "FMQT_2";
            else link.l1.go = "FMQT_1";
        break;
        
        case "FMQT_1":
            AddMoneyToCharacter(pchar, 1000);
            dialog.text = "总是这样! 拿着这个! 这是我桌子里所有的钱了! 现在滚! ";
            link.l1 = "谢谢您, 大人。 我这就告辞。 ";
            link.l1.go = "FMQT_3";
        break;
        
        case "FMQT_2":
            AddMoneyToCharacter(pchar, 1000);
            GiveItem2Character(pchar, "pistol6");
            GiveItem2Character(pchar, "purse1");
            Log_Info("你获得了一把双管手枪和一袋达布隆金币");
            dialog.text = "总是这样! 拿着这个! 这是我桌子里所有的钱了! ... 不过, 算了, 你看起来不像我岛上那些蠢货和失败者。 再拿点额外的... 现在滚! ";
            link.l1 = "谢谢您, 大人。 我这就告辞。 ";
            link.l1.go = "FMQT_3";
        break;
        
        case "FMQT_3":
            DialogExit();
            pchar.quest.FMQT_late1.over = "yes";
            ChangeCharacterNationReputation(pchar, FRANCE, 5);
            ChangeCharacterComplexReputation(pchar, "nobility", 2);
            pchar.questTemp.FMQT = "end";
            FMQ_Count();
            AddQuestRecord("FMQ_Tortuga", "7");
            CloseQuestHeader("FMQ_Tortuga");
            FMQT_ClearChest();
        break;
        
        // 杰森 圣马丁岛
        case "patria_tortuga":
            dialog.text = "很好, 查尔斯.德.莫尔船长。 男爵会得到相应的待遇, 我会尽我所能帮助他完成任务。 ";
            link.l1 = "";
            link.l1.go = "patria_tortuga_1";
        break;
        
        case "patria_tortuga_1":
            DialogExit();
            sld = characterFromId("Noel");
            sld.dialog.currentnode = "noel_5";
            ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
            LAi_SetActorType(sld);
            LAi_ActorDialogDelay(sld, pchar, "", 1.0);
            npchar.quest.patria = "true";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果switch内部有通过return退出的情况, 别忘了执行此卸载
}