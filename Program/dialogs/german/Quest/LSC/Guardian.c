// диалог протекторов, солдат и мушкетеров кланов LSC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Was zum Teufel willst du?";
			link.l1 = "Nein, es ist nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//------------------------------------- фразы гардов нарвалов --------------------------------------------
		// пост нарвалов на проход на Сан-Габриэль
		case "Narval_warning":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Jungs, vorsichtig, da ist der Wahnsinnige! Zu den Waffen!","Der Feind ist hier! Zu den Waffen!","Ach, du bist ein Bastard! Jetzt werden wir dir eine Lektion erteilen!");
				link.l1 = "Verdammt!";
				link.l1.go = "check_parol_fight";
				break;
			}
			ref location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "nrv_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "Halt, Kumpel. Vor uns liegen die Gebiete der Narwale, der Zutritt ist für Fremde verboten. Du kannst nur mit einer Einladung vorbeikommen. Kennst du das Passwort?";
					link.l1 = "Ja.";
					link.l1.go = "Narval_warning_yes";
					link.l2 = "Nein.";
					link.l2.go = "Narval_warning_no";
				}
				else // если друг нарвалам
				{
					dialog.text = "A-ah, "+GetFullName(pchar)+"! Hallo, Freund, uns wurde gesagt, dass du hier frei herumlaufen kannst. Willkommen!";
					link.l1 = "Danke, Freund!";
					link.l1.go = "exit";
				}
				location.nrv_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "Ich hoffe, du hast das Passwort nicht vergessen...";
					link.l1 = "Mach dir keine Sorgen...";
					link.l1.go = "exit";
				}
				else // если друг нарвалам
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! Wie geht es dir?";
					link.l1 = "Gut, danke!";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Narval_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Narval_warning_yes":
			dialog.text = "Dann geh und sag das dem harten Kerl da drüben. Versuch nicht, ihn zu betrügen, unsere Jungs mit Musketen wissen, was zu tun ist. Also, wenn du irgendwelche Tricks planst - du solltest dich besser umdrehen und gehen. Jetzt. Ich habe dich gewarnt.";
			link.l1 = "Gut, Freund. Ich habe es verstanden.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_no":
			dialog.text = "Dann haben Sie hier nichts zu tun, wenn Sie nicht vorhaben, Ihr Leben zu beenden, natürlich. Oder du machst nur Witze, huh? Machst du Witze mit mir? Eigentlich ist es mir egal. Geh runter, meine Aufgabe ist es zu warnen, aber nicht aufzuhalten. Du wirst nicht zurückkommen, wenn du das Passwort nicht kennst.";
			link.l1 = "Gut, Kumpel. Ich habe es verstanden.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "Was brauchst du noch? Geh runter zur 'San Gabriel' oder verschwinde!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Es tut mir leid, "+pchar.name+", aber ich bin im Dienst. Belästige mich nicht, Kumpel. Geh weiter!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_parol":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Jungs, Vorsicht, da ist der Irre! Zu den Waffen!","Feind ist hier! Zu den Waffen!","Ach, du bist ein Bastard! Jetzt werden wir dir eine Lektion erteilen!");
				link.l1 = "Verdammt!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "Es tut mir leid, "+pchar.name+", aber ich bin im Dienst. Belästige mich nicht, Kumpel. Zieh weiter!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_parol";
				break;
			}
			dialog.text = "Bleib genau da stehen, wo du bist! Du gehörst nicht zu uns!";
			link.l1 = "Ich stehe, stehe.";	
			link.l1.go = "check_parol";
		break;
		
		case "check_parol":
			dialog.text = "Sag ein Passwort und tu es klar und laut.";
			if (CheckAttribute(pchar, "questTemp.LSC.NParol_bye"))
			{
				link.l1 = StringFromKey("QuestsUtilite_" + (281 + rand(11)));
				link.l1.go = "check_parol_wrong";
				link.l2 = StringFromKey("QuestsUtilite_" + (293 + rand(11)));
				link.l2.go = "check_parol_wrong";
				link.l3 = StringFromKey("QuestsUtilite_" + (305 + rand(11)));
				link.l3.go = "check_parol_wrong";
				link.l4 = StringFromKey("QuestsUtilite_" + (317 + rand(11)));
				link.l4.go = "check_parol_wrong";
				
				switch (rand(3))
				{
					case 0:
						link.l1 = sTotalTemp;
						link.l1.go = "check_parol_1";
					break;

					case 1:
						link.l2 = sTotalTemp;
						link.l2.go = "check_parol_1";
					break;

					case 2:
						link.l3 = sTotalTemp;
						link.l3.go = "check_parol_1";
					break;

					case 3:
						link.l4 = sTotalTemp;
						link.l4.go = "check_parol_1";
					break;
				}
			}
			else
			{
				link.l1 = "Welches Passwort? Lass mich durch, oder...";
				link.l1.go = "check_parol_wrong";
			}
		break;
		
		case "check_parol_1":
			dialog.text = "Gut, Sie dürfen fortfahren.";
			link.l1 = "Danke, Kumpel...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			pchar.questTemp.LSC.parol_nrv = "true";
		break;
		
		case "check_parol_wrong":
			dialog.text = "Hm... Jungs! Wir haben Gesellschaft!";
			link.l1 = "Scheiße!";
			link.l1.go = "check_parol_fight";
		break;
		
		case "check_parol_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Narval_parol_repeat":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Jungs, vorsichtig, da ist der Psycho! Zu den Waffen!","Der Feind ist hier! Zu den Waffen!","Ach, du bist ein Schuft! Jetzt werden wir dir eine Lektion erteilen!");
				link.l1 = "Verdammt!";
				link.l1.go = "check_parol_fight";
				break;
			}
			dialog.text = "Geh weiter! Steh hier nicht rum!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
		break;
		
		// у резиденции
		case "Narval_residence":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Jungs, vorsichtig, da ist der Psycho! Zu den Waffen!","Der Feind ist hier! Zu den Waffen!","Ach, du bist ein Bastard! Jetzt werden wir dir eine Lektion erteilen!");
				link.l1 = "Verdammt!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // диалог от времени суток. лесник
			    {
					dialog.text = TimeGreeting()+", "+pchar.name+"! Die Tür ist offen, falls du den Boss sehen willst.";
					link.l1 = "Gut...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else
				{
                    dialog.text = TimeGreeting()+", "+pchar.name+"! Falls du den Boss sehen willst, er schläft jetzt. Komm morgen wieder.";
					link.l1 = "Gut...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");	
                }					
				break;	
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Freunde der Schwarzen haben hier nichts zu suchen. Eine direkte Anordnung vom Boss!";
				if (CheckAttribute(pchar, "questTemp.LSC.Donald_enter"))
				{
					link.l1 = "Er wird mich sehen müssen. Ihr habt echt Ärger, Leute. Ich bin hier auf offiziellen Befehl des Admirals. Also öffnet verdammt noch mal die Tür!";
					link.l1.go = "negotiations";
				}
				else
				{
				link.l1 = "Ich kann nicht sagen, dass ich ihn auch sehen möchte...";
				link.l1.go = "exit";
				}
				NextDiag.TempNode = "Narval_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "Möchten Sie den Chef sehen? Hm, nun, dann gehen Sie weiter.";
			link.l1 = "Danke, dass du mir erlaubt hast...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else
			{
            dialog.text = "Möchtest du den Boss sehen? Keine Besuche mehr heute. Komm morgen wieder.";
			link.l1 = "In Ordnung...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Narval_soldier":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Jungs, vorsichtig, da ist der Psycho! Zu den Waffen!","Der Feind ist hier! Zu den Waffen!","Ach, du bist ein Schuft! Jetzt werden wir dir eine Lektion erteilen!");
				link.l1 = "Verdammt!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Wie geht es Ihnen?";
				link.l1 = "Mir geht's gut, danke...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Hör zu, Kumpel, ich bin nicht in Stimmung zu reden. Zieh weiter...";
				link.l1 = "Gut.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_soldier";
		break;
		
		case "negotiations":
			dialog.text = "Nun-nun... Beruhigen Sie sich. Sie hätten zuerst sagen sollen, dass Sie vom Admiral kommen. Sehen Sie, es gibt verschiedene Leute, die hier herumwandern...";
			link.l1 = "Bist du endlich bereit, mich durchzulassen? Danke!";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			DialogExit();
			NextDiag.CurrentNode = "negotiations_2";
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false); // открыть вход к Дональду Гринспи
		break;
		
		case "negotiations_2":
			dialog.text = "Geh weiter, du darfst...";
			link.l1 = "Oh, wirklich? Kann es nicht glauben.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_2";
		break;
		
