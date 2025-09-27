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
			dialog.text = "Mi a fenét akarsz?";
			link.l1 = "Nem, semmi.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//------------------------------------- фразы гардов нарвалов --------------------------------------------
		// пост нарвалов на проход на Сан-Габриэль
		case "Narval_warning":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Fiúk, vigyázzatok, ott van a pszichopata! Fegyverbe!","Itt az ellenség! Fegyverbe!","Ah, te szemétláda! Most megleckéztetünk!");
				link.l1 = "Bassza meg!";
				link.l1.go = "check_parol_fight";
				break;
			}
			ref location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "nrv_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "Állj, haver. Narválok területe elôtt, idegeneknek tilos a belépés. Csak meghívóval mehetsz át. Tudod a jelszót?";
					link.l1 = "Igen.";
					link.l1.go = "Narval_warning_yes";
					link.l2 = "Nem.";
					link.l2.go = "Narval_warning_no";
				}
				else // если друг нарвалам
				{
					dialog.text = "A-ah, "+GetFullName(pchar)+"! Szia barátom, figyelmeztettek minket, hogy itt szabadon járhatsz. Üdvözöllek!";
					link.l1 = "Köszönöm, barátom!";
					link.l1.go = "exit";
				}
				location.nrv_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
				{
					dialog.text = "Remélem, nem felejtetted el a jelszót...";
					link.l1 = "Ne aggódj...";
					link.l1.go = "exit";
				}
				else // если друг нарвалам
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! Hogy vagy?";
					link.l1 = "Jól, köszönöm!";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Narval_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Narval_warning_yes":
			dialog.text = "Akkor menj és mondd ezt annak a kemény fickónak ott. Ne próbáld átverni, a mi muskétás fiaink tudják, mit kell tenni. Szóval ha bármilyen trükköt tervezel - jobb, ha megfordulsz és elmész. Most pedig... Figyelmeztettelek.";
			link.l1 = "Rendben, barátom. Megvan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_no":
			dialog.text = "Akkor persze nincs itt semmi dolgod, ha nem akarsz véget vetni az életednek. Vagy csak viccelsz, mi? Most viccelsz velem? Igazából nem érdekel. Menj le, az én dolgom figyelmeztetni, de nem megállítani. Ha nem tudod a jelszót, nem jutsz vissza.";
			link.l1 = "Rendben, haver. Megvan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "Mi másra van még szüksége? Menj le a 'San Gabriel' vagy tûnj el!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Sajnálom, "+pchar.name+", de szolgálatban vagyok. Ne zavarj, haver. Menjen tovább!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_warning_repeat";
		break;
		
		case "Narval_parol":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Fiúk, vigyázzatok, ott van a pszichopata! Fegyverbe!","Itt az ellenség! Fegyverbe!","Ah, te szemétláda! Most megleckéztetünk!");
				link.l1 = "Bassza meg!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = "Sajnálom, "+pchar.name+", de szolgálatban vagyok. Ne zavarj, haver. Menjen tovább!";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Narval_parol";
				break;
			}
			dialog.text = "Maradj ott, ahol vagy! Te nem tartozol közénk!";
			link.l1 = "Állok, állok.";	
			link.l1.go = "check_parol";
		break;
		
		case "check_parol":
			dialog.text = "Mondj egy jelszót, de tisztán és hangosan.";
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
				link.l1 = "Miféle jelszó? Engedj át, vagy különben...";
				link.l1.go = "check_parol_wrong";
			}
		break;
		
		case "check_parol_1":
			dialog.text = "Rendben, mehetnek tovább.";
			link.l1 = "Kösz, haver...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_NARVAL");
			pchar.questTemp.LSC.parol_nrv = "true";
		break;
		
		case "check_parol_wrong":
			dialog.text = "Hm... Fiúk! Van egy társaságunk!";
			link.l1 = "Basszus!";
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
				dialog.text = LinkRandPhrase("Fiúk, vigyázzatok, ott van a pszichopata! Fegyverbe!","Itt az ellenség! Fegyverbe!","Ah, te szemétláda! Most megleckéztetünk!");
				link.l1 = "Bassza meg!";
				link.l1.go = "check_parol_fight";
				break;
			}
			dialog.text = "Mozgás! Ne álljatok itt!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_parol_repeat";
		break;
		
		// у резиденции
		case "Narval_residence":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Fiúk, vigyázzatok, ott van a pszichopata! Fegyverbe!","Itt az ellenség! Fegyverbe!","Ah, te szemétláda! Most megleckéztetünk!");
				link.l1 = "Bassza meg!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // диалог от времени суток. лесник
			    {
					dialog.text = TimeGreeting()+", "+pchar.name+"! Az ajtó nyitva van, ha esetleg látni akarod a fônököt.";
					link.l1 = "Rendben...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else
				{
                    dialog.text = TimeGreeting()+", "+pchar.name+"! Ha esetleg a fônököt szeretnéd látni, mostanra már alszik. Jöjjön vissza reggel.";
					link.l1 = "Rendben...";
					link.l1.go = "exit";
					NextDiag.TempNode = "Narval_residence";
					DeleteAttribute(npchar, "protector.CheckAlways");	
                }					
				break;	
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "A feketék barátainak nincs itt semmi dolguk. Egyenes parancs a fônöktôl!";
				if (CheckAttribute(pchar, "questTemp.LSC.Donald_enter"))
				{
					link.l1 = "Találkoznia kell velem. Nagy bajban vagytok, fiúk. Az admirális hivatalos parancsára vagyok itt. Úgyhogy nyissátok ki azt a rohadt ajtót!";
					link.l1.go = "negotiations";
				}
				else
				{
				link.l1 = "Én sem mondhatom, hogy látni akarom...";
				link.l1.go = "exit";
				}
				NextDiag.TempNode = "Narval_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "Akarod látni a fônököt? Hm, nos, akkor menjetek tovább.";
			link.l1 = "Köszönöm, hogy megengedte...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else
			{
            dialog.text = "Akarod látni a fônököt? Ma nincs több látogatás. Jöjjön vissza reggel.";
			link.l1 = "Rendben...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Narval_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Narval_soldier":
			if (CheckAttribute(pchar, "GenQuest.NarvalConflict"))
			{
				dialog.text = LinkRandPhrase("Fiúk, vigyázzatok, ott van a pszichopata! Fegyverbe!","Itt az ellenség! Fegyverbe!","Ah, te szemétláda! Most megleckéztetünk!");
				link.l1 = "Bassza meg!";
				link.l1.go = "check_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Hogy vagy?";
				link.l1 = "Jól vagyok, köszönöm...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Figyelj, haver, nincs kedvem beszélgetni. Menj tovább...";
				link.l1 = "Rendben.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Narval_soldier";
		break;
		
		case "negotiations":
			dialog.text = "Hát, hát, hát... Nyugodj meg. Azt kellett volna mondanod, hogy az admirálistól jöttél. Látod, itt más emberek mászkálnak...";
			link.l1 = "Végre átengedsz? Köszönöm! Köszönöm!";
			link.l1.go = "negotiations_1";
		break;
		
		case "negotiations_1":
			DialogExit();
			NextDiag.CurrentNode = "negotiations_2";
			LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false); // открыть вход к Дональду Гринспи
		break;
		
		case "negotiations_2":
			dialog.text = "Menjen tovább, meg van engedve...";
			link.l1 = "Ó, tényleg? Nem hiszem el.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_2";
		break;
		
//------------------------------------- фразы гардов ривадос --------------------------------------------
		// пост ривадос на проход на Фурию и Веласко
		case "Rivados_warning":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Fiúk, vigyázzatok, ott van az agresszív pszichopata! Fegyverbe!","Itt az ellenség! Fegyverbe!","Ah, te beteg állat! Most megleckéztetünk!");
				link.l1 = "Bassza meg!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			location = &Locations[FindLocation(pchar.location)];
			if (!CheckAttribute(location, "rvd_parolinfo"))
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "Állj! A mögöttem lévô területek a Rivados klánhoz tartoznak, ilyen idegenek, mint te, nem mehetnek át meghívás nélkül. Tudod a jelszót?";
					link.l1 = "Igen.";
					link.l1.go = "Rivados_warning_yes";
					link.l2 = "Nem.";
					link.l2.go = "Rivados_warning_no";
				}
				else // если друг ривадос
				{
					dialog.text = "Ah, "+GetFullName(pchar)+"! Örülök, hogy látlak! Úgy értesültünk, hogy itt szabadon sétálhatsz. Üdvözöljük önöket!";
					link.l1 = "Köszönöm, barátom!";
					link.l1.go = "exit";
				}
				location.rvd_parolinfo = "true";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
				{
					dialog.text = "Remélem, nem felejtetted el a jelszót...";
					link.l1 = "Ne aggódj...";
					link.l1.go = "exit";
				}
				else // если друг ривадос
				{
					dialog.text = TimeGreeting()+", "+pchar.name+"! Hogy vagy?";
					link.l1 = "Jól vagyok, köszönöm...";
					link.l1.go = "exit";
				}
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_warning_yes":
			dialog.text = "Akkor mehetsz. Ez a fiú jelszót fog kérni tôled. Jobb, ha most azonnal távozol, ha át akarsz verni minket. Figyelmeztettelek titeket.";
			link.l1 = "Rendben, haver. Megvan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_no":
			dialog.text = "Ho-ho! Vagy nagyon bátor vagy, vagy nagyon buta vagy, ha jelszó nélkül látogatsz meg minket. Vagy csak viccelsz? Akkor menjetek. Azért vagyok itt, hogy figyelmeztesselek, nem azért, hogy megállítsalak. Vigyázz, ha tényleg nem tudod a jelszót!";
			link.l1 = "Rendben, haver. Megvan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_warning_repeat";
		break;
		
		case "Rivados_warning_repeat":
			if (!CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Nos, mit akarsz? Menj tovább, vagy tûnj el!";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Sajnálom, "+pchar.name+", de szolgálatban vagyok. Eddie nem akarja, hogy túl sokat beszéljek.";
				link.l1 = "...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_warning_repeat";
			DeleteAttribute(npchar, "protector.CheckAlways");
		break;
		
		case "Rivados_parol":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Fiúk, vigyázzatok, ott van az agresszív pszichopata! Fegyverbe!","Itt az ellenség! Fegyverbe!","Ah, te beteg állat! Most megleckéztetünk!");
				link.l1 = "Bassza meg!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "Sajnálom, "+pchar.name+", de szolgálatban vagyok. Eddie nem akarja, hogy túl sokat beszéljek.";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_parol";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			dialog.text = "Állj meg ott, ahol vagy! Te nem vagy Rivados!";
			link.l1 = "Át akarok menni.";	
			link.l1.go = "Rcheck_parol";
		break;
		
		case "Rcheck_parol":
			dialog.text = "Akkor mondj egy jelszót, de hangosan és tisztán.";
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
				link.l1 = "Miféle jelszó? Engedj át, vagy különben...";
				link.l1.go = "Rcheck_parol_wrong";
			}
		break;
		
		case "Rcheck_parol_1":
			dialog.text = "Jól van. Menjetek tovább.";
			link.l1 = "Kösz, haver...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
			LAi_SetGuardianType(NPChar);
			LAi_group_MoveCharacter(NPChar, "LSC_RIVADOS");
			pchar.questTemp.LSC.parol_rvd = "true";
		break;
		
		case "Rcheck_parol_wrong":
			dialog.text = "Ha-ha! Vendégünk van! Mutassuk meg neki, kik vagyunk!";
			link.l1 = "Basszus!";
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
				dialog.text = LinkRandPhrase("Fiúk, vigyázzatok, ott van az agresszív pszichopata! Fegyverbe!","Itt az ellenség! Fegyverbe!","Ah, te beteg állat! Most megleckéztetünk téged!");
				link.l1 = "Bassza meg!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			dialog.text = "Ne állj itt, menj tovább!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_parol_repeat";
		break;
		
		// у резиденции
		case "Rivados_residence":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Fiúk, vigyázzatok, ott van az agresszív pszichopata! Fegyverbe!","Itt az ellenség! Fegyverbe!","Ah, te beteg állat! Most majd megtanítunk rá!");
				link.l1 = "Bassza meg!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
				{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Az ajtó nyitva van, ha esetleg látni szeretnéd Eddie-t és Chimiset. Örülni fognak, ha találkozol velük.";
				link.l1 = "Rendben...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				else // лесник - режим пропуска 
				{	
				dialog.text = TimeGreeting()+", "+pchar.name+"! Abban az esetben, ha szeretnéd látni Eddie-t és Chimiset, ôk már pihennek. Gyertek vissza reggel, örülni fognak nektek.";
				link.l1 = "Rendben...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				}
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.nrv_friend") && !CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = "A Narvál barátainak nincs mit tenniük Eddie kunyhójában! Ez az ô közvetlen parancsa. Tûnjetek el!";
				link.l1 = "Én sem akartam látni...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (GetCharacterIndex("Chimiset") == -1) // Чимисет убит
			{
				dialog.text = "Semmit sem tehetsz Eddie kabinjában! Ez az ô közvetlen parancsa. Tûnjetek el!";
				link.l1 = "Én sem akartam látni...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Rivados_residence";
				DeleteAttribute(npchar, "protector.CheckAlways");
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00) // лесник . диалог от времени суток .
			{
			dialog.text = "Akarod látni Eddie-t? Rendben, menjen tovább, gondolom, szán egy percet magára.";
			link.l1 = "Köszönöm, hogy megengedte...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
			}
			else // лесник режим пропуска.
			{
            dialog.text = "Látni akarja Eddie-t? Ma nincs több látogatás, jöjjön vissza reggel, és majd szán egy percet magára.";
			link.l1 = "Rendben...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Rivados_residence";
			DeleteAttribute(npchar, "protector.CheckAlways");
            }			
		break;
		
		case "Rivados_soldier":
			if (CheckAttribute(pchar, "GenQuest.RivadosConflict"))
			{
				dialog.text = LinkRandPhrase("Fiúk, vigyázzatok, ott van az agresszív pszichopata! Fegyverbe!","Itt az ellenség! Fegyverbe!","Ah, te beteg állat! Most megleckéztetünk!");
				link.l1 = "Bassza meg!";
				link.l1.go = "Rcheck_parol_fight";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LSC.rvd_friend")) 
			{
				dialog.text = TimeGreeting()+", "+pchar.name+"! Hogy vagy?";
				link.l1 = "Jól vagyok, köszönöm...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Figyelj, haver, nincs kedvem beszélgetni. Menj tovább...";
				link.l1 = "Rendben.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rivados_soldier";
		break;
//------------------------------------- фразы гардов пиратов --------------------------------------------	
		// у склада
		case "Shark_storage":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Fiúk, vigyázzatok, ott van a fegyveres pszichopata! Fegyverbe!","Itt az ellenség! Fegyverbe!","Ah, te szemétláda! Most szétrúgjuk a segged!");
				link.l1 = "A fenébe!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "Állj! Ez tiltott terület!";
			link.l1 = "Rendben, ahogy mondod...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_storage";
		break;
		
		// у резиденции
		case "Shark_residence":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Fiúk, vigyázzatok, ott van a fegyveres pszichopata! Fegyverbe!","Itt az ellenség! Fegyverbe!","Ah, te szemétláda! Most szétrúgjuk a segged!");
				link.l1 = "A fenébe!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			if (stf(environment.time) >= 6.00 && stf(environment.time) < 21.00)
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Állj! Te nem vagy a miénk... Shark vár rád, vagy csak sétálgatsz céltalanul?";
					link.l1 = "Shark? Steve Dodson?";
					link.l1.go = "first_talk_day";
				}
				else
				{
				dialog.text = "Az admirális elfogadja magát. Menjen tovább.";
				link.l1 = "Köszönjük!";
				link.l1.go = "exit";
			}
			}
			else
			{
				if (pchar.questTemp.LSC == "begin" || pchar.questTemp.LSC == "mary") // тока прибыл
				{
					dialog.text = "Hová rohansz? Éjszaka van, nem látod?! Vagy tényleg azt hiszed, hogy az admirális fel fog ébredni, hogy személyesen üdvözöljön? Jöjjön reggel.";
					link.l1 = "Ahogy mondod. És hol pihenhetek?";
					link.l1.go = "first_talk_night";
				}
			else
			{
				dialog.text = "Késô van, az admirális most nem fogad. Jöjjön vissza holnap.";
				link.l1 = "Rendben...";
				link.l1.go = "exit";
			}
			}
			NextDiag.TempNode = "Shark_residence";
		break;
		
		case "Shark_soldier":
			if (CheckAttribute(pchar, "GenQuest.SharkConflict"))
			{
				dialog.text = LinkRandPhrase("Fiúk, vigyázzatok, ott van a fegyveres pszichopata! Fegyverbe!","Itt az ellenség! Fegyverbe!","Ah, te szemétláda! Most szétrúgjuk a segged!");
				link.l1 = "A fenébe!";
				link.l1.go = "shark_guard_fight";
				break;
			}
			dialog.text = "Az admirális nem fog örülni, ha meglátja, hogy beszélek. Menjetek tovább.";
			link.l1 = "Rendben...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Shark_soldier";
		break;
		
		case "first_talk_night":
			dialog.text = NPCStringReactionRepeat("Részeg vagy? Fordulj vissza, és menj át a hídon, menj el két hajó mellett, majd találsz egy másik hidat, amely a tavernához vezet. Aludj ott.", 
				"Fel akarsz húzni? Épp most mondtam meg, hogy mit kell tenned. Tûnj el!", 
				"Menj aludni, részeges pofa...",
				"Menj innen!!!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Köszönöm, uram. Lehetne udvariasabb is...", 
				"Sajnálom, elfelejtettem...",
				"Nem vagyok részeg!", 
				"Mi?!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		case "first_talk_day":
			dialog.text = "Ne nézz ilyen kerek szemekkel, fiú. Mindenki tudja, hogy Steve Shark az admirálisunk. Van valami dolga vele?";
			link.l1 = "Igen, a fenébe is! Üzletem van vele, és sürgôs.";
			link.l1.go = "first_talk_day_1";
		break;
		
		case "first_talk_day_1":
			dialog.text = "És miféle ügy?";
			link.l1 = "Csak Sharknak mondom el négyszemközt. Jan Svensonnak dolgozom, ismeri ôt?";
			link.l1.go = "first_talk_day_2";
		break;
		
		case "first_talk_day_2":
			dialog.text = "Forest Devil? Há! Fél Main ismeri ezt az embert. Figyelj, fiam, ne légy makacs. Vagy magyarázkodj, vagy tûnj el, mielôtt megharagszom. Cápa azt mondta, hogy kíméljem meg a haszontalan emberektôl, és én csak azt teszem, amit parancsolt.";
			link.l1 = "Rendben. Tessék, nézd meg ezt a levelet, Forest Devil írta Sharknak.";
			link.l1.go = "first_talk_day_3";
		break;
		
		case "first_talk_day_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(néz)... Rendben. Gondolom, Steve érdekesnek fogja találni. Menjünk tovább.";
			link.l1 = "Ó, tényleg? Adja vissza a levelet, ha nem esik nehezére, kérem.";
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
