// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Tutti i rumors di "+GetCityName(npchar.city)+" al vostro servizio. Cosa vorreste scoprire?","Ne stavamo proprio parlando. Devi aver dimenticato...","Questa è la terza volta oggi che parli di qualche domanda...","Ripeti sempre le stesse cose come un pappagallo...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, per qualche motivo ho dimenticato...","Sì, è davvero la terza volta...","Sì...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Sai per caso dove posso trovare Francois Gontier?";
                link.l1.go = "Jamaica_ratP_1";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Ascolta, è arrivato qui in città un alchimista, un medico? È italiano, ha circa trent'anni, si chiama Gino Gvineili. Hai sentito qualcosa a riguardo?";
				link.l1.go = "guardoftruth";
			}
		break;

		case "Jamaica_ratP_1":
			dialog.text = NPCStringReactionRepeat("Non ho la più pallida idea. Non ho mai sentito prima quel nome.","Hai già chiesto di questo e ti ho risposto.","Te l'ho detto, hai già chiesto di quel Gontier.","Ascolta, vattene e smetti di infastidirmi! Hai completamente perso la testa?","block",0,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ebbene, continuerò a cercare.","Mh, suppongo di sì...","Sì, esatto, l'ho chiesto...","Scusa, "+npchar.name+"...",npchar,Dialog.CurrentNode);
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("No, non l'ho fatto. Abbiamo erboristi e medici, ma nessuno con un nome del genere.","È la prima volta che sento un nome così strano. No, l'uomo di cui parli non è mai venuto a trovarci.","Non abbiamo nemmeno un alchimista qui. Abbiamo dei medici, ma nessuno con un nome strano come quello.");
			link.l1 = "Capisco. Che peccato. Continuerò a cercare!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
