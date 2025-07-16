// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Parla, sto ascoltando";
			link.l1 = "Mi sono sbagliato. Addio.";
			link.l1.go = "Exit";
			
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaZalog"))
			{
				link.l1 = "Recentemente, uno dei soldati della città ha arrestato e detenuto Charlie Knippel. È ancora qui?"; 
				link.l1.go = "DTSG_AntiguaZalog_2";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов
		case "DTSG_AntiguaZalog_2":
			dialog.text = "È vero, ma perché chiedi?";
			link.l1 = "La questione è che Charlie è uno dei miei ufficiali. Vorrei sapere di cosa è accusato. I soldati che lo hanno preso non mi hanno detto nulla."; 
			link.l1.go = "DTSG_AntiguaZalog_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaZalog_3":
			dialog.text = "Giusto. Non è di dominio pubblico. Purtroppo, nemmeno per te. È un segreto di stato, signore.";
			link.l1 = "Allora, capisco che la cauzione non è un'opzione?"; 
			link.l1.go = "DTSG_AntiguaZalog_4";
		break;
		
		case "DTSG_AntiguaZalog_4":
			dialog.text = "Esattamente. Capisco che è spiacevole perdere un prezioso membro dell'equipaggio, ma né tu né io possiamo farci nulla. Mi dispiace molto, Capitano.";
			link.l1 = "Niente cauzione, vedo. Allora che ne dici di... un risarcimento? Un risarcimento generoso, aggiungo. Per te e tutti i tuoi uomini, così nessuno viene escluso."; 
			link.l1.go = "DTSG_AntiguaZalog_5";
		break;
		
		case "DTSG_AntiguaZalog_5":
			dialog.text = "Una tangente? Audace da parte tua, Capitano, ma nessuna somma di denaro ci salverà dall'ira di coloro che scopriranno che abbiamo lasciato andare Charlie.";
			link.l1 = "Forse... Ma posso almeno parlare con lui?"; 
			link.l1.go = "DTSG_AntiguaZalog_6";
		break;
		
		case "DTSG_AntiguaZalog_6":
			dialog.text = "Perché no? Non puoi fare nulla per salvarlo o aiutarlo a scappare, quindi... vai avanti. È in una delle celle.";
			link.l1 = "Eh, e se mi dice di cosa è accusato e rivela quel segreto di stato di cui sei così preoccupato, Ufficiale?"; 
			link.l1.go = "DTSG_AntiguaZalog_7";
		break;
		
		case "DTSG_AntiguaZalog_7":
			dialog.text = "Non mi preoccupo di questo. Capirai perché. Vai, parla con il tuo ex ufficiale prima che cambi idea.";
			link.l1 = "Grazie."; 
			link.l1.go = "DTSG_AntiguaZalog_8";
		break;
		
		case "DTSG_AntiguaZalog_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaZalog");
			pchar.questTemp.jailCanMove = true;
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto9");
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Killer", "sold_eng_10", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Killer";
			LAi_SetStayType(sld);
			sld.talker = 5;
			GiveItem2Character(sld, "blade_14");
			EquipCharacterbyItem(sld, "blade_14");
			GiveItem2Character(sld, "pistol4");
			EquipCharacterbyItem(sld, "pistol4");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload12");
			sld.rank = 30;
			SetSelfSkill(sld, 80, 80, 80, 80, 80);
			LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
			LAi_SetImmortal(sld, true);
		break;
		
		case "DTSG_AntiguaTrevoga_2":
			dialog.text = "Non c'è bisogno, Capitano. Come ho detto, saresti stato rinchiuso nella stessa cella con quel pazzo di Charlie. Ma, prima, il Governatore ha apprezzato che non hai resistito all'arresto, e secondo, non era contento della recente visita dell'usuraio, i cui urla hanno quasi infranto le finestre del palazzo...";
			link.l1 = "Ha chiesto il mio arresto?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaTrevoga_3":
			dialog.text = "Non ha chiesto - ha preteso. E Sua Eccellenza non gradisce che gli venga imposto nulla. Pertanto, quel usuraio è stato mostrato alla porta.";
			link.l1 = "Divertente. Ora..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_4";
		break;
		
		case "DTSG_AntiguaTrevoga_4":
			dialog.text = "Ora suggerisco che tu faccia lo stesso, Capitano de Maure. E non fare domande a cui non otterrai risposte.";
			link.l1 = "Non me ne andrò da qui senza Charlie Knippel."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H1";
			link.l2 = "Per favore, signore, lasciatemi parlare con Charlie Knippel. O almeno scoprire cosa..."; 
			link.l2.go = "DTSG_AntiguaTrevoga_Ch1";
		break;
		
		case "DTSG_AntiguaTrevoga_H1":
			dialog.text = "In tal caso, unisciti a lui. Non in una cella, ma nell'aldilà.";
			link.l1 = "Allora, è morto..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H2";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_H2":
			dialog.text = "Sei maledettamente perspicace, Capitano. E spero che tu capisca che non ti dirò chi l'ha fatto o perché.";
			link.l1 = "È così?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_H3";
		break;
		
		case "DTSG_AntiguaTrevoga_H3":
			dialog.text = "Esatto. E ora non mettere alla prova la mia pazienza - prima che ti faccia gettare in una cella per aver ucciso un soldato inglese.";
			link.l1 = "Considerando che non molti escono dalle vostre celle, non vorrei finire lì. Non ti auguro una buona giornata."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_Ch1":
			dialog.text = "Charlie Knippel non parla con nessuno. Forse solo con il Creatore...";
			link.l1 = "È morto?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_Ch2";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_Ch2":
			dialog.text = "La sentenza è stata eseguita. Non posso darti alcun dettaglio. E spero che non insisterai - potrebbe finire male per te. Non solo con una cella. Sono chiaro, Capitano de Mor?";
			link.l1 = "Più che chiaro. Addio."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaTrevoga");
			AddQuestRecord("DTSG", "10");
			CloseQuestHeader("DTSG");
			ChangeCharacterComplexReputation(pchar, "authority", -10);
			AddCrewMorale(Pchar, -30);
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
