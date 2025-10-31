// Абигайль Шнеур
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyInHouse")
				{
					dialog.text = "Guten Tag, Mynheer. Was führt Sie zu uns nach Hause?";
					link.l1 = "Guten Tag, Abigail. Mein Name ist "+GetFullName(pchar)+". Ich bin ein Kapitän, der für das Wohl der Republik und der Niederländischen Westindien-Kompanie arbeitet.";
					link.l1.go = "AbbyAndLucas";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "Mein Gott, hast du das Geld meines Vaters gefunden? Ist es wahr? Ach, ich bin so froh! Geh schnell zu meinem Vater, er möchte mit dir sprechen. Geh und sieh ihn an!";
					link.l1 = "Ich bin auf dem Weg, Madame.";
					link.l1.go = "exit";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyLeavesMarried")
				{
					dialog.text = "Sie haben uns vor völliger Verzweiflung gerettet, Kapitän! Ich bin Ihnen so dankbar! Nun kann der gute Name der Familie Shneur wiederhergestellt werden!";
					link.l1 = "Nur meine Pflicht als Gentleman, Madame. Ich hoffe, es gibt nichts mehr, was Sie davon abhält, meinen Gönner zu heiraten.";
					link.l1.go = "AbbyAndLucas_8";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Brauchen Sie etwas, Kapitän?";
				link.l1 = "Jetzt nicht, Madame.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "AbigileInChurch")
				{
					dialog.text = "Heilige Königin, unser Leben, unsere Süße und unsere Hoffnung. Zu dir schreien wir, arme verbannte Kinder Evas. Zu dir schicken wir unsere Seufzer, Trauer und Weinen in diesem Tal der Tränen...oh Mynheer, du hast mich erschreckt! Was bringt dich hierher?";
					link.l1 = "Verzeihung, Sie sind doch Abigail, nicht wahr? Richard Fleetwood hat mich geschickt...";
					link.l1.go = "Seek_Island";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Wollen Sie etwas, Kapitän?";
				link.l1 = "Nicht jetzt, Madame.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "Was geht hier vor sich? Was ist das für ein Lärm? Papa, wer ist dieser seltsame Mann?";
					link.l1 = "Guten Tag, gnädige Frau. Abigail Schneur, nehme ich an? Es freut mich, Sie zu sehen. Sie müssen mir meine Unverschämtheit verzeihen, aber ich habe hier einen dringenden Brief an Sie... Nun, ich würde gerne erzählen, aber Ihr lieber Vater lässt mich nicht einmal in Ihr Haus, geschweige denn diese Nachricht für Sie überbringen.";
					link.l1.go = "Abigile_kidnapping";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDay")
				{
					dialog.text = "Ach, da bist du ja, Charles. Ich bin bereit, dir überall hin zu folgen!";
					link.l1 = "Dann lass uns gehen.";
					link.l1.go = "Abigile_kidnapping_7";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInCabin")
				{
					dialog.text = "Sind wir schon in St. John's, Charles? Werde ich Richard bald sehen?";
					link.l1 = "Ja, Madame, wir sind in St. John's. Leider ist Richard momentan nicht in der Stadt, er wurde beauftragt, vor zwei Tagen in der Nähe von Barbados zu patrouillieren. Machen Sie sich keine Sorgen, er sollte in einer Woche zurückkehren.";
					link.l1.go = "Abigile_kidnapping_8";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileLie")
				{
					dialog.text = "Charles! Ich bin so froh, dich zu sehen! Gibt es Neuigkeiten von Richard?";
					link.l1 = "Ach, meine liebe Dame. Richard musste für eine geheime und wichtige Mission für eine Weile in Bridgetown bleiben, es hat etwas mit den Holländern zu tun. Ich nehme an, dass Richard Ihnen erzählt hat, was er beruflich macht, richtig?";
					link.l1.go = "Abigile_kidnapping_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHome")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Charles! Du bist es! Du bist endlich zurück!";
					link.l1 = "Grüße, Madame. Ich freue mich, Sie zu sehen.";
					link.l1.go = "Abigile_return";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHomeGo")
				{
					dialog.text = "Ach, endlich bin ich zu Hause! Ich freue mich so, Papa wieder zu sehen! Charles, danke für alles, was du für mich getan hast!";
					link.l1 = "Bitte, es besteht keine Notwendigkeit für solche Gespräche, Madame. Ich tue nur meine Pflicht als Gentleman für eine Dame in Not.";
					link.l1.go = "Abigile_return_6";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryNext")
				{
					dialog.text = "Papa, wenn du dich an irgendetwas erinnerst, bitte sag es! Charles, er ist... er kann vertraut werden. Ich wage zu sagen, er ist der einzige, der uns helfen kann!";
					link.l1 = "";
					link.l1.go = "Abigile_return_12";
					pchar.questTemp.HWIC.Self = "SolomonHistoryAfter";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryEnd")
				{
					dialog.text = "Ich werde Nacht und Tag für dich beten! Sag mir... sag mir, dass du es tun wirst! Dass du die Insel finden wirst!";
					link.l1 = "Ich werde tun, was ich kann, Madame.";
					link.l1.go = "Abigile_return_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "final" || pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					dialog.text = "Ach, Charles! Du bist zurück! Erzähl mir schnell, hast du die Insel gefunden? Ich kann kaum noch warten!";
					if (makeint(Pchar.money) >= 200000)
					{
						link.l1 = "Ja, Abi. Ich habe die Insel und das Geld deines Vaters gefunden. Ich bin hier, um es dir zurückzugeben.";
						link.l1.go = "Abigile_GiveMoney";
					}
					link.l2 = "Ach, Madame. Es gelang mir nicht, weder Kapitän Keller noch Ihre Insel zu finden. Ich habe getan, was ich konnte, aber...";
					link.l2.go = "Abigile_NoMoney";
				break;
				}
				dialog.text = "Ach, du bist es Charles! Brauchst du etwas? Kann ich dir etwas Kaffee anbieten?";
				link.l1 = "Nein, nichts. Bitte bemühen Sie sich nicht.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Guten Tag, Mynheer. Was gibt's?";
			link.l1 = "Nichts, Madame. Ich muss um Ihre Verzeihung bitten. Auf Wiedersehen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

//-------------------------------------------------за Голландию-----------------------------------------------
		case "AbbyAndLucas":
			dialog.text = "Es ist mir eine Ehre, Sie zu treffen, Kapitän "+GetFullName(pchar)+". Ich habe alle möglichen Geschichten über Sie von den anderen Damen in der Stadt gehört. Sie sind der Mann, der das Piratengeisterschiff gefangen genommen und es als Preis nach Willemstad gebracht hat. Sagen Sie mir Kapitän... ist es wahr, dass dieses Schiff unter dem Kommando von... Richard Fleetwood stand?";
			link.l1 = "Alles, was Sie gehört haben, ist wahr, Madame. Ich war genauso schockiert wie jeder andere, die Wahrheit zu erfahren. Es ist ein Skandal! Ein Marineoffizier des Englischen Commonwealth, der Händler seiner eigenen Nation wie ein gewöhnlicher Pirat ausplündert! Dieser Schurke versuchte, seine niederträchtigen Taten zu verbergen, indem er vorgab, ein abtrünniges 'Geisterschiff' unter der Unterstützung der Holländischen Westindien-Kompanie zu sein. Er nutzte diese Tarnung, um die Kompanie zu beschuldigen und niederländische Schiffe anzugreifen.";
			link.l1.go = "AbbyAndLucas_1";
		break;
		
		case "AbbyAndLucas_1":
			dialog.text = "Mir dreht sich der Kopf... Es ist schwer, solche schrecklichen Dinge zu hören, Kapitän. Ich kannte Richard Fleetwood persönlich, ich hätte nie gedacht, dass er...";
			link.l1 = "Madame, mein Gönner Lucas Rodenburg hat mich über Ihre Reise von Recife nach Curacao informiert. Jetzt ist es klar. Fleetwood hat Ihr Schiff versenkt und ist dann zurückgekehrt, um Sie und Ihren Vater von dieser verlorenen Insel zu 'retten'. Ich habe das Tagebuch des Piraten selbst gelesen, er hat jedes Detail in sein Logbuch eingetragen.";
			link.l1.go = "AbbyAndLucas_2";
		break;
		
		case "AbbyAndLucas_2":
			dialog.text = "Was für ein Albtraum... Es scheint, dass mein Papa doch Recht hatte. Er hat mir immer gesagt, dass Richard dieser Pirat war, der die Quelle all unseres Unglücks war. Ich sollte froh sein, dass die Wahrheit ans Licht gekommen ist... ah, es tut mir leid, Kapitän. Es ist einfach zu viel für meinen armen Kopf... was will so ein wichtiger Mann wie Sie von einem gewöhnlichen Mädchen?";
			link.l1 = "Abigail, ich bin hier wegen einer sehr komplizierten und heiklen Angelegenheit. Wirst du mir zuhören?";
			link.l1.go = "AbbyAndLucas_3";
		break;
		
		case "AbbyAndLucas_3":
			dialog.text = "Natürlich, Mynheer. Ich bin ganz Ohr.";
			link.l1 = "Wie ich bereits gesagt habe, diene ich der Kompanie. Lucas Rodenburg ist nicht nur mein militärischer Kommandeur, sondern auch ein guter Freund. Er hat mich mit einer Botschaft zu Ihnen geschickt. Es wäre das größte Glück für Sie, seinem Heiratsantrag zuzustimmen. Ich bin hier, um Sie zu bitten, meinen Gönner zu heiraten. Er ist bereit, alles auf der Welt für Ihr Glück zu tun.";
			link.l1.go = "AbbyAndLucas_4";
		break;
		
		case "AbbyAndLucas_4":
			dialog.text = "Oh, Kapitän! Jetzt sehe ich, warum Mynheer Rodenburg das selbst nicht tun wollte... Mein armer Papa würde sich freuen, aber ich...";
			link.l1 = "Madame, ich sehe, dass Sie etwas beunruhigt. Zweifeln Sie an der Aufrichtigkeit von Mynheer Rodenburg? Vielleicht könnte ich Ihnen helfen, Ihre Meinung zu ändern?";
			link.l1.go = "AbbyAndLucas_5";
		break;
		
		case "AbbyAndLucas_5":
			dialog.text = "Oh nein, Kapitän, ich habe keinen Zweifel an Mynheer Rodenburgs Aufrichtigkeit. Lucas hat so viel für mich und meinen Papa getan, ich weiß nicht, was mit uns passieren würde, wenn er nicht auf uns aufpassen würde. Aber bitte, Sie müssen meine Position verstehen!\nMeine Familie sind keine Rothschilds, aber wir waren nie arm. Die Familie Shneur ist bekannt unter den Bankhäusern Europas für unser Vermögen... aber jetzt hat dieser schreckliche Pirat uns ruiniert! Ich kann dieses abscheuliche Gerede, von dem ich weiß, dass es hinter unserem Rücken stattfindet, nicht länger ertragen. Jede schwatzende Hausfrau und Magd in dieser Stadt denkt, dass ich nur hinter Mynheer Rodenburg her bin wegen seines Geldes. 'Wie jüdisch', sagen sie. Die grausamen Weiber! Wenn mein Vater nur die Lage der Insel wüsste! Er hat den Rest unseres Familienvermögens dort versteckt, um es vor den Händen dieser teuflischen Piraten zu retten, die meine Schwestern und meinen Bruder ermordet haben!\nAber mein armer Vater ist kein Seemann, er kann sich einfach nicht erinnern, wo diese Insel und unser Familienvermögen ist! Bitte sprechen Sie mit meinem Vater, Kapitän! Vielleicht kann er sich an etwas erinnern, das für Ihre erfahrenen Sinne nützlich sein kann. Bitte finden Sie diese Insel und unser Vermögen! Sie hätten ein armes Mädchen vor Schande und Schmach gerettet!";
			link.l1 = "Sehr gut, Abigail. Ich werde mit deinem Vater sprechen. Hab Vertrauen, Mädchen, ich werde tun, was ich kann.";
			link.l1.go = "AbbyAndLucas_6";
		break;
		
		case "AbbyAndLucas_6":
			dialog.text = "Danke, Mynheer. Ich werde Tag und Nacht für Sie beten. Möge der Gott unserer Väter mit Ihnen sein!";
			link.l1 = "Auf Wiedersehen, Abigail. Ich werde mit guten Nachrichten zurückkehren, das schwöre ich.";
			link.l1.go = "AbbyAndLucas_7";
		break;
		
		case "AbbyAndLucas_7":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-27");
			pchar.questTemp.HWIC.Holl = "AbbyFather";
			AddLandQuestMark(characterFromId("Solomon"), "questmarkmain");
		break;
		
		case "AbbyAndLucas_8":
			dialog.text = "Oh, ja! Mynheer Rodenburg ist ein ehrenhafter und freundlicher Mann. Ich werde ihm ohne zu zögern meine Zustimmung geben und ich werde glücklich sein, ihn meinen Ehemann zu nennen.";
			link.l1 = "Dann betrachte ich meine Aufgabe als erfüllt. Ich muss jetzt zu Mynheer Rodenburg gehen und ihm die guten Nachrichten mitteilen. Ich wünsche Ihnen aufrichtig Glück, Madame.";
			link.l1.go = "AbbyAndLucas_9";
		break;
		
		case "AbbyAndLucas_9":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-33");
			pchar.questTemp.HWIC.Holl = "AbbyAgreeMarried";//теперь к Лукасу
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
		break;
		
//-------------------------------------------------за Англию-----------------------------------------
		case "Seek_Island":
			dialog.text = "Richard hat dich geschickt?! Gesegnete Maria, danke dir! Ah, Mynheer! Ich habe gehört, dass der arme Richard verwundet und dem Tode nahe war. Ist das wahr? Sag mir, lebt er?! Ist er gesund?!";
			link.l1 = "Richard lebt und... ist größtenteils gesund. Hier sind zuerst die schlechten Nachrichten: Er ist etwas mitgenommen und vorübergehend erblindet, aber er erholt sich. Nun die guten Nachrichten: Richard will, dass du mit ihm nach England segelst, wo ihr heiraten werdet. Seine Zeit in der Karibik ist vorbei und er wartet auf deine Antwort.";
			link.l1.go = "Seek_Island_1";
		break;
		
		case "Seek_Island_1":
			dialog.text = "Ach, mein lieber Bote, sag Richard, dass ich für unser Glück bereit bin, mit ihm zu gehen, wohin er will. Aber ich befürchte, dass unser Durchbrennen meinen armen Vater umbringen wird... Herr, ich bin verzweifelt und weiß nicht, was ich tun soll. Ich wünschte, Richard könnte diese verfluchte Insel und die Truhe mit unserem Familiengold finden... Vielleicht würde das meinen Papa in meiner Abwesenheit irgendwie trösten.";
			link.l1 = "Ich verstehe... Meine Mission war es, Sie nach Antigua zu bringen, aber das kompliziert die Dinge ein wenig. Sollte ich die Insel und die Truhe finden und sie Ihnen bringen, würden Sie dann mit mir nach St. John's und Richard gehen?";
			link.l1.go = "Seek_Island_2";
		break;
		
		case "Seek_Island_2":
			dialog.text = "Oh ja, Herr, ich würde Sie in unseren Familiengebeten in Erinnerung behalten! Ich würde unseren erstgeborenen Sohn nach Ihnen benennen! Vielen Dank, Kapitän! Ich werde für Sie beten! Geh und mögen Christus und die Heilige Mutter bei dir sein!";
			link.l1 = "Ich werde Sie nicht zu lange warten lassen, Madame. Ich werde bald zurückkehren.";
			link.l1.go = "Seek_Island_3";
		break;
		
		case "Seek_Island_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-18");
			pchar.questTemp.HWIC.Eng = "SeekIsland";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Villemstad_houseSp2_bedroom", "goto", "goto1", "", -1);//Аби домой
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
			DelMapQuestMarkCity("Villemstad");
		break;
		
//--------------------------------------------против всех------------------------------------------------
		case "Abigile_kidnapping":
			dialog.text = "Oh... Sie haben einen Brief von ihm? Oh Papa, sei nicht so hart zu unseren Gästen! Du beschämst mich mit deinen neurotischen Fantasien! Mynheer, bitte folgen Sie mir, ich möchte mit Ihnen sprechen.";
			link.l1 = "Danke, Fräulein. Schön zu sehen, dass jemand in diesem Haus Sinn spricht.";
			link.l1.go = "Abigile_kidnapping_1";
		break;
		
		case "Abigile_kidnapping_1":
			DialogExit();
			npchar.greeting = "abigile_3";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "Abigile_Stay", -1);
			NextDiag.CurrentNode = "Abigile_kidnapping_2";
			pchar.questTemp.HWIC.Self = "AbigileTalk";
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Abigile_kidnapping_2":
			DelLandQuestMark(npchar);
			dialog.text = "Verzeihen Sie meinem Vater, Mynheer. Er ist wirklich ein guter und freundlicher Mann, aber unser... Unglück hat ihn gebrochen.";
			link.l1 = "Es ist in Ordnung, Herrin, ich verstehe. Lassen Sie mich mich vorstellen, ich bin Charlie der... Knippel. Ich bin hier auf Befehl von Richard Fleetwood, er möchte, dass ich Sie zu ihm bringe. Hier bitte, lesen Sie den Brief.";
			link.l1.go = "Abigile_kidnapping_3";
		break;
		
		case "Abigile_kidnapping_3":
			RemoveItems(PChar, "NPC_Letter", 1);
			dialog.text = "Oh Richard...(liest). Oh, Gott! Er hat beschlossen... meinem Vater all sein verlorenes Geld zurückzugeben! Solche Großzügigkeit! Lieber, süßer Richard! Mynheer, du bringst gute Nachrichten wie Gabriel selbst! Richard, wo ist er? Ist er auf Curacao?";
			link.l1 = "Nein, Fräulein. Es gab einen Mordversuch und er wurde schwer verletzt. Er ist jetzt auf Antigua... Sie haben den Brief noch nicht beendet.";
			link.l1.go = "Abigile_kidnapping_4";
		break;
		
		case "Abigile_kidnapping_4":
			dialog.text = "Heilige Maria, ohne Sünde empfangen, bete für uns, die wir zu dir Zuflucht nehmen! Sag mir, ist er sicher? Ist seine Wunde schlimm?";
			link.l1 = "Machen Sie sich keine Sorgen, Fräulein! Richard ist nicht der Art von Mann, der es zulassen würde, dass einige Bastarde ihn einfach so töten. Er ruht und erholt sich jetzt. Er möchte, dass ich Sie zu ihm bringe. Dann werden Sie beide nach London segeln... bitte, beenden Sie den Brief, Fräulein, Sie eilen voraus.";
			link.l1.go = "Abigile_kidnapping_5";
		break;
		
		case "Abigile_kidnapping_5":
			dialog.text = "Ach, ja...Es tut mir leid(liest). Herr Knippel, ich bin bereit, mit Ihnen zu segeln. Ich brauche einen Tag, um meine Sachen zu packen und mit meinem Papa zu sprechen. Kommen Sie morgen zurück und ich werde mit Ihnen gehen.";
			link.l1 = "In Ordnung, Dame. Ich werde morgen hier sein. Mach dir keine Sorgen, ich und meine Mannschaft werden dich während unserer Reise vor allen Gefahren schützen.";
			link.l1.go = "Abigile_kidnapping_6";
		break;
		
		case "Abigile_kidnapping_6":
			DialogExit();
			npchar.greeting = "abigile_2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Holl_Gambit", "3-22");
			pchar.quest.Abigile_Kidnap.win_condition.l1 = "Timer";
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.hour  = 7.0;
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l2 = "location";
			pchar.quest.Abigile_Kidnap.win_condition.l2.location = "Villemstad_houseSp2";
			pchar.quest.Abigile_Kidnap.function = "AbigileGoToShip";
			pchar.questTemp.HWIC.Self = "AbigileWaitNextDay";
			SetFunctionTimerCondition("AbigileGoToShipOver", 0, 0, 3, false);//таймер 3 дня, ибо нефиг
		break;
		
		case "Abigile_kidnapping_7":
			DialogExit();
			chrDisableReloadToLocation = true;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SetAbigileToCabin", -1);//Аби в каюту к ГГ поставим
			AddQuestRecord("Holl_Gambit", "3-23");
			pchar.questTemp.HWIC.Self = "AbigileOnShip";
			pchar.quest.AbigileGoToShipOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("RemoveAbigileOver", 0, 0, 30, false);//таймер на 1 месяц, ибо нефиг
			pchar.quest.Abigile_died.win_condition.l1 = "NPC_Death";
			pchar.quest.Abigile_died.win_condition.l1.character = "Abigile";
			pchar.quest.Abigile_died.function = "AbigileDied";//специально для особо упоротых
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_8":
			DelLandQuestMark(npchar);
			dialog.text = "Ach, wie schade. Aber ich denke, dass ich noch eine Woche warten kann, wie ich es zuvor getan habe...";
			link.l1 = "Gut gesagt, Fräulein. Und um Ihre Wartezeit zu erleichtern, schlage ich vor, diese eher strenge Kabine gegen das Haus meines Freundes zu tauschen. Dort wird ein weiches Bett und feines Essen für Sie vorbereitet sein.";
			link.l1.go = "Abigile_kidnapping_9";
		break;
		
		case "Abigile_kidnapping_9":
			dialog.text = "Du bist so freundlich, Charlie. Danke. Es wird gut sein, wieder festen Boden unter den Füßen zu haben...Mir ist ganz übel nach all dem Herumgeworfenwerden auf den Wellen.";
			link.l1 = "Folgen Sie mir bitte, Fräulein.";
			link.l1.go = "Abigile_kidnapping_10";
		break;
		
		case "Abigile_kidnapping_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.questTemp.HWIC.Self = "AbigileInHouse";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_11":
			dialog.text = "Es freut mich, Sie zu treffen, John. Vielen Dank für Ihre freundliche Gastfreundschaft, meine Herren!";
			link.l1 = "...";
			link.l1.go = "Abigile_kidnapping_12";
		break;
		
		case "Abigile_kidnapping_12":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "SentJons_HouseF3_Room2", "barmen", "bar1", "ContinueWithMerdok", -1);
			pchar.questTemp.HWIC.Self = "AbigileInRoom";
			NextDiag.CurrentNode = "First time";
			RemovePassenger(Pchar, npchar);
			pchar.quest.RemoveAbigileOver.over = "yes";//снять таймер
			sld = characterFromId("Merdok");
			LAi_SetActorType(sld);//чтобы геймер сам с ним не заговорил
		break;
		
		case "Abigile_kidnapping_13":
			DelLandQuestMark(npchar);
			dialog.text = "Oh Charlie, ich habe Richard nur ein paar Mal gesehen und er hat mir nicht viel über das erzählt, was er tut.";
			link.l1 = "Ich bin ziemlich überrascht, dass er ein so großes Geheimnis vor der Frau verbergen würde, die er liebt... Fräulein, Richard ist nicht nur ein gewöhnlicher Kapitän. Er ist auch ein Sonderagent des englischen Geheimrats. Ein sehr wichtiger Mann, der mit heiklen Aufträgen befasst ist, die direkt vom Lordprotektor selbst angeordnet wurden. Im Moment ist seine Aufgabe darauf ausgerichtet, die Handelsmacht der Niederländischen Westindien-Kompanie in der Karibik zu zerstören.";
			link.l1.go = "Abigile_kidnapping_14"
		break;
		
		case "Abigile_kidnapping_14":
			dialog.text = "Herr, wovon reden Sie?";
			link.l1 = "Ja, Fräulein. Ihr geliebter Richard - mein Freund - ist ein sehr wichtiger Mann. Ich war immer stolz darauf, sein Freund zu sein, aber er ist selbst mit mir sehr geheimnisvoll geworden. Es ist offensichtlich, dass er auf einer geheimen Mission ist. Es tut mir sehr leid, dass diese Mission ihn nicht mit Ihnen treffen lässt.";
			link.l1.go = "Abigile_kidnapping_15";
		break;
		
		case "Abigile_kidnapping_15":
			dialog.text = "Charlie, du machst mir Angst. Bist du dir sicher, dass es ihm gut geht?";
			link.l1 = "Ich bin mir dessen sicher. Ich... Ich billige einfach nicht, wie er dich gerade behandelt. Ich verstehe, dass seine Aufgabe von größter Bedeutung ist und er seine Pflicht auch nicht für dich verraten kann.";
			link.l1.go = "Abigile_kidnapping_16";
		break;
		
		case "Abigile_kidnapping_16":
			dialog.text = "Oh, mein lieber Charlie... Ich werde auf Richard warten, bis zum Jüngsten Gericht wenn nötig. Vielleicht könnte ich über der Taverne bleiben... Ich kann nicht so lange von Johns Gastfreundschaft profitieren.";
			link.l1 = "Hör auf, Unsinn zu reden, Dame! Ihre Anwesenheit ehrt uns und mein Name ist nicht Charlie der Knippel, wenn ich die Verlobte meiner Braut von meinem lieben Freund Richard Fleetwood aus Haus und Heim vertreibe!";
			link.l1.go = "Abigile_kidnapping_17";
		break;
		
		case "Abigile_kidnapping_17":
			dialog.text = "Charlie... Ich bin sehr berührt von deiner Einstellung mir gegenüber. Ich bin nur ein gewöhnliches Mädchen und dazu noch eine Jüdin...";
			link.l1 = "Fräulein! Ich weiß, das ist törichtes Gerede, du bist eine feine christliche junge Frau! Und denke nicht einmal an Tavernen! Ich werde es mir nie verzeihen, wenn ich dir in meinem Dienst für Richard versagt habe.";
			link.l1.go = "Abigile_kidnapping_18";
		break;
		
		case "Abigile_kidnapping_18":
			dialog.text = "Danke dir, Charlie. Ich bin froh, dass du so ein... guter Mann bist.";
			link.l1 = "Es ist meine Pflicht, Fräulein. Jetzt tut es mir leid, aber ich muss gehen. Sie können jetzt frei in der Stadt herumlaufen, Sie müssen sich ziemlich einsam fühlen, eingesperrt in diesem Haus, habe ich recht?";
			link.l1.go = "Abigile_kidnapping_19";
		break;
		
		case "Abigile_kidnapping_19":
			dialog.text = "Nun... John ist sehr interessante Gesellschaft. Er kann stundenlang über seine Pulver, Mixturen und verschiedene... Krankheiten reden. Er ist auch ein höflicher und liebenswürdiger Mann. Außerdem gehe ich regelmäßig in die Kirche, der örtliche Priester ist recht freundlich... aber natürlich vermisse ich Richard sehr.";
			link.l1 = "Ich glaube, er wird bald zurück sein. Charlie der Knippel steht zu Ihren Diensten, falls Sie etwas brauchen.";
			link.l1.go = "Abigile_kidnapping_20";
		break;
		
		case "Abigile_kidnapping_20":
			DialogExit();
			pchar.questTemp.HWIC.Self = "MeetTonzag";
			pchar.quest.Meet_Tonzag.win_condition.l1 = "location";
			pchar.quest.Meet_Tonzag.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Meet_Tonzag.function = "TonzagMeetingInDange";
		break;
		
		case "Abigile_return":
			dialog.text = "Ich habe Gerüchte über Richard gehört... dass er verschwunden ist. Wissen Sie etwas darüber, Charlie?";
			link.l1 = "Ich tue es, Abigail. Es tut mir leid... Richard Fleetwood ist nach England gegangen und er wird nicht zurückkommen. Er bekam eine Beförderung oder Versetzung, so etwas... Wie auch immer, nach dem, was er dir angetan hat, möchte ich ihn nicht kennen.";
			link.l1.go = "Abigile_return_1";
		break;
		
		case "Abigile_return_1":
			dialog.text = "Ach, ich wusste, dass es so enden würde....(schluchzt) Warum habe ich nicht auf Papa gehört! Zumindest hätte er sich gefreut, wenn ich Lucas Rodenburg geheiratet hätte.";
			link.l1 = "Verzeihen Sie mir noch einmal, Fräulein...";
			link.l1.go = "Abigile_return_2";
		break;
		
		case "Abigile_return_2":
			dialog.text = "Wofür, Charlie? Du bist überhaupt nicht schuldig. Du warst nichts als nett zu mir!";
			link.l1 = "Um dir noch mehr schlechte Nachrichten zu überbringen. Ich bin gerade aus Curacao zurückgekehrt, Lucas Rodenburg wurde wegen Aufruhr und Hochverrat gegen die Republik verhaftet. Er wird in Ketten nach Amsterdam zurückgeschickt, um sich vor Gericht zu verantworten. Er versuchte Peter Stuyvesant, den Direktor der Gesellschaft, zu ermorden. Darüber hinaus versuchte er, den Gouverneur von Willemstad zu stürzen und wird des Mordes an mindestens einer anderen Person verdächtigt, daher bezweifle ich, dass der Statthalter ihm nur auf die Hand klopfen wird.";
			link.l1.go = "Abigile_return_3";
		break;
		
		case "Abigile_return_3":
			dialog.text = "Oh Gott! Was für ein Alptraum! Ich glaube, ich werde ohnmächtig! Charles, ist es wahr? Nein, bitte sag, dass es nicht so ist!";
			link.l1 = "Es tut mir leid, Madam, es wird schlimmer. Es hat sich während der Untersuchung von Rodenburgs Handlungen herausgestellt, dass der Pirat, der Ihre Fluyt versenkt hat, auf Befehl von Lucas Rodenburg gehandelt hat. Er hat einen eigenen privaten Krieg gegen den englischen Seeverkehr geführt. Es tut mir so leid, Abigail. Alle Männer, denen Sie hier in der Karibik begegnet sind, waren Lügner, Diebe und Mörder.";
			link.l1.go = "Abigile_return_4";
		break;
		
		case "Abigile_return_4":
			dialog.text = "Oh...Ich bin ruiniert. Charles... bitte... bring mich zurück nach Hause nach Willemstad. Ich brauche meinen Papa...";
			link.l1 = "Natürlich, liebe Miss. Leider gibt es hier in St. John's nichts für Sie. Geh, pack deine Sachen, verabschiede dich von John und wir werden sofort in See stechen.";
			link.l1.go = "Abigile_return_5";
		break;
		
		case "Abigile_return_5":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-57");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);//откроем комнату Аби
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.HWIC.Self = "AbiReturnHomeGo";
			pchar.quest.AbiReturn_Home.win_condition.l1 = "location";
			pchar.quest.AbiReturn_Home.win_condition.l1.location = "Villemstad_town";
			pchar.quest.AbiReturn_Home.function = "AbiGoInVillemstad";
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "Abigile_return_6":
			dialog.text = "Nein, Charlie, ich muss dir danken. Wenn du und John nicht gewesen wärtet, weiß ich nicht einmal, was mir passiert wäre. Ihr seid die einzigen ehrlichen Männer, die ich im Archipel getroffen habe.";
			link.l1 = "Hm... du bringst mich zum Erröten, Abigail. Ich habe dir gerne geholfen. Und es tut mir sehr leid für all das Durcheinander.";
			link.l1.go = "Abigile_return_7";
		break;
		
		case "Abigile_return_7":
			dialog.text = "Weißt du, Charlie, ich habe während unserer Reise nach Curacao viel nachgedacht. Jetzt ist alles klar - Richard Fleetwood, Mynheer Rodenburg - alles scheint nur ein schrecklicher Alptraum zu sein, der endlich vorbei ist. Ich bin wieder bei meinem Vater und wir können zu einem normalen Leben zurückkehren\nEs wird nicht einfach sein - wir haben kein Geld. Aber wir werden es schaffen, alles wird gut. Die Heilige Mutter wird sich um uns kümmern, sie vergisst ihre Kinder nie, auch meinen sturen alten Vater, der Ihren Sohn leugnet.";
			link.l1 = "Fräulein Abigail, ich werde Ihnen helfen.";
			link.l1.go = "Abigile_return_8";
		break;
		
		case "Abigile_return_8":
			dialog.text = "Helfen Sie uns? Aber wie, Charlie?";
			link.l1 = "Richard hat mir die Geschichte von deinem Schiffbruch und deiner Rettung erzählt. Außerdem weiß ich, dass dein Vater in der Lage war, seine Habseligkeiten auf einer unverzeichneten Insel zu verstecken. Ich werde sie finden und dein Geld zurückbringen.";
			link.l1.go = "Abigile_return_9";
		break;
		
		case "Abigile_return_9":
			dialog.text = "Oh Charlie... Weder ich noch mein Vater können dir sagen, wo diese verfluchte Insel ist... Wir sind keine Seeleute. Darüber hinaus war ich während des Angriffs um mein Leben besorgt, ich erinnere mich an nichts außer Blut und den Geruch des Todes.";
			link.l1 = "Abigail, versuche dich zu erinnern. Bitte, jedes Detail kann mir helfen, sogar die kleinsten. Ist vielleicht etwas passiert, bevor der Angriff stattgefunden hat? Wie sieht diese Insel aus?";
			link.l1.go = "Abigile_return_10";
		break;
		
		case "Abigile_return_10":
			dialog.text = "Insel... Sieht es aus wie eine Insel? Eine Bucht, Dschungel. Nichts ist mir wirklich aufgefallen. Oh, ich erinnere mich! Vielleicht wird es Ihnen helfen. Nicht lange vor dem Piratenangriff hatten wir eine Fluyt getroffen und ihren Kapitän begrüßt. Er wurde zu unserem Schiff eingeladen und hat mit unserem Kapitän zu Abend gegessen. Wir waren auch dort. Vielleicht weiß er über diese Insel Bescheid.";
			link.l1 = "Das ist ja etwas! Wie hießen das Fluyt und ihr Kapitän?";
			link.l1.go = "Abigile_return_11";
		break;
		
		case "Abigile_return_11":
			dialog.text = "Ich erinnere mich nicht, Charlie. Ich wirklich nicht...";
			link.l1 = "Versuche dich zu erinnern, Abi!";
			link.l1.go = "Abigile_return_12";
			pchar.questTemp.HWIC.Self = "SolomonHistory";
		break;
		
		case "Abigile_return_12":
			DialogExit();
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_return_13":
			dialog.text = "Wir werden auf dich warten. Hilf mir Charlie der Knippel. Du bist unsere einzige Hoffnung... Ich werde für dich beten! Gott segne dich!";
			link.l1 = "Ich bin auf dem Weg. Lebewohl, Abi. Lebewohl, Solomon.";
			link.l1.go = "Abigile_return_14";
		break;
		
		case "Abigile_return_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "ReturnAbiNormal", -1);
			pchar.questTemp.HWIC.Self = "SeekFleut";
			AddQuestRecord("Holl_Gambit", "3-58");
			AddLandQuestMark(characterFromId("Villemstad_PortMan"), "questmarkmain");
		break;
		
		case "Abigile_NoMoney":
			dialog.text = "Oh, lieber...was für ein Pech. Wir hatten gehofft, aber... danke trotzdem, Charlie, dass du versucht hast uns zu helfen, als niemand sonst es tun würde. Es scheint, dass dies das Schicksal ist, das Gott für mich vorgesehen hat.";
			link.l1 = "Auf Wiedersehen, Abigail. Ich hoffe, es geht dir gut.";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Abigile_Poor";
		break;
		
		case "Abigile_GiveMoney":
			dialog.text = "Ist es... ist es wahr? Hast du wirklich unser verlorenes Geld zurückgebracht? Oh, Charlie!";
			link.l1 = "Ja, es ist wahr. Ich habe es. Hier, nimm es. Das gehört alles dir.";
			link.l1.go = "Abigile_GiveMoney_1";
		break;
		
		case "Abigile_GiveMoney_1":
			AddMoneyToCharacter(pchar, -200000);
			pchar.quest.MakeAbiPoor.over = "yes"; //снять прерывание
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			dialog.text = "Wie kann ich Ihnen danken?! Wie?!";
			link.l1 = "Ich brauche keinen Dank, Abi. Es ist das Mindeste, was ich für dich tun könnte. Jetzt kannst du ein neues Leben ohne Rodenburgs, Fleetwoods oder andere merkwürdige Männer beginnen, die versuchen, dich auszunutzen. Ich bin sicher, dass dein Vater einen Weg finden kann, dieses Geld noch mehr Geld wachsen zu lassen... scheint wie eine vererbte Eigenschaft.";
			link.l1.go = "Abigile_GiveMoney_2";
		break;
		
		case "Abigile_GiveMoney_2":
			dialog.text = "Charlie, sei nicht so frech! Du hast so viel für mich getan, für mich und meinen armen Vater. Warum, ich habe mich an deine Anwesenheit in meinem Leben gewöhnt. Ich bete jeden Tag unermüdlich für dich und ich werde jeden kommenden Tag für dich und deine Crew zur heiligen Mutter beten! Du bist unser Schutzengel. Der Herr selbst hat dich zu unserer Familie geschickt, glaub es oder nicht\nBevor du gehst, möchte ich, dass du weißt, dass die Türen unseres Hauses jederzeit für dich offen stehen. Und... bitte, lass mich dich küssen, mein lieber Charlie...";
			link.l1 = "Nun... ja, sicher Abi...wenn du darauf bestehst.";
			link.l1.go = "Abigile_GiveMoney_3";
		break;
		
		case "Abigile_GiveMoney_3":
			DialogExit();
			npchar.greeting = "abigile_1";
			npchar.dialog.currentnode = "Abigile_AllRight";
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("AbiKiss", "");
		break;
		
		case "Abigile_Poor":
			dialog.text = "Gott segne dich, Charles. Für uns hat sich nichts geändert...Ich bettle um Krümel vor der Kirche.";
			link.l1 = "Bleiben Sie stark, Fräulein. Gott sei mit Ihnen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_Poor";
		break;
		
		case "Abigile_AllRight":
			dialog.text = "Charles, bist du es! Ich bin so froh, dich zu sehen! Bitte, setz dich! Ich werde Kaffee kochen!";
			link.l1 = "Ich freue mich auch, dich zu sehen, Abi. Und ich bin froh, dass es dir gut geht.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_AllRight";
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Woman_FackYou":
			dialog.text = "Ach, so ist es also?! Ich habe dich als meinen Gast empfangen und du hast beschlossen, mich zu berauben?! Wachen!!!";
			link.l1 = "Halte den Mund, dummes Mädchen.";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
