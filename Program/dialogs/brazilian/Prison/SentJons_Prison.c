// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Fale, estou ouvindo";
			link.l1 = "Eu estava enganado. Adeus.";
			link.l1.go = "Exit";
			
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaZalog"))
			{
				link.l1 = "Recentemente, um dos soldados da cidade prendeu e deteve Charlie Knippel. Ele ainda está aqui?"; 
				link.l1.go = "DTSG_AntiguaZalog_2";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов
		case "DTSG_AntiguaZalog_2":
			dialog.text = "Isso mesmo, mas por que a pergunta?";
			link.l1 = "O problema é que o Charlie é um dos meus oficiais. Eu gostaria de saber do que ele está sendo acusado. Os soldados que o levaram não me disseram nada."; 
			link.l1.go = "DTSG_AntiguaZalog_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaZalog_3":
			dialog.text = "Certo. Não é algo de conhecimento geral. Infelizmente, nem mesmo para você. É um segredo de Estado, senhor.";
			link.l1 = "Então, imagino que fiança não seja uma opção?"; 
			link.l1.go = "DTSG_AntiguaZalog_4";
		break;
		
		case "DTSG_AntiguaZalog_4":
			dialog.text = "Exatamente. Eu entendo que é desagradável perder um tripulante valioso, mas nem você nem eu podemos fazer nada a respeito. Sinto muito, Capitão.";
			link.l1 = "Sem fiança, entendi. Então que tal... uma compensação? Bem generosa, devo dizer. Para você e todos os seus homens, para que ninguém fique de fora."; 
			link.l1.go = "DTSG_AntiguaZalog_5";
		break;
		
		case "DTSG_AntiguaZalog_5":
			dialog.text = "Suborno? Corajoso da sua parte, Capitão, mas nenhum dinheiro do mundo vai nos salvar da fúria de quem descobrir que deixamos Charlie escapar.";
			link.l1 = "Talvez... Mas posso ao menos falar com ele?"; 
			link.l1.go = "DTSG_AntiguaZalog_6";
		break;
		
		case "DTSG_AntiguaZalog_6":
			dialog.text = "Por que não? Você não pode fazer nada para resgatá-lo ou ajudá-lo a fugir, então... vá em frente. Ele está em uma das celas.";
			link.l1 = "Ha, e se ele me contar do que é acusado e revelar esse segredo de Estado que tanto te preocupa, oficial?"; 
			link.l1.go = "DTSG_AntiguaZalog_7";
		break;
		
		case "DTSG_AntiguaZalog_7":
			dialog.text = "Não me preocupo com isso. Você vai entender o motivo. Vá, converse com seu antigo oficial antes que eu mude de ideia.";
			link.l1 = "Obrigado."; 
			link.l1.go = "DTSG_AntiguaZalog_8";
		break;
		
		case "DTSG_AntiguaZalog_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaZalog");
			pchar.questTemp.jailCanMove = true;
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto9");
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Killer", "sold_eng_10", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
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
			dialog.text = "Não é necessário, Capitão. Como eu disse, você teria sido jogado na mesma cela daquele tolo do Charlie. Mas, primeiro, o Governador apreciou o fato de você não ter resistido à prisão, e segundo, ele não ficou nada satisfeito com a recente visita do agiota, cujos gritos quase estouraram as janelas do palácio...";
			link.l1 = "Ele pediu para me prenderem?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaTrevoga_3":
			dialog.text = "Ele não pediu – ele exigiu. E Sua Excelência não gosta que lhe exijam nada. Por isso, aquele agiota foi posto para fora.";
			link.l1 = "Hilário. Agora..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_4";
		break;
		
		case "DTSG_AntiguaTrevoga_4":
			dialog.text = "Agora sugiro que faça o mesmo, Capitão de Maure. E não faça perguntas para as quais não terá resposta.";
			link.l1 = "Não vou sair daqui sem o Charlie Knippel."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H1";
			link.l2 = "Por favor, senhor, deixe-me falar com Charlie Knippel. Ou pelo menos descobrir o que..."; 
			link.l2.go = "DTSG_AntiguaTrevoga_Ch1";
		break;
		
		case "DTSG_AntiguaTrevoga_H1":
			dialog.text = "Nesse caso, junte-se a ele. Não na cela, mas no além.";
			link.l1 = "Então, ele está morto..."; 
			link.l1.go = "DTSG_AntiguaTrevoga_H2";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_H2":
			dialog.text = "Você é mesmo muito perspicaz, Capitão. E espero que entenda que não vou te dizer quem fez isso ou por quê.";
			link.l1 = "É mesmo?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_H3";
		break;
		
		case "DTSG_AntiguaTrevoga_H3":
			dialog.text = "Exatamente. E agora não teste a minha paciência – antes que eu mande te jogar numa cela por matar um soldado inglês.";
			link.l1 = "Considerando que poucos saem dessas celas, eu não gostaria de acabar lá. Não vou te desejar um bom dia."; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_Ch1":
			dialog.text = "Charlie Knippel não fala com ninguém. Talvez só com o Criador...";
			link.l1 = "Ele está morto?"; 
			link.l1.go = "DTSG_AntiguaTrevoga_Ch2";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_Ch2":
			dialog.text = "A sentença foi cumprida. Não posso te dar detalhes. E espero que não insista – isso pode acabar mal pra você. Não só com uma cela. Fui claro, Capitão de Mor?";
			link.l1 = "Perfeitamente claro. Adeus."; 
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
