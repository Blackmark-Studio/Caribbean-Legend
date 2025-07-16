// диалоги по квесту Цена чахотки
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (pchar.questTemp.Consumption == "final")
			{
				dialog.text = "Kapitän! Sie sind zur See gefahren, habe ich gehört! Was ist passiert? Haben Sie etwas herausgefunden? Bitte erzählen Sie mir, spucken Sie es aus!";
				if (CheckAttribute(pchar, "questTemp.Consumption.TakeMoney"))
				{//взял деньги
					link.l1 = "Nein, meine Schönheit, dieser Überfall wurde auf Antrag Seiner Gnaden Gouverneur durchgeführt. Es tut mir sehr leid, aber Angelo starb in den Kasematten der Festung - daran besteht jetzt kein Zweifel mehr. Halte durch! ";
					link.l1.go = "Waitress";
				}
				else
				{//убил Хуана
					if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
					{
						link.l1 = "Du hattest recht. Dein Bruder wurde entführt. Der Kommandant hat Gefangene wie Vieh an einen Sklavenhändler verkauft, der den Spitznamen Verzehr trägt. Aber ich habe sein Schiff eingeholt, und jetzt liegt es auf dem Grund, und dein Bruder Angelo wird bald an Land kommen. Leider habe ich nicht so viele Langboote, wie benötigt, um alle Passagiere auf einmal an Land zu bringen. ";
						link.l1.go = "Waitress_2";
					}
					else
					{//отпустил Хуана
						link.l1 = "Du hattest recht. Dein Bruder wurde entführt. Der Kommandant hat Gefangene wie Vieh an einen Sklavenhändler verkauft, der den Spitznamen Verzehr hat. Aber ich habe sein Schiff eingeholt, obwohl es mir nicht gelungen ist, diesen Bastard zu töten, wird dein Bruder Angelo bald an Land gehen. Leider habe ich nicht so viele Langboote, wie benötigt, um alle Passagiere auf einmal an Land zu bringen.";
						link.l1.go = "Waitress_2";
					}
					sld = characterFromId("ConAndjelo");
					sld.lifeday = 0;
					RemovePassenger(Pchar, sld);
				}
			}
			else
			{
				dialog.text = "Haben Sie etwas über Angelos Schicksal herausfinden können, Kapitän?";
				link.l1 = "Noch nicht. Aber ich denke, ich werde bald Neuigkeiten haben. Du musst nur warten. ";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		case "without_moneysss": // лесник  если Гг нажрался..сволочь:D:D:D
		    dialog.text = "Herr, Sie versprachen, meinen Bruder zu finden... Warum verschwenden Sie Ihre Zeit hier mit Trinken?";
			link.l1 = "Ohh..Ja, richtig..hic... Entspann dich Mädel... Jesus hat die Kontrolle..'schlürf'... Jesus hat die Kontrolle. Ich bin schon weg...hic..";
			link.l1.go = "exit";
		break;
		
		case "Servant":
			dialog.text = "Guten Tag, Senor. Was führen Sie hier im Schilde?";
			link.l1 = "Ich habe eine Depesche für den Señor Kommandant gebracht, aber ich sollte sie ihm persönlich übergeben.";
			link.l1.go = "Servant_1";
		break;
		
		case "Servant_1":
			dialog.text = "Dann gehst du ihn in der Festung suchen.";
			link.l1 = "Diese Nachricht ist zu wichtig und nicht für Soldatenaugen und -ohren. Vielleicht bin ich zu früh gekommen, aber ich kann hier auf ihn warten. Vertrauen Sie mir, es ist sehr wichtig!";
			link.l1.go = "Servant_2";
		break;
		
		case "Servant_2":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < 40)
			{
				notification("Skill Check Failed (40)", SKILL_SNEAK);
				dialog.text = "Herr Kommandant warnt mich normalerweise vor allen wichtigen Angelegenheiten, die eine Änderung der Routine erfordern... Wissen Sie, tatsächlich hat er mich vor diesem speziellen Fall gewarnt.";
				link.l1 = "Und was hat er gesagt?";
				link.l1.go = "Servant_3";
			}
			else
			{
				notification("Skill Check Passed", SKILL_SNEAK);
				dialog.text = "In Ordnung, ich glaube dir. Und ich werde dir noch mehr glauben, wenn der Senior Kommandant ankommt, um deine Worte zu bestätigen. Aber bis dahin werde ich dich ständig im Auge behalten.";
				link.l1 = "Du kannst mich so viel beobachten, wie du möchtest...";
				link.l1.go = "Servant_4";
			}
		break;
		
		case "Servant_3":
			dialog.text = "Er hat mir gesagt, ich soll in solchen Fällen die Garnisonswachen rufen. Aber wir werden wahrscheinlich alleine zurechtkommen. Jungs! Lasst uns ihn ausnehmen!";
			link.l1 = "Verdammt!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Servant_4":
			DialogExit();
			NextDiag.CurrentNode = "Servant_repeat";
			LAi_SetOwnerType(npchar);
			chrDisableReloadToLocation = false;
		break;
		
		case "Servant_repeat":
			dialog.text = "Was willst du noch? Hast du dich entschieden, die Botschaft mir zu geben?";
			link.l1 = "Nein, ich werde auf den Kommandanten warten...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Servant_repeat";
		break;
		
		case "Servant_fight":
			int iRank = sti(pchar.rank)+5;
			int iScl = 15 + 2*sti(pchar.rank);
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			chrDisableReloadToLocation = true;
			for (i=9; i<=11; i++)
			{	
				sld = GetCharacter(NPC_GenerateCharacter("Conservant_"+i, "citiz_"+i, "man", "man", iRank, SPAIN, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_10", "pistol1", "bullet", iScl*2);
				DeleteAttribute(sld, "SaveItemsForDead");
				DeleteAttribute(sld, "DontClearDead");
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "goto", "goto5");
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Consumption_AfterHouseFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		//попытка залезть в сундук
		case "Man_FackYou":
			dialog.text = "Du bist ein Dieb! Oder vielleicht ein Spion? Jungs, schnell runter!";
			link.l1 = "Verdammt, Teufel!";
			link.l1.go = "Servant_fight";
		break;
		
		case "Sergio":
			dialog.text = "Entschuldigung, darf ich mit Ihnen sprechen?";
			link.l1 = "Ehrlich gesagt, ich habe es eilig. Was willst du?";
			link.l1.go = "Sergio_1";
		break;
		
		case "Sergio_1":
			dialog.text = "Ich habe mitbekommen, dass Sie sich nach einem Mann namens Juan und Krankheiten in unserem Gefängnis erkundigen...";
			link.l1 = "Tatsächlich habe ich... könnten Sie sich erklären.";
			link.l1.go = "Sergio_2";
		break;
		
		case "Sergio_2":
			dialog.text = "Ruhig, ruhig! Beruhige dich und berühre dein Schwert nicht! Wir sind hier auf der gleichen Seite! Ich weiß nicht, warum du dich um unsere Probleme kümmern würdest, aber das muss gestoppt werden! Ich kann nicht länger schweigen!";
			link.l1 = "Haltet den Mund? Über was? Was wisst ihr über die Schwindsucht?";
			link.l1.go = "Sergio_3";
		break;
		
		case "Sergio_3":
			dialog.text = "Ich weiß viel, wenn nicht alles, und ich werde mich erklären - aber nicht hier. Lasst uns am Abend treffen, wenn die Lichter aus sind, ich bin ein medizinischer Assistent, also darf ich das Fort verlassen. Wir treffen uns vor den Stadttoren, und ich erzähle dir alles. Ich bitte dich - hör auf, Fragen zu stellen, bevor du ihre Aufmerksamkeit erregst, wenn du es nicht schon getan hast... Ich muss jetzt gehen. Denk daran, nachts vor den Stadttoren.";
			link.l1 = "Also gut, ich werde da sein. Hey! Warte...";
			link.l1.go = "Sergio_4";
		break;
		
		case "Sergio_4":
			DialogExit();
			AddQuestRecord("Consumption", "8");
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption3.win_condition.l1 = "location";
			pchar.quest.Consumption3.win_condition.l1.location = "PortSpein_Exittown";
			pchar.quest.Consumption3.win_condition.l2 = "Hour";
			pchar.quest.Consumption3.win_condition.l2.start.hour = 0;
			pchar.quest.Consumption3.win_condition.l2.finish.hour = 3;
			pchar.quest.Consumption3.function = "Consumption_MeetSergio";
			pchar.quest.Consumption4.win_condition.l1 = "Timer";
			pchar.quest.Consumption4.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Consumption4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Consumption4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Consumption4.function = "Consumption_FailSergio";
			locations[FindLocation("PortSpein_Exittown")].DisableEncounters = true; //энкаутеры закрыть
			LAi_LocationDisableOfficersGen("PortSpein_Exittown", true);//офицеров не пускать
		break;
		
		case "Sergio_5":
			dialog.text = "Gott sei Dank, du bist hier... Ich hoffe, du wurdest nicht verfolgt?";
			link.l1 = "Warum? Du bist zu misstrauisch, vielleicht sogar mehr als der Senor Kommandant, also solltest du dich besser um deine Angelegenheiten kümmern... Was weißt du über Juan?";
			link.l1.go = "Sergio_6";
		break;
		
		case "Sergio_6":
			dialog.text = "Mein Name ist Sergio Saldo. Ich diene als medizinischer Assistent in unserer Festung und...";
			link.l1 = "";
			link.l1.go = "Sergio_6_1";
		break;
		
		case "Sergio_6_1":
			dialog.text = "";
			link.l1 = "Warte! Hast du das gehört?";
			link.l1.go = "Sergio_7";
			Play3DSound("lomanie_vetki", -33.25, 1.00, 3.73)
		break;
		
		case "Sergio_7":
			dialog.text = "Was?! Wo?";
			link.l1 = "Scheiße, wir sind hier nicht alleine... Wen hast du mitgebracht, Abschaum?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Consumption_CreateBandits");
		break;
		
		case "Bandit":
			dialog.text = "Sie haben uns bemerkt! Du nimmst den Arzt, und ich nehme den anderen!";
			link.l1 = "...";
			link.l1.go = "Bandit_1";
		break;
		
		case "Bandit_1":
			DialogExit();
			sld = characterFromId("Sergio");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=3; i++)
			{	
				sld = characterFromId("Conbandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Conbandit_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Sergio_8":
			dialog.text = "Steck dein Schwert weg, es ist vorbei! Du hast selbst gesehen, dass sie auch versucht haben, mich zu töten!";
			link.l1 = "Nun, es scheint zu raffiniert für ein böses Spiel - also, du bist nicht mit ihnen. Wo waren wir stehen geblieben? Du bist ein Gefängnisarzt, nicht wahr?";
			link.l1.go = "Sergio_9";
		break;
		
		case "Sergio_9":
			dialog.text = "Ja. Ich diene als Gefängnisarzt. Ich habe Medizin studiert, als ich jung war, und es gibt hier nicht viele gebildete Menschen. Deshalb weiß ich besser als jeder andere, was im Gefängnis vor sich geht!";
			link.l1 = "Was ist denn los? Was ist mit den Gefangenen? Weißt du etwas über ihr plötzliches Verschwinden.";
			link.l1.go = "Sergio_10";
		break;
		
		case "Sergio_10":
			dialog.text = "Unser Kommandant verkauft sie... verkauft sie wie Vieh an einen Sklavenhändler namens Juan. Er wählt diejenigen aus, nach denen nicht gesucht wird - Bettler, Seeleute von zufälligen Schiffen. Und dann sterben sie plötzlich 'an Schwindsucht' - du kannst dir den Rest vorstellen...";
			link.l1 = "Dieser Juan ist also ein Mensch! Was weißt du über ihn?";
			link.l1.go = "Sergio_11";
		break;
		
		case "Sergio_11":
			dialog.text = "Ein bisschen. Er pflegte sein schmutziges Geschäft in Marokko zusammen mit Berberpiraten zu machen, er erzählt gerne Geschichten aus dieser Zeit, wenn er uns einen Besuch abstattet. Dort erhielt er seinen Spitznamen - Verzehr. Will nicht über seine Herkunft nachdenken\nEr kommt jeden Monat hierher und nimmt alle Gefangenen an Bord.";
			link.l1 = "'Verzehr!' Und sie haben mich beschuldigt, zynisch zu sein! Also deswegen... Dieser Senor Kommandant von euch ist ein echter Trottel!";
			link.l1.go = "Sergio_12";
		break;
		
		case "Sergio_12":
			dialog.text = "Wie ich verstehe, brauchst du jemanden aus den verlorenen Gefangenen, sonst wie würdest du von dieser Geschichte erfahren, habe ich recht? Wenn ja, solltest du dich beeilen: diese Nacht ist die letzte in diesem Monat. Ich habe bereits die Papiere unterschrieben, die den Tod von drei weiteren Menschen bestätigen, und Juan wird morgen vor Mittag Anker lichten, wenn er sie erhält!";
			link.l1 = "Was haben Sie unterschrieben? Ich verstehe Sie nicht ganz...";
			link.l1.go = "Sergio_13";
		break;
		
		case "Sergio_13":
			dialog.text = "Ich musste es tun - so wie ich es schon seit mehreren Monaten getan habe! Deshalb bin ich hierher gekommen, um dies zu stoppen. Wissen Sie, wie Doktor Pinero gestorben ist? Derjenige, der vor mir die Gefangenen behandelt hat?";
			link.l1 = "Ich glaube, mir wurde gesagt, dass er an Schwindsucht gestorben ist, nicht wahr? Also, du bist dazu gezwungen. Das ist logisch - aber warum hat niemand die Behörden in dieser Angelegenheit kontaktiert?";
			link.l1.go = "Sergio_14";
		break;
		
		case "Sergio_14":
			dialog.text = "Und wer wird das glauben? Ich habe keine Beweise und die Soldaten, die die Gefangenen bewachen sollen, werden großzügig bezahlt, so dass es ihnen egal wäre, wenn sie Menschen an die Kariben als Mahlzeit verkaufen würden\nNiemand gibt einen Dreck auf die Gefangenen und das ist ein Ass in der Hand des Kommandanten. Aber du kannst das stoppen, zumindest für einige Zeit, indem du Juan beseitigst!";
			link.l1 = "Soweit ich verstehe, waren diese Kerle an Land seine Männer, nicht wahr? Wie kann ich ihn finden?";
			link.l1.go = "Sergio_15";
		break;
		
		case "Sergio_15":
			dialog.text = "Sie haben wahrscheinlich mit Ihren Fragen jemandes Aufmerksamkeit erregt... Ich habe Ihnen gesagt, vorsichtiger zu sein! Aber das ist jetzt nicht wichtig. Ich weiß nichts über Juans Schiff, aber Gefangene werden immer nach Galera Point geschickt, das im nördlichen Teil der Insel liegt. Ich vermute, dass das Sklavenschiff in der Nähe sein sollte und Sie könnten ihn einholen. Seine Boten haben heute erwähnt, dass er morgen Mittag absegeln wollte.";
			if (!CheckCharacterItem(pchar, "letter_consumption"))
			{
				link.l1 = "Danke dir, Sergio, du bist ein wahrer Offizier und ein Ehrenmann. Ich werde sofort Anker lichten und dieses dreckige Schiff finden. Du musst zurück zum Fort, bevor sie nach dir suchen.";
				link.l1.go = "Sergio_16";
			}
			else
			{
				link.l1 = "Nun, das ist alles, was ich wissen muss. Ich muss jetzt den Anker lichten, wenn ich nicht nach diesem 'Schwund' in der gesamten Neuen Welt suchen will. In der Zwischenzeit kannst du dies studieren.";
				link.l1.go = "Sergio_17";
			}
		break;
		
		case "Sergio_16":
			dialog.text = "Viel Glück, Kapitän! Mach dir keine Sorgen um mich - das Wichtigste ist, dies zumindest für eine Weile zu stoppen. Ich wünsche dir Glück!";
			link.l1 = "Meine Kanonen sind das beste Heilmittel gegen Beschwerden und Gemeinheit. Ich schwöre, dass alle Gefangenen vor der Morgendämmerung an Land sein werden - und Juans Schiff wird auf dem Meeresgrund ruhen!";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_17":
			RemoveItems(PChar, "letter_consumption", 1);
			Log_Info("You have given the letter");
			PlaySound("interface\important_item.wav");
			dialog.text = "Was ist das? Hier steht der Name des Obersten und ein Monogramm 'J'? Unglaublich! Wo haben Sie das her?";
			link.l1 = "Du solltest das besser nicht wissen, aber ich denke, du wirst es auf bestmögliche Weise einsetzen.";
			link.l1.go = "Sergio_18";
		break;
		
		case "Sergio_18":
			dialog.text = "Ich werde es tun, ich schwöre bei allem, was heilig ist! Der Oberst wird vor Ende des Monats am Galgen enden! Ich werde persönlich dafür sorgen!";
			link.l1 = "Ich fürchte, dass es mit einer Disziplinarstrafe enden wird, die, wie ich annehme, nicht die erste in seinem Leben sein wird. Vielleicht ist es besser, diesen Tölpel zu erschießen? Es ist ein sehr wirksames Mittel... Ich muss jetzt gehen - Ich möchte 'Konsumtion' nicht warten lassen.";
			link.l1.go = "Sergio_19";
		break;
		
		case "Sergio_19":
			DialogExit();
			AddQuestRecord("Consumption", "11");
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Consumption5.win_condition.l1 = "location";
			pchar.quest.Consumption5.win_condition.l1.location = "Trinidad";
			pchar.quest.Consumption5.function = "Consumption_CreateJuan";
			pchar.quest.Consumption6.win_condition.l1 = "HardHour";
			pchar.quest.Consumption6.win_condition.l1.hour = 13;
			pchar.quest.Consumption6.function = "Consumption_FailJuan";
			// Сержио теперь наш друг и будет торговать смолами
			SetFunctionTimerCondition("Oil_PrepareSergio", 0, 0, 20, false); // таймер
		break;
		
		// генератор торговли смолами
		case "Sergio_20":
			dialog.text = "Oh, was für ein glückliches Treffen! Senor "+GetFullName(pchar)+"! Ich bin so froh, dich zu sehen!";
			link.l1 = "Herr Sergio! Ich habe nicht erwartet, Sie zu treffen! Wie geht es Ihnen? Wie geht es dem guten alten Kommandanten?";
			link.l1.go = "Sergio_21";
		break;
		
		case "Sergio_21":
			dialog.text = "Ich bin gut, und Señor Kommandant ist zu den Minen von Los-Teques gegangen - seine schmutzigen Machenschaften mit Juan Konsumption sind aufgedeckt worden.";
			link.l1 = "Minen?! Bei meiner Seele! Ich hätte nie gedacht, dass in seinem Fall Gerechtigkeit geschehen würde...";
			link.l1.go = "Sergio_22";
		break;
		
		case "Sergio_22":
			dialog.text = "Ach, wenn es nur so wäre, Kapitän... Er wurde gerade versetzt und degradiert. Er dient jetzt in der Garnison, und er wurde nicht einmal seines Offiziersrangs beraubt. Nun, zumindest hat San Jose diesen Abschaum los.";
			link.l1 = "Nun, bisher so gut. Obwohl ich mehr erwartet habe.";
			link.l1.go = "Sergio_23";
		break;
		
		case "Sergio_23":
			dialog.text = "Ich auch... Aber lassen wir den Abschaum - er verdient es nicht, dass über ihn gesprochen wird. Señor, sobald ich gehört hatte, dass Ihr Schiff im Begriff war, den Hafen zu betreten, eilte ich mit aller Eile zum Pier. Ich habe ein Geschäft für Sie.";
			link.l1 = "Wirklich? Ich höre zu.";
			link.l1.go = "Sergio_24";
		break;
		
		case "Sergio_24":
			if (startHeroType == 1) sStr = "French";
			if (startHeroType == 2) sStr = "Spanish";
			if (startHeroType == 3) sStr = "English";
			if (startHeroType == 4) sStr = "English";
			dialog.text = "Kapitän, Sie scheinen ein Mann zu sein, dem man vertrauen kann. Ein weiterer sehr bedeutender Punkt ist, dass Sie sind "+sStr+" und du hast dein eigenes Schiff. Ich schlage vor, wir schließen ein Handelsabkommen.";
			link.l1 = "Klingt vielversprechend! Was für eine Vereinbarung?";
			link.l1.go = "Sergio_25";
		break;
		
		case "Sergio_25":
			dialog.text = "Wir sollten dies an einem anderen Ort besprechen - im Leuchtturmwärterhaus. Er ist mein alter Freund und ich vertraue ihm. Komm heute oder morgen zum Leuchtturm von San Jose. Dort werde ich auf dich warten. Ich bin sicher, dass du mein Angebot sehr interessant finden wirst!";
			link.l1 = "In Ordnung, Senor Sergio. Ich werde dort sein!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Oil_SergioRuntoMayak");
		break;
		
		case "Sergio_26":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Oil_SetSergioToMayakOver.over = "yes"; //снять прерывание
			dialog.text = "Willkommen zurück, senor. Lassen Sie mich Ihnen diese Angelegenheit erklären. ";
			link.l1 = "Ich bin ganz Ohr. ";
			link.l1.go = "Sergio_27";
		break;
		
		case "Sergio_27":
			dialog.text = "Wie Sie vielleicht schon wissen, bin ich nicht nur ein Soldat, sondern auch ein Arzt. Warum? Weil ich ein gut ausgebildeter Mann bin. Meine Bildung hinderte mich daran, meine Zeit hier mit Frauen und Getränken zu verschwenden. Stattdessen habe ich mehrere Expeditionen organisiert und konnte ein Harzlager nicht weit von hier finden\nDas ist eine Ressource von strategischer Bedeutung, diese Insel ist der einzige Ort, an dem man das spezielle Harz finden kann, das zum Bau solider und langlebiger Schiffe verwendet wird\nEin Gouverneur und ein Kommandant haben mir befohlen, all das Harz an die spanische Marine zu verkaufen\nDas Problem ist, dass sie mir die Hälfte des Marktpreises bezahlen und ich es nirgendwo anders verkaufen kann. Daher biete ich Ihnen an, es von mir zu kaufen. Es ist eine sehr wichtige Ware und es ist sehr schwer zu bekommen.";
			link.l1 = "Welches sind die Bedingungen unserer Vereinbarung? ";
			link.l1.go = "Sergio_28";
		break;
		
		case "Sergio_28":
			dialog.text = "Nach meinen Berechnungen werde ich in der Lage sein, 60 Fässer pro Monat zu sammeln, ohne Verdacht zu erregen. Lass uns einen Handel abschließen - jeden fünften jeden Monats werde ich diesen Leuchtturm besuchen, um mit meinem Freund einen Schluck zu trinken. Komm und mach mit, wenn du das Harz kaufen willst. Zehn goldene Dublonen für ein Fass\nDu bezahlst für eine ganze Lieferung und nimmst sie auf einmal mit. Kein Druck, es liegt an dir. Also, Handel?";
			link.l1 = "Hört sich für mich verdammt nach einem guten Deal an! Natürlich, es ist ein Deal!";
			link.l1.go = "Sergio_29";
		break;
		
		case "Sergio_29":
			dialog.text = "Wunderbar. Dann werde ich am fünften jeden Monats eine Flasche kanarischen Wein mit meinem alten Freund, dem Hüter, trinken und wir werden auf dich warten.";
			link.l1 = "Gut. Lass es uns so machen.";
			link.l1.go = "Sergio_30";
		break;
		
		case "Sergio_30":
			dialog.text = "Ich bin froh, dass wir eine Einigung erzielt haben. Auf Wiedersehen, Kapitän!";
			link.l1 = "Viel Glück in Ihrem Harzgeschäft, senor!";
			link.l1.go = "Sergio_31";
		break;
		
		case "Sergio_31":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			pchar.questTemp.OilTrade = "true";
			pchar.quest.Oil_fail.win_condition.l1 = "NPC_Death";
			pchar.quest.Oil_fail.win_condition.l1.character = "Sergio";
			pchar.quest.Oil_fail.function = "Oil_TradeFail";
			AddQuestRecordInfo("Unique_Goods", "4");
		break;
		
		case "oil_trade":
			dialog.text = "Hallo, Senor Kapitän! Sie sind wegen einer Ladung Harz gekommen, wie ich vermute.";
			link.l1 = "Das stimmt, Senor Sergio. Ist alles bereit?";
			link.l1.go = "oil_trade_1";
			link.l2 = "Herr Sergio, ich bin nicht in der Stimmung zu handeln. Vielleicht später.";
			link.l2.go = "oil_trade_exit";
		break;
		
		case "oil_trade_exit":
			DialogExit();
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "oil_trade_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeOil"))
			{
				dialog.text = "Ja. Hast du 2550 Dublonen dabei?";
				if (PCharDublonsTotal() >= 2550)
				{
					link.l1 = "Sicher. Hier bist du.";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "Pech gehabt! Ich habe das Geld auf meinem Schiff vergessen. Ich bringe es sofort hierher!";
					link.l1.go = "oil_trade_exit";
				}
			}
			else
			{
				dialog.text = "Ja. Hast du sechshundert Dublonen bei dir?";
				if (PCharDublonsTotal() >= 600)
				{
					link.l1 = "Sicher. Hier bist du.";
					link.l1.go = "oil_trade_2";
				}
				else
				{
					link.l1 = "Schweres Glück! Ich habe das Geld auf meinem Schiff vergessen. Ich bringe es sofort hierher!";
					link.l1.go = "oil_trade_exit";
				}
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && !CheckAttribute(pchar, "questTemp.SergioOilBlock")) // увеличить объём поставок смолами
			{
				link.l4 = "Herr Sergio, ich möchte mehr Harz kaufen. Könnten Sie Chargen liefern, sagen wir, fünfmal größer?";
				link.l4.go = "UpgradeOil";
			}
			if(sti(pchar.questTemp.SergioOil) >= 1 && CheckAttribute(pchar, "questTemp.SergioOilPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок смолами, если в первый раз не принесли
			{
				link.l4 = "Hier, wie versprochen, Señor Sergio, dreitausend Dublonen, wie Sie es verlangt haben. Ich bin sicher, dass dieses Unterfangen mit Ihrer Weitsicht und meiner Investition erhebliche Vorteile für uns beide bringen wird.";
				link.l4.go = "UpgradeOil_Agreed";
			}
		break;
		
		case "oil_trade_2":
			chrDisableReloadToLocation = true;//закрыть локацию
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) RemoveDublonsFromPCharTotal(2550);
			else RemoveDublonsFromPCharTotal(600);
			PlaySound("interface\important_item.wav");
			dialog.text = "Es ist ein Vergnügen, mit Ihnen zu handeln, Kapitän. Meine Leute werden Ihnen helfen, die Fässer auf Ihr Schiff zu laden.";
			link.l1 = "Danke dir!";
			link.l1.go = "oil_trade_3";
		break;
		
		case "oil_trade_3":
			dialog.text = "Das Angebot steht noch. Solltet ihr noch eine Ladung brauchen, kommt in einem Monat zurück.";
			link.l1 = "In Ordnung, Sergio. Wir sehen uns.";
			link.l1.go = "oil_trade_4";
		break;
		
		case "oil_trade_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
			if (CheckAttribute(pchar, "questTemp.UpgradeOil")) AddCharacterGoods(pchar, GOOD_OIL, 300);
			else AddCharacterGoods(pchar, GOOD_OIL, 60);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.SergioOil = sti(pchar.questTemp.SergioOil) + 1; // счётчик покупок
		break;
		
		case "UpgradeOil":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Herr"+GetSexPhrase("","es")+", Ihr Wunsch, mehr Harz zu kaufen, zeigt sicherlich Vertrauen in unser Geschäft. Es gibt jedoch eine Komplexität\nMit steigenden Mengen besteht ein größeres Risiko, die Aufmerksamkeit der Inselbehörden zu erregen, und die Kontrolle solcher Sendungen erfordert Menschen und Sicherheitsmaßnahmen, was, ich gebe es zu, nicht billig ist. Wenn Sie bereit sind, den Preis um drei Tausend Dublonen zu erhöhen, als einmalige Zahlung, werde ich zuverlässige Leute einstellen, die die Ladung schützen und Informationslecks verhindern können. Dann wird unsere Route sicherer und ich kann Ihnen monatlich dreihundert Fässer Harz liefern. Um Ihre Investition auszugleichen, biete ich Ihnen als Großkäufer einen fünfzehnprozentigen Rabatt auf alle zukünftigen Sendungen.";
				link.l1 = "Dreitausend Dublonen, um die Lieferungen zu sichern? Señor Sergio, ich werde es nicht verbergen, dieser Preis scheint unglaublich - als ob Sie eine Verschwörung im Escorial vorschlagen würden, anstatt nur eine Pechladung zu sichern!";
				link.l1.go = "UpgradeOil_1";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Herr"+GetSexPhrase("","es")+", Ich schätze Ihr Interesse, aber solche großen Transaktionen erfordern Erfahrung und Vorsicht. Zugegeben, Ihr Handelsniveau ist noch nicht hoch genug, um ein solches Volumen zu bewältigen. Ich rate Ihnen, etwas mehr Erfahrung zu sammeln und zu mir zurückzukommen, wenn Sie bereit für mehr Paritäten sind. Dann werden wir vielleicht die Angelegenheit gründlich besprechen.";
				link.l1 = "Gut. Wir werden später auf dieses Thema zurückkommen.";
				link.l1.go = "oil_trade_exit";
				notification("Skill Check Failed (80)", SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeOil_1":
			dialog.text = "Herr"+GetSexPhrase("","es")+", Ich verstehe Ihre Bedenken. Aber Sie wissen, Sicherheit ist nie billig, besonders bei so seltenen Waren. Außerdem garantiere ich nicht nur keine Lecks, sondern biete auch einen Rabatt an, der Ihre Investition über die Zeit ausgleichen wird. Ist das nicht ein vernünftiger Kompromiss?";
			link.l1 = "Ich gebe zu: In unserem Geschäft sind Zuverlässigkeit und Diskretion teuer und der Rabatt macht unser mögliches Geschäft etwas attraktiver. Aber trotzdem, dreitausend Dublonen sind eine übermäßige Summe. Vielleicht könnten Sie sie etwas reduzieren?";
			link.l1.go = "UpgradeOil_2";
		break;
		
		case "UpgradeOil_2":
			dialog.text = "Es tut mir leid, aber Halbheiten sind in solchen Angelegenheiten nicht akzeptabel. Entweder wir gewährleisten vollen Schutz oder wir riskieren alles. Die Summe bleibt dieselbe und nur auf diese Weise kann ich Zuverlässigkeit und Vertraulichkeit garantieren. Sie möchten doch nicht, dass die gesamte königliche Flotte erst mich, dann Sie jagt, oder?";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Sehr gut, Señor Saldo, Sie haben mich überzeugt. Sicherheit und Zuverlässigkeit haben ihren Preis. Dreitausend Dublonen. Hier sind sie.";
				link.l1.go = "UpgradeOil_Agreed";
			}
			link.l2 = "Herr Saldo, Sie haben mich von der Notwendigkeit dieser Maßnahmen überzeugt. Allerdings sind dreitausend Dublonen eine ernste Summe, und ich habe sie im Moment nicht. Ich muss warten, bis ich den erforderlichen Betrag gesammelt habe.";
			link.l2.go = "UpgradeOil_4";
			link.l3 = "Für solches Geld könnte man eine ganze Flotte und alle Soldaten auf dem Kontinent bestechen, geschweige denn Wachen für eine bescheidene Teerladung anheuern! Entschuldigung, aber ich kann einem solchen Angebot nicht zustimmen. Lassen wir alles so wie es ist, ohne Übertreibungen und zusätzliche Kosten.";
			link.l3.go = "UpgradeOil_3";
		break;
		
		case "UpgradeOil_Agreed":
			dialog.text = "Nun, Señor, ich sehe, dass unser Vertrauen gegenseitig ist. Seien Sie sicher, dass der Fall ordnungsgemäß behandelt wird. Nun zu den Details: 300 Fässer Öl, wie üblich, am 5. jeden Monats, werden hier am Leuchtturm von Trinidad auf Sie warten. Sie können die gesamte Partie für 2550 Dublonen einlösen.";
			link.l1 = "Das ist großartig, Señor Sergio. Enttäuschen Sie mich nicht.";
			link.l1.go = "UpgradeOil_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "4_1");
			pchar.questTemp.UpgradeOil = true;
			pchar.questTemp.SergioOilBlock = true;
			DeleteAttribute(pchar, "questTemp.SergioOilPotom");
		break;
		
		case "UpgradeOil_Agreed_1":
			dialog.text = "Zögern Sie nicht, señor"+GetSexPhrase("","es")+". Alles wird auf höchstem Niveau organisiert werden, und unsere gemeinsame Arbeit wird Vorteile bringen.";
			link.l1 = "Bis dann.";
			link.l1.go = "oil_trade_exit";
		break;
		
		case "UpgradeOil_3":
			DialogExit();
			pchar.questTemp.SergioOilBlock = true;
			NextDiag.CurrentNode = "oil_trade";
		break;
		
		case "UpgradeOil_4":
			dialog.text = "Komm, wenn du den vollen Betrag hast. Ich werde mich freuen, einen neuen Handel mit dir zu machen.";
			link.l1 = "In Ordnung.";
			link.l1.go = "oil_trade_exit";
			pchar.questTemp.SergioOilBlock = true;
			pchar.questTemp.SergioOilPotom = true;
		break;
	// <-- генератор смол
		
		case "Juan_abordage":
			dialog.text = "Wer zur Hölle bist du!?";
			link.l1 = "Mein Name ist "+GetFullName(pchar)+", was dich betrifft, Schwindsucht, der Teufel wartet auf dich - und er wird deine Seele sehr bald haben!";
			link.l1.go = "Juan_abordage_1";
		break;
		
		case "Juan_abordage_1":
			if (CheckAttribute(pchar, "questTemp.Consumption.House"))
			{
				dialog.text = "Dieses Schiff wird in die Luft gehen - eine Lunte brennt bereits im Pulverraum - warum sollten wir beide sterben? Legen wir die Schwerter nieder. Du wirst genug Zeit haben, um rauszukommen, und ich werde vom Schiff springen, Galera Point ist von hier aus nur einen Steinwurf entfernt. Wenn du Gold brauchst, nimm es! Fünfhundert Dublonen, bar auf die Kralle - und du vergisst mich, und ich vergesse dich! Abgemacht?";
				link.l1 = "Gold? Ich habe all das nicht für Geld begonnen, Juan, sondern um den Abschaum zu töten, und du bist die größte Belohnung an sich.";
				link.l1.go = "Juan_abordage_2";
				link.l2 = "Fünfhundert Dublonen? Du machst dich über mich lustig, Auszehrung. Ich denke, du hast hier mindestens doppelt so viel gestapelt... Gib mir jetzt tausend und du kannst zur Hölle fahren, sonst...";
				link.l2.go = "Juan_abordage_3";
			}
			else
			{
				dialog.text = "Das Schiff steht kurz vor der Explosion, also werde ich gute Gesellschaft haben, was denkst du?";
				link.l1 = "Du redest zu viel, Schwindsucht, komm zur Sache!";
				link.l1.go = "Juan_abordage_5";
			}
		break;
		
		case "Juan_abordage_2":
			dialog.text = "Wir hätten eine Vereinbarung treffen können... Ach, was auch immer!";
			link.l1 = "Du hast diese armen Leute aus ihren Zellen genommen, und sie konnten sich weder wehren noch weglaufen. Du bist ein Feigling, Schwindsucht, und jetzt wirst du wie ein Feigling sterben.";
			link.l1.go = "Juan_abordage_5";
		break;
		
		case "Juan_abordage_3":
			dialog.text = "Du hast einen harten Griff, Freund... Hier - das ist alles, was ich habe. Nicht zu viel für ein Leben, oder?";
			link.l1 = "Dein Leben ist keine Kugel wert, also scheint es das profitabelste Geschäft meines Lebens zu sein. Jetzt verschwinde.";
			link.l1.go = "Juan_abordage_4";
			TakeNItems(pchar, "gold_dublon", 1000);
			Log_Info("You received 1000 doubloons");
			PlaySound("interface\important_item.wav");
			ChangeCharacterComplexReputation(pchar, "nobility", -10);
			OfficersReaction("bad");
			pchar.questTemp.Consumption.TakeMoney = "true"; //атрибут для диалога
		break;
		
		case "Juan_abordage_4":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "ConJuan_AfterFight_1", 10.0);
		break;
		
		case "Juan_abordage_5":
			dialog.text = "Es ist schade, dass du nicht genug Zeit haben wirst, um jeden zu retten und mich zu töten, oder? Die Lunte brennt und die Zeit vergeht...";
			link.l1 = "Verdammt! Ich muss die Leute hier rausholen... Verschwinde, Abschaum - du bekommst früher oder später, was du verdienst!";
			link.l1.go = "Juan_abordage_4";
			link.l2 = "Ich werde es trotzdem versuchen...";
			link.l2.go = "Juan_abordage_6";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
			sld = GetCharacter(NPC_GenerateCharacter("ConAndjelo", "citiz_9", "man", "man", 5, SPAIN, -1, true, "quest"));
			sld.name = "Angelo";
			sld.lastname = "";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
		break;
		
		case "Juan_abordage_6":
			//LAi_SetCurHPMax(NPChar);
			//LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("ConJuan_AfterFight_2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Consumption.KillJuan = "true"; //атрибут для диалога
		break;
		
		case "Waitress":
			dialog.text = "Ach... Ich bin sprachlos... Was für ein Alptraum!";
			link.l1 = "Ach, ich konnte nichts tun. Es tut mir leid, Mädel. Lebewohl.";
			link.l1.go = "Waitress_1";
		break;
		
		case "Waitress_1":
			DialogExit();
			AddQuestRecord("Consumption", "16");
			AddQuestUserData("Consumption", "sSex", GetSexPhrase("",""));
			Consumption_Close();
		break;
		
		case "Waitress_2":
			dialog.text = "Unglaublich! Du... hast du ihn wirklich gerettet? Ich habe keine Ahnung, wie ich dir danken soll.";
			if (CheckAttribute(npchar, "quest.Consumption.sex"))
			{
				link.l1 = "Ich kann mir das vorstellen, Schönheit. Aber mein Teil des Geschäfts ist jetzt erledigt - es bleibt nur noch eine Kleinigkeit.";
				link.l1.go = "Waitress_3";
			}
			link.l2 = "Pflicht rief - und ich handelte. Das ist es.";
			link.l2.go = "Waitress_5";
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan")) AddQuestRecord("Consumption", "18");
			else AddQuestRecord("Consumption", "17");
		break;
		
		case "Waitress_3":
			dialog.text = "Ich ... oh Gott! Du hast recht. Für ihn, wie ich versprochen habe... Geh nach oben in das Zimmer - wir haben nicht viel Zeit.";
			link.l1 = "Lass uns dann beeilen!";
			link.l1.go = "Waitress_4";
		break;
		
		case "Waitress_4"://благодарность натурой
			DialogExit();
			LocatorReloadEnterDisable("PortSpein_tavern", "reload1_back", true); //закрыть таверну
			LocatorReloadEnterDisable("PortSpein_tavern", "reload2_back", false); //открыть комнату
			bDisableFastReload = true;//закрыть переход
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "PortSpein_tavern_upstairs", "goto", "goto3", "ConsumptionSexWaitress", -1);
			pchar.questTemp.Consumption.Sex = "true";
		break;
		
		case "Waitress_sex":
			dialog.text = "Hier bin ich, mein tapferer Caballero! Und schau, was ich mitgebracht habe.";
			link.l1 = "Nun, ich bin beeindruckt, lass uns diesen Kirschwein öffnen! Dann werden wir etwas anderes öffnen... Es ist schließlich dein Glückstag... Ha-ha!";
			link.l1.go = "Waitress_sex_1";
		break;
		
		case "Waitress_sex_1":
			DialogExit();
			DoQuestCheckDelay("PlaySex_1", 0.1);
		break;
		
		case "Waitress_5":
			if (CheckAttribute(pchar, "questTemp.Consumption.KillJuan"))
			{
				dialog.text = "Du bist ein echter Ritter! Caballero! Hier - nimm es nicht als Beleidigung, aber ich möchte, dass du es nimmst. Ich habe dieses Geld gesammelt, um Angelo auszulösen, aber jetzt ist es nicht wichtig! Bitte, lehne nicht ab - nimm es!";
				link.l1 = "Nun, ich werde mich an deine Augen erinnern, senorita - sie sind so viel schöner, wenn sie vor Glück und nicht vor Schmerz glänzen. Ich akzeptiere dein Geschenk. Tschüss und viel Glück für dich und Angelo.";
				link.l1.go = "Waitress_6";
				AddMoneyToCharacter(pchar, 5000);
			}
			else
			{
				dialog.text = "Du bist ein echter Ritter! Caballero! Ich werde es jedem erzählen! Ich werde dich immer in Erinnerung behalten!";
				link.l1 = "Nun, und ich werde mich an deine Augen erinnern, Señorita - sie sind so viel schöner, wenn sie mit Tränen des Glücks und nicht des Schmerzes leuchten. Mögest du immer glücklich sein. Lebewohl!";
				link.l1.go = "Waitress_6";
			}
		break;
		
		case "Waitress_6":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			Consumption_Close();
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
