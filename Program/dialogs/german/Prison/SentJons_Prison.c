// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Sprechen Sie, ich höre zu";
			link.l1 = "Ich habe mich geirrt. Lebewohl.";
			link.l1.go = "Exit";
			
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaZalog"))
			{
				link.l1 = "Kürzlich wurde Charlie Knippel von einem der Stadtsoldaten verhaftet und festgehalten. Ist er noch hier?"; 
				link.l1.go = "DTSG_AntiguaZalog_2";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов
		case "DTSG_AntiguaZalog_2":
			dialog.text = "Das stimmt, aber warum fragst du?";
			link.l1 = "Die Sache ist, Charlie ist einer meiner Offiziere. Ich würde gerne wissen, wessen er beschuldigt wird. Die Soldaten, die ihn mitgenommen haben, haben mir nichts gesagt."; 
			link.l1.go = "DTSG_AntiguaZalog_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaZalog_3":
			dialog.text = "Richtig. Das ist kein Allgemeinwissen. Leider auch nicht für Sie. Es ist ein Staatsgeheimnis, Herr.";
			link.l1 = "Also, ich nehme an, eine Kaution ist keine Option?"; 
			link.l1.go = "DTSG_AntiguaZalog_4";
		break;
		
		case "DTSG_AntiguaZalog_4":
			dialog.text = "Genau. Ich verstehe, dass es unangenehm ist, einen wertvollen Crewmitglied zu verlieren, aber weder Sie noch ich können etwas dagegen tun. Es tut mir sehr leid, Kapitän.";
			link.l1 = "Keine Kaution, sehe ich. Wie wäre es dann mit... einer Entschädigung? Eine großzügige, sollte ich hinzufügen. Für Sie und all Ihre Männer, damit niemand ausgelassen wird."; 
			link.l1.go = "DTSG_AntiguaZalog_5";
		break;
		
		case "DTSG_AntiguaZalog_5":
			dialog.text = "Eine Bestechung? Mutig von Ihnen, Kapitän, aber kein Geldbetrag wird uns vor dem Zorn derjenigen retten, die herausfinden, dass wir Charlie haben gehen lassen.";
			link.l1 = "Vielleicht... Aber kann ich zumindest mit ihm sprechen?"; 
			link.l1.go = "DTSG_AntiguaZalog_6";
		break;
		
		case "DTSG_AntiguaZalog_6":
			dialog.text = "Warum nicht? Du kannst nichts tun, um ihm zu helfen oder ihm bei der Flucht zu helfen, also... nur zu. Er ist in einer der Zellen.";
			link.l1 = "Ha, und wenn er mir sagt, wofür er angeklagt ist und dieses Staatsgeheimnis enthüllt, das Ihnen so am Herzen liegt, Offizier?"; 
			link.l1.go = "DTSG_AntiguaZalog_7";
		break;
		
		case "DTSG_AntiguaZalog_7":
			dialog.text = "Ich mache mir darüber keine Sorgen. Du wirst verstehen warum. Geh, sprich mit deinem ehemaligen Offizier, bevor ich meine Meinung ändere.";
			link.l1 = "Danke."; 
			link.l1.go = "DTSG_AntiguaZalog_8";
		break;
		
		case "DTSG_AntiguaZalog_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaZalog");
			pchar.questTemp.jailCanMove = true;
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto9");
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Killer", "sold_eng_10", "man", "man", int(pchar.rank), PIRATE, -1, false, "quest"));
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Killer";
			LAi_SetStayType(sld);
			sld.talker = 5;
			GiveItem2Character(sld, "blade_14");
			EquipCharacterbyItem(sld, "blade_14");
			GiveItem2Character(sld, "pistol4");
			EquipCharacterbyItem(sld, "pistol4");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload12");
			sld.rank = 30;
			SetSelfSkill(sld, 80, 80, 80, 80, 80);
			LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
			LAi_SetImmortal(sld, true);
		break;
		
		case "DTSG_AntiguaTrevoga_2":
			dialog.text = "Es besteht keine Notwendigkeit, Kapitän. Wie ich sagte, wären Sie in dieselbe Zelle mit diesem Narren Charlie geworfen worden. Aber erstens schätzte der Gouverneur, dass Sie der Verhaftung nicht widerstanden haben, und zweitens war er nicht erfreut über den jüngsten Besuch des Geldverleihers, dessen Schreie fast die Fenster im Palast zerschmettert hätten...";
			link.l1 = "Er hat meine Verhaftung gefordert?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaTrevoga_3":
			dialog.text = "Er hat nicht gefragt - er hat verlangt. Und Seine Exzellenz mag es nicht, zu etwas gezwungen zu werden. Daher wurde diesem Wucherer die Tür gezeigt.";
			link.l1 = "Lustig. Jetzt..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_4";
		break;
		
		case "DTSG_AntiguaTrevoga_4":
			dialog.text = "Nun schlage ich vor, dass Sie dasselbe tun, Kapitän de Maure. Und stellen Sie keine Fragen, auf die Sie keine Antworten erhalten werden.";
			link.l1 = "Ich werde hier nicht ohne Charlie Knippel gehen."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H1";
			link.l2 = "Bitte, Herr, lassen Sie mich mit Charlie Knippel sprechen. Oder zumindest herausfinden, was..."; 
			link.l2.go = "DTSG_AntiguaTrevoga_Ch1";
		break;
		
		case "DTSG_AntiguaTrevoga_H1":
			dialog.text = "In diesem Fall, schließe dich ihm an. Nicht in einer Zelle, sondern im Jenseits.";
			link.l1 = "Also, er ist tot..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H2";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_H2":
			dialog.text = "Du bist verdammt scharfsinnig, Kapitän. Und ich hoffe, du weißt, dass ich dir nicht sagen werde, wer es getan hat oder warum.";
			link.l1 = "So ist das also?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_H3";
		break;
		
		case "DTSG_AntiguaTrevoga_H3":
			dialog.text = "Genau. Und jetzt prüfe meine Geduld nicht - bevor ich dich wegen Tötung eines englischen Soldaten in eine Zelle werfen lasse.";
			link.l1 = "Wenn man bedenkt, dass nicht viele aus Ihren Zellen herauskommen, würde ich nicht dort landen wollen. Ich wünsche Ihnen keinen guten Tag."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_Ch1":
			dialog.text = "Charlie Knippel spricht mit niemandem. Außer vielleicht mit dem Schöpfer...";
			link.l1 = "Er ist tot?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_Ch2";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_Ch2":
			dialog.text = "Das Urteil wurde vollstreckt. Ich kann Ihnen keine Details geben. Und ich hoffe, Sie bestehen nicht darauf - es könnte schlecht für Sie enden. Nicht nur mit einer Zelle. Habe ich mich klar ausgedrückt, Kapitän de Mor?";
			link.l1 = "Mehr als klar. Auf Wiedersehen."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaTrevoga");
			AddQuestRecord("DTSG", "10");
			CloseQuestHeader("DTSG");
			ChangeCharacterComplexReputation(pchar, "authority", -10);
			AddCrewMorale(Pchar, -30);
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
