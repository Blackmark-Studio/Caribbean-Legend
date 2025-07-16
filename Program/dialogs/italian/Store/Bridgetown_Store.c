// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Vai avanti, cosa vuoi?","Ne stavamo proprio parlando. Devi aver dimenticato...","Questa è la terza volta oggi che parli di qualche domanda...","Ascolta, questo è un negozio. La gente compra roba qui. Non disturbarmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, per qualche motivo ho dimenticato...","Sì, è davvero la terza volta...","Mm, non lo farò...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Ascolta, un piccolo uccello mi ha detto che i prezzi del legno rosso e del cacao a Belize stanno per salire molto presto. Ho fatto un buon affare di recente e ho riempito la mia borsa con i dobloni, he-he... Mi piacerebbe acquistare un po' di questa merce. Posso contare su uno sconto?";
                link.l1.go = "StoreDone";
            }
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "barbados1")
			{
				link.l1 = "Una galea chiamata 'Ammirabile' è recentemente approdata alla tua colonia sotto il comando del capitano Gaius Marchais. Dimmi, avrebbe potuto rifornirsi qui di munizioni o merci da rivendere?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "StoreDone":
			dialog.text = "Ebbene, signore, se la partita è davvero grande, allora naturalmente, possiamo discutere uno sconto ragionevole.";
			link.l1 = "Meraviglioso! Ho sentito dire che un nuovo fluyt dovrebbe uscire in vendita al cantiere navale uno di questi giorni. Aspetterò e comprerò quella nave. Anche se ho smontato tutti i cannoni dalla mia brigata, non c'è ancora abbastanza spazio nel mio deposito per tutte queste merci! Passerò più tardi!";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-11");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Ah! Mi ricordo di quel tipo strano! Ha creduto ad una stupida voce che Guadalupa avrebbe disperatamente bisogno di vaniglia perché una grande carovana di mercanti europei si sarebbe fermata lì per comprare tutte le spezie che potevano contenere\nSento queste sciocchezze ogni mese, ma Marchais l'ha presa molto sul serio. Ha passato una settimana qui, mi ha detto di raccogliere abbastanza vaniglia per riempire i suoi stiva\nSembra che abbia speso ogni moneta per questo. Mi sento male per quel uomo, ma non posso impedire agli uomini di impazzire se vogliono.";
			link.l1 = "Allora, potrebbe essere a Guadalupe adesso?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Molto probabile. Perché continuerà ad aspettare i suoi fantomatici 'commercianti' fino alla seconda venuta di Cristo e perderà solo soldi vendendo vaniglia. Se è saggio, rimarrà a Basse-Terre fino a quando la domanda di vaniglia non aumenterà o fino a quando scoprirà con certezza un altro luogo dove ne hanno più bisogno.";
			link.l1 = "Già. Grazie, mi hai aiutato molto!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "14");
			pchar.questTemp.Guardoftruth = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1 = "location";
			pchar.quest.GuardOT_guadeloupe.win_condition.l1.location = "guadeloupe";
			pchar.quest.GuardOT_guadeloupe.function = "GuardOT_CreateTwoShips";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
