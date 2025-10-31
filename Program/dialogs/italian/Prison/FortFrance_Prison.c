// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Parla, sto ascoltando";
			link.l1 = "Mi sono sbagliato. Addio.";
			link.l1.go = "Exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "Ufficiale, ho sentito dire che c'è un uomo di nome Folke Deluc nella vostra prigione. C'è qualcosa che posso fare per liberarlo?";
                link.l1.go = "Sharlie";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "Ufficiale, sono di nuovo qui riguardo al prigioniero Folke Deluc. Ho acquistato i diritti sul suo debito e voglio che quest'uomo venga rilasciato e dato a me. Ecco i suoi documenti di debito, dai un'occhiata.";
                link.l1.go = "Sharlie_3";
			}	
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Deluck"))
			{
				link.l1 = "Buon pomeriggio, ufficiale. Vorrei informarmi sul mio membro dell'equipaggio...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_DeluckSvoboda"))
			{
				link.l1 = "Ecco i documenti, ora rilascia il mio uomo.";
                link.l1.go = "Del_DeluckSvoboda";
			}
			//<-- Миниквест "Делюк"
		break;
		
		//--> Бремя гасконца
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "Ah, quel marinaio? Aveva preso in prestito una somma significativa dal nostro banchiere, non l'ha restituita e ha anche cercato di fuggire. Ma è stato trovato in fretta. Da allora è sotto arresto e resterà qui finché non ripagherà il suo debito.";
			link.l1 = "Mh. E come farà mentre rimane in prigione?";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Non me ne importa, signore.";
			link.l1 = "Divertente... E quanto deve questa povera anima?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Non lo so. Chiedi al banchiere e lui ti darà i dettagli.";
			link.l1 = "Capisco, grazie per le vostre informazioni, ufficiale.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskiper";
			LocatorReloadEnterDisable("Fortfrance_town", "reload8_back", false);
			AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
		break;
		
		case "Sharlie_3":
			Log_Info("Avete consegnato i documenti di debito");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			DelLandQuestMark(npchar);
			dialog.text = "Mh. Sono tutti corretti. Vuoi davvero che io rilasci quel prigioniero?";
			link.l1 = "Sì. Ho bisogno di lui per ripagare il debito e conosco il modo in cui può farlo.";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "Bene, non ho motivi per rifiutarti. Deluc sarà portato qui presto. Ma devo avvertirti che questa volpe scapperà alla prima occasione, quindi non farti illusioni su di lui.";
			link.l1 = "Capisco, ufficiale. E ora voglio prendere il mio debitore.";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Sì, certo. Sergente! Porta avanti il prigioniero! Folke Deluc, sembra che abbia un nuovo padrone ora!";
			link.l1 = "...";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			DialogExit();
			// создаем штурмана
			sld = InitFolke("Folke", "Deluc");
			pchar.questTemp.Sharlie = "takeskiper";	
			ForceHeroAutolevel(sld);
			AddDialogExitQuestFunction("Del_Turma");
		break;
		//<-- Бремя гасконца
		
		//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
		case "Del_Deluck":
			DelLandQuestMark(npchar);
			dialog.text = "Ah! Dico, le chiacchiere sul tuo predicamento divertiranno Saint-Pierre per molto tempo. Ma non prenderla personalmente, Capitano. Sei chiaramente la vittima di sfortuna. Entra e non preoccuparti: il tuo navigatore non sfuggirà da questa conversazione, ah ah!";
			link.l1 = "Divertente. Grazie, ufficiale.";
            link.l1.go = "exit";
			AddDialogExitQuestFunction("Del_prison");
		break;
		
		case "Del_DeluckSvoboda":
			dialog.text = "Capito, Capitano. Procederemo di conseguenza.";
			link.l1 = "...";
			link.l1.go = "Del_DeluckSvoboda_2";
			Log_Info("Avete consegnato i documenti di debito");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "letter_open", 1);
			DelLandQuestMark(npchar);
		break;
		
		case "Del_DeluckSvoboda_2":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Del_DeluckSvoboda");
			
			sld = CharacterFromID("Folke");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_Folke_10";
			
			AddDialogExitQuestFunction("Del_Turma");
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
