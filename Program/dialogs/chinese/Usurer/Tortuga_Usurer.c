// 城市对话
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("你有什么问题? ", "我能为你做什么? "), "你不久前刚问过我这个问题... ", "没错, 让我猜猜... 又在绕圈子了? ",
                          "听着, 我在这里管财务, 不回答问题... ", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("我改变主意了... ", "我现在没什么可聊的。 "), "嗯, 我的记性哪去了... ",
                      "你猜对了, 抱歉... ", "我明白了... ", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail":
			dialog.text = "你好, 船长。 我和我的公司能为你做些什么? ";
			link.l1 = "我想为托尔图加赫赫有名的驻军养老基金捐款。 ";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "我明白了。 最近这事儿很流行啊! 你欠多少... 我是说, 你想捐多少? ";
			link.l1 = pchar.questTemp.TonzagQuest.Bail + " 杜布隆。 告诉我, 你们收比索吗? ";
			link.l1.go = "tonzag_bail_2";
		break;
		
		case "tonzag_bail_2":
			dialog.text = "当然收, 不过这对你来说要贵一点。 让我确切地告诉你... " + pchar.questTemp.TonzagQuest.Bail + " 杜布隆相当于 " + sti(pchar.questTemp.TonzagQuest.Bail) * 150 + " 比索。 ";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.TonzagQuest.Bail) || sti(pchar.money) >= sti(pchar.questTemp.TonzagQuest.Bail) * 150) {
				link.l1 = "你说要贵一点? 给你, 所需的全额款项。 ";
				link.l1.go = "tonzag_bail_give";
			} else {
				link.l1 = "你说要贵一点? 遗憾的是, 我现在没有那么多钱。 这件事可以贷款吗? ";
				link.l1.go = "tonzag_bail_loan";
			}
		break;
		
		case "tonzag_bail_give":
			dialog.text = "太好了。 我们会立即通知你的交易对手! 再见, 船长。 还有... 祝你好运, 我们期待你的表现很久了。 ";
			link.l1 = "再见。 ";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			if (PCharDublonsTotal() >= sti(pchar.questTemp.TonzagQuest.Bail)) {
				RemoveDublonsFromPCharTotal(sti(pchar.questTemp.TonzagQuest.Bail));
			} else {
				AddMoneyToCharacter(pchar, -(sti(pchar.questTemp.TonzagQuest.Bail) * 150));
			}
			sld = CharacterFromID("TortugaJailOff");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "tonzag_bailed";
		break;
		
		case "tonzag_bail_loan":
			dialog.text = "船长, 你总是有这样的机会! 比如说, 六个月后还二十万比索? ";
			link.l1 = "我别无选择。 我在哪里签字? ";
			link.l1.go = "tonzag_bail_give";
			
			pchar.quest.loans.tortuga.sum = 200000;
			pchar.quest.loans.tortuga.interest = 0;
			pchar.quest.loans.tortuga.period = 6;
			pchar.quest.loans.tortuga.StartDay = GetDataDay();
			pchar.quest.loans.tortuga.StartMonth = GetDataMonth();
			pchar.quest.loans.tortuga.StartYear = GetDataYear();
			pchar.quest.loans.tortuga.StartTime = GetTime();
			SetTimerCondition("Loans_Tortuga", 0, makeint(pchar.quest.loans.tortuga.period), 0, false);
			pchar.quest.Loans_Tortuga.CityId = "Tortuga";
			pchar.quest.Loans_Tortuga.win_condition = "LoansForAll";
			
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.TonzagQuest.Bail) * 150);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // 如果在switch内部的某个地方通过return退出, 不要忘记卸载
}
