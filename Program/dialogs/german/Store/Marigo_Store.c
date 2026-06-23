// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Mach schon, was willst du?","Wir haben gerade darüber gesprochen. Du musst es vergessen haben...","Das ist das dritte Mal heute, dass du von irgendeiner Frage redest...","Hör zu, das ist ein Laden. Leute kaufen hier Sachen. Stör mich nicht!","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Weißt du, "+NPChar.name+", vielleicht nächstes Mal.","Richtig, ich habe aus irgendeinem Grund vergessen...","Ja, es ist wirklich das dritte Mal...","Hm, ich werde nicht...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason --> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Findcloves" && !CheckAttribute(npchar, "quest.Portugal"))
			{
   				link.l1 = "Hör zu, ich brauche einige schicke Kleider. Teuer, ich möchte wie ein richtiger Edelmann aussehen. Haben Sie so etwas?";
				link.l1.go = "Portugal_cloves";
			}
			//<-- Португалец
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten")
			{
				link.l1 = "Ein Galeon namens 'Admirable' hat Ihnen vor kurzem eine Ladung Häute gebracht. Erinnern Sie sich daran?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		//Jason --> Португалец
		case "Portugal_cloves":
			dialog.text = "Edle Kleidung? Sicher, ich habe hier ein Set liegen: Hosen, eine Wams, ein Seidenhemd und Stiefel. Es kostet 20.000 Pesos. Die Kleidung ist von sehr hoher Qualität, sie sind bequem und haben ein bemerkenswertes Aussehen, also nehme ich nicht weniger dafür.";
			if (int(pchar.money) >= 20000)
			{
				link.l1 = "Großartig! Gib es hier.";
				link.l1.go = "Portugal_cloves_1";
			}
			link.l2 = "Hm... Ich habe im Moment nicht so viel Geld.";
			link.l2.go = "Portugal_cloves_nomoney";
		break;
		
		case "Portugal_cloves_nomoney":
			dialog.text = "Dann komm zurück, wenn du das Geld hast.";
			link.l1 = "In Ordnung. Ich komme wieder!";
			link.l1.go = "exit";
		break;
		
		case "Portugal_cloves_1":
			AddMoneyToCharacter(pchar, -20000);
			GiveItem2Character(pchar, "suit_1");
			Log_Info("You've received expensive clothing");
			PlaySound("interface\important_item.wav");
			dialog.text = "Hier, bitteschön.";
			link.l1 = "Danke dir!";
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
			dialog.text = "Ja. Er kam pünktlich an, entlud die Ware und ich bezahlte dafür, wie wir es vereinbart hatten. Warum fragst du?";
			link.l1 = "Der Kapitän jenes Schiffes ist Gaius Marchais, mein alter Bekannter. Also versuche ich, ihn zu finden. Könnten Sie mir sagen, was er danach getan hat? Vielleicht haben Sie ihm zusätzliche Fracht gegeben oder er hat erwähnt, wohin er gehen wollte?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Nothing of that. I didn't offer him any freight; he didn't even ask for it. He didn't share his plans for the future with me. I don't even remember all the details, do you know how many people have come in and out of here since that time? He unloaded and sailed off and that's all I can say about him.";
			link.l1 = "In Ordnung. Nun, danke trotzdem. Alles Gute!";
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
