// Соукинс в Пуэрто-Принсипе
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
            dialog.text = "Você tem algum assunto comigo? Não? Então cai fora!";
			link.l1 = "Já estou indo embora.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";


					if (npchar.city == sti(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "Tem algum trabalho pra mim?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "Eu peguei o rastro, mas preciso de umas moedas – 30.000 pesos para tirar o rato do buraco.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "Aqui, olha esta carta que encontrei no corpo do contrabandista";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "Está feito. Norman Vigo e seu navio já foram para o diabo do mar.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Hm... trabalho, é isso? Na verdade, ainda bem que você veio falar comigo. Preciso de alguém de fora. Quero descobrir uma coisa na cidade mais próxima, mas meus homens são conhecidos por lá. Não posso prometer muito, mas você vai receber alguma coisa.";
			link.l1 = "Boa! Qual é a missão?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Desculpe, mas não vou arriscar por algumas migalhas. Adeus.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "Então escuta, há um mês eu fechei um acordo para entregar 200 escravos com o capitão da escuna 'Saintblue'. Minha intenção era vendê-los para o dono da plantação local. O prazo passou e o cliente começou a ficar preocupado, mas ontem me disseram que a escuna foi vista perto da ilha. Mas! O capitão não apareceu. Hoje, meu cliente exigiu que eu devolvesse o adiantamento e disse que ofereceram a ele escravos de outro vendedor. Mais caro, mas o lote inteiro de uma vez só.";
			link.l1 = "E daí? Eu tenho que encontrar 200 escravos em poucos dias só pra te salvar de perder um adiantamento? Por umas moedas?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Claro que não. Eu pareço idiota pra você? Não vou devolver o adiantamento dele de qualquer jeito. Mas preciso de provas de que os escravos oferecidos a ele são meus. Descubra quem fez essa nova proposta pra ele e você recebe seus 10.000 pesos. Fechado?";
			link.l1 = "Estou dentro. Você tem alguma suspeita? Quem poderia ter feito isso?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Nem pensar. Procure outra pessoa. Só 10.000? Desculpe, mas isso não serve.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "Se eu tivesse alguma ideia, nunca usaria seus serviços. Aqueles homens já estariam mortos. Mas estou curioso para saber como eles descobriram sobre a carga do 'Saintblue' e meu cliente. Parece que foi bem fácil para eles. Entende agora?";
			link.l1 = "Sim, alguém te traiu.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "Exatamente! Estou procurando por ele. Matar meus concorrentes e trazer meus escravos de volta não é sua prioridade. Eu preciso daquele rato—na verdade, da cabeça dele numa estaca, pra ser sincero. Agora entende por que meus homens não devem saber nada sobre a sua missão? Vou desconfiar de todo mundo até descobrir quem está vendendo as informações. E eu realmente não quero isso...";
			link.l1 = "Entendi. Então vou ficar na minha. Estou a caminho.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Trinta mil, você disse? Isso é muito dinheiro... Só posso te dar 5.000 pesos, é tudo que tenho agora. E nem pense em fugir com o dinheiro, senão eu te acho e te enforco na cerca mais próxima! Entendeu?";
			link.l1 = "Certo, então me dê cinco mil...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Pegue. Estou esperando pelo resultado da sua busca.";
			link.l1 = "Vai dar tudo certo.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ha! Excelente notícia! Eu sabia que você conseguiria. Tenho umas informações interessantes.";
			link.l1 = "Eu fiz o meu trabalho e quero meus dez mil.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Claro, aqui está sua recompensa. Mas não vá embora ainda, tenho mais uma tarefa pra você.\nPfaifer é um dos tripulantes do Norman Vigo, do lugre 'Septima'. Tenho certeza de que Norman Vigo é o rato, mesmo sendo um dos nossos. Ele foi visto recentemente nas águas perto da ilha. Seu trabalho é mandar esse rato pro fundo do mar. Você não me decepcionou da primeira vez, então quero que cuide disso também. Vou te pagar 15.000 pesos. Fechado?";
			link.l1 = "Deixa comigo! Considere o traidor Norman Vigo morto.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "Sabe, eu não quero me meter nisso... De qualquer jeito, não tenho tempo. Desculpa, mas tô indo.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "Eu sei, eu sei. Meus homens estavam de olho na batalha e já me contaram sobre sua vitória impecável. Muito bem, você fez seu trabalho direito. Aqui estão os 15.000 pesos que prometi. E obrigado, você me ajudou bastante.";
			link.l1 = "Está tudo bem, fiquei feliz em ajudar! Mas agora preciso ir, já fiquei aqui tempo demais e tenho muita coisa pra fazer. Até logo!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;


	}
}
