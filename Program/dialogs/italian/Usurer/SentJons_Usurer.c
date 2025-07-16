// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti?"),"Hai cercato di farmi quella domanda poco tempo fa...","Sì, fammi indovinare... Ancora una volta girando in tondo?","Ascolta, io gestisco le finanze qui, non rispondo alle domande...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mi sono ricreduto...","Non ho nulla di cui parlare al momento."),"Uh, dove se n'è andata la mia memoria...","L'hai indovinato, mi dispiace...","Capisco...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Sinistra Длинные тени старых грехов	
			if (CheckAttribute(pchar, "questTemp.DTSG_KnippelDolg"))
			{
				link.l1 = "Vorrei parlare con te di uno dei tuoi debitori.";
				link.l1.go = "DTSG_KnippelDolg";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов	
		case "DTSG_KnippelDolg":
			DeleteAttribute(pchar, "questTemp.DTSG_KnippelDolg");
			dialog.text = "Quale?";
			if (sti(pchar.reputation.nobility) > 50)
			{
				link.l1 = "(Onore) È sicuramente Charlie Knippel.";
				link.l1.go = "DTSG_KnippelDolg_VD_2";
			}
			else
			{
				link.l2 = "(Onore) Hai il coraggio di parlarmi così tranquillamente. Hai mandato cacciatori di taglie dietro al mio uomo.";
				link.l2.go = "DTSG_KnippelDolg_2";
			}
		break;
		
		case "DTSG_KnippelDolg_VD_2":
			dialog.text = "Charlie? Ma lui non è più mio debitore. Il suo debito è stato saldato molto tempo fa, signore.";
			link.l1 = "Davvero? Da chi, se non è un segreto?";
			link.l1.go = "DTSG_KnippelDolg_VD_3";
		break;
		
		case "DTSG_KnippelDolg_VD_3":
			dialog.text = "Non lo è. Per suo capitano, Richard Fleetwood. Un vero gentiluomo, tutti dovrebbero avere amici come lui.";
			link.l1 = "Vedi, ora sono il capitano di Charlie. Il signor Fleetwood... lo ha trasferito al mio servizio. È bello sapere che ha mantenuto la sua promessa e ti ha pagato.";
			link.l1.go = "DTSG_KnippelDolg_VD_4";
		break;
		
		case "DTSG_KnippelDolg_VD_4":
			dialog.text = "Allora è per questo che stai chiedendo.";
			link.l1 = "Non solo quello. Conosci bene Charlie, giusto? È stato arrestato, e prima gli sono stati inviati dei mercenari. Hai idea del perché? Dopotutto, hai a che fare con un cerchio di persone molto... diverso.";
			link.l1.go = "DTSG_KnippelDolg_VD_5";
		break;
		
		case "DTSG_KnippelDolg_VD_5":
			dialog.text = "Charlie arrestato? Mi ha sorpreso, signore, non sapevo nulla a riguardo. Nemmeno sui suoi... nemici. Un bravo uomo, temente Dio, come lui...";
			link.l1 = "Non posso discutere su questo. Beh, grazie comunque. Spero che il comandante accetterà la mia cauzione.";
			link.l1.go = "DTSG_KnippelDolg_VD_6";
		break;
		
		case "DTSG_KnippelDolg_VD_6":
			dialog.text = "Non esitare a rivolgerti a me di nuovo se hai bisogno di fondi per garantire la cauzione - ti darò buone condizioni.";
			link.l1 = "Ah-ah, stai scherzando? Un usuraio sarà sempre un usuraio. Posso permettermi la cauzione da solo. Addio.";
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
			dialog.text = "Cacciatori di taglie? Dopo il tuo uomo? Di cosa stai parlando?..";
			link.l1 = "Non negarlo. Meglio confessare, e risolveremo la questione come gentiluomini. Ma se fai l'ignorante, dovrò occuparmi di te nel modo più duro.";
			link.l1.go = "DTSG_KnippelDolg_3";
		break;
		
		case "DTSG_KnippelDolg_3":
			dialog.text = "D-dovete sbagliarvi!.. Guardia!!! Mi sta minacciando di uccidermi!";
			link.l1 = "Oh per l'amor di Dio...";
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
