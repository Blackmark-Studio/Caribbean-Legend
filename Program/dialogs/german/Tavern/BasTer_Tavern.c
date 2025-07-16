// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Fragen haben Sie?","Wie kann ich Ihnen helfen, "+GetAddress_Form(NPChar)+"?"),"Was ist los, "+GetAddress_Form(NPChar)+"..., Freund.","Das ist jetzt das dritte Mal, dass du mich belästigst...","Noch mehr Fragen, nehme ich an?","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert...","Ich habe im Moment nichts zu besprechen."),"Umph, wo ist mein Gedächtnis hin...","Ja, es ist wirklich das dritte Mal...","Nein, welche Fragen?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "Ich suche meinen alten Kameraden Fernand Luc. Ich habe ein paar Fragen an ihn. Ich habe gehört, dass er vor einer Woche hier eine wirklich gute Zeit hatte ...";
				link.l1.go = "terrapin";
			}
			//Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerTavern"))
			{
				link.l1 = "Mein Freund und ich haben uns hier verabredet, aber ich sehe ihn nirgendwo. Weißt du, wo er hingegangen ist? Ist er noch in der Stadt, oder zumindest auf der Insel? Sein Name ist Longway - er ist Chinese.";
				link.l1.go = "PZ_BasTerTavern_1";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_2"))
			{
				link.l1 = "Gute Nachrichten, "+npchar.name+". Ich habe genau das, was Ihre Situation retten kann. Hundert Flaschen erstklassigen Weins und hundert Flaschen Rum. Mit so einer Lieferung werden Ihre Gäste wieder in Strömen trinken. Sind Sie bereit, tief in die Tasche zu greifen?";
				link.l1.go = "TPZ_Tavern2_1";
			}

			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_3"))
			{
				link.l1 = "Nun, "+npchar.name+", sind Sie bereit, die Bedingungen des Geschäfts zu besprechen?";
				link.l1.go = "TPZ_Tavern2_11";
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Tavern_4"))
			{
				link.l1 = "Also, "+npchar.name+". Von meiner Seite ist alles geregelt und die Ware ist bereits auf dem Weg zur Taverne. Wollen wir zur Bezahlung übergehen?";
				link.l1.go = "TPZ_Tavern3_1";
			}
			//<-- Торговля по закону
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "Er könnte immer noch Spaß haben, während er in der Hölle ist. Ihr Kumpel ist tot, also sind Sie ein klein wenig zu spät, Kapitän. Der Mann dort drüben am fernsten Tisch hat für seine Beerdigung bezahlt, obwohl ich das Gefühl habe, dass er derselbe Mann ist, der sie verursacht hat. Er hat ein Hängergesicht, wie man so sagt. Sein Name ist Robert Martene. Wenn Sie möchten, können Sie rübergehen und ihn selbst fragen. ";
			link.l1 = "Danke, Kumpel. Ich werde ein Gespräch mit Monsieur Robert führen. Wir werden auf die Seele des armen alten Luc trinken, damit seine Seele in Frieden ruhen kann...";
			link.l1.go = "terrapin_1";
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_1":
			DialogExit();
			AddQuestRecord("Terrapin", "4");
			pchar.questTemp.Terrapin = "rober";
		break;
		
		// Sinistra - Квест "Длинные тени старых грехов" ==>
		case "DTSG_BasTerTavern_1":
			dialog.text = "Was gibt es da zu besprechen? Er hat dich und deinen Freund angegriffen, ihr habt zurückgeschlagen, ich sehe das fast jeden Tag. Gute Arbeit. Jetzt muss ich nur noch das Durcheinander aufräumen...";
			Link.l1 = "Du wirst es aufräumen, ich bin sicher, du bist es mittlerweile gewöhnt. Was weißt du über ihn?";
			Link.l1.go = "DTSG_BasTerTavern_2";
		break;
		
		case "DTSG_BasTerTavern_2":
			dialog.text = "Nicht viel, wirklich. Er ist vor ein paar Tagen aufgetaucht. Es gefiel ihm hier, er hat sogar ein Haus am Stadtrand gemietet. Kam oft vorbei, zahlte regelmäßig. Und, am wichtigsten, er hat sich die ganze Zeit gut benommen, hat nie ein böses Wort zu jemandem gesagt. Ich bin immer noch schockiert, dass er dich und deinen Freund angegriffen hat\nIch dachte, er könnte sich hier für immer niederlassen.";
			Link.l1 = "Auf eine Art hat er das getan. Nun, das ist nicht viel, aber danke dafür, mein Freund. Wir sehen uns.";
			Link.l1.go = "DTSG_BasTerTavern_3";
		break;
		
		case "DTSG_BasTerTavern_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_BasTerTavern");
			LAi_LocationDisableOfficersGen("BasTer_tavern", false);
			SetQuestHeader("DTSG");
			AddQuestRecord("DTSG", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			Return_KnippelOfficer();
			
			PChar.quest.DTSG_BasTerDom.win_condition.l1 = "locator";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.location = "BasTer_town";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.locator_group = "reload";
			PChar.quest.DTSG_BasTerDom.win_condition.l1.locator = "HutFish1";
			PChar.quest.DTSG_BasTerDom.win_condition = "DTSG_BasTerDom";
			
			SetTimerCondition("DTSG_BasTerDom_Timer", 0, 0, 7, false);
			SetTimerCondition("DTSG_Etap2", 0, 0, 14, false);
		break;
		// <== Квест "Длинные тени старых грехов" - Sinistra
		
		// Sinistra - Квест "Путеводная звезда" ==>
		
		case "PZ_BasTerTavern_1":
			dialog.text = "Dieser Name bedeutet mir nichts, und im Allgemeinen lasse ich Leute wie ihn nicht in mein Etablissement, noch habe ich irgendein Interesse an ihnen.";
			Link.l1 = "Gut genug. Also dann, bis später.";
			Link.l1.go = "PZ_BasTerTavern_2";
		break;
		
		case "PZ_BasTerTavern_2":
			DialogExit();
			bDisableLandEncounters = true;
			DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
			DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
			pchar.questTemp.PZ_BasTerTavern2 = true;
			DeleteQuestCondition("PZ_BasTer_Opozdal");
			DelMapQuestMarkIsland("Guadeloupe");
			
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1 = "location";
			PChar.quest.PZ_BasTer_Strazha.win_condition.l1.location = "BasTer_town";
			PChar.quest.PZ_BasTer_Strazha.win_condition = "PZ_BasTer_Strazha";
		break;
		
		// <== Квест "Путеводная звезда" - Sinistra
		
		//--> Торговля по закону
		case "TPZ_Tavern_1":
			dialog.text = "Ach, "+GetAddress_Form(NPChar)+", es ist schlimmer als gedacht. Mein Lieferant aus Antigua hat seine Brennerei verloren – Piratenüberfall, alles bis auf die Grundmauern niedergebrannt. Er sagt, dass es mindestens zwei Monate dauern wird, bevor er wieder Rum oder Wein liefern kann.";
			link.l1 = "Dann finden Sie einen neuen Lieferanten. Sie werden doch nicht zwei Monate lang Däumchen drehen?";
			link.l1.go = "TPZ_Tavern_2";
		break;
		
		case "TPZ_Tavern_2":
			dialog.text = "Einen guten Lieferanten zu finden, ist nicht einfach. Ich habe versucht, mit kleinen Händlern zu verhandeln, aber sie sind unzuverlässig. Manchmal kommt die Ware, manchmal nicht. Ein großer Lieferant dagegen liefert regelmäßig und in guter Qualität.";
			link.l1 = "Wenn es mit gewöhnlichen Lieferanten solche Probleme gibt, vielleicht lohnt sich ein Blick in den Schattenmarkt? Diese Leute liefern zuverlässig und haben immer Ware auf Lager.";
			link.l1.go = "TPZ_Tavern_3";
		break;
		
		case "TPZ_Tavern_3":
			dialog.text = "Sie verstehen doch, "+GetAddress_Form(NPChar)+", die Taverne steht unter ständiger Beobachtung. Ich will keinen Ärger mit den Behörden. Wenn jemand mit gutem Ruf die Ware bringt, sehe ich gern über deren Herkunft hinweg.\nAm Ende zählt doch nur, dass es keine Zweifel von außen gibt. Langfristig arbeite ich aber nur mit ehrlichen und seriösen Händlern zusammen.";
			link.l1 = "Verstehe. Nun gut, vielleicht komme ich später noch einmal vorbei. Jedes Problem lässt sich lösen, wenn man klug herangeht.";
			link.l1.go = "TPZ_Tavern_4";
		break;
		
		case "TPZ_Tavern_4":
			DialogExit();
			AddQuestRecord("TPZ", "2");
			pchar.questTemp.TPZ_ContraInfo = true;
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
		break;
		
		case "TPZ_Tavern2_1":
			dialog.text = "Kapitän, das ist einfach unglaublich! Wie haben Sie das geschafft? Egal. Sagen Sie mir lieber, was Sie für diese prächtige Lieferung Alkohol haben wollen. Und... sind die Papiere in Ordnung?";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Die Papiere? Natürlich ist alles in bester Ordnung. Sie werden sie doch wohl nicht überprüfen wollen?";
				link.l1.go = "TPZ_Tavern2_2";
				notification("Ehrenprüfung bestanden", "None");
			}
			else
			{
				link.l1 = "Die Papiere?";
				link.l1.go = "TPZ_Tavern2_2_badrep";
				notification("Ehre zu niedrig! ("+XI_ConvertString(GetReputationName(40))+")", "None");
			}
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_2");
			DelLandQuestMark(npchar);
		break;

		case "TPZ_Tavern2_2_badrep":
			dialog.text = "Kapitän, verstehen Sie bitte – ich brauche diese Lieferung dringend. Aber meine Freiheit und mein Ruf sind mir nicht weniger wichtig. Der Gouverneur ist gnadenlos zu Schwarzmarktleuten, selbst zu den kleinsten. Wenn man besser über Sie spräche, könnte ich über fehlende Dokumente hinwegsehen, aber im Moment... Sie ziehen zu viel unerwünschte Aufmerksamkeit auf sich.";
			link.l1 = "Scheint, es ist an der Zeit, ein paar gute Taten zu vollbringen. Warten Sie auf mich, ich komme bald zurück.";
			link.l1.go = "exit";
			pchar.questTemp.TPZ_Tavern_3 = true;
		break;
		
		case "TPZ_Tavern2_2":
			dialog.text = "Diesmal will ich Ihnen glauben. Also, wie viel verlangen Sie für diese Lieferung?";
			link.l1 = "Ich möchte dreißig Dublonen für je zehn Flaschen Wein und fünf Dublonen für zehn Flaschen Rum. Insgesamt macht das für hundert Flaschen Rum und hundert Flaschen Wein dreihundertfünfzig Dublonen.";
			link.l1.go = "TPZ_Tavern2_3";
		break;
		
		case "TPZ_Tavern2_3":
			dialog.text = "Bitte, Kapitän! Das ist ja blanker Raub! Ja, meine Lage ist wirklich verzweifelt, aber ich werde trotzdem nicht mit Verlust arbeiten!";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 50)
			{
				link.l1 = "Vielleicht kann ich Ihnen einen Preisnachlass geben. Und noch etwas: ich möchte Ihr fester Lieferant werden. Ich garantiere pünktliche Lieferungen ohne Ausfälle. Ich werde ein Lagerhaus in Basse-Terre mieten, damit Sie Ihre Waren direkt dort abholen können – immer pünktlich und ausreichend bestückt. Der Preis mit Rabatt: zweihundertvierzig Dublonen. Was sagen Sie?";
				link.l1.go = "TPZ_Tavern2_4";
				notification("Prüfung bestanden", SKILL_COMMERCE);
			}
			else
			{
				link.l1 = "Na gut, ich kann den Preis auf zweihundertvierzig Dublonen pro Lieferung senken – ich bin an einer langfristigen Zusammenarbeit interessiert. Ich kann Ihre Bedürfnisse vollständig abdecken und stabile Lieferungen gewährleisten. Was sagen Sie?";
				link.l1.go = "TPZ_Tavern2_7";
				notification("Handelskunst zu niedrig (50)", SKILL_COMMERCE);
			}
		break;
		
		case "TPZ_Tavern2_4":
			dialog.text = "Das ist immer noch mehr, als ich früher bezahlt habe. Aber ich habe meine Lektion gelernt – Stabilität hat ihren Preis. Ich bin einverstanden, aber wissen Sie: ein Fehler, und ich suche mir einen neuen Lieferanten. Ich will verstehen, wofür ich mehr zahle. Und wie wollen Sie das mit den Behörden regeln?";
			link.l1 = "Darum werde ich mich sofort kümmern. Sobald alles geregelt ist, komme ich mit der Ware zurück.";
			link.l1.go = "TPZ_Tavern2_5";
		break;
		
		case "TPZ_Tavern2_5":
			dialog.text = "Bitte beeilen Sie sich. Ich kann es kaum erwarten, die Krüge meiner Gäste wieder zu füllen.";
			link.l1 = "Keine Sorge, ich lasse Sie nicht lange warten.";
			link.l1.go = "TPZ_Tavern2_6";
		break;
		
		case "TPZ_Tavern2_6":
			DialogExit();
			AddQuestRecord("TPZ", "5");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino240 = true;
			
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;

		case "TPZ_Tavern2_7":
			dialog.text = "Das ist trotzdem zu teuer, Kapitän. Dieser Preis liegt über dem meines bisherigen Lieferanten. Selbst wenn ich jetzt zustimme, werde ich in ein paar Monaten wohl wieder zu ihm zurückkehren müssen, wenn die Produktion wieder läuft. Ich sehe keinen Grund, mehr zu zahlen.";
			link.l1 = "Verstehe. Gut. Mein letztes Angebot: zweihundert Dublonen. Wenn das auch nicht akzeptabel ist, hat es keinen Sinn weiterzureden.";
			link.l1.go = "TPZ_Tavern2_8";
		break;
		
		case "TPZ_Tavern2_8":
			dialog.text = "In Ordnung, abgemacht. Zweihundert ist akzeptabel. Aber sagen Sie mir: Wie wollen Sie die Sache mit den Inselbehörden regeln? Wie ich bereits sagte, der Gouverneur ist äußerst wachsam, wenn es um Schmuggel geht. Er lässt keine Geschäfte unter seiner Nase zu.";
			link.l1 = "Ha-ha, darüber lässt sich streiten. Aber keine Sorge – ich werde alle bürokratischen Hürden so schnell wie möglich beseitigen.";
			link.l1.go = "TPZ_Tavern2_9";
		break;
		
		case "TPZ_Tavern2_9":
			dialog.text = "Bitte zögern Sie nicht. Ich kann es kaum erwarten, die Krüge meiner Gäste wieder zu füllen.";
			link.l1 = "Keine Sorge, ich lasse nicht lange auf mich warten.";
			link.l1.go = "TPZ_Tavern2_10";
		break;
		
		case "TPZ_Tavern2_10":
			DialogExit();
			AddQuestRecord("TPZ", "6");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_3");
			AddLandQuestMark(characterFromId("BasTer_Mayor"), "questmarkmain");
			pchar.questTemp.TPZ_guber_1 = true;
			pchar.questTemp.TPZ_Vino200 = true;
		break;
		
		case "TPZ_Tavern2_11":
			if (sti(pchar.reputation.nobility) >= 40)
			{
				dialog.text = "Natürlich, Kapitän! Also, wie viel verlangen Sie für Ihre Lieferung?";
				link.l1 = "Ich möchte dreißig Dublonen für je zehn Flaschen Wein und fünf Dublonen für zehn Flaschen Rum. Insgesamt macht das für hundert Flaschen Rum und hundert Flaschen Wein dreihundertfünfzig Dublonen.";
				link.l1.go = "TPZ_Tavern2_3";
				notification("Ehrenprüfung bestanden", "None");
			}
			else
			{
				dialog.text = "Es tut mir leid, Kapitän, aber Ihr Ruf lässt immer noch zu wünschen übrig.";
				link.l1 = "Verdammt...";
				link.l1.go = "exit";
				notification("Ehrenstufe zu niedrig! ("+XI_ConvertString(GetReputationName(40))+")", "None");
			}
		break;
		
		case "TPZ_Tavern3_1":
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino240"))
			{
				dialog.text = "Natürlich, Kapitän, natürlich! 240 Dublonen, wie vereinbart. Bitte sehr!";
				link.l1 = "Es ist mir eine Freude, mit Ihnen Geschäfte zu machen! Jetzt wird es in der Taverne wieder reichlich Rum und Wein geben.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 240);
			}
			if (CheckAttribute(pchar, "questTemp.TPZ_Vino200"))
			{
				dialog.text = "Natürlich, Kapitän, natürlich! 200 Dublonen, wie vereinbart. Bitte sehr!";
				link.l1 = "Es ist mir eine Freude, mit Ihnen Geschäfte zu machen! Jetzt wird es in der Taverne wieder reichlich Rum und Wein geben.";
				link.l1.go = "TPZ_Tavern3_2";
				AddItems(pchar, "gold_dublon", 200);
			}
			DelLandQuestMark(npchar);
		break;

				case "TPZ_Tavern3_2":
			dialog.text = "Sie sind mein Retter, Kapitän! Ich werde solche Lieferungen alle zwei Wochen erwarten. Ich hoffe, Sie halten sich strikt an Ihre Verpflichtungen. Eine zweite Durststrecke wird meine Taverne nicht überleben...";
			link.l1 = "Machen Sie sich keine Sorgen, "+npchar.name+". Mein Vertreter in der Stadt ist Christian Delouche. Er wird dafür sorgen, dass Ihre Taverne nie an Wein und Rum mangelt.";
			link.l1.go = "TPZ_Tavern3_3";
		break;
		
		case "TPZ_Tavern3_3":
			dialog.text = "Christian? Ich kenne ihn, er ist ein zuverlässiger Mann, aber... Ach, egal. Wenn Sie alles mit den Behörden geregelt haben, denke ich, kann ich ihm vertrauen.";
			link.l1 = "Wunderbar. Nun entschuldigen Sie mich, ich muss noch eine Angelegenheit in dieser Stadt erledigen.";
			link.l1.go = "TPZ_Tavern3_4";
		break;
		
		case "TPZ_Tavern3_4":
			dialog.text = "Kommen Sie öfter bei uns vorbei!";
			link.l1 = "Auf jeden Fall.";
			link.l1.go = "TPZ_Tavern3_5";
		break;
		
		case "TPZ_Tavern3_5":
			DialogExit();
			AddQuestRecord("TPZ", "7");
			DeleteAttribute(pchar, "questTemp.TPZ_Tavern_4");
			
			sld = CharacterFromID("TPZ_Kristian");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
