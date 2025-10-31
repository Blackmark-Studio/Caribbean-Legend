// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Was für Fragen?","Was möchten Sie?");
			link.l1 = RandPhraseSimple("Ah, ich habe meine Meinung geändert.'","Ich habe im Moment nichts zu sagen.");
		    link.l1.go = "exit";
			// Rebbebion, квест "Путеводная звезда" ==>
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.PZ_Sotta") && !CheckAttribute(npchar, "questTemp.PZ_Lutter"))
			{
				if (rand(1) == 0)
				{
					link.l1 = "Sind Sie zufällig Kapitän Edgardo Sotta begegnet? Können Sie mir etwas über ihn erzählen? Er klingt wie ein Mann, den man kennen sollte.";
					link.l1.go = "Sotta1";
					link.l2 = "Gehen Sie nicht zur Hinrichtung dieses Windbeutels?";
					link.l2.go = "Lutter1";
				}
				else
				{
					link.l1 = "Sagen Sie, haben Sie den Helden des Tages, Kapitän Edgardo Sotta, gesehen? Ich habe ihn leider verpasst. Wie ist er so? Ich kann nicht glauben, dass ein Kaufmann den berüchtigten Schwätzer Matt gefangen hat!";
					link.l1.go = "Sotta1_1";
					link.l2 = "Ich sehe, die ganze Stadt feiert Lutters Gefangennahme, sogar diejenigen, die nie zur See fahren."link.l2.go ="Lutter1_1";
				}
			}
			// <== квест "Путеводная звезда"
			
			//--> Дикая Роза
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "Vor etwa anderthalb Monaten kam ein gewisser Jérôme Sauvernier nach Belize. Er wurde bei einer Schlägerei im 'Glasauge' verletzt, hat aber überlebt. Können Sie mir sagen, wo ich ihn finden kann?";
				link.l1.go = "WildRose_Beliz_Citizen_1";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "Vor ungefähr anderthalb Monaten erschien ein Herr in Belize. Sein Name war Jérôme Sauvernier. Er suchte nach einem anderen Mann – also hat er sicher mit einigen Stadtbewohnern gesprochen. Später wurde er in einer Tavernenprügelei verletzt, hat aber zum Glück überlebt. Können Sie mir sagen, wo ich ihn finden kann?";
				link.l1.go = "WildRose_Beliz_Citizen_2";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "Ich versuche, einen Mann zu finden, der vor etwa zwei Monaten in Belize angekommen ist. Sein Name ist Jérôme Sauvernier. Er suchte nach einem bestimmten Herrn, und ich nehme an, er hat mit den Stadtbewohnern darüber gesprochen...";
				link.l1.go = "WildRose_Beliz_Citizen_3";
			}
			//<-- Дикая Роза
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Glauben Sie, ich arbeite für den Geheimdienst von "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Nun... nein. Leben Sie wohl.";
			link.l1.go = "exit";
			link.l2 = "Haben Sie noch eine andere Frage?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Sehe ich aus wie das Untersuchungsbüro? Ich weiß es nicht, ich weiß gar nichts.";

            link.l1 = "Sie sind ein Wirrkopf! Verschwinden Sie.";
			link.l1.go = "exit";
			link.l2 = "Haben Sie noch eine andere Frage?";
			link.l2.go = "new question";
		break;
		
		// Квест "Путеводная звезда" ==>
		case "Sotta1":
			dialog.text = "Ich habe nicht mit ihm gesprochen, aber ich habe sein Schiff gesehen - eine schwere Galeone. Es ist gefährlich, in diesen Gewässern alleine zu segeln, aber Sotta kommt ohne Eskorte aus.";
			link.l1 = "Wahrscheinlich jagt er jeder Goldmünze nach und spart Kosten, wo er kann. Nun, ich will Sie nicht aufhalten. Guten Tag.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sotta1_1":
			dialog.text = "Ja, es ist schwer zu glauben! Aber schenken Sie nicht allem, was Sie hören, Glauben, Herr. Ich habe ihn gesehen, so klar wie ich Sie jetzt sehe. Es ist gut, dass er Lutter gefangen hat, aber warum diese ganze Kaufmannsmasche? Er verhält sich wie ein Soldat. Ich erkenne das sofort - ein Verwandter von mir hat jahrelang gedient.";
			link.l1 = "Interessant. Nun, jeder hat seine Geheimnisse. Ich sollte besser gehen. Danke für die Informationen.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "Ich habe den Mann bereits gesehen. Es ist schwer zu glauben, dass dies derselbe Pirat sein soll, der unsere Händler jahrelang terrorisierte. Wie hat er überhaupt das Kommando erhalten? Ich sah die Soldaten, die ihn eskortierten - schreiend, weinend, lachend. Ein Wahnsinniger.";
			link.l1 = "Vielleicht waren die Niederlage und die Realität seines bevorstehenden Todes zu viel für ihn. Aber das spielt keine Rolle. Auf Wiedersehen!";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1_1":
			dialog.text = "Ja, und ich feiere auch - eine gute Anzahl meiner Landsleute starb durch seine Hände. Die Unglücklichen verloren einen Vater, einen Bruder, einen Sohn - Sie verstehen, was ich meine. Diese Barbarei dauerte zu lange! Matt muss einer der Piraten mit der größten Glückssträhne der letzten Jahre gewesen sein, wenn Sie mich fragen.";
			link.l1 = "Früher oder später endet die Glückssträhne immer. Bis dann.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		// <== Квест "Путеводная звезда"
		
		//--> Дикая Роза
		case "WildRose_Beliz_Citizen_1":
    		dialog.text = "Kenne ich nicht, mein Herr. Schlägereien in der Taverne sind hier fast alltäglich, und sich an jeden Verletzten zu erinnern – das ist müßig.";
    		link.l1 = "Verstehe, danke. Alles Gute.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen");
			pchar.questTemp.WildRose_Beliz_Citizen_2 = true;
			npchar.quest.WildRose_Vopros;
 		break;
		
		case "WildRose_Beliz_Citizen_2":
    		dialog.text = "Souvernier? Ein Franzose... Ja, da war so einer. Er hat mich angesprochen, aber ich konnte ihm nicht helfen. Danach habe ich ihn nicht mehr gesehen, tut mir leid.";
    		link.l1 = "Danke. Dann werde ich weiter fragen.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2");
			pchar.questTemp.WildRose_Beliz_Citizen_3 = true;
			npchar.quest.WildRose_Vopros;
 		break;
		
		case "WildRose_Beliz_Citizen_3":
			dialog.text = "Mister Jérôme! Natürlich erinnere ich mich an ihn. Er wurde in der Taverne verletzt. Seitdem verlässt er sein Haus kaum – heilt wohl seine Beinwunde aus.";
			link.l1 = "Und wo ist dieses Haus?";
    		link.l1.go = "WildRose_Beliz_Citizen_3_1";
 		break;
		
		case "WildRose_Beliz_Citizen_3_1":
    		dialog.text = "Ganz in der Nähe, beim Hafenamt. Ein Haus mit rotem Dach. Dort werden Sie ihn finden.";
    		link.l1 = "Vielen Dank, Sie haben mir sehr geholfen! Alles Gute!";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3");
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_3_citizen");
 		break;
		//<-- Дикая Роза
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
