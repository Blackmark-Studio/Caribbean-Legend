void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp, addGold;
	string attrL, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Wollten Sie etwas?";
			link.l1 = "Nein, nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> Шарль на носу корабля, Алонсо подходит с диалогом
		case "StartSailor":
			dialog.text = "Hübsch, nicht wahr?";
			link.l1 = "Diese Schönheit versucht mich seit zwei Monaten zu töten. Bisher ohne Erfolg.";
			link.l1.go = "StartSailor_1_fencing";
			link.l2 = "Durchaus. Manchmal erinnert das Meer daran, wie klein wir Menschen wirklich sind.";
			link.l2.go = "StartSailor_1_leadership";
			link.l3 = "Ich habe gelernt, dass es auf See nur zwei Zustände gibt: Langeweile oder Terror. Das hier... ist anders.";
			link.l3.go = "StartSailor_1_fortune";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;
		
		case "StartSailor_1_fencing":
			dialog.text = "Ha! Zum ersten Mal auf See, Monsieur? Wenn es so ruhig ist, kann jeder Kapitän spielen. Genießen Sie den Moment also.";
			link.l1 = ""+GetFullName(pchar)+". Ein Edelmann, wohlgemerkt. Nicht 'Monsieur', sondern Herr.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "StartSailor_1_leadership":
			dialog.text = "Ha! Zum ersten Mal auf See, Monsieur? Wenn es so ruhig ist, kann jeder Kapitän spielen. Genießen Sie den Moment also.";
			link.l1 = ""+GetFullName(pchar)+". Ein Edelmann, wohlgemerkt. Nicht 'Monsieur', sondern Herr.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "StartSailor_1_fortune":
			dialog.text = "Ha! Zum ersten Mal auf See, Monsieur? Wenn es so ruhig ist, kann jeder Kapitän spielen. Genießen Sie den Moment also.";
			link.l1 = ""+GetFullName(pchar)+". Ein Edelmann, wohlgemerkt. Nicht 'Monsieur', sondern Herr.";
			link.l1.go = "StartSailor_2";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;

		case "StartSailor_2":
			dialog.text = "Wie Ihr wünscht, Herr. Also dann, erste Seereise für Euch, Herr "+pchar.lastname+"?";
			link.l1 = "Ist es so offensichtlich? Ja, meine erste Reise. Und ich bin nicht für enge Kajüten und vergammelten Schiffszwieback geschaffen.";
			link.l1.go = "StartSailor_3";
		break;

		case "StartSailor_3":
			dialog.text = "Klar wie Kloßbrühe, dass Ihr ein Landei seid, Herr.";
			link.l1 = "Hütet Eure Zunge! Einem Ehrenmann würde ich den Handschuh hinwerfen und Genugtuung fordern. Aber einem Bauernlümmel wie Euch - schneide ich einfach die Ohren ab.";
			link.l1.go = "StartSailor_4";
		break;
		
		case "StartSailor_4":
			dialog.text = "Vielleicht in Paris. Aber hier können einen solche Worte zu den Fischen schicken. Ich würde nicht mit der Klinge herumfuchteln, Herr - und bringt den Kapitän nicht dazu zu bereuen, dass er Euch bewaffnet auf seinem Deck wandeln lässt. Den letzten Unruhestifter schickte er in den Laderaum - mit schimmligem Schiffszwieback und Bilgenwasser, das selbst die Ratten nicht trinken mochten. Und wisst Ihr was? Der Kerl musste noch draufzahlen, als wir den Hafen erreichten.";
			link.l1 = "Was kann man schon erwarten... Nun gut, vergessen wir dieses Missverständnis. Ich muss mich ständig daran erinnern, dass dieser Kahn weit vom Louvre entfernt ist.";
			link.l1.go = "StartSailor_5";
		break;

		case "StartSailor_5":
			dialog.text = "Äh? Der Louvre? Was soll das denn sein?";
			link.l1 = "Ha! Der Louvre ist ein Palast für Auserwählte. Bälle, Empfänge, Intrigen...";
			link.l1.go = "StartSailor_6";
		break;

		case "StartSailor_6":
			dialog.text = "Ach so... ein Bordell also. Davon haben wir auch genug. Nicht gerade für Auserwählte - zahlt nur und alles gehört euch.";
			link.l1 = "Ha! Du liegst nicht weit von der Wahrheit entfernt, Seemann.";
			link.l1.go = "StartSailor_7";
		break;

		case "StartSailor_7":
			dialog.text = "Ich heiße übrigens Alonso. Und was hat Euch hierher an den Rand der Welt verschlagen, Herr? Kaum vorstellbar, dass Ihr den Atlantik überquert habt, nur um mit einem einfachen Matrosen zu streiten.";
			link.l1 = "Mein Vater ist krank und kann unser Anwesen in Gascogne nicht verlassen. Ich wurde beauftragt, meinen... älteren Bruder zu finden. Er reiste geschäftlich hierher und man hat lange nichts mehr von ihm gehört.";
			link.l1.go = "StartSailor_8";
		break;

		case "StartSailor_8":
			dialog.text = "Warum nicht einfach einen zuverlässigen Mann schicken, statt sich selbst mit den Mühen der See zu plagen?";
			link.l1 = "Die Familie steht über allem. Ich kann ihr Schicksal keinem dahergelaufenen überlassen.";
			link.l1.go = "StartSailor_9_nobilityplus";
			link.l2 = "Ich würde ja gern - aber laut meines Vaters soll ich mich persönlich darum kümmern. Warum, weiß ich nicht.";
			link.l2.go = "StartSailor_9_nobilityminus";
		break;
		
		case "StartSailor_9_nobilityplus":
			dialog.text = "Und wie heißt Euer Bruder?";
			link.l1 = "Michelle de Monper.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "StartSailor_9_nobilityminus":
			dialog.text = "Und wie heißt Euer Bruder?";
			link.l1 = "Michelle de Monper.";
			link.l1.go = "StartSailor_10";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "StartSailor_10":
			dialog.text = "De Monper? Und Ihr seid "+pchar.lastname+"? Wie kommt das?";
			link.l1 = "Und starrt mich nicht so an. Ich bin ehelicher Sohn. Trage nur den Namen meiner Mutter.";
			link.l1.go = "StartSailor_11";
		break;

		case "StartSailor_11":
			dialog.text = "Nichts, wofür man sich schämen müsste. Ihr passt gut hierher – in der Neuen Welt hat jeder Zweite irgendeine Geschichte. Ich zum Beispiel...";
			link.l1 = "Ich schäme mich nicht! Erzähl mir lieber von Martinique. Ist das eine große Stadt? So wie Toulouse?";
			link.l1.go = "StartSailor_12";
		break;

		case "StartSailor_12":
			dialog.text = "Eine Stadt? Ha! Martinique ist eine ganze Insel. Eine der größten in Frankreichs Besitzungen in der Karibik. Dort wächst scharfer Kaffee, man fördert höllischen Schwefel, und es werden die schönsten Frauen der Welt geboren. Eine großartige Mischung, wie ich finde.";
			link.l1 = "Kaffee und Schwefel interessieren mich nicht. Aber warte... eine Insel? Wie soll ich meinen Bruder auf einer ganzen Insel finden?";
			link.l1.go = "StartSailor_13";
		break;
		
		case "StartSailor_13":
			dialog.text = "Macht Euch keine Sorgen. Saint-Pierre ist ein kleines Städtchen – nicht der Louvre natürlich, aber auch kein Dschungel. Aber im banditenverseuchten Le François, Gott bewahre, hat ein anständiger Mensch nichts verloren.";
			link.l1 = "Wenn es nötig ist, gehe ich auch zu den Banditen. Michelle hat mich immer aus Schwierigkeiten geholt. Jetzt bin ich dran.";
			link.l1.go = "StartSailor_14";
		break;

		case "StartSailor_14":
			dialog.text = "Nicht schlecht gesagt... für ein Landratte.";
			link.l1 = "Schon wieder diese Leier? Wie lange noch bis zum verdammten Martinique?";
			link.l1.go = "StartSailor_15";
		break;

		case "StartSailor_15":
			dialog.text = "Fünf Tage.";
			link.l1 = "Fünf?!";
			link.l1.go = "StartSailor_16";
		break;

		case "StartSailor_16":
			dialog.text = "Mindestens. Und wenn Piraten angreifen, kommen wir vielleicht gar nicht an. Die Kleinen Antillen sind gefährliches Pflaster, selbst wenn wir keine wertvolle Fracht an Bord haben.";
			link.l1 = "Außer den Passagieren!";
			link.l1.go = "StartSailor_17";
		break;

		case "StartSailor_17":
			dialog.text = "Ha-ha! Keine Sorge. Im schlimmsten Fall verstecke ich Euch persönlich im Laderaum – kein Pirat würde auf die Idee kommen, einen gascognischen Edelmann zwischen Rumfässern zu suchen! Wir sind doch keine Narren – einen lebenden Gascogner mit Rum zu mischen – das knallt schlimmer als Pulver, ha-ha!";
			link.l1 = "Ha! Zum Glück ist der Rum schon vor einem Monat ausgegangen!";
			link.l1.go = "StartSailor_18";
		break;

		case "StartSailor_18":
			dialog.text = "Äh... solche Dinge solltet Ihr besser nicht laut sagen. Sonst denken die Leute noch, Ihr wärt schuld an unserem Rumunglück.";
			link.l1 = "Schon gut, Alonso, ich werde mich zurückhalten. Diese Brühe kommt mir eh nie in den Mund. Und was Deinen genialen Plan angeht, mich vor der Schlacht in den Laderaum zu stecken – vergiss es.";
			link.l1.go = "StartSailor_20";
		break;

		case "StartSailor_20":
			dialog.text = "Warum denn das?";
			link.l1 = "Ich bin Edelmann, führe mein Schwert mit sicherer Hand und werde mich nicht im Laderaum verstecken.";
			link.l1.go = "StartSailor_21_fencing";
			link.l2 = "Wenn es losgeht – werde ich das Schiff verteidigen und mit allen anderen kämpfen. Was denn sonst?";
			link.l2.go = "StartSailor_21_leadership";
			link.l3 = "Ich entscheide selbst – wann zu kämpfen ist und wann zu fliehen. Schauen wir mal, was die Lage erfordert.";
			link.l3.go = "StartSailor_21_fortune";
			locCameraFromToPos(-14.85, 4.73, 5.82, true, -10.30, 4.52, 6.14);
		break;
		
		case "StartSailor_21_fencing":
			dialog.text = "Ha. Vielleicht steckt doch etwas in Euch. Aber seid auf der Hut – die Karibik häutet gern jene, die mit erhobenem Haupt auftreten. Ein Treffen mit der Vorhut der Piraten würdet Ihr nicht überleben. Ganz zu schweigen davon, dass Euch der erste Lump hinter den Toren von Saint-Pierre niederstechen würde.";
			link.l1 = "Du kennst mich überhaupt nicht.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "StartSailor_21_leadership":
			dialog.text = "Ha. Vielleicht steckt doch etwas in Euch. Aber seid auf der Hut – die Karibik häutet gern jene, die mit erhobenem Haupt auftreten. Ein Treffen mit der Vorhut der Piraten würdet Ihr nicht überleben. Ganz zu schweigen davon, dass Euch der erste Lump hinter den Toren von Saint-Pierre niederstechen würde.";
			link.l1 = "Du kennst mich überhaupt nicht.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "StartSailor_21_fortune":
			dialog.text = "Ha. Vielleicht steckt doch etwas in Euch. Aber seid auf der Hut – die Karibik häutet gern jene, die mit erhobenem Haupt auftreten. Ein Treffen mit der Vorhut der Piraten würdet Ihr nicht überleben. Ganz zu schweigen davon, dass Euch der erste Lump hinter den Toren von Saint-Pierre niederstechen würde.";
			link.l1 = "Du kennst mich überhaupt nicht.";
			link.l1.go = "StartSailor_22";
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;

		case "StartSailor_22":
			dialog.text = "Aber ich kenne die Neue Welt und ihre Bewohner. Wenn Ihr nicht plant, in den Kontorbüchern zu versauern oder einem Gouverneur zu dienen, müsst Ihr alles von Grund auf lernen.";
			link.l1 = "Zum Glück habe ich nicht vor, hier lange zu bleiben.";
			link.l1.go = "StartSailor_23";
		break;
		
		case "StartSailor_23":
			dialog.text = "Das denkt Ihr. Passagiere zurück nach Europa nehmen wir selten mit. Die einen sterben – an Fieber, am Galgen oder durch eine Kugel. Die anderen bleiben – für immer. Ich habe zarte Aristokraten zu Kapitänen werden sehen, und berüchtigte Räuber zu geachteten Plantagenbesitzern. Und ich habe glänzende Offiziere zu bettelarmen Landstreichern verkommen sehen.";
			link.l1 = "Verlockend, verdammt noch mal, aber ich kehre nach Frankreich zurück. Man erwartet mich dort.";
			link.l1.go = "StartSailor_24";
		break;

		case "StartSailor_24":
			dialog.text = "Ach ja, richtig. Der kranke Vater?";
			link.l1 = "Sagen wir... da ist eine Dame, deren Ehemann mich in Paris lieber nicht sehen möchte. Aber ein paar Monate, und die Gemüter haben sich beruhigt.";
			link.l1.go = "StartSailor_25";
		break;

		case "StartSailor_25":
			dialog.text = "Ha-ha-ha! Dann seid Ihr hier genau richtig. Die Karibik ist ein Paradies für Männer, die vor eifersüchtigen Ehemännern fliehen. Und die Zeit vergeht hier wie im Flug. Gebt Euch etwas Zeit – Ihr werdet noch zum Seemann!";
			link.l1 = "Eher schon zum Kapitän. Als einfacher Matrose tauge ich nichts. Ich bin nicht für Handarbeit gemacht.";
			link.l1.go = "StartSailor_26";
		break;

		case "StartSailor_26":
			dialog.text = "In Frankreich herrschen Menschen durch Geburtsrecht, aber an Bord ist der Kapitän König, Richter und Gott. Niemand weiß, was er durchmachen musste, um seinen Dreispitz zu verdienen. Hier bekommt jeder, was er verdient. Wie wir an Deck sagen – jedem das Seine.";
			link.l1 = "Was für ein Unsinn. Apropos Kapitäne – ich muss mit dem Euren sprechen. Er hat nach mir gefragt. Mach's gut, Alonso.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_StartKino_6");
		break;
		
		// <-- Шарль на носу корабля, матрос подходит с диалогом
		
		// --> С Алонсо можно в любой момент поговорить
		case "AlonsoWait":
			dialog.text = "Wolltet Ihr etwas fragen?";
			if (PCharDublonsTotal() >= 60 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Alonso"))
			{
				link.l1 = "Ich komme von Monsieur Pinchon.";
				link.l1.go = "AlonsoGold_2";
			}
			link.l2 = "Nichts.";
			link.l2.go = "AlonsoWait_2";
		break;

		case "AlonsoGold_2":
			dialog.text = "Ha! Unser Vierauge hat Euch also auch eingespannt?";
			link.l1 = "Vierauge?";
			link.l1.go = "AlonsoGold_3";
		break;

		case "AlonsoGold_3":
			dialog.text = "Habt Ihr seine Brille gesehen? Na also! Aber im Ernst – Monsieur Pinchon genießt bei der Mannschaft Respekt. Gute Ärzte sind auf einem Schiff immer gefragt. Und als Zahlmeister taugt er auch.";
			link.l1 = "Was habt Ihr mit ihm zu klären?";
			link.l1.go = "AlonsoGold_4";
		break;

		case "AlonsoGold_4":
			dialog.text = "Äh... Verzeiht, aber das ist eine interne Angelegenheit. Keine Sorge, wir brechen keine Schiffsgesetze.";
			link.l1 = "Und die normalen Gesetze?";
			link.l1.go = "AlonsoGold_5";
		break;

		case "AlonsoGold_5":
			dialog.text = "Die gehen uns nichts an. Und wie viel soll ich bekommen?";
			if (PCharDublonsTotal() >= 40)
			{
				link.l1 = "40 Dublonen.";
				link.l1.go = "AlonsoGold_DatDeneg_3_gold40";
			}
			if (PCharDublonsTotal() >= 50)
			{
				link.l2 = "50 Dublonen.";
				link.l2.go = "AlonsoGold_DatDeneg_3_gold50";
			}
			if (PCharDublonsTotal() >= 60)
			{
				link.l3 = "60 Dublonen.";
				link.l3.go = "AlonsoGold_DatDeneg_3_gold60";
			}
			link.l4 = "Ich muss das nochmal überprüfen. Ich komme später zurück.";
			link.l4.go = "AlonsoWait_2";
		break;
		
		case "AlonsoGold_DatDeneg_3_gold40":
			dialog.text = "Da ist es, das Goldstück. Jetzt halt dich fest, Saint-Pierre! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(40);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold50":
			dialog.text = "Da ist es, das Goldstück. Jetzt halt dich fest, Saint-Pierre! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(50);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoGold_DatDeneg_3_gold60":
			dialog.text = "Da ist es, das Goldstück. Jetzt halt dich fest, Saint-Pierre! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "AlonsoWait_2";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(60);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Alonso = true;
		break;
		
		case "AlonsoWait_2":
			DialogExit();
			NextDiag.CurrentNode = "AlonsoWait";
		break;
		
		// <-- С Алонсо можно в любой момент поговорить
		
		// --> капитан на корабле, который идёт из Европы
		case "Captain":
			dialog.text = "Ah, "+pchar.name+". Ihr habt Euch ja nicht gerade beeilt. Wenn der Kapitän eines Schiffes Euch sprechen will, habt Ihr unverzüglich zu erscheinen. Habt Ihr ein Problem mit der Befolgung von Befehlen?";
			link.l1 = "Ich bin keine Befehle gewohnt, Kapitän.";
			link.l1.go = "Captain_2_fencing";
			link.l2 = "Verzeiht, Kapitän, ich wurde aufgehalten.";
			link.l2.go = "Captain_2_leadership";
			link.l3 = "Man hat mir bereits deutlich gemacht, dass auf Eurem Schiff Eure Regeln gelten.";
			link.l3.go = "Captain_2_sailing";
			if (bBettaTestMode)
			{
				link.l9 = "BetaTest (Training überspringen und das Spiel in Martinique beginnen)";
				link.l9.go = "BetaTest_StartGame";
			}
			pchar.questTemp.SharlieTutorial_CaptainDialog = true;
		break;

		case "Captain_2_fencing":
			dialog.text = "Ich lasse meine Autorität nicht in Frage stellen. Ihr habt keine Vorstellung davon, wie oft Passagieren auf See etwas Ungutes widerfährt. Ihr habt großes Glück, dass ich daran interessiert bin, Euch wohlbehalten nach Saint-Pierre zu bringen.";
			link.l1 = "Worauf wollt Ihr hinaus?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "Captain_2_leadership":
			dialog.text = "Entschuldigung angenommen. Genießt den Moment. Es wird wohl eine Weile dauern, bis Ihr wieder so einen Sonnenuntergang erleben dürft.";
			link.l1 = "Worauf wollt Ihr hinaus?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "Captain_2_sailing":
			dialog.text = "Gut, dass Ihr während dieser Überfahrt wenigstens etwas gelernt habt. Die Autorität eines Kapitäns ist absolut – und manchmal reicht sie sogar an Land, weit weg vom Schiff.";
			link.l1 = "Worauf wollt Ihr hinaus?";
			link.l1.go = "Captain_3";
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		case "Captain_3":
			dialog.text = "Kapitän. Ich bitte Euch, mich gemäß dem Seereglement korrekt anzusprechen.";
			link.l1 = "Worauf wollt Ihr hinaus, Kapitän?";
			link.l1.go = "Captain_4";
		break;

		case "Captain_4":
			dialog.text = "Ich wollte Euch mitteilen, dass wir die Segel gestrichen und treiben gelassen haben. Leider wird sich Eure Ankunft auf Martinique um ein paar Tage verzögern.";
			link.l1 = "Aber warum, Kapitän?";
			link.l1.go = "Captain_5";
		break;

		case "Captain_5":
			dialog.text = "Weil ich es so beschlossen habe.";
			link.l1 = "Hat das etwas mit unserer gestrigen Begegnung mit dem Handelskonvoi zu tun, der nach... wie hieß das noch...";
			link.l1.go = "Captain_6";
		break;

		case "Captain_6":
			dialog.text = "Capsterville. Hört zu, "+pchar.name+": Ich muss ein ernstes Wort mit Euch reden. Ich lade Euch zum Abendessen in meine Kajüte ein. Wenn die Glasen geschlagen sind, können wir die letzte Flasche Wein an Bord wie zivilisierte Menschen leeren.";
			link.l1 = "Danke für die Einladung. Es ist mir eine Ehre, Kapitän.";
			link.l1.go = "Captain_7";
		break;

		case "Captain_7":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "Gebt mir Bescheid, wenn Ihr bereit seid. Wir haben noch etwas Zeit, also könnt Ihr Euch an Bord umsehen – solange Ihr meine Leute nicht bei der Arbeit stört.";
				npchar.SharlieTutorial_question_0 = true;
			}
			else dialog.text = "Noch Fragen?";
			link.l1 = "(Angelegenheiten abschließen) Ich bin bereit, Kapitän. Mit Euch – trinke ich sogar Burgunder!";
			link.l1.go = "Captain_8";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "Was begutachtet Ihr da durch Euer Fernrohr... Kapitän?";
				link.l2.go = "Captain_7_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Kapitän, ich hatte das Vergnügen, mich mit einem gewissen Alonso zu unterhalten. Was ist seine Funktion an Bord?";
				link.l3.go = "Captain_7_question_2_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_3"))
			{
				link.l4 = "Kapitän, erzählt mir etwas über Euer Schiff. Eine Pinasse, nicht wahr?";
				link.l4.go = "Captain_7_question_3_1";
			}
			link.l5 = "Bis später, Kapitän.";
			link.l5.go = "Captain_7_exit";
			// теперь можно пострелять из пушки
			sld = &Locations[FindLocation("Quest_Ship_deck_Medium_trade")];
			SetLocatorEvent(sld.id, "event3", "SharlieTutorial_cannon_1");
		break;
		
		case "Captain_7_exit":
			DialogExit();
			NextDiag.CurrentNode = "Captain_7";
			if (!CheckAttribute(npchar, "SharlieTutorial_Zapis"))
			{
				npchar.SharlieTutorial_Zapis = true;
				AddQuestRecord("SharlieTutorial", "0.1");
			}
		break;
		
		case "Captain_7_question_1_1":
			dialog.text = "Nichts Konkretes, ich beobachte nur den Horizont. Das Schiff liegt im Drift – wir sind leichte Beute.";
			link.l1 = "Haltet Ihr nach Piraten Ausschau?";
			link.l1.go = "Captain_7_question_1_2";
		break;

		case "Captain_7_question_1_2":
			dialog.text = "Oder Spanier. Wir segeln unter französischer Flagge und ohne Eskorte, und die Kleinen Antillen sind ein wahres Durchgangszentrum – das Revier von Jacques Barbazon.";
			link.l1 = "Wer ist das? Ein Gouverneur?";
			link.l1.go = "Captain_7_question_1_3";
		break;

		case "Captain_7_question_1_3":
			dialog.text = "Schlimmer – einer der Piratenbarone. Diese Galgenvögel haben so etwas wie eine Organisation gegründet und nennen sich die Brüder der Küste. Sie haben die Karibik in sechs Zonen aufgeteilt und in jeder einen Baron eingesetzt, damit sie sich nicht gegenseitig an die Gurgel gehen.";
			link.l1 = "Warum tut die Obrigkeit nichts dagegen?";
			link.l1.go = "Captain_7_question_1_4";
		break;

		case "Captain_7_question_1_4":
			dialog.text = "Ihr seid naiv, "+pchar.name+". Die Piraterie existiert nur, weil die lokalen Behörden ihnen erlauben, ihre Schiffe in bestimmten Häfen zu reparieren und zu versorgen – im Austausch gegen einen Großteil der Beute. Es ist unangenehm, das zuzugeben, aber die einzigen, die überhaupt etwas gegen diese schwarze Pest unternehmen, sind die Spanier. Ohne sie müssten wir unser Schiff nicht nur mit teurer Artillerie ausrüsten, sondern auch noch eine Eskorte anheuern.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "Captain_7_question_2_1":
			dialog.text = "Er ist der Obermatrose. Ich weiß wenig über ihn, aber eines ist sicher: Wenn jeder Mensch ein Skelett im Schrank hat, dann ist es bei Alonso ein ganzes Massengrab.";
			link.l1 = "Das klingt, als würdet Ihr ihm nicht trauen.";
			link.l1.go = "Captain_7_question_2_2";
		break;

		case "Captain_7_question_2_2":
			dialog.text = "Ganz und gar nicht. Glaubt Ihr, es ist einfach, erfahrene Leute für die Crew zu finden? Es braucht mindestens ein Jahr und einen guten Bootsmann, damit der in Tavernen angeheuerte Haufen wenigstens ansatzweise wie eine Besatzung funktioniert. Außerdem ist Alonso die Stimme der Mannschaft. Ein Kapitän kommuniziert nicht mit den einfachen Matrosen, aber es wäre dumm und lebensgefährlich, ihre Interessen zu ignorieren. Und genau die vertritt Alonso, wenn es darauf ankommt.";
			link.l1 = "Und was passiert, wenn die Mannschaft unzufrieden ist?";
			link.l1.go = "Captain_7_question_2_3";
		break;
		
		case "Captain_7_question_2_3":
			dialog.text = "Ich werde gehängt, und Ihr – einfach niedergestochen. Keine Angst. Solange die Mannschaft Sold, Rum, Proviant und medizinische Versorgung erhält – ist der Vertrag zwischen Kapitän und Crew erfüllt. Ich setze ihr Leben nicht leichtfertig aufs Spiel, bestrafe nicht willkürlich, teile die Beute und sorge ab und zu für kostenlosen Alkohol und andere Annehmlichkeiten an Land. So wird das fragile Gleichgewicht gewahrt, und das Schiff erreicht stets sein Ziel.";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_2 = true;
		break;

		case "Captain_7_question_3_1":
			dialog.text = "Ihr habt einen wunden Punkt getroffen, "+pchar.name+"! Über meine Schönheit könnte ich ewig sprechen. Dritte Klasse, zwanzig Kanonen, hervorragende Geschwindigkeit – lasst Euch nicht vom Begriff ‚Handelsschiff‘ täuschen!";
			link.l1 = "Kanonen und Geschwindigkeit habe ich verstanden. Aber ‚Klasse‘? ‚Handelsschiff‘?";
			link.l1.go = "Captain_7_question_3_2";
		break;

		case "Captain_7_question_3_2":
			dialog.text = "Die Klassen – das ist eine grobe Einteilung von Schiffen nach der Anzahl ihrer Kanonen. Die siebte Klasse ist kaum mehr als ein Boot, die erste eher eine Festung. Aber wiederholt das bloß nicht in Europa, vor allem nicht in Gegenwart von Marineoffizieren.";
			link.l1 = "Warum? Ist das irgendein Seemannswitz?";
			link.l1.go = "Captain_7_question_3_3";
		break;

		case "Captain_7_question_3_3":
			dialog.text = "Man wird Euch für einen völligen Laien halten und auslachen. Um ehrlich zu sein – bei einer echten Flotte funktioniert die Klasseneinteilung ganz anders und gilt nur für Kriegsschiffe. Aber hier in der Karibik, wie üblich, machen wir alles auf unsere Weise.";
			link.l1 = "Und was meintet Ihr, als Ihr Euer Schiff ‚Handelsschiff‘ nanntet?";
			link.l1.go = "Captain_7_question_3_4";
		break;

		case "Captain_7_question_3_4":
			dialog.text = "Noch so eine Konvention. Kriegsschiffe – stärker und mit besserer Feuerkraft, Freibeuter – rauben und fliehen. Handelsschiffe – bieten viel Platz für nützliche Ladung, Mannschaft oder Kanonen, aber man muss einen Kompromiss schließen, sonst wird das Schiff unerträglich langsam. Es gibt auch vielseitige Schiffe, aber über die lässt sich wenig sagen – sie passen sich einfach den Bedürfnissen ihres Besitzers an.";
			link.l1 = "Ihr seid richtig lebhaft geworden, Kapitän.";
			link.l1.go = "Captain_7_question_3_5";
		break;

		case "Captain_7_question_3_5":
			dialog.text = "Ich liebe mein Schiff, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "Captain_7";
			npchar.SharlieTutorial_question_3 = true;
		break;

		case "Captain_8":
			if (IsEquipCharacterByItem(pchar, "hat3"))
			{
				dialog.text = "Dann habt Ihr Glück – Burgunder ist alles, was mir noch bleibt... Wartet mal, "+pchar.name+". Woher habt Ihr meinen alten Hut?!\nWartet. He! Auf den Marsen! Was ist da los?";
				ChangeCharacterComplexReputation(pchar, "nobility", -1);
			}
			else dialog.text = "Dann habt Ihr Glück – Burgunder ist alles, was mir noch bleibt\nWartet. He! Auf den Marsen! Was ist da los?";
			link.l1 = "...";
			link.l1.go = "Captain_9";
		break;
		
		case "Captain_9":
			DialogExit();
			DelLandQuestMark(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga");
		break;
		
		case "BetaTest_StartGame":	// досрочный выход на сушу
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		
		// <-- капитан на корабле, который идёт из Европы
		
		// --> Диалог с охранником каюты
		case "OhrannikCabin":
			dialog.text = "Verzeihung, Herr "+pchar.lastname+", aber Ihr habt keinen Zutritt.";
			link.l1 = "Ich bin im Kapitänskajüten willkommen. Das solltet Ihr euch merken.";
			link.l1.go = "OhrannikCabin_1";
			link.l2 = "Wie schade, dass mein heimtückischer Plan gescheitert ist. Lebt wohl, Matrose.";
			link.l2.go = "exit";
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 15) NextDiag.TempNode = "OhrannikCabin";
			else NextDiag.TempNode = "OhrannikCabin_again";
			if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikStay"))
			{
				LAi_SetStayType(npchar);
				npchar.SharlieTutorial_OhrannikStay = true;
			}
		break;

		case "OhrannikCabin_1":
			dialog.text = "Verzeihung, Herr, aber die Umstände haben sich geändert.";
			link.l1 = "Was ist denn passiert?";
			link.l1.go = "OhrannikCabin_2";
		break;

		case "OhrannikCabin_2":
			dialog.text = "Die Reise neigt sich dem Ende zu, und der Kapitän möchte nicht, dass jemand sein Hab und Gut plündert und dann ungestraft zu den Banditen nach Le François abhaut.";
			link.l1 = "Ich glaube kaum, dass der Kapitän mich meinte, als er diesen Befehl erteilte.";
			link.l1.go = "OhrannikCabin_3";
		break;

		case "OhrannikCabin_3":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 15)
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Nun... Ihr habt recht. Außerdem habt Ihr schon mehrmals in der Kapitänskajüte gespeist. Geht nur, Herr "+pchar.lastname+".";
					link.l1 = "Na also!";
					link.l1.go = "OhrannikCabin_4";
					notification("Prüfung bestanden", SKILL_Leadership);
				}
				else
				{
					dialog.text = "Insin... insinuwas? Ich meinte nichts dergleichen, Herr "+pchar.lastname+"!";
					link.l1 = "Dann seid Ihr verpflichtet, mich durchzulassen.";
					link.l1.go = "OhrannikCabin_3_1";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "SharlieTutorial_OhrannikFail"))
				{
					dialog.text = "Herr, Ihr versteht doch sicher, dass die Kapitänskajüte kein Durchgang ist. Und Befehle werden bei uns strikt befolgt.";
					link.l1 = "Verdammt, ich will endlich festen Boden unter den Füßen haben. Das ist einfach erniedrigend!";
					npchar.SharlieTutorial_OhrannikFail = true;
				}
				else
				{
					dialog.text = "Herr, wir haben das bereits besprochen. Ich kann Euch nicht durchlassen.";
					link.l1 = "Ihr seid wirklich stur, Matrose. Lebt wohl.";
				}
				link.l1.go = "exit";
				NextDiag.TempNode = "OhrannikCabin_again";
				notification("Fähigkeit nicht ausreichend entwickelt (15)", SKILL_Leadership);
			}
		break;
		
		case "OhrannikCabin_3_1":
			dialog.text = "Ach, na gut. Ich denke, es wird kein großes Unglück daraus entstehen.";
			link.l1 = "Na also!";
			link.l1.go = "OhrannikCabin_4";
			notification("Prüfung bestanden", SKILL_Leadership);
		break;

		case "OhrannikCabin_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			LocatorReloadEnterDisable("Quest_Ship_deck_Medium_trade", "reload_cabin", false);
		break;

		case "OhrannikCabin_again":
			dialog.text = "Noch etwas, Herr? Ich kann Euch nicht durchlassen — der Kapitän fürchtet um sein Hab und Gut.";
			link.l1 = "Was wollt Ihr damit sagen, Matrose? Dass ich ein Dieb bin? Vorsicht mit Euren Worten. Das ist reine Insinuation!";
			if (CheckAttribute(npchar, "SharlieTutorial_OhrannikFail")) link.l1.go = "OhrannikCabin_3";
			else link.l1.go = "OhrannikCabin_1";
			link.l2 = "Nichts, Matrose.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OhrannikCabin_again";
		break;
		
		// <-- Диалог с охранником каюты
		
		// --> матрос ругается на ГГ, который активировал брашпиль
		case "SailorWithWindlass_1":
			dialog.text = "He, edler Trottel! Hast du den Teufel an die Winsch gebunden?!\nMit deinem königlichen Fuß hast du die Sperre gelöst! Willst du uns alle auf den Grund schicken, oder was?!\nTu uns einen Gefallen und rühr nichts an, es sei denn, es ist ein französischer Schnupfen!";
			link.l1 = "Und was ist das eigentlich?";
			link.l1.go = "SailorWithWindlass_2";
		break;

		case "SailorWithWindlass_2":
			dialog.text = "Das ist eine Winsch, du Holzkopf. Hebt den Anker. Und wenn man sie nicht stoppt – reißt sie das Schiff in Stücke oder wickelt jemanden auf wie einen Hering in ein Fass!";
			link.l1 = "Ha... Und wenn man sie in die andere Richtung dreht – senkt sie den Anker, ja?";
			link.l1.go = "SailorWithWindlass_3";
		break;

		case "SailorWithWindlass_3":
			dialog.text = "Nein, Schlauberger, dann dreht sie die Zeit zurück. Nur hast du Pech – du bist schon geboren!";
			link.l1 = "Na ja, es wurde niemand verletzt – oder? Ein erstaunlich kompliziertes Ding, so ein Schiff. Ich werde vorsichtiger sein.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_windlass_8");
			AddCharacterSkillPoints(pchar, "Sailing", 1);
		break;
		
		// <-- матрос ругается на ГГ, который активировал брашпиль
		
		// --> матрос ругается на ГГ, который активировал пушку
		case "SailorWithCannon_1":
			dialog.text = "Ihr betrachtet das lange Kanonenrohr mit demselben Staunen, wie ihr vorhin den Sonnenuntergang bewundert habt.";
			link.l1 = "Du beobachtest mich wohl gerne, Alonso. Erzähl mir lieber etwas über dieses Wunderwerk der Kriegskunst.";
			link.l1.go = "SailorWithCannon_2";
		break;

		case "SailorWithCannon_2":
			dialog.text = "Das ist eine Sechzehn-Pfund-Kanone. Nicht einmal jedes Kriegsschiff hat so etwas an Bord.";
			link.l1 = "Und trifft man damit leicht?";
			link.l1.go = "SailorWithCannon_3";
		break;

		case "SailorWithCannon_3":
			dialog.text = "Aus nächster Nähe zerschmettern wir alles. Ab hundert Yards wird es ernst. Darüber hinaus – hauptsächlich Krach und Flammen, aber immerhin.";
			link.l1 = "Ab hundert Yards macht der Gegner dasselbe.";
			link.l1.go = "SailorWithCannon_4";
		break;

		case "SailorWithCannon_4":
			dialog.text = "Stimmt. Aber da entscheidet, wer die eingespieltere Mannschaft und den besseren Schützen hat. Schade, dass unser Kanonier gerade pennt – der würde euch die ganze Kunst erklären, und euch dann eigenhändig in die Kanone stopfen, haha!";
			link.l1 = "Kanonier – das ist doch ein Offizier, oder?";
			link.l1.go = "SailorWithCannon_5";
		break;

		case "SailorWithCannon_5":
			dialog.text = "In der Regel ja. Ohne einen halbwegs fähigen Kanonier sollte man besser gar nicht erst kämpfen – da kann man die Kanonen gleich über Bord werfen und türmen.\nHandelskapitäne haben selten etwas Größeres als Sechs-Pfünder – sie verlassen sich entweder auf Eskorte oder auf Glück.\nDas ist auch sinnvoll: ohne schwere Kanonen und Munition ist das Schiff schneller, und im Laderaum ist mehr Platz für Waren.\nWenn unser Kapitän nicht so viel Geld für diese Schönheiten ausgegeben hätte – vielleicht hätten wir jetzt noch Rum. Tja!";
			link.l1 = "Und der Kapitän leitet das Feuer nicht persönlich?";
			link.l1.go = "SailorWithCannon_6";
		break;

		case "SailorWithCannon_6":
			dialog.text = "Mit einem guten Kanonier und einer eingespielten Crew braucht er das nicht. Aber ich sag euch eins: Wenn der Kapitän selbst zielt und nicht nur vom Achterdeck 'Feuer!' brüllt – gibt's mehr Löcher in den feindlichen Planken.";
			link.l1 = "Darf ich mal abfeuern?";
			link.l1.go = "SailorWithCannon_7";
			link.l2 = "Danke für die spannende Lektion, Alonso. Du bist eine wahre Schatzkiste maritimen Wissens.";
			link.l2.go = "SailorWithCannon_7_exit";
		break;
		
		case "SailorWithCannon_7_exit":
			dialog.text = "Aber sicher! Nur lasst die Kanone in Ruhe und beunruhigt nicht die Mannschaft.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_11");
		break;

		case "SailorWithCannon_7":
			dialog.text = "Feuern – eher nicht. Einen Schuss abgeben – das muss der Kapitän erlauben. Ich frag ihn gleich!";
			link.l1 = "Bloß nicht!";
			link.l1.go = "SailorWithCannon_8";
		break;

		case "SailorWithCannon_8":
			dialog.text = "Käääpt’n!";
			link.l1 = "...";
			link.l1.go = "exit";
			locCameraSleep(true);
			AddDialogExitQuestFunction("SharlieTutorial_cannon_3");
		break;

		case "CaptainWithCannon_1":
			dialog.text = "Was ist hier los, Alonso?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_2";
		break;

		case "CaptainWithCannon_2":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_3", "Quest\Sharlie\Tutorial.c");
		break;
		
		case "CaptainWithCannon_3":
			dialog.text = "Der Herr "+pchar.name+" schlägt vor, einen Schuss aus der Kanone abzugeben – ausschließlich zu Übungszwecken.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_4";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;
		
		case "CaptainWithCannon_4":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_5", "Quest\Sharlie\Tutorial.c");
		break;
		
		case "CaptainWithCannon_5":
			dialog.text = "Ich dachte, du vertrittst die Interessen der Mannschaft, Alonso. Und du schlägst vor, die nächste Wache zu wecken und den Rest auf die barbarischste Weise aufzuschrecken?";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_6";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;

		case "CaptainWithCannon_6":
			StartInstantDialog("SharlieTutorial_Sailor_10", "CaptainWithCannon_7", "Quest\\Sharlie\\Tutorial.c");
		break;

		case "CaptainWithCannon_7":
			dialog.text = "Ich denke, es schadet nicht, ihnen ein bisschen das Blut in Wallung zu bringen und sie auf Bereitschaft zu halten. Mir gefällt nicht, dass wir im Drift für alle sichtbar treiben. Hoffentlich geht das gut.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_8";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain_clone"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Captain_clone"), npchar);
		break;

		case "CaptainWithCannon_8":
			StartInstantDialog("SharlieTutorial_Captain_clone", "CaptainWithCannon_9", "Quest\\Sharlie\\Tutorial.c");
		break;

		case "CaptainWithCannon_9":
			dialog.text = "Nicht unken!... Na gut. Ein Schuss. Mit Platzpatrone.";
			link.l1 = "...";
			link.l1.go = "CaptainWithCannon_10";
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Sailor_10"));
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), npchar);
		break;
		
		case "CaptainWithCannon_10":
			dialog.text = "Viel Vergnügen, "+pchar.name+". Wir werden die Mannschaft wecken... auf Ihre Kosten, haha!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_cannon_5");
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("SharlieTutorial_Sailor_10"), pchar);
		break;
		
		// <-- матрос ругается на ГГ, который активировал пушку
		
		// --> Диалог с матросом, который хочет рома
		case "SailorWantRum":
			dialog.text = "Hätten Sie ein paar Minuten, mein Herr?";
			link.l1 = "Sprich, Matrose.";
			link.l1.go = "SailorWantRum_1";
		break;

		case "SailorWantRum_1":
			dialog.text = "Freut mich, Sie kennenzulernen, mein Herr. Ich heiße Henry. Wollen Sie etwas dazuverdienen?";
			link.l1 = "Etwas – wie viel genau?";
			link.l1.go = "SailorWantRum_2";
		break;

		case "SailorWantRum_2":
			dialog.text = "Fünfhundert Pesos.";
			link.l1 = "Wie viel?! Und was genau soll ich für so eine Summe tun? Hoffentlich keinen Aufstand anzetteln?";
			link.l1.go = "SailorWantRum_3";
		break;

		case "SailorWantRum_3":
			dialog.text = "Um Himmels willen, mein Herr! Warum so laut?";
			link.l1 = "Das ist eine Menge Geld, Matrose. Selbst in Paris könnte man davon gut leben.";
			link.l1.go = "SailorWantRum_4";
		break;

		case "SailorWantRum_4":
			dialog.text = "Ach, ich will Ihre Unwissenheit nicht ausnutzen und sage es, wie es ist: In der Karibik sind fünfhundert Pesos kein Vermögen. Kapitäne und Händler bringen so viele Waren, dass die Preise für alles Nützliche in die Höhe schnellen. Es ist absurd: Manchmal kostet ein seltener Degen so viel wie ein kleines Schiff.";
			link.l1 = "Das ist ja Wahnsinn.";
			link.l1.go = "SailorWantRum_5";
		break;

		case "SailorWantRum_5":
			dialog.text = "Was soll ich sagen? Wir alle hoffen, dass sich alles bald einpendelt und die Preise normal werden. Also, interessiert Sie das Angebot über fünfhundert Pesos?";
			link.l1 = "Zuerst möchte ich wissen, worum es überhaupt geht.";
			link.l1.go = "SailorWantRum_6";
		break;
		
		case "SailorWantRum_6":
			dialog.text = "Sie haben sicherlich von der traurigen Rumsituation an Bord gehört. Trotzdem bin ich überzeugt, dass sich mit etwas Mühe noch ein paar Flaschen auftreiben lassen. Flaschenrum ist kein Fassgebräu – hervorragender Geschmack, schützt vor Vergiftungen, stärkt Körper und Geist – kurz, ein wahres Wundermittel. Besonders am Ende der Reise, wenn einem der Horizont schon den Verstand raubt.";
			link.l1 = "Und was wirst du damit machen? Und warum suchst du nicht selbst?";
			link.l1.go = "SailorWantRum_7";
		break;

		case "SailorWantRum_7":
			dialog.text = "Wann denn bitte schön? Uns fehlt Personal, wir schuften für drei. Und den Rum werde ich weiterverkaufen – dafür finde ich schon einen Abnehmer.";
			link.l1 = "Ehrlichkeit weiß ich zu schätzen.";
			link.l1.go = "SailorWantRum_8";
		break;

		case "SailorWantRum_8":
			dialog.text = "Also, wie sieht’s aus? Ich brauche drei Flaschen.";
			link.l1 = "Ich werde mein Bestes tun, aber ich kann nichts versprechen.";
			link.l1.go = "SailorWantRum_9";
			link.l2 = "Ich glaube, ich lehne besser ab. Solche Aufgaben passen nicht zu mir.";
			link.l2.go = "SailorWantRum_10";
		break;
		
		case "SailorWantRum_9":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRum");
		break;
		
		case "SailorWantRum_10":
			dialog.text = "Schade, aber ich nehme es Ihnen nicht übel. Einen schönen Abend noch, mein Herr.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
			npchar.SailorWantRum_Done = true;
			DelLandQuestMark(npchar);
		break;

		case "SailorWantRum_PrinestiRum": // ждёт ром
			dialog.text = "Ja, Herr "+pchar.lastname+"?";
			if (GetCharacterItem(pchar, "potionrum") >= 3 && !CheckAttribute(npchar, "questTemp.SailorWantRum_Done"))
			{
				link.l1 = "Hier sind deine drei Flaschen Rum.";
				link.l1.go = "SailorWantRum_PrinestiRum_2";
			}
			if (PCharDublonsTotal() >= 42 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Anri"))
			{
				link.l2 = "Henry, ich habe etwas für dich von Monsieur Pinchon.";
				link.l2.go = "RumGold_2";
			}
			link.l3 = "Nichts.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorWantRum_PrinestiRum";
		break;

		case "RumGold_2":
			dialog.text = "Ich bin immer gern zu Diensten! Wie viel ist dieses Mal für mich vorgesehen?";
			if (PCharDublonsTotal() >= 28)
			{
				link.l1 = "28 Dublonen.";
				link.l1.go = "RumGold_DatDeneg_gold28";
			}
			if (PCharDublonsTotal() >= 35)
			{
				link.l2 = "35 Dublonen.";
				link.l2.go = "RumGold_DatDeneg_gold35";
			}
			if (PCharDublonsTotal() >= 42)
			{
				link.l3 = "42 Dublonen.";
				link.l3.go = "RumGold_DatDeneg_gold42";
			}
			link.l4 = "Ich muss alles noch einmal überprüfen. Ich komme später wieder.";
			link.l4.go = "RumGold_DatDeneg_3";
		break;
		
		case "RumGold_DatDeneg_gold28":
			dialog.text = "Ich danke Ihnen, Herr "+pchar.lastname+". Richten Sie dem Herrn Schatzmeister meine besten Grüße aus.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(28);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_gold35":
			dialog.text = "Ich danke Ihnen, Herr "+pchar.lastname+". Richten Sie dem Herrn Schatzmeister meine besten Grüße aus.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(35);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_gold42":
			dialog.text = "Ich danke Ihnen, Herr "+pchar.lastname+". Richten Sie dem Herrn Schatzmeister meine besten Grüße aus.";
			link.l1 = "...";
			link.l1.go = "RumGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(42);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Anri = true;
		break;
		
		case "RumGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorWantRum_PrinestiRum";
		break;
		
		case "SailorWantRum_PrinestiRum_2":
			dialog.text = "Danke, Herr "+pchar.lastname+". Das haben Sie wirklich geschickt angestellt!";
			link.l1 = "Ich hoffe, ich bekomme mein Geld genauso geschickt.";
			link.l1.go = "SailorWantRum_PrinestiRum_3";
			RemoveItems(pchar, "potionrum", 3);
			npchar.SailorWantRum_Done = true;
		break;

		case "SailorWantRum_PrinestiRum_3":
			dialog.text = "Vielleicht möchten Sie Ihre Bezahlung nicht in Geld erhalten?";
			link.l1 = "Du bist wohl doch nicht so ehrlich, wie du tust.";
			link.l1.go = "SailorWantRum_PrinestiRum_4";
		break;

		case "SailorWantRum_PrinestiRum_4":
			dialog.text = "Nein, nein! Wenn Sie Geld wollen – bekommen Sie Geld! Aber ich könnte Ihnen auch Wissen vermitteln.";
			link.l1 = "Was für Wissen meinst du?";
			link.l1.go = "SailorWantRum_PrinestiRum_5";
		break;

		case "SailorWantRum_PrinestiRum_5":
			dialog.text = "Ich kann Ihnen einiges über die Seefahrt beibringen. In Ihren gelehrten Büchern steht so etwas nicht.";
			link.l1 = "Na schön, gib mir die teuerste Lektion meines Lebens.";
			link.l1.go = "SailorWantRum_PrinestiRum_6";
			link.l2 = "Fünfhundert Ratschläge ersetzen keine fünfhundert Münzen. Ich nehme das Geld.";
			link.l2.go = "SailorWantRum_PrinestiRum_money";
		break;

		case "SailorWantRum_PrinestiRum_money":
			dialog.text = "Bitte sehr, Herr "+pchar.lastname+". Und nochmals vielen Dank!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;

		case "SailorWantRum_PrinestiRum_6":
			dialog.text = "Ich hoffe sehr, Herr "+pchar.name+", dass meine Lektion tatsächlich als solche empfunden wird. Wissen Sie, was Navigation ist?";
			link.l1 = "Du wirst überrascht sein, aber ich weiß es. Und ich kann sogar lesen. Navigation ist die Bestimmung der Position im Raum und die Berechnung des Kurses, zum Beispiel eines Schiffs.";
			link.l1.go = "SailorWantRum_PrinestiRum_7";
		break;
		
		case "SailorWantRum_PrinestiRum_7":
			dialog.text = "Ahh... Sie meinen Sterne und Karten. Nein, davon verstehe ich nichts. Das ist was für den Steuermann oder den Kapitän. Hier nennen wir 'Navigation' die Fähigkeit, ein Schiff zu führen und zu befehligen.";
			link.l1 = "Wer ist denn 'wir'?";
			link.l1.go = "SailorWantRum_PrinestiRum_8";
		break;

		case "SailorWantRum_PrinestiRum_8":
			dialog.text = "In der Karibik. So hat es sich eingebürgert, fragen Sie nicht warum. Je besser Sie sich mit der Navigation auskennen, desto mehr Geschwindigkeit und Wendigkeit holen Sie aus dem Schiff heraus. Und auch die Mannschaft bedient die Segel schneller. Aber das ist nicht das Wichtigste.";
			link.l1 = "Du verstehst es wirklich, Spannung aufzubauen.";
			link.l1.go = "SailorWantRum_PrinestiRum_9";
		break;

		case "SailorWantRum_PrinestiRum_9":
			dialog.text = "Je besser Ihre Navigationskenntnisse sind, desto größere Schiffe können Sie befehligen! Und wenn Sie ein Schiff steuern, das Ihre Fähigkeiten übersteigt, verlieren Sie Konzentration, Kraft und sogar Gesundheit!";
			link.l1 = "Klingt gefährlich. Erstaunlich, dass ich bisher ohne das ausgekommen bin.";
			link.l1.go = "SailorWantRum_PrinestiRum_10";
		break;

		case "SailorWantRum_PrinestiRum_10":
			dialog.text = "Zum Glück muss man nicht alles selbst wissen. Man kann immer einen guten Steuermann anheuern, der sich um die Navigation kümmert. Stellen Sie nur sicher, dass er pünktlich bezahlt wird und loyal ist. Ohne Steuermann auf einem Schiff, das Sie nicht selbst beherrschen können — das ist kein Spaß.";
			link.l1 = "Danke für die Lektion, Henry. Ich bin mir nicht sicher, ob ich das gebrauchen kann, aber Wissen schadet nie.";
			link.l1.go = "SailorWantRum_PrinestiRum_11";
			AddCharacterSkillPoints(pchar, "Sailing", 3);
		break;

		case "SailorWantRum_PrinestiRum_11":
			dialog.text = "Gern geschehen, Herr "+pchar.lastname+". Und nochmals vielen Dank!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_PrinestiRumFinal");
		break;
		
		// <-- Диалог с матросом, который хочет рома
		
		// --> Диалог со старым матросом в трюме
		case "OldSailor":
			dialog.text = "(singt) C’est la mère Michel qui a perdu son chat... Qui crie par la fenêtre à qui le lui rendra...";
			link.l1 = "Was macht Ihr hier, Matrose?";
			link.l1.go = "OldSailor_1";
			NextDiag.TempNode = "OldSailor";
		break;
		
		case "OldSailor_1":
			dialog.text = "Ich bin wohl wie Madame Michelle – suche die Katze. Aber ich schreie nicht – sie mag es nicht, wenn man sie anschreit.";
			link.l1 = "Ich sah sie heute Morgen – sie hat wieder meine Stiefel zerkratzt.";
			link.l1.go = "OldSailor_2";
		break;

		case "OldSailor_2":
			dialog.text = "Das ist noch harmlos. Die Stiefel des Kapitäns haben es schlimmer erwischt. Mögt Ihr Katzen?";
			link.l1 = "Natürlich mag ich sie.";
			link.l1.go = "OldSailor_3";
			link.l2 = "Nicht besonders.";
			link.l2.go = "OldSailor_4";
		break;

		case "OldSailor_3":
			dialog.text = "Verständlich. Wie soll man sonst diese verdammten Ratten bekämpfen?";
			link.l1 = "Aber Ihr könnt Euch doch nicht ewig auf Katzen verlassen? Sie sind ziemlich eigensinnige Kreaturen.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "OldSailor_4":
			dialog.text = "Ein Fehler. Auf Schiffen werden Katzen geschätzt. Wie soll man sonst diese verdammten Ratten bekämpfen?";
			link.l1 = "Aber Ihr könnt Euch doch nicht ewig auf Katzen verlassen? Sie sind ziemlich eigensinnige Kreaturen.";
			link.l1.go = "OldSailor_5";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "OldSailor_5":
			dialog.text = "Wahr. Deshalb müssen wir uns auf Arsen verlassen. Aber versuch das mal in der Karibik zu finden. Deshalb verlieren wir Waren – die Ratten verderben den Rum, ruinieren das Zwieback und fressen alles andere.\nUnd unser Zahlmeister sagt: „Seht es als Handelssteuer.“\nAber wir wissen es besser: er ist nur faul. Ohne unsere liebe Chantal hätte der Kapitän ihn längst in den Laderaum verbannt, um selbst Ratten zu jagen, ha-ha!";
			link.l1 = "Viel Glück mit der Katze. Ich muss los.";
			link.l1.go = "OldSailor_6";
		break;

		case "OldSailor_6":
			dialog.text = "Wartet, mein Herr. Ein einfacher Matrose sieht edle Passagiere sonst höchstens auf dem Deck – und Ihr seid bis in den Laderaum vorgedrungen!";
			link.l1 = "Neugier tötete die Katze, ha-ha!";
			link.l1.go = "OldSailor_7";
		break;
		
		case "OldSailor_7":
			dialog.text = "Interessiert Ihr Euch für die Seefahrt?";
			link.l1 = "Scheint, als hätte sich jedes Crewmitglied vorgenommen, mich als echten Seemann an Land zu schicken.";
			link.l1.go = "OldSailor_8";
		break;

		case "OldSailor_8":
			dialog.text = "Kein Wunder. Auch wenn das Meer vielen von uns nur Kummer gebracht hat, lieben wir unsere Arbeit. Und es freut einen Seemann immer, wenn ein Neuling echtes Interesse zeigt.";
			link.l1 = "...";
			link.l1.go = "OldSailor_9";
		break;

		case "OldSailor_9":
			dialog.text = "Na, sagt mal: Was ist die wichtigste Fähigkeit eines Kapitäns?";
			if (GetSummonSkillFromName(pchar, SKILL_Sailing) >= 6)
			{
				link.l1 = "Navigation. Davon hängt ab, wie groß das Schiff ist, das er führen kann.";
				link.l1.go = "OldSailor_10";
				notification("Prüfung bestanden", SKILL_Sailing);
			}
			else
			{
				link.l1 = "Ich will nicht lügen – ich weiß es nicht.";
				link.l1.go = "OldSailor_9_1";
				notification("Unzureichende Fertigkeit (6)", SKILL_Sailing);
			}
		break;

		case "OldSailor_9_1":
			dialog.text = "Seid nicht traurig, mein Herr. Sprecht mit der Crew, lauft über das Schiff. Wenn Ihr antworten könnt – erzähle ich Euch etwas sehr Interessantes. Wie einem von uns.";
			link.l1 = "Ich werde daran denken. Lebt wohl!";
			link.l1.go = "exit";
			NextDiag.TempNode = "OldSailor_again";
		break;

		case "OldSailor_10":
			dialog.text = "Richtig! Und nun eine Fangfrage: Was ist besser – Schratsegel oder Rahsegel?";
			link.l1 = "Ich will mich nicht festlegen, aber ich vermute, beide haben ihren Nutzen.";
			link.l1.go = "OldSailor_11";
		break;
		
		case "OldSailor_11":
			dialog.text = "Wieder richtig! Rahsegel sind stark, wenn der Wind von hinten kommt. Aber ein Schratsegler kreuzt und holt selbst bei Querwind auf. Es ist erfreulich zu sehen, dass Ihr Eure Zeit nicht vergeudet habt, mein Herr.";
			link.l1 = "Ich bin mir nicht sicher, ob mir dieses Wissen jemals nützen wird... Höchstens, um bei Damen der feinen Gesellschaft Eindruck zu schinden, als echter Seemann, ha-ha!";
			link.l1.go = "OldSailor_12";
		break;

		case "OldSailor_12":
			dialog.text = "Ach, ich weiß nicht, mein Herr "+pchar.name+". Ein Edelmann seid Ihr vielleicht – aber mit uns sprecht Ihr wie ein Mensch. Das schätzen wir. Unser Kapitän hat etwas im Sinn. Eine schwarze Katze ist zwischen Euch durchgelaufen.";
			link.l1 = "Was für ein Unsinn. Wovon redet Ihr, Matrose?";
			link.l1.go = "OldSailor_13";
		break;

		case "OldSailor_13":
			dialog.text = "Es wird gemunkelt, dass er nicht umsonst kürzlich einen Brief nach Capsterville mit einem vorbeifahrenden Schiff geschickt hat.\nUnd auch nicht ohne Grund treibt er seit Tagen – kurz vor Ende der Reise, wo alle nur noch schreien: 'Lasst uns endlich an Land!'";
			link.l1 = "Ich interessiere mich nicht für Gerüchte. Warum auch? Ich kann ihn einfach selbst fragen. Einem Edelmann wird er die Wahrheit nicht verweigern.";
			link.l1.go = "OldSailor_14";
		break;

		case "OldSailor_14":
			dialog.text = "Ihr kennt ihn nicht, mein Herr "+pchar.name+". Oh doch, er wird verweigern. Und wie! Er ist jetzt auch noch wütend – hat seinen Schlüssel verloren.";
			link.l1 = "Seinen Schlüssel?";
			link.l1.go = "OldSailor_15";
		break;

		case "OldSailor_15":
			dialog.text = "Von seiner Truhe in der Kajüte. Ich denke, es wird nicht schwer sein, ihn zu finden. Irgendwo muss er herumliegen.";
			link.l1 = "Den Schlüssel finden? Ich?";
			link.l1.go = "OldSailor_16";
		break;

		case "OldSailor_16":
			dialog.text = "Das liegt ganz bei Euch.\nÜbrigens, mein Herr "+pchar.name+", habt Ihr vielleicht noch Rum übrig? Ihr habt doch nicht alles Henry gegeben, ha-ha!";
			if (GetCharacterItem(pchar, "potionrum") >= 1)
			{
				link.l1 = "Ja. Nimm ihn.";
				link.l1.go = "OldSailor_17";
			}
			link.l2 = "Leider nein. Ein Wunder, dass ich überhaupt diese drei Flaschen gefunden habe.";
			link.l2.go = "OldSailor_16_1";
		break;

		case "OldSailor_16_1":
			dialog.text = "Stimmt. Viel Glück, mein Herr "+pchar.name+". Ich gehe weiter nach dieser gestreiften Nichtsnutzin suchen.";
			link.l1 = "Dir auch viel Glück, Matrose.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\\Animals\\Cat_01.wav");
		break;
		
		case "OldSailor_17":
			dialog.text = "Ach, das ist nett von Euch! Ihr seid gut mit der Mannschaft umgegangen, mein Herr "+pchar.name+". Hier ist ein kleines Geschenk – als Glücksbringer!";
			link.l1 = "Ein Stein mit einem Loch? Wie reizend.";
			link.l1.go = "OldSailor_18";
			GiveItem2Character(PChar, "talisman11");
			TakeItemFromCharacter(pchar, "potionrum");
		break;

		case "OldSailor_18":
			dialog.text = "Lacht nur, lacht nur. Aber ich sag's Euch: Auf See schaden Talismane nicht.";
			link.l1 = "Ihr seid ein abergläubisches Volk, ihr Seeleute. Viel Glück, Matrose.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_OldSailorKey");
			PlaySound("ambient\\Animals\\Cat_01.wav");
		break;

		case "OldSailor_again":
			dialog.text = "Habt Ihr die Antwort schon gefunden? Was ist die wichtigste Fähigkeit eines Kapitäns?";
			if (GetSummonSkillFromName(pchar, SKILL_Sailing) >= 6)
			{
				link.l1 = "Navigation. Davon hängt ab, wie groß das Schiff ist, das er führen kann.";
				link.l1.go = "OldSailor_10";
				notification("Prüfung bestanden", SKILL_Sailing);
			}
			else
			{
				link.l1 = "Noch nicht.";
				link.l1.go = "exit";
				NextDiag.TempNode = "OldSailor_again";
				notification("Unzureichende Fertigkeit (6)", SKILL_Sailing);
			}
		break;
		
		// <-- Диалог со старым матросом в трюме
		
		// --> Диалог с матросом, которому нужен ящик с ядрами (Поль)
		case "SailorNeedBox":
			dialog.text = "He, Junge!";
			link.l1 = "Du siehst meinem Vater nicht ähnlich. Und Gott sei Dank.";
			link.l1.go = "SailorNeedBox_1";
		break;

		case "SailorNeedBox_1":
			dialog.text = "Ha! Ich würde mich über einen so großen und edlen Sohn freuen. Nur das Salz der Erde kann so etwas wie mich hervorbringen.";
			link.l1 = "Na gut, Komplimente nehme ich an. Was ist passiert?";
			link.l1.go = "SailorNeedBox_2";
		break;

		case "SailorNeedBox_2":
			dialog.text = "Es fehlt einfach an menschlicher Hilfe, Junge. Ich soll die Kanonenkugeln an den Geschützen ordnen – falls in diesen gefährlichen Gewässern Ärger aufkommt. Ich habe die halbe Wache diese eisernen Biester aus dem Laderaum geschleppt, und beim letzten Kasten hat mein Rücken den Geist aufgegeben.";
			link.l1 = "Warum bittest du nicht einfach deine Kameraden? Ich dachte, ihr Seemänner helft einander.";
			link.l1.go = "SailorNeedBox_3";
		break;

		case "SailorNeedBox_3":
			dialog.text = "Eines mag unsere Bruderschaft wirklich nicht – schwere Lasten ohne Not schleppen. Dieses Los fiel heute auf mich – Kisten mit Kugeln aus dem Laderaum schleppen. Eine elende Arbeit, die eines Seemanns wie mir nicht würdig ist. Aber was soll man machen?";
			link.l1 = "Jammer nicht so. Ich helfe dir. Dann sehe ich mir mal den Laderaum an, mit dem man mich hier ständig erschreckt.";
			link.l1.go = "SailorNeedBox_4";
			if (IsCharacterPerkOn(pchar, "HT3"))
			{
				link.l2 = "(Athlet) Siehst du meinen Säbel am Gürtel? Der allein wiegt mehr als du. Ich hole deine Kugeln, kein Problem.";
				link.l2.go = "SailorNeedBox_4";
			}
			link.l3 = "Ich arbeite nicht mit den Händen, Matrose. Trag deine Kisten selbst.";
			link.l3.go = "SailorNeedBox_Net";
		break;

		case "SailorNeedBox_4":
			dialog.text = "Danke, Junge. Heb dich aber nicht auf!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBalls");
		break;
		
		case "SailorNeedBox_Net":
			DialogExit();
			
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;
		
		case "SailorNeedBox_PrinestiBalls": // ждёт ядра
			dialog.text = "Wie läuft’s, Junge?";
			if (CheckCharacterItem(PChar, "BoxOfBalls"))
			{
				link.l1 = "Hier, deine Kugeln. Ich dachte, sie wären größer.";
				link.l1.go = "SailorWantRum_PrinestiBalls_2";
			}
			if (PCharDublonsTotal() >= 30 && CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive") && !CheckAttribute(npchar, "SharlieTutorial_KaznacheyQuest_Poli"))
			{
				link.l2 = "Dein Name ist doch Paul, oder?";
				link.l2.go = "BallsGold_2";
			}
			link.l3 = "Mach’s gut.";
			link.l3.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
		break;

		case "BallsGold_2":
			dialog.text = "Ich bin immer froh, ihm helfen zu können! Wie viel soll ich diesmal bekommen?";
			if (PCharDublonsTotal() >= 20)
			{
				link.l1 = "20 Dublonen.";
				link.l1.go = "BallsGold_DatDeneg_gold20";
			}
			if (PCharDublonsTotal() >= 25)
			{
				link.l2 = "25 Dublonen.";
				link.l2.go = "BallsGold_DatDeneg_gold25";
			}
			if (PCharDublonsTotal() >= 30)
			{
				link.l3 = "30 Dublonen.";
				link.l3.go = "BallsGold_DatDeneg_gold30";
			}
			link.l4 = "Ich muss alles noch mal prüfen. Ich komme später zurück.";
			link.l4.go = "BallsGold_DatDeneg_3";
		break;

		case "BallsGold_DatDeneg_gold20":
			dialog.text = "Danke, Junge.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(20);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;
		
		case "BallsGold_DatDeneg_gold25":
			dialog.text = "Danke, Junge.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(25);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;
		
		case "BallsGold_DatDeneg_gold30":
			dialog.text = "Danke, Junge.";
			link.l1 = "...";
			link.l1.go = "BallsGold_DatDeneg_3";
			DelLandQuestMark(npchar);
			RemoveDublonsFromPCharTotal(30);
			pchar.questTemp.SharlieTutorial_KaznacheyQuest = sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) + 1;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.SharlieTutorial_KaznacheyQuest_Poli = true;
		break;
		
		case "BallsGold_DatDeneg_3":
			DialogExit();
			NextDiag.CurrentNode = "SailorNeedBox_PrinestiBalls";
		break;
		
		case "SailorWantRum_PrinestiBalls_2":
			dialog.text = "Na, viel größer geht’s nicht! Wenn so ein Geschenk gegen die Bordwand knallt – dann vielleicht Splitter, die jemanden treffen. Aber wenn’s das Heck trifft, hüpft das Ding wie ein Ball über das ganze Deck!";
			link.l1 = "Ein bekanntes Bild?";
			link.l1.go = "SailorWantRum_PrinestiBalls_3";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
		break;

		case "SailorWantRum_PrinestiBalls_3":
			dialog.text = "Ist schon passiert, Junge. Der Mensch erfindet gern tödliche Waffen. Nehmen wir Kartätschen – sie reichen nicht weit, durchschlagen keinen Rumpf, aber schicken ein Dutzend Leute locker ins Jenseits. Oder Kettenkugeln – treffen sie die Segel, zerfetzen sie alles! Und Bomben? Kein Kommentar – nie gesehen, Gott sei Dank! Teuflische Erfindung. Und teuer dazu.";
			link.l1 = "Von der Durchschlagskraft der Kugeln konnte ich mich schon überzeugen – an deinem armen Rücken.";
			link.l1.go = "SailorWantRum_PrinestiBalls_4";
		break;

		case "SailorWantRum_PrinestiBalls_4":
			dialog.text = "Das war wirklich nett von dir. Ich lasse mich auch nicht lumpen. Hier – eine Flasche erstklassiger Rum, fast voll, ha-ha!";
			link.l1 = "Wo hast du die her? Ich höre nur, dass der Rum an Bord viel zu früh ausgegangen ist. Mit so einer Ware hättest du jeden dazu gebracht, nicht nur eine, sondern alle Kisten aus dem Laderaum zu schleppen.";
			link.l1.go = "SailorWantRum_PrinestiBalls_5";
			GiveItem2Character(PChar, "potionrum");
		break;

		case "SailorWantRum_PrinestiBalls_5":
			dialog.text = "So ist es eben, Junge. Danke dir und mach’s gut.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "SailorNeedBox_PrinestiBalls";
			AddDialogExitQuestFunction("SharlieTutorial_SailorNeedBoxOfBallsFinal");
		break;
		
		// <-- Диалог с матросом, которому нужен ящик с ядрами
		
		// --> Диалог с офицером-торговцем, который торгует всяким
		case "OfficerTorgovets":
			dialog.text = "Ah, Monsieur "+pchar.lastname+". Wenn Ihr schlafen wolltet – Pech gehabt. Unser Kanonier hat Eure Koje belegt. Ihr wisst ja selbst, den weckt man nicht.";
			link.l1 = "Wenn es ihm passt – hört er plötzlich ganz hervorragend!";
			link.l1.go = "OfficerTorgovets_1";
		break;

		case "OfficerTorgovets_1":
			dialog.text = "Das ist noch gar nichts. Ich habe gehört, dass in Sharps Mannschaft sogar ein blinder Kanonier war. Der zielte angeblich nur nach dem Klang der Kanone.";
			link.l1 = "Heute seid Ihr erstaunlich gesprächig, Monsieur Bootsmann.";
			link.l1.go = "OfficerTorgovets_2";
		break;

		case "OfficerTorgovets_2":
			dialog.text = "Und das hat seinen Grund! Bald sind wir an Land, also ist es Zeit, die restliche Ware in klingende Pesos zu verwandeln. Im Bordell von Saint-Pierre sind sie immer willkommen, ha-ha!";
			link.l1 = "Erstaunlich, dass Ihr und nicht der Zahlmeister den Bordhandel übernehmt.";
			link.l1.go = "OfficerTorgovets_3";
		break;

		case "OfficerTorgovets_3":
			dialog.text = "Der kann nicht mit Leuten umgehen! Dafür gibt's auf dem Schiff einen Bootsmann – der kann mit Worten und Taten umgehen, ha-ha. Unser Zahlmeister hat auch ein Geschäft am Laufen – aber in so trübes Wasser steige ich nicht.";
			link.l1 = "Und was habt Ihr heute im Angebot?";
			link.l1.go = "OfficerTorgovets_4";
		break;

		case "OfficerTorgovets_4":
			if (!CheckAttribute(npchar, "SharlieTutorial_question_0"))
			{
				dialog.text = "Die letzte Flasche Rum auf dem Schiff, einige nützliche Amulette... und voilà! Eine vollständige Schatzkarte.";
				link.l1 = "Ihr solltet Händler sein, nicht Bootsmann! Zeigt mal her, was Ihr da habt.";
				npchar.SharlieTutorial_question_0 = true;
			}
			else
			{
				dialog.text = "Noch etwas?";
				link.l1 = "Zeigt mal her, was Ihr da habt.";
			}
			link.l1.go = "OfficerTorgovets_5";
			if (!CheckAttribute(npchar, "SharlieTutorial_question_1"))
			{
				link.l2 = "Amulette? So eins wie das, was Euch um den Hals baumelt?";
				link.l2.go = "OfficerTorgovets_6_question_1_1";
			}
			if (!CheckAttribute(npchar, "SharlieTutorial_question_2"))
			{
				link.l3 = "Verzeiht... Eine Schatzkarte?";
				link.l3.go = "OfficerTorgovets_6_question_2_1";
			}
			link.l4 = "Vielleicht ein andermal.";
			link.l4.go = "exit";
			NextDiag.TempNode = "OfficerTorgovets_4";
		break;
		
		case "OfficerTorgovets_5":
			DialogExit();
			NextDiag.CurrentNode = "OfficerTorgovets_4";
			sld = ItemsFromID("map_full");
			sld.price = 4000;
			LaunchItemsTrade(NPChar, 0);
		break;
		
		case "OfficerTorgovets_6_question_1_1":
			dialog.text = "Ah, ein scharfes Auge, Monsieur. Ja, der „Korallenkopf“ – ein nützliches Stück. Besonders für mich. Falls ich – Gott bewahre – mal ein Entern anführen muss, bringe ich mit dem Ding sofort Ordnung unter die Leute.";
			link.l1 = "Glaubt Ihr wirklich daran?";
			link.l1.go = "OfficerTorgovets_6_question_1_2";
		break;

		case "OfficerTorgovets_6_question_1_2":
			dialog.text = "Ich muss gar nicht glauben. So sind die Regeln der Karibik und unser Los als Seeleute. Amulette sind nützlich. Wenn Ihr länger bei uns bleibt, solltet Ihr ein paar Sets parat haben – für alle Fälle.";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_1 = true;
		break;

		case "OfficerTorgovets_6_question_2_1":
			dialog.text = "Oh ja. In der Karibik ist das nichts Ungewöhnliches. Manch einer hat Glück und macht den großen Fang. Dann gibt es zwei Wege: entweder er zahlt brav Steuern und lebt ruhig und lange – oder er versteckt das Gold in einer Höhle. Zurück bleiben ein Grab, ein Schatz... und ein Stück Papier.";
			link.l1 = "So einfach?";
			link.l1.go = "OfficerTorgovets_6_question_2_2";
		break;

		case "OfficerTorgovets_6_question_2_2":
			dialog.text = "Nicht ganz. Karten sind teuer, und sie locken andere Schatzjäger an – wie Euch. Und manchmal lohnt sich die Beute kaum. Selbst Albert Blackwood hat nicht sofort Erfolg gehabt. Macht die Schatzsuche zu Eurem Beruf – je mehr Ihr findet, desto größer die Belohnung. Und wenn Ihr noch ein Glücks-Amulett kauft – wird’s noch lustiger!";
			link.l1 = "...";
			link.l1.go = "OfficerTorgovets_4";
			npchar.SharlieTutorial_question_2 = true;
		break;
		
		// <-- Диалог с офицером-торговцем, который торгует всяким
		
		// --> Диалог с офицером-казначеем
		case "OfficerKaznachey":
			dialog.text = "Monsieur "+pchar.lastname+"! Einen Moment, bitte.";
			link.l1 = "Wollen Sie mir wieder eine Moralpredigt halten, Monsieur Pinchon? Ich habe Ihre wertvolle Tinte nicht angerührt!";
			link.l1.go = "OfficerKaznachey_2";
		break;

		case "OfficerKaznachey_2":
			dialog.text = "Womit schreiben Sie dann heimlich in Ihr Büchlein? Mit Weihwasser? In der Liste des Passagiergepäcks standen keine Tintenfässer. Aber im Moment haben Sie ernstere Probleme.";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_3";
		break;

		case "OfficerKaznachey_3":
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) sStr = "Und noch zweihundert für die beschädigte Spillwinde. Das Ankertaue ist gerissen.";
			dialog.text = "Zur Erinnerung: Sie schulden der Schiffskasse immer noch dreißig Pesos – wegen eines beschädigten Regenwasserfasses. Ihr komischer Versuch, Ihr Hemd zu waschen, hätte noch teurer werden können, wenn es damals nicht wieder geregnet hätte. "+sStr+"";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass"))
			{
				if (sti(pchar.Money) >= 230)
				{
					link.l1 = "Was mir gerade noch gefehlt hat – Schulden direkt bei der Ankunft. Bitte schön.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			else
			{
				if (sti(pchar.Money) >= 30)
				{
					link.l1 = "Was mir gerade noch gefehlt hat – Schulden direkt bei der Ankunft. Bitte schön.";
					link.l1.go = "OfficerKaznachey_4";
				}
			}
			link.l2 = "Und das soll alles sein? Das ist ja kein Kartenspielschulden, wirklich. Im Moment habe ich keine Zeit. Sie müssen bis zur Ankunft im Hafen warten.";
			link.l2.go = "OfficerKaznachey_3_1";
		break;

		case "OfficerKaznachey_3_1":
			dialog.text = "Schade. Dann gleich zur Sache – ich habe Arbeit für Sie.";
			link.l1 = "Sie kommen mit Menschen nicht gut zurecht, oder?";
			link.l1.go = "OfficerKaznachey_6";
		break;
		
		case "OfficerKaznachey_4":
			dialog.text = "Einen Moment, ich zähle nach.";
			link.l1 = "Vergesst nach dem Abendessen nicht, auch die Brotkrumen auf meinem Teller zu zählen.";
			link.l1.go = "OfficerKaznachey_5";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddMoneyToCharacter(pchar, -230);
			else AddMoneyToCharacter(pchar, -30);
		break;

		case "OfficerKaznachey_5":
			dialog.text = "Herzlichen Glückwunsch. Die Schiffskasse hat vorerst keine offenen Fragen mehr an Sie\nKommen wir gleich zur Sache – ich habe Arbeit für Sie.";
			link.l1 = "Mit Menschen kommen Sie nicht gut klar, oder?";
			link.l1.go = "OfficerKaznachey_6";
		break;

		case "OfficerKaznachey_6":
			dialog.text = "Mit Menschen – eher nicht. Aber ich kann gut rechnen\nUnd Sie, Monsieur "+pchar.lastname+", können Sie das auch?";
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				link.l1 = "(Buchhalter) Ich kenne mich mit Kontobüchern und Wechseln aus. Und ich weiß auch, was eine Null ist.";
				link.l1.go = "OfficerKaznachey_7";
			}
			else
			{
				link.l1 = "Genug, um das karge väterliche Stipendium bis zum Saisonende zu strecken.";
				link.l1.go = "OfficerKaznachey_8";
			}
		break;

		case "OfficerKaznachey_7":
			dialog.text = "Oh! Schade, dass Sie mir das nicht früher gesagt haben – diese Fahrt hätte viel spannender sein können.";
			link.l1 = "Sie haben etwas von Arbeit gesagt?";
			link.l1.go = "OfficerKaznachey_9";
		break;

		case "OfficerKaznachey_8":
			dialog.text = "Um Ihrer selbst willen – ich hoffe, Sie werden niemals Schiffseigner. Sie würden nicht nur sich selbst ruinieren, sondern auch alle an Bord.";
			link.l1 = "Sie haben etwas von Arbeit gesagt?";
			link.l1.go = "OfficerKaznachey_9";
		break;
		
		case "OfficerKaznachey_9":
			dialog.text = "Ja. Ich weiß nicht, ob Sie es wissen, aber Zahlmeister und Arzt sind direkt nach dem Kapitän die wichtigsten Personen an Bord\n"+
			"Ohne diese beiden zur See zu fahren, bedeutet, sein Geld zu riskieren – und ohne Geld ist ein Schiff nur ein teures Stück Holz\n"+
			"Ohne Zahlmeister kann sogar ein kleines Boot seinen Kapitän ruinieren. Und die erste Schlacht ohne Arzt kann die ganze Mannschaft kosten – was zu einem mühsamen und teuren Verfahren von Anwerbung und Ausbildung führt\n"+
			"Glücklicherweise für uns beide, vereine ich beide Rollen. Deshalb kann ich auch privaten Handel betreiben und kleine Dienste von der Crew nutzen\n"+
			"Natürlich werden diese Dienste großzügig entlohnt – und genau jetzt ist ein guter Moment dafür\n"+
			"Ich möchte, dass Sie diese Liste und diese Truhe mit Dublonen nehmen – und den Mannschaftsmitgliedern ihren Sold auszahlen\n"+
			"Streng nach Liste! Genau deshalb habe ich gefragt, ob Sie zählen können.";
			link.l1 = "Warum machen Sie das nicht selbst? Wenn die Leute auf ihr Geld warten, sollen sie doch selbst kommen.";
			link.l1.go = "OfficerKaznachey_10";
		break;

		case "OfficerKaznachey_10":
			dialog.text = "Ich habe gerade zu viel zu tun. Nur noch ein paar Tage bis zum Ende der Fahrt, und sehr bald wird hier eine Schlange von hundert Leuten stehen, die hartnäckig ihren Sold fordern.";
			link.l1 = "Sie haben Dublonen erwähnt...";
			link.l1.go = "OfficerKaznachey_11";
		break;

		case "OfficerKaznachey_11":
			dialog.text = "Spanische Goldmünzen. Harte Währung und wahrer Reichtum. Die seltensten, teuersten und nützlichsten Dienste – nur für sie\n"+
			"Sie werden in solchen Truhen aufbewahrt, der Bequemlichkeit halber.";
			link.l1 = "Und was bekomme ich dafür?";
			link.l1.go = "OfficerKaznachey_12";
		break;
		
		case "OfficerKaznachey_12":
			if (IsCharacterPerkOn(pchar, "HT2"))
			{
				dialog.text = "(Buchhalter) 150 Pesos und obendrauf 5 Dublonen – weil Sie fast mein Kollege sind. Und die Möglichkeit, Pesos zu einem fairen Kurs in Dublonen zu tauschen.";
			}
			else
			{
				dialog.text = "150 Pesos und die Möglichkeit, Pesos in Dublonen zu tauschen. Das ist nicht viel, aber die Arbeit ist einfach.";
			}
			link.l1 = "Einverstanden. Geben Sie mir die Liste und die Truhe.";
			link.l1.go = "OfficerKaznachey_11_agree";
			link.l2 = "Ich fürchte, das ist nicht die richtige Aufgabe für mich. Lebt wohl, Monsieur Pinchon.";
			link.l2.go = "OfficerKaznachey_11_otkaz";
		break;

		case "OfficerKaznachey_11_otkaz":
			dialog.text = "Wie Sie meinen. Dann lassen Sie mich jetzt bitte arbeiten, Monsieur "+pchar.lastname+".";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			DelLandQuestMark(npchar);
		break;

		case "OfficerKaznachey_11_agree":
			if(GetItemsWeight(pchar) + sti(Items[GetItemIndex("Chest")].weight) > GetMaxItemsWeight(pchar))
			{
				dialog.text = "Bitte sehr. Aber um Himmels willen – vergessen Sie nicht, die Dublonen aus der Truhe zu entnehmen, sich streng an die Liste zu halten, und nicht etwa etwas einzustecken. Ich erwarte die leere Truhe zurück\n"+
				"Überanstrengen Sie sich nicht, Monsieur. Und warum schleppen Sie eigentlich so viel Zeug mit sich herum? Ich empfehle, einen Teil in einer Truhe zu verstauen."; 
			}
			else
			{
				dialog.text = "Bitte sehr. Aber um Himmels willen – vergessen Sie nicht, die Dublonen aus der Truhe zu entnehmen, sich streng an die Liste zu halten, und nicht etwa etwas einzustecken. Ich erwarte die leere Truhe zurück.";
			}
			link.l1 = "Wie Sie wünschen. Bis bald, Monsieur Pinchon.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_QuestRazdatZoloto");
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_ActivateWindlass")) AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "1");
			else AddQuestRecordInfo("SharlieTutorial_ListOfSailors", "2");
			GiveItem2Character(PChar, "chest");
			SetFunctionExitFromLocationCondition("Tutorial_Logbook", pchar.location, false);
			Tutorial_Dubloons("");
			if (!isMultiObjectKnown("gold_dublon"))
			{
				SetAlchemyRecipeKnown("gold_dublon");
				SetAlchemyRecipeKnown("Chest");
			}
		break;
		
		case "OfficerKaznachey_12_Wait":
			dialog.text = "Na, wie läuft es? Haben Sie den Sold verteilt? Haben Sie alles zurückgebracht? Den Rest der Dublonen, die leere Truhe?";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuest") && sti(pchar.questTemp.SharlieTutorial_KaznacheyQuest) == 3 && CheckCharacterItem(PChar, "chest_open") && GetCharacterItem(pchar, "gold_dublon") >= 18)
			{
				link.l1 = "Alles erledigt.";
				link.l1.go = "OfficerKaznachey_13";
			}
			link.l2 = "Noch nicht, Monsieur Pinchon.";
			link.l2.go = "exit";
			NextDiag.TempNode = "OfficerKaznachey_12_Wait";
		break;

		case "OfficerKaznachey_13":
			dialog.text = "Dann wollen wir mal sehen...";
			link.l1 = "...";
			link.l1.go = "OfficerKaznachey_14";
		break;

		case "OfficerKaznachey_14":
			addGold = GetCharacterItem(pchar, "gold_dublon");
			if (addGold >= 18 && addGold <= 39)
			{
				dialog.text = "Und ich dachte, Sie könnten zählen. Hier fehlt etwas. Das bedeutet, meine Buchführung wird komplizierter, und Sie haben mir ein neues Problem beschert, anstatt das bestehende zu lösen\n"+
				"Das bedeutet, Monsieur "+pchar.lastname+", Sie erhalten keine Bezahlung.";
				link.l1 = "Tauschen Sie die Dublonen trotzdem um?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold >= 41)
			{
				dialog.text = "Und ich dachte, Sie könnten zählen. Hier ist zu viel. Das bedeutet, meine Buchführung wird komplizierter, und Sie haben mir ein neues Problem beschert, anstatt das bestehende zu lösen\n"+
				"Das bedeutet, Monsieur "+pchar.lastname+", Sie erhalten keine Bezahlung.";
				link.l1 = "Und was ist mit dem Tausch?";
				link.l1.go = "OfficerKaznachey_15_gold_115";
			}
			if (addGold == 40)
			{
				if (IsCharacterPerkOn(pchar, "HT2"))
				{
					dialog.text = "Alles korrekt. Es freut mich zu sehen, dass die Jugend mit Zahlen umgehen kann. Vielen Dank, Monsieur "+pchar.lastname+". Hier ist Ihr Lohn – und ein kleiner Bonus für einen fast-Kollegen.";
					link.l1 = "Und wie steht’s mit dem Tausch?";
					link.l1.go = "OfficerKaznachey_15_gold_100";
					AddItems(pchar, "gold_dublon", 5);
				}
				else
				{
					dialog.text = "Alles korrekt. Es freut mich zu sehen, dass junge Leute verantwortungsvoll mit Geld umgehen. Vielen Dank, Monsieur "+pchar.lastname+". Hier ist Ihr Lohn.";
					link.l1 = "Tauschen Sie die Dublonen immer noch?";
					link.l1.go = "OfficerKaznachey_15_gold_105";
				}
				AddMoneyToCharacter(pchar, 300);
				AddCharacterSkillPoints(pchar, "Commerce", 1);
			}
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "chest_open");
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", 100);
			pchar.questTemp.SharlieTutorial_KaznacheyQuestCompleted = true;
			DeleteAttribute(pchar, "questTemp.SharlieTutorial_KaznacheyQuestActive");
			npchar.Merchant.type = "SharlieTurorialK";
		break;
		
		case "OfficerKaznachey_15_gold_115":
			dialog.text = "Warum nicht. Einhundertfünfzehn Pesos pro Dublone. Kommen Sie jederzeit wieder, wenn Sie interessiert sind.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 115;
		break;

		case "OfficerKaznachey_15_gold_105":
			dialog.text = "Natürlich. Einhundertfünf Pesos pro Dublone. Kommen Sie jederzeit wieder, wenn Sie interessiert sind\n"+
			"Und ein Ratschlag: Sollte das Schicksal es wollen, dass Sie ein Schiff kommandieren – stellen Sie zuerst einen Zahlmeister ein. Selbst ein schwacher Spezialist spart Ihnen ein Vermögen.";
			link.l1 = "Danke, Monsieur Pinchon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 105;
		break;

		case "OfficerKaznachey_15_gold_100":
			dialog.text = "Natürlich! Einhundert Pesos pro Dublone – ein fairer Kurs. In den Karibikbanken würde man Ihnen mehr abknöpfen\n"+
			"Und ein Ratschlag: Sollte das Schicksal es wollen, dass Sie ein Schiff kommandieren – stellen Sie zuerst einen Zahlmeister ein. Selbst ein schwacher Spezialist spart Ihnen ein Vermögen.";
			link.l1 = "Danke, Monsieur Pinchon.";
			link.l1.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
			npchar.questTemp.GoldPrice = 100;
		break;
		
		case "OfficerKaznachey_16_Proval":
			dialog.text = "Lassen Sie es sich gutgehen, Monsieur "+pchar.lastname+"?";
			link.l2 = "Sind Sie auch in den Laderaum verbannt worden?";
			link.l2.go = "OfficerKaznachey_16_Proval_2";
		break;

		case "OfficerKaznachey_16_Proval_2":
			dialog.text = "Ich bin der Schiffsarzt, "+pchar.lastname+"! Bald wird der Aufenthaltsraum voller Verwundeter sein, und ich werde mehr Blut sehen als jeder Kämpfer. Und selbst wenn ich nur Zahlmeister wäre – im Gefecht würde ich mich wie alle anderen in die Reihe stellen. Nein, der Einzige, der es sich im gemütlichen Laderaum bequem gemacht hat – das sind Sie.";
			link.l2 = "Was machen Sie dann hier?";
			link.l2.go = "OfficerKaznachey_16_Proval_3";
		break;

		case "OfficerKaznachey_16_Proval_3":
			addGold = GetCharacterItem(pchar, "gold_dublon");
			dialog.text = "Die Schlacht beginnt erst in ein paar Stunden, also ist jetzt der richtige Moment, um die Tagesabrechnung zu machen. Sie haben meine Truhe mit Dublonen, "+pchar.lastname+". Bitte geben Sie sie zurück.";
			link.l2 = "...";
			link.l2.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumLoad_4");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			RemoveDublonsFromPCharTotal(addGold);
			AddItems(npchar, "gold_dublon", addGold);
			TakeItemFromCharacter(pchar, "chest");
			TakeItemFromCharacter(pchar, "chest_open");
		break;

		case "TreasurerTrade":
			dialog.text = "Interessieren Sie sich für Dublonen, Monsieur "+pchar.lastname+"?";
			link.l1 = "Lassen Sie uns handeln.";
			link.l1.go = "TreasurerTrade_1";
			link.l2 = "Noch nicht.";
			link.l2.go = "exit";
			NextDiag.TempNode = "TreasurerTrade";
		break;
		
		case "TreasurerTrade_1":
			DialogExit();
			LaunchItemsTrade(NPChar, 0);
			NextDiag.CurrentNode = "TreasurerTrade";
		break;
		
		// <-- Диалог с офицером-казначеем
		
		// --> Матрос сообщает о приближающихся кораблях
		case "Sailor_Trevoga":
			dialog.text = "Käpt’n, Alarm! Piraten am Horizont!";
			link.l1 = "...";
			link.l1.go = "Sailor_Trevoga_2";
			SetCameraDialogMode(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("SharlieTutorial_Captain"));
			PlaySound("Ship\rynda_alarm.wav");
		break;

		case "Sailor_Trevoga_2":
			StartInstantDialog("SharlieTutorial_Captain", "Sailor_Trevoga_3", "Quest\Sharlie\Tutorial.c");
		break;

		case "Sailor_Trevoga_3":
			dialog.text = "Alonso, begleite Monsieur "+pchar.lastname+" höflich in den Laderaum. Und sieh nach, dass Monsieur Dreussac sich herablässt aufzuwachen und die Geschützmannschaften für den Kampf vorbereitet.";
			link.l1 = "Kapitän, ich bin bereit zu kämpfen! Ein Edelmann kann nicht...";
			link.l1.go = "Sailor_Trevoga_4_fencing";
			link.l2 = "Wenn ich irgendwie helfen kann...";
			link.l2.go = "Sailor_Trevoga_4_leadership";
			link.l3 = "Heißt das etwa, es gibt keinen Burgunder?..";
			link.l3.go = "Sailor_Trevoga_4_fortune";
		break;

		case "Sailor_Trevoga_4_fencing":
			dialog.text = "Alonso, bring ihn weg. An die Arbeit, Faulenzer! Segel setzen!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Pistol", 1);
		break;

		case "Sailor_Trevoga_4_leadership":
			dialog.text = "Alonso, bring ihn weg. An die Arbeit, Faulenzer! Segel setzen!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;

		case "Sailor_Trevoga_4_fortune":
			dialog.text = "Alonso, bring ihn weg. An die Arbeit, Faulenzer! Segel setzen!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_Trevoga_7");
			AddCharacterSkillPoints(pchar, "Fortune", 1);
		break;
		
		// <-- Матрос сообщает о приближающихся кораблях
		
		// --> Диалог с пиратом в трюме
		case "EnemyPirate_1":
			dialog.text = "Verdammt! Was für hartnäckige Teufel!";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_2";
			//PlaySound("VOICE\\Russian\\OliverTrast01.wav");
			//PlaySound("VOICE\\Spanish\\OliverTrast01.wav"); //вставить для испанской версии
			PlaySound("interface\\abordage.wav");
			PlaySound("interface\\abordage.wav");
		break;

		case "EnemyPirate_2":
			dialog.text = "Und was machst du hier?! Hast deine Leute im Stich gelassen und versteckst dich vor dem Kampf, du Rattenfänger?! Ich werde dir die Eingeweide rausreißen!";
			link.l1 = "Du hättest besser nicht meinen Laderaum betreten. Jetzt bin ich es, der dir die Eingeweide rausreißt.";
			link.l1.go = "EnemyPirate_3_Fencing";
			link.l2 = "Du kannst dich kaum auf den Beinen halten, und das meiste Blut an dir ist nicht einmal deins.";
			link.l2.go = "EnemyPirate_3_Leadership";
			if (IsCharacterPerkOn(pchar, "HT1"))
			{
				link.l3 = "(Duellant) Das habe ich so vermisst.";
				link.l3.go = "EnemyPirate_3_Duelyant";
			}
		break;

		case "EnemyPirate_3_Fencing":
			dialog.text = "He-he. Dann versuch's mal, Bürschchen.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;

		case "EnemyPirate_3_Leadership":
			dialog.text = "He-he. Dann habe ich wohl nichts mehr zu verlieren.";
			link.l1 = "...";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "Leadership", 1);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "EnemyPirate_3_Duelyant":
			dialog.text = "Was redest du da?!";
			link.l1 = "Zwei Monate. Zwei Monate musste ich mein Schwert in der Scheide lassen. Tanzen wir!";
			link.l1.go = "EnemyPirate_4";
			AddCharacterSkillPoints(pchar, "FencingL", 1);
			AddCharacterSkillPoints(pchar, "FencingS", 1);
			AddCharacterSkillPoints(pchar, "FencingH", 1);
			AddCharacterSkillPoints(pchar, "Leadership", 1);
		break;
		
		case "EnemyPirate_4":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_2");
		break;
		
		// <-- Диалог с пиратом в трюме
		
		// --> Диалог с выжившим матросом
		case "SailorAlive_1":
			dialog.text = "Na, wenigstens lebt Ihr... Ich bin erledigt. Haben mich ordentlich am Ruder erwischt...";
			link.l1 = "Was ist passiert?!";
			link.l1.go = "SailorAlive_2";
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_2":
			dialog.text = "Ein Entern war das. Arrrgh! Diese verfluchten Kerle!\nHört gut zu: Das Geschützdeck haben wir gehalten, aber oben geht der Spaß erst richtig los. Ich schwöre, die kommen gleich wieder runter. Nehmt die Kartätsche! Zum Teufel, vorsichtig! Die ist geladen!";
			if (IsCharacterPerkOn(pchar, "HT4"))
			{
				link.l1 = "(Scharfschütze) Macht Euch keine Sorgen. Wer es wagt, bekommt sofort Löcher verpasst.";
			}
			else link.l1 = "...";
			link.l1.go = "SailorAlive_3";
		break;

		case "SailorAlive_3":
			dialog.text = "Da ist Kartätsche drin. Wenn Ihr es richtig anstellt — erwischt Ihr zwei oder drei auf einmal\nIch glaube an Euch, "+pchar.name+". Wenn Ihr Euch verteidigt habt, durchsucht die Leichen. Vielleicht findet Ihr einen Trank für mich... sonst bin ich Euch keine Hilfe.";
			link.l1 = "Halte durch, Alonso. Und da sind unsere Gäste!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_5");
			GiveItem2Character(PChar, "pistol3");
			EquipCharacterByItem(PChar, "pistol3");
			AddItems(pchar, "grapeshot", 5);
			AddItems(pchar, "GunPowder", 5);
			LAi_GunSetChargeQuant(pchar, GUN_ITEM_TYPE, 1);
		break;

		case "SailorAlive_11":
			dialog.text = "Gut... Gut gemacht, "+pchar.name+". Habt Ihr etwas für mich gefunden?";
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				link.l1 = "Ich denke, das ist es. Sieht zwar verdächtig aus, aber na gut.";
				link.l1.go = "SailorAlive_12";
			}
			link.l2 = "Ich suche noch!";
			link.l2.go = "exit";
			NextDiag.TempNode = "SailorAlive_11";
		break;
		
		case "SailorAlive_12":
			dialog.text = "Und er schmeckt gar nicht schlecht, ha-ha! Danke, "+pchar.name+". Und die drei habt Ihr schön erledigt. Wenn Ihr wirklich ein so ehrenhafter Edelmann seid, übernehmt das Kommando. Zu zweit halten wir das Deck sicher, und wenn die Jungs oben auch durchhalten – dann gehört der Tag uns!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_7");
			TakeItemFromCharacter(pchar, "quest_potion");
			PlaySound("Ambient\Tavern\glotok_001.wav");
			DelLandQuestMark(npchar);
		break;

		case "SailorAlive_13":
			if (CheckAttribute(npchar, "fighter"))
			{
				dialog.text = "So ist es besser. Habt Ihr die Kartätsche geladen?";
				link.l1 = "Bin gerade dabei... Aber warum ist es plötzlich so still?";
				link.l1.go = "SailorAlive_14";
				SetMusic("");
			}
			else
			{
				dialog.text = "Wenn Ihr wirklich ein so ehrenhafter Edelmann seid, übernehmt das Kommando.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "SailorAlive_13";
			}
		break;

		case "SailorAlive_14":
			dialog.text = "Das ist für die dramatische Wirkung. Jetzt geht’s los.";
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("SharlieTutorial_TrumBitva_8");
		break;
		
		// <-- Диалог с выжившим матросом
		
		// --> Диалог с Алонсо после боя
		case "AfterBattle_Alonso_1":
			dialog.text = "Und wieder enden wir dort, wo wir angefangen haben. Danke, dass Ihr mir das Leben gerettet habt, "+pchar.name+".";
			if (CheckAttribute(pchar, "questTemp.SharlieTutorial_Ranen"))
			{
				link.l1 = "Ich denke, wir sind quitt. Ich erinnere mich nicht mal daran, wie du mich da rausgeholt hast.";
			}
			else
			{
				link.l1 = "Ich denke, wir sind quitt. Wenn nicht du und die Jungs gewesen wärt, hätte ich das nicht überlebt.";
			}
			link.l1.go = "AfterBattle_Alonso_2";
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "tutorial_4", "", -1);
			CharacterTurnByLoc(pchar, "quest", "quest6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "tutorial_5", "", -1);
			CharacterTurnByLoc(npchar, "quest", "quest7");
		break;

		case "AfterBattle_Alonso_2":
			dialog.text = "Ihr hättet im Laderaum bleiben können, wie es Euch befohlen wurde. Schade, dass der Kapitän nicht mehr lebt, um Euch dafür die Leviten zu lesen.";
			link.l1 = "Wir mussten ihn unter einem ganzen Berg von Leichen hervorholen. Wie viele Halunken hat er erledigt?";
			link.l1.go = "AfterBattle_Alonso_3";
		break;

		case "AfterBattle_Alonso_3":
			dialog.text = "Manche sagen, er hat drei erwischt. Andere behaupten, es waren mindestens ein Dutzend. Ich denke, nur der Teufel hat genau mitgezählt.";
			link.l1 = "Du hast mir immer noch nicht erklärt, wie es so weit kommen konnte.";
			link.l1.go = "AfterBattle_Alonso_4";
		break;

		case "AfterBattle_Alonso_4":
			dialog.text = "Was gibt es da zu erzählen? Unsere Sechzehnpfünder konnten uns nicht vor einer einzigen Piratenbrigg retten. Das ist eben ein echtes Kriegsschiff\n"+
		"Es war blitzschnell heran, und während wir uns noch drehten, feuerte es Kartätschen und ging sofort zum Entern über. Ihr hättet sehen sollen, was auf dem Deck los war – es gab nichts mehr, was der Arzt noch retten konnte\n"+
		"Das Schlimmste an einem Kampf mit Piraten ist – man hat nichts davon. Nur Lumpenpack. Nicht einmal ihre Brigg konnten wir behalten.";
			link.l1 = "Und was passiert jetzt?";
			link.l1.go = "AfterBattle_Alonso_5";
		break;
		
		case "AfterBattle_Alonso_5":
			dialog.text = "Das Schiff ist noch schwimmfähig, und wir haben genug Männer gerettet, um Euch planmäßig nach Saint-Pierre zu bringen. Dort werde ich mir einen neuen Kapitän suchen, und Ihr werdet Euren Bruder treffen und ihm von Euren Abenteuern berichten. Was danach passiert – das weiß nur Gott.\n"+
		"Eines weiß ich aber sicher – Ihr werdet Euch bei uns einleben. Nicht schlecht für eine Landratte, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "AfterBattle_Alonso_6";
		break;

		case "AfterBattle_Alonso_6":
			dialog.text = "Ha! Jetzt wird Euch gleich übel. Keine Scheu. Das ist nur die Angst, die aus Euch herauskommt. Willkommen in der Karibik!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("SharlieTutorial_SeaNearMartinique");
		break;
		
		
		// <-- Диалог с Алонсо после боя
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}