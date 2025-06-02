// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tutte le voci di "+GetCityName(npchar.city)+" al vostro servizio. Cosa vorreste scoprire?","Ne stavamo proprio parlando. Devi averlo dimenticato...","È la terza volta che mi disturbi ora...","Ripeti sempre le stesse cose come un pappagallo...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, ho dimenticato per qualche motivo...","Sì, è davvero la terza volta...","Sì...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && !CheckAttribute(npchar, "quest.gonsales"))
			{
				link.l1 = "Sto cercando Enrique Gonzales. Potresti dirmi come trovarlo?";
				link.l1.go = "saga";				
			}
		break;
			
		case "saga":
			dialog.text = "Tutti conoscono il Signor Gonzales! La sua casa è accanto all'autorità portuale.";
			link.l1 = "Quanti anni ha?";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "Bhè, non lo so di certo, ma sembra avere almeno cinquanta anni. Vive in quella casa da parecchio tempo. Gli piace raccontare ogni tipo di storie incredibili sui pirati che probabilmente ha incontrato solo nei suoi sogni.";
			link.l1 = "Sembra che lui sia l'uomo di cui ho bisogno. Grazie, "+npchar.name+", sei stato di grande aiuto!";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			DialogExit();
			npchar.quest.gonsales = "true";
			pchar.questTemp.Saga.Gonsales = "true";
			pchar.quest.Saga_Gonsales1.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales1.win_condition.l1.location = "Cartahena_houseF2";
			pchar.quest.Saga_Gonsales1.function = "Saga_CreateGonsalesA";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
