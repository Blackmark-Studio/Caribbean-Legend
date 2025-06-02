// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti?"),"Hai cercato di farmi una domanda un po' di tempo fa...","Mai ho incontrato persone con tanta curiosità nel mio cantiere navale o in qualsiasi altro luogo di questa città.","Perché tutte queste domande? Il mio lavoro è costruire navi. Occupiamoci di questo.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Umph, dove se n'è andata la mia memoria...","Mh, beh...","Avanti...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Ascolta, un corsaro di nome Francois Gontier non si è fermato a parlare con te per caso, vero? E' stato di recente a Porto Bello, lo so.";
                link.l1.go = "Portobello_ratS_1";
            }
		break;
		
		case "Portobello_ratS_1":
			dialog.text = "L'ha fatto. Ha acquisito una corvetta da me e presto è partito per il mare.";
			link.l1 = "Grazie! E avete idea di dove sia partito?";
			link.l1.go = "Portobello_ratS_2";
		break;
			
		case "Portobello_ratS_2":
			dialog.text = "No, compagno, non ne ho idea. Riparo e vendo navi, non seguo dove vanno. Non sono affari miei.";
			link.l1 = "Allora, grazie... Scopriamo dove sei andato...";
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "FindRatPortobello_1";
			AddQuestRecord("Slavetrader", "21_2");
		break;
			
			
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
