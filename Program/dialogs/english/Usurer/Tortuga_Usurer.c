// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?","How can I help you?"),"You tried to ask me that question not long ago...","Yup, let me guess... Going around in circles again?","Listen, I handle the finances here, I don't answer questions...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...","I've got nothing to talk about at the moment."),"Umph, where has my memory gone...","You've guessed it, I'm sorry...","I understand...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail":
			dialog.text = "Hello, Captain. How can my firm and I be of service to you?";
			link.l1 = "I'd like to make a donation to the pension fund of the illustrious garrison of Tortuga.";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "I understand. Getting quite popular these days! How much do you owe... I mean, wish to donate?";
			link.l1 = pchar.questTemp.TonzagQuest.Bail+" doubloons. Tell me, do you accept pesos?";
			link.l1.go = "tonzag_bail_2";
		break;
		
		case "tonzag_bail_2":
			dialog.text = "Of course, however, it will be a bit more expensive for you. Let me tell you exactly... "+pchar.questTemp.TonzagQuest.Bail+" doubloons will be "+sti(pchar.questTemp.TonzagQuest.Bail)* 150+" pesos.";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.TonzagQuest.Bail) || sti(pchar.money) >= sti(pchar.questTemp.TonzagQuest.Bail) * 150) {
				link.l1 = "A bit more expensive, you say? Here you are, the full required amount.";
				link.l1.go = "tonzag_bail_give";
			} else {
				link.l1 = "A bit more expensive, you say? Unfortunately, I don't have that amount at the moment. Is it possible to take out a loan for this matter?";
				link.l1.go = "tonzag_bail_loan";
			}
		break;
		
		case "tonzag_bail_give":
			dialog.text = "Wonderful. We will inform your counterparty immediately! Goodbye, Captain. And... good luck, we've been looking forward to your performance for quite some time.";
			link.l1 = "So long.";
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
			dialog.text = "Such an opportunity is always available to you, Captain! Let's say, with the return of two hundred thousand pesos in six months?";
			link.l1 = "I have no choice. Where do I sign?";
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
