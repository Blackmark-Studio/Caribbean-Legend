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
			dialog.text = "Che diavolo vuoi?";
			link.l1 = "No, non è nulla.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//------------------------------------- фразы гардов нарвалов --------------------------------------------
		// пост нарвалов на проход на Сан-Габриэль
		case "Narval_warning":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Ragazzi, attenti, ecco il matto! Alle armi!","Il nemico è qui! Alle armi!","Ah, sei un figlio di puttana! Ora ti faremo vedere noi!");
				link.l1 = "Porca miseria!";
				link.l1.go = "check_parol_fight";
				break;
			}
			ref location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "nrv_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "Fermati, amico. Territori dei Narvali davanti, l’ingresso è vietato agli stranieri. Si passa solo su invito. Conosci la parola d’ordine?";
					link.l1 = "Sì.";
					link.l1.go = "Narval_warning_yes";
					link.l2 = "No.";
					link.l2.go = "Narval_warning_no";
				}
				else // если друг нарвалам
				{
					dialog.text = "A-ah, "+GetFullName(pchar)+"! Salve, amico, ci hanno avvisato che puoi camminare liberamente qui. Benvenuto!";
					link.l1 = "Grazie, amico!";
					link.l1.go = "exit";
				}
				location.nrv_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "Spero che tu non abbia scordato la parola d’ordine...";
					link.l1 = "Non temere...";
					link.l1.go = "exit";
				}
				else // если друг нарвалам
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! Come te la passi?";
					link.l1 = "Bene, grazie!";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Narval_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Narval_warning_yes":
			dialog.text = "Allora vai a dirlo a quel tipo tosto laggiù. Non provare a fregarlo, i nostri ragazzi coi moschetti sanno bene il mestiere. Se stai tramando qualche furbata – ti conviene voltarti e sparire. Subito. Ti ho avvisato.";
			link.l1 = "Va bene, compare. Ho capito.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_no":
			dialog.text = "Allora non hai nulla da fare qui, a meno che tu non abbia deciso di finirla, ovviamente. Oppure stai scherzando, eh? Mi prendi in giro? In realtà, non me ne importa un fico secco. Scendi pure, il mio compito è avvertire, non fermare. Se non conosci la parola d’ordine, non farai mai ritorno.";
			link.l1 = "Va bene, compare. Ho capito.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "Che altro vuoi? Scendi sulla 'San Gabriel' o sparisci dai piedi!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Mi rincresce, "+pchar.name+", ma sono di guardia. Non seccarmi, compare. Avanti, fila!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_parol":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Ragazzi, attenti, ecco il pazzo! Alle armi!","Il nemico è qui! Alle armi!","Ah, sei un bastardo! Ora ti daremo una lezione che non scorderai!");
				link.l1 = "Accidenti!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "Mi rincresce, "+pchar.name+", ma sono di guardia. Non scocciarmi, compare. Vai avanti!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_parol";
				break;
			}
			dialog.text = "Fermo dove stai! Non sei dei nostri!";
			link.l1 = "Sono in piedi, in piedi.";	
			link.l1.go = "check_parol";
		break;
		
		case "check_parol":
			dialog.text = "Pronuncia una parola d’ordine, chiara e forte.";
			link.l1.edit = 3;
			link.l1 = "";	
			link.l1.go = "check_parol_1";
		break;
		
		case "check_parol_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[3]);
			if (sTemp == sNrvParol && CheckAttribute(pchar, "questTemp.LSC.NParol_bye"))
			{
				dialog.text = "Bene, puoi procedere.";
				link.l1 = "Grazie, compare...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_parol_repeat";
				LAi_SetGuardianType(NPChar);
				LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
				pchar.questTemp.LSC.parol_nrv = "true";
			}
			else
			{
				dialog.text = "Uhm... Ragazzi! Abbiamo compagnia!";
				link.l1 = "Merda!";
				link.l1.go = "check_parol_fight";
			}
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
				dialog.text = LinkRandPhrase("Ragazzi, attenti, ecco il pazzo! Alle armi!","Il nemico è qui! Alle armi!","Ah, sei un bastardo! Ora ti insegneremo una lezione!");
				link.l1 = "Malasorte!";
				link.l1.go = "check_parol_fight";
				break;
			}
			dialog.text = "Avanti, non restare qui impalato!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
		break;
		
		// у резиденции
		case "Narval_residence":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Ragazzi, attenti, ecco il pazzo! Alle armi!","Il nemico è qui! Alle armi!","Ah, sei un bastardo! Ora ti faremo vedere noi, canaglia!");
				link.l1 = "Porca miseria!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // диалог от времени суток. лесник
			    {
					dialog.text = TimeGreeting()+", "+pchar.name+"! La porta è aperta, se vuoi far visita al capo.";
					link.l1 = "D’accordo...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else
				{
                    dialog.text = TimeGreeting()+", "+pchar.name+"! Se vuoi vedere il capo, ormai dorme. Torna domattina.";
					link.l1 = "Va bene...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");	
                }					
				break;	
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Gli amici dei neri qui non hanno niente da fare. Ordine diretto del capo!";
				if (CheckAttribute(pchar, "questTemp.LSC.Donald_enter"))
				{
					link.l1 = "Dovrà ricevermi. Avete dei veri guai, canaglie. Sono qui per ordine ufficiale dell’ammiraglio. Quindi aprite questa maledetta porta!";
					link.l1.go = "negotiations";
				}
				else
				{
				link.l1 = "Non posso dire che mi faccia piacere vederlo anch’io...";
				link.l1.go = "exit";
				}
				NextDiag.TempNode = "Narval_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "Vuoi vedere il capo? Mh, allora avanti, muoviti.";
			link.l1 = "Grazie per aver permesso di...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else
			{
            dialog.text = "Vuoi vedere il capo? Niente visite oggi. Torna domattina.";
			link.l1 = "D'accordo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Narval_soldier":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Ragazzi, attenti, ecco il pazzo! Alle armi!","Il nemico è qui! Alle armi!","Ah, sei un bastardo! Ora ti faremo vedere noi, dannato cane!");
				link.l1 = "Accidenti!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Come te la passi?";
				link.l1 = "Sto bene, grazie...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ascolta, compare, non ho voglia di ciarlare. Levati dai piedi...";
				link.l1 = "D’accordo.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_soldier";
		break;
		
		case "negotiations":
			dialog.text = "Ebbene, ebbene... Calmati. Avresti dovuto dire subito che vieni dall’ammiraglio. Vedi, qui si aggirano diversi tipi di gente...";
			link.l1 = "Finalmente mi lasci passare? Grazie!";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			DialogExit();
			NextDiag.CurrentNode = "negotiations_2";
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false); // открыть вход к Дональду Гринспи
		break;
		
		case "negotiations_2":
			dialog.text = "Avanti, ti è permesso...";
			link.l1 = "Oh, davvero? Non ci posso credere.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_2";
		break;
		