//------------------------------------- фразы гардов ривадос --------------------------------------------
		// пост ривадос на проход на Фурию и Веласко
		case "Rivados_warning":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Jungs, Vorsicht, da ist der aggressive Psycho! Zu den Waffen!","Der Feind ist hier! Zu den Waffen!","Ach, du bist ein kranker Bastard! Jetzt werden wir dir eine Lektion erteilen!");
				link.l1 = "Verdammt!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "rvd_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "Halt! Die Gebiete hinter mir gehören zum Rivados-Klan, Fremde wie du dürfen ohne Einladung nicht durch. Kennst du das Passwort?";
					link.l1 = "Ja.";
					link.l1.go = "Rivados_warning_yes";
					link.l2 = "Nein.";
					link.l2.go = "Rivados_warning_no";
				}
				else // если друг ривадос
				{
					dialog.text = "Ach, "+GetFullName(pchar)+"! Froh dich zu sehen! Uns wurde mitgeteilt, dass du dich hier frei bewegen kannst. Willkommen!";
					link.l1 = "Danke, Freund!";
					link.l1.go = "exit";
				}
				location.rvd_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "Ich hoffe, dass du das Passwort nicht vergessen hast...";
					link.l1 = "Mach dir keine Sorgen...";
					link.l1.go = "exit";
				}
				else // если друг ривадос
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! Wie geht es dir?";
					link.l1 = "Mir geht's gut, danke...";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_warning_yes":
			dialog.text = "Du kannst dann gehen. Dieser Bursche wird ein Passwort von dir verlangen. Du solltest jetzt besser gehen, wenn du vorhast, uns zu betrügen. Ich habe dich gewarnt.";
			link.l1 = "Gut, Kumpel. Ich habe es verstanden.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_no":
			dialog.text = "Ho-ho! Entweder bist du sehr mutig oder sehr dumm, wenn du uns ohne Passwort besuchen kommst. Oder machst du nur Witze? Mach weiter. Ich bin hier um zu warnen, nicht um zu stoppen. Sei vorsichtig, wenn du das Passwort wirklich nicht kennst!";
			link.l1 = "Gut, Kumpel. Ich habe es verstanden.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Nun, was willst du? Mach weiter oder verschwinde!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Es tut mir leid, "+pchar.name+", aber ich bin im Dienst. Eddie will nicht, dass ich zu viel rede.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_parol":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Jungs, vorsichtig, da ist der aggressive Psycho! Zu den Waffen!","Der Feind ist hier! Zu den Waffen!","Ach, du bist ein verdammter Schurke! Jetzt werden wir dir eine Lektion erteilen!");
				link.l1 = "Verdammt!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Es tut mir leid, "+pchar.name+", aber ich bin im Dienst. Eddie will nicht, dass ich zu viel rede.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_parol";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			dialog.text = "Halt, bleib genau da! Du bist kein Rivados!";
			link.l1 = "Ich möchte durchgehen.";	
			link.l1.go = "Rcheck_parol";
		break;
		
		case "Rcheck_parol":
			dialog.text = "Dann sag ein Passwort und mach es laut und klar.";
			if (CheckAttribute(pchar, "questTemp.LSC.RParol_bye"))
			{
				link.l1 = StringFromKey("QuestsUtilite_" + (281 + rand(11)));
				link.l1.go = "Rcheck_parol_wrong";

				link.l2 = StringFromKey("QuestsUtilite_" + (293 + rand(11)));
				link.l2.go = "Rcheck_parol_wrong";

				link.l3 = StringFromKey("QuestsUtilite_" + (305 + rand(11)));
				link.l3.go = "Rcheck_parol_wrong";

				link.l4 = StringFromKey("QuestsUtilite_" + (317 + rand(11)));
				link.l4.go = "Rcheck_parol_wrong";
				
				switch (rand(3))
				{
					case 0:
						link.l1 = sTotalTemp;
						link.l1.go = "Rcheck_parol_1";
					break;

					case 1:
						link.l2 = sTotalTemp;
						link.l2.go = "Rcheck_parol_1";
					break;

					case 2:
						link.l3 = sTotalTemp;
						link.l3.go = "Rcheck_parol_1";
					break;

					case 3:
						link.l4 = sTotalTemp;
						link.l4.go = "Rcheck_parol_1";
					break;
				}
			}
			else
			{
				link.l1 = "Welches Passwort? Lass mich durch, oder...";
				link.l1.go = "Rcheck_parol_wrong";
			}
		break;
		
		case "Rcheck_parol_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[3]);
			dialog.text = "Richtig. Geh weiter.";
			link.l1 = "Danke, Kumpel...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			pchar.questTemp.LSC.parol_rvd = "true";
		break;
		
		case "Rcheck_parol_wrong":
			dialog.text = "Ha-ha! Wir haben hier einen Gast! Zeigen wir ihm, wer wir sind!";
			link.l1 = "Scheiße!";
			link.l1.go = "Rcheck_parol_fight";
		break;
		
		case "Rcheck_parol_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Rivados_parol_repeat":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Jungs, Vorsicht, da ist der aggressive Psycho! Zu den Waffen!","Der Feind ist hier! Zu den Waffen!","Ach, du bist ein kranker Bastard! Jetzt werden wir dir eine Lektion erteilen!");
				link.l1 = "Verdammt!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			dialog.text = "Steh nicht hier rum, geh weiter!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
		break;
		
		// у резиденции
		case "Rivados_residence":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Jungs, vorsichtig, da ist der aggressive Psychopath! Zu den Waffen!","Der Feind ist hier! Zu den Waffen!","Ach, du bist ein kranker Bastard! Jetzt werden wir dir eine Lektion erteilen!");
				link.l1 = "Verdammt!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
				{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Die Tür steht offen, falls du Eddie und Chimiset besuchen möchtest. Sie werden sich freuen, dich zu sehen.";
				link.l1 = "Gut...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else // лесник - режим пропуска 
				{	
				dialog.text = TimeGreeting()+", "+pchar.name+"! Falls du Eddie und Chimiset sehen willst, sie ruhen bereits. Komme am Morgen zurück, sie werden sich freuen, dich zu sehen.";
				link.l1 = "Gut...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Es gibt nichts für Freunde des Narwals in Eddies Kabine zu tun! Das ist sein direkter Befehl. Verschwinde!";
				link.l1 = "Ich wollte ihn auch nicht sehen...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (GetCharacterIndex("Chimiset") == -1) // Чимисет убит
			{
				dialog.text = "Es gibt nichts für dich zu tun in Eddies Kabine! Das ist sein direkter Befehl. Verzieh dich!";
				link.l1 = "Ich wollte ihn auch nicht sehen...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "Wollen Sie Eddie sehen? Gut, gehen Sie weiter, ich nehme an, er wird eine Minute für Sie übrig haben.";
			link.l1 = "Danke, dass Sie mir erlauben...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else // лесник режим пропуска.
			{
            dialog.text = "Möchtest du Eddie sehen? Keine Besuche mehr heute, komm morgen zurück und er wird eine Minute für dich haben.";
			link.l1 = "In Ordnung...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Rivados_soldier":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Jungs, vorsichtig, da ist der aggressive Psycho! Zu den Waffen!","Der Feind ist hier! Zu den Waffen!","Ach, du bist ein krankes Schwein! Jetzt werden wir dir eine Lektion erteilen!");
				link.l1 = "Verdammt!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Wie geht's dir?";
				link.l1 = "Ich bin gut, danke...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Hör zu, Kumpel, ich bin nicht in Stimmung zu reden. Mach weiter...";
				link.l1 = "Gut.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_soldier";
		break;
//------------------------------------- фразы гардов пиратов --------------------------------------------	
		// у склада
		case "Shark_storage":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Jungs, vorsichtig, da ist der bewaffnete Psycho! Zu den Waffen!","Der Feind ist hier! Zu den Waffen!","Ach, du bist ein Mistkerl! Jetzt werden wir dir in den Arsch treten!");
				link.l1 = "Verdammt!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "Halt! Dies ist ein Sperrgebiet!";
			link.l1 = "Gut, wie du sagst...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_storage";
		break;
		
		// у резиденции
		case "Shark_residence":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Jungs, Vorsicht, da ist der bewaffnete Psycho! Zu den Waffen!","Der Feind ist hier! Zu den Waffen!","Ach, du bist ein Bastard! Jetzt werden wir deinen Arsch treten!");
				link.l1 = "Verdammt!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00)
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Halt! Du bist nicht einer von uns... Erwartet dich der Hai oder schlenderst du einfach ziellos umher?";
					link.l1 = "Hai? Steve Dodson?";
					link.l1.go = "first_talk_day";
				}
				else
				{
				dialog.text = "Der Admiral wird Sie akzeptieren. Machen Sie weiter.";
				link.l1 = "Danke!";
				link.l1.go = "exit";
			}
			}
			else
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Wohin hast du es so eilig? Es ist Nacht, siehst du nicht! Oder glaubst du wirklich, dass der Admiral aufwachen wird, um dich persönlich zu begrüßen? Komm am Morgen.";
					link.l1 = "Wie du sagst. Und wo kann ich mich ausruhen?";
					link.l1.go = "first_talk_night";
				}
			else
			{
				dialog.text = "Es ist spät, der Admiral empfängt jetzt nicht. Komm morgen wieder.";
				link.l1 = "Gut...";
				link.l1.go = "exit";
			}
			}
			NextDiag.TempNode = "Shark_residence";
		break;
		
		case "Shark_soldier":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Jungs, seid vorsichtig, da ist der bewaffnete Psycho! Zu den Waffen!","Der Feind ist hier! Zu den Waffen!","Ach, du bist ein Bastard! Jetzt werden wir dir in den Arsch treten!");
				link.l1 = "Verdammt!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "Der Admiral wird nicht erfreut sein, wenn er mich reden sieht. Mach weiter.";
			link.l1 = "Gut...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_soldier";
		break;
		
		case "first_talk_night":
			dialog.text = NPCStringReactionRepeat("Bist du betrunken? Geh zurück und überquere die Brücke, passiere zwei Schiffe und dann findest du eine weitere Brücke, die dich zur Taverne bringt. Schlaf dort.","Bist du dabei, mich zu verärgern? Ich habe dir gerade gesagt, was du tun sollst. Verschwinde!","Geh und schlaf dich aus, besoffenes Gesicht...","Geh weg!!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Danke, Herr. Sie könnten eigentlich höflicher sein...","Es tut mir leid, ich habe vergessen...","Ich bin nicht betrunken!","Was?!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "first_talk_day":
			dialog.text = "Mach keine runden Augen, Junge. Jeder weiß, dass Steve Shark unser Admiral ist. Hast du irgendwelche Geschäfte mit ihm?";
			link.l1 = "Ja, verdammt! Ich habe Geschäfte mit ihm und es ist dringend.";
			link.l1.go = "first_talk_day_1";
		break;
		
		case "first_talk_day_1":
			dialog.text = "Und was für ein Geschäft?";
			link.l1 = "Ich werde darüber nur mit Shark im Privaten sprechen. Ich arbeite für Jan Svenson, kennen Sie ihn?";
			link.l1.go = "first_talk_day_2";
		break;
		
		case "first_talk_day_2":
			dialog.text = "Waldteufel? Ha! Die Hälfte von Main kennt diesen Mann. Hör zu, Bursche, sei nicht stur. Erkläre dich entweder oder verschwinde, bevor ich wütend werde. Shark sagte, er wolle von nutzlosen Leuten verschont bleiben und ich tue nur, wie er befohlen hat.";
			link.l1 = "Gut. Hier, schau dir diesen Brief an, er wurde vom Waldteufel an den Hai geschrieben.";
			link.l1.go = "first_talk_day_3";
		break;
		
		case "first_talk_day_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(blickend)... Gut. Ich nehme an, Steve wird es interessant finden. Mach weiter.";
			link.l1 = "Oh, wirklich? Gib den Brief zurück, wenn es für dich nicht zu schwer sein wird, bitte.";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "first_talk_day_5";
			else link.l1.go = "first_talk_day_4";
		break;
		
		case "first_talk_day_4":
			PlaySound("interface\important_item.wav");
			npchar.dialog.currentnode = "First time";
			DialogExit();
			LSC_OpenSanAvgustinDoors(); // открываем Сан-Августин
			LocatorReloadEnterDisable("LostShipsCity_town", "reload2", true); //закрываем кладовку со стороны моря
			pchar.quest.LSC_entry_pantry.over = "yes"; //снять прерывание на арест
			pchar.quest.LSC_findMary.over = "yes"; //снять прерывание на Мэри
			pchar.questTemp.LSC = "entrance"; //меняем флаг
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance";
			// закрываем вход к Мэри
			LocatorReloadEnterDisable("LostShipsCity_town", "reload60", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload61", true);
		break;
		
		case "first_talk_day_5":
			PlaySound("interface\important_item.wav");
			npchar.dialog.currentnode = "First time";
			DialogExit();
			LSC_OpenSanAvgustinDoors(); // открываем Сан-Августин
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance";
		break;
		
		case "shark_guard_fight":
			DialogExit();
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_SHARK");
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
