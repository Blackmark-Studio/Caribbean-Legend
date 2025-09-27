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
			dialog.text = "What the hell do you want?";
			link.l1 = "No, it's nothing.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//------------------------------------- фразы гардов нарвалов --------------------------------------------
		// пост нарвалов на проход на Сан-Габриэль
		case "Narval_warning":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there's a madman! To arms!","The enemy is here! To arms!","Ah, you bastard! Now we'll teach you a lesson!");
				link.l1 = "Fuck!";
				link.l1.go = "check_parol_fight";
				break;
			}
			ref location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "nrv_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "Stop, pal. Narwhal's territory ahead, entry is prohibited for strangers. You can pass only with an invitation. Do you know the password?";
					link.l1 = "Yes.";
					link.l1.go = "Narval_warning_yes";
					link.l2 = "No.";
					link.l2.go = "Narval_warning_no";
				}
				else // если друг нарвалам
				{
					dialog.text = "A-ah, "+GetFullName(pchar)+"! Hello, friend, we've been told you may walk freely here. Welcome!";
					link.l1 = "Thank you, friend!";
					link.l1.go = "exit";
				}
				location.nrv_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "I hope you haven't forgotten the password...";
					link.l1 = "Don't worry...";
					link.l1.go = "exit";
				}
				else // если друг нарвалам
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! How are you doing?";
					link.l1 = "Fine, thanks!";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Narval_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Narval_warning_yes":
			dialog.text = "Then go and tell that to the tough guy over there. Don't try to cheat him, our boys with muskets know what to do. So if you're planning any tricks - you'd better turn and leave. Now. I warned you.";
			link.l1 = "Fine, friend. I got it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_no":
			dialog.text = "Then you have nothing to do here unless you're planning to end your life, of course. Or are you just joking, huh? Are you kidding me? Actually, I don't care. Go down, my job is to warn, not to stop. You won't make it back if you don't know the password.";
			link.l1 = "Fine, pal. I got it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "What else do you need? Go down to the 'San Gabriel' or get lost!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "I am sorry, "+pchar.name+", but I am on duty. Don't bother me, friend. Move along!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_parol":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there's the psycho! To arms!","The enemy is here! To arms!","Ah, you bastard! Now we'll teach you a lesson!");
				link.l1 = "Fuck!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "I am sorry, "+pchar.name+", but I am on duty. Don't bother me, friend. Move along!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_parol";
				break;
			}
			dialog.text = "Stand right where you are! You are not one of us!";
			link.l1 = "I am standing, standing.";	
			link.l1.go = "check_parol";
		break;
		
		case "check_parol":
			dialog.text = "Say the password, and make it clear and loud.";
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
				link.l1 = "What password? Let me through, or else...";
				link.l1.go = "check_parol_wrong";
			}
		break;
		
		case "check_parol_1":
			dialog.text = "Fine, you may proceed.";
			link.l1 = "Thanks, pal...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			pchar.questTemp.LSC.parol_nrv = "true";
		break;
		
		case "check_parol_wrong":
			dialog.text = "Hm... Lads! We've got company!";
			link.l1 = "Shit!";
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
				dialog.text = LinkRandPhrase("Lads, careful, there's the psycho! To arms!","The enemy is here! To arms!","Ah, you bastard! Now we'll teach you a lesson!");
				link.l1 = "Fuck!";
				link.l1.go = "check_parol_fight";
				break;
			}
			dialog.text = "Move along! Don't stand here!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
		break;
		
		// у резиденции
		case "Narval_residence":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there's the psycho! To arms!","The enemy is here! To arms!","Ah, you bastard! Now we will teach you a lesson!");
				link.l1 = "Fuck!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // диалог от времени суток. лесник
			    {
					dialog.text = TimeGreeting()+", "+pchar.name+"! The door is open, in case you want to see the boss.";
					link.l1 = "Fine...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else
				{
                    dialog.text = TimeGreeting()+", "+pchar.name+"! If you want to see the boss, he's asleep now. Come back in the morning.";
					link.l1 = "Fine...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");	
                }					
				break;	
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Friends of blacks have no business here. A direct order from the boss!";
				if (CheckAttribute(pchar, "questTemp.LSC.Donald_enter"))
				{
					link.l1 = "He will have to see me. You have real trouble, guys. I am here by official order of the admiral. So open the damn door!";
					link.l1.go = "negotiations";
				}
				else
				{
				link.l1 = "I can't say I want to see him either...";
				link.l1.go = "exit";
				}
				NextDiag.TempNode = "Narval_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "Want to see the boss? Hm, well, move along then.";
			link.l1 = "Thanks for allowing me to...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else
			{
            dialog.text = "Want to see the boss? No more visits today. Come back in the morning.";
			link.l1 = "Alright...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Narval_soldier":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there's the psycho! To arms!","The enemy is here! To arms!","Ah, you bastard! Now we'll teach you a lesson!");
				link.l1 = "Fuck!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! How are you doing?";
				link.l1 = "I am fine, thanks...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Listen, pal, I'm not in the mood to talk. Move along...";
				link.l1 = "Fine.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_soldier";
		break;
		
		case "negotiations":
			dialog.text = "Well, well... Calm down. You should have said you were from the admiral in the first place. See, there are all sorts of people wandering around...";
			link.l1 = "Are you finally going to let me through? Thanks!";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			DialogExit();
			NextDiag.CurrentNode = "negotiations_2";
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false); // открыть вход к Дональду Гринспи
		break;
		
		case "negotiations_2":
			dialog.text = "Move along, you are allowed to...";
			link.l1 = "Oh, really? I can't believe it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_2";
		break;
		
