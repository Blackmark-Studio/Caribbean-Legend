// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quais são as suas dúvidas?","Como posso ajudá-lo?"),"Você tentou me fazer essa pergunta não faz muito tempo...","É, deixa eu adivinhar... Dando voltas de novo?","Escute, eu cuido das finanças aqui, não respondo perguntas...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Não tenho nada para conversar no momento."),"Ah, onde foi parar minha memória...","Você adivinhou, me desculpe...","Entendi...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Sinistra Длинные тени старых грехов	
			if (CheckAttribute(pchar, "questTemp.DTSG_KnippelDolg"))
			{
				link.l1 = "Gostaria de falar com você sobre um dos seus devedores.";
				link.l1.go = "DTSG_KnippelDolg";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов	
		case "DTSG_KnippelDolg":
			DeleteAttribute(pchar, "questTemp.DTSG_KnippelDolg");
			dialog.text = "Qual deles?";
			if (sti(pchar.reputation.nobility) > 50)
			{
				link.l1 = "(Honra) Com certeza é o Charlie Knippel.";
				link.l1.go = "DTSG_KnippelDolg_VD_2";
			}
			else
			{
				link.l2 = "(Honra) Você tem a coragem de falar comigo tão calmamente. Você mandou caçadores de recompensa atrás do meu homem.";
				link.l2.go = "DTSG_KnippelDolg_2";
			}
		break;
		
		case "DTSG_KnippelDolg_VD_2":
			dialog.text = "Charlie? Mas ele já não é mais meu devedor. A dívida dele foi quitada faz tempo, senhor.";
			link.l1 = "Sério? Por quem, se não for segredo?";
			link.l1.go = "DTSG_KnippelDolg_VD_3";
		break;
		
		case "DTSG_KnippelDolg_VD_3":
			dialog.text = "It's not. By his captain, Richard Fleetwood. A true gentleman; everyone should have friends like him.";
			link.l1 = "Veja, agora sou o capitão do Charlie. O Sr. Fleetwood... transferiu ele para o meu comando. Fico feliz em saber que ele cumpriu a palavra e pagou você.";
			link.l1.go = "DTSG_KnippelDolg_VD_4";
		break;
		
		case "DTSG_KnippelDolg_VD_4":
			dialog.text = "Então é por isso que você está perguntando.";
			link.l1 = "Não só isso. Você conhece bem o Charlie, não é? Ele foi preso, e antes disso mandaram mercenários atrás dele. Sabe por quê? Afinal, você lida com um círculo de pessoas bem... diverso.";
			link.l1.go = "DTSG_KnippelDolg_VD_5";
		break;
		
		case "DTSG_KnippelDolg_VD_5":
			dialog.text = "Charlie foi preso? O senhor me surpreende, não sabia de nada disso. Nem sobre os... inimigos dele. Um homem bom, temente a Deus como ele...";
			link.l1 = "Não posso discordar disso. Bem, obrigado mesmo assim. Espero que o comandante aceite a fiança de mim.";
			link.l1.go = "DTSG_KnippelDolg_VD_6";
		break;
		
		case "DTSG_KnippelDolg_VD_6":
			dialog.text = "Não hesite em me procurar novamente se precisar de fundos para garantir a fiança – vou lhe oferecer boas condições.";
			link.l1 = "Ha-ha, está falando sério? Um agiota sempre será um agiota. Posso pagar a fiança sozinho. Adeus.";
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
			dialog.text = "Caçadores de recompensas? Atrás do seu homem? Do que você está falando?..";
			link.l1 = "Não negue. É melhor confessar, e resolvemos isso como cavalheiros. Mas se bancar o esperto, vou ter que lidar com você do jeito difícil.";
			link.l1.go = "DTSG_KnippelDolg_3";
		break;
		
		case "DTSG_KnippelDolg_3":
			dialog.text = "V-você deve estar enganado!.. Guarda!!! Ele está ameaçando me matar!";
			link.l1 = "Ah, pelo amor de Deus...";
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
