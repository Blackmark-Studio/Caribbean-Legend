// диалоги персонажей по пиратской линейке // Addon 2016-1 Jason пиратская линейка
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, attrL;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	if(HasSubStr(attrL, "ShipStockManBack_"))
 	{
        i = findsubstr(attrL, "_" , 0);
	 	NPChar.ShipToStoreIdx = strcut(attrL, i+1, strlen(attrL)-1); // индех в конце
 	    Dialog.CurrentNode = "ShipStockManBack";
 	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
        case "First time":
			dialog.text = "Was willst du?";
			link.l1 = "Ich sollte gehen...";
			link.l1.go = "exit";
		break;
		
		// Лопе Монторо
		case "Mtr_officer":
			if (pchar.questTemp.Mtraxx != "fail" && pchar.questTemp.Mtraxx == "jewelry_5")
			{
				pchar.quest.Mtraxx_JewelryHavanaOver.over = "yes"; //снять таймер
				dialog.text = "Verdammt noch mal, wer zur Hölle bist du?";
				link.l1 = "Guten Tag, Don Lope. Obwohl wir uns noch nicht kennen, wäre jetzt ein guter Zeitpunkt. Besonders jetzt, da ich so begierig darauf bin, Ihnen aus dieser schwierigen Situation zu helfen...";
				link.l1.go = "Mtr_officer_1";
			}
			else
			{
				dialog.text = "Was willst du?";
				link.l1 = "Ich sollte gehen...";
				link.l1.go = "exit";
			}
		break;
		
		case "Mtr_officer_1":
            dialog.text = "Hilfe? Mir? Was für eine Wendung! Könnten Sie mich erleuchten, senor, woher solche Großzügigkeit kommt?";
			link.l1 = "Sicherlich. Ich suche nach Ihrem ehemaligen Kapitän, Esberdo Cabanas, und ich habe nicht viel Zeit... am besten, ich würde ihn an diesem Ort treffen, den er geheim hält. Noch besser, wenn ich dort ankomme, bevor er es tut.";
			link.l1.go = "Mtr_officer_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_2":
            dialog.text = "Ha-ha! Ich habe diesem erbärmlichen Idioten gesagt, er soll sein Maul halten! Der blaue Bernstein, habe ich recht?";
			link.l1 = "Sie denken in die richtige Richtung, mein guter Herr.";
			link.l1.go = "Mtr_officer_3";
		break;
		
		case "Mtr_officer_3":
            dialog.text = "Dann lasst uns Eile machen. Ich würde dir gerne jedes letzte Detail erzählen, wenn du einen Weg findest, mich hier rauszuholen. Weißt du, wie ich in dieses Loch gekommen bin?";
			link.l1 = "Insgesamt, ja ich tue es.";
			link.l1.go = "Mtr_officer_4";
		break;
		
		case "Mtr_officer_4":
            dialog.text = "Ich war sturzbetrunken, als das passierte. Verdammt noch mal, dieser verdammte Barkeeper! Ich erinnere mich an nichts. Mir wurde alles erst erzählt, als ich im Laderaum der 'Cantavro' aufwachte. Es wäre alles vorbei gewesen, wenn wir einfach weggesegelt wären, sowohl der Kommandant als auch der Alcalde waren bereit, wegzuschauen. Aber dieser verfluchte Don Esberdo hat mich einfach ins Gefängnis gesteckt. Denkst du, er hat das getan, um 'das Richtige zu tun'? Wenn es doch so wäre, dieser Schurke wollte nur meinen Anteil an den Bernsteinstücken behalten\nEs war ich, der erwähnte, dass es unter Wasser mehr Bernsteine geben könnte, als wir am Strand gefunden haben. Es war ich, der einen Weg gefunden hat, sie zu bekommen. Ich sollte einen ordentlichen Anteil bekommen, aber... oh, dieser Hurensohn! Ugh, aber genug davon. Weder der Alcalde, noch der Kommandant, noch der Don de Toledo sind froh darüber, dass ich hier verrotte. Wenn es nicht für diesen Bauern und seine Kuhfrau wäre, die die Taubenschläge aufgeschreckt haben... so oder so, sie werden nichts dagegen haben, wenn du mir hilfst\nSprich mit dem Gouverneur, gib vor, mein alter Freund aus Europa zu sein - ich werde das selbst bestätigen. Wie ist eigentlich dein Name?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "Mtr_officer_5";
		break;
		
		case "Mtr_officer_5":
            dialog.text = ""+GetFullName(pchar)+", wunderbar. Geh zu Don Diego de Toledo und bitte ihn um Rat. Denk daran, du hast nur drei Tage, danach wäre es sinnlos, der 'Cantavro' hinterherzujagen. Befreie mich und ich gebe dir alles, was du brauchst, um mit diesem Bastard, Cabanas, fertig zu werden.";
			link.l1 = "Ich werde sofort zum Gouverneur gehen, Don Lope. Ich werde mein Bestes tun, um diese Situation zum Wohl von uns beiden zu lösen.";
			link.l1.go = "Mtr_officer_6";
		break;
		
		case "Mtr_officer_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_6";
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_1", "8");
			SetFunctionTimerCondition("Mtraxx_TimeclearPrison", 0, 0, 4, false); // таймер
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			AddLandQuestMark(characterFromId("Havana_Mayor"), "questmarkmain");
		break;
		
		case "Mtr_officer_7":
			pchar.quest.Mtraxx_TimeclearPrison.over = "yes"; //снять таймер
            dialog.text = "So, der Krämer und seine Glucke haben ihre Rache bekommen, und ich bin endlich mit diesem Loch fertig. Sie haben meine Dankbarkeit senor, Sie haben Ihren Teil getan. Jetzt lassen Sie mich meinen tun.";
			link.l1 = "Ich bin ganz Ohr!";
			link.l1.go = "Mtr_officer_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_officer_8":
            dialog.text = "Gut. Während unserer vorherigen Patrouille wurden wir von einem Sturm getroffen, der uns zwang, unseren Kurs zu verlassen. Wir landeten am Strand der Westlichen Haupt, nicht weit von der Mücken-Küste, um frisches Wasser zu holen. Dort fanden wir eine gute Lagerstätte von blauem Bernstein. Ich habe etwas Prospektion betrieben und einen Haufen davon unter Wasser gefunden. Wir brauchten bessere Ausrüstung, um ihn zu sammeln, deshalb haben wir beschlossen, später zurückzukehren\nEsberdo hat in Havanna fünf Langboote für die Indianer gekauft, um zu tauchen und den Bernstein zu sammeln. Sie kennen den Rest der Geschichte - der Abschaum hat mich losgeworden und ist weggesegelt. Finden Sie ihn an der Mücken-Küste nördlich von Blueweld, und machen Sie schnell - nach meinen Berechnungen haben Sie nur etwa sieben Tage Zeit, um dorthin zu gelangen. Ich hoffe, Sie erwischen den Schuft mitten in der Sammlung, nehmen ihm all seinen Bernstein ab und stechen ihm mehrmals in den Bauch. Seien Sie jedoch vorsichtig, mein ehemaliger Kapitän ist ein erfahrener Kämpfer und Seemann. Gute Reise, senor.";
			link.l1 = "Dasselbe wünsche ich dir, Lope. Leb wohl!";
			link.l1.go = "Mtr_officer_9";
		break;
		
		case "Mtr_officer_9":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_10";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Roger_1", "12");
			SetFunctionTimerCondition("Mtraxx_TimeclearGulf", 0, 0, 7, false); // таймер
			pchar.quest.mtr_jewelry_gulf.win_condition.l1 = "location";
			pchar.quest.mtr_jewelry_gulf.win_condition.l1.location = "Santacatalina";
			pchar.quest.mtr_jewelry_gulf.function = "Mtraxx_JewelryGulf";
			DeleteAttribute(pchar, "GenQuest.PrisonQuestLock");
			DelMapQuestMarkCity("Havana");
			AddMapQuestMarkShore("Shore53", true);
		break;
		
		// Росарио Гусман
		case "Mtr_rosario":
            dialog.text = "Möchten Sie etwas fragen, Herr?";
			link.l1 = "Was Don Montoro betrifft. Wir sind alte Bekannte und ich war wirklich verärgert, als ich von seinen Missgeschicken erfuhr. Don Diego de Toledo hat mich zu Ihnen geschickt, sagte, dass Sie bereits versucht hatten, unseren gemeinsamen Freund freizusetzen...";
			link.l1.go = "Mtr_rosario_1";
		break;
		
		case "Mtr_rosario_1":
            dialog.text = "Hm... senor, das ist ein bisschen... unerwartet, aber ich freue mich, einen Freund von Lope zu treffen! Er hatte schon seit geraumer Zeit Pech und jetzt das...";
			link.l1 = "Was können wir für ihn tun? Keine Möglichkeit für einen edlen Hidalgo, unter dem Abschaum der Gesellschaft zu verrotten!";
			link.l1.go = "Mtr_rosario_2";
		break;
		
		case "Mtr_rosario_2":
            dialog.text = "Ein Geschäftsmann! Es ist sowohl einfach als auch schwierig, dem armen Lope zu helfen. Ich hatte ein Gespräch mit dem Profitmacher, mit dem der arme Lope das Pech hatte, einen Streit zu haben. Er hat zugestimmt, uns für fünfhundert Dublonen entgegenzukommen. Eine beachtliche Summe für seine und seiner Frau 'Leiden'. Leider habe ich es nur geschafft, die Hälfte der benötigten Summe zu sammeln - zweihundertfünfzig Dublonen.";
			link.l1 = "Also, wenn ich Ihnen weitere zweihundertfünfzig Dublonen besorge, wird Don Lope dann freigelassen?";
			link.l1.go = "Mtr_rosario_3";
		break;
		
		case "Mtr_rosario_3":
            dialog.text = "Ja. Der gierige Bastard versprach mir, das Wort zu verbreiten, dass Lope ihm allen Schaden ersetzt hat. Er wird auch den Gouverneur um Begnadigung bitten.";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "Ich habe die erforderliche Summe gerade bei mir. Hier, lass diesen gierigen Bourgeois daran ersticken.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "Ich werde mein Bestes tun, um so schnell wie möglich Geld zu bekommen.";
			link.l2.go = "Mtr_rosario_5";
		break;
		
		case "Mtr_rosario_4":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "Ich kann meinen eigenen Ohren nicht glauben! Senor, Sie müssen vom Herrn gesandt worden sein!";
			link.l1 = "Wann werden sie unseren Mann freilassen?";
			link.l1.go = "Mtr_rosario_8";
			DelLandQuestMark(npchar);
		break;
		
		case "Mtr_rosario_5":
            dialog.text = "Es freut mich, das zu hören, senor. Sie sind ein wahrer Freund von Lope und ein echter Edelmann.";
			link.l1 = "Auf Wiedersehen!";
			link.l1.go = "Mtr_rosario_6";
		break;
		
		case "Mtr_rosario_6":
            DialogExit();
			AddQuestRecord("Roger_1", "10");
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_7":
            dialog.text = "Hast du das Geld mitgebracht?";
			if (PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "Ich habe die benötigte Summe gerade bei mir. Hier, lass diesen gierigen Bourgeois daran ersticken.";
				link.l1.go = "Mtr_rosario_4";
			}
			link.l2 = "Ich bin immer noch dabei.";
			link.l2.go = "Mtr_rosario_7_1";
		break;
		
		case "Mtr_rosario_7_1":
            DialogExit();
			npchar.dialog.currentnode = "Mtr_rosario_7";
		break;
		
		case "Mtr_rosario_8":
            dialog.text = "Ich werde dem schlauen Bastard heute Abend das Geld bringen. Ich glaube, sie werden bis Mittag einen Befehl zur Freilassung unseres Freundes haben. Und ich hoffe, wir werden uns später zum Feiern versammeln?";
			link.l1 = "Sicherlich, Don Rosario. Ich sollte jetzt gehen. Auf Wiedersehen!";
			link.l1.go = "Mtr_rosario_9";
		break;
		
		case "Mtr_rosario_9":
            DialogExit();
			AddQuestRecord("Roger_1", "11");
			npchar.lifeday = 1;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			npchar.dialog.currentnode = "Mtr_rosario_10";
			pchar.quest.mtr_prisoner.win_condition.l1 = "Timer";
			pchar.quest.mtr_prisoner.win_condition.l1.date.hour  = 12;
			pchar.quest.mtr_prisoner.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtr_prisoner.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtr_prisoner.function = "Mtraxx_PrisonerFree";
		break;
		
		case "Mtr_rosario_10":
            dialog.text = "Bald wird unser Freund frei sein!";
			link.l1 = "...";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Mtr_rosario_10";
		break;
		
		// Лысый Джеффри
		case "Jeffry":
			pchar.quest.Mtraxx_SilkCPVOver.over = "yes"; //снять прерывание
            dialog.text = "He, was zum Teufel machst du auf meinem Schiff? Ich glaube nicht, dass du meine Einladung bekommen hast, oder?";
			link.l1 = "Beruhige dich, Geffrey. Ich komme von Tyrex wegen des Schiffseidengeschäfts.";
			link.l1.go = "Jeffry_1";
		break;
		
		case "Jeffry_1":
            dialog.text = "A-ah, nun, lass uns dann reden. Was plant er? Ich habe bereits mit Schmugglern gesprochen, wenn du mich fragst, bieten sie einen guten Preis für die Waren...";
			link.l1 = "Und wie viel, darf ich fragen?";
			link.l1.go = "Jeffry_2";
		break;
		
		case "Jeffry_2":
            dialog.text = "1300 Pesos für eine Rolle. Ich denke, es ist ein guter Preis.";
			link.l1 = "Ja, und Tyrex will zwanzig Goldstücke für eine Rolle. Keine Münze weniger. Und ich meine Dublonen. Er hat mir den Auftrag gegeben, einen passenden Käufer für diesen Preis zu finden.";
			link.l1.go = "Jeffry_3";
		break;
		
		case "Jeffry_3":
            dialog.text = "Ha-ha-ha, Junge, bist du nicht ein Glückspilz! Marcus hat wirklich Appetit! Nun, geh und suche einen solchen Käufer, es wäre herrlich, dich zu sehen wie du es versuchst.";
			link.l1 = "Ja, das ist alles sehr verdammt lustig und zum Brüllen. Sehe ich glücklich aus? Tue ich nicht. Also schlage ich vor, du hörst auf zu lachen und hilfst mir.";
			link.l1.go = "Jeffry_4";
		break;
		
		case "Jeffry_4":
            dialog.text = "Gut, gut, Kumpel... Jesus, du bist nicht sehr angetan von Witzen, was? Aber ich verstehe, du bist nicht für Tyrex's Fantasien zu verantworten, wir werden alle unseren Anteil daran bekommen, vertrau mir. Und wie kann ich dir möglicherweise helfen? Du kannst es nicht in Geschäften verkaufen, Zoll ist auch keine Option, nur Schmuggler bleiben übrig. Wer sonst braucht es? Hast du irgendwelche Ideen?";
			link.l1 = "Ich habe seit Hispaniola darüber nachgedacht... Egal. Ich habe nur zwei Monate Zeit, um einen regelmäßigen Käufer zu finden. Etwas muss dagegen unternommen werden. Deine Aufträge sind, in der nächsten Bucht anzulegen und Reparaturen durchzuführen.";
			link.l1.go = "Jeffry_5";
		break;
		
		case "Jeffry_5":
            dialog.text = "Zwei Monate?! Was zum Teufel? Ach, verdammt. Die 'Schlange' braucht wirklich eine Reparatur und Reinigung oder sie wird nicht mal in der Lage sein, eine Barke zu verfolgen. Hey, französische Huren! Die Crew von Kahlkopf Geffrey bleibt für zwei Monate in Kapsterville! Ha-ha-ha!... Nun, viel Glück für dich Kumpel, bei deinen sinnlosen Suchen. Wenn du einen Idioten findest, der bereit ist, Marcus' Preis für diese verdammt Seide zu zahlen - du weißt, wo du mich findest.";
			link.l1 = "Warte! Gib mir eine Rolle von dieser Seide. Ich muss die Waren potenziellen Käufern zeigen.";
			link.l1.go = "Jeffry_6";
		break;
		
		case "Jeffry_6":
            dialog.text = "Sicher, kein Problem. Du kannst es mit dir auf einem Langboot mitnehmen... Hey Jungs! Werft einen Ballen Seide auf das Boot des Kapitäns!";
			link.l1 = "Gut. Nun, ich werde dich sehen, wenn ich den Käufer finde!";
			link.l1.go = "Jeffry_7";
		break;
		
		case "Jeffry_7":
            DialogExit();
			AddQuestRecord("Roger_2", "3");
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
			pchar.questTemp.Mtraxx = "silk_2";
			AddCharacterGoods(pchar, GOOD_SHIPSILK, 1);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Mtraxx_SilkTimeOver", 0, 0, 61, false); // таймер
		break;
		
		case "Jeffry_8":
            dialog.text = "Sonst noch etwas, Kumpel?";
			link.l1 = "Im Moment nichts...";
			link.l1.go = "Jeffry_8_1";
		break;
		
		case "Jeffry_8_1":
            DialogExit();
			npchar.DeckDialogNode = "Jeffry_8";
			npchar.dialog.currentnode = "Jeffry_8";
		break;
		
		case "Jeffry_9":
			pchar.quest.Mtraxx_SilkTimeOver.over = "yes";
            dialog.text = "Wie geht es dir, Kumpel?";
			link.l1 = "Macht gute Fortschritte. Ich habe uns einen Käufer gefunden. Fünfundzwanzig Dublonen für eine Rolle. Ich glaube, Tyrex wird es mögen.";
			link.l1.go = "Jeffry_10";
		break;
		
		case "Jeffry_10":
            dialog.text = "Unmöglich! Du bist der findige Sohn eines Teufels! Wie hast du das geschafft, huh?";
			link.l1 = "Es ist eine lange Geschichte, Geffrey. Jetzt hör zu. Du solltest zwischen dem 10. und 15. in Cape Negril in Jamaika ankommen. Sie werden dort nachts auf dich warten. Das Passwort ist 'Ein Kaufmann aus Lyon'. Verstanden? Wiederhole.";
			link.l1.go = "Jeffry_11";
		break;
		
		case "Jeffry_11":
            dialog.text = "Ein Kaufmann aus Lyon. Verstanden. Ich sollte meinem Zahlmeister sagen, dass er es aufschreibt, er ist der einzige Mann hier, der schreiben kann. Ha-ha!";
			link.l1 = "Haben Sie hundert Rollen im Laderaum?";
			link.l1.go = "Jeffry_12";
		break;
		
		case "Jeffry_12":
            dialog.text = "Ich habe noch mehr.";
			link.l1 = "Prächtig. Es ist Zeit für dich, die Segel zu setzen. Enttäusche mich nicht!";
			link.l1.go = "Jeffry_13";
		break;
		
		case "Jeffry_13":
            dialog.text = "Entspann dich, Kumpel, alles wird so gemacht, wie es gemacht werden sollte.";
			link.l1 = "Gottes Segen, Geffrey. Vielleicht treffen wir uns wieder.";
			link.l1.go = "Jeffry_14";
		break;
		
		case "Jeffry_14":
            DialogExit();
            AddQuestRecord("Roger_2", "22");
			pchar.questTemp.Mtraxx = "silk_14"; // к Тираксу
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_12";
			pchar.quest.mtraxx_hide_jeffry.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_hide_jeffry.function = "Mtraxx_SilkHideJeffry";
		break;
		
		case "Jeffry_15":
            dialog.text = "Ho-ho-ho! Schlauer Charlie Prince, in Fleisch und Blut! Schön, dich wieder zu sehen, Kumpel!";
			link.l1 = "Kahler Geffrey! Charlie Prince sagtest du? Ha!";
			link.l1.go = "Jeffry_15x";
		break;
		
		case "Jeffry_15x":
            dialog.text = "Noch nie deinen zweiten Namen gehört? So nennen sie dich jetzt in La Vega.";
			link.l1 = "Ich verstehe, woher Charlie kommt, aber warum Prinz?";
			link.l1.go = "Jeffry_15y";
		break;
		
		case "Jeffry_15y":
            dialog.text = "Nun, du bist der einzige noble Bastard in La Vega! Ha-ha-ha! Wie geht es dir? Warst du in Pasquales Laden? Hast du dem alten Schurken Vorräte abgekauft?";
			link.l1 = "Noch nie wieder!";
			link.l1.go = "Jeffry_16";
		break;
		
		case "Jeffry_16":
            dialog.text = "K-ha! Warum, er hat dir nicht gefallen? Hat er dir Pökelfleisch zum Preis von Rum verkauft?";
			link.l1 = "Schlimmer! Ich bekam von ihm einen Tipp zu einem holländischen Karawanen, beladen mit Ebenholz. Es war nicht einfach, ihn zu finden, den Kaufmann zu besteigen und dann dieses verdammte Holz vor ein paar Dutzend Ratten zu schützen! Und rat mal, das Miststück hat mir 150 Pesos pro Stück bezahlt. Für ein Stück verdammtes Ebenholz, Geffrey!";
			link.l1.go = "Jeffry_17";
		break;
		
		case "Jeffry_17":
            dialog.text = "Das passiert ständig, Kumpel, das versichere ich dir. Lavoisier hat schon ein Dutzend gute Burschen wie dich übers Ohr gehauen. Tatsächlich hat er dir etwas bezahlt, was für ihn selten ist. Wir nehmen seine 'Hinweise' nicht einmal an, wenn wir am Verhungern sind.";
			link.l1 = "Danke mein Freund, zumindest weiß ich jetzt, dass ich nicht der erste und einzige Idiot war! Aber dieses Mal hat sich der Bastard selbst ins Bein geschossen. Ich werde dafür sorgen, dass er den Tag bereut, an dem er mich gesehen hat.";
			link.l1.go = "Jeffry_18";
		break;
		
		case "Jeffry_18":
            dialog.text = "He-he-he! Warte Prinz, beruhige dich ein bisschen. Der Händler ist hier unantastbar. Wage es, ihn zu plündern - Marcus wird dir an den Arsch gehen. Sag mal, hat dich Tyrex zu Lavoisier geschickt?";
			link.l1 = "Hm. Ja... Warum?";
			link.l1.go = "Jeffry_19";
		break;
		
		case "Jeffry_19":
            dialog.text = "Hör zu... (senkt seine Stimme) Sie sagen, dass der Vieraugige mit Marcus teilt. Verstehst du mich jetzt? Deshalb wird kein Pirat es jemals wagen, Lavoisiers Schiffe anzugreifen, sonst sind sie erledigt.";
			link.l1 = "Bemerkt. Danke für die Warnung, Geffrey. Lebewohl und Gott beschütze dich!";
			link.l1.go = "Jeffry_20";
		break;
		
		case "Jeffry_20":
            dialog.text = "Gleichfalls, Kumpel.";
			link.l1 = "...";
			link.l1.go = "Jeffry_21";
		break;
		
		case "Jeffry_21":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 15.0);
			AddQuestRecord("Roger_4", "10");
			CloseQuestHeader("Roger_4");
			QuestSetCurrentNode("Terrax", "mtraxx_34"); // релиз-правка
			bDisableFastReload = false;
			pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират
			pchar.questTemp.CharleePrince = true; // атрибут для найма команды 
		break;
		
		case "Jeffry_22":
            dialog.text = "Ho-ho-ho Prinz! Ich hab mich gefragt, wer das Feuerwerk gemacht hat! Hab eine Truppe Musketiere mitgebracht, für den Fall, dass es die Spanier waren.";
			link.l1 = "Geffrey? Du bist auch hier? Aber wie? Hast du auch die Schatzkarte gekauft?";
			link.l1.go = "Jeffry_23";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
		break;
		
		case "Jeffry_23":
            dialog.text = "Kumpel, ich verschwende mein Geld nicht für solchen Unsinn. Sie haben mir das Tagebuch eines Reisenden geliefert, der über einen sicheren Weg zu diesen Verliesen geschrieben hat.";
			link.l1 = "Wer hat es dir gebracht?";
			link.l1.go = "Jeffry_24";
		break;
		
		case "Jeffry_24":
            dialog.text = "Ein Junkie. Alles, was er brauchte, waren hundert Pesos für einen Drink.";
			link.l1 = "Ist es auf Tortuga passiert?";
			link.l1.go = "Jeffry_25";
		break;
		
		case "Jeffry_25":
            dialog.text = "Nein. Es war Barbados? Prinz, warum machst du dir so viele Sorgen? Je mehr von uns da sind, desto schneller können wir die Schätze tragen!";
			link.l1 = "Ich mag das nicht. Ich glaube nicht an solche Zufälle. Könnte es Camillas Vater sein, der dieses Tagebuch geschrieben hat?";
			link.l1.go = "Jeffry_26";
		break;
		
		case "Jeffry_26":
            dialog.text = "Wer ist Camilla?";
			link.l1 = "Die Dirne, die mir eine Karte zu diesem Ort für zweihundert Pesos verkauft hat!";
			link.l1.go = "Jeffry_27";
		break;
		
		case "Jeffry_27":
            dialog.text = "Heh... Prinz, du denkst zu viel. Lass uns auf Schatzsuche gehen. Los!";
			link.l1 = "Keine Notwendigkeit. Ich habe sie bereits gefunden... Sie sind unten im Kerker, hinter Eisengittern. Wir müssen sie durchbrechen. Hör zu, Geffrey, es gibt noch eine Sache! Pelly der Säbel war auch hier!";
			link.l1.go = "Jeffry_28";
		break;
		
		case "Jeffry_28":
            dialog.text = "Säbel? Nun, dann ist es unser Glückstag! Aber wo ist er jetzt?";
			link.l1 = "Unten... tot. Ich traf ihn in der Nähe des Schatzes. Er wurde verrückt, fing an aus Gier zu schreien. Dann griffen er und seine Gefährten mich an.";
			link.l1.go = "Jeffry_29";
		break;
		
		case "Jeffry_29":
            dialog.text = "Hm... Pelly hatte immer Pech mit Geld. Er muss verrückt geworden sein, als er die Ladung Gold sah.";
			link.l1 = "Es mag so sein... aber Geffrey, du verstehst es nicht! Alle drei von uns sind hier! Und wir haben alle den gleichen Hinweis! Denkst du, das war ein Zufall? Jemand will uns offensichtlich alle an einem Ort haben, und dieser Ort fühlt sich wie ein Grab an.";
			link.l1.go = "Jeffry_30";
		break;
		
		case "Jeffry_30":
            dialog.text = "Hast du das Gold gesehen?";
			link.l1 = "Ich habe es mit meinen eigenen Augen gesehen. Mehrere riesige Kisten gefüllt mit Münzen und Barren.";
			link.l1.go = "Jeffry_31";
		break;
		
		case "Jeffry_31":
            dialog.text = "Dann warum sorgen Sie sich, Prinz? Führen Sie den Weg, lassen Sie uns einen Blick auf diese Bars von Ihnen werfen. Dann teilen wir das Gold.";
			link.l1 = "Ach, du könntest recht haben, was auch immer... Lass uns gehen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionWithJeffry");
		break;
		
		case "Jeffry_32":
            PlaySound("Voice\English\LE\Jeffry\Jeffry_gold.wav");
			dialog.text = "Was für ein Spektakel! Das ist ein großer Haufen Gold! Ich kann jetzt sehen, warum Cutlass verrückt geworden ist. Wir sind sehr glücklich, Prinz! Was denkst du, wie viel Gold werden wir hier finden?";
			link.l1 = "Genug. Wir werden es sicher wissen, wenn wir uns um diese Stangen kümmern.";
			link.l1.go = "Jeffry_33";
		break;
		
		case "Jeffry_33":
            dialog.text = "Ja, das Gitter ist sehr stark, wir werden es weder mit bloßen Händen noch mit Schwertern durchbrechen. Du hast recht, Kumpel - wir müssen einige Werkzeuge oder viel Schießpulver finden. Hey schau! Was ist das!?";
			link.l1 = "...";
			link.l1.go = "Jeffry_34";
		break;
		
		case "Jeffry_34":
            DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionJeffryMushketer", 0.1);
		break;
		
		case "Jeffry_35":
            PlaySound("Voice\English\LE\Jeffry\Jeffry_mozila.wav");
			dialog.text = RandSwear()+"Was für eine verdammte Pfeife!";
			link.l1 = "Du verdammte Schlange!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionJeffryFight");
		break;
		
		// Билли Сипатый
		case "Billy":
			pchar.quest.Mtraxx_BillySeaTimeOver.over = "yes"; //снять таймер
			PlaySound("VOICE\English\LE\Billy\Billy_01.wav");
            dialog.text = "Hai schluck mich, wenn das dieses Jahr auf der 'Fliegenfisch' passiert ist... Jungs, wir haben hier einen Gast! Was läuft so schief in deinem Leben, Kumpel, dass du dich entschlossen hast, meinem alten Kahn einen Besuch abzustatten?";
			link.l1 = "Grüße! Du bist doch der, den sie Husky Billy nennen, nicht wahr?";
			link.l1.go = "Billy_1";
		break;
		
		case "Billy_1":
            dialog.text = "Kannst du es nicht an meiner Stimme erkennen, Kapitän? Vor langer Zeit konnte sie britische und spanische Kaufleute dazu bringen, sich vor Angst in die Hosen zu machen. Herrliche Zeiten waren das!... Jetzt wartet der alte Billy darauf, dass sein Leben in der Nähe der Küsten seiner Lieblingsinsel auf seinem kostbaren Langboot endet...";
			link.l1 = "Ich habe ein Geschäft für dich, Billy. Mir wurde gesagt, dass du alles weißt, was hier um Jamaika herum vor sich geht. Ist das so?";
			link.l1.go = "Billy_2";
		break;
		
		case "Billy_2":
            dialog.text = "Wenn man dir das gesagt hat, dann muss es wohl so sein, meinst du nicht? Zieh eine Krabbe nicht an ihren Eiern, sprich. Was hast du für ein Anliegen bei mir?";
			link.l1 = "Sehr gut. Es gibt einen Schiffsbauer in Port Royal. Er bietet seinen Kunden spezielle Dienstleistungen an und benötigt Schiffsseide für seine Produktion und die genannten Dienstleistungen. Da der Handel mit dieser Ware hier illegal ist, hat er sich einen illegalen Verkäufer gesucht. Ich möchte wissen, wer und wie ihn mit Schiffsseide versorgt.";
			link.l1.go = "Billy_3";
		break;
		
		case "Billy_3":
            dialog.text = "Ho-ho-ho, schau dir das an! Arbeitest du für Oberst D'Oyley, Sohn?";
			link.l1 = "Hier gehen wir wieder! Nein, ich arbeite mit Marcus Tyrex. Er will einen Anteil am Schiffsseidenmarkt und dieser Schiffsbauer hat heilige Angst, mit 'unbekannten' Leuten zu handeln...";
			link.l1.go = "Billy_4";
		break;
		
		case "Billy_4":
            dialog.text = "Oh, du arbeitest für den Code Hüter! Das sind großartige Neuigkeiten... wenn du natürlich nicht lügst. Mir sind die Schiffsbauer egal, verhaften Sie einen - ein anderer kommt. Aber meine alte Dame ist mir wichtig. Die 'Fliegende Fisch' ist in schlechter Verfassung. Verstehst du mich?\nBring mir ein anderes Langboot, ein neues, und eine Rolle Schiffsseide, die gleiche Art, über die du sprichst - Billy wird daraus ein ordentliches Segel machen, um mit den Patrouillen zu ficken, ha-ha-ha! Im Gegenzug wird Billy alles über den Schiffsbauer und seine Seidenquelle erzählen. Vertrau mir, Sohn, ich weiß alles, was du wissen willst, ich muss nur sicherstellen, dass du ein ehrlicher Pirat und kein Arsch küssender Roter Mantel bist!";
			link.l1 = "Ein neues Langboot? Wie wäre es, wenn ich dir genug Geld gebe, um es selbst zu kaufen? Ich werde sogar extra hinzufügen.";
			link.l1.go = "Billy_5";
		break;
		
		case "Billy_5":
            dialog.text = "He-eh, Kapitän, der alte Billy ist in der Stadt nicht willkommen. Sie erinnern sich zu gut an mich in Port Royal und ich habe nicht die Absicht, unter meinen alten Freunden auf diesem Felsen gehängt zu werden. Also, Sohn, ich warte darauf, dass du mir ein brandneues langes Boot lieferst. Ich werde drei Tage lang am Negril Cape warten. Und vergiss die Seide nicht!";
			link.l1 = "Sehr gut, Billy. Du bekommst dein Langboot und eine Rolle Schiffsseide. Ich komme bald zurück.";
			link.l1.go = "Billy_6";
		break;
		
		case "Billy_6":
            dialog.text = "Sehr gut, Billy wird an einem Ufer auf dich warten, Kapitän. Bis bald!";
			link.l1 = "...";
			link.l1.go = "Billy_7";
		break;
		
		case "Billy_7":
            DialogExit();
			AddQuestRecord("Roger_2", "8");
			npchar.dialog.currentnode = "Billy_8";
			pchar.questTemp.Mtraxx = "silk_7";
			SetFunctionTimerCondition("Mtraxx_BillyTimeOver", 0, 0, 3, false); // таймер
			pchar.quest.mtr_billy_coast.win_condition.l1 = "ExitFromLocation";
			pchar.quest.mtr_billy_coast.win_condition.l1.location = pchar.location;
			pchar.quest.mtr_billy_coast.function = "Mtraxx_BillyOnCoast";
			locations[FindLocation("shore35")].DisableEncounters = true; //энкаутеры закрыть
			npchar.DontDeskTalk = true;
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "Billy_8":
			PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
            dialog.text = "Was? Haben Sie mir schon ein Langboot gebracht?";
			link.l1 = "Du bist ein Spaßvogel, was, Billy?";
			link.l1.go = "exit";
		break;
		
		case "Billy_9":
            dialog.text = "Also, Kapitän, wie steht's um mein nagelneues Langboot?";
			if(Companion_CheckShipType(SHIP_TARTANE) && GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0)
			{
				link.l1 = "Es ist vollbracht, Husky. Sie wurde zusammen mit einer Rolle Schiffsseide in ihrem Laderaum geliefert. Du bist frei, deine alte Kiste zu versenken.";
				link.l1.go = "Billy_11";
			}
			else
			{
				PlaySound("VOICE\English\LE\Billy\Billy_02.wav");
				link.l1 = "Ich bin noch dran. Warte.";
				link.l1.go = "Billy_10";
			}
		break;
		
		case "Billy_10":
			DialogExit();
			npchar.dialog.currentnode = "Billy_9";
		break;
		
		case "Billy_11":
			PlaySound("VOICE\English\LE\Billy\Billy_03.wav");
			pchar.quest.Mtraxx_BillyTimeOver.over = "yes"; //снять прерывание
            dialog.text = "Verdammt nochmal! Das sind die besten Neuigkeiten der letzten fünf Jahre im Leben des alten Billy! Heh, ein guter Grund, diese Flasche zu knacken...";
			link.l1 = "Ich werde passen. Was ist mit dem Seidenlieferanten?";
			link.l1.go = "Billy_12";
		break;
		
		case "Billy_12":
            dialog.text = "Schade, wir könnten auf meinen frischen neuen 'Fliegenden Fisch' trinken! Was auch immer... Hör zu, Sohn\nEine Brigantine unter der englischen Flagge kommt Mitte jeden Monats in die Portland-Bucht, irgendwann zwischen dem 10. und dem 15. Kein Rum für mich, bis ich tot bin, wenn sie wirklich Englisch ist! Ihr Name ist die 'Utrecht' und sie kommt aus Südwesten, wo Curacao liegt. Es ist klar ein niederländisches Schiffskapitän, das kann man sehen\nImmer die gleiche Gruppe von Leuten trifft sie am Ufer, angeführt von einem Meister dieses listigen Schiffbauers. Er ist ein Empfänger von Schiffsseide, welche die Niederländer dort entladen. Ich bin sicher, es ist die Schiffsseide, da nur die Niederländer sie so verpacken.";
			link.l1 = "Jeden Monat hast du gesagt?";
			link.l1.go = "Billy_13";
		break;
		
		case "Billy_13":
            dialog.text = "Tatsächlich, mein Junge, nicht ein einziger Monat fehlte im letzten Jahr. Wenn du dich mit dieser düsteren bärtigen Gesellschaft unterhalten willst, schlage ich vor, du wartest jeden Monat von der 10. bis zur 15. Nacht auf sie in der Portland Bucht. Ich schwöre darauf bei dem frischen neuen Seidentuch meines Langbootes!";
			link.l1 = "Heh! Sieht so aus, als ob mein Geld aus gutem Grund ausgegeben wurde. Gott sei mit dir, Billy, pass auf, dass du deinen alten Hintern von den Patrouillen fernhältst, sonst machst du mich wirklich sauer.";
			link.l1.go = "Billy_14";
		break;
		
		case "Billy_14":
            dialog.text = "Ha, der alte Billy wird gleich richtig Spaß an den Ufern Jamaikas machen! Gott segne dich, Kapitän! Gute Jagd!";
			link.l1 = "Gleichfalls, Billy!";
			link.l1.go = "Billy_15";
		break;
		
		case "Billy_15":
            DialogExit();
			npchar.lifeday = 0;
			pchar.questTemp.Mtraxx = "silk_8";
			chrDisableReloadToLocation = true;//закрыть локацию
			locations[FindLocation("shore35")].DisableEncounters = false; //энкаутеры открыть
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			AddDialogExitQuestFunction("Mtraxx_BillyTakeShip");
			AddQuestRecord("Roger_2", "9");
			//
			if (GetDataDay() >= 1 && GetDataDay() <= 9)
			{
				DoQuestFunctionDelay("Mtraxx_SilkCreateSmuggler", 1.0);
			}
			
			if (GetDataDay() >= 10 && GetDataDay() <= 15)
			{
				int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+2;
				if (iRank > 45) iRank = 45;
				Group_FindOrCreateGroup("Mtr_Utreht");
				sld = GetCharacter(NPC_GenerateCharacter("Cap_Utreht", "mercen_19", "man", "man", iRank, ENGLAND, -1, true, "quest"));
				FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, "Utrecht", CANNON_TYPE_CULVERINE_LBS18, 50, 50, 50);
				FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_13", "pistol5", "bullet", 100);
				sld.name = "Joachim";
				sld.lastname = "Gusen";
				sld.DontRansackCaptain = true;
				sld.AnalizeShips = true;
				sld.Coastal_Captain = true; // правки прогона 3
				DeleteAttribute(sld, "SaveItemsForDead");
				sld.Ship.Mode = "pirate";
				SetSailsColor(sld, 2);
				sld.ship.Crew.Morale = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Sailors = 60+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Cannoners = 40+MOD_SKILL_ENEMY_RATE*4;
				sld.Ship.Crew.Exp.Soldiers = 40+MOD_SKILL_ENEMY_RATE*4;
				if (MOD_SKILL_ENEMY_RATE > 4) SetCharacterPerk(sld, "MusketsShoot");
				SetCharacterGoods(sld, GOOD_SHIPSILK, 80);

				Group_AddCharacter("Mtr_Utreht", "Cap_Utreht");
				Group_SetGroupCommander("Mtr_Utreht", "Cap_Utreht");
				Group_SetTaskAttackInMap("Mtr_Utreht", PLAYER_GROUP);
				Group_SetAddress("Mtr_Utreht", "Jamaica", "Quest_Ships", "Quest_Ship_4");
				Group_SetTaskRunaway("Mtr_Utreht", PLAYER_GROUP);
				Group_LockTask("Mtr_Utreht");
				
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1 = "Group_Death";
				pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1.group = "Mtr_Utreht";
				pchar.quest.mtr_silksmuggler_AfterBattle.function = "Mtraxx_SilkSmugglerAfterBattle";
				
				SetTimerFunction("Mtraxx_SilkSmugglerFail", 0, 0, 2);
			}
			
			if (GetDataDay() >= 16 && GetDataDay() <= 20)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 15);
			}
			if (GetDataDay() >= 21 && GetDataDay() <= 26)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 10);
			}
			if (GetDataDay() >= 27 && GetDataDay() <= 31)
			{
				SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 5);
			}
		break;
		
		// мастеровой с верфи Порт-Ройаля
		case "Mtr_acceptor_fight":
            LAi_group_Delete("EnemyFight");
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation("shore36")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mtr_acceptor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_SilkWrongTalk");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Mtr_acceptor":
            dialog.text = "Hallo, Seemann, du bist gerade auf Jamaika angekommen, hm?";
			link.l1 = "Hm. Richtig. Was ist das Problem?";
			link.l1.go = "Mtr_acceptor_1";
		break;
		
		case "Mtr_acceptor_1":
            dialog.text = "Hast du etwas auf dem nahegelegenen Meer gesehen?";
			link.l1 = "Ja, habe ich. Eine Brigantine geriet in einen Kampf mit einer englischen Patrouillenkorvette. Die Briten haben sie hart getroffen, die Holländer haben ihre Ladung losgeworden, in dem Versuch zu fliehen.";
			link.l1.go = "Mtr_acceptor_2";
		break;
		
		case "Mtr_acceptor_2":
            dialog.text = "Warum bist du dir so sicher, dass sie eine Holländerin war? Kein vernünftiger Holländer würde es wagen, sich Port Royal so zu nähern...";
			link.l1 = "Sie hatte englische Farben, doch der Name... Die 'Utrecht'. Nicht sehr britisch, hm? Sie waren Holländer, sage ich dir, vielleicht sogar Schmuggler. Die Patrouille hat sie sicherlich erwartet.";
			link.l1.go = "Mtr_acceptor_3";
		break;
		
		case "Mtr_acceptor_3":
            dialog.text = "Verdammt!";
			link.l1 = "Sieht so aus, als wären Sie nicht gerade glücklich darüber...";
			link.l1.go = "Mtr_acceptor_4_1";
			link.l2 = "Hatten Sie hier auf diese Brigantine gewartet?";
			link.l2.go = "Mtr_acceptor_7";
		break;
		
		case "Mtr_acceptor_4_1":
            dialog.text = "Warum sollte ich das sein?";
			link.l1 = "Los geht's. Ich weiß, wer du bist. Du bist ein Vorarbeiter der Schiffswerft von Port Royal und du wartest auf eine ganz besondere Lieferung, die von der Brigantine geliefert werden soll.";
			link.l1.go = "Mtr_acceptor_wrong";
			link.l2 = "Es steht dir ins Gesicht geschrieben, genau da!";
			link.l2.go = "Mtr_acceptor_4_2";
		break;
		
		case "Mtr_acceptor_wrong":
            dialog.text = "Argh! Jungs, das ist eine Patrouille in Verkleidung! Schaltet sie aus und verschwindet zum Teufel hier weg!";
			link.l1 = "Scheiße! Warte, du bi...";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_4_2":
            dialog.text = "Unverschämt, 'Seewolf'? Pass auf deinen Mund auf oder...";
			link.l1 = "Komm schon. Du siehst offensichtlich verärgert aus. Hast du tatsächlich auf diese Holländer gewartet?";
			link.l1.go = "Mtr_acceptor_4_3";
			link.l2 = "Oder was? Wirst du mir eine Lebenslektion erteilen?";
			link.l2.go = "Mtr_acceptor_6";
		break;
		
		case "Mtr_acceptor_4_3":
            dialog.text = "Und was, wenn ich es war? Warum kümmert es dich?";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l1 = "Ich wirklich nicht. Sie sind hier die wartende Partei, nicht ich. Sie haben eine Ewigkeit vor sich.";
				link.l1.go = "Mtr_acceptor_4_4";
			}
			link.l2 = "Oh, ich habe jeden Grund, mich zu kümmern. Ich weiß, was im Frachtraum der Brigantine war. Schiffsseide. Du bist deswegen hier, richtig?";
			link.l2.go = "Mtr_acceptor_wrong";
		break;
		
		case "Mtr_acceptor_4_4":
            dialog.text = "Hm... Ewigkeit?";
			link.l1 = "Es dauert eine Ewigkeit, vom Meeresgrund zurückzukommen. Deine Brigantine wurde von einer Patrouillenkorvette versenkt, Kumpel. Einfach so. Obwohl, Krieg bringt sowohl Preise als auch Verluste. Ich werde eine gute Münze auf diesen versunkenen Holländer machen.";
			link.l1.go = "Mtr_acceptor_4_5";
		break;
		
		case "Mtr_acceptor_4_5":
            dialog.text = "Und wie genau, frage ich mich?";
			link.l1 = "Ich werde verkaufen, was sie über Bord geworfen haben, während sie versuchten zu fliehen. Fast alles ist verloren, aber kostbare Schiffsseide schwamm wie... Kork. Ich habe das Meiste davon geborgen, also gehe ich morgen in die Stadt, um einen Käufer zu finden. Man weiß nie, wo man gewinnt und wo man verliert.";
			link.l1.go = "Mtr_acceptor_4_6";
		break;
		
		case "Mtr_acceptor_4_6":
            dialog.text = "Warte!";
			link.l1 = "Verdammt! Was jetzt?";
			link.l1.go = "Mtr_acceptor_4_7";
		break;
		
		case "Mtr_acceptor_4_7":
            dialog.text = "Wie viel Seide konntest du sammeln?";
			link.l1 = "Und warum kümmern Sie sich darum? Das ist meine Seide! Oder bist du der Hund des Gouverneurs? Du bist de...";
			link.l1.go = "Mtr_acceptor_4_8";
		break;
		
		case "Mtr_acceptor_4_8":
            dialog.text = "Halte dein Schwert in der Scheide, Seemann. Ich bin kein Hund und kein Spitzel. Wir arbeiten in der lokalen Werft... Diese Seide war für uns und soweit ich verstehe, hast du sie jetzt. Ich werde dir alles abkaufen, wir brauchen diese Seide, Kumpel.";
			link.l1 = "Wirklich? Interessant... Wie viel?";
			link.l1.go = "Mtr_acceptor_4_9";
		break;
		
		case "Mtr_acceptor_4_9":
			i = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "Zweitausendfünfhundert für eine Rolle. Das ist ein guter Preis, du wirst keinen besseren finden.";
			link.l1 = "Sieht so aus, als hätte ich Glück! Ich habe "+FindRussianQtyString(i)+". Zeig mir das Geld und ich werde sofort anordnen, es an Land zu liefern.";
			if (i > 80) link.l1.go = "Mtr_acceptor_4_11";
			else link.l1.go = "Mtr_acceptor_4_10";
		break;
		
		case "Mtr_acceptor_4_10":
            dialog.text = "Abgemacht!";
			link.l1 = "..., Freund.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilk");
			AddCharacterExpToSkill(pchar, "Fortune", 300);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		case "Mtr_acceptor_4_11":
            dialog.text = "Hm... Joachim sollte nur achtzig Rollen liefern - unmöglich, dass du so viel bergen könntest... das bedeutet, du versuchst entweder, ein schmutziges Spiel zu spielen oder... du bist eine Ratte! Jungs, tötet ihn und verschwindet verdammt nochmal von hier!";
			link.l1 = "Verdammt!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_5":
            dialog.text = "";
			link.l1 = "Ein prächtiger Handel, Kumpel! Warum so düster? Besorgt über die Holländer auf dem Meeresgrund? Scheiße passiert, mach dir keine Sorgen!";
			link.l1.go = "Mtr_acceptor_5_1";
		break;
		
		case "Mtr_acceptor_5_1":
            dialog.text = "Ja, genau... Sie waren unser regulärer Lieferant. Wo sollen wir jetzt die Seide herkriegen? Wir haben immer zu wenig davon und der gesamte Handel steht unter direkter Kontrolle von Oberst D'Oyley. Verdammt...";
			link.l1 = "Hm... Hör zu, Freund, ich vermute, ich kann dir dabei helfen.";
			link.l1.go = "Mtr_acceptor_5_2";
		break;
		
		case "Mtr_acceptor_5_2":
            dialog.text = "Ach wirklich? Und wie stellen Sie sich vor, uns zu helfen? Werden Sie uns jeden Monat eine Lieferung von hundert Brötchen liefern?";
			link.l1 = "Ich? Hmm, wahrscheinlich nicht, aber Marcus Tyrex würde es tun. Hast du von ihm gehört?";
			link.l1.go = "Mtr_acceptor_5_3";
		break;
		
		case "Mtr_acceptor_5_3":
            dialog.text = "K-ha! Also, du bist ein Pirat?";
			link.l1 = "Nein, ich mache nur bei besonderen Gelegenheiten Geschäfte mit ihnen. Ich weiß sicher, dass Marcus ständig Schiffsladungen Seide erhält und sie an jeden verkauft, der es sich leisten kann. Und ich spreche hier nicht von 2500 Pesos pro Rolle, ich würde sagen, wenn du ihm für jede Rolle 25 Dublonen in Gold zahlen kannst, wird er dich darin ertränken, darauf kannst du zählen.";
			link.l1.go = "Mtr_acceptor_5_4";
		break;
		
		case "Mtr_acceptor_5_4":
            dialog.text = "Das sind interessante Neuigkeiten... Marcus Tyrex sagst du? Nur in Dublonen?..";
			link.l1 = "Komm schon, Kumpel, ist es dir wirklich wichtig, von wem du deine Seide bekommst? Und Geld ist Geld, du kannst Pesos immer in einer Bank gegen Dublonen eintauschen. Soll ich also ein oder zwei Worte über dich in die Ohren des Kodewächters flüstern? Ich gehe sowieso nach La Vega.";
			link.l1.go = "Mtr_acceptor_5_5";
		break;
		
		case "Mtr_acceptor_5_5":
            dialog.text = "Sehr gut. Lass uns einen Deal machen. Dies sind unsere Bedingungen: Eine Ladung von hundert Rollen jeden Monat zwischen dem 10. und 15. Wir werden hier warten... warte, lass uns den Treffpunkt ändern, dieser Ort ist jetzt kompromittiert. Wir werden am Kap Negril, in der Nähe von Maroon Town, warten, dort sollte es sicherer sein. Das Passwort - 'Ein Händler aus Lyon'.";
			link.l1 = "Abgemacht, Freund. Verdammte Reise war das! Tyrex wird mir ein oder zwei Dublonen für so einen Käufer zahlen! Ha-ha! Gut, ich sollte gehen. Warte nächsten Monat auf Tyrex's Schiff. Viel Glück für dich und deine Familie!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
		break;
		
		case "Mtr_acceptor_6":
            dialog.text = "Du wirst keine Lebenslektionen mehr brauchen, nachdem wir dir Anstand beigebracht haben.";
			link.l1 = "Willst du den Harten spielen, Zimmermann? Gut, warte auf deine Brigantine, obwohl es eine Weile dauern wird.";
			link.l1.go = "Mtr_acceptor_6_1";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "He, Lehrer, ich habe auch ein paar Lektionen für dich!";
				link.l2.go = "Mtr_acceptor_6_2";
			}
		break;
		
		case "Mtr_acceptor_6_1":
            dialog.text = "Tischler? Verdammt noch mal, wie weißt du das? K-ha! Verdammt, Jungs, das ist eine Patrouille in Verkleidung! Tötet ihn und verschwindet verdammt noch mal hier!";
			link.l1 = "Scheiße!";
			link.l1.go = "Mtr_acceptor_fight";
		break;
		
		case "Mtr_acceptor_6_2":
            dialog.text = "Lasst uns in Ruhe, du Fischschuppe, wir haben keine Zeit. Verschwinde!";
			link.l1 = "Bist du beschäftigt, auf ein bestimmtes holländisches Schiff zu warten? Viel Glück dabei. Du hast eine Ewigkeit vor dir.";
			link.l1.go = "Mtr_acceptor_4_4";
		break;
		
		case "Mtr_acceptor_7":
            dialog.text = "Wovon zum Teufel redest du?";
			link.l1 = "Ich verstehe. Aber, falls du es bist, vergiss es. Sie kommt nicht, dank einer Patrouillenkorvette. Ich habe durch ein Fernrohr das Ende eines Kampfes gesehen. Es passierte so schnell und nicht weit von hier";
			link.l1.go = "Mtr_acceptor_7_1";
		break;
		
		case "Mtr_acceptor_7_1":
            dialog.text = "Wieder einmal warten wir auf nichts und niemanden und...";
			link.l1 = "Schau, es ist mir wirklich scheißegal. Ich gehöre nicht zur Stadtwache und kümmere mich nicht um deine Machenschaften, ich bin selbst kein Engel. Wenn du schmuggelst - das ist dein Geschäft. Ich wollte dich nur warnen. Viel Glück, Kumpel.";
			link.l1.go = "Mtr_acceptor_7_2";
		break;
		
		case "Mtr_acceptor_7_2":
            dialog.text = "Warte... Bist du sicher, dass die 'Utrecht' gesunken ist?";
			link.l1 = "Absolut. Sie versuchte zu fliehen, warf alles weg, was sie in ihren Frachträumen hatte, sie verschonten nicht einmal kostbare Schiffsseide, aber solche drastischen Maßnahmen konnten gegen den Geschwindigkeitsvorteil einer Korvette nichts ausrichten.";
			link.l1.go = "Mtr_acceptor_7_3";
		break;
		
		case "Mtr_acceptor_7_3":
            dialog.text = "Wie schade... und was sollen wir ohne die Seide tun? Verdammt noch mal!";
			link.l1 = "Brauchst du Schiffsseide?";
			link.l1.go = "Mtr_acceptor_7_4";
		break;
		
		case "Mtr_acceptor_7_4":
            dialog.text = "Warum fragst du, verkaufst du es?";
			link.l1 = "Ich bin es nicht, aber ich kenne einen Mann, der es ist. Er sucht einen großzügigen und regelmäßigen Käufer. Glaubst du, du kannst dazu passen?";
			link.l1.go = "Mtr_acceptor_7_5";
		break;
		
		case "Mtr_acceptor_7_5":
            dialog.text = "Und wer ist dieser Mann?";
			link.l1 = "Marcus Tyrex, der Baron von La Vega, besser bekannt als der Code-Hüter. Er erhält ständig Lieferungen von Schiffsseide, also hat er immer etwas zu verkaufen. Ich nehme an, er wird in Erwägung ziehen, es auch an Sie zu verkaufen, wenn Ihr Preis hoch genug ist.";
			link.l1.go = "Mtr_acceptor_7_6";
		break;
		
		case "Mtr_acceptor_7_6":
            dialog.text = "Also bist du ein Pirat?";
			link.l1 = "Warum interessiert es dich? Ich kann einen Deal zwischen dir und Tyrex arrangieren, wenn du die Eier dazu hast. Wenn nicht - dann auf Wiedersehen.";
			link.l1.go = "Mtr_acceptor_7_7";
		break;
		
		case "Mtr_acceptor_7_7":
            dialog.text = "Fein-fein, werd nicht wütend. Sicher, ich mache es. Ich will einen Handel mit Tyrex abschließen. Aber was ist für dich drin?";
			link.l1 = "Wenn du einen guten Preis für die Ladung anbietest, werde ich wahrscheinlich von Marcus eine anständige Summe für meine Hilfe bekommen. Also, was wird es sein?";
			link.l1.go = "Mtr_acceptor_7_8";
		break;
		
		case "Mtr_acceptor_7_8":
            dialog.text = "Fünfundzwanzig Dublonen für eine Rolle. Das ist der beste Preis, den du bekommen kannst, vertrau mir darauf.";
			link.l1 = "Fünfundzwanzig Goldmünzen? Hm. Nicht schlecht. Ich glaube, Tyrex wird mir viel für einen solchen Käufer schulden. Sehr gutes Geschäft, ich werde es ihm mitteilen. Wenn du mich jedoch über den Preis belogen hast, dann bist du dran.";
			link.l1.go = "Mtr_acceptor_7_9";
		break;
		
		case "Mtr_acceptor_7_9":
            dialog.text = "Macht euch keine Sorgen, wir sind ehrliche Leute. Das sind unsere Bedingungen: Jeden Monat zwischen dem 10. und 15. ein Bündel von hundert Rollen. Wir werden hier warten... warte, lass uns den Treffpunkt ändern, dieser Ort ist jetzt kompromittiert. Wir werden am Kap Negril warten, in der Nähe von Maroon Stadt, es sollte dort sicherer sein. Das Passwort - 'Ein Kaufmann aus Lyon'.";
			link.l1 = "Verstanden. Warte auf die erste Lieferung nächsten Monat.";
			link.l1.go = "Mtr_acceptor_7_10";
		break;
		
		case "Mtr_acceptor_7_10":
            dialog.text = "Lass Tyrex wissen, dass er dieses Mal mehr Fracht mitbringen darf, wir sind diesen Monat ohne Seide geblieben.";
			link.l1 = "Ich werde. Gott beschütze dich, Freund.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
		
		// Тесак Пелли
		case "Pelly":
            dialog.text = "Ahoi! Was hat dich an Bord meines Schiffes gebracht, Freund?";
			link.l1 = "Hallo, Entermesser. Marcus Tyrex hat mich geschickt. Ein Marsch nach Maracaibo erwartet uns.";
			link.l1.go = "Pelly_1";
		break;
		
		case "Pelly_1":
            dialog.text = "A-ah, endlich. Also musst du mein neuer Boss für diese Reise sein. Gut. Wie lautet der Name meines neuen Admirals?";
			link.l1 = "Kapitän "+GetFullName(pchar)+".";
			link.l1.go = "Pelly_2";
		break;
		
		case "Pelly_2":
            dialog.text = "Befehle, Admiral "+GetFullName(pchar)+"?";
			link.l1 = "Wir werden getrennt zum Maracaibo See segeln. Du solltest dort nachts ankommen und heimlich in der Guajira Bucht anlanden. Warte dort auf mich und richte in der Zwischenzeit ein kleines Lager ein. Was mich betrifft, so werde ich im spanischen Hafen anlanden.";
			link.l1.go = "Pelly_3";
		break;
		
		case "Pelly_3":
            dialog.text = "Jawohl, Admiral!";
			link.l1 = "Wie lange wird es dauern, bis du dort bist?";
			link.l1.go = "Pelly_4";
		break;
		
		case "Pelly_4":
            dialog.text = "Hmmm... Es sollte ungefähr eine Woche dauern. Ein Tag weniger, ein Tag mehr, alles hängt vom Wind ab.";
			link.l1 = "Gut. Lassen wir dann keine Zeit verschwenden. Ich sehe dich in der Bucht von Guajira, Freund.";
			link.l1.go = "Pelly_5";
		break;
		
		case "Pelly_5":
            dialog.text = "Aye-aye, Admiral!";
			link.l1 = "...";
			link.l1.go = "Pelly_6";
		break;
		
		case "Pelly_6":
            DialogExit();
			AddQuestRecord("Roger_3", "3");
			LAi_CharacterDisableDialog(npchar);
			npchar.DontDeskTalk = true;
			Mtraxx_PlantContinue();
		break;
		
		case "Pelly_7":
            dialog.text = "Befehle, Admiral?";
			link.l1 = "Nichts im Moment. Ich bin beschäftigt mit unserer Operation.";
			link.l1.go = "Pelly_wait";
			if (pchar.questTemp.Mtraxx == "plant_3")
			{
				link.l1 = "Bereitet eine geräumige Truhe am Ufer vor. Wir werden darin Waffen für unsere gefangenen Brüder sammeln.";
				link.l1.go = "Pelly_7_1";
			}
			if (pchar.questTemp.Mtraxx == "plant_6" && CheckAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar"))
			{
				dialog.text = "Also, was ist los mit Handsome? Meine Hände jucken danach, etwas Don-Blut zu vergießen!";
				link.l1 = "Es ist komplizierter als wir dachten. Er sagte, die Wachen auf der Plantage sind zu wachsam. Die einzige Möglichkeit, Waffen einzuschleusen, besteht darin, sie in Waren zu verstecken. Wir müssen dringend eine Lieferung Kaffee, Kopra oder Vanille bekommen - der lokale Pflanzer handelt nur damit und sonst nichts.";
				link.l1.go = "Pelly_70";
				DelLandQuestMark(npchar);
			}
			if (pchar.questTemp.Mtraxx == "plant_8" && pchar.location.from_sea == "Shore37")
			{
				link.l1 = "Verlasst das Lager und sammelt eine Sturmgruppe. Es ist Zeit zu marschieren, wir greifen unter dem Schutz der Dunkelheit an.";
				link.l1.go = "Pelly_11";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Pelly_wait":
             DialogExit();
			 npchar.dialog.currentnode = "Pelly_7";
		break;
		
		case "Pelly_7_1":
            dialog.text = "Hör zu, Admiral, ich habe nachgedacht...";
			link.l1 = "Was ist das, Terrax bezahlt dich dafür zu denken anstatt mit deinem Säbel zu schwingen, eh, Entermesser?";
			link.l1.go = "Pelly_35";
		break;
		
		case "Pelly_8":
            dialog.text = "Ho! Ein Aufstand auf der Plantage, nicht wahr, Admiral? Flammen! Aus dieser Situation sollten wir etwas Gold herausholen!..";
			link.l1 = "Ich brauche eine Truhe am Ufer, Säbel.";
			link.l1.go = "Pelly_9";
		break;
		
		case "Pelly_9":
            dialog.text = "Sofort, Admiral!";
			link.l1 = "...";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_10":
            DialogExit();
			npchar.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_4";
			pchar.questTemp.Mtraxx.Chest = "true";
			// подгружаем сундук в локу и меняем локаторы
			int n = Findlocation("Shore37");
			Locations[n].models.always.locators = "shore03_q_locators";
			locations[n].models.always.chest = "chest_quest";
			Locations[n].models.always.chest.locator.group = "box";
			Locations[n].models.always.chest.locator.name = "private1";
			Locations[n].models.always.chest.tech = "DLightModel";
			DoQuestReloadToLocation("Shore37", "goto", "goto5", "Mtraxx_PlantChestReady");
		break;
		
		case "Pelly_11":
            dialog.text = "Sofort, Admiral!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantPrepareMarch");
		break;
		
		case "Pelly_12":
            dialog.text = "Die Männer sind bereit und vorbereitet, Admiral!";
			link.l1 = "Weiter!";
			link.l1.go = "Pelly_13";
		break;
		
		case "Pelly_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_14":
            dialog.text = "Admiral, es sieht so aus, als ob der Freund von Tyrex, den wir retten sollten, ... irgendwie tot ist.";
			link.l1 = "Ja, aber da konnte nichts gemacht werden. Du hast die Wachen gesehen, wir hatten Glück, am Leben zu bleiben.";
			link.l1.go = "Pelly_15";
		break;
		
		case "Pelly_15":
            dialog.text = "Admiral, Marcus wird wütend auf Sie sein. Gehen Sie jetzt nicht zu ihm. Ich gehe. Sie sollten auch gehen.";
			link.l1 = "Ja...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantFailFinal");
		break;
		
		case "Pelly_16":
            dialog.text = "Schlechte Nachrichten, Admiral. Eine spanische Eskadron kommt von Osten auf uns zu. Wir haben keine Zeit zu fliehen.";
			link.l1 = "Wie viele von ihnen?";
			link.l1.go = "Pelly_17";
		break;
		
		case "Pelly_17":
            dialog.text = "Drei Schiffe. Viele Kanonen. Wir sind am Arsch."; // лесникПОСЛЕДНЕЕ
			link.l1 = "Wir werden sehen.";// Жан, ты отправляйся на борт к Тесаку. Тесак, поднимешь испанский флаг и на всех парусах прочь отсюда - глядишь, за торговца сойдёшь. А я пойду прямо на испанцев - отвлеку их от вас. Увидимся в Ла Веге у Тиракса.";
			link.l1.go = "Pelly_181";
		break;
		case "Pelly_181":
	    	DialogExit();
		   sld = characterFromId("Mrt_Rocur");
		   sld.Dialog.currentnode = "Pelly_182";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_182":
		   dialog.text = ""; 
		   link.l1 = "Jean, du gehst zu Cutlass' Schiff.";
		   link.l1.go = "Pelly_183"; 
		break;
		case "Pelly_183":
		     DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_18";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "Pelly_18":
            dialog.text = "";//"Но...";
			link.l1 = "Säbel, du solltest die spanische Flagge hissen und dich zum Teufel scheren. Ich werde sie von dir ablenken. Wir sehen uns alle in La Vega.";//"Отставить! Тесак, за Жана Пикара отвечаешь головой перед Тираксом. Все на борт!";
			link.l1.go = "Pelly_19";
		break;
		
		case "Pelly_19":
            dialog.text = "Aber...";
			link.l1 = "Keine Widerrede! Cutlass, dein Hintern steht auf dem Spiel, wenn Picard nicht zu Tyrex's Ort kommt. Alle an Bord!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PlantSeaEscape");
		break;
		
		case "Pelly_20":
            dialog.text = "Befehle Admiral?";
			link.l1 = "Macht euch bereit zu kämpfen. Greift sie auf mein Kommando an!";
			link.l1.go = "Pelly_21";
		break;
		
		case "Pelly_21":
            dialog.text = "Aye-aye Admiral... auf Ihr Kommando!";
			link.l1 = "...";
			link.l1.go = "Pelly_22";
		break;
		
		case "Pelly_22":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
		break;
		
		case "Pelly_23":
            dialog.text = "Ho-ho! Hallo Prinz. Was hat dich nach Tortuga gebracht?";
			link.l1 = "Schon wieder Marcus's Aufgabe. Hör zu, Entermesser, warum lässt mich der Mistkerl in diesem Haus nicht rein?";
			link.l1.go = "Pelly_24";
		break;
		
		case "Pelly_24":
            dialog.text = "Gaspard Goldzähne? Er arbeitet nur mit vertrauenswürdigen Kameraden. Andere bräuchten eine Empfehlung, um mit ihm zu arbeiten. Möchtest du einige glänzende Kleinigkeiten verkaufen? Ich könnte für dich bürgen, wenn du willst...";
			link.l1 = "Also ist er ein Wucherer? Was ist sein Interesse?";
			link.l1.go = "Pelly_25";
		break;
		
		case "Pelly_25":
            dialog.text = "Bruder, dir fehlt etwas. Gaspard ist kein Wucherer, du solltest gehen zu "+GetFullName(characterFromId("Tortuga_Wucherer"))+" wenn du einen brauchst. Goldzähne kauft Edelsteine und Schmuck aller Art. Übrigens, er zahlt gut und stellt nie dumme Fragen. Jeder Piratenkapitän ist ein Kunde von ihm.";
			link.l1 = "Ich verstehe... Mir wurde gesagt, dass einige von ihnen sogar ihr Geld ihm anvertrauen...";
			link.l1.go = "Pelly_26";
		break;
		
		case "Pelly_26":
            dialog.text = "Ha-ha! Es war ein Lügner, der dir das erzählt hat, geh und spuck ihm in seine schamlosen Augen. Gaspard arbeitet nur mit Schmuck, das hat er immer getan. Warum sollte er Probleme mit fremdem Geld brauchen?";
			link.l1 = "Ich verstehe. Danke Cutlass, wir sehen uns auf dem Meer!";
			link.l1.go = "Pelly_27";
			link.l2 = "Hmm, tatsächlich. Also, er kauft Nippes? Interessant... Du sagst, du kannst ein gutes Wort für mich einlegen?";
			link.l2.go = "Pelly_27z";
		break;
		
		case "Pelly_27":
            dialog.text = "Auf Wiedersehen, Prinz.";
			link.l1 = "..., Freund.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookThird");
		break;
		
		case "Pelly_27z":
            dialog.text = "Natürlich! Du bist jetzt einer von uns, hehe! Warte hier einen Moment.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekPellyTalkGems");
		break;
		
		case "Pelly_28z":
            dialog.text = "Alles ist geregelt! Jetzt weiß Goldzahn, dass Charlie Prince vielleicht zu ihm kommt, um Nippes zu verkaufen. Denken Sie nur daran, dass sein Preis, obwohl gut, immer noch niedriger ist als das, was diese geizigen Wucherer zahlen. Aber er kauft alles tonnenweise! Und ohne unnötige Fragen, wie ich bereits sagte.";
			link.l1 = "Das ist mein hübscher Bursche! Gut gemacht Paul! Jetzt habe ich einen Ort, um all die Beute abzuladen!";
			link.l1.go = "Pelly_29z";
		break;
		
		case "Pelly_29z":
            dialog.text = "Nein, Jean Picard ist der 'Hübsche', ich bin der 'Säbel', haha! Auf Wiedersehen, Prinz!";
			link.l1 = "Danke, Entermesser, viel Glück auf See!";
			link.l1.go = "Pelly_27";
		break;
		
		case "Pelly_28":
			PlaySound("VOICE\English\LE\Pelly\Pelly_03.wav");
            dialog.text = "Ich habe drei Vögel für dich, Prinz. Gefunden sie versteckt in Schränken und unter einem Bett. Hübsche Dinger, nicht wahr? Ha-ha-ha!";
			link.l1 = "Ich sage, sie sind es in der Tat. Und sie sind auch gut gepflegt. Don Sturkopf muss sich sehr um sie kümmern.";
			link.l1.go = "Pelly_29";
		break;
		
		case "Pelly_29":
            DialogExit();
			sld = CharacterFromID("Mtr_CartahenaMayorClone");
			sld.dialog.currentnode = "CartahenaMayor_8";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Pelly_30":
			PlaySound("VOICE\English\LE\Pelly\Pelly_04.wav");
            dialog.text = "Alle hagel! Was zum Teufel machst du hier, Prinz?";
			link.l1 = "Säbel?.. Ich folgte den Stimmen und dem Lärm, aber nie hätte ich gedacht, dass du es bist. Wie zur Hölle bist du hier gelandet?";
			link.l1.go = "Pelly_31";
			QuestPointerDelLoc("Judgement_dungeon_01", "reload", "reload2_back");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload2");
			QuestPointerDelLoc("Judgement_dungeon_05", "quest", "pelly");
		break;
		
		case "Pelly_31":
            dialog.text = "Nein, warum bist du hier! Du bist immer in der Nähe! Tyrex muss dich für diesen Schatz geschickt haben, oder? Verdammt, ich bin schon wieder zu spät...";
			link.l1 = "Tyrex? Nein... Ich habe eine Karte von einer Schlampe gekauft. Sie hat wahrscheinlich auch dir eine Kopie verkauft, hm? Auf Tortuga? Was für eine gerissene Hündin. Sie hat jedoch nicht gelogen - schaut euch diesen Haufen Gold an! Ich werde mit mehr Leuten zurückkommen, um all dies zu tragen...";
			link.l1.go = "Pelly_32";
		break;
		
		case "Pelly_32":
            dialog.text = "Verdammt ja, es ist ein Haufen Gold! Aber es gehört weder dir noch Tyrex! Ich habe es zuerst gefunden! Es ist meins! Es ist egal, wie ich davon erfahren habe! Es geht dich nichts an!";
			link.l1 = "Beruhige dich Cutlass, warum bist du so wütend? Sieh dir diesen Haufen an - da muss eine Million sein. Vielleicht sogar mehr! Genug für uns beide!";
			link.l1.go = "Pelly_33";
		break;
		
		case "Pelly_33":
            dialog.text = "Du bekommst immer ein besseres Stück vom Kuchen, Prinz! Aber nicht dieses Mal! Der Schatz gehört mir! Ich habe ihn zuerst gefunden!";
			link.l1 = "Verdammt noch mal, Paul, was stimmt nicht mit dir? Können wir hier keinen Deal machen? Selbst die Hälfte dieses Goldes ist ein Vermögen. Du hast noch nie eine solche Summe in den Händen gehabt. Außerdem könnte ich eines Tages einen profitablen Hinweis finden und dir davon erzählen.";
			link.l1.go = "Pelly_34";
		break;
		
		case "Pelly_34":
            dialog.text = "Willst du mich fertig machen, Prinz? Keine Chance! Ich werde dir nicht einen einzigen Taler geben, nicht eine einzige Guinea! Du bist zu spät!\nA-ah, ich sehe, was du vorhast! Keine Chance, dass du dieses Gold bekommst!!!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionPellyFight");
		break;
		
		case "Pelly_35": //
            dialog.text = "Lustig. Wirklich. Du bist ein Komiker, Admiral. Aber es stimmt - Marcus mag es nicht, wenn man versucht, ihn zu überlisten, so wie du. Aber er schätzt kluge Männer.";
			link.l1 = "Also gut, also gut. Was hast du also auf dem Herzen?";
			link.l1.go = "Pelly_36";
		break;
		
		case "Pelly_36":
            dialog.text = "Etwas, woran du und Handsome ganz offensichtlich nicht gedacht habt. Ihr plant einen Aufstand auf der Plantage. Tolle Idee - wenn das Ziel Plünderung oder Chaos stiften wäre. Aber...";
			link.l1 = "Aber was? Du gegen den Aufstand? Erschreckend?";
			link.l1.go = "Pelly_37";
		break;
		
		case "Pelly_37":
            dialog.text = "Ich? Ha! Niemals. Aber denk mal nach, was passiert, wenn Handsome während des Gemetzels sein Ende findet. Was sagen wir Marcus? Ich sag dir was - es wird keine Rolle spielen, was wir sagen. Er wird uns sowieso häuten.";
			link.l1 = "Hmm. Also was ist dein genialer Plan? Wir müssen ihn irgendwie rauskriegen.";
			link.l1.go = "Pelly_38";
		break;
		
		case "Pelly_38":
            dialog.text = "Wir tun es. Deshalb... warum kaufen wir ihn nicht? Offiziell, das heißt. Eine Handvoll Gold kann jeden von diesen Bastarden kaufen - sogar ihre eigenen Mütter. Was soll man über den armen Jean sagen?";
			link.l1 = "Ha! Entermesser, schlägst du ernsthaft vor, dass ich auf eine Plantage gehe und frage, ob ich Picard kaufen kann? Soll ich ihnen auch sagen, für wen ich arbeite, nur zum Spaß? Du hast den Verstand verloren?";
			link.l1.go = "Pelly_39";
		break;
		
		case "Pelly_39":
            dialog.text = "Es besteht keine Notwendigkeit, das zu sagen. Tatsächlich ganz das Gegenteil - gib vor, du seist ein Händler. Sicher, du hast den Bauch nicht für die Rolle, aber du siehst auch nicht wie ein Pirat aus. Nichts für ungut, Admiral, aber es ist die Wahrheit. Schlendere einfach auf diese Plantage, wirke selbstbewusst und frage nach Jean. Der Besitzer könnte vermuten, wer du bist, aber er wird es nicht zeigen. Wie ich schon sagte - eine Handvoll Gold verschließt Münder.";
			link.l1 = "Und wie viel würde uns diese... goldene Hand kosten? Der ganze Berg?";
			link.l1.go = "Pelly_40";
		break;
		
		case "Pelly_40":
            dialog.text = "Vielleicht ja. Aber besser, man trennt sich von Gold als vom Kopf. Ich habe nicht untätig herumgesessen, während du an Land warst - Ich habe mich in etwas weniger Piratenhaftes verwandelt und mich nach der Plantage und ihrem bescheidenen Besitzer erkundigt.";
			link.l1 = "Und was hast du gefunden, Entermesser?";
			link.l1.go = "Pelly_41";
		break;
		
		case "Pelly_41":
            dialog.text = "Marktpreise, sozusagen. Dies ist nicht das erste Mal, dass ein wertvoller Gefangener in seinen Schoß gefallen ist. Normalerweise landen sie am Galgen oder schlimmer - in den Verliesen der Inquisition.";
			link.l1 = "Und für wie viel verkauft er sie?";
			link.l1.go = "Pelly_42";
		break;
		
		case "Pelly_42":
            dialog.text = "Für jemanden Wichtiges? Fünfhundert Münzen. Natürlich in Dublonen.";
			link.l1 = "FÜNFHUNDERT?!";
			link.l1.go = "Pelly_43";
		break;
		
		case "Pelly_43":
            dialog.text = "Pflanzer, was hast du erwartet?";
			link.l1 = "Für diesen Preis könnte ich eine kleine Armee ausstatten! Warum zum Teufel horte ich dann ein Arsenal auf meinem Schiff für einen Aufstand? Das wäre genug für einen kleinen Krieg.";
			link.l1.go = "Pelly_44";
		break;
		
		case "Pelly_44":
            dialog.text = "Die Waffen werden später für deine Mannschaft nützlich sein, unabhängig davon. Also, was sagst du?";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "(Vertrauenswürdig) Ich sage nur, es wäre lustig, wenn Terrax' Belohnung weniger wäre als das, was wir hier ausgeben. Aber du hast recht - unser Leben ist mehr wert. Ich habe die Dublonen.";
					link.l1.go = "Pelly_45";
				}
				link.l2 = "Ich habe gerade nicht so einen goldenen Berg.";
				link.l2.go = "Pelly_44_1";
				notification("Trustworthy", "Trustworthy");
			}
			else notification("Perk Check Failed", "Trustworthy");
			link.l3 = "Weißt du was, Entermesser? Vergiss es. Sind wir Piraten oder was? Und Jean? Oder ist sein hübsches Gesicht sein einziger Vorzug? Mach eine Kiste fertig - wir halten uns an den ursprünglichen Plan.";
			link.l3.go = "Pelly_62";
		break;
		
		case "Pelly_44_1":
            dialog.text = "Ich wäre überrascht, wenn du das tun würdest - es ist eine riesige Summe. Gut, wenn du bereit bist, oder wenn du etwas Besseres findest, komm und such mich.";
			link.l1 = "Wird gemacht. Warte hier.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_44_2":
			dialog.text = "Nun, Admiral, haben Sie genug Gold zusammengekratzt, um Picard zu retten?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Ja, ich habe es endlich geschafft. Hoffen wir, dass es funktioniert.";
				link.l1.go = "Pelly_45";
			}
			link.l2 = "Ich arbeite noch daran, Entermesser.";
			link.l2.go = "exit";
			link.l3 = "Ich gebe mein hart verdientes Geld nicht an diese gierigen Pflanzer! Macht die Truhe bereit - wir werden uns wie Gentlemen des Glücks verhalten. Das ist meine Entscheidung.";
			link.l3.go = "Pelly_9";
			NextDiag.TempNode = "Pelly_44_2";
		break;
		
		case "Pelly_45":
            dialog.text = "Woah. Du bist neu in unserer Mannschaft und wirfst schon mit so viel Geld um dich!";
			link.l1 = "Geld ist nicht alles. Aber in Terrax' Ruhm zu schwelgen? Unbezahlbar.";
			link.l1.go = "Pelly_46";
			pchar.questTemp.mtraxx_PlantVykup = true;
		break;
		
		case "Pelly_46":
            dialog.text = "Mit dem kann man nicht streiten. Aber wie Sie sagten, es geht nicht nur um Geld - es gibt noch etwas anderes Wichtiges, Admiral.";
			link.l1 = "Ich bin jetzt neugierig. Was?";
			link.l1.go = "Pelly_47";
		break;
		
		case "Pelly_47":
            dialog.text = "Ich habe dir gesagt, dass ich alles über die Plantage in Erfahrung gebracht habe. Einschließlich der Waren, die hier gefragt sind und auf dem Markt zirkulieren. Wenn du dich als rechtmäßiger Händler ausgeben willst, solltest du dich besser mit denen eindecken, anstatt einfach einen Haufen Gold auf den Schreibtisch des Pflanzers zu knallen.";
			link.l1 = "Macht Sinn. Um welche Art von Waren sprechen wir?";
			link.l1.go = "Pelly_48";
		break;
		
		case "Pelly_48":
            dialog.text = "Nun, abgesehen von lebenden Waren, heh-heh, kauft, handelt und verkauft der lokale Plantagenbesitzer Kaffee, Kopra und Vanille. Also...";
			link.l1 = "Ich muss mir schnell irgendwo welche besorgen. Oder ich überfalle eine Karawane und hoffe, dass sie das hat, was ich brauche.";
			link.l1.go = "Pelly_49";
		break;
		
		case "Pelly_49":
            dialog.text = "Nicht irgendein Karawan. Es tut mir leid, mich davon zu trennen, aber ich habe einen Vorlauf für mich selbst gespart. Eine Karawane, die genau das trägt, was du brauchst, wird bald auftauchen. Aber es gibt einen Haken...";
			link.l1 = "Oh, was jetzt?";
			link.l1.go = "Pelly_50";
		break;
		
		case "Pelly_50":
            dialog.text = "Es steht unter der französischen Flagge.";
			link.l1 = "Was?!";
			link.l1.go = "Pelly_51";
		break;
		
		case "Pelly_51":
            dialog.text = "Ich verstehe Ihren Frust, ha-ha. Die Entscheidung liegt bei Ihnen... Admiral. Möchten Sie die Details?";
			link.l1 = "Verdammt... Also gut, raus damit. Wir haben nicht viel Zeit - wenn du oder ich nicht an ihnen knabbern, wird es jemand anders tun.";
			link.l1.go = "Pelly_52";
			link.l2 = "Ich berühre die Franzosen nicht, es sei denn, ich habe keine andere Wahl. Ende der Diskussion.";
			link.l2.go = "Pelly_51_1";
		break;
		
		case "Pelly_51_1":
            dialog.text = "Dann solltest du besser anfangen, all diese Waren selbst und schnell zu sammeln, bevor Pretty Boy an jemanden verkauft wird. Ich kann hier auch nicht ewig herumhängen.";
			link.l1 = "Das dachte ich mir.";
			link.l1.go = "Pelly_51_2";
		break;
		
		case "Pelly_51_2": // добываем товары сами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
			//DoQuestCheckDelay("Mtraxx_PlantCaravanGuadeloupe", 1.0);
		break;
		
		case "Pelly_52":
            dialog.text = "So ist es recht! Ich wusste, dass du es in dir hast... Admiral. Also, hier ist der Deal: Mein zuverlässiger Kontakt hat kürzlich berichtet, dass in etwa zwei Wochen ein französischer Karawanentransport mit Kaffee und Gewürzen in den Gewässern von Guadeloupe auftauchen wird. Es ist groß und gut bewaffnet, also bereite dich gründlich vor.";
			link.l1 = "Welche andere Wahl habe ich.";
			link.l1.go = "Pelly_53";
		break;
		
		case "Pelly_53": // наводка на караван с нужными товарами
            DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("Roger_3", "28");
			//if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup")) AddQuestUserData("Roger_3", "sText", "Who would've thought that among the captains of Terrax, there'd be someone with at least the spark of a negotiator or a true entrepreneurial streak? That person turned out to be my temporary companion, Paul "Cutlass." Understanding the consequences of Marcus's wrath if we fail his assignment, Cutlass suggested... officially buying Picard from the plantation owner. While I scouted the situation and spoke with Jean, Cutlass didn't waste time either. He discovered that the plantation owner frequently sells valuable captives, with the average price for such transactions being around 500 doubloons - a small fortune. But Paul is right - it's better to do this than risk Picard being killed by a stray bullet or blade. Now all that's left is to load up on the plantation's usual trade goods - be it coffee, copra, or vanilla - in large quantities.");
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
			SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
			//DoQuestCheckDelay("Mtraxx_PlantCaravanGuadeloupe", 1.0);
		break;
		
		case "Pelly_54": // провал выкупа Красавчика
            dialog.text = "Sie sehen niedergeschlagen aus, Admiral. Wo ist der Hübsche? Ist alles den Bach runter?";
			link.l1 = "Allerdings. Ich habe gutes Geld verdient, aber dieser sture Esel weigerte sich, mir Picard zu verkaufen - selbst für einen Haufen Dublonen!";
			link.l1.go = "Pelly_55";
		break;
		
		case "Pelly_55":
            dialog.text = "Was für ein Narr! Was jetzt?";
			link.l1 = "Ich habe bereits mit dem Pflanzer vereinbart, die Waren zu entladen. Wir müssen zum ursprünglichen Plan zurückkehren - es ist jetzt oder nie!";
			link.l1.go = "Pelly_56";
		break;
		
		case "Pelly_56":
            dialog.text = "Aber wir haben noch nichts für Handsome und die anderen vorbereitet!";
			link.l1 = "Keine Zeit! Komm an Bord der Schiffe - wir werden Waffen und Medizin aus unseren Laderäumen in die Säcke mit Waren schleusen. Und vergiss nicht, die spanische Flagge zu hissen!";
			link.l1.go = "Pelly_57";
		break;
		
		case "Pelly_57":
            dialog.text = "Hört sich nach einem Plan an.";
			link.l1 = "So oder so, wir haben keine Zeit für etwas anderes. Beweg dich! Das Abladen passiert bald.";
			link.l1.go = "Pelly_58";
		break;
		
		case "Pelly_58":
            DialogExit();
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 1.0);
		break;
		
		case "Pelly_59":
            dialog.text = "Schau mal, wer da ist! Ein Schönling! Und angesichts deines unversehrten Gesichts und deines lässigen Gangs nehme ich an, dass alles reibungslos verlaufen ist?";
			link.l1 = "Gelinde gesagt ist es reibungslos verlaufen - ich habe nicht nur einen Kampf vermieden und Jean zurückgekauft, sondern auch noch etwas Geld verdient. Dein Plan hat einwandfrei funktioniert, Paul. Alles ruhig am Horizont?";
			link.l1.go = "Pelly_60";
		break;
		
		case "Pelly_60":
            dialog.text = "So leise wie möglich. Gehst du zurück zu Marcus?";
			link.l1 = "Richtig.";
			link.l1.go = "Pelly_61";
		break;
		
		case "Pelly_61":
            DialogExit();
			DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("shore37", "boat", false);
			bQuestDisableMapEnter = false;
			AddQuestRecord("Roger_3", "29");
			pchar.questTemp.Mtraxx = "plant_success";
			QuestSetCurrentNode("Terrax", "mtraxx_27");
			//SetFunctionTimerCondition("Mtraxx_PlantGoHomeOver", 0, 0, 40, false);
			SetFunctionTimerCondition("Mtraxx_PlantOpenMaracaibo", 0, 0, 5, false);
			
			sld = characterFromId("Mtr_plantation_boss");
			sld.lifeday = 0;
			
			sld = &Locations[FindLocation("shore37")];
			sld.DisableEncounters = false;
			sld = ItemsFromID("fire");
			sld.shown = false;
			DeleteAttribute(sld, "fire");
			for (i=1; i<=4; i++)
			{
				if (GetCharacterIndex("Pelly_sailor_"+i) != -1)
				{
					sld = characterFromId("Pelly_sailor_"+i);
					sld.lifeday = 0;
					LAi_SetActorType(sld);
					LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 5);
				}
			}
			sld = characterFromId("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "OpenTheDoors", 5);
			sld = characterFromId("mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 5);
		break;
		
		case "Pelly_62":
            dialog.text = "Hmm, wie du willst, Admiral. Aber wenn Handsome etwas passiert, werde ich sicherstellen, dass Terrax weiß, dass du meinen Rat ignoriert hast. Ist alles bereit für den Ausbruch?";
			link.l1 = "Lass mich nachzählen und prüfen, was ich in der Truhe habe.";
			link.l1.go = "Pelly_63";
		break;
		
		case "Pelly_63":
            dialog.text = "Sei dir dessen sicher. Ich kann helfen, für eine bescheidene Gebühr und um meine Mühen zu decken, heh-heh.";
			link.l1 = "Wie ist das?";
			link.l1.go = "Pelly_64";
		break;
		
		case "Pelly_64":
            dialog.text = "Ich habe einen Kontakt, einen Waffenschmuggler in Maracaibo. Ich werde mich verkleiden, einschleichen, ihn bezahlen und arrangieren, dass die Waffen hierher geschmuggelt werden. Aber es wird dich kosten - genau gesagt, Gold-Dublonen.";
			link.l1 = "Und warum hast du mich diesem Kerl nicht früher vorgestellt? Wie viel wird mich das kosten?";
			link.l1.go = "Pelly_65";
		break;
		
		case "Pelly_65":
            dialog.text = "Soll ich dich auch all meinen Informanten vorstellen? Gut. Mit Ausgaben, Risiken und meinem Anteil... es wird ungefähr so viel kosten wie das Lösegeld für Handsome.";
			link.l1 = "Säbel, fürchte Gott...";
			link.l1.go = "Pelly_66";
		break;
		
		case "Pelly_66":
            dialog.text = "Ich fürchte weder Gott noch dich, Admiral. Aber Marcus' Zorn, wenn wir es nicht schaffen, Jean zu retten? Das ist eine andere Geschichte. Also, was wird es sein? Brauchst du Hilfe mit der Truhe?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "In Ordnung, mach weiter - schon genug Zeit ist verschwendet worden. Hier, das sollte die richtige Menge sein.";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "Das ist viel Geld, Paul. Ich muss darüber nachdenken.";
			link.l2.go = "Pelly_67";
			link.l3 = "Das ist viel zu teuer für eine kleine Partie Waffen, die ich im Großhandel viel günstiger kaufen kann! Nein danke, ich werde das selbst in die Hand nehmen.";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_67":
            dialog.text = "Nun, denk schon. Aber erinnere dich - während du nachdenkst, erhöht sich die Anzahl der Prellungen im Gesicht und am Körper von Handsome stündlich, heh-heh-heh.";
			link.l1 = "Ich werde dir die Dublonen besorgen...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Pelly_67_2";
		break;
		
		case "Pelly_67_1":
            dialog.text = "Es geht nicht um die Größe der Lieferung - es geht um die Zeit und die Risiken. Aber mach, wie du denkst.";
			link.l1 = "Vertrau mir, ich weiß. Mach einfach die Kiste bereit - Ich kümmere mich um den Rest.";
			link.l1.go = "Pelly_10";
		break;
		
		case "Pelly_67_2":
            dialog.text = "Bereit, Admiral? Brauchen Sie Hilfe mit Waffen, oder fehlt Ihnen noch Gold?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "Endlich genug bekommen! Nimm es und kläre das endlich - es geht mir auf die Nerven.";
				link.l1.go = "Pelly_68";
			}
			link.l2 = "Halte den Ton, Entermesser. Ich bin bereit, aber ich brauche mehr Zeit, um das Geld aufzutreiben.";
			link.l2.go = "Pelly_67";
			link.l3 = "Das ist viel zu teuer für eine kleine Partie Waffen, die ich viel günstiger im Großhandel kaufen kann! Nein danke, ich kümmere mich selbst darum.";
			link.l3.go = "Pelly_67_1";
		break;
		
		case "Pelly_68":
            dialog.text = "Oh, was für ein Haufen Dublonen das ist! Aber mach dir keine Sorgen - jede Münze wird für den Plan verwendet. Andernfalls würde Marcus mich später aus dem Grab schaufeln, heh-heh. Nun geh zu Handsome, Admiral, und sag ihm, alles ist bereit.";
			link.l1 = "Ich bin derjenige, der hier Befehle gibt. Jetzt, beweg dich.";
			link.l1.go = "Pelly_69";
			RemoveDublonsFromPCharTotal(500);
		break;
		
		case "Pelly_69":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.dialog.currentnode = "Pelly_7";
			pchar.questTemp.Mtraxx = "plant_5";
			AddQuestRecord("Roger_3", "30");
			sld = characterFromId("Mrt_Rocur");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "rocur_wait";
			sld.greeting = "Rocur_02";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Pelly_70":
            dialog.text = "Ja, das ist ein Problem. Was ist Ihr Plan, Admiral?\nIch habe alles über die Plantage in Erfahrung gebracht. Einschließlich welche Waren hier gefragt sind und auf dem Markt zirkulieren. Wenn Sie sich als legitimer Händler ausgeben wollen, sollten Sie sich besser mit diesen eindecken, anstatt einfach einen Haufen Gold auf den Schreibtisch des Pflanzers zu knallen.";
			link.l1 = "Macht Sinn. Um welche Art von Waren sprechen wir?";
			link.l1.go = "Pelly_48";
			DeleteAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar");
		break;
		
		// Жан Пикар
		case "rocur":
            dialog.text = "Was willst du von mir?";
			link.l1 = "Mein Freund, ich suche nach Jean Picard. Ist es möglich, dass du denselben Namen trägst?";
			link.l1.go = "rocur_1";
		break;
		
		case "rocur_1":
            dialog.text = "Es gibt eine Chance. Allerdings erinnere ich mich nicht an dein Gesicht.";
			link.l1 = "Sei nicht zu rau, Jean. Ich wurde von Marcus Tyrex hierher geschickt. Meine Befehle sind, dich hier rauszuholen.";
			link.l1.go = "rocur_2";
		break;
		
		case "rocur_2":
            dialog.text = "Marcus? Tsh-sh... Ruhig. Es tut mir leid, Freund, ich wusste das nicht. Aber wir sollten hier nicht reden, verdammte Wachen sind überall und sie hören immer zu... Ich sehe, du bist ein willkommener Gast bei den Spaniern, finde mich in einer der Hütten in der Nacht und wir werden reden. Ich werde auf dich warten, Bruder.";
			link.l1 = "...";
			link.l1.go = "rocur_3";
		break;
		
		case "rocur_3":
            DialogExit();
			AddQuestRecord("Roger_3", "6");
			LAi_CharacterDisableDialog(npchar);
			Mtraxx_PlantMakeMaxRocurClone();
		break;
		
		case "rocur_4":
            dialog.text = "Nun, es ist sicher hier... Wie ist dein Name, Bruder?";
			link.l1 = "Kapitän "+GetFullName(pchar)+". Jetzt erzähl mir, wie du in diesen Scheiß hineingeraten bist. Tyrex will alles wissen.";
			link.l1.go = "rocur_5";
		break;
		
		case "rocur_5":
            dialog.text = "Ich wurde von einem Fremden in einer Taverne in Willemstad angesprochen... Er bat mich, sein Begleiter beim Plündern einiger niederländischen Karawane zu sein. Ich hatte eine Brigantine, er hatte einen Polacre, einen sehr einzigartigen dazu. Also verfolgten wir eine Karawane nicht weit von Caracas und plünderten sie... Es war Nacht, wir teilten die Beute, als plötzlich ein massives spanisches Galeon in der Dunkelheit auftauchte. \nMein Begleiter floh und ich ebenfalls. Aber es gab keine Möglichkeit für meine beschädigte Brigantine, vor einem Galeon und zwei anderen Schiffen zu fliehen. Sie enterten uns und verkauften alle Überlebenden wie Vieh an diesen Ort.";
			link.l1 = "Ich verstehe. Sie denken, es war ein Unfall? Ich spreche von der Galeone.";
			link.l1.go = "rocur_6";
		break;
		
		case "rocur_6":
            dialog.text = "Zum Teufel, wenn ich das wüsste. Sie könnten einen Schusswechsel gehört haben, es war nicht weit vom Hauptplatz.";
			link.l1 = "Hmm. Es ist möglich. Hast du deinen ehemaligen Begleiter schon einmal getroffen? Wer ist er?";
			link.l1.go = "rocur_7";
		break;
		
		case "rocur_7":
            dialog.text = "Noch nie zuvor getroffen. Sagte, sein Name sei Ignacio Marco, ein Freibeuter aus England. Er machte den Eindruck eines ernsten Mannes, deshalb habe ich zugestimmt, an diesem Unterfangen teilzunehmen. Er ist ein erfahrener Seemann und ein Kapitän, das ist sicher, er hat eine schmucke Crew hinter sich und seine Polacre ist eine Schönheit, nicht jeden Tag kann man ein Schiff wie dieses sehen.";
			link.l1 = "Ignacio Marco? Ein englischer Freibeuter? Ist er Spanier?";
			link.l1.go = "rocur_8";
		break;
		
		case "rocur_8":
            dialog.text = "Er ist Portugiese, kein Spanier. Was ist falsch mit einem britischen Kaperbrief? Wir haben genug Spanier unter unserer Art, das weißt du.";
			link.l1 = "Ich verstehe. Gut, sprechen wir über deine Flucht von hier. Irgendwelche Ideen?";
			link.l1.go = "rocur_9";
		break;
		
		case "rocur_9":
            dialog.text = "Wie viele seid ihr?";
			link.l1 = "Mein Schiff, eine Barkentine und die Männer von Pelly dem Entermesser. Mein Gefährt liegt im Hafen von Maracaibo. Entermesser ist in der Bucht von Guajira gelandet und hat dort ein Lager aufgeschlagen.";
			link.l1.go = "rocur_10";
		break;
		
		case "rocur_10":
            dialog.text = "Hmm...";
			link.l1 = "Was, erwarteten Sie, dass Tyrex hier eine Linie von Schiffen schickt?";
			link.l1.go = "rocur_11";
		break;
		
		case "rocur_11":
            dialog.text = "Ich habe nichts erwartet. Tatsächlich bin ich überrascht, dass Marcus mich nicht vergessen hat.";
			link.l1 = "Er hat es offensichtlich nicht getan. Also, irgendwelche Ideen?";
			link.l1.go = "rocur_12";
		break;
		
		case "rocur_12":
            dialog.text = "Keine Chance, von hier zu entkommen - diese Plantage ist zu gut bewacht und es gibt wilde Dschungel ringsum. Es hat auch keinen Sinn, sie zu stürmen, du hast nicht genug Männer, und außerdem gibt es eine Festung in der Nähe.";
			link.l1 = "Vielleicht könnt ihr und eure Jungs uns von innen helfen? Trefft sie hart von hinten.";
			link.l1.go = "rocur_13";
		break;
		
		case "rocur_13":
            dialog.text = "Mit was? Nackten Händen und rostigen Macheten?";
			link.l1 = "Und was ist, wenn du Waffen hättest?";
			link.l1.go = "rocur_14";
		break;
		
		case "rocur_14":
            dialog.text = "Nun, in diesem Fall hätten wir ihnen die Hölle heiß gemacht. Es gibt allerdings ein Problem, sie überprüfen alles, was du hineinbringst, es gibt keine Möglichkeit, Waffen zu schmuggeln. Also schlage ich vor, das zu vergessen.";
			link.l1 = "Und dennoch ist das im Moment unsere beste Option. Ich werde darüber nachdenken, wie ich dir und deinen Männern Waffen liefern kann... Sag mir, wie viele von euch sind in der Lage zu kämpfen?";
			link.l1.go = "rocur_15";
		break;
		
		case "rocur_15":
            dialog.text = "Dreißig Köpfe, würde ich sagen.";
			link.l1 = "Dreißig Säbel dann... Ich glaube, Handfeuerwaffen würden auch einen Unterschied machen.";
			link.l1.go = "rocur_16";
		break;
		
		case "rocur_16":
            dialog.text = "Kapitän, meinst du das ernst?";
			link.l1 = "Ich bin es. Ich bin absichtlich hierher gekommen, herumalbern ist nicht Teil davon. Was könntest du sonst noch gebrauchen?";
			link.l1.go = "rocur_17";
		break;
		
		case "rocur_17":
            dialog.text = "Sehr gut... Lasst es uns zumindest versuchen. Wir brauchen einfaches kaltes Stahl - meine Jungs sind nicht darin ausgebildet, mit schicken Degen und so weiter zu arbeiten. Das Gleiche gilt für Handfeuerwaffen, die billigsten werden völlig ausreichen. Wenn ihr uns ein oder zwei Musketen besorgen könntet, würde uns das sehr helfen, ich habe ein paar Jungs, die gut mit Musketen umgehen können. Kugeln, Schießpulver. Heiltränke sind am meisten willkommen.";
			link.l1 = "Verstanden. Schwerter und Äxte können aus dem Schiffswaffenlager genommen werden. Der Rest ist schwieriger zu bekommen. Ich werde dich informieren, wenn ich alles habe.";
			link.l1.go = "rocur_18";
		break;
		
		case "rocur_18":
            dialog.text = "Bitte beeile dich, Bruder. Wir haben hier nicht ein halbes Jahr, diese verdammte Vieharbeit tötet uns einer nach dem anderen. Wenn du mich brauchst - komm, besuche mich in der Nacht.";
			link.l1 = "Verstanden, Kumpel. Warte mal, ich werde versuchen, dich nicht warten zu lassen. Und sei vorsichtig, gib ihnen keinen Grund, dich schon abzuschreiben.";
			link.l1.go = "rocur_19";
		break;
		
		case "rocur_19":
            DialogExit();
			AddQuestRecord("Roger_3", "7");
			npchar.dialog.currentnode = "rocur_wait";
			pchar.questTemp.Mtraxx = "plant_3";
			pchar.questTemp.Mtraxx.MagicBox = "Baster";
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			pchar.quest.Mtraxx_PlantPrepareTimeOver.over = "yes"; //снять таймер
			SetFunctionTimerCondition("Mtraxx_SeekWeaponOver", 0, 0, 30, false); // таймер
		break;
		
		case "rocur_wait":
            dialog.text = "Gibt es Neuigkeiten, Kamerad? Hast du Waffen gesammelt?";
			if (pchar.questTemp.Mtraxx == "plant_5")
			{
				link.l1 = "Ja. Eine Kiste mit Munition befindet sich in der Bucht von Guajira. Alles, was übrig bleibt, ist einen Weg zu finden, sie heimlich auf die Plantage zu schmuggeln.";
				link.l1.go = "rocur_20";
			}
			else
			{
				link.l1 = "Ich bin dran. Warte.";
				link.l1.go = "rocur_wait_1";
			}
		break;
		
		case "rocur_wait_1":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait";
		break;
		
		case "rocur_20":
            dialog.text = "Sehr gut, Kapitän. Ich habe bereits darüber nachgedacht, wie man das durchführen könnte.";
			link.l1 = "Froh, es zu hören. Was liegt dir auf dem Herzen?";
			link.l1.go = "rocur_21";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_21":
            dialog.text = "Sie produzieren Zucker und züchten Kakao auf dieser Plantage. Manchmal verkauft der Chef die Waren selbst, das ist profitabler. Mach ihm ein Angebot. Bezahle ihm nicht mit Geld, sondern mit Waren. Etwas, das man in Kisten packen kann, wie Kopra, Vanille oder Kaffee. Gib dir Mühe beim Feilschen, aber übertreib es nicht\nVerstecke Waffen in ein oder zwei Kisten und markiere sie. Vereinbare einen Austausch am Abend, damit sie die Kisten über Nacht draußen lassen müssen\nIn der Nacht werden wir deine markierten Kisten finden, uns bewaffnen und den Spaniern die Hölle heiß machen. Natürlich mit deiner Hilfe.";
			link.l1 = "Schönes Denken hier, Bruder! Sehr gut, ich mag diesen Plan. Lassen wir uns daran halten.";
			link.l1.go = "rocur_22";
		break;
		
		case "rocur_22":
            dialog.text = "Eine letzte Sache - biete nur eine Art von Waren zum Austausch an. Mehr Arten von Waren - mehr Kisten, die von den Wächtern kontrolliert werden.";
			link.l1 = "Ich stimme zu. Ich werde dann nur eine Art auswählen. Kaffee, Vanille und Kopra, sagten Sie?";
			link.l1.go = "rocur_23";
		break;
		
		case "rocur_23":
            dialog.text = "Ja. Dies wird dem Plantagenbesitzer wie ein gutes Geschäft vorkommen.";
			link.l1 = "Verstanden. Ich werde dich informieren, wenn der Handel abgeschlossen ist.";
			link.l1.go = "rocur_24";
		break;
		
		case "rocur_24":
            DialogExit();
			AddQuestRecord("Roger_3", "9");
			npchar.dialog.currentnode = "rocur_wait_2";
			pchar.questTemp.Mtraxx = "plant_6";
			pchar.questTemp.mtraxx_PlantInfoTovar = true;
			AddLandQuestMark(characterFromId("Pelly"), "questmarkmain");
		break;
		
		case "rocur_wait_2":
            dialog.text = "Geh, mein Freund, Zeit ist Gold und wir haben keins ...";
			link.l1 = "";
			link.l1.go = "rocur_wait_3";
		break;
		
		case "rocur_wait_3":
            DialogExit();
			npchar.dialog.currentnode = "rocur_wait_2";
		break;
		
		case "rocur_25":
            dialog.text = "...";
			link.l1 = "(leise) Der Handel ist besiegelt. Die Kisten werden morgen Abend zur Plantage geliefert. Die Kisten, die du brauchst, sind mit einem 'W' gekennzeichnet. Die anderen haben den Rest des Alphabets auf ihnen. Mach deine Männer bereit. Wir greifen irgendwo um drei Uhr vor Tagesanbruch an.";
			link.l1.go = "rocur_25x";
			DelLandQuestMark(npchar);
		break;
		
		case "rocur_25x":
            dialog.text = "Wir werden mit deinem Signal beginnen...";
			link.l1 = "";
			link.l1.go = "rocur_26";
		break;
		
		case "rocur_26":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 3.0);
		break;
		
		case "rocur_27":
            dialog.text = "Endlich! Ich werde das Meer wieder sehen! Ich habe bereits sein Aussehen und seinen Geruch vergessen. Gut gemacht Kapitän! Ich schulde dir was.";
			link.l1 = "Mach dir keine Sorgen darum, wir werden es später klären... Jetzt lass uns an Bord gehen und hier raus!";
			link.l1.go = "rocur_28";
		break;
		
		case "rocur_28":
            DialogExit();
			sld = characterFromId("Pelly");
			sld.Dialog.currentnode = "Pelly_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "rocur_29":
            dialog.text = "Grüße "+pchar.name+". Schön dich wieder zu sehen, auch froh dich als meinen Begleiter in diesem Abenteuer zu haben. Diese Arbeit wird hart sein, aber ich bin sicher, wir werden es schaffen.";
			link.l1 = "Schön dich wieder zu sehen Picard. Ich bin ganz Ohr, erzähl mir von deinem Abenteuer.";
			link.l1.go = "rocur_30";
		break;
		
		case "rocur_30":
            dialog.text = "Ich habe es bereits Marcus gesagt, jetzt werde ich es dir sagen. Als ich Sklave auf der Plantage in Maracaibo war, habe ich etwas von den Spaniern gelernt. Sie sind ziemlich gesprächig, wenn sie betrunken sind... Hör zu, südöstlich der Bucht von Maracaibo gibt es ein kleines Dorf. Es liegt versteckt zwischen zwei Bergen tief im Dschungel. Verdammt nochmal, es hat einen Namen: Santiago-de-Los-Caballeros-de-Merida. Nennen wir es Merida\nKlingt noch nicht sehr interessant, hm? Die Berge, die das Dorf umgeben, stellten sich als reich an Edelsteinen heraus. Smaragde, Opale und legendäre Feueropale\nSoweit ich verstehe, haben die Siedler von Merida dem Generalgouverneur nichts von diesen Edelsteinen erzählt. Aber bald wird er davon erfahren, deshalb sollten wir Merida besuchen, bevor die spanischen Kolonialbeamten eintreffen.";
			link.l1 = "Möchtest du die Siedlung plündern?";
			link.l1.go = "rocur_31";
		break;
		
		case "rocur_31":
            dialog.text = "Genau. Es ist verloren inmitten von Dschungeln und Bergen mit einer kleinen Garnison - eine leichte Beute für eine Korsaren-Einheit. Außerdem sind sie weit weg vom Meer, sie erwarten keinen Angriff außer von Wilden mit Speeren und Bögen.";
			link.l1 = "Wie sicher sind Sie, dass es in der Siedlung Edelsteine gibt?";
			link.l1.go = "rocur_32";
		break;
		
		case "rocur_32":
            dialog.text = "Wenn unsere Abenteuer sich als falsche Spur herausstellen, werde ich selbst auf Ihrem Schiff als Offizier oder als Matrose dienen, ich werde die Decks reinigen und in unzähligen Enterungen kämpfen, bis meine Schuld bei Ihnen und Marcus getilgt ist.";
			link.l1 = "Ich sehe... Gut, weißt du, wie man nach Merida kommt?";
			link.l1.go = "rocur_33";
		break;
		
		case "rocur_33":
            dialog.text = "Natürlich kenne ich nicht den genauen Weg durch den Dschungel, aber wir werden einen Führer aus dem Indianer-Volk anheuern. Wir sollten südlich des Maracaibo-Sees landen, ein Indianerdorf finden und diejenigen finden, die wissen, wie man dorthin kommt.";
			link.l1 = "...";
			link.l1.go = "rocur_34";
		break;
		
		case "rocur_34":
            DialogExit();
			sld = characterFromId("Terrax");
			sld.Dialog.currentnode = "mtraxx_38";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_35":
            dialog.text = "Kapitän, es tut mir zutiefst leid wegen meiner Ausdrucksweise, aber warum zum Teufel sind wir noch nicht in Merida? Hm? Du hast auf unsere gemeinsame Sache gespuckt! Der Kobold und ich gehen ohne dich. Ich werde Tyrex alles erklären und du solltest gehen. Hier, nimm 50.000 Pesos für deine Hilfe in Maracaibo, ich habe sie von Freunden geliehen. Leb wohl, verdammt schade, ich hatte eine bessere Meinung von dir.";
			link.l1 = "Hmm... Es tut mir leid.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaTimeOverFail");
		break;
		
		case "rocur_36":
            dialog.text = "Hier sind wir. Dschungel voraus. Zuerst sollten wir ein indisches Dorf finden und nach einem Führer fragen.";
			link.l1 = "Lass uns das tun. Luke, hast du etwas zu sagen... oder vielleicht einen Rat?";
			link.l1.go = "rocur_37";
		break;
		
		case "rocur_37":
            DialogExit();
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_38":
            dialog.text = "Die Garnison von Merida ist erledigt. Ich erwarte keinen ernsthaften Widerstand innerhalb des Dorfes. Los geht's!";
			link.l1 = "Angriff!!!";
			link.l1.go = "rocur_39";
		break;
		
		case "rocur_39":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_ExitTown", "reload1_back", true);
			pchar.quest.mtraxx_merida_town.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_town.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_town.function = "Mtraxx_MeridaTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "16");
		break;
		
		case "rocur_40":
            dialog.text = "Es ist vollbracht! Keine Helden mehr übrig. Jetzt sollten wir mit dem Gouverneur dieser 'Stadt' sprechen. Ich hoffe, er ist ein überredbarer Typ.";
			link.l1 = "Ich stimme zu, lass uns ihn 'überzeugen'!.. Jean! Folge mir!";
			link.l1.go = "rocur_41";
		break;
		
		case "rocur_41":
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "gate_back", true);
			pchar.quest.mtraxx_merida_townhall.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_townhall.win_condition.l1.location = "Merida_townhall";
			pchar.quest.mtraxx_merida_townhall.function = "Mtraxx_MeridaTownhall";
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddQuestRecord("Roger_5", "17");
		break;
		
	case "rocur_42": //злой вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			pchar.questTemp.Mtraxx_MeridaZloVariant = true;
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_43": //мирный вариант
            DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Merida_Town", "reload3", true); 
			pchar.questTemp.Mtraxx = "merida_success";
			pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
			pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			sld = characterFromId("Merida_Head");
			LAi_SetActorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;
		
		case "rocur_44":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
            	dialog.text = "Gut gemacht, "+pchar.name+"! Zeit, die Anteile aufzuteilen. Ich habe bereits die Zahlen. Es waren fast 2000 Edelsteine in der Truhe: 1560 Smaragde, 1032 Opale und 363 Feueropale. Dein Anteil ist das Drittel: 350 Smaragde, 244 Opale und 63 Feueropale. Hier, nimm sie.";
            }
            else
           	{
           	dialog.text = "Gut gemacht, "+pchar.name+"! Zeit, die Anteile aufzuteilen. Ich habe bereits die Zahlen. Es waren fast 2000 Edelsteine in der Truhe: 1050 Smaragde, 732 Opale und 189 Feueropale. Dein Anteil ist das Drittel: 350 Smaragde, 244 Opale und 63 Feueropale. Hier, nimm sie.";
           	}
			link.l1 = "Schön!";
			link.l1.go = "rocur_45";
		break;
		
		case "rocur_45":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 520);
				TakeNItems(pchar, "jewelry16", 334);
				TakeNItems(pchar, "jewelry14", 121);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 350);
				TakeNItems(pchar, "jewelry16", 244);
				TakeNItems(pchar, "jewelry14", 63);
			}
            dialog.text = "Nun sprechen wir über meine Schuld für meine Rettung. Ich verstehe, dass du ernsthafte Kosten hattest. Welche Entschädigung würdest du als fair betrachten? Ich zahle von meinem Anteil an Edelsteinen.";
			link.l1 = "Ein Drittel deines Anteils wird ausreichen. Du brauchst auch Geld - um ein Schiff zu kaufen und auszustatten, um deine Crew zu bezahlen...";
			link.l1.go = "rocur_46";
		break;
		
		case "rocur_46":
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
			{
				TakeNItems(pchar, "jewelry4", 173);
				TakeNItems(pchar, "jewelry16", 111);
				TakeNItems(pchar, "jewelry14", 40);
			}
			else
			{
				TakeNItems(pchar, "jewelry4", 116);
				TakeNItems(pchar, "jewelry16", 81);
				TakeNItems(pchar, "jewelry14", 21);
			}
            dialog.text = "Danke dir, Freund! Ich dachte, du würdest nicht weniger als die Hälfte verlangen. Ich brauche jetzt wirklich Geld. Hier, nimm die Edelsteine.";
			link.l1 = "Was für ein Überfall Jean! Auf nach Hispaniola, zu Tyrex.";
			link.l1.go = "rocur_47";
		break;
		
		case "rocur_47":
            DialogExit();
			chrDisableReloadToLocation = false;
			pchar.questTemp.Mtraxx = "merida_gohome";
			AddQuestRecord("Roger_5", "18");
			sld = characterFromId("Mrt_Rocur");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld); // релиз-правка
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Lepricon");
			LAi_SetWarriorType(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "mtraxx_40";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_lavega.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_merida_lavega.function = "Mtraxx_IgnasioKitty";
			// таймер на доплыть домой 40 дней
			SetFunctionTimerCondition("Mtraxx_MeridaReturnLate", 0, 0, 40, false);
			DeleteAttribute(pchar, "GenQuest.HunterLongPause");
		break;
		
		case "rocur_48":
            dialog.text = "Oh, was für ein Treffen! Freut mich, dich zu sehen, "+pchar.name+". Wie geht es dir?";
			link.l1 = "Ziemlich gut. Habe gerade erst Red Wolfs Schätze gefunden. Jetzt geht es nach Martinique, um einen gemeinsamen Freund von uns zu treffen. Willst du Tyrex sehen?";
			link.l1.go = "rocur_49";
		break;
		
		case "rocur_49":
            dialog.text = "Ja. Ich möchte mit ihm über Pasquale Lavoisier sprechen. Marcus hat mich zu diesem Halb-Banditen-Halb-Händler geschickt. Ich habe getan, was er verlangt hat und er hat mit irgendeinem Scheiß bezahlt, den er als verdammt gute Bezahlung bezeichnet hat. Ich würde den Kerl sofort umbringen, wo er stand, aber Marcus bat, ihn mit Respekt zu behandeln... dann ist es an ihm, sich mit diesem Ärger zu befassen.";
			link.l1 = "Es tut mir Leid, aber Marcus wird nichts tun. Vier-Augen ist mit ihm im Geschäft.";
			link.l1.go = "rocur_50";
		break;
		
		case "rocur_50":
            dialog.text = "Was zum Teufel?";
			link.l1 = "Ja, aber ich habe dir nichts davon erzählt, klar? Lavoisier hat mich auch vor nicht allzu langer Zeit hintergangen. Tyrex bat mich, ihm zu helfen, genau wie er dich gefragt hat. Auf Isla Tesoro wurde ich gewarnt, dass es dasselbe ist, den Vieraugen zu hintergehen wie Marcus. Also schlage ich vor, dass du das vergisst. Du bist weder der Erste noch der Letzte in dieser Angelegenheit.";
			link.l1.go = "rocur_51";
		break;
		
		case "rocur_51":
            dialog.text = "Ich verstehe. Du wurdest also auch von diesen beiden über den Tisch gezogen?";
			link.l1 = "Nun, ja. Ich dachte daran, auch dem Vieräugigen Ärger zu machen, bevor ich mehr über ihn erfuhr. Es ist es nicht wert.";
			link.l1.go = "rocur_52";
		break;
		
		case "rocur_52":
            dialog.text = "Würdest du versuchen, dem Bastard zu vergelten, wenn du wüsstest, dass es niemand jemals herausfinden wird?";
			link.l1 = "Ha! Sicher würde ich! Obwohl ich nicht weiß wie. Greif die Flöten von Lavoisier an und eines glänzenden Tages werden deine Matrosen betrunken und plappern alles aus. Weißt du nicht, wie es funktioniert?";
			link.l1.go = "rocur_53";
		break;
		
		case "rocur_53":
            dialog.text = "Fahrt ihr jetzt nach Martinique? Wann werdet ihr wieder in La Vega ankommen?";
			link.l1 = "Marcus gab mir drei Wochen.";
			link.l1.go = "rocur_54";
		break;
		
		case "rocur_54":
            dialog.text = "Versuche es in zwei Tagen zu schaffen. Ich werde darüber nachdenken... Finde mich in der Bucht von Gonaives in 14 Tagen. Gehe direkt dorthin und betrete La Vega nicht.";
			link.l1 = "Ich sehe, du bist zu etwas aufgelegt, ha-ha. Gut. Ich werde es versuchen.";
			link.l1.go = "rocur_55";
		break;
		
		case "rocur_55":
            dialog.text = "Du solltest das besser tun. Wir sehen uns!";
			link.l1 = "...";
			link.l1.go = "rocur_56";
		break;
		
		case "rocur_56":
            DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 10.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			ReOpenQuestHeader("Roger_4");
			AddQuestRecord("Roger_4", "11");
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.hour  = 1.0;
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2 = "location";
			pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2.location = "Shore34";
			pchar.quest.mtraxx_pasq_gonaiv.function = "Mtraxx_PasqualeJanGonaiv";
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimer", 0, 0, 10, false); // правки прогона 3
			SetFunctionTimerCondition("Mtraxx_PasqualeJanTimeOver", 0, 0, 15, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.questTemp.Mtraxx.Pasquale.Grabbing = "true";
		break;
		
		case "rocur_57":
			if (pchar.location.from_sea != "Shore34")
			{
				dialog.text = RandSwear()+"Wo ist dein Schiff? Bist du von La Vega hierher gekommen? Merde! Ich habe dich gebeten, hier unbemerkt und im Geheimen anzukommen. Mein Plan ist jetzt ruiniert. Verdammt!..";
				link.l1 = "Hm...";
				link.l1.go = "rocur_58";
			}
			if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "Da bist du ja, "+pchar.name+". Es ist gut, dass du hier bist. Schick deine Kameraden zurück zum Schiff. Es ist ein privates Gespräch.";
				link.l1 = "Sehr gut.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "Da bist du ja , "+pchar.name+". Es ist gut, dass du hier bist. Ich habe ein Geschäft für dich. Bist du bereit, es zu hören?";
				link.l1 = "Sicher!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_58":
            DialogExit();
			Group_DelCharacter("RocurSeaGroup", "Mrt_Rocur");
			Group_DeleteGroup("RocurSeaGroup");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 10.0);
			AddQuestRecord("Roger_4", "14");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_59":
            DialogExit();
			LAi_SetStayType(npchar);
			npchar.dialog.currentnode = "rocur_60";
		break;
		
		case "rocur_60":
            if (GetOfficersQuantity(pchar) > 0)
			{
				dialog.text = "Ich habe es dir schon gesagt - schicke deine Offiziere weg!";
				link.l1 = "Ja-ja, ich habe es verstanden.";
				link.l1.go = "rocur_59";
			}
			else
			{
				dialog.text = "Großartig. Jetzt können wir frei sprechen. Ich habe ein Geschäft für dich. Bereit, es zu hören?";
				link.l1 = "Sicher!";
				link.l1.go = "rocur_61";
			}
		break;
		
		case "rocur_61":
            dialog.text = "Kennen Sie La Vega gut?";
			link.l1 = "Nun... Ich denke, ich tue es. Warum fragst du?";
			link.l1.go = "rocur_62";
			npchar.greeting = "";
		break;
		
		case "rocur_62":
            dialog.text = "Hast du jemals das Lagerhaus rechts vom örtlichen Laden bemerkt? Das einzige große Haus unter den Hütten.";
			link.l1 = "Der immer geschlossene? Ja, ich habe ihn gesehen. Was ist damit?";
			link.l1.go = "rocur_63";
		break;
		
		case "rocur_63":
            dialog.text = "Gut bemerkt - es ist immer geschlossen. Während du auf deiner Mission in Martinique warst, war unser gemeinsamer Freund Lavoisier für drei Tage zu Gast bei Marcus Tyrex. Sie verbrachten ihre Zeit in diesem Haus, tranken Rum und hatten Spaß.";
			link.l1 = "Hm...";
			link.l1.go = "rocur_64";
		break;
		
		case "rocur_64":
            dialog.text = "Dann schleppten die Männer von Lavoisier einige Kisten und Pakete ins Haus. Dann ist er gegangen. Was Marcus betrifft, so bleibt er jeden Tag mehrere Stunden an diesem Ort.";
			link.l1 = "Hast du Vorschläge?";
			link.l1.go = "rocur_65";
		break;
		
		case "rocur_65":
            dialog.text = "Welche Vorschläge? Ich bin sicher, dieses Haus muss eine Basis von Lavoisier in La Vega sein. Ich habe nicht viel durch das Fenster gesehen, aber dort sind Waren gelagert. Ich denke, dass der Vier-Augen die Mittel hat, uns zurückzuzahlen, was er uns schuldet.";
			link.l1 = "Nun, nun... Willst du einbrechen? Was ist mit der verschlossenen Tür? Sie ist schwer und robust, es gibt keine Möglichkeit, dass wir leise einbrechen.";
			link.l1.go = "rocur_66";
		break;
		
		case "rocur_66":
            dialog.text = ""+pchar.name+", hältst du mich für einen Idioten? Ich habe das schon geregelt. Ich habe den Schlüssel mit einer Wachsmaske des Schlosses gemacht. Hat mich eine hübsche Summe gekostet, aber das ist mein Problem.";
			link.l1 = "Heh! Warum dann auf mich warten?";
			link.l1.go = "rocur_67";
		break;
		
		case "rocur_67":
            dialog.text = "Es wird auf diese Weise sicherer sein, außerdem bist du der Einzige, dem ich vertrauen könnte. Ein Kopf ist gut, zwei Köpfe sind besser, und vier Augen sind besser als zwei.";
			link.l1 = "Nun ja, Lavoisier zu überqueren wird so viele Augen erfordern, wie er hat, ha-ha-ha! Aber was ist mit Tyrex? Was ist, wenn er das Haus betritt, während wir Pasquales Besitztümer überprüfen?";
			link.l1.go = "rocur_68";
		break;
		
		case "rocur_68":
            dialog.text = "Er wird nicht. Er ist immer vor Mitternacht wieder in seinem eigenen Haus. Bereit, nächste Nacht nach La Vega zu gehen? Sie werden nie herausfinden, wer sie gefickt hat: Du bist immer noch auf Martinique und ich habe La Vega vor einer Woche verlassen.";
			link.l1 = "Ich würde liebend gerne den vieräugigen Enculé schrauben. Aber sag mir Jean, wie sollen wir Fässer und Kisten aus dem Haus tragen?";
			link.l1.go = "rocur_69";
		break;
		
		case "rocur_69":
            dialog.text = "Ich bin sicher, wir werden dort wertvollere Gegenstände als Kisten und Fässer mit Waren finden, die viel leichter sein werden. Also, bist du dabei?";
			link.l1 = "Verdammt ja, das bin ich!";
			link.l1.go = "rocur_70";
		break;
		
		case "rocur_70":
            dialog.text = "Großartig, froh, dass ich mich nicht in dir getäuscht habe. Lassen wir uns jetzt ausruhen, wir machen uns um Mitternacht auf nach La Vega.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNight");
		break;
		
		case "rocur_71":
            dialog.text = "Zeit zu gehen. Wir sollten diesen Bastard ausrauben und vor der Morgendämmerung zur Hölle rauskommen.";
			link.l1 = "Weiter!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightMarch");
			SetLocationCapturedState("LaVega_town", true);
			LAi_LoginInCaptureTown(npchar, true);
		break;
		
		case "rocur_72":
            dialog.text = "Still... Jetzt beweg dich, leise, zu Pasquales Haus. Folge mir.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightToHouse");
		break;
		
		case "rocur_73":
            dialog.text = "Schau dir das an - so viel Zeug liegt herum. Lass uns anfangen. Überprüfe eine Truhe in der Nähe der Tür, dann geh nach oben und kümmere dich um ein Zimmer. Ich bleibe hier: Ich kenne die Tricks, Wertsachen unter dem Gerümpel zu verstecken. Halte deine Augen und Ohren offen und halte dich von den Fenstern fern.";
			link.l1 = "In Ordnung...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightInHouse");
		break;
		
		case "rocur_74":
            dialog.text = ""+pchar.name+", was hast du? Irgendetwas von Interesse?";
			link.l1 = "Komm und schau. Das ist etwas.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeJanSeeGirl");
		break;
		
		case "rocur_75":
            dialog.text = "Verdammt! Jetzt sehe ich, warum Tyrex jeden Tag hierher kommt. Es ist nicht nur das Lagerhaus des Vieräugigen, sondern auch ein Bordell.";
			link.l1 = "Sieht aus, als wäre sie hier eine Sklavin.";
			link.l1.go = "rocur_76";
		break;
		
		case "rocur_76":
            dialog.text = "Sicher. Schau sie dir an - sie ist eine offensichtliche Hafenprostituierte... Pech für uns. Wir müssen sie töten.";
			link.l1 = "Wirklich?";
			link.l1.go = "rocur_77";
		break;
		
		case "rocur_77":
            dialog.text = "Sie hat unsere Gesichter gesehen und deinen Namen gehört. Sie wird alles Tyrex erzählen.";
			link.l1 = "Hm...";
			link.l1.go = "rocur_78";
		break;
		
		case "rocur_78":
            dialog.text = "Es ist deine Wahl. Ihr Leben könnte dich deines kosten.";
			link.l1 = "";
			link.l1.go = "rocur_79";
		break;
		
		case "rocur_79":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_80":
            dialog.text = "Denk nicht mal daran, dieser Hure zu vertrauen. Morgen wird Tyrex alles wissen. Willst du ein schwarzes Zeichen erhalten?";
			link.l1 = "Nein, das tue ich nicht. Und ich will das Weib nicht töten - ich habe Verwendung für sie. Sie kommt mit mir.";
			link.l1.go = "rocur_81";
		break;
		
		case "rocur_81":
            dialog.text = "Sei kein Idiot! Sie wird weglaufen, sobald sie die Chance bekommt. Sieh dir ihre Stirn an, siehst du das Brandzeichen? Sie ist eine Diebin.";
			link.l1 = "Hm. Du hast wahrscheinlich recht, Jean. Gut, erledige sie und lass uns von hier verschwinden.";
			link.l1.go = "rocur_82";
			link.l2 = "Ich habe nicht vor, sie auf meinem Schiff zu behalten. Ich habe einen Ort für sie, von dem sie niemals entkommen wird, und es gibt auch keine Ohren, die ihre Schreie hören. Sie wird dort auch weiterhin ihrer Arbeit nachgehen... Eine persönliche Hure, kostenlos, he-he!";
			link.l2.go = "rocur_84";
		break;
		
		case "rocur_82":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto6", "", 5);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto7", "Mtraxx_PasqualeJanKillGirl", 5);
		break;
		
		case "rocur_83":
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
            dialog.text = "Das war's, es gibt keine Möglichkeit, dass sie jetzt noch etwas zu Marcus sagt...";
			link.l1 = "Armes Mädchen... hah naja wie man so sagt, Dame Glück ist eine Schlampe...";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_84":
            DialogExit();
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rocur_85":
            dialog.text = "Du bist ein freundlicher Mann, "+pchar.name+". Warum willst du dich mit ihr belästigen? Ach, was auch immer, es ist deine Wahl. Stelle sicher, dass sie still ist, während wir gehen.";
			link.l1 = "Wenn sie nicht will - sie ist tot.";
			link.l1.go = "rocur_86";
		break;
		
		case "rocur_86":
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing.Chest")) sTemp = "A bit. A chest full of doubloons, a handful of rubies, a map of Hispaniola and some rum.";
			else sTemp = "Nothing of value.";
            dialog.text = "Was hast du gefunden?";
			link.l1 = sTemp;
			link.l1.go = "rocur_87";
		break;
		
		case "rocur_87":
			Log_Info("You have received two treasure collections.");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 2);
            dialog.text = "Mehr Glück auf meiner Seite. Hier, nimm deinen Anteil. Ich würde es nie schaffen, alles mit mir an Land zu nehmen. Der Vieraugen hat uns voll bezahlt.";
			link.l1 = "Prächtig! Gut gemacht, Jean!";
			link.l1.go = "rocur_88";
		break;
		
		case "rocur_88":
            dialog.text = "Jetzt geh!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeNightOutHouse");
		break;
		
		case "rocur_89":
			PlaySound("VOICE\English\LE\Rocur\Rocur_04.wav");
            dialog.text = "Großartig. Es ist erledigt. Schön und leise. Jetzt gehen wir zurück zu den Schiffen.";
			link.l1 = "Hah, gute Idee.";
			link.l1.go = "rocur_89_1";
			//AddDialogExitQuestFunction("Mtraxx_PasqualeNightGulf");
		break;
		
		case "rocur_89_1":
			DialogExit();
			DoFunctionReloadToLocation("shore34", "goto", "goto13", "Mtraxx_PasqualeFinal");
		break;
		
		case "rocur_90":
			PlaySound("VOICE\English\LE\Rocur\Rocur_05.wav");
            dialog.text = "Nun, "+pchar.name+". Es ist Zeit, dass wir uns trennen. Ich bin mir nicht sicher, ob wir uns jemals wiedersehen werden, aber es war mir eine Freude, dich Freund zu kennen.";
			link.l1 = "Ach komm schon, wir werden uns oft in La Vega sehen.";
			link.l1.go = "rocur_91";
			SetLocationCapturedState("LaVega_town", false);
			LAi_LoginInCaptureTown(npchar, false);
		break;
		
		case "rocur_91":
            dialog.text = "Nein. Ich habe genug von Tyrex. Dieses Durcheinander mit Lavoisier war der letzte Tropfen.";
			link.l1 = "Hmm... Ich verstehe, vergiss es einfach. Wir haben bekommen, was uns zurecht gehört. Tyrex gibt profitable Hinweise, nicht wahr? Das letzte Mal habe ich mehr als eine halbe Million von Red Wolfs Schatz gemacht.";
			link.l1.go = "rocur_92";
		break;
		
		case "rocur_92":
            dialog.text = "Sag mir dann, hast du viel Mühe darauf verwendet, es zu finden?";
			link.l1 = "Nun... Es war nicht einfach. Hab viel nachgedacht, gereist und gekämpft. Es hat sich gelohnt, denke ich.";
			link.l1.go = "rocur_93";
		break;
		
		case "rocur_93":
            dialog.text = "Wie viel hast du Tyrex bezahlt?";
			link.l1 = "Ein Drittel.";
			link.l1.go = "rocur_94";
		break;
		
		case "rocur_94":
            dialog.text = "Welche Rolle spielte er in dieser Angelegenheit? Was hat Marcus genau gemacht?";
			link.l1 = "Hm... Er hat mir das Logbuch des Roten Wolfs gegeben...";
			link.l1.go = "rocur_95";
		break;
		
		case "rocur_95":
            dialog.text = "Und das ist alles? Richtig?";
			link.l1 = "Nun... Sonst hätte ich nie von Kapitän Wulfric erfahren...";
			link.l1.go = "rocur_96";
		break;
		
		case "rocur_96":
            dialog.text = ""+pchar.name+", siehst du nicht, dass Tyrex andere die Drecksarbeit machen lässt? Denkst du, er würde dir den Auftrag geben, diesen Schatz zu finden, wenn er es selbst tun könnte? Zur Hölle nein! Ich wette, er hat zuerst versucht, es selbst zu tun, und als er alles vermasselt hat, hat er dich gerufen, um die Arbeit zu erledigen. Und während du nachgedacht hast, Wochen auf See verbracht hast, gekämpft und dein eigenes Leben riskiert hast, hat dieser Bastard zusammen mit seinem widerlichen vieräugigen Freund die Hure in La Vega gefickt. Und dafür hat er auch ein Viertel Million Pesos bekommen. Einfach so\nGlaubst du, er hat seinen Hund Leprechaun geschickt, um uns bei unserem Überfall auf Merida zu helfen? Nein, er wollte sicherstellen, dass seine Interessen sicher sind. Alles, was Marcus alleine tun kann, tut er, entweder alleine oder mit Hilfe von Cutlasses, Balds, Leprechauns und anderen dummen Idioten, die für ihn arbeiten für Pfennige. Leute wie du und ich bekommen Hinweise, dass Marcus zu dumm ist, um sie selbst auszuführen\nErinnerst du dich an alle Aufgaben, die du für ihn erledigt hast? Zähl mal, wie viel er an dir verdient hat. Ich habe genug davon. Jetzt habe ich das Geld, eine großartige Korvette und eine treue Mannschaft... ab jetzt bin ich ein Freiberufler. Ich mache mich auf den Weg nach Jamaika, vielleicht erhalte ich dort einen Kaperbrief.";
			link.l1 = "Ich glaube nicht, dass du ganz richtig liegst über Tyrex... Aber ich wünsche dir Glück Jean! Hoffentlich findest du Erfolg in Jamaika.";
			link.l1.go = "rocur_97";
		break;
		
		case "rocur_97":
            dialog.text = "Ich werde es tun. Viel Glück auch dir und denk an das, was ich gesagt habe. Marcus' Hündchen zu sein, ist nicht die beste Rolle für dich, ich weiß, dass du zu viel mehr fähig bist. Nun... Lebewohl Bruder! Gott mit dir!";
			link.l1 = "Gute Jagd, Jean!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_PasqualeAddComplete");
		break;
		
		case "rocur_98":
            dialog.text = ""+pchar.name+", sag mal, wie haben wir so viel Zeit im Dschungel verbracht? Jetzt ist mein Plan im Eimer. Eh... Tschüss, Kumpel...";
			link.l1 = "Heh...";
			link.l1.go = "rocur_99";
		break;
		
		case "rocur_99":
            DialogExit();
		    LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			sld.lifeday = 0;
			Group_DeleteGroup("RocurSeaGroup");
			AddQuestRecord("Roger_4", "18");
			CloseQuestHeader("Roger_4");
		break;
		
		case "rocur_100":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				dialog.text = "Zeit zu gehen, Jungs. Verdammt, Prinz, du hast mich überrascht. Hast eine ganze Stadt verbrannt, aber geweigert, deine Hände schmutzig zu machen, wenn es darauf ankam.";
				link.l1 = "Ich habe nicht befohlen, die Stadt zu verbrennen!";
				link.l1.go = "rocur_101";
			}
			else
			{
				dialog.text = "Zeit zu gehen, Jungs. Lucas, du hast was verpasst. Der Prinz hat es brillant gehandhabt - und einen guten Gewinn gemacht!";
				link.l1 = "Was ist mit der Stadt, Hübscher?! Ich habe mein Wort gegeben!";
				link.l1.go = "rocur_102";
			}
			sld = CharacterFromID("Lepricon");
			CharacterTurnToLoc(sld, "reload", "reload3");
		break;
		
		case "rocur_101":
            dialog.text = "Zumindest hast du nicht versucht, es zu retten. Sonst hätten unsere Männer dich zuerst ausgenommen. Es war ein harter Tag für sie. Sie verdienten es, Dampf abzulassen. Du wirst dich daran gewöhnen. Du hast alles, was dazu gehört.";
			link.l1 = "Danke für den Rat, aber ich erinnere mich nicht, danach gefragt zu haben. Lass uns gehen.";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_102":
            dialog.text = " Ich dachte, du machst Witze. Nun... du warst zu voreilig. Die Stadt ist erledigt. So ist es immer, wenn die Bruderschaft der Küste zur Arbeit kommt. Du wirst dich daran gewöhnen.";
			link.l1 = "Ich bin mir nicht sicher, ob ich will. Na gut, lass uns gehen.";
			link.l1.go = "rocur_103";
		break;
		
		case "rocur_103":
            DialogExit();
			LAi_SetPlayerType(pchar);
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			sld = characterFromId("Tagofa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "12");
		break;
		
		case "rocur_104":
            dialog.text = "Kumpel... was war das gerade?";
			link.l1 = "Was, hast du es nicht verstanden? Ich habe dich gekauft. Du hast einmal gesagt, ich hätte Zugang zu den Spaniern, also habe ich es genutzt.";
			link.l1.go = "rocur_105";
		break;
		
		case "rocur_105":
            dialog.text = "Ich habe das verstanden - Ich bin kein Idiot. Aber arbeiteten wir nicht an einem anderen Plan?";
			link.l1 = "Nun, Cutlass und ich dachten, es wäre nicht richtig, wenn du während eines Aufstands oder einer Verfolgungsjagd sterben würdest, also haben wir beschlossen, dich direkt zu kaufen.";
			link.l1.go = "rocur_106";
		break;
		
		case "rocur_106":
            dialog.text = "Hah, beleidige mich nicht. Ich bin schließlich einer von Terrax's Kapitänen. Ich weiß, wie man ein Schwert hält.";
			link.l1 = "Ich bezweifle das nicht, aber bist du wirklich verärgert darüber, frei zu sein?";
			link.l1.go = "rocur_107";
		break;
		
		case "rocur_107":
            dialog.text = "Nein, nein - ich bin dankbar. Es ist nur... war es nicht ein bisschen zu viel, all dieses Gold auszugeben? Mir wird schon schlecht, wenn ich nur daran denke. Der Pflanzer sah aus wie ein poliertes Silbertablett.";
			link.l1 = "Ja, 'Das Geschäft des Jahrhunderts', in der Tat. Es sticht ein bisschen, sicher. Aber Zeit ist kostbarer als Gold, Jean. Pistolen und Medizin für euch alle zu suchen...";
			link.l1.go = "rocur_108";
		break;
		
		case "rocur_108":
            dialog.text = "Ich bin dankbar, aber Kumpel, du bist ein Narr - keine Beleidigung. Ich habe dir gesagt, dass meine Jungs nicht gut mit Schwertern umgehen können. Aber jeder kann einen Abzug betätigen. Du hättest Pistolen und Medizin aus dem Laderaum mitbringen können, wie mit den Säbeln und Äxten - sie sind nicht wählerisch.";
			link.l1 = "Hmm, ehrlich gesagt, daran hatte ich nicht gedacht... Wie auch immer, lass uns gehen - Cutlass wird wahrscheinlich ungeduldig.";
			link.l1.go = "rocur_109";
		break;
		
		case "rocur_109":
			DialogExit();
			DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_3");
		break;
		
		// Люк Лепрекон
		case "lepricon":
            dialog.text = "Grüße, Kapitän "+GetFullName(pchar)+". Luke der Kobold steht zu Eurem Dienst! Mir wurde gesagt, wir gehen in die Dschungel des Südlichen Main.";
			link.l1 = "Genau. Steigt in die Langboote, wir brechen sofort auf.";
			link.l1.go = "lepricon_1";
		break;
		
		case "lepricon_1":
            dialog.text = "Lass einen alten Freibeuter dir einen Rat geben, Kapitän. Da wir uns auf den Weg in den Dschungel machen - werden wir sicherlich auf die Indianer treffen. Nimm Geschenke für sie mit. Indianische Krieger verehren schöne Pistolen, besonders die Duellpistolen. Sie mögen auch Kompass und Spiongläser. Sie betrachten sie als magische Gegenstände\nIhre Frauen bevorzugen billigen Schmuck und Nippes wie Spiegel und Muscheln. Wenn wir mit ihnen in einen Kampf geraten, benutze Posaunen und Arkebusen: Schrot im Allgemeinen ist sehr gut gegen Feinde, die keine Rüstungen tragen. Was die Siedlung selbst betrifft, schlage ich Kanonen vor, die Papierpatronen verwenden können.";
			link.l1 = "Sehr gut, Luke. Deine Worte sind vermerkt. Willkommen an Bord.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaSail");
		break;
		
		case "lepricon_2":
            dialog.text = "Suche den Häuptling auf, sobald wir im Dorf ankommen. Und bringe Geschenke mit, sonst ist es sinnlos. Erkundige dich nach jemandem aus seinem Volk, der von geheimen Durchgängen im vorausliegenden Dschungel weiß, und frage nach denen, die keine Angst vor Reisen haben. Ich komme mit dir, wende dich an mich, falls du auf Schwierigkeiten stößt.";
			link.l1 = "Auf geht's! Jean, Luke - folgt mir!";
			link.l1.go = "exit";
			npchar.greeting = "Lepricon_02";
			AddDialogExitQuestFunction("Mtraxx_MeridaSeekVillage");
		break;
		
		case "lepricon_3":
            dialog.text = "Irgendwelche Fragen, Kapitän?";
			link.l1 = "Im Moment nichts, Luke.";
			link.l1.go = "lepricon_3x";
			if (pchar.questTemp.Mtraxx == "merida_advice")
			{
				link.l1 = "Ja! Ich habe mit ihrem Häuptling gesprochen, ich habe ihm Geschenke gemacht und später hat er seine Rothäute zu einer Versammlung gerufen. Es gibt welche unter ihnen, die wissen, wie man nach Merida kommt, aber niemand ist bereit zu gehen - sie fürchten einen anderen Stamm namens Capongs. Die machen den Einheimischen verdammt Angst. Der Rothaut-Bastard behauptet, dass wir keine Chance haben, den Weg alleine zu finden und dass es keinen Führer für uns zum Anheuern gibt. Was sollen wir jetzt also tun, hä?!";
				link.l1.go = "lepricon_4";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Potion") && GetCharacterItem(pchar, "potion3") >= 12)
			{
				link.l2 = "Ich habe Antidote bei mir.";
				if (GetCharacterItem(pchar, "potion3") > 42) link.l2.go = "lepricon_7";
				else link.l2.go = "lepricon_6";
			}
		break;
		
		case "lepricon_3x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		break;
		
		case "lepricon_4":
            dialog.text = "Hmm, ich verstehe... Kapitän, du musst wissen, dass Feigheit oft von Gier besiegt wird. Versprich eine so großzügige Belohnung, dass ein Mann den Job übernehmen wird... Weißt du was eigentlich? Versuche eine schlauere Option - ihre Frauen. Beschenke sie und frage nach ihren Männern und es besteht die Chance, dass du den Führer findest, den wir brauchen. Verspreche ihr Haufen von Perlen und Spiegeln für die Hilfe ihres Mannes. Sei großzügig und verspreche viel, überzeuge sie.";
			link.l1 = "Heh! Nun, das Mindeste, was ich tun kann, ist es zu versuchen, obwohl ich mir nicht sicher bin, ob es funktionieren wird...";
			link.l1.go = "lepricon_5_1";
			DelLandQuestMark(npchar);
		break;
		
		case "lepricon_5_1":
            dialog.text = "Nun, es gibt eine andere Option... Aber sie ist nicht gerade toll, wenn du verstehst, was ich meine.";
			link.l1 = "Eine andere Option? Leg sie mir vor! Ich bin nicht besonders scharf darauf, zu den indischen Frauen zu gehen und sie anzuflehen, ihre Ehemänner zu überzeugen, sich uns anzuschließen.";
			link.l1.go = "lepricon_5_2";
		break;
		
		case "lepricon_5_2":
            dialog.text = "Diese Option ist so alt wie die Zeit selbst. Zeige ihnen, dass sie dich mehr fürchten sollten als die Kapongs. Du weißt... Du könntest dem Häuptling erzählen, was deine Piraten mit allen Frauen im Dorf anstellen könnten, insbesondere mit seiner Frau und seinen Töchtern. Du könntest sogar einige Drohungen mit Foltern einwerfen. Wie auch immer, ich bin sicher, du wirst etwas finden, um diese Indianer vor dir erzittern zu lassen. Persönlich bin ich kein Fan dieses Weges, und dafür gibt es Gründe.";
			link.l1 = "Gründe? Wie zum Beispiel? In meinem Buch scheint es eine ziemlich effektive und unkomplizierte Lösung zu sein.";
			link.l1.go = "lepricon_5_3";
		break;
		
		case "lepricon_5_3":
            dialog.text = "Zum Anfang, wir werden nach dem nicht gerade die Lieblinge der Stadt sein. Wir könnten in eine Falle oder eine andere unangenehme Situation geraten. Und zweitens, nun... es fühlt sich einfach nicht richtig an. Es ist eine Sache, bewaffnete Gegner auszuschalten, aber es ist eine völlig andere Sache, Frauen zu bedrohen. Ich würde vorschlagen, einen Weg zu finden, mit den Indianern eher... diplomatisch umzugehen.";
			link.l1 = "Habe verstanden, ich werde darüber nachdenken. Vielleicht versuche ich, eine Dame mit Perlen zu umwerben... Oder vielleicht denke ich mir einige fantasievolle Foltermethoden für die Töchter des Häuptlings aus, haha!";
			link.l1.go = "lepricon_5";
		break;
		
		case "lepricon_5":
            dialog.text = "Noch eine Sache, Kapitän, laut dem Häuptling könnten wir im Dschungel auf einen feindlichen Stamm von Indianern stoßen, es ist sehr wahrscheinlich, dass sie nur eine kleine Gruppe von Kannibalen sind, aber besser sicher als leid. Wenn es ein kriegerischer Stamm ist, werden sie ihre Waffen vergiften, also sorge dafür, dass du deine Männer mit Gegengiften versorgst. \nIch und meine Männer haben immer genügend Tränke bei uns. Was deine Piraten angeht... Bring mir einfach die Gegengifte und ich werde sie unter deinen Männern verteilen. Ich brauche mindestens ein Dutzend Tränke dafür. Stelle sicher, dass du auch einige für dich und deine Offiziere mitbringst.";
			link.l1 = "Gut. Ich bringe die Gegengifte.";
			link.l1.go = "lepricon_5x";
		break;
		
		case "lepricon_5x":
           DialogExit();
		   npchar.dialog.currentnode = "lepricon_3";
		   pchar.questTemp.Mtraxx = "merida_advice2";
		   pchar.questTemp.Mtraxx.Merida.Women = "true";
		   pchar.questTemp.Mtraxx.Merida.Potion = "true";
		   AddQuestRecord("Roger_5", "8");
		   sld = characterFromId("Hayamee");
		   LAi_CharacterEnableDialog(sld);
		   AddLandQuestMark(sld, "questmarkmain");
		  // LocatorReloadEnterDisable("Shore_ship3", "boat", false); 
		   bQuestDisableMapEnter = false;
		   DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");// выпустим в море
		   SetFunctionTimerCondition("Mtraxx_MeridaPotionLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "lepricon_6":
			i = GetCharacterItem(pchar, "potion3");
			RemoveItems(pchar, "potion3", i);
			pchar.questTemp.Mtraxx.Merida.Antidote = i;
            dialog.text = "Sehr gut. Gib sie mir. Ich werde den Rest erledigen.";
			link.l1 = "Dort...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_7":
			RemoveItems(pchar, "potion3", 42);
			pchar.questTemp.Mtraxx.Merida.Antidote = 42;
            dialog.text = "Zweiundvierzig Tränke werden genug sein. Den Rest solltest du für dich behalten.";
			link.l1 = "In Ordnung...";
			link.l1.go = "lepricon_8";
		break;
		
		case "lepricon_8":
            DialogExit();
		    npchar.dialog.currentnode = "lepricon_3";
			DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Potion");
		break;
		
		case "lepricon_9":
            dialog.text = "Kapitän, Ihre Indianer - Hayami und Tagofa haben zu lange auf die Geschenke gewartet, die Sie ihnen versprochen hatten, und sind in ein anderes Dorf gezogen, um Kasheeri zu trinken und zu tanzen. Ich habe das Gefühl, dass Ihre Art Geschäfte zu machen uns nicht guttun wird. Es tut mir leid, aber Sie sind raus. Picard wird die Expedition leiten.";
			link.l1 = "Dann zum Teufel mit euch allen!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "19");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_10":
            dialog.text = "Kapitän, was zum Teufel? Wir haben zu viel Zeit für nichts verloren! Ich habe das Gefühl, dass Ihre Art, Geschäfte zu machen, uns nicht gut tun wird. Es tut mir leid, aber Sie sind raus. Picard wird die Expedition leiten.";
			link.l1 = "Verdammt seid ihr alle dann!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_11":
            dialog.text = "Kapitän, was zum Teufel? Sie hatten zehn Tage Zeit, um Leder und Bretter zu finden. Die Stadt Maracaibo ist nicht weit von hier! Ich habe das Gefühl, dass Ihre Art Geschäfte zu machen uns nicht gut tun wird. Es tut mir leid, aber Sie sind raus. Picard wird die Expedition leiten.";
			link.l1 = "Dann leckt mich doch alle!";
			link.l1.go = "exit";
			AddQuestRecord("Roger_5", "20");
			AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;
		
		case "lepricon_12":
            dialog.text = "Kapitän, es tut mir leid, aber ich sollte eigentlich schon längst in La Vega sein, genau wie Sie. Sie müssen meine und Marcus' Existenz vergessen haben. Wie dem auch sei, ich gehe jetzt. Machen Sie ruhig weiter mit dem, was Sie tun, und ich werde alles Marcus erklären. Lebewohl, es ist schade, ich hielt mehr von Ihnen.";
			link.l1 = "Hmph...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_MeridaReturnFail");
		break;
		
		case "lepricon_13":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_03.wav");
            dialog.text = "Also, soweit ich verstehe, hattet ihr Jungs einen Streit. Nicht in der Lage, die Beute zu teilen, stimmt's Charlie Prince?";
			link.l1 = "Leprechaun? Du bist hier... Keine große Überraschung allerdings. Ja, die gierigen Bastarde haben auf das Gesetz gespuckt und versucht, mich zu töten.";
			link.l1.go = "lepricon_14";
			QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload1");
			QuestPointerDelLoc("Judgement_dungeon_01", "quest", "lepricon");
		break;
		
		case "lepricon_14":
            dialog.text = "Ja, sie haben dir ganz schön zugesetzt, Prinz. Du siehst aus wie nasser Scheiß\nWas hast du über den Code gesagt? Lass mich dich aufklären: Ich habe mit Marcus gearbeitet, der angeblich der Hüter dieses Codes ist, ich habe gesehen, wie Männer ihn so oft bespuckt haben, dass ich es nicht wagen würde zu zählen. Einige dieser Männer haben einen schrecklichen Preis bezahlt. Einige von ihnen nicht\nDu kannst tun, was du willst, wenn der Preis es deckt. Besonders wenn niemand zuschaut.";
			link.l1 = "So... du bist also auch wegen des Schatzes hier?";
			link.l1.go = "lepricon_15";
		break;
		
		case "lepricon_15":
            dialog.text = "So eine dumme Frage. Was sollte ich sonst hier tun, so weit von meiner Heimat auf Hispaniola entfernt? Obwohl ich nach allem klüger bin als ihr alle: Ich kenne eure verdorbene Piratennatur. Ich habe einfach gewartet, ließ euch Ratten aufeinander losgehen und nur einen Feind am Leben lassen, aber verwundet und müde.";
			link.l1 = "Feind? So folgst du dem Kodex deines Patrons?! Er tötet Menschen dafür!";
			link.l1.go = "lepricon_16";
		break;
		
		case "lepricon_16":
            dialog.text = "Ich bin kein Untertan des Code Prinz, ich bin kein Pirat. Ich besitze nicht einmal ein Schiff - ich musste eine Tonne mieten, um hierher zu kommen. Ich bin nicht mehr als ein Freibeuter in einer Nussschale. Ich bin ein Jäger, ich jage Büffel und mache Boucan. Verdammt Spanier, die behaupten, dass wir, die französischen Freibeuter, ihr Leben verderben, haben mich dazu gebracht, Unterstützung und Schutz bei Marcus zu suchen. Manchmal helfe ich ihm bei seinen Geschäften dafür\nObwohl ich kein Pirat bin, kämpfen meine Männer und ich gut, du hast uns in Aktion gesehen.";
			link.l1 = "Wir haben gemeinsam Leprechaun überfallen und bekämpft. Wir haben einander den Rücken gedeckt und unser Leben riskiert, um ein anderes zu retten. Ist das alles nichts für dich?";
			link.l1.go = "lepricon_17";
		break;
		
		case "lepricon_17":
			PlaySound("VOICE\English\LE\Leprikon\Lepricon_04.wav");
            dialog.text = "Ich werde ehrlich zu dir sein, Prinz: Ich mochte dich nie. Du bist ein Emporkömmling. Ein frecher Jungspund, ein Fan von Getränken und gefallenen Frauen, der ein paar lukrative Aufträge für Tyrex erledigt hat und sich für einen großen Piraten hielt\nAußerdem bist du von Natur aus ein Schlächter. Du denkst, Cartagena hat dir mehr Gewicht innerhalb der Brüder gegeben? Ho-ho, oh verdammt nein, nur unter den Monstern wie du es bist.";
			link.l1 = "Oh, das ist zum Totlachen! Ha-ha-ha gesprochen von einem wahren Engel selbst! Du alter Bastard!";
			link.l1.go = "lepricon_18";
		break;
		
		case "lepricon_18":
            dialog.text = "Ich denke, wir haben jetzt alles beseitigt. Zeit, diese Komödie zu beenden. Die Teufel haben schon viel zu lange in der Hölle auf dich gewartet.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionLepriconFight");
		break;
		
		case "lepricon_19":
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZapugivanieIndeets"))
			{
				dialog.text = "Gefällt es dir, huh?";
				link.l1 = "Zurück weichen!";
				link.l1.go = "lepricon_20";
			}
			else
			{
				dialog.text = "Nun, was denkst du?";
				link.l1 = "Das ist nicht lustig, Leprechaun. Was zum Teufel?! Ich habe kein Massaker bestellt! Denkst du nicht, das ist zu viel?! Terrax wird nicht erfreut sein!";
				link.l1.go = "lepricon_24";
			}
		break;
		
		case "lepricon_20":
            dialog.text = "Warum dann der schuldige Blick? Gefällt es dir nicht? Lass es mich dir sagen - es wird nur noch schlimmer. Denkst du, das heutige Massaker passierte einfach, weil es so ein Tag ist? Hah, sicher. Das ist Routine. Picard hat nicht einmal gezuckt. Für sie ist es nur ein weiterer Tag, an dem sie tun, was sie lieben.";
			link.l1 = "Und was ist mit dir? Nur auf der Durchreise?";
			link.l1.go = "lepricon_21";
		break;
		
		case "lepricon_21":
            dialog.text = "Ich bin kein Pirat. Und ich hätte lieber nicht Teil der heutigen Ereignisse sein wollen. Und... wenn dich der Anblick von Frauenkörpern auf Meridas verbranntem Boden so sehr stört, warum hast du dich dann gegenüber den Indianern so verhalten, Prinz?";
			link.l1 = "Was sollte ich tun? Alles fallen lassen und zu Marcus kriechen, um mich zu entschuldigen?";
			link.l1.go = "lepricon_22";
		break;
		
		case "lepricon_22":
            dialog.text = "Ich dachte nur, du hättest es vollkommen akzeptiert, angefangen zu denken und zu handeln wie Tirax's Kapitäne. Aber nein, ha! Du bist zu weich für diese Art von Arbeit. Du würdest besser dran sein, deinen Anteil Marcus zu geben und mit eingezogenem Schwanz abzuhauen. Das ist nicht deine Berufung.";
			link.l1 = "Es liegt nicht an dir, für mich zu entscheiden, Leprechaun. Und du hast sicherlich kein Recht, mich zu beleidigen. Ich werde meinen Anteil an niemanden abgeben. Ich werde ihn fair mit Terrax teilen.";
			link.l1.go = "lepricon_23";
		break;
		
		case "lepricon_23":
            dialog.text = "Sicher. Aber wir sollten besser gehen, bevor du in Ohnmacht fällst.";
			link.l1 = "Das ist nicht lustig, verdammt noch mal.";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_24":
            dialog.text = "Dann kennen Sie ihn nicht gut. Da die heutigen Ereignisse Ihnen keine Freude bereiten, hören Sie, was ich zu bieten habe.";
			link.l1 = "Was könnten Sie möglicherweise nach diesem Angebot?";
			link.l1.go = "lepricon_25";
		break;
		
		case "lepricon_25":
            dialog.text = "Du solltest dich besser anstrengen zu zuhören, Junge.";
			link.l1 = "Hmm, mir gefällt dein Ton nicht, Lucas, aber gut, mach weiter.";
			link.l1.go = "lepricon_26";
		break;
		
		case "lepricon_26":
            dialog.text = "Ich kann es mir leisten - Ich habe länger gelebt als du, Prinz. Also habe ich ein scharfes Auge, nicht nur zum Schießen. Willst du wissen, was mir aufgefallen ist?";
			link.l1 = "Sag es einfach!";
			link.l1.go = "lepricon_27";
		break;
		
		case "lepricon_27":
            dialog.text = "Du bist fehl am Platz. Ja, du bist gut. Du machst Fortschritte. Aber nur weil du ein starker Kapitän bist, nicht weil dies wirklich deine Berufung ist. Ich weiß nicht, warum du dich Terrax zugewandt hast, oder warum, aber glaub mir, das ist nicht dein Ding.";
			link.l1 = "Ich habe... ein Ziel. Ich kann dir nicht sagen, was es ist.";
			link.l1.go = "lepricon_28";
		break;
		
		case "lepricon_28":
            dialog.text = "Und bist du ihm schon näher gekommen?";
			link.l1 = "Noch nicht.";
			link.l1.go = "lepricon_29";
		break;
		
		case "lepricon_29":
            dialog.text = "Nun, wenn selbst heute dich näher gebracht hat, gibt es hier nichts mehr zu gewinnen. Du bist ein guter Kerl, Prinz. Du hast die Indianer wie Menschen behandelt. Es ist ironisch, dass du hier bei uns gelandet bist. Mein Rat: Gib deinen Anteil an Terrax, um Problemen aus dem Weg zu gehen, und halte dich von all dem fern - rette deine Seele, solange du kannst.";
			link.l1 = "Ich werde darüber nachdenken.";
			link.l1.go = "lepricon_30";
		break;
		
		case "lepricon_30":
			DialogExit();
			locCameraFromToPos(21.35, 1.54, 0.05, true, 25.55, 0.46, -0.91);
			if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
			{
				PlaySound("People Fight\PistolShot.wav");
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 2.0);
			}
			else
			{
				DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 0.5);
			}
		break;
		
		// Тагофа - проводник к Мериде
		case "tagofa":
            dialog.text = "Tagofa begrüßt dich, Sohn des Meeres. Möchtest du, dass ich dir den Weg zur spanischen Siedlung in den Bergen zeige?";
			link.l1 = "Richtig. Ich sehe, dass du gut mit unserer Sprache umgehen kannst, im Gegensatz zum Rest deines Volkes.";
			link.l1.go = "tagofa_1";
		break;
		
		case "tagofa_1":
            dialog.text = "Tagofa hatte oft Geschäfte mit Yalanaui... Den größten Teil unseres Weges werden wir auf einem Fluss zurücklegen. Du wirst Langboote brauchen. Hast du welche?";
			link.l1 = "Bist du? Wir könnten sie für eine Weile ausleihen...";
			link.l1.go = "tagofa_2";
		break;
		
		case "tagofa_2":
            dialog.text = "Unser Dorf ist klein, wir haben nur sehr wenige Langboote und alle sind nur zum Fischen geeignet. Jetzt brauchen wir gute Langboote, die eine lange Reise aushalten, wie die auf Ihren Schiffen.";
			link.l1 = "Hmm... Wir brauchen dann sechs lange Boote. Das Schiff hat nicht so viele.";
			link.l1.go = "tagofa_3";
		break;
		
		case "tagofa_3":
            dialog.text = "Baut sie dann. Ihr, weiße Leute, könnt eure riesigen Schiffe an Land reparieren, sicher könnt ihr ein paar Langboote bauen.";
			link.l1 = "Heh, es scheint, dass du recht hast, Tagofa. Bring uns zum Fluss, ich hoffe, er ist nicht weit von hier?";
			link.l1.go = "tagofa_4";
		break;
		
		case "tagofa_4":
            dialog.text = "Es ist nicht. Folge mir.";
			link.l1 = "...";
			link.l1.go = "tagofa_5";
		break;
		
		case "tagofa_5":
           DialogExit();
		   chrDisableReloadToLocation = true;
		   npchar.dialog.currentnode = "tagofa_6";
		   LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_MeridaGotoRiver", 5.0);
		break;
		
		case "tagofa_6":
            dialog.text = "Hier ist der Fluss, von dem ich dir erzählt habe. Wir werden unsere Reise von hier aus beginnen. Du baust die Boote und dann werden wir beginnen.";
			link.l1 = "Habe verstanden, Tagofa. Ich werde dir sagen, wenn es erledigt ist.";
			link.l1.go = "tagofa_7";
		break;
		
		case "tagofa_7":
            DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.dialog.currentnode = "tagofa_8";
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.questTemp.Mtraxx = "merida_boats";
			pchar.questTemp.Mtraxx.Boats = "true";
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("TalkSelf_Quest", 2.0);
			// Лепрекона - гулять
			sld = characterFromId("Lepricon");
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			SetFunctionTimerCondition("Mtraxx_MeridaBoatLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;
		
		case "tagofa_8":
            dialog.text = "Sind die Boote bereit, weißer Häuptling?";
			link.l1 = "Ja. Meine Männer sind dabei, sie zu entern.";
			link.l1.go = "tagofa_9";
		break;
		
		case "tagofa_9":
            dialog.text = "Sehr gut. Steig mit mir auf das erste. Tagofa wird den Weg zeigen.";
			link.l1 = "";
			link.l1.go = "tagofa_10";
		break;
		
		case "tagofa_10":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "Mtraxx_MeridaRiverTrip", -1);
			chrDisableReloadToLocation = true;
		break;
		
		case "tagofa_11":
            dialog.text = "Der Flussteil ist erledigt. Wir sind nicht weit von der spanischen Siedlung entfernt. Dort ist der Pfad, halten wir uns daran, dann verirren wir uns nicht. Es ist uns gelungen, einen Wald voller Capong-Jäger zu umrunden, aber auch hier ist ihr Land. Wir müssen vorsichtig sein.";
			link.l1 = "Mach dir keine Sorgen. Wir werden sie auslöschen, sobald sie uns ihre hässlichen bemalten Gesichter zeigen.";
			link.l1.go = "tagofa_12";
		break;
		
		case "tagofa_12":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_warning.win_condition.l1 = "locator";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.location = "Serpentine2";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator_group = "quest";
			pchar.quest.mtraxx_merida_warning.win_condition.l1.locator = "detector1";
			pchar.quest.mtraxx_merida_warning.function = "Mtraxx_MeridaWarning";
			chrDisableReloadToLocation = false;
		break;
		
		case "tagofa_13":
			StartQuestMovie(true, false, true);
            dialog.text = "";
			link.l1 = "He! Tagofa! Schau! Was ist das... mitten auf dem Pfad? Irgendein Indianer-Ding.";
			link.l1.go = "tagofa_14";
			locCameraFromToPos(7.63, 9.07, 11.73, true, 2.97, 9.02, 7.70);
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;
		
		case "tagofa_14":
            DialogExit();
			LAi_SetActorType(pchar);
			LAi_FadeLong("Mtraxx_MeridaWarningCutscene", "");
			locCameraSleep(true);
		break;
		
		case "tagofa_15":
            dialog.text = "Es ist ein Zeichen der Capongs. Eine Warnung. Es sagt dir, dass du anhalten und nicht weitergehen sollst. Die Capongs haben uns bereits entdeckt.";
			link.l1 = "Und was ist, wenn wir weiter gehen? Werden sie uns angreifen?";
			link.l1.go = "tagofa_16";
		break;
		
		case "tagofa_16":
            dialog.text = "Ja, weißer Häuptling. Du musst ihnen bedrohlich erscheinen, da sie uns noch nicht angegriffen haben. Und doch haben sie ein Zeichen für dich gesetzt.";
			link.l1 = "Verdammt nochmal, das Schild. Wir gehen vorwärts... Alle hören zu! Bewaffnet euch! Macht euch bereit! Seid wachsam! Wenn diese Wilden uns ihre hässlichen Gesichter zeigen, werden wir sie alle töten!";
			link.l1.go = "tagofa_17";
		break;
		
		case "tagofa_17":
            DialogExit();
			EndQuestMovie();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_capong.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_capong.win_condition.l1.location = "Merida_jungle_01";
			pchar.quest.mtraxx_merida_capong.function = "Mtraxx_MeridaPrepareCapongAttack";
		break;
		
		case "tagofa_18":
            dialog.text = "Der weiße Häuptling und seine Männer haben die Capongas zerschlagen, Tagofa ist beeindruckt. Die spanische Stadt ist nahe. Es gibt ein Tal, wo du einen Wasserfall sehen wirst. Tagofa wird nicht zu den Spaniern gehen. Ich werde dich in der Nähe des Wasserfalls erwarten.";
			link.l1 = "Sehr gut. Vorwärts!";
			link.l1.go = "tagofa_19";
		break;
		
		case "tagofa_19":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_merida_exittown.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_exittown.win_condition.l1.location = "Merida_ExitTown";
			pchar.quest.mtraxx_merida_exittown.function = "Mtraxx_MeridaExitTown";
			Mtraxx_MeridaCheckOurWarriors();
			AddQuestRecord("Roger_5", "15");
		break;
		
		case "tagofa_20":
            dialog.text = "Wir sind zurückgekehrt, weißer Häuptling. Tagofa hat getan, was er versprochen hat.";
			link.l1 = "Dankbarkeit, Tagofa. Du hast gut gemacht.";
			link.l1.go = "tagofa_21";
		break;
		
		case "tagofa_21":
            dialog.text = "Tagofa sollte gehen. Hayami wartet sehr auf mich. Auf Wiedersehen Sohn des Meeres.";
			link.l1 = "Viel Glück, Sohn des Dschungels. Grüße Deine Frau von mir. Und danke, dass Du uns hilfst.";
			link.l1.go = "tagofa_22";
		break;
		
		case "tagofa_22":
            DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			pchar.quest.mtraxx_merida_final.win_condition.l1 = "location";
			pchar.quest.mtraxx_merida_final.win_condition.l1.location = "Shore_ship3";
			pchar.quest.mtraxx_merida_final.function = "Mtraxx_MeridaFinal";
			ChangeIndianRelation(7.0);
		break;
		
		// дозорный у Мериды
		case "merida_guard":
            dialog.text = "He! Wer bist du und was willst du?";
			link.l1 = "Wir müssen nach Merida und ein Gespräch mit eurem Gouverneur oder wer auch immer an seiner Stelle ist, führen...";
			link.l1.go = "merida_guard_1";
		break;
		
		case "merida_guard_1":
            dialog.text = "Wir lassen Fremde nicht nach Merida. Geh!";
			link.l1 = "Kumpel, wir haben zwei Tage lang hart gerudert und dann gegen Horden von Indianern gekämpft, um nicht einfach so zu gehen. Ich wiederhole, ich möchte mit dem Oberhaupt eures Dorfes sprechen! Wir haben ein... Geschäftsvorschlag für ihn, ja! Und wenn wir uns alle einig sind, bleibt euer Dorf unversehrt.";
			link.l1.go = "merida_guard_2";
		break;
		
		case "merida_guard_2":
            dialog.text = "Drohst du mir, Schurke?";
			link.l1 = "Wie hast du das herausgefunden? Ah ja in der Tat, ich mache Drohungen. Entweder wir bekommen, was wir hier mit Frieden oder mit Gewalt suchen, und du hast die Ehre, über das Schicksal deines Dorfes zu entscheiden.";
			link.l1.go = "merida_guard_3";
		break;
		
		case "merida_guard_3":
            dialog.text = "Du wirst niemals Merida betreten, du verdammter Pirat! Alarm! Feind an den Toren!";
			link.l1 = "Solch ein unvernünftiger Herr...";
			link.l1.go = "merida_guard_4";
		break;
		
		case "merida_guard_4":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			DoQuestFunctionDelay("Mtraxx_MeridaHouseGuards", 5.0);
		break;
		
		// мэр Мериды
		case "merida_head":
            dialog.text = "Verdammte Diebe! Was wollt ihr von uns?! Dies ist eine kleine, bescheidene Siedlung. Wir haben weder Gold noch Silber! Wie habt ihr überhaupt von uns erfahren?";
			link.l1 = "Oh, spielen Sie nicht unschuldig und ahnungslos, Eure Exzellenz. Die ganze Welt ist bereits voller Gerüchte über Ihre Opale.";
			link.l1.go = "merida_head_1";
		break;
		
		case "merida_head_1":
            dialog.text = "Und ihr habt dieses gottlose Massaker wegen... Gerüchten verursacht?! Niemanden verschont! Bestien... Damit ihr es wisst: Die Lagerstätten sind weit weg von hier. Es gibt hier nichts für euch zu holen. Geht.";
			link.l1 = "Du hast dieses gottlose Massaker begonnen. Die Zivilisten kämpften an der Seite deiner Soldaten. Ich werde nie glauben, dass solch sinnloser Heldentum nur möglich ist, um ein paar kahle Mauern zu schützen.";
			link.l1.go = "merida_head_2";
		break;
		
		case "merida_head_2":
            dialog.text = "Wissen Sie, wie viel Mühe in den Bau dieser Mauern gesteckt wurde? Wir haben keine externen Bauarbeiter eingestellt - wir haben sie selbst gebaut, Stein für Stein. Jeder einzelne Bewohner. Sogar ich, mit diesen eigenen Händen.";
			link.l1 = "So rührende Geschichte... Und was ist mit den Möbeln? Habt ihr die auch selbst gemacht? Was für ein fein geschnitzter Stuhl. Und Tisch. Und Schränke. Ist das gebeizte Eiche? Oder Ebenholz? Ein bisschen zu luxuriös für eine 'bescheidene Siedlung', meinst du nicht?";
			link.l1.go = "merida_head_3";
		break;
		
		case "merida_head_3":
            dialog.text = "Die Gier hat deinen Verstand vernebelt, Schurke.";
			link.l1 = "Komplizieren Sie die Dinge nicht, Senor Gouverneur. Sonst werden Sie es bereuen.";
			link.l1.go = "merida_head_4";
		break;
		
		case "merida_head_4":
            dialog.text = "Wirst du mich foltern, du verdammter Pirat? Schade für dich - ich glaube an den allmächtigen Gott. Und ich werde als Märtyrer aufsteigen, wenn du es übertreibst.";
			link.l1 = "Hm-m...";
			link.l1.go = "merida_head_5";
		break;

		case "merida_head_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_6", "Quest\Roger.c");
		break;
		
		case "merida_head_6":
            dialog.text = "Mein Freund, er wird nicht so reden. Lass mich das regeln.";
			link.l1 = "Oh?";
			link.l1.go = "merida_head_7";
		break;
		
		case "merida_head_7":
            dialog.text = "Ich erinnere mich an alles, was diese aufgeblasenen Spanier mir auf dieser verfluchten Plantage angetan haben. Ich würde es Ihnen gerne zeigen, Prinz. Und ich werde Ihnen dabei ein paar Geschichten erzählen. Ihnen wird nicht langweilig werden.";
			link.l1 = "Und was, wenn du dich hinreißen lässt?";
			link.l1.go = "merida_head_8";
		break;
		
	case "merida_head_8":
            dialog.text = "Er wird nicht nett reden. Ich kenne seine Art.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) >= 50 && GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50)
			{
				link.l1 = "(Vertrauenswürdig) (Ehre) (Führung) Das ist genug Blut für heute, Jean. Ich werde das selbst in die Hand nehmen.";
				link.l1.go = "merida_head_dobro_1";
				notification("Trustworthy", "Trustworthy");
				notification("Reputation Check Passed", "None");
				notification("Skill Check Passed", SKILL_Leadership);
			}
			else
			{
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
				if (sti(pchar.reputation.nobility) < 50) notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(50))+")", "None");
				if (GetCharacterSkill(pchar, SKILL_LEADERSHIP) < 50) notification("Skill Check Failed (50)", SKILL_LEADERSHIP);
			}
			link.l2 = "Mach es. Ich mische mich nicht ein. Und ich schaue auch nicht zu.";
			link.l2.go = "merida_head_zlo_1";
		break;
		
		case "merida_head_zlo_1":
            dialog.text = "Wenn ich nicht in deiner Schuld stände, hätte ich ein paar ausgesuchte Worte für dich... Verdammt. Mach weiter. Jetzt ist es Zeit für die echte Arbeit.";
			link.l1 = "Überanstrenge dich nicht.";
			link.l1.go = "rocur_42";
		break;
		
		case "merida_head_dobro_1":
            dialog.text = "Wie du wünschst, mein Freund. Es wird Spaß machen zuzusehen.";
			link.l1 = "Lächle nicht zu früh.";
			link.l1.go = "merida_head_dobro_2";
		break;
		
		case "merida_head_dobro_2":
			StartInstantDialog("Merida_Head", "merida_head_dobro_3", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_3":
            dialog.text = "Du sagst, du wirst das selbst in die Hand nehmen, ohne Blutvergießen, du verdammter Dieb? Es gibt nichts, was du sagen könntest, um Steine aus dem Nichts erscheinen zu lassen!";
			link.l1 = "Sie sollten besser auftauchen, Gouverneur. Andernfalls werden wir die Stadt bis zum Boden niederbrennen und jeden außer Ihnen töten. Mir gefällt diese Lösung nicht, aber ich bin bereit, meine Ehre für meine Sache zu kompromittieren. Ihre Pflicht hingegen besteht darin, die Zivilisten, überlebenden Soldaten und Arbeiter von Merida zu schützen. Oder würden Sie es vorziehen, 'als Märtyrer aufzusteigen' auf Kosten ihres Leidens? Das klingt für mich nicht sehr gottähnlich.";
			link.l1.go = "merida_head_dobro_4";
		break;
		
		case "merida_head_dobro_4":
            dialog.text = "Verdammt seist du...\nDort... in der Truhe. Schont nur die Stadtbewohner!";
			if (GetSummonSkillFromName(pchar, SKILL_Sneak) >= 50)
			{
				link.l1 = "(Schleichen) Ist alles in der Truhe?";
				link.l1.go = "merida_head_dobro_vnimatelnost_1";
				notification("Skill Check Passed", SKILL_Sneak);
			}
			else
			{
				link.l1 = "Ich halte mein Wort. Lebewohl, Gouverneur.";
				link.l1.go = "merida_head_dobro_5";
				notification("Skill Check Failed (50)", SKILL_SNEAK);
			}
		break;
		
		case "merida_head_dobro_vnimatelnost_1":
            dialog.text = "Verdammt seist du zur Hölle!\nDie Truhe hat auch einen falschen Boden. Nimm alles!!";
			link.l1 = "...";
			link.l1.go = "merida_head_dobro_vnimatelnost_2";
			pchar.questTemp.Mtraxx_MeridaKamushki = true;
		break;
		
		case "merida_head_dobro_vnimatelnost_2":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto2", "Mtraxx_MeridaOpenChest", -1);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
		break;
		
		case "merida_head_dobro_vnimatelnost_3":
            dialog.text = "Glatte Sache, Prinz. Entschuldigung für die Unterschätzung Ihrer.";
			link.l1 = "Zufrieden?";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_5":
			StartInstantDialog("Mrt_Rocur", "merida_head_dobro_6", "Quest\Roger.c");
		break;
		
		case "merida_head_dobro_6":
            dialog.text = "Glatt, Prinz.";
			link.l1 = "Zufrieden?";
			link.l1.go = "merida_head_dobro_7";
		break;
		
		case "merida_head_dobro_7":
            dialog.text = "More than. But... you'll see for yourself. You go ahead; I'll dig around a little more.";
			link.l1 = "...";
			link.l1.go = "rocur_43";
		break;
		
		/*case "merida_head_99999":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
		break;*/
		
		case "merida_head_sleep":
            dialog.text = "Du hast versprochen, die Stadt zu verlassen, sobald du die Edelsteine hast... Du hast sie jetzt und deine Schurken haben unsere Häuser in Brand gesetzt! Du bist ein Lügner und ein verdammter Pirat! Ich hoffe, die Flammen der Hölle werden für dich genauso heiß sein!!!";
			link.l1 = "";
			link.l1.go = "exit";
			locCameraFromToPos(19.18, 1.28, -0.28, true, 24.88, 1.62, -1.19);
			AddDialogExitQuest("Mtraxx_RetributionSleep2");
		break;
		
		// капитан пинаса Китти
		case "kittycap":
            dialog.text = TimeGreeting()+", gnädiger Herr. Was ist Ihr Anliegen hier?";
			link.l1 = "Ich komme aus Tyrex. Mir wurde befohlen, Ihr Schiff nach Bridgetown zu begleiten. Sind Sie bereit?";
			link.l1.go = "kittycap_1";
		break;
		
		case "kittycap_1":
            dialog.text = "Nun, endlich! Ja, meine Mannschaft ist bereit, sofort in See zu stechen!";
			link.l1 = "Hervorragend. Bereite die Segel vor, Kapitän. Bring uns auf den Weg!";
			link.l1.go = "kittycap_2";
		break;
		
		case "kittycap_2":
		    DialogExit();
            LAi_CharacterDisableDialog(npchar);
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			LAi_SetImmortal(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
		    pchar.quest.mtraxx_ignasio_sail.win_condition.l1 = "location";
			pchar.quest.mtraxx_ignasio_sail.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.mtraxx_ignasio_sail.function = "Mtraxx_IgnasioArrive";
			SetFunctionTimerCondition("Mtraxx_IgnasioTimeOver", 0, 0, 30, false);
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1 = "NPC_Death";
			pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1.character = "Mtr_KittyCap";
			pchar.quest.mtraxx_ignasio_sinkkitty.function = "Mtraxx_IgnasioKittySink";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "kittycap_3":
            dialog.text = "Danke, dass Sie mir geholfen haben, Kapitän! Mit Ihnen an meiner Seite war ich so sicher, als ob ich hinter den Mauern der Festung wäre.";
			link.l1 = "Hah, erwähn es nicht Kumpel! Alles geht auf Marcus. Viel Glück dir, Kamerad!";
			link.l1.go = "kittycap_4";
		break;
		
		case "kittycap_4":
            DialogExit();
			npchar.lifeday = 0;
			RemoveCharacterCompanion(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			Mtraxx_IgnasioCreateMarko();
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		// Игнасио Марко
		case "ignasio":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_01.wav");
			dialog.text = "Grüße an den tapferen Kapitän! Lassen Sie mich mich vorstellen - ein Freibeuter Englands, Ignacio Marco vom Torero.";
			link.l1 = TimeGreeting()+", Freund. Kapitän "+GetFullName(pchar)+" zu Ihren Diensten. Wie kann ich Ihnen helfen?";
			link.l1.go = "ignasio_1";
		break;
		
		case "ignasio_1":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "Oh, ich kenne dich! Monseniour "+GetFullName(pchar)+"! Gerüchte über Ihre Ressourcen und Gönner sind mir im gesamten Archipel zu Ohren gekommen. Ich glaube, mein Angebot wird für Sie ziemlich interessant sein.";
			link.l1 = "Welches Angebot?";
			link.l1.go = "ignasio_2";
		break;
		
		case "ignasio_2":
            dialog.text = "Lass uns in eine Taverne gehen und etwas trinken. Ich werde dir alles erzählen. Das ist kein Straßengespräch.";
			link.l1 = "Sehr gut... Los geht's!";
			link.l1.go = "ignasio_3";
		break;
		
		case "ignasio_3":
            DialogExit();
			FreeSitLocator("Bridgetown_tavern", "sit_front2");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Bridgetown_tavern", "sit", "sit_front2", "Mtraxx_IgnasioInTavern", -1);
		break;
		
		case "ignasio_4":
			LAi_SetSitType(pchar);
            dialog.text = "Eine Runde, Kapitän?";
			link.l1 = "Sicher!";
			link.l1.go = "ignasio_5";
		break;
		
		case "ignasio_5":
			LAi_Fade("", "");
            dialog.text = "Heh, sie mischen hier tatsächlich keinen Rum mit Wasser...";
			link.l1 = "Und behandle Kunden nicht mit faulem Fisch, ja-ja. Also, was ist der Deal?";
			link.l1.go = "ignasio_6";
		break;
		
		case "ignasio_6":
            dialog.text = "Ich mag Ihre Geradlinigkeit, Monsieur. Sagen Sie, sind Sie sich des Handelskrieges zwischen den Engländern und den Niederländern bewusst?";
			link.l1 = "Ich bin es. Hatte das Vergnügen, daran teilzunehmen.";
			link.l1.go = "ignasio_7";
		break;
		
		case "ignasio_7":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_02.wav");
			dialog.text = "Keine Notwendigkeit, es dann zu erklären. Als englischer Freibeuter kämpfe ich in diesem Krieg auf ihrer Seite. Du bist hauptsächlich ein Freelancer. Was dich gleichgültig macht, gegen welche Seite du kämpfst...";
			link.l1 = "Fast. Ich überquere Frankreich nicht, es tut mir leid.";
			link.l1.go = "ignasio_8";
		break;
		
		case "ignasio_8":
            dialog.text = "Aber sicher, Kapitän! Also, gleich zur Sache: es gibt eine kleine bewohnte Insel zwischen Curacao und Trinidad, sie ist nicht auf den Karten... Seit neuester Zeit, würde ich sagen sehr neuester Zeit, haben die Niederländer begonnen, sie als vorübergehenden Stopp zum Nachschub und zur Reparatur zu nutzen. Es scheint, dass sie glauben, dass nur sie von dieser Insel wissen. Falsch. He-he\nVor ein paar Tagen wurde ein Silberkonvoi von einem... Sturm getroffen, und nun reparieren die Niederländer ihre Schiffe auf dieser Insel. Das Flaggschiff hat ihren Mast verloren, also wird es einige Zeit dauern, ihn zu reparieren. Die Niederländer sind mit Reparaturen beschäftigt, und die Besatzungen sind größtenteils über die Insel verstreut...";
			link.l1 = "Und dann tauchen wir plötzlich auf, um den Tag zu retten?";
			link.l1.go = "ignasio_9";
		break;
		
		case "ignasio_9":
            dialog.text = "Genau, Kapitän. Ich kann das nicht alleine machen, aber mit Ihnen - das ist eine völlig andere Geschichte. Wirst du es riskieren? Ich habe ein großartiges Schiff, die Crew ist großartig und ich habe eine gute Menge an Erfahrung. Ihre Fähigkeiten ... sind ebenfalls lobenswert.";
			link.l1 = "Wie viel Zeit haben wir?";
			link.l1.go = "ignasio_10";
		break;
		
		case "ignasio_10":
            dialog.text = "Genug, wenn wir es nicht verschwenden und sofort aufbrechen.";
			link.l1 = "Dann lass uns mit Munition und Waffen nachrüsten, Kapitän Ignacio Marco, und die Segel setzen. Was sind die genauen Koordinaten der Insel?";
			link.l1.go = "ignasio_11";
		break;
		
		case "ignasio_11":
            dialog.text = "12'40 Nord, 64'11 West. Hast du das?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Isladecoche")) link.l1 = "Ha! Déjà-vu... Verstanden.";
			else link.l1 = "Habs verstanden.";
			link.l1.go = "ignasio_12";
		break;
		
		case "ignasio_12":
            dialog.text = "Kurs auf die 'Torero'. Ich werde auf dich warten, Kapitän!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioAddMarko");
		break;
		
		case "ignasio_13":
            PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_03.wav");
			dialog.text = "Hölle eines Kampfes, nicht wahr, Kapitän? Jetzt der angenehme Teil: Wir teilen unsere Anteile. Eine Hälfte geht an mich und meine Männer.";
			link.l1 = "Sehr gut, lass es uns tun...";
			link.l1.go = "ignasio_14";
		break;
		
		case "ignasio_14":
			LAi_Fade("", "");
			WaitDate("", 0, 0, 0, 3, 10); 
			pchar.questTemp.Mtraxx.Silver = GetSquadronGoods(pchar, GOOD_SILVER)-sti(pchar.questTemp.Mtraxx.Silver);
			pchar.questTemp.Mtraxx.Mahogany = GetSquadronGoods(pchar, GOOD_MAHOGANY)-sti(pchar.questTemp.Mtraxx.Mahogany);
			if (sti(pchar.questTemp.Mtraxx.Silver) < 100)
			{
				dialog.text = "Kapitän, was ist los? Wo ist unser Silber? Haben Sie unseren Preis versenkt?";
				if (sti(pchar.questTemp.Mtraxx.Mahogany) < 200) 
				{
					link.l1 = "Hm...";
					link.l1.go = "ignasio_15_1";
				}
				else
				{
					link.l1 = "Silber wurde irgendwie verschwendet, obwohl wir etwas Rotholz bekommen haben. Lasst uns es teilen.";
					link.l1.go = "ignasio_15_11";
				}
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 300 && sti(pchar.questTemp.Mtraxx.Silver) > 100)
			{
				dialog.text = "Hm.. Das ist arm. Ich dachte, es wäre viel mehr.";
				link.l1 = "Wir haben, was wir haben.";
				link.l1.go = "ignasio_15_2";
				break;
			}
			if (sti(pchar.questTemp.Mtraxx.Silver) < 700 && sti(pchar.questTemp.Mtraxx.Silver) > 300)
			{
				dialog.text = "Nicht schlecht, nicht schlecht. Obwohl, ich dachte, es gäbe mehr.";
				link.l1 = "Wir haben, was wir haben.";
				link.l1.go = "ignasio_15_3";
				break;
			}
            dialog.text = "Gut gemacht, Monseniour. Das ist ein feiner Preis...";
			link.l1 = "Kann Ihnen in diesem Punkt nicht widersprechen, Kapitän.";
			link.l1.go = "ignasio_15_4";
		break;
		
		case "ignasio_15_1":
			dialog.text = "Sieht so aus, als hätten Sie ernsthafte Probleme mit Ihrem Kopf. Wir gehen! Jungs!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_11":
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
			dialog.text = "Zumindest bekommen wir etwas aus diesem... Jungs! Auf geht's!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_2":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "Es ist etwas. Lass uns unsere Wege trennen.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_3":
            RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "Es ist etwas. Lass uns unsere Wege teilen. Es ist immerhin ein Erfolg, heh!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_15_4":
			RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver)/2));
			RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany)/2));
            dialog.text = "Wir hatten ein sehr profitables Treffen. Vielleicht ist es nicht das letzte Mal, dass wir zusammen Geschäfte machen, Kapitän!";
			link.l1 = "Ruf mich an, wenn du mehr fette Händler findest, he-he!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;
		
		case "ignasio_boarding":
			PlaySound("Voice\English\LE\Ignasio_Marko\Ignasio_04.wav");
            dialog.text = "Ich nehme an, das ist kein Zufall, Kapitän?";
			link.l1 = "Du wärest nicht schlau, wenn du es nicht sehen würdest. Du schuldest mir etwas für die Vorbereitung. Du weißt, wovon ich rede. Außerdem schuldest du mir etwas für die Einrichtung meines Freundes Jean Picard. Er wurde nach deinem Plan an eine Plantage verkauft... Du hast Ignacio verloren. Ich werde dich aufhängen, aber du kannst deine Strafe mildern...";
			link.l1.go = "ignasio_boarding_1";
		break;
		
		case "ignasio_boarding_1":
            dialog.text = "Ich frage mich sogar - was könnte ich tun, um Mitleid bei dir zu erwecken?";
			link.l1 = "Ich brauche Informationen. Ich werde dich in meinen Laderaum stecken, wo wir über deine Pläne in Havanna sprechen werden...";
			link.l1.go = "ignasio_boarding_2";
		break;
		
		case "ignasio_boarding_2":
            dialog.text = RandSwear()+" Ich habe das nicht kommen sehen! Denk nicht mal dran. Barbazon wird in kürzester Zeit von meinem Verrat erfahren. Du solltest besser nicht wissen, was er mit Leuten macht, die ihn verraten haben. Ich habe es gesehen.";
			link.l1 = "Also ist es besser gehängt zu werden?";
			link.l1.go = "ignasio_boarding_3";
		break;
		
		case "ignasio_boarding_3":
            dialog.text = "Ich würde lieber im Kampf sterben!";
			link.l1 = "...";
			link.l1.go = "ignasio_boarding_4";
		break;
		
		case "ignasio_boarding_4":
            DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "spy_sailor":
            dialog.text = "Kapitän! Kapitän! Beeil dich! Die spanische Militäreskorte ist hinter uns her!";
			link.l1 = RandSwear()+"Ich habe das erwartet... Dasselbe ist mit Picard passiert. Hast du gesehen, wie viele von ihnen draußen waren?";
			link.l1.go = "spy_sailor_1";
		break;
		
		case "spy_sailor_1":
            dialog.text = "Ja, Kapitän. Drei Schiffe. Ihr Flaggschiff ist eine Galeone, die größte, die ich je gesehen habe, und sie bewegt sich schnell, die anderen beiden sind eine Korvette und eine Xebec.";
			link.l1 = "Alle an Bord. Wir könnten immer noch in der Lage sein zu fliehen.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_IgnasioOurEscape");
		break;
		
		// индей-кариб в гроте Порто-Белло
		case "grot_canib":
            dialog.text = "Haya! Verdammt yalanaui kommt in unseren Wald! Tötet ihn! Haya!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekGrotFight");
		break;
		
		// бандит у пещеры Панамы
		case "cave_bandit":
            dialog.text = "He! Was zum Teufel machst du hier? A-ah, du stiehlst die Sachen von anderen? Nun, du bist am Arsch!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekCaveFight");
		break;
		
		case "carpenter":
            dialog.text = "He, haltet alle sofort an! Oder ich nehm euch alle mit einer Traubenschuss Salve!"+RandSwear()+"";
			link.l1 = "Wir bewegen uns gerade nirgendwohin. Aber hör zu, Kumpel - es gibt keine Möglichkeit, dass du uns alle auf einmal umbringst. Einige von uns werden dich in Stücke schneiden, während du nachlädst. Es wäre besser, wenn wir jetzt gleich reden würden.";
			link.l1.go = "carpenter_1";
			locCameraFromToPos(-71.57, 14.57, -130.20, true, -63.78, 11.36, -125.50);
		break;
		
		case "carpenter_1":
            dialog.text = "Bist du hier der Anführer? Antwort mir!";
			link.l1 = "Ich bin Kapitän "+GetFullName(pchar)+". Und du musst Red Wolfs Stellvertreter sein, während er von hier weg ist, habe ich recht?";
			link.l1.go = "carpenter_2";
		break;
		
		case "carpenter_2":
            dialog.text = "Was machen Sie hier Kapitän "+GetFullName(pchar)+"! Wir laden keine Gäste an diesen Ort ein!";
			link.l1 = "Wie heißt du? Ich möchte wissen, mit wem ich spreche.";
			link.l1.go = "carpenter_3";
		break;
		
		case "carpenter_3":
            dialog.text = "Mein Name ist Rodgar Janssen.";
			link.l1 = "Ich sehe, dass ihr Kerle hier im Dunkeln steht. Ihr habt keinen Kapitän mehr. Und eure Korvette ist auch weg. Die 'Freyja' wurde von den Spaniern nicht weit von Hispaniola zum Teufel gebombt. Ihre Besatzung wurde bis zum letzten Mann niedergemetzelt...";
			link.l1.go = "carpenter_4";
		break;
		
		case "carpenter_4":
            dialog.text = RandSwear()+"Wulfric... Aahhh-ghhhhh!!! ... Aber wie kann ich wissen, dass du die Wahrheit sagst?";
			link.l1 = "Ich habe das Logbuch Ihres Ex-Kapitäns! Wir haben ein paar Gegenstände aus Freyjas Wrack geborgen. Dank des Logbuchs habe ich diese Insel und diesen... euren Hort gefunden.";
			link.l1.go = "carpenter_5";
		break;
		
		case "carpenter_5":
            dialog.text = "Heh! Du schuldest mir noch eine Antwort: Warum bist du hier in diesem unbekannten Land?";
			link.l1 = "Ich werde nicht lügen, Kumpel. Sie sagen, der Rote Wolf besaß ein ziemliches Vermögen. Ich bin hier, um es zu finden, da auf seinem Schiff kein solcher Schatz gefunden wurde. Ich glaube, sie sollten dem guten Volk gehören, Wulfric kann sie jetzt sowieso nicht mehr gebrauchen.";
			link.l1.go = "carpenter_6";
		break;
		
		case "carpenter_6":
            dialog.text = "Ha! Kumpel, ich werde dich enttäuschen: Weder ich noch jemand anderes aus der Besatzung haben jemals Wolfs Schätze gesehen. Es war zu riskant, ihn zu fragen.";
			link.l1 = "Dann sollte ich sie wohl in eurem Dorf suchen. Wirst du deine Waffe wegnehmen oder sollte ich das Dorf stürmen? Du hast keine Chance Rodgar. Wenn nötig, bringe ich Waffen und mehr Männer.";
			link.l1.go = "carpenter_7";
		break;
		
		case "carpenter_7":
            dialog.text = "Bevor wir sterben, werden wir viele von euch Bastarden zur Hölle mitnehmen! Vielleicht auch dich!";
			link.l1 = "Bist du dir sicher? Du hast keinen Kapitän, kein Schiff und niemand wird kommen, um dich zu retten. Selbst wenn ich einfach gehe, werdet ihr alle bald genug verhungern!";
			link.l1.go = "carpenter_8";
		break;
		
		case "carpenter_8":
            dialog.text = "Hmm... hast du irgendwelche Vorschläge?";
			link.l1 = "Ja, das tue ich. Tritt einen Schritt zurück von der Kanone und halte deine Männer in Schach. Ich schwöre, ich werde dir oder deinen Männern keinen Schaden zufügen. Wenn du willst, kannst du dich meiner Crew anschließen oder wir bringen dich zu einer Zivilisation.";
			link.l1.go = "carpenter_9";
		break;
		
		case "carpenter_9":
            dialog.text = "Schwöre es vor deinen Männern laut und klar!";
			link.l1 = "Ich schwöre! Sie haben mein Wort: Sie und Ihre Männer werden nicht verletzt.";
			link.l1.go = "carpenter_10";
		break;
		
		case "carpenter_10":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_11";
			LAi_SetActorType(npchar);
			LAi_ActorDialog(npchar, pchar, "", -1, 0);
			for (i=1; i<=2; i++) // 
			{
				sld = CharacterFromID("Islamona_fort_pirate_"+i);
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
		break;
		
		case "carpenter_11":
            dialog.text = "Ich hoffe, Sie halten Ihr Wort, Kapitän.";
			link.l1 = "Ich tue immer. Wie viele von euch sind übrig?";
			link.l1.go = "carpenter_12";
		break;
		
		case "carpenter_12":
            dialog.text = "Sie sehen uns alle. Drei. Die anderen starben im Dschungel, als sie Sie angriffen. Ich sagte ihnen, sie sollen es nicht tun, aber sie hörten nicht zu...";
			link.l1 = "Ich sehe...";
			link.l1.go = "carpenter_13";
		break;
		
		case "carpenter_13":
            dialog.text = "Das Essen ging zur Neige. Wir begannen Papageien zu jagen. Die 'Freyja' war zu lange abwesend. Wir hatten unsere Vermutungen und sie bewahrheiteten sich.";
			link.l1 = "Dank Gott, dass ich mich entschieden habe, auf Schatzsuche zu gehen. Wo glaubst du, hat er sie versteckt?";
			link.l1.go = "carpenter_14";
		break;
		
		case "carpenter_14":
            dialog.text = "Ich habe es dir schon gesagt: Niemand hat sie jemals gesehen. Wulfric war vorsichtig mit seinem Anteil, hat ihn nie verschwendet. Er war fair zu uns, aber jeder, der versuchte, sein Versteck zu finden, ist verschwunden. Du bist frei, das Dorf zu durchsuchen, wenn du willst.";
			link.l1 = "Das ist mein Plan. Wo ist das Haus von Rotem Wolf?";
			link.l1.go = "carpenter_15";
		break;
		
		case "carpenter_15":
            dialog.text = "Das einzige zweistöckige Gebäude, das wir hier haben.";
			link.l1 = "Gut. Übrigens, was ist dein Beruf?";
			link.l1.go = "carpenter_16";
		break;
		
		case "carpenter_16":
			worldMap.labels.islamona.icon = 5;
			worldMap.labels.islamona.text = CheckingTranslate(LanguageOpenFile("LocLables.txt"),"Islamona");
            dialog.text = "Ich bin ein Zimmermann und diese beiden sind meine Gehilfen. Früher haben wir die 'Freyja' repariert und ausgetrickst. Wir könnten in deiner Mannschaft nützlich sein.";
			link.l1 = "Ich verstehe. Sehr gut, du bist dabei, wir werden später über die Details sprechen. Hol diese Pistole vom Eingang. Und Rodgar, verlass das Dorf nicht, während ich das Versteck suche.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_WolfreekInFort");
		break;
		
		case "carpenter_17":
            dialog.text = "Befehle, Kapitän?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.WolfreekGord"))
			{
				link.l1 = "Ja. Die Schätze Ihres Kapitäns wurden gefunden. Er hat sie gut versteckt, aber ich habe ihn überlistet!";
				link.l1.go = "carpenter_18";
				break;
			}
			// Jason Исла Мона -->
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "start")
			{
				link.l1 = "Rodgar, was denkst du, können wir noch etwas mit dieser Basis anfangen?";
				link.l1.go = "IslaMona";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "get_tools")
			{
				link.l1 = "Rodgar, ich habe die Werkzeuge gebracht. Sie sollten dir bereits geliefert worden sein.";
				link.l1.go = "IslaMona_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "himenes")
			{
				link.l1 = "Willkommen! Das ist Rodrigo Jimenez, der Anführer einer kleinen, aber sehr fleißigen Gemeinschaft aus Cadiz. Senor Jimenez hat freundlicherweise zugestimmt, sich vorübergehend in unserem Land niederzulassen und uns beim Bau zu helfen.";
				link.l1.go = "IslaMona_12";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "nextday")
			{
				link.l1 = "Rodgar, wie geht es dir? Hast du einen guten Rat für mich?";
				link.l1.go = "IslaMona_18";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "stalk")
			{
				link.l1 = "Rodgar, ich brauche einen Gefallen.";
				link.l1.go = "IslaMona_20";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "dublon_wait" && GetCharacterItem(pchar, "gold_dublon") >=600)
			{
				link.l1 = "Ich habe die Doubloons für dich mitgebracht, verschwende sie nur nicht sofort alles auf Schnaps.";
				link.l1.go = "IslaMona_24";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "storage" && !CheckAttribute(pchar, "questTemp.IslaMona.Food") && IslaMona_CheckFood())
			{
				link.l1 = "Rodgar, überprüfe das Lagerhaus. Ich habe die Medizin und die Vorräte gebracht.";
				link.l1.go = "IslaMona_30";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "village")
			{
				link.l1 = "Hallo, Rodgar, wie geht es in der neuen Siedlung?";
				link.l1.go = "IslaMona_32";
				break;
			}
			if (!CheckAttribute(npchar, "quest.stalk")) // ремонт кораблей
			{
				link.l2 = "Rodgar, mein Schiff braucht Reparaturen. Seid ihr und eure Leute bereit?";
				link.l2.go = "repair";
			}
			link.l3 = "Rodgar, ich möchte eines meiner Schiffe hier lassen.";
			if (CheckAttribute(npchar, "portman.info")) link.l3.go = "shipstock";
			else link.l3.go = "shipstock_info";
			if (CheckAttribute(npchar, "portman") && sti(npchar.portman > 0))
			{
				link.l4 = "Rodgar, ich möchte eines meiner Schiffe zurücknehmen.";
				link.l4.go = "shipstockreturn";
			}
			if (!CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Schau mal, gibt es irgendwelches leeres Gebäude, das ich als Lagerhaus nutzen könnte?";
				link.l5.go = "storadge";
			}
			if (CheckAttribute(npchar, "storadge"))
			{
				link.l5 = "Rodgar, ich möchte ein Lagerhaus sehen.";
				link.l5.go = "storadge_3";
			}
			if (CheckAttribute(npchar, "crew"))
			{
				link.l6 = "Rodgar, ich möchte einen Teil der Mannschaft auf der Insel lassen.";
				link.l6.go = "crew";
			}
			if (CheckAttribute(npchar, "crew") && sti(npchar.crew.qty) > 0)
			{
				link.l7 = "Rodgar, ich möchte meine Seeleute mit mir zurück aufs Meer nehmen.";
				link.l7.go = "crew_3";
			}// <-- Исла Мона
			link.l99 = "Noch nichts...";
			link.l99.go = "carpenter_exit";
		break;
		
		case "Crew":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchHireCrew();
		break;
		
		case "carpenter_exit":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
		break;
		
		case "carpenter_18":
            dialog.text = "Herzlichen Glückwunsch, Kapitän. Was machen wir als nächstes? Verlassen wir?";
			link.l1 = "Bist du schon lange hier?";
			link.l1.go = "carpenter_19";
		break;
		
		case "carpenter_19":
            dialog.text = "Viel zu lange. Es ist ein Jahr her, seit Wulfric mich hier zum Anführer gemacht hat.";
			link.l1 = "Ich habe entschieden, dass diese geheime Basis zu gut ist, um verschwendet zu werden. Das Dorf gehört jetzt mir. Ich kann dich und deine Männer hier lassen, wenn du willst. Rum, Vorräte, Medizin - alles deins.";
			link.l1.go = "carpenter_20";
		break;
		
		case "carpenter_20":
            dialog.text = "Das wäre großartig, Kapitän. Ich habe mich an das Leben an diesem Strand, auf dieser Insel gewöhnt.";
			link.l1 = "Prächtig. Übrigens, wie heißt die Insel?";
			link.l1.go = "carpenter_21";
		break;
		
		case "carpenter_21":
            dialog.text = "Isla Mona.";
			link.l1 = "Isla Mona... Vielleicht bauen wir eines Tages mehr Häuser und Strukturen hier... Aber später. Im Moment behältst du hier die gleiche Rolle, aber unter einem neuen Kapitän.";
			link.l1.go = "carpenter_22";
		break;
		
		case "carpenter_22":
            dialog.text = "Abgemacht. Kümmern Sie sich nur um sich selbst, Kapitän und vergessen Sie nicht, uns mit Proviant zu versorgen.";
			link.l1 = "Sicherlich Rodgar. Viel Glück, ich sollte nach La Vega segeln.";
			link.l1.go = "carpenter_exit";
			npchar.portman = 0;
			AddDialogExitQuestFunction("Mtraxx_WolfreekComplete");
		break;
		//------------------------------------------------------------ Исла Мона ------------------------------------
		case "IslaMona":
			sTemp = "";
			if (GetCharacterIndex("Mirabella") != -1) sTemp = ", not accounting for your woman";
            dialog.text = "Es ist schwer zu sagen, Käpt'n. Der verstorbene Wulfric hat hier nie mehr als zwei Dutzend Leute zurückgelassen. Im Moment sind wir nur zu dritt,"+sTemp+". Es gibt nicht viel, was wir tun können.";
			link.l1 = "Meinst du zu sagen, dass wenn mehr Leute hier leben würden, du diesen Ort zu einer vollwertigen Siedlung machen könntest?";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
            dialog.text = "Die Insel ist klein, daher können Sie keine Kolonie darauf errichten, aber eine Siedlung ist durchaus möglich! Sie können fischen, Vögel und Ziegen jagen, Früchte sammeln. Wir können uns selbst versorgen, aber wir werden damit nicht reich.\nAber es gibt eine Sache, die ich nicht ganz verstehe, Kap. Warum brauchen Sie das?";
			link.l1 = "Das ist mein Zuhause und mein Land, mein Volk. Was macht es aus mir, wenn ich mich nicht um sie kümmere?";
			link.l1.go = "IslaMona_2_1";
			link.l2 = "Ich möchte Geld in ein lohnendes Geschäft investieren.";
			link.l2.go = "IslaMona_2_2";
			link.l3 = "Diese kleine Insel liegt mitten in dieser Region. Es wäre klug, sie in eine vollwertige und geheime Militärbasis zu verwandeln.";
			link.l3.go = "IslaMona_2_3";
			link.l4 = "Ich mache mir Sorgen um dich, Rodgar, ihr seid alle völlig wild geworden.";
			link.l4.go = "IslaMona_2_4";
		break;
		
		case "IslaMona_2_1":
            dialog.text = "Du bist ein seltsamer Kauz. Nun, egal. Zumindest wird es etwas zu tun geben...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Defence", 2000);//защита
		break;
		
		case "IslaMona_2_2":
            dialog.text = "Du bist ein seltsamer. Na ja, egal. Wenigstens gibt es etwas zu tun...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Commerce", 1500);//торговля
		break;
		
		case "IslaMona_2_3":
            dialog.text = "Du bist ein seltsamer. Na ja, egal. Zumindest gibt es etwas zu tun...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddComplexSelfExpToScill(250, 250, 250, 250);//оружие
		break;
		
		case "IslaMona_2_4":
            dialog.text = "Du bist ein seltsamer. Nun, egal. Wenigstens gibt es etwas zu tun...";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
			AddCharacterExpToSkill(pchar, "Leadership", 1000);//авторитет
		break;
		
		case "IslaMona_3":
            dialog.text = "Zunächst müssen Sie ganz besondere Individuen finden. Solche, die überredet werden könnten, in diese Wildnis zu ziehen, um jahrelang in völliger Isolation von der Außenwelt zu leben und zu arbeiten. Das sind die besonderen Menschen, nach denen Sie suchen müssen. Hoffentlich nicht nur einer. Schließlich können Sie Ihrer Mannschaft noch nicht befehlen, hier zu leben. Kolonisten würden ihre etablierten Häuser und stabilen Jobs nicht aufgeben wollen. Und wir brauchen hier selbst keine Drifter und andere Unangepasste.\nDarüber hinaus wird das Geheimnis um diese Insel immer präsent sein. Wenn Sie jemandem davon erzählen, besteht sofort die Gefahr, dass Jäger kommen, um zu untersuchen.";
			link.l1 = "Ich verstehe, irgendwelche Vorschläge?";
			link.l1.go = "IslaMona_4";
		break;
		
		case "IslaMona_4":
            dialog.text = "Nein, Kapitän. Ich bin schon viel zu lange hier und habe den Kontakt zum zivilisierten Leben völlig verloren.";
			link.l1 = "Großartig, das ist hilfreich!";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
            dialog.text = "Ich arbeite mit Holz, nicht mit Menschen. Und das freut mich sehr, ha-ha! Übrigens, neben Menschen musst du auch einen Satz hochwertiger Schmiede- und Bauwerkzeuge hierher bringen. Sie werden nur im alten Europa hergestellt, also werden sie dich ein hübsches Sümmchen kosten. Frag die Besitzer der Schiffswerften, die größeren.";
			link.l1 = "Alles ist klar. Lassen wir zusammenfassen: Wenn ich diese Basis in etwas Größeres verwandeln will, muss ich mehr Siedler und Werkzeuge hierher zurückbringen?";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
            dialog.text = "Das ist korrekt!";
			link.l1 = "Ich werde sehen, was ich tun kann.";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "1");
			pchar.questTemp.IslaMona = "tools";
			IslaMona_SelectShipyard();
		break;
		
		case "IslaMona_8":
            dialog.text = "Jawohl, Kapitän! Erstklassiges Set, wir sind bereit, eine Kolonie zu bauen! War es teuer?";
			link.l1 = "Es hat mich ein Vermögen gekostet, ich hoffe wirklich, es hat sich gelohnt!";
			link.l1.go = "IslaMona_9_1";
			link.l2 = "Vor ein paar Jahren hätte ich gesagt, es war sehr teuer. Aber jetzt... Ich weiß es nicht einmal mehr.";
			link.l2.go = "IslaMona_9_2";
		break;
		
		case "IslaMona_9_1":
			AddCharacterExpToSkill(pchar, "Commerce", 600);
            dialog.text = "Du konntest dich nicht mit dem zufriedengeben, was du bereits hattest, oder? Auf jeden Fall, bereite dich darauf vor, dass deine Ausgaben nur noch steigen werden. Hast du das Problem mit den Siedlern gelöst?";
			link.l1 = "Nein, Rodgar. Ich habe noch nicht herausgefunden, wo ich sie finden kann. Schließlich habe ich nicht die souveränen Rechte, Siedlungen in diesen Gewässern zu gründen.";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_9_2":
			AddCharacterExpToSkill(pchar, "Leadership", 300);
            dialog.text = "Du konntest dich nicht mit dem zufrieden geben, was du bereits hattest, oder? Auf jeden Fall, sei darauf vorbereitet, dass deine Ausgaben nur noch wachsen werden. Hast du das Problem mit den Siedlern geklärt?";
			link.l1 = "Nein, Rodgar. Ich habe noch nicht herausgefunden, wo ich sie finden kann. Schließlich habe ich nicht die souveränen Rechte, Siedlungen in diesen Gewässern zu gründen.";
			link.l1.go = "IslaMona_10";
		break;
		
		case "IslaMona_10":
            dialog.text = "In diesen Gewässern, Kapitän, herrscht jeden Tag Chaos. Hören Sie auf das, was die Leute sagen, Sie könnten eine verborgene Gelegenheit sehen. Ich kümmere mich um die Werkzeuge für jetzt.";
			link.l1 = "In Ordnung, ich werde nach dieser Art von Informationen Ausschau halten.";
			link.l1.go = "IslaMona_11";
		break;
		
		case "IslaMona_11":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			AddQuestRecord("IslaMona", "3");
			RemoveItems(pchar, "islamona_toolbox", 1);
			pchar.questTemp.IslaMona = "rumours";
			AddRumor("They say some criminals have been cast out to one of the uninhabited islands! It seems they're such fierce monsters that even the executioner and the holy fathers wouldn't want to deal with them! But why do they always bring such people to us?!", 1, "all", "none", 0, (2022 - STARTGAME_YEAR) * 365, "IslaMona_TerksRumour", "none");
		break;
		
		case "IslaMona_12":
            dialog.text = "Spanier? Du machst wohl Witze, Kapitän. Ich dachte, du bringst Tagediebe aus Le Francois, nicht diese...";
			link.l1 = "";
			link.l1.go = "IslaMona_13";
		break;
		
		case "IslaMona_13":
            DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_14":
            dialog.text = "Bist du aus Europa? Hehe, das ist nicht schwer zu erkennen. Keine Sorge, du wirst dich daran gewöhnen.";
			link.l1 = "Jimenez, du wirst eine Weile in meinem Haus bleiben. Dort gibt es einen Keller, viel Platz. Rodgar, ich habe die Werkzeuge und auch die Siedler gebracht. Was kommt als nächstes?";
			link.l1.go = "IslaMona_15";
		break;
		
		case "IslaMona_15":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_20";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "IslaMona_16":
            dialog.text = "Bis morgen, Kapitän. Wir werden in einem Tag sprechen, sobald diese... Siedler sich mit ihren Schätzen eingelebt haben..";
			link.l1 = "Gut, wir machen morgen weiter.";
			link.l1.go = "IslaMona_17";
		break;
		
		case "IslaMona_17":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LAi_SetWarriorType(npchar);
			IslaMona_HimenesWait();
		break;
		
		case "IslaMona_18":
            dialog.text = "Kapitän, sprich mit dem Spanier. Er ist bereits voll und ganz in seiner Arbeit vertieft.";
			link.l1 = "Hab's verstanden, wird gemacht.";
			link.l1.go = "IslaMona_19";
			link.l2 = "Ist etwas nicht in Ordnung?";
			link.l2.go = "IslaMona_18_1";
		break;
		
		case "IslaMona_18_1":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
            dialog.text = "Kapitän, ich habe hier ein paar Jahre mit den Jungs herumgegammelt. Jetzt geht mir die geschäftige Aktivität der Spanier auf die Nerven.";
			link.l1 = "Keine Konflikte! Und ich verbiete dir und deinen Leuten auch nur in die Richtung ihrer Frauen zu schauen! Zumindest, vorerst... Wenn die Dinge heiß werden, nimm ein Skiff und geh... ein paar Tage angeln.";
			link.l1.go = "IslaMona_18_2";
		break;
		
		case "IslaMona_18_2":
            dialog.text = "Jawohl, Herr!";
			link.l1 = "Perfekt. Gut, ich werde mal sehen, was er vorhat.";
			link.l1.go = "IslaMona_19";
		break;
		
		case "IslaMona_19":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			IslaMona_SetHimenesNextDay();
		break;
		
		case "IslaMona_20":
            dialog.text = "Ich weiß schon, Kapitän. Der Spanier will, dass wir die Insel erkunden? Auf den Felsen herumspringen mit einer Karte wie eine Bande von Idioten?";
			link.l1 = "Das ist richtig, Rodgar.";
			link.l1.go = "IslaMona_21";
		break;
		
		case "IslaMona_21":
            dialog.text = "Sechshundert Dublonen und ich mach's.";
			link.l1 = "Bist du verrückt? Hat dich eine einheimische Spinne oder eine giftige Schlange gebissen? Was willst du mit einer Truhe voller Gold auf einer unbewohnten Insel machen? Vergraben?";
			link.l1.go = "IslaMona_22";
		break;
		
		case "IslaMona_22":
            dialog.text = "Los geht's, Kapitän. Eines Tages werden wir diesen Ort verlassen, und wer wird uns in der großen Welt ohne Münzen brauchen? Natürlich haben wir ein kleines Versteck, aber das ist bei weitem nicht genug. Wulfric hat seine Schulden bei mir und den Jungs für seine letzten Abenteuer nie beglichen.\nEs ist eine Sache, monatelang am Strand herumzuliegen und deine Flotte alle sechs Monate zu warten. Aber jeden Tag hart auf festem Boden zu arbeiten, wie ein verfluchter Freibeuter - das ist eine ganz andere Geschichte! Das ist ein Job, und Jobs zahlen. Du bezahlst doch deine Crew, oder nicht, Kapitän?";
			link.l1 = "Klingt vernünftig. Ich werde dir die 600 Dublonen besorgen. Du erwartest nicht etwa die Zahlung im Voraus, oder?";
			link.l1.go = "IslaMona_23";
			link.l2 = "Ich habe einen anderen Vorschlag. Sie arbeiten an Land, kratzen nicht Seepocken von Schiffen auf See. Momentan sind wir dringend auf diese Art von Arbeit angewiesen.";
			link.l2.go = "IslaMona_25";
		break;
		
		case "IslaMona_23":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddQuestRecord("IslaMona", "7");
            dialog.text = "Kapitän, ich bin bereit, sofort zu beginnen, aber meine Männer werden viel härter arbeiten, wenn sie Dublonen in ihren Händen sehen. Ich verspreche, wir werden kein einziges Stück unerforschtes Land auf dieser Insel lassen.";
			if (PCharDublonsTotal() >= 600)
			{
				link.l1 = "In Ordnung. Hier ist dein Gold. Verschwende es nur nicht sofort auf Getränke.";
				link.l1.go = "IslaMona_24";
			}
			else
			{
				link.l1 = "Gut, ich werde dir deine Dublonen bringen.";
				link.l1.go = "IslaMona_24_1";
			}
		break;
		
		case "IslaMona_24_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona = "dublon_wait";
		break;
		
		case "IslaMona_24":
			RemoveDublonsFromPCharTotal(600);
			Log_Info("You gave away 600 doubloons");
			PlaySound("interface\important_item.wav");
            dialog.text = "Ha-ha! Sie haben da einen Punkt, Kapitän! Oh, und ich habe fast vergessen. Jetzt leben hier ziemlich viele Leute, und sie brauchen etwas zu essen. Haben Sie diese Damen gesehen? Sie sind nicht an das Überleben und die Selbstversorgung gewöhnt. Sie werden keine Hilfe sein.";
			link.l1 = "Nur sag mir nicht, dass ich noch mehr Freibeuter finden muss, um dir zu helfen.";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_25":
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			pchar.questTemp.IslaMona.Nodublon = "true"; // дублоны не заплатил
			AddQuestRecord("IslaMona", "8");
            dialog.text = "Aye-aye, Kapitän! Wir sind bereit, auf dem Land zu arbeiten! Oh, und noch eine Sache, ich habe es fast vergessen. Jetzt leben hier ziemlich viele Menschen, und sie brauchen etwas zu essen. Haben Sie diese Damen gesehen? Sie sind nicht gewohnt zu überleben und sich vom Land zu ernähren. Sie werden keine Hilfe sein.";
			link.l1 = "Nur sag mir nicht, dass ich auch noch Freibeuter suchen muss, um euch zu helfen.";
			link.l1.go = "IslaMona_26";
		break;
		
		case "IslaMona_26":
            dialog.text = "Nein, warum sollten wir das tun? Wir werden die fähigsten unter ihnen für das Leben vorbereiten. Aber bis zu diesem wunderbaren Moment müssen Sie uns mit Essen versorgen. Ein paar tausend Schiffsrationen werden ausreichen. Und ein Zentner Medikamente für die Zukunft. Entladen Sie all dies von den Schiffen in unser Lager auf der Insel.";
			link.l1 = "Wird gemacht. Wie viel Zeit brauchst du für die Aufklärungsmission?";
			link.l1.go = "IslaMona_27";
		break;
		
		case "IslaMona_27":
            dialog.text = "Wir werden in zwei bis drei Tagen fertig sein, wir haben bereits einige interessante Dinge gefunden.";
			link.l1 = "Großartig!";
			link.l1.go = "IslaMona_28";
		break;
		
		case "IslaMona_28":
            dialog.text = "Sobald wir fertig sind, geh direkt zu diesem lachenden Spanier. Der Verrückte muss Schlussfolgerungen aus unserer Arbeit ziehen.";
			link.l1 = "Ich sehe, ihr seid schon fast Freunde. Ich werde ihn dann in drei Tagen besuchen. Nun, auf die Arbeit. Viel Glück uns allen!";
			link.l1.go = "IslaMona_29";
		break;
		
		case "IslaMona_29":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.quest.stalk = "true";
			AddQuestRecord("IslaMona", "9");
			pchar.questTemp.IslaMona = "storage";
			SetFunctionTimerCondition("IslaMona_StalkFin", 0, 0, 3, false);
		break;
		
		case "IslaMona_30":
            dialog.text = "Wow! Danke, Kapitän. Jetzt haben wir Zeit, die Damen auf dieses verrückte Leben in der Wildnis vorzubereiten.";
			link.l1 = "Sei nur vorsichtig, sie nicht zu Piraten zu machen! Danke, Rodgar";
			link.l1.go = "IslaMona_31";
		break;
		
		case "IslaMona_31":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			pchar.questTemp.IslaMona.Food = "true";
			AddQuestRecord("IslaMona", "10");
			IslaMona_RemoveFood();
		break;
		
		case "IslaMona_32":
            dialog.text = "Kapitän! Ich muss sagen, ich habe angefangen, mich hier eher unwohl zu fühlen.";
			link.l1 = "Warum ist das so, Rodgar? Vermisst du den Charme von Armut und Ruin?";
			link.l1.go = "IslaMona_33";
		break;
		
		case "IslaMona_33":
            dialog.text = "Man könnte das so sagen. Jetzt erreicht die Zivilisation sogar hierher. Und Leute wie ich haben darin keinen Platz.";
			link.l1 = "Kauf dir ein Jabot und einen Stock. Du wirst perfekt passen.";
			link.l1.go = "IslaMona_34";
		break;
		
		case "IslaMona_34":
            dialog.text = "Eher, lass uns zu deinem Spanier gehen und die Ergebnisse der Aufklärung besprechen. Ich habe noch eine verrückte Idee...";
			link.l1 = "Ich habe gerade mit ihm gesprochen! Gut, lass uns gehen, Rodgar.";
			link.l1.go = "IslaMona_37";
			link.l2 = "Wie gefällt es Ihnen, mit ihm zu arbeiten?";
			link.l2.go = "IslaMona_35";
		break;
		
		case "IslaMona_35":
            dialog.text = "Hochgebildete und fleißige Leute! Und Jimenez ist wirklich ein Meister. In alten Zeiten hätte man für solche Leute eine gute Menge Gold bekommen können. Und ihre Mädchen sind auch schön...";
			link.l1 = "Ich will davon nichts hören, Rodgar! Lass uns zu unserem Meister gehen";
			link.l1.go = "IslaMona_36_1";
			link.l2 = "Wenn sie die Arbeit nicht bewältigen können, verkaufen wir sie. Aber behalte die Mädchen, ha-ha! Lass uns zum Meister gehen..";
			link.l2.go = "IslaMona_36_2";
		break;
		
		case "IslaMona_36_1":
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
            dialog.text = "Ernsthaft, Kapitän? Ich habe nur gescherzt, lass uns gehen...";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_36_2":
			ChangeCharacterComplexReputation(pchar, "nobility", -6);
            dialog.text = "Ich wusste, dass du mich unterstützen würdest, Kapitän! Auf geht's...";
			link.l1 = "";
			link.l1.go = "IslaMona_37";
		break;
		
		case "IslaMona_37":
            DialogExit();
			DoQuestReloadToLocation("IslaMona_TwoFloorHouse", "goto", "goto5", "IslaMona_HouseDialog");
		break;
		
		case "IslaMona_38":
            dialog.text = "Er lacht nicht, Käpt'n...";
			link.l1 = "";
			link.l1.go = "IslaMona_39";
		break;
		
		case "IslaMona_39":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_48";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_40":
            dialog.text = "Auch das, Käpt'n. Wir werden es später besprechen...";
			link.l1 = "";
			link.l1.go = "IslaMona_41";
		break;
		
		case "IslaMona_41":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_52";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_42":
            dialog.text = "Der Herr hat einen Punkt, Kapitän. Keiner von uns wird sich im Dschungel den Rücken brechen. Das Geschäft mag schmutzig sein, aber auf andere Weise wirst du aus diesem Ort nichts mehr als ein Piratennest machen.";
			link.l1 = "";
			link.l1.go = "IslaMona_43";
		break;
		
		case "IslaMona_43":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_58";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_44":
            dialog.text = "Captain, when you build the factory, the slaves will need protection. My guys will take care of that. One of them even shoots like Thor with lightning. Nothing motivates work like a hunting scope. We already have one gun; now we need a second. Any musket will do.";
			link.l1 = "";
			link.l1.go = "IslaMona_45";
		break;
		
		case "IslaMona_45":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_60";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_46":
            dialog.text = "Und meine Leute werden die gleiche Menge Gold und ein weiteres Dutzend Flaschen guten Rums brauchen.";
			link.l1 = "Wie viel Holz können Sie in jeder Charge liefern? Und warum brauchen Sie Gold?";
			link.l1.go = "IslaMona_47";
		break;
		
		case "IslaMona_47":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_62";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_48":
            dialog.text = "Nun, zuallererst ist das Leben ohne Freizeit bedeutungslos, und bald werden sogar die frommen, hehe, Katholiken anfangen, die Wände hochzuklettern. Und zweitens, wenn es eine Taverne auf der Insel gibt, kannst du einen Teil der Crew hier in Bereitschaft lassen. Weißt du, die Leute davon zu überzeugen, ein ganzes Jahr lang kostenlos wie Wilde in Hütten am Strand zu leben, ist ziemlich schwierig. Aber wenn es eine Siedlung mit einer Taverne, warmem Essen, Musik und Unterhaltung in der Nähe gibt... Was braucht ein Seemann sonst noch an Landgang?";
			link.l1 = "Huren?";
			link.l1.go = "IslaMona_49";
			link.l2 = "Getränke?";
			link.l2.go = "IslaMona_49";
		break;
		
		case "IslaMona_49":
            dialog.text = "Du hast recht, aber lass uns die Probleme eins nach dem anderen lösen. Zuerst werden wir dein Haus wiederaufbauen...";
			link.l1 = "...";
			link.l1.go = "IslaMona_50";
		break;
		
		case "IslaMona_50":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_65";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_51":
            dialog.text = "Er hat nicht mal daran gedacht, Käpt'n.";
			link.l1 = "Danke dir, Rodgar. Ich verstehe, dass ich jetzt in dieser kleinen Bucht mehr Schiffe bedienen kann, richtig?";
			link.l1.go = "IslaMona_52";
		break;
		
		case "IslaMona_52":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_harbour_4";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_53":
            dialog.text = "Grüße, Kapitän! Sind Sie gekommen, um die Arbeit zu besprechen?";
			link.l1 = "Nein, überhaupt nicht. Mir hat nur dein nördliches Antlitz gefehlt.";
			link.l1.go = "IslaMona_54";
		break;
		
		case "IslaMona_54":
            dialog.text = "Sollen wir gehen? Ich zeige Ihnen Ihre Fabrik.";
			link.l1 = "Führe den Weg.";
			link.l1.go = "IslaMona_55";
		break;
		
		case "IslaMona_55":
            DialogExit();
			IslaMona_PlantationGo();
		break;
		
		case "IslaMona_56":
            dialog.text = "H-hicks! Kap, wir feiern!";
			link.l1 = "Rodgar! Rodrigo! Verdammt!";
			link.l1.go = "IslaMona_57";
		break;
		
		case "IslaMona_57":
            dialog.text = "Was ist los, K-K-Kapitän? Gefällt Ihnen die Farbe der Wände nicht?";
			link.l1 = "Erst jetzt habe ich bemerkt, dass ihr beide den gleichen Namen habt! Ha-ha-ha! Ein Spanier und ein Pirat, mit dem gleichen Namen, bauten eine Taverne auf einer verlassenen Insel und trinken zusammen, als ob die indischen Götter jeden verschlingen und die Welt bis zum Sonnenaufgang beenden werden! Ha-ha! Ich bin bei euch!";
			link.l1.go = "IslaMona_58";
		break;
		
		case "IslaMona_58":
            dialog.text = "Ha-ha-ha! So wahr! Prost!";
			link.l1 = "Prost!";
			link.l1.go = "IslaMona_59";
		break;
		
		case "IslaMona_59":
            DialogExit();
			npchar.dialog.currentnode = "IslaMona_60";
			IslaMona_ReloadTavern();
		break;
		
		case "IslaMona_60":
            dialog.text = "Möchten Sie einen Drink, Kapitän?";
			link.l1 = "Bist du dabei, ein Tavernenwirt zu werden, Rodgar?";
			link.l1.go = "IslaMona_61";
		break;
		
		case "IslaMona_61":
            dialog.text = "Vorübergehend! Die Spanier schätzen es besonders, wenn ein Pirat die Bar bedient - das ist die wahre Exotik und Abenteuer für sie. Aber insgesamt ist es hier schön. Wenn du dich entscheidest, einen Teil deiner Crew in Reserve in dieser Siedlung zu lassen, sag mir Bescheid - ich werde es arrangieren.";
			link.l1 = "Wo werden sie jedoch leben?";
			link.l1.go = "IslaMona_62";
		break;
		
		case "IslaMona_62":
            dialog.text = "Einfach - wir bauen einige Hütten am Strand. Auf diese Weise werden sie von der Taverne zum Ufer laufen. Nur eine Erinnerung, diese Insel wird nicht mehr als dreihundert Menschen aufnehmen können, also behalten Sie das für die Zukunft im Kopf. Manchmal werden wir Sie bitten, Rum und Wein zu bringen, daher wäre es großartig, wenn Sie, Kapitän, die Waren im Voraus im Lagerhaus lagern könnten.";
			link.l1 = "Ich werde das in Erinnerung behalten. Nun denn, Kamerad. Unterhalte die Spanier und mache eine Pause. Bitte trinke nur nicht, bis das ganze Dorf niederbrennt - ich könnte diesen Anblick nicht ertragen!";
			link.l1.go = "IslaMona_63";
		break;
		
		case "IslaMona_63":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload1", false);
			//LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload3", false);
			npchar.crew = "true"; // можно оставлять матросов
			npchar.crew.qty = 0;
			pchar.questTemp.IslaMona.Tavern = "done"; // флаг - таверна построена и сдана
			// belamour обнулим матросов-->
			ref rTown = GetColonyByIndex(FindColony(loadedLocation.fastreload));
			rTown.Ship.crew.quantity = 0;
			rTown.Ship.crew.morale = 0;
			rTown.Ship.Crew.Exp.Sailors   = 0;
			rTown.Ship.Crew.Exp.Cannoners = 0;
			rTown.Ship.Crew.Exp.Soldiers  = 0;
			ChangeCrewExp(rTown, "Sailors", 0);  // приведение к 1-100
			ChangeCrewExp(rTown, "Cannoners", 0);
			ChangeCrewExp(rTown, "Soldiers", 0);
			
		break;
		
		case "IslaMona_64":
            dialog.text = "Kapitän! Ich bin verdammt froh, Sie zu sehen! Dank Freyja, Sie kamen gerade rechtzeitig!";
			link.l1 = "Aye, wir haben uns wieder in ein feines Durcheinander gebracht. Hola, Rodrigo!";
			link.l1.go = "IslaMona_65";
		break;
		
		case "IslaMona_65":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_13";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_66":
            dialog.text = "Keine Verluste. Die überlebenden Spanier erreichten uns zuerst, berichteten, dass es möglich ist, weitere Gäste zu treffen, und wir konnten fast alle Vorräte und Ausrüstungen aus dem Gebiet zur Siedlung bringen. Die Situation mit den Sklaven hat natürlich nicht sehr gut geklappt.";
			link.l1 = "";
			link.l1.go = "IslaMona_67";
		break;
		
		case "IslaMona_67":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_16";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_68":
            dialog.text = "Was ist, wenn sie uns zu einem offenen Angriff herauszerren?";
			link.l1 = "Dann arbeiten wir ohne Gewehre. Wie auf einer Parade marschieren wir gemeinsam zu den Toren und schlagen sie dann einfach von hinten. Du hältst die Tore und leistest Unterstützung. Das war's, viel Glück für uns!";
			link.l1.go = "IslaMona_69";
		break;
		
		case "IslaMona_69":
            DialogExit();
			AddQuestRecord("IslaMona", "21");
			pchar.quest.islamona_def_jungle1.win_condition.l1 = "locator";
			pchar.quest.islamona_def_jungle1.win_condition.l1.location = "IslaMona_jungle_01";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator_group = "encdetector";
			pchar.quest.islamona_def_jungle1.win_condition.l1.locator = "enc04";
			pchar.quest.islamona_def_jungle1.function = "IslaMona_DefSoldiersInJungle"; // встреча с французами
			LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_jungle_01")], true);//запретить драться
		break;
		
		case "IslaMona_70":
            dialog.text = "Hurra, Kapitän!";
			link.l1 = "Einverstanden! Das war so ein Knall, ich hatte das Gefühl, mich selbst hinlegen zu müssen. Leute, was habt ihr da reingeladen?";
			link.l1.go = "IslaMona_71";
		break;
		
		case "IslaMona_71":
            dialog.text = "Doppelte Ladung, Kapitän. Damit eine Explosion sie davon abhält, weiter zu kämpfen!";
			link.l1 = "Hattest du keine Angst, dass die Kanone bei so sanfter Behandlung explodieren würde?";
			link.l1.go = "IslaMona_72";
		break;
		
		case "IslaMona_72":
            dialog.text = "Ich habe ein besonderes Talisman von Wulfric übrig. Eine Erinnerung an unser Heimatland Dänemark. Sollen wir alle in die Taverne gehen, Kapitän? Wir sind alle müde nach heute.";
			link.l1 = "Ja, das wäre großartig. Lass uns Karten spielen - wir setzen auf deinen wundersamen Talisman.";
			link.l1.go = "IslaMona_73";
		break;
		
		case "IslaMona_73":
            dialog.text = "Ha-ha, nach einer solch göttlichen Vorstellung heute, Kapitän, könnte ich diese Option sogar in Betracht ziehen!";
			link.l1 = "";
			link.l1.go = "IslaMona_74";
		break;
		
		case "IslaMona_74":
            DialogExit();
			sld = characterFromId("IM_fraofficer");
			sld.dialog.currentnode = "FraOfficer_18";
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_75":
            dialog.text = "Kapitän, haben Sie das gehört? Ich habe noch immer ein Klingeln in meinen Ohren. Wessen klägliche Stimme ist das?";
			link.l1 = "Das, Rodgar, ist ein lebendes Problem. Bring ihn zur Fabrik, leg ihm eine Kette an und warte auf weitere Anweisungen.";
			link.l1.go = "IslaMona_76";
		break;
		
		case "IslaMona_76":
            dialog.text = "Aye-aye, Kapitän!";
			link.l1 = "";
			link.l1.go = "IslaMona_77";
		break;
		
		case "IslaMona_77":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			sld = characterFromId("IM_fraofficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			for (i=1; i<=5; i++) 
			{
				sld = characterFromId("IM_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			for(i=4; i<=7; i++)
			{
				sld = characterFromId("IM_fra_sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
			}
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_78":
            dialog.text = "Kapitän, sind Sie gekommen, um die Angelegenheit mit dem Gefangenen zu klären? Ich bin es leid, hier Wache zu stehen.";
			link.l1 = "Wir müssen ihn töten. Das Risiko ist zu groß, wir haben keine andere Wahl. Ansonsten sollte ich mein Gesicht besser nicht in französischen Kolonien zeigen.";
			link.l1.go = "IslaMona_79";
			link.l2 = "Ich kann ihn nicht gehen lassen, sonst sollte ich mein Gesicht besser nicht in den französischen Kolonien zeigen. Legt ihn in Ketten und lasst ihn in der Fabrik arbeiten. Das ist besser als ihn zu töten.";
			link.l2.go = "IslaMona_80";
		break;
		
		case "IslaMona_79":
            dialog.text = "Hab's! Lassen Sie uns es schnell erledigen. Mach weiter, Kapitän. Bis morgen.";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
		break;
		
		case "IslaMona_80":
            dialog.text = "Wow. Du bist ein echtes böses Genie. Ich möchte nicht dein Feind sein. Nun, wir müssen erst einige erklärende Arbeiten mit ihm durchführen. Geh voran, Kapitän. Bis morgen.";
			link.l1 = "";
			link.l1.go = "IslaMona_81";
			pchar.questTemp.IslaMona.Fraprisoner = "true";
		break;
		
		case "IslaMona_81":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "IslaMona_DefFraPrisonerFin", 10.0); /// идёт внутрь фактории - УСТАНОВИТЬ ЛОКАТОР
		break;
		
		case "IslaMona_82":
            dialog.text = "Was für ein Gemetzel! Schade, dass wir nicht aus der Kanone schießen konnten, aber sie sind direkt in Ihren Hinterhalt gelaufen - es war schön zuzusehen!";
			link.l1 = "Ja, wir haben viel Blut auf diesem Land vergossen. Aber anscheinend gibt es keinen anderen Weg, ein Zuhause in dieser Welt zu bauen.";
			link.l1.go = "IslaMona_83";
		break;
		
		case "IslaMona_83":
            dialog.text = "Machen Sie sich nicht zu viele Gedanken, Kapitän. Das Schicksal selbst hat sie nach Isla Mona gebracht. Und lassen Sie mich Ihnen sagen, das Schicksal kann ziemlich die Hündin sein!";
			link.l1 = "Schicksal oder die Insel?";
			link.l1.go = "IslaMona_84";
		break;
		
		case "IslaMona_84":
            dialog.text = "Beide spielten ihre Rolle.";
			link.l1 = "Haha! Und beide sind schön! Also gut, tapferer Wikinger. Sammle die Trophäen und entferne diese Körper. Begrabe sie mit Würde. Sie sind schließlich unsere eigenen...";
			link.l1.go = "IslaMona_85";
		break;
		
		case "IslaMona_85":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_20a";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "IslaMona_86":
            dialog.text = "Ja, Kapitän. Das stimmt! Rodrigo hat es so schön gesagt, dass es mir eine Träne ins Auge getrieben hat. Es ist klar, warum die heiligen Väter seinen Hintern auf einen Pfahl stecken wollen!";
			link.l1 = "";
			link.l1.go = "IslaMona_87";
			locCameraFromToPos(1.36, 1.32, 0.31, true, 3.44, 0.20, -0.50);
		break;
		
		case "IslaMona_87":
            DialogExit();
			if (GetCharacterIndex("Mirabella") != -1)
			{
				sld = characterFromId("Mirabella");
				sld.dialog.currentnode = "mirabelle_46";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
					{
						sld = characterFromId("Helena");
						sld.dialog.currentnode = "IslaMona_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
					else
					{
						sld = characterFromId("Himenes_companion_1");
						sld.dialog.currentnode = "island_man_2";
						LAi_SetActorType(sld);
						LAi_ActorDialogDelay(sld, pchar, "", 0.0);
					}
				}
			}
		break;
		
		case "IslaMona_88":
            dialog.text = "Rodrigo, und hier bin ich direkt in unserem Prälaten im Boudoir gestoßen... Und lass mich dir sagen, es ist das beste Etablissement in Santiago!";
			link.l1 = "Der beste Ort, wenn Sie auch Prälaten mögen.";
			link.l1.go = "IslaMona_89";
		break
		
		case "IslaMona_89":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_90":
            dialog.text = "Ja, habe diesen Schurken und Häretiker Rodrigo tatsächlich in einen echten Piraten verwandelt.";
			link.l1 = "Nebenbei, kläre mich auf, Rodgar. Warum gibt es so wenige spanische Piraten?";
			link.l1.go = "IslaMona_91";
		break;
		
		case "IslaMona_91":
            dialog.text = "Wieso so wenige? Ah, du meinst Piratenkapitäne? Nun, davon gibt es viele, sie arbeiten hauptsächlich unter der Casa de Contratación in Sevilla. Es ist wie militärischer Nachrichtendienst, aber aus irgendeinem Grund nennen sie es Handelshaus...";
			link.l1 = "";
			link.l1.go = "IslaMona_92";
		break;
		
		case "IslaMona_92":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_77";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_93":
            dialog.text = "Ja, warum nicht ihnen eine Nachricht schicken und sie einladen. Nun, sie haben alle Patente und sind auch idealistisch. Sie berauben normalerweise nicht ihresgleichen, nur wenn der Überfall nicht erfolgreich war, ha-ha! Sie kommen nur nach Puerto Principe und stoßen ständig mit Pastor zusammen.\nKürzlich hat sich einer hervorgetan... Diego de Montoya. Gerade als ich das letzte Mal mit Wulfric auf Kampagne ging, hörte ich viel von seinen Abenteuern. Du, Kapitän, hast etwas mit ihm gemeinsam. Und gleichzeitig seid ihr sehr unterschiedlich... Wie auch immer, worüber rede ich? Lassen Sie uns noch eine Runde trinken und Karten spielen.";
			link.l1 = "Du hast kein Geld. Du spielst nicht etwa mit Dublonen, oder?";
			link.l1.go = "IslaMona_94";
		break;
		
		case "IslaMona_94":
            dialog.text = "Wir setzen jeweils einen Peso. Sollen wir bis zwanzig spielen? Hymenes, bist du dabei?";
			link.l1 = "";
			link.l1.go = "IslaMona_95";
		break;
		
		case "IslaMona_95":
            DialogExit();
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_79";
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_96":
            dialog.text = "Lass uns spielen, Käpt'n?";
			if (sti(pchar.money) >= 20)
			{
				link.l1 = "Startet es!";
				link.l1.go = "IslaMona_97";
			}
			link.l2 = "Ich passe auch, Rodgar. Pesos hin oder her, Leute verlieren so Schiffe. Mit Inseln. Du amüsierst dich hier, und ich schau mich noch ein bisschen um.";
			link.l2.go = "IslaMona_98";
		break;
		
		case "IslaMona_97": // игра в карты
            DialogExit();
			pchar.questTemp.GoldenGirl.Game.IslaMona = "true"; // атрибут квестовой игры
			npchar.money = 20;
			pchar.questTemp.IslaMona.Money = sti(pchar.money);
			pchar.money = 20;
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 1; // ставка
			LaunchCardsGame();
		break;
		
		case "IslaMona_98": // выход из-за стола
            DialogExit();
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_99":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Pass! Nun, nun, ich spiele nicht mehr mit dir! Ich bin sicher, du hast betrogen, Kapitän! Und einen Betrüger einfach so gehen zu lassen, wäre nicht richtig!";
				link.l1 = "Ich höre dir zu, Rodgar.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "Ich habe gewonnen, Käpt'n. Aber ich kann dich nicht einfach so mit leeren Händen gehen lassen, haha!";
					link.l1 = "In Ordnung, du Schurke. Das wird eine Lektion für mich sein...";
				}
				else
				{
					dialog.text = "Ich habe gewonnen, Käpt'n. Aber ich kann dich nicht einfach so mit leeren Händen gehen lassen, haha!";
					link.l1 = "Also gut, du Schurke. Es wird eine Lektion für mich sein...";
				}
			}
			link.l1.go = "IslaMona_100";
		break;
		
		case "IslaMona_100":
            dialog.text = "Ach, komm schon! Du hast mir und meiner Mannschaft eine Chance auf ein richtiges Leben fernab von beengten Quartieren, abgestandenem Wasser und dem Risiko, einen Splitter in... den Schädel zu bekommen, gegeben. Hier. Dieser Anhänger wurde von Wulfric aus dem fernen Dänemark gebracht und dann an mich weitergegeben, damit ich... heh, nicht allzu oft in seinen Keller hinabsteigen muss. Ich brauche ihn nicht mehr, aber du - oh, du wirst ihn ganz nützlich finden.";
			link.l1 = "Danke dir, Rodgar. Tatsächlich, ein nützlicher Gegenstand. Und auch schön...";
			link.l1.go = "IslaMona_101_1";
			link.l2 = "Behalte es, Rodgar. Ohne dich würde dieser Ort nicht existieren. Lass es eine Erinnerung an deine Heimat sein.";
			link.l2.go = "IslaMona_101_2";
		break;
		
		case "IslaMona_101_1":
			GiveItem2Character(pchar, "talisman3");
			Log_Info("You received 'Thor's Hammer'");
			PlaySound("interface\important_item.wav");
            dialog.text = "Ich freue mich, dass es Ihnen gefallen hat, Kapitän. Noch eine Runde?";
			link.l1 = "Ihr Leute entspannt euch hier, und ich schaue mich noch etwas um.";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_101_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			AddCharacterExpToSkill(pchar, "Fortune", 2000);
            dialog.text = "Wie du wünschst! Dann gebe ich eine Dame Glück, haha! Noch eine Runde?";
			link.l1 = "Ihr Leute entspannt euch hier, und ich schaue mich noch etwas um.";
			link.l1.go = "IslaMona_102";
		break;
		
		case "IslaMona_102":
            DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			DeleteAttribute(pchar, "GenQuest.Cards");
			pchar.money = sti(pchar.money)+sti(pchar.questTemp.IslaMona.Money);
			DeleteAttribute(pchar, "questTemp.IslaMona.Money");
			IslaMona_ChurchTavernStandUp();
		break;
		
		case "IslaMona_103":
            dialog.text = "Nun, Kapitän. Sie haben die Angelegenheiten mit dem Spanier geklärt, wir haben unser Fest gefeiert und der Kopfschmerz hat etwas nachgelassen. Das Leben ist gut!";
			link.l1 = "Was hast du vor, Rodgar?";
			link.l1.go = "IslaMona_104";
		break;
		
		case "IslaMona_104":
			sTemp = "";
            if (CheckAttribute(pchar, "questTemp.IslaMona.MiraRodgar")) sTemp = "I'll get along with the woman. ";
			dialog.text = "Ich werde wie gewohnt auf die Jagd gehen, ein Auge auf meine... unsere Taverne werfen, die Sklaven in der Fabrik treten. Perfekter Ruhestand.";
			link.l1 = "Du bist nur fünf Jahre älter als ich, Rodgar. Und du, Rodrigo? Wie geht's?";
			link.l1.go = "IslaMona_105";
		break;
		
		case "IslaMona_105":
            DialogExit();
			sld = characterFromId("Himenes");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		// <-- Исла Мона
		
		case "repair":
			if (CheckSelfRepairConditions())
			{
				dialog.text = "Aber natürlich, Kapitän! Alles, was wir brauchen, sind Planken und Segeltuch. Geh zu deinem Landeplatz und befehle deiner Mannschaft, die Materialien vorzubereiten.";
				link.l1 = "Auf meinem Weg. Mach es schnell.";
				link.l1.go = "repair_1";
			}
			else
			{
				dialog.text = "Sicher, Kapitän, aber wie ich es sehe, braucht Ihr Schiff jetzt keine Reparatur.";
				link.l1 = "Einfach gefragt...";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		case "repair_1":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			chrDisableReloadToLocation = true;
			DoQuestReloadToLocation(Pchar.location.from_sea, "reload", "sea", "Mtraxx_WolfreekRepairShore");
		break;
		
		case "shipstock_info":
			npchar.portman.info = "true";
            dialog.text = "Es ist möglich, Kapitän. Ein paar Einschränkungen allerdings: Es gibt nur zwei Orte auf dieser Insel, die dafür geeignet sind. Außerdem kannst du hier niemanden außer einem einzigen Offizier für jedes Schiff zurücklassen. Wir haben einfach nicht genug Ressourcen, um hier Mannschaften zu versorgen. Noch nicht. Schließlich ist kein Platz für erstklassige Schiffe.";
			link.l1 = "Habe es verstanden. Ich bin bereit, hier ein Schiff zu lassen.";
			link.l1.go = "shipstock";
			link.l2 = "Sehr gut, ich werde sie vorbereiten.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "shipstock":
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(npchar.portman) == 3)
				{
					dialog.text = "Kapitän, es liegen bereits drei Ihrer Schiffe am Dock. Es ist kein Platz mehr verfügbar.";
					link.l1 = "Du hast recht, ich habe es vergessen.";
					link.l1.go = "carpenter_exit";
					break;
				}
				else
				{
					if(CheckAttribute(npchar,"FstClassInHarbour") && sti(npchar.portman) > 0)
					{
						dialog.text = "Kapitän, es liegt bereits ein Erstklassenschiff am Dock. Es ist kein Platz mehr verfügbar.";
						link.l1 = "Du hast recht, ich habe es vergessen.";
						link.l1.go = "carpenter_exit";
						break;
					}
				}
			}
			else
			{
				if (sti(npchar.portman) == 2)
				{
					dialog.text = "Kapitän, zwei Ihrer Schiffe liegen bereits am Dock vor Anker. Es ist kein Platz mehr verfügbar.";
					link.l1 = "Du hast recht, ich habe es vergessen.";
					link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (GetCompanionQuantity(pchar) < 2)
			{
				dialog.text = "Kapitän, Sie haben nur ein Schiff.";
				link.l1 = "Hm... Ich sollte weniger trinken...";
				link.l1.go = "carpenter_exit";
				break;
			}
            dialog.text = "Welches Schiff möchten Sie hier lassen?";
			for(i=1; i<COMPANION_MAX; i++)
			{
				int cn = GetCompanionIndex(PChar, i);
				if( cn > 0 )
				{
					ref chref = GetCharacter(cn);
					if (!GetRemovable(chref)) continue;

					attrL = "l"+i;
					Link.(attrL) = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "ShipStockMan_" + i;
				}
			}
			Link.l9 = "Warte, ich habe meine Meinung geändert.";
			Link.l9.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_1":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
			dialog.text = "Lass uns mal sehen...";
			Link.l1 = "Sehr gut.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Warte, ich habe meine Meinung geändert.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_2":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
			dialog.text = "Lass uns mal sehen...";
			Link.l1 = "Sehr gut.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Warte, ich habe meine Meinung geändert.";
			Link.l2.go = "carpenter_exit";
		break;

		case "ShipStockMan_3":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
			dialog.text = "Mal sehen...";
			Link.l1 = "Sehr gut.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Warte, ich habe meine Meinung geändert.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockMan_4":
            NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
			dialog.text = "Lass uns mal sehen...";
			Link.l1 = "Sehr gut.";
			Link.l1.go = "ShipStock_2";
			Link.l2 = "Warte, ich habe meine Meinung geändert.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_2":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			if(CheckAttribute(pchar,"questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
			{
				if(sti(RealShips[sti(chref.Ship.Type)].Class) < 2 && sti(npchar.portman) > 0)
				{
					dialog.text = "Kapitän, ich habe bereits erwähnt, dass unser Ankerplatz nur ein erstklassiges Schiff aufnehmen kann. Es ist zu groß für den verfügbaren Platz.";
					Link.l1 = "Du hast recht, ich habe vergessen.";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			else
			{
				if (sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
				{
					dialog.text = "Kapitän, erstklassige Schiffe sind zu groß für unsere Küsten. Das habe ich Ihnen schon gesagt.";
					Link.l1 = "Du hast recht, ich habe es vergessen.";
					Link.l1.go = "carpenter_exit";
					break;
				}
			}
			if (sti(chref.Ship.Crew.Quantity) > 0)
			{
				dialog.text = "Kapitän, nehmen Sie die gesamte Besatzung mit auf Ihr Flaggschiff, außer einem Offizier.";
				Link.l1 = "Ach, richtig! Das werde ich tun!";
				Link.l1.go = "carpenter_exit";
				break;
			}
			dialog.Text = "Also, wir sollen hier bleiben, a"+XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName+"Acc")+" benannt '"+chref.Ship.Name+"'. Stimmt's?";
			Link.l1 = "Richtig.";
			Link.l1.go = "ShipStock_3";
			Link.l2 = "Warte, ich habe meine Meinung geändert.";
			Link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStock_3":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
            chref.ShipInStockMan = NPChar.id;
			chref.ShipInStockMan.MoneyForShip = 0;
            chref.ShipInStockMan.AltDate = GetQuestBookDataDigit();
            SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date");
            RemoveCharacterCompanion(pchar, chref);
            chref.location = "";
            chref.location.group = "";
            chref.location.locator = "";
			if(sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
			{
				npchar.FstClassInHarbour = 1;
			}
            npchar.portman = sti(npchar.portman)+1;
            pchar.ShipInStock = sti(pchar.ShipInStock)+1;
			dialog.text = "Sehr gut, wir werden sie zu einem sicheren Hafen bringen.";
			Link.l1 = "Ausgezeichnet!";
			Link.l1.go = "carpenter_exit";
		break;
		
		case "shipstockreturn":
            if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				dialog.text = "Welches Schiff werden Sie nehmen, Kapitän?";
				cn = 1;
				for (i=1; i<MAX_CHARACTERS; i++)
				{
					makeref(chref, Characters[i]);
					if (CheckAttribute(chref, "ShipInStockMan"))
					{
						if (chref.ShipInStockMan == NPChar.id)
						{
							attrL = "l"+cn;
							Link.(attrL)    = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
							Link.(attrL).go = "ShipStockManBack_" + i;
							cn++;
						}
					}
				}
				link.l9 = "Warte, ich habe meine Meinung geändert.";
				link.l9.go = "carpenter_exit";
			}
			else
			{
				dialog.text = "Kapitän, Sie haben keinen Platz in Ihrer Staffel für ein weiteres Schiff.";
				link.l1 = "Hm. Es scheint, du hast Recht.";
				link.l1.go = "carpenter_exit";
			}
		break;
		
		 case "ShipStockManBack":
            chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			dialog.Text = "Nimmst du sie mit?";
			link.l1 = "Ja.";
			link.l1.go = "ShipStockManBack2";
			link.l2 = "Warte, ich habe meine Meinung geändert.";
			link.l2.go = "carpenter_exit";
		break;
		
		case "ShipStockManBack2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			if(CheckAttribute(npchar,"FstClassInHarbour")) DeleteAttribute(npchar,"FstClassInHarbour");
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			DeleteAttribute(chref, "ShipInStockMan");
			SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
			npchar.portman = sti(npchar.portman)-1;
            pchar.ShipInStock = sti(pchar.ShipInStock)-1;
		break;
		
		case "storadge":
            dialog.text = "Hier? Nein. Aber Wulfric hat nicht weit von hier eine riesige Scheune gebaut. Ein solides Gebäude, gut bedeckt mit Palmenblättern und geteertem Segeltuch. Es hat ein Schloss und einen Raum für eine Ladung, die ausreicht, um ein Dutzend Handelsschiffe zu füllen\nEs ist jetzt leer, aber ich habe einen Schlüssel, wenn du es untersuchen willst. Sollen wir?";
			link.l1 = "Sicher! Übrigens: was ist mit den Ratten auf dieser Insel? Werden sie meine Waren in der Scheune verderben?";
			link.l1.go = "storadge_1";
		break;
		
		case "storadge_1":
            dialog.text = "Wolf hatte es auch abgedeckt: Er brachte zwei Katzen hierher vom Festland. Er hat jedoch die Männchen vergessen, so dass diese verrückten pelzigen Weiber jedes Mal laute Geräusche machen, wenn ihre Saison kommt. Aber sie jagen Mäuse und Ratten ziemlich gut. Mach dir keine Sorgen, Kapitän. Ihre Waren werden vor Schädlingen und Winden sicher sein.";
			link.l1 = "Großartig! Ich werde es gut gebrauchen. Behalte deinen Schlüssel für dich und zeige mir dieses Lagerhaus.";
			link.l1.go = "storadge_2";
		break;
		
		case "storadge_2":
			DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			npchar.city = "islamona";
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			npchar.MoneyForStorage = 0;
			npchar.storadge = true;
			LaunchStorage(29);
		break;
		
		case "storadge_3":
            dialog.text = "Folgen Sie mir, Kapitän.";
			link.l1 = "...";
			link.l1.go = "storadge_4";
		break;
		
		case "storadge_4":
            DialogExit();
			npchar.dialog.currentnode = "carpenter_17";
			LaunchStorage(29);
		break;
		
		// Мирабель
		case "mirabelle":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "Ach...";
			link.l1 = "Nun, eine Mädchen ... Was machst du hier?";
			link.l1.go = "mirabelle_1";
		break;
		
		case "mirabelle_1":
			PlaySound("Voice\English\Girl_Q.wav");
            dialog.text = "Oh...";
			link.l1 = "...";
			link.l1.go = "mirabelle_2";
		break;
		
		case "mirabelle_2":
            DialogExit();
			npchar.dialog.currentnode = "mirabelle_3";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_74";
			ChangeCharacterAddressGroup(sld, "LaVega_TwoFloorHouse", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;
		
		case "mirabelle_3":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_01.wav");
            dialog.text = "Herr! Herr "+pchar.name+" töte mich bitte nicht! Ich flehe dich an! Ich werde Tyrex nichts sagen! Ich hasse dieses Biest! Ich flehe dich an, por favor!";
			link.l1 = "...";
			link.l1.go = "mirabelle_4";
		break;
		
		case "mirabelle_4":
			DialogExit();
            npchar.dialog.currentnode = "mirabelle_5";
			npchar.greeting = "mirabella_goodgirl";
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_80";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "mirabelle_5":
            dialog.text = "";
			link.l1 = "He, Mädel! Hast du das gehört? Du gehst mit mir oder dieser harte Bastard wird dich töten.";
			link.l1.go = "mirabelle_6";
		break;
		
		case "mirabelle_6":
            dialog.text = "Ich werde mit Ihnen gehen, Senor, wohin auch immer Sie mich bringen!";
			link.l1 = "Gut dann. Halte deinen Mund, oder ich werde dich töten, wenn du anfängst zu schreien oder nach Tyrex zu rufen. Wie heißt du?";
			link.l1.go = "mirabelle_7";
		break;
		
		case "mirabelle_7":
            dialog.text = "Mirabelle...";
			link.l1 = "Verhalte dich gut, Mirabelle, und das wird gut für dich enden. Bleib mir nahe und mach keinen Lärm.";
			link.l1.go = "mirabelle_8";
		break;
		
		case "mirabelle_8":
            dialog.text = "Ich schwöre, ich werde es nicht tun, Senor.";
			link.l1 = "...";
			link.l1.go = "mirabelle_9";
		break;
		
		case "mirabelle_9":
            DialogExit();
            npchar.dialog.currentnode = "mirabelle_10";
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("Mrt_Rocur");
			sld.dialog.currentnode = "rocur_85";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
			pchar.questTemp.Mtraxx.Mirabella = "true";
		break;
		
		case "mirabelle_10":
            dialog.text = "Herr?";
			link.l1 = "Du hast gut gemacht, Mädchen, das gefällt mir an dir. Jetzt gehen wir zu meinem Schiff, wo du für einige Zeit in eine kleine Kabine gesteckt wirst. Es tut mir leid, aber ich möchte nicht, dass du zu Tyrex läufst und ihm irgendetwas erzählst.";
			link.l1.go = "mirabelle_11";
		break;
		
		case "mirabelle_11":
            dialog.text = "Keine Chance, Senor! Ich würde niemals zu Tyrex gehen, este bastardo! Ich hasse ihn! Ich hasse ihn!!!";
			link.l1 = "Woah! Was hat er dir angetan?";
			link.l1.go = "mirabelle_12";
		break;
		
		case "mirabelle_12":
            dialog.text = "Viel... Ich hasse ihn, ich hasse ihn!";
			link.l1 = "Ich verstehe. Sobald wir ankommen, wirst du in einem ziemlich schicken Haus leben. Allein. Halte mich bei guter Laune und niemand wird dir jemals wehtun. Jetzt geh zu einem Beiboot ... Mirabelle.";
			link.l1.go = "mirabelle_13";
		break;
		
		case "mirabelle_13":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella.win_condition.l1.location = "Shore75";
			pchar.quest.mtraxx_pasq_mirabella.function = "Mtraxx_PasqualeMirabella";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1.location = "Shore77";
			pchar.quest.mtraxx_pasq_mirabella1.function = "Mtraxx_PasqualeMirabella";
			AddPassenger(pchar, npchar, false);//добавить пассажира
			SetCharacterRemovable(npchar, false);
			SetFunctionTimerCondition("Mtraxx_MirabellaSailOver", 0, 0, 30, false); // месяц на доплыть до Исла Моны
		break;
		
		case "mirabelle_14":
            dialog.text = "Sind wir angekommen, senor?";
			link.l1 = "Ja, Liebling. Dies ist mein Dorf und mein Haus. Ich besitze den Ort. Ich bin jedoch ein seltener Gast hier - draußen gibt es zu viel Arbeit. Stelle sicher, dass du mein Haus sauber hältst, während du darin lebst, oder ich werde dich Rodgar und seinen Zimmerleuten übergeben. Fühle dich frei, auf der Insel herumzulaufen, sie ist sehr schön, aber es gibt sowieso kein Entkommen von ihr.";
			link.l1.go = "mirabelle_15";
			// belamour legendary edition -->
			link.l2 = "Nun, hier sind wir. Das ist mein Zuhause. Alles auf dieser Insel gehört mir. Ich komme nicht oft hierher - ich lebe schließlich auf dem Schiff, aber trotzdem muss jemand auf das Haus aufpassen. Rodgar hat sich gnädigerweise bereit erklärt, Ihnen diese ehrenvolle Rolle zu übergeben. Sie können sich frei bewegen, sogar im Dschungel oder an den Stränden, aber stellen Sie sicher, dass Sie jemanden als Begleiter haben, es gibt immer noch wilde Tiere. Wie auch immer, Sie können von hier aus ohne Schiff nicht weg.";
			link.l2.go = "mirabelle_15a";
		break;
		
		case "mirabelle_15a":
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
            dialog.text = "Ich habe nirgendwohin zu laufen, Senor "+pchar.name+". Ich habe niemanden, und niemand braucht mich. Außer du verkaufst mich an ein Bordell...";
			link.l1 = "Am Herd gibt es eine Luke, die in den Untergrund führt, geh nicht dorthin, du wirst in die Höhle fallen und dir die Knochen brechen, oder du wirst nicht zurückkommen können und könntest vor Hunger sterben. Und dann wäre es schade, dass ich dich umsonst gerettet habe.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_15":
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			// <-- legendary edition
            dialog.text = "Ich habe keinen Ort, um zu gehen, senor "+pchar.name+". Ich habe keine Familie und keinen Nutzen. Ich könnte wieder in einem Bordell landen.";
			link.l1 = "Es gibt eine Luke, die zur Höhle führt, halte dich fern davon. Es ist dunkel und gefährlich dort unten.";
			link.l1.go = "mirabelle_16";
		break;
		
		case "mirabelle_16":
            dialog.text = "Ich werde mich fernhalten, senor.";
			link.l1 = "Es gibt auch ein Schlafzimmer im Obergeschoss. Folge mir.";
			link.l1.go = "mirabelle_17";
		break;
		
		case "mirabelle_17":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1 = "location";
			pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1.location = "IslaMona_TwoFloorRoom";
			pchar.quest.mtraxx_islamona_mirabella1.function = "Mtraxx_PasqualeMirabellaRoom";
		break;
		
		case "mirabelle_18":
            dialog.text = "";
			link.l1 = "Dort. Ich habe dir das ganze Haus gezeigt. Es ist nicht schlimmer als Tyrex's Ort, in dem du vorher gelebt hast. Ich hoffe, es gefällt dir.";
			link.l1.go = "mirabelle_19";
		break;
		
		case "mirabelle_19":
            dialog.text = "Ja, Senor. Sie haben ein großes Haus. Ich verspreche, in Ihrer Abwesenheit gut darauf aufzupassen.";
			link.l1 = "Ich bin froh, dass du so kooperativ zu mir bist. Ich hoffe, du bist ehrlich. Sei ehrlich zu mir oder du wirst es bereuen, es nicht zu sein. Sei ein braves Mädchen und mach mich nicht traurig und ich werde gut zu dir sein. Charlie Prince hält sein Wort!";
			link.l1.go = "mirabelle_20";
			// belamour legendary edition -->
			link.l2 = "Ich glaube dir, Liebling. Ich denke, du wirst hier sicherer sein als gefesselt in diesem dunklen Lagerraum, in dem Tyrex dich gehalten hat.";
			link.l2.go = "mirabelle_20a";
		break;
		
		case "mirabelle_20a":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
            dialog.text = "Danke Ihnen, Senor "+pchar.name+". Danke, dass du deinen... Kameraden nicht mich töten lassen hast. Du bist so nett zu mir...";
			link.l1 = "Heh, und du bist lustig,... Und dein Gesicht ist auch hübsch, sogar mit einer Brandmarke auf deiner Stirn. Ich hoffe, alles andere ist auch in Ordnung... Nun, zeige deinem Kapitän, was du kannst. Lassen wir uns nach dem Seegang ein paar Stunden entspannen.";
			link.l1.go = "mirabelle_21";
			link.l2 = "Sehr gut. Das ist es, ich habe - viel Arbeit zu erledigen. Und du machst es dir bequem, triff Rodgar und die Jungs. Wenn ich zurückkomme, plaudern wir noch etwas.";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_20":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			// <-- legendary edition
            dialog.text = "Danke, Senor "+pchar.name+". Danke, dass Sie Ihren... Begleiter nicht erlaubt haben, mich zu töten. Sie sind sehr freundlich.";
			link.l1 = "Heh, du bist eine lustige kleine Süße... Ein hübsches Gesicht trotz der Narbe. Hoffe, der Rest ist auch in Ordnung.. Zeig jetzt deinem Kapitän, was du kannst.";
			link.l1.go = "mirabelle_21";
			// belamour legendary edition -->
			link.l2 = "Sehr gut. Das war's, ich habe - viel Arbeit zu tun. Und du mach dich häuslich, triff Rodgar und die Jungs. Wenn ich zurückkomme, plaudern wir noch etwas.";
			link.l2.go = "mirabelle_21a";
		break;
		
		case "mirabelle_21a":
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 400);
			pchar.questTemp.Mtraxx.MirabellaFirstTimeSex = true;
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_21":
			DialogExit();
			
			pchar.questTemp.Mtraxx.MirabellaFirstTimeKiss = true;
			sld = characterFromId("Mirabella");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("IslaMona_MirabelleKiss", "");
		break;
		
		case "mirabelle_22":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "Herr "+pchar.name+" du bist so süß... Du bist ein echter Gentleman. Du musst erst vor kurzem aus Europa angekommen sein.";
			link.l1 = "Schmeichle mir du kleiner Lügner, ich kaufe es. Heh, du bist gut, Mirabelle! Tyrex hat einen guten Geschmack, he-he...";
			link.l1.go = "mirabelle_23";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_23":
            dialog.text = "Ich bin es nicht. Sie sind ein Gentleman. Aber Sie geben vor, aus irgendeinem Grund unhöflich zu sein. Mhmm... Es hat mir sehr gefallen. Ich werde darauf warten, Sie wiederzusehen...";
			link.l1 = "Ach ja, ein Gentleman... ein Glücksritter, ha-ha! Nun gut, Liebchen, mach es dir hier erstmal gemütlich.";
			link.l1.go = "mirabelle_24";
		break;
		
		case "mirabelle_24":
            dialog.text = "Auf Wiedersehen, Senor.";
			link.l1 = "...";
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex"))
			{
				link.l1.go = "mirabelle_28";
				DeleteAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex");
			}
			else link.l1.go = "mirabelle_25";
			// <-- legendary edition
		break;
		
		case "mirabelle_25":
            DialogExit();
			npchar.InOurHouse = true;
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
		    chrDisableReloadToLocation = false;
			pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;
		
		case "mirabelle_26":
            dialog.text = TimeGreeting()+", señor "+pchar.name+"! Ich bin sehr froh, dich zu sehen. Wie geht es dir?";
			link.l1 = RandSwear()+""+RandPhraseSimple("Zittern mir die Balken, zittern mir die Seele!","Oh, besser zu leben und zu sterben, unter der mutigen schwarzen Flagge, die ich fliege!")+" Charlie Prince ist in Ordnung, Liebling.";
			link.l1.go = "mirabelle_26x";
			if (!CheckAttribute(pchar, "questTemp.MirabelleBlock")) {
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "Liebling, wie wäre es, wenn du einen Kapitän ein bisschen glücklicher machst?";
					link.l2.go = "mirabelle_sex";
				}
			}
		break;
		
		case "mirabelle_26x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
		break;
		
		case "mirabelle_sex":
            dialog.text = "Alles für Sie, senor!";
			link.l1 = RandPhraseSimple("Macht die Enterhaken bereit!","Entern Sie!");
			link.l1.go = "mirabelle_sex_1";
		break;
		
		case "mirabelle_sex_1":
            DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("", "");
			
			LAi_SetActorType(npchar);
			// belamour legendary edition -->
			if(CheckAttribute(pchar,"questTemp.Mtraxx.MirabellaFirstTimeSex")) npchar.dialog.currentnode = "mirabelle_22";
		    else npchar.dialog.currentnode = "mirabelle_27";
			// <-- legendary edition
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_27":
            dialog.text = "Mhm... Senor, Sie sind ein Zauberer! Hat es Ihnen auch gefallen? Ich habe mein Bestes gegeben.";
			link.l1 = "Du hast großartige Arbeit geleistet, Liebling.";
			link.l1.go = "mirabelle_28";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_28":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_26";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_sleep":
            dialog.text = "Das ist nicht wahr, nicht wahr! Senor "+pchar.name+" ist gut und freundlich! Er gibt nur vor, ein böser Pirat zu sein! Du bist, Herr "+pchar.name+"?";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6_1");
		break;
		
		case "mirabelle_29":
            dialog.text = TimeGreeting()+", Señor "+pchar.name+"! Ich freue mich sehr, dich zu sehen. Wie geht es dir? Warum bist du so traurig?";
			link.l1 = "Hallo, Mirabelle. Warum denkst du, dass ich traurig bin?";
			link.l1.go = "mirabelle_30";
		break;
		
		case "mirabelle_30":
            dialog.text = "Nun, ich kann es sehen. Du bist nicht der übliche du. Willst du, dass ich dich aufmuntere? Komm schon! Ich habe einige wirklich süße Früchte aus den Dschungeln gepflückt und der Fisch, den Rodgar und seine Jungs gestern gefangen haben, ist geröstet und noch warm.";
			link.l1 = "Warte. Ich möchte mit dir reden.";
			link.l1.go = "mirabelle_31";
		break;
		
		case "mirabelle_31":
            dialog.text = "Natürlich, Señor, was immer Sie sagen. Ich bin ganz Ohr";
			link.l1 = "Erzähl mir, wie du in die Hände von Tyrex geraten bist und warum auf deiner Stirn ein Diebeszeichen ist. Hab keine Angst, ich werde dir nie wehtun. Ich muss nur deine Geschichte hören.";
			link.l1.go = "mirabelle_32";
		break;
		
		case "mirabelle_32":
            dialog.text = "Ach, senor! Meine Geschichte ist kurz und langweilig. Ich wurde in Puerto Rico geboren, mein Vater war ein weißer Gentleman, meine Mutter - eine Indianerin. Ich habe meinen Vater nie gesehen. Als ich ein Kind war, war ich ein Diener und als ich aufwuchs, hatte ich die Torheit begangen, den Schmuck meines Meisters zu stehlen. Ich hatte nie meinen eigenen und ich wollte einen so sehr, nur um ihn für einen Tag zu tragen. Natürlich haben sie alles herausgefunden\nEs gab einen Prozess, ich wurde ausgepeitscht, gebrandmarkt und ins Gefängnis von San Juan gesteckt. Ich blieb dort zu lange: einer der Offiziere machte einen Deal mit einem Chef und ich wurde für eine Handvoll goldener Dublonen an ein Bordell in Philipsburg verkauft\nIch verbrachte dort ein Jahr oder so. Eines unglücklichen Tages wurden wir von Tyrex und seinem elenden Freund mit Brille besucht.";
			link.l1 = "Pasquale Lavoisier...";
			link.l1.go = "mirabelle_33";
		break;
		
		case "mirabelle_33":
            dialog.text = "Ja-ja, sein Name war Senor Pasquale Lavoisier. Ich habe keine Ahnung, was sie in mir sahen, aber kurz nach ihrem Besuch hat Tyrex mich von Madame Johanna gekauft und mich in ein abgeschlossenes Haus voller Truhen und Waren gesteckt. Es war die schlimmste Zeit meines Lebens, noch schlimmer als die Tage, die ich im Gefängnis von San Juan verbracht habe. Tyrex hat mich jeden Tag besucht, es sei denn, er war auf See und dann konnte ich frei atmen, aber jedes Mal, wenn Senor Lavoisier kam, habe ich... ich.... Es war das Schlimmste von allem. Senor "+pchar.name+", bitte, darf ich nicht davon sprechen?\nIch weiß nicht, wie lange ich dort war. Und dann bist du gekommen und hast mich von diesem schrecklichen Haus weggenommen. Ich hatte sehr viel Glück, dass du so freundlich warst.";
			link.l1 = "Kind? Mirabelle, aber ich habe genau dasselbe mit dir gemacht: Ich habe dich auf eine Insel gebracht und dich in einem Haus eingesperrt.";
			link.l1.go = "mirabelle_34";
		break;
		
		case "mirabelle_34":
            dialog.text = "Nein, senor, das ist nicht wahr. Bin ich hier eingesperrt? Ich mache jeden Tag einen Spaziergang um die Insel. Es ist ein wunderbarer und friedlicher Ort. Muss ich viel Hausarbeit machen? Überhaupt nicht, und ich gewöhne mich sowieso daran. Und du bist nicht wie Tyrex, nicht wie sein Kaufmannsfreund. Ich freue mich immer, dich zu sehen, du bist so jung und gutaussehend. Und auch ein Gentleman...";
			link.l1 = "Mirabelle, möchtest du, dass ich dich in eine Stadt bringe? Ich werde dir genug Geld geben. Wohin? Wähle irgendeine Kolonie.";
			link.l1.go = "mirabelle_35";
		break;
		
		case "mirabelle_35":
            dialog.text = "Herr, wollen Sie mich wegschicken? Bitte nicht, ich flehe Sie an!";
			link.l1 = "Nun... Ich dachte, du würdest in dein normales Leben zurückkehren wollen...";
			link.l1.go = "mirabelle_36";
		break;
		
		case "mirabelle_36":
            dialog.text = "Ach, Señor "+pchar.name+", und was bleibt für mich übrig? Wie soll ich heiraten, als gezeichnete Halbblut? Ich werde wieder in ein Bordell verkauft. Bitte, schickt mich nicht weg. Ich mag diesen Ort, nirgendwo habe ich mich so friedlich und sicher gefühlt. Rodgar und seine Jungs sind gute Kerle, wir sind Freunde und sie haben mich nie verletzt, jeder von ihnen würde sein Leben für mich riskieren. Ich mag es, Zeit mit ihnen zu verbringen, und es macht Spaß! Manchmal machen wir ein Feuer am Strand und ich tanze Samba. Bitte, Senor, ich werde alles für Sie tun, lassen Sie mich bleiben!";
			link.l1 = "Gut, Mirabelle, bleib hier, wenn dir dieser Ort so sehr gefällt. Wisse nur, dass du hier keine Gefangene bist, du kannst mich jederzeit bitten, dich von hier wegzubringen.";
			link.l1.go = "mirabelle_37";
		break;
		
		case "mirabelle_37":
            dialog.text = "Mein lieber guter Herr, danke! Danke! Danke! Ich werde Sie nie um so etwas bitten - ich möchte Gefangener dieser Insel bleiben... und Ihr Gefangener, hihi... Sie sind heute so freundlich, aber traurig! Sie singen und fluchen nicht wie sonst.";
			link.l1 = "Ich könnte singen, aber nicht mehr fluchen, Mirabelle. Und... es tut mir leid, wenn ich jemals unhöflich zu dir war.";
			link.l1.go = "mirabelle_38";
		break;
		
		case "mirabelle_38":
            dialog.text = "Werden Sie streng und strickt sein, genau wie ein englischer Lord?.. Ah... senor, möchten Sie, dass ich heute Abend für Sie tanze und singe? Komm jetzt mit mir! Es gibt keine bessere Heilung für Traurigkeit als Liebe. Ich habe Sie so sehr vermisst.";
			link.l1 = "Hah! Guter Punkt, mein liebes Mädchen... Lass uns gehen.";
			link.l1.go = "mirabelle_39";
		break;
		
		case "mirabelle_39":
            DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			if (pchar.location == "IslaMona_TwoFloorRoom") DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
			else DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;
		
		case "mirabelle_40":
			PlaySound("Voice\English\LE\Mirabel\Mirabel_07.wav");
            dialog.text = "Ach, Senor "+pchar.name+", Sie waren heute so sanft, mhm... Sind Sie zufrieden mit mir, mein lieber Kapitän?";
			link.l1 = "Alles war entzückend, Mirabelle.";
			link.l1.go = "mirabelle_41";
			locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;
		
		case "mirabelle_41":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			LAi_SetStayType(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;
		
		case "mirabelle_42":
			bool bMary = GetCharacterIndex("Mary") != -1 && CheckAttribute(pchar, "questTemp.LSC.Mary_officer");
			bool bHelena = GetCharacterIndex("Helena") != -1 && CheckAttribute(pchar, "questTemp.Saga.Helena_officer");
            dialog.text = TimeGreeting()+", Senor "+pchar.name+"! Ich bin so froh, dich zu sehen! Wie geht es dir?";
			link.l1 = ""+LinkRandPhrase("Froh dich auch zu sehen, mein Mädchen.","Hallo, Mirabelle. Du bist immer die Gleiche - fröhlich und schön, was für ein angenehmer Anblick.","Hallo, hübsche Dame. Du siehst umwerfend aus!")+"Mir geht es gut. Ich hoffe, dir geht es auch gut.";
			link.l1.go = "mirabelle_42x";
			if (!bMary && !bHelena && !CheckAttribute(npchar,"quest.rodgar")) // прогона 3
			{
				if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
				{
					link.l2 = "Mirabelle, ich vermisse dich und deinen Wiesel schon jetzt. Wirst du deinen Seewolf küssen?";
					link.l2.go = "mirabelle_43";
				}
			}
		break;
		
		case "mirabelle_42x":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		case "mirabelle_43":
            dialog.text = "Ach, mein süßer Kapitän, du hast mir auch gefehlt! Komm schon, ich bin am Rand!";
			link.l1 = "...";
			link.l1.go = "mirabelle_39";
		break;
		
		// Jason Исла Мона
		case "mirabelle_44":
			dialog.text = "Herr Kapitän! Kapitän "+pchar.name+"! Ich bin so glücklich! Du wirst uns retten!";
			link.l1 = "Ich freue mich auch, dich zu sehen, Mirabelle. Also, wie steht es um die Verluste?";
			link.l1.go = "mirabelle_45";
		break;
		
		case "mirabelle_45":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			sld = characterFromId("Islamona_carpenter");
			sld.dialog.currentnode = "IslaMona_66";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "mirabelle_46":
			dialog.text = "Kapitän, Kapitän, danke! Du bist der Beste, der Freundlichste! Du hast mich nicht nur vor Monstern gerettet, sondern mir auch ein neues Leben geschenkt! Uns allen!";
			link.l1 = "";
			link.l1.go = "mirabelle_47";
			locCameraFromToPos(1.25, 1.28, 0.71, false, 2.28, -0.20, 1.91);
		break;
		
		case "mirabelle_47":
            DialogExit();
		    npchar.dialog.currentnode = "mirabelle_42";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "IslaMona_2";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					sld = characterFromId("Helena");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					sld = characterFromId("Himenes_companion_1");
					sld.dialog.currentnode = "island_man_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
			}
		break;
		
		case "mirabelle_48":
			dialog.text = "Herr Kapitän!";
			link.l1 = "Hallo auch, Schönheit. Langweilst du dich nicht, oder?";
			link.l1.go = "mirabelle_49";
		break;
		
		case "mirabelle_49":
			dialog.text = "Ach, Kapitän! Seitdem Sie mich aus diesem schrecklichen Haus gerettet haben, hat mein Leben Farbe und Freude gewonnen.";
			link.l1 = "Bist du glücklich?";
			link.l1.go = "mirabelle_50";
		break;
		
		case "mirabelle_50":
			dialog.text = "Natürlich! Und ich möchte dieses Glück mit dir teilen... Ich warte auf dich in deinem Zimmer, oben.";
			link.l1 = "Was für eine Frau...";
			link.l1.go = "mirabelle_51";
		break;
		
		case "mirabelle_51":
			DialogExit();
			LAi_SetActorType(npchar);
		    npchar.dialog.currentnode = "mirabelle_40";
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			pchar.questTemp.IslaMona.Mirabelle = "true";
		break;
		
		case "mirabelle_52":
			dialog.text = "Herr Kapitän!";
			link.l1 = "Hallo auch dir, Schönheit. Langweilst du dich nicht, oder?";
			link.l1.go = "mirabelle_53";
		break;
		
		case "mirabelle_53":
			dialog.text = "Ach, Kapitän! Seitdem Sie mich aus diesem schrecklichen Haus gerettet haben, hat mein Leben Farbe und Freude gewonnen.";
			link.l1 = "Bist du glücklich?";
			link.l1.go = "mirabelle_54";
		break;
		
		case "mirabelle_54":
			dialog.text = "Sehr! Außer...";
			link.l1 = "Ich sehe, du willst mich etwas fragen?";
			link.l1.go = "mirabelle_55";
		break;
		
		case "mirabelle_55":
			dialog.text = "Ja, Kapitän! Ich möchte... meine Freude mit einem bestimmten Mann teilen...";
			link.l1 = "Wird es ihm etwas ausmachen?";
			link.l1.go = "mirabelle_56";
		break;
		
		case "mirabelle_56":
			dialog.text = "Nein, nein, Kapitän. Wir würden zusammen glücklich sein, das weiß ich sicher. Nur... würden Sie es erlauben?";
			link.l1 = "Du mehr als jeder andere verdienst dies. Aber ich werde die beiden von euch nicht heiraten, frag nicht mal!";
			link.l1.go = "mirabelle_57";
		break;
		
		case "mirabelle_57":
			dialog.text = "Ha-ha! Mein Herr! Danke, Senor Kapitän. Ich weiß nicht, was sie in der großen Welt über Sie sagen, aber ich habe Sie immer als die freundlichste und hellste Person gesehen.";
			link.l1 = "Viel Glück, Mirabelle.";
			link.l1.go = "mirabelle_58";
		break;
		
		case "mirabelle_58":
			DialogExit();
			npchar.quest.rodgar = true;
		    npchar.dialog.currentnode = "mirabelle_42";
		break;
		
		// губернатор Картахены
		case "CartahenaMayor":
            dialog.text = "Verdammte Diebe! Egal, unser Kurier ist bereits auf dem Weg nach Porto Bello. Bald wird unsere Staffel ankommen und...";
			link.l1 = TimeGreeting()+", Eure Hoheit. Es ist eine Freude, Sie in solch einem schönen Anwesen zu sehen. Ich hoffe, Sie behalten es, nachdem wir weg sind. Wenn ich Sie wäre, würde ich nicht auf das Geschwader zählen, plus wir bleiben hier nicht länger als drei Tage. Ich wette, Sie verstehen, dass die edlen Dons von Porto Bello nicht so schnell hierher kommen werden, um Ihnen zu helfen. Also, lassen wir uns direkt zum Geschäft kommen, sollen wir?";
			link.l1.go = "CartahenaMayor_1";
		break;
		
		case "CartahenaMayor_1":
            dialog.text = "Reden wir schon Geschäft? Sieh aus dem Fenster! Sieh, was deine Halsabschneider auf den Straßen und in den Häusern tun!";
			link.l1 = "Oh, Eure Hoheit, das ist nichts im Vergleich zu dem, was sie tun werden, wenn Sie nicht kooperativ genug sind. Ich hoffe, Sie verstehen, wer diese Männer sind...";
			link.l1.go = "CartahenaMayor_2";
		break;
		
		case "CartahenaMayor_2":
            dialog.text = "Ich weiß, zu welchem abscheulichen Übel Pirat Charlie Prince fähig ist! Ich weiß, wer sein Boss ist! Mit der Zeit werden wir euer Banditenversteck auf Hispaniola ausräuchern! Wie viel?";
			link.l1 = "Verschwende keine Worte, mein lieber Gouverneur. Du solltest mir besser 250 000 Pesos besorgen.";
			link.l1.go = "CartahenaMayor_3";
		break;
		
		case "CartahenaMayor_3":
            dialog.text = "Was?! Deine Frechheit kennt keine Grenzen! Dies ist ein Überfall!";
			link.l1 = "Es ist natürlich Raub. Was könnte es sonst sein? Versammle deine Eliten, deine Händler und Kaufleute, sammle Gold in einer großen Kiste, denn sonst... Ich werde es für dich und dein Volk viel schlimmer machen.";
			link.l1.go = "CartahenaMayor_4";
		break;
		
		case "CartahenaMayor_4":
            dialog.text = "Verdammter Pirat! Bastardo! Ketzer! Geh zum Teufel!";
			link.l1 = "Wegen deiner dreckigen Zunge erhöhe ich das Lösegeld auf 300.000.";
			link.l1.go = "CartahenaMayor_5";
		break;
		
		case "CartahenaMayor_5":
            dialog.text = "VERBRENN IN DER HÖLLE, DU HURENSOHN!!!";
			link.l1 = "350 000. Möchtest du weitermachen?";
			link.l1.go = "CartahenaMayor_6";
		break;
		
		case "CartahenaMayor_6":
            dialog.text = "Es gibt kein solches Geld in der Stadt!";
			link.l1 = "Du lügst. Das kann einfach nicht sein. Wir könnten hier mindestens eine Million zusammenkratzen, aber ich fürchte, wir haben nicht genug Zeit dafür. Daher werde ich freundlich und großzügig sein. Du kennst die Summe. Geh und hol sie.";
			link.l1.go = "CartahenaMayor_7";
		break;
		
		case "CartahenaMayor_7":
            dialog.text = "Ich sage es dir noch einmal, Charlie Prince: Es gibt kein solches Geld in Cartagena!";
			link.l1 = "Oh... wie kannst du nur so langweilig sein. Entermesser! Such herum und bring jeden hierher, den du findest. Such gut! Und wir werden hier auf dich warten, Euer Gnaden...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaInResidence");
		break;
		
		case "CartahenaMayor_8":
            dialog.text = "";
			link.l1 = "He, Senor 'Sturkopf'! Haben Sie Ihre Meinung bezüglich des Geldsammelns in der guten Stadt Cartagena geändert?... Was ist passiert, warum sind Sie plötzlich so ernst?! Geht es Ihnen gut? Soll ich Ihnen etwas Wasser bringen?";
			link.l1.go = "CartahenaMayor_9";
		break;
		
		case "CartahenaMayor_9":
            dialog.text = "";
			link.l1 = "Soweit ich verstehe, sind diese beiden Damen Ihre Frau und Ihre Tochter, habe ich recht? Das dritte Mädchen sieht aus wie eine Dienerin, Sie scheinen sich einen Dreck um sie zu kümmern, also werden wir ihr keinen Schaden zufügen, aber diese beiden Schönheiten könnten die Aufmerksamkeit meines Waffenbruders, Senor Cutlass, erregen. Er scheint sie zu mögen, Senor. Na und? Werden Sie das Lösegeld übernehmen?";
			link.l1.go = "CartahenaMayor_10";
		break;
		
		case "CartahenaMayor_10":
            dialog.text = "Ich... Ich werde Zeit brauchen.";
			link.l1 = "Aha! Jetzt redest du! Also, wer ist hier der Bastardo? Es hat dich einen Dreck gekümmert, dass meine Männer deine Bürger terrorisieren, aber deine zwei Frauen sind eine völlig andere Angelegenheit, oder? Hast du es gewagt, mit mir zu verhandeln, du Trottel? Ich werde dir zeigen, was es bedeutet, Charlie Prince zu kreuzen!";
			link.l1.go = "CartahenaMayor_10x";
		break;
		
		case "CartahenaMayor_10x":
            dialog.text = "";
			link.l1 = "Geh und sammle das verdammte Lösegeld. 350.000 und keinen Peso weniger. Du hast einen Tag. Wir bleiben hier, trinken etwas Wein und gesellen uns zu diesen süßen Frauen... Sei schnell, amigo, oder ich und mein Freund hier, senor Cutlass, könnten sich in deine Schönheiten verlieben, und dann müsstest du auch sie auslösen. Vorwärts! Marsch!";
			link.l1.go = "CartahenaMayor_11";
		break;
		
		case "CartahenaMayor_11":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaResidenceWait", 5.0);
		break;
		
		case "CartahenaMayor_12":
			AddMoneyToCharacter(pchar, 350000);
            dialog.text = "Nimm dein Blutgeld, Charlie Prince!";
			link.l1 = "Haben Sie das Lösegeld gesammelt? Prächtig! Aber Sie sind eine Stunde zu spät, mein lieber Gouverneur. Diese zusätzliche Stunde hat mir und dem Entermesser die Erkenntnis vermittelt, dass unser Leben ohne diese Schönheiten, die so freundlich und gesprächig mit uns waren, viel zu langweilig sein wird...";
			link.l1.go = "CartahenaMayor_13";
		break;
		
		case "CartahenaMayor_13":
            dialog.text = "Du... du!";
			link.l1 = "Ach, du bist zu nervös wegen deiner Arbeit, mein Freund. Ich habe nur gescherzt... Entermesser! Los geht's, wir verlassen diesen Ort!";
			link.l1.go = "CartahenaMayor_14";
		break;
		
		case "CartahenaMayor_14":
            DialogExit();
			AddQuestRecord("Roger_9", "7");
			AddDialogExitQuestFunction("Mtraxx_CartahenaToFort");
		break;
		
		// Камилла
		case "camilla":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "Oh, also das ist Der Charlie Prince, der berühmte Pirat, der Schrecken des spanischen Südhaupt!";
			link.l1 = RandSwear()+"Heh, ich hatte keine Ahnung, dass ich in Tortuga so beliebt bin. Wie heißt du, süßes Mädchen?";
			link.l1.go = "camilla_1";
		break;
		
		case "camilla_1":
            dialog.text = "Mein Name ist Camilla.";
			link.l1 = "Camilla... Ich kannte mal ein Mädchen mit dem gleichen Namen zurück in Frankreich. Es war so lange her!";
			link.l1.go = "camilla_2";
		break;
		
		case "camilla_2":
			PlaySound("ambient\tavern\orijka_003.wav");
            dialog.text = "";
			link.l1 = "(kotzend) ... verdammt... Es tut mir leid, Prinzessin, aber der Prinz ist heute Nacht etwas betrunken. Also... ähm.. warum bist du zu mir gekommen?";
			link.l1.go = "camilla_3";
		break;
		
		case "camilla_3":
            dialog.text = "Aus verschiedenen Gründen. Oder vielleicht ohne Grund.";
			link.l1 = "Gott, das ist zu kompliziert. Du scheinst ein Rätsel zu sein, Mädel.";
			link.l1.go = "camilla_4";
		break;
		
		case "camilla_4":
            dialog.text = "Jedes Mädchen muss ein Geheimnis haben.";
			link.l1 = "Scheint, als wolltet Ihr, dass ich dieses Geheimnis löse. Nicht wahr? Ich schwöre, ich bin ein Meister darin, die Geheimnisse von Mädchen zu lüften! Sollen wir in eine Taverne gehen und etwas Wein trinken? Ich werde Euch das beste Leckerbissen besorgen!";
			link.l1.go = "camilla_5";
		break;
		
		case "camilla_5":
            dialog.text = "Mmm... Ich mag harte Kerle. Aber ich werde keinen Wein unten bei betrunkenen Taugenichtsen trinken. Besorg uns ein Zimmer, dort werden wir trinken und reden.";
			link.l1 = RandSwear()+"Du bist heiß! Folge mir!";
			link.l1.go = "camilla_6";
		break;
		
		case "camilla_6":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1 = "locator";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.location = "Tortuga_town";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator = "reload4_back";
			pchar.quest.mtraxx_retribution_tavern.function = "Mtraxx_RetributionToTavern";
		break;
		
		case "camilla_7":
			PlaySound("Voice\English\hambit\Gr_officiant_1.wav");
            dialog.text = "Komm schon... Schenk ein, lass die Dame nicht warten!";
			link.l1 = "Sicher, mein Liebling!";
			link.l1.go = "camilla_8";
		break;
		
		case "camilla_8":
			LAi_Fade("", "");
			PlaySound("ambient\tavern\krujki_005.wav");
			PlaySound("ambient\tavern\naliv_003.wav");
			PlaySound("ambient\tavern\glotok_001.wav");
			WaitDate("", 0, 0, 0, 1, 5);
            dialog.text = "Mmm... Nur daran zu denken, ich bin hier ganz alleine mit Charlie Prince, trinke einen ausgezeichneten Wein...";
			link.l1 = "Du wirst diese Fahrt mit mir genießen, oh, das verspreche ich! Charlie Prince ist sanft und freundlich zu Damen, die sich ihm unterwerfen. Wirst du dich unterwerfen, Prinzessin?";
			link.l1.go = "camilla_9";
		break;
		
		case "camilla_9":
            dialog.text = "Tee-hee... Natürlich, Süße! Deine Versprechungen klingen so verlockend, weißt du...";
			link.l1 = "Nun, verschwenden wir dann keine Zeit, Schönheit?";
			link.l1.go = "camilla_10";
		break;
		
		case "camilla_10":
            dialog.text = "Oh! Ich liebe! Echte Männer!..";
			link.l1 = "...";
			link.l1.go = "camilla_11";
		break;
		
		case "camilla_11":
            DialogExit();
			pchar.GenQuest.FrameLockEsc = true;
			bDisableCharacterMenu = true;
			ResetSound();
			WaitDate("", 0, 0, 0, 2, 30);
			SetLaunchFrameFormParam("", "", 0, 5.1);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			PlayStereoSound("sex\sex2.wav");
			LaunchFrameForm();
			if(IsEquipCharacterByArtefact(pchar, "totem_03")) 	
			{
				AddCharacterHealth(pchar, 6);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else AddCharacterHealth(pchar, 3);
			LAi_SetCurHPMax(pchar);
			DoQuestCheckDelay("Mtraxx_RetributionRoomSex", 5.1);
		break;
		
		case "camilla_12":
            dialog.text = "Mmm...";
			link.l1 = "Hat es dir gefallen, meine Prinzessin?";
			link.l1.go = "camilla_13";
		break;
		
		case "camilla_13":
            dialog.text = "Sicher! Ich hoffe, ich habe dir auch gefallen.";
			link.l1 = "Heh! Sogar mein Kopf ist jetzt kristallklar!";
			link.l1.go = "camilla_14";
		break;
		
		case "camilla_14":
            dialog.text = "Prinz, ich habe eine Bitte an dich. Wirst du mir helfen?";
			link.l1 = "Ich hole dir einen Stern vom Himmel, ha-ha! Mach weiter.";
			link.l1.go = "camilla_15";
		break;
		
		case "camilla_15":
            dialog.text = "Ich muss nach La Vega, um Tyrex zu sehen. Ich habe Angst vor ihm, aber ihr macht zusammen Geschäfte. Bitte bring mich zu ihm.";
			link.l1 = "Schau dir das an! Und warum sollte so ein süßes, zerbrechliches Mädchen den Hüter des Kodex sehen wollen?";
			link.l1.go = "camilla_16";
		break;
		
		case "camilla_16":
            dialog.text = "Dieses süße, zerbrechliche Mädchen möchte etwas Geld verdienen. Mein verstorbener Vater und Brüder haben mir nicht viel Geld hinterlassen. Tyrex kann das regeln.";
			link.l1 = "Ach wirklich? Und wie? Willst du einen Hinweis für eine spanische Galeone? Ha-ha!";
			link.l1.go = "camilla_17";
		break;
		
		case "camilla_17":
            dialog.text = "Karawanen und Städte zu plündern ist ein Geschäft für harte Kerle, genau wie du, Schätzchen. Ich habe ein anderes Geschäft für Marcus. Er kauft und verkauft Informationen, richtig? Ich habe etwas... Keine Möglichkeit, dass ich es selbst nutzen kann, aber er könnte. Ich wäre schon glücklich genug, nur ein kleines Interesse daran zu bekommen.";
			link.l1 = "Interessant! Erzähl mir mehr.";
			link.l1.go = "camilla_18";
		break;
		
		case "camilla_18":
            dialog.text = "Hm... Ich weiß nicht...";
			link.l1 = "Oh, komm schon. Betrachte mich als rechte Hand von Tyrex, ich habe viel für ihn gegraben, glaub mir. Wenn deine Informationen es wert sind - Ich werde sie selbst kaufen.";
			link.l1.go = "camilla_19";
		break;
		
		case "camilla_19":
            dialog.text = "Gut. Ich werde dir mehr erzählen, aber keine Details, bis ich das Geld bekomme. Abgemacht, Liebling?";
			link.l1 = "Aber natürlich, hübsches Ding. Charlie Prince verarscht seine Partner nicht... du weißt, was ich meine, ha-ha-ha! Leg los, ich bin ganz Ohr.";
			link.l1.go = "camilla_20";
		break;
		
		case "camilla_20":
            dialog.text = "... Mein Vater war ein Skipper auf einem Handelsschooner. Eines Tages erfuhr er irgendwie von einer alten spanischen Bergbausiedlung tief in den Dschungeln von Main. Vor zwanzig Jahren wurde sie von einem Erdbeben zerstört. Die Bergleute verließen sie und die geheimen Passagen wurden vergessen. Bis auf eine. Mein Vater fand sie\nEr nahm meine Brüder und einen Führer mit und sie fanden den Ort voller Gold, das vor Jahren abgebaut und geschmolzen wurde. Viel Gold. Mindestens eine Million Pesos. Der Vater kehrte zum Schiff zurück, um Männer zum Transport des Goldes zu holen, aber er war schockiert zu erfahren, dass sie verschwunden war. Anscheinend hatte sein erster Offizier eine Meuterei begonnen und sie ließen ihn und meine Brüder an verlassenen Küsten zurück\nSie bauten ein Langboot und segelten verzweifelt an der Küste entlang auf der Suche nach einem bewohnten Ort, aber ... (schluchzt) ein Sturm traf sie und meine (schluchzt) Brüder starben. Der Vater überlebte, aber nach seiner Rückkehr nach Hause lebte er nicht lange - der Tod meiner Brüder tötete ihn Tag für Tag. Bevor er starb, hat er eine Karte gemacht und sie mir gegeben\nEr sagte mir, dass, wenn ich heirate, mein Mann dorthin gehen sollte, das Gold holen und wir werden unser Leben wie Könige leben. Sicher werden wir das, aber ich werde meinen Mann nicht wieder in diese verfluchten Dschungel lassen. Nicht wieder! Eine Million Pesos, sagte mein Vater, aber das ist einfach nicht meine Liga. Ein solcher Preis, nur die besten und härtesten Männer können ihn bekommen - Männer wie Marcus Tyrex. Deshalb gehe ich ihn treffen.";
			link.l1 = "Wie viel verlangst du für die Karte?";
			link.l1.go = "camilla_21";
		break;
		
		case "camilla_21":
            dialog.text = "Zweihundert goldene Dublonen. Es ist nichts im Vergleich zum Preis. Tyrex wird dem zustimmen, da bin ich sicher. Er ist so reich wie Crassus.";
			link.l1 = "Heh! Und was, wenn das alles nur Schabernack ist?";
			link.l1.go = "camilla_22";
		break;
		
		case "camilla_22":
            dialog.text = "Sehe ich aus, als hätte ich einen Todeswunsch? Versuchen, Tyrex zu überqueren? Liebling, besser in Armut leben als gar nicht leben. Also, wirst du mich dorthin bringen? Bitte...";
			link.l1 = "Wo ist die Karte? Zeigst du sie mir?";
			link.l1.go = "camilla_23";
		break;
		
		case "camilla_23":
            dialog.text = "Mein Priester hält es sicher. Ich werde es Ihnen für 200 Dublonen zeigen.";
			link.l1 = "Sehr gut! Ich kaufe es. Fremde in Tavernen verlangen manchmal viel mehr für Müll.";
			link.l1.go = "camilla_24";
		break;
		
		case "camilla_24":
            dialog.text = "Bist du es? Ist es wahr, Liebling? Ich bin so glücklich, dass ich nicht nach La Vega gehe! Ehrlich gesagt, habe ich Angst vor Marcus. Ich habe übrigens auch Angst vor dir... aber ein bisschen weniger.";
			link.l1 = "Ein so süßes kleines Mädchen braucht mich nicht zu fürchten. Wohin soll ich das Geld bringen?";
			link.l1.go = "camilla_25";
		break;
		
		case "camilla_25":
            dialog.text = "Lass uns einen Deal machen: Finde mich an jedem Tag von zehn Uhr morgens bis ein Uhr nachmittags in unserer Kirche. Ich werde mich unter dem Schutz dieses heiligen Ortes viel sicherer fühlen. Dort werden wir unseren Deal abschließen.";
			link.l1 = "Hast du immer noch Angst vor mir? Ha-ha! Nicht doch, Camilla, ich werde dich nicht hintergehen. Charlie Prince würde so etwas Niedriges für zweihundert Dublonen nicht tun, außerdem möchte ich dir helfen.";
			link.l1.go = "camilla_26";
		break;
		
		case "camilla_26":
            dialog.text = "Wunderbar. Sehr gut dann, Schönling, ich werde auf dich warten... Danke für die wundervolle Zeit, die wir heute Abend zusammen verbracht haben! Ich bin so glücklich, dass wir uns getroffen haben!";
			link.l1 = "Bis bald, Hübsche.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_RetributionOutRoom");
		break;
		
		case "camilla_27":
			PlaySound("Voice\English\hambit\Girls_3.wav");
            dialog.text = "So? Hast du das Geld gebracht, Süße?";
			if (PCharDublonsTotal() >= 200) // belamour legendary edition
			{
				link.l1 = "Ja. Nimm dein Gold und gib mir jetzt die Karte.";
				link.l1.go = "camilla_28";
			}
			else
			{
				link.l1 = "Ich bin gleich dahinter.";
				link.l1.go = "camilla_27x";
			}
		break;
		
		case "camilla_27x":
            DialogExit();
			npchar.dialog.currentnode = "camilla_27";
		break;
		
		case "camilla_28":
			RemoveDublonsFromPCharTotal(200); // belamour legendary edition
			GiveItem2Character(pchar, "mapEnrico"); 
            dialog.text = "Danke dir, Schatz... Hier, nimm es. Ich schwöre bei dem Gedächtnis meines Vaters - diese Karte ist kein Falsifikat, sie wird dich direkt dorthin führen, wo du hin sollst...";
			link.l1 = "Gut, Süße. Wie wäre es, wenn wir unseren Deal feiern, genau wie das letzte Mal?";
			link.l1.go = "camilla_29";
		break;
		
		case "camilla_29":
            dialog.text = "Ich würde gerne, Prinz, aber ich bereite mich auf eine Beichte vor meinem Priester vor, daher bin ich gerade verpflichtet, jeder Versuchung fernzubleiben. Lass es uns das nächste Mal machen.";
			link.l1 = "Uh, du neckst mich, Mädel. Gut! Keine Zeit zu verschwenden: wir sind dabei, die Segel zu setzen. Ich schwöre, ich werde deinen Anteil verdoppeln, wenn die Karte deines Vaters mich tatsächlich zum Gold führt.";
			link.l1.go = "camilla_30";
		break;
		
		case "camilla_30":
            dialog.text = "Du bist so großzügig, Liebling. Gute Reise!";
			link.l1 = "Yo-ho-ho!";
			link.l1.go = "camilla_31";
		break;
		
		case "camilla_31":
            DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Roger_10", "2");
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1 = "location";
			pchar.quest.mtraxx_retribution_carataska.win_condition.l1.location = "shore10";
			pchar.quest.mtraxx_retribution_carataska.function = "Mtraxx_RetributionCarataska";
			pchar.questTemp.Mtraxx.Retribution = "carataska";
		break;
		
		case "camilla_sleep":
            dialog.text = "Deine Bastarde haben meinen Vater und meine Brüder ermordet. Euer Angriff auf Cartagena hat jeder Familie dort Kummer bereitet. Ich hoffe, du hast jetzt Angst, genauso viel Angst wie wir, die Bürger von Cartagena, als deine Brut sich auf den Straßen und in den Häusern vergnügte. Du wirst in der Hölle brennen, Charlie Prince.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep4");
		break;
		
		// дон Энрико - народный мститель
		case "enrico":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_01.wav");
            dialog.text = "So wenige Dinge in dieser Welt erfreuen mich so sehr wie das Zuschauen, wie Ratten in der Kiste sich gegenseitig zerfleischen!\nNur die stärkste und abscheulichste Ratte überlebt. Dann musst du sie nur noch ausquetschen...";
			link.l1 = "Argh! Wer bist du?!";
			link.l1.go = "enrico_1";
		break;
		
		case "enrico_1":
			PlaySound("Voice\English\LE\Zorro\Don_Enriko_02.wav");
            dialog.text = "Ich bin Don Enrico. Englischer Abschaum nennt mich Fuchs, Holländer nennen mich Vos, Franzosen nennen mich Renaud. Aber ich bevorzuge meinen spanischen Spitznamen - Zorro. Ich bestrafe das Böse, das das einfache Volk quält und terrorisiert, den am wenigsten geschützten Teil des Volkes\nDieser Prozess heute wird vier Piraten von Marcus Tyrex richten: Bold Jeffry, Pelly der Entermesser, Luke der Kobold und Charlie Prince - diese Banditen sind verantwortlich für ein Massaker in Merida und Cartagena. Der letzte Mistkerl namens Handsome Jean ist hier nicht aufgetaucht, er muss der Klügste von euch allen sein.";
			link.l1 = "Was?!";
			link.l1.go = "enrico_2";
		break;
		
		case "enrico_2":
            dialog.text = "Du bist ein Abschaum, Charlie Prince, aber du bist kein Idiot. Ich habe es bereits herausgefunden, denke ich. Es ist eine Falle für euch alle, die ich mit Hilfe von gefälschten Karten, Dokumenten, Worten und Versprechen von Gold und Silber gestellt habe. Ich habe euch alle in diese Verliese gelockt, wo ihr einander aus euren widerlichen Eigenschaften heraus zerstört habt: Neid, Gier, Gemeinheit und Skrupellosigkeit. Es war wahrhaftig eine Nemesis!";
			link.l1 = "Camilla... Ich hätte wissen müssen, dass etwas mit diesem Mädchen nicht stimmt!";
			link.l1.go = "enrico_3";
		break;
		
		case "enrico_3":
            dialog.text = "Ein Mädchen namens Camilla führte ein friedliches Leben in Cartagena mit ihrem Vater und ihren Brüdern, sie stand kurz vor der Hochzeit, als du und deine Teufel die Stadt angegriffen haben. Deine Piraten haben alle, die ihr nahe standen, getötet, also schwor sie, alles zu tun, um sie zu rächen. Es war eine schwere Rolle für sie. Sie musste sogar mit einem Bastard schlafen, der für den Tod ihrer Familie verantwortlich war. Ich fürchte mir vorzustellen, was sie während der Tat gefühlt haben muss\nDas arme Mädchen verbrachte Tage in der Kirche und betete um Vergebung. Sie spendete die blutigen Dublonen, die du ihr gegeben hast, den Opfern, die am meisten unter deinem Angriff gelitten haben. Sie ist jetzt in einem Kloster, arme Seele. Du hast ihr Leben zerstört, Abschaum! Denke darüber nach! Denk an all die Camillas, Isabelas, Rositas, die du vergewaltigt und zu Witwen gemacht hast! Wie viele Juans, Carloses, Pedros ihr Bastarde getötet und gefoltert habt!\nErinnere dich an Merida! Erinnere dich daran, wie du dem Stadtoberhaupt versprochen hast, es nicht in Brand zu setzen und dann den ganzen Ort niedergebrannt hast!";
			link.l1 = "Ich habe das nie beabsichtigt! Als ich die Residenz verließ, stand bereits alles in Flammen. Ich habe das nicht angeordnet...";
			link.l1.go = "enrico_4";
		break;
		
		case "enrico_4":
            dialog.text = "Du bist verantwortlich für die Taten deiner Piraten. Tote Männer hängen an deinem Hals und bald werden sie dich in die Hölle ziehen!";
			link.l1 = "Komm schon! Huh? Kämpfe gegen mich! Das ist es, was du willst, oder?! Dann lass es uns tun!";
			link.l1.go = "enrico_5";
		break;
		
		case "enrico_5":
            PlaySound("Voice\English\LE\Zorro\Don_Enriko_03.wav");
            if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				dialog.text = "Nein, Charlie Prince. Greif nicht nach deiner Waffe, es ist sinnlos... Ich könnte dich leicht töten, aber ein schneller Tod ist nicht genug für einen Bastard wie dich. Du wirst für immer in diesem Verlies bleiben. Die Tür, durch die du hier eingetreten bist, ist von außen mit einem Stein blockiert, die Tür hinter mir wird auch blockiert sein, außerdem sind dort auch noch robuste Gitter, die sie schützen. Das ist es, es gibt keinen Ausweg außer diesen beiden Türen\nWas zum... Ich habe alle Türen verschlossen!";
				link.l1 = "Was geht ab...";
				link.l1.go = "exit";
				AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag");
			}
			else
			{
				dialog.text = "Nein, Charlie Prince. Greif nicht nach deiner Waffe, es ist sinnlos... Ich könnte dich leicht töten, aber ein schneller Tod ist für einen Bastard wie dich nicht genug. Du wirst für immer in diesem Verlies bleiben. Die Tür, durch die du hierher gekommen bist, ist von außen mit einem Stein blockiert, die Tür hinter mir wird auch blockiert sein, außerdem gibt es noch stabile Gitter, die sie schützen. Das ist es, es gibt keinen Ausweg außer diesen beiden Türen\nUnten ist Wasser, also wirst du genug Zeit haben, über deine Taten nachzudenken. Ganz alleine hier, in der Dunkelheit, wirst du vielleicht bereuen, was du getan hast, bevor du verhungerst oder wahnsinnig wirst\nNoch eine letzte Sache - der Schatz unten ist eine Fälschung. Goldbarren sind nichts weiter als gefärbtes Blei. Dublonen sind zwar echt, aber es gibt nur wenige von ihnen, die ausreichen, um die Felsen in den Truhen zu bedecken. Ein würdiges Ende für Piraten, was? Ihr habt euch gegenseitig für einen falschen Schatz getötet, Prinz. Leb wohl. Betet für deine sündige Seele, Charlie Prince, wenn du dich noch daran erinnerst, wie...";
		// belamour legendary edition -->
				link.l1 = "Ich habe gerade die gesamte Vorhut von Marcus Tyrex getötet! Ihr denkt, diese rostigen Gitterstäbe halten mich auf?! Ich zerbreche sie mit deinem eigenen Kopf!";
				link.l1.go = "enrico_5a";
				link.l2 = "Vielleicht habe ich es verdient. Aber ich gebe nicht auf, hörst du?! Ich werde einen Weg finden, das tue ich immer!";
				link.l2.go = "enrico_5b";
			}
		break;
		
		case "enrico_5a":
			AddCharacterHealth(pchar, 5);
			AddCharacterExpToSkill(pchar, "FencingL", 400);
			AddCharacterExpToSkill(pchar, "FencingS", 400);
			AddCharacterExpToSkill(pchar, "FencingH", 400);
			AddCharacterExpToSkill(pchar, "Pistol", 400);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		
		case "enrico_5b":
			AddCharacterExpToSkill(pchar, "Leadership", 1200);
			ChangeCharacterComplexReputation(pchar, "nobility", 15);
            DialogExit();
			AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		// <-- legendary edition
		
		case "enrico_Tonzag_1":
			dialog.text = "Du hast recht, die Tür ist zuverlässig, auch wenn sie alt ist. Danke, dass du das Tor nicht heruntergelassen hast - es hätte mich aufgehalten. Aber nicht für lange.";
			link.l1 = "Hercule Tonzag, Kahlkopf Gaston! Ich hätte ahnen sollen, dass jemand wie du sich mit dem Prinzen und all seinen Anhängern verbünden würde. Glück für mich, dich auch hier zu treffen.";
			link.l1.go = "enrico_Tonzag_2";
			sld = CharacterFromID("Zorro");
			CharacterTurnToLoc(sld, "quest", "door");
		break;
		
		case "enrico_Tonzag_2":
			dialog.text = "Glücklich, sagst du? Nun, wenn du es eilig hast zu sterben... Obwohl ich dachte, du hättest es nicht eilig, da du ihn hast verhungern lassen anstatt ihm gegenüberzutreten.";
			link.l1 = "Mir Feigheit vorwerfen? Wie töricht von dir. Wie ich dem Prinzen gesagt habe, ist der Tod eine zu leichte Strafe für ihn. Er ist kein Gegner für mich.";
			link.l1.go = "enrico_Tonzag_3";
		break;
		
		case "enrico_Tonzag_3":
			dialog.text = "Und du bist kein Gegner für mich, Don.";
			link.l1 = "Vor zehn Jahren? Sicherlich. Jetzt? Kaum. Darüber hinaus...";
			link.l1.go = "enrico_Tonzag_4";
		break;
		
		case "enrico_Tonzag_4":
			dialog.text = "Außerdem was? Was ist mit der dramatischen Pause? Obwohl, wenn ich über deine Karnevalsmaske nachdenke... Ist es nicht ein bisschen früh, mich schon abzuschreiben?";
			link.l1 = "Du hast die Tür aufgebrochen, aber allein mit roher Gewalt wirst du bei mir nicht weit kommen. Wie steht es mit deinen Reflexen? Deiner Sicht? Mit nur einem Auge. Ich habe noch beide.";
			link.l1.go = "enrico_Tonzag_5";
		break;
		
		case "enrico_Tonzag_5":
			dialog.text = "Nun, zumindest vorerst. Heh-heh.";
			link.l1 = "Für Porto Bello verdienst du eine schlimmere Qual als der Prinz!";
			link.l1.go = "enrico_Tonzag_6";
		break;
		
		case "enrico_Tonzag_6":
			dialog.text = "Ach, also hast du gehört, was ich getan habe? Vermute, sie werden noch eine Weile darüber in deinem Haufen tratschen. Dann weißt du, was ich durchgemacht habe.";
			link.l1 = "Du bist alt, Tonzag, und dieses Mal wird dein Übermut dein Untergang sein. Und ja, ich habe nicht nur davon gehört - Cartagena, Merida sind dein Werk. Genau wie Porto Bello.";
			link.l1.go = "enrico_Tonzag_7";
		break;
		
		case "enrico_Tonzag_7":
			dialog.text = "Hätte es als Schmeichelei aufgefasst, aber nein, nicht mein Werk. Obwohl es von weitem ähnlich aussehen mag. Zu amateurhaft. Aber selbst in Porto Bello gab es... Vorfälle.";
			link.l1 = "Zwischenfälle?! An jenem Tag starb eine Person... Und da du dieses Massaker begonnen hast, mache ich dich immer noch dafür verantwortlich, selbst wenn du nicht jeden selbst getötet hast. Ich mache dich für jeden 'Zwischenfall' verantwortlich.";
			link.l1.go = "enrico_Tonzag_8";
		break;
		
		case "enrico_Tonzag_8":
			dialog.text = "Eine Person, sagst du... Viele starben an jenem Tag. Sei präzise.";
			link.l1 = "Wahrlich, du hast kein Herz, wenn du das sagen kannst! Aber ich werde antworten: der, den du nicht hättest töten sollen. Mein Vater, Don de la Vega. Wäre er noch am Leben, hätte ich diesen Weg nicht eingeschlagen, und ihr alle würdet noch leben.";
			link.l1.go = "enrico_Tonzag_9";
		break;
		
		case "enrico_Tonzag_9":
			dialog.text = "Halt den Mund, Welpchen. Meine liebe Frau... starb auch dort.";
			link.l1 = "Erwartest du Beileid? Du wirst es nicht bekommen. Das ist die Strafe des Herrn für dich. Scheint, als hättest du doch ein Herz - klein und schwarz. Und ich werde es mit meiner Klinge finden.";
			link.l1.go = "enrico_Tonzag_10";
		break;
		
		case "enrico_Tonzag_10":
			dialog.text = "Oh, das Dramatische über mein Herz. Du irrst dich, wenn du denkst, du hättest Schlimmeres gesehen als ich.";
			link.l1 = "Glaubst du, ich bin nur ein verwöhnter reicher Jüngling, der Geld verschwendet? Wisse dies: Ich habe keinen Dublon für Glücksspiel oder Frauen ausgegeben! Ich habe alles in den Kampf gegen deinesgleichen geworfen und mein Leben dafür gewidmet!";
			link.l1.go = "enrico_Tonzag_11";
		break;
		
		case "enrico_Tonzag_11":
			dialog.text = "Und für was? Scheint nicht sehr erfolgreich zu sein. Handelsrouten sind immer noch voll von Piraten. Du bist allein in deinem Kreuzzug. Und sie sind eine ganze Legion.";
			link.l1 = "Jemand muss es tun. Wenigstens jemand. Und vielleicht rette ich durch den Tod eines einzigen Piratenkapitäns ein paar Leben.";
			link.l1.go = "enrico_Tonzag_12";
		break;
		
		case "enrico_Tonzag_12":
			dialog.text = "Dumm. Idealistisch. Und... auf eine Art, edel, würde ich sagen, wenn nicht für deine Methoden. Unehrenhaft, wie deine Feinde. Am Ende bist du... nicht besser.";
			link.l1 = "Lass es mich nicht predigen! Ehre ist für diejenigen, die ihre Gesetze befolgen. Ich verstehe dich. Ich denke wie du. Und ich bestrafe.";
			link.l1.go = "enrico_Tonzag_13";
		break;
		
		case "enrico_Tonzag_13":
			dialog.text = "Du hast recht. Dir etwas beizubringen ist sinnlos. Also, wir werden uns nicht friedlich trennen. Aber du, Don Enrico, bist mir völlig egal. Du bist nicht einmal meiner Zeit wert.";
			link.l1 = "Was meinst du...";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag2");
		break;
		
		case "enrico_Tonzag_14": // после выстрела в Зорро в подземелье
            dialog.text = "Bist du in Ordnung, Kapitän? Ich habe dich gewarnt, vorsichtig zu sein. Hätte auf mein Bauchgefühl hören sollen.";
			link.l1 = "Ja, mir geht's gut. Danke, Hercule. Nur ein bisschen...";
			link.l1.go = "enrico_Tonzag_15";
		break;
		
		case "enrico_Tonzag_15":
            dialog.text = "...schockiert? Hab keine Angst es zuzugeben - es ist normal für jemanden deines Alters und in einer solchen Situation. Außerdem ist dieser Don ein guter Manipulator.";
			link.l1 = "Uh-huh. Obwohl, er schien Angst vor dir zu haben. Das hat mich überrascht. Aber es hat mich auch wieder zur Besinnung gebracht. Übrigens, lebt er noch? Scheint so. Du solltest ihm nicht den Rücken zukehren.";
			link.l1.go = "enrico_Tonzag_16";
		break;
		
		case "enrico_Tonzag_16":
            dialog.text = "Lebendig, aber benommen. Er kommt zu sich. Ich hätte auf den Kopf zielen sollen, nicht auf den Rumpf - es stellt sich heraus, dass unser edler Hidalgo unter seinem Mantel eine leichte, aber robuste Kürass trägt. Heh, selbst Fleetwood blieb bei einem einfachen Pourpoint. Sonst gäbe es hier schon eine Blutlache.";
			link.l1 = "Und wie bist du hier gelandet? Am selben Ort wie er?";
			link.l1.go = "enrico_Tonzag_17";
		break;
		
		case "enrico_Tonzag_17":
            dialog.text = "Keine Zeit dafür jetzt. Er wird bald wieder auf den Beinen sein. Für jetzt heben wir dieses Tor.";
			link.l1 = "Wir... was?? Sicher, du könntest Herkules sein, aber...";
			link.l1.go = "enrico_Tonzag_18";
		break;
		
		case "enrico_Tonzag_18":
            dialog.text = "Männer meiner Jugend waren hart geschmiedet. Diese Scharniere haben kurze Stifte. Komm schon, gib mir eine Hand, Kapitän - Ich mag vielleicht Herkules sein, aber ich komme in die Jahre.";
			link.l1 = "Also gut, bei drei! Und hoch!";
			link.l1.go = "enrico_Tonzag_19";
		break;
		
		case "enrico_Tonzag_19":
            DialogExit();
			locCameraSleep(true);
			LAi_FadeLong("Mtraxx_RetributionEnricoAndTonzag6", "");
		break;
		
		case "enrico_Tonzag_20": // окружили Зорро
            dialog.text = "Glaubst du, du hast all meine Pläne ruiniert und gewonnen? Das war natürlich unerwartet, aber ich habe trotzdem viel berücksichtigt!";
			link.l1 = "Wie diese leichte Kürass unter deiner Kleidung. Warum das und nicht ein vollständiger oben drauf? Nur um deinen Mantel zur Schau zu stellen?";
			link.l1.go = "enrico_Tonzag_21";
		break;
		
		case "enrico_Tonzag_21":
            dialog.text = "Ich bin keine Jungfrau, Prinz. Meine Gründe sind rein praktisch - eine volle Rüstung schränkt meine Bewegungen zu sehr ein. Jeder hat seinen eigenen Ansatz.";
			link.l1 = "Und doch bin ich hier, ein Franzose, der bereits gewohnt ist, Kürassen zu tragen, im Gegensatz zu einem Spanier. Die Ironie. Also, was jetzt? Du konntest uns nicht einfangen. Du hast dich auf alles vorbereitet... Hat ein Duell in die Möglichkeiten hineingefigert? Oder ist das Schwert - und sogar die Kürass - für alles außer echten Kämpfen?";
			link.l1.go = "enrico_Tonzag_22";
		break;
		
		case "enrico_Tonzag_22":
            dialog.text = "Versuchst du auch, mich als Feigling zu bezeichnen? Wie ich schon sagte, du verdienst langes Leid, nicht den Tod in einem Duell. Was bringt es, wenn eure Seelen nicht die Zeit haben, all eure Sünden hier auf Erden zu ertragen und zu begreifen?";
			link.l1 = "Der Weg zur Hölle ist mit guten Vorsätzen gepflastert, wie man so schön sagt... Und würde das Quälen deiner Opfer nicht deine eigene Seele beschmutzen?";
			link.l1.go = "enrico_Tonzag_23";
		break;
		
		case "enrico_Tonzag_23":
            dialog.text = "Nie. Niemals. Denn ich bleibe mir und meinen Prinzipien treu.";
			link.l1 = "Aha, nicht wie wir. Du hast so viel darüber gesagt, wie wir abscheulicher Abschaum ohne einen Hauch von Ehre sind, also... warum nicht deinen Erwartungen gerecht werden? Wir werden uns selbst mit dir auseinandersetzen. Gemeinsam.";
			link.l1.go = "enrico_Tonzag_24";
			link.l2 = "Ich habe einen Vorschlag für Sie, Don Enrico. Ich fordere Sie hier und jetzt zu einem Duell heraus. Als Adliger zu einem Adligen.";
			link.l2.go = "enrico_Tonzag_26";
		break;
		
		case "enrico_Tonzag_24":
            dialog.text = "Hm-m. Sonst hättest du keine Chance. Tonzag wird natürlich knifflig sein... Also werde ich mich zuerst um dich kümmern.";
			link.l1 = "Als ob er dir das erlauben würde.";
			link.l1.go = "enrico_Tonzag_25";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "enrico_Tonzag_25":
            DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, false);
			LAi_SetCheckMinHP(sld, 1, true, "TonzagRanen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_26":
            dialog.text = "Du? Ein Adliger? Vielleicht bist du ein „Prinz“, aber ich bezweifle, dass ein Tropfen edlen Blutes in dir fließt.";
			link.l1 = "Du hast mir deinen wahren Namen offenbart. Ich werde dir meinen offenbaren. Ich bin Charles de Maure. Und wir haben einander genug beleidigt, dass jeder von uns das Recht hat, Genugtuung zu verlangen. Verteidige dich, Don Enrico.";
			link.l1.go = "enrico_Tonzag_27";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		case "enrico_Tonzag_27":
            dialog.text = "Aber bereue deine Entscheidung später nicht.";
			link.l1 = "Ich habe viele Entscheidungen in meinem Leben bereut, aber das wird nicht eine von ihnen sein. Fecht an!";
			link.l1.go = "enrico_Tonzag_28";
		break;
		
		case "enrico_Tonzag_28":
			DialogExit();
			EndQuestMovie();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Tonzag");
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			
			sld = CharacterFromID("Zorro");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;
		
		case "enrico_Tonzag_29": // после победы над Зорро
            dialog.text = "Geht es Ihnen gut, Kapitän? Unser edler Hidalgo trug nicht nur einen Kürass - er hat seine Klinge auch vergiftet. Hier, nehmen Sie das. Ich habe immer ein paar dabei, wenn ich durch den Dschungel gehe - man weiß nie, wann eine Schlange beißen könnte oder ein Rothaut einen vergifteten Pfeil wirft.";
			link.l1 = "Danke, Hercule. Mir geht's gut. Deine rechtzeitige Ankunft half mir, mich zusammenzureißen.";
			link.l1.go = "enrico_Tonzag_30";
			GiveItem2Character(PChar, "potion3");
			LAi_UseAtidoteBottle(pchar);
			LAi_UseAtidoteBottle(npchar);
		break;
		
		case "enrico_Tonzag_30":
            dialog.text = "Macht nichts. Los geht's, ich bringe dich hier raus - er hat erwähnt, den Eingang mit Steinen zu blockieren. Ich habe einen anderen Durchgang gefunden, eine Abkürzung.";
			link.l1 = "Sag mir, Hercule... was genau ist in Porto Bello passiert? Und wann?";
			link.l1.go = "enrico_Tonzag_31";
		break;
		
		case "enrico_Tonzag_31":
            dialog.text = "Ich habe heute keine Lust, darüber zu sprechen. Aber vielleicht eines Tages, bei einem Glas Wein oder etwas Stärkerem. Lass uns jetzt hier raus - der Bengel hatte recht, ich werde alt. Ich möchte auf dem Schiff ausruhen.";
			link.l1 = "Dann führe den Weg.";
			link.l1.go = "enrico_Tonzag_32";
		break;
		
		case "enrico_Tonzag_32":
            DoQuestReloadToLocation("Shore10", "goto", "goto2", "Mtraxx_RetributionEnricoAndTonzag8");
		break;
		
		case "mishelle_sleep":
            dialog.text = "Sag mir, Bruder - wie konntest du zu solch einer Abscheulichkeit werden? Als ich dir sagte, du solltest dich mit Piraten vertraut machen, meinte ich nicht, Städte niederzubrennen, unschuldige Zivilisten zu töten und Frauen zu foltern. Selbst ein Krieg kann mit Ehre und Würde geführt werden\nDu bist eine Schande für unsere Familie. Es ist gut, dass unser Vater nicht hier ist: Er wäre vor Scham gestorben, zu wissen, dass sein Sohn ein Pirat und Bandit geworden ist!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep5");
		break;
		
		case "mishelle_sleep_1":
            dialog.text = "Bruder! Bruder!\nKannst du mich hören?\nHinter einer von zwei Türen gibt es einen Durchgang. Die Tür kann geöffnet werden. Ein Schlüssel ist in deiner Nähe!\nFinde ihn auf der Treppe. Auf der Treppe!..";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep7");
		break;
		
		case "terrax_sleep":
            dialog.text = "Ha-ha-ha, hallo dort mein tapferer Schlitzhals! Warum bist du so traurig? Das Meer, Gold, Rum und Frauen - was fehlt dir noch? Erinnerst du dich an unser erstes Treffen? Ich sagte dir damals - ich brauche Männer, die den Geruch von Schießpulver oder das Austrocknen der roten Flüsse nicht fürchten. Du hast meine jede Hoffnung weit übertroffen! Du bist ein echter Pirat geworden, Charlie Prince! Ha-ha-ha!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_1";
			locCameraSleep(false);
		break;
		
		case "terrax_sleep_1":
            dialog.text = "Ein echter verfluchter Pirat! Ah-ah-ha-ha!";
			link.l1 = "";
			link.l1.go = "terrax_sleep_2";
		break;
		
		case "terrax_sleep_2":
			Mtraxx_RetributionSleepSkeletons();
            dialog.text = "Ua-ha-ha-ha-ha-ha!!!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionSleep6");
		break;

		// belamour legendary edition -->
		case "SlavesTrader":
            dialog.text = "Wer bist du? Was machst du hier? Antworte schnell!";
			link.l1 = "Ich komme aus Fadey, ich bin wegen einer Ladung schwarzer Knochen hier. Er hätte Sie warnen sollen.";
			link.l1.go = "SlavesTrader_1";
		break;
		
		case "SlavesTrader_1":
            dialog.text = "Hah! Schwitz nicht die Haut, Freund. Wir haben dich erkannt, Moscovit hat eine detaillierte Beschreibung gegeben. Er bat auch, sich nicht über den Preis zu ärgern. Also, unter Berücksichtigung der bereits von dir geleisteten Anzahlung sind es 10 000 Silber. Oder, wenn du in Gold bezahlst, dann nur 50 Dublonen. Nun, was hast du entschieden? Zieh nicht am Schwanz der Katze!";
			if(PCharDublonsTotal() >= 50)
			{
				link.l1 = "Ich werde 50 Dublonen zahlen. Es ist profitabler.";
				link.l1.go = "SlavesTrader_Dub";
			}
			if(sti(Pchar.money) >= 10000)
			{
				link.l2 = "Ich werde 10 000 Pesos zahlen.";
				link.l2.go = "SlavesTrader_P";
			}
			link.l3 = "Es tut mir leid, aber ich kann mir gerade keine Sklaven leisten.";
			link.l3.go = "SlavesTrader_X";
		break;
		
		case "SlavesTrader_Dub":
			RemoveDublonsFromPCharTotal(50);
            dialog.text = "Das ist großartig. Signalisiere deinen Männern, die Waren zu nehmen.";
			link.l1 = "Sicherlich.";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_P":
			AddMoneyToCharacter(pchar, -10000);
            dialog.text = "Das ist großartig. Signalisiere deinen Männern, die Waren zu nehmen.";
			link.l1 = "Gewiss.";
			link.l1.go = "SlavesTrader_End";
		break;
		
		case "SlavesTrader_End":
			DialogExit();
			AddQuestRecord("Roger_3", "25");
            pchar.questTemp.Mtraxx.GiveMeSlaves = "Deal";
			SetCharacterGoods(pchar, GOOD_SLAVES, (GetCargoGoods(pchar, GOOD_SLAVES) + 50));
			Log_Info("Fifty slaves shipped to "+PChar.Ship.Name);
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		
		case "SlavesTrader_X":
            dialog.text = "Nun, wie du wünschst. Es wird immer einen Käufer für dieses Produkt geben. Auf Wiedersehen, Freund.";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "SlavesTrader_EndX";
		break;
		
		case "SlavesTrader_EndX":
			DialogExit();
			AddQuestRecord("Roger_3", "26");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
			for(i=1; i<=3; i++)
			{
				sld = characterFromId("Mtraxx_SlavesSeller"+i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false); 
			DeleteAttribute(&locations[FindLocation("Shore29")],"DisableEncounters"); //энкаунтеры открыть
		break;
		// диалог Гаспара Златозубого Xenon
		case "GasparGold_meeting":
            dialog.text = "Grüße, Kapitän. Sie sind doch Charlie Prince, wenn ich mich nicht irre? Keine Sorge, meine Wände haben keine Ohren. Ehrlich gesagt, ist mir Ihr Name egal. Was zählt, ist, dass Sie mir empfohlen wurden, was bedeutet, dass wir Geschäfte machen können.";
			link.l1 = "Grüße auch an dich, Gaspard 'Goldenzahn'. Wobei, wie du heißt, ist mir eigentlich egal. Ich habe gehört, du wärst vielleicht daran interessiert, ein paar Kinkerlitzchen zu kaufen?";
			link.l1.go = "GasparGold_meeting_01";
		break;
		
		case "GasparGold_meeting_01":
            dialog.text = "Das ist korrekt. Niemand wird Ihnen einen besseren Preis anbieten als ich. Nun, außer vielleicht den Pfandleihern, aber sie kaufen nicht viel. Ich bin bereit, alles zu kaufen, was Sie anbieten. Sie müssen die Wertsachen nicht einmal persönlich zu mir bringen: Ich habe eine Hintertür, die zu einem abgelegenen Pier führt. Zögern Sie nicht, mir all den Schnickschnack zu verkaufen, den Sie in den Truhen auf Ihrem Schiff gelagert haben.";
			link.l1 = "Nun, das ist ausgezeichnet! Freut mich, Ihre Bekanntschaft zu machen.";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold_story":
			npchar.mtraxx.story = true;
            dialog.text = "Das ist meine persönliche Angelegenheit. Ich würde es bevorzugen, wenn du dich nicht darin einmischst. Ich sage nur, dass ich alles unter Kontrolle habe, so dass du risikofrei mit mir handeln kannst. Der Rest geht dich nichts an.";
			link.l1 = "Nun, risikofrei ist das Wichtigste! Es gibt noch etwas, was ich fragen wollte...";
			link.l1.go = "GasparGold";
		break;
		
		case "GasparGold":
			NextDiag.TempNode = "GasparGold";
            dialog.text = "Wie kann ich helfen? Möchten Sie einige zusätzliche Perlen oder Edelsteine loswerden? Vielleicht Gold, Silber, Schmuck? Ich kaufe alles.";
			if(!CheckAttribute(npchar,"mtraxx.story"))
			{
				link.l1 = "Sag mal, wie ist es, ein Käufer von gestohlenen Waren zu sein? Hast du keine Angst vor den Behörden?";
				link.l1.go = "GasparGold_story";
			}
			link.l2 = "Ich habe hier etwas... Ich möchte es gegen harte Münze tauschen.";
			link.l2.go = "GasparGold_01";
		break;
		
		case "GasparGold_01":
            dialog.text = "Nun, lass uns den Austausch machen. Dublonen oder Pesos?";
			link.l1 = "Lass uns mit Pesos gehen - kein Bedarf an Dublonen. Reguläres Geld wird überall akzeptiert.";
			link.l1.go = "GasparGold_peso";
			link.l2 = "Du hast es erraten - ich brauche speziell Dublonen. Also werde ich nur für diese verkaufen.";
			link.l2.go = "GasparGold_dub";
			link.l3 = "Ich habe gerade nichts zum Verkauf. Ich wollte nur sicherstellen, dass du bereit bist, wertvolle Gegenstände zu kaufen, wenn ich welche habe. Bis zum nächsten Mal!";
			link.l3.go = "exit";
		break;
		
		// окно торговли
		case "GasparGold_peso":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "GasparGold_dub":
            Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar, 1);
		break;
		
		// Диалоги после угроз вождю индейцев Кумване
		case "MeridaObsuzhdenie_Bad_1":
            dialog.text = "Hast du immer noch zu Einschüchterung, Kap, gegriffen? Ich hörte Drohungen sogar von draußen.";
			link.l1 = "Sie haben mir keine Wahl gelassen. Ich habe der Frau dieses Tagofa Geschenke für seine Hilfe angeboten. Sie wollte mir nicht einmal zuhören. Jetzt soll der Häuptling mit ihnen reden. Und wenn er es nicht schafft, diese sturen Kerle zur Vernunft zu bringen, werde ich ihm das Herz mit meinen eigenen Händen aus der Brust reißen. Und übrigens, wer ist Yahahu?";
			link.l1.go = "MeridaObsuzhdenie_Bad_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Bad_2":
            dialog.text = "Du hättest die Beziehungen zu den Indianern nicht verderben sollen. Wir Piraten haben nur ein Schwert und ein Schiff als Verbündete. Aber da dies deine Entscheidung ist, so sei es. Und Yahahu ist ein böser Dämon. Ich weiß nichts weiter über ihn.";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_3";
		break;
		
		case "MeridaObsuzhdenie_Bad_3":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Bad_4", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_4":
            dialog.text = "Zeit mit Überredung zu verschwenden, Leprechaun - das ist unklug. Oder würdest du lieber auf die reiche Beute verzichten und gute Beziehungen zu den Indianern pflegen?";
			link.l1 = "...";
			link.l1.go = "MeridaObsuzhdenie_Bad_5";
		break;
		
		case "MeridaObsuzhdenie_Bad_5":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Bad_6", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Bad_6":
            dialog.text = "Ich würde lieber beide bekommen.";
			link.l1 = "Es wird nicht funktionieren, in beiden Lagern einen Fuß zu haben. Nicht dieses Mal. Genug der Streitereien, alles ist bereits getan. Morgen wird uns der Chef über Tagofas Entscheidung informieren, und ich hoffe, er wird mich nicht enttäuschen. Andernfalls... werde ich zu extremen Maßnahmen greifen müssen. Was ich natürlich vermeiden möchte.";
			link.l1.go = "MeridaObsuzhdenie_Bad_7";
		break;
		
		case "MeridaObsuzhdenie_Bad_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CannotWait"); //разрешить отдыхать
			ChangeShowIntarface();
			
            sld = characterFromId("Lepricon");
			sld.dialog.Filename = "Quest\Roger.c";
			sld.dialog.currentnode = "lepricon_3";
			LAi_SetWarriorType(sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
		case "MeridaObsuzhdenie_Good_1":
            dialog.text = "Nun, wie laufen die Dinge? Werden wir einen Führer haben?";
			link.l1 = "Nein, Jean, das werden wir nicht tun. Der Häuptling und der gesamte Stamm fürchten die Kapongs wie der Teufel das Weihrauch. Es sieht so aus, als müssten wir unseren Plan aufgeben.";
			link.l1.go = "MeridaObsuzhdenie_Good_2";
			ChangeShowIntarface();
		break;
		
		case "MeridaObsuzhdenie_Good_2":
            StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Good_3", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_3":
            dialog.text = "Terrax wird über diese Wendung der Ereignisse nicht erfreut sein.";
			link.l1 = "Glaubst du, ich bin unglaublich glücklich, dass die Dinge so gekommen sind? Die feigen Lokono wollen sich nicht mit den Kapongs anlegen. Sie lassen sich weder durch Überredung noch durch Belohnungen locken.";
			link.l1.go = "MeridaObsuzhdenie_Good_4";
		break;
		
		case "MeridaObsuzhdenie_Good_4":
            StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Good_5", "Quest\Roger.c");
		break;
		
		case "MeridaObsuzhdenie_Good_5":
            dialog.text = "Dann werden wir Drohungen anwenden müssen. Sag ihnen, dass du ihr verdammtes Dorf niederbrennen und die Überlebenden foltern wirst, bis jemand zustimmt, uns zu führen.";
			link.l1 = "Jean, hast du völlig den Verstand verloren? Ich werde doch nicht die Häuser unschuldiger Menschen niederbrennen. Und sie schon gar nicht foltern.";
			link.l1.go = "MeridaObsuzhdenie_Good_6";
		break;
		
		case "MeridaObsuzhdenie_Good_6":
            dialog.text = "Charles Prince ist ein Muster an Wohltäter. Ich hätte nie solche Ausbrüche von Zärtlichkeit von dir erwartet.";
			link.l1 = "Das ist keine Zärtlichkeit, Hübscher. Nun, wir werden einen Indianer halbtot foltern. Aus Rache wird er uns direkt in die Hände der Kapongs führen und er wird auf Pfaden verschwinden, die nur ihm bekannt sind. Ich werde das Leben meiner Leute nicht so aufs Spiel setzen.";
			link.l1.go = "MeridaObsuzhdenie_Good_7";
		break;
		
		case "MeridaObsuzhdenie_Good_7":
            dialog.text = "In diesem Fall, Leprechaun und ich gehen. Hier sind fünfzigtausend Silber für die Befreiung von den Maracaibo Plantagen. Ich habe es für ein neues Schiff gespart. Und mein Rat an dich: Bleib eine Weile aus Marcus' Sicht. Auf Wiedersehen, Charles Prince.";
			link.l1 = "Auf Wiedersehen, Jean.";
			link.l1.go = "MeridaObsuzhdenie_Good_8";
			AddMoneyToCharacter(pchar, 50000);
		break;
		
		case "MeridaObsuzhdenie_Good_8":
            DialogExit();
			chrDisableReloadToLocation = false;
			ChangeShowIntarface();
			AddQuestRecord("Roger_5", "8b");
			CloseQuestHeader("Roger_5");
			
			sld = characterFromId("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Mrt_Rocur");
			LAi_type_actor_Reset(sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.location = "None";
			RemovePassenger(pchar, sld);
			
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "First time";
		break;
		
		// Немезида. Диалоги с офицерами после взрыва бочонков с порохом
		// Тонзаг
		case "Nemezida_Tonzag_1":
            dialog.text = "Jetzt wird jeder aus der Gegend hierher stürmen! Sind Sie sicher, dass es eine gute Idee war, diese Bäume in die Luft zu jagen, Kapitän?";
			link.l1 = "Verdammt! Vielleicht wäre es besser gewesen, wenn jeder mit Äxten gearbeitet hätte... Aber jetzt ist es zu spät dafür.";
			link.l1.go = "Nemezida_Tonzag_2";
		break;
		
		case "Nemezida_Tonzag_2":
            dialog.text = "Wahr. Wir müssen mit dem umgehen, was wir haben. Mach dich bereit.";
			link.l1 = "Du auch, Hercule.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tonzag_3":
            dialog.text = "Sie kommen immer noch in diese Richtung. Also, sollen wir uns auch um diese kümmern?";
			link.l1 = "Was ist, wenn es kein Ende von ihnen gibt? Wir sind nicht für diese Art von Ärger hier.";
			link.l1.go = "Nemezida_Tonzag_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_4":
            dialog.text = "Nun, alles hat ein Ende... Aber du hast recht. Lass uns zurückziehen. Und schnell.";
			link.l1 = "Lass uns eilen!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tonzag_5":
            dialog.text = "So unerbittlich, sie haben uns eingeholt. Es gibt hier einen Weg, sollen wir hineingehen? Es wird einfacher sein, die Linie zu halten.";
			link.l1 = "Warte, Hercule. Hörst du das? Da ist schon jemand drin. Du und die Jungs kümmert euch hier. Ich gehe rein, bevor sie den Schatz nehmen - ich bezweifle, dass jemand zufällig da reingestolpert ist.";
			link.l1.go = "Nemezida_Tonzag_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tonzag_6":
            dialog.text = "In Ordnung. Aber sei vorsichtig, ich habe ein schlechtes Gefühl bei der Sache.";
			link.l1 = "Auch du! Ich gehe da rüber.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Tonzag_7": // на берегу
            dialog.text = "Sie wollen etwas sagen, Kapitän? Sie waren auf unserem gesamten Weg zum Schiff in Gedanken versunken.";
			link.l1 = "Das stimmt. Ich habe über das nachgedacht, was ich in letzter Zeit getan habe. Über Terrax und... wohin es mich geführt hat. Bin ich meinem Bruder irgendwie näher gekommen, um ihn zu retten? Oder nach Hause zu gehen?..";
			link.l1.go = "Nemezida_Tonzag_8";
		break;
		
		case "Nemezida_Tonzag_8":
            dialog.text = "Hm-m. Gute Fragen. Und was sind deine Antworten?";
			link.l1 = "Nur noch eine Frage. Wenn es vorher sinnlos war, wird es dann wieder sinnlos sein? Terrax wird mir nicht helfen. Weder mit meinem Bruder, noch mit Tortuga.";
			link.l1.go = "Nemezida_Tonzag_9";
		break;
		
		case "Nemezida_Tonzag_9":
            dialog.text = "Wahrscheinlich nicht. Er hat dafür keine Verwendung. Überraschend, dass du es erst jetzt realisiert hast. Aber was ist deine nächste Frage?";
			link.l1 = "Wieso zum Teufel bin ich Terrax wie ein Schoßhund hinterhergelaufen und habe all die Zeit für ihn die Kastanien aus dem Feuer geholt?!";
			link.l1.go = "Nemezida_Tonzag_10";
		break;
		
		case "Nemezida_Tonzag_10":
            dialog.text = "Nun, das ist eine gute Frage. Eine richtige. Hast du diesmal eine Antwort?";
			link.l1 = "Mehr wie ein Vorsatz. Ich hatte heute Glück. Aber werde ich wieder Glück haben? Es ist wichtig zu wissen, wann man aufhören sollte. Und... sich selbst zu respektieren. Ich habe genug.";
			link.l1.go = "Nemezida_Tonzag_11";
		break;
		
		case "Nemezida_Tonzag_11":
            dialog.text = "Haben Sie beschlossen, Ihre Partnerschaft mit Terrax zu beenden?";
			link.l1 = "Ja. Ich habe wichtigeres zu tun. Familie, Freunde. Mit ihnen werde ich meine Ziele erreichen. Und nicht auf diese Weise. Und selbst wenn ich es tue... es wird nicht mit Marcus sein. Ich werde mein eigener Herr sein. Ich werde meine eigenen Entscheidungen treffen.";
			link.l1.go = "Nemezida_Tonzag_12";
		break;
		
		case "Nemezida_Tonzag_12":
            dialog.text = "Der Mann, dem ich einst folgte, spricht wieder. Verwickeln Sie sich nicht erneut mit den falschen Leuten. Verschwende das Potenzial nicht, das mich einst faszinierte.";
			link.l1 = "Habe es verstanden, Hercule. Und nochmals danke. Dieses Mal, dafür, dass du mir geholfen hast, es voll und ganz zu realisieren. Ich bin nicht länger der Prinz, ein Lakai. Ich bin Charles de Maure, ein stolzer Adliger. Lass uns das Schiff besteigen - wir sind beide müde.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Tonzag");
		break;
		
		// Книппель
		case "Nemezida_Knippel_1":
            dialog.text = "Das war eine verdammt große Explosion, Herr - eine Kanonenkugel an meinem Heck! Klang genau wie eine Breitseite von der Walküre. Aber ich fürchte, diese Kerle da drüben haben es auch bemerkt...";
			link.l1 = "Wenn sie es gemerkt haben, ist das ihr Problem. Niemand hat sie hier eingeladen. Bereit, ihnen eine Lektion zu erteilen, Charlie?";
			link.l1.go = "Nemezida_Knippel_2";
		break;
		
		case "Nemezida_Knippel_2":
            dialog.text = "Immer bereit, Herr!";
			link.l1 = "Ausgezeichnet. Lass uns anfangen.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Knippel_3":
            dialog.text = "Ich fürchte, wir bekommen gleich noch mehr Gesellschaft, Kapitän. Was sind Ihre Befehle?";
			link.l1 = "Wir werden tiefer in den Dschungel vordringen und uns verstecken - es gibt keine Möglichkeit, sie alle abzuwehren, und dafür sind wir sowieso nicht hier.";
			link.l1.go = "Nemezida_Knippel_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_4":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "Jawohl, Herr.";
			link.l1 = "Dann lasst uns auslaufen!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Knippel_5":
            dialog.text = "Sie haben uns aufgespürt, Kapitän! Aber wir können hier Schutz suchen - es scheint, dass dieser Weg irgendwohin führt, obwohl ich glaube, dass dort bereits jemand ist.";
			link.l1 = "Wir suchen nicht Schutz! Scheint, als hätte jemand anderes Wind von dem Schatz bekommen. Hier ist der Plan: Ich gehe schauen, was los ist, bevor sie mit allem davonlaufen, und du hältst sie hier mit den Jungs auf!";
			link.l1.go = "Nemezida_Knippel_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Knippel_6":
			PlaySound("VOICE\English\hambit\Charlie Knippel-05.wav");
            dialog.text = "Ja, Herr.";
			link.l1 = "Ausgezeichnet. Ich gehe jetzt runter! Ich vertraue darauf, dass du hier alles im Griff hast.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Knippel_7": // на берегу
            dialog.text = "Khe-khe... Sind Sie... in Ordnung, Herr?";
			link.l1 = "Charlie! Du hast den perfekten Zeitpunkt gewählt, um dich um mich zu sorgen. Spare deine Worte. Hältst du durch? Ich hätte dich auf dem Schiff lassen und stattdessen mehr Männer mitnehmen sollen...";
			link.l1.go = "Nemezida_Knippel_8";
		break;
		
		case "Nemezida_Knippel_8":
            dialog.text = "Ach, nur ein Kratzer, Herr. Ein bisschen müde. Hab noch nie so gekämpft, nicht einmal in meinen jungen Tagen! Aber ich habe ihnen eine solche Tracht Prügel verpasst, dass sie auf Ewigkeit Knippels hören werden!";
			link.l1 = "Königliche Marine, alte Schule! Es scheint, als hättest du wie ein Löwe gekämpft, Charlie. Aber dennoch kannst du kaum stehen. Bluff nicht - Wie schlimm ist die Wunde?";
			link.l1.go = "Nemezida_Knippel_9";
		break;
		
		case "Nemezida_Knippel_9":
            dialog.text = "Es ist nichts Ernstes, Kapitän, nur Erschöpfung. Der Eingang hinter Ihnen ist fast sofort eingestürzt, und wir haben all diese Männer über eine lange Zeit abgewehrt. Am Ende war ich allein, verwundet. Also habe ich meinen Weg hierher gemacht, um den Weg zu räumen und etwas Erste Hilfe zu bekommen.";
			link.l1 = "Ich verstehe. Nun, du hast heute deinen Teil getan. Was mich betrifft... Ich habe versagt. Wir wurden alle getäuscht und gegeneinander aufgehetzt für jemandes Amüsement-es gab nicht einmal einen Schatz. Und ich war nicht der einzige Narr dort.";
			link.l1.go = "Nemezida_Knippel_10";
		break;
		
		case "Nemezida_Knippel_10":
            dialog.text = "Sie haben versagt?.. Aber Sie leben noch, Herr. Was ist passiert? Sind Sie geflohen?";
			link.l1 = "Nein, aber es war immer noch etwas Laufen involviert. Entschuldigung, alter Freund, aber was dort drinnen passiert ist, werde ich niemandem erzählen - nicht einmal meinen engsten Freunden. Ich habe jedoch die notwendigen Schlüsse gezogen.";
			link.l1.go = "Nemezida_Knippel_11";
		break;
		
		case "Nemezida_Knippel_11":
            dialog.text = "Welche Schlussfolgerungen, Herr? Ich verstehe Ihre Überlegungen nicht immer. Meine Philosophie ist einfach - eine gute Culverin und Knüppel am Mast.";
			link.l1 = "Sag mir, du musst doch schon Spanier getötet haben, so wie ich es kürzlich getan habe. Damals, in deinen Tagen bei der königlichen Marine. Und später, mit Fleetwood.";
			link.l1.go = "Nemezida_Knippel_12";
		break;
		
		case "Nemezida_Knippel_12":
            dialog.text = "Ich habe es getan. Spanier, Niederländer - und viele andere auch. Wie Dick mir einmal sagte, unser Dienst ist gefährlich und anspruchsvoll. Aber warum fragst du? Was ist dein Punkt?";
			link.l1 = "Ich werde es erklären. Aber zuerst eine andere Frage. Hast du jemals daran gezweifelt, was du tust und warum du es tust, Charlie?";
			link.l1.go = "Nemezida_Knippel_13";
		break;
		
		case "Nemezida_Knippel_13":
            dialog.text = "Hm-m. Ich habe mir gesagt, dass ich im Interesse der Krone handle. Sich um Befehle zu sorgen, ist eine undankbare Aufgabe - man muss sie sowieso befolgen.";
			link.l1 = "Die Krone... Nun, du hattest deine Gründe. Ich hatte nicht einmal das - Michel hat mir gesagt, ich solle mich Terrax nähern. Aber war es all die Opfer wert? Hat es mir oder ihm geholfen? Ja, ja, wir mögen keine Don... aber wir sind alle menschlich.";
			link.l1.go = "Nemezida_Knippel_14";
		break;
		
		case "Nemezida_Knippel_14":
            dialog.text = "Ich glaube, ich beginne zu verstehen, worauf Sie hinauswollen, Herr.";
			link.l1 = "Gut. Sag mir, als Fleetwood ging, waren Sie froh, dass Sie nicht mehr auf niederländische Kaufleute schießen mussten? Einige von ihnen waren ehrliche Leute.";
			link.l1.go = "Nemezida_Knippel_15";
		break;
		
		case "Nemezida_Knippel_15":
            dialog.text = "Ich habe nie darüber nachgedacht, Kapitän. Aber das kann ich sagen - es war mir immer eine Freude, mit Ihnen zu dienen, Herr. Möge ich verdammt sein mit einem Knüppel um meinen Hals, wenn ich lüge!";
			link.l1 = "Ha-ha-ha, gut. Aber sag mir - wer glaubst du hat es schlimmer gehabt? Du, der Befehlen folgte? Oder ich, der nicht gezwungen wurde zu tun, was ich tat?";
			link.l1.go = "Nemezida_Knippel_16";
		break;
		
		case "Nemezida_Knippel_16":
            dialog.text = "Ich weiß es nicht, Herr...";
			link.l1 = "Ich auch nicht. Aber das spielt keine Rolle. Was zählt, ist, dass ich nichts mehr mit Terrax zu tun haben will. Genug ist genug. Kein Charlie Prince mehr. Nur noch Charles de Maure.";
			link.l1.go = "Nemezida_Knippel_17";
		break;
		
		case "Nemezida_Knippel_17":
            dialog.text = "Aber war das nicht Teil Ihres Plans, um Ihren Bruder zu retten?";
			link.l1 = "Es war so. Aber am Ende hat es mir überhaupt nicht geholfen. Also wenn ich jemals wieder so etwas tun muss - es wird nur meine Entscheidung sein. Und nur, wenn es mich wirklich meinem Ziel näher bringt.";
			link.l1.go = "Nemezida_Knippel_18";
		break;
		
		case "Nemezida_Knippel_18":
            dialog.text = "Ich hoffe, Sie wissen, was Sie tun, Kapitän. Und dass Sie nicht wie Terrax enden. Oder am Galgen.";
			link.l1 = "Ich hoffe es auch. Aber was ich sicher weiß, ist, dass meine Ziele und Interessen von nun an an erster Stelle stehen werden. Jetzt kümmern wir uns um deine Wunden.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Лонгвэй
		case "Nemezida_Longway_1":
            dialog.text = "Ihre Explosion hat Aufmerksamkeit erregt, Herr Kapitän. Eine feindliche Gruppe scheint sich uns zu nähern.";
			link.l1 = "Verdammt! ...Glaubst du, es gab einen besseren Weg, mit diesen Bäumen umzugehen? Und was hättest du getan?";
			link.l1.go = "Nemezida_Longway_2";
		break;
		
		case "Nemezida_Longway_2":
            dialog.text = "Ich weiß es nicht. Aber ich weiß jetzt, was zu tun ist - mit diesen Leuten umzugehen.";
			link.l1 = "Nun, fair genug. Ich nehme an, das ist genau das, was wir tun werden.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Longway_3":
            dialog.text = "Neue Leute kommen, Herr Kapitän.";
			link.l1 = "Ja, das habe ich bemerkt, danke, Longway. Aber wir haben keine Zeit für diese, also lasst uns uns in den Dschungel zurückziehen - vielleicht verlieren sie uns.";
			link.l1.go = "Nemezida_Longway_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_4":
            dialog.text = "Hmm, wir könnten sie natürlich bewältigen, aber wie du sagst.";
			link.l1 = "Wir brauchen diesen Kampf nicht, also lasst uns weiterziehen.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Longway_5":
            dialog.text = "Sie werden nicht nachlassen und uns fangen, Herr Kapitän! Ich habe es Ihnen gesagt, wir hätten sie früher töten sollen. Sollen wir in dieser Höhle einen Hinterhalt legen? Obwohl es scheint, dass dort bereits jemand ist.";
			link.l1 = "Besser hier mit den Jungs einen Hinterhalt legen! Was ich nicht verpassen werde, ist dieser Schatz. Sieht so aus, als hätte jemand anderes Wind von dem Hort bekommen... Also werde ich selbst nachsehen gehen.";
			link.l1.go = "Nemezida_Longway_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Longway_6":
            dialog.text = "Sei vorsichtig, Herr Kapitän. Erinnere dich daran, dass selbst ein großer Drache einmal auf einem Berg aus Gold gestorben ist.";
			link.l1 = "Ich werde das im Hinterkopf behalten, Longway. Lassen wir uns alle heute nicht sterben.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Longway_7": // на берегу
            dialog.text = "Herr Kapitän, es scheint, Sie haben es geschafft, von dort zu entkommen.";
			link.l1 = "Überrascht, Longway? Obwohl ich zugeben muss, ich bin selbst etwas überrascht. Sieht so aus, als wärst du der Einzige, der lebend herausgekommen ist. Aber wie hast du das geschafft?";
			link.l1.go = "Nemezida_Longway_8";
		break;
		
		case "Nemezida_Longway_8":
            dialog.text = "Eine Schar von struppigen Katzen kann keinen Tiger besiegen. Ein Nest von Schlangen kann keinen Drachen zu Fall bringen. Unter den Weißen sind nur wenige meiner würdigen Gegner.";
			link.l1 = "Aber denke daran, Longway, ein Rudel Hunde kann einen Löwen zerreißen.";
			link.l1.go = "Nemezida_Longway_9";
		break;
		
		case "Nemezida_Longway_9":
            dialog.text = "Nun teilt der Herr Kapitän seine Weisheit mit Longway? Schade, dass Sie meinen Rat nicht früher beherzigt haben.";
			link.l1 = "Über den Drachen auf dem Berg aus Gold? Wahr, ich wurde fast einer - bin fast gestorben, tatsächlich. Aber nicht auf einem Berg aus Gold - davon gab es nichts. Was ich stattdessen fand, war etwas anderes, genauso wichtig.";
			link.l1.go = "Nemezida_Longway_10";
		break;
		
		case "Nemezida_Longway_10":
            dialog.text = "Nächstes Mal könnte 'fast' nicht passieren. Was haben Sie gefunden, Herr Kapitän?";
			link.l1 = "Ja, das sehe ich jetzt. Was ich gefunden habe, war... Weisheit. Erfahrung. Verständnis. Eine Entscheidung. Sag mir, Longway, was haben wir in letzter Zeit getan?";
			link.l1.go = "Nemezida_Longway_11";
		break;
		
		case "Nemezida_Longway_11":
            dialog.text = "Wir seien Piraten. Arbeiten für euren neuen Herrn, Lord Terrax. Schmuggeln, Städte plündern, töten, retten und seinem Volk helfen.";
			link.l1 = "Er ist nicht mein Meister, wissen Sie. Aber verdammt noch mal, Sie haben das alles so perfekt beschrieben! Ich vergaß Stolz, Selbstachtung und folgte ihm herum wie ein Schoßhund.";
			link.l1.go = "Nemezida_Longway_12";
		break;
		
		case "Nemezida_Longway_12":
            dialog.text = "Longway versteht Euch, Herr Kapitän. Ich habe auch für van Merden und Rodenburg gearbeitet, Ehre, Stolz und Respekt vergessen um eines geliebten Ziels willen.";
			link.l1 = "Sag mir, verurteilst du dich selbst dafür? Hasst du dich selbst?";
			link.l1.go = "Nemezida_Longway_13";
		break;
		
		case "Nemezida_Longway_13":
            dialog.text = "Verdammen? Manchmal. Hassen? Nein. Ich weiß und erinnere mich, wer ich bin. Ich erinnere mich an mein Ziel, meinen Leitstern. Nichts ist wichtiger im Leben. Und hast du ein Ziel?";
			link.l1 = "Nicht ein leitender Stern wie du, aber dennoch ein wichtiges Ziel, ja - meinen Bruder zu retten. Aber ich bin von diesem Ziel abgekommen. Und das ist etwas, was ich mir nicht leisten kann zu wiederholen.";
			link.l1.go = "Nemezida_Longway_14";
		break;
		
		case "Nemezida_Longway_14":
            dialog.text = "Lass mich ein weiteres Stück Weisheit aus dem Himmlischen Reich mit dir teilen. Es gibt keine vollkommen guten oder schlechten Menschen. Jeder Mensch besitzt sowohl Yin - Dunkelheit und Unwissenheit - als auch Yang - Licht und Weisheit. Die Balance verschiebt sich in jedem von uns.";
			link.l1 = "Also, mein Yang ist Charles de Maure. Und mein Yin ist Charlie Prince. Obwohl vielleicht sogar Charles de Maure eines Tages dunkle und schwierige Entscheidungen treffen muss.";
			link.l1.go = "Nemezida_Longway_15";
		break;
		
		case "Nemezida_Longway_15":
            dialog.text = "Das ist das Leben, Herr Kapitän. Jeder Mensch ist dazu bestimmt, sowohl dunkle als auch helle Entscheidungen zu treffen.";
			link.l1 = "Und dennoch ist die Maske des Prinzen fast mit mir verschmolzen. Aber ich werde sie ablegen. Charles de Mort ist ein Adliger, kein Laufbursche. Von nun an wird es nur noch so sein. Ich beanspruche meinen Stolz und meine Würde zurück. Von nun an bin ich mein eigener Herr.";
			link.l1.go = "Nemezida_Longway_16";
		break;
		
		case "Nemezida_Longway_16":
            dialog.text = "Longway billigt Ihre Entscheidung, Lord Kapitän.";
			link.l1 = "Danke dir, Longway. Sag mal, bereust du es nicht, kein freier Kapitän zu sein? Mir zu dienen, wie du sagst, 'deinem Meister'?";
			link.l1.go = "Nemezida_Longway_17";
		break;
		
		case "Nemezida_Longway_17":
            dialog.text = "Hm-m. Longway vermisst es, sein eigenes Schiff zu befehlen. Aber meins erkennt das deine. Für den Respekt und die Weisheit, die du meinem zeigst, anders als der typische weiße Barbar. Vielleicht hätte meins ein anderes Leben gewollt. Aber meins bereut es nicht, dir geholfen zu haben.";
			link.l1 = "Ich freue mich, das zu hören, Longway. Jetzt... verlassen wir diesen Ort und den Pfad des Yin. Und bringen mehr Yang in unser Leben. Habe ich das richtig verstanden?";
			link.l1.go = "Nemezida_Longway_18";
		break;
		
		case "Nemezida_Longway_18":
            dialog.text = "Ja, das ist korrekt. Ich hoffe, dass du von nun an einen viel besseren Dao verfolgst.";
			link.l1 = "Dao?";
			link.l1.go = "Nemezida_Longway_19";
		break;
		
		case "Nemezida_Longway_19":
            dialog.text = "Der Weg, Herr Kapitän. Oder das Wesen. Aber in unserem Fall - der Weg.";
			link.l1 = "Was auch immer mein zukünftiger Weg bereithalten mag, ich werde mich nicht wieder von dem abwenden, was wirklich zählt. Lass uns diesen Ort verlassen, Longway.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Тичингиту
		case "Nemezida_Tichingitu_1":
            dialog.text = "Kapitän Charles, viele Leute kommen diesen Weg. Dein Rauchsignal hat sie angelockt. Und sie sind eindeutig keine Freunde von uns.";
			link.l1 = "Ach, wenn es nur ein 'Rauchsignal' wäre, wie du es genannt hast - es hallte durch den gesamten Dschungel. Es gibt keine Wahl - wir müssen uns verteidigen. Ein Angriff von hinten durch eine ganze Truppe brauchen wir definitiv nicht.";
			link.l1.go = "Nemezida_Tichingitu_2";
		break;
		
		case "Nemezida_Tichingitu_2":
            dialog.text = "Ja, Kapitän Charles. Schlage zuerst zu!";
			link.l1 = "Angriff! Schont die Kugeln nicht!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Tichingitu_3":
            dialog.text = "Noch mehr kommen! Noch mehr Leute.";
			link.l1 = "Zieh dich in den Dschungel zurück, Tichingitu! Wir werden uns verstecken und abwarten. Ich bin hierher gekommen, um Schätze zu suchen, nicht um zu kämpfen!";
			link.l1.go = "Nemezida_Tichingitu_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_4":
            dialog.text = "Wenn nötig, können wir einen Hinterhalt im Dschungel aufstellen.";
			link.l1 = "Wohl wahr. Nun, lasst uns gehen - schnell, aber leise.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Tichingitu_5":
            dialog.text = "Kapitän Charles, schau! Dort vorne ist ein Durchgang. Und ich kann Schritte und Stimmen von dort hören.";
			link.l1 = "Jemand anderes hat von dem Schatz erfahren? Verdammt! Hörst du auch dieses Geräusch hinter uns? Sieht so aus, als hätten sie uns eingeholt. Tichingitu! Ich gehe nachsehen, was vor uns liegt. Halte sie mit den Jungs auf!";
			link.l1.go = "Nemezida_Tichingitu_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Tichingitu_6":
            dialog.text = "Wir versuchen es! Du gehst!";
			link.l1 = "Ich zähle auf dich!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
			
		case "Nemezida_Tichingitu_7": // на берегу
            dialog.text = "Kapitän Charles! Du überlebst! Tichingitu freut sich darüber.";
			link.l1 = "Danke dir, mein Freund. Ich bin auch froh. Ich bin froh, dass ich überlebt habe und dass es dir gut geht. Sieht so aus, als wärst du der Einzige, der von der ganzen Truppe übrig geblieben ist. Waren es viele? Du hast sie wirklich gut abgewehrt.";
			link.l1.go = "Nemezida_Tichingitu_8";
		break;
		
		case "Nemezida_Tichingitu_8":
            dialog.text = "Viele. Aber meiner ist einer der besten Krieger aus unserem Maskog-Dorf. Was ist dir dort passiert? Hast du den Schatz gefunden, den du gesucht hast?";
			link.l1 = "Nein, Tichingitu. Wir wurden getäuscht - es gab keinen Schatz. Sag mir, was hältst du von dem, was wir alle in letzter Zeit getan haben?";
			link.l1.go = "Nemezida_Tichingitu_9";
		break;
		
		case "Nemezida_Tichingitu_9":
            dialog.text = "Was haben wir gemacht, Kapitän Charles? Segeln. Besiege deine Feinde.";
			link.l1 = "Es scheint, du verstehst mich nicht. Sag mir dann, bist du traurig, aus deinem Stamm verbannt zu sein? Willst du zurückkehren, vermisst du deine Brüder?";
			link.l1.go = "Nemezida_Tichingitu_10";
		break;
		
		case "Nemezida_Tichingitu_10":
            dialog.text = "Natürlich vermisse ich meine Freunde und Familie. Aber zurückkehren? Meine Heimat existiert nicht mehr ohne... sie. Außerdem gibt es diesen bösen Kojoten, den Schamanen!";
			link.l1 = "Es tut mir leid, ich wollte das nicht ansprechen. Weißt du, ich bin kürzlich einem Stamm beigetreten, sozusagen. Ein Stamm von Kapitänen wie mir. Aber am Ende habe ich festgestellt, dass es nur ein Rudel Schakale war, die sich für Seewölfe hielten...";
			link.l1.go = "Nemezida_Tichingitu_11";
		break;
		
		case "Nemezida_Tichingitu_11":
            dialog.text = "Und was passiert? Was machen wir jetzt?";
			link.l1 = "Gute Frage. Ich wäre fast selbst ein Schakal bei diesen Schakalen geworden. Also, das reicht mir. Meine Freunde und meine Mannschaft - das ist mein 'Stamm'.";
			link.l1.go = "Nemezida_Tichingitu_12";
		break;
		
		case "Nemezida_Tichingitu_12":
            dialog.text = "Tichingitu freut sich, dass Sie Ihren Stamm gefunden haben, Kapitän Charles.";
			link.l1 = "Danke, mein Freund. Das musste ich sagen. Du und ich, wir sind beide unsere eigenen Anführer und Stamm. Und jetzt ist es an der Zeit, sich wieder wirklich wichtigen Angelegenheiten zu widmen.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Айронс
		case "Nemezida_Irons_1":
            dialog.text = "Jemand kommt! Und nach dem Klang zu urteilen, nicht um mit uns Thanksgiving zu feiern.";
			link.l1 = "Verdammt Wurzeln! Gut, wir müssen uns jetzt mit diesen Schurken auseinandersetzen - besser jetzt als wenn wir den Schatz zum Schiff schleppen.";
			link.l1.go = "Nemezida_Irons_2";
		break;
		
		case "Nemezida_Irons_2":
            dialog.text = "Du hast recht. Bereit?";
			link.l1 = "Du musstest nicht fragen. Es ist nicht so, als hätten wir eine Wahl.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Irons_3":
            dialog.text = "Sie sind überall, wie Ratten in den Londoner Slums, Euer Ehren! Was ist der Plan - sollten wir unsere Position halten und uns mit den Jungs duellieren?";
			link.l1 = "Nicht jetzt, zurückfallen! Wir sind hier für den Schatz, nicht zum Kämpfen!";
			link.l1.go = "Nemezida_Irons_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_4":
            dialog.text = "Heh, keine Einwände hier.";
			link.l1 = "Dann mach schneller!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Irons_5":
            dialog.text = "He, Kapitän, schau mal - es scheint, als führe dieser Weg irgendwohin. Und dort drüben muss es ziemlich lebhaft zugehen, wenn man nach dem Lärm urteilt!";
			link.l1 = "Könnte es sein, dass jemand anderes Wind von dem Schatz bekommen hat? Tommy, hörst du das? Sie haben uns eingeholt. Also gut, ich gehe vor und ihr alle heißt sie hier ordentlich willkommen!";
			link.l1.go = "Nemezida_Irons_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Irons_6":
            dialog.text = "Jetzt höre ich es! Wer auch immer sie sind, du solltest dich besser beeilen, he-he. Sonst, welchen Sinn hatte es, dass wir hierher gekommen sind?!";
			link.l1 = "Oh, ich würde es hassen, wenn das der Fall wäre.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		case "Nemezida_Irons_7": // на берегу
            dialog.text = "Ach, du bist es, Kapitän! Wow, du hast überlebt. Ich werde nicht lügen - ich habe es nicht erwartet. Aber ich bin froh, versteh mich nicht falsch, heh-heh.";
			link.l1 = "Ich habe es auch nicht erwartet, ich werde auch nicht lügen. Aber die Tatsache, dass du überlebt hast - ich bin überhaupt nicht überrascht. Bist du weggelaufen?";
			link.l1.go = "Nemezida_Irons_8";
		break;
		
		case "Nemezida_Irons_8":
            dialog.text = "Du tust mir Unrecht! Tommy Irons rennt nie weg! Er holt nur Verstärkung. Aber es war nicht nötig - meine Jungs und ich haben es alleine geschafft, obwohl, schon wieder, ich der Einzige bin, der lebend rausgekommen ist, heh...";
			link.l1 = "Vielleicht hättest du diesmal Verstärkung holen sollen. Aber ich... ich bin weggelaufen.";
			link.l1.go = "Nemezida_Irons_9";
		break;
		
		case "Nemezida_Irons_9":
            dialog.text = "Du bist weggelaufen? Heh, du hast mich schon wieder überrascht. Aber ich wollte eigentlich zu dir eilen, sobald ich fertig war! Ich bin besser als jede Verstärkung, weißt du. Es ist nur so, dass...";
			link.l1 = "Was ist los, Tom?";
			link.l1.go = "Nemezida_Irons_10";
		break;
		
		case "Nemezida_Irons_10":
            dialog.text = "Verdammt, während ich herumgetrieben habe, wurde der Eingang hinter dir mit Steinen blockiert. Ich konnte nicht durchkommen. Es ist sogar peinlich, dass ich so lange gebraucht habe, um es zu räumen und dir dort nicht helfen konnte. Ich habe mich ein wenig verlaufen, als ich zurückging, um die Jungs zu holen und die Steine zu bewegen... Als ich zurückkam, warst du schon wieder da.";
			link.l1 = "Ja, vielleicht werde ich mich schämen zuzugeben, was mir heute passiert ist.";
			link.l1.go = "Nemezida_Irons_11";
		break;
		
		case "Nemezida_Irons_11":
            dialog.text = "Und was ist passiert? Hab keine Angst, erzähl mir. Aber wenn es etwas Lustiges ist, werde ich lachen, nur dass du es weißt. Wie sollte es sonst sein? Ein Freund bietet seine Schulter an und stößt dich lachend mit seinem Ellbogen an.";
			link.l1 = "Nun, du weißt sicher, wie man tröstet. Sag mir, Tommy. Du hast gesagt, dass du das Piratentum magst. Warst du froh, dass du es mit mir wieder aufgenommen hast?";
			link.l1.go = "Nemezida_Irons_12";
		break;
		
		case "Nemezida_Irons_12":
            dialog.text = "Ich sage es mal so. Ob ich nun ein Pirat bin oder nicht, was ich schon immer verdammt geliebt habe, ist Abenteuer! Ich sehe, meine Antwort befriedigt dich nicht. Diese Dinge, die großen Angelegenheiten, sind nicht mein Ding.";
			link.l1 = "Es ist nicht so, dass es mich nicht zufriedenstellt. Aber das wollte ich nicht besprechen. Du weißt... Ich habe erkannt, dass ich mit Tiraqs völlig von meinen Zielen abgekommen bin. Außerdem... Charlie Prince war irgendein Lakai, kein tapferer Piratenkapitän, verstehst du, Tom? Das reicht mir.";
			link.l1.go = "Nemezida_Irons_13";
		break;
		
		case "Nemezida_Irons_13":
            dialog.text = "Ich verstehe. Deshalb war ich überrascht, dass du Terrax so die Kontrolle über dich lassen hast. Es schien nicht einmal so, als wärst du du.";
			link.l1 = "Vielleicht war ich damals wirklich Charlie Prince. Aber ob wir zur Piraterie zurückkehren oder nicht, das entscheide ich! Und nur, wenn es wirklich meinen Interessen dient und mich meinem Ziel näher bringt!";
			link.l1.go = "Nemezida_Irons_14";
		break;
		
		case "Nemezida_Irons_14":
            dialog.text = "Das ist mehr so, wie ich es mir vorgestellt habe! Aber ich möchte sagen, ob es Charlie Prince oder Charles de Maure ist - du bist es immer noch. Mit dir war es immer verdammt interessant!";
			link.l1 = "Froh das zu hören, Tommy.";
			link.l1.go = "Nemezida_Irons_15";
		break;
		
		case "Nemezida_Irons_15":
            dialog.text = "Denke daran, fast niemand wird helfen außer dir selbst. Es ist besser, das zu tun, was du liebst, auch alleine, als andere für dich entscheiden zu lassen!";
			link.l1 = "Wahr. Genau das habe ich bei Terrax empfunden. Selbst wenn ich wieder jemandem folgen sollte, wird es nur unter würdigen Bedingungen sein, nicht wie ein verdammter Laufbursche!";
			link.l1.go = "Nemezida_Irons_16";
		break;
		
		case "Nemezida_Irons_16":
            dialog.text = "Du hast recht! Jetzt lasst uns von hier verschwinden - meine Beine sind schon wackelig.";
			link.l1 = "He, das wollte ich gerade sagen, ha-ha. Aber du hast recht, lass uns gehen. Wir haben noch viel wichtige Arbeit vor uns, Tom. Nicht diese Art von Zeug.";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;
		
		// Алонсо
		case "Nemezida_Alonso_1":
            dialog.text = "Kapitän, es sieht so aus, als hätten wir Gesellschaft! Wir sind hier nicht allein.";
			link.l1 = "Genau das, was wir brauchten... Na gut, lass uns jetzt mit ihnen fertig werden. Später werden sie nur noch mehr Ärger machen.";
			link.l1.go = "Nemezida_Alonso_2";
		break;
		
		case "Nemezida_Alonso_2":
            dialog.text = "Ja, Kapitän.";
			link.l1 = "Bereit machen!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;
		
		case "Nemezida_Alonso_3":
            dialog.text = "Es werden immer mehr von ihnen!";
			link.l1 = "Dann hat es keinen Sinn, das weiter zu verfolgen! Rückzug! Wir lassen sie zurück und steuern direkt auf den Schatz zu!";
			link.l1.go = "Nemezida_Alonso_4";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_4":
            dialog.text = "Ja, Kapitän!";
			link.l1 = "Beweg dich, beweg dich!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;
		
		case "Nemezida_Alonso_5":
            dialog.text = "Kapitän, es sieht so aus, als gäbe es hier einen Eingang! Und jemand ist bereits drinnen.";
			link.l1 = "Hört gut zu - wir wurden verfolgt. Ich gehe hinein und sieh nach, während ihr diesen Ort haltet. Deckt mich, Jungs!";
			link.l1.go = "Nemezida_Alonso_6";
			PlaySound("interface\abordage_wining.wav");
		break;
		
		case "Nemezida_Alonso_6":
            dialog.text = "Aye, Kapitän!";
			link.l1 = "Haltet stand. Viel Glück für dich - für uns alle!";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Du bist "+GetSexPhrase("ein Dieb, wie ich sehe! Wachen, ergreift ihn","ein Dieb, wie ich sehe! Wachen, ergreift sie")+"!!!","Ich kann es nicht glauben! Ich habe mich für eine Sekunde abgewendet - und du durchwühlst meine Sachen! Haltet den Dieb!!!","Wachen! Raub! Stoppt den Dieb!!!");
			link.l1 = "Aaaah, Teufel!!!";
			link.l1.go = "fight";
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук
		
		// <-- legendary edition
	}
}
