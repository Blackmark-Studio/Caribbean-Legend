// НПС офиса ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Brauchst du etwas?";
			link.l1 = "Nein.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// офицер
		case "HWIC_officer":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! Der Feind ist hier! Zu den Waffen!";
				link.l1 = "Verdammt!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Du da, halt! Dein Gesicht kommt mir bekannt vor...natürlich! Du wirst für deine Verbrechen gesucht! Jungs, schnappt ihn!";
				link.l1 = "Verdammt!";
				link.l1.go = "fight";
				break;
			}
			chrDisableReloadToLocation = true;
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				dialog.text = "Willkommen bei der Niederländischen Westindien-Kompanie. Sprich schnell, Zeit ist Geld.";
				link.l1 = "Ich bin hier wegen Handelsangelegenheiten. Lizenzen, Navigationsinstrumente und so weiter...";
				link.l1.go = "HWIC_officer_3";
				link.l2 = "Ich möchte der Gesellschaft meine Dienste anbieten. Natürlich im Austausch für Gold. Stellen Sie ein?";
				link.l2.go = "HWIC_officer_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "Willkommen bei der Niederländischen Westindien-Kompanie. Sprich schnell, Zeit ist Geld.";
				link.l1 = "Es tut mir leid, es scheint, dass ich mich geirrt habe. Ich gehe jetzt.";
				link.l1.go = "HWIC_officer_exit";
				link.l2 = "Ich bin hier wegen Handelsangelegenheiten. Lizenzen, Navigationsinstrumente und so weiter...";
				link.l2.go = "HWIC_officer_3";
				break;
			}
			dialog.text = "Sprechen Sie schnell, Zeit ist Geld.";
			link.l1 = "Ich bin hier für Handelsangelegenheiten. Lizenzen, Navigationsinstrumente und so weiter...";
			link.l1.go = "HWIC_officer_3";
			link.l2 = "Ich möchte meine Dienste der Kompanie anbieten. Natürlich im Austausch für Gold. Stellen Sie ein?";
			link.l2.go = "HWIC_officer_2";
		break;
		
		case "HWIC_officer_1":
			dialog.text = "Dann gehen Sie hinauf ins Büro von Mynheer Rodenburg.";
			link.l1 = "Danke, ich bin auf dem Weg.";
			link.l1.go = "HWIC_officer_exit";
			// belamour legendary edition переехали по другому адресу
			LocatorReloadEnterDisable("GVIK", "reload2", false);//кабинет откроем
		break;
		
		case "HWIC_officer_2":
			dialog.text = "Die Kompanie stellt momentan nicht ein.";
			link.l1 = "Das ist schade. Entschuldigung für die Störung.";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_3":
			dialog.text = "Sprich mit Mynheer Gerritz. Sein Tisch ist auf deiner linken Seite, wenn du reinkommst. Er macht Geschäfte mit vertraglich gebundenen Kapitänen.";
			link.l1 = "Danke, Offizier...";
			link.l1.go = "HWIC_officer_exit";
		break;
		
		case "HWIC_officer_exit":
			DialogExit();
			// belamour legendary edition переехали
			LAi_ActorGoToLocation(npchar, "soldiers", "soldier3", "GVIK", "soldiers", "soldier3", "", 5);
			DoQuestCheckDelay("ReturnTalkerToOfficer", 5.0); // 140313
			NextDiag.TempNode = "HWIC_officer";
		break;
		
		// солдаты
		case "HWIC_soldier":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! Der Feind ist hier! Zu den Waffen!";
				link.l1 = "Verdammt!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Aha! Ich glaube, ich weiß, wer du bist... Aber natürlich! Sie sind wegen Ihrer Verbrechen gesucht! Jungs, nehmt ihn!";
				link.l1 = "Verdammt!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Sprechen Sie mit unseren Offizieren oder mit Mynheer Gerritz. Ich habe nichts mit Ihnen zu besprechen. Ich bin im Dienst.";
			link.l1 = "Ihre Disziplin ist bewundernswert.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_soldier";
		break;
		
		// клерки
		case "HWIC_clerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! Der Feind ist hier! Soldaten!";
				link.l1 = "Verdammt!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Sprechen Sie mit Mynheer Gerritz.";
			link.l1 = "Gut, ich habe es verstanden.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "HWIC_clerk";
		break;
		
		// главный клерк - минхер Герритц
		case "HWIC_headclerk":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "Alarm! Der Feind ist hier! Soldaten, nehmt ihn fest!";
				link.l1 = "Verdammt!";
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = "Hm. Ich glaube, an dir ist etwas faul... Aber natürlich! Du wirst wegen deiner zahlreichen Verbrechen gegen Holland gesucht! Soldaten, nehmt ihn fest!";
				link.l1 = "Verdammt!";
				link.l1.go = "fight";
				break;
			}
			dialog.text = "Brauchen Sie etwas, Mynheer?";
			if (!CheckCharacterItem(pchar, "HolTradeLicence"))
			{
				link.l1 = "Ich möchte eine Handelslizenz der Niederländischen Westindien-Kompanie kaufen.";
				link.l1.go = "licence";	
			}
			if (!CheckAttribute(npchar, "quest.trade"))
			{
				link.l2 = "Ich habe gehört, dass man hier Navigationsinstrumente und andere nützliche Gegenstände kaufen kann. Ist das so?";
				link.l2.go = "trade";	
			}
			else
			{
				link.l2 = "Was verkaufen Sie heute?";
				link.l2.go = "trade_1";	
			}
			if (CheckCharacterItem(pchar, "Cromvel_depeshe"))
			{
				link.l3 = "Ich habe ein interessantes Dokument für Sie, mein Herr. Schauen Sie sich die ersten paar Zeilen an. Es geht um das Überleben der Republik und den Gewinn der Gesellschaft. Die Koordinaten eines bestimmten Treffens sind auch dabei. Ich werde sie Ihnen verkaufen, wenn Sie interessiert sind. Für einen großzügigen Preis natürlich.";
				link.l3.go = "depeshe";	
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Garpiya") && pchar.questTemp.Caleuche.Garpiya == "gwik")
			{
				link.l4 = "Ein Kapitän namens Reginald Jackson muss für Sie arbeiten. Er segelt auf einer Xebek namens 'Harpy'. Könnten Sie mir sagen, wie ich ihn finden kann? Ich habe wichtige Geschäfte mit ihm.";
				link.l4.go = "caleuche";	
			}
			// Sinistra Путеводная звезда
			if (CheckAttribute(pchar, "questTemp.PZ_RazgovorGerrits"))
			{
				link.l4 = "Ich muss dringend Mynheer Rodenburg sehen. Es ist von größter Wichtigkeit. Wo ist er?";
				link.l4.go = "PZ_RazgovorGerrits_1";
			}
			link.l9 = "Nein, es ist nichts.";
			link.l9.go = "exit";			
			NextDiag.TempNode = "HWIC_headclerk";
		break;
		
		// торговые лицензии
		case "licence":
			if (!CheckAttribute(npchar, "quest.licence"))
			{
				dialog.text = "Nun, Sie sind frei, es zu kaufen. Aber ich muss Sie warnen, dass die Kompanie ihren Ruf strikter Neutralität hochschätzt, daher ist es verboten, Handelsschiffe einer Nation anzugreifen, solange Sie diese Lizenz innehaben\nWenn wir herausfinden, dass ein solcher Akt begangen wurde - werden wir Ihre Lizenz annullieren. Zusätzlich, wenn Sie aus irgendeinem Grund mit den Niederlanden oder der Kompanie in Konflikt geraten, wird Ihre Lizenz ebenfalls annulliert. Ist das klar?";
				link.l1 = "Klar wie Kristall. Das werde ich mir merken.";
				link.l1.go = "licence_0";
				npchar.quest.licence = true;
			}
			else
			{
				dialog.text = "Sie können gerne eine Lizenz erwerben. Also, wie viele Tage?";
				link.l1.edit = 6;
				link.l1 = "";	
				link.l1.go = "licence_1";
			}
		break;
		
		case "licence_0":
			dialog.text = "Die Lizenz gewährt freie Durchfahrt zu jedem Hafen jeder Nation, sie zeigt Ihre friedlichen Absichten und erklärt Ihren Zweck - Handel zu treiben. Aber sie wird Ihnen nicht helfen, wenn Sie Probleme mit dem Gesetz haben. In diesem Fall wird sie Ihnen einfach weggenommen. Denken Sie daran, \nVergessen Sie nicht, eine freundliche Flagge zu hissen, bevor Sie in einen Hafen einlaufen. Patrouillen und Forts' Kanoniere schießen lieber zuerst und fragen später\nDie Mindestlaufzeit für die Lizenz beträgt zwanzig Tage und die maximale Laufzeit beträgt sechs Monate oder 180 Tage\nRichtig, ich hätte es fast vergessen... Nach unseren geschätzten Traditionen werden alle Geschäfte, die Lizenzen betreffen, in Dublonen bezahlt.  Jetzt diskutieren wir die Bedingungen. Wie lange möchten Sie, dass die Lizenz gültig ist?";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "Es tut mir leid, aber ich muss noch ein bisschen darüber nachdenken. Bis später.";	
			link.l2.go = "exit";
		break;
		
		case "licence_1":
			float fQty = stf(dialogEditStrings[6]);
			npchar.quest.lcc_summ = makeint(sqrt(fQty)*10)*7;
			if (fQty < 1)
			{
				dialog.text = "Mynheer bitte, sprechen Sie deutlich. Ich habe Sie nicht richtig gehört. Also, wie lange?";
				link.l1 = "Lass mich nachdenken...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 0 && fQty < 20)
			{
				dialog.text = "Die Mindestlaufzeit für die Lizenz beträgt zwanzig Tage. Na und? Zwanzig Tage oder länger?";
				link.l1 = "Lass mich nachdenken...";
				link.l1.go = "licence_r";
				break;
			}
			if (fQty > 180)
			{
				dialog.text = "Die maximale Laufzeit für die Lizenz beträgt ein halbes Jahr. Hundertachtzig Tage oder weniger?";
				link.l1 = "Lass mich nachdenken...";
				link.l1.go = "licence_r";
				break;
			}
			dialog.text = "Für "+FindRussianDaysString(sti(fQty))+"? Sehr gut. Es wird dich kosten "+FindRussianDublonString(sti(npchar.quest.lcc_summ))+". Sind diese Bedingungen akzeptabel?";
			if (PCharDublonsTotal() >= sti(npchar.quest.lcc_summ))
			{
				link.l1 = "Ja, das bin ich.";
				link.l1.go = "licence_2";
			}
			link.l2 = "Leider habe ich jetzt nicht so viel Geld dabei. Ich werde später wegen der Lizenz zurückkommen.";
			link.l2.go = "exit";
		break;
		
		case "licence_r":
			dialog.text = "";
			link.l1.edit = 6;
			link.l1 = "";	
			link.l1.go = "licence_1";
			link.l2 = "Es tut mir leid, aber ich muss noch darüber nachdenken. Wir sehen uns später.";	
			link.l2.go = "exit";
		break;
		
		case "licence_2":
			int iQty = sti(dialogEditStrings[6]);
			RemoveDublonsFromPCharTotal(sti(npchar.quest.lcc_summ));
			GiveNationLicence(HOLLAND, iQty);
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "start")
			{
				if(iQty < 180) 
				{
					Log_info("Quest: 'Together with the Shark' - your license is less than 180 days");
				}
				else 
				{
					pchar.questTemp.SharkGoldFleet.LicenceOk = true;
					AddQuestRecord("SharkGoldFleet", "2");
				}
				pchar.questTemp.SharkGoldFleet = "afterGvik";
			}
			dialog.text = "Warte eine Minute... Lass mich hier ein Zeichen und einen Stempel setzen...versiegelt und fertig. Nimm dein Dokument.";
			link.l1 = "Danke! Auf Wiedersehen, Mynheer.";
			link.l1.go = "exit";
		break;
		
		case "trade":
			dialog.text = "In der Tat tun wir das. Sie können hier Navigationsinstrumente wie Kompass, Astrolabium, Chronometer und Sanduhren kaufen. Aber wir haben nicht immer alles auf Lager zum Kauf, außer vielleicht Sanduhren. Unsere Vertragspartner und Kapitäne kaufen die anderen Werkzeuge sehr schnell auf. Wenn Sie also nicht finden, was Sie brauchen - besuchen Sie uns in einer Woche wieder, wenn wir auffüllen\nWir verkaufen auch Karten und Ferngläser. Möchten Sie sehen, was wir haben?";
			link.l1 = "Ja, bitte.";
			link.l1.go = "trade_1";
			npchar.quest.trade = "true";
		break;
		
		case "trade_1":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 7)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		// депеша Кромвеля
		case "depeshe":
			dialog.text = "Hm, zeig mir...(liest) Nun, nun... Cromwells Appetit wächst. Kanker! Haben diese Puritanerhunde nicht genug Blut auf ihrer eigenen Insel vergossen, ohne ihren Dreck hierher zu bringen!? Woher hast du diesen Bericht?";
			link.l1 = "Ich habe es von einem englischen Kurier genommen. Möchten Sie es kaufen?";
			link.l1.go = "depeshe_1";
		break;
		
		case "depeshe_1":
			dialog.text = "Ja. Peter Stuyvesant wird sicherlich sehr froh sein, es zu lesen, da bin ich sicher. Und er wird wirksame Maßnahmen ergreifen, um es zu stoppen... Ich kann mit Gold-Dukaten bezahlen oder ich kann Ihnen eine Lizenz für ein halbes Jahr ausstellen. Was ziehst du vor?";
			link.l1 = "Ich wähle Gold.";
			link.l1.go = "depeshe_dublon";
			link.l2 = "Ich möchte die Lizenz.";
			link.l2.go = "depeshe_licence";
		break;
		
		case "depeshe_dublon":
			TakeNItems(pchar, "gold_dublon", 700);
			Log_Info("You have received 700 doubloons");
			dialog.text = "Sehr gut. Hier sind deine siebenhundert Dublonen. Eine stattliche Belohnung für einen gut erbrachten Dienst.";
			link.l1 = "Hier ist Ihr Bericht.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_licence":
			if (CheckCharacterItem(pchar, "HolTradeLicence")) TakeNationLicence(HOLLAND);
			GiveNationLicence(HOLLAND, 180);
			dialog.text = "Gut. Hier ist Ihre Lizenz für ein halbes Jahr.";
			link.l1 = "Danke! Und hier ist Ihre Sendung.";
			link.l1.go = "depeshe_exit";
		break;
		
		case "depeshe_exit":
			RemoveItems(pchar, "Cromvel_depeshe", 1);
			pchar.quest.Terrapin_CromvelScuadron.over = "yes"; //снять прерывание
			ChangeCharacterNationReputation(pchar, HOLLAND, 15);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			dialog.text = "Danke. Es ist gut, dass Sie Ihr Bewusstsein und Ihre Loyalität gegenüber der Republik gezeigt haben. Ich werde Matthias Beck und Peter Stuyvesant von Ihrer guten Tat erzählen.";
			link.l1 = "Gut zu wissen. Auf Wiedersehen!";
			link.l1.go = "exit";
		break;
		
		// Sinistra Путеводная звезда
		case "PZ_RazgovorGerrits_1":
			dialog.text = "Fürchte, er ist bereits mit der Familie Schneur in die Alte Welt aufgebrochen. Ich glaube, er hat es Ihnen erwähnt.";
			link.l1 = "Das stimmt, das hat er. Aber ich hoffte, er könnte durch einige aktuelle Geschäfte auf dem Archipel verzögert worden sein. Sag mir, Gerritz, hat jemand in der Firma noch Kontakt zu Mynheer Rodenburg? Vielleicht über Kurierschiffe?";
			link.l1.go = "PZ_RazgovorGerrits_2";
		break;
		
		case "PZ_RazgovorGerrits_2":
			dialog.text = "Überhaupt nicht - bevor er ging, bat er uns, ihn nie zu stören - er sagte, er begänne ein neues, besseres Leben.";
			link.l1 = "Lassen wir hoffen, dass auch unser Leben besser wird. Auf Wiedersehen.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PZ_RazgovorGerrits");
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "Lassen Sie mich die Manifestprotokolle überprüfen....Ikema, Immerzeel, Jacobs...Jackson, gefunden. Hmm, Kapitän Reginald Jackson betreibt derzeit regelmäßige Schifffahrtsoperationen zwischen Port Royal und Philipsburg. Suchen Sie ihn auf dieser Route. Nun Kapitän, ich muss Sie im Voraus warnen - wenn Sie etwas Unfug planen, sollten Sie es besser nicht tun, denn dieser Kapitän Jackson steht unter unserem Schutz. Verstehen wir uns, mein Herr?";
			link.l1 = "Ich habe nur Geschäfte mit ihm. Ein gewöhnlicher Handel. Ich habe nicht vor, ihm in irgendeiner Weise zu schaden.";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Ausgezeichnet. Kapitän Jackson bleibt normalerweise nicht lange in Port Royal oder in Philipsburg. Zeit ist schließlich Geld. Sobald sein Schiff entladen und wieder beladen ist, setzt er normalerweise sofort die Segel. Sie werden mehr Glück haben, ihn auf den Seewegen zu treffen.";
			link.l1 = "Danke dir!";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			pchar.questTemp.Caleuche.Garpiya = "capitan";
			pchar.questTemp.Garpiya = "to_portroyal";
			AddQuestRecord("Caleuche", "19");
			DoQuestFunctionDelay("Caleuche_CreateGarpiyaInWorld", 1.0);
		break;
		
		// новый босс ГВИК
		case "HWIC_Boss":
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if (!CheckAttribute(npchar, "quest.silk_info") && sti(pchar.reputation.nobility) > 60)
				{
					dialog.text = "Aha, Kapitän "+GetFullName(pchar)+"! Es ist gut, dass du hierher gekommen bist. Ich habe ein Geschäftsangebot für dich.";
					link.l1 = "Interessant! Ich höre Ihnen zu, Mynheer.";
					link.l1.go = "silk_info";
					break;
				}
			}
			dialog.text = "Guten Tag, Kapitän "+GetFullName(pchar)+"! Wie kann ich dienen?";
			if(CheckAttribute(pchar,"questTemp.HWIC.Detector") && (pchar.questTemp.HWIC.Detector == "holl_win"))
			{
				if(CheckAttribute(npchar, "quest.silk")) // торговля шелком
				{
					if (GetDataDay() == 1 || GetDataDay() == 15)
					{
						link.l1 = "Über diese Schiffsseide...";
						link.l1.go = "trade_silk";
					}
				}
			}
			link.l2 = "Guten Tag. Nein, ich brauche nichts, wollte nur Hallo sagen.";
			link.l2.go = "exit";			
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "silk_info":
			dialog.text = "Ich habe kürzlich Handelsbeziehungen mit einem Kaufmann aus Lyon aufgenommen, um die Karibik mit Schiffsseide zu versorgen. Wissen Sie darüber? Die allerbesten Segel der Welt werden aus dieser Seide hergestellt, also müssen Sie interessiert sein.";
			link.l1 = "Schlag mich tot, ja das ist Musik in meinen Ohren. Was sind deine Bedingungen?";
			link.l1.go = "silk_info_1";
		break;
		
		case "silk_info_1":
			dialog.text = "Kleine, aber regelmäßige Sendungen. Ich kann alle zwei Wochen dreißig Rollen für dich aufbewahren. Eine Rolle kostet zwanzig Dublonen. Lass es uns so machen: Ich bewahre dir jeden ersten und fünfzehnten Tag des Monats dreißig Rollen auf. Wenn du sie dann nicht abholst, verkaufe ich die Rollen an einen anderen Kunden.";
			link.l1 = "Also keine Verpflichtungen?";
			link.l1.go = "silk_info_2";
		break;
		
		case "silk_info_2":
			dialog.text = "Genau, Kapitän. Kaufen Sie die Seide, wenn Sie wollen. Sie zahlen für die ganze Partie - sechshundert Dublonen. Ich hoffe, dass Sie ein Stammkunde werden.";
			link.l1 = "Danke für Ihren Vorschlag, Mynheer. Abgemacht.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			npchar.quest.silk_info = "true";
			npchar.quest.silk = "true";
			AddQuestRecordInfo("Unique_Goods", "3");
		break;
		
		// торговля шелком
		case "trade_silk":
			if (CheckAttribute(pchar, "questTemp.UpgradeSilk"))
			{
				dialog.text = "Sicher, Kapitän. Ihre Seide wartet auf Sie. Sind Sie bereit, dafür zu bezahlen?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "Sicher! Hier, nimm 2550 Dublonen.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "Verdammt, ich habe das Geld auf meinem Schiff vergessen. Ich bringe es in einer Sekunde!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Sicher, Kapitän. Ihre Seide wartet auf Sie. Sind Sie bereit, dafür zu bezahlen?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "Sicher! Hier, nimm sechshundert Dublonen.";
					link.l1.go = "trade_silk_1";
				}
				else
				{
					link.l1 = "Verdammt, ich habe das Geld auf meinem Schiff vergessen. Ich bringe es in einer Sekunde!";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && !CheckAttribute(pchar, "questTemp.GVIKSilkBlock")) // увеличить объём поставок шёлка
			{
				link.l4 = "Mijnheer "+npchar.name+", ich möchte gerne die Möglichkeit besprechen, die Seidenlieferungen zu erhöhen.";
				link.l4.go = "UpgradeSilk";
			}
			if(sti(pchar.questTemp.GVIKSilk) >= 1 && CheckAttribute(pchar, "questTemp.GVIKSilkPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок шёлка, если в первый раз не принесли
			{
				link.l4 = "Ich habe Ihre Dublonen gebracht, Mijnheer "+npchar.name+". Bitte nehmen Sie sie entgegen.";
				link.l4.go = "UpgradeSilk_Agreed";
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "trade_silk_1":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You have given 600 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Es war ein Vergnügen, Geschäfte mit Ihnen zu machen, Kapitän. Ihre Seide wird per Langboot zu Ihrem Schiff geliefert.";
			link.l1 = "Danke!";
			link.l1.go = "trade_silk_2";
		break;
		
		case "trade_silk_2":
			dialog.text = "Ich hoffe, dich bald zu sehen. Komm wieder.";
			link.l1 = "Sicher. Bis dann!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 30);
			DeleteAttribute(npchar, "quest.silk");
			SetFunctionTimerCondition("Silk_TraderAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk": //
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Ich schätze Ihren geschäftlichen Ansatz und bin bereit, Ihre Anfrage zu prüfen. Vielleicht könnten wir das Volumen, sagen wir, verfünffachen. Allerdings wird die Organisation solcher Lieferungen erhebliche Ressourcen erfordern. Wir müssen Lagerräume erweitern, die Sicherheit verstärken und zuverlässige Lieferwege gewährleisten. Da dies auch Ihnen zugute kommt, schlage ich vor, dass wir diese Kosten unter uns aufteilen.";
				link.l1 = "Das klingt alles vernünftig. Welchen Betrag halten Sie für notwendig, um diese Ausgaben zu decken?";
				link.l1.go = "UpgradeSilk_1";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Ich verstehe Ihr Interesse an einer Erhöhung der Lieferungen, allerdings fällt es mir in dieser Phase schwer, solchen Änderungen zuzustimmen. Ich zweifle nicht an Ihrem Streben nach Entwicklung, aber für diese Art von Transaktion benötigt man viel mehr Erfahrung in Handelsangelegenheiten und Vertrauen in die eigenen Handlungen. Ich schlage vor, dass Sie Ihre Kenntnisse in der Kunst der Verhandlung erweitern und dann mit einem konkreteren Vorschlag zu mir zurückkehren. Wenn Sie bereit sind, freue ich mich darauf, unsere Zusammenarbeit zu stärken.";
				link.l1 = "Hmm... Gut. Ich werde später auf dieses Gespräch zurückkommen.";
				link.l1.go = "exit";
				notification("Skill Check Failed (80)", SKILL_COMMERCE);
			}
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_1":
			dialog.text = "Unter Berücksichtigung aller Feinheiten wird Ihr Kostenanteil dreitausend goldene Dublonen betragen. Diese Mittel werden es uns ermöglichen, die notwendigen Maßnahmen ohne Verzögerung zu organisieren.";
			link.l1 = "Mijnheer "+npchar.name+", dreitausend Dublonen? Ist das ein Scherz? Ich bin mit einem ehrlichen Angebot zu Ihnen gekommen, und Sie wollen, dass ich einen solch unglaublichen Betrag für die Organisation von Lieferungen zahle?";
			link.l1.go = "UpgradeSilk_2";
		break;
		
		case "UpgradeSilk_2":
			dialog.text = "Ich bitte Sie, mich richtig zu verstehen. Ich versuche nicht, Sie zu täuschen. Dieses Geld ist der Betrag, der es uns ermöglichen wird, die richtige Ordnung bei der Organisation der Lieferungen zu gewährleisten. Es geht nicht nur um die Erweiterung von Lagern und Sicherheit, sondern auch darum, die Lieferung von Waren ohne Verzögerungen und Verluste zu garantieren, trotz aller Unvorhersehbarkeit dieses Geschäfts. Dies sind Standardausgaben für solche Mengen. Letztendlich werden sich Ihre Investitionen rechtfertigen, und Sie erhalten die Waren in einwandfreiem Zustand und pünktlich.";
			link.l1 = "Ihre Erklärungen beruhigen mich etwas, Mijnheer. Aber trotzdem bleibt dieser Betrag zu hoch. Ich bin bereit, Ihren Bedingungen zuzustimmen, wenn Sie den Preis auf mindestens zweieinhalbtausend Dublonen senken. Ich bin sicher, dass dies für die Organisation von Lieferungen und die Einhaltung aller Sicherheitsmaßnahmen ausreichen wird.";
			link.l1.go = "UpgradeSilk_3";
		break;
		
		case "UpgradeSilk_3":
			dialog.text = " Ich verstehe, der Betrag ist groß, aber wie ich bereits sagte, ist er für die ordnungsgemäße Ausführung der Arbeit notwendig. Ich kann ihn nicht reduzieren, da dies alle unsere Bemühungen gefährden würde. Damit Sie sich jedoch nicht betrogen fühlen, bin ich bereit, Ihnen einen Rabatt von fünfzehn Prozent auf alle zukünftigen Lieferungen anzubieten. Dies wird Ihnen hoffentlich helfen, die Kosten auszugleichen.";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Hmm, ein Rabatt von fünfzehn Prozent ist natürlich ein Schritt entgegen. In Ordnung. Ich bin bereit, Ihr Angebot anzunehmen, obwohl mir der Preis äußerst hoch erscheint. Ich hoffe, unsere Zusammenarbeit wird meine Erwartungen erfüllen. Hier ist Ihr Geld.";
				link.l1.go = "UpgradeSilk_Agreed";
			}
			link.l2 = "Mijnheer "+npchar.name+", Ihr Angebot lässt mir keine Wahl. Es sollen dreitausend Dublonen sein, obwohl es eine beträchtliche Summe ist. Allerdings kann ich jetzt nicht alles auf einmal bezahlen. Ich werde zurückkehren, sobald ich das Geld habe.";
			link.l2.go = "UpgradeSilk_5";
			link.l3 = "Ein Rabatt von fünfzehn Prozent? Mijnheer "+npchar.name+", das ist nicht das, was ich erwartet habe. Dieser Betrag sind nicht nur Kosten, das ist offener und unverhohlener Raub! Aber ich beabsichtige nicht, die Geschäftsbeziehungen mit Ihnen abzubrechen. Wir werden zu den vorherigen Bedingungen zurückkehren - 30 Rollen Seide zu je 20 Dublonen.";
			link.l3.go = "UpgradeSilk_4";
		break;
		
		case "UpgradeSilk_Agreed":
			dialog.text = " Ich freue mich, dass Sie einverstanden sind, "+pchar.name+". Nun zu den Details: 150 Rollen Seide zu je 17 Dublonen. Insgesamt - 2550 Dublonen für die gesamte Partie. Sie können die Waren wie üblich abholen - am 1. und 15. jeden Monats. Ich denke, dieses Geschäft wird für beide Seiten einen guten Gewinn bringen.";
			link.l1 = "Отлично! Вот это - уже неплохой размах. Всего доброго, минхер. Скоро увидимся.";
			link.l1.go = "exit";
			NextDiag.TempNode = "HWIC_Boss";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "3_1");
			pchar.questTemp.UpgradeSilk = true;
			pchar.questTemp.GVIKSilkBlock = true;
			DeleteAttribute(pchar, "questTemp.GVIKSilkPotom");
		break;
		
		case "UpgradeSilk_4":
			dialog.text = "Das ist nur ein geschäftlicher Ansatz und kein Raub, wie es Ihnen erschienen sein mag. Aber wie Sie wünschen. Kommen Sie wie gewohnt am 1. und 15. für eine Partie Seide, ich freue mich auf ein neues Geschäft.";
			link.l1 = "Gewiss, Mijnheer. Alles Gute.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "UpgradeSilk_5":
			dialog.text = "Ich bin froh, dass Sie die richtige Entscheidung getroffen haben. Sobald Sie das Geld bringen, werden wir alle Details des Geschäfts besprechen und mit der Umsetzung beginnen.";
			link.l1 = "Auf Wiedersehen, Mijnheer "+npchar.name+". Wir sehen uns, sobald ich den erforderlichen Betrag zusammenhabe.";
			link.l1.go = "exit";
			pchar.questTemp.GVIKSilkBlock = true;
			pchar.questTemp.GVIKSilkPotom = true;
			NextDiag.TempNode = "HWIC_Boss";
		break;
		
		case "fight":
			DialogExit();
			sld = characterFromId("HWIC_officer");
			LAi_SetGuardianTypeNoGroup(sld);
			LAi_group_Attack(sld, Pchar);
			for (i=1; i<=6; i++)
			{	
				sld = characterFromId("HWIC_sold_"+i);
				LAi_group_Attack(sld, Pchar);
			}
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
