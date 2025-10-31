// полковник Фокс - бравый командир морской пехоты 'морские лисы'.
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
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyReward"))
			{
				dialog.text = "Was wünschen Sie, Herr? Oh... mein... warten Sie! Sie sind der französische Kapitän, der meine Tochter aus den schmutzigen Händen von Levasseurs Dienern gerettet hat! ";
				link.l1 = "Ich sehe, dass Catherine Ihnen bereits von mir erzählt hat...";
				link.l1.go = "terrapin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Usurer") && !CheckAttribute(npchar, "quest.utensil"))
			{
				dialog.text = "Was wünschen Sie, Herr?";
				link.l1 = "Guten Tag, Oberst. Ich bin wegen einer 'ungewöhnlichen' Angelegenheit zu Ihnen gekommen. Könnten Sie etwas Zeit für mich erübrigen?";
				link.l1.go = "guardoftruth";
				break;
			}
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "eng_reward")
			{
				dialog.text = "Wenn ich mich nicht irre, sind Sie "+GetSexPhrase("der besagte Kapitän","die besagte Kapitänin")+", der meinen Leuten auf Sint Maarten bei ihrer Mission geholfen hat? "+TimeGreeting()+"!";
				link.l1 = TimeGreeting()+", Oberst. Ja, das wäre ich.";
				link.l1.go = "FMQN";
				break;
			}
			dialog.text = "Was wollen Sie, Herr?";
			link.l1 = "Nichts, Oberst. Ich nehme Abschied.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guardoftruth":
			dialog.text = "So sprich es schon aus, da Sie schon so weit gekommen sind...";
			link.l1 = "Sie haben kürzlich eine Schoner unter dem Kommando von Rollie dem Kapitän, einem holländischen Piraten, geentert und den Kapitän hierher, nach St. John's, gebracht.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Kapitän? Oh, bringt mich nicht zum Lachen! Dieser kriminelle Abschaum hat kein Recht, mit diesem ehrenhaften Rang bezeichnet zu werden. Ich habe einen verfluchten Piraten gefangen genommen, den Kopf einer Wolfsmeute, der englische Händler und Kaufleute ausgeraubt und ermordet hat. Und ich habe dafür gesorgt, dass er und seine Degenerierten bekommen haben, was sie verdienen - ganz St. John's hat ihre Hinrichtung am Pier beobachtet!";
			link.l1 = "Ich befürchte, ich werde diesen Schurken dann nicht befragen können... Oberst, könnten Sie mir vielleicht helfen? Der Pirat hatte etwas in seinem Besitz, das ihm nicht gehörte - ein goldenes Weihrauchfass. Haben Sie etwas bei ihm gefunden, das so aussieht?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Nein, wir haben ihn durchsucht und dieser Schuft hatte keine Besitztümer, außerdem wurden sie sicherlich von ehrlichen Händlern genommen! Und zu Ihrer Sorge... hmm nein, wir haben es nicht gefunden. Und was könnte ein Weihrauchfass auf einem Piratenschiff machen? Glauben Sie wirklich, dass dort ein Priester unter ihnen war?";
			link.l1 = "Nein, das tue ich nicht. Rollie der Kapitän hat es von dem Geldverleoher in Willemstad gekauft, der es von einem anderen Piraten gekauft hatte. Das Räuchergefäß ist fein und teuer, und ich versuche, es seinen rechtmäßigen Besitzern zurückzugeben. Ich vermute, dass Rollie es wie eine Elster im Auge hatte.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "In Wahrheit hatte Rollie leere Laderäume und ein paar Kisten mit Dublonen, als wir sein Schiff enterten und eroberten. Nichts als Müll. Keine Wertsachen, kein goldenes Weihrauchfass. Ich würde mich an ein solch unpassenden Gegenstand für einen Piraten erinnern.\nIch vermute, dass dieser verdammte Pirat seine Ersparnisse in Dominica versteckt hat. Wir sind sogar dort gelandet und haben die Gegend durchsucht, aber nichts gefunden. Aber wir blieben nicht auf der Insel oder erforschten ihre Tiefen wegen der großen Anzahl von Wilden dort.";
			link.l1 = "Hm... Der Pirat könnte das Räuchergefäß zusammen mit dem Rest seiner gestohlenen Sachen irgendwo auf Dominica versteckt haben... Schade. Haben Sie den Piraten vor der Hinrichtung verhört?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Ich tat es... und er fing einfach an, mir ins Gesicht zu lachen. Aber seine Verstecke waren mir eigentlich egal. Rollie der Kapitän wurde gehängt und das ist das Wichtigste.";
			link.l1 = "Ich verstehe. Danke für Ihre Geschichte und Ihre Zeit, Oberst. Lebewohl...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("GuardOT_Fox_DlgExit");
		break;
		
		case "terrapin":
			dialog.text = "Erneut guten Tag, Kapitän! Ihre ehrenhafte und mutige Tat war kaum von einem Franzosen zu erwarten. Ich schulde Ihnen meine Dankbarkeit, als Soldat und als Vater. Es gibt nichts Wertvolleres für mich in dieser ganzen Welt als meine Tochter...";
			link.l1 = "Ich freue mich, dass ich helfen konnte, und ich hoffe, dass Sie mit der Zeit ein Herz für die Franzosen gewinnen werden.";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Die Anwesenheit eines so ehrenwerten und großzügigen Herren wie Ihnen, der sein Leben für ein unbekanntes englisches Mädchen riskiert hat, wird eine wesentliche Verbesserung meiner Beziehung zu Ihren Landsleuten bewirken!";
			link.l1 = "Es gibt ehrliche Leute unter den Ratten jeder Nation, Oberst...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Und das haben Sie bewiesen! Eine Belohnung wartet auf Sie, Kapitän. Natürlich ist das Leben meiner Tochter unbezahlbar, aber Jonathan Fox zahlt immer seine Schulden, das schwöre ich! Sie sind ein echter Soldat, daher ist mein Geschenk für Sie ein Soldatengeschenk. Hier, seht mal. \nDas ist eine Donnerbüchse, eine hervorragende Marine-Muskete, sie kann mit einer Hand benutzt werden. Sie können sie mit speziellen Pfeilen laden, die selbst die haltbarsten Kürasse durchdringen. Sie schießt auch Schrot und ihre solide Konstruktion erlaubt es Ihnen, sie mit Ladungen von Nägeln zu laden. Hier, nehmt sie, sie gehört jetzt Ihnen.";
			link.l1 = "Ein solch ausgezeichnetes Geschenk für einen Soldaten, ich danke Ihnen, Oberst!";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			Log_Info("Sie haben eine Donnerbüchse erhalten");
			Log_Info("Sie haben 10 Pfeile erhalten");
			Log_Info("Sie haben 10 Ladungen Nägel erhalten");
			Log_Info("Sie haben eine Anleitung zur Erstellung der Harpunenpfeile erhalten");
			Log_Info("Sie haben eine Anleitung für die Herstellung einer Ladung von Nägeln erhalten");
			GiveItem2Character(pchar, "pistol8");
			TakeNItems(pchar, "harpoon", 10);
			TakeNItems(pchar, "GunEchin", 10);
			GiveItem2Character(pchar, "recipe_harpoon"); 
			GiveItem2Character(pchar, "recipe_GunEchin"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "Ich übergebe Ihnen auch eine kleine Menge Munition und Anleitungen zur Herstellung. Es wäre eine Schande, wenn Sie ihre Kraft nicht voll ausschöpfen würden!";
			link.l1 = "Danke, Oberst. Ich werde ein solches Geschenk nicht ablehnen, aber ich möchte, dass Sie wissen, dass ich Catherine nicht für eine Belohnung gerettet habe. Ich hätte das ungeschützte Mädchen einfach nicht in Gefahr bringen können.";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "Ich weiß das, Kapitän. Es ehrt Sie doppelt. Catherine war wirklich von Ihnen entzückt und es ist keine leichte Aufgabe, einen positiven Eindruck auf sie zu machen. Nochmals, wir schulden Ihnen unseren Dank für ihre Rettung. Ich schulde Ihnen!";
			link.l1 = "Nun, ich danke Ihnen für das Geschenk, Oberst. Richten Sie Catherine meine besten Grüße aus, und ich wünsche, dass sie das nächste Mal auf ihren Vater hören würde.";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "Das werde ich, Kapitän! Lebewohl und sichere Reisen!";
			link.l1 = "Auf Wiedersehen, Oberst.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Terrapin_KathyReward");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
			ChangeCharacterNationReputation(pchar, ENGLAND, 20);
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Ich habe den Bericht gelesen. Ihre Taten werden hoch geschätzt, daher müssen Sie belohnt werden. 30.000 Pesos für Expeditionsdienste und Waffen für Heldentum im Soldatentum. Nehmen Sie dieses Schwert und diese Arkebuse. Sie gehören jetzt ganz Ihnen!";
			link.l1 = "Danke, Herr.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Mit Vergnügen, Kapitän. Sie werden auch mit Liebe und Respekt der britischen Kolonien, Behörden und meiner persönlichen Anerkennung belohnt. Danke, dass Sie meine Männer nicht im Stich gelassen und ihnen bei ihrer Mission geholfen haben!";
			link.l1 = "Mit Vergnügen, Oberst...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "Nun, bitte entschuldigen Sie mich - ich habe andere Aufgaben zu erledigen. Gott segne Sie, Kapitän "+pchar.lastname+".";
			link.l1 = "Auf Wiedersehen, "+GetAddress_Form(NPChar)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
