// Альберт Локсли - адвокат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
    string sTemp, attrLoc;
	
    attrLoc = Dialog.CurrentNode;
	int iSumm = 0;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	if (findsubstr(attrLoc, "RelationTo_" , 0) != -1)
	{
		i = findsubstr(attrLoc, "_" , 0);
		npchar.quest.relation = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
			Dialog.CurrentNode = "RelationYet";
		}
		else
		{
			Dialog.CurrentNode = "RelationAny_Done";
			npchar.quest.relation.summ = CalculateRelationLoyerSum(sti(npchar.quest.relation));
		}
	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Mein Name ist Albert Loxley und ich bin Rechtsanwalt. Ich vertrete die Interessen meiner Klienten in Prozessen. Meine Dienstleistungen sind teuer, aber sie sind es wert, das kann ich Ihnen versichern.";
				if(SandBoxMode)
				{					
					if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
					{
						link.l1 = "Ich habe Ärger mit den englischen Behörden.";
						link.l1.go = "RelationTo_0";
					}
					
					if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
					{
						link.l2 = "Ich habe Ärger mit den französischen Behörden.";
						link.l2.go = "RelationTo_1";
					}
					if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
					{
						link.l3 = "Ich habe Ärger mit den spanischen Behörden.";
						link.l3.go = "RelationTo_2";
					}

					if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
					{
						link.l4 = "Ich habe Ärger mit den niederländischen Behörden.";
						link.l4.go = "RelationTo_3";
					}
					if (ChangeContrabandRelation(pchar, 0) <= 5)
					{
						Link.l5 = "Ich habe mich mit den Schmugglern gestritten.";
						Link.l5.go = "contraband";
					}
					Link.l7 = "Danke, aber glücklicherweise benötige ich bisher die Dienste eines Anwalts nicht.";
					Link.l7.go = "exit";
					NextDiag.TempNode = "Loxly";
					npchar.quest.meeting = "1";
				}
				link.l1 = "Danke, aber glücklicherweise brauche ich bisher keine Dienste eines Anwalts.";
				link.l1.go = "exit";
				npchar.quest.meeting = "1";
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "loxly")
				{
					link.l1 = "Ich benötige Ihre Dienste. Ich bin ein bevollmächtigter Vertreter einer jungen Dame namens Helen McArthur, sie ist die Enkelin des berühmten Nicolas Sharp. Sie ist die einzige gesetzliche Erbin nach dem Tod ihrer Mutter und ihres Onkels. Sie hat laut dem Testament ihres Onkels alle Rechte an Isla Tesoro. Wie viel würden Sie verlangen, um Helen dabei zu helfen, die rechtmäßige Herrin der Insel zu werden?";
					link.l1.go = "saga";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga"))
				{
					if (pchar.questTemp.Saga == "loxly") // первое обращение по саге
					{
						dialog.text = "Brauchen Sie meine Dienste, Mister? Sie werden zufrieden sein, das kann ich Ihnen versichern.";
						link.l1 = "Ja, ich brauche sie. Ich bin ein bevollmächtigter Vertreter einer jungen Dame namens Helen McArthur, sie ist die Enkelin des berühmten Nicolas Sharp. Sie ist die einzige gesetzliche Erbin nach dem Tod ihrer Mutter und ihres Onkels. Sie hat alle Rechte an Isla Tesoro laut dem Testament ihres Onkels. Wie viel würdest du für die Hilfe verlangen, damit Helen die rechtmäßige Herrin der Insel wird?";
						link.l1.go = "saga";
						break;
					}
					if (pchar.questTemp.Saga == "bakaut")
					{
						dialog.text = "Mister, ich bin noch nicht mit den Materialien Ihres Geschäfts vertraut. Bitte kommen Sie später zu mir, wie ich Ihnen bereits gesagt habe.";
						link.l1 = "Gut.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "molligan" || pchar.questTemp.Saga == "sellbakaut")
					{ // если не выполнил до конца квест по бакауту
						dialog.text = "Mister, leider brauche ich noch mehr Zeit, um alle notwendigen Unterlagen im Archiv zu sammeln. Ich bin noch nicht fertig. Bitte besuchen Sie mich später.";
						link.l1 = "Gut.";
						link.l1.go = "exit";
						break;
					}
					if (pchar.questTemp.Saga == "removebakaut") // с бакаутом разобрались
					{
						// четвертая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							RemoveItems(pchar, "map_sharp_full", 1);
							dialog.text = "Mister, warum haben Sie so langsam gearbeitet?! Es ist vorbei für Ihren Auftraggeber. Die Frist zur Bestätigung des Testaments ist abgelaufen und Isla Tesoro gehört nun England. Es wird bald zu einem Militärstützpunkt werden.";
							link.l1 = "Wow! Es scheint, dass all meine Bemühungen umsonst waren...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "Ach, da sind Sie ja, Mister. Ich habe mich mit den Materialien vertraut gemacht, daher ist es Zeit für eine Vorauszahlung. Haben Sie die Dublonen mitgebracht?";
							if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) {n = 1000;}
							else {n = 450;}
							if (PCharDublonsTotal() >= n)
							{
								link.l1 = "Ja, das habe ich. Hier sind eure Dublonen.";
								link.l1.go = "saga_5";
							}
							else
							{
								link.l1 = "Verzeihen Sie mir mein schlechtes Gedächtnis, ich habe sie in einer Truhe auf meinem Schiff gelassen. Ich werde sie sofort bringen.";
								link.l1.go = "exit";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "shadow")
					{
						// пятая проверка времени
						if (CheckAttribute(pchar, "questTemp.Saga.Late"))
						{
							dialog.text = "Mister, warum haben Sie so langsam gearbeitet?! Es ist vorbei für Ihren Auftraggeber. Die Frist zur Bestätigung des Testaments ist abgelaufen und Isla Tesoro gehört nun England. Es wird bald zu einem Militärstützpunkt werden.";
							link.l1 = "Wow! Es scheint, dass all meine Anstrengungen umsonst waren...";
							link.l1.go = "saga_l3";
						}
						else
						{
							dialog.text = "Mister, konnten Sie etwas finden, das die Abstammung Ihres Prinzipals beweisen kann?";
							if (!CheckCharacterItem(pchar, "Letter_beatriss"))
							{
								link.l1 = "Noch nicht. Aber ich arbeite daran.";
								link.l1.go = "exit";
							}
							else
							{
								link.l1 = "Ja. Ich habe wirklich ausführliche Beweise.";
								link.l1.go = "saga_14";
							}
						}
						break;
					}
					if (pchar.questTemp.Saga == "court" && GetNpcQuestPastDayParam(npchar, "court_date") >= 1 && IsOfficer(characterFromId("Helena")))
					{
						 // запрет сохранения чтобы ленку не заграбастали себе умники всякие с ГК-  лесник
						InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться																																			   
						dialog.text = "A-ah, hier sind Sie, Mister. Froh, Sie zu sehen. Ich muss zugeben, ich habe schon eine ganze Weile auf Sie gewartet. Ist das Ihr Auftraggeber?";
						link.l1 = "Ja. Lassen Sie mich Ihnen Helen McArthur vorstellen.";
						link.l1.go = "saga_26";
						break;
					}
					dialog.text = "Brauchen Sie meine Dienste, Mister? Sie werden zufrieden sein, das kann ich Ihnen versichern.";
					link.l1 = "Danke, aber ich brauche sie momentan nicht.";
					link.l1.go = "exit";
				}
				if (CheckAttribute(npchar, "quest.waitgold"))
				{
					dialog.text = "Guten Tag, Mister. Ich nehme an, dass Sie meine Gebühr mitgebracht haben?";
					if (PCharDublonsTotal() >= 450)
					{
						link.l1 = "Ja, habe ich. Hier sind eure Dublonen.";
						link.l1.go = "saga_36";
					}
					link.l2 = "So viel sei gesagt, Mister Loxley, ich dachte... Meine Meinung ist, dass 900 Dublonen mehr als genug für Ihre Arbeit sind.";
					link.l2.go = "saga_38";
					link.l3 = "Ich erinnere mich, Mister Loxley. Ich bringe es etwas später...";
					link.l3.go = "exit";
					break;
				}
				dialog.text = "Brauchen Sie meine Dienste, Mister? Sie werden zufrieden sein, das kann ich Ihnen versichern.";
				link.l1 = "Danke, aber ich brauche sie momentan nicht.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "saga":
			// третья проверка времени. Отбираем Элен, чистим квестовый лут, даем флаг на Свенсона, вызываем перемены
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				RemoveItems(pchar, "map_sharp_full", 1);
				dialog.text = "Mister, Sie müssen zu lange auf See gewesen sein. Isla Tesoro ist jetzt eine Militärbasis der englischen Marine! Ja, Sharps Testament existiert, aber es ist abgelaufen und Isla Tesoro ist Eigentum der englischen Krone geworden.";
				link.l1 = "Toll! Es scheint, dass all meine Bemühungen umsonst waren...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "Die Dame behauptet, sie besitzt die ganze Insel? Hm... Es scheint, dass dies keine leichte Angelegenheit sein wird. Isla Tesoro ist fast schon eine englische Kolonie...";
				link.l1 = "Noch nicht. Laut Testament wird der Mann oder die Frau, der oder die beide Teile der Karte vorzeigt, zum Besitzer von Isla Tesoro. Wir haben beide Teile von Sharps Karte, die der Hauptbeweis für das Erbe ist.";
				link.l1.go = "saga_1";
			}
		break;
		
		case "saga_1":
			dialog.text = "Nicolas Sharp... Nun, nun. Ich muss ein Archiv besuchen und mich mit Materialien vertraut machen, die für Isla Tesoro relevant sind. Habt Ihr die Karte bei euch?";
			link.l1 = "Habe ich, aber ich werde es Ihnen nur geben, nachdem wir einen Vertrag unterzeichnet haben. Also, wie steht es um den Preis für Ihre Dienste?";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			sTemp = "";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = " Auch Ihr geschätztes Engagement wird nicht unbemerkt bleiben. Cartagena... Es wird Fragen geben.";
			dialog.text = "Wie ich gesagt habe - es wird nicht einfach sein. Sie müssen das Eigentumsrecht für eine ganze Insel beweisen, nicht für irgendeine alte Wanne oder eine Hütte. Außerdem war Nicolas Sharp ein Pirat und Piraten oder ihren Verwandten zu helfen, ist teuer."+sTemp;
			link.l1 = "Werden Sie mir nun eine tatsächliche Summe nennen?";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			sTemp = "Vierhundertfünfzig";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "Eintausend";
			dialog.text = "Mister, die endgültige Summe wird während des Prozesses gebildet. Ich weiß noch nicht, wie problematisch es sein wird. Aber ich bin bereit, einen Vorschuss zu schätzen - "+sTemp+" Dublonen. Diese Menge Gold muss je nach Geschäftslage ein oder zwei Mal wieder bezahlt werden.\nBringen Sie mir das Geld in einer Woche, ich brauche Zeit, um die Archive zu überprüfen und mich vorzubereiten. Dann werden wir eine Vereinbarung treffen. Abgemacht?";
			link.l1 = "Sie haben Sie als den besten Anwalt im Archipel empfohlen, also haben wir einen Deal. Bis in einer Woche!";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			DialogExit();
			pchar.questTemp.Saga = "bakaut"; // обновляем флаг
			AddQuestRecord("Testament", "2");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) AddQuestUserData("Testament", "sMoney", "1000");
			else AddQuestUserData("Testament", "sMoney", "450");
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				bDisableFastReload = true;
				SetFunctionLocationCondition("HelenDrinking_PortRoyalDialog", "PortRoyal_town", false);
			}
		break;
		
		case "saga_5":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold"))
			{
				RemoveDublonsFromPCharTotal(1000);
				//Log_Info("You have given 1450 doubloons");
			}
			else
			{
				RemoveDublonsFromPCharTotal(450);
				//Log_Info("You have given 450 doubloons");
			}
			PlaySound("interface\important_item.wav");
			dialog.text = "Sehr gut. Ich bin bereit, Ihren Fall zu übernehmen und Ihre Interessen vor Gericht zu vertreten. Jetzt kommen wir zur Sache. Ich habe gute Arbeit in den Archiven geleistet und mit wichtigen Leuten gesprochen. Der Fall von Sharps Erbe wird nicht einfach sein. Es ist gut, dass Sie beide Teile der Karte erworben haben. Aber das könnte nicht genug sein.\nOberst Doyle hat große Pläne für Isla Tesoro, da er es nicht geschafft hat, die Kontrolle über Tortuga zu übernehmen. Es hat natürliche Verteidigungsanlagen und könnte als zukünftige Militärbasis in dieser Gegend dienen.";
			link.l1 = "Aber Helen hat laut englischem Recht alle Rechte an der Insel!";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Vielleicht wissen Sie es nicht, aber der verstorbene Sharp hat eine Ergänzung zu seinem Testament gemacht. Ein Erbe oder Erben müssen seinen Nachnamen tragen. Und soweit ich mich erinnere, hat Ihr Mädchen einen anderen Nachnamen. Sie haben gesagt, es war McArthur, richtig?";
			link.l1 = "Dies ist der Nachname ihres Stiefvaters, aber Helen hat alle Rechte, Sharp als ihren Nachnamen zu führen, weil sie eine Tochter der verstorbenen Beatrice Sharp ist, die Tochter von Nicolas.";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Prächtig! Aber wer kann das unter Eid bestätigen? Kannten Helenas Pflegeeltern Beatrice Sharp?";
			link.l1 = "Soweit ich verstehe, taten sie es nicht. Mister McArthur hielt sie für die Tochter von Gladys und Gladys kannte nur den Vater des Mädchens.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "Das ist bedauerlich. Sehen Sie, ich habe keine Erwähnung in den Archiven gefunden, dass Beatrice Sharp jemals Nachkommen hatte. Es besteht die Möglichkeit, dass es überhaupt keine offizielle Notiz über die Geburt des Kindes gibt. Jeder kann sich als Enkel von Sharp bezeichnen und das Recht beanspruchen, seinen Nachnamen zu tragen.";
			link.l1 = "Aber nur Helen hat die komplette Karte!";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Das ist ihr Trumpf und vielleicht würde es ausreichen, wenn die örtlichen Behörden nicht ihre eigenen Pläne für Isla Tesoro hätten. Ein Dokument mit der Handschrift von Beatrice und ihrer Unterschrift darunter befindet sich im Archiv. Wir müssen irgendein von ihr geschriebenes Dokument finden, das die Geburt ihrer Tochter beweist, die Tochter, die an diese Gladys... eh, wie war ihr Nachname?";
			link.l1 = "Chandler. Gladys Chandler aus Belize.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			dialog.text = "Genau. Haben Sie die Möglichkeit, so etwas zu finden?";
			link.l1 = "Ich bezweifle es. Zu viele Jahre sind vergangen. Der Legende nach könnte Kapitän Butcher selbst Helenas Vater sein. Vielleicht kann uns der ehemalige Henker von St. John's etwas darüber erzählen. Er war der letzte Mann, der ihren Vater lebend gesehen hat.";
			link.l1.go = "saga_11";
		break;
		
		case "saga_11":
			dialog.text = "Hm. Er war wirklich ein unterhaltsamer Mann. Soweit ich mich erinnere, war sein Name Raymond Baker. Ich hatte das Glück, einmal mit ihm zu plaudern. Er ist ein kluger und gut gebildeter Mann. Nun, versuche etwas auf Antigua zu finden und ich werde meine Suche in den Archiven fortsetzen, vielleicht finde ich etwas Nützliches.";
			link.l1 = "Gut. Passt für mich.";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "Geben Sie mir die Karte von Sharp und macht schnell, spricht mit Baker, vielleicht können Sie mit seiner Hilfe einige Dokumente finden. Vielleicht finden Sie sogar einen Beweis für ihre Geburt.";
			link.l1 = "Eh, ich wünschte, ich könnte. Gut, wir sehen uns, Mister Loxley.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			DialogExit();
			RemoveItems(pchar, "map_sharp_full", 1);
			pchar.questTemp.Saga = "shadow";
			pchar.questTemp.Saga.Shadows = "sentjons";
			AddQuestRecord("Shadows", "1");
		break;
		
		case "saga_14":
			dialog.text = "Ist das so? Lass uns diese Beweise mal ansehen.";
			link.l1 = "Das ist ein privater Brief, den Beatrice Sharp an ihren Bruder geschrieben hat. Hier steht, dass sie eine Tochter zur Welt gebracht hat und dass ihr Vater tatsächlich Lawrence Beltrope war. Das Mädchen wurde an eine junge Witwe namens Gladys Chandler geschickt. Lawrence Beltrope ist auch bekannt als Kapitän Butcher. Hier, nehmen Sie den Brief...";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			RemoveItems(pchar, "Letter_beatriss", 1);
			dialog.text = "";
			link.l1 = "Gladys ist bereit, dies unter Eid zu bestätigen. Sie ist auch bereit zu bestätigen, dass der Vater sich als Kapitän Butcher vorgestellt hat.";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) // Белтроп убит
			{
				dialog.text = "Wartet mal! Kapitän Butcher, der böse Pirat und Mörder englischer Untertanen, wurde vor zwanzig Jahren im Fort von St. Johannis gehängt. Und Lawrence Beltrope, ein enger Freund von Richard Doyle, ist vor kurzem tragisch gestorben. Und vor allem wollte Doyle ihn zum neuen Gouverneur von Sharptown machen!";
				link.l1 = "Ha! Sicher, das weiß niemand... Ich habe eine schriftliche Aussage von Raymond Baker, dem ehemaligen Henker von St. John's, dass er unter Androhung des sicheren Todes gezwungen wurde, die Hinrichtung von Butcher zu fälschen! Hier, schauen Sie mal...";
				link.l1.go = "saga_17";
			}
			else
			{
				dialog.text = "Wartet mal! Kapitän Butcher, der böse Pirat und Mörder englischer Untertanen, wurde vor zwanzig Jahren in der Festung von St. John's gehängt. Und Lawrence Beltrope lebt und wohnt in einer der besten Villen von Port Royal. Und vor allem will Doyle ihn zum neuen Gouverneur von Sharptown machen!";
				link.l1 = "Ha! Sicher, das weiß niemand... Ich habe eine schriftliche Aussage von Raymond Baker, dem ehemaligen Henker von St. John's, dass er unter Androhung des sicheren Todes gezwungen wurde, Butchers Hinrichtung zu fälschen! Hier, werfen Sie einen Blick darauf...";
				link.l1.go = "saga_17";
			}
		break;
		
		case "saga_17":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "Hm. Nun, nun...";
			link.l1 = "Ist das nicht sehr geschickt? Kapitän Butcher hat es geschafft, am Leben zu bleiben und ist nach England zurückgekehrt. Er hat seinen Namen wieder in Lawrence Beltrope geändert und ist hier unbemerkt zurückgekehrt.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "saga_18";
			else link.l1.go = "saga_22";
		break;
		
		case "saga_18":
			dialog.text = "Aber das... Das ändert alles! Die Veröffentlichung von Beatrices Brief wird zeigen, dass der Militärgouverneur die ganze Zeit über den flüchtigen Piraten Butcher versteckt hat, der bei Sicht verhaftet und für seine vergangenen Verbrechen vor Gericht gestellt hätte werden sollen! \nUnd Bakers Zeugenaussage wird jegliche Gründe dagegen vollständig zerstören! Das ist großartig! Mit einem solchen Ass in der Hand werden wir Doyle fair und eckig schlagen!";
			link.l1 = "Dann bin ich froh. Ich verlasse mich auf Sie in diesen Prozess. Sagen Sie mir auch wie Lawrence Beltrope gestorben ist?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "Das ist eine gruselige Geschichte, Mister. Er wurde in seinem eigenen Schlafzimmer mit einem verzerrten Gesicht gefunden. Es ist zu schwer vorzustellen, was diesen furchtlosen Mann so sehr erschreckt haben könnte. Sie sagen, er sei von Raureif bedeckt gewesen. Sein Körper war voller furchteinflößender, zerfetzter Wunden, aber kein einziger Blutstropfen auf dem Boden! Stellen Sie sich das vor! Kein einziger Tropfen!";
			link.l1 = "Ja, das scheint direkt aus einem Albtraum zu kommen. Es scheint, dass er ermordet wurde... Aber wer könnte das getan haben?";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "Es ist unbekannt. Es ist zu verworren... Der Garnisonsarzt sagte, dass seine Wunden nicht tödlich waren. Beltrope starb vor Angst, Schmerz oder etwas anderem. Auf jeden Fall ist dies ein mystischer Tod.";
			link.l1 = "Ich verstehe... Und wann beginnt der Prozess?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "Alles hängt von Ihnen ab, Mister. Ich reiche alle Unterlagen beim Gericht ein, sobald Sie mir den zweiten Teil meines Honorars - 450 Dublonen - bezahlen. Helen erhält ihre Rechte eine Woche danach.";
			if (PCharDublonsTotal() >= 450)
			{
				link.l1 = "Sehr gut. Hier sind eure Dublonen.";
				link.l1.go = "saga_24";
			}
			else
			{
				link.l1 = "Ja, sicher. Ich werde Ihnen die Summe bringen, die Sie benötigen.";
				link.l1.go = "exit";
				NextDiag.TempNode = "saga_23";
			}
		break;
		
		case "saga_23":
			// шестая проверка времени
			if (CheckAttribute(pchar, "questTemp.Saga.Late"))
			{
				dialog.text = "Mister, Sie haben mich erschüttert! Sie haben so viel getan, die Insel war fast in unseren Händen, aber jetzt ist es vorbei wegen Ihrer Verzögerung mit meinem Honorar! Das Testament ist abgelaufen und Isla Tesoro gehört jetzt der englischen Krone. Es wird eine Militärbasis sein.";
				link.l1 = "Wow! Es scheint, dass all meine Bemühungen umsonst waren...";
				link.l1.go = "saga_l3";
			}
			else
			{
				dialog.text = "Haben Sie den zweiten Teil meiner Gebühr mitgebracht, Mister?";
				if (PCharDublonsTotal() >= 450)
				{
					link.l1 = "Ja, sicher. Hier sind eure Dublonen.";
					link.l1.go = "saga_24";
				}
				else
				{
					link.l1 = "Verzeihen Sie mein schlechtes Gedächtnis, ich habe sie in einer Truhe auf meinem Schiff gelassen. Ich werde sie sofort bringen.";
					link.l1.go = "exit";
					NextDiag.TempNode = "saga_23";
				}
			}
		break;
		
		case "saga_22":
			dialog.text = "Aber das... das ändert alles! Die Veröffentlichung von Beatrices Brief wird bedeuten, dass Lawrence Beltrope sofort verhaftet und vor Gericht gestellt werden muss für seine vergangenen Verbrechen!\nUnd Bakers Zeugenaussage wird jegliche Gründe dagegen völlig zerstören! Das ist großartig! Mit solch einem Ass im Ärmel werden wir Doyle fair und quadratisch schlagen!";
			link.l1 = "Dann bin ich froh. Wann beginnt der Prozess?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_24":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ausgezeichnet, Mister. Es war mir ein Vergnügen, Geschäfte mit Ihnen zu machen. Nun, hier ist der Deal. Kommen Sie morgen wieder hierher. Ja-ja, Sie haben richtig gehört - morgen! Schließlich bin ich der beste Anwalt des Archipels und ich habe Verbindungen.\nBringen Sie Ihre Prinzipalin mit, der Prozess wird ohne sie nicht stattfinden. Seien Sie nicht zu spät und verlassen Sie die Stadt nicht. Und wenn Sie können, nehmen Sie den letzten Teil der Bezahlung mit, ich bin mir unseres Sieges völlig sicher.";
			link.l1 = "Gut. Wir werden morgen in Ihrem Büro sein, Mister Loxley.";
			link.l1.go = "saga_25";
		break;
		
		case "saga_25":
			DialogExit();
			SaveCurrentNpcQuestDateParam(npchar, "court_date");
			pchar.questTemp.Saga = "court"; // обновляем флаг
			AddQuestRecord("Testament", "10");
			NextDiag.CurrentNode = "First time";
			// закрываем выходы из города
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", true);// лесник там нет этого пирса
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true);
			//pchar.GenQuest.CannotWait = true;//запрет ожидания
			// снимаем общий таймер Саги!
			pchar.quest.Saga_TimeOver.over = "yes";
		break;
		
		case "saga_26":
			dialog.text = "MacArthur? Nein, es ist Sharp! Nun, folge mir jetzt!";
			link.l1 = "...";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			DialogExit();
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto10");
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			sld = characterFromId("Helena");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(npchar, "reload", "reload1", "Saga_CourtGo", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			LAi_ActorFollow(sld, npchar, "", -1);
			NextDiag.CurrentNode = "saga_28";
			// открываем выходы из города
			//LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник рано 
			//LocatorReloadEnterDisable("PortRoyal_town", "reload2_back", false);
			//LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
		break;
		
		case "saga_28":
			dialog.text = "Lassen Sie mich Ihnen gratulieren, Mister, und Ihrer Hauptperson. Sie ist nun die rechtmäßige Herrscherin von Ilsa Tesoro. Es lohnt sich, darauf ein Glas Champagner zu trinken!";
			link.l1 = "Absolut, Mister Loxley. Ihre Rede war ausgezeichnet. Ich dachte, dass Oberst Doyle einen Herzinfarkt erleiden würde, als Sie dem Gericht erzählten, dass Lawrence Beltrop Kapitän Butcher ist.";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "Ja, Mister Doyle muss sich von seinem Traum einer Militärbasis auf Isla Tesoro verabschieden. Und was kann er tun? Gesetz ist Gesetz und es gilt für jeden, auch für den angesehenen Oberst.";
			if (CheckAttribute(pchar, "questTemp.Saga.Beltrop_die"))
			{
				link.l1 = "Sind alle Papiere in Ordnung und bestätigen sie Helens Recht auf die Insel?";
				link.l1.go = "saga_30";
			}
			else
			{
				link.l1 = "Ich habe gehört, dass der Richter die Verhaftung von Lawrence Beltrop angeordnet hat. Ich nehme an, dass er gehängt wird?";
				link.l1.go = "saga_34";
			}
		break;
		
		case "saga_30":
			dialog.text = "Sicher, Mister. Ich habe jedes Komma überprüft. Sie können sich sicher sein, dass sie in Ordnung sind.";
			link.l1 = "Sehr gut...";
			link.l1.go = "saga_31";
		break;
		
		case "saga_31":
			dialog.text = "Nun, meine Arbeit ist getan. Der Fall war knifflig, aber wir haben ihn zusammen gewonnen. Jetzt, Mister, müssen Sie mir nur noch den letzten Teil meines Honorars zahlen. Kein Druck, ich verstehe, dass Sie beschäftigt sein müssen. Aber ich glaube, dass Sie Zeit finden werden, mir die letzten 450 Dublonen innerhalb einer Woche zu bringen.\nAußerdem kann ein Kunde wie Sie immer mit erheblichen Rabatten rechnen. Ich kann Ihnen sehr helfen, ich habe Verbindungen in jede Hauptstadt des Archipels, sogar in die feindlichen, also kann jedes rechtliche Problem, auf das Sie stoßen, gelöst werden.";
			link.l1 = "Ausgezeichnet. Jetzt weiß ich, wen ich fragen soll.";
			link.l1.go = "saga_32";
		break;
		
		case "saga_32":
			dialog.text = "Ich garantiere Ihnen ein positives Ergebnis, selbst in den schwierigsten Situationen.";
			link.l1 = "Schön. Ich muss jetzt gehen, Helen und ich haben viel zu tun.";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "Auf Wiedersehen, Mister.";
			link.l1 = "Auf Wiedersehen, Mister Loxley.";
			link.l1.go = "saga_35";
		break;
		
		case "saga_34":
			dialog.text = "Ich vermute schon, er ist Kapitän Butcher, ein Pirat und Bandit. Obwohl er jetzt nicht in Port Royal ist. Er hatte das Glück, tief in die Insel zu ziehen. Aber die Jagd hat begonnen und er wird sicher gefangen werden.";
			link.l1 = "Ich sehe... Sind die Papiere in Ordnung?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_35":
			DialogExit();
			SetFunctionTimerCondition("Saga_RemainGoldLoxly", 0, 0, 10, false); // таймер на оплату услуг
			DoQuestReloadToLocation("PortRoyal_town", "quest", "quest3", "Saga_HelenaIslaTesoro");
			npchar.quest.waitgold = "true";
			pchar.questTemp.Saga = "lastpages";
			NextDiag.CurrentNode = "First time";
		break;
		
		case "saga_36":
			RemoveDublonsFromPCharTotal(450);
			//Log_Info("You have given 450 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Herrlich! Es war mir ein Vergnügen, Geschäfte mit Ihnen zu machen, Mister! Jetzt können Sie in jeder Angelegenheit um meine Hilfe bitten und einen Rabatt erhalten. Ärger mit dem Gesetz, Kopfgeld für Ihren Kopf... Sie sind willkommen. Ich werde immer froh sein, Sie zu sehen.";
			link.l1 = "Es wäre besser, wenn ich überhaupt keinen Ärger hätte, aber... Dinge passieren. Danke und auf Wiedersehen, Mister Loxley.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			DialogExit();
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			NextDiag.CurrentNode = "Loxly"; // услуги адвоката
		break;
		
		case "saga_38":
			dialog.text = "Was meinen Sie, Mister? Werden Sie die Bedingungen unserer Vereinbarung verletzen?";
			link.l1 = "Genau. Ich habe die meiste Arbeit geleistet. Du kannst dir gar nicht vorstellen, was ich tun musste, um die Beweise zu bekommen. Und du hast nur diese Papiere genommen und bist vor Gericht gegangen. Neunhundert Dublonen sind mehr als genug, da bin ich mir sicher.";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = "Sie sprechen wie ein Pirat, Mister! Nun, ich werde nicht arm werden, indem ich vierhundertfünfzig Dublonen verliere, aber Sie werden auch nicht reich. Tatsächlich haben Sie gerade viel mehr verloren! Und vielleicht werden Sie in der Zukunft noch etwas verlieren... Verlassen Sie sofort mein Haus und zeigen Sie sich hier nie wieder!";
			link.l1 = "Und das werde ich tun. Lebewohl, Mister Loxley.";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
			pchar.quest.Saga_RemainGoldLoxly.over = "yes"; //снять таймер
			LocatorReloadEnterDisable("PortRoyal_town", "houseSp4", true); // закроем вход к Локсли
			ChangeCharacterNationReputation(pchar, ENGLAND, -10);
		break;
		
		case "saga_40":
			dialog.text = "Ich will nicht mit dir reden. Verschwinde oder ich rufe die Wachen!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "saga_40";
		break;
		
		// провалы Саги
		case "saga_l3":
			dialog.text = "Mister, wir hätten Ihren Fall gewonnen, wenn Sie früher zu mir gekommen wären. Das Testament ist abgelaufen. Es tut mir leid.";
			link.l1 = "Eh, es tut mir noch mehr leid! Nun, auf Wiedersehen, Mister Loxley.";
			link.l1.go = "saga_l3_1";
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l3";
		break;
		
		case "saga_l3_1":
			DialogExit();
			pchar.quest.Saga_Late_3.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_3.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_3.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga = "late_l3"; // для Свенсона
		break;
		
	//-------------------------------------- адвокатские услуги ------------------------------------------------
		case "Loxly":
			dialog.text = TimeGreeting()+", Mister. Schön, Sie zu sehen. Benötigen Sie meine Dienste?";
			link.l1 = "Ja. Deshalb bin ich hier.";
			link.l1.go = "loxly_1";
			link.l2 = "Nein, glücklicherweise brauche ich sie im Moment nicht. Wollte Sie nur grüßen.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "loxly_1":
			dialog.text = "Ich bin bereit, Ihnen zuzuhören. Welche Art von Hilfe benötigen Sie.";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
			{
				link.l1 = "Ich habe Ärger mit den englischen Behörden.";
				link.l1.go = "RelationTo_0";
			}
			
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
			{
				link.l2 = "Ich habe Ärger mit den französischen Behörden.";
				link.l2.go = "RelationTo_1";
			}
			if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
			{
				link.l3 = "Ich habe Ärger mit den spanischen Behörden.";
				link.l3.go = "RelationTo_2";
			}

			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
			{
				link.l4 = "Ich habe Ärger mit den niederländischen Behörden.";
				link.l4.go = "RelationTo_3";
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Ich habe mich mit den Schmugglern gestritten.";
				Link.l5.go = "contraband";
            }
			Link.l7 = "Es tut mir leid, ich habe meine Meinung geändert...";
			Link.l7.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		case "RelationYet": // уже оплачено
			dialog.text = "Ich arbeite bereits an Ihrer Angelegenheit. Es wird alles gut werden, das kann ich Ihnen versichern.";
			Link.l1 = "Danke. Ich werde warten.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;
		
		// --> снятие НЗГ
		case "RelationAny_Done":
			iSumm = sti(npchar.quest.relation.summ);
			int iRate = abs(ChangeCharacterNationReputation(pchar, sti(npchar.quest.relation), 0));
			if (iRate <= 10) sTemp = "Nun, ich würde das nicht als Ärger bezeichnen. Nur ein kleines Problem. Ich werde die Angelegenheit sofort regeln";
			if (iRate > 10 && iRate <= 30) sTemp = "Ja, Ihr Ruf ist etwas beschädigt, aber ich sehe nichts Kritisches. Ich werde die Angelegenheit sofort regeln";
			if (iRate > 30 && iRate <= 60) sTemp = "Ja, Sie haben den falschen Weg mit den Behörden eingeschlagen. Es wird nicht leicht sein, aber ich bin sicher, dass ich Ihre Meinungsverschiedenheiten problemlos beilegen kann";
			if (iRate > 60 && iRate <= 90) sTemp = "Und wie haben Sie das gemacht, Mister? Ihre Probleme sind nicht nur ernst, sie sind wirklich ernst. Die Behörden sind sehr erpicht darauf, Sie zu kriegen. Ich werde mich sehr anstrengen müssen, um Ihre Unstimmigkeiten zu schlichten";
			if (iRate > 90) sTemp = "Nun ja... Die Lage ist katastrophal - Sie sollen der erbittertste Feind sein. Es wird hart werden, aber ich bin schließlich der beste Anwalt in der Karibik, also werde ich eure Meinungsverschiedenheiten schlichten";
			dialog.text = ""+sTemp+" mit "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl")+". Es wird Sie "+FindRussianMoneyString(iSumm)+" kosten.";
			if(sti(pchar.money) >= iSumm)
			{
				link.l1 = "Sehr gut, Mister Loxley, ich stimme zu. Hier ist euer Geld und versucht, die Dinge so schnell wie möglich zu regeln.";
				link.l1.go = "relation";
			}
			link.l2 = "Ich habe momentan nicht die Summe, die Sie verlangen. Ich komme später wieder!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Loxly";
		break;

		case "relation":
			dialog.text = "Es war mir ein Vergnügen, Geschäfte mit Ihnen zu machen, Mister. Sie können wieder frei atmen, Ihr Problem wird in den nächsten zwei Wochen verschwinden. Bitte vermeiden Sie jegliche Konfrontationen mit "+XI_ConvertString(Nations[sti(npchar.quest.relation)].Name+"Abl")+", während ich mitten in Verhandlungen stecke.";
			link.l1 = "Gut, ich werde Ihre Warnung berücksichtigen. Danke und lebt wohl!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
			ChangeNationRelationFromRelationAgent(npchar);
			attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
            Pchar.GenQuest.(attrLoc) = true;
			Pchar.GenQuest.(attrLoc).loyer = "true";
			NextDiag.TempNode = "Loxly";
		break;
		// <-- снятие НЗГ
		
		case "contraband":
			npchar.quest.contrasum = makeint(0.3*stf(Pchar.rank)/stf(Pchar.reputation.nobility)*60000);
			dialog.Text = "Und warum haben Sie das getan? Schmuggler sind gute Jungs, sie sind auf ihre Weise ehrlich. Wir alle müssen leben und essen... Gut, es ist keine große Sache und es wird Sie nur "+FindRussianMoneyString(sti(npchar.quest.contrasum))+" kosten.";
			if(sti(Pchar.money) >= sti(npchar.quest.contrasum))
			{
				Link.l1 = "Sehr gut, Mister Loxley, ich stimme zu. Hier ist euer Geld und versuchen Sie, die Dinge so schnell wie möglich zu regeln.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Ich habe momentan nicht die Summe, die Sie verlangen. Ich komme später wieder!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Ausgezeichnet, ich werde Ihr Problem lösen. Sie werden bald wieder Geschäfte mit ihnen machen können.";
			Link.l1 = "Danke!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.contrasum));
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
