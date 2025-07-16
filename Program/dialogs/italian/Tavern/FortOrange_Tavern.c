// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),"Hai cercato di farmi una domanda non molto tempo fa, "+GetAddress_Form(NPChar)+"...","Durante l'intera giornata, questa è la terza volta che parli di qualche domanda...","Altre domande, presumo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Uhm, dove se ne è andata la mia memoria...","Sì, è davvero la terza volta...","No, quali domande?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "È passato di qui un uomo di nome Francois Gontier? Ho davvero bisogno di lui.";
                link.l1.go = "Jamaica_ratF_1";
            }
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_4")
            {
                link.l1 = "Ascolta compagno, c'è una nave fuori da Port Royal che sta acquistando della seta per il suo cantiere navale... una seta molto speciale, sicuramente ne hai sentito parlare. Dicono che un venditore di tale seta risieda da qualche parte in questo insediamento. Hai qualche indizio su come trovarlo? Ho una proposta commerciale per lui.";
                link.l1.go = "mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_5" && (PCharDublonsTotal() >= 50))
            {
                link.l1 = "Ho cinquanta dobloni con me. Prendili e inizia a parlare.";
                link.l1.go = "mtraxx_4_1";
			}
		break;

		case "Jamaica_ratF_1":
			dialog.text = "Ce l'ha. Aveva affittato una stanza per alcuni giorni. Non il tipo più piacevole, ti dirò. Oltre a questo, era ossessivamente paranoico di essere ricercato. Aveva sempre paura e guardava in giro. Sei l'uomo di cui aveva così paura?";
			link.l1 = "No, non sono io. Sai, i corsari hanno molti nemici. Quindi, dove posso trovarlo? Lui ed io abbiamo deciso di fare un accordo, ma sembra che la terra lo abbia inghiottito.";
			link.l1.go = "Jamaica_ratF_2";
		break;
		
		case "Jamaica_ratF_2":
			dialog.text = "È partito per mare sulla sua nave. Non so dove. Non mi ha messo al corrente di questo.";
			link.l1 = "Ah, che peccato! Dove lo cercherò ora?";
			link.l1.go = "Jamaica_ratF_3";
		break;
		
		case "Jamaica_ratF_3":
			dialog.text = "Non lo so, compagno. Te lo direi se lo sapessi.";
			link.l1 = "Va bene, capisco. Andrò a chiedere ad altre persone...";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_4");
			pchar.questTemp.Slavetrader = "FindRatJamaica_H";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = "Eh, se sospetti del nostro mercante, quello che tiene il negozio, posso dirti che non è lui, non tratta in seta per vele. Nemmeno i contrabbandieri vengono qui, non ne hanno bisogno quando non c'è una dogana. E inoltre nessun altro, tranne il nostro mercante, commercia qui. Dai un'occhiata in giro, non siamo quel tipo di persone, ah-ah!";
			link.l1 = "Ma qualcuno sta fornendo la seta a Port Royal - questo è indiscutibile. Hai qualche indizio su chi potrebbe essere il fornitore?";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Contrabbandieri da Port Royal, forse? O pirati ribelli? Devono scaricare il loro bottino in qualche insenatura nascosta... Ah! Ho un'idea, amico. C'è un locale, sa tutto quello che succede in queste acque. Se non avrà alcuna supposizione, allora non ci sono mercanti di seta.";
			link.l1 = "Splendido! Come si chiama il ragazzo?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Mh... Sto cercando di ricordare il suo nome ma per qualche motivo non mi viene in mente...";
			link.l1 = "Che ne dici di qualche moneta per aiutare la tua memoria?";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Immagino che potrebbe aiutare... Cinquanta dobloni d'oro illumineranno sicuramente questa vecchia testa.";
			if (PCharDublonsTotal() >= 50) // Rebbebion, учёт количества дублонов из рундука
			{
				link.l1 = "Capisco. Ecco, prendi le monete.";
				link.l1.go = "mtraxx_4_1";
			}
			else
			{
				link.l1 = "Capisco. Tornerò...";
				link.l1.go = "mtraxx_4_2";
			}
		break;
		
		case "mtraxx_4_1":
			RemoveDublonsFromPCharTotal(50);
			PlaySound("interface\important_item.wav");
            dialog.text = "Burbero Billy è l'uomo di cui hai bisogno. Vive in Jamaica da sempre, conosce ogni cane per strada. Era un pirata e un tormento per i britannici fino a quando non è stato ferito circa tre anni fa. Ora pesca per lo più, caccia gli squali e raccoglie ambra nelle baie della Jamaica. Lascia la sua vecchia barca a vela lunga solo per comprare più rum e cracker\nDovresti cercarlo nelle acque intorno alla Jamaica. Dicono che stia navigando sul lato nord, fino al punto più a est. Ma inseguire una barca a vela lunga è un'impresa da folli, sarebbe meglio che ti apposti intorno all'angolo sud-ovest, dicono che è stato visto vicino a Capo Negril circa una volta a settimana. La sua barca di vongole si chiama 'The Fly Fish'.";
			link.l1 = "Grazie, compagno. Hai guadagnato il tuo oro.";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "Buona fortuna, compagno! Spero che tu trovi quello che stai cercando!";
			link.l1 = "...";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_4_2":
            DialogExit();
			AddQuestRecord("Roger_2", "6");
			pchar.questTemp.Mtraxx = "silk_5";
		break;
		
		case "mtraxx_6":
            DialogExit();
			AddQuestRecord("Roger_2", "7");
			pchar.questTemp.Mtraxx = "silk_6";
			/*pchar.quest.mtr_negril.win_condition.l1 = "Timer";
			pchar.quest.mtr_negril.win_condition.l1.date.hour  = 12+rand(12);
			pchar.quest.mtr_negril.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2+rand(3));*/
			PChar.quest.mtr_negril.win_condition.l1 = "ExitFromLocation";
			PChar.quest.mtr_negril.win_condition.l1.location = PChar.location;
			pchar.quest.mtr_negril.function = "Mtraxx_CreateBilly";
			SetFunctionTimerCondition("Mtraxx_BillySeaTimeOver", 0, 0, 7, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
