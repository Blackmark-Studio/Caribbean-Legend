// диалоги НПС по квесту Коварный остров Ксочитэм
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Gibt es etwas, das du willst?";
			link.l1 = "Nein, nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// капитан-нежить Санта-Квитерии
		case "SQC_skeletcap":
			PlaySound("Types\skel.wav");
			dialog.text = "Du... wirst trotzdem.... sterben müssen. Er wird kommen... und dich töten... so wie er uns alle getötet hat... so wie er jeden hier getötet hat...";
			link.l1 = "Was? Wer bist du? Von wem redest du?";
			link.l1.go = "SQC_skeletcap_1";
		break;
		
		case "SQC_skeletcap_1":
			PlaySound("Types\skel.wav");
			dialog.text = "Er ist riesig... er ist unverwundbar... er tötet... er wird dich töten. Ich muss dich töten... wenn ich dich töte, wirst du nicht so wie wir... du verstehst nicht... du wirst durch sein Schwert sterben... du wirst zu dem, was wir sind... wie jeder auf der Santa Quiteria...";
			link.l1 = "Auf keinen Fall!";
			link.l1.go = "SQC_skeletcap_2";
		break;
		
		case "SQC_skeletcap_2":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=2; i<=3; i++)
			{
				sld = characterFromId("SQI_skelet_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ksochitam_SQCskeletcapdie");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Страж маски Кукулькана
		case "guardmask":
			PlaySound("Voice\English\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "Ich habe so lange auf dich gewartet!..";
			link.l1 = "Ähm!.. Atemberaubend!... Das ist ein ziemliches Skelett!";
			link.l1.go = "guardmask_1";
		break;
		
		case "guardmask_1":
			dialog.text = "Ich sehe es... Ich fühle es... Du hast mir... meine Freiheit gebracht...";
			link.l1 = "Wovon sprichst du? Was bist du?!";
			link.l1.go = "guardmask_2";
		break;
		
		case "guardmask_2":
			dialog.text = "Ich bin der Hüter von Ksocheatem, der Bewahrer der Maske von Kukulcan... und dein bevorstehender Tod!..";
			link.l1 = "...";
			link.l1.go = "guardmask_3";
		break;
		
		case "guardmask_3":
			PlaySound("Ambient\Teno_inside\big_ring.wav");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "KSOCHITAM_MONSTERS");
			LAi_group_FightGroups("KSOCHITAM_MONSTERS", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("Terrapin_SetMusic", 1.2);
			n = Findlocation("Shore_mask");
			locations[n].type = "seashore";
			pchar.questTemp.Ksochitam.GuardMaskFight = "true";
			for (i=1; i<=4; i++)
			{
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 1, 0, 0, "fortfire");
				CreateLocationParticles("fire_incas_Simple", "fire_incas", "fire_incas"+i, 2.5, 0, 0, "fortfire");
			}
		break;
		
		case "guardmask_4":
			PlaySound("Voice\English\sharlie\Hranitel Maski Kukulkana.wav");
			dialog.text = "Halt...";
			link.l1 = "Und warum sollte ich das tun, hm? Bist du außer Atem, Knochensack?";
			link.l1.go = "guardmask_5";
		break;
		
		case "guardmask_5":
			dialog.text = "Nein. Du wirst mich niemals töten können. Nicht einmal mit diesem magischen Dolch. Unser Duell könnte sehr, sehr lange dauern, bis du völlig entkräftet bist und stirbst.";
			link.l1 = "Ach wirklich? Und warum kannst du mich nicht schlagen?";
			link.l1.go = "guardmask_6";
		break;
		
		case "guardmask_6":
			dialog.text = "Du bist ein mutiger, starker Krieger und du führst die Klaue des Häuptlings. Ich bin verpflichtet, dich leben zu lassen, denn wer dieses Messer besitzt, wer es wagt, sich mir im Kampf entgegenzustellen, bekommt, was er gekommen ist.";
			link.l1 = "Wer bist du? Wer bist du wirklich, Wächter?";
			link.l1.go = "guardmask_7";
		break;
		
		case "guardmask_7":
			dialog.text = "Sie nannten mich einst Alberto Casco. Ich war ein Soldat in Alonso de Maldonados Trupp. Wir hatten das alte Tayasal gefunden, aber sie fingen uns und opferten uns. Wegen meiner Größe und meiner Stärke verwandelte der heidnische Kanek mich in den Wächter von Ksocheatem, den Hüter der Maske von Kukulcan. Jeder, der jemals auf Ksocheatem stand, wurde von mir gefunden und mit meiner Hand geschlachtet und dann in einen Untoten verwandelt. \nMit dem Dolch der Häuptlingsklaue wurde aus meinem Fleisch eine Karte dieses Ortes geschnitzt. Ich werde die Sicherheit der Maske für immer überwachen und ich werde unruhig sein, bis ich den Dolch in meinen Händen halte.";
			link.l1 = "Brauchst du die Klaue des Häuptlings?";
			link.l1.go = "guardmask_8";
		break;
		
		case "guardmask_8":
			dialog.text = "Ja. Da du die Maske brauchst. Gib mir den Dolch. Ich werde meinen lang ersehnten Frieden finden und du wirst die Maske erhalten. Ich schwöre dir, dass du sie mitnehmen und Ksocheatem lebend verlassen kannst.";
			link.l1 = "Ich akzeptiere Ihr Angebot, Wächter. Ich habe die Maske auf dem Sockel hinter dem Taufbrunnen gesehen. Ist das sie?";
			link.l1.go = "guardmask_9";
		break;
		
		case "guardmask_9":
			dialog.text = "Das ist es. Dies ist das mächtige Artefakt von Kukulcan selbst, der fliegenden Schlange. Nachdem wir dieses Gespräch beendet haben, kannst du rübergehen und es nehmen.";
			link.l1 = "Nun, ich hoffe, du hältst dein Wort, Wächter...";
			link.l1.go = "guardmask_10";
		break;
		
		case "guardmask_10":
			dialog.text = "Ich habe geschworen...";
			link.l1 = "Dann nimm die Klaue des Häuptlings. Ich hoffe, sie wird deiner Seele Ruhe bringen.";
			link.l1.go = "guardmask_11";
		break;
		
		case "guardmask_11":
			RemoveItems(pchar, "knife_01", 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You've given the Chief's Claw");
			RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "Oh, wie lange habe ich auf diesen Moment gewartet! Jetzt kann ich endlich gehen ... Aber als Abschiedsgeschenk möchte ich Ihnen ein Teil meiner Macht verleihen. Dies wird das letzte Geschenk sein, das Alberto Casco jemals geben wird.";
			link.l1 = "...";
			link.l1.go = "guardmask_12";
		break;
		
		case "guardmask_12":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Ksochitam_GuardMaskGift", 1.5);
		break;
		
		case "guardmask_13":
			dialog.text = "Jetzt ist es Zeit für mich zu gehen. Zögere nicht, ohne seinen Hüter und die Kukulcan-Maske wird die Insel bald für immer verschwinden.";
			link.l1 = "Es gibt nichts zu bedauern. Eine Hölle weniger auf der Welt... Aber warte, Wächter! Du warst in Tayasal! Bitte, erzähl mir, was das für ein Ort ist.";
			link.l1.go = "guardmask_14";
		break;
		
		case "guardmask_14":
			dialog.text = "Es ist eine alte Maya-Stadt. Ihr Aussehen wurde seit der Zeit bewahrt, als dort noch Menschen lebten. Majestätische Tempel, hohe Pyramiden... Jetzt leben dort der Itza-Stamm, sie behaupten, direkte Nachkommen der Maya zu sein. Sie versuchen, sie in jeder Hinsicht zu imitieren, in Religion, Kultur und Lebensweise.";
			link.l1 = "Wie komme ich dort hin?";
			link.l1.go = "guardmask_15";
		break;
		
		case "guardmask_15":
			dialog.text = "Unser Kommandant kannte den Weg, Alonso de Maldonado. Wir folgten ihm einfach durch den Dschungel. Ich erinnere mich nur daran, dass wir in der Moskito-Bucht nördlich von Cape Perlas an Land gingen und uns tief in den Westen der Selva hineinbewegten.";
			link.l1 = "Was ist bemerkenswert in Tayasal?";
			link.l1.go = "guardmask_16";
		break;
		
		case "guardmask_16":
			dialog.text = "Alles dort ist bemerkenswert. Absolut alles. Aber wir waren an nichts anderem als den Maya-Schätzen interessiert. Und wir haben sie gefunden. Und wir haben teuer dafür bezahlt, besonders ich. Aber jetzt bin ich endlich frei!";
			link.l1 = "Was muss ich wissen, bevor ich nach Tayasal aufbreche?";
			link.l1.go = "guardmask_17";
		break;
		
		case "guardmask_17":
			dialog.text = "Die Itza-Leute besitzen große Stärke und Witz. Sie hassen Weiße, egal welcher Nationalität, und werden jeden Eindringling, der ihr Territorium betritt, vernichten. Einfache Itza-Krieger werden sich auf keine Art von Kommunikation einlassen, aber Kanek oder sein Sohn Urakan, wenn sie die Maske sehen... vielleicht. Wenn es dir gelingt, lebend nach Tayasal zu kommen, wirst du es selbst sehen. Aber wirst du es verlassen können...";
			link.l1 = "Bietet Kanek alle Weißen, die nach Tayasal kommen, als Opfer an?";
			link.l1.go = "guardmask_18";
		break;
		
		case "guardmask_18":
			dialog.text = "Ich würde es vermuten. Aber das könnte den Mann, der die Kukulcan-Maske trägt, nicht einschließen.";
			link.l1 = "In Ordnung. Ich werde darauf zählen.";
			link.l1.go = "guardmask_19";
		break;
		
		case "guardmask_19":
			dialog.text = "Lebewohl, Soldat. Ich hoffe, du wirst die Macht der Maske für den richtigen Zweck einsetzen.";
			link.l1 = "..., Freund.";
			link.l1.go = "exit";
			AddDialogExitQuest("Ksochitam_GuardMaskGoAway");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
