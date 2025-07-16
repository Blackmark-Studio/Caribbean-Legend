// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Parla, ti sto ascoltando";
			link.l1 = "Mi sono sbagliato. Addio.";
			link.l1.go = "Exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "Sono informato che avete un'epidemia qui, ho ragione?";
				link.l1.go = "Consumption";
			}
		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "Hai ragione, quindi evita di visitare le segrete senza un motivo serio. Perché sei interessato a questo?";
			link.l1 = "Solo per curiosità. Quindi se i miei ragazzi si ubriacheranno troppo, faranno troppo rumore e finiranno qui, dovrei preparare un po' di lino giallo?";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "Purtroppo, signore, non capisco lo scherzo nel caso in cui stesse scherzando. Le segrete sono umide e fredde e conosci il clima. La consunzione è un ospite frequente in queste segrete. Devo anche pagare i miei ragazzi per portare il cibo nelle stanze. Pattugliare lì è considerato come la servitù penale.";
			link.l1 = "Mi dispiace, volevo solo sapere, quanto è grave la situazione?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "Troppo serio. Non abbiamo nemmeno un medico qui, è morto anche lui della maledetta consunzione. Ora solo un medico della guarnigione locale esamina i prigionieri una volta alla settimana. Ma a chi importa di questi vagabondi e criminali?\nLa maggior parte della gente pensa che si siano meritati completamente un tale destino ed è difficile discutere su questo.";
			link.l1 = "La mia conoscenza della medicina è modesta, ma per quanto ne so, la consunzione è pericolosa e mortale, ma non uccide le persone in pochi giorni come qui. Le vittime non dovrebbero soffrire per mesi o addirittura anni?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "Come hai appena menzionato, non sei un medico, quindi parlare delle caratteristiche della malattia potrebbe essere solo... una bugia inventata. Ho solo ripetuto quello che il nostro medico diceva prima che la malattia lo colpisse anche lui. Quindi non capisco la tua curiosità e comportamento cinico. La gente muore qui!";
			link.l1 = "Non hai appena detto che se lo meritavano?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Abbastanza, signore! Credo che tu ed io abbiamo altri affari da fare piuttosto che competere in arguzia. La porta è proprio dietro di te.";
			link.l1 = "Bene, perdonate la mia indelicatezza, sto già andando.";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			DialogExit();
			npchar.quest.Consumption = "true";
			pchar.questTemp.Consumption.Commandant = "true";
			AddQuestRecord("Consumption", "3");
			pchar.quest.Consumption.win_condition.l1 = "location";
			pchar.quest.Consumption.win_condition.l1.location = "PortSpein_houseF2";
			pchar.quest.Consumption.function = "Consumption_CommandantHouse";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
