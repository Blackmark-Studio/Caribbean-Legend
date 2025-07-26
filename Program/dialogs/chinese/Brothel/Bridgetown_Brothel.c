// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么样的问题, " + GetSexPhrase("年轻人", "年轻女士") + "?", "你需要什么, " + GetSexPhrase("帅哥", "美人") + "? 问吧。 "), "又问问题?", "嘻嘻, 如果你不介意的话 --还是问题... ",
                          "" + GetSexPhrase("嗯, 你怎么不自己挑个美人呢? 我开始怀疑你了... ", "嗯, 你怎么不自己挑个美人呢? 恐怕我们这儿可没有小伙子哦, 嘻嘻... ") + "", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了, 抱歉。 ", "其实, 算了... "), "我... 抱歉, 目前没什么问题了。 ",
                      "你说得对, 这都第三次了。 请原谅。 ", "也许下次吧, 夫人。 ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "我买了一船桃花心木准备去布莱维尔德贸易。 路程还很远, 我的人手又少, 大家都很焦虑... 让五十名水手在这里休息一晚要多少钱? ";
                link.l1.go = "BrothelDone";
            }
        break;
        
        case "BrothelDone":
            dialog.text = "五十名水手 - 一万五千。 ";
            link.l1 = "这是一大笔钱... 我需要考虑一下。 ";
            link.l1.go = "exit";    
            npchar.quest.HWICTalked = "true";
            pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
            AddQuestRecord("Holl_Gambit", "2-7");
            DelLandQuestMark(npchar);
            if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
            {
                AddQuestRecord("Holl_Gambit", "2-6");
                pchar.quest.GotoBridgetownOver.over = "yes"; // 取消计时器
                DelMapQuestMarkCity("Bridgetown");
                pchar.questTemp.HWIC.Eng = "SeekVanBerg";
                pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
                pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
                // if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
                // else AddDialogExitQuestFunction("CreateVanBergInWorld");
            }
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch内部的某个地方通过return退出, 别忘了进行卸载
}