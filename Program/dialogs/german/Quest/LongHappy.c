// диалоги персонажей по квесту Долго и счастливо
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Was brauchst du?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
		break;
		
		// вестовой капитан в порту
		case "cureer":
			dialog.text = "Herr de Maure, welch ein Glück! Ich habe monatelang nach Ihnen gesucht!";
			link.l1 = "Meine Liebe, ich kaufe keine gefälschten Karten, zweifelhafte Informationen und hausgemachten Rum - danke! Oder bist du ein Kopfgeldjäger? Und wie viel ist es für meinen Kopf jetzt?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "Oh, Monsieur, ich... ich handle nicht mit Trödel und töte keine Menschen - berühren Sie das Schwert nicht, Sie werden es nicht brauchen. Ich meine es nicht böse! Alles ist viel prosaischer - ich bin der Kapitän eines Kurierschiffs. Ich verteile Post. Und für Sie habe ich eine wichtige Korrespondenz!";
			link.l1 = "Einen Brief? Wer ist der Absender, darf ich fragen?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "Einer Abt hat es mir gegeben und bat, es persönlich von Hand zu Hand an Kapitän de Maure zu übergeben. Ich hatte bereits alle Hoffnung verloren, Sie zu finden und wollte es im Hafenbüro in Saint Pierre hinterlassen, aber welch ein Glück - hier sind Sie!";
			link.l1 = "Ja, hier bin ich, ich warte - gib mir den Brief.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "Es gibt ein Problem... Der Abt hat gesagt, dass die Lieferung vom Empfänger bezahlt wird. Also schulden Sie neuntausendzweihundert Pesos.";
			link.l1 = "Für solches Geld hätte es mir auf offener See direkt in die Kabine gebracht werden sollen, zusammen mit dem Morgenkaffee! Den Brief kannst du behalten.";
			link.l1.go = "cureer_6";
			if (sti(pchar.money) >= 9200)
			{
				link.l2 = "Und warum habe ich keine Post ausgeliefert?! Das ist profitabler als Piraterie! Hier ist dein Silber, meine Liebe, gib den Umschlag.";
				link.l2.go = "cureer_4";
			}
		break;
		
		case "cureer_4":
			AddMoneyToCharacter(pchar, -9200);
			dialog.text = "Schön, mit Ihnen Geschäfte zu machen! Abt Benoit sendet Ihnen die besten Wünsche! Auf Wiedersehen Monsieur de Maure!";
			link.l1 = "";
			link.l1.go = "cureer_5";
		break;
		
		case "cureer_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			LongHappy_RecibeLetter();
		break;
		
		case "cureer_6":
			dialog.text = "Wie du wünschst. Ich werde den Umschlag im Hafenbüro abgeben. Aber das wird den Preis beeinflussen, ich warne dich. Und ja - Abt Benoit sendet dir die besten Wünsche.";
			link.l1 = "Der Brief von Abt Benoit? Warum haben Sie das nicht von Anfang an gesagt! Es muss wichtig sein!";
			link.l1.go = "cureer_7";
		break;
		
		case "cureer_7":
			dialog.text = "So holt es vom Hafenmeister ab. Vergesst nicht, im Voraus einen Kredit aufzunehmen. Lebewohl, Kapitän de Maure.";
			link.l1 = "Ich kannte Piraten, die aufrichtiger waren als du. Viel Glück, meine Liebe.";
			link.l1.go = "cureer_8";
		break;
		
		case "cureer_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.LongHappy = "portman";
		break;
		
		// испанский офицер в Сантьяго
		case "spa_officer":
			dialog.text = "Heiliger Vater, Sie sind heute früher als sonst. Bitte, Ihre Eskorte wartet. Und Sie, Senor de Maure - Vater Vincento hat erfahren, dass Sie in der Stadt sind und drängt Sie, ihn zum Abendessen zu begleiten.";
			link.l1 = "Ich fürchte, der Inquisitor wird alleine zu Abend essen. Ich hoffe, das verschlechtert seinen Appetit nicht. Und Abt Benoit wird ihm auch seine Gesellschaft vorenthalten. Du weißt, wer ich bin, also empfehle ich dir, uns ohne Konflikte passieren zu lassen und meine besten Wünsche an Pater Palotti zu richten.";
			link.l1.go = "spa_officer_1";
		break;
		
		case "spa_officer_1":
			if(sti(pchar.reputation.nobility) > 80 || sti(pchar.reputation.nobility) < 20) // провести учёт чести и известности
			{
				Notification_Reputation(true, 81, "low");
				dialog.text = "Ja, ich habe viel über dich gehört, und ich habe klare Anweisungen, die Stadt nicht in ein Blutbad zu verwandeln, wenn du stur bist. Du kannst durchgehen. Aber Vater Vincento wird... unzufrieden sein. Behalte das im Kopf.";
				link.l1 = "Sie haben vernünftig gehandelt, Monsieur. Ich werde irgendwie überleben, der Schmerz in meinem Herzen, verursacht durch die Unzufriedenheit des Vater-Inquisitors. Haben Sie einen schönen Abend!";
				link.l1.go = "spa_officer_2";
			}
			else
			{
				Notification_Reputation(false, 81, "low");
				Notification_Reputation(false, 19, "high");
				dialog.text = "Ja, ich habe von Ihnen gehört... viele interessante Dinge. Allerdings ist es gefährlich für die Gesundheit, solche Einladungen abzulehnen, senor. Ebenso wie das Entführen von Gästen des Vater Vincento. Haltet sie fest!";
				link.l1 = "Jeder hat seine Wahl getroffen. Es tut mir leid, dass es dazu kommen musste. Zu den Waffen, Caballero!";
				link.l1.go = "spa_officer_3";
			}
		break;
		
		case "spa_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload3_back", "none", "", "", "", 15.0);
			}
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "spa_officer_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				LAi_group_Attack(sld, Pchar);
			}
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterNationReputation(pchar, SPAIN, -20);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "Guests_block":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		// Ян Свенсон патер
		case "Svenson":
			dialog.text = "Charles, Glückwunsch! Du weißt - ich mochte dich immer, und Helen ist für mich wie eine Tochter, also freue ich mich für euch beide. Verdammt... in der Kirche eine Träne zu vergießen, ist alles, was ich je wollte, werde ich alt oder was?";
			link.l1 = "Alles ist gut, Jan, ich hätte fast am Altar geweint. Weihrauch, wahrscheinlich?";
			link.l1.go = "Svenson_1";
		break;
		
		case "Svenson_1":
			dialog.text = "Richtig, Kampfer, verdammt noch mal. Ich habe nachgedacht - warum meine Augen kneifen und meine Nase juckt! Gut, wir werden in Scharfstadt reden, Gladys umarmen und zu den anderen gehen. Sie haben solche Gesichter, als würden wir den Westfälischen Frieden unterschreiben.";
			link.l1 = "Danke, dass du hergekommen bist, Jan. Ich freue mich, dich zu sehen, und das bedeutet Helen viel.";
			link.l1.go = "Guests_block";
		break;
		
		// Ян Свенсон на Исла Тесоро
		case "Svenson_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Hier bist du endlich, Charles! Meine Korvette hat dich um fast einen Tag überholt - ein wahrhaft stolzer Moment.";
			link.l1 = "Du bist willkommen Jan, aber wo ist Gladys, und deine Frau?";
			link.l1.go = "Svenson_3";
		break;
		
		case "Svenson_3":
			dialog.text = "Ich habe Gladys auf einem Handelsschiff zurück nach Blueveld geschickt - sie billigt all diese rauschenden Feste nicht. Joanna konnte nicht kommen - ach, ich hatte keine Zeit, es dir auf Martinique zu erzählen! Stell dir vor - in meinem Alter werde ich ein rechtmäßiger Vater, wie findest du das? Schau, wenn du dich beeilst, werden unsere Nachkommen fast gleich alt sein, hahaha!";
			link.l1 = "Jan, meine Glückwünsche, das sind gute Nachrichten!!! Wir sollten darauf trinken!";
			link.l1.go = "Svenson_4";
		break;
		
		case "Svenson_4":
			dialog.text = "Auf jeden Fall! Aber zuerst, auf dich und deine bessere Hälfte! Hey, du da, halt die Klappe!!! Der alte Waldteufel muss eine Rede halten!\nKhe-khe... Also, unsere lieben Monsieur und Madame de Maure... Verdammt! Ich kann so nicht reden! Charles, Helen - ihr beide seid für mich wie meine eigenen Kinder, und ich weiß, dass es in diesem Raum niemanden gibt, der sich nicht über eure Verbindung freuen würde! Also lasst uns trinken, meine Brüder, auf das Glück unserer treuen Freunde, auf den fairen Wind in ihren Segeln und auf die Liebe der Lady Fortune, so stark wie ihre Gefühle füreinander!!! Prost!";
			link.l1 = "Prost! Danke Jan... oh, dieser Rum ist viel stärker als gewöhnlich... Was hat Nathan da reingemischt?";
			link.l1.go = "Svenson_5";
		break;
		
		case "Svenson_5":
			dialog.text = "Ich habe keine Ahnung, aber es scheint korrekt zu sein. Alter Falke ist im Allgemeinen ein Experte für Getränke. Komm schon, geh zu den anderen, ich muss Getränke für eine gute Hundertschaft von Seelen machen, die gierig darauf sind, ihren Durst zu stillen.";
			link.l1 = "Der Waldteufel schenkt Getränke aus - was für ein Anblick! Danke, dass du die Organisation der Party übernommen hast. Ich komme definitiv zurück, sobald ich bei jedem vorbeigeschaut habe - vielleicht braucht ja jemand Hilfe.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_6":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Svenson_6_1":
			dialog.text = "Alles in Ordnung, Charles?";
			link.l1 = "Perfekt, Jan!";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_7":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Und hier bist du endlich! Wie ist es auf Martinique gelaufen? Hast du das Gefühl, dass sich dein Leben für immer verändert hat?";
			link.l1 = "Es hat sich viel früher verändert, Jan. Aber alles lief überraschend gut. Wo ist Joahnna und...";
			link.l1.go = "Svenson_8";
		break;
		
		case "Svenson_8":
			dialog.text = "Helen? Das Mädchen stach in See, sobald sie herausfand, was wir vorhatten, und segelte zum Horizont. Sie übermittelte dir allerlei herzliche Glückwünsche, aber trotzdem... du hast ihr Herz gebrochen, oh das hast du wirklich getan. Aber alles wird gut, es ist nur die Jugend.";
			link.l1 = "Nun, das Herz will, was es will, du verstehst es.";
			link.l1.go = "Svenson_9";
		break;
		
		case "Svenson_9":
			dialog.text = "Ich tue es. Nun, Joahnna konnte nicht kommen, stell dir vor - in meinem hohen Alter werde ich ein legaler Vater, wie wäre das? Schau mal, wenn du dich beeilst, werden unsere Nachkommen fast das gleiche Alter haben, hahaha!";
			link.l1 = "Jan, meine Glückwünsche, das sind gute Nachrichten!!! Darauf sollten wir trinken!";
			link.l1.go = "Svenson_10";
		break;
		
		case "Svenson_10":
			dialog.text = "Auf jeden Fall! Aber zuerst, zu dir und deiner besseren Hälfte! Hey, du da, halt die Klappe!!! Der alte Waldteufel muss eine Rede halten!\nCharles und Mary, die gesamte Bruderschaft erhebt nun die Becher zu eurer Ehre! Das Glück wahrer Freunde erfreut die Seele eines jeden Seewolfs, fast so sehr wie die Pracht des spanischen Goldes, ha-ha! Segelt gut, und mögen die fairen Winde euch auf eurer familiären Reise folgen!!! Prost!";
			link.l1 = "Prost! Danke Jan... oh, dieser Rum ist viel stärker als sonst... Was hat Nathan da reingemischt?";
			link.l1.go = "Svenson_11";
		break;
		
		case "Svenson_11":
			dialog.text = "Ich habe keine Ahnung, aber es scheint richtig zu sein. Alter Falke ist generell ein Experte für Getränke. Los, geh zu den anderen, ich muss Getränke für eine gute Hundertschaft von Seelen machen, die gierig auf ihren Anteil sind.";
			link.l1 = "Diese Taverne muss definitiv umbenannt werden - 'Der Waldteufel stand selbst hier hinter dem Tresen'! Danke, Jan, ich komme definitiv zurück, sobald ich bei allen vorbeikomme - vielleicht braucht jemand Hilfe.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_12":
			dialog.text = "Wie geht es dir, Charles? Wie war die Hochzeit?";
			link.l1 = "Sehr herzerwärmend, Jan. Ich bin froh, dass wir es geschafft haben, uns alle hierher zu bringen. Sieht so aus, als würden die Fässer mit Rum von Hawk langsam ihren Boden zeigen, nicht wahr?";
			link.l1.go = "Svenson_13";
		break;
		
		case "Svenson_13":
			dialog.text = "Ja, das sind sie! Also, es ist Zeit, das zu öffnen, was du hierher gebracht hast. Und noch etwas - die Kerle, die mir zuerst geholfen haben, sind im Hinterzimmer viel zu betrunken geworden. Du scheinst noch auf den Beinen zu sein, Bräutigam - kannst du eine Kiste Sherry bringen?";
			link.l1 = "Sicher, sag mir einfach, wohin ich gehen soll. Vielleicht finde ich ein paar nüchterne Köpfe, die mir helfen können. Obwohl, die meisten meiner Leute sind wahrscheinlich schon so betrunken wie ein Stinktier.";
			link.l1.go = "Svenson_14";
		break;
		
		case "Svenson_14":
			dialog.text = "Der Wein wurde im Keller unter der Werft gelagert, erinnerst du dich? Hawk sagte, wir sollten ihn im hintersten Gang aufbewahren, ''für den Feiertag aufheben'' - sagt er. Er meint auch, dass dort die perfekte Temperatur und Luftfeuchtigkeit herrscht, sagt, es wäre der perfekte Ort für einen Weinkeller. Nun, er ist ein großer Snob.";
			link.l1 = "Er traf die richtige Entscheidung, Jan. Ich gehe, aber zuerst, sag mir - hast du meine Frau gesehen?";
			link.l1.go = "Svenson_15";
		break;
		
		case "Svenson_15":
			dialog.text = "Sie und Dannie sind irgendwohin gegangen. Lass die Mädchen reden, Charles, und wir müssen eine echte Party starten. Geh in den Keller, während ich mich ums Essen kümmere. Denn es riecht so, als würden wir bald Kohle statt Schafrippen essen!";
			link.l1 = "In Ordnung, geh und rette das Fleisch, ich bringe unseren Wein.";
			link.l1.go = "Svenson_16";
		break;
		
		case "Svenson_16":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			LongHappy_IslaTesoroToVineGo();
		break;
		
		case "Svenson_17":
			dialog.text = "Charles, Nathan, was ist passiert, habt ihr einen betrunkenen Streit angefangen?!";
			link.l1 = "Nein, Jan, wir haben zusammen gegen einige bewaffnete Cutter in den Verliesen gekämpft. Wir haben sie erledigt, aber sie waren nur Späher - das Haupttrupp ist direkt hinter uns!";
			link.l1.go = "Svenson_18";
		break;
		
		case "Svenson_18":
			dialog.text = "Trupp? Wovon sprichst du?! Marcus, komm her! Charles, komm schon, erzähl uns alles.";
			link.l1 = "Wie ich schon sagte: Es gibt einige Bastarde in den Verliesen unter der Werft. Gut bewaffnet. Nathan und ich haben gegen sie gekämpft und sie alle wie durch ein Wunder niedergestreckt. Aber es kommen noch mehr - Ich habe gehört, einer von ihnen wurde um Hilfe geschickt. Und ja, einer von ihnen erinnerte sich an einen gewissen Jacques.";
			link.l1.go = "Svenson_19";
		break;
		
		case "Svenson_19":
			DialogExit();
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "Terrax_7";
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay8");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Svenson_20":
			dialog.text = "Ich erkenne ihre Gesichter... diesen Kerl, und diesen Bastard, der neben der Tür liegt. Sie sind Schläger von Jacques dem Gutherzigen. Ich erinnere mich nicht an ihre Namen, aber ich weiß es sicher.";
			link.l1 = "So ist das Barbazons Schuld? Ist er verrückt oder was?!";
			link.l1.go = "Svenson_21";
		break;
		
		case "Svenson_21":
			dialog.text = "Ich weiß es nicht, aber es scheint, dass der Kindmann die Gelegenheit genutzt hat, um eine radikale Umgestaltung unter den Baronen der Bruderschaft zu arrangieren.";
			link.l1 = "In diesem Fall hoffe ich, dass er sich selbst zeigen wird - Ich träume schon so lange davon, ein paar Löcher in seinen Körper zu schlagen. Mistkerl, hat meine Hochzeit ruiniert, stell dir das vor! Auf geht's, auf die Straßen! Wir werden unseren Gästen einen angemessenen Empfang bereiten!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernReload");
		break;
		
		case "Svenson_22":
			dialog.text = "Und hier ist unser müder Held! Hah, Charles, das war etwas! Jacques, so eine Ratte! Schau, wie er alles arrangiert hat - er hätte fast Erfolg gehabt!";
			link.l1 = "Ja, wahrscheinlich hätten wir diesen Bastard töten sollen, als wir mit Jackman fertig waren. Aber es ist vorbei. Barbazon ist tot.";
			link.l1.go = "Svenson_23";
		break;
		
		case "Svenson_23":
			if (CheckAttribute(pchar, "questTemp.LongHappy.SvensonsShipSink")) dialog.text = "Nun, kann nicht sagen, dass es überhaupt vorbei ist - unser Leben geht weiter! Obwohl ich mich völlig zerstört fühle. Ich bin zu alt, um ins Meer zu springen von einem Scheißkerl, der mit Feuer bedeckt ist, und eine ganze Stunde zur Küste zu schwimmen, auf der Suche nach Haien. Ich hoffe, wir haben noch etwas Rum...";
			else dialog.text = "Nun, kann nicht sagen, dass es überhaupt vorbei ist - unser Leben geht weiter! Verdammt, ich fühle mich zehn Jahre jünger! Es ist lange her, seit ich das letzte Mal so gekämpft habe! Ich hoffe, deine Vorräte an Rum und Wein wurden während des Durcheinanders nicht gestohlen - wir müssen gut darauf trinken!";
			link.l1 = "Ja, ich würde auch trinken, aber zuerst muss ich die Residenz überprüfen, ich weiß nicht, ob man es dir gesagt hat oder nicht...";
			link.l1.go = "Svenson_24";
		break;
		
		case "Svenson_24":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				dialog.text = "Geht es um deinen indischen Kameraden? Ja, ich habe gehört, wie ist es passiert?";
				link.l1 = "Er sprang, um meine Frau und Dannielle vor einem Schuss von einem Bastard zu schützen. Wir sollten gehen, ich erzähle dir unterwegs.";
			}
			else
			{
				dialog.text = "Geht es um Nathan? Ja, ich habe gehört, nur nicht verstanden, wie es passiert ist?";
				link.l1 = "Er sprang, um unsere Frauen vor einem Schuss von einem Bastard zu schützen. Wir sollten gehen, ich erzähle dir unterwegs.";
			}
			link.l1.go = "Svenson_25";
		break;
		
		case "Svenson_25":
			DialogExit();
			DoQuestReloadToLocation("Pirates_townhall", "goto", "goto4", "LongHappy_DannyInResidence");
		break;
		
		case "Svenson_26":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Bleib stark, Charles. Es tut mir wirklich leid um deine Jungs. Heute sind viele gute Kerle gegangen, und für jeden von ihnen wird Barbazon in der Hölle mehr Öl in seinen Kessel bekommen.";
				link.l1 = "Es ergibt keinen Sinn ... verdammt! Es ist hart, Jan ... Ich habe bereits Freunde verloren, aber ich kann mich nicht daran gewöhnen. Ich weiß nicht, ob ich noch weitermachen kann.";
				link.l1.go = "Svenson_28";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Also dieser stille Kerl-Arzt? Es tut mir leid, Charles, aufrichtig. Er war ein guter Kerl.";
					link.l1 = "Ja, Jan, mir auch. Aber ich fürchte, die Welt der Wissenschaft hat viel mehr verloren als ich. Er war ein Genie... raffiniert, wie alle von ihnen, aber... verdammt...";
					link.l1.go = "Svenson_27";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sTemp = "your Indian guy";
					else sTemp = "Nathan";
					dialog.text = "Nun, es scheint vorbei zu sein. Heute sind viele gute Kerle gegangen und für jeden von ihnen wird Barbazon in der Hölle mehr Öl in seinen Kessel bekommen, aber "+sTemp+" wird gut sein und das ist das Wichtigste.";
					link.l1 = "Du hast recht, Jan, und das nimmt mir eine große Last von den Schultern. Wie geht es den anderen Baronen? Sind sie in Ordnung?";
					link.l1.go = "Svenson_32";
				}
			}
		break;
		
		case "Svenson_27":
			dialog.text = "Der letzte Dreck von Jacques Barbazon. Du hast recht, wenn wir ihn vorher getötet hätten, könnte alles anders sein.";
			link.l1 = "Aber was bringt es, die Vergangenheit zu bedauern? Die Vergangenheit kann nicht geändert werden. Wie geht es den anderen Baronen? Hat jeder überlebt?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_28":
			dialog.text = "Niemand kann sich daran gewöhnen. Lassen wir auf unsere Kerle trinken? Ich habe eine Flasche im Tisch gefunden, sie hat dieses Durcheinander wie durch ein Wunder überlebt.";
			link.l1 = "Gieß, ich... Verdammt... tausend Verdammnisse!";
			link.l1.go = "Svenson_29";
		break;
		
		case "Svenson_29":
			dialog.text = "Sag mir über sie. Dieser Sanitäter schien klug zu sein. Er drückte sich so weise aus.";
			link.l1 = "Er hat es getan. Aber ich fürchte, die Welt der Wissenschaft hat weit mehr verloren als ich. Er war ein Genie... raffiniert, wie sie alle. Der Meister der Wunder!";
			link.l1.go = "Svenson_30";
		break;
		
		case "Svenson_30":
			dialog.text = "Über den Indianer? Wo hast du ihn gefunden?";
			link.l1 = "Habe ihn aus dem Gefängnis auf Guadeloupe gerettet, fast sofort nach meiner Ankunft. Wirklich lustige und dumme Geschichte. Also, er blieb bei mir. Er entschied sich dazu, ich gab ihm die Freiheit, aber er blieb an meiner Seite - ich rettete ihn und er dachte, er schulde mir bis ans Ende seines Lebens. Knapp, seltsam gekleidet, aber treuer als jeder Ritter, er hatte auch ein Talent, er konnte eine Münze mit einem Musketenschuss in der Luft auf jede Entfernung treffen.";
			link.l1.go = "Svenson_31";
		break;
		
		case "Svenson_31":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nun, er hat dir die Schuld bezahlt, was kann ich sagen. Gerettet "+sld.name+" und Dannielle von diesem Bastard. Es scheint mir - das ist ein würdiges Ende für einen so tapferen Krieger.";
			link.l1 = "Das ist es, Jan. Lass uns auf das Gedenken der Gefallenen trinken... Mögen sie Frieden finden. Wie geht es den anderen Baronen? Geht es ihnen gut?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_32":
			dialog.text = "Diese Nacht hat uns teuer zu stehen gekommen. Ich weiß nicht einmal, wann die Brüderschaft sich von diesem Massaker erholen wird. Kindman hat Zeit und Ort des Angriffs perfekt gewählt. Er wäre fast erfolgreich gewesen - nur ein bisschen mehr und alles wäre vorbei gewesen. Aber wir haben viel weniger verloren als wir hätten können.";
			link.l1 = "";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) link.l1.go = "Svenson_33";
			else link.l1.go = "Svenson_35";
		break;
		
		case "Svenson_33":
			dialog.text = "Der Hai liegt in der Krankenstation, sein Schiff hat eine Salve von vierundzwanzig Pfund abbekommen. Er wurde über Bord geworfen, brach sich ein paar Rippen, schluckte Meerwasser, aber er lebt, in ein paar Tagen wird er wieder so gut wie neu sein.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry")) link.l1.go = "Svenson_34"; // был Венсан
			else link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_34":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "Bernard hat nur ein paar Kratzer abbekommen - er verteidigte die Küste und räumte die Katakomben aus. Jetzt ist er im Hafen, organisiert Krankenhäuser für die Verwundeten und Bestattungen für die Unglücklichen.";
			else dialog.text = "Bernard hatte Pech, er räumte die Häuser nach dem Angriff aus den Katakomben auf und lief in eine Bande dieser Bastarde in den Lagerhäusern. Er fing eine Kugel, direkt in den Kopf. Es ist eine Schande, er war ein guter Kapitän... Tyrex wird wütend sein, wenn er es herausfindet.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "Bernard hat nur ein paar Kratzer abbekommen - er verteidigte die Küste und räumte die Katakomben aus. Jetzt ist er im Hafen, organisiert Lazarette für die Verwundeten und Beerdigungen für diejenigen, die weniger Glück hatten.";
			else dialog.text = "Bernard hatte Pech, er räumte die Häuser nach dem Angriff aus den Katakomben auf und lief in den Lagerhäusern in eine Bande dieser Bastarde. Er fing eine Kugel, mitten in den Kopf. Es ist schade, er war ein guter Kapitän... Tyrex wird wütend sein, wenn er es herausfindet.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_36":
			dialog.text = "Über Hawk weißt du Bescheid. Dannie wird ihm mindestens einen Monat lang nicht erlauben, die Insel zu verlassen, das ist sicher. Er hatte ein Geschäft im Kopf... naja.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Svenson_37";
			else link.l1.go = "Svenson_38";
		break;
		
		case "Svenson_37":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free"))
			{
				dialog.text = "Marcus geht es wie immer gut. Sobald er an Land ging, begann er sofort, die Seelen der Wachen auszuschütteln, die all diesen Dreck übersehen haben. Ihm gelingt es immer noch, die Wiederherstellung der Ordnung in der Stadt zu befehlen. Eisenmann, nicht anders.";
				link.l1 = "Eisen ist weicher. Ich vermute, unser Baron ist aus einem Metall gemacht, das der Wissenschaft noch unbekannt ist, haha!";
			}
			else
			{
				pchar.questTemp.LongHappy.Terrax.Lost = "true";
				dialog.text = "Nur mit Marcus ist unverständlich, sein Schiff wurde geentert, aber die Überlebenden behaupten, dass er es geschafft hat, über Bord zu springen. Ich habe bereits die Beiboote losgeschickt, um die Bucht zu durchsuchen. Ich hoffe, es stellt sich heraus, dass unser Baron zäh genug ist, um nicht so leicht aufzugeben.";
				link.l1 = "Das ist schlecht, aber es ist zu früh, um über ihn zu weinen, Marcus würde uns nicht so leicht aufgeben. Lassen wir auf das Ergebnis der Suche warten.";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_38":
			if (CheckAttribute(pchar, "questTemp.LongHappy.TerraxShipSink"))
			{
				dialog.text = "Marcus schwamm ans Ufer, nachdem sein Schiff gesunken war. Nun, du weißt, Tyrex ist nicht einer von denen, die wegen solch einer Kleinigkeit ertrinken werden. Jetzt ist er irgendwo in der Stadt. Wahrscheinlich schüttelt er die Seelen der Wachposten aus, die all diesen Dreck übersehen haben. Eiserner Mann, nicht anders.";
				link.l1 = "Eisen würde sinken. Ich vermute, unser Baron besteht aus einem Material, das der Wissenschaft noch unbekannt ist, haha!";
			}
			else
			{
				dialog.text = "Marcus ist wie immer in Ordnung. Sobald er an Land ging, begann er sofort, die Seelen der Wachposten auszuschütteln, die all diesen Dreck übersehen haben. Er schafft es immer noch, die Wiederherstellung der Ordnung in der Stadt zu befehlen. Eiserner Mann, nicht anders.";
				link.l1 = "Eisen ist weicher. Ich vermute, unser Baron ist aus einem Metall gemacht, das der Wissenschaft noch unbekannt ist, haha!";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_39":
			dialog.text = "Das ist alles. Nun, es hätte schlimmer kommen können. Selbst deine Hochzeit, Charles, endete... kämpferisch. Das Wichtige ist, dass ihr beide am Leben seid. Ein kleiner Rat, im Allgemeinen... liebe... und wage es nicht, dafür zu kämpfen aufzugeben!";
			link.l1 = "Danke Jan. Danke euch allen... Ich muss zugeben, ich habe vergessen, dass wir mit einer Feier begonnen haben.";
			link.l1.go = "Svenson_40";
		break;
		
		case "Svenson_40":
			dialog.text = "Also, hier ist eine Erinnerung.";
			link.l1 = "Ja, das war eine... wilde Party.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum")) link.l1.go = "Svenson_41";
			else link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_41":
			dialog.text = "Oh ja, das war es sicher, warte mal. Da ist etwas - du schienst einen indischen Kerl bei dir zu haben, oder? Immer an deiner Seite oder schaut herum, als ob jemand dich anvisiert. Komisch gekleidet und sehr auffällig in großen Menschenmassen.";
			link.l1 = "Ja, Tichingitu, er ist gleich zu Beginn dieses Durcheinanders verschwunden, ich mache mir ehrlich gesagt Sorgen. Weißt du etwas?";
			link.l1.go = "Svenson_42";
		break;
		
		case "Svenson_42":
			pchar.questTemp.LongHappy.Tichingitu_Wife = "true";
			dialog.text = "Scheint so. Unser Barkeeper hat Lärm gemacht, dass seine Nichte entführt wurde, nur angeblich vor dem Angriff. Er sagt, sie hätten sie mit einer Art Indianer gesehen, er trug sie auf seiner Schulter entlang der Küste östlich der Stadt. Unter Kindmans Abschaum habe ich keine Indianer bemerkt, aber als ich davon hörte, erinnerte ich mich an deine, also sagte ich nichts. Du solltest gehen, nach ihm suchen oder so, bevor er in Schwierigkeiten gerät. Denn der Barkeeper droht, ihn zu töten, wenn er ihn zuerst findet. Er ist ein guter Kerl, aber für seine Nichte wird er jeden Kopf abschrauben.";
			link.l1 = "Ja, ich kenne die Sorte, mach dir keine Sorgen, und danke Jan, ich werde sofort nach ihm suchen.";
			link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_43":
			dialog.text = "Nun, im Allgemeinen, so etwas... Entschuldigung, ich bin schlecht in Reden. Und jetzt ist es noch schlimmer - diese Nacht hat uns alle ausgesaugt. Wir sollten uns alle mindestens einen Tag ausruhen - dann werden wir entscheiden, wie es weitergeht.";
			link.l1 = "Du hast recht, Jan. Ich sollte gehen, ich muss meinen Kopf erfrischen.";
			link.l1.go = "Svenson_44";
		break;
		
		case "Svenson_44":
			DialogExit();
			DoQuestReloadToLocation("Pirates_town", "reload", "reload3", "LongHappy_WifeInTown");
		break;
		
		case "Svenson_45":
			dialog.text = "Du siehst gut aus, Charles. Hast du gut geschlafen?";
			link.l1 = "Ja, man hat uns ein gemütliches Haus am Stadtrand gegeben. Ich dachte sogar, ich hätte den ganzen Wahnsinn, der gestern passiert ist, geträumt. Und da bist du Jan, du siehst furchtbar aus. Was ist noch passiert?";
			link.l1.go = "Svenson_46";
		break;
		
		case "Svenson_46":
			dialog.text = "Oh nein, es ist nichts, ich habe nur noch nicht geschlafen. Du weißt... die Stadt nach allem, was hier passiert ist, aufzuräumen, ist eine schwere Aufgabe.";
			link.l1 = "Wie geht es Dannie und Nathan? Wo sind alle?";
			link.l1.go = "Svenson_47";
		break;
		
		case "Svenson_47":
			dialog.text = "Ruhe haben. Störe sie nicht, Dannie hat alle gewarnt, dass sie heute Waffen ins Bett genommen hat... Dodson ist auf See, ist ausgezogen, um mehr Schiffe zu sichern, damit die Insel sicher ist und dies nicht wieder passiert, die anderen begraben die Verstorbenen im Norden der Insel.";
			link.l1 = "";
			link.l1.go = "Svenson_48";
		break;
		
		case "Svenson_48":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner") && !CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free")) dialog.text = "Marcus wurde noch nicht gefunden, aber wir können das schaffen, mach dir keine Sorgen. Du hast so viel für uns alle getan, also belaste dich nicht selbst. Tyrax wird früher oder später zurückkehren - wir werden ihn finden.";
			else dialog.text = "Marcus hat hier fertig und ist mit einer fremden Schaluppe nach Hispaniola gesegelt. Es ist notwendig, einige Fragen zu klären, die nach dem Tod von Barbazon aufgetaucht sind. Er hat Grüße und beste Wünsche für dich und deine Frau geschickt.";
			link.l1 = "";
			link.l1.go = "Svenson_49";
		break;
		
		case "Svenson_49":
			dialog.text = "Nun, die Brüder haben diesen Schlag überstanden. Bald werden wir stärker auferstehen, als wir je waren. Kindman und Jackman haben unsere Einheit zu lange erschüttert, jetzt sind sie weg und mein Herz fühlt - wir werden die Karibik mehr als einmal zucken lassen. Das goldene Zeitalter kommt für diejenigen, denen Gesetze und Könige nicht nett sind, merkt euch meine Worte.";
			link.l1 = "Das wäre schön. Ich bin mir nicht sicher, ob ich die alte Welt noch ertragen kann. Ich hätte nie gedacht, als ich hierher kam, dass ich mich in die Freiheit des Meeres verlieben würde, diese verrückten Farben von Sonnenuntergängen und Sonnenaufgängen, dass ich die beste Frau der Welt finden und... Freunde, denen ich mein Leben anvertrauen würde.";
			link.l1.go = "Svenson_50";
		break;
		
		case "Svenson_50":
			dialog.text = "Nun, Sie kennen den Kurs, treffen Sie einfach Ihre Entscheidung. In unseren Häusern sind Sie immer willkommen.";
			link.l1 = "Danke, Jan. Das bedeutet mir viel.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete") link.l1.go = "Svenson_51";
				else link.l1.go = "Svenson_54";
			}		
			else link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_51":
			pchar.questTemp.LongHappy.Baron = "true";
			dialog.text = "Aber zuerst gibt es noch etwas Wichtiges. Charles, während du geschlafen hast, haben wir uns versammelt und haben entschieden\nDa Barbazon tot ist, braucht die Bruderschaft einen neuen Baron. Da die Mehrheit von uns hier war und die Entscheidung einstimmig getroffen wurde, ist es so. Herzlichen Glückwunsch - du bist der neue Baron von Le Francois. Aber warte ... Ich verstehe - du bist eine weltliche Person und hast keine Zeit, Geschäfte an diesem schönen Ort zu führen, also haben wir dort eine vertrauenswürdige Person hingesetzt und du machst, was du willst. Denk nur daran - deine Stimme ist jetzt in der Bruderschaft.";
			link.l1 = "Jan, ich... Ich bin sprachlos... Es ist eine große Ehre, ich weiß nicht einmal...";
			link.l1.go = "Svenson_52";
		break;
		
		case "Svenson_52":
			dialog.text = "Los geht's! Du hast dich damals bei Tyrex perfekt bewährt, und dann mit dieser ganzen Geschichte mit Sharps Vermächtnis. Du bist ein Segen Gottes. Für dich wird sich nichts ändern - mache wie geplant, und in deiner Abwesenheit wird dein Mann alle Angelegenheiten übernehmen. Es gibt einen vielversprechenden Kerl namens Jan David, er ist einer der Freibeuter. Ein ehrlicher Franzose mit brillantem Verstand und er weiß, wie man ihn benutzt, wie du. Aber es wird einige Zeit dauern, bis ich ihn finde - es scheint, er wurde von den Spaniern gefangen genommen, aber das lässt sich lösen, mach dir keine Sorgen. Ich werde dafür sorgen, dass er dir deinen Anteil schickt, sobald er sich mit dem Geschäft vertraut gemacht hat.";
			link.l1 = "Ich hätte wirklich nicht erwartet, dass alles so sein würde. Nun, da du dich bereits so entschieden hast, dann sei es so. Der Piratenbaron Charles de Maure!";
			link.l1.go = "Svenson_53";
		break;
		
		case "Svenson_53":
			dialog.text = "Es lebe der Baron! Wenn jemand den Namen verdient, dann du. Trage ihn mit Stolz, und vergiss nicht - du bist jetzt einer von uns, egal wie schön die Uniform ist, die du trägst, hier, direkt darunter schlägt das Herz eines echten Piraten.";
			link.l1 = "Ich weiß nicht, vielleicht übertreibst du... Aber ich werde alles tun, um dein Vertrauen zu rechtfertigen.";
			link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_54":
			dialog.text = "Was wirst du jetzt tun? Gehst du zurück nach Europa, zurück zu deinem Vater, um ihm deine Frau vorzustellen?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") || CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				link.l1 = "Ja, aber zuerst muss ich jemandem Lebewohl sagen... Sie wissen, was ich meine.";
				link.l1.go = "Svenson_56";
			}
			else	
			{
				link.l1 = "Vielleicht nicht so bald. Noch einmal werde ich durch das Archipel segeln, ich möchte diese Luft der Freiheit zum letzten Mal atmen.";
				link.l1.go = "Svenson_55";
			}
		break;
		
		case "Svenson_55":
			dialog.text = "Nun, du hast ein Schiff, du kannst jederzeit nach Hause segeln, wenn du möchtest.";
			link.l1 = "Ich hoffe es. Danke Jan, danke euch allen und bis später, mein alter Freund! Grüße die Falken und den Hai!";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_56":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died")) sTemp = "They deserve";
			else sTemp = "He deserve";
			dialog.text = "Ja, es ist hart, aber wir müssen das tun. Zum Meer?";
			link.l1 = "Nein, ich werde nach Antigua segeln. "+sTemp+" um in Frieden an einem Ort zu ruhen, der für eine Weile unser Zuhause wurde.";
			link.l1.go = "Svenson_57";
		break;
		
		case "Svenson_57":
			dialog.text = "Sag auch ein paar nette Worte von mir. Und mach dir keine Sorgen - wir können es von jetzt an alleine schaffen. Alles wird gut.";
			link.l1 = "Danke Jan. Bis bald mein alter Freund! Grüße die Falken und den Hai!... Nun, es geht nach Antigua.";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_58":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_IslaMarryComplete", 10.0);
		break;
		
		case "Svenson_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Svenson_";
		break;
		
		// Глэдис
		case "Gladis":
			dialog.text = "Junger Mann, du bist heute noch mehr in meinen Augen gewachsen. Du hast so viel für Helen getan, dass keine Worte des Dankes ausreichen werden. Ich hoffe nur, dass du weiterhin auf sie aufpassen wirst. Wenn ihr Vater noch am Leben wäre und das sehen könnte, wie glücklich er gewesen wäre... oh, es tut mir leid.";
			link.l1 = "Es ist in Ordnung, Gladys. Du hast den Archipel überquert, um Helen an diesem Tag zu unterstützen. Wir schätzen deinen Besuch mit Jan wirklich sehr, danke.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер Мэри
		case "forge":
			dialog.text = "Herr de Maure, ich entschuldige mich für die Vertraulichkeit, aber ich werde es so sagen - Charles, mein Freund, ich freue mich aufrichtig für dich! Wenn ich etwas für dich oder deine Braut tun kann, sag es einfach!";
			link.l1 = "Ich danke Ihnen, Baron, ich bin so glücklich, und die Weinberge, die mein Vater als Mitgift wollte, ich denke, ich kann mich erlösen - glücklicherweise hat sich meine finanzielle Situation während meines Aufenthaltes in der Neuen Welt erheblich verbessert.";
			link.l1.go = "forge_1";
		break;
		
		case "forge_1":
			dialog.text = "Ja, ich nehme an, du kannst dir so ziemlich alles leisten, was du willst, Charles. Entschuldigen Sie mich, aber ich werde meinen Beitrag als repräsentativer Vater leisten - Heute schreibe ich meinem guten Freund, dem Finanzminister. Ihre Auserwählte wird den Adelstitel erhalten, und, ich denke, wir werden für sie ein gutes Gut finden, sagen wir in der Gascogne, unter denen, die wegen Schulden beschlagnahmt wurden, und es ihr rückwirkend zuweisen. Also wird niemand wagen zu sagen, dass der Chevalier de Monper eine Frau mit niedriger Position gefunden hat!";
			link.l1 = "Ich glaube nicht, dass ich mir über solche Klatschgeschichten Sorgen mache, aber danke, Baron. Trotzdem sollten Sie nicht";
			link.l1.go = "forge_2";
		break;
		
		case "forge_2":
			dialog.text = "Ich sollte mehr als das! Geh jetzt, Charles, teile deine Aufmerksamkeit mit den restlichen Gästen. Und noch einmal, nimm meine aufrichtigsten Glückwünsche an!";
			link.l1 = "Ich und meine Frau danken Ihnen. Auf Wiedersehen, Baron.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер ГГ
		case "forge_3":
			dialog.text = "Herr de Maure, ich entschuldige mich für die Vertrautheit, aber ich werde es so sagen - Charles, mein Freund, ich freue mich aufrichtig für dich! Wenn ich etwas für dich oder deine Braut tun kann, sag es einfach!";
			link.l1 = "Danke, Baron, aber du hast schon viel für mich getan. Es reicht für uns, dass du auf die Einladung reagiert hast.";
			link.l1.go = "forge_4";
		break;
		
		case "forge_4":
			dialog.text = "Wie könnte ich nicht geantwortet haben, Charles! Aber hör zu - Ich möchte dir und deiner wunderschönen Braut ein würdiges Geschenk machen, aber mir fällt nichts ein, was du dir nicht selbst mit Geld oder einem Schwert besorgen könntest. Daher werde ich meinem Freund, dem Finanzminister in Paris, schreiben, und bis du in Europa ankommst, wirst du erwartet, das königliche Reskript der Erhebung des Namens de Monper in den Titel der Barone de Monper zu unterzeichnen! Nein, kein Wort, das ist das Mindeste, was ich für dich tun kann.";
			link.l1 = "Ich weiß nicht mal, was ich sagen soll, Baron... Vater wird so glücklich sein. Ich danke Ihnen aufrichtig.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже гость
		case "forge_5":
			dialog.text = "Charles, bitte, akzeptiere meine aufrichtigen Glückwünsche! Deine Auserwählte ist einfach ein Wunder! Ich denke, heute hat die koloniale Mode einen starken ... Stoß in eine neue Richtung erhalten. Deine Originalität hat mich schon immer fasziniert! Mögen du und deine schöne Hälfte auf ewig glücklich leben!";
			link.l1 = "Danke, Baron. Sie haben uns mit Ihrem Besuch geehrt.";
			link.l1.go = "forge_6";
		break;
		
		case "forge_6":
			dialog.text = "Wie könnte ich fernbleiben, mein Freund? Wir haben gemeinsam viel durchgemacht und ich bin stolz darauf, dich meinen Freund zu nennen, Charles. Denk daran - meine Türen sind immer für dich geöffnet, egal was passiert.";
			link.l1 = "Die Türen der Familie de Monper werden Ihnen immer offen stehen, Baron.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер Мэри
		case "puancie":
			dialog.text = "Charles, mein Freund, dies ist ein sehr wichtiger Tag, und ich bin froh, dass du mich eingeladen hast, ihn mit dir zu teilen. Du und ich haben einen langen und schwierigen Weg hinter uns, und zum Stellvertretenden Vater von Mademoiselle... bitte, verzeih mir - Madame de Maure zu werden, ist eine Ehre für mich, glaube mir. Ich wünsche dir von ganzem Herzen Glück!\nUnd bitte, lass mich wissen, wann du nach Europa gehst - ich, als der stellvertretende Vater deiner Auserwählten, werde deinem Vater alle notwendigen Hochzeitsgeschenke schicken. Glaub mir, niemand wird sagen, dass die Braut des Chevalier de Monper arm oder unwürdig ist!";
			link.l1 = "Wenn ich fragen darf, Chevalier, ein paar Meilen nördlich des Anwesens de Monper, gibt es gute Weinberge, sie gehören zur Familie La Brigne und ich...";
			link.l1.go = "puancie_1";
		break;
		
		case "puancie_1":
			dialog.text = "Kein Wort mehr, mein Freund, kein Wort! Ich werde sofort meinem Bevollmächtigten in Lyon schreiben - bei Ihrer Ankunft werden diese Weinberge Ihrem Auserwählten gegeben.";
			link.l1 = "Danke, Chevalier. Du hast recht - unsere... Freundschaft, hat... viel durchgemacht. Aber, ich bin wirklich froh, dass du diesen Tag mit uns geteilt hast. Wir sehen uns und danke nochmals!";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер ГГ
		case "puancie_2":
			dialog.text = "Charles, mein Freund, dies ist ein sehr wichtiger Tag, und ich bin froh, dass du mich eingeladen hast, ihn mit dir zu teilen. Wir haben einen langen und schwierigen Weg zurückgelegt, und heute auf deiner Hochzeit Zeugnis abzulegen, ist eine Ehre für mich. Mit ganzem Herzen wünsche ich dir Glück! Und lass mich wissen, wann du nach Europa gehst - Ich werde deinem Vater würdige Hochzeitsgeschenke schicken.";
			link.l1 = "Es besteht keine Notwendigkeit dafür, Chevalier. Danke, dass Sie meiner Einladung gefolgt sind.";
			link.l1.go = "puancie_3";
		break;
		
		case "puancie_3":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry2", 50);
			TakeNItems(pchar, "jewelry3", 50);
			TakeNItems(pchar, "jewelry4", 50);
			dialog.text = "Wie ich schon sagte - es ist eine Ehre für mich! Aber warte, mein Freund, ich möchte dir zu diesem Anlass etwas präsentieren - ich bin sicher, das wird sowohl dir als auch deiner Auserwählten gefallen. Schöne Steine aus unseren Minen in Neu-Guiana - such ihnen einen anständigen Rahmen und Madame de Maure wird selbst beim königlichen Empfang strahlen! Wenn du sie natürlich dazu überreden kannst, ein Kleid zu tragen...";
			link.l1 = "Oh, Sie sollten wirklich nicht, Chevalier. Danke nochmal.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси гость
		case "puancie_4":
			dialog.text = "Charles, mein Freund, lass mich dir gratulieren! Wir haben einen langen und schwierigen Weg hinter uns, und ich bin aufrichtig froh, heute hier zu sein. Unser Herr ist Zeuge - du verdienst dein Glück! Behalte es und beschütze es - ich wünsche dir viele glückliche Jahre!";
			link.l1 = "Danke, Chevalier, meine Frau und ich sind sehr dankbar.";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей патер
		case "fadey":
			dialog.text = "Charles, was für eine Feier, und wie viele wichtige Leute! Lasse mich dir von ganzem Herzen Glück und gute Gesundheit wünschen, und Kinder zur Freude! Wie wir sagen - 'gor'ko'!";
			link.l1 = "Danke dir, Fadey, du hast mir die Ehre erwiesen, zu kommen.";
			link.l1.go = "fadey_1";
		break;
		
		case "fadey_1":
			dialog.text = "Aber, ich verstehe nicht ganz, warum es so viele Leute gibt, als ob wir nicht eine Ehe, sondern einen großen Handelsvertrag abschließen, und immer noch nicht genug Bier und Wodka für meinen Geschmack hier... haha! Nun, ich mache nur Spaß, Charles, warum bist du so blass geworden? Gib mir eine Umarmung, du verheirateter Kapitän!";
			link.l1 = "Wow... Fadey, du bist stark wie ein Bär!";
			if (CheckAttribute(pchar, "questTemp.Persian"))
			{
				if (pchar.questTemp.Persian == "time" || pchar.questTemp.Persian == "end") link.l1.go = "fadey_2";
				else link.l1.go = "Guests_block";
			}
			else link.l1.go = "Guests_block";
		break;
		
		case "fadey_2":
			GiveItem2Character(pchar, "blade_22");
			GiveItem2Character(pchar, "blade_23");
			GiveItem2Character(pchar, "blade_24");
			Log_Info("You got three Persian sabres");
			PlaySound("interface\important_item.wav");
			dialog.text = "Warte, Charles, geh nicht weg - es ist nicht würdig, dass der Gast ohne Geschenke zur Hochzeit kommt. Hier, nimm sie. Ich weiß - du hast versucht, all diese Klingen zu finden und einige haben dir offensichtlich gefallen. Also akzeptiere sie - hänge sie in einem Familiengut auf und erinnere dich mit einem freundlichen Wort an Fadey Moskovit!";
			link.l1 = "Das ist ein wahres Geschenk! Danke dir, Fadey. Das sind in der Tat wundervolle Waffen, und sie werden ihren rechtmäßigen Platz im Anwesen de Monper einnehmen, das verspreche ich!";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей гость
		case "fadey_3":
			dialog.text = "Charles, so eine Feier und wie viele wichtige Leute! Lass mich dir von ganzem Herzen Glück und gute Gesundheit wünschen, und Kinder zur Freude! Wie wir sagen - 'gor'ko'! Gib mir eine Umarmung, du verheirateter Kapitän!";
			link.l1 = "Wow... Fadey, du bist stark wie ein Bär!";
			link.l1.go = "Guests_block";
		break;
		
		// Проспер Трубаль
		case "Prosper":
			dialog.text = "Charles, ich konnte es nicht verpassen, ich gratuliere dir und deiner Auserwählten von ganzem Herzen! Sei glücklich! Weißt du, vor ein paar Monaten habe ich meine Tochter verheiratet, für einen guten Menschen und aus Liebe, aber ehrlich gesagt, war ich enttäuscht, dass du es nicht warst... Na gut... worüber rede ich überhaupt - Glückwunsch! Mögt ihr glücklich bis ans Ende eurer Tage leben!";
			link.l1 = "Danke, Prosper, ich bin froh, dass du gekommen bist.";
			link.l1.go = "Guests_block";
		break;
		
		// Тичингиту
		case "Tichingitu":
			dialog.text = "Herzlichen Glückwunsch, Kapitän! Ein seltsames Ritual, aber schön - Tichingitu hat es gefallen. Obwohl, der Kapitän sollte einfach seine Squaw entführen und ein Lösegeld an ihre Verwandten schicken.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Nun, in gewisser Weise habe ich das getan und es ist nur eine Formalität. Danke, mein Freund!";
			else link.l1 = "Nun, in gewisser Weise habe ich das getan, und es ist nur eine Formalität. Danke, mein Freund! Du und ich werden mehr in Scharfstadt reden - es wird viel weniger offiziell und mehr aufrichtiger Spaß sein, das verspreche ich!";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Feuerwasser wieder? Tichingitu kann nicht sagen, dass er es mag. Vielleicht wird die Feier des Enterns besser sein, oder zumindest das Tanzen um ein Lagerfeuer?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "Ich hoffe doch, es wird nicht zu Tänzen um Lagerfeuer kommen, lange bevor das Ende naht, und ich würde lieber ohne Entern auskommen. Gut, sei geduldig - nur noch ein kleines Stück, und wir gehen sofort zur Taverne.";
			else link.l1 = "Ich fürchte, es wird lange vor dem Ende zu Tänzen um Lagerfeuer kommen, und ich würde lieber ohne Entern auskommen. Gut, sei geduldig - nur noch ein bisschen, und wir segeln sofort nach Scharfstadt.";
			link.l1.go = "Guests_block";
		break;
		
		case "Tichingitu_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Kapitän, nochmals Glückwunsch! Tichingitu mag diese Feier mehr als die vorherige. Der Kapitän weiß, wie man Freunde auswählt - hier ist mehr Aufrichtigkeit, weniger Heuchelei und falsches Haar.";
			link.l1 = "Danke dir, mein Freund! Trink nur nicht das Feuerwasser - es ist hier sehr hart.";
			link.l1.go = "Tichingitu_4";
			link.l2 = "Danke dir, mein Freund! Lass uns einen trinken? Ich weiß, du magst es nicht, aber heute solltest du es versuchen!";
			link.l2.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			pchar.questTemp.LongHappy.Tichingitu_Rum = "true";
			dialog.text = "Tichingitu mag kein Feuerwasser, aber wenn der Kapitän darauf besteht, ist es heute möglich. Auf Ihr Glück und Ihre Squaw!";
			link.l1 = "Und dir, Tichingitu! Auf deine Freundschaft und Loyalität!";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			DialogExit();
			npchar.dialog.currentnode = "Tichingitu_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "LongHappy_57";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tichingitu_4_1":
			dialog.text = "Schöne Party, Kapitän.";
			link.l1 = "Ich bin froh, dass Sie zufrieden sind.";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Kapitän, kam heraus, um die Sterne zu betrachten? Die Nacht verspricht sehr schön zu werden. Tichingitu liebt die Nacht über dem Meer. Es ist sehr friedlich.";
			link.l1 = "Froh zu sehen, dass du noch stehst, mein Freund! Nathaniel und ich brauchen deine Hilfe - die Kerle in der Taverne haben keine Getränke mehr, wir müssen ein paar Kisten Getränke aus dem Lager unter der Werft holen.";
			link.l1.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_6":
			dialog.text = "Bleib vorne, Kapitän. Tichingitu folgt dir, wie immer.";
			link.l1 = "In Ordnung, lass uns gehen!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Tichingitu_8":
			dialog.text = "Kapitän, es gibt Leute, und sie sind bewaffnet, Tichingitu hört das Klirren ihrer Waffen und es wird von Sekunde zu Sekunde lauter. Mir gefällt das nicht. Lass uns verstecken.";
			link.l1 = "Los geht's, Kumpel - das ist Sharptown, hier gehen die Leute sogar mit Pistolen auf die Toilette. Hey Nathan... na, verdammt! Da ist eine Flasche weg. Wenn das so weitergeht, zerbrichst du alle Flaschen! Steh auf deinen Füßen verdammt noch mal! Ha-Ha!";
			link.l1.go = "Tichingitu_9";
		break;
		
		case "Tichingitu_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LongHappy_SetBandosInDungeon();
		break;
		
		case "Tichingitu_10":
			dialog.text = "Kapitän... du... Tichingitus Kopf wankt wie ein Mast im Sturm. Was ist passiert?";
			link.l1 = "Ich wollte dich dasselbe fragen! Wo warst du die ganze Zeit?!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "Tichingitu ist vor einer Stunde wegen den Schreien dieses Mädchens aufgewacht. Sie rannte fast nackt am Strand entlang und schrie etwas über Entführer und Wilde... Aber hier sind wir außer uns niemand. Hast du Wasser? Nicht wieder das feurige, Tichingitu hasst es jetzt?";
			link.l1 = "Es gab irgendwo eine Flasche, wenn ich sie nicht in einer Schlacht verloren habe... hier bitte. Wie hast du das geschafft? Ihr Onkel, ein örtlicher Barkeeper, sucht nach einem Indianer, der seine Nichte entführt hat, und droht ihm den gefiederten leeren Kopf abzureißen. Wen glaubst du, meint er damit?";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "Tichingitu erinnerte sich. Sie half dem Waldteufel in der Taverne bei der Hochzeit. Wir tranken Feuerwasser mit dir, und Tichingitu wollte mehr. Und dann, diese Squaw... sie war so süß und... Kapitän, ich glaube, ich erinnere mich! Tichingitu wollte sie heiraten... Er wollte ein Kanu bauen und sie mitnehmen... Geister der Barmherzigkeit! Sehr böse Leute kamen mit Feuerwasser. Vielleicht die Dämonen oder böse Geister! Tichingitu wird nie wieder ...";
			link.l1 = "Sie wegnehmen? Ein Kanu bauen?! Ahah, du bist ein Romantiker, mein Freund... Ha-ha... ha-ha-ha-ha-ha-ha oh, ich kann nicht aufhören... Ich kann nicht aufhören zu lachen!";
			link.l1.go = "Tichingitu_13";
		break;
		
		case "Tichingitu_13":
			dialog.text = "Kapitän, Tichingitu hat die Squaw gestohlen, ja... aber, könnten wir, also... jetzt nicht heiraten? Sie ist... laut, wie ein Papagei, und... nicht so schön.";
			link.l1 = "Ja, mein Freund, die Frauen, die die ganze Nacht Spaß haben, sind am Morgen ein erbärmlicher Anblick. Mach dir keine Sorgen, Held-Liebhaber, wir werden uns etwas einfallen lassen. Los, wir müssen zurück nach Scharfstadt, du hast deine Feiertagsunterkunft verpasst...";
			link.l1.go = "Tichingitu_14";
		break;
		
		case "Tichingitu_14":
			dialog.text = "Eine Enterung? Der Kapitän hat zuvor von einer Schlacht gesprochen. Tichingitus Gedanken gehorchen immer noch nicht. Was ist in der Stadt passiert?";
			link.l1 = "Ein echter Kampf an Land und auf See. Die Kanonen schossen die ganze Nacht, ich vermute, sie wurden wahrscheinlich sogar in San Jose gehört. Allerdings, du warst mit einer anderen 'Schlacht' beschäftigt, alles ist gut, ich kann es verstehen... Los, ich erzähle dir alles unterwegs.";
			link.l1.go = "Tichingitu_15";
		break;
		
		case "Tichingitu_15":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("LH_waitress");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.longhappy_shoregirl1.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl1.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_shoregirl1.function = "LongHappy_ReturnShoreGirl";
		break;
		
		case "Tichingitu_16":
			dialog.text = "Danke, Kapitän... Tichingitu wird niemals...";
			link.l1 = "Ja, 'der Hengst von den fernen Ebenen', du solltest definitiv nicht mehr trinken. Geh schlafen. Mir fallen auch schon die Füße ab.";
			link.l1.go = "Tichingitu_17";
		break;
		
		case "Tichingitu_17":
			DialogExit();
			npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			LAi_SetImmortal(npchar, false);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			LAi_SetOfficerType(npchar);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			npchar.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_55";
			ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Tichingitu_18":
			dialog.text = "Kapitän, nochmals herzlichen Glückwunsch! Tichingitu mag diese Feier mehr als die vorherige. Der Kapitän weiß, wie man Freunde wählt - hier gibt es mehr Aufrichtigkeit, weniger Heuchelei und falsches Haar.";
			link.l1 = "Und viel mehr Feuerwasser. Übrigens, wirst du mit mir trinken? Ich weiß, dass du es nicht magst, aber wir haben einen ungewöhnlichen Anlass!";
			link.l1.go = "Tichingitu_19";
		break;
		
		case "Tichingitu_19":
			dialog.text = "Tichingitu mag kein Feuerwasser, aber wenn der Kapitän darauf besteht, ist es heute möglich. Auf dein Glück, und deine Squaw! Mögt ihr denselben Weg gehen, und mögen Sonne und Mond immer darauf scheinen.";
			link.l1 = "Danke dir, mein Freund. Prost auf dich, Tichingitu! Auf unsere Freundschaft!";
			link.l1.go = "Tichingitu_4";
		break;
		
		// губернаторы
		// Сен Пьер
		case "FortFrance_Mayor":
			if (pchar.questTemp.GoldenGirl == "end")
			{
				dialog.text = "Großartig ... Feier, ich bin sehr glücklich für dich, Charles. Obwohl, ich verstehe dich immer noch nicht... Eine unbezahlbare Rose in deinen Händen zu halten und sie für... eine Wildblume auszutauschen. Aber das Herz will, was es will... Sei glücklich, mein Freund. Mögest du glücklich bis ans Ende deiner Tage leben!";
				link.l1 = "In der Blume, die Sie halten, ist das schönste Ihr Gefühl dazu. Ohne es ist es nur ein Klumpen verblassendes Fleisch. Freut mich, dass Sie gekommen sind, Eure Gnaden.";
				link.l1.go = "FortFrance_Mayor_1";
			}
			else
			{
				dialog.text = "Einen wunderbaren Tag, mein Freund, und einen wunderbaren Anlass! Nehmen Sie meine aufrichtigen Glückwünsche an! Ich war dreimal verheiratet und jedes Mal zitterte ich wie beim ersten Mal, ah, Jugend...";
				link.l1 = "Herr, Sie sind noch weit vom Alter entfernt, lassen Sie sich nicht entmutigen. Danke, dass Sie gekommen sind, Jacques!";
				link.l1.go = "Guests_block";
			}
		break;
		
		case "FortFrance_Mayor_1":
			dialog.text = "Warte, Charles. Du hast mich missverstanden, ich bin wirklich von ganzem Herzen glücklich! Und ja... hier, nimm es. Unser gemeinsamer... Freund, hat wirklich darum gebeten, dass du es genau heute bekommst.";
			link.l1 = "Ich vermute, dass ich weiß, von wem es ist. Danke und bis bald.";
			link.l1.go = "Guests_block";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2-1");
					else AddQuestRecordInfo("Letter_Marquesa", "1-1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4-1");
					else AddQuestRecordInfo("Letter_Marquesa", "3-1");
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2");
					else AddQuestRecordInfo("Letter_Marquesa", "1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4");
					else AddQuestRecordInfo("Letter_Marquesa", "3");
				}
			}
		break;
		
		// Бас Тер
		case "BasTer_Mayor":
			dialog.text = "Eine entzückende Liturgie, nicht wahr, Charles? Ich freue mich aufrichtig für dich! Von mir persönlich und allen Bürgern von Basse-Terre - wir gratulieren dir und deiner... bezaubernden Frau. Ihr seid ein wunderbares Paar! Mögt ihr glücklich bis ans Ende eurer Tage leben!";
			link.l1 = "Danke Euch, Eure Gnaden. Freut mich, dass es Euch gefallen hat.";
			link.l1.go = "Guests_block";
		break;
		
		// Порт Принс
		case "PortPax_Mayor":
			dialog.text = "Ein solch wunderbarer Dienst, Monsieur de Maure, einfach wunderbar! Und die Braut ist so... originell in diesem Outfit. Im Namen aller Bewohner unserer Stadt - akzeptieren Sie meine aufrichtigsten Glückwünsche! Ich wünsche Ihnen viele glückliche Jahre!";
			link.l1 = "Danke, Eure Gnaden.";
			link.l1.go = "Guests_block";
		break;
		
		// Тортуга
		case "Tortuga_Mayor":
			dialog.text = "So süß - Sie und Ihre Braut, Monsieur de Maure, sahen so ungewöhnlich aus! Jedoch, Sie sind ein ungewöhnlicher Mann. Ich wünsche Ihnen ein langes und glückliches Familienleben. Mögen Sie glücklich bis ans Ende Ihrer Tage leben!";
			link.l1 = "Ich bin Ihnen sehr dankbar, Eure Gnaden.";
			link.l1.go = "Guests_block";
		break;
		
		// д'Ойли
		case "PortRoyal_Mayor":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_03.wav");
			dialog.text = "Für die Sake Ihrer Hochzeit, es war es wert, die Karibik zu überqueren! Herzlichen Glückwunsch, Kapitän, im Namen der Bewohner aller englischen Kolonien! Sie und Ihre Braut, Entschuldigung, schon eine Ehefrau, sind ein wunderbares Paar!";
			link.l1 = "Danke für den Besuch und die freundlichen Worte, Oberst!";
			link.l1.go = "Guests_block";
		break;
		
		// Исла Тесоро
		// Тиракс
		case "Terrax":
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "Und was macht dieser verheiratete Geck an meinem Piratenstrand, hm?! Erzähl mir, Monsieur, was hast du mit meinem alten Freund gemacht - dem harten Piraten Charlie Prince?";
					link.l1 = "Charlie Prince ist tot, daran erinnerst du dich, Marcus... Ha-ha-ha komm her, du Seeteufel! Ich freue mich, dich zu sehen! Wie geht es euch hier, haben sich alle versammelt?";
					link.l1.go = "Terrax_1_1";
				}
				else // 28-03-20
				{
					dialog.text = "Und was macht dieser verheiratete Geck an meinem Piratenstrand, huh?! Sag mir, Monsieur, was hast du mit meinem alten Freund gemacht - dem harten Kapitän Charles de Maure?";
					link.l1 = "Ahoi, Marcus, ich freue mich auch, dich zu sehen! Wie geht es euch hier, haben sich alle versammelt?";
					link.l1.go = "Terrax_1";
				}
			}
			else
			{
				dialog.text = "Und was macht dieser verheiratete Geck an meinem Piratenstrand, hm?! Sag mir, Monsieur, was hast du mit meinem alten Freund gemacht - dem harten Kapitän Charles de Maure?";
				link.l1 = "Ahoi, Marcus, ich bin auch froh, dich zu sehen! Wie geht es euch hier, hat sich schon jeder versammelt?";
				link.l1.go = "Terrax_1";
			}
		break;
		
		case "Terrax_1":
			dialog.text = "Ja, der Waldteufel kam erst gestern an und begann sofort zu kommandieren - also sind die Gäste hier und alles ist bereit für die Feier. Dein Schiff wurde in der Nähe der Riffe bemerkt, und die Jungs konnten es nicht aushalten - sie stürmten in die Taverne und haben wahrscheinlich schon dieses Fass von Hawk geöffnet. Beeil dich, vielleicht haben wir noch die Chance, ein Glas zu trinken - Nathaniel prahlte, dass dies eine Art besonderer Rum sei!";
			link.l1 = "Jetzt machen wir es so - vom Schiff direkt zur Feier! Ich werde auf meine bessere Hälfte warten und wir sind gleich hinter dir, Marcus!";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_1_1":
			dialog.text = "Ja, der Waldteufel ist erst gestern angekommen und hat sofort zu kommandieren begonnen - also sind die Gäste hier und alles ist bereit für die Feier. Dein Schiff wurde in der Nähe der Riffe bemerkt, und die Kerle konnten es nicht aushalten - sie stürzten in die Taverne und haben wahrscheinlich bereits dieses Hawk's Fass geöffnet. Beeil dich, vielleicht haben wir noch eine Chance, ein Glas zu trinken - Nathaniel prahlte, dass dies eine Art besonderer Rum sei!";
			link.l1 = "Jetzt machen wir es so - vom Schiff direkt zur Party! Ich warte auf meine bessere Hälfte und wir sind gleich hinter dir, Marcus!";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_2":
			DialogExit();
			DoQuestReloadToLocation("Pirates_tavern", "reload", "reload1", "LongHappy_IslaTesoroTavern");
		break;
		
		case "Terrax_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles de Maure geheiratet - kann mich immer noch nicht daran gewöhnen... Erst Svenson, jetzt du - und dann? Pastor Marlow oder Jacques der Gutmensch?";
			link.l1 = "Du hast die Falken vergessen. Und was ist mit dir, Marcus? Nicht müde, ein einsamer Seewolf zu sein?";
			link.l1.go = "Terrax_4";
		break;
		
		case "Terrax_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				dialog.text = "Dannie und Nathan sind ein langjähriger Fall - Ich habe mich bereits damit abgefunden, aber du hast mich überrascht, es gibt nichts zu sagen! Allerdings ist die Schülerin des Waldteufels wunderschön - es gibt nichts zu sagen, jederzeit bereit, ein Wort und eine Waffe zu benutzen, und sie kann jedem Sturm standhalten. Es ist unwahrscheinlich, dass du dir eine würdigere Frau finden könntest. Du bist ein Glückspilz, Kapitän - pass gut auf sie auf!";
			}
			else
			{
				dialog.text = "Dannie und Nathan sind ein altbekannter Fall - ich habe mich damit schon abgefunden, aber du hast mich überrascht, da gibt es nichts zu sagen! Obwohl, wie ich gehört habe, weiß deine Mary viel über Schwerter und sie weiß definitiv, wie man sie benutzt - meine Hochachtung! Eine wahre Kriegerin. Ich verrate dir ein Geheimnis, für ein solches Mädchen könnte ich selbst meine Überzeugungen als Junggeselle überdenken. Du bist ein Glückspilz, Kapitän - kümmere dich um sie!";
			}
			link.l1 = "Ich weiß, sie ist ein Wunder und ich bin wieder im siebten Himmel vor Glück - genau wie in den Tagen, als wir uns zum ersten Mal trafen!";
			link.l1.go = "Terrax_5";
		break;
		
		case "Terrax_5":
			dialog.text = "Nun denn, ein Toast!... Für die Liebe!... Aber nicht für die, die uns über die Schwelle und zum Horizont treibt!... Sondern für die, die auf uns an dieser Schwelle wartet! Für die Liebe, die uns dazu bringt, zu ihr zurückzukehren, selbst vom Ende der Welt und von den goldenen Bergen! Lebt mit ihr und seid glücklich!";
			link.l1 = "Großer Toast, Marcus, danke!";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6_1":
			dialog.text = "Prost, auf deine Hochzeit, Kumpel!";
			link.l1 = "Danke, Marcus...";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6":
			DialogExit();
			npchar.dialog.currentnode = "Terrax_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Terrax_7":
			dialog.text = "Jacques? Das ist definitiv nicht gut...";
			link.l1 = "Marcus, glaubst du...";
			link.l1.go = "Terrax_8";
		break;
		
		case "Terrax_8":
			dialog.text = "Es gibt keine Zeit! Sie sind hinter den Türen! Alle, zu den Waffen!";
			link.l1 = "Hier gehen wir!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernFight");
		break;
		
		case "Terrax_9":
			dialog.text = "Ich kann mich nicht erinnern, wann ich das letzte Mal so viel Spaß auf einer Party hatte! Es ist noch nicht vorbei! Hörst du das? Draußen wird geschossen! Lasst uns die Straßen mit ihrem Blut besudeln!";
			link.l1 = "Warte! Wer zum Teufel sind die!? Und was zum Teufel wollen sie überhaupt?!";
			link.l1.go = "Terrax_10";
		break;
		
		case "Terrax_10":
			DialogExit();
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		// Натаниэль Хоук
		case "Nathaniel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Verheirateter Kapitän de Maure, selten habe ich aufrichtigere Gründe für einen Toast getroffen. Erheben Sie ein Glas - das ist kein gewöhnlicher Kohlgetränk. Es ist mit schwarzem Tee aus Ostindien infundiert und mit echten persischen Gewürzen gewürzt!";
			link.l1 = "Und ich habe nachgedacht, warum es in meinem Hals brennt, als hätte ich geschmolzenes Blei getrunken. Nun, Nathan, Prost...";
			link.l1.go = "Nathaniel_1";
		break;
		
		case "Nathaniel_1":
			dialog.text = "Wartet, erst ein Toast! Hey Herren, erhebt eure Krüge! Heute betritt unser Freund und Partner Charles de Maure den Pfad des Familienlebens. Nehmt von uns die tiefsten Beilei.. oh, Dannie bitte, leg die Pistole ab! Herzlichen Glückwunsch, natürlich! Jetzt seid ihr die Segel desselben Schiffes, also führt sie durch alle Stürme zu den fruchtbarsten Ufern!";
			link.l1 = "Danke dir, Nathan, aufrichtig. Du und Danielle seid ein Beispiel für uns zum Folgen.";
			link.l1.go = "Nathaniel_2";
		break;
		
		case "Nathaniel_2":
			dialog.text = "Schön zu hören. Meine Frau und ich sind vielleicht nicht das beste Paar der Welt, aber wir sind glücklich zusammen, und du hast so viel für uns getan, also wenn du mich fragst, bist du ein Teil meiner Familie, und ich werde für dich da sein, wann immer du mich brauchst. Sei glücklich und bitte trink einen Schluck!";
			link.l1 = "Lass uns dann trinken! Oh... dieser Rum sollte seinen Platz im Arsenal der Heiligen Inquisition haben. Verdammt! Es brennt den ganzen Weg... aghhh! Puh!... Ich mag es!";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_3":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_3_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Nathaniel_3_1":
			dialog.text = "Du siehst mir und Dannie vor zwanzig Jahren so ähnlich!";
			link.l1 = "Noch ein Becher, Nathan!";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Was!? Hat Jan dich in den Keller geschickt, um Wein zu holen? Lass uns einen Spaziergang machen, ich werde dir ein bisschen helfen, und frische Luft wird nützlich sein.";
			link.l1 = "Aber wo sind Dannie und "+sld.name+"? Jan hat mir gesagt, dass sie gegangen sind, um zu reden.";
			link.l1.go = "Nathaniel_5";
		break;
		
		case "Nathaniel_5":
			dialog.text = "Ja, Dannie weiß, dass die Anwesenheit selbst der besten Mädchen-in-Armen den Herren der glücklichen Zeit immer noch nicht die Möglichkeit geben wird, sich voll und ganz zu entspannen. Also hörten sie auf all die Komplimente, die sie erhielten, und gingen zur Residenz, um den Jungs Spaß zu machen.";
			link.l1 = "Nun, dann lasst uns loslegen! Ich habe es geschafft, ein paar Krüge zu trinken, aber verdammt noch mal, jetzt ist es wirklich Zeit, ordentlich betrunken zu werden!";
			link.l1.go = "Nathaniel_6";
		break;
		
		case "Nathaniel_6":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableFastReload = true;//закрыть переход
			pchar.quest.longhappy_isla_vine.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_vine.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_isla_vine.function = "LongHappy_IslaTesoroToAlexus";
		break;
		
		case "Nathaniel_7":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "Also, hier ist die Truhe. Wir nehmen so viel wir tragen können und kehren zurück, bevor dieser alte Muffel uns hier einsperrt.";
			link.l1 = "Du übertreibst, Nathan. Er ist nicht so schlimm... Warte, hast du das gehört?";
			link.l1.go = "Nathaniel_8";
		break;
		
		case "Nathaniel_8":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "Jan hat wahrscheinlich mehr Leute gefunden und sie geschickt, um uns zu helfen. Verdammt!";
			link.l1 = "Komm schon, die Flaschen zerbrechen zum Glück. Nimm noch eine und lass uns gehen.";
			link.l1.go = "Nathaniel_9";
		break;
		
		case "Nathaniel_9":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum") && GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				sld.dialog.currentnode = "Tichingitu_8";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else LongHappy_SetBandosInDungeon();
		break;
		
		case "Nathaniel_10":
			dialog.text = "Was zum Teufel passiert hier, wer sind diese Bastarde? Verstehst du etwas, Charles?";
			link.l1 = "Ich weiß es nicht, Nathan, aber einer von ihnen ist losgerannt, um Hilfe zu holen, und es scheint, als ob ich weitere Schritte höre. Wir müssen zur Taverne zurückkehren!";
			link.l1.go = "Nathaniel_11";
		break;
		
		case "Nathaniel_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			pchar.quest.longhappy_totavern.win_condition.l1 = "location";
			pchar.quest.longhappy_totavern.win_condition.l1.location = "Pirates_tavern";
			pchar.quest.longhappy_totavern.function = "LongHappy_TavernAlarm";
		break;
		
		case "Nathaniel_12":
			LongHappy_TownRepose();
			dialog.text = "Wir haben diese Bastarde niedergemacht, aber die Kanonen donnern vom Meer, hörst du? Wir haben nur zwei Mannschaften bereit für den Kampf, auf Marcus' Fregatte und Jans Korvette. Ich, Dannie und die anderen haben unsere Leute abgesetzt - schließlich ist Hochzeit - also ist Centurion raus. Was ist mit deinem Schiff? Wir müssen schnell entscheiden, was zu tun ist!";
			link.l1 = "Ich habe die Hälfte der Mannschaft an Land gebracht, ich hoffe, der Rest ist nüchtern. Aber zuerst muss ich meine Frau finden und sicherstellen, dass es ihr gut geht.";
			link.l1.go = "Nathaniel_13";
		break;
		
		case "Nathaniel_13":
			dialog.text = "Ja, Dannie ist auch nirgends zu sehen. Dann handeln wir so - Tyrex und Svenson sind bereits zum Hafen geeilt, sie werden ihre Schiffe mit Booten erreichen. Wir gehen zur Residenz für die Ehefrauen, der Rest - soll die Verteidigung am Ufer organisieren. Kannst du einige deiner Offiziere schicken, um Leute auf deinem Schiff zu sammeln? Hilfe dort wird offensichtlich nicht schaden.";
			link.l1 = "Gut, alle bewegen sich! Jede Sekunde zählt!";
			link.l1.go = "Nathaniel_14";
		break;
		
		case "Nathaniel_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
		break;
		
		case "Nathaniel_15":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Schneller, nach oben! Dannie und "+sld.name+" muss da sein! Und wenn diese Bastarde sie verletzt haben...";
			link.l1 = "Denk nicht mal dran! Nach oben! Los geht's!";
			link.l1.go = "Nathaniel_16";
		break;
		
		case "Nathaniel_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_townhall", "reload1_back", true);
			pchar.quest.longhappy_isla_bedroom.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_bedroom.win_condition.l1.location = "Location_reserve_04";
			pchar.quest.longhappy_isla_bedroom.function = "LongHappy_IslaTesoroBedroom";
		break;
		
		case "Nathaniel_17":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Verdammt! Dein Kamerad, er stürzte sich direkt in das Gewehr, damit dieser Bastard die Mädchen nicht erschießen würde!";
			link.l1 = "Und er hat eine Kugel abbekommen... Warte, Nathan... er atmet! Er lebt noch! Verdammt, ich brauche Gino! "+sld.name+", Liebling, wie geht es dir?";
			link.l1.go = "Nathaniel_18";
		break;
		
		case "Nathaniel_18":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_19";
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_7_1";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Nathaniel_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Wir sind in Ordnung, Charles! Ich werde sie losbinden. Ich höre Kanonen im Hafen - du und Nathan müsst dorthin gehen, sonst wird Barbazon all unsere Schiffe zerstören. Verschwende keine Zeit!";
			link.l1 = "Ich werde Gino finden und ihn hierher schicken, er wird helfen ... er muss! "+sld.name+", Liebchen, bleib hier, kümmere dich um ihn, ihr beide.";
			link.l1.go = "Nathaniel_19";
		break;
		
		case "Nathaniel_19":
			dialog.text = "Charles, beeil dich! Was auch immer du entscheidest, Zeit ist jetzt ihr Gewicht in Gold wert! Wenn Jacques' Schiffe durchbrechen zur Küste, wird alles umsonst sein!";
			link.l1 = "Ja, ich weiß. Verdammt noch mal!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Nathaniel_20":
			dialog.text = "Schneller, wir haben keine Zeit zum Reden!";
			link.l1 = "";
			link.l1.go = "Nathaniel_20_1";
		break;
		
		case "Nathaniel_20_1":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_20";
		break;
		
		case "Nathaniel_21":
			dialog.text = "Mist! Verzeih mir Charles. Wir waren oben festgeklemmt, da waren ein Dutzend dieser Bastarde... Es ist schade, dass ich nicht rechtzeitig hierher gekommen bin, aber ich sehe, du hast die Situation bestmöglich gemeistert.";
			link.l1 = "Ich kann nicht sagen, dass es leicht war, aber, verdammt, ich habe eine große Freude empfunden, als ich diesen 'netten Mann' getötet habe! Es ist Zeit an Land zu gehen, Nathan, Unsere Leute warten dort auf uns!";
			link.l1.go = "Nathaniel_22";
		break;
		
		case "Nathaniel_22":
			dialog.text = "Ja, wir müssen deinen Indianerjungen besuchen, hier fertig werden und nach Scharfstadt gehen.";
			link.l1 = "Du hast recht, ich bin hinter dir.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Nathaniel_23";
			else link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_23":
			dialog.text = "Übrigens, wir haben Marcus gefunden! Er war im Laderaum, gefesselt und bewusstlos.";
			link.l1 = "Er lebt?";
			link.l1.go = "Nathaniel_24";
		break;
		
		case "Nathaniel_24":
			dialog.text = "Er ist in einem schlechten Zustand, aber er wird in Ordnung sein. Tyrex ist stärker als ein Nagel für einen Sarg, also mach dir keine Sorgen, er wurde bereits auf dein Schiff verlegt und hat nach einem Säbel gefragt.";
			link.l1 = "Endlich, gute Nachrichten! Gut, lass uns hier fertig werden und zurückkehren.";
			link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		// Даниэль Хоук
		case "Danielle":
			dialog.text = "Hallo, Charles. Lass mich dich anschauen - hübscher geworden, kann nicht klagen! Fast wie Nathan, vor etwa zehn Jahren! Komm rein, steh nicht auf der Türschwelle, alle haben gerade auf dich gewartet!";
			link.l1 = "Danke dir, Dannie, ich freue mich sehr, dich zu sehen! Ich werde etwas später zu dir und Nathan kommen und dann werden wir reden!";
			link.l1.go = "Danielle_1";
		break;
		
		case "Danielle_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "tables", "stay1", "LongHappy_DannyNorm", -1); 
		break;
		
		case "Danielle_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, nimm Platz - Nathan und ich sind so glücklich für dich! Marcus, Jan und mein Mann haben etwas für dich vorbereitet - aber Geschenke können warten. Lass mich dir jetzt gratulieren und dir Glück wünschen! Deine Auserwählte ist einfach ein Wunder! Sag, du hast es nicht geschafft, sie auf Martinique ein weißes Kleid tragen zu lassen, oder?";
			link.l1 = "Danke, Dannie. Ja, es hat sich lustig mit dem Kleid ergeben - ich bin mir sicher, dass unsere Hochzeit in der High Society viele skandalöse Gerüchte ausgelöst hat. Jeder hat ehrlich die Augen abgewendet und so getan, als würde nichts Außergewöhnliches passieren. Manieren und all diese Art - aber ich kümmere mich nicht um Klatsch, ich liebe sie und das ist das Wichtigste.";
			link.l1.go = "Danielle_3";
		break;
		
		case "Danielle_3":
			dialog.text = "Du hast absolut recht! Ich bin auch zum Altar gegangen, mit einem Schwert und einem Paar Pistolen hinter der Schärpe. Aber das war in Port Royal, noch bevor es eine respektable Kolonialresidenz wurde. Damals gab es so viel Spaß, sogar mehr als auf Tortuga unter Levasser und niemand war überrascht... eh. Wie auch immer, ich plaudere die ganze Zeit - gehe zu den Gästen, alle haben hier auf dich gewartet, gib mir nur eine Umarmung!";
			link.l1 = "Ach Dannie, wie könnte ich dir überhaupt ablehnen ha-ha! Du kannst dir gar nicht vorstellen, wie froh meine Frau und ich sind, dich alle zu sehen!";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_4":
			DialogExit();
			npchar.dialog.currentnode = "Danielle_4_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Danielle_4_1":
			dialog.text = "Sie sind ein schönes Paar, Charles!";
			link.l1 = "Danke, Dannie...";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_5":
			dialog.text = "Charles, er hat Recht... du hast keine Wahl. Ich glaube nicht an die Gnade von Jacques dem Gütigen, wenn er mit Tyrex und dem Rest handelt. Du weißt, was getan werden muss.";
			link.l1 = "";
			link.l1.go = "Danielle_6";
		break;
		
		case "Danielle_5_1":
			dialog.text = "Hör ihm nicht zu! Wenn der Kindmann sich zu solchem Wahnsinn entschlossen hat, wird er niemanden verschonen!";
			link.l1 = "";
			link.l1.go = "Danielle_6_1";
		break;
		
		case "Danielle_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_39";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_6_1":
			DialogExit();
			sld = characterFromId("LH_Dussak");
			sld.dialog.currentnode = "Dussak_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_7_1":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Wir sind in Ordnung, Charles! Ich werde sie losbinden. Ich höre Kanonen im Hafen, du und Nathan müsst dort hin, sonst wird Barbazon unsere Schiffe ertränken wie Entenküken in einem Fass. Du solltest keine Minute verlieren!";
			link.l1 = "Ich werde Gino finden und ihn hierhin schicken, er wird helfen ... er muss, verdammt noch mal! "+sld.name+", Liebling, bleib hier, pass auf Tichingitu auf.";
			link.l1.go = "Danielle_8_1";
		break;
		
		case "Danielle_7":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nathan, nein!!!";
			link.l1 = "Er ergriff den Moment und stürzte zur Kanone, um dich zu decken, Dannie... "+sld.name+", Schatz, wie geht es dir?";
			link.l1.go = "Danielle_8";
		break;
		
		case "Danielle_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_41";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_8_1":
			DialogExit();
			sld = characterFromId("Nathaniel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_9":
			dialog.text = "Ja, Charles, er lebt! Das Herz schlägt kaum, aber er lebt! Was sollen wir tun?!";
			link.l1 = "Wir brauchen Gino, sofort! Ich werde ihn finden und hierher schicken, er wird helfen... er muss!";
			link.l1.go = "Danielle_10";
		break;
		
		case "Danielle_10":
			dialog.text = "Charles, wir haben keine Zeit! Wenn Jacques' Schiffe an die Küste durchbrechen, wird alles umsonst sein! Mein Mann ... er hat getan, was er tun musste. Jetzt bist du dran. Ich bleibe bei ihm. Ihr zwei solltet gehen und Gino finden!";
			link.l1 = "Ja, ich weiß. Verdammt, dieser Bastard wird dafür bezahlen!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Danielle_11":
			dialog.text = "Hier bist du endlich! Ist jeder in Ordnung?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				link.l1 = "Wir sind in Ordnung, Dannie, mach dir keine Sorgen. Jacques ist tot, seine Schiffe liegen auf dem Grund. Wie geht es Tichingitu?";
				link.l1.go = "Danielle_17";
			}
			else
			{
				link.l1 = "Wir sind in Ordnung, Dannie, mach dir keine Sorgen. Jacques ist tot, seine Schiffe liegen auf dem Grund. Wie geht es Nathan?";
				link.l1.go = "Danielle_12";
			}
		break;
		
		case "Danielle_12":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "Er ist in Ordnung! Ihr italienischer Arzt ist ein Genie! Nathan schläft oben, aber laut Gino droht ihm nichts. Eine Woche oder zwei im Bett, Rotwein und, wie er sagte, 'der Besuch einer ihm wohlgesinnten Dame' ähem... Im Allgemeinen - alles ist in Ordnung, du hast uns wieder gerettet, Charles, wie kann ich dir danken?";
				link.l1 = "Es war Nathaniel, der meine Frau und dich gerettet hat. Und ich werde ihm dafür immer schulden. Du kannst dir nicht vorstellen, wie froh ich bin zu hören, dass er sich erholt. Lass ihn ruhen, ich werde später nach dir sehen.";
				link.l1.go = "Danielle_13";
			}
			else
			{
				dialog.text = "Es geht ihm gut, die Kugel ist durchgegangen und unser Chirurg von der 'Centurion' war nicht weit entfernt. Er hat sich vor diesem Durcheinander versteckt. Also Nathan wird leben, ein paar Wochen im Bett - kleine Mühe!";
				link.l1 = "Dannie, er hat meine Frau und dich vor einer Kugel geschützt und ich werde ihm das ewig schulden. Du kannst dir nicht vorstellen, wie froh ich bin zu hören, dass er sich erholt. Lass ihn ruhen, ich werde später nach euch sehen.";
				link.l1.go = "Danielle_14";
			}
		break;
		
		case "Danielle_13":
			dialog.text = "Natürlich! Aber, ich muss dich verlassen, ich muss zu meinem Mann gehen... Macht es dir etwas aus, wenn wir deinen Freund ausleihen? Wenn Nathan sich erholt, werde ich ihn selbst nach Antigua bringen. Die Centurion hat irgendwie wunderbar überlebt, sie muss nur ein neues Team rekrutieren.";
			link.l1 = "Gut, Dannie, grüße Gino und Nathan. Ich sollte gehen.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_14":
			dialog.text = "Natürlich, Charles, aber... ich habe schlechte Nachrichten. Dieser Italiener, Guineili, der auf deiner Hochzeit war... Sein Körper wurde in einem Zimmer in der Taverne gefunden. Ich... Es tut mir leid, Charles.";
			link.l1 = "Was? Gino?! Nein! Wie?";
			link.l1.go = "Danielle_15";
		break;
		
		case "Danielle_15":
			dialog.text = "Ich weiß es nicht, wahrscheinlich einer dieser Bastarde, die durch die Katakomben gegangen sind und die Stadt angegriffen haben. Anscheinend haben sie sich dort versteckt, auf einen Moment zur Flucht gewartet und ihn gefunden...";
			link.l1 = "Verdammt! Nein, ich glaube es nicht...";
			link.l1.go = "Danielle_16";
		break;
		
		case "Danielle_16":
			pchar.questTemp.LongHappy.Jino_died = "true";
			dialog.text = "Es tut mir leid, Charles. Es war ein verdammtes Blutbad, und er war kein Kämpfer... Wenn du willst, bringen wir seinen Körper zu deinem Schiff, bring ihn nach Hause und begrabe ihn, wie es sein sollte. Es tut mir wirklich leid...";
			link.l1 = "Danke, Dannie. Befiehl, den Körper auf ein Schiff zu laden. Ich muss jetzt gehen... Ich muss nachdenken. Und grüße Nathan.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_17":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "Er ist in Ordnung! Ihr italienischer Arzt ist ein Genie! Er schläft im Zimmer oben, und Gino kümmert sich um ihn. Er sagt 'eine Woche oder zwei und er wird in Ordnung sein'.";
				link.l1 = "Tolle Neuigkeiten! Ich nehme an, ich kann ihn jetzt nicht besuchen?";
				link.l1.go = "Danielle_18";
			}
			else
			{
				dialog.text = "Es tut mir so leid, Charles. Ich habe unseren Chirurgen von der Centurion gefunden, aber er konnte nichts tun... Dein Freund ist vor ein paar Stunden gestorben.";
				link.l1 = "Tichingitu?! Nein! Ich glaube es nicht!!!";
				link.l1.go = "Danielle_19";
			}
		break;
		
		case "Danielle_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nein, Italiener hat strikt verboten, ihn zu stören, lass ihn ruhen, und Gino sollte sich schließlich nach all den Sorgen ausruhen. Ich habe sogar gesagt "+sld.name+" um einen Spaziergang zu machen, als wir herausfanden, dass alles in Ordnung sein würde\nUnd noch etwas... dein Freund, er hat mich vor der Kugel geschützt. Ich weiß nicht einmal, wie ich ihm danken soll, sag ihm, dass er ab jetzt auch ein Teil unserer Familie ist, und du - du hast uns wieder gerettet, Charles!";
			link.l1 = "Alles ist gut, was gut endet, Dannie. Geh zu Nathan, er hat auf dich gewartet, und ich werde hier eine kleine Pause einlegen und nach meinem suchen "+sld.name+".";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_19":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Es tut mir leid, ich habe alles getan, was ich konnte, und "+sld.name+", auch. Er hat uns vor dieser Kugel geschützt, und das werde ich nie vergessen, glaub mir.";
			link.l1 = "... Vor langer Zeit sagte er, dass er für mich sterben würde... Ich schätze, er wusste nie, dass er sein Leben für uns alle opfern würde... und jetzt ist er ein Held und ich werde ihn als nichts Geringeres in Erinnerung behalten... Wo ist "+sld.name+"Geht es ihr gut?";
			link.l1.go = "Danielle_20";
		break;
		
		case "Danielle_20":
			dialog.text = "Ich kann es nicht sagen... Ich meine, körperlich ja. Aber... du weißt schon... Sie sagte, sie wäre spazieren gegangen, um ihren Kopf freizubekommen. Wahrscheinlich hat sie dich angedockt gesehen und wird bald zurück sein.";
			link.l1 = "Verfluchter Jacques Barbazon... Wir hätten ihn früher töten sollen!";
			link.l1.go = "Danielle_21";
		break;
		
		case "Danielle_21":
			dialog.text = "Warte... das ist noch nicht alles. Dieser Italiener, Guineili, ja? Dieser stille junge Mann. Er wurde... seine Leiche wurde in einer Taverne gefunden... Ich weiß nicht, wahrscheinlich einer dieser Bastarde, die durch die Katakomben gingen und die Stadt angriffen. Anscheinend haben sie sich dort versteckt, suchten einen Moment zur Flucht und fanden ihn...";
			link.l1 = "Und Gino auch?! Heute ist wahrlich ein regnerischer Tag...";
			link.l1.go = "Danielle_22";
		break;
		
		case "Danielle_22":
			pchar.questTemp.LongHappy.Tichingitu_died = "true";
			dialog.text = "Es tut mir leid, Charles... Wenn du möchtest, werden wir ihre Körper zu deinem Schiff schicken, die Jungs nach Hause bringen und sie so begraben, wie es sein sollte. Es tut mir wirklich leid...";
			link.l1 = "Danke Dannie. Mach es... Ich sollte gehen... Ich brauche... zum Nachdenken.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		// Додсон
		case "Dodson":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, kannst du dir überhaupt vorstellen, wie viele Mädchenherzen du mit dieser Hochzeit von dir gebrochen hast? Ja, die Hälfte der Mädchen des Archipels muss nach deiner Hochzeit getrauert haben, haha!";
			link.l1 = "Was kann ich tun - ich brauchte nur eine und ich habe sie bekommen. Aber es ist noch zu früh für die Mädchen, sich aufzuregen, denn sie haben immer noch dich, Stiven.";
			link.l1.go = "Dodson_1";
		break;
		
		case "Dodson_1":
			dialog.text = "Und das ist wahr! Wir werden hier fertig sein und ich werde mich sofort um sie kümmern, verdammt noch mal! Los, Charles, lass uns auf dein Glück und Familienleben trinken. Also, wie man so sagt, auf ein glückliches Ende!";
			link.l1 = "Danke mein Freund!";
			link.l1.go = "Dodson_2";
		break;
		
		case "Dodson_2":
			DialogExit();
			npchar.dialog.currentnode = "Dodson_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Dodson_2_1":
			dialog.text = "Auf ein glückliches Familienleben, ha-ha!";
			link.l1 = "Prost!";
			link.l1.go = "Dodson_2";
		break;
		
		// Венсан
		case "Vensan":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, kannst du dir überhaupt vorstellen, wie viele Mädchenherzen du mit dieser Hochzeit von dir gebrochen hast? Ja, die Hälfte der Mädchen des Archipels muss nach deiner Hochzeit getrauert haben, haha!";
			link.l1 = "Was kann ich tun - ich brauchte nur eine und ich habe sie bekommen. Aber es ist noch zu früh für die Mädchen, um sich aufzuregen, denn sie haben immer noch dich, Bernard.";
			link.l1.go = "Vensan_1";
		break;
		
		case "Vensan_1":
			dialog.text = "Und das ist wahr! Wir werden hier fertig und ich kümmere mich sofort um sie, verdammt nochmal! Komm schon, Charles, trinken wir auf dein Glück und Familienleben. Also, wie man so schön sagt, und sie lebten glücklich bis ans Ende ihrer Tage!";
			link.l1 = "Und sie lebten glücklich bis ans Ende ihrer Tage!";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_2":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_2_1":
			dialog.text = "Für ein glückliches Familienleben, ha ha!";
			link.l1 = "Großartiger Toast!";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Ha, Charles, also bist du auch verheiratet und langweilig geworden, wie unser alter Nathan! Heiße Affären und alles andere sind jetzt der Vergangenheit angehören, hm? Ungefährer Familienmann!";
			link.l1 = "Bleib warten, Bernard! Meine Frau ist nicht eine von denen, die sich gelangweilt unter dem Fenster eines Familienwracks setzen wird! Das einzige, was sich ändern wird, ist die Fülle der Geldbörsen der Dirnen von hier bis Curacao!";
			link.l1.go = "Vensan_4";
		break;
		
		case "Vensan_4":
			dialog.text = "Nicht ein großer Verlust, sage ich! Besser, man hat eine Goldmünze als einen Sack voller Nickel. Lass uns einen trinken! Prost auf dich und deine Frau! Bewahre dein Gold sicher auf und sei glücklich!";
			link.l1 = "Danke Bernard. Oh, das ist ein wirklich starker Rum. Uff!";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_5":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_5_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_5_1":
			dialog.text = "Zu deiner Braut, ich meine, schon eine Ehefrau!";
			link.l1 = "Danke dir!";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_6":
			dialog.text = "Du bist gerade rechtzeitig, Charles, danke!";
			link.l1 = "Was ist hier der Spaß? Ich dachte, ihr ladet bereits auf den Schiffen im Hafen.";
			link.l1.go = "Vensan_7";
		break;
		
		case "Vensan_7":
			dialog.text = "Marcus hat mich zurückgelassen, um eine Verteidigung am Ufer zu organisieren. Uns fehlen Leute, die Kerle im Hafen brauchen Schießpulver. Dachte, ich schau mal vorbei, nehme ein paar Fässer ... und dann diese Schläger. Hah, sie haben sich versteckt, denke ich, wollten abwarten oder jemanden ausrauben. Und ich bin noch voll von Hawks Rum, also ohne dich, ich weiß nicht, würde ich noch leben oder nicht.";
			link.l1 = "Du bist immer willkommen. Gut, Bernard, du sorgst dafür, dass die Stadt gesichert ist, und ich sollte gehen, bleib sicher!";
			link.l1.go = "Vensan_8";
		break;
		
		case "Vensan_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.LongHappy.Vensan_alive = "true";
		break;

		// Джино
		case "Jino":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Kapitän, lassen Sie mich Ihnen und Ihrer Liebsten an diesem glücklichen Tag herzlich gratulieren! Seid glücklich und kümmert Euch umeinander!";
			link.l1 = "Danke, Gino. Ich bin froh, dass du dich entschieden hast zu kommen! Ich hoffe, die lokale... Farbe, stört dich nicht?";
			link.l1.go = "Jino_1";
		break;
		
		case "Jino_1":
			dialog.text = "Das ist... eine sehr lehrreiche Reise. Ich muss sagen - ich war lange nicht mehr aus Antigua heraus, und in dieser Gesellschaft fällt es mir nicht leicht, mich wohl zu fühlen. Aber, du hast immer gewusst, wie man Menschen versteht, also werde ich versuchen, ruhig zu bleiben, da ich dir vertraue.";
			link.l1 = "Vielleicht musst du etwas Stärkeres trinken? Entspann dich und such jemanden zum Reden?";
			link.l1.go = "Jino_2";
		break;
		
		case "Jino_2":
			dialog.text = "Danke, Kapitän, ich habe genug verdünnten Wein. Alkohol, muss ich Sie warnen, ist nicht sehr gut für die Leber und möglicherweise das Herz. Was die Gespräche angeht, habe ich versucht, die Heileigenschaften von Chirik-Sanango mit dem Herrn dort drüben zu besprechen, es wird auch Manaka genannt. Ureinwohner von Maine verwenden es für...";
			link.l1 = "Lass mich raten - dieser Herr konnte der Diskussion nicht standhalten? Gino, um meinetwillen und nur heute - probier den Rum, den Jan dort drüben an der Theke einschenkt. Wenn du alle seine Zutaten erraten kannst, wird Nathaniel Hawk, dort drüben, äußerst beeindruckt sein. Ich bin sicher, er wird sich freuen, in deiner Gesellschaft zu sein, ebenso wie Svenson, der Mann an der Theke, beide respektieren gebildete Leute.";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_3":
			DialogExit();
			npchar.dialog.currentnode = "Jino_3_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.HambitOfficer"))
				{
					sld = characterFromId(pchar.questTemp.LongHappy.HambitOfficer);
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Baker") != -1)
					{
						sld = characterFromId("Baker");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						if (GetCharacterIndex("Tichingitu") != -1)
						{
							sld = characterFromId("Tichingitu");
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
						else
						{
							sld = characterFromId("Mary");
							sld.dialog.currentnode = "LongHappy_57";
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
					}
				}
			}
			else if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Jino_3_1":
			dialog.text = "Auf Ihre Gesundheit und die Gesundheit Ihrer bezaubernden Gattin!";
			link.l1 = "Danke, Freund!";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_4":
			dialog.text = "Kapitän, Sie sind es, Gott sei Dank! Diese maskierten Leute, ich habe sie gesehen und mich hier versteckt, und sie versuchten, die Tür aufzubrechen...";
			link.l1 = "Es ist in Ordnung, Gino, niemand wird dir mehr wehtun. Es ist ein großes Glück, dass ich dich gefunden habe, ich brauche deine Hilfe. Mein Freund ist verletzt - er wurde angeschossen und hat viel Blut verloren. Wir müssen uns beeilen!";
			link.l1.go = "Jino_5";
		break;
		
		case "Jino_5":
			dialog.text = "Schuss... Blut... In Ordnung, Kapitän. Auf dem Weg hierher, habe ich meine Campingkiste mit allen Werkzeugen im Falle einer Verletzung gegriffen. Führe mich zu ihm, ich werde sehen, was getan werden kann. Und diese... maskierten Männer, vielleicht haben sie sich irgendwo anders versteckt?";
			link.l1 = "Ich bin sicher, sie waren die letzten. Gino, im Hafen tobt die Schlacht und ich muss sofort dorthin. Du musst alleine zur Residenz gelangen, sie ist nicht weit. Das große Haus ist um die Ecke - du wirst es nicht verfehlen. Hab keine Angst - die Straßen sind voll von unseren Leuten, und beeil dich, ich flehe dich an!";
			link.l1.go = "Jino_6";
		break;
		
		case "Jino_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 7.0);
			LocatorReloadEnterDisable("Pirates_tavern", "reload1_back", false);
			pchar.questTemp.LongHappy.Jino_alive = "true";
			AddQuestRecord("LongHappy", "18");
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sld = characterFromId("Tichingitu");
			else sld = characterFromId("Nathaniel");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName1", sTemp);
		break;
		
		case "Jino_7":
			dialog.text = "Kapitän, lassen Sie mich Sie und Ihre Liebste an diesem glücklichen Tag herzlich beglückwünschen! Seien Sie glücklich und kümmern Sie sich um einander.";
			link.l1 = "Danke, Gino. Ich bin froh, dass du dich entschieden hast zu kommen! Ich hoffe, die Reise verlief reibungslos?";
			link.l1.go = "Jino_8";
		break;
		
		case "Jino_8":
			dialog.text = "Alles ist in Ordnung, Kapitän, danke für die Fürsorge. Ich muss sagen - ich war schon lange nicht mehr außerhalb von Antigua, und unter der Elite fühle ich mich... nicht sehr wohl. Aber der Grund zu kommen hat mir keine Wahl gelassen. Übrigens - der Service war ausgezeichnet, ich bin wirklich sehr glücklich für euch beide! Die Braut in diesem Outfit ist bezaubernd - ist das eine neue Mode? Es stellt sich heraus, dass ich hinter dem Leben zurückgeblieben bin, aber es gefällt mir, wirklich.";
			link.l1 = "Mode... Auf gewisse Weise ja, oder zumindest, wird es bald. Gut, hab Spaß, Gino, und wenn die edlen Gesprächspartner dir zu langweilig werden, dann komm zum Hafen. Die ganze Crew ist in der Kneipe. Die Jungs werden sich freuen, dich zu sehen.";
			link.l1.go = "Guests_block";
		break;
		
		case "Jino_9":
			dialog.text = "Kapitän, noch einmal gratuliere ich Ihnen und Ihrer schönen Frau! Lange und glückliche Jahre zusammen!";
			link.l1 = "Danke, Gino. Ich bin froh, dass du gekommen bist! Ich hoffe, die örtliche... Farbe, stört dich nicht?";
			link.l1.go = "Jino_10";
		break;
		
		case "Jino_10":
			dialog.text = "Diese Gesellschaft ist es nicht einfach für mich, mich wohl zu fühlen. Aber, du wusstest immer, wie man Leute auswählt, also werde ich versuchen, ruhig zu bleiben, da ich dir vertraue..";
			link.l1 = "Vielleicht musst du etwas Stärkeres trinken? Entspannen Sie sich und finden Sie jemanden zum Reden?";
			link.l1.go = "Jino_11";
		break;
		
		case "Jino_11":
			dialog.text = "Danke Ihnen, Kapitän, ich habe genug verdünnten Wein. Alkohol, das muss ich Ihnen sagen, ist nicht sehr gut für die Leber und möglicherweise das Herz. Was die Gespräche angeht, ich habe versucht, die heilenden Eigenschaften von Chirik-Sanango mit diesem Herrn zu diskutieren, es wird auch Manaka genannt. Die Einheimischen von Maine verwenden es für...";
			link.l1 = "Lass mich raten - dieser Herr konnte die Diskussion nicht unterstützen? Gino, um meinetwillen und nur heute - probiere den Rum, den Jan dort drüben an der Theke ausschenkt. Wenn du alle seine Zutaten erraten kannst, wird Nathaniel Hawk, dort drüben, äußerst beeindruckt sein. Ich bin mir sicher, dass er genauso wie Svenson, der Mann an der Theke, gerne in deiner Gesellschaft sein wird, beide respektieren gebildete Menschen.";
			link.l1.go = "Jino_3";
		break;
		
		// Лонгвэй
		case "Longway":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "'Alleine nun in einem fremden Land, fühle ich mich als Fremder, an diesem hellen Festtag sehne ich mich doppelt nach meinen Verwandten'";
			link.l1 = "Longway, hätte nie gedacht, dass du ein Meister des Wortes bist!";
			link.l1.go = "Longway_1";
		break;
		
		case "Longway_1":
			dialog.text = "Entschuldigung, Kapitän, ich habe viel nachgedacht. Das sind die Worte von Wang Wei - einem Dichter, der in einer Zeit der Tang-Dynastie lebte, die vor langer Zeit in meiner Heimat herrschte.";
			link.l1 = "Diese Worte sind so schön. Ich hoffe, eines Tages wirst du dein Heimatland wiedersehen...";
			link.l1.go = "Longway_2";
		break;
		
		case "Longway_2":
			dialog.text = "''Ist es möglich zu bürgen und zu wissen, dass es unter dem Bogen von mysteriösen Steinplatten unmöglich ist, einen Durchgang zu finden, jenseits dessen das U-Lin Tal liegt?'\nNein, Kapitän, du weißt es - Longway wird nicht nach Hause zurückkehren. Jetzt ist hier mein Zuhause und wir haben heute hier ein großes Ereignis! Ich sende meine besten Wünsche an dich und deine schöne Braut! Möge euer Glück so lang sein wie der mit Diamanten besetzte Yangtze-Fluss, zwischen den Perlen der Lotusblüten.";
			link.l1 = "Danke dir, mein alter Freund. Deine Worte sind nicht weniger schön als die von Wang Wei.";
			link.l1.go = "Longway_3";
		break;
		
		case "Longway_3":
			dialog.text = "Lassen wir uns einen trinken, Kapitän! Dieser Rum nimmt die Traurigkeit weg und erfrischt die Freude nicht schlechter als Maotai.";
			link.l1 = "Auf Ihre Gesundheit, Longway!";
			link.l1.go = "Longway_4";
		break;
		
		case "Longway_4":
			DialogExit();
			npchar.dialog.currentnode = "Longway_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Longway_4_1":
			dialog.text = "Große Hochzeit, Kapitän!";
			link.l1 = "Trink und hab Spaß!";
			link.l1.go = "Longway_4";
		break;
		
		// Книппель
		case "Knippel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "Schlag mir eine Kettenkugel! Alle unsere Leute gratulieren dir! Wie ist der Dienst gelaufen?";
				link.l1 = "Alles ist in Ordnung, Charlie! Jetzt bin ich offiziell verheiratet und respektabel, und meine erste Offizierin ist jetzt Madame de Monper.";
			}
			else
			{
				dialog.text = "Schlag mich mit einer Kettenkugel, so ein Ereignis, Kapitän! Fast jeder Baron der Brüderlichkeit ist hier! Ich schätze, jeder spanische Puritaner stellt sich die Hölle so vor! Und der Rum, der ist etwas Besonderes, eine Kettenkugel für mein Fass!";
				link.l1 = "Ja, die Leute hier sind nicht die gesetzestreuendsten, aber wir selbst sind keine Engel, Charlie, und jeder dieser Menschen ist mir auf seine Weise lieb.";
			}
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "Es ist wunderbar, Kettenkugel in meinem Hintern! Kapitän, ich meine, diese Feierlichkeit ist zu Ihrer Ehre, nun, ich... Ich gratuliere, ich meine... auch... Glück und... das, ich bin nicht gut in Reden. Aber Sie müssen wissen, dass wir Sie beide lieben und Ihnen sogar zur Hölle folgen würden, Kapitän!";
				link.l1 = "Danke dir, alter Freund.";
			}
			else
			{
				dialog.text = "Warte, ich meine... Was meine ich überhaupt, Kettenkugel in meinen Hintern?! Kapitän, ich meinte, dass dieser Tag zu deinen Ehren ist, also... Ich gratuliere dir... und auch... Ich wünsche dir Glück und... und entschuldige Kap, ich könnte ein bisschen zu betrunken sein, um eine Rede zu halten, Kettenkugel in meinen Hals, ich bin schon seit einer Weile nicht mehr nüchtern ha-ha-ha!";
				link.l1 = "Hah! Es ist in Ordnung... danke, alter Freund.";
			}
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry4", 20);
			dialog.text = "Ach! Und ja, Kapitän, nehmen Sie das bitte an. Für Sie und Ihre Dame. Ich habe diese Steine für einen Regentag aufgehoben... Ich verstehe, dass Sie keinen Mangel an Gold haben, aber sie werden nicht überflüssig sein, oder?";
			link.l1 = "Charlie, du bist wirklich eine großzügige Seele, und diese Smaragde werden in den Familienschmuckstücken von Madame de Monper großartig aussehen!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			dialog.text = "Nun, dann lasst uns darauf anstoßen, Kettenkugel auf mein... hm. Seid einfach glücklich, sowohl du als auch deine Schönheit, Kapitän!";
			link.l1 = "Wir werden, Charlie!";
			link.l1.go = "Knippel_4";
		break;
		
		case "Knippel_4":
			DialogExit();
			npchar.dialog.currentnode = "Knippel_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Knippel_4_1":
			dialog.text = "Tolle Hochzeit, Kapitän!";
			link.l1 = "Trink und hab Spaß!";
			link.l1.go = "Knippel_4";
		break;
		
		// Тонзаг
		case "Tonzag":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Ich hätte nie gedacht, Kapitän, dass ich Sie verheiratet sehen würde. Normalerweise führt der Weg, den wir gewählt haben, auf einen einsamen Pfad direkt in ein einsames Grab. In meiner Erinnerung sind Sie der Erste, der es geschafft hat, davon wegzukommen. Das ist einen zusätzlichen Toast wert, oder nicht?";
			link.l1 = "Das ist es, Kumpel! Und wirklich, ich bin froh, dass dieser Teil meines Lebens hinter mir liegt. Prost!";
			link.l1.go = "Tonzag_1";
		break;
		
		case "Tonzag_1":
			dialog.text = "Prost auf euch und euer langes und glückliches Leben zusammen! Verdammt, wenn ich euch so sehe, erinnere ich mich, dass ich selbst einmal verheiratet war.";
			link.l1 = "Du? Verheiratet? Interessante Sachen erzählst du mir! Aber was ist passiert?";
			link.l1.go = "Tonzag_2";
		break;
		
		case "Tonzag_2":
			dialog.text = "Was, denkst du, ich war schon immer ein alter Zyklop, der nach Schießpulver und Blut riecht, Kapitän? Aber nein. Madame Tonzag, sie... sie liebte mich, nehme ich an. Aber dann passierte eine unangenehme Geschichte. In der das Ehepaar Tonzag starb und nur der Narbengesichtige Gaston überlebte.";
			link.l1 = "Es tut mir leid, Hercule, ich wusste es nicht...";
			link.l1.go = "Tonzag_3";
		break;
		
		case "Tonzag_3":
			dialog.text = "Vergiss es, Kapitän, diese Geschichte ist schon lange her. Aber jetzt, wo ich dich anschaue, denke ich, dass meine Geschichte immer noch ein gutes Ende haben kann. Also, lass uns darauf trinken!";
			link.l1 = "Lass uns, Kumpel. Du weißt - seit dem Tag, als ich dich getroffen habe, habe ich dich immer wie meinen eigenen Vater angesehen, also hast du vielleicht eines Tages die Chance, ein großartiger Großvater zu sein. Wie auch immer, Prost! Ich muss mich um den Rest kümmern, wir werden später sprechen.";
			link.l1.go = "Tonzag_4";
		break;
		
		case "Tonzag_4":
			DialogExit();
			npchar.dialog.currentnode = "Tonzag_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tonzag_4_1":
			dialog.text = "Große Feier, Kapitän!";
			link.l1 = "Trink und hab Spaß!";
			link.l1.go = "Tonzag_4";
		break;
		
		// Бейкер
		case "Baker":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Hier ist unser Kapitän! Herzlichen Glückwunsch, du und deine Frau seid ein wunderschönes Paar! Möget ihr bis ans Ende eurer Tage glücklich leben!";
			link.l1 = "Danke dir, Raymond.";
			link.l1.go = "Baker_1";
		break;
		
		case "Baker_1":
			sTemp = "Sharptown";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) sTemp = "Sent Pierre";
			dialog.text = "Sieht so aus, als wären Sie für Ihre eigene Hochzeit zu nüchtern, Kapitän. Möchten Sie das beheben? Ich habe eine Flasche ausgezeichneten Sherry an der Bar genommen. Die Mischung mit dem lokalen Rum geht einfach gut!";
			link.l1 = "Ich würde gerne, aber jemand muss hier die Dinge im Auge behalten. Sonst, in "+sTemp+" nicht nur die Taverne wird fehlen, wenn der Morgen kommt.";
			link.l1.go = "Baker_2";
		break;
		
		case "Baker_2":
			DialogExit();
			npchar.dialog.currentnode = "Baker_2_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Tichingitu") != -1)
				{
					sld = characterFromId("Tichingitu");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "LongHappy_57";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Baker_2_1":
			dialog.text = "Ausgezeichnetes Essen und ausgezeichneter Rum, Kapitän! Prost auf Sie und Ihre junge Frau!";
			link.l1 = "Danke!";
			link.l1.go = "Baker_2";
		break;
		
		// Алексус
		case "Alexus":
			dialog.text = "Junge Leute, warum brecht ihr ein, darf ich fragen? Die Werft ist geschlossen, ist es nicht bemerkbar? Kommt morgen zurück.";
			link.l1 = "Herr, es tut mir leid, Sie zu stören, wir werden einfach durch die Verliese gehen. Es gibt Vorräte für die Hochzeit, die Taverne ist fast ausgetrunken.";
			link.l1.go = "Alexus_1";
		break;
		
		case "Alexus_1":
			dialog.text = "Oh, Charles de Maure und Nathan Hawk selbst! Ihr feiert doch jemandes Hochzeit, oder? Gut - holt euch euren Brennstoff. Junge Leute sollten Spaß haben - das ist zu jeder Zeit das Gesetz. Rasselt nur nicht auf dem Rückweg mit den Flaschen - ich gehe schlafen!";
			link.l1 = "Danke, Meister, wir werden so still sein wie der ruhigste Fluss.";
			link.l1.go = "Alexus_2";
		break;
		
		case "Alexus_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			pchar.GenQuestBox.Bermudes_Dungeon = true;
			pchar.GenQuestBox.Bermudes_Dungeon.box3.items.potionwine = 100;
			pchar.quest.longhappy_isla_box.win_condition.l1 = "locator";
			pchar.quest.longhappy_isla_box.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator_group = "box";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator = "box3";
			pchar.quest.longhappy_isla_box.function = "LongHappy_IslaTesoroDungeon";
		break;
		
		case "Alexus_2_1":
			dialog.text = "Los, steh nicht rum, geh! Nun, Kapitän, bist du mit allem zufrieden?";
			link.l1 = "...";
			link.l1.go = "Alexus_2_2";
		break;
		
		case "Alexus_2_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
		break;
		
		// пиратус в подземелье
		case "DungeonPirate":
			dialog.text = "Was zum Teufel?! Jacques hat gesagt 'Niemand kommt hier runter'! Hugo - renne zurück, ruf die anderen, wir räumen den Weg. Tötet sie, Jungs!";
			link.l1 = "Scheiße!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BandosInDungeonFight");
		break;
		
		// киллеры
		case "killer":
			dialog.text = "Jungs, vergesst die Kisten, wir haben Gäste!";
			link.l1 = "Ich dachte, Bastarde wie du wären mit Jackman getötet worden. Gut, beenden wir das!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_ResidenceFight");
		break;
		
		case "killer_1":
			dialog.text = "Verdammt... Wir wurden entdeckt! Alarm!";
			link.l1 = "Mach Platz, Arschloch!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernKillerFight");
		break;
		
		// Ангерран
		case "Shivo":
			dialog.text = "Herr de Maure, guten Abend, oder ist es schon fast Morgen? Kommen Sie herein, nehmen Sie Platz.";
			link.l1 = "Angerran De Chievous! Wen ich nicht überrascht bin zu sehen! Die Bedeutungslosigkeit, die nur mit Frauen kämpfen kann! Hast du sie auch gefesselt?! Jetzt werde ich beenden, was ich in diesem Duell auf Martinique begonnen habe!";
			link.l1.go = "Shivo_1";
		break;
		
		case "Shivo_1":
			dialog.text = "Beruhige dich, junger Mann, siehst du diese Pistole? Sie hat zwei Läufe. Vielleicht bin ich schlecht im Fechten, aber ich schieße ziemlich genau - leg dein Schwert nieder, oder du wirst ein paar schöne Damen verpassen, das versichere ich dir.";
			link.l1 = "Schuft... Verdammt seist du.";
			link.l1.go = "Shivo_2";
		break;
		
		case "Shivo_2":
			dialog.text = "Und Sie, Monsieur Pirat, legen Sie Ihre Waffe auch ab, genau so, ja. Und jetzt - setzen Sie sich, Sie können den Wein einschenken - dort drüben auf dem Tisch. Wir müssen ein wenig warten, bis Monsieur Barbazon fertig ist, die Schiffe Ihrer Freunde, der Piratenbarone, zu zerschlagen. Dann werden wir entscheiden, wie Sie und ich unsere... hm, Unstimmigkeiten beilegen werden.";
			link.l1 = "Streitigkeiten beilegen? Und wie? Willst du ein Duell?";
			link.l1.go = "Shivo_3";
		break;
		
		case "Shivo_3":
			dialog.text = "Sei nicht so lustig, Charles. Du und Madame Botot habt mir eine Menge Ärger bereitet, und ich beabsichtige, euch voll zu vergelten. Obwohl sie mir viel mehr Probleme bereitet hat als du... aber wenn du und der imposante Monsieur Pirat ruhig sitzen bleibt, dann gebe ich dir mein Ehrenwort - eure Frauen werden am Leben bleiben. Ich denke, in den spanischen Kolonien auf Maine sind solche Sklaven geschätzt. Selbst inoffiziell. Aber das ist immer noch Leben, nicht wahr?";
			link.l1 = "Angerran, du bist ein Feigling, ein Bastard und... Scheiße, es gibt noch keine passenden Worte für dich in irgendeiner Sprache!";
			link.l1.go = "Shivo_4";
		break;
		
		case "Shivo_4":
			dialog.text = "Du weißt es, du hast keine Wahl. Ich kann nur versprechen, dass es schnell sein wird. Also, wenn du diese Frauen liebst - benimm dich, rette ihr Leben und erleichtere dein Schicksal. Und ja - schließe die Tür ab, wenn es dir nicht zu schwer fällt. Danke.";
			link.l1 = "";
			link.l1.go = "Shivo_5";
		break;
		
		case "Shivo_5":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Shivo_6":
			dialog.text = "So kriegerische Damen. Ich werde euch trotzdem bitten, vorsichtig zu sein. Habe es nie geliebt, Frauen zu töten.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Shivo_7":
			dialog.text = "Scheiße...";
			link.l1 = "Stirb, Schurke!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Дюссак
		case "Dussak":
			dialog.text = "Kapitän Charles de Maure, Baron Hawk - welch angenehme Überraschung! Lassen Sie mich mich vorstellen - Mauritz Dussak, so heißt ich.";
			link.l1 = "Komm aus meinem Weg, Bastard! Wo ist meine Frau?!";
			link.l1.go = "Dussak_1";
		break;
		
		case "Dussak_1":
			dialog.text = "Beruhigt euch, Herren! Seht ihr diese Pistole? Sie hat zwei Läufe. Man hat mir diesen Spitznamen nicht ohne Grund gegeben - ich liebe Säbel, sicher... aber ich kann auch gut schießen, glaubt mir. Legt eure Schwerter nieder, oder ihr werdet ein paar eurer Damen vermissen!";
			link.l1 = "Ich werde dich wie ein Schwein schlachten, Abschaum...";
			link.l1.go = "Dussak_2";
		break;
		
		case "Dussak_2":
			dialog.text = "Aber du wirst bereits ein Witwer sein. Willst du das nicht? Dann beruhige dich und lege deine Waffe nieder. Baron Hawk, bitte, schließe die Tür ab. Und wir werden uns beruhigen und ein wenig warten, während Jacques Barbazon dort im Hafen die Anführer der Bruderschaft erledigt.";
			link.l1 = "Und was kommt als nächstes? Werden wir uns umarmen und gemeinsam in den Sonnenuntergang gehen?";
			link.l1.go = "Dussak_3";
		break;
		
		case "Dussak_3":
			dialog.text = "Ich glaube nicht. Für deine Gefangenschaft wird Jacques mich mit Gold überhäufen, mit Glück werde ich vielleicht ein Baron. Was deine Frauen betrifft, vielleicht lassen wir sie gehen, aber was dich betrifft - leider ... Wenn du Glück hast, werde ich um das Recht bitten, dich persönlich zu töten, Kapitän. Du bist ein berühmter Fechter - es wäre interessant, dich zu testen. Du weißt, ich halte mich auch für einen Meister.";
			link.l1 = "Ein Meister darin, nachts in Häuser einzubrechen und halbschlafende Frauen zu fesseln? Du bist ein Wurm, darüber hinaus - ein stinkender Wurm!";
			link.l1.go = "Dussak_4";
		break;
		
		case "Dussak_4":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Dussak_5":
			dialog.text = "Hören Sie, Madame, ich habe noch nie Frauen getötet, bringen Sie mich nicht dazu, in Ordnung? Sie beunruhigen den Kapitän und Ihren Ehemann... Verdammt!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Dussak_6":
			dialog.text = "Scheiße...";
			link.l1 = "Stirb, du Bastard!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Барбазон
		case "Barbazon_boarding":
			dialog.text = "Verfluchter Franzose, gab es denn kein Säbel oder eine Kugel?!";
			link.l1 = "Weißt du, Jacques, ich habe beides für dich. Ehrlich gesagt, ich bedauere fast, dass ich dich am Leben gelassen habe, als ich von deinen Tricks mit Jackman erfahren habe. Aber jetzt werde ich es in Ordnung bringen.";
			link.l1.go = "Barbazon_boarding_1";
		break;
		
		case "Barbazon_boarding_1":
			dialog.text = "Du bist also nur mutig, wenn du mit einer Horde deiner Kerle herumläufst? Lass uns die Situation ändern! Mit den Baronen werde ich später fertig, aber du wirst hier nicht lebend rauskommen, Ratte!";
			link.l1 = "Erwartet...";
			link.l1.go = "Barbazon_boarding_2";
		break;
		
		case "Barbazon_boarding_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			AddItems(npchar, "potion2", 1);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "LongHappy_BarbAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			sld = GetCharacter(NPC_GenerateCharacter("LH_BarbCabinHelper", "citiz_57", "man", "man", 35, PIRATE, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 70, 70, "blade_21", "pistol4", "bullet", 300);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			AddItems(sld, "potion2", 2);
		break;
		
		// официантка
		case "waitress":
			dialog.text = "Kapitän, Hilfe, dieser Wilde, er hat mich entführt! Ich... Ich muss nach Hause - Onkel hat wahrscheinlich schon die ganze Stadt auf den Kopf gestellt!";
			link.l1 = "Beruhige dich, Schönheit, alles wird gut. Tritt zur Seite, ich muss mit deinem 'Wilden' sprechen.";
			link.l1.go = "waitress_1a";
		break;
		
		case "waitress_1a":
			DialogExit();
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "waitress_1":
			dialog.text = "Danke, Kapitän! Sie haben mich gerettet! Als ich heute Morgen an diesem Strand aufgewacht bin, ich... kann nicht glauben, dass ich vorhatte, diesen Wilden zu heiraten, er...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 94)
			{
				link.l1 = "Ja, der Morgen ist ein strenger Hammer für die nächtliche Hoffnungskristall. Verstehe. Aber er stammt aus dem Stamm der Muscogue und lebt nach den harten Gesetzen seines Landes. Er hat dich mit deiner Zustimmung entführt, und ihr habt die Nacht zusammen verbracht. So seid ihr jetzt in den Augen seiner Götter Mann und Frau. Lass uns deine Sachen packen, und ich werde das Lösegeldproblem mit deinem Onkel klären.";
				link.l1.go = "waitress_2";
			}
			link.l2 = "Es tut mir leid für das. Tichingitu lebt nach den Gesetzen seines Stammes, aber er ist eine gute Person. Bitte, vergiss diese Entführungsgeschichte.";
			link.l2.go = "waitress_5";
		break;
		
		case "waitress_2":
			dialog.text = "Ehefrau? In den Augen seiner Götter?! Nein, Kapitän, ich flehe Sie an, retten Sie mich vor diesem! Es war nur... ein Abenteuer, er war so galant und nett, nicht wie diese Tölpel... Aber heiraten? Ich bin zu jung, um in eine Hütte zu einem Wilden zu ziehen!";
			link.l1 = "Er ist mein Offizier und mein bester Freund, also mach dir keine Sorgen, ich bezahle ihm gut, und du wirst die beste Hütte haben, die du dir je gewünscht hast. Tichingitu ist ein guter Jäger, er wird dir Essen beschaffen, und du wirst Kinder gebären und aufpassen.";
			link.l1.go = "waitress_3";
		break;
		
		case "waitress_3":
			dialog.text = "Kinder? Essen beschaffen?! Nein Kapitän, bitte tu mir das nicht an, ich flehe dich an!";
			link.l1 = "Nun, vielleicht kann ich ihn überzeugen. Aber es wird nicht einfach sein. Der Stamm der Muskogee nimmt solche Dinge sehr ernst, wenn jemand herausfindet, dass er eine Squaw gestohlen hat und nicht geheiratet hat...";
			link.l1.go = "waitress_4";
		break;
		
		case "waitress_4":
			dialog.text = "Du musst es versuchen, bitte! Ich werde niemandem etwas sagen, niemand wird es erfahren! Ich werde Onkel anlügen, es ist nicht das erste Mal!";
			link.l1 = "Gut, du solltest gehen, schöne Squaw. Ich werde versuchen, meinen Freund fernzuhalten.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_5":
			dialog.text = "Er hat mich gestohlen wie... wie eine Ziege aus einer Scheune! Ich werde es jedem erzählen! Onkel wird ihn töten! Er ist schrecklich in Wut! Er hat früher spanische Schiffe ausgeraubt - mit ihm sind Scherze schlecht!";
			link.l1 = "Also gut, schweig, schöne Dame, schweig. Vielleicht werden zwanzigtausend 'Gründe' ihn zu vergeben, eloquenter sein als meine Worte? Oder soll ich sie deinem Onkel geben, wie ein Lösegeld für eine Frau? Schließlich sind alle auf der Insel, nicht wahr? Morgen können wir eine weitere Hochzeit organisieren...";
			link.l1.go = "waitress_6";
		break;
		
		case "waitress_6":
			if (sti(Pchar.money) >= 20000) AddMoneyToCharacter(pchar, -20000); 
			dialog.text = "Nein nein, Kapitän, warte! Du hast mich überzeugt. Ich werde mir etwas einfallen lassen, damit mein Onkel nicht wütend ist. Lebewohl! Und auf Wiedersehen, mein Hengst aus den fernen Ebenen! Sieh mich das nächste Mal, wenn du besuchst...";
			link.l1 = "Das stimmt. Schön, dass wir uns einig sind. Lauf nach Hause, Schönheit.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// тавернщик Сен Пьер
		case "tavernkeeper":
			dialog.text = "Nun, Kapitän, sind Sie mit allem zufrieden? Der feinste Rum, Lammrippen, Schweinehämme und sogar hervorragender Wein aus meinen persönlichen Vorräten für Ihren wissenschaftlichen Freund! Und - meine Glückwünsche an Sie und Ihre schöne Frau!";
			link.l1 = "Danke! Ich muss zugeben, du hast alles perfekt organisiert. Ich hoffe, du hast genug Rumvorräte in deinen Kellern, der Morgen ist noch fern.";
			link.l1.go = "tavernkeeper_1";
		break;
		
		case "tavernkeeper_1":
			dialog.text = "Machen Sie sich keine Sorgen, wenn die Fässer den Boden zeigen, schicke ich einen Gehilfen zum Hafenlager. Viel Spaß, mein Herr, und machen Sie sich keine Sorgen um irgendwas.";
			link.l1 = "Gut, "+npchar.name+". Dann werde ich zu meinen Gästen gehen.";
			link.l1.go = "tavernkeeper_2";
		break;
		
		case "tavernkeeper_2":
			DialogExit();
			npchar.dialog.currentnode = "tavernkeeper_3";
		break;
		
		case "tavernkeeper_3":
			dialog.text = "Was wünschen Sie, Kapitän? Gebratene Rippen, geräucherter Schinken oder Bruststück? Vielleicht Wein für Ihre bessere Hälfte?";
			link.l1 = "";
			link.l1.go = "tavernkeeper_2";
		break;
		
		// моряки в таверне Сен Пьер
		case "sailor":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Auf die Gesundheit des Kapitäns und seiner Frau!","Mögest du glücklich bis ans Ende deiner Tage leben, Kapitän!","Lang lebe das Glück von euch beiden!"),LinkRandPhrase("Hurra auf den Kapitän und seine Schönheit!","Kapitän und Gattin mögen ihr ganzes Leben lang Glück haben!","Glückliche Familienzeit, Käpt'n!"));
			link.l1 = LinkRandPhrase("Danke!","Danke dir!","Prost!");
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor";
		break;
		
		// босс Ле Франсуа
		case "JanDavid":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Bist du wahnsinnig? Wolltest du den Schlachter spielen? Alle Piraten sind wütend auf dich, Kumpel, also solltest du diesen Ort besser verlassen.","Es scheint, Kumpel, dass du verrückt geworden bist. Wolltest du ein bisschen die Hände ausstrecken? Nichts für ungut, aber du hast hier nichts zu tun. Verschwinde!");
				link.l1 = RandPhraseSimple("Hör zu, ich möchte die Situation klären...","Hilf mir, das Problem zu lösen...");
				link.l1.go = "pirate_town";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron"))
			{
				if (!CheckAttribute(npchar, "quest.Baron"))
				{
					dialog.text = "Ach, ich habe auf deinen Besuch gewartet, Boss. Jan Svenson hat gewarnt, dass du definitiv kommen würdest, um zu überprüfen, wie es in Le Francois läuft. Ich habe alles in meine eigenen Hände genommen und schwöre beim Donner, dieses Dorf wird besser leben als mit dem verdammt Kindman, mögen die Teufel Spaß mit ihm in den dunkelsten Kellern der Hölle haben!";
					link.l1 = "Du bist Jean David, richtig? Svenson hat etwas über meinen Anteil gesagt...";
					link.l1.go = "JanDavid_2";
				}
				else
				{
					dialog.text = TimeGreeting()+" Chef. Alles ist gut in Le Francois, wie immer. Warum bist du gekommen? Kann ich dir bei etwas helfen?";
					link.l1 = "Nur vorbeigeschaut, um zu sehen, wie es läuft.";
					link.l1.go = "JanDavid_1";
					if (sti(pchar.questTemp.LongHappy.BaronMoney) > 0)
					{
						link.l2 = "Was ist mit meinem Anteil?";
						link.l2.go = "JanDavid_5";
					}
				}
			}
			else
			{
				dialog.text = TimeGreeting()+" Kamerad. Warum bist du gekommen? Kann ich dir bei etwas helfen?";
				link.l1 = "Bin nur vorbeigekommen, um Hallo zu sagen.";
				link.l1.go = "JanDavid_1";
			}
		break;
		
		case "JanDavid_1":
			DialogExit();
			npchar.dialog.currentnode = "JanDavid";
		break;
		
		case "JanDavid_2":
			npchar.quest.Baron = "true";
			dialog.text = "Zu Ihren Diensten, Boss! Was den Anteil betrifft - am fünften jeden Monats wird Ihnen ein Teil der Goldmünzen aus den Taten unserer Jungs abgezogen, und es wird so lange auf Sie warten, wie Sie es brauchen. Ab nächsten Monat können Sie dafür kommen.";
			link.l1 = "Schön!";
			link.l1.go = "JanDavid_3";
		break;
		
		case "JanDavid_3":
			dialog.text = "Und ich kümmere mich um den Rest. Der Waldteufel sagte, dass du keine Zeit hättest, dich mit solchen Kleinigkeiten wie Le Francois zu beschäftigen...";
			link.l1 = "Du wurdest richtig informiert. Gut, Jean, ich verlasse mich auf dich, ich hoffe, du lässt mich nicht im Stich.";
			link.l1.go = "JanDavid_4";
		break;
		
		case "JanDavid_4":
			dialog.text = "Alles wird gut, Käpt'n. Alles ist hier unter Kontrolle, ha-ha, und ich darf keinen Rum mehr trinken bis ans Ende meiner Tage, wenn ich etwas vermassle!";
			link.l1 = "Gut, wir sehen uns!";
			link.l1.go = "JanDavid_1";
			// запуск отчисления доли
			pchar.questTemp.LongHappy.BaronPart = "true";
			pchar.questTemp.LongHappy.BaronMoney = 0;
		break;
		
		case "JanDavid_5":
			dialog.text = "Warten auf Sie, Chef. In dieser Zeit haben wir für Sie gesammelt "+FindRussianMoneyString(sti(pchar.questTemp.LongHappy.BaronMoney))+". Nimm es.";
			link.l1 = "Ha, nicht schlecht. Gut gemacht, Jean.";
			link.l1.go = "JanDavid_6";
		break;
		
		case "JanDavid_6":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.LongHappy.BaronMoney));
			pchar.questTemp.LongHappy.BaronMoney = 0;
			dialog.text = "Ich gebe mein Bestes, Boss. Komm nächsten Monat zurück oder wann immer du willst - dein Geld ist bei mir sicher.";
			link.l1 = "Gut, wir sehen uns, Jean.";
			link.l1.go = "JanDavid_1";
		break;
		
		case "pirate_town":
             dialog.text = "Das Problem lösen? Haben Sie eine Ahnung, was Sie getan haben? Wie auch immer, bringen Sie mir eine Million Pesos und ich werde die Jungs überreden, Ihre Tat zu vergessen. Wenn Ihnen die Idee nicht gefällt, können Sie zur Hölle fahren.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Gut, ich bin bereit zu zahlen.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Habe es verstanden. Ich gehe jetzt.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Gut! Betrachte dich wieder als rein. Aber ich hoffe, dass du solche widerlichen Dinge nicht wieder tun wirst.";
			link.l1 = "Ich werde nicht. Viel zu teuer für mich. Lebewohl...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
} 
