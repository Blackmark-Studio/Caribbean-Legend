// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Domande, "+GetAddress_Form(NPChar)+"?","Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Mh, qual è la grande idea, "+GetAddress_Form(NPChar)+"? ","Di nuovo con le domande strane? Bella, vai a bere un po' di rum o qualcosa del genere...")+"","Durante tutto il giorno, questa è la terza volta che parli di qualche domanda..."+GetSexPhrase("Questi sono alcuni segni di attenzione?","")+"","Altre domande, presumo, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea","Non ho niente di cui parlare al momento."),"No, no bella...","Assolutamente no, cara...","No, quali domande?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "helendrinking":
			dialog.text = "Come ha dormito, signore? La signorina MacArthur ci ha ordinato di garantire il suo pieno comfort!";
			link.l1 = "Ho fatto un sogno molto strano...";
			link.l1.go = "helendrinking_1";
		break;

		case "helendrinking_1":
			dialog.text = "Ah!...";
			link.l1 = "Cosa c'è, mademoiselle? Posso aiutarti con qualcosa?";
			link.l1.go = "helendrinking_2";
		break;

		case "helendrinking_2":
			dialog.text = "Mi dispiace, Capitano... È un peccato, ma non posso resistere! Non sono molto esperta, ma non rifiutare la ragazza, Capitano! Sei così affascinante! Voglio compiacerti, toccarti...";
			link.l1 = "Certo, pieno comfort... Sei anche molto bella! Dai, non essere timida.";
			link.l1.go = "helendrinking_sex";
			link.l2 = "È meglio non toccarmi ora, mademoiselle - puzzo di rum. Ma puoi farmi piacere - una colazione sarebbe molto gradita!";
			link.l2.go = "helendrinking_nosex";
		break;
		
		case "helendrinking_sex":
			dialog.text = "Oh mio, oh mio!";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			notification("Helen disapproves", "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressSex");
		break;

		case "helendrinking_nosex":
			dialog.text = "Scortese!";
			link.l1 = "Niente colazione allora?";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			notification("Helen approves", "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressNoSex");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
