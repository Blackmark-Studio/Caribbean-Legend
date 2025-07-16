// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande, "+GetSexPhrase("mio figlio","mia figlia")+"?","Chiedi pure, sto ascoltando..."),"Sto ascoltando, parla ora, "+GetSexPhrase("mio figlio","mia figlia")+"...","Per la terza volta, "+GetSexPhrase("mio figlio","mia figlia")+", chiedi ciò di cui hai bisogno.","Un ecclesiastico ha molto lavoro e tu mi stai distrarrendo, "+GetSexPhrase("mio figlio","mia figlia")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non in questo momento, padre..."),"Non ho nulla da dire, mi scuso.","Chiederò, ma più tardi. Perdonami, padre.","Mi perdoni, santo padre...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Долго и счастливо
			if (CheckAttribute(pchar, "questTemp.LongHappy") && pchar.questTemp.LongHappy == "choose" && !CheckAttribute(npchar, "quest.LongHappy"))
			{
				link.l1 = "Santo Padre, sto cercando l'Abate Benoit, ho una questione urgente per lui. Puoi dirmi dove posso trovarlo?";
				link.l1.go = "LH_church";
			}
		break;
		
		// Jason Долго и счастливо
		case "LH_church":
			dialog.text = "L'abate Benoit ha lasciato la città per questioni ecclesiastiche con i rappresentanti della missione cattolica spagnola nel Nuovo Mondo. Non conosco i dettagli, ma l'abate Benoit è assente abbastanza a lungo da supporre che le negoziazioni si siano prolungate, o che sia accaduto qualcosa lungo il cammino. Siamo tutti inquieti, ma possiamo solo pregare e attendere notizie.";
			link.l1 = "Non posso presumere che tutto sia facile. Santo padre, potreste dirmi esattamente dove è andato l'abate Benoit? Ho bisogno di trovarlo il più rapidamente possibile.";
			link.l1.go = "LH_church_1";
		break;
		
		case "LH_church_1":
			dialog.text = "Temerei che non posso, mio figlio. Per quanto ne so, l'abate Benoit è andato a negoziare con il vescovo della Nuova Spagna e il prelato dell'Inquisizione, Padre Vincento Palotti, ma non ha specificato dove si terrà l'incontro.";
			link.l1 = "Dovrebbe bastare, Santo Padre, grazie. Conosco padre Palotti in qualche modo... Darò un'occhiata a Santiago.";
			link.l1.go = "LH_church_2";
		break;
		
		case "LH_church_2":
			DialogExit();
			npchar.quest.LongHappy = "true";
			LongHappy_GoToSantiago();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
