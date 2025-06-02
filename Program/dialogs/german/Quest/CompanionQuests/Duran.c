void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
	string sTemp;
	
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
			dialog.text = "Was braucht ihr?";
			link.l1 = "Nichts.";
			link.l1.go = "exit";
		break;
		
		case "SKD_DomAnri":
			dialog.text = "Grüße in meinem Zuhause, Herren. Was kann ich für euch tun?";
			link.l1 = "Levasseur sendet seine Grüße, Herr.";
			link.l1.go = "SKD_DomAnri_2";
			StartQuestMovie(true, false, true);
		break;
		
		case "SKD_DomAnri_2":
			dialog.text = "So ist es also... Alicia! Lass uns bitte. Diese Herren haben Geschäfte mit mir.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_2_1";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		case "SKD_DomAnri_2_1":
			StartInstantDialog("SKD_Alisia", "SKD_DomAnri_3", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_3":
			dialog.text = "Aber...";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_3_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
		break;
		case "SKD_DomAnri_3_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_4", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_4":
			dialog.text = "Ich liebe dich, Liebling. Mach schon!";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_5";
			CharacterTurnToLoc(npchar, "goto", "goto1");
		break;
		
		case "SKD_DomAnri_5":
			DialogExit();
			locCameraFromToPos(3.47, 2.41, 0.10, false, -1.05, 0.20, -0.07);
			
			sld = CharacterFromID("SKD_Anri");
			CharacterTurnByLoc(sld, "barmen", "stay");
			
			sld = CharacterFromID("SKD_Alisia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "", "", "", "", -1);
			sld.location = "None";
			sld.lifeday = 0;
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("SKD_DomAnri_2", 4.0);
		break;
		
		case "SKD_DomAnri_6":
			dialog.text = "Wunderbare Werke, o Herr! Es war es wert, alles zu verlieren, um die Liebe deines Lebens am Ende der Welt zu finden! Herren, ich gehöre ganz euch. Ich nehme nicht an, dass wir einen Deal machen können?";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_6_1";
		break;
		case "SKD_DomAnri_6_1":
			StartInstantDialog("Duran", "SKD_DomAnri_7", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_7":
			dialog.text = "Nein, und versuche auch nicht, um Gnade zu bitten.";
			link.l1 = "";
			link.l1.go = "SKD_DomAnri_7_1";
			CharacterTurnToLoc(npchar, "barmen", "stay");
			locCameraFromToPos(-0.52, 1.47, 0.76, false, -2.52, 0.20, 0.99);
		break;
		case "SKD_DomAnri_7_1":
			StartInstantDialog("SKD_Anri", "SKD_DomAnri_8", "Quest\CompanionQuests\Duran.c");
		break;
		
		case "SKD_DomAnri_8":
			dialog.text = "Es ist nicht angemessen für einen Ritter des Ordens, um Gnade zu bitten.";
			link.l1 = "Ein ehemaliger Ritter, allerdings.";
			link.l1.go = "SKD_DomAnri_9";
		break;
		
		case "SKD_DomAnri_9":
			dialog.text = "Die Bürokraten hätten nicht genug Tinte auf der ganzen Welt, um mir diesen Titel wegzunehmen.";
			link.l1 = "In diesem Fall, beweise es. Aber zuerst, befriedige meine Neugier: Bist du ein Verräter der Krone? Ansonsten verstehe ich nicht, warum Levasseur so sehr dein Leben wollte.";
			link.l1.go = "SKD_DomAnri_10";
		break;
		
		case "SKD_DomAnri_10":
			dialog.text = "Ich bin meinem Eid treu, Monsieur, also missgönne mir das nicht. Ich werde nur sagen, dass ein Verräter der Krone mich geschickt hat, um einen anderen Verräter zu eliminieren. Und er wird es immer wieder tun, bis ein Bruder, der fähiger ist als ich, Erfolg hat. Genug geredet. Meine Herren, zur Schlacht!";
			link.l1 = "..., Freund.";
			link.l1.go = "SKD_DomAnri_11";
		break;
		
		case "SKD_DomAnri_11":
			DialogExit();
			EndQuestMovie();
			
			sld = CharacterFromID("Duran");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_6");
		break;
		
		case "SKD_DomAnri_12":
			dialog.text = "Ach, danke, Käpt'n. Harter Teufel, der er war. Es gab keine Möglichkeit, dass ich ihn alleine hätte besiegen können.";
			link.l1 = "Irgendwie bin ich nicht sehr glücklich über diesen Sieg. Ich nehme an, wir sind hier fertig?";
			link.l1.go = "SKD_DomAnri_13";
		break;
		
		case "SKD_DomAnri_13":
			dialog.text = "Nicht ganz, zuerst müssen wir aufräumen und das Mädchen beseitigen, das so schnell in den zweiten Stock gerannt ist.";
			link.l1 = "Was?! Leg die Waffe nieder! Hast du den Verstand verloren, Claude? Ich bin kein Metzger!";
			link.l1.go = "SKD_DomAnri_14";
		break;
		
		case "SKD_DomAnri_14":
			dialog.text = "Du musst nichts tun, Käpt'n. Außerdem, das ist alles deine Schuld: du hättest ihr Levasseur nicht erwähnen sollen.";
			link.l1 = "Das ist Unsinn und du weißt es. Und wenn du es wagst, mir noch einmal eine unartikulierte Zurechtweisung zu geben, wirst du damit nicht davonkommen.";
			link.l1.go = "SKD_DomAnri_15";
		break;
		
		case "SKD_DomAnri_15":
			dialog.text = "Heh! Meine Schuld, Kapitän. Richtig, Levasseurs Befehle sagten klar, dass nicht nur der Ritter, sondern auch all seine Begleiter ausgeschaltet werden sollen. Alle von ihnen, verstehst du? Mit diesen Leuten ist nicht zu spaßen und ihre Forderungen müssen ernst genommen werden. Hindere mich nicht daran, meine Arbeit zu erledigen, Kap. Eine letzte schmutzige Arbeit und dann bin ich bis zum Ende mit dir, das schwöre ich!";
			if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
			{
				notification("Reputation Check Passed", "None");
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(Vertrauenswürdig) (Ehre) Du hast einmal gesagt, ich sei dazu bestimmt, hoch zu fliegen, und du warst glücklich, dazu beizutragen.";
				link.l1.go = "SKD_DomAnri_VD";
			}
			else
			{
				notification("Reputation Too Low! ("+XI_ConvertString(GetReputationName(71))+")", "None");
				notification("Perk Check Failed", "Trustworthy");
			}
			link.l2 = "Zum Teufel mit dir! Mach deine schmutzige Arbeit. Ich akzeptiere deinen Eid, und du solltest ihn tödlich ernst nehmen. Verstehen wir uns?";
			link.l2.go = "SKD_DomAnri_DuranDruzhba";
			link.l3 = "Nicht zu diesem Preis, Claude. Ich werde nicht zulassen, dass du dieses Mädchen tötest.";
			link.l3.go = "SKD_DomAnri_DuranDraka";
		break;
		
		case "SKD_DomAnri_DuranDraka":
			dialog.text = "Heh! Ich schätze, wir waren dazu bestimmt, uns gegenseitig zu töten, was, Käpt'n?";
			link.l1 = "Ich denke schon. Lassen wir dort weitermachen, wo wir auf Tortuga aufgehört haben, oder?";
			link.l1.go = "SKD_DomAnri_DuranDraka_2";
		break;
		
		case "SKD_DomAnri_DuranDraka_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			
			RemovePassenger(pchar, npchar);
			npchar.SaveItemsForDead = true;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "SKD_DomAnri_DuranDraka");
		break;
		
		case "SKD_DomAnri_DuranDruzhba":
			dialog.text = "Jawohl, Kapitän!";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_2";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_2":
			DialogExit();
			
			LocatorReloadEnterDisable("PortRoyal_houseSp1", "reload2", true);
			sld = CharacterFromID("Duran");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("PortRoyal_town", true);
			
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1 = "location";
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition.l1.location = "PortRoyal_town";
			PChar.quest.SKD_DomAnri_DuranDruzhba.win_condition = "SKD_DomAnri_DuranDruzhba";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_3":
			dialog.text = "Es ist erledigt, Käpt'n. Sie hat mich überrascht...";
			link.l1 = "Ich will nichts davon hören. Ich habe mein Wort gehalten. Jetzt bist du dran.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_4";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_4":
			dialog.text = "Gold ist das eine, aber seine eigene Haut für einen einfachen Söldner aufs Spiel zu setzen, ist viel mehr wert. Ich bin bis zum Ende mit dir, Kapitän.";
			link.l1 = "In diesem Fall sind wir hier fertig.";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_5";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_5":
			dialog.text = "Aye aye.";
			link.l1 = "...";
			link.l1.go = "SKD_DomAnri_DuranDruzhba_6";
		break;
		
		case "SKD_DomAnri_DuranDruzhba_6":
			DialogExit();
			
			EndQuestMovie();
			locCameraTarget(PChar);
			locCameraFollow();
			LAi_LocationDisableOfficersGen("PortRoyal_town", false);
			chrDisableReloadToLocation = false;
			AddQuestRecord("TheFormerKnight", "3");
			CloseQuestHeader("TheFormerKnight");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("Duran");	//Клод Дюран становится постоянным офицером
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			pchar.questTemp.SKD_DuranDruzhba = true;
			pchar.questTemp.SKD_DevushkaUbita = true;
			sld.reputation = sti(sld.reputation) - 15;
			OfficersFollow();
		break;
		
		case "SKD_DomAnri_VD":
			dialog.text = "Ich habe. Was ist dein Punkt, Kap?";
			link.l1 = "Beweise mir, dass diese Worte nicht nur leeres Gerede waren. Du willst einen Platz in meiner Mannschaft verdienen? Einen Anteil an zukünftigen Beutezügen? Dann befolge meine Befehle. Fass das Mädchen nicht an. Warum? Weil du sonst für immer ein Schlächter bleiben wirst, und für solche Leute habe ich keinen Platz.";
			link.l1.go = "SKD_DomAnri_VD_2";
		break;
		
		case "SKD_DomAnri_VD_2":
			dialog.text = "Das ist das zweite Mal, dass du und ich ums Überleben kämpfen, Kap\nUnd wieder einmal gewinnst du dank deiner Gabe, deine Zunge zu kratzen! Ha ha! Du hast es gesagt! Nun, zur Hölle mit dem Mädchen. Ich bin schließlich ein Tier. Erlaubnis, der Besatzung beizutreten?";
			link.l1 = "Willkommen, Claude. Diesmal wirklich.";
			link.l1.go = "SKD_DomAnri_VD_3";
		break;
		
		case "SKD_DomAnri_VD_3":
			dialog.text = "Jawohl, Kapitän!";
			link.l1 = "..., Freund.";
			link.l1.go = "SKD_DomAnri_VD_4";
		break;
		
		case "SKD_DomAnri_VD_4":
			DialogExit();
			AddQuestRecord("TheFormerKnight", "2");
			CloseQuestHeader("TheFormerKnight");
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("Duran");	//Клод Дюран становится постоянным офицером
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Enc_Officer_dialog.c";
			sld.Dialog.CurrentNode = "hired";
			sld.OfficerImmortal = true;
			sld.Health.HP       = 60.0;
			sld.Health.maxHP    = 60.0;
			SetCharacterPerk(sld, "ShipEscape");
			
			pchar.questTemp.SKD_DuranDruzhba = true;
			sld.reputation = 60;
			OfficersFollow();
		break;
		
		case "SKD_KlodDuran":
			dialog.text = "Etwas ist aufgetaucht, Kap.";
			Link.l1 = "Lass mich raten: Du wirst wieder drohen zu kündigen und eine Gehaltserhöhung fordern?";
			Link.l1.go = "SKD_KlodDuran_1";
		break;
		
		case "SKD_KlodDuran_1":
			dialog.text = "Heh! Nicht dieses Mal... Mach dir keine Sorgen, Kapitän, solange du zahlst, gehöre ich ganz dir... natürlich nur im Rahmen des Vernünftigen. Es ist die einzige Art, wie wir Söldnerbrüder überleben. Und selbst die Besten von uns bekommen nur einen Hungerlohn.";
			link.l1 = "Warum gehen wir nicht einfach direkt zur Sache?";
			link.l1.go = "SKD_KlodDuran_2";
		break;
		
		case "SKD_KlodDuran_2":
			dialog.text = "Erinnerst du dich an diese Schlampe aus Tortuga?";
			link.l1 = "Marceline? Die Frau des Gouverneurs? Eine solche Frau vergisst man nicht.";
			link.l1.go = "SKD_KlodDuran_3";
		break;
		
		case "SKD_KlodDuran_3":
			dialog.text = "Ich bin nicht zufällig zum Haus von Levasseur gekommen. Ich hatte Geschäfte mit diesem Schurken und Ketzer.";
			link.l1 = "Es ist eher seltsam von dir, so abschätzig über die Mächtigen zu sprechen, Claude.";
			link.l1.go = "SKD_KlodDuran_4";
		break;
		
		case "SKD_KlodDuran_4":
			dialog.text = "Hä? Heh! Levasseur ist der Teufel! Er ist weit schlimmer als selbst die Piraten, die sich von ihm ernähren!";
			link.l1 = "Du hast selbst gerade gesagt, dass du Geschäfte mit ihm gemacht hast. Ist das nicht ein bisschen heuchlerisch von dir?";
			link.l1.go = "SKD_KlodDuran_5";
		break;
		
		case "SKD_KlodDuran_5":
			dialog.text = "Ich bin kein Engel, Cap, und ich verdiene meinen Lebensunterhalt damit, jeden zu töten, den ich töten soll. Deshalb schätzt du mich so sehr, nicht wahr? Aber selbst Männer wie ich bekommen Gänsehaut, wenn sie Gerüchte darüber hören, was sie mit Frauen auf Tortuga in Levasseurs Verstecken anstellen!";
			link.l1 = "Gerüchte interessieren mich nicht. Dieser Mann ist ein Adliger und ein Diener des Königs, und er verdient Respekt.";
			link.l1.go = "SKD_KlodDuran_6";
		break;
		
		case "SKD_KlodDuran_6":
			dialog.text = "Also hast du diesen Diener des Königs ausgeraubt und seine Frau genommen? Heh! Mach wie du willst, Käpt'n. Kommen wir zur Sache. Seine Exzellenz hat mich beauftragt, einen Mann zu finden und zu töten. Eine ziemlich routinemäßige Aufgabe, auch wenn sie nicht oft von so einer hohen Person kommt, und sogar persönlich.";
			link.l1 = "Und was willst du? Dass ich dich freilasse, damit du dein Wort halten und diesen Mann töten kannst?";
			link.l1.go = "SKD_KlodDuran_7";
		break;
		
		case "SKD_KlodDuran_7":
			dialog.text = "Ich möchte, dass du mir hilfst, Kapitän. Als es mir auf Tortuga schlecht erging, habe ich zugestimmt, in deinen Dienst zu treten, aber ich werde nicht ruhen, bis ich die Arbeit erledigt habe. Levasseur würde mich töten, wenn er es herausfände. Außerdem ist es unprofessionell, eine Arbeit unvollendet zu lassen.";
			link.l1 = "Ist es professionell, Affären mit der Frau eines Klienten zu haben? Es ist sehr merkwürdig, solch eine Anfrage von dir zu hören, besonders wenn wir den Anfang unseres Gesprächs in Erinnerung rufen, wo du die Essenz unserer Beziehung ziemlich genau beschrieben hast. Blut für Gold, hm?";
			link.l1.go = "SKD_KlodDuran_8";
		break;
		
		case "SKD_KlodDuran_8":
			dialog.text = "Wenn du mir hilfst, bekommst du nicht nur mein Schwert, sondern auch meine Treue. Ich kann sofort sehen, dass du dazu bestimmt bist, hoch zu fliegen, Käpt'n. Ich würde mich freuen, dabei zu helfen, das zu verwirklichen.";
			link.l1 = "Ich gebe zu, ich hätte lieber einen Mann mit deinen Fähigkeiten, der mir den Rücken deckt. Wo können wir dein Ziel finden?";
			link.l1.go = "SKD_KlodDuran_10";
			link.l2 = "Dein Säbel wird vorerst ausreichen. Ich bin kein Mörder. Sei entspannt, Offizier!";
			link.l2.go = "SKD_KlodDuran_9";
		break;
		
		case "SKD_KlodDuran_9":
			dialog.text = "Jawohl, Käpt'n. Es war trotzdem einen Versuch wert.";
			link.l1 = "...";
			link.l1.go = "SKD_KlodDuran_9_1";
		break;
		
		case "SKD_KlodDuran_9_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.loyality = makeint(npchar.loyality) + 10;
			Return_DurandOfficer();
		break;
		
		case "SKD_KlodDuran_10":
			dialog.text = "Heh! Das ist das Problem, Käpt'n. Alles, was ich weiß, ist, dass er ein ehemaliger Ritter des Malteserordens ist, der irgendwo auf englischem Gebiet auf der Flucht ist. Ein Mann von edler Geburt, also wird er nicht in einer Hütte leben.";
			link.l1 = "Ritter des Ordens?";
			link.l1.go = "SKD_KlodDuran_11";
		break;
		
		case "SKD_KlodDuran_11":
			dialog.text = "Ein ehemaliger Ritter. Ja, und ich habe es schon tausendmal bereut, diesen Job angenommen zu haben. Ritter kämpfen wie Teufel, also garantiere ich dir eine ernsthafte Prüfung deiner Schwertkunst.";
			link.l1 = "Ich mag es nicht, aber lassen wir es versuchen. Also: kein armer Mann, ein Adliger und versteckt sich bei den Engländern? Levasseur hat nicht gesagt, warum er ausgeschaltet werden soll?";
			link.l1.go = "SKD_KlodDuran_12";
		break;
		
		case "SKD_KlodDuran_12":
			dialog.text = "Natürlich wird er das nicht! Aber es ist offensichtlich politisch, sonst hätte er Soldaten geschickt.";
			link.l1 = "Ich werde es versuchen, aber ich kann nichts versprechen.";
			link.l1.go = "SKD_KlodDuran_13";
		break;
		
		case "SKD_KlodDuran_13":
			dialog.text = "Danke, Käpt'n.";
			link.l1 = "..., Freund.";
			link.l1.go = "SKD_KlodDuran_14";
		break;
		
		case "SKD_KlodDuran_14":
			DialogExit();
			SetQuestHeader("TheFormerKnight");
			AddQuestRecord("TheFormerKnight", "1");
			chrDisableReloadToLocation = false;
			npchar.loyality = makeint(npchar.loyality) + 15;
			Return_DurandOfficer();
			PChar.quest.SKD_DomAnri.win_condition.l1 = "location";
			PChar.quest.SKD_DomAnri.win_condition.l1.location = "PortRoyal_houseSp1";
			PChar.quest.SKD_DomAnri.win_condition = "SKD_DomAnri";
			pchar.GenQuestBox.PortRoyal_houseSp1.box1.items.chest = 1;
		break;
		
	}
} 
