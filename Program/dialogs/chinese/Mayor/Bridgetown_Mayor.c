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
			//荷兰人的赌注
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "我在马提尼克岛谈成了一笔有利可图的交易, 现在我计划前往布卢韦尔德。 我想在贵殖民地购买红木和咖啡。 此外, 我的双桅横帆船装不下我想买的那么多货物, 所以我需要在贵造船厂买一艘长笛船。 您能在这些事情上给予我帮助吗? ";
                link.l1.go = "MayorDone";
            }
		break;
		
		case "MayorDone":
			dialog.text = "我的帮助? 我们的商人是非常诚实的, 所以我怀疑他不会试图欺骗您。 关于长笛船的事, 您可以和船匠谈谈, 他会帮您解决这个问题。 如果您还是遇到了麻烦, 就来找我。 我有兴趣促进与我们殖民地的贸易联系, 我会全力支持您。 \n另外, 我今晚要举办一场宴会, 布里奇敦的各界名流都会参加。 您也应该来, 船长。 ";
			link.l1 = "感谢您的邀请, 但遗憾的是我太忙了。 再见, 感谢您的帮助! ";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-8");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
			AddQuestRecord("Holl_Gambit", "2-6");
			pchar.questTemp.HWIC.Eng = "SeekVanBerg";
			pchar.quest.GotoBridgetownOver.over = "yes";//移除计时器
			DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
				//if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_VALCIRIA || GetCompanionQuantity(pchar) > 1) AddDialogExitQuestFunction("FailVanBergInWorld");
				//else AddDialogExitQuestFunction("CreateVanBergInWorld");
			}
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch内部某个地方通过return退出, 别忘了在此处卸载
}