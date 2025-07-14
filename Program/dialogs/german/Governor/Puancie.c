// Филипп де Пуанси - генерал-губернатор французских колоний
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyFox"))
			{
				dialog.text = "Grüße, "+pchar.name+".";
				link.l1 = "Es könnte ein Missverständnis vorliegen, Eure Exzellenz. Ich kam, um den erfolgreichen Abschluss Ihrer Mission zu melden, aber ich sehe, dass Sie nicht in bester Laune sind.";
				link.l1.go = "PZ_PoincyAngry1";
				DeleteAttribute(pchar, "questTemp.Terrapin");
				DeleteAttribute(pchar, "questTemp.Terrapin_KathyFox");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "done")
			{
				dialog.text = "Freut mich, dich zu sehen, "+pchar.name+". Ich bin über Ihre Leistungen informiert und vor allem, Sie haben Ihre Mission erfolgreich abgeschlossen! Sie haben sich von Ihrer besten Seite gezeigt und ich bin froh, dass ich mich in Ihnen nicht getäuscht habe.";
				link.l1 = "Kann ich jetzt von Ihnen einen schriftlichen Befehl zur Freilassung meines Bruders erhalten?";
				link.l1.go = "serve";
				AddCharacterExpToSkill(pchar, "Sneak", 500);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga") && CheckAttribute(pchar, "questTemp.Sharlie.LevasserDied"))
			{
				dialog.text = "Freut mich, Sie zu sehen, "+pchar.name+". Ich habe von Ihren Taten gehört und vor allem ist Ihre Mission abgeschlossen! Obwohl, ich muss sagen, ich habe eine intelligentere Idee als einen Frontalangriff erwartet. Schade um die toten französischen Soldaten.\nAber Krieg ist Krieg, es gibt immer Opfer. Sie haben Ihre Pflicht erfüllt, und ich bin froh, dass ich mit Ihnen richtig lag.";
				link.l1 = "Kann ich jetzt von Ihnen einen schriftlichen Befehl zur Freilassung meines Bruders erhalten?";
				link.l1.go = "serve";
				DeleteAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga");
				DeleteAttribute(pchar, "questTemp.Sharlie.LevasserDied");
				break;
			}
			// Jason НСО 
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && GetCharacterIndex("Noel") == -1 && pchar.questTemp.Patria != "epizode_12_barondie" && pchar.questTemp.Patria != "epizode_12_baronfail" && pchar.questTemp.Patria != "epizode_12_baronkilled" && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "Gut Sie zu sehen, Charles. Zuerst erlauben Sie mir, Ihnen zu gratulieren, dass Sie die komplexe Aufgabe, die Kolonie Saint-Pierre vor den spanischen Eindringlingen zu schützen, erfolgreich abgeschlossen haben. Hervorragende Arbeit, mein Freund!";
					link.l1 = "Danke, Chevalier.";
					link.l1.go = "patria";
					Patria_SetInspector();
				}
				else
				{
					dialog.text = "Gut Sie zu sehen, Charles. Zuerst erlauben Sie mir, Ihnen zu gratulieren, dass Sie die komplexe Aufgabe erfolgreich abgeschlossen haben, die Kolonie Saint-Pierre vor den spanischen Eindringlingen zu schützen. Brillante Arbeit, mein Freund! Ich biete Ihnen eine weitere Möglichkeit zur Zusammenarbeit mit der Marine an. Frankreich benötigt dringend Offiziere wie Sie. Ich hoffe, diesmal sind Sie vernünftiger ... Nehmen Sie das Patent, Kapitän Charles de Maure!";
					link.l1 = "Danke, Chevalier. Ich freue mich, dem Land zu helfen und bin begierig darauf, es weiter zu dienen!";
					link.l1.go = "patria";
					if (!CheckCharacterItem(pchar, "suit1")) GiveItem2Character(pchar, "suit1");
					GiveItem2Character(pchar, "patent_fra");
					EquipCharacterbyItem(pchar, "patent_fra");
					Items[sti(pchar.EquipedPatentId)].TitulCur = 2; 
					Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
					ChangeCharacterNationReputation(pchar, FRANCE, 100);
					Patria_SetInspector();
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria != "fail" && pchar.questTemp.Patria != "end")
			{
				if (!CheckCharacterItem(pchar, "patent_fra"))
				{
					dialog.text = "Charles, du enttäuschst mich. Aufgrund deiner unklugen Handlungen hast du dein Patent und den Rang in der königlichen Marine verloren. Es gibt keinen Raum für weitere Zusammenarbeit. Entlassen.";
					link.l1 = "Hmm...";
					link.l1.go = "patria_patentfail";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_1_return")
				{
					dialog.text = "Freut mich, dich zu sehen, Charles. Bericht!";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "Die Arbeit ist erledigt, das Lösegeld aus der Kolonie San Jose ist eingetroffen. Aber es gibt schlechte Nachrichten: Im Kampf mit dem Fort 'Eclatant' wurde versenkt. Ich warnte den Kapitän, aufzupassen, aber er hörte nicht auf mich, und...";
						link.l1.go = "patria_8_1";
					}
					else
					{
						link.l1 = "Die Arbeit ist erledigt, das Lösegeld aus der Kolonie San Jose ist eingegangen.";
						link.l1.go = "patria_8";
					}
					break;
				}
				// belamour legendary edition фикс проверки мундира с мушкетом
				if(!IsUniformEquip())
				{
					dialog.text = "Herr, betreten Sie ab diesem Tag nur in angemessener Uniform meine Hallen!";
					link.l1 = "...";
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_2_return" && IsUniformEquip())
				{
					dialog.text = "Baron, Kapitän! Froh, Sie zu sehen!";
					link.l1 = "Die Aufgabe ist abgeschlossen, Chevalier.";
					link.l1.go = "patria_14";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_3_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Kapitän. Welche Neuigkeiten bringst du?";
					if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail"))
					{
						link.l1 = "Die Spanier planten einen Angriff auf Port-au-Prince. Am westlichen Ende von Hispaniola fanden wir eine mächtige feindliche Staffel. Sie wurde vollständig zerstört. Allerdings wurde die 'Eclatant' versenkt.";
						link.l1.go = "patria_26_1";
					}
					else
					{
						link.l1 = "Die Spanier planten einen Angriff auf Port-au-Prince. Am westlichen Ende von Hispaniola fanden wir eine mächtige feindliche Staffel. Sie wurde vollständig zerstört.";
						link.l1.go = "patria_26";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_4_return" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Charles. Wie geht es Mynheer Stuyvesant?";
					link.l1 = "Alles ist in Ordnung, Chevalier. Die Lieferung war erfolgreich, hier ist die Antwort auf Ihren Brief.";
					link.l1.go = "patria_31";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_5_return" && IsUniformEquip())
				{
					dialog.text = "Charles, Baron... Du bist schon zurück?";
					link.l1 = "...";
					link.l1.go = "patria_36";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_6_return" && IsUniformEquip())
				{
					dialog.text = "Ich mag deine Stirnrunzeln nicht, Charles. Was hat Stuyvesant gesagt, berichte!";
					if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win") link.l1 = "Wörtlich sagte er: 'Sagen Sie Chevalier, dass er nicht mehr für Sint-Maarten verantwortlich ist. Genug von ihm. Und was die Inspektion vom Heimatstaat betrifft - er soll sich etwas einfallen lassen, Für de Poincy war es nie schwierig, alles auf den Kopf zu stellen'. Nachdem er diese Nachricht verkündet hatte, warf mich der Mynheer aus der Residenz. Das war das Ende unserer Verhandlungen.";
					else link.l1 = "Nun, das ist was er gesagt hat: 'Dein Lehnsherr war in letzter Zeit viel zu gierig auf Sint-Maarten, also ist es an der Zeit, seinen unersättlichen Hunger zu zügeln.' Danach versuchte er, mich festzunehmen. Ich musste meinen Weg zum Schiff mit einem Schwert freikämpfen. So viel zur niederländischen Diplomatie.";
					link.l1.go = "patria_43";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_go" && IsUniformEquip())
				{
					dialog.text = "Kapitän, wir haben auf Sie gewartet. Ich habe dem Baron den aktuellen Stand der Dinge erklärt, und er unterstützte meine Entscheidung voll und ganz. Die Holländer werden für ihre Arroganz büßen.";
					link.l1 = "Dann ist es Krieg?";
					link.l1.go = "patria_51";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_7_continue" && IsUniformEquip() && pchar.location.from_sea == "Charles_town") // add-7
				{
					Patria_HunterShipChecker();
					if (CheckAttribute(pchar, "questTemp.Patria.Hunter.GiveShip"))
					{
						dialog.text = "So, mein Freund, ich sehe, du hast das ostindische Schiff mit den Waren erobert. Ausgezeichnet!";
						link.l1 = "Ich übergebe Ihnen ein Schiff, erteilen Sie Befehle an die Hafenbeamten, Chevalier.";
						link.l1.go = "patria_55";
					}
					else
					{
						dialog.text = "Haben Sie Fragen, Charles?";
						link.l1 = "Nicht im Moment, Monsieur. Ich gehe dann mal...";
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8" && IsUniformEquip())
				{
					dialog.text = "Endlich sind Sie angekommen, Kapitän! Es gibt einen Notfall auf Saint Christopher!";
					link.l1 = "Eine feindliche Staffel?";
					link.l1.go = "patria_59";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_wait" && IsUniformEquip() && GetCompanionQuantity(pchar) < 5)
				{
					dialog.text = "Bist du bereit, unseren Kurierlugger aufzunehmen?";
					link.l1 = "Ich bin es.";
					link.l1.go = "patria_64";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_8_return")
				{
					dialog.text = "Kapitän de Maure, Sir Doily! Froh, Sie zu sehen! Die ganze Stadt hat zugeschaut, wie Sie den spanisch-niederländischen Schurken, die unsere Kolonie begehrten, eine Lektion erteilt haben!";
					link.l1 = "Es war meine Pflicht, Chevalier.";
					link.l1.go = "patria_66";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_start" && IsUniformEquip())
				{
					dialog.text = TimeGreeting()+", Charles. Lassen wir beginnen, sollen wir nicht?";
					link.l1 = "Natürlich, Chevalier. Deshalb bin ich hier.";
					link.l1.go = "patria_69";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_9_return" && IsUniformEquip())
				{
					dialog.text = "Es freut mich, in meinem Büro den Vizeadmiral der königlichen Marine Frankreichs willkommen zu heißen! Ja, mein Freund, Sie haben sich nicht geirrt: Ich habe persönlich den Befehl zu Ihrer Ernennung unterschrieben. Formell muss es noch in Frankreich genehmigt werden, aber Sie müssen nicht einmal daran zweifeln, dass es passieren wird. Herzlichen Glückwunsch!";
					link.l1 = "Ich diene meinem Land!";
					link.l1.go = "patria_76";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_10_return" && IsUniformEquip())
				{
					if (GetQuestPastDayParam("questTemp.Patria.Curacao.Date") < 30) sTemp = "will be ready soon and"; // в зависимости от времени сколько добирался
					else sTemp = "is ready and";
					dialog.text = "Haben Sie Erfolg in Ihren Bemühungen gehabt? War Oberst Doily zufrieden?";
					link.l1 = "Alles lief perfekt, Chevalier. Stuyvesants Karawane wurde gefangen genommen, alle Sklaven nach Jamaika gebracht, das Geschwader des Obersten "+sTemp+" auf dem Weg nach Curacao.";
					link.l1.go = "patria_81";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_11_return" && IsUniformEquip())
				{
					dialog.text = "Ehre den Siegern! Glückwunsch, Glückwunsch, mein Freund! Du hörst nie auf zu verblüffen.";
					link.l1 = "Danke Ihnen, Chevalier. Stuyvestant wurde bestraft und ist bereit, Entschädigungen zu zahlen, der Frieden ist wiederhergestellt, Saint Martin gehört jetzt ausschließlich Frankreich.";
					link.l1.go = "patria_85";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_continue")
				{
					dialog.text = "Also, mein Freund, ich freue mich, dich wieder zu sehen. Hast du dich gut erholt?";
					link.l1 = "Ja, Chevalier. Es war eine dringend benötigte Pause ... Sie haben von einer heiklen Angelegenheit gesprochen?";
					link.l1.go = "patria_88";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronalive")
				{
					dialog.text = "Mein Freund, du musst ein Zauberer sein! Du hast es geschafft, ein Kunststück zu vollbringen! Unser Baron möchte hier keine Handelsgesellschaft mehr gründen.";
					link.l1 = "Ich glaube, sein einziger Wunsch jetzt ist, zurück in Paris zu sein.";
					link.l1.go = "patria_103";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_barondie")
				{
					dialog.text = "Charles, hast du von dem Baron gehört? Er wurde von Piraten genommen...";
					link.l1 = "Ja, Chevalier. Leider ist der Baron tot. Das weiß ich sicher.";
					link.l1.go = "patria_112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronfail")
				{
					dialog.text = "Charles, wie sieht dein Fortschritt aus? Mir wurde gesagt, dass der Baron dein Schiff betreten hat...";
					link.l1 = "Ja, Chevalier. Er war an Bord, ich habe mich um ihn gekümmert, aber... er starb an Fieber.";
					link.l1.go = "patria_x112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronkilled")
				{
					dialog.text = "Charles, wie sieht es mit deinem Fortschritt aus? Mir wurde gesagt, dass der Baron dein Schiff betreten hat...";
					link.l1 = "Ja, Chevalier. Er war an Bord, ich habe an ihm gearbeitet, aber... er starb in einer Schlacht.";
					link.l1.go = "patria_y112";
					break;
				}
				if (pchar.questTemp.Patria == "epizode_12_baronwin")
				{
					dialog.text = "Mein Freund, du musst ein Zauberer sein! Du hast es geschafft, eine Heldentat zu vollbringen! Unser Baron möchte hier keine Handelsgesellschaft mehr gründen.";
					link.l1 = "Er ist wahrscheinlich gerade auf dem Weg nach Paris.";
					link.l1.go = "patria_117";
					break;
				}
				dialog.text = "Haben Sie irgendwelche Fragen, Charles?";
				link.l1 = "Nicht in diesem Moment, Monsieur. Ich werde dann gehen...";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Was wollen Sie? Monsieur?";
			link.l1 = "Nichts Ernstes, nur ein Höflichkeitsbesuch. Ich gehe jetzt...";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// в тюрьме при старте игры
		case "Puancie_Jail":
			dialog.text = "Guten Tag, Charles. Lassen Sie mich mich vorstellen: Ich bin Philippe de Poincy und ich...";
			link.l1 = "Warum zum Teufel habt ihr mich ins Gefängnis geworfen? Das ist unangebracht! Ich bin ein französischer Adeliger und...";
			link.l1.go = "Puancie_Jail_1";			
			// belamour legendary edition -->
			link.l2 = "Gut... Nachmittag? Guter Witz, Herr. Wie wissen Sie, wer ich bin?";
			link.l2.go = "Puancie_Jail_1a";	
		break;
		
		case "Puancie_Jail_1a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			dialog.text = "Junger Mann, ich bitte Sie, mich nicht zu unterbrechen! Sie sprechen mit dem Generalgouverneur der französischen Kolonien des Karibischen Archipels! Ich werde Ihren frechen Ton nur verzeihen, weil Sie nicht wissen konnten, wer vor Ihnen stand. Aber ich würde Ihnen empfehlen, sich mehr zurückzuhalten.";
			link.l1 = "Hmm... Es tut mir leid, Eure Gnaden.";
			link.l1.go = "Puancie_Jail_2";
		break;
		
		case "Puancie_Jail_1":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "FencingL", 10);
			AddCharacterExpToSkill(pchar, "FencingS", 10);
			AddCharacterExpToSkill(pchar, "FencingH", 10);
			AddCharacterExpToSkill(pchar, "Pistol", 10);
			// <-- legendary edition
			dialog.text = "Hören Sie mir zu, junger Mann, und unterbrechen Sie mich nicht! Sie sprechen mit dem Generalgouverneur der französischen Kolonien im karibischen Archipel! Ich werde Ihren Ton nur wegen Ihrer Unwissenheit darüber, mit wem Sie sprechen, verzeihen. Aber ich würde Ihnen empfehlen, in der Zukunft mehr zurückhaltend zu sein.";
			link.l1 = "Hm... verzeihen Sie mir, Eure Exzellenz.";
			link.l1.go = "Puancie_Jail_2";			
		break;
		
		case "Puancie_Jail_2":
			dialog.text = "Besser. Nun, bezüglich Ihrer vorherigen Frage - Sie wurden - fälschlicherweise - für einen spanischen Spion gehalten und unter Arrest gestellt, bis Ihr Status geklärt ist. Verdammte Kastilier sind in letzter Zeit aktiver geworden, daher habe ich angeordnet, alle verdächtigen Personen festzunehmen.\nAber wir wissen jetzt, wer Sie sind - Sie sind wirklich Charles de Maure, ein Bruder von Michel de Monper, und ich bin persönlich hierher gekommen, um Sie freizulassen. Und Sie schreien mich an wie ein kleiner Junge!";
			link.l1 = "Verzeihen Sie mir nochmals, Eure Exzellenz. Bin ich jetzt frei?";
			link.l1.go = "Puancie_Jail_3";			
		break;
		
		case "Puancie_Jail_3":
			dialog.text = "Ja, das sind Sie. Aber ich möchte mit Ihnen unter vier Augen sprechen, bevor ein Sergeant Ihre Zelle öffnet. Wissen Sie, dass Ihr Bruder, einer der würdigsten Krieger des Malteserordens, verhaftet und unter Bewachung gestellt wurde?";
			link.l1 = "Ich wusste nur, dass mein Bruder in Schwierigkeiten steckt und Hilfe braucht. Deshalb bin ich von Paris hierher gekommen.";
			link.l1.go = "Puancie_Jail_4";			
		break;
		
		case "Puancie_Jail_4":
			dialog.text = "Es freut mich, das zu hören. Sie sollten wissen, dass Monsieur de Monper in ernsten Schwierigkeiten steckt. Ich habe allen Grund, ihn des Amtsmissbrauchs, der Unterschlagung und des Meineids zu verdächtigen. Aber Sie können ihm helfen.";
			link.l1 = "Herr, könnten Sie mir mehr erzählen? Ich verstehe es nicht, Michel war der Stolz des Ordens und...";
			link.l1.go = "Puancie_Jail_5";			
		break;
		
		case "Puancie_Jail_5":
			dialog.text = "Ich dachte auch so. Wir alle taten es! Aber seine jüngsten Handlungen haben uns... unsicher über seine Loyalität zum Orden gemacht, also wurde er verhaftet. Michel wird Ihnen die Details selbst erzählen. Er wird erklären, wie Sie ihm helfen könnten, sich um die Vorwürfe zu kümmern und eine Schande zu vermeiden.";
			link.l1 = "Wo ist mein Bruder jetzt? Sie haben mir gesagt, dass er im Gefängnis ist, aber ich habe ihn nicht gesehen...";
			link.l1.go = "Puancie_Jail_6";			
		break;
		
		case "Puancie_Jail_6":
			dialog.text = "Habe ich gesagt eingesperrt, junger Mann? Hörst du überhaupt zu?! Ich sagte, er ist unter Arrest! Es ist nicht das Gleiche. Michel de Monper wird in der unterirdischen Basis von Saint Pierre, die Eigentum des Malteserordens ist, unter Arrest gehalten. \nIch erlaube Ihnen, die Basis ohne Einschränkungen zu besuchen und so oft mit Ihrem Bruder zu sprechen, wie Sie es für nötig halten. Die Offiziere und Soldaten des Ordens sind über meine Anweisungen informiert und sie werden Sie nicht stoppen.";
			link.l1 = "Wo ist dieser Untergrundstützpunkt?";
			link.l1.go = "Puancie_Jail_7";			
		break;
		
		case "Puancie_Jail_7":
			dialog.text = "Hier ist es, natürlich in Saint Pierre. Suchen Sie das örtliche Gefängnis und betreten Sie die Tür mit den Symbolen des Ordens. Gehen Sie hinunter zur Kaserne im zweiten Untergeschoss. Monsieur Monper wird dort sein. Aber keine Sorge: Beim Verlassen des Gefängnisses werden Sie getroffen und zu Ihrem Bruder eskortiert - ich habe alles arrangiert... Das ist alles. Ich hoffe, wir sehen uns wieder, Charles. Sergeant!";
			link.l1 = "Bitte warten Sie, Euer Exzellenz! Und was ist mit meinen... Habseligkeiten? Mein Schwert und der Rest?";
			link.l1.go = "Puancie_Jail_8";			
		break;
		
		case "Puancie_Jail_8":
			dialog.text = "Ihre Besitztümer wurden zur Begleichung der Schulden Ihres Bruders beschlagnahmt. Lebewohl, Monsieur de Maure.";
			link.l1 = "Was zum Teufel...";
			link.l1.go = "Puancie_Jail_9";			
		break;
		
		case "Puancie_Jail_9":
			DialogExit();
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Sharlie_GoFromPrison", 3.5);
			NextDiag.CurrentNode = "First time";
			locCameraFromToPos(-11.09, 0.65, 3.05, true, -12.59, 0.09, -4.66);
		break;
		
		// возвращаем деньги
		case "saga":
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", false);
			dialog.text = "Aha, Charles de Maure selbst! Schön, Sie zu sehen. Ich nehme an, Sie sind hier, um mit mir über das Schicksal Ihres Bruders zu sprechen?";
			link.l1 = "Ich bin bereit, das zurückzuzahlen, was Michel de Monper dem Orden und Ihnen persönlich schuldet.";
			if (sti(pchar.money) >= 1000000) link.l1.go = "saga_1";
			else link.l1.go = "saga_exit";			
		break;
		
		case "saga_exit":
			dialog.text = "Hm.. Aber wo ist das Geld? Du hast einen seltsamen Sinn für Humor, junger Mann und ich verstehe ihn nicht.";
			link.l1 = "Verzeihen Sie mir, Chevalier. Ich habe mein Geld in meinem Schrank auf dem Schiff vergessen. Ich komme bald zurück.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_repeat";	
		break;
		
		case "saga_repeat":
			dialog.text = "Haben Sie das Geld gebracht, Charles?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Sicher! Ich hoffe, dass diese Summe alle Ihre Kosten vollständig decken wird.";
				link.l1.go = "saga_1";
			}
			else
			{
				link.l1 = "Noch nicht...";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_repeat";
			}		
		break;
		
		case "saga_1":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Charles");
			AddMoneyToCharacter(pchar, -1000000);
			dialog.text = "Hervorragend! Ich nehme sie dir ab. Du hast dich von deiner besten Seite gezeigt, Charles!";
			link.l1 = "Wann bekomme ich den Befehl zur Freilassung von Michel de Monper?";
			link.l1.go = "saga_2";			
		break;
		
		case "saga_2":
			dialog.text = "Hast du es eilig, junger Mann. Ich kann nur respektieren, dass du Schulden begleichst und deine Familie schützt, indem du dein eigenes Leben in Gefahr bringst. Es ist eine seltene Adelheit heutzutage... Aber Geld ist nicht der Hauptteil dieser traurigen Geschichte. Dein Bruder hat eine so große Summe erhalten, um eine sehr heikle Mission zu erfüllen.\nMichel de Monper, als treuer Katholik, hat auf dem Buch geschworen, dass er einen Weg finden wird, einen unverschämten Ketzer zu bestrafen und die von ihm verletzte Gerechtigkeit zum Ruhm des Ordens und der Heiligen Kirche wiederherzustellen...";
			link.l1 = "Aber er wird sein Wort nicht unter Arrest halten können! Wenn Sie ihn freilassen, werden wir beide die Mission viel schneller abschließen können, als wenn ich es ganz alleine tun würde.";
			link.l1.go = "saga_3";			
		break;
		
		case "saga_3":
			dialog.text = "Sehen Sie, mein Freund, Ihr Bruder hat mir einen starken Grund gegeben, seiner Anständigkeit nicht zu vertrauen. Es gibt keine Garantien, dass er nicht fliehen und seinen Eid brechen wird. Also, wenn Sie alle Vorwürfe von ihm nehmen wollen - leisten Sie den Eid selbst. Monsieur de Monper wird Ihnen die Details erzählen.";
			link.l1 = "Hm... Das habe ich nicht erwartet. Aber du lässt mir keine Wahl. Ich werde meine endgültige Entscheidung treffen, nachdem ich mit meinem Bruder gesprochen habe.";
			link.l1.go = "saga_4";			
		break;
		
		case "saga_4":
			dialog.text = "Ich beginne dich wirklich zu mögen, Charles. Vielleicht werden wir eines Tages Freunde. Wie auch immer, dies ist meine letzte Bedingung um deinen Bruder freizulassen. Ich gebe dir mein Wort, dass der Ruf deiner Familie keinen Schaden nehmen wird, wenn du tust, was dein Bruder nicht getan hat. Und in der Zukunft kannst du auf meine Freundschaft zählen.";
			link.l1 = "Ich habe Sie vollkommen verstanden. Lebewohl!";
			link.l1.go = "saga_5";			
		break;
		
		case "saga_5":
			DialogExit();
			pchar.questTemp.Saga = "mishelle";//Сага - старт
			AddQuestRecord("Sharlie", "21");
			NextDiag.CurrentNode = "First time";
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
		break;
		
		case "serve":
			dialog.text = "Mach dir keine Sorgen, "+pchar.name+", Ich werde mein Wort halten. Ihr Bruder wird freigelassen und alle Anschuldigungen gegen ihn werden fallen gelassen. Der Ruf Ihrer Familie ist nun außer Gefahr. Ich würde sagen, das ist alles dank Ihrer Verdienste und nur Ihrer. Ihr Vater kann stolz darauf sein, einen solchen Sohn großgezogen zu haben.";
			link.l1 = "Danke für die freundlichen Worte, Chevalier. Darf ich also sofort nach Martinique aufbrechen?";
			link.l1.go = "serve_1";	
			Island_SetReloadEnableGlobal("Tortuga", true);
			CloseQuestHeader("Terrapin");
			SetFunctionTimerCondition("Terrapin_SetFontene", 0, 0, 5, false); // таймер
		break;
		
		case "serve_1":
			dialog.text = "Warten Sie einen Moment, mein Freund. Ich hoffe, dass ich Sie meinen Freund nennen kann, nicht wahr? Ich möchte Ihnen persönlich meinen Dank aussprechen. Seit Ihrer Ankunft hier verfolge ich Ihren Fortschritt und ich weiß über die meisten Ihrer Taten Bescheid. Sie haben sich in der Karibik einen großen Namen gemacht und sind ohne Zweifel auch in bestimmten Gesellschaftsschichten bekannt und respektiert. Frankreich braucht Menschen wie Sie\nKapitän "+GetFullName(pchar)+"! Durch die Macht, die mir von Seiner Majestät, dem König von Frankreich, verliehen wurde, habe ich die Ehre, Ihnen ein Patent des Kapitäns der königlichen Marine anzubieten und das Schiff der französischen Marine, die leichte Fregatte 'Gryffondor', unter Ihr Kommando zu stellen!\nDank Ihnen wird ihr ehemaliger Kapitän de Fontenot Gouverneur von Tortuga und die beste leichte Fregatte in der Karibik braucht einen Kapitän. Nehmen Sie das Angebot an?";
			link.l1 = "Interessant. Was bekomme ich dafür im Gegenzug?";
			link.l1.go = "serve_2";		
		break;
		
		case "serve_2":
			dialog.text = "Nur ein bisschen. Ein Zehntel Ihrer Fangquote und manchmal heikle Missionen erfüllen. Ich warte auf Ihre Entscheidung.";
			link.l1 = "Niemand würde ein solches Angebot ablehnen, Eure Exzellenz! Es ist eine Ehre, meiner Nation zu dienen!";
			link.l1.go = "serve_3";
			link.l2 = "Verzeihen Sie meine Unbescheidenheit, aber ich muss Ihr Angebot vorerst ablehnen. Familiäre Angelegenheiten könnten eine sofortige Rückkehr in die Heimat erfordern.";
			link.l2.go = "serve_no";
			InterfaceStates.Buttons.Save.enable = true;
		break;
		
		case "serve_no":
			ChangeCharacterComplexReputation(pchar, "fame", 7);
			dialog.text = "Schade. Ich hoffte, dass Sie zustimmen werden... Aber trotzdem bin ich gezwungen, Sie um einen weiteren Gefallen zu bitten, eigentlich liegt das auch in Ihrem Interesse. Martinique wird angegriffen. Es wird heftig im Hafen und in der Stadt selbst gekämpft.\nLeider habe ich niemanden, den ich dorthin schicken könnte, um der Garnison zu helfen, außer Ihnen. Ich bitte Sie als einen Patrioten Ihres Vaterlandes, den Angriff mit allen notwendigen Mitteln zurückzuschlagen. Ich hoffe, Sie haben genügend Ressourcen dafür.\nAußerdem ist Ihr Bruder immer noch dort, Sie können sein Leben retten.";
			link.l1 = "Mein Bruder ist in Gefahr? Ich bin auf dem Weg!";
			link.l1.go = "serve_exit";			
		break;
		
		case "serve_3":
			dialog.text = "So ehrenvolle Worte! Worte eines wahren Soldaten und loyalen Sohnes des Vaterlandes! Herzlichen Glückwunsch, monsieur "+GetFullName(pchar)+". Ihnen wird der Rang eines Kommandeurs der Seestreitkräfte Frankreichs verliehen. Nehmen Sie diese Uniform von mir an. Tragen Sie sie stolz und seien Sie ihrer würdig!";
			link.l1 = "Ich diene meiner Nation!";
			link.l1.go = "serve_4";	
			locCameraFromToPos(-2.63, 2.20, -4.96, true, 2.64, 0.22, -4.96);
			npchar.greeting = "puancie_1";			
		break;
		
		case "serve_4":
			dialog.text = "Die leichte Fregatte 'Gryffondor' steht nun unter Ihrem Kommando. Von diesem Moment an gehört dieses hervorragende Schiff Ihnen. Nutzen Sie seine hohen Qualitäten für die Ehre Seiner Majestät und zur Stärkung des französischen Einflusses auf dem karibischen Archipel!";
			link.l1 = "Sofort!";
			link.l1.go = "serve_5";
			LAi_Fade("SharlePutsSuit", "");
		break;
		
		case "serve_5":
			if (GetCompanionQuantity(pchar) > 4)
			{
				dialog.text = "Aber Ihre Staffel ist bereits zu groß, also kommen Sie zurück, um die 'Gryffondor' zu holen, wenn Sie ein Schiff loswerden.";
				link.l1 = "Gut. Ich werde das tun.";
				link.l1.go = "serve_wait";		
			}
			else
			{
				dialog.text = "Zusammen mit dem Schiff erhalten Sie auch den amtierenden Kapitän und die Besatzung. Wenn Sie möchten, können Sie ihn unter Ihrem Kommando lassen oder ihn von einem Schiff absetzen und wir finden eine andere Position für ihn.";
				link.l1 = "Verstanden!";
				link.l1.go = "serve_6";
			}
		break;
		
		case "serve_6":
			dialog.text = "Aber ich habe schlechte Nachrichten für dich, Kapitän. Mir wurde gerade mitgeteilt, dass Martinique angegriffen wird. Es gibt heftige Kämpfe im Hafen und in der Stadt selbst.\nLeider habe ich niemanden, den ich dorthin schicken könnte, um der Garnison zu helfen, außer dir. Hier ist deine erste Mission:\n Beschütze Saint Pierre! Außerdem ist dein Bruder immer noch dort, du kannst sein Leben retten.";
			link.l1 = "Mein Bruder ist in Gefahr? Ich bin unterwegs!";
			link.l1.go = "serve_7";
		break;
		
		case "serve_7":
			DialogExit();
			locCameraTarget(PChar);
			locCameraFollow();
			CreateGriffondor();
			sld = characterFromId("GriffOfficer");
			SetCharacterRemovable(sld, true);
			SetCompanionIndex(pchar, -1, sti(sld.index));
			sld.loyality = MAX_LOYALITY;
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "24");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 2000);
			AddCharacterExpToSkill(pchar, "Fortune", 500);
			pchar.questTemp.GoldenGirl_Block = true;	// Запрещаем квест Дороже Золота
		break;
		
		case "serve_wait":
			DialogExit();
			NextDiag.CurrentNode = "serve_shipcheck";
		break;
		
		case "serve_shipcheck":
			dialog.text = "Bist du bereit, das Kommando über 'Gryffondor' zu übernehmen?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Noch nicht, ich positioniere meine Schiffe im Geschwader neu...";
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = "Ich bin es.";
				link.l1.go = "serve_5a";
			}
			NextDiag.TempNode = "serve_wait";
		break;
		
		case "serve_5a":
			dialog.text = "Prächtig! Zusammen mit dem Schiff erhalten Sie auch den kommissarischen Kapitän und die Mannschaft. Wenn Sie wollen, können Sie ihn unter Ihrem Kommando lassen oder ihn von einem Schiff abziehen und wir finden eine andere Position für ihn.";
			link.l1 = "Habs verstanden!";
			link.l1.go = "serve_6";
		break;
		
		case "serve_exit":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(pchar, "questTemp.Terrapin");
			pchar.questTemp.Sharlie = "senpierbattle";
			pchar.questTemp.Sharlie.DefendSP = "true";
			AddQuestRecord("Sharlie", "23");
			pchar.quest.DefendSP_prepare.win_condition.l1 = "location";
			pchar.quest.DefendSP_prepare.win_condition.l1.location = "Martinique";
			pchar.quest.DefendSP_prepare.function = "DefendSP_PrepareMartinique";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
		break;
		
		// Jason НСО
		case "patria":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.CharleePrince")) DeleteAttribute(pchar, "questTemp.Mtraxx.CharleePrince"); // Rebbebion, удалить команду пиратов на всякий
			DelCharleePrince("");
			dialog.text = "Und das ist erst der Anfang, Monsieur! Ich bin sicher, dass Sie mit solchen militärischen Talenten weit kommen werden! Und ich habe bereits eine andere Aufgabe für einen ausgezeichneten Marineoffizier, mit dem Sie, da bin ich sicher, genauso gut zurechtkommen werden. Darüber hinaus hängt es direkt mit Ihrer vorherigen Mission zusammen.";
			link.l1 = "Ich höre, Monsieur";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Aber lassen Sie mich Ihnen zunächst die Person vorstellen, die mein Büro betreten hat. Treffen Sie Baron Noel Forget, Ehrenmitglied der Französischen Westindien-Handelsgesellschaft. Angekommen im Archipel, um unsere Kolonien für die Ausweitung der Organisation von Zuckerrohrplantagen und anderen Kulturen zu inspizieren, sowie die Möglichkeit der Entwicklung von Handelsbeziehungen in unserer Region zu erkunden. Von Paris aus ist ihm in diesen Angelegenheiten jede Art von Unterstützung und Hilfe vorgeschrieben, was wir zweifellos tun werden. Baron, ich stelle Ihnen Monsieur Charles de Maure vor, einer der talentiertesten Kapitäne im Dienst Frankreichs...";
			link.l1 = "";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			DialogExit();
			sld = characterFromId("Noel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_3":
			dialog.text = "So, Charles, während der Baron und ich Sankt Christopher inspizieren, weise ich dir die folgende Aufgabe zu. Niemand kann französische Siedlungen angreifen und erwarten, damit davonzukommen, und die Spanier, obwohl sie bereits für die Aggression auf Martinique eine Lektion erteilt bekommen haben, müssen für ihre Verbrechen mit ihren Geldbeuteln antworten und den der Kolonie zugefügten Schaden kompensieren.\nZusammen mit dem französischen Baron kam eine mächtige Staffel bestehend aus einem mächtigen 66-Kanonen-Schiff 'Eclatant'. Der Kapitän des Schiffes ist ein erfahrener Seemann, aber zum ersten Mal in der Karibik, also steht er unter deinem Kommando. Zusammen mit 'Eclatant' wirst du an die Küsten der spanischen Insel Trinidad gehen und von den Spaniern eine Geldentschädigung in Höhe von dreihunderttausend Pesos für den Angriff auf Saint Pierre verlangen.";
			link.l1 = "Chevalier, glauben Sie wirklich, dass die Spanier zustimmen werden?";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Ich bin mir sicher - nachdem die 'Eclatant' und Ihre Staffel Fort San Jose in Stücke geschossen haben. Truppen zu landen und die Stadt zu besetzen, dabei Soldaten zu verlieren, denke ich, wird nicht nötig sein. Greifen Sie ohne Vorwarnung an, zerstören Sie das Fort und signalisieren Sie dann dem Kommandanten, dass Sie die Bedingungen festlegen wollen. In dieser Situation werden die Spanier keinen Ausweg haben und sie werden es vorziehen zu zahlen. Was würden Sie tun, wenn Sie anstelle des Gouverneurs der Stadt handeln würden, die ohne Schutz zurückgelassen wurde?";
			link.l1 = "Hmm, scheint vernünftig, Chevalier.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ist es klar, was du zu tun hast?";
			link.l1 = "Ja, Eure Gnaden.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			// belamour legendary edition фикс проверки мундира с мушкетом
			if(IsUniformEquip())
			{
				dialog.text = " Dann machen Sie sich an die Arbeit. Hier ist ein Brief für den Kapitän der 'Eclatant' mit Bestätigung Ihrer Autorität. Dieses hervorragende Schiff mit einer gut ausgebildeten Besatzung steht Ihnen nun zur Verfügung. Charles, und vergessen Sie nicht, dass Sie jetzt Frankreich dienen, und um mit Beamten wie mir ordnungsgemäß zu kommunizieren, wird empfohlen, eine Uniform zu tragen. Es passt perfekt zu Ihnen. Viel Glück, Kapitän de Maure!";
			}
			else
			{
				dialog.text = " Dann machen Sie sich an die Arbeit. Hier ist ein Brief für den Kapitän der 'Eclatant' mit Bestätigung Ihrer Autorität. Dieses hervorragende Schiff mit einer gut ausgebildeten Besatzung steht Ihnen jetzt zur Verfügung. Oh und Charles: Zieh eine Kapitänsuniform an, ich befehle es dir! Erstens ist es für einen Offizier der französischen Königsmarine nicht würdig, wie ein Händler oder irgendein Freibeuter auszusehen, und zweitens steht dir deine Uniform perfekt. Führen Sie sofort aus, Kapitän de Maure!";
			}
			link.l1 = "";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "1");
			pchar.questTemp.Patria = "epizode_1";
			Patria_SetEcliaton();
			pchar.questTemp.GoldenGirl_Block = true;	// Запрещаем квест Дороже Золота
		break;
		
		case "patria_8_1":
			if (sti(pchar.money) >= 300000) AddMoneyToCharacter(pchar, -300000);
			else pchar.questTemp.Patria.NoMoney = "true";
			dialog.text = "'Eclatant' sank? Charles, das ist eine Katastrophe! Was wird der Minister jetzt sagen? Sie haben mich enttäuscht, Charles! Ich war sicher, ich könnte mich auf Ihre Erfahrung verlassen, und Sie... Ach, aber Sie werden dafür verantwortlich gemacht. Ich werde einen Bericht schreiben, und es wäre besser, Sie verschwinden für eine Weile. Ihr Dienst in der königlichen Marine ist vorbei.";
			link.l1 = "Hmm... Es tut mir leid, Monsieur. Es scheint, dass es wirklich besser für mich ist, für ein oder zwei Monate zu verschwinden, bis der Minister seinen Zorn beruhigt hat. Auf Wiedersehen, und noch einmal, es tut mir sehr leid, Sie enttäuscht zu haben.";
			link.l1.go = "patria_8_2";
		break;
		
		case "patria_8_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "8");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			if (CheckAttribute(pchar, "questTemp.Patria.NoMoney"))
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -20);
				ChangeCharacterNationReputation(pchar, FRANCE, -30);
				DeleteAttribute(pchar, "questTemp.Patria.NoMoney");
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -5);
				ChangeCharacterNationReputation(pchar, FRANCE, -5);
			}
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
		break;
		
		case "patria_8":
			if (sti(pchar.money) >= 300000)
			{
				dialog.text = "Perfekt!";
				link.l1 = "Hier, bitte nehmen Sie diese dreihunderttausend.";
				link.l1.go = "patria_9";
			}
			else
			{
				dialog.text = "Perfekt, aber wo ist das Geld, Charles?";
				link.l1 = "Hmm, in der Truhe auf dem Schiff, ich liefere es in einem Moment!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_8_3":
			DialogExit();
			npchar.dialog.currentnode = "patria_8_4";
		break;
		
		case "patria_8_4":
			dialog.text = "Also, Charles, haben Sie das Lösegeld aus Trinidad mitgebracht?";
			if (sti(pchar.money) >= 300000)
			{
				link.l1 = "Ja, Monsieur. Hier ist es.";
				link.l1.go = "patria_9";
			}
			else
			{
				link.l1 = "Ich bringe es in einem Moment!";
				link.l1.go = "patria_8_3";
			}
		break;
		
		case "patria_9":
			AddMoneyToCharacter(pchar, -300000);
			dialog.text = "Ich bin zufrieden mit dir, Charles, du enttäuschst nie. Die Aufgabe war nicht einfach, und dir wird eine Summe von 50.000 Pesos aus dem Erlösungsbetrag als Belohnung gewährt. Nimm es, es gehört alles dir.";
			link.l1 = "Mein Dank, Chevalier.";
			link.l1.go = "patria_10";
		break;
		
		case "patria_10":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "Es gibt bereits eine neue Aufgabe für Sie. Monsieur Forget hat die Inspektion auf Saint Christopher abgeschlossen und möchte nun unsere nördlichen Kolonien besuchen. Ich bitte Sie, den Baron nach Tortuga und Hispaniola zu bringen, ihm in jeder Hinsicht bei seinen Angelegenheiten zu helfen und seine Anfragen zu erfüllen. Ist das klar, Charles?";
			link.l1 = "Natürlich, Chevalier.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Der Baron hat wenig Zeit, also bitte ich Sie, sich nicht von anderen Angelegenheiten ablenken zu lassen und die Reise nicht länger als zwei Monate zu verzögern.";
			link.l1 = "Natürlich, Monsieur. Die Reise zwischen den Inseln dauert nicht so lange, es sei denn, Monsieur Forgets Geschäfte in den Kolonien sind zeitaufwendig.";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Perfekt. Dann wird der Baron auf Ihrem Schiff reisen. Geben Sie ihm die beste Kabine, die es gibt.";
			link.l1 = "Natürlich, Chevalier!";
			if(IsUniformEquip()) link.l1.go = "patria_13";
			else link.l1.go = "patria_13_1";
		break;
		
		case "patria_13_1":
			dialog.text = "Und noch etwas, Charles: Sie sind schon wieder ohne Ihre Offiziersuniform! Dies ist Ihre letzte Warnung. Von diesem Moment an bitte ich Sie, nur in Uniform zu mir zu kommen, sonst werde ich Ihnen nicht zuhören. Sie sind im Dienst, und Disziplin sollte alles sein, insbesondere im Aussehen eines Marineoffiziers!";
			link.l1 = "Verzeihen Sie mir, Chevalier. Das wird nicht wieder vorkommen.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "9");
			pchar.questTemp.Patria = "epizode_2";
			Patria_VisiterBegin();
			pchar.quest.Patria_SanJoseReturnOver.over = "yes"; // снять таймер
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_14":
			sld = characterFromId("Noel");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
			dialog.text = "Ich hatte keinen Zweifel, dass Ihre Reise erfolgreich sein würde. Gibt es Neuigkeiten aus Tortuga oder aus Port-au-Prince?";
			link.l1 = "...";
			link.l1.go = "patria_15";
		break;
		
		case "patria_15":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_16";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_16":
			dialog.text = "";
			link.l1 = "Ja, Chevalier, ich bringe Nachrichten, aber sie sind nicht sehr angenehm. Zuerst ist sich der Gouverneur von Port-au-Prince sicher, dass die Spanier einen Angriff auf die Kolonie vorbereiten und dafür stellen sie eine Militäreskadron auf ... em-m, wie heißt es ... auf Santiago, ja. Und das scheint kein Gerede zu sein. Ich glaube, dass wir diese Angelegenheit nicht ignorieren können, insbesondere da die Plantagen von Port-au-Prince eine der besten sind, die ich je gesehen habe.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Planen die Spanier einen Angriff auf Port-au-Prince? Hmm... In Ordnung. Wir werden Ihnen befehlen, sich mit diesem Kapitän Charles de Maure zu befassen. 'Eclatant' ist gerade repariert, ausgerüstet und bereit zum Segeln...";
			link.l1 = "Und noch etwas, Monsieur: In Paris gilt die Insel Saint Martin, die nördlich von hier liegt, als französische Kolonie, aber Kapitän Charles de Maure hat mir gesagt, dass die Holländer dort die Kontrolle haben. Ist das so, Chevalier?";
			link.l1.go = "patria_18";
		break;
		
		case "patria_18":
			dialog.text = "Hmm... Das stimmt bis zu einem gewissen Punkt. Saint Martin ist eine französische Kolonie. Allerdings, Baron, aus wirtschaftlicher Sicht ist diese Insel absolut nutzlos - das Gebiet ist klein, der Boden dort ist karg, mager, Süßwasser ist knapp und das, was in den Brunnen ist, ist trüb und bitter. Man hat mir sogar erzählt, dass dort Regenwasser zum Trinken gesammelt wird.\nDeshalb wurde Saint Martin an die Niederländische Westindien Handelsgesellschaft zur langfristigen Pacht übertragen, die es als nördlichen Transitpunkt für die Schiffe der Gesellschaft von der Region zur Metropole nutzt. Die Niederländer haben dort die Siedlung Phillipsburg erweitert, eine Festung und einen Hafen gebaut, und für diejenigen, die erst kürzlich in den Archipel gekommen sind, wie Kapitän Charles de Maure, scheint Saint Martin wie eine niederländische Kolonie.";
			link.l1 = "Aber de jure gehört die Insel uns?";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			dialog.text = "Natürlich. Aber wie ich schon sagte, es ist profitabler, Geld für Miete zu bekommen, als seine knappen Ressourcen zu nutzen.";
			link.l1 = "Es scheint mir, dass diese Insel sehr nützlich für die Französische Westindien-Handelsgesellschaft sein würde, wenn sie in der Karibik erscheint. Die Bedeutung, die Sie gerade angekündigt haben - der nördliche Außenposten auf dem Weg nach Europa. Ich muss diese Kolonie besuchen, und es ist sehr wahrscheinlich, dass die Vermietung der Insel an die Niederländer eingestellt wird.";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Zuerst müssen Sie eine Anfrage an Willemstad, den Direktor der Niederländischen Westindischen Handelsgesellschaft, die Münze von Peter Stuyvesant, senden. Er muss seine Erlaubnis für die Inspektion der Insel geben - schließlich sind die Niederländer schon lange dort.";
			link.l1 = "Dann müssen wir einen Kurier nach Willemstad schicken.";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			dialog.text = "Das Problem ist, Mynheer Stuyvesant ist selten in Willemstad anwesend, er ist ständig auf Reisen und kümmert sich um die Angelegenheiten der Kompanie auf seinem Galeon...";
			link.l1 = "Aber zumindest ist er manchmal dort, nehme ich an? Wie auch immer, die Holländer sind verpflichtet, die Inspektionsrechte an die rechtmäßigen Eigentümer zu gewährleisten. Warum schicken wir nicht einen Brief an den Gouverneur von Philipsburg?";
			link.l1.go = "patria_22";
		break;
		
		case "patria_22":
			dialog.text = "Herr Martin Thomas, bei allem gebotenen Respekt, er ist nur ein einfacher Angestellter, das wirkliche Management wird von der Kompanie ausgeführt. Baron, ich werde dieses Problem lösen, machen Sie sich keine Sorgen, es wird einige Zeit in Anspruch nehmen.";
			link.l1 = "Nun, ich habe viel Zeit. Schließlich müssen wir noch die südlichen Kolonien, Guadeloupe und Martinique, besuchen. Schade, dass Kapitän Charles de Maure diesmal nicht mit mir kommt - er muss wieder nach Hispaniola...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetActorType(pchar); // 17-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_24";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
		break;
		
		case "patria_24":
			dialog.text = "Ja, ja, wir verzögern unseren lieben Kapitän mit unseren langweiligen Gesprächen! Charles, bringe die 'Eclatant' zur Staffel, fahre nach Hispaniola und informiere dich über mögliche echte Bedrohungen für Port-au-Prince von den Spaniern. Wenn es welche gibt, dann kümmere dich darum. Allerdings ist es nicht an mir, dir etwas beizubringen, du weißt alles besser als ich. Wenn du nichts findest, dann solltest du deine Zeit nicht verschwenden, ich brauche dich hier. Ich warte nicht länger als einen Monat auf deinen Bericht. Viel Glück, mein Freund!";
			link.l1 = "Danke, Chevalier. Ich werde sofort auslaufen.";
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10) link.l1.go = "patria_25_1";
			else link.l1.go = "patria_25_2";
		break;
		
		case "patria_25_1":
			dialog.text = "Und noch eine Sache, Charles: Ich habe gehört, du hast Probleme mit den niederländischen Behörden? Bitte, kläre diese Angelegenheit so schnell wie möglich, in naher Zukunft wirst du ihre Kolonien besuchen müssen. Wie du verstehst, wäre das unter Beschuss der Festungen unmöglich.";
			link.l1 = "Gut, Monsieur, es wird erledigt werden.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25_2":
			dialog.text = "Und noch eine Sache, Charles: Ich warne Sie: Vermeiden Sie jegliche Konflikte mit den Holländern. In naher Zukunft müssen Sie ihre Kolonien besuchen. Wie Sie verstehen, wäre das unter Beschuss der Befestigungen unmöglich...";
			link.l1 = "Gut, Monsieur. Keine Streitigkeiten mit den Niederländern.";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "15");
			pchar.questTemp.Patria = "epizode_3";
			Patria_PortPaxBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_26_1":
			dialog.text = "'Eclatant' sank? Charles, das ist eine Katastrophe! Was wird der Minister jetzt sagen? Du hast mich enttäuscht, Charles! Ich war mir sicher, dass ich mich auf deine Erfahrung verlassen konnte, und du ... Ach, aber du wirst dafür verantwortlich gemacht werden. Ich werde einen Bericht schreiben, und es wäre besser, du verschwindest für eine Weile. Dein Dienst in der Königlichen Marine ist vorbei.";
			link.l1 = "Hmm ... Es tut mir leid, Monsieur. Es scheint, dass es für mich wirklich besser ist, für ein oder zwei Monate zu verschwinden, bis der Minister seinen Zorn beruhigt hat. Auf Wiedersehen, und nochmals entschuldigen Sie, dass ich Sie im Stich gelassen habe.";
			link.l1.go = "patria_26_2";
		break;
		
		case "patria_26_2":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Patria = "fail";
			AddQuestRecord("Patria", "19");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			RemoveItems(pchar, "patent_fra", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterNationReputation(pchar, FRANCE, -5);
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
		break;
		
		case "patria_26":
			dialog.text = "Ausgezeichnet! Solange wir Kapitäne wie dich in unserer Marine haben, sollten wir die Tricksereien der Kastilier nicht fürchten. Ich werde morgen einen Kurier mit einer Depesche und Post aus Frankreich nach Port-au-Prince schicken, und gleichzeitig werde ich in einem persönlichen Brief an Monsieur Jeremy Deschamps du Mussaca den Hinweis hinterlassen, dass es nett wäre, dir für den Dienst zu danken, so kann ich versichern, dass du, Charles, eine wohlverdiente Auszeichnung bekommst. \nUnd jetzt gehen wir zu deiner nächsten Aufgabe über. Ja, mein Freund, ich habe eine neue Aufgabe für dich, diesmal jedoch keine militärische, sondern eine sehr heikle, und ich möchte, dass du sie erledigst.";
			link.l1 = "Ich bin ganz Ohr, Chevalier.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Ich nehme an, Sie erinnern sich an meine Diskussion mit Monsieur Forget über Saint Martin? Wir müssen den Baron versichern, dass die Kolonie inspiziert wurde, und Sie werden nach Curacao, nach Willemstad, zum Direktor der Gesellschaft Peter Stuyvesant gehen. Er ist gerade dort und wird es noch drei weitere Wochen sein. Außerdem müssen Sie die Fluyt mit den Waren der Gesellschaft nach Curacao eskortieren und Mynheer Stuyvesant einen Brief von mir übergeben.";
			link.l1 = "Sind das alle Aufgaben?";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			dialog.text = "Ja, Kapitän. Informieren Sie mich über Mynheer Stuyvesants Antwort. Wir sollten gerade rechtzeitig vor Monsieur Forgets Rückkehr von seiner Reise nach Martinique und Guadeloupe sein, und er wird endlich in der Lage sein, Saint Martin zu besuchen, was er wirklich besuchen möchte.";
			link.l1 = "Sehr gut. Darf ich gehen?";
			link.l1.go = "patria_29";
		break;
		
		case "patria_29":
			dialog.text = "Du darfst, Charles. Lass dir nicht zu viel Zeit, der Baron mag es nicht zu warten. Und während du Peter Stuyvesant besuchst, achte darauf, deine Uniform zu tragen! Alles muss offiziell aussehen, wenn du verstehst, was ich meine.";
			link.l1 = "Natürlich, Chevalier. Auf Wiedersehen!";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "20");
			pchar.questTemp.Patria = "epizode_4";
			Patria_CureerBegin();
			pchar.quest.Patria_PortPaxOver.over = "yes"; // снять таймер
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_1");
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_31":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "Danke, Kapitän, geben Sie es mir... (liest)... Nun, ausgezeichnet! Peter Stuyvesant sagt, dass Baron Forget in der Lage sein wird, Saint Martin zur Inspektion zu besuchen und dass der Gouverneur von Philipsburg darüber informiert wird und kooperieren wird. Ich denke, nach einem Besuch wird der Baron die richtige Entscheidung treffen - die Insel zur Vermietung an die Niederländer zu lassen.\nUnd nun die erfreulichsten Nachrichten, Kapitän! Ich habe ein paar Dinge zu erzählen. Erstens: Unter Berücksichtigung all Ihrer militärischen Leistungen werden Sie zum 'Kommodore' befördert. Akzeptieren Sie meine Glückwünsche, Monsieur!";
			link.l1 = "Ich diene Frankreich!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			dialog.text = "Und zweitens: Der Gouverneur von Port-au-Prince hat uns ein Handelsschiff voller Güter für Euch geschickt: 500 große Säcke Kaffee und nochmals 500 Säcke Kakao. Dies sind die gesamten Ernten von Plantagen in Hispaniola, die Ihr vor den spanischen Überfällen geschützt habt. Außerdem war eine besonders wertvolle Fracht für Euch bestimmt - 50 Einheiten Lignum vitae. Ich glaube nicht, dass ich Euch erklären muss, was das ist. Eure Güter befinden sich im Lager beim Händler in Capsterville, und Ihr könnt sie jederzeit vom Händler abholen.";
			link.l1 = "Danke Ihnen, Chevalier! Fantastische Neuigkeiten!";
			link.l1.go = "patria_33";
		break;
		
		case "patria_33":
			dialog.text = "Und nun zu Ihrer nächsten Aufgabe: Baron Forget wird jeden Tag nach Saint-Christopher zurückkehren. Sie werden ihn nach Saint Martin bringen und dafür sorgen, dass er gut bewacht wird. Und, sozusagen, Sie werden genau beobachten, was in Philipsburg vor sich geht, und dann an mich berichten. Verlassen Sie die Stadt nicht, Kapitän, sobald der Baron ankommt - mein Bauer wird Sie finden und Bericht erstatten.";
			link.l1 = "Alles ist klar. Darf ich gehen?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "Ja, das dürfen Sie. Ein paar Tage Ruhe an Land werden Ihnen guttun und nützlich sein.";
			link.l1 = "...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "25");
			pchar.questTemp.Patria = "epizode_5";
			pchar.quest.Patria_CureerBackOver.over = "yes"; // снять таймер
			Items[sti(pchar.EquipedPatentId)].TitulCur = 4; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.quest.Patria_SanMartin_wait.win_condition.l1 = "Timer";
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.hour  = 8+rand(2);
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1+rand(1));
			pchar.quest.Patria_SanMartin_wait.win_condition.l2 = "Location_Type";
			pchar.quest.Patria_SanMartin_wait.win_condition.l2.location_type = "town";
			pchar.quest.Patria_SanMartin_wait.function = "Patria_SanMartinBaron";
			pchar.questTemp.Patria.Goods = "true"; // товары-призы
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_36":
			DialogExit(); // переключение на инспектора
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Noel"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_37";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "patria_37":
			dialog.text = "";
			link.l1 = "Ja, Chevalier, schon zurück! Ihre holländischen Freunde bei Saint Martin haben uns mit Feuer aus den Kanonen des Forts empfangen und uns mit einem Geschwader von drei Schiffen angegriffen. Nur dank der Fähigkeiten von Kapitän Charles de Maure und seiner Besatzung konnten wir entkommen! Es scheint, Mynheer Peter Stuyvesant möchte tatsächlich keine Gesandten des französischen Königs in Philipsburg sehen, was halten Sie davon, Chevalier?";
			link.l1.go = "patria_38";
		break;
		
		case "patria_38":
			dialog.text = "Was?! Hier ist ein Brief von Stuyvesant mit seiner persönlichen Unterschrift, in dem er garantiert...";
			link.l1 = "Aber der Kommandant des Forts Philipsburg hat offensichtlich einen anderen Brief von Stuyvesant erhalten, in dem er ihm befahl, nach Belieben zu feuern und uns mit einem Geschwader zu überfallen! War das ein Unfall, Chevalier?! Nein! Sie haben dort eindeutig auf uns gewartet! Mit Kanonenkugeln und Schrot!";
			link.l1.go = "patria_39";
		break;
		
		case "patria_39":
			dialog.text = "Baron, ich bitte Sie... Ich werde mich darum kümmern. Wir werden unseren lieben Kapitän, Charles de Maure, sofort erneut nach Curacao schicken, um sich mit Stuyvesant zu treffen. Der Kapitän hat eine lange Geschichte des Umgangs mit heiklen Situationen... Und jetzt werde ich die Diener bitten, ein Bad und ein gutes Mittagessen für Sie vorzubereiten.";
			link.l1 = "..., Freund.";
			link.l1.go = "patria_40";
		break;
		
		case "patria_40":
			DialogExit();
			LAi_SetActorType(pchar); // 14-add
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "patria_41";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "patria_41":
			dialog.text = "Charles, mein Freund, du musst dich beeilen nach Willemstad. Vielleicht ist Stuyvesant noch dort. Wenn nicht - finde heraus, wo er ist und finde ihn. Erzähle ihm bei dem Treffen von dem Vorfall und verlange eine Erklärung. Ich verlasse mich auf deine Erfahrung und Autorität und beauftrage dich, die Verhandlungen zu führen. Dann, ohne eine einzige Minute zu verschwenden, komm zurück und berichte mir über die Ergebnisse des Treffens.";
			link.l1 = "Die Aufgabe ist klar, Chevalier. Ich werde das Schiff vorbereiten und sofort aufbrechen.";
			link.l1.go = "patria_42";
		break;
		
		case "patria_42":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "29");
			pchar.questTemp.Patria = "epizode_6";
			Patria_DiplomatBegin();
			ChangeCharacterComplexReputation(pchar, "nobility", 3); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "patria_43":
			dialog.text = "Ich kann das nicht glauben...";
			link.l1 = "Außerdem wurde ich auf dem Rückweg von einem holländischen Marinegeschwader angegriffen. Bitte erklären Sie mir, Chevalier, was hier vor sich geht?";
			link.l1.go = "patria_44";
		break;
		
		case "patria_44":
			dialog.text = "Mein Freund, ich weiß, wie scharfsinnig du bist, also werde ich dir nichts verbergen. Das einzige, was ich von dir verlange - was du hören wirst, darf dieses Zimmer nicht verlassen. Versprichst du das?";
			link.l1 = "Natürlich, Chevalier.";
			link.l1.go = "patria_45";
		break;
		
		case "patria_45":
			dialog.text = "In Ordnung. Ich bin sicher, eine große Karriere in der französischen Marine erwartet Sie. Mit meiner Hilfe, natürlich, können Sie zum Vizeadmiral aufsteigen! Aber ich schweife ab... Und jetzt, was die Niederländer und Saint Martin betrifft.\nLange bevor Sie nach Saint Martin kamen, wurden dort große Salzvorkommen gefunden. Anfangs kümmerte sich niemand darum, aber dann zeigten die Spanier in Kuba und Hispaniola großes Interesse daran - um Bullenleichen zu salzen. Wie Sie zweifellos verstehen, können wir nicht direkt mit Spanien handeln, daher...";
			link.l1 = "...Sie haben einen 'Vermittler' in Form der niederländischen Westindien-Handelsgesellschaft geschaffen...";
			link.l1.go = "patria_46";
		break;
		
		case "patria_46":
			dialog.text = "Genau! Sie denken schnell - und genau, Charles! Und jetzt, da er von der Inspektion aus Paris weiß, hat Stuyvesant beschlossen, das Salzgeschäft ganz kühn in die eigenen Hände zu nehmen, in der Hoffnung, dass wir nicht darauf erpicht sind, allen von unserem Handel mit den Spaniern zu erzählen. Aber da lag er falsch. Niemand kann es wagen, dem französischen Generalgouverneur etwas ungeahndet aus den Händen zu nehmen! Und genau das werden wir ihm zeigen.";
			link.l1 = "Soweit ich verstehe, darf Baron Forget nichts davon wissen...";
			link.l1.go = "patria_47";
		break;
		
		case "patria_47":
			dialog.text = "Mein Freund, du hast absolut recht, der Baron muss die Details nicht wissen. Genug ist schon passiert: ein Versuch, das Leben des Vertreters des französischen Königs zu nehmen, der Angriff auf die Schiffe der diplomatischen Mission, das heißt - auf dich, und am wichtigsten: die de facto Annexion der Insel Saint Martin! Das reicht aus, um militärische Maßnahmen gegen die Niederländer zu rechtfertigen.";
			link.l1 = "Krieg?!";
			link.l1.go = "patria_48";
		break;
		
		case "patria_48":
			dialog.text = "Genau! Mein Freund, die Position des Vizeadmirals ist nicht so weit von Ihnen entfernt, verstehen Sie? Stellen Sie sich vor, Sie sind in einer Admiralsuniform bei den Gesprächen im Louvre, und Louis XIV selbst wird einen so ehrenvollen Gast akzeptieren... Wir müssen die Holländer an ihren Platz setzen! Stuyvesant wird bereuen, was er getan hat. Stimmen Sie zu?";
			link.l1 = "Ich stimme zu, Chevalier. Die Holländer müssen für ihre empörenden und abscheulichen Taten geradestehen.";
			link.l1.go = "patria_49";
		break;
		
		case "patria_49":
			dialog.text = "Ausgezeichnet. Ich werde den Baron sofort über unsere Entscheidung informieren und Boten zu den französischen Kolonien schicken! Und Sie, mein Freund, können sich nach einer langen Reise ausruhen und mich bitte morgen nach neun Uhr morgens besuchen. Ich werde eine Kampfaufgabe für Sie vorbereiten.";
			link.l1 = "Sehr gut, Monsieur. Erlauben Sie mir, mich zu entschuldigen.";
			link.l1.go = "patria_50";
		break;
		
		case "patria_50":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			LAi_SetHuberType(npchar);
			AddQuestRecord("Patria", "33");
			pchar.questTemp.Patria = "epizode_7";
			Patria_HunterBegin();
			pchar.quest.Patria_DiplomatTimeOver.over = "yes"; // снять таймер
			ChangeCharacterComplexReputation(pchar, "nobility", 1); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "patria_51":
			dialog.text = "Ich würde es nicht Krieg nennen, eher eine erzwungene Friedensschaffung. Und wenn Stuyvesant seine Meinung ändert, wird es uns nur noch glücklicher machen. Deshalb müssen wir ihm jetzt zeigen, dass er beim Versuch, die Insel Saint Martin zu beanspruchen, viel mehr verlieren wird, als er gewinnen kann. Hier kommst du ins Spiel, Charles.";
			link.l1 = "Ich höre zu.";
			link.l1.go = "patria_52";
		break;
		
		case "patria_52":
			dialog.text = "Heiliger Martin ist eine Umschlagbasis für die niederländischen Schiffe, die nach Europa fahren. Die Schiffe der Kompanie halten regelmäßig in der Bucht von Philipsburg. Bis jetzt waren die Gewässer für sie ziemlich sicher. Bis jetzt, Kapitän!.. Sie werden sich auf den Weg zu den Ufern von Heiliger Martin machen und dort patrouillieren und Handelsschiffe der Kompanie einfangen.\nFür den Transport wertvoller Güter nutzt die Kompanie die Ostindier - harte, gut bewaffnete Schiffe mit großen Laderäumen. Das werden Ihre Ziele sein. Fangen Sie fünf solcher Schiffe zusammen mit ihren Waren und bringen Sie sie als Preise nach Casterville. Danach werden wir die Verhandlungen mit Stuyvesant fortsetzen und vielleicht wird er seine Meinung ändern, nachdem er die Verluste gezählt hat.";
			link.l1 = "Die Aufgabe ist klar. Kann ich gehen?";
			link.l1.go = "patria_53";
		// belamour legendary edition -->
			link.l2 = "Herr, ich bin gezwungen zu fragen, könnten Sie sich an der Finanzierung dieser Operation beteiligen. Es werden Monate des Segelns, ständige Reparaturen und Verluste sein...";
			link.l2.go = "patria_53a";
		break;
		
		case "patria_53a":
			AddMoneyToCharacter(pchar, 20000);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			dialog.text = "Ich fürchte, unsere Reserven sind erschöpft, Charles. Die Instandhaltung der Ecliaton und die Kämpfe haben uns bereits ein halbes Jahresbudget der französischen Kolonien gekostet. Das ist alles, was ich dir jetzt geben kann. Denke an zukünftige Auszeichnungen, Charles! Eine großartige Zukunft erwartet dich!";
			link.l1 = "Jawohl, Herr!";
			link.l1.go = "patria_54";
		break;
		// <-- legendary edtion
		case "patria_53":
			dialog.text = "Geh, mein Freund, und möge das Glück deinem jeden Schritt folgen.";
			link.l1 = "...";
			link.l1.go = "patria_54";
		break;
		
		case "patria_54":
			DialogExit();
			npchar.dialog.currentnode = "First time";
			AddQuestRecord("Patria", "34");
			pchar.questTemp.Patria = "epizode_7_continue";
			Patria_HunterContinue();
		break;
		
		case "patria_55":
			pchar.questTemp.Patria.Hunter = sti(pchar.questTemp.Patria.Hunter)+1;
			if (sti(pchar.questTemp.Patria.Hunter) > 4) // все собрал
			{
				dialog.text = "Sie haben die Aufgabe, Kapitän, abgeschlossen. Ich danke Ihnen für Ihren hervorragenden Dienst! Sie sollten einen Teil des Einkommens aus dem Verkauf der Trophäen erhalten - zweihunderttausend Pesos.";
				link.l1 = "Freut mich zu hören, Monsieur!";
				link.l1.go = "patria_57";
			}
			else
			{
				dialog.text = "Also, du hast nur "+FindRussianQtyString(5-sti(pchar.questTemp.Patria.Hunter))+" Holländische Schiffe sind unterwegs, um in unseren Hafen zu gelangen.";
				link.l1 = "Ja, Chevalier!";
				link.l1.go = "patria_56";
			}
		break;
		
		case "patria_56":
			DialogExit();
			AddQuestRecord("Patria", "35");
			AddQuestUserData("Patria", "sQty", 5-sti(pchar.questTemp.Patria.Hunter));
			DeleteAttribute(pchar, "questTemp.Patria.Hunter.GiveShip");
		break;
		
		// belamour legendary edition -->
		case "patria_57":
			AddMoneyToCharacter(pchar, 200000);
			dialog.text = "Und das ist noch nicht alles. Ich habe neulich ein wenig nachgedacht... Charles, du hast wirklich viel für Frankreich getan. Die Eliminierung, ehrlich gesagt, des Verräters Levasseur, die Verteidigung von Saint-Pierre vor dem heimtückischen Angriff Spaniens, die erfolgreiche Niederlage der Festung der Kolonie San Jose und der Erhalt einer Entschädigung von den Spaniern als Strafe für ihren gewagten Trick... Und danach haben Sie persönlich den Vertreter der französischen Krone begleitet, der aus Europa ankam, und sogar sein Leben gerettet, indem Sie aus einem niederländischen Hinterhalt in den Gewässern von Philipsburg entkamen!";
			link.l1 = "Herr, wirklich, Sie bringen mich in Verlegenheit... Ich mache nur meine Pflicht.";
			link.l1.go = "patria_57_1";
		break;
		
		case "patria_57_1":
			PlaySound("interface\important_item.wav");
			dialog.text = "Sie sind wie immer bescheiden, mein Freund. Und jetzt, bei der Ausführung der nächsten Aufgabe, Holland zum Frieden zu zwingen, haben Sie mich wieder nicht im Stich gelassen. Sie fürchten dieses Wort nicht - der Held der Nation! Als Generalgouverneur der französischen Kolonien im Archipel habe ich mehrere Exemplare der höchsten Auszeichnung Frankreichs bei mir und ... Aber übrigens, ich bitte Sie, dieses Dokument zu lesen.";
			link.l1 = "Für hervorragenden Dienst an Frankreich... im Namen Seiner Majestät des Königs von Frankreich... um einen Marineoffizier im Dienst Frankreichs, Kapitän Charles de Maure, Sohn von Henri de Montpe... Chevalier, machst du Witze?";
			link.l1.go = "patria_57_2";
		break;
		
		case "patria_57_2":
			dialog.text = "Keineswegs, mein Freund. Ich habe die Ehre, Sie so zu belohnen, wie Sie es verdienen, indem ich Ihnen die höchste Auszeichnung Frankreichs überreiche - den Orden des Heiligen Ludwig! Jeder Bürger unseres Landes sollte seinen Helden kennen! Und Saint-Pierre schuldet Ihnen! Sie verdienen diesen Orden, Charles.";
			link.l1 = "Wirklich, ich weiß nicht, was ich sagen soll... Danke, Gouverneur General! Ich schwöre, Frankreich mit Stolz zu dienen und nicht vor dem Feind zurückzuweichen!";
			link.l1.go = "patria_57_3";
		break;
		
		case "patria_57_3":
			GiveItem2Character(pchar, "talisman9");
			Log_Info("You've received the Order of Saint Louis! You are the hero of the nation!");
			PlaySound("interface\important_item.wav");
			DoQuestCheckDelay("sea_victory", 0.5);
			dialog.text = "Worte eines wahren Offiziers! Ich bin wirklich stolz auf dich, Charles. Ruhe dich jetzt ein wenig aus. Du hast es verdient. In der Zwischenzeit werde ich Verhandlungen mit Stuyvesant führen - vielleicht hat er bereits erkannt, dass es für ihn viel unvorteilhafter ist, uns feindlich gegenüberzustehen als befreundet zu sein. Verlasse die Stadt nicht, ich werde dich in zwei Tagen brauchen.";
			link.l1 = "Sehr gut, Monsieur. Ich warte auf weitere Anweisungen.";
			link.l1.go = "patria_58";
		break;
		// <-- legendary edtion
		case "patria_58":
			DialogExit();
			AddQuestRecord("Patria", "36");
			pchar.questTemp.Patria = "epizode_7_end";
			pchar.quest.Patria_siege_begin.win_condition.l1 = "Timer";
			pchar.quest.Patria_siege_begin.win_condition.l1.date.hour  = 9.00;
			pchar.quest.Patria_siege_begin.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.Patria_siege_begin.win_condition.l2 = "location";
			pchar.quest.Patria_siege_begin.win_condition.l2.location = "Charles_town";
			pchar.quest.Patria_siege_begin.function = "Patria_SiegeBegin";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 5); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
		case "patria_59":
			dialog.text = "Ja. Es scheint, dass Stuyvesant mit militärischen Maßnahmen in einer Allianz mit Spanien zu reagieren begonnen hat. Ein gemeinsames niederländisch-spanisches Geschwader hat Saint-Christopher belagert. Wachposten berichten mir jede Stunde von jeder ihrer Bewegungen.";
			link.l1 = "Eine Belagerung?";
			link.l1.go = "patria_60";
		break;
		
		case "patria_60":
			dialog.text = "Offensichtlich. Sie haben keinen direkten Angriff durchgeführt, und das ist eigentlich gut. Wir müssen schnell handeln, Kapitän, solange der Feind es nicht geschafft hat, die ganze Insel zu blockieren.";
			link.l1 = "Was müssen wir tun?";
			link.l1.go = "patria_61";
		break;
		
		case "patria_61":
			dialog.text = "In Saint-Jones, auf Antigua, ist das englische Marinegeschwader von Oberst Doily stationiert. Zurzeit besucht er Sir Jonathan Fox. Sie müssen an den feindlichen Schiffen vorbeifahren und nach Antigua gelangen. Dort treffen Sie den Oberst, übergeben ihm meinen Brief und bitten ihn um Hilfe.";
			link.l1 = "Glauben Sie, dass der Oberst uns helfen wird?";
			link.l1.go = "patria_62";
		break;
		
		case "patria_62":
			dialog.text = "Ich hoffe es. Der Brief sollte ihn davon überzeugen, dass die Belohnung für seine Hilfe recht stattlich sein wird... Außerdem müssen wir einen Brief an den Kapitän der 'Eclatant' schicken, der sich derzeit in der Nähe der Küsten von Guadeloupe befindet, er muss sich beeilen, nach Saint-Christopher zu kommen. Die Feuerkraft der 'Eclatant' wird uns im Kampf erheblich helfen. Da du nicht an zwei Orten gleichzeitig sein kannst, wird unser Kurierkutter deinem Geschwader beitreten - du musst ihn unbeschädigt durch den Kreis der Feinde bringen, und er wird nach Guadeloupe abfahren, bevor die 'Eclatant' nach Süden geht...";
			link.l1 = "Ich verstehe. Durchqueren Sie die Belagerung, eskortieren Sie den Kurierkutter und beeilen Sie sich nach Saint-Jones zu Oberst Doily mit Ihrem Brief.";
			link.l1.go = "patria_63";
		break;
		
		case "patria_63":
			dialog.text = "Genau. Sind Sie bereit, ein weiteres Schiff in Ihrer Staffel zu akzeptieren?";
			if (GetCompanionQuantity(pchar) > 4)
			{
				link.l1 = "Ich werde ein Schiff loswerden und zu dir zurückkehren.";
				link.l1.go = "patria_63_1";
			}
			else
			{
				link.l1 = "Ja.";
				link.l1.go = "patria_64";
			}
		break;
		
		case "patria_63_1":
			DialogExit();
			pchar.questTemp.Patria = "epizode_8_wait";
		break;
		
		case "patria_64":
			dialog.text = "Ausgezeichnet. Nehmen Sie den Brief, der Schoner ist bereit und wartet auf Ihre Befehle.";
			link.l1 = "Lassen Sie uns keine Zeit verschwenden, Chevalier!";
			link.l1.go = "patria_65";
		break;
		
		case "patria_65":
			DialogExit();
			AddQuestRecord("Patria", "38");
			pchar.questTemp.Patria = "epizode_8_continue";
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_3");
			Patria_SiegeCreateSquadron();
		break;
		
		case "patria_66":
			dialog.text = "Ja-ja, mein Freund, ich kenne deine Bescheidenheit nur zu gut. Du bist ein wahrer Offizier! Und du wirst belohnt werden, das versichere ich dir! Ich nehme an, nach der schweren Schlacht brauchst du etwas Ruhe? Du hast eine ganze Woche. Komm in sieben Tagen in mein Zimmer, um zu reden - die Stadt wird eine Belohnung für ihren Helden vorbereiten.";
			link.l1 = "Ja, Monsieur. Darf ich gehen?";
			link.l1.go = "patria_67";
		break;
		
		case "patria_67":
			dialog.text = "Gehen Sie und ruhen Sie sich gut aus. Später werden wir uns mit ernsten Fragen befassen müssen - Wie Sie sehen können, ist ein Frieden mit den Niederländern zu diesem Zeitpunkt unmöglich. Vorerst werden der Oberst und ich einige wichtige Fragen besprechen.";
			link.l1 = "Dann treffen wir uns in einer Woche, Chevalier.";
			link.l1.go = "patria_68";
		break;
		
		case "patria_68":
			DialogExit();
			AddQuestRecord("Patria", "45");
			pchar.questTemp.Patria = "epizode_8_end";
			Patria_SiegeEnd();
			ChangeCharacterNationReputation(pchar, FRANCE, 20);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_69":
			pchar.quest.Patria_BastionTimeOver.over = "yes"; //снять таймер
			dialog.text = "Wir haben eine Diskussion mit Oberst Doily geführt und er hat zugestimmt, mir zu helfen. England wird uns im Krieg gegen die Holländer helfen. Sie und ich müssen zurückschlagen und die Gerechtigkeit wiederherstellen - die Insel Saint Martin muss nach Frankreich zurückkehren. Ich übertrage diese Aufgabe dem besten Marinekapitän - Ihnen, Charles de Maure! Der Feind hat sich noch nicht von der Niederlage ihrer Eskadron erholt, wir werden Philipsburg angreifen und einnehmen. \nDie Schlacht wird nicht einfach sein. Zuerst müssen wir das Fort zerstören, dann die Verteidigung der Garnison durchbrechen...(flüstert) Sie werden auch einen erzwungenen Marsch durch den Dschungel zu der Salzlagerstätte machen müssen, von der ich Ihnen erzählt habe, und die dort stationierten Feinde töten...";
			link.l1 = "Die Aufgabe ist ziemlich schwierig, Chevalier...";
			link.l1.go = "patria_70";
		break;
		
		case "patria_70":
			dialog.text = "Ich verstehe dich vollkommen, mein Freund. Dein Geschwader wird verstärkt. Die Gouverneure von Basse-Terre und Saint-Pierre sollten bis jetzt jeweils ein Schiff - eine Fregatte - vorbereitet haben. Du musst nur Guadeloupe und Martinique besuchen und diese Fregatten unter dein Kommando nehmen. Wenn du sie natürlich selbst willst - ich werde nicht auf deiner Wahl der Schiffe bestehen. Ich gebe dir auch eine Subvention in Höhe von 20.000 Pesos, um Proviant und Ausrüstung für dein Flaggschiff zu kaufen. Hier, nimm es...";
			link.l1 = "Sehr gut, Monsieur.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_71";
			else link.l1.go = "patria_71_1";
		break;
		
		case "patria_71_1":
			dialog.text = "Auch wie gewohnt steht Ihnen das Schiff 'Eclatant' zur Verfügung. Es wurde repariert und ausgestattet, wartet auf Reede und nach dem Gespräch mit dem Kapitän können Sie es jederzeit in Besitz nehmen.";
			link.l1 = "Ausgezeichnet!";
			link.l1.go = "patria_71";
			pchar.questTemp.Patria.Ecliaton_Bastion = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_7";
			sld.DeckDialogNode = "ecliaton_cap_7";
		break;
		
		case "patria_71":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "Wir können keine Zeit verschwenden, Kapitän. Wie meine Spione mich informiert haben, verstehen die Holländer die Gefahr für Saint Martin und beabsichtigen, seine Verteidigungen zu verstärken. Aber Sie haben noch zwei Monate. Sie müssen die Aufgabe rechtzeitig abschließen!";
			link.l1 = "Ich werde... (flüstert) Wo ist das Salzlager von Saint Martin? Es ist auf keiner Karte der Insel verzeichnet...";
			link.l1.go = "patria_72";
		break;
		
		case "patria_72":
			dialog.text = "(flüsternd) Wenn du die Stadt angreifst, verhöre den Vizekönig von Philipsburg, Mynheer Martin Thomas, er wird es dir sagen. Dieser Holländer ist ein Feigling und wird dir nicht widerstehen, das garantiere ich dir.";
			link.l1 = "Ich verstehe. Darf ich dann fortgehen?";
			link.l1.go = "patria_73";
		break;
		
		case "patria_73":
			dialog.text = "Warte mal einen Moment, Charles. Du hast deine Belohnung für die Rettung von Saint-Christopher noch nicht erhalten. Nimm diese Kisten Gold von den Leuten der Stadt, sowie unsere aufrichtigste Dankbarkeit, die kein Geldbetrag ausdrücken kann!";
			link.l1 = "Danke, Monsieur!";
			link.l1.go = "patria_74";
		break;
		
		case "patria_74":
			TakeNItems(pchar, "chest", 10);
			Log_Info("You've received 10 chests of doublons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Nun, Sie können gehen. Viel Glück, Kapitän! Wir alle warten auf Ihren Sieg!";
			link.l1 = "Auf Wiedersehen, Chevalier.";
			link.l1.go = "patria_75";
		break;
		
		case "patria_75":
			DialogExit();
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Bastion")) sTemp = "The warship 'Eclatant' will also be under my command.";
			AddQuestRecord("Patria", "48");
			AddQuestUserData("Patria", "sText", sTemp);
			pchar.questTemp.Patria = "epizode_9_continue";
			SetFunctionTimerCondition("Patria_BastionSturmTimeOver", 0, 0, 62, false);
			// вернуть Синт-Маартен в норму
			int n = FindIsland("SentMartin");
			Islands[n].reload.l1.radius = 600.0;
			LocatorReloadEnterDisable("Marigo_ExitTown", "reload3", false); // открыть городские ворота
			sld = CharacterFromID("Marigo Fort Commander");
			LAi_SetImmortal(sld, false);
			Character_SetAbordageEnable(sld, true);
			// атрибут квестовой высадки десанта
			pchar.TempPerks.QuestTroopers = true;
		break;
		
		case "patria_76":
			dialog.text = "Wer hätte vor nur einem Jahr gedacht, dass Sie zum Vizeadmiral befördert werden würden, mein Freund? Ich kann nur erraten, wie stolz Ihr Vater sein wird, wenn die Nachricht davon Frankreich erreicht!";
			link.l1 = "Mein lieber Vater wird sich sehr darüber freuen.";
			link.l1.go = "patria_77";
		break;
		
		case "patria_77":
			dialog.text = "Du hast deinen Platz in der Flotte verdient! Saint Martin wurde an Frankreich zurückgegeben, Stuyvesant hat eine harte Lektion gelernt. Das war ein großer Sieg! Aber wir dürfen nicht aufhören, wir können den Holländern keine Minute Ruhe lassen. Sie werden für ihren Verrat zur Rechenschaft gezogen! Oberst Doily befindet sich gerade in Port-Royal und bereitet seine Marine-Squadron vor: Wir werden den Rücken unseres Feindes brechen, indem wir Curacao angreifen. Aber das wird später sein, denn jetzt müssen wir zwei Fliegen mit einer Klappe schlagen, Charles.\nDie Kompanie hat ihren unermesslichen Reichtum nicht nur mit Handel verdient. Die Haupteinnahmequelle der Holländer in der Region ist die Sklavenarbeit auf ihren Plantagen. Falls du es noch nicht weißt, Charles: Holland ist die größte sklavereibesitzende und sklavenhandelnde Nation. Ostindier, die 'schwarzes Elfenbein' transportieren, kommen regelmäßig aus Westafrika nach Curacao. Und ich weiß zufällig etwas darüber, leider für Stuyvesant.\nGerade jetzt segeln zwei holländische Ostindier aus Guinea in die Karibik. Ihre Laderäume sind voll von schwarzen Gefangenen. In etwa zehn Tagen oder so wird die Karawane um die Insel Trinidad in Richtung Curacao segeln. Deine Aufgabe ist es, die Karawane zu finden und diese beiden Ostindienfahrer und ihre Ladung zu kapern. Du musst die begleitenden Schiffe zerstören und die Sklaven zu unserem Verbündeten, Oberst Doily, nach Jamaika bringen. Das ist sehr wichtig, Charles, so werden wir sein Vertrauen gewinnen... Ich hoffe, du verstehst.\nEs tut mir leid, dir keine Zeit zum Ausruhen zu lassen, aber diese Aufgabe ist wichtig und heikel, und ich kann sie nur dir anvertrauen.";
			link.l1 = "Dienst ist kein Zucker, Chevalier. Ich weiß es besser als jeder andere. Ich werde mein Schiff vorbereiten und so schnell wie möglich abfahren.";
			link.l1.go = "patria_78";
		break;
		
		case "patria_78":
			dialog.text = "Ich wünsche Ihnen gute Winde und eine sichere Reise, Vizeadmiral. Und wenn Sie nach Saint-Christopher zurückkehren, wird unser gemeinsamer Freund, Monsieur Noel Forget, seine Inspektion von Philipsburg abgeschlossen haben, und ich werde sicherstellen, dass ein Teil der Trophäen, die sie von den Holländern nehmen, persönlich an Sie geht.";
			link.l1 = "Es würde mich äußerst dankbar machen, Chevalier. Darf ich gehen?";
			link.l1.go = "patria_79";
		break;
		
		case "patria_79":
			dialog.text = "Geh. Viel Glück, mein Freund!";
			link.l1 = "...";
			link.l1.go = "patria_80";
		break;
		
		case "patria_80":
			DialogExit();
			Items[sti(pchar.EquipedPatentId)].TitulCur = 5; 
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
			pchar.questTemp.Patria = "epizode_10_start";
			AddQuestRecord("Patria", "52");
			Patria_SlaveShipsStart();
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			ChangeCharacterComplexReputation(pchar, "nobility", 10); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 10);
		break;
		
		case "patria_81":
			dialog.text = "Ausgezeichnet! Sie kennen das Wort 'unmöglich' nicht, Charles. Ich dachte immer, Ihr Bruder wäre der beste Marineoffizier in der Karibik, aber er hat viel von Ihnen zu lernen, wenn Sie mir diesen groben Vergleich erlauben. Ich denke, Sie wissen bereits, wer zu unserem lieben Oberst gehen wird, um am Angriff auf Willemstad teilzunehmen.";
			link.l1 = "Auf keinen Fall, Monsieur! Wie könnte ich das wissen!";
			link.l1.go = "patria_82";
		break;
		
		case "patria_82":
			dialog.text = "Ach, dein berühmter Sinn für Humor, mein lieber Freund! Ha-hah! Natürlich, es wird dich sein, Vizeadmiral. Der würdigste von allen. Bist du bereit?";
			link.l1 = "Natürlich, Chevalier. Alles, was ich brauche, sind einige Reparaturen, etwas Ausrüstung - und ich bin bereit zu gehen.";
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton_Fail")) link.l1.go = "patria_83";
			else link.l1.go = "patria_83_1";
		break;
		
		case "patria_83_1":
			dialog.text = "Vergessen Sie nicht, die 'Eclatant' unter Ihr Kommando zu nehmen. Sie wurde repariert und ausgestattet und wartet auf Sie in den Docks. Marquis Hubert Dassier wird bereits ungeduldig und wartet darauf, mit Ihnen in eine weitere Schlacht zu ziehen.";
			link.l1 = "Gut. Ein mächtiges Schiff mit Langstreckenkulverinen ist genau das, was ich brauche, um die Festung zu bombardieren.";
			link.l1.go = "patria_83";
			pchar.questTemp.Patria.Ecliaton_Curacao = "true";
			sld = characterFromId("Ecliaton_Cap");
			sld.dialog.currentnode = "ecliaton_cap_11";
			sld.DeckDialogNode = "ecliaton_cap_11";
		break;
		
		case "patria_83":
			dialog.text = "Warte einen Moment, Charles. Unser Freund, Baron Forget, hat Neuigkeiten für dich aus Saint Martin mitgebracht.";
			link.l1 = "...";
			link.l1.go = "patria_84";
		break;
		
		case "patria_84":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_25";
			sld.greeting = "noel_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 2);
		break;
		
		case "patria_85":
			dialog.text = "Ich habe Neuigkeiten für Sie aus Paris. Ihre Ernennung zum Vizeadmiral wurde vom König unterzeichnet. Sie werden die relevanten Papiere erhalten. Also, ich gratuliere Ihnen!";
			link.l1 = "Danke, Monsieur! Ich diene gerne Frankreich und dem König!";
			link.l1.go = "patria_coat";
		break;
		
		case "patria_coat":
			dialog.text = "Und ich, wie immer, freue mich sehr, diese Worte von Ihnen zu hören. Charles, vielleicht möchten Sie ein wenig Wein mit mir teilen? Direkt aus Paris gebracht, finden Sie hier nichts Vergleichbares, nicht einmal für einen Tagesritt!";
			link.l1 = "Danke, Chevalier, aber ich glaube, ich werde passen. Ich muss später zum Schiff zurückkehren, und es wäre nicht passend, wenn der Vizeadmiral von Frankreich betrunken auf dem Achterdeck stehen würde.";
			link.l1.go = "patria_coat_01";
			link.l2 = "Nun, warum nicht? Es ist nicht jeden Tag, dass ich die Gelegenheit habe, mit dem Generalgouverneur selbst einen Trunk zu teilen!";
			link.l2.go = "patria_coat_02";
		break;
		
		case "patria_coat_01":
			dialog.text = "Nun, Sie könnten eine Pause einlegen, es besteht keine Notwendigkeit, sofort zum Schiff zurückzukehren. Aber es ist Ihr Wunsch, und ich respektiere ihn. Also, lassen Sie uns gleich zur Sache kommen.";
			link.l1 = "Ich höre aufmerksam zu.";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_02":
			dialog.text = "Und nicht jeder Generalgouverneur hat das Glück, dass sein Vizeadmiral nicht nur der beste Marineoffizier ist, sondern auch ein Freund, mit dem er am selben Tisch sitzen und Wein trinken kann, der aus der fernen Heimat gebracht wurde!";
			link.l1 = "Für Frankreich!";
			link.l1.go = "patria_coat_03";
			link.l2 = "Auf Ihre Gesundheit, Chevalier!";
			link.l2.go = "patria_coat_04";
		break;
		
		case "patria_coat_03":
			dialog.text = "Und für den König!";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_04":
			dialog.text = "Und zu deinem, Charles!";
			link.l1 = "...";
			link.l1.go = "patria_coat_05";
		break;
		
		case "patria_coat_05":
			LAi_Fade("", "");
			if(LAi_GetCharacterHP(pchar) == LAi_GetCharacterMaxHP(pchar))
			pchar.chr_ai.hp = stf(pchar.chr_ai.hp) - 1.0;
			GiveItem2Character(pchar, "potionwine");
			DoCharacterUsedItem(pchar, "potionwine");
			npchar.dialog.currentnode = "patria_coat_06";
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorSetHuberMode(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 1.2);
		break;
		
		case "patria_coat_06":
			dialog.text = "Hm, exquisiter Wein! Findest du nicht auch?";
			link.l1 = "Ja, du hattest recht. Es erinnert mich an den Wein, den sie in meiner Heimat Gascogne herstellen...";
			link.l1.go = "patria_coat_07";
		break;
		
		case "patria_coat_07":
			dialog.text = "Du bist ein bisschen daneben, mein Freund - es ist Bordeaux. Trotzdem bin ich sicher, der Wein aus der Gascogne ist genauso gut!";
			link.l1 = "Ich glaube, ich fange an, seinen Geschmack zu vergessen... Wie viel Zeit ist vergangen, seit ich Frankreich verlassen habe? Ein Jahr? Zwei?";
			link.l1.go = "patria_coat_08";
		break;
		
		case "patria_coat_08":
			dialog.text = "Ach, Charles, es fühlt sich an, als hätten wir uns erst kürzlich getroffen...und nicht unter den angenehmsten Umständen. Verzeihen Sie mir, dass ich das zur Sprache bringe, aber hätte mir damals jemand gesagt, dass in der Gefängniszelle vor mir mein zukünftiger rechter Hand in den französischen Kolonien stand, hätte ich wahrscheinlich laut gelacht.";
			link.l1 = "Unergründlich sind die Wege des Herrn.";
			link.l1.go = "patria_coat_09";
		break;
		
		case "patria_coat_09":
			dialog.text = "Entschuldigung, was haben Sie gerade gesagt?";
			link.l1 = "Es ist Latein, Ritter. Die Wege des Herrn sind unergründlich. Niemand weiß, was das Leben bereithält.";
			link.l1.go = "patria_coat_10";
		break;
		
		case "patria_coat_10":
			dialog.text = "Sie hören nie auf, mich zu verblüffen, Charles. Schauen Sie sich an - ich hatte keine Ahnung, dass Sie auch Latein sprechen können. Aber andererseits, in gewissem Maße, schmieden wir unser eigenes Schicksal, nicht wahr?";
			link.l1 = "Ich denke, beides ist wahr. Nur der Herr weiß, was uns bevorsteht. Aber er belohnt die Hartnäckigen.";
			link.l1.go = "patria_coat_11";
		break;
		
		case "patria_coat_11":
			dialog.text = "Ich könnte nicht mehr zustimmen. Ich erinnere mich zum Beispiel daran, wie ich Ihnen die Kommission eines Marineoffiziers überreichte und Ihnen diese Uniform gab. Und jetzt steht vor mir ein Vizeadmiral, nicht weniger!";
			link.l1 = "Die Zeit verfliegt, Ritter.";
			link.l1.go = "patria_coat_12";
		break;
		
		case "patria_coat_12":
			dialog.text = "Indeed... And even on your uniform, I see the cuts left by sabers; some cuts have been stitched, and some are clearly fresh. This needs to be corrected.";
			link.l1 = "Was haben Sie im Sinn, Herr Generalgouverneur?";
			link.l1.go = "patria_coat_13";
		break;
		
		case "patria_coat_13":
			dialog.text = "Neben Ihrer neuen Position als Vizeadmiral der französischen Flotte im karibischen Archipel habe ich noch ein weiteres Geschenk für Sie.";
			link.l1 = "Sie bringen mich zum Erröten, Chevalier. Welches Geschenk?";
			link.l1.go = "patria_coat_14";
		break;
		
		case "patria_coat_14":
			dialog.text = "Ich habe mit meinem persönlichen Schneider - dem besten in den französischen Kolonien! - vereinbart, eine Uniform zu nähen, die Ihrem Rang entspricht. Machen Sie sich keine Sorgen um die Bezahlung, ich habe mich um alles gekümmert.";
			link.l1 = "Ich bin wirklich dankbar! Ich werde sicher Ihren Schneider besuchen. Wo kann ich ihn finden?";
			link.l1.go = "patria_coat_15";
		break;
		
		case "patria_coat_15":
			dialog.text = "Er sollte jetzt im Hafenbüro sein - ein neues Kurierschiff ist gerade vom Festland mit kleinen Paketen angekommen. Unser Schneider bestellt immer einige Materialien, die hier schwer zu finden sind.";
			link.l1 = "Ich gehe dann zum Hafenbüro. Nochmals vielen Dank, Monsieur!";
			link.l1.go = "patria_86";
		break;
		
		case "patria_86":
			dialog.text = "Und jetzt, da bin ich sicher, müssen Sie sich gut ausruhen. Ich gebe Ihnen einen Monat, und sorgen Sie dafür, dass Sie ihn gut nutzen. Keine Arbeit, keine Sorgen. Überlassen Sie alle Arbeiten Ihren Offizieren und ruhen Sie sich gut aus. Sie dürfen die Zimmer in meiner Residenz nutzen. Die Diener werden Ihren Urlaub äußerst komfortabel gestalten. Wir treffen uns in einem Monat wieder - und ich werde eine heikle Angelegenheit mit Ihnen besprechen.";
			link.l1 = "Sehr gut, Chevalier. Auf Wiedersehen!";
			link.l1.go = "patria_87";
		break;
		
		case "patria_87":
			npchar.dialog.currentnode = "First time";
			LAi_Fade("","");
			LAi_SetHuberType(npchar);
			DialogExit();
			AddQuestRecord("Patria", "65"); // далее коллизия Пуанси-Инспектор-Шарль
			pchar.questTemp.Patria = "epizode_12_start";
			ChangeCharacterNationReputation(pchar, FRANCE, 15);
			SetFunctionLocationCondition("Patria_Tailor", "Charles_PortOffice", false)
			Patria_CondotierStart();
			ChangeCharacterComplexReputation(pchar, "nobility", 15); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 15);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
		break;
		
		case "patria_88":
			dialog.text = "Ja, Charles. Ich dachte, ich würde das selbst schaffen, aber... leider muss ich noch einmal deine Talente in Anspruch nehmen. Aber zuerst muss ich dir etwas geben: dreihunderttausend Pesos und fünf Kisten mit Dublonen. Das ist ein großer Teil des Beitrags, den Stuyvesant mir gemäß der Vereinbarung gezahlt hat. Ich nehme an, du hast all das verdient, da du die meiste Arbeit geleistet hast. Nimm es an. Bist du zufrieden, mein Freund?";
			link.l1 = "Geld hat noch nie jemandem geschadet, Monsieur, diese Lektion habe ich gut gelernt.";
			link.l1.go = "patria_89";
		break;
		
		case "patria_89":
			AddMoneyToCharacter(pchar, 300000); 
			TakeNItems(pchar, "chest", 5);
			dialog.text = "Ach, Vizeadmiral, ich hoffe, Sie sind nicht beleidigt über das, was in der Vergangenheit passiert ist?.. Sie sind jetzt ein Held Ihrer Nation, wussten Sie das? Wie fühlen Sie sich in dieser neuen Position? Denken Sie daran: Viele würdige Offiziere haben Jahrzehnte damit verbracht, die Rangleiter zu erklimmen, aber ohne eine erfahrene Hand... bleiben sie auf der Position des Kommandanten. Aber Sie, mein Freund, haben die einzigartige Fähigkeit, immer das Unmögliche zu schaffen! Und Sie haben einen Freund in hohen Positionen, der auch Ihr Beschützer ist, also wenn Sie in Zukunft irgendwelche Probleme haben, werde ich da sein, um Ihnen zu helfen.";
			link.l1 = "Danke für diese freundlichen Worte, Eure Exzellenz. Ich habe das Gefühl, ich habe fast alles in dieser Region erreicht. Mit Ihrer Hilfe, natürlich. Ich nehme an, jetzt kann ich in Ruhe meine eigenen Angelegenheiten klären? Ich muss an meine Familie denken.";
			link.l1.go = "patria_90";
		break;
		
		case "patria_90":
			dialog.text = "Du willst heiraten, Charles? Ah-ha-ha! Zeige auf irgendeine schöne Frau in Paris - und sie wird sofort deine sein! Aber, ach, das muss warten. Ich brauche dich hier, mein Freund, zumindest vorerst.";
			link.l1 = "Es scheint, dass Frankreich im Archipel stärker denn je ist. Eine Allianz mit den Engländern, ein Waffenstillstand mit der Gesellschaft. Es gibt keine problematischen... 'Levasseurs' mehr. Richtig?";
			link.l1.go = "patria_91";
		break;
		
		case "patria_91":
			dialog.text = "Nationen, genau wie Menschen, wünschen sich immer mehr, egal wie viel sie haben... Und wir haben tatsächlich einen neuen 'Levasseur', Vizeadmiral...";
			link.l1 = "Wirklich? Und wer ist das?";
			link.l1.go = "patria_92";
		break;
		
		case "patria_92":
			dialog.text = "Es ist unser alter gemeinsamer Bekannter, Baron Noel Forget. Erinnern Sie sich, warum er hierher gekommen ist?";
			link.l1 = "Hmm... Sie haben etwas über die Westindische Handelsgesellschaft gesagt. Hat Paris beschlossen, eine ähnliche Organisation wie die Holländer zu gründen?";
			link.l1.go = "patria_93";
		break;
		
		case "patria_93":
			dialog.text = "Genau. Ähnlich wie die niederländische Gesellschaft. Aber eine von Grund auf neu zu schaffen ist sehr schwierig. Sie sehen, Stuyvesant hatte Jahrzehnte des Handels mit verschiedenen Kontinenten in seiner Erfahrung, ein entwickeltes Netz von Agenten und eine mächtige Flotte von Handelsschiffen. Frankreich hat das nicht, und, falls Sie es nicht wussten, Charles, der König hat gerade einen ernsthaften Geldmangel. Sie wünschen, die finanzielle Situation der Metropole durch Lenkung des Handels hier zu beheben, aber sie verstehen nicht, womit wir konfrontiert werden müssen.\nDie Rivalität sowohl der Engländer als auch der Niederländer, die territorialen Ambitionen der Spanier, die Piraterie blüht wie nie zuvor. Jedes Handelsfluyts muss von einem Marineschiff eskortiert werden, oder es läuft Gefahr, niemals an seinem Bestimmungsort anzukommen. Und wir haben keine mächtige Flotte wie die Ostinder der Niederländer, oder die mächtigen Galeonen wie die der Spanier.";
			link.l1 = "Aber haben Sie all dies dem Baron erklärt? Auch über die Piraten?";
			link.l1.go = "patria_94";
		break;
		
		case "patria_94":
			dialog.text = "Natürlich habe ich das getan. Und über das Verbot der Piraten von Tortuga nach Ihrer Mission zur Entfernung von Levasseur, das die Piraten nicht vergessen haben und uns immer Groll hegen werden. Ich habe Treffen mit verschiedenen Leuten organisiert, die meine Sorgen bestätigt haben, aber leider hat das keinen Einfluss auf den Baron. Er wurde von den Ministern hierher geschickt, und er schuldet ihnen... So ist es eben.";
			link.l1 = "Hmm...";
			link.l1.go = "patria_95";
		break;
		
		case "patria_95":
			dialog.text = "Und lassen wir uns nicht verbergen, dass eine Handelsgesellschaft im Archipel, mit direkter Kontrolle aus Paris... Sie und ich, Vizeadmiral... wir brauchen es hier nicht.";
			link.l1 = "Ich verstehe.";
			link.l1.go = "patria_96";
		break;
		
		case "patria_96":
			dialog.text = "Sie sehen, mein Freund, ich bin äußerst ehrlich zu Ihnen... Also, ich hoffte von ganzem Herzen, dass Monsieur Forget seine Meinung zur Gründung dieser Handelsgesellschaft ändern würde, aber... das ist nicht passiert. Ich habe all meinen Einfluss auf den Baron verschwendet, und jetzt müssen Sie ins Spiel kommen.";
			link.l1 = "Hmm... Genau wie bei Levasseur?";
			link.l1.go = "patria_97";
		break;
		
		case "patria_97":
			dialog.text = "Oh Gott nein, wen hältst du mich für, Charles?! Der Baron ist eine einflussreiche Persönlichkeit, ein Freund des Finanzministers! Und außerdem, ihn physisch zu entfernen wird nichts erreichen: Ein neuer Politiker wird einfach aus Paris geschickt. Wir müssen die Idee, überhaupt so eine Firma zu gründen, zerstören, verstehst du, Charles? Damit der Baron nach Frankreich zurückkehrt und berichtet, dass es finanziell riskant, unsinnig wäre...";
			link.l1 = "Haben Sie eine Idee, Monsieur?";
			link.l1.go = "patria_98";
		break;
		
		case "patria_98":
			dialog.text = "Ach nein, Charles. Ich habe alles versucht. Ich habe ihm mit Mangel an Schiffen und Geld, den Holländern, Piraten... Angst gemacht. Keine Wirkung.";
			link.l1 = "Es scheint, wir brauchen etwas Ernsthafteres als bloße Worte. Hm... Piraten, sagst du?";
			link.l1.go = "patria_99";
		break;
		
		case "patria_99":
			dialog.text = "Ich sehe, du hast eine Idee, mein Freund? Ich hatte keine Zweifel. Du hast einen brillanten Geist. Überzeuge diesen Baron, und ich werde dafür sorgen, dass dein Vater genug Geld hat, um dein ganzes Haus mit Reichtümern zu füllen, die dem Louvre würdig sind. Ich verspreche es dir, Charles.";
			link.l1 = "Sehr gut, Chevalier. Die Aufgabe ist klar.";
			link.l1.go = "patria_100";
		break;
		
		case "patria_100":
			dialog.text = "Ich schwöre, Charles, du wirst es nicht bereuen, wenn du Erfolg hast. Darauf kannst du dich verlassen. Habe ich dich jemals verraten, mein Freund?";
			link.l1 = "Auf keinen Fall, Monsieur. Wo kann ich den Baron finden?";
			link.l1.go = "patria_101";
		break;
		
		case "patria_101":
			dialog.text = "Gerade jetzt ist er in Port-au-Prince. Er findet die endlosen Felder und Täler von Hispaniola sehr schön, hat er gesagt...";
			link.l1 = "Großartig. Nun, erlauben Sie mir, mich zu entschuldigen.";
			link.l1.go = "patria_102";
		break;
		
		case "patria_102":
			DialogExit();
			AddQuestRecord("Patria", "67");
			pchar.questTemp.Patria = "epizode_12_pirates";
			Patria_CondotierSail();
		break;
		
		case "patria_103":
			dialog.text = "Genau das. Der Baron hat mir alles erzählt. Nach allem, was er durchgemacht hat... Aber Sie können Dinge klar erklären, wie niemand sonst, Vizeadmiral! Das sollte ich von Ihnen lernen!";
			link.l1 = "Ich habe viel von Ihnen gelernt, Chevalier.";
			link.l1.go = "patria_104";
		break;
		
		case "patria_104":
			dialog.text = "Mein Freund, ich bin dir etwas schuldig. Ich versichere dir, dass dein lieber Vater alles haben wird, was er in seinem Leben braucht oder jemals brauchen wird, und dein Familienhaus wird das beste in der Provinz sein... und eines der besten in ganz Frankreich. Außerdem werde ich dir 100.000 Pesos zahlen - ich hoffe, das deckt deine Schulden bei den Piraten...";
			link.l1 = "Das ist schön zu hören, Monsieur!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_105add":
			AddMoneyToCharacter(pchar, 100000); 
			dialog.text = "Ich habe auch ein besonderes Geschenk für dich vorbereitet. Ich bin sicher, du wirst den Wert dieses Gegenstandes und die Aufrichtigkeit meiner Dankbarkeit für deine treuen Dienste verstehen! Also, Vizeadmiral Charles de Maure, ich übergebe dir mein persönliches Zeremonienschwert des Malteserordens! Diese kostbare Waffe wird zu deiner Uniform passen, denke ich! Wenn du dich entscheidest, nach Paris zurückzukehren, hat Baron Noel Forget versprochen, dich dem König vorzustellen - du solltest in voller Parade zu ihm kommen: in deiner Uniform und mit dieser ausgezeichneten Klinge! Noch ruhmreichere Karrieremöglichkeiten in der französischen Marine erwarten dich!";
			link.l1 = "Dieses Schwert ist unübertroffen in seiner Schönheit! Danke, Monsieur, ich verdiene diese Ehre wirklich nicht...";
			link.l1.go = "patria_105";
		break;
		
		case "patria_105":
			ref itm = ItemsFromID("blade_36");
			itm.picIndex = 16;
			itm.picTexture = "ITEMS_17";
			itm.price = 10000;
			itm.Weight = 3.0;
			itm.lenght = 1.05;
			itm.curve = 1.0;
			itm.Balance = 1.9;
			GiveItem2Character(pchar, "blade_36");
			Log_Info("You've received the Maltese Sword");
			PlaySound("interface\important_item.wav");
			dialog.text = "Du tust es! Und während du hier bist, erwarten dich große Veränderungen. Gute Veränderungen. Vizeadmiral Charles de Maure, ich ernenne dich zum Gouverneur von Saint Martin!";
			link.l1 = "Hah! Habe ich dich richtig gehört?";
			link.l1.go = "patria_106";
		break;
		
		case "patria_106":
			ChangeCharacterComplexReputation(pchar, "nobility", 12); // 14-add
			ChangeCharacterComplexReputation(pchar, "authority", 12);
			ChangeCharacterComplexReputation(pchar, "fame", 12);
			dialog.text = "Ja, mein Freund. Du bist jetzt der Gouverneur von Saint Martin, den du so sorgfältig geschützt hast.";
			link.l1 = "Chevalier, erlauben Sie mir, diese Ehre abzulehnen. Ich möchte nicht an diese eine arme Insel gebunden sein! Und all diese inländischen Probleme... Das ist nicht, was ich tun sollte!";
			link.l1.go = "patria_107";
		break;
		
		case "patria_107":
			dialog.text = "Ich akzeptiere die Ablehnung nicht. Mein Freund, hab keine Angst: Du wirst wie früher leben. Alle langweiligen Dinge werden vom aktuellen amtierenden Gouverneur erledigt. Du wirst der de facto Gouverneur sein. Charles, verstehst du nicht, warum gerade DU zum Gouverneur von Saint Martin ernannt wurdest? Jetzt ist der richtige Moment dafür, wenn niemand irgendwelche Fragen stellen wird. Ich brauche einen MEINER Männer als Gouverneur dort, verstehst du, was ich meine?";
			link.l1 = "Die Salzmine?";
			link.l1.go = "patria_108";
		break;
		
		case "patria_108":
			dialog.text = "Natürlich! Und die zweite gute Nachricht: Ab jetzt erhalten Sie am 15. jeden Monats einen Teil des Gewinns aus der Mine sowie aus Doilys Handel. Ihr passives Einkommen wird 100.000 Pesos pro Monat betragen.";
			link.l1 = "Hah! Das freut mich zu hören! Danke, Chevalier. Nun, wenn ich nicht dazu gezwungen werde, dort zu sitzen, akzeptiere ich die Gouverneurschaft. Und was, wenn ich mich entscheide, nach Frankreich zu segeln?";
			link.l1.go = "patria_109";
		break;
		
		case "patria_109":
			dialog.text = "Wenn Sie sich entscheiden - Sie werden gehen, und ich, obwohl sehr enttäuscht, werde einen Ersatz für Sie finden. Aber das ist nicht alles. Ich habe hier einen Brief von Ihrem Vater. Schauen Sie mal.";
			link.l1 = "Von meinem Vater? Ich bin begeistert!.. Sehr gut, Monsieur, abgemacht. Darf ich jetzt gehen? Ich möchte den Brief lesen... Keine neuen Aufgaben für mich?";
			link.l1.go = "patria_110";
		break;
		
		case "patria_110":
			dialog.text = "Nicht jetzt, Gouverneur, aber wenn ich etwas Arbeit finde, weiß ich, wie ich Sie finden kann. Viel Glück, Charles!";
			link.l1 = "Und Ihnen, Chevalier!";
			if (pchar.questTemp.Patria == "epizode_12_baronwin") link.l1.go = "patria_119";
			else link.l1.go = "patria_111";
		break;
		
		case "patria_111":
			DialogExit();
			AddQuestRecord("Patria", "77");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_112":
			dialog.text = "Verdammt noch mal, was für ein Desaster! Jetzt haben wir noch mehr Probleme zu bewältigen. Bist du dafür verantwortlich, Charles? Sag mir die Wahrheit. War das ein Unfall?";
			link.l1 = "Nun, etwas ist schief gelaufen...";
			link.l1.go = "patria_113";
		break;
		
		case "patria_x112":
			dialog.text = "Verdammt noch mal, was für eine Katastrophe! Jetzt haben wir noch mehr Probleme zu bewältigen. Der Baron hat einen sehr schlechten Ort zum Sterben gewählt! Sind Sie sicher, dass Sie ihm nicht geholfen haben, von dieser Welt zu scheiden?";
			link.l1 = "Was sagen Sie, Chevalier?! Natürlich nicht!";
			link.l1.go = "patria_x113";
		break;
		
		case "patria_y112":
			dialog.text = "Verdammt nochmal, was für ein Desaster! Jetzt haben wir noch mehr Probleme zu bewältigen. Bist du sicher, dass du ihm nicht geholfen hast, diese Welt zu verlassen?";
			link.l1 = "Was sagen Sie, Chevalier?! Natürlich nicht!";
			link.l1.go = "patria_y113";
		break;
		
		case "patria_x113":
			dialog.text = "In Ordnung. Nun, mein Freund, vielleicht ist nicht alles ruiniert. Ein Fieber ist ein Fieber, richtig? Und bis ein neuer Inspektor vom Ministerium angekommen ist, werden wir hier das Durcheinander beseitigen und gut bewaffnet auf unsere Gäste warten... Und jetzt, Charles, müssen wir alle unsere Kontakte schließen. Ich hoffe, du verstehst warum?";
			link.l1 = "Natürlich.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_y113":
			dialog.text = "In Ordnung. Nun, mein Freund, vielleicht ist nicht alles verloren. Schlachten in der Karibik sind zu erwarten, nicht wahr? Und bis ein neuer Inspektor vom Ministerium eingetroffen ist, werden wir hier das Chaos beseitigen und gut bewaffnet auf unsere Gäste warten... Und jetzt, Charles, müssen wir alle unsere Kontakte abbrechen. Ich hoffe, du verstehst warum?";
			link.l1 = "Natürlich.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_113":
			dialog.text = "In Ordnung. Nun, mein Freund, vielleicht ist nicht alles verloren. Piraten sind Piraten, nicht wahr? Und bis ein neuer Inspektor aus dem Ministerium eingetroffen ist, werden wir hier das Durcheinander aufräumen und gut bewaffnet auf unsere Gäste warten... Und jetzt, Charles, müssen wir all unsere Kontakte abbrechen. Ich hoffe, du verstehst warum?";
			link.l1 = "Natürlich.";
			link.l1.go = "patria_114";
		break;
		
		case "patria_114":
			dialog.text = "Auf jeden Fall, mein Freund, du hast alles getan, was du konntest. Und das ist besser als nichts. Ich bin froh, dass das Schicksal uns zusammengebracht hat. Du darfst deine Position behalten, und ich bin sicher, in Frankreich erwartet dich eine großartige Karriere. Und, ich denke, es ist an der Zeit, dass du nach Paris zurückkehrst. Hier, ein Brief von deinem Vater. Nimm ihn.";
			link.l1 = "Mein Vater? Das ist äußerst willkommen!.. Also gut, Monsieur, ich verstehe. Keine Kontakte, volle Geheimhaltung und sobald ich kann - ab nach Paris. Darf ich jetzt gehen? Ich möchte den Brief lesen...";
			link.l1.go = "patria_115";
		break;
		
		case "patria_115":
			dialog.text = "Geh, Charles. Viel Glück!";
			link.l1 = "Und Ihnen, Chevalier!";
			link.l1.go = "patria_116";
		break;
		
		case "patria_116":
			DialogExit();
			AddQuestRecord("Patria", "78");
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			pchar.questTemp.Patria = "end"; // конец линейки
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			sld = CharacterFromID(pchar.questTemp.Patria.SpanishID);
			SetCharacterRemovable(sld, true);
		break;
		
		case "patria_117":
			dialog.text = "Genau. Sie können Dinge klar erklären wie kein anderer, Vizeadmiral! Das sollte ich von Ihnen lernen!!";
			link.l1 = "Ich habe viel von Ihnen gelernt, Chevalier.";
			link.l1.go = "patria_118";
		break;
		
		case "patria_118":
			dialog.text = "Mein Freund, ich bin dir zu Dank verpflichtet. Ich versichere dir, dass dein lieber Vater alles haben wird, was er im Leben braucht oder jemals brauchen wird, und dein Familienhaus wird das beste in der Provinz sein... und eines der besten in ganz Frankreich. Außerdem werde ich dir 100.000 Pesos zahlen - ich hoffe, das deckt deine Reisekosten und ermöglicht dir etwas wohlverdiente Ruhe.";
			link.l1 = "Das ist schön zu hören, Monsieur!";
			link.l1.go = "patria_105add";
		break;
		
		case "patria_119":
			DialogExit();
			AddQuestRecord("Patria", "87");
			pchar.questTemp.Patria = "europe";
			pchar.questTemp.Patria.Governor = "true"; // Шарль губернатор
			AddQuestRecordInfo("Sharlie_Father_1", "1");
			SetFunctionTimerCondition("Patria_EuropeTime", 0, 0, 175+rand(10), false); // таймер
		break;
		
		case "patria_prison":
			dialog.text = "Wie konntest du nur, Charles! Wie konntest du mir das antun?!";
			link.l1 = "Ähem...";
			link.l1.go = "patria_prison_1";
		break;
		
		case "patria_prison_1":
			dialog.text = "Ich weiß, dass du es warst! Du hast das getan! Leugne es nicht! Ohne deine Hilfe hätte Baron Forget weder die Berichte vom Minenmanager, noch den Standort der Mine, noch die Dokumente von Peter Stuyvesant bekommen. Dein Name wurde dort nicht gehört, aber lass mich dir sagen, ich weiß es genau: du warst es. Warum, Charles?.. Antworte mir einfach... Warum? Michel? Eine Million Pesos? Levasseur? Oder vielleicht die Position des Generalgouverneurs?";
			// belamour legendary edition -->
			link.l1 = "Erinnern Sie sich an unser erstes Treffen, Chevalier? Wie Sie mich in meine Schranken gewiesen haben? Wie Sie mir eine Million Pesos abgepresst haben? Ich wünschte nur, dass wir eines Tages die Rollen tauschen könnten. Ich habe Ihnen nichts mehr zu sagen.";
			link.l1.go = "patria_prison_2";
			link.l2 = "Für Levasseur. Eine Schuld von einer Million, das kann ich noch verstehen. Ich habe gearbeitet, getötet, verdient, geraubt, aber ich habe dir für all den Schaden entschädigt. Und das war dir nicht genug. Du Chevalier hast mich auf eine Selbstmordmission gegen die Krone geschickt, damit ich deine persönliche Macht weiter stärken kann! Dein Verrat verlangte eine Antwort. Und du hast sie bekommen!";
			link.l2.go = "patria_prison_2";
			link.l3 = "Ehrgeiz, Chevalier. In dieser seltsamen neuen Welt hatte ich fast alles erreicht, was ich konnte. Das Amt des Generalgouverneurs schien mir ein bemerkenswertes Ziel zu sein. Ich habe viel von Ihnen gelernt. Auf Wiedersehen!";
			link.l3.go = "patria_prison_2";
			link.l4 = "Ich weiß es selbst nicht, um ehrlich zu sein. Vielleicht weil ich vom Baron und seinem treuen Dienst an unserem Land beeindruckt bin? Auf jeden Fall haben Sie jetzt genug Zeit, über dieses Problem für mich nachzudenken. Auf Wiedersehen!";
			link.l4.go = "patria_prison_2";
			// <-- legendary edition
		break;
		
		case "patria_prison_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			SetFunctionTimerCondition("Patria_EuropePuancieClear", 0, 0, 5, false); // таймер
			pchar.quest.Patria_Europe_final.win_condition.l1 = "location";
			pchar.quest.Patria_Europe_final.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Europe_final.function = "Patria_EuropeFinal";
		break;
		
		case "patria_patentfail":
			DialogExit();
			pchar.questTemp.Patria = "fail";
			CloseQuestHeader("Patria");
			DeleteAttribute(pchar, "questTemp.GoldenGirl_Block");	// Разрешаем квест Дороже Золота
			// убрать Эклятон, если есть
			if (CheckAttribute(pchar, "questTemp.Patria.Ecliaton"))
			{
				sld = characterFromId("Ecliaton_Cap");
				RemoveCharacterCompanion(pchar, sld);
				sld.lifeday = 0;
				DeleteAttribute(pchar, "questTemp.Patria.Ecliaton");
			}
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ1":
			SetTimerCondition("PZ_NormanBackToStreets", 0, 0, 1, false);	//Вовзращаем Акулу или Тиракса в Шарптаун
			// ставим сразу прерывание, чтобы потом по тысячу раз не копировать
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang") || CheckAttribute(pchar, "questTemp.PZ.LongwayTorero") || CheckAttribute(pchar, "questTemp.PZ.LongwayElCasador"))
				{
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1 = "location";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition.l1.location = "Charles_town";
					PChar.quest.PZ_AfterPoincyLongwayDialog.win_condition = "PZ_AfterPoincyLongwayDialog";
				}
			}
			
			if (!CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva")) 
			{
				dialog.text = "Gut dich zu sehen, Charles. Ich habe von deinen Heldentaten gehört. Brillante Arbeit!";
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Das ist noch nicht alles, Eure Exzellenz.";
					link.l1.go = "PZ2";
				}
				else
				{
					link.l1 = "Kann ich von Ihnen eine schriftliche Anordnung erhalten, dass mein Bruder jetzt aus der Haft entlassen wird?";
					link.l1.go = "serve";
				}
			}
			else 
			{
				dialog.text = "Greetings, Charles. Come in; I've already been informed.";
				link.l1 = "Unterrichtet? Es könnte ein Missverständnis geben, Eure Exzellenz. Ich kam, um den erfolgreichen Abschluss Ihrer Mission zu melden, aber ich sehe, Sie sind nicht in bester Laune.";
				link.l1.go = "PZ_PoincyAngry1";
			}
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.PZ_LongwayNelzyaOtdatArube");
		break;
					
		case "PZ2":
			dialog.text = "Ist das so? Was meinen Sie damit, Kapitän?";
			link.l1 = "Ich habe es geschafft, Levasseur lebend zu fangen und zu Ihnen zu bringen. Sobald wir fertig sind, werde ich den Befehl geben, ihn zu Ihnen zu bringen.";
			link.l1.go = "PZ3";
		break;
		
		case "PZ3":
			dialog.text = "Ich hätte nie gedacht, dass so etwas überhaupt möglich ist! Wirklich brillante Arbeit, Charles! Ich bezweifle, dass selbst dein illustrierter Bruder es besser hätte machen können. Dein Vater wäre stolz auf dich, mein Freund.";
			link.l1 = "Danke für Ihre freundlichen Worte, Monsieur Philippe.";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "PZ5":
			dialog.text = "Sehr gut, Charles. Ich bin zufrieden mit dir.";
			link.l1 = "Kann ich von Ihnen eine schriftliche Anordnung erhalten, dass mein Bruder nun aus der Haft entlassen wird?";
			link.l1.go = "serve";
			LAi_SetHuberType(npchar);
		break;
		
		case "PZ_PoincyAngry1":
			dialog.text = "Vielleicht hätte ich bedenken sollen, dass du nicht dein Bruder bist - kein Militär, kein Geheimagent und noch nicht erfahren in heiklen Operationen. Du hättest nicht offen in den Straßen von Tortuga gegen Soldaten kämpfen sollen. Es wird Untersuchungen geben, und auch über mich. Von seriösen Leuten, wie du verstehst.";
			link.l1 = "Verzeihen Sie mir, Chevalier. Wie Sie wissen, hätte Levasseur nicht ohne Kampf nachgegeben.";
			link.l1.go = "PZ_PoincyAngry2";
		break;
		
		case "PZ_PoincyAngry2":
			dialog.text = "Wahrlich, aber... egal. Nicht schlecht für eine erste Operation. Ich werde berichten, dass er den königlichen Prüfer und seine Eskorte während einer offiziellen Inspektion angegriffen hat.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
			{
				link.l1 = "Eure Exzellenz, wenn es hilft, kann ich Ihnen Levasseur bringen. Meine Männer und ich hatten das Glück, ihn an einem abgelegenen Ort zu fangen, nachdem seine Handlanger versucht hatten, uns auf den Straßen zu verhaften.";
				link.l1.go = "PZ_PoincyAngry3";
			}
			else
			{
				link.l1 = "Kann ich von Ihnen eine schriftliche Anordnung erhalten, dass mein Bruder jetzt aus der Haft entlassen wird?";
				link.l1.go = "serve";
			}
		break;
				
		case "PZ_PoincyAngry3":
			dialog.text = "Was hast du gesagt, Charles? Sag das noch einmal.";
			link.l1 = "François Levasseur befindet sich gerade in meinem Gewahrsam, bereit, Ihnen übergeben zu werden, Monsieur Philippe.";
			link.l1.go = "PZ_PoincyAngry4";
		break;
		
		case "PZ_PoincyAngry4":
			dialog.text = "Vergiss alles, was ich vorher gesagt habe. Ich habe definitiv überreagiert. Hervorragende Arbeit. Ich bin mir nicht sicher, ob selbst dein illustrierter Bruder das hätte schaffen können.";
			link.l1 = "Danke, Chevalier.";
			link.l1.go = "PZ_PoincyAngry5";
		break;
		
		case "PZ_PoincyAngry5":
			dialog.text = "Sie haben großes Potenzial, mein Freund. Ich wünschte, Ihre Talente würden öfter zum Wohle des Landes genutzt. Aber bitte, versuchen Sie ab jetzt... diskreter zu sein. Unsere Arbeit erfordert normalerweise einen feinfühligen Ansatz. Oh ja, und noch eine Sache.";
			link.l1 = "Ja, Euer Herrlichkeit?";
			link.l1.go = "exit";
			npchar.greeting = "";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
