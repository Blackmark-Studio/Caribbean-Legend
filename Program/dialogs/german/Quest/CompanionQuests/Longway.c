void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
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
			dialog.text = "Was wollen Sie?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
		break;
		
		// Квест "Путеводная звезда"
		// Этап 0, ПРОЛОГ
		case "PZ_Alonso_1":
			dialog.text = "Entschuldigen Sie, dass ich in Ihre Quartiere eingedrungen bin, Senor Kapitän, aber das ist sehr wichtig.";
			link.l1 = "Ich hoffe es doch, Alonso. Wenn jeder von euch hier hereinplatzt, als ob es sein eigener Raum wäre, dann haben wir ein Problem. Also, was ist los?";
			link.l1.go = "PZ_Alonso_2";
		break;
		
		case "PZ_Alonso_2":
			dialog.text = "Wir haben festgestellt, dass in Ihrem Spind herumgewühlt wurde.";
			link.l1 = "Was?! Warte mal... Wie hast du das herausgefunden? Und was habt ihr alle in meiner Kajüte gemacht?";
			link.l1.go = "PZ_Alonso_3";
		break;
		
		case "PZ_Alonso_3":
			dialog.text = "Wir reinigen Ihre Quartiere ab und zu, wenn Sie unterwegs sind - entweder in der Stadt oder auf den Kojen ruhen. Haben Sie das nie bemerkt? Oder haben Sie es einfach vergessen?";
			link.l1 = "Ach, das ist richtig. Nun, du kannst jetzt gehen.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Tichingitu_1":
			dialog.text = "Kapitän Charles, schau! Jemand hat in deiner großen Schublade gewühlt.";
			link.l1 = "Was? Wann hast du das bemerkt? Weißt du, wer es war?";
			link.l1.go = "PZ_Tichingitu_2";
		break;
		
		case "PZ_Tichingitu_2":
			dialog.text = "Nicht lange her, als ich zu dir kam. Die Geister schweigen darüber, wer es sein könnte.";
			link.l1 = "Das ist eine nette Geste, Tichingitu. Jetzt entschuldige mich bitte, ich muss überprüfen, ob etwas fehlt.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Duran_1":
			dialog.text = "Hey, Kapitän, was guckst du an? Jemand hat in deinen Sachen gewühlt. Sogar ich habe es bemerkt.";
			link.l1 = "Warst du das nicht? Schließlich bezahle ich dich nicht so großzügig wie Francois.";
			link.l1.go = "PZ_Duran_2";
		break;
		
		case "PZ_Duran_2":
			dialog.text = "Heh, wenn ich der Dieb wäre, würde ich es dir doch nicht sagen, oder? Ich würde die Wertsachen nehmen und aufräumen. Dieses Durcheinander ist nicht mein Stil.";
			link.l1 = "Ich hasse es, es zuzugeben, aber du hast recht. Nun, Claude, spar dir deine Sticheleien für später. Ich muss überprüfen, was der Dieb genommen hat.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_Folke_1":
			dialog.text = "Kapitän, mir ist heute aufgefallen, dass jemand in Ihrem Schließfach herumgewühlt hat. Haben Sie das nicht bemerkt?";
			link.l1 = "Was? Ich überprüfe nicht ständig den Spind, Folke, und ich bin nicht einmal die ganze Zeit in der Kabine. Sag mir ehrlich - warst du das? Hast du wieder Mist gebaut und das letzte Mal, als wir an Land waren, weitere Bankdarlehen aufgenommen?";
			link.l1.go = "PZ_Folke_2";
		break;
		
		case "PZ_Folke_2":
			dialog.text = "Keineswegs, Kapitän. Ich habe nichts von Ihnen in meinen Taschen oder in meinem Spind. Und das werde ich auch nie haben.";
			link.l1 = "Ich hoffe doch nicht. Du kannst gehen - ich werde nachsehen, was fehlt.";
			link.l1.go = "PZ_OsmatrivaemKautu";
		break;
		
		case "PZ_OsmatrivaemKautu":
			DialogExit();
			
			if (npchar.id == "Tichingitu")
			{
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				npchar.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (npchar.id == "FMQT_mercen" || npchar.id == "Folke")
			{
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Enc_Officer_dialog.c";
				npchar.Dialog.CurrentNode = "hired";
			}
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "loc2", "PZ_OsmatrivaemSunduk", -1);
		break;
		
		case "PZ_LigaInJungle_1":
			dialog.text = "Charles de Maure, richtig?";
			link.l1 = "Nach deinem Gesichtsausdruck zu urteilen, würde ich sagen, du kennst bereits die Antwort. Also, was willst du?";
			link.l1.go = "PZ_LigaInJungle_2";
		break;
		
		case "PZ_LigaInJungle_2":
			dialog.text = "Dein Kopf.";
			link.l1 = "Faszinierend! Ich muss sagen, ich mag, wie dieses Gespräch beginnt. Aber bevor wir weitermachen, könnten Sie mir zumindest sagen, wen ich beleidigt habe? Vielleicht können wir verhandeln.";
			link.l1.go = "PZ_LigaInJungle_3";
		break;
		
		case "PZ_LigaInJungle_3":
			dialog.text = "Wir sind keine Amateure, Monsieur de Maure. Selbst wenn wir es Ihnen sagen würden, es würde Ihnen nicht helfen - unser Auftraggeber hat das Archipel bereits verlassen. Sie können ihnen keinen Schaden zufügen oder eine Entschuldigung anbieten. Wir wurden bezahlt und jetzt ist es an der Zeit, unseren Teil des Geschäfts einzuhalten.";
			link.l1 = "Wenn Sie bereits bezahlt wurden, warum noch mehr Blut vergießen?";
			link.l1.go = "PZ_LigaInJungle_4";
		break;
		
		case "PZ_LigaInJungle_4":
			dialog.text = "Wir sind keine Amateure. Wir schätzen unseren Ruf.";
			link.l1 = "Ich fürchte, diesmal wirst du dem nicht gerecht werden können.";
			link.l1.go = "PZ_LigaInJungle_5";
		break;
		
		case "PZ_LigaInJungle_5":
			dialog.text = "Wir werden sehen. Durchsucht seine Leiche, wenn wir fertig sind! Verbrennt alles, was ihr findet!";
			link.l1 = "Brennen was?..";
			link.l1.go = "PZ_LigaInJungle_6";
		break;
		
		case "PZ_LigaInJungle_6":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("LigaInJungle_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_LigaInJunglePosleBitvy");
			
			if (CharacterIsHere("Longway"))
			{
				sld = characterFromId("Longway");
				LAi_SetCheckMinHP(sld, 1, true, "");
			}
		break;
		
		case "PZ_Longway_1":
			dialog.text = "Was der maskierte Mann gesagt hat... Könnte es sein...?";
			link.l1 = "Was ist los, Longway? Es ist nicht das erste Mal, dass Kopfgeldjäger hinter mir her sind, aber du scheinst ungewöhnlich besorgt zu sein.";
			link.l1.go = "PZ_Longway_2";
		break;
		
		case "PZ_Longway_2":
			dialog.text = "Longway glaubt zu wissen, wer diese Männer auf Sie angesetzt hat, Herr Kapitän.";
			link.l1 = "Gibt es etwas, worüber ich Bescheid wissen sollte?";
			link.l1.go = "PZ_Longway_3";
		break;
		
		case "PZ_Longway_3":
			dialog.text = "Das ist Lord Rodenburgs Methode - diejenigen zu eliminieren, die ihm geholfen haben, aber zu viel wissen.";
			link.l1 = "Wirklich... Dieser maskierte Mann hat gesagt, sein Arbeitgeber hätte kürzlich den Archipel verlassen. Das ist genau das, was Lucas vorhatte! Denken Sie, wir sollten weitere Angriffe erwarten?";
			link.l1.go = "PZ_Longway_4";
		break;
		
		case "PZ_Longway_4":
			dialog.text = "Es ist klug, auf alles vorbereitet zu sein, Herr Kapitän.";
			link.l1 = "Weise Worte. Wir werden es sein. Aber was wollte Lucas? Was dachte er, hätte ich? Irgendwelche Ideen, Longway?";
			link.l1.go = "PZ_Longway_5";
		break;
		
		case "PZ_Longway_5":
			dialog.text = "Mm-mm, nein, Longway hat keine Ahnung, was es sein könnte.";
			link.l1 = "Das ist schade. Aber gut, lass uns hier raus.";
			link.l1.go = "PZ_Longway_6";
		break;
		
		case "PZ_Longway_6":
			DialogExit();
			
			Return_LongwayOfficer();
			
			chrDisableReloadToLocation = false;
			pchar.questTemp.PZ_RazgovorGerrits = true;
			pchar.questTemp.PZ_PodozrenieLucas = true;
		break;
		
		// Этап 1, ВЕРНЫЙ КЛЯТВЕ
		case "PZ_Longway_11":
			dialog.text = "Mein Herr Kapitän, Longway möchte mit Ihnen sprechen. Es ist von großer Wichtigkeit.";
			if (CheckAttribute(pchar, "questTemp.PZ_PodozrenieLucas"))
			{
				link.l1 = "Was ist los, Longway? Bist du wegen Lucas' Art, sich zu verabschieden, besorgt, oder hast du etwas Neues entdeckt?";
				link.l1.go = "PZ_Longway_12";
				AddCharacterExpToSkill(pchar, "Sneak", 100);
			}
			else
			{
				link.l1 = "Sicher! Was beschäftigt Sie?";
				link.l1.go = "PZ_Longway_13";
			}
		break;
		
		case "PZ_Longway_12":
			dialog.text = "Leider nein.";
			link.l1 = "Dann was ist es, Longway?";
			link.l1.go = "PZ_Longway_13";
		break;
		
		case "PZ_Longway_13":
			dialog.text = "Longway kann es nicht sagen. Aber... er möchte um Erlaubnis bitten, zu gehen.";
			link.l1 = "Verlassen? Wie, für immer? Warum, Longway? Als dein Kapitän habe ich das Recht, den Grund zu wissen.";
			link.l1.go = "PZ_Longway_14";
		break;
		
		case "PZ_Longway_14":
			dialog.text = "Das ist wahr, Herr Kapitän. Aber Longway ist weder ein Arbeiter noch ein Diener. Er kam aus freiem Willen zu helfen, und er kann auf die gleiche Weise gehen. Es wird nicht für immer sein - es gibt eine wichtige Angelegenheit zu erledigen. Longway hofft, zurückzukehren, sobald es erledigt ist.";
			link.l1 = "Was ist das Problem? Erzählen Sie mir - wenn nicht als Ihr Kapitän, dann als jemand, der viel mit Ihnen durchgemacht hat.";
			link.l1.go = "PZ_Longway_15";
		break;
		
		case "PZ_Longway_15":
			dialog.text = "Alles, was Longway sagen kann, ist, dass er vor langer Zeit ein Gelübde abgelegt hat. Die Zeit ist gekommen, es zu erfüllen. Andernfalls... hat Longways Leben keinen Sinn.";
			link.l1 = "Du hast recht, Longway - du bist kein Gefangener, und ich bin kein Kerkermeister. Du bist frei zu gehen. Gott mit dir.";
			link.l1.go = "PZ_Longway_Otpustit_1";
			link.l2 = "Du kannst gehen, aber sag mir wenigstens, wohin du gehst. Ich könnte helfen, ohne zu viele Fragen zu stellen.";
			link.l2.go = "PZ_Longway_Pomoch_1";
			link.l3 = "Ich habe auch eine wichtige Aufgabe - meinen Bruder zu retten. Dafür brauche ich jeden Mann, einschließlich dich, Longway. Ohne dich können wir es nicht schaffen.";
			link.l3.go = "PZ_Longway_NeOtpuskaem_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_1":
			dialog.text = "Versuchen Sie nicht, auf mein Mitleid oder Pflichtgefühl zu spielen. Ich verstehe vollkommen. Haben Sie jemals ein Gelübde abgelegt, Herr Kapitän?";
			link.l1 = "Natürlich habe ich. Also erzähl mir alles, wie es ist, und meine Männer und ich werden dir sicherlich helfen.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_2";
		break;
		
		case "PZ_Longway_NeOtpuskaem_2":
			dialog.text = "Longway kann nicht. Einfach... kann nicht. Es ist ein großes Geheimnis, und nicht einmal meins, um es zu teilen.";
			link.l1 = "Das ist schade. Ich dachte, zwischen uns besteht Vertrauen. Du verlässt das Schiff nicht - Ich habe jetzt alle Offiziere auf meiner Seite.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_3";
			link.l2 = "Du hast recht, Longway - du bist kein Gefangener und ich bin kein Kerkermeister. Du bist frei zu gehen. Gott mit dir.";
			link.l2.go = "PZ_Longway_Otpustit_1";
		break;
		
		case "PZ_Longway_NeOtpuskaem_3":
			dialog.text = "Das kannst du nicht tun!";
			link.l1 = "Leider kann ich das, Longway. Nun kehre zu deinen Pflichten zurück.";
			link.l1.go = "PZ_Longway_NeOtpuskaem_4";
		break;
		
		case "PZ_Longway_NeOtpuskaem_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_LongwayUhoditOtNasNavsegda.win_condition = "PZ_LongwayUhoditOtNasNavsegda";
		break;
		
		case "PZ_Longway_Otpustit_1":
			dialog.text = "Ich dachte nicht, dass Sie mich so leicht gehen lassen würden. Danke, Herr Kapitän.";
			link.l1 = "Ach, das ist nichts. Aber sag mir - wo kann ich dich finden, wenn deine Geschäfte erledigt sind?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
		break;
		
		case "PZ_Longway_Pomoch_1":
			dialog.text = "Longway kann wirklich nicht sagen, egal, wie sehr er es wünschte. Aber er schätzt die Bereitschaft des Herrn Kapitäns zu helfen.";
			link.l1 = "So sei es. Wo soll ich dich suchen, sobald du dein Gelübde erfüllt hast?";
			link.l1.go = "PZ_Longway_GdeIskat_1";
			pchar.questTemp.PZ_LongwayGood = true;
		break;
		
		case "PZ_Longway_GdeIskat_1":
			dialog.text = "Ich erwarte, meine Geschäfte in einem Monat abzuschließen. Danach wird Longway noch eine Woche lang in der Taverne in Basse-Terre auf dich warten.";
			link.l1 = "Nun, was auch immer du sagst, mein Freund. Es ist kein Abschied. Wir sehen uns in Basse-Terre.";
			link.l1.go = "PZ_Longway_GdeIskat_2";
		break;
		
		case "PZ_Longway_GdeIskat_2":
			DialogExit();
			
			RemovePassenger(pchar, npchar);
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.location = "None";
			
			SetQuestHeader("PZ");
			AddQuestRecord("PZ", "1");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			SetTimerCondition("PZ_IshemLongway", 0, 0, 30, false);	// ВЕРНУТЬ 30 дней
		break;
		
		case "PZ_SharliePlennik_BadFinal_1":
			dialog.text = "Nun, hallo, Kapitän.";
			link.l1 = "Ich mag dein Grinsen nicht, Herr.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_2";
		break;
		
		case "PZ_SharliePlennik_BadFinal_2":
			dialog.text = "Ich bin am Boden zerstört. Ich bin gekommen, um Ihnen zu sagen, dass Sie endlich frei sind. Aber wenn Sie länger in dieser luxuriösen Kabine bleiben möchten, sind Sie herzlich willkommen.";
			link.l1 = "Ganz und gar nicht. Also, Longway wurde gefunden? Wo ist er? In einer der Zellen?";
			link.l1.go = "PZ_SharliePlennik_BadFinal_3";
		break;
		
		case "PZ_SharliePlennik_BadFinal_3":
			dialog.text = "In einer anderen, passenderen Welt - er würde mit keinem von uns sprechen und direkt in die Schlacht gehen.";
			link.l1 = "Verdammt noch mal! Du hättest ihn einfach nur fangen können.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_4";
		break;
		
		case "PZ_SharliePlennik_BadFinal_4":
			dialog.text = "Einige Leute sind viel leichter zu töten als zu fangen, wissen Sie nicht? Sie sollten froh sein, dass wir Ihnen nichts vorwerfen - Ihr Chinese hat ein weiteres Massaker veranstaltet, und wir brauchten mehrere weitere Einheiten mit Scharfschützen, um mit ihm fertig zu werden.";
			link.l1 = "Ja, tatsächlich. Danke dafür.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_5";
		break;
		
		case "PZ_SharliePlennik_BadFinal_5":
			dialog.text = "Apropos, da er Ihr Freund war, haben wir einige Papiere bei ihm gefunden. Wir haben nicht verstanden, was sie waren - Sie würden wahrscheinlich besser Bescheid wissen. Auf den Teilen, die nicht blutgetränkt waren, stand irgendein Kauderwelsch.";
			link.l1 = "Das ist... Scheiße. Danke, dass du sie zurückgebracht hast. Auf Wiedersehen, Offizier.";
			link.l1.go = "PZ_SharliePlennik_BadFinal_6";
		break;
		
		case "PZ_SharliePlennik_BadFinal_6":
			DialogExit();
			
			LAi_ActorGoToLocator(npchar, "goto", "goto22", "", -1);
			DoQuestCheckDelay("PZ_SharliePlennik_BadFinal_2", 3.0);
		break;
		
		case "PZ_BasTerStop":
			dialog.text = "Kommen Sie mit uns, der Kommandant möchte mit Ihnen sprechen.";
			link.l1 = "Ich nehme an, das hat etwas mit meiner Suche nach dem Chinesen zu tun?";
			link.l1.go = "PZ_BasTerStop_2";
		break;
		
		case "PZ_BasTerStop_2":
			dialog.text = "Sie werden es selbst sehen, Monsieur.";
			link.l1 = "Werde ich irgendwie beschuldigt?";
			link.l1.go = "PZ_BasTerStop_3";
		break;
		
		case "PZ_BasTerStop_3":
			dialog.text = "Ganz und gar nicht. Niemand versucht, Sie zu verhaften oder festzuhalten. Zumindest jetzt nicht. Als ich sagte, der Kommandant wünscht mit Ihnen zu sprechen, meinte ich genau das.";
			link.l1 = "Ach, nun ja...";
			link.l1.go = "PZ_BasTerStop_4";
		break;
		
		case "PZ_BasTerStop_4":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_town")], false);
			DoQuestReloadToLocation("BasTer_prison", "goto", "goto17", "PZ_BasTer_TurmaPriveli");
		break;
		
		case "PZ_BasTer_OtryadPeshera_1":
			dialog.text = "Haben Sie irgendwelche Ideen? Dieser gelbhäutige Mann ist tödlich gefährlich. Wir sind nicht die erste Einheit, die hierher geschickt wurde. Befehle sind Befehle, aber ich möchte nicht dumm sterben, indem ich ohne einen soliden Plan hineingehe.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				link.l1 = "Er ist ganz alleine da drinnen, und ich bin bei dir. Ich kümmere mich um ihn - ihr konzentriert euch darauf, mich zu decken. Wir schaffen das.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "Ich habe eine. Ihr werdet alle sterben - genau hier.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				link.l1 = "Machen Sie sich keine Sorgen, wir werden nur mit ihm reden.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_2";
				if (pchar.location.from_sea != "BasTer_Town")
				{
					link.l2 = "Es tut mir leid, aber ihr werdet heute alle sterben. Und es wird nicht durch die Hand eines Chinesen geschehen.";
					link.l2.go = "PZ_BasTer_OtryadPeshera_Kill_1";
				}
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_1":
			pchar.questTemp.PZ_Podelnik = true;
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Also bist du kein Kopfgeldjäger... Aber selbst wenn du es bist, bist du ein Freund von diesem verdammten Chinesen!";
				link.l1 = "Das ist richtig. Ich müsste dich sowieso loswerden - keinen Sinn, das Unvermeidliche zu verzögern.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Was meinst du damit?! Du hast versprochen zu helfen!";
				link.l1 = "Ich denke, Sie hätten uns sowieso keinen friedlichen Ausweg gegeben. Es ist nichts Persönliches.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_Kill_2";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_Kill_2":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_OtryadPeshera_Kill_3");
		break;
		
		case "PZ_BasTer_OtryadPeshera_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Ich würde gerne glauben, dass das so ist.";
				link.l1 = "Ich habe Schlimmeres erlebt. Ein Chinese wird uns nicht das Ende bereiten. Los geht's, Jungs!";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Was ist, wenn das Gespräch nicht wie geplant verläuft?";
				link.l1 = "Ich würde das hassen, aber dann muss ich mich verteidigen. Lass uns gehen.";
				link.l1.go = "PZ_BasTer_OtryadPeshera_3";
			}
		break;
		
		case "PZ_BasTer_OtryadPeshera_3":
			DialogExit();
			
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload2", "PZ_IshemLongway_OtryadUPeshery");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway":
			dialog.text = "Herr Kapitän?! Longway kann nicht glauben, dass Sie bei ihnen sind!";
			link.l1 = "Nein, Longway, ich bin nur hier, um zu reden! Es ist nicht das, was du denkst!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_2":
			dialog.text = "Dann wären Sie alleine gekommen. Sie versuchen, meine Wachsamkeit zu senken, damit Sie mich mit Hilfe dieser Soldaten angreifen können!";
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayGood"))
			{
				link.l1 = "Wenn ich könnte, würde ich. Ich bin der einzige Grund, warum sie dich noch nicht angegriffen haben. Beruhige dich und lass uns reden, ja, gell?";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_3";
			}
			else
			{
				link.l1 = "Schnauze! Wenn ich gewollt hätte, hätte ich dich schon längst umgebracht. Leg deine Waffen nieder, und wir werden reden. Das ist ein Befehl von deinem Kapitän.";
				link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_3":
			dialog.text = "Jawohl. Longway vertraut Ihnen, Herr Kapitän.";
			link.l1 = "Dort, das ist besser. Jetzt erzähl mir...";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_4";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_4":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadom_DialogLongway_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_5":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Herr, was passiert hier? Was ist das... diese rührende Wiedervereinigung? Sie sollten uns doch helfen, diesen chinesischen Wilden zu beseitigen, nicht wahr?";
				link.l1 = "Ich bin es. Ich nehme ihn mit und all dieses Töten wird aufhören. Du wirst dem Kommandanten sagen, dass wir ihn zusammen getötet haben. Abmachung?";
				link.l1.go = "PZ_BasTer_SOtryadomOhotnik_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Gut gemacht, Kapitän! Er hat seine Waffen niedergelegt. Es ist gut, Sie bei uns zu haben. Jetzt bringen wir ihn zum Kommandanten.";
				link.l1 = "Warum sollte ich das tun? Ich habe eine Geldstrafe für die Taten von Longway bezahlt - eine großzügige. Ihre Kollegen Offiziere waren Zeugen - sie werden es bestätigen. Der Kommandant hat mir erlaubt, meinen Mann mit auf das Schiff zu nehmen.";
				link.l1.go = "PZ_BasTer_SOtryadomDrug_1";
			}
		break;
		
		case "PZ_BasTer_SOtryadomDrug_1":
			dialog.text = "Befehlshaber mag genug von diesem Blutgold haben, aber nicht ich. Einige der Männer, die er in dieser blutigen Höhle getötet hat, waren meine Freunde. Außerdem bezweifle ich, dass es ihm etwas ausmacht, wenn wir den Chinesen sowieso töten.";
			link.l1 = "Sicher, dass Sie es herausfinden wollen? Und über Ihre Freunde, die getötet wurden... haben Sie jemals von dieser dreisten Bande von Briganten gehört? Es müssen sie gewesen sein.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_2";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_2":
			StartInstantDialog("Longway", "PZ_BasTer_SOtryadomDrug_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_3":
			dialog.text = "";
			link.l1 = "Longway, Sie haben nicht so viele Soldaten getötet, wie sie behaupten, oder?";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_4";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_4":
			dialog.text = "Das stimmt, Herr Kapitän. Longway hat diese Bande gesehen. Sie haben sich tiefer in die Höhle versteckt, damit sie ihn nicht bemerken. Und Longway hörte die Geräusche von Gesprächen, Fluchen und Kämpfen zwischen den Banditen und den Soldaten.";
			link.l1 = "";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_5";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_5":
			StartInstantDialog("PZ_BasTer_OtryadPesheraOff", "PZ_BasTer_SOtryadomDrug_6", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_BasTer_SOtryadomDrug_6":
			dialog.text = "";
			link.l1 = "Sehen Sie? Es passt alles zusammen. Longway hat vielleicht einen schlechten Charakter, aber er ist ein ehrlicher Mann. Wir gehen. Wenn Sie uns anfassen, entehren Sie Ihre Uniform. Auf Wiedersehen, meine Herren.";
			link.l1.go = "PZ_BasTer_SOtryadomDrug_7";
		break;
		
		case "PZ_BasTer_SOtryadomDrug_7":
			DialogExit();
			
			AddQuestRecord("PZ", "13");
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_BasTer_OtryadRazveli", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_CharacterDisableDialog(sld);
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			LAi_SetImmortal(sld, false);
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_1":
			dialog.text = "Keine Chance, Monsieur! Er hat einen Haufen unserer Männer getötet, und jetzt sagst du, er kommt damit davon?! Entweder du hilfst uns, den Bastard zu töten, oder du hältst dich verdammt nochmal aus unserem Weg!";
			link.l1 = "Es tut mir leid, aber ich muss eingreifen. Wirklich, es tut mir leid.";
			link.l1.go = "PZ_BasTer_SOtryadomOhotnik_2";
		break;
		
		case "PZ_BasTer_SOtryadomOhotnik_2":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("PZ_BasTer_OtryadPesheraOff");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_CharacterDisableDialog(sld);
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_1":
			dialog.text = "Wenn Sie nur reden wollten, würden Sie mich nicht auffordern, mich zu entwaffnen. Aber ein Tiger bleibt ein Tiger, auch wenn seine Klauen eingezogen sind. Sie müssen sich schon vor langer Zeit entschieden haben, Longway zu verraten - es besteht keine Notwendigkeit zu lügen. Verteidigen Sie sich, Kapitän!";
			link.l1 = "Verdammt!";
			link.l1.go = "PZ_BasTer_SOtryadom_DialogLongway_Bad_2";
		break;
		
		case "PZ_BasTer_SOtryadom_DialogLongway_Bad_2":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_CharacterDisableDialog(sld);
			}
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_BasTer_MyUbilLongway_BadFinal");
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Ich kann nicht glauben, dass wir es mit ihm geschafft haben! Aber sag mir, warum hat er dich Kapitän genannt?";
				link.l1 = "Es ist komplizierter, als es aussieht, Kumpel. Ich musste Ihren Kommandanten beruhigen. Das Wichtigste ist das Ergebnis, oder? Und das Ergebnis ist, dass Longway tot ist und ich Ihnen dabei geholfen habe.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Sogar deine Anwesenheit hat nicht geholfen - er hat uns immer noch überfallen. Verfluchter Barbar...";
				link.l1 = "Du solltest nicht so über ihn reden. Er hat uns angegriffen, weil er verärgert war und dachte, ich wäre bei dir.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_2";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_2":
			if (CheckAttribute(pchar, "questTemp.PZ_OhotnikOtryad"))
			{
				dialog.text = "Vielleicht. In diesem Fall, auf Wiedersehen, Monsieur. Wir werden dem Kommandanten selbst sagen, dass der Chinese endlich tot ist.";
				link.l1 = "Sehr gut, danke. Auf Wiedersehen, Jungs.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DrugOtryad"))
			{
				dialog.text = "Nun, ob verärgert oder nicht, wild oder nicht, es ändert nichts - er hat vorher viele von uns getötet, hat zuerst Blut vergossen.";
				link.l1 = "Etwas muss ihn in diesen Zustand getrieben haben. Aber lassen wir das. Ich werde gehen, und Sie können zum Kommandanten zurückkehren, wann immer Sie es für richtig halten. Auf Wiedersehen.";
				link.l1.go = "PZ_BasTer_SOtryadom_UbiliLongway_3";
			}
		break;
		
		case "PZ_BasTer_SOtryadom_UbiliLongway_3":
			DialogExit();
			
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			ChangeCharacterNationReputation(pchar, FRANCE, 12);
			AddQuestRecord("PZ", "11");
			CloseQuestHeader("PZ");
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog":
			dialog.text = "Herr Kapitän?";
			link.l1 = "Aye! Ich habe überall nach dir gesucht, Longway. Du hast in der Stadt für ziemlich Aufregung gesorgt. Wir haben viel zu besprechen, also lass uns sofort zum Schiff zurückkehren.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_2";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_2":
			dialog.text = "Dort drüben!";
			link.l1 = "Ich sehe, wir haben Gesellschaft. Sieht so aus, als ob wir etwas spät dran sind.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_3";
			locCameraFromToPos(-12.27, 1.29, -8.89, true, -3.23, -1.20, -4.77);
			DoQuestCheckDelay("PZ_IshemLongway_SorraKomendant_Dialog_Povernutsya", 1.3);
			
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				LAi_SetHP(sld, 60.0, 60.0);
			}
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_3":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_CaveEntrance")], false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Longway");
			LAi_SetImmortal(sld, false);
			DeleteAttribute(sld, "OfficerImmortal");
			if(CheckAttribute(sld, "Health.HP")) DeleteAttribute(sld, "Health.HP");
			if(CheckAttribute(sld, "Health.maxHP")) DeleteAttribute(sld, "Health.maxHP");
			sTemp = "RestoreHealth_" + sld.index;
			if(CheckAttribute(PChar, "quest.RestoreHealth_" + sld.index)) PChar.quest.(sTemp).over = "Yes";
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("PZ_BasTer_OtryadPeshera"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_SorraKomendant_Pobeda1");
			
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition.l1.character = "Longway";
			PChar.quest.PZ_LongwayNelzyaUmeret.win_condition = "PZ_LongwayNelzyaUmeret";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_4":
			dialog.text = "Mehr kommen!";
			link.l1 = "Sture Bastarde - das muss ich ihnen lassen. Wir sind hier zu exponiert. Lasst uns zur Höhle gehen - dort können wir uns besser verteidigen.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_5";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_5":
			DialogExit();
			pchar.questTemp.PZ_IshemLongway_SorraKomendant = true;
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_6":
			dialog.text = "Wir können nicht für immer hier bleiben.";
			link.l1 = "Und das ist das Erste, was du nach allem, was passiert ist, sagen willst, Longway? Glaubst du nicht, dass es an der Zeit ist, dass du erklärst, was los ist?";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_7";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_7":
			dialog.text = "Herr Kapitän, Longway...";
			link.l1 = "Aber Sie haben recht - wir können nicht bleiben. Lassen Sie uns losgehen, bevor ein weiteres Trupp auftaucht. Wir reden auf dem Schiff, sobald wir in See gestochen sind.";
			link.l1.go = "PZ_IshemLongway_SorraKomendant_Dialog_8";
		break;
		
		case "PZ_IshemLongway_SorraKomendant_Dialog_8":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_1":
			dialog.text = "Die List und Bosheit des weißen Mannes kennt keine Grenzen.";
			link.l1 = "Hallo, ich bin auch ein Weißer! Außerdem hast du ihre Freunde und Kameraden getötet - sie haben das Recht, wütend zu sein.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_2";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_2":
			dialog.text = "Vergeben Sie ihnen, Herr Kapitän?";
			link.l1 = "Ich entbinde dich, Longway. Und ich rate dir, Menschen nicht nach ihrer Hautfarbe zu beurteilen. Du von allen Menschen solltest das verstehen. Wir wurden unterbrochen - wo waren wir...?";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_3";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_3":
			dialog.text = "Kapitän! Hinter dir!";
			link.l1 = "Oh, sie werden uns heute kein richtiges Gespräch führen lassen...";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_4";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_4":
			DialogExit();
			LAi_SetCurHPMax(pchar);
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			
			sld = CharacterFromID("Longway");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			for (i=6; i<=10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_BasTer_OtryadPeshera"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, 0, true, "soldier"));
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_SetHP(sld, 60.0, 60.0);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_IshemLongway_Zastupaemsya_5");
			
			AddDialogExitQuest("MainHeroFightModeOn"); // Rebbebion, fix
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_6":
			dialog.text = "Klar, Herr Kapitän.";
			link.l1 = "Das ist gut, aber wir sollten hier nicht verweilen. Du und ich haben viel zu besprechen. Folge mir - wir gehen zurück zum Schiff.";
			link.l1.go = "PZ_IshemLongway_Zastupaemsya_7";
		break;
		
		case "PZ_IshemLongway_Zastupaemsya_7":
			DialogExit();
			
			sld = CharacterFromID("Longway");
			AddPassenger(pchar, sld, false);
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
			
			LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
			LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
			//LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
			chrDisableReloadToLocation = false;
			bDisableLandEncounters = false;
			AddQuestRecord("PZ", "14");
			DeleteQuestCondition("PZ_LongwayNelzyaUmeret");
			DeleteQuestCondition("PZ_KorablBuhta_BadFinal");
			
			//Продолжение второго этапа
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition.l1 = "EnterToSea"
			PChar.quest.PZ_LongwayRazgovorVKaute.win_condition = "PZ_LongwayRazgovorVKaute";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_1":
			dialog.text = "Mein Herr Kapitän, bist du es wirklich...?";
			link.l1 = "Ja, Longway. Geht es dir gut?";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_2";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_2":
			dialog.text = "Longway geht es gut. Danke. Aber, Kapitän! Schau!";
			link.l1 = "Lauf zur Höhle, beeil dich! Es ist eine gute Verteidigungsposition!";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_3";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_3":
			DialogExit();
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			PlaySound("Interface\MusketFire1.wav");
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
			
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1", "Guadeloupe_Cave", "goto", "locator1", "PZ_IshemLongway_VPesheru", -1);
		break;
		
		case "PZ_IshemLongway_SrazuNashli_4":
			dialog.text = "Longway wird überprüfen, ob die Soldaten noch kommen.";
			link.l1 = "Wir gehen zusammen - wir können unsere Verteidigung gegen die gesamte Garnison nicht aufrechterhalten.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_5";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_5":
			dialog.text = "Ja, Herr Kapitän?";
			link.l1 = "Wir haben viel zu besprechen. Folgen Sie mir jetzt - wir müssen sofort den Anker lichten.";
			link.l1.go = "PZ_IshemLongway_SrazuNashli_6";
		break;
		
		case "PZ_IshemLongway_SrazuNashli_6":
			DoQuestReloadToLocation("Guadeloupe_CaveEntrance", "reload", "reload1", "PZ_IshemLongway_VyhodIsPeshery");
		break;
		
		// Этап 2, СТРАНИЦЫ ИСТОРИИ
		case "PZ_LongwayRazgovorOProshlom":
			dialog.text = "Vielen Dank noch einmal für Ihre Hilfe, Herr Kapitän. Ich bin sicher, Sie haben viele Fragen.";
			link.l1 = "Das ist milde ausgedrückt. Warum hast du diese Soldaten getötet? Du tötest nicht zum Vergnügen - das weiß ich.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_LongwayRazgovorOProshlom_2":
			dialog.text = "Nein, Longway tut es nicht. Die Soldaten versuchten, Longway zu stoppen, und Gefängnis war keine Option. Sie würden keinem Chinesen zuhören - nur ein Weißer bekommt diese Höflichkeit.";
			link.l1 = "Sie hören nicht immer auf andere Weiße, aber ich verstehe, was Sie meinen. Trotzdem, sie in der Stadt wie Vieh abzuschlachten? Was haben Sie in Basse-Terre gemacht?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_3":
			dialog.text = "Not only do white people often not listen to me; sometimes they won't even talk. And when they do, it's to call the guards. Longway didn't choose his skin or his eyes, but he's proud of who he is. When soldiers mock and threaten, Longway grows tired... and angry.";
			link.l1 = "Von nun an arbeiten wir zusammen. Die Leute reden mit mir, anstatt die Wachen zu rufen... normalerweise. Aber im Ernst, erzähl mir von deiner Mission. Lass mich dir helfen.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_4";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_4":
			dialog.text = "Bitte, Herr Kapitän, verstehen Sie Longway. Er hat geschworen, dies alleine zu tun. Drängen Sie ihn nicht. Das schulden Sie Longway zumindest.";
			link.l1 = "Ich bin wirklich dankbar, aber ich hätte damals van Merden selbst erledigen können. Allerdings waren wir von Anfang an quitt - du hast gesagt, ich hätte dein Gesicht gerettet, und du hast mein Leben gerettet. Jetzt habe ich dich wieder gerettet.";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) link.l1.go = "PZ_LongwayRazgovorOProshlom_5";
			else link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_5":
			dialog.text = "Hmm... Sie haben recht, Herr Kapitän. Longway glaubt, dass Sie sein wahrer Freund unter den weißen Männern sind. Einmal dachte er schon so, aber er wurde bitter enttäuscht. Erinnerst du dich an John Murdock? Johan van Merden?";
			link.l1 = "Wie seltsam, dass Sie van Merden erwähnen. Jemand hat vor kurzem einige Seiten direkt unter meiner Nase aus seinem Archiv gerissen. Hatte das mit Ihrem Fall zu tun? Haben Sie den Dieb gefunden?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_6";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_6":
			dialog.text = "Ich habe es getan. Der Dieb war... Longway. Er bedauert es sehr, Herr Kapitän. Damals wusste er nicht, ob er Ihnen voll vertrauen konnte.";
			if (sti(pchar.reputation.nobility) <= 60)
			{
				link.l1 = "Du redest von Freundschaft, aber du bestiehlst mich hinter meinem Rücken? Das ist das erste und letzte Mal, Longway. Verstehst du?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_1";
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(61))+")", "None");
			}
			else
			{
				link.l1 = "Und wie hast du das geschafft, Longway?";
				link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_1";
				notification("Reputation Check Passed", "None");
			}
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_1":
			dialog.text = "Longway versteht. Er meint es ernst.";
			link.l1 = "Ich hoffe es. Erzählen Sie mir jetzt, wie Sie zu diesem Leben gekommen sind - welches Versprechen Sie gemacht haben, wann und wem.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Grubim_2";
			if (CheckAttribute(pchar, "questTemp.PZ_NashliArhiv")) AddComplexSelfExpToScill(100, 100, 100, 100);
			notification("Longway disapproves", "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Grubim_2":
			dialog.text = "Ja, Mein Herr Kapitän\nLongway sucht die wichtigste noch lebende Person für ihn - Chang Xing.";
			link.l1 = "Chang Xing - ist er dein bester Freund?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_1":
			dialog.text = "Dank Ihrer Freundlichkeit haben sich der Rest der Crew schnell an mich gewöhnt und begonnen, mir zu vertrauen.";
			link.l1 = "Nun, ich verstehe. Du bist nicht einer für Lob, aber gute Arbeit, Longway... wenn du das Durcheinander bereinigt hast, das dein Eindringen hinterlassen hat.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_2";
			AddComplexLandExpToScill(200, 200, 0);
			pchar.questTemp.PZ_FlagArhiv = true;
			notification("Longway approves", "Longway");
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_2":
			dialog.text = "Richtig. Aber dafür ist jetzt keine Zeit.";
			link.l1 = "Ich denke nicht. Aber versuch das nicht noch einmal, ja? Wenn du etwas brauchst, frag einfach. Du kannst mir vertrauen. Jetzt erzähl mir von deinem Eid.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_Proshaem_3";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_Proshaem_3":
			dialog.text = "Natürlich ist Longway froh, seine Last mit Ihnen zu teilen, Herr Kapitän.\nLongway sucht die für ihn wichtigste noch lebende Person - Chang Xing.";
			link.l1 = "Chang Xing - ist er dein bester Freund?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_7";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_7":
			dialog.text = "Chang Xing ist meine Familie, meine Schwester. Sie verschwand vor Jahren. Um sie zu finden, sucht Longway diejenigen, die vielleicht wissen, wo sie ist.";
			link.l1 = "Was hat das mit van Merdens Archiv zu tun? Hängt es mit dem Verschwinden Ihrer Schwester zusammen?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_8";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_8":
			dialog.text = "Das ist richtig. Alles hängt zusammen. Longway und Johan trafen sich vor vielen Jahren, in dem Land, das ihr Formosa nennt, lange bevor ich zum Archipel kam.";
			link.l1 = "Sie kennen sich schon so viele Jahre? Und van Merden war involviert? Was für eine Geschichte! Was hatte er mit dem Verschwinden Ihrer Schwester zu tun?";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_9";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_9":
			dialog.text = "Er hat mir bei meiner Suche nach sehr schlechten Menschen geholfen - selbst nach den Maßstäben der weißen Männer. Oliveiro Fermentelos, Antoon van Diemen und Joep van der Vink.";
			link.l1 = "Nach ihren Namen zu urteilen, ist einer Portugiese und die anderen beiden sind Holländer.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_10";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_10":
			dialog.text = "Ja, das ist korrekt. Aber die Suche war erfolglos. Longway wartete geduldig auf die Führung des Himmels. Also als Sie van Merdens Archiv erhielten, beschloss ich, es zu studieren. Als ich die ersten Seiten fand, die Oliveiro erwähnten, riss ich sie heraus und floh aus der Kabine.";
			link.l1 = "Endlich passt alles in die Geschichte.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_11";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_11":
			dialog.text = "Aber die Geschichte selbst fängt gerade erst an. Mein Herr Kapitän, möchten Sie von Anfang an über Longways Suche erfahren? Sind Sie bereit, sich hinzusetzen und zuzuhören?";
			link.l1 = "Genau deshalb habe ich dich in die Kajüte gerufen. Mach weiter.";
			link.l1.go = "PZ_LongwayRazgovorOProshlom_12";
		break;
		
		case "PZ_LongwayRazgovorOProshlom_12":
			DialogExit();
			
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			DoQuestReloadToLocation("Formosa", "patrol", "patrol1", "PZ_Formosa_Start");
		break;
		
		case "PZ_Formosa_Tavern_1":
			dialog.text = "Chinesen sind hier nicht erlaubt. Dies ist ein respektables Etablissement, für respektable Menschen - nicht für Leute wie Sie.";
			link.l1 = "Ich habe nur eine Frage. Lass mich sie stellen, und ich werde gehen.";
			link.l1.go = "PZ_Formosa_Tavern_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_Tavern_2":
			dialog.text = "Lernen Sie zuerst ordentlich zu sprechen! Ich habe Ihnen gesagt - Ihre Art ist hier nicht willkommen.";
			link.l1 = "Wo kann ich Oliveiro Fermentelos finden? Sag es mir und ich werde meinen Weg fortsetzen.";
			link.l1.go = "PZ_Formosa_Tavern_3";
		break;
		
		case "PZ_Formosa_Tavern_3":
			dialog.text = "Bist du auch taub? Teste meine Geduld nicht, oder dieser ganze Raum wird bald von gelben Eingeweiden stinken.";
			link.l1 = "Mein Volk lebt hier schon seit Tausenden von Jahren. Das ist unsere Insel, und wir dürfen nicht einmal eine einfache Taverne betreten?";
			link.l1.go = "PZ_Formosa_Tavern_4";
		break;
		
		case "PZ_Formosa_Tavern_4":
			dialog.text = "Oh, du redest groß, oder? Dafür könntest du gehängt werden. Hau ab!";
			link.l1 = "..., Freund.";
			link.l1.go = "PZ_Formosa_Tavern_5";
		break;
		
		case "PZ_Formosa_Tavern_5":
			DialogExit();
			locCameraSleep(true);
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("PZ_Formosa_smuggler");
			LAi_CharacterEnableDialog(sld);
			//AddLandQuestMark(sld, "questmarkmain");
			LAi_Fade("PZ_Formosa1_9", "");
		break;
		
		case "PZ_Formosa_smuggler_1":
			dialog.text = "Ich habe von deinem großen Problem gehört, mein kleiner Freund. Du hättest nicht so laut sein sollen - falscher Name, falscher Ort.";
			link.l1 = "Kennen Sie etwas über diesen Mann?! Sagen Sie mir!";
			link.l1.go = "PZ_Formosa_smuggler_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_2":
			dialog.text = "Beruhige dich, Kumpel.";
			link.l1 = "Meine Entschuldigung.";
			link.l1.go = "PZ_Formosa_smuggler_3";
		break;
		
		case "PZ_Formosa_smuggler_3":
			dialog.text = "Ich will deine Entschuldigung nicht, aber dein Geld will ich. Vielleicht helfe ich dir dann. Ich bin Marcelo Schulte. Und du? Du hast Geld, oder?";
			link.l1 = "Mein Name ist Chang Tu. Ich habe Geld. Ist das genug?";
			link.l1.go = "PZ_Formosa_smuggler_4";
		break;
		
		case "PZ_Formosa_smuggler_4":
			dialog.text = "(pfeift) Escudos, Pesos, Gulden, Dublonen... und sogar einige von diesen seltsamen Münzen, die ihr Leute habt. Das wird reichen. Na gut, Chung Chung, ich werde sehen, was ich über den Mann herausfinden kann. Keine Sorge, ich bin fast jeden Tag hier, also ist dein Geld sicher. Schau täglich vorbei, und wir werden uns definitiv über den Weg laufen.";
			link.l1 = "Ich hoffe. Ich habe kein Geld mehr...";
			link.l1.go = "PZ_Formosa_smuggler_5";
		break;
		
		case "PZ_Formosa_smuggler_5":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A few days have passed,"+ NewStr() +"April 4, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_tavern", "goto", "goto1", "PZ_Formosa_Spustya4Dnya");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_11":
			dialog.text = "Ach, Chang-Chang! Du bist schon hier.";
			link.l1 = "Es ist Chang Tu.";
			link.l1.go = "PZ_Formosa_smuggler_12";
		break;
		
		case "PZ_Formosa_smuggler_12":
			dialog.text = "Macht nichts, Kumpel.";
			link.l1 = "Haben Sie herausgefunden, wo Oliveiro ist?";
			link.l1.go = "PZ_Formosa_smuggler_13";
		break;
		
		case "PZ_Formosa_smuggler_13":
			dialog.text = "Nein, keine Spur einer Idee.";
			link.l1 = "Mein Geld!";
			link.l1.go = "PZ_Formosa_smuggler_14";
		break;
		
		case "PZ_Formosa_smuggler_14":
			dialog.text = "Sei nicht so nervös! Würde ich es wagen, mich dir wieder zu nähern, wenn ich nichts herausgefunden hätte? Ich werde dich jemandem vorstellen, der Bescheid weiß. Und du hast Glück, er liebt euch Asiaten. Er hat sogar passende Diener - verdammt, sogar Dienerinnen. Sie lernen auch eure verdammte Sprache. Sein Name ist Johan van Merden. Er wird in einem zweistöckigen Haus in der Nähe der Residenz auf dich warten.";
			link.l1 = "Mein Dank.";
			link.l1.go = "PZ_Formosa_smuggler_15";
		break;
		
		case "PZ_Formosa_smuggler_15":
			DialogExit();
			
			locCameraSleep(true);
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload1_back", "PZ_Formosa1_11", -1);
			LAi_ActorGoToLocation(npchar, "goto", "goto3", "", "", "", "", -1);
			npchar.location = "None";
			LocatorReloadEnterDisable("Formosa", "houseSp1", false);
		break;
		
		case "PZ_Formosa_JohanVanMerden_1":
			dialog.text = "Sie sind anscheinend Chang Chang? Kommen Sie herein, seien Sie nicht schüchtern.";
			link.l1 = "Es ist Chang Tu.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2";
			DelLandQuestMark(npchar);
			locCameraFromToPos(-1.91, 2.06, -1.75, true, 2.23, -0.85, 0.85);
		break;
		
		case "PZ_Formosa_JohanVanMerden_2":
			dialog.text = "So ist das also? Meine Entschuldigungen. Dieser Marcelo und seine Parade von Witzen... Schade, dass sich so wenige für Ihre Kultur interessieren. Und das alles nur wegen einer anderen Sprache und der Form Ihrer Augen. Aber du bist intelligent. Im Gegensatz zu den Schwarzen, hehehe.";
			link.l1 = "(auf Mandarin) Also hat der Schmuggler nicht gelogen - du bist wirklich ein Mann der Kultur. Und du sprichst wirklich unsere Sprache?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_2a";
			link.l2 = "Mein Dank für die warmen Worte über meine Kultur. Sie müssen Johan van Merden sein?";
			link.l2.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_2a":
			dialog.text = "Oh... Ich habe nur ein paar Worte verstanden. Ich lerne noch, sehen Sie. Könnten Sie auf Niederländisch weitermachen?";
			link.l1 = "Wie Sie wünschen. Sie sind Johan van Merden?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_3";
		break;
		
		case "PZ_Formosa_JohanVanMerden_3":
			dialog.text = "Ja, Chung Tu, das bin ich. Ich höre, du suchst Oliveiro Fermentelos. Ich weiß, wo du ihn finden kannst, aber sag mir erst - warum suchst du ihn? Deine Antwort wird meine bestimmen.";
			link.l1 = "Er... hat mein letztes und liebstes Familienmitglied entführt-meine Schwester, Chang Xing.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_4";
		break;
		
		case "PZ_Formosa_JohanVanMerden_4":
			dialog.text = "Dann muss ich Sie enttäuschen, Chang Tu. Es gibt wahrscheinlich keine Hoffnung mehr für sie. Sie wurde wahrscheinlich an einen reichen Pflanzer oder an ein Bordell verkauft. So oder so, Sie werden sie nicht retten können.";
			link.l1 = "Ich glaube, Chang Xing lebt noch. Oliveiro hat sie ins Visier genommen. Sie hat ihn stolz abgelehnt. Er hat sie gestohlen, als ich nicht zu Hause war. Und... unsere Eltern getötet.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_5";
		break;
		
		case "PZ_Formosa_JohanVanMerden_5":
			dialog.text = "Ich... es tut mir so leid. Wenn das der Fall ist, könnte Chang Xing - richtig? - noch am Leben sein. Hier ist, was wir tun werden: Gib mir etwas Zeit, um herauszufinden, wo genau Oliveiro gerade ist. Sagen wir eine Woche. Dann sehen wir uns wieder. Triff mich vor den Stadttoren - wer weiß, welche Augen dir hier folgen. Ich möchte nicht mehr involviert sein, als ich es gewohnt bin, hoffe, du verstehst das.";
			link.l1 = "Ich bin... Ich bin Ihnen zutiefst dankbar, Mynheer van Merden. Ich freue mich auf unser nächstes Treffen.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_6";
		break;
		
		case "PZ_Formosa_JohanVanMerden_6":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A week has passed,"+ NewStr() +"April 11, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa_ExitTown", "goto", "goto3", "PZ_Formosa_Spustya7Dney");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_JohanVanMerden_11":
			dialog.text = "Hallo, Chung Tu. Ich sehe das Feuer in deinen Augen. Ich habe Neuigkeiten, aber sie sind nicht gut.";
			link.l1 = "Jede Nachricht ist von größter Bedeutung für mich. Bitte erzählen Sie mir, Mynheer van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_12";
		break;
		
		case "PZ_Formosa_JohanVanMerden_12":
			dialog.text = "Aye... Fermentelos ist vor etwa einem Monat nach Batavia aufgebrochen. Das ist die einzige Spur, die ich von ihm habe. Die gute Nachricht ist, dass er vorhat, dort eine Weile zu bleiben, also wenn du jetzt gehst, wirst du ihn erwischen. Die schlechte Nachricht? Er ist ein enger Freund von Generalgouverneur Anthony van Diemen. Du wirst ihm nicht nahe kommen.";
			link.l1 = "Diese Nachricht genügt. Meinen bescheidenen Dank an Sie, Mynheer van Merden. Ich werde sofort aufbrechen.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_13";
		break;
		
		case "PZ_Formosa_JohanVanMerden_13":
			dialog.text = "Etwas hat mir gesagt, dass du das sagen würdest, also habe ich beschlossen, die Chancen für dich und Chang Xing auszugleichen. Ich habe einen Brief an einen alten Freund von mir, Oliver Trust, geschrieben. Er besitzt einen Laden in Batavia. Er schuldet mir einen Gefallen, also wird er dir helfen.";
			link.l1 = "Ich... Ich weiß nicht, was ich sagen soll...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_14";
			//Log_Info("Вы получили письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Formosa_JohanVanMerden_14":
			dialog.text = "Ein einfaches „Danke“ genügt. Wenn du Oliveiro nicht in der Stadt findest, suche nach dem Morgenstern. Du kannst ihn immer über sein Schiff ausfindig machen. Viel Glück, mein Freund - du und deine Schwester werdet es brauchen.";
			link.l1 = "Vielen Dank von ganzem Herzen, Mynheer van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_15";
		break;
		
		case "PZ_Formosa_JohanVanMerden_15":
			DialogExit();
			LAi_SetStayType(pchar);
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Batavia,"+ NewStr() +"May 29, 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Batavia", "merchant", "mrcActive5", "PZ_Batavia_Puteshestvie");
			LaunchFrameForm();
		break;
		
		case "PZ_OliverTrust_1": //
			dialog.text = "Wer bist du und was machst du hier? Ich handle nicht mit deiner Art.";
			link.l1 = "Ich habe einen Brief für dich.";
			link.l1.go = "PZ_OliverTrust_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_OliverTrust_2":
			dialog.text = "Ach, der Bote! Obwohl ich heute keine Briefe erwartet habe. Bleib hier! Ich werde mal nachsehen.";
			link.l1 = "Sind Sie Oliver Trust? Van Merden hat mich zu Ihnen geschickt.";
			link.l1.go = "PZ_OliverTrust_3";
			//Log_Info("Вы отдали письмо");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_OliverTrust_3":
			dialog.text = "Ich kann lesen, wissen Sie. Normalerweise würde ich Sie wegschicken, aber Leute wie van Merden nehmen kein Nein zur Antwort. Endlich ist es an der Zeit, mit van Diemen abzurechnen.";
			link.l1 = "Mein Ziel ist Fermentelos. Was ist mit van Diemen?";
			link.l1.go = "PZ_OliverTrust_4";
		break;
		
		case "PZ_OliverTrust_4":
			dialog.text = "Das geht dich gar nichts an. Du solltest dankbar sein, dass ich dir überhaupt helfe. Jetzt hör gut zu, bevor ich entscheide, dass das eine schlechte Idee ist. Ich kenne Fermentelos. Er war eine Weile hier, aber jetzt ist er nicht mehr hier. Der Morgenstern verließ vor ein paar Wochen. Gott weiß, wann es zurück sein wird. Also hat sich dein Ziel geändert, und es ist ein Freund von Fermentelos...";
			link.l1 = "... van Diemen.";
			link.l1.go = "PZ_OliverTrust_5";
		break;
		
		case "PZ_OliverTrust_5":
			dialog.text = "Also. Sie wissen auch davon? Ich nehme an, Johan hat Ihnen davon erzählt? Oh, van Merden... du bist ein verwegenes Schwein. Aber da Sie bereits von van Diemen wissen, kennen Sie auch seine hohe Position, nicht wahr? Was ist Ihr Meisterplan, um zum Generalgouverneur zu gelangen? Sicherlich nicht, indem Sie seine Residenz stürmen!";
			link.l1 = "Chang Tu ist ein geschickter Krieger.";
			link.l1.go = "PZ_OliverTrust_6";
		break;
		
		case "PZ_OliverTrust_6":
			dialog.text = "Ein geschickter Krieger, hm? Dir ist klar, dass wir jetzt alle verwickelt sind? Und was passiert mit mir, wenn du gefangen wirst? Ich muss dir zu deiner eigenen Sicherheit und meiner helfen. Abgesehen von seinem Aufenthalt in seiner Residenz, besucht Van Diemen regelmäßig die Plantage außerhalb der Stadt und seine Geliebte Vette.";
			link.l1 = "Sie haben erwähnt, mir zu helfen.";
			link.l1.go = "PZ_OliverTrust_12";
		break;
		
		case "PZ_OliverTrust_12":
			dialog.text = "Ich glaube, jeder sollte eine Leidenschaft, ein Hobby haben. Was mich betrifft, so sammle ich seltene und teure Waffen. Manchmal haben sie eine Geschichte, manchmal nicht, aber sie sind immer tödlich. Meine Sammlung kann für Ihren Kreuzzug nützlich sein. Also, sagen Sie mir, wo planen Sie, van Diemen zu überfallen?";
			link.l1 = "(Residenz) Da Sie so viele gute Waffen haben, werde ich das beste Schwert nehmen. Damit wird Chang Tu unter den Weißen unübertroffen sein.";
			link.l1.go = "PZ_OliverTrust_resedinsia_1";
			link.l2 = "(Plantage) Ich werde sie auf der Plantagenstraße überfallen - sie werden keinen Ort zum Laufen haben.";
			link.l2.go = "PZ_OliverTrust_Plantation1";
			link.l3 = "(Herrin) Die Herrin - es werden nicht viele Leute da sein, also werden die Wachen nicht rechtzeitig reagieren.";
			link.l3.go = "PZ_OliverTrust_lubovnitsa_1";
			SetCharacterPerk(pchar, "Gunman");
			SetCharacterPerk(pchar, "GunProfessional");
			InterfaceStates.Buttons.Save.enable = false;
		break;
		
		// Rebbebion, ну, с Богом...
		case "PZ_OliverTrust_Plantation1":
			pchar.questTemp.PZ_Batavia_plantation_Go = true;
			
			dialog.text = "Gute Wahl! Ich bin beeindruckt. Um das Beste daraus zu machen, benötigen Sie eine gute Feuerwaffe. Sag mir, wie weit kannst du zielen, Chang Tu?";
			link.l1 = "Um ehrlich zu sein... nicht zu weit, ich muss sicherstellen, dass ich nicht vorbeischieße."link.l1.go ="PZ_OliverTrust_Plantation_MediumDistance1";
			link.l2 = "Ich werde aus der Ferne angreifen - mein Feind wird nicht einmal realisieren, woher ich ihn getroffen habe.";
			link.l2.go = "PZ_OliverTrust_Plantation_FarDistance1";
			notification("Jager Unlocked", "Longway");
			SetCharacterPerk(pchar, "Jager");
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket6"); 
			EquipCharacterByItem(pchar, "mushket6");
			//Log_Info("Вы получили башенный мушкетон");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "grapeshot", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "grapeshot");
			
			dialog.text = "Ich verstehe. In diesem Fall, nimm das! Eine antike portugiesische Turmblunderbuss, die eine großkalibrige Patrone abfeuert. Solche werden nicht mehr hergestellt, selbst in der Alten Welt.";
			link.l1 = "Ich habe als Kind einen gesehen...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance2";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance2":
			dialog.text = "Also, weißt du, wie man es benutzt?";
			link.l1 = "Nein...";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance3";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance3":
			dialog.text = "Denken Sie daran, der austauschbare Mechanismus ist im Laufe der Zeit rostig geworden. Kein Öl wird es reparieren - es ist für immer kaputt. Es ist schwierig, es aufzuladen, also lass es uns jetzt tun. Beobachten Sie genau - verwenden Sie ein wenig Kraft, so wie das. Aber nicht zu stark, oder Sie werden es brechen.";
			link.l1 = "So wie das?";
			link.l1.go = "PZ_OliverTrust_Plantation_MediumDistance4";
		break;
		
		case "PZ_OliverTrust_Plantation_MediumDistance4":
			dialog.text = "Genau.";
			link.l1 = "Verstanden. Vielen Dank!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_Plantation_FarDistance1":
			// делаем Лонгвэя мушкетёром с одновременной выдачей мушкета
			/* pchar.model = "Longway_mush";
			pchar.model.animation = "mushketer"; */
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			GiveItem2Character(pchar, "mushket2x2"); 
			EquipCharacterByItem(pchar, "mushket2x2");
			//Log_Info("Вы получили двуствольный штуцер");
			PlaySound("interface\important_item.wav");
			
			AddItems(pchar, "cartridge", 50);
			AddItems(pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(pchar, GUN_ITEM_TYPE, "cartridge");
			
			dialog.text = "Ein wahrer Jäger! Sei vorsichtig, das war ein Geschenk. Es ist einer dieser seltenen Fälle, in denen eine Waffe sowohl kunstvoll als auch tödlich ist. Ein doppelläufiges Jagdgewehr! Schwer zu halten, einfach zu benutzen. Hast du schon herausgefunden, wie man es abfeuert?";
			link.l1 = "Verstanden. Vielen Dank!";
			link.l1.go = "PZ_OliverTrust_13";
		break;
		
		case "PZ_OliverTrust_lubovnitsa_1":
			dialog.text = "Sie haben recht mit den Wachen, aber unterschätzen Sie nicht die Gefahr. Van Diemen geht nie irgendwo in der Stadt ohne seinen rechten Hand, Joep van der Vink.";
			link.l1 = "Also, sie sind zusammen mit Vette...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_2";
			pchar.questTemp.PZ_Batavia_lubovnitsa_Go = true;
			AddCharacterSkillDontClearExp(pchar, "Sailing", 10);
			AddCharacterSkillDontClearExp(pchar, "Commerce", 10);
			AddCharacterSkillDontClearExp(pchar, "Repair", 10);
			notification("Naval Skills +", "Longway");
			notification("Rat Wolf Unlocked", "Longway");
			SetCharacterPerk(pchar, "RatsWolf");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_2":
			dialog.text = "Was? Ha! Du hast eine ziemlich lebhafte Fantasie, Chinesenmann! Antoon ist ein Feigling, und van der Vink ist da, um ihn zu schützen, falls jemand ihre „privaten Stunden“ stört. /nJoep trägt immer schwere Schützengrabenrüstung - unempfindlich gegen die meisten Kaltwaffen. Deshalb brauchst du auch etwas Besonderes. Nimm diesen Degen. Er ist lang, stärker als die meisten anderen Schwerter, und wiegt wie eine gute Klinge.";
			link.l1 = "Ein Degen zum Kampf gegen gepanzerte Feinde...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_3";
			//Log_Info("Вы получили асоледу");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_26");
			EquipCharacterByItem(Pchar, "blade_26");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_3":
			dialog.text = "Zielen Sie nicht auf die Rüstung selbst - es ist kein Estoc. Schlagen Sie in die Spalten und anfälligen Stellen, wie die Leistengegend, die Achselhöhlen und den Hals. Zermürben Sie ihn, diktieren Sie die Bedingungen. Joep führt auch eine schwere Axt, also versuchen Sie nicht, seine Schläge zu parieren - weichen Sie stattdessen aus/nFalls Sie keine Öffnung finden, nehmen Sie diesen Donnerbüchse. Sie ist normalerweise mit Schrot geladen, aber ich habe einen Satz Stahlpfeile für Sie vorbereitet.";
			link.l1 = "Pfeile für ein Musket...?";
			link.l1.go = "PZ_OliverTrust_lubovnitsa_4";
			//Log_Info("Вы получили бландербуз");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "pistol8");
			EquipCharacterByItem(Pchar, "pistol8");
			AddItems(Pchar, "harpoon", 30);
			AddItems(Pchar, "gunpowder", 30);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "harpoon");
		break;
		
		case "PZ_OliverTrust_lubovnitsa_4":
			dialog.text = "Ungewöhnlich, nicht wahr? Eine Mischung aus Alt und Neu. Sie ist darauf ausgelegt, mit einer Hand abgefeuert zu werden, aber wenn sie zu schwer ist, benutze beide. Viele tun das/nUnd hier, probiere diese Weidenrüstung. Sie ist leichter als Joeps Kürass, bietet aber immer noch anständigen Schutz. Lass nicht zu, dass seine Axt einen direkten Treffer landet - selbst eine Mailänder Rüstung würde einem solchen Waffenschlag nicht standhalten. Verstehst du?";
			link.l1 = "Ja, ich verstehe. Danke, Herr Vertrauen!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили кожаный корсет");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "cirass5");
			EquipCharacterByItem(Pchar, "cirass5");
		break;
		
		case "PZ_OliverTrust_resedinsia_1":
			dialog.text = "Übermütig, sind Sie? Vielleicht habe ich Ihnen zu früh von meiner Sammlung erzählt. Aber... Sie sind bereits verpflichtet. Ein Wohnsitz bei Tageslicht anzugreifen ist ein kühner Zug, nicht zu erwarten. Diese Klinge sollte Ihren Bedürfnissen entsprechen. Sie ist nicht die feinste der Welt, aber perfekt zum Stechen, Schlagen und Hacken.";
			link.l1 = "Clewang! Ich erkenne diese Klinge. Leute von den Nachbarinseln benutzen oft eine solche.";
			link.l1.go = "PZ_OliverTrust_resedinsia_2";
			pchar.questTemp.PZ_Batavia_resedinsia_Go = true;
			notification("Duelist Unlocked", "Longway");
			SetCharacterPerk(pchar, "FencingMaster");
			SetCharacterPerk(pchar, "HT1");
		break;
		
		case "PZ_OliverTrust_resedinsia_2":
			dialog.text = "Have you used one before? Good. You'll have little time and many enemies to face. Here, take this as well - a handgun with three barrels, beautifully inlaid. Load it now in front of me; you won't have time for that later. And wear this dueling waistcoat. It's light, it will give you the speed you'll need, and some protection.";
			link.l1 = "Danke, Mynheer Trust!";
			link.l1.go = "PZ_OliverTrust_13";
			//Log_Info("Вы получили клеванг");
			//Log_Info("Вы получили трёхствольный дробовик");
			//Log_Info("Вы получили жилет бретера");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(PChar, "blade_30");
			EquipCharacterByItem(Pchar, "blade_30");
			GiveItem2Character(PChar, "pistol2");
			EquipCharacterByItem(Pchar, "pistol2");
			GiveItem2Character(PChar, "cirass6");
			EquipCharacterByItem(Pchar, "cirass6");
			AddItems(Pchar, "grapeshot", 50);
			AddItems(Pchar, "gunpowder", 50);
			LAi_SetCharacterUseBullet(Pchar, GUN_ITEM_TYPE, "grapeshot");
		break;
		
		case "PZ_OliverTrust_13":
			dialog.text = "Warte, wir sind noch nicht fertig. Es liegt in unserem beiderseitigen Interesse, dass du überlebst. Nimm diese Medizin, um deine Wunden nach der Schlacht zu heilen. \nUnd nimm auch dieses Elixier. Es schmeckt und riecht schrecklich, aber es tötet jedes Gift in deinem Körper. Joep van der Vink, der Leibwächter von Van Diemen, schmiert seine Waffen mit dieser Scheiße. Überheblicher Bastard, also wirst du im Vorteil sein.";
			link.l1 = "Ich weiß nicht, ob ich Ihnen jemals genug danken kann, Mynheer Trust...";
			link.l1.go = "PZ_OliverTrust_14";
			//Log_Info("Вы получили 10 лечебных зелий");
			//Log_Info("Вы получили противоядие");
			PlaySound("interface\important_item.wav");
			AddItems(Pchar, "potion1", 10);
			AddItems(Pchar, "potion3", 1);
		break;
		
		case "PZ_OliverTrust_14":
			dialog.text = "Ihre beste Danksagung wäre es, mich nicht zu verraten, wenn Sie erwischt werden. Obwohl sie Sie höchstwahrscheinlich direkt töten werden. Aber wenn Sie das überleben, sagen Sie Van Diemen, dass er seinen Tod mir verdankt. Können Sie das tun?";
			link.l1 = "Kein Problem. Danke nochmals, Mynheer Trust. Auf Wiedersehen!";
			link.l1.go = "PZ_Batavia_NaOhotu";
		break;
		
		case "PZ_Batavia_NaOhotu":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				DoQuestReloadToLocation("Batavia", "reload", "reload1", "PZ_Batavia_BitvaSoStrazhnikami");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				DoQuestReloadToLocation("Batavia_HouseF3", "reload", "reload1", "PZ_Batavia_BitvaLubovnitsa");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				/*EndQuestMovie();
				sld = &Locations[FindLocation("Batavia_plantation")];
				sld.locators_radius.quest.detector4 = 3.0;
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1 = "locator";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.location = "Batavia_plantation";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator_group = "quest";
				PChar.quest.PZ_Batavia_plantation1.win_condition.l1.locator = "detector4";
				PChar.quest.PZ_Batavia_plantation1.win_condition = "PZ_Batavia_plantation_selfdialog";*/
				DoQuestReloadToLocation("Batavia_plantation", "quest", "detector2", "PZ_Batavia_plantation_setguards");
			}
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_1":
			dialog.text = "Halt! Wohin gehst du, Chinese?";
			link.l1 = "Zur Residenz.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_2";
			locCameraFromToPos(-0.44, 7.45, 24.65, true, -1.90, 5.10, 18.50);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_2":
			dialog.text = "Das war eine rhetorische Frage, Genie. Was lässt dich denken, dass jemand wie du dort hineingelassen würde?";
			link.l1 = "Ich habe Geschäfte mit Mynheer Van Diemen. Lassen Sie mich bitte durch.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_3";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_3":
			dialog.text = "Sie kennen den Namen des Generalgouverneurs? Nun... sagen Sie mir, was Ihr Anliegen ist. Ich werde es weiterleiten und mich mit einer Antwort bei Ihnen melden.";
			link.l1 = "Mein Gespräch ist nur mit Mynheer Van Diemen. Er wartet auf mich. Tretet zur Seite, oder ihr werdet es bereuen.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_4";
			locCameraSleep(true);
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_4":
			dialog.text = "Nun, nun, krähe nicht, Schlitzaugen. Entweder auf meine Weise oder gar nicht.";
			link.l1 = "Mein Weg dann.";
			link.l1.go = "PZ_Batavia_BitvaSoStrazhnikami_5";
		break;
		
		case "PZ_Batavia_BitvaSoStrazhnikami_5":
			DialogExit();
			LAi_SetActorType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_SoldResid_1"));
			LAi_group_MoveCharacter(pchar, LAI_GROUP_PLAYER);
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			
			sld = CharacterFromID("PZ_SoldResid_1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
				
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			DoQuestCheckDelay("PZ_Batavia_resedinsia_1", 0.9);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_1":
			dialog.text = "Verdammter Bauer! Wer hat dich angestellt? Ich werde dir mehr zahlen als das!";
			link.l1 = "Sie Weißen kümmern sich nur um Gold. Mögen die Drachen Ihre Art verfluchen. Ich bin wegen Informationen gekommen, aber Ihre Leute lassen mich nicht rein.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_2":
			dialog.text = "Was wollen Sie?!";
			link.l1 = "Fermentelos. Wo ist er jetzt?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_3":
			dialog.text = "Oliveiro? Aber warum zum Teufel willst du ihn? Ich sag dir nichts!";
			link.l1 = "Er hat meine Familie getötet und meine Schwester entführt. Mein Rat an dich ist, zu reden. Zu deinem eigenen Wohl.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_4":
			dialog.text = "Was wirst du mit mir machen? Die ganze Garnison wird bald hier sein.";
			link.l1 = "Haben Sie von Lynchy gehört? Es ist eine Strafe in meiner Kultur. Es bedeutet 'Tod durch tausend Schnitte'.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_5":
			dialog.text = "Du wirst keine Zeit haben, mir so viele Schnitte zuzufügen, du Idiot!";
			link.l1 = "Es ist eine Redewendung. Der Henker fügt Schnitte zu, einen nach dem anderen. Oder schneidet Teile des Körpers ab. Wir machen so viel, wie wir Zeit haben - es sei denn, du fängst an zu reden.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_6":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Sepp", "mercen_26", "man", "man", sti(pchar.rank), HOLLAND, -1, false, "quest"));
			sld.name = "Joep";
			sld.lastname = "van der Vink";
			GiveItem2Character(sld, "topor_04");
			EquipCharacterByItem(sld, "topor_04");
			GiveItem2Character(sld, "pistol3");
			EquipCharacterByItem(sld, "pistol3");
			sld.CantLoot = true;
			LAi_SetHP(sld, 300.0, 300.0);
			ChangeCharacterAddressGroup(sld, "Batavia_townhallRoom", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			
			LAi_SetStayType(pchar);
			locCameraFromToPos(-3.06, 1.64, -0.43, true, 1.87, -1.20, 2.39);
			DoQuestCheckDelay("PZ_Batavia_BitvaResidensia_7", 2.5);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_7":
			dialog.text = "A-A-A!!! Halt! Halt, du dreckiges Biest. Ich werde es dir sagen, ich werde dir alles sagen. Hör einfach auf. Joep! Endlich! Wo zum Teufel warst du die ganze Zeit?!";
			link.l1 = "Welch schlechte Zeit...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_9":
			dialog.text = "Antoon? Du musst sofort einen Arzt aufsuchen. Ich helfe dir dorthin zu kommen, sobald ich hier fertig bin. Du! Was zum Teufel machst du, du gelber Metzger?!";
			link.l1 = "Gelber Metzger? Das gefällt mir irgendwie. Es gibt nur eine Frage, die ich beantwortet haben möchte, aber niemand scheint bereit dazu zu sein...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_10":
			dialog.text = "Welche Frage?!";
			link.l1 = "Wo ist Oliveiro Fermentelos? Kannst du mir das nicht einfach sagen?";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_11":
			dialog.text = "Es ist mir scheißegal um Fermentelos! Wer hat dir das Geld und die Informationen gegeben?!";
			link.l1 = "Oliver Trust. Übrigens wollte er mir sagen, dass du ihm deinen Tod schuldest.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12";
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_ActorSetGroundSitMode(sld);
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_12":
			dialog.text = "Vertrauen?! Ha-ha-ha-ha-ha-ha-ha! Dieser Geizhals, denkt er, er könnte Rache nehmen, nur weil wir seine Plantage genommen haben? Wir werden bald seinen Laden und sein Leben nehmen, wenn ich mit dir fertig bin.";
			link.l1 = "Du verschwendest meine Zeit.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_13":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1 = "NPC_Death";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition.l1.character = "PZ_Sepp";
			PChar.quest.PZ_Batavia_BitvaResidensia_8.win_condition = "PZ_Batavia_BitvaResidensia_8";
		break;
		
		case "PZ_Batavia_PlantationSelfDialog":
			dialog.text = "(auf Mandarin) Also, suchen wir einen guten Hinterhaltplatz.";
			if (CheckCharacterItem(pchar, "mushket6"))
			{
				link.l1 = "(auf Mandarin) Mit diesem rostigen Ding muss ich nahe ran kommen. Eine schnelle Salve - scharf und gnadenlos. Angst und Panik werden den Rest erledigen.";
				link.l1.go = "Exit";
			}
			else
			{
				link.l1 = "(auf Mandarin) Genau hier. Sie werden mich erst gar nicht bemerken. Die besten Schlachten sind die, die nicht beginnen... oder die schnell mit wenig Blutvergießen enden.";
				link.l1.go = "Exit";
			}
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_Batavia_PlantationFight");
		break;
		
		case "PZ_Batavia_PlantationDimen1":
			if (!CharacterIsAlive("PZ_SoldPlantation_1") && !CharacterIsAlive("PZ_SoldPlantation_2") &&  !CharacterIsAlive("PZ_SoldPlantation_3") && !CharacterIsAlive("PZ_SoldPlantation_4") && !CharacterIsAlive("PZ_SoldPlantation_5") && !CharacterIsAlive("PZ_SoldPlantation_6"))
			{
				dialog.text = "Widerlicher Schuft... Entlaufener Sklave, nicht wahr? Woher hast du solch eine Waffe? Hat dich jemand angeheuert...?";
				link.l1 = "Keine Zeit! Sag mir, wo Oliveiro Fermentelos ist - jetzt!";
				link.l1.go = "PZ_Batavia_PlantationDimen2";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_PlantationDimenSit");
			}
		break;
		
		case "PZ_Batavia_PlantationDimen2":
			dialog.text = "Hehehe, lustig... Es gibt keine Zeit - das Blut strömt aus meinem Bauch. Brenne in der Hölle, Heide...";
			link.l1 = "(auf Mandarin) Nein!!!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_Batavia_PlantationDimenDead1");
		break;
		
		case "PZ_Batavia_Plantation_DimenDeadSelfDialog":
			dialog.text = "(auf Mandarin) Warum, warum, warum?! Wie soll ich jetzt Fermentelos finden?!";
			link.l1 = "Aber zuerst muss ich mich verstecken - jemand muss dieses Blutbad bereits gemeldet haben...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_1":
			dialog.text = "Hicks! Ein Chinese! Ich hätte nicht erwartet, dass jemand wie du hier eingeladen wird. Du schaust gerne zu, hm? Hehe.";
			link.l1 = "Warum sind hier so viele Leute...? Und wer sind Sie?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_2":
			dialog.text = "Erkennen Sie mich nicht an meiner Kleidung? Und passen Sie auf Ihren Ton auf, wenn Sie mit dem Generalgouverneur sprechen! Hic!";
			link.l1 = "Also, Sie müssen Mynheer Van Diemen sein. Ich bitte um Verzeihung für meine Unwissenheit. Ist hier ein Karneval im Gange?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_3";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_3":
			dialog.text = "Das ist richtig, mein guter Mann, und kein anderer Weg! Ein Karneval im Kreuzkleid! Ha-ha-ha! Nicht so schlecht, Bauer! Ich bin mir sicher, Luthers würde es li-i-i-eben, Vettes Kleid zu tragen, ha ha ha!";
			link.l1 = "Luthers?..";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4";
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4":
			dialog.text = "Dieser erbärmliche Vorwand für einen Ehemann, der es liebt, aus dem Kleiderschrank zu spähen, während seine liebe Frau ins Bett gebracht wird. Es macht ihr nichts aus!";
			link.l1 = "";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_4_1";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, sld);
			CharacterTurnByChr(pchar, sld);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), sld);
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_4", 2.5);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_4_1":
			Event("QuestDelayExit","sl", "", 0);
			dialog.text = "Richtig, Vette, meine Liebe? Heh-heh.";
			link.l1 = "(auf Mandarin) Was zur Hölle geht hier vor...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_5";
			sld = CharacterFromID("PZ_Rubbe");
			CharacterTurnByChr(npchar, CharacterFromID("PZ_Brigitta"));
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), npchar);
			locCameraFromToPos(-2.21, 1.90, 2.26, true, -0.81, -0.40, 4.36);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_5":
			dialog.text = "Hicks! Ich weiß nicht, was du gerade gesagt hast, aber nach dem Blick in deinen Augen und deinem Tonfall stimmst du mir zu! Van Haan ist ein verdammter Perverser. Also, was bist du überhaupt? Ein Arbeiter? Hat Vette dich eingeladen?";
			link.l1 = "Ich...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_6";
			CharacterTurnByChr(pchar, npchar);
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(CharacterFromID("PZ_Brigitta"), pchar);
			locCameraFromToPos(-4.45, 2.11, 1.53, true, 0.47, -0.30, 2.74);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_6":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Sepp");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_7":
			dialog.text = "Einen Arbeiter hierher einzuladen ist selbst für Vette zu viel. Er ist offensichtlich verloren und am falschen Ort. Hey, du. Verschwinde hier und vergiss alles, was du gesehen hast. Wer ist dein Meister? Wir werden ihn kontaktieren, und ihr werdet beide für euer Schweigen bezahlt. Vielleicht darfst du sogar zu deiner Familie auf dem Kontinent zurückkehren. Antworte mir und geh.";
			link.l1 = "Eigentlich bin ich geschäftlich hier.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_8";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_8":
			dialog.text = "Heh, Geschäft. Nur Mynheer van Diemen macht hier „Geschäft“. Meine Aufgabe ist es, ihn vor Leuten wie dir zu schützen. Und Luthers... ist eben Luthers. Oder... hat Vette dich wirklich hierher eingeladen?";
			link.l1 = " Nein, ich bin hier um...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_9";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_9":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Rubbe");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_10";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_10":
			dialog.text = "Hätte meine liebste Vette wirklich einen gelben Arsch hier eingeladen?! Verschwinde hier!!!";
			link.l1 = "Der elende Hahnrei...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_11";
			link.l2 = "Niemand spricht mit dir. Halt dein Mund. Tu nicht so, als hättest du einen Schwanz oder Würde.";
			link.l2.go = "PZ_Batavia_BitvaLubovnitsa_12";
			GiveItem2Character(npchar, "blade_06");
			EquipCharacterByItem(npchar, "blade_06");
			LAi_SetActorType(npchar);
			npchar.model.animation = "man";
			Characters_RefreshModel(npchar);
			SetCameraDialogMode(npchar);
			locCameraToPos(-1.88, 1.72, 0.27, false);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_11":
			dialog.text = "Hahnrei?! Nein, ich liebe sie mehr als mich selbst. Ha, ein dummkopf Chinesischer wie du würde das nicht verstehen!";
			link.l1 = "(auf Mandarin) Krankes Schwein.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_12":
			dialog.text = "Hahn?! Es ist alles in Ordnung! Ja! Ich weiß nur, dass andere Männer meiner lieben Vette mehr Freude bereiten, das ist alles!";
			link.l1 = "Wie wir in meiner Heimat sagen, ist ein Mann noch immer ein Mann, bis er nur noch einen Finger übrig hat. Wärst du ein Mann, würdest du das verstehen.";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_13";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_13":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_Brigitta");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_14";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_14":
			dialog.text = "Ich habe ihn natürlich nicht eingeladen, aber, wissen Sie, er ist ziemlich nett. Er könnte bleiben, nachdem Sie alle gegangen sind. Ich habe es schon mit unserem Hund versucht, aber ich habe es noch nie mit...";
			link.l1 = "Schweig, wenn Männer sprechen, Hure! Du bist hier das einzige Tier. Ich bin geschäftlich hier. Ich suche Oliveiro Fermentelos. Ihr müsst seine Freunde sein. Könnt ihr mir bitte sagen, wo er sein könnte, Mynheer Van Diemen?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_15";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_15":
			dialog.text = "Antoon, er hat mich beleidigt! Beleidigt! Du wirst das nicht durchgehen lassen, oder?!";
			link.l1 = "...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_16";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_16":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PZ_AntoniOneDimen");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Batavia_BitvaLubovnitsa_17";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_17":
			dialog.text = "Hehe, Entschuldigung, Kumpel, aber die Dame ist sauer. Ich werde dir eine Lektion in Manieren geben müssen. Lektion eins.";
			link.l1 = "Aber können Sie mir bei meiner Suche nach Oliveiro helfen?";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_18";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_18":
			dialog.text = "Es wird einem toten Arbeiter nicht helfen.";
			link.l1 = "(auf Mandarin) Verdammt seid ihr alle...";
			link.l1.go = "PZ_Batavia_BitvaLubovnitsa_19";
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_19":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			PlaySound("Voice\Russian\hambit\Longway-02.wav");
			
			sld = CharacterFromID("PZ_AntoniOneDimen");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Sepp");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("PZ_Rubbe");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Batavia_BitvaLubovnitsa_3");
			
			sld = CharacterFromID("PZ_Brigitta");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			PlaySound("People Fight\Peace_woman_death_05.wav");
			DoQuestCheckDelay("PZ_Batavia_BitvaLubovnitsa_5", 3.0);	//Нужно ещё раз, а то не бежит
		break;
		
		case "PZ_Batavia_BitvaLubovnitsa_21":
			dialog.text = "(auf Mandarin) Verdammt! Ich habe nichts gelernt!";
			link.l1 = "(auf Mandarin) Ich werde diesen Tag nie vergessen... Ich muss hier raus, bevor die Wächter kommen. Nicht, dass sie sich um die Geräusche aus diesem Irrenhaus kümmern würden...";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_14":
			dialog.text = "(auf Mandarin) Die Götter haben diesen Tag verflucht! Van Diemen ist verblutet, während ich mit seinem Lakaien beschäftigt war...!";
			link.l1 = "(auf Mandarin) Die Wachen kommen. Ich muss mich hier rauskämpfen.";
			link.l1.go = "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final";
		break;
		
		case "PZ_Batavia_BitvaResidensia_AntoniOneDimen_final":
			DialogExit();
			RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_resedinsia_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_30");
				TakeItemFromCharacter(pchar, "pistol2");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_lubovnitsa_Go"))
			{
				TakeItemFromCharacter(pchar, "blade_26");
				TakeItemFromCharacter(pchar, "pistol8");
			}
			if (CheckAttribute(pchar, "questTemp.PZ_Batavia_Plantation_Go"))
			{
				TakeItemFromCharacter(pchar, "mushket6");
				TakeItemFromCharacter(pchar, "mushket2x2");
			}
			EquipCharacterByItem(Pchar, "blade_11");
			pchar.model = "Longway";
			pchar.model.animation = "Longway";
			Characters_RefreshModel(pchar);
			
			
			SetCurrentTime(2, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Formosa,"+ NewStr() +"26 July 1645.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Formosa", "goto", "goto7", "PZ_Formosa2_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Formosa_smuggler_21":
			dialog.text = "Oh, das ist Chang Chang! Womit brauchst du dieses Mal Hilfe, mein kleiner Freund?";
			link.l1 = "Es ist Chang Tu... was meinst du?";
			link.l1.go = "PZ_Formosa_smuggler_22";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Formosa_smuggler_22":
			dialog.text = "Sie verachten mich, nicht wahr? Sie würden nicht hierher kommen, es sei denn, Sie brauchen etwas.";
			link.l1 = "Wissen Sie, wo van Merden ist? Ist er in der Stadt? Er ist nicht zu Hause. Ich muss mit ihm sprechen.";
			link.l1.go = "PZ_Formosa_smuggler_23";
		break;
		
		case "PZ_Formosa_smuggler_23":
			dialog.text = "Man kann nicht erwarten, dass ein Mann den ganzen Tag zu Hause bleibt und auf einen einzigen gelblichen Mann wartet. Er hat Geschäfte auf der Insel. Er wird heute Abend wieder in der Stadt sein, also mach dir keine Sorgen, Chang Chang!";
			link.l1 = "Danke. Auf Wiedersehen.";
			link.l1.go = "PZ_Formosa_smuggler_24";
		break;
		
		case "PZ_Formosa_smuggler_24":
			SetCurrentTime(1, 30);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DoQuestReloadToLocation("Formosa", "goto", "goto7", "PZ_Formosa2_IshemMerden_3");
		break;
		
		case "PZ_Formosa_bandit_1":
			dialog.text = "Hallo, Schlitzaugen! Was hast du zu dieser Stunde so eilig? Alle anständigen Leute schlafen jetzt.";
			link.l1 = "Dann was ist mit dir?";
			link.l1.go = "PZ_Formosa_bandit_2";
		break;
		
		case "PZ_Formosa_bandit_2":
			dialog.text = "Gut gesagt! Wir sind auf Patrouille! Es heißt, es schleicht ein kleiner gelber Kerl durch die Stadt und belästigt gottesfürchtige Menschen.";
			link.l1 = "Wer könnte das sein, bitte erzählen Sie?";
			link.l1.go = "PZ_Formosa_bandit_3";
		break;
		
		case "PZ_Formosa_bandit_3":
			dialog.text = "Genug geredet - es wird spät und ich fange an, müde zu werden.";
			link.l1 = "Bald wird dein Schlaf ewig sein.";
			link.l1.go = "PZ_Formosa_bandit_4";
		break;
		
		case "PZ_Formosa_bandit_4":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_JohanVanMerden");
			ChangeCharacterAddressGroup(sld, PChar.location, "patrol", "patrol7");
			GiveItem2Character(sld, "blade_31");
			EquipCharacterByItem(sld, "blade_31");
			LAi_SetActorType(sld);
			
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_FormosaBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "PZ_Formosa2_IshemMerden_7");
			
			DoQuestCheckDelay("PZ_Formosa2_IshemMerden_6", 10.0);
		break;
		
		case "PZ_Formosa_JohanVanMerden_21":
			dialog.text = "Chang Tu, geht es dir gut?";
			link.l1 = "Herr van Merden! Dank Ihrer Intervention geht es mir gut. Geht es Ihnen gut? Das ist die wichtigste Frage.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_22";
		break;
		
		case "PZ_Formosa_JohanVanMerden_22":
			dialog.text = "Immer an andere denken, nicht wahr? Wir teilen diese Eigenschaft. Ich konnte nicht einfach zusehen, als ich sah, wie sie dich angriffen, obwohl ich wusste, dass du mit ihnen fertig werden würdest. Um deine Frage zu beantworten, mir geht es gut, nur ein bisschen müde. Meine Beine sind etwas wackelig. Lass uns hineingehen, wenn es dir nichts ausmacht. Wir können dort sprechen.";
			link.l1 = "Natürlich, Mynheer van Merden, es ist schließlich Ihr Haus.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_23";
		break;
		
		case "PZ_Formosa_JohanVanMerden_23":
			DoQuestReloadToLocation("Formosa_houseSp1", "goto", "goto1", "PZ_Formosa2_IshemMerden_8");
		break;
		
		case "PZ_Formosa_JohanVanMerden_24":
			dialog.text = "Nun können wir ohne Eile reden, in Ruhe und Frieden. Sag mir, was bringt dich zu mir, Chang Tu?";
			link.l1 = "Sie haben recht, Mynheer van Merden. Ich bin gerade aus Batavia zurückgekehrt, und...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_25";
		break;
		
		case "PZ_Formosa_JohanVanMerden_25":
			dialog.text = "Warte. Ist es der arme Chang Xing...?";
			link.l1 = "Nein, überhaupt nicht! Ich hoffe es nicht. Der Himmel behält ihr Schicksal immer noch für sich. Und was Fermentelos betrifft... er ist nicht in Batavia. Van Diemen war keine Hilfe.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_26";
		break;
		
		case "PZ_Formosa_JohanVanMerden_26":
			dialog.text = "Er wäre es nicht, denn er und Oliveiro sind alte Freunde. Wie die Engländer sagen, Freunde und Komplizen im Verbrechen. Ich wäre überrascht, wenn er Ihnen etwas Nützliches geben würde.";
			link.l1 = "Ja, dank euch beiden und Trust habe ich mächtige Waffen erworben. Ich griff Van Diemen an, um ihn zu verhören und herauszufinden, wo Fermentelos war. Aber er starb, bevor ich etwas erfahren konnte...";
			link.l1.go = "PZ_Formosa_JohanVanMerden_28";
		break;
		
		case "PZ_Formosa_JohanVanMerden_28":
			dialog.text = "Beeindruckend. Sie haben erkannt, dass die Menschen nicht immer bereit sind, ihr Wissen zu teilen. Es gibt also andere... Methoden der Überzeugung, sagen wir mal. Ich dachte, Sie hätten vom Tod Ihrer Schwester erfahren und deshalb diesen Amoklauf gestartet. Aber was führt Sie jetzt zu mir? Ich habe Ihnen gesagt, dass ich nicht weiß, wohin Fermentelos geht, abgesehen von seinen gelegentlichen Besuchen in Batavia. Mit Van Diemens Tod ist diese letzte Spur verloren.";
			link.l1 = "Aber Sie kennen viele Dinge und viele Menschen. Ich dachte, Sie könnten vielleicht wieder helfen, vielleicht herumfragen über Fermentelos, wie früher. Sie waren der erste weiße Mann, der mich gut behandelt hat. Der erste... weiße Freund.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_29";
		break;
		
		case "PZ_Formosa_JohanVanMerden_29":
			dialog.text = "Das ist... rührend.";
			link.l1 = "Mynheer van Merden, warum lächeln Sie...?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_30";
		break;
		
		case "PZ_Formosa_JohanVanMerden_30":
			dialog.text = "Huh? Oh, entschuldige, Chang Tu. Ich werde alt, sentimental und melancholisch mit dem Alter. Es ist ein aufrichtiges Lächeln - ich konnte es nicht verbergen. Ich bin froh, dass du mich als Freund betrachtest. Da wir Freunde sind, erwarte ich auch, dass du mir ab und zu hilfst. Im Gegenzug werde ich dir definitiv bei den Fermentelos helfen. Mach dir keine Sorgen - du gehst nicht in eine Falle.";
			link.l1 = "Hmm, wie soll ich Ihnen helfen?";
			link.l1.go = "PZ_Formosa_JohanVanMerden_31";
		break;
		
		case "PZ_Formosa_JohanVanMerden_31":
			dialog.text = "Seit unserem letzten Treffen habe ich meine Kenntnisse Ihrer Sprache und Kultur, insbesondere der Medizin, vertieft. Ich möchte, dass Sie mir von Zeit zu Zeit bestimmte Reliquientafeln finden. Ich werde Sie dafür großzügig bezahlen, genau wie für jede andere Arbeit. Und ich hoffe, wir können gelegentlich unsere Gespräche auf Chinesisch üben. Es ist mir peinlich, meine Diener zu fragen, aber ein Freund...";
			link.l1 = "Chang Tu wird sein Bestes geben, Herr van Merden.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_32";
		break;
		
		case "PZ_Formosa_JohanVanMerden_32":
			dialog.text = "Gut. Du und ich haben einen langen Weg vor uns, mein Freund. Einen langen Weg. Ha! Ich denke, das wäre ein guter Deckname für dich. Eine nützliche Praxis meines Handwerks. Auf Niederländisch ist es „Lange Afstand“. Die Engländer sagen „Long Way“. Was bevorzugst du?";
			link.l1 = "Ich mag die englische Version besser. Lang. Weg. Langweg. Es klingt sehr passend in meiner Sprache. Danke fürs Zuhören, Herr van Merden. Langweg wird auf Ihren Befehl warten und bereit sein, Ihnen zu helfen und Ihre Anfragen zu erfüllen.";
			link.l1.go = "PZ_Formosa_JohanVanMerden_33";
		break;
		
		case "PZ_Formosa_JohanVanMerden_33":
			DialogExit();
			
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			DeleteAttribute(pchar, "questTemp.lockedMusic");
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			bQuestDisableMapEnter = true;
			pchar.GenQuest.CabinLock = true;
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_SegodnyaVremya_2", 5.0);
		break;
		
		// Этап 3, СЛЕД ЗВЕЗДЫ
		case "PZ_Longway_PosleRasskaza":
			dialog.text = "Was das Archiv betrifft, Herr Kapitän, haben Sie es bei sich? Es ist alles, was ich brauche - ich kenne das Chiffre auswendig.";
			if (CheckCharacterItem(pchar, "MerdokArchive"))
			{
				notification("All Skills +", "Longway");
				AddCharacterExpToSkill(npchar, "Leadership", 50);
				AddCharacterExpToSkill(npchar, "FencingLight", 50);
				AddCharacterExpToSkill(npchar, "Fencing", 50);
				AddCharacterExpToSkill(npchar, "FencingHeavy", 50);
				AddCharacterExpToSkill(npchar, "Pistol", 50);
				AddCharacterExpToSkill(npchar, "Fortune", 50);
				AddCharacterExpToSkill(npchar, "Sneak", 50);
				AddCharacterExpToSkill(npchar, "Sailing", 50);
				AddCharacterExpToSkill(npchar, "Accuracy", 50);
				AddCharacterExpToSkill(npchar, "Cannons", 50);
				AddCharacterExpToSkill(npchar, "Grappling", 50);
				AddCharacterExpToSkill(npchar, "Defence", 50);
				AddCharacterExpToSkill(npchar, "Repair", 50);
				AddCharacterExpToSkill(npchar, "Commerce", 50);	
				
				link.l1 = "Ja, ich habe es behalten, in der Hoffnung, dass es eines Tages nützlich sein könnte.";
				link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_1";
			}
			else
			{
				link.l1 = "Leider nein. War es deine letzte Hoffnung, Schwester zu finden?";
				link.l1.go = "PZ_Longway_PosleRasskaza_2";
			}
		break;
		
		case "PZ_Longway_PosleRasskaza_2":
			dialog.text = "Longway ist sehr erfreut, dass sich Herr Kapitän kümmert. Für jetzt gibt es noch Hoffnung. Ich habe eine neue Spur auf Guadeloupe gefunden.";
			link.l1 = "Also gut, dann erzähl mir, was dir dort passiert ist.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_1":
			dialog.text = "Das war eine weise Entscheidung. Vielleicht finden wir dort etwas, das uns bei unserer Suche nach Chang Xing helfen kann.";
			link.l1 = "Das wäre ideal. Lassen wir es gleich studieren.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_2";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_2":
			dialog.text = "Ja, lass uns es gemeinsam studieren. Das Jahr ist... 1637. Antoon van Diemen hat verkauft... verkauft...";
			link.l1 = "Sklaven, richtig?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_3";
			AddQuestRecordInfo("PZ_ArchiveOneMerden", "1");
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_3":
			dialog.text = "Frauen aus meinem Volk, verkauft an reiche weiße Männer.";
			link.l1 = "Das ist schrecklich.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_4":
			dialog.text = "Herr Kapitän, Sie scheinen nicht überrascht zu sein. Beunruhigt Sie das Schicksal dieser Frauen überhaupt nicht?";
			link.l1 = "Longway, of course it sincerely troubles me. I've seen this filth from the inside. But I've always been an advocate for women... and a bit of a ladies' man, to be honest. It's good you killed van Diemen; he deserved it. Is there anything else?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_5":
			dialog.text = "Van Diemen hat nur mit denen zusammengearbeitet, denen er vollkommen vertraute - Joep van der Vink, sein rechter Hand, und dieser verdammte Oliveiro Fermentelos. Und... und...";
			link.l1 = "Was ist los? Du bist blass geworden, Longway.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_6":
			dialog.text = "Johan van Merden...";
			link.l1 = "Es tut mir so leid. Das ist schrecklich, aber warum sind Sie so schockiert? Früher sagten Sie, Sie hätten alle Seiten herausgerissen, die Fermentelos erwähnen. Haben Sie dann keine Erwähnung von van Merden gefunden?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_7";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_7":
			dialog.text = "Longway war in Eile und muss dieses wichtige Stück übersehen haben.";
			link.l1 = "Ich verstehe. Wenn Sie bereit sind, lass uns weiter suchen und alles finden, was wir gerade jetzt benutzen können.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_8";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_8":
			dialog.text = "Es steht geschrieben, dass Fermentelos seine Leute schicken würde, um Frauen zu fangen, sie auszutauschen und Aufzeichnungen zu zerstören. Merden würde sie dann nach Batavia schicken, wo van der Vink und van Diemen unsere Frauen an weiße Männer verkauften. Hätte ich das doch nur früher erfahren...";
			link.l1 = "Also, am Ende haben sie alle zusammengearbeitet. Mach dir keine Vorwürfe, Longway. Du konntest es nicht wissen. Das Archiv ist erst kürzlich in deine Hände gekommen. Gibt es noch etwas?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_9";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_9":
			dialog.text = "Ja. Sie tun es seit fast zehn Jahren. So viele Frauen haben ihre Familien, ihre Ehre, ihre Hoffnung verloren... Aber dann hörte Fermentelos auf, mit van Merden zu arbeiten. Das ist der einzige Grund, warum er mir geholfen hat - alles, was er wollte, war, seinen ehemaligen Partner loszuwerden.";
			link.l1 = "Welche anderen Details ihrer schmutzigen Taten sind hier verzeichnet?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_10";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_10":
			dialog.text = "Mehr von van Merdens dunklen Gedanken. Er fand heraus, dass van Diemen ihn um Geld betrog. Also schickte er mich nach Batavia in der Hoffnung, ich würde dort sterben, aber auch in der Hoffnung, dass ich van Diemen mit mir nehmen würde.";
			link.l1 = "Kalt. Aber auch unglaublich klug.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_11";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_11":
			dialog.text = "Es hätte noch schlimmer kommen können. Es war van Merden, der diese Schläger zu seinem Haus schickte, um mich zu töten. Er griff erst ein, als er merkte, dass ich sie vielleicht alleine besiegen könnte.";
			link.l1 = "Er hatte es zweifellos alles durchdacht.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_12";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_12":
			dialog.text = "Nachdem ich lebend zurückkehrte, muss er gedacht haben, ich hätte seine wirklichen Absichten entdeckt und käme zur Rache. Als wir sprachen, hatte er seine Pistole unter dem Tisch gerichtet. Aber dann nannte ich ihn meinen ersten weißen Freund... er wäre fast vor Lachen geplatzt...";
			link.l1 = "Das ist schrecklich, Longway. Es ist bitter zu erkennen, dass diejenigen, die wir als Freunde betrachteten, die ganze Zeit hinter unserem Rücken über uns gelacht haben.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_13";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_13":
			dialog.text = "Longway hat vor langer Zeit etwas gelernt, kurz bevor er in diesem Archipel ankam. Ich wurde von den Portugiesen gefangen genommen und sie wollten mich hängen. Herr Rodenburg hat mein Leben gerettet.";
			link.l1 = "Ist das, wie Sie in seinen Dienst gekommen sind? War Lucas auch in Formosa?";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_14";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_14":
			dialog.text = "Ja, das ist richtig. Und nicht nur er - auch Van Berg. Van Merden hat mir erzählt, dass er es war, der Rodenburg geraten hat, mich zu verschonen. Aber einige Zeit später erfuhr Longway aus einer zwielichtigen Quelle, dass eigentlich Johan die Portugiesen auf mich angesetzt hat. Damals habe ich es nicht geglaubt... aber jetzt merke ich, dass es wahr sein könnte...";
			link.l1 = "Ekelhaft.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_15";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_15":
			dialog.text = "Dennoch haben sich an diesem Tag Zweifel in meinem Herzen eingenistet. Als ich erfuhr, dass Lord Kapitän und van Merden sich gegenüberstanden, erinnerte sich Longway an Ihre Freundlichkeit und schlug sich auf Ihre Seite.";
			link.l1 = "Das war die richtige Entscheidung, Longway. Heh, es stellt sich heraus, dass ich die ganze Zeit über dein erster echter weißer Freund war.";
			link.l1.go = "PZ_Longway_PosleRasskaza_Shifr_16";
		break;
		
		case "PZ_Longway_PosleRasskaza_Shifr_16":
			dialog.text = "Es stellt sich also so heraus, Herr Kapitän. Jetzt verstehe ich. Van Merden hat mir gesagt, ich sei sein Freund. Aber in Wirklichkeit war Longway für ihn nichts weiter als ein weiterer Arbeiter - nur nützlicher als die meisten\nDas ist alles. Die anderen Seiten betreffen die Buchhaltung sowie Geschäftsdetails zwischen Van Berg und Rodenburg.";
			link.l1 = "Ich verstehe. Und jetzt ist es höchste Zeit, dass Sie mir erzählen, was Sie auf Guadeloupe gemacht haben.";
			link.l1.go = "PZ_Longway_PosleRasskaza_3";
		break;
		
		case "PZ_Longway_PosleRasskaza_3":
			dialog.text = "Ich suchte nach dem Morgenstern. Auf einer der herausgerissenen Archivseiten stand, dass er zuletzt in der Nähe von St. Christopher gesehen wurde.";
			link.l1 = "Warum dort? Wir haben uns darauf geeinigt, auf Guadeloupe zu treffen, und ich habe Sie dort gefunden.";
			link.l1.go = "PZ_Longway_PosleRasskaza_4";
		break;
		
		case "PZ_Longway_PosleRasskaza_4":
			dialog.text = "Denn St. Christopher's ist die Heimat von Georges Gravel, einem der Informanten von van Merden. Georges glaubt, dass ich noch für Johan arbeite. Außerdem hat Gravel einmal eine schwere Straftat gegen van Merden begangen. Und Longway half, es zu vertuschen.";
			link.l1 = "Und was für ein Vergehen war das?";
			link.l1.go = "PZ_Longway_PosleRasskaza_5";
		break;
		
		case "PZ_Longway_PosleRasskaza_5":
			dialog.text = "Das ist nicht wichtig. Was wichtig ist, ist dass Georges Longway etwas schuldete. Also ging ich zur Kirche, in der Gravel als Hilfspriester arbeitet. Ist Mein Herr Kapitän bereit, weiter zuzuhören? Sie scheinen ein wenig abgelenkt zu sein.";
			link.l1 = "Entschuldigung, ich war abgelenkt. Ja, sicher, mach weiter, Longway.";
			link.l1.go = "PZ_Longway_PosleRasskaza_6";
		break;
		
		case "PZ_Longway_PosleRasskaza_6":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			SetMainCharacterIndex(GetCharacterIndex("Longway"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("Capsterville,"+ NewStr() +"St. Christopher Island.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "patrol", "patrol12", "PZ_Kapstervil_Start");
			LaunchFrameForm();
		break;
		
		case "PZ_Zhorzh_1":
			dialog.text = "Gut, du bist nicht zu spät. Ich möchte nicht länger hier sein als nötig, weißt du! Was brauchst du diesmal, Longway?";
			link.l1 = "Ändere deinen Ton, Gravel. Die Organisation benötigt deine Dienste.";
			link.l1.go = "PZ_Zhorzh_2";
		break;
		
		case "PZ_Zhorzh_2":
			dialog.text = "Ich muss gestehen, ich habe schon lange nichts mehr von ihnen gehört. Haben sie mich vergessen?";
			link.l1 = "Ich kann sie daran erinnern. Vielleicht, indem ich Lord van Merden erzähle, was du getan hast.";
			link.l1.go = "PZ_Zhorzh_3";
		break;
		
		case "PZ_Zhorzh_3":
			dialog.text = "Schon gut, schon gut, es besteht kein Grund so wütend zu werden! Was kann ich für dich tun?";
			link.l1 = "Ich brauche Informationen über den Morgenstern. Alles, was Sie finden können. Je mehr, desto besser.";
			link.l1.go = "PZ_Zhorzh_4";
		break;
		
		case "PZ_Zhorzh_4":
			dialog.text = "Sicher, aber es wird Zeit brauchen! Zwei Tage! Mindestens.";
			link.l1 = "Warum so lange?";
			link.l1.go = "PZ_Zhorzh_5";
		break;
		
		case "PZ_Zhorzh_5":
			dialog.text = "Normalerweise würde es Geld aus der Opferbox brauchen, um die Zungen meiner Informanten zu lockern. Aber wir wurden kürzlich ausgeraubt! Der Vater wird natürlich eine neue Sammlung von Spenden ankündigen, aber wir müssen immer noch unser Dach reparieren - es leckt! Es wird eine Menge Spenden brauchen, um es zu reparieren.";
			link.l1 = "Zwei Tage. Ich kann nicht ewig hier bleiben. Ich habe nicht so viel Zeit. Longway ist nicht für seine Geduld bekannt. Lord van Merden noch weniger. Soll ich dich daran erinnern, Gravel?";
			link.l1.go = "PZ_Zhorzh_6";
		break;
		
		case "PZ_Zhorzh_6":
			dialog.text = "Ich kann nicht kontrollieren, was außerhalb meiner Reichweite liegt! Ich werde tun, was ich kann. Obwohl, ich würde viel schneller herausfinden, wenn Sie diese Briganten fanden und unsere Spenden zurückbrachten!";
			link.l1 = "Ich werde darüber nachdenken. Du beginnst mit der Suche. Zwei Tage. Nicht mehr. Treffen zur gleichen Zeit und am gleichen Ort.";
			link.l1.go = "PZ_Zhorzh_7";
		break;
		
		case "PZ_Zhorzh_7":
			DialogExit(); 
			SetCurrentTime(12, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("A Day Later..."+ NewStr() +"In Search of the Church Robbers.", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil_Jungle", "goto", "goto1", "PZ_Kapstervil_Jungle");
			LaunchFrameForm();
		break;
		
		case "PZ_VorugaChurch_1":
			dialog.text = "Nun, schau dir das an! Ein schmaläugiger Mann auf unserer Insel! Fliehst du vor deinen Herren, hmm? Vor wem versteckst du dich, wenn ich fragen darf?";
			link.l1 = "Ich bin ein freier Mann.";
			link.l1.go = "PZ_VorugaChurch_2";
		break;
		
		case "PZ_VorugaChurch_2":
			dialog.text = "Ha! Sicher bist du das. Aber du siehst stark und schlau aus, auch wenn deine Augen ein bisschen schief sind. Möchtest du unserer Bande beitreten? Ich glaube sowieso nicht, dass du sonst wohin gehen kannst.";
			link.l1 = "Longway denkt, dass Sie mehr daran interessiert sind, ihn auszurauben, als ihn anzuwerben.";
			link.l1.go = "PZ_VorugaChurch_3";
		break;
		
		case "PZ_VorugaChurch_3":
			dialog.text = "Heh, betrachte dich selbst als glücklich. Wir haben vor kurzem eine Kirche in der Stadt ausgeraubt, kannst du das glauben? Warum? Weil Stehlen von Dieben nicht wirklich Stehlen ist.";
			link.l1 = "Ich hatte nicht vor, dich zu jagen, aber ich bin froh, dass ich dich gefunden habe.";
			link.l1.go = "PZ_VorugaChurch_4";
		break;
		
		case "PZ_VorugaChurch_4":
			dialog.text = "Uns jagen? Ah, also bist du ein Söldner, nicht irgendein entlaufener Arbeiter. Schlecht für dich dann.";
			link.l1 = "Genau.";
			link.l1.go = "PZ_VorugaChurch_5";
		break;
		
		case "PZ_VorugaChurch_5":
			DialogExit();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			LAi_SetCheckMinHP(npchar, 1, true, "PZ_VorugaChurch_win");
			for (i=11; i<=14; i++)
			{
				sld = CharacterFromID("PZ_KapstervilBandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_VorugaChurch_6":
			if (!CharacterIsAlive("PZ_KapstervilBandit_11") && !CharacterIsAlive("PZ_KapstervilBandit_12") && !CharacterIsAlive("PZ_KapstervilBandit_13"))
			{
				dialog.text = "Verdammt... Warum hast du mich nicht gleich getötet? Was willst du von mir? Wirst du mich ins Gefängnis schleppen?";
				link.l1 = "Ich habe kein Interesse daran. Sag mir einfach, wo du das Gold versteckt hast.";
				link.l1.go = "PZ_VorugaChurch_7";
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_VorugaChurch_win");	
			}
		break;
		
		case "PZ_VorugaChurch_7":
			dialog.text = "Heh... Du gelbhäutiger Bastard...";
			link.l1 = "Longways Geduld wird dünn. Ich werde es sowieso herausfinden. Die einzige Frage ist, wie lange du leiden wirst.";
			link.l1.go = "PZ_VorugaChurch_8";
			LAi_group_Delete("EnemyFight");
		break;
		
		case "PZ_VorugaChurch_8":
			dialog.text = "Gut, in Ordnung... Es ist in einer Höhle. Alles ist da. Das Geld gehört Ihnen. Töten Sie mich einfach... einfach nicht, ja, gell?";
			link.l1 = "Ich habe nicht gesagt, es würde überhaupt kein Leiden geben...";
			link.l1.go = "PZ_VorugaChurch_9";
		break;
		
		case "PZ_VorugaChurch_9":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_VorugaChurch_win_2", 0.9);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0":
			StartQuestMovie(true, false, true);
			locCameraFromToPos(2.48, 0.87, 9.26, true, 6.72, -0.85, 6.05);
			dialog.text = "(auf Mandarin) Hier ist das Versteck der Banditen.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_0_1";
			CharacterTurnToLoc(pchar, "box", "box1");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_0_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "PZ_Kapstervil_Grot_1", -1);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1":
			dialog.text = "(auf Mandarin) Das ist viel!";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_1_1";
			CharacterTurnToLoc(pchar, "box", "box1");
			locCameraFromToPos(6.83, 2.65, 6.62, true, 2.83, -1.00, 7.67);
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_1_1":
			dialog.text = "(auf Mandarin) Ich höre Schritte...";
			link.l1 = "(auf Mandarin) Hier ist noch jemand...";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_2";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_2":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_1", "sold_fra_7", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.17, 0.65, -1.42, 0.00);
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_Kapstervil_GrotSoldier_2", "sold_fra_5", "man", "man", 5, FRANCE, -1, true, "soldier"));
			LAi_SetActorType(sld);
			sld.CantLoot = true;
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			TeleportCharacterToPosAy(sld, 4.10, 0.65, 0.30, 3.00);
			
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_Kapstervil_Grot_2", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_3":
			dialog.text = "Was zum Teufel machen wir hier? Es ist niemand mehr übrig - wir haben sichergestellt, dass alle Räuber fort sind.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_4");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_5":
			dialog.text = "Das ist der Punkt, Idiot! Sie werden zurückkommen und wir werden ihnen einen herzlichen Empfang bereiten.";
			link.l1 = "";
			link.l1.go = "exit";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_1"));
			AddDialogExitQuest("PZ_Kapstervil_Grot_5");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_7":
			dialog.text = "Ich werde mich mal umsehen, sicherstellen, dass sich niemand versteckt. Mir ist sowieso langweilig...";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_8";
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_Kapstervil_GrotSoldier_2"));
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_8":
			DialogExit();
			LAi_Fade("PZ_Kapstervil_Grot_5_1", "");
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_9":
			dialog.text = "(auf Mandarin) Soldaten! Wie unglücklich... Was soll ich jetzt tun?";
			link.l1 = "(auf Mandarin) Ich brauche dieses Geld mehr als die weißen Soldaten! Ich gehe nicht ohne es!";
			link.l1.go = "PZ_Kapstervil_GrotSoldiers_10";
		break;
		
		case "PZ_Kapstervil_GrotSoldiers_10":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("PZ_Kapstervil_GrotSoldier_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyWithRadius");
				LAi_group_SetRelation("EnemyWithRadius", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_SetLookRadius("EnemyWithRadius", 6.0);
				LAi_group_SetHearRadius("EnemyWithRadius", 2.0);
				LAi_group_SetSayRadius("EnemyWithRadius", 12.0);
				LAi_group_SetCheck("EnemyWithRadius", "PZ_Kapstervil_Grot_6");
			}
		break;
		
		case "PZ_Zhorzh_11":
			dialog.text = "Ach, Monsieur Longway, Sie sind zurückgekehrt!";
			link.l1 = "Natürlich. Gab es irgendwelche Zweifel? Hast du etwas über den Morgenstern herausgefunden, Georges?";
			link.l1.go = "PZ_Zhorzh_12";
		break;
		
		case "PZ_Zhorzh_12":
			dialog.text = "Ja, mein Herr. Es ist eine schwere Galeone, angeführt von einem Spanier, oder so sagt man...";
			link.l1 = "Er ist Portugiese. Ihr Weißen könnt euch nicht einmal voneinander unterscheiden.";
			link.l1.go = "PZ_Zhorzh_13";
		break;
		
		case "PZ_Zhorzh_13":
			dialog.text = "Ach ja, mein Fehler. Wie auch immer, ich habe herausgefunden, dass er die Galeone stark modifiziert hat, als Maßnahme, um sie als Handelsschiff zu tarnen, mit klein-kalibrigen Kanonen und einer kleineren Besatzung. Aber er hat den Laderaum erweitert, bis zum Rand gefüllt - es ist so schwer, dass es kaum segeln kann.";
			link.l1 = "Also hat er beschlossen, ein neues Leben zu beginnen. Gut. Wo kann ich ihn finden?";
			link.l1.go = "PZ_Zhorzh_14";
		break;
		
		case "PZ_Zhorzh_14":
			dialog.text = "Das ist kniffliger. Er bewegt sich ständig zwischen unseren Kolonien und den englischen hin und her, aber nur unter den Inseln über dem Winde. Allerdings habe ich erfahren, dass er gerade auf dem Weg nach Basse-Terre ist, mit einer großen Ladung Wein.";
			link.l1 = "Ich muss herausfinden, wie ich schnell dorthin komme.";
			link.l1.go = "PZ_Zhorzh_15";
		break;
		
		case "PZ_Zhorzh_15":
			dialog.text = "Das ist Ihr Anliegen, Monsieur Longway. Ich habe genug eigene Probleme... wie zum Beispiel dieses verdammte Dach zu reparieren.";
			link.l1 = "Was Sorgen angeht, ich habe diese Kirchenräuber gefunden. Hier ist Ihre Spende zurück. Reparieren Sie das Dach - es ist nicht gut für Ihren Gott, ohne eins zu sein.";
			link.l1.go = "PZ_Zhorzh_16";
		break;
		
		case "PZ_Zhorzh_16":
			dialog.text = "Vielen Dank, Monsieur Longway! Ich hätte nie gedacht, dass ausgerechnet Sie das tun würden.";
			link.l1 = "Ich dachte auch nicht so. Aber ich musste etwas mit diesen zwei Tagen anfangen.";
			link.l1.go = "PZ_Zhorzh_17";
		break;
		
		case "PZ_Zhorzh_17":
			dialog.text = "Also, Sie müssen nach Guadeloupe kommen? Ich werde Ihnen ein Schiff finden, das dorthin fährt. Rechnen Sie damit, bald von mir zu hören!";
			link.l1 = "Das wäre hilfreich. Danke, Georges.";
			link.l1.go = "PZ_Zhorzh_18";
		break;
		
		case "PZ_Zhorzh_18":
			DialogExit();
			SetCurrentTime(9, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = false;
			
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("The Next Morning..."+ NewStr() +"Capsterville", "Reload_To_Location", 0, 4.0);
			SetLaunchFrameReloadLocationParam("Kapstervil", "goto", "goto19", "PZ_Kapstervil_PoiskZvezda");
			LaunchFrameForm();
		break;
		
		case "PZ_Kapstervil_Kurier_1":
			dialog.text = "Sie müssen ein Bekannter von Georges sein? Er bat mich, Ihnen dies zu geben.";
			link.l1 = "Eine Notiz? Mein Dank. Wie wussten Sie, dass sie für mich war?";
			link.l1.go = "PZ_Kapstervil_Kurier_2";
		break;
		
		case "PZ_Kapstervil_Kurier_2":
			dialog.text = "Ernsthaft?";
			link.l1 = "Ach, richtig.";
			link.l1.go = "PZ_Kapstervil_Kurier_3";
		break;
		
		case "PZ_Kapstervil_Kurier_3":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("PZ_Kapstervil_ChitaemPismo", 1.5);
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog":
			dialog.text = "(Liest den Brief) Herr Longway, die Pinasse 'Provence' legt morgen früh nach Basse-Terre ab. Der Kapitän, Mathieu Terugny, ist in der Taverne zu finden. Grüßen Sie Herrn van Merden von mir. - Georges Gravel.";
			link.l1 = "";
			link.l1.go = "PZ_Kapstervil_ChitaemPismo_Dialog_2";
		break;
		
		case "PZ_Kapstervil_ChitaemPismo_Dialog_2":
			DialogExit();
			LAi_RemoveCheckMinHP(pchar);
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			sld = characterFromId("PZ_Kapstervil_tavernkeeper");
			sld.dialog.currentnode = "PZ_TerunyiTavern1";
			LAi_SetBarmanType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_TerunyiTavern1":
			dialog.text = "Wir servieren hier keine Getränke für Euresgleichen. Und es sei denn, ich will Beschwerden über Flöhe hören, werde ich Euch auch kein Zimmer vermieten.";
			link.l1 = "Ich brauche weder einen Drink noch ein Zimmer. Und... Longway hat keine Flöhe.";
			link.l1.go = "PZ_TerunyiTavern2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_TerunyiTavern2":
			dialog.text = "Wie zum Teufel soll ich das wissen? Nun gut, spuck es aus. Was willst du? Dann verschwinde.";
			link.l1 = "Ich werde. Ich suche nach Kapitän Mathieu Terugny. Ich kann ihn nicht finden. Wissen Sie, wo er ist?";
			link.l1.go = "PZ_TerunyiTavern3";
		break;
		
		case "PZ_TerunyiTavern3":
			dialog.text = "Er ist beschäftigt, sein Schiff in der örtlichen Werkstatt segelbereit zu machen. Das ist viel wichtiger als sich mit einem Chinesen wie dir zu unterhalten, aber das verstehst du offensichtlich nicht.";
			link.l1 = "Eigentlich war ich mal... Ach, vergiss es. Ist gerade nicht wichtig.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_CreateTerunyi");
		break;
		
		case "PZ_Terunyi1":
			dialog.text = "Was wollen Sie, Chinese? Siehst du nicht, dass ich beschäftigt bin? Ich muss mein Schiff bereitmachen.";
			link.l1 = "Hauptmann Mathieu Terugny?";
			link.l1.go = "PZ_Terunyi2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Terunyi2":
			dialog.text = "Nun, das hat gerade aufgehört, lustig zu sein. Wie kennt jemand wie du mich? Hat jemand dich geschickt?";
			link.l1 = "Keine Sorge. Ich habe gehört, Sie segeln nach Basse-Terre. Können Sie mich als Passagier mitnehmen? Ich werde bezahlen.";
			link.l1.go = "PZ_Terunyi3";
		break;
		
		case "PZ_Terunyi3":
			dialog.text = "Das wird immer besser. Ich fahre nach St. Pierre, nicht nach Basse-Terre, aber es ist nur ein kleiner Umweg. Das ist gut, weil ich dich nicht länger als nötig auf dem Schiff behalten muss. Fünftausend Pesos. Wir fahren in drei Stunden ab. Zahlung am Pier. Auch wenn ich ein Kaufmann bin, gibt es kein Feilschen. Verstanden?";
			link.l1 = "Ja. Danke. Wir sehen uns am Pier, Kapitän Terugny.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToPier");
		break;
		
		case "PZ_Terunyi4":
			dialog.text = "Du bist doch erschienen, Schlitzaugen. Ich dachte, du würdest es nicht schaffen - niemand gibt deiner Art freiwillig echtes Geld.";
			link.l1 = "Fünftausend Pesos, genau wie Sie gefragt haben. Sind Sie bereit, in See zu stechen?";
			link.l1.go = "PZ_Terunyi5";
		break;
		
		case "PZ_Terunyi5":
			AddMoneyToCharacter(pchar, -5000);
			
			dialog.text = "Nein, nein! Ich sollte derjenige sein, der Sie das fragt. Aber ich nehme an, Sie sind bereit. Los geht's. Sie werden das Beiboot rudern. Und erwarten Sie keine richtige Kabine! Sie sind der einzige Grund, warum wir diesen Umweg machen.";
			link.l1 = "Ich brauche keinen Trost. Bring mich einfach dorthin.";
			link.l1.go = "PZ_Terunyi6";
		break;
		
		case "PZ_Terunyi6":
			DialogExit();
			
			SetCurrentTime(2, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			InterfaceStates.Buttons.Save.enable = true;
			
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			
			QuestToSeaLogin_Launch();
			QuestToSeaLogin_PrepareLoc("Guadeloupe", "Quest_Ships", "Quest_ship_8", false);
			DoQuestCheckDelay("PZ_Flashback_Final_1", 3.5);
		break;
		
		case "PZ_Longway_PosleRasskaza21":
			dialog.text = "...also konnte Longway nicht genau herausfinden, wohin der Morgenstern steuert.";
			link.l1 = "Ja, ich kann sehen, wie du in all dieses Durcheinander geraten bist.";
			link.l1.go = "PZ_Longway_PosleRasskaza22";
		break;
		
		case "PZ_Longway_PosleRasskaza22":
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena")) sStr = "Helena";
			else sStr = "Alonso";
			dialog.text = "Ich habe eine Brigg in den Gewässern von Guadeloupe gesehen. Vielleicht war es die Banten. Ich werde versuchen, es herauszufinden. Nun, du kannst jetzt gehen, Longway. Bring mir "+sStr+".";
			link.l1.go = "PZ_Longway_PosleRasskaza23";
		break;
		
		case "PZ_Longway_PosleRasskaza23":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeLong("PZ_LongwayUhoditIzKauty", "PZ_HelenaOrAlonso");
		break;
		
		case "PZ_Helena_1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Mein Kapitän, ist alles gut? Ich kam, sobald Longway sagte, dass Sie mich brauchen.";
				link.l1 = "Ich versuche nur, die Dinge zusammenzusetzen. Erinnerst du dich an den Namen dieser Brigantine, die wir vor der Insel gesehen haben?";
				link.l1.go = "PZ_Helena_3";
			}
			else
			{
				dialog.text = "Sie wollten mich sehen?";
				link.l1 = "Ja. Erinnerst du dich an die Brigg, die wir kürzlich gesehen haben? Finde heraus, wo sie sich befindet und wie sie heißt.";
				link.l1.go = "PZ_Helena_2";
			}
		break;
		
		case "PZ_Helena_2":
			dialog.text = "Ich erinnere mich, aber warum das plötzliche Interesse an einer Brigantine? Herauszufinden könnte einige Zeit in Anspruch nehmen.";
			link.l1 = "Helen, mach es einfach, bitte. Und ja, ich weiß, es könnte eine Weile dauern. Ich werde warten.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Helena_3":
			dialog.text = "Nein, ich habe nicht nachgesehen. Warum? Ist es wichtig?";
			link.l1 = "Mm-hmm. Können Sie mehr herausfinden? Ich muss wissen, wo sie jetzt vor Anker liegen, wenn sie die Gewässer von Guadeloupe nicht schon verlassen haben.";
			link.l1.go = "PZ_Helena_4";
		break;
		
		case "PZ_Helena_4":
			dialog.text = "Natürlich. Nur zur Info, es könnte eine Weile dauern. Ich nehme ein Beiboot und ein paar Leute zur Hilfe, Ja, Charles?";
			link.l1 = "Natürlich, Helen, danke. Ich werde warten.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_Alonso_11":
			dialog.text = "Herr Kapitän, Sie haben gerufen?";
			link.l1 = "Ja, Alonso. Wir haben eine Brigg in den Gewässern vor der Insel passiert, als wir für Longway zurückkehrten. Hast du zufällig ihren Namen mitbekommen?";
			link.l1.go = "PZ_Alonso_12";
		break;
		
		case "PZ_Alonso_12":
			dialog.text = "Nein, meine Aufgabe ist es, ein Auge auf die neuen Rekruten zu haben und Teil der Enterteam-Avantgarde zu sein. Außerdem besitze ich kein Fernglas, und wir waren nicht so nah dran.";
			link.l1 = "Wahr. Aber ich muss es trotzdem herausfinden. Machen Sie es fertig.";
			link.l1.go = "PZ_Alonso_13";
		break;
		
		case "PZ_Alonso_13":
			dialog.text = "Ja, Kapitän. Ich denke, ich kann es in einem halben Tag schaffen.";
			link.l1 = "Beeil dich. Ich werde warten.";
			link.l1.go = "PZ_PoiskBanten";
		break;
		
		case "PZ_PoiskBanten":
			DialogExit();
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			LAi_SetStayType(pchar);
			SetLaunchFrameFormParam("Five hours later...", "PZ_PoiskBanten_2", 0, 4.0);
			LaunchFrameForm();
			locCameraSleep(true);
		break;
		
		case "PZ_Helena_5":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				dialog.text = "Ich habe alles gelernt. War alles in Ordnung während meiner Abwesenheit, mein Kapitän?";
				link.l1 = "Ja, mir geht es gut, danke, Helen. Erzähl mir.";
				link.l1.go = "PZ_Helena_7";
			}
			else
			{
				dialog.text = "Puh, ich bin zurück. Ich habe Ihre Brigg gefunden.";
				link.l1 = "Willkommen zurück. Wie lautet ihr Standort und Name?";
				link.l1.go = "PZ_Helena_6";
			}
		break;
		
		case "PZ_Helena_6":
			dialog.text = "Die Banten. Dieser Name bedeutet Ihnen etwas, nicht wahr? Sie ist jetzt am Leuchtturm, und einige ihrer Besatzungsmitglieder sind an Land gekommen. Werden wir dieses Schiff angreifen?";
			link.l1 = "Nein, wir müssen genau herausfinden, wer an Land gegangen ist. Wir werden über Land zum Leuchtturm gehen. Angesichts unserer bereits erfolgten Verzögerung ist es höchste Zeit, dass wir den Hafen verlassen. Wir sollten irgendwo abgelegen ankern. Capster Strand wäre gut. Lass uns uns beeilen, Helen.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Helena_7":
			dialog.text = "Nun, die Brigg heißt Banten und sie liegt am Leuchtturm vor Anker. Einige der Crew sind dort gelandet. Was wirst du tun?";
			link.l1 = "Um das herauszufinden, müssen wir unbemerkt zum Leuchtturm gelangen, und das können wir nur zu Fuß. Unser Schiff muss irgendwo sicher ankern. Wie wäre es mit dem Capster Strand?";
			link.l1.go = "PZ_Helena_8";
		break;
		
		case "PZ_Helena_8":
			dialog.text = "Gute Idee. Charles, möchtest du, dass ich mit dir zum Leuchtturm gehe?";
			link.l1 = "Ich werde darüber nachdenken, während wir das Schiff bewegen - Sie sind schon müde genug.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_Alonso_15":
			dialog.text = "Ich bin zurückgekommen, sobald ich fertig war, Senor Kapitän.";
			link.l1 = "Sehr gut. Bericht, Alonso.";
			link.l1.go = "PZ_Alonso_16";
		break;
		
		case "PZ_Alonso_16":
			dialog.text = "Die Brigg liegt immer noch vor der Insel - um genau zu sein, beim Leuchtturm. Der Name am Heck ist Banten. Ein paar ihrer Besatzung sind an Land gegangen.";
			link.l1 = "Gute Arbeit, Alonso. Mach die Crew sofort bereit, den Anker zu lichten.";
			link.l1.go = "PZ_Alonso_17";
		break;
		
		case "PZ_Alonso_17":
			dialog.text = "Bereiten Sie sich auch auf das Entern vor?";
			link.l1 = "Noch nicht. Wenn ihr Kapitän auf den Leuchtturm zusteuert, könnte er sich in der Stadt verstecken, wenn wir auf See angreifen. Wir werden zum Capster Strand gehen, um unser Schiff zu sichern, dann nähern wir uns zu Fuß dem Leuchtturm.";
			link.l1.go = "PZ_BasTerMayak";
		break;
		
		case "PZ_BasTerMayak":
			DialogExit();
			locCameraSleep(false);
			LAi_SetPlayerType(pchar);
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Guadeloupe", true);
			
			AddQuestRecord("PZ", "15");
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1 = "location";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition.l1.location = "Shore29";
			PChar.quest.PZ_Banten_PlyazhKapster.win_condition = "PZ_Banten_PlyazhKapster";
			
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1 = "Timer";
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.hour = sti(GetTime() + 7);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.PZ_Banten_PlyazhKapster_Proval.win_condition = "PZ_Banten_PlyazhKapster_Proval";
			
			if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
			{
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, pchar, "", -1);
				LAi_SetOfficerType(npchar);
				npchar.Dialog.Filename = "Quest\Saga\Helena.c";
				npchar.Dialog.CurrentNode = "Helena_officer";
			}
		break;
		
		case "PZ_Longway_21":
			dialog.text = "Herr Kapitän, schau! Da ist jemand im Leuchtturm.";
			link.l1 = "Gut, wir sind rechtzeitig! Lassen Sie uns beeilen und sie holen. Alonso wird heute viel Arbeit haben.";
			link.l1.go = "PZ_Longway_22";
		break;
		
		case "PZ_Longway_22":
			dialog.text = "Aber was ist, wenn sie dabei sterben?";
			link.l1 = "Was schlagen Sie vor?";
			link.l1.go = "PZ_Longway_23";
		break;
		
		case "PZ_Longway_23":
			dialog.text = "Wir schleichen uns leise ein und belauschen zuerst ihr Gespräch.";
			link.l1 = "Иch bezweifle, dass wir das tun können, ohne vom Fenster aus gesehen zu werden. Aber lass es uns versuchen.";
			link.l1.go = "PZ_Longway_24";
		break;
		
		case "PZ_Longway_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_SetOfficerType(npchar);
			npchar.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			npchar.Dialog.CurrentNode = "Longway_officer";
			LAi_SetCheckMinHP(npchar, 1, true, "SkritoeBessmertie");
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1 = "locator";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.location = "Mayak4";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator_group = "goto";
			PChar.quest.PZ_MayakPodslushivanie.win_condition.l1.locator = "goto31";
			PChar.quest.PZ_MayakPodslushivanie.win_condition = "PZ_MayakPodslushivanie";
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1":
			dialog.text = "Denken Sie über das nach, was ich gesagt habe. Denken Sie hart nach. Geld ist kein Problem - natürlich innerhalb bestimmter Grenzen. Aber selbst diese Grenze wird Ihnen wie ein Berg aus Gold erscheinen - der Chinese muss sterben! Ich habe schon Männer hinter ihm hergeschickt, aber vergebens. Dieses Mal jedoch, wenn sie sich mit Ihren Männern zusammentun...";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_1_1";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_BasTerJailOff_Clone"));
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_1_1":
			StartInstantDialog("PZ_BasTerJailOff_Clone", "PZ_MayakPodslushivanie_Dialog_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_2":
			dialog.text = "Schau, wir werden beobachtet! Es ist er! Er und sein verdammter Kapitän!";
			link.l1 = "";
			link.l1.go = "PZ_MayakPodslushivanie_Dialog_3";
			CharacterTurnToLoc(npchar, "item", "flower5");
		break;
		
		case "PZ_MayakPodslushivanie_Dialog_3":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			locCameraToPos(1.52, 18.87, -9.55, true);
			DoQuestCheckDelay("CameraReset", 1.0);
			DeleteAttribute(pchar, "questTemp.NoFast");
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("PZ_Neznakomets");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			sld = CharacterFromID("PZ_BasTerJailOff_Clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_MayakPodslushivanie_win");
			
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_Neznakomets_Bandit_"+i, "citiz_" + (rand(9) + 41), "man", "man", sti(pchar.rank), PIRATE, -1, true, "pirate"));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;
		
		case "PZ_Mayak_KomendantSidit_1":
			if (!CharacterIsAlive("PZ_Neznakomets_Bandit_1") && !CharacterIsAlive("PZ_Neznakomets_Bandit_2") && !CharacterIsAlive("PZ_Neznakomets_Bandit_3")&& !CharacterIsAlive("PZ_Neznakomets_Bandit_4"))
			{
				dialog.text = "Verdammt seist du, dreckiger Asiate... Ich musste so viel wegen dir ertragen. Und jetzt, nach all dem, stehe ich kurz vor dem Tod...";
				link.l1 = "Wir bringen Sie zu unserem Arzt, Herr Kommandant. Sagen Sie uns nur, mit wem Sie gesprochen haben - das ist sehr wichtig.";
				link.l1.go = "PZ_Mayak_KomendantSidit_2";
				LAi_group_Delete("EnemyFight");
			}
			else
			{
				dialog.text = RandSwear()+"";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_MayakPodslushivanie_win");	
			}
		break;
		
		case "PZ_Mayak_KomendantSidit_2":
			dialog.text = "Sein Name... ist Joep van der Vink, er... kha...";
			link.l1 = "...";
			link.l1.go = "PZ_Mayak_KomendantSidit_3";
		break;
		
		case "PZ_Mayak_KomendantSidit_3":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			DoQuestCheckDelay("PZ_Mayak_Longway", 1.5);
		break;
		
		case "PZ_Longway_25":
			dialog.text = "";
			link.l1 = "Er ist tot... Nun, zumindest kennen wir den Namen. Longway...?";
			link.l1.go = "PZ_Longway_26";
		break;
		
		case "PZ_Longway_26":
			dialog.text = "Das kann absolut nicht sein...";
			link.l1 = "Sie sehen ein wenig blass aus, Longway.";
			link.l1.go = "PZ_Longway_27";
		break;
		
		case "PZ_Longway_27":
			dialog.text = "Longway war sich ziemlich sicher, dass er van der Vink vor zehn Jahren getötet hat\nSie entkommen! Ihr Schiff ist schnell!";
			link.l1 = "Ja, eine wunderbare Brigg... leider für uns. Selbst wenn wir rechtzeitig unser Schiff erreichen, werden sie weg sein, bis wir die Segel hissen und den Wind fangen.";
			link.l1.go = "PZ_Longway_28";
		break;
		
		case "PZ_Longway_28":
			dialog.text = "Das könnte das Ende sein...";
			link.l1 = "Nein, Longway. Hör mir zu. Wenn sie vorhaben, im Archipel zu bleiben, werden wir früher oder später auf sie stoßen - es ist eine kleine Welt, und die Karibik besonders. Sobald wir ihre Spur wieder aufnehmen, werde ich alles fallen lassen und ihnen nachgehen. Das verspreche ich dir. Hörst du mich?";
			link.l1.go = "PZ_Longway_29";
		break;
		
		case "PZ_Longway_29":
			dialog.text = "Ja, Herr Kapitän. Danke.";
			link.l1 = "Halte den Kopf hoch, Longway. Wir müssen uns beeilen, zurück zum Schiff zu kommen - der Tod des Kommandanten wird sehr bald eine große Nachricht sein.";
			link.l1.go = "PZ_Longway_30";
		break;
		
		case "PZ_Longway_30":
			DialogExit();
			
			Return_LongwayOfficer();
			LAi_RemoveCheckMinHP(npchar);
			AddQuestRecord("PZ", "17");
			sld = &Locations[FindLocation("Mayak4")];
			sld.locators_radius.goto.goto31 = 0.5;
			
			chrDisableReloadToLocation = false;
			QuestOpenSeaExit();
			
			pchar.questTemp.PZ_Etap4_Start = true;
		break;
		
		// Этап 4, Обманчивая Звезда
		case "PZ_PoterpKrushenie_1":
			dialog.text = "Herr! Einen Moment! Sind Sie ein Kapitän?";
			link.l1 = "Vielleicht. Wie hast du das erraten? Und was willst du?";
			link.l1.go = "PZ_PoterpKrushenie_2";
		break;
		
		case "PZ_PoterpKrushenie_2":
			dialog.text = "Nun, es gibt hier nichts als Berge und dichten Dschungel - keine Straßen zur Stadt. Und doch bist du hier. Du bist nicht nur zum Sightseeing hier, oder?";
			link.l1 = "Gute Beobachtung. Aber Sie haben mir immer noch nicht gesagt, was Sie wollen.";
			link.l1.go = "PZ_PoterpKrushenie_3";
		break;
		
		case "PZ_PoterpKrushenie_3":
			dialog.text = "Ach, richtig! Kapitän, unser Schiff hat die Felsen direkt vor dieser Bucht getroffen. Wir sind die Einzigen, die es geschafft haben...";
			link.l1 = "Es tut mir leid. Sie möchten, dass ich Sie irgendwohin bringe, nicht wahr?";
			link.l1.go = "PZ_PoterpKrushenie_4";
		break;
		
		case "PZ_PoterpKrushenie_4":
			dialog.text = "Aye... Wir werden keine Schwierigkeiten bereiten, das schwöre ich. Setzt uns einfach in Belize ab, und wir werden uns von dort aus durchschlagen.";
			link.l1 = "Es ist nicht weit, oder? In diesem Fall, willkommen an Bord.";
			link.l1.go = "PZ_PoterpKrushenie_5";
			link.l2 = "Es tut mir leid, aber ich gehe in die andere Richtung.";
			link.l2.go = "PZ_PoterpKrushenie_7";
		break;
		
		case "PZ_PoterpKrushenie_5":
			dialog.text = "Danke, Kapitän! Wer weiß, wie lange wir ohne Sie festgesessen hätten.";
			link.l1 = "Tatsächlich. Verschwenden wir keine Zeit!";
			link.l1.go = "PZ_PoterpKrushenie_6";
		break;
		
		case "PZ_PoterpKrushenie_6":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_PoterpKrushenie";
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_7":
			dialog.text = "Aber Belize ist so nah! Es würde sicherlich nicht lange dauern, oder?";
			link.l1 = "Ich habe es eilig. Kann mir keine Umwege leisten.";
			link.l1.go = "PZ_PoterpKrushenie_8";
		break;
		
		case "PZ_PoterpKrushenie_8":
			dialog.text = "Nicht einmal eine kurze? Nur bis Belize? Bitte, Kapitän, lassen Sie uns nicht gestrandet!";
			link.l1 = "Gut, ich hoffe, ich werde es nicht bereuen. Alle an Bord!";
			link.l1.go = "PZ_PoterpKrushenie_6";
			link.l2 = "Das ist das Leben. Habt einen angenehmen Tag, meine Freunde.";
			link.l2.go = "PZ_PoterpKrushenie_9";
		break;
		
		case "PZ_PoterpKrushenie_9":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			DeleteAttribute(&locations[FindLocation("Shore9")], "DisableEncounters");
			
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "", "", "", "", 10);
				sld.location = "None";
			}
			
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1 = "location";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition.l1.location = "Beliz_town";
			PChar.quest.PZ_Beliz_PoterpKrushenie.win_condition = "PZ_Beliz_QuestCitizenDialog";
			
			AddMapQuestMarkCity("Beliz", false);
			
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "FencingL", 20);
			AddCharacterExpToSkill(pchar, "FencingS", 20);
			AddCharacterExpToSkill(pchar, "FencingH", 20);
			AddCharacterExpToSkill(pchar, "Pistol", 20);
			
			pchar.questTemp.PZ.Shipwreckers.Decline = true;
			
			SetTimerCondition("PZ_BelizFail", 0, 0, 30, false);
		break;
		
		case "PZ_PoterpKrushenie_11":
			dialog.text = "Nochmals vielen Dank, Kapitän! Wir sind nur einfache Seemänner, also haben wir nicht viel, um Ihnen anzubieten.";
			link.l1 = "Nun, zumindest mussten wir nicht allzu weit aus dem Weg gehen.";
			link.l1.go = "PZ_PoterpKrushenie_12";
		break;
		
		case "PZ_PoterpKrushenie_12":
			dialog.text = "Wir werden auf Ihre Gesundheit anstoßen und für Sie eine Kerze in der Kirche anzünden.";
			link.l1 = "Das ist besser als nichts. Prost, Jungs!";
			link.l1.go = "PZ_PoterpKrushenie_13";
		break;
		
		case "PZ_PoterpKrushenie_13":
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = CharacterFromID("PZ_PoterpKrushenie_"+i);
				LAi_SetCitizenType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0;
				sld.location = "None";
			}
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_BelizZhitelNovosti", "citiz_4", "man", "man", 1, ENGLAND, 0, false, "quest"));
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto5");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_BelizZhitelNovosti_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_BelizZhitelNovosti_1":
			dialog.text = "Hast du gehört? Sie haben ihn endlich gefangen! Unsere Gewässer sind endlich sicher!";
			link.l1 = "Das ist... gute Nachrichten? Aber wen haben sie gefangen genommen?";
			link.l1.go = "PZ_BelizZhitelNovosti_2";
			DeleteQuestCondition("PZ_BelizFail");
		break;
		
		case "PZ_BelizZhitelNovosti_2":
			dialog.text = "Matthew Lutter, der Windbeutel selbst!";
			link.l1 = "Ich bin nicht vertraut - was hat er getan?";
			link.l1.go = "PZ_BelizZhitelNovosti_3";
		break;
		
		case "PZ_BelizZhitelNovosti_3":
			dialog.text = "Du weißt es nicht?! Nun, du bist offensichtlich kein Engländer, das kann ich sagen. Er ist ein Pirat, der uns und die Spanier seit Jahren auf seinem Schiff, der Möwe, ausplündert.";
			link.l1 = "Beide, die Engländer und die Spanier zu plündern? Das ist ungewöhnlich.";
			link.l1.go = "PZ_BelizZhitelNovosti_4";
		break;
		
		case "PZ_BelizZhitelNovosti_4":
			dialog.text = "Gewiss. Die Küstenwache konnte ihn nie fangen, aber am Ende biss er mehr ab, als er kauen konnte - verlor gegen ein seltsames Handelsschiff, wenn Sie es glauben können.";
			link.l1 = "Das ist amüsant. Was war so seltsam an dem Händler?";
			link.l1.go = "PZ_BelizZhitelNovosti_5";
		break;
		
		case "PZ_BelizZhitelNovosti_5":
			dialog.text = "Nun, es war nur eine riesige, ungeschickte Galeone ohne Eskorte! Aber dank ihres wahnsinnigen Kapitäns wird Lutter heute sein letztes Lied singen - er wird gehängt. Du solltest kommen und zusehen!";
			link.l1 = "Ich könnte, aber momentan habe ich andere Angelegenheiten zu erledigen.";
			link.l1.go = "PZ_BelizZhitelNovosti_6";
		break;
		
		case "PZ_BelizZhitelNovosti_6":
			DialogExit();
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			
			sld = CharacterFromID("Longway");
			if (!CharacterIsHere("Longway"))
			{
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
			}
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_31";
		break;
		
		case "PZ_Longway_31":
			dialog.text = "Herr Kapitän!";
			link.l1 = "Ein spanischer Kaufmann besiegt einen wagemutigen Piraten... Du denkst, was Longway denkt, oder?";
			link.l1.go = "PZ_Longway_32";
		break;
		
		case "PZ_Longway_32":
			dialog.text = "Der Morgenstern...";
			link.l1 = "Höchstwahrscheinlich - es gibt keinen anderen Handelskapitän wie ihn im gesamten Archipel.";
			link.l1.go = "PZ_Longway_33";
		break;
		
		case "PZ_Longway_33":
			dialog.text = "Wir müssen ihn sofort finden!";
			link.l1 = "Richtig. Aber ich sehe keine schweren Galeone im Hafen. Lassen wir uns mit dem Windbeutel unterhalten, bevor er gehängt wird. Mal sehen, ob er diesen Spitznamen verdient hat.";
			link.l1.go = "PZ_Longway_34";
		break;
		
		case "PZ_Longway_34":
			DialogExit();
			Return_LongwayOfficer();
			if (!CheckAttribute(pchar, "questTemp.PZ.Shipwreckers.Decline")) AddQuestRecord("PZ", "18");
			else AddQuestRecord("PZ", "18_1");
			pchar.questTemp.PZ_Beliz_Komendant = true;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		break;
		
		case "PZ_Beliz_Komendant_8":
			dialog.text = "Ist er noch am Leben? Können wir mit ihm sprechen?";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_9";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_9":
			StartInstantDialogNoType("BelizJailOff", "PZ_Beliz_Komendant_10", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_10":
			dialog.text = "Was? Oh, ja. Er lebt noch - die Hinrichtung hat noch nicht stattgefunden. Du kannst mit ihm sprechen - er ist gesprächiger als je zuvor. Aber in letzter Zeit spricht er meistens Unsinn, spricht hauptsächlich mit sich selbst. Der Schwätzer ist verrückt geworden... Ich kann es kaum erwarten, ihn aufzuhängen, bevor wir alle von seinem endlosen Geschwätz verrückt werden.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_11";
		break;
		
		case "PZ_Beliz_Komendant_11":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Beliz_Komendant_12":
			dialog.text = "Danke dir.";
			link.l1 = "";
			link.l1.go = "PZ_Beliz_Komendant_13";
			CharacterTurnByChr(npchar, CharacterFromID("BelizJailOff"));
		break;
		
		case "PZ_Beliz_Komendant_13":
			DialogExit();
			pchar.questTemp.jailCanMove = true;
			
			Return_LongwayOfficer();
			
			sld = CharacterFromID("BelizJailOff");
			LAi_SetHuberType(sld);
			sld.Dialog.Filename = "Common_Prison.c";
			sld.Dialog.CurrentNode = "First_officer";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_MatthewLutter", "mercen_15", "man", "man", 1, ENGLAND, -1, false, "quest"));
			sld.name = "Matthew";
			sld.lastname = "Lutter";
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_MatthewLutter1";
			ChangeCharacterAddressGroup(sld, "Beliz_prison", "goto", "goto9");
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "PZ_MatthewLutter1":
			dialog.text = "Er hat meinen Schatz gestohlen!";
			link.l1 = "Matthew Lutter?";
			link.l1.go = "PZ_MatthewLutter2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MatthewLutter2":
			dialog.text = "Mein Schatz ist jetzt an ihn gebunden, weißt du, an IHN! Es gibt nichts, was wir tun können! Was willst du?! Willst du uns noch etwas wegnehmen? Es ist nichts mehr übrig! Sie wird sterben! Oder schlimmer!";
			link.l1 = "Wer wird sterben? Welcher Schatz? Macht nichts, es ist deine eigene Schuld - du hast diese Galeone angegriffen, nicht andersherum.";
			link.l1.go = "PZ_MatthewLutter3";
		break;
		
		case "PZ_MatthewLutter3":
			dialog.text = "Nein! Es war genau andersherum! Verdammt sei dieser Hidalgo! Er ist der Grund, warum wir in diesem Schlamassel stecken! Er kam direkt auf uns zu und feuerte aus nächster Nähe! Dann hat er sie uns weggenommen!";
			link.l1 = "Wirklich? Das ist nicht überraschend. Was können Sie uns noch über ihn erzählen? Und... was hat er genommen? Wer ist 'sie'?";
			link.l1.go = "PZ_MatthewLutter5";
		break;
		
		case "PZ_MatthewLutter5":
			dialog.text = "A-A-A-Ah!!! A-A-A-A!!!";
			link.l1 = "Ich sehe, ich verschwende meine Zeit...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonSoldierDialog");
		break;
		
		case "PZ_BelizPrisonQuestSoldier1":
			dialog.text = "Kapitän, mit Ihrer Erlaubnis... Lutter! Raus! Ende der Linie, Kumpel.";
			link.l1 = "";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongway_UvodyatNaKazn");
		break;
		
		case "PZ_Longway_35":
			dialog.text = "Kapitän, wir müssen mehr über Sotta und Lutter herausfinden. Lassen Sie uns herumfragen.";
			link.l1 = "Gute Idee, Longway. Wir haben sowieso nicht viel von dem schreienden Mann bekommen.";
			link.l1.go = "PZ_Longway_36";
		break;
		
		case "PZ_Longway_36":
			dialog.text = "Aber es ist besser, mit Sotta zu beginnen.";
			link.l1 = "Richtig, er ist derjenige, den wir suchen. Los geht's.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_BelizPrisonLongwayBack");
		break;
		
		case "PZ_Longway_37":
			dialog.text = "Sie wissen nichts!";
			link.l1 = "Natürlich. Aber wir haben genug, um selbst zu denken. Von dem, was ich gehört habe, wird Sotta wahrscheinlich versuchen, diese strategischen Güter, die er belohnt wurde, bald zu verkaufen.";
			link.l1.go = "PZ_Longway_38";
		break;
		
		case "PZ_Longway_38":
			dialog.text = "Genau!";
			link.l1 = "Wir sollten ihn auf seinem Weg in Port Royal oder Capsterville abfangen. Die einzige Frage ist, wohin er geht und wo wir ihn angreifen sollten. Oder vielleicht erwischen wir ihn auf offenem Meer.";
			link.l1.go = "PZ_Longway_39";
		break;
		
		case "PZ_Longway_39":
			dialog.text = "Nein! Longway meinte... Fermentelos ist ein erfahrener Kapitän. Ein Kampf auf hoher See könnte in beide Richtungen gehen. Wir hätten bessere Chancen, ihn im Hafen zu überfallen.";
			link.l1 = "Sie haben Recht, vermute ich. Unabhängig davon, was wirklich zwischen Matt und ihm passiert ist, Sotta ist gefährlich und darf nicht unterschätzt werden.";
			link.l1.go = "PZ_Longway_40";
		break;
		
		case "PZ_Longway_40":
			dialog.text = "Wir können es auch kaum erwarten!";
			link.l1 = "Stimmt wieder, Longway. Lassen wir also sofort den Anker lichten, und dann planen wir unseren nächsten Schritt.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayBelizDialogBack");
			DelMapQuestMarkCity("Beliz");
		break;
		
		case "PZ_Longway_41":
			dialog.text = "Mein Herr Kapitän, die Morgenstern liegt im Hafen!";
			link.l1 = "Ja, das habe ich schon bemerkt.";
			link.l1.go = "PZ_Longway_42";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Longway_42":
			dialog.text = "Was ist dein Plan?";
			link.l1 = "Ich habe mich noch nicht entschieden. Ein Versuch, sie unter den Kanonen des Forts zu entern, wäre Selbstmord. Und selbst wenn wir ihre schwere Galeone erobern, können wir nicht auf ihr entkommen. Hast du irgendwelche Ideen, Longway?";
			link.l1.go = "PZ_Longway_43";
		break;
		
		case "PZ_Longway_43":
			dialog.text = "Ja. Wir könnten in einer sicheren Bucht ankern und das Galeonenschiff nachts mit dem Boot unter Deckung der Dunkelheit nähern.";
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				link.l1 = "Was ist mit Half Moon Bay, Longway?";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				link.l1 = "Ich denke, Portland Cove wäre passend - nah genug und relativ sicher. Was denkst du?";
			}
			link.l1.go = "PZ_Longway_44";
		break;
		
		case "PZ_Longway_44":
			dialog.text = "Gute Wahl.";
			link.l1 = "Großartig, das ist geklärt. Haben wir etwas übersehen?";
			link.l1.go = "PZ_Longway_45";
		break;
		
		case "PZ_Longway_45":
			dialog.text = "Ich glaube nicht, Mein Herr Kapitän. Wir müssen nur gut vorbereitet sein.";
			link.l1 = "Absolut.";
			link.l1.go = "PZ_Longway_46";
		break;
		
		case "PZ_Longway_46":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "GenQuest.CabinLock");
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			bQuestDisableMapEnter = false;
			AddQuestRecord("PZ", "21");
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Kapstervil"))
			{
				AddQuestUserData("PZ", "sText", "Half Moon Bay");
				Island_SetReloadEnableGlobal("Nevis", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore43";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_OhotaNaZvezdu_Yamaika"))
			{
				AddQuestUserData("PZ", "sText", "Portland Cove");
				Island_SetReloadEnableGlobal("Jamaica", true);
				
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1 = "location";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition.l1.location = "Shore36";
				PChar.quest.PZ_GotovimShlupki_Buhta.win_condition = "PZ_GotovimShlupki_Buhta";
			}
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition.l1 = "MapEnter";
			PChar.quest.PZ_ZvezdaUhodimNaGlobalkru_Proval.win_condition = "PZ_ZvezdaUhodimNaGlobalkru_Proval";
			
			sld = CharacterFromID("Longway");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
			sld.Dialog.CurrentNode = "Longway_officer";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan":
			dialog.text = "Wer zum Teufel bist du, was ist los? Herr Holmes!";
			link.l1 = "Herr Holmes arbeitet hier nicht mehr. Und wir haben alle Luken dicht verschlossen. Also, wir werden für eine Weile nicht gestört, Mynheer Fermentelos.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_2":
			dialog.text = "Was? Fermentelos? Mein Name ist Edgardo Sotta!";
			link.l1 = "Uh-huh, das habe ich schon einmal gehört. Wir wissen, dass Oliveiro nicht Ihr richtiger Name ist.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_3";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_3":
			dialog.text = "Fermentelos ist tot!";
			link.l1 = "Bei näherer Betrachtung, siehst du zu jung aus. Du hättest offensichtlich vor zehn Jahren nicht der Kapitän der Morgenstern sein können. Also, was ist mit Oliveiro passiert?";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_4";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_4":
			dialog.text = "Wir haben ihn los. Er war nur ein weiteres Problem, das wir bereinigen mussten - genau wie das, das neben dir steht.";
			link.l1 = "Nun, da Sie nicht Fermentelos sind, können Sie vielleicht trotzdem unsere Fragen beantworten. Wir suchen jemanden, den er meinem Freund genommen hat.";
			link.l1.go = "PZ_Zvezda_DialogWithCapitan_5";
		break;
		
		case "PZ_Zvezda_DialogWithCapitan_5":
			dialog.text = "Ich werde dir nichts erzählen! Er wird mir das niemals vergeben.";
			link.l1 = "Im Moment solltest du dir eher Sorgen machen, ob wir dir vergeben...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_SottaFight");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_AnabelleLutter1":
			dialog.text = "Er ist endlich tot...";
			link.l1 = "That's right. And who are you, madam? Did he hold you against your will? I sympathize; you must have been through a terrible ordeal...";
			link.l1.go = "PZ_AnabelleLutter2";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_AnabelleLutter2":
			dialog.text = "Ich bin Annabel Lutter. Und Gott sei Dank, ich musste nicht viel ertragen, aber ich schätze Ihre Besorgnis, Herr...?";
			link.l1 = "Kapitän Charles de Maure. Lutter, sagst du...";
			link.l1.go = "PZ_AnabelleLutter3";
		break;
		
		case "PZ_AnabelleLutter3":
			dialog.text = "Ach, du musst von Matt gehört haben? Der arme Narr... Ich war seine... Gefährtin.";
			link.l1 = "Es tut mir leid für Ihren Verlust, Frau Lutter. Sie sind jetzt eine Witwe. Wie war Ihr Mädchenname, wenn es kein Geheimnis ist?";
			link.l1.go = "PZ_AnabelleLutter4";
		break;
		
		case "PZ_AnabelleLutter4":
			dialog.text = "Ich hatte keinen. Schau mich genauer an. Meine arme Mutter war eine dunkelhäutige Sklavin der Piraten. Niemand weiß, wer mein Vater war, also haben sie sich nicht die Mühe gemacht, mir einen richtigen Namen zu geben.";
			link.l1 = "Warum hat dich damals niemand angefasst? Versteh mich nicht falsch - ich bin froh, dass es nicht passiert ist. Aber trotzdem ist es... ungewöhnlich.";
			link.l1.go = "PZ_AnabelleLutter5";
		break;
		
		case "PZ_AnabelleLutter5":
			dialog.text = "You're right. But let's call things by their proper names. I'm not a pampered noblewoman; I'm the daughter of a slave. I won't faint from a heavy conversation.";
			link.l1 = "Ähem, ich bin auch nicht für Verhätschelung. Aber bitte, fahren Sie fort. Warum hat die Mannschaft keinen Finger auf die Tochter des Sklavenmädchens gelegt? Du kennst deinen Vater nicht, und er schien sich nicht zu kümmern.";
			link.l1.go = "PZ_AnabelleLutter6";
		break;
		
		case "PZ_AnabelleLutter6":
			dialog.text = "Ich vermute nicht. Da Sie über Matt Bescheid wissen, wissen Sie auch, dass er eine Zeit lang für Levasseur gearbeitet hat?";
			link.l1 = "Ja, ich habe davon gehört, während ich nach dem Morgenstern gesucht habe. Aber was hat das damit zu tun? Erzählen Sie mir bitte alles.";
			link.l1.go = "PZ_AnabelleLutter7";
		break;
		
		case "PZ_AnabelleLutter7":
			dialog.text = "Sie verstehen immer noch nicht, oder? Anscheinend haben Sie noch nichts von Levasseurs... Vorlieben gehört?";
			link.l1 = "Ich habe nicht, aber was hat das mit... zu tun?";
			link.l1.go = "PZ_AnabelleLutter8";
		break;
		
		case "PZ_AnabelleLutter8":
			dialog.text = "Oh, ich nehme an, ich muss Ihnen alles erzählen. Setzen Sie sich, wenn Sie zu leicht zu beeindrucken sind, mein Herr. Die Sache ist die, er schläft mit vielen Frauen, und...";
			if (pchar.questTemp.FMQT == "end")
			{
				link.l1 = "Seine Frau ist nicht weit von ihm entfernt, und sie schläft mit fast jedem.";
				link.l1.go = "PZ_AnabelleLutterKnow1";
			}
			else
			{
				link.l1 = "Oh nein.";
				link.l1.go = "PZ_AnabelleLutterDontKnow1";
			}
		break;
		
		case "PZ_AnabelleLutterKnow1":
			dialog.text = " Nun, Sie wissen, was sie sagen... wie der Ehemann, so die Ehefrau. Aber nein, ich bin sicher, er ging viel weiter als das.";
			link.l1 = "Und wie weit?";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutterDontKnow1":
			dialog.text = "Ihr Sarkasmus ist hier fehl am Platz, Herr. Sie haben keine Ahnung, wovon wir sprechen.";
			link.l1 = "In Ordnung, in Ordnung, es tut mir leid. Bitte mach weiter.";
			link.l1.go = "PZ_AnabelleLutter9";
		break;
		
		case "PZ_AnabelleLutter9":
			dialog.text = "Es geht nicht nur darum, dass er seine Ehefrau betrügt. Er nimmt Frauen gegen ihren Willen. Und es handelt sich nicht nur um einmaligen Missbrauch. Er entführt Mädchen und hält sie in einem der Weinkeller, die er besitzt.";
			link.l1 = "Also bekommt er regelmäßig Sklavinnen? Und du solltest eine von ihnen sein?";
			link.l1.go = "PZ_AnabelleLutter10";
		break;
		
		case "PZ_AnabelleLutter10":
			dialog.text = "Sie haben recht mit Letzterem. Aber leider nicht mit dem Ersten. Er braucht keine Sklaven. Levasseur ist verrückt - auf seine eigene Weise, nicht wie mein Matt. Francois will eine Frau vollständig besitzen, Körper und Seele. Und es ging natürlich nicht um Liebe. Er brauchte freie Frauen, um ihren Willen zu brechen. Er genoss es, zu beobachten, wie sich ihr Aussehen, Verhalten und ihre Sprechweise im Laufe der Zeit veränderten...";
			link.l1 = "Ekelhaft...";
			link.l1.go = "PZ_AnabelleLutter11";
		break;
		
		case "PZ_AnabelleLutter11":
			dialog.text = "Sie fühlen sich schon ein wenig krank. Stellen Sie sich nun vor, wie es für diese Frauen gewesen sein muss. Ich habe von all dem gehört, und nicht nur von Matt. Levasseur hatte einmal eine portugiesische Adlige...";
			link.l1 = "Sie haben weggeschaut und geschwiegen. Erzählen Sie uns alles. Ich habe allerlei Dinge in der Alten Welt und auch während meiner Zeit im Archipel gesehen. Jetzt überrascht mich nichts mehr.";
			link.l1.go = "PZ_AnabelleLutterWant1";
			link.l2 = "Halt, ich möchte nicht wissen, was mit ihr passiert ist. Ich hoffe, diese Frauen haben nicht zu lange in seinen Händen gelitten.";
			link.l2.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutterWant1":
			dialog.text = "Aber Sie haben noch nie etwas Ähnliches gehört. Und ich hoffe, Sie sehen es nie. Sie wurde ihm noch stolz und ungebrochen gebracht, obwohl, wie Matt mir erzählte, Levasseurs Männer sie auf dem Weg nach Tortuga vergewaltigten, nachdem sie die Plantage ihres Mannes in der Nähe von Campeche übernommen hatten - er starb an einer Blutung, nachdem diese Monster ihn in beide Knie geschossen hatten...";
			link.l1 = "Eine starke Frau... Aber du hast gesagt, Levasseur rührt normalerweise die Frauen nicht an, die er für sich selbst haben will.";
			link.l1.go = "PZ_AnabelleLutterWant2";
		break;
		
		case "PZ_AnabelleLutterWant2":
			dialog.text = "Diejenigen, die er speziell angefordert hatte, wurden in Ruhe gelassen. Aber Señora Leontina war ein Geschenk. Ein unerwartetes und angenehmes für sie alle. Also haben sie sich verwöhnt...";
			link.l1 = "Ich verstehe...";
			link.l1.go = "PZ_AnabelleLutterWant3";
		break;
		
		case "PZ_AnabelleLutterWant3":
			dialog.text = "Ich vermute... Matt war zu einem von Francois' Favoriten geworden. Er wurde zu einer von Levasseurs geheimen Soirées eingeladen... Während des Festes beschwerte sich einer der Piraten, dass es nicht genug Frauen gab. Levasseur lachte und dann...";
			link.l1 = "Und dann? Was ist passiert?";
			link.l1.go = "PZ_AnabelleLutterWant4";
		break;
		
		case "PZ_AnabelleLutterWant4":
			dialog.text = "...dann wurde sie herausgebracht. An einer Leine! Geschlagen, ihr Rücken zerkratzt, mit verbundenen Augen und geknebelt. Als sie den Knebel entfernten, sagte sie nur...";
			link.l1 = "Etwas Schreckliches, stelle ich mir vor. Hat sie ihn mit allem verflucht, was sie hatte?";
			link.l1.go = "PZ_AnabelleLutterWant5";
		break;
		
		case "PZ_AnabelleLutterWant5":
			dialog.text = "Wenn nur... Dona Leontina flüsterte einfach, 'Was wünscht mein Herr?'";
			link.l1 = "Ich glaube, mir wird übel. Hat Matt dir erzählt, was danach mit ihr passiert ist?";
			link.l1.go = "PZ_AnabelleLutterWant6";
		break;
		
		case "PZ_AnabelleLutterWant6":
			dialog.text = "Ermordet, natürlich. Aber nicht durch Levasseurs Hände. Er hat sie wie einen streunenden Hund weggeworfen. Einer seiner Kapitäne hat sie erschossen. Bevor sie starb, sprach sie nur ein Wort...";
			link.l1 = "Ein Fluch? Ein Gebet?";
			link.l1.go = "PZ_AnabelleLutterWant7";
		break;
		
		case "PZ_AnabelleLutterWant7":
			dialog.text = "Nein. 'Danke...'";
			link.l1 = "Nach solchen Qualen für den Tod dankbar zu sein... Was sie ertragen haben muss... und andere wie sie in der Höhle dieses Monsters...";
			link.l1.go = "PZ_AnabelleLutter12";
		break;
		
		case "PZ_AnabelleLutter12":
			dialog.text = "Levasseur verachtete Sklaven und dunkelhäutige Frauen besonders - er sagte, es gäbe nichts in ihnen zu brechen. Sie hielten nicht lange bei ihm aus und genauso wenig die Indianer - außer einigen besonders sturen. Aber Wildheit und Rebellion waren auch keine Lösung - er tötete diejenigen, die ihm zu früh gefallen wollten und diejenigen, die zu lange trotzig blieben.";
			link.l1 = "Das ist schrecklich... Sag mir, hatte Levasseur jemals asiatische Frauen?";
			link.l1.go = "PZ_AnabelleLutter13";
		break;
		
		case "PZ_AnabelleLutter13":
			dialog.text = "Nein, zumindest nicht, dass ich gehört hätte. Was mich betrifft... Ich habe dir schon gesagt, dass er dunkelhäutige Frauen nicht mochte. Also, als Matt für Francois arbeitete, spazierte er offen mit mir auf den Straßen von Tortuga. Er hat mich sogar einmal zur Residenz mitgenommen.";
			link.l1 = "Aber Levasseur wollte dich sowieso zu einem seiner Sklaven machen...";
			link.l1.go = "PZ_AnabelleLutter14";
		break;
		
		case "PZ_AnabelleLutter14":
			dialog.text = "Genau... Ich weiß nicht, warum er mich so sehr mochte... Als Matt es herausfand, floh er von der Insel, sobald er es erfuhr. Er kehrte nie nach Tortuga zurück. Er mag ein bisschen verrückt gewesen sein, aber er liebte mich. Er nannte mich seinen Schatz...";
			link.l1 = "Also das meinte er, als er sagte, Sotta hätte seinen Schatz von ihm genommen!";
			link.l1.go = "PZ_AnabelleLutter15";
		break;
		
		case "PZ_AnabelleLutter15":
			dialog.text = "Heh, hat er das gesagt? Oh, Matt... Aber es scheint, als ob wir nie dazu bestimmt waren, zusammen alt zu werden. Wenn Levasseur ein Auge auf eine Frau geworfen hat, würde er alles tun, um sie zu bekommen, egal welcher Hintergrund sie hatte oder was es kostete. Sotta war einer seiner Kapitäne, und er tat, was man ihm sagte.";
			link.l1 = "Ich verstehe. Und was gedenken Sie jetzt zu tun, Annabel?";
			link.l1.go = "PZ_AnabelleLutter16";
		break;
		
		case "PZ_AnabelleLutter16":
			dialog.text = "Laufen. Irgendwohin, wo Levasseurs Männer mich nicht erreichen können. Meinen Namen ändern. Mich verkleiden...";
			link.l1 = "Ich hoffe, du hast Erfolg. Ich wünsche dir alles Gute, Annabel.";
			link.l1.go = "PZ_AnabelleLutter17";
			if (sti(pchar.Money) >= 10000)
			{
				link.l2 = "Sie werden Geld brauchen, um eine Passage zu arrangieren. Nehmen Sie das. Hier sind zehntausend Pesos.";
				link.l2.go = "PZ_AnabelleLutter17_Peso";
			}
			if (PCharDublonsTotal() >= 100)
			{
				link.l3 = "Sie werden mehr als nur ein wenig Geld brauchen. Nicht jeder ist bereit, einem dunkelhäutigen Mädchen zu helfen, auch nicht einer Halbblut. Hier, nehmen Sie hundert Dublonen - finden Sie ein Schiff und verstecken Sie sich.";
				link.l3.go = "PZ_AnabelleLutter17_Dublon";
			}
		break;
		
		case "PZ_AnabelleLutter17":
			dialog.text = "Auch Sie! Auf Wiedersehen, Kapitän.";
			link.l1 = "Auf Wiedersehen.";
			link.l1.go = "Exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Peso":
			dialog.text = "Ich... Ich weiß nicht, was ich sagen soll. Niemand außer Matt hat mir jemals solche Freundlichkeit gezeigt.";
			link.l1 = "Vielleicht ist es ein Zeichen. Dass du doch irgendwo glücklich alt wirst. Leb wohl.";
			link.l1.go = "Exit";
			AddMoneyToCharacter(pchar, -10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_AnabelleLutter17_Dublon":
			dialog.text = "Du hast Recht. Vielen Dank dafür. Ich werde dich mein Leben lang in meinen Gebeten in Erinnerung behalten.";
			link.l1 = "Danke dir. Gute Fahrt.";
			link.l1.go = "Exit";
			RemoveDublonsFromPCharTotal(100);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddDialogExitQuest("PZ_AnabelleGo");
		break;
		
		case "PZ_Longway_47":
			dialog.text = "Dieser Mann... Nein, er ist kein Mann mehr. Er ist ein Biest. Ein Monster. Frauen so zu foltern...";
			link.l1 = "Ich weiß, was du denkst, Longway. Aber du hast gehört - er hatte noch nie eine gelbhäutige Frau.";
			link.l1.go = "PZ_Longway_48";
			SetCameraDialogMode(npchar);
		break;
		
		case "PZ_Longway_48":
			dialog.text = "Aber er kannte die ganze Gruppe! Van der Vink, Fermentelos, Sotta... Wir haben gerade in seinem Tagebuch darüber gelesen. Was ist, wenn diese bestimmte 'sie'... sie ist?";
			link.l1 = "Wer weiß... Eine Frau, die auf Rache gegen Fermentelos aus ist - es ist einfach zu verstehen, warum du das denken würdest. Aber es könnte jede Frau gewesen sein, deren Leben von Oliveiro zerstört wurde. Es muss nicht deine Schwester sein. Es muss nicht einmal eine gelbhäutige Frau sein.";
			link.l1.go = "PZ_Longway_49";
		break;
		
		case "PZ_Longway_49":
			dialog.text = "Sind Sie... weigern sich, das zu versuchen, Herr Kapitän? Im allerletzten Moment...?";
			link.l1 = "Nein, Longway. Aber wie stellen Sie sich das vor? Es ist unwahrscheinlich, dass Levasseur eine unserer Fragen beantworten wird. Und auf diese Weise in Tortuga herumzuschnüffeln ist zu gefährlich.";
			link.l1.go = "PZ_Longway_50";
		break;
		
		case "PZ_Longway_50":
			dialog.text = "Was schlagen Sie vor?";
			link.l1 = "Wartet es ab. Wir wissen, dass Levasseur Frauen wie deine Schwester nicht mag. Also können wir unsere Ressourcen vorerst schonen. Geduld und Stärke. Francois ist eine harte Nuss, nicht zuletzt wegen seiner 'Schildkröte'. Aber mit Svensons Hilfe können wir mit ihm auf unseren Bedingungen sprechen. Ich habe dir versprochen, dir zu helfen, deine Schwester zu finden und beabsichtige, mich daran zu halten. Glaubst du mir, Longway?";
			link.l1.go = "PZ_Longway_51";
		break;
		
		case "PZ_Longway_51":
			dialog.text = "Hmm... Jawohl, Herr Kapitän. Aber Longway hat noch eine Bitte an Sie.";
			link.l1 = "Was ist los? Du planst nicht etwa wieder alleine loszuziehen, oder? Das letzte Mal endete das nicht so gut.";
			link.l1.go = "PZ_Longway_52";
		break;
		
		case "PZ_Longway_52":
			dialog.text = "Ganz und gar nicht, Herr Kapitän. Ich erkenne jetzt, dass leider ein Mann wie ich in einer von weißen Männern beherrschten Welt nichts alleine tun kann. Longway bittet Sie, in Capsterville anzulegen und Georges Gravel eine Notiz zu übergeben, in der er ihn bittet, etwas herauszufinden, während Sie sich vorbereiten.";
			link.l1 = "Ein vernünftiger Vorschlag, Longway. Wir werden das tun.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TeleportToShore");
		break;
		
		case "PZ_Longway_53":
			dialog.text = "Mein Herr Kapitän, es gibt etwas, was Longway fragen muss...";
			link.l1 = "Haben Sie vergessen, den Brief zu schreiben? Sie können einfach mit Gravel sprechen.";
			link.l1.go = "PZ_Longway_54";
		break;
		
		case "PZ_Longway_54":
			dialog.text = "Nein, der Brief ist fertig. Aber Longway dachte, es wäre am besten, nicht alleine in der Stadt herumzuwandern. Herr Kapitän... könnten Sie den Brief bitte für mich zu Georges bringen?";
			link.l1 = "Sehe ich aus wie ein Kurier für dich? Oder bist du hier der Kapitän?";
			link.l1.go = "PZ_Longway_55";
		break;
		
		case "PZ_Longway_55":
			dialog.text = "Mein Herr Kapitän...";
			link.l1 = "Ha ha ha, ich mache nur Spaß, Longway! Erinnere mich, wo ich diesen Gravel von dir finden kann?";
			link.l1.go = "PZ_Longway_56";
		break;
		
		case "PZ_Longway_56":
			dialog.text = "Er arbeitet in der Kirche.";
			link.l1 = "Also gut, ich kümmere mich darum.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToCapstervilleChurch");
			AddLandQuestMark(characterFromId("Charles_Priest"), "questmarkmain");
		break;
		
		// Этап 5
		case "PZ_Mary_Sharptown1":
			dialog.text = "Charles, mein lieber Charles, stimmt etwas nicht? Du siehst besorgt und... müde aus, ja, gell?";
			link.l1 = "Oh, nein, nein, Mary, mir geht es gut. Es ist nur... diese Tortuga-Quest von mir. Sie scheint wieder in einer Sackgasse zu sein... und dieser Sharp's Wille hat mich definitiv mitgenommen, zum Teufel nochmal. Aber macht nichts.";
			link.l1.go = "PZ_Mary_Sharptown2";
		break;
		
		case "PZ_Mary_Sharptown2":
			dialog.text = "Was? Welche Quest? Und was hat das mit Sharp zu tun? Ich verstehe nichts!";
			link.l1 = "Zu viele Fragen, Mary. Dies ist kein Ort für solche Gespräche. Sollen wir es im Tavernenzimmer besprechen? Ganz nach Ihrem Geschmack, außer Sicht und außer Verstand. Ich werde Sie darüber informieren, was ich im vergangenen Jahr getan habe.";
			link.l1.go = "PZ_Mary_Sharptown3";
		break;
		
		case "PZ_Mary_Sharptown3":
			dialog.text = "In Ordnung! Aber seien Sie gewarnt: wenn Sie etwas verbergen...";
			link.l1 = "Auf keinen Fall! Los geht's, wir haben sowieso Zeit zu töten...";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_Helena_Sharptown1":
			dialog.text = "Wie seltsam, nicht wahr, Charles? Ich sollte diese Insel besitzen, aber ich fühle mich überhaupt nicht so, als würde ich sie besitzen.";
			link.l1 = "Du denkst?";
			link.l1.go = "PZ_Helena_Sharptown2";
		break;
		
		case "PZ_Helena_Sharptown2":
			dialog.text = "Oh, dieses Grinsen von dir... Du weißt wirklich, wie man ein Mädchen behandelt. Aber was ist mit dir los? Dein Gesicht sieht ganz falsch aus!";
			link.l1 = "Warum? Das ist mein gewöhnliches Gesicht, sehr hübsch auch.";
			link.l1.go = "PZ_Helena_Sharptown3";
		break;
		
		case "PZ_Helena_Sharptown3":
			dialog.text = "Charles, ich kann es in deiner Stimme hören - du warst in letzter Zeit niedergeschlagen.";
			link.l1 = "Ich habe viel um die Ohren, besonders mit Longway. Ich bin einfach erschöpft. Aber es ist zu spät aufzugeben, besonders da ich ihm und meinem Vater ein Versprechen gegeben habe.";
			link.l1.go = "PZ_Helena_Sharptown4";
		break;
		
		case "PZ_Helena_Sharptown4":
			dialog.text = "Ich verstehe nicht... Was hat Longway damit zu tun? Und welche Versprechen haben Sie gegeben?";
			link.l1 = "Wenn wir darüber sprechen wollen, dann tun wir das in der Taverne, mieten ein Zimmer. Fern von anderen Menschen.";
			link.l1.go = "PZ_Helena_Sharptown5";
		break;
		
		case "PZ_Helena_Sharptown5":
			dialog.text = "In Ordnung, lass uns gehen. Es gibt sowieso nichts anderes zu tun, also können wir zumindest etwas Zeit zusammen verbringen.";
			link.l1 = "Führe den Weg, Liebling!";
			link.l1.go = "PZ_HelenaMary_Exit";
		break;
		
		case "PZ_HelenaMary_Exit":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			WaitDate("", 0, 0, 0, 2, 0);
			LAi_SetImmortal(npchar, true);
			ChangeCharacterAddressGroup(npchar, "Pirates_tavern_upstairs", "goto", "goto1");
			DoQuestReloadToLocation("Pirates_tavern_upstairs", "goto", "goto2", "PZ_Etap5_NaverhuTavernBandits");
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Schau, wie süß sie in den Armen des anderen schlafen! Bezaubernd!";
				link.l1 = "Eifersüchtig?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Macht die Augen auf! Wie habt ihr geschlafen, Turteltäubchen?";
				link.l1 = "Gut, danke der Nachfrage. Und wie haben Sie Jungs geschlafen?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_2";
			locCameraFromToPos(2.34, 1.92, 1.66, true, -1.66, -0.69, -0.02);
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Das ist eine dumme Frage, findest du nicht?";
				link.l1 = "Das ist es. Und eine dumme Sache, die du da gemacht hast. Willst du wissen warum?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Man sagt, Sie haben eine scharfe Zunge, Charles de Maure.";
				link.l1 = "Und nicht nur meine Zunge. Willst du es herausfinden? Aber sag mir, warum hast du nicht angegriffen, während wir schliefen?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_3";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Und warum ist das so?";
				link.l1 = "Sie sollten Mary am Morgen nicht wütend machen. Sie werden bald genug herausfinden, warum.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Einfach! Es ist dunkel, wissen Sie, also konnten wir nicht erkennen, welcher von Ihnen das Mädchen war.";
				link.l1 = "Drecksack.";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_4";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Anders als du habe ich keine Angst vor Frauen. Apropos - Jungs, bringt sie sicher und unversehrt her, sonst macht uns der Hugenotte zu Frauen!";
				link.l1 = "Hu... wer?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Zumindest sehe ich wie ein Mann aus. Jungs, nehmt die Blondine lebendig - der Hugenotte wartet auf sie.";
				link.l1 = "Hu... wer?";
			}
			link.l1.go = "PZ_Etap5_NaverhuTavernBandits_5";
		break;
		
		case "PZ_Etap5_NaverhuTavernBandits_5":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("PZ_NaverhuTavernBandits_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "PZ_Etap5_NaverhuTavernBandits_Win");
			}
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_1":
			DelLandQuestMark(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Wer war das, Charles? Wer zum Teufel ist dieser Hugenotte? Ist es wirklich...?";
				link.l1 = "Es gibt nur eine, Mary. Und wir sollten besser...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Charles... was war das? Ein Hugenotte? Ist das der Mann, von dem ich denke, dass er es ist?";
				link.l1 = "Ich fürchte ja, Helen. Wir müssen...";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_2";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Hörst du das? Jemand kommt, ja, gell. Wahrscheinlich Freunde dieser toten Männer.";
				link.l1 = "Dann werden wir sie ihnen anschließen sehen. Mach dich bereit...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Hörst du das? Schritte.";
				link.l1 = "Tatsächlich tue ich das. Stehe hinter mir.";
			}
			link.l1.go = "PZ_MaryHelena_BitvaNaverhu_3";
		break;
		
		case "PZ_MaryHelena_BitvaNaverhu_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			sld = CharacterFromID("Longway");
			sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
			sld.dialog.currentnode = "PZ_Longway_61";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			RemovePassenger(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "PZ_Longway_61":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Mein Herr Kapitän, Dame "+sStr+".";
			link.l1 = "Longway?! Du denkst, du kannst einfach so in unser Zimmer kommen? Was wäre wenn wir...?";
			link.l1.go = "PZ_Longway_62";
			
			//заранее создаём заглушку для корабля
			sld = GetCharacter(NPC_GenerateCharacter("PZ_ShipStasis", "citiz_46", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			SetSPECIAL(sld, 1, 1, 1, 1, 1, 1, 1);
		break;
		
		case "PZ_Longway_62":
			dialog.text = "Hm, entschuldigen Sie, Herr Kapitän. Ich dachte, Sie hätten die Tür geschlossen, wenn Sie so beschäftigt wären. Aber Longway hat sie offen gefunden.";
			link.l1 = "Gebrochen, nicht offen. Aber sag mir, mein Freund, warum bist du so verdammt ruhig? Es liegen Leichen auf dem Boden, wir sind bewaffnet und du bist...";
			link.l1.go = "PZ_Longway_63";
		break;
		
		case "PZ_Longway_63":
			dialog.text = "Nun, ich bin es gewohnt.";
			link.l1 = "Und damit können Sie nicht argumentieren, oder? Aber wirklich, haben Sie auf dem Weg hierher nicht die Geräusche des Kampfes gehört? Haben Sie nicht gesehen, wie diese Brut in die Taverne ging und direkt vor Ihnen die Treppe hinaufging? ";
			link.l1.go = "PZ_Longway_64";
		break;
		
		case "PZ_Longway_64":
			dialog.text = "Nein, Herr Kapitän. Ich habe keine Fremden im Flur gesehen auf meinem Weg hierher.";
			link.l1 = "Das ist ein lächerlicher Zufall. Was willst du also, Longway?";
			link.l1.go = "PZ_Longway_65";
		break;
		
		case "PZ_Longway_65":
			dialog.text = "Ich brauche dringend ein Schiff und eine Mannschaft, Herr Kapitän.";
			link.l1 = "Was? Warum? Haben Sie endlich Chang Xings Spur gefunden? In diesem Fall, lassen Sie uns sofort zusammen losgehen.";
			link.l1.go = "PZ_Longway_66";
		break;
		
		case "PZ_Longway_66":
			dialog.text = "Nicht Chang Xing, leider. Es ist... Joep van der Vink. Georges Gravel hat eine Nachricht geschickt und ich habe sie bekommen, während ich im Dorf herumspazierte, während du... dich mit der Dame ausgeruht hast.";
			link.l1 = "Ja, ich hatte eine großartige Ruhe, das kann ich Ihnen sagen. Aber warum sollten wir uns jetzt trennen, Longway? Wir haben eine verdammte lange Liste von wichtigen Aufgaben zu erledigen und gefährliche Leute zu töten.";
			link.l1.go = "PZ_Longway_67";
		break;
		
		case "PZ_Longway_67":
			dialog.text = "Van der Vink ist nicht so gefährlich wie Levasseur. Außerdem, ich habe ihn schon einmal besiegt. Und ich werde ihn wieder besiegen. Dieses Mal, um sicherzustellen, dass er für immer tot ist. Ich möchte nicht, dass wir alle wertvolle Zeit mit ihm verschwenden. Sie sollten nach Tortuga gehen und die wichtigen Leute nach allem fragen, was wir brauchen. Ich werde van der Vink selbst fangen. Herr Kapitän, das ist es nicht wert, Ihre Zeit zu verschwenden und ich war auch einmal Kapitän. Ich werde zurechtkommen.";
			link.l1 = "Hmm, Sie haben einen Punkt, Longway. Van der Vink mag vielleicht nicht so gefährlich sein, aber die 'Banten' ist eines der schnellsten Schiffe im Archipel. Nicht jedes Schiff wird ausreichen, um sie einzuholen. Und was ist mit der Besatzung? Wie planen Sie so schnell und alleine Männer zu versammeln?";
			link.l1.go = "PZ_Longway_68";
		break;
		
		case "PZ_Longway_68":
			dialog.text = "Ich kenne den richtigen Ort und ich habe die Compnay dort stehen. Oder zumindest kann ich so tun, als hätte ich das getan, wie ich es bei Georges getan habe. Die Gesellschaft... Mynheer Rodenburg hat ihre Dienste in Anspruch genommen, als er dringend kämpfende Männer, professionelle Mannschaften, die keine Fragen stellen, benötigte.";
			link.l1 = "Also eine Schiffsmannschaft zur Miete ... Es ergibt Sinn, dass es so etwas gibt. Und wie viel wird es kosten?";
			link.l1.go = "PZ_Longway_69";
		break;
		
		case "PZ_Longway_69":
			dialog.text = "Zweieinhalbtausend. Sofort und jetzt gleich.";
			link.l1 = "Das ist alles? Es braucht mehr als das, um eine volle Besatzung von regulären Seeleuten aus einer Taverne anzuheuern, besonders für ein großes Schiff. Anscheinend haben Rodenburg und seine Agenten spezielle Preise an speziellen Orten.";
			link.l1.go = "PZ_Longway_70";
		break;
		
		case "PZ_Longway_70":
			dialog.text = "Ich meinte Dublonen, Herr Kapitän.";
			link.l1 = "WAS?!";
			link.l1.go = "PZ_Longway_70_4";
		break;
		
		case "PZ_Longway_70_4":
			dialog.text = "Sie haben mich richtig gehört, Herr Kapitän. Es ist wichtig. Ich würde nicht um einen solchen Betrag für eine Kleinigkeit bitten.";
			link.l1 = "Ja, ich habe dich gehört, aber ich kann es immer noch nicht glauben. Spezielle Preise in der Tat. Akzeptieren sie Pesos?";
			link.l1.go = "PZ_Longway_70_5";
		break;
		
		case "PZ_Longway_70_5":
			dialog.text = "Ja... von weißen Leuten. Longway könnte damit Probleme haben, aber... Ich denke, ich werde sie überzeugen können, wenn ich hart genug frage. Es gibt immer einen Weg.";
			link.l1 = "Nun, das ist etwas. Und das ist nur für die Mannschaft... Und du hast auch ein Schiff, zu dem du kommen musst. Wahrscheinlich auch an einem 'besonderen Ort'? Ich habe Angst zu fragen, wie viel es uns kosten wird...";
			link.l1.go = "PZ_Longway_70_6";
		break;
		
		case "PZ_Longway_70_6":
			dialog.text = "Nicht ganz so, Herr Kapitän. Die Mannschaft kommt mit ihrem eigenen Schiff.";
			link.l1 = "Aber?";
			link.l1.go = "PZ_Longway_70_7";
		break;
		
		case "PZ_Longway_70_7":
			dialog.text = "Die 'Meifeng'. Sie könnte ein entscheidender Faktor werden - kein Schiff im Archipel ist schneller als sie. Und sie ist... war mein, also kenne ich sie. Würden Sie sie mir leihen, Herr Kapitän?";
			if (PCharDublonsTotal() >= 2500)
			{
				link.l1 = "Hier. Zweitausendfünfhundert Dublonen. Solange Sie mir van der Vinks Kopf auf einem Teller aus purem Gold bringen, ha ha ha ha!";
				link.l1.go = "PZ_Longway_Dublons_1";
			}
			if (sti(pchar.Money) >= 300000)
			{
				link.l2 = "Ich habe nicht so viele Dublonen, Longway. Und ich bezweifle, dass ich so viele auf dem Schiff hätte - das ist ein Haufen Gold, über den du redest. Aber Pesos, sicher. Dreihunderttausend ist genau das, was du brauchst.";
				link.l2.go = "PZ_Longway_Peso_1";
			}
			link.l3 = "Weißt du was, Longway... Schlägst du wirklich vor, dass ich genug Geld bezahle, um eine Belagerungsflotte zu bewaffnen, nur damit du einen gewöhnlichen Schläger bekämpfen kannst?!";
			link.l3.go = "PZ_Longway_Otkaz";
		break;
				
		case "PZ_Longway_Dublons_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "Oh... Longway dankt Ihnen von ganzem Herzen, Herr Kapitän! Aber was ist mit der 'Meifeng'?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "Was ist mit ihr? Mein Freund, hast du dir den Kopf gestoßen auf dem Weg hierher? Sie ist gerade in unserer Flotte!";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "Ich muss darüber nachdenken, Longway. Wie viel Zeit haben wir, um van der Vink zu erwischen?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
			RemoveDublonsFromPCharTotal(2500);
			pchar.questTemp.PZ_FlagShipDublons = true;
			notification("Longway approves", "Longway");
		break;
		
		case "PZ_Longway_Peso_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			dialog.text = "Mein Herr Kapitän, Sie haben sich ein wenig geirrt. Es wären zweihundertfünfzigtausend Pesos.";
			link.l1 = "I did not; it's Charles de Maure's special exchange rate when his friends need help, ha ha. I'm giving you extra so you'll have enough for everything.";
			link.l1.go = "PZ_Longway_Peso_2";
			AddMoneyToCharacter(pchar, -300000);
		break;
		
		case "PZ_Longway_Peso_2":
			dialog.text = "Vielen Dank, Herr. Kapitän... Aber, was ist mit der 'Meifeng'?";
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l1 = "Und was ist mit ihr? Mein Freund, hast du dir den Kopf gestoßen auf dem Weg hierher? Sie ist gerade in unserer Flotte!";
				link.l1.go = "PZ_Longway_Mayfang1";
			}
			else
			{
				link.l1 = "Ich muss darüber nachdenken, Longway. Wie viel Zeit haben wir, um van der Vink zu fangen?";
				link.l1.go = "PZ_Longway_NoMayfang1";
			}
		break;
		
		case "PZ_Longway_Otkaz":
			dialog.text = "Es gibt keinen anderen Weg, Herr Kapitän, bitte beruhigen Sie sich...";
			link.l1 = "Oh, ich habe noch nicht angefangen. Hier ist der Deal. Fünfzigtausend Pesos. Das reicht gerade aus, um eine Brigg vom Schiffswerft zu kaufen, sie für den Kampf vorzubereiten und sogar eine Besatzung anzuheuern.";
			link.l1.go = "PZ_Longway_Otkaz_2";
			AddMoneyToCharacter(pchar, -50000);
			
			pchar.questTemp.PZ.LongwayBrig = true; // Лонгвэй будет на бриге
			notification("Longway disapproves", "Longway");
		break;
		
		case "PZ_Longway_Otkaz_2":
			dialog.text = "Aber, Herr Kapitän. Es mag für einen weißen Kapitän ausreichen! Nicht jeder wird sich darauf einlassen, mit Longway Geschäfte zu machen. Sie werden hart verhandeln, bevor sie mir etwas verkaufen!";
			link.l1 = "Also, sei überzeugend! Du bist ziemlich gut im Handeln, wie dein anfänglicher... Vorschlag zeigt. Bist du immer noch hier? Nimm dieses Geld und geh, da es so dringend ist, wie du sagst!";
			link.l1.go = "PZ_Longway_Otkaz_3";
		break;
		
		case "PZ_Longway_Otkaz_3":
			dialog.text = "Jawohl, Herr Kapitän...";
			link.l1 = "Und schau mich nicht so an. Wir sehen uns später auf Tortuga. Viel Glück.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "58");
		break;
		
		case "PZ_Longway_Mayfang1":
			dialog.text = "Ähem, nein, Herr Kapitän. Natürlich, ich erinnere mich. Longway fragte nur, ob Sie bereit sind, sie mit mir zu teilen.";
			link.l1 = "Ich bin es. Schließlich ist van der Vink genauso an den Unglücken Ihrer Schwester beteiligt wie die anderen Personen auf unserer Liste. Deshalb ist es wirklich wichtig, ihn zu fangen. Ich übergebe Ihnen das Kommando über die Meifeng.";
			link.l1.go = "PZ_Longway_Mayfang2";
		break;
		
		case "PZ_Longway_Mayfang2":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "Ich kann es nicht glauben... Danke, Herr Kapitän!";
			link.l1 = "Ach, es ist nichts. Sie war einmal dein Schiff, das werde ich immer in Erinnerung behalten. Nun, mach weiter. Töte den Hurensohn. Ich bin auf dem Weg nach Tortuga.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			AddQuestRecord("PZ", "59");
			notification("Longway approves", "Longway");
		break;
		
		
		case "PZ_Longway_NoMayfang1":
			dialog.text = "Die Zeit ist knapp, Herr Kapitän. Wir sollten sie nicht verschwenden - Chang Xing könnte unsere Hilfe benötigen...";
			link.l1 = "Ich weiß das, Longway. Aber wie lange haben wir genau, um van der Vink zu fangen?";
			link.l1.go = "PZ_Longway_NoMayfang2";
		break;
		
		case "PZ_Longway_NoMayfang2":
			dialog.text = "Ein paar Monate - er hält sich etwa so lange auf seiner regelmäßigen Route auf, bevor er für eine Weile verschwindet. So ist seine Art, wie Gravel mir in seinem Brief mitteilte.";
			link.l1 = "In Ordnung. Dann gehen wir zum Schiff...";
			link.l1.go = "PZ_Longway_NoMayfang3";
		break;
		
		case "PZ_Longway_NoMayfang3":
			dialog.text = "Ich fürchte, meine Vorbereitungen müssen sofort beginnen, Herr Kapitän. Damit wir sofort loslegen können, wenn ich die Meifeng habe. Ich muss im Voraus mit den Männern verhandeln. ";
			link.l1 = "Also, wo treffen wir uns?";
			link.l1.go = "PZ_Longway_NoMayfang4";
		break;
		
		case "PZ_Longway_NoMayfang4":
			AddQuestRecord("PZ", "60");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) AddQuestUserData("PZ", "sText", "Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) AddQuestUserData("PZ", "sText", "Helen");
			
			i = FindColony("Pirates");
			if (colonies[i].nation != ENGLAND)
			{
				dialog.text = "Genau hier. Aber wir können uns zu Ihrer Bequemlichkeit in der Werft treffen.";
				link.l1 = "Und warum bin ich der einzige, der nicht wusste, dass man hier für den richtigen Preis eine volle Besatzung von Kämpfern anheuern kann?";
				link.l1.go = "PZ_Longway_NoMayfangIslaTesoro1";
			}
			else
			{
				dialog.text = "Diese Söldner hatten früher einen Platz auf Isla Tesoro, wurden aber gezwungen, hierher zu ziehen.";
				link.l1 = "Ich kann verstehen warum. Also, wo finde ich dich in La Vega?";
				link.l1.go = "PZ_Longway_NoMayfangLaVega1";
			}
		break;
		
		case "PZ_Longway_NoMayfangIslaTesoro1":
			dialog.text = "Weil nur sehr wenige davon wissen. Und noch weniger können es sich leisten. Mynheer Rodenburg war lange Zeit ihr einziger Kunde.";
			link.l1 = "Ich verstehe. Also gut, Longway. Wir sehen uns dort.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToPiratesShipyard");
		break;
		
		case "PZ_Longway_NoMayfangLaVega1":
			dialog.text = "Die Taverne, Mein Herr Kapitän. Wo sonst sollte ich sein?";
			link.l1 = "Das stimmt. Bis später dann, Longway! Pass auf dich auf.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LongwayToLaVegaTavern");
		break;
		
		case "PZ_Longway_WaitForShip1":
			dialog.text = "Mein Herr Kapitän, ich muss Ihnen mitteilen, dass die Mannschaft bereit ist. Es gibt noch eine letzte Angelegenheit zu klären. Was ist mit der 'Meifeng'?";
			link.l1 = "Bis jetzt habe ich wirklich kein Schiff ausgewählt, das Ihrer würdig ist, Longway.";
			link.l1.go = "PZ_Longway_WaitForShip2";
			if ((FindCompanionShips(SHIP_SCHOONER_W)) || (FindCompanionShips(SHIP_BRIG)) || (FindCompanionShips(SHIP_CORVETTE)) || (FindCompanionShips(SHIP_POLACRE)) || (FindCompanionShips(SHIP_XebekVML)) || (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				if (FindCompanionShips(SHIP_SCHOONER_W)) sStr = "War schooner";
				if (FindCompanionShips(SHIP_BRIG)) sStr = "Brig";
				if (FindCompanionShips(SHIP_CORVETTE)) sStr = "Corvette";
				if (FindCompanionShips(SHIP_POLACRE)) sStr = "Polacre";
				if (FindCompanionShips(SHIP_XebekVML)) sStr = "Xebek";
				if (FindCompanionShips(SHIP_BRIGANTINE)) sStr = "Brigantine";
				link.l2 = "'"+sStr+"' gehört Ihnen.";
				link.l2.go = "PZ_Longway_NoQuestShip1";
			}
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				link.l3 = "Was ist mit der 'Meifeng'? Dachtest du, ich lasse sie verkommen?";
				link.l3.go = "PZ_Longway_Mayfang3";
			}
			if (FindCompanionShips(SHIP_CURSED_FDM))
			{
				link.l4 = "Ich habe ein... besonderes Schiff für Sie, Longway. Ein schnelles. Und sogar tödlicher als Meifeng. Es ist ein Kriegsgaleone, das 'Fliegende Herz'.";
				link.l4.go = "PZ_Longway_Caleuche1";
			}
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				link.l5 = "Du magst Xebecs, Longway. Was ist mit Polacres? Besonders dieser hier, der 'Torero'. Natürlich nicht für Regatten gebaut, aber sie ist ziemlich kraftvoll.";
				link.l5.go = "PZ_Longway_Torero1";
			}
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				link.l6 = "Ich muss gestehen, ich hätte nicht gedacht, dass es eines Tages einen würdigen Einsatz dafür geben würde. Was hältst du von dieser Galeone? Der mächtige 'El Casador'!";
				link.l6.go = "PZ_Longway_ElCasador1";
			}
		break;
		
		case "PZ_Longway_NoQuestShip1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			
			// а теперь хором, дети: ненавижу костыли, ненавижу костыли, ненавижу костыли, нена... помогите!!!
			if ((FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_SCHOONER_W)
						{
							//pchar.questTemp.PZ.SchoonerW.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.SchoonerW.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwaySchoonerW = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIG)
						{
							//pchar.questTemp.PZ.Brig.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brig.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrig = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_CORVETTE)
						{
							//pchar.questTemp.PZ.Corvette.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Corvette.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayCorvette = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE)
						{
							//pchar.questTemp.PZ.Polacre.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.Polacre.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayPolacre = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (FindCompanionShips(SHIP_XebekVML)) && (!FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_XebekVML)
						{
							//pchar.questTemp.PZ.Xebek.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Xebek.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayXebek = true;
			}
			if ((!FindCompanionShips(SHIP_SCHOONER_W)) && (!FindCompanionShips(SHIP_BRIG)) && (!FindCompanionShips(SHIP_CORVETTE)) && (!FindCompanionShips(SHIP_POLACRE)) && (!FindCompanionShips(SHIP_XebekVML)) && (FindCompanionShips(SHIP_BRIGANTINE)))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_BRIGANTINE)
						{
							//pchar.questTemp.PZ.Brigantine.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Brigantine.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
				
				pchar.questTemp.PZ.LongwayBrigantine = true;
			}
			
			dialog.text = "Es ist nicht die 'Meifeng', Herr Kapitän! Was ist mit der Meifeng passiert?";
			link.l1 = "Longway! "+sStr+" ist in Gefahr! Und auch deine Schwester! Und du bist launisch, weil du kein Schiff wie dieses hast?! Jeder wäre glücklich mit einem Schiff wie diesem! Übernimm das Kommando und zeige van der Vink, wozu du fähig bist.";
			link.l1.go = "PZ_Longway_NoQuestShip2";
		break;
		
		case "PZ_Longway_NoQuestShip2":
			dialog.text = "Gut... Ich hoffe, der Himmel schickt mir Glück. Genau wie ich hoffe, dass es dir auf Tortuga gut geht. Auf Wiedersehen, Herr Kapitän.";
			link.l1 = "Ich bin mir sicher. Auf Wiedersehen, Longway.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			pchar.questTemp.PZ_NoQuestShip = true;
		break;
		
		case "PZ_Longway_Mayfang3":
			// если "Мейфенг" у ГГ
			if (FindCompanionShips(SHIP_MAYFANG))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							//pchar.questTemp.PZ.Mayfang.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Mayfang.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayMayfang = true;
			pchar.questTemp.PZ_FlagShip = true;
			
			dialog.text = "Ähem, nein, Herr Kapitän. Natürlich, ich erinnere mich. Longway fragte nur, ob Sie bereit sind, sie mit mir zu teilen.";
			link.l1 = "Ich bin es. Schließlich ist van der Vink genauso an den Unglücken Ihrer Schwester beteiligt wie die anderen Leute auf unserer Liste. Daher ist es wirklich wichtig, ihn zu fangen. Ich übergebe Ihnen das Kommando über die 'Meifeng'.";
			link.l1.go = "PZ_Longway_Mayfang4";
		break;
		
		case "PZ_Longway_Mayfang4":
			dialog.text = "Ich kann es nicht glauben... Danke, Herr Kapitän!";
			link.l1 = "Ach, das ist nichts. Sie war mal dein Schiff, das werde ich immer in Erinnerung behalten. Na los, töte den Hurensohn. Ich bin auf dem Weg nach Tortuga.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
			notification("Longway approves", "Longway");
		break;
		
		case "PZ_Longway_Caleuche1":
			dialog.text = "Ich... Ich kann DAS nicht befehlen, Herr Kapitän. Longway schert sich noch um sein Leben, seine Seele und seinen Verstand.";
			link.l1 = "Ha ha ha, Longway! Komm schon, ich wusste nicht, dass du so abergläubisch bist. Aber wie auch immer, der Fluch wurde aufgehoben, also hast du nichts zu befürchten.";
			link.l1.go = "PZ_Longway_Caleuche2";
		break;
		
		case "PZ_Longway_Caleuche2":
			dialog.text = "Ach... aber weiß van der Vink das? Er wird wie ein verängstigtes Kaninchen davonlaufen, sobald er dieses Schiff sieht.";
			link.l1 = "Du hast recht damit. Gut, wir finden etwas anderes für dich.";
			link.l1.go = "PZ_Longway_WaitForShip2";
		break;
		
		case "PZ_Longway_Torero1":
			// если "Тореро" у ГГ
			if (FindCompanionShips(SHIP_POLACRE_QUEST))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_POLACRE_QUEST)
						{
							//pchar.questTemp.PZ.Torero.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.Torero.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayTorero = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				notification("Longway approves", "Longway");
			}
			
			dialog.text = "Bin nie einen Polacre gesegelt, als ich selbst Kapitän war. Sie ist interessant, aber Geschwindigkeit ist jetzt das Wichtigste, nicht Kraft.";
			link.l1 = "Das stimmt, aber es ist immerhin eine Polacre. Sie ist vielleicht nicht so schnell wie die 'Banten', aber Sie können den Wind aus Winkeln einfangen, die sie nicht können. Sogar mehr als die 'Meifeng' selbst es jemals konnte. Nutzen Sie das also aus.";
			link.l1.go = "PZ_Longway_Torero2";
		break;
		
		case "PZ_Longway_Torero2":
			dialog.text = "Noch ... die 'Meifeng' war besser ... Schade, dass du sie hast verfallen lassen, Herr Kapitän. Viel Glück auf Tortuga.";
			link.l1 = "Gleichfalls, Longway. Danke.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_ElCasador1":
			// если "Эль Касадор" у ГГ
			if (FindCompanionShips(SHIP_ELCASADOR))
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_ELCASADOR)
						{
							//pchar.questTemp.PZ.ElCasador.CompanionIndex = sld.Index;
							//sld = GetCharacter(sti(pchar.questTemp.PZ.ElCasador.CompanionIndex));
							SeaAI_SwapShipsAttributes(sld, CharacterFromID("PZ_ShipStasis"));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			
			pchar.questTemp.PZ.LongwayElCasador = true;
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShipDublons"))
			{
				pchar.questTemp.PZ_FlagShip = true;
				notification("Longway approves", "Longway");
			}
			
			dialog.text = "Dass es vielleicht die ungewöhnlichste Galeone im Archipel ist, Herr Kapitän. Ich kann damit umgehen, aber es ist langsamer als die 'Banten'...";
			link.l1 = "Nun, Sie treten doch nicht gegen Joep in einer Regatta an, oder?";
			link.l1.go = "PZ_Longway_ElCasador2";
		break;
		
		case "PZ_Longway_ElCasador2":
			dialog.text = "Was auch immer Sie sagen. Aber die 'Meifeng' war besser... Schade, dass Sie sie verschwendet haben, Herr Kapitän. Viel Glück auf Tortuga.";
			link.l1 = "Ebenso, Longway. Danke.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_NeedToTortuga");
		break;
		
		case "PZ_Longway_WaitForShip2":
			NextDiag.TempNode = "PZ_Longway_WaitForShip1";
			
			dialog.text = "Ich schätze Ihre Sorge, Herr Kapitän, aber bitte beeilen Sie sich - wir haben nicht viel Zeit.";
			link.l1 = "Ich weiß. Aber Sie wollen doch keine wilde Gansjagd machen, oder? Also gut, ich werde Ihnen ein anständiges Schiff finden.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaTortugaCabin_1":
			dialog.text = "Wir sind fast da, Charles. Haben Sie schon entschieden, wo wir anfangen sollen? Vielleicht macht es Sinn, die Leute auf der Straße zu fragen...";
			link.l1 = "Vielleicht tut es das. Aber nicht für uns - für mich. Du bleibst an Bord, Helen.";
			link.l1.go = "PZ_HelenaTortugaCabin_2";
		break;
		
		case "PZ_HelenaTortugaCabin_2":
			dialog.text = "Charles, natürlich, ich bin immer noch unruhig wegen dieser Schurken und was sie gesagt haben, und es ergibt Sinn für mich, unter dem Schutz der Crew zu bleiben... Aber dass du alleine in die Höhle des Biests gehst, lässt mich mich nicht sicherer fühlen.";
			link.l1 = "Ich verstehe. Aber wenn etwas schief geht, ist es viel einfacher, alleine zu fliehen, wenn man weiß, dass du sicher bist. Es ist ein Befehl, Helen. Warte hier auf mich und versuche, dir nicht zu viele Sorgen zu machen.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_MaryTortugaCabin_1":
			dialog.text = "Hier ist Tortuga, Charles, ja, gell. Ich kann es kaum erwarten, an einigen Türen zu klopfen und zu fragen, was dieser fette Esel von mir wollte...";
			link.l1 = "Genau deshalb bleibst du an Bord, meine Liebe.";
			link.l1.go = "PZ_MaryTortugaCabin_2";
			
			pchar.questTemp.MarySexBlock = true;
			pchar.quest.Mary_giveme_sex.over = "yes";
			pchar.quest.Mary_giveme_sex1.over = "yes";
		break;
		
		case "PZ_MaryTortugaCabin_2":
			dialog.text = "Auf keinen Fall! Denkst du, ich lasse dich alleine an Land gehen?";
			link.l1 = "Ich denke, wenn Levasseur beschließt, das zu beenden, was seinen Söldnern nicht gelungen ist, werden wir keine Chance haben, uns zu wehren. Ich möchte ihn nicht unnötig provozieren, vor allem da mein Ziel nicht er, sondern Joep van der Vink ist.";
			link.l1.go = "PZ_MaryTortugaCabin_3";
		break;
		
		case "PZ_MaryTortugaCabin_3":
			dialog.text = "Also bin ich jetzt eingesperrt, ja, gell?";
			link.l1 = " Ich befehle dir nicht, ich frage dich, Mary.";
			link.l1.go = "PZ_MaryTortugaCabin_4";
		break;
		
		case "PZ_MaryTortugaCabin_4":
			dialog.text = "Was ist, wenn dir in irgendeiner dunklen Gasse dieser Scheißinsel etwas zustößt?";
			link.l1 = "Dann verspreche ich, keinen Helden zu spielen. Und zu wissen, dass du sicher bist, wird mir helfen, schneller zu laufen. Also warte auf mich auf dem Schiff und um Gottes willen, geh nicht an Land, egal was passiert.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaCabin_Exit");
		break;
		
		case "PZ_RobertMartin1":
			chrDisableReloadToLocation = true;
			
			dialog.text = "Wer sind Sie? Ich bezweifle, dass Sie über den Strand gelaufen sind, nur um zu plaudern.";
			link.l1 = "Das stimmt. Charles de Maure. Rober Martene?";
			link.l1.go = "PZ_RobertMartin2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_RobertMartin2":
			dialog.text = "Der Charles de Maure? Scheiße, zieh mich bloß nicht in etwas Schattiges hinein. Ja, das bin ich. Also, was willst du?";
			link.l1 = "Ich habe gehört, du bist mit Joep van der Vink befreundet, und...";
			link.l1.go = "PZ_RobertMartin3";
		break;
		
		case "PZ_RobertMartin3":
			dialog.text = "Wer hat Ihnen das gesagt? Ich werde ihre Eingeweide ausschütten. Nun, wir kennen uns, das ist alles. Ich möchte keinen Ärger, weil er Sie überkreuzt hat.";
			link.l1 = "Heh, du gibst deine Freunde schnell auf...";
			link.l1.go = "PZ_RobertMartin4";
		break;
		
		case "PZ_RobertMartin4":
			dialog.text = "Denken Sie nicht so. Ich habe keine Angst vor Ihnen. Aber warum sich die Mühe machen oder sie sogar erst erzeugen? Ich kenne Joep nicht so intim, wie Ihnen erzählt wurde. Suchen Sie ihn?";
			link.l1 = "Ja, sozusagen. Ich weiß, dass er Tortuga bereits verlassen hat, aber es wäre nicht schlecht, mehr über ihn zu erfahren - wo er gewesen ist, mit wem er gesprochen hat. Können Sie helfen?";
			link.l1.go = "PZ_RobertMartin5";
		break;
		
		case "PZ_RobertMartin5":
			dialog.text = "Es würde dir sowieso nicht helfen, also... warum nicht? Er war in einem Bordell. Dem Bordell. Ich denke, du kannst es dir leisten, also erzähle ich dir davon.";
			link.l1 = "Ein neues Bordell? Ist Ihnen das alte nicht mehr genug?";
			link.l1.go = "PZ_RobertMartin6";
		break;
		
		case "PZ_RobertMartin6":
			dialog.text = "Nun, nicht neu, aber nicht viele Leute wissen davon. Und nur wenige können es sich leisten. Ich vermute, Ihre Zeit ist gekommen. Aber seien Sie gewarnt - nur Dublonen werden akzeptiert. Geben Sie Silber heraus, und Sie bekommen einen Tritt in den Arsch.";
			link.l1 = "Ich dachte es mir schon. Und wo sagtest du ist dieses Bordell?";
			link.l1.go = "PZ_RobertMartin7";
		break;
		
		case "PZ_RobertMartin7":
			dialog.text = "Sie kennen das Gebäude mit den Säulen? Das ist das. Und was für eine Gastgeberin sie haben! Gelbhäutig, so hübsch! Huh, ich sehe, Sie sabbern schon, huh?";
			link.l1 = "Heh-heh, sozusagen. Danke, Rober. Keine Schwierigkeiten heute für dich - du warst mir eine große Hilfe.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LighthouseMartinGo");
		break;
		
		case "PZ_MaryTortugaCabin_11":
			dialog.text = "Endlich bist du zurück, Charles! Ich konnte keinen Platz für mich finden, ja, gell!";
			link.l1 = "Ich werde nicht lange weg sein, Mary. Ich habe ein kleines Geschäft zu erledigen... Ich werde dich nicht in Spannung halten - es geht um Longways Angelegenheiten. Ich muss ein örtliches Bordell besuchen.";
			link.l1.go = "PZ_MaryTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_MaryTortugaCabin_12":
			dialog.text = "Ich wusste, dass ich dich nicht alleine an Land lassen hätte sollen. Entweder hast du vergessen, deinen Hut aufzusetzen, und dein Kopf wurde heiß... Oder du hast ihn dir gestoßen, ja, gell!";
			link.l1 = "Mary, höre mir zu. Es ist möglich, dass die Besitzerin dieses Etablissements Longways Schwester ist. Um sicher zu sein, müsste ich sie sehen, aber das ist alles, was ich tun werde. Ich kann das nicht tun, ohne hineinzugehen. Aber ich möchte nicht, dass du etwas denkst, was du nicht solltest.";
			link.l1.go = "PZ_MaryTortugaCabin_13";
		break;
		
		case "PZ_MaryTortugaCabin_13":
			dialog.text = "Bist du sicher, dass du mich nicht anlügst, Charles?";
			link.l1 = "Mary, sieh es so... Hast du jemals von einem Mann gehört, der seine Geliebte vor... warnt?";
			link.l1.go = "PZ_MaryTortugaCabin_14";
		break;
		
		case "PZ_MaryTortugaCabin_14":
			dialog.text = "Halt einfach an, Charles, ich möchte nicht einmal darüber nachdenken. Ich glaube und vertraue dir. Und ich hoffe, du bleibst dort nicht länger als nötig.";
			link.l1 = "Nicht eine Minute länger, Liebling, ich verspreche es. Rein und raus, du wirst sehen.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_HelenaTortugaCabin_11":
			dialog.text = "Charles! Du bist sogar schneller zurück als ich erwartet habe. Aber was ist passiert? Du siehst nicht gut aus... Hast du etwas über Joep van der Vink herausgefunden?";
			link.l1 = "Noch nicht. Ich habe ein paar Dinge gelernt, aber um weiter zu gehen... muss ich zu einem... Bordell. Natürlich nicht für das, was du vielleicht denkst.";
			link.l1.go = "PZ_HelenaTortugaCabin_12";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_HelenaTortugaCabin_12":
			dialog.text = "Ein Bordell? Ich wusste nicht, dass diese Orte etwas anderes als das Offensichtliche anbieten. Ш: Ich muss nur mit dem Besitzer sprechen, das ist alles. Und es ist nicht irgendein Bordell. Es heißt, es ist eine sehr teure Einrichtung, nur für Mitglieder der Oberschicht...";
			link.l1 = "Ich verspreche, dass ich strikt im Auftrag von Longway handle. Es ist durchaus möglich, dass die Besitzerin dieses Ortes seine Schwester ist. Ich werde nicht lange dort sein.";
			link.l1.go = "PZ_HelenaTortugaCabin_13";
		break;
				
		case "PZ_HelenaTortugaCabin_13":
			dialog.text = "Nun, dann ist es genau richtig für dich, Liebling. Oh, ich mache nur Spaß. Trotzdem bin ich nicht begeistert, dass du dorthin gehst. Aber... Wie du willst. Du bist nicht verpflichtet, mich über solche Dinge zu informieren. Ich habe dir nie versprochen, dass ich nicht mit einem anderen Mann schlafen würde. Und doch tue ich es nicht. Weil es etwas ist, was ich für selbstverständlich halte.";
			link.l1 = "Unter anderen Umständen hätte ich dich mitgenommen, aber...";
			link.l1.go = "PZ_HelenaTortugaCabin_14";
		break;
		
		case "PZ_HelenaTortugaCabin_14":
			dialog.text = "Danke, aber nein danke. Charles, mach dir keine Sorgen. Ich bin nicht irgendein dummer eifersüchtiges Mädchen. Nun, vielleicht eifersüchtig, aber nicht dumm. Und ich glaube dir. Dumm von mir!";
			link.l1 = "Danke, Helen. Ich bin gleich wieder da.";
			link.l1.go = "PZ_PredupredilNashuDevushku";
		break;
		
		case "PZ_PredupredilNashuDevushku":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.PZ_PredupredilNashuDevushku = true;
		break;
		
		case "PZ_ElitaShluha_1":
			dialog.text = "Oh, ein neues Gesicht in unserem Etablissement? Willkommen, Monsieur. Essen, gereifter Wein, ein heißes Bad - alles erwartet Sie, wenn Sie es sich leisten können, Zeit mit einem von uns zu verbringen.";
			link.l1 = "Danke für Ihre Begrüßung, Mademoiselle. Aber deswegen bin ich nicht hier. Ich suche jemanden...";
			link.l1.go = "PZ_ElitaShluha_2";
			
			// Убираем Мартэна с Маяка
			sld = characterFromID("PZ_RobertMartin");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			
			for (i=1; i<=3; i++)
			{
				sld = characterFromID("PZ_MayakPiraty_"+i);
				sld.lifeday = 0;
			}
			
			sld = characterFromID("PZ_RobertMartin_CloneMayakShip");
			sld.lifeday = 0;
			
			locations[FindLocation("Mayak6")].DisableEncounters = false;
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak6")], false);
			RemoveGeometryFromLocation("Mayak6", "smg");
		break;
		
		case "PZ_ElitaShluha_2":
			dialog.text = "It is only with the heart that one can see rightly; what is essential is invisible to the eye.";
			link.l1 = "Wunderschön. Diese Zeilen habe ich noch nie gehört.";
			link.l1.go = "PZ_ElitaShluha_3";
		break;
		
		case "PZ_ElitaShluha_3":
			dialog.text = "Wir sind hier gebildet, nicht nur Puppen. Die Gastgeberin hält es für wesentlich für unser Etablissement.";
			link.l1 = "Die Wirtin! Die suche ich. Ich habe gehört, sie hat gelbe Haut. Sag mal, stimmt das? Wie heißt sie eigentlich?";
			link.l1.go = "PZ_ElitaShluha_4";
		break;
		
		case "PZ_ElitaShluha_4":
			dialog.text = "Es ist wahr. Aber sie hat ein besseres Geschäftssinn als viele weiße Frauen. Ihr Name ist Belle Etoile. Aber genug geredet.";
			link.l1 = "Genug geredet, sagst du? Ich bin hier für das Gespräch. Ich werde noch ein paar Fragen stellen und dann gehen.";
			link.l1.go = "PZ_ElitaShluha_5";
		break;
		
		case "PZ_ElitaShluha_5":
			dialog.text = "Und welchen Nutzen hat das für das Etablissement? Hier zahlen sie nicht für Körper, sondern für Zeit. Sie wollen reden? Seien Sie willkommen. Aber Geld im Voraus. Und wir flüstern im Zimmer, fern von neugierigen Ohren. Es ist mir egal, was wir dort tun - es ist mir egal, ob wir Kerzen anzünden und beten. Ein Kunde bat mich einmal, ihm ein Gedicht zu schreiben. Ein anderer sprach über seine Probleme, nannte mich seinen guten Freund. Und ein dritter - nur um Kerzen zu anzünden, damit dann...";
			link.l1 = "Nun, ich möchte es nicht wissen - ich habe kürzlich schon etwas Unangenehmes gehört. Wie viel schulde ich Ihnen?";
			link.l1.go = "PZ_ElitaShluha_6";
		break;
		
		case "PZ_ElitaShluha_6":
			dialog.text = "Zweihundertfünfzig Dublonen. Kein Handeln. Wenn wir merken, dass wir einen mittellosen Blender betrachten, werfen wir ihn ohne Reue hinaus. Und wenn er wohlhabend, aber gierig ist, erhöhen wir den Preis - er wird sowieso bezahlen.";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Hier hast du, zweihundertfünfzig Goldstücke.";
				link.l1.go = "PZ_ElitaShluha_7";
			}
			link.l2 = "Whoa, dieser Ort ist teurer als das Bordell in Jamaika. Kann ich später zurückkommen, nachdem ich das Gold bekommen habe?";
			link.l2.go = "PZ_ElitaShluha_Otkaz_1";
		break;
		
		case "PZ_ElitaShluha_7":
			dialog.text = "Gut. Wo sollen wir anfangen? Abendessen, mit oder ohne Kerzen, Bad, Gespräch?";
			link.l1 = "Ich habe nicht viel Zeit, also kommen wir gleich zu meinen Fragen. Führen Sie den Weg.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Otkaz_1":
			dialog.text = "Natürlich können Sie das. Geduld ist eine der Tugenden einer Kurtisane. Einen Bettler hinauszuwerfen ist eine Sache. Einen wohlhabenden Herrn wie Sie gehen zu lassen und sein Geld zu holen oder es sogar auszuleihen, ist eine ganz andere Sache.";
			link.l1 = "Die Tugenden einer Kurtisane... Ironisch. Ich komme gleich zurück.";
			link.l1.go = "PZ_ElitaShluha_Otkaz_2";
		break;
		
		case "PZ_ElitaShluha_Otkaz_2":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
			npchar.dialog.filename = "Quest\CompanionQuests\Longway.c";
			npchar.dialog.currentnode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again":
			dialog.text = "Willkommen zurück, Monsieur! Also, wer bist du? Ein reicher Herr oder ein Prahlhans?";
			if (PCharDublonsTotal() >= 250)
			{
				link.l1 = "Natürlich bin ich ein wohlhabender Gentleman, Mademoiselle. Hier ist dein Gold - alle zweihundertfünfzig Dublonen. Keine Notwendigkeit, es zu zählen.";
				link.l1.go = "PZ_ElitaShluha_Again_1";
			}
			link.l2 = "Ich bin immer noch kurz angebunden, bitte ertragen Sie es.";
			link.l2.go = "exit";
			NextDiag.TempNode = "PZ_ElitaShluha_Again";
		break;
		
		case "PZ_ElitaShluha_Again_1":
			dialog.text = "Wir zählen hier nicht. Hmm, einige der Münzen sehen verbogen und kaputt aus - die Herrin wird das nicht besonders mögen, aber zumindest ist es alles echtes Gold.";
			link.l1 = "Wie... anmutig sie ist.";
			link.l1.go = "PZ_ElitaShluha_Again_2";
			RemoveDublonsFromPCharTotal(250);
		break;
		
		case "PZ_ElitaShluha_Again_2":
			dialog.text = "Das ist richtig. Madam Etoile kann sanft und fürsorglich sein, sie kann streng sein, und sie kann gnadenlos sein. Deswegen zählen wir übrigens nicht. Die Herrin wird nicht immer sofort bezahlt, aber sie bekommt immer ihr Fälliges. Wenn nicht in Gold, dann in Blut. Jedes Toleranzhaus braucht Beschützer und Gönner. Und unsere passen zum Status der Einrichtung.";
			link.l1 = "Ich habe bezahlt, also führen Sie den Weg.";
			link.l1.go = "PZ_ElitaShluha_IdemVKomnatu";
		break;
		
		case "PZ_ElitaShluha_IdemVKomnatu":
			DialogExit();
			pchar.PZ_ElitaShluha = npchar.id;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload3", "PZ_ElitaShluha_VKomnate", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			bDisableCharacterMenu = true;
		break;
		
		case "PZ_ElitaShluha_8":
			dialog.text = "Also, welche Fragen haben Sie, Monsieur? Ich werde versuchen, Ihre... Neugier zu befriedigen.";
			link.l1 = "Sie wissen, was mich interessiert, Mademoiselle - Ihre Herrin, Madame Etoile.";
			link.l1.go = "PZ_ElitaShluha_9";
		break;
		
		case "PZ_ElitaShluha_9":
			dialog.text = "Was kann ich über sie sagen? Sie bleibt ein Rätsel, sogar für uns. Obwohl sie sich um unser Wohlbefinden, unsere Gesundheit und Sicherheit kümmert, gesellt sie sich nicht oder kommt uns nicht nahe.";
			link.l1 = "Vielleicht mag sie keine langen Gespräche. Sag mir, spricht sie mit Akzent?";
			link.l1.go = "PZ_ElitaShluha_10";
		break;
		
		case "PZ_ElitaShluha_10":
			dialog.text = "Nein, was lässt Sie das denken? Nur weil sie gelbhäutig ist? Sie spricht reines Französisch und mehrere andere Sprachen. Und sie kann stundenlang über jedes Thema mit Gästen und potenziellen Interessenten sprechen.";
			link.l1 = "Das sagst du nicht. Interessant... Ist sie jetzt hier? Wenn ja, gehe ich einfach hinein und sehe sie, damit ich nicht mehr von deiner wirklich... teuren Zeit verschwende, damit du wieder arbeiten kannst.";
			link.l1.go = "PZ_ElitaShluha_11";
		break;
		
		case "PZ_ElitaShluha_11":
			dialog.text = "Es gibt nicht viel, zu dem man zurückkehren könnte - obwohl das Ziel unserer Gastgeberin ist, diesen Ort zum besten im Archipel zu machen. Ein elitärer Ort, an dem sich kein Kaufmann, Adliger oder einfach eine gebildete Person schämen würde zu kommen - weil wir viel mehr als unsere Körper anbieten.";
			link.l1 = "Aber sie ist nicht sehr erfolgreich dabei, oder?";
			link.l1.go = "PZ_ElitaShluha_12";
		break;
		
		case "PZ_ElitaShluha_12":
			dialog.text = "Wie soll ich es ausdrücken... Sie sieht jeden von uns nicht nur als Ware, wie in einfacheren Etablissements, sondern als ein Projekt. Teure Kleidung, Medizin, Bildung - sie investiert in jeden von uns. Und wenn wir in einer großen Stadt in der Alten Welt wären, hätte sie Erfolg gehabt! Aber hier... Selbst ein talentierter Händler wird nichts verdienen, wenn die Waren so teuer sind, dass fast niemand sie kaufen kann. Selbst wenn wir die Preise senken, sind wir doch dazu bestimmt, eines Tages pleite zu gehen.";
			link.l1 = "Es tut mir leid, das zu hören. Wo ist Ihre Herrin jetzt?";
			link.l1.go = "PZ_ElitaShluha_13";
		break;
		
		case "PZ_ElitaShluha_13":
			dialog.text = "Wir führen bisher ein gutes Leben hier, das kann ich Ihnen sagen. Es hat seinen Preis, es zu verdienen und ihren Standards gerecht zu werden... Was die Dame betrifft, so ist sie nach Espanola gegangen, um die Möglichkeit zu erörtern, uns alle nach Port-au-Prince umzusiedeln - schließlich laufen dort mehr Handelsrouten zusammen, und unser Handel wird nicht untätig bleiben und dort fast ständige Verluste erleiden.";
			link.l1 = "Ist das so? Hat Levasseur nicht in diesen Ort investiert, um seine Stabilität zu gewährleisten?";
			link.l1.go = "PZ_ElitaShluha_14";
		break;
		
		case "PZ_ElitaShluha_14":
			dialog.text = "Nicht zu viel. Er kam zu uns und sagte, er würde nur groß investieren, wenn wir ab und zu zu ihm kämen. Aber die Dame lehnte schroff ab. So sehr, dass Seine Gnaden für eine Sekunde aus dem Konzept gebracht wurde. Ich habe sie oder ihn noch nie so gesehen.";
			link.l1 = "Heh-heh, schau mal. Sie scheint zu wissen... Mutig, sehr mutig von ihr.";
			link.l1.go = "PZ_ElitaShluha_15";
		break;
		
		case "PZ_ElitaShluha_15":
			dialog.text = "Weißt du was? Aber da wir so gut sprechen, erzähle ich dir etwas anderes, aber es ist ein großes Geheimnis, also bespreche es mit niemandem!";
			link.l1 = "Ach nein, Mademoiselle. Ich versichere Ihnen, ich habe nicht vor, Ihrer Dame in irgendeiner Weise zu schaden. Bitte fahren Sie fort.";
			link.l1.go = "PZ_ElitaShluha_16";
		break;
		
		case "PZ_ElitaShluha_16":
			dialog.text = "Ich weiß nicht einmal, ob Sie ihr Schaden zufügen könnten, denn Belle Etoile übt jeden Tag das Fechten, und sie hat in der ganzen Stadt keinen würdigen Gegner. Zusätzlich zu Port-au-Prince plant sie, Marcus Tyrex selbst zum Investieren anzubieten! Oder eher, von ihm ein Darlehen zu bekommen. Können Sie sich das vorstellen?";
			link.l1 = "Ja, und ich habe das Gefühl, dass ich heute ein sehr schwieriges Gespräch mit einer anderen Frau führen werde, die regelmäßig Fechten übt... Nun, danke fürs Teilen, Mademoiselle. Einen schönen Tag und großzügige Kunden wünsche ich Ihnen.";
			link.l1.go = "PZ_ElitaShluha_17";
		break;
		
		case "PZ_ElitaShluha_17":
			dialog.text = "Danke. Aber warum die Eile? Sie haben vollständig bezahlt und wir haben noch nicht lange gesprochen. Außerdem haben Sie etwas Verfeinertes, Monsieur. Etwas viel mehr als die seltenen reichen Männer, die zu unserem Haus kommen. Sollen wir uns wirklich gegenseitig Gesellschaft leisten?";
			link.l1 = "Weißt du... was zur Hölle? Warum tue ich so, als ob ich das nicht will? Eine Chance mit einer Frau wie dir ist sehr selten.";
			link.l1.go = "PZ_ElitaShluha_YesSex";
			link.l2 = "Oh, ich bedaure, nein, Fräulein. Ich bin nur zum Reden hierher gekommen. Außerdem... Ich habe jemanden, der auf mich wartet.";
			link.l2.go = "PZ_ElitaShluha_NoSex";
		break;
		
		case "PZ_ElitaShluha_NoSex":
			dialog.text = "Als ob das jemals jemanden gestoppt hätte. In diesem Fall verdienen Sie Respekt, Monsieur. Ich freue mich sehr für Ihre 'jemand'.";
			link.l1 = "Vielen Dank noch einmal, Mademoiselle. Auf Wiedersehen.";
			link.l1.go = "PZ_ElitaShluha_NoSex_2";
		break;
		
		case "PZ_ElitaShluha_NoSex_2":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_ElitaShluha_YesSex":
			dialog.text = "Danke. Wie wäre es zum Anfang mit einem heißen Bad zusammen?";
			link.l1 = "Beide Hände dafür.";
			link.l1.go = "PZ_ElitaShluha_YesSex_2";
		break;
		
		case "PZ_ElitaShluha_YesSex_2":
			DialogExit();
			LAi_SetStayType(pchar);
			DoQuestCheckDelay("PlaySex_1", 1.0);
			DoQuestCheckDelay("PZ_ElitaShluha_Fuck", 1.0);
		break;
		
		case "PZ_ElitaShluha_After":
			dialog.text = "Das war eine magische Erfahrung, Monsieur. Ich dachte nicht, dass ein Mann mich so überraschen könnte. Sie wissen wirklich, wie man einer Frau Vergnügen bereitet...";
			link.l1 = "Es kommt auf die Frau an.";
			link.l1.go = "PZ_ElitaShluha_After_2";
		break;
		
		case "PZ_ElitaShluha_After_2":
			dialog.text = "Bereuen Sie es?";
			link.l1 = "Jetzt definitiv nicht. Auf Wiedersehen, Mademoiselle.";
			link.l1.go = "PZ_ElitaShluha_After_3";
		break;
		
		case "PZ_ElitaShluha_After_3":
			DialogExit();
			AddQuestRecord("PZ", "30");
			chrDisableReloadToLocation = false;
			bDisableFastReload = true;
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("PZ_ElitaShluha_"+i);
				LAi_CharacterDisableDialog(sld);
			}
			npchar.lifeday = 0;
			LAi_SetPlayerType(pchar);
			pchar.questTemp.PZ.EliteWhoreFucked = true; // флаг того, что секс был (понадобится для диалога с Тираксом)
			
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition.l1.location = "Tortuga_town";
			PChar.quest.PZ_TortugaKlemanLebren.win_condition = "PZ_TortugaKlemanLebren";
			DelMapQuestMarkCity("Tortuga");
			AddMapQuestMarkCity("LaVega", false);
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1 && !CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
			{
				setCharacterShipLocation(pchar, "Tortuga_town");
				setWDMPointXZ("Tortuga_town");
			}
		break;
		
		case "PZ_KlemanLebren_1":
			dialog.text = "Achte darauf, wohin du gehst, Möchtegern!";
			link.l1 = "Halte dein Maul!";
			link.l1.go = "PZ_KlemanLebren_2";
		break;
		
		case "PZ_KlemanLebren_2":
			dialog.text = "Ich habe darauf geachtet, wohin ich gehe, während Sie Krähen gezählt haben.";
			link.l1 = "Sie hätten doch herumgehen können, wenn Sie gesucht hätten, oder?";
			link.l1.go = "PZ_KlemanLebren_3";
		break;
		
		case "PZ_KlemanLebren_3":
			dialog.text = "Wieso sollte ich Sie umgehen?!";
			link.l1 = "Ich schlage vor, wir finden außerhalb der Stadt heraus, wer wem was schuldet.";
			link.l1.go = "PZ_KlemanLebren_4";
		break;
		
		case "PZ_KlemanLebren_4":
			dialog.text = "Mm-mm, nein. Ich wusste nicht, dass Eure Herrlichkeit so angeekelt von der unbeabsichtigten Berührung eines einfachen Mannes ist.";
			link.l1 = "Wie bitte?";
			link.l1.go = "PZ_KlemanLebren_5";
		break;
		
		case "PZ_KlemanLebren_5":
			dialog.text = "Hmm, entschuldigung. Es war nicht meine Absicht, dich zu drängen.";
			link.l1 = "Das ist besser.";
			link.l1.go = "PZ_KlemanLebren_6";
		break;
		
		case "PZ_KlemanLebren_6":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "", "", "", "", -1);
			npchar.location = "None";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				DelLandQuestMark(sld);
				if (CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku"))
				{
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
					PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
				}
				else
				{
					ChangeCharacterAddressGroup(sld, "Tortuga_town", "rld", "loc0");
					sld.dialog.filename = "Quest\CompanionQuests\Longway.c";
					sld.dialog.currentnode = "PZ_MaryRazgovorOBordeli_Bad_1";
					LAi_SetStayType(sld);
					CharacterTurnToLoc(sld, "quest", "quest1");
					sld.talker = 5;
					chrDisableReloadToLocation = true;
					LAi_LocationFightDisable(loadedLocation, true);
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				DelLandQuestMark(sld);
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
				PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_1":
			dialog.text = "Wenn du eine halbe Stunde zu spät wärst, Charles, hätten unsere Kanonenkugeln diese dreckige Höhle schon in Stücke geschlagen, ja, gell! Hast du gefunden, wonach du gesucht hast? Ist das sie, Longways Schwester? Hast du sie gesehen?";
			link.l1 = "Shh, Mary, sprich nicht so. Nein, ich konnte Chang Xing nicht treffen...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_2";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_2":
			dialog.text = "Dann was zum Teufel hat dich so lange aufgehalten?! Was hast du dort gemacht?";
			link.l1 = "Sie haben nichts zu befürchten. Sobald ich alles herausgefunden hatte, was ich konnte, verließ ich diesen Ort, genau wie ich es Ihnen versprochen habe.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_3":
			dialog.text = "Einfach ausspucken, ja, gell!";
			link.l1 = "Der Besitzer ist momentan nicht auf Tortuga. Die Nachfrage nach ihren Diensten ist hier gering, da sie gut ausgebildete Damen in teuren Kleidern beschäftigt, und sie akzeptieren nur Gold als Zahlung...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_4":
			dialog.text = "Haben Sie sie auch bezahlt?!";
			link.l1 = "Sie hätten sonst gar nicht mit mir gesprochen. Bei dieser Art von Vorgehen ist es kein Wunder, dass sie nicht viele Kunden haben. Die Madame hat beschlossen, ihr Geschäft nach Port-au-Prince zu verlegen, in der Hoffnung, eine wohlhabendere Kundschaft anzuziehen. Aber sie ist offensichtlich knapp bei Kasse, da sie sich dazu entschieden hat, Marcus Tyrex um ein Darlehen zu bitten...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_5":
			dialog.text = "Weiß er von ihr?";
			link.l1 = "Wir werden es herausfinden, wenn wir in La Vega ankommen. Und wenn wir uns beeilen und aufhören, Zeit mit unnötigem Geschwätz zu verschwenden, werden wir diese asiatische Frau fangen, wer immer sie auch sein mag.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Good_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Good_6":
			dialog.text = "Es war unnötig, in dieses Bordell zu gehen, Charles. Ich bin sicher, wir hätten all das in der Kneipe oder auf den Straßen herausfinden können, wenn wir uns genug angestrengt hätten, ja, gell?";
			link.l1 = "Nächstes Mal nehme ich dich mit, damit du deinen hübschen roten Kopf nicht mit Unsinn füllst, ja, gell? Jetzt aber zur Sache.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_1":
			dialog.text = "Oh, ich sehe, ich bin ein bisschen spät, ja, gell! Nun, halt durch, du Schurke...";
			link.l1 = "Mary, was zum Teufel machst du hier?! Ich habe dir gesagt, du sollst auf dem Boot bleiben!";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_2":
			dialog.text = "Also würde ich dich nicht davon abhalten, Spaß mit Huren zu haben?! Denk nicht einmal daran, es zu leugnen, Charles! Die Crew hat dich dort gesehen, ja, gell?! Wie konntest du?!";
			link.l1 = "Das habe ich mir gedacht. Ich vermute, ich hätte sie mitnehmen sollen, damit sie sehen könnten, was ich tue - oder besser gesagt, nicht tue - und nicht so ein großes Drama daraus machen...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_3":
			dialog.text = "Sie beschuldigen unsere Jungen der Lüge? Nach dem, was Sie selbst getan haben, Sie Brut?";
			link.l1 = "Ich beschuldige sie nur unvergleichlicher Dummheit. Ohne die Situation zu verstehen, du...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_4":
			dialog.text = "Oh-oh, Charles, ich glaube nicht, dass es dir und deinen Huren gefallen hätte, wie ich die Situation verstanden hätte, wenn ich rechtzeitig zu diesem Loch gekommen wäre. Aber du hast Glück - ich musste dieses verdammte Boot ganz alleine rudern...";
			link.l1 = "Sie sagen, harte körperliche Arbeit klärt den Kopf von unnötigen Gedanken. Aber du hast immer noch viele von ihnen, also rudern Sie auch zurück.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_5":
			dialog.text = "Ich bewege mich nicht, ja, gell!";
			link.l1 = "Mary, ich werde diese Unterhaltung hier nicht vor Levasseurs Männern führen. Beruhige dich, schau dich um und triff eine Entscheidung. Dies ist weder die Zeit noch der Ort.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_6":
			dialog.text = "Zum Teufel mit dir. Ich habe immer noch meine Sachen in der Kabine... Aber denke nicht, dass ich wieder die Ruder bedienen werde, ja, gell! Es muss noch etwas von einem Edelmann in dir übrig sein!";
			link.l1 = "Ich bin ein Schurke und ein Ungeheuer, erinnern Sie sich? Ich werde es auf dem Schiff beweisen, aber ich muss zuerst dorthin gelangen. Also sind Ihre Bitten zwecklos.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_7":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", Get_My_Cabin(), "rld", "loc1", "OpenTheDoors", -1);
			
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1 = "location";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_TortugaRazgovorVKauteSDevushkoy.win_condition = "PZ_TortugaRazgovorVKauteSDevushkoy";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_8":
			dialog.text = "Du hast die ganze Crew zum Lachen gebracht, ja, gell!";
			link.l1 = "Nun, vielleicht auch bei dir. Sie haben schon lange kein Spektakel mehr gesehen. Jetzt, wo dein Temperament ein wenig abgekühlt ist, lass mich dir erzählen, was passiert ist.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_9";
			
			DeleteAttribute(pchar, "questTemp.MarySexBlock");
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_9":
			dialog.text = "Charles, ich habe nun alles gehört. Ich habe nur eine Frage: War ich nicht gut genug für dich? Fehlt mir etwas?";
			link.l1 = "Es ist unhöflich, aber ich werde mit einer Frage antworten: Habe ich dir jemals einen guten Grund gegeben, mir nicht zu vertrauen? Huh? Ich erinnere mich nicht an so etwas. Also atme tief durch und hör mir zu. Ich konnte nicht viel über Joep van der Vink herausfinden, außer dass er in einem Bordell war. Nicht das in der Nähe der 'Singenden Krähe', sondern ein anderes in der Nähe des Piers. Ich wusste vorher nichts davon... im Gegensatz zu unseren Matrosen, die dich auf den neuesten Stand gebracht haben. Obwohl sie dort nicht hätten hingehen dürfen...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_10";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_10":
			dialog.text = "Welches Bordell lässt keine Matrosen rein, ja, gell?";
			link.l1 = "Ein Bordell, in dem sie seidenbekleidete Damen beschäftigen, die mehr als nur Luft in ihren Köpfen haben. Und ihre Dienste werden ausschließlich in Gold-Dukaten bezahlt. Es ist nicht nur eine Laune jedermanns, sondern die Anordnung ihrer geheimnisvollen Herrin, Belle Etoile.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_11";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_11":
			dialog.text = "Mysteriös, ja, gell.";
			link.l1 = "Es ist nicht nur das. Sie ist Asiatin.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_12";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_12":
			dialog.text = "Asiatin? Die Puffmutter vom Bordell auf Tortuga?";
			link.l1 = "Es könnte Chang Xing sein. Deshalb ging ich dorthin - Ich wollte sie mit meinen eigenen Augen sehen. Das ist alles.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_13";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_13":
			dialog.text = "Wie ist sie so?";
			link.l1 = "Ich habe keine Ahnung. Sie war nicht da, also musste ich mit einem anderen... Stern plaudern.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_14";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_14":
			dialog.text = "War sie auch Asiatin, ja, gell?";
			link.l1 = "Nein, sie war weiß. Sie hat mir erzählt, dass es Belle Etoile in letzter Zeit nicht so gut ging, also hat sie beschlossen, nach Port-au-Prince zu ziehen. Macht Sinn, da die Leute dort wohlhabender wären. Die Puffmutter muss knapp bei Kasse sein, da sie ein Darlehen benötigt, um einen Handel in Espanola zu eröffnen, welches sie von Tyrex nehmen möchte. Also, wenn wir uns nach La Vega beeilen, können wir sie abfangen, bevor sie Marcus trifft.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_15";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_15":
			dialog.text = "Es ist mir völlig egal, was mit ihr oder Marcus oder sonst wem passiert, ja, gell. Charles, sag mir nur eins - warst du bei einem der Mädchen in ihrem Bordell?";
			link.l1 = "Ich brauche das nicht, Mary. Ich habe dich, das beste Mädchen der Welt. Ich verstehe nicht, warum du das nicht erkennst.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_16";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_16":
			dialog.text = "Eigentlich ist es wirklich einfach, die Wahrheit herauszufinden, ja, gell, hihi. Wenn du mit niemandem zusammen warst, musst du jetzt voller Energie sein. Das werden wir jetzt überprüfen, ja, gell!";
			link.l1 = "Mary, bitte..";
			link.l1.go = "exit";
			pchar.quest.sex_partner = Npchar.id;
			AddDialogExitQuest("cabin_sex_go");
			pchar.questTemp.PZ_MaryRazgovorOBordeli = true;
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_17":
			DeleteAttribute(pchar, "questTemp.PZ_MaryRazgovorOBordeli");
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				if (IsCharacterPerkOn(pchar, "Medic"))
				{
					notification("Excellent Health", "Medic");
					dialog.text = "(Ausgezeichnete Gesundheit) Ugh... Sieht so aus, als hättest du nicht gelogen, Charles, ja, gell...";
					link.l1 = "Ich habe keine Notwendigkeit, Sie zu täuschen, meine Liebe...";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
				}
				else
				{
					notification("Perk check failed", "Medic");
					dialog.text = "Charles, bist du... bist du ernsthaft?! Was war das?";
					link.l1 = "Ach, diese Hitze tut mir nicht gut. Ähem.";
					link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_19";
				}
			}
			else
			{
				dialog.text = "Ugh... Sieht so aus, als hättest du nicht gelogen, Charles, ja, gell...";
				link.l1 = "Ich habe keine Notwendigkeit, Sie zu täuschen, meine Liebe...";
				link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_18";
			}
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_18":
			dialog.text = "Aber diese Dinghy-Fahrt werde ich lange nicht vergessen!";
			link.l1 = "Ha!";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_19":
			dialog.text = "Sie haben sich noch nie zuvor darüber beschwert, oder?";
			link.l1 = "Versuchen Sie, auf der verdammten Insel herumzurennen...";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_20";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_20":
			dialog.text = "Und die Bordelle, ja, gell! Hast du wirklich...";
			link.l1 = "Mary, es tut mir leid.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_21";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_21":
			dialog.text = "Was?! Also du bist...";
			link.l1 = "Es tut mir nicht leid dafür. Scheiße. Ich meine, ich war mit niemandem außer dir, habe ich dir gesagt. Ich konnte einfach... meinen Verstand nicht beruhigen, das ist alles. Es ist schwer, das zu tun, weißt du, mit den Kanonen von La Roche, die dich anstarren.";
			link.l1.go = "PZ_MaryRazgovorOBordeli_Bad_22";
		break;
		
		case "PZ_MaryRazgovorOBordeli_Bad_22":
			dialog.text = "Das ist eine feine Ausrede, Charles. In Ordnung, ich werde dir glauben. Dieses Mal... Aber wisse, dass ich immer noch sauer auf dich bin, ja, gell!";
			link.l1 = "Ich werde mir deine Vergebung verdienen, das verspreche ich.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_1":
			dialog.text = "Nun, Liebesjunge, erzähl mir, was du herausgefunden hast. War es das Risiko meiner Gunst wert?";
			link.l1 = "Ich kann wirklich nicht sagen, ob Sie scherzen oder ernst sind. Es hat sich gelohnt - obwohl ich die Gastgeberin nicht mit meinen eigenen Augen gesehen habe. Sie ist Asiatin und ihr Name ist Belle Etoile - ein wunderbarer Stern. Natürlich nicht ihr echter Name...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_2":
			dialog.text = "Und dafür musstest du in ein Bordell gehen? Konntest du das nicht in der Kneipe herausfinden? Ш: In der Stadt sprechen sie nicht wirklich über diesen Ort. Warum? Das ist eine gute Frage. Sie können Belle Etoile selbst fragen - sie ist nach Espanola gegangen.";
			link.l1 = "Sie sprechen in der Stadt nicht wirklich über diesen Ort. Warum? Das ist eine gute Frage. Sie können Belle Etoile selbst fragen - sie ist nach Espanola gegangen.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_3":
			dialog.text = "War Tortuga nicht genug für sie?";
			link.l1 = "Der Handel scheint hier nicht gut zu laufen. Sie beschäftigt keine gewöhnlichen Hafendamen, sondern reich gekleidete, gebildete Damen.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_4":
			dialog.text = "Und warum sollten sie das tun?";
			link.l1 = "Das ist eine weitere gute Frage. Wie auch immer, unser kleiner Vogel hat sich entschieden, nach Port-au-Prince zu fliegen, das Lehen von de Mussac. Aber das Darlehen für dieses Unterfangen sollte von niemand anderem als Tyrex kommen.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Good_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Good_5":
			dialog.text = "Ich möchte, dass diese Geschichte bald vorbei ist. Lassen wir keine Zeit verschwenden und setzen den Kurs auf La Vega.";
			link.l1 = "Das werden wir tun.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_1":
			dialog.text = "Du bist ein tapferer Mann, Charles, das muss ich dir lassen. So einfach auftauchen, mit solch einem ernsten Gesicht, als wäre nichts passiert.";
			link.l1 = "Ich vermute, einer der Besatzungsmitglieder hat geplaudert? Natürlich ohne jeden Zusammenhang. Denn es ist wirklich nichts passiert - zumindest nicht das, was Sie denken.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_2";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_2":
			dialog.text = "Ich bin froh, dass du es nicht geleugnet hast, Charles.";
			link.l1 = "Ich wollte dir alles erzählen, Helen.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_3";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_3":
			dialog.text = "Mach's nicht, Charles. Die Details interessieren mich nicht sehr. Aber die Gründe dafür schon. Sag mal, stimmt etwas nicht mit mir?";
			link.l1 = "Lassen wir mit den Gründen anfangen. Ich habe herausgefunden, dass es auf Tortuga zwei Bordelle gibt. Das eine ist bekannt. Über das andere - die Leute wissen davon, aber wenige wollen darüber sprechen. Es gehört einer asiatischen Frau...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_4";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_4":
			dialog.text = "Machst du das gerade aus dem Stegreif?";
			link.l1 = "Warum zum Teufel sollte ich das tun, Helen?! Wenn du mir nicht glaubst, sie werden es an dem Ort bestätigen!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_5";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_5":
			dialog.text = "Erstens, Sie haben mir gesagt, ich soll nicht an Land gehen, also gibt es keine Möglichkeit, dass ich dorthin komme. Zweitens, wer zur Hölle glauben Sie, dass ich bin?! Ich werde mich nicht einem Ort wie diesem nähern! Drittens... machen Sie einfach weiter.";
			link.l1 = "Gut. Ich habe beschlossen, dorthin zu gehen, um Madame Étoile mit meinen eigenen Augen zu sehen. Das war meine einzige Absicht, verdammt noch mal!";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_6";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_6":
			dialog.text = "Ich vermute. Hast du sie getroffen?";
			link.l1 = "Nein. Sie ist nach Espanola gegangen. Hier läuft es nicht gut für sie, also hat sie beschlossen, ihr Glück in Port-au-Prince zu versuchen. Dort können die in Seide gekleideten, gut ausgebildeten Damen, die in ihrer Einrichtung arbeiten, ihr mehr Gewinn bringen als auf Tortuga...";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_7";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_7":
			dialog.text = "Aufgeputzt und gebildet? Oh, was das Leben einem bringen kann. Aber du solltest sie genau so mögen, wie sie sind.";
			link.l1 = "Helen, hör auf. Ich habe nichts getan, um dein Misstrauen zu verdienen.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_8";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_8":
			dialog.text = "Das stimmt. Wenn du versucht hättest, mich zu täuschen, wärst du nicht so ruhig. Aber du hättest mich vor deinen Plänen warnen sollen, Charles.";
			link.l1 = "Du hast recht, Liebling. Aber ich habe beschlossen, etwas Zeit zu sparen. Mein Fehler.";
			link.l1.go = "PZ_HelenaRazgovorOBordeli_Bad_9";
		break;
		
		case "PZ_HelenaRazgovorOBordeli_Bad_9":
			dialog.text = "In Ordnung. Was jetzt, setzen wir einen Kurs nach Port-au-Prince?";
			link.l1 = "La Vega. Seien Sie nicht überrascht, Helen. Madame Belle Etoile geht es nicht gut. Sie brauchte ein Darlehen, um ihren Handel nach Port-au-Prince zu verlegen, also entschied sie sich, es von Marcus zu leihen. Wenn wir uns beeilen, können wir sie dort erwischen. Also verschwenden wir keine Minute.";
			link.l1.go = "PZ_NaLaVega";
		break;
		
		case "PZ_NaLaVega":
			DialogExit();
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) 
			{
				AddLandQuestMark(characterFromId("Terrax"), "questmarkmain");
				QuestSetCurrentNode("Terrax", "PZ1");
			}
			else 
			{
				AddLandQuestMark(characterFromId("Vensan"), "questmarkmain");
				QuestSetCurrentNode("Vensan", "PZ1");
			}
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			Island_SetReloadEnableGlobal("Tortuga", true);
			bQuestDisableMapEnter = false;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = CharacterFromID("Mary");
				AddPassenger(pchar, sld, false);
				Return_MaryOfficer();
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = CharacterFromID("Helena");
				AddPassenger(pchar, sld, false);
				Return_HelenaOfficer();
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_PredupredilNashuDevushku")) AddQuestRecord("PZ", "31");
		break;
		
		case "PZ_KlemanLebren_7":
			dialog.text = "Ich kann nicht glauben, dass ein Arschloch wie du und dein Gesindel uns besiegt haben!";
			link.l1 = "Du...";
			link.l1.go = "PZ_KlemanLebren_8";
		break;
		
		case "PZ_KlemanLebren_8":
			dialog.text = "Oh, erkennst du mich?";
			link.l1 = "Haben wir uns getroffen?";
			link.l1.go = "PZ_KlemanLebren_9";
		break;
		
		case "PZ_KlemanLebren_9":
			dialog.text = "Was?! Verarschst du mich?!";
			link.l1 = "Ich kann mich nicht an jeden unzivilisierten Abschaum erinnern, den ich treffe. Du solltest uns besser sagen, wer dich geschickt hat, um uns zu töten. Oder wollten sie dich vielleicht nur loswerden?";
			link.l1.go = "PZ_KlemanLebren_10";
		break;
		
		case "PZ_KlemanLebren_10":
			dialog.text = "Ich werde jemandem wie dir nichts sagen. Du hältst dich für so verdammt hoch! Mal sehen, ob du das nach unserer kleinen Pause hier wieder untermauern kannst.";
			link.l1 = "Schade. Du bist widerlich, aber ich hätte dich einfach auf einer anderen Insel absetzen können. Jetzt kann ich dich nur auf die andere Seite schicken.";
			link.l1.go = "PZ_KlemanLebren_11";
		break;
		
		case "PZ_KlemanLebren_11":
			pchar.questTemp.PZ.HeavyFrigateAbordage = true; // флаг - абордаж был
			
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PZ_Tichingitu_11":
			dialog.text = "Rufen Sie mich, Kapitän?";
			link.l1 = "Ja, Kamerad. Bericht über den Schaden.";
			link.l1.go = "PZ_Tichingitu_12";
		break;
		
		case "PZ_Tichingitu_12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "There's a violent storm. The ship is creaking and cracking; it's wobbling badly.";
			link.l1 = "Ja, das habe ich bemerkt. Tichingitu, mein Freund. Ich und der "+sStr+" wird an Land gehen. Du bleibst in Verantwortung. Beginne sofort mit den Reparaturen - bis der Sturm nachlässt, ist es sinnlos, zur Werft zu gehen. Außerdem werden wir nicht lange hier sein.";
			link.l1.go = "PZ_Tichingitu_13";
		break;
		
		case "PZ_Tichingitu_13":
			dialog.text = "Ich werde alles besser aussehen lassen.";
			link.l1 = "Gut, danke. Dann gehen wir ohne Sorgen in die Stadt.";
			link.l1.go = "PZ_Tichingitu_14";
		break;
		
		case "PZ_Tichingitu_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_Matros_1":
			dialog.text = "Mein Herr Kapitän? Es ist eine Ehre. Aber normalerweise wenden Sie sich in solchen Zeiten an Alonso. Ist alles in Ordnung, wenn ich fragen darf?";
			link.l1 = "Ja, alles ist in Ordnung. Aber unser Alonso ist mehr für die Zerstörung, er repariert nichts. In jeder Hinsicht. Wie schlimm ist das Schiff?";
			link.l1.go = "PZ_Matros_2";
		break;
		
		case "PZ_Matros_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Alonso würde Ihnen sagen, dass es miserabel ist, auch wenn wir nicht untergehen. Sie haben Reparaturen erwähnt - sollen wir sie beginnen?";
			link.l1 = "Ja, tun Sie, was Sie können. Aber planen Sie keine umfangreiche langfristige Arbeit - wir werden bald den Anker lichten, gleich nachdem ich meine Geschäfte in der Stadt erledigt habe. Ich und "+sStr+" wird nicht da sein, also triff im Falle eines Falles alle Entscheidungen selbst. Hör in allem auf Alonso.";
			link.l1.go = "PZ_Matros_3";
		break;
		
		case "PZ_Matros_3":
			dialog.text = "Wie Sie befehlen, Herr Kapitän.";
			link.l1 = "Ruhig.";
			link.l1.go = "PZ_Matros_4";
		break;
		
		case "PZ_Matros_4":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			bQuestDisableMapEnter = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "PZ_PoP_Rain_4", -1);
		break;
		
		case "PZ_AnriTibo_1":
			dialog.text = "Grüße, Monsieur! Willkommen in Port-au-Prince.";
			link.l1 = "Und einen guten Tag wünsche ich Ihnen, Monsieur. Wer sind Sie und wem verdanke ich diesen Empfang? Ich würde nicht sagen, dass ich bei diesem Regen und nach einem Sturm für ein langes Gespräch aufgelegt bin.";
			link.l1.go = "PZ_AnriTibo_2";
			
			sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_ChangShin", "Mei_Shin", "woman", "towngirl2", 30, FRANCE, 0, false, "quest"));
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_41", "", "", 0);
			sld.name = "Чанг";
			sld.lastname = "Шин";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto16");
			EquipCharacterByItem(sld, "blade_41");
			GiveItem2Character(sld, "cirass8");
			EquipCharacterByItem(sld, "cirass8");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload8_back", "none", "", "", "", -1);
		break;
		
		case "PZ_AnriTibo_2":
			dialog.text = "Oh, ich werde nicht viel Ihrer Zeit in Anspruch nehmen, Monsieur de Maure.";
			link.l1 = "Kenne ich Sie?";
			link.l1.go = "PZ_AnriTibo_3";
		break;
		
		case "PZ_AnriTibo_3":
			dialog.text = "Oh, nein, aber der ganze Archipel weiß, wer Sie sind. Ah, wo sind meine Manieren! Henri Thibaut, zu Ihren Diensten. Ich bin der Bote Seiner Exzellenz, Monsieur de Mussac. Sobald er Ihr Schiff entdeckt hat, hat er mir befohlen, Ihnen den herzlichsten Empfang zu bereiten, monsieur.";
			link.l1 = "Nun, das erklärt einiges. Freut mich, Sie kennenzulernen, Monsieur Thibaut.";
			link.l1.go = "PZ_AnriTibo_4";
		break;
		
		case "PZ_AnriTibo_4":
			dialog.text = "Und das Vergnügen ist gegenseitig, Monsieur de Maure! Bitte folgen Sie mir. Es ist nicht richtig, dass ein Mann Ihrer Statur und seine schöne Begleiterin auf diese stinkende Taverne beschränkt sind. Seine Herrlichkeit hat Ihnen ein Haus in der Stadt zugeteilt und mich beauftragt, Ihnen in jeder Hinsicht zu helfen. Vergessen Sie bitte nicht, Seine Exzellenz Poincy danach seine besten Wünsche zu übermitteln.";
			link.l1 = "Eigentlich ist mein Auftrag ein diskreter. Wissen Sie, Monsieur Thibaut, ich glaube, dass...";
			link.l1.go = "PZ_AnriTibo_5";
		break;
		
		case "PZ_AnriTibo_5":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_HelenaPortPax1", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_MaryPortPax1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_HelenaPortPax1":
			dialog.text = "Charles. Ich bitte dich selten um etwas, und erst recht nicht, dich zu unterbrechen, aber können wir ihr Angebot annehmen? Ich habe es satt, im Regen nass zu werden. Mir ist auch übel und schwindelig.";
			link.l1 = "Heh-heh, bist du sicher, dass es der Regen ist?";
			link.l1.go = "PZ_HelenaPortPax2";
		break;
		
		case "PZ_HelenaPortPax2":
			dialog.text = "Beiß dir auf die Zunge, Charles! Wie auch immer, ich will mich ausruhen. Auf einem großen Bett und ohne Wellen.";
			link.l1 = "In Ordnung. Wir werden uns abtrocknen, eine Pause einlegen und dann gleich wieder zur Sache kommen.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_MaryPortPax1":
			dialog.text = "Können wir in diesem Haus eine Pause einlegen? Mir geht es nicht gut und ich bin auch... müde, Charles. Ja, gell.";
			link.l1 = "Mary, Liebste, ich verstehe, aber vielleicht sollten wir zur Taverne gehen. Das Ganze riecht übel, nicht wahr?";
			link.l1.go = "PZ_MaryPortPax2";
		break;
		
		case "PZ_MaryPortPax2":
			dialog.text = "Was könnte mir schon passieren? Das ist nicht einmal Tortuga.";
			link.l1 = "Das ist es, was mir Angst macht.";
			link.l1.go = "PZ_MaryPortPax3";
		break;
		
		case "PZ_MaryPortPax3":
			dialog.text = "Bitte? Wenn schon, dann richte ich eine Verteidigung im Zimmer ein - genau wie... damals, ja, gell. Du kennst mich besser als jeder andere, Charles, also weißt du, dass ich damit umgehen kann.";
			link.l1 = "In Ordnung, in Ordnung. Hoffentlich wird es nicht wie damals sein.";
			link.l1.go = "PZ_AnriTibo_6";
		break;
		
		case "PZ_AnriTibo_6":
			StartInstantDialog("Tibo", "PZ_AnriTibo_7", "Quest\CompanionQuests\Longway.c");
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		break;
		
		case "PZ_AnriTibo_7":
			dialog.text = "Ich wusste, dass Sie Ihre Meinung ändern würden, Monsieur! Was Ihre Sorgen angeht, verstehe ich vollkommen. Aber sehen Sie, Seine Exzellenz Poincy und der Gouverneur sind alte Freunde und daher sind Sie ein willkommener Gast in unserer Stadt, Monsieur de Maure!";
			link.l1 = "Oh, also... Na dann, bring uns zum Haus.";
			link.l1.go = "PZ_AnriTibo_8";
		break;
		
		case "PZ_AnriTibo_8":
			dialog.text = "Sicherlich, Monsieur! Folgen Sie mir bitte.";
			link.l1 = "Danke.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_GoToTiboHouse");
		break;
		
		case "PZ_AnriTibo_9":
			dialog.text = "Mein Herr, der Gouverneur erwartet Sie. Er hat Sie gebeten, so schnell wie möglich zu ihm zu kommen - er möchte mit Ihnen unter vier Augen sprechen.";
			link.l1 = "Weiß er das schon?";
			link.l1.go = "PZ_AnriTibo_10";
		break;
		
		case "PZ_AnriTibo_10":
			pchar.questTemp.PZ.PortPaxMayorTalk = true; // флаг для разговора с губернатором
			
			dialog.text = "Natürlich weiß er das! Deshalb wartet er auf dich. Lass deine Geliebte süß schlafen, während du Monsieur de Mussac besuchst. Ein Sturm wird den berühmten Charles de Maure nicht aufhalten, oder? Aber Seine Lordschaft, wie du verstehst, hat zwischen den Terminen nicht viel Zeit...";
			link.l1 = "Nun, das ist wahr, Monsieur Thibaut.";
			link.l1.go = "PZ_AnriTibo_11";
			
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("PZ_PoP_Escort_"+i, "sold_fra_"+(rand(7)+1), "man", "man", sti(pchar.rank), FRANCE, -1, true, "soldier"));
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
		break;
		
		case "PZ_AnriTibo_11":
			StartInstantDialog("PZ_PoP_Escort_1", "PZ_AnriTibo_12", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_AnriTibo_12":
			dialog.text = "Wir zeigen Ihnen den Weg, Kapitän.";
			link.l1 = "Oh, also habe ich sogar eine Ehreneskorte... Nun denn, führen Sie den Weg.";
			link.l1.go = "PZ_AnriTibo_13";
		break;
		
		case "PZ_AnriTibo_13":
			DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "PZ_PoP_EscortToGuber");
		break;
		
		case "PZ_Longway_71":
			dialog.text = "Herr Kapitän!";
			link.l1 = "Longway! Zum Schiff! Jetzt!";
			link.l1.go = "PZ_Longway_72";
		break;
		
		case "PZ_Longway_72":
			dialog.text = "Aber ich habe Chang Xing gesehen!";
			link.l1 = "Was?! Wo? Wann? Ist sie auf Ihrem Schiff?";
			link.l1.go = "PZ_Longway_73";
		break;
		
		case "PZ_Longway_73":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Nein! Hier in der Stadt hat Longway sie aus der Ferne gesehen. Keine Zeit nachzukommen - sie geht an Bord eines Galeons, das gerade in See gestochen ist!";
			link.l1 = "Wir werden die Galeone einholen! Aber sag mir - hast du gesehen "+sStr+" irgendwo?";
			link.l1.go = "PZ_Longway_74";
		break;
		
		case "PZ_Longway_74":
			dialog.text = "Nein! Ist etwas passiert?";
			link.l1 = "Ja, etwas ist passiert! Sie ist in Gefahr! Haben Sie Levasseurs Neffen gesehen? Er heißt Henri Thibaut! Ein widerlicher, dünner, langhaariger junger Mann mit einem merkwürdigen Schnurrbart!";
			link.l1.go = "PZ_Longway_75";
		break;
		
		case "PZ_Longway_75":
			dialog.text = "(auf Mandarin) Sie müssen nicht über lustige Schnurrbärte sprechen, Kapitän... (in gebrochenem Französisch) Ich habe ihn gesehen! Er und die Söldner sind auch auf die gleiche Galeone gestiegen.";
			link.l1 = "Lassen Sie uns sofort die Verfolgung aufnehmen!";
			link.l1.go = "PZ_Longway_76";
		break;
		
		case "PZ_Longway_76":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ihr Schiff ist stark abgenutzt, Herr Kapitän!";
			link.l1 = "Es ist mir egal! "+sStr+"'s Leben steht auf dem Spiel!";
			link.l1.go = "PZ_Longway_77";
		break;
		
		case "PZ_Longway_77":
			if (CheckAttribute(pchar, "questTemp.PZ.LongwayMayfang"))
			{
				dialog.text = "Mein... 'Deine Meifeng' wird uns durchbringen!";
				link.l1 = "Ach, sie wird es tun! Beeil dich!";
				link.l1.go = "PZ_Longway_78";
			}
			else
			{
				dialog.text = "Stürzen Sie uns nicht in einen selbstmörderischen Angriff. Benutzen Sie das Schiff, das Sie mir früher gegeben haben!";
				link.l1 = "Gute Idee, Longway! Lass uns beeilen!";
				link.l1.go = "PZ_Longway_78";
			}
		break;
		
		case "PZ_Longway_78":
			DialogExit();
			chrDisableReloadToLocation = false;
			Island_SetReloadEnableGlobal("Hispaniola2", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
			SetCurrentTime(15, 00);
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
			pchar.GenQuest.AbordageInStorm = true;	//Разрешить абордаж во время шторма
			SetLocationCapturedState("PortPax_town", false);

			LAi_LoginInCaptureTown(npchar, false);
			AddPassenger(pchar, npchar, false);
			Return_LongwayOfficer();
			
			if (GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				AddPassenger(pchar, sld, false);
				Return_TichingituOfficer();
			}
			
			PChar.quest.PZ_PoP_Pogonya.win_condition.l1 = "location";
			PChar.quest.PZ_PoP_Pogonya.win_condition.l1.location = "Hispaniola2";
			PChar.quest.PZ_PoP_Pogonya.win_condition = "PZ_PoP_Pogonya";
			
			SeaAI_SwapShipsAttributes(pchar, CharacterFromID("PZ_ShipStasis"));
			AddCharacterGoodsSimple(pchar, GOOD_GRAPES, 300);
			AddCharacterGoodsSimple(pchar, GOOD_BOMBS, 200);
			AddCharacterGoodsSimple(pchar, GOOD_POWDER, 350);
			AddCharacterGoodsSimple(pchar, GOOD_FOOD, 150);
			AddCharacterGoodsSimple(pchar, GOOD_RUM, 50);
			AddCharacterGoodsSimple(pchar, GOOD_FOOD, 700);
			SetCrewQuantityFull(pchar);
			pchar.ship.HP = sti(pchar.ship.HP) / 2;
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) / 2;
			AddCrewMorale(Pchar, 100);
			ChangeCrewExp(pchar, "Sailors", 100);
			ChangeCrewExp(pchar, "Cannoners", 100);
			ChangeCrewExp(pchar, "Soldiers", 100);
			
			//Вражина
			sld = characterFromId("PZ_RobertMartin");
			sld.nation = PIRATE;
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				GiveItem2Character(sld, "blade_31");
				EquipCharacterByItem(sld, "blade_31");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				GiveItem2Character(sld, "pirate_cutlass");
				EquipCharacterByItem(sld, "pirate_cutlass");
			}
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS16, 50, 50, 50);
			sld.AlwaysEnemy = true;
			sld.AlwaysSandbankManeuver = true;
			sld.DontRansackCaptain = true;
			sld.ShipHideImmortal = 800;
			Group_FindOrCreateGroup("PZ_RM_Attack");
			Group_SetType("PZ_RM_Attack", "pirate");
			Group_AddCharacter("PZ_RM_Attack", "PZ_RobertMartin");
			Group_SetGroupCommander("PZ_RM_Attack", "PZ_RobertMartin");
			Group_SetTaskAttack("PZ_RM_Attack", PLAYER_GROUP);
			Group_SetAddress("PZ_RM_Attack", "Hispaniola2", "quest_ships", "Quest_ship_1");
			Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), sti(pchar.index));
		break;
		
		case "PZ_RobertMartin_8":
			dialog.text = "Du schon wieder... Ich wusste, ich hätte ablehnen und jemand anderen dein Mädchen nehmen lassen sollen.";
			link.l1 = "Wo ist sie?! Sag es mir! Nein... Halt den Mund. Du wirst nur im Frachtraum reden, in Fesseln! Hörst du mich?!";
			link.l1.go = "PZ_RobertMartin_9";
		break;
		
		case "PZ_RobertMartin_9":
			dialog.text = "..., Freund.";
			link.l1 = "Ihr Schwert. Wenn Sie nicht sofort anfangen zu singen, werde ich Sie damit in Stücke schneiden.";
			link.l1.go = "PZ_RobertMartin_10";
			/*RemoveAllCharacterItems(npchar, true);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) GiveItem2Character(pchar, "blade_31");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) GiveItem2Character(pchar, "pirate_cutlass");*/
		break;
		
		case "PZ_RobertMartin_10":
			dialog.text = "Du... du bist verdammt nochmal verrückt!..";
			link.l1 = "Nun wirst du meine unangenehme Seite kennen lernen...";
			link.l1.go = "PZ_RobertMartin_11";
		break;
		
		case "PZ_RobertMartin_11":
			DialogExit();
			LAi_ReloadBoarding();
		break;
		
		case "PZ_RobertMartin_13":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Das ist es?";
			link.l1 = "Ich frage dich noch einmal! Wo ist "+sStr+"?! Wo ist die chinesische Frau?! Wo ist Henri Thibaut?!";
			link.l1.go = "PZ_RobertMartin_14";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_14":
			dialog.text = "(spuckt Blut) Du schlägst wie ein Mädchen.";
			link.l1 = "Du Schlampe! Ich werde dir jedes Wort aus dem Leib prügeln!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_6");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_1", "", 0.3);
		break;
		
		case "PZ_RobertMartin_16":
			dialog.text = "Erbärmlich. Obwohl ... ich werde es sagen. Warum nicht, ha ha. Sie sind alle auf dem anderen Schiff, direkt auf dem Weg nach Tortuga. Sie sind zu spät.";
			link.l1 = "Wenn auch nur ein Haar von ihrem Kopf fällt...";
			link.l1.go = "PZ_RobertMartin_17";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_2", "", 0.3);
			locCameraFromToPos(0.27, 14.52, -3.38, true, -1.80, 9.90, -1.76);
		break;
		
		case "PZ_RobertMartin_17":
			dialog.text = "Und wessen Schuld ist das?! Du hast Edgardo Sotta getötet! Zum ersten Mal in seinem Leben wollte Levasseur eine Frau kosten und hat sie nicht sofort bekommen! Das erste Mal, dass unsere Mannschaft seinen direkten Befehl nicht befolgt hat! Der Mann kann so beängstigend sein wie der Teufel...";
			link.l1 = "Dann werde ich furchterregender sein als der Teufel selbst und dir eine kleine persönliche Hölle bereiten, wenn du mir nicht sagst, was ich wissen will, hörst du mich?!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) link.l1.go = "PZ_RobertMartin_Mary_1";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) link.l1.go = "PZ_RobertMartin_Helena_1";
		break;
		
		case "PZ_RobertMartin_Mary_1":
			dialog.text = "Mir ist egal, was deine Sorgen sind - ich bin sowieso ein toter Mann, wenn ich mir diese verrückten Augen von dir anschaue. Ich werde dir aber etwas anerkennen, de Maure.";
			link.l1 = "Wovon zum Teufel sprichst du?";
			link.l1.go = "PZ_RobertMartin_Mary_2";
		break;
		
		case "PZ_RobertMartin_Mary_2":
			dialog.text = "Levasseur bevorzugt Blondinen. Aber ich habe immer Rothaarige besser gemocht, genau wie du, hehehe... Was für eine scharfe du hast!";
			link.l1 = "Du hast recht, du wirst den Tag nicht überleben...";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_Helena_1":
			dialog.text = "Ich gebe einen Dreck darauf, was Sie wollen. Aber lassen Sie mich Ihnen sagen, was Levasseur will - hübsche blonde Mädchen, ha ha ha ha ha ha ha ha ha! Zuerst nimmt er sie...";
			link.l1 = "A-AH!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DoprosRobertMartin_Trum_7");
		break;
		
		case "PZ_RobertMartin_19":
			dialog.text = "Quietschen und einen unbewaffneten Mann schlagen - erbärmlich. Das ist alles, was du kannst. Du hast verloren, de Maure! Willst du wissen, wann du wirklich verloren hast, du erbärmlicher Trottel?";
			link.l1 = "Erklären Sie mir das. Aber wenn ich nicht beeindruckt bin, verlieren Sie einen Finger. Oder ein Ohr. Oder diese faulen Zähne aus Ihrem stinkenden Mund. Oder vielleicht etwas anderes. Die Wahl liegt bei Ihnen...";
			link.l1.go = "PZ_RobertMartin_20";
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "beatmarten_idle_3", "", 0.3);
			//locCameraFromToPos(-1.75, 14.14, -0.31, true, 1.26, 11.00, -4.00);
			locCameraFromToPos(-2.47, 14.15, -0.01, true, 1.23, 10.92, -3.60);
		break;
		
		case "PZ_RobertMartin_20":
			dialog.text = "Heh-heh, ich habe etwas, das du nicht hast. Glaubst du, Levasseur wusste nicht, was dieser alte Fuchs Poincy gegen ihn plante? Francois weiß alles, alles! Selbst die Barone der Bruderschaft wagen es nicht, ihn herauszufordern. Und du, Klugscheißer, du hast es getan. Aber...";
			link.l1 = "Aber was?! Fang bloß nicht an, das herauszuziehen!! Fang an zu reden, oder ich fange an, deine Finger einzeln zu brechen!";
			link.l1.go = "PZ_RobertMartin_21";
		break;
		
		case "PZ_RobertMartin_21":
			dialog.text = "Ha-ha, tapferer Kapitän de Maure! Aber gut. Ich, Henri und die gelbhäutige Frau haben beschlossen, dass es am besten wäre, dich hier zu vernichten. Und es Tyrex in die Schuhe zu schieben, sodass die alten Narren in der Bruderschaft einen weiteren Krieg untereinander beginnen! Oder vielleicht de Mussac - er hat seine Nase dort hineingesteckt, wo sie nicht hingehört... Weißt du, alle haben mich ausgelacht, weil ich eine Galeone segelte, aber sie hat den Sturm mit Leichtigkeit überstanden, im Gegensatz zu deinem Stück Schrott.";
			link.l1 = "Genug! Wo hält Levasseur seine Opfer fest?";
			link.l1.go = "PZ_RobertMartin_22";
		break;
		
		case "PZ_RobertMartin_22":
			dialog.text = "Also wissen Sie von seinem geheimen Ort, dem Verlies? Oh ja, er ist der echte Verliesmeister, ha-ha-ha! Aber können Sie ihn wirklich herausfordern? Ich bezweifle es. Sie wollen das Biest besiegen? Dann werden Sie selbst zum Biest. Sehen Sie, ob Sie mich brechen können, wie Francois diese Mädchen bricht. Wie er bald Ihre brechen wird...";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "Alo-o-o-ns-o-o!!! ";
				link.l1.go = "PZ_RobertMartin_23";
			}
			else
			{
				link.l1 = "..., Freund.";
				link.l1.go = "PZ_LongwayKaznDialog_1";
			}
		break;
		
		case "PZ_RobertMartin_23":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_Fade("PZ_AlonsoKazn", "");
		break;
		
		case "PZ_LongwayKaznDialog_1":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			DoQuestCheckDelay("PZ_LongwayKazn_1", 1.0);
		break;
		
		case "PZ_LongwayKaznDialog_2":
			dialog.text = "";
			link.l1 = "Ich habe dir gesagt, du sollst dich nicht bemühen, verdammt!..";
			link.l1.go = "PZ_LongwayKaznDialog_3";
		break;
		
		case "PZ_LongwayKaznDialog_3":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_Fade("PZ_LongwayKazn_3", "");
		break;
		
		case "PZ_LongwayKaznDialog_4":
			dialog.text = "Erlauben Sie mir, Herr Kapitän.";
			link.l1 = "Longway? Erlauben Sie was?";
			link.l1.go = "PZ_LongwayKaznDialog_5";
		break;
		
		case "PZ_LongwayKaznDialog_5":
			dialog.text = "Die Weißen quälen den Körper. Mein Volk weiß, dass man zuerst eine elende Seele quälen muss, verrückt vor kleinem, ständigem Schmerz. Man kann nicht einfach nehmen und quälen ohne Vorbereitung. Es braucht immer einen besonderen Ansatz. Hier brauchst du... Lynchy.";
			link.l1 = "Lynchy?";
			link.l1.go = "PZ_LongwayKaznDialog_6";
		break;
		
		case "PZ_LongwayKaznDialog_6":
			dialog.text = "Ja, Herr Kapitän. Tod durch tausend Schnitte.";
			link.l1 = "Bist du verrückt?! Hast du dir den Kopf gestoßen? Wovon faselst du da von Tod?! Ich muss ihn erst zum Reden bringen!";
			link.l1.go = "PZ_LongwayKaznDialog_7";
		break;
		
		case "PZ_LongwayKaznDialog_7":
			dialog.text = "Longway weiß, Herr Kapitän. Er weiß, was zu tun ist. Dieser Bastard wird mir alles erzählen. Gib mir Zeit...";
			link.l1 = "Zeit? Zeit?! In Ordnung... Mach es. Aber bitte, ich flehe dich an, hol alles aus ihm heraus, alles!";
			link.l1.go = "PZ_LongwayKaznDialog_8";
		break;
		
		case "PZ_LongwayKaznDialog_8":
			DialogExit();
			LAi_SetActorType(npchar);
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_SetStayType(pchar);
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_LongwayKazn_4", 1.5);
		break;
		
		case "PZ_LongwayKaznDialog_9":
			dialog.text = "Töte mich, töte mich einfach, bitte... Was willst du noch von mir?!";
			link.l1 = "Nichts mehr. Halte dein Maul und stirb.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayKazn_11");
		break;//
		
		case "PZ_LongwayKaznDialog_9_1":
			DialogExit();
			sld = CharacterFromID("PZ_RobertMartinPlennik")
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Shot", "1", 1.5);
			DoQuestCheckDelay("PZ_LongwayKazn_9", 0.9);
		break;
		
		case "PZ_LongwayKaznDialog_11":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Saubere Schuss, Mein Herr Kapitän. Ich habe Ihnen gesagt, dass es funktionieren würde.";
			link.l1 = "Ja. Gute Arbeit. Also, ab zum Verlies. Alle Segel hissen! Kurs auf Tortuga. Und Gott helfe dieser verdammten Stadt, wenn auch nur ein einziges Haar von "+sStr+" Kopf...";
			link.l1.go = "PZ_LongwayKaznDialog_12";
		break;
		
		case "PZ_LongwayKaznDialog_12":
			DialogExit();
			ResetSound();
			chrDisableReloadToLocation = false;
			EndQuestMovie();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			locCameraTarget(PChar);
			locCameraFollow();
			AddQuestRecord("PZ", "39");
			
			LAi_SetPlayerType(pchar);
			npchar.greeting = "Longway";
			Return_LongwayOfficer();
			
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_2", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_3", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_3", true);
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", false);
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			DeleteAttribute(pchar, "GenQuest.AbordageInStorm");
			
			PChar.quest.PZ_Etap6_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Etap6_Start.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_Etap6_Start.win_condition = "PZ_Etap6_Start";
			locations[FindLocation("Shore58")].DisableEncounters = true;
			SetTimerCondition("PZ_Etap6_Opozdal", 0, 0, 7, false);
			DelMapQuestMarkCity("PortPax");
			AddMapQuestMarkShore("Shore58", true);
			pchar.questTemp.PZ_FlagMartinInfo = true;
			
			// Компаньон-заглушка входит в состав нашей экскадры
			sld = CharacterFromID("PZ_ShipStasis");
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetCharacterRemovable(sld, true);
			SetShipRemovable(sld, true);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.ship.HP = sti(sld.ship.HP) / 2;
			
			//
			makearef(arTmp, pchar.questTemp.PZ_PoP_More.ShipPos);
			QuestToSeaLogin_Prepare(stf(arTmp.x), stf(arTmp.z), arTmp.Island);
			DeleteAttribute(pchar, "questTemp.PZ_PoP_More.ShipPos");
			QuestToSeaLogin_Launch();
		break;
		
		case "PZ_AlonsoKaznDialog_1":
			dialog.text = "Mein Gott... Ich habe Sie noch nie so gesehen oder gehört, Herr Kapitän.";
			link.l1 = "Er gehört ganz dir, Alonso! Geh voran, zeig mir, was die Heilige Inquisition mit Hugenotten und ihren Lakaien macht... Und ich werde zusehen... Dann kannst du mit ihm machen, was du willst.";
			link.l1.go = "PZ_AlonsoKaznDialog_2";
		break;
		
		case "PZ_AlonsoKaznDialog_2":
			dialog.text = "Aye aye, senor Kapitän...";
			link.l1 = "";
			link.l1.go = "PZ_AlonsoKaznDialog_3";
		break;
		
		case "PZ_AlonsoKaznDialog_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, CharacterFromID("PZ_RobertMartinPlennik"), "PZ_AlonsoKazn_2", -1);
		break;
		
		case "PZ_AlonsoKaznDialog_4":
			dialog.text = "Es wird nicht lange dauern, Herr Kapitän...";
			link.l1 = "Mach es, um Himmels willen!";
			link.l1.go = "PZ_AlonsoKaznDialog_5";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			LAi_ActorAnimation(npchar, "Barman_idle", "1", 5);
		break;
		
		case "PZ_AlonsoKaznDialog_5":
			DialogExit();
			LAi_SetStayType(pchar);
			LAi_FadeToBlackStart();
			DoQuestCheckDelay("PZ_AlonsoKazn_3", 1.5);
		break;
		
		case "PZ_AlonsoKaznDialog_6":
			dialog.text = "Steh auf, du Stück Scheiße. Steh auf, habe ich gesagt!";
			link.l1 = "Ist er tot? Tot?!";
			link.l1.go = "PZ_AlonsoKaznDialog_7";
			CharacterTurnByChr(npchar, CharacterFromID("PZ_RobertMartinPlennik"));
			CharacterTurnByChr(pchar, CharacterFromID("PZ_RobertMartinPlennik"));
		break;
		
		case "PZ_AlonsoKaznDialog_7":
			dialog.text = "Sieht so aus, Kap...";
			link.l1 = "Was zum Teufel hast du getan?!";
			link.l1.go = "PZ_AlonsoKaznDialog_8";
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
		break;
		
		case "PZ_AlonsoKaznDialog_8":
			dialog.text = "Wer hätte gedacht, dass dieser Tölpel sich als solch ein Schwächling entpuppen würde! Er hat auch seine Unterhosen beschmutzt, der dreckige Abschaum! Verdammt, das Feuer war unnötig...";
			link.l1 = "Du... Nun, werft ihn den Fischen zum Fraß vor. Setzt Kurs auf Tortuga. Wenn es sein muss, nehme ich sie Stein für Stein auseinander - zuerst La Roche, dann... Dann möge Gott mir helfen, wenn ich sie nicht lebendig finde...";
			link.l1.go = "PZ_AlonsoKaznDialog_9";
		break;
		
		case "PZ_AlonsoKaznDialog_9":
			DialogExit();
			ResetSound();
			chrDisableReloadToLocation = false;
			EndQuestMovie();
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			locCameraTarget(PChar);
			locCameraFollow();
			AddQuestRecord("PZ", "38");
			
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.lifeday = 0;
			npchar.location = "None";
			
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_2", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_2", true);
			Island_SetReloadEnableLocal("Hispaniola2", "reload_3", true)
			Island_SetGotoEnableLocal("Hispaniola2", "reload_3", true);
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			DeleteAttribute(pchar,"questTemp.TimeLock");
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", false);
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			DeleteAttribute(pchar, "GenQuest.AbordageInStorm");
			
			PChar.quest.PZ_Etap6_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Etap6_Start.win_condition.l1.location = "Tortuga";
			PChar.quest.PZ_Etap6_Start.win_condition = "PZ_Etap6_Start";
			locations[FindLocation("Shore58")].DisableEncounters = true;
			SetTimerCondition("PZ_Etap6_Opozdal", 0, 0, 7, false);
			DelMapQuestMarkCity("PortPax");
			AddMapQuestMarkShore("Shore58", true);
			
			// Компаньон-заглушка входит в состав нашей экскадры
			sld = CharacterFromID("PZ_ShipStasis");
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetCharacterRemovable(sld, true);
			SetShipRemovable(sld, true);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			sld.Dialog.CurrentNode = "hired";
			sld.Payment = true;
			sld.ship.HP = sti(sld.ship.HP) / 2;
			
			//
			makearef(arTmp, pchar.questTemp.PZ_PoP_More.ShipPos);
			QuestToSeaLogin_Prepare(stf(arTmp.x), stf(arTmp.z), arTmp.Island);
			DeleteAttribute(pchar, "questTemp.PZ_PoP_More.ShipPos");
			QuestToSeaLogin_Launch();
		break;
		
		case "PZ_Norman1":
			dialog.text = "Endlich. Dieser Thron gehört jetzt mir. Auf diesem Felsen werde ich bauen...";
			link.l1 = "Was zum Teufel... Ernsthaft?";
			link.l1.go = "PZ_Norman2";
		break;
		
		case "PZ_Norman2":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Shark";
			
			dialog.text = "... meine Kirche. Ich bin jetzt der Papst von Rom. Schwöre nicht im Hause Gottes!";
			link.l1 = "Und hier dachte ich... Nun, Eure Heiligkeit, würden Sie bitte Ihren Gläubigen sagen, wo der "+sTemp+" ist jetzt?";
			link.l1.go = "PZ_Norman3";
		break;
		
		case "PZ_Norman3":
			dialog.text = "Er ist auf einer heiligen Quest. Eine neue Kreuzzug, wenn man so will. Er wird das Geld von den Bösen nehmen und es mir bringen.";
			link.l1 = "An Sie, richtig. Hat er erwähnt, wann er zurück sein wird?";
			link.l1.go = "PZ_Norman4";
		break;
		
		case "PZ_Norman4":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "In einem Monat. Vielleicht etwas später. Ich warte auf seine Rückkehr, zusammen mit dem Rest unserer Herde.";
			link.l1 = "So ist er wirklich auf See. Ich sollte besser gehen, bevor ich mich mit dem anstecke, was auch immer du hast.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_NormanBlock":
			NextDiag.TempNode = "PZ_NormanBlock";
			
			dialog.text = "Ich werde sie alle in den heiligen Flammen reinigen...";
			link.l1 = "Dein Kopf könnte eine Reinigung gebrauchen...";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoro1":
			if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
			{
				// ох, какой же костыль, м-м-мать...
				sld = characterFromId("Mary");
				if (sld.location != "Pirates_townhall")
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "with Marcus";
					else sTemp = "with Steve";
					
					dialog.text = "Charles! Was kann ich für dich tun?";
					link.l1 = "Hallo, Helen! Ich möchte mit dir reden "+sTemp+". Ist er oben? Oder ist er in der Taverne?";
					link.l1.go = "PZ_HelenaIslaTesoroGood1";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
					else sTemp = "Steve";
					
					dialog.text = "Charles! Und ... Ach, was für eine schöne Überraschung. Was kann ich für euch beide tun?";
					link.l1 = "Hallo, Helen. Wo ist "+sTemp+"?";
					link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere1";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
				else sTemp = "Shark";
				
				dialog.text = TimeGreeting()+", Charles. Was bringt dich hierher?";
				link.l1 = TimeGreeting()+", Helen. Ich suche nach der "+sTemp+". Wissen Sie, wo er ist?";
				link.l1.go = "PZ_HelenaIslaTesoroBad1";
			}
		break;
		
		case "PZ_HelenaIslaTesoroGood1":
			dialog.text = "Er ist weg, aber ich fürchte, er ist lange weg - genau gesagt auf See.";
			link.l1 = "Verdammt. Ist etwas passiert? Hat er gesagt, wann er zurück sein wird?";
			link.l1.go = "PZ_HelenaIslaTesoroGood2";
		break;
		
		case "PZ_HelenaIslaTesoroGood2":
			dialog.text = "Er hat nicht, aber es ist nichts Ernstes - er hat wie gewöhnlich einen guten Vorsprung. Er kehrt normalerweise in einem Monat, höchstens zwei zurück. Ich weiß, wie es ist, manchmal vermisse ich das Schiffsdeck selbst...";
			link.l1 = "Sie können immer auf See gehen. Es wäre schön, dies irgendwann gemeinsam zu tun - Sie auf der 'Rainbow', ich auf dem...";
			link.l1.go = "PZ_HelenaIslaTesoroGood3";
		break;
		
		case "PZ_HelenaIslaTesoroGood3":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			dialog.text = "Das wäre es. Aber deine... Freundin könnte es nicht schätzen. Und ich möchte nicht das fünfte Rad am Wagen sein.";
			link.l1 = "Ähem, entschuldige, Helen, ich wollte dich nicht beleidigen. Danke für den Plausch. Bis später.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steve";
			
			dialog.text = "Charles, du bist zurück. Kann ich dir noch mit etwas anderem helfen?";
			link.l1 = "Nein, danke, Helen. Ich wollte nur überprüfen, ob "+sTemp+" tauchte auf.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroBad1":
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			else sTemp = "Steven";
			
			dialog.text = "Ich wäre überrascht, wenn du mich suchen würdest. Was betrifft "+sTemp+", er ist auf See.";
			link.l1 = "Ach wirklich? Hat er dir gesagt, wann er zurück sein wird?";
			link.l1.go = "PZ_HelenaIslaTesoroBad2";
		break;
		
		case "PZ_HelenaIslaTesoroBad2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			dialog.text = "Anscheinend hat er es satt, diese Kloake zu führen und muss sich daran erinnern, dass er immer noch Kapitän eines Schiffes ist. Nicht das erste Mal. Er kehrt normalerweise in einem Monat, vielleicht anderthalb Monaten zurück.";
			link.l1 = "Verdammt, also sitzen die Barone nicht immer so still da? Danke, Helen. Auf Wiedersehen.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroBadBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroBadBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "Steven";
			
			dialog.text = ""+sTemp+"'s ist immer noch nicht zurück, Charles";
			link.l1 = "Ich sehe, nur zur Überprüfung.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere1":
			dialog.text = "Er ist ein freier Mann, nicht wahr? Er kann zur See gehen, wann immer er will.";
			link.l1 = "Natürlich kann er das. Also, wo ist er?";
			link.l1.go = "PZ_HelenaIslaTesoroGoodMaryHere2";
		break;
		
		case "PZ_HelenaIslaTesoroGoodMaryHere2":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus";
			else sTemp = "the Shark";
			
			dialog.text = "Aber Charles, wenn er nicht auf der Insel ist, dann ist er gegangen, um die Spanier zu plündern. Und jetzt, wenn Sie mich entschuldigen, habe ich viel zu tun. Schauen Sie von Zeit zu Zeit vorbei - normalerweise, der "+sTemp+"kommt in etwa einem Monat zurück, manchmal ein wenig später.";
			link.l1 = "Gut, Helen, danke. Wir werden beschäftigt bleiben.";
			link.l1.go = "Exit";
		break;
		
		// Синистра, не забудь снять эту заглушку и вернуть дефолтную после этого этапа, плиз
		case "PZ_HelenaIslaTesoroGoodMaryHereBlock":
			NextDiag.TempNode = "PZ_HelenaIslaTesoroGoodMaryHereBlock";
			
			dialog.text = "Ich bin gerade nicht in Stimmung. Vielleicht kommst du ein anderes Mal zurück, Charles?";
			link.l1 = "Sicher, Helen. Entschuldigung für die Störung. Pass auf dich auf.";
			link.l1.go = "Exit";
		break;
		
		case "PZ_Longway_81":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				dialog.text = "Wir sind in Position, Herr Kapitän. Erinnern Sie sich an den Weg?";
				link.l1 = "Natürlich, Longway. Lassen wir nur hoffen, dass wir es nicht in diesem verfluchten Verlies verlieren...";
				link.l1.go = "PZ_Longway_FlagMartinInfo_1";		//Sinistra
			}
			else
			{
				dialog.text = "Wir sind in Position, Herr Kapitän. Haben Sie einen Plan?";
				link.l1 = "Ich arbeite noch daran... Warum, haben Sie etwas im Kopf?";
				link.l1.go = "PZ_Longway_NotMartinInfo_1";		//Rebbebion
			}
			DelLandQuestMark(npchar);
			LAi_SetCheckMinHP(npchar, 1, true, "");		//На 6 эпизод даём Лонгвею бессмертие
			
			LocatorReloadEnterDisable("Tortuga_town", "houseS4", false);
		break;
		
		case "PZ_Longway_NotMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Nun, ich denke, wenn wir uns zu Chang Xing beeilen...";
			link.l1 = "Longway... Ich verstehe, wie sehr du deine Schwester sehen möchtest, aber "+sStr+" ist gerade in tödlicher Gefahr, und das ist keine bloße Redewendung! Sie müssen verstehen, dass es oberste Priorität ist, sie zu retten!";
			link.l1.go = "PZ_Longway_NotMartinInfo_2";
		break;
		
		case "PZ_Longway_NotMartinInfo_2":
			dialog.text = "Herr Kapitän, ich bezweifle, dass Sie wirklich verstehen, was ich all diese zehn Jahre durchgemacht habe. Was ich gerade durchmache.";
			link.l1 = "Weißt du, irgendwie schon. Mein Bruder wird im Gefängnis festgehalten. Und obwohl sie ihm noch nichts angetan haben, könnten sie jederzeit mit ihm machen, was sie wollen.";
			link.l1.go = "PZ_Longway_NotMartinInfo_3";
		break;
		
		case "PZ_Longway_NotMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Aber wohin würdest du gehen, wenn es nur um die Dame ginge "+sStr+" wer brauchte Rettung?";
			if (CheckAttribute(pchar, "questTemp.FMQT.GiveDiamonds") && !CheckAttribute(pchar, "questTemp.FMQT_ObchistilSunduk"))
			{
				link.l1 = "Es gibt einen Ort... eine Person... Aber kümmere dich nicht darum, Longway - das muss ich selbst in die Hand nehmen.";
				link.l1.go = "PZ_GoMarceline1";
			}
			link.l2 = "Ehrlich gesagt, ich weiß nicht einmal, wohin ich gehen soll. Wenn ich überall unvorsichtig herumschnüffle, ziehe ich Aufmerksamkeit auf mich und dann "+sStr+" ist definitiv erledigt. Also... Ich weiß einfach nicht.";
			link.l2.go = "PZ_GoTogether1";
		break;
		
		case "PZ_GoMarceline1":
			dialog.text = "Was? Warum?";
			link.l1 = "Sie lassen Sie dort nicht einfach rein - das ist die hohe Gesellschaft, verdammt noch mal. Also, ich gehe allein. In der Zwischenzeit, Sie gehen zu Ihrer Schwester. Ich werde mich Ihnen so schnell wie möglich anschließen. Viel Glück, Longway!";
			link.l1.go = "PZ_GoMarceline2";
			RemovePassenger(pchar, npchar);
		break;
		
		case "PZ_GoMarceline2":
			dialog.text = "Aye! Danke, Herr Kapitän. Und auch Ihnen viel Glück!";
			link.l1 = "Oh, danke - Ich brauche es heute dringend. Wir alle tun es.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineLongwayGo");
		break;
		
		case "PZ_GoTogether1":
			dialog.text = "Mein Herr Kapitän...";
			link.l1 = "Macht nichts. Gehen wir zu deiner Schwester, Longway. Wenn wir uns jetzt aufteilen - sind wir tot. Lassen uns zu deiner Schwester beeilen und herausfinden, wo sich Levasseurs Versteck befindet. Dann gehen wir wieder zusammen - ich brauche gerade jetzt jede Hilfe, die ich bekommen kann. Ich hoffe, wir sind nicht zu spät.";
			link.l1.go = "PZ_GoTogether2";
		break;
		
		case "PZ_GoTogether2":
			dialog.text = "Wir werden nicht zu spät kommen, Herr Kapitän. Lassen Sie uns nicht länger zögern oder Zeit mit Streitigkeiten verschwenden. Auf nach Chang Xing!";
			link.l1 = "Du hast recht, lass uns beeilen.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_FrenchSoldier1":
			dialog.text = "Wohin zum Teufel gehst du? Weißt du überhaupt, wohin diese Tür führt?";
			link.l1 = "Ich weiß es ganz genau. Ich gehe dorthin, um Geschäfte zu machen, nicht aus leerer Neugier oder um zu stehlen.";
			link.l1.go = "PZ_FrenchSoldier2";
		break;
		
		case "PZ_FrenchSoldier2":
			dialog.text = "Welches Geschäft? Madame Levasseur ist momentan nicht verfügbar. Außerdem ist sie eine verheiratete Frau - es ist nicht richtig, dass Leute um ihren Ort herumhängen.";
			link.l1 = "Verheiratet, ja, gell. Aber sie empfängt ab und zu, eh? Inklusive private Empfänge. Dies ist einer dieser Zeiten. Sie erwartet mich, und ich habe es eilig.";
			link.l1.go = "PZ_FrenchSoldier3";
		break;
		
		case "PZ_FrenchSoldier3":
			dialog.text = "Sie hätte mich gewarnt, wenn das der Fall wäre.";
			link.l1 = "Ich bin eine besondere Art von Gast - die Art, die keine Ankündigungen braucht.";
			link.l1.go = "PZ_FrenchSoldier4";
		break;
		
		case "PZ_FrenchSoldier4":
			dialog.text = "Aye, die Art von Gast, die Seine Lordschaft dazu bringt, mich erschießen zu lassen. Oder die Dame selbst wird mich häuten.";
			link.l1 = "Ich war schon einmal Gast bei Madame Marceline. Ich versichere Ihnen, Soldat, Ihnen wird danach nichts passieren.";
			link.l1.go = "PZ_FrenchSoldier5";
		break;
		
		case "PZ_FrenchSoldier5":
			dialog.text = "Aber natürlich, blind bleiben und jeden reinlassen - das ist die Aufgabe der Stadtwache.";
			link.l1 = "Ich habe keine Zeit für diesen Unsinn, du sturer Esel...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_FrenchSoldierFight");
		break;
		
		case "PZ_Marceline1":
			dialog.text = "Du...";
			// начинаем проверять результат прохождения "Почти как дома"
			switch (pchar.questTemp.FMQT.Marceline)
			{
				// поделили алмазы и "охладили трахание, углепластики" (с)
				case "Fuck":
					link.l1 = "Oh ja, gnädige Frau. Ihr Ritter freut sich, Sie wieder zu sehen. Ich sehe, Sie sind überrascht, mich zu sehen. Ist die Freude an diesem Treffen... nicht gegenseitig?";
					link.l1.go = "PZ_MarcelineFuck1";
				break;
				
				// поделили алмазы, без трахания и углепластиков
				case "NoFuck":
					link.l1 = "Ja, das habe ich. Ich erkenne, dass ich vielleicht nicht der schönste oder würdigste Mann auf dieser Insel bin, wie Sie bei unserem letzten Treffen erwähnten, aber zumindest wissen Sie, dass ich ein ehrlicher Mann bin. Hören Sie mir zu, gnädige Frau - ich werde nicht viel von Ihrer... kostbaren Zeit in Anspruch nehmen.";
					link.l1.go = "PZ_MarcelineNoFuck1";
				break;
				
				// "сошлись вот где-то посередине" (с)
				case "Deception":
					link.l1 = "Um Gottes willen, hören Sie auf zu schreien, gnädige Frau. Ich bin nicht hier, um mich für Ihre Täuschung Ihres Ritters und das Abhauen mit dem Drachenschatz zu rächen. Und ich versichere Ihnen, wenn ich Sie töten wollte, würde ich Sie einfach erschießen und um mein Leben rennen. Das ist schließlich Tortuga! Aber ich denke, Sie wissen bereits, dass das unter meiner Würde wäre.";
					link.l1.go = "PZ_MarcelineDeception1";
				break;
			}
		break;
		
		case "PZ_MarcelineFuck1":
			dialog.text = "Ach nein! Ich dachte nur, dass... Nun, es spielt keine Rolle! Sie sehen, böse Zungen verbreiten schmutzige Gerüchte über mich - eine arme Frau, die, selbst wenn sie wollte, weder jemandem schaden noch sich gegen Feinde wehren könnte. Außerdem ist es schon so lange her... Ich dachte, du bist mit schlechten Absichten zu mir gekommen, und nicht mit guten. Ich freue mich, mich geirrt zu haben. Es ist schwer zu leben, wenn man von Übelwollenden umgeben ist.";
			link.l1 = "Wie könnte ich? Selbst wenn ich so etwas gehört hätte, würde ich kein Wort davon glauben. Aber Sie haben recht - ich bin nicht nur gekommen, um Sie zu sehen. Obwohl ich froh bin, dass ich es getan habe. Ich weiß, das wird ungewöhnlich klingen, aber... diesmal braucht Ihr Ritter Ihre Hilfe, gnädige Frau.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineNoFuck1":
			dialog.text = "Und Sie sind viel sensibler, als ich dachte, dass Sie es wären. Aber Sie sind nicht ohne Fehler, Monsieur de Maure - ich habe erwartet, dass Sie mehr... verfeinert sind. Tatsächlich... entweder waren Sie schon immer so, oder der Archipel hat Sie bereits korrumpiert. Sie sollten wieder lernen, wie man mit einer Dame spricht. Aber Sie haben Recht - Sie sind ein ehrlicher Mann, wenn auch... einfach.";
			link.l1 = "Und Sie sind eine stolze und rachsüchtige Frau. Ihre Augen, Worte und ... Taten verraten das. Also wenn jemand mich verstehen wird, dann Sie. Genau wie ich Sie einst verstanden habe. Also lass uns nicht länger in der Vergangenheit verweilen. Können Sie mir helfen, gnädige Frau?";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_MarcelineDeception1":
			dialog.text = "Oh... Ich gebe zu, dass ich damals unfreundlich zu dir war. Aber nur, weil ich mir nicht ganz sicher war, nichts weiter! Hättest du mir alle Diamanten weggenommen? Oder hättest du meinen Ehemann dorthin gebracht, mit der Behauptung, du hättest von unseren Dienern erfahren, dass ich ihn bestohlen habe, und deine Beteiligung abgestritten? Schließlich sucht jeder nach seiner Gunst, nicht nach einer armen Frau wie mir... Jetzt erkenne ich, dass ich mich in dir getäuscht habe. Bitte akzeptiere meine Entschuldigung... mein Ritter.";
			link.l1 = "Ich weiß jetzt nicht, ob sie aufrichtig sind oder nicht. Aber das spielt keine Rolle. Ich brauche Ihre Hilfe, Madame Marceline. Es geht um Leben und Tod. Bitte lehnen Sie nicht ab.";
			link.l1.go = "PZ_Marceline2";
		break;
		
		case "PZ_Marceline2":
			dialog.text = "Meine Hilfe...? Ich bin sicherlich nicht die letzte Frau in der Stadt, aber mein Einfluss ist nicht so groß, wie ihr alle denkt. Ich bin eine Königin, die regiert, nicht herrscht. Aber ich werde dir zuhören. Was kann meine bescheidene Person für dich tun?";
			link.l1 = "Ich verstehe, dass dies ein unangenehmes Thema für Sie ist, aber ich suche Ihren Ehemann, Madame, und das so schnell wie möglich. Die Tatsache ist...";
			link.l1.go = "PZ_Marceline3";
		break;
		
		case "PZ_Marceline3":
			dialog.text = "Ist das ein Witz? Er ist gerade nicht in der Residenz? Dann ist er auf Geschäftsreise. Ich kann Ihnen nicht helfen, Monsieur de Maure.";
			link.l1 = "Sie haben Ihre Augen abgewendet. Sie wissen es. Ich weiß es auch. Ich muss nur dorthin. Bitte tun Sie nicht so, als ob Sie zum ersten Mal von dem Verließ gehört hätten - Sie sind zu klug, um es nicht zu wissen.";
			link.l1.go = "PZ_Marceline4";
		break;
		
		case "PZ_Marceline4":
			dialog.text = "Oh, ich habe das Gefühl, dass dieses Gespräch mir noch ein graues Haar bescheren wird. Als ob ich nicht schon genug erste Falten hätte. Was tust du uns allen nur an, Francois...";
			link.l1 = "Eine graue Strähne wird nur zu Ihrer Noblesse beitragen und Ihrer Schönheit nicht schaden. Aber ein gutes, unschuldiges Mädchen ist in die Hände Ihres Mannes gefallen. Und jetzt riskiert sie, ihre Schönheit, ihre Gesundheit und sogar ihr Leben zu verlieren!...! Sie wissen, was denen passiert, die dort gefangen sind. Bitte, Madame. Marceline... Helfen Sie Ihrem Ritter.";
			link.l1.go = "PZ_Marceline5";
		break;
		
		case "PZ_Marceline5":
			dialog.text = "Nicht wirklich mehr mein Ritter, oder? Komm schon, ich bin nicht dumm. Aber... Ich werde dir helfen, de Maure. Schließlich konnte es nicht ewig so weitergehen. Und eines Tages wäre es öffentlich geworden. Was mir jetzt wichtig ist, ist rechtzeitig und auf die richtige Weise auszusteigen. Und... Ich kann dich nicht zu ewigem Leiden verurteilen, das von dem verursacht wird, was mein 'Ehemann' deinem... Bekannten antun wird.";
			link.l1 = "Ich bin vielleicht nicht mehr Ihr Ritter, meine Dame. Aber auch Sie waren von Anfang an nicht meine Dame. Dennoch werde ich Ihnen mein Leben lang dankbar sein. Also, wo ist dieser Ort?";
			link.l1.go = "PZ_Marceline6";
		break;
		
		case "PZ_Marceline6":
			dialog.text = "Nun, ich nehme Sie beim Wort, Charles. In den Stadtverliesen. Es gibt ein großes Fass in einer der Sackgassen, und daneben beginnt ein Durchgang, der zu dem Versteck dieses Ungeheuers führt. Ich habe nicht hineingeschaut. Ich habe ihm nur einmal vor langer Zeit gefolgt. Und ich erschrak, als ich die unmenschlichen Schreie dieser armen Kreaturen hörte.";
			link.l1 = "Sie haben heute viele Leben gerettet, Madame. Nicht nur meine Geliebte, sondern auch alle, die in der Zukunft Ihrem Ehemann zum Opfer gefallen wären. Danke.";
			link.l1.go = "PZ_Marceline7";
		break;
		
		case "PZ_Marceline7":
			dialog.text = "Ach, lassen Sie mich mit diesen leeren Worten, Monsieur. Sie haben viel von mir verlangt. Und ich habe ein großes Risiko eingegangen. Versuchen Sie jetzt, Ihre neue Quest in das Drachenversteck erfolgreich zu machen... mein Ritter.";
			link.l1 = "Ich werde mein Bestes geben. Auf Wiedersehen, Marceline.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_MarcelineOver");
		break;
		
		case "PZ_ElitaShluha_18":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "So, you're a bandit, monsieur...? We don't hire new girls like this; we all came here voluntarily. I'm going to have to ask you and your... accomplice to step out. And I'll make sure this girl gets treatment - otherwise, I'll report you to the authorities!";
				link.l1 = "Wir sind keine Banditen. Aber dieses Mädchen kann es mit jedem von ihnen aufnehmen. Sie trägt kein Schwert zur Schau. Sie ist nur verwundet. Dieser Mann ist ein Freund von mir und auch der Bruder deiner Herrin. Also lasst uns sie sehen.";
				link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl1";
			}
			else
			{
				dialog.text = "Schön, Sie wieder zu sehen, Monsieur! Aber Sie wissen, dass wir hier keine Gäste ... niedrigen Standes akzeptieren. Selbst wenn sie empfohlen und bezahlt sind. Besonders gelbhäutige Arbeiter oder Negersklaven. Ich fürchte, Ihr Freund wird gehen müssen.";
				link.l1 = "Sagen Sie das nicht vor Ihrer Herrin. Sie hat auch gelbe Haut. Und das ist nicht ein Arbeiter, sondern ihr Bruder. Sie würden doch nicht ein Familientreffen stören, oder?";
				link.l1.go = "PZ_ElitaShluha_WithLongway1";
			}
		break;
		
		case "PZ_ElitaShluha_18_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "It's getting worse by the hour. First the mad yellow laborer and now you. No, monsieur, we don't pay for the girls who are brought to us by force; they are all here of their own free will.";
				link.l1 = "Ich habe dieses Mädchen gerettet und sie wird niemals an einem Ort arbeiten, der unter ihrer Würde ist. Eine Arbeiterin, sagst du?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl1";
			}
			else
			{
				dialog.text = "Oh Monsieur, was für ein schlechter Zeitpunkt! Wir nehmen heute keine weiteren Gäste auf - Sie können selbst sehen, was hier passiert ist.";
				link.l1 = "Deswegen bin ich hier. Es war ein gelbhäutiger Mann, der das alles organisiert hat, nicht wahr?";
				link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl1";
			}
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl1":
			dialog.text = "Ja, Monsieur, ein Arbeiter! Wir konnten kaum verstehen, was er sagte! Dieser Lump stürmte herein und verlangte, die Dame zu sehen. Er versicherte uns, er sei ihr Bruder. Wir haben nach Männern gerufen, aber...";
			link.l1 = "Das ist kein Hindernis für ihn. Was ist dann passiert?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithGirl2":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "Wie sich herausstellte, hat er nicht gelogen. Die Dame kam zu uns heraus und erkannte ihn. Tatsächlich sprechen sie immer noch in ihrem luxuriösen Ort.";
			link.l1 = "Wer weiß, was in seinem Kopf vor sich geht. Wir gehen da rein - wir werden sie retten, wenn wir müssen. Mach kein Aufhebens - es würde den Ruf des Ortes zerstören.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl1":
			dialog.text = "Das stimmt, Monsieur. Er sagte, er sei der Bruder der Dame.";
			link.l1 = "Und Sie haben ihn nicht hereingelassen...";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl2";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl2":
			dialog.text = "Natürlich nicht! Die Dame ist exquisit gekleidet und spricht ohne Akzent, im Gegensatz zu diesem Arbeiter. Wir haben versucht, ihn zu vertreiben, und er hat alle Wachen niedergeschlagen, können Sie sich das vorstellen?!";
			link.l1 = "Ich kann es mir leicht vorstellen. Und wo ist er jetzt?";
			link.l1.go = "PZ_ElitaShluha_AfterLevasseurWithoutGirl3";
		break;
		
		case "PZ_ElitaShluha_AfterLevasseurWithoutGirl3":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("PZ_EliteBrothelMercenary" + i);
				sld.lifeday = 0;
			}
			
			dialog.text = "Er und die Dame unterhalten sich immer noch über irgendetwas, aber wir können nicht verstehen, was es ist - wahrscheinlich in ihrer eigenen Sprache.";
			link.l1 = "Ich werde zu ihnen gehen. Vielleicht braucht Ihre Dame Hilfe. Rufen Sie nicht die Wachen - wenn es öffentlich wird, wird niemand mehr an Ihre Tür klopfen.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_EliteBrothelCreateChangShin");
		break;
		
		case "PZ_ElitaShluha_WithLongway1":
			dialog.text = "Ein Bruder? Die Herrin ist würdevoll, was mehr ist, als ich von diesem 'Bruder' von ihr sagen kann. Keine Notwendigkeit, ihr den Kopf zu verdrehen oder sie mit diesem Arbeiter zu betrügen. Bring ihn weg.";
			link.l1 = "Ich habe dir gesagt, dass sie sich schon vor langer Zeit verloren haben. Er hat einfach weniger Glück. Wir werden die Einrichtung selbst für unsere Zeit bezahlen. Benachrichtigen Sie jetzt die Herrin.";
			link.l1.go = "PZ_ElitaShluha_WithLongway2";
		break;
		
		case "PZ_ElitaShluha_WithLongway2":
			dialog.text = "Sie hat keinen Grund, sich vor Ihnen in Acht zu nehmen. Und Ihre Hartnäckigkeit missfällt mir. Jungs! Werft diesen Arbeiter hinaus! Und seinen verwirrten Meister auch!";
			link.l1 = "Verdammt! So viel Arroganz für eine Kurtisane!";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl1":
			dialog.text = "Keine Chance! Die Herrin allein mit all dieser seltsamen Gesellschaft von Ihnen? Nur wenn Sie alleine dorthin gehen, mein Herr. Und Ihre... Freunde werden draußen warten - wir haben hier ein anständiges Etablissement.";
			link.l1 = "Warum sorgen Sie sich um sie? Jeder weiß, dass sie eine der besten Schwertkämpferinnen in Tortuga ist. Und meine Freunde sind anständiger als die meisten Leute in dieser Stadt.";
			link.l1.go = "PZ_ElitaShluha_WithLongwayAndGirl2";
		break;
		
		case "PZ_ElitaShluha_WithLongwayAndGirl2":
			dialog.text = "Jungs! Hier drin sind ein verwundeter Bandit und ein schmutziger Arbeiter! Sie wollen etwas von unserer Herrin! Kümmert euch um sie!";
			link.l1 = "Welche Hingabe, verdammt...";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_EliteBrothelFight");
		break;
		
		case "PZ_ChangShin1":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			
			// итак, снова проверка по результатам прохождения. Лонгвэй с нами, тян ещё в пыточной
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Ich nehme an, du bist Charles de Maure? Und das... Oh.";
				link.l1 = "Und Sie müssen Belle Etoile sein. Oder soll ich Chang Xing sagen? Und ja, das ist dein Bruder. Er sucht seit über einem Jahrzehnt nach dir. Er und ich haben viele, viele Fragen an dich. Und nicht viel Zeit.";
				link.l1.go = "PZ_ChangShin_WithLongway1";
			}
			// пришли с Лонгвэем и тян
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				dialog.text = "Mein Gott, du hast überlebt. Du hast einen ziemlich guten Verteidiger, auch wenn er ein wenig spät war. Besser als derjenige, der mich offenbar für seinen Beschützer hält und jetzt neben dir steht. Der Himmel bevorzugt dich, mein liebes Mädchen.";
				link.l1 = "Ich sehe, dass du es weißt. Das ist sogar noch besser - keine Notwendigkeit zu erklären. Aber sag mir, worüber lächelst du, Chang Xing? Du genießt es, andere Mädchen leiden zu sehen, nicht wahr? Du verkaufst sie ja schließlich.";
				link.l1.go = "PZ_ChangShin_WithLongwayAndGirl1";
			}
			// Лонгвэй с нами, тян на небесах
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom") && CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
				dialog.text = "Charles de Maure, richtig? Ich habe gehört, Sie wollten mich sehen. Also, was bedrückt Sie? Hat Ihnen der Service in unserer Einrichtung beim letzten Mal nicht gefallen?";
				link.l1 = "Ich komme gerade aus einem anderen Ihrer Etablissements, Chang Xing. "+sStr+", mein Geliebter, ist tot. Und ich weiß, dass du auch daran beteiligt warst.";
				link.l1.go = "PZ_ChangShin_GirlDied1";
			}
		break;
		
		case "PZ_ChangShin_WithLongway1":
			dialog.text = "Chang Xing... Es ist lange her, dass ich diesen Namen gehört habe. Es ist wirklich lange her. Weiße Leute... Ihr seid immer in Eile. Was ist mit einem gemütlichen Familientreffen? Mir ist es allerdings egal. Ich habe vor Jahren aufgehört, mich auf andere Leute zu verlassen. Warum sagst du nichts, mein Bruder? Bist du nicht glücklich, deine eigene Schwester zu sehen? Du hast mich schließlich so unerbittlich gesucht.";
			link.l1 = "Wir haben andere dringende und wichtigere Angelegenheiten zu erledigen. Sprich mit deiner Schwester, Longway. Aber erinnere dich daran, wo wir noch hin müssen. Wir müssen uns beeilen. Und ich habe auch Fragen an sie.";
			link.l1.go = "PZ_Longway_SisterDialog1";
		break;
		
		case "PZ_Longway_SisterDialog1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "(Auf Mandarin) Longway, hm? Nun, abgesehen vom Namen, hast du dich nicht viel verändert... Chang Tu.";
			link.l1 = "(Auf Mandarin) Aber du hast dich sehr verändert, Schwester. Was ist passiert? Dein Blick war einst so warm wie die Mittagssonne. Jetzt ist er kalt und drückt nichts als Verachtung aus. Und deine Stimme? Ich liebte es, dich zum Lachen zu bringen und diesen silbernen Glocken zuzuhören... Jetzt ist sie kälter als ein Goango im Winter. Und du trägst ihre Kleidung. Und du verkaufst die Frauen selbst, obwohl du einst von Fermentelos entführt wurdest.";
			link.l1.go = "PZ_Longway_SisterDialog2";
		break;
		
		case "PZ_Longway_SisterDialog2":
			dialog.text = "Du kommst, um mir Vorlesungen zu halten, obwohl du einst für Rodenburg gearbeitet hast, einen der größten Schurken des Archipels? Du denkst, ich wusste nichts über dich? Ich wusste immer Bescheid. Es steht dir nicht zu, zu beurteilen, was ich geworden bin und warum, mein fehlgeleiteter älterer Bruder.";
			link.l1 = "Lass mich also herausfinden, Xing! Und sag mir. Wenn du wusstest, dass ich im Archipel war, warum wolltest du mich nach all diesen Jahren nicht treffen? Ich habe mein ganzes Leben damit verbracht, nach dir zu suchen...";
			link.l1.go = "PZ_Longway_SisterDialog3";
		break;
		
		case "PZ_Longway_SisterDialog3":
			dialog.text = "Denn weder du noch der Himmel haben mich vor dem schrecklichsten aller Schicksale geschützt. Dann wurde mir klar, dass niemand in dieser Welt jemand anderen braucht. Wir können uns nur auf uns selbst verlassen. Nun, ich werde es dir erzählen, wenn du es wissen willst. Aber ich werde in seiner Sprache sprechen. Ich bin sicher, er würde es auch gerne hören. Du verstehst Französisch, nicht wahr, Tu?";
			link.l1 = "(auf gebrochenem Französisch): Ja, ich spreche diese Sprache.";
			link.l1.go = "PZ_Longway_SisterDialog4";
		break;
		
		case "PZ_Longway_SisterDialog4":
			dialog.text = "Ha ha ha, oh, Himmel! Ihr Akzent ist schrecklich. Es ist aber nicht Ihre Schuld - die französische Aussprache und Schrift sind tatsächlich schwierig.";
			link.l1 = "Du lachst jetzt anders, Schwester...";
			link.l1.go = "PZ_ChangShin_WithLongway3";
		break;
		
		/*case "PZ_Longway_SisterDialog5":
			Return_LongwayOfficer();
			
			StartInstantDialog("PZ_ChangShin", "PZ_ChangShin_WithLongway3", "Quest\CompanionQuests\Longway.c");
		break;*/
		
		case "PZ_ChangShin_WithLongway3":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
			dialog.text = "Mein lieber Bruder möchte wissen, was mir in all den Jahren passiert ist. Ich denke, es wäre gut, wenn auch du zuhörst - wie du gesagt hast, hast du Fragen. Mach dir also keine Sorgen - ich werde dir alles auf Französisch erzählen.";
			link.l1 = "Sag mir nur das Wichtigste - als Longway mir seine Lebensgeschichte erzählte, dauerte es ein paar gute Stunden. Und ich habe jetzt Eile.";
			link.l1.go = "PZ_ChangShin_WithLongway4";
		break;
		
		case "PZ_ChangShin_WithLongway4":
			dialog.text = "Sie werden geduldig sein. Ich habe es mehr als ein Jahr lang für mich behalten. Und wenn Sie unterbrechen, werde ich keine Ihrer Fragen beantworten.";
			link.l1 = "In Ordnung... Dann mach weiter.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl1":
			dialog.text = "Wo sind Ihre Manieren, Charles de Maure? Mir wurde gesagt, Sie seien ein Mann von vorzüglichen Manieren und ein Muster-Liebhaber. Nur Gerüchte, aber in Wirklichkeit... ein Flop? Das dachte ich mir. Und Sie irren sich - ich hasse alle Männer und Frauen gleichermaßen. Tatsächlich vertraue ich niemandem, ich wundere mich nicht, ich erwarte nichts. Ich würde Ihre Hoden nur zu gerne zerquetschen, wenn ich Sie in die Finger bekommen könnte. Aber meinen echten Namen nach all diesen Jahren zu hören, war ein kleines... erfrischendes Erlebnis.";
			link.l1 = "Ich bin ein Frauenheld für Damen, nicht für Hexen wie Sie. Und was haben Sie erwartet, wenn Sie die Person quälen, die mir am meisten bedeutet? Ich kann mich kaum zurückhalten, auch Ihnen etwas anzutun. Nicht zuletzt um seinetwillen. Longway ist mein Freund. Und Sie sind seine Familie. Er hat über ein Jahrzehnt nach Ihnen gesucht. Und er hat es verdient, mit Ihnen zu sprechen.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl2";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl2":
			dialog.text = "Wie sentimental. Und wie traurig, dass es mir egal ist. Aber du wirst jetzt nicht so leicht davonkommen, oder, Tu? Nicht für das Töten von dir und all euch für einmal zu spät sein. Aber zu wissen... Ich schätze, du verdienst es zu wissen. Du kanntest mich, als ich nicht so war, Bruder.";
			link.l1 = "Egal was dir passiert ist... du hattest immer eine Wahl, Chang Xing.";
			link.l1.go = "PZ_ChangShin_WithLongwayAndGirl3";
		break;
		
		case "PZ_ChangShin_WithLongwayAndGirl3":
			dialog.text = "Du bist noch jung und weißt nicht, wie die Welt funktioniert, Charles de Maure. Im Leben gibt es nur eine echte Wahl: leben oder sterben. Ich denke, es wäre auch gut für dich, alles zu wissen. Also werde ich meine Geschichte auf Französisch erzählen. Du sprichst es, nicht wahr, Tu?";
			link.l1 = "Mit Akzent. Aber er versteht es sehr gut. Sie können beginnen.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin_GirlDied1":
			dialog.text = "Und wo waren Sie die ganze Zeit? Espanola ist nur ein oder zwei Tage entfernt. Ihr Tod ist auch deine Schuld. Und du. Du bist mehr als ein Jahrzehnt zu spät. Unsere Retter, unsere Beschützer. Je früher eine Frau lernt, sich zu verteidigen, desto besser. Einige schaffen es rechtzeitig, andere nicht. Und jemand hat nicht genug Verstand, um darauf zu kommen.";
			link.l1 = "Seien Sie vorsichtig mit jedem Wort, das Sie als nächstes sagen. Ich habe dich noch nicht in Stücke gerissen nur für meinen Freund, deinen Bruder. Sie haben keine Ahnung, was er für dich durchgemacht hat.";
			link.l1.go = "PZ_ChangShin_GirlDied2";
		break;
		
		case "PZ_ChangShin_GirlDied2":
			dialog.text = "Ich bezweifle sehr, dass er etwas auch nur annähernd Ähnliches wie das, was ich durchgemacht habe, erlebt hat.";
			link.l1 = "Also erzähl uns.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_ChangShin2":
			dialog.text = "Nun, was kann ich sagen, ich war damals jung, dumm und naiv. Und intolerant. Hat Tu dir schon erzählt, wie ich von Oliverio Fermentelos entführt wurde, nachdem er meine Eltern und mich getötet hatte?";
			link.l1 = "Das ist richtig.";
			link.l1.go = "PZ_ChangShin3";
		break;
		
		case "PZ_ChangShin3":
			dialog.text = "Er umwarb mich und gestand seine Gefühle, aber ich habe ihn abgelehnt. Und dann hat er unsere Familie abgeschlachtet und mich gestohlen. Und dann...";
			link.l1 = "Ich kann raten.";
			link.l1.go = "PZ_ChangShin4";
		break;
		
		case "PZ_ChangShin4":
			dialog.text = "Ich wünschte, du könntest es. Dann gestand er mir wieder seine Gefühle, heiß und unter Tränen, und sagte, dass es der einzige Weg sei, weil meine Familie mich nie mit ihm gehen lassen würde.";
			link.l1 = "Wahnsinn...";
			link.l1.go = "PZ_ChangShin5";
		break;
		
		case "PZ_ChangShin5":
			dialog.text = "Heh, ein Wort, das mein ganzes Leben seit damals beschreibt. Ich habe ihn wieder abgelehnt. Und so ging es eine Weile weiter. Aber klar, es konnte nicht ewig so weitergehen, denn ich war völlig in seiner Gewalt.";
			link.l1 = "Also ist es passiert?";
			link.l1.go = "PZ_ChangShin6";
		break;
		
		case "PZ_ChangShin6":
			dialog.text = "Natürlich. Er nahm mich mit Gewalt, rau und gnadenlos. Nicht, dass es Vergewaltiger jemals stören würde, aber hatte er mir nicht zuvor unter Tränen seine große Liebe gestanden? Pfft! Die Liebe war anscheinend verschwunden. Und all das ging Tag für Tag weiter, als wäre es eine Routine. Zuerst schrie ich und wehrte mich, aber dann hörte ich auf - was hatte es überhaupt für einen Sinn...?";
			link.l1 = "Aber Fermentelos hat bekommen, was er verdient hat, und du bist hier gelandet. Wie kam es dazu?";
			link.l1.go = "PZ_ChangShin7";
		break;
		
		case "PZ_ChangShin7":
			dialog.text = "Nun, ziemlich bald hatte er genug von mir. Das ist lustig, nicht wahr? Er tötete meine und Tu's Eltern, stahl mich, entehrte mich regelmäßig, nur um mich am Ende wegzuwerfen. Er kam zu diesem Archipel und verkaufte mich als Sklavin an Levasseur.";
			link.l1 = "Ich würde das meinem Feind nicht wünschen. Wie haben Sie überlebt? Und wie sind Sie überhaupt frei gekommen? Nach dem, was ich gehört habe, hat Levasseur nie Frauen aus seinem Versteck gelassen. Er hat sie immer losgeworden.";
			link.l1.go = "PZ_ChangShin8";
		break;
		
		case "PZ_ChangShin8":
			dialog.text = "So ist es jetzt. Levasseur war damals anders. Nein, er war immer ein Tier. Aber anfangs entführte er gelegentlich junge Kolonisten vor Ort, vergewaltigte sie in seinem Keller und wurde sie fast sofort los, um nicht für ihr Schweigen bezahlen zu müssen. Nur selten behielt er sie länger als ein paar Tage in diesen Jahren. Bei mir hingegen war es von Anfang an anders.";
			link.l1 = "Weil du ein Sklave warst, richtig?";
			link.l1.go = "PZ_ChangShin9";
		break;
		
		case "PZ_ChangShin9":
			dialog.text = "Genau. Levasseurs Hauptwunsch war nicht nur körperliches Vergnügen. Und nicht einmal ein momentanes Gefühl der Macht über seine Opfer - schließlich hat er es über die ganze Insel. Aber...";
			link.l1 = "... das Vergnügen, sie brechen zu sehen - ihren Willen, ihr Aussehen, ihre Stimme, ihr Verhalten.";
			link.l1.go = "PZ_ChangShin10";
		break;
		
		case "PZ_ChangShin10":
			dialog.text = "Ja. Ich sehe, Sie haben Ihre Hausaufgaben gemacht, Kapitän. Aber in dieser Hinsicht war ich ihm kein Spaß - Fermentelos brachte mich schon gebrochen. Und Levasseur fand mich nicht schön - er mag keine asiatischen Frauen. Wissen Sie, aus irgendeinem Grund hat mich das so sehr beeinflusst - ich weiß, dass ich attraktiv bin, aber ich glaube nicht, dass ich wirklich schön bin. Und ich glaube es nicht, wenn mir Leute das sagen. Selbst jetzt, wenn ich trainiere, Seide trage und mich mit feinem Parfüm besprühe. Nicht, dass ich die Zustimmung meines Peinigers brauche, aber...";
			link.l1 = "Nun, dann wiederhole ich meine Frage - wie haben Sie überlebt? Sobald er sich mit einer Frau langweilt, wird er sie los. Mit dir war ihm von Anfang an langweilig, wie du sagst.";
			link.l1.go = "PZ_ChangShin11";
		break;
		
		case "PZ_ChangShin11":
			dialog.text = "Ich vermute, die Tatsache, dass ich ihn von Anfang an gelangweilt habe, hatte einen Effekt. Und die Tatsache, dass ich eine Sklavin war - ich konnte nirgendwo hingehen oder etwas sagen. Sklavinnen werden seit Tausenden von Jahren so behandelt. Er fing an, darüber nachzudenken, wie er die Zeit, die er mit mir verbrachte, für ihn 'spaßig' gestalten konnte.";
			link.l1 = "Ich vermute, so wurden seine Süchte geboren, in ihrer jetzigen Form.";
			link.l1.go = "PZ_ChangShin12";
		break;
		
		case "PZ_ChangShin12":
			dialog.text = "Genau. Zuerst waren es Schläge, Spucken und andere Demütigungen. Und Spott - sowohl über mein Aussehen als auch über meine Herkunft, mein Blut. Und dann kamen die ersten Folterungen - Messer, Zangen, eine Pfanne... Deshalb trage ich solch geschlossene Kleidung - mein ganzer Körper ist vernarbt, verbrannt und verstümmelt. Und deshalb habe ich nie vor, mich wieder vor einem Mann auszuziehen. Niemals wieder. Dann habe ich endlich erkannt, was ich hätte erkennen sollen, als Fermentelos mich entführte.";
			link.l1 = "Was war das?";
			link.l1.go = "PZ_ChangShin13";
		break;
		
		case "PZ_ChangShin13":
			dialog.text = "Dass ich nicht länger eine hilflose Marionette sein sollte. Im Gegenteil, ich sollte die Kontrolle über mein Leben haben. Bei mir war es so, dass eine Frau ihr Leben nur auf irgendeine Weise verändern kann, indem sie die Männer um sie herum kontrolliert.";
			link.l1 = "Ich würde nicht sagen, dass Levasseur kontrolliert werden kann.";
			link.l1.go = "PZ_ChangShin14";
		break;
		
		case "PZ_ChangShin14":
			dialog.text = "Und Sie hätten nicht Unrecht. Aber es ist möglich, ihn vorsichtig zu beeinflussen. Levasseur hasst gleichermaßen sowohl vollständigen Gehorsam von Anfang an als auch Streitigkeiten oder Bitten. So geht es ihm auch mit Schmeichelei - anscheinend hat er erkannt, was für ein Schwein er wirklich ist. Das habe ich sofort zu einem ziemlich quälenden Preis erkannt. Aber wenn er nach einem weiteren Abend voller Folter und Gewalt mit allem zufrieden war, war es möglich, sanft mit ihm zu sprechen. Ich bin vielleicht nicht von edler Geburt, aber es fehlt mir nicht an Intelligenz.";
			link.l1 = "Und worüber habt ihr gesprochen?";
			link.l1.go = "PZ_ChangShin15";
		break;
		
		case "PZ_ChangShin15":
			dialog.text = "Ich weckte sein Interesse. Schlug Foltermethoden vor, riet ihm, welche Folterinstrumente man am besten nicht benutzen sollte, und mit welchen man anfangen könnte. Zuerst probierte er es natürlich alles an mir aus. Aber dann... fing er an, mich auf seine verdrehte Art zu respektieren. Was geht in seinem Kopf vor? Ich versuchte herauszufinden, wie er so geworden ist, aber er prügelte mich wieder halb tot. Dann holte er einen persönlichen Arzt.";
			link.l1 = "Das ist noch seltsamer und abscheulicher als das, was ich bereits über ihn gehört habe.";
			link.l1.go = "PZ_ChangShin16";
		break;
		
		case "PZ_ChangShin16":
			dialog.text = "Er verlangte nicht länger, dass ich mich ihm hingeben sollte. Er nannte mich eine Schülerin. Aber er sagte immer, dass ich als sein Projekt eine totale Enttäuschung war. Ich vermute, um mich auf Trab zu halten. Also begann er, mir Fechten und Sprachen beizubringen. Obwohl er mich im Keller hielt, war ich es, nicht seine Frau, die alle teuren Kleider bekam.";
			link.l1 = "Ein Projekt in der Tat. Man kann einen klaren Parallelismus erkennen, wie Sie diesen Ort führen.";
			link.l1.go = "PZ_ChangShin17";
		break;
		
		case "PZ_ChangShin17":
			dialog.text = "Ich habe nicht daran gedacht, hmmm. Und ich mag Ihre Parallele nicht, denn ich quäle meine weiblichen Angestellten nicht. Und ich lasse meine Kunden das auch nicht tun. Obwohl ich diese Schlampen hasse und ihre Schönheit beneide. Und ich habe nichts mit diesem Schwein gemeinsam, erinnere dich daran.";
			link.l1 = "Wie haben Sie dieses Bordell bekommen?";
			link.l1.go = "PZ_ChangShin18";
		break;
		
		case "PZ_ChangShin18":
			dialog.text = "Von Levasseur, natürlich. Eine Zeit lang hielt er mich bei sich. Ab und zu bat er sogar um Rat, wie man dieses oder jenes Mädchen brechen könnte. Schließlich war ich ihm besonders, auch wenn er es nie zugeben würde. Ich war die Erste. Ich habe alles gesehen.";
			link.l1 = "Von wem hat nochmal wer gelernt?";
			link.l1.go = "PZ_ChangShin19";
		break;
		
		case "PZ_ChangShin19":
			dialog.text = "Ich bin nicht so! Ich hasse aus tiefstem Herzen jeden, dem alles auf dem Silbertablett serviert wurde! Das ist nicht fair! Dieses Bordell war meine Idee! Meine Arbeiterinnen sind die Töchter von Kaufleuten, Beamten und Edelmännern, die manchmal mit Levasseur zu tun hatten. Ich habe ihn gebeten, sie mir zu geben. Folter und Demütigung in einem geheimen Keller sind eine Sache. Aber die öffentlichen Aktivitäten einer Kurtisane für solche Leute sind etwas ganz anderes!";
			link.l1 = "Ich würde nicht sagen, dass Ihre weiblichen Arbeiter so gedemütigt, elend und gebrochen aussehen.";
			link.l1.go = "PZ_ChangShin20";
		break;
		
		case "PZ_ChangShin20":
			dialog.text = "Weil sie wissen, was Levasseur oder sogar ich mit ihnen machen würde, wenn sie auch nur einen Mucks machen. Aber Sie haben natürlich teilweise Recht. Der Wein, das Essen, die Seidenstoffe, das Fehlen täglicher Folter - viele von ihnen begannen, mich als Retter zu sehen. Verdammt Narren! Nur wenige von ihnen sind unglücklich hier zu sein. Einige von ihnen hat er mit schwerem Herzen weggegeben. Und er würde kichern und sagen, ich könnte ihm jederzeit einen von ihnen im Austausch für die Behebung meiner finanziellen Probleme zurückgeben. Aber ich habe immer nein gesagt. Zumindest würden sie auf diese Weise das Gold zurückbringen, anstatt im Keller umsonst zu sterben. Es wäre für sie auch ein zu einfacher Ausweg.";
			link.l1 = "Wie schade, dass sich nicht jeder gedemütigt fühlte, die Klausuren schlimmer als die Heilige Inquisition gegen einen goldenen Käfig zu tauschen, wie es dein Bordell ist...";
			link.l1.go = "PZ_ChangShin21";
		break;
		
		case "PZ_ChangShin21":
			dialog.text = "Du urteilst über mich? Ich wollte nicht nur überleben, sondern einen erfolgreichen Handel aufbauen. Zwar unwissentlich, war Levasseur mir dankbar. Obwohl ich nicht länger ein Sklave war, konnte er mich nicht gehen lassen. Ich war immer noch gezwungen, für ihn zu arbeiten und seinen Handlangern zu helfen. Besonders seinem dürren Neffen, der jedes Mal sabberte, wenn er mich sah. Aber er würde nicht wagen, mich anzugreifen oder in schlechter Weise mit mir zu sprechen. Widerlich. Weißt du, obwohl er mich eine Enttäuschung nannte, war ich nützlicher als Thibaut und Martene zusammen. Ich begleitete sie oft auf seinen Befehl, wie damals in Port-au-Prince.";
			link.l1 = "Das erklärt eine ganze Menge...";
			link.l1.go = "PZ_ChangShin22";
		break;
		
		case "PZ_ChangShin22":
			dialog.text = "Das stimmt. Hören Sie. Ich habe deinen Geliebten nicht gefoltert. Genau wie ich kein Mädchen mit diesen Händen gefoltert habe, auch wenn ich Levasseur manchmal Ratschläge gegeben habe. Aber wo wir schon beim Thema sind...";
			link.l1 = "Was?";
			link.l1.go = "PZ_ChangShin23";
		break;
		
		case "PZ_ChangShin23":
			dialog.text = "Wie Sie vielleicht auch wissen, verlangt Levasseur manchmal, dass man ihm ein bestimmtes Mädchen bringt, das in Tortuga gesehen wurde, und dann verließ sie die Insel. Oder jemand würde ihn überraschen und ihm einen Fremden bringen, um seine Gunst zu verdienen, wie es bei mir der Fall war. Ihre Geliebte zu entführen war meine Idee.";
			link.l1 = "Was hast du gerade gesagt...?";
			link.l1.go = "PZ_ChangShin24";
		break;
		
		case "PZ_ChangShin24":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "At first, we were considering capturing that blonde who used be so close to you. But since she is untouchable now, and because we have already promised him a girl, you redhead had to do.";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "I heard rumors about your gorgeous companion who never leaves your side. Considering Levausser's love for blondes, I had very little trouble selling him this idea.";
			dialog.text = "Sotta, sein Köter, sollte ihm die Mulattin, Lutters Frau, bringen. Aber du hast Sotta getötet, also - keine Mulattin für den großen Mann. Levasseur war wütend. Alle bekamen Prügel - Thibaut, Martene, sogar ich. Ich weiß nicht, wer mich wütender gemacht hat: Er, weil er mich wieder verprügelt hat, oder du, der es verursacht hat... "+sStr+"";
			link.l1 = "Also ist es nicht einmal wegen ihm... Du hast das getan.";
			link.l1.go = "PZ_ChangShin25";
		break;
		
		case "PZ_ChangShin25":
			dialog.text = "Ich hoffe nicht einmal auf Ihre Vergebung, und was mehr ist, ich brauche sie nicht. Wenn Sie Blut wollen, bekommen Sie Blut. Und Sie werden es sehr bereuen. Aber ich werde das Verständnis nicht ablehnen. Zum ersten Mal in zehn langen Jahren könnte ich es gebrauchen. Alles, was ich je getan habe, war nur mein Bestes zu geben, um eines Tages aus Tortuga herauszukommen. Haben Sie Fragen an mich, Charles de Maure?";
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo") && !CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "Aber Sie waren an der Entführung beteiligt. Und Sie wissen, wo Levasseur seine Opfer festhält. Sagen Sie mir, wo es ist. Und wenn das Schlimmste nicht passiert ist - werde ich hart darüber nachdenken, mich nicht an Ihnen zu rächen.";
				link.l1.go = "PZ_ChangShinDontKnow1";
			}
			else
			{
				link.l1 = "Nun, das kommt endlich alles zusammen...";
				link.l1.go = "PZ_ChangShin26";
			}
		break;
		
		case "PZ_ChangShinDontKnow1":
			dialog.text = "Ich weiß es, weil ich dort war. Und wenn Sie den Eindruck haben, dass ich ihm gegenseitig und ungesund anhänge - dann irren Sie sich gewaltig. Ich würde mich freuen, jemanden zu sehen, der dieses Schwein auf einen Spieß steckt.";
			link.l1 = "Ich habe keine Zeit, Chang Xing. Wo ist es?";
			link.l1.go = "PZ_ChangShinDontKnow2";
		break;
		
		case "PZ_ChangShinDontKnow2":
			dialog.text = "Kennen Sie das örtliche Verlies unter den Stadtstraßen? Dorthin gehen Sie. In einer der Sackgassen steht ein großes Weinfass und daneben beginnt ein geheimer Durchgang zu seinem Vergnügungszimmer, wie er es manchmal nennt.";
			link.l1 = "Nun, schließlich kommt alles zusammen...";
			link.l1.go = "PZ_ChangShin26";
		break;
		
		case "PZ_ChangShin26":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip")) StartInstantDialog("Longway", "PZ_Longway_SisterDialog6", "Quest\CompanionQuests\Longway.c");
			else
			{
				dialog.text = "Gut für dich. Jetzt raus. So sehr ich nach so vielen Jahren sprechen wollte, die Erkenntnis, dass du all meine Geheimnisse kennst, weißt, was mir angetan wurde - es ist widerlich. Der Anblick von dir macht mich jetzt nur noch wütend. Oh, und Tu bleibt bei mir.";
				link.l1 = "Warum ist das so?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet1";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet1":
			dialog.text = "Vielleicht weil ich seine Familie bin? Und weil ich sehe, wie er mit dir ist - ein geschlagener, elender Murmler, der noch nicht einmal Zeit hatte, die Sprache vollständig zu erlernen und richtig zu sprechen. Doch er hat mir gesagt, ihr zwei wärt Freunde. Es ist klar, wie du ihn beeinflusst hast. Zumindest werde ich einen Mann aus ihm machen.";
			link.l1 = "Und bist du wirklich zufrieden mit dir selbst? Was wirst du aus ihm machen? Ein grausames, bitteres Geschöpf, das mit Leben handelt?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet2";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet2":
			StartInstantDialog("Longway", "PZ_Longway_SisterDialog_Ubezhdaet3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet3":
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				dialog.text = "Mein Herr Kapitän, bitte haltet ein. Ich bitte Euch, meine Schwester in Frieden zu lassen. Und... Ich werde bei ihr bleiben.";
				link.l1 = "Du... was? Longway... aber warum? Siehst du nicht, was aus ihr geworden ist?";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet4";
			}
			else
			{
				dialog.text = "Bist du anders? Du hast dich im Laufe der Zeit verändert. Zum Schlechteren. Anfangs warst du höflich und verständnisvoll. Aber dann wurdest du unhöflich, noch unhöflicher als Rodenburg. Und als ich ein gutes Schiff brauchte, um Van der Vink zu fangen, hast du mir nur Schrott gegeben!";
				link.l1 = "Longway...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet8";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Einmal bin ich auf See gegangen und habe all diese Jahre verbracht, nur um meine Schwester zu finden und zu retten. Und jetzt ist sie hier und sicher. Meine Mission ist abgeschlossen. Und... Mein Name ist Chang Tu. Longway ist der Name, den mir der Verräter Van Merden gegeben hat, falls du es vergessen hast. Aber Chang Tu ist ein freier Mann. Chang Tu's lange Reise ist endlich vorbei.";
			link.l1 = "Sie wird dich zu einem Diener machen, wie es einst Rodenburg tat. Sie wird dich unter Druck setzen, weil du zur Familie gehörst. Und wirst du dich so leicht auf die Seite dessen stellen, der mir und "+sStr+" so viel Schmerz?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet5";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Gerade jetzt sind Sie es, der Druck auf Chang Tu ausübt. Bitte, lassen Sie mich gehen. Ich bin sehr müde. Sie sind ein guter Mann, Kapitän - der Himmel kann das bezeugen. Aber Sie sind für mich keine Familie. Sie ist es. Wenn ich nicht bleibe, dann waren all diese Jahre umsonst. Jetzt werde ich ihr Leitstern sein und ihr erloschenes Feuer wieder entfachen - warm und tröstend, nicht alles verbrennend, was es berührt.";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				link.l1 = "Hmm, du hast recht. Vielleicht dränge ich gerade zu sehr. Nun, ich habe dich schon immer respektiert. Ich wünsche dir ein langersehntes Familientreffen mit deiner Schwester. Aber ich warne dich, du wirst bei ihr keinen Frieden finden.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko") && !CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva")) 
				{
					pchar.questTemp.PZ_LongwayHochetMira = true;
					link.l1.go = "PZ_Longway_SisterDialog_ReactiaDevushek";
				}
				
			}
			else
			{
				link.l1 = "Du kannst mich jetzt nicht verlassen! Ich muss immer noch retten "+sStr+" von Levasseur! Willst du, dass ich dort alleine hingehe? Hilf mir, Longway. Und dann lasse ich dich gehen. Ich verspreche es dir.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet6";
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet6":
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Ich kann damit umgehen. Du musst dir keine Sorgen mehr um mich machen. Danke.";
				link.l1 = "Es scheint, dass Ihre Schwester ärgerlich ist, dass wir uns friedlich getrennt haben.";
			}
			else
			{
				dialog.text = "Sie werden es herausfinden, Herr Kapitän. Sie sind der intelligenteste Mann, den ich je gesehen habe. Sie können diesen Wurm, der es gewohnt ist, Frauen zu quälen, leicht in den Griff bekommen. Ich bitte Sie, zwingen Sie mich nicht. Meine Schwester hat so viel mit mir zu besprechen! Und... mein Name ist Chang Tu.";
				link.l1 = "Sie erkennen, dass Sie mich verraten, indem Sie mich jetzt verlassen?! Besonders, indem Sie bei ihr bleiben - der Frau, die das alles ins Rollen gebracht hat!";
			}
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet7";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Fürchte dich nicht, Kapitän. Obwohl sie respektlos von mir spricht, bin ich der ältere Bruder und ihr letzter männlicher Verwandter. Du kannst gehen. Ich werde nicht zulassen, dass sie dich tötet. Leb wohl.";
				link.l1 = "Lebewohl... Chang Tu.";
				DeleteAttribute(pchar, "questTemp.PZ_LongwayRyadom");
				AddDialogExitQuest("PZ_BrothelTeleportVZal");	//Мирно разошлись
			}
			else
			{
				dialog.text = "Ich habe alles gesagt, was ich zu sagen hatte. Auf Wiedersehen, Kapitän. Und viel Glück für dich. Chang Tu wird immer ein freier Mann sein. Vergiss das nicht.";
				link.l1 = "Und das ist, was ich bekomme, nachdem ich alles aufgegeben und Ihnen bei Ihrer Suche geholfen habe?! Nach dem, was sie tun zu "+sStr+" jetzt?! Du bist ein Verräter, Chang Tu. Und du wirst als solcher sterben, beide, ihr verdammten Schlangen!";
				link.l1.go = "exit";
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				AddDialogExitQuest("MainHeroFightModeOn");
				AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
			}
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8":
			dialog.text = "Mein Name ist Chang Tu. Longway ist tot. Du hast ihn getötet. Du bist nicht mehr mein Kapitän. Und jetzt wirst du sterben. Meine Familie wird endlich Frieden finden, und unser Stern wird hell in der Nacht leuchten.";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
			{
				link.l1 = "(Vertrauenswürdig) (Führung) Longway... Chang Tu. Halt. Ich weiß, dass ich nicht der perfekte Kapitän für dich war. Aber willst du mich wirklich so sehr dafür töten? Nach allem, was wir durchgemacht haben? Erst Rodenburg, jetzt die Suche nach deiner Schwester.";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet9";
				notification("Trustworthy", "Trustworthy");
				notification("Skill Check Passed", SKILL_LEADERSHIP);
			}
			else
			{
				link.l1 = "Longway, ich bin dein Kapitän. Nicht deine Familie und nicht eine Kindermädchen. Ich gebe Befehle, und frage mich nicht, ob ich dich unbeabsichtigt beleidigt habe. Du stellst Forderungen, als wären wir alte Eheleute, beim Gott...";
				link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet15";
				if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
			}
			link.l2 = "Aye. Ich kann es jetzt sehen. Du bist genau so ein verdammter Abschaum, der nur an sich selbst denkt... Longway. Genau wie deine Schwester. Meine Familie wird den Tag überleben. Deine - wird es nicht. Fahr zur Hölle!";
			link.l2.go = "PZ_Longway_SisterDialog_Ubezhdaet8_1";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet8_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetFightMode(pchar, true);
			DoQuestCheckDelay("PZ_ChangShinAndLongwayFightMe", 0.5);
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet9":
			dialog.text = "Wenn die Wahl zwischen dir und meiner Familie besteht - Ich wähle immer noch die Familie, auch wenn es eine schwere Wahl ist.";
			link.l1 = "Eine Familie, die keinen Finger gerührt hat, während du all diese Jahre nach ihr gesucht hast? Oh, aber dann kam einfach die richtige Zeit! Was mich betrifft, habe ich alles aufgegeben, um dir zu helfen. Du, der du hier stehst, bist das Ergebnis davon. Verdammt, ich bin dir näher als Familie, als sie es ist, mein Freund!";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet10";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet10":
			dialog.text = "Du hast recht. Wie immer hast du recht. Wirst du mir vergeben, Herr Kapitän?";
			link.l1 = "Es gibt nichts zu vergeben! Sie haben in einer Sache recht - ich war nicht immer der Kapitän, den Sie verdienen. Ich denke, das macht uns jetzt gleich. Übrigens, wie möchten Sie, dass ich Sie ab jetzt anspreche? Longway? Oder ist es Chang Tu?";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet11";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet11":
			dialog.text = "Lassen Sie es Longway sein. Ich bin es bereits gewohnt, dass Sie mich so ansprechen.";
			link.l1 = "Dann vergessen wir alle Meinungsverschiedenheiten und heißen Sie an Bord willkommen, Longway.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet12";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet12":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_Ubezhdaet13", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet13":
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			dialog.text = "Tu! Was sagst du?! Warum hast du aufgehört?! Töte ihn! Du wirst für ihn immer nur ein Arbeiter sein! Deine Familie bin ich und nur ich!";
			link.l1 = "Sie ist so wütend, nicht wahr, Longway? Du bist nicht mehr seine Familie, Xing. Das endete, als du von Longways Ankunft im Archipel erfuhrst und beschlossen hast, sie zu ignorieren. Wir gehen.";
			link.l1.go = "PZ_Longway_SisterDialog_Ubezhdaet14";
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet14":
			dialog.text = "Ich vermute, ich hatte nie eine echte Chance, diese Sklavenmentalität aus ihm herauszutreiben. Ich kann ihn nicht retten. Dann werde ich euch beide selbst töten.";
			link.l1 = "Sie sind derjenige hier, der nicht gerettet werden kann. Sie wissen, ich war zu verständnisvoll und nachsichtig mit Ihnen. Aber das ist noch besser. Ich denke, sogar Longway hat erkannt, was für eine Schlange Sie sind. Er wird Sie nicht allzu sehr betrauern.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_SisterDialog_Ubezhdaet15":
			dialog.text = "Witze sind jetzt unangebracht! Du versteckst deine Angst und dein Versagen dahinter! Was mich nur noch mehr überzeugt. Verteidige dich, de Maure! Denn Chang Tu hat nicht vor, dir zu schonen.";
			link.l1 = "Es tut mir leid, dass es so enden musste. Aber wenn das der Weg ist, den du wählst, dann sei es so. In diesem Fall wirst du auch keine Gnade von mir erhalten.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaDevushek":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) StartInstantDialog("Mary", "PZ_Longway_SisterDialog_ReactiaMary", "Quest\CompanionQuests\Longway.c");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Charles, hör zu...";
				link.l1 = "Helen?";
			}
			else
			{
				dialog.text = "Charles, Longway, halt ...";
				link.l1 = "Helen, du solltest dich besser hinter mich stellen. Ich würde mich sicherer fühlen, falls sie uns angreifen.";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena2":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "I'm so tired; I can hardly stand. I just want to get out of here. We're not going to drag Longway back to the ship if he doesn't want to come, are we? I'll be your navigator and first mate, my Captain. Hopefully, your most trusted and beloved too. Besides, he's got a point - we're not his family. She is, for better or worse.";
				link.l1 = "But what about her? She's the reason you were tortured; it was all her idea. And she's the one who kidnapped you.";
			}
			else
			{
				dialog.text = "Aber sie werden es nicht tun, oder? Lassen wir einfach jetzt los, das ist alles. Wenn er so über uns denkt, nach allem, was wir für ihn getan haben, hat es keinen Sinn, seine Meinung zu ändern. Taten sprechen lauter als Worte. Wenn er bei seiner Schwester bleiben will, lass ihn.";
				link.l1 = "Helen, du hast so viel wegen ihr gelitten...";
			}
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena3":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayHochetMira"))
			{
				dialog.text = "Lasst diese Teufelin mit ihren Dämonen allein. Sie werden ihre Seele bald genug verzehren. Und unsere verdienen eine gute Ruhe. Lass uns gehen.";
				link.l1 = "Ja. Ich denke, wir sollten. Lass uns hier raus, mein Engel. Und du - Longway, oder Chang Tu - auf Wiedersehen.";
			}
			else
			{
				dialog.text = "Aber ich bin nicht gestorben. Und das Schlimmste ist nicht passiert. Ich bin hier, mit dir, und das ist es, was zählt. Und Levasseur ist tot. Ohne ihn ist sie nichts. Ihr Platz verliert Geld und wird bald untergehen. Und sie werden mit ihm untergehen. Lass uns gehen, mein Kapitän. Es gibt hier nichts mehr für uns zu tun.";
				link.l1 = "Ich werde nicht streiten, Helen.";
			}
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena4":
			StartInstantDialog("Helena", "PZ_Longway_SisterDialog_ReactiaHelena5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena5":
			dialog.text = "Wohin gehst du?";
			link.l1 = "Was, überrascht, dass wir nicht begierig darauf sind, deine und die Eingeweide deiner Schwester zu vergießen, Longway? Das ist der Unterschied zwischen uns. Und du denkst immer noch, ich bin der Bösewicht... Aber gut, schau. Wenn du mich töten willst, bedeutet das, dass du auch Helen töten musst. Sie ist verwundet, verletzt. Willst du das wirklich tun?";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena6":
			dialog.text = "Mm-hmm.";
			link.l1 = "Ich kann den Zweifel in deinen Augen sehen, obwohl du viele Groll gegen mich hast. Aber nehmen wir beide uns ein Beispiel an Helen, nicht wahr? Niemand in unserer Besatzung ist freundlicher oder vergebender als sie. Wir gehen. Und wenn in dir noch irgendeine Güte oder Vernunft übrig ist, wirst du uns nicht in den Weg stellen.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaHelena7";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaHelena7":
			dialog.text = "Sei es so. Ich entschuldige mich. Aber du bist nicht mehr mein Kapitän.";
			link.l1 = "Ich werde es irgendwie überstehen. Ich wünsche dir und deiner Schwester das Beste, trotz dessen, was sie getan hat. Auf Wiedersehen, Longway.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_BrothelTeleportVZal");		//Мирно разошлись
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary":
			dialog.text = "Los geht's, Charles, es ist Zeit, diese Meuterei auszurotten.";
			link.l1 = "Gott weiß, dass ich das nicht tun wollte... und ich will es immer noch nicht.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary2";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary2":
			dialog.text = "Du tust es nicht?! Charles, hör mir zu. Du hast so viel für ihn getan, und was hast du dafür bekommen? Verrat und üble Worte, ja, gell! Wirst du das wirklich durchgehen lassen?";
			link.l1 = "Ich möchte nicht Longways Blut vergießen. Ich habe nicht vergessen, dass wir einst Freunde waren.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary3";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary3":
			dialog.text = "Freunde wie diese kannst du vergessen - sie sind schlimmer als Feinde, ja, gell! Charles, sieh mich an. Sieh, was mir passiert ist - wegen seiner Schwester, die mich verspottet, beleidigt und gedemütigt hat auf dem Weg zu dieser verdammten Insel!";
			link.l1 = "Mary, ich verstehe - du bist gerade sehr, sehr wütend ...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary4";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary4":
			dialog.text = "Oh nein, Charles, ich bin nicht nur wütend, nein... Ich bin rasend! Und nicht nur wegen dem, was dieser elende kleine Bastard zu dir gesagt hat! Schau mich noch einmal an, Charles - und stelle dir vor, wie viele weitere Mädchen das durchmachen müssen, wenn wir dem nicht ein Ende setzen. Hier und jetzt.";
			link.l1 = "Sie werden niemandem mehr wehtun. Levasseur ist tot.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary5";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary5":
			dialog.text = "Charles, hast du wirklich zugehört, was für Ketzereien sie von sich gegeben hat? Sie ist genauso verantwortlich für das, was in diesem Keller passiert ist, wie dieser stinkende Schweinehund. Schau dir nur Longway an - oder wie auch immer er jetzt heißt. Siehst du, wie schnell sie ihn auf ihre Seite gebracht hat, ja, gell! Wer weiß, was für kranke Ideen sie dem Verräter noch einflößen wird? Glaubst du, dass diese Dämonin viel Mühe haben wird, ihn auf Levasseurs Weg zu stoßen? Denk nicht darüber nach, was er jetzt ist, Charles. Denk darüber nach, was für ein Monster er in einem Jahr... oder sogar in einem Monat werden könnte. Du weißt, dass ich recht habe, oder?";
			link.l1 = "So sehr ich es auch hasse, zuzugeben, ich habe nichts, um dir zu widersprechen, Mary...";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary6";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary6":
			StartInstantDialog("PZ_ChangShin", "PZ_Longway_SisterDialog_ReactiaMary7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary7":
			dialog.text = "Ha-ha-ha! Faszinierend, was für eine Vorstellung. Ich habe schon lange nicht mehr so herzhaft gelacht. Und sie hat Mut, das muss ich ihr zugestehen.";
			link.l1 = "Schließe dein Maul, du Hündin.";
			link.l1.go = "PZ_Longway_SisterDialog_ReactiaMary8";
		break;
		
		case "PZ_Longway_SisterDialog_ReactiaMary8":
			dialog.text = "Das ist amüsant, nicht wahr, de Maure? Ich würde es lieben, zu sehen, wie Tu dich selbst zu Fall bringt. Und hier ist deine Frau genauso blutrünstig wie ich. Sehr gut. Ich werde nicht untätig daneben stehen-Ich habe mit Levasseur und einigen von Tortugas Top-Hunden trainiert. Mal sehen, welches Duo am Ende oben steht.";
			link.l1 = "Sie hatten keinen sehr guten Lehrer. Und Sie haben Mary verärgert. Sie sind erledigt. Selbst wenn ich nicht hier wäre, hätte Ihr Duo keine Chance gegen sie.";
			link.l1.go = "exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinAndLongwayFightMe");
		break;
		
		case "PZ_Longway_SisterDialog6":
			dialog.text = "Ja. Endlich. Darf Longway wieder mit meiner Schwester sprechen, Herr Kapitän? Nicht lange.";
			link.l1 = "Natürlich. Mach es einfach schnell - wir haben nicht viel Zeit.";
			link.l1.go = "PZ_Longway_SisterDialog7";
		break;
		
		case "PZ_Longway_SisterDialog7":
			dialog.text = "Longway, mach es schnell.";
			link.l1 = "Gut.";
			link.l1.go = "PZ_Longway_SisterDialog7_1";
		break;
		
		case "PZ_ChangShin26":
			StartInstantDialog("СhangShin", "PZ_Longway_SisterDialog7_1", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_Longway_SisterDialog7_1":
			locCameraFromToPos(0.65, 2.59, -3.06, true, 0.23, 0.34, -5.21);
			
			sld = characterFromId("Longway");
			ChangeCharacterAddressGroup(sld, "Tortuga_brothelElite_room2", "goto", "goto8");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("PZ_ChangShin"));
			
			sld = characterFromId("PZ_ChangShin");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromId("Longway"));
			
			dialog.text = "Und was wolltest du mir erzählen, mein Bruder?";
			link.l1 = "Dieser Longway ist sehr enttäuscht von dir, Xing.";
			link.l1.go = "PZ_Longway_SisterDialog8";
		break;
		
		case "PZ_Longway_SisterDialog8":
			dialog.text = "(Auf Mandarin) Warum sprichst du unsere Sprache nicht, da du wieder reden wolltest, Tu? Schämst du dich für ihn? Wenn ich du wäre, würde ich mich eher für deinen Akzent schämen.";
			link.l1 = "Nein. Longway hat keine Geheimnisse vor dem Herrn Kapitän. Nicht mehr.";
			link.l1.go = "PZ_Longway_SisterDialog9";
		break;
		
		case "PZ_Longway_SisterDialog9":
			dialog.text = "(auf Französisch) Zuerst Rodenburg, jetzt de Maure. Du brauchst immer einen 'Monsieur'. Du hast hier in über einem Dutzend Jahren nichts erreicht. Du kannst nicht einmal eine ihrer Sprachen lernen. Und sie sind so viel einfacher als unsere! Wenn jemand eine Enttäuschung ist, dann bist du es.";
			link.l1 = "Aber ich handele nicht mit Frauen. Ich beteilige mich nicht an ihrer Entführung und Folter.";
			link.l1.go = "PZ_Longway_SisterDialog10";
		break;
		
		case "PZ_Longway_SisterDialog10":
			dialog.text = "Sind Sie ernsthaft? Soll ich auflisten, was Sie für Rodenburg getan haben? Was ich getan habe, wäre im Vergleich dazu ein Kinderspiel.";
			link.l1 = "Ich hatte ein Ziel - dich zu finden. Aber du wolltest mich nicht einmal sehen. Und als ich dich fand, fand ich ein Monster, nicht den warmen Leitstern, der einst meinen Weg erhellte.";
			link.l1.go = "PZ_Longway_SisterDialog11";
		break;
		
		case "PZ_Longway_SisterDialog11":
			dialog.text = "Ein Monster? Nun, vielleicht hast du recht. Ich bin nicht mehr das fröhliche Mädchen, das du kanntest. Wäre ich so geblieben, hätte das Leben mich zerkaut und ausgespuckt. Ich musste meine eigenen Zähne wachsen lassen. Mein Stern ist längst erloschen. Aber ich bin immer noch deine Schwester, Tu.";
			link.l1 = "Nein. Du bist nicht mehr meine Schwester.";
			link.l1.go = "PZ_Longway_SisterDialog12";
		break;
		
		case "PZ_Longway_SisterDialog12":
			dialog.text = "Aufgeben so leicht nach all diesen Jahren? Heh... Und wer weiß, vielleicht wäre ich immer noch der Gleiche, wenn du es rechtzeitig nach Hause geschafft hättest, um Fermentelos an diesem Tag zu töten?";
			link.l1 = "Du hast recht. Es ist teilweise auch meine Schuld. Es ist meine Verantwortung. Und ich werde es beenden. Ich werde dir dein Leiden ersparen. Beende diese elende Existenz.";
			link.l1.go = "PZ_Longway_SisterDialog13";
		break;
		
		case "PZ_Longway_SisterDialog13":
			dialog.text = "Wirst du wirklich deine eigene Schwester töten, Chung Tu? Nicht, dass du Erfolg haben wirst, aber die Tatsache ist...";
			link.l1 = "Du bist nicht länger meine Schwester. Xing starb vor zehn Jahren. Und heute ist der Tag, an dem Chung Tu endlich stirbt. Von nun an und für immer ist mein Name... Longway.";
			link.l1.go = "Exit";
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddDialogExitQuest("MainHeroFightModeOn");
			AddDialogExitQuest("PZ_ChangShinFightWithLongway");
		break;
		
		case "PZ_Longway_FlagMartinInfo_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Zuerst retten wir Chang Xing.";
			link.l1 = "Was?! Sie scheinen es nicht zu verstehen, mein Freund. Ihre Schwester ist nicht in unmittelbarer Gefahr, aber "+sStr+" ist. Und muss ich Sie daran erinnern, dass Chang Xing genauso schuld an all dem ist wie Martene und Thibaut?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Das ist nicht wahr! Sie ist...";
			link.l1 = "Haben Sie eine Ahnung, was Levasseur anstellen könnte "+sStr+" während wir hier streiten?";
			link.l1.go = "PZ_Longway_FlagMartinInfo_3";
		break;
		
		case "PZ_Longway_FlagMartinInfo_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Aber Chang Xing ist alles, was mir noch geblieben ist, Kapitän... Ihre Familie ist noch intakt...";
			link.l1 = +sStr+" mag nicht meine Frau sein, aber sie ist mir so lieb wie meine eigene Familie.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_4";
		break;
		
		case "PZ_Longway_FlagMartinInfo_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Chang Xing ist mein letzter Leitstern, Kapitän. Außerdem schulden Sie mir für das Geständnis, das wir aus Robert Marten herausgeholt haben.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") && CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
			{
				link.l1 = "Wir werden nach deiner Schwester suchen, das verspreche ich. Aber Levasseur hat sie all diese Zeit nicht berührt. "+sStr+" ist in weit größerer Gefahr als Chang Xing. Hilf mir, sie zuerst zu retten, und ich schulde dir einen großen Gefallen.";
				link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_FlagArhiv") || CheckAttribute(pchar, "questTemp.PZ_FlagShip"))
				{
					if (IsCharacterPerkOn(pchar, "Trustworthy") && GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 85)
					{
						link.l1 = "(Vertrauenswürdig) (Führung) Wir werden nach deiner Schwester suchen, das verspreche ich. Aber Levasseur hat sie die ganze Zeit nicht berührt. "+sStr+" ist in weit größerer Gefahr als Chang Xing. Hilf mir, sie zuerst zu retten, und ich schulde dir einen großen Gefallen.";
						link.l1.go = "PZ_Longway_FlagMartinInfo_VD1";
						notification("Trustworthy", "Trustworthy");
						notification("Skill Check Passed", SKILL_LEADERSHIP);
					}
					else
					{
						link.l1 = "Hören Sie mir zu! Ihre Schwester ist sicher. Aber "+sStr+" ist jetzt in den Händen eines Perversen, der sie gerade quälen könnte - oder schlimmer! Glauben Sie, Levasseur würde Ihrer Schwester erlauben, ein so nobles Etablissement zu besitzen, wenn er sie wie andere arme Mädchen in seinem Verlies behandeln würde?!";
						link.l1.go = "PZ_Longway_FlagMartinInfo_netVD1";
						if (!IsCharacterPerkOn(pchar, "Trustworthy")) notification("Perk Check Failed", "Trustworthy");
						if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 85) notification("Skill Check Failed (85)", SKILL_LEADERSHIP);
					}
				}
			}
			link.l2 = "Ich werde keine Zeit mit sinnlosen Streitigkeiten verschwenden. Jeder von uns hat seine eigenen Prioritäten. Lassen wir uns wieder trennen. Möge mein Gott mir helfen und deiner dir.";
			link.l2.go = "PZ_Longway_FlagMartinInfo_Razdelimsya";
			link.l3 = "Du hast recht. Ich schulde dir was. Gut, mach es auf deine Weise. Außerdem könnte ich ohne dich vielleicht nicht mit Levasseur und seinen Männern fertig werden. Aber wenn etwas passiert mit "+sStr+" während wir uns um deine Schwester kümmern...";
			link.l3.go = "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya";
		break;
		
		case "PZ_Longway_FlagMartinInfo_Razdelimsya":
			dialog.text = "Danke für Ihr Verständnis, Herr Kapitän. Viel Glück Ihnen!";
			link.l1 = "Und dir, Longway.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_IdemKSestreLongweya":
			dialog.text = "Leere Drohungen sind leere Drohungen, Herr Kapitän. Wir müssen uns beeilen, damit wir rechtzeitig für alles da sind.";
			link.l1 = "Ich hoffe, dein Gott hört es. Lass uns gehen!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TogetherLongwayGo");
		break;
		
		case "PZ_Longway_FlagMartinInfo_netVD1":
			dialog.text = "'Ich werde das aus Respekt vorbei gehen lassen, Herr Kapitän. Nur dieses eine Mal. Nächstes Mal werde ich dich schlagen. Ich suche jetzt nach meiner Schwester, mit oder ohne deine Zustimmung.";
			link.l1 = "Ich werde keine Zeit mehr damit verschwenden, mit dir zu streiten, Longway. Letztendlich haben wir alle etwas, das uns teurer ist als alles andere.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie";
		break;
		
		case "PZ_Longway_FlagMartinInfo_SharleOdinVPodzemelie":
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD1":
			dialog.text = "Mm-hmm, in Ordnung, Herr Kapitän. Aber dann müssen wir uns beeilen.";
			link.l1 = "Richtig. Danke, Longway.";
			link.l1.go = "PZ_Longway_FlagMartinInfo_VD2";
		break;
		
		case "PZ_Longway_FlagMartinInfo_VD2":
			pchar.questTemp.PZ_LongwayRyadom = true;
			pchar.questTemp.PZ_DevushkaRanena_Legko = true;
			LAi_LocationDisableOfficersGen("Tortuga_Cave", true);
			DoQuestReloadToLocation("Tortuga_Cave", "reload", "reload2", "PZ_Etap6TortugaPodzemelie");
		break;
		
		case "PZ_TortureRoom_Levasser_1":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Nun, nun, wen zum Teufel haben wir denn hier... Verdammt. Charles de Maure und sein schieläugiger Köter.";
				link.l1 = "Es gibt hier nur einen Köter. Wenn Sie ihn sehen wollen, schauen Sie in den Spiegel, Sie Hugenottenbastard. Oder schauen Sie einfach Ihren Neffen an. Obwohl, er sieht eher aus wie eine räudige Ratte.";
				link.l1.go = "PZ_TortureRoom_Levasser_2";
			}
			else
			{
				dialog.text = "Ich habe dir gesagt, du sollst mich nicht stören! Ah, Charles de Maure, hehehe. Was für ein hartnäckiger kleiner Schädling.";
				link.l1 = "So bin ich eben. Jetzt halt die verdammte Klappe und...";
				link.l1.go = "PZ_TortureRoom_Levasser_1_1";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne") || CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo") || CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal")) Achievment_Set("ach_CL_130");
			}
			locCameraSleep(true);
			sld = CharacterFromID("Tibo");
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_1_1":
			dialog.text = "Du bist nicht auf deinem eigenen Schiff, Welpe! Es gibt nur einen Mann auf dieser Insel, und das bin ich!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
		break;
		
		case "PZ_TortureRoom_Levasser_2":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_3":
			dialog.text = "Wie kannst du es wagen, du Abschaum!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_4";
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_4":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_5":
			dialog.text = "Beruhige dich, Neffe! Monsieur de Maure wird eine Lektion in gutem Benehmen bekommen.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya9");
			sld = CharacterFromID("Tibo");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_6":
			if (!CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Habe ich dir die Erlaubnis gegeben zu quieken?!";
			}
			else
			{
				dialog.text = "Wo ist all das Feuer hin, huh, hübsches Ding? Ah, ich glaube, ich verstehe es...";
			}
			link.l1 = "Lass sie in Ruhe, du Bastard!";
			link.l1.go = "PZ_TortureRoom_Levasser_7";
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Mary"));
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) LAi_ActorTurnToCharacter(npchar, CharacterFromID("Helena"));
		break;
		
		case "PZ_TortureRoom_Levasser_7":
			dialog.text = "Heh-heh-heh... Du kannst schreien und mich beleidigen, so viel du willst, aber ich sehe, wie du zitterst wie ein Blatt im Wind. Ich sehe die Angst in deinen Augen. Du und Henri habt das gemeinsam. Nichts für ungut, Neffe.";
			link.l1 = "Du hast recht, es ist Angst. Aber nicht vor dir, Abschaum.";
			link.l1.go = "PZ_TortureRoom_Levasser_7_1";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_7_1":
			dialog.text = "Natürlich, natürlich. Ich habe das alles schon gehört - dass du vor niemandem Angst hast, de Maure. Sie hat mir das erzählt. 'O-oh, Charles wird kommen, Charles wird mich retten... Charles dies, Charles das...' Nun, Charles ist hier. Charles hat einen Platz in der ersten Reihe. Henri, mach unseren Gast bequem.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_8";
		break;
		
		case "PZ_TortureRoom_Levasser_8":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_9", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_9":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Das ist nicht nötig, Onkel. Ich fürchte, dieses Mal bist du ein bisschen zu weit gegangen...";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Onkel, ich werde deine Hilfe bei dieser Sache brauchen...";
				}
				else
				{
					dialog.text = "Soll ich ihn fertigmachen, Onkel, oder soll er zuerst zusehen?";
				}
			}
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_10";
			LAi_SetActorType(npchar);
			//LAi_ActorTurnToCharacter(npchar, CharacterFromID("Levasser"));
			LAi_ActorTurnToLocator(npchar, "goto", "goto8");
			locCameraFromToPos(-15.67, 2.57, -1.23, true, -17.49, 1.42, -3.26);
		break;
		
		case "PZ_TortureRoom_Levasser_10":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_11", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_11":
			if (CheckAttribute(pchar, "questTemp.PZ_Etap6_Opozdal"))
			{
				dialog.text = "Es war nicht ich, es war Monsieur Weißer Ritter hier, der zu lange gebraucht hat, um zur Rettung zu kommen. Sieht so aus, als wäre die Show vorbei, ha-ha-ha-ha!";
				link.l1 = "Gott, nein...";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_DevushkaMertva");
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Ich dachte es mir. Wie haben Sie es geschafft, bis zu diesem Alter zu leben? Übrigens, dieselbe Frage an Sie, de Maure.";
					link.l1 = "Sie haben keine Ahnung, wie viele Fragen ich für Sie habe, Schlächter!";
				}
				else
				{
					dialog.text = "Ich wünschte, unsere kleine Vorstellung hätte ein Publikum... Aber ich glaube nicht, dass Monsieur Sturkopf uns dieses Vergnügen bereiten wird.";
					link.l1 = "Das einzige Vergnügen, das jemand bekommt, bin ich - indem ich dich ausnehme, Schlächter!";
				}
				link.l1.go = "PZ_TortureRoom_Levasser_14";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				locCameraFromToPos(-16.74, 2.58, -0.51, true, -13.13, -0.72, 2.49);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
			{
				locCameraFromToPos(-18.38, 1.77, 2.73, true, -20.53, 0.01, 0.32);
			}
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
			{
				locCameraFromToPos(-16.97, 2.09, 3.98, true, -20.02, -0.17, 2.28);
			}
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_12":
			dialog.text = "Los, geh schon und heb sie auf! Ha-ha-ha!";
			link.l1 = "Verfluchte Tiere, ich werde es euch bereuen lassen, geboren zu sein!";
			link.l1.go = "PZ_TortureRoom_Levasser_13";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_13":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				Return_LongwayOfficer();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PZ_TortureRoom_Levasser_DevushkaMertva5");
		break;
		
		case "PZ_TortureRoom_Levasser_14":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Metzger? Ich betrachte mich eher als Künstler, als Maler - würden Sie es zumindest versuchen, es als Kunst zu sehen... Schauen Sie.\nMögen Sie meine Arbeit? Wahrlich eines meiner Meisterwerke. Um ganz ehrlich zu sein, bevorzuge ich Blondinen, aber sie... Am Ende habe ich ihr diese hässliche Haarfarbe verziehen. Es war nicht nur das Haar - das Mädchen ist wie Feuer! Ich habe mich fast verbrannt. Sie hat gekämpft, gebissen, geknurrt wie ein wildes Tier! Erinnerte mich an einen rothäutigen Wilden, mit dem ich viel Spaß hatte, auch wenn nicht lange...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Metzger? Ich sehe mich eher als Künstler, als Maler - würdest du es wenigstens als Kunst betrachten... Beobachte.\nSiehst du, ich bin noch nicht mit ihr fertig - es gibt noch viel leeren Raum auf dieser Leinwand. Sie ist nicht nur schön, sondern auch hart wie ein Felsen und kalt wie Eis. Ich musste sogar ein bisschen schwitzen, um sie zum Schreien zu bringen. Sie hat bis zum Ende durchgehalten, nur um mir das Vergnügen zu verwehren, ihre schöne Stimme zu hören.";
			}
			link.l1 = "Gib sie jetzt frei, du Degenerierter.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_Etap6TortugaPytochnaya13");
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_15":
			dialog.text = "Wohin glaubst du, gehst du? Dieses Stück Fleisch gehört jetzt mir. Genau wie alles herum - diese Stadt, diese Festung... Ich bin Tortuga. Und du und Poincy, dieser stinkende alte Truthahn, könnt das nie ändern.";
			link.l1 = "Levasseur, du...";
			link.l1.go = "PZ_TortureRoom_Levasser_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "PZ_TortureRoom_Levasser_16":
			dialog.text = "Es ist Signor de René de Buaduflé de Lettre für dich.";
			link.l1 = "Ich gebe einen Dreck darauf. Zieh dein Schwert und zeig mir, was du in einem Kampf wert bist - mit einem Mann, nicht einem wehrlosen Mädchen.";
			link.l1.go = "PZ_TortureRoom_Levasser_17";
		break;
		
		case "PZ_TortureRoom_Levasser_17":
			dialog.text = "Und was für ein Mann du bist! Aber du hast recht, auch mir ist all dieses Gerede leid. Ich will zurück zu... meiner Dame. Aber eine letzte Frage werde ich dir noch stellen. Wie bist du hierher gekommen? Wer hat den Standort dieses Ortes verraten? Nur eine Handvoll Menschen wissen davon.";
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMartinInfo"))
			{
				link.l1 = "Euer gemeinsamer Freund, Martene, hat gesungen wie eine Nachtigall. Eigentlich, eher gequiekt wie ein Schwein im Schlachthaus...";
				link.l1.go = "PZ_TortureRoom_Levasser_FlagMartinInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagMarselinaInfo"))
			{
				link.l2 = "Vielleicht ist es besser, es vor Ihnen geheim zu halten. Ich fürchte, es könnte Ihr Ego verletzen, Signor de René... etwas.";
				link.l2.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l3 = "Eines deiner Opfer, Levasseur.";
				link.l3.go = "PZ_TortureRoom_Levasser_FlagShinInfo_1";
			}
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_1":
			dialog.text = "Lügner, du Schurke! Niemand verlässt diese Mauern!";
			link.l1 = "Benutze dein Gedächtnis, komm schon. Es gab einen. Chang Xing.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagShinInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagShinInfo_2":
			dialog.text = "Auf keinen Fall. Nicht sie. Einige meiner Ideen stammen von diesem kleinen Teufel. Oh-oh, wir haben uns viel beigebracht, hehe. Hat sie sich entschieden, am Ende ihr Gewissen zu bereinigen? Ich bezweifle es. Schließlich habe ich es ihr vor langer Zeit ausgetrieben!";
			link.l1 = "Jetzt werde ich dich austrocknen. Tropfen für Tropfen.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMartinInfo_1":
			dialog.text = "Und du nennst mich einen Schlächter, du elender Heuchler! Heh-heh... Aber solange er in der Hölle brennt, habe ich nichts zu befürchten.";
			link.l1 = "Er wartet dort auf Sie. Und auch Ihr Schurke von einem Neffen. Lassen wir ihn nicht enttäuscht sein.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_1":
			dialog.text = "Wie wäre es, wenn ich dieses Spielzeug ein wenig mehr verletze? Schlitz ihr den Bauch oder die Kehle auf und schau zu, wie sie ausblutet, während du versuchst, zu ihr herunterzukommen...";
			link.l1 = "Was auch immer du sagst, Levasseur, was auch immer du sagst... Deine Frau lässt dich grüßen. Und dazu, einen Abschiedsgruß.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_2":
			dialog.text = "WAS?! Kha-kha... Verfickte Marceline... Du elendige Schlampe, Schlampe, Schlampe, Schlampe!";
			link.l1 = "Das ist sie. Ihr seid einander würdig. Sie ist allerdings ein bisschen besser, wenn sie einen klaren Kopf hat. Zumindest auf den ersten Blick.";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_3":
			dialog.text = "Ich werde ihren Hühnerkopf auf einen Spieß stecken. Aber davor... oh-oh, dieser Hure wird vieles zustoßen.... Ich werde sogar meinem neuen Spielzeug eine Pause gönnen. Warte! Ich habe eine bessere Idee. Ich werde sie Henri leihen. Natürlich nur für eine Weile.";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4";
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_4":
			StartInstantDialog("Tibo", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_5":
			dialog.text = "Wirklich? Danke, Onkel!";
			link.l1 = "";
			link.l1.go = "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6";
			CharacterTurnByChr(npchar, CharacterFromID("Levasser"));
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_6":
			StartInstantDialog("Levasser", "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_FlagMarselinaInfo_7":
			dialog.text = "Verdien es zuerst - hilf mir mit diesem hier, ja?";
			link.l1 = "Er steht kurz davor, die Beherrschung zu verlieren.";
			link.l1.go = "PZ_TortureRoom_Levasser_Bitva";
			CharacterTurnByChr(npchar, CharacterFromID("Tibo"));
		break;
		
		case "PZ_TortureRoom_Levasser_Bitva":
			DialogExit();
			EndQuestMovie();
			locCameraSleep(false);
			DeleteAttribute(pchar, "GenQuest.BlockDialogCamera");
			LAi_SetPlayerType(pchar);
			locCameraTarget(PChar);
			locCameraFollow();
			
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
				Return_LongwayOfficer();
				PlaySound("VOICE\Russian\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
			LAi_SetImmortal(sld, true);
			
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("Levasser");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "PZ_Etap6TortugaPytochnaya19");
			sld = CharacterFromID("Tibo");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		
		case "PZ_TortureRoom_Longway_1":
			dialog.text = "Mein Herr Kapitän... Longway bietet sein Beileid an. Wir haben alles getan, was wir konnten.";
			link.l1 = "Nicht alles, bei weitem nicht genug.";
			link.l1.go = "PZ_TortureRoom_Longway_2";
		break;
		
		case "PZ_TortureRoom_Longway_2":
			dialog.text = "Longway wird Chang Xing finden. Kommst du mit mir?";
			link.l1 = "Ja, ich gehe mit dir, Longway. Aber erinnere dich - auch deine Schwester hatte einen sehr aktiven Teil an diesem blutigen Spektakel. Sie wird sehr hart arbeiten müssen, um mich davon zu überzeugen, sie zu verschonen. Und du wirst ihr nicht helfen. Jetzt komm, es ist Zeit, damit zu enden.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Longway_3":
			DialogExit();
			Return_LongwayOfficer();
			chrDisableReloadToLocation = false;
		break;
		
		case "PZ_TortureRoom_Devushka_1":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Charles, ich wusste es, ja, gell! Ich wusste, dass du kommen würdest! Du tust es immer, nicht wahr?";
					link.l1 = "Ich würde das nicht zum vierten Mal testen wollen, Mary... Diese Schurken, sie...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Oh, mein Kapitän, Sie ahnen nicht, wie rechtzeitig Sie sind. Diese... diese Monster...";
					link.l1 = "Es ist jetzt vorbei, Helen. Es ist in Ordnung, es ist alles vorbei. Oh mein Gott, was haben sie dir angetan...";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Charles, du bist hier! Ich wusste es, ich wusste es, ja, gell!";
					link.l1 = "Ich segelte mit voller Fahrt, rannte um mein Leben, Mary. Du... haben sie?..";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Mein Kapitän... Du bist hier... Ich hatte fast die Hoffnung verloren...";
					link.l1 = "Ich bin so schnell gekommen, wie ich konnte, Helen. Es tut mir leid, dass es so lange gedauert hat.";
				}
				locCameraFromToPos(-15.32, 1.24, 1.31, true, -14.25, -1.00, -1.50);
			}
			link.l1.go = "PZ_TortureRoom_Devushka_2";
		break;
		
		case "PZ_TortureRoom_Devushka_2":
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Nein, Charles, nein. Sie haben es versucht, aber ich habe sie so gut ich konnte abgewehrt. Deshalb haben sie mich so schlimm verprügelt... Bitte, Charles, lass uns hier raus... ja, gell?";
					link.l1 = "Sofort, meine Liebe. Noch eine letzte Sache zu erledigen.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Sie haben es nicht getan, Charles! Sie haben es nicht getan. Der Rest wird heilen. Bitte, bring mich von hier weg.";
					link.l1 = "Natürlich, meine Liebe. Es bleibt nur noch eine Sache zu tun.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Nein, Charles, nein. Sie haben es versucht, aber du hast es gerade noch rechtzeitig geschafft. Wie damals. Wie oft ist das jetzt schon?";
					link.l1 = "Ich habe nicht gezählt, Mary. Und ich werde es nie tun.";
					link.l1.go = "PZ_TortureRoom_Devushka_2_1";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Du bist hier angekommen... gerade rechtzeitig. Das Schlimmste ist nicht passiert. Jetzt, bitte, lass uns hier rauskommen. Irgendwohin.";
					link.l1 = "Steh auf, Helen. Geh nach oben. Ich muss mich erst um diesen Schurken kümmern.";
					link.l1.go = "PZ_TortureRoom_Devushka_3";
				}
			}
		break;
		
		case "PZ_TortureRoom_Devushka_2_1":
			dialog.text = "Und ich werde nicht aufhören zu zählen. Lassen wir diesen Ort jetzt bitte.";
			link.l1 = "Natürlich, meine Liebe. Es gibt nichts mehr für uns hier zu tun. Außer einer Sache.";
			link.l1.go = "PZ_TortureRoom_Longway_3";
		break;
		
		case "PZ_TortureRoom_Devushka_3":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko")) AddPassenger(pchar, npchar, false);
			LAi_SetPlayerType(pchar);
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
		break;
		
		case "PZ_TortureRoom_Levasser_18":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Na und, kha-kha, hast du keine Eier, Rotznase? Bittet doch euer gelbärschiges Wildschwein um Hilfe... Oder mach es selbst und dann hast du einen Grund, Poincy zu erzählen, wie mutig du bist.";
				link.l1 = "Ich würde lieber allen erzählen, was für ein feiger Stück Scheiße du warst.";
			}
			else
			{
				dialog.text = "Was, willst du wirklich zusehen, wie ich verblute? Du genießt es, nicht wahr? Du wirst deiner Frau erzählen, was für ein Held du bist. Siehst du dieses Skelett dort an der Wand? Die Frau des Bankiers von Santiago... Ihr Mann dachte auch, er wäre ein Held, aber er stellte sich als guter Schreier heraus - als ich ihn auf diesem Rad drehte...";
				link.l1 = "Ich könnte deinen Kadaver darauf rollen, du Abschaum, aber ich fürchte, es würde das Gewicht deines Arsches nicht tragen.";
			}
			link.l1.go = "PZ_TortureRoom_Levasser_19";
		break;
		
		case "PZ_TortureRoom_Levasser_19":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
			{
				dialog.text = "Feige? Oh, kha-kha, komm schon...";
				link.l1 = "Grausamkeit ist nicht das Gegenteil von Feigheit. Aber jemand wie du würde den Unterschied nicht kennen.";
				link.l1.go = "PZ_TortureRoom_Levasser_20";
			}
			else
			{
				dialog.text = "Das ist sehr klug. Merk dir meine Worte, de Maure: du wirst genauso sterben wie dieser Großkopferte, heiser von deinen eigenen Schreien und taub von den Schreien deiner...";
				link.l1 = "Brenne in der Hölle, Abschaum.";
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
			}
		break;
		
		case "PZ_TortureRoom_Levasser_20":
			dialog.text = "Ja, ich bin kein großer Philosoph, das gebe ich zu. Siehst du dieses Skelett an der Wand, de Maure? Das ist alles, was von der Frau des Bankiers von Santiago übrig bleibt. Er mochte es auch, große Reden zu schwingen, aber all das hörte auf, als ich anfing, seinen Körper auf dieses Rad zu wickeln. Alles, was übrig blieb, war das Schreien, das mich fast taub machte...";
			link.l1 = "Lassen Sie uns dies hinter uns bringen.";
			link.l1.go = "PZ_TortureRoom_Levasser_21";
		break;
		
		case "PZ_TortureRoom_Levasser_21":
			StartInstantDialog("Longway", "PZ_TortureRoom_Levasser_22", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_22":
			dialog.text = "Warten Sie eine Minute, Herr Kapitän... Seien Sie nicht so schnell.";
			link.l1 = "Was ist los, Longway?";
			link.l1.go = "PZ_TortureRoom_Levasser_23";
		break;
		
		case "PZ_TortureRoom_Levasser_23":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Lass ihn nicht sterben. Zu einfach. Er verdient Schlimmeres.";
			link.l1 = "Du bist wütend wegen deiner Schwester, mein Freund. Und ich bin wütend über das, was er getan hat "+sStr+"... und was er ihr angetan haben könnte. Aber ich bin kein Tier wie er. Ich könnte ihn mit Kohlen aus diesem Kohlenbecken verbrennen, seine Knochen an diesem Rad brechen... Ich könnte ihn fesseln und ihn durch Blutverlust sterben lassen. Aber ich kann nicht riskieren, dass einer seiner Handlanger ihn rettet. Ich kann dieses Risiko nicht eingehen.";
			link.l1.go = "PZ_TortureRoom_Levasser_24";
		break;
		
		case "PZ_TortureRoom_Levasser_24":
			dialog.text = "Warten Sie, Herr Kapitän. Das ist nicht, was ich meinte. Ich spreche von Poincy.";
			link.l1 = "Was ist mit ihm?";
			link.l1.go = "PZ_TortureRoom_Levasser_25";
		break;
		
		case "PZ_TortureRoom_Levasser_25":
			dialog.text = "Stellen Sie sich vor, wie er Sie belohnen würde, wenn Sie ihm dieses Tier lebendig brächten. Er würde Sie mit Dublonen überschütten. Und dieses Gesindel würde lieber hier sterben, als in einem Verlies in Capsterville zu verrotten.";
			link.l1 = "Vielleicht haben Sie recht, Longway. Aber ich weiß nicht genau, was zwischen diesem Abschaum und dem Chevalier passiert ist. Glauben Sie mir, ich kenne diese Leute besser als Sie. Wenn es nur um Geld geht, wie sie sagen, könnten diese beiden einen Deal machen. Poincy könnte ihn gehen lassen, und ein anderer Raum wie dieser könnte auf einer anderen Insel oder in einer der Städte der Alten Welt auftauchen.";
			link.l1.go = "PZ_TortureRoom_Levasser_26";
			link.l2 = "Keine schlechte Idee, Longway. Ich bezweifle jedoch, dass der Chevalier so großzügig sein wird... Es liegt nicht wirklich in seiner Natur. Aber für mich geht es sowieso nicht um das Geld. Hol ihn hoch! Und versorge seine Wunden, damit er nicht vor seiner Zeit stirbt.";
			link.l2.go = "PZ_TortureRoom_Levasser_28";
		break;
		
		case "PZ_TortureRoom_Levasser_26":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_27", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_27":
			dialog.text = "Aber zuerst komme ich für dich. Und deinen Kumpel. Ich werde dich nicht berühren, schmaläugiger Mann - du bist meiner Zeit nicht wert.";
			link.l1 = "Siehst du, Longway? Das alles muss jetzt aufhören. Hier und jetzt.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_TortureRoom_Levasser_Mertv1");
		break;
		
		case "PZ_TortureRoom_Levasser_28":
			StartInstantDialogNoType("Levasser", "PZ_TortureRoom_Levasser_29", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_TortureRoom_Levasser_29":
			dialog.text = "Warten Sie eine Minute, Kapitän, warten Sie eine Minute, kha-kha.";
			link.l1 = "Was ist los, Monsieur Ex-Gouverneur?";
			link.l1.go = "PZ_TortureRoom_Levasser_30";
		break;
		
		case "PZ_TortureRoom_Levasser_30":
			dialog.text = "Mein Schlüssel befindet sich irgendwo in diesem Raum. Er öffnet eine Truhe in meinem Büro. Dort sind zweihunderttausend in Silber und eine feine Klinge. Wenn das nicht genug ist, gibt es in dem Schlafzimmer meiner Frau, in der Kommode, eine Sammlung teurer Edelsteine.";
			link.l1 = "Hmm, und was möchtest du im Gegenzug?";
			link.l1.go = "PZ_TortureRoom_Levasser_31";
		break;
		
		case "PZ_TortureRoom_Levasser_31":
			dialog.text = "Eine Kugel. Mach es zu Ende. Hier und jetzt.";
			link.l1 = "Was ist mit dem Chevalier de Poincy? Ich habe gehört, ihr seid alte Freunde... Möchtest du ihn nicht sehen?";
			link.l1.go = "PZ_TortureRoom_Levasser_32";
		break;
		
		case "PZ_TortureRoom_Levasser_32":
			dialog.text = "Zur Hölle mit Poincy! Also, stimmst du zu oder nicht?";
			link.l1 = "Eigentlich nicht, Monsieur de... Ich möchte Ihren vollen Namen nicht auflisten.";
			link.l1.go = "PZ_TortureRoom_Levasser_33";
		break;
		
		case "PZ_TortureRoom_Levasser_33":
			dialog.text = "Ist das nicht genug für dich? Gut, es gibt noch mehr...";
			link.l1 = "Die Schreie deiner Opfer müssen dich taub gemacht haben, Levasseur. Ich sagte dir, es geht nicht um das Geld. Du hast aus einem Grund Angst vor Poincy, oder? Ich will gar nicht wissen, was er mit dir anstellen wird. Aber wenn es ein wenig Vergeltung für deine... Kunstfertigkeit ist, dann soll es so sein.";
			link.l1.go = "PZ_TortureRoom_Levasser_34";
			pchar.questTemp.PZ_LevasserPlenen = true;
			pchar.questTemp.PZ_LevasserPobezhden = true;
		break;
		
		case "PZ_TortureRoom_Levasser_34":
			dialog.text = "So bist du also wirklich, kha-kha... Nicht besser als ich.";
			link.l1 = "Genug. Longway - bring ihn hoch!";
			link.l1.go = "PZ_TortureRoom_Levasser_35";
		break;
		
		case "PZ_TortureRoom_Levasser_35":
			DialogExit();
			
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1 = "locator";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.location = "Tortuga_Torture_room";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator_group = "reload";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition.l1.locator = "reload1";
			PChar.quest.PZ_TortureRoom_Levasser_ObratnoNaBereg.win_condition = "PZ_TortureRoom_Levasser_ObratnoNaBereg";
			
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) Return_MaryOfficer();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) Return_HelenaOfficer();
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) Return_LongwayOfficer();
			sld = CharacterFromID("Levasser");
			sld.location = "None";
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "Unser Schiff... Ich hätte nie gedacht, dass ich so froh sein würde, es zu sehen... also gut. Endlich ist dieser Alptraum vorbei.";
				}
				else
				{
					dialog.text = "Es ist endlich vorbei. Wohin jetzt, Charles?";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
				{
					dialog.text = "Ich kann es kaum glauben, dass alles vorbei ist... Was machen wir jetzt, mein Kapitän?";
				}
				else
				{
					dialog.text = "Nun, das war's, mein Kapitän. Was machen wir jetzt?";
				}
			}
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				link.l1 = "Ach, es ist noch nicht vorbei. Chang Xing... Diese Geschichte endet erst wirklich, wenn ich meine Antworten von ihr bekomme.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Setzen Sie den Kurs auf Capsterville. Es ist Zeit, dass Monsieur Levasseur Teil der Geschichte wird.";
				}
				else
				{
					link.l1 = "Die Mission des Chevaliers ist abgeschlossen. Ich muss es ihm melden. Einige Details werde ich allerdings weglassen. Ich hoffe nur, er hält sein Wort und Michel wird freigelassen...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Ich auch, ja, gell. Also komme ich mit dir. Und versuche nicht einmal, mit mir zu streiten, Charles.";
				link.l1 = "Mary, Liebling, du musst dich ausruhen. Du bist kurz davor, in Ohnmacht zu fallen...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Ich komme mit dir.";
				link.l1 = "Helen, du bist beinahe in den Händen dieses Teufels gestorben. Du kannst kaum auf deinen Füßen stehen...";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Ich brauche dich, Charles. Und du brauchst mich. Und wenn heute Abend jemand in Ohnmacht fällt, dann ist es Chang Xing. Auf dem Boden ihres Bordells, mit einer Kugel zwischen ihren Augen!";
				link.l1 = "Ja, Levasseur hat dir den Kampfgeist nicht ausgetrieben. Ich würde dich zurück zum Schiff schicken, aber ich weiß, dass du mir sowieso folgen würdest...";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Aber ich kann immer noch eine Klinge halten. Charles, ich muss dabei sein. Ich muss verstehen, was sie dazu getrieben hat. Verstehst du, warum das für mich so wichtig ist?";
				link.l1 = "Ich verstehe, dass Sie Ruhe und Heilung brauchen. Und zwar eine lange.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaZdorovaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaZdorovaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Sie kennen mich zu gut, Charles, ja, gell. Also lassen wir das Gerede und beenden das.";
				link.l1 = "Haben Sie es auf Ihre Weise. Aber bleiben Sie wachsam. Niemand weiß, welche Überraschungen uns dort draußen erwarten.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Es kann warten. Du bist für mich gekommen, und jetzt komme ich mit dir mit. Ob du willst oder nicht.";
				link.l1 = "Ich sehe, du hast immer noch deinen Mut, Helen. Gut. Bleib hinter mir und um Gottes willen, sei vorsichtig.";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SDevushkoyKShin");
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_1":
			if (!CheckAttribute(pchar, "questTemp.PZ_FlagShinInfo"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Unser Schiff... Ich kann es nicht glauben, dass ich sie wieder betreten werde, ja, gell...";
					link.l1 = "Sie wartet auf dich, Mary. Ein herzhaftes Mahl und ein weiches Bett auch...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ugh... Ich dachte nicht, dass ich es mit meinen eigenen zwei Füßen zum Boot schaffen würde.";
					link.l1 = "Du bist die widerstandsfähigste Person, die ich je gekannt habe, Helen. Jetzt geh rein und dann ins Bett...";
				}
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
				{
					dialog.text = "Unser Schiff... Ich kann es nicht glauben, dass ich es wieder betreten werde, ja, gell...";
				}
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					dialog.text = "Ugh... Ich dachte nicht, dass ich es mit meinen eigenen zwei Füßen zum Boot schaffen würde.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_LevasserPlenen"))
				{
					link.l1 = "Setzen Sie Kurs auf Capsterville. Es ist Zeit, dass Monsieur Levasseur Teil der Geschichte wird.";
				}
				else
				{
					link.l1 = "Die Mission des Chevaliers ist abgeschlossen. Ich muss ihm Bericht erstatten. Allerdings werde ich einige Details weglassen. Ich hoffe nur, er hält sein Wort und Michel wird freigelassen...";
				}
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_Final_SdaemKvestPuansi");
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Und du, Charles... Warum dieser Blick? Du heckst wieder etwas aus, oder?";
				link.l1 = "Chang Xing. Ich muss auch zu ihr gelangen.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Und Sie? Wohin gehen Sie?";
				link.l1 = "Um Chang Xing zu sehen. Sie ist das letzte Kapitel dieses Albtraums.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_3";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Dann komme ich mit dir! Sie schuldet mir viel, ja, gell!";
				link.l1 = "Mary, meine Liebe, du hast es gerade noch rechtzeitig zum Boot geschafft. Und du kannst gerade jetzt kein Schwert halten. Ich werde sie für das bezahlen lassen, was sie dir angetan hat, ich schwöre es bei Gott. Aber es wird mir viel besser gehen, wenn du auf dem Schiff bleibst, in dem Wissen, dass du sicher bist.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mein Kapitän, ich würde so gerne mit Ihnen gehen... Bitte seien Sie vorsichtig. Wer weiß, wozu sie sonst noch fähig ist? Sie hat mich festgehalten, während dieser Welpe Thibaut...";
				link.l1 = "Das Schlimmste ist vorbei, Helen. Es wird bald vorbei sein, das verspreche ich.";
			}
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_4";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Nun, zumindest wird Longway in meiner Abwesenheit deinen Rücken decken. Aber wenn dir etwas passiert, werde ich ihn und Chang Xing selbst unter die Erde bringen!";
					link.l1 = "Es wird alles gut. Geh jetzt und ruhe dich aus. Ich bin zurück, bevor du es merkst.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "Wo ist Longway hin, Charles?";
					link.l1 = "Er ist ohne mich hinter Chang Xing hergegangen. Ich konnte ihn nicht aufhalten, aber was hätte ich tun können?";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom"))
				{
					dialog.text = "Nun, zumindest kommt Longway mit dir. Das ist zumindest ein Trost.";
					link.l1 = "Siehst du? Es besteht kein Grund zur Sorge. Ich werde nicht lange weg sein.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
				}
				else
				{
					dialog.text = "Wo ist Longway? Mir ist gerade aufgefallen, dass er nicht hier ist.";
					link.l1 = "Er ging ohne mich zu seiner Schwester. Ich mache ihm keine Vorwürfe. Er hat zu lange auf diesen Moment gewartet.";
					link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_5";
					
				}
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_5":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, ich habe ein schlechtes Gefühl dabei...";
				link.l1 = "Ich weiß. Dieser Albtraum dauert schon zu lange und das Ende ist nahe. Das Schlimmste ist vorbei.";
				link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Wer weiß, was in seinem Kopf vorgeht, Charles? Halte deine Augen offen, ja, gell?";
				link.l1 = "Ich werde es tun. Ich komme bald zurück, Helen."link.l1.go ="PZ_Etap6_AmUfer_KrankeJungfrau_7";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_6":
			dialog.text = "Versprich mir, dass du auf alles vorbereitet sein wirst.";
			link.l1 = "Ich bin es, und ich werde es sein. Ich komme bald zurück, Mary.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_7";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_7":
			if (CheckAttribute(pchar, "questTemp.PZ_LongwayRyadom")) StartInstantDialog("Longway", "PZ_Etap6_NaBeregu_DevaBolnaya_8", "Quest\CompanionQuests\Longway.c");
			else
			{
				DialogExit();
				LAi_SetPlayerType(pchar);
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = CharacterFromID("Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sld = CharacterFromID("Helena");
				LAi_ActorRunToLocation(sld, "reload", "sea", "", "", "", "", -1);
				sld.location = "None";
				AddQuestRecord("PZ", "51");
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) AddQuestUserData("PZ", "sText", "Mary");
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) AddQuestUserData("PZ", "sText", "Helen");
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1 = "location";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition.l1.location = "Tortuga_brothelElite";
				PChar.quest.PZ_Etap6_BrothelPoiskSestry.win_condition = "PZ_Etap6_BrothelPoiskSestry";
			}
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_8":
			dialog.text = "Longway hat Ihnen geholfen, Kapitän. Jetzt ist es an Ihnen, Ihr Wort zu halten.";
			link.l1 = "Du hast alles gehört, Longway. Lass uns deine Schwester besuchen.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_9";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_9":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Herr Kapitän, Longway hat eine letzte Bitte: Lassen Sie Chang Xing sich erklären. Hören Sie sie an, bevor Sie eine Entscheidung treffen.";
			link.l1 = "Was ist passiert mit "+sStr+" liegt bei ihr. Aber ich gebe ihr erst eine Chance zu erklären.";
			link.l1.go = "PZ_Etap6_NaBeregu_DevaBolnaya_10";
		break;
		
		case "PZ_Etap6_NaBeregu_DevaBolnaya_10":
			dialog.text = "Longway vertraut auf Ihr Wort, Ihr Urteil und Ihre Güte.";
			link.l1 = "Kamerad, es gibt keinen Platz für Vernunft oder Güte in diesem blutigen Durcheinander. Und es ist höchste Zeit, es zu beenden.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_SLongwayKShin");
		break;
		
		case "PZ_LongwayPrishelOdin":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sStr = "Helen";
			if (CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				dialog.text = "Herr Kapitän...";
				link.l1 = +sStr+" ist tot.";
				link.l1.go = "PZ_LongwayPrishelOdin2";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Kapitän, Dame "+sStr+", es ist eine Freude, Sie zu sehen. Das ist... Chang Xing.";
					link.l1 = "Ich habe es erraten, Longway. Tritt zurück. Du hattest genug Zeit, mit deiner Schwester zu sprechen. Jetzt muss sie antworten auf "+sStr+" dafür, dass sie Levasseurs Schergen geholfen hat, sie zu entführen.";
					link.l1.go = "PZ_LongwayPrishelOdin7";
				}
				else
				{
					dialog.text = "Du bist gekommen... Wo ist die Dame "+sStr+" Ist sie...?";
					link.l1 = "Nein, Longway. Gott sei Dank, nein. Ich habe sie zum Schiff gebracht. Sonst würde ich jetzt nicht mal dieses Gespräch führen. Aber es wird trotzdem nicht leicht oder angenehm sein.";
					link.l1.go = "PZ_LongwayPrishelOdin12";
				}
			}
		break;
		
		case "PZ_LongwayPrishelOdin2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Chang Xing und ich sprechen unser Beileid aus...";
			link.l1 = "Beileid von Chang Xing?! Du könntest genauso gut Beileid im Namen von Levasseur anbieten, Longway! Du weißt ganz genau, dass sie an der Entführung teilgenommen hat "+sStr+" zusammen mit den anderen, seinen Schergen! Und jetzt ist sie weg...!";
			link.l1.go = "PZ_LongwayPrishelOdin3";
		break;
		
		case "PZ_LongwayPrishelOdin3":
			dialog.text = "Wir.. Ich verstehe, was Sie gerade fühlen, Herr Kapitän.";
			link.l1 = "Ach, wirklich?";
			link.l1.go = "PZ_LongwayPrishelOdin4";
		break;
		
		case "PZ_LongwayPrishelOdin4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Ich habe meine Eltern verloren, wie du dich erinnerst. Wenn du dich erinnerst. Außerdem war es nicht Chang Xing, der gefoltert und getötet hat "+sStr+". Ich verstehe deinen Schmerz, deine Wut. Aber die Schuld meiner Schwester ist nicht so groß wie deine. Bitte, hör mir zu.";
			link.l1 = "Ich erinnere mich. Ich werde mir deine Geschichte anhören. Aber mach es schnell! Und wisse, dass ich so etwas nicht ungestraft lassen kann!";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin5":
			dialog.text = "Dann sollte ich wohl alles noch einmal erzählen, Monsieur de Maure. Unser Tu spricht so schlecht Französisch, dass Sie ihn fast angegriffen hätten.";
			link.l1 = "Sie hätten Ihren Mund halten sollen. Ich hatte nicht vor, Longway anzugreifen, aber Sie... Sie sind derjenige, der für ihren Tod verantwortlich ist.";
			link.l1.go = "PZ_LongwayPrishelOdin6";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin6":
			dialog.text = "Ich würde dem widersprechen, aber ich merke, dass ich das lieber nicht tun würde. Tu sprach von dir als einer Person des Respekts und Verständnisses. Aber ist das wirklich der Fall? Macht es Sinn, dass ich überhaupt anfange zu reden? Oder haben Sie sich bereits entschieden?";
			link.l1 = "Sie wissen, wie man in den Kopf eines Menschen gelangt, Mademoiselle. Es lohnt sich wirklich nicht, jetzt zu streiten. Aber wenn Sie versuchen möchten, sich zu rechtfertigen... Nun, nur zu. Um Longways willen, werde ich Ihnen zuhören.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Sie kann alles erklären, Herr Kapitän... Es ist nicht das, was Sie denken... Nicht wirklich...";
			link.l1 = "Dann erkläre es. Aber nicht mir. "+sStr+". Schau ihr in die Augen. Betrachte ihre Prellungen und Wunden. Und sag ihr, es war nicht so.";
			link.l1.go = "PZ_LongwayPrishelOdin8";
		break;
		
		case "PZ_LongwayPrishelOdin8":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Meine Entschuldigung im Namen von Xing, Kapitän...";
			link.l1 = "Nach ihrem grinsenden Gesicht zu urteilen, tust du es vergeblich. Sie verdient deine Entschuldigung nicht.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin9":
			dialog.text = "Sie sind zu hart zu ihm, Monsieur de Maure. Obwohl Sie es wahrscheinlich gewohnt sind, ihn so zu behandeln - wie einen typischen gelbhäutigen Arbeiter.";
			link.l1 = "Versuchst du, Longway gegen mich aufzubringen? Das wird nicht funktionieren. Ich habe ihn immer mit Respekt behandelt, und er weiß das. Das ist alles, was zählt. Ich weiß, dass Spielereien jetzt alles sind, was dir noch bleibt.";
			link.l1.go = "PZ_LongwayPrishelOdin10";
			locCameraFromToPos(2.17, 2.32, 0.55, true, -0.92, -0.37, -4.09);
			sld = characterFromId("Longway");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "PZ_LongwayTurnToChangShin", -1);
		break;
		
		case "PZ_LongwayPrishelOdin10":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Was wollen Sie tun? Den armen Tu von seiner Familie wegnehmen? Als er sie endlich nach zehn Jahren wiedergefunden hat?";
			link.l1 = "Blut macht nicht immer eine Familie aus. Aber was schlagen Sie vor, dass wir tun? Lassen Sie, was Sie getan haben, um"+sStr+" ungestraft davonkommen? Und dass Longway gelegentlich eine Frau besucht, die ohne zu zögern mit anderen Mädchen handelt?";
			link.l1.go = "PZ_LongwayPrishelOdin11";
		break;
		
		case "PZ_LongwayPrishelOdin11":
			dialog.text = "Nun, zum Anfang, hör zu. Im Gegensatz zu ihm kann ich, was ich ihm gerade erzählt habe, in perfektem Französisch nacherzählen. Meine Geschichte. Direkt in deine Augen schauend, oder sogar in ihre. Und das alles ohne den Akzent, den du wahrscheinlich bis zum Tod satt hast. Schließlich, was haben wir alle zu verlieren?";
			link.l1 = "I'm used to Longway's accent; it's part of who he is to me. I'll listen to you, but only for the sake of my friend. Go on.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_LongwayPrishelOdin12":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Warum nicht, Herr Kapitän...?";
			link.l1 = "Müssen Sie das wirklich fragen? Sie war an der Entführung von "+sStr+", war sie nicht?";
			link.l1.go = "PZ_LongwayPrishelOdin13";
		break;
		
		case "PZ_LongwayPrishelOdin13":
			dialog.text = "Ich ... entschuldige mich aufrichtig. Es ist auch meine Schuld, dass ich meine Schwester vor zehn Jahren nicht retten konnte, um sie vor all dem zu schützen.";
			link.l1 = "Sie sollten sich nicht für diejenigen entschuldigen, die nicht die geringste Reue haben, Longway. Sind Sie hier fertig? Jetzt ist es an der Zeit, dass ich mit ihr spreche.";
			link.l1.go = "PZ_LongwayPrishelOdin14";
		break;
		
		case "PZ_LongwayPrishelOdin14":
			dialog.text = "Mein Herr Kapitän, warten Sie! Chang Xing ist nicht ganz wie Levasseur. Sie wird mir von ihrem Leben in diesen zehn Jahren erzählen. Lassen Sie mich Ihnen auch erzählen.";
			link.l1 = "In Ordnung, Longway. Ich höre zu. Vieles hängt davon ab, was du mir erzählen wirst.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LongwayPrishelOdin_ChangShinNext");
		break;
		
		case "PZ_LongwayPrishelOdin15":
			dialog.text = "Wenn Sie es erzählen, bekommen wir alle Kopfschmerzen. Lassen Sie mich, Tu. Charles de Maure, nehme ich an?";
			link.l1 = "Richtig. Und du bist Belle Etoile, auch bekannt als Chang Xing. Du hast eine Rolle bei der Entführung meiner Liebe gespielt, zusammen mit Thibaut und Martene. Und du lächelst, wenn ich es erwähne. Glückliche Erinnerungen?";
			link.l1.go = "PZ_LongwayPrishelOdin16";
		break;
		
		case "PZ_LongwayPrishelOdin16":
			dialog.text = "Es ist dumm, es zu leugnen. Aber was jetzt? Wirst du mich vor meinem Bruder foltern? Oder ihn sogar bitten, dir dabei zu helfen, mich zu foltern? Oder wirst du mich einfach töten? Würdest du ihm das wirklich antun?";
			link.l1 = "Wie ich bereits sagte, trotz allem, was ich jetzt gerne tun würde, spreche ich immer noch mit Ihnen. Drängen Sie nicht. Erzählen Sie mir, was Sie ihm vorher gesagt haben. Und dann werden wir sehen, wo wir von dort aus alle hingehen.";
			link.l1.go = "PZ_ChangShin2";
		break;
		
		case "PZ_Longway_91":
			if (!CheckAttribute(pchar, "questTemp.PZ_LevasserPobezhden"))
			{
				dialog.text = "Ich kann immer noch nicht glauben, dass Chang Xing sich in ... dies verwandelt hat.";
				link.l1 = "Menschen ändern sich, Longway. Jeder kann gebrochen werden oder die letzten Tropfen von Güte und Glauben aus ihnen herausgekratzt bekommen.";
				link.l1.go = "PZ_Longway_ToGirl1";
			}
			else
			{
				dialog.text = "Longway kann immer noch nicht glauben, dass meine Schwester sich in... dies verwandelt hat. Warum... warum? Wenn ich doch nur an diesem Tag zu Hause gewesen wäre...";
				link.l1 = "Machen Sie sich keine Vorwürfe wegen der Was-wäre-wenns. Außerdem haben Sie all die Jahre nicht untätig verbracht - Sie haben so verdammt hart versucht, die Dinge zu reparieren.";
				link.l1.go = "PZ_Longway_ToShore1";
			}
		break;
		
		case "PZ_Longway_ToGirl1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Mary";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Helen";
			dialog.text = "Eh ... Ich denke, das ist einfach so, Herr Kapitän.";
			link.l1 = "Lass uns hier raus. Wir müssen immer noch das Chaos aufräumen, das sie hinterlassen hat, und retten die "+sStr+" so schnell wie möglich.";
			link.l1.go = "PZ_Longway_ToGirl2";
		break;
		
		case "PZ_Longway_ToGirl2":
			dialog.text = "Ja. Wir müssen uns beeilen - es hat sich schon zu lange wegen mir verzögert.";
			link.l1 = "Es ist nicht deine Schuld, Longway. Lass uns beeilen!";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Longway_ToShore1":
			dialog.text = "Richtig. Danke für Ihre Unterstützung, Herr Kapitän.";
			link.l1 = "Erwähne es nicht. Sie hat deine Hingabe sowieso nicht verdient - sie war nicht diejenige, die dich gesucht hat, auch wenn sie es hätte tun können. Dein Stern ist schon lange erloschen, und sie hat vor langer Zeit aufgehört, deine Familie zu sein. Wir sind jetzt deine Familie, Longway.";
			link.l1.go = "PZ_Longway_ToShore2";
		break;
		
		case "PZ_Longway_ToShore2":
			dialog.text = "Aye... So bist du also. Und ich war zu blind, um es die ganze Zeit zu sehen.";
			link.l1 = "Besser spät als nie. Jetzt gehen wir nach Hause - unser Schiff wartet auf uns.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_Mary_91":
			dialog.text = "In Ordnung. Du hast keine Ahnung, wie sehr ich das wollte.";
			link.l1 = "Ich glaube, das tue ich. Wie fühlst du dich, Mary? Der Grund, warum ich Blutvergießen vermeiden wollte, war, weil ich mir nicht sicher war, ob du dein Schwert so fest halten könntest, wie du es immer getan hast - einer von ihnen hätte die Oberhand gewinnen können, während ich mit einem anderen beschäftigt war.";
			link.l1.go = "PZ_Mary_92";
		break;
		
		case "PZ_Mary_92":
			dialog.text = "Du unterschätzt mich. Außerdem ist Wut eine verdammt gute Medizin. Ich hatte keine Zweifel, dass du dich beeilen würdest, mich zu retten - genau wie du es immer tust, ja, gell. Weißt du, Charles ... Obwohl du mich dein Roter Talisman nennst, was ist, wenn du auch meiner bist? Wenn wir zusammen sind, passiert immer etwas Erstaunliches.";
			link.l1 = "Ich bin dein Talisman? Nun, diese Idee gefällt mir.";
			link.l1.go = "PZ_Mary_93";
		break;
		
		case "PZ_Mary_93":
			dialog.text = "Da hast du es, du lächelst schon! Jetzt lass uns aus diesem widerlichen Ort verschwinden - beeil dich, schnipp-schnapp, ja, gell?";
			link.l1 = "Eh-heh, dieses Durcheinander hat mich hart getroffen. Ich wünschte, es hätte auf irgendeine andere Weise enden können.";
			link.l1.go = "PZ_Mary_94";
		break;
		
		case "PZ_Mary_94":
			dialog.text = "Ich nicht. Es gab keine Rettung für sie, Charles. Und sie hat Longway mit sich gezogen. Er hat seine Entscheidung getroffen, und er ließ uns keine Wahl. Denken Sie an all die Menschen, denen wir heute geholfen haben.";
			link.l1 = "Noch einmal kann ich dir, Mary, nichts entgegensetzen. Und dieses Mal will ich es nicht einmal. Komm, mein roter Talisman...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_LeaveEliteBrothel");
		break;
		
		case "PZ_ElitaShluha_Final1":
			if (CheckAttribute(pchar, "questTemp.PZ_ChangShinMertva"))
			{
				dialog.text = "Was ist dort passiert, Monsieur? Wir haben Fluchen und Schreien gehört. Aber wir haben uns nicht getraut, um Hilfe zu rufen, bis es vorbei war.";
				link.l1 = "Und das zu Recht. Eure Wirtin ist tot. Ihr seid frei zu gehen. Wenn ich du wäre, würde ich die Schatzkammer des Etablissements einziehen, aufteilen und so schnell wie möglich die Insel fliehen. Ich weiß, dass ihr ehrenwerte Damen seid, keine bloßen Prostituierten, also werdet ihr eine Zukunft jenseits dieses elenden Ortes haben.";
				link.l1.go = "PZ_ElitaShluha_Final2";
			}
			else
			{
				dialog.text = "Ach, Sie sind es, Monsieur. Wissen Sie, wann die Gastgeberin herunterkommt?";
				link.l1 = "Nicht bald. Und ich würde mich von der Tür fernhalten, wenn ich du wäre. Und sprechen Sie nie mit ihr über diesen Abend - sie wird nichts teilen, und neugierige Katzen verlieren ihr Leben auf einmal. Es scheint, Ihre Dame mag es nicht, wenn jemand in ihre Geheimnisse eindringt.";
				link.l1.go = "PZ_ElitaShluha_Final3";
			}
		break;
		
		case "PZ_ElitaShluha_Final2":
			dialog.text = "Hast du sie getötet?!";
			link.l1 = "Ich habe es getan. Und wenn Sie zögern oder versuchen, die Wachen auf mich zu rufen, wäre das Ihr größter Fehler. Sie war nie eine Schutzheilige für Sie - egal wie viel Seide und Bildung sie Ihnen gab, Sie waren hier eingesperrt, gezwungen, sich jedem Pöbel zu geben, auf den sie zeigte. Ich wünsche Ihnen allen viel Glück beim Verlassen dieses Ortes. Auf Wiedersehen, meine Damen.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_ElitaShluha_Final3":
			dialog.text = "Ist sie wirklich in Ordnung? Können wir reingehen? Müssen wir die Wachen rufen?";
			link.l1 = "Sie wird nie wieder in Ordnung sein. Sie können versuchen, sie selbst zu fragen... auf eigene Gefahr. Sie spricht immer noch mit ihrem Bruder. Und ich glaube nicht, dass sie es gerne haben werden, gestört zu werden.";
			link.l1.go = "PZ_ElitaShluha_Final4";
		break;
		
		case "PZ_ElitaShluha_Final4":
			dialog.text = "Ich sehe... Nun, besuchen Sie uns wieder einmal, Monsieur.";
			link.l1 = "Nie. Auf Wiedersehen, Damen.";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_ToTortugaStreets");
		break;
		
		case "PZ_TortugaSoldier1":
			dialog.text = "Halt! Es wurden Schreie und Kämpfe aus Mademoiselle Etoiles Ort gemeldet. Die Wache glaubt, dass Sie damit zu tun hatten. Übergeben Sie Ihre Waffen und folgen Sie uns, Monsieur.";
			if (!CheckAttribute(pchar, "questTemp.PZ_DevushkaMertva"))
			{
				link.l1 = "Das ist wahr, aber wir haben den Kampf nicht begonnen, wir haben ihn beendet. Die angestellten Schläger rebellierten wegen verspäteter Zahlungen und griffen Madame Etoile an, um sie auszurauben. Man kann sich immer auf Söldner verlassen, nicht wahr? Wir haben den Tag gewonnen, aber leider hat sie nicht überlebt.";
				link.l1.go = "PZ_TortugaSoldier2";
			}
			else
			{
				link.l1 = "Ich habe heute die Liebe meines Lebens verloren, also lass mich passieren, Offizier.";
				link.l1.go = "PZ_TortugaSoldierGirlDied1";
			}
		break;
		
		case "PZ_TortugaSoldier2":
			dialog.text = "Sie verstehen doch, dass wir Ihnen nicht einfach so glauben können, oder? Wir müssen Sie festnehmen. Und Sie benötigen Zeugenaussagen von den weiblichen Mitarbeitern. Mal sehen, was sie zu sagen haben.";
			link.l1 = "Meine Geliebte ist schwer verletzt. Ich bin auch todmüde. Könntest du uns nicht einfach gehen lassen, bitte?";
			link.l1.go = "PZ_TortugaSoldier3";
		break;
		
		case "PZ_TortugaSoldier3":
			dialog.text = "Wir werden versuchen, das so schnell wie möglich zu klären. Folgen Sie uns jetzt.";
			link.l1 = "Zur Hölle mit dir...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_TortugaSoldierGirlDied1":
			dialog.text = "Mein Beileid, Monsieur. Und ich bin noch kein Offizier, aber... egal, lassen wir das. Könnten Sie mit uns kommen und uns erzählen, was dort passiert ist?";
			link.l1 = "Ich werde es Ihnen erzählen. Das Bordell verlor Geld, und es blieb kein Bargeld übrig, um die Söldner zu bezahlen, die es bewachten. Sie beschlossen, alles zu nehmen, was übrig blieb, gerade als ich dort war. Madame Etoile und ich wehrten sie ab, aber sie starb an ihren Wunden. Lassen Sie mich nun endlich passieren.";
			link.l1.go = "PZ_TortugaSoldierGirlDied2";
		break;
		
		case "PZ_TortugaSoldierGirlDied2":
			dialog.text = "Ich würde gerne, aber es gibt eine Menge Papierkram zu erledigen. Und ich muss die Damen, die dort arbeiten, interviewen. Ich fürchte, Sie müssen mindestens einen Tag in der Stadt bleiben, selbst wenn Sie die Wahrheit sagen, Monsieur.";
			link.l1 = "Geh zur Hölle...";
			link.l1.go = "Exit";
			AddDialogExitQuest("PZ_TortugaSoldiersFight");
		break;
		
		case "PZ_Longway_101":
			dialog.text = "Longway hat etwas für Sie, Herr Kapitän.";
			link.l1 = "Wie schön und launisch. Ich habe noch nie so etwas gesehen. Was ist das?";
			link.l1.go = "PZ_Longway_102";
			GiveItem2Character(PChar, "talisman14");
			PlaySound("interface\important_item.wav");
		break;
		
		case "PZ_Longway_102":
			dialog.text = "Es ist das Amulett des Kapitäns meiner Heimat. Und da Longway nicht mehr Kapitän ist, gebe ich es dir.";
			link.l1 = "Danke, Longway. Mit van der Vinks Tod hast du deine Rache an allen bekommen, die du wolltest. Ich bin froh, dass alles so geklappt hat.";
			link.l1.go = "PZ_Longway_103";
		break;
		
		case "PZ_Longway_103":
			dialog.text = "Wenn ich nur Xing dazu überzeugen könnte, wieder ein guter Mensch zu werden...";
			link.l1 = "Sie würde niemandem mehr zuhören wollen, auch nicht ihrem Bruder. Du hast dein Bestes gegeben. Wir alle haben.";
			link.l1.go = "PZ_Longway_104";
		break;
		
		case "PZ_Longway_104":
			dialog.text = "Aye... Vielen Dank, Herr Kapitän. Longway ist frei und hat wieder ein Zuhause und Freunde.";
			link.l1 = "Gern geschehen, mein Freund. Nun, warum kommst du nicht mit mir, um meinen Bruder zu besuchen. Oh, die Ironie!";
			link.l1.go = "PZ_Longway_105";
		break;
		
		case "PZ_Longway_105":
			DialogExit();
			DeleteAttribute(npchar, "CompanionDisable");//теперь можем и в компаньоны
			chrDisableReloadToLocation = false;
			Return_LongwayOfficer();
		break;
		
		case "PZ_PuansieDialogWithLevasser_1":
			dialog.text = "Hier sind wir wieder, François. Ich sehe, das Leben hat seinen Tribut von dir gefordert, hehe.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_1_1";
			LAi_SetHuberType(npchar);
		break;
		case "PZ_PuansieDialogWithLevasser_1_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_2", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_2":
			dialog.text = "Poincy, du gieriger Bastard... Fast erstickt an dem Gold, von dem deine Kassen voll sind, und du kannst immer noch nicht genug bekommen?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_2_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_2_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_3", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_3":
			//LAi_SetActorType(npchar);
			//LAi_ActorSetHuberMode(npchar);
			dialog.text = "Ich teile einige mit dir, François. Du wirst genug haben, glaub mir.";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_3_1";
			//LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;
		case "PZ_PuansieDialogWithLevasser_3_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_4", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_4":
			dialog.text = "Was... was meinen Sie?";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_4_1";
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
		break;
		case "PZ_PuansieDialogWithLevasser_4_1":
			StartInstantDialogNoType("Puancie", "PZ_PuansieDialogWithLevasser_5", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_5":
			dialog.text = "";
			link.l1 = "Generalgouverneur, werden Sie ...";
			link.l1.go = "PZ_PuansieDialogWithLevasser_6";
		break;
		
		case "PZ_PuansieDialogWithLevasser_6":
			dialog.text = "Charles, mein Freund, du hast deine Arbeit getan und das brilliant! Was mit diesem Mann geschieht, sollte dich nicht kümmern... Es wird jedoch nützlich sein zu wissen, Kapitän, für den Fall, dass dein heller Kopf eines Tages dumme Ideen bekommt. Unserem gemeinsamen Freund erwartet eine schlimme Magenverstimmung, sozusagen. Gold ist nicht gut für den Magen, habe ich gehört... Ich hoffe, ich muss nicht weiter erklären.";
			link.l1 = "Nein, Generalgouverneur.";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7";
		break;
		
		case "PZ_PuansieDialogWithLevasser_7":
			dialog.text = "Anders als Monsieur François, haben Sie, Charles, eine große Zukunft vor sich. Jungs, bringt dieses Schwein ins Gefängnis!";
			link.l1 = "";
			link.l1.go = "PZ_PuansieDialogWithLevasser_7_1";
		break;
		case "PZ_PuansieDialogWithLevasser_7_1":
			StartInstantDialog("Levasser", "PZ_PuansieDialogWithLevasser_8", "Quest\CompanionQuests\Longway.c");
		break;
		
		case "PZ_PuansieDialogWithLevasser_8":
			dialog.text = "Finger weg, ihr Fotzen! Bist du zufrieden, de Maure?! Fick dich! Ihr werdet beide in der Hölle brennen, in derselben Pfanne mit mir!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_LevasserVGostyahUPuansie3");
			CharacterTurnByChr(npchar, CharacterFromID("Puancie"));
			sld = characterFromID("PZ_SoldFra_1");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
			sld = characterFromID("PZ_SoldFra_2");
			CharacterTurnByChr(sld, CharacterFromID("Levasser"));
		break;
		
		case "PZ_Baker_1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sStr = "Kasper";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1) sStr = "Sharp";
			dialog.text = "Nun, mein Herr. Ich habe Fräulein "+sStr+"...";
			link.l1 = "Wie schlimm ist es, Raymond?";
			link.l1.go = "PZ_Baker_2";
		break;
		
		case "PZ_Baker_2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Keine Sorge, Kapitän. Mary wurde natürlich hart getroffen, aber im Großen und Ganzen wird alles in Ordnung sein. Sie sollte ein paar Tage im Bett bleiben, und ich erwarte, dass sie in einer vierzehn Tagen wieder einsatzbereit sein wird.";
					link.l1 = "Ich verstehe. Danke, Raymond. Sie können gehen.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Mary hat eine ordentliche Tracht Prügel bekommen, Kapitän. Prellungen, Schnitte... und natürlich der Schock von allem - obwohl sie versucht, es nicht zu zeigen.";
					link.l1 = "Sie hält wie immer ein hartes Gesicht. Aber ich glaube, sie merkt, dass sie jetzt besser im Bett bleibt. Aber wie lange noch?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Sogar ein professioneller Soldat hätte Schwierigkeiten zu überleben, was sie durchgemacht hat, Kapitän. Verstauchungen, Zerrungen, Prellungen - wir haben Glück, dass diese Bastarde ihr die Knochen nicht gebrochen haben. Ihre Sehnen sind jedoch beschädigt, daher wird sie mindestens einen Monat lang keine Klinge führen können.";
					link.l1 = "Zur Hölle mit der Klinge. Wann wird sie wieder auf den Beinen stehen können?";
					link.l1.go = "PZ_Baker_3";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					dialog.text = "Machen Sie sich keine Sorgen, Kapitän. Hellen ist verletzt, aber nicht schlimm. Sie muss jetzt im Bett bleiben, aber ich denke, sie wird sich in ein paar Wochen vollständig erholen.";
					link.l1 = "Ich verstehe. Danke, Raymond. Dismissiert.";
					link.l1.go = "PZ_Baker_4";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Sie hat einiges einstecken müssen, Kapitän. Und die körperlichen Verletzungen sind nur ein Teil der Diagnose... Dieser schreckliche Ort erinnerte sie an den Albtraum, den sie auf der Arbutus erlebt hat.";
					link.l1 = "Natürlich... verdammt! Wann wird sie wieder auf den Beinen sein?";
					link.l1.go = "PZ_Baker_3";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Helen ging auf Messers Schneide, Kapitän. Ich bin überrascht, dass sie nach allem, was sie durchgemacht hat, überlebt hat. Keine inneren Verletzungen oder Frakturen, aber viele Verstauchungen und Zerrungen.";
					link.l1 = "Armes Ding. Wie lange wird ihre Genesung dauern?";
					link.l1.go = "PZ_Baker_3";
				}
			}
		break;
		
		case "PZ_Baker_3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Mindestens eine Woche, Herr. Wenn sie meinen Empfehlungen folgt, sollte sie in etwa einem Monat wieder einsatzbereit sein.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "Nicht vor einer vierzehn Tagen, Herr. Danach erlaube ich ihr kurze Spaziergänge auf dem Achterdeck. Eine vollständige Genesung wird mindestens zwei Monate dauern.";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Sredne"))
				{
					dialog.text = "Belästigen Sie sie mindestens eine Woche nicht, das sage ich Ihnen, Herr. Die vollständige Genesung wird etwa einen Monat dauern.";
				}
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Tyazhelo"))
				{
					dialog.text = "She should stay in bed for a fortnight; after that, she may be able to walk around the deck. But don't expect to see her back in action for at least two months.";
				}
			}
			link.l1 = "Ich verstehe. Danke, Raymond. Abtreten.";
			link.l1.go = "PZ_Baker_4";
		break;
		
		case "PZ_Baker_4":
			DialogExit();
			sld = CharacterFromID("Baker");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "PZ_RazgovorSVrachom_4", -1);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Es ist schwieriger als ich dachte, nach so langer Zeit des Liegens wieder auf eigenen Beinen zu stehen, ja, gell!";
				link.l1 = "Vielleicht sollten Sie den Bettruhe nicht so abrupt aufhören, Liebe.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Oh-h, mein Kopf...";
				link.l1 = "Helen! Bist du nicht ein bisschen früh auf? Du kannst kaum stehen!";
			}
			link.l1.go = "PZ_DevushkaVstalaSKrovati_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaVstalaSKrovati_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Ich würde dieses verdammte Bett lieber verbrennen, als wieder darin zu liegen - zumindest bis ich von Bug bis Heck und zurück gelaufen bin!";
				link.l1 = "Es ist ein schönes bequemes Bett. Und es ist auch kein schlechtes Schiff. Also werde ich dich nicht aufhalten. Aber ich werde da sein, um sicherzustellen, dass du nichts Dummes tust.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Ich bin in Ordnung, Kapitän, wenn auch nicht vollständig. Ich bin noch nicht bereit, ein Schwert zu schwingen, aber ich hasse dieses Bett mit meiner ganzen Seele.";
				link.l1 = "Nun, ein kurzer Spaziergang an Deck wird Ihnen wahrscheinlich nicht schaden. Aber denken Sie nicht einmal daran, in die Nähe der Seile zu kommen!";
			}
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaStoitVosstanovlenie");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, denkst du nicht, du hast mich völlig vergessen? Erinnere mich, wann wir zuletzt zusammen im Bett waren, ja, gell!";
				link.l1 = "Bevor... Lass uns darüber nicht reden, ja, gell, Mary?";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mein Kapitän, habe ich aufgehört, Sie als Frau zu interessieren?";
				link.l1 = "Das ist unerwartet, Helen. Normalerweise bin ich derjenige, der das anspricht... aber ich war mir nicht sicher, ob du bereit bist nach...";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Sex2";
			DelLandQuestMark(npchar);
			pchar.questTemp.PZ_DevushkaSnovaOfficer = true;
			DeleteQuestCondition("PZ_DevushkaSnovaOfficer2");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Dann sprich wenigstens über mich, ja, gell. Bin ich dir unangenehm geworden, nachdem diese zwei Bastarde mich verprügelt haben?";
				link.l1 = "Das ist das Dümmste, was ich je gehört habe. Ich wollte Sie nur nicht stören, bis Sie bereit waren. Und da Sie es jetzt sind...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Sex3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Es ist in Ordnung, Charles, wirklich. Ich versuche einfach, nicht darüber nachzudenken. Und außerdem hast du mich vor dem Schlimmsten bewahrt. Also lassen wir das Reden und... holen wir einfach auf.";
				link.l1 = "Das ist eine verdammt gute Idee, Helen.";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuest("cabin_sex_go");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Sex3":
				dialog.text = "Charles, ich will es nicht, ich fordere es, ja, gell!";
				link.l1 = "Ich würde es nicht wagen, Ihnen zu widersprechen...";
				link.l1.go = "exit";
				pchar.quest.sex_partner = Npchar.id;
				AddDialogExitQuest("cabin_sex_go");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog1":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Charles, wir müssen reden, ja, gell.";
				link.l1 = "Stimmt etwas nicht, Mary? Du siehst ziemlich ängstlich aus, und das verheißt normalerweise nichts Gutes.";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Mein Herr Kapitän, es gibt etwas, das ich Ihnen mitteilen muss.";
				link.l1 = "Ist das so, Helen? Ich höre zu.";
			}
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Genau das ist es! Ist es nicht gut, dass ich bereit bin, meine Pflichten als Offizier wieder aufzunehmen?";
				link.l1 = "Also das ist es. Nun, wenn du dich stark genug fühlst, ist es nicht nur gut, es ist wunderbar.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Ich bin es leid, dass die Mannschaft mich ansieht, als wäre ich eine schwache alte Frau. Ich will zurück ans Steuer und meine Arme durch Übungen mit einer Klinge lockern...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Wenn du dich dazu in der Lage fühlst, werde ich nicht dagegensprechen, Lieber. Ich werde deine Ausrüstung holen. Und ich lasse dich gerne das Steuer übernehmen. Aber sei vorsichtig im Kampf, ja, gell?";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog2_1";
				}
				else
				{
					link.l1 = "Sie wurden auf der Brücke vermisst, Helen. Was das Schwert betrifft, so denke ich, dass es an der Zeit ist, dass Sie es zurückbekommen.";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog3";
				}
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog2_1":
			dialog.text = "Natürlich, Mein Kapitän, was immer Sie sagen.";
			link.l1 = "Gut.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog3":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Wunderbar, ja, gell! Ich kann es kaum erwarten, mit dem Schwert zu üben...";
				if (CheckAttribute(pchar, "questTemp.PZ_DevushkaRanena_Legko"))
				{
					link.l1 = "Schön zu hören, Mary. Aber stürz dich noch nicht Hals über Kopf ins Getümmel... Aber wem sage ich das?";
					link.l1.go = "exit";
					AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
				}
				else
				{
					link.l1 = "Ich nehme an, Sie werden froh sein, diesen Palash wieder in seiner Scheide zu sehen...";
					link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Ich... Ich weiß nicht, was ich sagen soll, Charles. Ich habe gerade erst realisiert, wie viel mir dieses Krummschwert bedeutet...";
				link.l1 = "Ich wusste das schon vor langer Zeit, deshalb hat es sicher und unversehrt auf dich gewartet.";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog4";
				notification("Gave Cutlass of Blaze", "None");
				PlaySound("interface\important_item.wav");
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog4":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				dialog.text = "Mein Narwal, ja, gell!!! Charles, du hast ihn gerettet! Ich bin nicht nur glücklich, ich bin begeistert! Danke, danke! Ich hatte so Angst, dass er auf Martins Schiff zurückgeblieben ist...";
				link.l1 = "Dieses Schwert gehört in deine Hand, mein Roter Talisman. Ich vertraue darauf, dass du es nicht wieder verlierst... Nun, ich werde eurer Wiedervereinigung nicht im Weg stehen, ha-ha!";
				notification("Gave Narwhal", "None");
				PlaySound("interface\important_item.wav");
				link.l1.go = "exit";
				AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
			}
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				dialog.text = "Danke dir, Charles. Weißt du, das ist wahrscheinlich der Grund, warum ich dich liebe...";
				link.l1 = "Um verlorene Dinge zurückzubringen? Ha ha ha ha...";
				link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog5";
			}
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog5":
			dialog.text = "Du lachst, aber ich bin ernst.";
			link.l1 = "Ich weiß, Helen. Ich liebe dich auch, obwohl ich immer noch nicht sicher bin, warum.";
			link.l1.go = "PZ_DevushkaSnovaOfficer_Dialog6";
		break;
		
		case "PZ_DevushkaSnovaOfficer_Dialog6":
			dialog.text = "Vielleicht, weil ich dieses Entermesser noch nicht an dir ausprobiert habe.";
			link.l1 = "Ich werde mich dem entziehen, indem ich zu den Booten gehe. Dort werde ich auf dich warten, Helen.";
			link.l1.go = "exit";
			AddDialogExitQuest("PZ_DevushkaSnovaOfficer3");
		break;
	}
} 