// 城市对话处理
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("什么问题? ", "你想要什么, " + GetAddress_Form(NPChar) + "? "), "你已经试过问我问题了, " + GetAddress_Form(NPChar) + "... ", "你今天已经第三次谈论某个问题了... ",
                          "听着, 如果你没有关于港口事务的事告诉我, 就别用问题打扰我。 ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了。 ", "我没什么可谈的。 "), "没关系。 ", "确实, 已经第三次了... ", "抱歉, 我现在对港口事务不感兴趣。 ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";

			// 奴隶贩子
			if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_P")
            {
    			link.l1 = "我想了解那艘在奴隶起义后失踪的三桅帆船的情况。 ";
    			link.l1.go = "EscapeSlave_Villemstad_P1";
            }
			// 荷兰人的策略, 对抗所有人
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "SeekFleut")
            {
    			link.l1 = "我要找一个叫托夫.凯勒的船长。 他有一艘叫'莱顿号'的荷兰商船。 有人告诉我他经常来威廉斯塔德, 所以你帮我应该不难。 ";
    			link.l1.go = "SeekTradeFleut";
            }
		break;

		// 奴隶贩子
		case "EscapeSlave_Villemstad_P1":
				dialog.text = "嗯... 你为什么感兴趣? 黑人是你的专长? ";
				link.l1 = "我是奉总督马蒂亚斯.贝克的命令来的。 我有充分理由怀疑逃跑的黑人偷走了那艘船并驾船逃走了。 所以我请你尽一切可能协助我的调查。 ";
				link.l1.go = "EscapeSlave_Villemstad_P2";
		break;
		
		case "EscapeSlave_Villemstad_P2":
				dialog.text = "明白了。 好吧, 我帮不了你。 三桅帆船'" + pchar.questTemp.Slavetrader.ShipName + "'到早上就不见了, 没人看到什么。 我当时在家睡觉。 码头守望员也不见了, 没留下任何线索。 \n总督派了一艘单桅帆船去追踪, 趁线索还没断, 但他们空手而归。 既没有黑人的踪迹, 也没有'" + pchar.questTemp.Slavetrader.ShipName + "'的影子。 说实话, 那艘单桅帆船没怎么仔细找, 每个人都还处于恐慌中, 以为卡菲尔人会拿着干草叉和大砍刀从丛林里冲出来 --渴望白人的鲜血。 ";
				link.l1 = "这没什么帮助, 但还是谢谢你。 再见。 ";
				link.l1.go = "exit";
				AddQuestRecord("Slavetrader", "22_3");
				AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
				pchar.questTemp.Slavetrader = "EscapeSlaveVillemstad_H";
		break;				
		// 荷兰人的策略
		case "SeekTradeFleut":
			DelLandQuestMark(npchar);
			dialog.text = "托夫.凯勒? 我当然认识他! 他定期航行到特立尼达的圣何塞和库马纳。 他最近刚去过特立尼达。 我想你可以在那里找到他。 ";
			link.l1 = "谢谢! ";
			link.l1.go = "SeekTradeFleut_1";
		break;
		
		case "SeekTradeFleut_1":
			DialogExit();
			AddMapQuestMarkIsland("Trinidad", true);
			pchar.questTemp.HWIC.Self = "FleutOnTrinidad";
			AddQuestRecord("Holl_Gambit", "3-59");
			pchar.quest.Seek_Fleut.win_condition.l1 = "location";
			pchar.quest.Seek_Fleut.win_condition.l1.location = "Trinidad";
			pchar.quest.Seek_Fleut.function = "CreateTradeFleut";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 若switch内部通过return退出, 需确保执行卸载
}