// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
    {
        case "quests":
            dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么事? 直说吧。 ", "我在听, 有什么问题? "), "这是你第二次试图提问... ", "这是你第三次试图提问... ",
                          "这要到什么时候才结束? ! 我是个大忙人, 正处理着殖民地的事务, 而你还在试图问东问西! ", "block", 1, npchar, Dialog.CurrentNode);
            link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "现在不行。 地点和时间都不合适。 "), "确实... 但稍后吧, 不是现在... ",
                      "我会问的... 但稍后一点... ", "抱歉, " + GetAddress_FormToNPC(NPChar) + "... ", npchar, Dialog.CurrentNode);
            link.l1.go = "exit";
            //--> 加斯科涅人的负担
            if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "saga" && !CheckAttribute(npchar, "quest.saga"))
            {
                link.l1 = "我想见德.庞西骑士。 是关于我兄弟们的债务问题。 ";
                link.l1.go = "puancie";
            }
            //< —加斯科涅人的负担
        break;
        
        case "puancie":
            dialog.text = "啊哈, 好吧, 我知道那笔债务... 你带够钱了吗? ";
            if (sti(pchar.money) >= 1000000)
            {
                link.l1 = "当然带够了。 不然还能怎样? ";
                link.l1.go = "puancie_1";
            }
            else
            {
                link.l1 = "不, 我还没凑够那么多钱。 ";
                link.l1.go = "puancie_exit";
            }
        break;
        
        case "puancie_exit":
            dialog.text = "等你凑够了钱再来, 别烦骑士大人。 ";
            link.l1 = "... ";
            link.l1.go = "exit";
        break;
        
        case "puancie_1":
            dialog.text = "那就从右边的门进去。 骑士会接见你的。 ";
            link.l1 = "谢谢! ";
            link.l1.go = "puancie_2";
        break;
        
        case "puancie_2":
            DialogExit();
            npchar.quest.saga = "true";
            bDisableFastReload = true;//关闭快速移动
            LocatorReloadEnterDisable("Charles_townhall", "reload1_back", true);//防止出去
            LocatorReloadEnterDisable("Charles_townhall", "reload3", false);//打开通往庞西的入口
            ref sld = characterFromId("Puancie");
            ChangeCharacterAddressGroup(sld, "Charles_Roomtownhall", "sit", "sit1");
            LAi_SetHuberType(sld);
            sld.dialog.currentnode = "saga";
        break;
    }
    UnloadSegment(NPChar.FileDialog2);  // 如果在switch内部某个地方通过return退出, 别忘了在此处卸载
}