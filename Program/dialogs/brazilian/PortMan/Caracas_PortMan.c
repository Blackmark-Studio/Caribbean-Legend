// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que tipo de perguntas?","O que você quer, "+GetAddress_Form(NPChar)+"?"),"Você já tentou me fazer uma pergunta "+GetAddress_Form(NPChar)+"...","Você já trouxe essa questão pela terceira vez hoje...","Olha, se você não tem nada pra me contar sobre os assuntos do porto, então não me incomode com suas perguntas.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Mudei de ideia.","Não tenho nada para conversar."),"Deixa pra lá.","De fato, já é a terceira vez...","Desculpe, mas no momento não estou interessado nos assuntos do porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toCarPortOffice" || pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik" || pchar.questTemp.SharkGoldFleet == "buyincar")
				{
					link.l1 = "O fato é que estou prestes a zarpar para Porto Bello a qualquer momento com uma carga de mercadorias que comprei de você na colônia. Pensei que talvez você tivesse alguma encomenda ou negócio que eu pudesse cuidar no caminho... Por uma taxa, é claro.";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "LightVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "Olá de novo. Entreguei sua carta em Porto Bello. Lá, me pediram para lhe trazer uma resposta.";
					link.l1.go = "SharkGoldFleet_09";
				}
				if(pchar.questTemp.SharkGoldFleet == "DifficultVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "Olá. Vim até você de Porto Bello. Seu colega da autoridade portuária local pediu para lhe entregar esta carta.";
					link.l1.go = "SharkGoldFleet_13";
				}
			}
			//<-- на пару с Акулой
		break;
		
		// belamour на пару с Акулой -->
		case "SharkGoldFleet":
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet.Fail21"))
			{
				pchar.questTemp.SharkGoldFleet = "toCurierDie";
				AddQuestRecord("SharkGoldFleet", "5");
				SGF_CreateCurierInWorld("");
				dialog.text = "Obrigado pela preocupação, mas não tenho nenhum caso assim. Na verdade, havia uma tarefa, mas você chegou literalmente alguns dias atrasado: já mandei um lugre-correio rápido para isso.";
				link.l1 = "Entendi... Bem, obrigado por isso.";
				link.l1.go = "exit";
			}
			else
			{
				if(!bImCasual) pchar.quest.SharkGoldFleet21.over = "yes"; 
				if(!bImCasual) pchar.quest.SharkGoldFleet30.over = "yes"; 
				if(GetCompanionQuantity(pchar) > 1)
				{
					pchar.questTemp.SharkGoldFleet = "toCurierWait";
					AddQuestRecord("SharkGoldFleet", "10");
					SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
					dialog.text = "Vejo que você não tem nem um único navio. Deve ser um comerciante muito rico, não é? Hmm... Mas conheço todos os mercadores locais com esquadras de vista, e ainda assim não conheço você. Então não me leve a mal, mas não posso confiar nada sério a você.";
					link.l1 = "Entendi... Bem, obrigado por isso.";
					link.l1.go = "exit";
				}
				else
				{
					if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
					{
						pchar.questTemp.SharkGoldFleet = "toCurierWait";
						AddQuestRecord("SharkGoldFleet", "11");
						SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
						dialog.text = "Hum... Eu tenho uma tarefa. Mas agora seu navio não serve. Preciso de um navio que seja rápido e poderoso ao mesmo tempo, e o seu não atende totalmente a esses requisitos. Pelo menos, não ao mesmo tempo. Então, por favor, me perdoe.";
						link.l1 = "Entendi... Bem, obrigado por isso.";
						link.l1.go = "exit";
					}
					else
					{
						if(!CheckAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk"))
						{
							pchar.questTemp.SharkGoldFleet = "toCurierWait";
							AddQuestRecord("SharkGoldFleet", "12");
							SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
							dialog.text = "Tenho algo para resolver... E você tem um bom navio. Só que ele não parece um navio mercante. E, pelo que vejo, você não tem uma licença de longo prazo da Companhia Holandesa das Índias Ocidentais. Não leve a mal, mas você não me parece um comerciante. Não posso correr esse risco.";
							link.l1 = "Entendi... Bem, obrigado por isso.";
							link.l1.go = "exit";
						}
						else
						{
							if(pchar.questTemp.SharkGoldFleet != "toCarPortOffice" || GetSquadronGoods(pchar, GOOD_COFFEE) < 300 || GetSquadronGoods(pchar, GOOD_CHOCOLATE) < 300)
							{
								pchar.questTemp.SharkGoldFleet = "toCurierWait";
								AddQuestRecord("SharkGoldFleet", "13");
								SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
								dialog.text = "Eu tenho um trabalho para fazer... E você tem um bom navio. Só que agora eu não entendo o que você vai negociar... Você disse que ia para Porto Bello vender a mercadoria, mas, pelo que eu sei, você não comprou nada de nós aqui na colônia. Não leve a mal, mas você não me parece um comerciante. Eu não posso correr esse risco.";
								link.l1 = "Entendi... Bem, obrigado por isso.";
								link.l1.go = "exit";
							}
							else
							{
								dialog.text = "Tenho coisas a fazer. Claro, não te conheço... Mas, pra falar a verdade, só lembro de mercadores com esquadras no nome. O resto – não. E você tem uma licença de longo prazo, então está claro que é um comerciante experiente. Mas o seu navio é interessante. Por que negociar com uma fragata?";
								link.l1 = "Hah, esta não é uma fragata comum. Ela pode atingir velocidades muito altas mesmo com o porão cheio. Sempre é mais fácil fugir dos piratas do que enfrentá-los, não é? Embora minha embarcação tenha uma capacidade menor do que os navios mercantes comuns, o risco é muito menor.";
								link.l1.go = "SharkGoldFleet_01";
							}
						}
						
					}
					
				}
			}
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = " Hmm, mas você tem razão! Os espanhóis sabem construir navios, não é? Sim, sim, percebi logo que essa bela embarcação saiu dos estaleiros daqui. E sim, me disseram hoje mesmo que você comprou um lote de café e cacau do nosso comerciante para revender em Porto Bello. Negócio esperto, eu diria. Quem não entende de comércio não sabe que esses produtos são baratos aqui, graças às plantações, e em Porto Bello são muito procurados, já que de lá seguem para a metrópole.";
			link.l1 = "Bem, é disso que se trata, señor. Por uns poucos pesos, eu não levaria meu barco tão longe.";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Bem, para ser sincero, eu tenho um trabalho para você. E é muito bom que você tenha um navio tão rápido, que também saiba se defender em caso de emergência.";
			link.l1 = "Espere, senhor... Seu caso sugere que eu preciso lutar...?";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "Não, não! Na verdade, minha tarefa é o mais simples possível. Preciso que você entregue uma carta à Autoridade Portuária em Porto Bello. A carta está lacrada e não deve ser aberta. Ninguém precisa comentar sobre isso também, a correspondência é... pessoal. Entregue em mãos. O prazo é de dez dias. Depois disso, não terá mais importância.";
			link.l1 = "Tão simples assim? E quanto vou receber por isso?";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "Cinco mil pesos. Considere isso como pagamento por eu não precisar enviar um lugre de mensageiro até Porto Bello.";
			link.l1 = "E quais eram suas perguntas sobre mim e meu navio?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "Não importa. É só que a correspondência é importante, e preciso ter certeza de que vai chegar ao destinatário. Então, nada demais. Burocracia... Para uma pessoa comum, esses documentos não têm interesse algum.";
			link.l1 = "Bem, eu concordo. Vamos pegar seus documentos aqui. Assim que eu chegar em Porto Bello, vou entregá-los ao seu colega. Vou resolver isso em dez dias, não se preocupe.";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "Um momento. Me desculpe, esqueci completamente o seu nome. Poderia me dizer, por favor? Preciso anotá-lo nos documentos.";
			link.l1 = "Meu nome é Andreas Garcia.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Obrigado. Então... Ótimo. Lembre-se, é você quem deve entregar este documento, e diretamente nas mãos do destinatário. Aqui está. A recompensa será entregue a você pelo chefe da Autoridade Portuária em Porto Bello. Boa viagem!";
			link.l1 = "Obrigado! Agora, com licença.";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToPB10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			AddCharacterSkillDontClearExp(pchar, SKILL_LEADERSHIP, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_SNEAK, 1);
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_SharkGoldFleet_1");
			AddQuestRecord("SharkGoldFleet", "14");
			pchar.questTemp.SharkGoldFleet = "toPBPortOffice";
		break;
		
		case "SharkGoldFleet_09":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "Ótimo! Você me ajudou muito. Teve alguma dificuldade?";
			link.l1 = "Não, não houve dificuldades. É verdade, seu colega te xingou: disse que vocês aqui são todos uns mãos de vaca, porque não mandam um navio-correio, só usam mercadores de passagem, e ainda cobram do destinatário pelo serviço. Ele ameaçou escrever uma reclamação para Havana...";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "O quê?! Eu sou o rabugento?! O que ele pensa que é? Primeiro, fique com seus cinco... não, seis mil pesos! Eu estou chorando de verdade!";
			link.l1 = "Obrigado. É bom ver que seu colega estava enganado sobre você.";
			link.l1.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			AddMoneyToCharacter(pchar, 6000);
			dialog.text = "E em segundo lugar, esse canalha parece ter esquecido como, dois meses atrás, ele me deixou com todas as despesas de manutenção de um navio mercante que saiu de Caracas para Porto Bello, e de lá para Havana! E nós combinamos que ele pagaria pela segunda parte da viagem! Ele nunca quitou a dívida, mas prometeu que resolveria tudo no mês passado! E ainda dizem que eu sou o pão-duro... Pois bem, vou escrever uma queixa contra ele para Havana eu mesmo!";
			link.l1 = "Bem, você tem as paixões da corte de Madri, é claro ...";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "LightVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "Não, pensando bem ... Que sujeito insolente! Tudo bem, vou lidar com ele de novo ... Agora, peço licença: tenho assuntos urgentes a tratar. Foi um prazer fazer negócios com você!";
			link.l1 = "E boa sorte pra você!";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_13":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "Ótimo! Você me ajudou muito. Mas olha só, mandei um lugre mensageiro pra eles, e eles mandaram a resposta de volta com um navio de passagem. Pois é... E depois ainda reclamam que só tem mão de vaca por aqui.";
			link.l1 = "Bem, talvez tenham economizado o dinheiro do mensageiro ...";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			AddMoneyToCharacter(pchar, 5000);
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "DifficultVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "Não é 'talvez', é com certeza, estou te dizendo! Tudo bem, não importa. Aqui, pegue seu trabalho. E agora eu tenho muito o que fazer, com licença.";
			link.l1 = "Bem, talvez eles tenham economizado o dinheiro do mensageiro ...";
			link.l1.go = "exit";
		break;
		// <-- на пару с Акулой
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
