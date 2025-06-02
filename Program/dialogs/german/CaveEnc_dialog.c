// пещерные энкаунтеры
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, sGroup;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	sTemp = "CaveBandos" + locations[FindLocation(npchar.location)].index + "_";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Brauchst du etwas?";
			link.l1 = "Nein, nichts.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "CaveBanditosSit":
			if (hrand(2) == 1) 
			{
				dialog.text = NPCStringReactionRepeat("Woah-ho, schau mal wer da ist! Nun, heute ist dein Glückstag, Kumpel. Wir sind gute Kerle, siehst du, kochen etwas Essen und so... Ich lade dich nicht zu unserem Abendessen ein, aber du solltest verschwinden, solange du noch kannst.","Verschwinde jetzt und belästige uns nicht. Komm morgen wieder - und vergiss nicht, deinen Geldbeutel mitzubringen, ha-ha-ha!","Mach mich nicht wütend, Seemann! Erinnerst du dich noch, wo der Eingang zur Höhle ist? Du solltest jetzt dorthin gehen, sehr, sehr schnell...","Nun, jetzt hast du die Linie überschritten, Kamerad! Scheint, als müsste ich mich von meinen Angelegenheiten losreißen und mich mit dir beschäftigen, Arschloch!","Block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("So nett von dir, Kumpel...","Ich sehe, du bist ganz der Scherzkeks...","Also gut, brat weiter deine Pfannkuchen...","Jetzt reden wir, ha-ha!",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Whoa, beim Himmel! Keine Notwendigkeit, die Beute zu jagen - sie ist schon hier... Hey, Jungs - wollen wir diesen Fatzke schütteln, oder?","Niemand hat dich hier eingeladen, Kumpel... Aber es ist so gut, dass du trotzdem hier bist. Lass uns mal sehen, wie schwer deine Brieftasche ist!","Niemand hat dich hierher gezwungen, he-he... Aber da du schon hier bist, vermuten wir, dass wir dich ein bisschen kitzeln werden, um zu sehen, was aus deinen Taschen fällt...");
				link.l1 = LinkRandPhrase("Jetzt werde ich deine Zunge ein bisschen kürzen...","Ich hoffe, deine Fertigkeiten mit dem Schwert entsprechen deinem Witz, Klappergestell!","Nun, es scheint, dass es Zeit ist, ein paar weitere Löcher in deinen vergänglichen Körper zu machen...");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveBanditosSit";
		break;
		
		case "CaveBanditosStay":
			dialog.text = LinkRandPhrase("Woah, beim Himmel! Keine Notwendigkeit, die Beute zu jagen - sie ist schon hier... Hey, Leute - lassen wir diesen Geck zittern, sollen wir?","Niemand hat dich hier eingeladen, Kumpel... Aber es ist so gut, dass du trotzdem hier bist. Lass uns jetzt sehen, wie schwer deine Börse ist!","Niemand hat dich hierher gezwungen, he-he... Aber wenn du schon hier bist, vermuten wir, dass wir dich ein bisschen kitzeln, um zu sehen, was aus deinen Taschen fällt...");
			link.l1 = LinkRandPhrase("Jetzt werde ich deine Zunge ein bisschen kürzer machen...","Ich hoffe, deine Fähigkeiten mit dem Schwert sind ebenso gut wie dein Scharfsinn, Schwatzmaul!","Nun, es scheint, dass es Zeit ist, ein paar weitere Löcher in deinen vergänglichen Körper zu machen...");
			link.l1.go = "fight";
		break;
		
		case "CaveBanditosTreasure":
			dialog.text = NPCStringReactionRepeat("Verschwinde, Kumpel. Hier gibt's nichts für dich zu tun!","Hallo, ich bitte in einer freundlichen Art: Verschwinde. Man weiß nie, was passieren kann...","Letzte Warnung: Wenn du jetzt nicht verschwindest, wirst du bereuen, hierher gekommen zu sein.","Das ist es, Kumpel, du hast nach Ärger gefragt.","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sag mir nicht, was ich tun soll, verstanden?","Und was ist dort unten so besonders? Nur eine Höhle, nichts weiter...","Ach, komm schon...","Ha! Nun, lass uns mal sehen, wer besser ist, du Made!",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "CaveBanditosTreasure";
		break;
		
		case "CaveCaribSit":
			if (hrand(2) == 2) 
			{
				dialog.text = NPCStringReactionRepeat("Bleichgesicht geht weg. Er sei glücklich, dass "+npchar.name+"  nett. Die Götter haben heute Mitleid mit dir.","Verlass meine Höhle, bevor ich und meine Brüder wütend werden!","Verschwinde, bleichgesichtiger Hund!","Dein Glück und Leben ist vorbei, weißer Hund!","Block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Nun, danke dir, Kamerad, sehr freundlich von dir...","Diese Höhle gehört dir nicht, und ich gehe, wohin ich will.","Nimm einen Gang runter, Sumpfbrut.","Jetzt werde ich dir diese Worte zurück in den Hals stopfen, du Tier...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("Verfluchter Bleichgesicht ist zu unserem Lagerfeuer gekommen! Wheppee! Du bist erledigt!","Dummer Bleichgesicht ist in den Jaguarbau gekommen. Ich werde deine Leber braten!","Unverschämter Bleichgesicht wagt es, in meine Höhle zu kommen? Dann kommt er nie lebend raus!");
				link.l1 = LinkRandPhrase("Jetzt werde ich dir die Zunge herausreißen...","Nun wird die Welt einige Kannibalen weniger haben...","Nun, es scheint, dass es Zeit ist, ein paar weitere Löcher in deinen vergänglichen Körper zu machen, du rotgesichtiger Affe.");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveCaribSit";
		break;
		
		case "CaveCaribStay":
			dialog.text = LinkRandPhrase("Widerlicher Bleichgesicht ist in unsere Höhle gekommen! Whe-hee! Ich werde deine Zunge ausschneiden und braten!","Dummer Bleichgesicht ist in das Jaguarversteck gekommen. Brüder, schneidet diesen verfluchten weißen Köter!","Frecher Bleichgesicht wagt es, in meine Höhle zu kommen? Dann kommt er nie lebend raus!");
			link.l1 = LinkRandPhrase("Ich werde deinen verdammten Kopf abschneiden...","Nun wird die Welt einige Kannibalen weniger haben...","Nun, bereite dich darauf vor, deine Ahnen zu treffen, Rothaut. Zur Hölle mit dir!");
			link.l1.go = "fight";
		break;
		
		case "exit_talk":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
		break;
		
		case "fight":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "CaveEnc_RaidersAfrer");
			chrDisableReloadToLocation = true;
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
