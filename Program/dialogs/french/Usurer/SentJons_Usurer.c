// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions avez-vous ?","Comment puis-je vous aider ?"),"Vous avez essayé de me poser cette question il n'y a pas longtemps...","Oui, laissez-moi deviner... Encore en train de tourner en rond ?","Ecoutez, je m'occupe des finances ici, je ne réponds pas aux questions...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Où est donc passée ma mémoire...","Vous avez deviné, je suis désolé...","Je comprends...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Sinistra Длинные тени старых грехов	
			if (CheckAttribute(pchar, "questTemp.DTSG_KnippelDolg"))
			{
				link.l1 = "Je voudrais vous parler de l'un de vos débiteurs.";
				link.l1.go = "DTSG_KnippelDolg";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов	
		case "DTSG_KnippelDolg":
			DeleteAttribute(pchar, "questTemp.DTSG_KnippelDolg");
			dialog.text = "Lequel ?";
			if (int(pchar.reputation.nobility) > 50)
			{
				link.l1 = "(Honneur) C'est certain Charlie Knippel.";
				link.l1.go = "DTSG_KnippelDolg_VD_2";
			}
			else
			{
				link.l2 = "(Honneur) Vous avez le culot de me parler si calmement. Vous avez envoyé des chasseurs de primes après mon homme.";
				link.l2.go = "DTSG_KnippelDolg_2";
			}
		break;
		
		case "DTSG_KnippelDolg_VD_2":
			dialog.text = "Charlie ? Mais il n'est plus mon débiteur. Sa dette a été réglée il y a longtemps, monsieur.";
			link.l1 = "Vraiment ? Par qui, si ce n'est pas un secret ?";
			link.l1.go = "DTSG_KnippelDolg_VD_3";
		break;
		
		case "DTSG_KnippelDolg_VD_3":
			dialog.text = "Ce n'est pas. Par son capitaine, Richard Fleetwood. Un vrai gentilhomme, tout le monde devrait avoir des amis comme lui.";
			link.l1 = "Vous voyez, je suis maintenant le capitaine de Charlie. M. Fleetwood... l'a transféré à mon service. C'est bon de savoir qu'il a tenu sa promesse et vous a payé.";
			link.l1.go = "DTSG_KnippelDolg_VD_4";
		break;
		
		case "DTSG_KnippelDolg_VD_4":
			dialog.text = "Ah, c'est donc pourquoi vous demandez.";
			link.l1 = "Pas seulement cela. Vous connaissez bien Charlie, n'est-ce pas? Il a été arrêté, et auparavant des mercenaires ont été envoyés à sa poursuite. Une idée de la raison? Après tout, vous avez des affaires avec un cercle de personnes très... diversifié.";
			link.l1.go = "DTSG_KnippelDolg_VD_5";
		break;
		
		case "DTSG_KnippelDolg_VD_5":
			dialog.text = "Charlie arrêté ? Vous me surprenez, monsieur, je n'étais pas au courant. Ni de ses... ennemis. Un bon homme, craignant Dieu, comme lui...";
			link.l1 = "On ne peut pas contester cela. Eh bien, merci quand même. J'espère que le commandant acceptera ma caution.";
			link.l1.go = "DTSG_KnippelDolg_VD_6";
		break;
		
		case "DTSG_KnippelDolg_VD_6":
			dialog.text = "N'hésitez pas à revenir me voir si vous avez besoin de fonds pour obtenir la caution - je vous offrirai de bonnes conditions.";
			link.l1 = "Ha-ha, es-tu sérieux ? Un prêteur sur gages sera toujours un prêteur sur gages. Je peux me permettre la caution moi-même. Adieu.";
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
			dialog.text = "Chasseurs de primes ? Après votre homme ? De quoi parlez-vous ?..";
			link.l1 = "Ne le niez pas. Mieux vaut avouer, et nous réglerons cela comme des gentlemen. Mais si vous faites l'idiot, je devrai m'occuper de vous à la dure.";
			link.l1.go = "DTSG_KnippelDolg_3";
		break;
		
		case "DTSG_KnippelDolg_3":
			dialog.text = "V-vous devez vous tromper!.. Garde !!! Il menace de me tuer !";
			link.l1 = "Oh pour l'amour du ciel...";
			link.l1.go = "DTSG_KnippelDolg_4";
		break;
		
		case "DTSG_KnippelDolg_4":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaStrazhBank_1", "sold_eng_"+(rand(15)+1), "man", "man", 10, ENGLAND, 0, false, "soldier"));
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
