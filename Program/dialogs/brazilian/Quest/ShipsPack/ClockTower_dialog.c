int iClockSP4PseudoGlobal = SOUND_INVALID_ID;

void ProcessDialogEvent()
{
	ref NPChar, sld, realShip;
	aref Link, NextDiag, arTmp;
	int i, n, NextMonth, idx;
	string sTemp, sStr, Month, NationName, shipType;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	if (HasSubStr(Dialog.CurrentNode, "chosenIdx/"))
	{
		Dialog.tmpIdx = FindStringAfterChar(Dialog.CurrentNode, "/");
		Dialog.CurrentNode = FindStringBeforeChar(Dialog.CurrentNode, "/");
	}

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "O que você quer?";
			link.l1 = "Ничего.";
			link.l1.go = "exit";
		break;
		
		// Диалог с Йоханом
		case "ClockTower_Johan_1":
			dialog.text = "Pare aí, senhor capitão. Ninguém passa além deste ponto.";
			link.l1 = "Por que não?";
			link.l1.go = "ClockTower_Johan_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_2":
			dialog.text = "Tá vendo aquela torre? Escritório da Companhia Holandesa das Índias Ocidentais. Departamento de registro de navios e arquivo. Só entra com hora marcada.";
			link.l1 = "E como se consegue uma audiência?";
			link.l1.go = "ClockTower_Johan_3";
		break;

		case "ClockTower_Johan_3":
			dialog.text = "Aqueles que precisam saber, sabem. O senhor diretor não trabalha com qualquer um.";
			link.l1 = "'Mynheer diretor'? Quem é esse?";
			link.l1.go = "ClockTower_Johan_4";
		break;

		case "ClockTower_Johan_4":
			dialog.text = "Diretor van Doorn. Talvez ele nem seja exatamente um diretor, mas é assim que todo mundo chama. Trabalha aqui há dez anos — colocou ordem em tudo. Agora, todo navio no Caribe passa pelo escritório dele.";
			link.l1 = "Todo tipo de navio? Até navios de guerra?";
			link.l1.go = "ClockTower_Johan_5";
		break;

		case "ClockTower_Johan_5":
			dialog.text = "Apenas os navios mais finos e os capitães mais ricos. Ser cliente do nosso escritório é uma grande honra!";
			link.l1 = "Que tipo de serviços você oferece?";
			link.l1.go = "ClockTower_Johan_6";
		break;

		case "ClockTower_Johan_6":
			dialog.text = "Não sei dos detalhes — só faço a guarda da entrada. Mas ouvi dizer que quem entra sai satisfeito.";
			link.l1 = "Impressionante.";
			link.l1.go = "ClockTower_Johan_7";
		break;
		
		case "ClockTower_Johan_7":
			dialog.text = "E vou te dizer mais uma coisa. Tá vendo aquele relógio? Uma maravilha europeia — você não vai encontrar nada parecido nesse fim de mundo. O próprio senhor diretor faz questão de cuidar dele.";
			link.l1 = "Talvez possamos chegar a um acordo?";
			link.l1.go = "ClockTower_Johan_8_1";
			link.l2 = "Com certeza tem algo que eu possa fazer pra entrar?";
			link.l2.go = "ClockTower_Johan_8_2";
		break;

		case "ClockTower_Johan_8_1":
			dialog.text = "Eu não aceito suborno!";
			link.l1 = "Me desculpe. Você é um bom homem. Qual é o seu nome?";
			link.l1.go = "ClockTower_Johan_9";
		break;
		
		case "ClockTower_Johan_9":
			dialog.text = ""+npchar.name+"... Olha... Eu entendo que você não é daqui. Mas aqui temos ordem. O senhor diretor sempre diz: mostre fraqueza uma vez, e nossa torre desaba. Quer entrar? Ajude a cidade — e você será notado.";
			link.l1 = "Entendi. Fique atento, soldado.";
			link.l1.go = "ClockTower_Johan_11";
		break;

		case "ClockTower_Johan_8_2":
			dialog.text = "Olha, eu não sei. O senhor diretor recompensa os amigos de Willemstad. Ajude a cidade — e você será notado. Eu sei que você não é daqui. Mas aqui temos ordem. O senhor diretor sempre diz: mostre fraqueza uma vez, e nossa torre desaba.";
			link.l1 = "Entendi. E qual é o seu nome?";
			link.l1.go = "ClockTower_Johan_10";
		break;
		
		case "ClockTower_Johan_10":
			dialog.text = ""+npchar.name+", "+GetTitle(NPChar,true)+".";
			link.l1 = "E eu estou "+GetTitle(NPChar,false)+" "+GetFullName(pchar)+". Fique atento, soldado.";
			link.l1.go = "ClockTower_Johan_11";
		break;
		
		case "ClockTower_Johan_11":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_1");
		break;
		
		case "ClockTower_Johan_repeat":
			if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) >= 51)
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"!";
				link.l1 = "Aconteceu alguma coisa?";
				link.l1.go = "ClockTower_Johan_22";
				Notification_ReputationNation(true, 51, HOLLAND);
			}
			else 
			{
				dialog.text = ""+Greeting(true)+", "+GetTitle(NPChar,true)+". Posso ajudar em alguma coisa?";
				link.l1 = "Não, "+npchar.name+". Continue.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_repeat";
				Notification_ReputationNation(false, 51, HOLLAND);
			}
		break;
		
		case "ClockTower_Johan_21":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"!";
			link.l1 = "Aconteceu alguma coisa?";
			link.l1.go = "ClockTower_Johan_22";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_22":
			dialog.text = "Parabéns. Você tem um compromisso marcado.";
			link.l1 = "Um encontro? Com quem?";
			link.l1.go = "ClockTower_Johan_23";
		break;

		case "ClockTower_Johan_23":
			dialog.text = "Com o vice-diretor mynheer. Ele soube da sua ajuda à cidade e me mandou convidar você.";
			link.l1 = "E o próprio diretor?";
			link.l1.go = "ClockTower_Johan_24";
		break;

		case "ClockTower_Johan_24":
			dialog.text = "Ah... Não tenho autorização para te contar nada sobre isso. Boa sorte lá dentro, "+GetTitle(NPChar,true)+".";
			link.l1 = "Obrigado.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower");
		break;
		
		// Диалог с Маартеном Виссером, заместителем директора
		case "ClockTower_Visser_1":
			dialog.text = "Bem-vindo ao departamento de registro de navios da DWIC. Capitão...?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_2":
			dialog.text = ""+GetFullName(NPChar)+",\n"+"Maarten Visser, vice-diretor.\n"+"Ouvi dizer que você tem sido bastante útil para Willemstad. Talvez nosso escritório também possa lhe ser útil.";
			link.l1 = "É por isso que estou aqui.";
			link.l1.go = "ClockTower_Visser_3_1";
			link.l2 = "Fico feliz por poder servir à capital de Curaçao.";
			link.l2.go = "ClockTower_Visser_3_2";
		break;

		case "ClockTower_Visser_3_1":
			dialog.text = "Qualquer capitão — francês, espanhol, holandês — pode solicitar uma inspeção naval conosco. Examinamos o cordame, os canhões, o equipamento. Encontramos pontos fracos e damos recomendações";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
		break;

		case "ClockTower_Visser_3_2":
			dialog.text = "Qualquer capitão — francês, espanhol, holandês — pode solicitar uma inspeção de navio conosco. Inspecionamos o cordame, os canhões, o equipamento. Encontramos pontos fracos e damos recomendações";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "ClockTower_Visser_4":
			dialog.text = "E se uma auditoria não for suficiente, também podemos providenciar novos documentos para o seu navio. Em outras palavras, o trabalho do nosso escritório vai melhorar sua embarcação — sem gastar o precioso mogno e seda.";
			link.l1 = "Como isso é possível?";
			link.l1.go = "ClockTower_Visser_4_1";
		break;

		case "ClockTower_Visser_4_1":
			dialog.text = "Capitão, você não faz ideia do quão poderoso é o lugar em que entrou, e do quanto um simples traço de pena pode realizar.";
			link.l1 = "Por dobrões, imagino?";
			link.l1.go = "ClockTower_Visser_5";
		break;

		case "ClockTower_Visser_5":
			dialog.text = "Naturalmente. Nossos serviços não são baratos e dependem do tamanho do seu navio. Mas sempre valem o investimento. Um capitão que já passou por aqui dificilmente falha\n"+"No entanto, não ficamos só com o seu ouro — também lhe damos oportunidades de ganhá-lo. Os piratas se multiplicaram tanto que, até nas Pequenas Antilhas, capitães precisam montar esquadrões para expulsar esses parasitas. Traga provas de que eliminou algum deles — e receberá o pagamento nesses mesmos dobrões.";
			link.l1 = "Que tipo de prova?";
			link.l1.go = "ClockTower_Visser_6";
		break;

		case "ClockTower_Visser_6":
			dialog.text = "Diários de bordo. Até aquela ralé precisa manter algum tipo de registro — caso contrário, não dá pra comandar nem uma canoa direito. Além de servirem como prova incontestável de crimes, esses diários sempre acabam nos nossos arquivos. Úteis para resolver disputas de seguro\n"+"Se estiver interessado nos nossos serviços, abriu uma vaga na nossa lista de clientes — um dos nossos capitães encerrou recentemente a parceria. Conclua o trabalho — e a vaga será sua.";
			link.l1 = "Por que tanta complicação? Meus dobrões não bastam?";
			link.l1.go = "ClockTower_Visser_7";
		break;

		case "ClockTower_Visser_7":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+", nós trabalhamos com qualidade, não quantidade. Cada cliente do nosso escritório recebe o melhor atendimento e a atenção pessoal do próprio diretor mynheer. E isso, acredite, custa uma boa quantia até mesmo para a nossa empresa, que está longe de ser pobre. Como o mês só tem trinta dias, só podemos atender trinta clientes.";
			link.l1 = "O que precisa ser feito?";
			link.l1.go = "ClockTower_Visser_8";
		break;

		case "ClockTower_Visser_8":
			dialog.text = "Traga cinco diários de bordo de navios piratas — isso vai provar sua habilidade. A recompensa depende do quão perigosos eram seus donos.";
			link.l1 = "Muito bem. Eu vou fazer isso.";
			link.l1.go = "ClockTower_Visser_9_1";
			link.l2 = "Preciso pensar sobre isso.";
			link.l2.go = "ClockTower_Visser_9_2";
			link.l3 = "Onde está o próprio diretor?";
			link.l3.go = "ClockTower_Visser_9_3";
		break;

		case "ClockTower_Visser_9_1":
			dialog.text = "Excelente. Aguardo os resultados e espero ansioso pela nossa parceria.";
			link.l1 = Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_2":
			dialog.text = "Como quiser. A oferta continua de pé. Mas sua vaga pode ser ocupada mais rápido do que imagina.";
			link.l1 = Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;

		case "ClockTower_Visser_9_3":
			dialog.text = "No mar. Mynheer van Doorn concilia a administração do escritório com o comando da nau capitânia.";
			link.l1 = "Como ele consegue fazer isso?";
			link.l1.go = "ClockTower_Visser_10";
		break;

		case "ClockTower_Visser_10":
			dialog.text = "Ele trabalha dezoito horas por dia. Dorme aqui, no escritório lá em cima. Diz que dormir é perda de tempo. Quatro horas são suficientes pra ele.";
			link.l1 = "E aquele barulho todo desses mecanismos enormes de relógio? Como alguém consegue dormir aqui?";
			link.l1.go = "ClockTower_Visser_11";
		break;

		case "ClockTower_Visser_11":
			dialog.text = "Você mesmo poderá perguntar a ele e talvez aprender alguma coisa. Ele sempre gosta de conversar com os clientes. Estamos entendidos?";
			link.l1 = "Perfeitamente.";
			link.l1.go = "ClockTower_Visser_12";
			link.l2 = "Não exatamente...";
			link.l2.go = "ClockTower_Visser_12";
		break;

		case "ClockTower_Visser_12":
			dialog.text = "Bom dia para você, "+GetTitle(NPChar,false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "ClockTower_Visser_13_exit";
		break;
		
		case "ClockTower_Visser_13_exit":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Quest_2");
		break;
		
		// Йохан спрашивает про журналы
		case "ClockTower_Johan_31":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"! Você está com os registros?";
			link.l1 = "Vejo que você está bem informado, "+npchar.name+".";
			link.l1.go = "ClockTower_Johan_32";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Johan_32":
			if (!CheckAttribute(npchar, "questTemp.ClockTower_Johan_journal"))
			{
				dialog.text = "Ha! Aqui não é o cais nem os portões da cidade, e eu não sou só um guarda de plantão, mas sim um funcionário da companhia.";
				npchar.questTemp.ClockTower_Johan_journal = true;
			}
			else
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+"! Você está com os registros?";
			}
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "Trouxe os troncos. Vai me deixar passar?";
				link.l1.go = "ClockTower_Johan_33";
			}
			link.l2 = "Outra hora.";
			link.l2.go = "ClockTower_Johan_34";
		break;
		
		case "ClockTower_Johan_33":
			dialog.text = "Que bom que deu certo! Pode ir, estão te esperando.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_InvitationToTheTower_2");
		break;
		
		case "ClockTower_Johan_34":
			dialog.text = "Tenha um bom dia, senhor capitão, "+GetTitle(NPChar,true)+".";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Johan_32";
		break;
		
		case "ClockTower_Visser_21":
			dialog.text = "Capitão! Você voltou. Trouxe os registros?";
			if (ClockTower_JournalsQty() >= 5 || bBettaTestMode)
			{
				link.l1 = "Sim. Todos os cinco.";
				link.l1.go = "ClockTower_Visser_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "Outra hora.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Visser_21";
			}
			// link.l1.go = "ClockTower_Visser_36";	
			
		break;

		case "ClockTower_Visser_22":
			dialog.text = "Excelente. Deixe-me ver. \n"+"Sim, está tudo em ordem. Esses são navios piratas de verdade. Trabalho de qualidade. Você tem direito a "+SellJournals()+" dobrões\nPor favor, aceite-os. E assine aqui também, por favor.";
			link.l1 = "Então eu estou na lista?";
			link.l1.go = "ClockTower_Visser_23";
			//RemoveItemsFromKPTotal("ClockTower_PirateJournal", 5);	// 
		break;

		case "ClockTower_Visser_23":
			dialog.text = "Quase. Primeiro precisamos cuidar da papelada. Vai levar alguns minutos\n"+"Nome completo?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_24";
		break;

		case "ClockTower_Visser_24":
			dialog.text = "Nacionalidade?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_25";
		break;

		case "ClockTower_Visser_25":
			dialog.text = "Nome do seu navio?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_26";
		break;

		case "ClockTower_Visser_26":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "Tipo de embarcação?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_27";
		break;

		case "ClockTower_Visser_27":
			dialog.text = "Quantos canhões?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_28";
		break;

		case "ClockTower_Visser_28":
			dialog.text = "Tamanho da tripulação?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_29";
		break;

		case "ClockTower_Visser_29":
			dialog.text = "Ótimo. Agora assine aqui. E aqui. E aqui também.";
			link.l1 = "É só isso?";
			link.l1.go = "ClockTower_Visser_30";
		break;

		case "ClockTower_Visser_30":
			dialog.text = "Quase. Só falta registrar você no cadastro. Claro, o senhor diretor deveria conhecê-lo pessoalmente antes... Mas é só uma formalidade — estou autorizado a aceitar novos clientes\n"+"...Mas estou me desviando do assunto de novo. Agora, sobre os serviços que podem ser repetidos...\n"+"Seguro. Caro, mas nenhuma esquadra naval se atreve a mexer com navios segurados pela companhia. Você poderá manter quantos navios quiser armazenados no porto, sem medo de perdê-los durante um cerco à colônia\n"+"Auditoria do navio — aumenta levemente todas as características sem gastar recursos estratégicos. Vamos inspecionar tudo: cordame, porão, alojamentos da tripulação. Fornecemos recomendações. O preço depende do tamanho do navio\n"+"Registro nos nossos arquivos. Aumenta a segurança da embarcação na região do Caribe, fazendo com que caçadores de recompensas, piratas e militares pensem duas vezes antes de atacar você\n"+"A auditoria e o registro só podem ser feitos uma vez para um navio específico. Então, se você já gastou o dinheiro, cuide bem da sua embarcação. Você não faz ideia de como meus superiores ficam irritados quando os capitães tratam seus navios com descuido e trocam de embarcação como quem troca de luvas!\n"+"Mas estou me desviando do assunto de novo. Agora, sobre os serviços que podem ser repetidos...\n"+"Substituição de documentos. Você sabe que os navios podem ter especializações diferentes. Mas talvez não imagine que isso depende, antes de tudo, de como o navio está registrado. Se não gosta que seu navio de guerra esteja documentado para cercos a fortalezas, já sabe a quem recorrer\n"+"Bem, você já ouviu falar das recompensas por entregar os diários de bordo dos piratas... Quanto mais perigoso o pirata, mais vamos pagar pelo diário dele.";
			link.l1 = "Impressionante. Preciso dizer, senhor Visser, seu gabinete realmente...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor");
		break;

		case "ClockTower_Visser_31":
			dialog.text = "O Amsterdam está no porto! O senhor diretor voltou!";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_31_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
			ClockTower_AmsterdamInTheHarbor_2();
		break;

		case "ClockTower_Visser_31_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_32", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_32":
			dialog.text = "O quê?! Já?! Mas ele não deveria voltar por mais três dias!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_32_add";
		break;

		case "ClockTower_Visser_32_add":
			StartInstantDialog("ClockTower_Johan_clone", "ClockTower_Visser_33", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_33":
			dialog.text = "O senhor diretor já desembarcou! Ele está vindo direto pra cá!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_33_add";
			CharacterTurnByChr(CharacterFromID("ClockTower_Johan_Clone"), CharacterFromID("ClockTower_Visser"));
		break;

		case "ClockTower_Visser_33_add":
			StartInstantDialogNoType("ClockTower_Visser", "ClockTower_Visser_34", "Quest\ShipsPack\ClockTower_dialog.c");
		break;

		case "ClockTower_Visser_34":
			dialog.text = "Meu Deus... Se ele te vir...";
			link.l1 = "Qual é o problema? Você mesmo disse que tem autoridade para aceitar novos clientes.";
			link.l1.go = "ClockTower_Visser_35";
		break;

		case "ClockTower_Visser_35":
			dialog.text = "Eu quero sim! Mas ele não gosta quando... Deixa pra lá. Capitão, espere lá fora. Perto da entrada. O senhor diretor vai querer falar com você.";
			link.l1 = "Comigo?";
			link.l1.go = "ClockTower_Visser_36";
		break;

		case "ClockTower_Visser_36":
			dialog.text = "Ele avalia pessoalmente cada novo cliente. Sempre. Vá, depressa!";
			link.l1 = "Não vou devolver os dobrões pelos troncos!";
			link.l1.go = "ClockTower_Visser_36_1";
			link.l2 = "Que pena, eu teria ficado para ouvir.";
			link.l2.go = "ClockTower_Visser_36_2";
		break;

		case "ClockTower_Visser_36_1":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;

		case "ClockTower_Visser_36_2":
			DialogExit();
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddDialogExitQuestFunction("ClockTower_AmsterdamInTheHarbor_Kino_1");
		break;
		
		// диалог с Йоханом, после того как мы вышли из башни
		case "ClockTower_Johan_41":
			dialog.text = "...";
			link.l1 = "O que foi isso, Johan?";
			link.l1.go = "ClockTower_Johan_42";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Johan_42":
			dialog.text = "O senhor diretor voltou.";
			link.l1 = "O que há de tão terrível nisso?";
			link.l1.go = "ClockTower_Johan_43";
		break;

		case "ClockTower_Johan_43":
			dialog.text = "Nada de terrível! É só que... O senhor diretor não gosta de surpresas. Tudo precisa sair conforme o planejado. E agora aparece um cliente novo que ele ainda não avaliou.";
			link.l1 = "O Maarten disse que tinha autoridade para me registrar.";
			link.l1.go = "ClockTower_Johan_44";
		break;

		case "ClockTower_Johan_44":
			dialog.text = "Não, não é isso. O senhor diretor simplesmente... bem, ele quer controlar tudo sozinho. Cada pequeno detalhe. Diz que, do contrário, tudo vai desmoronar. Você vai ver, agora ele vai começar a se preocupar com o relógio dele de novo.";
			link.l1 = "O quê?";
			link.l1.go = "ClockTower_Johan_45";
		break;

		case "ClockTower_Johan_45":
			dialog.text = "Mynheer van Doorn, quando fica irritado, para o relógio e começa a mexer nele. Às vezes, a cidade fica sem saber as horas por meio dia. E isso acontece...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_45_1";
		break;

		case "ClockTower_Johan_45_1":
			dialog.text = "Oh... Ouviu isso? Já começou.";
			link.l1 = "O chefe voltou. Tudo como sempre.";
			link.l1.go = "ClockTower_Johan_46_1";
			link.l2 = "Eu estou ouvindo, sim. Eles estão acabando com o Maarten.";
			link.l2.go = "ClockTower_Johan_46_2";
			iClockSP4PseudoGlobal = ClockTower_PlaySound_rh2("Location/SP4_quest2");
		break;

		case "ClockTower_Johan_46_1":
			dialog.text = "Infelizmente, isso virou rotina.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_46_2":
			dialog.text = "Isso é duro da sua parte. Não é justo, se quer saber.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_47";	
			ChangeCharacterComplexReputation(pchar, "nobility", -2);

			if (iClockSP4PseudoGlobal != SOUND_INVALID_ID)
				SendMessage(Sound, "lll", MSG_SOUND_EVENT_STOP, iClockSP4PseudoGlobal, 0);
			ClockTower_PlaySound_rh2("Location/SP4_quest3");
		break;

		case "ClockTower_Johan_47":
			dialog.text = "Parece que as coisas se acalmaram. Logo vão te chamar para entrar.";
			link.l1 = "Estou encrencado?";
			link.l1.go = "ClockTower_Johan_48";
		break;

		case "ClockTower_Johan_48":
			dialog.text = "Não se preocupe. Você não fez nada de errado.";
			link.l1 = "Isso é reconfortante.";
			link.l1.go = "ClockTower_Johan_49";
		break;

		case "ClockTower_Johan_49":
			dialog.text = "Vamos lá! O senhor diretor às vezes pode ser rigoroso demais... Mas ele é generoso e educado... Ah, viu?";
			link.l1 = "...";
			link.l1.go = "ClockTower_Johan_50";
		break;

		case "ClockTower_Johan_50":
			dialog.text = "Ah, eu te disse!";
			link.l1 = "...";
			link.l1.go = "exit";
			ClockTower_VisserComingTowardsUs();
		break;

		case "ClockTower_Visser_37":
			dialog.text = "O senhor diretor está esperando por você lá dentro.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VisserComingTowardsUs_2");
			DelLandQuestMark(npchar);
		break;
		
		// Первое знакомство с ван Дорном
		case "ClockTower_VanDoorn_1":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+GetFullName(pchar)+", "+NationName+". Seu navio — '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" armas e "+GetMaxCrewQuantity(pchar)+" tripulação.";
			link.l1 = "Tudo certo.";
			link.l1.go = "ClockTower_VanDoorn_2";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_VanDoorn_2":
			shipType = XI_ConvertString(GetShipTypeName(npchar));
			dialog.text = "Não é justo que eu saiba tudo sobre você, enquanto você não sabe nada sobre mim além das fofocas do Johan. Hendrik van Doorn. Diretor do departamento de registros da Companhia Holandesa das Índias Ocidentais no Caribe. Comandante da fragata Amsterdam. "+shipType+". "+GetCannonQuantity(npchar)+" armas e "+GetMaxCrewQuantity(npchar)+" tripulação.";
			link.l1 = "Prazer em conhecê-lo.";
			link.l1.go = "ClockTower_VanDoorn_3";
		break;

		case "ClockTower_VanDoorn_3":
			dialog.text = "Você conseguiu cinco diários de bordo de navios piratas. Meu assistente passou a te respeitar, registrou seu nome no cadastro de clientes e te apresentou aos serviços do meu escritório\n"+"Mas a decisão final sobre a admissão é sempre minha. Pessoalmente. Depois de uma entrevista. Maarten pode indicar um candidato — nada além disso.";
			link.l1 = "Vamos começar.";
			link.l1.go = "ClockTower_VanDoorn_4";
		break;

		case "ClockTower_VanDoorn_4":
			if (!CheckAttribute(npchar, "ClockTower_option"))
			{
				dialog.text = "Preciso de capitães que combatam piratas de forma eficiente e que também tenham sucesso comercial suficiente para pagar pelos nossos serviços. Você se encaixa nesses critérios?";
			}
			else dialog.text = "";
			if (!CheckAttribute(npchar, "ClockTower_option_1") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_Memento"))
			{
				link.l1 = "Eu destruí Mortimer Grimm. Capitão do brigue Memento.";
				link.l1.go = "ClockTower_VanDoorn_option_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_2") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_LadyBeth"))
			{
				link.l2 = "Acho que sua companhia valorizou muito minha vitória sobre Albert Blackwood. O Lady Beth de neve foi uma adversária formidável.";
				link.l2.go = "ClockTower_VanDoorn_option_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_3") && CheckAttribute(pchar, "questTemp.DiegoDeLanda_SantaMisericordia"))
			{
				link.l3 = "Fernando de Alamida não era um pirata, mas...";
				link.l3.go = "ClockTower_VanDoorn_option_3";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_4") && CheckAttribute(pchar, "questTemp.KhaelRoa"))
			{
				link.l4 = "Derrotei o terror de todos que navegam. Você precisa saber.";
				link.l4.go = "ClockTower_VanDoorn_option_4";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_5") && GetCharacterShipClass(PChar) <= 3)
			{
				link.l5 = "Você acabou de registrar meu navio. Acha mesmo que um capitão incompetente conseguiria mantê-lo?";
				link.l5.go = "ClockTower_VanDoorn_option_5";
			}
			if (!CheckAttribute(npchar, "ClockTower_option_6") && sti(pchar.Money) >= 1000000)
			{
				link.l6 = "Estou me virando muito bem, e dinheiro nasce em árvore no Caribe.";
				link.l6.go = "ClockTower_VanDoorn_option_6";
			}
			link.l7 = "O Mynheer Visser já confirmou minha competência. A avaliação do seu próprio assistente não é suficiente?";
			link.l7.go = "ClockTower_VanDoorn_5";
			npchar.ClockTower_option = true;
		break;

		case "ClockTower_VanDoorn_option_1":
			dialog.text = "Grimm? Nossa organização nunca teve reclamações sobre o Grimm, muito pelo contrário. Mas aquele que tomou o lugar dele... Eu sei quem ele era e o que o trouxe originalmente para o Caribe. Uma vilania dessas não prescreve, e fico feliz que você tenha punido o criminoso e verdadeiro inimigo do meu país.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_1 = true;
		break;

		case "ClockTower_VanDoorn_option_2":
			dialog.text = "Se bem me lembro do relatório sobre o incidente em Cayman, você não teve oportunidade de confirmar essa afirmação. Na minha opinião, a situação não é totalmente clara, mas sua vitória foi, sem dúvida, competente.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_2 = true;
		break;

		case "ClockTower_VanDoorn_option_3":
			dialog.text = "Mas poderia ter se tornado algo muito pior, com certeza. Um inimigo digno, embora ele não tenha perdido para você, e sim para seus superiores ingratos. Sou holandês, então sei do que falo quando o assunto é guerra contra Castela.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_3 = true;
		break;

		case "ClockTower_VanDoorn_option_4":
			dialog.text = "'"+GetShipName("Coração Voador")+"'. Ainda me surpreende que gente decente não fuja ao ver aquela monstruosidade entrando no porto. Muita coisa nessa história me espanta, capitão. Mas um dia ela vai encontrar seu lugar em nossos livros e perder todo esse mistério. Quanto a você... já se tornou imortal.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_4 = true;
		break;

		case "ClockTower_VanDoorn_option_5":
			dialog.text = "Você ficaria surpreso. Mas no seu caso, não há espaço para dúvidas, isso é verdade.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_5 = true;
		break;

		case "ClockTower_VanDoorn_option_6":
			dialog.text = "E portanto não valem nada. A menos que sejam dobrões, é claro.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_4";
			npchar.ClockTower_option_6 = true;
		break;

		case "ClockTower_VanDoorn_5":
			dialog.text = "\nVocê está autorizado a usar os serviços do escritório. Bem-vindo ao respeitado Registro Naval da Companhia Holandesa das Índias Ocidentais.";
			link.l1 = "Obrigado.";
			link.l1.go = "ClockTower_VanDoorn_6";
		break;

		case "ClockTower_VanDoorn_6":
			dialog.text = "Esta é uma cooperação mutuamente benéfica. Você terá acesso aos melhores serviços do Caribe. Nós ganhamos um parceiro confiável.";
			link.l1 = "Bom.";
			link.l1.go = "ClockTower_VanDoorn_7";
		break;

		case "ClockTower_VanDoorn_7":
			dialog.text = "Espere! Você está ouvindo isso?";
			link.l1 = "Não ouço nada.";
			link.l1.go = "ClockTower_VanDoorn_8";
			// sound stops
			i = FindSoundEventId("Location/clocks_mechanism_inside");
			SetSoundEventPauseState(i, true);
			DelEventHandler("NextHour", "Villemstad_BigClock_Above");
		break;

		case "ClockTower_VanDoorn_8":
			dialog.text = "Exatamente isso! Bastou eu sair por uma semana...";
			link.l1 = "Aconteceu alguma coisa?";
			link.l1.go = "ClockTower_VanDoorn_9";
		break;

		case "ClockTower_VanDoorn_9":
			dialog.text = "Com o relógio. Preciso verificar o mecanismo. Me desculpe. Isso... é importante.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
		break;

		case "ClockTower_VanDoorn_10":
			if (!CheckAttribute(npchar, "ClockTower_question"))
			{
				dialog.text = "Parece tudo certo agora. Me desculpe novamente. Você tem alguma pergunta?";
				LAi_Fade("", "");
				// sound returns
				i = FindSoundEventId("Location/clocks_mechanism_inside");
				SetSoundEventPauseState(i, false);
				SetEventHandler("NextHour", "Villemstad_BigClock_Above", 0);
			}
			else dialog.text = "Mais perguntas?";
			if (!CheckAttribute(npchar, "ClockTower_question_1"))
			{
				link.l1 = "Seu assistente explicou os serviços do escritório em detalhes. Como tudo isso é possível?";
				link.l1.go = "ClockTower_VanDoorn_question_1";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_2"))
			{
				link.l2 = "Como você consegue juntar dois cargos? Capitão e diretor?";
				link.l2.go = "ClockTower_VanDoorn_question_2";
			}
			if (!CheckAttribute(npchar, "ClockTower_question_3"))
			{
				link.l3 = "Como você consegue trabalhar nessas condições? O barulho das engrenagens do relógio, a escuridão e as janelas cobertas por cortinas pesadas.";
				link.l3.go = "ClockTower_VanDoorn_question_3";
			}
			link.l4 = "Não, eu que agradeço pelo seu tempo. E quanto aos serviços do escritório?";
			link.l4.go = "ClockTower_VanDoorn_11";
			npchar.ClockTower_question = true;
		break;

		case "ClockTower_VanDoorn_question_1":
			dialog.text = "Aqui não há feitiçaria, capitão. Pena e tinta governam o mundo. A Igreja registra o nascimento, batismo, casamento e morte de uma pessoa. Mude uma única linha — e o destino dela muda. Um navio é um pouco mais complicado, mas até nesse caso, um traço da pena muda muita coisa. Não vou negar, tenho orgulho do que conquistei. E ainda assim sei que poderia ser melhor. E se, nos registros, anotássemos não só navios e pessoas, mas um mundo inteiro?";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_1 = true;
		break;

		case "ClockTower_VanDoorn_question_2":
			dialog.text = "Porque alguém precisava. O antigo capitão do Amsterdam morreu em batalha contra um grupo de Antígua. A companhia não encontrou nenhum substituto à altura. Eu me ofereci. Passei por treinamento. Fui aprovado nos exames. Consegui uma comissão\n"+"Sim, sou um capitão medíocre. Bem pior do que você — disso não tenho dúvidas. Mas um bom gestor pode liderar qualquer coisa, não só um navio. É difícil aprender a comandar três pessoas. Depois que você domina isso, pode comandar três mil. Escritório, navio, cidade, até uma grande companhia — não há limites, desde que você encontre pessoas talentosas e confie nelas para te substituir... Essa última parte é a mais difícil. Maldição de verdade.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_2 = true;
		break;

		case "ClockTower_VanDoorn_question_3":
			dialog.text = "E quase não há ar para respirar. Capitão, cada pessoa cria o próprio ambiente. Aqui nada e ninguém me distrai, tudo está ao meu alcance e só depende de mim e do tempo. Se eu pudesse, me comunicaria com o mundo lá fora só por papel. Infelizmente, isso é impossível. Não leve para o lado pessoal, capitão. É melhor estar só, mas não solitário. Se é que me entende.";
			link.l1 = "...";
			link.l1.go = "ClockTower_VanDoorn_10";
			npchar.ClockTower_question_3 = true;
		break;

		case "ClockTower_VanDoorn_11":
			// pchar.quest.ClockTower.date = rand(27)+1;
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Só atendemos clientes com hora marcada. Sua consulta está agendada para... "+pchar.quest.ClockTower.date+" "+month+". Se você não vier no dia marcado, não tem problema. Procure o Johan, e ele vai te informar sobre o próximo horário disponível.";
			link.l1 = "Por que tanta complicação?";
			link.l1.go = "ClockTower_VanDoorn_12";
		break;

		case "ClockTower_VanDoorn_12":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Nosso trabalho é caro porque realizamos verdadeiros milagres e trazemos grandes benefícios aos nossos clientes. Conflitos de interesse são impossíveis, por isso dedicamos um dia inteiro de trabalho para atender uma pessoa em específico. Sua próxima data disponível: "+pchar.quest.ClockTower.date+" "+month+"\n"+"Se você encontrar o Visser... Maarten agiu certo ao indicar você como candidato. Por favor, transmita essa mensagem. Ele é um bom vice. Que ele não duvide disso.";
			link.l1 = "Bom.";
			link.l1.go = "ClockTower_VanDoorn_13";
		break;

		case "ClockTower_VanDoorn_13":
			dialog.text = "Bom dia, "+GetTitle(NPChar,false)+".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VanDoornInCabinet_3");
		break;
		
		case "ClockTower_Visser_41":
			dialog.text = "Como foi?";
			link.l1 = "Foi um dia longo, mas van Doorn confirmou sua decisão.";
			link.l1.go = "ClockTower_Visser_42";
		break;

		case "ClockTower_Visser_42":
			dialog.text = "Graças a Deus. Então eu fiz tudo certo.";
			link.l1 = "Ele me pediu pra te dizer que você é um bom ajudante.";
			link.l1.go = "ClockTower_Visser_43";
		break;

		case "ClockTower_Visser_43":
			dialog.text = "Sério? Ele... disse isso?";
			link.l1 = "Sim. Ele disse isso.";
			link.l1.go = "ClockTower_Visser_44";
		break;

		case "ClockTower_Visser_44":
			dialog.text = "Droga. Ele não devia ter dito isso. Agora vou me sentir um desgraçado ingrato. Ou talvez ele já esperasse por isso e planejou tudo?";
			link.l1 = "Mynheer deputado, de repente você deixou de ser você mesmo.";
			link.l1.go = "ClockTower_Visser_45";
		break;

		case "ClockTower_Visser_45":
			dialog.text = "Capitão, eu sou um homem de negócios, assim como você, então vamos direto ao ponto.\n"+"O senhor diretor já não trabalha para nós há muito tempo.";
			link.l1 = "O quê, como é?!";
			link.l1.go = "ClockTower_Visser_46";
		break;

		case "ClockTower_Visser_46":
			dialog.text = "Ele veio para cá contratado com um único objetivo — criar o departamento de registro de navios. Conseguiu com maestria, treinou seu sucessor, me promoveu... e foi só isso.";
			link.l1 = "O quê, só isso?";
			link.l1.go = "ClockTower_Visser_47";
		break;

		case "ClockTower_Visser_47":
			dialog.text = "O contrato dele terminou há muito tempo. Não sabemos exatamente quando, mas temos plena certeza de que esse homem já não tem mais direito de ocupar esse cargo.";
			link.l1 = "Entendi. Os engravatados no setor central deste prédio ficam todos nervosos.";
			link.l1.go = "ClockTower_Visser_48_1";
			link.l2 = "Entendi. Você está cansado de esperar que ele desocupe a cadeira para você.";
			link.l2.go = "ClockTower_Visser_48_2";
		break;

		case "ClockTower_Visser_48_1":
			dialog.text = "Exatamente! E eles não podem fazer nada a respeito!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_48_2":
			dialog.text = "Vou ser franco. Estou realmente exausto. Droga, o van Doorn me promoveu justamente pra eu substituir ele quando o contrato acabasse!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_49";
		break;

		case "ClockTower_Visser_49":
			dialog.text = "Ainda assim, eu jamais balançaria essa maldita cadeira debaixo dele só porque me sinto enganado! Deus sabe, sou grato e admiro esse homem!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_50";
		break;

		case "ClockTower_Visser_50":
			dialog.text = "Não, senhor. Van Doorn quer expulsar nossos superiores em comum. Aqueles mesmos que estão sentados atrás do muro da torre — na ala central deste próprio prédio! Mas nem eles conseguem encontrar um jeito de controlá-lo!";
			link.l1 = "O que há de tão difícil nisso? Van Doorn não é mais importante do que Stuyvesant.";
			link.l1.go = "ClockTower_Visser_51";
		break;

		case "ClockTower_Visser_51":
			dialog.text = "Isso aqui não é um navio nem uma corte real, capitão. Nossa companhia é um tipo totalmente novo de organização. Você não pode simplesmente apontar o dedo e dispensar uma pessoa tão valiosa.\n"+"Primeiro, ninguém sabe onde está o original do contrato do van Doorn. Portanto, não há motivo para demiti-lo. Se tentássemos, ele mandaria um batalhão de advogados e acabaríamos devendo para ele.\n"+"Segundo, a administração cometeu um erro ao dar a comissão do Amsterdam para van Doorn. Ele pode ser um capitão fraco, mas reuniu uma tripulação — a melhor de toda a região. Dê a ordem — e os soldados de elite da Companhia vão ocupar este prédio sem hesitar.\n"+"Terceiro, a esposa dele o adora de verdade. Não importa que ele não a veja há vários anos. A própria filha de De Witt é capaz de tudo pelo marido amado. E o Conselho dos Dezessete é obrigado a aceitar isso.\n"+"Você viu o surto de hoje, capitão. Vou te contar um segredo: isso acontece cada vez com mais frequência. Os diretores têm medo de que um dia ele os expulse. E não vão poder fazer nada, porque o Amsterdam está no porto, o van Doorn tem um cliente valioso no escritório, e em casa — o apoio do sogro, o Grão-Pensionário da República das Sete Províncias Unidas!\n"+"Em outras palavras, a diretoria vai pagar muito bem pela sua ajuda. E vai manter seus privilégios no cartório naval.";
			link.l1 = "Impressionante. Você é mesmo um homem de negócios, Maarten. Está me vendendo traição com a mesma profissionalidade com que vendeu os serviços do seu escritório há pouco.";
			link.l1.go = "ClockTower_Visser_57";
		break;

		case "ClockTower_Visser_57":
			dialog.text = "Não é difícil quando o próprio van Doorn te ensinou a arte da negociação e você realmente acredita no que está dizendo.";
			link.l1 = "O que você quer de mim?";
			link.l1.go = "ClockTower_Visser_58";
		break;

		case "ClockTower_Visser_58":
			dialog.text = "Algo que só alguém de fora pode fazer. Invada o escritório à noite e encontre o contrato original do van Doorn lá. Eu vou garantir que as portas estejam destrancadas.";
			link.l1 = "Por que você mesmo não faz isso? E o que me impede de ir agora mesmo contar tudo ao seu superior?";
			link.l1.go = "ClockTower_Visser_59";
		break;

		case "ClockTower_Visser_59":
			dialog.text = "Porque van Doorn tem o hábito de receber qualquer um à noite, menos funcionários da companhia. Ninguém vai se surpreender ao ver você saindo desta torre em um horário estranho.";
			link.l1 = "";
			link.l1.go = "ClockTower_Visser_60";
		break;

		case "ClockTower_Visser_60":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			dialog.text = "Quanto à sua ameaça... Você não vai conseguir falar com o diretor agora, você tem outro compromisso marcado para hoje. "+pchar.quest.ClockTower.date+" "+month+", certo? Até lá, a urgência da notícia já terá diminuído um pouco. E além disso, o diretor nunca recompensa informantes. E sempre protege seus funcionários.";
			link.l1 = "Conveniente para você.";
			link.l1.go = "ClockTower_Visser_61";
		break;

		case "ClockTower_Visser_61":
			dialog.text = "Isso não é traição, capitão. Só queremos cumprir o contrato e proteger a companhia. E Willemstad, que você tanto ajudou, aliás.";
			link.l1 = "Vou pensar nisso. Mas não prometo nada.";
			link.l1.go = "ClockTower_Visser_62";
		break;

		case "ClockTower_Visser_62":
			dialog.text = "Não peço mais nada de você, capitão. Antes de tudo, você é nosso cliente. Seja como for, tenho muito orgulho de ter sido eu quem te encontrou e te registrou nos arquivos do escritório.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_63";
		break;

		case "ClockTower_Visser_63":
			dialog.text = "Você sempre pode me encontrar no ala central. Tenha um bom dia.";
			link.l1 = "Até nos encontrarmos de novo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Quest_3");
		break;
		
		case "ClockTower_Visser_64":
			dialog.text = "Olá, "+GetTitle(NPChar,false)+". Alguma novidade?";
			link.l1 = "Nada ainda.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_64";
		break;
		
		case "ClockTower_Johan_51":
			if (GetHour() >= 6 && GetHour() < 24)
			{
				if (pchar.quest.ClockTower.date <= GetDataDay())
				{
					NextMonth = GetDataMonth() + 1;
					if (NextMonth == 13) NextMonth = 1;
				}
				else NextMonth = GetDataMonth();
				Month = XI_ConvertString("MonthGen_" + NextMonth);
				if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+", hoje é o seu dia. Por favor, vá em frente.";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
						
						ClockTower_RightDay();
					}
					else
					{
						dialog.text = "Bom dia, "+GetTitle(NPChar,false)+"!";
					}
				}
				else
				{
					if (!CheckAttribute(npchar, "ClockTower_repeat"))
					{
						dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+", você é esperado em outro dia. Ficaremos felizes em vê-lo: "+pchar.quest.ClockTower.date+" "+month+".";
						npchar.ClockTower_repeat = true;
						SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					}
					else
					{
						dialog.text = "Bom dia, "+GetTitle(NPChar,false)+"!";
					}
				}
				link.l1 = "Obrigado, Johan.";
				link.l1.go = "exit";
				NextDiag.TempNode = "ClockTower_Johan_51";
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeatnight"))
				{	// первая ночная встреча с Йоханом
					dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+", você chegou um pouco tarde. O escritório está fechado.";
					link.l1 = "Olá, "+npchar.name+". Ouvi dizer que funciona até mesmo à noite.";
					link.l1.go = "ClockTower_Johan_52";
					npchar.ClockTower_repeatnight = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = ""+TimeGreeting()+", "+GetTitle(NPChar,false)+"!";
					link.l1 = "";
					link.l1.go = "ClockTower_Johan_53";
				}
			}
		break;
		
		case "ClockTower_Johan_52":
			dialog.text = "É verdade. Todo tipo de gente passa por aqui. Até padres aparecem de vez em quando, heh-heh. Mas todos têm que passar por mim primeiro. E eu não recebi nenhuma instrução sobre você.";
			link.l1 = "Espera, você faz guarda aqui o tempo todo? Como isso é possível?";
			link.l1.go = "ClockTower_Johan_53";
		break;

		case "ClockTower_Johan_53":
			if (!CheckAttribute(npchar, "ClockTower_repeatnight_2"))
			{
				dialog.text = "Sim. O senhor diretor acabou de ordenar isso. Como ele consegue, não faço ideia, mas ainda tenho tempo suficiente tanto para descansar quanto para cumprir meu dever. E ainda aumentaram meu salário — não posso reclamar!";
				npchar.ClockTower_repeatnight_2 = true;
			}
			else
			{
				dialog.text = "Mais alguma coisa?";
			}
			if (!CheckAttribute(pchar, "questTemp.ClockTower_NightFree"))
			{
				link.l1 = "Você deveria me deixar passar. Eu trabalho para a diretoria da companhia.";
				link.l1.go = "ClockTower_Johan_54";
				link.l2 = "(Mate ele)";
				link.l2.go = "ClockTower_Johan_KillHim";
			}
			link.l3 = "Continue, soldado.";
			link.l3.go = "ClockTower_Johan_NightExit";
		break;
		
		case "ClockTower_Johan_KillHim":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_KillToJohan");
		break;
		
		case "ClockTower_Johan_NightExit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_Johan_51";
		break;
		
		case "ClockTower_Johan_54":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 80)
			{
				dialog.text = "Ah. O que você quer de mim, senhor capitão? Sou só um soldado simples, não sei de nada.";
				link.l1 = "Você sabe de tudo, Johan. Não seja tão modesto. Os senhores dos altos cargos podem não prestar contas a você, mas com certeza já ouviu falar da rivalidade entre eles.";
				link.l1.go = "ClockTower_Johan_55";
				Notification_Skill(true, 80, SKILL_LEADERSHIP);
			}
			else
			{
				dialog.text = "Sou um homem simples, mas não vou passar por cima do meu superior direto. Me desculpe, "+GetTitle(NPChar,true)+".";
				link.l1 = "Vamos voltar a essa conversa.";
				link.l1.go = "ClockTower_Johan_NightExit";
				Notification_Skill(false, 80, SKILL_LEADERSHIP);
			}
		break;
		
		case "ClockTower_Johan_55":
			Achievment_Set("ach_CL_197");
			dialog.text = "É verdade, "+GetTitle(NPChar,true)+". O senhor diretor se demorou demais. Uma tempestade está se formando.";
			link.l1 = "O que exatamente você ouviu?";
			link.l1.go = "ClockTower_Johan_56";
		break;
		
		case "ClockTower_Johan_56":
			dialog.text = "Todo mundo teme que, se não for hoje, amanhã ele vai tomar o poder. Ele é grande demais pra esse nosso fim de mundo. Tá sufocando todo mundo com essas inspeções, faz questão de que toda assinatura passe por ele\nVou te falar a verdade, e você mesmo viu: toda vez que o Amsterdam entra no porto — o clima pesa na hora.";
			link.l1 = "Eu posso resolver isso, mas para isso você precisa me deixar passar.";
			link.l1.go = "ClockTower_Johan_57";
		break;

		case "ClockTower_Johan_57":
			dialog.text = "Vá em frente, "+GetTitle(NPChar,true)+". Só te peço, não me arruína: se o senhor diretor descobrir, vou perder a cabeça, e tenho uma família para sustentar.";
			link.l1 = "Vou fazer o meu melhor.";
			// if (sti(pchar.reputation.nobility) >= 71) link.l1.go = "ClockTower_Johan_58_hint";
			// else link.l1.go = "ClockTower_Johan_NightSuccess";
			link.l1.go = "ClockTower_Johan_58_hint";
		break;

		case "ClockTower_Johan_58_hint":
			ClockTower_AddBook();
			dialog.text = "Você é um bom homem, "+GetTitle(NPChar,true)+"Talvez eu possa te ajudar: sei que em um dos livros o senhor diretor guarda uma chave. Para que serve — não sei, mas talvez seja útil.";
			link.l1 = "Obrigado, Johan.";
			link.l1.go = "ClockTower_Johan_NightSuccess";
			// if (sti(pchar.reputation.nobility) >= 71) Notification_Reputation(true, 71, "low");
		break;
		
		case "ClockTower_Johan_NightSuccess":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_NightFree");
			NextDiag.CurrentNode = "ClockTower_Johan_51";
			// if (sti(pchar.reputation.nobility) < 71) Notification_Reputation(false, 71, "low");
		break;
		
		case "ClockTower_Peter_50":
			dialog.text = "Pare. Você está em propriedade da Companhia Holandesa das Índias Ocidentais. Departamento de registro naval e arquivo. Entrada somente com hora marcada.";
			link.l1 = "Eu sou "+GetTitle(NPChar,false)+" "+pchar.name+".";
			link.l1.go = "ClockTower_Peter_51";
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_51":
			if (pchar.quest.ClockTower.date <= GetDataDay())
			{
				NextMonth = GetDataMonth() + 1;
				if (NextMonth == 13) NextMonth = 1;
			}
			else NextMonth = GetDataMonth();
			Month = XI_ConvertString("MonthGen_" + NextMonth);
			if (pchar.quest.ClockTower.date == GetDataDay() && CheckAttribute(pchar, "questTemp.ClockTower_NoToday"))
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "Você tem hora marcada? Pode entrar.";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
					
					ClockTower_RightDay();
				}
				else
				{
					dialog.text = "...";
				}
			}
			else
			{
				if (!CheckAttribute(npchar, "ClockTower_repeat"))
				{
					dialog.text = "Sua consulta está marcada para outro dia: "+pchar.quest.ClockTower.date+" "+month+".";
					npchar.ClockTower_repeat = true;
					SetFunctionTimerCondition("ClockTower_GuardianNewDay", 0, 0, 1, false);
				}
				else
				{
					dialog.text = "...";
				}
			}
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Peter_51";
		break;
		
		case "ClockTower_Visser_71":
			dialog.text = "Olá, "+GetTitle(NPChar,false)+". Alguma novidade?";
			link.l1 = "Sim. Aqui está o contrato.";
			link.l1.go = "ClockTower_Visser_72";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_72":
			dialog.text = "Incrível... Isso venceu há sete anos!";
			link.l1 = "Então era isso que você precisava?";
			link.l1.go = "ClockTower_Visser_73";
		break;

		case "ClockTower_Visser_73":
			dialog.text = "Exatamente! Com este documento, a companhia pode chamá-lo de volta legalmente. Sem brechas. Sem desculpas. O tempo acabou — ponto final.";
			link.l1 = "O que vem agora?";
			link.l1.go = "ClockTower_Visser_74";
		break;

		case "ClockTower_Visser_74":
			dialog.text = "Vou enviar o contrato para Amsterdã. O Conselho dos Dezessete vai tomar uma decisão. Doorn será obrigado a voltar. Ele não vai poder recusar.";
			link.l1 = "E se ele recusar?";
			link.l1.go = "ClockTower_Visser_75";
		break;

		case "ClockTower_Visser_75":
			dialog.text = "Ele não pode. A esposa dele pode até ser filha de um acionista, o Grande Pensionário, mas nem o próprio pai dela enfrentaria o Conselho. E a própria Catharina... Ela já espera há dez anos. Se descobrir que ele pode voltar mas se recusa — isso vai acabar com ela.";
			link.l1 = "Cruel.";
			link.l1.go = "ClockTower_Visser_76";
		break;
		
		case "ClockTower_Visser_76":
			dialog.text = "Sim. Mas é o único jeito. Obrigado, capitão. Você fez um trabalho importante.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_77";
		break;
		
		case "ClockTower_Visser_77":
			if (CharacterIsAlive("ClockTower_Johan"))
			{
				dialog.text = "Sua recompensa — quinhentos dobrões. E te dou minha palavra: em dois ou três meses, quando eu assumir a direção, você terá acesso ilimitado aos serviços do escritório. Sem filas. Sem marcar hora. A qualquer momento.";
				AddItems(pchar, "gold_dublon", 500);
			}
			else
			{
				dialog.text = "E você matou o Johan. Já traí um homem que admiro e a quem devo tudo. Agora isso também\n"+"Talvez na sua embarcação as pessoas sejam tratadas como lenha, mas aqui a companhia valoriza seus funcionários. E me enoja ser cúmplice de assassinato\n"+"Seus dobrões vão para a família do Johan, mas eu vou cumprir a segunda parte do acordo\n"+"Dou minha palavra: em dois ou três meses, quando eu assumir a cadeira de diretor, você terá acesso ilimitado aos serviços do escritório.";
			}
			link.l1 = "Estou contando com a sua palavra. Tenha um bom dia.";
			link.l1.go = "ClockTower_Visser_78";
		break;
		
		case "ClockTower_Visser_78":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_WaitFewMonths");
		break;
		
		case "ClockTower_Visser_79":
			dialog.text = "Olá, "+GetTitle(NPChar,false)+". Ainda não há novidades. Não se preocupe, eu lembro do nosso acordo.";
			link.l1 = "Espero que sim.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ClockTower_Visser_79";
		break;
		
		case "ClockTower_Visser_81":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+"! Entre, entre. Que bom ver você.";
			link.l1 = "Parabéns pela sua nomeação.";
			link.l1.go = "ClockTower_Visser_82";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_82":
			dialog.text = "Obrigado. O Conselho dos Dezessete tomou a decisão mais rápido do que eu esperava. O contrato serviu como prova suficiente. Mynheer van Doorn foi afastado da administração do escritório.";
			link.l1 = "Como ele reagiu?";
			link.l1.go = "ClockTower_Visser_83";
		break;

		case "ClockTower_Visser_83":
			dialog.text = "Ele sabe perder. Só juntou suas coisas pessoais do escritório e foi embora. Mas será que ele realmente perdeu?\n"+"Deixaram ele no comando do Amsterdam. Nesse ponto, a companhia certamente cometeu um erro. Não deviam ter dado aquele navio pra ele naquela época.\n"+"Subestimamos ele. Espero que as coisas não acabem pior no final\n"+"E isso não é tudo.";
			link.l1 = "Como poderia ser pior?";
			link.l1.go = "ClockTower_Visser_84";
		break;

		case "ClockTower_Visser_84":
			dialog.text = "O senhor van Doorn sabe quem pegou o contrato em seu escritório.";
			link.l1 = "Como?!";
			link.l1.go = "ClockTower_Visser_85";
		break;

		case "ClockTower_Visser_85":
			dialog.text = "Não me olhe assim! Eu não contei nada pra ele. Ele descobriu sozinho.";
			link.l1 = "E agora?";
			link.l1.go = "ClockTower_Visser_86";
		break;

		case "ClockTower_Visser_86":
			dialog.text = "Agora ele te considera um inimigo. Mas enquanto você não representar ameaça para a República das Sete Províncias Unidas — ele não vai te incomodar\n"+"Van Doorn sempre soube separar o pessoal do profissional. A questão é: e você?";
			link.l1 = "E se eu não conseguir?";
			link.l1.go = "ClockTower_Visser_87";
		break;

		case "ClockTower_Visser_87":
			dialog.text = "Então ele vai te encontrar. E fazer o trabalho dele. Não dê motivo pra isso.";
			link.l1 = "Vou tentar.";
			link.l1.go = "ClockTower_Visser_88";
		break;

		case "ClockTower_Visser_88":
			dialog.text = "Bom dia para você, "+GetTitle(NPChar,false)+". Fique à vontade para usar os serviços do nosso... do meu escritório a qualquer momento.";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_VillemstadStreet");
		break;
		
		case "ClockTower_Johan_61":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,true))+", você está sendo esperado. O senhor Visser ordenou que todos os clientes fossem autorizados a entrar livremente. Disse que as regras antigas eram rígidas demais.";
			link.l1 = "Obrigado, Johan.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Peter_61":
			dialog.text = "Vá em frente durante o expediente. As consultas foram abolidas.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FreeAccess_2");
			DelLandQuestMark(npchar);
		break;
		
		case "ClockTower_Helena_1":
			dialog.text = "Tem um minuto?";
			link.l1 = "Para você — sempre.";
			link.l1.go = "ClockTower_Helena_2";
		break;

		case "ClockTower_Helena_2":
			dialog.text = "Ah, se ao menos fosse assim, meu capitão. Você tem outras paixões na vida. Agora mesmo, por exemplo, sua bela cabeça está ocupada por alguém que não sou eu, não é?";
			link.l1 = "...";
			link.l1.go = "ClockTower_Helena_3";
		break;

		case "ClockTower_Helena_3":
			dialog.text = "Era o que eu imaginava. Conheço bem o meu homem. E a empolgação de um marinheiro — essa então, conheço melhor ainda. Então me diga logo, querido\n"+"Quanto vai nos custar capturar o navio principal da estimada Companhia Holandesa das Índias Ocidentais?";
			link.l1 = "Para van Doorn vir atrás de nós pessoalmente, vou ter que me tornar inimigo de Willemstad.";
			link.l1.go = "ClockTower_Helena_4";
		break;

		case "ClockTower_Helena_4":
			dialog.text = "Oh, meu capitão... Então é assim que vai ser. Não é a primeira vez, não é?";
			link.l1 = "Como se você não aprovasse.";
			link.l1.go = "ClockTower_Helena_5";
		break;

		case "ClockTower_Helena_5":
			dialog.text = "Me apaixonei por você do jeito que você é. E sempre vou estar ao seu lado. Só não esqueça do peso da responsabilidade que nós... quer dizer, que você carrega diante do seu povo.";
			link.l1 = "Mas é pra isso que temos o nosso Alonso. Ele vai te lembrar.";
			link.l1.go = "ClockTower_Helena_6";
		break;

		case "ClockTower_Helena_6":
			dialog.text = "Assim que zarparmos, meu capitão.";
			link.l1 = "Então não vamos demorar, meu bem.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Mary_1":
			dialog.text = "Charles? Quero te perguntar uma coisa.";
			link.l1 = "Claro, Mary. O que aconteceu?";
			link.l1.go = "ClockTower_Mary_2";
		break;

		case "ClockTower_Mary_2":
			dialog.text = "Eu... Eu estou preocupado com você, tá bom. Eu conheço esse olhar. Você está pensando em alguma coisa ruim.";
			link.l1 = "Besteira. Eu nem lembro do que estava pensando agora há pouco. Como é que você saberia?";
			link.l1.go = "ClockTower_Mary_3";
		break;

		case "ClockTower_Mary_3":
			dialog.text = "Eu sei, eu vi aquele Amsterdam, tá bom. Navio lindo. Muito lindo. Mas\n"+"Você já decidiu tudo... Como antes, certo?";
			link.l1 = "Van Doorn vai vir atrás de nós pessoalmente, mas para isso vou ter que me tornar inimigo de Willemstad.";
			link.l1.go = "ClockTower_Mary_4";
		break;

		case "ClockTower_Mary_4":
			dialog.text = "Vale a pena, Charles?";
			link.l1 = "Eu não sei, Mary.";
			link.l1.go = "ClockTower_Mary_5";
		break;

		case "ClockTower_Mary_5":
			dialog.text = "Eu quero que você seja feliz, tá bom. Mas mesmo assim vou pedir pro Alonso tentar te convencer a desistir disso, tá bom!";
			link.l1 = "Parece mesmo com ele. Vamos, meu amor.";
			link.l1.go = "ClockTower_Girl_End";
		break;
		
		case "ClockTower_Girl_End":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_Girl_DlgExit");
		break;
		
		case "ClockTower_Alonso_1":
			dialog.text = "Capitão, precisamos conversar.";
			link.l1 = "Estou ouvindo.";
			link.l1.go = "ClockTower_Alonso_2";
			link.l2 = "Agora não, Alonso.";
			link.l2.go = "ClockTower_Alonso_2";
		break;

		case "ClockTower_Alonso_2":
			dialog.text = "É o seguinte, capitão, mas você vai ter que me ouvir. É, ahm, como é mesmo a palavra\n"+"Um assunto urgente — é isso!\n"+"Então, ouvi dizer que você pessoalmente tirou um dos diretores da companhia do seu cargo confortável, e agora ele está remoendo o rancor e caçando a gente no seu belo navio.";
			link.l1 = "Isso é um exagero absurdo.";
			link.l1.go = "ClockTower_Alonso_3";
		break;

		case "ClockTower_Alonso_3":
			dialog.text = "Você sabe como as pessoas adoram fofocar, capitão. Deixe um boato circular por uma semana — e você vai ouvir que van Doorn foi seduzido pela filha de um fazendeiro, que o Amsterdam tem uma tripulação de mortos-vivos e que há um tesouro do próprio Cortés no porão\n"+"Mas o que me interessa mesmo é saber como as coisas realmente estão. Então, capitão, vai ter briga ou não?";
			link.l1 = "...";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Томми
			{
				link.l1.go = "ClockTower_Alonso_4_1";
			}
			else
			{
				link.l1.go = "ClockTower_Alonso_4_5";
			}
		break;
		
		case "ClockTower_Alonso_4_1":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin");
		break;
		
		case "ClockTower_Alonso_4_2":
			dialog.text = "Aliás, isso seria uma baita diversão, não vou negar! Nau capitânia holandesa! Ha! Consigo imaginar a cara daqueles come-queijos quando a gente...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_3";
		break;
		
		case "ClockTower_Alonso_4_3":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_TommyInCabin_2");
		break;
		
		case "ClockTower_Alonso_4_4":
			dialog.text = "Tommy, cala a boca.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_4_5";
		break;
		
		case "ClockTower_Alonso_4_5":
			dialog.text = "...";
			link.l1 = "Se houver uma briga, não vai ser tão cedo. Van Doorn não vai buscar vingança, ele não é desse tipo de homem. Primeiro, vamos ter que irritar os holandeses de verdade.";
			link.l1.go = "ClockTower_Alonso_4_6";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "ClockTower_Alonso_4_6":
			dialog.text = "Valeu, capitão, isso vai tranquilizar a tripulação.";
			link.l1 = "E você?";
			link.l1.go = "ClockTower_Alonso_5";
		break;
		
		case "ClockTower_Alonso_5":
			dialog.text = "Minha preocupação é proteger a tripulação. Deles mesmos e... de você, se eu puder. De qualquer jeito, você vai fazer o que planejou.";
			if (CheckPassengerInCharacter(pchar, "Irons")) // Томми
			{
				link.l1 = "...";
				link.l1.go = "ClockTower_Alonso_5_add";
			}
			else
			{
				link.l1 = "Continue, Alonso.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
			}
		break;
		
		case "ClockTower_Alonso_5_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_6", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;
		
		case "ClockTower_Alonso_6":
			dialog.text = "Teimoso como uma mula espanhola!";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_6_add";
		break;
		
		case "ClockTower_Alonso_6_add":
			StartInstantDialogTurnToNPC("ClockTower_Alonso", "ClockTower_Alonso_7", "Quest\ShipsPack\ClockTower_dialog.c", "Irons");
		break;
		
		case "ClockTower_Alonso_7":
			dialog.text = "Senhor, por que eu.";
			link.l1 = "...";
			link.l1.go = "ClockTower_Alonso_7_add";
		break;
		
		case "ClockTower_Alonso_7_add":
			StartInstantDialogTurnToNPC("Irons", "ClockTower_Alonso_8", "Quest\ShipsPack\ClockTower_dialog.c", "ClockTower_Alonso");
		break;

		case "ClockTower_Alonso_8":
			dialog.text = "Você está complicando tudo demais! O capitão quer um navio bonito — vamos conseguir um navio bonito pra ele! Somos uma tripulação só!";
			link.l1 = "Continue, Alonso. Tommy, saia.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_CuracaoInCabin_4_DlgExit");
		break;
		
		// Абордаж Амстердама, перед боем с Ван Дормом
		case "ClockTower_VanDoorn_21":
			NationName = GetSexPhrase(""+NationNameMan(sti(pchar.baseNation))+"",""+NationNameWoman(sti(pchar.baseNation))+"");
			shipType = LowerFirst(XI_ConvertString(GetShipTypeName(pchar)));
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+GetFullName(pchar)+", "+NationName+". Seu navio — '"+PChar.Ship.Name+"', "+shipType+". "+GetCannonQuantity(pchar)+" armas e "+GetMaxCrewQuantity(pchar)+" tripulação.";
			link.l1 = "Você continua tão preciso quanto sempre, senhor diretor.";
			link.l1.go = "ClockTower_VanDoorn_22";
		break;

		case "ClockTower_VanDoorn_22":
			dialog.text = "Esse título já não me pertence — graças aos seus esforços. Mas nem pense que eu te ataquei por vingancinha. Eu só estava fazendo meu trabalho.\n"+"E obviamente fracassei nisso. Também não teria conseguido: já te disse uma vez que você é um capitão muito melhor do que eu.";
			link.l1 = "Você assumiu esse fardo por vontade própria! Seu contrato acabou faz sete anos. O que te impediu de simplesmente voltar pra casa?";
			link.l1.go = "ClockTower_VanDoorn_23";
		break;

		case "ClockTower_VanDoorn_23":
			dialog.text = "O que te impede de fazer o mesmo? Você sabe a resposta, capitão. Você tem um sonho. Não tem outra vida. E se perder o controle — tudo desmorona.\n"+"Eu poderia ter trazido ordem para esta região. Poderia ter acabado com o ciclo interminável de violência. Se eu não tivesse afrouxado meu controle. Se eu tivesse vencido meu medo e feito o que já devia ter feito há muito tempo.\n"+"Mas chega de sentimentalismo. Sou tão ruim de espada quanto de comando, mas sei escolher meus homens. Você se tornou minha última missão, capitão. Hoje o registro da capitania vai ter dois capitães a menos!";
			if (CheckCharacterItem(PChar, "CatharinaLetter"))
			{
				link.l1 = "Você estava falando algo sobre medo. Então leia esta carta."; // Доступно, если игрок принёс письмо
				link.l1.go = "ClockTower_VanDoorn_24";
			}
			link.l2 = "Só um. Para a batalha!"; // бой
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_24":
			dialog.text = "Da Catharina?! Como você ousa misturar o pessoal com os negócios?!";
			link.l1 = "Como pode ver, a carta ainda está lacrada. Estou esperando.";
			link.l1.go = "ClockTower_VanDoorn_25";
			TakeItemFromCharacter(pchar, "CatharinaLetter");
			pchar.questTemp.ClockTower_GaveCatharinaLetter = true;
		break;

		case "ClockTower_VanDoorn_25":
			dialog.text = "...ela não aguenta mais esperar... vai procurar outro... se eu não voltar?!";
			link.l1 = "Você já perdeu o comando. Sua tripulação está morrendo neste exato momento. Está pronto para perder sua família também?";
			link.l1.go = "ClockTower_VanDoorn_26";
		break;

		case "ClockTower_VanDoorn_26":
			dialog.text = "Não assim. Capitão, aceita minha rendição?";
			link.l1 = "Isso. Cai fora do meu navio."; // Отпускает, повышает честь
			link.l1.go = "ClockTower_VanDoorn_27";
			link.l2 = "Não. Essa foi a última cortesia aos condenados. À batalha!"; // бой
			link.l2.go = "ClockTower_cabinFight";
		break;

		case "ClockTower_VanDoorn_27":
			dialog.text = "Então, parabéns pela sua vitória, Capitão "+GetFullName(pchar)+". Hoje o registro terá apenas um capitão a menos.";
			link.l1 = "...";
			link.l1.go = "ClockTower_cabinPeace";
			GiveItem2Character(PChar, "pistol15");
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE); // нужно два раза, чтобы сработало...
			TakeItemFromCharacter(npchar, "pistol15");
		break;
		
		// Финальный диалог с Маартеном
		case "ClockTower_Visser_101":
			dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+GetFullName(pchar)+". Eu não esperava que você tivesse coragem de aparecer aqui.";
			link.l1 = "Por que não? Ainda sou seu cliente, e preciso dos serviços do escritório.";
			link.l1.go = "ClockTower_Visser_102";
			DelLandQuestMark(npchar);
		break;

		case "ClockTower_Visser_102":
			dialog.text = "Serviços? SERVIÇOS?! Depois do que você fez? Você é inimigo da respeitada Companhia Holandesa das Índias Ocidentais! Outro capitão vai ocupar o lugar do seu cliente!";
			link.l1 = "Improvável. Olhe o que encontrei nos papéis do van Doorn.";
			link.l1.go = "ClockTower_Visser_103";
		break;
		
		case "ClockTower_Visser_103":
			dialog.text = "...";
			link.l1 = "Seu antecessor achava indigno usar este documento — mesmo quando a cadeira dele começou a balançar.";
			link.l1.go = "ClockTower_Visser_104";
			// отдаём Ключ к Маартену Виссеру
			TakeItemFromCharacter(pchar, "Visser_Key");
		break;
		
		case "ClockTower_Visser_104":
			dialog.text = "...";
			link.l1 = "Você teve sorte de ter um superior assim. Por essas travessuras, no mínimo você iria a julgamento.";
			link.l1.go = "ClockTower_Visser_105";
		break;
		
		case "ClockTower_Visser_105":
			dialog.text = "...";
			link.l1 = "Você é um homem de negócios. Você sabe onde quero chegar com isso.";
			link.l1.go = "ClockTower_Visser_106";
		break;
		
		case "ClockTower_Visser_106":
			dialog.text = "Você... Seu nome foi restaurado no registro.";
			link.l1 = "Ah, Maarten. Você queria tomar o lugar do diretor, mesmo depois de tudo que ele fez por você. Ele te salvou do julgamento e nem achou necessário te avisar.";
			link.l1.go = "ClockTower_Visser_107";
		break;
		
		case "ClockTower_Visser_107":
			dialog.text = "...";
			link.l1 = "Esse pequeno pecado nunca vai deixar você subir mais alto e vai te deixar vivendo em medo constante.";
			link.l1.go = "ClockTower_Visser_108";
		break;
		
		case "ClockTower_Visser_108":
			dialog.text = "...";
			link.l1 = "Agora é a sua vez de ficar acorrentado a este lugar. Mas com certeza você não vai ter um ajudante como o van Doorn tinha.";
			link.l1.go = "ClockTower_Visser_109";
		break;
		
		case "ClockTower_Visser_109":
			dialog.text = "Chega. Você quer acabar comigo de vez?!";
			link.l1 = "Não exatamente. Quero que registre meu novo navio. Não quero nenhum mal-entendido.";
			link.l1.go = "ClockTower_Visser_110";
		break;
		
		case "ClockTower_Visser_110":
			dialog.text = "Seu navio é o '"+GetShipName("Amsterdam")+"'. Nau capitânia da DWIC. Não pode simplesmente ser... re-registrada.";
			link.l1 = "Por que não? O papel aguenta tudo. Não é assim que funciona o seu sistema?";
			link.l1.go = "ClockTower_Visser_111";
		break;
		
		case "ClockTower_Visser_111":
			dialog.text = "Meu Deus, mas tudo tem limite!";
			link.l1 = "Eu acredito no poder deste lugar. Você também deveria.";
			link.l1.go = "ClockTower_Visser_112";
		break;
		
		case "ClockTower_Visser_112":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "ClockTower_Visser_113";
		break;
		
		case "ClockTower_Visser_113":
			dialog.text = "Nome completo?";
			link.l1 = ""+GetFullName(pchar)+".";
			link.l1.go = "ClockTower_Visser_114";
		break;
		
		case "ClockTower_Visser_114":
			dialog.text = "Cidadania?";
			link.l1 = ""+NationNameNominative(sti(pchar.baseNation))+".";
			link.l1.go = "ClockTower_Visser_115";
		break;

		case "ClockTower_Visser_115":
			dialog.text = "Nome do seu navio?";
			link.l1 = ""+PChar.Ship.Name+".";
			link.l1.go = "ClockTower_Visser_116";
		break;

		case "ClockTower_Visser_116":
			shipType = XI_ConvertString(GetShipTypeName(pchar));
			dialog.text = "Tipo de embarcação?";
			link.l1 = ""+shipType+".";
			link.l1.go = "ClockTower_Visser_117";
		break;

		case "ClockTower_Visser_117":
			dialog.text = "Quantos canhões?";
			link.l1 = ""+GetCannonQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_118";
		break;

		case "ClockTower_Visser_118":
			dialog.text = "Tamanho da tripulação?";
			link.l1 = ""+GetMaxCrewQuantity(pchar)+".";
			link.l1.go = "ClockTower_Visser_119";
		break;

		case "ClockTower_Visser_119":
			dialog.text = "Ótimo. Agora assine aqui. E aqui. E aqui também.";
			link.l1 = "É só isso?";
			link.l1.go = "ClockTower_Visser_120";
		break;
		
		case "ClockTower_Visser_120":
			dialog.text = "É isso.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_Visser_pausa_1");
		break;
		
		case "ClockTower_Visser_121":
			dialog.text = "...";
			link.l1 = "Você esqueceu de dizer algo.";
			link.l1.go = "ClockTower_Visser_122";
		break;
		
		case "ClockTower_Visser_122":
			dialog.text = "\n"+"Bem-vindo ao respeitado Registro Naval da Companhia Holandesa das Índias Ocidentais.";
			link.l1 = "Até nos encontrarmos novamente, senhor diretor.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ClockTower_FINAL");
		break;
		

		//------------------Услуги конторы------------------//
		case "ClockTower_OfficeServices":
			if (npchar.id == "ClockTower_VanDoorn")
			{
				dialog.text = ""+UpperFirst(GetTitle(NPChar,false))+" "+pchar.name+". Como posso ajudar você hoje, em nome do meu cargo?";
			}
			if (npchar.id == "ClockTower_Visser")
			{
				if (CharacterIsAlive("ClockTower_VanDoorn"))
				{
					dialog.text = "Que bom te ver, "+GetTitle(NPChar,false)+"! Sempre às suas ordens. O que te interessa hoje?";
				}
				else
				{
					dialog.text = "Então? O que te interessa hoje?";
				}
			}
			link.l1 = "Você vai fazer uma inspeção no meu navio? Quero melhorar as características dele.";
			link.l1.go = "ClockTower_OfficeServices_audit"; // Аудит
			link.l2 = "Não estou satisfeito com a especialização do meu navio. Você pode providenciar novos documentos?";
			link.l2.go = "ClockTower_OfficeServices_changeTrait"; // Смена документов
			link.l3 = "Você vai registrar meu navio na companhia? Assim piratas e caçadores vão pensar duas vezes.";
			link.l3.go = "ClockTower_OfficeServices_buffSpec"; // Занесение в реестр
			if (!CheckAttribute(pchar, "questTemp.ShipInsurance"))
			{
				link.l4 = "Quero assegurar meus navios guardados no porto. Os atuais e os que vierem.";
				link.l4.go = "ClockTower_OfficeServices_Insurance"; // Страховка (пропадает после оплаты)
			}
			if(!CheckAttributeEqualTo(npchar, "last_logbook_date", LastSpeakDate()) && ClockTower_JournalsQty() > 0)
			{
				link.l5 = "Você aceita os diários de bordo dos capitães piratas, não é?";
				link.l5.go = "ClockTower_OfficeServices_logbook"; // Награда за пиратов (раз в сутки)
			}
			link.l6 = "Talvez não hoje. Tenha um bom dia.";
			link.l6.go = "ClockTower_OfficeServices_exit"; // Отказ
		break;

		// --> Аудит
		case "ClockTower_OfficeServices_audit":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "O custo depende do tamanho do navio. De qual embarcação estamos falando?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.Audit")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}
 
			if (n == 0)
			{
				dialog.text = "Infelizmente, a auditoria é um serviço único para cada navio. Mais alguma coisa?";
				link.l1 = "Vamos deixar para outra hora.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "Audit"))
			{
				n = GetAuditShipCost(sld);
				dialog.text = "Vamos ver... Isso vai custar "+n+" dobrões.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Prossiga.";
					link.l1.go = "ClockTower_OfficeServices_audit_upgradeShip";
				}
				link.l2 = "Mas... vamos deixar isso para outra hora.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "Receio que terei que recusar. Segundo o registro, seu navio foi para o fundo do mar há muitos anos, e tal fantasma do tempo não pode ser desfeito com uma simples canetada. Antes de podermos cooperar, você precisará restaurá-lo. Dizem que há um mestre na Isla Tesoro que aceitaria esse trabalho.";
				link.l1 = "Tá bom, obrigado.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$O navio já está melhorado";
				link.l1 = "Obrigado.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_audit_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetAuditShipCost(sld));
			UpgradeShipAudit(sld);
			dialog.text = "Pronto.";
			link.l1 = "Obrigado.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;
		// <-- Аудит

		// --> Улучшение специализации
		case "ClockTower_OfficeServices_buffSpec":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "O custo depende do tamanho do navio. De qual embarcação estamos falando?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				if (CheckAttribute(realShip, "tuning.SpecialityUpgrade")) continue;
				if (!IsFellowOurCrew(sld)) continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Infelizmente, o registro é um serviço único para cada navio. Mais alguma coisa?";
				link.l1 = "Vamos deixar para outra hora.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";
			if (CanUpgradeShip(sld, &sTemp, "SpecialityUpgrade"))
			{
				n = GetSpecialityUpgradeShipCost(sld);
				dialog.text = "Vamos ver... Isso vai custar "+n+" dobrões.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Prossiga.";
					link.l1.go = "ClockTower_OfficeServices_buffSpec_upgradeShip";
				}
				link.l2 = "Mas... vamos deixar isso para outra hora.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "Kaleuche")
			{
				dialog.text = "Receio que terei que recusar. Segundo o registro, seu navio foi para o fundo do mar há muitos anos, e um fantasma do tempo assim não pode ser desfeito com um simples traço de pena. Antes de podermos cooperar, você precisará restaurá-lo. Dizem que há um mestre na Isla Tesoro que aceitaria esse trabalho.";
				link.l1 = "Tá bom, obrigado.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "alreadyUpgraded")
			{
				dialog.text = "$O navio já está aprimorado";
				link.l1 = "Obrigado.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_buffSpec_upgradeShip":
			Achievment_Set("ach_CL_199");
			sld = GetCharacter(sti(Dialog.tmpIdx));
			RemoveDublonsFromPCharTotal(GetSpecialityUpgradeShipCost(sld));
			UpgradeShipSpeciality(sld);
			dialog.text = "Pronto.";
			link.l1 = "Obrigado.";
			link.l1.go = "ClockTower_OfficeServices_exit";
		break;
		// <-- Улучшение специализации

		// --> Смена трейта корабля
		case "ClockTower_OfficeServices_changeTrait":
			if (!IsShipInPort(npchar.city))
			{
				ClockTower_NoShipInPort(link);
				break;
			}
			n = 0;
			dialog.text = "O custo depende do tamanho do navio. De qual embarcação estamos falando?";
			for (i = 0; i < COMPANION_MAX; i++)
			{
				idx = GetCompanionIndex(pchar, i);
				if (idx < 0) continue;

				sld = GetCharacter(idx);
				realShip = GetRealShip(GetCharacterShipType(sld));
				sTemp = "";
				ShipTraitCanBeChanged(sld, &sTemp);
				if (sTemp == "EmptyShip" || sTemp == "QuestCompanion") continue;

				n++;
				sTemp = "l"+n;
				link.(sTemp) = XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName) + " '" + sld.Ship.Name + "'.";
				link.(sTemp).go = Dialog.currentNode + "_chosenIdx/" + idx;
			}

			if (n == 0)
			{
				dialog.text = "Hum. Não vejo nenhum dos seus navios no porto.";
				link.l1 = "Vamos deixar para outra hora.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
		break;

		case "ClockTower_OfficeServices_changeTrait_chosenIdx":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			sTemp = "";

			if (ShipTraitCanBeChanged(sld, &sTemp))
			{
				n = GetChangeShipTraitCost(sld);
				dialog.text = "Vamos ver... Isso vai custar "+n+" dobrões.";
				if (PCharDublonsTotal() > n)
				{
					link.l1 = "Prossiga.";
					link.l1.go = "ClockTower_OfficeServices_changeTrait_upgradeShip";
				}
				link.l2 = "Mas... vamos deixar isso para outra hora.";
				link.l2.go = "ClockTower_OfficeServices_exit";
			}
			else if (sTemp == "QuestSP")
			{
				dialog.text = "Infelizmente, isso não é possível. Seu navio é uma peça única, envolta em lendas. A caneta não tem poder algum em casos assim.";
				link.l1 = "Tá bom, obrigado.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			else
			{
				dialog.text = "Que tipo de especialização você está falando? Seu navio é versátil, não tem nenhuma característica marcante.";
				link.l1 = "Bom saber, obrigado.";
				link.l1.go = "ClockTower_OfficeServices_exit";
			}
			// тут можно обработать другие причины отказа, но на данный момент таковых не будет
		break;

		case "ClockTower_OfficeServices_changeTrait_upgradeShip":
			sld = GetCharacter(sti(Dialog.tmpIdx));
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
			DialogExit();
			LaunchChangeShipTraitScreen(sld);
		break;
		// <-- Смена трейта корабля

		// --> Страховка
		case "ClockTower_OfficeServices_Insurance":
			n = GetInsuranceCost();
			dialog.text = "Deixe-me ver... Isso vai custar "+n+" dobrões.";
			if (PCharDublonsTotal() > n)
			{
				link.l1 = "Prossiga.";
				link.l1.go = "ClockTower_OfficeServices_Insurance_done";
			}
			link.l2 = "Mas... vamos deixar isso para outra hora.";
			link.l2.go = "ClockTower_OfficeServices_exit";
		break;

		case "ClockTower_OfficeServices_Insurance_done":
			pchar.questTemp.ShipInsurance = true;
			RemoveDublonsFromPCharTotal(GetInsuranceCost());
			dialog.text = "Pronto.";
			link.l1 = "Obrigado.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			Achievment_Set("ach_CL_199");
		break;
		// <-- Страховка
		
		// Награда за пиратов (раз в сутки) -->
		case "ClockTower_OfficeServices_logbook":
			dialog.text = "Exatamente. A recompensa depende do número de registros e do perigo relativo dos seus donos.\n"+"Quantos troncos você trouxe?"link.l1 =""+ClockTower_JournalsQty();
			link.l1.go = "ClockTower_OfficeServices_logbook_1";
		break;
		
		case "ClockTower_OfficeServices_logbook_1":
			dialog.text = "A companhia agradece pelo seu trabalho. Você tem direito a "+JournalsCost()+" dobrões. Por favor, aceite-os e assine aqui"link.l1 ="Obrigado.";
			link.l1.go = "ClockTower_OfficeServices_exit";
			npchar.last_logbook_date = LastSpeakDate();
			Achievment_Set("ach_CL_199");
		break;
		// <-- Награда за пиратов

		case "ClockTower_OfficeServices_exit":
			DialogExit();
			NextDiag.CurrentNode = "ClockTower_OfficeServices";
		break;

		case "ClockTower_cabinFight":
			QuestAboardCabinDialogExitWithBattle("");
			DialogExit();
			ClockTower_CabinFight2();
		break;
		
		case "ClockTower_cabinPeace":
			DialogExit();
			AddDialogExitQuestFunction("ClockTower_cabinPeace");
		break;
	}
}

void ClockTower_NoShipInPort(ref link)
{
	dialog.text = "Não vejo seu navio no porto.";
	link.l1 = "Vamos deixar isso para outra hora.";
	link.l1.go = "ClockTower_OfficeServices_exit";
}

int ClockTower_PlaySound_rh2(string name)
{
    float x = stf(loadedLocation.locators.reload.houseO2.x);
    float y = stf(loadedLocation.locators.reload.houseO2.y);
    float z = stf(loadedLocation.locators.reload.houseO2.z);
    return SendMessage(Sound, "lslfff", MSG_SOUND_EVENT_PLAY, name, 0, x, y, z);
}
