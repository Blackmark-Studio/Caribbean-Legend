// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti?"),"Hai provato a farmi quella domanda poco tempo fa...","Sì, lascia che indovini... Ancora una volta a girare in cerchio?","Ascolta, io gestisco le finanze qui, non rispondo alle domande...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto...","Non ho nulla di cui parlare al momento."),"Umph, dove se n'è andata la mia memoria...","Hai indovinato, mi dispiace...","Capisco...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит, Голландия
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				link.l1 = "Signore, sono il capitano "+GetFullName(pchar)+", e sono qui per un incarico da parte di Lucas Rodenburg. Ho un pacco per te da parte sua.";
				link.l1.go = "SantiagoTripBank";	
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripReturn")
			{
				link.l1 = "Sono venuto per la risposta del signor Lucas Rodenburg.";
				link.l1.go = "SantiagoTripBank_3";	
			}
			//Голландский гамбит, Голландия
		break;
		
		case "SantiagoTripBank":
			if (GetCharacterItem(pchar, "Chest") >= 5)
			{
			dialog.text = "Solo immagina... un pacco! Beh, dammelo, signore.";
			link.l1 = "Inoltre, il Signor Rodenburg ha chiesto di trasferirti questo...";
			link.l1.go = "SantiagoTripBank_1";
			RemoveItems(PChar, "NPC_Letter", 1);
			RemoveItems(PChar, "Chest", 5);
			DelLandQuestMark(npchar);
			}
			else
			{
			dialog.text = "Per quanto ne so, dovevo ricevere qualcos'altro oltre al pacco, capitano. Quindi... dov'è? Capisci di cosa sto parlando?";
			link.l1 = "Ma certamente! Le casse sono sotto stretta sorveglianza sulla mia nave. Te le consegnerò immediatamente.";
			link.l1.go = "exit";
			}
		break;
		
		case "SantiagoTripBank_1":
			dialog.text = "Hm-m... interessante. Quindi 'manda i suoi rimpianti'. Beh-beh. Anche se, i rimpianti del signor Rodenburg sono piuttosto convincenti, è difficile negarlo. Signore, ci vorrà del tempo per scrivere una risposta adeguata, potrebbe tornare a trovarmi domani intorno a mezzogiorno per poter prendere una risposta? Riposati in una taverna, fai un giro per la città. Santiago ha molto da offrire.";
			link.l1 = "Bene, tornerò verso mezzogiorno domani. Ci vediamo allora, signore.";
			link.l1.go = "SantiagoTripBank_2";
		break;
		
		case "SantiagoTripBank_2":
			DialogExit();
			pchar.quest.SantiagoTripOver.over = "yes"; //снять таймер
			bDisableFastReload = true;
			pchar.quest.Santiago_Trip.win_condition.l1 = "location";
			pchar.quest.Santiago_Trip.win_condition.l1.location = "Santiago_town";
			pchar.quest.Santiago_Trip.function = "SantiagoTrip_Attack";
			pchar.questTemp.HWIC.Holl = "SantiagoTripAttack";
			LAi_LocationDisableOfficersGen("Santiago_town", true);//офицеров не пускать // 291112
		break;
		
		case "SantiagoTripBank_3":
			dialog.text = "Sì, certamente... ma credo che possiamo andare d'accordo senza formalità scritte. Ditegli semplicemente queste parole 'quest'uomo deve morire'. Sarebbe equo e non avremmo problemi a considerare il 'valore' delle scuse ricevute. E l'incidente sarà considerato completamente risolto.";
			link.l1 = "Bene, mi ricorderò di questo, signore. Qualcos'altro?";
			link.l1.go = "SantiagoTripBank_4";
			DelLandQuestMark(npchar);
		break;
		
		case "SantiagoTripBank_4":
			dialog.text = "Sì, certo. Quello che ho detto è la volontà della famiglia Giraldi. E ovviamente, puoi trasmettere i miei migliori auguri al Signor Lucas. Ti auguro un vento favorevole, capitano "+GetFullName(pchar)+".";
			link.l1 = "Capisco. Addio, signore "+npchar.name+".";
			link.l1.go = "SantiagoTripBank_5";
		break;
		
		case "SantiagoTripBank_5":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "SantiagoTripFinal";
			LAi_LocationDisableOfficersGen("Santiago_town", false);//офицеров пускать // 291112
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
