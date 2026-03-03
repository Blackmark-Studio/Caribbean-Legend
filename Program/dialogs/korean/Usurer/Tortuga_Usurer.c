// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("무슨 질문이 있으십니까?","무엇을 도와드릴까요?"),"얼마 전에 그 질문을 나에게 하려고 했었지...","그래, 맞지... 또 빙빙 돌고 있는 거야?","이봐, 여기서 재정은 내가 맡고 있어. 질문엔 답하지 않아...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("내 마음이 바뀌었어...","지금은 할 말이 없소."),"으음, 내 기억이 다 어디로 갔지...","맞췄군, 미안하네...","알겠습니다...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail":
			dialog.text = "안녕하십니까, 선장님. 저와 저희 회사가 어떻게 도와드릴 수 있을까요?";
			link.l1 = "토르투가의 명망 높은 주둔군 연금 기금에 기부를 하고 싶소.";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "알겠습니다. 요즘 꽤 인기가 많으시군요! 얼마를 빚지셨... 아니, 기부하시고 싶으신가요?";
			link.l1 = pchar.questTemp.TonzagQuest.Bail+" 두블론. 그런데, 페소도 받습니까?";
			link.l1.go = "tonzag_bail_2";
		break;
		
		case "tonzag_bail_2":
			dialog.text = "물론입니다만, 다만 비용이 조금 더 들 것입니다. 정확히 말씀드리자면... "+pchar.questTemp.TonzagQuest.Bail+" 두블룬이 될 것이오 "+sti(pchar.questTemp.TonzagQuest.Bail)* 150+" 페소입니다.";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.TonzagQuest.Bail) || sti(pchar.money) >= sti(pchar.questTemp.TonzagQuest.Bail) * 150) {
				link.l1 = "조금 더 비싸다고요? 여기 있습니다, 필요한 전액입니다.";
				link.l1.go = "tonzag_bail_give";
			} else {
				link.l1 = "조금 더 비싸다고요? 안타깝게도 지금은 그만한 금액이 없습니다. 이 일로 대출을 받을 수 있을까요?";
				link.l1.go = "tonzag_bail_loan";
			}
		break;
		
		case "tonzag_bail_give":
			dialog.text = "훌륭합니다. 즉시 거래 상대방에게 알리겠습니다! 안녕히 가십시오, 선장님. 그리고... 행운을 빕니다. 저희는 오래전부터 당신의 활약을 기대해 왔습니다.";
			link.l1 = "안녕히 가십시오.";
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
			dialog.text = "이런 기회는 언제나 "+pchar.name+" 선장님께 열려 있습니다! 예를 들어, 6개월 후에 20만 페소를 상환하는 조건으로 어떻겠습니까?";
			link.l1 = "별 수 없군. 어디에 서명하면 되지?";
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
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
