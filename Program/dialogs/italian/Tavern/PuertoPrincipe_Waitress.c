// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Domande, "+GetAddress_Form(NPChar)+"?","Come posso aiutarti, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Ehm, qual è la grande idea, "+GetAddress_Form(NPChar)+"? ","Di nuovo con le strane domande? Bella, vai a bere un po' di rum o qualcosa del genere...")+"","Durante tutto il giorno, questa è la terza volta che parli di qualche domanda..."+GetSexPhrase("Questi sono alcuni segni di attenzione?","")+"","Altre domande, presumo, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea","Non ho nulla di cui parlare al momento."),"No, no bella...","Assolutamente no, cara...","No, quali domande?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_2"))
			{
				link.l1 = "Devo farti alcune domande. Lavoravi nella taverna il giorno in cui è scomparso il barile di gin, vero? Cosa mi puoi dire sugli avvenimenti di quel giorno?";
				link.l1.go = "OS_Tavern2_1";
			}
			//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern2_1":
			dialog.text = "Io... Io non so cosa dire. Tutto era normale, niente fuori dall'ordinario.";
			link.l1 = "Davvero? Niente di strano? E quel marinaio del 'Lupo di Mare' che ti importunava? Sembrava convinto che avresti apprezzato la sua compagnia per la notte.";
			link.l1.go = "OS_Tavern2_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern2_2":
			dialog.text = "Oh, lui! Lui... lui ha solo bevuto un goccio di troppo, tutto qui. Succede spesso qui, sai. Certamente non l'ho incoraggiato, ma ha iniziato a fare avances. Quindi l'ho messo al suo posto.";
			link.l1 = "Nessun incoraggiamento? Lui racconta una storia diversa. Perché hai fatto tanto rumore questa volta, ma non in altre occasioni?";
			link.l1.go = "OS_Tavern2_3";
		break;

		case "OS_Tavern2_3":
			dialog.text = "Io... Io non so cosa altro dirti! Veramente non so nulla! Ero... Ero alla vista di tutti tutta la sera! Non ho visto niente, non ho sentito niente! E riguardo al barile... Non sono a conoscenza di cosa gli sia successo! Perché questo interrogatorio? Stavo solo... solo facendo il mio lavoro come sempre!";
			link.l1 = "Sospetto che tu stia nascondendo qualcosa. Una notte nella stiva della nave senza luce o cibo fa miracoli sulla memoria di uno. Vuoi scoprirlo? O preferisci avere una conversazione decente?";
			link.l1.go = "OS_Tavern2_4_HO";
			link.l2 = "Credo che tu sappia molto più di quanto stai facendo vedere. Hai un'opportunità rara ora — dimmi tutto, e terrò per me il tuo ruolo in questo piccolo teatro. Ma se rimani silenzioso — sarà peggio per te. Scoprirò la verità con o senza il tuo aiuto.";
			link.l2.go = "OS_Tavern2_4_harizma";
		break;

		case "OS_Tavern2_4_HO":
			dialog.text = "I... I... Ti dirò tutto! È stato tutto il mio... pretendente, Jack. Jack Veils! Mi ha persuasa a sedurre qualsiasi marinaio della 'Sea Beast'. E quando lui avrebbe fatto le sue avances, dovevo causare una scena per attirare l'oste da dietro il bancone. Quando il tumulto cominciava a calmarsi, due marinai avrebbero iniziato una rissa per tenerlo occupato nella sala principale. È esattamente quello che è successo\nDurante quel tempo, il capitano della 'Sea Beast' è riuscito a rubare il barile. Questo... questo è tutto quello che so, "+GetSexPhrase("signore","signora")+"! Per favore, non mi denunciare! Io solo... Io solo... Volevo semplicemente... che Jack finalmente mi trattasse con un po' di rispetto! Dopotutto l'ho aiutato...";
			link.l1 = "Hai aiutato un uomo mentre ne lanciavi un altro ai lupi senza esitare un attimo?! Comunque, mantengo la mia parola - non rivelerò il tuo ruolo in tutto questo. Ma dovrai vivere con ciò che hai fatto! La tua insensatezza avrebbe potuto mettere il locandiere in grave pericolo. Dove posso trovare questo tuo Jack? E ricorda: mentimi, e tornerò. Credimi, non ti piacerà la mia seconda visita.";
			link.l1.go = "OS_Tavern2_5";
			AddComplexSelfExpToScill(40, 40, 40, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;

		case "OS_Tavern2_4_harizma":
			dialog.text = "Io... Io... Ti dirò tutto! E' stato tutto merito del mio... pretendente, Jack. Jack Veils! Mi ha convinto a sedurre qualsiasi marinaio della 'Sea Beast'. E quando lui avrebbe fatto le sue avances, avrei dovuto causare un trambusto per attirare il gestore della taverna fuori dal bancone. Quando l'agitazione iniziava a placarsi, due marinai avrebbero iniziato una rissa per mantenerlo occupato nella sala principale. E' esattamente quello che è successo\nDurante quel tempo, il capitano della 'Sea Beast' è riuscito a rubare il barile. Questo è... questo è tutto quello che so, "+GetSexPhrase("signore","signora")+"! Per favore, non mi denunciare! Io solo... Stavo solo... Volevo semplicemente... che Jack finalmente mi trattasse con un po' di rispetto! Dopotutto l'ho aiutato...";
			link.l1 = "Hai aiutato un uomo mentre gettavi un altro ai lupi senza un attimo di esitazione?! Tuttavia, mantengo la mia parola: non rivelerò il tuo ruolo in tutto questo. Ma dovrai vivere con quello che hai fatto! La tua insensatezza avrebbe potuto mettere il locandiere in grave pericolo. Dove posso trovare questo tuo Jack? E ricorda: mentimi, e tornerò. Credimi, non ti piacerà la visita di ritorno.";
			link.l1.go = "OS_Tavern2_5";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "OS_Tavern2_5":
			dialog.text = "Non mi rendevo conto che fosse così grave! È solo un barile dopo tutto... Jack vive dall'altra parte della strada. Affitta la casa lì, io... io non so nient'altro! Per favore, perdonami! Capitano, giuro che non farò mai più nulla del genere!";
			link.l1 = "Torna ai tuoi doveri, e non osare metterti a piangere — il locandiere non deve sospettare nulla.";
			link.l1.go = "OS_Tavern2_6";
		break;
		
		case "OS_Tavern2_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_2");
			AddQuestRecord("OS", "4");
			
			//
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.cask_gin = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.map_full = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.jewelry2 = 10;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.GunPowder = 50;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.bullet = 50;
			
			PChar.quest.OS_Zasada.win_condition.l1 = "item";
			PChar.quest.OS_Zasada.win_condition.l1.item = "cask_gin";
			PChar.quest.OS_Zasada.function = "OS_Zasada";
			
			SetFunctionLocationCondition("DWH_Close_House", "PuertoPrincipe_QuestHouse_1", false);
		break;
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
