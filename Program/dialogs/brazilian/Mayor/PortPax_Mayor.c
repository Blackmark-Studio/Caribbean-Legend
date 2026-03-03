// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("O que você deseja? Pode perguntar.","Estou ouvindo você, qual é a sua pergunta?"),"Esta é a segunda vez que você tenta perguntar...","Esta é a terceira vez que você tenta perguntar...","Quando isso vai acabar?! Sou um homem ocupado, cuidando dos assuntos da colônia, e você ainda está me importunando!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia...","Agora não. Lugar e hora errados."),"Verdade... Mas depois, não agora...","Vou perguntar... Mas um pouco mais tarde...","Me desculpe, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+"Monsieur. Estou aqui a mando do Governador-Geral Chevalier de Poincy. Minha missão é escoltar um barão chamado Noel Forget até Tortuga, que chegou da metrópole com a tarefa de inspecionar as colônias. Seu principal objetivo é fundar uma Companhia Francesa das Índias Ocidentais. Permita-me apresentá-lo a você... Ele mesmo explicará todos os detalhes.";
                link.l1.go = "patria_portpax";
			}
			// Rebbebion, квест "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk"))
			{
				link.l1 = "Vossa Senhoria, desejava me ver?";
				link.l1.go = "PZ_1";
			}
			// Украденное воспоминание
			if (CheckAttribute(pchar, "questTemp.UV_DialogMayor"))
			{
				link.l1 = "Excelência, venho trazendo informações de natureza extremamente delicada que exigem sua atenção.";
				link.l1.go = "UV_1";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Você já levou tudo. O que mais você quer?","Ficou alguma coisa que você ainda não pegou?");
            link.l1 = RandPhraseSimple("Só dando uma olhada...","Só conferindo, posso acabar esquecendo de pegar alguma coisa...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		// Jason НСО
		case "patria_portpax":
			dialog.text = "Estou muito feliz em conhecê-lo, Capitão Charles de Maure, e também o Barão. Farei tudo para garantir que a estadia do Monsieur Forget em nossa colônia seja a mais confortável possível. E aproveitando que um Monsieur de tão alta posição me faz uma visita, gostaria de lhe apresentar um pedido.";
			link.l1 = "Muito interessante! Conte-nos sobre seus negócios, sua Graça.";
			link.l1.go = "patria_portpax_1";
		break;
		
		case "patria_portpax_1":
			dialog.text = "Nos últimos meses, nossa colônia não recebeu a visita de nenhum representante do Governador-Geral, como se tivessem nos esquecido completamente aqui em Saint Kitts! Enquanto isso, os espanhóis, ansiosos para tornar toda Hispaniola inteiramente espanhola e para quem os colonos franceses e bucaneiros no oeste da ilha são um grande incômodo, estão preparando um ataque! Meus oficiais de patrulha, nossos capitães mercantes e até mesmo pescadores comuns relataram que uma poderosa esquadra espanhola está se reunindo em Santiago e que está se preparando para atacar Port-au-Prince!";
			link.l1 = "A evidência está clara o suficiente, Vossa Majestade?";
			link.l1.go = "patria_portpax_2";
		break;
		
		case "patria_portpax_2":
			dialog.text = "Não tenho informações precisas, mas tantas notícias vindas de pessoas tão diferentes não podem ser apenas boatos. Nossa colônia é muito importante para a França, temos aqui as melhores plantações, que o Barão pode ver com os próprios olhos. Perder esta colônia, ou até mesmo expô-la ao risco de ser saqueada, é inaceitável!";
			link.l1 = "Vou levar suas provas em consideração e informar o Chevalier de Poincy. Tenho certeza de que ele tomará medidas imediatas.";
			link.l1.go = "patria_portpax_3";
		break;
		
		case "patria_portpax_3":
			dialog.text = "Obrigado, capitão...";
			link.l1 = "";
			link.l1.go = "patria_portpax_4";
		break;
		
		case "patria_portpax_4":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
		
		case "PZ_1":
			DeleteAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk");
			dialog.text = "Não, eu não o chamei, monsieur. Deseja algo?";
			link.l1 = "How could I? But your messenger met us; he said you had prepared one of the houses in the town for me...";
			link.l1.go = "PZ_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_2":
			dialog.text = "Que casa, que mensageiro, que insolência é essa?!";
			link.l1 = "Como assim, que mensageiro... O nome dele é Henri Thibaut, e...";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "O QUÊ? Você ao menos sabe quem ele é? Pelo visto não. Mas isso não importa. O que o sobrinho de Levasseur está fazendo na minha cidade?";
			link.l1 = "Meu Deus...";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "De Maure, consegue me ouvir? Monsieur?";
			link.l1 = "...";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload1", "PZ_SharleBezhitObratno", -1);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			SetMusic("music_teleport");
			pchar.questTemp.lockedMusic = true;
		break;
		
		//--> Украденное воспоминание
		case "UV_1":
			dialog.text = "Um assunto delicado, diz você? Agora fiquei interessado, Capitão. Por favor, continue—tem toda a minha atenção.";
			link.l1 = "A questão diz respeito à sua sobrinha, Julie. Ela me procurou para recuperar um colar que havia sido roubado dela.";
			link.l1.go = "UV_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			DelLandQuestMark(npchar);
		break;

		case "UV_2":
			dialog.text = "Um colar? Curioso. Não me lembro de nenhum objeto assim entre os pertences dela.";
			link.l1 = "Permita-me apresentar os fatos em ordem, Governador. Consegui recuperar o colar em questão. Minha investigação revelou que a ladra foi a dama de companhia de sua sobrinha, Giselle. Pelas minhas observações sobre o comerciante que comprou o item roubado, suspeito fortemente que esta não foi a primeira nem será a última transgressão dela.";
			link.l1.go = "UV_3";
		break;

		case "UV_3":
			dialog.text = "Muito esclarecedor. Por favor, continue com seu relato.";
			link.l1 = "O que me chamou a atenção, Excelência, foi que Julie optou por não buscar sua ajuda neste assunto. O colar, ao que parece, foi um presente de alguém com quem a senhora expressamente proibiu que ela se relacionasse. Acreditando que suas restrições partem das intenções mais sábias e protetoras, senti-me na obrigação de trazer este assunto ao seu conhecimento e devolver o colar diretamente à senhora.";
			link.l1.go = "UV_4";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
		break;

		case "UV_4":
			dialog.text = "Seu julgamento se mostra sensato"+GetSexPhrase(", Capitão","")+". Agradeço sua discrição em trazer isso diretamente a mim, em vez de alimentar as imprudências juvenis de minha sobrinha.";
			link.l1 = "Eu ajo apenas pensando no bem-estar dela, Governador. Não tenho dúvidas de que sua orientação também nasce dessa mesma fonte de preocupação e sabedoria.";
			link.l1.go = "UV_5";
		break;

		case "UV_5":
			dialog.text = "De fato, Capitão. Como tio e tutor dela, o bem-estar dela é minha maior prioridade. Por favor, aceite estes cento e cinquenta dobrões como um sinal da minha gratidão pela sua discrição. Também lhe entrego esta bússola de navegação—que ela possa guiá-lo em segurança por suas jornadas através de águas traiçoeiras.";
			link.l1 = "Sinto-me honrado por sua generosidade, Excelência, embora tal recompensa fosse desnecessária. Infelizmente, devo agora me despedir— a maré não espera por nenhum marinheiro, e minha embarcação exige minha atenção.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_End");
			AddItems(pchar, "gold_dublon", 150);
			GiveItem2Character(PChar, "compass1");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		//<-- Украденное воспоминание
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
