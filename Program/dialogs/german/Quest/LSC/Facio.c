// посредник-дипломат кланов Джузеппе Фацио
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Hallo, hallo... Bist du neu hier? Ich erinnere mich nicht an dein Gesicht. Lass mich mich vorstellen - Ich bin Giuseppe Fazio, ein Spezialist für die Lösung von Problemen auf dieser kleinen Insel.";
				link.l1 = TimeGreeting()+". Mein Name ist "+GetFullName(pchar)+". Sie haben recht, ich bin neu hier. Verzeihen Sie meine Neugier - aber welche Art von Problemen lösen Sie?";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ach, du schon wieder, Lieber "+pchar.name+"! Was führt dich zu meinem bescheidenen Haus?";
				if (CheckAttribute(pchar, "GenQuest.NarvalConflict") || CheckAttribute(pchar, "GenQuest.RivadosConflict") || CheckAttribute(pchar, "GenQuest.SharkConflict"))
				{
					link.l10 = "Fazio, ich habe einen ernsten Konflikt mit einem Clan. Ich muss dieses Problem lösen.";
					link.l10.go = "conflict";
				}
				// --> квестовые ветки
				if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_3")
				{
					link.l4 = "Giuseppe, ich suche einen Mann namens Adolf Barbier. Mir wurde gesagt, dass du kürzlich mit ihm in der Taverne getrunken hast...";
					link.l4.go = "adolf";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && pchar.questTemp.LSC.Drink == "begin")
				{
					link.l5 = "Giuseppe, man sagt, du seist vollkommen widerstandsfähig gegenüber Getränken. Egal wie viel du trinkst, du stehst immer noch auf deinen Füßen.";
					link.l5.go = "drink";
				}
				if (CheckAttribute(pchar, "questTemp.LSC.Drink") && PCharDublonsTotal() >= 100 && pchar.questTemp.LSC.Drink == "wait")
				{
					link.l5 = "Ich bin bereit, dein Spiel zu spielen. Hier ist mein Einsatz.";
					link.l5.go = "drink_4";
				}
				// <-- квестовые ветки
				if (CheckAttribute(npchar, "quest.parol"))
				{
					link.l1 = "Ich möchte das aktuelle Passwort der Clans wissen, um in ihre Gebiete zu gelangen.";
					link.l1.go = "parol_choice";
				}
				link.l2 = LinkRandPhrase("Hast du etwas Interessantes zu sagen?","Gibt es Neuigkeiten auf der Insel?","Wirst du mir die neuesten Klatsch und Tratsch erzählen?");
				link.l2.go = "rumours_LSC";
				link.l3 = "Nichts Besonderes, Giuseppe. Ich wollte dich nur sehen.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "Alle Arten, mein Lieber, alle Arten. Zum Beispiel, ich mache die Dinge zwischen Admiral und Clans glatt. Wie du vielleicht schon weißt, sind Rivados, Narwale und Admiral gegenseitige Feinde. Ich fungiere als Vermittler, wenn die Dinge kompliziert werden.\nAußerdem spiele ich oft eine neutrale Seite, wenn der Admiral Proviant an die Clans verkauft. Aber das ist nur ein kleiner Teil meines Geschäfts. Also wenn du Probleme mit Rivados oder Narwalen hast - zögere nicht, um meine Hilfe zu bitten, wir werden sehen, was getan werden kann.";
			link.l1 = "Gut. Ich werde das in Betracht ziehen.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// пароли
		case "parol_choice":
			dialog.text = "Welcher Clan?";
			link.l1 = "Narwale.";
			link.l1.go = "parol_nrv";
			link.l2 = "Rivados.";
			link.l2.go = "parol_rvd";
		break;
		
		case "parol_nrv":
			dialog.text = "Möchten Sie Donald Greenspen sehen, habe ich recht?";
			link.l1 = "Richtig. Kennst du also das Passwort?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Narwals";
			sTotalTemp = sNrvParol;
		break;
		
		case "parol_rvd":
			dialog.text = "Möchten Sie Black Eddie sehen, habe ich recht?";
			link.l1 = "So etwas in der Art. Kennst du also das Passwort?";
			link.l1.go = "parol";
			pchar.questTemp.LSC.parol = "Rivados";
			sTotalTemp = sRvdParol;
		break;
		
		case "parol":
			if (!CheckAttribute(npchar, "quest.parolrules"))
			{
				dialog.text = "Sicher! Aber lassen Sie mich Ihnen zuerst einige Details geben. Passwörter enthalten nur ein Wort und ändern sich jede Woche. Jeden siebten, vierzehnten, einundzwanzigsten und achtundzwanzigsten Tag des Monats\nAchten Sie also auf das aktuelle Datum, um Fehler zu vermeiden. Schließlich, wie Sie verstehen müssen, ist es keine Wohltätigkeit. Fünfzig Dublonen für ein Passwort. Denken Sie daran, nur Dublonen.";
				link.l1 = "Fünfzig Dublonen? Das ist eine riesige Summe!";
				link.l1.go = "parol_1";
			}
			else
			{
				dialog.text = "Sicher, mein Junge. Du kennst den Preis. Hast du fünfzig Dublonen?";
				if (PCharDublonsTotal() >= 50)
				{
					link.l1 = "Ja. Nehmen Sie Ihre Münzen.";
					link.l1.go = "parol_pay";
				}
				link.l2 = "Leider nicht. Vielleicht später...";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "parol_1":
			dialog.text = "Nun-nun, mein Junge, beruhige dich. Sei nicht gierig, vertrau mir: Ich kenne den wahren Preis meiner Informationen. Du wirst nicht einfach nur um die Schiffe herumlaufen "+pchar.questTemp.LSC.parol+" richtig? Richtig. Also musst du bereit sein, etwas Geld zu verlieren... Also, bist du bereit, fünfzig Dublonen zu bezahlen?";
			if (PCharDublonsTotal() >= 50)
			{
				link.l1 = "Ja. Nimm deine Münzen.";
				link.l1.go = "parol_pay";
			}
			link.l2 = "Leider habe ich kein solches Geld. Vielleicht später...";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
			npchar.quest.parolrules = "true";
		break;
		
		case "parol_pay":
			RemoveDublonsFromPCharTotal(50);
			dialog.text = "Großartig! Schön, Geschäfte mit Ihnen zu machen. Das aktuelle Passwort für "+pchar.questTemp.LSC.parol+" ist: '"+sTotalTemp+"'. Merk es dir gut und mach keinen Fehler oder ich gebe keinen einzigen Pfennig für dein Leben.";
			link.l1 = "Ich weiß, ich weiß... Danke!";
			link.l1.go = "exit";
			AddQuestRecord("LSC", "parol");
			AddQuestUserData("LSC", "sText", pchar.questTemp.LSC.parol);
			AddQuestUserData("LSC", "sParol", sTotalTemp);
			if (pchar.questTemp.LSC.parol == "Rivados") pchar.questTemp.LSC.RParol_bye = "true";
			else pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "adolf":
			dialog.text = "Ach, aber natürlich, mein guter alter Adolfo! Ja, ich habe mit ihm gesprochen. Siehst du, mein Lieber, ich war froh, mein Geld zurück zu haben, das Geld, von dem ich dachte, ich würde es nie wieder sehen! Adolfo lieh eine große Summe auf die Sicherheit seiner hervorragenden Flinte und er hatte Schwierigkeiten, mein Geld zurückzugeben\nIch hatte jede Hoffnung aufgegeben, sie zurückzubekommen und wollte diesen Stutzen an unseren geliebten Axel Yost verkaufen. Aber plötzlich brachte mir der liebe Adolfo mein Gold! Es stellte sich heraus, dass er genug Münzen sammeln konnte, nicht nur, um seinen Stutzen einzulösen, sondern auch, um die Kabine von Sessile Gallard am Kopf der 'Santa Florentina' zu kaufen!\nSicher, das ist viel besser als in einem halb überfluteten Laderaum zu leben\nDaher hat Adolfo seine Flinte zurück, ein neues Zuhause und ich habe mein Geld. Warum sollte ich ablehnen, mit ihm zu trinken, besonders wenn er zahlte?";
			link.l1 = "Ach, sicher! Du hattest viel zum Anstoßen. Und kostenlos... Danke, Giuseppe, du hast mir sehr geholfen. Jetzt weiß ich, wo ich Adolf finden kann.";
			link.l1.go = "adolf_1";
		break;
		
		case "adolf_1":
			dialog.text = "Es ist immer meine Freude, Lieber. Aber such nicht nach Adolfo in seiner Kabine, bis der Abend kommt, er ist sehr beschäftigt, läuft mit einigen Geschäften herum... Ja, und besuche mich öfter, lass uns plaudern!";
			link.l1 = "Ich lade dich ein, wenn ich meine eigene Kajüte habe... Lebewohl und viel Glück!";
			link.l1.go = "adolf_2";
		break;
		
		case "adolf_2":
			DialogExit();
			LSC_CreateAdolfClone(); // заменяем Адольфа клоном
			pchar.questTemp.Saga.SharkHunt = "search_mush_4"; //флаг на Адольфа в каюте
			AddQuestRecord("SharkHunt", "14");
		break;
		
		case "whiskey":
			switch (sti(npchar.quest.poisonnode))
			{
				case 1: // у себя
					dialog.text = "Ach? Warum dringen Sie in meinen Platz ein, als ob es brennen würde? Wer glauben Sie, dass Sie sind??";
					link.l1 = "Deine Gerechtigkeit... Giftmischer!";
					link.l1.go = "whiskey_1";
				break;
				
				case 2: // на Эве
					dialog.text = "Verschone mich! Ich schwöre, sie haben mich gezwungen! Sie haben eine Pistole an meinen...";
					link.l1 = "Schweig. Das weiß ich. Wo ist der letzte Bastard? Wo ist Marcello Zyklop?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
				
				case 3: // у Акулы
					dialog.text = "Ich schwöre, sie haben mich gezwungen! Ich habe dem Admiral schon alles erzählt! Ich konnte ihnen nicht widerstehen, sie würden...";
					link.l1 = "Schweig. Das weiß ich. Wo ist der letzte Bastard? Wo ist Marcello Zyklop?!";
					link.l1.go = "whiskey_3";
					SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
				break;
			}
		break;
		
		case "whiskey_1":
			dialog.text = "Was... was haben Sie gesagt?";
			link.l1 = "Ich weiß alles, du Bastard. Du hast mit Chad Kapper gearbeitet. Du hast dem Admiral ein Fass mit vergiftetem Rum gebracht. Jetzt bete, du elender Tunichtgut...";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "Warte! Halt! Verschone mich! Ich schwöre, sie haben mich gezwungen! Sie hatten eine Pistole gegen meinen...";
			link.l1 = "Schweig still. Das weiß ich. Wo ist der letzte Bastard? Wo ist Marcello Zyklop?!";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "Ich... Ich.... Ich weiß es nicht!";
			link.l1 = "Du lügst, Abschaum! Das sehe ich. Wo ist Zyklop?";
			if (pchar.questTemp.LSC.Mary == "die") link.l1.go = "whiskey_10"; // ушел на Флерон
			else link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "Er... er hat einen Befehl von Kapper erhalten und ist gegangen. Ich weiß nicht, wo er ist!";
			link.l1 = "Wieder lügst du. Du weißt alles. Sei kein Feigling, du dreckiges Geschöpf - Kapper ist tot und er wird dir keinen Schaden zufügen. Aber wenn du mir nicht sagst, wo Marcello ist - werde ich dich jetzt wie ein Schwein schlachten! Was hat Chad dem Zyklop befohlen?";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = "Er hat ihn geschickt, um... die Rote Maria zu töten.";
			link.l1 = "Was?! Sprich jetzt, wie will er das machen? Es ist unmöglich, in ihre Kabine zu kommen! Wie plant er, sie zu töten?!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			dialog.text = "Er wird in Jürgens Kabine gelangen, während der Schmied draußen ist. Dann wird er zum unteren Teil des Laderaums gehen, ihn überqueren und Marys Kabine erreichen\nDann wird er nur noch warten müssen, bis das Mädchen ihm den Rücken zukehrt oder einschläft. Das hat Chad mir erzählt. Ich schwöre, ich weiß nichts weiter!";
			link.l1 = "Das wird genug sein. Wann ist er gegangen? Wann, frage ich dich, ist Zyklop zur 'Ceres Schmiede' gegangen?";
			link.l1.go = "whiskey_7";
		break;
		
		case "whiskey_7":
			dialog.text = "Er muss bereits in Jürgens Kabine sein... oder sich im Laderaum befinden...";
			link.l1 = "Verdammt! Ich habe keine Zeit, um die Insel herum zu schwimmen! Sag mir das Passwort für die Narwale Schiffe! Sprich, und wenn du mich belügst, werde ich sowieso am Leben bleiben, aber du wirst mit Sicherheit sterben!";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "'"+sNrvParol+"'...";
			link.l1 = "Verstanden. Beten Sie jetzt, dass das Mädchen überlebt.";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			NextDiag.CurrentNode = "whiskey_repeat";
			pchar.quest.LSC_RescueMary.win_condition.l1 = "location";
			pchar.quest.LSC_RescueMary.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_RescueMary.function = "LSC_RescueMary";
			AddQuestRecord("SharkHunt", "46");
			AddQuestUserData("SharkHunt", "sParol", sNrvParol);
			pchar.questTemp.LSC.NParol_bye = "true";
		break;
		
		case "whiskey_repeat":
			dialog.text = "Ich habe dir schon alles erzählt, was ich wusste! Ich schwöre!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "whiskey_repeat";
		break;
		
		case "whiskey_10":
			dialog.text = "Er... Er ist irgendwo im 'Fleron'. Chad hat ihm befohlen, sich dort zu verstecken und auf seine nächsten Befehle zu warten.";
			link.l1 = "Ich verstehe. Es wäre besser, es wäre die Wahrheit...";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.LSC_FindCyclop.win_condition.l1 = "location";
			pchar.quest.LSC_FindCyclop.win_condition.l1.location = "FleuronTavern";
			pchar.quest.LSC_FindCyclop.function = "LSC_SetCyclop_Fl";
			NextDiag.CurrentNode = "whiskey_repeat";
			AddQuestRecord("SharkHunt", "51");
			
		break;
		
		// --> конфликты
		case "conflict":
			dialog.text = "Ist das so? Nun, mein Junge, welcher Clan bereitet dir Ärger?";
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				link.l1 = "Narwale.";
				link.l1.go = "narval";
				npchar.quest.clan = "narval";
			}
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				link.l2 = "Rivados.";
				link.l2.go = "rivados";
				npchar.quest.clan = "rivados";
			}
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				link.l3 = "Admiralspiraten.";
				link.l3.go = "shark";
				npchar.quest.clan = "shark";
			}
			link.l4 = "Keineswegs. Ich habe nur gescherzt, Giuseppe, mir geht es gut.";
			link.l4.go = "exit";
		break;
		
		case "narval":
			npchar.quest.price = sti(pchar.GenQuest.NarvalConflict)*50;
			if (sti(pchar.GenQuest.NarvalConflict) < 3) dialog.text = "Nun, es ist eigentlich kein Konflikt, nur ein kleines Missverständnis, he-he. "+sti(npchar.quest.price)+"  Dublonen und dein Problem wird innerhalb eines Tages gelöst sein.";
			else
			{
				if (sti(pchar.GenQuest.NarvalConflict) >= 3 && sti(pchar.GenQuest.NarvalConflict) < 10) dialog.text = "Sicher, ich habe davon gehört. Du hast eine große Unordnung angerichtet, mein Lieber. Aber es gibt einen Ausweg. "+sti(npchar.quest.price)+" Dublonen und dein Problem wird innerhalb eines Tages gelöst sein.";
				else dialog.text = "Die gesamte Insel ist sich des Gemetzels bewusst, das du angerichtet hast. Es wird nicht einfach sein, dir zu helfen, aber es gibt eine Chance. "+sti(npchar.quest.price)+" Doubloons und ich werde versuchen, dein Problem zu lösen.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "Hier, nimm deine Münzen und komm damit klar.";
				link.l1.go = "pay";
			}
			link.l2 = "Leider habe ich gerade nicht genug Dublonen bei mir. Aber ich werde sie später bringen, und wir werden wieder sprechen.";
			link.l2.go = "exit";
		break;
		
		case "rivados":
			npchar.quest.price = sti(pchar.GenQuest.RivadosConflict)*50;
			if (sti(pchar.GenQuest.RivadosConflict) < 3) dialog.text = "Nun, es ist eigentlich kein Konflikt, nur ein kleines Missverständnis, he-he. "+sti(npchar.quest.price)+"  Dublonen und dein Problem wird in einem Tag gelöst sein.";
			else
			{
				if (sti(pchar.GenQuest.RivadosConflict) >= 3 && sti(pchar.GenQuest.RivadosConflict) < 10) dialog.text = "Sicher, ich habe davon gehört. Du hast ein großes Durcheinander angerichtet, mein Lieber. Aber es gibt einen Ausweg. "+sti(npchar.quest.price)+"  Dublonen und dein Problem wird in einem Tag gelöst sein.";
				else dialog.text = "Die ganze Insel ist sich des Gemetzels bewusst, das du angerichtet hast. Es wird nicht einfach sein, dir zu helfen, aber es gibt eine Chance. "+sti(npchar.quest.price)+" Dublonen und ich werde versuchen, Ihr Problem zu lösen.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "Hier, nimm deine Münzen und komm damit klar.";
				link.l1.go = "pay";
			}
			link.l2 = "Leider habe ich im Moment nicht genug Dublonen bei mir. Aber ich werde sie später bringen, und wir werden wieder reden.";
			link.l2.go = "exit";
		break;
		
		case "shark":
			npchar.quest.price = sti(pchar.GenQuest.SharkConflict)*50;
			if (sti(pchar.GenQuest.SharkConflict) < 3) dialog.text = "Nun, es ist eigentlich kein Konflikt, nur ein kleines Missverständnis, he-he. "+sti(npchar.quest.price)+" Doubloons und Ihr Problem wird innerhalb eines Tages gelöst sein.";
			else
			{
				if (sti(pchar.GenQuest.SharkConflict) >= 3 && sti(pchar.GenQuest.SharkConflict) < 10) dialog.text = "Sicher, ich habe davon gehört. Du hast eine große Unordnung angerichtet, mein Lieber. Aber es gibt einen Ausweg. "+sti(npchar.quest.price)+" Dublonen und Ihr Problem wird in einem Tag gelöst sein.";
				else dialog.text = "Die ganze Insel ist sich des Gemetzels bewusst, das du angerichtet hast. Es wird nicht leicht sein, dir zu helfen, aber es gibt eine Chance."+sti(npchar.quest.price)+" Dublonen und ich werde versuchen, Ihr Problem zu lösen.";
			}
			if (PCharDublonsTotal() >= sti(npchar.quest.price))
			{
				link.l1 = "Hier, nimm deine Münzen und komm damit klar.";
				link.l1.go = "pay";
			}
			link.l2 = "Leider habe ich gerade nicht genug Dublonen bei mir. Aber ich werde sie später bringen, und wir werden wieder reden.";
			link.l2.go = "exit";
		break;
		
		case "pay":
			RemoveDublonsFromPCharTotal(sti(npchar.quest.price));
			PlaySound("interface\important_item.wav");
			Log_Info("You have given "+sti(npchar.quest.price)+" doubloons");
			dialog.text = "Herrlich. Nun setzen Sie sich und ruhen Sie sich aus. Es wäre besser, wenn Sie in meiner Kajüte bleiben, bis ich Ihr Problem gelöst habe. Ich möchte nicht, dass Sie es noch schlimmer machen, mein Lieber.";
			link.l1 = "Gut...";
			link.l1.go = "peace";
		break;
		
		case "peace":
			DialogExit();
			GetCharacterPos(pchar, &locx, &locy, &locz);
			pchar.locx = locx;
			pchar.locy = locy;
			pchar.locz = locz;
			SetLaunchFrameFormParam("One day later..."+ NewStr() +"Fazio has dealt with the conflict", "Reload_To_Location", 0.1, 5.0);
			SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
			WaitDate("", 0, 0, 1, 3, 10); //крутим время
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
			switch (npchar.quest.clan)
			{
				case "narval":
					DeleteAttribute(pchar, "GenQuest.NarvalConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") || !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false);//открыть вход к Дональду
					LAi_group_SetRelation("LSC_NARVAL", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "rivados":
					DeleteAttribute(pchar, "GenQuest.RivadosConflict"); // мирим
					if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend") || !CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) LocatorReloadEnterDisable("LostShipsCity_town", "reload33", false);//открыть вход к Эдди
					LAi_group_SetRelation("LSC_RIVADOS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
				
				case "shark":
					DeleteAttribute(pchar, "GenQuest.SharkConflict"); // мирим
					LSC_OpenSanAvgustinDoors(); // открыть сан-августин
					LSC_OpenTartarusDoors(); // открыть тартарус
					LAi_group_SetRelation("LSC_SHARK", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
				break;
			}
			DeleteAttribute(npchar, "quest.clan");
			DeleteAttribute(npchar, "quest.price");
		break;
		
		// --> пей до дна
		case "drink":
			dialog.text = "Komm schon, mein Junge! Sie lügen alle, he-he. Mein Kopf ist nur ein bisschen härter als ein durchschnittlicher Kopf, aber ich bin genau wie du ein Mensch, also werde ich auch mit Rum betrunken. Die Leute trinken Rum, um betrunken zu werden, das ist sein einziger Zweck. Hast du darüber nachgedacht, Lieber?";
			link.l1 = "Ganz richtig.";
			link.l1.go = "drink_1";
		break;
		
		case "drink_1":
			dialog.text = "Möchtest du ein lustiges Spiel mit mir spielen? Es heißt 'Trink bis zum Boden!', ha-ha! Ich bin sicher, du hast schon davon gehört. Habe ich Recht?";
			link.l1 = "Ja, es gab einige Gerüchte darüber... Ich würde es 'Gesicht auf dem Tisch' nennen.";
			link.l1.go = "drink_2";
		break;
		
		case "drink_2":
			dialog.text = "Ha-ha-ha, mein lieber Junge, du hast den alten Mann zum Lachen gebracht, was soll ich sonst sagen! 'Gesicht auf dem Tisch!' Ich werde es mir merken... Was sagst du dazu? Spielst du um hundert Dublonen?";
			link.l1 = "Hundert Dublonen?";
			link.l1.go = "drink_3";
		break;
		
		case "drink_3":
			dialog.text = "Ja, und der Verlierer zahlt für die Getränke. Abgemacht?";
			if (PCharDublonsTotal() >= 100)
			{
				link.l1 = "Ja, Abmachung. Hier ist mein Einsatz.";
				link.l1.go = "drink_4";
			}
			link.l2 = "Hm. Ich habe nicht so viele Dublonen.";
			link.l2.go = "drink_wait";
		break;
		
		case "drink_wait":
			dialog.text = "Nun, komm und besuch mich, wenn du sie hast, und wir werden spielen!";
			link.l1 = "Gut...";
			link.l1.go = "exit";
			pchar.questTemp.LSC.Drink = "wait";
		break;
		
		case "drink_4":
			RemoveDublonsFromPCharTotal(100);
			Log_Info("You have given 100 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "Ausgezeichnet, mein Lieber! Dann sehen Sie mich um neun Uhr abends in der Taverne von Sancho! Ja, Ihr Einsatz bleibt bei mir, wenn Sie zu spät kommen, das ist eine der Regeln. Aber Sie werden nicht zu spät kommen, mein Junge, oder?";
			link.l1 = "Sicher, Giuseppe. Bereite dich auf eine Flaschenschlacht vor!";
			link.l1.go = "drink_5";
		break;
		
		case "drink_5":
			dialog.text = "Und du, und du, meine Liebe! Gesicht auf den Tisch! Ha-ha!";
			link.l1 = "Bis neun in der Taverne!";
			link.l1.go = "drink_6";
		break;
		
		case "drink_6":
			DialogExit();
			pchar.questTemp.LSC.Drink = "start";
			pchar.quest.LSC_DrinkOver.over = "yes"; //снять таймер
			pchar.quest.LSC_Drink.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink.win_condition.l1.date.hour  = 21.0;
			pchar.quest.LSC_Drink.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink.function = "LSC_DrinkPrepare";
			pchar.quest.LSC_Drink_Over.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.hour  = 23.0;
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink_Over.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink_Over.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "2");
		break;
		
		case "drink_8":
			dialog.text = "Nun, meine Liebe, bist du bereit, einen Tisch zu küssen, he-he? Der gute Sancho hat uns bereits Rum gebracht. Ich muss dir die Regeln wohl nicht erklären? Sie sind ziemlich einfach: Wir trinken die gleiche Flasche, bis einer von uns unter dem Tisch liegt.\nJa, wir können reden, wir sollten reden! Mit anständigen Leuten zu reden ist großartig, nicht wahr? Und wenn du gewinnst, kannst du deinen Preis von Sancho abholen. Bereit?";
			link.l1 = "Ich würde ja sagen. Lass uns anfangen, Giuseppe!";
			link.l1.go = "drink_9";
		break;
		
		case "drink_9":
			DialogExit();
			pchar.questTemp.LSC.Drink = "go";
			pchar.quest.LSC_Drink_Over.over = "yes"; //снять таймер
			ChangeCharacterAddressGroup(pchar, "FleuronTavern", "quest", "sit1");
			LAi_SetActorType(pchar);
			LAi_ActorSetSitMode(pchar);
			ChangeCharacterAddressGroup(npchar, "FleuronTavern", "quest", "sit2");
			LAi_SetActorType(npchar);
			LAi_ActorSetSitMode(npchar);
			DoQuestFunctionDelay("LSC_DrinkGo", 0.6);
		break;
		
		case "drunk":
			dialog.text = "Fünf-zehn Männer au-auf dem Toten... hic! Aha! Yo-ho-ho-kha... Und... Flasche...";
			link.l1 = "Herrlich...";
			link.l1.go = "exit";
			NextDiag.TempNode = "drunk";
		break;
		// <-- пей до дна
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
