// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande, "+GetSexPhrase("mio figlio","mia figlia")+"?","Chiedi pure, sto ascoltando..."),"Sto ascoltando, parla ora, "+GetSexPhrase("mio figlio","mia figlia")+"...","Per la terza volta, "+GetSexPhrase("mio figlio","mia figlia")+", chiedi ciò di cui hai bisogno.","Un religioso ha molto da fare e tu mi stai distrarrendo, "+GetSexPhrase("mio figlio","mia figlia")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto...","Non in questo momento, padre..."),"Non ho nulla da dire, mi scuso.","Chiederò, ma più tardi. Perdonami, padre.","Mi scusi, santo padre...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_pastor"))
			{
				link.l1 = "Santo Padre, desidero parlare della figlia di Thomas Morrison.";
                link.l1.go = "dwh_pastor_1";
			}
			if (CheckAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi"))
			{
				link.l1 = "Santo Padre, Thomas mi ha chiesto di dirvi che accetta il cammino del pentimento, si dedicherà alle buone opere e fornirà alla parrocchia una nuova campana - a qualunque costo.";
                link.l1.go = "dwh_pastor_VD_5";
			}
			// <-- Тёмные воды исцеления
		break;

		// --> Тёмные воды исцеления
		case "dwh_pastor_1":
			dialog.text = "Parla, mio figlio, ti sto ascoltando.";
			link.l1 = "So che sei contrario all'aiuto della zingara per la ragazza. Ma come puoi costringere un padre a rifiutare anche la più piccola possibilità di salvare sua figlia? I suoi metodi possono essere discutibili, ma ha delle conoscenze che potrebbero aiutare.";
			link.l1.go = "dwh_pastor_2";
			DelLandQuestMark(npchar);
		break;

		case "dwh_pastor_2":
			dialog.text = "Mio figlio, solo il Signore può guarire la ragazza. La fede nel Suo piano è ciò che ci guida attraverso le prove. Se Thomas prega con diligenza, segue la parola di Dio e dona generosamente alla chiesa, il Signore ascolterà le sue preghiere e mostrerà misericordia.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Affidabile) Ma anche tu devi ammettere, il Signore agisce attraverso le persone. Cosa succede se la zingara è semplicemente uno strumento della Sua volontà? E se il Suo disegno è così profondo che noi, semplici mortali, non possiamo capire? Il Signore opera in modi misteriosi, non è vero?";
				link.l1.go = "dwh_pastor_VD_1";
				notification("Trustworthy", "Trustworthy");
			}
			else
			{
				link.l1 = "Stai costringendo un padre a guardare sua figlia deteriorarsi, invece di lasciarlo cercare di salvarla. È questa la pietà?";
				link.l1.go = "dwh_pastor_bez_VD_1";
				notification("Ability not unlocked", "Trustworthy");
			}
		break;

		case "dwh_pastor_VD_1":
			dialog.text = "Le tue parole sono sagge, Capitano. Ma ancora, non posso permettere che l'eresia penetri nel cuore del nostro gregge e scuota la fede di uno dei suoi figli più devoti.";
			link.l1 = "Nulla potrebbe scuotere di più la sua fede che perdere sua figlia. Ma se gli permetti di usare tutti i mezzi, anche quelli considerati peccaminosi, la sua fede diventerà più forte, non più debole.";
			link.l1.go = "dwh_pastor_VD_2";
		break;

		case "dwh_pastor_VD_2":
			dialog.text = "Ma... che tipo di esempio darebbe questo al resto della congregazione?";
			link.l1 = "Un esempio che la chiesa non punisce ciecamente, ma guida e conduce verso il vero pentimento. La Scrittura non ci insegna che un pentimento sincero e le buone azioni possono redimere il peccato? Una generosa donazione alla chiesa potrebbe essere il primo passo verso la redenzione.";
			link.l1.go = "dwh_pastor_VD_3";
		break;

		case "dwh_pastor_VD_3":
			dialog.text = "Forse hai ragione, Capitano. Sono disposto a dare a Thomas questa possibilità. Ma sappi questo: se si allontana dal sentiero giusto e perde la sua fede, anche tu ne porterai la responsabilità! Per quanto riguarda le donazioni, la chiesa non ha bisogno di ricchezze, abbiamo ciò di cui abbiamo bisogno. Eccetto... la campana è stata danneggiata durante il raid spagnolo...";
			link.l1 = "Riferirò le tue parole a Thomas. Grazie per il tuo tempo, Santo Padre. Che il Signore ti protegga.";
			link.l1.go = "dwh_pastor_VD_4";
		break;

		case "dwh_pastor_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_11";
		break;

		case "dwh_pastor_bez_VD_1":
			dialog.text = "Questo non è insensibilità, Capitano, questa è fede. Non abbandoniamo il destino della ragazza, lo affidiamo nelle mani del Signore. Se Thomas prega, crede e aspetta umilmente, sono certo che il Signore ascolterà le nostre preghiere e la guarirà.";
			link.l1 = "Sai che perfino i nobili dell'isola, incluso il governatore, hanno usufruito dei servizi della zingara. E non sono scomunicati. Allora perché sei così severo con Thomas?";
			link.l1.go = "dwh_pastor_bez_VD_2";
		break;

		case "dwh_pastor_bez_VD_2":
			dialog.text = "Certo che lo so, mio figlio. Ma sono anime perdute, ancora non toccate dalla vera luce del Signore. Thomas è un pilastro del nostro gregge, uno dei migliori. Permettere al male di minare la sua fede metterebbe in pericolo l'intera chiesa, e non posso permettere un peccato così grave.";
			link.l1 = "Allora rifiuti di dare anche una piccola possibilità? È davvero giusto?";
			link.l1.go = "dwh_pastor_bez_VD_3";
		break;

		case "dwh_pastor_bez_VD_3":
			dialog.text = "Quello che chiami salvezza potrebbe ben portare alla rovina. Parlo per esperienza. Una volta, contro la mia volontà, un guaritore come lei ha curato mia nipote. Una piccola ragazza, è morta in agonia. E solo il Signore sa se la sua anima è stata condannata da quei rituali. Non cercare di convincermi, è inutile.";
			link.l1 = "Molto bene. Se questa è la tua risposta definitiva, non discuterò. Che il Signore ti protegga.";
			link.l1.go = "dwh_pastor_bez_VD_4";
		break;

		case "dwh_pastor_bez_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			
			AddQuestRecord("DWH", "4");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetCitizenType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_6";
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto23");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "dwh_pastor_VD_5":
			dialog.text = "Eccellente, mio figlio. Una nuova campana sarà un simbolo della sua devozione al Signore e alla chiesa. Lascia che faccia ciò che è necessario, ma ricordagli — l'occhio dell'Onnipotente vigila su ogni atto, e nulla sfugge alla Sua volontà.";
			link.l1 = "Così sia, Santo Padre. Addio.";
			link.l1.go = "dwh_pastor_VD_6";
			DelLandQuestMark(npchar);
		break;

		case "dwh_pastor_VD_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_15";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "barmen", "bar1");
			DelLandQuestMark(sld);
		break;
		// <-- Тёмные воды исцеления
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
