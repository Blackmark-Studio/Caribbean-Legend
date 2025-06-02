// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti?"),"Hai cercato di farmi una domanda un po' di tempo fa...","Non ho mai incontrato persone con tanta curiosità nel mio cantiere navale o in qualsiasi altro luogo di questa città.","Perché tutte queste domande? Il mio lavoro è costruire navi. Occupiamoci di questo.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Uh, dove se n'è andata la mia memoria...","Mm, beh...","Avanti...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "helendrinking_buy_rainbow":
			dialog.text = "... una scelta degna, signore. Allora, abbiamo un accordo?";
			link.l1 = "S-sì! Alla salute! Avvolgilo e mandalo al molo. E fallo in fretta, una signora mi sta aspettando per strada!";
			link.l1.go = "helendrinking_buy_rainbow_1";
			locCameraFromToPos(0.36, 1.86, 1.15, true, 2.06, -0.20, -4.38);
		break;
		
		case "helendrinking_buy_rainbow_1":
			dialog.text = "Cinquanta mila argenti per tutto, signore.";
			if (sti(pchar.money) >= 55000) {
				link.l1 = "C-cosa hai detto? C-cinquanta mila? Beh, contali tu stesso! E prendi altri cinque mila come mancia. Andiamo!";
				link.l1.go = "helendrinking_buy_rainbow_yes";
			}
			
			link.l2 = "No-no, potrei essere ricco, hic! ...uomo, ma non lo prenderò per così tanto. No, signore! Addio, barcaiolo.";
			link.l2.go = "helendrinking_buy_rainbow_no";
		break;
		
		case "helendrinking_buy_rainbow_yes":
			dialog.text = "Grazie, signore. Possa servirti bene!";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddMoneyToCharacter(pchar, -55000);
			pchar.questTemp.HelenDrinking.BoughtRainbow = true;
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
		case "helendrinking_buy_rainbow_no":
			dialog.text = "Sì, vattene, riccone. Abbiamo chiuso tre ore fa.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
