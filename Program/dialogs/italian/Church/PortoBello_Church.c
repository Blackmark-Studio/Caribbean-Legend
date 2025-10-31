// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande, "+GetSexPhrase("mio figlio","mia figlia")+"?","Chiedi pure, ti sto ascoltando..."),"Sto ascoltando, parla ora, "+GetSexPhrase("mio figlio","mia figlia")+"...","Per la terza volta, "+GetSexPhrase("mio figlio","mia figlia")+", chiedi ciò di cui hai bisogno.","Un religioso ha molto lavoro e tu mi stai distrarrendo, "+GetSexPhrase("figlio mio","mia figlia")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non in questo momento, padre..."),"Non ho nulla da dire, mi scuso.","Chiederò, ma più tardi. Perdonami, padre.","Perdonami, santo padre...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Church_1"))
            {
                link.l1 = "Padre santo, sto cercando Marisa Caldera. Si dice che fosse molto devota e frequentasse regolarmente la chiesa. Potete dirmi dove posso trovarla?";
                link.l1.go = "LFD_Church_1_1";
            }
			//<-- Письмо от покойника
		break;
		//--> Письмо от покойника
		case "LFD_Church_1_1":
			dialog.text = "Marisa era una delle nostre parrocchiane più devote, la vera anima della nostra chiesa. La sua assenza è una grande perdita per la comunità. Non so cosa l'abbia spinta a sparire, ma non ho dubbi: ha dovuto affrontare prove ingiuste, e il maligno non è rimasto con le mani in mano.\nA volte giungono voci che sia stata vista in città, ma nulla di più. Non ci resta che affidarci alla volontà del Signore e sperare che un giorno torni e trovi di nuovo conforto sotto la protezione della chiesa.";
			link.l1 = "Forse conoscete qualcuno che potrebbe raccontarmi di più su di lei?";
			link.l1.go = "LFD_Church_1_2";
			DelLandQuestMark(npchar);
		break;

		case "LFD_Church_1_2":
			dialog.text = ""+GetSexPhrase("Figlio mio","Figlia mia")+", dimmi, perché cerchi Marisa? So che di tanto in tanto viene cercata da persone il cui aspetto è lontano da quello di un giusto. Il mondo è pieno di tentazioni, e non tutti quelli che la cercano sono mossi da buone intenzioni. Prima di dire una parola, devo essere sicuro che non porterai sventura né a lei né a chi le sta vicino.";
			link.l1 = "Comprendo le vostre preoccupazioni, padre, ma vi assicuro che non ho cattive intenzioni. Voglio solo consegnarle una lettera che ha impiegato troppo tempo per arrivare al destinatario. Chissà, forse contiene qualcosa d'importante per lei. Guardate.";
			link.l1.go = "LFD_Church_1_3";
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Consegnata: Lettera per Marisa Caldera", "None");
		break;

		case "LFD_Church_1_3":
			dialog.text = "Sì, pare che questa lettera abbia affrontato molte tempeste prima di giungere a te. Chi può dire cosa contenga e quali conseguenze porterà... Ma tu agisci con nobiltà, capitano, restituendola alla destinataria. Se qualcuno può sapere dov'è Marisa adesso, è la sua amica Dolores Moño – l’unica di cui si fidava.\nLa sua casa si trova a sinistra dell’ufficio del porto. Spero solo che questa lettera non porti nuovi tormenti a Marisa: ne ha già avuti abbastanza.";
			link.l1 = "Grazie, padre. Che il Signore vi protegga.";
			link.l1.go = "LFD_Church_1_4";
			GiveItem2Character(PChar, "LFD_letter");
		break;

		case "LFD_Church_1_4":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Church_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
