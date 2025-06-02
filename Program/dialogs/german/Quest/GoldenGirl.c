// диалоги персонажей по квесту Дороже золота
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
			dialog.text = "Was willst du?";
			link.l1 = "Ich sollte gehen...";
			link.l1.go = "exit";
		break;
		
		// вестовой в Сен Пьере
		case "fraofficer":
			dialog.text = "Kapitän Charles de Maure! Endlich! Seine Exzellenz Jacques Dille do Parkuet verlangt Sie zu sehen! Dies ist dringend!";
			link.l1 = "Warum bin ich nicht überrascht? Sehr gut, bitte sagen Sie Seiner Exzellenz, dass ich bald komme.";
			link.l1.go = "fraofficer_1";
		break;
		
		case "fraofficer_1":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", 10.0);
			LocatorReloadEnterDisable("FortFrance_town", "reload1_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "reload2_back", true);
			LocatorReloadEnterDisable("FortFrance_town", "gate_back", true);//закрыть выходы из города
			LAi_LocationDisableOfficersGen("FortFrance_townhall", true);//офицеров не пускать
			pchar.questTemp.GoldenGirl = "message";
			AddQuestRecord("GoldenGirl", "1");
		break;
		
		// маркиза Джулиана Бото
		case "Julianna":
			dialog.text = "Meine Augen müssen mich täuschen, wenn es Charles de Maure selbst ist! Ich mache solche Empfänge nicht sehr oft und ich bin erfreut, dass Sie etwas Zeit für mein bescheidenes Kloster erübrigen konnten. Glücklicher ich! Das verdient einen Toast!";
			link.l1 = "Meine Grüße, gnädige Frau. Verzeihen Sie mir eine mögliche Enttäuschung meiner Manieren - es ist eine sehr lange Zeit vergangen, seit ich das letzte Mal an solchen... Veranstaltungen teilgenommen habe. Die Etikette auf einem Schiff beschränkt sich auf Unterordnung, saubere Halstücher und eine regelmäßige Tasse erfrischenden Kaffees jeden Morgen.";
			link.l1.go = "Julianna_1";
		break;
		
		case "Julianna_1":
			dialog.text = "So charmant, Kapitän, Sie haben immer noch Ihren Pariser Glanz bei sich. Ich kann seinen schüchternen Blick unter dieser erfahrenen und gesalzenen Maske sehen. Machen Sie sich keine Sorgen, ich freue mich so sehr, Sie endlich zu treffen, dass ich Ihnen vieles vergeben kann. Für jetzt. Wir werden sehen, wie es in der Zukunft mit uns läuft. Wein? Rot oder weiß?";
			link.l1 = "Ein perfekter Moment für einen Rumwitz, aber leider bin ich nicht in Stimmung, es tut mir leid. Ich trinke gerne alles, was deine hübschen Hände mir einschenken.";
			link.l1.go = "Julianna_2";
		break;
		
		case "Julianna_2":
			dialog.text = "Feine Sache. Aber ich bestehe darauf. Die Vorliebe für Wein kann viel über einen Mann verraten und ich beabsichtige, heute Abend alles über dich zu erfahren. Also frage ich noch einmal: rot oder weiß?";
			link.l1 = "Haben Sie es auf Ihre Weise. Ich sehe, dass Sie Rotwein trinken. Gleiches gilt für mich - ich möchte auch etwas über Sie lernen.";
			link.l1.go = "Julianna_3";
			link.l2 = "In diesem Fall nehme ich weiß, aber du entscheidest. Das sollte in beide Richtungen funktionieren, findest du nicht?";
			link.l2.go = "Julianna_4";
		break;
		
		case "Julianna_3":
			pchar.questTemp.GoldenGirl.Vine = "red";
			dialog.text = "Prächtig, also bin ich jetzt dran? Das hier ist ein Burgunder Pinot Noir, Winzer nennen ihn 'ein freches Mädchen'. Es ist keine einfache Sorte und sein Nachgeschmack kann auch ziemlich täuschend sein. Zufrieden?";
			link.l1 = "Pinot Noir, hm? Passt zu mir. Unzuverlässig und geheimnisvoll, ein düsterer Geschmack zuerst, aber lass ihn eine Weile atmen und du wirst überrascht sein. Ein leichter Tanz von Schattierungen und Geschmäckern, die Wahl eines erfahrenen Kenners. Der erste Eindruck täuscht, nicht wahr? Ich trinke auf Ihre Augen, Madame!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_4":
			pchar.questTemp.GoldenGirl.Vine = "white";
			dialog.text = "Herrlich, also bin ich jetzt dran? Ich habe einen wunderbaren Sauvignon Blanc, direkt aus dem Loiretal. Ziemlich wild, man kann fast spüren, wie er auf der Zunge knallt. Und als i-Tüpfelchen - eine Note von Schießpulver. Ich nehme an, du teilst etwas Gemeinsames.";
			link.l1 = "Ich hätte Besseres erwartet, vielleicht so etwas wie Riesling. Nun, lasst uns diesen einfachen Tölpel trinken, der nach Sommer und Schießpulver riecht. Hast du schon gehört, dass manche Leute es für Katzenpipi halten? Ich werde auf dein Lächeln trinken, so hell wie diese Saphire!";
			link.l1.go = "Julianna_5";
		break;
		
		case "Julianna_5":
			dialog.text = "Bemerkenswert, Charles! Darf ich dich so nennen? Ich lag nicht falsch bei dir, an einem anderen Tag würdest du der Star meiner Nacht sein. Aber ach, mein Kapitän, heute hast du starke Konkurrenz. Es scheint, dass wir am Rande eines Skandals stehen, siehst du das?";
			link.l1 = "Ich höre wütende Stimmen. Wer ist dieser unangenehme Monsieur und was hat er getan, um unseren liebsten Gouverneur zu verärgern?";
			link.l1.go = "Julianna_6";
		break;
		
		case "Julianna_6":
			dialog.text = "Dieser 'unangenehme' Monsieur ist Angerran de Chievous, ein unanerkannter Bastard des Grafen de Levi Vantadur. Sie amüsieren sich über ihr Streitthema. De Chievous versucht seit Jahren, meine Gunst zu gewinnen, und er ist mir hierher gefolgt, in der Hoffnung, dass er seinen Vater bei mir ersetzen kann. Obwohl er kein rechtmäßiger Sohn ist, ist er reich und mächtig. Sturheit ist eine weitere seiner Eigenschaften, für manche Menschen ersetzt sie Weisheit. Kurz vor Ihrer Ankunft begann er mit Jacques über das offensichtliche Thema zu streiten. Seine Exzellenz beschützt mich immer auf sehr rührende Weise, das sollten Sie sehen! Los, lass uns zusehen und sehen, wie es diesmal endet.";
			link.l1 = "Ich rieche Ärger in der Luft... Warum gibt es immer einen Haken, selbst in so einer wunderbaren Nacht...";
			link.l1.go = "Julianna_7";
		break;
		
		case "Julianna_7":
			dialog.text = "Entschuldigen Sie, Charles?";
			link.l1 = "Vergiss es. Bitte stelle mich deinem aufdringlichen Freund vor, dann werden wir sehen...";
			link.l1.go = "Julianna_8";
		break;
		
		case "Julianna_8":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest1", "GoldenGirl_PartyTalk", -1);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Julianna_9":
			dialog.text = "Herr, erlauben Sie mir, Ihnen meinen lieben Gast vorzustellen - Kapitän Charles de Maure, in Fleisch und Blut, hat uns mit seinem Besuch geehrt! So berühmte Persönlichkeiten sind hier nicht oft zu Gast.";
			link.l1 = "...";
			link.l1.go = "Julianna_10";
		break;
		
		case "Julianna_10":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "Julianna_11":
			dialog.text = "Charles, mir gefällt nicht, wohin das führt! Jacques ist taub für meine Argumente, während Angerran sicherlich etwas im Schilde führt. Dieser Kampf hatte einen Zweck und ich brauche deine Hilfe!";
			link.l1 = "Ich fürchte, ich verstehe Sie nicht... Was kann ich hier möglicherweise tun? Er hat sich bereits geweigert, mit mir zu duellieren...";
			link.l1.go = "Julianna_12";
		break;
		
		case "Julianna_12":
			dialog.text = "Kapitän, bitte enttäuschen Sie mich nicht. Noch vor einem Moment waren Sie ein Virtuose der Gespräche und jetzt teilt sich Ihre Welt zwischen Dingen, die Sie mit einem Schwert stechen können und Dingen, die Sie nicht können. Denken Sie doch mal aus der Box heraus! Lassen Sie uns Angerrans Spiel verderben. Er will den armen Jacques alleine herausfordern, aber das ist einfach langweilig! Lassen Sie uns ein Turnier veranstalten! Mehrere Herren hier können ernsthafte Einsätze unterstützen und Ihr Glück ist bereits als legendär bekannt! Vielleicht werden die Karten es heute Abend begünstigen?";
			link.l1 = "Ich sehe nicht ganz, wie das verhindern wird, dass de Chievous gegen unseren lieben Gouverneur kämpft, aber ich bin dabei, gnädige Frau. Alles, um dieses kleine Lächeln von ihm zu verwerfen.";
			link.l1.go = "Julianna_13";
		break;
		
		case "Julianna_13":
			dialog.text = "Hervorragend, jetzt geh zum Tisch und iss etwas, es wird eine lange Nacht. Sobald du bereit bist, triff mich im Saal, wir werden mehr Platz dafür brauchen. In der Zwischenzeit werde ich eine Show abziehen, andere überreden, mir Spektakel und Spiele mit hohen Einsätzen zu geben. Ich könnte sogar anfangen, sie anzuschreien, um diese Hähne darauf aufmerksam zu machen, dass eine Dame vor Langeweile ertrinkt. Bitte misch dich nicht ein, niemand darf wissen, dass wir heute Abend im selben Team sind. Bis später, mein Kapitän!";
			link.l1 = "Was immer Sie sagen, Madame, was immer Sie sagen...";
			link.l1.go = "Julianna_14";
		break;
		
		case "Julianna_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "barmen", "stay", "GoldenGirl_JulianaPause", -1);
			AddQuestRecord("GoldenGirl", "4");
		break;
		
		case "Julianna_15":
			dialog.text = "Nun, gratuliere mir, es hat funktioniert! Ein bisschen Stolz, einige Vorurteile und voila! Mach ein gelangweiltes Gesicht, sie beobachten uns. Lass sie denken, du bist am Trinken interessiert, nicht an mir\nEin Turnier steht kurz bevor, die Einsätze sind hoch, keine zweiten Chancen und Neuansetzungen. Irgendwie weiß ich, dass du daran gewöhnt bist. Du wirst das schaffen. Denk daran, Angerran plant definitiv etwas, er wird einen Zug gegen unseren Freund Jacques machen, aber er hat deine Ankunft nicht berücksichtigt. Sei mein Ass im Ärmel, denn sein selbstgefälliges Grinsen ist nie ein gutes Zeichen. Wir haben acht Spieler, aber ich habe dafür gesorgt, dass du ihm erst im Finale gegenüberstehen wirst\nOh! Dein erster Gegner! Oberst und unser Forts Kommandant. Meer gegen Land - eine würdige Herausforderung für Gäste mit militärischer Erfahrung! Applaus!";
			link.l1 = "";
			link.l1.go = "Julianna_16";
		break;
		
		case "Julianna_16":
			DialogExit();
			DoQuestCheckDelay("GoldenGirl_CreateColonel", 0.5);
		break;
		
		case "Julianna_17":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "Du hast großartige Arbeit geleistet, Charles, einfach herrlich. Angerran und Jacques werden sich in einem Moment gegenüberstehen. Schade, dass sie nicht zugehört haben und das Turnier um eine Woche verschoben haben. Ich könnte wirklich eine herausragende Party organisieren, über die bis nach Paris geredet würde! Nun, vielleicht beim nächsten Mal. Es scheint, dass dein nächster Gegner ein würdiger Konkurrent zu deinem Glück ist, ein wahrer Seewolf, Kapitän Moreno! Kapitäne, bitte!";
				link.l1 = "";
			}
			else
			{
				dialog.text = "Ach, Ihr Glück hat Euch im Stich gelassen, Kapitän. Es tut mir leid, aber das Spiel ist für Euch vorbei. Angerran spielt bereits gegen Jacques, also sollte ich gehen. Lebewohl.";
				link.l1 = "Es war mir ein Vergnügen... meine Dame.";
			}
			link.l1.go = "Julianna_18";
		break;
		
		case "Julianna_18":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) GoldenGirl_CreateCaptainMoreno();
			else GoldenGirl_CardsFail();
		break;
		
		case "Julianna_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win")) 
			{
				dialog.text = "Ich gratuliere Ihnen zu Ihrem wohlverdienten Sieg, Kapitän! Es ist noch unklar, wer Ihnen im Finale gegenüberstehen wird... Lassen Sie uns ein wenig zur Seite treten. Senken Sie Ihre Stimme und beobachten Sie diesen Tisch. Schauen Sie, da geht er hin! Ich beginne zu verstehen, was Angerran vorhat! Er hat den süßen Jacques schon um sein Geld gebracht, aber er lässt ihn nicht vom Tisch weg. Als ich vorbeiging, hatte der arme Kerl auf einige Dokumente über ein ganzes Schiff mit Ladung gewettet. Leider ist ihm das Glück heute Nacht nicht hold. Oder jemand hat es ihm nicht erlaubt.";
				link.l1 = "Denkst du, de Chievous betrügt?";
				link.l1.go = "Julianna_21";
			}
			else
			{
				dialog.text = "Ach, dein Glück hat dich verlassen, Kapitän. Es tut mir leid, aber das Spiel ist für dich vorbei. Angerran spielt bereits gegen Jacques, also sollte ich gehen. Lebewohl.";
				link.l1 = "Es war mir ein Vergnügen... Madame.";
				link.l1.go = "Julianna_20";
			}
		break;
		
		case "Julianna_20":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Julianna_21":
			dialog.text = "Er könnte definitiv, wenn er wollte, aber ich habe keinen Beweis. Unser lieber Gouverneur ist gut mit Karten, aber auch sein Gegner. Angerran hat nicht einmal geblinzelt, als er auf seine Fregatte gewettet hat, stell dir das vor. Hätten wir dieses Duell in Paris oder in Lyon, es würde zur Legende werden, Charles! Trotzdem, er könnte heute Abend einfach nur Glück haben. Lass uns näher kommen und es selbst sehen.";
			link.l1 = "...";
			link.l1.go = "Julianna_22";
		break;
		
		case "Julianna_22":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "quest", "quest3", "GoldenGirl_Talking", -1); 
			LAi_ActorFollow(npchar, pchar, "", 10.0);
		break;
		
		case "Julianna_23":
			dialog.text = "Charles, halt mich fest oder ich werde fallen... Oder nicht - diese Idioten würden nicht einmal bemerken, wenn ich ohnmächtig werde. Hast du das gesehen? Jacques, verdammt noch mal, du Dummkopf! Wie ein Kind, Jesus! Ein idiotisches Kind!";
			link.l1 = "Marquise, ich glaube, ich verstehe Sie nicht. Was passiert jetzt an diesem Tisch? Worüber wetten sie?";
			link.l1.go = "Julianna_24";
		break;
		
		case "Julianna_24":
			dialog.text = "Auf mich, Charles. Unser süßer, dummer Jacques hat auf mich gewettet. Angerran hat seine einzige Schwachstelle gefunden und im richtigen Moment getroffen.";
			link.l1 = "Verdammt! Aber ich bin der Nächste im Turnier, ich könnte sein verfluchtes Schiff zurückgewinnen! Warum?";
			link.l1.go = "Julianna_25";
		break;
		
		case "Julianna_25":
			dialog.text = "Weil Angerran einen großen Gedanken darin gelegt und alles durchdacht hat. Hör mir zu, wir haben nicht viel Zeit. Du musst ihm dasselbe antun. Nimm ihm alles weg, nimm all sein Geld, all seine Schiffe, provoziere ihn! Bring ihn dazu, seinen Kopf wegen Ruf, Ehre, Leidenschaft, wegen allem zu verlieren! Du hast gesehen, wie es heute Abend gemacht wurde. Ecke ihn ein und zwinge ihn zu setzen\nIch flehe dich an, Charles! Ich bin bereit für alles, aber ich gehe nicht zu ihm. Nicht so! Selbst Graf Vantadur wird sich nicht gegen einen ehrlichen Kartengewinn stellen, er wird nicht mal seinen Finger rühren, um mir zu helfen. Siehst du, Karten sind verdammt heilig für noble Leute, verdammt sie! Du bist meine letzte und einzige Hoffnung, Charles!";
			link.l1 = "Lassen Sie unseren Gouverneur noch nicht begraben, gnädige Frau. Vielleicht gewinnt er sein Schiff zurück? Lady Luck ist eine launische... Frau.";
			link.l1.go = "Julianna_26";
		break;
		
		case "Julianna_26":
			dialog.text = "Sie verstehen es immer noch nicht, oder? Glück hat an diesem Tisch keinen Platz! Angerran de Chievous hat das Sagen. Er hat einen Weg gefunden, mich zu besitzen und gleichzeitig seinen Vater fernzuhalten. Ich habe keine Ahnung, wie lange er das schon geplant hat, aber er hat fast gewonnen. Er kontrolliert das Spiel und wir haben nur eine Chance, es zu durchbrechen. Hier, nehmen Sie das! Ich werde einen Scheinangriff machen, das gibt uns ein oder zwei Minuten. Nutzen Sie sie weise.";
			link.l1 = "Markgräfin... Jemand, bitte helft! Die Dame fühlt sich nicht gut! Schnell!";
			link.l1.go = "Julianna_27";
		break;
		
		case "Julianna_27":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			GiveItem2Character(pchar, "obereg_5");
			GiveItem2Character(pchar, "totem_13");
			Log_Info("You have received amulet 'Turtle'");
			Log_Info("You have received amulet 'Joker'");
			PlaySound("interface\important_item.wav");
		break;
		
		case "Julianna_28":
			dialog.text = "Nein, nein, mir geht es gut... Es ist ein wenig stickig hier... Es tut mir so leid, meine Herren. Ich werde euch einen Augenblick für etwas frische Luft verlassen. Ihr könnt ohne mich fortfahren.";
			link.l1 = "...";
			link.l1.go = "Julianna_29";
		break;
		
		case "Julianna_29":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto1", "", 10.0); // уходит
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromId("FortFrance_Mayor");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
		break;
		
		case "Julianna_30":
			dialog.text = "Nicht in diesem Moment und nicht in St. Pierre, aber ich kenne jemanden. Ich verspreche dir, Angerran, das wird ein würdiges Gemälde sein...";
			link.l1 = "...";
			link.l1.go = "Julianna_31";
		break;
		
		case "Julianna_31":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_32":
			dialog.text = "Angerran, du bist unmöglich! Lerne, wie man verliert! Das ist nur ein Spiel und du kannst nicht alles vorhersagen. Trink deinen Wein aus und zieh dich an - die Regeln bleiben - ein Besiegter verlässt unsere gemütliche Party.";
			link.l1 = "Marquise, warte...";
			link.l1.go = "Julianna_33";
		break;
		
		case "Julianna_33":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_24";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_34":
			dialog.text = "Das geht zu weit, meine Herren! Hört sofort auf! Wir sind alle sehr müde nach der anstrengenden Nacht und ich fürchte, ich muss meine Gäste bitten, sich zu verabschieden. Ihr könnt euren Streit morgen fortsetzen, wie es sich für Ehrenmänner gehört, es sei denn, ihr ändert eure Meinung. Aber niemand berührt hier Waffen, ist das klar?";
			link.l1 = "...";
			link.l1.go = "Julianna_35";
		break;
		
		case "Julianna_35":
			DialogExit();
			sld = characterFromId("Angerran");
			sld.dialog.currentnode = "Angerran_27";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Julianna_36":
			dialog.text = "Charles, ich fürchte, ich muss dich auch bitten zu gehen. Geh nach oben und nimm dir ein Zimmer. Ich werde alles arrangieren. Ich bin dir für alles, was du für mich getan hast, über alle Maßen dankbar, aber ich brauche etwas Zeit für mich und du musst schrecklich müde sein.";
			link.l1 = "Es ist nicht zu schlimm, gnädige Frau, aber ich würde nicht Nein zu einem Bett sagen. Diese lässige Party hat mich härter getroffen als eine massive feindliche Marinegeschwader. Ich verstehe, dass das alles auch für Sie nicht einfach war, Marquise. Ruhen Sie sich aus und machen Sie sich keine Sorgen, Sie schulden mir nichts. Alles, was ich jetzt brauche, ist ein Schlaf.";
			link.l1.go = "Julianna_37";
		break;
		
		case "Julianna_37":
			dialog.text = "Ich werde dafür sorgen, dass sie dich bis Mittag wecken. Es ist bereits Morgendämmerung, also kann ich dir keine gute Nacht mehr wünschen. Schlaf gut.";
			link.l1 = "Sie auch, Marquise.";
			link.l1.go = "Julianna_38";
		break;
		
		case "Julianna_38":
			DialogExit();
			GoldenGirl_SleepInBrothel();
		break;
		
		case "Julianna_39":
			dialog.text = "Da bist du ja, Charles. Um ehrlich zu sein, ich habe überhaupt nicht geschlafen, aber du siehst gut ausgeruht aus. Wie hast du geschlafen? Das Frühstück ist unterwegs.";
			link.l1 = "Ihre Gastfreundschaft ist legendär, Madame, aber ich fürchte, ich habe keine Zeit, sie zu genießen. Seine Exzellenz, de Chievous' Sekunden, Schiffe, die ich gewonnen habe - all das wartet auf mich.";
			link.l1.go = "Julianna_40";
		break;
		
		case "Julianna_40":
			dialog.text = "Du hast nicht nur die Schiffe gewonnen. Es gibt noch etwas, das ich dich fragen wollte, Charles...";
			link.l1 = "Ich bin weder Jacques noch Angerran, Marquise. Ich spiele nicht um Frauen, um ihre Gunst zu gewinnen. Du schuldest mir nichts.";
			link.l1.go = "Julianna_41";
			link.l2 = "Sie stehen unter meinem Schutz, Marquise. Weder Jacques noch Angerran werden Ihnen jemals Ärger bereiten, das kann ich Ihnen versprechen.";
			link.l2.go = "Julianna_42";
		break;
		
		case "Julianna_41":
			pchar.questTemp.GoldenGirl.J1 = "true";
			dialog.text = "Du bist entweder fabelhaft ehrenhaft oder verliebt, Charles. Und nicht in mich. Aber noch einmal, ich bin dir von ganzem Herzen ewig dankbar. Wenn ich dir irgendwie helfen kann - sag es mir einfach.";
			link.l1 = "Julianne, die Zeit rennt und ich stehe vor der unbehaglichsten Aufgabe. De Chievous ist ein Abschaum und selbst ein ehrliches Duell kann schnell enden wie das, was wir gestern Nacht beobachtet haben. Lass uns später reden, wenn all dies endgültig erledigt ist. Ich danke dir für die Möglichkeit, in Ruhe zu schlafen und freue mich darauf, dich wiederzusehen.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_42":
			pchar.questTemp.GoldenGirl.J2 = "true";
			dialog.text = "Ich bin dir von ganzem Herzen dankbar, Charles... Glaub mir, deine Beute zu sein ist auch für mich eine Art Sieg. Sollten wir dieses Gespräch in einer eher... privaten Umgebung fortsetzen?";
			link.l1 = "Julianne, die Zeit läuft und ich stehe vor der unangenehmsten Aufgabe. De Chievous ist ein Abschaum und selbst ein ehrliches Duell kann schnell enden wie das, was wir letzte Nacht beobachtet haben. Lass uns später reden, wenn all das für immer erledigt ist. Ich danke dir für die Möglichkeit, in Ruhe zu schlafen und freue mich darauf, dich wiederzusehen.";
			link.l1.go = "Julianna_43";
		break;
		
		case "Julianna_43":
			dialog.text = "Ich werde Sie dann nicht länger aufhalten, mein Kapitän. Denken Sie jedoch daran, Angerran ist gefährlich. Ich kann seine Kampffähigkeiten nicht beurteilen, aber er hat an mehreren Kriegen teilgenommen und in Rocroi gekämpft. Ich habe auch von ein paar Duellen gehört, die er gewonnen hat, meistens mit Pistolen. Vor allem ist er ein hinterhältiger Typ, wie Sie selbst bemerkt haben. Ich bitte Sie, vorsichtig zu sein und mich bitte danach zu sehen!";
			link.l1 = "Aufmerksamkeit steht Ihnen erstaunlich gut, Marquise. Glauben Sie mir, de Chievous ist nicht der erste Bastard, der mir im Weg steht. Ich werde zurechtkommen. Jetzt sollte ich wirklich zu Seiner Exzellenz gehen und das Duellgeschäft besprechen.";
			link.l1.go = "Julianna_44";
		break;
		
		case "Julianna_44":
			dialog.text = "Gott segne dich, mein Kapitän! Und sag Jacques, er soll sich so weit wie möglich von den Türen meines Hauses fernhalten.";
			link.l1 = "Sie haben mein Wort. Auf Wiedersehen, Marquise!";
			link.l1.go = "Julianna_45";
		break;
		
		case "Julianna_45":
			DialogExit();
			GoldenGirl_ToGovernor();
		break;
		
		case "Julianna_46":
			dialog.text = "Kapitän, Sie haben es geschafft, was für eine Erleichterung! Wie ist es gelaufen? Bluten Sie?!";
			link.l1 = "Es ist nicht mein Blut... zumindest nicht alles. Marquise, wo ist de Chievous?";
			link.l1.go = "Julianna_47";
		break;
		
		case "Julianna_47":
			dialog.text = "Ich wollte dich genau dasselbe fragen - hast du ihn nicht erledigt? Was ist passiert? Warum sehe ich die Hälfte der Stadtwache draußen?";
			link.l1 = "Ich habe dem Gouverneur gesagt, dass du vielleicht in Gefahr bist. De Chievous wurde verletzt und ist weggerannt, hat seine Schläger auf uns losgelassen. Es war ein Massaker. Obwohl, Geschichten wie diese sind nichts für deine schönen Ohren. Es ist vorbei. Du bist frei von ihm und von unserem 'süßen' Jacques.";
			link.l1.go = "Julianna_48";
		break;
		
		case "Julianna_48":
			dialog.text = "Das ist so schlimm, Charles. Feinde wie Angerran de Chievous sollten für immer getötet werden, wenn sich die Gelegenheit bietet. Ich kannte den Mann viele Jahre - er ist nicht der vergebende Typ. Früher oder später wird er einen Weg zur Rache finden. Aber ich mag es nicht, wie du hängst, wurde deine Wunde versorgt?";
			link.l1 = "Nur ein Kratzer, es war schon viel schlimmer. Es tut ein bisschen weh, das ist alles. Danke, dass Sie sich um mich kümmern, Madame, aber ich sollte gehen...";
			link.l1.go = "Julianna_49";
		break;
		
		case "Julianna_49":
			dialog.text = "Kapitän, Sie haben um mich gewettet, Ihre Schiffe und Ihren Reichtum riskiert, Sie haben für mich in einem Geschäft gekämpft, Ihr Leben und Ihre Karriere riskiert. Das Mindeste, was ich für Sie tun könnte, ist, mich um Ihre Wunden zu kümmern und Ihnen einen sicheren Ort zum Ausruhen zu bieten. Nein! Ich will nichts mehr davon hören. Nehmen Sie meine Hand und folgen Sie mir nach oben. Ihr Zimmer wartet auf Sie.";
			link.l1 = "Ich nehme Ihr Angebot an, Madame, danke. Aber ich möchte Sie nicht belasten. Ich schaffe es alleine nach oben.";
			link.l1.go = "Julianna_50";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.J2") && pchar.questTemp.GoldenGirl.Vine == "red")
			{
				link.l2 = "Marquise, Sie sind mein Schutzengel. Ich fürchte, jetzt bin ich es, der Ihnen etwas schuldet.";
				link.l2.go = "Julianna_52";
			}
		break;
		
		case "Julianna_50":
			dialog.text = "Charles, du bist ein Beispiel für Ritterlichkeit! Ich schwöre bei Gott, wenn du so weitermachst, verliere ich meinen Kopf! Also gut, mein Ritter, ich werde Denise zu dir schicken, sie wird sich um deine Wunden kümmern, wie es sich für einen ordentlichen Arzt gehört.";
			link.l1 = "Danke, Marquise. Wenn mein Herz nicht schon besetzt wäre, würde ich gerne mitspielen. Aber ach! Gute Nacht!";
			link.l1.go = "Julianna_51";
		break;
		
		case "Julianna_51":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_WithoutJulianna"); // найти нужные локаторы
		break;
		
		case "Julianna_52":
			dialog.text = "In diesem Fall verlange ich, dass Sie mich sofort verwöhnen. Halten Sie meine Hand und tun Sie, was ich sage. Denise! Bring Flusen, heißen Wein und etwas zu essen nach oben! Los geht's, mein Kapitän. Und denken Sie daran - dieses Mal kein Streit!";
			link.l1 = "Wie Sie sagen, Marquise, gehöre ich ganz Ihnen.";
			link.l1.go = "Julianna_53";
		break;
		
		case "Julianna_53":
			DialogExit();
			pchar.questTemp.GoldenGirl.JulianaSex = "true";
			DoQuestReloadToLocation("FortFrance_Brothel_room", "goto", "goto1", "GoldenGirl_KissJulianna");
			sld = characterFromId("Julianna");
			ChangeCharacterAddressGroup(sld, "FortFrance_Brothel_room", "goto", "goto2");
		break;
		
		case "Julianna_54":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Guten Morgen, Charles. Wie geht es deinen 'Kratzern'?";
				link.l1 = "Dank deiner Bemühungen fühle ich mich wiedergeboren. Bitte akzeptiere meine aufrichtige Dankbarkeit, Julianna.";
				link.l1.go = "Julianna_56";
			}
			else
			{
				dialog.text = "Guten Morgen, mein Held. Wie geht es deinen 'Kratzern'?";
				link.l1 = "Danke für Ihre Besorgnis, Madame, mir geht es völlig gut. Ich würde ein Vermögen zahlen, um Ihre Denise als Schiffsärztin zu haben. Sie ist ein Wunder!";
				link.l1.go = "Julianna_55";
			}
		break;
		
		case "Julianna_55":
			dialog.text = "Ich fürchte, es wird nicht einfach zu arrangieren sein. Aber ich würde es nie wagen, Sie ohne triftigen Grund zu wecken. Glauben Sie mir, ich habe Ihren Schlaf furchtlos bewacht, aber dieser Mann unten besteht darauf. Er sagt, er ist einer Ihrer Crew und es ist dringend.";
			link.l1 = "Meine Crew? Sie haben das Richtige getan, indem Sie mich geweckt haben, Marquise! Ich werde sofort aufbrechen.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_56":
			dialog.text = "In einem anderen Umstand würde ich, mein Kapitän, aber wir müssen verschieben. Ein äußerst ungebildeter Monsieur unten erwartet Sie. Er sagt, er sei einer Ihrer Crew und dies sei dringend.";
			link.l1 = "Wir werden darauf zurückkommen, Madame, wenn ich zurück bin. Ich hoffe, es geht nicht schon wieder um die Spanier, die Belagerung halten.";
			link.l1.go = "Julianna_57";
		break;
		
		case "Julianna_57":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_town", "reload", "reload9_back", "GoldenGirl_BadNews");
		break;
		
		case "Julianna_58":
			dialog.text = "Charles, du bist zurück! Welche Neuigkeiten hat dein Mann gebracht? Du hast dich nicht einmal verabschiedet!";
			link.l1 = "Es tut mir leid, Marquise. De Chievous hat wieder schmutzige Spielchen gespielt. Er hat mein Schiff gestohlen und ist diese Nacht in See gestochen. Eine meiner vertrauensvollen Offiziere war auf diesem Schiff und ich kann sie nicht in den Händen dieses Bastards lassen.";
			link.l1.go = "Julianna_59";
		break;
		
		case "Julianna_59":
			dialog.text = "Sie? Sie haben eine weibliche Offizierin auf Ihrem Schiff stationiert? Das widerspricht allem, was ich über Seemannschaft weiß. Was lässt Sie denken, dass sie noch lebt?";
			link.l1 = "Ich hoffe. Julianna, Hoffnung ist alles, was ich bisher habe. Ich muss mehr über Angerran de Chievous erfahren. Ich muss unbedingt herausfinden, wohin er gegangen ist! Ich muss sie zurückbringen!";
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) link.l1.go = "Julianna_62";
			else link.l1.go = "Julianna_60";
		break;
		
		case "Julianna_60":
			dialog.text = "Nun sehe ich! Du bist tatsächlich verliebt, mein Ritter! Ich würde ohne zu zögern die Hälfte meines Lebens für solche Loyalität und Zuneigung geben!";
			link.l1 = "Ich habe keine Gelübde abgelegt, aber diese Frau bedeutet mir sehr viel, Marquise.";
			link.l1.go = "Julianna_61";
		break;
		
		case "Julianna_61":
			dialog.text = "Diese Eifersucht berührt mich. Hör mal, Charles, ich bin bereit, eifersüchtig auf dich zu werden! Aber welche Kurtisane kann der Stimme der wahren Liebe widerstehen? Außerdem hast du mich gerettet, mein Ritter, natürlich werde ich dir helfen. Frage nur.";
			link.l1 = "Danke. Sie kennen de Chievous schon eine Weile. Wo könnte er nach all dem Trubel hingehen, um den Zorn seines Vaters abzuwarten?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_62":
			dialog.text = "Was wäre, wenn ich dich mit einem Brunch verführen könnte? Du hast zwei Tage nicht an dieses... Mädchen gedacht, vielleicht kann sie noch einen Tag warten?";
			link.l1 = "Marquise, ich verstehe, wie ich in Ihren Augen aussehen mag, aber was getan ist, ist getan. Obwohl ich keine Gelübde abgelegt habe, gehört mein Herz ihr. Ich bitte Sie, mich zu verstehen und mir zu helfen.";
			link.l1.go = "Julianna_63";
		break;
		
		case "Julianna_63":
			dialog.text = "Komm schon, Charles! Du verteidigst dich mit einer Liebesrede vor einer Kurtisane? Ich habe schon lange nicht mehr so gelacht! Du bist so unglaublich! Entspann dich, was in diesem Haus passiert, bleibt in diesem Haus. Ich erinnere mich, was ich dir schulde. Frag einfach.";
			link.l1 = "Danke. Sie kennen de Chievous schon seit einiger Zeit. Wo könnte er nach all dem Trubel hingehen, um den Zorn seines Vaters zu überstehen?";
			link.l1.go = "Julianna_64";
		break;
		
		case "Julianna_64":
			dialog.text = "Ehrlich gesagt, auch wenn es vielleicht nicht das Angenehmste ist, Angerran de Chievous einzuladen, ist es politisch sehr nützlich. Er ist überall ein willkommener Gast, auch in mit Frankreich verbündeten Nationen. Aber ich kenne nur einen Mann in der Nähe, der ihm immer eine Hand und ein Heiligtum bieten wird. Francois de Lyon, der Gouverneur unserer Kolonie Guadeloupe. Er ist ein alter Vertrauter des Grafen de Levi Vantadur und hatte schon immer eine Schwäche für diesen Bastard.";
			link.l1 = "Guadeloupe ist es! Es ist die beste Führung, auf die ich zu hoffen wagte! Wenn wir heute Abend in See stechen, werden wir nur einen Tag hinter ihnen sein.";
			link.l1.go = "Julianna_65";
		break;
		
		case "Julianna_65":
			dialog.text = "Warte, Charles, es gibt noch etwas. Ich habe kürzlich einen Brief für dich erhalten. Ich nahm an, es hätte etwas mit dem Duell zu tun, aber ich bin mir nicht mehr sicher. Hier ist er.";
			link.l1 = "Kein Siegel, aber das Papier ist teuer. Das gefällt mir nicht...";
			link.l1.go = "Julianna_66";
		break;
		
		case "Julianna_66":
			DialogExit();
			AddQuestRecordInfo("GG_Letter_1", "1");
			chrDisableReloadToLocation = true;
			npchar.dialog.currentnode = "Julianna_67";
			LAi_SetStayType(npchar);
		break;
		
		case "Julianna_67":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Komm schon, Charles! Halte mich nicht in der Schwebe, ist es von ihm?";
			link.l1 = "Ja, es ist von ihm. Sie lebt! Er hat sie gefangen genommen, während er mein Schiff gestohlen hat. Nun schlägt er vor, dass wir uns treffen und das in einer zivilisierten Umgebung besprechen. Genau wie du gesagt hast, Guadeloupe, Basse-Terre.";
			link.l1.go = "Julianna_68";
		break;
		
		case "Julianna_68":
			dialog.text = "Monseniour de Lyons wird definitiv den Sohn von Leve Vantadur über dich wählen. De Chievous könnte wieder eine Falle für dich aufstellen! Du hast einen sehr mächtigen Feind gemacht, indem du mich verteidigt hast, Charles. Ich wünschte, ich könnte dir helfen, aber ich fürchte, alles, was ich tun kann, ist dich zu bitten, vorsichtig zu sein.";
			link.l1 = "Julianne, ich hätte es in der Neuen Welt nie geschafft, wenn ich immer den direkten Weg gewählt hätte. Schmutzige Geschäfte sind nicht meine Stärke, aber ich weiß, wie man mitspielt.";
			link.l1.go = "Julianna_69";
		break;
		
		case "Julianna_69":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			chrDisableReloadToLocation = false;
			GoldenGirl_ToBaster();
		break;
		
		case "Julianna_70":
			dialog.text = "Gibt es Neuigkeiten, Kapitän?";
			link.l1 = "Ach, nichts...";
			link.l1.go = "Julianna_71";
		break;
		
		case "Julianna_71":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
		break;
		
		case "Julianna_72":
			dialog.text = "Willkommen zurück, Charles! Ich bin froh, dass du lebendig und munter bist. Was gibt's Neues?";
			link.l1 = "Alles, was wir über die Fähigkeiten von de Chievous wussten, stellte sich als eine gravierende Untertreibung heraus. Der Bastard hält meinen... Offizier gefangen, und ich habe nur zwei Wochen, um das Lösegeld zu sammeln. Ich fürchte, dass es ohne deine Hilfe nicht passieren kann.";
			link.l1.go = "Julianna_73";
		break;
		
		case "Julianna_73":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, deine Liebe ist eine echte Windblume, und doch schulde ich dir viel und werde dir so gut ich kann helfen. Wie kann ich dir behilflich sein?";
			}
			else
			{
				dialog.text = "Charles, ich habe bereits gesagt, dass ich nie vergessen werde, was du für mich getan hast. Ich werde tun, was ich kann, um dir zu danken. Ich bin bereit, aber ich verstehe nicht ganz, wie ich dir dabei von Nutzen sein kann?";
			}
			link.l1 = "Bitte setz dich, Julianna. Siehst du, Angerrans Lösegeld... bist du. Und ich meine nicht eine offizielle Patenschaft, ich meine wie eine gefesselte Gefangene in seinem Laderaum.";
			link.l1.go = "Julianna_74";
		break;
		
		case "Julianna_74":
			dialog.text = "Ich bin sprachlos... Aber dein Gesicht sagt mir, dass das kein Scherz ist. Hat er den Verstand verloren?";
			link.l1 = "Mehr so, er glaubt, dass ich es getan habe. Er ist verzweifelt genug, um alle möglichen Grenzen zu überschreiten.";
			link.l1.go = "Julianna_75";
		break;
		
		case "Julianna_75":
			dialog.text = "Und was, du fragst mich? Nicht zu schreien während meiner Entführung? Kapitän, glaubst du nicht, dass das ein bisschen zu viel verlangt ist? Ich schulde dir viel, aber das Leben eines anderen zu retten, indem ich mein eigenes Leben in die Hände eines ruhmlosen Bastards gebe... Du bist der Ritterlichkeit hier, während ich eine äußerst realistische und materialistische Frau bin.";
			link.l1 = "Ich fürchte, Madame, genau das verlange ich von Ihnen. Packen Sie Ihre Sachen, wir gehen. Es tut mir zutiefst leid, aber die Zeit drängt.";
			link.l1.go = "Julianna_76";
			link.l2 = "Marquise, ich entführe keine Frauen, die mir vertrauen. Und das könnte unsere Chance sein.";
			link.l2.go = "Julianna_81";
		break;
		
		case "Julianna_76":
			dialog.text = "Du bist voller Überraschungen, Charles. Hast du das gehört? Das war all die Gnade, die ich für dich hatte, sie ist gerade zerbrochen. Liebe oder nicht, ich werde es nicht zulassen, dass du mich entführst. Wachen! Hilfe!!! Jemand!!!!";
			link.l1 = "Und ich dachte, wir wären Freunde.";
			link.l1.go = "Julianna_77";
		break;
		
		case "Julianna_77":
			DialogExit();
			LAi_SetActorType(npchar);
			GoldenGirl_PatrolInBrothel();
		break;
		
		case "Julianna_78":
			dialog.text = "Das ist ein Skandal! Was hast du aus meiner Lounge gemacht?! Was für ein dämonisches Grauen ist das? Charles, komm zur Besinnung! Du bist ein Edelmann, kein verfluchter Pirat!!";
			link.l1 = "Ich habe mich bereits bei dir entschuldigt. Ich bat dich, die Dinge nicht weiter zu komplizieren - du hast nicht zugehört. Glaube mir, ich mag nicht, was ich tue, aber ich habe keine Wahl. Ich werde alles tun, um der Frau willen.";
			link.l1.go = "Julianna_79";
		break;
		
		case "Julianna_79":
			dialog.text = "Welche Dame würde sich für einen solchen Chevalier wie dich entscheiden? Ich gehe selbst, halt deine Hände von mir fern! Du stiehlst keine Kuh, also zeige etwas Würde!";
			link.l1 = "Gut. Komm mit mir, Madame. Bleib hinter meinem Rücken und halt den Kopf unten - vielleicht fangen sie an zu schießen.";
			link.l1.go = "Julianna_80";
		break;
		
		case "Julianna_80":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.greeting = "Marquesa_again";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.quest.goldengirl_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_alarm.win_condition.l1.location = "FortFrance_Town";
			pchar.quest.goldengirl_alarm.function = "GoldenGirl_AlarmSP";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1 = "location";
			pchar.quest.goldengirl_dominica_alarm.win_condition.l1.location = "Dominica";
			pchar.quest.goldengirl_dominica_alarm.function = "GoldenGirl_DominicaAlarm";
			ChangeCharacterComplexReputation(pchar, "nobility", -15);
			ChangeCharacterNationReputation(pchar, FRANCE, -50);
			ChangeOfficersLoyality("bad_all", 5);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "14");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			pchar.questTemp.GoldenGirl = "dominica_alarm"; // флаг - силовое решение
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
		break;
		
		case "Julianna_81":
			dialog.text = "Einen Moment lang dachte ich, dass ich dich überhaupt nicht kenne, Charles. Dieser Blick... Aber was hast du dann vor? Welche Chance hast du erwähnt?";
			link.l1 = "Warum benutzt der Schurke mich, um an dich heranzukommen? Warum hat er dieses Kartenspiel inszeniert, anstatt einfach zu nehmen, was er wollte? Wovor hat er Angst?";
			link.l1.go = "Julianna_82";
		break;
		
		case "Julianna_82":
			dialog.text = "Nichts. Leider sind die Gründe dafür primitiv. Graf Henri hat immer noch eine Schwäche für mich. Angerran würde viel riskieren, wenn er gegen meinen Willen etwas mit mir machen würde. Es tut mir leid Charles, aber das ist eine Sackgasse. Er wird alles abstreiten und davonkommen. Niemand wird den Worten von dir, dem Entführer, glauben, während sein Vater dich zerstören wird.";
			link.l1 = "Verdammt! Ich wünschte, es wäre nicht dazu gekommen... Mach dich bereit, Marquise, wir müssen gehen. Und ja, ich bitte dich, still zu sein.";
			link.l1.go = "Julianna_76";
			link.l2 = "Aber der Bastard muss neben seinem Vater noch andere Schwächen haben, oder? Er ist nicht perfekt, ganz im Gegenteil, er ist das Gegenteil von perfekt!";
			link.l2.go = "Julianna_83";
		break;
		
		case "Julianna_83":
			dialog.text = "Ich weiß nicht, ob das für... uns nützlich sein wird. Angerran hatte einige Geschäfte mit dem örtlichen Piratenbaron. Jacques Baraban?";
			link.l1 = "Es ist Barbazon, Madame. Nettes Paar, beide! Aber Jacques der Gütige hat keine Liebe für mich und ich kann keinen Angriff auf Le Francois starten, ohne eine feste Gewissheit.";
			link.l1.go = "Julianna_84";
		break;
		
		case "Julianna_84":
			if (CheckAttribute(pchar, "questTemp.Portugal.GG1"))
			{
				dialog.text = "Du bist wieder zu direkt, mein Ritter. Erinnerst du dich an Kapitän Moreno? Dein zweiter Glücksspielgegner? Ich wette, er kam hierher wegen Angerran. Er muss etwas wissen, was für uns von Wert ist.";
				link.l1 = "Kapitän Moreno, hah! Ja, natürlich. Ist er immer noch hier in der Stadt? Wo kann ich ihn finden?";
				link.l1.go = "Julianna_85";
			}
			else
			{
				dialog.text = "Du bist mal wieder zu direkt, mein Ritter. Jemand weiß immer etwas und nicht jeder kann in bestimmten Situationen den Mund halten. Meine... Schüler hören Dinge, in diesem Haus. Gib mir einen Tag und ich werde mehr erfahren oder ich finde dir jemanden, der es wird.";
				link.l1 = "Marquise, ich dachte, dass Ihnen Sorge steht, aber Sie in Zorn steht Ihnen noch mehr. Danke, Sie wecken Hoffnung in mir!";
				link.l1.go = "Julianna_86";
			}
		break;
		
		case "Julianna_85":
			pchar.questTemp.GoldenGirl.Portugal = "true";
			dialog.text = "Ja, er ist noch hier und ich werde dir das Herumlaufen ersparen, um ihn zu suchen. Komm morgen Abend hierher - Kapitän Moreno wird hier, in diesem Raum, auf dich warten. Ich wünschte, ich könnte mehr tun, aber ich kann nicht, Charles.";
			link.l1 = "Es ist schon mehr als genug, Marquise. Mit ihm an meiner Seite werden die Dinge viel einfacher sein. Danke. Wir sehen uns morgen Abend.";
			link.l1.go = "Julianna_87";
		break;
		
		
		case "Julianna_86":
			pchar.questTemp.GoldenGirl.Portugal = "false";
			dialog.text = "Ich wünschte, ich hätte das von dir in einer anderen Situation gehört, Charles. Komm morgen Abend zu mir. Ich hoffe, ich bekomme, was du brauchst.";
			link.l1 = "Danke nochmals, Julianna! Dann also morgen Abend.";
			link.l1.go = "Julianna_87";
		break;
		
		case "Julianna_87":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_70";
			LAi_SetOwnerType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			SetFunctionTimerCondition("GoldenGirl_JuliannaOneDay", 0, 0, 1, false); // таймер
		break;
		
		case "Julianna_88":
			pchar.quest.GoldenGirl_JuliannaOneDayFail.over = "yes"; //снять прерывание
			if (pchar.questTemp.GoldenGirl.Portugal == "true")
			{
				dialog.text = "Hier bist du, mein Freund! Kapitän Moreno wartet bereits auf dich.";
				link.l1 = "...";
				link.l1.go = "Julianna_89";
			}
			else
			{
				dialog.text = "Charles, ich glaube, ich habe etwas gefunden. Erinnerst du dich an Kapitän Moreno? Derjenige, der in jener unglücklichen Nacht gegen dich gespielt hat?";
				link.l1 = "Ich tue es, was für ein Vagabund. Was ist mit ihm?";
				link.l1.go = "Julianna_102";
			}
		break;
		
		case "Julianna_89":
			DialogExit();
			LAi_SetActorType(npchar);
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chrDisableReloadToLocation = true;
		break;
		
		case "Julianna_90":
			dialog.text = "Ich habe das immer gewusst, Bartolomeo de la Cueva. Deswegen bist du überhaupt auf meine Party gekommen. Es war wie Jalapenos zum Abendessen hinzuzufügen. Ich weiß, dass du und deine Jungs schon ein paar Wochen auf dieser Insel herumschnüffelt. Ich weiß, dass dies irgendwie mit dem Piratenbaron von Le Francois und Angerran de Chievous verbunden sein muss. Erzähl meinem Freund alles darüber und wir werden im Gegenzug deinen legendären Namen geheim halten. Ansonsten rufe ich die Wachen, die bereits hinter den Türen stehen. Ich habe sie bei deiner Ankunft gerufen.";
			link.l1 = "...";
			link.l1.go = "Julianna_91";
		break;
		
		case "Julianna_91":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_92":
			dialog.text = "Nicht nur sie! Angerran hat mir eine Halskette geschenkt, eine wunderschöne! Große und saubere Perlen einschließlich dieser einen, dunkel wie südliche Nacht, in der Mitte. Aber er hat es bei den örtlichen Juwelieren bestellt!";
			link.l1 = "...";
			link.l1.go = "Julianna_93";
		break;
		
		case "Julianna_93":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_18";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_94":
			dialog.text = "Ich wette, er hat es nicht nur getan, um mir mit einem Luxusgeschenk zu gefallen. Obwohl, dieses Geschenk war seine letzte Möglichkeit, meine Gunst im Rahmen der Anständigkeit zu gewinnen. Angerran hat keine Titel und Land, sogar seine Fregatte bleibt nur seine, bis sein Vater anders entscheidet. Er nutzt Macht und Einfluss, hat aber keine eigene Einkommensquelle. Vielleicht hat er es satt, auf die Spenden seines Vaters zu warten und hat beschlossen, seinen finanziellen Zustand zu regeln?";
			link.l1 = "Warte, Frau! Das Kartenspiel! Wenn wir recht haben und de Chievous das Ganze im Voraus geplant hat, dann hätte er viel Geld für Einsätze gebraucht, um unseren Gouverneur in die Enge zu treiben. Einen Elternteil um solches Geld zu bitten, könnte seine unerwünschte Aufmerksamkeit auf die Sache lenken. Schon gestohlene Schätze von Freibeutern zu stehlen, scheint ein ruhiger und sicherer Weg zu sein, das benötigte Geld zu beschaffen. Niemand würde es wissen!";
			link.l1.go = "Julianna_95";
		break;
		
		case "Julianna_95":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_21";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_96":
			dialog.text = "Auf uns, Charles! Angerran darf diesmal nicht ungeschoren davonkommen. Seine Position über mir ist zu weit gegangen und ich möchte dir dabei helfen, das zu sehen.";
			link.l1 = "";
			link.l1.go = "Julianna_97";
		break;
		
		case "Julianna_97":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_23";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_98":
			dialog.text = "Ein Verlierer-Pirat und eine fast verliebte Kurtisane. Charles, du hast ein Traumteam für dich selbst!";
			link.l1 = "Dennoch, danke, euch beiden. Aufrichtig! Jetzt muss ich das ein bisschen durchdenken und einen Plan ausarbeiten.";
			link.l1.go = "Julianna_99";
		break;
		
		case "Julianna_99":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_25";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_100":
			dialog.text = "Dieses Haus hat alles, was seine Gäste wünschen. Ich werde die Vorbereitungen treffen. Kommen Sie, wenn Sie bereit sind, Charles.";
			link.l1 = "Sehr gut, Madame.";
			link.l1.go = "Julianna_101";
		break;
		
		case "Julianna_101":
			DialogExit(); // фин 3
			AddQuestRecord("GoldenGirl", "22");
			npchar.Dialog.currentnode = "Julianna_119";
			LAi_SetOwnerType(npchar);
		break;
		
		case "Julianna_102":
			dialog.text = "Nichts, aber jemand in der Stadt sucht ihn. Sie erkundigen sich aktiv nach dir und anderen Gästen jener Nacht. Ich weiß noch nicht, was vor sich geht, aber ich bin sicher, du bist in etwas Größeres geraten, als du denkst. ";
			link.l1 = "Etwas Größeres? Was meinst du, Julianne?";
			link.l1.go = "Julianna_103";
		break;
		
		case "Julianna_103": // запускаем Кортни
			chrDisableReloadToLocation = true;
			DialogExit();
			sld = characterFromId("Cortny");
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_104":
			dialog.text = "Angerran... Ich meine Monseniour de Chievous hat mir eine wunderbare Perlenkette geschenkt. Eine der Perlen war schwarz wie die Nacht. Ich dachte, es wäre nur eine Fälschung mit einer netten Geschichte dahinter. Ich habe sie nie getragen, wollte keine falschen Hoffnungen wecken, aber sie ist so faszinierend schön.";
			link.l1 = "";
			link.l1.go = "Julianna_105";
		break;
		
		case "Julianna_105":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Julianna_106":
			dialog.text = "Was wirst du tun, Charles? Hast du eine Ahnung, was vor sich geht?";
			link.l1 = "Noch nicht, aber ich werde es tun. De Chievous steckt bis zum Hals in etwas Ernstem und das ist meine Chance. Seine Heimat wird es nicht wagen, ihn anzufassen, aber die britischen Behörden könnten es vielleicht tun. Ich würde dich lieber nicht entführen, Julianne.";
			link.l1.go = "Julianna_107";
		break;
		
		case "Julianna_107":
			dialog.text = "Das ist sehr nett von dir, Charles, aber nicht sehr lustig.";
			link.l1 = "";
			link.l1.go = "Julianna_108";
		break;
		
		case "Julianna_108":
			DialogExit();
			chrDisableReloadToLocation = false;
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.hour  = 20.00;
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny.function = "GoldenGirl_TimeCortny";
			pchar.quest.goldengirl_time_cortny.win_condition.l1 = "Timer";
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.hour  = 23.00;
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.goldengirl_time_cortny_fail.function = "GoldenGirl_TimeCortnyFail";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			AddQuestRecord("GoldenGirl", "17");
		break;
		
		case "Julianna_109":
			dialog.text = "Charles, hast du etwas herausgefunden? Du siehst nervös aus... Was ist los?";
			link.l1 = "Verdammt! Ich wünschte, die Dinge wären anders... Pack deine Sachen, wir sollten gehen, Marquise. Bitte mach keine Schwierigkeiten.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_110":
			pchar.quest.goldengirl_time_cortny_fail.over = "yes"; //снять прерывание
			dialog.text = "Charles, komm rein. Der Baronet ist bereits hier und wir haben angenehm geplaudert. Ich habe ihm gerade von deinem Interesse an den aktuellen Ereignissen erzählt.";
			link.l1 = "Julianne, ich bin nicht so sicher, dass es weise war...";
			link.l1.go = "Julianna_111";
		break;
		
		case "Julianna_111":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_112":
			dialog.text = "Baronet, es scheint, dass Ihre Männer gerade etwas hinter der Tür fallen gelassen haben! Würden Sie ihnen bitte sagen, dass sie sich besser benehmen sollen?";
			link.l1 = "";
			link.l1.go = "Julianna_113";
		break;
		
		case "Julianna_113":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_114":
			dialog.text = "Schrecklich! Was machen wir jetzt?!";
			link.l1 = "Verdammt! Ich wünschte, die Dinge wären anders... Pack deine Sachen, wir sollten gehen, Marquise. Bitte mach keine Schwierigkeiten.";
			link.l1.go = "Julianna_76";
		break;
		
		case "Julianna_115":
			dialog.text = "Herrgott! Was haben Sie mit meinem Wohnzimmer gemacht, meine Herren?! Das sieht aus wie ein mittelalterlicher Albtraum! Wer sind diese Leute? Und wo sind die Wachen?";
			link.l1 = "Geht es dir gut, Julianne? Gut. Ich wette, dass die Wachen ihren wohlverdienten Bestechungsgeld in einer Taverne ausgeben. Baronet, meine Glückwünsche sind angebracht - du hast es geschafft, Goodman Jack richtig zu verärgern. So ein chaotischer und schlecht vorbereiteter Attentatsversuch ist überhaupt nicht sein Stil.";
			link.l1.go = "Julianna_116";
		break;
		
		case "Julianna_116":
			DialogExit();
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_21";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_117":
			dialog.text = "Entschuldigung für die Unterbrechung eurer spannenden Diskussion, aber es sei denn, einer von euch ist verletzt, lass uns in einen Schrank ziehen. Ein Anblick wie dieser ist für eine Dame nicht sehr beruhigend... Nur die Decke ist blutfrei!";
			link.l1 = "Dann gehen Sie nach oben, Marquise. Sie sollten wirklich ein bisschen liegen und weg von all diesem Blut sein. Baronet Cortney und ich werden das durchsprechen. Sollen wir fortfahren?";
			link.l1.go = "Julianna_118";
		break;
		
		case "Julianna_118":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto2", "", 20.0);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_24";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_119":
			dialog.text = "Charles, bist du bereit, deinen Plan mit uns zu teilen?";
			link.l1 = "Fast. Sag mir, ist de Chievous ein pedantischer Typ? Hält er seine Bücher und Logs in Ordnung?";
			link.l1.go = "Julianna_120";
		break;
		
		case "Julianna_120":
			dialog.text = "Angerran ist die Verkörperung des Zögerns, wenn es um Finanzen geht! Er unterschreibt mehr Papier als jeder Bankier, den ich kenne. Ich nehme an, er war schon so seit seiner Kindheit, als er nicht wusste, wer sein Vater war und in Armut auf den Straßen lebte.";
			link.l1 = "Prächtig! Jetzt brauchen wir sein Logbuch und seine Bücher! Sie werden als stichhaltige Beweise für die Briten dienen. Wir müssen herausfinden, wie wir sie bekommen! Hätte ich das doch nur gewusst, als ich sein Schiff in meinem Besitz hatte... seufz.";
			link.l1.go = "Julianna_121";
		break;
		
		case "Julianna_121":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_27";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_122":
			dialog.text = "Warte, Charles, glaubst du wirklich, dass ich mich nach allem, was passiert ist, wie eine Bauernziege an de Chievous verkaufen lassen werde?";
			link.l1 = "Mach dir keine Sorgen, Julianne, es wird nur ein paar Tage dauern. Ich verspreche, dass sie dich behandeln werden wie eine unbezahlbare Vase aus China. Korrigiere mich, wenn ich mich irre, aber de Chievous wird sich nie zum Austausch zeigen?";
			link.l1.go = "Julianna_123";
		break;
		
		case "Julianna_123":
			dialog.text = "Ich bin mir sicher. Angerran wird unter dem Flügel von Francois de Lyons warten und wird es nie wagen, Sie auf offener See zu treffen. Aber über diese Gefangennahme von mir...";
			link.l1 = "";
			link.l1.go = "Julianna_124";
		break;
		
		case "Julianna_124":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_29";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_125":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, es tut mir leid, dich zu unterbrechen, aber hast du vergessen, meine Meinung zu all dem zu fragen? Wochenlang in diesen quietschenden Särgen... Begreifst du überhaupt, was du von mir verlangst?! Offensichtlich hängst du an diesem... Mädchen, aber ich bin nicht einer deiner Matrosen! Es tut mir leid, aber das klingt für mich nicht nach einer ernsthaften Liebesgeschichte.";
				link.l1 = "Ich fürchte, Marquise, ich muss darauf bestehen. Ich kann es mir nicht leisten, sie zu verlieren.";
				link.l1.go = "Julianna_127";
				link.l2 = "Wir alle machen Fehler, Julianna. Du von allen Menschen solltest das wissen. Ich bitte dich um Hilfe.";
				link.l2.go = "Julianna_126";
			}
			else
			{
				dialog.text = "Charles, es tut mir leid zu unterbrechen, aber hast du vergessen, meine Meinung dazu zu fragen? Wochen in diesen quietschenden Särgen... Begreifst du überhaupt, was du von mir verlangst?! Deine Gefühle sind einer klassischen Literatur über Ritterlichkeit würdig, aber ich bin nur eine gewöhnliche Kurtisane. Ich bewundere dich und ich möchte dir helfen, aber alles hat eine Grenze!";
				link.l1 = "";
				link.l1.go = "Julianna_128";
			}
		break;
		
		case "Julianna_126":
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			if(sti(pchar.reputation.nobility) > 65)
			{
				pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
				dialog.text = "Ich verstehe, Charles. Ich möchte an perfekte wahre Liebe glauben, aber ich vermute, es gibt so etwas nicht in dieser Welt.";
				link.l1 = "Danke Ihnen, Marquise. Diesmal werde ich alles richtig machen. Ich habe viel aus dieser Geschichte gelernt und bete, dass ich keinen allzu schrecklichen Preis für das zahlen muss, was ich getan habe.";
				link.l1.go = "Julianna_129";
			}
			else
			{
				dialog.text = "Du hast deine Entscheidung getroffen, ich habe dich auf all deinem Weg unterstützt, aber jetzt ist genug. Alles für die Liebe zu opfern, die du bereits in meinem Schlafzimmer aufgegeben hast. All dies ist sehr rührend, Charles, aber ich bin nicht mehr so jung und naiv.";
				link.l1 = "Ich fürchte, Marquise, ich muss darauf bestehen. Ich kann es mir nicht leisten, sie zu verlieren.";
				link.l1.go = "Julianna_127";
			}
		break;
		
		case "Julianna_127":
			pchar.questTemp.GoldenGirl.Julianna_Prisoner = "true";
			dialog.text = "Nun, Kapitän, tun Sie, was Sie wollen. Ich werde Ihnen nicht widerstehen, aber seien Sie sich bewusst, dass ich es gegen meinen Willen tue.";
			link.l1 = "Denk von mir was du willst, Julianna, ich habe es verdient. Aber ich werde sie zurückholen, koste es was es wolle. \nJulianna, hör zu, ich weiß, was ich von dir verlange. Alles hinter sich zu lassen und sich von anderen in ein fragwürdiges Spiel hineinziehen zu lassen. Aber in diesem Moment bist du meine einzige Hoffnung! Ich brauche deine Hilfe dabei und ich werde dir bis zu meinem Tod in deiner Schuld stehen!";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_128":
			pchar.questTemp.GoldenGirl.Julianna_Helper = "true";
			dialog.text = "Sehr gut, Kapitän. Am Ende muss Angerran ein für alle Mal ausgeschaltet werden. Ich werde Ihnen helfen, aber sagen Sie mir, wie wollen Sie mich von seinem Schiff retten?";
			link.l1 = "...";
			link.l1.go = "Julianna_129";
		break;
		
		case "Julianna_129":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_31";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_130":
			dialog.text = "Warte. Du kannst meine Halskette Perle nehmen, die Engländer jagen nach schwarzer Perle, richtig? Diese wird sie dazu bringen, dir zuzuhören. Was kommt als nächstes?";
			link.l1 = "Als nächstes werde ich den Ermittler an Bord nehmen und wir werden nach Guadeloupe segeln. Wir werden eine offizielle Suche auf der Fregatte de Chievous durchführen, wenn sie mit Ihnen an Bord zurückkehrt. Das Geschäft mit dem Quecksilber war ein ernsthafter Vorfall, der unseren Verbündeten betraf, daher wird De Lyon es zulassen müssen!";
			link.l1.go = "Julianna_131";
		break;
		
		case "Julianna_131":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_33";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_132":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Er wird jedem erzählen, dass seine Männer mich aus der Gefangenschaft gerettet haben. Und seien Sie vorsichtig, Kapitän, ich habe noch nicht entschieden, was ich ihnen erzählen werde.";
				link.l1 = "Es wäre vollkommen in Ordnung, nichts zu sagen, Marquise. Glauben Sie mir, ich werde Sie herausziehen und Angerran für alles bezahlen lassen.";
			}
			else
			{
				dialog.text = "Ich werde ihnen erzählen, dass ich von Fremden entführt wurde, direkt aus meinem Haus, um an Bord von Angerrans Schiff gebracht zu werden. Es wird so aussehen, als hätte er Söldner bezahlt, um mich zu entführen.";
				link.l1 = "Ein weiterer Nagel im Sarg von Angerran, Marquise.";
			}
			link.l1.go = "Julianna_133";
		break;
		
		case "Julianna_133":
			DialogExit();
			sld = characterFromId("GG_Moreno");
			sld.Dialog.currentnode = "moreno_35";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Julianna_134":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Gib mir Zeit bis zum Morgen, es sei denn, du willst mich in einem Sack tragen. Schick auch ein paar Männer, um mir zu helfen - eine Frau von Stand kann nicht ohne Annehmlichkeiten reisen. Charles, du hast mich gerettet und ich werde dir helfen, bitte nimm auch diese unbezahlbare schwarze Perle, mein Geschenk an dich. Wenn das klappt, sind wir quitt.";
				link.l1 = "Wie Ihr wünscht, Marquise. Gott beschütze Euch beide! Wir sehen uns wieder, wenn alles vorbei ist.";
			}
			else
			{
				dialog.text = "Ich werde bei Sonnenaufgang bereit sein. Ich werde nicht in einer Frachthalle herumlungern, also sorge dafür, dass ein anständiges Zimmer, oder wie auch immer du es nennst, für mich vorbereitet ist. Charles, hier, nimm das. Das ist eine kostbare schwarze Perle. Mir ist klar, dass sie mehr kostet als dieser Ort, aber manche Dinge können nicht in Gold gemessen werden. Ich hoffe, sie wird dir von Nutzen sein. Gott helfe dir!";
				link.l1 = "Viel Glück, euch beiden! Wir sehen uns hier wieder, wenn es vorbei ist.";
			}
			link.l1.go = "Julianna_135";
		break;
		
		case "Julianna_135":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			sld = characterFromId("GG_Moreno");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "23");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
			chrDisableReloadToLocation = false;
			pchar.questTemp.GoldenGirl = "antigua";
			// убрать фрегат Шиво
			pchar.quest.goldengirl_AngerranCap_AfterBattle.over = "yes";
			Group_DeleteGroup("GG_AngerranGroup");
			sld = characterFromId("GG_AngerranCap");
			sld.lifeday = 0;
			GiveItem2Character(pchar, "blackpearl"); // черная жемчужина 
		break;
		
		case "Julianna_136":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Herzlichen Glückwunsch, Kapitän. Ihr Plan hat funktioniert. Was für einen riesigen Skandal haben Sie inszeniert! Die Engländer haben Angerran und sein Schiff mit allem Inhalt, außer mir, genommen.";
				link.l1 = "Herr William ist nicht einmal gekommen, um auf Wiedersehen zu sagen. Er versprach sich zu entschuldigen.";
				link.l1.go = "Julianna_137";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
				else sld = characterFromId("Mary");
				dialog.text = "Charles, wir haben es geschafft! Sie werden dich jeden Moment freilassen! Wir müssen die Insel jedoch so schnell wie möglich verlassen. Der Gouverneur ist sehr verärgert über Angerrans jüngste Verhaftung.";
				link.l1 = "Ich freue mich, dich zu sehen, Julianne. Wie geht es dir? Wie lief der Austausch? Geht es ihr gut?";
				link.l1.go = "Julianna_140";
			}
		break;
		
		case "Julianna_137":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Ich nehme an, er war zu beschäftigt dafür. Wie unser Gouverneur gerade jetzt. Du solltest die Stadt verlassen, bevor er sich an deine Existenz erinnert. Er liebte Henri's Sohn, aber die britischen Papiere haben ihn völlig in die Ecke gedrängt. Ich würde nicht darauf warten, dass er sich entscheidet, all seinen Frust auf dich zu entladen.";
			link.l1 = "Gut genug. Außerdem wartet sie auf mich in Martinique. Wie lief der Austausch? Geht es ihr gut?";
			link.l1.go = "Julianna_138";
		break;
		
		case "Julianna_138":
			dialog.text = "Verzeihen Sie mir, aber ich möchte nicht darüber sprechen. Fragen Sie sie stattdessen. Lebewohl, Kapitän. Ich werde alleine zurückkehren. Ich muss mich von der See erholen - Francois ist ein recht netter Gastgeber, wenn er nicht von langweiligen britischen Beamten belästigt wird.";
			link.l1 = "Es tut mir aufrichtig leid wegen all dem, Madame. Danke für Ihre Zusammenarbeit trotzdem. Es freut mich zu hören, dass Sie einen neuen... Freund gemacht haben.";
			link.l1.go = "Julianna_139";
		break;
		
		case "Julianna_139":
			dialog.text = "Danke auch dir, Charles, dass du dein Wort gehalten hast. Finde Bartholomäus in meinem Haus in St. Pierre. Leb wohl. Wir werden uns wiedersehen.";
			link.l1 = "Auf Wiedersehen, Julianne. Gottes Geschwindigkeit.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_140":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Ich habe sie nicht gesehen, aber Bartholomäus hat sie lebend und gesund mitgenommen. Dieser Engländer hat de Chievous und sein Eigentum direkt unter der Nase des örtlichen Gouverneurs verhaftet - er hat kein Wort gesagt! Wunderbar!";
			link.l1 = "Weißt du, es lief überraschend reibungslos, wenn man bedenkt, was hinter dieser Verhaftung steckt. Obwohl, es könnte später doch noch nach hinten losgehen. Was auch immer! Ich muss sofort nach Martinique, ich muss sie so schnell wie möglich sehen!";
			link.l1.go = "Julianna_141";
		break;
		
		case "Julianna_141":
			dialog.text = "Es besteht kein Zweifel, dass ihr beiden viel miteinander zu besprechen habt. Oh, Charles, ich wünschte, ich hätte einen Mann mit solchem Feuer in den Augen an meiner Seite. Lass uns beeilen, ich vermisse wirklich heißes Bad und saubere Laken. Bartholomew wird uns in meinem Haus in St. Pierre erwarten.";
			link.l1 = "Ja, die Romantik der Seereisen ist überbewertet. Sie sollen meine Kabine haben, Marquise, das ist das Mindeste, was ich tun kann. Los geht's.";
			link.l1.go = "Julianna_142";
		break;
		
		case "Julianna_142":
			dialog.text = "Du hast bereits alles für mich getan, was du nur konntest, Charles. Du hast eine zynische Frau wieder glauben lassen.";
			link.l1 = "Ich auch, Julianne. Ich auch.";
			link.l1.go = "Julianna_143";
		break;
		
		case "Julianna_143":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "none", "", "", "GoldenGirl_BasterReloadJail", 7.0);
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterComplexReputation(pchar, "nobility", -10);
				ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			}
			else
			{
				ChangeCharacterComplexReputation(pchar, "fame", 15);
				ChangeCharacterNationReputation(pchar, ENGLAND, 20);
			}
		break;
		
		case "Julianna_144":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex"))
			{
				dialog.text = "Charles, ich bin so erfreut, dass du gekommen bist! Wie geht es deiner Dame? Ist sie in Ordnung?";
				link.l1 = "Alles ist gut, dank dir, Julianne. Ich wollte es dir noch einmal sagen. Du bist eine wunderbare Frau und ich werde dir für all deinen Mut und Einfallsreichtum ewig dankbar sein.";
				link.l1.go = "Julianna_145";
			}
			else
			{
				dialog.text = "Charles, ich bin so froh, dass du gekommen bist! Wie geht es deiner Dame? Ist sie in Ordnung?";
				link.l1 = "Alles ist gut, dank dir, Julianne. Ich wollte es dir noch einmal sagen. Du bist eine wundervolle Frau und ich werde dir für all deinen Mut und Einfallsreichtum ewig dankbar sein.";
				link.l1.go = "Julianna_148";
			}
		break;
		
		case "Julianna_145":
			dialog.text = "Vielleicht bin ich es, der Ihnen verpflichtet ist. Schließlich haben Sie mich vor zwei äußerst lästigen Gästen gerettet. Ich glaube, ich schulde Ihnen noch etwas. Fragen Sie nach allem, Charles.";
			link.l1 = "In diesem Fall hätte ich eine kleine Bitte an Sie, meine Dame. Sie könnten etwas tun, um uns quitt zu machen.";
			link.l1.go = "Julianna_146";
		break;
		
		case "Julianna_146":
			dialog.text = "Ich bin ganz Ohr, mein Kapitän. Was gibt's?";
			link.l1 = "Menschen machen Fehler, aber das macht die Welt nicht schlecht. Denke daran und sei glücklich, Julianne. Du hast es verdient, glücklich zu sein.";
			link.l1.go = "Julianna_147";
		break;
		
		case "Julianna_147":
			dialog.text = "Ich... Ich werde es versuchen, Charles. Danke dir. Wirst du mich ab und zu besuchen... als Freund? Du bist immer willkommen bei mir!";
			link.l1 = "Schätze es, Marquise. Lebewohl und denken Sie an das, was Sie mir versprochen haben.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_148":
			dialog.text = "Noch anscheinend nicht wunderbar genug... aber ich bin froh, dass es gut für dich geendet hat. Du schuldest mir nichts, nach dem, was du getan hast, kann ich dir nicht genug danken! Komm mich besuchen, wann immer du an Land bist. Du wirst immer willkommen sein bei mir, als ein Freund!";
			link.l1 = "Danke, Marquise. Ich wünsche alles Gute. Lebewohl!";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_149":
			DialogExit();
			npchar.dialog.currentnode = "Julianna_150";
		break;
		
		case "Julianna_150":
			dialog.text = "Charles, mein Freund, du bist so unhöflich - du besuchst mich so selten! Ich habe dich vermisst, weißt du das? Wie wäre es mit etwas Wein? Ich kann es kaum erwarten, spannende Geschichten aus erster Hand zu hören! Und dein berühmtes Glück auszuprobieren!";
			link.l1 = "Marquise, ich wollte nur hallo sagen und sicherstellen, dass es Ihnen gut geht.";
			link.l1.go = "Julianna_149";
		break;
		
		case "Julianna_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Julianna_";
		break;
		
		// Жак Дьель дю Парке
		case "governor":
			dialog.text = "Und da bist du ja, mein Freund! Schön, dich wieder zu sehen!";
			link.l1 = "... ";
			link.l1.go = "governor_1";
		break;
		
		case "governor_1":
			DialogExit();
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "governor_2":
			dialog.text = "Nun, die Art und Weise, wie Sie meinen Freund behandeln, lässt mir keine Wahl, Monsieur. Ich nehme Ihre Herausforderung an. Zeit und Ort?";
			link.l1 = "Hier und jetzt. Ruf die Diener, sag ihnen, sie sollen Kerzen bringen, ein gemütliches Zwielicht wie dieses reicht nicht aus. Dieser Ort muss hell wie der Tag sein!";
			link.l1.go = "governor_3";
		break;
		
		case "governor_3":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_4";
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			sld = characterFromId("Angerran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
		break;
		
		case "governor_4":
			dialog.text = "Mein Freund, bitte, nimm das nicht zu persönlich. Angerran ist ein übles Stück Arbeit, das ist wahr, aber du solltest nicht auf ihn schießen. Überlass das mir.";
			link.l1 = "Sind Sie sicher, Eure Exzellenz? Er ist so betrunken wie mein Quartiermeister nach einer Woche an Land, aber er weiß sicherlich, wie man sein Schwert handhabt. Ich erkenne so etwas sofort.";
			link.l1.go = "governor_5";
		break;
		
		case "governor_5":
			dialog.text = "Gott bewahre, Charles! Ich werde nicht mit ihm fechten. Wir werden spielen, Karten sind die Waffen zivilisierter Männer. Ich werde ihn ausnehmen und ihn bettelnd um ein Darlehen für eine sichere Rückkehr nach Quebec zu dir schicken.";
			link.l1 = "Das ist sicher ein solider Plan. Aber wenn Sie mich fragen, würde ich den Bastard lieber tot als arm sehen. Gott segne Sie, Eure Exzellenz!";
			link.l1.go = "governor_6";
		break;
		
		case "governor_6":
			DialogExit();
			sld = characterFromId("FortFrance_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_11";
			sld.greeting = "Marquesa_needhelp";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_7":
			dialog.text = "Verdammt, Angerran, es könnte dort unmöglich eine Zehn geben! Auf keinen Fall!";
			link.l1 = "War das eine Anschuldigung? Es war dein Geschäft, Monsieur.";
			link.l1.go = "governor_8";
		break;
		
		case "governor_8":
			dialog.text = "Es war nicht so. Ich bin nur... ein bisschen überreizt und ich entschuldige mich. Es war ein Unfall und ich verlange eine Chance auf ein Rückspiel! Dieses Schiff, ich... muss es zurückbekommen! Oder zum Teufel mit dem Spiel, sag mir einfach, für wie viel bist du bereit, es mir zu verkaufen? Nenne den Preis und ich sorge dafür, dass er morgen vor Mittag bezahlt wird!";
			link.l1 = "Ach, aber ich glaube von ganzem Herzen, dass man die Beute aus dem Glücksspiel nicht zurückkaufen kann. Man kann sie nur zurückgewinnen. Die Flöte gehört jetzt mir und ich habe nicht vor, sie zu verkaufen. Es tut mir leid, dass deine Leidenschaft dich in eine solche Position gebracht hat, manchmal sollten wir realistischer über unsere Fähigkeiten sein... Vielleicht hast du noch mehr Schiffspapiere?";
			link.l1.go = "governor_9";
		break;
		
		case "governor_9":
			dialog.text = "Du bist ein Abschaum, Angerran und du hast mich in die Enge getrieben. Ich glaube, ich kann einen Einsatz bieten, den du akzeptieren wirst.";
			link.l1 = "...";
			link.l1.go = "governor_10";
		break;
		
		case "governor_10":
			DialogExit();
			LAi_SetStayType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			bDisableCharacterMenu = false;//лоченые интерфейсы
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_23";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "governor_11":
			dialog.text = "Charles, du bist meine einzige Hoffnung, ich flehe dich an, hilf mir! Diese Flöte und ihre... Ladung wurden bereits an die Niederländische Kompanie verkauft. Ich muss ihnen morgen alle Dokumente übergeben. Ich dachte, ich würde die ganze Nacht hier bleiben, also habe ich sie mitgebracht. Ich werde in eine katastrophale Situation geraten, wenn der Deal platzt!";
			link.l1 = "Aber 'süßer Jacques', stimmst du nicht zu, dass die Frau, die du bevorzugt hast, jetzt sogar noch katastrophalere Situation gegenübersteht? Ich habe meine Portion Glücksspiel gehabt und ich verstehe so etwas wie über ein Schiff zu zocken, auch wenn es nicht dein eigenes ist. Aber über eine Dame zu zocken?! Du hast mich wirklich überrascht! Und jetzt kümmert dich nur noch das Schicksal deines Geschäfts?";
			link.l1.go = "governor_12";
		break;
		
		case "governor_12":
			dialog.text = "Verurteile mich nicht, Charles. Eine ehemalige Geliebte eines mächtigen Grafen zu bevorzugen und sich sogar ein wenig zu verlieben, ist nichts im Vergleich dazu, Peter Stuyvesant eine Million Pesos zu schulden. Wie erkläre ich das seinem Agenten? Stell dir all den Rufschaden vor!";
			link.l1 = "Ich hatte früher eine ähnliche Schulden, aber ich hatte absolut nichts und doch habe ich es geschafft. Du wirst es auch schaffen. Wir sehen uns, Jacques. Keine Versprechungen und ich werde nicht einmal fragen, welche Art von Ladung eine Million wert ist, dass du sie in der Flöte behalten würdest.";
			link.l1.go = "governor_13";
		break;
		
		case "governor_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto5", "", 10.0); // уходит
			LocatorReloadEnterDisable("FortFrance_SecBrRoom", "reload3", false); // открыть доступ в малую комнату
		break;
		
		case "governor_14":
			dialog.text = "Da bist du ja, Charles. Ich wollte dich gerade holen. De Chievous besteht auf einem Duell und lehnt bereits jegliche Versöhnungsmöglichkeiten ab. Du hast dich gut mit Karten geschlagen, aber bist du sicher, dass du das weiterhin tun möchtest?";
			link.l1 = "Ich habe einen juckenden Verdacht, Eure Exzellenz, dass Sie dieses Ergebnis die ganze Zeit wollten. Also sage ich ja. Dies muss endgültig gelöst werden. Was ist mit den Bedingungen des Duells?";
			link.l1.go = "governor_15";
		break;
		
		case "governor_15":
			dialog.text = "Du bist zu sehr in deinem Kopf, mein Freund. Einige Teile unserer Welt drehen sich immer noch nicht um dich. Glaub mir, ich bin zutiefst enttäuscht, wie alles letzte Nacht gelaufen ist. Sehr tief. Aber zuerst, lass uns über das Schicksal deiner... Gewinne sprechen.";
			link.l1 = "Gut. Möchten Sie wissen, wie Sie Ihre Flöte zurückgeben können oder wie es Madame Julianne geht?";
			link.l1.go = "governor_16";
		break;
		
		case "governor_16":
			dialog.text = "Ich sehe, du hast deine unangebrachte Ironie gegen Spott eingetauscht? Charles, wir sind auf der gleichen Seite, vergiss das nicht.";
			link.l1 = "Streitbares Argument, Eure Exzellenz. Um es gelinde auszudrücken. Wo sollen wir anfangen: das Schiff oder die Dame?";
			link.l1.go = "governor_17";
		break;
		
		case "governor_17":
			dialog.text = "Der Stuyvesant-Deal natürlich - sein Agent hat den ganzen Morgen auf mich gewartet und mir gehen die Ausreden aus. Ich brauche die Flötenpapiere, Charles.";
			link.l1 = "Gut. Sie gehört dir. Ich glaube nicht, dass de Chievous ehrlich gespielt hat, daher kannst du dein Eigentum für die Hälfte seines Preises zurückhaben. 150 000.";
			link.l1.go = "governor_18";
			link.l2 = "Ich wäre froh, Ihnen zu helfen. Wie hoch war der Preis des Schiffes, sagten Sie? 500 000? Das passt für mich.";
			link.l2.go = "governor_19";
		break;
		
		case "governor_18":
			AddMoneyToCharacter(pchar, 135000);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			dialog.text = "Nun, es werden vierhundertsechzigtausend Pesos inklusive Steuern sein. Abgemacht. 135 000.";
			link.l1 = "Hör zu... Ich werde müde vom Streiten. Also zahl, hol deine Dokumente und mach Schluss damit.";
			link.l1.go = "governor_20";
		break;
		
		case "governor_19":
			AddMoneyToCharacter(pchar, 300000);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			dialog.text = "Du hast kein Mitleid mit alten Freunden, oder Charles? Jetzt, mit allen Steuern inklusive...";
			link.l1 = "Kartenschulden und Freundschaft haben nichts gemeinsam, Eure Exzellenz. Sie werden selbst als Käufer Steuern zahlen oder ich verkaufe das Schiff in Le Francois. Bedenken Sie, ich nutze Ihre Position... noch nicht aus.";
			link.l1.go = "governor_20";
		break;
		
		case "governor_20":
			dialog.text = "Gut, so sei es. Jetzt, das Duell. Ich brauche keine Ärger mit Graf de Levi Vantadur, daher muss alles so legal wie möglich ablaufen. Hast du mich gehört, Charles? Nach dem Gesetz! Ich werde zwei Offiziere meiner Garnison schicken, um dich zu begleiten - beide sind noble und respektierte Männer. Sie werden deine Sekundanten sein, anstelle deiner üblichen ... Begleiter. Ich möchte, dass alles kristallklar ist, bis die Angelegenheit erledigt ist!";
			link.l1 = "Wie nett von Ihnen. Und was ist, wenn unser guter Freund beschließt, schmutzige Spielchen zu spielen? Ich vertraue lieber Leuten, die ich als Freunde bezeichne und die wissen, was in solchen Situationen zu tun ist, als Leuten, die in die richtigen Familien hineingeboren wurden.";
			link.l1.go = "governor_21";
		break;
		
		case "governor_21":
			dialog.text = "Charles, hör auf dich zu benehmen, als wäre dieses Duell zwischen dir und mir. Das ist eine ernste Angelegenheit. De Chievous ist kein Mann, den man tötet und einfach davonkommt. Jedes Ergebnis wird Untersuchungen nach sich ziehen, vielleicht sogar vor Gericht. Wir werden vertrauenswürdige Zeugen brauchen. Siehst du, ich kümmere mich um dich! Das Wichtigste ist jedoch, dass du ihn nicht töten kannst\nIch verstehe, Angerran ist entschlossen und wahrscheinlich ist er ein anständiger Kämpfer, aber Charles, du kannst ihn nicht töten! Verwunde ihn, demütige ihn sogar, aber hör dann auf. Wenn du ihn tötest - wird es Konsequenzen geben und keiner von uns wird in der Lage sein, ihnen auszuweichen oder sie zu überleben. Obwohl Graf von Levi Vantadur seinen Bastard nie offiziell anerkannt hat, hat er keine anderen Söhne. Seine Wut wird kein Ende haben.";
			link.l1 = "Wunderbar, also würde ich lieber mich selbst töten lassen, als zuzulassen, dass der aufgebrachte Graf dich von deinem Gouverneurssitz kickt?";
			link.l1.go = "governor_22";
		break;
		
		case "governor_22":
			dialog.text = "Ich befürchte, dass wir ohne dein Gehör Angerran de Chievous nicht mehr lange überleben werden. Denk daran und sei vorsichtig. Das Duell ist für zehn Uhr heute Abend hinter den Stadttoren angesetzt. Meine Offiziere werden dich dort treffen. Nun, zum letzten Punkt: Madame Julianne Botot - wie geht es ihr?";
			link.l1 = "Möchten Sie wissen, ob ich meinen Preis bereits genutzt habe? Nein, Exzellenz, noch nicht oder nie - das spielt keine Rolle. Was zählt, ist, dass Sie für immer aus dem Haus der Marquise verbannt sind. Sie war kristallklar darüber. Ich kann sie dafür nicht verurteilen. Julianne wird ihren nächsten Gönner selbst auswählen.";
			link.l1.go = "governor_23";
		break;
		
		case "governor_23":
			dialog.text = "Du weißt sicher, wie man überrascht, Charles. Was auch immer, ich habe ein langweiliges Treffen mit dem Agenten der Kompanie zu erledigen. Du solltest auch gehen, mach dich bereit und ich erinnere mich, was ich dich gewarnt habe.";
			link.l1 = "Ich werde es auf jeden Fall versuchen, Exzellenz. Aber es ist ein Kampf, also keine Versprechen. Danke für Ihre Hilfe.";
			link.l1.go = "governor_24";
		break;
		
		case "governor_24":
			DialogExit();
			GoldenGirl_GovernorOut();
		break;
		
		case "governor_25":
			dialog.text = "Du lebst, Charles! Was für eine Erleichterung, wie ist es dir ergangen? Ist das Blut?! Hat es de Chievous geschafft?";
			link.l1 = "Leider ja. Er ist verwundet, nicht ernsthaft. Er musste fliehen, aber er hatte auch seine Schergen auf uns geworfen. Kurz gesagt, ein Teil dieses Blutes ist nicht meins.";
			link.l1.go = "governor_26";
		break;
		
		case "governor_26":
			dialog.text = "Drecksack! Und meine Männer? Leben sie noch, um zu bezeugen, was passiert ist?";
			if (sti(pchar.questTemp.GoldenGirl.Officer) > 1)
			{
				link.l1 = "Sie sind in Ordnung, Exzellenz. Ein bisschen geschlagen, aber sie werden leben.";
				link.l1.go = "governor_27_1";
			}
			else
			{
				if (sti(pchar.questTemp.GoldenGirl.Officer) == 1)
				{
					link.l1 = "Nicht alle, Euer Exzellenz. Ein Gentleman hat es nicht geschafft - de Chievous hat sich die Mühe gemacht, Musketiere mitzubringen. Ich konnte nichts tun.";
					link.l1.go = "governor_27_2";
				}
				else 
				{
					link.l1 = "Es war die Hölle los, Exzellenz. Beide tapferen Herren fielen im Kampf. Wenn es sie nicht gäbe, würde es für mich hässlich werden. De Chievous hat einen verdammt guten Hinterhalt inszeniert.";
					link.l1.go = "governor_27_3";
				}
			}
		break;
		
		case "governor_27_1":
			dialog.text = "Prächtig! Ich werde ihre schriftlichen Aussagen in Gegenwart zuverlässiger Zeugen einholen. De Chievous wird dafür bezahlen!";
			link.l1 = "Ich glaube nicht, dass wir seinem Namen auch nur den geringsten Schaden zufügen können. Trotz all eurer Warnungen würde ich ihn lieber finden und die Arbeit selbst beenden. So ein Feigling hat es nicht verdient zu leben.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 6);
			ChangeCharacterComplexReputation(pchar, "authority", 6);
			ChangeCharacterComplexReputation(pchar, "fame", 6);
		break;
		
		case "governor_27_2":
			dialog.text = "Schrecklich. Aber wir werden zumindest eine schriftliche Aussage von einem Zeugen bekommen. De Chievous wird dafür bezahlen!";
			link.l1 = "Ich glaube nicht, dass wir seinem Namen auch nur den geringsten Schaden zufügen können. Trotz all deiner Warnungen würde ich ihn lieber selbst finden, um die Arbeit zu beenden. Ein solcher Feigling verdient es nicht zu leben.";
			link.l1.go = "governor_28";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
		break;
		
		case "governor_27_3":
			dialog.text = "Verdammt sei er! Sie waren gute Männer, Charles! Ich schwöre, der Bastard wird bezahlen!";
			link.l1 = "Ich glaube nicht, dass wir seinem Namen auch nur den geringsten Schaden zufügen können. Trotz all deiner Warnungen würde ich ihn lieber finden, um die Arbeit selbst zu beenden. Solch ein Feigling verdient es nicht zu leben.";
			link.l1.go = "governor_28";
		break;
		
		case "governor_28":
			dialog.text = "Vergiss es, Charles. Der Bastard hat all den nötigen Schaden selbst angerichtet. Ich würde wetten, er ist jetzt auf der Flucht, versteckt im Dreck irgendeiner armen Kolonie. Es ist unwahrscheinlich, dass er jetzt noch eine Bedrohung für dich darstellt. Diese Schurkerei war nur der Biss einer fliehenden Schlange. Du scheinst auch verletzt zu sein, brauchst du einen Arzt?";
			link.l1 = "Danke für Ihre Sorge, Exzellenz, aber es geht mir gut.";
			link.l1.go = "governor_29";
		break;
		
		case "governor_29":
			dialog.text = "Gut zu wissen. Sie können jetzt frei atmen, diese Geschichte ist vorbei. Entspannen Sie sich und kümmern Sie sich um Ihre Angelegenheiten. Übrigens, darüber... Wir haben unser vorheriges Gespräch über Ihre jüngsten Gewinne nicht beendet. Haben Sie sich entschieden, was Sie damit machen werden?";
			link.l1 = "Ich verstehe dich nicht ganz, Jacques. Was meinst du mit 'Es'? Meinst du die Marquise? Scheiße! Madame Botot! De Chievous ist auf der Flucht, er ist keine Bedrohung mehr für mich, aber er ist verzweifelt und kann alles tun! Ich sollte gehen! Schicke die Wachen zum Haus der Marquise! Jetzt!";
			link.l1.go = "governor_30";
		break;
		
		case "governor_30":
			DialogExit();
			GoldenGirl_ToJulianna();
		break;
		
		case "governor_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "governor_";
		break;
		
		case "Angerran":
			if (pchar.questTemp.Sharlie == "escape")
			{
				dialog.text = "Ein berühmter Kapitän, sagst du? Derjenige, der den spanischen Angriff abgewehrt hat und beinahe diese kleine Stadt verbrannt hat? Ich verstehe. Was ist dein Gift?";
			}
			else
			{
				dialog.text = "Ein berühmter Kapitän, sagst du? Ich habe noch nie von Ihnen gehört... Was ist dein Gift?";
			}
			link.l1 = "...";
			if (pchar.questTemp.GoldenGirl.Vine == "red") link.l1.go = "Angerran_1";
			else link.l1.go = "Angerran_2";
		break;
		
		case "Angerran_1":
			dialog.text = "Pinot Noir, genau wie unsere schöne Gastgeberin? Sind Sie sicher, dass Sie nach all diesem Meersalz noch richtig schmecken können? Normalerweise ziehen Leute Ihrer Kragenweite es vor, Zeug zu trinken, das einen alten Stiefel auflösen kann.";
			link.l1 = "Wenn dies ein Vorschlag war, gemeinsam durch die Tore zu gehen, dann bin ich dabei. Ich mag dich auch nicht und ich bin froh, dass das Gefühl auf Gegenseitigkeit beruht. Lassen wir das Gerede, du bist sowieso nicht gut darin. Ich überlasse dir die Wahl der Bedingungen und Waffen.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_2":
			dialog.text = "Ein Strauß aus Dreck und Katzenpisse? Charmant! Sie lassen diesen sauren Mist nicht einmal in Fässern reifen, denn es wird sowieso nie zu Wein. Sag mir, klopft das Meersalz so hart auf den Geschmack?";
			link.l1 = "Wenn das ein Vorschlag war, gemeinsam durch die Tore zu gehen, dann bin ich dabei. Ich mag dich auch nicht und bin froh, dass das Gefühl auf Gegenseitigkeit beruht. Lassen wir das Gerede, du bist sowieso nicht gut darin. Ich überlasse dir die Wahl der Bedingungen und Waffen.";
			link.l1.go = "Angerran_3";
		break;
		
		case "Angerran_3":
			dialog.text = "Ha, so ein tapferer Junge! Beruhige jetzt dein Temperament und halte Abstand. Wir sind nicht in einer Taverne und ich bin nicht dein Trinkkumpan. Du bist weit unter meiner Klasse, wir sollten gar nicht erst reden, aber die Dame hat es verlangt. Nun, Jacques und ich haben noch eine offene Rechnung...";
			link.l1 = "";
			link.l1.go = "Angerran_4";
		break;
		
		case "Angerran_4": // перекидываем pchar на Ангеррана и говорим с губером
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Angerran"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
			bDisableCharacterMenu = true;//лоченые интерфейсы
		break;
		
		case "Angerran_5":
			dialog.text = "Julianne, geht es dir gut? Wasser, ihr Idioten! Bringt Wasser!";
			link.l1 = "...";
			link.l1.go = "Angerran_6";
		break;
		
		case "Angerran_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.Dialog.currentnode = "Julianna_28";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "Angerran_7":
			dialog.text = "Du hast vollkommen recht, es ist hier schwül. Es war bisher ein sehr unterhaltsames Spiel, aber lass uns eine kleine Pause vor dem Finale machen. Auf Wiedersehen, Jacques - erinnerst du dich an die Bedingungen unseres Turniers?\nUnd hier haben wir Charles de Maure, stimmt? Ein Kapitän mit einem schlechten Geschmack für Wein, ich erinnere mich an dich. Mach dir keine Sorgen, nachdem ich hier fertig bin, wirst du nur noch Wasser trinken. Also nimm dir Zeit, genieße den Moment, trink etwas. Wenn du bereit bist, komm und begleite mich in diesem kleinen Raum. Wir werden die Nacht in einer angenehmeren Umgebung beenden...";
			link.l1 = "Freue mich darauf, 'monsieur'.";
			link.l1.go = "Angerran_8";
		break;
		
		case "Angerran_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "Location_reserve_02", "goto", "goto6", "GoldenGirl_AngerranCards", 10.0); // уходит
			sld = characterFromId("FortFrance_Mayor");
			sld.dialog.currentnode = "governor_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Angerran_9":
			dialog.text = "Da bist du ja, endlich. Bereit, dich von deinem Geld zu trennen?";
			link.l1 = "Ich würde lieber deine zu ihnen hinzufügen. Bitte!";
			link.l1.go = "Angerran_10";
		break;
		
		case "Angerran_10":
			dialog.text = "Gut gesagt, leider bestand unser lieber Gouverneur darauf, die Regeln kurz vor seiner schändlichen Niederlage zu ändern. Jetzt sind wir verpflichtet, etwas mehr zum Einsatz hinzuzufügen. Die Einsätze müssen von beiden Parteien anerkannt werden. Mein Einsatz ist die Flöte mit Silber.";
			link.l1 = "Los geht's, das ist langweilig - Ich kann in ein paar Wochen Raub fünf von ihnen mit Gold bekommen. Gib mir etwas Größeres.";
			link.l1.go = "Angerran_11";
		break;
		
		case "Angerran_11":
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Ja, ich habe dein Schiff gesehen, ich muss zugeben, es ist wirklich ein Anblick zum Bewundern. Lassen wir es dann steigen - zwei Schiffe gegen eins. Meine Fregatte und Flöte mit Silber gegen dein Schiff?";
				link.l1 = "Ein würdiges Spiel! Madame Botot lag falsch - DIESER Zweikampf wird in Legenden leben. Abgemacht!";
			}
			else
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
				{
					dialog.text = "Schau mal an, unser Kapitän ist ein unartiger Bursche! Jedoch ist das Freibeutertum heilig. Wie wäre es dann mit einem Kriegsschiff? Eine Fregatte, 48 Kanonen. Schneller als viele Korvetten - ein Produkt königlicher Werften, noch weiter verbessert von den besten Schiffsbauern der Welt. Die von ihr getragenen Kartaunen haben eine hervorragende Reichweite und Genauigkeit. Was sagst du dazu?";
					link.l1 = "Viel besser, ich bin dabei! Los geht's!";
				}
				else
				{
					dialog.text = "Ich habe gehört, was ihr hier geankert habt, Kapitän. Seid dankbar, dass ich zugestimmt habe, eure alte Kiste als Einsatz zu akzeptieren. Kommt dann, es sei denn, ihr lehnt ab?";
					link.l1 = "Gut, du hast einen Punkt. Lass uns gehen.";
				}
			}
			link.l1.go = "Angerran_12";
		break;
		
		case "Angerran_12":
			DialogExit();
			npchar.money = 200000;
			pchar.questTemp.GoldenGirl.Game.G3 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_13":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
				{
					dialog.text = "Spiel vorbei, Kapitän, du hast bekommen, was du wolltest. Schwelge in deinem Triumph, wenn du willst. Ich schlage vor, wir besprechen die Bedingungen für den Kauf meines Fregattenschiffs morgen Mittag.";
					link.l1 = "Das ist alles? Ich glaube aufrichtig, genau wie du, dass das, was beim Glücksspiel verloren geht, nicht herausgekauft werden kann, nur zurückgewonnen. Oder ich kann sie an lokale Fischer verkaufen und ihnen alles über deine großzügige Spende erzählen.";
					link.l1.go = "Angerran_15";
				}
				else
				{
					if (sti(RealShips[sti(pchar.ship.type)].Class) <= 3)
					{
						dialog.text = "So hat das Schicksal gesprochen. Das hat sich ganz merkwürdig entwickelt. Glückwunsch. Kapitän de Maure. Ich schlage vor, wir besprechen die Bedingungen für den Ankauf meiner Fregatte morgen Mittag.";
						link.l1 = "So bald? Wir enttäuschen andere Gäste, Monsieur. Wenn ich mich richtig erinnere, haben Sie noch ein weiteres Schiff. Ich glaube aufrichtig, genau wie Sie, dass das, was im Spiel verloren geht, nicht ausgelöst werden kann, sondern nur zurückgewonnen werden kann.";
						link.l1.go = "Angerran_16";
					}
					else
					{
						dialog.text = "So hatte das Schicksal ihr Wort. Das hat sich sehr kurios entwickelt. Glückwunsch, Kapitän de Maure. Sie haben sich einen ordentlichen Trunk verdient, probieren Sie Sangiovese. Ich nehme an, Jacques wird Ihnen gut für diese Badewanne bezahlen, es scheint, er hat Gefühle für sie, Gefühle, die viel größer sind als für andere bestimmte Dinge. Es wird ausreichen, um einen anständigen Wein zu kaufen.";
						link.l1 = "Kapitulieren Sie schon? Wir enttäuschen die anderen Gäste, Monsieur. Wenn ich mich richtig erinnere, haben Sie noch ein weiteres Schiff. Ich fordere Ihre Fregatte gegen meine Flöte mit Silber heraus, da Sie mein eigenes Schiff für zu bescheiden hielten.";
						link.l1.go = "Angerran_17";
					}
				}
			}
			else
			{
				dialog.text = "Schlechtes Glück, Kapitän. Dennoch schätze ich Ihre Tapferkeit, und ich bin heute gut gelaunt. Ich nehme Ihr Gold, aber Sie können Ihr Schiff behalten. Verschwinden Sie aus meinen Augen und bitte vermeiden Sie in der Zukunft das Glücksspiel. Eines Tages wird es Sie töten.";
				link.l1 = "Sehr edel von Ihnen, das habe ich nicht erwartet. Lebewohl, Monsieur de Chievous.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_14":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Cards");
			GoldenGirl_CardsFail();
		break;
		
		case "Angerran_15":
			dialog.text = "Es gibt einen bemerkenswerten Unterschied zwischen dem Triumphieren und dem Verspotten Ihres besiegten Gegners, Monsieur de Maure.";
			link.l1 = "Bereits besiegt? Aber es fing so gut an... ah! Madame Botot, ich glaube, Ihr Salon hat gerade eine weitere reiche Geschichte über die Unterschiede zwischen sagen und tun bekommen!";
			link.l1.go = "Angerran_15_1";
		break;
		
		case "Angerran_15_1":
			dialog.text = "Was willst du noch? Ich habe auch keine weiteren Schiffe hinter meinem Gürtel und genug Bargeld, um auch nur ein Schiff zu decken. Über Dublonen zu spielen ist nach allem, was wir heute Abend gesehen haben, nicht ernst.";
			link.l1 = "Bist du weniger einfallsreich als unser süßer Jacques Dille do Parkuet? Ich schenke dir die schönste Gelegenheit zu beweisen, dass nicht alle Liebe käuflich ist. Das Glück verkauft seine Gunst auch nicht. Das Silberschiff und deine Fregatte gegen das, was du mehr als Gold schätzt.";
			link.l1.go = "Angerran_15_2";
		break;
		
		case "Angerran_15_2":
			dialog.text = "Kapitän, das ist nicht einmal lustig. Lassen Sie uns das erledigen - der Morgen kommt bald. Wir werden morgen über den Auskauf meiner Fregatte sprechen.";
			link.l1 = "Gut, du hast es - drei Schiffe! Einschließlich eines echten Kriegsschiffes gegen die teuerste... nun ja, teuerste Dame der Neuen Welt. Kannst du überhaupt so einen Einsatz ablehnen?";
			link.l1.go = "Angerran_15_3";
		break;
		
		case "Angerran_15_3":
			dialog.text = "Es wäre Wahnsinn. Obwohl, es ist Wahnsinn, Monsieur de Maure. Bitte. Aber denken Sie daran, es war Ihre Idee.";
			link.l1 = "Das wird die Legende sein, die sie ein Jahr lang hinter verschlossenen Türen genießen werden! Hey du, mehr Wein und Kerzen! Das Spiel muss weitergehen!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_16":
			dialog.text = "Soeben hieltest du diese Flöte für einen unwürdigen Einsatz gegen unsere Schiffe. Was hat sich geändert?";
			link.l1 = "Habe mich gelangweilt. Lass uns etwas Würze zu unserem Duell hinzufügen - deine Fregatte und mein Schiff gegen...";
			link.l1.go = "Angerran_16_1";
		break;
		
		case "Angerran_16_1":
			dialog.text = "Die Flöte, die du so gering schätzt? Bist du etwa im Fieber? Du siehst nicht allzu gut aus.";
			link.l1 = "Ich bin völlig in Ordnung, danke. Du hast nicht zugehört. Zwei zu eins Einsätze sind nicht gerade spektakulär, das stimmt, also lasst uns die Chancen ausgleichen! Nicht alle Werte können in Gold gemessen werden, nicht wahr? Oder vielleicht ziehst du es einfach vor, nicht gegen den Wind zu kämpfen, wenn etwas nicht nach deinem Plan läuft, so dass du deinen Kurs änderst? Schade dann, es scheint, ich habe mich in dir getäuscht. Madame Botot, ich glaube, Ihr Salon hat gerade eine weitere reiche Geschichte über die Unterschiede zwischen Sagen und Tun bekommen...";
			link.l1.go = "Angerran_16_2";
		break;
		
		case "Angerran_16_2":
			dialog.text = "Versuchen Sie nicht, mich zu durchschauen, Monsieur de Maure, Sie sind viel zu naiv dafür.";
			link.l1 = "Gewiss. Der Mangel an Willen ist keine Sünde... es sei denn, du bist natürlich ein Militärmann. Oder ein Adeliger, Familienehre, wie du vielleicht weißt, ist manchmal so eine Last. Wahrscheinlich bist du mit solchen Dilemmata allerdings überhaupt nicht vertraut.";
			link.l1.go = "Angerran_16_3";
		break;
		
		case "Angerran_16_3":
			dialog.text = "Versuchst du ein Duell zu beginnen oder ein Spiel fortzusetzen?";
			link.l1 = "Beides würde passen. Ich werde der Weinsammlung der Marquise Tribut zollen, während du dich sammelst.";
			link.l1.go = "Angerran_16_4";
		break;
		
		case "Angerran_16_4":
			dialog.text = "So sei es. Diese Nacht sollte ordentlich enden. Zwei große Schiffe gegen die alte Wanne voller Silber und die beste Frau von Neu-Frankreich! Atme tiefer, Monsieur de Maure, dieser Einsatz wird zur Legende unter den Klatschern der gehobenen Gesellschaft.";
			link.l1 = "Ihre Niederlage wird in der Tat zur Legende werden, Monsieur de Chievous. Bringt uns mehr Wein und Kerzen! Lasst es uns tun!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_17":
			dialog.text = "Sie haben über Glück den Kopf verloren, Monsieur de Maure. Sie riskieren hier, die Gunst des Mangels ist kurz.";
			link.l1 = "Kurzer Gefallen ist ein Weg zur wahren Liebe. Das Gleiche kann über gekaufte Loyalität gesagt werden. Sie führt nur zu Verachtung oder Langeweile.";
			link.l1.go = "Angerran_17_1";
		break;
		
		case "Angerran_17_1":
			dialog.text = "Deine Versuche, mir unter die Haut zu gehen, amüsieren mich. Du solltest besser Madame Juliana nach Dingen wie Gunst, Liebe und allem anderen fragen, das du kaufen kannst oder nicht. Aber beeile dich - sie verlässt morgen die Stadt.";
			link.l1 = "Zumindest ist Ihr Wissen über das Thema einseitig. Sie können die Gunst von Lady Fortune weder durch Gewinnen noch durch Bezahlen hier gewinnen, daher können Sie ihre Liebe nicht kennen. Es braucht Mut, Monsieur, und einen unerschütterlichen Willen, ein Risiko einzugehen. Ganz zu schweigen davon, dass auch mehr... irdische Damen diese Dinge schätzen. Ich setze zwei meiner Schiffe gegen eines von Ihnen, sind Sie dabei?";
			link.l1.go = "Angerran_17_2";
		break;
		
		case "Angerran_17_2":
			dialog.text = "Sie wollen so eifrig weitermachen? Gut, was auch immer. Aber lassen Sie uns zumindest etwas Drama hinzufügen, Monsieur de Maure. Sie sagten etwas von Liebe und Preisen? Ich schlage vor, unsere Einsätze auszugleichen - Ihre Wanne und die Silberflöte gegen meine Fregatte und die beste Frau von Neu-Frankreich. Was sagen Sie jetzt?";
			link.l1 = "Ich sage, dass Sie definitiv stilvoll zu spielen wissen, Monsieur! Mehr Wein und Kerzen! Los geht's!";
			link.l1.go = "Angerran_18";
		break;
		
		case "Angerran_18":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.GoldenGirl.Game"); // fix 22-03-20
			npchar.money = 70000; // на 2 кона
			pchar.questTemp.GoldenGirl.Game.G4 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "Angerran_19":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Unglaublich, Monsieur de Maure, das ist einfach unglaublich!";
				link.l1 = "Ja klar, Europa hat seit der Schlacht von Rocroi keine solche Niederlage mehr erlebt, Monsieur de Chievous. Ein Künstler, der irgendwo in mir lebt, zittert vor Verlangen, einen solchen historischen Moment zu malen. Es ist schade, dass ich nicht mehr zeichne wie in meiner Jugend. Aber vielleicht hat Madame Julianne einen talentierten Künstler zur Hand, nicht wahr?";
				link.l1.go = "Angerran_20";
			}
			else
			{
				dialog.text = "Schlechtes Glück, Kapitän. Trotzdem schätze ich Ihren Mut, zudem bin ich heute gut gelaunt. Ich nehme Ihr Gold, aber Sie können Ihr Schiff behalten. Verschwinden Sie aus meinem Blick und bitte vermeiden Sie in Zukunft das Glücksspiel. Eines Tages wird es Sie umbringen.";
				link.l1 = "Sehr edel von Ihnen, das habe ich nicht erwartet. Auf Wiedersehen, Monsieur de Chievous.";
				link.l1.go = "Angerran_14";
			}
		break;
		
		case "Angerran_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_30";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_21":
			dialog.text = "Nein, du verstehst nicht. Das ist so unglaublich, dass es einfach nicht sein kann!";
			link.l1 = "Wir alle haben die Karten gesehen, Monsieur de Chievous - das Schicksal lügt nie.";
			link.l1.go = "Angerran_22";
		break;
		
		case "Angerran_22":
			dialog.text = "Das Glück nicht, aber du, Monsieur de Maure, das tust du! Es scheint mir, dass hinter deiner Unverschämtheit ein Plan steckte, nicht nur Leidenschaft. Du bist ein Lügner und ein Betrüger - ich bin bereit, dies vor allen Gästen zu bestätigen.";
			link.l1 = "...";
			link.l1.go = "Angerran_23";
		break;
		
		case "Angerran_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_32";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_24":
			dialog.text = "";
			link.l1 = "Herr de Chievous, habe ich das richtig gehört? Sie sind bereit, Ihre Verdächtigungen nicht nur mit Worten zu bestätigen? Es scheint, dass Ihre Beleidigungen zu weit gehen und ich, im Gegensatz zu Ihnen, schätze meine Familienehre.";
			link.l1.go = "Angerran_25";
		break;
		
		case "Angerran_25":
			dialog.text = "Zweiter Sohn, ein Betrüger und Hochstapler wird mit mir nicht über Familienehre sprechen! Halte den Mund, Julianne, ich werde mich später mit dir beschäftigen! Charles de Maure, ich bestehe darauf, dass du mir sofort Genugtuung gibst! Schwert oder Pistole?";
			link.l1 = "Beides. Ehrlich gesagt, bin ich froh, dass du deine Meinung geändert hast. Erinnerst du dich, wie ich vorschlug, wir machen einen Spaziergang vorbei an den Toren? Was hast du über meine unwürdige Klasse gesagt? Vielleicht hat dir das Kartenspiel doch etwas Mut geschenkt?";
			link.l1.go = "Angerran_26";
		break;
		
		case "Angerran_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_34";
			sld.greeting = "Marquesa_vecherkonchen";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_27":
			dialog.text = "Zu große Ehre, aber ich stimme mit der Marquise überein. Ich werde dich wie einen Edelmann beenden, de Maure, obwohl du dies nicht verdienst. Ich fordere dich morgen Mittag zu einem Duell heraus, durch Seine Exzellenz den Gouverneur. Komm selbst zu ihm oder schicke deine Sekunden, um die Bedingungen zu besprechen. Bis dann. Madame, meine Achtung.";
			link.l1 = "...";
			link.l1.go = "Angerran_28";
		break;
		
		case "Angerran_28":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0); // уходит
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_36";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Angerran_29":
			dialog.text = "Und da bist du ja, der Liebling des Glücks. Hast du dich um deine Sachen gekümmert, hoffe ich? Nicht vergessen zu beichten? Sie sagen, die Hölle kann ohne sie ziemlich ungemütlich sein.";
			link.l1 = "Gerede ist billig, Monsieur. Sie können nicht ordentlich Karten spielen, jetzt stellen wir Ihre Fechtkunst auf die Probe... Lassen Sie uns tanzen!";
			link.l1.go = "Angerran_30";
		break;
		
		case "Angerran_30":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ExitTown")], false);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantGG_"+i);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocator(sld, "goto", "goto1"+(7+i), "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			}
			LAi_group_Delete("EnemyFight");
			LAi_SetCheckMinHP(npchar, 10, true, "GoldenGirl_Duel"); 
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Angerran_31":
			dialog.text = "Schön.. eins, verdammt nochmal. Aber ich lebe noch!";
			link.l1 = "Deine Wunde sieht nicht gut aus, aber du solltest dich trotzdem einem Arzt zeigen. Offensichtlich kannst du so nicht weitermachen, du wirst sterben, wenn du es tust. Es sieht so aus, als wären wir hier fertig. Ich habe gewonnen, und ich habe nicht betrogen. Ich werde dir dein Schiff zurückgeben und du wirst St. Pierre verlassen. Wir werden uns nie wiedersehen.";
			link.l1.go = "Angerran_32";
		break;
		
		case "Angerran_32":
			dialog.text = "Welch enorme Ritterlichkeit! Schau, Monsieur de Maure, du magst ein natürlicher Schwertkämpfer sein, aber beim Kartenspiel hast du definitiv betrogen. Ich habe das Deck dreimal manipuliert. Dreimal, verdammt! Kein Wunder der Welt könnte dich möglichweise retten, aber du hast trotzdem gewonnen! Ich wünschte, ich wüsste, wie du das gemacht hast... Wie auch immer, bald wirst du dem Teufel alles darüber erzählen. Schlage sie, Jungs!";
			link.l1 = "Du Bastard! Ich habe dir Gnade gezeigt und so dankst du mir?! Messieurs, zu den Waffen!";
			link.l1.go = "Angerran_33";
		break;
		
		case "Angerran_33":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 20.0);
			LAi_RemoveCheckMinHP(npchar); 
            LAi_SetCurHPMax(npchar);
			GoldenGirl_DuelNext();
		break;
		
		case "Angerran_34":
			dialog.text = "Ich gebe zu, Monseniour de Maure, ich bin ein wenig überrascht, Sie hier zu sehen. Das bedeutet, ich lag nicht falsch über Sie und die wilde Maid bedeutet Ihnen etwas?";
			link.l1 = "Ich frage mich, was Ihre guter Freund de Lyons Haltung zum Entführen von Offizieren von angesehenen Kapitänen unserer Marine ist? Vielleicht sollten wir ihn bitten, sich uns anzuschließen und ihm die ganze Geschichte zu erzählen?";
			link.l1.go = "Angerran_35";
		break;
		
		case "Angerran_35":
			dialog.text = "Das wird dir kein bisschen helfen, vertrau mir. Außerdem habe ich deine Schlampe besser behandelt als einen gefangenen General. Fürs Erste. Aber alles kann sich ändern und es liegt an dir, Charles.";
			link.l1 = "Ich erinnere mich nicht daran, mit dir einen Liebesschuss getrunken zu haben. Charles mich nicht, Monsieur de Chievous. Komm sofort zur Sache und sag mir, was du von mir willst?";
			link.l1.go = "Angerran_36";
		break;
		
		case "Angerran_36":
			dialog.text = "Von dir? Nichts, Gott bewahre! Du und ich haben gerade einen unglücklichen Streit nach einem skandalösen Kartenspiel beigelegt, ein paar Drinks gehabt und diesen Raum als gute alte Freunde verlassen.";
			link.l1 = "Angerran, du siehst trotz deiner kürzlichen Wunde gut aus und jede Minute dieses wertlosen Geschwätzes lässt mich das beheben wollen. Sogar der Gedanke, diese feinen Teppiche von Francois de Lyons zu verderben, wird für mich immer reizvoller.";
			link.l1.go = "Angerran_37";
		break;
		
		case "Angerran_37":
			dialog.text = "Aber der gute alte Francois liebt diese Teppiche, Charles. Jeder liebt etwas. Da du hier bist, musst du deine kleine Freundin im Arm lieben. Ich bin bereit, sie dir gegen meine Eigentum zurückzugeben. Du hast das Spiel vermasselt und obwohl ich solche Vergehen normalerweise nicht verzeihe, kann ich für dich eine Ausnahme machen. Du wirst mir den Preis geben, den ich so sehr begehre und ich werde dir dasselbe geben. Dann werden wir uns auf schöne Weise trennen. So viel zur Liebe.";
			link.l1 = "Denkst du, ich trage die Marquise wie ein verdammtes Juwel in meiner Börse? Unsinn! Wie könnte ich sie dir überhaupt geben?!";
			link.l1.go = "Angerran_38";
		break;
		
		case "Angerran_38":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Ich kümmere mich überhaupt nicht darum, Charles. Du hast zwei Wochen Zeit, um das zu regeln. Und ja, ich möchte, dass dieser Preis heimlich erhalten wird. Sagen wir, irgendein Kapitän, der eine lächerlich teure Kurtisane gewonnen hat, es aber dennoch nicht geschafft hat, ihre Gunst zu gewinnen, könnte etwas Dummes darüber tun, richtig? Denkst du, du bist schon verzweifelt genug, Charles?";
			link.l1 = "Ich möchte zuerst meinen Offizier sehen, um sicher zu sein, ob sie noch lebt.";
			link.l1.go = "Angerran_39";
		break;
		
		case "Angerran_39":
			dialog.text = "Ausgeschlossen. Du wirst meinem Wort vertrauen müssen. Sie bleibt an einem sicheren Ort und sie bleibt dort, bis ich meinen Preis bekomme. Aber wenn du darauf bestehst, sie vorher zu sehen, werde ich dir gerne entgegenkommen, indem ich dir einen Teil von ihr schicke. Was sind deine Favoriten? Ein Ohr, eine Nase, ein paar Finger?";
			link.l1 = "Leg eine Hand auf sie, du Abschaum, und ich werde dich mit meinen bloßen Händen erwürgen, das schwöre ich bei Gott! Verdammt nochmal, fordere mich nicht heraus!";
			link.l1.go = "Angerran_40";
		break;
		
		case "Angerran_40":
			dialog.text = "Beruhige dich. Alles, was passieren wird, hängt ganz von dir ab. Ich mag keine Gewalt, ich setze sie nur ein, wenn ich muss. Zwing mich nicht dazu. Übergib mir einfach meinen Preis auf Cape Scott Head auf Dominica in weniger als zwei Wochen und du bekommst, was dir gehört. Es ist mir egal, wie du es machst. Wenn du stehlen willst - stehle, du bist schließlich ein Pirat, nur gut gekleidet.";
			link.l1 = "Du bist verdammt verrückt, es gibt einen großen Unterschied zwischen einem Piraten und einem verdammten Sklavenhändler...";
			link.l1.go = "Angerran_41";
		break;
		
		case "Angerran_41":
			dialog.text = "Atme tiefer, wir sind kurz davor, vor dem alten Francois aufzutreten. Wir sind jetzt Freunde, erinnere dich? Lächle Charles, komm schon! Lassen wir uns trennen. Cape Scott Head, Dominica, zwei Wochen. Sei nicht zu spät.";
			link.l1 = "Ich werde dich dort sehen.";
			link.l1.go = "Angerran_42";
		break;
		
		case "Angerran_42":
			DialogExit();
			DoQuestReloadToLocation("Baster_townhall", "goto", "goto1", "GoldenGirl_AfterBaster");
		break;
		
		case "Cortny":
			PlaySound("VOICE\English\LE\Cortny\Cortny_01.wav");
			dialog.text = "Guten Abend, Frau Botot, Kapitän de Maure. Ich bitte Sie, ruhig zu bleiben.";
			link.l1 = "Marquise, hinter mir, jetzt! Monseniour, was bedeutet das?!";
			link.l1.go = "Cortny_1";
		break;
		
		case "Cortny_1":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "Ich habe ein Dutzend Männer hinter der Tür und Notfallvollmachten, die von Ihrem Staat genehmigt wurden. Die Wachen werden Ihnen nicht helfen. Legen Sie daher bitte Ihr Schwert weg, Herr. Ich möchte nur reden. Für jetzt.";
			link.l1 = "Herr, wer sind Sie und wie sind Sie hierher gekommen?! Sie sollten sich erklären!";
			link.l1.go = "Cortny_2";
		break;
		
		case "Cortny_2":
			dialog.text = "Erlauben Sie mir, mich vorzustellen - Sir William Cortney, Baronet Cortney. Jetzt beruhigen wir uns alle und reden.";
			link.l1 = "Gut, Monseniour Cortney, wir sind ganz Ohr.";
			link.l1.go = "Cortny_3";
		break;
		
		case "Cortny_3":
			dialog.text = "Entschuldigen Sie bitte, dass ich lausche, aber die aktuellen Umstände lassen mir keine andere Wahl. Auch wenn ich hier in St. Pierre anonym bleibe, führe ich im Auftrag der Krone von England eine äußerst wichtige Untersuchung durch. Es geht um ein Kurierschiff, das auf See verloren ging. Haben Sie jemals von einer Brigantine namens Regina gehört?";
			link.l1 = "Ich habe nicht und ich folge nicht Ihren zwielichtigen Hinweisen, Monseniour. Ich bin ein ehrlicher Kapitän...";
			link.l1.go = "Cortny_4";
		break;
		
		case "Cortny_4":
			dialog.text = "Ich gebe keinen kleinen Dreck auf Ihre zwielichtigen Geschäfte, mein Herr. Ich habe ein wenig über Sie gegraben und, um ehrlich zu sein, habe ich Sie zu meinem ersten Verdächtigen gemacht, als ich hörte, dass Sie Martinique kurz nach dem Verschwinden der Regina besucht haben. Sie sind jedoch kein Idiot und Ihre Männer haben hier nicht mit Perlen herumgespielt. Daher sind Sie vorerst nicht mehr in meinem Verdacht.";
			link.l1 = "Perlen? Welche Perlen faselst du da?";
			link.l1.go = "Cortny_5";
		break;
		
		case "Cortny_5":
			dialog.text = "Handverlesene, große Perlen aus den Operationen des Spanischen Westhaupt. Die Perlen sind auch schwarz, was bedeutet, dass sie extrem selten sind, hast du jemals von solchen gehört?";
			link.l1 = "Ich vermute, aber ich dachte immer, es ist nur eine weitere Seefahrer-Schwachsinnsgeschichte. Genauso wie Geschichten über den Fliegenden Holländer. Julianne, was ist los?";
			link.l1.go = "Cortny_6";
		break;
		
		case "Cortny_6":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_104";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_7":
			dialog.text = "Ich muss Sie bitten, es hier vorzustellen, Madame. Es ist von größter Wichtigkeit. In der Zwischenzeit, Sie Herr, müssen mir alles über Kapitän Moreno erzählen. Ich vermute, er war es, der Ihnen diesen Hinweis gegeben hat. Ich bin sehr neugierig, seine Rolle in diesem Spiel zu erfahren.";
			if (CheckAttribute(pchar, "questTemp.Portugal"))
			{
				link.l1 = "Moreno ist nicht sein echter Name, Monseniour Cortney. Sein Name ist Hernando Vasquez, auch bekannt als der Blutige Don, ein spanischer Pirat, der einst Quartiermeister der Albatros war - das Schiff des berüchtigten Bartholomäus der Portugiese.";
				link.l1.go = "Cortny_8";
			}
			else
			{
				link.l1 = "Wir haben nur ein paar Worte gewechselt. Ich habe nicht viel zu erzählen. Er sah aus wie ein echter Seewolf.";
				link.l1.go = "Cortny_9";
			}
		break;
		
		case "Cortny_8":
			dialog.text = "Also, also. Und darf ich fragen, wie Sie das wissen?";
			link.l1 = "Ich kannte einst seinen Kapitän. Tatsächlich war ich es, der ihn gefangen nahm und den Holländern übergab. Es ist eine lange Geschichte. Schade, dass ich damals nicht Vasquez selbst bekommen habe...";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_9":
			dialog.text = "Sie sind selbst ein Seewolf, Herr. Ich glaube nicht, dass Sie mehr übersehen haben.";
			link.l1 = "Nur ein leichter Akzent, die Art und Weise, wie er aussah und sich verhielt. Ich wette, er ist ein Spanier, Monsieur Cortney.";
			link.l1.go = "Cortny_10";
		break;
		
		case "Cortny_10":
			dialog.text = "Das ist ein Spielverderber, Herr. Und es ist schlecht. Madame, haben Sie die Halskette gefunden? Lassen Sie mich sie inspizieren\nJa tatsächlich, das ist eine der spanischen Schwarzen Perlen. Schauen Sie mal, dieser Seefahrer's Quatsch ist ziemlich real. Alles, was noch übrig bleibt, ist herauszufinden, wie dieser de Chievous eine davon bekommen hat. Übrigens, ist er nicht ein Bastard von Herzog de Levy Vantadur?";
			link.l1 = "Das ist er, ganz richtig. Soweit wir wissen, hatte er Geschäfte mit dem örtlichen Piratenbaron in Le Francois. Vielleicht hat er diese Perle von ihm gekauft?";
			link.l1.go = "Cortny_11";
		break;
		
		case "Cortny_11":
			dialog.text = "Vielleicht. Aber mir gefällt die spanische Spur in all dem überhaupt nicht. Wie auch immer, danke für deine Zusammenarbeit. Ich fürchte, ich muss dich morgen zur gleichen Tageszeit wieder besuchen. Ich würde auch um die Anwesenheit von Kapitän de Maure bitten. Vielleicht habe ich noch mehr Fragen an dich. Ich sollte jetzt nach Le Francois gehen.";
			link.l1 = "Monseniour Cortney, warten Sie. Vielleicht könnte ich mich Ihnen anschließen? Jacques Barbazon hat seinen Spitznamen nicht dafür verdient, eine liebevolle und sanfte Person zu sein, außerdem ist diese Angelegenheit auch für mich von Interesse.";
			link.l1.go = "Cortny_12";
		break;
		
		case "Cortny_12":
			dialog.text = "Kapitän, ich bin von Ihrer Sorge bewegt, aber es ist ein Nein. Dies ist eine Staatsangelegenheit. Der Schurke kennt seinen Platz und würde es nicht wagen, Hand an den Gesandten der Krone zu legen, sonst ist sein jämmerliches Dorf nicht mehr! Ich entschuldige mich nochmals für die Störung, gnädige Frau. Guten Abend.";
			link.l1 = "Bis morgen Abend, Baronet.";
			link.l1.go = "Cortny_13";
		break;
		
		case "Cortny_13":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_106";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_14":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Sei nicht böse auf sie, Kapitän. Ich kann sehr überzeugend sein. Deine Geschichte ist wirklich beeindruckend. Ich glaube, ich könnte eine Verwendung für dich haben.";
			link.l1 = "Du siehst zufrieden aus, wie lief es in Le Francois?";
			link.l1.go = "Cortny_15";
		break;
		
		case "Cortny_15":
			dialog.text = "Wie ich erwartet hatte, war dieser Baron von dir sanft wie ein Lamm. Er hat mir alles erzählt, was ich hören wollte. Wie ich sagte, ich kann äußerst überzeugend sein.";
			link.l1 = "";
			link.l1.go = "Cortny_16";
		break;
		
		case "Cortny_16":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_112";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_17":
			dialog.text = "Heute bin ich alleine hierher gekommen, hinter dieser Tür sind keine meiner Männer. Was zum Teufel?!";
			link.l1 = "Ich habe ein schlechtes Gefühl dabei. Julianne, stell dich hinter mich, jetzt! Baronet, kämpfen Gesandte der Krone genauso gut, wie sie reden?";
			link.l1.go = "Cortny_18";
		break;
		
		case "Cortny_18":
			DialogExit();
			GoldenGirl_CortnyBandosFight();
		break;
		
		case "Cortny_19":
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Sie wissen wirklich, wie man ein Schwert handhabt, Kapitän! Äh, um ehrlich zu sein, es war kein Spaziergang im Park. Wer zur Hölle waren diese Leute?!";
			link.l1 = "Wir sollten ihre Freunde fragen - Ich höre mehr Schritte. Ich wünschte, es wären die Wachen...";
			link.l1.go = "Cortny_20";
		break;
		
		case "Cortny_20":
			DialogExit();
			GoldenGirl_CortnyMercenFight();
		break;
		
		case "Cortny_21":
			dialog.text = "Unglaublich! Du denkst, der Bastard hat es gewagt, all das zu tun?! Er wird bezahlen, das schwöre ich!";
			link.l1 = "Atme. Barbazon wird sich aus allen Anschuldigungen herauswinden. Er wird dir sagen, dass es nur ein gewöhnlicher Überfall von kleinen Dieben auf einen wohlhabenden Haushalt war. Außerdem ist er ein verdammter Pirat, warum sollte er sich um die Behörden kümmern! Trotzdem bin ich jetzt sicher, dass du etwas wirklich Wertvolles gelernt hast. Ich bitte dich, dieses Wissen mit mir zu teilen.";
			link.l1.go = "Cortny_22";
		break;
		
		case "Cortny_22":
			dialog.text = "Ich kann wirklich nicht nein sagen, oder? Sonst könnte der nächste Versuch ein Erfolg sein? Gut, ich werde so tun, als hätte ich keine Bedrohung in deinem Ton bemerkt. Sagen wir, ich erweise dir einen Gefallen. Jacques Der Gute hat deinem noblen Bastard keine Perlen verkauft. Er hat gekauft. Das ist es.";
			link.l1 = "Also war es de Chievous, der die Regina abgefangen hat? Ein Schurke ist er, aber es ist schwer zu glauben, dass er sich auf gewöhnliche Piraterie herablassen würde.";
			link.l1.go = "Cortny_23";
		break;
		
		case "Cortny_23":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_117";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "Cortny_24":
			dialog.text = "Einen würde kaum die Regina einen regulären Preis eines Piraten nennen, Kapitän. Wir gehen davon aus, dass sie mindestens ein halbes Dutzend schwarze Perlen hatte. Selbst eine einzige schwarze Perle ist unbezahlbar. Ich muss diesen Sir de Chievous unbedingt um jeden Preis treffen.";
			link.l1 = "Ich kann hier von einigem Nutzen sein, Monseniour. Aber lassen Sie uns zuerst etwas klarstellen. Mir schien es egal zu sein, um Madam Botots Halskette, daher sind die Perlen nicht der Grund, warum Sie hier sind. Was hatte die Regina sonst noch an Bord?";
			link.l1.go = "Cortny_25";
		break;
		
		case "Cortny_25":
			dialog.text = "Sehr gut, ich nehme an, ich muss dir mehr erzählen, wenn man die... Umstände bedenkt. Siehst du, die Ladung ist nicht so wichtig wie das Schiff selbst. Die Kurierbrigantine Regina wurde dem Hafen von San Jose, Trinidad, zugewiesen. Ihr Kapitän sammelte Informationen und erledigte einige... ähm, Aufgaben für uns\nDie letzte Aufgabe von ihm war es, die Beute zu transportieren, die unsere Kaperer von den spanischen Perlenoperationen erbeuten konnten. Es hat drei Jahre unserer Bemühungen gekostet, diese Führung zu bekommen. Schwarze Perlen sind sicherlich bedeutend, aber der Verlust der Regina ist schicksalhaft. Es war kein Unfall, jemand, der von ihren Perlen wusste, muss auch von dem Rest gewusst haben.";
			link.l1 = "Prächtig, es geht also doch um Geheimdienstgeschäfte! Hast du Angst, dass das gesamte Spionagenetzwerk, das du aufgebaut hast, in Gefahr ist? Jetzt kann ich das ganze Ausmaß deiner Probleme sehen.";
			link.l1.go = "Cortny_26";
		break;
		
		case "Cortny_26":
			dialog.text = "Haben Sie schon mal von John Thurloe gehört? Er ist der Leiter des Kronengeheimdienstes. Eines Tages werde ich in London sein und ihm persönlich über das Schicksal der Regina berichten. Ich muss herausfinden, wo das Leck ist und... mit der Quelle umgehen. Außerdem gibt es da noch diesen mysteriösen Kapitän Moreno von Ihnen. Wenn die Spanier unser koloniales Spionagenetzwerk aufspüren, werden Jahre harter und mühsamer Arbeit den Bach runtergehen!";
			link.l1 = "Du weißt, all das fängt an Sinn zu machen, wenn man das große Ganze betrachtet. Ich fange an zu denken, dass jemand mit einem spanischen Akzent de Chievous von der Regina und den schwarzen Perlen erzählt hat.";
			link.l1.go = "Cortny_27";
		break;
		
		case "Cortny_27":
			dialog.text = "Wir denken gleich. Es gibt keinen besseren Weg, ein bloßgestelltes Spionagenetzwerk auszunutzen. Ein diplomatischer Zwischenfall mit einem Mann von solch hohem Ansehen... Ein solcher Vorfall kann die Beziehungen zwischen Großbritannien und Frankreich ernsthaft schädigen, alles, was du tun musst, ist die richtigen Fäden zu ziehen und einfach auf einen internationalen Skandal zu warten. Vielleicht wurde uns sogar diese Spur über schwarze Perlen absichtlich zugespielt.";
			link.l1 = "Diese verdammten Kastilier, stimmt's? Also, was machen wir mit de Chievous?";
			link.l1.go = "Cortny_28";
		break;
		
		case "Cortny_28":
			dialog.text = "Ehrlich gesagt, habe ich keine Ahnung. Wenn es eine spanische Provokation ist, wäre es klug, sie einfach zu ignorieren. Aber ich muss herausfinden, wie er von der Regina erfahren hat und wie schlecht es für unser Netzwerk in den spanischen Kolonien aussieht. Ich schulde dir auch mein Leben und ich beabsichtige, es zurückzuzahlen.";
			link.l1 = "Ehrlichkeit für Ehrlichkeit, Baronet. Ich könnte jede Hilfe gebrauchen, die ich bekommen kann. Ich bin schon verzweifelt genug, um darüber nachzudenken, die Marquise zu entführen.";
			link.l1.go = "Cortny_29";
		break;
		
		case "Cortny_29":
			dialog.text = "Du weißt schon, dass dies die Art und Weise ist, wie de Chievous seine Spuren verwischt? Es wird so einfach sein, das ganze Durcheinander auf dich zu schieben, einschließlich des Verschwindens der Regina. Daher schlage ich folgendes vor. Marquise Botot hat mir erzählt, dass de Chievous den Austausch nicht besuchen wird und sicher in Basse-Terre bleiben wird. Entweder hat er realisiert, in welches Durcheinander er sich hineinmanövriert hat, oder er fängt an, etwas zu vermuten. Er wird so vorsichtig sein wie eine Küchenmaus. Deshalb werde ich mit dir nach Dominica gehen.";
			link.l1 = "Aber seine Gefangene ist meine Priorität, ich kann ihr Leben nicht riskieren! Sie ist eine Geisel, die auf einen Austausch wartet!";
			link.l1.go = "Cortny_30";
		break;
		
		case "Cortny_30":
			dialog.text = "Macht euch keine Sorgen - Ich werde Jacques Dille auf die Pelle rücken und einen Haftbefehl für das Schiff von de Chievous besorgen. Ich bezweifle, dass seine Männer sich vollständig über die Situation im Klaren sind, in der sie sich befinden, sonst wären sie mit diesen Perlen vorsichtiger gewesen. Wir werden mit einem Langboot zu ihnen fahren und ihnen den Haftbefehl direkt vorlegen.";
			link.l1 = "Ja, ich erinnere mich an Ihr Geschenk der Überredung, Monseniour, aber es ist ein Risiko. Und ein schweres dazu.";
			link.l1.go = "Cortny_31";
		break;
		
		case "Cortny_31":
			dialog.text = "Sie haben völlig recht, aber Sie müssen es annehmen, wenn Sie meine Hilfe in Anspruch nehmen wollen. Sobald wir in Dominica fertig sind, werde ich nach Basse-Terre gehen und den Gouverneur de Lyon auffordern, Ihren Gegner zu übergeben. Meine Macht erlaubt es. Wir können es nicht zulassen, dass de Chievous davonkommt.";
			link.l1 = "Bist du wirklich dafür bereit, Monseniour? Es könnte einen Krieg auslösen, nicht wahr?";
			link.l1.go = "Cortny_32";
		break;
		
		case "Cortny_32":
			dialog.text = "Ich wette, sie werden es nie zulassen. Es ist definitiv ein No-Go, da wir die Wahrheit bereits kennen. Politik ist eine Hure, Kapitän. Ich verspreche, ich werde de Chievous persönlich in die britischen Verliese einführen. Das klingt nach einer Lösung, die sogar sein Vater als angemessenen Preis betrachten würde.";
			link.l1 = "Ich kann nicht sagen, dass mir dein Plan gefällt, aber ich sehe keinen anderen.";
			link.l1.go = "Cortny_33";
		break;
		
		case "Cortny_33":
			dialog.text = "Ich versichere Ihnen, dass wir es schaffen werden. Ich sollte jetzt gehen, um einen Gouverneur zu sehen und meinen Männern Befehle zu geben. Wenn Sie die Marquise sehen, sagen Sie ihr, dass sie die Perle als Dank für ihre Hilfe bei der Untersuchung behalten darf.";
			link.l1 = "Danke, Baronet. Wir sehen uns auf meinem Schiff, wir werden bald ablegen.";
			link.l1.go = "Cortny_34";
		break;
		
		case "Cortny_34":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "GoldenGirl_CortnyPassenger", 15.0);
		break;
		
		case "Cortny_35":
			PlaySound("VOICE\English\LE\Cortny\Cortny_02.wav");
			dialog.text = "William Cortney, Baronet Cortney, zu Ihren Diensten. Im Namen des Britischen Reiches und mit voller Unterstützung unseres vertrauenswürdigen Verbündeten Frankreich, ist Ihr Schiff hiermit festgenommen. Hier sind die Papiere, bitte stellen Sie sicher, dass Sie sie lesen und Ihren Männern sagen, sie sollen die Hände von den Waffen lassen. Sie sind in Haft, aber noch nicht verhaftet. Wenn Sie nichts Dummes tun, werden Sie im ersten Hafen freigelassen.";
			link.l1 = "Baronet, ich muss meinen... meinen Offizier zurückholen!";
			link.l1.go = "Cortny_36";
		break;
		
		case "Cortny_36":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Machen Sie sich keine Sorgen, Kapitän, ich werde sie zu Ihrem Schiff bringen. Ich bitte Sie, jetzt zum Beiboot zurückzukehren. Ich werde das Kommando über dieses Schiff übernehmen und nach Basse-Terre segeln. Zögern Sie nicht, uns zu verlassen, wenn Sie nicht die Absicht haben, sich persönlich über Ihren Erzfeind lustig zu machen. Ich bitte Sie nur, mir einige Ihrer Männer zu übergeben, um uns zu helfen, nach Guadeloupe zu kommen.";
			link.l1 = "Sehr gut, Monseniour. Ich würde lieber nicht. Schicken Sie ihm meine schlimmsten Grüße. Auf Wiedersehen und nochmals danke!";
			link.l1.go = "Cortny_37";
		break;
		
		case "Cortny_37":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaCortnyFinal");
		break;
		
		case "Cortny_38":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Charles, ich freue mich, dich zu sehen. Ich hatte auf deine Rückkehr gehofft, aber nie wirklich daran geglaubt.";
			link.l1 = "Ebenso, Baronet. Sind Sie gekommen, um der Markgräfin einen Besuch abzustatten? Wo ist sie übrigens?";
			link.l1.go = "Cortny_39";
		break;
		
		case "Cortny_39":
			dialog.text = "Sie verstehen es immer noch nicht, oder? Sie ist geflohen. Auch Angerran de Chievous sendet Ihnen seine aufrichtigen Entschuldigungen. Ich habe es geschafft, ihn davon zu überzeugen, dass Sie nie Teil des Spiels waren, sondern nur ein weiteres Opfer davon. Genau wie er. Der gute Mann hat sich nicht die Mühe gemacht zu schreiben, aber es tut ihm zutiefst leid, wie die Dinge gelaufen sind.";
			link.l1 = "Tut ihm zutiefst leid, nicht wahr?! Worüber reden Sie, Monseniour?";
			link.l1.go = "Cortny_40";
		break;
		
		case "Cortny_40":
			dialog.text = "Du und ich, wir haben das Wichtigste übersehen. Wie hat er von den Perlen erfahren? Wer hat diesen spanischen Kapitän in dieses Haus eingeladen? Wer könnte den Bastard dazu bewegen, einen solchen Preis zu verfolgen?";
			link.l1 = "Bist du ernst? Das kann nicht sein...";
			link.l1.go = "Cortny_41";
		break;
		
		case "Cortny_41":
			dialog.text = "Es kann definitiv. Marquise spielte ihre Rolle perfekt, sie hätte das Ganze fast durchgezogen. Dank einer Untersuchung von uns trat ich jedoch nicht als Dieb und Pirat, sondern als Opfer von Betrug auf, was er ist. Er fand ziemlich schnell heraus, in was sie ihn hineingezogen hatte, doch er hatte keine Beweise und beschloss, auf eigene Faust zu handeln. Du weißt, was danach passiert ist.";
			link.l1 = "Du meinst, dass das alles von der Marquise orchestriert wurde? De Chievous hat es gekauft wie ein sorgloses Kind!";
			link.l1.go = "Cortny_42";
		break;
		
		case "Cortny_42":
			dialog.text = "Genau. Leidenschaft ist eine sehr gefährliche Sache, Charles! Erinnerst du dich an die Nacht, in der du in diesem Haus gespielt hast? Angerran wollte die Beweise, die er brauchte, aus der Marquise herauspressen, indem er ein Patronat über sie erlangte. Ja, er hat betrogen, aber er war verzweifelt nach Jahren hoffnungsloser Leidenschaft, die durch den verheerendsten Verrat beendet wurden! Aber du bist eingeschritten, hast dich als ihr Champion bezeichnet und in dieser Rolle Erfolg gehabt. De Chievous dachte, du und sie seid einer Meinung. Er hat ein Schiff gestohlen, das er dir verloren hat, um dich daran zu hindern, seine Logs zu bekommen. Er hat deinen Offizier benutzt, um sie und dich - seine tödlichen Feinde, wie er glaubte - gegeneinander auszuspielen.";
			link.l1 = "Ich bin sprachlos!";
			link.l1.go = "Cortny_43";
		break;
		
		case "Cortny_43":
			dialog.text = "Jetzt weißt du, wie es ist, Charles! Die Marquise ist klug, atemberaubend schön und nicht weniger gefährlich. Ich weiß nicht, wie lange sie die besten Leute von Neu-Frankreich manipuliert hat. Viele Jahre, würde ich sagen. Wie auch immer, es betrifft dich nicht mehr. Es war mir eine Freude, dich wiederzusehen, aber ich habe noch mehr Zimmer zum Durchsuchen, es ist ein großes Haus. Wir werden wahrscheinlich nichts finden, aber wir müssen es zumindest versuchen\nNoch eine Sache, bevor wir uns trennen. Hier, nimm das. Ein Souvenir zur Erinnerung. Vielleicht wirst du es deiner Freundin schenken, wenn du bereit bist. Du hast sehr viel Glück, weißt du. Besonders im Vergleich zu de Chievous, dem armen Kerl!";
			link.l1 = "Sie haben recht, das tue ich. Lebewohl und Gottes Segen auf Ihrer Suche, Baronet!";
			link.l1.go = "Cortny_44";
		break;
		
		case "Cortny_44":
			DialogExit();
			DoQuestReloadToLocation("FortFrance_Town", "reload", "reload9", "GoldenGirl_SPFinal");
		break;
		
		case "Cortny_45": // фин 3
			PlaySound("VOICE\English\LE\Cortny\Cortny_03.wav");
			dialog.text = "Was für einen schönen Tag haben wir heute, nicht wahr, Kapitän? Ich habe von Ihren Heldentaten gehört, hätte Sie aber nie für einen banalen Piraten gehalten. So eine Unverschämtheit - nach dem, was Sie getan haben, nach St. Jones zu kommen!";
			link.l1 = "Es mag sein, dass ich ein Pirat bin, das ist ganz richtig, Herr, aber sehe ich aus wie ein Idiot? Warum zum Teufel sollte ich hierher kommen, nachdem ich die Mercury geplündert und sie von spanischen Perlen befreit habe?";
			link.l1.go = "Cortny_46";
		break;
		
		case "Cortny_46":
			dialog.text = "Ich gebe zu, das ist der einzige Grund, warum du jetzt dieses Gespräch führst, anstatt an einer Schlinge zu baumeln. Siehst du, es gibt ein kleines Detail, das wir in diesem Fall verborgen haben. Und ich rede nicht von der Perle, die wir bei dir gefunden haben. Es ist der Name der Brigantine.";
			link.l1 = "Bedeutung?";
			link.l1.go = "Cortny_47";
		break;
		
		case "Cortny_47":
			PlaySound("VOICE\English\LE\Cortny\Cortny_04.wav");
			dialog.text = "Eine Kurierbriggantine, die Regina, war seit den letzten zwei Jahren im Hafen von San Jose registriert. Ihr Kapitän sammelte Informationen für uns und erledigte auch... äh... Botengänge aller Art. Offiziell suchen wir nach ihr unter dem Vorwand der verlorenen diplomatischen Post, die sie beförderte. Es ist nicht viel von einem Vorwand, das gebe ich zu. Dennoch könntest du den wahren Namen des Schiffes nicht herausfinden, ohne ordentlich in der Kapitänskajüte zu suchen.";
			link.l1 = "Ich war blind, aber jetzt sehe ich. Bitte hören Sie mir zu, Herr, ich werde es erklären!";
			link.l1.go = "Cortny_48";
		break;
		
		case "Cortny_48":
			dialog.text = "Nun, streng dich mehr an, Kapitän. Dein Leben hängt in der Schwebe.";
			link.l1 = "Ich habe nichts mit dieser Spionagegeschichte zu tun! Auch die Spanier nicht. Euer Netzwerk ist sicher, macht euch keine Sorgen. Allerdings hattet ihr eine undichte Stelle und jemand hat sie ausgenutzt. Und dann geriet ich mit diesem Jemand in Streit. Ich fand Beweise für seine Beteiligung am Merkur-Geschäft und wollte sie verwenden, um ihn zu schlagen.";
			link.l1.go = "Cortny_48_1";
		break;
		
		case "Cortny_48_1":
			dialog.text = "";
			link.l1 = "Gott sei mein Zeuge, ich dachte an diesen Fall als eine gewöhnliche Piraterieaktion, ich könnte nicht einmal denken, dass die Krone eine Verbindung dazu hat! Alles was ich habe, ist diese Perle, aber ich weiß sehr gut, wann und wo ihr mehr finden könnt.";
			link.l1.go = "Cortny_49";
		break;
		
		case "Cortny_49":
			dialog.text = "Hast du jemals von John Thurloe gehört? Er ist der Leiter der Kronenintelligenz. Eines Tages werde ich in London sein und ihm persönlich über das Schicksal der Merkur berichten. Gib mir also den Namen dieses elenden Gegners von dir.";
			link.l1 = "Angerran de Chievous, Graf de Levy Vantadur, der Bastard. Ich nehme an, er hat die Mercury nur für einen Transporter von Kapernbeute gehalten. Er könnte von den Perlen gewusst haben, hatte aber keine Ahnung von der Verbindung des britischen Geheimdienstes.";
			link.l1.go = "Cortny_50";
		break;
		
		case "Cortny_50":
			dialog.text = "Sie enttäuschen nicht, Kapitän, das gebe ich Ihnen! Was für eine Auswahl an Unterhaltung und Feinden! Sehr gut. Welche weiteren Beweise außer der Perle haben Sie?";
			link.l1 = "De Chievous hat eine Fregatte. Ich habe sie mal besessen... nur für eine Nacht, aber ich habe etwas gelernt. Er ist ein äußerst penibler Mann, du wirst alles über seinen Angriff auf die Mercury aus seinem Logbuch erfahren. Ich bin mir ziemlich sicher, dass er noch einen Teil der Beute besitzt. Vielleicht sogar mehr schwarze Perlen, wenn es mehr als eine gab.";
			link.l1.go = "Cortny_51";
		break;
		
		case "Cortny_51":
			dialog.text = "Mehr als eine, darauf kannst du wetten. Wir würden niemals die Regina für eine Ladung gewöhnlicher Perlen riskieren. Ich hoffe, du begreifst, dass ich unbedingt mit Monseniour de Chievous sprechen muss. Mir ist egal, ob es um Perlen geht, aber ich muss mehr über das Leck herausfinden. Meine Vorgesetzten werden mich begraben, wenn ich ihnen nicht ein vollständiges Bild liefern kann.";
			link.l1 = "Ich würde mich freuen, ein Treffen für Sie zu arrangieren, aber wir müssen uns beeilen! In diesem Moment ist die Fregatte von de Chievous auf dem Weg nach Guadeloupe, wo ihr Besitzer derzeit unter dem Schutz des örtlichen Gouverneurs lebt. Ich bin mir sicher, dass er sich bewusst ist, was er getan hat und wird so schnell wie möglich aus der Neuen Welt fliehen.";
			link.l1.go = "Cortny_52";
		break;
		
		case "Cortny_52":
			dialog.text = "Das sind sehr ernste Anschuldigungen von sehr ernsten Leuten, Kapitän. Ist Ihnen klar, was für einen... Scheißsturm das nach hinten losgehen könnte? Ein Brigantenangriff auf ein Schiff, das die Flagge eines Verbündeten hisst? Das kann die Beziehungen zwischen zwei großen Nationen ernsthaft belasten. Ich kann mir kaum vorstellen, wie tief er Ihnen unter die Haut geschlüpft sein muss, um Sie zu so einem großen Risiko zu bringen.";
			link.l1 = "Er hat mir etwas genommen, Milord. Etwas, das mir am meisten bedeutet. Mehr als mein Leben. Ich muss das in Ordnung bringen. Wenn es zum Krieg führt, dann werde ich meinem Land unter seiner Flagge dienen. Trotzdem wird de Chievous bekommen, was er verdient und er ist der einzige, der zu beschuldigen ist!";
			link.l1.go = "Cortny_53";
		break;
		
		case "Cortny_53":
			dialog.text = "Hat Ihnen jemals jemand gesagt, dass Sie ein Mann von großer Gefahr sind, Kapitän? Bereit, einen Krieg auf der halben Welt zu beginnen, um Ihr Ziel zu erreichen? Sehr gut, wir machen es auf Ihre Weise. Ich werde mit Ihnen nach Basse-Terre gehen. Ich kann eine solche Spur nicht loslassen. Ich werde einen Schreiber schicken, um Ihre Beweise aufzuschreiben, während ich mein Schiff vorbereite.";
			link.l1 = "Danke, Herr. Aber wir haben hier keine Zeit zu verlieren, ich warne Sie!";
			link.l1.go = "Cortny_54";
		break;
		
		case "Cortny_54":
			dialog.text = "Kapitän de Maure, wir werden es rechtzeitig schaffen, daran habe ich keinen Zweifel. Aber wenn dieses Abenteuer nicht klappt... verstehst du mich? Ich kann dir nicht einmal ein anständiges Grab versprechen.";
			link.l1 = "Ja, Milord. Ich verstehe Sie vollkommen.";
			link.l1.go = "Cortny_55";
		break;
		
		case "Cortny_55":
			DialogExit();
			npchar.dialog.currentnode = "Cortny_56";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto13", "Baster_Townhall", "goto", "goto4", "GoldenGirl_ReloadToBaster", 10.0);
		break;
		
		case "Cortny_56":
			dialog.text = "Die Würfel sind gefallen, Kapitän. Ich habe ein Treffen mit Angerran de Chievous gefordert. Seine Fregatte wird sofort bei ihrer Ankunft durchsucht. Francois de Lyon hat seine Zweifel, aber die Siegel auf meinen Papieren halten ihn vorerst zurück. Ich bitte Sie, in der Stadt zu bleiben, bis die Situation geklärt ist.";
			link.l1 = "Sicher, Milord, ich verstehe.";
			link.l1.go = "Cortny_57";
		break;
		
		case "Cortny_57":
			dialog.text = "Dann hoffe ich, dass Sie auch das verstehen. Geben Sie Ihr Schwert an die Herren dort rüber und folgen Sie ihnen, damit ich sicher bin, dass Sie Ihr Versprechen einhalten.";
			link.l1 = "Unglaublich... Milord Cortney, meint Ihr das ernst?!";
			link.l1.go = "Cortny_58";
		break;
		
		case "Cortny_58":
			dialog.text = "Todernst. Du bleibst weiterhin einer meiner Hauptverdächtigen und dich unter diesen Umständen gehen zu lassen wäre äußerst dumm von mir. Ich werde mich bei dir auf jede mir passende Weise entschuldigen, wenn und falls deine Worte sich als wahr erweisen.";
			link.l1 = "";
			link.l1.go = "Cortny_59";
		break;
		
		case "Cortny_59":
			DialogExit();
			GoldenGirl_BasterArest();
		break;
		
		case "comendant":
			dialog.text = "Grüß Gott, Herr de Maure. Sollen wir?";
			link.l1 = "Mit Vergnügen, was sind die Regeln? Um ehrlich zu sein, ich war zu sehr mit dem Essen beschäftigt und habe die Bedingungen wahrscheinlich missverstanden.";
			link.l1.go = "comendant_1";
		break;
		
		case "comendant_1":
			dialog.text = "Die Regeln sind einfach. 10 000 Pesos für eine Karte, wir spielen, bis einer von uns aufgibt. Quittungen und Kredite werden nicht akzeptiert.";
			link.l1 = "Funktioniert für mich. Lass es uns tun, Oberst.";
			link.l1.go = "comendant_2";
		break;
		
		case "comendant_2":
			DialogExit();
			npchar.money = 70000;
			pchar.questTemp.GoldenGirl.Game.G1 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "comendant_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
			{
				dialog.text = "Verdammt! Nie wieder! Sehr gut, Monsieur de Maure, viel Glück in der nächsten Runde.";
				link.l1 = "Mit Vergnügen, Oberst. Auf Wiedersehen.";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
				{
					dialog.text = "Sie haben gut gekämpft, aber Dame Fortuna hatte ihren eigenen Plan. Lebewohl, Monsieur de Maure. Danke für das Spiel.";
					link.l1 = "Ja, ich schätze, ich habe mich dabei überschätzt. Auf Wiedersehen, Oberst.";
				}
				else
				{
					dialog.text = "Sie haben sich entschieden, das weitere Spiel abzulehnen und damit Ihre Niederlage zugegeben! Sie haben glorreich gekämpft, aber das Schicksal hat anders entschieden. Auf Wiedersehen, Monsieur de Maure, danke für das Spiel.";
					link.l1 = "Ja, ich schätze, ich habe mich in dieser Hinsicht überschätzt. Lebewohl, Oberst.";
				}
			}
			link.l1.go = "comendant_4";
		break;
		
		case "comendant_4":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// Португалец или Васкез
		case "moreno":
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "Kapitän Charles de Maure, was für eine verdammte Überraschung!";
					link.l1 = "Kapitän. Moreno mein Arsch! Was bringt dich hierher?!";
					link.l1.go = "moreno_1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						pchar.questTemp.GoldenGirl.Vaskez = "true";
						dialog.text = "Kapitän Charles de Maure, mein Vergnügen.";
						link.l1 = "Haben wir uns schon mal getroffen, Monsieur... Moreno?";
						link.l1.go = "moreno_5";
					}
					else // васкез нейтральный
					{
						dialog.text = "Kapitän Charles de Maure, meine Freude.";
						link.l1 = "Haben wir uns schon einmal getroffen, Monsieur... Moreno?";
						link.l1.go = "moreno_4";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "Kapitän Charles de Maure, meine Freude.";
				link.l1 = "Haben wir uns schon einmal getroffen, Monsieur... Moreno?";
				link.l1.go = "moreno_4";
			}
		break;
		
		case "moreno_1":
			dialog.text = "Es ist eine lange Geschichte. Wie immer, Kapitän. Ich kann in deinen Augen sehen, dass du Fragen hast. Mach einfach weiter und tu so, als würdest du einen einfachen Seemann verspotten.";
			link.l1 = "Ja, dieser schicke Anzug steht dir gut, mein einfacher Freund. Ich würde sagen, du weißt, wie man ihn trägt.";
			link.l1.go = "moreno_3";
		break;
		
		case "moreno_3":
			dialog.text = "Nur bei seltenen Gelegenheiten, auf Glück. Heutiger Tag. Lass uns spielen, Kapitän. Die Leute sehen zu, es ist unhöflich, sie warten zu lassen.";
			link.l1 = "Also gut, wir werden später sprechen. Abgemacht... Kapitän Moreno, wenn es Ihnen recht ist.";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_4":
			dialog.text = "Ich kenne Sie ein wenig, aber das ist irrelevant. Verteilen Sie die Karten, Kapitän de Maure, die Leute wollen eine Show.";
			link.l1 = "Seltsam. Besonders Ihr spanischer Akzent zusammen mit den Credits von Madame Botot für Sie. Sehr gut. Meer gegen Meer, lass es uns tun!";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_5":
			dialog.text = "Ich erinnere mich gut an dich. Als du und mein Ex-Kapitän meine Jungs in Le Francois aufgespießt haben. Der Bastard hat bekommen, was er verdient hat, nicht ohne deine Hilfe, wie ich mich erinnere. Aber warte nicht auf meine Dankbarkeit, du hast Franz Garke getötet und ich werde dir das nicht verzeihen.";
			link.l1 = "Der Quartiermeister des Portugiesen? Der Blutige Don, richtig? Diese Nacht wird immer besser und besser. Los geht's!";
			link.l1.go = "moreno_6";
		break;
		
		case "moreno_6":
			DialogExit();
			npchar.money = 110000;
			pchar.questTemp.GoldenGirl.Game.G2 = "true"; // атрибут квестовой игры
			// вызов интерфейса игры
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
            pchar.GenQuest.Cards.iRate     = 10000; // ставка
            pchar.GenQuest.Cards.SitType   = false;
			LaunchCardsGame();
		break;
		
		case "moreno_7":
			if (!CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win") && !CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
			{
				dialog.text = "Du hast dich entschieden, das weitere Spiel abzulehnen und damit deine Niederlage zugegeben! Ich nehme an, Dame Fortune hatte ihr Mitspracherecht. Auf Wiedersehen, Kapitän.";
				link.l1 = "Ebenso, Monsieur Moreno. Danke für das Spiel.";
				link.l1.go = "moreno_8";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Portugal")) // был квест
			{
				if (CheckAttribute(pchar, "questTemp.Portugal.GG1")) // португалец
				{
					dialog.text = "Ich nehme an, Lady Fortune hatte ihr Wort. Auf Wiedersehen, Kapitän, vielleicht treffen wir uns wieder.";
					link.l1 = "Ebenso, Monsieur Moreno. Danke für das Spiel.";
					link.l1.go = "moreno_8";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Portugal.GG2")) // васкез враждебный
					{
						dialog.text = "Ich nehme an, Lady Fortune hatte ihr Mitspracherecht. Auf Wiedersehen, Kapitän, vielleicht treffen wir uns wieder unter anderen Umständen, he-he.";
						link.l1 = "Mit Freude erwarte ich es, Monsieur Moreno.";
						link.l1.go = "moreno_8";
					}
					else // васкез нейтральный
					{
						dialog.text = "Das ist es. Das Schicksal hat entschieden, Kapitän. Lebewohl.";
						link.l1 = "Auf Wiedersehen, Monsieur Moreno.";
						link.l1.go = "moreno_8";
					}
				}
			}
			else  // васкез нейтральный
			{
				dialog.text = "Das ist es. Das Schicksal hat entschieden, Kapitän. Lebewohl.";
				link.l1 = "Auf Wiedersehen, Monsieur Moreno.";
				link.l1.go = "moreno_8";
			}
		break;
		
		case "moreno_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 20.0);
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_19";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "moreno_9":
			dialog.text = "So schön, Sie zu sehen, Monseniour Kapitän de Maure! Um ehrlich zu sein, ich erwartete alles zu sehen, einschließlich einer vollständigen Wache, aber nicht Sie.";
			link.l1 = "Monseniour Moreno, haben Sie einige Probleme mit den örtlichen Beamten? Übrigens, es ist schön, Sie auch zu sehen ha-ha!";
			link.l1.go = "moreno_10";
		break;
		
		case "moreno_10":
			dialog.text = "Ich sage, man kann die Einladung unserer Gastgeberin nicht ablehnen. Zumindest nicht diese Art von Einladung. Komm schon Charles, hör auf mit dieser Komödie. Die Marquise hat dafür gesorgt, dass ich weiß, dass sie meine wahre Identität kennt.";
			link.l1 = "...";
			link.l1.go = "moreno_11";
		break;
		
		case "moreno_11":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_90";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_12":
			dialog.text = "Madame, Sie sind bezaubernd! Dieser neue Freund von Ihnen hat schon einmal versucht, mich zu verraten. Tatsächlich hat es nicht sehr gut geklappt, und tatsächlich hat er meinen bedauernswerten Arsch so oft gerettet, dass ich die Zählung verloren habe. Wie auch immer, jetzt schulde ich ihm etwas, also besteht keine Notwendigkeit für Drohungen, machen Sie sich keine Sorgen.";
			link.l1 = "Das weiß ich zu schätzen, Bartholomäus. Angerran de Chievous hat mich in eine äußerst unangenehme Lage gebracht und ich muss ihn unbedingt stürzen. Ein Leben von... jemandem, der mir sehr lieb ist, hängt davon ab. Vertraue mir, dieses Mal wird mich nichts aufhalten.";
			link.l1.go = "moreno_13";
		break;
		
		case "moreno_13":
			dialog.text = "Genug, Kapitän, wir sind Freunde, richtig? Erinnern Sie sich an das Rennen über die Hälfte des Archipels? Solch eine Sache bedeutet mir viel. Ich werde mein Bestes tun, um Ihnen zu helfen. Haben Sie jemals von dem Merkur gehört?";
			link.l1 = "Was ist das denn? Ein Schiff?";
			link.l1.go = "moreno_14";
		break;
		
		case "moreno_14":
			dialog.text = "Eine britische Brigantine, um genau zu sein. Ihre Aufgabe war es, die Beute von Colonel D'Oyleys Freibeutern zu transportieren, die die spanischen Perlenbetriebe im West Main geplündert haben. Diejenigen, die gelegentlich legendäre schwarze Perlen fischen, haben Sie davon schon einmal gehört? Wenn meine Informationsquelle zuverlässig ist, wurden mehrere solcher Perlen auf der Mercury gelagert. Vor einem Monat legte ich einen Hinterhalt zwischen Martinique und Guadeloupe, um auf diese feinen Herren zu warten. Aber es war vergeblich! Wir verbrachten eine Woche auf See, bis wir es als Misserfolg abhaken mussten.";
			link.l1 = "Also war deine Quelle doch nicht zuverlässig und du hast keinen Preis für dich selbst bekommen. Was hat de Chievous damit zu tun?";
			link.l1.go = "moreno_15";
		break;
		
		case "moreno_15":
			dialog.text = "Hatte die gleichen Gedanken, bis ich herausfand, dass die Mercury nie in Antigua aufgetaucht ist. Stell dir meine Überraschung vor, als sie sie in der Nähe von Curacao sahen und sie unmöglich an mir vorbei bei Martinique kommen konnte. Die Briten sind wütend! Stell dir vor, so einen Preis zu verpassen und alles! Auf jeden Fall wurde ich neugierig und fing an zu ermitteln, über diese besondere Person, die den Spaß für alle ruiniert hat. Solche Beute kann nicht schnell verkauft werden, also ging ich nach Le Francois, um den Bastard zu finden und das zu bekommen, was er mir schuldete.";
			link.l1 = "Deine Geschichte kommt mir bekannt vor. Hast du schon mal das Wort 'Karma' gehört? Du weißt definitiv, wie man sich Ärger auf den Hals holt. Aber ich sehe immer noch nicht, wie das für mich von Nutzen sein kann?";
			link.l1.go = "moreno_16";
		break;
		
		case "moreno_16":
			dialog.text = "Überstürzen Sie es nicht, Kapitän, ich bin dabei, Ihnen den besten Teil meiner Geschichte zu erzählen. Dieser ungepflegte, gut gekleidete Freund von Ihnen - seine Jungs haben eine deutliche Spur von großen Perlen in den örtlichen Läden hinterlassen. Ein Stolz der spanischen Perlenbetriebe, die sie in großer Zahl verschwendeten.";
			link.l1 = "...";
			link.l1.go = "moreno_17";
		break;
		
		case "moreno_17":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_92";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_18":
			dialog.text = "Hast du gehört, Käpt'n?";
			link.l1 = "Denkst du, de Chievous hat gestohlene Perlen von Jacques dem Freundlichen und seinen Jungs gekauft? Ich fürchte, das... ist nicht genug.";
			link.l1.go = "moreno_19";
		break;
		
		case "moreno_19":
			dialog.text = "Das ist es, Kapitän. Er hat nicht gekauft, er hat verkauft! Ich habe mit Barbazon darüber gesprochen und er bestätigte, dass er eine erhebliche Menge an perfekten Perlen von einem seiner Partner gekauft hat. Er hat es danach nach Europa geschickt. Wir haben auch diese schwarze Perle in der Halskette und die Tatsache, dass das Schiff von de Chievous repariert wurde. Arbeiter haben mir erzählt, dass seine Fregatte Löcher von Zwölfpfündern hatte. Wer in aller Welt würde jemals eine Fregatte mit solchen Babys angreifen?";
			link.l1 = "Hört sich nach unserer Brigantine an! Außerdem erinnere ich mich, wie de Chievous damit prahlte, wie schnell seine Fregatte ist. Aber warum diese Wahnsinn? Wir sind im Frieden mit Großbritannien, warum so viel riskieren und für was? Schwarze Perlen sind zwar extrem selten, aber nicht unerreichbar.";
			link.l1.go = "moreno_20";
		break;
		
		case "moreno_20":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_94";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_21":
			dialog.text = "Und da lag er falsch! Die Briten hatten bereits eine offizielle Untersuchung zum Verschwinden der Merkur begonnen, obwohl sie ihr nur ein vermisstes Kurierschiff mit einigen wichtigen Dokumenten an Bord nennen. Jede Spur wird großzügig belohnt, jeder Verantwortliche wird streng bestraft. Das Beste daran ist, dass sie einen besonderen Adligen nach Antigua geschickt haben, der jetzt unermüdlich den Fall durchwühlt. Ich erinnere mich nicht an seinen Namen, so ausgefallen wie sein selbstgefälliges Gesicht, aber ich bin froh, dass er nicht hinter mir her ist!";
			link.l1 = "Na, das ist doch mal etwas! Es scheint, dass sie diese schwarzen Perlen unbedingt wollen. Ich frage mich, wie viele davon sie auf der Merkur hatten und wie all dieses Wissen mir nützlich sein kann?";
			link.l1.go = "moreno_22";
		break;
		
		case "moreno_22":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_96";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_23":
			dialog.text = "Warum, der Abschaum hat es geschafft, auch Sie zu verärgern, Marquise? Winkender Bastard! Ich bin auch bei Ihnen, Kapitän de Maure! Niemand wagt es, die Beute von Bartolomeo dem Portugiesen zu stehlen!";
			link.l1 = "";
			link.l1.go = "moreno_24";
		break;
		
		case "moreno_24":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_98";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_25":
			dialog.text = "Ich brauche einen anständigen Trunk nach all dem Gerede. Marquise, da wir jetzt Freunde sind...";
			link.l1 = "Ich glaube nicht, dass sie in diesem Haus Rum haben, Bartholomäus.";
			link.l1.go = "moreno_26";
		break;
		
		case "moreno_26":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_100";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_27":
			dialog.text = "Ja klar, lenk einfach seine Fregatte in die Aufmerksamkeit dieses britischen Ermittlers! Wenn das unser Plan ist, dann erkenne ich unseren guten alten Kapitän de Maure nicht wieder!";
			link.l1 = "Du wirst lachen, aber das ist der Plan. Ich werde Hilfe von euch beiden brauchen. Dame - du wirst eine Gefangene des Piraten sein, den ich angeheuert habe - Bartholomäus, das ist dein Teil.";
			link.l1.go = "moreno_28";
		break;
		
		case "moreno_28":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_122";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_29":
			dialog.text = "Und über diese Schurkerei von mir auch! Bartolomeo der Portugiese hat nie eine Frau entführt!";
			link.l1 = "Und er wird nicht, aber es wird so aussehen, als ob er für die Männer von de Chievous. Außerdem, es gibt keine Notwendigkeit, ihnen deinen Namen zu sagen. Nimm unsere Dame an Bord und triff dich mit Angerrans Fregatte in der Nähe von Kap Scott Head. Tausche Julianna gegen meinen Offizier und kehre zurück nach Martinique. Dann warte auf Marquise und mich.";
			link.l1.go = "moreno_30";
		break;
		
		case "moreno_30":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_125";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_31":
			dialog.text = "Das war alles sehr faszinierend und du bist ein natürlicher Chevalier, Charles. Aber wie zum Teufel sollen wir sie nach dem Austausch zurückbringen?";
			link.l1 = "Ich werde mich darum kümmern. Wir haben nicht viel Zeit, also teilen wir uns auf. Du und die Marquise werdet nach Dominica gehen, während ich nach St. Jones eilen werde. Ich werde Oberst D'Oyley oder diesen britischen Ermittler finden und ihm sagen, wer für das Verschwinden der Merkur verantwortlich ist.";
			link.l1.go = "moreno_32";
		break;
		
		case "moreno_32":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_130";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_33":
			dialog.text = "Haben Sie sich überlegt, welche Scheißsturm sicherlich auf einen solchen Vorfall folgen wird, Kapitän? Im Moment ist Antigua ein Hornissennest und Sie sagen mir, ich soll einen Stein darauf werfen. Ich erinnere mich, dass Kriege wegen weniger begonnen haben!";
			link.l1 = "Eins nach dem anderen... Ich werde sie um jeden Preis zurückbringen! Lasst de Levy Vantadur das ganze Chaos alleine aufräumen, wenn er so mächtig ist, wie sie sagen! Außerdem wird de Chievous es schwer haben zu erklären, wie Madame Botot an Bord seines Schiffes gelandet ist.";
			link.l1.go = "moreno_34";
		break;
		
		case "moreno_34":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_132";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "moreno_35":
			if(CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
			{
				dialog.text = "Bereit? Auf ein Gebet hin! Marquise, sind Sie bereit, entführt zu werden?";
			}
			else
			{
				dialog.text = "Fertig? Bei einem Gebet! Marquise, wie lange dauert es, bis Sie zusammengepackt haben?";
			}
			link.l1 = "";
			link.l1.go = "moreno_36";
		break;
		
		case "moreno_36":
			DialogExit();
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_134";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "secundant": // fix 22-03-20
			dialog.text = TimeGreeting()+", Monsieur de Maure. Mein Name ist "+GetFullName(npchar)+", und das ist "+GetFullName(characterFromId("Hallo, Freund."))+". Seine Exzellenz hat uns gebeten, Ihr Duell mit Monsieur de Chievous zu bezeugen.";
			link.l1 = "Guten Abend, meine Herren. Ich hoffe, alles wird reibungslos verlaufen und heute Nacht wird niemand sterben. Seid aber trotzdem auf alles vorbereitet. Dieser 'Herr' kann eine Enttäuschung sein.";
			link.l1.go = "secundant_1";
		break;
		
		case "secundant_1":
			dialog.text = "Ihre Unruhe ist grundlos. Nach den festgelegten Bedingungen dieses Duells dürfen Sekundanten unter keinen Umständen eingreifen. Aber trotzdem danke für die Warnung. Ihr Gegner ist eingetroffen. Viel Glück, Kapitän. Seine Exzellenz bat mich, Ihnen zu sagen, dass er für Ihre... Klugheit beten wird.";
			link.l1 = "Ich bin sicher, es wird mir sehr helfen. Wie auch immer, lass uns anfangen.";
			link.l1.go = "secundant_2";
		break;
		
		case "secundant_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto8", "", 5); 
			sld = characterFromId("Angerran");
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			for (i=1; i<=2; i++)
			{
				ref chr = characterFromId("GG_SecundantAG_"+i);
				LAi_SetActorType(chr);
				LAi_ActorFollow(chr, sld, "", 10.0);
			}
		break;
		
		case "sailor":
			dialog.text = "Käpt'n, wir haben ein Problem. Unser Schiff ist... nun, nicht mehr.";
			link.l1 = "Warte, was?! Wie, wer? Eine volle Wacheinheit sollte bei ihr stationiert sein, also wovon zum Teufel redest du?!";
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Nein, Kapitän, nicht das Schiff. Sie glänzt. Die Fregatte, die du gestern gewonnen hast, sie gehört jetzt auch uns, ja? Wir haben nur eine Prisenmannschaft von einem Dutzend dorthin geschickt. Sie sagte, das würde ausreichen.";
			link.l1 = "Hör verdammt nochmal auf und erzähl mir genau, was von Anfang an passiert ist!";
			link.l1.go = "sailor_2";
		break;
		
		case "sailor_2":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Keine Ahnung, Käpt'n. Die Fregatte stach im Morgennebel in See. Die Wache bemerkte ihr Fehlen einige Stunden später, als der Nebel sich verzogen hatte.";
			link.l1 = "Es kann einfach nicht sein! Sie würde mir das niemals antun! Obwohl... Scheiße, wir hatten erst kürzlich einen Streit. Könnte sie...";
			link.l1.go = "sailor_3";
		break;
		
		case "sailor_3":
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "Einer fürchtet, es ist sogar noch schlimmer, Kap. Fischer fanden heute Morgen zwei unserer Jungs von der Prisenbesatzung. Beide tot, Kehlen durchgeschnitten.";
			link.l1 = "Verdammter Albtraum! De Chievous! Er hat sein Schiff gestohlen, während ich mit der Marquise beschäftigt war! Ich hoffe, sie lebt... Wenn sie nur ein Haar verliert, ich...";
			link.l1.go = "sailor_4";
		break;
		
		case "sailor_4":
			dialog.text = "Werden Sie den Jungs die Befehle geben, sich fertig zu machen, Cap? Wir können in zwei Stunden segeln, alle sind den ganzen Morgen über angespannt, Ihr zweiter Kommandant besonders, wir haben es kaum geschafft, ihn davon abzuhalten, ihnen nachzusegeln.";
			link.l1 = "Zu früh dafür. Ich muss... das richtig durchdenken und mit jemandem sprechen. Ja! Bereitet das Schiff vor! Ich möchte, dass jeder bereit ist, wir werden in See stechen, sobald ich zurückkehre.";
			link.l1.go = "sailor_5";
		break;
		
		case "sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			GoldenGirl_GirlPrisoner();
		break;
		
		case "off_brothel":
			dialog.text = "Kapitän de Maure, was ist los? Hat jemand die Dame angegriffen?";
			link.l1 = "Du hättest nicht hierher kommen sollen. Nun, Gott ist mein Zeuge, das wollte ich nicht.";
			link.l1.go = "off_brothel_1";
		break;
		
		case "off_brothel_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("GG_PatrolBrl_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GoldenGirl_BrothelAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Cap_Nayad":
			dialog.text = "Herr, wir hatten fast die Hoffnung verloren, Sie hier zu haben. Ich kann Marquise Botot in Ihrem Beiboot sehen. Ich werde nicht einmal fragen, wie es passiert ist. Ihre Begleiterin wartet auf Sie. Sie ist sicher und unversehrt, nehmen Sie sie und hauen Sie verdammt noch mal hier raus.";
			link.l1 = "Wenn du ihr ein Haar krümmst, werde ich deinen alten Kahn in Stücke reißen!";
			link.l1.go = "Cap_Nayad_1";
		break;
		
		case "Cap_Nayad_1":
			dialog.text = "Was für eine unerwartete Fürsorge. Mach dir keine Sorgen, sie wurde wie eine Gefängniskönigin gehalten. Deine Drohungen bereiten mir keine Sorgen. Übrigens, Chevalier de Chievous lässt grüßen.";
			link.l1 = "Schert ihn und seine Grüße. Wo ist mein... Offizier? Beginnen wir mit dem Austausch.";
			link.l1.go = "Cap_Nayad_2";
		break;
		
		case "Cap_Nayad_2":
			DialogExit();
			DoQuestReloadToLocation("Shore27", "goto", "goto13", "GoldenGirl_DominicaAlarmFinal");
		break;
		
		case "Cap_Nayad_3":
			dialog.text = "Monseniour, wir hatten fast die Hoffnung verloren, Sie hier zu sehen. Ihre Begleiterin wartet auf Sie. Sie ist sicher und unversehrt... warte, wer zum Teufel ist das? Wo ist die Marquise?";
			link.l1 = "";
			link.l1.go = "Cap_Nayad_4";
		break;
		
		case "Cap_Nayad_4":
			DialogExit();
			LAi_SetActorType(npchar);
			chrDisableReloadToLocation = true;
			GoldenGirl_CortnySetOnDeck();
		break;
		
		case "antigua_officer":
			dialog.text = "Ihr Schwert, Herr. Und keine Späße, meine Jungs sind in letzter Zeit etwas nervös. Ihr wollt doch keine Kugel kassieren, oder?";
			link.l1 = "Im Ernst? Gut, nimm es, aber sei vorsichtig, es kostet mehr als deine Kaserne. Ich verlange ein Treffen mit Baronet Cortney, Eure Exzellenz!";
			link.l1.go = "antigua_officer_1";
		break;
		
		case "antigua_officer_1":
			dialog.text = "Mach dir keine Sorgen, ich bin sicher, er wird sich die Zeit nehmen, dich zu besuchen.";
			link.l1 = "Wenn du versuchst, jemandem zu helfen...";
			link.l1.go = "antigua_officer_2";
		break;
		
		case "antigua_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("SentJons_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 1, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			sld = characterFromId("Cortny");
			sld.dialog.currentnode = "Cortny_45"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_CortnyInJail", 10.0);
			bDisableCharacterMenu = true;//лочим F2
		break;
		
		case "baster_officer":
			dialog.text = "Ich mag das auch nicht, Monseniour. Leider hat dieser unverschämte Brite eine solche Autorität, dass sogar Monseniour de Lyon nicht viel dagegen tun kann. Ich bitte um Entschuldigung, Kapitän, geben Sie bitte Ihr Schwert ab.";
			link.l1 = "Ich hoffe doch sehr, dass Monsieur de Chievous nicht dieselbe Zelle mit mir teilen wird. Los geht's, meine Herren, ich bin todmüde. Endlich etwas Schlaf.";
			link.l1.go = "baster_officer_1";
		break;
		
		case "baster_officer_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("Baster_prison", "goto", "goto9", "");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			sld = characterFromId("Cortny");
			sld.lifeday = 0; // Captain Beltrop, убираем Кортни
			sld = characterFromId("Julianna");
			sld.dialog.currentnode = "Julianna_136"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "Baster_prison", "goto", "goto13");
			DoQuestFunctionDelay("GoldenGirl_JuliannaInJail", 7.0);
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Helena")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sTemp = sld.name;
			AddQuestRecord("GoldenGirl", "24");
			AddQuestUserData("GoldenGirl", "sName", sTemp);
		break;
		
		case "statist_1":
			dialog.text = "Ich möchte nicht unhöflich erscheinen, Monsieur, aber ich habe jetzt keine Zeit zum Reden, Sie sehen, was los ist. Ich möchte nichts verpassen!";
			link.l1 = "Wie Sie wünschen, Herr.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1_1":
			dialog.text = "Dieser Abend wird in die Geschichte eingehen, ich spüre es! Die Leute werden darüber von hier bis Versailles diskutieren! Meine Marianne wird entzückt sein und alle Einzelheiten wissen wollen. Bitte, Herr, treten Sie beiseite, Sie versperren mir die Sicht.";
			link.l1 = "Ich gehe schon, Monsieur, genießen Sie die Show und grüßen Sie die unvergessliche Marianne... wer auch immer sie ist.";
			link.l1.go = "statist_1a";
		break;
		
		case "statist_1a":
			DialogExit();
			npchar.dialog.currentnode = "statist_1_1"; 
		break;
		
		case "statist_2":
			dialog.text = "Hah! Also, hier ist Monsieur de Maure! Entschuldigen Sie... Kapitän Charles de Maure! Begleiten Sie mich bitte, hier ist eine prächtige Auswahl an Weinen aus der guten Alten Welt. Mit was möchten Sie den Abend beginnen: Es gibt eine Neuheit - Cabernet Sauvignon von den Ufern unserer geliebten Gironde, oder unvergänglicher Klassiker - italienischer Sangiovese?";
			link.l1 = "Danke, Monsieur, ich werde mit Ihnen trinken, aber ein wenig später.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2_1":
			dialog.text = "Oh, Kapitän de Maure! Möchten Sie noch etwas mehr Wein... hick? Schauen Sie, was uns gerade serviert wurde - Syrah aus dem Jahr 1643, direkt von den nördlichen Hügeln des Rhonetals. Das ist, verdammt noch mal, eine echte Perle! Und das Jahr war in jeder Hinsicht ausgezeichnet, sage ich Ihnen... eine Niederlage der Spanier am Kap Gat ist es wert! Übrigens ... warum ist denn hier so ein Aufruhr, wissen Sie das? Fühlt sich jemand unwohl? Nun - egal, Prost...";
			link.l1 = "Nun, zumindest zollt jemand den Leckereien Tribut. Au Revoir, Monsieur.";
			link.l1.go = "statist_2a";
		break;
		
		case "statist_2a":
			DialogExit();
			npchar.dialog.currentnode = "statist_2_1"; 
		break;
		
		case "statist_3":
			dialog.text = "Oh, Kapitän Charles de Maure, ich habe von Ihnen gehört, wie jeder andere in dieser Stadt! Lassen Sie mich mich vorstellen - "+GetFullName(npchar)+", Sie zu treffen, ist eine große Ehre, glauben Sie mir! Stehen Sie wirklich auf gutem Fuß mit unserem Gouverneur? Können Sie uns vorstellen? Ich möchte ihm meinen tiefsten Respekt ausdrücken und...";
			link.l1 = "Vielleicht später. Einen schönen Abend noch, Monsieur.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3_1":
			dialog.text = "Herr de Maure, haben Sie das gesehen?! Unser geschätzter Gouverneur und Monsieur de Chievous selbst - ich dachte, sie würden sich gleich hier umbringen! Grandios! Marquise Botot hat sich heute selbst übertroffen - es ist alles so verdammt aufregend! Ich warte ungeduldig auf die Fortsetzung. Übrigens, vielleicht ist jetzt der richtige Moment? Sie versprachen, mich vorzustellen... ";
			link.l1 = "Ich erinnere mich nicht, dass ich etwas versprochen habe. Es tut mir leid, aber ich muss gehen.";
			link.l1.go = "statist_3a";
		break;
		
		case "statist_3a":
			DialogExit();
			npchar.dialog.currentnode = "statist_3_1"; 
		break;
		
		case "statist_4":
			dialog.text = "Herr de Maure, Sie haben endlich den Salon der brillanten Madame Botot erreicht! Sie hat schon ein paar Mal gemunkelt, dass sie Sie sehen wollte. Haben Sie es geschafft, ihre 'Schülerinnen' zu bewerten? Ja, Sterne wie die Marquise sind für gewöhnliche Sterbliche wie Sie und mich nicht bestimmt. Aber glauben Sie mir: diese Damen sind wahre Kunstwerke. Vielleicht weniger erstaunlich, aber trotzdem - wie Michelangelo und sagen wir, Tizian.";
			link.l1 = "Eine interessante Vergleichung, monsieur. Nun, ich lasse Sie, um die Nacht zu genießen....";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4_1":
			dialog.text = "Nein, es ist immer lustig hier, aber jetzt riecht die Luft eindeutig nach einem luxuriösen Skandal, fühlst du? Lady Jacqueline wartet oben auf mich, aber ich kann mich immer noch nicht von den Spieltischen losreißen! Seine Lordschaft und Monsieur de Chievous sind würdige Gegner und äußerst entschlossen. Es scheint, dass die Wetten heute nicht nur zu den Sternen fliegen werden, sondern das Firmament direkt zu den Teufeln durchbrechen werden!";
			link.l1 = "Die Teufel sind unten, Monsieur. Es müssen Engel hinter dem Firmament des Himmels sein.";
			link.l1.go = "statist_4a";
		break;
		
		case "statist_4a":
			DialogExit();
			npchar.dialog.currentnode = "statist_4_1"; 
		break;
		
		case "statist_5":
			dialog.text = "Nun, zumindest eine angenehme Begegnung! Wir haben uns bereits getroffen, Kapitän de Maure, aber Sie erinnern sich kaum. "+GetFullName(npchar)+"- Ich war der Kapitän der sechsten Infanteriekompanie der Garnison, kämpfte mit euch auf unseren Straßen gegen die Spanier. Zugegeben, ich bekam eine Kugel ins Knie und den größten Teil der Schlacht bewunderte ich, wie dieses Bordell brannte, während ich in einem Graben lag. Jetzt bin ich wieder ein Zivilist und bewundere es erneut, aber jetzt von innen.";
			link.l1 = "Freut mich, Sie zu treffen, Monsieur. Dieser Tag war wirklich heiß, aber zugegeben, seit diesem Tag ist dieser Ort deutlich schöner geworden!";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5_1":
			dialog.text = "Und wie gefällt Ihnen die Atmosphäre hier, Kapitän? Es scheint, dass diese weltlichen Tölpel beschlossen haben, eine verdammt große Sauerei zu machen! Interessanterweise, kann der Gouverneursstuhl wie eine Wette in Karten gespielt werden? Merken Sie mein Wort - es wird mit Stahl enden. Schade, mit meinem Knie sind solche Unterhaltungen nicht mehr für mich. Allerdings habe ich irgendwo Jacqueline gesehen - ihr Gentleman ist ernsthaft begeistert von dem, was passiert... Ich denke, ich werde mein Glück versuchen, während hier noch alles ruhig ist.";
			link.l1 = "Gute Entscheidung, ich wünsche Ihnen Erfolg, Monsieur. Und ich muss zurück zu... Wallies.";
			link.l1.go = "statist_5a";
		break;
		
		case "statist_5a":
			DialogExit();
			npchar.dialog.currentnode = "statist_5_1"; 
		break;
	}
} 
