
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
		////// Леа Карно //////
		
		case "Exit":
			DialogExit();
		break;
		
		case "First Time":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"! Verzeiht... seid Ihr Seemann"+GetSexPhrase("","sfrau")+"?";
			link.l1 = "Ich bin Kapitän "+GetFullName(pchar)+", zu Euren Diensten.";
			link.l1.go = "Lea First Talk";
			DelLandQuestMark(npchar);
		break;

		case "Lea First Talk":
			dialog.text = "Ich bin Léa. Léa Carnot... "+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitän, seid Ihr schon lange hier? Habt Ihr draußen auf See ein Fischerboot namens 'Cormoran' gesehen? Seht Ihr, mein Mann... mein Mann Pierre... er ist vor zwei Tagen ausgelaufen und nicht zurückgekehrt.";
			link.l1 = "'Cormoran'? Nein, so ein Boot ist mir nicht begegnet"+GetSexPhrase("","e")+". Einen solchen Namen hätte ich mir gemerkt. Das tut mir leid, Madame. Ich hoffe, es geht Eurem Mann gut und er wurde nur irgendwo aufgehalten.";
			link.l1.go = "Lea First Talk Rep Plus";
			link.l2 = "'Cormoran'? Ha-ha! Ist das der Name des Kahns oder der Spitzname seines Besitzers? Aber was soll's. Ich habe weder den einen noch den anderen gesehen.";
			link.l2.go = "Lea First Talk Rep Minus";
		break;

		case "Lea First Talk Rep Plus":
			dialog.text = "Ich weiß nicht, was ich denken soll... Er ist noch nie so lange weg gewesen. Er war immer spätestens mittags zurück. Und jetzt... Irgendetwas ist passiert. Ich fühle es.";
			link.l1 = "Wendet Euch an die Behörden. Sie könnten ein Patrouillenboot aussenden, um die Küstengewässer abzusuchen.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", 3);
		break;

		case "Lea First Talk Rep Minus":
			dialog.text = "Ich weiß nicht, was ich denken soll... Er ist noch nie so lange weg gewesen. Er war immer spätestens mittags zurück. Und jetzt... Irgendetwas ist passiert. Ich fühle es.";
			link.l1 = "Wendet Euch an die Behörden. Sie könnten ein Patrouillenboot aussenden, um die Küstengewässer abzusuchen.";
			link.l1.go = "Lea First Talk1";
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
		break;

		case "Lea First Talk1":
			dialog.text = "Oh, "+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitän, ich habe mich natürlich bereits an den Kommandanten gewandt. Aber was nützt es? Er hat nur mit den Schultern gezuckt... Er meinte, er habe momentan keine freien Schiffe, um nach meinem Mann suchen zu lassen.\nUnd was kann ich tun? Ich stehe nur hier, blicke aufs Meer hinaus, warte... und hoffe.";
			link.l1 = "Ach, Madame Léa. Verliert nicht zu früh den Mut. Ich denke, ich kann einen Tag entbehren, um Euch bei der Suche zu helfen.";
			link.l1.go = "Agree To Help";
			link.l2 = "Was macht Ihr Euch solche Sorgen? Vielleicht hat ihn die Morgenbrise in die Arme einer reizenden Dame geweht. Er wird etwas spazieren gehen, frische Luft schnappen – und dann zurückkehren.";
			link.l2.go = "bad joke";
			link.l3 = "Wollt Ihr einen Rat? Schont Euch die Augen, das Meer wird Euch keine Antworten geben. Besser Ihr sucht Euren Angetrauten in der Taverne von Le François. Verzeiht mir, aber wahrscheinlich wollte er einfach eine kleine Pause vom Ehealltag... Viel Glück bei Eurer Suche.";
			link.l3.go = "Rejection";
		break;

		case "Agree To Help":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitän, ich... ich weiß gar nicht, wie ich Euch danken soll... Ihr... Ihr könnt Euch nicht vorstellen, was das für mich bedeutet! Alle anderen zucken nur mit den Schultern... Aber Ihr... Ihr wollt wirklich helfen. Danke!";
			link.l1 = "Dankt mir noch nicht. Erzählt mir lieber, wo Euer Mann gewöhnlich fischte. Hatte er einen festen Platz, oder wählte er oft neue?";
			link.l1.go = "Go To Help";
		break;
		
		case "bad joke":
			dialog.text = "Eine reizende Dame?! Glaubt Ihr wirklich, dies sei der richtige Moment für Späße? Ich spüre, dass er in Gefahr ist... und Ihr macht Euch lustig über mein Leid! (weint) Die ganze Welt scheint sich gegen mich verschworen zu haben. Niemand will helfen... Niemand versteht, wie schwer es für mich ist.";
			link.l1 = "Madame Léa, um Himmels willen, verzeiht mir meine Taktlosigkeit. Ich wollte Euch keinesfalls beleidigen! Ich verspreche, ich werde nach Eurem Mann suchen. Sagt mir nur, wo ich beginnen soll.";
			link.l1.go = "bad joke1";
		break;

		case "bad joke1":
			dialog.text = "Ihr...? Ihr wollt mir wirklich helfen?";
			link.l1 = "Natürlich. Es ist das Mindeste, was ich tun kann, um meinen unentschuldbaren und unangebrachten Scherz wiedergutzumachen.";
			link.l1.go = "bad joke2";
		break;

		case "bad joke2":
			dialog.text = "Danke, "+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitän. Danke... Ehrlich, Ihr überrascht mich – ich weiß gar nicht, was ich sagen soll...";
			link.l1 = "Dankt mir noch nicht. Erzählt mir lieber, wo Euer Mann gewöhnlich fischte. Hatte er einen festen Ort, oder suchte er sich oft neue?";
			link.l1.go = "Go To Help";
		break;

		case "Go To Help":
			dialog.text = "Nun... Pierre... Er sprach selten darüber, wo genau er fischte. Er nannte es 'sein Geheimnis'. Aber wenn es helfen kann, ihn zu finden... Vielleicht... Ich weiß nicht... Wollt Ihr mir wirklich helfen, "+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitän? Wirklich?";
			link.l1 = "Zweifelt Ihr daran, dass Ihr mir das Geheimnis Eures Mannes anvertrauen solltet? Ich versichere Euch, es bleibt unter uns – Kapitänsehrenwort. Ich muss wissen, wo dieser Ort ist, um zu wissen, wo ich mit der Suche beginnen kann.";
			link.l1.go = "Go To Help1";
		break;

		case "Go To Help1":
			dialog.text = "Ihr habt recht, "+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitän... Verzeiht. Dieser Ort bedeutete Pierre so viel. Er sagte immer, es sei sein einziges Geheimnis, sein kleiner Rückzugsort.\nAber ich weiß, wo er ist. Wenn es hilft, ihn zu finden... Er fischte in der Bucht von Le Marin. Sie liegt an der Südküste, nicht weit von der Stadt. Bitte, findet ihn, ich flehe Euch an!";
			link.l1 = "Macht Euch keine Sorgen, Léa. Es wird alles gut. Ich werde tun, was ich kann. Hatte Pierre vielleicht Feinde? Hat ihm jemand gedroht?";
			link.l1.go = "Go To Help2";
		break;

		case "Go To Help2":
			dialog.text = "Feinde? Pierre? Er ist der gutmütigste Mensch auf der Welt! Er würde keiner Seele etwas zuleide tun... Er ist nur ein einfacher Fischer. Wem hätte er im Weg sein können? Ich verstehe einfach nicht, was passiert sein könnte... Es ist alles so seltsam... und beängstigend...";
			link.l1 = "Keine Sorge, Madame Léa. Ich mache mich sofort auf die Suche. Ich bin sicher, es geht Eurem Mann gut. Ich bringe ihn zurück – in Eure liebevollen Arme. Haltet durch.";
			link.l1.go = "Return Lea Exit";
		break;

		case "Return back to Lea":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitän, sagt, habt Ihr Neuigkeiten? Habt Ihr etwas erfahren? Irgendetwas?";
			link.l1 = "Leider noch nicht, Léa. Aber ich suche weiter!";
			link.l1.go = "Exit";
		break;
		
		case "Return Lea Exit":
			DialogExit();
			npchar.dialog.currentnode = "Return back to Lea";
			AddQuestRecord("VPVL", "2"); 
			DoQuestCheckDelay("VPVL_Start", 0.1);
		break;
		
		case "Rejection":
			DialogExit();
			npchar.dialog.currentnode = "Rejection1";
			SetTimerCondition("VPVL_ClearLea", 0, 0, 2, false);  // Удаляем Леа через 2 дня
			CloseQuestHeader("VPVL");
		break;
		
		case "Rejection1":
			dialog.text = "Was wollt Ihr noch? Habt Ihr Euch nicht schon genug über eine arme Frau lustig gemacht?";
			link.l1 = "...";
			link.l1.go = "Exit";
		break;

		case "Lea second talk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitän! Pierre! Wie froh ich bin, Euch zu sehen! Ihr habt ihn gefunden!";
			link.l1 = "Léa, darf ich vorstellen – Pierre Carnot, persönlich. Ich kann nicht behaupten, dass er unversehrt ist, aber ich bin sicher, Eure Fürsorge wird ihn im Nu wieder auf die Beine bringen!";
			link.l1.go = "Lea second talk1";
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
		break;

		case "Lea second talk1":
			dialog.text = "Pierre! Heilige Mutter Maria! Ich habe mir solche Sorgen gemacht! Wo warst du nur? Du siehst ja schrecklich aus... so bleich... Oh! Was ist das?! Was sind das für... furchtbare Wunden?! Schnitte... und Verbrennungen...";
			link.l1 = "Alles ist gut, meine Liebste. Es sind nur Kratzer. Ich bin so froh, dich wiederzusehen! Wenn der Kapitän nicht gewesen wäre... ich verdanke ihm mein Leben.";
			link.l1.go = "Lea second talk2";
			CharacterTurnByChr(npchar, CharacterFromID("VPVL_Pier_carno"));
			sld = CharacterFromID("VPVL_Pier_carno");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_Lea_girl"));
			locCameraFromToPos(-7.62, 3.1, 83.26, false, 30, -15, 0);
		break;

		case "Lea second talk2":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitän... ich... ich weiß gar nicht, wie ich Euch danken soll... Ihr habt ihn gefunden! Ihr habt meinen Pierre gerettet! Danke... danke für alles! Möge der Herr Euch behüten, "+GetSexPhrase("Monsieur","Mademoiselle")+" Kapitän!";
			link.l1 = "Nun beruhigt Euch, bitte. Im Moment ist es viel wichtiger, dass Pierre etwas Gutes zu essen bekommt und sich ausruht.";
			link.l1.go = "Exit";
			CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
			locCameraFromToPos(-7.58, 3.1, 82.5, false, -10, -15, 0);
			AddDialogExitQuest("VPVL_PierTalkOnThePirs");
		break;
		
		//////   Контры   //////
		
		case "Kontr Le Maren":
			dialog.text = "Na endlich bist du aufgetaucht, "+GetSexPhrase("du Hund","du Schlampe")+"! Wo zum Teufel warst du? Wir liegen hier seit drei Tagen am Strand und vergehen in der Hitze! Wo ist unsere Ladung?!";
			link.l1 = "Scheint, als könne der Ball ohne mich nicht beginnen, was? Ich bin zwar etwas spät dran, aber besser spät als nie!";
			link.l1.go = "Exit_Sneak";
			link.l2 = "Spricht Ihr mit mir? Hm, vielleicht lernt Ihr zuerst Manieren, bevor Ihr Fragen stellt?";
			link.l2.go = "Exit_Lucky";
			//locCameraFromToPos(-3.35, 2.23, 6.93, false, 20, -1, 10);
			locCameraFromToPos(-3.53, 2.35, 6.35, true, 1.93, -0.60, 11.17);
			DeleteAttribute(pchar, "questTemp.VPVL_Contr_V_Lemaren");
		break;
		
		case "Exit_Sneak":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			notification("Erfahrung erhalten", SKILL_SNEAK);
		break;
		
		case "Exit_Lucky":
			DialogExit();
			sld = CharacterFromID("VPVL_contr_1");
			sld.dialog.filename = "Quest\MiniEvents\VPVL_dialog.c";
			sld.dialog.currentnode = "Kontr Le Maren0";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			notification("Erfahrung erhalten", SKILL_FORTUNE);
		break;
		
		case "Kontr Le Maren0":
			sld = CharacterFromID("VPVL_contr_2");
			dialog.text = ""+sld.name+", bist du völlig hirnlos?! Mach die Augen auf, Dummkopf – das ist nicht unser Kontakt!";
			link.l1 = "Arrgh... Noch ein Lakai des Gouverneurs! War ja klar! Und wenn sich das Miststück schon selbst herbemüht hat, werfen wir sie gleich zu ihrem Kameraden in die Höhle. Wir werden unseren Spaß haben! Und dabei kriegen wir alles aus ihr heraus, was sie über die Pläne ihres Herrn weiß!";
			if (pchar.sex == "man")
			{
				link.l1 = "Arrgh... Noch ein Lakai des Gouverneurs! War ja klar! Und wenn sich dieser Dreckskerl schon selbst herbemüht hat, werfen wir ihn gleich zu seinem Kameraden in die Höhle. Soll ruhig sehen, wie wir mit Schnüfflern umgehen. Der wird ganz schnell singen und die Pläne seines Herrn ausspucken!";
			}
			link.l1.go = "Kontr Le Maren1";
			locCameraFromToPos(-3.53, 2.35, 6.35, false, -0.03, 0.40, 7.77);
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_1"));
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_2"));
			
			sld = CharacterFromID("VPVL_contr_1");
			CharacterTurnByChr(sld, CharacterFromID("VPVL_contr_2"));
		break;
		
		case "Kontr Le Maren1":
			dialog.text = "Was träumst du da, du Vieh? Wisch dir lieber den Sabber vom Kinn! Wir verkaufen sie besser an... du weißt schon wen. Für so ein Mädchen zahlt er einen Sack voller Münzen, und wir feiern dann einen Monat lang durch!";
			if (pchar.sex == "man")
			{
				dialog.text = "Wozu zum Henker brauchen wir noch so einen Affen? Wir setzen seinen Kumpan unter Druck – der wird schon auspacken. Und den hier bringen wir gleich um, damit er uns nicht mehr auf die Nerven geht!";
			}
			link.l1 = "Tausend Haie sollen dich verschlingen, Simon! Du bist der gerissenste Schmuggler im ganzen Archipel!";
			link.l1.go = "Kontr Le Maren2";
		break;

		case "Kontr Le Maren2":
			dialog.text = "...";
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) >= 20)
			{
				if(GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) == "") {	
				notification("Keine Pistole ausgerüstet", "NONE");
				link.l2 = "Wenn das der Schlauste unter euch ist, dann will ich gar nicht wissen, was in den Köpfen der anderen vor sich geht!";
				link.l2.go = "Kontr Le Maren3";
				CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
				locCameraFromToPos(-3.73, 2.45, 5.75, false, -0.53, -0.0, 9.17);
				CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
				sld = CharacterFromID("VPVL_contr_1");
				CharacterTurnByChr(sld, CharacterFromID("Blaze"));
				CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
				}
				else
				{
				link.l1 = "(Gedanken)(Pistole) Während diese Schwätzer sich weiter in ihrem sinnlosen Gerede verlieren, habe ich die Chance, einen Überraschungsangriff zu starten.";
				link.l1.go = "murder";
				notification("Prüfung bestanden", SKILL_PISTOL);
				locCameraFromToPos(-5.73, 2.45, 5.75, true, -0.53, 0.40, 7.17);
				}
			}
			if (GetSummonSkillFromName(pchar, SKILL_PISTOL) < 20)
			{
			notification("Fertigkeit nicht ausreichend entwickelt (20)", SKILL_PISTOL);
			CharacterTurnByChr(npchar, CharacterFromID("Blaze"));
			sld = CharacterFromID("VPVL_contr_2");
			CharacterTurnByChr(sld, CharacterFromID("Blaze"));
			locCameraFromToPos(-3.73, 2.45, 5.75, false, -0.53, -0.0, 9.17);
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
			}
			link.l2 = "Wenn das der Schlauste unter euch ist, dann will ich gar nicht wissen, was in den Köpfen der anderen vor sich geht!";
			link.l2.go = "Kontr Le Maren3";
		break;
		
		case "Kontr Le Maren3":
			dialog.text = "Ich reiß dir jetzt die Zunge raus, du "+GetSexPhrase("frecher Köter","verfluchtes Biest")+", damit du nie wieder kläffen kannst!";
			link.l1 = "Ach ja? Dann versuch's doch.";
			link.l1.go = "Kontr Le Maren Fight";
			CharacterTurnByChr(pchar, CharacterFromID("VPVL_contr_1"));
		break;
		
		case "Kontr Le Maren Fight":
			DialogExit();
			AddDialogExitQuest("VPVL_EveryoneFight");
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], false);
			EndQuestMovie();
		break;
		
		case "murder":
			DialogExit();
			AddDialogExitQuest("VPVL_Pistol_Murder");
			//locCameraFromToPos(-5.04, 2.62, 8.65, false, 20, -6, -15);
		break;
		
		/////////////   Пьер Карно   /////////////
		
		case "PierFirstTalk":
			dialog.text = ""+GetSexPhrase("Monsieur","Mademoiselle")+"... Verzeihen Sie... Ich verstehe gar nichts mehr... Sind Sie gekommen, um mich zu töten?";
			link.l1 = "Sind Sie Pierre Carnot?";
			link.l1.go = "Pier_1";
			DelLandQuestMark(npchar);
			DeleteAttribute(pchar, "questTemp.VPVL_SetFlagLeMaren");
		break;
		
		case "Pier_1":
			dialog.text = "Ja, das bin ich. Sie kennen meinen Namen?";
			link.l1 = "Natürlich. Sonst hätte ich hier wohl kaum etwas verloren...";
			link.l1.go = "Pier_2";
		break;
		
		case "Pier_2":
			dialog.text = "Verzeihen Sie, ich verstehe nichts mehr... Schmerz und Hunger rauben mir den klaren Verstand... Warum sind Sie hier?";
			link.l1 = "Ganz einfach. Seit Ihrem Verschwinden weicht Ihre treue Frau nicht vom Pier. In der Hoffnung, die Segel der 'Baklan' zu erblicken. Ihr Verzweiflungsschrei war so durchdringend, dass ich nicht untätig bleiben konnte und mich auf die Suche nach Ihnen machte.";
			link.l1.go = "Pier_3";
		break;
		
		case "Pier_3":
			dialog.text = "Meine Frau... meine liebe Léa... Ich war sicher, dass ich sie nie wiedersehen würde...";
			link.l1 = "Das ist jetzt vorbei. Sie wartet am Pier und gibt die Hoffnung nicht auf. Lassen Sie uns hier verschwinden. Ich helfe Ihnen aufzustehen.";
			link.l1.go = "Pier_4";
		break;
		
		case "Pier_4":
			dialog.text = "Uff... Verzeihen Sie, "+GetSexPhrase("Monsieur","Mademoiselle")+"... ich brauche einen Moment... Meine Beine gehorchen mir nicht, sie sind völlig taub... Ich danke Ihnen von Herzen. Wären Sie nicht gewesen... Sie wurden mir vom Himmel geschickt!.. Sie haben sich nicht vorgestellt. Wie darf ich Sie nennen?";
			link.l1 = "Kapitän "+GetFullName(pchar)+". Während Sie zu Kräften kommen, erzählen Sie mir, wie Sie hierher geraten sind. Hatten Sie etwa Geschäfte mit diesen... Leuten geplant?";
			link.l1.go = "Pier_5";
			LAi_Fade("VPVL_PierStay", "");
		break;
		
		case "Pier_5":
			dialog.text = "Was denken Sie, Kapitän? Das ist nicht mein Gewerbe, ich bin nur ein einfacher Fischer. Es fing alles so gut an. Ich fischte im Westen der Bucht. Der Fang war unglaublich\nIch war so in Eile, den Fisch in Fässer zu packen, um die Netze erneut auszuwerfen, dass ich gar nicht bemerkte, wie das Boot zu den Riffen abdriftete. Die Planken waren wie Eierschalen, ein kleiner Stoß reichte – und das Wasser strömte hinein. Die 'Baklan', schon gut beladen mit Fisch, sank schnell.";
			link.l1 = "Und dann sind Sie an Land gekommen, und die Schmuggler hielten Sie für einen Spitzel des Gouverneurs?";
			link.l1.go = "Pier_6";
		break;
		
		case "Pier_6":
			dialog.text = "Ganz genau. Ich habe es kaum lebend durch die verfluchten Wellen an Land geschafft. Ich wollte mich nur kurz trocknen, ausruhen, Kraft sammeln, bevor ich mich auf den Rückweg machte. Alles geschah so schnell... Als ich mich schließlich entschloss, in die Stadt aufzubrechen, bin ich diesen Halunken begegnet\nSie hielten mich sofort für einen Agenten des Gouverneurs. Ich konnte kein Wort sagen, schon war ich gefesselt und hierher verschleppt. Sie folterten mich und ließen mich zwei Tage hungern, verlangten, ich solle alle Geheimagenten des Gouverneurs und seine Pläne preisgeben. Doch wie hätte ich etwas enthüllen sollen, das ich nicht wusste?";
			link.l1 = "Verstand gehörte nie zu ihren Stärken – deshalb sind sie jetzt auch tot. Das ist nun vorbei. Sie sind frei. Zeit, Ihrer Frau Hoffnung zu bringen – sie ist sicher völlig erschöpft von der Sorge.";
			link.l1.go = "Pier_7";
		break;
		
		case "Pier_7":
			dialog.text = "Wie sehr wünsche ich mir, sie endlich wieder in die Arme zu schließen. Ich glaube, ich kann schon aufstehen.";
			link.l1 = "Dann verlieren wir keine Zeit.";
			link.l1.go = "exit_grot";
		break;
		
		case "exit_grot":
			DialogExit();  
			AddQuestRecord("VPVL", "4");
			AddDialogExitQuest("VPVL_PierFollow");
		break;
		
		case "PierInThePirs":
			dialog.text = "Kapitän, kommen Sie morgen Abend um sechs in die Taverne. Ich würde es mir nie verzeihen, wenn ich Ihnen nicht anständig danke. Im Moment... im Moment finde ich einfach nicht die richtigen Worte, um meine Dankbarkeit angemessen auszudrücken. Bitte kommen Sie. Es ist mir sehr wichtig.";
			link.l1 = "In Ordnung, Pierre, machen Sie sich keine Sorgen, ich komme.";
			link.l1.go = "GoHome";
			locCameraFromToPos(-8.28, 3.1, 82.93, false, 40, -15, 0);
		break;
		
		case "GoHome":
			DialogExit();
			AddQuestRecord("VPVL", "5");
			AddDialogExitQuest("VPVL_KarnoGoHome");
		break;
		
		case "PierTalkTavern":
			dialog.text = "Kapitän! Da sind Sie ja! Setzen Sie sich.";
			link.l1 = "Mit Vergnügen!";
			link.l1.go = "PierTalkTavern1";
			LAi_Fade("VPVL_SitOnTheTable", "");
			FreeSitLocator("FortFrance_Tavern", "sit6");  // Für alle Fälle
			DeleteAttribute(pchar, "questTemp.VPVL_Magor_Dialogue");
			pchar.questTemp.VPVL_DontSpawnSmugglersShipPier = true;
			DelLandQuestMark(npchar);
			AddDialogExitQuest("VPVL_KillCapitanOfSmuggler");
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
		break;
		
		case "PierTalkTavern1":
			dialog.text = "Stoßen wir auf Ihre Gesundheit an!";
			link.l1 = "Nicht nur auf meine, sondern auch auf Ihre! Sie sehen schon viel besser aus als damals in der Höhle. Auf uns!";
			link.l1.go = "PierTalkTavern2";
		break;
		
		case "PierTalkTavern2":
			dialog.text = "Kapitän, erlauben Sie mir, meine grenzenlose Dankbarkeit auszudrücken! Sie sind nicht einfach weitergegangen, haben sich nicht abgewandt, sondern einem völlig Fremden geholfen, einem einfachen Fischer. Ihre Edelmut verdient Bewunderung, und ich möchte Ihnen alles geben, was ich besitze. Hier. Nehmen Sie dies. Zwanzig Stücke Bernstein und fünf seltene blaue Bernsteine. Ich habe sie von einem gesunkenen Schiff geborgen. Jetzt gehören sie Ihnen. Und außerdem möchte ich Ihnen meine nautischen Werkzeuge und Ausrüstung geben. Bis ich ein neues Schiff habe, brauche ich sie nicht.";
			link.l1 = "Ich danke Ihnen, Pierre, sie werden mir sehr nützlich sein. Aber das Wichtigste ist, dass Sie wieder zu Hause sind und Ihre Frau nicht länger in Sorge leben muss. Jetzt wird sich alles zum Guten wenden.";
			link.l1.go = "PierTakeGift";
			link.l2 = "Danke für Ihre Großzügigkeit, Pierre, aber behalten Sie das lieber. Sie brauchen es gerade mehr – um Ihr Boot zu reparieren, Ausrüstung und Netze zu kaufen. Ihre Dankbarkeit und die Tatsache, dass Sie wieder mit Ihrer Frau vereint sind, sind mir Lohn genug. Passen Sie gut aufeinander auf!";
			link.l2.go = "PierWontGift1";
		break;
		
		case "PierTakeGift":
			dialog.text = "Ich kann immer noch nicht glauben, dass all das mir passiert ist. Stoßen wir an auf ein neues Kapitel im Leben meiner Familie – und auf Ihre edle Gesinnung, Kapitän!";
			link.l1 = "Und auf das Glück, Pierre. Davon können wir alle etwas gebrauchen!";
			link.l1.go = "ZastavkaVPVL";
			AddItems(PChar, "jewelry8", 20);
			AddItems(PChar, "jewelry7", 5);
			AddItems(PChar, "A_map_martiniqua", 1);
			AddItems(PChar, "spyglass3", 1);
			AddItems(PChar, "obereg_7", 1);
		break;
		
		case "PierWontGift1":
			dialog.text = "Kapitän, ich kann das einfach nicht so stehen lassen... Sie haben mir das Leben gerettet, und ich schulde Ihnen alles. Wenn Sie den Bernstein und die anderen Geschenke ablehnen, dann erlauben Sie mir wenigstens, Ihrer Mannschaft beizubringen, wie man im Flachwasser fischt. Das verschafft Ihnen frische Nahrung und hilft, Proviant zu sparen. Was meinen Sie?";
			link.l1 = "Das ist eine ausgezeichnete Idee! Wie man sagt: Gib einem Menschen nicht einfach Brot, sondern lehre ihn pflügen – dann wird er selbst satt und kann auch andere ernähren.";
			link.l1.go = "PierWontGift2";
			pchar.questTemp.VPVL_Food = true;
		break;
		
		case "PierWontGift2":
			dialog.text = "Weise Worte, Kapitän! Ich freue mich, nützlich sein zu können. Na, wie wär's mit einem Becher?";
			link.l1 = "Auf Ihre Gesundheit und Ihr Wohlergehen, Pierre!";
			link.l1.go = "ZastavkaVPVL";
		break;
		
		case "ZastavkaVPVL":
			DialogExit();
			SetLaunchFrameFormParam("Vier Stunden später...", "VPVL_SitOnTheTable", 2, 2);
			LaunchFrameForm();
			locCameraFromToPos(-2.87, 1.37, -1.09, false, 0, -0.8, -0.90);
			sld = CharacterFromID("VPVL_Pier_carno");
			sld.dialog.currentnode = "PierTalkTavern3";
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, sld, "", -1, 0);
		break;
		
		case "PierTalkTavern3":
			if(CheckAttribute(pchar, "questTemp.VPVL_Food"))
			{
				int foodDays = CalculateShipFood(&pchar);
				dialog.text = "Ganz schön starkes Zeug! Ich spüre schon, noch ein oder zwei Schlucke, und ich... hicks... werde ein Lied anstimmen, dass ganz Fort-de-France es hören kann!";
				link.l1 = "Pierre, heb dir das Lied lieber für später auf... für unser nächstes Treffen. Sonst... hicks... stecken Sie mich noch an, und ich... äh... hab noch Wege zu gehen, Geschäfte... warten wohl! Passen Sie auf sich auf... hicks... und auf Ihre Frau!";
				link.l1.go = "PierTalkTavern4";
				WaitDate("", 0, 0, 0, 4, 10);
				LAi_AlcoholSetDrunk(pchar, 71, 5600);
				notification("Proviantverbrauch auf dem Schiff -15%", "None");
			}
			else
			{
				dialog.text = "Ganz schön starkes Zeug! Ich spüre schon, noch ein oder zwei Schlucke, und ich... hicks... werde ein Lied anstimmen, dass ganz Fort-de-France es hören kann!";
				link.l1 = "Pierre, heb dir das Lied lieber für später auf... für unser nächstes Treffen. Sonst... hicks... stecken Sie mich noch an, und ich... äh... hab noch Wege zu gehen, Geschäfte... warten wohl! Passen Sie auf sich auf... hicks... und auf Ihre Frau!";
				link.l1.go = "PierTalkTavern4";
				WaitDate("", 0, 0, 0, 4, 10);
				LAi_AlcoholSetDrunk(pchar, 71, 5600);
			}
		break;
		
		case "PierTalkTavern4":
			dialog.text = "Ach, Kapitän... also wirklich... danke für alles! Ich stehe in Ihrer Schuld, verstehen Sie? Sollten Sie jemals wieder hierher kommen... wir... wir heißen Sie immer willkommen wie... wie einen Bruder! Ehrlich! Ach... wir werden bestimmt wieder einmal zusammen trinken!";
			link.l1 = "Bleiben Sie standhaft, Pierre... ich... hicks... ich mache mich besser auf den Weg, solange ich noch auf meinen Beinen stehen kann!";
			npchar.dialog.currentnode = "RepeatTavern";
			link.l1.go = "Exit2";
			CloseQuestHeader("VPVL");
		break;
		
		case "Exit2":
			DialogExit()
			LAi_Fade("VPVL_ExitFromTableVPVL", "VPVL_PierLivingTavern");
			DeleteAttribute(pchar, "questTemp.VPVL_Delete_Ship_RemoveFlag");
		break;
		
		case "RepeatTavern":
			dialog.text = "Trinket auf das Mee-e-er, und auf den Wi-i-ind... hicks... auf unseren Fischzug im Morgengrauen!.. Verflucht, wie ging’s dann weiter? Kapitän!.. Sind Sie noch da? Wirt... hicks... den besten Rum auf diesen Tisch!";
			link.l1 = "Ich gehe schon, Pierre! Hicks... solange ich noch in der Lage bin, mein Schiff zu finden!";
			link.l1.go = "Exit";
		break;
		
		case "MeetingInTneCity":
			dialog.text = ""+pchar.name+"! Was für eine Freude, Sie zu sehen! Wie wär’s mit einem Glas Rum? Auf unser Wiedersehen!";
			link.l1 = "Ich freue mich ebenfalls, Sie zu sehen, Pierre. Aber leider muss ich diesmal ablehnen. Es gibt noch viel zu tun, und ich muss einen klaren Kopf bewahren. Vielleicht ein andermal?";
			link.l1.go = "MeetingInTneCity1";
		break;
		
		case "MeetingInTneCity1":
			dialog.text = "Aber natürlich, Kapitän. Erst die Arbeit, dann das Vergnügen. Ich hoffe, wir sehen uns bald wieder – und dann trinken wir bestimmt!";
			link.l1 = "Auf jeden Fall, Pierre. Bis bald!";
			link.l1.go = "Exit";
			npchar.dialog.currentnode = "ExitRepeat";
		break;
		
		case "ExitRepeat":
			dialog.text = "Kapitän! Haben Sie sich bereits freigemacht?";
			link.l1 = "Leider nein, Pierre. Die Pflichten lassen mich noch nicht los.";
			link.l1.go = "Exit";
		break;
	}
}   