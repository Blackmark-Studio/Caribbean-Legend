// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti?"),"Hai provato a farmi quella domanda non molto tempo fa...","Sì, lascia che indovini... Ancora una volta girando in tondo?","Ascolta, io gestisco le finanze qui, non rispondo alle domande...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Uhm, dove se ne è andata la mia memoria...","Hai indovinato, mi dispiace...","Capisco...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail":
			dialog.text = "Salve, Capitano. Come posso io e la mia compagnia esserle di servizio?";
			link.l1 = "Vorrei fare una donazione al fondo pensione dell'illustre guarnigione di Tortuga.";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "Capisco. Sempre più popolare al giorno d'oggi! Quanto devi... voglio dire, desideri donare?";
			link.l1 = pchar.questTemp.TonzagQuest.Bail+" dobloni. Dimmi, accetti in pesos?";
			link.l1.go = "tonzag_bail_2";
		break;
		
		case "tonzag_bail_2":
			dialog.text = "Certo, tuttavia, sarà un po' più costoso per te. Lascia che ti dica esattamente... "+pchar.questTemp.TonzagQuest.Bail+" i dobloni saranno "+sti(pchar.questTemp.TonzagQuest.Bail)* 150+" pesos.";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.TonzagQuest.Bail) || sti(pchar.money) >= sti(pchar.questTemp.TonzagQuest.Bail) * 150) {
				link.l1 = "Un po' più costoso, dici? Ecco a te, l'intero importo richiesto.";
				link.l1.go = "tonzag_bail_give";
			} else {
				link.l1 = "Un po' più costoso, dici? Purtroppo, al momento non dispongo di tale somma. È possibile ottenere un prestito per questa questione?";
				link.l1.go = "tonzag_bail_loan";
			}
		break;
		
		case "tonzag_bail_give":
			dialog.text = "Meraviglioso. Informeremo immediatamente la vostra controparte! Addio, Capitano. E... buona fortuna, aspettavamo la vostra performance da molto tempo.";
			link.l1 = "Arrivederci.";
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
			dialog.text = "Un'opportunità del genere è sempre disponibile per te, Capitano! Diciamo, con il ritorno di duecentomila pesos in sei mesi?";
			link.l1 = "Non ho scelta. Dove firmo?";
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