//------------------------------------- фразы гардов ривадос --------------------------------------------
		// пост ривадос на проход на Фурию и Веласко
		case "Rivados_warning":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Ragazzi, attenti, ecco il pazzo furioso! Alle armi!","Il nemico è qui! Alle armi!","Ah, sei proprio un bastardo malato! Ora ti daremo una bella lezione!");
				link.l1 = "Accidenti!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "rvd_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "Fermati! Le terre alle mie spalle appartengono al clan Rivados, nessun forestiero come te può passare senza invito. Conosci la parola d'ordine?";
					link.l1 = "Sì.";
					link.l1.go = "Rivados_warning_yes";
					link.l2 = "No.";
					link.l2.go = "Rivados_warning_no";
				}
				else // если друг ривадос
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"Felice di vederti! Ci hanno detto che puoi girare liberamente qui. Benvenuto!";
					link.l1 = "Grazie, amico!";
					link.l1.go = "exit";
				}
				location.rvd_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "Spero che tu non abbia dimenticato la parola d’ordine...";
					link.l1 = "Non temere...";
					link.l1.go = "exit";
				}
				else // если друг ривадос
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! Come te la cavi?";
					link.l1 = "Sto bene, grazie...";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_warning_yes":
			dialog.text = "Puoi andare, allora. Quel ragazzo ti chiederà una parola d’ordine. Se pensi di fregarci, meglio che te ne vada subito. Ti ho avvertito.";
			link.l1 = "Va bene, compare. Ho capito.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_no":
			dialog.text = "Ho-ho! O sei davvero coraggioso o sei proprio uno sciocco se vieni a trovarci senza parola d’ordine. Oppure stai scherzando? Avanti allora. Io sono qui per avvisare, non per fermare. Fa’ attenzione se davvero non conosci la parola segreta!";
			link.l1 = "Va bene, compare. Ho capito.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "E allora, che vuoi? Cammina o sparisci!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Mi rincresce, "+pchar.name+", ma sono di guardia. Eddie non vuole che chiacchieri troppo.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_parol":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Ragazzi, attenti, ecco il pazzo furioso! Alle armi!","Il nemico è qui! Alle armi!","Ah, sei proprio un bastardo malato! Ora ti insegneremo una bella lezione!");
				link.l1 = "Accidenti!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Mi rincresce, "+pchar.name+", ma sono di guardia. Eddie non vuole che mi metta a chiacchierare troppo.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_parol";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			dialog.text = "Fermati dove sei! Non sei dei Rivados!";
			link.l1 = "Voglio passare.";	
			link.l1.go = "Rcheck_parol";
		break;
		
		case "Rcheck_parol":
			dialog.text = "Allora pronuncia la parola d’ordine, e fallo forte e chiaro.";
			link.l1.edit = 3;
			link.l1 = "";	
			link.l1.go = "Rcheck_parol_1";
		break;
		
		case "Rcheck_parol_1":
			sTemp = GetStrSmallRegister(dialogEditStrings[3]);
			if (sTemp == sRvdParol && CheckAttribute(pchar, "questTemp.LSC.RParol_bye"))
			{
				dialog.text = "Esatto. Avanti, su.";
				link.l1 = "Grazie, compare...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_parol_repeat";
				LAi_SetGuardianType(NPChar);
				LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
				pchar.questTemp.LSC.parol_rvd = "true";
			}
			else
			{
				dialog.text = "Ah-ah! Abbiamo un ospite, ragazzi! Mostriamogli chi siamo davvero!";
				link.l1 = "Merda!";
				link.l1.go = "Rcheck_parol_fight";
			}
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
				dialog.text = LinkRandPhrase("Ragazzi, attenti, ecco il pazzo furioso! Alle armi!","Il nemico è qui! Alle armi!","Ah, sei proprio un bastardo malato! Ora ti daremo una bella lezione, una bella lezione!");
				link.l1 = "Porca vacca!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			dialog.text = "Non restare qui impalato, avanti, cammina!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
		break;
		
		// у резиденции
		case "Rivados_residence":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Ragazzi, attenti, ecco il furioso psicopatico! Alle armi!","Il nemico è qui! Alle armi!","Ah, sei proprio un figlio di puttana! Ora ti insegneremo noi come si sta al mondo!");
				link.l1 = "Maledizione!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
				{
				dialog.text = TimeGreeting()+", "+pchar.name+"! La porta è aperta, se vuoi andare a trovare Eddie e Chimiset. Saranno lieti di vederti.";
				link.l1 = "Va bene...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else // лесник - режим пропуска 
				{	
				dialog.text = TimeGreeting()+", "+pchar.name+"! Se vuoi vedere Eddie e Chimiset, stanno già riposando. Torna domattina, saranno lieti di vederti.";
				link.l1 = "D’accordo...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Non c’è nulla che gli amici dei Narvali debbano fare nella cabina di Eddie! Questo è un suo ordine diretto. Sloggia!";
				link.l1 = "Neanch'io volevo rivederlo...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (GetCharacterIndex("Chimiset") == -1) // Чимисет убит
			{
				dialog.text = "Non hai nulla da cercare nella cabina di Eddie! È un suo ordine diretto. Sparisci!";
				link.l1 = "Nemmeno io volevo rivederlo...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "Vuoi vedere Eddie? Va bene, fatti avanti, suppongo che ti concederà un minuto.";
			link.l1 = "Grazie per avermi permesso di...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else // лесник режим пропуска.
			{
            dialog.text = "Vuoi vedere Eddie? Niente visite oggi, torna all’alba e forse ti concederà un attimo.";
			link.l1 = "D’accordo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Rivados_soldier":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Ragazzi, attenti, ecco il matto furioso! Alle armi!","Il nemico è qui! Alle armi!","Ah, sei un bastardo malato! Ora ti daremo una lezione che non scorderai!");
				link.l1 = "Accidenti!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Come ve la passate?";
				link.l1 = "Sto bene, grazie...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ascolta, compare, non ho voglia di ciarlare. Vai per la tua strada...";
				link.l1 = "Bene.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_soldier";
		break;
//------------------------------------- фразы гардов пиратов --------------------------------------------	
		// у склада
		case "Shark_storage":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Ragazzi, occhio, arriva il pazzo armato! Alle armi!","Il nemico è qui! Alle armi!","Ah, sei proprio un bastardo! Ora ti spaccheremo il culo!");
				link.l1 = "Maledizione!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "Fermati! Questa è una zona proibita!";
			link.l1 = "Va bene, come dici tu...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_storage";
		break;
		
		// у резиденции
		case "Shark_residence":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Ragazzi, attenti, c'è il pazzo armato! Alle armi!","Il nemico è qui! Alle armi!","Ah, sei proprio un bastardo! Ora ti prenderemo a calci nel culo!");
				link.l1 = "Maledizione!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00)
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Fermo lì! Tu non sei dei nostri... È lo Squalo che ti aspetta, o stai solo vagando senza meta?";
					link.l1 = "Squalo? Steve Dodson?";
					link.l1.go = "first_talk_day";
				}
				else
				{
				dialog.text = "L’Ammiraglio t’accoglierà. Avanti, muoviti.";
				link.l1 = "Grazie!";
				link.l1.go = "exit";
			}
			}
			else
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Dove corri così in fretta? È notte, non lo vedi! O pensi davvero che l’ammiraglio si sveglierà per accoglierti di persona? Torna al mattino.";
					link.l1 = "Come desideri. E dove posso trovare un po' di riposo?";
					link.l1.go = "first_talk_night";
				}
			else
			{
				dialog.text = "È tardi, l’ammiraglio non riceve adesso. Torna domani.";
				link.l1 = "Va bene...";
				link.l1.go = "exit";
			}
			}
			NextDiag.TempNode = "Shark_residence";
		break;
		
		case "Shark_soldier":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Ragazzi, attenti, arriva quel pazzo armato! Alle armi!","Il nemico è qui! Alle armi!","Ah, sei un bastardo! Ora ti spaccheremo il culo!");
				link.l1 = "Maledizione!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "L’Ammiraglio non gradirà vedermi chiacchierare. Va’ per la tua strada.";
			link.l1 = "D'accordo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_soldier";
		break;
		
		case "first_talk_night":
			dialog.text = NPCStringReactionRepeat("Sei ubriaco? Torna indietro e attraversa il ponte, passa due navi e poi troverai un altro ponte che ti porterà alla taverna. Là potrai dormire.","Stai cercando di farmi perdere la pazienza? Ti ho appena detto cosa devi fare. Sparisci!","Vai a dormire, faccia da fiasco...","Vattene!!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Grazie, signore. Potresti anche essere più cortese, in verità...","Mi dispiace, mi sono scordato...","Non sono ubriaco!","Cosa?!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "first_talk_day":
			dialog.text = "Non spalancare gli occhi, ragazzo. Tutti sanno che Steve Squalo è il nostro ammiraglio. Hai qualche faccenda da sbrigare con lui?";
			link.l1 = "Sì, maledizione! Ho faccende da sbrigare con lui, ed è urgente.";
			link.l1.go = "first_talk_day_1";
		break;
		
		case "first_talk_day_1":
			dialog.text = "E che tipo d'affari porti?";
			link.l1 = "Ne parlerò solo con Squalo, in privato. Lavoro per Jan Svenson, lo conosci?";
			link.l1.go = "first_talk_day_2";
		break;
		
		case "first_talk_day_2":
			dialog.text = "Diavolo della Foresta? Ah! Mezzo continente conosce quell’uomo. Senti, ragazzo, non fare il testardo. O ti spieghi, o sparisci prima che perda la pazienza. Lo Squalo ha detto di risparmiargli la gente inutile e io sto solo seguendo i suoi ordini.";
			link.l1 = "Bene. Ecco, dai un’occhiata a questa lettera, l’ha scritta il Diavolo della Foresta allo Squalo.";
			link.l1.go = "first_talk_day_3";
		break;
		
		case "first_talk_day_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(guardando)... Va bene. Suppongo che Steve lo troverà interessante. Avanti, muoviti.";
			link.l1 = "Oh, davvero? Restituisci la lettera, se non ti pesa troppo, per favore.";
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
