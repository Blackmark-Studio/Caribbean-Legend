// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Welche Fragen haben Sie?","Wie kann ich Ihnen helfen?"),"Du hast versucht, mir diese Frage vor nicht allzu langer Zeit zu stellen...","Ja, lass mich raten... Wieder im Kreis unterwegs?","Hör zu, ich mache hier die Finanzen, ich beantworte keine Fragen...","Block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ich habe es mir anders überlegt...","Ich habe im Moment nichts zu besprechen."),"Umph, wo ist mein Gedächtnis hin...","Du hast es erraten, es tut mir leid...","Ich verstehe...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Sinistra Длинные тени старых грехов	
			if (CheckAttribute(pchar, "questTemp.DTSG_KnippelDolg"))
			{
				link.l1 = "Ich möchte mit Ihnen über einen Ihrer Schuldner sprechen.";
				link.l1.go = "DTSG_KnippelDolg";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов	
		case "DTSG_KnippelDolg":
			DeleteAttribute(pchar, "questTemp.DTSG_KnippelDolg");
			dialog.text = "Welcher?";
			if (int(pchar.reputation.nobility) > 50)
			{
				link.l1 = "(Ehre) Es ist sicher Charlie Knippel.";
				link.l1.go = "DTSG_KnippelDolg_VD_2";
			}
			else
			{
				link.l2 = "(Ehre) Du hast den Nerv, so ruhig mit mir zu reden. Du hast Kopfgeldjäger auf meinen Mann angesetzt.";
				link.l2.go = "DTSG_KnippelDolg_2";
			}
		break;
		
		case "DTSG_KnippelDolg_VD_2":
			dialog.text = "Charlie? Aber er ist nicht mehr mein Schuldner. Seine Schuld wurde schon vor langer Zeit beglichen, Herr.";
			link.l1 = "Wirklich? Von wem, wenn es kein Geheimnis ist?";
			link.l1.go = "DTSG_KnippelDolg_VD_3";
		break;
		
		case "DTSG_KnippelDolg_VD_3":
			dialog.text = "Es ist nicht. Von seinem Kapitän, Richard Fleetwood. Ein wahrer Gentleman, jeder sollte Freunde wie ihn haben.";
			link.l1 = "Sie sehen, ich bin jetzt Charlies Kapitän. Herr Fleetwood... hat ihn in meinen Dienst überstellt. Es ist gut zu wissen, dass er sein Versprechen gehalten und Sie bezahlt hat.";
			link.l1.go = "DTSG_KnippelDolg_VD_4";
		break;
		
		case "DTSG_KnippelDolg_VD_4":
			dialog.text = "Also deshalb fragst du.";
			link.l1 = "Nicht nur das. Du kennst Charlie gut, oder? Er wurde verhaftet, und zuvor wurden Söldner auf ihn angesetzt. Irgendeine Idee warum? Schließlich hast du Geschäfte mit einem sehr... vielfältigen Kreis von Leuten.";
			link.l1.go = "DTSG_KnippelDolg_VD_5";
		break;
		
		case "DTSG_KnippelDolg_VD_5":
			dialog.text = "Charlie verhaftet? Sie überraschen mich, Herr, ich wusste nichts davon. Auch nicht über seine... Feinde. Ein guter, gottesfürchtiger Mann wie er...";
			link.l1 = "Mit dem kann man nicht streiten. Nun, danke trotzdem. Ich hoffe, der Kommandant akzeptiert meine Kaution.";
			link.l1.go = "DTSG_KnippelDolg_VD_6";
		break;
		
		case "DTSG_KnippelDolg_VD_6":
			dialog.text = "Zögern Sie nicht, mich erneut anzusprechen, wenn Sie Geldmittel benötigen, um die Kaution zu sichern - Ich werde Ihnen gute Konditionen anbieten.";
			link.l1 = "Ha-ha, bist du ernst? Ein Geldverleiher wird immer ein Geldverleiher sein. Ich kann die Kaution selbst bezahlen. Auf Wiedersehen.";
			link.l1.go = "DTSG_KnippelDolg_VD_7";
		break;
		
		case "DTSG_KnippelDolg_VD_7":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			AddQuestRecord("DTSG", "11");
			pchar.questTemp.DTSG_AntiguaZalog = true;
			AddLandQuestMarkToPhantom("SentJons_prison", "SentJonsJailOff");
		break;
		
		case "DTSG_KnippelDolg_2":
			dialog.text = "Kopfgeldjäger? Auf der Suche nach Ihrem Mann? Wovon reden Sie?..";
			link.l1 = "Leugne es nicht. Besser gestehen Sie, und wir werden es wie Gentlemen klären. Aber wenn Sie sich dumm stellen, muss ich auf die harte Tour mit Ihnen umgehen.";
			link.l1.go = "DTSG_KnippelDolg_3";
		break;
		
		case "DTSG_KnippelDolg_3":
			dialog.text = "Du... du musst dich irren!.. Wache!!! Er droht, mich zu töten!";
			link.l1 = "Ach zum Teufel...";
			link.l1.go = "DTSG_KnippelDolg_4";
		break;
		
		case "DTSG_KnippelDolg_4":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaStrazhBank_1", "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, false, "soldier"));
			GiveItem2Character(sld, "blade_10");
			EquipCharacterByItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterByItem(sld, "pistol1");
			ChangeCharacterAddressGroup(sld, "SentJons_bank", "reload", "reload1");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_AntiguaStrazhBank";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			LAi_SetHP(sld, 140+MOD_SKILL_ENEMY_RATE*10, 140+MOD_SKILL_ENEMY_RATE*10);
			AddLandQuestMarkToPhantom("SentJons_prison", "SentJonsJailOff");
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
