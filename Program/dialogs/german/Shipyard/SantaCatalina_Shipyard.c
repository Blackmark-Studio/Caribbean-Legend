// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Fragen haben Sie?","Wie kann ich Ihnen helfen?"),"Du hast versucht, mir vorhin eine Frage zu stellen...","Ich habe noch nie Menschen mit solcher Neugier in meiner Werft oder sonst wo in dieser Stadt getroffen.","Was ist mit all den Fragen? Meine Aufgabe ist es, Schiffe zu bauen. Lass uns uns darum kümmern.","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe es mir anders überlegt...","Ich habe im Moment nichts zu reden."),"Umph, wo ist mein Gedächtnis hin...","Hm, nun...","Mach weiter...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		
		case "helendrinking_buy_rainbow":
			dialog.text = "... eine würdige Wahl, Herr. Also, haben wir einen Deal?";
			link.l1 = "J-ja! Prost! Verpackt es und schickt es zum Pier. Und macht schnell, eine Dame wartet auf mich auf der Straße!";
			link.l1.go = "helendrinking_buy_rainbow_1";
			locCameraFromToPos(0.36, 1.86, 1.15, true, 2.06, -0.20, -4.38);
		break;
		
		case "helendrinking_buy_rainbow_1":
			dialog.text = "Fünfzigtausend Silber für alles, Herr.";
			if (int(pchar.money) >= 55000) {
				link.l1 = "W-wie viel sagten Sie? F-fünfzigtausend? Nun, zählen Sie es selbst! Und nehmen Sie weitere fünftausend als Trinkgeld. Los geht's!";
				link.l1.go = "helendrinking_buy_rainbow_yes";
			}
			
			link.l2 = "Nein-nein, ich mag ein reicher, hic! ... Kerl sein, aber ich werde es nicht für so viel nehmen. Nein, Herr! Auf Wiedersehen, Bootsmann.";
			link.l2.go = "helendrinking_buy_rainbow_no";
		break;
		
		case "helendrinking_buy_rainbow_yes":
			dialog.text = "Danke, Herr. Möge sie Ihnen gut dienen!";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddMoneyToCharacter(pchar, -55000);
			pchar.questTemp.HelenDrinking.BoughtRainbow = true;
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
		case "helendrinking_buy_rainbow_no":
			dialog.text = "Ja, verzieh dich, reicher Kerl. Wir haben vor drei Stunden geschlossen.";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToPerlas");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
