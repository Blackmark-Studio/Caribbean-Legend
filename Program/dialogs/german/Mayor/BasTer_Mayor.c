// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Was wünscht Ihr? Fragt nur.","Ich höre Ihnen zu, was ist die Frage?"),"Es ist das zweite Mal, dass Sie versuchen zu fragen...","Es ist das dritte Mal, dass Sie wieder versuchen zu fragen...","Wann wird es endlich vorbei sein?! Ich bin ein beschäftigter Mann, der an den Angelegenheiten der Kolonie arbeitet und Sie versuchen immer noch, etwas zu fragen!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe meine Meinung geändert...","Nicht jetzt. Falscher Ort und Zeit."),"Wahr... Aber später, nicht jetzt...","Ich werde fragen... Aber ein bisschen später...","Es tut mir leid, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);			  
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "Ich habe eine heikle Angelegenheit für Sie. Vor nicht allzu langer Zeit hat ein Freibeuter dem Pfarrhaus von Basse-Terre ein goldenes Kreuz mit einem Lapislazuli darauf geschenkt. Das Problem ist, dass das Kreuz aus der Pfarrkirche von Santiago gestohlen wurde und ein Geistlicher während des Diebstahls ermordet wurde...";
                link.l1.go = "guardoftruth";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_9_continue" && !CheckAttribute(npchar, "quest.frigate"))
			{
				link.l1 = "Ich bin auf Befehl des Gouverneurs General Philippe de Poincy eingetroffen, um das Kommando über Ihre bewaffnete Fregatte zu übernehmen.";
                link.l1.go = "patria";
			}
			if (CheckAttribute(npchar, "quest.frigate.wait") && GetCompanionQuantity(pchar) < 5)
			{
				link.l1 = "Ich bin bereit, die Fregatte in das Geschwader zu nehmen.";
                link.l1.go = "patria_2";
			}
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "baster")
			{
				link.l1 = "Ich habe hier ein Treffen mit einer Person...";
                link.l1.go = "baster_goldengirl";
			}
			//--> Торговля по закону
			if (CheckAttribute(pchar, "questTemp.TPZ_guber_1"))
			{
				link.l1 = "Monsieur, ich plane, mich hier in der Stadt geschäftlich zu betätigen. Insbesondere interessiere ich mich für den regelmäßigen Handel mit Spirituosen in großen Mengen.";
				link.l1.go = "TPZ_guber_1";
			}
			//<-- Торговля по закону

		break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
            dialog.text = RandPhraseSimple("Du hast bereits alles genommen. Was willst du noch?","Gibt es noch etwas, das Sie nicht ergriffen haben?");
            link.l1 = RandPhraseSimple("Nur mal umsehen...","Nur zur Kontrolle, ich könnte vergessen, etwas mitzunehmen...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		case "guardoftruth":
			dialog.text = "Hm. Das ist ziemlich interessant. Aber warum denken Sie, dass ich mich um die Probleme der Spanier kümmere?";
			link.l1 = "Es geht nicht um die Spanier, Monsieur. Religion teilt Menschen nicht nach Nationalität. Es gibt einen Gegenstand in Ihrer Pfarrei, der mit dem Blut des heiligen Dieners bedeckt ist, und es wurde eine Entweihung in der Pfarrei von Santiago begangen...";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "";
			link.l1 = "Ich bitte Sie, Gerechtigkeit zu zeigen und den heiligen Vater anzuweisen, das Kreuz seinen Eigentümern zurückzugeben.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Und seit wann bist du solch ein wahrer und ernsthafter Gläubiger geworden, ha, "+pchar.name+"? Die Spanier sind nicht unsere Freunde und ich sehe keinen Grund, den Heiligen Vater in dieser Angelegenheit zu drängen. Das Kreuz war ein Geschenk und das ist gut so. Unser Priester hat nichts mit diesem Diebstahl und Mord zu tun, also...";
			link.l1 = "Und Sie können mir nicht helfen, richtig?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Um ehrlich zu sein, "+pchar.name+", Ich fühle nicht, dass ich muss. Ich habe keine Liebe zu diesen Papistenfanatikern.";
			link.l1 = "Ich verstehe. Entschuldigung für die Störung, Monsieur...";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "28");
		break;
		
		// Jason НСО
		case "patria":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Das Schiff ist bereit, aber Sie haben keinen freien Platz dafür in Ihrer Staffel. Kapitän, verkleinern Sie Ihre Staffel und kehren Sie zurück, dann werde ich Ihnen sofort die Fregatte geben.";
				link.l1 = "Gut.";
				link.l1.go = "patria_1";
			}
			else
			{
				dialog.text = "Ja, natürlich, das Schiff ist bereit zum Auslaufen. Sein Kapitän ist informiert und wird all Ihren Befehlen folgen.";
				link.l1 = "Dann brechen wir auf. Auf Wiedersehen, Eure Gnaden.";
				link.l1.go = "patria_3";
			}
		break;
		
		case "patria_1":
			DialogExit();
			npchar.quest.frigate.wait = "true";
		break;
		
		case "patria_2":
			DeleteAttribute(npchar, "quest.frigate.wait");
			dialog.text = "Ausgezeichnet. Machen Sie sich bereit, Ihr neues Schiff zu begrüßen. Der Kapitän ist informiert und wird all Ihren Befehlen folgen.";
			link.l1 = "Dann brechen wir auf. Auf Wiedersehen, Eure Gnaden.";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			DialogExit();
			npchar.quest.frigate = "true";
			Patria_BastionFrigateGlp(); // присоединяем фрегат
		break;
		
		// Jason Дороже золота
		case "baster_goldengirl":
			dialog.text = "Ach, Monsieur Charles de Maure, perfektes Timing! Mein alter Freund ist sehr gespannt darauf, Sie kennenzulernen und hat darum gebeten, ihm von Ihrer Ankunft zu berichten. Bitte, kommen Sie in mein Wohnzimmer, ich werde Angerran sofort Bescheid geben. Wie haben Sie zwei sich eigentlich kennengelernt?";
			link.l1 = "Wir haben zusammen gespielt. Er hat verloren, wir hatten einen kleinen Streit. Ich vermute, Monsieur de Chievous würde gerne die Dinge zwischen uns klären.";
			link.l1.go = "baster_goldengirl_1";
		break;
		
		case "baster_goldengirl_1":
			dialog.text = "Ohne Zweifel! Ich hoffe, Sie werden die Dinge zwischen Ihnen beiden klären. Angerran mag vielleicht nicht die angenehmste Person sein, mit der man zu tun hat, aber er ist klug und ehrenhaft, genau wie Sie. Das ist eine seltene Rasse.";
			link.l1 = "Sie schmeicheln mir, Exzellenz. Wenn es Ihnen nichts ausmacht, werde ich auf ihn im Wohnzimmer warten.";
			link.l1.go = "baster_goldengirl_2";
		break;
		
		case "baster_goldengirl_2":
			dialog.text = "Aber natürlich, machen Sie es sich bequem. Vielleicht müssen Sie ein wenig warten. Ich werde anordnen, dass einige Getränke gebracht werden.";
			link.l1 = "Danke, Exzellenz, aber ich werde passen. Ich werde einfach sitzen und auf unseren gemeinsamen... Freund warten.";
			link.l1.go = "baster_goldengirl_3";
		break;
		
		case "baster_goldengirl_3":
			DialogExit();
			pchar.questTemp.GoldenGirl = "baster1";
			DoQuestReloadToLocation("CommonResidence_3", "reload", "reload1", "GoldenGirl_AngerranInResidence");
		break;
		
		//--> Торговля по закону
		case "TPZ_guber_1":
			dialog.text = "Kapitän, Sie haben richtig gehandelt, indem Sie sich an mich gewandt haben. Wir setzen alle Kräfte ein, um den illegalen Handel auf der Insel zu bekämpfen, und ich freue mich aufrichtig, wenn ehrliche Kapitäne zu mir kommen, um alles gesetzeskonform zu organisieren.";
			link.l1 = "Also, welche Bedingungen und Schritte sind erforderlich, um mit dem Handel zu beginnen?";
			link.l1.go = "TPZ_guber_2";
			DelLandQuestMark(npchar);
		break;

		case "TPZ_guber_2":
			dialog.text = "Es ist ganz einfach. Für den Handel mit Spirituosen müssen Sie eine Steuer an die Staatskasse zahlen, die hundert Dublonen pro Monat beträgt, sowie Buchhaltung führen und regelmäßig Berichte über Ihre Tätigkeit einreichen. Sobald Sie das Geld in die Kasse eingezahlt haben, können Sie mit dem Handel beginnen.";
			link.l1 = "Ausgezeichnet. Die Bedingungen sind durchaus akzeptabel. Im Namen von mir wird hier ein Einheimischer - Christian Deluce - die Geschäfte führen. Ich hoffe, das wird kein Problem sein?";
			link.l1.go = "TPZ_guber_3";
		break;

		case "TPZ_guber_3":
			dialog.text = "Wie Sie wünschen, Kapitän. Denken Sie jedoch daran: Die gesamte Verantwortung für Ihren Schützling liegt bei Ihnen, und im Falle seines Fehlverhaltens teilen Sie sein Schicksal.";
			link.l1 = "Natürlich. Vielen Dank für die Erläuterungen, Herr Gouverneur. Wir werden alles vorbereiten, und Christian wird die Steuer zahlen.";
			link.l1.go = "TPZ_guber_4";
		break;

		case "TPZ_guber_4":
			dialog.text = "Ausgezeichnet. Ich freue mich, einen so gewissenhaften Ansatz zu sehen. Viel Erfolg bei Ihrem Vorhaben.";
			link.l1 = "Danke. Ich bin sicher, unsere Zusammenarbeit wird der Stadt zugutekommen. Auf Wiedersehen.";
			link.l1.go = "TPZ_guber_5";
		break;

		case "TPZ_guber_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.TPZ_guber_1");
			AddQuestRecord("TPZ", "11");

			sld = CharacterFromID("TPZ_Kristian");
			sld.dialog.filename = "Quest\MiniEvents\TradingByLaw_dialog.c";
			sld.dialog.currentnode = "Kristian_21";
			ChangeCharacterAddressGroup(sld, "BasTer_houseF3", "barmen", "stay");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		//<-- Торговля по закону
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
