// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Avanti, cosa desideri?","Ne stavamo proprio parlando. Devi averlo dimenticato...","Questa è la terza volta oggi che parli di qualche domanda...","Ascolta, questo è un negozio. Le persone comprano roba qui. Non disturbarmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, ho dimenticato per qualche motivo...","Sì, è davvero la terza volta...","Mh, non lo farò...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason --> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Findcloves" && !CheckAttribute(npchar, "quest.Portugal"))
			{
   				link.l1 = "Ascolta, ho bisogno di vestiti eleganti. Costosi, voglio sembrare un vero nobile. Hai qualcosa del genere?";
				link.l1.go = "Portugal_cloves";
			}
			//<-- Португалец
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten")
			{
				link.l1 = "Una galea chiamata 'Admirable' ti ha recentemente portato un carico di pelli. Te lo ricordi?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		//Jason --> Португалец
		case "Portugal_cloves":
			dialog.text = "Vestiti nobili? Certo, ho un set qui: pantaloni, un giubbotto, una camicia di seta e stivali. Costa 20.000 pesos. I vestiti sono di altissima qualità, sono comodi e hanno un look notevole, quindi non accetterò di meno per esso.";
			if (sti(pchar.money) >= 20000)
			{
				link.l1 = "Ottimo! Dammi qui.";
				link.l1.go = "Portugal_cloves_1";
			}
			link.l2 = "Mm... Non ho così tanti soldi al momento.";
			link.l2.go = "Portugal_cloves_nomoney";
		break;
		
		case "Portugal_cloves_nomoney":
			dialog.text = "Allora torna quando avrai i soldi.";
			link.l1 = "Va bene. Tornerò!";
			link.l1.go = "exit";
		break;
		
		case "Portugal_cloves_1":
			AddMoneyToCharacter(pchar, -20000);
			GiveItem2Character(pchar, "suit_1");
			Log_Info("You've received expensive clothing");
			PlaySound("interface\important_item.wav");
			dialog.text = "Eccoti qua.";
			link.l1 = "Grazie!";
			link.l1.go = "exit";
			npchar.quest.Portugal = "true";
			sld = characterFromId("PortugalDoctor");
			sld.dialog.currentnode = "Portugal_doctor_4";
			DelLandQuestMark(characterFromId("Marigo_trader"));
			AddLandQuestMark(characterFromId("PortugalDoctor"), "questmarkmain");
			QuestPointerDelLoc("marigo_town", "reload", "reload6_back");
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		//<-- Португалец
		case "guardoftruth":
			dialog.text = "Sì. È arrivato in orario, ha scaricato la merce, e l'ho pagata come avevamo concordato. Perché chiedi?";
			link.l1 = "Il capitano di quella nave è Gaius Marchais, un mio vecchio conoscente. Quindi sto cercando di trovarlo. Riusciresti a dirmi cosa ha fatto dopo questo? Forse gli hai fornito qualche carico aggiuntivo o ha menzionato dove stava per dirigersi?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Nothing of that. I didn't offer him any freight; he didn't even ask for it. He didn't share his plans for the future with me. I don't even remember all the details, do you know how many people have come in and out of here since that time? He unloaded and sailed off and that's all I can say about him.";
			link.l1 = "Va bene. Comunque, grazie. Tutto il meglio!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "11");
			pchar.questTemp.Guardoftruth = "maarten1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
