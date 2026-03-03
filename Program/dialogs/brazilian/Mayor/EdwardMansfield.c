// Эдвард Мэнсфилд, глава буканьеров и авторитетный пират, английская линейка
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================
	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
            if (CheckAttribute(npchar, "Sp5LaVegaAttackDone"))
            {
            	if (NPChar.quest.meeting == "0")
				{
					dialog.Text = TimeGreeting()+"! Eu sou "+GetFullName(NPChar)+", o novo governador desse buraco. Não vai ser fácil colocar os marginais locais na linha, mas eles já não representam mais ameaça para as colônias espanholas.";
					Link.l1 = "É um prazer conhecê-lo. Sou o Capitão "+GetFullName(Pchar)+". Desculpe, mas eu preciso ir.";
					Link.l1.go = "exit";
					NPChar.quest.meeting = "1";
				}
				else
				{
					dialog.Text = TimeGreeting()+". Estou ocupado, muito ocupado, preciso manter os bandidos locais sob controle para evitar qualquer ameaça às colônias espanholas.";
					Link.l1 = "Então não vou te incomodar.";
					Link.l1.go = "exit";
				}
            }
            else
            {
				dialog.text = NPCStringReactionRepeat("Tem algo pra me dizer? Não? Então "+GetSexPhrase("Saia daqui!","Peço que não me incomode.")+"","Acho que fui bem claro...","Apesar de eu já ter deixado tudo claro, você continua me irritando!","Bem, você é incomparável "+GetSexPhrase("grosseiro demais, mon chéri","que falta de respeito, garota","que falta de respeito, garota")+"...","repeat",30,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Estou indo embora.","Sim, "+npchar.name+", entendi.","Desculpe, "+npchar.name+"...","Ai...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}


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
								link.l2 = "Eu peguei o rastro, mas preciso de umas moedas — 30.000 pesos pra atrair o rato pra fora do buraco.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "Aqui, olha esta carta que encontrei no corpo do contrabandista";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "Está feito. Norman Vigo e o navio dele agora pertencem ao diabo do mar.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Hm... Trabalho, é? Na verdade, ainda bem que você veio falar comigo. Preciso de alguém de fora. Quero descobrir umas coisas na cidade mais próxima, mas meus homens já são conhecidos por lá. Não posso prometer muito, mas você vai ganhar alguma coisa.";
			link.l1 = "Qual é a missão?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Desculpe, mas não vou arriscar por umas migalhas. Adeus.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "Então escuta, há um mês fechei um acordo para entregar 200 escravos com o capitão da escuna 'Saintblue'. Minha intenção era vendê-los para o dono da plantação local. O prazo já passou e o cliente começou a ficar preocupado, mas ontem me disseram que a escuna foi vista perto da ilha. Mas! O capitão não apareceu. Hoje, meu cliente exigiu o adiantamento de volta e disse que recebeu uma oferta de escravos de outro vendedor. Mais caro, mas o lote inteiro de uma vez.";
			link.l1 = "E daí? Eu tenho que arranjar 200 escravos em poucos dias só pra te salvar de perder um adiantamento? Por umas moedas?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Claro que não. Eu pareço idiota pra você? Não vou devolver o adiantamento de jeito nenhum. Mas preciso de provas de que os escravos que ofereceram pra ele são meus. Encontre quem fez essa nova proposta pra ele e você recebe seus 10.000 pesos. Fechado?";
			link.l1 = "Estou dentro. Você desconfia de alguém?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Nem pensar. Procure outra pessoa, só por 10.000? Desculpe, mas assim não vai rolar.";
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
			dialog.text = "Exatamente! Estou procurando por ele. Matar meus concorrentes e trazer meus escravos de volta não são suas prioridades. Eu quero aquele rato—na verdade, quero a cabeça dele numa estaca, pra ser sincero. Agora entende por que meus homens não podem saber nada sobre sua missão? Vou desconfiar de todo mundo até descobrir quem está vendendo as informações. E isso é algo que eu realmente não quero...";
			link.l1 = "Entendi. Então vou ficar na minha. Estou a caminho.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Trinta mil, é isso que você quer? É muito dinheiro... Só posso te dar 5.000 pesos, é tudo que tenho agora. E nem pense em fugir com esse dinheiro, senão eu te acho e te penduro na cerca mais próxima! Entendeu?";
			link.l1 = "Tá bom, então me dá cinco mil...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Pegue. Estou esperando o resultado da sua busca.";
			link.l1 = "Vai ficar tudo bem.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ha! Excelente notícia! Eu tinha certeza que você conseguiria. Tenho umas informações interessantes.";
			link.l1 = "Terminei meu serviço e quero meus dez mil.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Claro, aqui está sua recompensa. Mas não vá embora ainda, tenho mais uma tarefa pra você.\nPfaifer é tripulante do Norman Vigo, do lugre 'Septima'. Tenho certeza de que Norman Vigo é o rato, mesmo sendo um dos nossos. Ele foi visto recentemente nas águas perto da ilha. Seu trabalho é mandar esse rato pro diabo do mar. Você não me decepcionou da primeira vez, então quero que resolva isso também. Vou te pagar 15.000 pesos. Fechado?";
			link.l1 = "Deixa comigo! Pode considerar o traidor morto.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "Sabe, eu não quero me meter nisso... De qualquer forma, não tenho tempo. Desculpa, mas estou indo embora.";
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
			dialog.text = "Eu sei, eu sei. Meus homens estavam de olho na batalha e já me contaram sobre sua vitória impecável. Muito bem, você fez seu trabalho direito. Aqui estão 15.000 pesos, como prometido. E obrigado, você me ajudou bastante.";
			link.l1 = "Está bem, fiquei feliz em ajudar! Mas preciso ir agora, já fiquei aqui tempo demais e tenho muita coisa pra fazer. Adeus!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;
				
 		case "No_Mansfield_first_time":
			dialog.text = "Saudações, meu nome é Alistair Good. Fui eleito chefe dos bucaneiros depois da morte de Mansfield.";
			link.l1 = "Prazer em conhecê-lo, Alistair.";
			link.l1.go = "exit";
			NextDiag.TempNode = "No_Mansfield";
  		break;
 		case "No_Mansfield":
			dialog.text = "Não tenho tempo pra falar com você. Volte mais tarde.";
			link.l1 = "Já estou indo embora.";
			link.l1.go = "exit";
  		break;
		

// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Pegar","Pegar")+" fora!","Saia da minha casa!");
			link.l1 = "Opa...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Мэнсфилдом через 30 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Não me incomode, lembre-se disso.";
        			link.l1 = "Entendi.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("LaVega_town","reload","reload6");
		break;
// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
