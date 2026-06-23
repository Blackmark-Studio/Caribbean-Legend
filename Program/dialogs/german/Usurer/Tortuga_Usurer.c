// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Fragen haben Sie?","Wie kann ich Ihnen helfen?"),"Du hast versucht, mir diese Frage vor nicht allzu langer Zeit zu stellen...","Ja, lass mich raten... Wieder im Kreis herumlaufen?","Hör zu, ich mache hier die Finanzen, ich beantworte keine Fragen...","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe es mir anders überlegt...","Ich habe im Moment nichts zu besprechen."),"Umph, wo ist mein Gedächtnis hin...","Du hast es erraten, es tut mir leid...","Ich verstehe...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail":
			dialog.text = "Hallo, Kapitän. Wie können ich und meine Firma Ihnen behilflich sein?";
			link.l1 = "Ich möchte eine Spende an den Pensionsfonds der illustren Garnison von Tortuga machen.";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "Ich verstehe. Wird heutzutage ziemlich beliebt! Wie viel schulden Sie... ich meine, möchten Sie spenden?";
			link.l1 = pchar.questTemp.TonzagQuest.Bail+" Dublonen. Sag mir, akzeptierst du in Pesos?";
			link.l1.go = "tonzag_bail_2";
		break;
		
		case "tonzag_bail_2":
			dialog.text = "Natürlich, es wird jedoch ein bisschen teurer für Sie sein. Lassen Sie mich Ihnen genau sagen... "+pchar.questTemp.TonzagQuest.Bail+" Dublonen werden sein "+int(pchar.questTemp.TonzagQuest.Bail)* 150+" Pesos.";
			if (PCharDublonsTotal() >= int(pchar.questTemp.TonzagQuest.Bail) || int(pchar.money) >= int(pchar.questTemp.TonzagQuest.Bail) * 150) {
				link.l1 = "Etwas teurer, sagst du? Hier hast du den vollen geforderten Betrag.";
				link.l1.go = "tonzag_bail_give";
			} else {
				link.l1 = "Etwas teurer, sagen Sie? Leider habe ich momentan nicht diesen Betrag. Ist es möglich, für diese Angelegenheit einen Kredit aufzunehmen?";
				link.l1.go = "tonzag_bail_loan";
			}
		break;
		
		case "tonzag_bail_give":
			dialog.text = "Wunderbar. Wir werden Ihre Vertragspartei sofort informieren! Auf Wiedersehen, Kapitän. Und... viel Glück, wir freuen uns schon seit langem auf Ihre Leistung.";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			if (PCharDublonsTotal() >= int(pchar.questTemp.TonzagQuest.Bail)) {
				RemoveDublonsFromPCharTotal(int(pchar.questTemp.TonzagQuest.Bail));
			} else {
				AddMoneyToCharacter(pchar, -(int(pchar.questTemp.TonzagQuest.Bail) * 150));
			}
			sld = CharacterFromID("TortugaJailOff");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "tonzag_bailed";
		break;
		
		case "tonzag_bail_loan":
			dialog.text = "Solch eine Gelegenheit steht Ihnen immer zur Verfügung, Kapitän! Sagen wir mal, mit der Rückgabe von zweihunderttausend Pesos in sechs Monaten?";
			link.l1 = "Ich habe keine Wahl. Wo soll ich unterschreiben?";
			link.l1.go = "tonzag_bail_give";
			
			pchar.quest.loans.tortuga.sum = 200000;
			pchar.quest.loans.tortuga.interest = 0;
			pchar.quest.loans.tortuga.period = 6;
			pchar.quest.loans.tortuga.StartDay = GetDataDay();
			pchar.quest.loans.tortuga.StartMonth = GetDataMonth();
			pchar.quest.loans.tortuga.StartYear = GetDataYear();
			pchar.quest.loans.tortuga.StartTime = GetTime();
			SetTimerCondition("Loans_Tortuga", 0, int(pchar.quest.loans.tortuga.period), 0, false);
			pchar.quest.Loans_Tortuga.CityId = "Tortuga";
			pchar.quest.Loans_Tortuga.win_condition = "LoansForAll";
			
			AddMoneyToCharacter(pchar, int(pchar.questTemp.TonzagQuest.Bail) * 150);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
