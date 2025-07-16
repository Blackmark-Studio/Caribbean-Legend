// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Fragen, "+GetAddress_Form(NPChar)+"?","Wie kann ich Ihnen helfen, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Hm, was soll das, "+GetAddress_Form(NPChar)+"? ","Wieder mit den seltsamen Fragen? Toots, geh und trink etwas Rum oder so...")+"","Über den ganzen Tag hinweg ist dies das dritte Mal, dass du von irgendeiner Frage sprichst..."+GetSexPhrase(" Sind das Zeichen der Aufmerksamkeit?","")+"","Noch mehr Fragen, nehme ich an, "+GetAddress_Form(NPChar)+"?","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert","Ich habe im Moment nichts zu besprechen."),"Nein, nein schön...","Keine Chance, Liebchen...","Nein, welche Fragen?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Старые счёты
			if (CheckAttribute(pchar, "questTemp.OS_Tavern_2"))
			{
				link.l1 = "Ich muss dir ein paar Fragen stellen. Du hast doch an dem Tag gearbeitet, als das Gin-Fass verschwand, oder? Was kannst du mir über das sagen, was hier los war?";
				link.l1.go = "OS_Tavern2_1";
			}
			//<-- Старые счёты
		break;

		//--> Старые счёты
		case "OS_Tavern2_1":
			dialog.text = "Ich... ich weiß nicht, was ich sagen soll. Es war alles wie immer, nichts Ungewöhnliches.";
			link.l1 = "Ach ja? Nichts Ungewöhnliches? Und was ist mit dem Matrosen vom 'Sea Beast', der dir an dem Tag nachgestellt hat? Er schien zu glauben, du wärst bereit, die Nacht mit ihm zu verbringen.";
			link.l1.go = "OS_Tavern2_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Tavern2_2":
			dialog.text = "Ach, der! Er... er hatte einfach zu viel getrunken, das ist alles. Das ist hier keine Seltenheit, wisst Ihr. Ich habe ihm keinen Anlass gegeben, aber er wurde zudringlich. Also habe ich ihn abgewiesen.";
			link.l1 = "Keinen Anlass? Nun, er sieht das offenbar anders. Warum hast du gerade diesmal so laut geschrien, und nicht bei anderen Gelegenheiten?";
			link.l1.go = "OS_Tavern2_3";
		break;

		case "OS_Tavern2_3":
			dialog.text = "Ich... ich weiß nicht, was ich Euch noch sagen soll! Ich weiß wirklich nichts! Ich war... ich war den ganzen Abend über für alle sichtbar! Ich habe nichts gesehen, nichts gehört! Und das Fass... ich habe keine Ahnung, was damit passiert ist! Warum dieses Verhör? Ich habe doch nur... nur wie immer gearbeitet!";
			link.l1 = "Ich glaube, du verschweigst etwas. Weißt du, eine Nacht im Laderaum – ohne Licht und Essen – kann Wunder bewirken. Willst du das ausprobieren? Oder reden wir lieber offen?";
			link.l1.go = "OS_Tavern2_4_HO";
			link.l2 = "Ich glaube, du weißt deutlich mehr, als du sagst. Du hast jetzt eine einmalige Chance – erzähl alles, und ich werde über deine Rolle in diesem Stück schweigen. Wenn du schweigst – wird es nur schlimmer für dich. Ich werde die Wahrheit ohnehin herausfinden.";
			link.l2.go = "OS_Tavern2_4_harizma";
		break;

		case "OS_Tavern2_4_HO":
			dialog.text = "Ich... ich... ich erzähle Euch alles! Es war... mein Geliebter, Jack. Jack Veils! Er hat mich überredet, einen beliebigen Matrosen vom 'Sea Beast' zu verführen. Und sobald der zudringlich wurde, sollte ich eine Szene machen, damit der Wirt hinter dem Tresen hervorkommt. Wenn sich alles beruhigte, sollten zwei Matrosen eine Schlägerei anfangen, um ihn weiter abzulenken. Genau so lief es ab\nWährenddessen hat der Kapitän des 'Sea Beast' das Fass gestohlen. Das... das ist alles, was ich weiß, "+GetSexPhrase("mein Herr","meine Dame")+"! Bitte verratet mich nicht! Ich wollte doch nur... ich wollte nur, dass Jack mich endlich respektiert! Ich habe ihm doch geholfen...";
			link.l1 = "Einem hast du geholfen, und den anderen hast du bedenkenlos ins Verderben geschickt?! Na schön, ich halte mein Wort – ich werde dich nicht verraten. Aber du wirst damit leben müssen! Wegen deiner Dummheit hätte der Wirt ernsthafte Probleme bekommen können. Wo finde ich deinen Jack? Und lüg nicht – ich komme wieder. Und glaub mir, das willst du nicht.";
			link.l1.go = "OS_Tavern2_5";
			AddComplexSelfExpToScill(40, 40, 40, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;

		case "OS_Tavern2_4_harizma":
			dialog.text = "Ich... ich... ich erzähle Euch alles! Es war... mein Geliebter, Jack. Jack Veils! Er hat mich überredet, einen beliebigen Matrosen vom 'Sea Beast' zu verführen. Und sobald der zudringlich wurde, sollte ich eine Szene machen, damit der Wirt hinter dem Tresen hervorkommt. Wenn sich alles beruhigte, sollten zwei Matrosen eine Schlägerei anfangen, um ihn weiter abzulenken. Genau so lief es ab\nWährenddessen hat der Kapitän des 'Sea Beast' das Fass gestohlen. Das... das ist alles, was ich weiß, "+GetSexPhrase("mein Herr","meine Dame")+"! Bitte verratet mich nicht! Ich wollte doch nur... ich wollte nur, dass Jack mich endlich respektiert! Ich habe ihm doch geholfen...";
			link.l1 = "Einem hast du geholfen, und den anderen hast du bedenkenlos ins Verderben geschickt?! Na schön, ich halte mein Wort – ich werde dich nicht verraten. Aber du wirst damit leben müssen! Wegen deiner Dummheit hätte der Wirt ernsthafte Probleme bekommen können. Wo finde ich deinen Jack? Und lüg nicht – ich komme wieder. Und glaub mir, das willst du nicht.";
			link.l1.go = "OS_Tavern2_5";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "OS_Tavern2_5":
			dialog.text = "Ich wusste nicht, dass es so ernst ist! Es ist doch nur ein Fass... Jack wohnt gegenüber. Er mietet ein Haus, ich... ich weiß nichts weiter! Verzeiht mir bitte! Kapitän, ich schwöre, ich werde so etwas nie wieder tun!";
			link.l1 = "Zurück an die Arbeit – und fang bloß nicht an zu heulen, damit der Wirt keinen Verdacht schöpft.";
			link.l1.go = "OS_Tavern2_6";
		break;
		
		case "OS_Tavern2_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.OS_Tavern_2");
			AddQuestRecord("OS", "4");
			
			//
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.cask_gin = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.map_full = 1;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.jewelry2 = 10;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.GunPowder = 50;
			pchar.GenQuestBox.PuertoPrincipe_QuestHouse_1.box1.items.bullet = 50;
			
			PChar.quest.OS_Zasada.win_condition.l1 = "item";
			PChar.quest.OS_Zasada.win_condition.l1.item = "cask_gin";
			PChar.quest.OS_Zasada.function = "OS_Zasada";
			
			SetFunctionLocationCondition("DWH_Close_House", "PuertoPrincipe_QuestHouse_1", false);
		break;
		//<-- Старые счёты
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
