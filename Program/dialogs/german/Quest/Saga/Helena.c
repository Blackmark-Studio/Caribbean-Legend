// Элен МакАртур - сомнительная любовь и офицер
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Was ist los?";
			link.l1 = "Nein, es ist nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "After_boarding":
			dialog.text = "Danke für Ihre Hilfe, Kapitän!";
			link.l1 = "Mein Gott... Du bist sogar noch schöner als ich mir vorgestellt habe!";
			link.l1.go = "After_boarding_1";
		break;
		
		case "After_boarding_1":
			dialog.text = "Zum Teufel mit meiner Schönheit! Weißt du, wie viel Kummer sie mir bereitet hat? Ich würde mir meine eigene Nase abschneiden, wenn es meinen Ruf nicht zerstören würde. Dieser Bastard ließ mich nicht lebend die Korvette verlassen, behauptete immer, ich 'wüsste zu viel'. Dann sagte er mir gestern, dass er es leid sei zu warten und mich gegen meinen Willen nehmen würde\nDu hättest zu keinem besseren Zeitpunkt ankommen können! Aber wo sind meine Manieren, mein Name ist Helen McArthur. Mein Papa hat mich Rumba genannt, weil ich ständig das feine Porzellan, das er 'erworben' hatte, versehentlich zerbrach, deshalb nennt mich meine Crew jetzt so.";
			link.l1 = "Mein Name ist "+GetFullName(pchar)+" und ich bin hier, um dich zu retten. Ich habe die Karibik seit einigen Tagen durchkämmt, auf der Suche nach dir um der Miss Gladys willen.";
			link.l1.go = "After_boarding_2";
		break;
		
		case "After_boarding_2":
			dialog.text = "Miss Gladys!? Wie geht es ihr?";
			link.l1 = "Sie ist krank vor Sorge um dich. Aber du wirst sie bald sehen, wir segeln nach Blueweld. Du kannst mir alles erzählen, was dir auf dem Weg dorthin passiert ist.";
			link.l1.go = "After_boarding_3";
		break;
		
		case "After_boarding_3":
			dialog.text = "Um ehrlich zu sein, "+pchar.name+", Ich hätte jetzt gerne etwas zu essen und ein Nickerchen. Ich bin erschöpft nach all den Tagen, die ich auf dem Schiff dieses Monsters verbracht habe...";
			link.l1 = "Natürlich, Miss McArthur. Ich werde den Steward beauftragen, Ihnen eine Mahlzeit zu servieren und ein Bett für Sie in Ihren eigenen privaten Quartieren vorzubereiten.";
			link.l1.go = "After_boarding_4";
		break;
		
		case "After_boarding_4":
			DialogExit();
			LAi_SetActorType(npchar);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			npchar.greeting = "helena_2";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.Saga = "returntoblueveld";
			Island_SetReloadEnableGlobal("Antigua", true);//на остров можно
			bQuestDisableMapEnter = false;//открыть карту
			AddQuestRecord("Saga", "11");
			pchar.quest.Saga_returnBlueveld.win_condition.l1 = "location";
			pchar.quest.Saga_returnBlueveld.win_condition.l1.location = "Santacatalina_town";
			pchar.quest.Saga_returnBlueveld.function = "Saga_returnBlueveld";
			SetFunctionTimerCondition("Helena_ReturnOver", 0, 0, 45, false);
			sld = characterFromId("gladis");
			sld.greeting = "gladis_3";
		break;
		
		case "Return_blueveld":
			pchar.quest.Helena_ReturnOver.over = "yes";
			dialog.text = "Kapitän de Maure, ich danke Ihnen nochmals von ganzem Herzen für Ihre rechtzeitige Rettung. Sie müssen mich und meine Mutter besuchen. Unser Haus ist nicht weit von hier, auf Ihrer linken Seite, wenn Sie vom Pier kommen. Und denken Sie dran "+pchar.name+", Ich werde es euch nie vergeben, wenn Ihr absegelst, ohne Auf Wiedersehen zu sagen!";
			link.l1 = "Das Vergnügen war ganz meinerseits, Miss McArthur. Ich werde sicherlich auf Sie zurückkommen!";
			link.l1.go = "Return_blueveld_1";
		break;
		
		case "Return_blueveld_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseSp3", "SantaCatalina_houseSp3_bedroom", "goto", "goto1", "OpenTheDoors", -1);
			AddQuestRecord("Saga", "13");
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", false); // открыть кабинет Свенсона
			pchar.questTemp.Saga = "svenson";//идем к Свенсону
			sld = characterFromId("JS_girl");
			sld.dialog.currentnode = "js_girl";
			npchar.dialog.currentnode = "Helena_wait";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_regard";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			// закрыть город до беседы с Глэдис
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);
		break;
		
		case "Helena_wait":
			dialog.text = "Ach, da sind Sie ja, Kapitän de Maure! Ich bin so froh, dass Sie hier sind, ich habe viele Fragen an Sie.";
			link.l1 = "Es tut mir leid, Miss McArthur, aber wir müssen unser Gespräch ein wenig verschieben. Ich brauche noch einige Informationen, bevor ich zufriedenstellende Antworten liefern kann. Im Moment bitte ich Sie, sich nicht auf der Straße zu zeigen. Ich hoffe, dass Ihr Warten nicht lange dauern wird. Vertrauen Sie mir und warten Sie.";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CanDrink")) {
				link.l1.go = "drinking_refuse";
				link.l2 = "Du hast selbst gesagt, dass du mir nicht vergeben würdest, wenn ich nicht vorbeikommen würde.";
				link.l2.go = "drinking_accept";
				
				DeleteQuestCondition("HelenDrinking_NoVisit");
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CanDrink");
			} else {
				link.l1.go = "exit";
				NextDiag.TempNode = "Helena_wait";
			}
		break;
		
		case "Helena_hire":
			dialog.text = "Ach, da bist du ja, mein Kapitän! Deine Augen verraten mir, dass du Neuigkeiten für mich hast!";
			link.l1 = "Kapitän Svenson hat mir erzählt, dass Sie mit mir segeln wollen. Ich schätze Ihren Wunsch, zudem hat Miss Gladys erwähnt, dass Sie das Meer vermisst haben. Willkommen an Bord, Miss Helen McArthur!";
			link.l1.go = "Helena_hire_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend"))
			{
				link.l2 = "Kapitän Svenson hat mir gesagt, dass Sie mit mir segeln wollen. Ich schätze Ihren Wunsch, außerdem hat Miss Gladys erwähnt, dass Sie das Meer vermisst haben. Willkommen in meiner Mannschaft, Miss Helen Sharp!";
				link.l2.go = "Helena_hire_2";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 2;
			}
		break;
		
		case "Helena_hire_1":
			DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
			dialog.text = "Aye aye, Kapitän! Es tut mir leid, dies sagen zu müssen, aber ich kann für mich selbst einstehen und ich werde es nicht dulden, dass Männer sich Freiheiten nehmen. Ich bin nicht verantwortlich für abgetrennte Hände oder ausgestochene Augen.";
			link.l1 = "Mach dir keine Sorgen, auf meinem Schiff herrscht unerschütterliche Disziplin. Ich muss dich allerdings etwas fragen...";
			link.l1.go = "Helena_hire_1_1";
		break;
		
		case "Helena_hire_1_1":
			dialog.text = "...Ja?";
			link.l1 = "Jan Svenson und ich haben herausgefunden, dass du die rechtmäßige Erbin von Isla Tesoro bist. Ja, es ist wahr, schüttle nicht deinen Kopf! Ich habe die Hälfte der Karte, die deine Rechte beweist. Es wird nicht einfach sein, aber Jan und ich werden unser Bestes tun, um dir zu helfen, der rechtmäßige Eigentümer zu werden.";
			link.l1.go = "Helena_hire_1_2";
		break;
		
		case "Helena_hire_1_2":
			dialog.text = ""+pchar.name+", meinst du das ernst? Es ist nicht nett, ein armes Mädchen so zu necken! Wie kann ich das Recht auf Besitz einer ganzen Insel haben?!";
			link.l1 = "Ich meine es absolut ernst, Miss McArthur. Und ich werde dir helfen, dein Geburtsrecht zu bekommen. Lass uns jetzt segeln!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_2":
			dialog.text = "W-was hast du gesagt? Helen Sharp? Warum Sharp?";
			link.l1 = "Helen, du bist die Tochter von Beatrice Sharp und die einzige Erbin der Sharp-Dynastie. Dies ist die Hälfte der Karte, die Miss Gladys all die Jahre aufbewahrt hat. Es ist der Beweis für deine Rechte an Isla Tesoro. Es wird nicht einfach sein, aber ich und Jan Svenson werden unser Bestes tun, um dir zu helfen, die Insel deines Großvaters zu erben.";
			link.l1.go = "Helena_hire_3";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
			notification("Helen approves", "Helena");
			npchar.lastname = "Sharp";
		break;
		
		case "Helena_hire_3":
			dialog.text = "Oh... Meine arme Mutter! Ich wünschte, ich könnte eines Tages ihr Grab finden und dort für ihre Seele beten. Aber... warte! Unmöglich!";
			link.l1 = "Was ist los, Miss Sharp?";
			link.l1.go = "Helena_hire_4";
		break;
		
		case "Helena_hire_4":
			dialog.text = "Die Prophezeiung der Zigeunerfrau ist gerade in Erfüllung gegangen... Ich verstehe es jetzt endlich.";
			link.l1 = "Eh? Welche Prophezeiung?";
			link.l1.go = "Helena_hire_5";
		break;
		
		case "Helena_hire_5":
			dialog.text = ""+pchar.name+", Du kannst mich für naiv halten, aber ich werde es dir trotzdem erzählen. Als ich ein junges Mädchen war, sagte mir eine Zigeunerin: 'Dein Schicksal wird in den Händen des Mannes liegen, der die Münze der Witwe nicht nimmt, der das Gold des toten Mannes zurückgibt und der die Mutter nennt'\nIch dachte damals, dass das alles Unsinn war, aber irgendwie hast du es geschafft, jeden Teil der Prophezeiung zu erfüllen, es gibt keine Möglichkeit, dass du davon wüsstest!";
			link.l1 = "Dein Schicksal, sagst du... Nun, vielleicht hast du recht. Ich werde dich nicht enttäuschen. Wir werden zusammen das Grab deiner Mutter suchen. Und jetzt... Miss Helen Sharp! Machen Sie sich bereit zur Abfahrt und kommen Sie nicht zu spät!";
			link.l1.go = "Helena_hire_6";
		break;
		
		case "Helena_hire_6":
			dialog.text = "Aye-aye, Kapitän!";
			link.l1 = "...";
			link.l1.go = "Helena_hire_add";
		break;
		
		case "Helena_hire_add":
			LAi_SetImmortal(npchar, false);
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_HireHelena", -1);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.Saga = "svenson_wait";
			AddQuestRecord("Saga", "24");
			AddQuestUserData("Saga", "sTimer", AddDaysToDateString(367));
			if(bImCasual) NewGameTip("Erkundungsmodus: Der Timer ist nicht deaktiviert. Halte die Frist ein!");
			SetFunctionTimerCondition("Saga_BaronsQuestsGo", 0, 0, 2, false);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			
			if (pchar.questTemp.HelenDrinking.Result != "no_visit") {
				AddQuestRecord("HelenDrinking", "3");
				
				SetFunctionLocationCondition("HelenDrinking_IslaTesoroAmbush", "Pirates_town", false);
				sld = &locations[FindLocation("Pirates_town")];
				sld.locators_radius.quest.detector1 = 4.0;
			}
		break;
		
		//-->  консультации по морским сражениям в искушении барбазона
		case "sea_bomb":
			dialog.text = "Kapitän "+pchar.name+"! Ich habe eine Idee...";
			link.l1 = ""+npchar.name+"? Es ist hier nicht sicher und ich habe dir gesagt, du sollst auf dem Schiff bleiben...";
			link.l1.go = "sea_bomb_1";
		break;
		
		case "sea_bomb_1":
			dialog.text = "Charles, in diesem alten Kasten ist so viel Schießpulver gestopft, dass wenn es hochgeht, die ganze Insel direkt nach St. Peters Haustür fliegen wird! Es macht keinen Unterschied, ob du mir sagst, mich zu verstecken oder nicht, also hör mir zu!";
			link.l1 = "Gut, rede schnell!";
			link.l1.go = "sea_bomb_2";
		break;
		
		case "sea_bomb_2":
			dialog.text = "Die Korvette und die Fregatte. Sie erkennen das Schiff von Knive nicht als feindlich. Wir können ihre Selbstgefälligkeit gegen sie verwenden. Lassen Sie uns ein paar Fässer Schießpulver nehmen, eine Lunte setzen und zu den Schiffen segeln. \nSie lassen uns nahe kommen, wir zünden die Lunte an, lassen das Fass zu einem von ihnen fallen und segeln so schnell wie möglich davon. Und dann schauen wir uns eine spektakuläre Explosion an... Was sagst du?";
			link.l1 = "Ein improvisiertes Feuerschiff... sehr schlau! Dein Plan ist verrückt genug, dass er vielleicht funktionieren könnte... wenn wir nah genug herankommen können, ohne erkannt zu werden.";
			link.l1.go = "sea_bomb_3";
		break;
		
		case "sea_bomb_3":
			dialog.text = "Was haben wir zu verlieren "+pchar.name+"? Es wird nicht leicht sein, gegen zwei Schiffe gleichzeitig zu kämpfen, aber wir werden die Chance bekommen, die Chancen auszugleichen...";
			link.l1 = "Gut. Lasst uns damit anfangen! Jungs! Nehmt drei Fässer Schießpulver! Wir werden hier verdammt noch mal rauskommen! Ich liebe deine Vorstellungskraft, "+npchar.name+"... Ich wäre nie selbst auf diese Idee gekommen.";
			link.l1.go = "sea_bomb_4";
		break;
		
		case "sea_bomb_4":
			chrDisableReloadToLocation = false;
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Bomb = "true";
			pchar.questTemp.Saga.BarbTemptation.adviser = "Helena";
		break;
		
		case "fugas":
			dialog.text = "Aye Kapitän, was ist los?";
			link.l1 = "Jackmans Schiff befindet sich in der Sabo-Matila-Bucht, die schwere Fregatte 'Centurion'. Dieses Schiff war einst Eigentum der Hawks, daher müssen sich wichtige Gegenstände und Dokumente in Jackmans Kabine befinden...wir müssen es entern.";
			link.l1.go = "fugas_1";
		break;
		
		case "fugas_1":
			dialog.text = "Leichter gesagt als getan. Wie willst du das auf unserer Polacre machen? Sie übermannen und übertrumpfen uns.";
			link.l1 = "Du hast recht. Jackman hat mindestens doppelt so viele Männer wie wir, und alle sind erfahrene Fechter. Es wäre Wahnsinn, sie ohne vorheriges Bombardement anzugreifen. Aber auch ein langwieriger Kampf ist nicht die beste Option. Also habe ich darüber nachgedacht, was zu tun ist.";
			link.l1.go = "fugas_2";
		break;
		
		case "fugas_2":
			dialog.text = ""+pchar.name+", sie haben uns noch nicht als Feind erkannt, genau wie diese Idioten zurück bei Turks... Wir können unseren Trick noch einmal versuchen...";
			link.l1 = "Helen, ich habe dir gerade gesagt, dass wir die Fregatte entern und durchsuchen müssen, sie in die Luft zu sprengen ist keine Option.";
			link.l1.go = "fugas_3";
		break;
		
		case "fugas_3":
			dialog.text = "Warte eine Minute, "+pchar.name+", wir werden sie nicht versenken. Lass uns eine List einfallen.  Hört zu, wir werden ein paar leere Rumfässer nehmen und sie mit Schießpulver, Traubenschuss und kurzen Zündschnüren füllen. Dann werden wir näher an ihre Fregatte segeln und die improvisierten Sprengstoffe auf ihr Deck werfen.";
			link.l1 = "Ha! Deine feminine Genialität hört nicht auf, mich zu überraschen! Anstatt eines Feuerschiffs schlägst du eine Fougasse vor? Du denkst, es könnte funktionieren?";
			link.l1.go = "fugas_4";
		break;
		
		case "fugas_4":
			dialog.text = "Und warum nicht? Ihr Freibord ist höher als unseres, aber zwei oder drei Männer könnten mit Hilfe einer Rolle ein voll beladenes Fass leicht hochheben und werfen. Wir rufen aus - 'Hier ist etwas freier Rum von Knive! Und die Fässer werden explodieren, bevor sie überhaupt reagieren können";
			link.l1 = "Die explodierende Kartätschenkugeln wird seine besten Männer an Deck in Hackfleisch verwandeln... Verdammt, das klingt verlockend.";
			link.l1.go = "fugas_5";
		break;
		
		case "fugas_5":
			dialog.text = "Lassen wir gleich fünf Fässer vom Achterdeck bis zum Achtersteven werfen. "+pchar.name+", wir haben das Überraschungselement. Sie werden noch nichts vermuten! Und dann werden wir sofort von ihnen wegschippern, bevor sie die Chance haben, uns zu entern.";
			link.l1 = "Nun, lasst es uns versuchen. Sie dürfen uns nicht identifizieren, bevor wir diese explosiven Fässer auf ihr Deck bekommen... Es wird nicht einfach sein, näher zu kommen. Jackman ist nicht so ein großer Narr wie Ghoul es war.";
			link.l1.go = "fugas_6";
		break;
		
		case "fugas_6":
			dialog.text = "Lass es uns riskieren, "+pchar.name+"! Wie ich schon sagte, was haben wir zu verlieren?";
			link.l1 = "Guter Punkt... Auf die Plätze, Jungs! Bereitet die Fougassen vor und macht euch bereit zu kämpfen!";
			link.l1.go = "fugas_7";
		break;
		
		case "fugas_7":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			pchar.questTemp.Saga.BarbTemptation.Fugas = "true";
			AddQuestRecord("BarbTemptation", "21");
			DeleteAttribute(npchar, "quest.fugas");
		break;
		//<--  консультации по морским сражениям
		
	// --> разговор по итогам Саги
		case "result":
			//if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) // не друзья
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 11) {
				Achievment_Set("ach_CL_83");
			}
			
			if (sti(pchar.questTemp.Saga.HelenRelation) < 6)
			{
				dialog.text = "Nun, mein lieber Kapitän... Es ist Zeit für uns, uns voneinander zu verabschieden. Mein Dienst ist vorbei und es ist Zeit, sich an das Leben als Piratenkönigin von Isla Tesoro zu gewöhnen. Ich hoffe, dass ich ein würdiger Nachfolger meines Onkels sein werde. Danke für deine Hilfe.";
				link.l1 = "Aye, es ist ein Jammer, sich von dir zu trennen, aber so sind die Launen des Schicksals. Du hast jetzt viel wichtigere Verantwortlichkeiten als auf meinem Schiff zu dienen.";
				link.l1.go = "result_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Mary")) {
					dialog.text = "Ich würde liebend gerne auf deinem Schiff bleiben. Nah bei dir... Aber es ist unmöglich. Sei glücklich, Charles. Und sie sollte deiner würdig sein!";
					link.l1 = "Es tut mir leid, Helen.";
					link.l1.go = "result_mary";
				} else {
					dialog.text = "Es ist so seltsam, "+pchar.name+"! Ich bin gerade Besitzerin einer ganzen Insel geworden, aber ich fühle mich nicht als Königin von Isla Tesoro... Ich vermute, dass ein neuer Anführer der Bruderschaft die Kolonie besser verwalten würde als ich. Ich habe noch viel zu lernen.";
					link.l1 = "Mach dir keine Sorgen, Helen, du bist eine Frau, die auf sich selbst aufpassen kann - genau wie du mir gesagt hast, als du das erste Mal an Bord gekommen bist.";
					link.l1.go = "result_9";
				}
			}
			
			DeleteQuestCondition("HelenDrinking_AtSHDN");
			DeleteQuestCondition("HelenDrinking_InBlueweldAfterCave");
		break;
		
		case "result_mary":
			dialog.text = "Nun, wir werden immer noch Freunde sein, nicht wahr?";
			link.l1 = "Natürlich... Helen, wir werden uns wieder auf der Isla Tesoro treffen. Soll ich dich zu deiner Insel bringen?";
			link.l1.go = "result_12";
		break;
		
		case "result_1":
			dialog.text = "Du hast recht... Schau, ich habe meinen Anteil an der Beute gespart, während ich auf deinem Schiff segelte. Nimm es und versuche nicht einmal, mein Angebot abzulehnen - ich möchte nicht in deiner Schuld stehen.";
			link.l1 = "He, warte jetzt mal einen Moment...";
			link.l1.go = "result_2";
		break;
		
		case "result_2":
			dialog.text = "Ich weiß, was du sagen wirst. Sicher, deine Hilfe war viel bedeutender als diese mickrige Schatztruhe. Aber das ist alles, was ich gerade besitze und ich muss dir etwas zurückgeben. Nimm es, wenn du es nicht selbst nimmst, werde ich es in deiner Kajüte lassen.";
			link.l1 = "Wirst du jetzt alleine segeln? Vielleicht könnte ich dich zur Isla Tesoro bringen?";
			link.l1.go = "result_3";
		break;
		
		case "result_3":
			GiveItem2Character(pchar, "chest");
			Log_Info("Du hast eine Truhe mit Dublonen erhalten");
			PlaySound("interface\important_item.wav");
			dialog.text = "Keine Notwendigkeit dafür, "+pchar.name+". Ich werde selbst zur Insel gelangen. Ich habe mein Schwert und meine Pistole bei mir, das wird für eine Weile ausreichen... Ich bin sicher, dass die Königin von Isla Tesoro sich keine Sorgen um Einkommen machen muss, sobald ich dort bin.";
			link.l1 = "Aye aye, Eure Majestät. Ich wünsche Ihnen Glück in Ihrem neuen Leben.";
			if (!CheckAttribute(pchar, "questTemp.Saga.Beltrop_die")) link.l1.go = "result_4";
			else link.l1.go = "result_7";
		break;
		
		case "result_4":
			dialog.text = "Genug damit, auch im Scherz. Ich bin immer noch Helen für dich. Aber das ist nicht alles, was ich sagen wollte. Ich habe meinen Vater wieder gefunden, wenn auch etwas seltsam. Er hat mit seinem guten Namen eines englischen Edelmanns für mein Erbe bezahlt und das stört mich. Das englische Commonwealth jagt ihn und ich möchte nicht, dass du, "+pchar.name+", daran teilnimmst.";
			link.l1 = "Komm zur Besinnung, Helen! Er ist ein Bandit und ein Pirat!";
			link.l1.go = "result_5";
		break;
		
		case "result_5":
			dialog.text = "Pirat? Und wer zum Teufel bist du, um so etwas zu sagen? Er ist mein Vater und das ist es, was für mich zählt! Und ich, die Tochter eines Banditen und eines Piraten, scheißt darauf, was die englische Justiz von ihm hält. Wenn du versuchst, meinem Vater in irgendeiner Weise zu schaden, werde ich alles Gute vergessen, was du für mich getan hast, das solltest du wissen. Betrachte dies als Warnung.";
			link.l1 = "So ist das also? Eigentlich, Mädchen, solltest du etwas höflicher sein. Ich habe keine Beschwerden von dir über meine piratische Haltung gehört, als ich deine hübsche Haut vor den Händen dieses Vergewaltigers Donovan rettete, oder als wir die Gewinne unserer Eroberungen teilten!";
			link.l1.go = "result_6";
		break;
		
		case "result_6":
			dialog.text = "Es.....Es tut mir leid. Ich nehme es zurück, vergib mir. Ich habe den Kopf verloren... Aber trotzdem, ich möchte dein Freund bleiben, was unmöglich wäre, wenn du anfängst, meinem Vater nachzujagen.";
			link.l1 = "Verstanden. Aber wage es nicht, mich zu bedrohen, Miss. Du solltest jetzt wissen, nachdem du auf meinem Schiff gesegelt bist, dass ich vor niemandem und nichts Angst habe. Besonders werde ich keinen Respektlosigkeit von einer Frau tolerieren - ob Piratenkönigin oder nicht. Ich mag ein Gentleman sein, aber auch meine Geduld hat ihre Grenzen. Jetzt ist das geklärt, auf Wiedersehen. Ich wünsche dir viel Glück.";
			link.l1.go = "result_8";
		break;
		
		case "result_7":
			dialog.text = "Danke.... Vielleicht treffen wir uns wieder, "+pchar.name+"...";
			link.l1 = "Und warum nicht? Ich werde Isla Tesoro in Zukunft mehr als einmal besuchen. Wir sehen uns dort... Auf Wiedersehen, Helen.";
			link.l1.go = "result_8";
		break;
		
		case "result_8": // Элен уходит, но её не затираем
			DialogExit();
			RemovePassenger(pchar, npchar);
			//chrDisableReloadToLocation = true;//закрыть локацию  // уже не надо.
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto24", "", "", "", "", 7);//OpenTheDoors лесник . чтобы бежала и исчезла а не стояла.
			AddQuestRecord("Testament", "11");
			CloseQuestHeader("Testament");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться		
			if (CheckAttribute(pchar, "questTemp.LSC.MaryWait")) {
				pchar.questTemp.LSC.Mary = "return";
			}
		break;
		
		case "result_9": // вот тут - ключевой момент, если игрок нашёл Мэри - выбирай, какая девушка милее
			dialog.text = "Ich bin mir sicher. "+pchar.name+", Ich würde gerne auf dein Schiff bleiben, wenn du mich lässt. Bei dir bleiben...";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				link.l1 = "(wähle Mary) Du verstehst nicht, Helen. Deine ganze Zukunft liegt vor dir und du musst dir keine Sorgen machen. Alles, was ich vor mir habe, ist Krieg, politische Intrigen und totale Ungewissheit. Du musst dir ein eigenes Leben arrangieren, es ist kein Platz für einen solchen wilden Vagabund wie mich darin.";
				link.l1.go = "result_10";
				link.l2 = "(wähle Helen) Es ist mehr, als ich hoffen könnte, Helen. Natürlich möchte ich dich nicht verlieren, aber es wäre besser für dich, nach Isla Tesoro zu gehen. Wer weiß, wohin mein Schicksal mich noch führen wird. Im Moment habe ich Krieg, politische Intrigen und Unsicherheit vor mir.";
				link.l2.go = "result_15";
			}
			else
			{
				link.l1 = "Es ist mehr, als ich hoffen könnte, Helen. Natürlich möchte ich dich nicht verlieren, aber es wäre besser für dich, nach Isla Tesoro zu gehen. Wer weiß, wohin mein Schicksal mich noch führen wird. Im Moment habe ich Krieg, politische Intrigen und Unsicherheit vor mir.";
				link.l1.go = "result_15";
			}
		break;
		
		case "result_10":
			dialog.text = ""+pchar.name+"! Lüge mich nicht an. Du willst einfach nicht... Sag mir, wer ist sie? Ist es diese rothaarige Dirne aus der Stadt der verlassenen Schiffe, habe ich recht?";
			link.l1 = "Helen! Ich versuche dir zu sagen, was ich für das Beste für dich halte! Wie kannst du das nicht verstehen?!";
			link.l1.go = "result_11";
		break;
		
		case "result_11":
			dialog.text = "Ach sicher, natürlich tust du das... Und wie konnte sie dich verzaubern, hm? Was hat sie, was *ich* nicht habe?! Ist sie wirklich so gut? Eh, "+pchar.name+"... Nun, es ist deine Entscheidung, mir bleibt nichts anderes übrig, als zu meiner Insel zu gehen. Ich kann nicht zwischen euch beiden stehen\nDanke für alles, was du für mich getan hast, Charles. Du bist der beste Mann, den ich je getroffen habe. Ich hoffe, wir können Freunde bleiben?";
			link.l1 = "Natürlich... Helen, ich werde dich wieder auf Isla Tesoro sehen. Soll ich dich dorthin bringen?";
			link.l1.go = "result_12";
		break;
		
		case "result_12":
			dialog.text = "Keine Notwendigkeit. Ich werde ein neues Schiff kaufen. Ich habe genug Geld gesammelt, um eine Schoner zu kaufen und auszustatten, während ich unter deinem Kommando diente. Ich werde wieder auf einer neuen 'Rainbow' segeln.";
			link.l1 = "Ich bin froh, Helen, dass du so... sparsam warst. Aber auf einer Schoner zu segeln passt nicht zur Piratenkönigin von Isla Tesoro. Bald solltest du dir eine Fregatte zulegen.";
			link.l1.go = "result_13";
		break;
		
		case "result_13":
			dialog.text = "Vielleicht, "+pchar.name+". Gut. Ich gehe zur Werft, aber zuerst... gib mir einen Abschiedskuss... Bitte...?";
			link.l1 = "Helen...";
			link.l1.go = "result_14";
		break;
		
		case "result_14": // прощальный поцелуй
			DialogExit();
			SetMusic("music_romantic");
			SetLaunchFrameFormParam("", "", 0, 12);
			SetLaunchFrameFormPic("loading\inside\kiss.tga");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); //крутим время
			RecalculateJumpTable();
			DoQuestCheckDelay("Saga_HelenaBye", 0.5);
			pchar.questTemp.LSC.Mary = "return"; // к Мэри
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.
			InterfaceStates.Buttons.Save.enable = true;//можно сохраняться
		break;
		
		case "result_15":
			dialog.text = "Mein Schicksal ist dein Schicksal seit wir uns getroffen haben. Verstehst du das nicht? "+pchar.name+"? Ich werde dir bis ans Ende der Welt folgen!";
			link.l1 = "Und was ist mit deinem Vater? Laurence Beltrope? Er ist mein Feind...";
			link.l1.go = "result_16";
		break;
		
		case "result_16":
			dialog.text = "Mein Vater ist Sean McArthur. Ich liebte ihn und betrauerte seinen Tod. Er war mein einziger Vater. Und dieser Pirat... Ich will nicht einmal über ihn sprechen.";
			link.l1 = "Helen... Meine liebe Helen!";
			link.l1.go = "result_17";
		break;
		
		case "result_17":
			dialog.text = ""+pchar.name+", Ich wollte dir schon immer sagen, dass du der größte Mann bist, den ich je getroffen habe! Du hast so viel für mich getan, dass ich es dir nie zurückzahlen kann. Ich möchte für immer bei dir bleiben. Ich werde dich heiraten, wenn du willst... Ich liebe dich.";
			link.l1 = "Wir werden zusammen sein. Ich verspreche es!"; // а куда же ты теперь денешься :)
			if (!CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) {
				link.l1.go = "result_17A";
			} else {
				link.l1.go = "result_18";
			}
		break;
		
		case "result_17A":
			dialog.text = "Versprichst du mir, dass du jetzt etwas für mich tun wirst? Und bitte lach nicht!";
			link.l1 = "Ich verspreche es, meine Liebe!";
			link.l1.go = "result_17A_1";
		break;
		
		case "result_17A_1":
			dialog.text = "Nenne mich bei meinem echten Namen. Bitte!";
			link.l1 = "Ich liebe dich, Helen Sharp.";
			link.l1.go = "result_18";
		break;
		
		case "result_18":
			dialog.text = ""+pchar.name+", Liebster... Umarme mich! Ich habe viel zu lange auf diesen Moment gewartet!";
			link.l1 = "Helen, meine Liebe...";
			link.l1.go = "result_19";
		break;
		
		case "result_19": // романтик-сцена
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			StartQuestMovie(true, true, true);
			PlayStereoOGG("music_romantic");
			InterfaceStates.Buttons.Save.enable = false;//запретить сохраняться
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.01, 0.0, 2.0, 0.0, 580);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("Saga_HelenaRomantic", 20.0);
			pchar.GenQuest.MusicContinue = true;
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			DeleteAttribute(pchar, "questTemp.LSC.MaryWait");
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", false); // лесник . пирс. 
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", false); // ворота.																					   
			
			pchar.quest.HelenUpgradeShip.win_condition.l1 = "Timer";
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.day = GetAddingDataDay(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 180);
			pchar.quest.HelenUpgradeShip.win_condition.l2 = "location";
			pchar.quest.HelenUpgradeShip.win_condition.l2.location = "PortRoyal_town";
			pchar.quest.HelenUpgradeShip.function = "HelenUpgradeShip";
			
			// Квест Лонгвея "Путеводная звезда", начало 5 этапа
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap5_Start") && !CheckAttribute(pchar, "questTemp.PZ_ProvalFinal"))
			{
				PChar.quest.PZ_Etap5_Start.win_condition.l1 = "location";
				PChar.quest.PZ_Etap5_Start.win_condition.l1.location = "Pirates_town";
				PChar.quest.PZ_Etap5_Start.win_condition = "PZ_Etap5_Start";
				AddMapQuestMarkCity("Pirates", false);
			}
		break;
		
		case "happy":
			dialog.text = ""+pchar.name+"! Das war... unglaublich! Ich will nirgendwo anders hin... Lass uns hier bis zum Morgen bleiben. Die Welt kann warten!";
			link.l1 = "Wir lassen es warten, Helen!";
			link.l1.go = "happy_1";
		break;
		
		case "happy_1":
			DialogExit();
			LSC_MaryLoveWaitTime();
			SetLaunchFrameFormParam("Am nächsten Morgen...", "", 0, 4);
			LaunchFrameForm();
			DoQuestCheckDelay("Saga_HelenaRomantic_5", 4.0);
			pchar.questTemp.Saga.Helena_officer = "true"; // показатель, что Элен - наша навсегда
			
			pchar.GenQuest.BrothelCount = 0;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
			
			// Запуск квеста Дороже золота
			SetFunctionTimerCondition("GoldenGirl_Start", 0, 0, 1, false);
		break;
		
	// -------------------------------------------- провалы саги ------------------------------------
		case "failcenturion":
			dialog.text = "Kapitän! Jackman ist tot... Ist meine Familie endlich sicher?";
			link.l1 = "Ja, Helen, ihr seid alle sicher. Aber die 'Centurion' wurde versenkt und damit auch alle Dokumente, die uns helfen könnten, das Grab deiner Mutter zu finden und deine Rechte auf Isla Tesoro zu beweisen... Eh... Jetzt werde ich Tortuga alleine stürmen müssen...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = ""+pchar.name+", mach dir keine Sorgen. Es gibt nichts, was wir dagegen tun können. Mach dir auch keine Sorgen um mich, ich werde ohne diese Insel gut leben können. Danke für alles, was du für mich getan hast!";
			link.l1 = "Es klingt, als ob du vorhast... mich zu verlassen, nicht wahr?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "Ja, mein Kapitän. Ich konnte genug Geld sammeln, um eine Schoner zu kaufen und auszurüsten. Ich werde wieder auf meiner 'Rainbow' segeln. Wir werden uns wieder in Blueweld treffen... Ich gehe nach Hause zurück.";
			link.l1 = "Nun... viel Glück, Helen!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) // patch-6
			{
				pchar.questTemp.LSC.Mary = "return"; // к Мэри
			}
		break;
		
		case "late_l1":
			dialog.text = "Nun, mein Kapitän... Es scheint, dass wir gescheitert sind. Lebewohl. Ich gehe zurück nach Hause. Unter deinem Kommando habe ich genug Geld verdient, um mir eine neue Schoner zu kaufen. Wir werden uns wieder auf See treffen!";
			link.l1 = "Viel Glück, Helen. Es tut mir leid für alles. Auf Wiedersehen.";
			link.l1.go = "failcenturion_3";
		break;
		
		case "late_l2":
			dialog.text = "Kapitän! Jackman ist tot... Es scheint also, dass meine Familie sicher ist, nicht wahr?";
			link.l1 = "Ja, Helen, es ist sicher. Aber ich bin nicht glücklich, ich habe zu viel Zeit verloren und Isla Tesoro ist jetzt eine englische Kolonie. Du wurdest ohne dein Erbe gelassen, also muss ich selbst Tortuga stürmen...";
			link.l1.go = "failcenturion_1";
		break;
		
		case "late_l3":
			dialog.text = ""+pchar.name+", was hat der Anwalt dir gesagt?";
			link.l1 = "Ich habe zu viel Zeit verloren und Isla Tesoro ist jetzt eine englische Kolonie. Du wurdest ohne dein Erbe zurückgelassen, also muss ich Tortuga selbst stürmen... Leider haben wir verloren.";
			link.l1.go = "failcenturion_1";
		break;
	// <-- провалы Саги
		
		// секс - Элен соглашается не всегда (голова болит, а что вы хотели? :)) и сама не требует секса
		case "cabin_sex":
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Nein, Liebling, das wird nicht funktionieren.";
				link.l1 = "Nun, warum nicht?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (hrand(4) == 0)// вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", mir geht es heute nicht gut. Fühl dich bitte nicht schlecht, es ist nicht deine Schuld. Lass uns das heute nicht tun...",""+pchar.name+", Liebling, ich war die letzten Tage so müde. Um ehrlich zu sein, möchte ich nur schlafen. Verzeih mir. Lass uns ein anderes Mal machen.");
				link.l1 = RandPhraseSimple("Fein...","Das ist in Ordnung. Wie du wünschst...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", die Stimmung ist genau richtig, los geht's!",""+pchar.name+", sicher, keine Frage! Los geht's!");
				link.l1 = RandPhraseSimple("Das ist mein Mädchen...","Du bist so lieblich, Helen...");
				link.l1.go = "exit";
				AddDialogExitQuest("cabin_sex_go");
			}
		break;
		
		case "sex_after":
			dialog.text = LinkRandPhrase(RandPhraseSimple("Es war wunderbar, "+pchar.name+"!..","Du warst wie immer großartig, Liebster..."),RandPhraseSimple("Es war großartig, Charles!","Hatte eine wunderbare Zeit, Liebling!"),RandPhraseSimple("Mit dir wird es nie langweilig, mein Kapitän!","Du warst wunderbar, Liebling!"));
			link.l1 = RandPhraseSimple("Ich liebe dich...","Es ist immer schön, bei dir zu sein, Helen...");
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_officer";
			chrDisableReloadToLocation = false;//открыть локаци.
		break;
		
		case "room_sex":
			if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "tavern")
			{
				dialog.text = ""+pchar.name+", du weißt, ich bin immer froh zu... Aber jetzt ist nicht der richtige Zeitpunkt - wir müssen diesen Schurken Thibaut fangen, bevor er entkommt.";
				link.l1 = "Du hast wie immer recht, Helen...";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Nein, Liebling, das wird nicht funktionieren.";
				link.l1 = "Nun, warum nicht?!";
				link.l1.go = "refuse";
				break;
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			if (hrand(4) == 0) // вероятность отказа 20%
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", Ich fühle mich heute nicht gut. Bitte nimm es nicht persönlich. Lass es uns heute nicht tun...",""+pchar.name+", Liebste, ich bin in den letzten Tagen so müde gewesen. Um ehrlich zu sein, möchte ich nur schlafen. Verzeih mir. Lass uns das ein anderes Mal machen.");
				link.l1 = RandPhraseSimple("Fein...","Das ist in Ordnung. Wie du wünschst...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple(""+pchar.name+", Ich liebe dich! Los geht's!",""+pchar.name+", aye aye Kapitän! Auf geht's!");
				link.l1 = RandPhraseSimple("Du bist mein braves Mädchen...","Du bist wunderschön, Helen...");
				link.l1.go = "room_sex_go";
			}
		break;
		
		case "room_sex_go":
			DialogExit();
			chrDisableReloadToLocation = true;
			//npchar.quest.daily_sex_room = true; // для первого раза в таверне чтобы счетчик запустить . лесник
			//npchar.quest.daily_sex_cabin = true;
			if (sti(pchar.money) >= 10) AddMoneyToCharacter(pchar, -10);
			sld = CharacterFromID("Helena");
			ChangeCharacterAddressGroup(sld, loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest3");
			DoFunctionReloadToLocation(loadedLocation.fastreload + "_tavern_upstairs", "quest", "quest4", "GiveKissInRoom");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Helena_officer":
			ref rLoc = &Locations[FindLocation(pchar.location)];
			dialog.text = LinkRandPhrase("Ja, "+pchar.name+"?","Ja, mein Kapitän?","Ich höre zu, "+pchar.name+"...");
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.CutlassTraining");
				dialog.text = "Schau dir das mal an, mein Kapitän!";
				link.l1 = "Wow, was für ein Griff! Ich sehe, du hast keine Zeit verschwendet, Helen.";
				link.l1.go = "cutlass_training";
				NextDiag.TempNode = "Helena_officer";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && sti(pchar.GenQuest.BrothelCount) > 0 && !CheckAttribute(npchar, "quest.refusesex")) {
				dialog.text = "Liebling, über deine Besuche bei Prostituierten.";
				npchar.quest.refusesex = true;
				link.l1 = "Was? Helen, du hast alles falsch verstanden! Ich habe nur...";
				link.l1.go = "brothel_found";
				NextDiag.TempNode = "Helena_officer";
				SetFunctionTimerCondition("Helena_ClearRefuseSex", 0, 0, 180, false);
				DeleteQuestCondition("Helen_GiveSex");
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "Helen, ich werde die verlorene indische Stadt Tayasal besuchen. Ich werde dir nicht lügen: Diese Reise ist sehr gefährlich und beinhaltet sogar Teleportation durch das Idol. Wirst du... mir folgen?";
				Link.l4.go = "tieyasal";
			}
       ////////////////////////казначей///////////////////////////////////////////////////////////
           		// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "Helen, gib mir einen vollständigen Schiffsbericht.";
			    Link.l11.go = "QMASTER_1";
			        
			    // Warship. Автозакупка товара
				Link.l12 = "Ich möchte, dass du bestimmte Waren kaufst, jedes Mal wenn wir angedockt sind.";
				Link.l12.go = "QMASTER_2";
			}
			
            /////////////////////////////////////казначей////////////////////////////////////////////////////////////     			
			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "Ich bin auf Ihren Befehl angekommen, Kapitän.";
				Link.l2 = "Helen, ich muss dir mehrere Befehle geben.";
				Link.l2.go = "Companion_Tasks";
				
				sld = GetCharacter(sti(npchar.RealCompanionIdx));
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Rainbow") && sld.ship.type == pchar.questTemp.HelenDrinking.Rainbow && CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
					DeleteAttribute(link, "");
					dialog.text = "Glaubst du, das ist lustig?";
					link.l1 = "Schönes Schiff, nicht wahr? Hab es für dich geholt, Helen! Stell dir vor, was für ein Kerl in der Karibik seiner Dame ein echtes Schiff schenkt, hm?";
					link.l1.go = "rainbow";
					
					NextDiag.TempNode = "Helena_officer";
					break;
				}
				
				NextDiag.TempNode = "Helena_officer";// не забыть менять в зависисомости от оффа
				break;
			}																															
			if (CheckAttribute(npchar, "quest.fugas"))
			{
				Link.l3 = "Helen, ich brauche deinen Rat.";
				Link.l3.go = "fugas";
			}
			Link.l1 = "Helen, ich habe einen Auftrag für dich...";
            Link.l1.go = "stay_follow";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && pchar.location == Get_My_Cabin() && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Helen, lass uns ein paar Stunden alleine in der Kabine bleiben... Was denkst du?","Liebling, verbringen wir die nächsten Stunden Tete-a-Tete? Gefällt dir diese Idee?");
				Link.l2.go = "cabin_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "tavern" && sti(pchar.money) >= 10 && GetNpcQuestPastDayWOInit(npchar, "sex_date") >= 1) // mitrokosta - очередные исправления интима
			{
				Link.l2 = RandPhraseSimple("Helen, warum mieten wir nicht ein Zimmer und bleiben dort für die nächsten Stunden privat... Wie findest du das?","Liebling, wollen wir die nächsten Stunden tête-à-tête verbringen? Wir mieten ein Zimmer... was denkst du?");
				Link.l2.go = "room_sex";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && rLoc.type == "town" && sti(pchar.money) >= 1000 && GetNpcQuestPastDayWOInit(npchar, "special_sex_date") >= 30 && !CheckAttribute(npchar, "quest.refusesex"))
			{
				Link.l2 = "Helen, Liebste, darf ich dich einladen, einige schöne Stunden in der Taverne zu verbringen?";
				Link.l2.go = "special_sex";
			}
			if (CheckAttribute(pchar, "questTemp.MysteryPortRoyal_Helena")) {
				link.l4 = "Helen, ich glaube, ich habe das letzte Vermächtnis deines Verehrers Francis gefunden. Er hat dir sein Erbe hinterlassen.";
				link.l4.go = "MysteryPortRoyal_Helena_1";
			}
			if (CheckCharacterItem(pchar, "pirate_cutlass") && !CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) {
				link.l4 = "Ich glaube, dieser Entermesser gehört jetzt dir. Blaise ist dein sogenannter Onkel...";
				link.l4.go = "give_cutlass";
			}
			link.l9 = "Im Moment nichts, Helen.";
			NPChar.id = "Helena"; // лесник . Идентификация Элен на всяк. случай . если потеряет сознание.
			link.l9.go = "exit";
			NextDiag.TempNode = "Helena_officer";
		break;
		
		/////////////////////////// ответы для казнаячея - Элен ..(элен казначей - ужас!))///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "Charles, Liebling, bist du krank oder so? Was, du erwartest von mir, dass ich unter Deck gehe, den Laderaum fegen und Ratten zählen anfange?";
			Link.l1 = "Stimmt, entschuldige Liebling, mein Fehler...";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "Und ich will mein ganz eigenes Linienschiff, mit hundert Kanonen, die mit 20 Knoten fliegen. Ich war mein ganzes Leben lang ein Kapitän wie du. Geh und hol dir einen verdammten Zahlmeister und belästige ihn damit.";
			link.l1 = "Aye, du hast recht, Helen. Entschuldigung dafür.";
			link.l1.go = "exit";
		break;
		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "Ich bin ganz Ohr.";
			Link.l1 = "Über unsere Strategie der Enterung...";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "Über das Schiff, das du kommandierst...";
			Link.l2.go = "Companion_TaskChange";
			Link.l8 = "Bisher nichts.";
			Link.l8.go = "exit";
			 
		break;
		
		case "Companion_TaskBoarding":
			dialog.Text = "Was ist Ihr Wunsch, mein Kapitän?";
			Link.l1 = "Ich möchte nicht, dass du irgendwas entert. Halte dich und deine Männer sicher.";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "Ich will, dass du bei der ersten Gelegenheit feindliche Schiffe entert.";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;
		
		case "Companion_TaskChange":
			dialog.Text = "Ja, mein Kapitän?";
			Link.l1 = "Ich würde es schätzen, wenn ihr nach dem Entern keine Schiffe mehr tauscht. Sie ist mir zu wertvoll.";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "Wenn du zufällig beim Entern bist, sieh dir das Prachtschiff gut an. Wenn es gut ist, nimm es ruhig für dich.";
			Link.l2.go = "Companion_TaskChangeYes";
		break;
		
		case "Companion_TaskBoardingNo":
			dialog.Text = "Gut, ich werde darüber nachdenken.";
			Link.l1 = "Sie wird darüber nachdenken... Richtig, als ob ich ihr sowieso Befehle geben könnte.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;
		
		case "Companion_TaskBoardingYes":
			dialog.Text = "Gut, ich werde darüber nachdenken.";
			Link.l1 = "Sie wird darüber nachdenken... Richtig, als könnte ich ihr sowieso Befehle erteilen.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;
		
		case "Companion_TaskChangeNo":
			dialog.Text = "Gut, ich werde darüber nachdenken.";
			Link.l1 = "Sie wird darüber nachdenken... Richtig, als ob ich ihr Befehle geben könnte.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;
		
		case "Companion_TaskChangeYes":
			dialog.Text = "Gut, ich werde darüber nachdenken.";
			Link.l1 = "Sie wird darüber nachdenken... Richtig, als könnte ich ihr sowieso Befehle geben.";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========//////////////////////////////////////																																			  
		
		case "stay_follow":
            dialog.Text = "Befehle?";
            Link.l1 = "Steh hier!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "Folgt mir und haltet Schritt!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "Ändere die Munitionsart für deine Feuerwaffen.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "Wähle die Art der Munition:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetConvertStr(rItem.name, "ItemsDescribe.txt")+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "Sofort, Kapitän!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "Sofort, Kapitän!";
            Link.l1 = "...";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
		// --> суп из черепахи
		case "terrapin_grot":
			dialog.text = "Da bist du ja! Ich habe dich endlich gefunden... Das war was, mein Kapitän! So einen Dachlauf und einen Sprung aus solch atemberaubender Höhe habe ich noch nie gesehen! Mein Herz war kurz davor zu explodieren! Eines Tages wirst du mich mit diesen Tricks von dir umbringen, Liebster... Oh, du bist nicht allein... Wer ist dieses Mädchen?";
			link.l1 = "Das ist Catherine Fox, die Tochter von Oberst Fox, dem Kommandanten des berühmten englischen Seefußregiments, den 'Sea Foxes'. Wir bringen sie nach Antigua.";
			link.l1.go = "terrapin_grot_1";
		break;
		
		case "terrapin_grot_1":
			dialog.text = "So ist das also ...Willkommen an Bord, Miss Fox! Nein nein, haltet nicht Kapitän de Maures Arm, ihr könnt ganz gut alleine gehen! Und jetzt lasst uns zum Langboot kommen - wir müssen hier weg."; 
			link.l1 = "Ha! Danke dir, Helen! Was würde ich ohne dich tun? Catherine, folge uns!";
			link.l1.go = "terrapin_grot_2";
		break;
		
		case "terrapin_grot_2":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			Terrapin_GotoShip();
		break;
		// <-- суп из черепахи
		
		// --> калеуче
		case "on_coast":
			dialog.text = "Endlich bist du aufgewacht, Liebling! Wie fühlst du dich? Du hast mich zu Tode erschreckt...";
			link.l1 = "Helen, was ist passiert? Mein Kopf spaltet sich...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "Als wir die Kapitänskabine betraten, lagst du noch auf dem Boden. Mein Herz hörte fast auf zu schlagen! Die Jungs hoben dich auf und schleppten dich zurück zu unserem Schiff - gerade rechtzeitig, da die toten Männer auf dem Deck begannen, wieder aufzustehen. \nWas für ein Horror! Es ist fast genug, um mich Gott finden zu lassen! Sie waren völlig unempfindlich gegen unsere Klingen und Kugeln! Wir schnitten schnell die Seile durch und versuchten wegzusegeln, aber eine Salve von ihrem Schiff beschädigte unser Schiff schwer und wir verloren die Kontrolle. Dann setzten sie die Segel und waren im Nu verschwunden. \nUnser Schiff lief auf Grund, also mussten wir fliehen zu diesem Ufer, bevor der Sturm es zerstören konnte. Viele gute Leute starben heute, aber das Schiff überlebte am Ende... wenn ich es nur nicht befehlen würde, es zu verlassen...";
			link.l1 = "Nicht deine Schuld, Helen. Es war die richtige Entscheidung. Was würde ich ohne dich tun?";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "Ich zog dich ins Boot und brachte dich dann an Land. Du sahst tot aus, nur dein Herz schlug sehr schwach. Schau! Meine Hände zittern immer noch";
			link.l1 = "Danke, Liebe. Ich bin dir zu Dank verpflichtet. Wie lange habe ich hier gelegen?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "Für einen ganzen Tag. Ich habe deine Wunden gewaschen und verbunden, dir Medizin gegeben und dich mit Rum abgefüllt. Jetzt musst du gesund werden!";
			link.l1 = "Ich werde diesmal nicht sterben, Liebling. Obwohl ich mich nicht gut fühle...blurgh....";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "Sag mir.... War es der echte 'Fliegende Holländer', Charles? Warum haben sie uns angegriffen? Und warum haben sie nicht auf uns geschossen, als wir uns näherten, sondern versuchten uns sofort zu versenken, nachdem sie an Bord gegangen waren?";
			link.l1 = "Ihr Kapitän benötigte dieses Amulett, über das ich mit Tuttuathapak, einem indianischen Schamanen, gesprochen hatte. Warum sie es brauchten, weiß ich nicht...aber sobald ihr Anführer das Amulett bekam, haben sie uns losgeworden...Gott Allmächtiger, was für ein elendes Alptraum! Ein Schiff, bemannt von den lebenden Toten! Unmöglich zu glauben...";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "Aye, jetzt war es an uns, den 'Fliegenden Holländer' zu begegnen. Pfui! Es lässt meine Haut kriechen! Im nächsten Hafen, den wir anlaufen, gehe ich in die Kirche, zünde eine Kerze an und bete zu unserem Herrn Jesus Christus für unsere wunderbare Rettung. Verdammt, ich fühle mich so dankbar, dass ich sogar zu einigen päpstlichen Heiligen beten werde...";
			link.l1 = "Ich werde gleich bei dir sein, Helen, ich war schon lange nicht mehr bei einer ordentlichen Beichte... Aber zuerst müssen wir in dieses Dorf zurückkehren. Ich muss Tuttuathapak alles erzählen. Dieses verfluchte Schiff hat uns wegen des Amuletts angegriffen! Ich hoffe, dieser rothäutige Teufel hat eine Idee, warum zum Teufel diese Untoten es gebraucht haben könnten.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "In Ordnung. Aber wir müssen vorsichtig sein - deine Wunden sind kaum verheilt.";
			link.l1 = "Aber du wirst mir helfen, schneller zu heilen, nicht wahr? Ich liebe dich, Helen...";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			chrDisableReloadToLocation = false;//открыть локацию
			dialog.text = "Ich liebe dich auch, mein Liebling...";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		// <-- калеуче
		
		// на Тайясаль
		case "tieyasal":
			dialog.text = ""+pchar.name+", Ich habe dir schon einmal gesagt, dass wir nun Schicksale teilen. Dein Schicksal ist mein Schicksal. Wann gehen wir?";
			link.l1 = "Ich freue mich sehr, das zu hören. Ich werde dir ein wenig später erzählen, wenn wir dorthin gehen. Wir müssen uns vorbereiten.";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "Ich bin bereit, mein Kapitän! Ich werde dir bis ans Ende der Welt folgen!";
			link.l1 = "Danke, meine Liebe...";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "20");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		// на Исла Тесоро
		case "islatesoro":
			dialog.text = "Ach, "+pchar.name+"! Bin froh dich zu sehen! Was machst du hier auf Isla Tesoro?";
			link.l1 = "Das Gleiche wie immer - Geschäfte. Wollte auch mal vorbeischauen und dich sehen. Wie geht es dir, Helen?";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			DialogExit();
			NextDiag.CurrentNode = "islatesoro";
		break;
		
		// Jason Дороже золота
		case "GoldenGirl":
			dialog.text = "Was ist mit unserem liebsten Gouverneur los, Kapitän? Wessen Arsch treten wir diesmal? Spanier, Piraten, oder jemand Schlimmeres?";
			link.l1 = "Es ist schlimmer, Helen, viel schlimmer. Der Gouverneur beabsichtigt, eine teure Kurtisane zu besuchen und ich soll ihn als Kuriosität begleiten. Er hat seiner Geliebten versprochen, einen echten Freibeuter, Abenteurer und Seehund mitzubringen. Also erwartet mich langweiliges Gerede, überteuerter Wein und fade Adlige.";
			link.l1.go = "GoldenGirl_1";
			link.l2 = "Ganz im Gegenteil, eine Einladung zu einer angenehmen gesellschaftlichen Veranstaltung, organisiert von einer Dame. Seine Exzellenz überraschte mich mit der Bitte, ihn zu begleiten, aber um ehrlich zu sein, ich bin froh, für eine Veränderung meine Gedanken von der Arbeit abzulenken.";
			link.l2.go = "GoldenGirl_5";
		break;
		
		case "GoldenGirl_1":
			dialog.text = "Aye...also wird der furchtbare Kapitän Charles de Maure sich verkleiden und wie ein Haustieraffe für ihre Unterhaltung tanzen? Wie süß! Ich habe eine bessere Idee. Lassen wir die Segel setzen und verschwinden aus diesem Höllenloch. Wenn du in Stimmung für einen lang ersehnten Urlaub bist, segeln wir nach Isla Tesoro. Dort sind wir immer willkommen. Sonnenbaden, weißer Sand, alte Freunde, Rum Punch, den Kopf freikriegen - was immer du willst.";
			link.l1 = "Schau, das klingt alles fantastisch, und ich würde gerne... aber später. Ich habe dem Gouverneur versprochen, diese Sache ist wichtig für den alten Mann und...";
			link.l1.go = "GoldenGirl_2";
		break;
		
		case "GoldenGirl_2":
			dialog.text = "Und was? Glaubst du, dein Adelsblut bedeutet ihnen einen Dreck? Ich bin vielleicht nicht französischen Blutes, aber ich kenne ihre 'hohe Gesellschaft' und für sie ist Charles de Maure nicht ein Kapitän, dem Männer folgen und ihr Leben anvertrauen. Er ist kein Gentleman wie sie. Echte Gentlemen gehen nicht zur See und kämpfen im Nebel des Schießpulverrauchs. Charles de Maure ist nur eine kuriose Zugabe zu ihrem Mahl. Wie ein Haustier Leopard oder ein Hausneger, der sich verkleidet! Ein schickes Spielzeug! Seit wann lässt du so eine Behandlung zu?!";
			link.l1 = "Helen, beruhige dich bitte. Ich bin mir sicher, dass ich ein paar unangenehme Blicke für die Zufriedenheit des Gouverneurs und unseren zukünftigen Wohlstand ertragen kann. Es ist gut, mächtige Freunde zu haben. Schließlich wird dies einfacher sein als eine Entermannschaft zu führen! Und diese 'Nichtsnutze' sind nicht immer so. Auch die hohe Gesellschaft hat würdige Leute... zumindest sollte sie das.";
			link.l1.go = "GoldenGirl_3";
		break;
		
		case "GoldenGirl_3":
			dialog.text = "Egal. (fährt sich mit der Hand durchs Haar) Aber seid gewarnt - es gibt keine Möglichkeit, dass ich mich in ein edles Kleid zwänge. Wenn ihr mich gehen lasst, trage ich meine Kniehosen. Es ist mir egal, ob alle Damen in der Karibik vor Missbilligung in Ohnmacht fallen.";
			link.l1 = "Ich hatte nicht vor, dich dazu zu bringen. Kein Grund, dass wir beide leiden. Ich werde diese Party überstehen und dann werden wir nach Isla Tesoro segeln. Als Belohnung habe ich im Laderaum eine Kiste hervorragenden spanischen Madeira aufbewahrt...";
			link.l1.go = "GoldenGirl_4";
		break;
		
		case "GoldenGirl_4":
			dialog.text = "Oh ho ho, Charles! Sagst du etwa, dass ich für eine so angesehene Gesellschaft nicht gut genug bin? Dass ein Mädchen in Hosen deinen Abend ruinieren würde? Wie interessant. Gut dann, aber vergiss nicht, dich wie ein Geck zu kleiden. Affen in schicken Kleidern können sogar das Herz einer Kurtisane berühren. Fröhliche Vorstellung!";
			link.l1 = "Helen, warte! Verdammte...Frauen!";
			link.l1.go = "GoldenGirl_8";
		break;
		
		case "GoldenGirl_5":
			dialog.text = "Ja, wir haben uns wirklich eine Ruhepause verdient. Aber verdammt noch mal, wenn ich mich in ein schickes Kleid zwänge für das. Wie weit denkst du, werden Gerüchte über deine Frau, die wie ein Mann und ein Seemann gekleidet ist, reisen?";
			link.l1 = "Ah...Ich denke nicht, dass das eine gute Idee ist. Wie soll ich das sagen...dies ist kein Ereignis, zu dem Männer ihre Ehefrauen oder respektable Damen mitbringen...";
			link.l1.go = "GoldenGirl_6";
		break;
		
		case "GoldenGirl_6":
			dialog.text = "Ha! Huren und Verdorbenheit! Einfach wunderbar - also gehst du zu einer Orgie! Warum hast du das nicht einfach verdammt nochmal gesagt? Du hast Glück, dass ich nicht irgendeine eifersüchtige Tussi bin und dich nicht gleich hier und jetzt erschieße. Zumindest nicht im Moment.";
			link.l1 = "Helen bitte, ich begleite nur unseren Gouverneur, er hat mich darum gebeten und war sehr hartnäckig dabei. Es wird keine verdammten Kurtisanen geben\nWarte, das kam falsch raus... Ich meine, es wird das verdammte von Kurtisanen geben... oh verdammt! Ich zolle nur meinen Respekt!";
			link.l1.go = "GoldenGirl_7";
		break;
		
		case "GoldenGirl_7":
			dialog.text = "Ich schlage vor, Sie kleiden sich modisch, um 'Ihre Achtung zu zollen', Kapitän de Maure. Es ist die hohe Gesellschaft und so weiter. Es ist ein reiner Skandal, dort ohne Kragen und Manschetten aufzutauchen. Selbst für eine Orgie. Viel Spaß.";
			link.l1 = "Helen, warte! Verdammt...Frauen!";
			link.l1.go = "GoldenGirl_9";
		break;
		
		case "GoldenGirl_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry1 = "true";
		break;
		
		case "GoldenGirl_9":
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlExit", 15.0);
			pchar.questTemp.GoldenGirl.Angry2 = "true";
		break;
		
		case "GoldenGirl_10":
			dialog.text = "Manschetten und ein Kragen, Kapitän. Und vielleicht eine Spitze. Ich habe gehört, sie ist wieder in Mode. Aber was weiß ich schon!";
			link.l1 = "Ach Helen, komm schon!";
			link.l1.go = "GoldenGirl_11";
		break;
		
		case "GoldenGirl_11":
			DialogExit();
			NextDiag.CurrentNode = "GoldenGirl_10";
		break;
		
		case "GoldenGirl_12":
			dialog.text = "Schau dir das an! Mein lieber Kapitän, zurück von seiner Orgie!";
			link.l1 = "...";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angry1")) link.l1.go = "GoldenGirl_13";
			else link.l1.go = "GoldenGirl_18";
		break;
		
		case "GoldenGirl_13":
			dialog.text = "Ist der örtliche Adel immer noch von seinem neuen Affen begeistert? Sie sagen, dass seine Leistung gestern Abend legendär war! Zocken um Schiffe und Dirnen, Herausforderung von hochgeborenen Prinzen zu Duellen? Kannst du bitte erklären, was zum Teufel mit dir los ist?";
			link.l1 = "Helen, lass mich erklären! Es ist nicht so einfach. Verdammt, es tut mir leid, aber ich hätte nie gedacht, dass ich die Nacht bei Madame Botot verbringen müsste. Ich habe dort nur geschlafen, ja alleine, ich schwöre es! Und ja, ich habe eine Fregatte in einem Kartenspiel gewonnen. Stell dir das vor?";
			link.l1.go = "GoldenGirl_14";
		break;
		
		case "GoldenGirl_14":
			dialog.text = "Nun denn! Du bist entweder ein großer Lügner, ein Heiliger oder ein Narr. Wir werden später über die Huren und Schiffe sprechen, die du gewonnen hast - erzähl mir jetzt alles über das Duell und warum alle tuscheln, dass du einen Kronprinzen herausgefordert hast?";
			link.l1 = "Nicht ein Kronprinz, nur ein Grafenbastard. Er ist der Sohn eines sehr einflussreichen Adligen, Graf de Levi Vantadur. Schau, ich habe es nicht angefangen! Er hat mich zuerst herausgefordert, und jetzt muss ich das Duell gewinnen, ohne ihn zu sehr zu verletzen, um den Zorn seines Vaters zu vermeiden.";
			link.l1.go = "GoldenGirl_15";
		break;
		
		case "GoldenGirl_15":
			dialog.text = "Oh, 'nur ein Grafensohn' huh? Meinst du das gerade ernst, Charles?! Und wie sollen wir das machen? Was, wenn er betrügt? Er wird dich umbringen!";
			link.l1 = "Deswegen hat Exzellenz mir noble Sekundanten zur Verfügung gestellt. Ich werde nur sie mitnehmen - wenn alles den Bach runtergeht, kann ich zumindest beweisen, dass alles nach dem Duellkodex und dem Gesetz verlaufen ist. Ich bitte dich, während meiner Abwesenheit auf die Fregatte zu achten.";
			link.l1.go = "GoldenGirl_16";
		break;
		
		case "GoldenGirl_16":
			dialog.text = "Lass uns sicherstellen, dass ich das richtig verstanden habe... Du warst einen ganzen Tag und eine Nacht weg und hast in einem Kartenspiel eine Hure und eine Fregatte gewonnen. Und jetzt stehst du kurz davor, einen edlen Hurensohn zu bekämpfen, den du nicht töten darfst, während *ich* hier einfach nur sitze und warte? Wie soll ich mich bei all dem fühlen?!";
			link.l1 = "Helen, hör zu, du hast jedes Recht, wütend auf mich zu sein und es tut mir sehr leid, aber es ist einfach...";
			link.l1.go = "GoldenGirl_17";
		break;
		
		case "GoldenGirl_17":
			dialog.text = "Weißt du was, ich habe genug von all dem. Geh einfach und mach dein Ding! Ich werde nur deine Kabine abstauben und deine schmutzige Wäsche waschen! Denk nicht einmal, dass du aus dem Schneider bist. Wir werden darüber reden, wenn das vorbei ist. Ich kümmere mich um deine neue Fregatte, großer Kapitän de Maure, mach dir keine Sorgen. Oh, und Kapitän de Maure, versuche nicht zu sterben... denn ich habe vor, dich danach selbst zu töten. Jetzt entschuldige mich, ich werde mich in meine Quartiere einschließen und eine Flasche von diesem schönen Madeira trinken, den ich in deiner Kabine gefunden habe.";
			link.l1 = "Helen, lass mich einfach erklären! Verdammt... Hier geht's schon wieder los!";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_18":
			dialog.text = "Ich habe gehört, die neueste Pariser Mode verlangt, dass Gentlemen Schiffe und Kurtisanen in Kartenspielen gewinnen, anstatt sie zu kaufen! Darüber hinaus, wenn man einen guten Eindruck von sich selbst machen will, muss er ihre früheren Besitzer zu einem Duell herausfordern. In welche Scheiße hast du dich diesmal reingeritten?!";
			link.l1 = "Helen, es ist nicht so einfach. Verdammt, es tut mir leid, aber ich hätte nie gedacht, dass ich bei Madame Botot übernachten müsste! Die letzte Nacht hat sich in eine erschöpfende und brutale Schlacht der Köpfe verwandelt. Und ja, ich habe eine verdammt Fregatte in Karten gewonnen. Stell dir das vor?";
			link.l1.go = "GoldenGirl_19";
		break;
		
		case "GoldenGirl_19":
			dialog.text = "Wunderbar. Bedeutet das, dass du auch eine Kurtisane gewonnen hast? Und gegen was hast du die Fregatte gewonnen, die du gewonnen hast? Nicht unser Schiff, das könntest du nicht...";
			link.l1 = "Ich musste es tun. Schau, es spielt jetzt keine Rolle mehr, am Ende habe ich gewonnen. Mein Gegner forderte mich zu einem Duell heraus und beschuldigte mich des Betrugs. Er ist ein Bastard eines äußerst einflussreichen Adligen, Graf de Levi Vantadur. Das bedeutet, dass ich mein Bestes geben muss, um ihn nicht zu töten oder ihn zu stark zu verletzen.";
			link.l1.go = "GoldenGirl_20";
		break;
		
		case "GoldenGirl_20":
			dialog.text = "Wird er dasselbe tun? Hast du den Verstand verloren, Charles? Dein Schiff aufs Spiel setzen, dein Leben riskieren, wegen einer anderen Frau?! Ist sie das wirklich wert? Bedeute ich dir nichts?!";
			link.l1 = "Helen, es gibt keinen Grund zur Eifersucht, ich schwöre es. Es passierte einfach. Ich musste es tun und der Gouverneur stellte mir noble Offiziere als meine Sekundanten zur Verfügung, um sicherzustellen, dass alles nach den Regeln abläuft. Ich kann dich noch einen unserer Männer mitnehmen. Bitte kümmere dich um die Fregatte, während ich weg bin.";
			link.l1.go = "GoldenGirl_21";
		break;
		
		case "GoldenGirl_21":
			dialog.text = "Einfach großartig! Erst gehst du zu einer Orgie mit fremden Frauen und tauchst am nächsten Morgen wieder auf und ich habe dich dafür nicht mal gerügt. Jetzt sagst du mir, dass du fast unser Schiff bei einem Kartenspiel verloren hast, aber eine Kurtisane gewonnen hast! Und jetzt willst du für ihre 'Ehre' gegen irgendeinen hochnäsigen Hurensohn kämpfen, den du nicht einmal töten darfst! Wie soll ich das alles finden? Sag mir das.";
			link.l1 = "Helen, hör zu, du hast jedes Recht, wütend auf mich zu sein, aber lass mich einfach erklären...";
			link.l1.go = "GoldenGirl_22";
		break;
		
		case "GoldenGirl_22":
			dialog.text = "Weißt du was, ich habe genug von all dem. Geh und führe dein verdammtes Duell durch. Ich werde mich um deine neue Fregatte kümmern, großer Kapitän de Maure, mach dir keine Sorgen. Entschuldige mich jetzt, ich werde mich in meine Quartiere einschließen und eine Flasche dieses netten Madeira trinken, den ich in deiner Kabine gefunden habe. Aber wenn dir etwas passiert, schwöre ich bei Gott, dass ich dieses Dorf mit Höllenfeuer überziehen und dieses Bordell und den geliebten Palast deiner Exzellenz begraben werde!";
			link.l1 = "Helen, es wird alles gut, vertrau mir... Warte, wohin gehst du?! Verdammt! Da gehen wir wieder...";
			link.l1.go = "GoldenGirl_23";
		break;
		
		case "GoldenGirl_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_GirlToFregat", 15.0);
		break;
		
		case "GoldenGirl_24":
			dialog.text = "Charles, du hast einiges zu erklären. Würdest du mir freundlicherweise sagen, was zum Teufel passiert ist? Ich habe keine ordentliche Wache aufgestellt und die Jungs haben getrunken...einige Schurken haben unser Schiff überfallen und uns im Schlaf gefesselt. Dann hat der dreckige Abschaum angefangen, mich zu fragen, wie weit du gehen würdest, um mich zu retten. Am Ende sperrten sie mich in den Laderaum. Ich habe die Tage, die ich gewartet habe, nicht gezählt!";
			link.l1 = "Dieser Bastard wollte sich für die Schande, die ich ihm zugefügt habe, rächen. Ich hatte Angst, er könnte dir etwas antun! Gott sei Dank, du bist in Ordnung!";
			link.l1.go = "GoldenGirl_25";
		break;
		
		case "GoldenGirl_25":
			dialog.text = "Ich nehme an, du musstest etwas tun, um mich zurückzuholen? Etwas Schlimmes, richtig?";
			link.l1 = "Alles, was zählt, ist, dass du wieder bei mir bist. Ich habe dich im Stich gelassen, Helen. Es tut mir so leid! Ich hoffe, du kannst es in deinem Herzen finden, mir zu vergeben!";
			link.l1.go = "GoldenGirl_26";
		break;
		
		case "GoldenGirl_26":
			dialog.text = "Habe ich schon. Ich hatte viel Zeit, über das nachzudenken, was ich gesagt habe... Es tut mir auch leid, Charles. Wenn ich nur deine Geschäfte mit jenem Marquis nicht zu persönlich genommen hätte. Ich hätte in jener Nacht eine ordentliche Wache aufgestellt, ich wäre auf der Hut gewesen. Ach! Ich bin nur eine nutzlose Frau!";
			link.l1 = "Hör auf das zu sagen, die Vergangenheit ist die Vergangenheit. Ich liebe dich und ich werde dich nie wieder verlassen. Ich verspreche es!";
			link.l1.go = "GoldenGirl_27";
		break;
		
		case "GoldenGirl_27":
			dialog.text = "Ich nehme an, ich sollte wohl besser nicht wissen, was genau du getan hast, oder? Gut, wir sind wieder zusammen und das ist das Wichtigste.";
			link.l1 = "Ich habe keine Geheimnisse vor dir. Ich werde dir erzählen...";
			link.l1.go = "GoldenGirl_28";
		break;
		
		case "GoldenGirl_28":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_28_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_28_1":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Was für ein Durcheinander... Ich weiß, du hattest keine Wahl, aber wie erklärt man das Di Lu Parkes und seinen Freunden? Ich meine, du bist jetzt ein Verbrecher!";
				link.l1 = "Ich habe mich entschieden, diesen Preis zu zahlen, aber ich hatte wirklich keine Wahl. Mach dir keine Sorgen, ich werde einen Weg finden, es zu beheben und unseren guten Namen wiederherzustellen. Wenn nicht, dann werden wir immer auf der Isla Tesoro willkommen sein! Ich kann es schaffen, wenn du bei mir bist.";
			}
			else
			{
				dialog.text = "Welche Geschichte, Charles... Ich glaube, du hattest keine Wahl in der Sache, aber was kommt als nächstes? Wird dieser Engländer die Dinge in Ordnung bringen oder ist es Krieg? Bist du sicher, dass du nicht nach Basse-Terre kommen willst, um zu sehen, wie sie diesen Bastard in Ketten legen?";
				link.l1 = "Du weißt, Helen, vor zwei Wochen hätte ich es nie vermisst. Aber heute sage ich zum Teufel mit ihm! Ich kümmere mich nicht mehr um seine gerechte Strafe. Wir sind wieder zusammen, das ist alles, was zählt!";
			}
			link.l1.go = "GoldenGirl_29";
		break;
		
		case "GoldenGirl_29":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Du weißt, dass ich immer bei dir sein werde. Ha! Es ist nicht das erste Mal, dass du und ich bis zum Hals in den Bilgen stecken. Wir schaffen es wieder.";
				link.l1 = "Wahrlich. Lass uns in See stechen, mein Liebchen! Der Horizont erwartet uns!";
			}
			else
			{
				dialog.text = "Ich mag deine Denkweise, Charles! Keine Adligen mehr: Franzosen, Briten, Spanier - was auch immer. Ich glaube, wir haben uns einen Urlaub verdient!";
				link.l1 = "Einverstanden. Nur du und ich! Keine Gouverneure und adeligen Bastarde mehr!";
			}
			link.l1.go = "GoldenGirl_30";
		break;
		
		case "GoldenGirl_30":
			if (pchar.questTemp.GoldenGirl == "alarm_fin")
			{
				dialog.text = "Aye, aye, Kapitän!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Klingt wunderbar! Ich werde den Jungs sagen, dass es Zeit ist, den Anker zu lichten! Und Charles...";
				link.l1 = "Ich weiß, Helen, ich weiß. Ich werde mich in einem Moment zu dir gesellen.";
			}
			link.l1.go = "GoldenGirl_31";
		break;
		
		case "GoldenGirl_31":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "GoldenGirl_GirlGoOnBoard", 10.0);
		break;
		
		case "GoldenGirl_32":
			dialog.text = "Charles, Du hast es geschafft! Die Portugiesen haben mir alles erzählt! Was für eine Geschichte!";
			link.l1 = "Gott sei Dank, du lebst, Helen! Du hast keine Ahnung, wie froh ich bin, dich wieder zu sehen!";
			link.l1.go = "GoldenGirl_33";
		break;
		
		case "GoldenGirl_33":
			dialog.text = "Da wir gerade davon sprechen. Du hast versprochen, mir etwas zu erzählen, erinnerst du dich? Etwas Großes und Kompliziertes. Das ist deine Chance, Kapitän. Was zum Teufel ist passiert?!";
			link.l1 = "Ich liebe dich, Helen. Der Rest ist irrelevant.";
			link.l1.go = "GoldenGirl_34";
		break;
		
		case "GoldenGirl_34":
			dialog.text = "Ja, das war hilfreich, aber... Verdammt, ich auch, Charles. Ich liebe dich auch. Mein Gott, ich habe dich so sehr vermisst!";
			link.l1 = "Ich auch. Komm mit mir, ich werde dich heute Nacht nicht verlassen, selbst wenn der Himmel auf diese elende Stadt zu fallen beginnt. Ich werde dich nie wieder verlassen. Niemals.";
			link.l1.go = "GoldenGirl_35";
		break;
		
		case "GoldenGirl_35":
			dialog.text = "Ich nehme an, es ist besser, wenn ich nicht genau weiß, was du getan hast, oder? Aye, wir sind wieder zusammen und das ist das Wichtigste.";
			link.l1 = "Ich habe keine Geheimnisse vor dir. Ich werde dir erzählen...";
			link.l1.go = "GoldenGirl_36";
		break;
		
		case "GoldenGirl_36":
			DialogExit();
			SetLaunchFrameFormParam("Some time has passed...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0);
			npchar.dialog.currentnode = "GoldenGirl_36_1";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "GoldenGirl_36_1":
			dialog.text = "Unglaublich! Hast du gerade gesagt, dass Frankreich und England wegen mir am Rande eines Krieges miteinander stehen?";
			link.l1 = "Nein, Helen. Es liegt daran, dass ich einen sehr schlechten Fehler im Urteil gemacht habe. Aber ich musste dich zurückbringen und alles in Ordnung bringen.";
			link.l1.go = "GoldenGirl_37";
		break;
		
		case "GoldenGirl_37":
			dialog.text = "Das ist alles sehr rührend und romantisch, ich bin sogar bereit, zu vergessen, wie das alles überhaupt angefangen hat. Fast bereit. Aber ernsthaft, sie haben dich verhaftet, weil die Portugiesen den falschen Namen der verdammten Brigantine genannt haben?";
			link.l1 = "Ganz im Gegenteil, er hat mir den richtigen gegeben! Ich wünschte, ich wüsste, wie er das geschafft hat und warum. Übrigens, wo ist der Mann selbst?!";
			link.l1.go = "GoldenGirl_38";
		break;
		
		case "GoldenGirl_38":
			dialog.text = "Er ist weg. Gleich nachdem er mich hierher gebracht hat. Ich wollte die 'Gastfreundschaft' der Kurtisane, die du gewonnen hast, nicht in Anspruch nehmen, also habe ich Bartholomäus gebeten, ein Zimmer für mich zu mieten. Er hat dafür bezahlt und ist verschwunden, ohne ein Wort zu sagen. Eigentlich warte, nein, er hat doch einen Brief für dich hinterlassen!";
			link.l1 = "Ein Brief? Von Bartholomäus dem Portugiesen? Das ist neu. Mir gefällt nicht, wohin das führt...";
			link.l1.go = "GoldenGirl_39";
		break;
		
		case "GoldenGirl_39":
			dialog.text = "Also gut, ich werde es hier lassen, damit du es lesen kannst, währenddessen gehe ich und sage den Jungs hallo. Sie müssen sich Sorgen machen. Ich hätte nie gedacht, dass ich diese düsteren Hundegesichter vermissen würde! Versuch in der Zwischenzeit nicht, in eine weitere Katastrophe zu stürzen!";
			link.l1 = "Verdammt... Ich kann immer noch nicht glauben, dass ich dich zurückgebracht habe!";
			link.l1.go = "GoldenGirl_40";
		break;
		
		case "GoldenGirl_40":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "GoldenGirl_SPGirlReturn", 10.0);
		break;
		
		// Jason Долго и счастливо
		case "LongHappy":
			RemoveItems(pchar, "potionwine", 2);
			dialog.text = "Weißer Sand, klares grünes Wasser, du, ich und guter Wein - Charles, das ist so romantisch! Wir sollten öfter so zusammen spazieren gehen, nicht wahr!";
			link.l1 = "Gut, dass es dir gefällt. Ich denke, wir sollten dafür jetzt mehr Zeit einplanen.";
			link.l1.go = "LongHappy_1";
		break;
		
		case "LongHappy_1":
			dialog.text = "Charles, was hast du vor und warum bist du auf den Knien? Das ist so plötzlich...";
			link.l1 = "Helen, ich liebe dich. Und ich möchte jeden Tag, der mir von oben zugeteilt ist, mit dir verbringen. Deshalb frage ich dich hier und jetzt, im Angesicht dieses Meeres und Himmels - Helen Beatrice Sharp -  gib mir die Ehre, mit mir vor Mensch und Gott zu stehen, bis der Tod uns scheidet. Ich, Charles de Maure, Chevalier de Monper, frage dich - willst du mich heiraten?";
			link.l1.go = "LongHappy_2";
		break;
		
		case "LongHappy_2":
			if (pchar.location == "Shore_ship1")
			{
				dialog.text = "Weißt du, ich mochte diese Formalitäten nie, aber ich bin bis ans Ende der Welt bei dir. Und was deine Frage betrifft, die Antwort ist... oh, entschuldigung, ich habe verschüttet!";
				link.l1 = "Schon gut, das ist nur Wein und ich mochte dieses Hemd nie besonders...";
				link.l1.go = "LongHappy_3";
			}
			else
			{
				dialog.text = "Charles, natürlich ja! Ja, ja und nochmals ja!!! Aber ich hoffe doch sehr, du planst nicht, uns in irgendein verstaubtes Familienschloss zu verfrachten, um Rüben zu züchten bis an unser Lebensende?";
				link.l1 = "Nun, wir haben zwar eine Familienburg, aber sie ist nicht verstaubt und wir bleiben dort nicht. Unser Leben ist Freiheit und der Horizont liegt uns zu Füßen!";
				link.l1.go = "LongHappy_4";
			}
		break;
		
		case "LongHappy_3":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			DoQuestCheckDelay("Helena_LoveSex", 1.0);
			npchar.dialog.currentnode = "LongHappy_5";
			LAi_SetStayType(npchar);
		break;
		
		case "LongHappy_4":
			dialog.text = "Dann ein Toast auf dich, mein Kapitän, mein Ehemann, und auf unsere Hochzeit!";
			link.l1 = "Auf dich, meine Liebe! Und auf unsere gemeinsame Zukunft, es steht uns so viel bevor!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_5":
			dialog.text = "Dann ein Toast auf dich, mein Kapitän, mein Ehemann, und auf meine Hochzeit!";
			link.l1 = "Auf dich, meine Liebe! Und auf unsere gemeinsame Zukunft, es steht uns so viel bevor!";
			link.l1.go = "LongHappy_6";
		break;
		
		case "LongHappy_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.dialog.currentnode = "Helena_officer";
			LongHappy_MarryToSenPierre();
		break;
		
		case "LongHappy_7":
			dialog.text = "Also, Abbot Benoit ist zurückgekehrt und bereit, uns zu verheiraten. Aber nur damit du es weißt, ich werde auch für so einen Anlass kein Kleid tragen! Glaubst du, dass meine Hosen Aufsehen erregen werden?";
			link.l1 = "Helen, ich liebe dich in jedem Outfit, und sie werden darüber hinwegkommen. Zuerst wollte ich mich mit dir über die Gäste und die Zeremonie beraten.";
			link.l1.go = "LongHappy_8";
		break;
		
		case "LongHappy_8":
			dialog.text = "Ja, es gibt ein Problem - die meisten unserer besten Freunde, mit denen wir diesen Tag gerne teilen würden, dürfen die Stadt nicht betreten, geschweige denn die Kirche. Deshalb - lasst uns hier mit all den wichtigen Leuten heiraten, wie erwartet, und dann segeln wir zur Isla Tessoro und feiern richtig mit unseren echten Freunden, was denkst du?";
			link.l1 = "Das klingt gut für mich! Ich werde mit Abbot Benoit sprechen, aber wir müssen Einladungen und mehr verschicken...";
			link.l1.go = "LongHappy_9";
		break;
		
		case "LongHappy_9":
			dialog.text = "Beruhige dich, Kapitän. Deine bezaubernde zukünftige Frau wird einen Teil der Last auf sich nehmen! Ich werde alles auf der Isla Tesoro arrangieren und unseren Freunden schreiben, sag mir nur: Wie groß soll Ihre Hochzeit sein?";
			link.l1 = "Nur du, ich und unsere engsten Freunde. Nach all dem offiziellen Tand hier auf Martinique werden wir etwas aufrichtige Intimität wollen.";
			link.l1.go = "LongHappy_10";
			link.l2 = "Jeder muss diesen Tag in Erinnerung behalten! Ruft alle! Niemand wird ausgelassen!";
			link.l2.go = "LongHappy_11";
		break;
		
		case "LongHappy_10":
			pchar.questTemp.LongHappy.SmallMarry = "true";
			dialog.text = "Gemütlich und freundlich - du liest mir aus der Seele! Wir werden Sharptown besuchen müssen und ich werde alles vorbereiten. Ich denke, fünfzig Fässer Rum und zwei Dutzend Fässer Wein werden ausreichen. Außerdem werden wir für Essen und Unterhaltung dreihunderttausend Achtstücke benötigen.";
			link.l1 = "Erinnere mich - warum verwaltest du nicht wieder die Schiffskasse? Ich werde alles besorgen. Nur ein kurzer Besuch bei Abbot und dann segeln wir nach Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_11":
			pchar.questTemp.LongHappy.BigMarry = "true";
			dialog.text = "Also, du willst eine Party wie echte Seewölfe haben? In Ordnung! Wir werden Sharptown besuchen müssen und ich werde alles vorbereiten. Wir müssen uns ernsthaft eindecken - ich denke, hundert Fässer Rum und fünfzig Fässer Wein werden ausreichen. Und die anderen Ausgaben werden mindestens fünfhunderttausend Achtstücke betragen.";
			link.l1 = "Ladest du die gesamte Bruderschaft der Küste ein? Verdammt, lass es uns tun! Ich werde die Vorräte besorgen. Nur ein kurzer Besuch bei Abbot und wir setzen die Segel für Sharptown.";
			link.l1.go = "LongHappy_12";
		break;
		
		case "LongHappy_12":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "10");
			AddQuestUserData("LongHappy", "sName", "Helen");
			LongHappy_MarryGoToBenua();
		break;
		
		case "LongHappy_13":
			dialog.text = "Charles, ich kümmere mich um das Verladen, dann verteile ich die Einladungen an den Baron und mache mit dem Wirt alles klar. Sollte nicht zu lange dauern.";
			link.l1 = "Mach dir keine Sorgen, meine Liebe, ich werde mich mit lohnenswerter Beschäftigung ablenken... Oder einfach nur ein Nickerchen im Sand machen. Ich hätte nicht gedacht, dass es einfacher wäre, Tortuga zu stürmen, als meine eigene Hochzeit zu planen, um Himmels willen.";
			link.l1.go = "LongHappy_14";
		break;
		
		case "LongHappy_14":
			DialogExit();
			SetLaunchFrameFormParam("Mehrere Stunden sind vergangen...", "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 4, 0);
			LongHappy_IslaTesoroRemoveGoods();
			npchar.dialog.currentnode = "LongHappy_15";
			LAi_SetActorType(npchar);
			LAi_ActorDialogDelay(npchar, pchar, "", 4.0);
		break;
		
		case "LongHappy_15":
			dialog.text = "Hast du etwas Ruhe bekommen, Charles? Ich habe gute und schlechte Neuigkeiten. Die schlechte Nachricht ist, dass die Einheimischen letzte Woche so viel Spaß hatten, dass sie versehentlich die verdammte 'Old Woodpecker' Kneipe abgebrannt haben! Hier ist die gute Nachricht, der Baron hat versprochen, dass sie bis zu unserer Rückkehr größer und besser als je zuvor wieder aufgebaut wird. Ich habe Vorkehrungen getroffen, sodass wir in See stechen können.";
			link.l1 = "Ich hoffe, unsere Hochzeit wird nicht einen ähnlichen Haufen Asche in der Stadt hinterlassen, wenn wir gehen. Das ist verdammt schade, mir hat der 'Alte Specht' ziemlich gut gefallen - gemütlich, intim, mit nur einem leichten Hauch von Erbrochenem und Teer! Nun ja, Liebling, du hast recht - wir sollten losgehen.";
			link.l1.go = "LongHappy_16";
		break;
		
		case "LongHappy_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_GirlNorm", 5.0);
			AddQuestRecord("LongHappy", "12");
			pchar.questTemp.LongHappy = "marry_wait";
			pchar.questTemp.LongHappy.DrinkReady = "true";
		break;
		
		case "LongHappy_17":
			dialog.text = "Jan ist bereits mit Gladys in der Stadt, kannst du dir das vorstellen? Ich hätte nie gedacht, dass sie jemals meine Hochzeit besuchen würden! Oh süßer Jesus! Selbst als wir in dieser schrecklichen indischen Tempelstadt waren, hatte ich nicht so viel Angst wie jetzt!";
			link.l1 = "Alles ist gut, Liebling, alles ist gut. Ich bin auch besorgt - Nervosität ist normal. Da die Gäste bereits gekommen sind, sollte ich zu Vater Benoit gehen und herausfinden, wann der Gottesdienst beginnen wird.";
			link.l1.go = "LongHappy_18";
		break;
		
		case "LongHappy_18":
			dialog.text = "Es wird ein verdammt langer und schwieriger Tag... Ich gehe Jan und Gladys sehen.";
			link.l1 = "Ich bin froh, dass sie kommen konnten. Der alte Herr Svensson liebt dich wie seine eigene Tochter, und Miss McArthur noch mehr. Es ist gut, dass sie heute hier sind. Geh und mach dir keine Sorgen - alles wird gut.";
			link.l1.go = "LongHappy_19";
		break;
		
		case "LongHappy_19":
			DialogExit();
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			AddQuestRecord("LongHappy", "14");
			AddQuestUserData("LongHappy", "sName", "Helen");
		break;
		
		case "LongHappy_20":
			dialog.text = "Ja.";
			link.l1 = "";
			link.l1.go = "LongHappy_21";
		break;
		
		case "LongHappy_21":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_22":
			dialog.text = "Ja.";
			link.l1 = "";
			link.l1.go = "LongHappy_23";
		break;
		
		case "LongHappy_23":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_29";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_24":
			dialog.text = "Ja.";
			link.l1 = "";
			link.l1.go = "LongHappy_25";
		break;
		
		case "LongHappy_25":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_31";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_26":
			dialog.text = "";
			link.l1 = "Ich, Charles Henry de Maure, Ritter von Monper, nehme dich, Helen Beatrice Sharp, zu meiner Frau, zu haben und zu halten, von diesem Tag an, zum Besseren und zum Schlechteren, im Reichtum und in Armut, in Krankheit und Gesundheit, bis der Tod uns scheidet. Nach Gottes heiligem Gesetz, in Gottes Gegenwart, gebe ich dieses Gelübde ab.";
			link.l1.go = "LongHappy_27";
		break;
		
		case "LongHappy_27":
			dialog.text = "Ich, Helen Beatrice Sharp, nehme dich, Charles Henry de Maure, zu meinem Ehemann, um dich zu haben und zu halten, von diesem Tag an, zum Besseren und zum Schlechteren, im Reichtum und in Armut, in Krankheit und Gesundheit, bis der Tod uns scheidet. Nach Gottes heiligem Gesetz, in Gegenwart Gottes, gebe ich dieses Gelübde ab.";
			link.l1 = "";
			link.l1.go = "LongHappy_28";
		break;
		
		case "LongHappy_28":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_33";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_29":
			dialog.text = "Amen.";
			link.l1 = "";
			link.l1.go = "LongHappy_30";
		break;
		
		case "LongHappy_30":
			DialogExit();
			sld = characterFromId("Benua");
			sld.dialog.currentnode = "LH_abbat_35";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "LongHappy_31":
			dialog.text = "Helen Beatrice de Maure, Madame de Monper - oh, mir gefällt der Klang davon, mein liebster Ehemann!";
			link.l1 = "Habe nichts Besseres gehört, meine Frau!";
			link.l1.go = "LongHappy_32";
		break;
		
		case "LongHappy_32":
			dialog.text = "Weißt du - ich dachte, dass dies nichts ändern würde, und wahrscheinlich hat es das auch nicht - ich habe dich vorher geliebt und wollte den Rest der Tage mit dir verbringen, aber dieser Tag, dieser heilige Dienst... Ich bin wahrhaft glücklich, Charles! Glücklich wie nie zuvor, und schau dir Gladys und Jan an - sie strahlen! Es gibt so viele glückliche Gesichter hier! Übrigens - es ist Zeit für dich, bei den Gästen herumzugehen und ihre Glückwünsche entgegenzunehmen. Komm zurück, wenn du fertig bist, vergiss nicht - wir werden in Sharptown erwartet.";
			link.l1 = "Ich mache es sofort, Liebling. Ein Kuss bevor ich gehe!";
			link.l1.go = "LongHappy_33";
		break;
		
		case "LongHappy_33":
			DialogExit();
			LongHappy_MarryKiss();
		break;
		
		case "LongHappy_34":
			dialog.text = "Hallo Ehemann, hast du schon mit den Gästen gesprochen?";
			link.l1 = "Noch nicht, sei geduldig, Frau, ich komme bald zurück.";
			link.l1.go = "LongHappy_34_1";
			link.l2 = "Ja, ich habe noch nie so viele Glückwünsche auf einmal gehört. Und weißt du was - Ich glaube, die meisten von ihnen sprachen aufrichtig!";
			link.l2.go = "LongHappy_35";
		break;
		
		case "LongHappy_34_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_34";
		break;
		
		case "LongHappy_35":
			dialog.text = "Ja, diese Edelleute sind überraschend aufrichtig - zugegeben, ich habe mehr Falschheit und Heuchelei erwartet. Oder ich bin einfach so glücklich, dass ich nichts bemerke. Aber schließlich warten unsere Freunde auf uns in Sharptown! Wann segeln wir?";
			link.l1 = "Jetzt sofort. Wir fliegen auf Adlersflügeln direkt zu einem freundlichen Fest. Ich hoffe, meine Frau, es stört dich nicht, diese Nacht in unserer Kajüte zu verbringen?";
			link.l1.go = "LongHappy_36";
		break;
		
		case "LongHappy_36":
			dialog.text = "Oh ja, mein Mann, du bist so romantisch! Und zucke nicht so, jetzt habe ich das Recht, dich in der Öffentlichkeit zu küssen... Aye, wir können jetzt gehen!";
			link.l1 = "Navigator, setze Kurs auf Sharptown und störe uns aus keinem Grund! Es ist mir egal, wenn eine Geisterflotte auf uns zukommt!";
			link.l1.go = "LongHappy_37";
		break;
		
		case "LongHappy_37":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
			LongHappy_MarryComplete();
		break;
		
		case "LongHappy_38":
			dialog.text = "Oh mein lieber Ehemann, ich bin so glücklich! Heute ist ein wunderbarer Tag...";
			link.l1 = "";
			link.l1.go = "LongHappy_38_1";
		break;
		
		case "LongHappy_38_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_38";
		break;
		
		case "LongHappy_39":
			dialog.text = "Komm schon Charles. Dieser Lügner wird tot sein, bevor er den Boden berührt!";
			link.l1 = "";
			link.l1.go = "LongHappy_40";
		break;
		
		case "LongHappy_40":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Angerran") && CharacterIsAlive("Angerran")) // fix 02-04-20
			{
				sld = characterFromId("Angerran");
				sld.dialog.currentnode = "Shivo_6";
			}
			else 
			{
				sld = characterFromId("LH_Dussak");
				sld.dialog.currentnode = "Dussak_5";
			}
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_41":
			dialog.text = "Ich bin in Ordnung, Charles, alles ist gut. Wie geht es Nathan?";
			link.l1 = "So viel Blut... Dannie, atmet er? Ich sehe ihn atmen!";
			link.l1.go = "LongHappy_42";
		break;
		
		case "LongHappy_42":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "LongHappy_43":
			dialog.text = "Schneller, Liebling, verschwende keine Zeit!";
			link.l1 = "";
			link.l1.go = "LongHappy_43_1";
		break;
		
		case "LongHappy_43_1":
			DialogExit();
			npchar.dialog.currentnode = "LongHappy_43";
		break;
		
		case "LongHappy_44":
			dialog.text = "Charles, geht es dir gut? Was für ein Blutbad! Entschuldigung, wir waren oben festgefahren, es gab ein Dutzend dieser Bastarde, also musste ich mich zuerst um sie kümmern!";
			link.l1 = "Es ist in Ordnung, ich habe es geregelt. Ich bin froh, dass ich diese Geschichte mit Jacques... endlich abschließen konnte. Er hat bekommen, was er verdient hat.";
			link.l1.go = "LongHappy_45";
		break;
		
		case "LongHappy_45":
			dialog.text = "Gut, meine Liebe, lass uns hier fertig werden und zurückkehren. Ich kann nicht aufhören an Nathan zu denken, wie geht es ihm? Er hat mich vor dieser Kugel geschützt!";
			link.l1 = "Du hast recht, Liebling, ich mache mir auch Sorgen. Geh voran, ich bin direkt hinter dir.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "LongHappy_46";
			else link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_46":
			dialog.text = "Wir haben Marcus gefunden! Er war im Frachtraum, gefesselt und bewusstlos.";
			link.l1 = "Er lebt?";
			link.l1.go = "LongHappy_47";
		break;
		
		case "LongHappy_47":
			dialog.text = "Mach dir keine Sorgen, Liebe, Baron Tyrex wird noch länger leben als wir. Er ist gerade aufgewacht und brummt schon, er ruft ständig nach Rum, seinem Säbel und der Brücke - in dieser Reihenfolge.";
			link.l1 = "Das ist unser alter Marcus! Lasst ihn ein bisschen ruhen, während wir hier fertig werden und dann zurück zum Ufer gehen.";
			link.l1.go = "LongHappy_48";
		break;
		
		case "LongHappy_48":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		case "LongHappy_49":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Es tut mir so leid, Liebling... Erst unser treuer Freund Tichingitu, jetzt Gino... Barbazon hätte ein Dutzend Mal für all das getötet werden sollen, was er getan hat!";
				link.l1 = "Ach, ich habe es nur einmal getan. Ich fühle mich auch schlecht... Aber wir haben gewonnen und er wird nie wieder jemandem wehtun.";
				link.l1.go = "LongHappy_50";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "Ich fühle mich so schrecklich wegen Gino, Charles! Als ich es herausfand, konnte ich es nicht glauben! Wie geht es dir, Liebling?";
					link.l1 = "Ich kann es auch nicht glauben... was für ein Weg zu gehen... Ich hätte nie gedacht, dass dieser Tag so enden würde.";
				}
				else
				{
					dialog.text = "Ich frage mich, werden zukünftige Historiker über die große Schlacht von Privateer Bay schreiben? Der Tag, an dem die Barone der Bruderschaft der Küste in offener Schlacht aufeinandertrafen - ich wette, die spanische Costa Garda wischt sich Tränen der Dankbarkeit weg! Aber, wir haben wieder gewonnen! Unsere Freunde sind am Leben und unsere Feinde sind tot - ein glorreiches Hochzeitsgeschenk!";
					link.l1 = "Ja, so eine Feier, aber wir haben es geschafft, mein Engel. Wir haben es geschafft.";
				}
				link.l1.go = "LongHappy_50";
			}
		break;
		
		case "LongHappy_50":
			dialog.text = "Komm schon, Dannie hat uns ein Haus hier am Stadtrand gefunden, ich möchte jetzt nicht zum Schiff zurückkehren, bis es aufgeräumt ist. Wir werden sitzen und auf die trinken, die es nicht geschafft haben.";
			link.l1 = "Ja, Helen, lass uns gehen.";
			link.l1.go = "LongHappy_51";
		break;
		
		case "LongHappy_51":
			DialogExit();
			LongHappy_LogBook();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "LongHappy_52":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "Ich fühle mich so schlecht wegen Gino, Charles! Als ich es erfahren habe, konnte ich es nicht glauben! Wie geht es dir?";
				link.l1 = "Ich kann es auch nicht glauben... was für ein Weg zu gehen... Ich hätte nicht gedacht, dass dieser Tag so enden würde.";
			}
			else
			{
				dialog.text = "Hast du Hawk gesehen? Dannie hat mich rausgelassen, als Gino sagte 'die Gefahr ist vorbei'. Ich bin froh, dass alles in Ordnung ist. Unsere Freunde leben und unsere Feinde sind tot - ein glorreiches Hochzeitsgeschenk!";
				link.l1 = "Ich Auch, Liebling. Und wir haben gewonnen. Barbazon ist tot, die Barone sammeln, was von ihren Mannschaften übrig ist. Der Kampf ist vorbei.";
			}
			link.l1.go = "LongHappy_53";
		break;
		
		case "LongHappy_53":
			dialog.text = "Charles, ich sehe, du kannst kaum stehen, aber ich habe die Taverne besucht und du wirst nicht glauben, was ich vom Wirt gehört habe.";
			link.l1 = "Ja, ich habe es von Jan gehört, er war auch dort. Es scheint mir, dass unser lieber Indianer auf den Kriegspfad gegangen ist. Lass uns zur Sabo-Matila-Bucht spazieren, ein paar Leute haben gesehen, wie er in diese Richtung abgezogen ist.";
			link.l1.go = "LongHappy_54";
		break;
		
		case "LongHappy_54":
			DialogExit();
			LongHappy_LogBook();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.longhappy_shoregirl.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl.win_condition.l1.location = "Shore_ship1";
			pchar.quest.longhappy_shoregirl.function = "LongHappy_SetShoreGirl";
		break;
		
		case "LongHappy_55":
			dialog.text = "Gott im Himmel! Das ist der Geist, Tichingitu! Phew, ich lache mir hier den Arsch ab! Warum übernehmen wir Europäer nicht auch so einen Brauch?! Oh Charles, du schläfst fast auf den Beinen! Los, Dannie hat für uns ein Haus am Stadtrand gefunden - du musst dich ausruhen.";
			link.l1 = "Führe weiter ... Ich glaube, ich bin schon einmal an diesem Strand eingeschlafen.";
			link.l1.go = "LongHappy_56";
		break;
		
		case "LongHappy_56":
			DialogExit();
			DoQuestCheckDelay("LongHappy_MarryFinalizing", 0.5);
		break;
		
		case "tonzag_jailed":
			dialog.text = "... Es ist in Ordnung.";
			link.l1 = "Gut zu hören.";
			link.l1.go = "exit";
			link.l2 = "Wirklich?";
			link.l2.go = "tonzag_jailed_1";
			locCameraFromToPos(-15.50, 2.28, -1.23, true, -27.00, -10.60, -22.70);
		break;
		
		case "tonzag_jailed_1":
			dialog.text = "Ja.";
			link.l1 = "Gut zu hören.";
			link.l1.go = "exit";
			link.l2 = "Los, ich kann sehen, dass dich etwas bedrückt!";
			link.l2.go = "tonzag_jailed_2";
		break;
		
		case "tonzag_jailed_2":
			dialog.text = "Ich bin völlig in Ordnung, lass es gut sein!\nCharles, fahr zur Hölle! Ich hasse Verliese, ich hasse dich und ich hasse diese verdammte Insel! Hol mich sofort hier raus!\nTut mir leid... Ich mag wirklich keine Verliese, fass mich nicht an!";
			link.l1 = "Entschuldigung. Wir alle fürchten etwas.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_aftershot":
			dialog.text = "AAAA! Lass uns hier raus! Charles, tu etwas!";
			link.l1 = "Reiß dich zusammen!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("Tonzag_TichingituAfterShot");
		break;
		
		case "tonzag_after_boarding":
			dialog.text = "Mein Kapitän, der Feind hat das Rumpf auf dem zweiten Deck durchbrochen und eine Entertruppe gelandet. Schlachten toben über das ganze Schiff, und die meisten Geschützmannschaften sind ausgeschaltet! Wir müssen unsere Besatzung und Hercule retten! Gehst du, oder soll ich?";
			link.l1 = "Dieses Mal gehe ich selbst, Helen! Übernimm das Kommando über das Schiff und bring uns hier raus!";
			link.l1.go = "tonzag_after_boarding_1";
			DelLandQuestMark(npchar);
		break;
		
		case "tonzag_after_boarding_1":
			dialog.text = "Aye aye, mein Kapitän. Ich werde dich nicht enttäuschen, und bitte sei vorsichtig!";
			link.l1 = "Ich weiß, Helen. Und sei auch du vorsichtig!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_GoToGunDeck");
		break;
		
		case "tonzag_after_victory":
			dialog.text = "Sieg, mein Kapitän! Die Landungspartei wurde eliminiert, der Feind hat sich zur Rückzug entschieden und ist nach Süden gezogen. Der Zustand des Schiffes ist akzeptabel. Lebende Besatzung: "+GetCrewQuantity(pchar)+" Leute. Bericht abgeschlossen!";
			link.l1 = "Danke dir, Helen, und was...";
			link.l1.go = "tonzag_after_victory_1";
		break;
		
		case "tonzag_after_victory_1":
			dialog.text = "Entkleide dich, Sieger, deine Belohnung ist es, mit mir zu tun, was immer du willst!";
			link.l1 = "Äh...";
			link.l1.go = "tonzag_after_victory_2";
			link.l2 = "Los geht's!";
			link.l2.go = "tonzag_after_victory_2";
		break;
		
		case "tonzag_after_victory_2":
			dialog.text = "Oh, hallo, Hercule. Entschuldigung, du hast uns in einem ungünstigen Moment erwischt! Aber verdammt, ich bin froh, dich lebend und mit jemand anderem's Blut bedeckt zu sehen - ein natürlicher Zustand für dich, hm!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog");
		break;
		
		case "tonzag_after_victory_3":
			dialog.text = "";
			link.l1 = "Nun, Helen, du bist etwas Besonderes!";
			link.l1.go = "tonzag_after_victory_4";
		break;
		
		case "tonzag_after_victory_4":
			dialog.text = "Ich habe noch nicht einmal angefangen, mein Kapitän. Sollen wir feiern?";
			link.l1 = "Ich brauche keine Überzeugung!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;
		
		case "tonzag_dead":
			dialog.text = "Nicht hinsehen, nicht hinsehen, nicht hinsehen... Das ist eine andere Welt, mein Kapitän! Es kann nicht so sein!";
			link.l1 = "Ich denke, das ist jetzt unsere Welt, Liebling. Und du hast recht, lass uns nicht herumhängen...";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
		break;
		
		// Jason Исла Мона
		case "IslaMona":
			dialog.text = "Ich fürchte, diese Pandemie zehrt an deinen Mädchen, Rodrigo. Beschäftige sie mit Stricken oder so etwas!";
			link.l1 = "Dieses Gespräch führt klar zu nichts. Wir haben vereinbart, dass wir morgen zur Kirche gehen werden. Zum Beten... natürlich.";
			link.l1.go = "IslaMona_1";
		break;
		
		case "IslaMona_1":
			DialogExit();
			LAi_SetOfficerType(npchar);
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes");
			sld.dialog.currentnode = "Himenes_church_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_2":
			dialog.text = "Ich bin stolz auf dich, meine Liebe!";
			link.l1 = "";
			link.l1.go = "IslaMona_3";
		break;
		
		case "IslaMona_3":
			DialogExit();
			npchar.dialog.currentnode = "Helena_officer";
			sld = characterFromId("Himenes_companion_1");
			sld.dialog.currentnode = "island_man_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "IslaMona_4":
			dialog.text = "Nun, Charles...";
			link.l1 = "Was geht dir schon wieder durch den Kopf, Helen?";
			link.l1.go = "IslaMona_5";
		break;
		
		case "IslaMona_5":
			dialog.text = "Die Tatsache, dass das skandalöseste Paar der Karibik zwei ganze Inseln besitzt! Mein Piratenhafen Isla Tesora und dein gelobtes Land - wie lange glaubst du, können sie bestehen, wenn die Zivilisation endlich in die Westindischen Inseln kommt?";
			link.l1 = "Lang genug, um unser ganzes Leben zu dauern, Liebling. Und danach? Wir können nicht kontrollieren, was dann passiert. Andere werden unsere Geschichte erzählen. Das Wichtigste ist, dass du und ich hier und jetzt sind, zusammen und glücklich.";
			link.l1.go = "IslaMona_6";
		break;
		
		case "IslaMona_6":
			dialog.text = "Vom Glück sprechend... Ich werde jetzt gleich nach oben gehen: Ich muss die Kerzen anzünden, das Bett machen, vielleicht in mein Tagebuch schreiben...";
			link.l1 = "Ich bleibe hier noch ein wenig, und dann werde ich dir 'beim Bettenmachen' helfen.";
			link.l1.go = "IslaMona_7";
		break;
		
		case "IslaMona_7":
			dialog.text = "Mach nicht zu lange...";
			link.l1 = "";
			link.l1.go = "IslaMona_8";
		break;
		
		case "IslaMona_8":
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
			ChangeCharacterAddressGroup(npchar, "IslaMona_TwoFloorRoom", "goto", "goto4");
			DoQuestCheckDelay("Helena_LoveSex", 2.5);
			NextDiag.CurrentNode = "sex_after";
			pchar.questTemp.IslaMona.Doorlock = "true";
		break;
		
		case "drinking_refuse":
			dialog.text = "Bist du wirklich so beschäftigt? Zu schade, aber ich verstehe. Ich werde etwas anderes finden, womit ich mich beschäftigen kann.";
			link.l1 = "";
			link.l1.go = "exit";
			NextDiag.TempNode = "Helena_wait";
			
			pchar.questTemp.HelenDrinking.Result = "no_visit";
			CloseQuestHeader("HelenDrinking");
		break;
		
		case "drinking_accept":
			dialog.text = "Es ist schön, dass du dich erinnerst. Ich wollte dir sagen, dass ich dir sehr dankbar bin. Nicht jeden Tag rettet dich jemand vor... du weißt schon was. Lass uns etwas trinken gehen. Ich lade dich ein.";
			link.l1 = "Helen... Was wird Gladys sagen?";
			link.l1.go = "drinking_accept_1";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToHouse");
		break;
		
		case "drinking_accept_1":
			dialog.text = "Sehr lustig, Charles. Komm schon, und nerv mich nicht.";
			link.l1 = "Ist das ein Date?";
			link.l1.go = "drinking_accept_1_1";
			link.l2 = "Komme schon, kein Grund, mürrisch zu werden.";
			link.l2.go = "drinking_accept_1_2";
		break;
		
		case "drinking_accept_1_1":
			dialog.text = "Ha-ha! Du wünscht! Ich müsste komplett betrunken sein!";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_accept_1_2":
			dialog.text = "Das ist besser.";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "drinking_in_tavern":
			dialog.text = "";
			link.l1 = "... sie hatte viele Tugenden, aber sie konnte ihren Alkohol nicht halten. So haben wir uns getroffen.";
			link.l1.go = "drinking_in_tavern_1";
			link.l2 = "... mein Vater bestand auf Militärdienst. Ich gab nach und ging mit einem Empfehlungsschreiben nach Paris. Aber ich schaffte es nie zur angegebenen Adresse und wurde Künstler.";
			link.l2.go = "drinking_in_tavern_2";
		break;
				
		case "drinking_in_tavern_1":
			dialog.text = "Ach, jetzt verstehe ich, von welchen Tugenden du sprichst. Wie war ihr Name?";
			link.l1 = "Lulu.";
			link.l1.go = "drinking_in_tavern_1_1";
		break;
		
		case "drinking_in_tavern_1_1":
			dialog.text = "Lulu... Mit diesen Geschichten hast du Paris für mich völlig ruiniert. Ich dachte, es wäre eine Stadt des prächtigen Lebens, aber es klingt eher wie ein großes, schickes Bordell.";
			link.l1 = "Verurteilen Sie Bordelle?";
			link.l1.go = "drinking_in_tavern_1_2";
		break;
		
		case "drinking_in_tavern_1_2":
			dialog.text = "Ja, Kapitän, und ich verstehe Männer nicht, die sie besuchen.";
			link.l1 = "(in den Becher starren)";
			link.l1.go = "drinking_in_tavern_1_4";
			link.l2 = "(habe einen schrecklichen Husten)";
			link.l2.go = "drinking_in_tavern_1_4";
			link.l3 = "Äh... jedem das Seine... nehme ich an?";
			link.l3.go = "drinking_in_tavern_1_4";
		break;
		
		case "drinking_in_tavern_1_4":
			dialog.text = "(lacht) Ha! Du hättest dein Gesicht sehen sollen! Angst? Lass uns noch einen heben! Auf Paris!";
			link.l1 = "Auf Paris!";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_2":
			dialog.text = "(lacht) Du?! Ein Künstler? Also, die Schönheit und der Stolz der englischen Flotte, ein Vergewaltiger und einfach ein Hurensohn Donovan, starb durch die Hände eines Pariser Künstlers? Ah, zu schade, dass du beim Entern nicht dein makelloses Jabot getragen hast und dieses Gesindel nicht mit einem Stock geschlagen hast!";
			link.l1 = "Ja, sehr unglücklich. Der Jabot war gerade an diesem Tag in der Wäsche.";
			link.l1.go = "drinking_in_tavern_2_1";
		break;
		
		case "drinking_in_tavern_2_1":
			dialog.text = "(lacht) Nun, danke, Charles. Ich weiß nicht, wie der Rest des Abends verlaufen wird, aber der Abend war bereits großartig. Ich könnte dir sogar erlauben, mein Porträt zu malen. Aber, pass auf, nicht im gleichen Stil, wie du deine Pariser Mädchen gemalt hast!";
			link.l1 = "Ha! Das auch nur, wenn ich zustimme, dich zu malen.";
			link.l1.go = "drinking_in_tavern_3";
		break;
		
		case "drinking_in_tavern_3":
			dialog.text = "Entschuldigen Sie, mein Kapitän, ich höre von Ihren Abenteuern und dem Leben der edlen... Kurtisanen beider Geschlechter. Ein Hai soll mich beißen, ich werde nie glauben, dass du nichts Besseres mit deiner Zeit anfangen könntest! Wage es nicht einmal, mir zu sagen, dass du nur Leinwände beschmiert und Papas Geld verschwendet hast. Du hättest keinen Tag bei uns überlebt, wenn das wahr wäre.";
			link.l1 = "Ich hatte auch... andere Beschäftigungen.";
			link.l1.go = "drinking_in_tavern_" + pchar.HeroParam.HeroType;
		break;
		
		case "drinking_in_tavern_herotype_3":
			dialog.text = "";
			link.l1 = "Ich habe das Leben am Hof mit dem Militärdienst kombiniert, aber nicht... hehe, natürlich nicht ganz so, wie mein Vater es wollte. Ein paar Fluchten durch das Fenster und eine Schlägerei - und ich wurde mit den Wachen befreundet. Und natürlich habe ich eine Menge Dinge aufgegriffen, meinen Körper gestählt. Ältere Kameraden haben mir beigebracht, einen Schlag einzustecken, eine Rüstung zu tragen, ein Schwert zu handhaben und mich richtig zu entspannen. Der letzte Teil hat mir natürlich besonders gut gefallen. Du wirst es nicht glauben, aber nicht jeder kann von morgens bis mittags ein Schwert schwingen und dann von mittags bis zum nächsten Morgen trinken.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_1":
			dialog.text = "";
			link.l1 = "Glaubst du, es war einfach in der Hauptstadt für einen Adligen mit schlechtem Ruf und leerer Börse, der bereits am ersten Tag Vaters Empfehlungsschreiben verlor? Ich musste mich durchsetzen und niemanden über mich lachen lassen. Die Fechtlektionen zu Hause wurden nicht vergessen, und ich antwortete auf jeden seitlichen Blick mit einem Duell. Dann bekam ich wirklich den Dreh raus. Trotzdem habe ich niemanden getötet und es geschafft, Paris zu verlassen, bevor ich auf einen erfahrenen Kämpfer traf, der mich erledigt hätte.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_4":
			dialog.text = "";
			link.l1 = "Habe viel Zeit auf Friedhöfen verbracht. Denk nichts Schlechtes - es war einfach ein beliebtes Hobby in meinem Freundeskreis. Für den Mut gingen wir nachts auf einen Friedhof, stellten leere Flaschen auf den Zaun und schossen auf sie mit einem Timer. Über Nacht verschwendeten wir hundert Kugeln und eine Kiste Champagner. Jetzt natürlich schäme ich mich für ein solches Verhalten, aber damals nahm der Gewinner einen soliden Jackpot mit und bekam einige... Gefälligkeiten von der weiblichen Seite des Hofes. Alles wurde genutzt - ich habe sogar ein bisschen mit Schießpulvermischungen herumexperimentiert. Aber warum keiner von uns daran gedacht hat, zu lernen, wie man Papierpatronen herstellt - das werde ich nie wissen.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_herotype_2":
			dialog.text = "";
			link.l1 = "Studierte, und zwar ziemlich fleißig - war sogar kurz davor, an die Sorbonne zu kommen. Arbeitete in einem Büro, bis es langweilig wurde, und im Allgemeinen - habe ich ein bisschen von allem gemacht. Der Lehrer, ein alter Freund meines Vaters, zog die Praxis der Theorie vor, also bekam ich Paris von allen Seiten zu sehen und mit verschiedenen Leuten zu reden: von Banditen bis zu Adligen. All das hat sich hier als nützlich erwiesen.";
			link.l1.go = "drinking_in_tavern_4";
		break;
		
		case "drinking_in_tavern_4":
			dialog.text = "Und... das ist alles? Also steckt noch etwas in dir, mein Kapitän. Etwas, das du selbst noch nicht gesehen hast. Auf dich!";
			link.l1 = "Guter Toast!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernChange");
		break;
		
		case "drinking_my_background":
			dialog.text = "";
			link.l1 = "Erzähl mir deine Geschichte, Helen. Meine Abenteuer in der Hauptstadt verblassen im Vergleich zu einem Mädchen knapp unter dreißig, das einen Schoner mit hundert Männern an Bord kommandiert.";
			link.l1.go = "drinking_my_background_1";
		break;
		
		case "drinking_my_background_1":
			dialog.text = "Knapp unter dreißig, hm, Charles? Für so einen starken Kommentar wirst du die nächste Runde bezahlen müssen! All meine Leute sind tot, und ich befehlige keine Schoner mehr. Ehrlich gesagt, ich weiß nicht, ob ich jemals wieder einen befehligen werde.";
			link.l1 = "Es tut mir leid, Helen. Ich wollte nicht einen Nerv treffen. Aber warum glaubst du, dass deine Kapitänkarriere vorbei ist?";
			link.l1.go = "drinking_my_background_2";
		break;
		
		case "drinking_my_background_2":
			dialog.text = "Weil meine Mannschaft tot ist, und eine andere wird mich nie akzeptieren. Eh! Gut, mein Kapitän, Du hast mir schon viel über dein Leben erzählt, jetzt bin ich dran! Die Wahrheit liegt nicht auf dem Grund dieses Bechers, also lassen wir das Rätselraten sein.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_3";
		break;
		
		case "drinking_my_background_3":
			dialog.text = "Mein Fall, Charles, ist einzigartig. Mein Vater war einer der besten Seefahrer in diesen Teilen, hoch geschätzt vom Forest Devil, seine Crew verehrte ihn, und er liebte mich mehr als das Leben selbst.";
			link.l1 = "";
			link.l1.go = "drinking_my_background_4";
		break;
		
		case "drinking_my_background_4":
			dialog.text = "Nimm nur eines dieser Dinge weg, und er hätte mich entweder nach London geschickt, um in... Zivilisation zu leben, oder er hätte mich hier verwelken lassen wie meine Mutter. Am Anfang lief alles großartig: Ich wollte Freiheit, echte Freiheit, Charles, und ein geschicktes Kommando über ein Kriegsschiff mit einer treuen Besatzung gibt dir genau das. Und mein Vater gab mir alles, was er konnte. Mit zwölf Jahren fuhr ich mit ihm auf See hinaus, verbrachte die ersten sechs Monate damit, Ratten im Frachtraum zu jagen, und durfte erst dann mit den Matrosen arbeiten.";
			link.l1 = "Sean MacArthur hat dich zu einer Schiffsratte gemacht? Tut mir leid, Helen, aber da gibt es kein Zurück mehr! Wie haben die Mannschaft dich akzeptiert?";
			link.l1.go = "drinking_my_background_5";
		break;
		
		case "drinking_my_background_5":
			dialog.text = "Nun, vielleicht übertreibe ich ein wenig, um eine gute Geschichte zu erzählen? Die Mannschaft meines Vaters hat mich akzeptiert, er hat gute Leute um sich geschart. Aber seitdem habe ich Angst... vor Laderäumen und kleinen dunklen Räumen im Allgemeinen. Ha! Svensson hätte meinen Vater fast umgebracht, als er davon erfuhr!";
			link.l1 = "Er ist dir wichtig. Er hat offensichtlich eine Rolle in deinem Schicksal gespielt, nicht weniger als Sean.";
			link.l1.go = "drinking_my_background_6";
		break;
		
		case "drinking_my_background_6":
			dialog.text = "Ja. Alle Barone haben meinem Vater direkt gesagt, dass er ein Narr ist, aber es war der Forest Devil, der ihm seine Zustimmung gab und ihm die Hand schüttelte, nachdem ich den Rekord der Mannschaft beim Mastklettern gebrochen hatte. Dieser Moment wird für immer bei mir bleiben: die triumphierenden Rufe der Mannschaft und, wohin ich auch blickte, der saubere Meereshorizont. Und der zustimmende Blick meines Vaters, ich konnte ihn nicht sehen, aber ich fühlte ihn mit meinem ganzen Herzen.";
			link.l1 = "Mein Triumph endete damit, dass ich am ersten Tag auf dem Weg nach Guadeloupe aus dem Rigg fiel.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.TakeFolke")) {
				link.l1 = link.l1+" Mein Steuermann, Deluc, hatte auch einen sehr aussagekräftigen Blick."}
			link.l1.go ="trinkend_mein_Hintergrund_7";
		break;
		
		case "drinking_my_background_7":
			dialog.text = "Ah-ha-ha! Das kann ich mir vorstellen! Keine Sorge, das ist schon lange her, jetzt bist du ein echter Seewolf!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_8";
		break;
		
		case "drinking_my_background_8":
			dialog.text = "Auf unsere Triumphe!";
			link.l1 = "Hört, hört!";
			link.l1.go = "drinking_my_background_12";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "... Und dann bin ich nach und nach aufgestiegen, habe mit meinem Vater und den Offizieren am Tisch des Kapitäns gesessen und mich beraten. Ich lernte eine Menge. Ab meinem fünfzehnten Lebensjahr nahmen sie mich auf Feldzüge mit, und in meiner ersten Schlacht habe ich einen Mann getötet. Es war ein ekelhafter Feldzug, wir hätten nicht an einem Montag in See stechen sollen... Das wäre wirklich nicht nötig gewesen!";
			link.l1 = "Mit fünfzehn? Du machst mir Angst, Helen.";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_12":
			dialog.text = "Ich habe nicht einmal verstanden, was passiert ist. Der holländische Händler hatte seine Vorhut - Söldner der Kompanie. Sie beschlossen mutig zu sein und griffen unser Achterdeck an. Und ich, ein Nar, ohne jede Angst um mein Leben, steckte meinen blonden Kopf heraus. Ich wurde sofort mit dem Schaft einer Pistole getroffen. Aber einen Moment davor gelang es mir, meinen Degen in einen Narren der Kompanie zu stecken.";
			link.l1 = "Großer Gott, was ist mit Sean? Wie hat er dich nach dem nicht an Land getreten?";
			link.l1.go = "drinking_my_background_13";
		break;
		
		case "drinking_my_background_13":
			dialog.text = "Mein Vater kam auch nicht unversehrt aus dieser Schlacht heraus, und der Anblick meines gebrochenen dummen Kopfes half sicherlich nicht. Er begann langsam zu verfallen, und wahrscheinlich bemerkte niemand außer mir. Und dann war er weg. Laut seinem Willen erbte ich die Rainbow mit ihrer Besatzung und genug Mitteln, um das Schiff ein Jahr lang über Wasser zu halten.";
			link.l1 = "Und hat die Mannschaft dich als Kapitän akzeptiert?";
			link.l1.go = "drinking_my_background_14";
		break;
		
		case "drinking_my_background_14":
			dialog.text = "Wir leben nicht in einem Märchen, mein Kapitän. Einige haben das Testament meines Vaters feindselig aufgenommen - die Dinge haben eine unangenehme Wendung genommen\nWenn auch nur ein Seemann die Rainbow verlassen hätte, um sich zu weigern, unter meinem Kommando zu dienen, wäre das sehr schlecht für mein Image gewesen. Aber Svensson griff ein und richtete alle auf. Niemand verließ die Crew offen... damals. Sieben Jahre lang befehligte ich meine Schönheit, transportierte zweifelhafte Güter für den Forest Devil, suchte nach Schätzen, lebte... Aber jetzt ist das alles Vergangenheit.";
			link.l1 = "Nicht in der Vergangenheit. Ich glaube, du bist dazu bestimmt, wieder unter deiner eigenen Flagge zu segeln! Lasst uns darauf trinken!";
			link.l1.go = "drinking_my_background_sea";
			link.l2 = "Wir können das Schiff vielleicht nicht zurückholen, aber dein Degen ist immer noch bei dir.";
			link.l2.go = "drinking_my_background_land";
		break;
		
		case "drinking_my_background_sea":
			dialog.text = "Du weißt, wenn du es so sagst, glaube ich es auch. Lass uns trinken!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_COMMERCE, 5);
			AddCharacterSkill(npchar, SKILL_ACCURACY, 5);
			AddCharacterSkill(npchar, SKILL_CANNONS, 5);
			AddCharacterSkill(npchar, SKILL_SAILING, 5);
			AddCharacterSkill(npchar, SKILL_REPAIR, 5);
			AddCharacterSkill(npchar, SKILL_GRAPPLING, 5);
			AddCharacterSkill(npchar, SKILL_DEFENCE, 5);
			notification("Naval Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "sea";
		break;
		
		case "drinking_my_background_land":
			dialog.text = "Aber wird mein Degen mir Glück bringen? Die Antwort liegt wahrscheinlich irgendwo auf dem Grund dieses Bechers. Lasst uns trinken!";
			link.l1 = "";
			link.l1.go = "drinking_my_background_15";
			
			AddCharacterSkill(npchar, SKILL_F_LIGHT, 5);
			AddCharacterSkill(npchar, SKILL_FENCING, 5);
			AddCharacterSkill(npchar, SKILL_F_HEAVY, 5);
			AddCharacterSkill(npchar, SKILL_PISTOL, 5);
			AddCharacterSkill(npchar, SKILL_FORTUNE, 5);
			AddCharacterSkill(npchar, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(npchar, SKILL_SNEAK, 5);
			notification("Personal Skills +", "Helena");
			
			pchar.questTemp.HelenDrinking.Background = "land";
		break;
		
		case "drinking_my_background_15":
			dialog.text = "Ich habe über dein Leben in Europa nachgedacht... Schau, du bist ein Stadtmensch und ich bin nur ein gewöhnliches Mädchen, aber wir haben uns bereits in der gefährlichsten Ecke der Welt einen Namen gemacht.";
			link.l1 = "Klingt wie ein Trinkspruch! Also, gibt es etwas, das uns vereint?";
			link.l1.go = "drinking_my_background_16";
		break;
		
		case "drinking_my_background_16":
			dialog.text = "Nun, ich stehe auf den Schultern meines Vaters. Ich weiß nicht, wie es bei dir ist, aber vielleicht hat deine Familie auch nicht weniger Einfluss auf dich gehabt? Vielleicht hast du es noch nicht realisiert?";
			link.l1 = "Ich werde meinen lieben Bruder fragen, sobald ich ihn aus dem Gefängnis hole.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TavernEmpty");
		break;
		
		case "drinking_game":
			dialog.text = "Nun, das war's, mein Kapitän. Wir haben Geschichten ausgetauscht, Zeit, die Nacht zu beenden.";
			link.l1 = "Hmm, ich hatte auf ein anderes Ende des Abends gehofft.";
			link.l1.go = "drinking_game_1";
		break;
		
		case "drinking_game_1":
			dialog.text = "Die Nacht ist noch nicht vorbei. Ich schlage ein Spiel vor: Wenn du deine Karten richtig spielst, werden vielleicht deine Gebete erhört.";
			link.l1 = "Wir spielen Karten? Ich bin dabei!";
			link.l1.go = "drinking_game_2";
		break;
		
		case "drinking_game_2":
			dialog.text = "Ruhig, Seewolf. Ich werde kein Strip-Poker mit dir spielen.";
			link.l1 = "Ja, du hast recht, Helen. Wir haben hier keine Privatsphäre.";
			link.l1.go = "drinking_game_3";
		break;
		
		case "drinking_game_3":
			dialog.text = "Das ist nicht das Einzige, was wir nicht haben, Charles... Es ist kein Kartenspiel, aber mach dir keine Sorgen, ich wette, du bist ein Meister darin. 'Ich habe nie' - hast du davon gehört?";
			link.l1 = "Ist mir bekannt. Aus dem früheren Leben. Und spielst du es oft?";
			link.l1.go = "drinking_game_4";
		break;
		
		case "drinking_game_4":
			dialog.text = "Immer gewollt zu versuchen, aber hatte niemanden zum Spielen.";
			link.l1 = "Das ist ein ziemlich kühnes Spiel für unseren ersten gemeinsamen Drink. Bist du sicher?";
			link.l1.go = "drinking_game_5";
			link.l2 = "Apropos, wo sind alle? Sind wir hier alleine?";
			link.l2.go = "drinking_game_6";
		break;
		
		case "drinking_game_5":
			dialog.text = "Ja, nach den letzten Ereignissen, muss ich ein wenig leben. Etwas Dummes tun, weißt du?";
			link.l1 = "Nein, es endet immer schlecht, Rumba.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "Lass uns anfangen! Damen zuerst!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_6":
			dialog.text = "Schickte sie alle nach Hause - kein Grund, Außenstehenden zu erlauben, zu belauschen.";
			link.l1 = "Nein, es endet immer schlecht, Rumba.";
			link.l1.go = "drinking_game_refuse";
			link.l2 = "Lass uns das tun! Damen zuerst!";
			link.l2.go = "drinking_game_accept";
		break;
		
		case "drinking_game_refuse":
			dialog.text = "Schade, aber vielleicht hast du recht. Noch ein Getränk dann?";
			link.l1 = "Lass uns anfangen! Damen zuerst!";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_refuse_1":
			dialog.text = "Ich habe es arrangiert - das Zimmer oben gehört dir. Es war von einem wichtigen französischen Offizier besetzt, aber die Jungs vom Forest Devil haben ihn höflich gebeten, den Platz zu räumen. Geh und schlaf ein wenig - Ich werde dich nicht auf der Straße herumirren lassen, oder noch schlimmer, in diesem Zustand aufs Meer hinausgehen lassen.";
			link.l1 = "Ja, gnädige Frau!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToTavernRoom");
		break;
		
		case "drinking_game_accept":
			dialog.text = "Ha! Hic! Das heißt, du fängst an!";
			link.l1 = "Vorsichtig, Liebling! Hmm. Ich habe noch nie Ratten im Laderaum gejagt!";
			link.l1.go = "drinking_game_accept_1";
		break;
		
		case "drinking_game_accept_1":
			dialog.text = "So ist das also? Bei dir muss man auf der Hut sein! (Trinkt)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_2";
		break;
		
		case "drinking_game_accept_2":
			dialog.text = "Brr! Nur die Erinnerung daran... Nun, mache dich bereit, hübscher: Ich bin noch nie von den Rahen gefallen!";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_3";
		break;
		
		case "drinking_game_accept_3":
			dialog.text = "";
			link.l1 = "Nicht Schlecht! Erlauben Sie mir, Mademoiselle, auf Sie zu trinken! (Trinkt)";
			link.l1.go = "drinking_game_accept_4";
		break;
		
		case "drinking_game_accept_4":
			dialog.text = "";
			link.l1 = "Ich war noch nie abergläubisch.";
			link.l1.go = "drinking_game_accept_5";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 1;
			SetCamShuttle(loadedLocation);
			SetPitch(0.95);
		break;
		
		case "drinking_game_accept_5":
			dialog.text = "Und du nennst dich einen Seemann! Du weißt ganz genau, was für Leute wir sind. Man weiß nie, was die Reise bringt, weiß nicht, wann und wo man Land sieht, wenn überhaupt. Man muss Antworten jenseits von Karten und Navigationswerkzeugen suchen! Auf dein Wohl! (Trinkt)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_6";
		break;
		
		case "drinking_game_accept_6":
			dialog.text = "Und die Mädchen, die du persönlich gemalt hast... Hat ihnen das Ergebnis gefallen?";
			link.l1 = "Sie mochten die Gemälde nicht immer, aber, ähm... das Ergebnis - immer.";
			link.l1.go = "drinking_game_accept_7";
		break;
		
		case "drinking_game_accept_7":
			dialog.text = "Charles! Hätten wir uns damals getroffen, hätte ich dich erschossen oder als Geisel für Lösegeld genommen. Und übrigens, ich habe noch nie Pinsel in die Hand genommen.";
			link.l1 = "He! Nun, das ist völlig banal. Liebe Helen, wenn ich anfange Dinge aufzulisten, die du nie in Angriff genommen hast...";
			link.l1.go = "drinking_game_accept_8";
		break;
		
		case "drinking_game_accept_8":
			dialog.text = "Gut, gut, ich spiele fair. Dein Zug, mein Kapitän.";
			link.l1 = "(Schlürft) Hic! Hmm...Noch nie hat mir ein Model mit dem Griff einer Pistole auf den Kopf geschlagen.";
			link.l1.go = "drinking_game_accept_9";
		break;
		
		case "drinking_game_accept_9":
			dialog.text = "(Schluckt) Ugh. Wir spielen dieses Spiel falsch, Liebling. Ich dachte, wir würden trinken und uns kennenlernen, aber stattdessen tauschen wir Sticheleien aus und... und... Hic. Verdammt!";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_10";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 2;
			SetCamShuttle(loadedLocation);
			SetPitch(0.90);
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "Lassen wir es interessanter machen! Und vorzugsweise etwas, worüber wir nicht vor einer Stunde gesprochen haben!";
			link.l1 = "Ich bin noch nie nach einem Trinkgelage an einem unbekannten Ort aufgewacht.";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_10":
			dialog.text = "Autsch! Verdammt, Charles! (Trinkt)";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_11";
		break;
		
		case "drinking_game_accept_11":
			dialog.text = "Ich... Hic... kann es nicht glauben. Ich gestehe, schuldig - der kleine Rumba hat früher den Boden berührt. Aber ich bin noch nie im Gefängnis gewesen!";
			link.l1 = "Wie hast du...?";
			link.l1.go = "drinking_game_accept_12";
		break;
		
		case "drinking_game_accept_12":
			dialog.text = "Hahaha! Trink, trink!";
			link.l1 = "Ich werde das bereuen. (Trinkt)";
			
			if (IsCharacterEquippedArtefact(pchar, "totem_01")) {
				link.l1.go = "drinking_game_accept_13";
			} else {
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_LightsOut");
			}
		break;
		
		case "drinking_game_accept_13":
			dialog.text = "Komm schon, mein Liebling. Die letzte Frage und die letzte Chance, mich zu übertrumpfen!";
			link.l1 = "Nein... Ich... Lass uns etwas frische Luft schnappen.";
			link.l1.go = "drinking_game_enough";
			link.l2 = "Ich habe oft getrunken, aber nie so... Ich war noch nie so betrunken mit einem Mädchen. Bei meinem W-Wort, Trinken ist wirklich eine g-große Sünde...";
			link.l2.go = "drinking_game_accept_14";
			
			LAi_Fade("", "");
			pchar.GenQuest.CamShuttle = 3;
			SetCamShuttle(loadedLocation);
			SetPitch(0.85);
		break;
		
		case "drinking_game_enough":
			dialog.text = "Eh!";
			link.l1 = "";
			link.l1.go = "drinking_game_refuse_1";
		break;
		
		case "drinking_game_accept_14":
			dialog.text = "";
			link.l1 = "W-warte... Du trinkst nicht?";
			link.l1.go = "drinking_game_accept_15";
		break;
		
		case "drinking_game_accept_15":
			dialog.text = "Ach-ha-ha! Das ist zum Totlachen! Du hast hohe Ziele, mein Kapitän. Lass es... hic!... dir bekannt sein...";
			link.l1 = "";
			link.l1.go = "drinking_game_accept_16";
		break;
		
		case "drinking_game_accept_16":
			dialog.text = "Dass ich das Unglück habe, in einer rein männlichen Crew zu leben, und ich muss mich vorsichtig verhalten. Ich bin ein ehrliches Mädchen.";
			link.l1 = "Ich bin gl-glücklich für dich, H-Helen.";
			link.l1.go = "drinking_game_accept_17";
		break;
		
		case "drinking_game_accept_17":
			dialog.text = "Du wirst noch glücklicher sein, weil ich gewonnen habe! Aber um ehrlich zu sein, ich habe mich auch noch nie so mit einem Kerl betrunken.";
			link.l1 = "(Schweigend nimmt einen Schluck) A-auf dich. Glückwünsche... h-hicks...";
			link.l1.go = "drinking_game_accept_18";
		break;
		
		case "drinking_game_accept_18":
			dialog.text = "He-he-he! Kapitän, wohin gehst du? Beleidigt, vielleicht?";
			link.l1 = "Ich b-brauche... eine Pause? Ich gehe nur mein S-schwert suchen...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_ExitTavern");
		break;
		
		case "drinking_at_svenson":
			dialog.text = "Kapitän, bist du bereit? Es gibt kein Zurück mehr, und wenn etwas schief geht, werde ich dich zwingen, mich zu heiraten.";
			link.l1 = "Puh! Lass mich wenigstens etwas frische Luft schnappen! Bist du sicher, Helen?";
			link.l1.go = "drinking_at_svenson_1";
		break;
		
		case "drinking_at_svenson_1":
			dialog.text = "Ja, verdammt, und steh nicht da wie ein Pfahl! Ich muss mich verlieren, wenn auch nur für eine Nacht!";
			link.l1 = "Ich fürchte, nach dieser Nacht werde ich derjenige sein, der sich verlieren will. Lass uns gehen, bevor wir die ganze Stadt aufwecken.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_EnterSvenson");
		break;
		
		case "drinking_give_key":
			dialog.text = "Kapitän, nimm den Schlüssel und geh die Treppe hinauf. Dort sollte eine Truhe stehen; du hast sie wahrscheinlich gesehen, als Svensson sie hatte. Nimm das Fass und geh sofort zurück.";
			link.l1 = "Halte ein, Liebling, warum muss ich deinen Chef ausrauben?";
			link.l1.go = "drinking_give_key_1";
			
			GiveItem2Character(pchar, "key3");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_give_key_1":
			dialog.text = "Sei nicht dumm. Ich bin seit meiner Kindheit hier, wenn die Besitzer zurückkommen, kann ich das regeln und für dich einspringen. Komm schon, nimm jetzt nicht die Segel runter!";
			link.l1 = "Scharf wie ein Messer, ein wahrer Schmuggler! Warte, ich werde schnell sein.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GotKey");
		break;
		
		case "drinking_got_whiskey":
			dialog.text = "Hast du es verstanden?";
			link.l1 = "Klar doch! Nicht die erste Truhe, die ich geleert habe, und sicherlich nicht die letzte!";
			link.l1.go = "drinking_got_whiskey_1";
		break;
		
		case "drinking_got_whiskey_1":
			dialog.text = "Ich bin stolz auf dich! Haha! Erstklassiger irischer Whiskey, 'Bushmills'! Solch einen Trank würden sie uns in der Kneipe nicht servieren.";
			link.l1 = "Klingt gut, aber wird Svensson nicht bemerken, dass es fehlt?";
			link.l1.go = "drinking_got_whiskey_2";
		break;
		
		case "drinking_got_whiskey_2":
			dialog.text = "Er wird es sicher bemerken, aber er trinkt es nicht selbst. Es scheint, er hat es als Geschenk für seinen Piratenkumpel Dodson aufgehoben, und Dodson ist entweder verschwunden oder hat jemanden umgebracht...";
			link.l1 = "Das ist schrecklich! So ein Geschenk darf auf keinen Fall verschwendet werden. Greif das Fass und lass uns die Szenerie ändern!";
			link.l1.go = "drinking_got_whiskey_3";
		break;
		
		case "drinking_got_whiskey_3":
			dialog.text = "Gut gesagt, Käpt'n. Noch eine Sache - sag mal, hast du noch etwas aus der Truhe genommen? Antworte ehrlich.";
			if (HelenDrinking_RobbedSvenson()) {
				link.l1 = "Habe noch etwas genommen, eine Gewohnheit, verstehst du.";
				link.l1.go = "drinking_got_whiskey_notbelieve";
			}
			
			link.l2 = "Nein. Ich bin mir nicht sicher, ob ich ein Pirat bin, aber ich bin definitiv kein Dieb.";
			link.l2.go = "drinking_got_whiskey_believe";
			
			if (HelenDrinking_RobbedSvenson()) {
				link.l2.go = "drinking_got_whiskey_notbelieve";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 2;
				notification("Helen disapproves", "Helena");
				pchar.questTemp.HelenDrinking.RobbedSvenson = true;
			}
		break;
		
		case "drinking_got_whiskey_believe":
			dialog.text = "Irgendwie glaube ich dir... die Närrin, die ich bin!";
			link.l1 = "";
			link.l1.go = "drinking_get_out";
		break;
		
		case "drinking_got_whiskey_notbelieve":
			dialog.text = "Geh und stell sicher, dass du aus irgendeinem Grund nichts mitgenommen hast.";
			link.l1 = "";
			link.l1.go = "exit";
			if (!HelenDrinking_RobbedSvenson()) {
				AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
				TakeItemFromCharacter(pchar, "cask_whisky");
				sld = ItemsFromID("cask_whisky");
				sld.price = sld.pricebak;
				DeleteAttribute(sld, "pricebak");
			}
			
			NextDiag.TempNode = "drinking_got_whiskey_notbelieve";
		break;
		
		case "drinking_get_out":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_JoanEnter");
			TakeItemFromCharacter(pchar, "cask_whisky");
			sld = ItemsFromID("cask_whisky");
			sld.price = sld.pricebak;
			DeleteAttribute(sld, "pricebak");
		break;
		
		case "drinking_at_fort":
			dialog.text = "He, he, Liebling! Konzentrier dich! Mein Gesicht, geküsst von der Meeresbrise, ist genau hier!";
			link.l1 = "Puh, nun, dein Kostüm ist etwas! Du musst viel Geld für Nähmaterial gespart haben. Und ich... hic! Ich habe viel gesehen! Aber das... Aber das ist das Beste, was ich gesehen habe.";
			link.l1.go = "drinking_at_fort_1";
			locCameraFromToPos(-1.65, 44.45, 76.64, true, -5.93, 42.10, 70.13);
		break;
		
		case "drinking_at_fort_1":
			dialog.text = "Jeder sagt das, aber aus irgendeinem Grund glaube ich dir! Magst du es wirklich?";
			link.l1 = "Nun, natürlich betont es sehr vorteilhaft deine Figur, obwohl...";
			link.l1.go = "drinking_at_fort_2";
		break;
		
		case "drinking_at_fort_2":
			dialog.text = "Oh, jetzt hast du alles ruiniert!";
			link.l1 = "... obwohl ich keinen Zweifel daran habe, dass es unter den gewöhnlichen Leuten Ehrfurcht einflößt!";
			link.l1.go = "drinking_at_fort_3";
		break;
		
		case "drinking_at_fort_3":
			dialog.text = "Ich bewundere eher diese seltsame weit verbreitete Gewohnheit unter dem gemeinen und nicht so gemeinen Volk, dichte europäische Kleidung in dieser Hitze zu tragen. Dadurch sehen unsere Dörfer noch komischer aus... Ich mag mein Outfit, Charles. Darin fühle ich mich schön, und das ist für eine Frau wichtig.";
			link.l1 = "Du würdest genauso schön bleiben, auch ohne dieses Outfit, Helen.";
			link.l1.go = "drinking_at_fort_4";
		break;
		
		case "drinking_at_fort_4":
			dialog.text = "Sei vorsichtig, mein Kapitän! Solche süßen Worte könnten ein armes Mädchen verderben!";
			link.l1 = "Wenn sie nichts dagegen hat, dann habe ich auch nichts dagegen.";
			link.l1.go = "drinking_at_fort_5";
		break;
		
		case "drinking_at_fort_5":
			dialog.text = "Hee-hee! Frag mich lieber etwas anderes. Ich mag es, wenn du neugierig wirst.";
			link.l1 = "Dann lassen Sie uns eine Frage zu deiner Kostümierung einbringen. Ich glaube nicht, dass Seehunde einen Kapitän in solch einer Aufmachung ernst nehmen können.";
			link.l1.go = "drinking_at_fort_6";
		break;
		
		case "drinking_at_fort_6":
			dialog.text = "Und ich glaube nicht, dass Seehunde im Allgemeinen eine Frau als Kapitänin sehen können, also hat meine Kleidung wahrscheinlich nicht zu meinen Problemen beigetragen. Oder vielleicht hat sie noch keine Zeit gehabt hinzuzufügen, da es etwas Neues ist. Ich habe es selbst genäht!\nAh-ha-ha! Ich trug früher eines von denen... wie nennt man sie? Unser Militär trägt sie immer noch! B-r-r... Eines davon jetzt zu sehen, macht mich krank.";
			link.l1 = "Uniformen?";
			link.l1.go = "drinking_at_fort_7";
		break;
		
		case "drinking_at_fort_7":
			dialog.text = "Oh, genau, eine Uniform! Eine rote Uniform! Wie der Kerl dort sie trägt.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.GenQuest.BlockDialogCamera = true;
			AddDialogExitQuestFunction("HelenDrinking_OfficerAtFort");
		break;
		
		case "drinking_at_fort_7_1":
			dialog.text = "Oh, es tut mir leid, Major, lassen Sie mich Ihnen mit etwas feinem irischem Whisky als... hic!... Entschuldigung einladen.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog2");
		break;
		
		case "drinking_at_fort_7_2":
			dialog.text = "Charles wird doch nicht in Schwierigkeiten geraten, oder, Major? Sag mir, dass er es nicht wird, bitte!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog4");
		break;
		
		case "drinking_at_fort_8":
			dialog.text = "Ich bin so froh! Lasst uns trinken!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToVillage");
		break;
		
		case "drinking_at_miskito":
			dialog.text = "Ugh. Schau mal, was ich habe!";
			link.l1 = "Helen... Planst du das... um deine Stimmung zu heben?!.. Denk nicht mal dran! Tollkirsche kann eine Person völlig überwältigen, ihre Kräfte ausschöpfen, ihren Willen brechen! Bevor du es merkst, bist du ein lebender Leichnam und dann sehr schnell ein toter...";
			link.l1.go = "drinking_at_miskito_1";
		break;
		
		case "drinking_at_miskito_1":
			dialog.text = "Charles, aber... gerade jetzt...";
			link.l1 = "Keine Widersprüche. Es tut mir leid, dass ich so streng bin, aber das ist kein Scherz. Ich nehme dir das weg. Kann nicht glauben, was du dir gedacht hast... Hier, trink das und komm wieder zu dir.";
			link.l1.go = "drinking_at_miskito_2";
			
			GiveItem2Character(pchar, "cannabis7");
			PlaySound("interface\important_item.wav");
		break;
		
		case "drinking_at_miskito_2":
			dialog.text = "Es tut mir leid, Charles. Du hast absolut recht, ich weiß. Ein momentane Schwäche. Es wird nicht wieder passieren. Danke, dass du mich vor der Versuchung des Teufels gerettet hast...";
			link.l1 = "Lassen wir das... Jetzt sag mir, wie hast du es geschafft, Respekt in der Stadt zu erlangen, gute Beziehungen zu den Offizieren der Garnison zu pflegen und dich mit den Einheimischen anzufreunden?";
			link.l1.go = "drinking_at_miskito_3";
		break;
		
		case "drinking_at_miskito_3":
			dialog.text = "Sie respektieren Svensson, und einiges davon färbt auf mich ab. Unsere kleine Stadt überlebt einzig und allein durch Jans Geschäfte. Er teilt einen Teil der Gewinne aus seinen Kakaoplantagen mit den Rotröcken, und die Miskito schulden ihm ihren gesamten Lebensunterhalt.";
			link.l1 = "Wie ist das passiert?";
			link.l1.go = "drinking_at_miskito_4";
		break;
		
		case "drinking_at_miskito_4":
			dialog.text = "Als die Kastilier die Kontrolle hatten, störten sie die Indianer kaum. Aber nachdem sie die edlen Hidalgos rausgeworfen haben, haben unsere Leute beschlossen, die Kontrolle über die lokalen Wälder zu übernehmen. Jan hat die Sache damals ganz entschieden gelöst - hat sogar Leute nach London geschickt! Natürlich nicht aus Güte seines Herzens: Kakao in einem Wald zu gewinnen, in dem jeder Busch dich hasst, ist ein hoffnungsloses Unterfangen. Aber jetzt helfen die Indianer Jan nicht nur beim Schmuggel von Porto Bello nach Blueweld, sondern fällen auch ihre eigenen Wälder für einen Apfel und ein Ei. Bravo, Forest Devil, bravo!";
			link.l1 = "Es klingt, als ob Sie seine Methoden nicht ganz billigen.";
			link.l1.go = "drinking_at_miskito_5";
		break;
		
		case "drinking_at_miskito_5":
			dialog.text = "Ich liebe und respektiere das Miskito Volk, aber ich respektiere auch Jans Strategie. Wir leben nicht in einem Märchen, mein Kapitän.";
			link.l1 = "Hm... Ich sehe, deine Beziehung zu Svensson ist komplizierter als es auf den ersten Blick scheint...";
			link.l1.go = "drinking_at_miskito_6";
		break;
		
		case "drinking_at_miskito_6":
			dialog.text = "Sogar mehr, als du weißt. Seine Frau hat einen guten Grund, mir gegenüber giftig zu sein... Jan hat ein Auge auf mich geworfen, seit ich etwa fünfzehn war. Das war ungefähr zu der Zeit, als ich anfing, gleichberechtigt auf den Decks der Rainbow zu wandeln, und anscheinend hat es damals im Kopf des Forest Devils Klick gemacht... Aber ich habe schon zu viel gesagt, mein Kapitän. Wir sollten dieses Thema nicht weiter vertiefen, es ist nicht sehr anständig, über unseren Gönner zu tratschen.";
			link.l1 = "Dann ändern wir das Thema. Ich wollte sagen, dass du offensichtlich in diese Gesellschaft passt und sie dich als einen der ihren betrachten.";
			link.l1.go = "drinking_at_miskito_7";
		break;
		
		case "drinking_at_miskito_7":
			dialog.text = "Es stellt sich heraus, dass es für mich viel einfacher ist, in der Gesellschaft von Indianern, Zigeunern und anderen anständigen Außenseitern zu sein. Mamas Eintöpfe, Strandlagerfeuer und den Laufgang auf der Rainbow - Ich habe mir eine gemütliche kleine Welt aufgebaut, Kapitän. Schade, dass alles zusammenbrach, gerade als ich dachte, ich hätte alles herausgefunden.";
			link.l1 = "Das Fass ist fast leer... Eine letzte Runde?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoToShipyard");
		break;
		
		case "drinking_at_perlas":
			dialog.text = "Es ist so schön... Ich bin froh, dass du zugestimmt hast, Zeit mit mir zu verbringen, Kapitän. Ich brauchte das wirklich. Ich glaube, du auch.";
			link.l1 = "Ja, es ist eine Weile her, seit ich mich so entspannt habe. Das wird etwas zum Erinnern sein!";
			link.l1.go = "drinking_at_perlas_1";
		break;
		
		case "drinking_at_perlas_1":
			dialog.text = "Du denkst wahrscheinlich, der Teufel weiß was über mich gerade jetzt. Ich bin von Natur aus eine sehr verschlossene Person, Charles. Ich wollte nur... verdammt, ich wollte mich einfach lebendig fühlen! Wollte nur mit jemandem reden!";
			link.l1 = "Was ist mit Gladys? Jan?";
			link.l1.go = "drinking_at_perlas_2";
		break;
		
		case "drinking_at_perlas_2":
			dialog.text = "Alles, was Mutter tut, ist weinen, und Jan scheint jetzt eine andere Person zu sein. Vielleicht bilde ich mir Dinge ein, ich weiß es nicht, aber es ist, als ob er sich jetzt für mich schämt? Verzeih mir, ich... (schnieft).\nDas reicht, altes Mädchen. Entschuldigung, ich habe mich ein wenig hinreißen lassen.";
			link.l1 = "Es besteht keine Notwendigkeit sich zu entschuldigen. Ich verstehe alles, oder zumindest denke ich das.";
			link.l1.go = "drinking_at_perlas_3";
		break;
		
		case "drinking_at_perlas_3":
			dialog.text = "Ich sage das alles, weil wir uns gerade erst kennengelernt haben, und ich bin es nicht gewohnt, selbst mit denen, die ich schon lange kenne, so offen zu sein. Man nennt mich Rumba, angeblich wegen meines Charakters, aber wie du sehen kannst, ist das ein Fehlname. Ist der Schnaps alle?";
			link.l1 = "Vor einer Weile, und die Morgendämmerung bricht bereits an.";
			link.l1.go = "drinking_at_perlas_4";
		break;
		
		case "drinking_at_perlas_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend") && !CheckAttribute(pchar, "questTemp.HelenDrinking.RobbedSvenson")) {
				dialog.text = "Es tut mir leid, mein Kapitän, wenn Sie andere Erwartungen an unseren Abend hatten. Ich... Ich kann nicht. Nicht heute.";
			} else {
				dialog.text = "Dann danke ich dir für den Abend, Kapitän. Wer weiß, vielleicht wiederholen wir das noch einmal.";
			}
			link.l1 = "Natürlich, Helen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_PoormanTalk");
		break;
		
		case "ambush":
			dialog.text = "Danke, dass du mich hierher gebracht hast, Kapitän. Lass uns umsehen, nicht wahr? Untersuchen wir mein Erbe.";
			link.l1 = "Bist du nicht schon mal hier gewesen?";
			link.l1.go = "ambush_1";
		break;
		
		case "ambush_1":
			dialog.text = "Nein, das ist ziemlich weit weg, außerdem bin ich kein Pirat. Dieser Ort war noch nie besonders faszinierend, und nachdem sie Blaise getötet haben... Es ist besser, sich hier nicht aufzuhalten.";
			link.l1 = "Werden wir nicht. Ich bereue es bereits, dich hierher gebracht zu haben.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPrepareAmbush");
		break;
		
		case "after_ambush":
			switch (pchar.questTemp.HelenDrinking.IslaTesoroAmbush) {
				case "A":
					if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB") && !CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC")) {
						dialog.text = "Musstest du das tun, Kapitän? Warum so schnell zum Kampf? Nun, man sollte nicht nur einen Gewinner haben, denke ich. Kommen Sie, wir sehen uns die Residenz an, hier gibt es sowieso nichts Sehenswertes mehr.";
						pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
						notification("Helen disapproves", "Helena");
					} else {
						dialog.text = "Hut ab, mein Kapitän, dass Sie versucht haben, das Problem klug zu lösen, bevor Sie sich auf einen Kampf einlassen. Komm wir sehen uns die Residenz an, hier gibt es sowieso nichts Sehenswertes mehr.";
					}
					
					link.l1 = "Was ist mit diesem riesigen Schiff, das an Land gezogen wurde?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "B":
					dialog.text = "Du hast diese Narren gekonnt getäuscht, mein Kapitän! Ich habe mich fast kaputtgelacht, ehrlich! Komm wir sehen uns die Residenz an, hier gibt es sowieso nichts Sehenswertes mehr.";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					notification("Helen approves", "Helena");
					
					link.l1 = "Was ist mit diesem riesigen Schiff, das an Land gezogen wurde?";
					link.l1.go = "after_ambush_1";
				break;
				
				case "C":
					dialog.text = "Halt ein, lass ein Mädchen Luft holen! Bist du wirklich der Charlie Prinz?";
					pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
					notification("Helen approves", "Helena");
					
					link.l1 = "Ja, es gab eine solche Zeit in meiner Biographie. Bist du beeindruckt?";
					link.l1.go = "after_ambush_c";
				break;
			}
		break;
		
		case "after_ambush_1":
			dialog.text = "Ja, du hast recht. Ich würde es gerne erkunden, aber um ehrlich zu sein, Charles, habe ich irgendwie Angst davor. Lass uns gehen.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroGoToResidence");
		break;
		
		case "after_ambush_c":
			dialog.text = "Ach du meine Güte, ja! Erzähl mir später unbedingt alles, ja? Weil ich nur Geschichten gehört habe... sehr unanständige Geschichten!";
			link.l1 = "Ich werde dir alles erzählen... fast alles.";
			link.l1.go = "after_ambush_c_1";
		break;
		
		case "after_ambush_c_1":
			dialog.text = "Ich warte sehnsüchtig! Komm wir sehen uns die Residenz an, hier gibt es sowieso nichts Sehenswertes mehr.";
			link.l1 = "Was ist mit diesem riesigen Schiff, das an Land gezogen wurde?";
			link.l1.go = "after_ambush_1";
		break;
		
		case "ambush_inresidence":
			dialog.text = "Eine beengte, kalte Hütte mit absurden Forderungen. Ich fühle mich schon wie in einer Falle!";
			link.l1 = "Ich sehe, dass du bisher mit dem potenziellen Eigentum nicht zufrieden bist?";
			link.l1.go = "ambush_inresidence_1";
		break;
		
		case "ambush_inresidence_1":
			dialog.text = "Nein, Charles. Vielleicht bin ich zu pingelig, aber im Moment verkörpert es alles, was ich fürchte und hasse. Ich hoffe, ich werde es vermieten können... Obwohl, ich bin nicht sicher, wo ich das Geld ausgeben werde.";
			link.l1 = "Unterschätze nicht den Wert von Miete. Ich habe keine Miete, und oft muss ich mir Wege ausdenken, um meine Crew zu bezahlen. Du wirst dir ein neues Schiff kaufen, 'Rainbow II' - klingt gut, oder?!";
			link.l1.go = "ambush_inresidence_sea";
			link.l2 = "Es gibt viele Möglichkeiten, Geld für dich selbst auszugeben. Beginne mit einem personalisierten Schwert und einer Flasche ausgezeichnetem Wein. Gönn dir etwas, Helen, du hast es verdient.";
			link.l2.go = "ambush_inresidence_land";
		break;
		
		case "ambush_inresidence_sea":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "sea") {
				dialog.text = "Danke, mein Kapitän. Es freut mich, das zu hören. Besonders schön ist es, es zum zweiten Mal zu hören. Du kennst mich gut.";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 3;
				notification("Helen approves", "Helena");
			} else {
				dialog.text = "Danke dir, mein Kapitän. Es freut mich, das zu hören.";
			}
			
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_COMMERCE, 5);
			AddCharacterSkill(sld, SKILL_ACCURACY, 5);
			AddCharacterSkill(sld, SKILL_CANNONS, 5);
			AddCharacterSkill(sld, SKILL_SAILING, 5);
			AddCharacterSkill(sld, SKILL_REPAIR, 5);
			AddCharacterSkill(sld, SKILL_GRAPPLING, 5);
			AddCharacterSkill(sld, SKILL_DEFENCE, 5);
		break;
		
		case "ambush_inresidence_land":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Background") && pchar.questTemp.HelenDrinking.Background == "land") {
				dialog.text = "Glaubst du, dass ich es verdiene? Ich habe noch nie Geld für solche Kleinigkeiten ausgegeben, aber ich vermute, es gibt ein erstes Mal für alles. Ich sehe, du hörst nicht auf zu versuchen, mich das Meer vergessen zu lassen, hm, Kapitän? Vielleicht hast du recht...";
				pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 3;
				notification("Helen disapproves", "Helena");
			} else {
				dialog.text = "Glaubst du, ich verdiene es? Ich habe noch nie Geld für solche Kleinigkeiten ausgegeben, aber ich denke, es gibt ein erstes Mal für alles.";
			}
			link.l1 = "";
			link.l1.go = "ambush_inresidence_2";
			
			sld = CharacterFromID("Helena");
			
			AddCharacterSkill(sld, SKILL_F_LIGHT, 5);
			AddCharacterSkill(sld, SKILL_FENCING, 5);
			AddCharacterSkill(sld, SKILL_F_HEAVY, 5);
			AddCharacterSkill(sld, SKILL_PISTOL, 5);
			AddCharacterSkill(sld, SKILL_FORTUNE, 5);
			AddCharacterSkill(sld, SKILL_LEADERSHIP, 5);
			AddCharacterSkill(sld, SKILL_SNEAK, 5);
		break;
		
		case "ambush_inresidence_2":
			dialog.text = "Auf jeden Fall ist die Inspektion abgeschlossen. Hier scheint es keine Wertsachen zu geben - der Abschaum hat es schon geschafft, alles zu plündern, und ich bin sicher, dass das Obergeschoss in dem gleichen Zustand ist.";
			link.l1 = "Es ist, als hättest du dich verändert, Helen. Als wir das letzte Mal zusammen waren, warst du... ich weiß nicht, offener?";
			link.l1.go = "ambush_inresidence_3";
		break;
		
		case "ambush_inresidence_3":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Nichts hat sich geändert, mein Kapitän, aber viel ist auf die Schultern eines armen Mädchens gefallen, haha! Ich wollte dich nicht beleidigen. Ich muss gerade viele Dinge überdenken. Sie wissen, solche scharfen Wendungen im Leben passieren nicht jeden Tag. Und wir haben noch viel Zeit zusammen!";
				link.l1 = "Bin Froh das zu hören! Lass uns hier raus.";
			} else {
				dialog.text = "Es hat sich viel verändert, Kapitän. Ich fürchte, ich muss jetzt reifer sein und das Leben anders betrachten. Es ist kein Märchen über eine Prinzessin und ein Erbe, es geht um große Politik, und ich muss meinen Platz darin noch erkennen. Und der Platz meiner Familie auch.";
				link.l1 = "Ich bin froh, dass wir das geklärt haben. Lass uns hier raus.";
			}
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroBeforeExit");
		break;
		
		case "ambush_inresidence_wait":
			dialog.text = "Ja?";
			if (CheckCharacterItem(pchar, "pirate_cutlass")) {
				link.l1 = "Hey, nicht alles wurde geplündert! Schau, Helen! Dieser Säbel scheint legendär zu sein, wenn man bedenkt, dass selbst der lokale Abschaum gezögert hat, ihn einzustecken.";
				link.l1.go = "ambush_inresidence_give_cutlass";
			}
			
			link.l2 = "Nein, nichts.";
			link.l2.go = "exit";
			
			NextDiag.TempNode = "ambush_inresidence_wait";
		break;
		
		case "ambush_inresidence_give_cutlass":
			dialog.text = "Wow, das ist... der legendäre Krummsäbel des Blaise selbst! Die Piraten respektierten ihn zu sehr, um das Säbel nach seinem Tod aus seinem Haus zu nehmen. Sie nahmen natürlich das Geld und die Wertsachen, aber selbst die zukünftigen Galgenvögel haben Reste von Ehre...";
			link.l1 = "Es sieht so aus, als würde hier jemand aufräumen. Als ob der Besitzer zurückkommen würde... Das ist kein Haus, sondern eine Gedenkstätte!";
			link.l1.go = "ambush_inresidence_give_cutlass_1";
		break;
		
		case "ambush_inresidence_give_cutlass_1":
			dialog.text = "Danke für die scharfsinnige Beobachtung, Charles. Du hast diesen Ort in meinen Augen völlig ruiniert, ha-ha!";
			link.l1 = "Ich denke, dieser Säbel gehört jetzt dir. Blaise ist dein so genannter Onkel...";
			link.l1.go = "ambush_inresidence_give_cutlass_2";
		break;
		
		case "ambush_inresidence_give_cutlass_2":
			dialog.text = "Du fügst noch mehr Schrecken hinzu, mein Kapitän. Ich... Ich kann nicht. Ich fürchte, dass, wenn ich es akzeptiere, mein früheres Leben vollständig enden wird.";
			link.l1 = "Dann nimm es nicht als Teil des Erbes, sondern als Geschenk von einem gutaussehenden Mann.";
			link.l1.go = "ambush_inresidence_give_cutlass_3";
		break;
		
		case "ambush_inresidence_give_cutlass_3":
			dialog.text = "Wer könnte das sein? Nur ein Scherz! Danke, dass du meine düsteren Gedanken verscheucht hast, mein Kapitän. Ich verspreche, ich werde viel trainieren, um dieses Schwert würdig zu sein!";
			link.l1 = "Du bist einer feinsten Waffe würdig, Helen. Los geht's, wir sind hier fertig.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "give_cutlass":
			dialog.text = "Wahnsinn, das ist... der legendäre Säbel von Blaise selbst! Die Piraten respektierten ihn zu sehr, um den Säbel nach seinem Tod aus seinem Haus zu nehmen. Sie nahmen das Geld und die Wertsachen, natürlich, aber sogar die zukünftigen Galgenvögel haben Reste von Ehre\nIch... Ich kann nicht. Ich fürchte, dass, wenn ich es annehme, mein früheres Leben endgültig zu Ende gehen wird.";
			link.l1 = "Dann nimm es nicht als Teil des Erbes, sondern als Geschenk von einem gutaussehenden Mann.";
			link.l1.go = "give_cutlass_1";
		break;
		
		case "give_cutlass_1":
			dialog.text = "Wer könnte das sein? Nur ein Scherz! Danke, dass du meine dunklen Gedanken vertrieben hast, mein Kapitän.";
			link.l1 = "Du bist einer der feinsten Waffen würdig, Helen. Ich freue mich, dass es dir gefällt.";
			link.l1.go = "give_cutlass_2";
		break;
		
		case "give_cutlass_2":
			dialog.text = "Ich verspreche, ich werde viel trainieren, um dieser Klinge würdig zu werden!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GiveCutlass");
		break;
		
		case "arrive":
			dialog.text = "Mein Kapitän! Charlie!";
			link.l1 = "Charlie? Das ist neu! Schön dich zu sehen, Liebste.";
			link.l1.go = "arrive_1";
		break;

		case "arrive_1":
			dialog.text = "Ich habe aus Versehen einen Fehler gemacht, haha! Schön, dich auch zu sehen...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog1");
		break;

		case "arrive_2":
			dialog.text = "So viel zur schwesterlichen Solidarität! Mein Kapitän, ich... ich habe mir wirklich Sorgen gemacht und dich so sehr vermisst!";
			link.l1 = "Also, wofür musstest du nach Hause rennen?";
			link.l1.go = "arrive_3";
		break;

		case "arrive_3":
			dialog.text = "Zu... Oh, richtig! Ich habe ein kleines Geschenk für dich, hier!";
			link.l1 = "Drei Amulette... Helen, warum? Wolltest du mir folgen?";
			link.l1.go = "arrive_4";
			
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Indian);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Amulet);
			GiveItem2Character(pchar, pchar.questTemp.Saga.BaronReturn.Obereg);
		break;

		case "arrive_4":
			dialog.text = "Komm her, du Narr!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FirstKiss");
		break;

		case "after_kiss":
			dialog.text = "Nur wag es nicht, diesen Moment zu verderben - Ich habe ihn mein ganzes Leben lang vorgestellt!";
			link.l1 = "Ich werde nicht, Helen.";
			link.l1.go = "after_kiss_a";
			link.l2 = "Du hast dein ganzes Leben darauf gewartet, mich zu treffen? Ich fühle mich geschmeichelt!";
			link.l2.go = "after_kiss_b";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l3 = "Helen, es gibt etwas... Auf Justice Island, ich habe eine Frau getroffen, und...";
				link.l3.go = "after_kiss_c";
			}
			locCameraFromToPos(-19.00, 1.56, 19.07, true, -11.19, -0.90, 17.49);
		break;
		
		case "after_kiss_a":
			dialog.text = "Verdammt richtig! Du wirst mir alles erzählen, alles! Ich werde auf dem Schiff auf dich warten, mein Kapitän!";
			link.l1 = "Warte!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_b":
			dialog.text = "Dummkopf! Willst du mich beleidigen? Gut, ich bin beleidigt! Ha-ha! Ich gehe jetzt zum Schiff, bevor Danny sich noch mehr über mich lustig macht...";
			link.l1 = "Warte!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "after_kiss_c":
			dialog.text = "Dummkopf! Ich bat dich, den Moment nicht zu ruinieren! Eine Frau Getroffen... nun, du hast eine Frau getroffen - ich sehe noch keinen Ring an deinem Finger. Aber denk nicht, dass du damit durchkommst - ich werde auf eine detaillierte Geschichte warten, wenn du zum Schiff zurückkehrst.";
			link.l1 = "Warte!...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss1");
		break;
		
		case "loot_good":
			dialog.text = "Mein Kapitän, was gibt's Neues? An deinem blassen Gesicht kann ich erkennen, dass der Anwalt beschlossen hat, dir mehr Probleme zu bereiten, anstatt zu helfen.";
			link.l1 = "Du hast recht, Helen. Loxley verlangte einen beeindruckenden Vorschuss, und der Fall selbst wird mich ein hübsches Sümmchen kosten. Ich werde Jan durchschütteln - ich habe genug! Es ist, als hätte die Bruderschaft beschlossen, alle ihre Ausgaben auf mich abzuwälzen!";
			link.l1.go = "loot_good_1";
		break;
		
		case "loot_good_1":
			dialog.text = "Es steckt keine Bosheit dahinter, Charles. So sind sie eben - heben keinen Finger, es sei denn, sie müssen. Ich bin sicher, Jan wird dir helfen, und ich werde auch nicht untätig daneben stehen.";
			link.l1 = "Ich weiß, Helen. Sag mir, was du im Sinn hast.";
			link.l1.go = "loot_good_2";
		break;
		
		case "loot_good_2":
			dialog.text = "Ich habe früher für Jan gearbeitet - wertvolles Holz in ganz Maine geschmuggelt. Aber ich bin ein findiges Mädchen und habe während all dieser Reisen etwas für mich selbst beiseite gelegt.";
			link.l1 = "Und Jan hat nichts herausgefunden? Schlau!";
			link.l1.go = "loot_good_3";
		break;
		
		case "loot_good_3":
			dialog.text = "Ich hatte einen guten Schatzmeister. Kurz gesagt, ich habe eine anständige Menge Geld gesammelt und es nicht weit von hier versteckt. Gehst du jetzt zu Jan? Dann besuchen wir San Juan del Norte. In der Nähe gibt es eine Höhle, und wir brauchen nur ein paar Matrosen, die uns helfen, damit wir nicht alles selbst tragen müssen.";
			link.l1 = "Du hast schon an alles gedacht, nicht wahr? Danke, Helen, wir werden definitiv es besuchen, wenn wir die Zeit haben.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "loot_bad":
			dialog.text = "Mein Kapitän, was gibt's Neues? Ich kann an Deinem blassen Gesicht erkennen, dass der Anwalt sich entschieden hat, Dir mehr Probleme zu bereiten, anstatt zu helfen.";
			link.l1 = "Du hast recht, Helen. Loxley verlangte eine beeindruckende Vorauszahlung, und der Fall selbst wird mich ein hübsches Sümmchen kosten. Ich werde Jan durchschütteln - ich habe genug! Es ist, als ob die Bruderschaft beschlossen hätte, alle ihre Ausgaben auf mich zu übertragen!";
			link.l1.go = "loot_bad_1";
		break;
		
		case "loot_bad_1":
			dialog.text = "Dachtest du, du wärst in einem Märchen? Mach dir keine Sorgen, wir sitzen alle im selben Boot und ich werde dir helfen. Schließlich habe ich doch ein Anrecht auf ein Erbe, oder nicht?";
			link.l1 = "Das stimmt... Sag mir, was geht dir durch den Kopf!";
			link.l1.go = "loot_bad_2";
		break;
		
		case "loot_bad_2":
			dialog.text = "Ich habe etwas in San Juan del Norte versteckt. Es gibt eine Höhle in der Nähe - wir müssen nur ein paar Seemänner anheuern, damit wir nicht alles selbst tragen müssen.";
			link.l1 = "Du hast schon an alles gedacht, oder? Danke, Helen, wir werden auf jeden Fall vorbeikommen, wenn wir die Zeit haben.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_CreateLoot");
		break;
		
		case "shdn":
			dialog.text = "Das ist es, Charles! Aber du musst alleine gehen - ich hasse Höhlen!";
			link.l1 = "Wie alle geschlossenen Räume, das weiß ich, Helen. Warte hier auf mich.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GoForLoot");
		break;
		
		case "shdn_ambush":
			dialog.text = "Wir haben ein Problem! Eine Gruppe von Soldaten kommt auf uns zu, und sie sehen bedrohlich aus. Sei vorsichtig, Charles, es sind nicht nur gewöhnliche Küstenwachen - es ist auch ein französischer Offizier dabei! Ich bitte dich, mach bloß nichts Dummes!";
			link.l1 = "Wann habe ich jemals etwas Dummes getan?!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SpawnAmbushSoldiers");
		break;
		
		case "shdn_ambush_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6) {
				dialog.text = "Ha, die zweite Option klingt verlockender, aber ich hoffe, du bist nicht zu stolz auf dich selbst, Charles?";
			} else {
				dialog.text = "Kann nicht sagen, dass ich überrascht bin, Charles...";
			}
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog1");
		break;
		
		case "shdn_ambush_2":
			dialog.text = "Bist du fertig? Jetzt ist es an der Zeit, dass ich spreche!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_HelenKillFrancois");
		break;
		
		case "shdn_ambush_3":
			dialog.text = "Mein Name ist Helen MacArthur! Kapitän, du weißt, wer ich bin und für wen ich arbeite! Informiere deine Leute, besonders diesen feinen Idioten, der auf dem Boden liegt, über die heutigen Ergebnisse, die ich jetzt verkünden werde!";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "richard");
			sld = CharacterFromID("HelenDrinking_Richard");
			CharacterTurnByChr(sld, npchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath2");
		break;
		
		case "shdn_ambush_4":
			dialog.text = "Protest? Es ist mir egal, ob du an Cromwell selbst schreibst. Erstens hat Monsieur de Maure heute seine Ehre nicht verloren.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_5";
			CharacterTurnToLoc(npchar, "quest", "richard");
		break;
		
		case "shdn_ambush_5":
			dialog.text = "Zweitens, Oberst de Tavann wurde von einem Mädchen in einem sehr scharfen Outfit erschossen, weil er sie eine Dirne genannt hat.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_6";
		break;
		
		case "shdn_ambush_6":
			dialog.text = "Drittens, ziehst du sofort deine Soldaten zurück und vergisst, was passiert ist, es sei denn, du möchtest, dass der Forest Devil davon erfährt.";
			link.l1 = "";
			link.l1.go = "shdn_ambush_7";
		break;
		
		case "shdn_ambush_7":
			locCameraSleep(false);
			dialog.text = "Keine Fragen, sehe ich. Einen schönen Tag noch, Kapitän.";
			link.l1 = "Großer Gott, Helen, du brennst!";
			link.l1.go = "shdn_ambush_8";
		break;
		
		case "shdn_ambush_8":
			dialog.text = "Später, Charles. Lass uns verschwinden, bevor sie sich von dem Schock erholen. Ich zittere auch überall. Können wir in Blueweld sprechen?";
			link.l1 = "Einverstanden.";
			link.l1.go = "exit";
			CharacterTurnByChr(npchar, pchar);
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath3");
		break;
		
		case "duel_victory":
			dialog.text = "Lassen wir uns hier raushauen, bevor sie sich vom Schock erholen. Wir müssen das Eisenholz noch bergen, erinnerst du dich? Wir können in Blauweld sprechen.";
			link.l1 = "Wow! Nicht mal ein Glückwunsch? Gut, lass uns gehen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory1");
		break;
		
		case "after_cave":
			dialog.text = "Endlich, zu Hause...";
			link.l1 = "Was denkst du über das, was passiert ist?";
			link.l1.go = "after_cave_1";
		break;
		
		case "after_cave_1":
			dialog.text = "Ich verstehe Duelle nicht. Ein Männervergnügen, das meist mit zwei Leichen endet, und an einem glücklichen Tag sogar noch mehr. Und Ehre... Ich glaube, Ehre basiert auf dem Wunsch, Konflikte bis zum bitteren Ende zu vermeiden, da sie sich selten als würdig erweisen. Ha! Hört nur zu mir - ich rede einen solchen Unsinn!";
			link.l1 = "Das ist eine interessante Perspektive, Helen. Obwohl nicht jeder damit übereinstimmen würde.";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Duel")) {
				link.l1.go = "after_cave_duel";
			} else {
				link.l1.go = "after_cave_notduel";
			}
		break;
		
		case "after_cave_duel":
			dialog.text = "Schade, dass du Ihnen in die Hände gespielt hast. Der Oberst war offensichtlich besessen und der Rest wollte nur ein Spektakel und etwas Klatschmaterial. Nun, ich werde es nicht weiter ausreizen - du hast heute schon genug durchgemacht.";
			link.l1 = "Ja, nach Duellen gibt es immer ein Gefühl der Leere. Genug Abenteuer für heute. Was möchtest du als nächstes tun?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_notduel":
			dialog.text = "Ach! Ich wollte nur sagen, dass ich stolz auf uns bin. Du hast heute echten Mut gezeigt, mein Kapitän. Bist nicht der Hysterie der Mannschaft erlegen, die dich einfach mal kommandieren wollte. Standhaft gegen die Vortäuschung der roten Uniform und die Besessenheit der Blauen. Der Oberst suchte offensichtlich den Tod, bekam aber nichts weiter als eine Wunde an einer unpassenden Stelle, ha-ha!";
			link.l1 = "Danke, Helen. Du hast uns brillant von dem Schlag weggesteuert, wie ein wahrer Marineoffizier. Bist du stolz auf dich selbst?";
			link.l1.go = "after_cave_notduel_1";
		break;
		
		case "after_cave_notduel_1":
			dialog.text = "Ja, das brauchte ich. Es ist nur schade, dass es eine blaue Uniform war und nicht eine rote, aber zumindest hat die Person, die sie trug, das bekommen, was sie verdient hat.";
			link.l1 = "Diese Person ist in der Tat unbedeutend, das gebe ich zu. Genug Abenteuer für heute. Was möchtest du als nächstes tun?";
			if (sti(pchar.questTemp.Saga.HelenRelation) == 7 || sti(pchar.questTemp.Saga.HelenRelation) == 8) {
				link.l1.go = "after_cave_mild";
			} else {
				if (sti(pchar.questTemp.Saga.HelenRelation) < 7) {
					link.l1.go = "after_cave_cold";
				} else {
					link.l1.go = "after_cave_lewd";
				}
			}
		break;
		
		case "after_cave_mild":
			dialog.text = "Ich gehe nach Hause, mein Kapitän. Meine Mu... Gladys hat mir gefehlt. Schade, dass sie gerade zu Hause ist, sonst hätte ich dich eingeladen!";
			link.l1 = "Tatsächlich, das ist eine Schande!";
			link.l1.go = "after_cave_mild_1";
		break;
		
		case "after_cave_mild_1":
			dialog.text = "Sei nicht so aufgebracht. Bald, mein Liebster. In der Zwischenzeit...";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "M-m-m, dieser ist sogar besser als unser erster. Erinnerst du dich? Beim Idol?";
				link.l1 = "Das vergisst man nicht, Liebchen.";
				link.l1.go = "after_second_kiss_1";
			} else {
				dialog.text = "Verdamm noch mal, wag es nicht, diesen Moment zu ruinieren - ich habe mein ganzes Leben davon geträumt!";
				link.l1 = "Ich werde nicht, Helen.";
				link.l1.go = "after_second_kiss_a";
				link.l2 = "Du hast dein ganzes Leben darauf gewartet, mich zu treffen? Ich fühle mich geschmeichelt!";
				link.l2.go = "after_second_kiss_b";
			}
		break;
		
		case "after_second_kiss_1":
			dialog.text = "Ohh! Fass dich, Mädchen! Bis wir uns wiedersehen, mein Kapitän.";
			link.l1 = "Bis dahin, Helen.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_a":
			dialog.text = "Verdammt richtig! Wir sehen uns bald, mein Kapitän.";
			link.l1 = "Bis wir uns wiedersehen, Helen. Oh Gott, was für ein Mädchen...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_second_kiss_b":
			dialog.text = "Dummkopf! Willst du mich beleidigen? Also gut, ich bin beleidigt! Ha-ha! Wir sehen uns bald, mein Kapitän.";
			link.l1 = "Bis wir uns wiedersehen, Helen. Oh Gott, was für ein Mädchen...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveMild");
		break;
		
		case "after_cave_cold":
			dialog.text = "Ich gehe nach Hause, Käpt'n. Ich nehme an, die Geldangelegenheit mit dem Anwalt ist jetzt geklärt? Wir haben harte Hindernisse vor uns, also versuchen wir, Ärger von nun an zu vermeiden. Der Ärger wird uns selbst finden.";
			link.l1 = "Wirklich, wow?";
			link.l1.go = "after_cave_cold_1";
		break;
		
		case "after_cave_cold_1":
			dialog.text = "Entschuldigung für meine Direktheit, Kap. Mein Schicksal wird jetzt auch entschieden, wissen Sie.";
			link.l1 = "Ich weiß, ich werde versuchen, es so würdevoll wie möglich zu handhaben. Wir sehen uns auf dem Schiff, Helen.";
			link.l1.go = "after_cave_cold_2";
		break;
		
		case "after_cave_cold_2":
			dialog.text = "Jawohl, Kap'n!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveCold");
		break;
		
		case "after_cave_lewd":
			dialog.text = "Was kommt als nächstes? Ich zeige es dir.";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SecondKiss");
		break;
		
		case "after_second_kiss1":
			locCameraFromToPos(4.97, 3.71, 16.06, true, 5.09, 1.25, 11.67);
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Kiss")) {
				dialog.text = "M-m-m, dieser hier ist sogar besser als unser erster. Erinnerst du dich? Bei dem Idol?";
				link.l1 = "Das ist nicht etwas, was man vergisst, Liebling.";
				link.l1.go = "after_second_kiss1_1";
			} else {
				dialog.text = "Lass es dir bloß nicht einfallen, diesen Moment zu ruinieren - Ich habe ihn mir mein ganzes Leben lang vorgestellt!";
				link.l1 = "Ich werde nicht, Helen.";
				link.l1.go = "after_second_kiss1_a";
				link.l2 = "Du hast dein ganzes Leben darauf gewartet, mich zu treffen? Ich fühle mich geschmeichelt!";
				link.l2.go = "after_second_kiss1_b";
			}
		break;
		
		case "after_second_kiss1_1":
			dialog.text = "Verdammt richtig! Wow! Gladys ist jetzt nicht zu Hause. Willst du reinkommen?";
			link.l1 = "Mich einladen? Und was werden wir machen?";
			link.l1.go = "after_cave_lewd_accept";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l2 = "Nein, Helen. Eine andere Frau wartet auf mich auf Justice Island. Das kann ich ihr nicht antun.";
				link.l2.go = "after_cave_lewd_refuse_mary";
			}
			link.l3 = "Ein andermal, meine Liebe. Ich will wirklich, aber heute hat mich fast erledigt. Wir werden aufholen und die verpasste Zeit zehnfach kompensieren.";
			link.l3.go = "after_cave_lewd_refuse_head";
		break;
		
		case "after_second_kiss1_a":
			dialog.text = "Verdammt richtig! Wow! Gladys ist jetzt nicht zu Hause. Willst du reinkommen?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "Nein, Helen. Eine andere Frau wartet auf mich auf Justice Island. Ich kann ihr das nicht antun.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "Ein anderes Mal, meine Liebe. Ich möchte wirklich, aber heute hat mich fast erledigt. Wir werden aufholen und die verlorene Zeit zehnfach kompensieren.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "Mich einladen? Und was werden wir machen?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_second_kiss1_b":
			dialog.text = "Dummkopf! Willst du mich beleidigen? Gut, ich bin beleidigt! Ha-ha! Du wirst Wiedergutmachung leisten müssen, mein Kapitän. Wow! Gladys ist jetzt nicht zu Hause. Willst du reinkommen?";
			if (GetCharacterIndex("Mary") >= 0 && CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive") {
				link.l1 = "Nein, Helen. Eine andere Frau wartet auf mich auf Justice Island. Ich kann ihr das nicht antun.";
				link.l1.go = "after_cave_lewd_refuse_mary";
			}
			link.l2 = "Ein anderes Mal, meine Liebe. Ich möchte wirklich, aber heute hat mich fast erledigt. Wir werden aufholen und die verpasste Zeit zehnfach kompensieren.";
			link.l2.go = "after_cave_lewd_refuse_head";
			link.l3 = "Laden Sie mich ein? Und was werden wir machen?";
			link.l3.go = "after_cave_lewd_accept";
		break;
		
		case "after_cave_lewd_refuse_mary":
			dialog.text = "Ach, also bin ich nicht geschickt genug in der Kunst der Verführung? Und sie ist es? Wer ist sie?";
			link.l1 = "Ihr Name ist Mary Casper, und ich liebe sie.";
			link.l1.go = "after_cave_lewd_refuse_mary_1";
		break;
		
		case "after_cave_lewd_refuse_mary_1":
			dialog.text = "Die Rothaarige in der roten Uniform? In der roten Uniform... Nun, wenn ich ein Zeichen brauchte, dann ist es das. Es ist nicht dazu bestimmt. Und machen Sie sich keine Sorgen, Kapitän, es wird meinen Dienst auf Ihrem Schiff nicht beeinflussen.";
			link.l1 = "Es tut mir leid, Helen.";
			link.l1.go = "exit";
			
			pchar.questTemp.HelenDrinking.Mary = true;
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMary");
		break;
		
		case "after_cave_lewd_refuse_head":
			dialog.text = "Oh, mein Kapitän! Es ist gefährlich, eine Frau in einem solchen Zustand zu lassen! Ich halte dich an dein Wort, und jetzt lauf... Ich muss jetzt allein sein und versuchen, mein Problem... alleine zu lösen! Wir sehen uns auf dem Schiff!";
			link.l1 = "Was für ein Mädchen!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveRefuseMild");
		break;
		
		case "after_cave_lewd_accept":
			dialog.text = "Mach dir keine Sorgen, meine Liebe, ich werde dir den Weg weisen, falls du dich verirrst.";
			link.l1 = "Nun dann... führe uns an!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveAccept");
		break;
		
		case "after_cave_bedroom":
			dialog.text = "Sag nichts, ich flehe dich an.";
			link.l1 = "...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex1");
		break;
		
		case "after_cave_sex":
			dialog.text = "... natürlich, bis heute war mein Verständnis für dieses Thema ausschließlich auf die vulgären Gespräche der 'Rainbow' Besatzung gestützt, wenn man sie Gespräche nennen kann, natürlich.";
			link.l1 = "Und wie war es? Hat die Realität deinen Erwartungen entsprochen?";
			link.l1.go = "after_cave_sex_1";
		break;
		
		case "after_cave_sex_1":
			dialog.text = "Es hat mir sehr gefallen, aber es fühlt sich an, als hätte ich es nicht vollständig erlebt. Und wie...";
			link.l1 = "Lass mich dir zeigen! Sollen wir fortfahren?";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveSex2");
		break;
		
		case "after_cave_sex_again":
			dialog.text = "Oh, jetzt verstehe ich! Es war einfach wunderbar, mein Kapitän!";
			link.l1 = "Du hast mich überrascht, gelinde gesagt!";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysEnter");
		break;
		
		case "after_cave_gladys":
			dialog.text = "Ah-ha-ha! Das ist ein guter, sicher! Jetzt wird sie entweder ihre Ohren mit Wachs verstopfen oder zur höchsten Plattform des Forts rennen!";
			link.l1 = "Das war unerwartet, aber sehr lustig, ah-ha-ha!";
			link.l1.go = "after_cave_gladys_1";
			locCameraFromToPos(-0.62, 1.93, -0.39, true, -2.46, -1.20, 1.01);	// Sinistra - постельная камера
		break;
		
		case "after_cave_gladys_1":
			dialog.text = "Bereit, mein Kapitän?";
			link.l1 = "Schon?! Nein, Helen, hab Erbarmen mit mir, bitte. Gladys' plötzliches Auftauchen hat der Atmosphäre definitiv nicht geholfen.";
			link.l1.go = "after_cave_gladys_2";
		break;
		
		case "after_cave_gladys_2":
			dialog.text = "Nun, was kannst du tun... Obwohl...";
			link.l1 = "Nein, nein, setz deine Segel runter!";
			link.l1.go = "after_cave_gladys_3";
		break;
		
		case "after_cave_gladys_3":
			dialog.text = "In Ordnung, dann bleiben wir einfach eine Weile zusammen. Unsere Zukunft ist so trübe und beängstigend, aber zum ersten Mal seit langem habe ich keine Angst vor irgendetwas anderem. Ich weiß, dass eine neue Angst einschleichen wird, aber nicht heute. Nicht heute, mein Kapitän.";
			link.l1 = "Heute nicht, meine Liebe. Heute nicht.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterCaveFin");
		break;
		
		case "give_potions":
			dialog.text = "Darf ich sprechen, Kapitän?";
			link.l1 = "Ja, Helen?";
			link.l1.go = "give_potions_1";
		break;
		
		case "give_potions_1":
			dialog.text = "Ich kenne diesen Snake Eye - er ist ein guter Mann, aber ein bisschen seltsam. Er schickt regelmäßig Leute auf Quests für wer weiß was. Ich sehe, dass du auch diese zweifelhafte Ehre bekommen hast.";
			if (!CheckAttribute(CharacterFromID("SnakeEye"), "quest.amulet")) {
				link.l1 = "Stimmt, ich muss ihm drei Amulette bringen, sonst kann er mir nicht helfen, zu Hawks Ort zu gelangen. Aber weißt du, was lustig ist? Ich hatte sie schon bei mir! Vielleicht wusste er das von Anfang an?";
				link.l1.go = "give_potions_already";
			} else {
				link.l1 = "Das stimmt, ich muss ihm drei Amulette bringen, sonst kann er mir nicht helfen, zu Hawk's Ort zu kommen. Ich kann nicht herausfinden, wo ich sie jetzt finden kann, und die Zeit läuft ab.";
				link.l1.go = "give_potions_3";
			}
		break;
		
		case "give_potions_already":
			dialog.text = "Oh, was für eine Schande! Ich bin froh, dass du nicht herumlaufen musstest, um diese Amulette von Leuchtturmwärtern zu holen, aber ich hatte gehofft, dass ich dir einmal nützlich sein könnte, hoffte, mich beweisen zu können.";
			link.l1 = "Unsinn, Helen. Du musst mir nichts beweisen.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_3":
			dialog.text = "Ich werde dir helfen! Ich gebe zu, ich hatte gehofft, dass ich dir endlich von Nutzen sein könnte, hoffte, mich beweisen zu können.";
			link.l1 = "Unsinn, Helen. Du musst mir nichts beweisen.";
			link.l1.go = "give_potions_4";
		break;
		
		case "give_potions_4":
			dialog.text = "Trotzdem möchte ich dir helfen. Hier, nimm den Schlüssel zu meinem Zimmer... ich meine, zu der Truhe in meinem Zimmer! Es ist nicht viel, aber für dich wird es nützlich sein. Und... Charles, versuche gerade jetzt nicht los zu lachen!";
			link.l1 = "Ähem, das wollte ich nicht. Ich sehe, du bist in solche Dinge verwickelt?";
			link.l1.go = "give_potions_5";
		break;
		
		case "give_potions_5":
			dialog.text = "Ich bin ein Seemann, mein Kapitän, genau wie Sie. In unserem Geschäft müssen wir alles tun, um das Glück auf unsere Seite zu bekommen.";
			link.l1 = "Danke, Helen. Ich schätze es wirklich sehr.";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_GivePotionsKey");
		break;
		
		case "upgrade":
			dialog.text = "Liebling, ich habe ein Geschenk für dich!";
			link.l1 = "Ich sehe, da steht es - lächelnd und froh!";
			link.l1.go = "upgrade_1";
		break;
		
		case "upgrade_1":
			dialog.text = "Ach-ha, hör auf! Ich habe einmal eine ordentliche Ladung Seide an den örtlichen Schiffsbaumeister geliefert, also schuldet er mir eine komplette Überholung des Schiffes. Ich dachte daran, ihm die 'Rainbow' für diese Arbeit zu geben, aber das war nicht so gemeint. Dein Schiff hingegen könnte wirklich von solcher Pflege profitieren, denkst du nicht?";
			link.l1 = "Tatsächlich, ein herrliches Geschenk, Helen - genau dein Ding!";
			link.l1.go = "upgrade_2";
		break;
		
		case "upgrade_2":
			dialog.text = "Ich freue mich, dass es dir gefällt. Besuche ihn jederzeit und sag ihm, dass ich dich geschickt habe. Sie werden ihr Bestes tun.";
			link.l1 = "Sicherlich!";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "Helena_officer";
			AddDialogExitQuestFunction("HelenUpgradeShip1");
		break;
		
		case "give_sex":
			dialog.text = "Erlaubnis zu sprechen, mein Kapitän?";
			link.l1 = "Natürlich, meine Liebe.";
			link.l1.go = "give_sex_1";
		break;
		
		case "give_sex_1":
			dialog.text = LinkRandPhrase("Ihre Dame vermisst Sie und verlangt Aufmerksamkeit. Darf ich darum bitten, ein Zimmer für sie zu arrangieren und ihr etwas Zeit zu widmen","Meldung: Ihre Anwesenheit ist in einem Bett in der örtlichen Taverne erforderlich. Nur fünf Minuten Ihrer Zeit, aber die Mannschaft hofft, dass Sie länger bleiben!","Meuterei auf dem Schiff, mein Kapitän! Ich habe den Auftrag, Ihnen in privater Atmosphäre ein schwarzes Zeichen zu übergeben. Kommen Sie sofort mit mir!");
			link.l1 = "He-he, ähem! Ihr Antrag ist genehmigt, Offizier Sharp!";
			link.l1.go = "give_sex_1_yes";
			link.l2 = "Heute nicht, Liebling. Zu viel passiert gerade.";
			link.l2.go = "give_sex_1_no";
		break;
		
		case "give_sex_1_yes":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			DialogExit();
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "give_sex_1_no":
			dialog.text = "Oh, und was soll ein armes Mädchen denn tun, hm? Nun gut, mein Lieber, dann eben ein anderes Mal.";
			link.l1 = "";
			link.l1.go = "give_sex_2_no";
		break;
		
		case "give_sex_2_no":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			npchar.location = "None";
			npchar.dialog.currentnode = "Helena_officer";
			LAi_SetOfficerType(npchar);
			chrDisableReloadToLocation = false;
			
			pchar.quest.Helen_GiveSex.win_condition.l1 = "Timer";
			pchar.quest.Helen_GiveSex.win_condition.l1.date.day = GetAddingDataDay(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.month = GetAddingDataMonth(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l1.date.year  = GetAddingDataYear(0, 2, 0);
			pchar.quest.Helen_GiveSex.win_condition.l2 = "Location_Type";
			pchar.quest.Helen_GiveSex.win_condition.l2.location_type = "town";
			pchar.quest.Helen_GiveSex.function = "Helen_GiveSex";
		break;
		
		case "special_sex":
			SaveCurrentNpcQuestDateParam(npchar, "sex_date");
			SaveCurrentNpcQuestDateParam(npchar, "special_sex_date");
			
			dialog.text = "Ha! Du musst mich nicht zweimal fragen! Natürlich, auf geht's!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("Helen_GiveSexGoToTavern");
		break;
		
		case "rainbow":
			dialog.text = "Ich werfe dich jetzt gleich über Bord!";
			link.l1 = "Hey, hey, hey! Beruhige dich, Liebling!";
			link.l1.go = "rainbow_1";
		break;
		
		case "rainbow_1":
			dialog.text = "Komm her, du Schurke!";
			link.l1 = "Nur ein Scherz, Helen! Ich wollte dich nicht beleidigen!";
			link.l1.go = "rainbow_2";
		break;
		
		case "rainbow_2":
			dialog.text = "Oh wirklich? So ein Wtzbold...";
			link.l1 = "Du bist die Schönste und ich liebe dich wahnsinnig!";
			link.l1.go = "rainbow_3";
		break;
		
		case "rainbow_3":
			dialog.text = "Verschwinde, Charles.";
			link.l1 = "";
			link.l1.go = "exit";
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Rainbow");
			Achievment_Set("ach_CL_84");
		break;
		
		case "joan":
			dialog.text = "Du bist doch die Dirne! Sei froh, dass Jan aus dir eine ehrliche Frau gemacht hat, sonst würdest du immer noch jedem Vorübergehenden deine Beine breit machen!";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog2");
		break;
		
		case "joan_1":
			dialog.text = "Hure! Los geht's, Charles!";
			link.l1 = "";
			link.l1.go = "exit";
			
			ResetSound();
			SetMusic("helendrinking_shanty");
			pchar.questTemp.lockedMusic = true;
			AddDialogExitQuestFunction("HelenDrinking_GoToFort");
		break;
		
		case "cutlass_training":
			dialog.text = "Die Entermesser passt perfekt in meine Hand! Ich weiß nicht, wie ich es erklären soll... Ich hatte immer Schwierigkeiten mit anderen Arten von Kaltwaffen, wie Rapiere und Schwerter. Aber diese Entermesser ist eine andere Geschichte! Es fühlt sich unglaublich an! Danke, Charles!";
			link.l1 = "Das Schicksal hat eine Art, uns zu finden. Ich freue mich für dich, Helen!";
			link.l1.go = "exit";
			notification("Medium Weapons +", "Helena");
		break;
		
		case "brothel_found":
			dialog.text = "Erzähl deine Geschichten jemand anderem, sie werden bei mir nicht wirken. Sehe ich aus wie eine naive, verliebte Närrin? Ich meine, ich BIN verrückt nach dir, aber mich eine Närrin zu nennen, wäre übertrieben\n Hör zu, Liebling, tu, was du willst, aber behalte im Kopf, dass du keine bessere Frau als mich finden wirst. Wenn du sie in Bordellen suchen willst, mach weiter, aber dann werde ich für immer aus deinem Leben verschwinden.";
			link.l1 = "Helen, ich...";
			link.l1.go = "brothel_found_1";
		break;
		
		case "brothel_found_1":
			dialog.text = "Ich verstehe alles, Charles. Du liebst nur mich, und das sind nur natürliche Triebe. Weißt du, was mein natürlicher Trieb ist? Respekt von meinem Mann. Eine Frau kann nicht nur mit Liebe zufrieden sein, Liebling. Lass uns dieses Missverständnis vorerst vergessen, aber denke ein wenig über meine Worte nach. Gut?";
			link.l1 = "Gut, Helen.";
			link.l1.go = "exit";
		break;
		
		case "refuse":
			dialog.text = "Du weißt, wie es läuft. Lass ein Mädchen zuerst abkühlen.";
			link.l1 = "Seufz...";
			link.l1.go = "exit";
		break;
		
		// Тайна Порт-Рояля
		case "MysteryPortRoyal_Helena_1":
			dialog.text = "Francis... ich erinnere mich. Er wartete immer auf meine Ankunft in Port Royal und war ein unverbesserlicher Romantiker. Ich genoss es, Zeit mit jemandem zu verbringen, der so weit weg vom Meer war – all diese Gedichte und Serenaden... Es war etwas Neues. Ein Hauch einer Welt, die ich nie gekannt hatte\nFrancis war reich, klug und gut aussehend – ein begehrenswerter Bräutigam. Jedes Mädchen hier hätte sich um seine Aufmerksamkeit gerissen, aber damals war ich mehr damit beschäftigt, die Rainbow über Wasser zu halten.";
			link.l1 = "Offenbar konnte die empfindsame Seele eines Dichters deine Ablehnung nicht ertragen. In all seinen Briefen sprach er nur von dir, erinnerte sich an eure Treffen. Ich kann dir alles geben, was er hinterlassen hat, wenn du es möchtest.";
			link.l1.go = "MysteryPortRoyal_Helena_2";
		break;
		
		case "MysteryPortRoyal_Helena_2":
			dialog.text = "Ich wusste nicht, dass er krank war. Das ist irgendwie... dumm. Und was sein Geschenk angeht... Ich habe genug von Testamenten und Erbschaften. Glaub mir, ich habe alles, was ich brauche – und noch mehr. Behalte es lieber.";
			link.l1 = "Sein Vermächtnis wird dir so oder so zugutekommen – also habe ich wohl ungewollt seinen letzten Wunsch erfüllt. Eine interessante Geschichte.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.MysteryPortRoyal_Helena");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenDrinking_RobbedSvenson() {
	sld = &locations[FindLocation("SantaCatalina_houseS1_residence")];
	if (!CheckAttribute(sld, "private1.items.chest")) { 
		return true;
	}
	
	if (sti(sld.private1.items.chest) < 2) {
		return true;
	}
	
	return false;
}