//------------------------------------- фразы гардов ривадос --------------------------------------------
		// пост ривадос на проход на Фурию и Веласко
		case "Rivados_warning":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there's an aggressive psycho! To arms!","The enemy is here! To arms!","Ah, you sick bastard! Now we'll teach you a lesson!");
				link.l1 = "Fuck!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "rvd_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "Stop! The territories behind me belong to the Rivados clan, and no strangers like you are allowed to pass through without an invitation. Do you know the password?";
					link.l1 = "Yes.";
					link.l1.go = "Rivados_warning_yes";
					link.l2 = "No.";
					link.l2.go = "Rivados_warning_no";
				}
				else // если друг ривадос
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! Glad to see you! We've been told that you're free to walk here. Welcome!";
					link.l1 = "Thank you, friend!";
					link.l1.go = "exit";
				}
				location.rvd_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "I hope you haven't forgotten the password...";
					link.l1 = "Don't worry...";
					link.l1.go = "exit";
				}
				else // если друг ривадос
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! How are you doing?";
					link.l1 = "I am fine, thanks...";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_warning_yes":
			dialog.text = "You can go then. This lad will demand a password from you. You'd better leave now if you have any thoughts about tricking us. I have warned you.";
			link.l1 = "Fine, pal. I got it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_no":
			dialog.text = "Ho-ho! Either you are very brave or very foolish if you are going to visit us without a password. Or are you just joking? Go on then. I am here to warn, not to stop. Beware if you really don't know the password!";
			link.l1 = "Fine, pal. I got it.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Well, what do you want? Move along or get lost!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "I am sorry, "+pchar.name+", but I'm on duty. Eddie doesn't want me to talk too much.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_parol":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there's an aggressive madman! To arms!","The enemy is here! To arms!","Ah, you are a sick bastard! Now we'll teach you a lesson!");
				link.l1 = "Fuck!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "I am sorry, "+pchar.name+", but I'm on duty. Eddie doesn't want me to talk too much.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_parol";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			dialog.text = "Stop right where you are! You are not Rivados!";
			link.l1 = "I want to pass through.";	
			link.l1.go = "Rcheck_parol";
		break;
		
		case "Rcheck_parol":
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
				link.l1 = "What password? Let me through, or else...";
				link.l1.go = "Rcheck_parol_wrong";
			}
		break;
		
		case "Rcheck_parol_1":
			dialog.text = "Correct. Move along.";
			link.l1 = "Thanks, pal...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			pchar.questTemp.LSC.parol_rvd = "true";
		break;
		
		case "Rcheck_parol_wrong":
			dialog.text = "Ha-ha! We have a guest here! Let's show him who we are!";
			link.l1 = "Shit!";
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
				dialog.text = LinkRandPhrase("Lads, careful, there's an aggressive psycho! To arms!","The enemy is here! To arms!","Ah, you are a sick bastard! Now we will teach you a lesson!");
				link.l1 = "Fuck!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			dialog.text = "Don't stand here, move along!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
		break;
		
		// у резиденции
		case "Rivados_residence":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there's an aggressive psycho! To arms!","The enemy is here! To arms!","Ah, you sick bastard! Now we'll teach you!");
				link.l1 = "Fuck!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
				{
				dialog.text = TimeGreeting()+", "+pchar.name+"! The door is open, in case you want to see Eddie and Chimiset. They'll be glad to see you.";
				link.l1 = "Fine...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else // лесник - режим пропуска 
				{	
				dialog.text = TimeGreeting()+", "+pchar.name+"! If you want to see Eddie and Chimiset, they're already resting. Come back in the morning, they'll be glad to see you.";
				link.l1 = "Fine...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "There is nothing for friends of the Narwhal to do inside Eddie's cabin! This is his direct order. Get lost!";
				link.l1 = "I didn't want to see him either...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (GetCharacterIndex("Chimiset") == -1) // Чимисет убит
			{
				dialog.text = "There is nothing for you to do inside Eddie's cabin! That's a direct order from him. Get lost!";
				link.l1 = "I didn't want to see him either...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "Do you want to see Eddie? Fine, move along, I suppose he'll spare a minute for you.";
			link.l1 = "Thanks for allowing me to...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else // лесник режим пропуска.
			{
            dialog.text = "Do you want to see Eddie? No more visits today, come back in the morning and he will spare a minute for you.";
			link.l1 = "Alright...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Rivados_soldier":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there's an aggressive madman! To arms!","The enemy is here! To arms!","Ah, you are a sick bastard! Now we'll teach you a lesson!");
				link.l1 = "Fuck!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! How are you doing?";
				link.l1 = "I am fine, thanks...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Listen, pal, I'm not in the mood to talk. Move along...";
				link.l1 = "Fine.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_soldier";
		break;
//------------------------------------- фразы гардов пиратов --------------------------------------------	
		// у склада
		case "Shark_storage":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there's an armed madman! To arms!","The enemy is here! To arms!","Ah, you bastard! Now we'll kick your arse!");
				link.l1 = "Damn!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "Stop! This is a restricted area!";
			link.l1 = "Fine, as you say...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_storage";
		break;
		
		// у резиденции
		case "Shark_residence":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there's an armed madman! To arms!","The enemy is here! To arms!","Ah, you bastard! Now we'll kick your arse!");
				link.l1 = "Damn!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00)
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Stop! You're not one of ours... Is Shark expecting you, or are you just wandering around aimlessly?";
					link.l1 = "Shark? Steve Dodson?";
					link.l1.go = "first_talk_day";
				}
				else
				{
				dialog.text = "The Admiral will accept you. Move along.";
				link.l1 = "Thanks!";
				link.l1.go = "exit";
			}
			}
			else
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Where are you rushing to? It's night, can't you see! Or do you really think the admiral will wake up to greet you personally? Come back in the morning.";
					link.l1 = "As you say. And where can I rest?";
					link.l1.go = "first_talk_night";
				}
			else
			{
				dialog.text = "It's late, the admiral is not receiving now. Come back tomorrow.";
				link.l1 = "Fine...";
				link.l1.go = "exit";
			}
			}
			NextDiag.TempNode = "Shark_residence";
		break;
		
		case "Shark_soldier":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Lads, careful, there's an armed madman! To arms!","The enemy is here! To arms!","Ah, you bastard! Now we'll kick your arse!");
				link.l1 = "Damn!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "The Admiral won't be pleased if he sees me talking. Move along.";
			link.l1 = "Fine...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_soldier";
		break;
		
		case "first_talk_night":
			dialog.text = NPCStringReactionRepeat("Are you drunk? Turn back and walk across the bridge, pass two ships, and then you will find another bridge which will take you to the tavern. Sleep there.","Are you trying to piss me off? I just told you what to do. Get lost!","Go and get some sleep, drunk face...","Go away!!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Thank you, sir. You could be a bit more polite, actually...","I am sorry, I forgot...","I am not drunk!","What?!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "first_talk_day":
			dialog.text = "Don't look so surprised, lad. Everybody knows that Steve Shark is our admiral. Do you have any business with him?";
			link.l1 = "Yes, damn it! I have business with him and it is urgent.";
			link.l1.go = "first_talk_day_1";
		break;
		
		case "first_talk_day_1":
			dialog.text = "And what kind of business?";
			link.l1 = "I will only tell Shark about it in private. I am working for Jan Svenson, do you know him?";
			link.l1.go = "first_talk_day_2";
		break;
		
		case "first_talk_day_2":
			dialog.text = "Forest Devil? Ha! Half of Main knows that man. Listen, lad, don't be stubborn. Either explain yourself or get lost before I get angry. Shark said to spare him from useless people and I'm just doing as he ordered.";
			link.l1 = "Fine. Here, take a look at this letter, it's written by Forest Devil to Shark.";
			link.l1.go = "first_talk_day_3";
		break;
		
		case "first_talk_day_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(looking)... Fine. I suppose Steve will find it interesting. Move along.";
			link.l1 = "Oh, really? Give the letter back if it's not too much trouble, please.";
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
