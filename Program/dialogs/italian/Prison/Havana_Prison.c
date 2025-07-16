// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Parla, sto ascoltando";
			link.l1 = "Mi sono sbagliato. Addio.";
			link.l1.go = "Exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_4")
			{
				link.l1 = "Ufficiale, mi è giunto all'orecchio che un ufficiale della nave 'Cantavro' è detenuto qui. È corretto?";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_8")
			{
				link.l1 = "Sono tornato per informarmi di nuovo su don Lope, ufficiale. Hai già ricevuto i suoi ordini di rilascio?";
                link.l1.go = "Mtraxx_5";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "L'ufficiale di 'Cantavro'? Don Lope Montoro? Sì, è detenuto qui. Che cosa c'entra con te?";
			link.l1 = "Vorrei il permesso di farlo visita.";
			link.l1.go = "Mtraxx_1";
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Lope"), "questmarkmain");
		break;
		
		case "Mtraxx_1":
            dialog.text = "Chiedo scusa, ma su quali basi?";
			link.l1 = "È solo una questione personale. Lo conoscevo in Europa, e sono rimasto scioccato dalla notizia del suo imprigionamento, e dai pettegolezzi che si sono diffusi in tutta la città. Vorrei parlargli.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
            dialog.text = "Hm...";
			link.l1 = "Ufficiale, forse potrei... 'ringraziarti' per avermi permesso di visitarlo?";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            dialog.text = "Non c'è bisogno di questo. Ti permetto di incontrare don Montoro. Le guardie ti faranno passare.";
			link.l1 = "Grazie!";
			link.l1.go = "Mtraxx_4";
		break;
		
		case "Mtraxx_4":
			DialogExit();
            pchar.questTemp.jailCanMove = true;
			pchar.questTemp.Mtraxx = "jewelry_5";
		break;
		
		case "Mtraxx_5":
            dialog.text = "Infatti, il mio ordine è di consegnare don Lope Montoro direttamente al comandante. Ma immagino che non lascerà la cella per un paio di settimane. Puoi andare a vederlo però, mentre è ancora qui.";
			link.l1 = "Grazie, ufficiale, è per questo che sono qui.";
			link.l1.go = "Mtraxx_6";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtraxx_6":
            DialogExit();
            pchar.questTemp.jailCanMove = true;
			pchar.questTemp.Mtraxx = "jewelry_9";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
