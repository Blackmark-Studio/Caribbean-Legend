// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("O que você deseja? Pode perguntar.","Estou ouvindo, qual é a pergunta?"),"Esta é a segunda vez que você tenta perguntar...","Esta é a terceira vez que você tenta perguntar...","Quando isso vai acabar?! Sou um homem ocupado, cuidando de assuntos coloniais, e você ainda continua me importunando!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia, desculpe.","Agora não. Lugar e hora errados."),"É verdade, não tenho nada a dizer no momento, desculpe.","Vou perguntar depois.","Sinto muito, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "huber")
			{
				link.l1 = "Monsieur Governador, trago notícias terríveis. Serei direto: sua esposa planeja roubá-lo. Ela tentou me convencer a arrombar um dos baús do seu gabinete. Achei que o senhor deveria saber disso.";
                link.l1.go = "FMQT";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+", Monsieur. Estou aqui a mando do Governador-Geral Chevalier de Poincy. Minha missão é trazer um barão chamado Noel Forget até Tortuga, que chegou da metrópole com ordens para inspecionar as colônias. Seu principal objetivo é fundar uma Companhia Francesa das Índias Ocidentais. Permita-me apresentá-lo... Ele mesmo explicará todos os detalhes.";
                link.l1.go = "patria_tortuga";
			}
		break;
		
		case "FMQT":
			dialog.text = "O quê? De novo? Aquela desgraçada! Ela vai se arrepender, juro! Kampacho vai fazer ela gritar. Por que você ainda está aqui? Cai fora daqui!";
			link.l1 = "Eu pensei...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 25) link.l1.go = "FMQT_2";
			else link.l1.go = "FMQT_1";
		break;
		
		case "FMQT_1":
			Notification_Skill(false, 26, SKILL_LEADERSHIP);
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "Sempre a mesma coisa! Aqui, pegue isto! É tudo o que tenho na mesa! Agora vá embora!";
			link.l1 = "Obrigado, Vossa Excelência. Eu mesmo me retiro.";
			link.l1.go = "FMQT_3";
		break;
		
		case "FMQT_2":
			AddMoneyToCharacter(pchar, 1000);
			GiveItem2Character(pchar, "pistol6");
			GiveItem2Character(pchar, "purse1");
			Log_Info("You have received a double barreled pistol and a purse of doubloons");
			dialog.text = "Sempre a mesma coisa! Aqui, pegue isso! É tudo o que tenho na mesa!.. Mas, tudo bem, você não parece com o resto dos idiotas e fracassados que enchem minha ilha. Pegue um pouco mais... Agora vá embora!";
			link.l1 = "Obrigado, Vossa Excelência. Eu mesmo me retiro.";
			link.l1.go = "FMQT_3";
		break;
		
		case "FMQT_3":
			DialogExit();
			pchar.quest.FMQT_late1.over = "yes";
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.FMQT = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Tortuga", "7");
			CloseQuestHeader("FMQ_Tortuga");
			FMQT_ClearChest();
		break;
		
		// Jason НСО
		case "patria_tortuga":
			dialog.text = "Muito bem, Capitão Charles de Maure. O barão será tratado como merece e farei o que estiver ao meu alcance para ajudá-lo em sua missão.";
			link.l1 = "";
			link.l1.go = "patria_tortuga_1";
		break;
		
		case "patria_tortuga_1":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
