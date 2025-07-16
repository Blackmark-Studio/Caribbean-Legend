// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tutte le voci di "+GetCityName(npchar.city)+" al vostro servizio. Cosa vorreste scoprire?","Ne stavamo proprio parlando. Devi aver dimenticato...","Questa è la terza volta oggi che parli di qualche domanda...","Ripeti sempre la stessa cosa come un pappagallo...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, ho dimenticato per qualche motivo...","Sì, è davvero la terza volta...","Sì...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "portprince")
			{
				link.l1 = "Dimmi, una galeone di nome 'Santa Margarita' è passata di recente per la tua colonia? Forse come il premio di un corsaro?";
                link.l1.go = "guardoftruth";
			}
			//--> Украденное воспоминание
			if (CheckAttribute(pchar, "questTemp.UV_DialogCitizen"))
			{
				link.l1 = "Tristan Renier è passato di qui recentemente?";
				link.l1.go = "UV_DialogTavern";
			}
			//<-- Украденное воспоминание
		break;
		
		case "guardoftruth":
			dialog.text = "Compagno, è piuttosto raro che qualcuno passi dalla nostra colonia con dei premi e non abbiamo mai visto un galeone con un nome del genere. Hispaniola è un'isola selvaggia e noi siamo una piccola colonia. È tranquillo qui. Commerciando con i bucanieri nelle montagne per pelli di vacca e carne di manzo secca. Di solito i corsari non si attardano, non abbiamo bordelli qui e abbiamo gli spagnoli nelle vicinanze. Vai a cercare il tuo galeone da qualche altra parte.";
			link.l1 = "Capisco. Grazie per il consiglio!";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "7");
			pchar.questTemp.Guardoftruth = "tortuga";
		break;
		
		//--> Украденное воспоминание
		case "UV_DialogTavern":
			dialog.text = "Renier? Sì, non solo è stato qui, ma l'uomo non se n'è andato. Ha preso una stanza.";
			link.l1 = "La fortuna mi sorride! Il mio affare con il buon capitano non tollera ritardi, la sua privacy deve cedere alla necessità. In quale stanza posso trovarlo?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RoomInTavern");
			DelLandQuestMark(npchar);
		break;
		//<-- Украденное воспоминание

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
