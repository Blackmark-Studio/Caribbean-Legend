// Ричард Флитвуд - английский капитан
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "Start_main")
				{
					dialog.text = "Grüße, Kapitän! Lassen Sie sich nicht von meinem Aussehen ablenken, es geht mir gut, fast blind, aber mir geht es gut. Lassen Sie mich vorstellen, ich bin Richard Fleetwood.";
					link.l1 = "Guten Tag, es ist ein Vergnügen Sie zu treffen, ich bin der Kapitän "+GetFullName(pchar)+".";
					link.l1.go = "First_Task";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "GotoPortoffice")
				{
					if (int(Pchar.Ship.Type) != SHIP_NOTUSED)
					{
						dialog.text = "Ich habe Sie gebeten, Ihr Schiff zu vertäuen. Hören Sie mir überhaupt zu?";
						link.l1 = "Sicher, das tue ich. Ich kümmere mich darum.";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Also, du bist wieder hier. Übernimm das Kommando über die 'Walküre' - meine Mannschaft ist über die Details informiert - und segle nach Bridgetown. Besuche jede interessante Person in der Stadt und verbreite die Gerüchte, über die wir gesprochen haben. Dann sei bereit, dass der Bastard angreift. Ändere das Schiff nicht und bilde keine Staffel, sonst wird er eine Falle vermuten und nicht auftauchen\nDu musst sein Schiff entern und es nach St. John's bringen. Es ist unerlässlich, dass du das Logbuch des Piraten findest, denn es ist der einzige Beweis, den wir jemals für Lucas Rodenburgs Beteiligung haben werden. Ich bin mir sicher, dass du das schaffst. Gott mit dir, Kapitän.";
						link.l1 = "Dankbarkeit! Ich werde den Job gemäß unserem Plan erledigen.";
						link.l1.go = "First_Task_3";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
					}
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "MirageTake")//а вот теперь начинается перебор кораблей
				{
					pchar.quest.ToAntiguaMirageOver.over = "yes"; //снять таймер
					int iMir = 0;
					int iVal = 0;
					for(i = 0; i < COMPANION_MAX; i++)
					{
						iTemp = GetCompanionIndex(PChar, i);
						if(iTemp > 0)
						{
							sld = GetCharacter(iTemp);
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							if(int(RealShips[int(sld.ship.type)].basetype) == SHIP_MIRAGE)
							{
							iMir = 1;
							RealShips[int(sld.Ship.Type)].ship.upgrades.hull = 1;//чистый корпус
							SetShipSailsFromFile(sld, "ships/parus_silk.tga");
							SetSailsColor(sld, 0);//белый хлопковый парус
							DeleteAttribute(sld, "ship.sails");//починить паруса
							DeleteAttribute(sld, "ship.masts");//вернуть мачты
							}
							if(int(RealShips[int(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
						}
					}//установили признак наличия кораблей в эскадре.
					if (iMir == 1 && iVal == 0)//потеряли Валькирию
					{
						dialog.text = "Sie sind zurück, Kapitän... Ich weiß bereits alles über Ihre Reise.";
						link.l1 = "Tun Sie das? Dann müssen Sie wissen, dass...";
						link.l1.go = "Fleetwood_lostVal";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 1)//потеряли Мираж
					{
						dialog.text = "Du bist zurück, Kapitän... Ich weiß bereits alles über deine Reise.";
						link.l1 = "Tun Sie das? Dann müssen Sie auch wissen, dass...";
						link.l1.go = "Fleetwood_lostMir";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 0)//а это вообще плохо
					{
						dialog.text = "Du bist zurück, Kapitän... Ich weiß bereits alles über deine Reise.";
						link.l1 = "Tust du? Also musst du wissen, dass...";
						link.l1.go = "Fleetwood_lostFull";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
						dialog.text = "Sie sind zurück, Kapitän... Ich weiß bereits alles über Ihre Reise.";
						link.l1 = "Tun Sie das? Dann müssen Sie wissen, dass...";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "toAntigua")
				{
					dialog.text = "Grüße, mein Freund! Schön, dich zu sehen! Hast du Abigail an Bord deines Schiffes?";
					link.l1 = "Leider nicht, Richard. Sie weigerte sich, mit mir zu gehen, weil ihre Abreise für ihren Vater, der bereits jeden einzelnen Taler verloren hat, ein schwerer Schlag wäre. Ich habe beschlossen, das Problem zu lösen und Salomons Geld und diese Insel zu finden...";
					link.l1.go = "Fleetwood_LastTask";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				dialog.text = "Gibt es sonst noch etwas, Kapitän?";
				link.l1 = "Nein, ich gehe schon.";
				link.l1.go = "exit";		
				NextDiag.TempNode = "First time";
			}
				dialog.text = "Sonst noch etwas, Kapitän?";
				link.l1 = "Nein, ich gehe schon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Fleetwood_abordage":
			PlaySound("Voice\English\hambit\Richard Flitwood-03.wav");
			dialog.text = "Verdammter Pirat! Du hast den Enterkampf gewonnen, aber ich werde meine Pflicht trotzdem erfüllen. Ich habe arrangiert, dass der Pulverraum in die Luft geht und mein Schiff wird bald zusammen mit deinem 'Geisterschiff' explodieren. Du wirst kein einziges englisches Schiff mehr versenken. Ich werde mit Ehre sterben!";
			link.l1 = "Es tut mir leid, dich enttäuschen zu müssen, aber du liegst falsch, Fleetwood. Es gibt keine Piraten auf meinem Schiff, ich habe schon früher mit ihnen zu tun gehabt. Ich brauchte dich und dieses Schiff diente als eine nette Falle.\nGenug der freundlichen Worte, ich muss dich noch töten und von deinem brennenden Kahn wegkommen!";
			link.l1.go = "Fleetwood_abordage_1";
		break;
		
		case "Fleetwood_abordage_1":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.HWIC.Holl = "FleetwoodCapture";
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "First_Task":
			dialog.text = "Charlie hat mich bereits über Ihre erfolgreiche Abfangaktion des feindlichen Handelskarawane informiert. Es freut mich, Sie kennenzulernen, England braucht solche mutigen Kapitäne. Nun, lassen Sie mich Ihnen etwas von großer Bedeutung erzählen.";
			link.l1 = "Ich höre zu, Herr Fleetwood.";
			link.l1.go = "First_Task_1";			
		break;
		
		case "First_Task_1":
			dialog.text = "Ein Pirat hat im gesamten Archipel Gewaltakte begangen und sich dabei als der 'Fliegende Holländer', ein legendäres Geisterschiff, ausgegeben. Er gibt vor, der 'Fliegende Holländer' zu sein, ein legendäres Geisterschiff. Ich bin mir sicher, dass er ein Holländer ist, aber er kann nicht fliegen. Ich neige dazu zu glauben, dass dies ein Söldner von Lucas Rodenburg ist, einem Vize-Direktor der Niederländischen Westindien-Kompanie.\nRodenburg hat einen Schattenhandelskrieg gegen England erklärt - dieses 'Geisterschiff' greift nur Handelsschiffe unter der englischen Flagge an. Es ist für die Gesellschaft von entscheidender Bedeutung, unseren Einfluss in diesem Gebiet zu schwächen, ohne einen echten Krieg zu führen.\nIch jage dieses Geisterschiff schon eine Weile, aber ihr Kapitän ist ein sehr erfahrener Seemann und sein Schiff ist schnell und flink.\nDa es unmöglich ist, den Schakal im offenen Kampf zu fangen, sollten wir schlau handeln und der jüngste Mordversuch an mir wird uns sehr zugute kommen. Was denken Sie darüber, Kapitän? Haben Sie Angst?";
			link.l1 = "Keine Chance. Ich würde Ihnen gerne helfen, diesen Bastard aufzuspüren und zu versenken. Sie wollten mich das fragen, habe ich recht?";
			link.l1.go = "First_Task_2";	
		break;
		
		case "First_Task_2":
			dialog.text = "Du hast Recht. Jetzt sprechen wir über Details. Meine Leute werden das Gerücht verbreiten, dass ich fast tot bin und mein Schiff die 'Walküre' an dich verkauft habe. Dann führen wir unsere kleine Täuschung fort. Du wirst dich als Kaufmann ausgeben, der die Brigg von mir gekauft hat und die meisten Kanonen losgeworden ist.\nDeshalb ist deine Aufgabe, nach Barbados zu segeln und jedem dort zu erzählen, dass deine Laderäume mit wertvoller Fracht gefüllt sind und deine Taschen mit Münzen gefüllt sind. Lass sie wissen, dass du bald in See stechen wirst. Spiele die Rolle eines gierigen, einfachen, aber reichen Kaufmanns.\nUnser verdammter Holländer erhält seine Informationen über Handelsschiffe durch Bridgetown. Es ist unbekannt, wer ihn genau damit versorgt. Jeder steht unter Verdacht - von einem lokalen Kaufmann bis zum Gouverneur, obwohl die letzte Möglichkeit ziemlich beängstigend ist.\nÜbernimm mein 'Walküre' und ihre Besatzung. Aber zuerst solltest du all deine Schiffe hier lassen, ich habe bereits mit dem örtlichen Hafenmeister gesprochen, es wird 10.000 Pesos pro Monat für dein Flaggschiff kosten.\nWenn das erledigt ist, komm zu mir zurück und ich werde Vorkehrungen treffen. Ach, Kapitän, vergiss nicht, deinen Anteil für die Gefangennahme des Silberkarawane und zehntausend für den Hafenmeister zu nehmen, das Geld ist in der Kommode.";
			link.l1 = "Ich habe es verstanden, Herr Fleetwood. Ich werde zum Hafenmeister gehen.";
			link.l1.go = "exit";	
			pchar.questTemp.HWIC.Eng = "GotoPortoffice";
			bDisableFastReload = false;//откроем быстрый переход
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			AddLandQuestMark(characterFromId("SentJons_PortMan"), "questmarkmain");
		break;
		
		case "First_Task_3":
			DialogExit();
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.EngEquip = "true"; //форма солдат
			pchar.questTemp.HWIC.Eng = "GotoBridgetown";
			GetValckiriaToCharacter(pchar);
			pchar.quest.Knippel_Officer.win_condition.l1 = "location";
			pchar.quest.Knippel_Officer.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Knippel_Officer.function = "KnippelToOfficer";
			pchar.questTemp.HWIC.Eng.BridgeCounter = 0;//счетчик посещений неписей Бриджтауна по квесту
			AddQuestRecord("Holl_Gambit", "2-5");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_shipyarder"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Mayor"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_usurer"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_PortMan"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Hostess"), "questmarkmain");
		break;
		
		//изымаем корабль
		case "Fleetwood_lostMir":
			dialog.text = "Ja, mir ist bewusst, dass du es nicht geschafft hast, das Piratenschiff zu erobern. All meine Pläne sind ruiniert. Ich nehme dir die 'Walküre' weg. Du kannst jetzt gehen, ich brauche deine Dienste nicht mehr.";
			link.l1 = "Es tut mir so leid dafür. Auf Wiedersehen, Herr Fleetwood.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
		break;
		
		case "Fleetwood_lostVal":
			dialog.text = "Ja, mir ist bewusst, dass Sie die 'Walküre' verloren haben. Es war das Unannehmbarste... Ich werde das eroberte Piratenschiff wegnehmen. Sie können jetzt gehen, ich brauche Ihre Dienste nicht.";
			link.l1 = "Es tut mir so leid dafür. Auf Wiedersehen, Herr Fleetwood.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_MIRAGE;
		break;
		
		case "Fleetwood_lostFull":
			dialog.text = "Ja, mir ist bewusst, dass du ein seltener Stümper und Pfuscher bist. Du hast das Piratenschiff nicht erobert und meine 'Walküre' verloren. Ich bin wirklich enttäuscht von dir. Geh weg!";
			link.l1 = "Es tut mir so leid dafür. Auf Wiedersehen, Herr Fleetwood.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Knippel");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Книппеля из офицеров
			sld = characterFromId("Knippel");
			ChangeCharacterAddressGroup(sld, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of Richard Fleetwood. Well, you have got nothing to do on Antigua now...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of Richard Fleetwood. Well, you have got nothing to do on Antigua now...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_complete":
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");	
			if (CheckCharacterItem(pchar, "JacobJournal"))//проверяем журнал
			{
				dialog.text = "Ja, mir ist bewusst, dass du unseren Plan erfolgreich umgesetzt hast. Du hast den bösen Piraten eliminiert und sein Schiff erobert. Wie lautet der echte Name von ihr?";
				link.l1 = "Fata Morgana";
				link.l1.go = "Abigile";
			}
			else//нет журнала - нет продолжения квеста
			{
				dialog.text = "Ja, ich bin mir bewusst, dass du unseren Plan erfolgreich umgesetzt hast. Du hast den bösen Piraten beseitigt und sein Schiff erobert. Ich werde meine 'Walküre' zurücknehmen. Du kannst das Piratenschiff als Preis behalten. Es wird auch eine Art... Entschädigung dienen. Dein im Hafen verankertes Schiff hat gebrannt, als das Feuer auf den Docks begann, sich auszubreiten. Ich entschuldige mich für die Unannehmlichkeiten, "+pchar.name+"... Ich hoffe, das Geisterschiff wird Ihnen besser dienen.\nIch habe angeordnet, dass Ihr neues Schiff von dem hartnäckigen Schmutz und Seetang gereinigt wird. Sie werden auch Ihre Schönheit in neue Segel aus bester Baumwolle kleiden.\nSchließlich akzeptieren Sie bitte Ihre Belohnung von 100 000 Pesos und dieses Navigationstool. Ich wollte es immer einem würdigen Seemann präsentieren und Sie haben dort draußen eine bewundernswerte Arbeit geleistet! Nun, die Zeit ist gekommen, um Abschied zu nehmen, ich habe hier meine Geschäfte erledigt und sollte nach Europa zurückkehren. Viel Glück, Kapitän!";
				link.l1 = "Gleichfalls, Richard!";
				link.l1.go = "exit";
				LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//закроем Флитвуда в комнате и пусть там сидит
				pchar.questTemp.HWIC.Eng = "end";
				pchar.questTemp.HWIC.Detector = "eng_win_half";
				CloseQuestHeader("Holl_Gambit");
			}
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "bussol");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			AddSimpleRumourCity("They say that you and Richard Fleetwood has planned some military operation and you have personally destroyed that elusive pirate who has been robbing our trade ships. You are a real hero, captain!", "SentJons", 20, 3, "");
		break;
		
		case "Abigile":
			dialog.text = "Fata Morgana? Ein sehr passender Name, würde ich sagen... Ich werde meine 'Walküre' von dir zurücknehmen und daher kannst du das Piratenschiff als Preis behalten. Es wird auch als eine Art Entschädigung dienen. Dein im Hafen verankertes Schiff brannte nieder, als das Feuer auf den Docks begann sich auszubreiten. Es tut mir leid, "+pchar.name+"... Ich hoffe, das Geisterschiff wird Ihnen besser dienen.\nIch habe angeordnet, Ihr neues Schiff von diesem hartnäckigen Schmutz und Seegras zu reinigen. Sie werden Ihre Schönheit auch in neue Segel aus bester Baumwolle kleiden.\nSchließlich akzeptieren Sie Ihre Belohnung von 100.000 Pesos und dieses Navigationswerkzeug, ich wollte es immer einem würdigen Seemann übergeben... Sie haben dort draußen gute Arbeit geleistet und ich bin stolz auf Sie! Haben Sie das Logbuch des Bastards?";
			link.l1 = "Ja, sicher. Hier ist es, nimm es. Ich möchte dich etwas fragen, gibt es irgendeinen... Asiaten unter den Söldnern von Lucas Rodenburg?";
			link.l1.go = "Abigile_1";			
		break;
		
		case "Abigile_1":
			RemoveItems(PChar, "JacobJournal", 1);
			dialog.text = "Ja, das gibt es. Chinese Longway, ein Kapitän auf seinem privaten Schiff 'Meifeng'. Haben Sie das aus dem Piratenlogbuch gelesen? Lassen Sie uns mal sehen...(liest) Na, na. Wie ich erwartet habe, war Lucas Rodenburg hinter all dem! Nun, was auch immer, es ist jetzt nicht unsere Sorge... Unser Generalgouverneur wird sich um diesen Bastard kümmern. Lucas Rodenburg wird die Verantwortung für alles, was er getan hat, übernehmen müssen!";
			link.l1 = "Hm, interessant, und wie wird der englische Generalgouverneur in der Lage sein, mit einem Untertan Hollands 'umzugehen'?";
			link.l1.go = "Abigile_2";			
		break;
		
		case "Abigile_2":
			dialog.text = "Es gibt immer politische Fäden zu ziehen, mein lieber Freund... Holland wird zugeben müssen, dass sie den Handelskrieg gegen England begonnen haben, aber es ist unwahrscheinlich, dass sie das tun werden. Stattdessen werden sie Rodenburg für alles verantwortlich machen. Lucas könnte seine Position verlieren, oder auch nicht. So oder so wird seine Karriere einen schweren Schlag erleiden.\nDas ist jedoch jetzt nicht unser Geschäft, Kapitän. Du hast deinen Teil der Arbeit gut gemacht. Deshalb habe ich eine weitere sehr heikle Angelegenheit für dich.";
			link.l1 = "Ich höre zu, Richard. Wer wird dieses Mal der nächste Feind der englischen Krone sein, der vernichtet wird?";
			link.l1.go = "Abigile_3";			
		break;
		
		case "Abigile_3":
			dialog.text = "Nein, ich möchte Sie diesmal bitten, sich um eine persönlichere und friedlichere Angelegenheit zu kümmern. Lassen Sie mich Ihnen eine kurze Geschichte erzählen, die übrigens Ihre 'Mirage' betrifft.";
			link.l1 = "Mach weiter.";
			link.l1.go = "Abigile_4";			
		break;
		
		case "Abigile_4":
			dialog.text = "Ich war auf einem Überfall, jagte das Geisterschiff einen Monat bevor wir uns trafen. Es war südlich von Martinique, nicht weit von der Länge 64 dg. 41'. Wir hörten einen Kampf in der Ferne, aber der Wind war zu schwach, also kamen wir nicht rechtzeitig hin. Eine englische Flöte wurde von einem Geisterschiff in der Nähe einer kleinen Insel versenkt, die nicht einmal auf der Karte eingetragen ist\nIch konnte den Piraten nicht fangen und beschloss, diese Insel zu besuchen, in der Hoffnung, Überlebende zu finden. Und ich fand sie. Ein paar jüdische Flüchtlinge, Vater und Tochter. Das Mädchen hieß Abigail und sie war schön! Ein lebendes Wunder... Ich nahm sie an Bord und brachte sie nach Curaçao, obwohl ihr Vater, Solomon, mir gegenüber nicht viel Sympathie zeigte\nSoweit ich verstanden habe, dachte er, dass ich der Pirat war, der ihr Schiff versenkt hat, der alte Mann weiß nicht viel über Schiffe und die Unterschiede zwischen ihnen. Während dieser kleinen Reise wurden Abigail und ich Freunde, oder um ganz ehrlich zu sein, verliebten wir uns ineinander. Ist das nicht eine Geschichte?\nUnd ich habe erst kürzlich herausgefunden, dass dieser Bastard Rodenburg schon eine Weile um meine Abigail wirbt, stell dir das vor! Ich hatte vor, sie hierher zu bringen, sobald ich die Angelegenheit bezüglich des verlorenen Geldes ihres Vaters kläre, er hat jeden einzelnen Taler, den er auf dieser Insel hatte, versteckt. Ich habe es nicht geschafft, seinen Standort zu finden. Wir können nicht länger warten\nDa meine Gesundheit es mir immer noch nicht erlaubt, selbst zu segeln, bitte ich dich, nach Willemstad zu gehen, Abigail zu finden und sie hierher zu bringen. Nenne meinen Namen und sie wird dir vertrauen.";
			link.l1 = "Sehe keine Probleme in dieser Angelegenheit. Ich bin bereit, jetzt in See zu stechen.";
			link.l1.go = "Abigile_5";			
		break;
		
		case "Abigile_5":
			PlaySound("Voice\English\hambit\Richard Flitwood-02.wav");
			dialog.text = "Ausgezeichnet! Ich bin froh, dass ich auf dich zählen kann, "+pchar.name+". Ihre Arbeit wird gut bezahlt, machen Sie sich darüber keine Sorgen.";
			link.l1 = "Ich werde dich nicht zu lange warten lassen. Bis bald, Richard!";
			link.l1.go = "Abigile_6";			
		break;
		
		case "Abigile_6":
			DialogExit();
			npchar.greeting = "fleetwood_2";
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload2", true);//закроем спальню Аби
			AddQuestRecord("Holl_Gambit", "2-16");
			pchar.questTemp.HWIC.Eng = "toAbigile";
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			sld.greeting = "barmen_1";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Fleetwood_LastTask":
			dialog.text = ""+pchar.name+", hast du dich wirklich entschieden, die Insel zu finden? Ich bin beeindruckt von deiner Großzügigkeit. Hast du sie gefunden?";
			link.l1 = "Ja, das habe ich. Leider beginnt hier die schlechte Nachricht. Ich bin kaum lebend aus diesem verdammten Ort entkommen... Ich zittere immer noch, wenn ich daran denke...";
			link.l1.go = "Fleetwood_LastTask_1";
		break;
		
		case "Fleetwood_LastTask_1":
			dialog.text = "Was ist dort passiert? Erzähle mir, mein Freund, halte mich nicht in Spannung!";
			link.l1 = "Ich kam auf die Insel und begab mich zur Grotte, wo Solomon wahrscheinlich seine Truhe versteckt hatte. Sie war wirklich da. Aber als ich sie berührte, schleuderte mich eine unbekannte Kraft hoch. Ich hörte eine Explosion und wurde zehn Fuß von der Truhe entfernt auf den Boden geworfen...";
			link.l1.go = "Fleetwood_LastTask_2";
		break;
		
		case "Fleetwood_LastTask_2":
			dialog.text = "Unglaublich!";
			link.l1 = "Ich habe es kaum überlebt - ich habe ein paar schmerzhafte Kratzer abbekommen. Als ich wieder zu Bewusstsein kam, summten erschreckende Geräusche in meinem Kopf und das schreckliche Wesen tauchte direkt aus dem Boden auf... oh, Gott, dieses Monster!";
			link.l1.go = "Fleetwood_LastTask_3";
		break;
		
		case "Fleetwood_LastTask_3":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Richard, ich bin nicht verrückt. Es ist wirklich passiert, obwohl ich selbst kaum daran glaube. Es war die völlig ausgetrocknete und bemalte Leiche eines Indianers mit einem Büschel Federn auf dem Kopf. Dieses Ungeheuer hat etwas gemurmelt, dann einen riesigen Indianerkeule gezogen und mich angegriffen!";
			link.l1.go = "Fleetwood_LastTask_4";
		break;
		
		case "Fleetwood_LastTask_4":
			dialog.text = "";
			link.l1 = "Guter Herr... Ich verstehe immer noch nicht, wie ich mit diesem Ding fertig werden konnte... Ich habe es so oft geschlagen, dass es ausgereicht hätte, ein Dutzend Männer zu töten und es stand immer noch... Nachdem ich meinen Atem wiedererlangt hatte, öffnete ich diese unglückliche Truhe... Es war kein Geld darin, aber stattdessen war etwas drin. Schau mal, ein sehr interessantes Objekt!";
			link.l1.go = "Fleetwood_LastTask_5";
		break;
		
		case "Fleetwood_LastTask_5":
			RemoveItems(PChar, "GastonHead", 1);
			dialog.text = "B-r-r... schrecklich..."+pchar.name+", warte... sicher, es ist er! Es ist der Kopf des Bastards, der versucht hat, mich zu töten, indem er mich mit Pfeffer geblendet hat!";
			link.l1 = "Sie kennen ihn? Sein Name ist Gaston, der Barkeeper von Bridgetown und ein Unterstützer von van Berg, dem Kapitän des Geisterschiffs. Ich habe ihn sofort erkannt, aber ich weiß nicht, wer ihn getötet hat und wie sein abgetrennter Kopf in der Truhe von Solomon auf der unbekannten Insel gelandet ist!";
			link.l1.go = "Fleetwood_LastTask_6";
		break;
		
		case "Fleetwood_LastTask_6":
			dialog.text = "Du hast recht, es ist eine wirklich gruselige und obskure Geschichte. Mystisch...";
			link.l1 = "Genau. Es hatte keinen Sinn, wegen des fehlenden Geldes zu Abigail zurückzukehren. Also bin ich hier, um Ihnen davon zu erzählen. Vielleicht wirst du, Richard, in diesem Durcheinander etwas verstehen...";
			link.l1.go = "Fleetwood_LastTask_7";
		break;
		
		case "Fleetwood_LastTask_7":
			dialog.text = "Ich? Ich verstehe hier genauso wenig wie du... Aber ich kann dir eins sicher sagen - ich habe ein schlechtes Gefühl dabei..."+pchar.name+", hör mir jetzt zu. Geh und überprüfe Bridgetown, um sicher zu sein, dass... Gaston für immer weg ist. Dann bitte ich dich, in 20 Tagen zur Blanca Lagune von Curacao zu kommen. Charlie Knippel wird dort auf dich warten. Ich werde Geld für Abigails Vater sammeln. Ich werde es Charlie geben, und du wirst es zu Solomon bringen und Abigail nach Antigua liefern. Dieses Mal wird es keine Hindernisse geben, das musst du verstehen. Geh, mein Freund!";
			link.l1 = "Gut, Richard. Ich werde sofort die Segel setzen.";
			link.l1.go = "Fleetwood_LastTask_8";
		break;
		
		case "Fleetwood_LastTask_8":
			DialogExit();
			pchar.questTemp.HWIC.Eng = "toBarbados";
			AddQuestRecord("Holl_Gambit", "2-21");
			SetFunctionTimerCondition("HWICEng_toBarbadosOver", 0, 0, 20, false);//чтобы не тянули
			AddSimpleRumourCity("Oh, captain, I have heard that Richard Fleetwood really admires you. Trust me, his praise costs a lot. You must be a very important person...", "SentJons", 20, 3, "");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
		break;
		
//---------------------------------------------против всех-----------------------------------------------
		
		case "InTerksShore":
			DelLandQuestMark(npchar);
			pchar.quest.Fleetwood_ShoreOver.over = "yes";//снять таймер
			dialog.text = "Ich nehme an, dass du der Bastard bist, der meine Abigail entführt hat. Charlie ist nicht zu mir zurückgekehrt, also musst auch du der Schuldige sein.";
			link.l1 = "Sie haben recht, Herr Fleetwood. Ich bin es. Charlie hat mir geholfen, mich dank Ihres Briefes an sie in das Vertrauen von Abigail einzuschleichen. Aber direkt zum Geschäft... Haben Sie das Geld mitgebracht?";
			link.l1.go = "InTerksShore_1";
		break;
		
		case "InTerksShore_1":
			dialog.text = "Ich habe. Aber ich möchte zuerst Abigail sehen. Ich muss sicher sein, dass sie lebt und unberührt ist, da ich nicht das Wort eines Bastards vertrauen werde.";
			link.l1 = "Glauben Sie nicht, Herr, dass Sie nicht in der Lage sind, Ihre Bedingungen zu diktieren?";
			link.l1.go = "InTerksShore_2";
			// belamour legendary edition -->
			link.l2 = "Ich will dieses Spiel nicht mehr spielen. Abi bleibt bei mir, und du bist an diesem Strand! Feuer!";
			link.l2.go = "InTerksShore_2a";
		break;

		case "InTerksShore_2a"://массовая драка на необитаемом острове
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;

		case "InTerksShore_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "Ich verstehe das, aber ich bin auch kein Narr. Kein Geldgespräch, bis ich Abigail sehe. Na und? Ich warte.";
			link.l1 = "Gut. Jetzt ist es an der Zeit, meine Karten auf den Tisch zu legen, Kapitän Fleetwood. Ich habe unser Treffen hier nicht wegen des Geldes organisiert. Sicher, ich würde es gerne nehmen, aber ich brauche dich zuerst.";
			link.l1.go = "InTerksShore_3";
		break;
		
		case "InTerksShore_3":
			dialog.text = "Ich? Das wird ja immer interessanter... Ich glaube, ich fange an zu verstehen, was hier wirklich vor sich geht. Sag mal, lebt Abigail? Lebt sie oder hast du sie ermordet, du Bastard?";
			link.l1 = "Ich nehme an, ich werde dich über ihr Schicksal im Unklaren lassen. Nur eines sollst du wissen - sie ist nicht hier. Sie hat ihre Rolle gut gespielt, du bist jetzt in meinen Händen. Liebe ist so eine wunderbare Sache... Wie sonst könnte ich einen Fuchs aus seinem Bau auf offenes Gelände locken? Ha-ha-ha!";
			link.l1.go = "InTerksShore_4";
		break;
		
		case "InTerksShore_4":
			dialog.text = "Mach dich nicht so schnell froh, Schurke. Ich habe eine feine Begrüßung für dich auf dieser Insel organisiert und es ist ungewiss, wer in wessen Händen ist! Also bereite dich vor, du hast mir viel zu erzählen - über Abigail, über Charlie, du wirst dafür bezahlen, dass du ihnen wehgetan hast!";
			link.l1 = "Ich zittere vor Angst schon! Zeit unser Gespräch zu beenden, Herr. Bereite dich auf die Hölle vor, denn im Himmel ist kein Platz für dich.";
			link.l1.go = "InTerksShore_5";
		break;
		
		case "InTerksShore_5"://массовая драка на необитаемом острове
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
