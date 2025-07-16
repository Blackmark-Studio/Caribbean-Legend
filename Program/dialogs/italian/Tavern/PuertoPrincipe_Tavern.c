// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),"Hai cercato di farmi una domanda poco tempo fa, "+GetAddress_Form(NPChar)+"...","Durante tutto il giorno, questa è la terza volta che parli di qualche domanda...","Altre domande, presumo?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto...","Non ho nulla di cui parlare al momento."),"Uhm, dove se ne è andata la mia memoria...","Sì, è davvero la terza volta...","No, quali domande?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_1"))
			{
				link.l1 = "Si dice che qualcuno ti abbia privato del tuo prezioso gin. O le voci parlano falsamente?";
				link.l1.go = "OS_Tavern1_1";
			}
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_3"))
			{
				link.l1 = "Buone notizie, "+npchar.name+"! Ho recuperato il tuo barile!";
				link.l1.go = "OS_Tavern3_1";
			}
		//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern1_1":
			dialog.text = "Per le piaghe di Dio, è vero. Che altro hai sentito? Sai qualcosa? Ti supplico, di' che sai dove trovarlo. Se non lo recupero... dovrò fuggire da questa città. Sia con le mie due gambe o in una cassa di pino.";
			link.l1 = "Effettivamente, la tua situazione sembra grave, amico. No, ho solo sentito sussurri della tua sfortuna. Come hai fatto a lasciarti sfuggire un carico così prezioso?";
			link.l1.go = "OS_Tavern1_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern1_2":
			dialog.text = "Maledizione... Che devo dire? Rubato proprio sotto il mio naso! La botte era sicuramente qui la mattina. È arrivata due giorni fa, e per sicurezza, l'ho portata a casa durante la notte. Di mattina, l'ho riportata indietro, nascosta sotto il bancone. Entro sera, era sparita senza lasciare traccia! Nessuno ha visto o sentito nulla.";
			link.l1 = "Beh, dannazione...";
			link.l1.go = "OS_Tavern1_3";
		break;

		case "OS_Tavern1_3":
			dialog.text = "Se avessi anche la più pallida idea, sarei già a caccia. Ma ahimè, nulla - come se quella botte fosse troppo pregiata per questo mondo mortale e i cieli l'abbiano semplicemente reclamata. Pagherò centocinquanta dobloni a chiunque la riporti indietro. Più di così, monterò una targa con il loro nome nella mia taverna in modo che tutti conoscano la loro impresa eroica!";
			link.l1 = "Vedrò cosa posso fare. Torneremo su questa faccenda della targa più tardi. Dimmi invece chi sapeva di questo barile? E chi oltre a te potrebbe essere stato dietro il bancone?";
			link.l1.go = "OS_Tavern1_4";
			link.l2 = "Cento cinquanta dobloni per un barile? Divertente. Ma i tuoi guai non sono i miei. Risolvilo da solo.";
			link.l2.go = "OS_Tavern1_end";
		break;

		case "OS_Tavern1_end":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			CloseQuestHeader("OS");

			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			sld = CharacterFromID("OS_Pirate");
			sld.lifeday = 0;
		break;

		case "OS_Tavern1_4":
			dialog.text = "Praticamente nessuno! Forse solo la mia cameriera, ma è impossibile. La taverna era in gran forma quel giorno - l'equipaggio del 'Lupo di Mare' era tornato dalla caccia con un bel premio. Non ha avuto un momento di riposo, figuriamoci il tempo di intrufolarsi dietro il mio bancone.";
			link.l1 = "Ne sei sicuro?";
			link.l1.go = "OS_Tavern1_5";
		break;

		case "OS_Tavern1_5":
			dialog.text = "Senza dubbio! Lavorare senza sosta non era nel suo temperamento, e verso sera era tesa come una molla. Quando uno dei marinai ha fatto avances, lei ha sollevato un tale trambusto che ha quasi reso sordi tutti i presenti. Ho dovuto abbandonare il mio posto per ripristinare l'ordine. Strano, però - di solito gestisce tali avances con molto più autocontrollo.";
			link.l1 = "È tutto? Nient'altro di insolito quel giorno?";
			link.l1.go = "OS_Tavern1_6";
		break;

		case "OS_Tavern1_6":
			dialog.text = "While I was quelling that first disturbance, another flared up - two sailors came to blows in the far corner. The scuffle didn't last long, though; they appeared to be shipmates, and were quickly separated. After that, everything truly quieted down with nothing further worthy of mention.";
			link.l1 = "Molto bene, inizierò la ricerca. Aspetta. Penso che presto la botte sarà di nuovo sotto il tuo, ehm... occhio vigile.";
			link.l1.go = "OS_Tavern1_7";
		break;
		//<-- Старые счёты
		
		case "OS_Tavern1_7":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_1");
			AddQuestRecord("OS", "2");
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Matros_1", "citiz_31", "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "OS_Matros";
			LAi_SetImmortal(sld, true);
			sld.City = "PuertoPrincipe";
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_town", "goto", "goto14");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "OS_Tavern3_1":
			dialog.text = "L'hai trovato?! Può davvero essere? Capitano, hai salvato la mia stessa vita! Chi c'era dietro? Devo conoscere il nome dello scellerato!";
			link.l1 = "È stato un piano meticolosamente pianificato da un certo Jack Veils, in collaborazione con il capitano del 'Sea Beast'. Hanno arruolato i loro marinai e organizzato una diversione elaborata per distoglierti. Quando hai lasciato il tuo posto, la botte era senza custodia, e se ne sono andati facilmente con essa.";
			link.l1.go = "OS_Tavern3_2";
			DelLandQuestMark(npchar);
			pchar.questTemp.CameraDialogMode = true;
		break;

		case "OS_Tavern3_2":
			dialog.text = "Santo cielo! Jack Veils! Quindi è tornato... E sembra che abbia pensato di riprendere la taverna con metodi così subdoli. Quella volpe non ammette mai la sconfitta!";
			link.l1 = "Allora lui era una volta il proprietario di questo stabilimento? Sii certo, non tramerà di nuovo. L'ho mandato a incontrare il suo Creatore.";
			link.l1.go = "OS_Tavern3_3";
		break;

		case "OS_Tavern3_3":
			dialog.text = "Capitano! Questo è straordinario! Mi hai... mi hai liberato dal costante terrore che offuscava i miei giorni! Sapevo sempre che sarebbe tornato prima o poi... Alcuni anni fa, eravamo rivali per la proprietà di questa taverna, e lui riuscì a superarmi\nMa la gioia della vittoria si rivelò la sua rovina - nel suo eccesso di celebrazione, inconsapevolmente scommise il posto a me a carte. Naturalmente, al mattino, venne correndo, implorando di riprendere la taverna, promettendo qualsiasi cosa e tutto\nMa non sono un completo idiota da accettare tali condizioni. Poi è sparito... Sapevo che non avrebbe lasciato la questione in sospeso. Presagivo che sarebbe tornato un giorno. E ora, quel giorno è arrivato.";
			link.l1 = "Dare credito a chi lo merita – ha eseguito il suo piano con astuzia.";
			link.l1.go = "OS_Tavern3_4";
		break;

		case "OS_Tavern3_4":
			dialog.text = "Aspetta un momento! Come ha fatto a scoprire del barile? Sembra... sembra che sto iniziando a capire! La cameriera! Ecco perché è scappata come un gatto scottato, senza nemmeno un addio. Deve aver sentito dire che ti sei occupato di Jack. Ora tutto torna al suo posto. Capitano, ti sono infinitamente grato, tu...";
			link.l1 = "...";
			link.l1.go = "OS_Tavern3_5";
		break;
		
		case "OS_Tavern3_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_3");
			ChangeShowIntarface();
			
			sld = GetCharacter(NPC_GenerateCharacter("OS_Zaharia", "Marlow", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
			sld.name = GetCharacterName("Zachary");
			sld.lastname = GetCharacterName("Marlow");
			ChangeCharacterAddressGroup(sld, "PuertoPrincipe_tavern", "reload", "reload1");
			TeleportCharacterToPosAy(sld, -1.30, 0.00, -0.67, 1.50);
			sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
			sld.dialog.currentnode = "Zaharia_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
