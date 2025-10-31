// НПС по квесту Суп из черепахи
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Was brauchen Sie?";
			link.l1 = "Nein, nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// денщик Фокса - Бенджамин Джонс
		case "BenjaminJons":
			if (CheckAttribute(PChar, "questTemp.Terrapin.Benjamin") && pchar.questTemp.Terrapin == "baster")
			{
				dialog.text = "Der Herr Oberst ist momentan auf einem militärischen Manöver im Feld. Was wollen Sie von ihm, Kapitän?";
				link.l1 = "Diesmal, Ben, bist du derjenige, den ich brauche. Ich habe schlechte Nachrichten über deine Schwester Molly. Dieses schöne Mädchen ist anscheinend in Schwierigkeiten geraten. Sie wurde von Piraten aus Tortuga gefangen genommen. Sie braucht Hilfe und hat darum gebeten, dich zu warnen. Der Mann, der es auf sich genommen hat, die Nachricht zu überbringen, wurde getötet, aber vor seinem Tod konnte er mir von deiner Schwester erzählen.";
				link.l1.go = "sister";
				break;
			}
			sld = characterFromId("Fox");
			if (sld.location == pchar.location)
			{
				dialog.text = "Wenn du auf dem Weg zu Oberst Fox bist, dann dreh dich um 360 Grad und geh weg. Er nimmt keine Gäste auf.";
				link.l1 = "Sehr gut dann.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Der Oberst ist nicht hier. Kommen Sie später vorbei.";
				link.l1 = "In Ordnung...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "BenjaminJons";
		break;
		
		case "sister":
			dialog.text = "Ha! Sie sind der allererste Mann, der meine Schwester jemals 'schön' genannt hat. Gott hat ihr den Körper eines Grenadiers und das Horn von Jericho anstelle einer Stimme gegeben. Unsere Molly kann sich selbst verteidigen\nAber die Kreativität unseres Herrn hörte nicht einfach bei allem unter ihrem Kinn auf. Nein nein, das Feinste, was Er tat, war das behaarte, pockennarbige Gesicht unseres verstorbenen Vaters über ihre Brüste zu kleben. Und ich muss sagen, mein Herr, das Gesicht meines alten Mannes ließ Pferde in Ohnmacht fallen.";
			link.l1 = "Ich sehe, du bist nicht besonders verärgert...";
			link.l1.go = "sister_1";
		break;
		
		case "sister_1":
			dialog.text = "Und warum sollte sie in Tortuga auftauchen? Molly ist eine Dienerin von Catherine Fox, der Tochter unseres tapferen Kolonels. Catherine kam aus Europa, um ihrem Vater zu seinem Geburtstag einen Besuch abzustatten. Aber das Geschwader, mit dem ihr Schiff segelte, hat sich verspätet\nWenn du die echte Molly Jones und ihre Herrin sehen willst, die übrigens sehr schön ist, komm in einem Monat hierher. Nicht einen Tag früher.";
			link.l1 = "Es stellt sich heraus, dass deine Schwester Molly Jones Frau Fox gedient hat und sich im Moment auf der anderen Seite des Atlantiks befindet?";
			link.l1.go = "sister_2";
		break;
		
		case "sister_2":
			dialog.text = "Genau so! Der letzte Kurier informierte uns, dass eine von Lord Protector Cromwell persönlich entsandte Marineeskadron vor nur einem Monat London verlassen sollte. Die Brigg 'Albatros' mit Catherine an Bord sollte sie begleiten. Ob das wirklich so ist, erfahren wir von der nächsten Postpacketboot. Obwohl die Schiffe noch nicht angekommen sind und der Oberst der 'Albatros' streng verboten hat, allein zu segeln\nWusstest du, dass seine geliebte Frau bei einem Angriff französischer Korsaren gestorben ist? Es war nicht leicht für den Oberst und er fürchtet immer noch die Gefahren der hohen See... Also kann ich dir bei Molly Jones, Kapitän, nicht helfen! Es gibt viele Kolonistinnen namens Molly! Außerdem ist es in Großbritannien so gut wie keinen Nachnamen zu haben, wenn man Jones heißt!\nJeder Seehund in Antigua kennt mich und meinen Kommandanten. Nicht überrascht, dass irgendein armes Mädchen, das in Schwierigkeiten geraten ist, meine Hilfe will. Ich würde gerne, aber ich habe kein Geld für ein Lösegeld. Der Oberst schuldet mir drei Monatsgehälter, mein Gehalt kommt zusammen mit dem der anderen mit der 'Albatros'.";
			link.l1 = "Anscheinend liege ich dann falsch. Aber trotzdem danke für die Klarstellung.";
			link.l1.go = "sister_3";
		break;
		
		case "sister_3":
			dialog.text = "Überhaupt nicht, Kapitän.";
			link.l1 = "...";
			link.l1.go = "sister_4";
		break;
		
		case "sister_4":
			DialogExit();
			AddQuestRecord("Terrapin", "3");
			pchar.questTemp.Terrapin.Catherina = "take"; // возможен вариант с Кати
			DeleteAttribute(pchar, "questTemp.Terrapin.Benjamin");
		break;
		
		// Робер Мартэн
		case "Rober":
			PlaySound("Voice\English\sharlie\Rober Marten-01.wav");
			dialog.text = "Was willst du?! Ich will nicht reden.";
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "rober")
			{
				link.l1 = "Ich habe ein Geschäft für dich, Kapitän. Ich sehe, dass du nicht in heiterer Stimmung bist und vielleicht wird mein Vorschlag dich ein wenig aufheitern.";
				link.l1.go = "rober_1";
			}
			else
			{
				link.l1 = "Beruhige dich, trink etwas Rum. Mein Fehler, Kumpel. Es tut mir leid.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rober";
		break;
		
		case "rober_1":
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Terrapin_LateBaster.over = "yes"; //снять таймер
			dialog.text = "Der Klang davon ist ziemlich ansprechend! Und dein Gesicht sieht aus, als hätte ich es schon irgendwo gesehen... Ich kann mich einfach nicht erinnern, wo ich dich gesehen habe. Leg es mir dar!";
			link.l1 = "Ich weiß von deinem Geschäft mit Thibaut... Entspann dich, Kumpel! Du brauchst keine Angst vor mir zu haben. Ich habe ein Angebot für dich.";
			link.l1.go = "rober_2";
		break;
		
		case "rober_2":
			dialog.text = "Verdammt zur Hölle! Fick dieses betrunkene Schwein!... Ich konnte nicht...";
			link.l1 = "Das hast du richtig erkannt. Dein Seemann hatte eine große Klappe, aber seine Gerüchte sind nicht über mich hinausgekommen. Und diese Gerüchte werden nicht weiterkommen, da du es bist, der sich darum gekümmert hat, nicht wahr?";
			link.l1.go = "rober_3";
		break;
		
		case "rober_3":
			dialog.text = "Verdammt! Ich erkenne dich jetzt! Du bist der Mann, der aus Oberst Doiley einen Schlamassel gemacht und seine ganze Insel genommen hat! Du warst in große Geschäfte mit der Niederländischen Westindien-Kompanie verwickelt, du reibst dir die Ellbogen mit einem West Main Baron... Dein Name ist... "+GetFullName(pchar)+", richtig?";
			link.l1 = "Sie besitzen einige genaue Informationen. Ja, das bin ich. Könnten Sie sich aber für eine Sekunde beruhigen, Robert?";
			link.l1.go = "rober_4";
		break;
		
		case "rober_4":
			PlaySound("Voice\English\sharlie\Rober Marten-02.wav");
			dialog.text = "Argh! Nun, wie soll ich mich beruhigen, wenn einer der bekanntesten Seehunde des Archipels sich für mich interessiert hat und nicht nur das, er hat auch von meinem Geschäft erfahren! Was zum Teufel hat mich dazu gebracht, diese Brigantine anzugreifen! Was willst du von mir?";
			link.l1 = "Halt den Mund und hör mir zu. Es scheint mir, dass wir beide Levasseurs Kopf auf dem Silbertablett wollen. Dieser prahlerische Aufschneider hat sich zu weit aus dem Fenster gelehnt und einige ernste Leute verärgert. Ich beabsichtige, das Machtgleichgewicht auf der Insel zu ändern und de Poincy an seinen Platz zu setzen, aber ich möchte kein überflüssiges Blut von Männern aus meiner Heimat vergießen, besonders wegen irgendeines schmutzigen Diebes. Du kannst mir helfen. Und ich kann dir und Thibaut helfen, eure Privilegien zu behalten.";
			link.l1.go = "rober_5";
		break;
		
		case "rober_5":
			dialog.text = "Warte, warte! Ich kann meinen Ohren nicht trauen! Fortuna lächelt mir heute zu. Du hast recht, wir teilen Ziele. Mit dir könnte es viel interessanter werden... Thibaut ist ein guter Fechter, aber er hat nicht den Mumm, seinem Onkel die Kehle durchzuschneiden... Aber ein schlauer Hai wie du könnte es schaffen. Dein Ruhm ist bekannt\nIch brauche deine Garantien nicht, aber ich werde dir im Austausch für das Mädchen helfen. Ich brauche sie als meine Geisel, bis ich meine Geschäfte in der Karibik abgeschlossen habe. Bald werden mich englische Fregatten jagen. Was zum Teufel hat mich dazu gebracht, diese Brigg anzugreifen! Sie sah aus wie eine so leichte Beute, getrennt von der Staffel...";
			link.l1 = "Was war so besonders an ihr? Das Mädchen, das du vor Levasseur versteckt hast?";
			link.l1.go = "rober_6";
		break;
		
		case "rober_6":
			dialog.text = "Ja. Du musst Thibaut überzeugen, sich von dem Mädchen zu trennen. Ich bat ihn, auf sie aufzupassen, während ich herausfand, wer zum Teufel sie war, aber diese 'Miss Jones' oder wie auch immer sie heißt, hat ihm völlig den Kopf verdreht und jetzt versteckt Henry sie sogar vor mir! Bring diese verzaubernde Sirene zu mir und ich werde ein Treffen mit Levasseur außerhalb der Stadt für dich organisieren. Zu diesem Zeitpunkt hast du die Möglichkeit, ihn zu überfallen. Ich warte am Fisheye Beach auf dich.";
			link.l1 = "Abgemacht. Jetzt sag mir, wie ich Thibaut fangen kann.";
			link.l1.go = "rober_7";
		break;
		
		case "rober_7":
			dialog.text = "Die Leute in der Taverne können dir den Weg zu seinem Haus zeigen. Henri ist ziemlich bekannt. Drohe ihm mit Enthüllung und lass ihn das Mädchen zu mir bringen. Noch am selben Tag werde ich Levasseur wissen lassen, dass sein Neffe eine seltene Schönheit im Stadtverlies versteckt\nMein Bote wird dich in der Taverne finden. Nachdem er Henri nicht finden kann, wird der Gouverneur mit einer kleinen Truppe zum Verlies gehen und du wirst eine schöne Gelegenheit haben, mit ihm zu plaudern.";
			link.l1 = "Wohin soll ich das Mädchen bringen?";
			link.l1.go = "rober_8";
		break;
		
		case "rober_8":
			dialog.text = "Sag ihm, er soll sie selbst zum Strand bringen. Ich werde ihm dabei noch ein oder zwei Dinge sagen...";
			link.l1 = "In Ordnung. Betrachten Sie es als abgemacht. Wir sehen uns auf Tortuga!";
			link.l1.go = "rober_9";
		break;
		
		case "rober_9":
			dialog.text = "Wenn alles nach Plan läuft, werden wir uns nie wiedersehen. Das hoffe ich zumindest. Lebewohl!";
			link.l1 = "...";
			link.l1.go = "rober_10";
		break;
		
		case "rober_10":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Baster_tavern", "goto", "goto2");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina")) AddQuestRecord("Terrapin", "6");
			else AddQuestRecord("Terrapin", "5");
			pchar.questTemp.Terrapin = "tortuga";
			// создаем Тибо
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Tibo", "Tibo", "man", "man", 35, FRANCE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_18", "pistol4", "bullet", 250);
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.name = "Henry";
			sld.lastname = "Thibaut";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "tibo";
			sld.greeting = "Tibo";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			TakeNItems(sld, "potion2", 8);
			TakeNItems(sld, "potion3", 5);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
		
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 40, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 20, false); // таймер
			SetFunctionLocationCondition("Tonzag_AtTortuga", "Tortuga_town", false);
		break;
		
		case "rober_abordage":
			dialog.text = "Argh! Ich habe es nicht kommen sehen... Du bist für meine Seele gekommen, nicht wahr, Kumpel? Ich habe alles wie vereinbart gemacht! Was zur Hölle?!";
			link.l1 = "Du hast ein Urteil über dich, Robert. Das Urteil wurde mir zur Vollstreckung gegeben. Also erfülle ich meine Aufgabe.";
			link.l1.go = "rober_abordage_1";
		break;
		
		case "rober_abordage_1":
			dialog.text = "Du Teufel! Das ist unmöglich! Er konnte nicht so schnell alles herausgefunden haben! Und wie hat er es überhaupt herausgefunden?!";
			link.l1 = "Du meinst Fox? Nein. Er hat mich nicht geschickt. Der Oberst weiß immer noch nicht einmal, dass du seine Tochter niedergeschlagen hast. Dein alter Kumpel Henry Thibaut ist derjenige, der dich tot sehen will. Er hat mich angeheuert.";
			link.l1.go = "rober_abordage_2";
		break;
		
		case "rober_abordage_2":
			dialog.text = "Dieser verdammte Knabenschänder! Ich hätte ihn den Krabben zum Fraß vorwerfen sollen, als er noch auf der 'Voltigeur' war... Wie viel hat dir dieses Schwein versprochen?";
			link.l1 = "Es ist nicht jeden Tag, dass ein Mann den Preis auf seinem Kopf erfährt, oder Robert? Thibaut hat dich auf eine Viertelmillion geschätzt, aber ich habe ihn überzeugt, dass du mehr kostest. Du bist dreihunderttausend Silberpesos wert, mein Freund. Bist du nicht froh?";
			link.l1.go = "rober_abordage_3";
		break;
		
		case "rober_abordage_3":
			dialog.text = "Warte mal... Lass uns einen Deal machen! Ich zahle dir mehr!";
			link.l1 = "Mit welchem Geld, Robert? Ich bin absolut sicher, dass du lügst. Du hast nicht so viel Geld, wie Henry mir versprochen hat. Und das ist sowieso nicht das Wichtigste. Wenn es nicht eine Tatsache gäbe, hätte ich sein Angebot abgelehnt, dich zu jagen und deine schmutzigen Geschäfte mit Thibaut zu beenden.";
			link.l1.go = "rober_abordage_4";
		break;
		
		case "rober_abordage_4":
			dialog.text = "Welche Tatsache ist das?";
			link.l1 = "Du hast Catherine Fox getötet. Die einzige Schuld dieses armen Mädchens war es, als Tochter von Colonel Fox geboren zu sein. Ich hasse verachtenswerte Feiglinge wie dich, die wehrlose Frauen töten! Ich mache keinen Deal mit dir. Ich werde es nicht einmal in Betracht ziehen. Verschwende nicht deinen Atem.";
			link.l1.go = "rober_abordage_5";
		break;
		
		case "rober_abordage_5":
			PlaySound("Voice\English\sharlie\Rober Marten-03.wav");
			dialog.text = "Verdammt! Was hätte ich sonst tun sollen?! Ich konnte sie nicht am Leben lassen und sie endlos auf dem Boot verstecken! Und wer bist du... du Taugenichts, du Bastard, du Mörder, um mir Moralpredigten zu halten! Sieh dich doch mal an! Deine 'Methoden'! Du bist nicht besser als ich!";
			link.l1 = "Genug. Martene, zieh dein Schwert! Es ist Zeit, das zu beenden.";
			link.l1.go = "rober_abordage_6";
		break;
		
		case "rober_abordage_6":
			dialog.text = "Ich werde dich in der Hölle sehen!";
			link.l1 = "...";
			link.l1.go = "rober_abordage_7";
		break;
		
		case "rober_abordage_7":
			DialogExit();
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Тибо, вариант без Кати
		case "tibo":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "Was machen Sie in meinem Haus, Herr?";
			link.l1 = TimeGreeting()+", Herr Thibaut. Ich bin hier im Auftrag eines Mannes, den Sie kennen, Kapitän Robert Martene.";
			link.l1.go = "tibo_1";
		break;
		
		case "tibo_1":
			dialog.text = "Hm. Und? Na und?";
			link.l1 = "Kapitän Martene erbittet das Vergnügen Ihrer Gesellschaft sofort am Fisheye-Strand. Aber nicht alleine. Er würde es auch schätzen, Molly Jones in Ihrer Begleitung zu sehen. Verstehen Sie, was ich meine?";
			link.l1.go = "tibo_2";
		break;
		
		case "tibo_2":
			PlaySound("Voice\English\sharlie\Henry Thibault-01.wav");
			dialog.text = "Ach, mein Herr, das tue ich nicht. Ich habe noch nie von einer Molly Jones gehört und Robert hat noch nie einen... Bevollmächtigten zu mir geschickt, den ich noch nie zuvor gesehen habe. Nur zu Ihrer Information, Monsieur, ich bin der zweite Mann auf dieser Insel nach meinem Onkel dem Gouverneur, also...";
			link.l1 = "Das Leben ist ein unberechenbares Biest, Henry... Im Moment bist du der zweite Mann auf der Insel und in ein paar Stunden könntest du in Fesseln in den Kasematten sein... Alles für das Leben von jemandem, der dir nicht einen einzigen Peso geben würde. Du hast den Befehl deines Onkels missachtet, nicht wahr, Monsieur Thibaut? Was ist dir wichtiger: ein leichtfertiges Mädchen oder dein Leben?";
			link.l1.go = "tibo_3";
		break;
		
		case "tibo_3":
			dialog.text = "Warum du... Du lügst! Du redest Unsinn!";
			link.l1 = "Du, wie jeder andere auch, musst wissen, wie feurig das Temperament deines Onkels sein kann. Levasseur wird herausfinden, dass du das Mädchen versteckst, bevor die Sonne untergeht. Frag mich nicht, wie Robert das herausgefunden hat, beachte einfach meine Worte: er hat Todesangst und ist bereit, sofort den Anker zu lichten. Er wagte es nicht einmal, die Stadt zu betreten und zahlte mir eine stattliche Summe, um dir diese Nachricht stattdessen zu überbringen.";
			link.l1.go = "tibo_4";
		break;
		
		case "tibo_4":
			dialog.text = "Verdammt... Das kann nicht sein!";
			link.l1 = "Es liegt an Ihnen, Herr. Martene wird nicht länger als zwei Stunden auf Sie warten. Er schätzt den Kopf auf seinen eigenen Schultern. Nur als Zeichen seiner Freundschaft hält er sich noch am Ufer von Tortuga auf und versteckt sich nicht irgendwo bei den Holländern.";
			link.l1.go = "tibo_5";
		break;
		
		case "tibo_5":
			dialog.text = "Verdammt! Wie konnte mein Onkel das herausfinden?";
			link.l1 = "Zungen, Henry. Schwatzende Zungen. Selbst ich weiß, dass du und Robert die Schönheit von der von deinem Kumpel beschlagnahmten englischen Brigg genommen habt. Vor Levasseur versteckt...tsk tsk. Glaubst du wirklich, dass ich der Einzige bin, der von dieser Geschichte weiß?";
			link.l1.go = "tibo_6";
		break;
		
		case "tibo_6":
			dialog.text = "Es scheint, dass Sie die Wahrheit sagen, Herr. Sagen Sie Martene...";
			link.l1 = "Ich glaube nicht, dass du verstehst, Henry. Martene wird nicht auf dich warten. Deine einzige Hoffnung ist es, dieses Mädchen hier rauszubekommen, der Grund, warum sowohl du als auch Robert Schlingen um den Hals haben. Lauf dorthin, wo du sie versteckst, nimm sie an ihren hübschen kleinen Händen und bring sie zum Voltigeur. Finde sie schnell und bring sie noch schneller. Dein Onkel wird kein Wort davon von mir hören.";
			link.l1.go = "tibo_7";
		break;
		
		case "tibo_7":
			dialog.text = "In Ordnung. Dann machen wir das so. Danke für Ihre Großzügigkeit, Herr!";
			link.l1 = "Kein Grund, mir zu danken, Monsieur. Meine Arbeit ist bezahlt ... Ich möchte nur, dass Sie aus der Suppe kommen, bevor Sie gekocht sind.";
			link.l1.go = "tibo_8";
		break;
		
		case "tibo_8":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Terrapin_wait.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_wait.win_condition.l1.date.hour  = sti(GetTime()+3);
			pchar.quest.Terrapin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l2 = "location";
			pchar.quest.Terrapin_wait.win_condition.l2.location = "Tortuga_tavern";
			pchar.quest.Terrapin_wait.function = "Terrapin_SetEnvoy";
			pchar.questTemp.Terrapin = "cave";
			AddQuestRecord("Terrapin", "8");
			SetFunctionTimerCondition("Terrapin_ReturnTibo", 0, 0, 10, false);
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 4, false);
			} 
			else SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 2, false);
		break;
		
		// вариант с Кати
		case "tibo_9":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "Was machen Sie hier, Herr? Ich habe Sie nicht hier eingeladen.";
			link.l1 = TimeGreeting()+", Herr Thibaut. Ich komme von einem Mann, den Sie kennen. Sein Name ist Kapitän Robert Martene.";
			link.l1.go = "tibo_10";
		break;
		
		case "tibo_10":
			dialog.text = "Hm. Und? Na und?";
			link.l1 = "Kapitän Martene erbittet das Vergnügen Ihrer Gesellschaft jetzt sofort am Fischauge Strand. Aber nicht alleine. Er würde sich auch freuen, Molly Jones in Ihrer Gesellschaft zu sehen. Verstehen Sie, was ich meine?";
			link.l1.go = "tibo_11";
		break;
		
		case "tibo_11":
			dialog.text = "Ach, Herr, ich tue es nicht.";
			link.l1 = "Das ist genau das, was ich erwartet habe, dass du sagst. Natürlich zweifle ich daran, dass du zuvor Colonel Fox's Tochter vorgestellt wurdest, du kennst natürlich Colonel Fox, den Kommandanten der berüchtigten Sea Foxes...der Schrecken von Englands Feinden in der Karibik? Du und Robert habt ein solches Hornissennest aufgewirbelt, es ist ein Wunder, dass ihr noch nicht gestochen wurdet! Das Mädchen Molly Jones, das ihr von dem englischen Brigadier gefangen genommen habt, das ihr vor Levasseur versteckt habt. ist die Tochter von Colonel Fox, Catherine Fox!";
			link.l1.go = "tibo_12";
		break;
		
		case "tibo_12":
			dialog.text = "W-was?";
			link.l1 = "Sie sind ziemlich bleich geworden, Herr. Jetzt hören Sie mir genau zu, Henry, und achten Sie darauf: Sie und Ihr Kamerad Robert stecken bis zum Hals in der Scheiße. Jeden Tag jetzt wird Cromwells Marinegeschwader in der Karibik ankommen. Sie werden nach Ihnen suchen. Sein Flaggschiff allein ist in der Lage, Ihre gerühmte La Roche und ihre Mannschaft in ein paar Stunden in Splitter und Hackfleisch zu verwandeln. Was denken Sie? War der Angriff auf diese englische Brig und die Gefangennahme von Fox's Tochter es wert?";
			link.l1.go = "tibo_13";
		break;
		
		case "tibo_13":
			dialog.text = "";
			link.l1 = "Aber das ist nicht alles. Deine Machenschaften sind nicht nur mir bekannt geworden. Dein lieber Onkel, der Gouverneur, wird herausfinden, dass du gegen seine strengen Anordnungen verstoßen und ein Mädchen vor ihm verborgen hast, das der alte Lüstling definitiv für sich selbst haben wollte. Was denkst du, Henry? Was wird dein Onkel dir antun? Du musst wie kein anderer wissen, wie feurig sein Temperament ist...";
			link.l1.go = "tibo_14";
		break;
		
		case "tibo_14":
			dialog.text = "Alles Lügen!";
			link.l1 = "Ist das so? Mein lieber Henry, du kannst deinen Freund Martene fragen. Er war es, der mich geschickt hat. Levasseur wird herausfinden, dass du das Mädchen versteckst, bevor die Sonne untergeht. Frag mich nicht, wie Robert das herausgefunden hat, hör einfach auf meine Worte: er hat einen Heidenangst und ist bereit, sofort den Anker zu lichten und abzulegen. Er hat sich nicht einmal getraut, in die Stadt zu kommen. Deshalb bat er mich, dir diese Nachricht zu überbringen.";
			link.l1.go = "tibo_15";
		break;
		
		case "tibo_15":
			dialog.text = "";
			link.l1 = "Martene wird nicht länger als zwei Stunden auf dich warten. Er schätzt den Kopf auf seinen eigenen Schultern. Nur als Zeichen eurer Freundschaft hält er sich noch immer an der Küste von Tortuga auf und versteckt sich nicht irgendwo bei den Holländern. Allerdings ahnt der arme Robert nicht einmal, wer Molly Jones wirklich ist. Wisst ihr, ihr beiden erstaunt mich wirklich mit eurer unglaublichen Unkenntnis der Damenmode und des Aussehens! Ihr könntet nicht einmal eine Adlige von ihrer Dienerin unterscheiden!";
			link.l1.go = "tibo_16";
		break;
		
		case "tibo_16":
			dialog.text = "Was willst du?";
			link.l1 = "Endlich einige weise Worte von dem jungen Emporkömmling! Nun gut, Thibaut: Geh dorthin, wo du sie gerade versteckt hältst, nimm sie sanft an ihre lilienweißen Hände und schlendere schnell mit ihr zum Fisheye-Strand, wo Martenes Voltigeur ist. Sag ihm, deine Pläne haben sich geändert...";
			link.l1.go = "tibo_17";
		break;
		
		case "tibo_17":
			dialog.text = "";
			link.l1 = "Martene muss sein Versprechen mir gegenüber erfüllen, er sollte nicht einmal versuchen, das Mädchen auf sein eigenes Schiff zu nehmen. Sie wird am Strand bleiben und auf mich warten. Sag Robert, dass wenn er seine Verpflichtungen nicht erfüllt, oder Catherine wegnimmt, oder wenn ein Haar von ihrem hübschen kleinen Kopf fällt, werde ich den Rest meines Lebens damit verbringen, sie zu finden. Und wenn ich sie finde, werde ich sie Colonel Fox... lebend übergeben. Aber für euch beide...ich bringe euch in Stücken zurück. Ja, übrigens, das beinhaltet auch dich, Thibaut.";
			link.l1.go = "tibo_18";
		break;
		
		case "tibo_18":
			dialog.text = "";
			link.l1 = "Wer ich bin und was meine Möglichkeiten sind, können Sie Robert fragen. Er ist gut informiert. Wenn ihr beide tut, was ich gesagt habe, dann gewinnen wir alle. Robert kann sein Piratengeschäft fortsetzen und ihr werdet alle eure Privilegien bewahren und das Erbe eures lieben alten Onkels erhalten, wenn er seinen letzten Schnaufer macht. Was mich betrifft... ich werde auch nicht als Verlierer dastehen. Ist das alles klar?";
			link.l1.go = "tibo_19";
		break;
		
		case "tibo_19":
			PlaySound("Voice\English\sharlie\Henry Thibault-03.wav");
			dialog.text = "Ich würde lieber in ewigem Höllenfeuer brennen, als deinen Befehlen zu folgen... "+GetFullName(pchar)+"! Wie konnte ich dich nicht von Anfang an erkennen? Du Schlächter! Du hast nicht vor, mich oder Robert am Leben zu lassen! Deine 'Methoden' sind weit bekannt! Es gibt keine Möglichkeit, dass ich Molly ... oder Catherine dazu aufgebe, an Abschaum wie dich! Du wirst Tortuga nicht lebend verlassen, Scheißkerl!";
			link.l1 = "..., Freund.";
			link.l1.go = "tibo_20";
		break;
		
		case "tibo_20":
			dialog.text = "";
			link.l1 = "Halt, Feigling!";
			link.l1.go = "tibo_21"; // patch
		break;
		
		case "tibo_21":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload_window", "none", "", "", "Terrapin_LevasserRoomEnter", 5); // patch
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_window");
			LAi_RemoveLoginTime(npchar);
		break;
		
		case "tibo_22":
			pchar.quest.Terrapin_TiboCallOver.over = "yes"; //снять прерывание
			pchar.quest.Terrapin_tibo_call.over = "yes"; //снять прерывание
			PlaySound("Voice\English\sharlie\Henry Thibault-04.wav");
			dialog.text = "Nun, endlich! Kapitän "+GetFullName(pchar)+", Ich freue mich sehr, dass du gekommen bist. Komm rein, setz dich. Etwas zu trinken? Ich habe ein ziemlich lukratives Geschäftsangebot für dich, mein Freund...";
			link.l1 = "Nun, Sie sind heute in der zuvorkommendsten Laune, Monsieur Thibaut... Lassen wir uns nicht herumsitzen. Kommen wir gleich zur Sache.";
			link.l1.go = "tibo_23";
		break;
		
		case "tibo_23":
			dialog.text = "Der Vorschlag betrifft meinen ehemaligen Freund und Gefährten, den ihr als Robert Martene kennt, ehemaliger Kapitän des Galeonen 'Voltigeur'...";
			link.l1 = "Also, du und Robert seid keine Kameraden mehr? Eine faszinierende Entwicklung.";
			link.l1.go = "tibo_24";
		break;
		
		case "tibo_24":
			dialog.text = "Kapitän, bitte, hören Sie meine Beweggründe für die Suche nach Ihrer Hilfe und alles wird klar werden. Wie Sie selbst wissen, hat Martene mit einer englischen Brigantine gerungen und eine Engländerin gefangen genommen, eine Dienerin namens Molly Jones, der ganze Grund, warum all diese Probleme aufgewühlt wurden.";
			link.l1 = "Natürlich, ich weiß. Wie ich verstehe, haben Sie meinen Empfehlungen entsprochen und das Mädchen zu Martenes Schiff geführt?";
			link.l1.go = "tibo_25";
		break;
		
		case "tibo_25":
			dialog.text = "Ja, ich habe es getan. Aber ich bereue es jeden Tag. Du sollst wissen, dass Molly ein sehr bezauberndes und schönes Mädchen ist, ich habe noch nie jemanden wie sie getroffen. Ich muss zugeben, ich habe mich in sie verliebt. Sie mochte mich auch, sie hat es selbst gesagt! Ich konnte nicht zulassen, dass mein Onkel sie nimmt\nAls ich sie zum 'Voltigeur' begleitete, hoffte ich, dass der Onkel sich beruhigen würde, sobald er herausfand, dass niemand Mädchen vor ihm versteckt, der alte Lüstling. Dann würde Robert sie nach Tortuga zurückbringen, damit ich sie sicher zu mir bringen könnte. So oder so, das war der Deal, den ich mit Martene gemacht habe. Aber es lief anders\nAls ich erfuhr, dass mein Onkel getötet worden war, gab es keinen Grund mehr, Molly zu verstecken, also wartete ich geduldig darauf, dass der 'Voltigeur' mit Molly an Bord ankam.";
			link.l1 = "Ist sie angekommen?";
			link.l1.go = "tibo_26";
		break;
		
		case "tibo_26":
			dialog.text = "Ja. Leider war Molly nicht auf dem Schiff. Robert war erschüttert, als hätte er mit Luzifer selbst den Kopf gestoßen. Während seiner kurzlebigen Expedition fand er irgendwie ein schreckliches Detail heraus: das Mädchen, Molly, war überhaupt nicht Molly Jones, sondern Catherine Fox! Die Tochter von Colonel Fox selbst, Kommandant der Sea Foxes, des Elite-Englischen Marine-Regiments! Du weißt, was das bedeutet!";
			link.l1 = "Verdammt nochmal, wie kann das sein! Zweifellos hat Robert dann etwas zu fürchten. Aber wie konnte es so weit kommen?";
			link.l1.go = "tibo_27";
		break;
		
		case "tibo_27":
			dialog.text = "Als Catherine gefangen genommen wurde, versteckte sie absichtlich ihre Identität und gab sich als Molly Jones aus, ein Dienstmädchen, das während des Enterns starb. Sie hatte Angst, dass Martene herausfinden würde, wer sie wirklich ist. Und es gelang ihr, ihn zu täuschen. Aber während der letzten Reise fand Robert irgendwie heraus, wer sie wirklich ist. Er sagte, dass er einige ihrer Briefe oder Papiere gefunden hätte...";
			link.l1 = "Und wo ist das Mädchen jetzt, wenn es nicht an Bord der 'Voltigeur' gegangen ist?";
			link.l1.go = "tibo_28";
		break;
		
		case "tibo_28":
			dialog.text = "Sie ist tot. Aus Angst vor der bevorstehenden Strafe von Fox für den Angriff auf die englische Brigg, beschloss Martene, das einzige verbleibende Beweismittel im Wasser zu verstecken. Sie war der letzte Zeuge seines Angriffs auf die 'Albatros'.";
			link.l1 = "Dann hätte er genauso gut all seine Matrosen ermorden können... Wie Fernand Luc. Sonst werden sie eines Tages betrunken und plaudern in der Taverne ein bisschen zu viel aus...";
			link.l1.go = "tibo_29";
		break;
		
		case "tibo_29":
			dialog.text = "Er hat das Gefühl, dass seine ganze Mannschaft ihm aufs Blut geschworen ist. Vielleicht hat er teilweise recht. Aber ich kenne Oberst Fox! Er wird bis zum Ende seiner Tage graben, um herauszufinden, wer seine Tochter entführt hat!";
			link.l1 = "Ich bezweifle das nicht. Besonders nachdem ein französischer Pirat seine Frau getötet hat. Jetzt auch seine Tochter... Übrigens, sind Sie sich absolut sicher, Monsieur, dass Catherine wirklich tot ist? Vielleicht hat Robert sie irgendwo vor Ihnen versteckt.";
			link.l1.go = "tibo_30";
		break;
		
		case "tibo_30":
			dialog.text = "Ich bin sicher. Ich habe mit einem Matrosen von der 'Voltigeur' gesprochen. Ich glaubte ihm. Er sah mit eigenen Augen, wie sie dem Mädchen die Kehle durchschnitten und dann eine Kanonenkugel an ihre Füße banden und sie über Bord warfen.";
			link.l1 = "Gott im Himmel! Diese arme Frau... was willst du von mir, Henry?";
			link.l1.go = "tibo_31";
		break;
		
		case "tibo_31":
			dialog.text = "Ich kann seit diesem Tag nicht mehr schlafen. Ich sehe Molly die ganze Zeit vor meinen Augen... Catherine, eher. Ich habe sie in den Tod geführt, "+GetFullName(pchar)+"! Ich kann mir das nicht vergeben. Darüber hinaus mache ich mir keine Illusionen über Fox. Dieser Mann ist nicht selbstzufrieden und ich denke nicht einmal, dass er schläft. Früher oder später wird er Martenes Spur aufnehmen, jemanden zum Reden bringen und wenn er herausfindet, wer seine Tochter getötet hat, wird die Hölle losbrechen. Es wird hart für jeden, der auf die eine oder andere Weise mit der ganzen Geschichte verbunden war.";
			link.l1 = "Das schließt mich ein.";
			link.l1.go = "tibo_32";
		break;
		
		case "tibo_32":
			dialog.text = "Aye, mir geht's genauso. Deshalb möchte ich, dass du Martene findest, bevor Fox es tut. Finde diesen Bastard und töte ihn. Und wenn du kannst, lass ihn zuerst leiden. Für die arme Catherine. Wenn es getan ist, schneid den fetten Ring ab, den er an der Hand trägt, mit dem Finger darin und bring ihn mir als Beweis\nIch kenne seinen krummen Finger und diesen Ring gut. Wenn du das tust, zahle ich dir ein Viertel Million in Silber.";
			link.l1 = "Sieht so aus, als hätten Sie ein großes Erbe von Ihrem lieben alten Onkel in Frieden erhalten, nicht wahr? Sagen Sie mir, Henry, warum haben Sie sich entschieden, mich um Hilfe bei dieser Angelegenheit zu bitten?";
			link.l1.go = "tibo_33";
		break;
		
		case "tibo_33":
			dialog.text = "Weil ich auch einige Dinge über dich gelernt habe, "+GetFullName(pchar)+". Es war einfach, Sie sind ein berühmter Mann. Es ist unbekannt, für wen Sie wirklich arbeiten, entweder für de Poincy, oder für die Holländer, oder für die Engländer oder für Baron Jan Svenson... Aber eines ist klar: Sie übernehmen heikle, diskrete Aufträge und erledigen sie. Dann werden Sie dafür fürstlich bezahlt. Und am besten sind Sie nicht mit den Spaniern verbunden\nSchließlich haben Sie auch an den Ereignissen teilgenommen, nach denen ich das Vermögen meines Onkels geerbt habe. Leugnen Sie es nicht... Ein Viertel Million ist gutes Geld. Ich werde Ihnen sagen, wo Sie Martene finden. Sie müssen nur sein Schiff abfangen und es entern.";
			link.l1 = "Noch hunderttausend und ich kümmere mich um Martene für dich.";
			link.l1.go = "tibo_34";
			link.l2 = "Ach, Monsieur Thibaut, Sie müssen sich um Ihr Problem mit Martene und Oberst Fox ohne meine Beteiligung kümmern. Ich verspreche Ihnen meinerseits, dass ich kein Wort an den Oberst über das Schicksal seiner Tochter und diejenigen, die für ihren Tod verantwortlich sind, senden werde. Alles Gute, mein Herr.";
			link.l2.go = "tibo_exit";
		break;
		
		case "tibo_exit":
			DialogExit();
			AddQuestRecord("Sharlie", "26");
			NextDiag.CurrentNode = "tibo_over";
		break;
		
		case "tibo_34":
			dialog.text = "Herr, fürchte Gott... Ich habe keine Millionen in Schatztruhen gelagert, glauben Sie mir! Ich verstehe, dass Ihre Dienstleistungen Geld kosten, weshalb ich Ihnen gleich zweihundertfünfzigtausend angeboten habe...Gut...Also, wie wäre es, wenn ich noch fünfzigtausend Gold hinzufüge. Mehr kann ich Ihnen nicht anbieten!";
			link.l1 = "Gut. Du hast einen Deal. Wo hast du Martene zum letzten Mal gesehen?";
			link.l1.go = "tibo_35";
		break;
		
		case "tibo_35":
			dialog.text = "Er segelte nach Süden zur Spanischen Hauptstadt in Caracas und es gelang ihm, eine Audienz bei Don Diego Francisco de Kerres, dem Gouverneur, zu erlangen. Es scheint, dass er ihn irgendwie bestochen hat, denn Don Diego gewährte Robert den Schutz der spanischen Krone. Er verkaufte den 'Voltigeur' und ist nun Kapitän der schweren Galeone 'Infanta'. Er muss wirklich gute Ersparnisse gehabt haben, da er es sich leisten konnte, den Gouverneur zu bestechen und ein großes Kriegsschiff wie dieses zu kaufen und auszurüsten\nAlso, als nächstes wird er von Caracas nach Santo Domingo auf seinem neuen Schiff als Teil einer spanischen Eskadron segeln. Das ist alles, was mein Agent herausfinden konnte. Die einzige Möglichkeit, Martene zu erwischen, besteht darin, die spanische Eskadron einzuholen\nWenn sie Santo Domingo erreichen, ist es vorbei. Keine Ahnung, wohin Robert als nächstes gehen wird. Er wird sich wie ein Kaninchen in einem Bau verstecken und wir werden ihn nie finden.";
			link.l1 = "Verstanden. Ich werde sie abfangen.";
			link.l1.go = "tibo_36";
		break;
		
		case "tibo_36":
			dialog.text = "Und vergiss nicht den Finger mit dem Ring! Das ist eine obligatorische Bedingung unserer Vereinbarung! Ich möchte absolut sicher sein, dass Robert tot ist!";
			link.l1 = "In Ordnung. Lass uns keine Zeit verschwenden, ich werde sofort in See stechen!";
			link.l1.go = "tibo_37";
		break;
		
		case "tibo_37":
			DialogExit();
			AddQuestRecord("Sharlie", "27");
			Terrapin_CreateRoberConvoy();
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			NextDiag.CurrentNode = "tibo_time";
		break;
		
		case "tibo_time":
			dialog.text = "Ist Martene noch immer mit seiner Anwesenheit die Karibik verpestet, Kapitän?";
			link.l1 = "Er hat nicht mehr viel Zeit!";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_time";
		break;
		
		case "tibo_38":
			dialog.text = "Ist Martene dabei, die Karibik mit seiner Anwesenheit zu stinken, Kapitän?";
			link.l1 = "Nicht mehr. Ihr braucht Colonel Fox nicht mehr zu fürchten und eure Catherine ist gerächt. Hier ist euer Beweis.";
			link.l1.go = "tibo_39";
		break;
		
		case "tibo_39":
			RemoveItems(pchar, "finger", 1);
			dialog.text = "Ja... Das ist ohne Zweifel Martenes Finger. Du hörst nie auf zu beeindrucken, Kapitän "+GetFullName(pchar)+"! Du verdienst wirklich den Ruf, der dir gegeben wird.";
			link.l1 = "Lassen wir uns zur Zahlung kommen, oder, Thibaut?";
			link.l1.go = "tibo_40";
		break;
		
		case "tibo_40":
			AddMoneyToCharacter(pchar, 250000);
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You've received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Alles ist fertig. Hier, nimm deine Belohnung.";
			link.l1 = "Mein Dank. Ich bin froh, dass du das im Voraus vorbereiten konntest. Nun, Henry, ich hoffe, dass du in Zukunft nicht in weitere solche Schwierigkeiten gerätst und dir bessere Freunde aussuchst. Alles Gute!";
			link.l1.go = "tibo_41";
		break;
		
		case "tibo_41":
			dialog.text = "Danke für Ihre Hilfe, Kapitän! Ich werde Sie all meinen Freunden empfehlen. Viel Glück!";
			link.l1 = "...";
			link.l1.go = "tibo_42";
		break;
		
		case "tibo_42":
			DialogExit();
			AddQuestRecord("Sharlie", "31");
			NextDiag.CurrentNode = "tibo_stop";
		break;
		
		case "tibo_stop":
			dialog.text = "Ja, mein Herr "+GetFullName(pchar)+"? Hast du ein Anliegen bei mir?";
			link.l1 = "Nein, Monsieur Thibaut. Hab mich nur entschieden, einen Moment vorbeizuschauen. Auf Wiedersehen!";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_stop";
		break;
		
		case "tibo_late":
			dialog.text = "Ach, "+GetFullName(pchar)+"...Los, was dauert das so lange! Wer zum Teufel weiß jetzt, wo Robert Martene ist?! Wenn Oberst Fox es schafft, alles herauszufinden, glaube ich, dass ich in großen Schwierigkeiten stecken werde...";
			link.l1 = "Ich verstehe. Ich war zu spät. Meine Entschuldigungen, Monsieur Thibaut, aber ich wurde durch einige sehr dringende Angelegenheiten aufgehalten. Ich werde Ihre Zeit nicht verschwenden. Auf Wiedersehen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		case "tibo_over":
			dialog.text = "Was willst du, "+GetFullName(pchar)+"? Ich habe keine Zeit zum Plaudern. Ich habe größere Fische zu braten. Ich muss Martene finden, bevor Fox es tut...";
			link.l1 = "Ja, ja. Ich bin auf dem Weg.";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		// посланник от Мартэна
		case "envoy":
			dialog.text = "Bist du Kapitän "+GetFullName(pchar)+"?";
			link.l1 = "Du bist beim richtigen Mann gelandet, Kumpel. Ich bin ganz Ohr.";
			link.l1.go = "envoy_1";
		break;
		
		case "envoy_1":
			dialog.text = "Ihr Schuldner hat mich gebeten, Ihnen mitzuteilen, dass die Tat getan ist und der Fisch in weniger als einer Stunde ins Netz schwimmen wird. Also beeil dich.";
			link.l1 = "Ich verstehe. Danke!";
			link.l1.go = "envoy_2";
		break;
		
		case "envoy_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Terrapin", "9");
			pchar.quest.Terrapin_cave.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_cave.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.Terrapin_cave.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l2 = "location";
			pchar.quest.Terrapin_cave.win_condition.l2.location = "Tortuga_cave";
			pchar.quest.Terrapin_cave.function = "Terrapin_LevasserInCave";
		break;
		
		// Левассер в пещере
		case "levasser_cave":
			pchar.quest.Terrapin_LateDungeon.over = "yes"; //снять таймер
			dialog.text = "Warum zum Teufel streunst du hier herum? Wer bist du? Antworte mir jetzt!";
			link.l1 = "Wer zum Teufel bist du und warum stellst du mir solche dummen Fragen?";
			link.l1.go = "levasser_cave_1";
		break;
		
		case "levasser_cave_1":
			dialog.text = "Was?! Du Rotznase! Wer ich bin? Ich bin der Gouverneur dieser Insel, Francois Levasseur, Senior de Renet de Boidouflet de Lettre! Und alles auf dieser Insel fällt in meine Zuständigkeit! Das schließt dich ein, solange du auf meinem Territorium bist, du Grünschnabel!";
			link.l1 = "Nun, nun... Der große böse Wolf selbst, was? Du bist ein wenig verloren, Levasseur, Senior de Renet de was auch immer es war. Deine Zeit ist um. Auf Befehl des Generalgouverneurs Francois Longvillier de Poincy wurdest du von deinem Posten entfernt und zum sofortigen Tod verurteilt! Ich bin dein Richter und Henker in einem! Irgendwelche letzten Worte?";
			link.l1.go = "levasser_cave_2";
		break;
		
		case "levasser_cave_2":
			dialog.text = "";
			link.l1 = "Ich nehme an, du wirst nicht aufgeben und mich um Gnade bitten wird dir nichts nützen, also zieh dein Stahl!";
			link.l1.go = "levasser_cave_3";
		break;
		
		case "levasser_cave_3":
			dialog.text = "Verdammt! Es ist ein Agent von de Poincy! Zieht eure Schwerter! Tötet ihn!";
			link.l1 = "Lass uns tanzen.";
			link.l1.go = "levasser_cave_4";
		break;
		
		case "levasser_cave_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_cave")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=2; i<=4; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+7;
			int iScl = 30 + 2*sti(pchar.rank);
			for (i=5; i<=9; i++)
			{		
				sld = GetCharacter(NPC_GenerateCharacter("TerrapinGuard"+i, "citiz_5"+i, "man", "man", iRank, PIRATE, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2+50);
				ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserCaveDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Левассер в комнате таверны
		case "levasser_room":
			dialog.text = "Was zum Teufel machst du hier? Wer bist du? Antworte mir, jetzt!";
			link.l1 = "Wie wäre es damit! Das habe ich nicht kommen sehen... Monsieur Levasseur selbst, nehme ich an?";
			link.l1.go = "levasser_room_1";
		break;
		
		case "levasser_room_1":
			dialog.text = "Ja, ich bin der Gouverneur dieser Insel, Francois Levasseur, Senior de Renet de Boidouflet de Lettre! Und alles auf dieser Insel untersteht meiner Jurisdiktion! Und das schließt dich ein, während du auf meinem Territorium herumläufst, du Halunke! Beantworte die Fragen! Sergeant, schließ diese Tür ab. Dieser Mann führt nichts Gutes im Schilde!";
			link.l1 = "Sie sind unglaublich scharfsinnig, Monsieur Levasseur, Senior de Renet de was auch immer. Meine Anwesenheit hier wird Ihnen keine Freude bereiten. Auf Befehl des Generalgouverneurs Francois Longvillier de Poincy wurden Sie von Ihrem Posten entfernt und zum sofortigen Tod verurteilt! Ich bin Ihr Richter und Ihr Henker in einem!";
			link.l1.go = "levasser_room_2";
		break;
		
		case "levasser_room_2":
			dialog.text = "";
			link.l1 = "Ich nehme an, du wirst nicht aufgeben und mich um Gnade zu bitten wird dir nichts nutzen, also zieh Stahl! Du bist meine Aufgabe, nichts Persönliches. Ich diene nur der Krone, ha! Sergeant, ich rate Ihnen nicht einzugreifen, während ich die Befehle des Generalgouverneurs ausführe!";
			link.l1.go = "levasser_room_3";
		break;
		
		case "levasser_room_3":
			dialog.text = "Hör ihm nicht zu, Sergeant! Er ist ein spanischer Agent! Töte ihn! Wachen, Hilfe! Hier sind Spanier!";
			link.l1 = "Noch nie in Spanien gewesen, eigentlich nur in Narbonne.";
			link.l1.go = "levasser_room_4";
		break;
		
		case "levasser_room_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserRoomDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// девушка на балконе
		case "roof_girl":
			dialog.text = "Autsch! Hilf mir! Soldaten!";
			link.l1 = "Beruhige dich, du Narr! Wenn du nicht schreist, werde ich dir nichts antun!";
			link.l1.go = "roof_girl_1";
		break;
		
		case "roof_girl_1":
			dialog.text = "Töte mich nicht!";
			link.l1 = "Sei nicht dumm! Ein Mann ist hier vor zehn Minuten vorbeigelaufen. Ein gut gekleideter Adliger. Wo versteckt er sich? Und denk nicht einmal daran, mir zu sagen, dass du ihn nicht gesehen hast!";
			link.l1.go = "roof_girl_2";
		break;
		
		case "roof_girl_2":
			dialog.text = "Herr Thibaut?";
			link.l1 = "Nun, du kennst ihn also! Wo ist er hin gelaufen? Wirst du antworten oder soll ich deinen Kopf kräftig schütteln, damit er funktioniert?";
			link.l1.go = "roof_girl_3";
		break;
		
		case "roof_girl_3":
			dialog.text = "Oh nein, bitte tu mir nichts an! Monsieur Thibaut ist weggerannt, in Richtung Meer. Und er sprang vom Hebewerk direkt ins Wasser. Er ist wahrscheinlich gestorben, es ist so hoch oben...";
			link.l1 = "Ich glaube nicht. Er ist nicht der Typ, der Selbstmord begehen würde. Du solltest reingehen. Es ist gefährlich, heute Nacht hier draußen zu sein..";
			link.l1.go = "roof_girl_4";
		break;
		
		case "roof_girl_4":
			dialog.text = "Autsch! Au! Schieß nicht!";
			link.l1 = "Was?!";
			link.l1.go = "roof_girl_5";
		break;
		
		case "roof_girl_5":
			DialogExit();
			LAi_SetActorType(pchar);
			PlaySound("People Fight\MushketShot.wav");
			DoQuestCheckDelay("Terrapin_GirlShot", 1.0);
		break;
		
		// Кати
		case "kathy":
			PlaySound("Voice\English\Armo02.wav");
			dialog.text = "Wer bist du? Bist du gekommen, um mich zu töten oder... schlimmer?";
			link.l1 = "Mitnichten, Madame. Ich werde Sie, Catherine Fox, zu Ihrem Vater nach St. John's zurückbringen. Wenn er Ihnen danach eine Tracht Prügel für das Missachten seiner Befehle gibt, wird mein Schuldgefühl wiederholt. Ich hoffe jedoch, dass der Oberst trotz all der Sorgen, die sie ihm bereitet hat, froh sein wird, seine Tochter lebend zu sehen.";
			link.l1.go = "kathy_1";
		break;
		
		case "kathy_1":
			dialog.text = "Dank Gott! Ich muss träumen! Weißt du nicht, wer ich bin? Du bist ein Franzose und ein Katholik und hast dennoch beschlossen, hierher zu kommen, um mich aus den Händen meiner eigenen Landsleute zu retten? Du hast dein Leben nur für die Tochter von Oberst Fox riskiert?";
			link.l1 = "Mein ursprünglicher Grund, hier auf Tortuga zu sein, war ganz anders. Aber ich konnte auch eine schöne Dame nicht in den Händen einer Bande von Dieben und Räubern lassen.";
			link.l1.go = "kathy_2";
		break;
		
		case "kathy_2":
			dialog.text = "Sie sind ein edler Herr! Wie ist Ihr Name, Monsieur?";
			link.l1 = ""+GetFullName(pchar)+". Kapitän "+GetFullName(pchar)+".";
			link.l1.go = "kathy_3";
		break;
		
		case "kathy_3":
			dialog.text = "Sagen Sie mir, Kapitän, werden Sie mich wirklich zu meinem Vater in St. John's bringen?";
			link.l1 = "Ja, obwohl er Franzosen nicht gut gesinnt ist. Nun, ich werde ihn daran erinnern, dass es auch englische Schurken gibt, einschließlich englischer Offiziere! Ich war Zeuge von mindestens einem von ihnen... Richard Fleetwood war sein Name.";
			link.l1.go = "kathy_4";
		break;
		
		case "kathy_4":
			dialog.text = "Wenn wir es nach Antigua schaffen, werde ich alles tun, um meinen Vater davon zu überzeugen, dass es unter den Franzosen wahre Ritter gibt.";
			link.l1 = "Ich würde das sehr schätzen... Also gut, ich hoffe, dass meine Schutzengel meinen Weg über die Dächer der Stadt verfolgt haben und bereits auf unsere Rückkehr warten.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_OwrInGrot");
		break;
		
		case "kathy_5":
			PlaySound("Voice\English\Armo01.wav");
			dialog.text = "Ich konnte nicht glauben, dass du dein Versprechen bis jetzt halten würdest! Mir sind in letzter Zeit so viele schreckliche und widerliche Dinge passiert... Ich danke dir, Kapitän, dass du meinen Glauben an Menschen und Ritterlichkeit zurückgebracht hast. Du solltest meinen Vater besuchen, wenn du kannst!\nEr respektiert Männer wie dich. Und es ist egal, dass du Franzose bist. Ich werde alles tun, um meinen Vater zu überreden, seine Einstellung zu deiner Nation zu überdenken.";
			link.l1 = "Danke dir, Catherine. Vielleicht werde ich dein höfliches Angebot in Anspruch nehmen.";
			link.l1.go = "kathy_6";
		break;
		
		case "kathy_6":
			dialog.text = "Ich hoffe doch sehr, Kapitän. Nochmals vielen Dank für das, was Sie für mich getan haben. Ich werde es nie vergessen.";
			link.l1 = "Geh schon, beeil dich zu deinem Vater. Er wird begeistert sein, dich zu sehen. Vielleicht ist er schon vom Feld zurück. Nun, es ist sowieso Zeit für mich zu gehen. Auf Wiedersehen!";
			link.l1.go = "kathy_7";
		break;
		
		case "kathy_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.lifeday = 0;
			SetFunctionTimerCondition("Terrapin_ReturnFox", 0, 0, 3, false); // Фокса на место
			pchar.questTemp.Terrapin_KathyReward = "true"; // награда за спасение Кати 160912
		break;
		
		// наш матрос
		case "terrapin_grot":
			dialog.text = "Da bist du ja, Käpt'n! Du hast uns krank vor Sorge gemacht! Ein Sprint wie der über die gekachelten Dächer und ein Sprung aus dieser Magen umdrehenden Höhe war ein Anblick zum Staunen! Gott sei unser Zeuge, wir waren besorgt, dass du es nicht schaffen würdest... Willkommen zurück an Bord, Käpt'n, das Beiboot ist bereit!";
			link.l1 = "Großartig. Catherine, folge mir!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_GotoShip");
		break;
		
		case "tibo_sailor":
			dialog.text = "Hallo, Monsieur. Sind Sie Kapitän "+GetFullName(pchar)+"?";
			link.l1 = "Ja, das bin ich. Was ist los?";
			link.l1.go = "tibo_sailor_1";
		break;
		
		case "tibo_sailor_1":
			dialog.text = "Puh, ich habe dich gerade noch eingeholt... Ich bin im Auftrag eines Gentleman zu dir gekommen, den du unter dem Namen Henry Thibaut kennst.";
			link.l1 = "Henry? Und was will er? Seine Freude teilen, weil sein Erbe unerwartet auf ihn gefallen ist nach dem Tod seines lieben Onkels?";
			link.l1.go = "tibo_sailor_2";
		break;
		
		case "tibo_sailor_2":
			dialog.text = "Herr Thibaut hat dringend darum gebeten, dass Sie ihn so schnell wie möglich in seinem Anwesen auf Tortuga besuchen. Er hat gut bezahlte Arbeit für Sie. Er sagte mir auch, ich solle Ihnen einen Namen nennen: Robert Martene. Das sollte ein Funken Interesse für Sie sein.";
			link.l1 = "Ist das so? Und was hat Henry diese Idee gegeben?";
			link.l1.go = "tibo_sailor_3";
		break;
		
		case "tibo_sailor_3":
			dialog.text = "Auch wenn Sie das noch nicht überzeugt hat, ihn zu besuchen, bat er mich, folgendes hinzuzufügen: 'Robert Martene muss sterben'.";
			link.l1 = "Also gut, also gut... Jetzt wird es interessant. Zwei eingeschworene Freunde haben gerade einen Streit... Wie du sagst, ich werde versuchen, Henry zu besuchen, wenn ich die Chance dazu habe.";
			link.l1.go = "tibo_sailor_4";
		break;
		
		case "tibo_sailor_4":
			dialog.text = "Herr Thibaut hat Sie gebeten, Ihren Besuch nicht zu verzögern. 'Der Fisch wird in zehn Tagen aus dem Netz schwimmen', waren seine genauen Worte...";
			link.l1 = "Er und Robert haben die gleiche Sprechweise. Gut, ich werde Henry einen Besuch abstatten.";
			link.l1.go = "tibo_sailor_5";
		break;
		
		case "tibo_sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Terrapin_TiboCallOver", 0, 0, 10, false);
			AddQuestRecord("Sharlie", "25");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
