// лидер клана ривадос - Чёрный Эдди
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
			dialog.text = "Was machst du auf dem Territorium der Rivados, Weißer?";
			link.l1 = "Nur um die Einheimischen kennenzulernen. Entschuldigung, wenn ich Sie gestört habe.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "Friend":
			dialog.text = "Ich freue mich, einen Freund der Rivados und auch einen guten Mann zu begrüßen! Chimiset hat mir erzählt, was du für ihn getan hast. Alle Rivados, einschließlich mir, sind dir jetzt schuldig. Darf ich mich vorstellen - Edward Black, auch bekannt als Black Eddie, der Anführer der Rivados-Bande.";
			link.l1 = ""+GetFullName(pchar)+". Obwohl ich denke, dass Chimiset Ihnen bereits von mir erzählt hat. Er versprach, Ihnen zu erzählen...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			dialog.text = "Und das hat er. Jetzt kannst du unsere Schiffe frei besuchen. Die Wachen werden dich nicht aufhalten und wir werden uns freuen, dich zu sehen. Sei vorsichtig mit den Narwalen, sie müssen bereits herausgefunden haben, dass du Chimiset gerettet hast, und das wird ihnen nicht gefallen, da wir Feinde sind.";
			link.l1 = "Ich werde das berücksichtigen. Danke für die herzliche Begrüßung, Eddie! Erlauben Sie mir jetzt bitte, mit Chimiset zu sprechen.";
			link.l1.go = "Friend_2";
		break;
		
		case "Friend_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			AddSimpleRumourCityTip("They say that you are a close friend of Black Eddie, the head of Rivados. How did you do this?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Rivados claim you as their friend. How'd you do it?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that the Narwhals have a price on your head. Are you scared?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		// --> информационный блок
		case "Total_info": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "Weißer Bruder? Lebendig? Ich freue mich! Also, die Narwale haben gelogen, als sie allen erzählt haben, dass du ertrunken bist...";
				link.l1 = "Ich freue mich auch, dich zu sehen, Eddie. Gerüchte über meinen Tod sind stark übertrieben worden.";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "Schön, dich zu sehen, "+pchar.name+". Gibt es Neuigkeiten?";
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l1 = "Eddie, kennst du einen Mann namens Nathaniel Hawk? Er muss hier sein, soweit ich weiß.";
				link.l1.go = "natan";
			}
			if (!CheckAttribute(npchar, "quest.rivados"))
			{
				link.l2 = "Erzähl mir mehr über die Rivados Bande.";
				link.l2.go = "rivados";
			}
			link.l9 = "Nichts Besonderes, wirklich. Wollte nur Hallo sagen.";
			link.l9.go = "exit";
		break;
		
		case "natan":
			dialog.text = "Nathaniel Hawk? Nein, ich kenne diesen Mann nicht. Er ist weder auf den Rivados Schiffen, noch im neutralen Gebiet. Ich kann das Gleiche nicht über die Narwal-Gang sagen, wir besuchen sie nicht.";
			link.l1 = "Ich sehe...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_info";
		break;
		
		case "rivados":
			dialog.text = "Die Rivados-Bande wurde vor vielen Jahren gegründet. Es war der allererste Clan in dieser Stadt der verlassenen Schiffe. Vor mehr als fünfzig Jahren segelte die Expedition von Admiral Betancourt von Westafrika hierher mit mehreren großen Sklavenschiffen. Die Laderäume der Tartarus waren gefüllt mit Hunderten von schwarzen Sklaven, die für die karibischen Plantagen bestimmt waren. Unter diesen Sklaven war ein Mann namens Pedro Rivados, einige portugiesische Priester hatten ihm das Lesen und Schreiben beigebracht\nEr schaffte es, ein paar Dutzend Sklaven von ihren Fesseln zu befreien und eine Meuterei zu starten. Leider schlossen sich die übrigen Sklaven ihm nicht an. Der Aufstand wurde niedergeschlagen. Die Sklavenhändler fesselten Rivados an Händen und Füßen und ließen ihn im Schiffsraum zurück, um vor Hunger und Durst zu sterben. Ein paar Tage später verschlechterte sich das Wetter und Betancourts Geschwader wurde von einem mächtigen Sturm erfasst.\nTage später, nach dem Kampf gegen das Wetter, steckten die 'San Augustine' und die 'Tartarus', die einzigen beiden noch intakten Schiffe, mitten auf dieser Insel fest. Viele Männer starben bei diesen Ereignissen, schwarz und weiß, aber noch mehr schafften es zu überleben. Die ehemaligen Sklaven begannen ein neues Leben zusammen und nannten sich die Rivados zu Ehren von Pedro Rivados, dem Befreier.";
			link.l1 = "Eine sehr interessante Geschichte... Danke!";
			link.l1.go = "exit";
			npchar.quest.rivados = "true";
			NextDiag.TempNode = "Total_info";
		break;
		// <-- информационный блок
		
		case "capper":
			dialog.text = "Was brauchst du auf den Territorien der Rivados, Weißer?";
			link.l1 = "Mein Name ist "+GetFullName(pchar)+" und ich bin hier auf Befehl von Admiral Dodson. Ich muss mit Black Eddie sprechen. Wie ich verstehe, bist du es.";
			link.l1.go = "capper_1";
		break;
		
		case "capper_1":
			dialog.text = "Ja, ich bin Edward Black, auch bekannt als Schwarzer Eddie. Sag mir, was braucht der Admiral von mir.";
			link.l1 = "Es gibt einen Mann auf der 'Tartarus' namens Chimiset. Der Admiral ist bereit, ihn freizulassen.";
			link.l1.go = "capper_2";
		break;
		
		case "capper_2":
			dialog.text = "Das ist sehr gute Nachrichten. Chimiset ist unser spiritueller Führer und alle Rivados vermissen ihn. Aber ich verstehe, dass der Admiral etwas im Austausch für seine Freiheit will, richtig?";
			link.l1 = "Nichts. Er möchte ihn nur aus reiner Güte befreien. Aber es gibt ein Problem...";
			link.l1.go = "capper_3";
		break;
		
		case "capper_3":
			dialog.text = "Mach weiter, weißer Mann.";
			link.l1 = "Der ehemalige Bootsmann des Admirals, der jetzige Gefängniswärter Chad Kapper, trat den Narwalen bei, wurde zum Schurken und ist jetzt außerhalb der Kontrolle des Admirals. Wir wissen, dass Chad plant, Chimiset zu töten. Der Admiral möchte nicht, dass das passiert. Wir bieten Ihnen eine kombinierte Operation an, um den Verräter zu beseitigen und Ihren Mann zu befreien.";
			link.l1.go = "capper_4";
		break;
		
		case "capper_4":
			dialog.text = "Deine Worte klingen ein bisschen seltsam, aber erzähl weiter. Ist Chimiset in Schwierigkeiten?";
			link.l1 = "Ja. Chad plant, ihn zu töten. Kapper wird die Narwale benutzen, um die Kontrolle über die Stadt zu übernehmen. Wir müssen schnell handeln, wenn wir Chimiset retten wollen, da Chad momentan nichts ahnt. Der Admiral hat alle Wächter aus dem 'Tartarus' abgezogen, der Durchgang ist frei. Hier ist der Schlüssel, der die Tür im Gefängnis öffnet. Nimm ihn.";
			link.l1.go = "capper_5";
		break;
		
		case "capper_5":
			RemoveItems(pchar, "key_capper", 1);
			dialog.text = "";
			link.l1 = "Sammle deine Männer, geh zum Tartarus und befreie Chimiset. Alle Karten liegen bei dir.";
			link.l1.go = "capper_6";
		break;
		
		case "capper_6":
			dialog.text = "Es riecht nach einer Falle... Und was ist, wenn es einen Hinterhalt gibt? Was ist, wenn der Admiral beschlossen hat, die Rivados niederzuschlagen? Warum kümmert er sich nicht selbst um Kapper?";
			link.l1 = "Dodson sagte, dass Ihnen das Leben von Chimiset wichtig ist... Er hat genug getan: hier ist der Schlüssel und die Wachen sind weg. Sie müssen nur hineingehen, sich um Chad kümmern und Ihren Mann befreien. Sie haben mein Wort, dass es keine Falle gibt. Ja, und noch eine letzte Sache: Der Admiral möchte Chads Kopf im Austausch für Chimisets Leben und Freiheit. Haben wir eine Vereinbarung?";
			link.l1.go = "capper_7";
		break;
		
		case "capper_7":
			dialog.text = "Chimisets Leben ist für die Rivados von unschätzbarem Wert. Wir werden sofort zur 'Tartarus' gehen. Aber du wirst hier als unsere Geisel bleiben. Und wenn es einen Hinterhalt gibt, wirst du die Wut der Rivados spüren!\nZikomo! Bleib in der Nähe der Tür und pass auf unseren Gast auf. Lass ihn nicht raus. Ich werde den Angriff auf die 'Tartarus' selbst führen!";
			link.l1 = "Viel Glück, Eddie. Und denk dran: Ich brauche den Kopf von Chad Kapper!";
			link.l1.go = "capper_8";
		break;
		
		case "capper_8":
			DialogExit();
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_ZikomoNearDoor", 10.0);
			NextDiag.CurrentNode = "chimiset";
		break;
		
		case "chimiset":
			dialog.text = "Chimiset ist frei! Du hast nicht gelogen, Weißer, ich bin bereit, dich einen Freund der Rivados zu nennen!";
			link.l1 = "Ich bin froh. Ist Chad Kapper tot?";
			link.l1.go = "chimiset_1";
		break;
		
		case "chimiset_1":
			dialog.text = "Ich muss um deine Vergebung bitten, weißer Freund: du hast alles für uns getan, aber wir haben dich enttäuscht... Ich habe dich enttäuscht! Dieser verdammte Kapper ist entkommen. Zwei Narwale waren bei ihm. Wir haben sie getötet, aber der schmutzige Kerkermeister ist durch die untere Tür zu den Narwal-Territorien geschwommen.";
			link.l1 = "Verdammt... Wusstest du nicht, dass es zwei Ausgänge aus dem 'Tartarus' gibt?";
			link.l1.go = "chimiset_2";
		break;
		
		case "chimiset_2":
			dialog.text = "Wir haben nicht darüber nachgedacht. Wir haben vom Haupteingang aus angegriffen...";
			link.l1 = "Schade. Ich hatte auf seinen Kopf gezählt. Zu schlimm. Jetzt wird er weiter gegen uns vorgehen.";
			link.l1.go = "chimiset_3";
		break;
		
		case "chimiset_3":
			dialog.text = "Ich gebe meine Schuld zu. Aber wir konnten ihm nicht zu den feindlichen Schiffen folgen. Stattdessen wirst du unsere Freundschaft und unseren Respekt anstelle von Chads Kopf haben. Ab jetzt darfst du unser Territorium frei besuchen. Auch die Weisheit von Chimiset wird dir gut dienen, sprich mit ihm, wenn du etwas brauchst. Sprich mit ihm, wenn du etwas brauchst. Sag auch dem Admiral meine Versicherung, dass ich seine Aktion geschätzt habe.";
			link.l1 = "Gut.";
			link.l1.go = "chimiset_4";
		break;
		
		case "chimiset_4":
			dialog.text = "Warte! Wir haben Chad verloren, aber ich habe einige Papiere auf seinem Schreibtisch gefunden, die er studierte, als wir ankamen. Hier sind sie. Sie könnten Ihnen nützlich sein, weißer Bruder.";
			link.l1 = "Ha! Vielleicht... Chad setzt großes Vertrauen in Papier...";
			link.l1.go = "chimiset_5";
		break;
		
		case "chimiset_5":
			dialog.text = "Du bist immer ein willkommener Gast hier, weißer Freund. Alle Rivados werden davon informiert. Viel Glück!";
			link.l1 = "Das Gleiche gilt für dich, Eddie...";
			link.l1.go = "chimiset_6";
		break;
		
		case "chimiset_6":
			DialogExit();
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "LSC_EddyStay", -1);
			sld = CharacterFromID("Zikomo");
            LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, true);
			GiveItem2Character(pchar, "letter_chad");
			ChangeItemDescribe("letter_chad", "itmdescr_letter_aeva");
			GiveItem2Character(pchar, "letter_chad_1");
			ChangeItemDescribe("letter_chad_1", "itmdescr_letter_axel");
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			// // ривадосы не будут останавливать где просят пароль
			pchar.questTemp.Saga.SharkHunt = "dodson_whiskey"; // к Акуле
			sld = CharacterFromID("Dodson");
			sld.dialog.currentnode = "Chad_escape"; // ноду Акуле
			AddQuestRecord("SharkHunt", "33");
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", true); // закрыть вход к Дональду Гринспи
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("Have you heard the latest news? The Rivados' insolence is out of control, they have attacked the admiral's prison and released their wizard!", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("Just think about it - those uppity Rivados dared to attack the 'Tartarus'! They say that the jailer, Chad Kapper, has escaped to the Narwhals...", "LostShipsCity", 3, 2, "LSC", "");
			AddSimpleRumourCityTip("This is the height of impudence, isn't it? Attacking a military facility of the admiral! Aye, looks like Black Eddie is getting stronger...", "LostShipsCity", 3, 2, "LSC", "");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
