// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Come posso aiutarti?","Cosa posso fare per te?"),"Dimmi, cosa ti preoccupa, "+GetAddress_Form(NPChar)+"?","Per la terza volta, "+GetAddress_Form(NPChar)+", di cosa hai bisogno?","Ne ho abbastanza di te. Vattene!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea, le mie scuse.","Non è niente, mi scusi."),"Perdonami, non è niente.","Hai ragione, è già la terza volta. Perdonami...","Scuse.",npchar,Dialog.CurrentNode);		
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "graveyard" && !CheckAttribute(npchar, "quest.caleuche"))
			{
				link.l1 = "Ascolta, hai visto o incontrato un uomo di nome Joachim Merriman, qui a L'Avana o nelle vicinanze? È un signore di mezza età, portoghese con baffi, barba imperiale e occhi penetranti. Forse in una caletta o nella giungla? Lo sto cercando.";
				link.l1.go = "caleuche";
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "N-no, marinaio, c-certo che no. Ricevo raramente visitatori qui sotto, vedi, uh... e io... Io n-non ho visto nessuno come l'uomo che hai descritto, quindi...";
			link.l1 = "Davvero? Allora perché stai balbettando e nascondendo i tuoi occhi? Non mentire ora, conosci la verità. Meglio che mi dici di nuovo - hai visto quell'uomo?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "I-Io ti sto dicendo, Signore, non h-ho visto nessuno! Ho b-balbettato d-dal momento in cui ero un b-bambino...";
			link.l1 = "Bugie, tutte bugie. Lo vedo nei tuoi occhi. Dove si trova, dove si trova Merriman?! Dimmelo, SUBITO!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Non conosco nessun Merriman! Non ho mai sentito nemmeno quel nome prima! E non cercare di farmi del male o il Comandante ti impiccherà nel forte! Quindi cammina con attenzione, ragazzo!";
			link.l1 = "Oh, la pensi così? Bene. Ora, ascoltami molto attentamente: Joachim Merriman è un stregone. La Sacra Inquisizione lo sta cercando. Molti anni fa in Europa, fu condannato a bruciare sul rogo per aver profanato tombe, disonorato i morti e praticato stregoneria. E so con certezza che ora si nasconde da qualche parte, qui, alla periferia dell'Avana...";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "...";
			link.l1 = "...recentemente ho liberato la grotta nelle vicinanze dagli zombi e so chi è il responsabile! Certamente, dove altro andrebbe Merriman, se non al cimitero! Tu sai dove si trova. Ma fa' come ti pare, non ti toccherò un capello, ma farò una visita agli Inquisitori a Santiago. Padre Vincento troverà molto intrigante che Joachim Merriman si nasconda nel cimitero di L'Avana con il suo complice, il guardiano locale...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "...";
			link.l1 = "...Il colore è già sparito dal tuo viso? Ti do la parola di un nobile: Un giorno dopo che riporterò le mie scoperte, tutta l'Isola brulicherà di soldati spagnoli. E tu sarai allungato su un rack, supplicando e piangendo finché non rivelerai dove si nasconde quel Mago. Non più tardi di allora sarai bruciato al rogo come suo complice mentre io guardo l'auto-da-fe. Ti piacerebbe?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "P-per favore, signore! Non ho partecipato a nulla di tutto questo, lo giuro! Io... Io non potevo fare nulla... Come avrei potuto oppormi a lui?! È un uomo terribile, può... non hai idea di cosa sia capace! Pietà, ti supplico!";
			link.l1 = "Fidati di me, so cosa può fare. L'ho visto con i miei stessi occhi. Allora? Dov'è? Dimmi e ti prometto che non ti coinvolgerò in questa faccenda.";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Lui... Lui si nasconde in una grotta sotto il cimitero. Si può arrivare lì solo attraverso la porta della cappella. Quando esce, mi nascondo in casa mia e rimango lì. Non hai idea di quanto vorrei liberarmi di quell'orrore!\nMa non oserei nemmeno avvicinarmi. Io... Ho visto lui scavare una tomba fresca, e poi... poi l'uomo morto si è alzato e ha camminato per il cimitero al chiaro di luna! Ho quasi perso la mia sanità mentale allora! Ma Merriman mi ha vietato di partire. Mi ha minacciato che se avessi lasciato la mia casa senza il suo permesso anche per mezza giornata, mi avrebbe trovato e trasformato in quell'abominio... uno scheletro che cammina!";
			link.l1 = "Quanto spesso lascia la sua grotta?";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "Ebbene, gli porto cibo e pozioni curative dalla città e... qualsiasi altra cosa lui richieda. Se ne va una o due volte al mese... quando la luna è piena. Lascia un biglietto alla porta, scrive ciò di cui ha bisogno... Io-i lo consegno e lo metto alla porta, e lui lo prende una volta tornato.";
			link.l1 = "Capisco. Quella porta per il suo covo - è in qualche modo chiusa a chiave?";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			dialog.text = "È così. È sempre chiuso a chiave. È molto robusto e il lucchetto è massiccio e complesso.";
			link.l1 = "Mh... Merriman non è un idiota, sicuramente deve avere un'altra uscita dal suo covo, come la sua casa in Europa. Se tentassimo di forzare la porta, lui scapperebbe, per non essere mai più trovato. Mmmm...";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "Signore, giurerai di non consegnarmi all'Inquisizione?";
			link.l1 = "Ti ho dato la mia parola, e la parola di un nobile è sacra. Giuro che non ti consegnerò.";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "Oh benedica te, Signore! So come arrivare alla grotta. C'è una chiave, una seconda chiave... L'ho io. Merriman non sa che ci sono due chiavi per quel lucchetto. Non oserei mai entrare, ma tu...";
			link.l1 = "Dammi la chiave, e ti libererò da questo incubo.";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			GiveItem2Character(pchar, "kaleuche_key");
			ChangeItemDescribe("kaleuche_key", "itmdescr_kaleuche_key_crypt");
			dialog.text = "Ecco a te, Signore. Stai davvero entrando nel suo covo?";
			link.l1 = "Sì, sono io. Rinchiuditi in casa tua e aspetta lì quando entro. Se non dovessi tornare, lascia tutto e scappa il più velocemente possibile.";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "Ma fai attenzione, Signore. Da quella caverna si sono sentiti suoni spaventosi e ho paura di pensare anche solo a chi potrebbe abitarla. Ma una cosa è certa - Merriman non è solo.";
			link.l1 = "Prenderò tutte le misure possibili. Addio.";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			DialogExit();
			AddQuestRecord("Caleuche", "30");
			pchar.questTemp.Caleuche = "merriman";
			pchar.quest.caleuche_merriman_cave.win_condition.l1 = "locator";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.location = "Havana_CryptBig2";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator_group = "reload";
			pchar.quest.caleuche_merriman_cave.win_condition.l1.locator = "reload2";
			pchar.quest.caleuche_merriman_cave.function = "Caleuche_OpenMerrimanCave";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1 = "location";
			pchar.quest.caleuche_merriman_cave1.win_condition.l1.location = "Havana_CryptDungeon";
			pchar.quest.caleuche_merriman_cave1.function = "Caleuche_InMerrimanCave";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Caleuche_MerrimanCaveOver", 0, 0, 3, false); // таймер
			npchar.quest.caleuche = "true";
			// логово Мерримана
			int n = Findlocation("Havana_CryptDungeon");
			locations[n].id.label = "Merrimancave";
		break;
	}
	UnloadSegment(NPChar.FileDialog2); 
}
